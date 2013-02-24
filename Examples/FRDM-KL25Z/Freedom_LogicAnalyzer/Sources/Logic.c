/*
 * Logic.c
 *
 *  Created on: Feb 2, 2013
 *      Author: Erich Styger
 */
#include "Logic.h"
#include "AS1.h"
#include "LEDR.h"
#include "LEDG.h"
#include "LEDB.h"
#include "Byte1.h"
#include "TI1.h"
#include "TI2.h"

/* 
 * SUMP command definitions, 
 * see http://www.sump.org/projects/analyzer/protocol/ 
 * http://dangerousprototypes.com/docs/The_Logic_Sniffer%27s_extended_SUMP_protocol 
 *
 * Current status is shown with
 * - Re LED blinking: device is idle
 * - Green LED on: start capturing
 * - Blue LED on: trigger found
 */

#define DEVICE_NAME             "FRDM-KL25Z LogicLogger"
#define DEVICE_FW_VERSION       "V1.1"
#define DEVICE_ANCILLARY        "V2.0"
#define DEVICE_NOF_PROBES       8 /* number of probes */
#define DEVICE_PROTOCOL_VERSION 2 /* always 2! */

#define SUMP_RESET                0x00  /* resets the device */
#define SUMP_RUN                  0x01  /* arms the trigger */
#define SUMP_ID                   0x02  /* asks for device identification. First three bytes are "SLA" followed by either 0 or 1 */
#define SUMP_SELFTEST             0x03  /* trigger self-test */
#define SUMP_GET_METADATA         0x04  /* as the name defines */
#define SUMP_RLE                  0x05  /* finish now, end current RLE capture */
#define SUMP_RUN_ADVANCED_TRIGGER 0x0F
#define SUMP_SET_DIVIDER          0x80 /* set sample frequency, which is f=clock/(x+1), so it is 999 for 100 kHz, 1999 for 50 kHz */
#define SUMP_SET_READ_DELAY_COUNT 0x81
#define SUMP_SET_FLAGS            0x82
  #define SUMP_FLAGS_TEST_DATA    (1<<10)   /* Internal test pattern mode (supplies data internally) (http://dangerousprototypes.com/docs/The_Logic_Sniffer%27s_extended_SUMP_protocol)  */
#define SUMP_WRITE_TRIGGER_SELECT 0x9E
#define SUMP_WRITE_TRIGGER_DATA   0x9F

#define SUMP_SET_TRIGGER_MASK_0   0xC0 /* trigger mask stage 0 */
#define SUMP_SET_TRIGGER_VALUE_0  0xC1 /* trigger value stage 0 */
#define SUMP_SET_TRIGGER_CONFIG_0 0xC2 /* trigger configuration stage 0 */

#define SUMP_SET_TRIGGER_MASK_1   0xC4 /* trigger mask stage 1 */
#define SUMP_SET_TRIGGER_VALUE_1  0xC5 /* trigger value stage 1 */
#define SUMP_SET_TRIGGER_CONFIG_1 0xC6 /* trigger configuration stage 1 */

#define SUMP_SET_TRIGGER_MASK_2   0xC8 /* trigger mask stage 2 */
#define SUMP_SET_TRIGGER_VALUE_2  0xC9 /* trigger value stage 2 */
#define SUMP_SET_TRIGGER_CONFIG_2 0xCA /* trigger configuration stage 2 */

#define SUMP_SET_TRIGGER_MASK_3   0xCC /* trigger mask stage 3 */
#define SUMP_SET_TRIGGER_VALUE_3  0xCD /* trigger value stage 3 */
#define SUMP_SET_TRIGGER_CONFIG_3 0xCE /* trigger configuration stage 3 */

/* actually we support only trigger stage 0 */
#define SUMP_TRIGGER_STAGES 1

typedef uint32_t triggerMask;
typedef uint32_t triggerValues;
typedef uint32_t triggerConfiguration;
typedef uint32_t triggerFlags;
typedef uint32_t frequencyDivider;
typedef uint32_t RandDCount;

typedef struct trigger_data {
  triggerMask mask;     /* if bit is set, that probe has a trigger */
  triggerValues values; /* trigger if (probe&mask)==values */
  triggerConfiguration configuration; /* NYI: delay, level, channel, serial, start */
} TRIGGER_DATA;

/* Trigger Data */
static TRIGGER_DATA triggerData[1]; /* we actually support only ONE trigger stage */
static frequencyDivider divider; /* defines the sampling frequency, based on MAX_SAMPLERATE. f=MAX_SAMPLERATE/(divider+1) */
static RandDCount rdCount; // not supported in V1.01 BETA1
static triggerFlags flags; /* right now only the test data flag is supported */

/* Buffer size */
#define BUFFERSIZE     (14*1024) /* maximum buffer size */
#define MAX_SAMPLERATE 750000  /* max 750 kHz for now */

/* Sampling buffer */
static uint8_t buffer[BUFFERSIZE];
static int bufferIdx;
static volatile bool doSampling = FALSE;
static volatile bool finishedSampling = FALSE;
static volatile bool triggered = FALSE;

static LDD_TDeviceData *TimerHndl;
static bool isFastSampling = FALSE;

/* \brief Send single character over UART */
static void PutChar(uint8_t ch) {
  while(AS1_SendChar(ch)!=ERR_OK) {
    /* retry */
  }
}

/* \brief Send null terminated string over UART */
static void PutString(char *s) {
  while (*s != 0) {
    PutChar(*s);
    s++;
  }
}

/* \brief Send 32bit unsigned integer as SUMP meta data */
static void SUMP_sendmeta_uint32(char type, unsigned int i) {
  PutChar(type);
  PutChar((i>>24)&0xff);
  PutChar((i>>16)&0xff);
  PutChar((i>>8)&0xff);
  PutChar(i&0xff);
}

/* \brief Send 8bit unsigned integer as SUMP meta data */
static void SUMP_sendmeta_uint8(char type, unsigned char i) {
  PutChar(type);
  PutChar(i);
}

/* \brief Send it over UART */
static void SendData(void) {
  int i;
  
  for (i = 0; i < BUFFERSIZE; i++) {
    PutChar(buffer[i]);
  }
}

static uint8_t GetChar(void) {
  uint8_t ch;
  
  while(AS1_RecvChar(&ch)!=ERR_OK) {}
  return ch;
}

/* \brief Do sampling if trigger is active*/
void LOGIC_Sample(void) {
  /* we support BITS 0-DEVICE_NOF_PROBES (up to 32) */
  unsigned long data;

  //LEDB_Neg();
  if (doSampling) { /* Acquire data */
    if (flags&SUMP_FLAGS_TEST_DATA) {
      data = bufferIdx; /* use test data */
    } else {
      data = Byte1_GetVal();
    }
    if (!triggered && triggerData[0].mask!=0) {
      if ((data&triggerData[0].mask)==triggerData[0].values) { /* matching trigger */
        LEDG_Off(); LEDB_On(); /* blue led on: found trigger */
        triggered = TRUE;
      }
    }
    if (triggered) {
      if (bufferIdx != 0) {
        buffer[bufferIdx-1] = (uint8_t)(data&0xFF);
        bufferIdx--;
        if (bufferIdx == 0) { /* filled buffer */
          finishedSampling = TRUE;
        }
      }
    }
  }
}

static void SetSampleFrequency(uint32_t divider) {
  /* just supporting two modes right now */
  if (divider==499 || divider==0) {
    isFastSampling = TRUE;
    TI1_Enable();
    TI2_Disable();
  } else {
    isFastSampling = FALSE;
    TI1_Disable();
    TI2_Enable();
  }
}

void LOGIC_Run(void) {
  unsigned char cmd;
  int i = 0;

  /* prepare SUMP variables */
  triggerData[0].mask = 0;
  triggerData[0].values = 0;
  triggerData[0].configuration = 0;
  //rdCount = 0;
  flags = 0;
  TimerHndl = TU1_Init(NULL);
  SetSampleFrequency(0);
  for (;;) {
    if (!doSampling) {
      i++;
      if (   (isFastSampling && i>50000)
          ||  (i>200000)
         ) 
      {
        /* heart-beat LED (red) if not sampling: 
         * fast blinking if fast sampling mode was used, 
         * slow for slow sampling mode */
        LEDR_Neg();
        i = 0;
      }
    }
    if (finishedSampling) {
      finishedSampling = FALSE;
      doSampling = FALSE;
      triggered = FALSE;
      SendData();
      LEDB_Off();
      LEDG_Off();
    }
    if (AS1_GetCharsInRxBuf() != 0) {
      cmd = GetChar();
      switch (cmd) {
      case SUMP_RESET:
        finishedSampling = FALSE;
        doSampling = FALSE;
        triggered = FALSE;
        LEDB_Off();
        LEDG_Off();
        break;
      case SUMP_RUN:
        bufferIdx = BUFFERSIZE;
        finishedSampling = FALSE;
        doSampling = TRUE;
        if (triggerData[0].mask == 0) {
          /* no trigger active, simply start sampling */
          LEDB_On();
          triggered = TRUE;
        } else {
          LEDG_On();
        }
        LEDR_Off();
        break;
      case SUMP_ID:
        PutString("1ALS");
        break;
      case SUMP_GET_METADATA:
        /* device name: */
        PutChar(0x01);
        PutString(DEVICE_NAME);
        PutChar(0x00);
        /* 'Firmware version: */
        PutChar(0x02);
        PutString(DEVICE_FW_VERSION);
        PutChar(0x00);
        /* 'Ancillary' version: */
        PutChar(0x03);
        PutString(DEVICE_ANCILLARY);
        PutChar(0x00);
        /* amount of sample memory available (bytes) */
        SUMP_sendmeta_uint32(0x21, BUFFERSIZE);
        /* maximum sample rate (Hz) */
        SUMP_sendmeta_uint32(0x23, MAX_SAMPLERATE);
        /* number of usable probes (short) */
        SUMP_sendmeta_uint8(0x40, DEVICE_NOF_PROBES);
        /* protocol version (short) */
        SUMP_sendmeta_uint8(0x41, DEVICE_PROTOCOL_VERSION);
        /* end of meta data */
        PutChar(0x00);
        break;
        /* long commands.. consume bytes from UART, NYI */
      case SUMP_SET_TRIGGER_MASK_0:
        triggerData[0].mask = GetChar();
        triggerData[0].mask |= (GetChar()<<8);
        triggerData[0].mask |= (GetChar()<<16);
        triggerData[0].mask |= (GetChar()<<24);
        break;
      case SUMP_SET_TRIGGER_VALUE_0:
        triggerData[0].values = GetChar();
        triggerData[0].values |= (GetChar()<<8);
        triggerData[0].values |= (GetChar()<<16);
        triggerData[0].values |= (GetChar()<<24);
        break;
      case SUMP_SET_TRIGGER_CONFIG_0:
        triggerData[0].configuration = GetChar();
        triggerData[0].configuration |= (GetChar()<<8);
        triggerData[0].configuration |= (GetChar()<<16);
        triggerData[0].configuration |= (GetChar()<<24);
        break;
      case SUMP_SET_TRIGGER_MASK_1:
      case SUMP_SET_TRIGGER_MASK_2:
      case SUMP_SET_TRIGGER_MASK_3: /* NYI */
      case SUMP_SET_TRIGGER_VALUE_1:
      case SUMP_SET_TRIGGER_VALUE_2:
      case SUMP_SET_TRIGGER_VALUE_3: /* NYI */
      case SUMP_SET_TRIGGER_CONFIG_1:
      case SUMP_SET_TRIGGER_CONFIG_2:
      case SUMP_SET_TRIGGER_CONFIG_3: /* NYI */
        (void)GetChar();
        (void)GetChar();
        (void)GetChar();
        (void)GetChar();
        break;
      case SUMP_SET_DIVIDER:
        divider = GetChar();
        divider |= (GetChar() << 8);
        divider |= (GetChar() << 16);
        (void) GetChar();
        SetSampleFrequency(divider);
        break;
      case SUMP_SET_READ_DELAY_COUNT:
        rdCount = GetChar();
        rdCount |= (GetChar()<<8);
        rdCount |= (GetChar()<<16);
        rdCount |= (GetChar()<<24);
        break;
      case SUMP_SET_FLAGS:
        flags = GetChar();
        flags |= (GetChar()<<8);
        flags |= (GetChar()<<16);
        flags |= (GetChar()<<24);
        break;
      default:
        break;
      } /* switch */
    }
  }
}

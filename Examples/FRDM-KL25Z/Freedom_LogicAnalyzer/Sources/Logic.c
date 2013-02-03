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

/* 
 * SUMP command definitions, 
 * see http://www.sump.org/projects/analyzer/protocol/ 
 * http://dangerousprototypes.com/docs/The_Logic_Sniffer%27s_extended_SUMP_protocol 
 */

#define DEVICE_NAME             "FRDM-KL25Z LogicLogger"
#define DEVICE_FW_VERSION       "V1.0"
#define DEVICE_ANCILLARY        "V2.0"
#define DEVICE_NOF_PROBES       8 /* number of probes */
#define DEVICE_PROTOCOL_VERSION 2 /* always 2! */

#define SUMP_RESET 0x00     /* resets the device */
#define SUMP_RUN   0x01     /* arms the trigger */
#define SUMP_ID    0x02     /* asks for device identification. First three bytes are "SLA" followed by either 0 or 1 */
#define SUMP_GET_METADATA 0x04

/* Buffer size */
#define BUFFERSIZE 14*1024
#define MAX_SAMPLERATE 10000000

/* Sampling buffer */
static uint8_t buffer[BUFFERSIZE];
static int bufferIdx;
static volatile bool doSampling = FALSE;
static volatile bool finishedSampling = FALSE;

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
  PutChar((i >> 24) & 0xff);
  PutChar((i >> 16) & 0xff);
  PutChar((i >> 8) & 0xff);
  PutChar(i & 0xff);
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

/* \brief Do sampling */
void LOGIC_Sample(void) {
  if (doSampling) {   /* Acquire data */
    if (bufferIdx!=0) {
#if 1 /* use test data */
      buffer[bufferIdx-1] = bufferIdx;
#else
      buffer[bufferIdx-1] = Byte1_GetVal();
#endif
      bufferIdx--;
      if (bufferIdx==0) {
        finishedSampling = TRUE;
      }
    }
  }
}

uint8_t GetChar(void) {
  uint8_t ch;
  
  while(AS1_RecvChar(&ch)!=ERR_OK) {}
  return ch;
}

void LOGIC_Run(void) {
  unsigned char cmd;
  int i=0;

  for(;;) {
    i++;
    if (i>100000) { /* heartbeat LED */
      LEDR_Neg();
      i = 0;
    }
    if (finishedSampling) {
      SendData();
      finishedSampling = FALSE;
      LEDB_Off();
    }
    if (AS1_GetCharsInRxBuf()!=0) {
      cmd = GetChar();
      switch (cmd) {
        case SUMP_RESET:
            break;
        case SUMP_RUN:
            LEDB_On();
            bufferIdx = BUFFERSIZE;
            finishedSampling = FALSE;
            doSampling = TRUE;
            break;
        case SUMP_ID:
            PutString("1ALS");
            break;
        case SUMP_GET_METADATA:
            /* device name: */
            PutChar(0x01); PutString(DEVICE_NAME); PutChar(0x00);
            /* 'Firmware version: */
            PutChar(0x02); PutString(DEVICE_FW_VERSION); PutChar(0x00);
            /* 'Ancillary' version: */
            PutChar(0x03); PutString(DEVICE_ANCILLARY); PutChar(0x00);
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
        case 0xC0:
        case 0xC4:
        case 0xC8:
        case 0xCC:
        case 0xC1:
        case 0xC5:
        case 0xC9:
        case 0xCD:
        case 0xC2:
        case 0xC6:
        case 0xCA:
        case 0xCE:
        case 0x80:
        case 0x81:
        case 0x82:
          (void)GetChar();
          (void)GetChar();
          (void)GetChar();
          (void)GetChar();
          break;
        default:
          break;
      } /* switch */
    }
  }
}

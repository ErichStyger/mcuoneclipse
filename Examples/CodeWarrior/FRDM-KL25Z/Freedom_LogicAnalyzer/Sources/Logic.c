/*
 * Logic.c
 *
 *  Created on: Feb 2, 2013
 *      Author: Erich Styger
 *  Edited on:  Feb 10, 2013 by: Reiner Geiger why: started with simple trigger support
 *   			Feb 11, 2013 by: Reiner Geiger why: started with 1 MHz support
 *   			Feb 25, 2013 by: Reiner Geiger why: updating to Version 1.1 from E. Styger
 *   			Mar 20, 2013 by: Reiner Geiger why: 1st DMA based Impl. works up to 4 MHz
 *  
 */
#include "IO_Map.h"
#include "Logic.h"
#include "AS1.h"
#include "LEDR.h"
#include "LEDG.h"
#include "Byte1.h"
#include "TPM_PDD.h"
#include "DMA_PDD.h"
#include "DMAMUX_PDD.h"

/* 
 * SUMP command definitions, 
 * see http://www.sump.org/projects/analyzer/protocol/ 
 * http://dangerousprototypes.com/docs/The_Logic_Sniffer%27s_extended_SUMP_protocol 
 */

/* Trigger Data and Sampling setup */
static TRIGGER_DATA triggerData[4]; // we actually support only ONE trigger stage
static RandDCount rdCount; // actually not supported 
static triggerFlags flags; // actually not supported 

/* Sampling buffer */
static unsigned int bufferSize = BUFFERSIZE;
static volatile uint8_t sampleBuffer[BUFFERSIZE];

/* Sampling Logic */
static volatile bool finishedSampling = FALSE;

/* utility */
#define DEFAULT_HEARTBEAT_COUNTER 250000
#define LOG_TMR_FREQ  48000000UL  /* 48 MHz TPM clock */


//##########################################################################
/* DMA Functions */
static void InitDMA(void) {
  /* enable DMA MUX0: */
  DMAMUX_PDD_EnableChannel(DMAMUX0_BASE_PTR, 0, PDD_ENABLE); /* enable DMA MUX0 */
  /* PIT triggering for DMA0: */
  DMAMUX_PDD_EnableTrigger(DMAMUX0_BASE_PTR, 0, PDD_DISABLE); /* disable PIT Trigger */
  /* use TPM0 overflow for DMA0 request: */
  DMAMUX_PDD_SetChannelSource(DMAMUX0_BASE_PTR, 0, 25); /* KL25Z reference manual, 3.4.8.1, p64: source number 25 TPM0 CH1 DMA source */
  
  /* DMA channel 0 source configuration: */
  DMA_PDD_SetSourceAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, (uint32_t)&GPIOC_PDIR); /* set source address */
  DMA_PDD_SetSourceAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* no circular buffer */
  DMA_PDD_EnableSourceAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_DISABLE); /* source address will be incremented by transfer size */
  DMA_PDD_SetSourceDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_8_BIT); /* Transfer size from source  */
  
  /* DMA channel 0 destination configuration: */
  DMA_PDD_SetDestinationAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, (uint32_t)&sampleBuffer[0]); /* set destination address */
  DMA_PDD_SetDestinationAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* no circular buffer */
  DMA_PDD_EnableDestinationAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE); /* auto-increment for destination address */
  DMA_PDD_SetDestinationDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_8_BIT); /* Transfer to destination size */
  
  /* DMA channel 0 transfer configuration: */
  DMA_PDD_EnableTransferCompleteInterrupt(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE); /* request interrupt at the end of the DMA transfer */
  (void)DMA_PDD_GetRequestAutoDisableEnabled(DMA_BASE_PTR, DMA_PDD_CHANNEL_0); /* disable DMA request at the end of the sequence */
}

static void TMR_SetTimerValue(uint32_t val) {
  TPM_PDD_WriteModuloReg(TPM0_BASE_PTR, val); /* set period of TPM0 */
  TPM_PDD_WriteChannelValueReg(TPM0_BASE_PTR, 1, val/2); /* channel 1: PWM low 50% */
}

static void TMR_Init(void) {
  TMR_SetTimerValue(LOG_TMR_FREQ/1000000); /* default of 1 MHz */
  TPM_PDD_EnableChannelDma(TPM0_BASE_PTR, 1); /* enable DMA for channel */
}

static void TransferDMA(void) {
  DMA_PDD_SetDestinationAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, (uint32_t)&sampleBuffer[0]); /* set destination address */
  DMA_PDD_SetByteCount(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, bufferSize); /* set number of bytes to transfer */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE); /* enable request from peripheral */
}

void LOGIC_OnComplete(void) {
  finishedSampling = TRUE;
}
//##########################################################################
/* Local Functions */

/* \brief Send single character over UART */
static void PutChar(uint8_t ch) {
  while (AS1_SendChar(ch) != ERR_OK) {
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

  AS1_ClearTxBuf();
  for (i = 0; i < bufferSize; i++) {
    PutChar(sampleBuffer[i]);
  }
}

/* \brief Setup timing for timer. Returns the module counter based on 48 MHz counter frequency */
static void setSampleFrequency(frequencyDivider freqDivider) {
  uint32_t brg;
  
  switch (freqDivider) {
	case 9999: // 10 kHz
		brg = LOG_TMR_FREQ/10000;
		break;
	case 3999:	// 25 kHz
		brg = LOG_TMR_FREQ/25000;
		break;
	case 1999: 	// 50 kHz
		brg = LOG_TMR_FREQ/50000;
		break;
	case 999:	// 100 kHz
		brg = LOG_TMR_FREQ/100000;
		break;
	case 399: 	// 250 kHz
		brg = LOG_TMR_FREQ/250000;
		break;
	case 199:	// 500 kHz
		brg = LOG_TMR_FREQ/500000;
		break;
	case 99:	// 1 MHz
		brg = LOG_TMR_FREQ/1000000;
		break;
	case 49:	// 2 MHz
		brg = LOG_TMR_FREQ/2000000;
		break;
	case 24:	// 4 MHz
		brg = LOG_TMR_FREQ/4000000;
		break;
	case 11:	// 8 MHz
		brg = LOG_TMR_FREQ/8000000;
		break;
	case 7:	// 12 MHz
		brg = LOG_TMR_FREQ/12000000;
		break;
	case 3:	// 24 MHz
		brg = LOG_TMR_FREQ/24000000;
		break;
	default:
		brg = LOG_TMR_FREQ/1000000; /* 1 MHz */
		break;
  } /* switch */
  TMR_SetTimerValue(brg-1);
}

static uint8_t GetChar(void) {
  uint8_t ch;

  while (AS1_RecvChar(&ch) != ERR_OK) {
  }
  return ch;
}

static void Run(void) {
  bool doSampling = FALSE;
  bool triggered = FALSE;
  uint32_t heartBeat;
  frequencyDivider freqDivider; // supported from V1.02
  unsigned long data;
  unsigned char cmd;
  int i = 0;

  // prepare SUMP variables
  triggerData[0].mask = 0;
  triggerData[0].values = 0;
  triggerData[0].configuration = 0;
  triggerData[1].mask = 0;
  triggerData[1].values = 0;
  triggerData[1].configuration = 0;
  triggerData[2].mask = 0;
  triggerData[2].values = 0;
  triggerData[2].configuration = 0;
  triggerData[3].mask = 0;
  triggerData[3].values = 0;
  triggerData[3].configuration = 0;
  // and preset Timer
  setSampleFrequency(DEFAULT_CLOCK_DIVIDER);
  heartBeat = DEFAULT_HEARTBEAT_COUNTER;
  for(;;) {
    i++;
    if (i > heartBeat) { /* heartbeat LED (red) if not sampling */
      if (!doSampling) {
        LEDR_Neg();
      }
      i = 0;
    }
    if (finishedSampling) {
      finishedSampling = FALSE;
      doSampling = FALSE;
      triggered = FALSE;
      SendData();
      LEDR_Off();
      LEDG_Off();
    }
    if (AS1_GetCharsInRxBuf()!=0) {
      cmd = GetChar();
      switch (cmd) {
        case SUMP_RESET:
          finishedSampling = FALSE;
          doSampling = FALSE;
          triggered = FALSE;
          LEDR_Off();
          LEDG_Off();
          break;
        case SUMP_RUN:
          bufferSize = BUFFERSIZE;
          finishedSampling = FALSE;
          doSampling = TRUE;
          if (triggerData[0].mask==0) { // no trigger active, simply start sampling
            LEDR_Off();
            //LEDB_On();
            triggered = TRUE;
            TransferDMA();
          } else {
            LEDR_Off();
            LEDG_On();
            while (!triggered) {
              // Use short (fast) loop to detect trigger
              data = (Byte1_GetVal() & 0xFF);
              /* for now, we support only reading from 8 Probes
               data = ( Byte2_GetVal() & 0xFF ) << 8;
               data = ( Byte3_GetVal() & 0xFF ) << 16;
               data = ( Byte4_GetVal() & 0xFF ) << 24;
               */
              /* use this, if single condition mask (AND) needed */
              if (!triggered && triggerData[0].mask != 0) {
                if ((data & triggerData[0].mask) == triggerData[0].values) { /* matching trigger */
                  /* use this, if multiple conditions (OR) are needed
                   for (i = 0; i < DEVICE_NOF_PROBES; i++)
                   { // we can handle all supported 32 Bits
                   if ((triggerData[0].mask & 1 << i) > 0)
                   { // if mask bit is set, check if values bit meets the probe bit
                   if ((triggerData[0].values & 1 << i)
                   == (data & 1 << i))
                   { // yes, we start if any trigger bit meets condition (primitive trigger only)
                   */
                  LEDG_Off();
                  //LEDB_On();
                  triggered = TRUE;
                  // enable DMA AND Trigger first transfer to pick up Trigger
                  // port value from Port
                  // TODO: replace trigger handling by GPIO external trigger
                  //       for Level and Edge
                  TransferDMA();
                  break;
                } /* if */
              } /* if */
              // BUT : do not lockup the analyzer!!!
              if (AS1_GetCharsInRxBuf()!= 0 && GetChar() == SUMP_RESET) {
                finishedSampling = FALSE;
                doSampling = FALSE;
                triggered = FALSE;
                //LEDB_Off();
                LEDG_Off();
                break; // leave the While(!triggered) loop 
              } /* while */
            } /* while */
          } /* if-else */
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
  
        /* Set Trigger Mask*/
        case 0xC0:
          triggerData[0].mask = GetChar();
          triggerData[0].mask |= GetChar() << 8;
          triggerData[0].mask |= GetChar() << 16;
          triggerData[0].mask |= GetChar() << 24;
          break;
        case 0xC4:
          triggerData[1].mask = GetChar();
          triggerData[1].mask |= GetChar() << 8;
          triggerData[1].mask |= GetChar() << 16;
          triggerData[1].mask |= GetChar() << 24;
          break;
        case 0xC8:
          triggerData[2].mask = GetChar();
          triggerData[2].mask |= GetChar() << 8;
          triggerData[2].mask |= GetChar() << 16;
          triggerData[2].mask |= GetChar() << 24;
          break;
        case 0xCC:
          triggerData[3].mask = GetChar();
          triggerData[3].mask |= GetChar() << 8;
          triggerData[3].mask |= GetChar() << 16;
          triggerData[3].mask |= GetChar() << 24;
          break;
  
        /* Set Trigger Values */
        case 0xC1:
          triggerData[0].values = GetChar();
          triggerData[0].values |= GetChar() << 8;
          triggerData[0].values |= GetChar() << 16;
          triggerData[0].values |= GetChar() << 24;
          break;
        case 0xC5:
          triggerData[1].values = GetChar();
          triggerData[1].values |= GetChar() << 8;
          triggerData[1].values |= GetChar() << 16;
          triggerData[1].values |= GetChar() << 24;
          break;
        case 0xC9:
          triggerData[2].values = GetChar();
          triggerData[2].values |= GetChar() << 8;
          triggerData[2].values |= GetChar() << 16;
          triggerData[2].values |= GetChar() << 24;
          break;
        case 0xCD:
          triggerData[3].values = GetChar();
          triggerData[3].values |= GetChar() << 8;
          triggerData[3].values |= GetChar() << 16;
          triggerData[3].values |= GetChar() << 24;
          break;
          /* Set Trigger Configuration */
        case 0xC2:
          triggerData[0].configuration = GetChar();
          triggerData[0].configuration |= GetChar() << 8;
          triggerData[0].configuration |= GetChar() << 16;
          triggerData[0].configuration |= GetChar() << 24;
          break;
        case 0xC6:
          triggerData[1].configuration = GetChar();
          triggerData[1].configuration |= GetChar() << 8;
          triggerData[1].configuration |= GetChar() << 16;
          triggerData[1].configuration |= GetChar() << 24;
          break;
        case 0xCA:
          triggerData[2].configuration = GetChar();
          triggerData[2].configuration |= GetChar() << 8;
          triggerData[2].configuration |= GetChar() << 16;
          triggerData[2].configuration |= GetChar() << 24;
          break;
        case 0xCE:
          triggerData[3].configuration = GetChar();
          triggerData[3].configuration |= GetChar() << 8;
          triggerData[3].configuration |= GetChar() << 16;
          triggerData[3].configuration |= GetChar() << 24;
          break;
        case SUMP_SET_DIVIDER:
          // preliminary; received divider values seems to need more testing
          freqDivider = GetChar();
          freqDivider |= GetChar() << 8;
          freqDivider |= GetChar() << 16;
          (void)GetChar();
          setSampleFrequency(freqDivider);
          break;
        case SUMP_SET_READ_DELAY_COUNT:
          rdCount = GetChar();
          rdCount |= GetChar() << 8;
          rdCount |= GetChar() << 16;
          rdCount |= GetChar() << 24;
          break;
          /* Set Flag */
        case SUMP_SET_FLAGS:
          flags = GetChar();
          flags |= (GetChar() << 8);
          flags |= (GetChar() << 16);
          flags |= (GetChar() << 24);
          break;
        default:
          break;
      } /* switch */
    }
  }
}

void LOGIC_Run(void) {
  TMR_Init();
  InitDMA();
  //TransferDMA();
  for (;;) {
    //WAIT1_Waitms(100);
    Run();
  }
}

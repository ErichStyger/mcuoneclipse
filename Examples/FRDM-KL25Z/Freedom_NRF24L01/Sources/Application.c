/*
 * Application.c
 *
 *      Author: Erich Styger
 */
#include "Application.h"
#include "nRF24L01.h"
#include "LEDR.h"
#include "LEDG.h"
#include "LEDB.h"
#include "WAIT1.h"
#include "CE.h"

#define IS_SENDER    0  /* 1 if we are the sender, 0 if we are the receiver */
#define PAYLOAD_SIZE 16  /* number of payload bytes, 0 to 32 bytes */
#define CHANNEL_NO   2  /* communication channel */

/* macros to configure device either for RX or TX operation */
#define TX_POWERUP()   RF_WriteRegister(RF24_CONFIG, RF24_EN_CRC|RF24_CRCO|RF24_PWR_UP|RF24_PRIM_TX) /* enable 2 byte CRC, power up and set as PTX */
#define RX_POWERUP()   RF_WriteRegister(RF24_CONFIG, RF24_EN_CRC|RF24_CRCO|RF24_PWR_UP|RF24_PRIM_RX) /* enable 2 byte CRC, power up and set as PRX */

static const uint8_t TADDR[5] = {0x11, 0x22, 0x33, 0x44, 0x55}; /* device address */
static uint8_t payload[PAYLOAD_SIZE]; /* buffer for payload */
static volatile bool isrFlag; /* flag set by ISR */

void APP_OnInterrupt(void) {
  CE_ClrVal(); /* stop sending/listening */
  isrFlag = TRUE;
}

void APP_Run(void) {
#if IS_SENDER
  int i;
#endif
  int cntr;
  uint8_t status;
  
  WAIT1_Waitms(100); /* give device time to power up */
  RF_Init(); /* set CE and CSN to initialization value */
  
  RF_WriteRegister(RF24_RF_SETUP, RF24_RF_SETUP_RF_PWR_0|RF24_RF_SETUP_RF_DR_250);
  RF_WriteRegister(RF24_RX_PW_P0, PAYLOAD_SIZE); /* number of payload bytes we want to send and receive */
  RF_WriteRegister(RF24_RF_CH, CHANNEL_NO); /* set channel */
  
  /* Set RADDR and TADDR as the transmit address since we also enable auto acknowledgment */
  RF_WriteRegisterData(RF24_RX_ADDR_P0, (uint8_t*)TADDR, sizeof(TADDR));
  RF_WriteRegisterData(RF24_TX_ADDR, (uint8_t*)TADDR, sizeof(TADDR));

  /* Enable RX_ADDR_P0 address matching */
  RF_WriteRegister(RF24_EN_RXADDR, RF24_EN_RXADDR_ERX_P0); /* enable data pipe 0 */
  
  /* clear interrupt flags */
  RF_ResetStatusIRQ(RF24_STATUS_RX_DR|RF24_STATUS_TX_DS|RF24_STATUS_MAX_RT);

#if IS_SENDER
  RF_WriteRegister(RF24_EN_AA, RF24_EN_AA_ENAA_P0); /* enable auto acknowledge. RX_ADDR_P0 needs to be equal to TX_ADDR! */
  RF_WriteRegister(RF24_SETUP_RETR, RF24_SETUP_RETR_ARD_750|RF24_SETUP_RETR_ARC_15); /* Important: need 750 us delay between every retry */
  TX_POWERUP();  /* Power up in transmitting mode */
  CE_ClrVal();   /* Will pulse this later to send data */
#else
  RX_POWERUP();  /* Power up in receiving mode */
  CE_SetVal();   /* Listening for packets */
#endif
  
  cntr = 0;
  for(;;) {
#if IS_SENDER
    cntr++;
    if (cntr==200) { /* send data every 200 ms */
      cntr = 0;
      for(i=0;i<PAYLOAD_SIZE;i++) {
        payload[i] = i+1; /* just fill payload with some data */
      }
      LEDR_On();
      RF_TxPayload(payload, sizeof(payload)); /* send data */
    }
    if (cntr>50) { /* not able to send data for 50 ms? */
      LEDR_Off();
    }

    if (isrFlag) { /* check if we have received an interrupt */
      isrFlag = FALSE; /* reset interrupt flag */
      status = RF_GetStatus();
      if (status&RF24_STATUS_RX_DR) { /* data received interrupt */
        RF_ResetStatusIRQ(RF24_STATUS_RX_DR); /* clear bit */
      }
      if (status&RF24_STATUS_TX_DS) { /* data sent interrupt */
        cntr = 0; /* reset timeout counter */
        LEDR_Off(); /* indicate data has been sent */
        RF_ResetStatusIRQ(RF24_STATUS_TX_DS); /* clear bit */
      }
      if (status&RF24_STATUS_MAX_RT) { /* retry timeout interrupt */
        RF_ResetStatusIRQ(RF24_STATUS_MAX_RT); /* clear bit */
      }
    }
    WAIT1_Waitms(1);
#else 
    if (isrFlag) { /* interrupt? */
      isrFlag = FALSE; /* reset interrupt flag */
      cntr = 0; /* reset counter */
      LEDB_Off();
      LEDG_Neg(); /* blink green LED to indicate good communication */
      status = RF_GetStatus();
      if (status&RF24_STATUS_RX_DR) { /* data received interrupt */
        RF_RxPayload(payload, sizeof(payload)); /* will reset RX_DR bit */
        RF_ResetStatusIRQ(RF24_STATUS_RX_DR|RF24_STATUS_TX_DS|RF24_STATUS_MAX_RT); /* make sure we reset all flags. Need to have the pipe number too */
      }
      if (status&RF24_STATUS_TX_DS) { /* data sent interrupt */
        RF_ResetStatusIRQ(RF24_STATUS_TX_DS); /* clear bit */
      }
      if (status&RF24_STATUS_MAX_RT) { /* retry timeout interrupt */
        RF_ResetStatusIRQ(RF24_STATUS_MAX_RT); /* clear bit */
      }
    } else {
      cntr++;
      if (cntr>500) { /* blink every 500 ms if not receiving data */
        cntr = 0; /* reset counter */
        LEDG_Off();
        LEDB_Neg(); /* blink blue to indicate no communication */
      }
      WAIT1_Waitms(1); /* burning some cycles here */
    }
#endif
  }
}


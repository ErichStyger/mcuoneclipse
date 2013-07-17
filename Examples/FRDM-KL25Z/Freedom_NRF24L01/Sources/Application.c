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

#define IS_SENDER    1  /* 1 if we are the sender, 0 if we are the receiver */
#define PAYLOAD_SIZE 2  /* number of payload bytes */
#define CHANNEL_NO   2  /* communication channel */

/* macros to configure device either for RX or TX operation */
#define TX_POWERUP()   RF_WriteRegister(RF24_CONFIG, RF24_EN_CRC|RF24_CRCO|RF24_PWR_UP|RF24_PRIM_TX) /* enable 1 byte CRC, power up and set as PTX */
#define RX_POWERUP()   RF_WriteRegister(RF24_CONFIG, RF24_EN_CRC|RF24_CRCO|RF24_PWR_UP|RF24_PRIM_RX) /* enable 1 byte CRC, power up and set as PRX */

static const uint8_t TADDR[5] = {0x11, 0x22, 0x33, 0x44, 0x55}; /* device address */
static uint8_t payload[PAYLOAD_SIZE]; /* buffer for payload */
static volatile bool isrFlag; /* flag set by ISR */

void APP_OnInterrupt(void) {
  CE_ClrVal(); /* stop sending/listening */
  /* read data here */
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
  RF_WriteRegister(RF24_RF_CH, CHANNEL_NO); /* set channel: 1: 2.401 GHz */
  
  /* Set RADDR and TADDR as the transmit address since we also enable auto acknowledgment */
  RF_WriteRegisterData(RF24_RX_ADDR_P0, (uint8_t*)TADDR, sizeof(TADDR));
  RF_WriteRegisterData(RF24_TX_ADDR, (uint8_t*)TADDR, sizeof(TADDR));

  /* Enable RX_ADDR_P0 address matching */
  RF_WriteRegister(RF24_EN_RXADDR, 0x01); /* enable data pipe 0 */
 
#if IS_SENDER
  RF_WriteRegister(RF24_EN_AA, 0x01); /* enable auto acknowledge. RX_ADDR_P0 needs to be equal to TX_ADDR! */
  RF_WriteRegister(RF24_SETUP_RETR, 0x2F); /* Important: need 750 us delay between every retry */
  TX_POWERUP();  /* Power up in transmitting mode */
  CE_ClrVal();   /* Will pulse this later to send data */
#else
  RX_POWERUP();  /* Power up in receiving mode */
  CE_SetVal();   /* Listening for packets */
#endif
  
  /* clear interrupt flags */
  RF_ResetStatusIRQ(RF24_STATUS_RX_DR|RF24_STATUS_TX_DS|RF24_STATUS_MAX_RT);
  cntr = 0;
  for(;;) {
#if IS_SENDER
    cntr++;
    if (cntr==200) { /* send data every 200 ms */
      cntr = 0;
      //TX_POWERUP();
      for(i=0;i<PAYLOAD_SIZE;i++) {
        payload[i] = i+1; /* just fill payload with some data */
      }
      RF_TxPayload(payload, sizeof(payload)); /* send data */
    }

    if (isrFlag) { /* check if we have received an interrupt */
      isrFlag = FALSE; /* reset interrupt flag */
      status = RF_GetStatus();
      if (status&RF24_STATUS_RX_DR) { /* data received interrupt */
        RF_ResetStatusIRQ(RF24_STATUS_RX_DR); /* clear bit */
      }
      if (status&RF24_STATUS_TX_DS) { /* data sent interrupt */
        cntr = 0; /* reset timeout counter */
        LEDR_Neg(); /* indicate data has been sent */
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

#if 0
  RF_WriteRegister(RF24_EN_AA, 0x01); /* enable auto acknowledge. RX_ADDR_P0 needs to be equal to TX_ADDR! */
  RF_WriteRegister(RF24_EN_RXADDR, 0x01); /* enable data pipe 0 */
  RF_WriteRegister(RF24_SETUP_AW, 0x03); /* RF_Adddress with, 0x3 means 5 bytes RF Address */
  RF_WriteRegisterData(RF24_TX_ADDR, buf, sizeof(buf)); /* write RF address */
#if IS_SENDER
  /* mask retry interrupt, enable CRC, 2-byte CRC, power up, Tx (bit cleared) */  
  RF_WriteRegister(RF24_CONFIG, RF24_MASK_MAX_RT|RF24_EN_CRC|RF24_CRCO|RF24_PWR_UP|RF24_PRIM_TX); /* 0b0001 1110: b0=0: transmitter, b1=1 power up, b4=1 mask MAX RT, IRQ is not triggered */
#else
  /* mask retry interrupt, enable CRC, 2-byte CRC, power up, Rx (bit set) */  
  RF_WriteRegister(RF24_CONFIG, RF24_MASK_MAX_RT|RF24_EN_CRC|RF24_CRCO|RF24_PWR_UP|RF24_PRIM_RX);
#endif
  RF_WriteRegister(RF24_SETUP_RETR, 0x2F); /* 750 us delay between every retry */
#endif


#if 0
//sets the RX address in the RX_ADDR register that is offset by rxpipenum
//unsigned char * address is the actual address to be used.  It should be sized
//  according to the rx_addr length that is being filled.
//unsigned int len is the length of the address.  Its value should be specified
//  according to the rx_addr length specified to the nrf24l01.
//unsigned char rxpipenum is the pipe number (zero to five) whose address is being
//  specified.  If an invalid address (greater than five) is supplied, the function
//  does nothing.
void wl_module_set_rx_addr(uint8_t * address, uint8_t len, uint8_t rxpipenum)
{ 
  if (rxpipenum > 5) {
    return;
  }
  RF_WriteRegisterData(RF24_RX_ADDR_P0 + rxpipenum, address, len);
}

static void wl_module_rx_config(void) 
// Sets the important registers in the wl-module and powers the module
// in receiving mode
{
  uint8_t data[5];
    // Set RF channel
  RF_WriteRegister(RF24_RF_CH, CHANNEL_NO);
  // Set data speed & Output Power configured in wl_module.h
  RF_WriteRegister(RF24_RF_SETUP, wl_module_RF_SETUP);
  //Enable all RX Data-Pipes
  RF_WriteRegister(RF24_EN_RXADDR, RF24_EN_RXADDR_ERX_ALL);
  //Set RX_Address Pipe 0
  data[0]= data[1]= data[2]= data[3]= data[4]= RF24_RX_ADDR_P0_B0_DEFAULT_VAL;
  wl_module_set_rx_addr(data, 5, 0);
  //Set RX_Address Pipe 1
  data[0]= data[1]= data[2]= data[3]= data[4]= RF24_RX_ADDR_P1_B0_DEFAULT_VAL;
  wl_module_set_rx_addr(data, 5, 1);
  //Set RX_Address Pipe 2-5
  data[0]=RF24_RX_ADDR_P2_DEFAULT_VAL;
  wl_module_set_rx_addr(data, 1, 2);
  data[0]=RF24_RX_ADDR_P3_DEFAULT_VAL;
  wl_module_set_rx_addr(data, 1, 3);
  data[0]=RF24_RX_ADDR_P4_DEFAULT_VAL;
  wl_module_set_rx_addr(data, 1, 4);
  data[0]=RF24_RX_ADDR_P5_DEFAULT_VAL;
  wl_module_set_rx_addr(data, 1, 5);
    // Set length of incoming payload 
  RF_WriteRegister(RF24_RX_PW_P0, PAYLOAD_SIZE);
  RF_WriteRegister(RF24_RX_PW_P1, PAYLOAD_SIZE);
  RF_WriteRegister(RF24_RX_PW_P2, PAYLOAD_SIZE);
  RF_WriteRegister(RF24_RX_PW_P3, PAYLOAD_SIZE);
  RF_WriteRegister(RF24_RX_PW_P4, PAYLOAD_SIZE);
  RF_WriteRegister(RF24_RX_PW_P5, PAYLOAD_SIZE);
  
  // Start receiver 
  RX_POWERUP();     // Power up in receiving mode
  CE_SetVal();     // Listening for packets
}

void wl_module_set_RADDR(uint8_t * adr) 
// Sets the receiving address
{
    CE_ClrVal();
    RF_WriteRegisterData(RF24_RX_ADDR_P0,adr,5);
    CE_SetVal();
}

void wl_module_set_TADDR(uint8_t * adr)
// Sets the transmitting address
{
  RF_WriteRegisterData(RF24_TX_ADDR, adr,5);
}


// Sets the wl-module as one of the six sender. Define for every sender a unique Number (wl_module_TX_NR_x) 
// when you call this Function.
//  Each TX will get a TX-Address corresponding to the RX-Device.
// RX_Address_Pipe_0 must be the same as the TX-Address
void wl_module_tx_config(uint8_t tx_nr) 
{
  uint8_t tx_addr[5];
  
    // Set RF channel
  RF_WriteRegister(RF24_RF_CH, CHANNEL_NO);
  // Set data speed & Output Power configured in wl_module.h
  RF_WriteRegister(RF24_RF_SETUP, wl_module_RF_SETUP);
  //Config the CONFIG Register (Mask IRQ, CRC, etc)
  RF_WriteRegister(RF24_CONFIG, wl_module_CONFIG);
    // Set length of incoming payload 
    //wl_module_config_register(RX_PW_P0, wl_module_PAYLOAD);
  
  RF_WriteRegister(RF24_SETUP_RETR,(RF24_SETUP_RETR_ARD_750 | RF24_SETUP_RETR_ARC_15));
  
  //set the TX address for the pipe with the same number as the iteration
  switch(tx_nr)     
  {
    case 0: //setup TX address as default RX address for pipe 0 (E7:E7:E7:E7:E7)
      tx_addr[0] = tx_addr[1] = tx_addr[2] = tx_addr[3] = tx_addr[4] = RF24_RX_ADDR_P0_B0_DEFAULT_VAL;
      wl_module_set_TADDR(tx_addr);
      wl_module_set_RADDR(tx_addr);
      break;
    case 1: //setup TX address as default RX address for pipe 1 (C2:C2:C2:C2:C2)
      tx_addr[0] = tx_addr[1] = tx_addr[2] = tx_addr[3] = tx_addr[4] = RF24_RX_ADDR_P1_B0_DEFAULT_VAL;
      wl_module_set_TADDR(tx_addr);
      wl_module_set_RADDR(tx_addr);
      break;
    case 2: //setup TX address as default RX address for pipe 2 (C2:C2:C2:C2:C3)
      tx_addr[1] = tx_addr[2] = tx_addr[3] = tx_addr[4] = RF24_RX_ADDR_P1_B0_DEFAULT_VAL;
      tx_addr[0] = RF24_RX_ADDR_P2_DEFAULT_VAL;
      wl_module_set_TADDR(tx_addr);
      wl_module_set_RADDR(tx_addr);
      break;
    case 3: //setup TX address as default RX address for pipe 3 (C2:C2:C2:C2:C4)
      tx_addr[1] = tx_addr[2] = tx_addr[3] = tx_addr[4] = RF24_RX_ADDR_P1_B0_DEFAULT_VAL;
      tx_addr[0] = RF24_RX_ADDR_P3_DEFAULT_VAL;
      wl_module_set_TADDR(tx_addr);
      wl_module_set_RADDR(tx_addr);
      break;
    case 4: //setup TX address as default RX address for pipe 4 (C2:C2:C2:C2:C5)
      tx_addr[1] = tx_addr[2] = tx_addr[3] = tx_addr[4] = RF24_RX_ADDR_P1_B0_DEFAULT_VAL;
      tx_addr[0] = RF24_RX_ADDR_P4_DEFAULT_VAL;
      wl_module_set_TADDR(tx_addr);
      wl_module_set_RADDR(tx_addr);
      break;
    case 5: //setup TX address as default RX address for pipe 5 (C2:C2:C2:C2:C6)
      tx_addr[1] = tx_addr[2] = tx_addr[3] = tx_addr[4] = RF24_RX_ADDR_P1_B0_DEFAULT_VAL;
      tx_addr[0] = RF24_RX_ADDR_P5_DEFAULT_VAL;
      wl_module_set_TADDR(tx_addr);
      wl_module_set_RADDR(tx_addr);
      break;
  }
  TX_POWERUP();
  /*
    // Start receiver 
    PTX = 0;        // Start in receiving mode
    RX_POWERUP;     // Power up in receiving mode
    wl_module_CE_hi;     // Listening for pakets
  */
}
#endif

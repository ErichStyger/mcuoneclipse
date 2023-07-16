/**
 * \file
 * \brief This is the implementation of the Nordic Semiconductor nRF24L01+ low level driver.
 * \author (c) 2013-2019 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module deals with the low level functions of the transceiver.
 */

#include "McuRNetConfig.h"
#if McuRNET_CONFIG_IS_ENABLED
#include "Radio.h"
#include "RadioNRF24.h"
#include "McuNRF24L01.h"
#include "RMSG.h"
#include "RStdIO.h"
#include "RPHY.h"
#include "McuUtility.h"
#include "McuRNet.h"

extern void McuRNet_OnRadioEvent(McuRNet_RadioEvent event);

#define NRF24_DYNAMIC_PAYLOAD     1 /* if set to one, use dynamic payload size */
#define NRF24_AUTO_ACKNOWLEDGE    1 /* if set to one, the transceiver is configured to use auto acknowledge */
#define RADIO_CHANNEL_DEFAULT     RNET_CONFIG_TRANSCEIVER_CHANNEL  /* default communication channel */
#define RADIO_WAITNG_TIMEOUT_MS   250 /* timeout value in milliseconds, used for RADIO_WAITING_DATA_SENT */

/* macros to configure device either for RX or TX operation */
#define McuNRF24L01_CONFIG_SETTINGS  (McuNRF24L01_EN_CRC|McuNRF24L01_CRCO)
#define TX_POWERUP()         McuNRF24L01_WriteRegister(McuNRF24L01_CONFIG, McuNRF24L01_CONFIG_SETTINGS|McuNRF24L01_PWR_UP|McuNRF24L01_PRIM_TX) /* enable 2 byte CRC, power up and set as PTX */
#define RX_POWERUP()         McuNRF24L01_WriteRegister(McuNRF24L01_CONFIG, McuNRF24L01_CONFIG_SETTINGS|McuNRF24L01_PWR_UP|McuNRF24L01_PRIM_RX) /* enable 1 byte CRC, power up and set as PRX */
#define POWERDOWN()          McuNRF24L01_WriteRegister(McuNRF24L01_CONFIG, McuNRF24L01_CONFIG_SETTINGS) /* power down */

static bool RADIO_isSniffing = FALSE;
#define RADIO_NOF_ADDR_BYTES   5  /* we are using 5 address bytes */
static const uint8_t RADIO_TADDR_P0[RADIO_NOF_ADDR_BYTES] = {0x11, 0x22, 0x33, 0x44, 0x55}; /* device address for pipe 0 */
static const uint8_t RADIO_TADDR_P1[RADIO_NOF_ADDR_BYTES] = {0xB3, 0xB4, 0xB5, 0xB6, 0xF1}; /* device address for pipe 1 */
static const uint8_t RADIO_TADDR_P2[1] = {0xF2}; /* device address for pipe 2 */
static const uint8_t RADIO_TADDR_P3[1] = {0xF3}; /* device address for pipe 3 */
static const uint8_t RADIO_TADDR_P4[1] = {0xF4}; /* device address for pipe 4 */
static const uint8_t RADIO_TADDR_P5[1] = {0xF5}; /* device address for pipe 5 */

#if RNET_CONFIG_SEND_RETRY_CNT>0
  static uint8_t RADIO_RetryCnt;
  static uint8_t TxDataBuffer[RPHY_BUFFER_SIZE]; /*!< global buffer if using retries */
#endif

/* Radio state definitions */
typedef enum RADIO_AppStatusKind {
  RADIO_INITIAL_STATE, /* initial state of the state machine */
  RADIO_RECEIVER_ALWAYS_ON, /* receiver is in RX mode */
  RADIO_TRANSMIT_DATA, /* send data */
  RADIO_WAITING_DATA_SENT, /* wait until data is sent */
  RADIO_TIMEOUT,
  RADIO_READY_FOR_TX_RX_DATA,
  RADIO_CHECK_TX,   /* send data if any */
  RADIO_POWER_DOWN, /* transceiver powered down */
} RADIO_AppStatusKind;

static RADIO_AppStatusKind RADIO_AppStatus = RADIO_INITIAL_STATE;
static RPHY_PacketDesc radioRx;
static uint8_t radioRxBuf[RPHY_BUFFER_SIZE];
static uint8_t RADIO_CurrChannel = RADIO_CHANNEL_DEFAULT;

/* need to have this in case RF device is still added to project */
static volatile bool RADIO_isrFlag; /* flag set by ISR */

static void Err(unsigned char *msg) {
  McuShell_SendStr(msg, McuShell_GetStdio()->stdErr);
}

/* callback called from radio driver */
void RADIO_OnInterrupt(void) {
  RADIO_isrFlag = TRUE;
}

uint8_t RADIO_FlushQueues(void) {
  uint8_t res = ERR_OK;
  
  if (RPHY_FlushRxQueue()!=ERR_OK) {
    res = ERR_FAILED;
  }
  if (RPHY_FlushTxQueue()!=ERR_OK) {
    res = ERR_FAILED;
  }
  return res;
}

static uint8_t RADIO_Flush(void) {
  McuNRF24L01_Write(McuNRF24L01_FLUSH_RX); /* flush old data */
  McuNRF24L01_Write(McuNRF24L01_FLUSH_TX); /* flush old data */
  return ERR_OK;
}

bool RADIO_CanDoPowerDown(void) {
  if (RADIO_isrFlag) {
    return FALSE; /* interrupt pending */
  }
  switch(RADIO_AppStatus) {
    case RADIO_TRANSMIT_DATA:
    case RADIO_WAITING_DATA_SENT:
    case RADIO_TIMEOUT:
      return FALSE; /* sending/receiving data, cannot power down */

    case RADIO_INITIAL_STATE:
    case RADIO_RECEIVER_ALWAYS_ON:
    case RADIO_READY_FOR_TX_RX_DATA:
    case RADIO_CHECK_TX:
    case RADIO_POWER_DOWN:
      break; /* check other conditions */
    default:
      break;
  } /* switch */
  if (RMSG_RxQueueNofItems()!=0) {
    return FALSE; /* items received, cannot power down */
  }
  if (RMSG_TxQueueNofItems()!=0) {
    return FALSE; /* items to be sent, cannot power down */
  }
  return TRUE; /* ok to power down */
}

uint8_t RADIO_PowerDown(void) {
  uint8_t res;
  
  res = RADIO_Flush();
  POWERDOWN();
  return res;
}

static uint8_t CheckTx(void) {
  RPHY_PacketDesc packet;
#if RNET_CONFIG_SEND_RETRY_CNT==0
  uint8_t TxDataBuffer[RPHY_BUFFER_SIZE]; /* local tx buffer if not using retries */
#endif
  RPHY_FlagsType flags;
  
  if (RMSG_GetTxMsg(TxDataBuffer, sizeof(TxDataBuffer))==ERR_OK) {
    flags = RPHY_BUF_FLAGS(TxDataBuffer);
    if (flags&RPHY_PACKET_FLAGS_POWER_DOWN) {
      /* special request */
      (void)RADIO_PowerDown();
      return ERR_DISABLED; /* no more data, pipes flushed */
    }
    McuNRF24L01_StopRxTx();  /* CE low */
    TX_POWERUP();
    /* set up packet structure */
    packet.phyData = &TxDataBuffer[0];
    packet.flags = flags;
    packet.phySize = sizeof(TxDataBuffer);
#if NRF24_DYNAMIC_PAYLOAD
    packet.rxtx = RPHY_BUF_PAYLOAD_START(packet.phyData);
#else
    packet.rxtx = &RPHY_BUF_SIZE(packet.phyData); /* we transmit the data size too */
#endif
    if (RADIO_isSniffing) {
      RPHY_SniffPacket(&packet, TRUE); /* sniff outgoing packet */
    }
#if NRF24_DYNAMIC_PAYLOAD
    McuNRF24L01_TxPayload(packet.rxtx, RPHY_BUF_SIZE(packet.phyData)); /* send data, using dynamic payload size */
#else
    McuNRF24L01_TxPayload(packet.rxtx, RPHY_PAYLOAD_SIZE); /* send data, using fixed payload size */
#endif
    return ERR_OK;
  }
  return ERR_NOTAVAIL; /* no data to send? */
}

/* called to check if we have something in the RX queue. If so, we queue it */
static uint8_t CheckRx(void) {
#if NRF24_DYNAMIC_PAYLOAD
  uint8_t payloadSize;
#endif
  uint8_t res = ERR_OK;
  uint8_t RxDataBuffer[RPHY_BUFFER_SIZE];
  uint8_t status;
  RPHY_PacketDesc packet;
  bool hasRxData, hasRx;
  
  hasRxData = FALSE;
  packet.flags = RPHY_PACKET_FLAGS_NONE;
  packet.phyData = &RxDataBuffer[0];
  packet.phySize = sizeof(RxDataBuffer);
#if NRF24_DYNAMIC_PAYLOAD
  packet.rxtx = RPHY_BUF_PAYLOAD_START(packet.phyData);
#else
  packet.rxtx = &RPHY_BUF_SIZE(packet.phyData); /* we transmit the data size too */
#endif
  status = McuNRF24L01_GetStatusClrIRQ();
  hasRx = (status&McuNRF24L01_STATUS_RX_DR)!=0;
#if !McuNRF24L01_CONFIG_IRQ_PIN_ENABLED
#if 1 /* experimental */
  if (!hasRx) { /* interrupt flag not set, check if we have otherwise data */
    (void)McuNRF24L01_GetFifoStatus(&status);
    if (!(status&McuNRF24L01_FIFO_STATUS_RX_EMPTY) || (status&McuNRF24L01_FIFO_STATUS_RX_FULL)) { /* Rx not empty? */
      hasRx = TRUE;
    }
  }
#endif
#endif
  if (hasRx) { /* data received interrupt */
    hasRxData = TRUE;
#if NRF24_DYNAMIC_PAYLOAD
    (void)McuNRF24L01_ReadNofRxPayload(&payloadSize);
    if (payloadSize==0 || payloadSize>32) { /* packet with error? */
      McuNRF24L01_Write(McuNRF24L01_FLUSH_RX); /* flush old data */
      return ERR_FAILED;
    } else {
      McuNRF24L01_RxPayload(packet.rxtx, payloadSize); /* get payload: note that we transmit <size> as payload! */
      RPHY_BUF_SIZE(packet.phyData) = payloadSize;
    }
#else
    McuNRF24L01_RxPayload(packet.rxtx, RPHY_PAYLOAD_SIZE); /* get payload: note that we transmit <size> as payload! */
#endif
  }
  if (hasRxData) {
    /* put message into Rx queue */
#if McuRNet_CREATE_EVENTS
    /*lint -save -e522 function lacks side effect  */
    McuRNet_OnRadioEvent(McuRNet_RADIO_MSG_RECEIVED);
    /*lint -restore */
#endif
    res = RMSG_QueueRxMsg(packet.phyData, packet.phySize, RPHY_BUF_SIZE(packet.phyData), packet.flags);
    if (res!=ERR_OK) {
      if (res==ERR_OVERFLOW) {
        Err((unsigned char*)"ERR: Rx queue overflow!\r\n");
      } else {
        Err((unsigned char*)"ERR: Rx Queue full?\r\n");
      }
    }
  } else {
    res = ERR_RXEMPTY; /* no data */
  }
  return res;
}

static void WaitRandomTime(void) {
  if (configTICK_RATE_HZ<=100) { /* slower tick rate */
    vTaskDelay(10+(xTaskGetTickCount()%16));
  } else { /* higher tick rate: wait between 10 and 10+32 ticks */
    vTaskDelay(10+(xTaskGetTickCount()%32));
  }
}

static void RADIO_HandleStateMachine(void) {
#if RADIO_WAITNG_TIMEOUT_MS>0
  static TickType_t sentTimeTickCntr = 0; /* used for timeout */
#endif
  uint8_t status, res;
  
  for(;;) { /* will break/return */
    switch (RADIO_AppStatus) {
      case RADIO_INITIAL_STATE:
        McuNRF24L01_StopRxTx();  /* will send/receive data later */
        RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* turn receive on */
        break; /* process switch again */
  
      case RADIO_RECEIVER_ALWAYS_ON: /* turn receive on */
        RX_POWERUP();
        McuNRF24L01_StartRxTx(); /* Listening for packets */
        RADIO_AppStatus = RADIO_READY_FOR_TX_RX_DATA;
        break; /* process switch again */
  
      case RADIO_READY_FOR_TX_RX_DATA: /* we are ready to receive/send data data */
#if !McuNRF24L01_CONFIG_IRQ_PIN_ENABLED
        McuNRF24L01_PollInterrupt();
#if 1 /* experimental */
        if (!RADIO_isrFlag) { /* interrupt flag not set, check if we have otherwise data */
          (void)McuNRF24L01_GetFifoStatus(&status);
          if (!(status&McuNRF24L01_FIFO_STATUS_RX_EMPTY) || (status&McuNRF24L01_FIFO_STATUS_RX_FULL)) { /* Rx not empty? */
            RADIO_isrFlag = TRUE;
          }
        }
#endif
#endif
        if (RADIO_isrFlag) { /* Rx interrupt? */
          RADIO_isrFlag = FALSE; /* reset interrupt flag */
          res = CheckRx(); /* get message */
#if 1 /* experimental */
          if (res==ERR_FAILED) { /* failed reading from device */
            RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* continue listening */
            return; /* get out of loop */
          }
          (void)McuNRF24L01_GetFifoStatus(&status);
          if (res==ERR_RXEMPTY && !(status&McuNRF24L01_FIFO_STATUS_RX_EMPTY)) { /* no data, but still flag set? */
            McuNRF24L01_Write(McuNRF24L01_FLUSH_RX); /* flush old data */
            RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* continue listening */
          } else if (!(status&McuNRF24L01_FIFO_STATUS_RX_EMPTY) || (status&McuNRF24L01_FIFO_STATUS_RX_FULL)) { /* Rx not empty? */
            RADIO_isrFlag = TRUE; /* stay in current state */
          } else {
            RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* continue listening */
          }
#else
          RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* continue listening */
#endif
          break; /* process switch again */
        }
#if RNET_CONFIG_SEND_RETRY_CNT>0
        RADIO_RetryCnt=0;
#endif
        RADIO_AppStatus = RADIO_CHECK_TX; /* check if we can send something */
        break;
        
      case RADIO_CHECK_TX:
        res = CheckTx();
        if (res==ERR_OK) { /* there was data and it has been sent */
          #if RADIO_WAITNG_TIMEOUT_MS>0
          sentTimeTickCntr = xTaskGetTickCount(); /* remember time when it was sent, used for timeout */
          #endif
          RADIO_AppStatus = RADIO_WAITING_DATA_SENT;
          break; /* process switch again */
        } else if (res==ERR_DISABLED) { /* powered down transceiver */
          RADIO_AppStatus = RADIO_POWER_DOWN;
        } else {
          RADIO_AppStatus = RADIO_READY_FOR_TX_RX_DATA;
        }
        return;
        
      case RADIO_POWER_DOWN:
        return;
  
      case RADIO_WAITING_DATA_SENT:
#if !McuNRF24L01_CONFIG_IRQ_PIN_ENABLED
        McuNRF24L01_PollInterrupt();
#else /* experimental */
        if (!RADIO_isrFlag) { /* check if we missed an interrupt? */
          McuNRF24L01_PollInterrupt();
        }
#endif
        if (RADIO_isrFlag) { /* check if we have received an interrupt: this is either timeout or low level ack */
          RADIO_isrFlag = FALSE; /* reset interrupt flag */
          status = McuNRF24L01_GetStatusClrIRQ();
          if (status&McuNRF24L01_STATUS_MAX_RT) { /* retry timeout interrupt */
            McuNRF24L01_Write(McuNRF24L01_FLUSH_TX); /* flush old data */
            RADIO_AppStatus = RADIO_TIMEOUT; /* timeout */
            WaitRandomTime();
          } else {
    #if McuRNet_CREATE_EVENTS
            /*lint -save -e522 function lacks side effect  */
            McuRNet_OnRadioEvent(McuRNet_RADIO_MSG_SENT);
            /*lint -restore */
    #endif
            RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* turn receive on */
          }
          break; /* process switch again */
        }
      #if RADIO_WAITNG_TIMEOUT_MS>0
        if (pdMS_TO_TICKS((xTaskGetTickCount()-sentTimeTickCntr))>RADIO_WAITNG_TIMEOUT_MS) {
          RADIO_AppStatus = RADIO_TIMEOUT; /* timeout */
        }
      #endif
        return;
        
      case RADIO_TIMEOUT:
#if RNET_CONFIG_SEND_RETRY_CNT>0
        if (RADIO_RetryCnt<RNET_CONFIG_SEND_RETRY_CNT) {
          Err((unsigned char*)"ERR: Retry\r\n");
  #if McuRNet_CREATE_EVENTS
          /*lint -save -e522 function lacks side effect  */
          McuRNet_OnRadioEvent(McuRNet_RADIO_RETRY);
          /*lint -restore */
  #endif
          RADIO_RetryCnt++;
          if (RMSG_PutRetryTxMsg(TxDataBuffer, sizeof(TxDataBuffer))==ERR_OK) {
            RADIO_AppStatus = RADIO_CHECK_TX; /* resend packet */
            return; /* iterate state machine next time */
          } else {
            Err((unsigned char*)"ERR: PutRetryTxMsg failed!\r\n");
  #if McuRNet_CREATE_EVENTS
            /*lint -save -e522 function lacks side effect  */
            McuRNet_OnRadioEvent(McuRNet_RADIO_RETRY_MSG_FAILED);
            /*lint -restore */
  #endif
          }
        }
#endif
        Err((unsigned char*)"ERR: Timeout\r\n");
#if McuRNet_CREATE_EVENTS
        /*lint -save -e522 function lacks side effect  */
        McuRNet_OnRadioEvent(McuRNet_RADIO_TIMEOUT);
        /*lint -restore */
#endif
        RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* turn receive on */
        break; /* process switch again */
  
      default: /* should not happen! */
        return;
    } /* switch */
  } /* for */
}

uint8_t RADIO_SetChannel(uint8_t channel) {
  RADIO_CurrChannel = channel;
  return McuNRF24L01_SetChannel(channel);
}

uint8_t RADIO_IsSane(void) {
  uint8_t res;
  uint8_t ch;

  res = McuNRF24L01_GetChannel(&ch); /* get channel set in transceiver */
  if (res!=ERR_OK) {
    return ERR_FAILED;
  }
  if (ch!=RADIO_CurrChannel) { /* HW has not the correct register set? */
    return ERR_FAILED;
  }
  return ERR_OK; /* transceiver seems to be ok */
}

/*! 
 * \brief Radio power-on initialization.
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t RADIO_PowerUp(void) {
  uint8_t addr[RADIO_NOF_ADDR_BYTES];
  int i;

  McuNRF24L01_Init(); /* set CE and CSN to initialization value */
  
  McuNRF24L01_WriteRegister(McuNRF24L01_RF_SETUP, McuNRF24L01_RF_SETUP_RF_PWR_0|RNET_CONFIG_NRF24_DATA_RATE);
#if NRF24_DYNAMIC_PAYLOAD
  /* enable dynamic payload */
  (void)McuNRF24L01_WriteFeature(McuNRF24L01_FEATURE_EN_DPL|McuNRF24L01_FEATURE_EN_ACK_PAY|McuNRF24L01_FEATURE_EN_DYN_PAY); /* set EN_DPL for dynamic payload */
//  (void)McuNRF24L01_EnableDynamicPayloadLength(McuNRF24L01_DYNPD_DPL_P0); /* set DYNPD register for dynamic payload for pipe0 */
  (void)McuNRF24L01_EnableDynamicPayloadLength(McuNRF24L01_DYNPD_DPL_ALL); /* set DYNPD register for dynamic payload for all pipes */
#else
  (void)McuNRF24L01_SetStaticPipePayload(0, RPHY_PAYLOAD_SIZE); /* static number of payload bytes we want to send and receive */
#endif
  (void)RADIO_SetChannel(RADIO_CurrChannel);

  (void)McuNRF24L01_SetAddressWidth(RADIO_NOF_ADDR_BYTES); /* set address width to 5 bytes (default) */

  /* Set RADDR and TADDR as the transmit address since we also enable auto acknowledgment */
  (void)McuNRF24L01_SetTxAddress((uint8_t*)RADIO_TADDR_P0, sizeof(RADIO_TADDR_P0));
  /* Pipes 0 to 5 */
  (void)McuNRF24L01_SetRxAddress(0, (uint8_t*)RADIO_TADDR_P0, RADIO_NOF_ADDR_BYTES);
  (void)McuNRF24L01_SetRxAddress(1, (uint8_t*)RADIO_TADDR_P1, RADIO_NOF_ADDR_BYTES);
  /* for the following pipes, use P1 as base. Only need to write single byte to transceiver */
  for(i=0;i<RADIO_NOF_ADDR_BYTES;i++) {
    addr[i] = RADIO_TADDR_P1[i]; /* use P1 as base */
  }
  addr[RADIO_NOF_ADDR_BYTES-1] = RADIO_TADDR_P2[0];
  (void)McuNRF24L01_SetRxAddress(2, addr, RADIO_NOF_ADDR_BYTES);

  addr[RADIO_NOF_ADDR_BYTES-1] = RADIO_TADDR_P3[0];
  (void)McuNRF24L01_SetRxAddress(3, addr, RADIO_NOF_ADDR_BYTES);

  addr[RADIO_NOF_ADDR_BYTES-1] = RADIO_TADDR_P4[0];
  (void)McuNRF24L01_SetRxAddress(4, addr, RADIO_NOF_ADDR_BYTES);

  addr[RADIO_NOF_ADDR_BYTES-1] = RADIO_TADDR_P5[0];
  (void)McuNRF24L01_SetRxAddress(5, addr, RADIO_NOF_ADDR_BYTES);

  /* Enable RX_ADDR address matching */
  (void)McuNRF24L01_WriteRegister(McuNRF24L01_EN_RXADDR, McuNRF24L01_EN_RXADDR_ERX_ALL); /* enable all data pipes */
  
  /* clear interrupt flags */
  McuNRF24L01_ResetStatusIRQ(McuNRF24L01_STATUS_RX_DR|McuNRF24L01_STATUS_TX_DS|McuNRF24L01_STATUS_MAX_RT);
  
  /* rx/tx mode */
#if NRF24_AUTO_ACKNOWLEDGE
#if 0
  (void)McuNRF24L01_EnableAutoAck(McuNRF24L01_EN_AA_ENAA_P0); /* enable auto acknowledge on pipe 0. RX_ADDR_P0 needs to be equal to TX_ADDR! */
#else
  (void)McuNRF24L01_EnableAutoAck(McuNRF24L01_EN_AA_ENAA_ALL); /* enable auto acknowledge on all pipes. RX_ADDR_P0 needs to be equal to TX_ADDR! */
#endif
#endif
  McuNRF24L01_WriteRegister(McuNRF24L01_SETUP_RETR, McuNRF24L01_SETUP_RETR_ARD_750|McuNRF24L01_SETUP_RETR_ARC_15); /* Important: need 750 us delay between every retry */
  
  RX_POWERUP();  /* Power up in receiving mode */
  (void)RADIO_Flush(); /* flush possible old data */
  McuNRF24L01_StartRxTx(); /* Listening for packets */

  RADIO_AppStatus = RADIO_INITIAL_STATE;
  /* init Rx descriptor */
  radioRx.phyData = &radioRxBuf[0];
  radioRx.phySize = sizeof(radioRxBuf);
  radioRx.rxtx = &RPHY_BUF_SIZE(radioRx.phyData); /* we transmit the size too */
  return ERR_OK;
}

uint8_t RADIO_Process(void) {
  uint8_t res;
  int i;
  
  RADIO_HandleStateMachine(); /* process state machine */
  for(i=0;i<10;i++) { /* breaks, tries to handle multiple incoming messages */
    /* process received packets */
    res = RPHY_GetPayload(&radioRx); /* get message */
    if (res==ERR_OK) { /* packet received */
      if (RADIO_isSniffing) {
        RPHY_SniffPacket(&radioRx, FALSE); /* sniff incoming packet */
      }
      if (RPHY_OnPacketRx(&radioRx)==ERR_OK) { /* process incoming packets */
  #if McuRNet_CREATE_EVENTS
        if (radioRx.flags&RPHY_PACKET_FLAGS_IS_ACK) { /* it was an ack! */
          /*lint -save -e522 function lacks side effect */
          McuRNet_OnRadioEvent(McuRNet_RADIO_ACK_RECEIVED);
          /*lint -restore */
        }
  #endif
      }
    } else {
      break; /* no message, get out of for loop */
    }
  } /* for */
  return ERR_OK;
}

static const unsigned char *RadioStateStr(RADIO_AppStatusKind state) {
  switch(state) {
    case RADIO_INITIAL_STATE:         return (const unsigned char*)"INITIAL";
    case RADIO_RECEIVER_ALWAYS_ON:    return (const unsigned char*)"ALWAYS_ON";
    case RADIO_TRANSMIT_DATA:         return (const unsigned char*)"TRANSMIT_DATA";
    case RADIO_WAITING_DATA_SENT:     return (const unsigned char*)"WAITING_DATA_SENT";
    case RADIO_READY_FOR_TX_RX_DATA:  return (const unsigned char*)"READY_TX_RX";
    case RADIO_CHECK_TX:              return (const unsigned char*)"CHECK_TX";
    case RADIO_POWER_DOWN:            return (const unsigned char*)"POWER_DOWN"; 
    default:                          break;
  }
  return (const unsigned char*)"UNKNOWN";
}

static void RADIO_PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"radio", (unsigned char*)"Group of radio commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows radio help or status\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  channel <number>", (unsigned char*)"Switches to the given channel (0..127)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  datarate <rate>", (unsigned char*)"Changes the datareate (250, 1000, 2000)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  txaddr <addr>", (unsigned char*)"Set TX address, <addr> of up to 5 hex bytes, separated by space\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  rxaddr <pipe> <addr>", (unsigned char*)"Set RX pipe address for pipe (0-5), <addr> of up to 5 hex bytes, separated by space\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  power <number>", (unsigned char*)"Changes output power (0, -10, -12, -18)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  sniff on|off", (unsigned char*)"Turns sniffing on or off\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  writereg 0xReg 0xVal", (unsigned char*)"Write a transceiver register\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  readreg 0xReg", (unsigned char*)"Read a transceiver register\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  printregs", (unsigned char*)"Print the radio registers\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  flush", (unsigned char*)"Empty all queues\r\n", io->stdOut);
}

static void RadioPrintRegisters(McuShell_ConstStdIOType *io) {
  int i;
  uint8_t val;
  uint8_t bufidx[16], buf[16];
  
  for(i=0;i<=0x1D;i++) {
    val = McuNRF24L01_ReadRegister(i);
    McuUtility_strcpy(bufidx, sizeof(bufidx), (unsigned char*)"  addr 0x");
    McuUtility_strcatNum8Hex(bufidx, sizeof(bufidx), i);
    buf[0] = '\0';
    McuUtility_strcatNum8Hex(buf, sizeof(buf), val);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    McuShell_SendStatusStr(bufidx, buf, io->stdOut);
  }
}

static void RADIO_PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[48];
  uint8_t val0, val1;
  int8_t val;
  uint16_t dataRate;
  
  McuShell_SendStatusStr((unsigned char*)"Radio", (unsigned char*)"\r\n", io->stdOut);
  
  McuShell_SendStatusStr((unsigned char*)"  state", RadioStateStr(RADIO_AppStatus), io->stdOut);
  McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
  
  McuShell_SendStatusStr((unsigned char*)"  sniff", RADIO_isSniffing?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  sniff stdio", McuShell_GetStdio()==NULL?(unsigned char*)"NULL\r\n":(unsigned char*)"Shell default standard I/O\r\n", io->stdOut);
  (void)McuNRF24L01_GetChannel(&val0);
  McuUtility_Num8uToStr(buf, sizeof(buf), val0);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (HW), ");
  McuUtility_strcatNum8u(buf, sizeof(buf), RADIO_CurrChannel);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (SW)\r\n");
  McuShell_SendStatusStr((unsigned char*)"  channel", buf, io->stdOut);

  (void)McuNRF24L01_GetAddressWidth(&val0);
  McuUtility_Num8uToStr(buf, sizeof(buf), val0);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" bytes\r\n");
  McuShell_SendStatusStr((unsigned char*)"  addr width", buf, io->stdOut);

  {
    int i, pipe; /* Pipes 0 to 5 */
    uint8_t pipeAddr[RADIO_NOF_ADDR_BYTES];
    uint8_t str[sizeof("  RX_ADDR_Px")];

    for(i=0;i<RADIO_NOF_ADDR_BYTES;i++) {
      pipeAddr[i] = 0; /* init */
    }
    /* TX_ADDR */
    buf[0] = '\0';
    (void)McuNRF24L01_GetTxAddress(pipeAddr, sizeof(pipeAddr));
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"0x");
    for(i=0;i<RADIO_NOF_ADDR_BYTES;i++) {
      McuUtility_strcatNum8Hex(buf, sizeof(buf), pipeAddr[i]);
    }
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    McuShell_SendStatusStr((unsigned char*)"  TX_ADDR", buf, io->stdOut);

    for (pipe=0;pipe<6;pipe++) { /* pipes 0 to 5 */
      /* RX_ADDR_Px */
      (void)McuNRF24L01_GetRxAddress(pipe, &pipeAddr[0], sizeof(pipeAddr));
      buf[0] = '\0';
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"0x");
      for(i=0;i<RADIO_NOF_ADDR_BYTES;i++) {
        McuUtility_strcatNum8Hex(buf, sizeof(buf), pipeAddr[i]);
      }
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
      McuUtility_strcpy(str, sizeof(str), (unsigned char*)"  RX_ADDR_P");
      McuUtility_strcatNum8u(str, sizeof(str), pipe);
      McuShell_SendStatusStr(str, buf, io->stdOut);
    }
  }

  (void)McuNRF24L01_GetOutputPower(&val);
  McuUtility_Num8sToStr(buf, sizeof(buf), val);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" dBm\r\n");
  McuShell_SendStatusStr((unsigned char*)"  power", buf, io->stdOut);
 
  (void)McuNRF24L01_GetDataRate(&dataRate);
  McuUtility_Num16uToStr(buf, sizeof(buf), dataRate);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" kbps\r\n");
  McuShell_SendStatusStr((unsigned char*)"  data rate", buf, io->stdOut);

  val0 = McuNRF24L01_GetStatus();
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), val0);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)": ");
  if (val0&McuNRF24L01_STATUS_RX_DR) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"RX_DR ");
  }
  if (val0&McuNRF24L01_STATUS_TX_DS) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"TX_DS ");
  }
  if (val0&McuNRF24L01_STATUS_MAX_RT) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"MAX_RT ");
  }
  if ((val0&McuNRF24L01_STATUS_RX_P_NO) == McuNRF24L01_STATUS_RX_P_NO_RX_FIFO_EMPTY) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"RxFifoEmpty ");
  }
  if ((val0&McuNRF24L01_STATUS_RX_P_NO) == McuNRF24L01_STATUS_RX_P_NO_UNUSED) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"RxUnused ");
  }
  if ((val0&McuNRF24L01_STATUS_RX_P_NO) == McuNRF24L01_STATUS_RX_P_NO_5) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"RxP#5 ");
  }
  if ((val0&McuNRF24L01_STATUS_RX_P_NO) == McuNRF24L01_STATUS_RX_P_NO_4) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"RxP#4 ");
  }
  if ((val0&McuNRF24L01_STATUS_RX_P_NO) == McuNRF24L01_STATUS_RX_P_NO_3) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"RxP#3 ");
  }
  if ((val0&McuNRF24L01_STATUS_RX_P_NO) == McuNRF24L01_STATUS_RX_P_NO_2) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"RxP#2 ");
  }
  if ((val0&McuNRF24L01_STATUS_RX_P_NO) == McuNRF24L01_STATUS_RX_P_NO_1) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"RxP#1 ");
  }
  if ((val0&McuNRF24L01_STATUS_RX_P_NO) == McuNRF24L01_STATUS_RX_P_NO_0) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"RxP#0 ");
  }
  if (val0&McuNRF24L01_STATUS_TX_FULL) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"TX_FULL ");
  }
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  STATUS", buf, io->stdOut);

  (void)McuNRF24L01_GetFifoStatus(&val0);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), val0);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)": ");
  if (val0&McuNRF24L01_FIFO_STATUS_TX_REUSE) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"REUSE ");
  }
  if (val0&McuNRF24L01_FIFO_STATUS_TX_FULL) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"TX_FULL ");
  }
  if (val0&McuNRF24L01_FIFO_STATUS_TX_EMPTY) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"TX_EMPTY ");
  }
  if (val0&McuNRF24L01_FIFO_STATUS_RX_FULL) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"RX_FULL ");
  }
  if (val0&McuNRF24L01_FIFO_STATUS_RX_EMPTY) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"RX_EMPTY ");
  }
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  FIFO_STATUS", buf, io->stdOut);

  (void)McuNRF24L01_ReadObserveTxRegister(&val0, &val1);
  McuUtility_Num8uToStr(buf, sizeof(buf), val0);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" lost, ");
  McuUtility_strcatNum8u(buf, sizeof(buf), val1);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" retry\r\n");
  McuShell_SendStatusStr((unsigned char*)"  OBSERVE_TX", buf, io->stdOut);
#if 0  /* The RPD status will get reset very fast by another (e.g. WLAN) packet. So this is not really a useful feature :-( */
  (void)McuNRF24L01_ReadReceivedPowerDetector(&val0); /*! \todo only works in RX mode, but somehow this still does not work? */
  if (val0&1) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"1, > -64 dBm\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0, < -64 dBm\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  RPD", buf, io->stdOut);
#endif
  McuUtility_Num16uToStr(buf, sizeof(buf), RNET_CONFIG_SEND_RETRY_CNT);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  Max Retries", buf, io->stdOut);
}

uint8_t RADIO_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;
  const unsigned char *p;
  uint8_t val;
  int8_t vals;
  uint8_t addr[RADIO_NOF_ADDR_BYTES];
  int i;

  if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, (char*)"radio help")==0) {
    RADIO_PrintHelp(io);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_STATUS)==0 || McuUtility_strcmp((char*)cmd, (char*)"radio status")==0) {
    RADIO_PrintStatus(io);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, (char*)"radio sniff on")==0) {
    RADIO_isSniffing = TRUE;
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, (char*)"radio sniff off")==0) {
    RADIO_isSniffing = FALSE;
    *handled = TRUE;
  } else if (McuUtility_strncmp((char*)cmd, (char*)"radio channel", sizeof("radio channel")-1)==0) {
    p = cmd+sizeof("radio channel");
    if (McuUtility_ScanDecimal8uNumber(&p, &val)==ERR_OK && val<=0x7F) {
      res = RADIO_SetChannel(val);
      *handled = TRUE;
    } else {
      McuShell_SendStr((unsigned char*)"Wrong argument, must be in the range 0..128\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, (char*)"radio power", sizeof("radio power")-1)==0) {
    p = cmd+sizeof("radio power");
    if (McuUtility_ScanDecimal8sNumber(&p, &vals)==ERR_OK && (vals==0 || vals==-10 || vals==-12 || vals==-18)) {
      (void)McuNRF24L01_SetOutputPower(vals);
      *handled = TRUE;
    } else {
      McuShell_SendStr((unsigned char*)"Wrong argument, must be 0, -10, -12 or -18\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, (char*)"radio writereg", sizeof("radio writereg")-1)==0) {
    uint8_t reg;
    
    p = cmd+sizeof("radio writereg");
    if (McuUtility_ScanHex8uNumber(&p, &reg)==ERR_OK && McuUtility_ScanHex8uNumber(&p, &val)==ERR_OK) {
      McuNRF24L01_WriteRegister(reg, val);
      *handled = TRUE;
    } else {
      McuShell_SendStr((unsigned char*)"Wrong arguments\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, (char*)"radio readreg", sizeof("radio readreg")-1)==0) {
    uint8_t reg;
    uint8_t buf[16];

    p = cmd+sizeof("radio readreg");
    if (McuUtility_ScanHex8uNumber(&p, &reg)==ERR_OK) {
      val = McuNRF24L01_ReadRegister(reg);
      buf[0] = '\0';
      McuUtility_strcpy(buf, sizeof(buf), (uint8_t*)"0x");
      McuUtility_strcatNum8Hex(buf, sizeof(buf), val);
      McuUtility_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
      McuShell_SendStr(buf, io->stdOut);
      *handled = TRUE;
    } else {
      McuShell_SendStr((unsigned char*)"Wrong arguments\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (McuUtility_strcmp((char*)cmd, (char*)"radio flush")==0) {
    *handled = TRUE;
    if (RADIO_Flush()!=ERR_OK) {
      McuShell_SendStr((unsigned char*)"Flushing failed!\r\n", io->stdErr);
      res = ERR_FAILED;
    }
    if (RADIO_FlushQueues()!=ERR_OK) {
      McuShell_SendStr((unsigned char*)"Flushing queues failed!\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (McuUtility_strcmp((char*)cmd, (char*)"radio printregs")==0) {
    RadioPrintRegisters(io);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, (char*)"radio datarate 250")==0) {
    (void)McuNRF24L01_SetDataRate(250);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, (char*)"radio datarate 1000")==0) {
    (void)McuNRF24L01_SetDataRate(1000);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, (char*)"radio datarate 2000")==0) {
    (void)McuNRF24L01_SetDataRate(2000);
    *handled = TRUE;
  } else if (McuUtility_strncmp((char*)cmd, (char*)"radio txaddr ", sizeof("radio txaddr ")-1)==0) {
    p = cmd+sizeof("radio txaddr ")-1;
    for(i=0;i<RADIO_NOF_ADDR_BYTES;i++) {
      if (McuUtility_ScanHex8uNumber(&p, &addr[i])!=ERR_OK) {
        /* error parsing number */
        McuShell_SendStr((unsigned char*)"Error reading hex number!\r\n", io->stdErr);
        res = ERR_FAILED;
        break; /* break for loop */
      }
    } /* for */
    if (McuNRF24L01_SetTxAddress(addr, sizeof(addr))!=ERR_OK) {
      McuShell_SendStr((unsigned char*)"Error setting TX address!\r\n", io->stdErr);
      res = ERR_FAILED;
    }
    *handled = TRUE;
  } else if (McuUtility_strncmp((char*)cmd, (char*)"radio rxaddr ", sizeof("radio rxaddr ")-1)==0) {
    uint8_t pipe;

    p = cmd+sizeof("radio rxaddr ")-1;
    if (McuUtility_ScanDecimal8uNumber(&p, &pipe)==ERR_OK) {
      for(i=0;i<RADIO_NOF_ADDR_BYTES;i++) {
        if (McuUtility_ScanHex8uNumber(&p, &addr[i])!=ERR_OK) {
          /* error parsing number */
          McuShell_SendStr((unsigned char*)"Error reading hex number!\r\n", io->stdErr);
          res = ERR_FAILED;
          break; /* break for loop */
        }
      } /* for */
      if (McuNRF24L01_SetRxAddress(pipe, addr, sizeof(addr))!=ERR_OK) {
        McuShell_SendStr((unsigned char*)"Error setting RX address!\r\n", io->stdErr);
        res = ERR_FAILED;
      }
    }
    *handled = TRUE;
  }
  return res;
}

void RADIO_Deinit(void) {
  /* nothing to do */
}

void RADIO_Init(void) {
  RADIO_isSniffing = FALSE;
  RADIO_CurrChannel = RADIO_CHANNEL_DEFAULT;
}
  
#endif /* McuRNET_CONFIG_IS_ENABLED */

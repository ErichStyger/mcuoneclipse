/**
 * \file
 * \brief This is the implementation of the Nordic Semiconductor nRF24L01+ low level driver.
 * \author (c) 2013-2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module deals with the low level functions of the transceiver.
 */

#include "RNetConf.h"
#include "Radio.h"
#include "RadioNRF24.h"
#include "%@nRF24L01p@'ModuleName'.h"
#include "RMSG.h"
#include "RStdIO.h"
#include "RPHY.h"
#include "%@Utility@'ModuleName'.h"

#define NRF24_DYNAMIC_PAYLOAD  1 /* if set to one, use dynamic payload size */
#define RADIO_CHANNEL_DEFAULT  RNET_CONFIG_TRANSCEIVER_CHANNEL  /* default communication channel */

/* macros to configure device either for RX or TX operation */
#define %@nRF24L01p@'ModuleName'%.CONFIG_SETTINGS  (%@nRF24L01p@'ModuleName'%.EN_CRC|%@nRF24L01p@'ModuleName'%.CRCO)
#define TX_POWERUP()         %@nRF24L01p@'ModuleName'%.WriteRegister(%@nRF24L01p@'ModuleName'%.CONFIG, %@nRF24L01p@'ModuleName'%.CONFIG_SETTINGS|%@nRF24L01p@'ModuleName'%.PWR_UP|%@nRF24L01p@'ModuleName'%.PRIM_TX) /* enable 1 byte CRC, power up and set as PTX */
#define RX_POWERUP()         %@nRF24L01p@'ModuleName'%.WriteRegister(%@nRF24L01p@'ModuleName'%.CONFIG, %@nRF24L01p@'ModuleName'%.CONFIG_SETTINGS|%@nRF24L01p@'ModuleName'%.PWR_UP|%@nRF24L01p@'ModuleName'%.PRIM_RX) /* enable 1 byte CRC, power up and set as PRX */
#define POWERDOWN()          %@nRF24L01p@'ModuleName'%.WriteRegister(%@nRF24L01p@'ModuleName'%.CONFIG, %@nRF24L01p@'ModuleName'%.CONFIG_SETTINGS) /* power down */

static bool RADIO_isSniffing = FALSE;
static const uint8_t RADIO_TADDR[5] = {0x11, 0x22, 0x33, 0x44, 0x55}; /* device address */

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

/* need to have this in case RF device is still added to project */
static volatile bool RADIO_isrFlag; /* flag set by ISR */

static void Err(unsigned char *msg) {
%if defined(Shell)
  %@Shell@'ModuleName'%.SendStr(msg, %@Shell@'ModuleName'%.GetStdio()->stdErr);
%endif
}

/* callback called from radio driver */
void RADIO_OnInterrupt(void) {
  RADIO_isrFlag = TRUE;
}

static uint8_t RADIO_Flush(void) {
  uint8_t res = ERR_OK;
  
  if (RPHY_FlushRxQueue()!=ERR_OK) {
    res = ERR_FAILED;
  }
  if (RPHY_FlushTxQueue()!=ERR_OK) {
    res = ERR_FAILED;
  }
  %@nRF24L01p@'ModuleName'%.Write(%@nRF24L01p@'ModuleName'%.FLUSH_RX); /* flush old data */
  %@nRF24L01p@'ModuleName'%.Write(%@nRF24L01p@'ModuleName'%.FLUSH_TX); /* flush old data */
  return res;
}

uint8_t RADIO_PowerDown(void) {
  uint8_t res;
  
  res = RADIO_Flush();
  POWERDOWN();
  return res;
}

static uint8_t CheckTx(void) {
  RPHY_PacketDesc packet;
  uint8_t res = ERR_OK;
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
    %@nRF24L01p@'ModuleName'%.StopRxTx();  /* CE low */
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
    %@nRF24L01p@'ModuleName'%.TxPayload(packet.rxtx, RPHY_BUF_SIZE(packet.phyData)); /* send data, using dynamic payload size */
#else
    %@nRF24L01p@'ModuleName'%.TxPayload(packet.rxtx, RPHY_PAYLOAD_SIZE); /* send data, using fixed payload size */
#endif
    return ERR_OK;
  } else {
    return ERR_NOTAVAIL; /* no data to send? */
  }
  return res;
}

/* called to check if we have something in the RX queue. If so, we queue it */
static uint8_t CheckRx(void) {
  uint8_t res = ERR_OK;
  uint8_t RxDataBuffer[RPHY_BUFFER_SIZE];
  uint8_t status;
  RPHY_PacketDesc packet;
  bool hasRxData;
  
  hasRxData = FALSE;
  packet.flags = RPHY_PACKET_FLAGS_NONE;
  packet.phyData = &RxDataBuffer[0];
  packet.phySize = sizeof(RxDataBuffer);
#if NRF24_DYNAMIC_PAYLOAD
  packet.rxtx = RPHY_BUF_PAYLOAD_START(packet.phyData);
#else
  packet.rxtx = &RPHY_BUF_SIZE(packet.phyData); /* we transmit the data size too */
#endif
  status = %@nRF24L01p@'ModuleName'%.GetStatusClrIRQ();
  if (status&%@nRF24L01p@'ModuleName'%.STATUS_RX_DR) { /* data received interrupt */
    hasRxData = TRUE;
#if NRF24_DYNAMIC_PAYLOAD
    uint8_t payloadSize;
    
    (void)%@nRF24L01p@'ModuleName'%.ReadNofRxPayload(&payloadSize);
    if (payloadSize>32) { /* packet with error? */
      %@nRF24L01p@'ModuleName'%.Write(%@nRF24L01p@'ModuleName'%.FLUSH_RX); /* flush old data */
      return ERR_FAILED;
    } else {
      %@nRF24L01p@'ModuleName'%.RxPayload(packet.rxtx, payloadSize); /* get payload: note that we transmit <size> as payload! */
      RPHY_BUF_SIZE(packet.phyData) = payloadSize;
    }
#else
    %@nRF24L01p@'ModuleName'%.RxPayload(packet.rxtx, RPHY_PAYLOAD_SIZE); /* get payload: note that we transmit <size> as payload! */
#endif
  }
  if (hasRxData) {
    /* put message into Rx queue */
    res = RMSG_QueueRxMsg(packet.phyData, packet.phySize, RPHY_BUF_SIZE(packet.phyData), packet.flags);
    if (res!=ERR_OK) {
      if (res==ERR_OVERFLOW) {
        Err((unsigned char*)"ERR: Rx queue overflow!\r\n");
      } else {
        Err((unsigned char*)"ERR: Rx Queue full?\r\n");
      }
    }
  }
  return res;
}

static void RADIO_HandleStateMachine(void) {
  uint8_t status, res;
  
  for(;;) { /* will break/return */
    switch (RADIO_AppStatus) {
      case RADIO_INITIAL_STATE:
        %@nRF24L01p@'ModuleName'%.StopRxTx();  /* will send/receive data later */
        RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* turn receive on */
        break; /* process switch again */
  
      case RADIO_RECEIVER_ALWAYS_ON: /* turn receive on */
        RX_POWERUP();
        %@nRF24L01p@'ModuleName'%.StartRxTx(); /* Listening for packets */
        RADIO_AppStatus = RADIO_READY_FOR_TX_RX_DATA;
        break; /* process switch again */
  
      case RADIO_READY_FOR_TX_RX_DATA: /* we are ready to receive/send data data */
#if !%@nRF24L01p@'ModuleName'%.IRQ_PIN_ENABLED
        %@nRF24L01p@'ModuleName'%.PollInterrupt();
#endif
        if (RADIO_isrFlag) { /* Rx interrupt? */
          RADIO_isrFlag = FALSE; /* reset interrupt flag */
          (void)CheckRx(); /* get message */
          RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* continue listening */
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
#if !%@nRF24L01p@'ModuleName'%.IRQ_PIN_ENABLED
        %@nRF24L01p@'ModuleName'%.PollInterrupt();
#endif
        if (RADIO_isrFlag) { /* check if we have received an interrupt: this is either timeout or low level ack */
          RADIO_isrFlag = FALSE; /* reset interrupt flag */
          status = %@nRF24L01p@'ModuleName'%.GetStatusClrIRQ();
          if (status&%@nRF24L01p@'ModuleName'%.STATUS_MAX_RT) { /* retry timeout interrupt */
            %@nRF24L01p@'ModuleName'%.Write(%@nRF24L01p@'ModuleName'%.FLUSH_TX); /* flush old data */
            RADIO_AppStatus = RADIO_TIMEOUT; /* timeout */
          } else {
            RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* turn receive on */
          }
          break; /* process switch again */
        }
        return;
        
      case RADIO_TIMEOUT:
#if RNET_CONFIG_SEND_RETRY_CNT>0
        if (RADIO_RetryCnt<RNET_CONFIG_SEND_RETRY_CNT) {
          Err((unsigned char*)"ERR: Retry\r\n");
          RADIO_RetryCnt++;
          if (RMSG_PutRetryTxMsg(TxDataBuffer, sizeof(TxDataBuffer))==ERR_OK) {
            RADIO_AppStatus = RADIO_CHECK_TX; /* resend packet */
            return; /* iterate state machine next time */
          } else {
            Err((unsigned char*)"ERR: Retry failed!\r\n");
          }
        }
#endif
        Err((unsigned char*)"ERR: Timeout\r\n");
        RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* turn receive on */
        break; /* process switch again */
  
      default: /* should not happen! */
        return;
    } /* switch */
  } /* for */
}

uint8_t RADIO_SetChannel(uint8_t channel) {
  return %@nRF24L01p@'ModuleName'%.SetChannel(channel);
}

/*! 
 * \brief Radio power-on initialization.
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t RADIO_PowerUp(void) {
  %@nRF24L01p@'ModuleName'%.Init(); /* set CE and CSN to initialization value */
  
  %@nRF24L01p@'ModuleName'%.WriteRegister(%@nRF24L01p@'ModuleName'%.RF_SETUP, %@nRF24L01p@'ModuleName'%.RF_SETUP_RF_PWR_0|RNET_CONFIG_NRF24_DATA_RATE);
//  %@nRF24L01p@'ModuleName'%.WriteRegister(%@nRF24L01p@'ModuleName'%.RF_SETUP, %@nRF24L01p@'ModuleName'%.RF_SETUP_RF_PWR_18|%@nRF24L01p@'ModuleName'%.RF_SETUP_RF_DR_1000);
#if NRF24_DYNAMIC_PAYLOAD
  /* enable dynamic payload */
  %@nRF24L01p@'ModuleName'%.WriteFeature(%@nRF24L01p@'ModuleName'%.FEATURE_EN_DPL|%@nRF24L01p@'ModuleName'%.FEATURE_EN_ACK_PAY|%@nRF24L01p@'ModuleName'%.FEATURE_EN_DYN_PAY); /* set EN_DPL for dynamic payload */
  %@nRF24L01p@'ModuleName'%.EnableDynamicPayloadLength(%@nRF24L01p@'ModuleName'%.DYNPD_DPL_P0); /* set DYNPD register for dynamic payload for pipe0 */
#else
  %@nRF24L01p@'ModuleName'%.SetStaticPipePayload(0, RPHY_PAYLOAD_SIZE); /* static number of payload bytes we want to send and receive */
#endif
  (void)RADIO_SetChannel(RADIO_CHANNEL_DEFAULT);

  /* Set RADDR and TADDR as the transmit address since we also enable auto acknowledgment */
  %@nRF24L01p@'ModuleName'%.WriteRegisterData(%@nRF24L01p@'ModuleName'%.RX_ADDR_P0, (uint8_t*)RADIO_TADDR, sizeof(RADIO_TADDR));
  %@nRF24L01p@'ModuleName'%.WriteRegisterData(%@nRF24L01p@'ModuleName'%.TX_ADDR, (uint8_t*)RADIO_TADDR, sizeof(RADIO_TADDR));

  /* Enable RX_ADDR_P0 address matching */
  %@nRF24L01p@'ModuleName'%.WriteRegister(%@nRF24L01p@'ModuleName'%.EN_RXADDR, %@nRF24L01p@'ModuleName'%.EN_RXADDR_ERX_P0); /* enable data pipe 0 */
  
  /* clear interrupt flags */
  %@nRF24L01p@'ModuleName'%.ResetStatusIRQ(%@nRF24L01p@'ModuleName'%.STATUS_RX_DR|%@nRF24L01p@'ModuleName'%.STATUS_TX_DS|%@nRF24L01p@'ModuleName'%.STATUS_MAX_RT);
  
  /* rx/tx mode */
  %@nRF24L01p@'ModuleName'%.EnableAutoAck(%@nRF24L01p@'ModuleName'%.EN_AA_ENAA_P0); /* enable auto acknowledge on pipe 0. RX_ADDR_P0 needs to be equal to TX_ADDR! */
  %@nRF24L01p@'ModuleName'%.WriteRegister(%@nRF24L01p@'ModuleName'%.SETUP_RETR, %@nRF24L01p@'ModuleName'%.SETUP_RETR_ARD_750|%@nRF24L01p@'ModuleName'%.SETUP_RETR_ARC_15); /* Important: need 750 us delay between every retry */
  
  RX_POWERUP();  /* Power up in receiving mode */
  RADIO_Flush(); /* flush possible old data */
  %@nRF24L01p@'ModuleName'%.StartRxTx(); /* Listening for packets */

  RADIO_AppStatus = RADIO_INITIAL_STATE;
  /* init Rx descriptor */
  radioRx.phyData = &radioRxBuf[0];
  radioRx.phySize = sizeof(radioRxBuf);
  radioRx.rxtx = &RPHY_BUF_SIZE(radioRx.phyData); /* we transmit the size too */
  return ERR_OK;
}

uint8_t RADIO_Process(void) {
  uint8_t res;
  
  RADIO_HandleStateMachine(); /* process state machine */
  /* process received packets */
  res = RPHY_GetPayload(&radioRx); /* get message */
  if (res==ERR_OK) { /* packet received */
    if (RADIO_isSniffing) {
      RPHY_SniffPacket(&radioRx, FALSE); /* sniff incoming packet */
    }
    if (RPHY_OnPacketRx(&radioRx)==ERR_OK) { /* process incoming packets */
      if (radioRx.flags&RPHY_PACKET_FLAGS_IS_ACK) { /* it was an ack! */
        //EVNT_SetEvent(EVNT_RADIO_ACK); /* set event */
      }
    }
  }
  return ERR_OK;
}

%if defined(Shell)
static const unsigned char *RadioStateStr(RADIO_AppStatusKind state) {
  switch(state) {
    case RADIO_INITIAL_STATE:         return (const unsigned char*)"INITIAL";
    case RADIO_RECEIVER_ALWAYS_ON:    return (const unsigned char*)"ALWAYS_ON";
    case RADIO_TRANSMIT_DATA:         return (const unsigned char*)"TRANSMIT_DATA";
    case RADIO_WAITING_DATA_SENT:     return (const unsigned char*)"WAITING_DATA_SENT";
    case RADIO_READY_FOR_TX_RX_DATA:  return (const unsigned char*)"READY_TX_RX";
    case RADIO_CHECK_TX:              return (const unsigned char*)"CHECK_TX";
    case RADIO_POWER_DOWN:            return (const unsigned char*)"POWER_DOWN"; 
    default:                          return (const unsigned char*)"UNKNOWN";
  }
  return (const unsigned char*)"UNKNOWN";
}

static void RADIO_PrintHelp(const %@Shell@'ModuleName'%.StdIOType *io) {
  %@Shell@'ModuleName'%.SendHelpStr((unsigned char*)"radio", (unsigned char*)"Group of radio commands\r\n", io->stdOut);
  %@Shell@'ModuleName'%.SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows radio help or status\r\n", io->stdOut);
  %@Shell@'ModuleName'%.SendHelpStr((unsigned char*)"  channel <number>", (unsigned char*)"Switches to the given channel. Channel must be in the range 0..127\r\n", io->stdOut);
  %@Shell@'ModuleName'%.SendHelpStr((unsigned char*)"  power <number>", (unsigned char*)"Changes output power to 0, -10, -12, -18\r\n", io->stdOut);
  %@Shell@'ModuleName'%.SendHelpStr((unsigned char*)"  sniff on|off", (unsigned char*)"Turns sniffing on or off\r\n", io->stdOut);
  %@Shell@'ModuleName'%.SendHelpStr((unsigned char*)"  writereg 0xReg 0xVal", (unsigned char*)"Write a transceiver register\r\n", io->stdOut);
  %@Shell@'ModuleName'%.SendHelpStr((unsigned char*)"  flush", (unsigned char*)"Empty all queues\r\n", io->stdOut);
  %@Shell@'ModuleName'%.SendHelpStr((unsigned char*)"  printreg", (unsigned char*)"Print the radio registers\r\n", io->stdOut);
}

static void RadioPrintRegisters(%@Shell@'ModuleName'%.ConstStdIOType *io) {
  int i;
  uint8_t val;
  uint8_t bufidx[16], buf[16];
  
  for(i=0;i<=0x1D;i++) {
    val = %@nRF24L01p@'ModuleName'%.ReadRegister(i);
    %@Utility@'ModuleName'%.strcpy(bufidx, sizeof(bufidx), (unsigned char*)"  addr 0x");
    %@Utility@'ModuleName'%.strcatNum8Hex(bufidx, sizeof(bufidx), i);
    buf[0] = '\0';
    %@Utility@'ModuleName'%.strcatNum8Hex(buf, sizeof(buf), val);
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    %@Shell@'ModuleName'%.SendStatusStr(bufidx, buf, io->stdOut);
  }
}

static void RADIO_PrintStatus(const %@Shell@'ModuleName'%.StdIOType *io) {
  uint8_t buf[48];
  uint8_t val0, val1;
  int8_t val;
  uint16_t dataRate;
  
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"Radio", (unsigned char*)"\r\n", io->stdOut);
  
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"  state", RadioStateStr(RADIO_AppStatus), io->stdOut);
  %@Shell@'ModuleName'%.SendStr((unsigned char*)"\r\n", io->stdOut);
  
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"  sniff", RADIO_isSniffing?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  
  (void)%@nRF24L01p@'ModuleName'%.GetChannel(&val0);
  %@Utility@'ModuleName'%.Num8uToStr(buf, sizeof(buf), val0);
  %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"  channel", buf, io->stdOut);

  (void)%@nRF24L01p@'ModuleName'%.GetOutputPower(&val);
  %@Utility@'ModuleName'%.Num8sToStr(buf, sizeof(buf), val);
  %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)" dBm\r\n");
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"  power", buf, io->stdOut);
 
  (void)%@nRF24L01p@'ModuleName'%.GetDataRate(&dataRate);
  %@Utility@'ModuleName'%.Num16uToStr(buf, sizeof(buf), dataRate);
  %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)" kbps\r\n");
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"  data rate", buf, io->stdOut);

  val0 = %@nRF24L01p@'ModuleName'%.GetStatus();
  %@Utility@'ModuleName'%.strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  %@Utility@'ModuleName'%.strcatNum8Hex(buf, sizeof(buf), val0);
  %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)": ");
  if (val0&%@nRF24L01p@'ModuleName'%.STATUS_RX_DR) {
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"RX_DR ");
  }
  if (val0&%@nRF24L01p@'ModuleName'%.STATUS_TX_DS) {
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"TX_DS ");
  }
  if (val0&%@nRF24L01p@'ModuleName'%.STATUS_MAX_RT) {
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"MAX_RT ");
  }
  if ((val0&%@nRF24L01p@'ModuleName'%.STATUS_RX_P_NO) == %@nRF24L01p@'ModuleName'%.STATUS_RX_P_NO_RX_FIFO_EMPTY) {
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"RxFifoEmpty ");
  }
  if ((val0&%@nRF24L01p@'ModuleName'%.STATUS_RX_P_NO) == %@nRF24L01p@'ModuleName'%.STATUS_RX_P_NO_UNUSED) {
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"RxUnused ");
  }
  if ((val0&%@nRF24L01p@'ModuleName'%.STATUS_RX_P_NO) == %@nRF24L01p@'ModuleName'%.STATUS_RX_P_NO_5) {
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"RxP#5 ");
  }
  if ((val0&%@nRF24L01p@'ModuleName'%.STATUS_RX_P_NO) == %@nRF24L01p@'ModuleName'%.STATUS_RX_P_NO_4) {
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"RxP#4 ");
  }
  if ((val0&%@nRF24L01p@'ModuleName'%.STATUS_RX_P_NO) == %@nRF24L01p@'ModuleName'%.STATUS_RX_P_NO_3) {
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"RxP#3 ");
  }
  if ((val0&%@nRF24L01p@'ModuleName'%.STATUS_RX_P_NO) == %@nRF24L01p@'ModuleName'%.STATUS_RX_P_NO_2) {
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"RxP#2 ");
  }
  if ((val0&%@nRF24L01p@'ModuleName'%.STATUS_RX_P_NO) == %@nRF24L01p@'ModuleName'%.STATUS_RX_P_NO_1) {
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"RxP#1 ");
  }
  if ((val0&%@nRF24L01p@'ModuleName'%.STATUS_RX_P_NO) == %@nRF24L01p@'ModuleName'%.STATUS_RX_P_NO_0) {
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"RxP#0 ");
  }
  if (val0&%@nRF24L01p@'ModuleName'%.STATUS_TX_FULL) {
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"TX_FULL ");
  }
  %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"  STATUS", buf, io->stdOut);

  (void)%@nRF24L01p@'ModuleName'%.GetFifoStatus(&val0);
  %@Utility@'ModuleName'%.strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  %@Utility@'ModuleName'%.strcatNum8Hex(buf, sizeof(buf), val0);
  %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)": ");
  if (val0&%@nRF24L01p@'ModuleName'%.FIFO_STATUS_TX_REUSE) {
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"REUSE ");
  }
  if (val0&%@nRF24L01p@'ModuleName'%.FIFO_STATUS_TX_FULL) {
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"TX_FULL ");
  }
  if (val0&%@nRF24L01p@'ModuleName'%.FIFO_STATUS_TX_EMPTY) {
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"TX_EMPTY ");
  }
  if (val0&%@nRF24L01p@'ModuleName'%.FIFO_STATUS_RX_FULL) {
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"RX_FULL ");
  }
  if (val0&%@nRF24L01p@'ModuleName'%.FIFO_STATUS_RX_EMPTY) {
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"RX_EMPTY ");
  }
  %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"  FIFO_STATUS", buf, io->stdOut);

  (void)%@nRF24L01p@'ModuleName'%.ReadObserveTxRegister(&val0, &val1);
  %@Utility@'ModuleName'%.Num8uToStr(buf, sizeof(buf), val0);
  %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)" lost, ");
  %@Utility@'ModuleName'%.strcatNum8u(buf, sizeof(buf), val1);
  %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)" retry\r\n");
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"  OBSERVE_TX", buf, io->stdOut);
#if 0  /* The RPD status will get reset very fast by another (e.g. WLAN) packet. So this is not really a useful feature :-( */
  (void)%@nRF24L01p@'ModuleName'%.ReadReceivedPowerDetector(&val0); /*! \todo only works in RX mode, but somehow this still does not work? */
  if (val0&1) {
    %@Utility@'ModuleName'%.strcpy(buf, sizeof(buf), (unsigned char*)"1, > -64 dBm\r\n");
  } else {
    %@Utility@'ModuleName'%.strcpy(buf, sizeof(buf), (unsigned char*)"0, < -64 dBm\r\n");
  }
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"  RPD", buf, io->stdOut);
#endif
}

uint8_t RADIO_ParseCommand(const unsigned char *cmd, bool *handled, const %@Shell@'ModuleName'%.StdIOType *io) {
  uint8_t res = ERR_OK;
  const unsigned char *p;
  uint8_t val;
  int8_t vals;

  if (%@Utility@'ModuleName'%.strcmp((char*)cmd, (char*)%@Shell@'ModuleName'%.CMD_HELP)==0 || %@Utility@'ModuleName'%.strcmp((char*)cmd, (char*)"radio help")==0) {
    RADIO_PrintHelp(io);
    *handled = TRUE;
  } else if (%@Utility@'ModuleName'%.strcmp((char*)cmd, (char*)%@Shell@'ModuleName'%.CMD_STATUS)==0 || %@Utility@'ModuleName'%.strcmp((char*)cmd, (char*)"radio status")==0) {
    RADIO_PrintStatus(io);
    *handled = TRUE;
  } else if (%@Utility@'ModuleName'%.strcmp((char*)cmd, (char*)"radio sniff on")==0) {
    RADIO_isSniffing = TRUE;
    *handled = TRUE;
  } else if (%@Utility@'ModuleName'%.strcmp((char*)cmd, (char*)"radio sniff off")==0) {
    RADIO_isSniffing = FALSE;
    *handled = TRUE;
  } else if (%@Utility@'ModuleName'%.strncmp((char*)cmd, (char*)"radio channel", sizeof("radio channel")-1)==0) {
    p = cmd+sizeof("radio channel");
    if (%@Utility@'ModuleName'%.ScanDecimal8uNumber(&p, &val)==ERR_OK && val>=0 && val<=0x7F) {
      RADIO_SetChannel(val);
      *handled = TRUE;
    } else {
      %@Shell@'ModuleName'%.SendStr((unsigned char*)"Wrong argument, must be in the range 0..128\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (%@Utility@'ModuleName'%.strncmp((char*)cmd, (char*)"radio power", sizeof("radio power")-1)==0) {
    p = cmd+sizeof("radio power");
    if (%@Utility@'ModuleName'%.ScanDecimal8sNumber(&p, &vals)==ERR_OK && (vals==0 || vals==-10 || vals==-12 || vals==-18)) {
      (void)%@nRF24L01p@'ModuleName'%.SetOutputPower(vals);
      *handled = TRUE;
    } else {
      %@Shell@'ModuleName'%.SendStr((unsigned char*)"Wrong argument, must be 0, -10, -12 or -18\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (%@Utility@'ModuleName'%.strncmp((char*)cmd, (char*)"radio writereg", sizeof("radio writereg")-1)==0) {
    uint8_t reg;
    
    p = cmd+sizeof("radio writereg");
    if (%@Utility@'ModuleName'%.ScanHex8uNumber(&p, &reg)==ERR_OK && %@Utility@'ModuleName'%.ScanHex8uNumber(&p, &val)==ERR_OK) {
      %@nRF24L01p@'ModuleName'%.WriteRegister(reg, val);
      *handled = TRUE;
    } else {
      %@Shell@'ModuleName'%.SendStr((unsigned char*)"Wrong arguments\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (%@Utility@'ModuleName'%.strcmp((char*)cmd, (char*)"radio flush")==0) {
    *handled = TRUE;
    if (RADIO_Flush()!=ERR_OK) {
      %@Shell@'ModuleName'%.SendStr((unsigned char*)"Flushing failed!\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (%@Utility@'ModuleName'%.strcmp((char*)cmd, (char*)"radio printreg")==0) {
    RadioPrintRegisters(io);
    *handled = TRUE;
  }
  return res;
}
%endif

void RADIO_Deinit(void) {
  /* nothing to do */
}

void RADIO_Init(void) {
  RADIO_isSniffing = FALSE;
}

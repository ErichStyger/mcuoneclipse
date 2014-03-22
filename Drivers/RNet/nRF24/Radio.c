/**
 * \file
 * \brief This is the implementation of the Nordic Semiconductor nRF24L01+ low level driver.
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module deals with the low level functions of the transceiver.
 */

#include "RNetConf.h"
#include "Radio.h"
#include "RadioNRF24.h"
#include "RF1.h"
#include "RMSG.h"
#include "RStdIO.h"
#include "RPHY.h"
#include "WAIT1.h"
#include "%@Utility@'ModuleName'.h"

#define NRF24_DYNAMIC_PAYLOAD  1 /* if set to one, use dynamic payload size */
#define RADIO_CHANNEL_DEFAULT  0  /* default communication channel */

/* macros to configure device either for RX or TX operation */
#define RF1_CONFIG_SETTINGS  (RF1_EN_CRC|RF1_CRCO)
#define TX_POWERUP()         RF1_WriteRegister(RF1_CONFIG, RF1_CONFIG_SETTINGS|RF1_PWR_UP|RF1_PRIM_TX) /* enable 1 byte CRC, power up and set as PTX */
#define RX_POWERUP()         RF1_WriteRegister(RF1_CONFIG, RF1_CONFIG_SETTINGS|RF1_PWR_UP|RF1_PRIM_RX) /* enable 1 byte CRC, power up and set as PRX */
#define POWERDOWN()          RF1_WriteRegister(RF1_CONFIG, RF1_CONFIG_SETTINGS) /* power down */

static bool RADIO_isSniffing = FALSE;
static const uint8_t TADDR[5] = {0x11, 0x22, 0x33, 0x44, 0x55}; /* device address */

/* Radio state definitions */
typedef enum RADIO_AppStatusKind {
  RADIO_INITIAL_STATE, /* initial state of the state machine */
  RADIO_RECEIVER_ALWAYS_ON, /* receiver is in RX mode */
  RADIO_TRANSMIT_DATA, /* send data */
  RADIO_WAITING_DATA_SENT, /* wait until data is sent */
  RADIO_TIMEOUT,
  RADIO_READY_FOR_TX_RX_DATA,
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

uint8_t RADIO_PowerDown(void) {
  uint8_t res = ERR_OK;
  
  POWERDOWN();
  if (RPHY_FlushRxQueue()!=ERR_OK) {
    res = ERR_FAILED;
  }
  if (RPHY_FlushTxQueue()!=ERR_OK) {
    res = ERR_FAILED;
  }
  return res;
}

static uint8_t CheckTx(void) {
  RPHY_PacketDesc packet;
  uint8_t res = ERR_OK;
  uint8_t TxDataBuffer[RPHY_BUFFER_SIZE];
  RPHY_FlagsType flags;
  
  if (RMSG_GetTxMsg(TxDataBuffer, sizeof(TxDataBuffer))==ERR_OK) {
    flags = RPHY_BUF_FLAGS(TxDataBuffer);
    if (flags&RPHY_PACKET_FLAGS_POWER_DOWN) {
      /* special request */
      (void)RADIO_PowerDown();
      return ERR_DISABLED; /* no more data, pipes flushed */
    }
    RF1_StopRxTx();  /* CE low */
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
    RF1_TxPayload(packet.rxtx, RPHY_BUF_SIZE(packet.phyData)); /* send data, using dynamic payload size */
#else
    RF1_TxPayload(packet.rxtx, RPHY_PAYLOAD_SIZE); /* send data, using fixed payload size */
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
  status = RF1_GetStatusClrIRQ();
  if (status&RF1_STATUS_RX_DR) { /* data received interrupt */
    hasRxData = TRUE;
#if NRF24_DYNAMIC_PAYLOAD
    uint8_t payloadSize;
    
    (void)RF1_ReadNofRxPayload(&payloadSize);
    if (payloadSize>32) { /* packet with error? */
      RF1_Write(RF1_FLUSH_RX); /* flush old data */
      return ERR_FAILED;
    } else {
      RF1_RxPayload(packet.rxtx, payloadSize); /* get payload: note that we transmit <size> as payload! */
      RPHY_BUF_SIZE(packet.phyData) = payloadSize;
    }
#else
    RF1_RxPayload(packet.rxtx, RPHY_PAYLOAD_SIZE); /* get payload: note that we transmit <size> as payload! */
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
        RF1_StopRxTx();  /* will send/receive data later */
        RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* turn receive on */
        break; /* process switch again */
  
      case RADIO_RECEIVER_ALWAYS_ON: /* turn receive on */
        RX_POWERUP();
        RF1_StartRxTx(); /* Listening for packets */
        RADIO_AppStatus = RADIO_READY_FOR_TX_RX_DATA;
        break; /* process switch again */
  
      case RADIO_READY_FOR_TX_RX_DATA: /* we are ready to receive/send data data */
        if (RADIO_isrFlag) { /* Rx interrupt? */
          RADIO_isrFlag = FALSE; /* reset interrupt flag */
          (void)CheckRx(); /* get message */
          RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* continue listening */
          break; /* process switch again */
        }
        res = CheckTx();
        if (res==ERR_OK) { /* there was data and it has been sent */
          RADIO_AppStatus = RADIO_WAITING_DATA_SENT;
          break; /* process switch again */
        } else if (res==ERR_DISABLED) { /* powered down transceiver */
          RADIO_AppStatus = RADIO_POWER_DOWN;
        }
        return;
        
      case RADIO_POWER_DOWN:
        return;
  
      case RADIO_WAITING_DATA_SENT:
        if (RADIO_isrFlag) { /* check if we have received an interrupt: this is either timeout or low level ack */
          RADIO_isrFlag = FALSE; /* reset interrupt flag */
          status = RF1_GetStatusClrIRQ();
          if (status&RF1_STATUS_MAX_RT) { /* retry timeout interrupt */
            RF1_Write(RF1_FLUSH_TX); /* flush old data */
            RADIO_AppStatus = RADIO_TIMEOUT; /* timeout */
          } else {
            RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* turn receive on */
          }
          break; /* process switch again */
        }
        return;
        
      case RADIO_TIMEOUT:
        Err((unsigned char*)"ERR: Timeout\r\n");
        RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* turn receive on */
        break; /* process switch again */
  
      default: /* should not happen! */
        return;
    } /* switch */
  } /* for */
}

uint8_t RADIO_SetChannel(uint8_t channel) {
  return RF1_SetChannel(channel);
}

/*! 
 * \brief Radio power-on initialization.
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t RADIO_PowerUp(void) {
  RF1_Init(); /* set CE and CSN to initialization value */
  
  RF1_WriteRegister(RF1_RF_SETUP, RF1_RF_SETUP_RF_PWR_0|RF1_RF_SETUP_RF_DR_250);
//  RF1_WriteRegister(RF1_RF_SETUP, RF1_RF_SETUP_RF_PWR_18|RF1_RF_SETUP_RF_DR_1000);
#if NRF24_DYNAMIC_PAYLOAD
  /* enable dynamic payload */
  RF1_WriteFeature(RF1_FEATURE_EN_DPL|RF1_FEATURE_EN_ACK_PAY|RF1_FEATURE_EN_DYN_PAY); /* set EN_DPL for dynamic payload */
  RF1_EnableDynanicPayloadLength(RF1_DYNPD_DPL_P0); /* set DYNPD register for dynamic payload for pipe0 */
#else
  RF1_SetStaticPipePayload(0, RPHY_PAYLOAD_SIZE); /* static number of payload bytes we want to send and receive */
#endif
  (void)RADIO_SetChannel(RADIO_CHANNEL_DEFAULT);

  /* Set RADDR and TADDR as the transmit address since we also enable auto acknowledgment */
  RF1_WriteRegisterData(RF1_RX_ADDR_P0, (uint8_t*)TADDR, sizeof(TADDR));
  RF1_WriteRegisterData(RF1_TX_ADDR, (uint8_t*)TADDR, sizeof(TADDR));

  /* Enable RX_ADDR_P0 address matching */
  RF1_WriteRegister(RF1_EN_RXADDR, RF1_EN_RXADDR_ERX_P0); /* enable data pipe 0 */
  
  /* clear interrupt flags */
  RF1_ResetStatusIRQ(RF1_STATUS_RX_DR|RF1_STATUS_TX_DS|RF1_STATUS_MAX_RT);
  
  /* rx/tx mode */
  RF1_EnableAutoAck(RF1_EN_AA_ENAA_P0); /* enable auto acknowledge on pipe 0. RX_ADDR_P0 needs to be equal to TX_ADDR! */
  RF1_WriteRegister(RF1_SETUP_RETR, RF1_SETUP_RETR_ARD_750|RF1_SETUP_RETR_ARC_15); /* Important: need 750 us delay between every retry */
  
  RX_POWERUP();  /* Power up in receiving mode */
  RF1_StartRxTx(); /* Listening for packets */

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
}

static void RADIO_PrintStatus(const %@Shell@'ModuleName'%.StdIOType *io) {
  uint8_t buf[24];
  uint8_t val0, val1;
  int8_t val;
  
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"Radio", (unsigned char*)"\r\n", io->stdOut);
  
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"  state", RadioStateStr(RADIO_AppStatus), io->stdOut);
  %@Shell@'ModuleName'%.SendStr((unsigned char*)"\r\n", io->stdOut);
  
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"  sniff", RADIO_isSniffing?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  
  (void)RF1_GetChannel(&val0);
  %@Utility@'ModuleName'%.Num8uToStr(buf, sizeof(buf), val0);
  %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"  channel", buf, io->stdOut);

  (void)RF1_GetOutputPower(&val);
  %@Utility@'ModuleName'%.Num8sToStr(buf, sizeof(buf), val);
  %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)" dBm\r\n");
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"  power", buf, io->stdOut);
 
  (void)RF1_ReadObserveTxRegister(&val0, &val1);
  %@Utility@'ModuleName'%.Num8uToStr(buf, sizeof(buf), val0);
  %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)" lost, ");
  %@Utility@'ModuleName'%.strcatNum8u(buf, sizeof(buf), val1);
  %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)" retry\r\n");
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"  OBSERVE_TX", buf, io->stdOut);
#if 0  /* The RPD status will get reset very fast by another (e.g. WLAN) packet. So this is not really a useful feature :-( */
  (void)RF1_ReadReceivedPowerDetector(&val0); /*! \todo only works in RX mode, but somehow this still does not work? */
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
      (void)RF1_SetOutputPower(vals);
      *handled = TRUE;
    } else {
      %@Shell@'ModuleName'%.SendStr((unsigned char*)"Wrong argument, must be 0, -10, -12 or -18\r\n", io->stdErr);
      res = ERR_FAILED;
    }
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

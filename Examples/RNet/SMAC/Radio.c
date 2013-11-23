/**
 * \file
 * \brief Radio Module
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * Implementation of the Radio module to handle everything around the radio transceiver
 */

#include "RNetConf.h"
#if PL_HAS_RADIO
#include "Radio.h"
#include "RadioSMAC.h"
#include "SMAC1.h"
#include "UTIL1.h"
#include "Event.h"
#if PL_HAS_SHELL
  #include "CLS1.h"
#endif
#include "FRTOS1.h"
#if PL_HAS_RTOS_TRACE
  #include "RTOSTRC1.h"
#endif
#include "RPHY.h"
#include "RMAC.h"
#include "RMSG.h"

/* Radio state definitions */
typedef enum RADIO_AppStatusKind {
  RADIO_INITIAL_STATE,
  RADIO_RESET_STATE,
  RADIO_RECEIVER_ALWAYS_ON,
  RADIO_TRANSMIT_DATA,
  RADIO_WAIT_FOR_ACK,
  RADIO_READY_FOR_TX_RX_DATA
} RADIO_AppStatusKind;

#define RADIO_TIMEOUT_COUNT    0xB000 /*!< how long the timeout value will be while transmitting a message */

static volatile RADIO_AppStatusKind RADIO_AppStatus = RADIO_INITIAL_STATE;
static uint8_t RADIO_Channel = 5;
static uint8_t RADIO_OutputPower = 15;
static bool RADIO_isOn = TRUE;
static bool RADIO_isSniffing = FALSE;

static tRxPacket RADIO_RxPacket;            /*!< SMAC structure for RX packets */
static uint8_t RADIO_RxDataBuffer[RPHY_BUFFER_SIZE]; /*!< Data buffer to hold RX data */
static tTxPacket RADIO_TxPacket;            /*!< SMAC structure for TX packets */
static uint8_t RADIO_TxDataBuffer[RPHY_BUFFER_SIZE]; /*!< Data buffer to hold TX data */

static RPHY_PacketDesc radioRx, radioTx;
static uint8_t radioRxBuf[RPHY_BUFFER_SIZE];
static uint8_t radioTxBuf[RPHY_BUFFER_SIZE];

void RADIO_OnInterrupt(void) {
  uint8_t res;
  
  res = SMAC1_CheckRx(&RADIO_RxPacket);
  if (res==ERR_OK) {
    if (RADIO_RxPacket.u8Status==SMAC1_TIMEOUT) { /* Put timeout condition code here */
      EVNT_SetEvent(EVNT_RADIO_TIMEOUT);
    } else if (RADIO_RxPacket.u8Status == SMAC1_SUCCESS) { /* good packet received: handle it. */
      (void)RMSG_QueuePut(RADIO_RxPacket.pu8Data-RPHY_BUF_IDX_PAYLOAD, RPHY_BUFFER_SIZE, RADIO_RxPacket.u8DataLength, TRUE, FALSE);
      EVNT_SetEvent(EVNT_RADIO_DATA);
    } else if (RADIO_RxPacket.u8Status==SMAC1_OVERFLOW) { /* received packet, but it was longer than what we expect. */
      EVNT_SetEvent(EVNT_RADIO_OVERFLOW);
    } else if (RADIO_RxPacket.u8Status==SMAC1_RESET) {
      EVNT_SetEvent(EVNT_RADIO_RESET); /* MC13192 reset, re-initialize.*/
    } else { /* something unknown? */
      EVNT_SetEvent(EVNT_RADIO_UNKNOWN);
    }
  }
}

/*!
 * \brief Sets the channel number to be used
 * \param ch The channel to be used, in the range 0..15
 */
static void RADIO_SetChannel(uint8_t ch) {
  RADIO_Channel = ch&0xF; /* make sure it remains in range 0..15 */
  (void)SMAC1_MLMESetChannelRequest(RADIO_Channel);  /* Set channel */
}

/*!
 * \brief Sets the channel number to be used
 * \param power The channel to be used, in the range 0..15
 */
static void RADIO_SetOutputPower(uint8_t power) {
  RADIO_OutputPower = power&0xF; /* make sure it remains in range 0..15 */
  (void)SMAC1_MLMEMC13192PAOutputAdjust(RADIO_OutputPower); /* Set output power setting */
}

static void RADIO_InitRadio(void) {
  RADIO_isSniffing = FALSE;
  RADIO_isOn = TRUE;
  TRSVR1_Init(); /* init transceiver and get it out of reset */
  SMAC1_RadioInit();
  
  (void)SMAC1_MLMESetMC13192ClockRate(0);    /* Set initial Clock speed from transceiver (CLKO)*/
  RADIO_SetChannel(RADIO_Channel);           /* Set channel */
  RADIO_SetOutputPower(RADIO_OutputPower);   /* Set output power */

  /* Initialize the packet */
  RADIO_TxPacket.u8DataLength = 0;               /* Set TX default length to 0 */
  RADIO_TxPacket.pu8Data = &RADIO_TxDataBuffer[RPHY_BUF_IDX_PAYLOAD]; /* Load the address of our txbuffer into the tx structure */

  RADIO_RxPacket.u8DataLength = 0;               /* Set RX default to 0*/
  RADIO_RxPacket.pu8Data = &RADIO_RxDataBuffer[RPHY_BUF_IDX_PAYLOAD];  /* Load the address of our rxbuffer into rx structure */
  RADIO_RxPacket.u8MaxDataLength = SMAC1_RADIO_BUF_SIZE; /* Define the max buffer we are interested in */
  RADIO_RxPacket.u8Status = TRSVR1_INITIAL_VALUE;  /* initialize the status packet to 0 */

  RADIO_AppStatus = RADIO_INITIAL_STATE;        /* Set the initial status of the application state variable */

  /* Initialize Rx/Tx descriptor */
  radioRx.data = &radioRxBuf[0];
  radioRx.dataSize = sizeof(radioRxBuf);
  radioTx.data = &radioTxBuf[0];
  radioTx.dataSize = sizeof(radioTxBuf);
}

static const unsigned char *RadioStateStr(RADIO_AppStatusKind state) {
  switch(state) {
    case RADIO_INITIAL_STATE:         return (const unsigned char*)"INITIAL";
    case RADIO_RESET_STATE:           return (const unsigned char*)"RESET";
    case RADIO_RECEIVER_ALWAYS_ON:    return (const unsigned char*)"ALWAYS_ON";
    case RADIO_TRANSMIT_DATA:         return (const unsigned char*)"TRANSMIT_DATA";
    case RADIO_WAIT_FOR_ACK:          return (const unsigned char*)"WAIT_FOR_ACK"; 
    case RADIO_READY_FOR_TX_RX_DATA:  return (const unsigned char*)"READY_TX_RX"; 
    default:                          return (const unsigned char*)"UNKNOWN";
  }
}

static void RADIO_SniffPacket(RPHY_PacketDesc *packet, bool isTx) {
#if PL_HAS_SHELL
  uint8_t buf[32];
  const CLS1_StdIOType *io;
  int i;
  uint8_t dataSize;
  
  if (!RADIO_isSniffing) {
    return;
  }
  io = CLS1_GetStdio();
  if (isTx) {
    UTIL1_strcpy(buf, sizeof(buf),(unsigned char*)"Radio Tx: ");
  } else {
    UTIL1_strcpy(buf, sizeof(buf),(unsigned char*)"Radio Rx: ");
  }
  CLS1_SendStr(buf, io->stdOut);
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"ch #:");
  UTIL1_strcatNum16s(buf, sizeof(buf), RADIO_Channel);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" flags: ");
  UTIL1_strcatNum16s(buf, sizeof(buf), packet->flags);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" data size: ");
  UTIL1_strcatNum16s(buf, sizeof(buf), packet->dataSize);
  CLS1_SendStr(buf, io->stdOut);
  /* write as hex */
  buf[0] = '\0';
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" hex: ");
  CLS1_SendStr(buf, io->stdOut);
  dataSize = packet->data[0]; /* first byte in data buffer is number of bytes */
  for(i=0; i<dataSize;i++) {
    buf[0] = '\0';
    UTIL1_strcatNum8Hex(buf, sizeof(buf), packet->data[i]);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" ");
    CLS1_SendStr(buf, io->stdOut);
  }
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStr(buf, io->stdOut);
#endif
}

/*!
 \brief A simple state machine iterating through different transceiver states
 */
static void RADIO_HandleStateMachine(void) {
  byte res;

  for(;;) { /* will break/return */
    switch (RADIO_AppStatus) {
      case RADIO_INITIAL_STATE:
        RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
        break;
        
      case RADIO_RESET_STATE:
          /* MC13192 Reset, reinitialize and return to default state. */
          RADIO_InitRadio();
          RADIO_AppStatus = RADIO_INITIAL_STATE;
          break;
  
      case RADIO_RECEIVER_ALWAYS_ON:
        RADIO_AppStatus = RADIO_READY_FOR_TX_RX_DATA;
        (void)SMAC1_MLMERXEnableRequest(0); /* Zero means wait forever with RX ON. */
        return;
  
      case RADIO_READY_FOR_TX_RX_DATA: /* we are ready to receive/send data data */
        return;
  
      case RADIO_TRANSMIT_DATA:
        res = SMAC1_MLMERXDisableRequest(); /* turn RX receiver off */
        if (res != SMAC1_SUCCESS) { /* Turn off the RX forever mode. */
          RADIO_AppStatus = RADIO_TRANSMIT_DATA; /* retry */
          break;
        }       
        res = SMAC1_MCPSDataRequest(&RADIO_TxPacket); /* send data */
#if RNET_CONFIG_USE_ACK
        if (res == SMAC1_SUCCESS) { /* transmitting data was ok */
          if (RMAC_GetType(RADIO_TxPacket.pu8Data-RPHY_BUF_IDX_PAYLOAD, 0)==RMAC_MSG_TYPE_ACK) {
            RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* we have sent ACK, go back to receiving mode */
          } else {
            RADIO_AppStatus = RADIO_WAIT_FOR_ACK;
            (void)SMAC1_MLMERXEnableRequest(RADIO_TIMEOUT_COUNT); /* turn RX receiver on with timeout for ack */
          }
        } else {
          RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* what could we otherwise do? */
        }
#else
        RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
#endif
        break;

      case RADIO_WAIT_FOR_ACK:
        /* At this point only two things happen, 1-we receive the ack packet or 2-timeout.
          * Either way the TX will leave this state and continue. Low power mode could be placed here
          * because both 1 and 2 are interrupt driven, in this case we keep it simple
          */
        return;
  
      default:
        return;
    } /* switch */
  } /* for */
}

void RADIO_AppHandleEvent(EVNT_Handle event) {
  /*! \todo You might disable later some of the messages. */
  switch(event) {
    case EVNT_RADIO_RESET: /* radio transceiver has reset */
#if PL_HAS_SHELL
      CLS1_SendStr((unsigned char*)"RADIO reset\r\n", CLS1_GetStdio()->stdOut);
#endif
      RADIO_AppStatus = RADIO_RESET_STATE;
      break;
    case EVNT_RADIO_TIMEOUT: /* packet sent was causing timeout */
#if PL_HAS_SHELL
      CLS1_SendStr((unsigned char*)"RADIO timeout\r\n", CLS1_GetStdio()->stdOut);
#endif
      RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
      break;
    case EVNT_RADIO_OVERFLOW: /* packet received was too long */
#if PL_HAS_SHELL
      CLS1_SendStr((unsigned char*)"RADIO overflow\r\n", CLS1_GetStdio()->stdOut);
#endif
      RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
      break;
    case EVNT_RADIO_DATA: /* data received */
#if PL_HAS_SHELL
      //CLS1_SendStr((unsigned char*)"RADIO rx\r\n", CLS1_GetStdio()->stdOut);
#endif
      RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
      break;
    case EVNT_RADIO_ACK: /* ack received */
#if PL_HAS_SHELL
      CLS1_SendStr((unsigned char*)"RADIO ack\r\n", CLS1_GetStdio()->stdOut);
#endif
      RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
      break;
    case EVNT_RADIO_UNKNOWN: /* unknown package received */
#if PL_HAS_SHELL
      CLS1_SendStr((unsigned char*)"RADIO unknown\r\n", CLS1_GetStdio()->stdOut);
#endif
      RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
      break;
    default:
      break;
  } /* switch */
}

static uint8_t RADIO_CheckTx(RPHY_PacketDesc *packet) {
  uint8_t size, i, *p;
  
  if (RMSG_GetTxMsg(packet->data, packet->dataSize)==ERR_OK) {
    size = packet->data[RPHY_BUF_IDX_SIZE]; /* first byte in msg queue is size of message itself */
    p = &packet->data[RPHY_BUF_IDX_PAYLOAD]; /* pointer to start of data to transmit: starting with type field */
    i = RPHY_BUF_IDX_PAYLOAD; /* start copy from here */
    while(i<sizeof(RADIO_TxDataBuffer) && size>0) {
      RADIO_TxDataBuffer[i] = *p;
      size--; i++;
      p++;
    }
    if (size!=0) { /* not enough room in transmit buffer */
      return ERR_OVERFLOW;
    }
    RADIO_TxPacket.pu8Data = &RADIO_TxDataBuffer[RPHY_BUF_IDX_PAYLOAD];  /* Load the address of our txbuffer into tx structure.*/
    RADIO_TxPacket.u8DataLength = i-RPHY_BUF_IDX_PAYLOAD; /* Set the data length of the packet */
    RADIO_AppStatus = RADIO_TRANSMIT_DATA;
    RADIO_SniffPacket(packet, TRUE); /* sniff outgoing packet */
    return ERR_OK;
  } else {
    return ERR_FAILED; /* no data to send? */
  }
  return ERR_OK;
}

/*! \brief Send outgoing packets */
static uint8_t RADIO_ProcessTx(RPHY_PacketDesc *packet) {
  /* check if we have to send out a message */
  if (RADIO_AppStatus == RADIO_READY_FOR_TX_RX_DATA) { /* we are ready to send data */
    return RADIO_CheckTx(packet); /* send any pending messages */
  }
  return ERR_OK;
}

uint8_t RADIO_Process(void) {
  uint8_t res;
  
  if (RADIO_isOn) { /* radio turned on? */
    RADIO_HandleStateMachine(); /* process state machine */
    (void)RADIO_ProcessTx(&radioTx); /* send outgoing packets (if any) */
    res = RPHY_GetPayload(&radioRx); /* get message */
    if (res==ERR_OK) { /* packet received */
      RADIO_SniffPacket(&radioRx, FALSE); /* sniff incoming packet */
      if (RPHY_OnPacketRx(&radioRx)==ERR_OK) { /* process incoming packets */
        if (radioRx.flags&RPHY_PACKET_FLAGS_ACK) { /* it was an ack! */
          EVNT_SetEvent(EVNT_RADIO_ACK); /* set event */
        }
      }
    }
  }
  return ERR_OK;
}

#if PL_HAS_SHELL
static void RADIO_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"radio", (unsigned char*)"Group of radio commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows radio help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  on|off", (unsigned char*)"Turns the radio on or off\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  sniff on|off", (unsigned char*)"Turns sniffing on or off\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  channel <number>", (unsigned char*)"Switches to the given channel. Channel must be in the range 0..15\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  power <number>", (unsigned char*)"Changes the output power. Power must be in the range 0..15\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  reset", (unsigned char*)"Reset transceiver\r\n", io->stdOut);
}

static void RADIO_PrintStatus(const CLS1_StdIOType *io) {
  short dBm;
  unsigned char link_quality;  /* Holds the link quality of the last received Packet.*/

  CLS1_SendStatusStr((unsigned char*)"Radio", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  on", RADIO_isOn?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  sniff", RADIO_isSniffing?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  link_quality = SMAC1_MLMELinkQuality();  /* Read the link quality of the last received packet.*/
  dBm = (short)(-(link_quality/2));
  CLS1_SendStatusStr((unsigned char*)"  LQ", (unsigned char*)"", io->stdOut); 
  CLS1_SendNum16s(dBm, io->stdOut); 
  CLS1_SendStr((unsigned char*)" dBm\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  channel", (unsigned char*)"", io->stdOut); 
  CLS1_SendNum16u((uint16_t)RADIO_Channel, io->stdOut); 
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  outputPower", (unsigned char*)"", io->stdOut); 
  CLS1_SendNum16u((uint16_t)RADIO_OutputPower, io->stdOut); 
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  state", RadioStateStr(RADIO_AppStatus), io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
}

uint8_t RADIO_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  int32_t val;
  const unsigned char *p;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"radio help")==0) {
    RADIO_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"radio status")==0) {
    RADIO_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"radio reset")==0) {
    RADIO_AppStatus = RADIO_RESET_STATE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"radio on")==0) {
    RADIO_isOn = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"radio off")==0) {
    RADIO_isOn = FALSE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"radio sniff on")==0) {
    RADIO_isSniffing = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"radio sniff off")==0) {
    RADIO_isSniffing = FALSE;
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, (char*)"radio channel", sizeof("radio channel")-1)==0) {
    p = cmd+sizeof("radio channel");
    if (UTIL1_xatoi(&p, &val)==ERR_OK && val>=0 && val<=15) {
      RADIO_SetChannel((uint8_t)val);
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument, must be in the range 0..15\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, "radio power", sizeof("radio power")-1)==0) {
    p = cmd+sizeof("radio power");
    if (UTIL1_xatoi(&p, &val)==ERR_OK && val>=0 && val<=15) {
      RADIO_SetOutputPower((uint8_t)val);
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument, must be in the range 0..15\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  }
  return res;
}
#endif /* PL_HAS_SHELL */

uint8_t RADIO_PowerUp(void){
  /* nothing special to do */
  return ERR_OK;
}

void RADIO_Deinit(void) {
  /* nothing needed */
}

void RADIO_Init(void) {
  RADIO_InitRadio();
}
#endif

/**
 * \file
 * \brief Radio Module
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Implementation of the Radio module to handle everything around the radio transceiver
 */

#include "Platform.h"
#if PL_HAS_RADIO
#include "SMAC1.h"
#include "UTIL1.h"
#include "Radio.h"
#include "Event.h"
#if PL_HAS_LED
  #include "LED.h"
#endif
#if PL_IS_ROBOT
  #include "LEDG.h"
#endif
#include "CLS1.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#include "MyQueue.h"
#if PL_HAS_REMOTE
  #include "Remote.h"
#endif
#if PL_HAS_RTOS_TRACE
  #include "Ptrc1.h"
#endif

/* Radio state definitions */
typedef enum RADIO_AppStatusKind {
  RADIO_INITIAL_STATE,
  RADIO_RESET_STATE,
  RADIO_RECEIVER_ALWAYS_ON,
  RADIO_TRANSMIT_DATA,
  RADIO_WAITING_FOR_ACK,
  RADIO_TRANSMIT_ACK,
  RADIO_READY_FOR_TX_RX_DATA
} RADIO_AppStatusKind;

#define RADIO_QUEUE_DATA_SIZE    SMAC1_RADIO_BUF_SIZE /* number of data bytes in radio tx/rx queue */

#define RADIO_QUEUE_RX_NOF_ITEMS  6 /* number of items in the queue */
#define RADIO_QUEUE_TX_NOF_ITEMS  6 /* number of items in the queue */
#define RADIO_QUEUE_ITEM_SIZE  (RADIO_QUEUE_DATA_SIZE+2) /* size of each queue item. x bytes for data as 1 byte for 'kind' plus 1 byte for size needed */
static xQueueHandle RADIO_MsgRxQueue, RADIO_MsgTxQueue; /* queue for messages,  format is: kind(8bit) dataSize(8bit) data */

typedef enum RADIO_QueueMsgKind {
  RADIO_QUEUE_MSG_GENERIC,/* generic message */
  RADIO_QUEUE_MSG_SNIFF,  /* sniffing message */
  RADIO_QUEUE_MSG_STDIN,  /* stdin message */
  RADIO_QUEUE_MSG_STDOUT, /* stdout message */
  RADIO_QUEUE_MSG_STDERR, /* stderr message */
  RADIO_QUEUE_MSG_ACCEL   /* acceleration message */
} RADIO_QueueMsgKind;

/*! \todo RADIO: Define here your PAN ID and acknowledge message you want to use */
#define RADIO_ACK_STR     "ack"      /* acknowledge string */
#define RADIO_STDIN_STR   "stdin "   /* stdio stdin string */
#define RADIO_STDOUT_STR  "stdout "  /* stdio stdout string */
#define RADIO_STDERR_STR  "stderr "  /* stdio stderr string */

#define RADIO_TIMEOUT_COUNT    0xB000 /*!< how long the timeout value will be while transmitting a message */

static RADIO_AppStatusKind RADIO_AppStatus = RADIO_INITIAL_STATE;
static uint8_t RADIO_Channel = 5;
static uint8_t RADIO_OutputPower = 15;
static bool RADIO_isOn = TRUE;
static bool RADIO_isSniffing = FALSE;

static tRxPacket RADIO_RxPacket;            /*!< SMAC structure for RX packets */
static uint8_t RADIO_RxDataBuffer[SMAC1_RADIO_BUF_SIZE]; /*!< Data buffer to hold RX data */

static tTxPacket RADIO_TxPacket;            /*!< SMAC structure for TX packets */
static uint8_t RADIO_TxDataBuffer[SMAC1_RADIO_BUF_SIZE]; /*!< Data buffer to hold TX data */

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
  TRSVR1_Init(); /* init transceiver and get it out of reset */
  SMAC1_RadioInit();
  
  (void)SMAC1_MLMESetMC13192ClockRate(0);    /* Set initial Clk speed from transceiver (CLKO)*/
  RADIO_SetChannel(RADIO_Channel);           /* Set channel */
  RADIO_SetOutputPower(15);                  /* Set output power */

  /*Initialize the packet */
  RADIO_TxPacket.u8DataLength = 0;               /* Set TX default length to 0 */
  RADIO_TxPacket.pu8Data = &RADIO_TxDataBuffer[0]; /* Load the address of our txbuffer into the tx structure */

  RADIO_RxPacket.u8DataLength = 0;               /* Set RX default to 0*/
  RADIO_RxPacket.pu8Data = &RADIO_RxDataBuffer[0];  /* Load the address of our rxbuffer into rx structure */
  RADIO_RxPacket.u8MaxDataLength = SMAC1_RADIO_BUF_SIZE; /* Define the max buffer we are interested in */
  RADIO_RxPacket.u8Status = TRSVR1_INITIAL_VALUE;  /* initialize the status packet to 0 */

  RADIO_AppStatus = RADIO_INITIAL_STATE;        /* Set the initial status of the application state variable */
}

static const unsigned char *RadioStateStr(RADIO_AppStatusKind state) {
  switch(state) {
    case RADIO_INITIAL_STATE:         return (const unsigned char*)"INITIAL";
    case RADIO_RESET_STATE:           return (const unsigned char*)"RESET";
    case RADIO_RECEIVER_ALWAYS_ON:    return (const unsigned char*)"ALWAYS_ON";
    case RADIO_TRANSMIT_DATA:         return (const unsigned char*)"TRANSMIT_DATA";
    case RADIO_WAITING_FOR_ACK:       return (const unsigned char*)"WAITING_FOR_ACK";
    case RADIO_TRANSMIT_ACK:          return (const unsigned char*)"TRANSMIT_ACK";
    case RADIO_READY_FOR_TX_RX_DATA:  return (const unsigned char*)"READY_TX_RX"; 
    default:                          return (const unsigned char*)"UNKNOWN";
  }
  return (const unsigned char*)"UNKNOWN";
}

/*!
 \brief A simple state machine iterating through different transceiver states
 */
static void RADIO_HandleState(void) {
  tTxPacket ackTxPacket;  /* SMAC structure for TX packets */
  static uint8_t ackTxDataBuffer[SMAC1_RADIO_BUF_SIZE];    /* Data buffer to hold TX data */
  byte res;

  for(;;) { /* will break/return */
    switch (RADIO_AppStatus) {
      case RADIO_INITIAL_STATE:
        RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
        break;
  
      case RADIO_RECEIVER_ALWAYS_ON:
        RADIO_AppStatus = RADIO_READY_FOR_TX_RX_DATA;
        (void)SMAC1_MLMERXEnableRequest(&RADIO_RxPacket, 0); /* Zero means wait forever with RX ON. */
        return;
  
      case RADIO_READY_FOR_TX_RX_DATA: /* we are ready to receive/send data data */
        return;
  
      case RADIO_TRANSMIT_DATA:
        res = SMAC1_MLMERXDisableRequest();
        if (res != SMAC1_SUCCESS) { /* Turn off the RX forever mode. */
          RADIO_AppStatus = RADIO_TRANSMIT_DATA; /* retry */
          break;
        }       
  #if PL_HAS_LED
        LED1_Neg();
  #endif
        res = SMAC1_MCPSDataRequest(&RADIO_TxPacket);
        if (res == SMAC1_SUCCESS) { /* transmit data */
          RADIO_AppStatus = RADIO_WAITING_FOR_ACK;
          (void)SMAC1_MLMERXEnableRequest(&RADIO_RxPacket, RADIO_TIMEOUT_COUNT);
        } else {
          RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* what should we otherwise do? */
        }
        break;
  
      case RADIO_TRANSMIT_ACK:
          /* Initialize the packet. */
          /*! \todo RADIO: Below we send back the acknowledge message:
           *        check that your RADIO_ACK_STR is what you want and need.
           *        Notice the implicit string concatenation for efficiency and reduced code size. */
          UTIL1_strcpy(ackTxDataBuffer, sizeof(ackTxDataBuffer), (unsigned char*)RADIO_PREFIX_STR RADIO_ACK_STR);
          ackTxPacket.pu8Data = &ackTxDataBuffer[0]; /* Load the address of our txbuffer into the tx structure*/
          ackTxPacket.u8DataLength = (byte)(UTIL1_strlen((char*)ackTxDataBuffer)+1); /* set the size of the packet */
          (void)SMAC1_MCPSDataRequest(&ackTxPacket); /* transmit data */
          RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
          break;
  
      case RADIO_RESET_STATE:
          /* MC13192 Reset, reinitialize and return to default state.   */
          RADIO_InitRadio();
          RADIO_AppStatus = RADIO_INITIAL_STATE;
          break;
  
      case RADIO_WAITING_FOR_ACK:
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
/*!
 * \brief This function gets called from the transceiver interrupt!
 */
static void QueueRadioRxMessage(RADIO_QueueMsgKind kind, const char *msg, uint8_t msgSize) {
  /* format is: kind(8bit) dataSize(8bit) data */
  uint8_t i, buf[RADIO_QUEUE_ITEM_SIZE];
  signed portBASE_TYPE pxHigherPriorityTaskWoken;

  buf[0] = kind;
  buf[1] = msgSize;
  i = 2;
  while(msgSize>0 && i<sizeof(buf)) {
    buf[i++] = *msg;
    msg++;
    msgSize--;
  }
  if (FRTOS1_xQueueSendToBackFromISR(RADIO_MsgRxQueue, &buf[0], &pxHigherPriorityTaskWoken)!=pdTRUE) {
    /* was not able to send to the queue. Well, not much we can do here... */
  }
}

static uint8_t QueueRadioTxMessage(const uint8_t *msg, uint8_t msgSize) {
  /* format is: kind(8bit) dataSize(8bit) data */
  uint8_t i, buf[RADIO_QUEUE_ITEM_SIZE];
  uint8_t res = ERR_OK;
  static uint8_t err_cnt = 0;

  buf[0] = RADIO_QUEUE_MSG_GENERIC;
  buf[1] = msgSize;
  i = 2;
  while(msgSize>0 && i<sizeof(buf)) {
    buf[i++] = *msg;
    msg++;
    msgSize--;
  }
  if (msgSize!=0) {
    res = ERR_OVERFLOW; /* not enough room in message! */
  }
  for(i=0;i<10;i++) { /* retry */
    if (FRTOS1_xQueueSendToBack(RADIO_MsgTxQueue, &buf[0], 250/portTICK_RATE_MS /*portMAX_DELAY*/)!=pdTRUE) {
      err_cnt++;
      res = ERR_BUSY;
    } else {
      res = ERR_OK;
      break; /* success! */
    }
  }
  return res;
}

void RADIO_DataIndicationPacket(tRxPacket *sRxPacket) {
  if (sRxPacket->u8Status==SMAC1_TIMEOUT) {      /* Put timeout condition code here */
#if PL_HAS_LED
    LED1_Neg(); LED2_Neg();  /* indicator for bad or no communication */
#endif
    EVNT_SetEvent(EVNT_RADIO_TIMEOUT);
  } else if (sRxPacket->u8Status == SMAC1_SUCCESS) { /* good packet received: handle it. */
    if (RADIO_isSniffing) {
      QueueRadioRxMessage(RADIO_QUEUE_MSG_SNIFF, (const char*)sRxPacket->pu8Data, sRxPacket->u8DataLength);
    }
    /* check if it is the packet we expect...*/
    if (   RADIO_AppStatus==RADIO_WAITING_FOR_ACK
        && UTIL1_strncmp((char*)sRxPacket->pu8Data, RADIO_PREFIX_STR RADIO_ACK_STR, sizeof(RADIO_PREFIX_STR RADIO_ACK_STR)-1)==0
       ) /* is it our acknowledge packet? */
    {
      EVNT_SetEvent(EVNT_RADIO_ACK);
    } else if (UTIL1_strncmp((char*)sRxPacket->pu8Data, RADIO_PREFIX_STR, sizeof(RADIO_PREFIX_STR)-1)==0) {
#if PL_HAS_REMOTE && PL_HAS_MOTOR
      /*! \todo Implement your own message handling */
      if (UTIL1_strncmp((char*)sRxPacket->pu8Data, RADIO_PREFIX_STR REMOTE_ACCEL_PREFIX, sizeof(RADIO_PREFIX_STR REMOTE_ACCEL_PREFIX)-1)==0) {
        QueueRadioRxMessage(RADIO_QUEUE_MSG_ACCEL, (const char*)sRxPacket->pu8Data, sRxPacket->u8DataLength);
      }
#endif
      if (UTIL1_strncmp((char*)sRxPacket->pu8Data, RADIO_PREFIX_STR RADIO_STDIN_STR, sizeof(RADIO_PREFIX_STR RADIO_STDIN_STR)-1)==0) {
        QueueRadioRxMessage(RADIO_QUEUE_MSG_STDIN, (const char*)sRxPacket->pu8Data+(sizeof(RADIO_PREFIX_STR RADIO_STDIN_STR)-1), sRxPacket->u8DataLength-sizeof(RADIO_PREFIX_STR RADIO_STDIN_STR)+1);
      } else if (UTIL1_strncmp((char*)sRxPacket->pu8Data, RADIO_PREFIX_STR RADIO_STDOUT_STR, sizeof(RADIO_PREFIX_STR RADIO_STDOUT_STR)-1)==0) {
        QueueRadioRxMessage(RADIO_QUEUE_MSG_STDOUT, (const char*)sRxPacket->pu8Data+(sizeof(RADIO_PREFIX_STR RADIO_STDOUT_STR)-1), sRxPacket->u8DataLength-sizeof(RADIO_PREFIX_STR RADIO_STDOUT_STR)+1);
      } else if (UTIL1_strncmp((char*)sRxPacket->pu8Data, RADIO_PREFIX_STR RADIO_STDERR_STR, sizeof(RADIO_PREFIX_STR RADIO_STDERR_STR)-1)==0) {
        QueueRadioRxMessage(RADIO_QUEUE_MSG_STDERR, (const char*)sRxPacket->pu8Data+(sizeof(RADIO_PREFIX_STR RADIO_STDERR_STR)-1), sRxPacket->u8DataLength-sizeof(RADIO_PREFIX_STR RADIO_STDERR_STR)+1);
      }
      EVNT_SetEvent(EVNT_RADIO_DATA);
    } else { /* unknown packet? */
      EVNT_SetEvent(EVNT_RADIO_UNKNOWN);
    }
  } else if (sRxPacket->u8Status==SMAC1_OVERFLOW) { /* received packet, but it was longer than what we expect. */
    EVNT_SetEvent(EVNT_RADIO_OVERFLOW);
#if PL_HAS_LED
    LED1_Neg(); LED2_Neg(); /* indicator for bad or no communication */
#endif
  }
}

void RADIO_ResetIndication(void) {
  EVNT_SetEvent(EVNT_RADIO_RESET);         /* MC13192 reset, re-initialize.*/
}

void RADIO_AppHandleEvent(EVNT_Handle event) {
  /*! \todo You might disable later some of the messages. */
  switch(event) {
    case EVNT_RADIO_RESET: /* radio transceiver has reset */
      QUEUE_SendString(QUEUE_StdOut, (unsigned char*)"RADIO reset\r\n");
      RADIO_AppStatus = RADIO_RESET_STATE;
      break;
    case EVNT_RADIO_TIMEOUT: /* packet sent was causing timeout */
      QUEUE_SendString(QUEUE_StdOut, (unsigned char*)"RADIO timeout\r\n");
      RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
      break;
    case EVNT_RADIO_ACK: /* acknowledge received */
     // QUEUE_SendMessage(QUEUE_StdOut, (unsigned char*)"RADIO rx ack\r\n");
      RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
      break;
    case EVNT_RADIO_OVERFLOW: /* packet received was too long */
      QUEUE_SendString(QUEUE_StdOut, (unsigned char*)"RADIO overflow\r\n");
      RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
      break;
    case EVNT_RADIO_DATA: /* data received */
     // QUEUE_SendString(QUEUE_StdOut, (unsigned char*)"RADIO rx data, going to tx ACK\r\n");
      RADIO_AppStatus = RADIO_TRANSMIT_ACK;
      break;
    case EVNT_RADIO_UNKNOWN: /* unknown package received */
      QUEUE_SendString(QUEUE_StdOut, (unsigned char*)"RADIO unknown\r\n");
      RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
      break;
    default:
      break;
  } /* switch */
}

uint8_t RADIO_SendData(const uint8_t *data, uint8_t dataSize) {
  if (!RADIO_isOn) {
    return ERR_DISABLED;
  }
  return QueueRadioTxMessage(data, dataSize);
}

static void RADIO_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"radio", (unsigned char*)"Group of radio commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows radio help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  on|off", (unsigned char*)"Turns the radio on or off\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  sniff on|off", (unsigned char*)"Turns packet sniffing on or off\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  channel <number>", (unsigned char*)"Switches to the given channel. Channel must be in the range 0..15\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  power <number>", (unsigned char*)"Changes the output power. Power must be in the range 0..15\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  send <string>", (unsigned char*)"Send a string using the wireless transceiver\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  send (stdin/out/err)", (unsigned char*)"Send a string to stdio using the wireless transceiver\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  reset", (unsigned char*)"Reset transceiver\r\n", io->stdOut);
}

static void RADIO_PrintStatus(const CLS1_StdIOType *io) {
  short dBm;
  unsigned char link_quality;  /* Holds the link quality of the last received Packet.*/

  CLS1_SendStatusStr((unsigned char*)"Radio", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  transceiver", RADIO_isOn?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  sniffing", RADIO_isSniffing?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
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
  CLS1_SendStatusStr((unsigned char*)"  PAIND", (unsigned char*)RADIO_PREFIX_STR, io->stdOut); 
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  ACK", (unsigned char*)RADIO_ACK_STR, io->stdOut); 
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  state", RadioStateStr(RADIO_AppStatus), io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
}

uint8_t RADIO_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  long val;
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
  } else if (UTIL1_strncmp((char*)cmd, (char*)"radio send", sizeof("radio send")-1)==0) {
    unsigned char buf[32];
    
    UTIL1_strcpy(buf, sizeof(buf), cmd+sizeof("radio send"));
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\n");
    buf[sizeof(buf)-1] = '\n'; /* have a '\n' in any case */
    if (RADIO_SendData(buf, (uint8_t)UTIL1_strlen((char*)buf))!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"failed!\r\n", io->stdErr);
    }
    *handled = TRUE;
  }
  return res;
}

/*!
  \brief This routine is called as callback by the radio driver on reception of a data packet
  \param msg Pointer to the message we received.
 */
static void RADIO_HandleMessage(uint8_t *msg) {
  unsigned char buf[32];
  uint8_t i, size;

  if (RADIO_isSniffing && *msg==RADIO_QUEUE_MSG_SNIFF) {
    msg++;
    size = *msg++;
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"\r\nch #:"); /* use new line at the beginning, as the hex dump at the end might be fill up buffer completely */
    UTIL1_strcatNum16s(buf, sizeof(buf), RADIO_Channel);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" size:");
    UTIL1_strcatNum16s(buf, sizeof(buf), size);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" ASCII: ");
    QUEUE_SendString(QUEUE_StdOut, buf);
    buf[0] = '\0';
    /* write as string */
    for(i=0;i<size && i<sizeof(buf);i++) {
      UTIL1_chcat(buf, sizeof(buf), msg[i]);
    }
    QUEUE_SendString(QUEUE_StdOut, buf);
    /* write as hex */
    buf[0] = '\0';
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" hex: ");
    for(i=0; i<size;i++) {
      UTIL1_strcatNum8Hex(buf, sizeof(buf), msg[i]);
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" ");
    }
    QUEUE_SendString(QUEUE_StdOut, buf);
    QUEUE_SendString(QUEUE_StdOut, (unsigned char*)"\r\n");
  } else if (*msg==RADIO_QUEUE_MSG_STDIN) {
    msg++; /* skip message kind */
    size = *msg++;
    QUEUE_SendData(QUEUE_StdIn, msg, size);
  } else if (*msg==RADIO_QUEUE_MSG_STDOUT) {
    msg++; /* skip message kind */
    size = *msg++;
    QUEUE_SendData(QUEUE_StdOut, msg, size);
  } else if (*msg==RADIO_QUEUE_MSG_STDERR) {
    msg++; /* skip message kind */
    size = *msg++;
    QUEUE_SendData(QUEUE_StdErr, msg, size);
#if PL_HAS_REMOTE && PL_HAS_MOTOR
  /*! \todo Implement handling for your remote control */
  } else if (*msg==RADIO_QUEUE_MSG_ACCEL) {
    msg++; /* skip message kind */
    size = *msg++;
    REMOTE_ParseMsg((const unsigned char*)msg+sizeof(RADIO_PREFIX_STR)-1, size-sizeof(RADIO_PREFIX_STR)-1);
#endif
  }
}

/*! \brief Radio application state machine */
uint8_t RADIO_Handle(void) {
  uint8_t buf[RADIO_QUEUE_ITEM_SIZE];
  uint8_t size, i, *p;
  static byte cnt = 0;
  uint8_t res =  ERR_OK;

  if (RADIO_isOn) {
    RADIO_HandleState(); /* advance state machine */
  }
  /* poll radio message queue */
  if (FRTOS1_xQueueReceive(RADIO_MsgRxQueue, buf, 0)==pdPASS) {
    /* received message from queue */
    RADIO_HandleMessage(buf);
#if PL_IS_ROBOT
    LEDG_Neg();
    LEDR_Off();
#endif
    cnt = 0; /* reset counter */
  } else {
    cnt++; /* incremented every 10 ms */
  }
#if PL_APP_ACCEL_CONTROL && PL_IS_ROBOT
  if (cnt>100) { /* no message for more than 1 s? */
    cnt = 0;
    LEDG_Off();
    LEDR_Off();
    REMOTE_ParseMsg((const unsigned char *)"xyz 0 0 0", sizeof("xyz 0 0 0")-1); /* shut down motors */
    //EVNT_SetEvent(EVNT_RADIO_RESET); /* reset Transceiver */
  } else if (cnt==50) {
    LEDR_Neg();
  }
#endif
  /* check if we have to send out a message */
  if (RADIO_AppStatus == RADIO_READY_FOR_TX_RX_DATA) { /* we are ready to send data */
    if (FRTOS1_xQueueReceive(RADIO_MsgTxQueue, buf, 0)==pdPASS) {
      size = buf[1];
      p = &buf[2];
      UTIL1_strcpy(RADIO_TxDataBuffer, sizeof(RADIO_TxDataBuffer), (unsigned char*)RADIO_PREFIX_STR);
      i = sizeof(RADIO_PREFIX_STR)-1; /* index pointing after prefix */
      while(i<sizeof(RADIO_TxDataBuffer) && size>0) {
        RADIO_TxDataBuffer[i] = *p;
        size--; i++;
        p++;
      }
      if (size!=0) {
        /* not enough room in transmit buffer */
        res = ERR_OVERFLOW;
      }
      RADIO_TxPacket.pu8Data = &RADIO_TxDataBuffer[0];  /* Load the address of our txbuffer into tx structure.*/
      RADIO_TxPacket.u8DataLength = i; /* Set the data length of the packet */
      RADIO_AppStatus = RADIO_TRANSMIT_DATA;
      RADIO_HandleState(); /* advance state machine */
    }
  }
  return res;
}

void RADIO_Deinit(void) {
  /* nothing needed */
}

void RADIO_Init(void) {
  RADIO_InitRadio();
  /* create data queues */
  RADIO_MsgRxQueue = FRTOS1_xQueueCreate(RADIO_QUEUE_RX_NOF_ITEMS, RADIO_QUEUE_ITEM_SIZE);
#if PL_HAS_RTOS_TRACE
  Ptrc1_vTraceSetQueueName(RADIO_MsgRxQueue, "RadioRxMsg");
#endif
  if (RADIO_MsgRxQueue==NULL) { /* queue creation failed! */
    for(;;) {} /* not enough memory? */
  }
  RADIO_MsgTxQueue = FRTOS1_xQueueCreate(RADIO_QUEUE_TX_NOF_ITEMS, RADIO_QUEUE_ITEM_SIZE);
#if PL_HAS_RTOS_TRACE
  Ptrc1_vTraceSetQueueName(RADIO_MsgTxQueue, "RadioTxMsg");
#endif
  if (RADIO_MsgTxQueue==NULL) { /* queue creation failed! */
    for(;;) {} /* not enough memory? */
  }
}
#endif

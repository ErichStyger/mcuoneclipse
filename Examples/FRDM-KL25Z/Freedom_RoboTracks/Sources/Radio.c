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
#include "LEDG.h"
#include "CLS1.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#include "Shell.h"
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

#define RADIO_QUEUE_NOF_ITEMS  8 /* number of items in the queue */
#define RADIO_QUEUE_ITEM_SIZE  32 /* size of each queue item */
static xQueueHandle RADIO_MsgQueue; /* queue for messages,  format is: kind(8bit) dataSize(8bit) data */

typedef enum RADIO_QueueMsgKind {
  RADIO_QUEUE_MSG_SNIFF, /* sniffing message */
  RADIO_QUEUE_MSG_ACCEL  /* acceleration message */
} RADIO_QueueMsgKind;

/*! \todo RADIO: Define here your PAN ID and acknowledge message you want to use */
#define RADIO_PREFIX_STR "EST"   /* prefix used for every message */
#define RADIO_ACK_STR    "ack"   /* acknowledge string */

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

static void RADIO_InitTransceiver(void) {
  (void)SMAC1_MLMESetMC13192ClockRate(0);    /* Set initial Clk speed from transceiver (CLKO)*/
  RADIO_SetChannel(RADIO_Channel);           /* Set channel */
  RADIO_SetOutputPower(15);                  /* Set output power */

  /*Initialize the packet */
  RADIO_TxPacket.u8DataLength = 0;               /* Set TX default length to 0 */
  RADIO_TxPacket.pu8Data = &RADIO_TxDataBuffer[0]; /* Load the address of our txbuffer into the tx structure */

  RADIO_RxPacket.u8DataLength = 0;               /* Set RX default to 0*/
  RADIO_RxPacket.pu8Data = &RADIO_RxDataBuffer[0];  /* Load the address of our rxbuffer into rx structure */
  RADIO_RxPacket.u8MaxDataLength = 24;           /* Define the max buffer we are interested in */
  RADIO_RxPacket.u8Status = TRSVR1_INITIAL_VALUE;  /* initialize the status packet to 0 */

  RADIO_AppStatus = RADIO_INITIAL_STATE;        /* Set the initial status of the application state variable */
}

/*!
 \brief A simple state machine iterating through different transceiver states
 */
static void RADIO_HandleState(void) {
  tTxPacket ackTxPacket;  /* SMAC structure for TX packets   */
  static uint8_t ackTxDataBuffer[SMAC1_RADIO_BUF_SIZE];    /*Data buffer to hold TX data */

  switch (RADIO_AppStatus) {
    case RADIO_INITIAL_STATE:
        RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
        break;

    case RADIO_RECEIVER_ALWAYS_ON:
        RADIO_AppStatus = RADIO_READY_FOR_TX_RX_DATA;
        (void)SMAC1_MLMERXEnableRequest(&RADIO_RxPacket, 0); /* Zero means wait forever with RX ON. */
        break;

    case RADIO_READY_FOR_TX_RX_DATA: /* we are ready to receive/send data data */
        break;

    case RADIO_TRANSMIT_DATA:
        if (SMAC1_MLMERXDisableRequest() != SMAC1_SUCCESS) { /* Turn off the RX forever mode. */
          RADIO_AppStatus = RADIO_TRANSMIT_DATA; /* retry */
          break;
        }
#if PL_HAS_LED
        LED1_Neg();
#endif
        if ((SMAC1_MCPSDataRequest(&RADIO_TxPacket) == SMAC1_SUCCESS)) { /* transmit data */
          RADIO_AppStatus = RADIO_WAITING_FOR_ACK;
          (void)SMAC1_MLMERXEnableRequest(&RADIO_RxPacket, RADIO_TIMEOUT_COUNT);
        } else {
          RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* what should we otherwise do? */
        }
        break;

    case RADIO_TRANSMIT_ACK:
        /*Initialize the packet.*/
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
        TRSVR1_Init();
        SMAC1_RadioInit();
        RADIO_InitTransceiver();
        RADIO_AppStatus = RADIO_INITIAL_STATE;
        break;

    case RADIO_WAITING_FOR_ACK:
        /* At this point only two things happen, 1-we receive the ack packet or 2-timeout.
         * Either way the TX will leave this state and continue. Low power mode could be placed here
         * because both 1 and 2 are interrupt driven, in this case we keep it simple
         */
        break;

    default:
        break;
  }
}

static void QueueMessage(uint8_t kind, const char *msg, uint8_t msgSize) {
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
  if (FRTOS1_xQueueSendToBackFromISR(RADIO_MsgQueue, &buf[0], &pxHigherPriorityTaskWoken)!=pdTRUE) {
    /* was not able to send to the queue. Well, not much we can do here... */
  }
}


void RADIO_DataIndicationPacket(tRxPacket *sRxPacket) {
  if (sRxPacket->u8Status==SMAC1_TIMEOUT) {      /* Put timeout condition code here */
#if PL_HAS_LED
    LED1_Neg(); LED2_Neg();  /* indicator for bad or no communication */
#endif
    EVNT_SetEvent(EVNT_RADIO_TIMEOUT);
  } else if (sRxPacket->u8Status == SMAC1_SUCCESS) { /* good packet received: handle it. */
    if (RADIO_isSniffing) {
      QueueMessage(RADIO_QUEUE_MSG_SNIFF, (const char*)sRxPacket->pu8Data, sRxPacket->u8DataLength);
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
        QueueMessage(RADIO_QUEUE_MSG_ACCEL, (const char*)sRxPacket->pu8Data, sRxPacket->u8DataLength);
      }
#endif
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
      SHELL_SendString((unsigned char*)"RADIO reset\r\n");
      RADIO_AppStatus = RADIO_RESET_STATE;
      break;
    case EVNT_RADIO_TIMEOUT: /* packet sent was causing timeout */
      SHELL_SendString((unsigned char*)"RADIO timeout\r\n");
      RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
      break;
    case EVNT_RADIO_ACK: /* acknowledge received */
      SHELL_SendString((unsigned char*)"RADIO rx ack\r\n");
      RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
      break;
    case EVNT_RADIO_OVERFLOW: /* packet received was too long */
      SHELL_SendString((unsigned char*)"RADIO overflow\r\n");
      RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
      break;
    case EVNT_RADIO_DATA: /* data received */
      //SHELL_SendString((unsigned char*)"RADIO rx data, going to tx ACK\r\n");
      RADIO_AppStatus = RADIO_TRANSMIT_ACK;
      break;
    case EVNT_RADIO_UNKNOWN: /* unknown package received */
      SHELL_SendString((unsigned char*)"RADIO unknown\r\n");
      RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON;
      break;
    default:
      break;
  } /* switch */
}

void RADIO_SendData(const uint8_t *data, uint8_t dataSize) {
  if (!RADIO_isOn) {
    return;
  }
  while (RADIO_AppStatus != RADIO_READY_FOR_TX_RX_DATA) { /* we are not ready yet! */
    RADIO_HandleState(); /* advance state machine */
  }
  if (dataSize>sizeof(RADIO_TxDataBuffer)) {
    dataSize = sizeof(RADIO_TxDataBuffer); /* avoid buffer overflow */
  }
  (void)memcpy((char*)RADIO_TxDataBuffer, data, dataSize);
  RADIO_TxPacket.pu8Data = &RADIO_TxDataBuffer[0];            /* Load the address of our txbuffer into tx structure.*/
  RADIO_TxPacket.u8DataLength = dataSize; /* Set the data length of the packet */
  RADIO_AppStatus = RADIO_TRANSMIT_DATA;
  RADIO_HandleState(); /* advance state machine */
}

/*!
 * \brief Sends a data packet trough the Radio
 * \param[in] data Data to be sent (binary), zero terminated
*/
void RADIO_SendString(const unsigned char *data) {
  if (!RADIO_isOn) {
    return;
  }
  while (RADIO_AppStatus != RADIO_READY_FOR_TX_RX_DATA) { /* we are not ready yet! */
    RADIO_HandleState(); /* advance state machine */
  }
  UTIL1_strcpy(RADIO_TxDataBuffer, sizeof(RADIO_TxDataBuffer), (unsigned char*)RADIO_PREFIX_STR);
  UTIL1_strcat(RADIO_TxDataBuffer, sizeof(RADIO_TxDataBuffer), data);
  RADIO_TxPacket.pu8Data = &RADIO_TxDataBuffer[0];            /* Load the address of our txbuffer into tx structure.*/
  RADIO_TxPacket.u8DataLength = (byte)(UTIL1_strlen((char*)RADIO_TxDataBuffer)+1); /* Set the data length of the packet */
  RADIO_AppStatus = RADIO_TRANSMIT_DATA;
  RADIO_HandleState(); /* advance state machine */
}

static void RADIO_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"radio", (unsigned char*)"Group of radio commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows radio help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  on|off", (unsigned char*)"Turns the radio on or off\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  sniff on|off", (unsigned char*)"Turns packet sniffing on or off\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  channel <number>", (unsigned char*)"Switches to the given channel. Channel must be in the range 0..15\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  power <number>", (unsigned char*)"Changes the output power. Power must be in the range 0..15\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  send <string>", (unsigned char*)"Send a string using the wireless transceiver\r\n", io->stdOut);
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
    p = cmd+sizeof("radio send");
    RADIO_SendString(p);
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
    SHELL_SendString(buf);
    buf[0] = '\0';
    /* write as string */
    for(i=0;i<size && i<sizeof(buf);i++) {
      UTIL1_chcat(buf, sizeof(buf), msg[i]);
    }
    SHELL_SendString(buf);
    /* write as hex */
    buf[0] = '\0';
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" hex: ");
    for(i=0; i<size;i++) {
      UTIL1_strcatNum8Hex(buf, sizeof(buf), msg[i]);
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" ");
    }
    SHELL_SendString(buf);
    SHELL_SendString((unsigned char*)"\r\n");
#if PL_HAS_REMOTE && PL_HAS_MOTOR
  /*! \todo Implement handling for your remote control */
  } else if (*msg==RADIO_QUEUE_MSG_ACCEL) {
    msg++;
    size = *msg++;
    REMOTE_ParseMsg((const unsigned char*)msg+sizeof(RADIO_PREFIX_STR)-1, size-sizeof(RADIO_PREFIX_STR)-1);
#endif
  }
}

/*! \brief Radio application state machine */
void RADIO_Handle(void) {
  uint8_t buf[RADIO_QUEUE_ITEM_SIZE];
  static uint8_t cnt = 0;

  if (RADIO_isOn) {
    RADIO_HandleState(); /* advance state machine */
  }
  /* poll radio message queue */
  if (FRTOS1_xQueueReceive(RADIO_MsgQueue, buf, 0)==pdPASS) {
    /* received message from queue */
    RADIO_HandleMessage(buf);
    LEDG_Neg();
    LEDR_Off();
    cnt = 0; /* reset counter */
  } else {
    cnt++; /* incremented every 10 ms */
  }
  if (cnt>100) { /* no message for more than 1 s? */
    cnt = 0;
    LEDG_Off();
    LEDR_Off();
    REMOTE_ParseMsg((const unsigned char *)"xyz 0 0 0", sizeof("xyz 0 0 0")-1);
  } else if (cnt==50) {
    LEDR_Neg();
  }
}

void RADIO_Deinit(void) {
  /* nothing needed */
}

void RADIO_Init(void) {
  RADIO_InitTransceiver();
  /* create data queue */
  RADIO_MsgQueue = FRTOS1_xQueueCreate(RADIO_QUEUE_NOF_ITEMS, RADIO_QUEUE_ITEM_SIZE);
#if PL_HAS_RTOS_TRACE
  Ptrc1_vTraceSetQueueName(RADIO_MsgQueue, "RadioMsg");
#endif
  if (RADIO_MsgQueue==NULL) { /* queue creation failed! */
    for(;;) {} /* not enough memory? */
  }
}
#endif

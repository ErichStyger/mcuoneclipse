/**
 * \file
 * \brief This is main application file
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This module implements the application part of the program.
 */

#include "Platform.h"
#if PL_HAS_RADIO
#include "RNet_App.h"
#include "RStack.h"
#include "RApp.h"
#include "LED1.h"
#include "FRTOS1.h"
#include "Radio.h"
#if PL_HAS_RSTDIO
  #include "RStdIO.h"
#endif

static RNWK_ShortAddrType APP_dstAddr = RNWK_ADDR_BROADCAST; /* destination node address */

static uint8_t HandleRxMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet) {
#if PL_HAS_SHELL
  uint8_t buf[16];
  CLS1_ConstStdIOTypePtr io = CLS1_GetStdio();
#endif
  uint8_t val;
  
  (void)size;
  (void)packet;
  switch(type) {
    case RAPP_MSG_TYPE_DATA: /* <type><size><data */
      *handled = TRUE;
      val = *data; /* get data value */
#if PL_HAS_SHELL
      CLS1_SendStr((unsigned char*)"Data: ", io->stdOut);
      CLS1_SendNum8u(val, io->stdOut);
      CLS1_SendStr((unsigned char*)" from addr 0x", io->stdOut);
      buf[0] = '\0';
#if RNWK_SHORT_ADDR_SIZE==1
      UTIL1_strcatNum8Hex(buf, sizeof(buf), srcAddr);
#else
      UTIL1_strcatNum16Hex(buf, sizeof(buf), srcAddr);
#endif
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
      CLS1_SendStr(buf, io->stdOut);
#endif      
      return ERR_OK;
    default:
      break;
  } /* switch */
  return ERR_OK;
}

static void Err(unsigned char *msg) {
#if PL_HAS_SHELL
  CLS1_ConstStdIOTypePtr io = CLS1_GetStdio();
  
  CLS1_SendStr(msg, io->stdErr); /* print error message */
#else
  (void)msg; /* not used */
#endif
}

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if PL_HAS_RADIO
  RADIO_ParseCommand,
  RNWK_ParseCommand,
  RNETA_ParseCommand,
#endif
  NULL /* Sentinel */
};

static const RAPP_MsgHandler handlerTable[] = 
{
#if PL_HAS_RSTDIO
  RSTDIO_HandleStdioRxMessage,
#endif
  HandleRxMessage,
  NULL /* sentinel */
};

static portTASK_FUNCTION(RadioTask, pvParameters) {
  (void)pvParameters; /* not used */
  (void)RADIO_PowerUp();
  for(;;) {
    (void)RADIO_Process();
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

static portTASK_FUNCTION(MainTask, pvParameters) {
#if PL_HAS_SHELL
  static unsigned char localConsole_buf[48];
#endif
#if PL_HAS_RSTDIO
  static unsigned char radio_cmd_buf[48];
  CLS1_ConstStdIOType *ioRemote = RSTDIO_GetStdioRx();
#endif
#if PL_HAS_RSTDIO || PL_HAS_SHELL
  CLS1_ConstStdIOTypePtr ioLocal = CLS1_GetStdio();
#endif
  
#if PL_HAS_RSTDIO
  radio_cmd_buf[0] = '\0';
#endif
#if PL_HAS_SHELL
  localConsole_buf[0] = '\0';
  CLS1_SendStr((unsigned char*)"nRF24L01+ Demo\r\n", ioLocal->stdOut);
#endif
  RSTACK_Init(); /* initialize stack */
  if (RAPP_SetMessageHandlerTable(handlerTable)!=ERR_OK) { /* assign application message handler */
    Err((unsigned char*)"Failed setting message handler!\r\n");
  }
  if (RAPP_SetThisNodeAddr(RNWK_ADDR_BROADCAST)!=ERR_OK) { /* set a default address */
    Err((unsigned char*)"Failed setting source address!\r\n");
  }
#if PL_HAS_SHELL
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, ioLocal, CmdParserTable);
#endif
  for(;;) {
#if PL_HAS_SHELL
    (void)CLS1_ReadAndParseWithCommandTable(localConsole_buf, sizeof(localConsole_buf), ioLocal, CmdParserTable);
#endif
#if PL_HAS_RSTDIO
    RSTDIO_Print(ioLocal); /* handle stdout/stderr messages coming in */
    (void)CLS1_ReadAndParseWithCommandTable(radio_cmd_buf, sizeof(radio_cmd_buf), ioRemote, CmdParserTable);
#endif
    LED1_Neg();
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

void RNETA_Run(void) {
  if (FRTOS1_xTaskCreate(
        MainTask,  /* pointer to the task */
        (signed char *)"Main", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  if (FRTOS1_xTaskCreate(
        RadioTask,  /* pointer to the task */
        (signed char *)"Radio", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  FRTOS1_vTaskStartScheduler();
}

#if PL_HAS_SHELL
static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[32];
  
  CLS1_SendStatusStr((unsigned char*)"app", (unsigned char*)"\r\n", io->stdOut);
  
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
#if RNWK_SHORT_ADDR_SIZE==1
  UTIL1_strcatNum8Hex(buf, sizeof(buf), APP_dstAddr);
#else
  UTIL1_strcatNum16Hex(buf, sizeof(buf), APP_dstAddr);
#endif
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  dest addr", buf, io->stdOut);
  
  return ERR_OK;
}

static void PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"app", (unsigned char*)"Group of application commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows application help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  saddr 0x<addr>", (unsigned char*)"Set source node address\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  daddr 0x<addr>", (unsigned char*)"Set destination node address\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  send val <val>", (unsigned char*)"Set a value to the destination node\r\n", io->stdOut);
#if PL_HAS_RSTDIO
  CLS1_SendHelpStr((unsigned char*)"  send (in/out/err)", (unsigned char*)"Send a string to stdio using the wireless transceiver\r\n", io->stdOut);
#endif
}

uint8_t RNETA_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  const uint8_t *p;
  uint16_t val16;
  uint8_t val8;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"app help")==0) {
    PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"app status")==0) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strncmp((char*)cmd, (char*)"app saddr", sizeof("app saddr")-1)==0) {
    p = cmd + sizeof("app saddr")-1;
    *handled = TRUE;
    if (UTIL1_ScanHex16uNumber(&p, &val16)==ERR_OK) {
      (void)RNWK_SetThisNodeAddr((RNWK_ShortAddrType)val16);
    } else {
      CLS1_SendStr((unsigned char*)"ERR: wrong address\r\n", io->stdErr);
      return ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"app send val", sizeof("app send val")-1)==0) {
    p = cmd + sizeof("app send val")-1;
    *handled = TRUE;
    if (UTIL1_ScanDecimal8uNumber(&p, &val8)==ERR_OK) {
      if (RAPP_SendPayloadDataBlock(&val8, sizeof(val8), RAPP_MSG_TYPE_DATA, APP_dstAddr, RPHY_PACKET_FLAGS_REQ_ACK) != ERR_OK) {
        CLS1_SendStr((unsigned char*)"ERR: failed sending data\r\n", io->stdErr);
        return ERR_FAILED;
      }
    } else {
      CLS1_SendStr((unsigned char*)"ERR: wrong number format\r\n", io->stdErr);
      return ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"app daddr", sizeof("app daddr")-1)==0) {
    p = cmd + sizeof("app daddr")-1;
    *handled = TRUE;
    if (UTIL1_ScanHex16uNumber(&p, &val16)==ERR_OK) {
      APP_dstAddr = val16;
    } else {
      CLS1_SendStr((unsigned char*)"ERR: wrong address\r\n", io->stdErr);
      return ERR_FAILED;
    }
#if PL_HAS_RSTDIO
    } else if (UTIL1_strncmp((char*)cmd, (char*)"app send", sizeof("app send")-1)==0) {
    unsigned char buf[32];
    RSTDIO_QueueType queue;
    
    if (UTIL1_strncmp((char*)cmd, (char*)"app send in", sizeof("app send in")-1)==0) {
      queue = RSTDIO_QUEUE_TX_IN;
      cmd += sizeof("app send in");
    } else if (UTIL1_strncmp((char*)cmd, (char*)"app send out", sizeof("app send out")-1)==0) {
      queue = RSTDIO_QUEUE_TX_OUT;      
      cmd += sizeof("app send out");
    } else if (UTIL1_strncmp((char*)cmd, (char*)"app send err", sizeof("app send err")-1)==0) {
      queue = RSTDIO_QUEUE_TX_ERR;      
      cmd += sizeof("app send err");
    } else {
      return ERR_OK; /* not handled */
    }
    UTIL1_strcpy(buf, sizeof(buf), cmd);
    UTIL1_chcat(buf, sizeof(buf), '\n');
    buf[sizeof(buf)-2] = '\n'; /* have a '\n' in any case */
    if (RSTDIO_SendToTxStdio(queue, buf, UTIL1_strlen((char*)buf))!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"failed!\r\n", io->stdErr);
    }
    *handled = TRUE;
#endif
  }
  return res;
}
#endif /* PL_HAS_SHELL */

#endif /* PL_HAS_RADIO */


/**
 * \file
 * \brief This is main application file
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This module implements the application part of the program.
 */

#include "Platform.h"
#if PL_HAS_RADIO
#include "Application.h"
#include "RNet_App.h"
#include "RStack.h"
#include "RApp.h"
#include "FRTOS1.h"
#include "RPHY.h"
#include "Radio.h"
#if PL_HAS_RSTDIO
  #include "RStdIO.h"
#endif

#if PL_HAS_SHELL
static RNWK_ShortAddrType APP_dstAddr = RNWK_ADDR_BROADCAST; /* destination node address */
#endif

#define RADIO_CHANNEL_DATA    0  /* communication channel for read station */

typedef enum {
  RNETA_NONE,
  RNETA_POWERUP, /* powered up */
  RNETA_TX_RX,
  RNETA_DONE,
} RNETA_State;

static RNETA_State appState = RNETA_NONE;

static const RAPP_MsgHandler handlerTable[] = 
{
#if PL_HAS_RSTDIO
  RSTDIO_HandleStdioRxMessage,
#endif
  NULL /* sentinel */
};

void RNETA_Deinit(void) {
  /* nothing to do */
}

#if PL_HAS_SHELL
static unsigned char *StringForState(RNETA_State state) {
  switch(state) {
    case RNETA_NONE: return (unsigned char*)"NONE";
    case RNETA_POWERUP: return (unsigned char*)"POWERUP";
    case RNETA_TX_RX: return (unsigned char*)"TX_RX";
    default: return (unsigned char*)"UNKNOWN";
  }
}
#endif /* PL_HAS_SHELL */

static void RadioPowerUp(void) {
  /* need to ensure that we wait 100 ms after power-on of the transceiver */
  portTickType xTime;
  
  xTime = FRTOS1_xTaskGetTickCount();
  if (xTime<(100/portTICK_RATE_MS)) {
    /* not powered for 100 ms: wait until we can access the radio transceiver */
    xTime = (100/portTICK_RATE_MS)-xTime; /* remaining ticks to wait */
    FRTOS1_vTaskDelay(xTime);
  }
  (void)RADIO_PowerUp();
}

static void Process(void) {
  for(;;) {
    switch(appState) {
    case RNETA_NONE:
      appState = RNETA_POWERUP;
      continue;
      
    case RNETA_POWERUP:
      RadioPowerUp();
      (void)RADIO_SetChannel(RADIO_CHANNEL_DATA);
      appState = RNETA_TX_RX;
      break;
      
    case RNETA_TX_RX:
      (void)RADIO_Process();
      break;
  
    default:
      break;
    } /* switch */
    break; /* break for loop */
  } /* for */
}

static void Init(void) {
  if (RAPP_SetThisNodeAddr(RNWK_ADDR_BROADCAST)!=ERR_OK) { /* set a default address */
    APP_DebugPrint((unsigned char*)"ERR: Failed setting node address\r\n");
  }
}

static portTASK_FUNCTION(RNetTask, pvParameters) {
  (void)pvParameters; /* not used */
  Init();
  appState = RNETA_NONE;
  for(;;) {
    Process();
    FRTOS1_vTaskDelay(2/portTICK_RATE_MS);
  } /* for */
}

void RNETA_Init(void) {
  RSTACK_Init(); /* initialize stack */
  if (RAPP_SetMessageHandlerTable(handlerTable)!=ERR_OK) { /* assign application message handler */
    APP_DebugPrint((unsigned char*)"ERR: failed setting message handler!\r\n");
  }
  if (FRTOS1_xTaskCreate(
        RNetTask,  /* pointer to the task */
        "RNet", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+3,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}

#if PL_HAS_SHELL
static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[32];
  
  CLS1_SendStatusStr((unsigned char*)"app", (unsigned char*)"\r\n", io->stdOut);
  
  CLS1_SendStatusStr((unsigned char*)"  state", StringForState(appState), io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  
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
  CLS1_SendHelpStr((unsigned char*)"  help", (unsigned char*)"Shows radio help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  saddr 0x<addr>", (unsigned char*)"Set source node address\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  daddr 0x<addr>", (unsigned char*)"Set destination node address\r\n", io->stdOut);
#if PL_HAS_RSTDIO
  CLS1_SendHelpStr((unsigned char*)"  send (in/out/err)", (unsigned char*)"Send a string to stdio using the wireless transceiver\r\n", io->stdOut);
#endif
}

uint8_t RNETA_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  const uint8_t *p;
  uint16_t val16;

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

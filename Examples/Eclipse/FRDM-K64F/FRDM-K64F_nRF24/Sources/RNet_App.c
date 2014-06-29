/**
 * \file
 * \brief This is main application file
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This module implements the application part of the program.
 */

#include "RNet_App.h"
#include "RStack.h"
#include "RApp.h"
#include "FRTOS1.h"
#include "RPHY.h"
#include "Radio.h"

typedef enum {
  RNETA_NONE,
  RNETA_POWERUP, /* powered up */
  RNETA_TX_RX,
  RNETA_DONE,
} RNETA_State;

static RNETA_State appState = RNETA_NONE;

static const RAPP_MsgHandler handlerTable[] = 
{
#if 0
  RSTDIO_HandleStdioRxMessage,
#endif
  NULL /* sentinel */
};

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

static portTASK_FUNCTION(RNetTask, pvParameters) {
  (void)pvParameters; /* not used */
  if (RAPP_SetThisNodeAddr(RNWK_ADDR_BROADCAST)!=ERR_OK) { /* set a default address */
    for(;;); /* "ERR: Failed setting node address" */
  }
  appState = RNETA_NONE;
  for(;;) {
    Process();
    FRTOS1_vTaskDelay(2/portTICK_RATE_MS);
  } /* for */
}

void RNETA_Init(void) {
  RSTACK_Init(); /* initialize stack */
  if (RAPP_SetMessageHandlerTable(handlerTable)!=ERR_OK) { /* assign application message handler */
    for(;;); /* "ERR: failed setting message handler!" */
  }
  if (FRTOS1_xTaskCreate(
        RNetTask,  /* pointer to the task */
        "RNet", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}


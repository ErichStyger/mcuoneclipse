/**
 * \file
 * \brief This is main application file
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This module implements the application part of the program.
 */

#include "Platform.h"
#if PL_HAS_NRF24
#include "RNET1.h"
#include "Application.h"
#include "RNet_App.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "LED2.h"
#include "RStack.h"
#include "RApp.h"
#if PL_HAS_RSTDIO
  #include "RStdIO.h"
#endif

typedef enum {
  RNETA_NONE,
  RNETA_POWERUP, /* powered up */
  RNETA_TX_RX,
} RNETA_State;

static RNETA_State appState = RNETA_NONE;

static uint8_t RNETA_HandleRxMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet) {
  uint8_t val;
  
  (void)srcAddr;
  (void)packet;
  switch(type) {
    case RAPP_MSG_TYPE_DATA: /* <type><size><data */
      *handled = TRUE;
      val = *data; /* get data from packet */
      if (val==1) {
        LED1_Neg();
      } else if (val==2) {
        LED2_Neg();
      } else if (val==3) {
//        LED3_Neg();
      }
      return ERR_OK;
    default:
      break;
  } /* switch */
  return ERR_OK;
}

static const RAPP_MsgHandler handlerTable[] = 
{
#if PL_HAS_RSTDIO
  RSTDIO_HandleStdioRxMessage,
#endif
  RNETA_HandleRxMessage,
  NULL /* sentinel */
};

static void RadioPowerUp(void) {
  /* need to ensure that we wait 100 ms after power-on of the transceiver */
  TickType_t xTime;
  
  xTime = FRTOS1_xTaskGetTickCount();
  if (xTime<pdMS_TO_TICKS(100)) {
    /* not powered for 100 ms: wait until we can access the radio transceiver */
    xTime = pdMS_TO_TICKS(100)-xTime; /* remaining ticks to wait */
    FRTOS1_vTaskDelay(xTime);
  }
  (void)RNET1_PowerUp();
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
      (void)RNET1_Process();
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
    Process(); /* process radio in/out queues */
    vTaskDelay(pdMS_TO_TICKS(5));
  } /* for */
}

void RNETA_Deinit(void) {
  RNET1_Deinit();
}

void RNETA_Init(void) {
  RNET1_Init(); /* initialize stack */
  if (RAPP_SetMessageHandlerTable(handlerTable)!=ERR_OK) { /* assign application message handler */
    APP_DebugPrint((unsigned char*)"ERR: failed setting message handler!\r\n");
  }
  if (FRTOS1_xTaskCreate(
        RNetTask,  /* pointer to the task */
        "RNet", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+3,  /* initial priority */
        (TaskHandle_t*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}
#endif /* PL_HAS_NRF24 */

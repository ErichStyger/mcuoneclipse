/**
 * \file
 * \brief This is main application file
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This module implements the application part of the program.
 */
#include "Platform.h"
#if PL_HAS_RNET
#include "RNet_App.h"
#include "RStack.h"
#include "RApp.h"
#include "FRTOS1.h"
#include "RPHY.h"
#include "Radio.h"
#include "LED1.h"
#include "LED2.h"
//#include "LED3.h"
#include "LEDFrame.h"

typedef enum {
  RNETA_INITIAL, /* initialization state */
  RNETA_POWERUP, /* powered up the transceiver */
  RNETA_TX_RX /* ready to send and receive data */
} RNETA_State;

static RNETA_State appState = RNETA_INITIAL;

uint8_t RNETA_SendIdValuePairMessage(uint8_t msgType, uint16_t id, uint32_t value, RAPP_ShortAddrType addr, RAPP_FlagsType flags) {
  uint8_t dataBuf[6]; /* 2 byte ID followed by 4 byte data */

  UTIL1_SetValue16LE(id, &dataBuf[0]);
  UTIL1_SetValue32LE(value, &dataBuf[2]);
  return RAPP_SendPayloadDataBlock(dataBuf, sizeof(dataBuf), msgType, addr, flags);
}

static uint8_t RNETA_HandleRxMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet) {
#if PL_HAS_LED_FRAME
  uint32_t val;
#else
  (void)srcAddr; /* not used */
#endif
  uint16_t id;

  (void)size;
  (void)packet;
  switch(type) {
    case RAPP_MSG_TYPE_REQUEST_SET_VALUE:
      id = UTIL1_GetValue16LE(data); /* extract 16bit ID (little endian) */
      if (id==RAPP_MSG_TYPE_DATA_ID_NEO_BRIGHTNESS) {
#if PL_HAS_LED_FRAME
        val = UTIL1_GetValue32LE(&data[2]);
        LEDFRAME_SetBrightnessPercent(val);
        *handled = TRUE;
#else
        *handled = FALSE;
#endif
       }
      break;

    case RAPP_MSG_TYPE_QUERY_VALUE:
      id = UTIL1_GetValue16LE(data); /* extract 16bit ID (little endian) */
      if (id==RAPP_MSG_TYPE_DATA_ID_NEO_BRIGHTNESS) { /* send back data */
#if PL_HAS_LED_FRAME
        RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_QUERY_VALUE_RESPONSE, id, LEDFRAME_GetBrightnessPercent(), srcAddr, RPHY_PACKET_FLAGS_NONE);
        *handled = TRUE;
#else
        *handled = FALSE;
#endif
      } else if (id==RAPP_MSG_TYPE_DATA_ID_NEO_RED) { /* send back data */
#if PL_HAS_LED_FRAME
        RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_QUERY_VALUE_RESPONSE, id, LEDFRAME_GetColorRedValue(), srcAddr, RPHY_PACKET_FLAGS_NONE);
        *handled = TRUE;
#else
        *handled = FALSE;
#endif
      } else if (id==RAPP_MSG_TYPE_DATA_ID_NEO_GREEN) { /* send back data */
#if PL_HAS_LED_FRAME
        RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_QUERY_VALUE_RESPONSE, id, LEDFRAME_GetColorGreenValue(), srcAddr, RPHY_PACKET_FLAGS_NONE);
        *handled = TRUE;
#else
        *handled = FALSE;
#endif
      } else if (id==RAPP_MSG_TYPE_DATA_ID_NEO_BLUE) { /* send back data */
#if PL_HAS_LED_FRAME
        RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_QUERY_VALUE_RESPONSE, id, LEDFRAME_GetColorBlueValue(), srcAddr, RPHY_PACKET_FLAGS_NONE);
        *handled = TRUE;
#else
        *handled = FALSE;
#endif
      }
      break;

    default:
      break;
  } /* switch */
  if (*handled) {
  #if PL_HAS_BUZZER
    BUZ_PlayTune(BUZ_TUNE_BUTTON);
  #endif
  }
  return ERR_OK;
}

static const RAPP_MsgHandler handlerTable[] = 
{
  RNETA_HandleRxMessage,
  NULL /* sentinel */
};

static void RadioPowerUp(void) {
  /* need to ensure that we wait at least 100 ms (I use 150 ms here) after power-on of the transceiver */
  portTickType xTime;
  
  xTime = FRTOS1_xTaskGetTickCount();
  if (xTime<(150/portTICK_RATE_MS)) {
    /* not powered for 100 ms: wait until we can access the radio transceiver */
    xTime = (150/portTICK_RATE_MS)-xTime; /* remaining ticks to wait */
    FRTOS1_vTaskDelay(xTime);
  }
  (void)RADIO_PowerUp(); /* enable the transceiver */
}

static void Process(void) {
  for(;;) {
    switch(appState) {
    case RNETA_INITIAL:
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
  uint32_t cntr;
  uint8_t msgCntr;

  (void)pvParameters; /* not used */
  if (RAPP_SetThisNodeAddr(RNWK_ADDR_BROADCAST)!=ERR_OK) { /* set a default address */
    for(;;); /* "ERR: Failed setting node address" */
  }
  cntr = 0; /* initialize LED counter */
  msgCntr = 0; /* initialize message counter */
  appState = RNETA_INITIAL; /* initialize state machine state */
  for(;;) {
    Process(); /* process state machine */
    cntr++;
    if (cntr==100) { /* with an RTOS 10 ms/100 Hz tick rate, this is every second */
     // LED3_On(); /* blink blue LED for 20 ms */
     // RAPP_SendPayloadDataBlock(&msgCntr, sizeof(msgCntr), RAPP_MSG_TYPE_PING, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
      msgCntr++;
      cntr = 0;
      FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
      //LED3_Off(); /* blink blue LED */
    }
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
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
        (600/sizeof(StackType_t)), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}
#endif /* PL_HAS_RNET */

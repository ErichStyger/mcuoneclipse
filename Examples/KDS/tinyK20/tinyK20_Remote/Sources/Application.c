/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Platform.h"
#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "LED1.h"
#include "RNet_App.h"
#if PL_CONFIG_HAS_LCD
  #include "LCD.h"
#endif
#if PL_CONFIG_HAS_SNAKE
  #include "Snake.h"
#endif
#if PL_CONFIG_HAS_TETIRS
  #include "Tetris.h"
#endif
#include "Keys.h"
#include "KeyDebounce.h"
#include "SW1.h"
#include "SW2.h"
#include "SW3.h"
#include "SW4.h"
#include "SW5.h"
#if PL_CONFIG_HAS_RADIO
  #include "RApp.h"
#endif
#if PL_CONFIG_HAS_LCD
  #include "Event.h"
  #include "GDisp1.h"
  #include "FDisp1.h"
#endif

void APP_DebugPrint(uint8_t *str) {
 /* dummy */
}

static uint8_t REMOTE_SendButton(uint8_t button) {
  return RAPP_SendPayloadDataBlock(&button, sizeof(button), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
}

static void App_HandleKeys(void) {
#if PL_CONFIG_HAS_KEYS && !PL_CONFIG_HAS_KBI
    KEY_Scan();
#endif

    if (EVNT_EventIsSetAutoClear(EVNT_SW1_PRESSED)) { /* right */
#if PL_CONFIG_HAS_SNAKE
      EVNT_SetEvent(EVNT_SNAKE_RIGHT);
#else
    #if PL_CONFIG_HAS_REMOTE
      REMOTE_SendButton('r');
    #endif
      EVNT_SetEvent(EVNT_LCD_BTN_RIGHT);
#endif
    }
    if (EVNT_EventIsSetAutoClear(EVNT_SW2_PRESSED)) { /* left */
#if PL_CONFIG_HAS_SNAKE
      EVNT_SetEvent(EVNT_SNAKE_LEFT);
#else
    #if PL_CONFIG_HAS_REMOTE
      REMOTE_SendButton('l');
    #endif
      EVNT_SetEvent(EVNT_LCD_BTN_LEFT);
#endif
    }
    if (EVNT_EventIsSetAutoClear(EVNT_SW3_PRESSED)) { /* down */
#if PL_CONFIG_HAS_SNAKE
      EVNT_SetEvent(EVNT_SNAKE_DOWN);
#else
    #if PL_CONFIG_HAS_REMOTE
      REMOTE_SendButton('b');
    #endif
      EVNT_SetEvent(EVNT_LCD_BTN_DOWN);
#endif
    }
    if (EVNT_EventIsSetAutoClear(EVNT_SW4_PRESSED)) { /* middle */
#if PL_CONFIG_HAS_SNAKE
      EVNT_SetEvent(EVNT_SNAKE_START_PAUSE);
#else
    #if PL_CONFIG_HAS_REMOTE
      REMOTE_SendButton('c');
    #endif
      EVNT_SetEvent(EVNT_LCD_BTN_CENTER);
#endif
    }
    if (EVNT_EventIsSetAutoClear(EVNT_SW5_PRESSED)) { /* up */
#if PL_CONFIG_HAS_SNAKE
      EVNT_SetEvent(EVNT_SNAKE_UP);
#else
    #if PL_CONFIG_HAS_REMOTE
      REMOTE_SendButton('f');
    #endif
      EVNT_SetEvent(EVNT_LCD_BTN_UP);
#endif
    }

}

static void app_task(void *param) {
  (void)param;
  for(;;) {
    App_HandleKeys();
    LED1_Neg();
    vTaskDelay(pdMS_TO_TICKS(10));
  } /* for */
}

void APP_Run(void) {
#if PL_CONFIG_HAS_SHELL
  SHELL_Init();
#endif
#if PL_CONFIG_HAS_KEYS
  KEY_Init();
#endif
#if PL_CONFIG_HAS_DEBOUNCE
  KEYDBNC_Init();
#endif
#if PL_CONFIG_HAS_RADIO
  RNETA_Init();
#endif
#if PL_CONFIG_HAS_LCD && !PL_CONFIG_HAS_SNAKE
  LCD_Init();
#endif
#if PL_CONFIG_HAS_SNAKE
  SNAKE_Init();
#endif
#if PL_CONFIG_HAS_TETIRS
  TETRIS_Init();
#endif

  if (xTaskCreate(app_task, "App", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
}


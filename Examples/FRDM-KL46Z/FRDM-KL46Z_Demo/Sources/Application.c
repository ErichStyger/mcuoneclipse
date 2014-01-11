/**
 * \file
 * \brief Main application
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This implements the application main loop.
 */

#define APP_USE_KEY_COMPONENT 1 /* using Key component */

#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "MMA1.h"
#include "Trace.h"
#include "LCD.h"
#include "SegLCD1.h"
#if APP_USE_KEY_COMPONENT
  #include "KEY1.h"
  #include "EVNT1.h"
#else
  #include "SW1.h"
  #include "SW3.h"
#endif
#include "MAG1.h"

void APP_HandleEvent(uint8_t event) {
  switch(event) {
    case EVNT1_KEY1_PRESSED:
      CLS1_SendStr((unsigned char*)"SW1 pressed!\r\n", CLS1_GetStdio()->stdOut);
      break;
    case EVNT1_KEY1_RELEASED:
      CLS1_SendStr((unsigned char*)"SW1 released!\r\n", CLS1_GetStdio()->stdOut);
      break;
    case EVNT1_KEY1_LONG_RELEASED:
      CLS1_SendStr((unsigned char*)"SW1 long released!\r\n", CLS1_GetStdio()->stdOut);
      break;
    case EVNT1_KEY3_PRESSED:
      CLS1_SendStr((unsigned char*)"SW3 pressed!\r\n", CLS1_GetStdio()->stdOut);
      break;
    case EVNT1_KEY3_RELEASED:
      CLS1_SendStr((unsigned char*)"SW3 released!\r\n", CLS1_GetStdio()->stdOut);
      break;
    case EVNT1_KEY3_LONG_RELEASED:
      CLS1_SendStr((unsigned char*)"SW3 long released!\r\n", CLS1_GetStdio()->stdOut);
      break;
    default:
      break;
  }
}

static portTASK_FUNCTION(MainTask, pvParameters) {
  unsigned char lcdBuf[sizeof("1234")];
  uint16_t cntr;
  
  (void)pvParameters; /* parameter not used */
  TRACE_Init();
  MMA1_Init(); /* enable accelerometer, if not already enabled */
  MAG1_Enable(); /* enable magnetometer */
  SHELL_Init();
  cntr = 0;
  for(;;) {
    UTIL1_Num16uToStrFormatted(lcdBuf, sizeof(lcdBuf), cntr, '0', 4);
    vfnLCD_Write_Msg(lcdBuf);
    cntr++;
    if (cntr>9999) { /* can only display 4 digits */
      cntr = 0;
    }
#if APP_USE_KEY_COMPONENT
    KEY1_ScanKeys(); /* using component in polling mode: poll keys, this will create events as needed. */
    EVNT1_HandleEvent();
#else
    if (SW1_GetVal()==0) { /* button pressed */
      FRTOS1_vTaskDelay(50/portTICK_RATE_MS); /* wait to debounce */
      while (SW1_GetVal()==0) { /* still pressed? */
        LED1_On();
      }
    }
    if (SW3_GetVal()==0) { /* button pressed */
      FRTOS1_vTaskDelay(50/portTICK_RATE_MS); /* wait to debounce */
      while (SW3_GetVal()==0) { /* still pressed? */
        LED2_On();
      }
    }
#endif
    LED1_Neg();
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  }
}

static LDD_TDeviceData *MySegLCDPtr;

void APP_Run(void) {
  MySegLCDPtr = SegLCD1_Init(NULL);  //initialize sLCD according to PEx 
  
  vfnLCD_Write_Msg((uint8 *)"8888");
  _LCD_DP1_ON(); /* dot for first digit */
  _LCD_DP2_ON(); /* dot for second digit */
  _LCD_DP3_ON(); /* dot for third digit */
  _LCD_COL_ON(); /* : between digit two and three */

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
  FRTOS1_vTaskStartScheduler();
}


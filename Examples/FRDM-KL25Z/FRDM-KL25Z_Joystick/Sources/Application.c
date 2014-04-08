/*
 * Application.c
 *
 *  Created on: Apr 7, 2014
 *      Author: tastyger
 */

#include "Platform.h"
#include "Application.h"
#include "EVNT1.h"
#include "WAIT1.h"
#include "KEY1.h"
#include "LED1.h"
#include "LED2.h"
#include "CLS1.h"
#include "FRTOS1.h"
#include "RNet_App.h"
#include "AD1.h"
#include "UTIL1.h"

void APP_DebugPrint(unsigned char *str) {
  CLS1_SendStr(str, CLS1_GetStdio()->stdOut);
}

static uint8_t APP_GetXY(uint16_t *x, uint16_t *y) {
  uint8_t res;
  uint16_t values[2];
  
  res = AD1_Measure(TRUE);
  if (res!=ERR_OK) {
    return res;
  }
  res = AD1_GetValue16(&values[0]);
  if (res!=ERR_OK) {
    return res;
  }
  *x = values[0];
  *y = values[1];
  return ERR_OK;
}

void APP_OnKeyPressed(uint8_t keys) {
  if (keys&(1<<0)) {
    EVNT1_SetEvent(EVNT1_A_PRESSED);
  }
  if (keys&(1<<1)) {
    EVNT1_SetEvent(EVNT1_B_PRESSED);
  }
  if (keys&(1<<2)) {
    EVNT1_SetEvent(EVNT1_C_PRESSED);
  }
  if (keys&(1<<3)) {
    EVNT1_SetEvent(EVNT1_D_PRESSED);
  }
  if (keys&(1<<4)) {
    EVNT1_SetEvent(EVNT1_E_PRESSED);
  }
  if (keys&(1<<5)) {
    EVNT1_SetEvent(EVNT1_F_PRESSED);
  }
  if (keys&(1<<6)) {
    EVNT1_SetEvent(EVNT1_KEY_PRESSED);
  }
}

void APP_OnKeyReleasedLong(uint8_t keys) {
  
}

void APP_OnKeyReleased(uint8_t keys) {
  
}

void APP_HandleEvent(uint8_t event) {
  switch(event) {
  case EVNT1_A_PRESSED:
    CLS1_SendStr((unsigned char*)"A pressed!\r\n", CLS1_GetStdio()->stdOut);
    break;
  case EVNT1_B_PRESSED:
    CLS1_SendStr((unsigned char*)"B pressed!\r\n", CLS1_GetStdio()->stdOut);
    break;
  case EVNT1_C_PRESSED:
    CLS1_SendStr((unsigned char*)"C pressed!\r\n", CLS1_GetStdio()->stdOut);
    break;
  case EVNT1_D_PRESSED:
    CLS1_SendStr((unsigned char*)"D pressed!\r\n", CLS1_GetStdio()->stdOut);
    break;
  case EVNT1_E_PRESSED:
    CLS1_SendStr((unsigned char*)"E pressed!\r\n", CLS1_GetStdio()->stdOut);
    break;
  case EVNT1_F_PRESSED:
    CLS1_SendStr((unsigned char*)"F pressed!\r\n", CLS1_GetStdio()->stdOut);
    break;
  case EVNT1_KEY_PRESSED:
    CLS1_SendStr((unsigned char*)"KEY pressed!\r\n", CLS1_GetStdio()->stdOut);
    break;
  default:
    break;
  } /* switch */
}

static void PrintXY(void) {
  uint16_t x, y;
  uint8_t buf[32];
  
  if (APP_GetXY(&x, &y)==ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"X: 0x");
    UTIL1_strcatNum16Hex(buf, sizeof(buf), x);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" Y: 0x");
    UTIL1_strcatNum16Hex(buf, sizeof(buf), y);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
  } else {
    CLS1_SendStr((unsigned char*)"GetXY() failed!\r\n", CLS1_GetStdio()->stdErr);
  }
}

static void AppTask(void *pvParameters) {
  uint16_t cntMs;
  
  CLS1_SendStr((unsigned char*)"Hello from the Joystick App!\r\n", CLS1_GetStdio()->stdOut);
  cntMs = 0;
  for(;;) {
    if (cntMs>500) {
      PrintXY();
      LED1_Neg();
      cntMs = 0;
    }
    KEY1_ScanKeys();
    EVNT1_HandleEvent();
    WAIT1_Waitms(20);
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
    cntMs += 10;
  }
}


void APP_Run(void) {
//  RNETA_Init();
  if (FRTOS1_xTaskCreate(
        AppTask,  /* pointer to the task */
        "App", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+2,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  FRTOS1_vTaskStartScheduler();
}

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
#include "AD1.h"
#include "UTIL1.h"
#include "Shell.h"
#if PL_HAS_NRF24
  #include "RNet_App.h"
  #include "RNet_AppConfig.h"
  #include "RNWK.h"
  #include "Rapp.h"
#endif
#if PL_HAS_LCD
  #include "PDC1.h"
  #include "Snake.h"
#endif
#include "Control.h"

static bool JoyStickEnabled = FALSE; /* controlled by F key */
static bool ButtonsEnabled = TRUE;  /* controlled by E key */

void APP_DebugPrint(unsigned char *str) {
  CLS1_SendStr(str, CLS1_GetStdio()->stdOut);
}

static int8_t ToSigned8Bit(uint16_t val) {
  int tmp;

  tmp = ((int)((val>>8)&0xFF))-127;
  if (tmp<-128) {
    tmp = -128;
  } else if (tmp>127) {
    tmp = 127;
  }
  return (int8_t)tmp;
}

static uint8_t APP_GetXY(uint16_t *x, uint16_t *y, int8_t *x8, int8_t *y8) {
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
  /* transform into -128...127 with zero as mid position */
  *x8 = ToSigned8Bit(values[0]);
  *y8 = ToSigned8Bit(values[1]);
  return ERR_OK;
}

static void APP_HandleEvent(void) {
#if PL_HAS_NRF24
  uint8_t data;
#endif
  
  if (EVNT1_GetClearEvent(EVNT1_A_PRESSED)) {
    CLS1_SendStr((unsigned char*)"A pressed!\r\n", CLS1_GetStdio()->stdOut);
#if PL_HAS_NRF24
    data = 'A';
    (void)RAPP_SendPayloadDataBlock(&data, sizeof(data), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
#endif
#if PL_HAS_SNAKE_GAME
    EVNT1_SetEvent(EVNT1_SNAKE_UP);
#endif
  }
  if (EVNT1_GetClearEvent(EVNT1_B_PRESSED)) {
    CLS1_SendStr((unsigned char*)"B pressed!\r\n", CLS1_GetStdio()->stdOut);
#if PL_HAS_NRF24
    data = 'B';
    (void)RAPP_SendPayloadDataBlock(&data, sizeof(data), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
#endif
#if PL_HAS_SNAKE_GAME
    EVNT1_SetEvent(EVNT1_SNAKE_RIGHT);
#endif
  }
  if (EVNT1_GetClearEvent(EVNT1_C_PRESSED)) {
    CLS1_SendStr((unsigned char*)"C pressed!\r\n", CLS1_GetStdio()->stdOut);
#if PL_HAS_NRF24
    data = 'C';
    (void)RAPP_SendPayloadDataBlock(&data, sizeof(data), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
#endif
#if PL_HAS_SNAKE_GAME
    EVNT1_SetEvent(EVNT1_SNAKE_DOWN);
#endif
  }  
  if (EVNT1_GetClearEvent(EVNT1_D_PRESSED)) {
    CLS1_SendStr((unsigned char*)"D pressed!\r\n", CLS1_GetStdio()->stdOut);
#if PL_HAS_NRF24
    data = 'D';
    (void)RAPP_SendPayloadDataBlock(&data, sizeof(data), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
#endif
#if PL_HAS_SNAKE_GAME
    EVNT1_SetEvent(EVNT1_SNAKE_LEFT);
#endif
  }  
  if (EVNT1_GetClearEvent(EVNT1_E_PRESSED)) {
    CLS1_SendStr((unsigned char*)"E pressed!\r\n", CLS1_GetStdio()->stdOut);
    ButtonsEnabled = !ButtonsEnabled;
#if PL_HAS_NRF24
    data = 'E';
    (void)RAPP_SendPayloadDataBlock(&data, sizeof(data), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
#endif
#if PL_HAS_SNAKE_GAME
    EVNT1_SetEvent(EVNT1_SNAKE_RESET);
#endif
  }  
  if (EVNT1_GetClearEvent(EVNT1_F_PRESSED)) {
    CLS1_SendStr((unsigned char*)"F pressed!\r\n", CLS1_GetStdio()->stdOut);
    JoyStickEnabled = !JoyStickEnabled;
#if PL_HAS_NRF24
    data = 'F';
    (void)RAPP_SendPayloadDataBlock(&data, sizeof(data), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
#endif
#if PL_HAS_SNAKE_GAME
    EVNT1_SetEvent(EVNT1_SNAKE_RESET);
#endif
  }  
  if (EVNT1_GetClearEvent(EVNT1_KEY_PRESSED)) {
    CLS1_SendStr((unsigned char*)"KEY pressed!\r\n", CLS1_GetStdio()->stdOut);
#if PL_HAS_NRF24
    data = 'K';
    (void)RAPP_SendPayloadDataBlock(&data, sizeof(data), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
#endif
#if PL_HAS_SNAKE_GAME
    EVNT1_SetEvent(EVNT1_SNAKE_START_PAUSE);
#endif
  }  
}

static void StatusPrintXY(CLS1_ConstStdIOType *io) {
  uint16_t x, y;
  int8_t x8, y8;
  uint8_t buf[64];
  KEY1_KeyStorage keys;
  
  keys = KEY1_GetKeys();
  buf[0] = '\0';
  UTIL1_strcat(buf, sizeof(buf), (keys&(1<<0))?(unsigned char*)"A(ON) ":(unsigned char*)"A(off) ");
  UTIL1_strcat(buf, sizeof(buf), (keys&(1<<1))?(unsigned char*)"B(ON) ":(unsigned char*)"B(off) ");
  UTIL1_strcat(buf, sizeof(buf), (keys&(1<<2))?(unsigned char*)"C(ON) ":(unsigned char*)"C(off) ");
  UTIL1_strcat(buf, sizeof(buf), (keys&(1<<3))?(unsigned char*)"D(ON) ":(unsigned char*)"D(off) ");
  UTIL1_strcat(buf, sizeof(buf), (keys&(1<<4))?(unsigned char*)"E(ON) ":(unsigned char*)"E(off) ");
  UTIL1_strcat(buf, sizeof(buf), (keys&(1<<5))?(unsigned char*)"F(ON) ":(unsigned char*)"F(off) ");
  UTIL1_strcat(buf, sizeof(buf), (keys&(1<<6))?(unsigned char*)"KEY(ON)\r\n":(unsigned char*)"KEY(off)\r\n");
  CLS1_SendStatusStr((unsigned char*)"  Buttons", buf, io->stdOut);

  if (APP_GetXY(&x, &y, &x8, &y8)==ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"X: 0x");
    UTIL1_strcatNum16Hex(buf, sizeof(buf), x);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"(");
    UTIL1_strcatNum8s(buf, sizeof(buf), x8);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)") Y: 0x");
    UTIL1_strcatNum16Hex(buf, sizeof(buf), y);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"(");
    UTIL1_strcatNum8s(buf, sizeof(buf), y8);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)")\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"GetXY() failed!\r\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  Analog", buf, io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  Joystick", JoyStickEnabled?(unsigned char*)"yes (toggle with F)\r\n":(unsigned char*)"no (toggle with F)\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  Buttons", ButtonsEnabled?(unsigned char*)"yes (toggle with E)\r\n":(unsigned char*)"no (toggle with E)\r\n", io->stdOut);
}

uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, CLS1_ConstStdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "app help")==0) {
    CLS1_SendHelpStr((unsigned char*)"app", (const unsigned char*)"Group of app commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"print help or status information\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, "app status")==0) {
    CLS1_SendStatusStr((unsigned char*)"app", (unsigned char*)"\r\n", io->stdOut);
    StatusPrintXY(io);
    *handled = TRUE;
    return ERR_OK;
  }
  return ERR_OK; /* no error */
}

static void AppTask(void *pvParameters) {
  uint16_t cntMs;
  uint16_t x, y;
  int8_t x8, y8, x8prev, y8prev;
#if PL_HAS_NRF24
  uint8_t data[2];
#endif
  uint8_t buf[24];
  
  cntMs = 0;
  x8prev = 127; y8prev = 127; /* should be different from center position */
  for(;;) {
    if (APP_GetXY(&x, &y, &x8, &y8)!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"Failed to get x/y!\r\n", CLS1_GetStdio()->stdErr);
    } else {
#if PL_HAS_SNAKE_GAME
      if (y8>25) {
        EVNT1_SetEvent(EVNT1_SNAKE_UP);
      } else if (y8<-25) {
        EVNT1_SetEvent(EVNT1_SNAKE_DOWN);
      }
      if (x8>25) {
        EVNT1_SetEvent(EVNT1_SNAKE_RIGHT);
      } else if (x8<-25) {
        EVNT1_SetEvent(EVNT1_SNAKE_LEFT);
      }
#endif
      if (JoyStickEnabled && ((x8!=x8prev) || (y8!=y8prev))) { /* process only changing data, and only if not zero/midpoint */
        UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"xy: ");
        UTIL1_strcatNum8s(buf, sizeof(buf), x8);
        UTIL1_chcat(buf, sizeof(buf), ',');
        UTIL1_strcatNum8s(buf, sizeof(buf), y8);
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
        CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
#if PL_HAS_NRF24
        if (JoyStickEnabled) {
          data[0] = (uint8_t)x8;
          data[1] = (uint8_t)y8;
          (void)RAPP_SendPayloadDataBlock(&data[0], sizeof(data), RAPP_MSG_TYPE_JOYSTICK_XY, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
        }
#endif
        x8prev = x8;
        y8prev = y8;
      }
    }
    if (cntMs>500) {
      LED1_Neg();
      cntMs = 0;
    }
    CTRL_ScanKeys();
    APP_HandleEvent();
    vTaskDelay(pdMS_TO_TICKS(10));
    cntMs += 10;
  }
}

void APP_Run(void) {
  CTRL_Init();
#if PL_HAS_SNAKE_GAME
  SNAKE_Init();
#endif
#if PL_HAS_NRF24
  WAIT1_Waitms(200); /* wait at least 100 ms to power-up the receiver */
#endif
#if PL_HAS_SHELL
  SHELL_Init();
#endif
#if PL_HAS_NRF24
  RNETA_Init();
#endif
  if (xTaskCreate(
        AppTask,  /* pointer to the task */
        "App", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (TaskHandle_t*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  FRTOS1_vTaskStartScheduler();
}

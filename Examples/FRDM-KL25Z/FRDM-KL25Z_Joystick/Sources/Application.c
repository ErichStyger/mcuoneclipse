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
#include "Shell.h"
#include "RNet_AppConfig.h"
#include "RNWK.h"
#include "Rapp.h"

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
#if PL_HAS_NRF24
  uint8_t data;
#endif
  
  switch(event) {
  case EVNT1_A_PRESSED:
    CLS1_SendStr((unsigned char*)"A pressed!\r\n", CLS1_GetStdio()->stdOut);
#if PL_HAS_NRF24
    data = 'A';
    (void)RAPP_SendPayloadDataBlock(&data, sizeof(data), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
#endif
    break;
  case EVNT1_B_PRESSED:
    CLS1_SendStr((unsigned char*)"B pressed!\r\n", CLS1_GetStdio()->stdOut);
#if PL_HAS_NRF24
    data = 'B';
    (void)RAPP_SendPayloadDataBlock(&data, sizeof(data), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
#endif
    break;
  case EVNT1_C_PRESSED:
    CLS1_SendStr((unsigned char*)"C pressed!\r\n", CLS1_GetStdio()->stdOut);
#if PL_HAS_NRF24
    data = 'C';
    (void)RAPP_SendPayloadDataBlock(&data, sizeof(data), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
#endif
    break;
  case EVNT1_D_PRESSED:
    CLS1_SendStr((unsigned char*)"D pressed!\r\n", CLS1_GetStdio()->stdOut);
#if PL_HAS_NRF24
    data = 'D';
    (void)RAPP_SendPayloadDataBlock(&data, sizeof(data), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
#endif
    break;
  case EVNT1_E_PRESSED:
    CLS1_SendStr((unsigned char*)"E pressed!\r\n", CLS1_GetStdio()->stdOut);
#if PL_HAS_NRF24
    data = 'E';
    (void)RAPP_SendPayloadDataBlock(&data, sizeof(data), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
#endif
    break;
  case EVNT1_F_PRESSED:
    CLS1_SendStr((unsigned char*)"F pressed!\r\n", CLS1_GetStdio()->stdOut);
#if PL_HAS_NRF24
    data = 'F';
    (void)RAPP_SendPayloadDataBlock(&data, sizeof(data), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
#endif
    break;
  case EVNT1_KEY_PRESSED:
    CLS1_SendStr((unsigned char*)"KEY pressed!\r\n", CLS1_GetStdio()->stdOut);
#if PL_HAS_NRF24
    data = 'K';
    (void)RAPP_SendPayloadDataBlock(&data, sizeof(data), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
#endif
    break;
  default:
    break;
  } /* switch */
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
  uint8_t data[2];
  uint8_t buf[24];
  
  CLS1_SendStr((unsigned char*)"Hello from the Joystick App!\r\n", CLS1_GetStdio()->stdOut);
  cntMs = 0;
  x8prev = 127; y8prev = 127; /* should be different from center position */
  for(;;) {
    if (APP_GetXY(&x, &y, &x8, &y8)==ERR_OK) {
      CLS1_SendStr((unsigned char*)"Failed to get x/y!\r\n", CLS1_GetStdio()->stdErr);
    } else {
      if (x8!=x8prev || y8!=y8prev || x8!=0 || y8!=0) { /* send only changing data, and only if not zero/midpoint */
        UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"xy: ");
        UTIL1_strcatNum8s(buf, sizeof(buf), x8);
        UTIL1_chcat(buf, sizeof(buf), ',');
        UTIL1_strcatNum8s(buf, sizeof(buf), y8);
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
        CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
        data[0] = (uint8_t)x8;
        data[1] = (uint8_t)y8;
        (void)RAPP_SendPayloadDataBlock(&data[0], sizeof(data), RAPP_MSG_TYPE_JOYSTICK_XY, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
      }
    }
    if (cntMs>500) {
      //PrintXY();
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
#if PL_HAS_SHELL
  SHELL_Init();
#endif
#if PL_HAS_NRF24
  RNETA_Init();
#endif
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

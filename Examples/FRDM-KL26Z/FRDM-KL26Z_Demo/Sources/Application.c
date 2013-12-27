/**
 * \file
 * \brief Application module
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This is the implementation of the application.
 */
#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "FRTOS1.h"
#include "EVNT1.h"
#include "Shell.h"
#include "FX1.h"
#include "AD1.h"
#include "UTIL1.h"

static uint16_t GetLightValue(void) {
  uint16_t val;
  
  (void)AD1_Measure(TRUE);
  (void)AD1_GetValue16(&val);
  return val;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[24];
  
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  UTIL1_strcatNum16Hex(buf, sizeof(buf), GetLightValue());
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  Light", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"app", (unsigned char*)"Group of application commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "app help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "app status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  }
  return ERR_OK;
}


void APP_HandleEvent(uint8_t event) {
  switch(event) {
    case EVNT1_KEY1_PRESSED:
      CLS1_SendStr((unsigned char*)"KEY1 pressed!\r\n", CLS1_GetStdio()->stdOut);
      break;
    case EVNT1_KEY1_RELEASED:
      CLS1_SendStr((unsigned char*)"KEY1 released!\r\n", CLS1_GetStdio()->stdOut);
      break;
    case EVNT1_KEY1_LONG_RELEASED:
      CLS1_SendStr((unsigned char*)"KEY1 long released!\r\n", CLS1_GetStdio()->stdOut);
      break;
    default:
      break;
  }
}

static void AppTask(void *pvParameters) {
  uint16_t lightVal;
  
  FX1_Init();
  for(;;) {
    EVNT1_HandleEvent();
    LED1_Neg();
#if 0
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
#else /* task rate depending on light sensor value */
    lightVal = GetLightValue();
    FRTOS1_vTaskDelay((lightVal>>8)/portTICK_RATE_MS);
#endif
  }
}

void APP_Run(void) {
  /* some hardware test... */
#if 0
  LED1_Neg();
  LED2_Neg();
  LED3_Neg();
  CLS1_SendStr((unsigned char*)"Hello world!\r\n", CLS1_GetStdio()->stdOut);
  LED1_Neg();
  LED2_Neg();
  LED3_Neg();
#endif
  
  /* now start the application */
  SHELL_Init();
  if (FRTOS1_xTaskCreate(
        AppTask,  /* pointer to the task */
        (signed char *)"App", /* task name for kernel awareness debugging */
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

/*
 * Application.c
 *
 *  Created on: 27.08.2018
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "Application.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "McuRTT.h"
#include "McuRTOS.h"
#include "McuWait.h"
#include "McuUtility.h"
#include "McuHardFault.h"
#include "McuArmTools.h"
#include "McuSystemView.h"
#include "McuPercepio.h"
#include "McuLED.h"
#include "McuGenericI2C.h"
#include "McuGenericSWI2C.h"
#include "McuSSD1306.h"
#include "McuTimeDate.h"
#include "McuCriticalSection.h"
#include "McuXFormat.h"
#include "McuTrigger.h"
#if PL_CONFIG_HAS_HD44780
  #include "McuHD44780.h"
#endif

static TimerHandle_t timerHndl;
#define TIMER_PERIOD_MS 100

static void vTimerCallback(xTimerHandle pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
}

void McuGenericI2C_OnError(void) {
	/* I2C error hook */  /* disable with McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT */
}

static void AppTask(void *param) {
	(void)param;
	for(;;) {
		McuLED_Neg();
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

void APP_Run(void) {
  unsigned char buf[17];

  /* initialize components */
//  McuRTOS_Init();
  McuCriticalSection_Init();
//  McuRTT_Init();
#if configUSE_PERCEPIO_TRACE_HOOKS
  //McuPercepio_Init();
#elif configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
 // McuXFormat_Init();
 // McuTrigger_Init();
  McuWait_Init();
  McuUtility_Init();
  McuHardFault_Init();
  McuArmTools_Init();
  McuLED_Init(); /* initializes as well the LED pin */
 // McuGenericI2C_Init();
 // McuGenericSWI2C_Init(); /* initializes as well the SCL and SDA pins */
#if PL_CONFIG_HAS_SSD1606
  McuSSD1306_Init(); /* requires display on the I2C bus! */
#endif
#if PL_CONFIG_HAS_HD44780
  McuWait_Waitms(200); /* give hardware time to power up */
  McuHD44780_Init();
#endif
  McuTimeDate_Init();

#if PL_CONFIG_HAS_HD44780
  McuHD44780_Clear();
#endif

  for(;;) {
#if PL_CONFIG_HAS_HD44780
  {
    DATEREC date;
    TIMEREC time;

    buf[0] = '\0';
    McuTimeDate_GetTime(&time);
    McuTimeDate_AddTimeString(buf, sizeof(buf), &time, (uint8_t*)"hh:mm.ss,cc");
    McuHD44780_WriteLineStr(1, (char*)buf);

    buf[0] = '\0';
    McuTimeDate_GetDate(&date);
    McuTimeDate_AddDateString(buf, sizeof(buf), &date, (uint8_t*)"dd.mm.yyyy");
    McuHD44780_WriteLineStr(2, (char*)buf);
  }
#endif
    McuWait_Waitms(100);
    McuLED_Neg();
  }

  if (xTaskCreate(
	  AppTask,  /* pointer to the task */
	  "App", /* task name for kernel awareness debugging */
	  configMINIMAL_STACK_SIZE+500, /* task stack size */
	  (void*)NULL, /* optional task startup argument */
	  tskIDLE_PRIORITY,  /* initial priority */
	  (xTaskHandle*)NULL /* optional task handle to create */
	) != pdPASS) {
    /*lint -e527 */
	 for(;;){} /* error! probably out of memory */
	/*lint +e527 */
  }
  timerHndl = xTimerCreate("timer0", TIMER_PERIOD_MS/portTICK_RATE_MS, pdTRUE, (void *)0, vTimerCallback);
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) {
    for(;;); /* failure! */
  }
  vTaskStartScheduler();
  for(;;) {}
}

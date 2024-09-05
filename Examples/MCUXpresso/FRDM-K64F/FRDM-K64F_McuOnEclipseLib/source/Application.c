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
#include "McuLED.h"
#include "McuPercepio.h"
#include "McuGenericI2C.h"
#include "McuGenericSWI2C.h"
#include "McuSSD1306.h"
#include "McuTimeDate.h"
#include "McuCriticalSection.h"
#include "McuXFormat.h"
#include "McuTrigger.h"
#include "Accel.h"
#if PL_CONFIG_HAS_HD44780
  #include "McuHD44780.h"
#endif

static TimerHandle_t timerHndl;
#define TIMER_PERIOD_MS 100

static void vTimerCallback(TimerHandle_t pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
}

void McuGenericI2C_OnError(void) {
	/* I2C error hook */  /* disable with McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT */
}

static void AppTask(void *param) {
  McuLED_Config_t config;
  McuLED_Handle_t led; /* red */
  #define LEDpin_CONFIG_PORT_NAME       PORTB
  #define LEDpin_CONFIG_GPIO_NAME       GPIOB
  #define LEDpin_CONFIG_PIN_NUMBER      22u

  McuLED_GetDefaultConfig(&config);
  config.hw.gpio = LEDpin_CONFIG_GPIO_NAME;
  config.hw.pin = LEDpin_CONFIG_PIN_NUMBER;
  config.hw.port = LEDpin_CONFIG_PORT_NAME;
  config.isLowActive = true;
  led = McuLED_InitLed(&config);
  McuLED_Off(led);
  McuLED_On(led);
	for(;;) {
		McuLED_Toggle(led);
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

#define SEGGER_SYSVIEW_DATA_ID_ACCEL_X   (0)
#define SEGGER_SYSVIEW_DATA_ID_ACCEL_Y   (1)
#define SEGGER_SYSVIEW_DATA_ID_ACCEL_Z   (2)

static I32 accelX = 0;
static I32 accelY = 0;
static I32 accelZ = 0;

static const SEGGER_SYSVIEW_DATA_SAMPLE accelXdata = {
    .ID = SEGGER_SYSVIEW_DATA_ID_ACCEL_X,
    .pValue.pI32_Value = &accelX,
};

static const SEGGER_SYSVIEW_DATA_SAMPLE accelYdata = {
    .ID = SEGGER_SYSVIEW_DATA_ID_ACCEL_Y,
    .pValue.pI32_Value = &accelY,
};

static const SEGGER_SYSVIEW_DATA_SAMPLE accelZdata = {
    .ID = SEGGER_SYSVIEW_DATA_ID_ACCEL_Z,
    .pValue.pI32_Value = &accelZ,
};

static const SEGGER_SYSVIEW_DATA_REGISTER regdataX = {
    .ID = SEGGER_SYSVIEW_DATA_ID_ACCEL_X,
    .DataType = SEGGER_SYSVIEW_TYPE_I32,
    .Offset = 0,
    .RangeMin = 0,
    .RangeMax = 0,
    .ScalingFactor = 1.0f,
    .sName = "Accel X",
    .sUnit = "mg"
};

static const SEGGER_SYSVIEW_DATA_REGISTER regdataY = {
    .ID = SEGGER_SYSVIEW_DATA_ID_ACCEL_Y,
    .DataType = SEGGER_SYSVIEW_TYPE_I32,
    .Offset = 0,
    .RangeMin = 0,
    .RangeMax = 0,
    .ScalingFactor = 1.0f,
    .sName = "Accel Y",
    .sUnit = "mg"
};

static const SEGGER_SYSVIEW_DATA_REGISTER regdataZ = {
    .ID = SEGGER_SYSVIEW_DATA_ID_ACCEL_Z,
    .DataType = SEGGER_SYSVIEW_TYPE_I32,
    .Offset = 0,
    .RangeMin = 0,
    .RangeMax = 0,
    .ScalingFactor = 1.0f,
    .sName = "Accel Z",
    .sUnit = "mg"
};

void App_SysView_ConfigCallback(void) { /* configured with McuSystemView_CONFIG_SYSVIEW_CONFIG_CALLBACK */
  SEGGER_SYSVIEW_SendSysDesc("N="SYSVIEW_APP_NAME",O="SYSVIEW_OS_NAME",D="SYSVIEW_DEVICE_NAME);
  SEGGER_SYSVIEW_SendSysDesc("I#15=SysTick");
  SEGGER_SYSVIEW_RegisterData((SEGGER_SYSVIEW_DATA_REGISTER*)&regdataX);
  SEGGER_SYSVIEW_RegisterData((SEGGER_SYSVIEW_DATA_REGISTER*)&regdataY);
  SEGGER_SYSVIEW_RegisterData((SEGGER_SYSVIEW_DATA_REGISTER*)&regdataZ);
}

static void AccelTask(void *pv) {
  uint8_t res;
  int16_t x, y, z;

#if CONFIG_I2C_USE_PORT_E24_E25
  CLOCK_EnableClock(kCLOCK_PortE); /* PTE24 (I2C SCL), PTE25 (I2C SDA) */
#endif

  /* I2C and related modules. Note that if using HW I2C with interrupts, this requires interrupts enabled */
#if PL_CONFIG_USE_I2C
  McuGenericI2C_Init();
  #if PL_CONFIG_USE_HW_I2C
    I2CLIB_Init();
  #else
    McuGenericSWI2C_Init();
  #endif
#endif

  res = ACCEL_LowLevelInit();
  if (res!=ERR_OK) {
    for(;;) {}
  }
  res = ACCEL_Enable();
  if (res!=ERR_OK) {
    for(;;) {}
  }
  for(;;) {
    ACCEL_GetValues(&x, &y, &z);
    accelX = x;
    accelY = y;
    accelZ = z;
    SEGGER_SYSVIEW_SampleData(&accelXdata);
    SEGGER_SYSVIEW_SampleData(&accelYdata);
    SEGGER_SYSVIEW_SampleData(&accelZdata);
    vTaskDelay(pdMS_TO_TICKS(5));
  }
}

float calib[16];

extern float calib[16];

static float calc(float f, int idx) {
  return f*calib[16];
}

static void test2(double val) {
   calib[0] = (float)(val)/10.0f + 233.0f;
}

static void test(double val) {
   calib[0] = (float)(val)/10.0 + 233.0;
}

void APP_Run(void) {
  /* initialize components */

  calc(3.0, 0);
  test(3.0);
  test2(3.0f);

  McuRTOS_Init();
  McuCriticalSection_Init();
  McuRTT_Init();
#if configUSE_PERCEPIO_TRACE_HOOKS
  //McuPercepio_Init();
#elif configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
  McuXFormat_Init();
  McuTrigger_Init();
  McuWait_Init();
  McuUtility_Init();
  McuHardFault_Init();
  McuArmTools_Init();
  McuLED_Init(); /* initializes as well the LED pin */
//  McuGenericI2C_Init();
//  McuGenericSWI2C_Init(); /* initializes as well the SCL and SDA pins */
#if PL_CONFIG_HAS_SSD1606
  McuSSD1306_Init(); /* requires display on the I2C bus! */
#endif
#if PL_CONFIG_HAS_HD44780
  McuHD44780_Init();
#endif
  McuTimeDate_Init();

  if (xTaskCreate(
	  AppTask,  /* pointer to the task */
	  "App", /* task name for kernel awareness debugging */
	  configMINIMAL_STACK_SIZE+500, /* task stack size */
	  (void*)NULL, /* optional task startup argument */
	  tskIDLE_PRIORITY+1,  /* initial priority */
	  (TaskHandle_t*)NULL /* optional task handle to create */
	) != pdPASS) {
    /*lint -e527 */
	 for(;;){} /* error! probably out of memory */
	/*lint +e527 */
  }
  timerHndl = xTimerCreate("timer0", pdMS_TO_TICKS(TIMER_PERIOD_MS), pdTRUE, (void *)0, vTimerCallback);
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) {
    for(;;); /* failure! */
  }
  if (xTaskCreate(
    AccelTask,  /* pointer to the task */
    "Accel", /* task name for kernel awareness debugging */
    configMINIMAL_STACK_SIZE+500, /* task stack size */
    (void*)NULL, /* optional task startup argument */
    tskIDLE_PRIORITY+1,  /* initial priority */
    (TaskHandle_t*)NULL /* optional task handle to create */
  ) != pdPASS) {
    /*lint -e527 */
   for(;;){} /* error! probably out of memory */
  /*lint +e527 */
  }

  vTaskStartScheduler();
  for(;;) {}
}

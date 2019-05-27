/*
 * application.c
 *      Author: Erich Styger
 */

/* own modules and standard library */
#include "McuArmTools.h"
#include "application.h" /* own interface */
#include <ctype.h> /* for isupper() */
#include "platform.h"

/* SDK */
#include "fsl_lpuart.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "pin_mux.h"
#include "board.h"

/* own modules */
#include "leds.h"
#include "initPins.h"
#include "gateway.h"
#include "shutdown.h"
#include "oled.h"
#include "McuRB.h"

/* McuLib */
#include "McuWait.h"
#include "McuArmTools.h"
#include "McuGenericI2C.h"
#include "McuGenericSWI2C.h"
#if PL_CONFIG_USE_LVGL
  #include "lv.h"
  #include "gui.h"
#endif
#if PL_CONFIG_USE_UPS
  #include "ups.h"
#endif
#if PL_CONFIG_USE_SHT31
  #include <McuSHT31.h>
#endif
#include "McuRTOS.h"
#include "FreeRTOS.h"

static void AppTask(void *pv) {
#if PL_CONFIG_USE_UPS
  float voltage, prevVoltage = 0.0f, charge;
  bool isCharging = true;
  int chargeCounter = 0; /* counting up for charging, counting down for discharging */
#endif

#if PL_CONFIG_USE_UPS
  UPS_SetIsCharging(false);
#endif
  for(;;) { /* main loop */
  #if PL_CONFIG_USE_UPS
    if (UPS_GetCharge(&charge)==0 && UPS_GetVoltage(&voltage)==0) {
      if (prevVoltage==0.0f) { /* first check */
        prevVoltage = voltage;
      }
      if (voltage-prevVoltage>0.02f) {
        chargeCounter++;
      } else if (prevVoltage-voltage>0.02f) {
        chargeCounter--;
      }
      if (!isCharging && chargeCounter>=5) {
        isCharging = true;
        UPS_SetIsCharging(true);
        prevVoltage = voltage;
        chargeCounter = 5;
      } else if (isCharging && chargeCounter<=-5) {
        isCharging = false;
        UPS_SetIsCharging(false);
        prevVoltage = voltage;
        chargeCounter = -5;
      }
    #if PL_CONFIG_USE_SHUTDOWN
      if (charge<20.0f && !isCharging) { /* low battery and not is charging => power down */
        SHUTDOWN_RequestPowerOff();
      }
    #endif
    } /* for */
#endif /* PL_CONFIG_USE_UPS */
    McuLED_Neg(tinyLED);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void APP_Run(void) {
  PL_Init();
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      600/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
  for(;;) { /* should not get here */ }
}

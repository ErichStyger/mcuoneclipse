/*
 * Application.c
 *
 *  Created on: 14.10.2016
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "Application.h"
#include "Servo.h"
#include "PCA9685.h"
#include "Shell.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "Plotclock.h"
#include "TmDt1.h"

static void AppTask(void *pvParameters) {
  (void)pvParameters; /* parameter not used */

  vTaskDelay(pdMS_TO_TICKS(1000)); /* wait some time to allow RTC to power up */
  TmDt1_SyncWithExternalRTC(); /* synchronize internal clock from external RTC */
  if (SERVO_InitHardware(PCA9685_I2C_DEFAULT_ADDR)!=ERR_OK) {
    CLS1_SendStr("ERROR: Failed init of PCA9685!\r\n", CLS1_GetStdio()->stdErr);
  }
  PlotClock_Setup(); /* setup the clock and move servos to parking position */
  for(;;) {
    PlotClock_Loop();
    LED1_Neg();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void APP_Start(void) {
  SERVO_Init();
  PCA9685_Init();
  SHELL_Init();
  PLOTCLOCK_Init();
  if (xTaskCreate(AppTask, "App", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  vTaskStartScheduler();
  for(;;) {} /* does not return, as scheduler should not be stopped */
}

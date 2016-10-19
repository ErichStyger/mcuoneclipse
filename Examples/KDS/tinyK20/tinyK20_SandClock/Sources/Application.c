/*
 * Application.c
 *
 *  Created on: 14.10.2016
 *      Author: Erich Styger Local
 */

#include "Platform.h"
#include "Application.h"
#include "Servo.h"
#include "PCA9685.h"
#include "Shell.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "Plotclock.h"

#define PCA9685_I2C_ADDR  (0b1000000)

#define SERVO_MIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVO_MAX  600 // this is the 'maximum' pulse length count (out of 4096)

static void AppTask(void *pvParameters) {
  uint16_t val = 0x100;
  uint8_t res;
  uint16_t min = 225;
  uint16_t max = 645;

  (void)pvParameters; /* not used */
  if (SERVO_InitHardware(PCA9685_I2C_ADDR)!=ERR_OK) {
    CLS1_SendStr("ERROR: Failed init of PCA9685!\r\n", CLS1_GetStdio()->stdErr);
  }
  PlotClock_Setup();
  for(;;) {
    PlotClock_Loop();
    vTaskDelay(pdMS_TO_TICKS(500));
    LED1_Neg();
  }
#if 0
  for(;;) {
    LED1_Neg();
    for(val=0; val<=1500; val++) {
      SERVO_WriteDutyMicroSeconds(PCA9685_I2C_ADDR, 0, val, SERVO_MIN_TICKS, SERVO_MAX_TICKS);
      vTaskDelay(pdMS_TO_TICKS(10));
    }
    for (val=min; val<max; val++) {
      res = PCA9685_SetChannelDuty12Bit(PCA9685_I2C_ADDR, 0, 4095-val);
      res = PCA9685_SetChannelDuty12Bit(PCA9685_I2C_ADDR, 1, 4095-val);
      res = PCA9685_SetChannelDuty12Bit(PCA9685_I2C_ADDR, 2, 4095-val);
      vTaskDelay(pdMS_TO_TICKS(10));
    }
    for (val=max; val>min; val--) {
      res = PCA9685_SetChannelDuty12Bit(PCA9685_I2C_ADDR, 0, 4095-val);
      res = PCA9685_SetChannelDuty12Bit(PCA9685_I2C_ADDR, 1, 4095-val);
      res = PCA9685_SetChannelDuty12Bit(PCA9685_I2C_ADDR, 2, 4095-val);
      vTaskDelay(pdMS_TO_TICKS(10));
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
#endif
}

void APP_Start(void) {
  SERVO_Init();
  PCA9685_Init();
  SHELL_Init();
  if (xTaskCreate(AppTask, "App", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  vTaskStartScheduler();
  for(;;) {}
}


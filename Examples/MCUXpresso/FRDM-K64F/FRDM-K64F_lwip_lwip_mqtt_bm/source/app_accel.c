/*
 * app_accel.c
 *
 *  Created on: 05.05.2017
 *      Author: Erich Styger
 */


#include "config.h"
#if CONFIG_USE_ACCELEROMETER
#include "app_accel.h"
#include "GI2C1.h"
#include "I2C1.h"
#include "FX1.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include <math.h>

#if CONFIG_USE_FREERTOS
static void AccelTask(void *param) {
  int16_t x, y; //, z;
  int32_t value;
  int32_t max_value;
/*
 * Every sec it looks at 50 samples of X and Y from the onboard accelerometer working at +-2g, and it selects the maximum value
 *  (‘N’)‘N’ equals max sqrt(x2+ y2)The device then composes a JSON and sends to the Azure IOT Hub service (so each sec it sends a JSON msg)The JSON contains the
 * deviceid, the UTC timestamp taken from NTP, and ‘N’Every hour the device updates its time with NTP
 *
 */
  (void)param;
  /*! \todo calibrate on zero values (flat) */
  max_value = 0;
  for(;;) {
    x = FX1_GetXmg();
    y = FX1_GetYmg();
    //z = FX1_GetZmg();
    value = (x*x)+(y*y);
    if (value>max_value) {
      max_value = value;
    }
    LED2_Neg();
    vTaskDelay(pdMS_TO_TICKS(20)); /* 50 Hz */
  }
}
#endif

void ACCEL_Init(void) {
  GI2C1_Init();
  I2C1_Init();
  FX1_Init();
#if CONFIG_USE_FREERTOS
  if (xTaskCreate(AccelTask, "Accel", 1000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
}

#endif /* CONFIG_USE_ACCELEROMETER */

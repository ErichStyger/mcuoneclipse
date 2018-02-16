/*
 * Application.c
 *
 *  Created on: 06.02.2018
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "Application.h"
#include "LED1.h"
#include "WAIT1.h"
#include "AD1.h"
#include "FRTOS1.h"
#include "GI2C1.h"
#include "Shell.h"
#include "AD5252.h"
#include "AD5141.h"
#include "CLS1.h"

#if 0
static void AD5252Task(void *pv) {
  uint8_t res;
  uint8_t addr, data;

  for(;;) {
#if 0
    /* write */
    addr = AD5252_EEMEM1 | AD5252_I2C_REG | AD5252_I2C_EE;
    data = 0x12; /* init */
    res = GI2C1_WriteAddress(AD5252_I2C_ADDR, &addr, sizeof(addr), &data, sizeof(data));
    if (res!=ERR_OK) { /* bit banging works, but not internalI2C? */
      for(;;){}
    }
    vTaskDelay(pdMS_TO_TICKS(5));
    /* read */
    addr = AD5252_EEMEM1 | AD5252_I2C_REG | AD5252_I2C_EE;
    data = 0; /* init */
    res = GI2C1_ReadAddress(AD5252_I2C_ADDR, &addr, sizeof(addr), &data, sizeof(data));
    if (res!=ERR_OK) { /* bit banging works, but not internalI2C? */
      for(;;){}
    }
#endif
    vTaskDelay(pdMS_TO_TICKS(100));
    LED1_Neg();
  }
}
#endif

static void ADCTask(void *pv) {
  uint8_t res;
  uint16_t val16u, val8u;
  int i;

  for(;;) {
    res = AD1_Measure(TRUE);
    if (res!=ERR_OK) {
      for(;;){}
    }
    res = AD1_GetValue16(&val16u);
    if (res!=ERR_OK) {
      for(;;){}
    }
    val8u = val16u>>8;
//    CLS1_SendNum8u(val8u, CLS1_GetStdio()->stdOut);
//    CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
#if 1
    if (AD5141_WriteRDACReg(val8u)!=ERR_OK) {
      CLS1_SendStr("FAILED writing AD5141!\r\n", CLS1_GetStdio()->stdOut);
      for(i=0;i<3;i++) {
        vTaskDelay(pdMS_TO_TICKS(100));
        LED1_Neg();
      }
      AD5141_HardwareReset(); /* reset hardware in case of failure */
    }
    if (AD5252_WriteRDACReg(AD5252_EEMEM1, val8u)!=ERR_OK) {
      CLS1_SendStr("FAILED writing AD5252!\r\n", CLS1_GetStdio()->stdOut);
      for(i=0;i<6;i++) {
        vTaskDelay(pdMS_TO_TICKS(100));
        LED1_Neg();
      }
    }
#endif
    vTaskDelay(pdMS_TO_TICKS(1000));
    LED1_Neg();
  }
}

void APP_Run(void) {
  SHELL_Init();
  WAIT1_Waitms(500); /* give hardware time to power up */
  AD5252_Init();
  AD5141_Init();
  if (xTaskCreate(ADCTask, "adc", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#if 0
  if (xTaskCreate(AD5252Task, "AD5252", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
  vTaskStartScheduler();
  for(;;) {
    LED1_Neg();
    WAIT1_Waitms(100);
  }
}

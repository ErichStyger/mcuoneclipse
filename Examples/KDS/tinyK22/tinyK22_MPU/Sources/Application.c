/*
 * Application.c
 *
 *  Created on: 25.06.2018
 *      Author: Erich Styger
 */

#include "Application.h"
#include "FRTOS1.h"
#include "LED1.h"

#if configUSE_MPU_SUPPORT
BaseType_t xPortRaisePrivilege( void ) {

}


void vPortStoreTaskMPUSettings( xMPU_SETTINGS *xMPUSettings, const struct xMEMORY_REGION * const xRegions, StackType_t *pxBottomOfStack, uint32_t ulStackDepth ) PRIVILEGED_FUNCTION {
  if (xRegions==NULL) {
    int ul;
    /* no MPU regions are defined, so allow access to everything */
    xMPUSettings->xRegion[0].ulRegionBaseAddress  = 0x08000000;
    xMPUSettings->xRegion[0].ulRegionAttribute = portMPU_REGION_READ_WRITE;
    /* Invalidate all other regions.   */
    for(ul = 1; ul < portNUM_CONFIGURABLE_REGIONS; ul++) {
      xMPUSettings->xRegion[ul].ulRegionBaseAddress = 0x00000000UL;
      xMPUSettings->xRegion[ul].ulRegionAttribute = 0UL;
    }
   } else {

  }
}
#endif

static void AppTask(void *param) {
  (void)param;
  for(;;) {
    LED1_Neg();
    vTaskDelay(pdMS_TO_TICKS(1000));
  } /* for */
}

void APP_Run(void) {
  if (xTaskCreate(AppTask, "App", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
  for(;;){}
}

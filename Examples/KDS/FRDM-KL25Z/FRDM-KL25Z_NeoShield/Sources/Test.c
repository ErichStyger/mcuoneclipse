/*
 * Test.c
 *
 *  Created on: 20.10.2014
 *      Author: tastyger
 */

#include "Test.h"
#include "PTC.h"
#include "GPIO_PDD.h"
#include "TPM_PDD.h"
#include "DMA_PDD.h"
#include "WAIT1.h"
#include "TMOUT1.h"
#include "TPM0.h"
#include "Bit2.h"
#include "NeoPixel.h"
#include "NeoLine.h"

//static int transferCntr = 50;
static portTASK_FUNCTION(TaskT0, pvParameters) {
  int i;

  (void)pvParameters; /* not used */
  for(;;) {
    NEOL_PixelTrail(0xff, 0x00, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
    NEOL_PixelTrail(0xff, 0xff, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
    NEOL_PixelTrail(0x00, 0xff, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
    NEOL_PixelTrail(0x00, 0xff, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
    NEOL_PixelTrail(0x00, 0x00, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
    NEOL_PixelTrail(0xff, 0x00, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  } /* for */
}

void Test(void) {
  NEO_Init();
  NEO_SetPixelRGB(0, 0xff, 0x00, 0x00);
  NEO_SetPixelRGB(1, 0x00, 0xFF, 0x00);
  NEO_SetPixelRGB(2, 0x00, 0x00, 0xff);
  NEO_SetPixelRGB(3, 0xff, 0x00, 0x00);
  NEO_SetPixelRGB(4, 0xff, 0x00, 0xFF);
  NEO_SetPixelRGB(5, 0xff, 0x00, 0xFF);
  NEO_SetPixelRGB(6, 0xff, 0x00, 0xFF);
  NEO_SetPixelRGB(7, 0xff, 0x00, 0xFF);
#if 0
  //for(;;) {
//#if 0
    //GPIO_PDD_TogglePortDataOutputMask(FPTC_BASE_PTR, 0xff);
    GPIO_PDD_SetPortDataOutputMask(FPTC_BASE_PTR, 0xff);
    WAIT1_Waitms(10);
    GPIO_PDD_ClearPortDataOutputMask(FPTC_BASE_PTR, 0xff);
    WAIT1_Waitms(10);

    GPIO_PDD_SetPortDataOutputMask(PTC_BASE_PTR, 0xff);
    WAIT1_Waitms(10);
    GPIO_PDD_ClearPortDataOutputMask(PTC_BASE_PTR, 0xff);
    WAIT1_Waitms(10);
//#endif
 // }
#endif
#if 0
  GPIO_PDD_SetPortDataOutput(PTC_DEVICE, 0xff);
  GPIO_PDD_SetPortDataOutput(PTC_DEVICE, 0x00);
  GPIO_PDD_SetPortDataOutput(PTC_DEVICE, 0xff);
  GPIO_PDD_SetPortDataOutput(PTC_DEVICE, 0x00);
#endif
  if (FRTOS1_xTaskCreate(TaskT0, "T0", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+3, NULL) != pdPASS) {
    for(;;){} /* error */
  }

}



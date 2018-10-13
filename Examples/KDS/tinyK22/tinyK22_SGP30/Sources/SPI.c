/*
 * SPI.c
 *
 *  Created on: 10.12.2014
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_HAS_SPI
#include "SPI.h"
#include "FRTOS1.h"
#include "SM1.h"

static SemaphoreHandle_t spiSem;

void SPI_OnSPIActivate(SPI_BaudIndex idx) {
  (void)idx;
  (void)xSemaphoreTakeRecursive(spiSem, portMAX_DELAY);
  //SM1_SetBaudRateMode(index);
  SM1_SelectConfiguration(SM1_DeviceData, 0, idx);
}

void SPI_OnSPIDeactivate(SPI_BaudIndex idx) {
  (void)idx;
  (void)xSemaphoreGiveRecursive(spiSem);
}

void SPI_Deinit(void) {
  if (spiSem!=NULL) {
    vSemaphoreDelete(spiSem);
  }
}

void SPI_Init(void) {
  spiSem = xSemaphoreCreateRecursiveMutex();
  if (spiSem==NULL) { /* creation failed? */
    for(;;);
  }
  vQueueAddToRegistry(spiSem, "SpiSem");
}

#endif /* PL_HAS_SPI */

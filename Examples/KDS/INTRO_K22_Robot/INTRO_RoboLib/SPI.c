/*
 * SPI.c
 *
 *  Created on: 10.12.2014
 *      Author: tastyger
 */

#include "Platform.h"
#if PL_HAS_SPI
#include "SPI.h"
#include "FRTOS1.h"
#include "SM1.h"

static SemaphoreHandle_t spiSem;

void SPI_OnSPIActivate(SPI_BaudIndex idx) {
  (void)idx;
  (void)FRTOS1_xSemaphoreTakeRecursive(spiSem, portMAX_DELAY);
  //SM1_SetBaudRateMode(index);
}

void SPI_OnSPIDeactivate(SPI_BaudIndex idx) {
  (void)idx;
  (void)FRTOS1_xSemaphoreGiveRecursive(spiSem);
}

void SPI_Deinit(void) {
  if (spiSem!=NULL) {
    FRTOS1_vQueueUnregisterQueue(spiSem);
    FRTOS1_vSemaphoreDelete(spiSem);
  }
}

void SPI_Init(void) {
  spiSem = FRTOS1_xSemaphoreCreateRecursiveMutex();
  if (spiSem==NULL) { /* creation failed? */
    for(;;);
  }
  FRTOS1_vQueueAddToRegistry(spiSem, "SpiSem");
}

#endif /* PL_HAS_SPI */

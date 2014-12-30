/*
 * SPIBus.c
 *
 *  Created on: 29.12.2014
 *      Author: Erich Styger
 */

#include "SPIBus.h"
#include "FRTOS1.h"

static SemaphoreHandle_t spiSem;

void SPIBus_OnActivate(void) {
  FRTOS1_xSemaphoreTakeRecursive(spiSem, portMAX_DELAY);
}

void SPIBus_OnDeactivate(void) {
  FRTOS1_xSemaphoreGiveRecursive(spiSem);
}

void SPIBus_Deinit(void) {
  if (spiSem!=NULL) {
    FRTOS1_vQueueUnregisterQueue(spiSem);
    FRTOS1_vSemaphoreDelete(spiSem);
  }
}

void SPIBus_Init(void) {
  spiSem = FRTOS1_xSemaphoreCreateRecursiveMutex();
  if (spiSem==NULL) { /* creation failed? */
    for(;;);
  }
  FRTOS1_vQueueAddToRegistry(spiSem, "SpiSem");
}

/*
 * SPI.c
 *
 *  Created on: Apr 23, 2014
 *      Author: tastyger
 */

#include "Platform.h"
#include "SM1.h"
#include "FRTOS1.h"

static volatile bool SPI_DataReceivedFlag = FALSE;
static xSemaphoreHandle SPI_mutex = NULL; /* Semaphore to protect SPI access */

void SPI_RequestSPIBus(void) {
  (void)FRTOS1_xSemaphoreTakeRecursive(SPI_mutex, portMAX_DELAY);
}

void SPI_ReleaseSPIBus(void) {
  (void)FRTOS1_xSemaphoreGiveRecursive(SPI_mutex);
}

void SPI_OnBlockReceived(LDD_TUserData *UserDataPtr) {
  (void)UserDataPtr;
  SPI_DataReceivedFlag = TRUE;
}


void SPI_WriteByte(unsigned char write) {
  unsigned char dummy;

  SPI_DataReceivedFlag = FALSE;
  (void)SM1_ReceiveBlock(SM1_DeviceData, &dummy, sizeof(dummy));
  (void)SM1_SendBlock(SM1_DeviceData, &write, sizeof(write));
  while(!SPI_DataReceivedFlag){}
}

uint8_t SPI_ReadByte(void) {
  uint8_t val, write = 0xff; /* dummy */
  
  SPI_DataReceivedFlag = FALSE;
  (void)SM1_ReceiveBlock(SM1_DeviceData, &val, 1);
  (void)SM1_SendBlock(SM1_DeviceData, &write, 1);
  while(!SPI_DataReceivedFlag){}
  return val;
}

void SPI_Init(void) {
  SPI_mutex = FRTOS1_xSemaphoreCreateRecursiveMutex();
}

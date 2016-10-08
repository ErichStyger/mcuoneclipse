#include <stdint.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include <tool.h>
#include "GI2C1.h"
#include "VEN.h"

#define NXPNCI_I2C_ADDR_7BIT    (0x28)
SemaphoreHandle_t IrqSem = NULL;

typedef enum {ERROR = 0, SUCCESS = !ERROR} Status;

void PORTC_IRQHandler(void)
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  xSemaphoreGiveFromISR(IrqSem, &xHigherPriorityTaskWoken);
}

static Status I2C_WRITE(uint8_t *pBuff, uint16_t buffLen)
{
  uint8_t res;

  GI2C1_SelectSlave(NXPNCI_I2C_ADDR_7BIT);
  res = GI2C1_WriteBlock(pBuff, buffLen, GI2C1_SEND_STOP);
  GI2C1_UnselectSlave();
  if (res==ERR_OK) {
    return SUCCESS;
  }
  return ERROR;
}

static Status I2C_READ(uint8_t *pBuff, uint16_t buffLen)
{
  uint8_t res;

  GI2C1_SelectSlave(NXPNCI_I2C_ADDR_7BIT);
  res = GI2C1_ReadBlock(pBuff, buffLen, GI2C1_SEND_STOP);
  GI2C1_UnselectSlave();
  if (res==ERR_OK) {
    return SUCCESS;
  }
  return ERROR;
}

static Status tml_Init(void) {
    IrqSem = xSemaphoreCreateBinary();
    return SUCCESS;
}

static Status tml_Reset(void) {
  VEN_ClrVal();
  Sleep(10);
  VEN_SetVal();
  Sleep(10);
	return SUCCESS;
}

static Status tml_Tx(uint8_t *pBuff, uint16_t buffLen) {
  if (I2C_WRITE(pBuff, buffLen) != SUCCESS)
  {
    Sleep(10);
    if(I2C_WRITE(pBuff, buffLen) != SUCCESS)
    {
      return ERROR;
    }
  }
	return SUCCESS;
}

static Status tml_Rx(uint8_t *pBuff, uint16_t buffLen, uint16_t *pBytesRead) {
  if(I2C_READ(pBuff, 3) == SUCCESS)
  {
    if ((pBuff[2] + 3) <= buffLen)
    {
    if (pBuff[2] > 0)
    {
      if(I2C_READ(&pBuff[3], pBuff[2]) == SUCCESS)
      {
        *pBytesRead = pBuff[2] + 3;
      }
      else return ERROR;
    } else
    {
      *pBytesRead = 3;
    }
    }
  else return ERROR;
 }
  else return ERROR;
	return SUCCESS;
}

static Status tml_WaitForRx(uint32_t timeout) {
	if (xSemaphoreTake(IrqSem, (timeout==0)?(portMAX_DELAY):(portTICK_PERIOD_MS*timeout)) != pdTRUE) return ERROR;
	return SUCCESS;
}

void tml_Connect(void) {
	tml_Init();
	tml_Reset();
}

void tml_Send(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytesSent) {
	if(tml_Tx(pBuffer, BufferLen) == ERROR) *pBytesSent = 0;
	else *pBytesSent = BufferLen;
}

void tml_Receive(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytes, uint16_t timeout) {
	if (tml_WaitForRx(timeout) == ERROR) *pBytes = 0;
	else tml_Rx(pBuffer, BufferLen, pBytes);
}


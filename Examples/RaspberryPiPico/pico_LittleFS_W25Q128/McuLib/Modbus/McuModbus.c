/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuModbus.h"
#if McuModbus_CONFIG_IS_ENABLED
#include <stddef.h>
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuUart485.h"
#include "McuLog.h"

#define McuModbus_TELEGRAM_SIZE   (8)

#if McuModbus_CONFIG_USE_MUTEX
  static SemaphoreHandle_t McuModbus_Mutex = NULL; /* Semaphore to protect bus access */
#endif

#if McuModbus_CONFIG_USE_MUTEX
static bool McuModbus_RequestBus(void) {
  return xSemaphoreTakeRecursive(McuModbus_Mutex, portMAX_DELAY)==pdPASS;
}
#endif

#if McuModbus_CONFIG_USE_MUTEX
static void McuModbus_ReleaseBus(void) {
  (void)xSemaphoreGiveRecursive(McuModbus_Mutex);
}
#endif

static uint16_t McuModbus_CRC(uint8_t *buf, size_t len) {
  uint16_t crc = 0xFFFF;

  for(int pos=0; pos<len; pos++) {
    crc ^= (uint16_t)buf[pos];
    for (int i=8; i>0; i--) {
      if ((crc&0x1)!=0) {
        crc >>= 1;
        crc ^= 0xA001;
      } else {
        crc >>= 1;
      }
    }
  }
  return crc;
}

static void McuModbus_CreateReadTelegram(uint8_t telegram[McuModbus_TELEGRAM_SIZE], uint8_t slaveId, McuModbus_Func_Code_e function, uint16_t addr, uint16_t nofCoils) {
  telegram[0] = slaveId;
  telegram[1] = function;
  telegram[2] = addr>>8;
  telegram[3] = addr&0xff;
  telegram[4] = nofCoils>>8;
  telegram[5] = nofCoils&0xff;
  uint16_t crc = McuModbus_CRC(telegram, 6);
  telegram[6] = crc&0xff;
  telegram[7] = crc>>8;
}

static void McuModbus_CreateWriteTelegram(uint8_t telegram[McuModbus_TELEGRAM_SIZE], uint8_t slaveId, McuModbus_Func_Code_e function, uint16_t addr, uint16_t data) {
  telegram[0] = slaveId;
  telegram[1] = function;
  telegram[2] = addr>>8;
  telegram[3] = addr&0xff;
  telegram[4] = data>>8;
  telegram[5] = data&0xff;
  uint16_t crc = McuModbus_CRC(telegram, 6);
  telegram[6] = crc&0xff;
  telegram[7] = crc>>8;
}

static void McuModbus_SendTelegram(uint8_t *telegram, size_t size) {
  McuUart485_ClearRxQueue(); /* clear queue just in case */
  McuUart485_SendBlock(telegram, size); /* send telegram */
}

static uint8_t McuModbus_ReceiveResponseInputRegister(uint8_t deviceID, McuModbus_Func_Code_e function, uint16_t *regs, uint16_t nofRegs, int timeoutMs) {
  unsigned char response[32]; /* minimum of 5 bytes + nofRegs*2 */
  int i;

  if (5+nofRegs*sizeof(uint16_t)>sizeof(response)) {
    return ERR_OVERFLOW; /* response buffer size too small */
  }
  i = 0;
  memset(regs, 0, nofRegs/sizeof(uint16_t)); /* clear response buffer */
  while(i<sizeof(response) && i<(5+nofRegs*sizeof(uint16_t)) && timeoutMs>0) {
    if (McuUart485_GetRxQueueByte(&response[i], pdMS_TO_TICKS(McuModbus_CONFIG_QUEUE_RX_TIMEOUT_MS))==ERR_OK) {
      i++;
    } else { /* timeout */
      timeoutMs -= McuModbus_CONFIG_QUEUE_RX_TIMEOUT_MS; /* queue waiting time */
      if (timeoutMs<0) {
        return ERR_IDLE; /* timeout */
      }
    }
  }
  /* check response, see https://www.simplymodbus.ca/FC04.htm */
  if (i!=5+nofRegs*sizeof(uint16_t)) { /* 1: slave addr, 1: function code, 1: nof bytes, nofData*2, 2: CRC */
    return ERR_FAILED; /* response size does not match */
  }
  if (response[0]!=deviceID) {
    return ERR_FAILED; /* response ID does not match */
  }
  if (response[1]!=function) {
    return ERR_FAILED; /* response function code does not match */
  }
  if (response[2]!=nofRegs*sizeof(uint16_t)) {
    return ERR_FAILED; /* number of bytes does not match expectation */
  }
  uint16_t crc = (response[4+nofRegs*sizeof(uint16_t)]<<8)+response[3+nofRegs*sizeof(uint16_t)];
  if (crc!=McuModbus_CRC(response, 3+nofRegs*sizeof(uint16_t))) {
    return ERR_CRC; /* CRC does not match */
  }
  for(int i=0; i<nofRegs; i++) {
    regs[i] = (response[3+i*sizeof(uint16_t)]<<8)+response[4+i*sizeof(uint16_t)];
  }
  return ERR_OK;
}

static uint8_t McuModbus_ReadRegister(uint8_t deviceID, McuModbus_Func_Code_e function, uint16_t addr, uint16_t nofRegs, uint16_t *result) {
  uint8_t telegram[McuModbus_TELEGRAM_SIZE];
  uint8_t res;

  McuModbus_CreateReadTelegram(telegram, deviceID, function, addr, nofRegs);
#if McuModbus_CONFIG_USE_MUTEX
  if (McuModbus_RequestBus()) {
#endif
    McuModbus_SendTelegram(telegram, sizeof(telegram));
    res = McuModbus_ReceiveResponseInputRegister(deviceID, function, result, nofRegs, McuModbus_CONFIG_RX_TIMEOUT_MS);
    vTaskDelay(pdMS_TO_TICKS(McuModbus_CONFIG_BUS_WAIT_TIME_MS));
#if McuModbus_CONFIG_USE_MUTEX
    McuModbus_ReleaseBus();
  }
#endif
  return res;
}

static uint8_t McuModbus_WriteRegister(uint8_t deviceID, McuModbus_Func_Code_e function, uint16_t addr, uint16_t value) {
  uint8_t telegram[McuModbus_TELEGRAM_SIZE];

  McuModbus_CreateWriteTelegram(telegram, deviceID, function, addr, value);
#if McuModbus_CONFIG_USE_MUTEX
  if (McuModbus_RequestBus()) {
#endif
    McuModbus_SendTelegram(telegram, sizeof(telegram));
    vTaskDelay(pdMS_TO_TICKS(McuModbus_CONFIG_BUS_WAIT_TIME_MS));
#if McuModbus_CONFIG_USE_MUTEX
    McuModbus_ReleaseBus();
  }
#endif
  return ERR_OK;
}

uint8_t McuModbus_ReadInputRegisters(uint8_t deviceID, uint16_t addr, uint16_t nofRegs, uint16_t *result) {
  return McuModbus_ReadRegister(deviceID, McuModbus_Func_ReadInputRegisters, addr, nofRegs, result);
}

uint8_t McuModbus_ReadHoldingRegisters(uint8_t deviceID, uint16_t addr, uint16_t nofRegs, uint16_t *result) {
  return McuModbus_ReadRegister(deviceID, McuModbus_Func_ReadHoldingRegisters, addr, nofRegs, result);
}

uint8_t McuModbus_WriteHoldingRegister(uint8_t deviceID, uint16_t addr, uint16_t value) {
  return McuModbus_WriteRegister(deviceID, McuModbus_Func_WriteSingleRegister, addr, value);
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  McuShell_SendStatusStr((unsigned char*)"McuModbus", (unsigned char*)"Modbus settings\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"McuModbus", (unsigned char*)"Group of McuModbus commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t McuModbus_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "McuModbus help")==0) {
    *handled = true;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "McuModbus status")==0)) {
    *handled = true;
    return PrintStatus(io);
  }
  return ERR_OK;
}

void McuModbus_Deinit(void) {
#if McuModbus_CONFIG_USE_MUTEX
  vSemaphoreDelete(McuModbus_Mutex);
  McuModbus_Mutex = NULL;
#endif
}

void McuModbus_Init(void) {
#if McuModbus_CONFIG_USE_MUTEX
  McuModbus_Mutex = xSemaphoreCreateRecursiveMutex();
  if (McuModbus_Mutex==NULL) { /* semaphore creation failed */
    McuLog_fatal("failed creating mutex");
    for(;;) {} /* error, not enough memory? */
  }
  vQueueAddToRegistry(McuModbus_Mutex, "McuModbus_Mutex");
#endif
}

#endif /* McuModbus_CONFIG_IS_ENABLED */

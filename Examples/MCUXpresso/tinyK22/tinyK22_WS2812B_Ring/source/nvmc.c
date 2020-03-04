/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_NVMC
#include <string.h>
#include "nvmc.h"
#if McuLib_CONFIG_CPU_IS_LPC  /* LPC845-BRK */
  #include "fsl_iap.h"
#elif McuLib_CONFIG_CPU_IS_KINETIS /* K22FN512 */
  #include "fsl_flash.h"
#endif
#include "McuLib.h"
#include "McuUtility.h"
#include "Shell.h"

/* Note: the flash memory has been reduced for the linker file (project settings, managed linker file) */
#if McuLib_CONFIG_CPU_IS_LPC  /* LPC845-BRK */
  #define FLASH_NVM_ADDR_START      (0xFC00) /* LPC845 has 64k FLASH (0x10000), last 1k page is used for NVM */
  #define FLASH_NVM_SECTOR_START    (FLASH_NVM_ADDR_START/1024) /* sector size is 1k */
#elif McuLib_CONFIG_CPU_IS_KINETIS /* K22FN512 */
  #define FLASH_NVM_ADDR_START    ((0+0x80000)-FLASH_NVM_BLOCK_SIZE) /* last block in FLASH, start address of configuration data in flash */
  #define FLASH_NVM_BLOCK_SIZE    0x1000
  /*! @brief Flash driver Structure */
  static flash_config_t s_flashDriver;
#endif

static uint8_t NVMC_Erase(void) {
#if McuLib_CONFIG_CPU_IS_LPC  /* LPC845-BRK */
  uint32_t startSector = FLASH_NVM_SECTOR_START; /* sector is 1k in size */
  uint32_t endSector = FLASH_NVM_SECTOR_START;
  status_t res;

  res = IAP_BlankCheckSector(startSector, endSector);
  if (res==kStatus_IAP_Success) { /* already erased */
    return ERR_OK;
  }
  /* erase sector */
  res = IAP_PrepareSectorForWrite(startSector, endSector);
  if (res!=kStatus_IAP_Success) {
    return ERR_FAILED;
  }
  res = IAP_EraseSector(startSector, endSector, SystemCoreClock);
  if (res!=kStatus_IAP_Success) {
    return ERR_FAILED;
  }
  res = IAP_BlankCheckSector(startSector, endSector);
  if (res!=kStatus_IAP_Success) {
    return ERR_FAILED;
  }
#elif McuLib_CONFIG_CPU_IS_KINETIS /* K22FN512 */
  uint32_t pflashSectorSize = 0;
  status_t status;

  /* erase */
  FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0SectorSize, &pflashSectorSize);
  status = FLASH_Erase(&s_flashDriver, FLASH_NVM_ADDR_START, pflashSectorSize, kFTFx_ApiEraseKey);
  if (status!=kStatus_FTFx_Success) {
    return ERR_FAILED;
  }
  /* Verify sector if it's been erased. */
  status = FLASH_VerifyErase(&s_flashDriver, FLASH_NVM_ADDR_START, pflashSectorSize, kFTFx_MarginValueUser);
  if (status!=kStatus_FTFx_Success) {
    return ERR_FAILED;
  }
#endif
  return ERR_OK;
}

#if McuLib_CONFIG_CPU_IS_KINETIS /* K22FN512 */
uint8_t NVMC_SetBlockFlash(uint32_t addr, void *data, size_t dataSize) {
  static uint32_t buf[FLASH_NVM_BLOCK_SIZE/4]; /* backup buffer */
  int i;
  status_t status;
  uint8_t *p, *q;

  /* make backup of current content */
  for(i=0;i<sizeof(buf)/4; i++) {
    buf[i] = ((uint32_t*)FLASH_NVM_ADDR_START)[i];
  }
  if (NVMC_Erase()!=ERR_OK) {
    return ERR_FAILED;
  }
  /* copy new data into backup */
  p = ((uint8_t*)buf)+(addr-FLASH_NVM_ADDR_START);
  q = (uint8_t*)data;
  for(i=0;i<dataSize; i++) {
    *p = *q;
    p++; q++;
  }
  status = FLASH_Program(&s_flashDriver, FLASH_NVM_ADDR_START, (uint8_t*)buf, sizeof(buf));
  if (status!=kStatus_FTFx_Success) {
    return ERR_FAILED;
  }
  return ERR_OK;
}
#endif

uint8_t NVMC_WriteConfig(NVMC_Data_t *data) {
#if McuLib_CONFIG_CPU_IS_LPC  /* LPC845-BRK */
  uint32_t startSector = FLASH_NVM_SECTOR_START;
  uint32_t endSector = FLASH_NVM_SECTOR_START;
  status_t res;

  if (NVMC_Erase()!=ERR_OK) {
    return ERR_FAILED;
  }
  res = IAP_PrepareSectorForWrite(startSector, endSector);
  if (res!=kStatus_IAP_Success) {
    return ERR_FAILED;
  }
  /* destination address should be on a 64byte boundary.
   * Source address should be word (4byte) boundary
   * data size (number of bytes) shall be 64, 128, 256, 512, 1024 bytes */
  res = IAP_CopyRamToFlash(FLASH_NVM_ADDR_START, (uint32_t*)data, sizeof(NVMC_Data_t), SystemCoreClock);
  if (res!=kStatus_IAP_Success) {
    return ERR_FAILED;
  }
  res = IAP_Compare(FLASH_NVM_ADDR_START, (uint32_t*)data, sizeof(NVMC_Data_t));
  if (res!=kStatus_IAP_Success) {
    return ERR_FAILED;
  }
#elif McuLib_CONFIG_CPU_IS_KINETIS /* K22FN512 */
  return NVMC_SetBlockFlash(FLASH_NVM_ADDR_START, (uint32_t*)data, sizeof(NVMC_Data_t));
#endif
  return ERR_OK;
}

static uint8_t NVMC_InitConfig(void) {
  NVMC_Data_t data;

  if (NVMC_Erase()!=ERR_OK) {
    return ERR_FAILED;
  }
  memset(&data, 0, sizeof(data)); /* initialize data */
  data.version = NVMC_VERSION_1_0;
#if PL_CONFIG_IS_MASTER
  data.addrRS485 = 0x01;
#else
  data.addrRS485 = 0x0A;
#endif
  for (int i=0; i<sizeof(data.zeroOffsets)/sizeof(data.zeroOffsets[0]); i++) {
    for(int j=0; j<sizeof(data.zeroOffsets[0])/sizeof(data.zeroOffsets[0][0]); j++) {
      data.zeroOffsets[i][j] = 0; /* default offset */
    }
  }
  return NVMC_WriteConfig(&data);
}

static bool isErased(const uint8_t *ptr, int nofBytes) {
  while (nofBytes>0) {
    if (*ptr!=0xFF) {
      return false; /* byte not erased */
    }
    ptr++;
    nofBytes--;
  }
  return true;
}

bool NVMC_IsErased(void) {
  return isErased((uint8_t*)FLASH_NVM_ADDR_START, sizeof(NVMC_Data_t));
}

const NVMC_Data_t *NVMC_GetDataPtr(void) {
  if (NVMC_IsErased()) {
    return NULL;
  }
  return (const NVMC_Data_t *)FLASH_NVM_ADDR_START;
}

uint8_t NVMC_GetRS485Addr(void) {
  const NVMC_Data_t *data;

  data = NVMC_GetDataPtr();
  if (data!=NULL) {
    return data->addrRS485;
  }
  return 0x1; /* default */
}

int16_t NVMC_GetStepperZeroOffset(uint8_t clock, uint8_t motor) {
  const NVMC_Data_t *data;

  data = NVMC_GetDataPtr();
  if (data!=NULL) {
    return data->zeroOffsets[clock][motor];
  }
  return 0; /* default */
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  const NVMC_Data_t *data;
  uint8_t buf[24];

  McuShell_SendStatusStr((unsigned char*)"nvmc", (unsigned char*)"Non-volatile memory configuration area\r\n", io->stdOut);
  if (NVMC_IsErased()) {
    McuShell_SendStatusStr((unsigned char*)"  Version", (unsigned char*)"ERASED\r\n", io->stdOut);
    return ERR_OK;
  } else {
    data = NVMC_GetDataPtr();

    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"V");
    McuUtility_strcatNum32u(buf, sizeof(buf), data->version/10);
    McuUtility_chcat(buf, sizeof(buf), '.');
    McuUtility_strcatNum32u(buf, sizeof(buf), data->version%10);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    McuShell_SendStatusStr((unsigned char*)"  version", buf, io->stdOut);

    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"addr: 0x");
    McuUtility_strcatNum8Hex(buf, sizeof(buf), data->addrRS485);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    McuShell_SendStatusStr((unsigned char*)"  RS-458", buf, io->stdOut);
#if PL_CONFIG_USE_STEPPER
    uint8_t status[12];

    for (int i=0; i<sizeof(data->zeroOffsets)/sizeof(data->zeroOffsets[0]); i++) {
      buf[0] = '\0';
      for(int j=0; j<sizeof(data->zeroOffsets[0])/sizeof(data->zeroOffsets[0][0]); j++) {
        McuUtility_strcatNum16sFormatted(buf, sizeof(buf), data->zeroOffsets[i][j], ' ', 5);
        McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" ");
      }
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
      McuUtility_strcpy(status, sizeof(status), (unsigned char*)"  offset[");
      McuUtility_strcatNum16s(status, sizeof(status), i);
      McuUtility_strcat(status, sizeof(status), (unsigned char*)"]");
      McuShell_SendStatusStr(status, buf, io->stdOut);
    }
#endif
  }
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"nvmc", (unsigned char*)"Group of NVMC commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  erase", (unsigned char*)"Erase configuration area\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  init", (unsigned char*)"Erase and initialize configuration area\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t NVMC_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "nvmc help")==0) {
    *handled = true;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "nvmc status")==0)) {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "nvmc erase")==0) {
    *handled = true;
    return NVMC_Erase();
  } else if (McuUtility_strcmp((char*)cmd, "nvmc init")==0) {
    *handled = true;
    return NVMC_InitConfig();
  }
  return ERR_OK;
}

void NVMC_Deinit(void) {
  /* nothing needed */
}

void NVMC_Init(void){
#if McuLib_CONFIG_CPU_IS_KINETIS
  status_t result;    /* Return code from each flash driver function */

  memset(&s_flashDriver, 0, sizeof(flash_config_t));
  /* Setup flash driver structure for device and initialize variables. */
  result = FLASH_Init(&s_flashDriver);
  if (result!=kStatus_FTFx_Success) {
   for(;;) { /* error */ }
  }
#endif
  if(sizeof(NVMC_Data_t) != 64) {
    /* data size (number of bytes) shall be 64, 128, 256, 512, 1024 bytes */
    SHELL_SendString((unsigned char*)"FATAL: wrong size of NVMC_Data_t!\r\n");
    for(;;) {}
  }
  if (NVMC_IsErased()) { /* Flash erased? */
    if (NVMC_InitConfig()!=ERR_OK) { /* initialize it first */
    #if PL_CONFIG_USE_SHELL
      SHELL_SendString((unsigned char*)"FATAL: NVMC_InitConfig() failed!\r\n");
    #endif
      for(;;) {}
    }
  }
}

#endif /* PL_CONFIG_USE_NVMC */

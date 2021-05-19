/*
 * Copyright (c) 2019, 2020, 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "nvmc.h"
#include <string.h>
#if McuLib_CONFIG_CPU_IS_LPC  /* LPC845-BRK */
  #include "fsl_iap.h"
#elif McuLib_CONFIG_CPU_IS_KINETIS /* K22FN512 */
  #include "fsl_flash.h"
  #include "fsl_smc.h"
  #include "McuWait.h"
#endif
#include "McuLib.h"
#include "McuUtility.h"
#include "Shell.h"
#include "McuLog.h"

#if PL_CONFIG_USE_NVMC
/* Note: the flash memory has been reduced for the linker file (project settings, managed linker file) */
#if McuLib_CONFIG_CPU_IS_LPC &&  McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845
  #define FLASH_NVM_ADDR_START      (0xFC00) /* LPC845 has 64k FLASH (0x10000), last 1k page is used for NVM */
  #define FLASH_NVM_SECTOR_START    (FLASH_NVM_ADDR_START/1024) /* sector size is 1k */
#elif McuLib_CONFIG_CPU_IS_LPC &&  McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16
  #define FLASH_NVM_ADDR_START      ((0+244*1024)-FLASH_NVM_BLOCK_SIZE) /* last block in FLASH, start address of configuration data in flash */
  #define FLASH_NVM_BLOCK_SIZE      0x200 /* must match FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0SectorSize, &pflashSectorSize) */
#elif McuLib_CONFIG_CPU_IS_KINETIS
  #define FLASH_NVM_ADDR_START      ((0+512*1024)-FLASH_NVM_BLOCK_SIZE) /* last block in FLASH, start address of configuration data in flash */
  #define FLASH_NVM_BLOCK_SIZE      0x800 /* must match FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0SectorSize, &pflashSectorSize) */
#else
  #error "Unknown MCU!"
#endif

#if PL_CONFIG_USE_NVMC
/*! @brief Flash driver Structure */
#if McuLib_CONFIG_CPU_IS_LPC &&  McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845
  /* nothing needed */
#elif McuLib_CONFIG_CPU_IS_KINETIS
  static flash_config_t s_flashDriver;
#elif McuLib_CONFIG_CPU_IS_LPC55xx
  static flash_config_t s_flashDriver;
#endif
#endif
#endif /* PL_CONFIG_USE_NVMC */

#if PL_CONFIG_USE_NVMC
bool NVMC_HasValidConfig(void) {
  const NVMC_Data_t *data;

  data = NVMC_GetDataPtr();
  return data != NULL && data->version == NVMC_CURRENT_VERSION;
}
#endif

#if PL_CONFIG_USE_NVMC
static bool isErased(const uint8_t *ptr, int nofBytes) {
#if McuLib_CONFIG_CPU_IS_LPC55xx
  /* see https://community.nxp.com/t5/LPC-Microcontrollers-Knowledge/LPC55xx-Erased-Memory-State-0-or-1/ta-p/1135084 */
  status_t status;

  status = FLASH_VerifyErase(&s_flashDriver, (uint32_t)ptr, FLASH_NVM_BLOCK_SIZE);
  return status==kStatus_Success;
#else
  while (nofBytes>0) {
    if (*ptr!=0xFF) {
      return false;  /* byte not erased */
    }
    ptr++;
    nofBytes--;
  }
  return true;
#endif
}
#endif

#if PL_CONFIG_USE_NVMC
bool NVMC_IsErased(void) {
  return isErased((uint8_t*)FLASH_NVM_ADDR_START, sizeof(NVMC_Data_t));
}
#endif

#if PL_CONFIG_USE_NVMC
const NVMC_Data_t *NVMC_GetDataPtr(void) {
  if (NVMC_IsErased()) {
    return NULL;
  }
  return (const NVMC_Data_t *)FLASH_NVM_ADDR_START;
}
#endif

#if PL_CONFIG_USE_NVMC
uint32_t NVMC_GetFlags(void) {
  const NVMC_Data_t *data;

  if (!NVMC_HasValidConfig()) {
    McuLog_error("no valid NVMC configuration, returning 0");
    return 0;
  }
  data = NVMC_GetDataPtr();
  if (data!=NULL) {
    return data->flags;
  }
  McuLog_error("NVMC does not exist, returning 0");
  return 0; /* default */
}
#endif

#if PL_CONFIG_USE_NVMC
static uint8_t NVMC_SetFlags(uint32_t flags) {
  NVMC_Data_t data;

  if (NVMC_IsErased()) {
    McuLog_error("FLASH is erased, initialize it first!");
    return ERR_FAILED;
  }
  data = *NVMC_GetDataPtr(); /* struct copy */
  data.flags = flags;
  if (NVMC_WriteConfig(&data)!=ERR_OK) {
    McuLog_error("Failed writing configuration!");
    return ERR_FAILED;
  }
  return ERR_OK;
}
#endif

#if PL_CONFIG_USE_NVMC
static uint8_t NVMC_Erase(void) {
#if McuLib_CONFIG_CPU_IS_LPC &&  McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845 /* LPC845-BRK */
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
  return ERR_OK;
#elif McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC55xx
  status_t status;
  uint8_t res = ERR_OK;
  uint32_t PflashBlockSize = 0;

#if McuLib_CONFIG_CPU_IS_KINETIS
  if (NVMC_IsErased()) { /* already eased? */
    return ERR_OK; /* yes, nothing to do */
  }
#endif
#if McuLib_CONFIG_CPU_IS_KINETIS
  /* need to switch to normal RUN mode for flash programming,
   * with Fcore=60MHz Fbus=Fflash=20MHz
   * see https://community.nxp.com/thread/377633
   */
  status = SMC_SetPowerModeRun(SMC);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  McuWait_Waitms(1); /* give time to switch clock, otherwise flash programming might fail below */
#endif
  /* erase */
#if McuLib_CONFIG_CPU_IS_KINETIS
  status = FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0SectorSize, &PflashBlockSize);
#elif McuLib_CONFIG_CPU_IS_LPC55xx
  status = FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflashPageSize, &PflashBlockSize);
#endif
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  if (PflashBlockSize!=FLASH_NVM_BLOCK_SIZE) {
    return ERR_FAILED;
  }
  for(;;) { /* breaks, switch back to HSRUN if things fail */
  #if McuLib_CONFIG_CPU_IS_KINETIS && (PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K02FN64 || PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K02FN128)
    uint32_t primask = DisableGlobalIRQ(); /* workaround: need to disable interrupts? */
  #endif
  #if McuLib_CONFIG_CPU_IS_KINETIS
    status = FLASH_Erase(&s_flashDriver, FLASH_NVM_ADDR_START, PflashBlockSize, kFTFx_ApiEraseKey);
  #elif McuLib_CONFIG_CPU_IS_LPC55xx
    status = FLASH_Erase(&s_flashDriver, FLASH_NVM_ADDR_START, PflashBlockSize, kFLASH_ApiEraseKey);
  #endif
    if (status!=kStatus_Success ) {
      res = ERR_FAILED;
  #if McuLib_CONFIG_CPU_IS_KINETIS && (PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K02FN64 || PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K02FN128)
      EnableGlobalIRQ(primask); /* workaround: need to disable interrupts? */
  #endif
      break;
    }
  #if McuLib_CONFIG_CPU_IS_KINETIS && (PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K02FN64 || PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K02FN128)
    EnableGlobalIRQ(primask); /* workaround: need to disable interrupts? */
  #endif
    /* Verify sector if it's been erased. */
#if McuLib_CONFIG_CPU_IS_KINETIS
    status = FLASH_VerifyErase(&s_flashDriver, FLASH_NVM_ADDR_START, PflashBlockSize, kFTFx_MarginValueUser);
#elif McuLib_CONFIG_CPU_IS_LPC55xx
    status = FLASH_VerifyErase(&s_flashDriver, FLASH_NVM_ADDR_START, PflashBlockSize);
#else
  #error
#endif
    if (status!=kStatus_Success) {
      res = ERR_FAILED;
      break;
    }
    break;
  } /* for */
#if McuLib_CONFIG_CPU_IS_KINETIS
  status = SMC_SetPowerModeHsrun(SMC);
  if (status!=kStatus_Success) {
    res = ERR_FAILED;
  }
#endif
  return res;
#endif
}

#if McuLib_CONFIG_CPU_IS_KINETIS /* K22FN512 */
uint8_t NVMC_SetBlockFlash(uint32_t addr, void *data, size_t dataSize) {
  static uint32_t NVMC_SetBlockFlashBuffer[FLASH_NVM_BLOCK_SIZE/32/4]; /* backup buffer */
  int i;
  status_t status;
  uint8_t *p, *q;
  uint8_t res = ERR_OK;

  /* make backup of current content */
  for(i=0;i<sizeof(NVMC_SetBlockFlashBuffer)/4; i++) {
    NVMC_SetBlockFlashBuffer[i] = ((uint32_t*)FLASH_NVM_ADDR_START)[i];
  }

  if (NVMC_Erase()!=ERR_OK) {
    return ERR_FAILED;
  }
  /* copy new data into backup */
  p = ((uint8_t*)NVMC_SetBlockFlashBuffer)+(addr-FLASH_NVM_ADDR_START);
  q = (uint8_t*)data;
  for(i=0;i<dataSize; i++) {
    *p = *q;
    p++; q++;
  }
#if PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K22FN512 || PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K02FN64 || PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K02FN128
  /* need to switch to normal RUN mode for flash programming,
   * with Fcore=60MHz Fbus=Fflash=20MHz
   * see https://community.nxp.com/thread/377633
   */
  status = SMC_SetPowerModeRun(SMC);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  McuWait_Waitms(1); /* give time to switch clock, otherwise flash programming might fail below */
#endif
  /* program */
#if PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K02FN64 || PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K02FN128
    uint32_t primask = DisableGlobalIRQ(); /* workaround: need to disable interrupts? */
#endif
  for(;;) { /* breaks, switch back to HSRUN if things fail */
    status = FLASH_Program(&s_flashDriver, FLASH_NVM_ADDR_START, (uint8_t*)NVMC_SetBlockFlashBuffer, sizeof(NVMC_SetBlockFlashBuffer));
    if (status!=kStatus_FTFx_Success) {
      res = ERR_FAILED;
      break;
    }
    break;
  } /* for */
#if PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K02FN64 || PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K02FN128
    EnableGlobalIRQ(primask); /* workaround: need to disable interrupts? */
#endif
#if PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K22FN512 || PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K02FN64 || PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K02FN128
  status = SMC_SetPowerModeHsrun(SMC);
  if (status!=kStatus_Success) {
    res = ERR_FAILED;
  }
#endif
  return res;
}
#endif

uint8_t NVMC_WriteConfig(NVMC_Data_t *data) {
#if McuLib_CONFIG_CPU_IS_LPC &&  McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845
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
#elif McuLib_CONFIG_CPU_IS_LPC55xx
  status_t status;
  uint32_t failedAddress, failedData;

  if (NVMC_Erase()!=ERR_OK) {
    return ERR_FAILED;
  }
  status = FLASH_Program(&s_flashDriver, FLASH_NVM_ADDR_START, (uint8_t*)data, sizeof(NVMC_Data_t));
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  status = FLASH_VerifyProgram(&s_flashDriver, FLASH_NVM_ADDR_START, sizeof(NVMC_Data_t), (const uint8_t *)data, &failedAddress, &failedData);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
#elif McuLib_CONFIG_CPU_IS_KINETIS /* K22FN512 or K02FN64 */
  if (NVMC_Erase()!=ERR_OK) {
    return ERR_FAILED;
  }
  return NVMC_SetBlockFlash(FLASH_NVM_ADDR_START, (uint32_t*)data, sizeof(NVMC_Data_t));
#endif
  return ERR_OK;
}

static uint8_t NVMC_InitConfig(void) {
  NVMC_Data_t data;

  memset(&data, 0, sizeof(data)); /* initialize data */
  data.version = NVMC_CURRENT_VERSION;
  data.flags = 0;
  data.flags |= NVMC_FLAGS_MAGNET_ENABLED;
  return NVMC_WriteConfig(&data);
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  const NVMC_Data_t *data;
  uint8_t buf[64];

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

    uint32_t flags;

    flags = NVMC_GetFlags();
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
    McuUtility_strcatNum32Hex(buf, sizeof(buf), flags);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" mag: ");
    if (flags&NVMC_FLAGS_MAGNET_ENABLED) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"1");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"0");
    }
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    McuShell_SendStatusStr((unsigned char*)"  flags", buf, io->stdOut);
  }
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"nvmc", (unsigned char*)"Group of NVMC commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  erase", (unsigned char*)"Erase configuration area\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  init", (unsigned char*)"Erase and initialize configuration area\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  flags <val>", (unsigned char*)"Set flags\r\n", io->stdOut);
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
  } else if (McuUtility_strncmp((char*)cmd, "nvmc flags", sizeof("nvmc flags")-1)==0) {
    *handled = true;
    const unsigned char *p;
    int32_t val;

    p = cmd + sizeof("nvmc flags ")-1;
    if (McuUtility_xatoi(&p, &val)==ERR_OK) {
       return NVMC_SetFlags((uint32_t)val);
    } else {
      return ERR_FAILED;
    }
  }
  return ERR_OK;
}

void NVMC_Deinit(void) {
  /* nothing needed */
}

void NVMC_Init(void){
#if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC55xx
  /* NOTE: For LPC the CPU clock has to be 96 MHz max (FRO): 150 MHz does not work! */
  status_t result;    /* Return code from each flash driver function */

  memset(&s_flashDriver, 0, sizeof(flash_config_t));
  /* Setup flash driver structure for device and initialize variables. */
  result = FLASH_Init(&s_flashDriver);
  if (result!=kStatus_Success) {
    McuLog_fatal("NVMC_Init() failed!");
    for(;;) { /* error */ }
  }
#endif
  if(sizeof(NVMC_Data_t) != NVMC_ALIGNED_BLOCK_SIZE) {
    /* data size (number of bytes) shall be 64, 128, 256, 512, 1024 bytes */
    McuLog_fatal("wrong size of NVMC_Data_t!\r\n");
    for(;;) {}
  }
  if (NVMC_IsErased()) { /* Flash erased? */
    McuLog_info("NVMC is erased, initializing it.");
    if (NVMC_InitConfig()!=ERR_OK) { /* initialize it first */
      McuLog_fatal("NVMC_InitConfig() failed!");
      for(;;) {}
    }
  }
}
#endif /* PL_CONFIG_USE_NVMC */

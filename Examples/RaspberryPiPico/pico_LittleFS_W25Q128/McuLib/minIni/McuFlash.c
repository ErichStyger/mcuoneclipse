/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuFlash.h"
#if McuFlash_CONFIG_IS_ENABLED
#include "McuLib.h"
#if McuLib_CONFIG_CPU_IS_LPC || McuLib_CONFIG_CPU_IS_KINETIS  || McuLib_CONFIG_CPU_IS_RPxxxx /* currently limited support, only for these CPUs */

#include "McuLog.h"
#include "McuUtility.h"
#include "McuCriticalSection.h"

#if McuLib_CONFIG_CPU_IS_LPC
  #include "fsl_iap.h"
#elif McuLib_CONFIG_CPU_IS_KINETIS
  #include "fsl_flash.h"
  #include "fsl_smc.h"
  #include "McuWait.h"
#elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_RP2040
  #include "hardware/flash.h"
  #include "hardware/sync.h"
#endif

typedef struct {
  uint32_t addr;
  size_t size;
} McuFlash_Memory;

static McuFlash_Memory McuFlash_RegisteredMemory; /* used in shell status, for information only */

#if McuLib_CONFIG_CPU_IS_LPC && (McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845 || McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC804)
  /* nothing needed */
#elif   McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K22FN \
     || McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K22FX \
     || McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K02FN \
     || McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16
  static flash_config_t s_flashDriver;
#elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_RP2040
  /* nothing  needed */
#else
  #error "device not yet supported"
#endif

void McuFlash_RegisterMemory(const void *addr, size_t nofBytes) {
  McuFlash_RegisteredMemory.addr = (uint32_t)addr;
  McuFlash_RegisteredMemory.size = nofBytes;
}

bool McuFlash_IsAccessible(const void *addr, size_t nofBytes) {
#if McuLib_CONFIG_CPU_IS_LPC55xx
  /* see https://community.nxp.com/t5/LPC-Microcontrollers-Knowledge/LPC55xx-Erased-Memory-State-0-or-1/ta-p/1135084 and
   * https://www.nxp.com/docs/en/application-note/AN12949.pdf
   * Accessing erased (and not written yet) memory causes a hard-fault.
   */
  status_t status;

  status = FLASH_VerifyErase(&s_flashDriver, (uint32_t)addr, nofBytes);
#if McuFlash_CONFIG_LOGGING_TRACE
  McuLog_trace("IsAccessible: 0x%x, size %u, %s", (uint32_t)addr, nofBytes, status==kStatus_Success?"no":"yes");
#endif
  if (status==kStatus_Success) {
    return false; /* if it is an erased FLASH: accessing it will cause a hard fault! */
  }
  return true;
#else
  return true;
#endif
}

bool McuFlash_IsErased(const void *addr, size_t nofBytes) {
#if McuLib_CONFIG_CPU_IS_LPC55xx
  /* see https://community.nxp.com/t5/LPC-Microcontrollers-Knowledge/LPC55xx-Erased-Memory-State-0-or-1/ta-p/1135084 and
   * https://www.nxp.com/docs/en/application-note/AN12949.pdf
   * Accessing erased (and not written yet) memory causes a hard-fault.
   */
  status_t status;

  status = FLASH_VerifyErase(&s_flashDriver, (uint32_t)addr, nofBytes);
#if McuFlash_CONFIG_LOGGING_TRACE
  McuLog_trace("IsErased: 0x%x, size %u, %s", (uint32_t)addr, nofBytes, status==kStatus_Success?"yes":"no");
#endif
  return status==kStatus_Success;  /* true if it is an erased FLASH: accessing it will cause a hard fault! */
#else
  uint8_t *ptr = (uint8_t*)addr;
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

uint8_t McuFlash_Read(const void *addr, void *data, size_t dataSize) {
#if McuFlash_CONFIG_LOGGING_TRACE
  McuLog_trace("Read: 0x%x, size %u", (uint32_t)addr, dataSize);
#endif
  if (!McuFlash_IsAccessible(addr, dataSize)) {
    memset(data, 0xff, dataSize);
    return ERR_FAULT;
  }
#if McuLib_CONFIG_CPU_IS_LPC55xx
  status_t status;

  status = FLASH_Read(&s_flashDriver, (uint32_t)addr, data, (uint32_t)dataSize);
  if(status != kStatus_Success){
    return ERR_FAULT;
  }
  return ERR_OK;
#else
  memcpy(data, addr, dataSize);
  return ERR_OK;
#endif
}

static uint8_t McuFlash_ProgramPage(void *addr, const void *data, size_t dataSize) {
#if McuFlash_CONFIG_LOGGING_TRACE
  McuLog_trace("ProgramPage: 0x%x, size %u", (uint32_t)addr, dataSize);
#endif
#if McuLib_CONFIG_CPU_IS_KINETIS
  status_t status;
  uint8_t res = ERR_OK;

  if (McuFlash_Erase(addr, dataSize)!=ERR_OK) {
    return ERR_FAILED;
  }
#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K02FN || McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
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
#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K02FN
    uint32_t primask = DisableGlobalIRQ(); /* workaround: need to disable interrupts? */
#endif
  for(;;) { /* breaks, switch back to HSRUN if things fail */
    status = FLASH_Program(&s_flashDriver, (uint32_t)addr, (uint8_t*)data, dataSize);
    if (status!=kStatus_FTFx_Success) {
      res = ERR_FAILED;
      break;
    }
    break;
  } /* for */
#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K02FN
  EnableGlobalIRQ(primask); /* workaround: need to disable interrupts? */
#endif
#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K02FN || McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
  status = SMC_SetPowerModeHsrun(SMC);
  if (status!=kStatus_Success) {
    res = ERR_FAILED;
  }
#endif
  return res;
#elif McuLib_CONFIG_CPU_IS_LPC55xx
  status_t status;
  uint32_t failedAddress, failedData;

  if (((uint32_t)addr%s_flashDriver.PFlashPageSize) != 0) {
    McuLog_fatal("addr %08x must be aligned to flash page size %08x", (uint32_t)addr, s_flashDriver.PFlashPageSize);
    return ERR_FAILED;
  }
  if (dataSize!=s_flashDriver.PFlashPageSize) { /* must match flash page size! */
    McuLog_fatal("data size %08x must match flash page size %08x", dataSize, s_flashDriver.PFlashPageSize);
    return ERR_FAILED;
  }
  /* erase first */
  status = FLASH_Erase(&s_flashDriver, (uint32_t)addr, dataSize, kFLASH_ApiEraseKey);
  if (status!=kStatus_Success ) {
    McuLog_fatal("erasing failed with error code %d", status);
    return ERR_FAILED;
  }
  /* check if it is erased */
  status = FLASH_VerifyErase(&s_flashDriver, (uint32_t)addr, dataSize);
  if (status!=kStatus_Success) {
    McuLog_fatal("erase check failed");
    return ERR_FAILED;
  }
  /* here the flash is erased, ready for getting programmed */
  status = FLASH_Program(&s_flashDriver, (uint32_t)addr, (uint8_t*)data, dataSize);
  if (status!=kStatus_Success) {
    McuLog_fatal("failed programming flash, error %d", status);
    return ERR_FAILED;
  }
  status = FLASH_VerifyProgram(&s_flashDriver, (uint32_t)addr, dataSize, (const uint8_t *)data, &failedAddress, &failedData);
  if (status!=kStatus_Success) {
    McuLog_fatal("failed verify at address %08x, data %08x", failedAddress, failedData);
    return ERR_FAILED;
  }
  return ERR_OK;
#elif McuLib_CONFIG_CPU_IS_LPC && (McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845 || McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC804)
  uint32_t startSector = (uint32_t)addr/McuFlash_CONFIG_FLASH_BLOCK_SIZE; /* sector is 1k in size */
  uint32_t endSector = ((uint32_t)addr+(McuFlash_CONFIG_FLASH_BLOCK_SIZE-1))/McuFlash_CONFIG_FLASH_BLOCK_SIZE;
  uint8_t result = ERR_FAILED; /* default */
  status_t res;

  if (McuFlash_Erase(addr, dataSize)!=ERR_OK) {
    return ERR_FAILED;
  }
  res = IAP_PrepareSectorForWrite(startSector, endSector); /* sector size is 1k */
  if (res!=kStatus_IAP_Success) {
    result = ERR_FAILED;
  } else {
    /* destination address should be on a 64byte boundary.
     * Source address should be word (4byte) boundary
     * data size (number of bytes) shall be 64, 128, 256, 512, 1024 bytes */
    res = IAP_CopyRamToFlash((uint32_t)addr, (uint32_t*)data, dataSize, SystemCoreClock);
    if (res!=kStatus_IAP_Success) {
      result = ERR_FAILED;
    } else {
      res = IAP_Compare((uint32_t)addr, (uint32_t*)data, dataSize);
      if (res!=kStatus_IAP_Success) {
        result = ERR_FAILED;
      } else {
        result = ERR_OK;
      }
    }
  }
  return result;
#elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_RP2040
  uint32_t base, size;

  base = (uint32_t)addr-XIP_BASE;
  if ((base%FLASH_PAGE_SIZE)!=0) {
    return ERR_FAILED; /* address must be page size aligned! */
  }
  size = dataSize;
  if ((size%FLASH_PAGE_SIZE)!=0) {
    return ERR_FAILED; /* size must multiple of a page! */
  }

  /* first, erase the flash */
  if (McuFlash_Erase(addr, dataSize)!=ERR_OK) {
    return ERR_FAILED;
  }
  /* need to turn off interrupts. But: only for this core. If other core is running, problems might occur! */
  McuCriticalSection_CriticalVariable();

  McuCriticalSection_EnterCritical();
  flash_range_program(base, (const uint8_t *)data, size);
  McuCriticalSection_ExitCritical();
  return ERR_OK;
#else
  #error "target not supported yet!"
  return ERR_FAILED;
#endif /* McuLib_CONFIG_CPU_IS_KINETIS or McuLib_CONFIG_CPU_IS_LPC */
}

uint8_t McuFlash_Program(void *addr, const void *data, size_t dataSize) {
#if McuFlash_CONFIG_LOGGING_TRACE
  McuLog_trace("Program: 0x%x, size %u", (uint32_t)addr, dataSize);
#endif
#if McuLib_CONFIG_CPU_IS_LPC55xx
  if (((uint32_t)addr%McuFlash_CONFIG_FLASH_BLOCK_SIZE) != 0 || (dataSize!=McuFlash_CONFIG_FLASH_BLOCK_SIZE)) {
    /* address and size not aligned to page boundaries: make backup into buffer */
    uint8_t buffer[McuFlash_CONFIG_FLASH_BLOCK_SIZE];
    uint8_t res;
    size_t offset, remaining, size;
    uint32_t pageAddr; /* address of page */

    pageAddr = ((uint32_t)addr/McuFlash_CONFIG_FLASH_BLOCK_SIZE)*McuFlash_CONFIG_FLASH_BLOCK_SIZE;
    offset = (uint32_t)addr%McuFlash_CONFIG_FLASH_BLOCK_SIZE; /* offset inside page */
    remaining = dataSize;
    while (remaining>0) {
      res = McuFlash_Read((void*)pageAddr, buffer, sizeof(buffer)); /* read current flash content */
      if (res!=ERR_OK) {
        McuLog_fatal("failed reading from Flash at 0x%x", pageAddr);
        return ERR_FAILED;
      }
      if (offset+remaining>McuFlash_CONFIG_FLASH_BLOCK_SIZE) {
        size = McuFlash_CONFIG_FLASH_BLOCK_SIZE-offset; /* how much we can copy in this step */
      } else {
        size = remaining;
      }
      memcpy(buffer+offset, data, size); /*  merge original page with new data */
      /* program new data/page */
      res = McuFlash_ProgramPage((void*)pageAddr, buffer, sizeof(buffer));
      if (res!=ERR_OK) {
        McuLog_fatal("failed making backup from Flash at 0x%x", pageAddr);
        return ERR_FAILED;
      }
      pageAddr += McuFlash_CONFIG_FLASH_BLOCK_SIZE;
      offset = 0;
      data += size;
      remaining -= size;
    } /* while */
    return res;
  } else { /* a full page to program */
    return McuFlash_ProgramPage(addr, data, dataSize);
  }
#else
  return McuFlash_ProgramPage(addr, data, dataSize);
#endif
}

#if McuLib_CONFIG_CPU_IS_LPC55xx
uint8_t McuFlash_InitErase(void *addr, size_t nofBytes) {
  /* LPC55Sxx specific: erases the memory, makes it inaccessible */
  status_t status;

#if McuFlash_CONFIG_LOGGING_TRACE
  McuLog_trace("InitErase: 0x%x, size %u", (uint32_t)addr, nofBytes);
#endif
  if ((nofBytes%McuFlash_CONFIG_FLASH_BLOCK_SIZE)!=0) { /* check if size is multiple of page size */
    McuLog_fatal("wrong erase data size %d, expected multiple %d", nofBytes, McuFlash_CONFIG_FLASH_BLOCK_SIZE);
    return ERR_FAILED;
  }
  for(int i=0; i<nofBytes/McuFlash_CONFIG_FLASH_BLOCK_SIZE; i++) { /* erase and program each page */
    /* erase each page */
    status = FLASH_Erase(&s_flashDriver, (uint32_t)addr+i*McuFlash_CONFIG_FLASH_BLOCK_SIZE, McuFlash_CONFIG_FLASH_BLOCK_SIZE, kFLASH_ApiEraseKey);
    if (status!=kStatus_Success ) {
      McuLog_fatal("erasing failed with error code %d", status);
      return ERR_FAILED;
    }
  }
  return ERR_OK;
}
#endif

uint8_t McuFlash_Erase(void *addr, size_t nofBytes) {
#if McuFlash_CONFIG_LOGGING_TRACE
  McuLog_trace("Erase: 0x%x, size %u", (uint32_t)addr, nofBytes);
#endif
#if McuLib_CONFIG_CPU_IS_LPC && (McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845 || McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC804)
  /* determine sector numbers based on block/sector size */
  uint32_t startSector = (uint32_t)addr/McuFlash_CONFIG_FLASH_BLOCK_SIZE;
  uint32_t endSector = (((uint32_t)addr+(McuFlash_CONFIG_FLASH_BLOCK_SIZE-1))/McuFlash_CONFIG_FLASH_BLOCK_SIZE);
  status_t res;

  if (McuFlash_IsErased(addr, nofBytes)) { /* already eased? */
    return ERR_OK; /* yes, nothing to do */
  }
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
#elif McuLib_CONFIG_CPU_IS_KINETIS
  uint32_t pflashSectorSize = 0;
  status_t status;
  uint8_t res = ERR_OK;

  if (McuFlash_IsErased(addr, nofBytes)) { /* already eased? */
    return ERR_OK; /* yes, nothing to do */
  }
  #if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K02FN || McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
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
  status = FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0SectorSize, &pflashSectorSize);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  if (pflashSectorSize!=McuFlash_CONFIG_FLASH_BLOCK_SIZE) {
    return ERR_FAILED;
  }

  for(;;) { /* breaks, switch back to HSRUN on Kinetis if things fail */
  #if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K02FN
    uint32_t primask = DisableGlobalIRQ(); /* workaround: need to disable interrupts? */
  #endif
    status = FLASH_Erase(&s_flashDriver, (uint32_t)addr, nofBytes, kFTFx_ApiEraseKey);
    if (status!=kStatus_FTFx_Success) {
      res = ERR_FAILED;
    #if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K02FN
      EnableGlobalIRQ(primask); /* workaround: need to disable interrupts? */
    #endif
      break; /* error, leave for(;;) loop */
    }
  #if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K02FN
    EnableGlobalIRQ(primask); /* workaround: need to disable interrupts? */
  #endif
    /* Verify sector if it's been erased. */
    status = FLASH_VerifyErase(&s_flashDriver, (uint32_t)addr, nofBytes, kFTFx_MarginValueUser);
    if (status!=kStatus_FTFx_Success) {
      res = ERR_FAILED;
      break;
    }
    break; /* leave loop */
  } /* for */
  #if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K02FN || McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
  status = SMC_SetPowerModeHsrun(SMC);
  if (status!=kStatus_Success) {
    res = ERR_FAILED;
  }
  #endif
  return res;
#elif McuLib_CONFIG_CPU_IS_LPC55xx
  static const uint8_t zeroBuffer[McuFlash_CONFIG_FLASH_BLOCK_SIZE]; /* initialized with zeros, buffer in FLASH to save RAM */
  uint8_t res;

  if ((nofBytes%McuFlash_CONFIG_FLASH_BLOCK_SIZE)!=0) { /* check if size is multiple of page size */
    McuLog_fatal("wrong erase data size %d, expected multiple of %d", nofBytes, McuFlash_CONFIG_FLASH_BLOCK_SIZE);
    return ERR_FAILED;
  }
  for(int i=0; i<nofBytes/McuFlash_CONFIG_FLASH_BLOCK_SIZE; i++) { /* erase and program each page */
    res = McuFlash_Program(addr+i*McuFlash_CONFIG_FLASH_BLOCK_SIZE, zeroBuffer, sizeof(zeroBuffer));
    if (res!=ERR_OK) {
      return res;
    }
  }
  return res;
#elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_RP2040
  uint32_t base, size;

  base = (uint32_t)addr-XIP_BASE; /* flash erase operation is without the XIP_BASE offset */
  if ((base%FLASH_SECTOR_SIZE)!=0) {
    return ERR_FAILED; /* address must be sector aligned! */
  }
  size = nofBytes;
  if ((size%FLASH_SECTOR_SIZE)!=0) {
    return ERR_FAILED; /* size must multiple of a sector! */
  }

  /* need to turn off interrupts. But: only for this core. If other core is running, problems might occur! */
  McuCriticalSection_CriticalVariable();

  McuCriticalSection_EnterCritical();
  flash_range_erase(base, size);
  McuCriticalSection_ExitCritical();

  return ERR_OK;
#else
  #error "target not supported yet!"
#endif
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[48];

  McuShell_SendStatusStr((unsigned char*)"McuFlash", (unsigned char*)"McuFlash status\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"size 0x");
  McuUtility_strcatNum16Hex(buf, sizeof(buf), McuFlash_CONFIG_FLASH_BLOCK_SIZE);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  block", buf, io->stdOut);

#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_RP2040
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"page 0x");
  McuUtility_strcatNum16Hex(buf, sizeof(buf), FLASH_PAGE_SIZE);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", sector 0x");
  McuUtility_strcatNum16Hex(buf, sizeof(buf), FLASH_SECTOR_SIZE);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", block 0x");
  McuUtility_strcatNum32Hex(buf, sizeof(buf), FLASH_BLOCK_SIZE);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  Flash", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum32Hex(buf, sizeof(buf), PICO_FLASH_SIZE_BYTES);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", ");
  McuUtility_strcatNum32u(buf, sizeof(buf), PICO_FLASH_SIZE_BYTES/(1024*1024));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" MBytes\r\n");
  McuShell_SendStatusStr((unsigned char*)"  Size", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"base 0x");
  McuUtility_strcatNum32Hex(buf, sizeof(buf), XIP_BASE);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  XIP", buf, io->stdOut);
#endif

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"addr 0x");
  McuUtility_strcatNum32Hex(buf, sizeof(buf), McuFlash_RegisteredMemory.addr);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", size 0x");
  McuUtility_strcatNum32Hex(buf, sizeof(buf), McuFlash_RegisteredMemory.size);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  registered", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t ReadData(void *hndl, uint32_t addr, uint8_t *buf, size_t bufSize) {
  (void)hndl; /* not used */
  if (!McuFlash_IsAccessible((void*)addr, bufSize)) {
    memset(buf, 0xff, bufSize);
    return ERR_FAILED;
  }
  memcpy(buf, (void*)addr, bufSize);
  return ERR_OK;
}

uint8_t McuFlash_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;
  uint32_t addr32;
  int32_t size;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "McuFlash help")==0) {
    McuShell_SendHelpStr((unsigned char*)"McuFlash", (const unsigned char*)"Group of flash ini commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  dump <start> <size>", (unsigned char*)"Dump memory data\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  erase <addr> <size>", (unsigned char*)"Erase memory at address\r\n", io->stdOut);
#if McuLib_CONFIG_CPU_IS_LPC55xx
    McuShell_SendHelpStr((unsigned char*)"  init <addr> <size>", (unsigned char*)"Initialize memory (erase only, no programming!)\r\n", io->stdOut);
#endif
    *handled = TRUE;
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "McuFlash status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "McuFlash dump ", sizeof("McuFlash dump ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("McuFlash dump ")-1;
    if (McuUtility_xatoi(&p, (int32_t*)&addr32)==ERR_OK) {
      if (McuUtility_xatoi(&p, &size)==ERR_OK && size>0) {
        if (McuFlash_IsAccessible((void*)addr32, size)) {
          (void)McuShell_PrintMemory(NULL, addr32, addr32+size-1, 4, 16, ReadData, io);
        } else {
          McuShell_SendStr((unsigned char*)"*** memory not accessible\r\n", io->stdErr);
          return ERR_FAILED;
        }
      } else {
        McuShell_SendStr((unsigned char*)"*** wrong end address\r\n", io->stdErr);
        return ERR_FAILED;
      }
    } else {
      McuShell_SendStr((unsigned char*)"*** wrong start address\r\n", io->stdErr);
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, "McuFlash erase ", sizeof("McuFlash erase ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("McuFlash erase ")-1;
    if (McuUtility_xatoi(&p, (int32_t*)&addr32)==ERR_OK) {
      if ((addr32%McuFlash_CONFIG_FLASH_BLOCK_SIZE)!=0) {
        McuShell_SendStr((unsigned char*)"*** address is not flash block aligned\r\n", io->stdErr);
        return ERR_FAILED;
      }
      if (McuUtility_xatoi(&p, &size)==ERR_OK) {
        return McuFlash_Erase((void*)addr32, size);
      } else {
        McuShell_SendStr((unsigned char*)"*** failed scanning size\r\n", io->stdErr);
        return ERR_FAILED;
      }
    }
#if McuLib_CONFIG_CPU_IS_LPC55xx
  } else if (McuUtility_strncmp((char*)cmd, "McuFlash init ", sizeof("McuFlash init ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("McuFlash init ")-1;
    if (McuUtility_xatoi(&p, (int32_t*)&addr32)==ERR_OK) {
      if ((addr32%McuFlash_CONFIG_FLASH_BLOCK_SIZE)!=0) {
        McuShell_SendStr((unsigned char*)"*** address is not flash block aligned\r\n", io->stdErr);
        return ERR_FAILED;
      }
      if (McuUtility_xatoi(&p, &size)==ERR_OK) {
        return McuFlash_InitErase((void*)addr32, size);
      } else {
        McuShell_SendStr((unsigned char*)"*** failed scanning size\r\n", io->stdErr);
        return ERR_FAILED;
      }
    }
#endif
  }
  return ERR_OK;
}

void McuFlash_Deinit(void) {
}

void McuFlash_Init(void) {
#if McuLib_CONFIG_CPU_IS_KINETIS || McuLib_CONFIG_CPU_IS_LPC55xx
  status_t result;    /* Return code from each flash driver function */

  memset(&s_flashDriver, 0, sizeof(flash_config_t));
  /* Setup flash driver structure for device and initialize variables. */
  result = FLASH_Init(&s_flashDriver);
#if McuLib_CONFIG_CPU_IS_KINETIS
  if (result!=kStatus_FTFx_Success) {
    McuLog_fatal("McuFlash_Init() failed!");
    for(;;) { /* error */ }
  }
#elif McuLib_CONFIG_CPU_IS_LPC55xx
  if (result!=kStatus_Success) {
    McuLog_fatal("McuFlash_Init() failed!");
    for(;;) { /* error */ }
  }
#endif
#endif
}

#endif

#endif /* McuFlash_CONFIG_IS_ENABLED */

/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuArmTools.h"
#include "McuLog.h"
#include "McuRTOS.h"
#if PL_CONFIG_USE_SHELL
  #include "McuShell.h"
  #include "McuShellUart.h"
  #include "shell.h"
#endif
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#if PL_CONFIG_USE_MININI
  #include "McuMinINI.h"
#endif
#include "McuFlash.h"
#include "McuWait.h"
#include "application.h"

static void CheckFlash(uint32_t startAddr, size_t size, uint32_t blockSize) {
  uint32_t addr = startAddr;

  while(addr<startAddr+size) {
    if (!McuFlash_IsAccessible((const void*)addr, blockSize)) {
      McuLog_info("Flash block at %u with size %u is not accessible, initializing memory ...", addr, blockSize);
      if (McuFlash_Erase((void*)addr, size)!=ERR_OK) {
        McuLog_fatal("Erasing flash memory failed");
        for(;;) {}
      }
    }
    addr += blockSize;
  }
}

void PL_Init(void) {
  /* McuLib */
  McuLib_Init();
  McuWait_Init();
#if McuLib_CONFIG_SDK_USE_FREERTOS
  McuRTOS_Init();
#endif
  McuArmTools_Init();
  McuLog_Init();
#if PL_CONFIG_USE_MININI
  McuMinINI_Init();
#endif
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
#if PL_CONFIG_USE_SHELL
  McuShell_Init();
#endif
#if PL_CONFIG_USE_SHELL_UART
  McuShellUart_Init();
#endif
  /* application */
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
  McuFlash_Init();
  McuFlash_RegisterMemory((const void*)PL_CONFIG_FLASH_NVM_ADDR_START, PL_CONFIG_FLASH_NVM_NOF_BLOCKS*PL_CONFIG_FLASH_NVM_BLOCK_SIZE);

  /* Note: we check a 4KB block here: but it could be that this works, but later if we want to check the first 512 bytes it fails? */
  CheckFlash(PL_CONFIG_FLASH_NVM_ADDR_START, PL_CONFIG_FLASH_NVM_NOF_BLOCKS*PL_CONFIG_FLASH_NVM_BLOCK_SIZE, PL_CONFIG_FLASH_NVM_BLOCK_SIZE);
  CheckFlash(PL_CONFIG_FLASH_NVM_ADDR_START, PL_CONFIG_FLASH_NVM_NOF_BLOCKS*PL_CONFIG_FLASH_NVM_BLOCK_SIZE, 2*PL_CONFIG_FLASH_NVM_BLOCK_SIZE);
  CheckFlash(PL_CONFIG_FLASH_NVM_ADDR_START, PL_CONFIG_FLASH_NVM_NOF_BLOCKS*PL_CONFIG_FLASH_NVM_BLOCK_SIZE, 4*PL_CONFIG_FLASH_NVM_BLOCK_SIZE);
  CheckFlash(PL_CONFIG_FLASH_NVM_ADDR_START, PL_CONFIG_FLASH_NVM_NOF_BLOCKS*PL_CONFIG_FLASH_NVM_BLOCK_SIZE, 8*PL_CONFIG_FLASH_NVM_BLOCK_SIZE);
#if 0
  if (!McuFlash_IsAccessible((const void*)PL_CONFIG_FLASH_NVM_ADDR_START, PL_CONFIG_FLASH_NVM_NOF_BLOCKS*PL_CONFIG_FLASH_NVM_BLOCK_SIZE)) {
    McuLog_info("Flash for EEPROM emulation is not accessible, initializing memory ...");
    if (McuFlash_Erase((void*)PL_CONFIG_FLASH_NVM_ADDR_START, PL_CONFIG_FLASH_NVM_NOF_BLOCKS*PL_CONFIG_FLASH_NVM_BLOCK_SIZE)!=ERR_OK) {
      McuLog_fatal("Erasing flash memory failed");
      for(;;) {}
    }
  }
#endif
  APP_Init();
}

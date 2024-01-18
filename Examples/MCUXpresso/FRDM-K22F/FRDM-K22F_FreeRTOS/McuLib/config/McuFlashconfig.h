/*!
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * \file
 * \brief Configuration items for the McuFlash module.
 */

#ifndef MCUFLASHCONFIG_H_
#define MCUFLASHCONFIG_H_

#include "McuLib.h"

#ifndef McuFlash_CONFIG_IS_ENABLED
  #define McuFlash_CONFIG_IS_ENABLED              (0)
    /*!< if the module MucFlash is enabled or not: 1: enabled; 0: disabled */
#endif

#ifndef McuFlash_CONFIG_LOGGING_TRACE
  #define McuFlash_CONFIG_LOGGING_TRACE           (0)
    /*!< 1: extra trace logging: 0: no extra trace logging */
#endif

#ifndef McuFlash_CONFIG_FLASH_BLOCK_SIZE
#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845
  #define McuFlash_CONFIG_FLASH_BLOCK_SIZE         (0x400)
#elif McuLib_CONFIG_CPU_IS_LPC55xx
  #define McuFlash_CONFIG_FLASH_BLOCK_SIZE         (0x200)
#elif McuLib_CONFIG_CPU_IS_KINETIS
  #define McuFlash_CONFIG_FLASH_BLOCK_SIZE         (0x800)
#elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_RP2040
  #include "hardware/flash.h"
  #define McuFlash_CONFIG_FLASH_BLOCK_SIZE         (0x1000) /* size of block which can be erased, 4K on RP2040 */
#else /* default */
  #define McuFlash_CONFIG_FLASH_BLOCK_SIZE         (0x400)
#endif
    /*!< size of a flash page, FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0SectorSize, &pflashSectorSize) */
#endif

#endif /* MCUFLASHCONFIG_H_ */

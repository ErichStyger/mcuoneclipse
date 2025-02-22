/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUFLASHCONFIG_H_
#define MCUFLASHCONFIG_H_

#include "McuLib.h"

#ifndef McuFlash_CONFIG_FLASH_BLOCK_SIZE
#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845
  #define McuFlash_CONFIG_FLASH_BLOCK_SIZE         (0x400)
#elif McuLib_CONFIG_CPU_IS_LPC55xx
  #define McuFlash_CONFIG_FLASH_BLOCK_SIZE         (0x200)
#elif McuLib_CONFIG_CPU_IS_KINETIS
  #define McuFlash_CONFIG_FLASH_BLOCK_SIZE         (0x800)
#else /* default */
  #define McuFlash_CONFIG_FLASH_BLOCK_SIZE         (0x400)
#endif
    /*!< size of a flash page, FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0SectorSize, &pflashSectorSize) */
#endif



#endif /* MCUFLASHCONFIG_H_ */

/*
 * ConfigNVM.h
 *
 *  Created on: Sep 12, 2013
 *      Author: tastyger
 */

#ifndef CONFIGNVM_H_
#define CONFIGNVM_H_

#include "Platform.h"

#if PL_IS_FRDM
  #define NVMC_FLASH_START_ADDR    0x1FC00 /* NVRM_Config, start address of configuration data in flash */
#elif PL_IS_SRB
  #define NVMC_FLASH_START_ADDR    0xFBB0 /* NVRM_Config, start address of configuration data in flash */
#else
  #error "unknown target?"
#endif

#define NVMC_FLASH_ERASED_UINT8  0xFF
#define NVMC_FLASH_ERASED_UINT16 0xFFFF

#if PL_HAS_RADIO
#include "RNWK.h"

#define NVMC_DEVICE_ADDR16_START_ADDR     (NVMC_FLASH_START_ADDR)
#define NVMC_DEVICE_ADDR16_DATA_SIZE      (sizeof(RNWK_ShortAddrType))
#define NVMC_DEVICE_ADDR16_END_ADDR       (NVMC_DEVICE_ADDR16_START_ADDR+NVMC_DEVICE_ADDR16_DATA_SIZE)
/* Access macros */
#define NVMC_GetDeviceAddr16Addr()              ((RNWK_ShortAddrType*)(NVMC_DEVICE_ADDR16_START_ADDR))
#endif

#if PL_HAS_RADIO
#define NVMC_REFLECTANCE_DATA_START_ADDR  (NVMC_DEVICE_ADDR16_END_ADDR)
#else
#define NVMC_REFLECTANCE_DATA_START_ADDR  (NVMC_FLASH_START_ADDR)
#endif
#define NVMC_REFLECTANCE_DATA_SIZE        (8*2*2) /* maximum of 8 sensors (min and max) values with 16 bits */
#define NVMC_REFLECTANCE_END_ADDR         (NVMC_REFLECTANCE_DATA_START_ADDR+NVMC_REFLECTANCE_DATA_SIZE)



uint8_t NVMC_SaveReflectanceData(void *data, uint16_t dataSize);
void *NVMC_GetReflectanceData(void);

uint8_t NVMC_SaveDeviceAddress16(void *data, size_t dataSize);


uint8_t NVMC_SaveTurnData(void *data, uint16_t dataSize);
void *NVMC_GetTurnData(void);


#endif /* CONFIGNVM_H_ */

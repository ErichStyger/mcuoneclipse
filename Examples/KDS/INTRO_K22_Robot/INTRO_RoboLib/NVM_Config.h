/**
 * \file
 * \brief Interface for the Non-Volatile-Memory
 * \author Erich Styger
 *
 * This provides an interface to store and retrieve data from the on-chip memory.
 */

#ifndef CONFIGNVM_H_
#define CONFIGNVM_H_

#include "Platform.h"
#if PL_CONFIG_HAS_NVM_CONFIG

#if PL_IS_FRDM
  #define NVMC_FLASH_START_ADDR    0x1FC00 /* NVRM_Config, start address of configuration data in flash */
  #define NVMC_FLASH_BLOCK_SIZE    0x400   /* IntFlashLdd1_BLOCK0_ERASABLE_UNIT_SIZE */
#elif PL_IS_INTRO_ZUMO_K22
  #define NVMC_FLASH_START_ADDR    0x10000000 /* DFLASH, NVRM_Config, start address of configuration data in flash */
  #define NVMC_FLASH_BLOCK_SIZE    0x1000  /* IntFlashLdd1_BLOCK0_ERASABLE_UNIT_SIZE */
#else
  #error "unknown platform/board!"
#endif
#define NVMC_FLASH_ERASED_UINT8  0xFF
#define NVMC_FLASH_ERASED_UINT16 0xFFFF

typedef struct {
  uint8_t version;
  bool MazeLeftHandOnTheWall; /* use left-hand-on-the-wall */
} NVMC_RobotData;


#define NVMC_DEVICE_ADDR16_START_ADDR     (NVMC_FLASH_START_ADDR)
#define NVMC_DEVICE_ADDR16_DATA_SIZE      (2)
#define NVMC_DEVICE_ADDR16_END_ADDR       (NVMC_DEVICE_ADDR16_START_ADDR+NVMC_DEVICE_ADDR16_DATA_SIZE)

#define NVMC_REFLECTANCE_DATA_START_ADDR  (NVMC_DEVICE_ADDR16_END_ADDR)
#define NVMC_REFLECTANCE_DATA_SIZE        (8*2*2) /* maximum of 8 sensors (min and max) values with 16 bits */
#define NVMC_REFLECTANCE_END_ADDR         (NVMC_REFLECTANCE_DATA_START_ADDR+NVMC_REFLECTANCE_DATA_SIZE)

#define NVMC_SUMO_DATA_START_ADDR         (NVMC_REFLECTANCE_END_ADDR)
#define NVMC_SUMO_DATA_SIZE               (4) /* 4 bytes of data */
#define NVMC_SUMO_END_ADDR                (NVMC_SUMO_DATA_START_ADDR+NVMC_SUMO_DATA_SIZE)

#define NVMC_ROBOT_DATA_START_ADDR         (NVMC_SUMO_END_ADDR)
#define NVMC_ROBOT_DATA_SIZE               (sizeof(NVMC_RobotData))
#define NVMC_ROBOT_END_ADDR                (NVMC_ROBOT_DATA_START_ADDR+NVMC_ROBOT_DATA_SIZE)

/* Access macros */
#define NVMC_GetDeviceAddr16Addr()        ((uint16_t*)(NVMC_DEVICE_ADDR16_START_ADDR))


uint8_t NVMC_SaveReflectanceData(void *data, uint16_t dataSize);
void *NVMC_GetReflectanceData(void);

uint8_t NVMC_SaveDeviceAddress16(void *data, size_t dataSize);

uint8_t NVMC_SaveRobotData(NVMC_RobotData *data);
const NVMC_RobotData *NVMC_GetRobotData(void);

#if PL_DO_SUMO
uint8_t NVMC_SaveSumoData(void *data, uint16_t dataSize);
void *NVMC_GetSumoData(void);
#endif /* PL_DO_SUMO */

#endif /* #if PL_CONFIG_HAS_NVM_CONFIG */

#endif /* CONFIGNVM_H_ */

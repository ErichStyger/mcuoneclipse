/**
 * \file
 * \brief Implementation of Non-Volatile-Memory storage
 * \author Erich Styger
 *
 * This provides an implementation to store and retrieve data from the on-chip memory.
 */

#include "Platform.h"
#if PL_CONFIG_HAS_NVM_CONFIG
#include "NVM_Config.h"
#include "IFsh1.h"

static bool isErased(uint8_t *ptr, int nofBytes) {
  while (nofBytes>0) {
    if (*ptr!=0xFF) {
      return FALSE; /* byte not erased */
    }
    ptr++;
    nofBytes--;
  }
  return TRUE;
}

#if PL_HAS_RADIO
uint8_t NVMC_SaveDeviceAddress16(void *data, size_t dataSize) {
  uint8_t res;
  
  if (dataSize!=2) {
    return ERR_OVERFLOW;
  }
  res = IFsh1_SetBlockFlash((byte*)data, (IFsh1_TAddress)(NVMC_GetDeviceAddr16Addr()), dataSize);  
  return res;
}
#endif

uint8_t NVMC_SaveReflectanceData(void *data, uint16_t dataSize) {
  if (dataSize>NVMC_REFLECTANCE_DATA_SIZE) {
    return ERR_OVERFLOW;
  }
  return IFsh1_SetBlockFlash(data, (IFsh1_TAddress)(NVMC_REFLECTANCE_DATA_START_ADDR), dataSize);  
}

void *NVMC_GetReflectanceData(void) {
  if (isErased((uint8_t*)NVMC_REFLECTANCE_DATA_START_ADDR, NVMC_REFLECTANCE_DATA_SIZE)) {
    return NULL;
  }
  return (void*)NVMC_REFLECTANCE_DATA_START_ADDR;
}

#if PL_DO_SUMO
uint8_t NVMC_SaveSumoData(void *data, uint16_t dataSize) {
  if (dataSize>NVMC_SUMO_DATA_SIZE) {
    return ERR_OVERFLOW;
  }
  return IFsh1_SetBlockFlash(data, (IFsh1_TAddress)(NVMC_SUMO_DATA_START_ADDR), dataSize);  
}

void *NVMC_GetSumoData(void) {
  if (isErased((uint8_t*)NVMC_SUMO_DATA_START_ADDR, NVMC_SUMO_DATA_SIZE)) {
    return NULL;
  }
  return (void*)NVMC_SUMO_DATA_START_ADDR;
}

#endif /* PL_DO_SUMO */

uint8_t NVMC_SaveRobotData(NVMC_RobotData *data) {
  return IFsh1_SetBlockFlash((void*)data, (IFsh1_TAddress)(NVMC_ROBOT_DATA_START_ADDR), sizeof(NVMC_RobotData));
}

const NVMC_RobotData *NVMC_GetRobotData(void) {
  if (isErased((uint8_t*)NVMC_ROBOT_DATA_START_ADDR, sizeof(NVMC_RobotData))) {
    return NULL;
  }
  return (void*)NVMC_ROBOT_DATA_START_ADDR;
}


#endif /* PL_CONFIG_HAS_NVM_CONFIG */



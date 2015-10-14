/*
 * ConfigNVM.c
 *
 *  Created on: Sep 12, 2013
 *      Author: tastyger
 */

#include "Platform.h"
#if PL_HAS_CONFIG_NVM
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


#endif /* PL_HAS_CONFIG_NVM */



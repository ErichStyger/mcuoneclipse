/*!
 * \file      eeprom-board.c
 *
 * \brief     Target board EEPROM driver implementation
 *
 * \remark	  This board doesn't use EEPROM, but Flash instead
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \author    Diego Bienz
 */

#include "platform.h"
#include "utilities.h"
#include "eeprom-board.h"
#include "fsl_iap.h"
#include "fsl_iap_ffr.h"
#include "McuFlash.h"
#include "McuArmTools.h"

static bool FlashProgrammingOnGoing = false;

/************************************************
*
* Total Flash Size: 256 KB (244 KB available for customer)
* Sector Size: 32 KB
* Page Size: 512 Bytes
* CAUTION: The LoRa stack is using 16 bit addressing scheme
* while the MCU requires 32 bit. The 16 bit offset
* given to this driver are converted to a suitable
* 32 bit flash address.
*
************************************************/

/*!
 * \brief Initializes the EEPROM emulation module.
 */
void EepromMcuInit(void) {
}

/*!
 * \brief Indicates if an erasing operation is on going.
 *
 * \retval isEradingOnGoing Returns true is an erasing operation is on going.
 */
bool EepromMcuIsErasingOnGoing(void) {
  return FlashProgrammingOnGoing;
}

/*!
 * CAUTION: The address and size has to be a multiple of the page size (512 Bytes)
 */
LmnStatus_t EepromMcuWriteBuffer(uint16_t addr, uint8_t *buffer, uint16_t size) {
	/* The MCU is working with a 32-bit address, while the stack is using a 16 bit address. We are
	 * converting the 16 bit address to 32 bit here.
	 */
	uint32_t convertedAddress = (uint32_t)addr + PL_CONFIG_FLASH_NVM_ADDR_START;
	uint8_t res;

  if (!(convertedAddress>=PL_CONFIG_FLASH_NVM_ADDR_START && convertedAddress+size <= PL_CONFIG_FLASH_NVM_ADDR_START+PL_CONFIG_FLASH_NVM_NOF_BLOCKS*PL_CONFIG_FLASH_NVM_BLOCK_SIZE)) {
    /* not within reserved memory area? */
    return LMN_STATUS_ERROR;
  }
  FlashProgrammingOnGoing = true;
	res = McuFlash_Program((void*)convertedAddress, buffer, size);
	FlashProgrammingOnGoing = false;

	if(res != ERR_OK){
    return LMN_STATUS_ERROR;
  }
  return LMN_STATUS_OK;
}

/*!
 * CAUTION: The address and size has to be a multiple of the page size (512 Bytes)
 */
LmnStatus_t EepromMcuReadBuffer(uint16_t addr, uint8_t *buffer, uint16_t size) {
	/* The MCU is working with a 32-bit address, while the stack is using a 16 bit address. We are
		 * converting the 16 bit address to 32 bit here.
		 */
	uint32_t convertedAddress = (uint32_t)addr + PL_CONFIG_FLASH_NVM_ADDR_START;
  uint8_t res;

  if (!(convertedAddress>=PL_CONFIG_FLASH_NVM_ADDR_START && convertedAddress+size <= PL_CONFIG_FLASH_NVM_ADDR_START+PL_CONFIG_FLASH_NVM_NOF_BLOCKS*PL_CONFIG_FLASH_NVM_BLOCK_SIZE)) {
    /* not within memory area? */
    return LMN_STATUS_ERROR;
  }
	res = McuFlash_Read((void*)convertedAddress, buffer, (uint32_t)size);
  if(res != ERR_OK){
    return LMN_STATUS_ERROR;
  }
  return LMN_STATUS_OK;
}

void EepromMcuSetDeviceAddr(uint8_t addr) {
	for(;;){
		/* This method is not allowed on this platform. */
	}
}

LmnStatus_t EepromMcuGetDeviceAddr(void) {
  return LMN_STATUS_ERROR;
}

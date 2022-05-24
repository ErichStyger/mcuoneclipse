/*
 * w25_interface.h
 *
 *  Created on: 23.05.2022
 *      Author: cc-isn
 */

#ifndef W25_INTERFACE_H_
#define W25_INTERFACE_H_
#include "platform.h"
#include "McuLib.h"

#if PL_CONFIG_HAS_LITTLE_FS
  #include "littleFS/McuLittleFS.h"
  #include "littleFS/lfs.h"
  #include "littleFS/McuLittleFSBlockDevice.h"
#endif

uint8_t W25_read_block_for_SHA(lfs_t *lfs, lfs_file_t* file, size_t nofBytes,  void *outputHASH);

#endif /* W25_INTERFACE_H_ */

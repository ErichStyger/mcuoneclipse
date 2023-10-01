/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuLib.h" /* for error codes */
#include "McuLittleFSBlockDevice.h"
#include "McuLittleFSconfig.h"
#include "littleFS/lfs.h"

/* pre-configured memory devices */
#if McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE==McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_WINBOND_W25Q128
  #include "McuW25Q128.h"
#elif McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE==McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_MCU_FLASH
  #include "McuFlash.h"
#endif

int McuLittleFS_block_device_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size) {
  uint8_t res;

#if McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE==McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_GENERIC
  res = ERR_FAILED; /* NYI */
#elif McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE==McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_WINBOND_W25Q128
  res = McuW25_Read((block+McuLittleFS_CONFIG_BLOCK_OFFSET) * c->block_size + off, buffer, size);
#elif McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE==McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_MCU_FLASH
  res = McuFlash_Read((void*)((block+McuLittleFS_CONFIG_BLOCK_OFFSET) * c->block_size + off), buffer, size);
#endif
  if (res != ERR_OK) {
    return LFS_ERR_IO;
  }
  return LFS_ERR_OK;
}

int McuLittleFS_block_device_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size) {
  uint8_t res;

#if McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE==McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_GENERIC
  res = ERR_FAILED; /* NYI */
#elif McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE==McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_WINBOND_W25Q128
  res = McuW25_ProgramPage((block+McuLittleFS_CONFIG_BLOCK_OFFSET) * c->block_size + off, buffer, size);
#elif McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE==McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_MCU_FLASH
  res = McuFlash_Program((void*)((block+McuLittleFS_CONFIG_BLOCK_OFFSET) * c->block_size + off), buffer, size);
#endif
  if (res != ERR_OK) {
    return LFS_ERR_IO;
  }
  return LFS_ERR_OK;
}

int McuLittleFS_block_device_erase(const struct lfs_config *c, lfs_block_t block) {
  uint8_t res;

#if McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE==McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_GENERIC
  res = ERR_FAILED; /* NYI */
#elif McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE==McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_WINBOND_W25Q128
  res = McuW25_EraseSector4K((block+McuLittleFS_CONFIG_BLOCK_OFFSET) * c->block_size);
#elif McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE==McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_MCU_FLASH
  res = McuFlash_Erase((void*)((block+McuLittleFS_CONFIG_BLOCK_OFFSET) * c->block_size), c->block_size);
#endif
  if (res != ERR_OK) {
    return LFS_ERR_IO;
  }
  return LFS_ERR_OK;
}

int McuLittleFS_block_device_sync(const struct lfs_config *c) {
  return LFS_ERR_OK;
}

int McuLittleFS_block_device_deinit(void) {
  return LFS_ERR_OK;
}

int McuLittleFS_block_device_init(void) {
  return LFS_ERR_OK;
}

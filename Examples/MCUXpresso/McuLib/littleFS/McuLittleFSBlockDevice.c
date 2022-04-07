/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuLittleFSBlockDevice.h"
#include "littleFS/lfs.h"

int McuLittleFS_block_device_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size) {
#if 0
  uint8_t res;

  res = McuLFSMem_Read(block * c->block_size + off, buffer, size);
  if (res != ERR_OK) {
    return LFS_ERR_IO;
  }
#endif
  return LFS_ERR_OK;
}

int McuLittleFS_block_device_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size) {
#if 0
  uint8_t res;

  res = McuLFSMem_Program(block * c->block_size + off, buffer, size);
  if (res != ERR_OK) {
    return LFS_ERR_IO;
  }
#endif
  return LFS_ERR_OK;
}

int McuLittleFS_block_device_erase(const struct lfs_config *c, lfs_block_t block) {
#if 0
  uint8_t res;

  res = McuLFSMem_EraseBlock(block * c->block_size);
  if (res != ERR_OK) {
    return LFS_ERR_IO;
  }
#endif
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

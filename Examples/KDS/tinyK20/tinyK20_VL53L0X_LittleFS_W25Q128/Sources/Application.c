/*
 * Application.c
 *
 *  Created on: 04.03.2016
 *      Author: Erich Styger
 */

#include <CLS1.h>
#include <littleFS/lfs.h>
#include <LED1.h>
#include <PE_Error.h>
#include <PORT_PDD.h>
#include <stdint.h>
#include <Shell.h>
#include <W25Q128.h>
#include <WAIT1.h>
#include "Application.h"

/* variables used by the file system */
lfs_t lfs;
lfs_file_t file;

static int block_device_read(const struct lfs_config *c, lfs_block_t block,  lfs_off_t off, void *buffer, lfs_size_t size) {
  uint8_t res;

  res = W25_Read(block*c->block_size + off, buffer, size);
  if (res!=ERR_OK) {
    return LFS_ERR_IO;
  }
  return LFS_ERR_OK;
}

int block_device_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size) {
  uint8_t res;

  res = W25_ProgramPage(block*c->block_size + off, buffer, size);
  if (res!=ERR_OK) {
    return LFS_ERR_IO;
  }
  return LFS_ERR_OK;
}

int block_device_erase(const struct lfs_config *c, lfs_block_t block) {
  uint8_t res;

  res = W25_EraseSector4K(block*c->block_size);
  if (res!=ERR_OK) {
    return LFS_ERR_IO;
  }
  return LFS_ERR_OK;
}

int block_device_sync(const struct lfs_config *c) {
  return LFS_ERR_OK;
}

// configuration of the filesystem is provided by this struct
const struct lfs_config cfg = {
    // block device operations
    .read  = block_device_read,
    .prog  = block_device_prog,
    .erase = block_device_erase,
    .sync  = block_device_sync,

    // block device configuration
    .read_size = 16,
    .prog_size = 16,
    .block_size = 4096,
    .block_count = 128,
    .lookahead = 128,
};


static void testFS(void) {
  /* mount the filesystem */
  int err = lfs_mount(&lfs, &cfg);

  /* reformat if we can't mount the filesystem */
  /* this should only happen on the first boot */
  if (err) {
    CLS1_SendStr("failed to mount file system, formatting it.\r\n", CLS1_GetStdio()->stdOut);
    lfs_format(&lfs, &cfg);
    lfs_mount(&lfs, &cfg);
  }

  /* read current count */
  uint32_t boot_count = 0;
  lfs_file_open(&lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
  lfs_file_read(&lfs, &file, &boot_count, sizeof(boot_count));

  /* update boot count */
  boot_count += 1;
  lfs_file_rewind(&lfs, &file);
  lfs_file_write(&lfs, &file, &boot_count, sizeof(boot_count));

  /* remember the storage is not updated until the file is closed successfully */
  lfs_file_close(&lfs, &file);

  /* release any resources we were using */
  lfs_unmount(&lfs);

  /* print the boot count */
  CLS1_printf("boot_count: %d\r\n", boot_count);
}


void APP_Start(void) {
  WAIT1_Waitms(100); /* give sensor time to power up */
  /* need pull-up on UART Rx pin (PTC3) on tinyK20 */
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 3, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 3, PORT_PDD_PULL_ENABLE);

  CLS1_SendStr("\r\n*****************************\r\nLittleFS with tinyK20\r\n*****************************\r\n", CLS1_GetStdio()->stdOut);
  if (W25_Init()!=ERR_OK) {
    CLS1_SendStr("ERROR: Failed W25_Init()\r\n", CLS1_GetStdio()->stdErr);
  }
  testFS();
  for(;;) { /* main loop */
    LED1_Neg();
    WAIT1_Waitms(50);
    SHELL_Parse(); /* call command line parser */
  }
}

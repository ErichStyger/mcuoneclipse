/*
 * fs.c
 *
 *  Created on: 06.01.2019
 *      Author: Erich Styger
 */
#include "fs.h"
#include "W25Q128.h"
#include "CLS1.h"
#include "littleFS/lfs.h"

/* variables used by the file system */
static bool FS_isMounted = FALSE;
static lfs_t FS_lfs;
static lfs_file_t file;

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
const struct lfs_config FS_cfg = {
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
  int err = lfs_mount(&FS_lfs, &FS_cfg);

  /* reformat if we can't mount the filesystem */
  /* this should only happen on the first boot */
  if (err) {
    CLS1_SendStr("failed to mount file system, formatting it.\r\n", CLS1_GetStdio()->stdOut);
    lfs_format(&FS_lfs, &FS_cfg);
    lfs_mount(&FS_lfs, &FS_cfg);
  }

  /* read current count */
  uint32_t boot_count = 0;
  lfs_file_open(&FS_lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
  lfs_file_read(&FS_lfs, &file, &boot_count, sizeof(boot_count));

  /* update boot count */
  boot_count += 1;
  lfs_file_rewind(&FS_lfs, &file);
  lfs_file_write(&FS_lfs, &file, &boot_count, sizeof(boot_count));

  /* remember the storage is not updated until the file is closed successfully */
  lfs_file_close(&FS_lfs, &file);

  /* release any resources we were using */
  lfs_unmount(&FS_lfs);

  /* print the boot count */
  CLS1_printf("boot_count: %d\r\n", boot_count);
}

uint8_t FS_Format(CLS1_ConstStdIOType *io) {
  int res;

  if (FS_isMounted) {
    if (io!=NULL) {
      CLS1_SendStr("File system is mounted, unmount it first.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  if (io!=NULL) {
    CLS1_SendStr("Formatting ...", io->stdOut);
  }
  res = lfs_format(&FS_lfs, &FS_cfg);
  if (res==LFS_ERR_OK) {
    if (io!=NULL) {
      CLS1_SendStr(" done.\r\n", io->stdOut);
    }
    return ERR_OK;
  } else {
    if (io!=NULL) {
      CLS1_SendStr(" FAILED!\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
}

uint8_t FS_Mount(CLS1_ConstStdIOType *io) {
  int res;

  if (FS_isMounted) {
    if (io!=NULL) {
      CLS1_SendStr("File system is already mounted.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  if (io!=NULL) {
    CLS1_SendStr("Mounting ...", io->stdOut);
    return ERR_FAILED;
  }
  res = lfs_mount(&FS_lfs, &FS_cfg);
  if (res==LFS_ERR_OK) {
    if (io!=NULL) {
      CLS1_SendStr(" done.\r\n", io->stdOut);
    }
    FS_isMounted = TRUE;
    return ERR_OK;
  } else {
    if (io!=NULL) {
      CLS1_SendStr(" FAILED!\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
}

uint8_t FS_Unmount(CLS1_ConstStdIOType *io) {
  int res;

  if (!FS_isMounted) {
    if (io!=NULL) {
      CLS1_SendStr("File system is already unmounted.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  if (io!=NULL) {
    CLS1_SendStr("Unmounting ...", io->stdOut);
    return ERR_FAILED;
  }
  res = lfs_unmount(&FS_lfs);
  if (res==LFS_ERR_OK) {
    if (io!=NULL) {
      CLS1_SendStr(" done.\r\n", io->stdOut);
    }
    FS_isMounted = FALSE;
    return ERR_OK;
  } else {
    if (io!=NULL) {
      CLS1_SendStr(" FAILED!\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
}

static uint8_t FS_PrintStatus(CLS1_ConstStdIOType *io) {
  CLS1_SendStatusStr((const unsigned char*)"FS", (const unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((const unsigned char*)"  mounted", FS_isMounted?"yes\r\n":"no\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t FS_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "FS help")==0) {
    CLS1_SendHelpStr((unsigned char*)"FS", (const unsigned char*)"Group of FS commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  format", (const unsigned char*)"Format the file system\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  mount", (const unsigned char*)"Mount the file system\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  unmount", (const unsigned char*)"unmount the file system\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, "FS status")==0) {
    *handled = TRUE;
    return FS_PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "FS format")==0) {
    *handled = TRUE;
    return FS_Format(io);
  } else if (UTIL1_strcmp((char*)cmd, "FS mount")==0) {
    *handled = TRUE;
    return FS_Mount(io);
  } else if (UTIL1_strcmp((char*)cmd, "FS umount")==0) {
    *handled = TRUE;
    return FS_Unmount(io);
  }
  return ERR_OK;
}

uint8_t FS_Init(void) {
  if (W25_Init()!=ERR_OK) {
    return ERR_FAILED;
  }
  return ERR_OK;
}


/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCULITTLEFS_H_
#define MCULITTLEFS_H_

#include "littleFS/McuLittleFSBlockDeviceconfig.h"
#include "McuShell.h"
#include "littleFS/lfs.h"
#include "McuRTOS.h"

bool McuLFS_IsMounted(void);

lfs_t* McuLFS_GetFileSystem(void);
uint8_t McuLFS_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#if LITTLEFS_CONFIG_THREAD_SAFE
  void McuLFS_GetFileAccessMutex(SemaphoreHandle_t* mutex);
#endif

uint8_t McuLFS_ReadFile(lfs_file_t* file, bool readFromBeginning, size_t nofBytes, McuShell_ConstStdIOType *io);
uint8_t McuLFS_FileList(const char *path, McuShell_ConstStdIOType *io);
uint8_t McuLFS_RemoveFile(const char *filePath, McuShell_ConstStdIOType *io);
uint8_t McuLFS_MoveFile(const char *srcPath, const char *dstPath,McuShell_ConstStdIOType *io);

uint8_t McuLFS_Mount(McuShell_ConstStdIOType *io);
uint8_t McuLFS_Unmount(McuShell_ConstStdIOType *io);

uint8_t McuLFS_openFile(lfs_file_t* file,uint8_t* filename);
uint8_t McuLFS_closeFile(lfs_file_t* file);
uint8_t McuLFS_writeLine(lfs_file_t* file,uint8_t* line);
uint8_t McuLFS_readLine(lfs_file_t* file,uint8_t* lineBuf,size_t bufSize,uint8_t* nofReadChars);

/* Functions ported from FatFS (Used by MiniIni) */
char* McuLFS_gets (char* buff,int len, lfs_file_t* fp);
int McuLFS_putc (char c, lfs_file_t* fp);
int McuLFS_puts (const char* str, lfs_file_t* fp);

void McuLFS_Deinit(void);
void McuLFS_Init(void);

#endif /* MCULITTLEFS_H_ */

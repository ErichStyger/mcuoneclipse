/*
 * fs.c
 *
 *  Created on: 06.01.2019
 *      Author: Erich Styger
 */
#include "fs.h"
#include "W25Q128.h"
#include "CLS1.h"
#include "TmDt1.h"
#include "littleFS/lfs.h"

#define FS_FILE_NAME_SIZE  32 /* Length of file name, used in buffers */

/* variables used by the file system */
static bool FS_isMounted = FALSE;
static lfs_t FS_lfs;

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

// configuration of the file system is provided by this struct
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
  .block_count = 4096, /* 4096 * 4K = 16 MByte */
  .lookahead = 128,
};

#if 0
static void testFS(void) {
  /* mount the filesystem */
  int err = lfs_mount(&FS_lfs, &FS_cfg);
  lfs_file_t file;

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
#endif

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

uint8_t FS_Dir(const char *path, CLS1_ConstStdIOType *io) {
  int res;
  lfs_dir_t dir;
  struct lfs_info info;

  if (io==NULL) {
    return ERR_FAILED; /* listing a directory without an I/O channel does not make any sense */
  }
  if (!FS_isMounted) {
    CLS1_SendStr("File system is not mounted, mount it first.\r\n", io->stdErr);
    return ERR_FAILED;
  }
  if (path==NULL) {
    path = "/"; /* default path */
  }
  res = lfs_dir_open(&FS_lfs, &dir, path);
  if (res!=LFS_ERR_OK) {
    CLS1_SendStr("FAILED lfs_dir_open()!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  for(;;) {
    res = lfs_dir_read(&FS_lfs, &dir, &info);
    if (res < 0) {
      CLS1_SendStr("FAILED lfs_dir_read()!\r\n", io->stdErr);
      return ERR_FAILED;
    }
    if (res == 0) { /* no more files */
       break;
    }
    switch (info.type) {
      case LFS_TYPE_REG: CLS1_SendStr("reg ", io->stdOut); break;
      case LFS_TYPE_DIR: CLS1_SendStr("dir ", io->stdOut); break;
      default:           CLS1_SendStr("?   ", io->stdOut); break;
    }
    static const char *prefixes[] = {"", "K", "M", "G"}; /* prefixes for kilo, mega and giga */
    for (int i = sizeof(prefixes)/sizeof(prefixes[0])-1; i >= 0; i--) {
        if (info.size >= (1 << 10*i)-1) {
            CLS1_printf("%*u%sB ", 4-(i != 0), info.size >> 10*i, prefixes[i]); /* \todo: remove printf */
            break;
        }
    } /* for */
    CLS1_SendStr(info.name, io->stdOut);
    CLS1_SendStr("\r\n", io->stdOut);
  } /* for */
  res = lfs_dir_close(&FS_lfs, &dir);
  if (res!=LFS_ERR_OK) {
    CLS1_SendStr("FAILED lfs_dir_close()!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t FS_CopyFile(const char *srcPath, const char *dstPath, CLS1_ConstStdIOType *io) {
  lfs_file_t fsrc, fdst;
  uint8_t res =  ERR_OK;
  int result, nofBytesRead;
  uint8_t buffer[32];   /* copy buffer */

  if (!FS_isMounted) {
    if (io!=NULL) {
      CLS1_SendStr("ERROR: File system is not mounted.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }

  /* open source file */
  result = lfs_file_open(&FS_lfs, &fsrc, srcPath, LFS_O_RDONLY);
  if (result<0) {
    CLS1_SendStr((const unsigned char*)"*** Failed opening source file!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  /* create destination file */
  result = lfs_file_open(&FS_lfs, &fdst, dstPath, LFS_O_WRONLY | LFS_O_CREAT);
  if (result<0) {
    (void)lfs_file_close(&FS_lfs, &fsrc);
    CLS1_SendStr((const unsigned char*)"*** Failed opening destination file!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  /* now copy source to destination */
  for (;;) {
    nofBytesRead = lfs_file_read(&FS_lfs, &fsrc, buffer, sizeof(buffer));
    if (nofBytesRead<0) {
      CLS1_SendStr((const unsigned char*)"*** Failed reading source file!\r\n", io->stdErr);
      res = ERR_FAILED;
      break;
    }
    if (nofBytesRead==0) { /* end of file */
      break;
    }
    result = lfs_file_write(&FS_lfs, &fdst, buffer, nofBytesRead);
    if (result<0) {
      CLS1_SendStr((const unsigned char*)"*** Failed writing destination file!\r\n", io->stdErr);
      res = ERR_FAILED;
      break;
    }
  } /* for */
  /* close all files */
  result = lfs_file_close(&FS_lfs, &fsrc);
  if (result<0) {
    CLS1_SendStr((const unsigned char*)"*** Failed closing source file!\r\n", io->stdErr);
    res = ERR_FAILED;
  }
  result = lfs_file_close(&FS_lfs, &fdst);
  if (result<0) {
    CLS1_SendStr((const unsigned char*)"*** Failed closing destination file!\r\n", io->stdErr);
    res = ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t FS_MoveFile(const char *srcPath, const char *dstPath, CLS1_ConstStdIOType *io) {
  if (!FS_isMounted) {
    if (io!=NULL) {
      CLS1_SendStr("ERROR: File system is not mounted.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  if (lfs_rename(&FS_lfs, srcPath, dstPath)<0) {
    if (io!=NULL) {
      CLS1_SendStr("ERROR: failed renaming file or directory.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  return ERR_OK;
}

static uint8_t readFromFile(void *hndl, uint32_t addr, uint8_t *buf, size_t bufSize) {
  lfs_file_t *fp;

  fp = (lfs_file_t*)hndl;
  if (lfs_file_read(&FS_lfs, fp, buf, bufSize)<0) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t FS_PrintHexFile(const char *filePath, CLS1_ConstStdIOType *io) {
  lfs_file_t file;
  uint8_t res = ERR_OK;
  int32_t fileSize;
  int result;

  if (io==NULL) {
    return ERR_FAILED; /* printing a file without an I/O channel does not make any sense */
  }
  if (!FS_isMounted) {
    if (io!=NULL) {
      CLS1_SendStr("ERROR: File system is not mounted.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  result = lfs_file_open(&FS_lfs, &file, filePath, LFS_O_RDONLY);
  if (result<0) {
    if (io!=NULL) {
      CLS1_SendStr("ERROR: Failed opening file.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  fileSize = lfs_file_size(&FS_lfs, &file);
  if (fileSize<0) {
    if (io!=NULL) {
      CLS1_SendStr("ERROR: getting file size\r\n", io->stdErr);
      (void)lfs_file_close(&FS_lfs, &file);
    }
    return ERR_FAILED;
  }
  res = CLS1_PrintMemory(&file, 0, fileSize-1, 4, 16, readFromFile, io);
  if (res!=ERR_OK) {
    CLS1_SendStr("ERROR while calling PrintMemory()\r\n", io->stdErr);
  }
  (void)lfs_file_close(&FS_lfs, &file);
  return res;
}

uint8_t FS_RemoveFile(const char *filePath, CLS1_ConstStdIOType *io) {
  int result;

  if (!FS_isMounted) {
    if (io!=NULL) {
      CLS1_SendStr("ERROR: File system is not mounted.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  result = lfs_remove(&FS_lfs, filePath);
  if (result<0) {
    if (io!=NULL) {
      CLS1_SendStr("ERROR: Failed removing file.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t FS_RunBenchmark(CLS1_ConstStdIOType *io) {
  lfs_file_t file;
  int result;
  uint32_t i;
  uint8_t read_buf[10];
  TIMEREC time, startTime;
  int32_t start_mseconds, mseconds;

  if (!FS_isMounted) {
    if (io!=NULL) {
      CLS1_SendStr("ERROR: File system is not mounted.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  /* write benchmark */
  CLS1_SendStr((const unsigned char*)"Benchmark: write/copy/read a 100kB file:\r\n", io->stdOut);
  CLS1_SendStr((const unsigned char*)"Delete existing benchmark files...\r\n", io->stdOut);
  (void)FS_RemoveFile((const unsigned char*)"./bench.txt", io);
  (void)FS_RemoveFile((const unsigned char*)"./copy.txt", io);

  CLS1_SendStr((const unsigned char*)"Create benchmark file...\r\n", io->stdOut);
  (void)TmDt1_GetTime(&startTime);
  if (lfs_file_open(&FS_lfs, &file, "./bench.txt", LFS_O_WRONLY | LFS_O_CREAT)<0) {
    CLS1_SendStr((const unsigned char*)"*** Failed creating benchmark file!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  for(i=0;i<1024/*0*/;i++) {
    if (lfs_file_write(&FS_lfs, &file, "benchmark ", sizeof("benchmark ")-1)<0) {
      CLS1_SendStr((const unsigned char*)"*** Failed writing file!\r\n", io->stdErr);
      (void)lfs_file_close(&FS_lfs, &file);
      return ERR_FAILED;
    }
  }
  (void)lfs_file_close(&FS_lfs, &file);
  (void)TmDt1_GetTime(&time);
  start_mseconds = startTime.Hour*60*60*1000 + startTime.Min*60*1000 + startTime.Sec*1000
#if TmDt1_HAS_SEC100_IN_TIMEREC
  + startTime.Sec100*10
#endif
  ;
  mseconds = time.Hour*60*60*1000 + time.Min*60*1000 + time.Sec*1000
#if TmDt1_HAS_SEC100_IN_TIMEREC
  + time.Sec100*10
#endif
  - start_mseconds;
  CLS1_SendNum32s(mseconds, io->stdOut);
  CLS1_SendStr((const unsigned char*)" ms for writing (", io->stdOut);
  CLS1_SendNum32s((100*1000)/mseconds, io->stdOut);
  CLS1_SendStr((const unsigned char*)" kB/s)\r\n", io->stdOut);

  /* read benchmark */
  CLS1_SendStr((const unsigned char*)"Read 100kB benchmark file...\r\n", io->stdOut);
  (void)TmDt1_GetTime(&startTime);
  if (lfs_file_open(&FS_lfs, &file, "./bench.txt", LFS_O_RDONLY)<0) {
    CLS1_SendStr((const unsigned char*)"*** Failed opening benchmark file!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  for(i=0;i<10240;i++) {
    if (lfs_file_read(&FS_lfs, &file, &read_buf[0], sizeof(read_buf))<0) {
      CLS1_SendStr((const unsigned char*)"*** Failed reading file!\r\n", io->stdErr);
      (void)lfs_file_close(&FS_lfs, &file);
      return ERR_FAILED;
    }
  }
  (void)lfs_file_close(&FS_lfs, &file);
  (void)TmDt1_GetTime(&time);
  start_mseconds = startTime.Hour*60*60*1000 + startTime.Min*60*1000 + startTime.Sec*1000
#if TmDt1_HAS_SEC100_IN_TIMEREC
  + startTime.Sec100*10
#endif
  ;
  mseconds = time.Hour*60*60*1000 + time.Min*60*1000 + time.Sec*1000
#if TmDt1_HAS_SEC100_IN_TIMEREC
  + time.Sec100*10
#endif
  - start_mseconds;
  CLS1_SendNum32s(mseconds, io->stdOut);
  CLS1_SendStr((const unsigned char*)" ms for reading (", io->stdOut);
  CLS1_SendNum32s((100*1000)/mseconds, io->stdOut);
  CLS1_SendStr((const unsigned char*)" kB/s)\r\n", io->stdOut);

  /* copy benchmark */
  CLS1_SendStr((const unsigned char*)"Copy 100kB file...\r\n", io->stdOut);
  (void)TmDt1_GetTime(&startTime);
  (void)FS_CopyFile((const unsigned char*)"./bench.txt", (const unsigned char*)"./copy.txt", io);
  (void)TmDt1_GetTime(&time);
  start_mseconds = startTime.Hour*60*60*1000 + startTime.Min*60*1000 + startTime.Sec*1000
#if TmDt1_HAS_SEC100_IN_TIMEREC
  + startTime.Sec100*10
#endif
  ;
  mseconds = time.Hour*60*60*1000 + time.Min*60*1000 + time.Sec*1000
#if TmDt1_HAS_SEC100_IN_TIMEREC
  + time.Sec100*10
#endif
  - start_mseconds;
  CLS1_SendNum32s(mseconds, io->stdOut);
  CLS1_SendStr((const unsigned char*)" ms for copy (", io->stdOut);
  CLS1_SendNum32s((100*1000)/mseconds, io->stdOut);
  CLS1_SendStr((const unsigned char*)" kB/s)\r\n", io->stdOut);
  CLS1_SendStr((const unsigned char*)"done!\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t FS_PrintStatus(CLS1_ConstStdIOType *io) {
  CLS1_SendStatusStr((const unsigned char*)"FS", (const unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((const unsigned char*)"  mounted", FS_isMounted?"yes\r\n":"no\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t FS_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io) {
  unsigned char fileNameSrc[FS_FILE_NAME_SIZE], fileNameDst[FS_FILE_NAME_SIZE];
  size_t lenRead;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "FS help")==0) {
    CLS1_SendHelpStr((unsigned char*)"FS", (const unsigned char*)"Group of FS commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  format", (const unsigned char*)"Format the file system\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  mount", (const unsigned char*)"Mount the file system\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  unmount", (const unsigned char*)"unmount the file system\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  ls", (const unsigned char*)"List directory and files\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  rm <file>", (const unsigned char*)"Remove a file\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  mv <src> <dst>", (const unsigned char*)"Rename a file\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  cp <src> <dst>", (const unsigned char*)"Copy a file\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  printhex <file>", (const unsigned char*)"Print the file data in hexadecimal format\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  benchmark", (const unsigned char*)"Run a benchmark to measure performance\r\n", io->stdOut);
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
  } else if (UTIL1_strcmp((char*)cmd, "FS unmount")==0) {
    *handled = TRUE;
    return FS_Unmount(io);
  } else if (UTIL1_strcmp((char*)cmd, "FS ls")==0) {
    *handled = TRUE;
    return FS_Dir(NULL, io);
  } else if (UTIL1_strcmp((char*)cmd, "FS benchmark")==0) {
    *handled = TRUE;
    return FS_RunBenchmark(io);
  } else if (UTIL1_strncmp((char*)cmd, "FS printhex ", sizeof("FS printhex ")-1)==0) {
    *handled = TRUE;
    if (   (UTIL1_ReadEscapedName(cmd+sizeof("FS printhex ")-1, fileNameSrc,
            sizeof(fileNameSrc), &lenRead, NULL, NULL)==ERR_OK)
       )
    {
      return FS_PrintHexFile(fileNameSrc, io);
    }
    return ERR_FAILED;
  } else if (UTIL1_strncmp((char*)cmd, "FS rm ", sizeof("FS rm ")-1)==0) {
    *handled = TRUE;
    if (   (UTIL1_ReadEscapedName(cmd+sizeof("FS rm ")-1, fileNameSrc,
            sizeof(fileNameSrc), &lenRead, NULL, NULL)==ERR_OK)
       )
    {
      return FS_RemoveFile(fileNameSrc, io);
    }
    return ERR_FAILED;
  } else if (UTIL1_strncmp((char*)cmd, "FS mv ", sizeof("FS mv ")-1)==0) {
    *handled = TRUE;
    if (   (UTIL1_ReadEscapedName(cmd+sizeof("FS mv ")-1, fileNameSrc,
            sizeof(fileNameSrc), &lenRead, NULL, NULL)==ERR_OK)
        && *(cmd+sizeof("FS cp ")-1+lenRead)==' '
        && (UTIL1_ReadEscapedName(cmd+sizeof("FS mv ")-1+lenRead+1,
            fileNameDst,
            sizeof(fileNameDst), NULL, NULL, NULL)==ERR_OK)
       )
    {
      return FS_MoveFile(fileNameSrc, fileNameDst, io);
    }
    return ERR_FAILED;
  } else if (UTIL1_strncmp((char*)cmd, "FS cp ", sizeof("FS cp ")-1)==0) {
    *handled = TRUE;
    if (   (UTIL1_ReadEscapedName(cmd+sizeof("FS cp ")-1, fileNameSrc,
            sizeof(fileNameSrc), &lenRead, NULL, NULL)==ERR_OK)
        && *(cmd+sizeof("FS cp ")-1+lenRead)==' '
        && (UTIL1_ReadEscapedName(cmd+sizeof("FS cp ")-1+lenRead+1,
            fileNameDst,
            sizeof(fileNameDst), NULL, NULL, NULL)==ERR_OK)
       )
    {
      return FS_CopyFile(fileNameSrc, fileNameDst, io);
    }
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t FS_Init(void) {
  if (W25_Init()!=ERR_OK) {
    return ERR_FAILED;
  }
  return ERR_OK;
}


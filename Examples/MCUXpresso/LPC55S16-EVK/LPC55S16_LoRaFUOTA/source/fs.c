/*
 * fs.c
 *
 *  Created on: 06.01.2019
 *      Author: Erich Styger
 */
#include "fs.h"
#include "W25Q128.h"
#include "McuShell.h"
#include "McuUtility.h"
#include "McuTimeDate.h"
//#include "TmDt1.h"
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
  .read_size = 256,
  .prog_size = 256,
  .block_size = 4096,
  .block_count = 4096, /* 4096 * 4K = 16 MByte */
  .lookahead = 128,
};

uint8_t FS_Format(const McuShell_ConstStdIOType *io) {
  int res;

  if (FS_isMounted) {
    if (io!=NULL) {
      McuShell_SendStr("File system is mounted, unmount it first.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  if (io!=NULL) {
    McuShell_SendStr("Formatting ...", io->stdOut);
  }
  res = lfs_format(&FS_lfs, &FS_cfg);
  if (res==LFS_ERR_OK) {
    if (io!=NULL) {
      McuShell_SendStr(" done.\r\n", io->stdOut);
    }
    return ERR_OK;
  } else {
    if (io!=NULL) {
      McuShell_SendStr(" FAILED!\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
}

uint8_t FS_Mount(const McuShell_ConstStdIOType *io) {
  int res;

  if (FS_isMounted) {
    if (io!=NULL) {
      McuShell_SendStr("File system is already mounted.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  if (io!=NULL) {
    McuShell_SendStr("Mounting ...", io->stdOut);
  }
  res = lfs_mount(&FS_lfs, &FS_cfg);
  if (res==LFS_ERR_OK) {
    if (io!=NULL) {
      McuShell_SendStr(" done.\r\n", io->stdOut);
    }
    FS_isMounted = TRUE;
    return ERR_OK;
  } else {
    if (io!=NULL) {
      McuShell_SendStr(" FAILED!\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
}

uint8_t FS_Unmount(const McuShell_ConstStdIOType *io) {
  int res;

  if (!FS_isMounted) {
    if (io!=NULL) {
      McuShell_SendStr("File system is already unmounted.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  if (io!=NULL) {
    McuShell_SendStr("Unmounting ...", io->stdOut);
  }
  res = lfs_unmount(&FS_lfs);
  if (res==LFS_ERR_OK) {
    if (io!=NULL) {
      McuShell_SendStr(" done.\r\n", io->stdOut);
    }
    FS_isMounted = FALSE;
    return ERR_OK;
  } else {
    if (io!=NULL) {
      McuShell_SendStr(" FAILED!\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
}

uint8_t FS_Dir(const char *path, const McuShell_ConstStdIOType *io) {
  int res;
  lfs_dir_t dir;
  struct lfs_info info;

  if (io==NULL) {
    return ERR_FAILED; /* listing a directory without an I/O channel does not make any sense */
  }
  if (!FS_isMounted) {
    McuShell_SendStr("File system is not mounted, mount it first.\r\n", io->stdErr);
    return ERR_FAILED;
  }
  if (path==NULL) {
    path = "/"; /* default path */
  }
  res = lfs_dir_open(&FS_lfs, &dir, path);
  if (res!=LFS_ERR_OK) {
    McuShell_SendStr("FAILED lfs_dir_open()!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  for(;;) {
    res = lfs_dir_read(&FS_lfs, &dir, &info);
    if (res < 0) {
      McuShell_SendStr("FAILED lfs_dir_read()!\r\n", io->stdErr);
      return ERR_FAILED;
    }
    if (res == 0) { /* no more files */
       break;
    }
    switch (info.type) {
      case LFS_TYPE_REG: McuShell_SendStr("reg ", io->stdOut); break;
      case LFS_TYPE_DIR: McuShell_SendStr("dir ", io->stdOut); break;
      default:           McuShell_SendStr("?   ", io->stdOut); break;
    }
    static const char *prefixes[] = {"", "K", "M", "G"}; /* prefixes for kilo, mega and giga */
    for (int i = sizeof(prefixes)/sizeof(prefixes[0])-1; i >= 0; i--) {
        if (info.size >= (1 << 10*i)-1) {
            McuShell_printf("%*u%sB ", 4-(i != 0), info.size >> 10*i, prefixes[i]); /* \todo: remove printf */
            break;
        }
    } /* for */
    McuShell_SendStr(info.name, io->stdOut);
    McuShell_SendStr("\r\n", io->stdOut);
  } /* for */
  res = lfs_dir_close(&FS_lfs, &dir);
  if (res!=LFS_ERR_OK) {
    McuShell_SendStr("FAILED lfs_dir_close()!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t FS_CopyFile(const char *srcPath, const char *dstPath, const McuShell_ConstStdIOType *io) {
  lfs_file_t fsrc, fdst;
  uint8_t res =  ERR_OK;
  int result, nofBytesRead;
  uint8_t buffer[32];   /* copy buffer */

  if (!FS_isMounted) {
    if (io!=NULL) {
      McuShell_SendStr("ERROR: File system is not mounted.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }

  /* open source file */
  result = lfs_file_open(&FS_lfs, &fsrc, srcPath, LFS_O_RDONLY);
  if (result<0) {
    McuShell_SendStr((const unsigned char*)"*** Failed opening source file!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  /* create destination file */
  result = lfs_file_open(&FS_lfs, &fdst, dstPath, LFS_O_WRONLY | LFS_O_CREAT);
  if (result<0) {
    (void)lfs_file_close(&FS_lfs, &fsrc);
    McuShell_SendStr((const unsigned char*)"*** Failed opening destination file!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  /* now copy source to destination */
  for (;;) {
    nofBytesRead = lfs_file_read(&FS_lfs, &fsrc, buffer, sizeof(buffer));
    if (nofBytesRead<0) {
      McuShell_SendStr((const unsigned char*)"*** Failed reading source file!\r\n", io->stdErr);
      res = ERR_FAILED;
      break;
    }
    if (nofBytesRead==0) { /* end of file */
      break;
    }
    result = lfs_file_write(&FS_lfs, &fdst, buffer, nofBytesRead);
    if (result<0) {
      McuShell_SendStr((const unsigned char*)"*** Failed writing destination file!\r\n", io->stdErr);
      res = ERR_FAILED;
      break;
    }
  } /* for */
  /* close all files */
  result = lfs_file_close(&FS_lfs, &fsrc);
  if (result<0) {
    McuShell_SendStr((const unsigned char*)"*** Failed closing source file!\r\n", io->stdErr);
    res = ERR_FAILED;
  }
  result = lfs_file_close(&FS_lfs, &fdst);
  if (result<0) {
    McuShell_SendStr((const unsigned char*)"*** Failed closing destination file!\r\n", io->stdErr);
    res = ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t FS_MoveFile(const char *srcPath, const char *dstPath, const McuShell_ConstStdIOType *io) {
  if (!FS_isMounted) {
    if (io!=NULL) {
      McuShell_SendStr("ERROR: File system is not mounted.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  if (lfs_rename(&FS_lfs, srcPath, dstPath)<0) {
    if (io!=NULL) {
      McuShell_SendStr("ERROR: failed renaming file or directory.\r\n", io->stdErr);
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

uint8_t FS_PrintHexFile(const char *filePath, const McuShell_ConstStdIOType *io) {
  lfs_file_t file;
  uint8_t res = ERR_OK;
  int32_t fileSize;
  int result;

  if (io==NULL) {
    return ERR_FAILED; /* printing a file without an I/O channel does not make any sense */
  }
  if (!FS_isMounted) {
    if (io!=NULL) {
      McuShell_SendStr("ERROR: File system is not mounted.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  result = lfs_file_open(&FS_lfs, &file, filePath, LFS_O_RDONLY);
  if (result<0) {
    if (io!=NULL) {
      McuShell_SendStr("ERROR: Failed opening file.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  fileSize = lfs_file_size(&FS_lfs, &file);
  if (fileSize<0) {
    if (io!=NULL) {
      McuShell_SendStr("ERROR: getting file size\r\n", io->stdErr);
      (void)lfs_file_close(&FS_lfs, &file);
    }
    return ERR_FAILED;
  }
  res = McuShell_PrintMemory(&file, 0, fileSize-1, 4, 16, readFromFile, io);
  if (res!=ERR_OK) {
    McuShell_SendStr("ERROR while calling PrintMemory()\r\n", io->stdErr);
  }
  (void)lfs_file_close(&FS_lfs, &file);
  return res;
}

uint8_t FS_RemoveFile(const char *filePath, const McuShell_ConstStdIOType *io) {
  int result;

  if (!FS_isMounted) {
    if (io!=NULL) {
      McuShell_SendStr("ERROR: File system is not mounted.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  result = lfs_remove(&FS_lfs, filePath);
  if (result<0) {
    if (io!=NULL) {
      McuShell_SendStr("ERROR: Failed removing file.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t FS_RunBenchmark(const McuShell_ConstStdIOType *io) {
  lfs_file_t file;
  int result;
  uint32_t i;
  uint8_t read_buf[10];
  TIMEREC time, startTime;
  int32_t start_mseconds, mseconds;

  if (!FS_isMounted) {
    if (io!=NULL) {
      McuShell_SendStr("ERROR: File system is not mounted.\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  /* write benchmark */
  McuShell_SendStr((const unsigned char*)"Benchmark: write/copy/read a 100kB file:\r\n", io->stdOut);
  McuShell_SendStr((const unsigned char*)"Delete existing benchmark files...\r\n", io->stdOut);
  (void)FS_RemoveFile((const unsigned char*)"./bench.txt", io);
  (void)FS_RemoveFile((const unsigned char*)"./copy.txt", io);

  McuShell_SendStr((const unsigned char*)"Create benchmark file...\r\n", io->stdOut);
  (void)McuTimeDate_GetTime(&startTime);
  if (lfs_file_open(&FS_lfs, &file, "./bench.txt", LFS_O_WRONLY | LFS_O_CREAT)<0) {
    McuShell_SendStr((const unsigned char*)"*** Failed creating benchmark file!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  for(i=0;i<10240;i++) {
    if (lfs_file_write(&FS_lfs, &file, "benchmark ", sizeof("benchmark ")-1)<0) {
      McuShell_SendStr((const unsigned char*)"*** Failed writing file!\r\n", io->stdErr);
      (void)lfs_file_close(&FS_lfs, &file);
      return ERR_FAILED;
    }
  }
  (void)lfs_file_close(&FS_lfs, &file);
  (void)McuTimeDate_GetTime(&time);
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
  McuShell_SendNum32s(mseconds, io->stdOut);
  McuShell_SendStr((const unsigned char*)" ms for writing (", io->stdOut);
  McuShell_SendNum32s((100*1000)/mseconds, io->stdOut);
  McuShell_SendStr((const unsigned char*)" kB/s)\r\n", io->stdOut);

  /* read benchmark */
  McuShell_SendStr((const unsigned char*)"Read 100kB benchmark file...\r\n", io->stdOut);
  (void)McuTimeDate_GetTime(&startTime);
  if (lfs_file_open(&FS_lfs, &file, "./bench.txt", LFS_O_RDONLY)<0) {
    McuShell_SendStr((const unsigned char*)"*** Failed opening benchmark file!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  for(i=0;i<10240;i++) {
    if (lfs_file_read(&FS_lfs, &file, &read_buf[0], sizeof(read_buf))<0) {
      McuShell_SendStr((const unsigned char*)"*** Failed reading file!\r\n", io->stdErr);
      (void)lfs_file_close(&FS_lfs, &file);
      return ERR_FAILED;
    }
  }
  (void)lfs_file_close(&FS_lfs, &file);
  (void)McuTimeDate_GetTime(&time);
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
  McuShell_SendNum32s(mseconds, io->stdOut);
  McuShell_SendStr((const unsigned char*)" ms for reading (", io->stdOut);
  McuShell_SendNum32s((100*1000)/mseconds, io->stdOut);
  McuShell_SendStr((const unsigned char*)" kB/s)\r\n", io->stdOut);

  /* copy benchmark */
  McuShell_SendStr((const unsigned char*)"Copy 100kB file...\r\n", io->stdOut);
  (void)McuTimeDate_GetTime(&startTime);
  (void)FS_CopyFile((const unsigned char*)"./bench.txt", (const unsigned char*)"./copy.txt", io);
  (void)McuTimeDate_GetTime(&time);
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
  McuShell_SendNum32s(mseconds, io->stdOut);
  McuShell_SendStr((const unsigned char*)" ms for copy (", io->stdOut);
  McuShell_SendNum32s((100*1000)/mseconds, io->stdOut);
  McuShell_SendStr((const unsigned char*)" kB/s)\r\n", io->stdOut);
  McuShell_SendStr((const unsigned char*)"done!\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t FS_PrintStatus(const McuShell_ConstStdIOType *io) {
  uint8_t buf[24];

  McuShell_SendStatusStr((const unsigned char*)"FS", (const unsigned char*)"\r\n", io->stdOut);
  McuShell_SendStatusStr((const unsigned char*)"  mounted", FS_isMounted?"yes\r\n":"no\r\n", io->stdOut);

  McuUtility_Num32uToStr(buf, sizeof(buf), FS_cfg.block_count*FS_cfg.block_size);
  McuUtility_strcat(buf, sizeof(buf), " bytes\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  space", buf, io->stdOut);

  McuUtility_Num32uToStr(buf, sizeof(buf), FS_cfg.read_size);
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  read_size", buf, io->stdOut);

  McuUtility_Num32uToStr(buf, sizeof(buf), FS_cfg.prog_size);
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  prog_size", buf, io->stdOut);

  McuUtility_Num32uToStr(buf, sizeof(buf), FS_cfg.block_size);
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  block_size", buf, io->stdOut);

  McuUtility_Num32uToStr(buf, sizeof(buf), FS_cfg.block_count);
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  block_count", buf, io->stdOut);

  McuUtility_Num32uToStr(buf, sizeof(buf), FS_cfg.lookahead);
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  lookahead", buf, io->stdOut);
  return ERR_OK;
}

uint8_t FS_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  unsigned char fileNameSrc[FS_FILE_NAME_SIZE], fileNameDst[FS_FILE_NAME_SIZE];
  size_t lenRead;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "FS help")==0) {
    McuShell_SendHelpStr((unsigned char*)"FS", (const unsigned char*)"Group of FS commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  format", (const unsigned char*)"Format the file system\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  mount", (const unsigned char*)"Mount the file system\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  unmount", (const unsigned char*)"unmount the file system\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  ls", (const unsigned char*)"List directory and files\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  rm <file>", (const unsigned char*)"Remove a file\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  mv <src> <dst>", (const unsigned char*)"Rename a file\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  cp <src> <dst>", (const unsigned char*)"Copy a file\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  printhex <file>", (const unsigned char*)"Print the file data in hexadecimal format\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  benchmark", (const unsigned char*)"Run a benchmark to measure performance\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0 || McuUtility_strcmp((char*)cmd, "FS status")==0) {
    *handled = TRUE;
    return FS_PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "FS format")==0) {
    *handled = TRUE;
    return FS_Format(io);
  } else if (McuUtility_strcmp((char*)cmd, "FS mount")==0) {
    *handled = TRUE;
    return FS_Mount(io);
  } else if (McuUtility_strcmp((char*)cmd, "FS unmount")==0) {
    *handled = TRUE;
    return FS_Unmount(io);
  } else if (McuUtility_strcmp((char*)cmd, "FS ls")==0) {
    *handled = TRUE;
    return FS_Dir(NULL, io);
  } else if (McuUtility_strcmp((char*)cmd, "FS benchmark")==0) {
    *handled = TRUE;
    return FS_RunBenchmark(io);
  } else if (McuUtility_strncmp((char*)cmd, "FS printhex ", sizeof("FS printhex ")-1)==0) {
    *handled = TRUE;
    if (   (McuUtility_ReadEscapedName(cmd+sizeof("FS printhex ")-1, fileNameSrc,
            sizeof(fileNameSrc), &lenRead, NULL, NULL)==ERR_OK)
       )
    {
      return FS_PrintHexFile(fileNameSrc, io);
    }
    return ERR_FAILED;
  } else if (McuUtility_strncmp((char*)cmd, "FS rm ", sizeof("FS rm ")-1)==0) {
    *handled = TRUE;
    if (   (McuUtility_ReadEscapedName(cmd+sizeof("FS rm ")-1, fileNameSrc,
            sizeof(fileNameSrc), &lenRead, NULL, NULL)==ERR_OK)
       )
    {
      return FS_RemoveFile(fileNameSrc, io);
    }
    return ERR_FAILED;
  } else if (McuUtility_strncmp((char*)cmd, "FS mv ", sizeof("FS mv ")-1)==0) {
    *handled = TRUE;
    if (   (McuUtility_ReadEscapedName(cmd+sizeof("FS mv ")-1, fileNameSrc,
            sizeof(fileNameSrc), &lenRead, NULL, NULL)==ERR_OK)
        && *(cmd+sizeof("FS cp ")-1+lenRead)==' '
        && (McuUtility_ReadEscapedName(cmd+sizeof("FS mv ")-1+lenRead+1,
            fileNameDst,
            sizeof(fileNameDst), NULL, NULL, NULL)==ERR_OK)
       )
    {
      return FS_MoveFile(fileNameSrc, fileNameDst, io);
    }
    return ERR_FAILED;
  } else if (McuUtility_strncmp((char*)cmd, "FS cp ", sizeof("FS cp ")-1)==0) {
    *handled = TRUE;
    if (   (McuUtility_ReadEscapedName(cmd+sizeof("FS cp ")-1, fileNameSrc,
            sizeof(fileNameSrc), &lenRead, NULL, NULL)==ERR_OK)
        && *(cmd+sizeof("FS cp ")-1+lenRead)==' '
        && (McuUtility_ReadEscapedName(cmd+sizeof("FS cp ")-1+lenRead+1,
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
  return FS_Mount(NULL);
}


/*
 * LiDoReader.c
 *
 *  Created on: 03.03.2026
 *      Author: Erich Styger
 */

#include "platform.h"
#if PL_CONFIG_USE_LIDO_READER
#include "LiDoReader.h"
#include "McuShell.h"
#include "McuUtility.h"
#include "FatFS/McuFatFS.h"
#include "McuLog.h"

/* date files look like this:
FS printhex Samples/07_12_2025/00.bin
0x00000000: 4C 69 44 6F 20 53 61 6D 70 6C 65 20 46 69 6C 65  LiDo Sample File
0x00000010: 20 56 31 2E 30 0D 0A 7F C3 34 69 03 00 00 00 00   V1.0...4i.....
*/

static uint8_t ParseLine(const unsigned char *buf, uint32_t *addr, uint32_t *lineNumber) {
  (*lineNumber)++;
  if (buf[0]=='0' && buf[1]=='x' && buf[10]==':' && buf[11]==' ') { /* starting line with address, e.g. "0x00000000: " */
    const unsigned char *p;
    int32_t value;
    uint8_t res;
    unsigned char addrBuf[sizeof("0x00000000")]; /* includes space for zero byte */
    #define ADDRESS_INCREMENT_VALUE (16) /* address increment in file */

    strncpy((char*)addrBuf, (char*)buf, sizeof("0x00000000")-1);
    addrBuf[sizeof("0x00000000")-1] = '\0';
    p = addrBuf;
    res = McuUtility_xatoi(&p, &value);
    if (res!=ERR_OK) {
      McuLog_error("xatoi() failed at line %d", *lineNumber);
      return ERR_FAILED;
    }
    if (*addr!=0 && value!=0 && *addr!=value-ADDRESS_INCREMENT_VALUE) { /* check that we have not missed something */
      McuLog_error("at line %d, reading address %x, expecting %x", *lineNumber, value, (*addr)+ADDRESS_INCREMENT_VALUE);
      return ERR_FAILED;
    }
    *addr = value;
  } else if (buf[0]=='\r' && buf[1]=='\n' && buf[2]=='\0') {
//    McuLog_info("ignoring empty line at %d", *lineNumber);
  } else if (McuUtility_strncmp((const char*)buf, "FS printhex ", sizeof("FS printhex ")-1)==0 || McuUtility_strncmp((const char*)buf, "CMD> FS printhex ", sizeof("CMD> FS printhex ")-1)==0) {
    McuLog_info("file name at line %d: %s", *lineNumber, buf);
  } else {
    /* e.g. text line at the beginning: ignore */
    McuLog_info("ignoring line %d: %s", *lineNumber, buf);
  }
  return ERR_OK;
}

static uint8_t ReadLine(McuFatFS_FIL *file, unsigned char *buf, size_t bufSize) {
  McuFatFS_FRESULT fres;
  UINT nofRead = 0;
  int i = 0;

  while(i<bufSize-1) { /* -1 for zero byte at the end */
    fres = McuFatFS_read(file, &buf[i], 1, &nofRead);
    if (fres!= FR_OK) {
      McuLog_error("read failed");
      return ERR_FAILED;
    }
    if (nofRead==0) {
      McuLog_info("reached end of file");
      return ERR_BREAK;
    }
    if (buf[i]=='\n') {
      buf[i+1] = '\0';
      return ERR_OK;
    }
    i++;
  }
  return ERR_OVERFLOW;
}

static uint8_t PrintFile(const uint8_t *fileName, const McuShell_StdIOType *io) {
  static McuFatFS_FIL file;
  McuFatFS_FRESULT fres = FR_OK;
  uint8_t buf[128];
  uint8_t res = ERR_OK;
  uint32_t addr = 0;
  uint32_t lineNumber = 0;

  fres = McuFatFS_open(&file, (const TCHAR *)fileName, FA_READ);
  if (fres == FR_OK) {
    for(;;) { /* breaks */
      res = ReadLine(&file, buf, sizeof(buf));
      if (res==ERR_BREAK) {
        McuLog_info("reached end of file");
        res = ERR_OK;
        break;
      }
      if (res!=ERR_OK) {
        McuLog_error("ReadLine() failed");
        break;
      }
      res = ParseLine(buf, &addr, &lineNumber);
      if (res!=ERR_OK) {
        McuLog_error("ParseLine() failed");
        break;
      }
 //     nofRead = 0;
//      fres=McuFatFS_read(&file, buf, sizeof(buf)-1, &nofRead); /* read one byte less for zero byte */
//      if (fres != FR_OK) {
//        McuShell_SendStr((unsigned char*)"fread failed\r\n", io->stdErr);
//        res = ERR_FAILED;
 //     } else {
 //       buf[nofRead] = '\0'; /* terminate buffer */
 //       McuShell_SendStr(buf, io->stdOut);
 //     }
    } /* for */
    fres=McuFatFS_close(&file);
    if (fres != FR_OK) {
      McuShell_SendStr((unsigned char*)"fclose failed\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else {
    McuLog_error("open file failed");
    res = ERR_FAILED;
  }
  McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
  return res;
}

static uint8_t ConvertFile(const unsigned char *name, const McuShell_ConstStdIOType *io) {
  /* precondition: cmd starts with the file name */
  uint8_t res = ERR_OK;
  uint8_t fileName[64];

  if (McuUtility_ReadEscapedName(name, fileName,
        sizeof(fileName), NULL, NULL, NULL)==ERR_OK
     )
  {
    res = PrintFile((uint8_t*)fileName, io);
  } else {
    res = ERR_FAILED;
    McuLog_error("reading file name failed");
  }
  return res;
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  McuShell_SendStatusStr((unsigned char*)"lido", (unsigned char*)"lido reader status\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"lido", (unsigned char*)"Group of lido reader commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  convert <file>", (unsigned char*)"Convert a text dump file produced with printhex\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t LiDoReader_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "lido help") == 0)
  {
    *handled = true;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "lido status")==0)
            )
  {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "lido convert ", sizeof("lido convert ")-1)==0) {
    *handled = true;
    return ConvertFile(cmd+sizeof("lido convert ")-1, io);
  }
  return ERR_OK;
}

void LiDoReader_Init(void) {
}

#endif /* PL_CONFIG_USE_LIDO_READER */

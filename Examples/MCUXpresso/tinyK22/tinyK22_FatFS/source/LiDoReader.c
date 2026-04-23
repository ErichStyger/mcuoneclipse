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
#include "McuRB.h"
#include "McuTimeDate.h"

/* date files look like this:
FS printhex Samples/07_12_2025/00.bin
0x00000000: 4C 69 44 6F 20 53 61 6D 70 6C 65 20 46 69 6C 65  LiDo Sample File
0x00000010: 20 56 31 2E 30 0D 0A 7F C3 34 69 03 00 00 00 00   V1.0...4i.....
*/
#define DATA_FILE_HEX_NOF_ITEMS  (16) /* there are 16 hex numbers in each line */

typedef struct liDoSample_t {
  int32_t unixTimeStamp;
  uint8_t lightIntTime;
  uint8_t lightGain;
  uint16_t lightChannelX;
  uint16_t lightChannelY;
  uint16_t lightChannelZ;
  uint16_t lightChannelNIR;
  uint16_t lightChannelB440;
  uint16_t lightChannelB490;
  int8_t accelX;
  int8_t accelY;
  int8_t accelZ;
  uint8_t temp; //Bit7 = UserButtonMarker
  uint8_t crc;
} liDoSample_t;

typedef struct dataInfo_t {
  McuFatFS_FIL srcFile; /* source file descriptor */
  McuFatFS_FIL dstFile; /* destination file descriptor */
  uint32_t lineNumber; /* line number inside file */
  uint32_t addr; /* address noted in file */
  McuRB_Handle_t dataRingBuffer; /* read binary data from file */
} dataInfo_t;

static dataInfo_t dataInfo;

static uint8_t DecodeLine(const unsigned char *buf, uint32_t *addr, uint32_t *lineNumber) {
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
    p = buf + sizeof("0x00000000: ")-1; /* pointing to the first byte (hex), e.g. "4C 69 44 6F 20 53 61 6D 70 6C 65 20 46 69 6C 65" */
    for(int i=0; i<DATA_FILE_HEX_NOF_ITEMS; i++) {
      uint8_t val;

      if (*p=='-') { /* empty numbers in a line of data are like this: "-- -- ..." */
          break;
      }
      if (McuUtility_ScanHex8uNumberNoPrefix(&p, &val)==ERR_OK) {
        if (McuRB_Put(dataInfo.dataRingBuffer, &val)!=ERR_OK) {
          McuLog_error("failed to store data in ring buffer");
        }
      }
    }
  } else if (buf[0]=='\r' && buf[1]=='\n' && buf[2]=='\0') {
    /* McuLog_info("ignoring empty line at %d", *lineNumber); */
  } else if (McuUtility_strncmp((const char*)buf, "FS printhex ", sizeof("FS printhex ")-1)==0 || McuUtility_strncmp((const char*)buf, "CMD> FS printhex ", sizeof("CMD> FS printhex ")-1)==0) {
    const unsigned char *p;
    unsigned char dataFileName[sizeof("Samples/07_12_2025/23.bin")];

    if (McuUtility_strncmp((const char*)buf, "FS printhex ", sizeof("FS printhex ")-1)==0) {
      p = buf+sizeof("FS printhex ")-1;
    } else {
      p = buf+sizeof("CMD> FS printhex ")-1;
    }
    dataFileName[0] = '\0';
    while(*p!='\r' && *p!='\0') {
      McuUtility_chcat(dataFileName, sizeof(dataFileName), *p);
      p++;
    }
    McuLog_info("file name at line %d: %s", *lineNumber, dataFileName);
  } else {
    /* e.g. text line at the beginning: ignore */
    McuLog_info("ignoring line %d: %s", *lineNumber, buf);
  }
  return ERR_OK;
}

static uint8_t ReadLine(dataInfo_t *info, unsigned char *buf, size_t bufSize) {
  McuFatFS_FRESULT fres;
  UINT nofRead = 0;
  int i = 0;

  while(i<bufSize-1) { /* -1 for zero byte at the end */
    fres = McuFatFS_read(&info->srcFile, &buf[i], 1, &nofRead);
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

static int ReadNextLine(dataInfo_t *info) {
  int res = ERR_OK;
  uint8_t buf[128];

  for(;;) { /* breaks */
    res = ReadLine(info, buf, sizeof(buf));
    if (res==ERR_BREAK) {
      res = EOF;
      break;
    }
    if (res!=ERR_OK) {
      McuLog_error("ReadLine() failed");
      break;
    }
    res = DecodeLine(buf, &info->addr, &info->lineNumber);
    if (res!=ERR_OK) {
      McuLog_error("ParseLine() failed");
      break;
    }
    break;
  } /* for */
  return res;
}

int getChar(dataInfo_t *info) {
  uint8_t ch, res;

  res = McuRB_Get(info->dataRingBuffer, &ch);
  if (res==ERR_NOTAVAIL) { /* buffer empty */
    if (ReadNextLine(info)==EOF) {
      return EOF;
    }
    return getChar(info);
  } else {
    return ch;
  }
}

static int readHeader(dataInfo_t *info) {
  int res = ERR_OK;
  int ch;
  unsigned char headerBuf[64];

  headerBuf[0] = '\0';
  for(;;) { /* breaks */
    ch = getChar(info); /* just consume the data */
    if (ch==EOF){ /* end of file reached */
      res = EOF;
      break;
    }
    if (ch=='\r' && getChar(info)=='\n') { /* reached end of header */
      res = ERR_OK;
      break;
    }
    McuUtility_chcat(headerBuf, sizeof(headerBuf), ch);
  } /* for */
  McuLog_info("header: %s", headerBuf);
  return res;
}

static int read_u8(dataInfo_t *info, uint8_t *data) {
  int res = ERR_OK;
  int ch;

  for(;;) { /* breaks */
    ch = getChar(info);
    if (ch==EOF){ /* end of file reached */
      res = EOF;
      break;
    }
    *data = ch;
    break;
  }
  return res;
}

static int read_i8(dataInfo_t *info, int8_t *data) {
  return read_u8(info, (uint8_t*)data);
}

static int read_u16(dataInfo_t *info, uint16_t *data) {
  int res = ERR_OK;
  uint8_t u8_0, u8_1;

  for(;;) { /* breaks */
    res = read_u8(info, &u8_0);
    if (res==EOF){ /* end of file reached */
      break;
    }
    res = read_u8(info, &u8_1);
    if (res==EOF){ /* end of file reached */
      break;
    }
    *data = (u8_1<<8) | u8_0;
    break;
  }
  return res;
}

#if 0 /* not used */
static int read_i16(dataInfo_t *info, int16_t *data) {
  return read_u16(info, (uint16_t*)data);
}
#endif

static int read_i32(dataInfo_t *info, int32_t *data) {
  int res = ERR_OK;
  uint16_t u16_0, u16_1;

  for(;;) { /* breaks */
    res = read_u16(info, &u16_0);
    if (res==EOF){ /* end of file reached */
      break;
    }
    res = read_u16(info, &u16_1);
    if (res==EOF){ /* end of file reached */
      break;
    }
    *data = (u16_1<<16) | u16_0;
    break;
  }
  return res;
}

#define CRC8_POLYNOM (0x07)

static uint8_t crc8_bytecalc(unsigned char byte, uint8_t* seed) {
  uint8_t i;
  uint8_t flag;
  uint8_t polynom = CRC8_POLYNOM;

  for (i = 0; i < 8; i++) {
    if (*seed & 0x80) {
      flag = 1;
    } else {
      flag = 0;
    }
    *seed <<= 1;
    if (byte & 0x80) {
      *seed |= 1;
    }
    byte <<= 1;
    if (flag) {
      *seed ^= polynom;
    }
  }
  return *seed;
}

static uint8_t crc8_liDoSample(liDoSample_t *sample) {
  uint8_t crc, seed = 0;

  crc = crc8_bytecalc((uint8_t) sample->unixTimeStamp, &seed); /* Byte 1 */
  crc = crc8_bytecalc((uint8_t) (sample->unixTimeStamp >> 8), &seed); /* Byte 2 */
  crc = crc8_bytecalc((uint8_t) (sample->unixTimeStamp >> 16), &seed); /* Byte 3 */
  crc = crc8_bytecalc((uint8_t) (sample->unixTimeStamp >> 24), &seed); /* Byte 4 */
  crc = crc8_bytecalc((uint8_t) sample->lightGain, &seed); /* Byte 5 */
  crc = crc8_bytecalc((uint8_t) sample->lightIntTime, &seed); /* Byte 6 */
  crc = crc8_bytecalc((uint8_t) sample->lightChannelX, &seed); /* Byte 7 */
  crc = crc8_bytecalc((uint8_t) (sample->lightChannelX >> 8), &seed); /* Byte 8 */
  crc = crc8_bytecalc((uint8_t) sample->lightChannelY, &seed); /* Byte 9 */
  crc = crc8_bytecalc((uint8_t) (sample->lightChannelY >> 8), &seed); /* Byte 10 */
  crc = crc8_bytecalc((uint8_t) sample->lightChannelZ, &seed); /* Byte 11 */
  crc = crc8_bytecalc((uint8_t) (sample->lightChannelZ >> 8), &seed); /* Byte 12 */
  crc = crc8_bytecalc((uint8_t) sample->lightChannelNIR, &seed); /* Byte 13 */
  crc = crc8_bytecalc((uint8_t) (sample->lightChannelNIR >> 8), &seed); /* Byte 14 */
  crc = crc8_bytecalc((uint8_t) sample->lightChannelB440, &seed); /* Byte 15 */
  crc = crc8_bytecalc((uint8_t) (sample->lightChannelB440 >> 8), &seed); /* Byte 16 */
  crc = crc8_bytecalc((uint8_t) sample->lightChannelB490, &seed); /* Byte 17 */
  crc = crc8_bytecalc((uint8_t) (sample->lightChannelB490 >> 8), &seed); /* Byte 18 */
  crc = crc8_bytecalc((uint8_t) sample->accelX, &seed); /* Byte 19 */
  crc = crc8_bytecalc((uint8_t) sample->accelY, &seed); /* Byte 20 */
  crc = crc8_bytecalc((uint8_t) sample->accelZ, &seed); /* Byte 21 */
  crc = crc8_bytecalc((uint8_t) sample->temp, &seed); /* Byte 22 */
  crc = crc8_bytecalc(0, &seed);
  return crc;
}

static int writeSampleHeaderCSV(dataInfo_t *info) {
  unsigned char buf[256];

  buf[0] = '\0';
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"time,gain,intTime,chX,chY,chZ,chNIR,chB440,chB490,accelX,accelY,accelZ,temp,crc");
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\n");
  int nof = McuFatFS_f_puts((const char*)buf, &info->dstFile);
  if (nof<0) {
    McuLog_error("failed writing to destination file");
    return ERR_FAILED;
  }
  return ERR_OK;
}

static int writeSampleToCSV(dataInfo_t *info, liDoSample_t *sample) {
  TIMEREC time;
  DATEREC date;
  unsigned char buf[256];

  buf[0] = '\0';
  McuTimeDate_UnixSecondsToTimeDate(sample->unixTimeStamp, 0, &time, &date);
  McuTimeDate_AddDateString(buf, sizeof(buf), &date, (unsigned char*)McuTimeDate_CONFIG_DEFAULT_DATE_FORMAT_STR);
  McuUtility_chcat(buf, sizeof(buf), ' ');
  McuTimeDate_AddTimeString(buf, sizeof(buf), &time, (unsigned char*)McuTimeDate_CONFIG_HH_MM_SS_TIME_FORMAT_STR);
  McuUtility_chcat(buf, sizeof(buf), ',');
  McuUtility_strcatNum8u(buf, sizeof(buf), sample->lightGain);
  McuUtility_chcat(buf, sizeof(buf), ',');
  McuUtility_strcatNum8u(buf, sizeof(buf), sample->lightIntTime);
  McuUtility_chcat(buf, sizeof(buf), ',');
  McuUtility_strcatNum16u(buf, sizeof(buf), sample->lightChannelX);
  McuUtility_chcat(buf, sizeof(buf), ',');
  McuUtility_strcatNum16u(buf, sizeof(buf), sample->lightChannelY);
  McuUtility_chcat(buf, sizeof(buf), ',');
  McuUtility_strcatNum16u(buf, sizeof(buf), sample->lightChannelZ);
  McuUtility_chcat(buf, sizeof(buf), ',');
  McuUtility_strcatNum16u(buf, sizeof(buf), sample->lightChannelNIR);
  McuUtility_chcat(buf, sizeof(buf), ',');
  McuUtility_strcatNum16u(buf, sizeof(buf), sample->lightChannelB440);
  McuUtility_chcat(buf, sizeof(buf), ',');
  McuUtility_strcatNum16u(buf, sizeof(buf), sample->lightChannelB490);
  McuUtility_chcat(buf, sizeof(buf), ',');
  McuUtility_strcatNum8s(buf, sizeof(buf), sample->accelX);
  McuUtility_chcat(buf, sizeof(buf), ',');
  McuUtility_strcatNum8s(buf, sizeof(buf), sample->accelY);
  McuUtility_chcat(buf, sizeof(buf), ',');
  McuUtility_strcatNum8s(buf, sizeof(buf), sample->accelZ);
  McuUtility_chcat(buf, sizeof(buf), ',');
  McuUtility_strcatNum8s(buf, sizeof(buf), sample->temp);
  McuUtility_chcat(buf, sizeof(buf), ',');
  McuUtility_strcatNum8s(buf, sizeof(buf), sample->crc);
  McuUtility_chcat(buf, sizeof(buf), '\n');
  int nof = McuFatFS_f_puts((const char*)buf, &info->dstFile);
  if (nof<0) {
    McuLog_error("failed writing to destination file");
    return ERR_FAILED;
  }
  return ERR_OK;
}

static int readDataSample(dataInfo_t *info, liDoSample_t *sample) {
  int res = ERR_OK;
  for(;;) { /* breaks */
    res = read_i32(info, &sample->unixTimeStamp);
    if (res!=ERR_OK) { break; }
    res = read_u8(info, &sample->lightGain);
    if (res!=ERR_OK) { break; }
    res = read_u8(info, &sample->lightIntTime);
    if (res!=ERR_OK) { break; }
    res = read_u16(info, &sample->lightChannelX);
    if (res!=ERR_OK) { break; }
    res = read_u16(info, &sample->lightChannelY);
    if (res!=ERR_OK) { break; }
    res = read_u16(info, &sample->lightChannelZ);
    if (res!=ERR_OK) { break; }
    res = read_u16(info, &sample->lightChannelNIR);
    if (res!=ERR_OK) { break; }
    res = read_u16(info, &sample->lightChannelB440);
    if (res!=ERR_OK) { break; }
    res = read_u16(info, &sample->lightChannelB490);
    if (res!=ERR_OK) { break; }
    res = read_i8(info, &sample->accelX);
    if (res!=ERR_OK) { break; }
    res = read_i8(info, &sample->accelY);
    if (res!=ERR_OK) { break; }
    res = read_i8(info, &sample->accelZ);
    if (res!=ERR_OK) { break; }
    res = read_u8(info, &sample->temp);
    if (res!=ERR_OK) { break; }
    res = read_u8(info, &sample->crc);
    if (res!=ERR_OK) { break; }
    break;
  }
  if (res!=ERR_OK) {
    return res;
  }
  uint8_t crc = crc8_liDoSample(sample);
  if (crc!=sample->crc) {
    McuLog_error("Wrong CRC %x, expected %x", crc, sample->crc);
    return ERR_FAILED;
  } else {
    res = writeSampleToCSV(info, sample);
  }
  return res;
}

static int convertFile(dataInfo_t *info) {
  int res = ERR_OK;
  liDoSample_t sample;

  if (readHeader(info)!=ERR_OK) {
    McuLog_error("failed reading header on line %d", info->lineNumber);
    return ERR_FAILED;
  }
  for(;;) { /* breaks */
    res = readDataSample(info, &sample);
    if (res==EOF) {
      return res;
    }
    if (res!=ERR_OK) {
      McuLog_error("failed reading data sample on line %d", info->lineNumber);
      res = ERR_FAILED;
      break;
    }
  } /* for */
  return res;
}

static uint8_t Convert(const uint8_t *srcFileName, const uint8_t *dstFileName, const McuShell_StdIOType *io) {
  McuFatFS_FRESULT fres = FR_OK;
  int res = ERR_OK;

  dataInfo.addr = 0;
  dataInfo.lineNumber = 0;

  McuRB_Config_t config;
  McuRB_GetDefaultconfig(&config);
  config.elementSize = 1;
  config.nofElements = 64;
  dataInfo.dataRingBuffer = McuRB_InitRB(&config);
  fres = McuFatFS_open(&dataInfo.dstFile, (const TCHAR *)dstFileName, FA_OPEN_APPEND|FA_WRITE);
  if (fres!=FR_OK) {
    McuLog_error("failed creating destination file '%s'", dstFileName);
    return ERR_FAILED;
  }
  fres = McuFatFS_open(&dataInfo.srcFile, (const TCHAR *)srcFileName, FA_READ);
  if (fres == FR_OK) {
    res = writeSampleHeaderCSV(&dataInfo);
    if (res!=ERR_OK) {
      McuLog_error("failed writing cvs header");
    }
    res = convertFile(&dataInfo);
    if (res!=EOF) {
      McuLog_error("failed converting file");
    } else {
      res = ERR_OK;
    }
    fres = McuFatFS_close(&dataInfo.srcFile);
    if (fres != FR_OK) {
      McuShell_SendStr((unsigned char*)"closing source file failed\r\n", io->stdErr);
      res = ERR_FAILED;
    }
    fres = McuFatFS_close(&dataInfo.dstFile);
    if (fres != FR_OK) {
      McuShell_SendStr((unsigned char*)"closing destination file failed\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else {
    McuLog_error("open file failed");
    res = ERR_FAILED;
  }
  dataInfo.dataRingBuffer = McuRB_DeinitRB(dataInfo.dataRingBuffer);
  return res;
}

static uint8_t ConvertFile(const unsigned char *name, const McuShell_ConstStdIOType *io) {
  /* precondition: cmd starts with the file name */
  uint8_t res = ERR_OK;
  uint8_t srcFileName[64];
  uint8_t dstfileName[64];
  size_t lenRead = 0;

  if (McuUtility_ReadEscapedName(name, srcFileName, sizeof(srcFileName), &lenRead, NULL, NULL)==ERR_OK) {
    name += lenRead+1;
    if (McuUtility_ReadEscapedName(name, dstfileName, sizeof(dstfileName), NULL, NULL, NULL)==ERR_OK) {
      res = Convert((uint8_t*)srcFileName, (uint8_t*)dstfileName, io);
    } else {
      res = ERR_FAILED;
      McuLog_error("reading destination file name failed");
    }
  } else {
    res = ERR_FAILED;
    McuLog_error("reading source file name failed");
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
  McuShell_SendHelpStr((unsigned char*)"  convert <infile> <csv>", (unsigned char*)"Convert a text dump file produced with printhex and appends data to csv file\r\n", io->stdOut);
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

void LiDoReader_Deinit(void) {
}

void LiDoReader_Init(void) {
}

#endif /* PL_CONFIG_USE_LIDO_READER */

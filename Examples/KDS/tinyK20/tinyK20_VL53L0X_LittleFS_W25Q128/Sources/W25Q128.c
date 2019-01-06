/*
 * W25Q128.c
 *
 *  Created on: 05.01.2019
 *      Author: Erich Styger
 */

#include "W25Q128.h"
#include "SM1.h"
#include "WSCS.h"
#include "UTIL1.h"
#include "CLS1.h"
#include "WAIT1.h"

#define W25_CMD_PAGE_PROGRAM  0x02
#define W25_CMD_DATA_READ     0x03

#define W25_CMD_READ_STATUS1  0x05

#define W25_CMD_WRITE_ENABLE  0x06

#define W25_CMD_GET_ID        0x9F
#define W25_ID0_WINBOND       0xEF

#define W25_CMD_GET_SERIAL    0x4B

#define W25_CMD_SECTOR_ERASE_4K 0x20
#define W25_CMD_BLOCK_ERASE_32K 0x52
#define W25_CMD_BLOCK_ERASE_64K 0xD8
#define W25_CMD_CHIP_ERASE      0xC7


/* W25Q128 chip select is LOW active */
#define W25_CS_ENABLE()   WSCS_ClrVal()
#define W25_CS_DISABLE()  WSCS_SetVal()

static uint8_t rxDummy; /* dummy byte if we do not need the result. Needed to read from SPI register. */
#define SPI_WRITE(write)            \
   { \
     while(SM1_SendChar(write)!=ERR_OK) {} \
     while(SM1_RecvChar(&rxDummy)!=ERR_OK) {} \
   }
#define SPI_WRITE_READ(write, readP) \
   { \
     while(SM1_SendChar(write)!=ERR_OK) {} \
     while(SM1_RecvChar(readP)!=ERR_OK) {} \
   }

uint8_t W25_ReadStatus1(uint8_t *status) {
  W25_CS_ENABLE();
  SPI_WRITE(W25_CMD_READ_STATUS1);
  SPI_WRITE_READ(0, status);
  W25_CS_DISABLE();
  return ERR_OK;
}

bool W25_isBusy(void) {
  uint8_t status;

  W25_ReadStatus1(&status);
  return (status&1);
}

void W25_WaitIfBusy(void) {
  while(W25_isBusy()) {
    WAIT1_Waitms(1);
  }
}

uint8_t W25_Read(uint32_t address, uint8_t *buf, size_t bufSize) {
  size_t i;

  W25_WaitIfBusy();

  W25_CS_ENABLE();
  SPI_WRITE(W25_CMD_DATA_READ);
  SPI_WRITE(address>>16);
  SPI_WRITE(address>>8);
  SPI_WRITE(address);
  for(i=0;i<bufSize;i++) {
    SPI_WRITE_READ(0, &buf[i]);
  }
  W25_CS_DISABLE();
  return ERR_OK;
}

uint8_t W25_EraseAll(void) {
  W25_WaitIfBusy();

  W25_CS_ENABLE();
  SPI_WRITE(W25_CMD_WRITE_ENABLE);
  W25_CS_DISABLE();
  WAIT1_Waitus(1);

  W25_CS_ENABLE();
  SPI_WRITE(W25_CMD_CHIP_ERASE);
  W25_CS_DISABLE();

  return ERR_OK;
}


uint8_t W25_EraseSector4K(uint32_t address) {
  W25_WaitIfBusy();

  W25_CS_ENABLE();
  SPI_WRITE(W25_CMD_WRITE_ENABLE);
  W25_CS_DISABLE();
  WAIT1_Waitus(1);

  W25_CS_ENABLE();
  SPI_WRITE(W25_CMD_SECTOR_ERASE_4K);
  SPI_WRITE(address>>16);
  SPI_WRITE(address>>8);
  SPI_WRITE(address);
  W25_CS_DISABLE();

  return ERR_OK;
}

uint8_t W25_EraseBlock32K(uint32_t address) {
  W25_WaitIfBusy();

  W25_CS_ENABLE();
  SPI_WRITE(W25_CMD_WRITE_ENABLE);
  W25_CS_DISABLE();
  WAIT1_Waitus(1);

  W25_CS_ENABLE();
  SPI_WRITE(W25_CMD_BLOCK_ERASE_32K);
  SPI_WRITE(address>>16);
  SPI_WRITE(address>>8);
  SPI_WRITE(address);
  W25_CS_DISABLE();

  return ERR_OK;
}

uint8_t W25_EraseBlock64K(uint32_t address) {
  W25_WaitIfBusy();

  W25_CS_ENABLE();
  SPI_WRITE(W25_CMD_WRITE_ENABLE);
  W25_CS_DISABLE();
  WAIT1_Waitus(1);

  W25_CS_ENABLE();
  SPI_WRITE(W25_CMD_BLOCK_ERASE_64K);
  SPI_WRITE(address>>16);
  SPI_WRITE(address>>8);
  SPI_WRITE(address);
  W25_CS_DISABLE();

  return ERR_OK;
}

/*!
 * Program a page with data
 * \param address, should be aligned on page (256 bytes) if programming 256 bytes
 * \param data pointer to data
 * \param dataSize size of data in bytes, max 256
 * \return error code, ERR_OK for no error
 */
uint8_t W25_ProgramPage(uint32_t address, uint8_t *data, size_t dataSize) {
  W25_WaitIfBusy();

  W25_CS_ENABLE();
  SPI_WRITE(W25_CMD_WRITE_ENABLE);
  W25_CS_DISABLE();
  WAIT1_Waitus(1);

  W25_CS_ENABLE();
  SPI_WRITE(W25_CMD_PAGE_PROGRAM);
  SPI_WRITE(address>>16);
  SPI_WRITE(address>>8);
  SPI_WRITE(address);
  while(dataSize>0) {
    SPI_WRITE(*data);
    dataSize--;
    data++;
  }
  W25_CS_DISABLE();

  return ERR_OK;
}


uint8_t W25_GetCapacity(const uint8_t *id, uint32_t *capacity) {
  uint32_t n = 0x100000; // unknown chips, default to 1 MByte

  if (id[2] >= 16 && id[2] <= 31) {
    n = 1ul << id[2];
  } else if (id[2] >= 32 && id[2] <= 37) {
    n = 1ul << (id[2] - 6);
  } else if ((id[0]==0 && id[1]==0 && id[2]==0) || (id[0]==255 && id[1]==255 && id[2]==255)) {
    *capacity = 0;
    return ERR_FAILED;
  }
  *capacity = n;
  return ERR_OK;
}

uint8_t W25_ReadSerialNumber(uint8_t *buf, size_t bufSize) {
  int i;

  if (bufSize<W25_SERIAL_BUF_SIZE) {
    return ERR_OVERFLOW; /* buffer not large enough */
  }

  W25_CS_ENABLE();
  SPI_WRITE(W25_CMD_GET_SERIAL);
  for(i=0;i<4;i++) {
    SPI_WRITE(0); /* 4 dummy bytes */
  }
  for(i=0; i<W25_SERIAL_BUF_SIZE; i++) {
    SPI_WRITE_READ(0, &buf[i]);
  }
  W25_CS_DISABLE();
  return ERR_OK;
}

uint8_t W25_ReadID(uint8_t *buf, size_t bufSize) {
  if (bufSize<W25_ID_BUF_SIZE) {
    return ERR_OVERFLOW; /* buffer not large enough */
  }

  W25_CS_ENABLE();
  SPI_WRITE(W25_CMD_GET_ID);
  /* W25Q128 should report EF 40 18 */
  SPI_WRITE_READ(0, &buf[0]);
  SPI_WRITE_READ(0, &buf[1]);
  SPI_WRITE_READ(0, &buf[2]);
  W25_CS_DISABLE();
  if (buf[0]==W25_ID0_WINBOND && buf[1]==0x40 && buf[2]==0x18) {
    return ERR_OK;
  }
  return ERR_FAILED; /* not expected part */
}

static uint8_t W25_PrintStatus(CLS1_ConstStdIOType *io) {
  uint8_t buf[60];
  uint8_t id[W25_ID_BUF_SIZE] = {0,0,0};
  uint8_t serial[W25_SERIAL_BUF_SIZE] = {0,0,0,0,0,0,0,0};
  uint8_t res, status;
  uint32_t capacity;
  int i;

  CLS1_SendStatusStr((const unsigned char*)"W25", (const unsigned char*)"\r\n", io->stdOut);

  res = W25_ReadID(id, sizeof(id)); /* check ID */
  if(res==ERR_OK) {
    buf[0] = '\0';
    UTIL1_strcatNum8Hex(buf, sizeof(buf), id[0]);
    UTIL1_chcat(buf, sizeof(buf), ' ');
    UTIL1_strcatNum8Hex(buf, sizeof(buf), id[1]);
    UTIL1_chcat(buf, sizeof(buf), ' ');
    UTIL1_strcatNum8Hex(buf, sizeof(buf), id[2]);
    if (id[0]==W25_ID0_WINBOND && id[1]==0x40 && id[2]==0x18) {
      UTIL1_strcat(buf, sizeof(buf), " (Winbond W25Q128)\r\n");
    } else {
      UTIL1_strcat(buf, sizeof(buf), " (UNKNOWN)\r\n");
    }
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr((const unsigned char*)"  ID", buf, io->stdOut);

  res = W25_GetCapacity(id, &capacity);
  if (res==ERR_OK) {
    buf[0] = '\0';
    UTIL1_strcatNum32u(buf, sizeof(buf), capacity);
    UTIL1_strcat(buf, sizeof(buf), " bytes\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr((const unsigned char*)"  Capacity", buf, io->stdOut);

  res = W25_ReadSerialNumber(serial, sizeof(serial)); /* check serial number */
  if(res==ERR_OK) {
    buf[0] = '\0';
    for(i=0; i<sizeof(serial); i++) {
      UTIL1_strcatNum8Hex(buf, sizeof(buf), serial[i]);
      UTIL1_chcat(buf, sizeof(buf), ' ');
    }
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr((const unsigned char*)"  Serial", buf, io->stdOut);

  res = W25_ReadStatus1(&status);
  if(res==ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), "0x");
    UTIL1_strcatNum8Hex(buf, sizeof(buf), status);
    UTIL1_strcat(buf, sizeof(buf), " SEC:"); UTIL1_strcat(buf, sizeof(buf), status&(1<<6)?"1": "0");
    UTIL1_strcat(buf, sizeof(buf), " TB:"); UTIL1_strcat(buf, sizeof(buf), status&(1<<5)?"1": "0");
    UTIL1_strcat(buf, sizeof(buf), " BP2:"); UTIL1_strcat(buf, sizeof(buf), status&(1<<4)?"1": "0");
    UTIL1_strcat(buf, sizeof(buf), " BP1:"); UTIL1_strcat(buf, sizeof(buf), status&(1<<3)?"1": "0");
    UTIL1_strcat(buf, sizeof(buf), " BP0:"); UTIL1_strcat(buf, sizeof(buf), status&(1<<2)?"1": "0");
    UTIL1_strcat(buf, sizeof(buf), " WEL:"); UTIL1_strcat(buf, sizeof(buf), status&(1<<1)?"1": "0");
    UTIL1_strcat(buf, sizeof(buf), " BUSY:"); UTIL1_strcat(buf, sizeof(buf), status&(1<<0)?"1": "0");
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr((const unsigned char*)"  Status", buf, io->stdOut);
  return ERR_OK;
}

uint8_t W25_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io) {
  const unsigned char *p;
  uint32_t val;
  uint32_t res;
  uint8_t data[32];
  int i;
  uint8_t buf[8];

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "W25 help")==0) {
    CLS1_SendHelpStr((unsigned char*)"W25", (const unsigned char*)"Group of W25 commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  read <addr>", (const unsigned char*)"Read 32 bytes from address\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  erase all", (const unsigned char*)"Erase all\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  erase 4k <addr>", (const unsigned char*)"Erase a 4K sector\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  erase 32k <addr>", (const unsigned char*)"Erase a 32K block\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  erase 64k <addr>", (const unsigned char*)"Erase a 64K block\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  write <addr> <data>", (const unsigned char*)"Write to page (max 32 bytes data, separated by spaces)\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, "W25 status")==0) {
    *handled = TRUE;
    return W25_PrintStatus(io);
  } else if (UTIL1_strncmp((char*)cmd, "W25 read ", sizeof("W25 read ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("W25 read ")-1;
    res = UTIL1_xatoi(&p, &val);
    if (res!=ERR_OK) {
      CLS1_SendStr("wrong address\r\n", io->stdErr);
      return ERR_FAILED;
    } else {
      res = W25_Read(val, &data[0], sizeof(data));
      if (res!=ERR_OK) {
        CLS1_SendStr("failed reading memory\r\n", io->stdErr);
        return ERR_FAILED;
      } else {
        for(i=0; i<sizeof(data); i++) {
          buf[0] = '\0';
          UTIL1_strcatNum8Hex(buf, sizeof(buf), data[i]);
          UTIL1_chcat(buf, sizeof(buf), ' ');
          CLS1_SendStr(buf, io->stdOut);
        }
        CLS1_SendStr("\r\n", io->stdOut);
      }
    }
    return ERR_OK;
  } else if (UTIL1_strncmp((char*)cmd, "W25 write ", sizeof("W25 write ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("W25 write ")-1;
    res = UTIL1_xatoi(&p, &val);
    if (res!=ERR_OK) {
      CLS1_SendStr("wrong address\r\n", io->stdErr);
      return ERR_FAILED;
    } else {
      for(i=0; i<sizeof(data); i++) {
        uint32_t v;
        res = UTIL1_xatoi(&p, &v);
        if (res!=ERR_OK) {
          break;
        }
        data[i] = v;
      }
      if (i>0) {
        res = W25_ProgramPage(val, data, i);
        if (res!=ERR_OK) {
          CLS1_SendStr("failed programming page\r\n", io->stdErr);
          return ERR_FAILED;
        }
      }
    }
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "W25 erase all")==0) {
    *handled = TRUE;
    res = W25_EraseAll();
    if (res!=ERR_OK) {
      CLS1_SendStr("failed erasing all memory\r\n", io->stdErr);
      return ERR_FAILED;
    }
    return ERR_OK;
  } else if (UTIL1_strncmp((char*)cmd, "W25 erase 4k ", sizeof("W25 erase 4k ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("W25 erase 4k ")-1;
    res = UTIL1_xatoi(&p, &val);
    if (res!=ERR_OK) {
      CLS1_SendStr("wrong address\r\n", io->stdErr);
      return ERR_FAILED;
    } else {
      res = W25_EraseSector4K(val);
      if (res!=ERR_OK) {
        CLS1_SendStr("failed erasing 4k sector\r\n", io->stdErr);
        return ERR_FAILED;
      }
    }
    return ERR_OK;
  } else if (UTIL1_strncmp((char*)cmd, "W25 erase 32k ", sizeof("W25 erase 32k ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("W25 erase 32k ")-1;
    res = UTIL1_xatoi(&p, &val);
    if (res!=ERR_OK) {
      CLS1_SendStr("wrong address\r\n", io->stdErr);
      return ERR_FAILED;
    } else {
      res = W25_EraseBlock32K(val);
      if (res!=ERR_OK) {
        CLS1_SendStr("failed erasing 32k block\r\n", io->stdErr);
        return ERR_FAILED;
      }
    }
    return ERR_OK;
  } else if (UTIL1_strncmp((char*)cmd, "W25 erase 64k ", sizeof("W25 erase 64k ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("W25 erase 64k ")-1;
    res = UTIL1_xatoi(&p, &val);
    if (res!=ERR_OK) {
      CLS1_SendStr("wrong address\r\n", io->stdErr);
      return ERR_FAILED;
    } else {
      res = W25_EraseBlock64K(val);
      if (res!=ERR_OK) {
        CLS1_SendStr("failed erasing 32k block\r\n", io->stdErr);
        return ERR_FAILED;
      }
    }
    return ERR_OK;
  }
  return ERR_OK;
}

uint8_t W25_Init(void) {
  uint8_t buf[W25_ID_BUF_SIZE];

  W25_CS_DISABLE();
  return W25_ReadID(buf, sizeof(buf)); /* check ID */
}

/* from https://github.com/PaulStoffregen/SerialFlash/blob/master/SerialFlashChip.cpp */
//                   size  sector          busy  pgm/erase chip
// Part              Mbyte kbyte ID bytes  cmd   suspend   erase
// ----               ----  ----- --------  --- -------   -----
// Winbond W25Q64CV 8 64  EF     40 17
// Winbond W25Q128FV  16  64     EF 40 18  05  single    60 & C7
// Winbond W25Q256FV  32  64     EF 40 19
// Spansion S25FL064A 8 ? 01     02 16
// Spansion S25FL127S 16  64     01 20 18  05
// Spansion S25FL128P 16  64     01 20 18
// Spansion S25FL256S 32  64     01 02 19  05      60 & C7
// Spansion S25FL512S 64  256    01 02 20
// Macronix MX25L12805D 16  ? C2 20 18
// Macronix MX66L51235F 64    C2 20 1A
// Numonyx M25P128  16  ? 20 20 18
// Micron M25P80  1 ? 20 20 14
// Micron N25Q128A  16  64  20 BA 18
// Micron N25Q512A  64  ? 20 BA 20  70  single    C4 x2
// Micron N25Q00AA  128 64  20 BA 21    single    C4 x4
// Micron MT25QL02GC  256 64  20 BA 22  70      C4 x2
// SST SST25WF010 1/8 ? BF 25 02
// SST SST25WF020 1/4 ? BF 25 03
// SST SST25WF040 1/2 ? BF 25 04
// SST SST25VF016B  1 ? BF 25 41
// SST26VF016     ? BF 26 01
// SST26VF032     ? BF 26 02
// SST25VF032   4 64  BF 25 4A
// SST26VF064   8 ? BF 26 43
// LE25U40CMC   1/2 64  62 06 13

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

#define W25_GET_ID       0x9F
#define W25_GET_SERIAL   0x4B


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
  SPI_WRITE(W25_GET_SERIAL);
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
  SPI_WRITE(W25_GET_ID);
  /* W25Q128 should report EF 40 18 */
  SPI_WRITE_READ(0, &buf[0]);
  SPI_WRITE_READ(0, &buf[1]);
  SPI_WRITE_READ(0, &buf[2]);
  W25_CS_DISABLE();
  if (buf[0]==0xEF && buf[1]==0x40 && buf[2]==0x18) {
    return ERR_OK;
  }
  return ERR_FAILED; /* not expected part */
}

static uint8_t W25_PrintStatus(CLS1_ConstStdIOType *io) {
  uint8_t buf[48];
  uint8_t id[W25_ID_BUF_SIZE] = {0,0,0};
  uint8_t serial[W25_SERIAL_BUF_SIZE] = {0,0,0,0,0,0,0,0};
  uint8_t res;
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
    if (id[0]==0xEF && id[1]==0x40 && id[2]==0x18) {
      UTIL1_strcat(buf, sizeof(buf), " (W25Q128)\r\n");
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

  return ERR_OK;
}

uint8_t W25_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "W25 help")==0) {
    CLS1_SendHelpStr((unsigned char*)"W25", (const unsigned char*)"Group of W25 commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, "W25 status")==0) {
    *handled = TRUE;
    return W25_PrintStatus(io);
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

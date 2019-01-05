/*
 * W25Q128.c
 *
 *  Created on: 05.01.2019
 *      Author: Erich Styger
 */


#include "W25Q128.h"
#include "SM1.h"
#include "WSCS.h"

#define W25_GET_ID       0x9F

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

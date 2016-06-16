/*
 * Buffer.c
 *
 *  Created on: 16.06.2016
 *      Author: Erich Styger
 */

#include "Buffer.h"
#include "IFsh1.h"
#include "CLS1.h"
#include "UTIL1.h"

#define BUF_BUFFER_SIZE  IntFlashLdd1_BLOCK1_ERASABLE_UNIT_SIZE

typedef enum {
  BUF_STATE_NONE,
  BUF_STATE_INIT, /* no data in buffer */
  BUF_STATE_DATA  /* data in buffer */
} BUF_State;

static struct {
  BUF_State state;
  uint32_t flashPage; /* page, based on IntFlashLdd1_BLOCK1_ERASABLE_UNIT_SIZE */
  uint8_t buffer[BUF_BUFFER_SIZE];
} BUF_Buffer;

uint8_t BUF_Flush(void) {
  uint8_t res = ERR_OK;
  uint8_t buf[32];

  if (BUF_Buffer.state==BUF_STATE_DATA) {
    /* erase sector first */
    UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"\r\nErase Sector at 0x");
    UTIL1_strcatNum32Hex(buf, sizeof(buf), BUF_Buffer.flashPage*BUF_BUFFER_SIZE);
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
    CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
    res = IFsh1_EraseSector(BUF_Buffer.flashPage*BUF_BUFFER_SIZE);
    if (res != ERR_OK) {
      return res;
    }
    BUF_Buffer.state=BUF_STATE_INIT;
    /* flash current data */
    UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"Program Sector at 0x");
    UTIL1_strcatNum32Hex(buf, sizeof(buf), BUF_Buffer.flashPage*BUF_BUFFER_SIZE);
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
    CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
    res = IFsh1_SetBlockFlash((IFsh1_TDataAddress)&BUF_Buffer.buffer[0], BUF_Buffer.flashPage*BUF_BUFFER_SIZE, BUF_BUFFER_SIZE);
    if (res!= ERR_OK) {
      return res; /* flash programming failed */
    }
  }
  return res;
}

uint8_t BUF_Write(uint32_t address, uint8_t *data, uint32_t dataSize) {
  uint32_t page, offset;
  uint8_t res;
  uint32_t i;

  page = address/BUF_BUFFER_SIZE;
  offset = address%BUF_BUFFER_SIZE;
  if (BUF_Buffer.state==BUF_STATE_INIT) {/* new page */
    uint8_t *data;

    BUF_Buffer.flashPage = page;
    /* copy existing data into buffer */
    data = (uint8_t*)(page*BUF_BUFFER_SIZE);
    for(i=0; i<BUF_BUFFER_SIZE; i++) {
      BUF_Buffer.buffer[i] = data[i];
    }
    BUF_Buffer.state=BUF_STATE_DATA;
  }
  if (page==BUF_Buffer.flashPage && BUF_Buffer.state==BUF_STATE_DATA) { /* still on the same page */
    /* \todo handle buffer boundaries */
    /* copy data */
    for(i=0;i<dataSize;i++) {
      BUF_Buffer.buffer[offset+i] = data[i];
    }
  } else { /* new page */
    res = BUF_Flush(); /* flush current page */
    if (res!=ERR_OK) {
      return res;
    }
    return BUF_Write(address, data, dataSize);
  }
  return ERR_OK;
}


void BUF_Init(void) {
  BUF_Buffer.state = BUF_STATE_INIT;
}

/*
 * w5100.c
 *
 *  Created on: Jan 3, 2014
 *      Author: tastyger
 */

/* https://github.com/braiden/embedded-ac-controller/blob/master/w5100.c */
#include "w5100.h"
#include "ETH_CS.h"
//#include "ETH_INT.h"
#include "WAIT1.h"
#include "SM1.h"

#define W5100_CS_ENABLE()   ETH_CS_ClrVal() /* chip select is low active */
#define W5100_CS_DISABLE()  ETH_CS_SetVal() /* chip select is low active */

static volatile bool W5100_DataReceivedFlag = FALSE;

void W5100_OnBlockReceived(LDD_TUserData *UserDataPtr) {
  (void)UserDataPtr;
  W5100_DataReceivedFlag = TRUE;
}

static void SPIWriteByte(unsigned char write) {
  unsigned char dummy;

  W5100_DataReceivedFlag = FALSE;
  (void)SM1_ReceiveBlock(SM1_DeviceData, &dummy, sizeof(dummy));
  (void)SM1_SendBlock(SM1_DeviceData, &write, sizeof(write));
  while(!W5100_DataReceivedFlag){}
}

static uint8_t SPIReadByte(void) {
  uint8_t val, write = 0xff; /* dummy */
  
  W5100_DataReceivedFlag = FALSE;
  (void)SM1_ReceiveBlock(SM1_DeviceData, &val, 1);
  (void)SM1_SendBlock(SM1_DeviceData, &write, 1);
  while(!W5100_DataReceivedFlag){}
  return val;
}


void W5100_MemWrite(uint16_t addr, uint8_t val) {
  W5100_CS_ENABLE();
  SPIWriteByte(W5100_CMD_WRITE);
  SPIWriteByte(addr>>8); /* high address */
  SPIWriteByte(addr&0xff); /* low address */
  SPIWriteByte(val); /* data */
  W5100_CS_DISABLE();
}

uint8_t W5100_MemRead(uint16_t addr) {
  uint8_t val;
  
  W5100_CS_ENABLE();
  SPIWriteByte(W5100_CMD_READ);
  SPIWriteByte(addr>>8); /* high address */
  SPIWriteByte(addr&0xff); /* low address */
  val = SPIReadByte(); /* data */
  W5100_CS_DISABLE();
  return val;
}

static uint8_t tmp;

void W5100_Init(void) {
  /* bring reset pin low */
 // ETH_RESET_ClrVal();
 // WAIT1_Waitms(10);
 // ETH_RESET_SetVal();
  /* gateway IP register */
  W5100_MemWrite(W5100_GAR0, 0xc0); /* 192 */
  tmp = W5100_MemRead(W5100_GAR0);
}

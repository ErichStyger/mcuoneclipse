/*
 * nRF24L01.c
 *
 *  Created on: Jul 13, 2013
 *      Author: tastyger
 */

#include "nRF24L01.h"
#include "SM1.h"
#include "CE.h"
#include "CSN.h"
#include "WAIT1.h"



/* ------------------------------ */
// WL-Module settings
#define wl_module_CH      2
#define wl_module_PAYLOAD   16
#define wl_module_RF_DR_HIGH  0   //0 = 1Mbps, 1 = 2Mpbs
#define wl_module_TX_NR_0   0
#define wl_module_TX_NR_1   1
#define wl_module_TX_NR_2   2
#define wl_module_TX_NR_3   3
#define wl_module_TX_NR_4   4
#define wl_module_TX_NR_5   5

#define RF_WAIT_US(x)  WAIT1_Waitus(x)
#define RF_WAIT_MS(x)  WAIT1_Waitms(x)
#define RF_CE_LOW()    CE_ClrVal()
#define RF_CE_HIGH()   CE_SetVal()
#define RF_CSN_LOW()   CSN_ClrVal()
#define RF_CSN_HIGH()  CSN_SetVal()

static volatile bool PTX; /* flag to denote transmitting mode */

static byte SPI_Write_Read(uint8_t val) {
  uint8_t ch;

  while (SM1_GetCharsInTxBuf()!=0) {} /* wait until tx is empty */
  while (SM1_SendChar(val)!=ERR_OK) {} /* send character */
  while (SM1_GetCharsInTxBuf()!=0) {} /* wait until data has been sent */
  while (SM1_GetCharsInRxBuf()==0) {} /* wait until we receive data */
  while (SM1_RecvChar(&ch)!=ERR_OK) {} /* get data */
  return ch;
}

static byte SPI_WriteDummy_Read(void) {
  uint8_t ch;

  while (SM1_GetCharsInTxBuf()!=0) {} /* wait until tx is empty */
  while (SM1_SendChar(0)!=ERR_OK) {} /* send character */
  while (SM1_GetCharsInTxBuf()!=0) {} /* wait until data has been sent */
  while (SM1_GetCharsInRxBuf()==0) {} /* wait until we receive data */
  while (SM1_RecvChar(&ch)!=ERR_OK) {} /* get data */
  return ch;
}

static void SPI_Write_ReadDummy(uint8_t val) {
  while (SM1_GetCharsInTxBuf()!=0) {} /* wait until tx is empty */
  while (SM1_SendChar(val)!=ERR_OK) {} /* send the value to the bus */
  while (SM1_GetCharsInTxBuf()!=0) {} /* wait until data has been sent */
  while (SM1_GetCharsInRxBuf()==0) {} /* wait until we receive data */
  while (SM1_RecvChar(&val)!=ERR_OK) {} /* get data, but throw it away */
}

static void SPI_Write_Read_Data(uint8_t *bufOut, uint8_t *bufIn, uint8_t bufSize) {
  uint8_t i;
  
  for(i=0;i<bufSize;i++) {
    bufIn[i] = SPI_Write_Read(bufOut[i]);
  }
}

static void SPI_Write_Data(uint8_t *bufOut, uint8_t bufSize) {
  uint8_t i;
  
  for(i=0;i<bufSize;i++) {
    SPI_Write_ReadDummy(bufOut[i]);
  }
}

void RF_WriteRegister(uint8_t reg, uint8_t val) {
  RF_CSN_LOW();
  SPI_Write_ReadDummy(RF24_W_REGISTER|reg); /* not masking as would conflict with FLUSH_TX and FLUSH_RX write operation */
  SPI_Write_ReadDummy(val);
  RF_CSN_HIGH();
  RF_WAIT_US(10);
}

uint8_t RF_ReadRegister(uint8_t reg) {
  uint8_t val;
  
  RF_CSN_LOW();
  SPI_Write_ReadDummy(reg);
  val = SPI_WriteDummy_Read();
  RF_CSN_HIGH();
  RF_WAIT_US(10);
  return val;
}

void RF_ReadRegisterData(uint8_t reg, uint8_t *buf, uint8_t bufSize) {
  RF_CSN_LOW();
  SPI_Write_ReadDummy(RF24_R_REGISTER|(RF24_REGISTER_MASK&reg));
  SPI_Write_Read_Data(buf, buf, bufSize);
  RF_CSN_HIGH();
  RF_WAIT_US(10);
}

void RF_WriteRegisterData(uint8_t reg, uint8_t *buf, uint8_t bufSize) {
  RF_CSN_LOW();
  SPI_Write_ReadDummy(RF24_W_REGISTER|reg); /* not masking registers as it would conflict with RF24_W_TX_PAYLOAD */
  SPI_Write_Data(buf, bufSize);
  RF_CSN_HIGH();
  RF_WAIT_US(10);
}

uint8_t RF_WriteRead(uint8_t val) {
  RF_CSN_LOW();
  val = SPI_Write_Read(val);
  RF_CSN_HIGH();
  RF_WAIT_US(10);
  return val;
}

void RF_Write(uint8_t val) {
  RF_CSN_LOW();
  SPI_Write_ReadDummy(val);
  RF_CSN_HIGH();
  RF_WAIT_US(10);
}

uint8_t RF_GetChannel(void) {
  return RF_ReadRegister(RF24_RF_CH);
}

void RF_SetChannel(uint8_t channel) {
  RF_WriteRegister(RF24_RF_CH, channel);
}

void RF_SetPayloadSize(uint8_t payloadSize) {
  RF_WriteRegister(RF24_RX_PW_P0, payloadSize);
}

uint8_t RF_GetStatus(void) {
  return RF_WriteRead(RF24_NOP);
}

/* reset status after every payload rx/tx */
void RF_ResetStatusIRQ(void) {
  RF_WAIT_US(10);
  RF_CSN_LOW();
  RF_WAIT_US(10);
  RF_WriteRegister(RF24_STATUS, 0x70); /* reset all IRQ in status register */
  RF_WAIT_US(10);
  RF_CSN_HIGH();
  RF_WAIT_US(10);
}

uint8_t RF_TxPayload(uint8_t *payload, uint8_t payloadSize) {
  RF_CE_LOW();
  TX_POWERUP();
  
  RF_Write(RF24_FLUSH_TX); /* flush old data */
  
  RF_WAIT_US(10);
  
  RF_WriteRegisterData(RF24_W_TX_PAYLOAD, payload, payloadSize);
  //RF_WAIT_MS(10); /* need 10 ms to wait here? */
  
  RF_CE_HIGH();
  RF_WAIT_US(10);
  RF_CE_LOW();
  
  //RF_WAIT_MS(10); /* need 10 ms to wait here? */
  return ERR_OK;
}

void RF_RxPayload(uint16_t listenMs) {
  RF_CE_HIGH(); /* high to 'listen for data' */
  RF_WAIT_MS(listenMs); /* listen for data for one second */
  RF_CE_LOW(); /* stop listening */
}

void RF_Init(void) {
  RF_CE_LOW();
  RF_CSN_HIGH();
}

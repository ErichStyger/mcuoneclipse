/*
 * nRF24L01.c
 *
 *      Author: Erich Styger
 */

#include "nRF24L01.h"
#include "SM1.h"
#include "CE.h"
#include "CSN.h"
#include "WAIT1.h"

/* Macros to hide low level functionality */
#define RF_WAIT_US(x)  WAIT1_Waitus(x)  /* wait for the given number of micro-seconds */
#define RF_WAIT_MS(x)  WAIT1_Waitms(x)  /* wait for the given number of milli-seconds */
#define RF_CE_LOW()    CE_ClrVal()      /* put CE LOW */
#define RF_CE_HIGH()   CE_SetVal()      /* put CE HIGH */
#define RF_CSN_LOW()   CSN_ClrVal()     /* put CSN LOW */
#define RF_CSN_HIGH()  CSN_SetVal()     /* put CSN HIGH */

/*!
 * \brief Writes a byte and reads the value
 * @param val Value to write
 * @return The value shifted in
 */
static uint8_t SPI_WriteRead(uint8_t val) {
  uint8_t ch;

  while (SM1_GetCharsInTxBuf()!=0) {} /* wait until tx is empty */
  while (SM1_SendChar(val)!=ERR_OK) {} /* send character */
  while (SM1_GetCharsInTxBuf()!=0) {} /* wait until data has been sent */
  while (SM1_GetCharsInRxBuf()==0) {} /* wait until we receive data */
  while (SM1_RecvChar(&ch)!=ERR_OK) {} /* get data */
  return ch;
}

/*!
 * \brief Read a value from SPI bus
 * \return Value read
 */
static uint8_t SPI_Read(void) {
  return SPI_WriteRead(0); /* zero is dummy value */
}

/*!
 * \brief Writes a value to the SPI bus
 * \param val Value to write
 */
static void SPI_Write(uint8_t val) {
  (void)SPI_WriteRead(val);
}

/*!
 * \brief Writes a buffer to the SPI bus and the same time reads in the data
 * \param bufOut Output buffer
 * \param bufIn Input buffer
 * \param bufSize Size of input and output buffer
 */
static void SPI_WriteReadBuffer(uint8_t *bufOut, uint8_t *bufIn, uint8_t bufSize) {
  uint8_t i;
  
  for(i=0;i<bufSize;i++) {
    bufIn[i] = SPI_WriteRead(bufOut[i]);
  }
}

static void SPI_WriteBuffer(uint8_t *bufOut, uint8_t bufSize) {
  uint8_t i;
  
  for(i=0;i<bufSize;i++) {
    SPI_Write(bufOut[i]);
  }
}

/*!
 * \brief Write a register value to the transceiver
 * \param reg Register to write
 * \param val Value of the register to write
 */
void RF_WriteRegister(uint8_t reg, uint8_t val) {
  RF_CSN_LOW(); /* initiate command sequence */
  SPI_Write(RF24_W_REGISTER|reg); /* write register command */
  SPI_Write(val); /* write value */
  RF_CSN_HIGH(); /* end command sequence */
  RF_WAIT_US(10); /* insert a delay until next command */
}

uint8_t RF_ReadRegister(uint8_t reg) {
  uint8_t val;
  
  RF_CSN_LOW();
  SPI_Write(reg);
  val = SPI_Read();
  RF_CSN_HIGH();
  RF_WAIT_US(10);
  return val;
}

void RF_ReadRegisterData(uint8_t reg, uint8_t *buf, uint8_t bufSize) {
  RF_CSN_LOW();
  SPI_Write(RF24_R_REGISTER|reg);
  SPI_WriteReadBuffer(buf, buf, bufSize);
  RF_CSN_HIGH();
  RF_WAIT_US(10);
}

void RF_WriteRegisterData(uint8_t reg, uint8_t *buf, uint8_t bufSize) {
  RF_CSN_LOW();
  SPI_Write(RF24_W_REGISTER|reg); /* not masking registers as it would conflict with RF24_W_TX_PAYLOAD */
  SPI_WriteBuffer(buf, bufSize);
  RF_CSN_HIGH();
  RF_WAIT_US(10);
}

uint8_t RF_WriteRead(uint8_t val) {
  RF_CSN_LOW();
  val = SPI_WriteRead(val);
  RF_CSN_HIGH();
  RF_WAIT_US(10);
  return val;
}

void RF_Write(uint8_t val) {
  RF_CSN_LOW();
  SPI_Write(val);
  RF_CSN_HIGH();
  RF_WAIT_US(10);
}

/*!
 * \brief Read and return the STATUS
 * \return Status
 */
uint8_t RF_GetStatus(void) {
  return RF_WriteRead(RF24_NOP);
}

/*!
 * \brief Reset the given mask of status bits
 * \param flags Flags, one or more of of RF24_STATUS_RX_DR, RF24_STATUS_TX_DS, RF24_STATUS_MAX_RT
 */
void RF_ResetStatusIRQ(uint8_t flags) {
  RF_WAIT_US(10);
  RF_CSN_LOW();
  RF_WAIT_US(10);
  RF_WriteRegister(RF24_STATUS, flags); /* reset all IRQ in status register */
  RF_WAIT_US(10);
  RF_CSN_HIGH();
  RF_WAIT_US(10);
}

/*!
 * \brief Send the payload to the Tx FIFO and send it
 * \param payload Buffer with payload to send
 * \param payloadSize Size of payload buffer
 */
void RF_TxPayload(uint8_t *payload, uint8_t payloadSize) {
  RF_Write(RF24_FLUSH_TX); /* flush old data */
  RF_WriteRegisterData(RF24_W_TX_PAYLOAD, payload, payloadSize); /* write payload */
  RF_CE_HIGH(); /* start transmission */
  RF_WAIT_US(15); /* keep signal high for 15 micro-seconds */
  RF_CE_LOW();  /* back to normal */
}

/*!
 * \brief Receive the Rx payload from the FIFO and stores it in a buffer.
 * \param payload Pointer to the payload buffer
 * \param payloadSize Size of the payload buffer
 */
void RF_RxPayload(uint8_t *payload, uint8_t payloadSize) {
  RF_CE_LOW(); /* need to disable rx mode during reading RX data */
  RF_ReadRegisterData(RF24_R_RX_PAYLOAD, payload, payloadSize); /* rx payload */
  RF_CE_HIGH(); /* re-enable rx mode */
}

/*!
 * \brief Initializes the transceiver.
 */
void RF_Init(void) {
  RF_CE_LOW();   /* CE high: do not send or receive data */
  RF_CSN_HIGH(); /* CSN low: not sending commands to the device */
}

#if 0 /* not used yet */
uint8_t RF_GetChannel(void) {
  return RF_ReadRegister(RF24_RF_CH);
}

void RF_SetChannel(uint8_t channel) {
  RF_WriteRegister(RF24_RF_CH, channel);
}

void RF_SetPayloadSize(uint8_t payloadSize) {
  RF_WriteRegister(RF24_RX_PW_P0, payloadSize);
}

bool RF_DataIsReady(void) {
  return (RF_GetStatus()&RF24_STATUS_RX_DR);
}

bool RF_MaxRetryReached(void) {
  return (RF_GetStatus()&RF24_STATUS_MAX_RT);
}

#endif

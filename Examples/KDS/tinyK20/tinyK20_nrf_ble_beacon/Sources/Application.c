/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Platform.h"
#include "Application.h"
#include "LED1.h"
#include "RF1.h"

/* credits to http://dmitry.gr/index.php?r=05.Projects&proj=15&proj=11.%20Bluetooth%20LE%20fakery */
void btLeCrc(const uint8_t* data, uint8_t len, uint8_t* dst) {
  uint8_t v, t, d;

  while(len--){
    d = *data++;
    for(v = 0; v < 8; v++, d >>= 1){
      t = dst[0] >> 7;
      dst[0] <<= 1;
      if(dst[1] & 0x80) dst[0] |= 1;
      dst[1] <<= 1;
      if(dst[2] & 0x80) dst[1] |= 1;
      dst[2] <<= 1;
      if(t != (d & 1)){
        dst[2] ^= 0x5B;
        dst[1] ^= 0x06;
      }
    }
  }
}

/* credits to http://dmitry.gr/index.php?r=05.Projects&proj=15&proj=11.%20Bluetooth%20LE%20fakery */
void btLeWhiten(uint8_t* data, uint8_t len, uint8_t whitenCoeff){
  uint8_t  m;

  while(len--){
    for(m = 1; m; m <<= 1) {
      if(whitenCoeff & 0x80) {
        whitenCoeff ^= 0x11;
        (*data) ^= m;
      }
      whitenCoeff <<= 1;
    }
    data++;
  }
}

uint8_t swapbits(uint8_t a) {
  uint8 v = 0;

  if(a & 0x80) v |= 0x01;
  if(a & 0x40) v |= 0x02;
  if(a & 0x20) v |= 0x04;
  if(a & 0x10) v |= 0x08;
  if(a & 0x08) v |= 0x10;
  if(a & 0x04) v |= 0x20;
  if(a & 0x02) v |= 0x40;
  if(a & 0x01) v |= 0x80;
  return v;
}

#define MY_MAC_0  0xEF
#define MY_MAC_1  0xFF
#define MY_MAC_2  0xC0
#define MY_MAC_3  0xAA
#define MY_MAC_4  0x18
#define MY_MAC_5  0x00

struct adv_hdr {
  uint8_t header; //we use 0x40 to say it is a non-connectable undirected
      //advertisement and address we're sending is random (not assigned)
  uint8_t dataLen; //length of following data (including MAC addr)
  uint8_t MAC[6]; //the mac address
};

static inline uint8_t btLeWhitenStart(uint8_t chan){
  //the value we actually use is what BT'd use left shifted one...makes our life easier
  return swapbits(chan) | 2;
}

void btLePacketEncode(uint8_t* packet, uint8_t len, uint8_t chan){
  //length is of packet, including crc. pre-populate crc in packet with initial crc value!
  uint8_t i, dataLen = len - 3;

  btLeCrc(packet, dataLen, packet + dataLen);
  for(i = 0; i < 3; i++, dataLen++) packet[dataLen] = swapbits(packet[dataLen]);
  btLeWhiten(packet, len, btLeWhitenStart(chan));
  for(i = 0; i < len; i++) packet[i] = swapbits(packet[i]);
}

uint8_t spi_byte(uint8_t byte) {
}

void nrf_cmd(uint8_t cmd, uint8_t data) {
  RF1_WriteRegister(cmd, data);
#if 0
  cbi(PORTB, PIN_nCS);
  spi_byte(cmd);
  spi_byte(data);
  sbi(PORTB, PIN_nCS); //Deselect chip
#endif
}

void nrf_simplebyte(uint8_t cmd) {
  RF1_Write(cmd);
#if 0
  cbi(PORTB, PIN_nCS);
  spi_byte(cmd);
  sbi(PORTB, PIN_nCS);
#endif
}

void nrf_manybytes(uint8_t* data, uint8_t len){
#if 0
  cbi(PORTB, PIN_nCS);
  do {
    spi_byte(*data++);
  } while(--len);
  sbi(PORTB, PIN_nCS);
#endif
}

void APP_Run(void) {
  static const uint8_t chRf[] = {2, 26,80};
  static const uint8_t chLe[] = {37,38,39};
  uint8_t i, L, ch = 0;
  uint8_t buf[32];

  nrf_cmd(0x20, 0x12);  //on, no crc, int on RX/TX done
  nrf_cmd(0x21, 0x00);  //no auto-acknowledge
  nrf_cmd(0x22, 0x00);  //no RX
  nrf_cmd(0x23, 0x02);  //5-byte address
  nrf_cmd(0x24, 0x00);  //no auto-retransmit
  nrf_cmd(0x26, 0x06);  //1MBps at 0dBm
  nrf_cmd(0x27, 0x3E);  //clear various flags
  nrf_cmd(0x3C, 0x00);  //no dynamic payloads
  nrf_cmd(0x3D, 0x00);  //no features
  nrf_cmd(0x31, 32);  //always RX 32 bytes
  nrf_cmd(0x22, 0x01);  //RX on pipe 0

  buf[0] = 0x30;      //set addresses
  buf[1] = swapbits(0x8E);
  buf[2] = swapbits(0x89);
  buf[3] = swapbits(0xBE);
  buf[4] = swapbits(0xD6);
#if 0
  nrf_manybytes(buf, 5);
#else
  RF1_WriteRegisterData(RF1_TX_ADDR, &buf[1], 4);
#endif
  buf[0] = 0x2A;
#if 0
  nrf_manybytes(buf, 5);
#else
  RF1_WriteRegisterData(RF1_RX_ADDR_P0, &buf[1], 4);
#endif

  while(1) {
      L = 0;
      buf[L++] = 0x40;  //PDU type, given address is random
      buf[L++] = 11;  //17 bytes of payload

      buf[L++] = MY_MAC_0;
      buf[L++] = MY_MAC_1;
      buf[L++] = MY_MAC_2;
      buf[L++] = MY_MAC_3;
      buf[L++] = MY_MAC_4;
      buf[L++] = MY_MAC_5;

      buf[L++] = 2;   //flags (LE-only, limited discovery mode)
      buf[L++] = 0x01;
      buf[L++] = 0x05;

      buf[L++] = 7;
      buf[L++] = 0x08;
      buf[L++] = 'n';
      buf[L++] = 'R';
      buf[L++] = 'F';
      buf[L++] = ' ';
      buf[L++] = 'L';
      buf[L++] = 'E';

      buf[L++] = 0x55;  //CRC start value: 0x555555
      buf[L++] = 0x55;
      buf[L++] = 0x55;

      if(++ch == sizeof(chRf)) { /* channel hopping */
        ch = 0;
      }

      //nrf_cmd(0x25, chRf[ch]);
      (void)RF1_SetChannel(chRf[ch]);

      //nrf_cmd(0x27, 0x6E);  //clear flags
      RF1_WriteRegister(RF1_STATUS, RF1_STATUS_RX_DR|RF1_STATUS_TX_DS|RF1_STATUS_RX_P_NO_RX_FIFO_EMPTY); /* clear flags */

      btLePacketEncode(buf, L, chLe[ch]);

      //nrf_simplebyte(0xE2); //Clear RX Fifo
      RF1_Write(RF1_FLUSH_RX); /* flush old data */

      //nrf_simplebyte(0xE1); //Clear TX Fifo
      //RF1_Write(RF1_FLUSH_TX); /* flush old data */ /* done in RF1_TxPayload() */


      RF1_TxPayload(buf, L);
#if 0
      cbi(PORTB, PIN_nCS);
      spi_byte(0xA0);
      for(i = 0 ; i < L ; i++) {
        spi_byte(buf[i]);
      }
      sbi(PORTB, PIN_nCS);
      nrf_cmd(0x20, 0x12);  //tx on
      sbi(PORTB, PIN_CE);  //do tx
      delay_ms(10);
      cbi(PORTB, PIN_CE); (in preparation of switching to RX quickly);
#endif
      LED1_Neg();
      WAIT1_Waitms(10);
  } /* for */
}


/*
 * DHT11.c
 *
 *  Created on: 26.03.2015
 *      Author: tastyger
 */

#include "DHT11.h"
#include "WAIT1.h"
#include "LEDR.h"
#include "LEDG.h"
#include "Data.h"
#include "CLS1.h"
#include "UTIL1.h"

typedef enum {
  DHT11_OK, /* OK */
  DHT11_NO_PULLUP, /* no pullup present */
  DHT11_NO_ACK_0, /* no 0 acknowledge detected */
  DHT11_NO_ACK_1, /* no 1 acknowledge detected */
  DHT11_NO_DATA_0, /* low level expected during data transmission */
  DHT11_NO_DATA_1, /* high level expected during data transmission */
  DHT11_BAD_CRC,   /* bad CRC */
} DHT11_ReturnCode;

const unsigned char* DHT1_GetReturnCodeString(DHT11_ReturnCode code) {
  switch(code) {
    case DHT11_OK:        return "OK";
    case DHT11_NO_PULLUP: return "NO_PULLUP";
    case DHT11_NO_ACK_0:  return "NO_ACK_0";
    case DHT11_NO_ACK_1:  return "NO_ACK_1";
    case DHT11_NO_DATA_0: return "NO_DATA_0";
    case DHT11_NO_DATA_1: return "NO_DATA_1";
    case DHT11_BAD_CRC:   return "BAD_CRC";
    default:              return "UNKNOWN?";
  }
}

DHT11_ReturnCode DHT11_Read(uint16_t *temperatureCentigrade, uint16_t *humidityCentipercent) {
  int cntr;
  int loopBits;
  uint8_t buffer[5];
  int i;
  int data;

  /* init buffer */
  for(i=0;i<sizeof(buffer); i++) {
    buffer[i] = 0;
  }
  /* set to input and check if the signal gets pulled up */
  Data_SetInput();
  WAIT1_Waitus(50);
  if(Data_GetVal()==0) {
    return DHT11_NO_PULLUP;
  }
  /* send start signal */
  Data_SetOutput();
  Data_ClrVal();
  WAIT1_Waitms(18); /* keep signal low for at least 18 ms */
  Data_SetInput();
  WAIT1_Waitus(50);
  /* check for acknowledge signal */
  if (Data_GetVal()!=0) { /* signal must be pulled low by the sensor */
    return DHT11_NO_ACK_0;
  }
  /* wait max 100 us for the ack signal from the sensor */
  cntr = 18;
  while(Data_GetVal()==0) { /* wait until signal goes up */
    WAIT1_Waitus(5);
    if (--cntr==0) {
      return DHT11_NO_ACK_1; /* signal should be up for the ACK here */
    }
  }
  /* wait until it goes down again, end of ack sequence */
  cntr = 18;
  while(Data_GetVal()!=0) { /* wait until signal goes down */
    WAIT1_Waitus(5);
    if (--cntr==0) {
      return DHT11_NO_ACK_0; /* signal should be down to zero again here */
    }
  }
  /* now read the 40 bit data */
  i = 0;
  data = 0;
  loopBits = 40;
  do {
    cntr = 11; /* wait max 55 us */
    while(Data_GetVal()==0) {
      WAIT1_Waitus(5);
      if (--cntr==0) {
        return DHT11_NO_DATA_0;
      }
    }
    cntr = 15; /* wait max 75 us */
    while(Data_GetVal()!=0) {
      WAIT1_Waitus(5);
      if (--cntr==0) {
        return DHT11_NO_DATA_1;
      }
    }
    data <<= 1; /* next data bit */
    if (cntr<10) { /* data signal high > 30 us ==> data bit 1 */
      data |= 1;
    }
    if ((loopBits&0x7)==1) { /* next byte */
      buffer[i] = data;
      i++;
      data = 0;
    }
  } while(--loopBits!=0);
  /* now we have the 40 bit (5 bytes) data:
   * byte 1: humidity integer data
   * byte 2: humidity decimal data (not used for DTH11, always zero)
   * byte 3: temperature integer data
   * byte 4: temperature fractional data (not used for DTH11, always zero)
   * byte 5: checksum, the sum of byte 1 + 2 + 3 + 4
   */
  /* test CRC */
  if (buffer[0]+buffer[1]+buffer[2]+buffer[3]!=buffer[4]) {
    return DHT11_BAD_CRC;
  }
  *humidityCentipercent = buffer[0]*100+buffer[1];
  *temperatureCentigrade = buffer[2]*100+buffer[3];
  return DHT11_OK;
}

void DHT11_Run(void) {
  DHT11_ReturnCode res;
  uint16_t temperature, humidity;
  CLS1_ConstStdIOType *io = CLS1_GetStdio();
  uint8_t buf[48];

  CLS1_SendStr("DHT11 Sensor:\r\n", io->stdErr);
  WAIT1_Waitms(1000); /* wait one second after power-up to get the sensor stable */
  for(;;) {
    res = DHT11_Read(&temperature, &humidity);
    if (res!=DHT11_OK) {
      LEDR_Neg(); /* error */
      CLS1_SendStr("ERROR: ", io->stdErr);
      CLS1_SendStr(DHT1_GetReturnCodeString(res), io->stdErr);
      CLS1_SendStr("\r\n", io->stdErr);
    } else {
      LEDG_Neg(); /* ok */
      UTIL1_strcpy(buf, sizeof(buf), "Temperature ");
      UTIL1_strcatNum32sDotValue100(buf, sizeof(buf), (int32_t)temperature);
      UTIL1_strcat(buf, sizeof(buf), "°C, Humidity ");
      UTIL1_strcatNum32sDotValue100(buf, sizeof(buf), (int32_t)humidity);
      UTIL1_strcat(buf, sizeof(buf), "%\r\n");
      CLS1_SendStr(buf, io->stdOut);
    }
    WAIT1_Waitms(1000); /* can only read sensor values with 1 Hz! */
  }
}

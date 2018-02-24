/**
 * \file
 * \brief Implementation of a driver for the DHT11 temperature/humidity sensor.
 * \author Erich Styger, adopted from http://doitwireless.com/2014/07/01/temperature-and-humidity-measurement-with-dht11/
 */

#include "DHTxx.h"
#include "WAIT1.h"
#include "Data.h"

const unsigned char *DHTxx_GetReturnCodeString(DHTxx_ErrorCode code) {
  switch(code) {
    case DHTxx_OK:        return "OK";
    case DHTxx_NO_PULLUP: return "NO_PULLUP";
    case DHTxx_NO_ACK_0:  return "NO_ACK_0";
    case DHTxx_NO_ACK_1:  return "NO_ACK_1";
    case DHTxx_NO_DATA_0: return "NO_DATA_0";
    case DHTxx_NO_DATA_1: return "NO_DATA_1";
    case DHTxx_BAD_CRC:   return "BAD_CRC";
    default:              return "UNKNOWN?";
  }
}

DHTxx_ErrorCode DHTxx_Read(uint16_t *temperatureCentigrade, uint16_t *humidityCentipercent) {
  int cntr;
  int loopBits;
  uint8_t buffer[5];
  int i;
  int data;

  /* init buffer */
  for(i=0;i<sizeof(buffer); i++) {
    buffer[i] = 0;
  }
  EnterCritical(); /* disabling interrupts */
  /* Disabling interrupts so we do not get interrupted. Note that this is for a about 25 ms!
   * Alternatively only disable interrupts during sampling the data bits, and not during the first 18 ms.
   */
  /* set to input and check if the signal gets pulled up */
  Data_SetInput();
  WAIT1_Waitus(50);
  if(Data_GetVal()==0) {
    ExitCritical(); /* re-enabling interrupts */
    return DHTxx_NO_PULLUP;
  }
  /* send start signal */
  Data_SetOutput();
  Data_ClrVal();
  WAIT1_Waitms(18); /* keep signal low for at least 18 ms */
  Data_SetInput();
  WAIT1_Waitus(50);
  /* check for acknowledge signal */
  if (Data_GetVal()!=0) { /* signal must be pulled low by the sensor */
    ExitCritical(); /* re-enabling interrupts */
    return DHTxx_NO_ACK_0;
  }
  /* wait max 100 us for the ack signal from the sensor */
  cntr = 18;
  while(Data_GetVal()==0) { /* wait until signal goes up */
    WAIT1_Waitus(5);
    if (--cntr==0) {
      ExitCritical(); /* re-enabling interrupts */
      return DHTxx_NO_ACK_1; /* signal should be up for the ACK here */
    }
  }
  /* wait until it goes down again, end of ack sequence */
  cntr = 18;
  while(Data_GetVal()!=0) { /* wait until signal goes down */
    WAIT1_Waitus(5);
    if (--cntr==0) {
      ExitCritical(); /* re-enabling interrupts */
      return DHTxx_NO_ACK_0; /* signal should be down to zero again here */
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
        ExitCritical(); /* re-enabling interrupts */
        return DHTxx_NO_DATA_0;
      }
    }
    cntr = 15; /* wait max 75 us */
    while(Data_GetVal()!=0) {
      WAIT1_Waitus(5);
      if (--cntr==0) {
        ExitCritical(); /* re-enabling interrupts */
        return DHTxx_NO_DATA_1;
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
  ExitCritical(); /* re-enabling interrupts */

  /* now we have the 40 bit (5 bytes) data:
   * byte 1: humidity integer data
   * byte 2: humidity decimal data (not used for DTH11, always zero)
   * byte 3: temperature integer data
   * byte 4: temperature fractional data (not used for DTH11, always zero)
   * byte 5: checksum, the sum of byte 1 + 2 + 3 + 4
   */
  /* test CRC */
  if ((uint8_t)(buffer[0]+buffer[1]+buffer[2]+buffer[3])!=buffer[4]) {
    return DHTxx_BAD_CRC;
  }
  /* store data values for caller */
#if DHTxx_SENSOR_TYPE_IS_DHT11
  *humidityCentipercent = ((int)buffer[0])*100;
  *temperatureCentigrade = ((int)buffer[2])*100;
#else
  *humidityCentipercent = (((int)buffer[0]<<8)+buffer[1])*10;
  *temperatureCentigrade = (((int)buffer[2]<<8)+buffer[3])*10;
#endif
  return DHTxx_OK;
}

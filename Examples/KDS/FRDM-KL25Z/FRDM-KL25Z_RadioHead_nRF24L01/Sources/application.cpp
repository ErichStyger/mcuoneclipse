/*
 * application.cpp
 *
 *  Created on: 23.07.2016
 *      Author: Erich Styger Local
 */
#include "Platform.h"
#include "Kinetis.h"
#include "application.h"
#if PL_RH_TRANSCEIVER_TYPE==PL_RH_TRANSCEIVER_NRF24L01
  #include <RH_NRF24.h>
#elif PL_RH_TRANSCEIVER_TYPE==PL_RH_TRANSCEIVER_RH_RF95
  #include <RH_RF95.h>
#endif
#include "CLS1.h"
#include "UTIL1.h"
#include <RHReliableDatagram.h>
#include <stdlib.h>

#define IS_CLIENT   1  /* client or server */
#define IS_RELIABLE 0  /* reliable or not */

#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2

// Singleton instance of the radio driver
#if PL_RH_TRANSCEIVER_TYPE==PL_RH_TRANSCEIVER_NRF24L01
  static RH_NRF24 device(KINETIS_CE, KINETIS_SS);
  #define RH_APP_MAX_MESSAGE_LEN  RH_NRF24_MAX_MESSAGE_LEN
#elif PL_RH_TRANSCEIVER_TYPE==PL_RH_TRANSCEIVER_RH_RF95
  static RH_RF95 device(KINETIS_SS, KINETIS_ISR1);
  #define RH_APP_MAX_MESSAGE_LEN  RH_RF95_MAX_MESSAGE_LEN
#endif

static void Serial_println(const char *msg) {
  CLS1_ConstStdIOType *io = CLS1_GetStdio();

  CLS1_SendStr((const unsigned char*)msg, io->stdOut);
  CLS1_SendStr((const unsigned char*)"\r\n", io->stdOut);
}

void Serial_print(const char *msg) {
  CLS1_SendStr((const unsigned char*)msg, CLS1_GetStdio()->stdOut);
}

#if IS_CLIENT && !IS_RELIABLE
void setup(void) {
  if (!device.init()) {
    Serial_println("init failed");
  }
#if PL_RH_TRANSCEIVER_TYPE==PL_RH_TRANSCEIVER_NRF24L01
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!device.setChannel(1)) {
    Serial_println("setChannel failed");
  }
  if (!device.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm)) {
    Serial_println("setRF failed");
  }
#elif PL_RH_TRANSCEIVER_TYPE==PL_RH_TRANSCEIVER_RH_RF95
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
//  driver.setTxPower(23, false);
  // If you are using Modtronix inAir4 or inAir9,or any other module which uses the
  // transmitter RFO pins and not the PA_BOOST pins
  // then you can configure the power transmitter power for -1 to 14 dBm and with useRFO true.
  // Failure to do that will result in extremely low transmit powers.
//  driver.setTxPower(14, true);
#endif
}

void loop(void)
{
#if PL_RH_TRANSCEIVER_TYPE==PL_RH_TRANSCEIVER_RH_RF95
  Serial_println("Sending to RF95 LoRa server");
#elif PL_RH_TRANSCEIVER_TYPE==PL_RH_TRANSCEIVER_NRF24L01
  Serial_println("Sending to nRF24L01+ server");
#endif
  // Send a message to nrf24_server
  uint8_t data[] = "Hello World!";
  device.send(data, sizeof(data));

  device.waitPacketSent();
  // Now wait for a reply
  uint8_t buf[RH_APP_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
#if PL_RH_TRANSCEIVER_TYPE==PL_RH_TRANSCEIVER_RH_RF95
  if (device.waitAvailableTimeout(3000)) {
#elif PL_RH_TRANSCEIVER_TYPE==PL_RH_TRANSCEIVER_NRF24L01
  if (device.waitAvailableTimeout(500)) {
#endif
    // Should be a reply message for us now
    if (device.recv(buf, &len)) {
      Serial_print("got reply: ");
      Serial_println((char*)buf);
    } else {
      Serial_println("recv failed");
    }
  } else {
    Serial_println("No reply, is server running?");
  }
  delay(400);
}

#elif !IS_CLIENT && !IS_RELIABLE /* server */

void setup(void)  {
  //Serial.begin(9600);
  //while (!Serial)
  //  ; // wait for serial port to connect. Needed for Leonardo only
  if (!device.init()) {
    Serial_println("init failed");
  }
#if PL_RH_TRANSCEIVER_TYPE==PL_RH_TRANSCEIVER_NRF24L01
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!device.setChannel(1)) {
    Serial_println("setChannel failed");
  }
  if (!device.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm)) {
    Serial_println("setRF failed");
  }
#elif PL_RH_TRANSCEIVER_TYPE==PL_RH_TRANSCEIVER_RH_RF95
  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
//  driver.setTxPower(23, false);
  // If you are using Modtronix inAir4 or inAir9,or any other module which uses the
  // transmitter RFO pins and not the PA_BOOST pins
  // then you can configure the power transmitter power for -1 to 14 dBm and with useRFO true.
  // Failure to do that will result in extremely low transmit powers.
//  driver.setTxPower(14, true);
#endif
}

void loop(void) {
  if (device.available())
  {
    // Should be a message for us now
    uint8_t buf[RH_APP_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (device.recv(buf, &len))
    {
//      NRF24::printBuffer("request: ", buf, len);
      Serial_print("got request: ");
      Serial_println((char*)buf);

      // Send a reply
      uint8_t data[] = "And hello back to you";
      device.send(data, sizeof(data));
      device.waitPacketSent();
      Serial_println("Sent a reply");
    }
    else
    {
      Serial_println("recv failed");
    }
  }
}
#elif IS_CLIENT && IS_RELIABLE /* reliable client */
// Class to manage message delivery and receipt, using the driver declared above
RHReliableDatagram manager(device, CLIENT_ADDRESS);

void setup(void) {
  srand(100); /* initialize random seed */ /* \todo use soemthing 'random' */
  if (!manager.init())
    Serial_println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
}

uint8_t data[] = "Hello World!";
// Dont put this on the stack:
uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];

void loop(void) {
  Serial_println("Sending to nrf24_reliable_datagram_server");

  // Send a message to manager_server
  if (manager.sendtoWait(data, sizeof(data), SERVER_ADDRESS))
  {
    // Now wait for a reply from the server
    uint8_t len = sizeof(buf);
    uint8_t from;
    if (manager.recvfromAckTimeout(buf, &len, 2000, &from))
    {
      uint8_t buf[16];

      Serial_print("got reply from : 0x");
      buf[0] = '\0';
      UTIL1_strcatNum16Hex(buf, sizeof(buf), from);
      Serial_print((const char*)buf);
      Serial_print(": ");
      Serial_println((char*)buf);
    } else {
      Serial_println("No reply, is nrf24_reliable_datagram_server running?");
    }
  } else {
    Serial_println("sendtoWait failed");
  }
  delay(500);
}


#elif !IS_CLIENT && IS_RELIABLE /* reliable server */

// Class to manage message delivery and receipt, using the driver declared above
RHReliableDatagram manager(device, SERVER_ADDRESS);

void setup(void)  {
  srand(50); /* initialize random seed */ /* \todo use soemthing 'random' */
  if (!manager.init())
    Serial_println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
}

uint8_t data[] = "And hello back to you";
// Dont put this on the stack:
uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];

void loop(void) {
  if (manager.available()) {
    // Wait for a message addressed to us from the client
    uint8_t len = sizeof(buf);
    uint8_t from;
    if (manager.recvfromAck(buf, &len, &from))
    {
      uint8_t buf[16];

      Serial_print("got request from : 0x");
      buf[0] = '\0';
      UTIL1_strcatNum16Hex(buf, sizeof(buf), from);
      Serial_print((const char*)buf);
      Serial_print(": ");
      Serial_println((char*)buf);

      // Send a reply back to the originator client
      if (!manager.sendtoWait(data, sizeof(data), from))
        Serial_println("sendtoWait failed");
    }
  }
}


#endif /* server */

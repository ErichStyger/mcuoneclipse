/*
 * application.cpp
 *
 *  Created on: 23.07.2016
 *      Author: Erich Styger Local
 */

#include "Kinetis.h"
#include "application.h"
#include "RH_NRF24.h"
#include "CLS1.h"
#include <RH_NRF24.h>
#include <RHReliableDatagram.h>
#include "UTIL1.h"
#include <stdlib.h>

#define IS_CLIENT   0  /* client or server */
#define IS_RELIABLE 1  /* reliable or not */

#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2

// Singleton instance of the radio driver
RH_NRF24 nrf24(KINETIS_CE, KINETIS_SS);

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
  if (!nrf24.init())
    Serial_println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial_println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial_println("setRF failed");
}

void loop(void)
{
  Serial_println("Sending to nrf24_server");
  // Send a message to nrf24_server
  uint8_t data[] = "Hello World!";
  nrf24.send(data, sizeof(data));

  nrf24.waitPacketSent();
  // Now wait for a reply
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  if (nrf24.waitAvailableTimeout(500))
  {
    // Should be a reply message for us now
    if (nrf24.recv(buf, &len))
    {
      Serial_print("got reply: ");
      Serial_println((char*)buf);
    }
    else
    {
      Serial_println("recv failed");
    }
  }
  else
  {
    Serial_println("No reply, is nrf24_server running?");
  }
  delay(400);
}

#elif !IS_CLIENT && !IS_RELIABLE /* server */

void setup(void)  {
  //Serial.begin(9600);
  //while (!Serial)
  //  ; // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init())
    Serial_println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial_println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial_println("setRF failed");
}

void loop(void) {
  if (nrf24.available())
  {
    // Should be a message for us now
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (nrf24.recv(buf, &len))
    {
//      NRF24::printBuffer("request: ", buf, len);
      Serial_print("got request: ");
      Serial_println((char*)buf);

      // Send a reply
      uint8_t data[] = "And hello back to you";
      nrf24.send(data, sizeof(data));
      nrf24.waitPacketSent();
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
RHReliableDatagram manager(nrf24, CLIENT_ADDRESS);

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
RHReliableDatagram manager(nrf24, SERVER_ADDRESS);

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

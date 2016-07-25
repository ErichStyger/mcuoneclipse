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
//#include <SPI.h>
#include <RH_NRF24.h>
// Singleton instance of the radio driver
//RH_NRF24 nrf24;
// RH_NRF24 nrf24(8, 7); // use this to be electrically compatible with Mirf
// RH_NRF24 nrf24(8, 10);// For Leonardo, need explicit SS pin
// RH_NRF24 nrf24(8, 7); // For RFM73 on Anarduino Mini
RH_NRF24 nrf24(KINETIS_CE, KINETIS_SS);

static void Serial_println(const char *msg) {
  CLS1_ConstStdIOType *io = CLS1_GetStdio();

  CLS1_SendStr((const unsigned char*)msg, io->stdOut);
  CLS1_SendStr((const unsigned char*)"\r\n", io->stdOut);
}

void Serial_print(const char *msg) {
  CLS1_SendStr((const unsigned char*)msg, CLS1_GetStdio()->stdOut);
}


void setup()
{
 // Serial.begin(9600);
 // while (!Serial)
 //   ; // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init())
    Serial_println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial_println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial_println("setRF failed");
}
void loop()
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

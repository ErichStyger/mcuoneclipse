// serial_reliable_datagram_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple addressed, reliable messaging server
// with the RHReliableDatagram class, using the RH_Serial driver to
// communicate using packets over a serial port (or a radio connected to a
// serial port, such as the 3DR Telemetry radio V1 and others).
// It is designed to work with the other example serial_reliable_datagram_client
// Tested on Arduino Mega and ChipKit Uno32 (normal Arduinos only have one
// serial port and so it not possible to test on them and still have debug
// output)
// Tested with Arduino Mega, Teensy 3.1, Moteino, Arduino Due
// Also works on Linux an OSX. Build and test with:
//  tools/simBuild examples/serial/serial_reliable_datagram_server/serial_reliable_datagram_server.pde
//  RH_HARDWARESERIAL_DEVICE_NAME=/dev/ttyUSB0 ./serial_reliable_datagram_server 

#include <RHReliableDatagram.h>
#include <RH_Serial.h>

#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2

#if (RH_PLATFORM == RH_PLATFORM_UNIX)
 #include <RHutil/HardwareSerial.h>
 // On Unix we connect to a physical serial port
 // You can override this with RH_HARDWARESERIAL_DEVICE_NAME environment variable
 HardwareSerial hardwareserial("/dev/ttyUSB0");
 RH_Serial driver(hardwareserial);

#else
 // On arduino etc, use a predefined local serial port
 // eg Serial1 on a Mega
 #include <SPI.h>
 // Singleton instance of the Serial driver, configured
 // to use the port Serial1. Caution: on Uno32, Serial1 is on pins 39 (Rx) and
 // 40 (Tx)
 RH_Serial driver(Serial1);
#endif

// Class to manage message delivery and receipt, using the driver declared above
RHReliableDatagram manager(driver, SERVER_ADDRESS);

void setup() 
{
  Serial.begin(9600);
  // Configure the port RH_Serial will use:
  driver.serial().begin(9600);
  if (!manager.init())
    Serial.println("init failed");
}

uint8_t data[] = "And hello back to you";
// Dont put this on the stack:
uint8_t buf[RH_SERIAL_MAX_MESSAGE_LEN];

void loop()
{

  // Wait for a message addressed to us from the client
  manager.waitAvailable();
      
  uint8_t len = sizeof(buf);
  uint8_t from;
  if (manager.recvfromAck(buf, &len, &from))
  {
    Serial.print("got request from : 0x");
    Serial.print(from, HEX);
    Serial.print(": ");
    Serial.println((char*)buf);

    // Send a reply back to the originator client
    if (!manager.sendtoWait(data, sizeof(data), from))
      Serial.println("sendtoWait failed");
  }
}


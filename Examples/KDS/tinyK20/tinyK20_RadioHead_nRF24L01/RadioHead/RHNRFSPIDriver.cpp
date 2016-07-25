// RHNRFSPIDriver.cpp
//
// Copyright (C) 2014 Mike McCauley
// $Id: RHNRFSPIDriver.cpp,v 1.3 2015/12/16 04:55:33 mikem Exp $

#include <RHNRFSPIDriver.h>

RHNRFSPIDriver::RHNRFSPIDriver(uint8_t slaveSelectPin, RHGenericSPI& spi)
    : 
    _spi(spi),
    _slaveSelectPin(slaveSelectPin)
{
}

bool RHNRFSPIDriver::init()
{
    // start the SPI library with the default speeds etc:
    // On Arduino Due this defaults to SPI1 on the central group of 6 SPI pins
    _spi.begin();

    // Initialise the slave select pin
    // On Maple, this must be _after_ spi.begin
    pinMode(_slaveSelectPin, OUTPUT);
    digitalWrite(_slaveSelectPin, HIGH);

    delay(100);
    return true;
}

// Low level commands for interfacing with the device
uint8_t RHNRFSPIDriver::spiCommand(uint8_t command)
{
    uint8_t status;
    ATOMIC_BLOCK_START;
    digitalWrite(_slaveSelectPin, LOW);
    status = _spi.transfer(command);
    digitalWrite(_slaveSelectPin, HIGH);
    ATOMIC_BLOCK_END;
    return status;
}

uint8_t RHNRFSPIDriver::spiRead(uint8_t reg)
{
    uint8_t val;
    ATOMIC_BLOCK_START;
    digitalWrite(_slaveSelectPin, LOW);
    _spi.transfer(reg); // Send the address, discard the status
    val = _spi.transfer(0); // The written value is ignored, reg value is read
    digitalWrite(_slaveSelectPin, HIGH);
    ATOMIC_BLOCK_END;
    return val;
}

uint8_t RHNRFSPIDriver::spiWrite(uint8_t reg, uint8_t val)
{
    uint8_t status = 0;
    ATOMIC_BLOCK_START;
    digitalWrite(_slaveSelectPin, LOW);
    status = _spi.transfer(reg); // Send the address
    _spi.transfer(val); // New value follows
#if (RH_PLATFORM == RH_PLATFORM_ARDUINO) && defined(__arm__) && defined(CORE_TEENSY)
    // Sigh: some devices, such as MRF89XA dont work properly on Teensy 3.1:
    // At 1MHz, the clock returns low _after_ slave select goes high, which prevents SPI
    // write working. This delay gixes time for the clock to return low.
delayMicroseconds(5);
#endif
    digitalWrite(_slaveSelectPin, HIGH);
    ATOMIC_BLOCK_END;
    return status;
}

uint8_t RHNRFSPIDriver::spiBurstRead(uint8_t reg, uint8_t* dest, uint8_t len)
{
    uint8_t status = 0;
    ATOMIC_BLOCK_START;
    digitalWrite(_slaveSelectPin, LOW);
    status = _spi.transfer(reg); // Send the start address
    while (len--)
	*dest++ = _spi.transfer(0);
    digitalWrite(_slaveSelectPin, HIGH);
    ATOMIC_BLOCK_END;
    return status;
}

uint8_t RHNRFSPIDriver::spiBurstWrite(uint8_t reg, const uint8_t* src, uint8_t len)
{
    uint8_t status = 0;
    ATOMIC_BLOCK_START;
    digitalWrite(_slaveSelectPin, LOW);
    status = _spi.transfer(reg); // Send the start address
    while (len--)
	_spi.transfer(*src++);
    digitalWrite(_slaveSelectPin, HIGH);
    ATOMIC_BLOCK_END;
    return status;
}

void RHNRFSPIDriver::setSlaveSelectPin(uint8_t slaveSelectPin)
{
    _slaveSelectPin = slaveSelectPin;
}



// RHHardwareSPI.h
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2011 Mike McCauley
// Contributed by Joanna Rutkowska
// $Id: RHHardwareSPI.h,v 1.9 2014/08/12 00:54:52 mikem Exp $

#ifndef RHHardwareSPI_h
#define RHHardwareSPI_h

#include <RHGenericSPI.h>

/////////////////////////////////////////////////////////////////////
/// \class RHHardwareSPI RHHardwareSPI.h <RHHardwareSPI.h>
/// \brief Encapsulate a hardware SPI bus interface
///
/// This concrete subclass of GenericSPIClass encapsulates the standard Arduino hardware and other
/// hardware SPI interfaces.
class RHHardwareSPI : public RHGenericSPI
{
#ifdef RH_HAVE_HARDWARE_SPI
public:
    /// Constructor
    /// Creates an instance of a hardware SPI interface, using whatever SPI hardware is available on
    /// your processor platform. On Arduino and Uno32, uses SPI. On Maple, uses HardwareSPI.
    /// \param[in] frequency One of RHGenericSPI::Frequency to select the SPI bus frequency. The frequency
    /// is mapped to the closest available bus frequency on the platform.
    /// \param[in] bitOrder Select the SPI bus bit order, one of RHGenericSPI::BitOrderMSBFirst or 
    /// RHGenericSPI::BitOrderLSBFirst.
    /// \param[in] dataMode Selects the SPI bus data mode. One of RHGenericSPI::DataMode
    RHHardwareSPI(Frequency frequency = Frequency1MHz, BitOrder bitOrder = BitOrderMSBFirst, DataMode dataMode = DataMode0);

    /// Transfer a single octet to and from the SPI interface
    /// \param[in] data The octet to send
    /// \return The octet read from SPI while the data octet was sent
    uint8_t transfer(uint8_t data);

    // SPI Configuration methods
    /// Enable SPI interrupts
    /// This can be used in an SPI slave to indicate when an SPI message has been received
    /// It will cause the SPI_STC_vect interrupt vectr to be executed
    void attachInterrupt();

    /// Disable SPI interrupts
    /// This can be used to diable the SPI interrupt in slaves where that is supported.
    void detachInterrupt();
    
    /// Initialise the SPI library
    /// Call this after configuring the SPI interface and before using it to transfer data.
    /// Initializes the SPI bus by setting SCK, MOSI, and SS to outputs, pulling SCK and MOSI low, and SS high. 
    void begin();

    /// Disables the SPI bus (leaving pin modes unchanged). 
    /// Call this after you have finished using the SPI interface.
    void end();
#else
    // not supported on ATTiny etc
    uint8_t transfer(uint8_t data) {return 0;}
    void begin(){}
    void end(){}

#endif
};

// Built in default instance
extern RHHardwareSPI hardware_spi;

#endif

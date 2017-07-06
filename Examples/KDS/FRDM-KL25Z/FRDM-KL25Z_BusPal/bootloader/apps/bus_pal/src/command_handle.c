/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "command_handle.h"
#include "bus_pal_hardware.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief constant definitions
enum
{
    kBusPalMaxReadWriteSize = 2048,
    kBusPalCommandBufferSize = 8200,
    kBusPalMaxCommandLength = 50
};

//! @brief string size macro
#define STRING_SIZE_NO_NULL(string) (sizeof(string) - 1)

//! @brief Response to enter bit bang mode.
// static const uint8_t k_responseBitBangMode[] = "BBIO1";
static const uint8_t k_responseReset[] = "BBIO1";
static const uint8_t k_responseSpiMode[] = "SPI1";
static const uint8_t k_responseI2cMode[] = "I2C1";
static const uint8_t k_responseCanMode[] = "CAN1";
// static const uint8_t k_responseUartMode[] = "ART1";

//! @brief BusPal working mode constants
typedef enum
{
    kBusPalBitBang, //!< buspal is in default bit bang mode
    kBusPalSpiMode, //!< buspal works on SPI bit bang mode
    kBusPalI2cMode, //!< buspal works on I2C bit bang mode
    kBusPalCanMode, //!< buspal works on CAN bit bang mode
} bus_pal_mode_t;

//! @brief BusPal response
enum
{
    kBusPalResponseOK = 1,
    kBusPalResponseFail = 0
};

//! @brief BusPal bit bang commands
enum
{
    kBitBang_Reset = 0x00,        //!< Reset, responds "BBIO1"
    kBitBang_SpiMode = 0x01,      //!< Enter binary SPI mode, responds "SPI1"
    kBitBang_I2cMode = 0x02,      //!< Enter binary I2C mode, responds "I2C1"
    kBitBang_UartMode = 0x03,     //!< Enter binary UART mode, responds "ART1"
    kBitBang_1Wire = 0x04,        //!< Enter binary 1-Wire mode, responds "1W01"
    kBitBang_RawWire = 0x05,      //!< Enter binary raw-wire mode, responds "RAW1"
    kBitBang_Jtag = 0x06,         //!< Enter OpenOCD JTAG mode
    kBitBang_CanMode = 0x07,      //!< Enter binary CAN mode, responds "CAN1"
    kBitBang_HardReset = 0x0f,    //!< Reset Bus Pal
    kBitBang_SelfTest = 0x10,     //!< Bus Pal self-tests
    kBitBang_SetupPwm = 0x12,     //!< Setup pulse-width modulation (requires 5 byte setup)
    kBitBang_ClearPwm = 0x13,     //!< Clear/disable PWM
    kBitBang_Probe = 0x14,        //!< Take voltage probe measurement (returns 2 bytes)
    kBitBang_ContProbe = 0x15,    //!< Continuous voltage probe measurement
    kBitBang_FreqAux = 0x16,      //!< Frequency measurement on AUX pin
    kBitBang_SetFpgaClock = 0x20, //!< Set the clock frequency on the FPGA board
    kBitBang_CfgPins = 0x40,      //!< Configure pins as input(1) or output(0): AUX|MOSI|CLK|MISO|CS
    kBitBang_SetPins = 0x80       //!< Set on (1) or off (0): POWER|PULLUP|AUX|MOSI|CLK|MISO|CS
};

//! @brief Spi mode commands.
enum
{
    kSpi_Exit = 0x00,         //!< 00000000 - Exit to bit bang mode
    kSpi_Version = 0x01,      //!< 00000001 - Enter raw SPI mode, display version string
    kSpi_ChipSelect = 0x02,   //!< 0000001x - CS high (1) or low (0)
    kSpi_Sniff = 0x0c,        //!< 000011XX - Sniff SPI traffic when CS low(10)/all(01)
    kSpi_BulkTransfer = 0x10, //!< 0001xxxx - Bulk SPI transfer, send/read 1-16 bytes (0=1byte!)
    kSpi_ConfigPeriph = 0x40, //!< 0100wxyz - Configure peripherals w=power, x=pull-ups, y=AUX, z=CS
    kSpi_SetSpeed = 0x60,     //!< 01100000 - SPI speed
    kSpi_ConfigSpi = 0x80,    //!< 1000wxyz - SPI config, w=HiZ/3.3v, x=CKP idle, y=CKE edge, z=SMP sample
    kSpi_WriteThenRead = 0x04 //!< 00000100 - Write then read extended command
};

//! @brief Spi configuration shifts for the mask
#define kSpi_ChipSelect_mask 0x01
#define kSpi_Sniff_mask 0x03
#define kSpi_BulkTransfer_mask 0x0F
#define kSpi_ConfigPeriph_mask 0x0F
#define kSpi_ConfigSpi_mask 0x0F
#define kSpiConfigShift_Direction 0
#define kSpiConfigShift_Phase 1
#define kSpiConfigShift_Polarity 2

//! @brief Can mode commands.
enum
{
    kCan_Exit = 0x00,          //!< 00000000 - Exit to bit bang mode
    kCan_Version = 0x01,       //!< 00000001 – Display mode version string, responds "CANx"
    kCan_BulkWrite = 0x02,     //!< 00000010
    kCan_WriteThenRead = 0x03, //!< 00000011 - Write then read extended command
    kCan_ReadFrame = 0x04,     //!< 00000100 - CAN read frame
    kCan_WriteFrame = 0x05,    //!< 00000101 - CAN write frame
    kCan_AckBit = 0x06,        //!< 00000110 - ACK bit
    kCan_NackBit = 0x07,       //!< 00000111 - NACK bit
    kCan_SetRxFifoId = 0x10,   //!< 00010000 - Set CAN RX FIFO id
    kCan_SetRxMbId = 0x20,     //!< 00100000 - Set CAN RX MB id
    kCan_SetTxMbId = 0x30,     //!< 00110000 - Set CAN TX MB id
    kCan_SetSpeed = 0x40       //!< 010000xx - Set CAN speed, 4=125kHz, 3=250kHz, 2=500kHz, 1=750kHz, 0=1MHz
};

//! @brief I2c mode commands.
enum
{
    kI2c_Exit = 0x00,            //!< 00000000 - Exit to bit bang mode
    kI2c_Version = 0x01,         //!< 00000001 – Display mode version string, responds "I2Cx"
    kI2c_StartBit = 0x02,        //!< 00000010 – I2C start bit
    kI2c_StopBit = 0x03,         //!< 00000011 – I2C stop bit
    kI2c_ReadByte = 0x04,        //!< 00000100 - I2C read byte
    kI2c_AckBit = 0x06,          //!< 00000110 - ACK bit
    kI2c_NackBit = 0x07,         //!< 00000111 - NACK bit
    kI2c_BusSniff = 0x0F,        //!< 00001111 - Start bus sniffer
    kI2c_BulkWrite = 0x10,       //!< 0001xxxx – Bulk I2C write, send 1-16 bytes (0=1byte!)
    kI2c_ConfigurePeriph = 0x40, //!< 0100wxyz – Configure peripherals w=power, x=pullups, y=AUX, z=CS
    kI2c_PullUpSelect = 0x50,    //!< 010100xy - Pull up voltage select (BPV4 only)- x=5v y=3.3v
    kI2c_SetSpeed =
        0x60, //!< 011000xx - Set I2C speed, 3=~400kHz, 2=~100kHz, 1=~50kHz, 0=~5kHz (updated in v4.2 firmware)
    kI2c_SetAddress = 0x70,   //!< 11100000 - Set I2C address
    kI2c_WriteThenRead = 0x08 //!< Write then read
};

//! @brief I2c configuration shifts for the mask
#define kI2c_BulkWrite_mask 0x0F
#define kI2c_ConfigurePeriph_mask 0x0F
#define kI2c_PullUpSelect_mask 0x03

//! @brief Uart Mode commands.
enum
{
    kUart_Version = 0x01,      //!< Display mode version string, responds "ARTx"
    kUart_EchoRx = 0x02,       //!< Start (0)/stop(1) echo UART RX
    kUart_SetBaud = 0x07,      //!< Manual baud rate configuration, send 2 bytes
    kUart_Bridge = 0x0f,       //!< UART bridge mode (reset to exit)
    kUart_BulkWrite = 0x10,    //!< Bulk UART write, send 1-16 bytes (0 = 1byte!)
    kUart_ConfigPeriph = 0x40, //!< Configure peripherals w = power, x = pullups, y = AUX, z = CS
    kUart_SetSpeed = 0x60,     //!< Set UART speed
    kUart_ConfigUart = 0x80    //!< Configure UART settings
};

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Variable for buspal working peripheral
static bus_pal_mode_t s_mode = kBusPalBitBang;
static uint32_t s_commandOffset;
static uint8_t s_commandBuffer[kBusPalCommandBufferSize];
static uint8_t s_targetRxBuffer[kBusPalMaxReadWriteSize];

/*!
 * @brief The below pointer is used for the buffer locations instead of the s_commandBuffer
 * specifically because it can make it easier for tracking the command history by incrementing
 * the pointer
 */
static uint8_t *s_commandPtr = s_commandBuffer;

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief static local function prototypes
 */
//! @brief handle bit ban command
static void handleBitBangCommand(uint8_t command);

//! @brief handle spi mode command
static void handleSpiModeCommand(uint8_t command);

//! @brief handle i2c mode command
static void handleI2cModeCommand(uint8_t command);

//! @brief handle can mode command
static void handleCanModeCommand(uint8_t command);

//! @brief handle reset mode command
static void handleResetMode(void);

//! @brief send ok response
static void sendOKResponse(void);

//! @brief send fail response
static void sendFailResponse(void);

//! @brief wait for command bytes
static void wait_for_command_bytes(uint32_t currentBytesReceived, uint32_t numBytesRemaining);

//! @brief handle gpio set command
static void handleGpioSet(void);

//! @brief handle gpio configue command
static void handleGpioConfigure(void);

//! @brief handle fpga clock
static void handleSetFpgaClock(void);

//! @brief handle spi enter mode
static void handleSpiEnterMode(void);

//! @brief handle spi bulk transfer
static void handleSpiBulkTransfer(uint8_t bytes);

//! @brief handle spi speed set up
static void handleSpiSetSpeed(void);

//! @brief handle spi configue command
static void handleSpiConfigCommand(uint8_t configMask);

//! @brief handle spi write then read
static void handleSpiWriteThenRead(void);

//! @brief handle flexcan enter mode
static void handleCanEnterMode(void);

//! @brief handle flexcan set up speed
static void handleCanSetSpeed(void);

//! @brief handle i2c enter mode
static void handleI2cEnterMode(void);

//! @brief handle i2c bulk write
static void handleI2cBulkWrite(uint8_t bytes);

//! @brief handle i2c set up address
static void handleI2cSetAddress(void);

//! @brief handle i2c set up speed
static void handleI2cSetSpeed(void);

//! @brief handle i2c write then read
static void handleI2cWriteThenRead(void);

#if defined(CPU_MK65FN2M0VMI18)
//! @brief handle USB command
extern void handleUsbBusPalCommand();
#endif

extern void init_hardware(void);

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Helper functions
////////////////////////////////////////////////////////////////////////////////

/*FUNCTION**********************************************************************
 *
 * Function Name : uint16_from_buffer
 * Description   : get 16 bit from buffer
 *
 *END**************************************************************************/
/*inline*/ uint16_t uint16_from_buffer(uint8_t *buffer)
{
    return (((uint32_t)buffer[1] << 8) | (uint32_t)buffer[0]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : uint32_from_buffer
 * Description   : get 32 bit from buffer
 *
 *END**************************************************************************/
/*inline*/ uint32_t uint32_from_buffer(uint8_t *buffer)
{
    return (((uint32_t)buffer[3] << 24) | ((uint32_t)buffer[2] << 16) | ((uint32_t)buffer[1] << 8) |
            (uint32_t)buffer[0]);
}

////////////////////////////////////////////////////////////////////////////////
// Bit bang and Common code
////////////////////////////////////////////////////////////////////////////////

/*FUNCTION**********************************************************************
 *
 * Function Name : sendOKResponse
 * Description   : send of response
 *
 *END**************************************************************************/
static void sendOKResponse(void)
{
    uint8_t byte = kBusPalResponseOK;
    write_bytes_to_host(&byte, sizeof(byte));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : sendFailResponse
 * Description   : send fail response
 *
 *END**************************************************************************/
static void sendFailResponse(void)
{
    uint8_t byte = kBusPalResponseFail;
    write_bytes_to_host(&byte, sizeof(byte));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleResetMode
 * Description   : handle reset mode
 *
 *END**************************************************************************/
static void handleResetMode(void)
{
    init_hardware();
    s_mode = kBusPalBitBang;
    write_bytes_to_host((uint8_t *)k_responseReset, STRING_SIZE_NO_NULL(k_responseReset));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleSetFpgaClock
 * Description   : handle set fpga clock
 *
 *END**************************************************************************/
static void handleSetFpgaClock(void)
{
    uint32_t clock;

    wait_for_command_bytes(s_commandOffset, sizeof(clock));
    clock = uint32_from_buffer(s_commandPtr + s_commandOffset);

    set_fpga_clock(clock);

    sendOKResponse();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleGpioConfigure
 * Description   : handle gpio configuration
 *
 *END**************************************************************************/
static void handleGpioConfigure(void)
{
    uint8_t port;
    uint8_t pinNum;
    uint8_t muxVal;

    wait_for_command_bytes(s_commandOffset, sizeof(port));
    port = s_commandPtr[s_commandOffset];
    s_commandOffset += sizeof(port);

    wait_for_command_bytes(s_commandOffset, sizeof(pinNum));
    pinNum = s_commandPtr[s_commandOffset];
    s_commandOffset += sizeof(pinNum);

    wait_for_command_bytes(s_commandOffset, sizeof(muxVal));
    muxVal = s_commandPtr[s_commandOffset];
    s_commandOffset += sizeof(muxVal);

    configure_gpio(port, pinNum, muxVal);

    sendOKResponse();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleGpioSet
 * Description   : handle gpio set up
 *
 *END**************************************************************************/
static void handleGpioSet(void)
{
    uint8_t port;
    uint8_t pinNum;
    uint8_t level;

    wait_for_command_bytes(s_commandOffset, sizeof(port));
    port = s_commandPtr[s_commandOffset];
    s_commandOffset += sizeof(port);

    wait_for_command_bytes(s_commandOffset, sizeof(pinNum));
    pinNum = s_commandPtr[s_commandOffset];
    s_commandOffset += sizeof(pinNum);

    wait_for_command_bytes(s_commandOffset, sizeof(level));
    level = s_commandPtr[s_commandOffset];
    s_commandOffset += sizeof(level);

    set_gpio(port, pinNum, level);

    sendOKResponse();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleBitBangCommand
 * Description   : handle big ban command
 *
 *END**************************************************************************/
static void handleBitBangCommand(uint8_t command)
{
    switch (command)
    {
        case kBitBang_Reset:
            handleResetMode();
            break;
        case kBitBang_SpiMode:
            handleSpiEnterMode();
            break;
        case kBitBang_CanMode:
            handleCanEnterMode();
            break;
        case kBitBang_I2cMode:
            handleI2cEnterMode();
            break;
        case kBitBang_SetPins:
            handleGpioSet();
            break;
        case kBitBang_CfgPins:
            handleGpioConfigure();
            break;
        case kBitBang_SetFpgaClock:
            handleSetFpgaClock();
            break;
        default:
            sendFailResponse();
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handle_command
 * Description   : general command handler
 *
 *END**************************************************************************/
void handle_command(void)
{
    // Read command from host
    s_commandOffset = 0;
    uint8_t command = 0;

    host_start_command_rx(s_commandPtr, kBusPalCommandBufferSize);

    wait_for_command_bytes(s_commandOffset, sizeof(command));

    command = s_commandPtr[s_commandOffset];
    s_commandOffset += sizeof(command);

    switch (s_mode)
    {
        case kBusPalBitBang:
            handleBitBangCommand(command);
            break;
        case kBusPalSpiMode:
            handleSpiModeCommand(command);
            break;
        case kBusPalCanMode:
            handleCanModeCommand(command);
            break;
        case kBusPalI2cMode:
            handleI2cModeCommand(command);
            break;
        default:
            sendFailResponse();
            break;
    }

    host_stop_command_rx();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : wait_for_command_bytes
 * Description   : wait for command bytes
 *
 *END**************************************************************************/
void wait_for_command_bytes(uint32_t currentBytesReceived, uint32_t numBytesRemaining)
{
    uint32_t totalBytes = currentBytesReceived + numBytesRemaining;

#if defined(CPU_MK65FN2M0VMI18)
    bool usbActive = false;

    if (scuart_poll_for_activity() == true)
    {
        while (currentBytesReceived < totalBytes)
        {
            currentBytesReceived = get_bytes_received_from_host();
        }
    }
    else
    {
        while (currentBytesReceived < totalBytes &&
               ((usbActive = usb_hid_poll_for_activity(&g_peripherals[0])) == false))
        {
            currentBytesReceived = get_bytes_received_from_host();
        }

        if (usbActive == true)
        {
            usb_hid_packet_init(&g_peripherals[0]);
            handleUsbBusPalCommand();
        }
    }
#else
    while (currentBytesReceived < totalBytes)
    {
        currentBytesReceived = get_bytes_received_from_host();
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
// Spi commands
////////////////////////////////////////////////////////////////////////////////

/*FUNCTION**********************************************************************
 *
 * Function Name : handleSpiEnterMode
 * Description   : handle spi enter mode
 *
 *END**************************************************************************/
static void handleSpiEnterMode(void)
{
    if (s_mode != kBusPalSpiMode)
    {
        s_mode = kBusPalSpiMode;
    }

    write_bytes_to_host((uint8_t *)k_responseSpiMode, STRING_SIZE_NO_NULL(k_responseSpiMode));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleSpiBulkTransfer
 * Description   : handle spi bulk transfer
 *
 *END**************************************************************************/
static void handleSpiBulkTransfer(uint8_t bytes)
{
    sendOKResponse();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleSpiSetSpeed
 * Description   : handle spi set up speed
 *
 *END**************************************************************************/
static void handleSpiSetSpeed(void)
{
    uint32_t speed = 0;

    wait_for_command_bytes(s_commandOffset, sizeof(speed));
    speed = uint32_from_buffer(s_commandPtr + s_commandOffset);
    s_commandOffset += sizeof(speed);

    configure_spi_speed(speed);

    sendOKResponse();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleSpiConfigCommand
 * Description   : handle spi configuration command
 *
 *END**************************************************************************/
static void handleSpiConfigCommand(uint8_t configMask)
{
#if defined(CPU_MKL25Z128VLK4) || defined(CPU_MKL43Z256VLH4)
    spi_clock_polarity_t polarity = (spi_clock_polarity_t)((configMask >> kSpiConfigShift_Polarity) & 1);
    spi_clock_phase_t phase = (spi_clock_phase_t)((configMask >> kSpiConfigShift_Phase) & 1);
    spi_shift_direction_t direction = (spi_shift_direction_t)((configMask >> kSpiConfigShift_Direction) & 1);
#endif
#if defined(CPU_MKV46F256VLL16) || defined(CPU_MK65FN2M0VMI18)
    dspi_clock_polarity_t polarity = (dspi_clock_polarity_t)((configMask >> kSpiConfigShift_Polarity) & 1);
    dspi_clock_phase_t phase = (dspi_clock_phase_t)((configMask >> kSpiConfigShift_Phase) & 1);
    dspi_shift_direction_t direction = (dspi_shift_direction_t)((configMask >> kSpiConfigShift_Direction) & 1);
#endif
    configure_spi_settings(polarity, phase, direction);

    sendOKResponse();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleSpiWriteThenRead
 * Description   : handle spi write and read
 *
 *END**************************************************************************/
static void handleSpiWriteThenRead(void)
{
    uint16_t numBytesToWrite = 0;
    uint16_t numBytesToRead = 0;

    // Get the number of bytes to write
    wait_for_command_bytes(s_commandOffset, sizeof(numBytesToWrite));
    numBytesToWrite = uint16_from_buffer(s_commandPtr + s_commandOffset);
    s_commandOffset += sizeof(numBytesToWrite);

    // Get the number of bytes to read
    wait_for_command_bytes(s_commandOffset, sizeof(numBytesToRead));
    numBytesToRead = uint16_from_buffer(s_commandPtr + s_commandOffset);
    s_commandOffset += sizeof(numBytesToRead);

    // If there are bytes to write and we have enough buffer space for them
    // read the bytes that we need to write to Spi from the host
    if (numBytesToWrite && (numBytesToWrite < kBusPalMaxReadWriteSize))
    {
        wait_for_command_bytes(s_commandOffset, numBytesToWrite);
    }

    // if there are bytes to be written send these bytes to the target
    if (numBytesToWrite)
    {
        send_spi_data(s_commandPtr + s_commandOffset, numBytesToWrite);

        s_commandOffset += numBytesToWrite;
    }

    // If there are bytes to read and we have enough buffer space read
    // the bytes from the target
    if (numBytesToRead && (numBytesToRead < kBusPalMaxReadWriteSize))
    {
        receive_spi_data(s_targetRxBuffer, numBytesToRead);
    }

    sendOKResponse();

    // If everything went ok then send these bytes back to the host
    if (numBytesToRead)
    {
        write_bytes_to_host(s_targetRxBuffer, numBytesToRead);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleSpiModeCommand
 * Description   : handle spi mode command
 *
 *END**************************************************************************/
static void handleSpiModeCommand(uint8_t command)
{
    if (command == kSpi_Exit)
    {
        handleResetMode();
    }
    else if (command == kSpi_WriteThenRead)
    {
        handleSpiWriteThenRead();
    }
    else if (command == kSpi_SetSpeed)
    {
        handleSpiSetSpeed();
    }
    else if (command <= kSpi_Version)
    {
        handleSpiEnterMode();
    }
    else if ((command >= kSpi_ChipSelect) && (command <= (kSpi_ChipSelect | kSpi_ChipSelect_mask)))
    {
        sendFailResponse();
    }
    else if ((command >= kSpi_Sniff) && (command <= (kSpi_Sniff | kSpi_Sniff_mask)))
    {
        sendFailResponse();
    }
    else if ((command >= kSpi_BulkTransfer) && (command <= (kSpi_BulkTransfer | kSpi_BulkTransfer_mask)))
    {
        handleSpiBulkTransfer(command & kSpi_BulkTransfer_mask);
    }
    else if ((command >= kSpi_ConfigPeriph) && (command <= (kSpi_ConfigPeriph | kSpi_ConfigPeriph_mask)))
    {
        sendFailResponse();
    }
    else if ((command >= kSpi_ConfigSpi) && (command <= (kSpi_ConfigSpi | kSpi_ConfigSpi_mask)))
    {
        handleSpiConfigCommand(command & kSpi_ConfigSpi_mask);
    }
    else
    {
        sendFailResponse();
    }
}

////////////////////////////////////////////////////////////////////////////////
// Can commands
////////////////////////////////////////////////////////////////////////////////

/*FUNCTION**********************************************************************
 *
 * Function Name : handleCanEnterMode
 * Description   : handle flexcan enter mode
 *
 *END**************************************************************************/
static void handleCanEnterMode(void)
{
    if (s_mode != kBusPalCanMode)
    {
        s_mode = kBusPalCanMode;
    }

    write_bytes_to_host((uint8_t *)k_responseCanMode, STRING_SIZE_NO_NULL(k_responseCanMode));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleCanSetTxid
 * Description   : handle flexcan tx id
 *
 *END**************************************************************************/
static void handleCanSetTxid(void)
{
#if defined(CPU_MKV46F256VLL16) || defined(CPU_MK65FN2M0VMI18)
    uint32_t txid = 0;

    wait_for_command_bytes(s_commandOffset, sizeof(txid));
    txid = uint32_from_buffer(s_commandPtr + s_commandOffset);
    s_commandOffset += sizeof(txid);

    configure_can_txid(txid);

    sendOKResponse();
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleCanSetRxid
 * Description   : handle flexcan rx id
 *
 *END**************************************************************************/
static void handleCanSetRxid(void)
{
#if defined(CPU_MKV46F256VLL16) || defined(CPU_MK65FN2M0VMI18)
    uint32_t rxid = 0;

    wait_for_command_bytes(s_commandOffset, sizeof(rxid));
    rxid = uint32_from_buffer(s_commandPtr + s_commandOffset);
    s_commandOffset += sizeof(rxid);

    configure_can_rxid(rxid);

    sendOKResponse();
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleCanSetSpeed
 * Description   : handle flexcan speed set up
 *
 *END**************************************************************************/
static void handleCanSetSpeed(void)
{
#if defined(CPU_MKV46F256VLL16) || defined(CPU_MK65FN2M0VMI18)
    uint32_t speed = 0;

    wait_for_command_bytes(s_commandOffset, sizeof(speed));
    speed = uint32_from_buffer(s_commandPtr + s_commandOffset);
    s_commandOffset += sizeof(speed);

    configure_can_speed(speed);

    sendOKResponse();
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleCanWriteThenRead
 * Description   : handle flexcan write then read
 *
 *END**************************************************************************/
static void handleCanWriteThenRead(void)
{
#if defined(CPU_MKV46F256VLL16) || defined(CPU_MK65FN2M0VMI18)
    uint16_t numBytesToWrite = 0;
    uint16_t numBytesToRead = 0;

    // Get the number of bytes to write
    wait_for_command_bytes(s_commandOffset, sizeof(numBytesToWrite));
    numBytesToWrite = uint16_from_buffer(s_commandPtr + s_commandOffset);
    s_commandOffset += sizeof(numBytesToWrite);

    // Get the number of bytes to read
    wait_for_command_bytes(s_commandOffset, sizeof(numBytesToRead));
    numBytesToRead = uint16_from_buffer(s_commandPtr + s_commandOffset);
    s_commandOffset += sizeof(numBytesToRead);

    // If there are bytes to write and we have enough buffer space for them
    // read the bytes that we need to write to Can from the host
    if (numBytesToWrite && (numBytesToWrite < kBusPalMaxReadWriteSize))
    {
        wait_for_command_bytes(s_commandOffset, numBytesToWrite);
    }

    // if there are bytes to be written send these bytes to the target
    if (numBytesToWrite)
    {
        send_can_data(s_commandPtr + s_commandOffset, numBytesToWrite);
        reset_can_buffer();
        s_commandOffset += numBytesToWrite;
    }

    // If there are bytes to read and we have enough buffer space read
    // the bytes from the target
    if (numBytesToRead && (numBytesToRead < kBusPalMaxReadWriteSize))
    {
        read_can_data(s_targetRxBuffer, numBytesToRead);
    }

    sendOKResponse();

    // If everything went ok then send these bytes back to the host
    if (numBytesToRead)
    {
        write_bytes_to_host(s_targetRxBuffer, numBytesToRead);
    }
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleCanModeCommand
 * Description   : handle flexcan mode command
 *
 *END**************************************************************************/
static void handleCanModeCommand(uint8_t command)
{
    if (command == kCan_Exit)
    {
        handleResetMode();
    }
    else if (command == kCan_WriteThenRead)
    {
        handleCanWriteThenRead();
    }
    else if (command == kCan_SetTxMbId)
    {
        handleCanSetTxid();
    }
    else if (command == kCan_SetRxMbId)
    {
        handleCanSetRxid();
    }
    else if (command == kCan_SetSpeed)
    {
        handleCanSetSpeed();
    }
    else if (command <= kCan_Version)
    {
        //        handleCanEnterMode();
    }
    else
    {
        //        sendFailResponse();
    }
}

////////////////////////////////////////////////////////////////////////////////
// I2c commands
////////////////////////////////////////////////////////////////////////////////

/*FUNCTION**********************************************************************
 *
 * Function Name : handleI2cEnterMode
 * Description   : handle i2c enter mode
 *
 *END**************************************************************************/
static void handleI2cEnterMode(void)
{
    if (s_mode != kBusPalI2cMode)
    {
        s_mode = kBusPalI2cMode;
    }

    write_bytes_to_host((uint8_t *)k_responseI2cMode, STRING_SIZE_NO_NULL(k_responseI2cMode));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleI2cBulkWrite
 * Description   : handle i2c bulk write
 *
 *END**************************************************************************/
static void handleI2cBulkWrite(uint8_t bytes)
{
    sendOKResponse();

    uint32_t i;
    // bytes value of 0 in the Bulk Transfer command means 1 byte
    for (i = 0; i < bytes + 1; i++)
    {
        wait_for_command_bytes(s_commandOffset, 1);
        s_commandOffset++;
        sendOKResponse();
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleI2cSetAddress
 * Description   : handle i2c set up address
 *
 *END**************************************************************************/
static void handleI2cSetAddress(void)
{
    uint8_t address;

    wait_for_command_bytes(s_commandOffset, sizeof(address));
    address = s_commandPtr[s_commandOffset];
    s_commandOffset += sizeof(address);

    configure_i2c_address(address);

    sendOKResponse();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleI2cSetSpeed
 * Description   : handle i2c set up speed
 *
 *END**************************************************************************/
static void handleI2cSetSpeed(void)
{
    uint32_t speed = 0;

    wait_for_command_bytes(s_commandOffset, sizeof(speed));
    speed = uint32_from_buffer(s_commandPtr + s_commandOffset);
    s_commandOffset += sizeof(speed);

    configure_i2c_speed(speed);

    sendOKResponse();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleI2cWriteThenRead
 * Description   : handle i2c write then read
 *
 *END**************************************************************************/
static void handleI2cWriteThenRead(void)
{
    uint16_t numBytesToWrite = 0;
    uint16_t numBytesToRead = 0;

    // Get the number of bytes to write
    wait_for_command_bytes(s_commandOffset, sizeof(numBytesToWrite));
    numBytesToWrite = uint16_from_buffer(s_commandPtr + s_commandOffset);
    s_commandOffset += sizeof(numBytesToWrite);

    // Get the number of bytes to read
    wait_for_command_bytes(s_commandOffset, sizeof(numBytesToRead));
    numBytesToRead = uint16_from_buffer(s_commandPtr + s_commandOffset);
    s_commandOffset += sizeof(numBytesToRead);

    // If there are bytes to write and we have enough buffer space for them
    // read the bytes that we need to write to Spi from the host
    if (numBytesToWrite && (numBytesToWrite < kBusPalMaxReadWriteSize))
    {
        wait_for_command_bytes(s_commandOffset, numBytesToWrite);
    }

    // if there are bytes to be written send these bytes to the target
    if (numBytesToWrite)
    {
        if (send_i2c_data(s_commandPtr + s_commandOffset, numBytesToWrite) != kStatus_Success)
        {
            sendFailResponse();
            return;
        }
        s_commandOffset += numBytesToWrite;
    }

    // If there are bytes to read and we have enough buffer space read
    // the bytes from the target
    if (numBytesToRead && (numBytesToRead < kBusPalMaxReadWriteSize))
    {
        if (receive_i2c_data(s_targetRxBuffer, numBytesToRead) != kStatus_Success)
        {
            sendFailResponse();
            return;
        }
    }

    sendOKResponse();

    // If everything went ok then send these bytes back to the host
    if (numBytesToRead)
    {
        write_bytes_to_host(s_targetRxBuffer, numBytesToRead);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : handleI2cModeCommand
 * Description   : handle i2c mode command
 *
 *END**************************************************************************/
static void handleI2cModeCommand(uint8_t command)
{
    if (command == kI2c_Exit)
    {
        handleResetMode();
    }
    else if (command == kI2c_WriteThenRead)
    {
        handleI2cWriteThenRead();
    }
    else if (command <= kI2c_Version)
    {
        handleI2cEnterMode();
    }
    else if (command == kI2c_StartBit)
    {
        sendFailResponse();
    }
    else if (command == kI2c_StopBit)
    {
        sendFailResponse();
    }
    else if (command == kI2c_ReadByte)
    {
        sendFailResponse();
    }
    else if (command == kI2c_AckBit)
    {
        sendFailResponse();
    }
    else if (command == kI2c_NackBit)
    {
        sendFailResponse();
    }
    else if (command == kI2c_BusSniff)
    {
        sendFailResponse();
    }
    else if (command == kI2c_SetAddress)
    {
        handleI2cSetAddress();
    }
    else if (command == kI2c_SetSpeed)
    {
        handleI2cSetSpeed();
    }
    else if ((command >= kI2c_BulkWrite) && (command <= (kI2c_BulkWrite | kI2c_BulkWrite_mask)))
    {
        handleI2cBulkWrite(command & kI2c_BulkWrite_mask);
    }
    else if ((command >= kI2c_ConfigurePeriph) && (command <= (kI2c_ConfigurePeriph | kI2c_ConfigurePeriph_mask)))
    {
        sendFailResponse();
    }
    else if ((command >= kI2c_PullUpSelect) && (command <= (kI2c_PullUpSelect | kI2c_PullUpSelect_mask)))
    {
        sendFailResponse();
    }
    else
    {
        sendFailResponse();
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

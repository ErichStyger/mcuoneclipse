/*
* Copyright (c) 2013 - 15, Freescale Semiconductor, Inc.
* All rights reserved
*
* Redistribution and use in source and binary forms, with or without modification,
*are permitted provided that the following conditions are met :
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and / or
*   other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
*   contributors may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*!
* @brief Device specific configuration file for Kinetis bootloader
*
* Provides a bootloader configuration structure and a global variable that
* contains
* the system bootloader configuration data.
*/

#include <stdint.h>

/*!
* @brief Defines the structure to set the Bootloader Configuration Area
*
* This type of variable is used to set the Bootloader Configuration Area
* of the chip.
*
* Warning: some configuration may not work on the devices that donot support 
* corresponding feature.
*/
typedef struct BootloaderConfiguration
{
    uint32_t tag; //!< [00:03] Magic number to verify bootloader configuration is
                  //! valid. Must be set to 'kcfg'.
    uint32_t crcStartAddress; //!< [04:07] Start address for application image CRC
                              //! check. If the bits are all set then Kinetis
                              //! bootloader by default will not perform any CRC 
                              //! check.
    uint32_t crcByteCount; //!< [08:0b] Byte count for application image CRC
                           //! check. If the bits are all set then Kinetis
                           //! bootloader by default will not prform any CRC check.
    uint32_t crcExpectedValue; //!< [0c:0f] Expected CRC value for application CRC
                               //! check. If the bits are all set then Kinetis
                               //! bootloader by default will not perform any CRC
                               //! check.
    uint8_t enabledPeripherals; //!< [10:10] Bitfield of peripherals to enable.
                                //! bit 0 - LPUART, bit 1 - I2C, bit 2 - SPI,
                                //! bit 3 - CAN, bit 4 - USB
                                //! Kinetis bootloader will enable the peripheral if
                                //! corresponding bit is set to 1.
    uint8_t i2cSlaveAddress; //!< [11:11] If not 0xFF, used as the 7-bit I2C slave
                             //! address. If 0xFF, defaults to 0x10
                             //! for I2C slave address.
    uint16_t peripheralDetectionTimeoutMs; //!< [12:13] Timeout in milliseconds
                                           //! for active peripheral detection. If
                                           //! 0xFFFF, defaults to 5 seconds.
    uint16_t usbVid; //!< [14:15] Sets the USB Vendor ID reported by the device
                     //! during enumeration. If 0xFFFF, it defaults to 0x15A2.
    uint16_t usbPid; //!< [16:17] Sets the USB Product ID reported by the device
                     //! during enumeration.
    uint32_t usbStringsPointer; //!< [18:1b] Sets the USB Strings reported by the
                                //! device during enumeration.
    uint8_t clockFlags; //!< [1c:1c] The flags in the clockFlags configuration
                        //! field are enabled if the corresponding bit is cleared (0).
                        //! bit 0 - HighSpeed Enable high speed mode (i.e., 48 MHz).
    uint8_t clockDivider; //!< [1d:1d] Inverted value of the divider to use for
                          //! core and bus clocks when in high speed mode.
    uint8_t bootFlags; //!< [1e:1e] If bit 0 is cleared, then Kinetis bootloader
                       //! will jump to either Quad SPI Flash or internal flash
                       //! image depending on FOPT BOOTSRC_SEL bits.
                       //! If the bit is set, then Kinetis bootloader will prepare
                       //! for host communication over serial peripherals.
    uint8_t pad0; //!< [1f:1f] Reserved, set to 0xFF
    uint32_t mmcauConfigPointer; //!< [20:23] A pointer to the MMCAU configuration
                                 //! structure in memory.
    uint32_t keyBlobPointer; //!< [24:27]Holds a pointer value to the key blob
                             //! array used to configure OTFAD
    uint8_t pad1; //!< [28:28] reserved
    uint8_t canConfig1; //!< [29:29] ClkSel[1], PropSeg[3], SpeedIndex[4]
    uint16_t canConfig2; //!< [2a:2b] Pdiv[8], Pseg1[3], Pseg2[3],  rjw[2]
    uint16_t canTxId; //!< [2c:2d] txId
    uint16_t canRxId; //!< [2e:2f] rxId
    uint32_t qspi_config_block_pointer; //!< [30:33] A pointer to the QSPI config
                                        //! block in internal flash array.
    uint32_t reserved[3]; //!<[34:3f] reserved
} bootloader_config_t;

/*
* Warning: To enable bootloader configuration, User still needs two extra steps :
*
*   Step1 : Enable BOOTLOADER_CONFIG.
*   Example : #define BOOTLOADER_CONFIG 1
*
*   Step2 : Add configuration of the section "BootloaderConfig" to your
*   linker configuration file.
*   Example(IAR) :
*       define symbol __application_startaddress = 0; // User-defined
*       define symbol m_bootloader_config_start = __application_startaddress + 0x3C0;
*       define symbol m_bootloader_config_end = __application_startaddress + 0x3FF;
*       define region m_bootloader_config_region = mem:[from m_bootloader_config_start to m_bootloader_config_end];
*       place in m_bootloader_config_region{ section BootloaderConfig };
*
*   Example(Keil) :
*       #define __application_startaddress = 0 // User-defined
*       #define m_bootloader_config_start      __application_startaddress + 0x3C0
*       #define m_bootloader_config_size       0x00000040
*
*       LR_m_bootloader_config m_bootloader_config_start m_bootloader_config_size{
*         ER_m_bootloader_config m_bootloader_config_start m_bootloader_config_size{ ; load address = execution address
*           * (BootloaderConfig)
*         }
*       }
*
*   Example(ARM - GCC) :
*       MEMORY
*       {
*           m_bootloader_config(RX) : ORIGIN = 0x000003C0, LENGTH = 0x00000040
*       }
*       .bootloader_config :
*       {
*           . = ALIGN(4);
*           KEEP(*(.BootloaderConfig)) // Bootloader Configuration Area (BCA)
*           . = ALIGN(4);
*       } > m_bootloader_config
*
*/

/* bits for enabledPeripherals */
#define ENABLE_PERIPHERAL_UART     (1<<0)
#define ENABLE_PERIPHERAL_I2C      (1<<1)
#define ENABLE_PERIPHERAL_SPI  	   (1<<2)
#define ENABLE_PERIPHERAL_CAN      (1<<3)
#define ENABLE_PERIPHERAL_USB_HID  (1<<4)
#define ENABLE_PERIPHERAL_USB_MSC  (1<<7)

#if 1 || BOOTLOADER_CONFIG
/* Bootlader configuration area */
#if defined(__IAR_SYSTEMS_ICC__)
/* Pragma to place the Bootloader Configuration Array on correct location
* defined in linker file. */
#pragma language = extended
#pragma location = "BootloaderConfig"
__root const bootloader_config_t BootloaderConfig @"BootloaderConfig" =
#elif defined(__GNUC__)
__attribute__((section(".BootloaderConfig"))) const bootloader_config_t BootloaderConfig =
#elif defined(__CC_ARM)
__attribute__((section("BootloaderConfig"))) const bootloader_config_t BootloaderConfig __attribute__((used)) =
#else
#error Unsupported compiler!
#endif
    {
        .tag = 0x6766636B, //!< Magic Number
        .crcStartAddress = 0xFFFFFFFF, //!< Disable CRC check
        .crcByteCount = 0xFFFFFFFF, //!< Disable CRC check
        .crcExpectedValue = 0xFFFFFFFF, //!< Disable CRC check
        .enabledPeripherals = ENABLE_PERIPHERAL_UART|ENABLE_PERIPHERAL_I2C|ENABLE_PERIPHERAL_SPI|ENABLE_PERIPHERAL_CAN|ENABLE_PERIPHERAL_USB_HID|ENABLE_PERIPHERAL_USB_MSC, //!< Enabled Peripheral: UART I2C SPI CAN USB-HID
        .i2cSlaveAddress = 0xFF, //!< Use default I2C address(0x10)
        .peripheralDetectionTimeoutMs = 2000, //!< Use user-defined timeout(ms)
        .usbVid = 0xFFFF, //!< Use default Vendor ID(0x15A2)
        .usbPid = 0xFFFF, //!< Use default Product ID(0x0073)
        .usbStringsPointer = 0xFFFFFFFF, //!< Use default USB String
        .clockFlags = 0xFF, //!< Disable High speed mode
        .clockDivider = 0xFF, //!< Use clock divider(0)
        .bootFlags = 0xFF, //!< Enable communication with host
        .mmcauConfigPointer = 0x00000000, //!< MMCAU configuration is available
        .keyBlobPointer = 0x00000000, //!< Key blob is available
        .canConfig1 = 0xF0, //!< Use user-defined canConfig1
        .canConfig2 = 0xFFFF, //!< Use default canConfig2
        .canTxId = 0x0000, //!< Use user-defined CAN TX ID
        .canRxId = 0x0000, //!< Use user-defined CAN RX ID
        .qspi_config_block_pointer = 0x00000000, //!< QSPI configuration is available
    };
#endif

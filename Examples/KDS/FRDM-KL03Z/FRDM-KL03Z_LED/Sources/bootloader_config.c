/* KBOOT ROM Bootloader configuration for FRDM-KL03Z Board */

#include <stdint.h>

#define ENABLE_BCA     (1)
  /*!< 1: define Bootloader Configuration Area mit magic number to use it from ROM bootloader; 0: use default setting (no BCA) */


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
} bootloader_config_t;


/* bits for enabledPeripherals */
#define ENABLE_PERIPHERAL_UART     (1<<0)
#define ENABLE_PERIPHERAL_I2C      (1<<1)
#define ENABLE_PERIPHERAL_SPI  	   (1<<2)
#define ENABLE_PERIPHERAL_CAN      (1<<3)
#define ENABLE_PERIPHERAL_USB_HID  (1<<4)
#define ENABLE_PERIPHERAL_USB_MSC  (1<<7)

/* Bootloader configuration area */
__attribute__((section(".BootloaderConfig"))) const bootloader_config_t BootloaderConfig =
    {
#if ENABLE_BCA
        .tag = 0x6766636B, //!< Magic Number
#else
		.tag = 0xFFFFFFFF, //!< No Magic Number
#endif
        .crcStartAddress = 0xFFFFFFFF, //!< Disable CRC check
        .crcByteCount = 0xFFFFFFFF, //!< Disable CRC check
        .crcExpectedValue = 0xFFFFFFFF, //!< Disable CRC check
        .enabledPeripherals = 0xFF /*0xE2*/, /*ENABLE_PERIPHERAL_I2C, *///ENABLE_PERIPHERAL_UART|ENABLE_PERIPHERAL_I2C|ENABLE_PERIPHERAL_SPI|ENABLE_PERIPHERAL_CAN|ENABLE_PERIPHERAL_USB_HID|ENABLE_PERIPHERAL_USB_MSC, //!< Enabled Peripheral: UART I2C SPI CAN USB-HID
        .i2cSlaveAddress = 0x10, //!< Use default I2C address(0x10)
        //.i2cSlaveAddress = 0xFF, //!< Use default I2C address(0x10)
        //.peripheralDetectionTimeoutMs = /*2000*/0xFFFF, //!< Use user-defined timeout(ms)
        .peripheralDetectionTimeoutMs = 5000, //!< Use user-defined timeout(ms)
        .usbVid = 0xFFFF, //!< Use default Vendor ID(0x15A2)
        .usbPid = 0xFFFF, //!< Use default Product ID(0x0073)
        .usbStringsPointer = 0xFFFFFFFF, //!< Use default USB String
        .clockFlags = 0xFE /*0xFE*/, //!< 0 bit cleared: Enable High speed mode
        //.clockFlags = 0xFF, //!< Disable High speed mode
        //.clockDivider = 0xFF, //!< Use clock divider(0)
		.clockDivider = 0xff /*0x1*//*0xFF*/, //!< Use clock divider(0)
    };

/* 16 bytes at address 0x400 */
__attribute__((used, section(".FlashConfig"))) const uint32_t FOPTConfig[4] = {
  0xFFFFFFFF,
  0xFFFFFFFF,
  0xFFFFFFFF,
 // 0xFFFF3DFE // boot from FLASH
  0xFFFFBDFE   // boot from ROM, means this will kick in the bootloader by default
};

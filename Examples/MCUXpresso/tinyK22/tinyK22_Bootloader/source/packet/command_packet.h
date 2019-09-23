/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if !defined(__COMMAND_PACKET_H__)
#define __COMMAND_PACKET_H__

#include "bootloader_common.h"

//! @addtogroup packet
//! @{

////////////////////////////////////////////////////////////////////////////////
// Declarations
////////////////////////////////////////////////////////////////////////////////

//! @brief Command/Data Packet constants.
enum _command_packet_constants
{
    kMinPacketBufferSize = 32,
#if BL_FEATURE_EXPAND_PACKET_SIZE
    kDefaultFramingPacketBufferSize = 1024,
#if BL_CONFIG_HS_USB_HID
    // Make sure that kDefaultUsbHidPacketBufferSize < 1018
    kDefaultUsbHidPacketBufferSize = 1016,
#else
    kDefaultUsbHidPacketBufferSize = 56,
#endif // BL_CONFIG_HS_USB_HID
#if defined(BL_EXPANDED_FRAMING_PACKET_SIZE)
    kMinFramingPacketBufferSize = BL_EXPANDED_FRAMING_PACKET_SIZE,
#else
    kMinFramingPacketBufferSize = kDefaultFramingPacketBufferSize,
#endif // defined(BL_EXPANDED_FRAMING_PACKET_SIZE)
#if defined(BL_EXPANDED_USB_HID_PACKET_SIZE)
    kMinUsbHidPacketBufferSize = BL_EXPANDED_USB_HID_PACKET_SIZE,
#else
    kMinUsbHidPacketBufferSize = kDefaultUsbHidPacketBufferSize,
#endif // defined(BL_EXPANDED_USB_HID_PACKET_SIZE)
#else  // !BL_FEATURE_EXPAND_PACKET_SIZE
    kMinFramingPacketBufferSize = kMinPacketBufferSize,
    kMinUsbHidPacketBufferSize = kMinPacketBufferSize,
#endif // BL_FEATURE_EXPAND_PACKET_SIZE
    kMaxHostPacketSize = 8192,
    kMaxBootloaderPacketSize = MAX(kMinFramingPacketBufferSize, kMinUsbHidPacketBufferSize),
    kDefaultMaxPacketSize = kMinPacketBufferSize,
    kMaxPropertyReturnValues =
        (kMinPacketBufferSize / sizeof(uint32_t)) - 2, //!< Max number of words a property can return
                                                       //! One word is header, one parameter reserved for status

    kMaxProgramOnceValues =
        (kMinPacketBufferSize / sizeof(uint32_t)) - 3, //!< Max number of words a program once command can write
    //! One word is header, two parameters reserved for index and byteCount
    kCommandTagCount = 12 //!< Number of non-response command tags
};

//! @brief Commands codes.
enum _command_tags
{
    kCommandTag_GenericResponse = 0xa0,
    kCommandTag_FlashEraseAll = 0x01,
    kCommandTag_FlashEraseRegion = 0x02,
    kCommandTag_ReadMemory = 0x03,
    kCommandTag_ReadMemoryResponse = 0xa3,
    kCommandTag_WriteMemory = 0x04,
    kCommandTag_FillMemory = 0x05,
    kCommandTag_FlashSecurityDisable = 0x06,
    kCommandTag_GetProperty = 0x07,
    kCommandTag_GetPropertyResponse = 0xa7,
    kCommandTag_ReceiveSbFile = 0x08,
    kCommandTag_Execute = 0x09,
    kCommandTag_Call = 0x0a,
    kCommandTag_Reset = 0x0b,
    kCommandTag_SetProperty = 0x0c,
    kCommandTag_FlashEraseAllUnsecure = 0x0d,
    kCommandTag_FlashProgramOnce = 0x0e,
    kCommandTag_FlashReadOnce = 0x0f,
    kCommandTag_FlashReadOnceResponse = 0xaf,
    kCommandTag_FlashReadResource = 0x10,
    kCommandTag_FlashReadResourceResponse = 0xb0,
    kCommandTag_ConfigureMemory = 0x11,
    kCommandTag_ReliableUpdate = 0x12,
    kCommandTag_GenerateKeyBlob = 0x13,
    kCommandTag_GenerateKeyBlobResponse = 0xb3,
    kCommandTag_KeyProvisioning = 0x15,
    kCommandTag_KeyProvisioningResponse = 0xb5,

    kCommandTag_ConfigureI2c = 0xc1, //! Reserved command tag for Bus Pal
    kCommandTag_ConfigureSpi = 0xc2, //! Reserved command tag for Bus Pal
    kCommandTag_ConfigureCan = 0xc3, //! Reserved command tag for Bus Pal

    kFirstCommandTag = kCommandTag_FlashEraseAll,

    //! Maximum linearly incrementing command tag value, excluding the response commands and bus pal commands.
    kLastCommandTag = kCommandTag_KeyProvisioning,

    kResponseCommandHighNibbleMask =
        0xa0 //!< Mask for the high nibble of a command tag that identifies it as a response command.
};

//! @brief Command packet flags.
enum _command_packet_flags
{
    kCommandFlag_None = 0,
    kCommandFlag_HasDataPhase = 1
};

enum _command_key_provisioning_operation
{
    kKeyProvisioning_Operation_Enroll = 0,
    kKeyProvisioning_Operation_SetUserKey = 1,
    kKeyProvisioning_Operation_SetIntrinsicKey = 2,
    kKeyProvisioning_Operation_WriteNonVolatile = 3,
    kKeyProvisioning_Operation_ReadNonVolatile = 4,
    kKeyProvisioning_Operation_WriteKeyStore = 5,
    kKeyProvisioning_Operation_ReadKeyStore = 6,
};

enum _command_dataPhase_option_direction
{
    kCmd_DataPhase_Option_Consumer = 0,
    kCmd_DataPhase_Option_Producer = 1,
    kCmd_DataPhase_Option_Skip = 2,
};

//! @brief Command packet format.
typedef struct CommandPacket
{
    uint8_t commandTag;     //!< A command tag.
    uint8_t flags;          //!< Combination of packet flags.
    uint8_t reserved;       //!< Reserved, helpful for alignment, set to zero.
    uint8_t parameterCount; //!< Number of parameters that follow in buffer.
} command_packet_t;

//! @name Command Packet formats
//@{

//! @brief FlashEraseAll packet format.
typedef struct FlashEraseAllPacket
{
    command_packet_t commandPacket; //!< header
    uint32_t memoryId;              //!< Paremeter 0: Flash memory identifiers.
} flash_erase_all_packet_t;

//! @brief FlashEraseRegion packet format.
typedef struct FlashEraseRegionPacket
{
    command_packet_t commandPacket; //!< header
    uint32_t startAddress;          //!< Paremeter 0: start address.
    uint32_t byteCount;             //!< Parameter 1: number of bytes.
    uint32_t memoryId;              //!< Parameter 2: ID of the Memory Device to erase.
} flash_erase_region_packet_t;

//! @brief GetProperty packet format.
typedef struct GetPropertyPacket
{
    command_packet_t commandPacket; //!< header
    uint32_t propertyTag;           //!< Parameter 0: requested property tag.
    uint32_t memoryId;              //!< Parameter 1: requested property for certain external memory
} get_property_packet_t;

//! @brief SetProperty packet format.
typedef struct SetPropertyPacket
{
    command_packet_t commandPacket; //!< header
    uint32_t propertyTag;           //!< Paremeter 0: property tag.
    uint32_t propertyValue;         //!< Parameter 1: value to set.
} set_property_packet_t;

//! @brief ReceiveSbFile packet format.
typedef struct ReceiveSbFilePacket
{
    command_packet_t commandPacket; //!< header
    uint32_t byteCount;             //!< Parameter 0: Number of bytes to receive.
} receive_sb_file_packet_t;

//! @brief WriteMemory packet format.
typedef struct WriteMemoryPacket
{
    command_packet_t commandPacket; //!< header
    uint32_t startAddress;          //!< Paremeter 0: Start address of memory to write to.
    uint32_t byteCount;             //!< Parameter 1: Number of bytes to write.
    uint32_t memoryId;              //!< Parameter 2: ID of the Memory Device to write to.
} write_memory_packet_t;

//! @brief GenerateKeyBlob packet format.
typedef struct GenerateKeyBlobPacket
{
    command_packet_t commandPacket; //!< header
    uint32_t keyAddress;            //!< Paremeter 0: Start address of key data.
    uint32_t keyLength;             //!< Parameter 1: Key length in byte.
    uint32_t keyDataPhase;          //!< phase 0, send key, phase 1, receive key blob
} generate_key_blob_packet_t;

//! @brief ReadMemory packet format.
typedef struct ReadMemoryPacket
{
    command_packet_t commandPacket; //!< header
    uint32_t startAddress;          //!< Paremeter 0: Start address of memory to read from.
    uint32_t byteCount;             //!< Parameter 1: Number of bytes to read.
    uint32_t memoryId;              //!< Parameter 2: ID of the Memory Device to read from.
} read_memory_packet_t;

//! @brief FillMemory packet format.
typedef struct FillMemoryPacket
{
    command_packet_t commandPacket; //!< header
    uint32_t startAddress;          //!< Paremeter 0: start address.
    uint32_t byteCount;             //!< Parameter 1: number of bytes.
    uint32_t patternWord;           //!< Parameter 1: pattern word.
} fill_memory_packet_t;

//! @brief Execute/Call command function pointer definition.
typedef status_t (*call_function_t)(uint32_t);

//! @brief Execute/Call packet format.
typedef struct ExecuteCallPacket
{
    command_packet_t commandPacket; //!< header
    uint32_t callAddress;           //!< Paremeter 0: function address.
    uint32_t argumentWord;          //!< Parameter 1: argument.
    uint32_t stackpointer;          //!< Parameter 2: stack pointer
} execute_call_packet_t;

//! @brief FlashSecurityDisable packet format.
typedef struct FlashSecurityDisablePacket
{
    command_packet_t commandPacket; //!< header
    uint32_t keyLow;                //!< Paremeter 0: key bytes 0-3.
    uint32_t keyHigh;               //!< Parameter 1: key bytes 4-7.
} flash_security_disable_packet_t;

//! @brief FlashProgramOnce packet format
typedef struct ProgramOncePacket
{
    command_packet_t commandPacket;       //!< header
    uint32_t index;                       //!< Parameter 0: index of pragram once field
    uint32_t byteCount;                   //!< Parameter 1: number of bytes
    uint32_t data[kMaxProgramOnceValues]; //!< Parameter 2: data to be programmed
} flash_program_once_packet_t;

//! @brief FlashReadOnce packet format
typedef struct ReadOncePacket
{
    command_packet_t commandPacket; //!< header
    uint32_t index;                 //!< Parameter 0: index of pragram once field to be read
    uint32_t byteCount;             //!< Parameter 1: number of bytes
} flash_read_once_packet_t;

//! @brief FlashReadResource packet format
typedef struct FlashReadResourcePacket
{
    command_packet_t commandPacket; //!< header
    uint32_t startAddress;          //!< Parameter 0: start address
    uint32_t byteCount;             //!< Parameter 1: number of bytes
    uint32_t option;                //!< Parameter 2: option for  flash read resource command
} flash_read_resource_packet_t;

//! @brief ConfigureMemory packet format
typedef struct ConfigureMemoryPacket
{
    command_packet_t commandPacket; //!< header
    uint32_t flashMemId;            //!< Parameter 0: ID of the Memory Device to configure.
    uint32_t configBlockAddress;    //!< Parameter 1: address of config block to use
} configure_memory_packet_t;

//! @brief ReliableUpdate packet format
typedef struct ReliableUpdatePacket
{
    command_packet_t commandPacket; //!< header
    uint32_t address;               //!< Parameter 0: For software implementation , this is backup app start address;
                                    //!< Parameter 0: For hardware implementation , this is swap indicator address;
} reliable_update_packet_t;

//! @brief KeyProvisioning packet format
typedef struct KeyProvisioningPacket
{
    command_packet_t commandPacket; //!< header
    uint32_t operation;             //!< Key operation, refer to the definition of _command_key_provisioning_operation.
    uint32_t type;                  //!< Key type.
    uint32_t size;                  //!< Key size.
} key_provisioning_packet_t;

//@}

//! @name Response bus-pal command formats
//@{

//! @brief ConfigureI2c packet format
typedef struct ConfigureI2cPacket
{
    command_packet_t commandPacket; //!< header
    uint32_t address;               //!< Parameter 0: address
    uint32_t speed;                 //!< Parameter 1: speed
} configure_i2c_packet_t;

//! @brief ConfigureSpi packet format
typedef struct ConfigureSpiPacket
{
    command_packet_t commandPacket; //!< header
    uint32_t speedKhz;              //!< Parameter 0: spped Khz
    uint32_t polarity;              //!< Parameter 1: polarity
    uint32_t phase;                 //!< Parameter 2: phase
    uint32_t direction;             //!< Parameter 3: directionpolarity
} configure_spi_packet_t;

//! @brief ConfigureCan packet format
typedef struct ConfigureCanPacket
{
    command_packet_t commandPacket; //!< header
    uint32_t speed;                 //!< Parameter 0: spped index
    uint32_t txid;                  //!< Parameter 1: txid
    uint32_t rxid;                  //!< Parameter 2: rxid
} configure_can_packet_t;

//@}

//! @name Response Packet formats
//@{

//! @brief Generic response packet format.
typedef struct GenericResponsePacket
{
    command_packet_t commandPacket; //!< header
    uint32_t status;                //!< parameter 0
    uint32_t commandTag;            //!< parameter 1
} generic_response_packet_t;

//! @brief Get Property response packet format.
typedef struct GetPropertyResponsePacket
{
    command_packet_t commandPacket;                   //!< header
    uint32_t status;                                  //!< parameter 0
    uint32_t propertyValue[kMaxPropertyReturnValues]; //!< up to 6 other parameters
} get_property_response_packet_t;

//! @brief Generate Key Blob response packet format.
typedef struct GenerateKeyBlobResponsePacket
{
    command_packet_t commandPacket; //!< header
    uint32_t status;                //!< parameter 0
    uint32_t dataByteCount;         //!< parameter 1
} generate_key_blob_response_packet_t;

//! @brief Read Memory response packet format.
typedef struct ReadMemoryResponsePacket
{
    command_packet_t commandPacket; //!< header
    uint32_t status;                //!< parameter 0
    uint32_t dataByteCount;         //!< parameter 1
} read_memory_response_packet_t;

//! @brief Flash Read Once response packet format.
typedef struct FlashReadOnceResponsePacket
{
    command_packet_t commandPacket;       //!< header
    uint32_t status;                      //!< parameter 0
    uint32_t byteCount;                   //!< parameter 1
    uint32_t data[kMaxProgramOnceValues]; //!< parameter 2
} flash_read_once_response_packet_t;

//! @brief Flash Read Resource response packet format.
typedef struct FlashReadResourceResponsePacket
{
    command_packet_t commandPacket; //!< header
    uint32_t status;                //!< parameter 0
    uint32_t dataByteCount;         //!< parameter 1
} flash_read_resource_response_packet_t;

//! @brief Key Provisioning response packet format.
typedef struct KeyProvisioningResponsePacket
{
    command_packet_t commandPacket; //!< header
    uint32_t status;                //!< parameter 0
    uint32_t keyByteCount;          //!< parameter 1
} key_provisioning_response_packet_t;
//@}

//! @}

#endif // __COMMAND_PACKET_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

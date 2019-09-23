/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _packet_h
#define _packet_h

#include "bootloader_common.h"
#include "bootloader/bl_peripheral.h"
#include "property/property.h"

//! @addtogroup packet
//! @{

////////////////////////////////////////////////////////////////////////////////
// Declarations
////////////////////////////////////////////////////////////////////////////////

//! @brief Version constants for serial framing protocol.
//! @note Recalculate crc16 in k_PingResponse if these values change.
enum _serial_protocol_version_constants
{
    kSerialProtocol_Version_Name = 'P',
    kSerialProtocol_Version_Major = 1,
    kSerialProtocol_Version_Minor = 2,
    kSerialProtocol_Version_Bugfix = 0
};

//! @brief Serial framing packet constants.
enum _framing_packet_constants
{
    kFramingPacketStartByte = 0x5a,
    kFramingPacketType_Ack = 0xa1,
    kFramingPacketType_Nak = 0xa2,
    kFramingPacketType_AckAbort = 0xa3,
    kFramingPacketType_Command = 0xa4,
    kFramingPacketType_Data = 0xa5,
    kFramingPacketType_Ping = 0xa6,
    kFramingPacketType_PingResponse = 0xa7
};

//! @brief Timeout and other constants.
enum _timing_constants
{
    kHostMaxStartByteReadCount = 2,
    kDefaultByteReadTimeoutMs = 10, //!< Default value for receiving 1 byte timeout
    kCallbackBufferSize = 64        //!< Size for callback buffer, Must be power of 2 for easy wrap
};

//! @brief Incoming data buffer allocation size.
enum _serial_packet_constants
{
    kIncomingPacketBufferSize = kMinFramingPacketBufferSize,
    kOutgoingPacketBufferSize = kMinFramingPacketBufferSize
};

//! @brief Packet state machine modes.
enum _serial_packet_mode
{
    kSerialModeCmd,
    kSerialModeAck,
    kSerialModeIdle
};

//! @brief Serial framing header.
typedef struct FramingHeader
{
    uint8_t startByte;  //!< #kFramingPacketStartByte
    uint8_t packetType; //!< Framing packet type
} framing_header_t;

//! @brief Serial framing sync packet.
typedef struct FramingSyncPacket
{
    framing_header_t header; //!< Framing packet header
} framing_sync_packet_t;

//! @brief Serial framing data packet.
#pragma pack(1)
typedef struct FramingDataPacket
{
    framing_header_t header; //!< Framing packet header
    uint16_t length;         //!< Number of data bytes that follow
    uint16_t crc16;          //!< CRC-16 of data packet header and data
} framing_data_packet_t;
#pragma pack()

//! @brief Framing packet with data area.
typedef struct SerialFramingPacket
{
    framing_data_packet_t dataPacket;        //!< Packet header.
    uint8_t data[kOutgoingPacketBufferSize]; //!< Payload.
} serial_framing_packet_t;

//! @brief Format of global context data.
typedef struct SerialData
{
    uint8_t data[kIncomingPacketBufferSize]; //!< Buffer for incomming packet data payload, must be uint32_t aligned.
    uint8_t callbackBuffer[kCallbackBufferSize]; //!< Buffer for incoming data from the byte callback
    serial_framing_packet_t framingPacket;       //!< Buffer for outgoing packet.
    volatile uint32_t writeOffset;               //!< The offset into the buffer that the ISR will queue data into
    uint32_t readOffset;                         //!< The offset into the buffer that the app has read out
    bool isAckNeeded;                            //!< True if need to send ACK to previously received packet
    bool isBackToBackWrite;                      //!< True if executing back-to-back write
    bool isAckAbortNeeded;                       //!< True if next ACK should be ACK Abort
} serial_data_t;

//! @brief Serial ping response format.
//!
//! This is the format of the response to a Ping packet.
typedef struct PingResponse
{
    standard_version_t version; //!< Serial framing protocol version
    uint16_t options;           //!< Serial framing protocol options bitfield
    uint16_t crc16;             //!< CRC-16 of other fields
} ping_response_t;

////////////////////////////////////////////////////////////////////////////////
// Externs
////////////////////////////////////////////////////////////////////////////////

extern const peripheral_packet_interface_t g_framingPacketInterface;

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

//! @brief Initialize component.
status_t serial_packet_init(const peripheral_descriptor_t *self);

//! @brief Read packet using serial framing.
//!
//! On return, caller must call flow control method to send AckContinue or AckWait followed by Continue.
status_t serial_packet_read(const peripheral_descriptor_t *self,
                            uint8_t **packet,
                            uint32_t *packetLength,
                            packet_type_t packetType);

//! @brief Write packet using serial framing.
status_t serial_packet_write(const peripheral_descriptor_t *self,
                             const uint8_t *packet,
                             uint32_t byteCount,
                             packet_type_t packetType);

//! @brief Abort data phase.
//!
//! Respond to next host data packet with AckAbort instead of Ack
//! (i.e. receiver data phase abort).
void serial_packet_abort(const peripheral_descriptor_t *self);

//! @brief Finalize.
status_t serial_packet_finalize(const peripheral_descriptor_t *self);

//! @brief Get max packet size.
uint32_t serial_packet_get_max_packet_size(const peripheral_descriptor_t *self);

//! @brief Send a sync packet of the specified type.
status_t serial_packet_send_sync(uint8_t framingPacketType);

//! @brief Send a ping message back in response to a ping.
status_t serial_send_ping_response(const peripheral_descriptor_t *peripheral);

//! @brief Queues a byte received by the active peripheral
void serial_packet_queue_byte(uint8_t byte);

#if defined(__cplusplus)
}
#endif // __cplusplus

//! @}

#endif // _packet_h
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

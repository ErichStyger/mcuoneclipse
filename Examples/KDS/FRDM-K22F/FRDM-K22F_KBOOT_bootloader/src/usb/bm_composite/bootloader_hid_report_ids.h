/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
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
#if !defined(__BOOTLOADER_HID_REPORT_IDS_H__)
#define __BOOTLOADER_HID_REPORT_IDS_H__

#include "packet/command_packet.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Report IDs to use for the bootloader.
enum _hid_report_ids
{
    kBootloaderReportID_CommandOut = 1,
    kBootloaderReportID_DataOut = 2,
    kBootloaderReportID_CommandIn = 3,
    kBootloaderReportID_DataIn = 4
};

//! @brief Structure of a bootloader HID header.
typedef struct _bl_hid_header
{
    uint8_t reportID; //!< The report ID.
    uint8_t _padding; //!< Pad byte necessary so that the length is 2-byte aligned and the data is 4-byte aligned. Set
    //! to zero.
    uint8_t packetLengthLsb; //!< Low byte of the packet length in bytes.
    uint8_t packetLengthMsb; //!< High byte of the packet length in bytes.
} bl_hid_header_t;

//! @brief Structure of a bootloader HID report.
typedef struct _bl_hid_report
{
    bl_hid_header_t header;               //!< Header of the report.
    uint8_t packet[kMinPacketBufferSize]; //!< The packet data that is transferred in the report.
} bl_hid_report_t;

#endif // __BOOTLOADER_HID_REPORT_IDS_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

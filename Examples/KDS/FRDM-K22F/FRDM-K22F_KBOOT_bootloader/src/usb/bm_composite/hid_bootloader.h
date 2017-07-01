/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#ifndef __USB_HID_MOUSE_H__
#define __USB_HID_MOUSE_H__ 1

#include "utilities/fsl_rtos_abstraction.h"
#include "bootloader_hid_report_ids.h"

#define USB_DEVICE_INTERRUPT_PRIORITY (4)

//! @brief Request parameters.
enum
{
    kAppRequestParam_IdleRate = 0,
    kAppRequestParam_Protocol,
    kAppRequestParamCount
};

//! @brief State information for the USB HID packetizer.
typedef struct _usb_hid_packetizer_info
{
    bool didReceiveFirstReport;        //!< Whether the first report has been received.
    bool didReceiveDataPhaseAbort;     //!< Whether we received a data phase abort request.
    bool isReceiveDataRequestRequired; //!< Whether an interrupt out pipe receive data request is required.
    uint8_t appRequestParams[kAppRequestParamCount]; //!< Storage for request parameter values.
    sync_object_t receiveSync;                       //!< Sync object used for reading packets.
    sync_object_t sendSync;                          //!< Sync object used for sending packets.
    uint32_t reportSize; //!< The size in bytes of a received report. May be greater than the packet contained within
    //! the report plus the header, as the host can send up to the max report size bytes.
    bl_hid_report_t report; //!< Buffer used to hold HID reports for sending and receiving.
} usb_hid_packetizer_info_t;

typedef struct _usb_hid_generic_struct
{
    usb_device_handle device_handle;
    class_handle_t hid_handle;
    //    uint32_t                  buffer[2][USB_HID_GENERIC_IN_BUFFER_LENGTH>>2];
    //    uint8_t                   buffer_index;
    usb_hid_packetizer_info_t hid_packet;
    uint8_t idle_rate;
    uint8_t speed;
    uint8_t attach;
    uint8_t current_configuration;
    uint8_t current_interface_alternate_setting[USB_HID_GENERIC_INTERFACE_COUNT];
} usb_hid_generic_struct_t;

#endif

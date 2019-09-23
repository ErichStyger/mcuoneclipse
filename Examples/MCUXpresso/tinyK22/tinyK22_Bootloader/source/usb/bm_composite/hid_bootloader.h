/*
 * Copyright (c) 2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * 
 * SPDX-License-Identifier: BSD-3-Clause
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

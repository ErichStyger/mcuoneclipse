/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
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

#ifndef __USB_DESCRIPTOR_H__
#define __USB_DESCRIPTOR_H__ 1

#include "bootloader_common.h"
#include "usb_device_config.h"
#include "usb.h"
#include "usb_device.h"

#include "usb_device_class.h"
#include "usb_device_hid.h"
#include "usb_device_msc.h"

#include "usb_descriptor.h"

#define USB_BCD_VERSION (0x0200)

/*******************************************************************************
 * For generic HID
 *******************************************************************************/

/* usb descritpor length */
#define USB_DEVICE_DESCRIPTOR_LENGTH (18)

#if (USB_DEVICE_CONFIG_HID == 0) && (USB_DEVICE_CONFIG_MSC == 1)
#define USB_CONFIGURE_DESCRIPTOR_LENGTH (32) // 64, HID_only = 41, MSC_ONLY = 32
#elif(USB_DEVICE_CONFIG_HID == 1) && (USB_DEVICE_CONFIG_MSC == 0)
#define USB_CONFIGURE_DESCRIPTOR_LENGTH (41) // 64, HID_only = 41, MSC_ONLY = 32
#elif(USB_DEVICE_CONFIG_HID == 1) && (USB_DEVICE_CONFIG_MSC == 1)
#define USB_CONFIGURE_DESCRIPTOR_LENGTH (64) // 64, HID_only = 41, MSC_ONLY = 32
#else
#define USB_CONFIGURE_DESCRIPTOR_LENGTH (41) // 64, HID_only = 41, MSC_ONLY = 32
#endif

#define USB_HID_REPORT_DESC_SIZE (76)
#define USB_HID_GENERIC_DESCRIPTOR_LENGTH (32)
#define USB_CONFIGURE_ONLY_DESCRIPTOR_LENGTH (9)
#define USB_INTERFACE_DESCRIPTOR_LENGTH (9)
#define USB_HID_DESCRIPTOR_LENGTH (9)
#define USB_ENDPOINT_DESCRIPTOR_LENGTH (7)
#define USB_MSC_DISK_REPORT_DESCRIPTOR_LENGTH (63)
#define USB_IAD_DESC_SIZE (8)

#define USB_CONFIGURE_COUNT (1)
#define USB_STRING_COUNT (4)
#define USB_LANGUAGE_COUNT (1)

#if (USB_DEVICE_CONFIG_HID == 1) && (USB_DEVICE_CONFIG_MSC == 1)
// HID + MSC composite device
#define USB_HID_CONFIG_INDEX (USB_CONFIGURE_ONLY_DESCRIPTOR_LENGTH)
#define USB_MSC_CONFIG_INDEX                                                                       \
    (USB_HID_CONFIG_INDEX + 2 * USB_ENDPOINT_DESCRIPTOR_LENGTH + USB_INTERFACE_DESCRIPTOR_LENGTH + \
     USB_HID_DESCRIPTOR_LENGTH)
#elif(USB_DEVICE_CONFIG_HID == 1) && (USB_DEVICE_CONFIG_MSC == 0)
// HID-Only device
#define USB_HID_CONFIG_INDEX (USB_CONFIGURE_ONLY_DESCRIPTOR_LENGTH)
#define USB_MSC_CONFIG_INDEX (0)
#elif(USB_DEVICE_CONFIG_HID == 0) && (USB_DEVICE_CONFIG_MSC == 1)
// MSC-only device
#define USB_HID_CONFIG_INDEX (0)
#define USB_MSC_CONFIG_INDEX (USB_CONFIGURE_ONLY_DESCRIPTOR_LENGTH)
#else
// No USB
#define USB_HID_CONFIG_INDEX (USB_CONFIGURE_ONLY_DESCRIPTOR_LENGTH)
#define USB_MSC_CONFIG_INDEX                                                                       \
    (USB_HID_CONFIG_INDEX + 2 * USB_ENDPOINT_DESCRIPTOR_LENGTH + USB_INTERFACE_DESCRIPTOR_LENGTH + \
     USB_HID_DESCRIPTOR_LENGTH)
#endif

#define HS_BULK_IN_PACKET_SIZE (512)
#define HS_BULK_OUT_PACKET_SIZE (512)
#define FS_BULK_IN_PACKET_SIZE (64)
#define FS_BULK_OUT_PACKET_SIZE (64)

// MSC
#define USB_MSC_CLASS (0x08)
/* scsi command set */
#define USB_MSC_SUBCLASS (0x06)
/* bulk only transport protocol */
#define USB_MSC_PROTOCOL (0x50)

#define USB_MSC_CONFIGURE_INDEX (1)
#define USB_MSC_ENDPOINT_COUNT (2)
#define USB_MSC_BULK_IN_ENDPOINT (3)
#define USB_MSC_BULK_OUT_ENDPOINT (4)
#define USB_MSC_INTERFACE_COUNT (1)

#if (USB_DEVICE_CONFIG_HID == 1) && (USB_DEVICE_CONFIG_MSC == 1)
#define USB_HID_GENERIC_INTERFACE_INDEX (0)
#define USB_MSC_INTERFACE_INDEX (1)
#else
#define USB_HID_GENERIC_INTERFACE_INDEX (0)
#define USB_MSC_INTERFACE_INDEX (0)
#endif

// HID
#define USB_HID_GENERIC_CONFIGURE_INDEX (1)
#define USB_HID_GENERIC_INTERFACE_COUNT (1)

#define USB_HID_GENERIC_IN_BUFFER_LENGTH (8)
#define USB_HID_GENERIC_OUT_BUFFER_LENGTH (8)
#define USB_HID_GENERIC_ENDPOINT_COUNT (2)
#define USB_HID_GENERIC_ENDPOINT_IN (1)
#define USB_HID_GENERIC_ENDPOINT_OUT (2)

#define USB_HID_GENERIC_CLASS (0x03)
#define USB_HID_GENERIC_SUBCLASS (0x00)
#define USB_HID_GENERIC_PROTOCOL (0x00)

#define HS_HID_GENERIC_INTERRUPT_OUT_PACKET_SIZE (64)
#define FS_HID_GENERIC_INTERRUPT_OUT_PACKET_SIZE (64)
#define HS_HID_GENERIC_INTERRUPT_OUT_INTERVAL (0x04) /* 2^(4-1) = 1ms */
#define FS_HID_GENERIC_INTERRUPT_OUT_INTERVAL (0x01)

#define HS_HID_GENERIC_INTERRUPT_IN_PACKET_SIZE (64)
#define FS_HID_GENERIC_INTERRUPT_IN_PACKET_SIZE (64)
#define HS_HID_GENERIC_INTERRUPT_IN_INTERVAL (0x04) /* 2^(4-1) = 1ms */
#define FS_HID_GENERIC_INTERRUPT_IN_INTERVAL (0x01)

#if (USB_DEVICE_CONFIG_HID == 1) && (USB_DEVICE_CONFIG_MSC == 1)
#define USB_COMPOSITE_INTERFACE_COUNT (USB_HID_GENERIC_INTERFACE_COUNT + USB_MSC_INTERFACE_COUNT)
#elif(USB_DEVICE_CONFIG_HID == 1) && (USB_DEVICE_CONFIG_MSC == 0)
#define USB_COMPOSITE_INTERFACE_COUNT (USB_HID_GENERIC_INTERFACE_COUNT)
#elif(USB_DEVICE_CONFIG_HID == 0) && (USB_DEVICE_CONFIG_MSC == 1)
#define USB_COMPOSITE_INTERFACE_COUNT (USB_MSC_INTERFACE_COUNT)
#else
#define USB_COMPOSITE_INTERFACE_COUNT (USB_HID_GENERIC_INTERFACE_COUNT)
#endif

#define USB_COMPOSITE_CONFIGURE_INDEX (1)

#define USB_STRING_DESCRIPTOR_HEADER_LENGTH (0x02)
#define USB_STRING_DESCRIPTOR_0_LENGTH (0x02)
#define USB_STRING_DESCRIPTOR_1_LENGTH (56)
#define USB_STRING_DESCRIPTOR_2_LENGTH (40)
#if ((USB_DEVICE_CONFIG_MSC > 0U) && (USB_DEVICE_CONFIG_HID > 0U)) // MSC + HID
#define USB_STRING_DESCRIPTOR_3_LENGTH (60)
#elif((USB_DEVICE_CONFIG_MSC == 0U) && (USB_DEVICE_CONFIG_HID > 0U)) // Only HID
#define USB_STRING_DESCRIPTOR_3_LENGTH (44)
#elif((USB_DEVICE_CONFIG_MSC > 0U) && (USB_DEVICE_CONFIG_HID == 0U)) // Only MSC
#define USB_STRING_DESCRIPTOR_3_LENGTH (28)
#else
#define USB_STRING_DESCRIPTOR_3_LENGTH (2)
#endif
#define USB_STRING_DESCRIPTOR_ERROR_LENGTH (32)

#define USB_DEVICE_CLASS (0x00)
#define USB_DEVICE_SUBCLASS (0x00)
#define USB_DEVICE_PROTOCOL (0x00)

#define USB_CONFIGURE_DRAWN (0x32)

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
enum _usb_descriptor_index
{
    kUsbDescriptorIndex_VidLow = 8,
    kUsbDescriptorIndex_VidHigh = 9,
    kUsbDescriptorIndex_PidLow = 10,
    kUsbDescriptorIndex_PidHigh = 11
};

typedef struct _usb_hid_config_descriptor
{
    usb_descriptor_interface_t interface;   /* Interface descriptor */
    usb_descriptor_interface_t hid_report;  /* Interface descriptor */
    usb_descriptor_endpoint_t endpoint_in;  /* Endpoint descriptor */
    usb_descriptor_endpoint_t endpoint_out; /* Endpoint descriptor */
} usb_hid_config_descriptor_t;

typedef struct _usb_msc_config_descriptor
{
    usb_descriptor_interface_t interface;   /* Interface descriptor */
    usb_descriptor_endpoint_t endpoint_in;  /* Endpoint descriptor */
    usb_descriptor_endpoint_t endpoint_out; /* Endpoint descriptor */
} usb_msc_config_descriptor_t;

extern usb_device_class_struct_t g_hid_generic_class;
extern usb_device_class_struct_t g_msc_class;

/* Configure the device according to the USB speed. */
extern usb_status_t usb_device_set_speed(usb_device_handle handle, uint8_t speed);

/* Get device descriptor request */
usb_status_t usb_device_get_device_descriptor(usb_device_handle handle,
                                              usb_device_get_device_descriptor_struct_t *device_descriptor);

/* Get device configuration descriptor request */
usb_status_t usb_device_get_configuration_descriptor(
    usb_device_handle handle, usb_device_get_configuration_descriptor_struct_t *configuration_descriptor);

/* Get device string descriptor request */
usb_status_t usb_device_get_string_descriptor(usb_device_handle handle,
                                              usb_device_get_string_descriptor_struct_t *string_descriptor);

/* Get hid descriptor request */
usb_status_t usb_device_get_hid_descriptor(usb_device_handle handle,
                                           usb_device_get_hid_descriptor_struct_t *hid_descriptor);

/* Get hid report descriptor request */
usb_status_t usb_device_get_hid_report_descriptor(usb_device_handle handle,
                                                  usb_device_get_hid_report_descriptor_struct_t *hid_report_descriptor);

/* Get hid physical descriptor request */
usb_status_t usb_device_get_hid_physical_descriptor(
    usb_device_handle handle, usb_device_get_hid_physical_descriptor_struct_t *hid_physical_descriptor);

extern uint8_t g_device_descriptor[];
extern usb_language_list_t g_language_list;

extern usb_language_list_t *g_language_ptr;

#endif /* __USB_DESCRIPTOR_H__ */

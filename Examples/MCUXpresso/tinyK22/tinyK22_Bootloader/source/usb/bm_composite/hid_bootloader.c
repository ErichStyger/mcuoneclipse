/*
 * Copyright (c) 2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "usb_device_config.h"
#include "usb.h"
#include "usb_device.h"

#include "usb_device_class.h"
#include "usb_device_hid.h"
#include "usb_device_ch9.h"
#include "usb_descriptor.h"
#include "hid_bootloader.h"

#include "fsl_device_registers.h"
#include "bootloader_hid_report_ids.h"
#include "utilities/fsl_rtos_abstraction.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "composite.h"

#if (BL_CONFIG_USB_HID || BL_CONFIG_HS_USB_HID)

/*******************************************************************************
 * Variables
 ******************************************************************************/
extern usb_device_endpoint_struct_t g_hid_generic_endpoints[];
static usb_device_composite_struct_t *g_device_composite;

/* The hid class callback */
usb_status_t usb_device_hid_generic_callback(class_handle_t handle, uint32_t event, void *param)
{
    usb_status_t error = kStatus_USB_Error;

    usb_device_hid_report_struct_t *hid_report_param;

    hid_report_param = (usb_device_hid_report_struct_t *)param;

    switch (event)
    {
        case kUSB_DeviceHidEventSendResponse:
            /*!< Send data completed */
            if ((hid_report_param->reportLength == 0xFFFFFFFF) || (hid_report_param->reportLength == 0x0))
            {
                return kStatus_USB_Success;
            }
            if ((g_device_composite->hid_generic.hid_packet.sendSync > 0) &&
                (g_device_composite->hid_generic.attach == 1))
            // Protect against extra complete due to data abort.
            {
                // Signal that write has completed.
                sync_signal(&g_device_composite->hid_generic.hid_packet.sendSync);
            }
            error = kStatus_USB_Success;

            break;
        case kUSB_DeviceHidEventRecvResponse:
            /*!< Data received */
            // Save the report size.
            if ((hid_report_param->reportLength == 0xFFFFFFFF) || (hid_report_param->reportLength == 0x0))
            {
                return kStatus_USB_Success;
            }
            g_device_composite->hid_generic.hid_packet.reportSize = hid_report_param->reportLength;

            g_device_composite->hid_generic.hid_packet.didReceiveFirstReport = true;

            // Wake up the read packet handler.
            sync_signal(&g_device_composite->hid_generic.hid_packet.receiveSync);
            error = kStatus_USB_Success;

            break;
        case kUSB_DeviceHidEventGetReport:
        case kUSB_DeviceHidEventSetReport:
        case kUSB_DeviceHidEventRequestReportBuffer:
            error = kStatus_USB_InvalidRequest;
            break;
        case kUSB_DeviceHidEventGetIdle:
        case kUSB_DeviceHidEventGetProtocol:
        case kUSB_DeviceHidEventSetIdle:
            sync_init(&g_device_composite->hid_generic.hid_packet.receiveSync, false);
            sync_init(&g_device_composite->hid_generic.hid_packet.sendSync, false);
            break;
        case kUSB_DeviceHidEventSetProtocol:
            break;
    }

    return error;
}

/*!
 * @brief HID device set configuration function.
 *
 * This function sets configuration for HID class.
 *
 * @param handle The HID class handle.
 * @param configure The HID class configure index.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t usb_device_hid_generic_set_configure(class_handle_t handle, uint8_t configure)
{
    usb_status_t error = kStatus_USB_Success;
    if (USB_COMPOSITE_CONFIGURE_INDEX == configure)
    {
        g_device_composite->hid_generic.attach = 1;

        /* Set device configuration request */
        error = USB_DeviceHidRecv(g_device_composite->hid_generic.hid_handle, USB_HID_GENERIC_ENDPOINT_OUT,
                                  (uint8_t *)&g_device_composite->hid_generic.hid_packet.report.header,
                                  sizeof(g_device_composite->hid_generic.hid_packet.report));
        g_device_composite->hid_generic.current_configuration = configure;
    }
    return error;
}

usb_status_t usb_device_hid_generic_set_interface(class_handle_t handle, uint8_t interface, uint8_t alternate_setting)
{
    usb_status_t error = kStatus_USB_Success;
    if (interface < USB_HID_GENERIC_INTERFACE_COUNT)
    {
        g_device_composite->hid_generic.current_interface_alternate_setting[interface] = alternate_setting;
        error = USB_DeviceHidRecv(g_device_composite->hid_generic.hid_handle, USB_HID_GENERIC_ENDPOINT_OUT,
                                  (uint8_t *)&g_device_composite->hid_generic.hid_packet.report.header,
                                  sizeof(g_device_composite->hid_generic.hid_packet.report));
    }
    return error;
}

usb_status_t usb_device_hid_generic_init(usb_device_composite_struct_t *device_composite)
{
    g_device_composite = device_composite;
    return kStatus_USB_Success;
}

usb_status_t usb_device_hid_generic_deinit(usb_device_composite_struct_t *device_composite)
{
    g_device_composite = device_composite;
    g_device_composite->hid_generic.hid_handle = (class_handle_t)NULL;
    return kStatus_USB_Success;
}

#endif //  BL_CONFIG_USB_HID

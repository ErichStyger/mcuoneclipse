/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bootloader/bl_context.h"
#include "bootloader/bootloader.h"
#include "bootloader_common.h"
#include "fsl_device_registers.h"
#include "bootloader_core.h"
#include "sbloader/sbloader.h"
#include "sbloader/sb_file_format.h"
#include "utilities/fsl_rtos_abstraction.h"
#include <string.h>
#include "property/property.h"

#include "usb_device_config.h"
#include "usb.h"
#include "usb_device.h"

#include "usb_device_class.h"
#include "usb_device_msc.h"
#include "usb_device_hid.h"
#include "usb_device_ch9.h"
#include "usb_descriptor.h"
#include "bootloader_hid_report_ids.h"
#include "composite.h"

#include <stdio.h>
#include <stdlib.h>

#if defined(K65F18_SERIES)
#include "MK65F18_INV.h"
#endif

#if (BL_CONFIG_USB_HID || BL_CONFIG_HS_USB_HID || BL_CONFIG_USB_MSC || BL_CONFIG_HS_USB_MSC)

//! @addtogroup usb_hid_peripheral
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
#define REQ_DATA_SIZE (1)

#define USB_HID_INDEX (0)
#define USB_MSC_INDEX (1)

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

static bool usb_hid_poll_for_activity(const peripheral_descriptor_t *self);
static status_t usb_device_full_init(const peripheral_descriptor_t *self, serial_byte_receive_func_t function);
static void usb_device_full_shutdown(const peripheral_descriptor_t *self);
static void usb_msc_pump(const peripheral_descriptor_t *self);

static status_t usb_hid_packet_init(const peripheral_descriptor_t *self);
static status_t usb_hid_packet_read(const peripheral_descriptor_t *self,
                                    uint8_t **packet,
                                    uint32_t *packetLength,
                                    packet_type_t packetType);
static status_t usb_hid_packet_write(const peripheral_descriptor_t *self,
                                     const uint8_t *packet,
                                     uint32_t byteCount,
                                     packet_type_t packetType);
static void usb_hid_packet_abort_data_phase(const peripheral_descriptor_t *self);
static status_t usb_hid_packet_finalize(const peripheral_descriptor_t *self);
static uint32_t usb_hid_packet_get_max_packet_size(const peripheral_descriptor_t *self);

// static bool s_dHidMscActivity[USB_COMPOSITE_INTERFACE_COUNT] = {false};
static bool s_dHidMscActivity[2] = { false };

static IRQn_Type s_usbIRQs[] = USB_IRQS;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

const peripheral_control_interface_t g_usbHidControlInterface = {.pollForActivity = usb_hid_poll_for_activity,
                                                                 .init = usb_device_full_init,
                                                                 .shutdown = usb_device_full_shutdown,
                                                                 .pump = usb_msc_pump };

const peripheral_packet_interface_t g_usbHidPacketInterface = {.init = usb_hid_packet_init,
                                                               .readPacket = usb_hid_packet_read,
                                                               .writePacket = usb_hid_packet_write,
                                                               .abortDataPhase = usb_hid_packet_abort_data_phase,
                                                               .finalize = usb_hid_packet_finalize,
                                                               .getMaxPacketSize = usb_hid_packet_get_max_packet_size,
                                                               .byteReceivedCallback = 0 };

static usb_device_composite_struct_t g_device_composite;

usb_status_t usb_device_callback(usb_device_handle handle, uint32_t event, void *param);

extern usb_status_t usb_device_msc_callback(class_handle_t handle, uint32_t event, void *param);

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

bool usb_hid_poll_for_activity(const peripheral_descriptor_t *self)
{
    //    uint32_t hidInfoIndex = self->instance / 2;
    bool hid_active = false;
    bool msc_active = false;
#if USB_DEVICE_CONFIG_HID
    hid_active = g_device_composite.hid_generic.hid_packet.didReceiveFirstReport;
#endif //  USB_DEVICE_CONFIG_HID
#if USB_DEVICE_CONFIG_MSC
    msc_active = g_device_composite.msc_disk.msc_state.isActive;
#endif //  USB_DEVICE_CONFIG_HID

    s_dHidMscActivity[0] = hid_active;
    s_dHidMscActivity[1] = msc_active;
    return (g_device_composite.attach && (hid_active || msc_active));
}

usb_status_t usb_device_callback(usb_device_handle handle, uint32_t event, void *param)
{
    usb_status_t error = kStatus_USB_Success;
    uint16_t *temp16 = (uint16_t *)param;
    uint8_t *temp8 = (uint8_t *)param;

    switch (event)
    {
        case kUSB_DeviceEventBusReset:
        {
            g_device_composite.attach = 0;
#if (defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0)) || \
    (defined(USB_DEVICE_CONFIG_LPCIP3511HS) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0))
            if (kStatus_USB_Success == USB_DeviceClassGetSpeed(CONTROLLER_ID, &g_device_composite.speed))
            {
                usb_device_set_speed(handle, g_device_composite.speed);
            }
#endif
        }
        break;
        case kUSB_DeviceEventSetConfiguration:
            if (param)
            {
                g_device_composite.attach = 1;
                g_device_composite.current_configuration = *temp8;
#if USB_DEVICE_CONFIG_HID
                error = usb_device_hid_generic_set_configure(g_device_composite.hid_generic.hid_handle, *temp8);
#endif // USB_DEVICE_CONFIG_HID
#if USB_DEVICE_CONFIG_MSC
                usb_device_msc_disk_set_configure(g_device_composite.msc_disk.msc_handle, *temp8);
#endif // USB_DEVICE_CONFIG_MSC
                error = kStatus_USB_Success;
            }
            break;
        case kUSB_DeviceEventSetInterface:
            if (g_device_composite.attach)
            {
                uint8_t interface = (uint8_t)((*temp16 & 0xFF00U) >> 0x08U);
                uint8_t alternate_setting = (uint8_t)(*temp16 & 0x00FFU);
                if (interface < USB_COMPOSITE_INTERFACE_COUNT)
                {
                    g_device_composite.current_interface_alternate_setting[interface] = alternate_setting;
#if USB_DEVICE_CONFIG_HID
                    usb_device_hid_generic_set_interface(g_device_composite.hid_generic.hid_handle, interface,
                                                         alternate_setting);
#endif
                    error = kStatus_USB_Success;
                }
            }
            break;
        case kUSB_DeviceEventGetConfiguration:
            if (param)
            {
                *temp8 = g_device_composite.current_configuration;
                error = kStatus_USB_Success;
            }
            break;
        case kUSB_DeviceEventGetInterface:
            if (param)
            {
                uint8_t interface = (uint8_t)((*temp16 & 0xFF00) >> 0x08);
                if (interface < USB_COMPOSITE_INTERFACE_COUNT)
                {
                    *temp16 = (*temp16 & 0xFF00) | g_device_composite.current_interface_alternate_setting[interface];
                    error = kStatus_USB_Success;
                }
                else
                {
                    error = kStatus_USB_InvalidRequest;
                }
            }
            break;
        case kUSB_DeviceEventGetDeviceDescriptor:
            if (param)
            {
                error = usb_device_get_device_descriptor(handle, (usb_device_get_device_descriptor_struct_t *)param);
            }
            break;
        case kUSB_DeviceEventGetConfigurationDescriptor:
            if (param)
            {
                error = usb_device_get_configuration_descriptor(
                    handle, (usb_device_get_configuration_descriptor_struct_t *)param);
            }
            break;
        case kUSB_DeviceEventGetStringDescriptor:
            if (param)
            {
                error = usb_device_get_string_descriptor(handle, (usb_device_get_string_descriptor_struct_t *)param);
            }
            break;
        case kUSB_DeviceEventGetHidDescriptor:
            if (param)
            {
                error = usb_device_get_hid_descriptor(handle, (usb_device_get_hid_descriptor_struct_t *)param);
            }
            break;
        case kUSB_DeviceEventGetHidReportDescriptor:
            if (param)
            {
                error = usb_device_get_hid_report_descriptor(handle,
                                                             (usb_device_get_hid_report_descriptor_struct_t *)param);
            }
            break;
        case kUSB_DeviceEventGetHidPhysicalDescriptor:
            if (param)
            {
                error = usb_device_get_hid_physical_descriptor(
                    handle, (usb_device_get_hid_physical_descriptor_struct_t *)param);
            }
            break;
    }

    return error;
}

status_t usb_device_full_init(const peripheral_descriptor_t *self, serial_byte_receive_func_t function)
{
    // Not used for USB
    (void)function;

    uint8_t irqNumber;

#if defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0U)
    uint8_t usbDeviceEhciIrq[] = USBHS_IRQS;
    irqNumber = usbDeviceEhciIrq[CONTROLLER_ID - kUSB_ControllerEhci0];
#endif
#if defined(USB_DEVICE_CONFIG_KHCI) && (USB_DEVICE_CONFIG_KHCI > 0U)
    uint8_t usbDeviceKhciIrq[] = USB_IRQS;
    irqNumber = usbDeviceKhciIrq[CONTROLLER_ID - kUSB_ControllerKhci0];
#endif
#if defined(USB_DEVICE_CONFIG_LPCIP3511FS) && (USB_DEVICE_CONFIG_LPCIP3511FS > 0U)
    uint8_t usbDeviceLpcip3511Irq[] = USB_IRQS;
    irqNumber = usbDeviceLpcip3511Irq[CONTROLLER_ID - kUSB_ControllerLpcIp3511Fs0];
#endif
#if defined(USB_DEVICE_CONFIG_LPCIP3511HS) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0U)
    uint8_t usbhsDeviceLpcip3511Irq[] = USBHSD_IRQS;
    irqNumber = usbhsDeviceLpcip3511Irq[CONTROLLER_ID - kUSB_ControllerLpcIp3511Hs0];
#endif

    // Init the state info.
    memset(&g_device_composite, 0, sizeof(g_device_composite));

    // Init the usb clock, if usb clock cannot be enabled, clear corresponding bit even it is enabled by user.
    if (!usb_clock_init())
    {
        g_bootloaderContext.propertyInterface->store->configurationData.enabledPeripherals &= ~kPeripheralType_USB_HID;
        g_bootloaderContext.propertyInterface->store->availablePeripherals &= ~kPeripheralType_USB_HID;
        return kStatus_Fail;
    }

    property_store_t *propertyStore = g_bootloaderContext.propertyInterface->store;

    if ((propertyStore->configurationData.usbPid != (uint16_t)0xFFFF) ||
        (propertyStore->configurationData.usbVid != (uint16_t)0xFFFF))
    {
        g_device_descriptor[kUsbDescriptorIndex_VidLow] = ((propertyStore->configurationData.usbVid) & 0xFF);
        g_device_descriptor[kUsbDescriptorIndex_VidHigh] = ((propertyStore->configurationData.usbVid) & 0xFF00) >> 8;
        g_device_descriptor[kUsbDescriptorIndex_PidLow] = ((propertyStore->configurationData.usbPid) & 0xFF);
        g_device_descriptor[kUsbDescriptorIndex_PidHigh] = ((propertyStore->configurationData.usbPid) & 0xFF00) >> 8;
    }

    if (propertyStore->configurationData.usbStringsPointer != 0xFFFFFFFF)
    {
#if FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
        // Make sure the usb string isn't in execute-only region.
        if (is_in_execute_only_region(propertyStore->configurationData.usbStringsPointer, sizeof(usb_language_list_t)))
        {
            g_language_ptr = &g_language_list;
        }
        else
#endif // #if FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
        {
            g_language_ptr = (usb_language_list_t *)propertyStore->configurationData.usbStringsPointer;
        }
    }
    else
    {
        g_language_ptr = &g_language_list;
    }

    g_device_composite.speed = USB_SPEED_FULL;
    g_device_composite.attach = 0;
#if USB_DEVICE_CONFIG_HID
    g_device_composite.hid_generic.hid_handle = (class_handle_t)NULL;
#endif // USB_DEVICE_CONFIG_HID
#if USB_DEVICE_CONFIG_MSC
    g_device_composite.msc_disk.msc_handle = (class_handle_t)NULL;
#endif // USB_DEVICE_CONFIG_MSC
    g_device_composite.device_handle = NULL;

    if (kStatus_USB_Success !=
        USB_DeviceClassInit(CONTROLLER_ID, &g_composite_device_config_list, &g_device_composite.device_handle))
    {
        return kStatus_Fail;
    }
    else
    {
#if ((USB_DEVICE_CONFIG_HID == 1) && (USB_DEVICE_CONFIG_MSC == 1))
        g_device_composite.msc_disk.msc_handle = g_composite_device_config_list.config[1].classHandle;
        usb_device_msc_disk_init(&g_device_composite);
        g_device_composite.hid_generic.hid_handle = g_composite_device_config_list.config[0].classHandle;
        usb_device_hid_generic_init(&g_device_composite);
#endif
#if ((USB_DEVICE_CONFIG_MSC == 1) && (USB_DEVICE_CONFIG_HID == 0))
        g_device_composite.msc_disk.msc_handle = g_composite_device_config_list.config[0].classHandle;
        usb_device_msc_disk_init(&g_device_composite);
#endif // USB_DEVICE_CONFIG_MSC
#if ((USB_DEVICE_CONFIG_HID == 1) && (USB_DEVICE_CONFIG_MSC == 0))
        g_device_composite.hid_generic.hid_handle = g_composite_device_config_list.config[0].classHandle;
        usb_device_hid_generic_init(&g_device_composite);
#endif // USB_DEVICE_CONFIG_HID
    }

    /* Install isr, set priority, and enable IRQ. */
    NVIC_SetPriority((IRQn_Type)irqNumber, USB_DEVICE_INTERRUPT_PRIORITY);
    NVIC_EnableIRQ((IRQn_Type)irqNumber);

    USB_DeviceRun(g_device_composite.device_handle);

    return kStatus_Success;
}

void usb_device_full_shutdown(const peripheral_descriptor_t *self)
{
    if (kStatus_USB_Success != USB_DeviceClassDeinit(CONTROLLER_ID))
    {
        return;
    }
    else
    {
// Shutdown class driver
#if USB_DEVICE_CONFIG_MSC
        usb_device_msc_disk_deinit(&g_device_composite);
#endif // USB_DEVICE_CONFIG_MSC
#if USB_DEVICE_CONFIG_HID
        usb_device_hid_generic_deinit(&g_device_composite);
#endif // USB_DEVICE_CONFIG_MSC
    }

// Make sure we are clocking to the peripheral to ensure there
// are no bus errors
#if !BL_DEVICE_IS_LPC_SERIES
#if USB_DEVICE_CONFIG_KHCI
#if defined(PCC_BASE_ADDRS)
    if ((self->instance == kUSB_ControllerEhci0) && ((*(volatile uint32_t *)kCLOCK_Usbfs0) & PCC_CLKCFG_CGC_MASK))
    {
        // Disable the USB interrupt
        NVIC_DisableIRQ(USB0_IRQn);

        // Clear any pending interrupts on USB
        NVIC_ClearPendingIRQ(USB0_IRQn);

        // Turn off clocking to USB
        CLOCK_DisableClock(kCLOCK_Usbfs0);
    }
#else
    if ((CONTROLLER_ID == kUSB_ControllerKhci0) && (SIM->SCGC4 & SIM_SCGC4_USBOTG_MASK))
    {
        // Disable the USB interrupt
        NVIC_DisableIRQ(USB0_IRQn);

        // Clear any pending interrupts on USB
        NVIC_ClearPendingIRQ(USB0_IRQn);

        // Turn off clocking to USB
        SIM->SCGC4 &= ~SIM_SCGC4_USBOTG_MASK;
    }
#endif // defined(PCC_BASE_ADDRS)
#endif // #if USB_DEVICE_CONFIG_EHCI

#if USB_DEVICE_CONFIG_EHCI
    if (CONTROLLER_ID == kUSB_ControllerEhci0)
    {
        // Disable the USB interrupt
        NVIC_DisableIRQ(s_usbIRQs[self->instance]);

        // Clear any pending interrupts on USB
        NVIC_ClearPendingIRQ(s_usbIRQs[self->instance]);

#if defined(ANATOP_BASE_ADDRS) || defined(CCM_ANALOG_BASE)
#if defined(K32H844P_SERIES)
        CLOCK_DisableClock(kCLOCK_Usbhs0);
#else
        CLOCK_DisableClock(kCLOCK_UsbOh3);
#endif
#else
        if (SIM->SCGC3 & SIM_SCGC3_USBHS_MASK)
        {
            // Disable the USB interrupt
            NVIC_DisableIRQ(USBHS_IRQn);

            // Clear any pending interrupts on USB
            NVIC_ClearPendingIRQ(USBHS_IRQn);
            // Turn off HS USB PHY clock gate
            SIM->SCGC3 &= ~(SIM_SCGC3_USBHS_MASK | SIM_SCGC3_USBHSPHY_MASK);
        }
#endif // ANATOP_BASE_ADDRS
    }
#endif
#else // BL_DEVICE_IS_LPC_SERIES
    if ((CONTROLLER_ID == kUSB_ControllerLpcIp3511Fs0))
    {
        // Disable the USB interrupt
        NVIC_DisableIRQ(USB0_IRQn);

        // Clear any pending interrupts on USB
        NVIC_ClearPendingIRQ(USB0_IRQn);
    }
#if USB_DEVICE_CONFIG_LPCIP3511HS
    else if ((CONTROLLER_ID == kUSB_ControllerLpcIp3511Hs0))
    {
        // Disable the USB interrupt
        NVIC_DisableIRQ(USB1_IRQn);

        // Clear any pending interrupts on USB
        NVIC_ClearPendingIRQ(USB1_IRQn);
    }
#endif
#endif // !BL_DEVICE_IS_LPC_SERIES
}

//! @brief Run the sbloader state machine.
//!
//! This function is called repeatedly by the main application loop. We use it
//! to run the sbloader state machine from non-interrupt context.
void usb_msc_pump(const peripheral_descriptor_t *self)
{
    s_dHidMscActivity[USB_HID_INDEX] = false;
    s_dHidMscActivity[USB_MSC_INDEX] = true;

//#if (USB_DEVICE_CONFIG_MSC)
#if (BL_CONFIG_USB_MSC || BL_CONFIG_HS_USB_MSC)
    lock_acquire();
    usb_device_msc_disk_pump();

    if (g_device_composite.msc_disk.msc_state.sbLoaderStatus == kSbLoaderFinal)
    {
        g_device_composite.msc_disk.msc_state.sbLoaderStatus = kSbLoaderFree;
        sbloader_finalize();
    }
    lock_release();

    s_dHidMscActivity[USB_MSC_INDEX] = g_device_composite.msc_disk.msc_state.isActive;
#endif // BL_CONFIG_USB_MSC

    s_dHidMscActivity[USB_HID_INDEX] = true;
}

static status_t usb_hid_packet_init(const peripheral_descriptor_t *self)
{
#if USB_DEVICE_CONFIG_HID
    sync_init(&g_device_composite.hid_generic.hid_packet.receiveSync, false);
    sync_init(&g_device_composite.hid_generic.hid_packet.sendSync, false);

    // Check for any received data that may be pending
    sync_signal(&g_device_composite.hid_generic.hid_packet.receiveSync);
#endif
    return kStatus_Success;
}

static status_t usb_hid_packet_read(const peripheral_descriptor_t *self,
                                    uint8_t **packet,
                                    uint32_t *packetLength,
                                    packet_type_t packetType)
{
    if (!packet || !packetLength)
    {
        return kStatus_InvalidArgument;
    }
    *packetLength = 0;

    // Determine report ID based on packet type.
    uint8_t reportID;
    switch (packetType)
    {
        case kPacketType_Command:
            reportID = kBootloaderReportID_CommandOut;
            break;
        case kPacketType_Data:
            reportID = kBootloaderReportID_DataOut;
            break;
        default:
            //            debug_printf("usbhid: unsupported packet type %d\r\n", (int)packetType);
            return kStatus_Fail;
    };
#if USB_DEVICE_CONFIG_HID
    if (s_dHidMscActivity[USB_HID_INDEX])
    {
        // The first receive data request was initiated after enumeration.
        // After that we wait until we are ready to read data before
        // we request more. This mechanism prevents data loss
        // by allowing the USB controller to hold off the host with NAKs
        // on the interrupt out pipe until we are ready.
        if (g_device_composite.hid_generic.hid_packet.isReceiveDataRequestRequired)
        {
            // Initiate receive on interrupt out pipe.
            USB_DeviceHidRecv(g_device_composite.hid_generic.hid_handle, USB_HID_GENERIC_ENDPOINT_OUT,
                              (uint8_t *)&g_device_composite.hid_generic.hid_packet.report.header,
                              sizeof(g_device_composite.hid_generic.hid_packet.report));
        }

        g_device_composite.hid_generic.hid_packet.isReceiveDataRequestRequired = true;

        // Wait until we have received a report.

        sync_wait(&g_device_composite.hid_generic.hid_packet.receiveSync, kSyncWaitForever);

        // Check the report ID, the first byte of the report buffer.
        if (g_device_composite.hid_generic.hid_packet.report.header.reportID != reportID)
        {
            // If waiting for a command but get data, this is a flush after a data abort.
            if ((reportID == kBootloaderReportID_CommandOut) &&
                (g_device_composite.hid_generic.hid_packet.report.header.reportID == kBootloaderReportID_DataOut))
            {
                return kStatus_AbortDataPhase;
            }
            //        debug_printf("usbhid: received unexpected report=%x\r\n",
            //        g_device_composite.hid_generic.hid_packet.report.header.reportID);
            return kStatus_Fail;
        }

        // Extract the packet length encoded as bytes 1 and 2 of the report. The packet length
        // is transferred in little endian byte order.
        uint16_t lengthOfPacket = g_device_composite.hid_generic.hid_packet.report.header.packetLengthLsb |
                                  (g_device_composite.hid_generic.hid_packet.report.header.packetLengthMsb << 8);

        // Make sure we got all of the packet. Some hosts (Windows) may send up to the maximum
        // report size, so there may be extra trailing bytes.
        if ((g_device_composite.hid_generic.hid_packet.reportSize -
             sizeof(g_device_composite.hid_generic.hid_packet.report.header)) < lengthOfPacket)
        {
            //        debug_printf("usbhid: received only %d bytes of packet with length %d\r\n",
            //        s_hidInfo[hidInfoIndex].reportSize - 3, lengthOfPacket);
            return kStatus_Fail;
        }

        // Return packet to caller.
        *packet = g_device_composite.hid_generic.hid_packet.report.packet;
        *packetLength = lengthOfPacket;
    }
#endif // USB_DEVICE_CONFIG_HID
    return kStatus_Success;
}

static status_t usb_hid_packet_write(const peripheral_descriptor_t *self,
                                     const uint8_t *packet,
                                     uint32_t byteCount,
                                     packet_type_t packetType)
{
#if USB_DEVICE_CONFIG_HID
    if (s_dHidMscActivity[USB_HID_INDEX])
    {
        if (byteCount > kMinUsbHidPacketBufferSize)
        {
            debug_printf("Error: invalid packet size %d\r\n", byteCount);
            return kStatus_InvalidArgument;
        }

        // Determine report ID based on packet type.
        uint8_t reportID;
        switch (packetType)
        {
            case kPacketType_Command:
                reportID = kBootloaderReportID_CommandIn;
                break;
            case kPacketType_Data:
                reportID = kBootloaderReportID_DataIn;
                break;
            default:
                debug_printf("usbhid: unsupported packet type %d\r\n", (int)packetType);
                return kStatus_Fail;
        };

        // Check for data phase aborted by receiver.
        lock_acquire();
        if (g_device_composite.hid_generic.hid_packet.didReceiveDataPhaseAbort)
        {
            g_device_composite.hid_generic.hid_packet.didReceiveDataPhaseAbort = false;
            lock_release();
            return kStatus_AbortDataPhase;
        }
        lock_release();

        // Construct report contents.
        g_device_composite.hid_generic.hid_packet.report.header.reportID = reportID;
        g_device_composite.hid_generic.hid_packet.report.header._padding = 0;
        g_device_composite.hid_generic.hid_packet.report.header.packetLengthLsb = byteCount & 0xff;
        g_device_composite.hid_generic.hid_packet.report.header.packetLengthMsb = (byteCount >> 8) & 0xff;
        if (packet && byteCount > 0)
        {
            memcpy(&g_device_composite.hid_generic.hid_packet.report.packet, packet, byteCount);
        }
        if (g_device_composite.hid_generic.attach == 1)
        {
            // Send the maximum report size since that's what the host expects.
            // There may be extra trailing bytes.
            USB_DeviceHidSend(g_device_composite.hid_generic.hid_handle, USB_HID_GENERIC_ENDPOINT_IN,
                              (uint8_t *)&g_device_composite.hid_generic.hid_packet.report.header,
                              sizeof(g_device_composite.hid_generic.hid_packet.report));
            sync_wait(&g_device_composite.hid_generic.hid_packet.sendSync, kSyncWaitForever);
        }
    }
#endif // USB_DEVICE_CONFIG_HID
    return kStatus_Success;
}

static void usb_hid_packet_abort_data_phase(const peripheral_descriptor_t *self)
{
    status_t status = self->packetInterface->writePacket(self, NULL, 0, kPacketType_Command);
    if (status != kStatus_Success)
    {
        debug_printf("Error: usb_hid_packet_abort write packet returned status 0x%x\r\n", status);
        return;
    }
}

static status_t usb_hid_packet_finalize(const peripheral_descriptor_t *self)
{
    return kStatus_Success;
}

static uint32_t usb_hid_packet_get_max_packet_size(const peripheral_descriptor_t *self)
{
    return kMinUsbHidPacketBufferSize;
}

#if defined(USBIRQ_Handler)
void USBIRQ_Handler(void)
{
#if USB_DEVICE_CONFIG_MSC
    if ((g_device_composite.msc_disk.msc_state.sbLoaderStatus == kSbLoaderLoading) ||
        (g_device_composite.msc_disk.msc_state.sbLoaderStatus == kSbLoaderFinal))
    {
        //#if USB_DEVICE_CONFIG_HID
        sync_reset(&g_device_composite.hid_generic.hid_packet.receiveSync);
        sync_reset(&g_device_composite.hid_generic.hid_packet.sendSync);
        //#endif //#if USB_DEVICE_CONFIG_HID
    }
#endif // USB_DEVICE_CONFIG_MSC
    USB_DeviceEhciIsrFunction(g_device_composite.device_handle);
}
#else
#if defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0)
void USBHS_IRQHandler(void)
{
#if USB_DEVICE_CONFIG_MSC
    if ((g_device_composite.msc_disk.msc_state.sbLoaderStatus == kSbLoaderLoading) ||
        (g_device_composite.msc_disk.msc_state.sbLoaderStatus == kSbLoaderFinal))
    {
#if USB_DEVICE_CONFIG_HID
        sync_reset(&g_device_composite.hid_generic.hid_packet.receiveSync);
        sync_reset(&g_device_composite.hid_generic.hid_packet.sendSync);
#endif //#if USB_DEVICE_CONFIG_HID
    }
#endif // USB_DEVICE_CONFIG_MSC
    USB_DeviceEhciIsrFunction(g_device_composite.device_handle);
}
#endif // #if defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0)

#if defined(USB_DEVICE_CONFIG_KHCI) && (USB_DEVICE_CONFIG_KHCI > 0)
void USB0_IRQHandler(void)
{
#if USB_DEVICE_CONFIG_MSC
    if ((g_device_composite.msc_disk.msc_state.sbLoaderStatus == kSbLoaderLoading) ||
        (g_device_composite.msc_disk.msc_state.sbLoaderStatus == kSbLoaderFinal))
    {
#if USB_DEVICE_CONFIG_HID
        sync_reset(&g_device_composite.hid_generic.hid_packet.receiveSync);
        sync_reset(&g_device_composite.hid_generic.hid_packet.sendSync);
#endif //#if USB_DEVICE_CONFIG_HID
    }
#endif // USB_DEVICE_CONFIG_MSC
    USB_DeviceKhciIsrFunction(g_device_composite.device_handle);
}
#endif // #if defined(USB_DEVICE_CONFIG_KHCI) && (USB_DEVICE_CONFIG_KHCI > 0)
#endif // USBIRQ_Handler

#if defined(USB_DEVICE_CONFIG_LPCIP3511FS) && (USB_DEVICE_CONFIG_LPCIP3511FS > 0)
void USB0_IRQHandler(void)
{
#if USB_DEVICE_CONFIG_MSC
    if ((g_device_composite.msc_disk.msc_state.sbLoaderStatus == kSbLoaderLoading) ||
        (g_device_composite.msc_disk.msc_state.sbLoaderStatus == kSbLoaderFinal))
    {
#if USB_DEVICE_CONFIG_HID
        sync_reset(&g_device_composite.hid_generic.hid_packet.receiveSync);
        sync_reset(&g_device_composite.hid_generic.hid_packet.sendSync);
#endif //#if USB_DEVICE_CONFIG_HID
    }
#endif // USB_DEVICE_CONFIG_MSC
    USB_DeviceLpcIp3511IsrFunction(g_device_composite.device_handle);
}
#endif

#if defined(USB_DEVICE_CONFIG_LPCIP3511HS) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0)
void USB1_IRQHandler(void)
{
#if USB_DEVICE_CONFIG_MSC
    if ((g_device_composite.msc_disk.msc_state.sbLoaderStatus == kSbLoaderLoading) ||
        (g_device_composite.msc_disk.msc_state.sbLoaderStatus == kSbLoaderFinal))
    {
#if USB_DEVICE_CONFIG_HID
        sync_reset(&g_device_composite.hid_generic.hid_packet.receiveSync);
        sync_reset(&g_device_composite.hid_generic.hid_packet.sendSync);
#endif //#if USB_DEVICE_CONFIG_HID
    }
#endif // USB_DEVICE_CONFIG_MSC
    USB_DeviceLpcIp3511IsrFunction(g_device_composite.device_handle);
}
#endif

//! @}

#endif // (BL_CONFIG_USB_HID || BL_CONFIG_HS_USB_HID || BL_CONFIG_USB_MSC || BL_CONFIG_HS_USB_MSC)

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

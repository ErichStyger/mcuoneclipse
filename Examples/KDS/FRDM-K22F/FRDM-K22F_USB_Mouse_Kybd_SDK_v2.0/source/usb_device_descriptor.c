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

#include "usb_device_config.h"
#include "usb.h"
#include "usb_device.h"

#include "usb_device_class.h"
#include "usb_device_hid.h"

#include "usb_device_descriptor.h"

#include "composite.h"

#include "hid_mouse.h"
#include "hid_keyboard.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* hid keyboard endpoint information */
usb_device_endpoint_struct_t g_UsbDeviceHidKeyboardEndpoints[USB_HID_KEYBOARD_ENDPOINT_COUNT] = {
    /* HID keyboard interrupt IN pipe */
    {
        USB_HID_KEYBOARD_ENDPOINT_IN | (USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT),
        USB_ENDPOINT_INTERRUPT, FS_HID_KEYBOARD_INTERRUPT_IN_PACKET_SIZE,
    },
};

/* HID keyboard interface information */
usb_device_interface_struct_t g_UsbDeviceHidKeyboardInterface[] = {{
    0U, /* The alternate setting of the interface */
    {
        USB_HID_KEYBOARD_ENDPOINT_COUNT, /* Endpoint count */
        g_UsbDeviceHidKeyboardEndpoints, /* Endpoints handle */
    },
    NULL,
}};

usb_device_interfaces_struct_t g_UsbDeviceHidKeyboardInterfaces[USB_HID_KEYBOARD_INTERFACE_COUNT] = {
    {
        USB_HID_KEYBOARD_CLASS,           /* HID keyboard class code */
        USB_HID_KEYBOARD_SUBCLASS,        /* HID keyboard subclass code */
        USB_HID_KEYBOARD_PROTOCOL,        /* HID keyboard protocol code */
        USB_HID_KEYBOARD_INTERFACE_INDEX, /* The interface number of the HID keyboard */
        g_UsbDeviceHidKeyboardInterface,  /* Interfaces handle */
        sizeof(g_UsbDeviceHidKeyboardInterface) / sizeof(usb_device_interfaces_struct_t),
    },
};

usb_device_interface_list_t g_UsbDeviceHidKeyboardInterfaceList[USB_DEVICE_CONFIGURATION_COUNT] = {
    {
        USB_HID_KEYBOARD_INTERFACE_COUNT, /* The interface count of the HID keyboard */
        g_UsbDeviceHidKeyboardInterfaces, /* The interfaces handle */
    },
};

usb_device_class_struct_t g_UsbDeviceHidKeyboardConfig = {
    g_UsbDeviceHidKeyboardInterfaceList, /* The interface list of the HID keyboard */
    kUSB_DeviceClassTypeHid,             /* The HID class type */
    USB_DEVICE_CONFIGURATION_COUNT,      /* The configuration count */
};

/* hid mouse endpoint information */
usb_device_endpoint_struct_t g_UsbDeviceHidMouseEndpoints[USB_HID_MOUSE_ENDPOINT_COUNT] = {
    /* HID mouse interrupt IN pipe */
    {
        USB_HID_MOUSE_ENDPOINT_IN | (USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT), USB_ENDPOINT_INTERRUPT,
        FS_HID_MOUSE_INTERRUPT_IN_PACKET_SIZE,
    },
};

/* HID mouse interface information */
usb_device_interface_struct_t g_UsbDeviceHidMouseInterface[] = {{
    0U, /* The alternate setting of the interface */
    {
        USB_HID_MOUSE_ENDPOINT_COUNT, /* Endpoint count */
        g_UsbDeviceHidMouseEndpoints, /* Endpoints handle */
    },
    NULL,
}};

usb_device_interfaces_struct_t g_UsbDeviceHidMouseInterfaces[USB_HID_MOUSE_INTERFACE_COUNT] = {
    {
        USB_HID_MOUSE_CLASS,           /* HID mouse class code */
        USB_HID_MOUSE_SUBCLASS,        /* HID mouse subclass code */
        USB_HID_MOUSE_PROTOCOL,        /* HID mouse protocol code */
        USB_HID_MOUSE_INTERFACE_INDEX, /* The interface number of the HID mouse */
        g_UsbDeviceHidMouseInterface,  /* Interfaces handle */
        sizeof(g_UsbDeviceHidMouseInterface) / sizeof(usb_device_interfaces_struct_t),
    },
};

usb_device_interface_list_t g_UsbDeviceHidMouseInterfaceList[USB_DEVICE_CONFIGURATION_COUNT] = {
    {
        USB_HID_MOUSE_INTERFACE_COUNT, /* The interface count of the HID mouse */
        g_UsbDeviceHidMouseInterfaces, /* The interfaces handle */
    },
};

usb_device_class_struct_t g_UsbDeviceHidMouseConfig = {
    g_UsbDeviceHidMouseInterfaceList, /* The interface list of the HID mouse */
    kUSB_DeviceClassTypeHid,          /* The HID class type */
    USB_DEVICE_CONFIGURATION_COUNT,   /* The configuration count */
};

uint8_t g_UsbDeviceDescriptor[USB_DESCRIPTOR_LENGTH_DEVICE] = {
    USB_DESCRIPTOR_LENGTH_DEVICE, /* Size of this descriptor in bytes */
    USB_DESCRIPTOR_TYPE_DEVICE,   /* DEVICE Descriptor Type */
    USB_SHORT_GET_LOW(USB_DEVICE_SPECIFIC_BCD_VERSION),
    USB_SHORT_GET_HIGH(USB_DEVICE_SPECIFIC_BCD_VERSION), /* USB Specification Release Number in
                                                            Binary-Coded Decimal (i.e., 2.10 is 210H). */
    USB_DEVICE_CLASS,                                    /* Class code (assigned by the USB-IF). */
    USB_DEVICE_SUBCLASS,                                 /* Subclass code (assigned by the USB-IF). */
    USB_DEVICE_PROTOCOL,                                 /* Protocol code (assigned by the USB-IF). */
    USB_CONTROL_MAX_PACKET_SIZE,                         /* Maximum packet size for endpoint zero
                                                            (only 8, 16, 32, or 64 are valid) */
    0xA2U, 0x15U,                                        /* Vendor ID (assigned by the USB-IF) */
    0x7EU, 0x00U,                                        /* Product ID (assigned by the manufacturer) */
    USB_SHORT_GET_LOW(USB_DEVICE_DEMO_BCD_VERSION),
    USB_SHORT_GET_HIGH(USB_DEVICE_DEMO_BCD_VERSION), /* Device release number in binary-coded decimal */
    0x01U,                                           /* Index of string descriptor describing manufacturer */
    0x02U,                                           /* Index of string descriptor describing product */
    0x00U,                                           /* Index of string descriptor describing the
                                                        device's serial number */
    USB_DEVICE_CONFIGURATION_COUNT,                  /* Number of possible configurations */
};

uint8_t g_UsbDeviceConfigurationDescriptor[USB_DESCRIPTOR_LENGTH_CONFIGURATION_ALL] = {
    USB_DESCRIPTOR_LENGTH_CONFIGURE, /* Size of this descriptor in bytes */
    USB_DESCRIPTOR_TYPE_CONFIGURE,   /* CONFIGURATION Descriptor Type */
    USB_SHORT_GET_LOW(USB_DESCRIPTOR_LENGTH_CONFIGURATION_ALL),
    USB_SHORT_GET_HIGH(
        USB_DESCRIPTOR_LENGTH_CONFIGURATION_ALL), /* Total length of data returned for this configuration. */
    USB_COMPOSITE_INTERFACE_COUNT,                /* Number of interfaces supported by this configuration */
    USB_COMPOSITE_CONFIGURE_INDEX,                /* Value to use as an argument to the
                                                       SetConfiguration() request to select this configuration */
    0x00U,                                        /* Index of string descriptor describing this configuration */
    (USB_DESCRIPTOR_CONFIGURE_ATTRIBUTE_D7_MASK) |
        (USB_DEVICE_CONFIG_SELF_POWER << USB_DESCRIPTOR_CONFIGURE_ATTRIBUTE_SELF_POWERED_SHIFT) |
        (USB_DEVICE_CONFIG_REMOTE_WAKEUP << USB_DESCRIPTOR_CONFIGURE_ATTRIBUTE_REMOTE_WAKEUP_SHIFT),
    /* Configuration characteristics
         D7: Reserved (set to one)
         D6: Self-powered
         D5: Remote Wakeup
         D4...0: Reserved (reset to zero)
    */
    USB_DEVICE_MAX_POWER,            /* Maximum power consumption of the USB
                                      * device from the bus in this specific
                                      * configuration when the device is fully
                                      * operational. Expressed in 2 mA units
                                      *  (i.e., 50 = 100 mA).
                                      */
    USB_DESCRIPTOR_LENGTH_INTERFACE, /* Size of this descriptor in bytes */
    USB_DESCRIPTOR_TYPE_INTERFACE,   /* INTERFACE Descriptor Type */
    USB_HID_MOUSE_INTERFACE_INDEX,   /* Number of this interface. */
    0x00U,                           /* Value used to select this alternate setting
                                        for the interface identified in the prior field */
    USB_HID_MOUSE_ENDPOINT_COUNT,    /* Number of endpoints used by this
                                          interface (excluding endpoint zero). */
    USB_HID_MOUSE_CLASS,             /* Class code (assigned by the USB-IF). */
    USB_HID_MOUSE_SUBCLASS,          /* Subclass code (assigned by the USB-IF). */
    USB_HID_MOUSE_PROTOCOL,          /* Protocol code (assigned by the USB). */
    0x03U,                           /* Index of string descriptor describing this interface */

    USB_DESCRIPTOR_LENGTH_HID,      /* Numeric expression that is the total size of the
                                       HID descriptor. */
    USB_DESCRIPTOR_TYPE_HID,        /* Constant name specifying type of HID
                                       descriptor. */
    0x00U, 0x01U,                   /* Numeric expression identifying the HID Class
                                       Specification release. */
    0x00U,                          /* Numeric expression identifying country code of
                                       the localized hardware */
    0x01U,                          /* Numeric expression specifying the number of
                                       class descriptors(at least one report descriptor) */
    USB_DESCRIPTOR_TYPE_HID_REPORT, /* Constant name identifying type of class descriptor. */
    USB_SHORT_GET_LOW(USB_DESCRIPTOR_LENGTH_HID_MOUSE_REPORT),
    USB_SHORT_GET_HIGH(USB_DESCRIPTOR_LENGTH_HID_MOUSE_REPORT),
    /* Numeric expression that is the total size of the
       Report descriptor. */
    USB_DESCRIPTOR_LENGTH_ENDPOINT, /* Size of this descriptor in bytes */
    USB_DESCRIPTOR_TYPE_ENDPOINT,   /* ENDPOINT Descriptor Type */
    USB_HID_MOUSE_ENDPOINT_IN | (USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT),
    /* The address of the endpoint on the USB device
       described by this descriptor. */
    USB_ENDPOINT_INTERRUPT, /* This field describes the endpoint's attributes */
    USB_SHORT_GET_LOW(FS_HID_MOUSE_INTERRUPT_IN_PACKET_SIZE), USB_SHORT_GET_HIGH(FS_HID_MOUSE_INTERRUPT_IN_PACKET_SIZE),
    /* Maximum packet size this endpoint is capable of
       sending or receiving when this configuration is
       selected. */
    FS_HID_MOUSE_INTERRUPT_IN_INTERVAL, /* Interval for polling endpoint for data transfers. */

    USB_DESCRIPTOR_LENGTH_INTERFACE,  /* Size of this descriptor in bytes */
    USB_DESCRIPTOR_TYPE_INTERFACE,    /* INTERFACE Descriptor Type */
    USB_HID_KEYBOARD_INTERFACE_INDEX, /* Number of this interface. */
    0x00U,                            /* Value used to select this alternate setting
                                         for the interface identified in the prior field */
    USB_HID_KEYBOARD_ENDPOINT_COUNT,  /* Number of endpoints used by this
                                        interface (excluding endpoint zero). */
    USB_HID_KEYBOARD_CLASS,           /* Class code (assigned by the USB-IF). */
    USB_HID_KEYBOARD_SUBCLASS,        /* Subclass code (assigned by the USB-IF). */
    USB_HID_KEYBOARD_PROTOCOL,        /* Protocol code (assigned by the USB). */
    0x04U,                            /* Index of string descriptor describing this interface */

    USB_DESCRIPTOR_LENGTH_HID,      /* Numeric expression that is the total size of the
                                       HID descriptor. */
    USB_DESCRIPTOR_TYPE_HID,        /* Constant name specifying type of HID
                                       descriptor. */
    0x00U, 0x01U,                   /* Numeric expression identifying the HID Class
                                       Specification release. */
    0x00U,                          /* Numeric expression identifying country code of
                                       the localized hardware */
    0x01U,                          /* Numeric expression specifying the number of
                                       class descriptors(at least one report descriptor) */
    USB_DESCRIPTOR_TYPE_HID_REPORT, /* Constant name identifying type of class descriptor. */
    USB_SHORT_GET_LOW(USB_DESCRIPTOR_LENGTH_HID_KEYBOARD_REPORT),
    USB_SHORT_GET_HIGH(USB_DESCRIPTOR_LENGTH_HID_KEYBOARD_REPORT),
    /* Numeric expression that is the total size of the
       Report descriptor. */
    USB_DESCRIPTOR_LENGTH_ENDPOINT, /* Size of this descriptor in bytes */
    USB_DESCRIPTOR_TYPE_ENDPOINT,   /* ENDPOINT Descriptor Type */
    USB_HID_KEYBOARD_ENDPOINT_IN | (USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT),
    /* The address of the endpoint on the USB device
       described by this descriptor. */
    USB_ENDPOINT_INTERRUPT, /* This field describes the endpoint's attributes */
    USB_SHORT_GET_LOW(FS_HID_KEYBOARD_INTERRUPT_IN_PACKET_SIZE),
    USB_SHORT_GET_HIGH(FS_HID_KEYBOARD_INTERRUPT_IN_PACKET_SIZE),
    /* Maximum packet size this endpoint is capable of
       sending or receiving when this configuration is
       selected. */
    FS_HID_KEYBOARD_INTERRUPT_IN_INTERVAL, /* Interval for polling endpoint for data transfers. */
};

uint8_t g_UsbDeviceHidMouseReportDescriptor[USB_DESCRIPTOR_LENGTH_HID_MOUSE_REPORT] = {
    0x05U, 0x01U, /* Usage Page (Generic Desktop)*/
    0x09U, 0x02U, /* Usage (Mouse) */
    0xA1U, 0x01U, /* Collection (Application) */
    0x09U, 0x01U, /* Usage (Pointer) */

    0xA1U, 0x00U, /* Collection (Physical) */
    0x05U, 0x09U, /* Usage Page (Buttons) */
    0x19U, 0x01U, /* Usage Minimum (01U) */
    0x29U, 0x03U, /* Usage Maximum (03U) */

    0x15U, 0x00U, /* logical Minimum (0U) */
    0x25U, 0x01U, /* logical Maximum (1U) */
    0x95U, 0x03U, /* Report Count (3U) */
    0x75U, 0x01U, /* Report Size (1U) */

    0x81U, 0x02U, /* Input(Data, Variable, Absolute) 3U button bit fields */
    0x95U, 0x01U, /* Report count (1U) */
    0x75U, 0x05U, /* Report Size (5U) */
    0x81U, 0x01U, /* Input (Constant), 5U constant field */

    0x05U, 0x01U, /* Usage Page (Generic Desktop) */
    0x09U, 0x30U, /* Usage (X) */
    0x09U, 0x31U, /* Usage (Y) */
    0x09U, 0x38U, /* Usage (Z) */

    0x15U, 0x81U, /* Logical Minimum (-127) */
    0x25U, 0x7FU, /* Logical Maximum (127) */
    0x75U, 0x08U, /* Report Size (8U) */
    0x95U, 0x03U, /* Report Count (3U) */

    0x81U, 0x06U, /* Input(Data, Variable, Relative), three position bytes (X & Y & Z)*/
    0xC0U,        /* end collection, Close Pointer collection*/
    0xC0U         /* end collection, Close Mouse collection */
};

/* HID keyboard report descriptor */
uint8_t g_UsbDeviceHidKeyboardReportDescriptor[USB_DESCRIPTOR_LENGTH_HID_KEYBOARD_REPORT] = {
    0x05U, 0x01U, /* Usage Page (Generic Desktop)*/
    0x09U, 0x06U, /* Usage (Keyboard) */
    0xA1U, 0x01U, /* Collection (Application) */
    0x75U, 0x01U, /* Report Size (1U) */
    0x95U, 0x08U, /* Report Count (8U) */
    0x05U, 0x07U, /* Usage Page (Key Codes) */
    0x19U, 0xE0U, /* Usage Minimum (224U) */
    0x29U, 0xE7U, /* Usage Maximum (231U) */

    0x15U, 0x00U, /* Logical Minimum (0U) */
    0x25U, 0x01U, /* Logical Maximum (1U) */
    0x81U, 0x02U, /* Input(Data, Variable, Absolute) Modifier byte */

    0x95U, 0x01U, /* Report count (1U) */
    0x75U, 0x08U, /* Report Size (8U) */
    0x81U, 0x01U, /* Input (Constant), Reserved byte */
    0x95U, 0x05U, /* Report count (5U) */
    0x75U, 0x01U, /* Report Size (1U) */

    0x05U, 0x01U, /* Usage Page (Page# for LEDs) */
    0x19U, 0x01U, /* Usage Minimum (1U) */
    0x29U, 0x05U, /* Usage Maximum (5U) */
    0x91U, 0x02U, /* Output (Data, Variable, Absolute) LED report */
    0x95U, 0x01U, /* Report count (1U) */
    0x75U, 0x03U, /* Report Size (3U) */
    0x91U, 0x01U, /* Output (Constant), LED report padding */

    0x95U, 0x06U, /* Report count (6U) */
    0x75U, 0x08U, /* Report Size (8U) */
    0x15U, 0x00U, /* logical Minimum (0U) */
    0x25U, 0xFFU, /* logical Maximum (255U) */
    0x05U, 0x07U, /* Usage Page (Key Codes) */
    0x19U, 0x00U, /* Usage Minimum (0U) */
    0x29U, 0xFFU, /* Usage Maximum (255U) */

    0x81U, 0x00U, /* Input(Data, Array), Key arrays(6U bytes)*/
    0xC0U,        /* end collection */
};

uint8_t g_UsbDeviceString0[USB_DESCRIPTOR_LENGTH_STRING0] = {
    sizeof(g_UsbDeviceString0), USB_DESCRIPTOR_TYPE_STRING, 0x09U, 0x04U,
};

uint8_t g_UsbDeviceString1[USB_DESCRIPTOR_LENGTH_STRING1] = {
    sizeof(g_UsbDeviceString1),
    USB_DESCRIPTOR_TYPE_STRING,
    'F',
    0x00U,
    'R',
    0x00U,
    'E',
    0x00U,
    'E',
    0x00U,
    'S',
    0x00U,
    'C',
    0x00U,
    'A',
    0x00U,
    'L',
    0x00U,
    'E',
    0x00U,
    ' ',
    0x00U,
    'S',
    0x00U,
    'E',
    0x00U,
    'M',
    0x00U,
    'I',
    0x00U,
    'C',
    0x00U,
    'O',
    0x00U,
    'N',
    0x00U,
    'D',
    0x00U,
    'U',
    0x00U,
    'C',
    0x00U,
    'T',
    0x00U,
    'O',
    0x00U,
    'R',
    0x00U,
    ' ',
    0x00U,
    'I',
    0x00U,
    'N',
    0x00U,
    'C',
    0x00U,
    '.',
    0x00U,
};

uint8_t g_UsbDeviceString2[USB_DESCRIPTOR_LENGTH_STRING2] = {
    sizeof(g_UsbDeviceString2),
    USB_DESCRIPTOR_TYPE_STRING,
    'C',
    0x00U,
    'O',
    0x00U,
    'M',
    0x00U,
    'P',
    0x00U,
    'O',
    0x00U,
    'S',
    0x00U,
    'I',
    0x00U,
    'T',
    0x00U,
    'E',
    0x00U,
    ' ',
    0x00U,
    'D',
    0x00U,
    'E',
    0x00U,
    'V',
    0x00U,
    'I',
    0x00U,
    'C',
    0x00U,
    'E',
    0x00U,
};

uint8_t g_UsbDeviceString3[USB_DESCRIPTOR_LENGTH_STRING3] = {
    sizeof(g_UsbDeviceString3),
    USB_DESCRIPTOR_TYPE_STRING,
    'H',
    0x00U,
    'I',
    0x00U,
    'D',
    0x00U,
    ' ',
    0x00U,
    'M',
    0x00U,
    'O',
    0x00U,
    'U',
    0x00U,
    'S',
    0x00U,
    'E',
    0x00U,
    ' ',
    0x00U,
    'D',
    0x00U,
    'E',
    0x00U,
    'V',
    0x00U,
    'I',
    0x00U,
    'C',
    0x00U,
    'E',
    0x00U,
};

uint8_t g_UsbDeviceString4[USB_DESCRIPTOR_LENGTH_STRING4] = {
    sizeof(g_UsbDeviceString4),
    USB_DESCRIPTOR_TYPE_STRING,
    'H',
    0x00U,
    'I',
    0x00U,
    'D',
    0x00U,
    ' ',
    0x00U,
    'K',
    0x00U,
    'E',
    0x00U,
    'Y',
    0x00U,
    'B',
    0x00U,
    'O',
    0x00U,
    'A',
    0x00U,
    'R',
    0x00U,
    'D',
    0x00U,
    ' ',
    0x00U,
    'D',
    0x00U,
    'E',
    0x00U,
    'V',
    0x00U,
    'I',
    0x00U,
    'C',
    0x00U,
    'E',
    0x00U,
};

uint32_t g_UsbDeviceStringDescriptorLength[USB_DEVICE_STRING_COUNT] = {
    sizeof(g_UsbDeviceString0), sizeof(g_UsbDeviceString1), sizeof(g_UsbDeviceString2),
    sizeof(g_UsbDeviceString3), sizeof(g_UsbDeviceString4),
};

uint8_t *g_UsbDeviceStringDescriptorArray[USB_DEVICE_STRING_COUNT] = {
    g_UsbDeviceString0, g_UsbDeviceString1, g_UsbDeviceString2, g_UsbDeviceString3, g_UsbDeviceString4,
};

usb_language_t g_UsbDeviceLanguage[USB_DEVICE_LANGUAGE_COUNT] = {{
    g_UsbDeviceStringDescriptorArray, g_UsbDeviceStringDescriptorLength, (uint16_t)0x0409U,
}};

usb_language_list_t g_UsbDeviceLanguageList = {
    g_UsbDeviceString0, sizeof(g_UsbDeviceString0), g_UsbDeviceLanguage, USB_DEVICE_LANGUAGE_COUNT,
};

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Get device descriptor request */
usb_status_t USB_DeviceGetDeviceDescriptor(usb_device_handle handle,
                                           usb_device_get_device_descriptor_struct_t *deviceDescriptor)
{
    deviceDescriptor->buffer = g_UsbDeviceDescriptor;
    deviceDescriptor->length = USB_DESCRIPTOR_LENGTH_DEVICE;
    return kStatus_USB_Success;
}

/* Get device configuration descriptor request */
usb_status_t USB_DeviceGetConfigurationDescriptor(
    usb_device_handle handle, usb_device_get_configuration_descriptor_struct_t *configurationDescriptor)
{
    if (USB_COMPOSITE_CONFIGURE_INDEX > configurationDescriptor->configuration)
    {
        configurationDescriptor->buffer = g_UsbDeviceConfigurationDescriptor;
        configurationDescriptor->length = USB_DESCRIPTOR_LENGTH_CONFIGURATION_ALL;
        return kStatus_USB_Success;
    }
    return kStatus_USB_InvalidRequest;
}

/* Get device string descriptor request */
usb_status_t USB_DeviceGetStringDescriptor(usb_device_handle handle,
                                           usb_device_get_string_descriptor_struct_t *stringDescriptor)
{
    if (stringDescriptor->stringIndex == 0U)
    {
        stringDescriptor->buffer = (uint8_t *)g_UsbDeviceLanguageList.languageString;
        stringDescriptor->length = g_UsbDeviceLanguageList.stringLength;
    }
    else
    {
        uint8_t languageId = 0U;
        uint8_t languageIndex = USB_DEVICE_STRING_COUNT;

        for (; languageId < USB_DEVICE_STRING_COUNT; languageId++)
        {
            if (stringDescriptor->languageId == g_UsbDeviceLanguageList.languageList[languageId].languageId)
            {
                if (stringDescriptor->stringIndex < USB_DEVICE_STRING_COUNT)
                {
                    languageIndex = stringDescriptor->stringIndex;
                }
                break;
            }
        }

        if (USB_DEVICE_STRING_COUNT == languageIndex)
        {
            return kStatus_USB_InvalidRequest;
        }
        stringDescriptor->buffer = (uint8_t *)g_UsbDeviceLanguageList.languageList[languageId].string[languageIndex];
        stringDescriptor->length = g_UsbDeviceLanguageList.languageList[languageId].length[languageIndex];
    }
    return kStatus_USB_Success;
}

/* Get hid descriptor request */
usb_status_t USB_DeviceGetHidDescriptor(usb_device_handle handle, usb_device_get_hid_descriptor_struct_t *hidDescriptor)
{
    return kStatus_USB_InvalidRequest;
}

/* Get hid report descriptor request */
usb_status_t USB_DeviceGetHidReportDescriptor(usb_device_handle handle,
                                              usb_device_get_hid_report_descriptor_struct_t *hidReportDescriptor)
{
    if (USB_HID_MOUSE_INTERFACE_INDEX == hidReportDescriptor->interfaceNumber)
    {
        hidReportDescriptor->buffer = g_UsbDeviceHidMouseReportDescriptor;
        hidReportDescriptor->length = USB_DESCRIPTOR_LENGTH_HID_MOUSE_REPORT;
    }
    else if (USB_HID_KEYBOARD_INTERFACE_INDEX == hidReportDescriptor->interfaceNumber)
    {
        hidReportDescriptor->buffer = g_UsbDeviceHidKeyboardReportDescriptor;
        hidReportDescriptor->length = USB_DESCRIPTOR_LENGTH_HID_KEYBOARD_REPORT;
    }
    else
    {
        return kStatus_USB_InvalidRequest;
    }
    return kStatus_USB_Success;
}

/* Get hid physical descriptor request */
usb_status_t USB_DeviceGetHidPhysicalDescriptor(usb_device_handle handle,
                                                usb_device_get_hid_physical_descriptor_struct_t *hidPhysicalDescriptor)
{
    return kStatus_USB_InvalidRequest;
}

/* Due to the difference of HS and FS descriptors, the device descriptors and configurations need to be updated to match
 * current speed.
 * As the default, the device descriptors and configurations are configured by using FS parameters for both EHCI and
 * KHCI.
 * When the EHCI is enabled, the application needs to call this fucntion to update device by using current speed.
 * The updated information includes endpoint max packet size, endpoint interval, etc. */
usb_status_t USB_DeviceSetSpeed(usb_device_handle handle, uint8_t speed)
{
    usb_descriptor_union_t *descriptorHead;
    usb_descriptor_union_t *descriptorTail;

    descriptorHead = (usb_descriptor_union_t *)&g_UsbDeviceConfigurationDescriptor[0];
    descriptorTail =
        (usb_descriptor_union_t *)(&g_UsbDeviceConfigurationDescriptor[USB_DESCRIPTOR_LENGTH_CONFIGURATION_ALL - 1U]);

    while (descriptorHead < descriptorTail)
    {
        if (descriptorHead->common.bDescriptorType == USB_DESCRIPTOR_TYPE_ENDPOINT)
        {
            if (USB_SPEED_HIGH == speed)
            {
                if (((descriptorHead->endpoint.bEndpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_IN) ==
                     USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_IN) &&
                    (USB_HID_MOUSE_ENDPOINT_IN ==
                     (descriptorHead->endpoint.bEndpointAddress & USB_ENDPOINT_NUMBER_MASK)))
                {
                    descriptorHead->endpoint.bInterval = HS_HID_MOUSE_INTERRUPT_IN_INTERVAL;
                    USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(HS_HID_MOUSE_INTERRUPT_IN_PACKET_SIZE,
                                                       descriptorHead->endpoint.wMaxPacketSize);
                }
                else if (((descriptorHead->endpoint.bEndpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_IN) ==
                          USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_IN) &&
                         (USB_HID_KEYBOARD_ENDPOINT_IN ==
                          (descriptorHead->endpoint.bEndpointAddress & USB_ENDPOINT_NUMBER_MASK)))
                {
                    descriptorHead->endpoint.bInterval = HS_HID_KEYBOARD_INTERRUPT_IN_INTERVAL;
                    USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(HS_HID_KEYBOARD_INTERRUPT_IN_PACKET_SIZE,
                                                       descriptorHead->endpoint.wMaxPacketSize);
                }
                else
                {
                }
            }
            else
            {
                if (((descriptorHead->endpoint.bEndpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_IN) ==
                     USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_IN) &&
                    (USB_HID_MOUSE_ENDPOINT_IN ==
                     (descriptorHead->endpoint.bEndpointAddress & USB_ENDPOINT_NUMBER_MASK)))
                {
                    descriptorHead->endpoint.bInterval = FS_HID_MOUSE_INTERRUPT_IN_INTERVAL;
                    USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(FS_HID_MOUSE_INTERRUPT_IN_PACKET_SIZE,
                                                       descriptorHead->endpoint.wMaxPacketSize);
                }
                else if (((descriptorHead->endpoint.bEndpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_IN) ==
                          USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_IN) &&
                         (USB_HID_KEYBOARD_ENDPOINT_IN ==
                          (descriptorHead->endpoint.bEndpointAddress & USB_ENDPOINT_NUMBER_MASK)))
                {
                    descriptorHead->endpoint.bInterval = FS_HID_KEYBOARD_INTERRUPT_IN_INTERVAL;
                    USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(FS_HID_KEYBOARD_INTERRUPT_IN_PACKET_SIZE,
                                                       descriptorHead->endpoint.wMaxPacketSize);
                }
                else
                {
                }
            }
        }
        descriptorHead = (usb_descriptor_union_t *)((uint8_t *)descriptorHead + descriptorHead->common.bLength);
    }

    if (USB_SPEED_HIGH == speed)
    {
        g_UsbDeviceHidMouseEndpoints[0].maxPacketSize = HS_HID_MOUSE_INTERRUPT_IN_PACKET_SIZE;
    }
    else
    {
        g_UsbDeviceHidMouseEndpoints[0].maxPacketSize = FS_HID_MOUSE_INTERRUPT_IN_PACKET_SIZE;
    }

    if (USB_SPEED_HIGH == speed)
    {
        g_UsbDeviceHidKeyboardEndpoints[0].maxPacketSize = HS_HID_KEYBOARD_INTERRUPT_IN_PACKET_SIZE;
    }
    else
    {
        g_UsbDeviceHidKeyboardEndpoints[0].maxPacketSize = FS_HID_KEYBOARD_INTERRUPT_IN_PACKET_SIZE;
    }

    return kStatus_USB_Success;
}

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
#include "usb_device_msc.h"
#include "bootloader_hid_report_ids.h"

#include "usb_descriptor.h"

#define BL_MIN_PACKET_SIZE (32)
#define BL_PACKET_SIZE_HEADER_SIZE (3) // alignment byte + length lsb + length msb (does not include report id)
#define BL_REPORT_SIZE (BL_MIN_PACKET_SIZE + BL_PACKET_SIZE_HEADER_SIZE)

/* hidtc data buffer out report descriptor */
#define HID_USAGE_HIDTC_DATA_OUT(__id, __count, __size)          \
    0x85, ((uint8_t)(__id)),        /*	 REPORT_ID (__id) */      \
        0x19, 0x01,                 /*   USAGE_MINIMUM (1)*/     \
        0x29, 0x01,                 /*   USAGE_MAXIMUM (1)*/     \
        0x15, 0x00,                 /*   LOGICAL_MINIMUM (0)*/   \
        0x26, 0xff, 0x00,           /*   LOGICAL_MAXIMUM (255)*/ \
        0x75, ((uint8_t)(__size)),  /*	 REPORT_SIZE (n)*/        \
        0x95, ((uint8_t)(__count)), /*	 REPORT_COUNT (n)*/       \
        0x91, 0x02                  /*   OUTPUT (Data,Var,Abs) */

/* hidtc data buffer in report descriptor */
#define HID_USAGE_HIDTC_DATA_IN(__id, __count, __size)           \
    0x85, ((uint8_t)(__id)),        /*	 REPORT_ID (__id) */      \
        0x19, 0x01,                 /*   USAGE_MINIMUM (1)*/     \
        0x29, 0x01,                 /*   USAGE_MAXIMUM (1)*/     \
        0x15, 0x00,                 /*   LOGICAL_MINIMUM (0)*/   \
        0x26, 0xff, 0x00,           /*   LOGICAL_MAXIMUM (255)*/ \
        0x75, ((uint8_t)(__size)),  /*	 REPORT_SIZE (n)*/        \
        0x95, ((uint8_t)(__count)), /*	 REPORT_COUNT (n)*/       \
        0x81, 0x02                  /*   INPUT (Data,Var,Abs) */

/* hid device information */
/* hid generic endpoint information */
usb_device_endpoint_struct_t g_hid_generic_endpoints[USB_HID_GENERIC_ENDPOINT_COUNT] = {
    /* HID generic interrupt IN pipe */
    {
        USB_HID_GENERIC_ENDPOINT_IN | (USB_IN << 7), USB_ENDPOINT_INTERRUPT, FS_HID_GENERIC_INTERRUPT_IN_PACKET_SIZE,
    },
    /* HID generic interrupt OUT pipe */
    {
        USB_HID_GENERIC_ENDPOINT_OUT | (USB_OUT << 7), USB_ENDPOINT_INTERRUPT, FS_HID_GENERIC_INTERRUPT_OUT_PACKET_SIZE,
    }
};

/* HID generic interface information */
usb_device_interface_struct_t g_hid_generic_interface[] = { {
    0, /* The alternate setting of the interface */
    {
        USB_HID_GENERIC_ENDPOINT_COUNT, /* Endpoint count */
        g_hid_generic_endpoints,        /* Endpoints handle */
    },
} };

usb_device_interfaces_struct_t g_hid_generic_interfaces[USB_HID_GENERIC_INTERFACE_COUNT] = { {
    USB_HID_GENERIC_CLASS,           /* HID generic class code */
    USB_HID_GENERIC_SUBCLASS,        /* HID generic subclass code */
    USB_HID_GENERIC_PROTOCOL,        /* HID generic protocol code */
    USB_HID_GENERIC_INTERFACE_INDEX, /* The interface number of the HID generic */
    g_hid_generic_interface,         /* Interfaces handle */
    sizeof(g_hid_generic_interface) / sizeof(usb_device_interfaces_struct_t),
} };

usb_device_interface_list_t g_hid_generic_interface_list[USB_CONFIGURE_COUNT] = {
    {
        USB_HID_GENERIC_INTERFACE_COUNT, /* The interface count of the HID generic */
        g_hid_generic_interfaces,        /* The interfaces handle */
    },
};

usb_device_class_struct_t g_hid_generic_class = {
    g_hid_generic_interface_list, /* The interface list of the HID generic */
    kUSB_DeviceClassTypeHid,      /* The HID class type */
    USB_CONFIGURE_COUNT,          /* The configuration count */
};

/* msc disk information */
/* Define endpoint for MSC class */
usb_device_endpoint_struct_t g_msc_disk_endpoints[USB_MSC_ENDPOINT_COUNT] = {
    {
        USB_MSC_BULK_IN_ENDPOINT | (USB_IN << 7), USB_ENDPOINT_BULK, FS_BULK_IN_PACKET_SIZE,
    },
    {
        USB_MSC_BULK_OUT_ENDPOINT | (USB_OUT << 7), USB_ENDPOINT_BULK, FS_BULK_OUT_PACKET_SIZE,
    }
};

/* Define interface for MSC class */
usb_device_interface_struct_t g_msc_disk_interface[] = { {
    0,
    {
        USB_MSC_ENDPOINT_COUNT, g_msc_disk_endpoints,
    },
} };

/* Define interfaces for MSC disk */
usb_device_interfaces_struct_t g_msc_disk_interfaces[USB_MSC_INTERFACE_COUNT] = { {
    USB_MSC_CLASS, USB_MSC_SUBCLASS, USB_MSC_PROTOCOL, USB_MSC_INTERFACE_INDEX, g_msc_disk_interface,
    sizeof(g_msc_disk_interface) / sizeof(usb_device_interfaces_struct_t),
} };

/* Define configurations for MSC disk */
usb_device_interface_list_t g_msc_disk_interface_list[USB_CONFIGURE_COUNT] = {
    {
        USB_MSC_INTERFACE_COUNT, g_msc_disk_interfaces,
    },
};

/* Define class information for MSC disk */
usb_device_class_struct_t g_msc_class = {
    g_msc_disk_interface_list, kUSB_DeviceClassTypeMsc, USB_CONFIGURE_COUNT,
};

uint8_t g_hid_generic_report_descriptor[USB_HID_REPORT_DESC_SIZE] = {
    0x06,
    0x00,
    0xFF, /* Usage Page (Vendor Defined Page 1)*/
    0x09,
    0x01, /* USAGE (Vendor 1) */
    0xA1,
    0x01, /* Collection (Application) */
    HID_USAGE_HIDTC_DATA_OUT(kBootloaderReportID_CommandOut, BL_REPORT_SIZE, 8),
    HID_USAGE_HIDTC_DATA_OUT(kBootloaderReportID_DataOut, BL_REPORT_SIZE, 8),
    HID_USAGE_HIDTC_DATA_IN(kBootloaderReportID_CommandIn, BL_REPORT_SIZE, 8),
    HID_USAGE_HIDTC_DATA_IN(kBootloaderReportID_DataIn, BL_REPORT_SIZE, 8),
    0xC0 /* end collection */
};

/* Define device descriptor */
uint8_t g_device_descriptor[USB_DEVICE_DESCRIPTOR_LENGTH] = {
    /* "Device Descriptor Size */
    USB_DEVICE_DESCRIPTOR_LENGTH,
    /* "Device" Type of descriptor */
    USB_DESCRIPTOR_TYPE_DEVICE,
    /*  BCD USB version  */
    USB_SHORT_GET_LOW(USB_BCD_VERSION), USB_SHORT_GET_HIGH(USB_BCD_VERSION),
    /* Device Class is indicated in the interface descriptors */
    USB_DEVICE_CLASS,
    /*  Device Subclass is indicated in the interface descriptors  */
    USB_DEVICE_SUBCLASS,
    /*  Device Protocol  */
    USB_DEVICE_PROTOCOL,
    /* Max Packet size */
    USB_CONTROL_MAX_PACKET_SIZE,
    /* Vendor ID */
    0xa2, 0x15, /*  Vendor ID for Freescale       */
    /* Product ID */
    0x73, 0x00, /* 0x73,0x00,ProductID for KL25Z48M */
    /* BCD Device version */
    0x02, 0x00,
    /* Manufacturer string index */
    0x01,
    /* Product string index */
    0x02,
/*  Serial number string index */
#if (USB_DEVICE_CONFIG_MSC > 0)
    0x03,
#else
    0x00,
#endif
    /*  Number of configurations */
    USB_CONFIGURE_COUNT,
};

/* Define configuration descriptor */
uint8_t g_config_descriptor[USB_CONFIGURE_DESCRIPTOR_LENGTH] = {
    /* Configuration Descriptor Size*/
    USB_CONFIGURE_ONLY_DESCRIPTOR_LENGTH,
    /* "Configuration" type of descriptor */
    USB_DESCRIPTOR_TYPE_CONFIGURE,
    /*  Total length of the Configuration descriptor */
    USB_SHORT_GET_LOW(USB_CONFIGURE_DESCRIPTOR_LENGTH), USB_SHORT_GET_HIGH(USB_CONFIGURE_DESCRIPTOR_LENGTH),
    /*  NumInterfaces */
    USB_COMPOSITE_INTERFACE_COUNT,
    /*  Configuration Value */
    USB_COMPOSITE_CONFIGURE_INDEX,
    /* Configuration Description String Index */
    0,
    /*  Attributes.support RemoteWakeup and self power */
    (USB_DESCRIPTOR_CONFIGURE_ATTRIBUTE_D7_MASK) |
        (USB_DEVICE_CONFIG_SELF_POWER << USB_DESCRIPTOR_CONFIGURE_ATTRIBUTE_SELF_POWERED_SHIFT) |
        (USB_DEVICE_CONFIG_REMOTE_WAKEUP << USB_DESCRIPTOR_CONFIGURE_ATTRIBUTE_REMOTE_WAKEUP_SHIFT),
    /*  Current draw from bus */
    USB_CONFIGURE_DRAWN,

#if USB_DEVICE_CONFIG_HID
    /* Interface Descriptor */
    USB_INTERFACE_DESCRIPTOR_LENGTH, USB_DESCRIPTOR_TYPE_INTERFACE, USB_HID_GENERIC_INTERFACE_INDEX, 0x00,
    USB_HID_GENERIC_ENDPOINT_COUNT, USB_HID_GENERIC_CLASS, USB_HID_GENERIC_SUBCLASS, USB_HID_GENERIC_PROTOCOL, 0x03,

    /* HID descriptor */
    USB_HID_DESCRIPTOR_LENGTH, USB_DESCRIPTOR_TYPE_HID, 0x00, 0x01, 0x00, 0x01, USB_DESCRIPTOR_TYPE_HID_REPORT,
    USB_SHORT_GET_LOW(USB_HID_REPORT_DESC_SIZE), USB_SHORT_GET_HIGH(USB_HID_REPORT_DESC_SIZE),

    /*Endpoint descriptor */
    USB_ENDPOINT_DESCRIPTOR_LENGTH, USB_DESCRIPTOR_TYPE_ENDPOINT, USB_HID_GENERIC_ENDPOINT_IN | (USB_IN << 7),
    USB_ENDPOINT_INTERRUPT, FS_HID_GENERIC_INTERRUPT_IN_PACKET_SIZE, 0x00, FS_HID_GENERIC_INTERRUPT_IN_INTERVAL,

    /*Endpoint descriptor */
    USB_ENDPOINT_DESCRIPTOR_LENGTH, USB_DESCRIPTOR_TYPE_ENDPOINT, USB_HID_GENERIC_ENDPOINT_OUT | (USB_OUT << 7),
    USB_ENDPOINT_INTERRUPT, FS_HID_GENERIC_INTERRUPT_OUT_PACKET_SIZE, 0x00, FS_HID_GENERIC_INTERRUPT_OUT_INTERVAL,

#endif // USB_DEVICE_CONFIG_HID

#if USB_DEVICE_CONFIG_MSC
    /* MSC Interface Descriptor */
    USB_INTERFACE_DESCRIPTOR_LENGTH, USB_DESCRIPTOR_TYPE_INTERFACE, USB_MSC_INTERFACE_INDEX, 0x00,
    USB_MSC_ENDPOINT_COUNT, USB_MSC_CLASS, USB_MSC_SUBCLASS, USB_MSC_PROTOCOL,
    0x03, /* Interface Description String Index*/

    /*Bulk IN Endpoint descriptor */
    USB_ENDPOINT_DESCRIPTOR_LENGTH, USB_DESCRIPTOR_TYPE_ENDPOINT, USB_MSC_BULK_IN_ENDPOINT | (USB_IN << 7),
    USB_ENDPOINT_BULK,

    USB_SHORT_GET_LOW(FS_BULK_IN_PACKET_SIZE), USB_SHORT_GET_HIGH(FS_BULK_IN_PACKET_SIZE),
    0x00, /* This value is ignored for Bulk ENDPOINT */

    /*Bulk OUT Endpoint descriptor */
    USB_ENDPOINT_DESCRIPTOR_LENGTH, USB_DESCRIPTOR_TYPE_ENDPOINT, USB_MSC_BULK_OUT_ENDPOINT | (USB_OUT << 7),
    USB_ENDPOINT_BULK, USB_SHORT_GET_LOW(FS_BULK_OUT_PACKET_SIZE), USB_SHORT_GET_HIGH(FS_BULK_OUT_PACKET_SIZE),
    0x00 /* This value is ignored for Bulk ENDPOINT */
#endif   // USB_DEVICE_CONFIG_HID
};

/* Define string descriptor */
uint8_t g_usb_str_0[USB_STRING_DESCRIPTOR_0_LENGTH + USB_STRING_DESCRIPTOR_HEADER_LENGTH] = {
    sizeof(g_usb_str_0), USB_DESCRIPTOR_TYPE_STRING, 0x09, 0x04
};

uint8_t g_usb_str_1[USB_STRING_DESCRIPTOR_1_LENGTH + USB_STRING_DESCRIPTOR_HEADER_LENGTH] = {
    sizeof(g_usb_str_1),
    USB_DESCRIPTOR_TYPE_STRING,
    'F',
    0,
    'R',
    0,
    'E',
    0,
    'E',
    0,
    'S',
    0,
    'C',
    0,
    'A',
    0,
    'L',
    0,
    'E',
    0,
    ' ',
    0,
    'S',
    0,
    'E',
    0,
    'M',
    0,
    'I',
    0,
    'C',
    0,
    'O',
    0,
    'N',
    0,
    'D',
    0,
    'U',
    0,
    'C',
    0,
    'T',
    0,
    'O',
    0,
    'R',
    0,
    ' ',
    0,
    'I',
    0,
    'N',
    0,
    'C',
    0,
    '.',
    0
};

uint8_t g_usb_str_2[USB_STRING_DESCRIPTOR_2_LENGTH + USB_STRING_DESCRIPTOR_HEADER_LENGTH] = {
    sizeof(g_usb_str_2),
    USB_DESCRIPTOR_TYPE_STRING,
    'U',
    0,
    'S',
    0,
    'B',
    0,
    ' ',
    0,
    'C',
    0,
    'O',
    0,
    'M',
    0,
    'P',
    0,
    'O',
    0,
    'S',
    0,
    'I',
    0,
    'T',
    0,
    'E',
    0,
    ' ',
    0,
    'D',
    0,
    'E',
    0,
    'V',
    0,
    'I',
    0,
    'C',
    0,
    'E',
    0
};

#if ((USB_DEVICE_CONFIG_MSC > 0U) && (USB_DEVICE_CONFIG_HID > 0U)) // MSC + HID
uint8_t g_usb_str_3[USB_STRING_DESCRIPTOR_3_LENGTH + USB_STRING_DESCRIPTOR_HEADER_LENGTH] = {
    sizeof(g_usb_str_3),
    USB_DESCRIPTOR_TYPE_STRING,
    'M',
    0,
    'C',
    0,
    'U',
    0,
    ' ',
    0,
    'M',
    0,
    'S',
    0,
    'C',
    0,
    ' ',
    0,
    'A',
    0,
    'N',
    0,
    'D',
    0,
    ' ',
    0,
    'H',
    0,
    'I',
    0,
    'D',
    0,
    ' ',
    0,
    'G',
    0,
    'E',
    0,
    'N',
    0,
    'E',
    0,
    'R',
    0,
    'I',
    0,
    'C',
    0,
    ' ',
    0,
    'D',
    0,
    'E',
    0,
    'V',
    0,
    'I',
    0,
    'C',
    0,
    'E',
    0
};
#elif((USB_DEVICE_CONFIG_MSC == 0U) && (USB_DEVICE_CONFIG_HID > 0U)) // Only HID
uint8_t g_usb_str_3[USB_STRING_DESCRIPTOR_3_LENGTH + USB_STRING_DESCRIPTOR_HEADER_LENGTH] = {
    sizeof(g_usb_str_3),
    USB_DESCRIPTOR_TYPE_STRING,
    'M',
    0,
    'C',
    0,
    'U',
    0,
    ' ',
    0,
    'H',
    0,
    'I',
    0,
    'D',
    0,
    ' ',
    0,
    'G',
    0,
    'E',
    0,
    'N',
    0,
    'E',
    0,
    'R',
    0,
    'I',
    0,
    'C',
    0,
    ' ',
    0,
    'D',
    0,
    'E',
    0,
    'V',
    0,
    'I',
    0,
    'C',
    0,
    'E',
    0
};
#elif((USB_DEVICE_CONFIG_MSC > 0U) && (USB_DEVICE_CONFIG_HID == 0U)) // Only MSC
uint8_t g_usb_str_3[USB_STRING_DESCRIPTOR_3_LENGTH + USB_STRING_DESCRIPTOR_HEADER_LENGTH] = {
    sizeof(g_usb_str_3),
    USB_DESCRIPTOR_TYPE_STRING,
    'M',
    0,
    'C',
    0,
    'U',
    0,
    ' ',
    0,
    'M',
    0,
    'S',
    0,
    'C',
    0,
    ' ',
    0,
    'D',
    0,
    'E',
    0,
    'V',
    0,
    'I',
    0,
    'C',
    0,
    'E',
    0
};
#else                                                                // None
uint8_t g_usb_str_3[USB_STRING_DESCRIPTOR_3_LENGTH + USB_STRING_DESCRIPTOR_HEADER_LENGTH] = {
    sizeof(g_usb_str_3), USB_DESCRIPTOR_TYPE_STRING, ' ', 0,
};
#endif

uint8_t g_usb_str_n[USB_STRING_DESCRIPTOR_ERROR_LENGTH + USB_STRING_DESCRIPTOR_HEADER_LENGTH] = {
    sizeof(g_usb_str_n),
    USB_DESCRIPTOR_TYPE_STRING,
    'B',
    0,
    'A',
    0,
    'D',
    0,
    ' ',
    0,
    'S',
    0,
    'T',
    0,
    'R',
    0,
    'I',
    0,
    'N',
    0,
    'G',
    0
};

/* Define string descriptor size */
uint32_t g_string_desc_size[USB_STRING_COUNT + 1] = { sizeof(g_usb_str_0), sizeof(g_usb_str_1), sizeof(g_usb_str_2),
                                                      sizeof(g_usb_str_3), sizeof(g_usb_str_n) };

uint8_t *g_string_descriptors[USB_STRING_COUNT + 1] = { g_usb_str_0, g_usb_str_1, g_usb_str_2, g_usb_str_3,
                                                        g_usb_str_n };

usb_language_t g_usb_lang[USB_LANGUAGE_COUNT] = { {
    g_string_descriptors, g_string_desc_size, (uint16_t)0x0409,
} };

usb_language_list_t g_language_list = {
    g_usb_str_0, sizeof(g_usb_str_0), g_usb_lang, USB_LANGUAGE_COUNT,
};

usb_language_list_t *g_language_ptr;

/* Get hid descriptor request */
usb_status_t usb_device_get_hid_descriptor(usb_device_handle handle,
                                           usb_device_get_hid_descriptor_struct_t *hid_descriptor)
{
    return kStatus_USB_InvalidRequest;
}

/* Get hid report descriptor request */
usb_status_t usb_device_get_hid_report_descriptor(usb_device_handle handle,
                                                  usb_device_get_hid_report_descriptor_struct_t *hid_report_descriptor)
{
    if (USB_HID_GENERIC_INTERFACE_INDEX == hid_report_descriptor->interfaceNumber)
    {
        hid_report_descriptor->buffer = g_hid_generic_report_descriptor;
        //        hid_report_descriptor->length = USB_HID_REPORT_DESC_SIZE;
        hid_report_descriptor->length = sizeof(g_hid_generic_report_descriptor);
    }
    else
    {
        return kStatus_USB_InvalidRequest;
    }
    return kStatus_USB_Success;
}

/* Get hid physical descriptor request */
usb_status_t usb_device_get_hid_physical_descriptor(
    usb_device_handle handle, usb_device_get_hid_physical_descriptor_struct_t *hid_physical_descriptor)
{
    return kStatus_USB_InvalidRequest;
}

/*!
 * @brief USB device get device descriptor function.
 *
 * This function gets the device descriptor of the USB devcie.
 *
 * @param handle The USB device handle.
 * @param device_descriptor The pointer to the device descriptor structure.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t usb_device_get_device_descriptor(usb_device_handle handle,
                                              usb_device_get_device_descriptor_struct_t *device_descriptor)
{
    device_descriptor->buffer = g_device_descriptor;
    device_descriptor->length = USB_DEVICE_DESCRIPTOR_LENGTH;
    return kStatus_USB_Success;
}

/*!
 * @brief USB device get configuration descriptor function.
 *
 * This function gets the configuration descriptor of the USB devcie.
 *
 * @param handle The USB device handle.
 * @param configuration_descriptor The pointer to the configuration descriptor structure.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t usb_device_get_configuration_descriptor(
    usb_device_handle handle, usb_device_get_configuration_descriptor_struct_t *configuration_descriptor)
{
    //    if (USB_COMPOSITE_CONFIGURE_INDEX > configuration_descriptor->configuration)
    if (USB_HID_GENERIC_CONFIGURE_INDEX > configuration_descriptor->configuration)
    {
        configuration_descriptor->buffer = g_config_descriptor;
        configuration_descriptor->length = USB_CONFIGURE_DESCRIPTOR_LENGTH;
        return kStatus_USB_Success;
    }
    return kStatus_USB_InvalidRequest;
}

/*!
 * @brief USB device get string descriptor function.
 *
 * This function gets the string descriptor of the USB devcie.
 *
 * @param handle The USB device handle.
 * @param string_descriptor Pointer to the string descriptor structure.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t usb_device_get_string_descriptor(usb_device_handle handle,
                                              usb_device_get_string_descriptor_struct_t *string_descriptor)
{
    if (string_descriptor->stringIndex == 0)
    {
        string_descriptor->buffer = (uint8_t *)g_language_list.languageString;
        string_descriptor->length = g_language_list.stringLength;
    }
    else
    {
        uint8_t lang_id = 0;
        uint8_t lang_index = USB_STRING_COUNT;

        for (; lang_id < USB_LANGUAGE_COUNT; lang_id++)
        {
            if (string_descriptor->languageId == g_language_list.languageList[lang_id].languageId)
            {
                if (string_descriptor->stringIndex < USB_STRING_COUNT)
                {
                    lang_index = string_descriptor->stringIndex;
                }
                break;
            }
        }

        if (USB_STRING_COUNT == lang_index)
        {
            return kStatus_USB_InvalidRequest;
        }
        string_descriptor->buffer = (uint8_t *)g_language_list.languageList[lang_id].string[lang_index];
        string_descriptor->length = g_language_list.languageList[lang_id].length[lang_index];
    }
    return kStatus_USB_Success;
}

/*!
 * @brief USB device set speed function.
 *
 * This function sets the speed of the USB devcie.
 *
 * @param handle The USB device handle.
 * @param speed Speed type. USB_SPEED_HIGH/USB_SPEED_FULL/USB_SPEED_LOW.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t usb_device_set_speed(usb_device_handle handle, uint8_t speed)
{
    usb_hid_config_descriptor_t *ptr_hid = NULL;
    usb_msc_config_descriptor_t *ptr_msc = NULL;

#if (USB_DEVICE_CONFIG_HID == 1) && (USB_DEVICE_CONFIG_MSC == 1)
    ptr_hid = (usb_hid_config_descriptor_t *)&g_config_descriptor[USB_HID_CONFIG_INDEX];
    ptr_msc = (usb_msc_config_descriptor_t *)&g_config_descriptor[USB_MSC_CONFIG_INDEX];
#elif(USB_DEVICE_CONFIG_HID == 1) && (USB_DEVICE_CONFIG_MSC == 0)
    // HID only
    //    ptr_msc = NULL;
    ptr_hid = (usb_hid_config_descriptor_t *)&g_config_descriptor[USB_HID_CONFIG_INDEX];
#elif(USB_DEVICE_CONFIG_HID == 0) && (USB_DEVICE_CONFIG_MSC == 1)
    // MSC only
    //    ptr_hid = NULL;
    ptr_msc = (usb_msc_config_descriptor_t *)&g_config_descriptor[USB_MSC_CONFIG_INDEX];
#endif

    if (USB_SPEED_HIGH == speed)
    {
        if (ptr_hid != NULL)
        {
            // HID interface
            USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(HS_HID_GENERIC_INTERRUPT_IN_PACKET_SIZE,
                                               ptr_hid->endpoint_in.wMaxPacketSize);
            ptr_hid->endpoint_in.bInterval = HS_HID_GENERIC_INTERRUPT_IN_INTERVAL;

            USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(HS_HID_GENERIC_INTERRUPT_OUT_PACKET_SIZE,
                                               ptr_hid->endpoint_out.wMaxPacketSize);
            ptr_hid->endpoint_out.bInterval = HS_HID_GENERIC_INTERRUPT_OUT_INTERVAL;
        }
        if (ptr_msc != NULL)
        {
            // MSC interface
            USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(HS_BULK_IN_PACKET_SIZE, ptr_msc->endpoint_in.wMaxPacketSize);
            USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(HS_BULK_OUT_PACKET_SIZE, ptr_msc->endpoint_out.wMaxPacketSize);
        }
    }
    else
    {
        if (ptr_hid != NULL)
        {
            // HID interface
            USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(FS_HID_GENERIC_INTERRUPT_IN_PACKET_SIZE,
                                               ptr_hid->endpoint_in.wMaxPacketSize);
            ptr_hid->endpoint_in.bInterval = FS_HID_GENERIC_INTERRUPT_IN_INTERVAL;

            USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(FS_HID_GENERIC_INTERRUPT_OUT_PACKET_SIZE,
                                               ptr_hid->endpoint_out.wMaxPacketSize);
            ptr_hid->endpoint_out.bInterval = FS_HID_GENERIC_INTERRUPT_OUT_INTERVAL;
        }
        if (ptr_msc != NULL)
        {
            // MSC interface
            USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(FS_BULK_IN_PACKET_SIZE, ptr_msc->endpoint_in.wMaxPacketSize);
            USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(FS_BULK_OUT_PACKET_SIZE, ptr_msc->endpoint_out.wMaxPacketSize);
        }
    }

    for (uint32_t i = 0; i < USB_HID_GENERIC_ENDPOINT_COUNT; i++)
    {
        if (USB_SPEED_HIGH == speed)
        {
            if (g_hid_generic_endpoints[i].endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_IN)
            {
                g_hid_generic_endpoints[i].maxPacketSize = HS_HID_GENERIC_INTERRUPT_IN_PACKET_SIZE;
            }
            else
            {
                g_hid_generic_endpoints[i].maxPacketSize = HS_HID_GENERIC_INTERRUPT_OUT_PACKET_SIZE;
            }
        }
        else
        {
            if (g_hid_generic_endpoints[i].endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_IN)
            {
                g_hid_generic_endpoints[i].maxPacketSize = FS_HID_GENERIC_INTERRUPT_IN_PACKET_SIZE;
            }
            else
            {
                g_hid_generic_endpoints[i].maxPacketSize = FS_HID_GENERIC_INTERRUPT_OUT_PACKET_SIZE;
            }
        }
    }

    for (uint32_t i = 0; i < USB_MSC_ENDPOINT_COUNT; i++)
    {
        if (USB_SPEED_HIGH == speed)
        {
            if ((USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT) ==
                (g_msc_disk_endpoints[i].endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK))
            {
                g_msc_disk_endpoints[i].maxPacketSize = HS_BULK_IN_PACKET_SIZE;
            }
            else
            {
                g_msc_disk_endpoints[i].maxPacketSize = HS_BULK_OUT_PACKET_SIZE;
            }
        }
        else
        {
            if ((USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT) ==
                (g_msc_disk_endpoints[i].endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK))
            {
                g_msc_disk_endpoints[i].maxPacketSize = FS_BULK_IN_PACKET_SIZE;
            }
            else
            {
                g_msc_disk_endpoints[i].maxPacketSize = FS_BULK_OUT_PACKET_SIZE;
            }
        }
    }
    return kStatus_USB_Success;
}

/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016, 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "usb_device_config.h"
#include "usb.h"

#include "usb_device.h"
#include "usb_device_ch9.h"
#include "usb_device_class.h"

#if ((defined(USB_DEVICE_CONFIG_NUM)) && (USB_DEVICE_CONFIG_NUM > 0U))
/* Include the class drivers according to the usb_device_config.h. */
#if ((defined(USB_DEVICE_CONFIG_HID)) && (USB_DEVICE_CONFIG_HID > 0U))
#include "usb_device_hid.h"
#endif

#if ((defined(USB_DEVICE_CONFIG_CDC_ACM)) && (USB_DEVICE_CONFIG_CDC_ACM > 0U))
#include "usb_device_cdc_acm.h"
#endif

#if ((defined(USB_DEVICE_CONFIG_MSC)) && (USB_DEVICE_CONFIG_MSC > 0U))
#include "usb_device_msc.h"
#endif

#if ((defined(USB_DEVICE_CONFIG_MTP)) && (USB_DEVICE_CONFIG_MTP > 0U))
#include "usb_device_mtp.h"
#endif

#if ((defined(USB_DEVICE_CONFIG_AUDIO)) && (USB_DEVICE_CONFIG_AUDIO > 0U))
#include "usb_device_audio.h"
#endif

#if ((defined(USB_DEVICE_CONFIG_PHDC)) && (USB_DEVICE_CONFIG_PHDC > 0U))
#include "usb_device_phdc.h"
#endif

#if ((defined(USB_DEVICE_CONFIG_VIDEO)) && (USB_DEVICE_CONFIG_VIDEO > 0U))
#include "usb_device_video.h"
#endif

#if ((defined(USB_DEVICE_CONFIG_PRINTER)) && (USB_DEVICE_CONFIG_PRINTER > 0U))
#include "usb_device_printer.h"
#endif

#if ((defined(USB_DEVICE_CONFIG_DFU)) && (USB_DEVICE_CONFIG_DFU > 0U))
#include "usb_device_dfu.h"
#endif

#if ((defined(USB_DEVICE_CONFIG_CCID)) && (USB_DEVICE_CONFIG_CCID > 0U))
#include "usb_device_ccid.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static usb_status_t USB_DeviceClassAllocateHandle(uint8_t controllerId, usb_device_common_class_struct_t **handle);
static usb_status_t USB_DeviceClassFreeHandle(uint8_t controllerId);
static usb_status_t USB_DeviceClassGetHandleByControllerId(uint8_t controllerId,
                                                           usb_device_common_class_struct_t **handle);
static usb_status_t USB_DeviceClassGetHandleByDeviceHandle(usb_device_handle deviceHandle,
                                                           usb_device_common_class_struct_t **handle);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* The device class driver list. */
static const usb_device_class_map_t s_UsbDeviceClassInterfaceMap[] = {
#if ((defined(USB_DEVICE_CONFIG_HID)) && (USB_DEVICE_CONFIG_HID > 0U))
    {USB_DeviceHidInit, USB_DeviceHidDeinit, USB_DeviceHidEvent, kUSB_DeviceClassTypeHid},
#endif

#if ((defined(USB_DEVICE_CONFIG_CDC_ACM)) && (USB_DEVICE_CONFIG_CDC_ACM > 0U))
    {USB_DeviceCdcAcmInit, USB_DeviceCdcAcmDeinit, USB_DeviceCdcAcmEvent, kUSB_DeviceClassTypeCdc},
#endif

#if ((defined(USB_DEVICE_CONFIG_MSC)) && (USB_DEVICE_CONFIG_MSC > 0U))
    {USB_DeviceMscInit, USB_DeviceMscDeinit, USB_DeviceMscEvent, kUSB_DeviceClassTypeMsc},
#endif

#if ((defined(USB_DEVICE_CONFIG_MTP)) && (USB_DEVICE_CONFIG_MTP > 0U))
    {USB_DeviceMtpInit, USB_DeviceMtpDeinit, USB_DeviceMtpEvent, kUSB_DeviceClassTypeMtp},
#endif

#if ((defined USB_DEVICE_CONFIG_AUDIO) && (USB_DEVICE_CONFIG_AUDIO > 0U))
    {USB_DeviceAudioInit, USB_DeviceAudioDeinit, USB_DeviceAudioEvent, kUSB_DeviceClassTypeAudio},
#endif

#if ((defined USB_DEVICE_CONFIG_PHDC) && (USB_DEVICE_CONFIG_PHDC > 0U))
    {USB_DevicePhdcInit, USB_DevicePhdcDeinit, USB_DevicePhdcEvent, kUSB_DeviceClassTypePhdc},
#endif

#if ((defined USB_DEVICE_CONFIG_VIDEO) && (USB_DEVICE_CONFIG_VIDEO > 0U))
    {USB_DeviceVideoInit, USB_DeviceVideoDeinit, USB_DeviceVideoEvent, kUSB_DeviceClassTypeVideo},
#endif

#if ((defined USB_DEVICE_CONFIG_PRINTER) && (USB_DEVICE_CONFIG_PRINTER > 0U))
    {USB_DevicePrinterInit, USB_DevicePrinterDeinit, USB_DevicePrinterEvent, kUSB_DeviceClassTypePrinter},
#endif

#if ((defined USB_DEVICE_CONFIG_DFU) && (USB_DEVICE_CONFIG_DFU > 0U))
    {USB_DeviceDfuInit, USB_DeviceDfuDeinit, USB_DeviceDfuEvent, kUSB_DeviceClassTypeDfu},
#endif

#if ((defined USB_DEVICE_CONFIG_CCID) && (USB_DEVICE_CONFIG_CCID > 0U))
    {USB_DeviceCcidInit, USB_DeviceCcidDeinit, USB_DeviceCcidEvent, kUSB_DeviceClassTypeCcid},
#endif

    /* please make sure the following member is in the end of s_UsbDeviceClassInterfaceMap*/
    {(usb_device_class_init_call_t)NULL, (usb_device_class_deinit_call_t)NULL, (usb_device_class_event_callback_t)NULL,
     (usb_device_class_type_t)0},
};

USB_GLOBAL USB_RAM_ADDRESS_ALIGNMENT(USB_DATA_ALIGN_SIZE) static usb_device_common_class_struct_t
    s_UsbDeviceCommonClassStruct[USB_DEVICE_CONFIG_NUM];
USB_GLOBAL USB_RAM_ADDRESS_ALIGNMENT(USB_DATA_ALIGN_SIZE) static uint8_t
    s_UsbDeviceSetupBuffer[USB_DEVICE_CONFIG_NUM][USB_DATA_ALIGN_SIZE_MULTIPLE(USB_SETUP_PACKET_SIZE)];

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Allocate a device common class handle.
 *
 * This function allocates a a device common class handle.
 *
 * @param controllerId   The controller id of the USB IP. Please refer to the enumeration usb_controller_index_t.
 * @param handle          It is out parameter, is used to return pointer of the device common class handle to the
 * caller.
 *
 * @retval kStatus_USB_Success              Get a device handle successfully.
 * @retval kStatus_USB_Busy                 Cannot allocate a common class handle.
 * @retval kStatus_USB_Error                The common class has been initialized.
 */
static usb_status_t USB_DeviceClassAllocateHandle(uint8_t controllerId, usb_device_common_class_struct_t **handle)
{
    uint32_t count;
    OSA_SR_ALLOC();

    OSA_ENTER_CRITICAL();
    /* Check the controller is initialized or not. */
    for (count = 0U; count < USB_DEVICE_CONFIG_NUM; count++)
    {
        if ((NULL != s_UsbDeviceCommonClassStruct[count].handle) &&
            (controllerId == s_UsbDeviceCommonClassStruct[count].controllerId))
        {
            OSA_EXIT_CRITICAL();
            return kStatus_USB_Error;
        }
    }
    /* Get a free common class handle. */
    for (count = 0U; count < USB_DEVICE_CONFIG_NUM; count++)
    {
        if (NULL == s_UsbDeviceCommonClassStruct[count].handle)
        {
            s_UsbDeviceCommonClassStruct[count].controllerId = controllerId;
            s_UsbDeviceCommonClassStruct[count].setupBuffer  = s_UsbDeviceSetupBuffer[count];
            *handle                                          = &s_UsbDeviceCommonClassStruct[count];
            OSA_EXIT_CRITICAL();
            return kStatus_USB_Success;
        }
    }

    OSA_EXIT_CRITICAL();
    return kStatus_USB_Busy;
}

/*!
 * @brief Free a device common class handle.
 *
 * This function frees a device common class handle.
 *
 * @param controllerId   The controller id of the USB IP. Please refer to the enumeration usb_controller_index_t.
 *
 * @retval kStatus_USB_Success              Free device handle successfully.
 * @retval kStatus_USB_InvalidParameter     The common class can not be found.
 */
static usb_status_t USB_DeviceClassFreeHandle(uint8_t controllerId)
{
    uint32_t count = 0U;
    OSA_SR_ALLOC();

    OSA_ENTER_CRITICAL();
    for (; count < USB_DEVICE_CONFIG_NUM; count++)
    {
        if ((NULL != s_UsbDeviceCommonClassStruct[count].handle) &&
            (controllerId == s_UsbDeviceCommonClassStruct[count].controllerId))
        {
            s_UsbDeviceCommonClassStruct[count].handle       = NULL;
            s_UsbDeviceCommonClassStruct[count].configList   = (usb_device_class_config_list_struct_t *)NULL;
            s_UsbDeviceCommonClassStruct[count].controllerId = 0U;
            OSA_EXIT_CRITICAL();
            return kStatus_USB_Success;
        }
    }
    OSA_EXIT_CRITICAL();

    return kStatus_USB_InvalidParameter;
}

/*!
 * @brief Get the device common class handle according to the controller id.
 *
 * This function gets the device common class handle according to the controller id.
 *
 * @param controllerId   The controller id of the USB IP. Please refer to the enumeration usb_controller_index_t.
 * @param handle          It is out parameter, is used to return pointer of the device common class handle to the
 * caller.
 *
 * @retval kStatus_USB_Success              Free device handle successfully.
 * @retval kStatus_USB_InvalidParameter     The common class can not be found.
 */
static usb_status_t USB_DeviceClassGetHandleByControllerId(uint8_t controllerId,
                                                           usb_device_common_class_struct_t **handle)
{
    uint32_t count = 0U;
    OSA_SR_ALLOC();

    OSA_ENTER_CRITICAL();
    for (; count < USB_DEVICE_CONFIG_NUM; count++)
    {
        if ((NULL != s_UsbDeviceCommonClassStruct[count].handle) &&
            (controllerId == s_UsbDeviceCommonClassStruct[count].controllerId))
        {
            *handle = &s_UsbDeviceCommonClassStruct[count];
            OSA_EXIT_CRITICAL();
            return kStatus_USB_Success;
        }
    }
    OSA_EXIT_CRITICAL();
    return kStatus_USB_InvalidParameter;
}

/*!
 * @brief Get the device common class handle according to the device handle.
 *
 * This function gets the device common class handle according to the device handle.
 *
 * @param deviceHandle          The device handle, got from the USB_DeviceInit.
 * @param handle                 It is out parameter, is used to return pointer of the device common class handle to the
 * caller.
 *
 * @retval kStatus_USB_Success              Free device handle successfully.
 * @retval kStatus_USB_InvalidParameter     The common class can not be found.
 */
static usb_status_t USB_DeviceClassGetHandleByDeviceHandle(usb_device_handle deviceHandle,
                                                           usb_device_common_class_struct_t **handle)
{
    uint32_t count = 0U;
    OSA_SR_ALLOC();

    OSA_ENTER_CRITICAL();
    for (; count < USB_DEVICE_CONFIG_NUM; count++)
    {
        if (deviceHandle == s_UsbDeviceCommonClassStruct[count].handle)
        {
            *handle = &s_UsbDeviceCommonClassStruct[count];
            OSA_EXIT_CRITICAL();
            return kStatus_USB_Success;
        }
    }
    OSA_EXIT_CRITICAL();
    return kStatus_USB_InvalidParameter;
}

/*!
 * @brief Get the device handle according to the controller id.
 *
 * This function gets the device handle according to the controller id.
 *
 * @param controllerId   The controller id of the USB IP. Please refer to the enumeration usb_controller_index_t.
 * @param handle          It is out parameter, is used to return pointer of the device handle to the caller.
 *
 * @retval kStatus_USB_Success              Free device handle successfully.
 * @retval kStatus_USB_InvalidParameter     The device handle not be found.
 */
usb_status_t USB_DeviceClassGetDeviceHandle(uint8_t controllerId, usb_device_handle *handle)
{
    uint32_t count = 0U;
    OSA_SR_ALLOC();

    OSA_ENTER_CRITICAL();
    for (; count < USB_DEVICE_CONFIG_NUM; count++)
    {
        if ((NULL != s_UsbDeviceCommonClassStruct[count].handle) &&
            (controllerId == s_UsbDeviceCommonClassStruct[count].controllerId))
        {
            *handle = s_UsbDeviceCommonClassStruct[count].handle;
            OSA_EXIT_CRITICAL();
            return kStatus_USB_Success;
        }
    }
    OSA_EXIT_CRITICAL();
    return kStatus_USB_InvalidParameter;
}

/*!
 * @brief Handle the event passed to the class drivers.
 *
 * This function handles the event passed to the class drivers.
 *
 * @param handle          The device handle, got from the USB_DeviceInit.
 * @param event           The event codes. Please refer to the enumeration usb_device_class_event_t.
 * @param param           The param type is determined by the event code.
 *
 * @return A USB error code or kStatus_USB_Success.
 * @retval kStatus_USB_Success              A valid request has been handled.
 * @retval kStatus_USB_InvalidParameter     The device handle not be found.
 * @retval kStatus_USB_InvalidRequest       The request is invalid, and the control pipe will be stalled by the caller.
 */
usb_status_t USB_DeviceClassEvent(usb_device_handle handle, usb_device_class_event_t event, void *param)
{
    usb_device_common_class_struct_t *classHandle;
    uint8_t mapIndex;
    uint8_t classIndex;
    usb_status_t errorReturn;
    usb_status_t status = kStatus_USB_Error;

    if (NULL == param)
    {
        return kStatus_USB_InvalidParameter;
    }

    /* Get the common class handle according to the device handle. */
    errorReturn = USB_DeviceClassGetHandleByDeviceHandle(handle, &classHandle);
    if (kStatus_USB_Success != errorReturn)
    {
        return kStatus_USB_InvalidParameter;
    }

    for (classIndex = 0U; classIndex < classHandle->configList->count; classIndex++)
    {
        for (mapIndex = 0U; mapIndex < (ARRAY_SIZE(s_UsbDeviceClassInterfaceMap) - 1U); mapIndex++)
        {
            if (s_UsbDeviceClassInterfaceMap[mapIndex].type ==
                classHandle->configList->config[classIndex].classInfomation->type)
            {
                /* Call class event callback of supported class */
                errorReturn = s_UsbDeviceClassInterfaceMap[mapIndex].classEventCallback(
                    (void *)classHandle->configList->config[classIndex].classHandle, event, param);
                /* Return the error code kStatus_USB_InvalidRequest immediately, when a class returns
                 * kStatus_USB_InvalidRequest. */
                if (kStatus_USB_InvalidRequest == errorReturn)
                {
                    return kStatus_USB_InvalidRequest;
                }
                /* For composite device, it should return kStatus_USB_Success once a valid request has been handled */
                if (kStatus_USB_Success == errorReturn)
                {
                    status = kStatus_USB_Success;
                }
                break;
            }
        }
    }

    return status;
}

/*!
 * @brief Handle the common class callback.
 *
 * This function handles the common class callback.
 *
 * @param handle          The device handle, got from the USB_DeviceInit.
 * @param event           The event codes. Please refer to the enumeration usb_device_event_t.
 * @param param           The param type is determined by the event code.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceClassCallback(usb_device_handle handle, uint32_t event, void *param)
{
    usb_device_common_class_struct_t *classHandle;
    usb_status_t status;

    /* Get the common class handle according to the device handle. */
    status = USB_DeviceClassGetHandleByDeviceHandle(handle, &classHandle);
    if (kStatus_USB_Success != status)
    {
        return status;
    }

    if ((uint32_t)kUSB_DeviceEventBusReset == event)
    {
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
        if ((kStatus_USB_Success != USB_DeviceControlPipeInit(handle, classHandle)) ||
            (kStatus_USB_Success != USB_DeviceClassEvent(handle, kUSB_DeviceClassEventDeviceReset, classHandle)))
        {
            return kStatus_USB_Error;
        }
#else
        /* Initialize the control pipes */
        (void)USB_DeviceControlPipeInit(handle, classHandle);

        /* Notify the classes the USB bus reset signal detected. */
        (void)USB_DeviceClassEvent(handle, kUSB_DeviceClassEventDeviceReset, classHandle);
#endif
    }

    /* Call the application device callback function. deviceCallback is from the second parameter of
       USB_DeviceClassInit */
    status = classHandle->configList->deviceCallback(handle, event, param);
    return status;
}

/*!
 * @brief Initialize the common class and the supported classes.
 *
 * This function is used to initialize the common class and the supported classes.
 *
 * @param[in] controllerId   The controller id of the USB IP. Please refer to the enumeration #usb_controller_index_t.
 * @param[in] configList     The class configurations. The pointer must point to the global variable.
 *                           Please refer to the structure #usb_device_class_config_list_struct_t.
 * @param[out] handle        It is out parameter, is used to return pointer of the device handle to the caller.
 *                           The value of parameter is a pointer points the device handle, and this design is used to
 *                           make simple device align with composite device. For composite device, there are many
 *                           kinds of class handle, but there is only one device handle. So the handle points to
 *                           a device instead of a class. And the class handle can be got from the
 *                           #usb_device_class_config_struct_t::classHandle after the function successfully.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceClassInit(
    uint8_t controllerId,                              /*!< [IN] Controller ID */
    usb_device_class_config_list_struct_t *configList, /*!< [IN] Pointer to class configuration list */
    usb_device_handle *handle                          /*!< [OUT] Pointer to the device handle */
)
{
    usb_device_common_class_struct_t *classHandle;
    usb_status_t error;
    uint8_t mapIndex;
    uint8_t classIndex;

    if ((NULL == handle) || (NULL == configList) || ((usb_device_callback_t)NULL == configList->deviceCallback))
    {
        return kStatus_USB_InvalidParameter;
    }

    /* Allocate a common class driver handle. */
    error = USB_DeviceClassAllocateHandle(controllerId, &classHandle);
    if (kStatus_USB_Success != error)
    {
        return error;
    }
    /* Save the configuration list */
    classHandle->configList = configList;

    /* Initialize the device stack. */
    error = USB_DeviceInit(controllerId, USB_DeviceClassCallback, &classHandle->handle);

    if (kStatus_USB_Success != error)
    {
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
        if (((kStatus_USB_Success != USB_DeviceDeinit(classHandle->handle))) ||
            (kStatus_USB_Success != USB_DeviceClassFreeHandle(controllerId)))
        {
            return kStatus_USB_Error;
        }
#else
        (void)USB_DeviceDeinit(classHandle->handle);
        (void)USB_DeviceClassFreeHandle(controllerId);
#endif
        return error;
    }

    /* Initialize the all supported classes according to the configuration list. */
    for (classIndex = 0U; classIndex < classHandle->configList->count; classIndex++)
    {
        for (mapIndex = 0U; mapIndex < (sizeof(s_UsbDeviceClassInterfaceMap) / sizeof(usb_device_class_map_t));
             mapIndex++)
        {
            if (classHandle->configList->config[classIndex].classInfomation->type ==
                s_UsbDeviceClassInterfaceMap[mapIndex].type)
            {
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
                error = s_UsbDeviceClassInterfaceMap[mapIndex].classInit(
                    controllerId, &classHandle->configList->config[classIndex],
                    &classHandle->configList->config[classIndex].classHandle);
                if (kStatus_USB_Success != error)
                {
                    return error;
                }
#else
                (void)s_UsbDeviceClassInterfaceMap[mapIndex].classInit(
                    controllerId, &classHandle->configList->config[classIndex],
                    &classHandle->configList->config[classIndex].classHandle);
#endif
            }
        }
    }

    *handle = classHandle->handle;
    return error;
}

/*!
 * @brief De-initialize the common class and the supported classes.
 *
 * This function is used to de-initialize the common class and the supported classes.
 *
 * @param controllerId   The controller id of the USB IP. Please refer to the enumeration usb_controller_index_t.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceClassDeinit(uint8_t controllerId /*!< [IN] Controller ID */
)
{
    usb_device_common_class_struct_t *classHandle;
    usb_status_t error;
    uint8_t mapIndex;
    uint8_t classIndex;

    /* Get the common class handle according to the controller id. */
    error = USB_DeviceClassGetHandleByControllerId(controllerId, &classHandle);

    if (kStatus_USB_Success != error)
    {
        return error;
    }

    /* De-initialize the all supported classes according to the configuration list. */
    for (classIndex = 0U; classIndex < classHandle->configList->count; classIndex++)
    {
        for (mapIndex = 0U; mapIndex < (sizeof(s_UsbDeviceClassInterfaceMap) / sizeof(usb_device_class_map_t));
             mapIndex++)
        {
            if (classHandle->configList->config[classIndex].classInfomation->type ==
                s_UsbDeviceClassInterfaceMap[mapIndex].type)
            {
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
                error = s_UsbDeviceClassInterfaceMap[mapIndex].classDeinit(
                    classHandle->configList->config[classIndex].classHandle);
                if (kStatus_USB_Success != error)
                {
                    return error;
                }
#else
                (void)s_UsbDeviceClassInterfaceMap[mapIndex].classDeinit(
                    classHandle->configList->config[classIndex].classHandle);
#endif
            }
        }
    }

    /* De-initialize the USB device stack. */
    error = USB_DeviceDeinit(classHandle->handle);
    if (kStatus_USB_Success == error)
    {
        /* Free the common class handle. */
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
        if (kStatus_USB_Success != USB_DeviceClassFreeHandle(controllerId))
        {
            return kStatus_USB_Error;
        }
#else
        (void)USB_DeviceClassFreeHandle(controllerId);
#endif
    }
    return error;
}

/*!
 * @brief Get the USB bus speed.
 *
 * This function is used to get the USB bus speed.
 *
 * @param controllerId   The controller id of the USB IP. Please refer to the enumeration usb_controller_index_t.
 * @param speed           It is an OUT parameter, return current speed of the controller.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceClassGetSpeed(uint8_t controllerId, /*!< [IN] Controller ID */
                                     uint8_t *speed        /*!< [OUT] Current speed */
)
{
    usb_device_common_class_struct_t *classHandle;
    usb_status_t error;

    /* Get the common class handle according to the controller id. */
    error = USB_DeviceClassGetHandleByControllerId(controllerId, &classHandle);

    if (kStatus_USB_Success != error)
    {
        return error;
    }

    /* Get the current speed. */
    error = USB_DeviceGetStatus(classHandle->handle, kUSB_DeviceStatusSpeed, speed);

    return error;
}

#if defined(USB_DEVICE_CONFIG_GET_SOF_COUNT) && (USB_DEVICE_CONFIG_GET_SOF_COUNT > 0U)
/*!
 * @brief Get the USB SOF count.
 *
 * This function is used to get the USB SOF count.
 *
 * @param controllerId   The controller id of the USB IP. Please refer to the enumeration usb_controller_index_t.
 * @param currentFrameCount           It is an OUT parameter, return current sof count of the controller.
 *                                    HS: micro frame count, FS: frame count
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceClassGetCurrentFrameCount(uint8_t controllerId,       /*!< [IN] Controller ID */
                                                 uint32_t *currentFrameCount /*!< [OUT] Current frame count */
)
{
    usb_device_common_class_struct_t *classHandle;
    usb_status_t error;

    /* Get the common class handle according to the controller id. */
    error = USB_DeviceClassGetHandleByControllerId(controllerId, &classHandle);

    if (kStatus_USB_Success != error)
    {
        return error;
    }

    /* Get the current frame count. */
    error = USB_DeviceGetStatus(classHandle->handle, kUSB_DeviceStatusGetCurrentFrameCount, currentFrameCount);

    return error;
}
#endif /* USB_DEVICE_CONFIG_GET_SOF_COUNT */

#endif /* USB_DEVICE_CONFIG_NUM */

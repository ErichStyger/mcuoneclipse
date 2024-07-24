/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016, 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>

#include "usb_device_config.h"
#include "usb.h"
#include "usb_device.h"

#include "usb_device_class.h"

#if USB_DEVICE_CONFIG_CDC_ACM
#include "usb_device_cdc_acm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define USB_CDC_ACM_ENTER_CRITICAL() \
    OSA_SR_ALLOC();                  \
    OSA_ENTER_CRITICAL()

#define USB_CDC_ACM_EXIT_CRITICAL() OSA_EXIT_CRITICAL()

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* CDC ACM device instance */

USB_GLOBAL USB_RAM_ADDRESS_ALIGNMENT(USB_DATA_ALIGN_SIZE) static usb_device_cdc_acm_struct_t
    g_cdcAcmHandle[USB_DEVICE_CONFIG_CDC_ACM];

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Allocates the CDC ACM device handle.
 *
 * This function allocates the CDC ACM device handle.
 *
 * @param handle The class handle of the CDC ACM class.
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceCdcAcmAllocateHandle(usb_device_cdc_acm_struct_t **handle)
{
    uint32_t count;
    for (count = 0; count < (uint32_t)USB_DEVICE_CONFIG_CDC_ACM; count++)
    {
        if (NULL == g_cdcAcmHandle[count].handle)
        {
            *handle = &g_cdcAcmHandle[count];
            return kStatus_USB_Success;
        }
    }

    return kStatus_USB_Busy;
}

/*!
 * @brief Frees the CDC ACM device handle.
 *
 * This function frees the CDC ACM device handle.
 *
 * @param handle The class handle of the CDC ACM class.
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceCdcAcmFreeHandle(usb_device_cdc_acm_struct_t *handle)
{
    handle->handle        = NULL;
    handle->configStruct  = NULL;
    handle->configuration = 0;
    handle->alternate     = 0;
    return kStatus_USB_Success;
}

/*!
 * @brief Responds to the interrupt in endpoint event.
 *
 * This function responds to the interrupt in endpoint event.
 *
 * @param handle The device handle of the CDC ACM device.
 * @param message The pointer to the message of the endpoint callback.
 * @param callbackParam The pointer to the parameter of the callback.
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceCdcAcmInterruptIn(usb_device_handle handle,
                                                usb_device_endpoint_callback_message_struct_t *message,
                                                void *callbackParam)
{
    usb_device_cdc_acm_struct_t *cdcAcmHandle;
    usb_status_t error = kStatus_USB_Error;
    cdcAcmHandle       = (usb_device_cdc_acm_struct_t *)callbackParam;
    if (NULL == cdcAcmHandle)
    {
        return kStatus_USB_InvalidHandle;
    }

    cdcAcmHandle->interruptIn.isBusy = 0U;

    if ((NULL != cdcAcmHandle->configStruct) && (NULL != cdcAcmHandle->configStruct->classCallback))
    {
        /*classCallback is initialized in classInit of s_UsbDeviceClassInterfaceMap,
        it is from the second parameter of classInit */
        error = cdcAcmHandle->configStruct->classCallback((class_handle_t)cdcAcmHandle,
                                                          kUSB_DeviceCdcEventSerialStateNotif, message);
    }
    return error;
}

/*!
 * @brief Responds to the bulk in endpoint event.
 *
 * This function responds to the bulk in endpoint event.
 *
 * @param handle The device handle of the CDC ACM device.
 * @param message The pointer to the message of the endpoint callback.
 * @param callbackParam The pointer to the parameter of the callback.
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceCdcAcmBulkIn(usb_device_handle handle,
                                           usb_device_endpoint_callback_message_struct_t *message,
                                           void *callbackParam)
{
    usb_device_cdc_acm_struct_t *cdcAcmHandle;
    usb_status_t status = kStatus_USB_Error;
    cdcAcmHandle        = (usb_device_cdc_acm_struct_t *)callbackParam;

    if (NULL == cdcAcmHandle)
    {
        return kStatus_USB_InvalidHandle;
    }

    cdcAcmHandle->bulkIn.isBusy = 0;

    if ((NULL != cdcAcmHandle->configStruct) && (NULL != cdcAcmHandle->configStruct->classCallback))
    {
        /*classCallback is initialized in classInit of s_UsbDeviceClassInterfaceMap,
        it is from the second parameter of classInit */
        status = cdcAcmHandle->configStruct->classCallback((class_handle_t)cdcAcmHandle,
                                                           kUSB_DeviceCdcEventSendResponse, message);
    }
    return status;
}

/*!
 * @brief Responds to the bulk out endpoint event.
 *
 * This function responds to the bulk out endpoint event.
 *
 * @param handle The device handle of the CDC ACM device.
 * @param message The pointer to the message of the endpoint callback.
 * @param callbackParam The pointer to the parameter of the callback.
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceCdcAcmBulkOut(usb_device_handle handle,
                                            usb_device_endpoint_callback_message_struct_t *message,
                                            void *callbackParam)
{
    usb_device_cdc_acm_struct_t *cdcAcmHandle;
    usb_status_t status = kStatus_USB_Error;
    cdcAcmHandle        = (usb_device_cdc_acm_struct_t *)callbackParam;

    if (NULL == cdcAcmHandle)
    {
        return kStatus_USB_InvalidHandle;
    }

    cdcAcmHandle->bulkOut.isBusy = 0U;

    if ((NULL != cdcAcmHandle->configStruct) && (NULL != cdcAcmHandle->configStruct->classCallback))
    {
        /*classCallback is initialized in classInit of s_UsbDeviceClassInterfaceMap,
        it is from the second parameter of classInit */
        status = cdcAcmHandle->configStruct->classCallback((class_handle_t)cdcAcmHandle,
                                                           kUSB_DeviceCdcEventRecvResponse, message);
    }
    return status;
}

/*!
 * @brief Initializes the endpoints in CDC ACM class.
 *
 * This function initializes the endpoints in CDC ACM class.
 *
 * @param cdcAcmHandle The class handle of the CDC ACM class.
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceCdcAcmEndpointsInit(usb_device_cdc_acm_struct_t *cdcAcmHandle)
{
    usb_device_interface_list_t *interfaceList;
    usb_device_interface_struct_t *interface = NULL;
    usb_device_endpoint_callback_struct_t epCallback;
    usb_status_t error = kStatus_USB_Error;
    uint32_t count;
    uint32_t index;

    if (NULL == cdcAcmHandle)
    {
        return error;
    }
    epCallback.callbackFn = (usb_device_endpoint_callback_t)NULL;
    /* return error when configuration is invalid (0 or more than the configuration number) */
    if ((cdcAcmHandle->configuration == 0U) ||
        (cdcAcmHandle->configuration > cdcAcmHandle->configStruct->classInfomation->configurations))
    {
        return error;
    }

    interfaceList = &cdcAcmHandle->configStruct->classInfomation->interfaceList[cdcAcmHandle->configuration - 1U];

    for (count = 0; count < interfaceList->count; count++)
    {
        if (USB_DEVICE_CONFIG_CDC_COMM_CLASS_CODE == interfaceList->interfaces[count].classCode)
        {
            for (index = 0; index < interfaceList->interfaces[count].count; index++)
            {
                if (interfaceList->interfaces[count].interface[index].alternateSetting == cdcAcmHandle->alternate)
                {
                    interface = &interfaceList->interfaces[count].interface[index];
                    break;
                }
            }
            cdcAcmHandle->interfaceNumber = interfaceList->interfaces[count].interfaceNumber;
            break;
        }
    }
    if (NULL == interface)
    {
        return error;
    }
    cdcAcmHandle->commInterfaceHandle = interface;
    for (count = 0; count < interface->endpointList.count; count++)
    {
        usb_device_endpoint_init_struct_t epInitStruct;
        epInitStruct.zlt             = 0;
        epInitStruct.interval        = interface->endpointList.endpoint[count].interval;
        epInitStruct.endpointAddress = interface->endpointList.endpoint[count].endpointAddress;
        epInitStruct.maxPacketSize   = interface->endpointList.endpoint[count].maxPacketSize;
        epInitStruct.transferType    = interface->endpointList.endpoint[count].transferType;

        if ((USB_IN == ((epInitStruct.endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
                        USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT)) &&
            (USB_ENDPOINT_INTERRUPT == epInitStruct.transferType))
        {
            cdcAcmHandle->interruptIn.ep = (epInitStruct.endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_NUMBER_MASK);
            cdcAcmHandle->interruptIn.isBusy         = 0;
            cdcAcmHandle->interruptIn.pipeDataBuffer = (uint8_t *)USB_INVALID_TRANSFER_BUFFER;
            cdcAcmHandle->interruptIn.pipeStall      = 0U;
            cdcAcmHandle->interruptIn.pipeDataLen    = 0U;
            epCallback.callbackFn                    = USB_DeviceCdcAcmInterruptIn;
        }

        epCallback.callbackParam = cdcAcmHandle;

        error = USB_DeviceInitEndpoint(cdcAcmHandle->handle, &epInitStruct, &epCallback);
        if (kStatus_USB_Success != error)
        {
            return error;
        }
    }

    for (count = 0; count < interfaceList->count; count++)
    {
        if (USB_DEVICE_CONFIG_CDC_DATA_CLASS_CODE == interfaceList->interfaces[count].classCode)
        {
            for (index = 0; index < interfaceList->interfaces[count].count; index++)
            {
                if (interfaceList->interfaces[count].interface[index].alternateSetting == cdcAcmHandle->alternate)
                {
                    interface = &interfaceList->interfaces[count].interface[index];
                    break;
                }
            }
            break;
        }
    }

    cdcAcmHandle->dataInterfaceHandle = interface;

    for (count = 0; count < interface->endpointList.count; count++)
    {
        usb_device_endpoint_init_struct_t epInitStruct;
        epInitStruct.zlt             = 0;
        epInitStruct.interval        = interface->endpointList.endpoint[count].interval;
        epInitStruct.endpointAddress = interface->endpointList.endpoint[count].endpointAddress;
        epInitStruct.maxPacketSize   = interface->endpointList.endpoint[count].maxPacketSize;
        epInitStruct.transferType    = interface->endpointList.endpoint[count].transferType;

        if ((USB_IN == ((epInitStruct.endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
                        USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT)) &&
            (USB_ENDPOINT_BULK == epInitStruct.transferType))
        {
            cdcAcmHandle->bulkIn.ep     = (epInitStruct.endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_NUMBER_MASK);
            cdcAcmHandle->bulkIn.isBusy = 0;
            cdcAcmHandle->bulkIn.pipeDataBuffer = (uint8_t *)USB_INVALID_TRANSFER_BUFFER;
            cdcAcmHandle->bulkIn.pipeStall      = 0U;
            cdcAcmHandle->bulkIn.pipeDataLen    = 0U;
            epCallback.callbackFn               = USB_DeviceCdcAcmBulkIn;
        }
        else if ((USB_OUT == ((epInitStruct.endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
                              USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT)) &&
                 (USB_ENDPOINT_BULK == epInitStruct.transferType))
        {
            cdcAcmHandle->bulkOut.ep     = (epInitStruct.endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_NUMBER_MASK);
            cdcAcmHandle->bulkOut.isBusy = 0;
            cdcAcmHandle->bulkOut.pipeDataBuffer = (uint8_t *)USB_INVALID_TRANSFER_BUFFER;
            cdcAcmHandle->bulkOut.pipeStall      = 0U;
            cdcAcmHandle->bulkOut.pipeDataLen    = 0U;
            epCallback.callbackFn                = USB_DeviceCdcAcmBulkOut;
        }
        else
        {
            /*no action*/
        }
        epCallback.callbackParam = cdcAcmHandle;

        error = USB_DeviceInitEndpoint(cdcAcmHandle->handle, &epInitStruct, &epCallback);
    }
    return error;
}

/*!
 * @brief De-initializes the endpoints in CDC ACM class.
 *
 * This function de-initializes the endpoints in CDC ACM class.
 *
 * @param cdcAcmHandle The class handle of the CDC ACM class.
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceCdcAcmEndpointsDeinit(usb_device_cdc_acm_struct_t *cdcAcmHandle)
{
    usb_status_t status = kStatus_USB_Error;
    uint32_t count;

    if ((NULL == cdcAcmHandle->commInterfaceHandle) || (NULL == cdcAcmHandle->dataInterfaceHandle))
    {
        return status;
    }
    for (count = 0; count < cdcAcmHandle->commInterfaceHandle->endpointList.count; count++)
    {
        status = USB_DeviceDeinitEndpoint(
            cdcAcmHandle->handle, cdcAcmHandle->commInterfaceHandle->endpointList.endpoint[count].endpointAddress);
    }
    for (count = 0; count < cdcAcmHandle->dataInterfaceHandle->endpointList.count; count++)
    {
        status = USB_DeviceDeinitEndpoint(
            cdcAcmHandle->handle, cdcAcmHandle->dataInterfaceHandle->endpointList.endpoint[count].endpointAddress);
    }
    cdcAcmHandle->commInterfaceHandle = NULL;
    cdcAcmHandle->dataInterfaceHandle = NULL;

    return status;
}

/*!
 * @brief Handles the CDC ACM class event.
 *
 * This function responses to various events including the common device events and the class specific events.
 * For class specific events, it calls the class callback defined in the application to deal with the class specific
 * event.
 *
 * @param handle The class handle of the CDC ACM class.
 * @param event The event type.
 * @param param The class handle of the CDC ACM class.
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceCdcAcmEvent(void *handle, uint32_t event, void *param)
{
    usb_device_cdc_acm_struct_t *cdcAcmHandle;
    usb_device_cdc_acm_request_param_struct_t reqParam;
    usb_status_t error = kStatus_USB_Error;
    uint32_t count;
    uint16_t interfaceAlternate;
    uint8_t *temp8;
    uint8_t alternate;
    usb_device_class_event_t eventCode = (usb_device_class_event_t)event;
    if ((NULL == param) || (NULL == handle))
    {
        return kStatus_USB_InvalidHandle;
    }

    cdcAcmHandle = (usb_device_cdc_acm_struct_t *)handle;

    switch (eventCode)
    {
        case kUSB_DeviceClassEventDeviceReset:
            /* Bus reset, clear the configuration. */
            cdcAcmHandle->configuration = 0;
            error                       = kStatus_USB_Success;
            break;
        case kUSB_DeviceClassEventSetConfiguration:
            temp8 = ((uint8_t *)param);
            if (NULL == cdcAcmHandle->configStruct)
            {
                break;
            }
            if (*temp8 == cdcAcmHandle->configuration)
            {
                error = kStatus_USB_Success;
                break;
            }

            error                       = USB_DeviceCdcAcmEndpointsDeinit(cdcAcmHandle);
            cdcAcmHandle->configuration = *temp8;
            cdcAcmHandle->alternate     = 0U;
            error                       = USB_DeviceCdcAcmEndpointsInit(cdcAcmHandle);
            if (kStatus_USB_Success != error)
            {
#if 0
                (void)usb_echo("kUSB_DeviceClassEventSetConfiguration, USB_DeviceInitEndpoint fail\r\n");
#endif
            }
            break;
        case kUSB_DeviceClassEventSetInterface:
            if (NULL == cdcAcmHandle->configStruct)
            {
                break;
            }

            interfaceAlternate = *((uint16_t *)param);
            alternate          = (uint8_t)(interfaceAlternate & 0xFFU);

            if (cdcAcmHandle->interfaceNumber != ((uint8_t)(interfaceAlternate >> 8U)))
            {
                break;
            }
            if (alternate == cdcAcmHandle->alternate)
            {
                error = kStatus_USB_Success;
                break;
            }
            error                   = USB_DeviceCdcAcmEndpointsDeinit(cdcAcmHandle);
            cdcAcmHandle->alternate = alternate;
            error                   = USB_DeviceCdcAcmEndpointsInit(cdcAcmHandle);
            if (kStatus_USB_Success != error)
            {
#if 0
                (void)usb_echo("kUSB_DeviceClassEventSetInterface, USB_DeviceInitEndpoint fail\r\n");
#endif
            }
            break;
        case kUSB_DeviceClassEventSetEndpointHalt:
            if ((NULL == cdcAcmHandle->configStruct) || (NULL == cdcAcmHandle->commInterfaceHandle) ||
                (NULL == cdcAcmHandle->dataInterfaceHandle))
            {
                break;
            }
            temp8 = ((uint8_t *)param);
            for (count = 0; count < cdcAcmHandle->commInterfaceHandle->endpointList.count; count++)
            {
                if (*temp8 == cdcAcmHandle->commInterfaceHandle->endpointList.endpoint[count].endpointAddress)
                {
                    cdcAcmHandle->interruptIn.pipeStall = 1U;
                    error                               = USB_DeviceStallEndpoint(cdcAcmHandle->handle, *temp8);
                }
            }
            for (count = 0; count < cdcAcmHandle->dataInterfaceHandle->endpointList.count; count++)
            {
                if (*temp8 == cdcAcmHandle->dataInterfaceHandle->endpointList.endpoint[count].endpointAddress)
                {
                    if (USB_IN == (((*temp8) & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
                                   USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT))
                    {
                        cdcAcmHandle->bulkIn.pipeStall = 1U;
                    }
                    else
                    {
                        cdcAcmHandle->bulkOut.pipeStall = 1U;
                    }
                    error = USB_DeviceStallEndpoint(cdcAcmHandle->handle, *temp8);
                }
            }
            break;
        case kUSB_DeviceClassEventClearEndpointHalt:
            if ((NULL == cdcAcmHandle->configStruct) || (NULL == cdcAcmHandle->commInterfaceHandle) ||
                (NULL == cdcAcmHandle->dataInterfaceHandle))
            {
                break;
            }
            temp8 = ((uint8_t *)param);
            for (count = 0; count < cdcAcmHandle->commInterfaceHandle->endpointList.count; count++)
            {
                if (*temp8 == cdcAcmHandle->commInterfaceHandle->endpointList.endpoint[count].endpointAddress)
                {
                    error = USB_DeviceUnstallEndpoint(cdcAcmHandle->handle, *temp8);
                    if (USB_IN == (((*temp8) & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
                                   USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT))
                    {
                        if (0U != cdcAcmHandle->interruptIn.pipeStall)
                        {
                            cdcAcmHandle->interruptIn.pipeStall = 0U;
                            if ((uint8_t *)USB_INVALID_TRANSFER_BUFFER != cdcAcmHandle->interruptIn.pipeDataBuffer)
                            {
                                error = USB_DeviceSendRequest(cdcAcmHandle->handle, (cdcAcmHandle->interruptIn.ep),
                                                              cdcAcmHandle->interruptIn.pipeDataBuffer,
                                                              cdcAcmHandle->interruptIn.pipeDataLen);
                                if (kStatus_USB_Success != error)
                                {
                                    usb_device_endpoint_callback_message_struct_t endpointCallbackMessage;
                                    endpointCallbackMessage.buffer  = cdcAcmHandle->interruptIn.pipeDataBuffer;
                                    endpointCallbackMessage.length  = cdcAcmHandle->interruptIn.pipeDataLen;
                                    endpointCallbackMessage.isSetup = 0U;
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
                                    if (kStatus_USB_Success != USB_DeviceCdcAcmBulkIn(cdcAcmHandle->handle,
                                                                                      (void *)&endpointCallbackMessage,
                                                                                      handle))
                                    {
                                        return kStatus_USB_Error;
                                    }
#else
                                    (void)USB_DeviceCdcAcmBulkIn(cdcAcmHandle->handle, (void *)&endpointCallbackMessage,
                                                                 handle);
#endif
                                }
                                cdcAcmHandle->interruptIn.pipeDataBuffer = (uint8_t *)USB_INVALID_TRANSFER_BUFFER;
                                cdcAcmHandle->interruptIn.pipeDataLen    = 0U;
                            }
                        }
                    }
                }
            }
            for (count = 0; count < cdcAcmHandle->dataInterfaceHandle->endpointList.count; count++)
            {
                if (*temp8 == cdcAcmHandle->dataInterfaceHandle->endpointList.endpoint[count].endpointAddress)
                {
                    error = USB_DeviceUnstallEndpoint(cdcAcmHandle->handle, *temp8);
                    if (USB_IN == (((*temp8) & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
                                   USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT))
                    {
                        if (0U != cdcAcmHandle->bulkIn.pipeStall)
                        {
                            cdcAcmHandle->bulkIn.pipeStall = 0U;
                            if ((uint8_t *)USB_INVALID_TRANSFER_BUFFER != cdcAcmHandle->bulkIn.pipeDataBuffer)
                            {
                                error = USB_DeviceSendRequest(cdcAcmHandle->handle, (cdcAcmHandle->bulkIn.ep),
                                                              cdcAcmHandle->bulkIn.pipeDataBuffer,
                                                              cdcAcmHandle->bulkIn.pipeDataLen);
                                if (kStatus_USB_Success != error)
                                {
                                    usb_device_endpoint_callback_message_struct_t endpointCallbackMessage;
                                    endpointCallbackMessage.buffer  = cdcAcmHandle->bulkIn.pipeDataBuffer;
                                    endpointCallbackMessage.length  = cdcAcmHandle->bulkIn.pipeDataLen;
                                    endpointCallbackMessage.isSetup = 0U;
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
                                    if (kStatus_USB_Success != USB_DeviceCdcAcmBulkIn(cdcAcmHandle->handle,
                                                                                      (void *)&endpointCallbackMessage,
                                                                                      handle))
                                    {
                                        return kStatus_USB_Error;
                                    }
#else
                                    (void)USB_DeviceCdcAcmBulkIn(cdcAcmHandle->handle, (void *)&endpointCallbackMessage,
                                                                 handle);
#endif
                                }
                                cdcAcmHandle->bulkIn.pipeDataBuffer = (uint8_t *)USB_INVALID_TRANSFER_BUFFER;
                                cdcAcmHandle->bulkIn.pipeDataLen    = 0U;
                            }
                        }
                    }
                    else
                    {
                        if (0U != cdcAcmHandle->bulkOut.pipeStall)
                        {
                            cdcAcmHandle->bulkOut.pipeStall = 0U;
                            if ((uint8_t *)USB_INVALID_TRANSFER_BUFFER != cdcAcmHandle->bulkOut.pipeDataBuffer)
                            {
                                error = USB_DeviceRecvRequest(cdcAcmHandle->handle, (cdcAcmHandle->bulkOut.ep),
                                                              cdcAcmHandle->bulkOut.pipeDataBuffer,
                                                              cdcAcmHandle->bulkOut.pipeDataLen);
                                if (kStatus_USB_Success != error)
                                {
                                    usb_device_endpoint_callback_message_struct_t endpointCallbackMessage;
                                    endpointCallbackMessage.buffer  = cdcAcmHandle->bulkOut.pipeDataBuffer;
                                    endpointCallbackMessage.length  = cdcAcmHandle->bulkOut.pipeDataLen;
                                    endpointCallbackMessage.isSetup = 0U;
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
                                    if (kStatus_USB_Success != USB_DeviceCdcAcmBulkOut(cdcAcmHandle->handle,
                                                                                       (void *)&endpointCallbackMessage,
                                                                                       handle))
                                    {
                                        return kStatus_USB_Error;
                                    }
#else
                                    (void)USB_DeviceCdcAcmBulkOut(cdcAcmHandle->handle,
                                                                  (void *)&endpointCallbackMessage, handle);
#endif
                                }
                                cdcAcmHandle->bulkOut.pipeDataBuffer = (uint8_t *)USB_INVALID_TRANSFER_BUFFER;
                                cdcAcmHandle->bulkOut.pipeDataLen    = 0U;
                            }
                        }
                    }
                }
            }
            break;
        case kUSB_DeviceClassEventClassRequest:

        {
            usb_device_control_request_struct_t *controlRequest = (usb_device_control_request_struct_t *)param;

            if ((controlRequest->setup->bmRequestType & USB_REQUEST_TYPE_RECIPIENT_MASK) !=
                USB_REQUEST_TYPE_RECIPIENT_INTERFACE)
            {
                break;
            }

            if ((controlRequest->setup->wIndex & 0xFFU) != cdcAcmHandle->interfaceNumber)
            {
                break;
            }

            error = kStatus_USB_InvalidRequest;
            /* Standard CDC request */
            reqParam.buffer         = &(controlRequest->buffer);
            reqParam.length         = &(controlRequest->length);
            reqParam.interfaceIndex = controlRequest->setup->wIndex;
            reqParam.setupValue     = controlRequest->setup->wValue;
            reqParam.isSetup        = controlRequest->isSetup;
            switch (controlRequest->setup->bRequest)
            {
                case USB_DEVICE_CDC_REQUEST_SEND_ENCAPSULATED_COMMAND:
                    if (((controlRequest->setup->bmRequestType & USB_REQUEST_TYPE_DIR_MASK) ==
                         USB_REQUEST_TYPE_DIR_OUT) &&
                        (controlRequest->setup->wLength != 0U))
                    {
                        /* classCallback is initialized in classInit of s_UsbDeviceClassInterfaceMap,
                        it is from the second parameter of classInit */
                        error = cdcAcmHandle->configStruct->classCallback(
                            (class_handle_t)cdcAcmHandle, kUSB_DeviceCdcEventSendEncapsulatedCommand, &reqParam);
                    }
                    break;
                case USB_DEVICE_CDC_REQUEST_GET_ENCAPSULATED_RESPONSE:
                    if (((controlRequest->setup->bmRequestType & USB_REQUEST_TYPE_DIR_MASK) ==
                         USB_REQUEST_TYPE_DIR_IN) &&
                        (controlRequest->setup->wLength != 0U))
                    {
                        /* classCallback is initialized in classInit of s_UsbDeviceClassInterfaceMap,
                        it is from the second parameter of classInit */
                        error = cdcAcmHandle->configStruct->classCallback(
                            (class_handle_t)cdcAcmHandle, kUSB_DeviceCdcEventGetEncapsulatedResponse, &reqParam);
                    }
                    break;
                case USB_DEVICE_CDC_REQUEST_SET_COMM_FEATURE:
                    if (((controlRequest->setup->bmRequestType & USB_REQUEST_TYPE_DIR_MASK) ==
                         USB_REQUEST_TYPE_DIR_OUT) &&
                        (controlRequest->setup->wLength != 0U))
                    {
                        /* classCallback is initialized in classInit of s_UsbDeviceClassInterfaceMap,
                        it is from the second parameter of classInit */
                        error = cdcAcmHandle->configStruct->classCallback((class_handle_t)cdcAcmHandle,
                                                                          kUSB_DeviceCdcEventSetCommFeature, &reqParam);
                    }
                    break;
                case USB_DEVICE_CDC_REQUEST_GET_COMM_FEATURE:
                    if (((controlRequest->setup->bmRequestType & USB_REQUEST_TYPE_DIR_MASK) ==
                         USB_REQUEST_TYPE_DIR_IN) &&
                        (controlRequest->setup->wLength != 0U))
                    {
                        /* classCallback is initialized in classInit of s_UsbDeviceClassInterfaceMap,
                        it is from the second parameter of classInit */
                        error = cdcAcmHandle->configStruct->classCallback((class_handle_t)cdcAcmHandle,
                                                                          kUSB_DeviceCdcEventGetCommFeature, &reqParam);
                    }
                    break;
                case USB_DEVICE_CDC_REQUEST_CLEAR_COMM_FEATURE:
                    if (((controlRequest->setup->bmRequestType & USB_REQUEST_TYPE_DIR_MASK) ==
                         USB_REQUEST_TYPE_DIR_OUT) &&
                        (controlRequest->setup->wLength == 0U))
                    {
                        /* classCallback is initialized in classInit of s_UsbDeviceClassInterfaceMap,
                        it is from the second parameter of classInit */
                        error = cdcAcmHandle->configStruct->classCallback(
                            (class_handle_t)cdcAcmHandle, kUSB_DeviceCdcEventClearCommFeature, &reqParam);
                    }
                    break;
                case USB_DEVICE_CDC_REQUEST_GET_LINE_CODING:
                    if (((controlRequest->setup->bmRequestType & USB_REQUEST_TYPE_DIR_MASK) ==
                         USB_REQUEST_TYPE_DIR_IN) &&
                        (controlRequest->setup->wLength != 0U))
                    {
                        /* classCallback is initialized in classInit of s_UsbDeviceClassInterfaceMap,
                        it is from the second parameter of classInit */
                        error = cdcAcmHandle->configStruct->classCallback((class_handle_t)cdcAcmHandle,
                                                                          kUSB_DeviceCdcEventGetLineCoding, &reqParam);
                    }
                    break;
                case USB_DEVICE_CDC_REQUEST_SET_LINE_CODING:
                    if (((controlRequest->setup->bmRequestType & USB_REQUEST_TYPE_DIR_MASK) ==
                         USB_REQUEST_TYPE_DIR_OUT) &&
                        (controlRequest->setup->wLength != 0U))
                    {
                        /* classCallback is initialized in classInit of s_UsbDeviceClassInterfaceMap,
                        it is from the second parameter of classInit */
                        error = cdcAcmHandle->configStruct->classCallback((class_handle_t)cdcAcmHandle,
                                                                          kUSB_DeviceCdcEventSetLineCoding, &reqParam);
                    }
                    break;
                case USB_DEVICE_CDC_REQUEST_SET_CONTROL_LINE_STATE:
                    if (((controlRequest->setup->bmRequestType & USB_REQUEST_TYPE_DIR_MASK) ==
                         USB_REQUEST_TYPE_DIR_OUT) &&
                        (controlRequest->setup->wLength == 0U))
                    {
                        /* classCallback is initialized in classInit of s_UsbDeviceClassInterfaceMap,
                        it is from the second parameter of classInit */
                        error = cdcAcmHandle->configStruct->classCallback(
                            (class_handle_t)cdcAcmHandle, kUSB_DeviceCdcEventSetControlLineState, &reqParam);
                    }
                    break;
                case USB_DEVICE_CDC_REQUEST_SEND_BREAK:
                    if (((controlRequest->setup->bmRequestType & USB_REQUEST_TYPE_DIR_MASK) ==
                         USB_REQUEST_TYPE_DIR_OUT) &&
                        (controlRequest->setup->wLength == 0U))
                    {
                        /* classCallback is initialized in classInit of s_UsbDeviceClassInterfaceMap,
                        it is from the second parameter of classInit */
                        error = cdcAcmHandle->configStruct->classCallback((class_handle_t)cdcAcmHandle,
                                                                          kUSB_DeviceCdcEventSendBreak, &reqParam);
                    }
                    break;
                default:
                    /* no action, return kStatus_USB_InvalidRequest */
                    break;
            }
        }
        break;
        default:
            /*no action*/
            break;
    }
    return error;
}

/*!
 * @brief Initializes the USB CDC ACM class.
 *
 * This function obtains a usb device handle according to the controller id, initializes the CDC ACM class
 * with the class configure parameters and creates the mutex for each pipe.
 *
 * @param controllerId The id of the controller. The value can be choosen from kUSB_ControllerKhci0,
 *  kUSB_ControllerKhci1, kUSB_ControllerEhci0 or kUSB_ControllerEhci1.
 * @param config The user configuration structure of type usb_device_class_config_struct_t. The user
 *  populates the members of this structure and passes the pointer of this structure
 *  into this function.
 * @param handle  It is out parameter. The class handle of the CDC ACM class.
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceCdcAcmInit(uint8_t controllerId,
                                  usb_device_class_config_struct_t *config,
                                  class_handle_t *handle)
{
    usb_device_cdc_acm_struct_t *cdcAcmHandle;
    usb_status_t error;

    error = USB_DeviceCdcAcmAllocateHandle(&cdcAcmHandle);

    if (kStatus_USB_Success != error)
    {
        return error;
    }

    error = USB_DeviceClassGetDeviceHandle(controllerId, &cdcAcmHandle->handle);

    if (kStatus_USB_Success != error)
    {
        return error;
    }

    if (NULL == cdcAcmHandle->handle)
    {
        return kStatus_USB_InvalidHandle;
    }
    cdcAcmHandle->configStruct  = config;
    cdcAcmHandle->configuration = 0;
    cdcAcmHandle->alternate     = 0xFF;

    cdcAcmHandle->bulkIn.mutex = (osa_mutex_handle_t)&cdcAcmHandle->bulkIn.mutexBuffer[0];
    if (KOSA_StatusSuccess != OSA_MutexCreate((cdcAcmHandle->bulkIn.mutex)))
    {
#if 0
        (void)usb_echo("mutex create error!");
#endif
    }
    cdcAcmHandle->bulkOut.mutex = (osa_mutex_handle_t)&cdcAcmHandle->bulkOut.mutexBuffer[0];
    if (KOSA_StatusSuccess != OSA_MutexCreate((cdcAcmHandle->bulkOut.mutex)))
    {
#if 0
        (void)usb_echo("mutex create error!");
#endif
    }
    cdcAcmHandle->interruptIn.mutex = (osa_mutex_handle_t)&cdcAcmHandle->interruptIn.mutexBuffer[0];
    if (KOSA_StatusSuccess != OSA_MutexCreate((cdcAcmHandle->interruptIn.mutex)))
    {
#if 0
        (void)usb_echo("mutex create error!");
#endif
    }
    *handle = (class_handle_t)cdcAcmHandle;
    return error;
}

/*!
 * @brief De-Initializes the USB CDC ACM class.
 *
 * This function destroys the mutex for each pipe, deinit each endpoint of the CDC ACM class and free
 * the CDC ACM class handle.
 *
 * @param handle The class handle of the CDC ACM class.
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceCdcAcmDeinit(class_handle_t handle)
{
    usb_device_cdc_acm_struct_t *cdcAcmHandle;
    usb_status_t error;

    cdcAcmHandle = (usb_device_cdc_acm_struct_t *)handle;

    if (NULL == cdcAcmHandle)
    {
        return kStatus_USB_InvalidHandle;
    }
    if (KOSA_StatusSuccess != OSA_MutexDestroy((cdcAcmHandle->bulkIn.mutex)))
    {
#if 0
        (void)usb_echo("mutex destroy error!");
#endif
    }
    if (KOSA_StatusSuccess != OSA_MutexDestroy((cdcAcmHandle->bulkOut.mutex)))
    {
#if 0
        (void)usb_echo("mutex destroy error!");
#endif
    }
    if (KOSA_StatusSuccess != OSA_MutexDestroy((cdcAcmHandle->interruptIn.mutex)))
    {
#if 0
        (void)usb_echo("mutex destroy error!");
#endif
    }
    error = USB_DeviceCdcAcmEndpointsDeinit(cdcAcmHandle);
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
    if (kStatus_USB_Success != USB_DeviceCdcAcmFreeHandle(cdcAcmHandle))
    {
        return kStatus_USB_Error;
    }
#else
    (void)USB_DeviceCdcAcmFreeHandle(cdcAcmHandle);
#endif
    return error;
}

/*!
 * @brief Prime the endpoint to send packet to host.
 *
 * This function checks whether the endpoint is sending packet, then it primes the endpoint
 * with the buffer address and the buffer length if the pipe is not busy. Otherwise, it ignores this transfer by
 * returning an error code.
 *
 * @param handle The class handle of the CDC ACM class.
 * @param ep The endpoint number of the transfer.
 * @param buffer The pointer to the buffer to be transferred.
 * @param length The length of the buffer to be transferred.
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceCdcAcmSend(class_handle_t handle, uint8_t ep, uint8_t *buffer, uint32_t length)
{
    usb_device_cdc_acm_struct_t *cdcAcmHandle;
    usb_status_t status                   = kStatus_USB_Error;
    usb_device_cdc_acm_pipe_t *cdcAcmPipe = NULL;

    if (NULL == handle)
    {
        return kStatus_USB_InvalidHandle;
    }
    cdcAcmHandle = (usb_device_cdc_acm_struct_t *)handle;

    if (cdcAcmHandle->bulkIn.ep == ep)
    {
        cdcAcmPipe = &(cdcAcmHandle->bulkIn);
    }
    else if (cdcAcmHandle->interruptIn.ep == ep)
    {
        cdcAcmPipe = &(cdcAcmHandle->interruptIn);
    }
    else
    {
        /*no action*/
    }

    if (NULL != cdcAcmPipe)
    {
        if (1U == cdcAcmPipe->isBusy)
        {
            return kStatus_USB_Busy;
        }
        cdcAcmPipe->isBusy = 1U;

        if (0u != cdcAcmPipe->pipeStall)
        {
            cdcAcmPipe->pipeDataBuffer = buffer;
            cdcAcmPipe->pipeDataLen    = length;
            return kStatus_USB_Success;
        }

        status = USB_DeviceSendRequest(cdcAcmHandle->handle, ep, buffer, length);
        if (kStatus_USB_Success != status)
        {
            cdcAcmPipe->isBusy = 0U;
        }
    }
    return status;
}

/*!
 * @brief Prime the endpoint to receive packet from host.
 *
 * This function checks whether the endpoint is receiving packet, then it primes the endpoint
 * with the buffer address and the buffer length if the pipe is not busy. Otherwise, it ignores this transfer by
 * returning an error code.
 *
 * @param handle The class handle of the CDC ACM class.
 * @param ep The endpoint number of the transfer.
 * @param buffer The pointer to the buffer to be transferred.
 * @param length The length of the buffer to be transferred.
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceCdcAcmRecv(class_handle_t handle, uint8_t ep, uint8_t *buffer, uint32_t length)
{
    usb_device_cdc_acm_struct_t *cdcAcmHandle;
    usb_status_t status;
    if (NULL == handle)
    {
        return kStatus_USB_InvalidHandle;
    }
    cdcAcmHandle = (usb_device_cdc_acm_struct_t *)handle;

    if (1U == cdcAcmHandle->bulkOut.isBusy)
    {
        return kStatus_USB_Busy;
    }
    cdcAcmHandle->bulkOut.isBusy = 1U;

    if (0U != cdcAcmHandle->bulkOut.pipeStall)
    {
        cdcAcmHandle->bulkOut.pipeDataBuffer = buffer;
        cdcAcmHandle->bulkOut.pipeDataLen    = length;
        return kStatus_USB_Success;
    }

    status = USB_DeviceRecvRequest(cdcAcmHandle->handle, ep, buffer, length);
    if (kStatus_USB_Success != status)
    {
        cdcAcmHandle->bulkOut.isBusy = 0U;
    }
    return status;
}

#endif /* USB_DEVICE_CONFIG_CDC_ACM */

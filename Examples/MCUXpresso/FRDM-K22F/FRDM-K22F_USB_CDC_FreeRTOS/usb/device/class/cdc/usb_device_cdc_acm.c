/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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

#include "fsl_device_registers.h"

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
    \
USB_OSA_SR_ALLOC();                  \
    \
USB_OSA_ENTER_CRITICAL()

#define USB_CDC_ACM_EXIT_CRITICAL() USB_OSA_EXIT_CRITICAL()

/*******************************************************************************
* Variables
******************************************************************************/
/* CDC ACM device instance */

USB_GLOBAL usb_device_cdc_acm_struct_t g_cdcAcmHandle[USB_DEVICE_CONFIG_CDC_ACM_MAX_INSTANCE];

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
    int32_t count;
    for (count = 0; count < USB_DEVICE_CONFIG_CDC_ACM_MAX_INSTANCE; count++)
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
    handle->handle = NULL;
    handle->configStruct = NULL;
    handle->configuration = 0;
    handle->alternate = 0;
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
usb_status_t USB_DeviceCdcAcmInterruptIn(usb_device_handle handle,
                                         usb_device_endpoint_callback_message_struct_t *message,
                                         void *callbackParam)
{
    usb_device_cdc_acm_struct_t *cdcAcmHandle;
    usb_status_t error = kStatus_USB_Error;
    cdcAcmHandle = (usb_device_cdc_acm_struct_t *)callbackParam;
    if (!cdcAcmHandle)
    {
        return kStatus_USB_InvalidHandle;
    }

    cdcAcmHandle->interruptIn.isBusy = 0;

    if ((NULL != cdcAcmHandle->configStruct) && (cdcAcmHandle->configStruct->classCallback))
    {
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
usb_status_t USB_DeviceCdcAcmBulkIn(usb_device_handle handle,
                                    usb_device_endpoint_callback_message_struct_t *message,
                                    void *callbackParam)
{
    usb_device_cdc_acm_struct_t *cdcAcmHandle;
    usb_status_t error = kStatus_USB_Error;
    cdcAcmHandle = (usb_device_cdc_acm_struct_t *)callbackParam;

    if (!cdcAcmHandle)
    {
        return kStatus_USB_InvalidHandle;
    }

    cdcAcmHandle->bulkIn.isBusy = 0;

    if ((NULL != cdcAcmHandle->configStruct) && (cdcAcmHandle->configStruct->classCallback))
    {
        error = cdcAcmHandle->configStruct->classCallback((class_handle_t)cdcAcmHandle, kUSB_DeviceCdcEventSendResponse,
                                                          message);
    }
    return error;
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
usb_status_t USB_DeviceCdcAcmBulkOut(usb_device_handle handle,
                                     usb_device_endpoint_callback_message_struct_t *message,
                                     void *callbackParam)
{
    usb_device_cdc_acm_struct_t *cdcAcmHandle;
    usb_status_t error = kStatus_USB_Error;
    cdcAcmHandle = (usb_device_cdc_acm_struct_t *)callbackParam;

    if (!cdcAcmHandle)
    {
        return kStatus_USB_InvalidHandle;
    }

    cdcAcmHandle->bulkOut.isBusy = 0;

    if ((NULL != cdcAcmHandle->configStruct) && (cdcAcmHandle->configStruct->classCallback))
    {
        error = cdcAcmHandle->configStruct->classCallback((class_handle_t)cdcAcmHandle, kUSB_DeviceCdcEventRecvResponse,
                                                          message);
    }
    return error;
}

/*!
 * @brief Initializes the endpoints in CDC ACM class.
 *
 * This function initializes the endpoints in CDC ACM class.
 *
 * @param cdcAcmHandle The class handle of the CDC ACM class.
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceCdcAcmEndpointsInit(usb_device_cdc_acm_struct_t *cdcAcmHandle)
{
    usb_device_interface_list_t *interfaceList;
    usb_device_interface_struct_t *interface = NULL;
    usb_status_t error = kStatus_USB_Error;

    if (!cdcAcmHandle)
    {
        return error;
    }

    /* return error when configuration is invalid (0 or more than the configuration number) */
    if ((cdcAcmHandle->configuration == 0U) ||
        (cdcAcmHandle->configuration > cdcAcmHandle->configStruct->classInfomation->configurations))
    {
        return error;
    }

    interfaceList = &cdcAcmHandle->configStruct->classInfomation->interfaceList[cdcAcmHandle->configuration - 1];

    for (int count = 0; count < interfaceList->count; count++)
    {
        if (USB_DEVICE_CONFIG_CDC_COMM_CLASS_CODE == interfaceList->interfaces[count].classCode)
        {
            for (int index = 0; index < interfaceList->interfaces[count].count; index++)
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
    if (!interface)
    {
        return error;
    }
    cdcAcmHandle->commInterfaceHandle = interface;
    for (int count = 0; count < interface->endpointList.count; count++)
    {
        usb_device_endpoint_init_struct_t epInitStruct;
        usb_device_endpoint_callback_struct_t epCallback;
        epInitStruct.zlt = 0;
        epInitStruct.endpointAddress = interface->endpointList.endpoint[count].endpointAddress;
        epInitStruct.maxPacketSize = interface->endpointList.endpoint[count].maxPacketSize;
        epInitStruct.transferType = interface->endpointList.endpoint[count].transferType;

        if ((USB_IN == ((epInitStruct.endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
                        USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT)) &&
            (USB_ENDPOINT_INTERRUPT == epInitStruct.transferType))
        {
            cdcAcmHandle->interruptIn.ep = (epInitStruct.endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_NUMBER_MASK);
            cdcAcmHandle->interruptIn.isBusy = 0;
            epCallback.callbackFn = USB_DeviceCdcAcmInterruptIn;
        }

        epCallback.callbackParam = cdcAcmHandle;

        error = USB_DeviceInitEndpoint(cdcAcmHandle->handle, &epInitStruct, &epCallback);
    }

    for (int count = 0; count < interfaceList->count; count++)
    {
        if (USB_DEVICE_CONFIG_CDC_DATA_CLASS_CODE == interfaceList->interfaces[count].classCode)
        {
            for (int index = 0; index < interfaceList->interfaces[count].count; index++)
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

    for (int count = 0; count < interface->endpointList.count; count++)
    {
        usb_device_endpoint_init_struct_t epInitStruct;
        usb_device_endpoint_callback_struct_t epCallback;
        epInitStruct.zlt = 0;
        epInitStruct.endpointAddress = interface->endpointList.endpoint[count].endpointAddress;
        epInitStruct.maxPacketSize = interface->endpointList.endpoint[count].maxPacketSize;
        epInitStruct.transferType = interface->endpointList.endpoint[count].transferType;

        if ((USB_IN == ((epInitStruct.endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
                        USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT)) &&
            (USB_ENDPOINT_BULK == epInitStruct.transferType))
        {
            cdcAcmHandle->bulkIn.ep = (epInitStruct.endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_NUMBER_MASK);
            cdcAcmHandle->bulkIn.isBusy = 0;
            epCallback.callbackFn = USB_DeviceCdcAcmBulkIn;
        }
        else if ((USB_OUT == ((epInitStruct.endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
                              USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT)) &&
                 (USB_ENDPOINT_BULK == epInitStruct.transferType))
        {
            cdcAcmHandle->bulkOut.ep = (epInitStruct.endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_NUMBER_MASK);
            cdcAcmHandle->bulkOut.isBusy = 0;
            epCallback.callbackFn = USB_DeviceCdcAcmBulkOut;
        }
        else
        {
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
usb_status_t USB_DeviceCdcAcmEndpointsDeinit(usb_device_cdc_acm_struct_t *cdcAcmHandle)
{
    usb_status_t error = kStatus_USB_Error;

    if ((!cdcAcmHandle->commInterfaceHandle) || (!cdcAcmHandle->dataInterfaceHandle))
    {
        return error;
    }
    for (int count = 0; count < cdcAcmHandle->commInterfaceHandle->endpointList.count; count++)
    {
        error = USB_DeviceDeinitEndpoint(
            cdcAcmHandle->handle, cdcAcmHandle->commInterfaceHandle->endpointList.endpoint[count].endpointAddress);
    }
    for (int count = 0; count < cdcAcmHandle->dataInterfaceHandle->endpointList.count; count++)
    {
        error = USB_DeviceDeinitEndpoint(
            cdcAcmHandle->handle, cdcAcmHandle->dataInterfaceHandle->endpointList.endpoint[count].endpointAddress);
    }
    cdcAcmHandle->commInterfaceHandle = NULL;
    cdcAcmHandle->dataInterfaceHandle = NULL;

    return error;
}

/*!
* @brief Handles the CDC ACM class event.
*
* This function responses to various events includiing the common device events and the class specific events.
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
    uint16_t interfaceAlternate;
    uint8_t *temp8;
    uint8_t alternate;

    if ((!param) || (!handle))
    {
        return kStatus_USB_InvalidHandle;
    }

    cdcAcmHandle = (usb_device_cdc_acm_struct_t *)handle;

    switch (event)
    {
        case kUSB_DeviceClassEventDeviceReset:
            /* Bus reset, clear the configuration. */
            cdcAcmHandle->configuration = 0;
            break;
        case kUSB_DeviceClassEventSetConfiguration:
            temp8 = ((uint8_t *)param);
            if (!cdcAcmHandle->configStruct)
            {
                break;
            }
            if (*temp8 == cdcAcmHandle->configuration)
            {
                break;
            }

            error = USB_DeviceCdcAcmEndpointsDeinit(cdcAcmHandle);
            cdcAcmHandle->configuration = *temp8;
            cdcAcmHandle->alternate = 0;
            error = USB_DeviceCdcAcmEndpointsInit(cdcAcmHandle);
            if (kStatus_USB_Success != error)
            {
                usb_echo("kUSB_DeviceClassEventSetConfiguration, USB_DeviceInitEndpoint fail\r\n");
            }
            break;
        case kUSB_DeviceClassEventSetInterface:
            if (!cdcAcmHandle->configStruct)
            {
                break;
            }

            interfaceAlternate = *((uint16_t *)param);
            alternate = (uint8_t)(interfaceAlternate & 0xFFU);

            if (cdcAcmHandle->interfaceNumber != ((uint8_t)(interfaceAlternate >> 8U)))
            {
                break;
            }
            if (alternate == cdcAcmHandle->alternate)
            {
                break;
            }
            error = USB_DeviceCdcAcmEndpointsDeinit(cdcAcmHandle);
            cdcAcmHandle->alternate = alternate;
            error = USB_DeviceCdcAcmEndpointsInit(cdcAcmHandle);
            if (kStatus_USB_Success != error)
            {
                usb_echo("kUSB_DeviceClassEventSetInterface, USB_DeviceInitEndpoint fail\r\n");
            }
            break;
        case kUSB_DeviceClassEventSetEndpointHalt:
            if ((!cdcAcmHandle->configStruct) || (!cdcAcmHandle->commInterfaceHandle) ||
                (!cdcAcmHandle->dataInterfaceHandle))
            {
                break;
            }
            temp8 = ((uint8_t *)param);
            for (int count = 0; count < cdcAcmHandle->commInterfaceHandle->endpointList.count; count++)
            {
                if (*temp8 == cdcAcmHandle->commInterfaceHandle->endpointList.endpoint[count].endpointAddress)
                {
                    error = USB_DeviceStallEndpoint(cdcAcmHandle->handle, *temp8);
                }
            }
            for (int count = 0; count < cdcAcmHandle->dataInterfaceHandle->endpointList.count; count++)
            {
                if (*temp8 == cdcAcmHandle->dataInterfaceHandle->endpointList.endpoint[count].endpointAddress)
                {
                    error = USB_DeviceStallEndpoint(cdcAcmHandle->handle, *temp8);
                }
            }
            break;
        case kUSB_DeviceClassEventClearEndpointHalt:
            if ((!cdcAcmHandle->configStruct) || (!cdcAcmHandle->commInterfaceHandle) ||
                (!cdcAcmHandle->dataInterfaceHandle))
            {
                break;
            }
            temp8 = ((uint8_t *)param);
            for (int count = 0; count < cdcAcmHandle->commInterfaceHandle->endpointList.count; count++)
            {
                if (*temp8 == cdcAcmHandle->commInterfaceHandle->endpointList.endpoint[count].endpointAddress)
                {
                    error = USB_DeviceUnstallEndpoint(cdcAcmHandle->handle, *temp8);
                }
            }
            for (int count = 0; count < cdcAcmHandle->dataInterfaceHandle->endpointList.count; count++)
            {
                if (*temp8 == cdcAcmHandle->dataInterfaceHandle->endpointList.endpoint[count].endpointAddress)
                {
                    error = USB_DeviceUnstallEndpoint(cdcAcmHandle->handle, *temp8);
                }
            }
            break;
        case kUSB_DeviceClassEventClassRequest:
            if (param)
            {
                usb_device_control_request_struct_t *controlRequest = (usb_device_control_request_struct_t *)param;

                if ((controlRequest->setup->wIndex & 0xFFU) != cdcAcmHandle->interfaceNumber)
                {
                    break;
                }
                /* Standard CDC request */
                if (USB_REQUEST_TYPE_TYPE_CLASS == (controlRequest->setup->bmRequestType & USB_REQUEST_TYPE_TYPE_MASK))
                {
                    reqParam.buffer = &(controlRequest->buffer);
                    reqParam.length = &(controlRequest->length);
                    reqParam.interfaceIndex = controlRequest->setup->wIndex;
                    reqParam.setupValue = controlRequest->setup->wValue;
                    reqParam.isSetup = controlRequest->isSetup;
                    switch (controlRequest->setup->bRequest)
                    {
                        case USB_DEVICE_CDC_REQUEST_SEND_ENCAPSULATED_COMMAND:
                            error = cdcAcmHandle->configStruct->classCallback(
                                (class_handle_t)cdcAcmHandle, kUSB_DeviceCdcEventSendEncapsulatedCommand, &reqParam);
                            break;
                        case USB_DEVICE_CDC_REQUEST_GET_ENCAPSULATED_RESPONSE:
                            error = cdcAcmHandle->configStruct->classCallback(
                                (class_handle_t)cdcAcmHandle, kUSB_DeviceCdcEventGetEncapsulatedResponse, &reqParam);
                            break;
                        case USB_DEVICE_CDC_REQUEST_SET_COMM_FEATURE:
                            error = cdcAcmHandle->configStruct->classCallback(
                                (class_handle_t)cdcAcmHandle, kUSB_DeviceCdcEventSetCommFeature, &reqParam);
                            break;
                        case USB_DEVICE_CDC_REQUEST_GET_COMM_FEATURE:
                            error = cdcAcmHandle->configStruct->classCallback(
                                (class_handle_t)cdcAcmHandle, kUSB_DeviceCdcEventGetCommFeature, &reqParam);
                            break;
                        case USB_DEVICE_CDC_REQUEST_CLEAR_COMM_FEATURE:
                            error = cdcAcmHandle->configStruct->classCallback(
                                (class_handle_t)cdcAcmHandle, kUSB_DeviceCdcEventClearCommFeature, &reqParam);
                            break;
                        case USB_DEVICE_CDC_REQUEST_GET_LINE_CODING:
                            error = cdcAcmHandle->configStruct->classCallback(
                                (class_handle_t)cdcAcmHandle, kUSB_DeviceCdcEventGetLineCoding, &reqParam);
                            break;
                        case USB_DEVICE_CDC_REQUEST_SET_LINE_CODING:
                            error = cdcAcmHandle->configStruct->classCallback(
                                (class_handle_t)cdcAcmHandle, kUSB_DeviceCdcEventSetLineCoding, &reqParam);
                            break;
                        case USB_DEVICE_CDC_REQUEST_SET_CONTROL_LINE_STATE:
                            error = cdcAcmHandle->configStruct->classCallback(
                                (class_handle_t)cdcAcmHandle, kUSB_DeviceCdcEventSetControlLineState, &reqParam);
                            break;
                        case USB_DEVICE_CDC_REQUEST_SEND_BREAK:
                            error = cdcAcmHandle->configStruct->classCallback((class_handle_t)cdcAcmHandle,
                                                                              kUSB_DeviceCdcEventSendBreak, &reqParam);
                            break;
                        default:
                            error = kStatus_USB_InvalidRequest;
                            break;
                    }
                }
            }
            break;
        default:
            break;
    }
    return error;
}

/*!
 * @brief Initializes the USB CDC ACM class.
 *
 * This function obtains a usb device handle according to the controller id, initializes the CDC ACM class
 * with the class configure parameters and creats the mutex for each pipe.
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
    usb_status_t error = kStatus_USB_Error;

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

    if (!cdcAcmHandle->handle)
    {
        return kStatus_USB_InvalidHandle;
    }
    cdcAcmHandle->configStruct = config;
    cdcAcmHandle->configuration = 0;
    cdcAcmHandle->alternate = 0xFF;

    if (kStatus_USB_OSA_Success != USB_OsaMutexCreate(&(cdcAcmHandle->bulkIn.mutex)))
    {
        usb_echo("mutex create error!");
    }
    if (kStatus_USB_OSA_Success != USB_OsaMutexCreate(&(cdcAcmHandle->bulkOut.mutex)))
    {
        usb_echo("mutex create error!");
    }
    if (kStatus_USB_OSA_Success != USB_OsaMutexCreate(&(cdcAcmHandle->interruptIn.mutex)))
    {
        usb_echo("mutex create error!");
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
    usb_status_t error = kStatus_USB_Error;

    cdcAcmHandle = (usb_device_cdc_acm_struct_t *)handle;

    if (!cdcAcmHandle)
    {
        return kStatus_USB_InvalidHandle;
    }
    if (kStatus_USB_OSA_Success != USB_OsaMutexDestroy((cdcAcmHandle->bulkIn.mutex)))
    {
        usb_echo("mutex destroy error!");
    }
    if (kStatus_USB_OSA_Success != USB_OsaMutexDestroy((cdcAcmHandle->bulkOut.mutex)))
    {
        usb_echo("mutex destroy error!");
    }
    if (kStatus_USB_OSA_Success != USB_OsaMutexDestroy((cdcAcmHandle->interruptIn.mutex)))
    {
        usb_echo("mutex destroy error!");
    }
    error = USB_DeviceCdcAcmEndpointsDeinit(cdcAcmHandle);
    USB_DeviceCdcAcmFreeHandle(cdcAcmHandle);
    return error;
}

/*!
 * @brief Prime the endpoint to send packet to host.
 *
 * This function checks whether the endpoint is sending packet, then it primes the endpoint
 * with the buffer address and the buffer length if the pipe is not busy. Otherwise, it ignores this transfer by
 * returnning an error code.
 *
 * @param handle The class handle of the CDC ACM class.
 * @param ep The endpoint number of the transfer.
 * @param buffer The pointer to the buffer to be transferrd.
 * @param length The length of the buffer to be transferrd.
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceCdcAcmSend(class_handle_t handle, uint8_t ep, uint8_t *buffer, uint32_t length)
{
    usb_device_cdc_acm_struct_t *cdcAcmHandle;
    usb_status_t error = kStatus_USB_Error;
    usb_device_cdc_acm_pipe_t *cdcAcmPipe = NULL;

    if (!handle)
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
    }

    if (NULL != cdcAcmPipe)
    {
        if (1 == cdcAcmPipe->isBusy)
        {
            return kStatus_USB_Busy;
        }
        USB_CDC_ACM_ENTER_CRITICAL();
        error = USB_DeviceSendRequest(cdcAcmHandle->handle, ep, buffer, length);
        if (kStatus_USB_Success == error)
        {
            cdcAcmPipe->isBusy = 1;
        }
        USB_CDC_ACM_EXIT_CRITICAL();
    }
    return error;
}

/*!
 * @brief Prime the endpoint to receive packet from host.
 *
 * This function checks whether the endpoint is receiving packet, then it primes the endpoint
 * with the buffer address and the buffer length if the pipe is not busy. Otherwise, it ignores this transfer by
 * returnning an error code.
 *
 * @param handle The class handle of the CDC ACM class.
 * @param ep The endpoint number of the transfer.
 * @param buffer The pointer to the buffer to be transferrd.
 * @param length The length of the buffer to be transferrd.
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceCdcAcmRecv(class_handle_t handle, uint8_t ep, uint8_t *buffer, uint32_t length)
{
    usb_device_cdc_acm_struct_t *cdcAcmHandle;
    usb_status_t error = kStatus_USB_Error;
    if (!handle)
    {
        return kStatus_USB_InvalidHandle;
    }
    cdcAcmHandle = (usb_device_cdc_acm_struct_t *)handle;

    if (1 == cdcAcmHandle->bulkOut.isBusy)
    {
        return kStatus_USB_Busy;
    }
    USB_CDC_ACM_ENTER_CRITICAL();
    error = USB_DeviceRecvRequest(cdcAcmHandle->handle, ep, buffer, length);
    if (kStatus_USB_Success == error)
    {
        cdcAcmHandle->bulkOut.isBusy = 1;
    }
    USB_CDC_ACM_EXIT_CRITICAL();
    return error;
}

#endif /* USB_DEVICE_CONFIG_CDC_ACM */

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

#if ((defined(USB_DEVICE_CONFIG_MSC)) && (USB_DEVICE_CONFIG_MSC > 0U))
#include "usb_device_msc.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
usb_status_t USB_DeviceMscRecv(usb_device_msc_struct_t *mscHandle);
usb_status_t USB_DeviceMscSend(usb_device_msc_struct_t *mscHandle);
/*******************************************************************************
 * Variables
 ******************************************************************************/

USB_GLOBAL usb_device_msc_struct_t g_msc_handle[USB_DEVICE_CONFIG_MSC_MAX_INSTANCE];
/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Allocate a device msc class handle.
 *
 * This function allocates a device msc class handle.
 *
 * @param handle          It is out parameter, is used to return pointer of the device msc class handle to the caller.
 *
 * @retval kStatus_USB_Success              Get a device msc class handle successfully.
 * @retval kStatus_USB_Busy                 Cannot allocate a device msc class handle.
 */

static usb_status_t USB_DeviceMscAllocateHandle(usb_device_msc_struct_t **handle)
{
    uint32_t count;
    for (count = 0; count < USB_DEVICE_CONFIG_MSC_MAX_INSTANCE; count++)
    {
        if (NULL == g_msc_handle[count].handle)
        {
            *handle = &g_msc_handle[count];
            return kStatus_USB_Success;
        }
    }

    return kStatus_USB_Busy;
}

/*!
 * @brief Free a device msc class hanlde.
 *
 * This function frees a device msc class hanlde.
 *
 * @param handle          The device msc class hanlde.
 *
 * @retval kStatus_USB_Success              Free device msc class hanlde successfully.
 */
static usb_status_t USB_DeviceMscFreeHandle(usb_device_msc_struct_t *handle)
{
    handle->handle = NULL;
    handle->configurationStruct = (usb_device_class_config_struct_t *)NULL;
    handle->configuration = 0;
    handle->alternate = 0;
    return kStatus_USB_Success;
}

/*!
 * @brief Process usb msc ufi command.
 *
 * This function analyse the cbw , get the command code.
 *
 * @param handle          The device msc class hanlde.
 *
 * @retval kStatus_USB_Success              Free device msc class hanlde successfully.
 */
usb_status_t USB_DeviceMscProcessUfiCommand(usb_device_msc_struct_t *mscHandle)
{
    usb_status_t error = kStatus_USB_Error;
    usb_device_msc_ufi_struct_t *ufi = NULL;

    ufi = &mscHandle->mscUfi;

    ufi->requestSense.senseKey = USB_DEVICE_MSC_UFI_NO_SENSE;
    ufi->requestSense.additionalSenseCode = USB_DEVICE_MSC_UFI_NO_SENSE;
    ufi->requestSense.additionalSenseQualifer = USB_DEVICE_MSC_UFI_NO_SENSE;
    ufi->thirteenCase.hostExpectedDataLength = mscHandle->mscCbw.dataTransferLength;
    ufi->thirteenCase.hostExpectedDirection = (uint8_t)(mscHandle->mscCbw.flags >> USB_DEVICE_MSC_CBW_DIRECTION_SHIFT);
    /*The first byte of all ufi command blocks shall contain an Operation Code, refer to ufi spec*/
    switch (mscHandle->mscCbw.cbwcb[0])
    {
        /* ufi commmand operation code*/
        case USB_DEVICE_MSC_INQUIRY_COMMAND: /*operation code : 0x12*/
            error = USB_DeviceMscUfiInquiryCommand(mscHandle);
            break;
        case USB_DEVICE_MSC_READ_10_COMMAND: /*operation code : 0x28 */
        case USB_DEVICE_MSC_READ_12_COMMAND: /*operation code : 0xA8 */
            error = USB_DeviceMscUfiReadCommand(mscHandle);
            break;
        case USB_DEVICE_MSC_REQUEST_SENSE_COMMAND: /*operation code : 0x03*/
            error = USB_DeviceMscUfiRequestSenseCommand(mscHandle);
            break;
        case USB_DEVICE_MSC_TEST_UNIT_READY_COMMAND: /*operation code : 0x00 */
            error = USB_DeviceMscUfiTestUnitReadyCommand(mscHandle);
            break;
        case USB_DEVICE_MSC_WRITE_10_COMMAND: /*operation code : 0x2A */
        case USB_DEVICE_MSC_WRITE_12_COMMAND: /*operation code : 0xAA */
            error = USB_DeviceMscUfiWriteCommand(mscHandle);
            break;
        case USB_DEVICE_MSC_PREVENT_ALLOW_MEDIUM_REM_COMMAND: /*operation code :0x1E */
            error = USB_DeviceMscUfiPreventAllowMediumCommand(mscHandle);
            break;
        case USB_DEVICE_MSC_FORMAT_UNIT_COMMAND: /*operation code : 0x04*/
            error = USB_DeviceMscUfiFormatUnitCommand(mscHandle);
            break;
        case USB_DEVICE_MSC_READ_CAPACITY_10_COMMAND: /*operation code : 0x25*/
        case USB_DEVICE_MSC_READ_CAPACITY_16_COMMAND: /*operation code : 0x9E*/
            error = USB_DeviceMscUfiReadCapacityCommand(mscHandle);
            break;
        case USB_DEVICE_MSC_MODE_SENSE_10_COMMAND: /* operation code :0x5A*/
        case USB_DEVICE_MSC_MODE_SENSE_6_COMMAND:  /* operation code : 0x1A */
            error = USB_DeviceMscUfiModeSenseCommand(mscHandle);
            break;
        case USB_DEVICE_MSC_MODE_SELECT_10_COMMAND: /*operation code : 0x55 */
        case USB_DEVICE_MSC_MODE_SELECT_6_COMMAND:  /*operation code : 0x15 */
            error = USB_DeviceMscUfiModeSelectCommand(mscHandle);
            break;
        case USB_DEVICE_MSC_READ_FORMAT_CAPACITIES_COMMAND: /*operation code : 0x23 */
            error = USB_DeviceMscUfiReadFormatCapacityCommand(mscHandle);
            break;
        case USB_DEVICE_MSC_SEND_DIAGNOSTIC_COMMAND: /*operation code : 0x1D*/
            error = USB_DeviceMscUfiSendDiagnosticCommand(mscHandle);
            break;
        case USB_DEVICE_MSC_VERIFY_COMMAND: /*operation code : 0x2F*/
            error = USB_DeviceMscUfiVerifyCommand(mscHandle);
            break;
        case USB_DEVICE_MSC_START_STOP_UNIT_COMMAND: /*operation code : 0x1B*/
            error = USB_DeviceMscUfiStartStopUnitCommand(mscHandle);
            break;
        default:
            error = USB_DeviceMscUfiUnsupportCommand(mscHandle);
            mscHandle->dataOutFlag = 0;
            mscHandle->dataInFlag = 0;
            mscHandle->outEndpointStallFlag = 0;
            mscHandle->inEndpointStallFlag = 0;
            mscHandle->needOutStallFlag = 0;
            mscHandle->needInStallFlag = 0;
            break;
    }
    return error;
}

/*!
 * @brief Bulk IN endpoint callback function.
 *
 * This callback function is used to notify uplayer the tranfser result of a transfer.
 * This callback pointer is passed when the Bulk IN pipe initialized.
 *
 * @param handle          The device handle. It equals the value returned from USB_DeviceInit.
 * @param message         The result of the Bulk IN pipe transfer.
 * @param callbackParam  The paramter for this callback. It is same with
 * usb_device_endpoint_callback_struct_t::callbackParam. In the class, the value is the MSC class handle.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceMscBulkIn(usb_device_handle handle,
                                        usb_device_endpoint_callback_message_struct_t *message,
                                        void *callbackParam)
{
    usb_device_msc_struct_t *mscHandle = (usb_device_msc_struct_t *)callbackParam;
    usb_device_msc_csw_t *csw;
    usb_status_t error = kStatus_USB_Error;

    if (message->length == USB_UNINITIALIZED_VAL_32)
    {
        if ((mscHandle->dataInFlag) && (mscHandle->configurationStruct->classCallback != NULL) &&
            ((USB_DEVICE_MSC_READ_10_COMMAND == mscHandle->mscCbw.cbwcb[0]) ||
             (USB_DEVICE_MSC_READ_12_COMMAND == mscHandle->mscCbw.cbwcb[0])))
        {
            usb_device_lba_app_struct_t lbaData;

            lbaData.size = 0;
            lbaData.buffer = message->buffer;
            lbaData.offset = 0;
            mscHandle->configurationStruct->classCallback((class_handle_t)mscHandle, kUSB_DeviceMscEventReadResponse,
                                                          (void *)&lbaData);
        }
        return error;
    }
    if (mscHandle->transferRemaining >= message->length)
    {
        mscHandle->transferRemaining -= message->length;
    }

    if (mscHandle->needInStallFlag == 1)
    {
        mscHandle->needInStallFlag = 0;
        mscHandle->inEndpointStallFlag = 1;
        mscHandle->dataInFlag = 0;
        USB_DeviceStallEndpoint(mscHandle->handle, mscHandle->bulkInEndpoint);
        return error;
    }
    if ((!mscHandle->dataInFlag) && (message->length == USB_DEVICE_MSC_CSW_LENGTH))
    {
        csw = (usb_device_msc_csw_t *)(message->buffer);
    }

    if (mscHandle->dataInFlag)
    {
        if ((mscHandle->configurationStruct->classCallback != NULL))
        {
            usb_device_lba_app_struct_t lbaData;

            lbaData.size = message->length;
            lbaData.buffer = message->buffer;
            lbaData.offset = mscHandle->currentOffset;

            if ((USB_DEVICE_MSC_READ_10_COMMAND == mscHandle->mscCbw.cbwcb[0]) ||
                (USB_DEVICE_MSC_READ_12_COMMAND == mscHandle->mscCbw.cbwcb[0]))
            {
                mscHandle->configurationStruct->classCallback((class_handle_t)mscHandle,
                                                              kUSB_DeviceMscEventReadResponse, (void *)&lbaData);
            }

            if (mscHandle->transferRemaining)
            {
                mscHandle->currentOffset += message->length;
                error = USB_DeviceMscSend(mscHandle);
            }
            if (!mscHandle->transferRemaining)
            {
                mscHandle->dataInFlag = 0;
                /*data transfer has been done, send the csw to host */
                USB_DeviceSendRequest(mscHandle->handle, mscHandle->bulkInEndpoint, (uint8_t *)&mscHandle->mscCsw,
                                      USB_DEVICE_MSC_CSW_LENGTH);
            }
        }
    }
    else if ((message->length == USB_DEVICE_MSC_CSW_LENGTH) && (csw->signature == USB_DEVICE_MSC_DCSWSIGNATURE))
    {
        mscHandle->cbwValidFlag = 1;

        (void)USB_DeviceRecvRequest(mscHandle->handle, mscHandle->bulkOutEndpoint, (uint8_t *)&mscHandle->mscCbw,
                                    USB_DEVICE_MSC_CBW_LENGTH);
        mscHandle->cbwPrimeFlag = 1;
    }
    else
    {
    }
    return error;
}

/*!
 * @brief Bulk OUT endpoint callback function.
 *
 * This callback function is used to notify uplayer the tranfser result of a transfer.
 * This callback pointer is passed when the Bulk OUT pipe initialized.
 *
 * @param handle          The device handle. It equals the value returned from USB_DeviceInit.
 * @param message         The result of the Bulk OUT pipe transfer.
 * @param callbackParam  The paramter for this callback. It is same with
 * usb_device_endpoint_callback_struct_t::callbackParam. In the class, the value is the MSC class handle.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceMscBulkOut(usb_device_handle handle,
                                  usb_device_endpoint_callback_message_struct_t *message,
                                  void *callbackParam)
{
    usb_device_msc_struct_t *mscHandle = (usb_device_msc_struct_t *)callbackParam;
    usb_status_t error = kStatus_USB_Success;
    if (message->length == USB_UNINITIALIZED_VAL_32)
    {
        if ((mscHandle->dataInFlag) && (mscHandle->configurationStruct->classCallback != NULL) &&
            ((USB_DEVICE_MSC_WRITE_10_COMMAND == mscHandle->mscCbw.cbwcb[0]) ||
             (USB_DEVICE_MSC_WRITE_12_COMMAND == mscHandle->mscCbw.cbwcb[0])))
        {
            usb_device_lba_app_struct_t lbaData;

            lbaData.size = 0;
            lbaData.buffer = message->buffer;
            lbaData.offset = 0;
            mscHandle->configurationStruct->classCallback((class_handle_t)mscHandle, kUSB_DeviceMscEventWriteResponse,
                                                          (void *)&lbaData);
        }
        return error;
    }

    if (mscHandle->transferRemaining >= message->length)
    {
        mscHandle->transferRemaining -= message->length;
    }

    if (mscHandle->needOutStallFlag == 1)
    {
        mscHandle->needOutStallFlag = 0;
        mscHandle->outEndpointStallFlag = 1;
        mscHandle->dataOutFlag = 0;
        mscHandle->cbwPrimeFlag = 0;
        USB_DeviceStallEndpoint(mscHandle->handle, mscHandle->bulkOutEndpoint);
        return error;
    }

    if (mscHandle->dataOutFlag)
    {
        usb_device_lba_app_struct_t lbaData;

        lbaData.size = message->length;
        lbaData.buffer = message->buffer;
        lbaData.offset = mscHandle->currentOffset;

        if ((mscHandle->configurationStruct->classCallback != NULL))
        {
            if ((USB_DEVICE_MSC_WRITE_10_COMMAND == mscHandle->mscCbw.cbwcb[0]) ||
                (USB_DEVICE_MSC_WRITE_12_COMMAND == mscHandle->mscCbw.cbwcb[0]))
            {
                mscHandle->configurationStruct->classCallback((class_handle_t)mscHandle,
                                                              kUSB_DeviceMscEventWriteResponse, (void *)&lbaData);
            }

            if (mscHandle->transferRemaining)
            {
                mscHandle->currentOffset += message->length;
                error = USB_DeviceMscRecv(mscHandle);
            }
        }

        if (!mscHandle->transferRemaining)
        {
            mscHandle->dataOutFlag = 0;
            {
                USB_DeviceSendRequest(mscHandle->handle, mscHandle->bulkInEndpoint, (uint8_t *)&mscHandle->mscCsw,
                                      USB_DEVICE_MSC_CSW_LENGTH);
                mscHandle->cswPrimeFlag = 1;
            }
        }
    }
    else if ((mscHandle->cbwValidFlag) && (message->length == USB_DEVICE_MSC_CBW_LENGTH) &&
             (mscHandle->mscCbw.signature == USB_DEVICE_MSC_DCBWSIGNATURE) &&
             (!((mscHandle->mscCbw.logicalUnitNumber & 0xF0) || (mscHandle->mscCbw.cbLength & 0xE0))) &&
             (mscHandle->mscCbw.logicalUnitNumber < (mscHandle->logicalUnitNumber + 1)) &&
             ((mscHandle->mscCbw.cbLength >= 0x01) && (mscHandle->mscCbw.cbLength <= 0x10)))
    {
        mscHandle->cbwPrimeFlag = 0;
        mscHandle->transferRemaining = 0;

        mscHandle->mscCsw.signature = USB_DEVICE_MSC_DCSWSIGNATURE;
        mscHandle->mscCsw.dataResidue = 0;
        mscHandle->mscCsw.tag = mscHandle->mscCbw.tag;

        mscHandle->cbwValidFlag = 0;

        mscHandle->mscCbw.dataTransferLength = USB_LONG_TO_LITTLE_ENDIAN(mscHandle->mscCbw.dataTransferLength);

        mscHandle->dataOutFlag = (uint8_t)(((!(mscHandle->mscCbw.flags & USB_DEVICE_MSC_CBW_DIRECTION_BIT)) &&
                                            (mscHandle->mscCbw.dataTransferLength)) ?
                                               1 :
                                               0);

        mscHandle->dataInFlag = (uint8_t)(
            ((mscHandle->mscCbw.flags & USB_DEVICE_MSC_CBW_DIRECTION_BIT) && (mscHandle->mscCbw.dataTransferLength)) ?
                1 :
                0);

        if ((0 != mscHandle->dataInFlag) && (0 != mscHandle->inEndpointStallFlag))
        {
            error = kStatus_USB_Error;
            return error;
        }
        error = USB_DeviceMscProcessUfiCommand(mscHandle);
        if (error == kStatus_USB_InvalidRequest)
        {
            if (mscHandle->dataOutFlag == 1)
            {
                if (mscHandle->outEndpointStallFlag == 0)
                {
                    mscHandle->needOutStallFlag = 1;
                }
                mscHandle->dataOutFlag = 0;
            }
            else if (mscHandle->dataInFlag == 1)
            {
                if (mscHandle->inEndpointStallFlag == 0)
                {
                    mscHandle->needInStallFlag = 1;
                }
                mscHandle->dataInFlag = 0;
            }
            else
            {
            }
            mscHandle->stallStatus = (uint8_t)USB_DEVICE_MSC_STALL_IN_DATA;
        }

        if (!((mscHandle->dataOutFlag) || ((mscHandle->dataInFlag) || (mscHandle->needInStallFlag))))
        {
            USB_DeviceSendRequest(mscHandle->handle, mscHandle->bulkInEndpoint, (uint8_t *)&mscHandle->mscCsw,
                                  USB_DEVICE_MSC_CSW_LENGTH);
            mscHandle->cswPrimeFlag = 1;
        }
    }
    else
    {
        USB_DeviceStallEndpoint(mscHandle->handle, mscHandle->bulkOutEndpoint);
        USB_DeviceStallEndpoint(mscHandle->handle, mscHandle->bulkInEndpoint);
        mscHandle->cbwValidFlag = 0;
        mscHandle->outEndpointStallFlag = 1;
        mscHandle->inEndpointStallFlag = 1;
        mscHandle->stallStatus = (uint8_t)USB_DEVICE_MSC_STALL_IN_CBW;
        mscHandle->performResetRecover = 1;
    }
    return error;
}

/*!
 * @brief Initialize the endpoints of the msc class.
 *
 * This callback function is used to initialize the endpoints of the msc class.
 *
 * @param mscHandle          The device msc class handle. It equals the value returned from
 * usb_device_class_config_struct_t::classHandle.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceMscEndpointsInit(usb_device_msc_struct_t *mscHandle)
{
    usb_device_interface_list_t *interfaceList;
    usb_device_interface_struct_t *interface = (usb_device_interface_struct_t *)NULL;
    usb_status_t error = kStatus_USB_Error;

    /* Check the configuration is valid or not. */
    if (mscHandle->configuration > mscHandle->configurationStruct->classInfomation->configurations)
    {
        return error;
    }

    /* Get the interface list of the new configuration. */
    /* Check the interface list is valid or not. */
    if (NULL == mscHandle->configurationStruct->classInfomation->interfaceList)
    {
        return error;
    }
    interfaceList = &mscHandle->configurationStruct->classInfomation->interfaceList[mscHandle->configuration - 1];

    /* Find interface by using the alternate setting of the interface. */
    for (int count = 0; count < interfaceList->count; count++)
    {
        if (USB_DEVICE_CONFIG_MSC_CLASS_CODE == interfaceList->interfaces[count].classCode)
        {
            for (int index = 0; index < interfaceList->interfaces[count].count; index++)
            {
                if (interfaceList->interfaces[count].interface[index].alternateSetting == mscHandle->alternate)
                {
                    interface = &interfaceList->interfaces[count].interface[index];
                    break;
                }
            }
            mscHandle->interfaceNumber = interfaceList->interfaces[count].interfaceNumber;
            break;
        }
    }
    if (!interface)
    {
        /* Return error if the interface is not found. */
        return error;
    }

    /* Keep new interface handle. */
    mscHandle->interfaceHandle = interface;
    /* Initialize the endpoints of the new interface. */
    for (int count = 0; count < interface->endpointList.count; count++)
    {
        usb_device_endpoint_init_struct_t epInitStruct;
        usb_device_endpoint_callback_struct_t ep_callback;
        epInitStruct.zlt = 0;
        epInitStruct.endpointAddress = interface->endpointList.endpoint[count].endpointAddress;
        epInitStruct.maxPacketSize = interface->endpointList.endpoint[count].maxPacketSize;
        epInitStruct.transferType = interface->endpointList.endpoint[count].transferType;

        if (USB_IN == ((epInitStruct.endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
                       USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT))
        {
            mscHandle->bulkInEndpoint = epInitStruct.endpointAddress;
            ep_callback.callbackFn = USB_DeviceMscBulkIn;
        }
        else
        {
            mscHandle->bulkOutEndpoint = epInitStruct.endpointAddress;
            ep_callback.callbackFn = USB_DeviceMscBulkOut;
        }
        ep_callback.callbackParam = mscHandle;

        error = USB_DeviceInitEndpoint(mscHandle->handle, &epInitStruct, &ep_callback);
    }

    mscHandle->dataOutFlag = 0;
    mscHandle->dataInFlag = 0;
    mscHandle->outEndpointStallFlag = 0;
    mscHandle->inEndpointStallFlag = 0;
    mscHandle->needOutStallFlag = 0;
    mscHandle->needInStallFlag = 0;
    mscHandle->cbwValidFlag = 1;
    mscHandle->transferRemaining = 0;
    mscHandle->performResetRecover = 0;
    mscHandle->performResetDoneFlag = 0;
    mscHandle->stallStatus = 0;

    if (mscHandle->cbwPrimeFlag == 1)
    {
        USB_DeviceCancel(mscHandle->handle, mscHandle->bulkOutEndpoint);
    }
    USB_DeviceRecvRequest(mscHandle->handle, mscHandle->bulkOutEndpoint, (uint8_t *)&mscHandle->mscCbw,
                          USB_DEVICE_MSC_CBW_LENGTH);
    mscHandle->cbwPrimeFlag = 1;

    return error;
}

/*!
 * @brief De-initialize the endpoints of the msc class.
 *
 * This callback function is used to de-initialize the endpoints of the msc class.
 *
 * @param mscHandle          The device msc class handle. It equals the value returned from
 * usb_device_class_config_struct_t::classHandle.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceMscEndpointsDeinit(usb_device_msc_struct_t *mscHandle)
{
    usb_status_t error = kStatus_USB_Error;

    if (!mscHandle->interfaceHandle)
    {
        return error;
    }
    /* De-initialize all endpoints of the interface */
    for (int count = 0; count < mscHandle->interfaceHandle->endpointList.count; count++)
    {
        error = USB_DeviceDeinitEndpoint(mscHandle->handle,
                                         mscHandle->interfaceHandle->endpointList.endpoint[count].endpointAddress);
    }
    return error;
}

/*!
 * @brief Initialize the msc class.
 *
 * This function is used to initialize the msc class.
 *
 * @param controllerId   The controller id of the USB IP. Please refer to the enumeration usb_controller_index_t.
 * @param config          The class configuration information.
 * @param handle          It is out parameter, is used to return pointer of the msc class handle to the caller.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceMscInit(uint8_t controllerId, usb_device_class_config_struct_t *config, class_handle_t *handle)
{
    usb_device_msc_struct_t *mscHandle;
    usb_status_t error = kStatus_USB_Error;
    uint32_t implementingDiskDrive = USB_DEVICE_CONFIG_MSC_IMPLEMENTING_DISK_DRIVE;
    usb_device_lba_information_struct_t diskInformation;
    usb_device_msc_ufi_struct_t *ufi = NULL;

    /* Allocate a msc class handle. */
    error = USB_DeviceMscAllocateHandle(&mscHandle);

    if (kStatus_USB_Success != error)
    {
        return error;
    }

    /* Get the device handle according to the controller id. */
    error = USB_DeviceClassGetDeviceHandle(controllerId, &mscHandle->handle);

    if (kStatus_USB_Success != error)
    {
        USB_DeviceMscFreeHandle(mscHandle);
        return error;
    }
    if (!mscHandle->handle)
    {
        USB_DeviceMscFreeHandle(mscHandle);
        return kStatus_USB_InvalidHandle;
    }
    /* Save the configuration of the class. */
    mscHandle->configurationStruct = config;
    /* Clear the configuration value. */
    mscHandle->configuration = 0;
    mscHandle->alternate = 0xff;

    /* Get device information. */
    error = mscHandle->configurationStruct->classCallback(
        (class_handle_t)mscHandle, kUSB_DeviceMscEventGetLbaInformation, (void *)&diskInformation);

    if (((diskInformation.lengthOfEachLba) && (diskInformation.totalLbaNumberSupports)) == 0)
    {
        error = kStatus_USB_Error;
        USB_DeviceMscFreeHandle(mscHandle);
        return error;
    }
    mscHandle->logicalUnitNumber = diskInformation.logicalUnitNumberSupported;
    /*initialize the basic device information*/
    ufi = &mscHandle->mscUfi;
    mscHandle->totalLogicalBlockNumber = diskInformation.totalLbaNumberSupports;
    mscHandle->lengthOfEachLba = diskInformation.lengthOfEachLba;
    mscHandle->logicalUnitNumber = diskInformation.logicalUnitNumberSupported - 1;
    mscHandle->bulkInBufferSize = diskInformation.bulkInBufferSize;
    mscHandle->bulkOutBufferSize = diskInformation.bulkOutBufferSize;
    mscHandle->implementingDiskDrive = implementingDiskDrive;

    ufi->requestSense.validErrorCode = USB_DEVICE_MSC_UFI_REQ_SENSE_VALID_ERROR_CODE;
    ufi->requestSense.additionalSenseLength = USB_DEVICE_MSC_UFI_REQ_SENSE_ADDITIONAL_SENSE_LEN;
    ufi->requestSense.senseKey = USB_DEVICE_MSC_UFI_NO_SENSE;
    ufi->requestSense.additionalSenseCode = USB_DEVICE_MSC_UFI_NO_SENSE;
    ufi->requestSense.additionalSenseQualifer = USB_DEVICE_MSC_UFI_NO_SENSE;

    ufi->readCapacity.lastLogicalBlockAddress = USB_LONG_TO_BIG_ENDIAN(mscHandle->totalLogicalBlockNumber - 1);
    ufi->readCapacity.blockSize = USB_LONG_TO_BIG_ENDIAN((uint32_t)mscHandle->lengthOfEachLba);
    ufi->readCapacity16.lastLogicalBlockAddress1 = USB_LONG_TO_BIG_ENDIAN(mscHandle->totalLogicalBlockNumber - 1);
    ufi->readCapacity16.blockSize = USB_LONG_TO_BIG_ENDIAN((uint32_t)mscHandle->lengthOfEachLba);

    mscHandle->cbwPrimeFlag = 0;
    mscHandle->cswPrimeFlag = 0;

    *handle = (class_handle_t)mscHandle;
    return error;
}

/*!
 * @brief De-initialize the device msc class.
 *
 * The function de-initializes the device msc class.
 *
 * @param handle The msc class handle got from usb_device_class_config_struct_t::classHandle.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceMscDeinit(class_handle_t handle)
{
    usb_device_msc_struct_t *mscHandle;
    usb_status_t error = kStatus_USB_Error;

    mscHandle = (usb_device_msc_struct_t *)handle;

    if (!mscHandle)
    {
        return kStatus_USB_InvalidHandle;
    }
    error = USB_DeviceMscEndpointsDeinit(mscHandle);
    USB_DeviceMscFreeHandle(mscHandle);
    return error;
}

/*!
 * @brief Handle the event passed to the msc class.
 *
 * This function handles the event passed to the msc class.
 *
 * @param handle          The msc class handle, got from the usb_device_class_config_struct_t::classHandle.
 * @param event           The event codes. Please refer to the enumeration usb_device_class_event_t.
 * @param param           The param type is determined by the event code.
 *
 * @return A USB error code or kStatus_USB_Success.
 * @retval kStatus_USB_Success              Free device handle successfully.
 * @retval kStatus_USB_InvalidParameter     The device handle not be found.
 * @retval kStatus_USB_InvalidRequest       The request is invalid, and the control pipe will be stalled by the caller.
 */
usb_status_t USB_DeviceMscEvent(void *handle, uint32_t event, void *param)
{
    usb_status_t error = kStatus_USB_Error;
    usb_device_msc_struct_t *mscHandle;

    uint16_t interfaceAlternate;
    uint8_t *temp8;
    uint8_t alternate;

    if ((!param) || (!handle))
    {
        return kStatus_USB_InvalidHandle;
    }

    /* Get the msc class handle. */
    mscHandle = (usb_device_msc_struct_t *)handle;
    switch (event)
    {
        case kUSB_DeviceClassEventDeviceReset:
            /* Bus reset, clear the configuration. */
            mscHandle->configuration = 0;
            break;
        case kUSB_DeviceClassEventSetConfiguration:
            /* Get the new configuration. */
            temp8 = ((uint8_t *)param);
            if (!mscHandle->configurationStruct)
            {
                break;
            }
            if (*temp8 == mscHandle->configuration)
            {
                break;
            }

            if (mscHandle->configuration)
            {
                /* De-initialize the endpoints when current configuration is none zero. */
                error = USB_DeviceMscEndpointsDeinit(mscHandle);
            }
            /* Save new configuration. */
            mscHandle->configuration = *temp8;
            /* Clear the alternate setting value. */
            mscHandle->alternate = 0;
            /* Initialize the endpoints of the new current configuration by using the alternate setting 0. */
            error = USB_DeviceMscEndpointsInit(mscHandle);
            break;
        case kUSB_DeviceClassEventSetInterface:

            if (!mscHandle->configurationStruct)
            {
                break;
            }
            /* Get the new alternate setting of the interface */
            interfaceAlternate = *((uint16_t *)param);
            /* Get the alternate setting value */
            alternate = (uint8_t)(interfaceAlternate & 0xFF);

            /* Whether the interface belongs to the class. */
            if (mscHandle->interfaceNumber != ((uint8_t)(interfaceAlternate >> 8)))
            {
                break;
            }
            /* Only handle new alternate setting. */
            if (alternate == mscHandle->alternate)
            {
                break;
            }
            /* De-initialize old endpoints */
            error = USB_DeviceMscEndpointsDeinit(mscHandle);
            mscHandle->alternate = alternate;
            /* Initialize new endpoints */
            error = USB_DeviceMscEndpointsInit(mscHandle);
            break;
        case kUSB_DeviceClassEventSetEndpointHalt:
            if ((!mscHandle->configurationStruct) || (!mscHandle->interfaceHandle))
            {
                break;
            }
            /* Get the endpoint address */
            temp8 = ((uint8_t *)param);
            for (int count = 0; count < mscHandle->interfaceHandle->endpointList.count; count++)
            {
                if (*temp8 == mscHandle->interfaceHandle->endpointList.endpoint[count].endpointAddress)
                {
                    if (mscHandle->inEndpointStallFlag == 0)
                    {
                        /* Only stall the endpoint belongs to the class */
                        error = USB_DeviceStallEndpoint(mscHandle->handle, *temp8);
                        mscHandle->inEndpointStallFlag = 1;
                    }
                    if (mscHandle->outEndpointStallFlag == 0)
                    {
                        error = USB_DeviceStallEndpoint(mscHandle->handle, *temp8);
                        mscHandle->inEndpointStallFlag = 0;
                    }
                }
            }

            break;
        case kUSB_DeviceClassEventClearEndpointHalt:
            if ((!mscHandle->configurationStruct) || (!mscHandle->interfaceHandle) ||
                (mscHandle->performResetRecover == 1))
            {
                break;
            }
            /* Get the endpoint address */
            temp8 = ((uint8_t *)param);
            for (int count = 0; count < mscHandle->interfaceHandle->endpointList.count; count++)
            {
                if (*temp8 == mscHandle->interfaceHandle->endpointList.endpoint[count].endpointAddress)
                {
                    /* Only un-stall the endpoint belongs to the class , If the dedpoint is in stall status ,then
                     * un-stall it*/
                    if (mscHandle->inEndpointStallFlag == 1)
                    {
                        error = USB_DeviceUnstallEndpoint(mscHandle->handle, *temp8);
                        mscHandle->inEndpointStallFlag = 0;
                    }
                    if (mscHandle->outEndpointStallFlag == 1)
                    {
                        error = USB_DeviceUnstallEndpoint(mscHandle->handle, *temp8);
                        mscHandle->inEndpointStallFlag = 0;
                    }
                }
            }
            if (((mscHandle->stallStatus == USB_DEVICE_MSC_STALL_IN_CSW) ||
                 (mscHandle->stallStatus == USB_DEVICE_MSC_STALL_IN_DATA)) &&
                (mscHandle->performResetDoneFlag != 1))
            {
                if (mscHandle->cswPrimeFlag == 1)
                {
                    USB_DeviceCancel(mscHandle->handle, mscHandle->bulkInEndpoint);
                }
                /*send csw*/
                USB_DeviceSendRequest(mscHandle->handle, mscHandle->bulkInEndpoint, (uint8_t *)&mscHandle->mscCsw,
                                      USB_DEVICE_MSC_CSW_LENGTH);
                mscHandle->cswPrimeFlag = 0;
                mscHandle->stallStatus = 0;
            }
            if ((mscHandle->performResetDoneFlag == 1) && (mscHandle->inEndpointStallFlag == 0) &&
                (mscHandle->outEndpointStallFlag == 0))
            {
                mscHandle->performResetDoneFlag = 0;
                if (mscHandle->cswPrimeFlag == 1)
                {
                    USB_DeviceCancel(mscHandle->handle, mscHandle->bulkInEndpoint);
                }
                /*prime cbw for new transfer*/
                USB_DeviceRecvRequest(mscHandle->handle, mscHandle->bulkOutEndpoint, (uint8_t *)&mscHandle->mscCbw,
                                      USB_DEVICE_MSC_CBW_LENGTH);
                mscHandle->cswPrimeFlag = 0;
                mscHandle->stallStatus = 0;
            }
            break;
        case kUSB_DeviceClassEventClassRequest:
            if (param)
            {
                /* Handle the msc class specific request. */
                usb_device_control_request_struct_t *control_request = (usb_device_control_request_struct_t *)param;

                if ((control_request->setup->bmRequestType & USB_REQUEST_TYPE_RECIPIENT_MASK) !=
                    USB_REQUEST_TYPE_RECIPIENT_INTERFACE)
                {
                    break;
                }

                if ((control_request->setup->wIndex & 0xFF) != mscHandle->interfaceNumber)
                {
                    break;
                }

                switch (control_request->setup->bRequest)
                {
                    case USB_DEVICE_MSC_GET_MAX_LUN:
                        /*Get Max LUN */
                        if ((control_request->setup->wIndex == mscHandle->interfaceNumber) &&
                            (!control_request->setup->wValue) && (control_request->setup->wLength <= 0x0001) &&
                            ((control_request->setup->bmRequestType & USB_REQUSET_TYPE_DIR_MASK) ==
                             USB_REQUEST_TYPE_DIR_IN))
                        {
                            control_request->buffer = &mscHandle->logicalUnitNumber;
                            control_request->length = (uint32_t)control_request->setup->wLength;
                        }
                        else
                        {
                            error = kStatus_USB_InvalidRequest;
                        }

                        break;
                    case USB_DEVICE_MSC_BULK_ONLY_MASS_STORAGE_RESET:
                        /*Bulk-Only Mass Storage Reset (class-specific request)*/
                        if ((control_request->setup->wIndex == mscHandle->interfaceNumber) &&
                            (!control_request->setup->wValue) && (!control_request->setup->wLength) &&
                            ((control_request->setup->bmRequestType & USB_REQUSET_TYPE_DIR_MASK) ==
                             USB_REQUEST_TYPE_DIR_OUT))
                        {
                            error = USB_DeviceMscEndpointsDeinit(mscHandle);
                            error = USB_DeviceMscEndpointsInit(mscHandle);
                            mscHandle->performResetRecover = 0;
                            mscHandle->performResetDoneFlag = 1;
                        }
                        else
                        {
                            error = kStatus_USB_InvalidRequest;
                        }

                        break;
                    default:
                        break;
                }
            }
            break;
        default:
            break;
    }

    return error;
}

/*!
 * @brief Send data through a specified endpoint.
 *
 * The function is used to send data through a specified endpoint.
 * The function calls USB_DeviceSendRequest internally.
 *
 * @param handle The msc class handle got from usb_device_class_config_struct_t::classHandle.
 *
 * @return A USB error code or kStatus_USB_Success.
 *
 * @note The return value just means if the sending request is successful or not; the transfer done is notified by
 * USB_DeviceMscBulkIn.
 * Currently, only one transfer request can be supported for one specific endpoint.
 * If there is a specific requirement to support multiple transfer requests for one specific endpoint, the application
 * should implement a queue in the application level.
 * The subsequent transfer could begin only when the previous transfer is done (get notification through the endpoint
 * callback).
 */
usb_status_t USB_DeviceMscSend(usb_device_msc_struct_t *mscHandle)
{
    usb_status_t error = kStatus_USB_Success;
    usb_device_lba_app_struct_t lba;

    lba.offset = mscHandle->currentOffset;
    /*bulkInBufferSize is the application buffer size, USB_DEVICE_MSC_MAX_SEND_TRANSFER_LENGTH is the max transfer
       length by the hardware,
        lba.size is the data pending  for transfer ,select the minimum size to transfer ,the remaining will be transfer
       next time*/
    lba.size = (mscHandle->bulkInBufferSize > USB_DEVICE_MSC_MAX_SEND_TRANSFER_LENGTH) ?
                   USB_DEVICE_MSC_MAX_SEND_TRANSFER_LENGTH :
                   mscHandle->bulkInBufferSize;
    lba.size =
        (mscHandle->transferRemaining > lba.size) ? lba.size : mscHandle->transferRemaining; /* which one is smaller */

    lba.buffer = NULL;
    mscHandle->configurationStruct->classCallback((class_handle_t)mscHandle, kUSB_DeviceMscEventReadRequest, &lba);

    if (mscHandle->currentOffset < (mscHandle->totalLogicalBlockNumber * mscHandle->lengthOfEachLba))
    {
        error = USB_DeviceSendRequest(mscHandle->handle, mscHandle->bulkInEndpoint, lba.buffer, lba.size);
    }
    else
    {
        mscHandle->needInStallFlag = 0;
        mscHandle->inEndpointStallFlag = 1;
        mscHandle->dataInFlag = 0;
        mscHandle->stallStatus = (uint8_t)USB_DEVICE_MSC_STALL_IN_DATA;
        USB_DeviceStallEndpoint(mscHandle->handle, mscHandle->bulkInEndpoint);
    }
    return error;
}

/*!
 * @brief Receive data through a specified endpoint.
 *
 * The function is used to receive data through a specified endpoint.
 * The function calls USB_DeviceRecvRequest internally.
 *
 * @param handle The msc class handle got from usb_device_class_config_struct_t::classHandle.
 *
 * @return A USB error code or kStatus_USB_Success.
 *
 * @note The return value just means if the receiving request is successful or not; the transfer done is notified by
 * USB_DeviceMscBulkOut.
 * Currently, only one transfer request can be supported for one specific endpoint.
 * If there is a specific requirement to support multiple transfer requests for one specific endpoint, the application
 * should implement a queue in the application level.
 * The subsequent transfer could begin only when the previous transfer is done (get notification through the endpoint
 * callback).
 */
usb_status_t USB_DeviceMscRecv(usb_device_msc_struct_t *mscHandle)
{
    usb_status_t error = kStatus_USB_Success;
    usb_device_lba_app_struct_t lba;

    lba.offset = mscHandle->currentOffset;
    /*bulkOutBufferSize is the application buffer size, USB_DEVICE_MSC_MAX_RECV_TRANSFER_LENGTH is the max transfer
       length by the hardware,
       lba.size is the data pending  for transfer ,select the minimum size to transfer ,the remaining will be transfer
       next time*/
    lba.size = (mscHandle->bulkOutBufferSize > USB_DEVICE_MSC_MAX_RECV_TRANSFER_LENGTH) ?
                   USB_DEVICE_MSC_MAX_RECV_TRANSFER_LENGTH :
                   mscHandle->bulkOutBufferSize;
    lba.size =
        (mscHandle->transferRemaining > lba.size) ? lba.size : mscHandle->transferRemaining; /* whichever is smaller */

    lba.buffer = NULL;
    mscHandle->configurationStruct->classCallback((class_handle_t)mscHandle, kUSB_DeviceMscEventWriteRequest, &lba);

    if (mscHandle->currentOffset < (mscHandle->totalLogicalBlockNumber * mscHandle->lengthOfEachLba))
    {
        error = USB_DeviceRecvRequest(mscHandle->handle, mscHandle->bulkOutEndpoint, lba.buffer, lba.size);
    }
    else
    {
        mscHandle->needOutStallFlag = 0;
        mscHandle->outEndpointStallFlag = 1;
        mscHandle->dataOutFlag = 0;
        mscHandle->stallStatus = (uint8_t)USB_DEVICE_MSC_STALL_IN_DATA;
        USB_DeviceStallEndpoint(mscHandle->handle, mscHandle->bulkOutEndpoint);
    }
    return error;
}

/*!
 * @brief Recv Send data through a specified endpoint.
 *
 * The function is used when ufi process read/write command .
 * The function calls USB_DeviceMscRecv or  usb_device_send_recv as the direction internally.
 *
 * @param handle The msc class handle got from usb_device_class_config_struct_t::classHandle.
 * @param direction     Data direction: 0 = Data-Out from host to the device, 1 = Data-In from the device to the host.
 * @param buffer The memory address to hold the data need to be sent.
 * @return A USB error code or kStatus_USB_Success.
 *
 * @note The return value just means if the sending or reciving request is successful or not.
 */
usb_status_t USB_DeviceMscLbaTransfer(usb_device_msc_struct_t *mscHandle,
                                      uint8_t direction,
                                      usb_lba_transfer_information_struct_t *lba_info_ptr)
{
    usb_status_t error = kStatus_USB_Success;

    mscHandle->transferRemaining = lba_info_ptr->transferNumber * mscHandle->lengthOfEachLba;
    mscHandle->currentOffset = lba_info_ptr->startingLogicalBlockAddress * mscHandle->lengthOfEachLba;

    if (direction == USB_IN)
    {
        error = USB_DeviceMscSend(mscHandle);
    }
    else
    {
        error = USB_DeviceMscRecv(mscHandle);
    }
    return error;
}
#endif

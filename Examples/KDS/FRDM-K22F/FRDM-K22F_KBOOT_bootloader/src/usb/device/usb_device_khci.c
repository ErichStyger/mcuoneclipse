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

#include "fsl_device_registers.h"

#if ((defined(USB_DEVICE_CONFIG_KHCI)) && (USB_DEVICE_CONFIG_KHCI > 0U))

#include "usb_khci.h"
#include "usb_device_dci.h"

#include "usb_device_khci.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static usb_status_t USB_DeviceKhciEndpointTransfer(
    usb_device_khci_state_struct_t *khciState, uint8_t endpoint, uint8_t direction, uint8_t *buffer, uint32_t length);
static void USB_DeviceKhciPrimeNextSetup(usb_device_khci_state_struct_t *khciState);
static void USB_DeviceKhciSetDefaultState(usb_device_khci_state_struct_t *khciState);
static usb_status_t USB_DeviceKhciEndpointInit(usb_device_khci_state_struct_t *khciState,
                                               usb_device_endpoint_init_struct_t *epInit);
static usb_status_t USB_DeviceKhciEndpointDeinit(usb_device_khci_state_struct_t *khciState, uint8_t ep);
static usb_status_t USB_DeviceKhciEndpointStall(usb_device_khci_state_struct_t *khciState, uint8_t ep);
static usb_status_t USB_DeviceKhciEndpointUnstall(usb_device_khci_state_struct_t *khciState, uint8_t ep);
static void USB_DeviceKhciInterruptTokenDone(usb_device_khci_state_struct_t *khciState);
static void USB_DeviceKhciInterruptReset(usb_device_khci_state_struct_t *khciState);
#if ((defined(USB_DEVICE_CONFIG_LOW_POWER_MODE) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U)) || \
     (defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U)))
static void USB_DeviceKhciInterruptSleep(usb_device_khci_state_struct_t *khciState);
static void USB_DeviceKhciInterruptResume(usb_device_khci_state_struct_t *khciState);
#endif /* USB_DEVICE_CONFIG_LOW_POWER_MODE || USB_DEVICE_CONFIG_REMOTE_WAKEUP */
static void USB_DeviceKhciInterruptStall(usb_device_khci_state_struct_t *khciState);
#if defined(USB_DEVICE_CONFIG_KHCI_ERROR_HANDLING) && (USB_DEVICE_CONFIG_KHCI_ERROR_HANDLING > 0U)
static void USB_DeviceKhciInterruptError(usb_device_khci_state_struct_t *khciState);
#endif /* USB_DEVICE_CONFIG_KHCI_ERROR_HANDLING */

extern usb_status_t USB_DeviceNotificationTrigger(void *handle, void *msg);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Apply for BDT buffer, 512-byte alignment */
USB_RAM_ADDRESS_ALGINMENT_512 USB_BDT static uint8_t s_UsbDeviceKhciBdtBuffer[USB_DEVICE_CONFIG_KHCI][512U];

/* Apply for khci device state structure */
USB_GLOBAL static usb_device_khci_state_struct_t s_UsbDeviceKhciState[USB_DEVICE_CONFIG_KHCI];
/* Apply for KHCI DMA aligned buffer when marco USB_DEVICE_CONFIG_KHCI_DMA_ALIGN enabled */
USB_GLOBAL static uint32_t s_UsbDeviceKhciDmaAlignBuffer
    [USB_DEVICE_CONFIG_KHCI][((USB_DEVICE_CONFIG_KHCI_DMA_ALIGN_BUFFER_LENGTH - 1U) >> 2U) + 1U];

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Write the BDT to start a transfer.
 *
 * The function is used to start a transfer by writing the BDT.
 *
 * @param khciState       Pointer of the device KHCI state structure.
 * @param endpoint         Endpoint number.
 * @param direction        The direction of the endpoint, 0U - USB_OUT, 1U - USB_IN.
 * @param buffer           The memory address to save the received data, or the memory address to hold the data need to
 * be sent.
 * @param length           The length of the data.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceKhciEndpointTransfer(
    usb_device_khci_state_struct_t *khciState, uint8_t endpoint, uint8_t direction, uint8_t *buffer, uint32_t length)
{
    uint32_t index = ((uint32_t)endpoint << 1U) | (uint32_t)direction;
    USB_OSA_SR_ALLOC();

    /* Enter critical */
    USB_OSA_ENTER_CRITICAL();

    /* Flag the endpoint is busy. */
    khciState->endpointState[index].stateUnion.stateBitField.transferring = 1U;

    /* Add the data buffer address to the BDT. */
    USB_KHCI_BDT_SET_ADDRESS((uint32_t)khciState->bdt, endpoint, direction,
                             khciState->endpointState[index].stateUnion.stateBitField.bdtOdd, (uint32_t)buffer);

    /* Change the BDT control field to start the transfer. */
    USB_KHCI_BDT_SET_CONTROL(
        (uint32_t)khciState->bdt, endpoint, direction, khciState->endpointState[index].stateUnion.stateBitField.bdtOdd,
        USB_LONG_TO_LITTLE_ENDIAN(USB_KHCI_BDT_BC(length) | USB_KHCI_BDT_OWN | USB_KHCI_BDT_DTS |
                                  USB_KHCI_BDT_DATA01(khciState->endpointState[index].stateUnion.stateBitField.data0)));

    /* Exit critical */
    USB_OSA_EXIT_CRITICAL();

    /* Clear the token busy state */
    khciState->registerBase->CTL &= ~USB_CTL_TXSUSPENDTOKENBUSY_MASK;
    return kStatus_USB_Success;
}

/*!
 * @brief Prime a next setup transfer.
 *
 * The function is used to prime a buffer in control out pipe to wait for receiving the host's setup packet.
 *
 * @param khciState       Pointer of the device KHCI state structure.
 *
 */
static void USB_DeviceKhciPrimeNextSetup(usb_device_khci_state_struct_t *khciState)
{
/* Update the endpoint state */
/* Save the buffer address used to receive the setup packet. */
#if defined(FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED) && (FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED > 0U) \
&& defined(USB_DEVICE_CONFIG_KEEP_ALIVE_MODE) &&                                         \
    (USB_DEVICE_CONFIG_KEEP_ALIVE_MODE > 0U) && defined(FSL_FEATURE_USB_KHCI_USB_RAM) && \
    (FSL_FEATURE_USB_KHCI_USB_RAM > 0U)
    /* In case of lowpower mode enabled, it requires to put the setup packet buffer(16 bytes) into the USB RAM so
     * that the setup packet would wake up the USB.
     */
    khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_OUT].transferBuffer =
        (uint8_t *)(khciState->bdt + 0x200U - 0x10U) +
        khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_OUT].stateUnion.stateBitField.bdtOdd *
            USB_SETUP_PACKET_SIZE;
#else
    khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_OUT].transferBuffer =
        (uint8_t *)&khciState->setupPacketBuffer[0] +
        khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_OUT].stateUnion.stateBitField.bdtOdd *
            USB_SETUP_PACKET_SIZE;
#endif
    /* Clear the transferred length. */
    khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_OUT].transferDone = 0U;
    /* Save the data length expected to get from a host. */
    khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_OUT].transferLength = USB_SETUP_PACKET_SIZE;
    /* Save the data buffer DMA align flag. */
    khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_OUT].stateUnion.stateBitField.dmaAlign = 1U;
    /* Set the DATA0/1 to DATA0. */
    khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_OUT].stateUnion.stateBitField.data0 = 0U;

    USB_DeviceKhciEndpointTransfer(khciState, USB_CONTROL_ENDPOINT, USB_OUT,
                                   khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_OUT].transferBuffer,
                                   USB_SETUP_PACKET_SIZE);
}

/*!
 * @brief Set device controller state to default state.
 *
 * The function is used to set device controller state to default state.
 * The function will be called when USB_DeviceKhciInit called or the control type kUSB_DeviceControlGetEndpointStatus
 * received in USB_DeviceKhciControl.
 *
 * @param khciState       Pointer of the device KHCI state structure.
 *
 */
static void USB_DeviceKhciSetDefaultState(usb_device_khci_state_struct_t *khciState)
{
    uint8_t interruptFlag;

    /* Clear the error state register */
    khciState->registerBase->ERRSTAT = 0xFFU;

    /* Setting this bit to 1U resets all the BDT ODD ping/pong fields to 0U, which then specifies the EVEN BDT bank. */
    khciState->registerBase->CTL |= USB_CTL_ODDRST_MASK;

    /* Clear the device address */
    khciState->registerBase->ADDR = 0U;

    /* Clear the endpoint state and disable the endpoint */
    for (uint8_t count = 0U; count < USB_DEVICE_CONFIG_ENDPOINTS; count++)
    {
        USB_KHCI_BDT_SET_CONTROL((uint32_t)khciState->bdt, count, USB_OUT, 0U, 0U);
        USB_KHCI_BDT_SET_CONTROL((uint32_t)khciState->bdt, count, USB_OUT, 1U, 0U);
        USB_KHCI_BDT_SET_CONTROL((uint32_t)khciState->bdt, count, USB_IN, 0U, 0U);
        USB_KHCI_BDT_SET_CONTROL((uint32_t)khciState->bdt, count, USB_IN, 1U, 0U);

        khciState->endpointState[((uint32_t)count << 1U) | USB_OUT].stateUnion.state = 0U;
        khciState->endpointState[((uint32_t)count << 1U) | USB_IN].stateUnion.state = 0U;
        khciState->registerBase->ENDPOINT[count].ENDPT = 0x00U;
    }
    khciState->isDmaAlignBufferInusing = 0U;

    /* Clear the BDT odd reset flag */
    khciState->registerBase->CTL &= ~USB_CTL_ODDRST_MASK;

    /* Enable all error */
    khciState->registerBase->ERREN = 0xFFU;

    /* Enable reset, sof, token, stall interrupt */
    interruptFlag = kUSB_KhciInterruptReset
#if 0U
                    | kUSB_KhciInterruptSofToken
#endif
                    | kUSB_KhciInterruptTokenDone | kUSB_KhciInterruptStall;

#if ((defined(USB_DEVICE_CONFIG_LOW_POWER_MODE) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U)) || \
     (defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U)))
    /* Enable suspend interruprt */
    interruptFlag |= kUSB_KhciInterruptSleep;
#endif /* USB_DEVICE_CONFIG_LOW_POWER_MODE || USB_DEVICE_CONFIG_REMOTE_WAKEUP */

#if defined(USB_DEVICE_CONFIG_KHCI_ERROR_HANDLING) && (USB_DEVICE_CONFIG_KHCI_ERROR_HANDLING > 0U)
    /* Enable error interruprt */
    interruptFlag |= kUSB_KhciInterruptError;
#endif /* USB_DEVICE_CONFIG_KHCI_ERROR_HANDLING */
    /* Write the interrupt enable register */
    khciState->registerBase->INTEN = interruptFlag;

    /* Clear reset flag */
    khciState->isResetting = 0U;

    khciState->registerBase->CTL &= ~USB_CTL_TXSUSPENDTOKENBUSY_MASK;
}

/*!
 * @brief Initialize a specified endpoint.
 *
 * The function is used to initialize a specified endpoint.
 *
 * @param khciState       Pointer of the device KHCI state structure.
 * @param epInit          The endpoint initialization structure pointer.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceKhciEndpointInit(usb_device_khci_state_struct_t *khciState,
                                               usb_device_endpoint_init_struct_t *epInit)
{
    uint16_t maxPacketSize = epInit->maxPacketSize;
    uint8_t endpoint = (epInit->endpointAddress & USB_ENDPOINT_NUMBER_MASK);
    uint8_t direction = (epInit->endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
                        USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT;
    uint8_t index = ((uint8_t)((uint32_t)endpoint << 1U)) | (uint8_t)direction;

    /* Make the endpoint max packet size align with USB Specification 2.0. */
    if (USB_ENDPOINT_ISOCHRONOUS == epInit->transferType)
    {
        if (maxPacketSize > USB_DEVICE_MAX_FS_ISO_MAX_PACKET_SIZE)
        {
            maxPacketSize = USB_DEVICE_MAX_FS_ISO_MAX_PACKET_SIZE;
        }
    }
    else
    {
        if (maxPacketSize > USB_DEVICE_MAX_FS_NONE_ISO_MAX_PACKET_SIZE)
        {
            maxPacketSize = USB_DEVICE_MAX_FS_NONE_ISO_MAX_PACKET_SIZE;
        }
        /* Enable an endpoint to perform handshaking during a transaction to this endpoint. */
        khciState->registerBase->ENDPOINT[endpoint].ENDPT |= USB_ENDPT_EPHSHK_MASK;
    }
    /* Set the endpoint idle */
    khciState->endpointState[index].stateUnion.stateBitField.transferring = 0U;
    /* Save the max packet size of the endpoint */
    khciState->endpointState[index].stateUnion.stateBitField.maxPacketSize = maxPacketSize;
    /* Set the data toggle to DATA0 */
    khciState->endpointState[index].stateUnion.stateBitField.data0 = 0U;
    /* Clear the endpoint stalled state */
    khciState->endpointState[index].stateUnion.stateBitField.stalled = 0U;
    /* Enable the endpoint. */
    khciState->registerBase->ENDPOINT[endpoint].ENDPT |=
        (USB_IN == direction) ? USB_ENDPT_EPTXEN_MASK : USB_ENDPT_EPRXEN_MASK;

    /* Prime a transfer to receive next setup packet when the endpoint is control out endpoint. */
    if ((USB_CONTROL_ENDPOINT == endpoint) && (USB_OUT == direction))
    {
        USB_DeviceKhciPrimeNextSetup(khciState);
    }

    return kStatus_USB_Success;
}

/*!
 * @brief De-initialize a specified endpoint.
 *
 * The function is used to de-initialize a specified endpoint.
 * Current transfer of the endpoint will be canceled and the specified endpoint will be disabled.
 *
 * @param khciState       Pointer of the device KHCI state structure.
 * @param ep               The endpoint address, Bit7, 0U - USB_OUT, 1U - USB_IN.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceKhciEndpointDeinit(usb_device_khci_state_struct_t *khciState, uint8_t ep)
{
    uint8_t endpoint = (ep & USB_ENDPOINT_NUMBER_MASK);
    uint8_t direction =
        (ep & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >> USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT;
    uint8_t index = ((uint8_t)((uint32_t)endpoint << 1U)) | (uint8_t)direction;

    /* Cancel the transfer of the endpoint */
    USB_DeviceKhciCancel(khciState, ep);

    /* Disable the endpoint */
    khciState->registerBase->ENDPOINT[endpoint].ENDPT = 0x00U;
    /* Clear the max packet size */
    khciState->endpointState[index].stateUnion.stateBitField.maxPacketSize = 0U;

    return kStatus_USB_Success;
}

/*!
 * @brief Stall a specified endpoint.
 *
 * The function is used to stall a specified endpoint.
 * Current transfer of the endpoint will be canceled and the specified endpoint will be stalled.
 *
 * @param khciState       Pointer of the device KHCI state structure.
 * @param ep               The endpoint address, Bit7, 0U - USB_OUT, 1U - USB_IN.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceKhciEndpointStall(usb_device_khci_state_struct_t *khciState, uint8_t ep)
{
    uint8_t endpoint = ep & USB_ENDPOINT_NUMBER_MASK;
    uint8_t direction =
        (ep & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >> USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT;
    uint8_t index = ((uint8_t)((uint32_t)endpoint << 1U)) | (uint8_t)direction;

    /* Cancel the transfer of the endpoint */
    USB_DeviceKhciCancel(khciState, ep);

    /* Set endpoint stall flag. */
    khciState->endpointState[index].stateUnion.stateBitField.stalled = 1U;

    /* Set endpoint stall in BDT. And then if the host send a IN/OUT tanscation, the device will response a STALL state.
     */
    USB_KHCI_BDT_SET_CONTROL(
        (uint32_t)khciState->bdt, endpoint, direction, khciState->endpointState[index].stateUnion.stateBitField.bdtOdd,
        USB_LONG_TO_LITTLE_ENDIAN(
            (uint32_t)(USB_KHCI_BDT_BC(khciState->endpointState[index].stateUnion.stateBitField.maxPacketSize) |
                       USB_KHCI_BDT_DTS | USB_KHCI_BDT_STALL | USB_KHCI_BDT_OWN)));

    khciState->registerBase->CTL &= ~USB_CTL_TXSUSPENDTOKENBUSY_MASK;

    return kStatus_USB_Success;
}

/*!
 * @brief Un-stall a specified endpoint.
 *
 * The function is used to un-stall a specified endpoint.
 * Current transfer of the endpoint will be canceled and the specified endpoint will be un-stalled.
 *
 * @param khciState       Pointer of the device KHCI state structure.
 * @param ep               The endpoint address, Bit7, 0U - USB_OUT, 1U - USB_IN.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceKhciEndpointUnstall(usb_device_khci_state_struct_t *khciState, uint8_t ep)
{
    uint32_t control;
    uint8_t endpoint = ep & USB_ENDPOINT_NUMBER_MASK;
    uint8_t direction =
        (ep & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >> USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT;
    uint8_t index = ((uint8_t)((uint32_t)endpoint << 1U)) | (uint8_t)direction;

    /* Clear the endpoint stall state */
    khciState->endpointState[index].stateUnion.stateBitField.stalled = 0U;
    /* Reset the endpoint data toggle to DATA0 */
    khciState->endpointState[index].stateUnion.stateBitField.data0 = 0U;

    /* Clear stall state in BDT */
    for (uint8_t i = 0U; i < 2U; i++)
    {
        control = USB_KHCI_BDT_GET_CONTROL((uint32_t)khciState->bdt, endpoint, direction, i);
        if (control & USB_KHCI_BDT_STALL)
        {
            USB_KHCI_BDT_SET_CONTROL(
                (uint32_t)khciState->bdt, endpoint, direction, i,
                USB_LONG_TO_LITTLE_ENDIAN(
                    (uint32_t)(USB_KHCI_BDT_BC(khciState->endpointState[index].stateUnion.stateBitField.maxPacketSize) |
                               USB_KHCI_BDT_DTS | USB_KHCI_BDT_DATA01(0U))));
        }
    }

    /* Clear stall state in endpoint control register */
    khciState->registerBase->ENDPOINT[endpoint].ENDPT &= ~USB_ENDPT_EPSTALL_MASK;

    /* Prime a transfer to receive next setup packet when the endpoint is a control out endpoint. */
    if ((USB_CONTROL_ENDPOINT == endpoint) && (USB_OUT == direction))
    {
        USB_DeviceKhciPrimeNextSetup(khciState);
    }

    khciState->registerBase->CTL &= ~USB_CTL_TXSUSPENDTOKENBUSY_MASK;

    return kStatus_USB_Success;
}

/*!
 * @brief Handle the token done interrupt.
 *
 * The function is used to handle the token done interrupt.
 *
 * @param khciState       Pointer of the device KHCI state structure.
 *
 */
static void USB_DeviceKhciInterruptTokenDone(usb_device_khci_state_struct_t *khciState)
{
    uint32_t control;
    uint32_t length;
    uint32_t remainingLength;
    usb_device_callback_message_struct_t message;
    uint8_t endpoint;
    uint8_t direction;
    uint8_t bdtOdd;
    uint8_t isSetup;
    uint8_t index;
    uint8_t stateRegister = khciState->registerBase->STAT;

    /* Get the endpoint number to identify which one triggers the token done interrupt. */
    endpoint = (stateRegister & USB_STAT_ENDP_MASK) >> USB_STAT_ENDP_SHIFT;

    /* Get the direction of the endpoint number. */
    direction = (stateRegister & USB_STAT_TX_MASK) >> USB_STAT_TX_SHIFT;

    /* Get the finished BDT ODD. */
    bdtOdd = (stateRegister & USB_STAT_ODD_MASK) >> USB_STAT_ODD_SHIFT;

    /* Clear token done interrupt flag. */
    khciState->registerBase->ISTAT = kUSB_KhciInterruptTokenDone;

    /* Get the Control field of the BDT element according to the endpoint number, the direction and finished BDT ODD. */
    control = USB_KHCI_BDT_GET_CONTROL((uint32_t)khciState->bdt, endpoint, direction, bdtOdd);

    /* Get the transferred length. */
    length = ((USB_LONG_FROM_LITTLE_ENDIAN(control)) >> 16U) & 0x3FFU;

    /* Get the transferred length. */
    isSetup = (USB_KHCI_BDT_DEVICE_SETUP_TOKEN == ((uint8_t)(((USB_LONG_FROM_LITTLE_ENDIAN(control)) >> 2U) & 0x0FU))) ?
                  1U :
                  0U;

    index = ((uint8_t)((uint32_t)endpoint << 1U)) | (uint8_t)direction;

    if (0U == khciState->endpointState[index].stateUnion.stateBitField.transferring)
    {
        return;
    }

    if (isSetup)
    {
        khciState->setupBufferIndex = bdtOdd;
    }

    /* USB_IN, Send completed */
    if (direction == USB_IN)
    {
        /* The transferred length */
        khciState->endpointState[index].transferDone += length;

        /* Remaining length */
        remainingLength = khciState->endpointState[index].transferLength - khciState->endpointState[index].transferDone;

        /* Change the data toggle flag */
        khciState->endpointState[index].stateUnion.stateBitField.data0 ^= 1U;
        /* Change the BDT odd toggle flag */
        khciState->endpointState[index].stateUnion.stateBitField.bdtOdd ^= 1U;

        /* Whether the transfer is completed or not. */
        /*
         * The transfer is completed when one of the following conditions meet:
         * 1. The remaining length is zero.
         * 2. The length of current transcation is less than the max packet size of the current pipe.
         */
        if ((0U == remainingLength) ||
            (khciState->endpointState[index].stateUnion.stateBitField.maxPacketSize > length))
        {
            message.length = khciState->endpointState[index].transferDone;
            message.buffer = khciState->endpointState[index].transferBuffer;
            khciState->endpointState[index].stateUnion.stateBitField.transferring = 0U;

            /*
             * Whether need to send ZLT when the pipe is control in pipe and the transferred length of current
             * transaction equals to max packet size.
             */
            if ((length == khciState->endpointState[index].stateUnion.stateBitField.maxPacketSize) &&
                (USB_CONTROL_ENDPOINT == endpoint))
            {
                usb_setup_struct_t *setup_packet =
                    (usb_setup_struct_t
                         *)(&khciState->setupPacketBuffer[(USB_SETUP_PACKET_SIZE * khciState->setupBufferIndex)]);
                /*
                 * Send the ZLT and terminate the token done interrupt service when the tranferred length in data phase
                 * is less than the host request.
                 */
                if (USB_SHORT_FROM_LITTLE_ENDIAN(setup_packet->wLength) >
                    khciState->endpointState[index].transferLength)
                {
                    (void)USB_DeviceSendRequest(khciState->deviceHandle, endpoint, (uint8_t *)NULL, 0U);
                    return;
                }
            }
        }
        else
        {
            /* Send remaining data and terminate the token done interrupt service. */
            (void)USB_DeviceKhciSend(khciState, endpoint | (USB_IN << 0x07U),
                                     khciState->endpointState[index].transferBuffer, remainingLength);
            return;
        }
    }
    else
    {
        if ((USB_CONTROL_ENDPOINT == endpoint) && (0U == length))
        {
            message.length = 0U;
            message.buffer = (uint8_t *)NULL;
        }
        else
        {
            if (0U == khciState->endpointState[index].stateUnion.stateBitField.dmaAlign)
            {
                uint8_t *buffer = (uint8_t *)USB_LONG_FROM_LITTLE_ENDIAN(
                    USB_KHCI_BDT_GET_ADDRESS((uint32_t)khciState->bdt, endpoint, USB_OUT,
                                             khciState->endpointState[index].stateUnion.stateBitField.bdtOdd));
                uint8_t *transferBuffer =
                    khciState->endpointState[index].transferBuffer + khciState->endpointState[index].transferDone;
                if (buffer != transferBuffer)
                {
                    for (uint32_t i = 0U; i < length; i++)
                    {
                        transferBuffer[i] = buffer[i];
                    }
                }
                khciState->isDmaAlignBufferInusing = 0U;
            }
            /* The transferred length */
            khciState->endpointState[index].transferDone += length;
            /* Remaining length */
            remainingLength =
                khciState->endpointState[index].transferLength - khciState->endpointState[index].transferDone;

            if ((USB_CONTROL_ENDPOINT == endpoint) && isSetup)
            {
                USB_DeviceKhciCancel(khciState,
                                     (endpoint | (USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT)));
                khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_OUT].stateUnion.stateBitField.data0 = 1U;
                khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_IN].stateUnion.stateBitField.data0 = 1U;
            }
            else
            {
                khciState->endpointState[index].stateUnion.stateBitField.data0 ^= 1U;
            }
            khciState->endpointState[index].stateUnion.stateBitField.bdtOdd ^= 1U;
            if ((!khciState->endpointState[index].transferLength) || (!remainingLength) ||
                (khciState->endpointState[index].stateUnion.stateBitField.maxPacketSize > length))
            {
                message.length = khciState->endpointState[index].transferDone;
                message.buffer = khciState->endpointState[index].transferBuffer;
                khciState->endpointState[index].stateUnion.stateBitField.transferring = 0U;
            }
            else
            {
                /* Receive remaining data and terminate the token done interrupt service. */
                USB_DeviceKhciRecv(khciState, (endpoint) | (USB_OUT << 0x07U),
                                   khciState->endpointState[index].transferBuffer, remainingLength);
                return;
            }
        }
    }

    message.isSetup = isSetup;
    message.code = (endpoint) | (uint8_t)(((uint32_t)direction << 0x07U));

    /* Notify the up layer the KHCI status changed. */
    USB_DeviceNotificationTrigger(khciState->deviceHandle, &message);

    khciState->registerBase->CTL &= ~USB_CTL_TXSUSPENDTOKENBUSY_MASK;
}

/*!
 * @brief Handle the USB bus reset interrupt.
 *
 * The function is used to handle the USB bus reset interrupt.
 *
 * @param khciState       Pointer of the device KHCI state structure.
 *
 */
static void USB_DeviceKhciInterruptReset(usb_device_khci_state_struct_t *khciState)
{
    usb_device_callback_message_struct_t message;

    /* Set KHCI reset flag */
    khciState->isResetting = 1U;

    /* Clear the reset interrupt */
    khciState->registerBase->ISTAT = (kUSB_KhciInterruptReset);

    message.buffer = (uint8_t *)NULL;
    message.code = kUSB_DeviceNotifyBusReset;
    message.length = 0U;
    message.isSetup = 0U;
    /* Notify up layer the USB bus reset signal detected. */
    USB_DeviceNotificationTrigger(khciState->deviceHandle, &message);
}

/* The USB suspend and resume signals need to be detected and handled when the low power or remote wakeup function
 * enabled. */
#if ((defined(USB_DEVICE_CONFIG_LOW_POWER_MODE) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U)) || \
     (defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U)))

/*!
 * @brief Handle the suspend interrupt.
 *
 * The function is used to handle the suspend interrupt when the suspend signal detected.
 *
 * @param khciState       Pointer of the device KHCI state structure.
 *
 */
static void USB_DeviceKhciInterruptSleep(usb_device_khci_state_struct_t *khciState)
{
    usb_device_callback_message_struct_t message;

    /* Enable the resume interrupt */
    khciState->registerBase->INTEN |= kUSB_KhciInterruptResume;
    /* Disable the suspend interrupt */
    khciState->registerBase->INTEN &= ~kUSB_KhciInterruptSleep;

    /* Clear the suspend interrupt */
    khciState->registerBase->ISTAT = (kUSB_KhciInterruptSleep);
    /* Clear the resume interrupt */
    khciState->registerBase->ISTAT = (kUSB_KhciInterruptResume);

    message.buffer = (uint8_t *)NULL;
    message.code = kUSB_DeviceNotifySuspend;
    message.length = 0U;
    message.isSetup = 0U;

    /* Notify up layer the USB suspend signal detected. */
    USB_DeviceNotificationTrigger(khciState->deviceHandle, &message);
}

/*!
 * @brief Handle the resume interrupt.
 *
 * The function is used to handle the resume interrupt when the resume signal detected.
 *
 * @param khciState       Pointer of the device KHCI state structure.
 *
 */
static void USB_DeviceKhciInterruptResume(usb_device_khci_state_struct_t *khciState)
{
    usb_device_callback_message_struct_t message;

    /* Enable the suspend interrupt */
    khciState->registerBase->INTEN |= kUSB_KhciInterruptSleep;
    /* Disable the resume interrupt */
    khciState->registerBase->INTEN &= ~kUSB_KhciInterruptResume;

    /* Clear the resume interrupt */
    khciState->registerBase->ISTAT = (kUSB_KhciInterruptResume);
    /* Clear the suspend interrupt */
    khciState->registerBase->ISTAT = (kUSB_KhciInterruptSleep);

    message.buffer = (uint8_t *)NULL;
    message.code = kUSB_DeviceNotifyResume;
    message.length = 0U;
    message.isSetup = 0U;

    /* Notify up layer the USB resume signal detected. */
    USB_DeviceNotificationTrigger(khciState->deviceHandle, &message);
}
#endif /* USB_DEVICE_CONFIG_LOW_POWER_MODE || USB_DEVICE_CONFIG_REMOTE_WAKEUP */

#if (defined(USB_DEVICE_CONFIG_DETACH_ENABLE) && (USB_DEVICE_CONFIG_DETACH_ENABLE > 0U)) && \
    (defined(FSL_FEATURE_USB_KHCI_VBUS_DETECT_ENABLED) && (FSL_FEATURE_USB_KHCI_VBUS_DETECT_ENABLED > 0U))
/*!
 * @brief Handle the VBUS rising interrupt.
 *
 * The function is used to handle the VBUS rising interrupt when the VBUS rising signal detected.
 *
 * @param khciState       Pointer of the device KHCI state structure.
 *
 */
static void USB_DeviceKhciInterruptVbusRising(usb_device_khci_state_struct_t *khciState)
{
    usb_device_callback_message_struct_t message;

    /* Disable the VBUS rising interrupt */
    khciState->registerBase->MISCCTRL &= ~USB_MISCCTRL_VREDG_EN_MASK;
    /* Enable the VBUS rising interrupt */
    khciState->registerBase->MISCCTRL |= USB_MISCCTRL_VREDG_EN_MASK;

    message.buffer = (uint8_t *)NULL;
    message.code = kUSB_DeviceNotifyAttach;
    message.length = 0U;
    message.isSetup = 0U;

    /* Notify up layer the USB VBUS rising signal detected. */
    USB_DeviceNotificationTrigger(khciState->deviceHandle, &message);
}

/*!
 * @brief Handle the VBUS falling interrupt.
 *
 * The function is used to handle the VBUS falling interrupt when the VBUS falling signal detected.
 *
 * @param khciState       Pointer of the device KHCI state structure.
 *
 */
static void USB_DeviceKhciInterruptVbusFalling(usb_device_khci_state_struct_t *khciState)
{
    usb_device_callback_message_struct_t message;

    /* Disable the VBUS rising interrupt */
    khciState->registerBase->MISCCTRL &= ~USB_MISCCTRL_VFEDG_EN_MASK;
    /* Enable the VBUS rising interrupt */
    khciState->registerBase->MISCCTRL |= USB_MISCCTRL_VFEDG_EN_MASK;

    message.buffer = (uint8_t *)NULL;
    message.code = kUSB_DeviceNotifyDetach;
    message.length = 0U;
    message.isSetup = 0U;

    /* Notify up layer the USB VBUS falling signal detected. */
    USB_DeviceNotificationTrigger(khciState->deviceHandle, &message);
}
#endif /* USB_DEVICE_CONFIG_DETACH_ENABLE || FSL_FEATURE_USB_KHCI_VBUS_DETECT_ENABLED */

#if 0U
/*!
 * @brief Handle the sof interrupt.
 *
 * The function is used to handle the sof interrupt.
 *
 * @param khciState       Pointer of the device KHCI state structure.
 *
 */
void USB_DeviceKhciInterruptSof(usb_device_khci_state_struct_t *khciState)
{
    khciState->registerBase->ISTAT = (kUSB_KhciInterruptSofToken);

    khciState->registerBase->ISTAT = (kUSB_KhciInterruptResume);
}
#endif

/*!
 * @brief Handle endpoint stalled interrupt.
 *
 * The function is used to handle  endpoint stalled interrupt.
 *
 * @param khciState       Pointer of the device KHCI state structure.
 *
 */
static void USB_DeviceKhciInterruptStall(usb_device_khci_state_struct_t *khciState)
{
    /* Clear the endpoint stalled interrupt flag */
    khciState->registerBase->ISTAT = (kUSB_KhciInterruptStall);

    /* Un-stall the control in and out pipe when the control in or out pipe stalled. */
    if ((khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_IN].stateUnion.stateBitField.stalled) ||
        (khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_OUT].stateUnion.stateBitField.stalled))
    {
        USB_DeviceKhciEndpointUnstall(
            khciState, (USB_CONTROL_ENDPOINT | (USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT)));
        USB_DeviceKhciEndpointUnstall(
            khciState, (USB_CONTROL_ENDPOINT | (USB_OUT << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT)));
    }
}

#if defined(USB_DEVICE_CONFIG_KHCI_ERROR_HANDLING) && (USB_DEVICE_CONFIG_KHCI_ERROR_HANDLING > 0U)
static void USB_DeviceKhciInterruptError(usb_device_khci_state_struct_t *khciState)
{
    usb_device_callback_message_struct_t message;

    khciState->registerBase->ISTAT = (kUSB_KhciInterruptError);

    message.buffer = (uint8_t *)NULL;
    message.code = kUSB_DeviceNotifyError;
    message.length = 0U;
    message.isSetup = 0U;

    /* Notify up layer the USB error detected. */
    USB_DeviceNotificationTrigger(khciState->deviceHandle, &message);
}
#endif /* USB_DEVICE_CONFIG_KHCI_ERROR_HANDLING */

/*!
 * @brief Initialize the USB device KHCI instance.
 *
 * This function initizlizes the USB device KHCI module specified by the controllerId.
 *
 * @param controllerId The controller id of the USB IP. Please refer to enumeration type usb_controller_index_t.
 * @param handle        Pointer of the device handle, used to identify the device object is belonged to.
 * @param khciHandle   It is out parameter, is used to return pointer of the device KHCI handle to the caller.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceKhciInit(uint8_t controllerId,
                                usb_device_handle handle,
                                usb_device_controller_handle *khciHandle)
{
    usb_device_khci_state_struct_t *khciState;
    uint32_t khci_base[] = USB_BASE_ADDRS;

    if (((controllerId - kUSB_ControllerKhci0) >= (uint8_t)USB_DEVICE_CONFIG_KHCI) ||
        ((controllerId - kUSB_ControllerKhci0) >= (sizeof(khci_base) / sizeof(uint32_t))))
    {
        return kStatus_USB_ControllerNotFound;
    }
    khciState = &s_UsbDeviceKhciState[controllerId - kUSB_ControllerKhci0];

    khciState->controllerId = controllerId;

    khciState->registerBase = (USB_Type *)khci_base[controllerId - kUSB_ControllerKhci0];

    khciState->dmaAlignBuffer = (uint8_t *)&s_UsbDeviceKhciDmaAlignBuffer[controllerId - kUSB_ControllerKhci0][0];

    /* Clear all interrupt flags. */
    khciState->registerBase->ISTAT = 0xFFU;

    /* Disable the device functionality. */
    USB_DeviceKhciControl(khciState, kUSB_DeviceControlStop, NULL);

    khciState->bdt = s_UsbDeviceKhciBdtBuffer[controllerId - kUSB_ControllerKhci0];

    /* Set BDT buffer address */
    khciState->registerBase->BDTPAGE1 = (uint8_t)((((uint32_t)khciState->bdt) >> 8U) & 0xFFU);
    khciState->registerBase->BDTPAGE2 = (uint8_t)((((uint32_t)khciState->bdt) >> 16U) & 0xFFU);
    khciState->registerBase->BDTPAGE3 = (uint8_t)((((uint32_t)khciState->bdt) >> 24U) & 0xFFU);

#if (defined(USB_DEVICE_CONFIG_DETACH_ENABLE) && (USB_DEVICE_CONFIG_DETACH_ENABLE > 0U)) && \
    (defined(FSL_FEATURE_USB_KHCI_VBUS_DETECT_ENABLED) && (FSL_FEATURE_USB_KHCI_VBUS_DETECT_ENABLED > 0U))
    khciState->registerBase->MISCCTRL |= USB_MISCCTRL_VREDG_EN_MASK | USB_MISCCTRL_VFEDG_EN_MASK;
#endif

#if defined(FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED) && (FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED > 0U) \
&& defined(USB_DEVICE_CONFIG_KEEP_ALIVE_MODE) &&                                         \
    (USB_DEVICE_CONFIG_KEEP_ALIVE_MODE > 0U) && defined(FSL_FEATURE_USB_KHCI_USB_RAM) && \
    (FSL_FEATURE_USB_KHCI_USB_RAM > 0U)
    khciState->registerBase->CLK_RECOVER_CTRL |= USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_MASK;
    khciState->registerBase->KEEP_ALIVE_CTRL =
        USB_KEEP_ALIVE_CTRL_KEEP_ALIVE_EN_MASK | USB_KEEP_ALIVE_CTRL_OWN_OVERRD_EN_MASK |
        USB_KEEP_ALIVE_CTRL_STOP_ACK_DLY_EN_MASK | USB_KEEP_ALIVE_CTRL_AHB_DLY_EN_MASK |
        USB_KEEP_ALIVE_CTRL_WAKE_INT_EN_MASK;
    /* wake on out and setup transaction */
    khciState->registerBase->KEEP_ALIVE_WKCTRL = 0x1U;
    MCG->MC |= MCG_MC_HIRCLPEN_MASK;
    PMC->REGSC |= PMC_REGSC_BGEN_MASK | PMC_REGSC_VLPO_MASK;
#endif
    /* Set KHCI device state to default value. */
    USB_DeviceKhciSetDefaultState(khciState);

    *khciHandle = khciState;
    khciState->deviceHandle = (usb_device_struct_t *)handle;

    return kStatus_USB_Success;
}

/*!
 * @brief De-initialize the USB device KHCI instance.
 *
 * This function de-initizlizes the USB device KHCI module.
 *
 * @param khciHandle   Pointer of the device KHCI handle.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceKhciDeinit(usb_device_controller_handle khciHandle)
{
    usb_device_khci_state_struct_t *khciState = (usb_device_khci_state_struct_t *)khciHandle;

    if (!khciHandle)
    {
        return kStatus_USB_InvalidHandle;
    }
    /* Clear all interrupt flags. */
    khciState->registerBase->ISTAT = 0xFFU;
    /* Disable all interrupts. */
    khciState->registerBase->INTEN &= ~(0xFFU);
    /* Clear device address. */
    khciState->registerBase->ADDR = (0U);

    /* Clear USB_CTL register */
    khciState->registerBase->CTL = 0x00U;
    khciState->registerBase->USBCTRL |= USB_USBCTRL_PDE_MASK | USB_USBCTRL_SUSP_MASK;

    return kStatus_USB_Success;
}

/*!
 * @brief Send data through a specified endpoint.
 *
 * This function sends data through a specified endpoint.
 *
 * @param khciHandle      Pointer of the device KHCI handle.
 * @param endpointAddress Endpoint index.
 * @param buffer           The memory address to hold the data need to be sent.
 * @param length           The data length need to be sent.
 *
 * @return A USB error code or kStatus_USB_Success.
 *
 * @note The return value just means if the sending request is successful or not; the transfer done is notified by the
 * corresponding callback function.
 * Currently, only one transfer request can be supported for one specific endpoint.
 * If there is a specific requirement to support multiple transfer requests for one specific endpoint, the application
 * should implement a queue in the application level.
 * The subsequent transfer could begin only when the previous transfer is done (get notification through the endpoint
 * callback).
 */
usb_status_t USB_DeviceKhciSend(usb_device_controller_handle khciHandle,
                                uint8_t endpointAddress,
                                uint8_t *buffer,
                                uint32_t length)
{
    usb_device_khci_state_struct_t *khciState = (usb_device_khci_state_struct_t *)khciHandle;
    uint32_t index = ((endpointAddress & USB_ENDPOINT_NUMBER_MASK) << 1U) | USB_IN;
    usb_status_t error = kStatus_USB_Error;

    /* Save the tansfer information */
    if (0U == khciState->endpointState[index].stateUnion.stateBitField.transferring)
    {
        khciState->endpointState[index].transferDone = 0U;
        khciState->endpointState[index].transferBuffer = buffer;
        khciState->endpointState[index].transferLength = length;
        khciState->endpointState[index].stateUnion.stateBitField.dmaAlign = 1U;
    }

    /* Data length needs to less than max packet size in each call. */
    if (length > khciState->endpointState[index].stateUnion.stateBitField.maxPacketSize)
    {
        length = khciState->endpointState[index].stateUnion.stateBitField.maxPacketSize;
    }

    /* Send data when the device is not resetting. */
    if (0U == khciState->isResetting)
    {
        error = USB_DeviceKhciEndpointTransfer(khciState, endpointAddress & USB_ENDPOINT_NUMBER_MASK, USB_IN,
                                               (uint8_t *)((uint32_t)khciState->endpointState[index].transferBuffer +
                                                           (uint32_t)khciState->endpointState[index].transferDone),
                                               length);
    }

    /* Prime a transfer to receive next setup packet if the dat length is zero in a control in endpoint. */
    if ((0U == khciState->endpointState[index].transferDone) && (0U == length) &&
        (USB_CONTROL_ENDPOINT == (endpointAddress & USB_ENDPOINT_NUMBER_MASK)))
    {
        USB_DeviceKhciPrimeNextSetup(khciState);
    }
    return error;
}

/*!
 * @brief Receive data through a specified endpoint.
 *
 * This function Receives data through a specified endpoint.
 *
 * @param khciHandle      Pointer of the device KHCI handle.
 * @param endpointAddress Endpoint index.
 * @param buffer           The memory address to save the received data.
 * @param length           The data length want to be received.
 *
 * @return A USB error code or kStatus_USB_Success.
 *
 * @note The return value just means if the receiving request is successful or not; the transfer done is notified by the
 * corresponding callback function.
 * Currently, only one transfer request can be supported for one specific endpoint.
 * If there is a specific requirement to support multiple transfer requests for one specific endpoint, the application
 * should implement a queue in the application level.
 * The subsequent transfer could begin only when the previous transfer is done (get notification through the endpoint
 * callback).
 */
usb_status_t USB_DeviceKhciRecv(usb_device_controller_handle khciHandle,
                                uint8_t endpointAddress,
                                uint8_t *buffer,
                                uint32_t length)
{
    usb_device_khci_state_struct_t *khciState = (usb_device_khci_state_struct_t *)khciHandle;
    uint32_t index = ((endpointAddress & USB_ENDPOINT_NUMBER_MASK) << 1U) | USB_OUT;
    usb_status_t error = kStatus_USB_Error;

    /* Save the tansfer information */
    if (0U == khciState->endpointState[index].stateUnion.stateBitField.transferring)
    {
        khciState->endpointState[index].transferDone = 0U;
        khciState->endpointState[index].transferBuffer = buffer;
        khciState->endpointState[index].transferLength = length;
    }
    khciState->endpointState[index].stateUnion.stateBitField.dmaAlign = 1U;

    /* Data length needs to less than max packet size in each call. */
    if (length > khciState->endpointState[index].stateUnion.stateBitField.maxPacketSize)
    {
        length = khciState->endpointState[index].stateUnion.stateBitField.maxPacketSize;
    }

    buffer = (uint8_t *)((uint32_t)buffer + (uint32_t)khciState->endpointState[index].transferDone);

    if ((khciState->dmaAlignBuffer) && (0U == khciState->isDmaAlignBufferInusing) &&
        (USB_DEVICE_CONFIG_KHCI_DMA_ALIGN_BUFFER_LENGTH >= length) &&
        ((length & 0x03U) || (((uint32_t)buffer) & 0x03U)))
    {
        khciState->endpointState[index].stateUnion.stateBitField.dmaAlign = 0U;
        buffer = khciState->dmaAlignBuffer;
        khciState->isDmaAlignBufferInusing = 1U;
    }

    /* Receive data when the device is not resetting. */
    if (0U == khciState->isResetting)
    {
        error = USB_DeviceKhciEndpointTransfer(khciState, endpointAddress & USB_ENDPOINT_NUMBER_MASK, USB_OUT, buffer,
                                               length);
    }

    /* Prime a transfer to receive next setup packet if the dat length is zero in a control out endpoint. */
    if ((0U == length) && (USB_CONTROL_ENDPOINT == (endpointAddress & USB_ENDPOINT_NUMBER_MASK)))
    {
        khciState->endpointState[index].stateUnion.stateBitField.bdtOdd ^= 1U;
        khciState->endpointState[index].stateUnion.stateBitField.transferring = 0U;
        USB_DeviceKhciPrimeNextSetup(khciState);
    }
    return error;
}

/*!
 * @brief Cancel the pending transfer in a specified endpoint.
 *
 * The function is used to cancel the pending transfer in a specified endpoint.
 *
 * @param khciHandle      Pointer of the device KHCI handle.
 * @param ep               Endpoint address, bit7 is the direction of endpoint, 1U - IN, abd 0U - OUT.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceKhciCancel(usb_device_controller_handle khciHandle, uint8_t ep)
{
    usb_device_khci_state_struct_t *khciState = (usb_device_khci_state_struct_t *)khciHandle;
    usb_device_callback_message_struct_t message;
    uint8_t index = ((ep & USB_ENDPOINT_NUMBER_MASK) << 1U) | ((ep & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
                                                               USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT);

    /* Cancel the transfer and notify the up layer when the endpoint is busy. */
    if (khciState->endpointState[index].stateUnion.stateBitField.transferring)
    {
        message.length = USB_UNINITIALIZED_VAL_32;
        message.buffer = khciState->endpointState[index].transferBuffer;
        message.code = ep;
        message.isSetup = 0U;
        khciState->endpointState[index].stateUnion.stateBitField.transferring = 0U;
        USB_DeviceNotificationTrigger(khciState->deviceHandle, &message);
    }
    return kStatus_USB_Success;
}

/*!
 * @brief Control the status of the selected item.
 *
 * The function is used to control the status of the selected item.
 *
 * @param khciHandle      Pointer of the device KHCI handle.
 * @param type             The selected item. Please refer to enumeration type usb_device_control_type_t.
 * @param param            The param type is determined by the selected item.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceKhciControl(usb_device_controller_handle khciHandle, usb_device_control_type_t type, void *param)
{
    usb_device_khci_state_struct_t *khciState = (usb_device_khci_state_struct_t *)khciHandle;
    usb_status_t error = kStatus_USB_Error;
    uint16_t *temp16;
    uint8_t *temp8;
#if defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U)
    USB_OSA_SR_ALLOC();
#endif /* USB_DEVICE_CONFIG_REMOTE_WAKEUP */

    if (!khciHandle)
    {
        return kStatus_USB_InvalidHandle;
    }

    switch (type)
    {
        case kUSB_DeviceControlRun:
            khciState->registerBase->USBCTRL = 0U;
#if defined(FSL_FEATURE_USB_KHCI_OTG_ENABLED) && (FSL_FEATURE_USB_KHCI_OTG_ENABLED > 0U)
            if (khciState->registerBase->OTGCTL & USB_OTGCTL_OTGEN_MASK)
            {
                khciState->registerBase->OTGCTL |= USB_OTGCTL_DPHIGH_MASK;
            }
#endif /* FSL_FEATURE_USB_KHCI_OTG_ENABLED */
            khciState->registerBase->CONTROL |= USB_CONTROL_DPPULLUPNONOTG_MASK;
            khciState->registerBase->CTL |= USB_CTL_USBENSOFEN_MASK;

            error = kStatus_USB_Success;
            break;
        case kUSB_DeviceControlStop:
#if defined(FSL_FEATURE_USB_KHCI_OTG_ENABLED) && (FSL_FEATURE_USB_KHCI_OTG_ENABLED > 0U)
            if (khciState->registerBase->OTGCTL & USB_OTGCTL_OTGEN_MASK)
            {
                khciState->registerBase->OTGCTL &= ~USB_OTGCTL_DPHIGH_MASK;
            }
#endif /* FSL_FEATURE_USB_KHCI_OTG_ENABLED */
            khciState->registerBase->CONTROL &= ~USB_CONTROL_DPPULLUPNONOTG_MASK;
            error = kStatus_USB_Success;
            break;
        case kUSB_DeviceControlEndpointInit:
            if (param)
            {
                error = USB_DeviceKhciEndpointInit(khciState, (usb_device_endpoint_init_struct_t *)param);
            }
            break;
        case kUSB_DeviceControlEndpointDeinit:
            if (param)
            {
                temp8 = (uint8_t *)param;
                error = USB_DeviceKhciEndpointDeinit(khciState, *temp8);
            }
            break;
        case kUSB_DeviceControlEndpointStall:
            if (param)
            {
                temp8 = (uint8_t *)param;
                error = USB_DeviceKhciEndpointStall(khciState, *temp8);
            }
            break;
        case kUSB_DeviceControlEndpointUnstall:
            if (param)
            {
                temp8 = (uint8_t *)param;
                error = USB_DeviceKhciEndpointUnstall(khciState, *temp8);
            }
            break;
        case kUSB_DeviceControlGetDeviceStatus:
            if (param)
            {
                temp16 = (uint16_t *)param;
                *temp16 =
                    (USB_DEVICE_CONFIG_SELF_POWER << (USB_REQUSET_STANDARD_GET_STATUS_DEVICE_SELF_POWERED_SHIFT)) |
                    (USB_DEVICE_CONFIG_REMOTE_WAKEUP << (USB_REQUSET_STANDARD_GET_STATUS_DEVICE_REMOTE_WARKUP_SHIFT));
                error = kStatus_USB_Success;
            }
            break;
        case kUSB_DeviceControlGetEndpointStatus:
            if (param)
            {
                usb_device_endpoint_status_struct_t *endpointStatus = (usb_device_endpoint_status_struct_t *)param;

                if (((endpointStatus->endpointAddress) & USB_ENDPOINT_NUMBER_MASK) < USB_DEVICE_CONFIG_ENDPOINTS)
                {
                    endpointStatus->endpointStatus =
                        (uint16_t)(
                            khciState
                                ->endpointState[(((endpointStatus->endpointAddress) & USB_ENDPOINT_NUMBER_MASK) << 1U) |
                                                (((endpointStatus->endpointAddress) &
                                                  USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
                                                 USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT)]
                                .stateUnion.stateBitField.stalled == 1U) ?
                            kUSB_DeviceEndpointStateStalled :
                            kUSB_DeviceEndpointStateIdle;
                    error = kStatus_USB_Success;
                }
            }
            break;
        case kUSB_DeviceControlSetDeviceAddress:
            if (param)
            {
                temp8 = (uint8_t *)param;
                khciState->registerBase->ADDR = (*temp8);
                error = kStatus_USB_Success;
            }
            break;
        case kUSB_DeviceControlGetSynchFrame:
            break;
        case kUSB_DeviceControlResume:
#if defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U)
            USB_OSA_ENTER_CRITICAL();
            khciState->registerBase->CTL |= USB_CTL_RESUME_MASK;
            for (uint32_t i = 500U; i > 0U; i--)
            {
                __ASM("nop");
            }
            khciState->registerBase->CTL &= ~USB_CTL_RESUME_MASK;
            USB_OSA_EXIT_CRITICAL();
            error = kStatus_USB_Success;
#endif /* USB_DEVICE_CONFIG_REMOTE_WAKEUP */
            break;
        case kUSB_DeviceControlSetDefaultStatus:
            for (uint8_t count = 0U; count < USB_DEVICE_CONFIG_ENDPOINTS; count++)
            {
                USB_DeviceKhciEndpointDeinit(khciState, (count | (USB_IN << 0x07U)));
                USB_DeviceKhciEndpointDeinit(khciState, (count | (USB_OUT << 0x07U)));
            }
            USB_DeviceKhciSetDefaultState(khciState);
            error = kStatus_USB_Success;
            break;
        case kUSB_DeviceControlGetSpeed:
            if (param)
            {
                temp8 = (uint8_t *)param;
                *temp8 = USB_SPEED_FULL;
                error = kStatus_USB_Success;
            }
            break;
        case kUSB_DeviceControlGetOtgStatus:
            break;
        case kUSB_DeviceControlSetOtgStatus:
            break;
        case kUSB_DeviceControlSetTestMode:
            break;
        default:
            break;
    }

    return error;
}

/*!
 * @brief Handle the KHCI device interrupt.
 *
 * The function is used to handle the KHCI device interrupt.
 *
 * @param deviceHandle    The device handle got from USB_DeviceInit.
 *
 */
void USB_DeviceKhciIsrFunction(void *deviceHandle)
{
    usb_device_struct_t *handle = (usb_device_struct_t *)deviceHandle;
    usb_device_khci_state_struct_t *khciState;
    uint8_t status;

    if (NULL == deviceHandle)
    {
        return;
    }

    khciState = (usb_device_khci_state_struct_t *)(handle->controllerHandle);

    status = khciState->registerBase->ISTAT;
#if defined(FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED) && (FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED > 0U) \
&& defined(USB_DEVICE_CONFIG_KEEP_ALIVE_MODE) &&                                         \
    (USB_DEVICE_CONFIG_KEEP_ALIVE_MODE > 0U) && defined(FSL_FEATURE_USB_KHCI_USB_RAM) && \
    (FSL_FEATURE_USB_KHCI_USB_RAM > 0U)
    /* Clear EEP_ALIVE_CTRL_WAKE_INT interrupt state */
    if (khciState->registerBase->KEEP_ALIVE_CTRL & USB_KEEP_ALIVE_CTRL_WAKE_INT_STS_MASK)
    {
        khciState->registerBase->KEEP_ALIVE_CTRL |= USB_KEEP_ALIVE_CTRL_WAKE_INT_STS_MASK;
    }
    /* Clear SOFTOK interrupt state */
    if (khciState->registerBase->ISTAT & USB_ISTAT_SOFTOK_MASK)
    {
        khciState->registerBase->ISTAT = USB_ISTAT_SOFTOK_MASK;
    }
#endif
#if defined(USB_DEVICE_CONFIG_KHCI_ERROR_HANDLING) && (USB_DEVICE_CONFIG_KHCI_ERROR_HANDLING > 0U)
    /* Error interrupt */
    if (status & kUSB_KhciInterruptError)
    {
        USB_DeviceKhciInterruptError(khciState);
    }
#endif /* USB_DEVICE_CONFIG_KHCI_ERROR_HANDLING */
    /* Token done interrupt */
    if (status & kUSB_KhciInterruptTokenDone)
    {
        USB_DeviceKhciInterruptTokenDone(khciState);
    }

    /* Reset interrupt */
    if (status & kUSB_KhciInterruptReset)
    {
        USB_DeviceKhciInterruptReset(khciState);
    }

#if ((defined(USB_DEVICE_CONFIG_LOW_POWER_MODE) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U)) || \
     (defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U)))
    /* Suspend interrupt */
    if (status & kUSB_KhciInterruptSleep)
    {
        USB_DeviceKhciInterruptSleep(khciState);
    }

    /* Resume interrupt */
    if (status & kUSB_KhciInterruptResume)
    {
        USB_DeviceKhciInterruptResume(khciState);
    }
#endif /* USB_DEVICE_CONFIG_LOW_POWER_MODE || USB_DEVICE_CONFIG_REMOTE_WAKEUP */

    /* Endpoint stalled interrupt */
    if (status & kUSB_KhciInterruptStall)
    {
        USB_DeviceKhciInterruptStall(khciState);
    }

#if (defined(USB_DEVICE_CONFIG_DETACH_ENABLE) && (USB_DEVICE_CONFIG_DETACH_ENABLE > 0U)) && \
    (defined(FSL_FEATURE_USB_KHCI_VBUS_DETECT_ENABLED) && (FSL_FEATURE_USB_KHCI_VBUS_DETECT_ENABLED > 0U))
    if (khciState->registerBase->USBTRC0 & USB_USBTRC0_VREDG_DET_MASK)
    {
        USB_DeviceKhciInterruptVbusRising(khciState);
    }

    if (khciState->registerBase->USBTRC0 & USB_USBTRC0_VFEDG_DET_MASK)
    {
        USB_DeviceKhciInterruptVbusFalling(khciState);
    }
#endif /* USB_DEVICE_CONFIG_DETACH_ENABLE && FSL_FEATURE_USB_KHCI_VBUS_DETECT_ENABLED */

#if 0U
    /* Sof token interrupt */
    if (status & kUSB_KhciInterruptSofToken)
    {
        USB_DeviceKhciInterruptSof(khciState);
    }
#endif

#if ((defined FSL_FEATURE_USB_KHCI_IRC48M_MODULE_CLOCK_ENABLED) && \
     (FSL_FEATURE_USB_KHCI_IRC48M_MODULE_CLOCK_ENABLED > 0U))
    status = khciState->registerBase->CLK_RECOVER_INT_STATUS;
    if (status)
    {
        /* USB RECOVER interrupt is happenned */
        if (USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_MASK & status)
        {
            /* Indicates that the USB clock recovery algorithm has detected that the frequency trim adjustment needed
             * for the IRC48M output clock is outside the available TRIM_FINE adjustment range for the IRC48M
             * module.
             */
        }
        khciState->registerBase->CLK_RECOVER_INT_STATUS = status;
    }
#endif
}

#endif /* USB_DEVICE_CONFIG_KHCI */

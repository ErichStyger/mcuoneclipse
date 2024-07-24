/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "usb_device_config.h"
#include "usb.h"

#include "usb_device.h"

#include "fsl_device_registers.h"

#if ((defined(USB_DEVICE_CONFIG_KHCI)) && (USB_DEVICE_CONFIG_KHCI > 0U))

#include "usb_device_dci.h"

#include "usb_device_khci.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if defined(USB_STACK_USE_DEDICATED_RAM) && (USB_STACK_USE_DEDICATED_RAM > 0U)

/* USB_STACK_USE_DEDICATED_RAM */
#if defined(FSL_FEATURE_USB_KHCI_USB_RAM) && (FSL_FEATURE_USB_KHCI_USB_RAM > 0U)

#if (USB_STACK_USE_DEDICATED_RAM == USB_STACK_DEDICATED_RAM_TYPE_BDT_GLOBAL)
#if (FSL_FEATURE_USB_KHCI_USB_RAM > 512U)
#else
#error The dedicated RAM length is not more than 512 Bytes, the SOC does not support this case.
#endif
#endif /* USB_STACK_USE_DEDICATED_RAM */

#else
#error The SOC does not suppoort dedicated RAM case.
#endif /* USB_STACK_USE_DEDICATED_RAM */

#endif

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
#if (defined(USB_DEVICE_CONFIG_LOW_POWER_MODE) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U))
static void USB_DeviceKhciInterruptSleep(usb_device_khci_state_struct_t *khciState);
static void USB_DeviceKhciInterruptResume(usb_device_khci_state_struct_t *khciState);
#endif /* USB_DEVICE_CONFIG_LOW_POWER_MODE */
static void USB_DeviceKhciInterruptStall(usb_device_khci_state_struct_t *khciState);
#if defined(USB_DEVICE_CONFIG_ERROR_HANDLING) && (USB_DEVICE_CONFIG_ERROR_HANDLING > 0U)
static void USB_DeviceKhciInterruptError(usb_device_khci_state_struct_t *khciState);
#endif /* USB_DEVICE_CONFIG_ERROR_HANDLING */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Apply for BDT buffer, 512-byte alignment */
USB_BDT USB_RAM_ADDRESS_ALIGNMENT(512) static uint32_t
    s_UsbDeviceKhciBdtBuffer[USB_DEVICE_CONFIG_KHCI][512U / sizeof(uint32_t)];

/* Apply for khci device state structure */
USB_GLOBAL USB_RAM_ADDRESS_ALIGNMENT(USB_DATA_ALIGN_SIZE) static usb_device_khci_state_struct_t
    s_UsbDeviceKhciState[USB_DEVICE_CONFIG_KHCI];

#if (defined(USB_DEVICE_CHARGER_DETECT_ENABLE) && (USB_DEVICE_CHARGER_DETECT_ENABLE > 0U)) && \
    (defined(FSL_FEATURE_SOC_USBDCD_COUNT) && (FSL_FEATURE_SOC_USBDCD_COUNT > 0U))
/* Apply for device dcd state structure */
USB_GLOBAL USB_RAM_ADDRESS_ALIGNMENT(USB_DATA_ALIGN_SIZE) static usb_device_dcd_state_struct_t
    s_UsbDeviceDcdState[USB_DEVICE_CONFIG_KHCI];
#endif

/* Apply for KHCI DMA aligned buffer when macro USB_DEVICE_CONFIG_KHCI_DMA_ALIGN enabled */
USB_GLOBAL USB_RAM_ADDRESS_ALIGNMENT(USB_DATA_ALIGN_SIZE) static uint32_t
    s_UsbDeviceKhciDmaAlignBuffer[USB_DEVICE_CONFIG_KHCI]
                                 [((USB_DEVICE_CONFIG_KHCI_DMA_ALIGN_BUFFER_LENGTH - 1U) >> 2U) + 1U];

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
    OSA_SR_ALLOC();

    /* Enter critical */
    OSA_ENTER_CRITICAL();

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
    OSA_EXIT_CRITICAL();

    /* Clear the token busy state */
    khciState->registerBase->CTL &= (uint8_t)(~USB_CTL_TXSUSPENDTOKENBUSY_MASK);
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
#if defined(FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED) && (FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED > 0U) && \
    defined(USB_DEVICE_CONFIG_KEEP_ALIVE_MODE) && (USB_DEVICE_CONFIG_KEEP_ALIVE_MODE > 0U) &&             \
    defined(FSL_FEATURE_USB_KHCI_USB_RAM) && (FSL_FEATURE_USB_KHCI_USB_RAM > 0U)
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
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
    if (kStatus_USB_Success !=
        USB_DeviceKhciEndpointTransfer(khciState, USB_CONTROL_ENDPOINT, USB_OUT,
                                       khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_OUT].transferBuffer,
                                       USB_SETUP_PACKET_SIZE))
    {
#if (defined(DEVICE_ECHO) && (DEVICE_ECHO > 0U))
        usb_echo("start transfer error\r\n");
#endif
    }
#else
    (void)USB_DeviceKhciEndpointTransfer(
        khciState, USB_CONTROL_ENDPOINT, USB_OUT,
        khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_OUT].transferBuffer, USB_SETUP_PACKET_SIZE);
#endif
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
    uint8_t count;

    /* Clear the error state register */
    khciState->registerBase->ERRSTAT = 0xFFU;

    /* Setting this bit to 1U resets all the BDT ODD ping/pong fields to 0U, which then specifies the EVEN BDT bank. */
    khciState->registerBase->CTL |= USB_CTL_ODDRST_MASK;

    /* Clear the device address */
    khciState->registerBase->ADDR = 0U;

    /* Clear the endpoint state and disable the endpoint */
    for (count = 0U; count < USB_DEVICE_CONFIG_ENDPOINTS; count++)
    {
        USB_KHCI_BDT_SET_CONTROL((uint32_t)khciState->bdt, count, USB_OUT, 0U, 0U);
        USB_KHCI_BDT_SET_CONTROL((uint32_t)khciState->bdt, count, USB_OUT, 1U, 0U);
        USB_KHCI_BDT_SET_CONTROL((uint32_t)khciState->bdt, count, USB_IN, 0U, 0U);
        USB_KHCI_BDT_SET_CONTROL((uint32_t)khciState->bdt, count, USB_IN, 1U, 0U);

        khciState->endpointState[((uint32_t)count << 1U) | USB_OUT].stateUnion.state = 0U;
        khciState->endpointState[((uint32_t)count << 1U) | USB_IN].stateUnion.state  = 0U;
        khciState->registerBase->ENDPOINT[count].ENDPT                               = 0x00U;
    }
    khciState->isDmaAlignBufferInusing = 0U;

    /* Clear the BDT odd reset flag */
    khciState->registerBase->CTL &= (uint8_t)(~USB_CTL_ODDRST_MASK);

    /* Enable all error */
    khciState->registerBase->ERREN = 0xFFU;

    /* Enable reset, sof, token, stall interrupt */
    interruptFlag = USB_INTEN_USBRSTEN_MASK
#if 0U
                    | USB_INTEN_SOFTOKEN_MASK
#endif
                    | USB_INTEN_TOKDNEEN_MASK | USB_INTEN_STALLEN_MASK;

#if (defined(USB_DEVICE_CONFIG_LOW_POWER_MODE) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U))
    /* Enable suspend interruprt */
    interruptFlag |= USB_INTEN_SLEEPEN_MASK;
#endif /* USB_DEVICE_CONFIG_LOW_POWER_MODE */

#if defined(USB_DEVICE_CONFIG_ERROR_HANDLING) && (USB_DEVICE_CONFIG_ERROR_HANDLING > 0U)
    /* Enable error interruprt */
    interruptFlag |= USB_INTEN_ERROREN_MASK;
#endif /* USB_DEVICE_CONFIG_ERROR_HANDLING */
    /* Write the interrupt enable register */
    khciState->registerBase->INTEN = interruptFlag;

    /* Clear reset flag */
    khciState->isResetting = 0U;

    khciState->registerBase->CTL &= (uint8_t)(~USB_CTL_TXSUSPENDTOKENBUSY_MASK);
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
    uint8_t endpoint       = (epInit->endpointAddress & USB_ENDPOINT_NUMBER_MASK);
    uint8_t direction      = (epInit->endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
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
    /* Set the ZLT field */
    khciState->endpointState[index].stateUnion.stateBitField.zlt = epInit->zlt;
    /* Enable the endpoint. */
    khciState->registerBase->ENDPOINT[endpoint].ENDPT |=
        (USB_IN == direction) ? USB_ENDPT_EPTXEN_MASK : USB_ENDPT_EPRXEN_MASK;
#if defined(FSL_FEATURE_USB_KHCI_HAS_STALL_LOW) && (FSL_FEATURE_USB_KHCI_HAS_STALL_LOW > 0U)
    /*control endpoint bidirection stall default state should be enable, iso doesn't support stall*/
    if ((USB_ENDPOINT_BULK == epInit->transferType) || (USB_ENDPOINT_INTERRUPT == epInit->transferType))
    {
        if (USB_IN == direction)
        {
            if (endpoint < 8U)
            {
                khciState->registerBase->STALL_IL_DIS |= (uint8_t)(1UL << endpoint);
            }
#if defined(FSL_FEATURE_USB_KHCI_HAS_STALL_HIGH) && (FSL_FEATURE_USB_KHCI_HAS_STALL_HIGH > 0U)
            else if ((endpoint >= 8U) && (endpoint < 16U))
            {
                khciState->registerBase->STALL_IH_DIS |= (uint8_t)(1UL << (endpoint - 8U));
            }
#endif
            else
            {
                /*no action*/
            }
        }
        else
        {
            if (endpoint < 8U)
            {
                khciState->registerBase->STALL_OL_DIS |= (uint8_t)(1UL << endpoint);
            }
#if defined(FSL_FEATURE_USB_KHCI_HAS_STALL_HIGH) && (FSL_FEATURE_USB_KHCI_HAS_STALL_HIGH > 0U)
            else if ((endpoint >= 8U) && (endpoint < 16U))
            {
                khciState->registerBase->STALL_OH_DIS |= (uint8_t)(1UL << (endpoint - 8U));
            }
#endif
            else
            {
                /*no action*/
            }
        }
    }
    else if ((USB_ENDPOINT_CONTROL == epInit->transferType))
    {
        khciState->registerBase->STALL_IL_DIS &= (uint8_t)(~(1UL << endpoint));
        khciState->registerBase->STALL_OL_DIS &= (uint8_t)(~(1UL << endpoint));
    }
    else
    {
        /*no action*/
    }
#endif

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
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
    if (kStatus_USB_Success != USB_DeviceKhciCancel(khciState, ep))
    {
        return kStatus_USB_Error;
    }
#else
    (void)USB_DeviceKhciCancel(khciState, ep);
#endif

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
    OSA_SR_ALLOC();

    if (USB_CONTROL_ENDPOINT == endpoint)
    {
        /* Cancel the transfer of the endpoint */
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
        if ((kStatus_USB_Success != USB_DeviceKhciCancel(khciState, 0x00)) ||
            (kStatus_USB_Success != USB_DeviceKhciCancel(khciState, 0x80)))
        {
            return kStatus_USB_Error;
        }
#else
        (void)USB_DeviceKhciCancel(khciState, 0x00);
        (void)USB_DeviceKhciCancel(khciState, 0x80);
#endif
        /* Set endpoint stall flag. */
        khciState->endpointState[0].stateUnion.stateBitField.stalled = 1U;
        khciState->endpointState[1].stateUnion.stateBitField.stalled = 1U;
        /* Enter critical */
        OSA_ENTER_CRITICAL();
        /* Set endpoint stall in BDT. And then if the host send a IN/OUT tansaction, the device will response a STALL
         * state. */
        USB_KHCI_BDT_SET_CONTROL(
            (uint32_t)khciState->bdt, endpoint, 0, khciState->endpointState[0].stateUnion.stateBitField.bdtOdd,
            USB_LONG_TO_LITTLE_ENDIAN(
                (uint32_t)(USB_KHCI_BDT_BC(khciState->endpointState[0].stateUnion.stateBitField.maxPacketSize) |
                           USB_KHCI_BDT_DTS | USB_KHCI_BDT_STALL | USB_KHCI_BDT_OWN)));
        /* Set endpoint stall in BDT. And then if the host send a IN/OUT tansaction, the device will response a STALL
         * state. */
        USB_KHCI_BDT_SET_CONTROL(
            (uint32_t)khciState->bdt, endpoint, 1, khciState->endpointState[1].stateUnion.stateBitField.bdtOdd,
            USB_LONG_TO_LITTLE_ENDIAN(
                (uint32_t)(USB_KHCI_BDT_BC(khciState->endpointState[1].stateUnion.stateBitField.maxPacketSize) |
                           USB_KHCI_BDT_DTS | USB_KHCI_BDT_STALL | USB_KHCI_BDT_OWN)));
        /* Exit critical */
        OSA_EXIT_CRITICAL();
    }
    else
    {
        /* Cancel the transfer of the endpoint */
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
        if (kStatus_USB_Success != USB_DeviceKhciCancel(khciState, ep))
        {
            return kStatus_USB_Error;
        }
#else
        (void)USB_DeviceKhciCancel(khciState, ep);
#endif

        /* Set endpoint stall flag. */
        khciState->endpointState[index].stateUnion.stateBitField.stalled = 1U;
#if defined(FSL_FEATURE_USB_KHCI_HAS_STALL_LOW) && (FSL_FEATURE_USB_KHCI_HAS_STALL_LOW > 0U)
        if (USB_CONTROL_ENDPOINT != endpoint)
        {
            if (USB_IN == direction)
            {
                /*endpoint is between 1 and 15*/
                if (endpoint < 8U)
                {
                    khciState->registerBase->STALL_IL_DIS &= (uint8_t)(~(1UL << endpoint));
                }
#if defined(FSL_FEATURE_USB_KHCI_HAS_STALL_HIGH) && (FSL_FEATURE_USB_KHCI_HAS_STALL_HIGH > 0U)
                else if (endpoint >= 8U)
                {
                    khciState->registerBase->STALL_IH_DIS &= (uint8_t)(~(1UL << (endpoint - 8U)));
                }
#endif
                else
                {
                    /*no action*/
                }
            }
            else
            {
                if (endpoint < 8U)
                {
                    khciState->registerBase->STALL_OL_DIS &= (uint8_t)(~(1UL << endpoint));
                }
#if defined(FSL_FEATURE_USB_KHCI_HAS_STALL_HIGH) && (FSL_FEATURE_USB_KHCI_HAS_STALL_HIGH > 0U)
                else if (endpoint >= 8U)
                {
                    khciState->registerBase->STALL_OH_DIS &= (uint8_t)(~(1UL << (endpoint - 8U)));
                }
#endif
                else
                {
                    /*no action*/
                }
            }
        }
#endif
        /* Set endpoint stall in BDT. And then if the host send a IN/OUT tansaction, the device will response a STALL
         * state.
         */
        USB_KHCI_BDT_SET_CONTROL(
            (uint32_t)khciState->bdt, endpoint, direction,
            khciState->endpointState[index].stateUnion.stateBitField.bdtOdd,
            USB_LONG_TO_LITTLE_ENDIAN(
                (uint32_t)(USB_KHCI_BDT_BC(khciState->endpointState[index].stateUnion.stateBitField.maxPacketSize) |
                           USB_KHCI_BDT_DTS | USB_KHCI_BDT_STALL | USB_KHCI_BDT_OWN)));
    }

    khciState->registerBase->CTL &= (uint8_t)(~USB_CTL_TXSUSPENDTOKENBUSY_MASK);

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
    uint8_t endpoint = ep & USB_ENDPOINT_NUMBER_MASK;
    uint8_t direction =
        (ep & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >> USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT;
    uint8_t index = ((uint8_t)((uint32_t)endpoint << 1U)) | (uint8_t)direction;
    uint8_t i;

    /* Clear the endpoint stall state */
    khciState->endpointState[index].stateUnion.stateBitField.stalled = 0U;
    /* Reset the endpoint data toggle to DATA0 */
    khciState->endpointState[index].stateUnion.stateBitField.data0 = 0U;

    /* Clear stall state in BDT */
    for (i = 0U; i < 2U; i++)
    {
        USB_KHCI_BDT_SET_CONTROL(
            (uint32_t)khciState->bdt, endpoint, direction, i,
            USB_LONG_TO_LITTLE_ENDIAN(
                (uint32_t)(USB_KHCI_BDT_BC(khciState->endpointState[index].stateUnion.stateBitField.maxPacketSize) |
                           USB_KHCI_BDT_DTS | USB_KHCI_BDT_DATA01(0U))));
    }

    /* Clear stall state in endpoint control register */
    khciState->registerBase->ENDPOINT[endpoint].ENDPT &= (uint8_t)(~USB_ENDPT_EPSTALL_MASK);
#if defined(FSL_FEATURE_USB_KHCI_HAS_STALL_LOW) && (FSL_FEATURE_USB_KHCI_HAS_STALL_LOW > 0U)
    if (USB_CONTROL_ENDPOINT != endpoint)
    {
        if (USB_IN == direction)
        {
            if (endpoint < 8U)
            {
                khciState->registerBase->STALL_IL_DIS |= (uint8_t)(1UL << endpoint);
            }
#if defined(FSL_FEATURE_USB_KHCI_HAS_STALL_HIGH) && (FSL_FEATURE_USB_KHCI_HAS_STALL_HIGH > 0U)
            else if (endpoint >= 8U)
            {
                khciState->registerBase->STALL_IH_DIS |= (uint8_t)(1UL << (endpoint - 8U));
            }
#endif
            else
            {
                /*no action*/
            }
        }
        else
        {
            if (endpoint < 8U)
            {
                khciState->registerBase->STALL_OL_DIS |= (uint8_t)(1UL << endpoint);
            }
#if defined(FSL_FEATURE_USB_KHCI_HAS_STALL_HIGH) && (FSL_FEATURE_USB_KHCI_HAS_STALL_HIGH > 0U)
            else if (endpoint >= 8U)
            {
                khciState->registerBase->STALL_OH_DIS |= (uint8_t)(1UL << (endpoint - 8U));
            }
#endif
            else
            {
                /*no action*/
            }
        }
    }
#endif
    if ((USB_CONTROL_ENDPOINT != endpoint))
    {
        /* Cancel the transfer of the endpoint */
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
        if (kStatus_USB_Success != USB_DeviceKhciCancel(khciState, ep))
        {
            return kStatus_USB_Error;
        }
#else
        (void)USB_DeviceKhciCancel(khciState, ep);
#endif
    }

    /* Prime a transfer to receive next setup packet when the endpoint is a control out endpoint. */
    if ((USB_CONTROL_ENDPOINT == endpoint) && (USB_OUT == direction))
    {
        USB_DeviceKhciPrimeNextSetup(khciState);
    }

    khciState->registerBase->CTL &= (uint8_t)(~USB_CTL_TXSUSPENDTOKENBUSY_MASK);

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
    uint8_t *bdtBuffer;
    void *temp;
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
    khciState->registerBase->ISTAT = USB_INTEN_TOKDNEEN_MASK;

    /* Get the Control field of the BDT element according to the endpoint number, the direction and finished BDT ODD. */
    control = USB_KHCI_BDT_GET_CONTROL((uint32_t)khciState->bdt, endpoint, direction, bdtOdd);

    /* Get the buffer field of the BDT element according to the endpoint number, the direction and finished BDT ODD. */
    bdtBuffer = (uint8_t *)USB_KHCI_BDT_GET_ADDRESS((uint32_t)khciState->bdt, endpoint, direction, bdtOdd);

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

    if (0U != isSetup)
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
         * 2. The length of current tansaction is less than the max packet size of the current pipe.
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
            if ((0U != length) &&
                (0U == (length % khciState->endpointState[index].stateUnion.stateBitField.maxPacketSize)))
            {
                if (USB_CONTROL_ENDPOINT == endpoint)
                {
                    temp =
                        (void *)(&khciState->setupPacketBuffer[(USB_SETUP_PACKET_SIZE * khciState->setupBufferIndex)]);
                    usb_setup_struct_t *setup_packet = (usb_setup_struct_t *)temp;
                    /*
                     * Send the ZLT and terminate the token done interrupt service when the transferred length in data
                     * phase
                     * is less than the host request.
                     */
                    if (USB_SHORT_FROM_LITTLE_ENDIAN(setup_packet->wLength) >
                        khciState->endpointState[index].transferLength)
                    {
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
                        if (kStatus_USB_Success !=
                            USB_DeviceKhciEndpointTransfer(khciState, endpoint, USB_IN, (uint8_t *)NULL, 0U))
                        {
#if (defined(DEVICE_ECHO) && (DEVICE_ECHO > 0U))
                            usb_echo("prime error\r\n");
#endif
                        }
#else
                        (void)USB_DeviceKhciEndpointTransfer(khciState, endpoint, USB_IN, (uint8_t *)NULL, 0U);
#endif
                        return;
                    }
                }
                else if (0U != khciState->endpointState[index].stateUnion.stateBitField.zlt)
                {
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
                    if (kStatus_USB_Success !=
                        USB_DeviceKhciEndpointTransfer(khciState, endpoint, USB_IN, (uint8_t *)NULL, 0U))
                    {
#if (defined(DEVICE_ECHO) && (DEVICE_ECHO > 0U))
                        usb_echo("start transfer error\r\n");
#endif
                    }
#else
                    (void)USB_DeviceKhciEndpointTransfer(khciState, endpoint, USB_IN, (uint8_t *)NULL, 0U);
#endif
                    return;
                }
                else
                {
                }
            }
        }
        else
        {
            /* Send remaining data and terminate the token done interrupt service. */
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
            if (kStatus_USB_Success != USB_DeviceKhciSend(khciState, endpoint | (USB_IN << 0x07U),
                                                          khciState->endpointState[index].transferBuffer,
                                                          remainingLength))
            {
#if (defined(DEVICE_ECHO) && (DEVICE_ECHO > 0U))
                usb_echo("send error\r\n");
#endif
            }
#else
            (void)USB_DeviceKhciSend(khciState, endpoint | (USB_IN << 0x07U),
                                     khciState->endpointState[index].transferBuffer, remainingLength);
#endif
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
                    (void)memcpy(transferBuffer, buffer, length);
                }
                khciState->isDmaAlignBufferInusing = 0U;
            }
            /* The transferred length */
            khciState->endpointState[index].transferDone += length;
            /* Remaining length */
            remainingLength =
                khciState->endpointState[index].transferLength - khciState->endpointState[index].transferDone;

            if ((USB_CONTROL_ENDPOINT == endpoint) && (0U != isSetup))
            {
                khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_OUT].stateUnion.stateBitField.data0 = 1U;
                khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_IN].stateUnion.stateBitField.data0  = 1U;
            }
            else
            {
                khciState->endpointState[index].stateUnion.stateBitField.data0 ^= 1U;
            }
            khciState->endpointState[index].stateUnion.stateBitField.bdtOdd ^= 1U;
            if ((0U == khciState->endpointState[index].transferLength) || (0U == remainingLength) ||
                (khciState->endpointState[index].stateUnion.stateBitField.maxPacketSize > length))
            {
                message.length = khciState->endpointState[index].transferDone;
                if (0U != isSetup)
                {
                    message.buffer = bdtBuffer;
                }
                else
                {
                    message.buffer = khciState->endpointState[index].transferBuffer;
                }
                khciState->endpointState[index].stateUnion.stateBitField.transferring = 0U;
            }
            else
            {
                /* Receive remaining data and terminate the token done interrupt service. */
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
                if (kStatus_USB_Success != USB_DeviceKhciRecv(khciState, (endpoint) | (USB_OUT << 0x07U),
                                                              khciState->endpointState[index].transferBuffer,
                                                              remainingLength))
                {
#if (defined(DEVICE_ECHO) && (DEVICE_ECHO > 0U))
                    usb_echo("recv error\r\n");
#endif
                }
#else
                (void)USB_DeviceKhciRecv(khciState, (endpoint) | (USB_OUT << 0x07U),
                                         khciState->endpointState[index].transferBuffer, remainingLength);
#endif
                return;
            }
        }
    }

    message.isSetup = isSetup;
    message.code    = (endpoint) | (uint8_t)(((uint32_t)direction << 0x07U));

    /* Notify the up layer the KHCI status changed. */
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
    if (kStatus_USB_Success != USB_DeviceNotificationTrigger(khciState->deviceHandle, &message))
    {
#if (defined(DEVICE_ECHO) && (DEVICE_ECHO > 0U))
        usb_echo("notification error\n");
#endif
    }
#else
    (void)USB_DeviceNotificationTrigger(khciState->deviceHandle, &message);
#endif

    khciState->registerBase->CTL &= (uint8_t)(~USB_CTL_TXSUSPENDTOKENBUSY_MASK);
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
    khciState->registerBase->ISTAT = (USB_INTEN_USBRSTEN_MASK);
#if ((defined(USB_DEVICE_CONFIG_LOW_POWER_MODE)) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U))
    /* Clear the suspend interrupt */
    khciState->registerBase->ISTAT = (USB_INTEN_SLEEPEN_MASK);
    khciState->registerBase->USBCTRL &= (uint8_t)(~USB_USBCTRL_SUSP_MASK);
#endif

    message.buffer  = (uint8_t *)NULL;
    message.code    = (uint8_t)kUSB_DeviceNotifyBusReset;
    message.length  = 0U;
    message.isSetup = 0U;
    /* Notify up layer the USB bus reset signal detected. */
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
    if (kStatus_USB_Success != USB_DeviceNotificationTrigger(khciState->deviceHandle, &message))
    {
#if (defined(DEVICE_ECHO) && (DEVICE_ECHO > 0U))
        usb_echo("notification error\n");
#endif
    }
#else
    (void)USB_DeviceNotificationTrigger(khciState->deviceHandle, &message);
#endif
}

/* The USB suspend and resume signals need to be detected and handled when the low power or remote wakeup function
 * enabled. */
#if (defined(USB_DEVICE_CONFIG_LOW_POWER_MODE) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U))

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
    khciState->registerBase->INTEN |= USB_INTEN_RESUMEEN_MASK;
    khciState->registerBase->USBTRC0 |= USB_USBTRC0_USBRESMEN_MASK;
    khciState->registerBase->USBCTRL |= USB_USBCTRL_SUSP_MASK;
    /* Disable the suspend interrupt */
    khciState->registerBase->INTEN &= (uint8_t)(~(USB_INTEN_SLEEPEN_MASK));

    /* Clear the suspend interrupt */
    khciState->registerBase->ISTAT = (USB_INTEN_SLEEPEN_MASK);
    /* Clear the resume interrupt */
    khciState->registerBase->ISTAT = (USB_INTEN_RESUMEEN_MASK);

    message.buffer  = (uint8_t *)NULL;
    message.code    = (uint8_t)kUSB_DeviceNotifySuspend;
    message.length  = 0U;
    message.isSetup = 0U;

    /* Notify up layer the USB suspend signal detected. */
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
    if (kStatus_USB_Success != USB_DeviceNotificationTrigger(khciState->deviceHandle, &message))
    {
        return kStatus_USB_Error;
    }
#else
    (void)USB_DeviceNotificationTrigger(khciState->deviceHandle, &message);
#endif
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

    khciState->registerBase->USBCTRL &= (uint8_t)(~USB_USBCTRL_SUSP_MASK);
    /* Enable the suspend interrupt */
    khciState->registerBase->INTEN |= USB_INTEN_SLEEPEN_MASK;
    /* Disable the resume interrupt */
    khciState->registerBase->INTEN &= (uint8_t)(~(USB_INTEN_RESUMEEN_MASK));
    khciState->registerBase->USBTRC0 &= (uint8_t)(~USB_USBTRC0_USBRESMEN_MASK);

    /* Clear the resume interrupt */
    khciState->registerBase->ISTAT = (USB_INTEN_RESUMEEN_MASK);
    /* Clear the suspend interrupt */
    khciState->registerBase->ISTAT = (USB_INTEN_SLEEPEN_MASK);

    message.buffer  = (uint8_t *)NULL;
    message.code    = (uint8_t)kUSB_DeviceNotifyResume;
    message.length  = 0U;
    message.isSetup = 0U;

    /* Notify up layer the USB resume signal detected. */
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
    if (kStatus_USB_Success != USB_DeviceNotificationTrigger(khciState->deviceHandle, &message))
    {
        return kStatus_USB_Error;
    }
#else
    (void)USB_DeviceNotificationTrigger(khciState->deviceHandle, &message);
#endif
}
#endif /* USB_DEVICE_CONFIG_LOW_POWER_MODE */

#if (defined(USB_DEVICE_CONFIG_DETACH_ENABLE) && (USB_DEVICE_CONFIG_DETACH_ENABLE > 0U))
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
    khciState->registerBase->MISCCTRL &= (uint8_t)(~USB_MISCCTRL_VREDG_EN_MASK);
    /* Enable the VBUS rising interrupt */
    khciState->registerBase->MISCCTRL |= USB_MISCCTRL_VREDG_EN_MASK;

    message.buffer  = (uint8_t *)NULL;
    message.code    = (uint8_t)kUSB_DeviceNotifyAttach;
    message.length  = 0U;
    message.isSetup = 0U;

    /* Notify up layer the USB VBUS rising signal detected. */
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
    if (kStatus_USB_Success != USB_DeviceNotificationTrigger(khciState->deviceHandle, &message))
    {
        return kStatus_USB_Error;
    }
#else
    (void)USB_DeviceNotificationTrigger(khciState->deviceHandle, &message);
#endif
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
    khciState->registerBase->MISCCTRL &= (uint8_t)(~USB_MISCCTRL_VFEDG_EN_MASK);
    /* Enable the VBUS rising interrupt */
    khciState->registerBase->MISCCTRL |= USB_MISCCTRL_VFEDG_EN_MASK;

    message.buffer  = (uint8_t *)NULL;
    message.code    = (uint8_t)kUSB_DeviceNotifyDetach;
    message.length  = 0U;
    message.isSetup = 0U;

    /* Notify up layer the USB VBUS falling signal detected. */
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
    if (kStatus_USB_Success != USB_DeviceNotificationTrigger(khciState->deviceHandle, &message))
    {
        return kStatus_USB_Error;
    }
#else
    (void)USB_DeviceNotificationTrigger(khciState->deviceHandle, &message);
#endif
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
    khciState->registerBase->ISTAT = (USB_INTEN_SOFTOKEN_MASK);

    khciState->registerBase->ISTAT = (USB_INTEN_RESUMEEN_MASK);
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
    while (0U != (khciState->registerBase->ISTAT & (USB_INTEN_STALLEN_MASK)))
    {
        khciState->registerBase->ISTAT = (USB_INTEN_STALLEN_MASK);
    }

    /* Un-stall the control in and out pipe when the control in or out pipe stalled. */
    if ((0U != khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_IN].stateUnion.stateBitField.stalled) ||
        (0U != khciState->endpointState[(USB_CONTROL_ENDPOINT << 1U) | USB_OUT].stateUnion.stateBitField.stalled))
    {
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
        if ((kStatus_USB_Success !=
             USB_DeviceKhciEndpointUnstall(
                 khciState, (USB_CONTROL_ENDPOINT | (USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT)))) ||
            (kStatus_USB_Success !=
             USB_DeviceKhciEndpointUnstall(
                 khciState, (USB_CONTROL_ENDPOINT | (USB_OUT << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT)))))
        {
#if (defined(DEVICE_ECHO) && (DEVICE_ECHO > 0U))
            usb_echo("unstall endpoint error\n");
#endif
        }
#else
        (void)USB_DeviceKhciEndpointUnstall(
            khciState, (USB_CONTROL_ENDPOINT | (USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT)));
        (void)USB_DeviceKhciEndpointUnstall(
            khciState, (USB_CONTROL_ENDPOINT | (USB_OUT << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT)));
#endif
    }
}

#if defined(USB_DEVICE_CONFIG_ERROR_HANDLING) && (USB_DEVICE_CONFIG_ERROR_HANDLING > 0U)
static void USB_DeviceKhciInterruptError(usb_device_khci_state_struct_t *khciState)
{
    usb_device_callback_message_struct_t message;

    khciState->registerBase->ISTAT = (USB_INTEN_ERROREN_MASK);

    message.buffer  = (uint8_t *)NULL;
    message.code    = (uint8_t)kUSB_DeviceNotifyError;
    message.length  = 0U;
    message.isSetup = 0U;

    /* Notify up layer the USB error detected. */
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
    if (kStatus_USB_Success != USB_DeviceNotificationTrigger(khciState->deviceHandle, &message))
    {
        return kStatus_USB_Error;
    }
#else
    (void)USB_DeviceNotificationTrigger(khciState->deviceHandle, &message);
#endif
}
#endif /* USB_DEVICE_CONFIG_ERROR_HANDLING */

/*!
 * @brief Initialize the USB device KHCI instance.
 *
 * This function initializes the USB device KHCI module specified by the controllerId.
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

    if (((controllerId - (uint8_t)kUSB_ControllerKhci0) >= (uint8_t)USB_DEVICE_CONFIG_KHCI) ||
        ((controllerId - (uint8_t)kUSB_ControllerKhci0) >= (sizeof(khci_base) / sizeof(uint32_t))))
    {
        return kStatus_USB_ControllerNotFound;
    }
    khciState = &s_UsbDeviceKhciState[controllerId - (uint8_t)kUSB_ControllerKhci0];

    khciState->controllerId = controllerId;

    khciState->registerBase = (USB_Type *)khci_base[controllerId - (uint8_t)kUSB_ControllerKhci0];

    khciState->dmaAlignBuffer =
        (uint8_t *)&s_UsbDeviceKhciDmaAlignBuffer[controllerId - (uint8_t)kUSB_ControllerKhci0][0];

    /* Clear all interrupt flags. */
    khciState->registerBase->ISTAT = 0xFFU;

#if (defined(USB_DEVICE_CONFIG_OTG) && (USB_DEVICE_CONFIG_OTG))
    khciState->otgStatus = 0U;
#else
    /* Disable the device functionality. */
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
    if (kStatus_USB_Success != USB_DeviceKhciControl(khciState, kUSB_DeviceControlStop, NULL))
    {
        return kStatus_USB_Error;
    }
#else
    (void)USB_DeviceKhciControl(khciState, kUSB_DeviceControlStop, NULL);
#endif
#endif

#if defined(__DSC__) || defined(__CW__)
    khciState->bdt = (void *)s_UsbDeviceKhciBdtBuffer[controllerId - (uint8_t)kUSB_ControllerKhci0];
#else
    khciState->bdt = s_UsbDeviceKhciBdtBuffer[controllerId - (uint8_t)kUSB_ControllerKhci0];
#endif

    /* Set BDT buffer address */
    khciState->registerBase->BDTPAGE1 = (uint8_t)((((uint32_t)khciState->bdt) >> 8U) & 0xFFU);
    khciState->registerBase->BDTPAGE2 = (uint8_t)((((uint32_t)khciState->bdt) >> 16U) & 0xFFU);
    khciState->registerBase->BDTPAGE3 = (uint8_t)((((uint32_t)khciState->bdt) >> 24U) & 0xFFU);

#if (defined(USB_DEVICE_CONFIG_DETACH_ENABLE) && (USB_DEVICE_CONFIG_DETACH_ENABLE > 0U))
    khciState->registerBase->MISCCTRL |= USB_MISCCTRL_VREDG_EN_MASK | USB_MISCCTRL_VFEDG_EN_MASK;
#endif

#if defined(FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED) && (FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED > 0U) && \
    defined(USB_DEVICE_CONFIG_KEEP_ALIVE_MODE) && (USB_DEVICE_CONFIG_KEEP_ALIVE_MODE > 0U) &&             \
    defined(FSL_FEATURE_USB_KHCI_USB_RAM) && (FSL_FEATURE_USB_KHCI_USB_RAM > 0U)
    khciState->registerBase->CLK_RECOVER_CTRL |= USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_MASK;
    khciState->registerBase->KEEP_ALIVE_CTRL =
        USB_KEEP_ALIVE_CTRL_KEEP_ALIVE_EN_MASK | USB_KEEP_ALIVE_CTRL_OWN_OVERRD_EN_MASK |
        USB_KEEP_ALIVE_CTRL_WAKE_INT_EN_MASK | FSL_FEATURE_USB_KHCI_KEEP_ALIVE_MODE_CONTROL;
    /* wake on out and setup transaction */
    khciState->registerBase->KEEP_ALIVE_WKCTRL = 0x1U;
#if defined(FSL_FEATURE_SOC_MCGLITE_COUNT) && (FSL_FEATURE_SOC_MCGLITE_COUNT > 0U)
    MCG->MC |= MCG_MC_HIRCLPEN_MASK;
#endif

#endif
#if defined(FSL_FEATURE_USB_KHCI_HAS_STALL_LOW) && (FSL_FEATURE_USB_KHCI_HAS_STALL_LOW > 0U)
    khciState->registerBase->MISCCTRL |= USB_MISCCTRL_STL_ADJ_EN_MASK;
#endif

    /* Set KHCI device state to default value. */
    USB_DeviceKhciSetDefaultState(khciState);

    *khciHandle             = khciState;
    khciState->deviceHandle = (usb_device_struct_t *)handle;

    return kStatus_USB_Success;
}

/*!
 * @brief De-initialize the USB device KHCI instance.
 *
 * This function de-initializes the USB device KHCI module.
 *
 * @param khciHandle   Pointer of the device KHCI handle.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceKhciDeinit(usb_device_controller_handle khciHandle)
{
    usb_device_khci_state_struct_t *khciState = (usb_device_khci_state_struct_t *)khciHandle;

    if (NULL == khciHandle)
    {
        return kStatus_USB_InvalidHandle;
    }
    /* Clear all interrupt flags. */
    khciState->registerBase->ISTAT = 0xFFU;
    /* Disable all interrupts. */
    khciState->registerBase->INTEN = (0U);
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
    uint32_t index                            = (((uint32_t)endpointAddress & USB_ENDPOINT_NUMBER_MASK) << 1U) | USB_IN;
    usb_status_t status                       = kStatus_USB_Error;

    /* Save the transfer information */
    if (0U == khciState->endpointState[index].stateUnion.stateBitField.transferring)
    {
        khciState->endpointState[index].transferDone                      = 0U;
        khciState->endpointState[index].transferBuffer                    = buffer;
        khciState->endpointState[index].transferLength                    = length;
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
        status = USB_DeviceKhciEndpointTransfer(khciState, endpointAddress & USB_ENDPOINT_NUMBER_MASK, USB_IN,
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
    return status;
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
    uint32_t index      = (((uint32_t)endpointAddress & USB_ENDPOINT_NUMBER_MASK) << 1U) | USB_OUT;
    usb_status_t status = kStatus_USB_Error;

    if ((0U == length) && (USB_CONTROL_ENDPOINT == (endpointAddress & USB_ENDPOINT_NUMBER_MASK)))
    {
        khciState->endpointState[index].stateUnion.stateBitField.transferring = 0U;
        USB_DeviceKhciPrimeNextSetup(khciState);
    }
    else
    {
        /* Save the transfer information */
        if (0U == khciState->endpointState[index].stateUnion.stateBitField.transferring)
        {
            khciState->endpointState[index].transferDone   = 0U;
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

        if ((NULL != khciState->dmaAlignBuffer) && (0U == khciState->isDmaAlignBufferInusing) &&
            (USB_DEVICE_CONFIG_KHCI_DMA_ALIGN_BUFFER_LENGTH >= length) &&
            ((0U != (length & 0x03U)) || (0U != (((uint32_t)buffer) & 0x03U))))
        {
            khciState->endpointState[index].stateUnion.stateBitField.dmaAlign = 0U;
            buffer                                                            = khciState->dmaAlignBuffer;
            khciState->isDmaAlignBufferInusing                                = 1U;
        }

        /* Receive data when the device is not resetting. */
        if (0U == khciState->isResetting)
        {
            status = USB_DeviceKhciEndpointTransfer(khciState, endpointAddress & USB_ENDPOINT_NUMBER_MASK, USB_OUT,
                                                    buffer, length);
        }
    }
    return status;
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
    if (0U != khciState->endpointState[index].stateUnion.stateBitField.transferring)
    {
        message.length  = USB_CANCELLED_TRANSFER_LENGTH;
        message.buffer  = khciState->endpointState[index].transferBuffer;
        message.code    = ep;
        message.isSetup = 0U;
        khciState->endpointState[index].stateUnion.stateBitField.transferring = 0U;
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
        if (kStatus_USB_Success != USB_DeviceNotificationTrigger(khciState->deviceHandle, &message))
        {
            return kStatus_USB_Error;
        }
#else
        (void)USB_DeviceNotificationTrigger(khciState->deviceHandle, &message);
#endif
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
    uint16_t *temp16;
    uint8_t *temp8;
    uint8_t count;

#if (defined(USB_DEVICE_CHARGER_DETECT_ENABLE) && (USB_DEVICE_CHARGER_DETECT_ENABLE > 0U)) && \
    (defined(FSL_FEATURE_SOC_USBDCD_COUNT) && (FSL_FEATURE_SOC_USBDCD_COUNT > 0U))
    usb_device_dcd_state_struct_t *dcdState;
    dcdState = &s_UsbDeviceDcdState[khciState->controllerId - kUSB_ControllerKhci0];
    usb_device_dcd_charging_time_t *deviceDcdTimingConfig = (usb_device_dcd_charging_time_t *)param;
#endif
#if ((defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP)) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U))
    usb_device_struct_t *deviceHandle;
#endif
#if ((defined(USB_DEVICE_CONFIG_LOW_POWER_MODE)) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U))
#if ((defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP)) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U))
    uint64_t startTick;
#endif
#endif
    usb_status_t status = kStatus_USB_Error;

    if (NULL == khciHandle)
    {
        return kStatus_USB_InvalidHandle;
    }

#if ((defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP)) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U))
    deviceHandle = (usb_device_struct_t *)khciState->deviceHandle;
#endif

    switch (type)
    {
        case kUSB_DeviceControlRun:
            khciState->registerBase->USBCTRL = 0U;
#if defined(FSL_FEATURE_USB_KHCI_OTG_ENABLED) && (FSL_FEATURE_USB_KHCI_OTG_ENABLED > 0U)
            if (0U != (khciState->registerBase->OTGCTL & USB_OTGCTL_OTGEN_MASK))
            {
                khciState->registerBase->OTGCTL |= USB_OTGCTL_DPHIGH_MASK;
            }
#endif /* FSL_FEATURE_USB_KHCI_OTG_ENABLED */
            khciState->registerBase->CONTROL |= USB_CONTROL_DPPULLUPNONOTG_MASK;
            khciState->registerBase->CTL |= USB_CTL_USBENSOFEN_MASK;

            status = kStatus_USB_Success;
            break;
        case kUSB_DeviceControlStop:
#if defined(FSL_FEATURE_USB_KHCI_OTG_ENABLED) && (FSL_FEATURE_USB_KHCI_OTG_ENABLED > 0U)
            if (0U != (khciState->registerBase->OTGCTL & USB_OTGCTL_OTGEN_MASK))
            {
                khciState->registerBase->OTGCTL &= (uint8_t)(~USB_OTGCTL_DPHIGH_MASK);
            }
#endif /* FSL_FEATURE_USB_KHCI_OTG_ENABLED */
            khciState->registerBase->CONTROL &= (uint8_t)(~USB_CONTROL_DPPULLUPNONOTG_MASK);
            status = kStatus_USB_Success;
            break;
        case kUSB_DeviceControlEndpointInit:
            if (NULL != param)
            {
                status = USB_DeviceKhciEndpointInit(khciState, (usb_device_endpoint_init_struct_t *)param);
            }
            break;
        case kUSB_DeviceControlEndpointDeinit:
            if (NULL != param)
            {
                temp8  = (uint8_t *)param;
                status = USB_DeviceKhciEndpointDeinit(khciState, *temp8);
            }
            break;
        case kUSB_DeviceControlEndpointStall:
            if (NULL != param)
            {
                temp8  = (uint8_t *)param;
                status = USB_DeviceKhciEndpointStall(khciState, *temp8);
            }
            break;
        case kUSB_DeviceControlEndpointUnstall:
            if (NULL != param)
            {
                temp8  = (uint8_t *)param;
                status = USB_DeviceKhciEndpointUnstall(khciState, *temp8);
            }
            break;
        case kUSB_DeviceControlGetDeviceStatus:
            if (NULL != param)
            {
                temp16  = (uint16_t *)param;
                *temp16 = (USB_DEVICE_CONFIG_SELF_POWER << (USB_REQUEST_STANDARD_GET_STATUS_DEVICE_SELF_POWERED_SHIFT))
#if ((defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP)) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U))
                          | ((uint16_t)(((uint32_t)deviceHandle->remotewakeup)
                                        << (USB_REQUEST_STANDARD_GET_STATUS_DEVICE_REMOTE_WARKUP_SHIFT)))
#endif
                    ;
                status = kStatus_USB_Success;
            }
            break;
        case kUSB_DeviceControlGetEndpointStatus:
            if (NULL != param)
            {
                usb_device_endpoint_status_struct_t *endpointStatus = (usb_device_endpoint_status_struct_t *)param;

                if (((endpointStatus->endpointAddress) & USB_ENDPOINT_NUMBER_MASK) < USB_DEVICE_CONFIG_ENDPOINTS)
                {
                    endpointStatus->endpointStatus = (uint16_t)(
                        (khciState
                             ->endpointState[(((endpointStatus->endpointAddress) & USB_ENDPOINT_NUMBER_MASK) << 1U) |
                                             (((endpointStatus->endpointAddress) &
                                               USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
                                              USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT)]
                             .stateUnion.stateBitField.stalled == 1U) ?
                            kUSB_DeviceEndpointStateStalled :
                            kUSB_DeviceEndpointStateIdle);
                    status = kStatus_USB_Success;
                }
            }
            break;
        case kUSB_DeviceControlSetDeviceAddress:
            if (NULL != param)
            {
                temp8                         = (uint8_t *)param;
                khciState->registerBase->ADDR = (*temp8);
                status                        = kStatus_USB_Success;
            }
            break;
        case kUSB_DeviceControlGetSynchFrame:
            break;
#if ((defined(USB_DEVICE_CONFIG_LOW_POWER_MODE)) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U))
#if defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U)
        case kUSB_DeviceControlResume:
            khciState->registerBase->CTL |= USB_CTL_RESUME_MASK;
            startTick = deviceHandle->hwTick;
            while ((deviceHandle->hwTick - startTick) < 10U)
            {
                __NOP();
            }
            khciState->registerBase->CTL &= (uint8_t)(~USB_CTL_RESUME_MASK);
            status = kStatus_USB_Success;
            break;
#endif /* USB_DEVICE_CONFIG_REMOTE_WAKEUP */
        case kUSB_DeviceControlSuspend:
            status = kStatus_USB_Success;
            break;
#endif /* USB_DEVICE_CONFIG_LOW_POWER_MODE */
        case kUSB_DeviceControlSetDefaultStatus:
            for (count = 0U; count < USB_DEVICE_CONFIG_ENDPOINTS; count++)
            {
#if (defined(USB_DEVICE_CONFIG_RETURN_VALUE_CHECK) && (USB_DEVICE_CONFIG_RETURN_VALUE_CHECK > 0U))
                if ((kStatus_USB_Success != USB_DeviceKhciEndpointDeinit(khciState, (count | (USB_IN << 0x07U)))) ||
                    (kStatus_USB_Success != USB_DeviceKhciEndpointDeinit(khciState, (count | (USB_OUT << 0x07U)))))
                {
                    return kStatus_USB_Error;
                }
#else
                (void)USB_DeviceKhciEndpointDeinit(khciState, (count | (USB_IN << 0x07U)));
                (void)USB_DeviceKhciEndpointDeinit(khciState, (count | (USB_OUT << 0x07U)));
#endif
            }
            USB_DeviceKhciSetDefaultState(khciState);
            status = kStatus_USB_Success;
            break;
        case kUSB_DeviceControlGetSpeed:
            if (NULL != param)
            {
                temp8  = (uint8_t *)param;
                *temp8 = USB_SPEED_FULL;
                status = kStatus_USB_Success;
            }
            break;
#if (defined(USB_DEVICE_CONFIG_OTG) && (USB_DEVICE_CONFIG_OTG))
        case kUSB_DeviceControlGetOtgStatus:
            *((uint8_t *)param) = khciState->otgStatus;
            break;
        case kUSB_DeviceControlSetOtgStatus:
            khciState->otgStatus = *((uint8_t *)param);
            break;
#endif
        case kUSB_DeviceControlSetTestMode:
            break;
#if (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U))
        case kUSB_DeviceControlUpdateHwTick:
            /*udpate 1ms time tick*/
            status = kStatus_USB_Success;
            break;
#endif

        default:
            /*no action*/
            break;
    }

    return status;
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
    status &= khciState->registerBase->INTEN;
#if defined(FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED) && (FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED > 0U) && \
    defined(USB_DEVICE_CONFIG_KEEP_ALIVE_MODE) && (USB_DEVICE_CONFIG_KEEP_ALIVE_MODE > 0U) &&             \
    defined(FSL_FEATURE_USB_KHCI_USB_RAM) && (FSL_FEATURE_USB_KHCI_USB_RAM > 0U)
    /* Clear EEP_ALIVE_CTRL_WAKE_INT interrupt state */
    if (0U != (khciState->registerBase->KEEP_ALIVE_CTRL & USB_KEEP_ALIVE_CTRL_WAKE_INT_STS_MASK))
    {
        khciState->registerBase->KEEP_ALIVE_CTRL |= USB_KEEP_ALIVE_CTRL_WAKE_INT_STS_MASK;
    }
    /* Clear SOFTOK interrupt state */
    if (0U != (khciState->registerBase->ISTAT & USB_ISTAT_SOFTOK_MASK))
    {
        khciState->registerBase->ISTAT = USB_ISTAT_SOFTOK_MASK;
    }
#endif
#if defined(USB_DEVICE_CONFIG_ERROR_HANDLING) && (USB_DEVICE_CONFIG_ERROR_HANDLING > 0U)
    /* Error interrupt */
    if (0U != (status & USB_INTEN_ERROREN_MASK))
    {
        USB_DeviceKhciInterruptError(khciState);
    }
#endif /* USB_DEVICE_CONFIG_ERROR_HANDLING */
    /* Token done interrupt */
    if (0U != (status & USB_INTEN_TOKDNEEN_MASK))
    {
        USB_DeviceKhciInterruptTokenDone(khciState);
    }

    /* Reset interrupt */
    if (0U != (status & USB_INTEN_USBRSTEN_MASK))
    {
        USB_DeviceKhciInterruptReset(khciState);
    }

#if (defined(USB_DEVICE_CONFIG_LOW_POWER_MODE) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U))
    /* Suspend interrupt */
    if (0U != (status & USB_INTEN_SLEEPEN_MASK))
    {
        USB_DeviceKhciInterruptSleep(khciState);
    }

    /* Resume interrupt */
    if (0U != (status & USB_INTEN_RESUMEEN_MASK))
    {
        USB_DeviceKhciInterruptResume(khciState);
    }

    /* Check for Asynchronous Resume interrupt if it was enabled */
    if ((0U != (khciState->registerBase->USBTRC0 & USB_USBTRC0_USB_RESUME_INT_MASK)) &&
        (0U != (khciState->registerBase->USBTRC0 & USB_USBTRC0_USBRESMEN_MASK)))
    {
        USB_DeviceKhciInterruptResume(khciState);
    }
#endif /* USB_DEVICE_CONFIG_LOW_POWER_MODE */

    /* Endpoint stalled interrupt */
    if (0U != (status & USB_INTEN_STALLEN_MASK))
    {
        USB_DeviceKhciInterruptStall(khciState);
    }

#if (defined(USB_DEVICE_CONFIG_DETACH_ENABLE) && (USB_DEVICE_CONFIG_DETACH_ENABLE > 0U)) && \
    (defined(FSL_FEATURE_USB_KHCI_VBUS_DETECT_ENABLED) && (FSL_FEATURE_USB_KHCI_VBUS_DETECT_ENABLED > 0U))
    if (0U != (khciState->registerBase->USBTRC0 & USB_USBTRC0_VREDG_DET_MASK))
    {
        USB_DeviceKhciInterruptVbusRising(khciState);
    }

    if (0U != (khciState->registerBase->USBTRC0 & USB_USBTRC0_VFEDG_DET_MASK))
    {
        USB_DeviceKhciInterruptVbusFalling(khciState);
    }
#endif /* USB_DEVICE_CONFIG_DETACH_ENABLE && FSL_FEATURE_USB_KHCI_VBUS_DETECT_ENABLED */

#if 0U
    /* Sof token interrupt */
    if (0U != (status & USB_INTEN_SOFTOKEN_MASK))
    {
        USB_DeviceKhciInterruptSof(khciState);
    }
#endif

#if ((defined FSL_FEATURE_USB_KHCI_IRC48M_MODULE_CLOCK_ENABLED) && \
     (FSL_FEATURE_USB_KHCI_IRC48M_MODULE_CLOCK_ENABLED > 0U))
    status = khciState->registerBase->CLK_RECOVER_INT_STATUS;
    if (0U != status)
    {
        /* USB RECOVER interrupt is happened */
        if (0U != (USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_MASK & status))
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

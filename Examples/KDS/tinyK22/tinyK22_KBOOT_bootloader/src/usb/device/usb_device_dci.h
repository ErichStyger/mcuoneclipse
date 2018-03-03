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

#ifndef __USB_DEVICE_DCI_H__
#define __USB_DEVICE_DCI_H__

/*!
 * @addtogroup usb_device_controller_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Macro to define controller handle */
#define usb_device_controller_handle usb_device_handle

/*! @brief Available notify types for device notification */
typedef enum _usb_device_notification
{
    kUSB_DeviceNotifyBusReset = 0x10U, /*!< Reset signal detected */
    kUSB_DeviceNotifySuspend,          /*!< Suspend signal detected */
    kUSB_DeviceNotifyResume,           /*!< Resume signal detected */
    kUSB_DeviceNotifyError,            /*!< Errors happened in bus */
    kUSB_DeviceNotifyDetach,           /*!< Device disconnected from a host */
    kUSB_DeviceNotifyAttach,           /*!< Device connected to a host */
} usb_device_notification_t;

/*! @brief Device notification message structure */
typedef struct _usb_device_callback_message_struct
{
    uint8_t *buffer; /*!< Transferred buffer */
    uint32_t length; /*!< Transferred data length */
    uint8_t code;    /*!< Notification code */
    uint8_t isSetup; /*!< Is in a setup phase */
} usb_device_callback_message_struct_t;

/*! @brief Control type for controller */
typedef enum _usb_device_control_type
{
    kUSB_DeviceControlRun = 0U,          /*!< Enable the device functionality */
    kUSB_DeviceControlStop,              /*!< Disable the device functionality */
    kUSB_DeviceControlEndpointInit,      /*!< Initialize a specified endpoint */
    kUSB_DeviceControlEndpointDeinit,    /*!< De-initialize a specified endpoint */
    kUSB_DeviceControlEndpointStall,     /*!< Stall a specified endpoint */
    kUSB_DeviceControlEndpointUnstall,   /*!< Unstall a specified endpoint */
    kUSB_DeviceControlGetDeviceStatus,   /*!< Get device status */
    kUSB_DeviceControlGetEndpointStatus, /*!< Get endpoint status */
    kUSB_DeviceControlSetDeviceAddress,  /*!< Set device address */
    kUSB_DeviceControlGetSynchFrame,     /*!< Get current frame */
    kUSB_DeviceControlResume,            /*!< Drive controller to generate a resume signal in USB bus */
    kUSB_DeviceControlSetDefaultStatus,  /*!< Set controller to default status */
    kUSB_DeviceControlGetSpeed,          /*!< Get current speed */
    kUSB_DeviceControlGetOtgStatus,      /*!< Get OTG status */
    kUSB_DeviceControlSetOtgStatus,      /*!< Set OTG status */
    kUSB_DeviceControlSetTestMode,       /*!< Drive xCHI into test mode */
} usb_device_control_type_t;

/*! @brief USB device controller initialization function typedef */
typedef usb_status_t (*usb_device_controller_init_t)(uint8_t controllerId,
                                                     usb_device_handle handle,
                                                     usb_device_controller_handle *controllerHandle);

/*! @brief USB device controller de-initialization function typedef */
typedef usb_status_t (*usb_device_controller_deinit_t)(usb_device_controller_handle controllerHandle);

/*! @brief USB device controller send data function typedef */
typedef usb_status_t (*usb_device_controller_send_t)(usb_device_controller_handle controllerHandle,
                                                     uint8_t endpointAddress,
                                                     uint8_t *buffer,
                                                     uint32_t length);

/*! @brief USB device controller receive data function typedef */
typedef usb_status_t (*usb_device_controller_recv_t)(usb_device_controller_handle controllerHandle,
                                                     uint8_t endpointAddress,
                                                     uint8_t *buffer,
                                                     uint32_t length);

/*! @brief USB device controller cancel transfer function in a specified endpoint typedef */
typedef usb_status_t (*usb_device_controller_cancel_t)(usb_device_controller_handle controllerHandle,
                                                       uint8_t endpointAddress);

/*! @brief USB device controller control function typedef */
typedef usb_status_t (*usb_device_controller_control_t)(usb_device_controller_handle controllerHandle,
                                                        usb_device_control_type_t command,
                                                        void *param);

/*! @brief USB device controller interface structure */
typedef struct _usb_device_controller_interface_struct
{
    usb_device_controller_init_t deviceInit;       /*!< Controller initialization */
    usb_device_controller_deinit_t deviceDeinit;   /*!< Controller de-initialization */
    usb_device_controller_send_t deviceSend;       /*!< Controller send data */
    usb_device_controller_recv_t deviceRecv;       /*!< Controller receive data */
    usb_device_controller_cancel_t deviceCancel;   /*!< Controller cancel transfer */
    usb_device_controller_control_t deviceControl; /*!< Controller control */
} usb_device_controller_interface_struct_t;

/*! @brief USB device status structure */
typedef struct _usb_device_struct
{
    usb_device_controller_handle controllerHandle;                       /*!< Controller handle */
    const usb_device_controller_interface_struct_t *controllerInterface; /*!< Controller interface handle */
#if USB_DEVICE_CONFIG_USE_TASK
    usb_osa_msgq_handle notificationQueue; /*!< Message queue */
#endif
    usb_device_callback_t deviceCallback; /*!< Device callback function pointer */
    usb_device_endpoint_callback_struct_t
        endpointCallback[USB_DEVICE_CONFIG_ENDPOINTS << 1U]; /*!< Endpoint callback function structure */
    uint8_t deviceAddress;                                   /*!< Current device address */
    uint8_t controllerId;                                    /*!< Controller ID */
    uint8_t state;                                           /*!< Current device state */
} usb_device_struct_t;

/*******************************************************************************
 * API
 ******************************************************************************/

/*! @}*/

#endif /* __USB_DEVICE_DCI_H__ */

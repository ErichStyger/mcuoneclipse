/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuRTOS.h"

#include "usb_host_config.h"
#include "usb_host.h"
#include "fsl_device_registers.h"
#include "usb_host_msd.h"
#include "board.h"
#include "host_msd_fatfs.h"
#include "fsl_common.h"
#if (defined(FSL_FEATURE_SOC_SYSMPU_COUNT) && (FSL_FEATURE_SOC_SYSMPU_COUNT > 0U))
#include "fsl_sysmpu.h"
#endif /* FSL_FEATURE_SOC_SYSMPU_COUNT */
#include "app.h"
#include "board.h"

#if ((!USB_HOST_CONFIG_KHCI) && (!USB_HOST_CONFIG_EHCI) && (!USB_HOST_CONFIG_OHCI) && (!USB_HOST_CONFIG_IP3516HS))
#error Please enable USB_HOST_CONFIG_KHCI, USB_HOST_CONFIG_EHCI, USB_HOST_CONFIG_OHCI, or USB_HOST_CONFIG_IP3516HS in file usb_host_config.
#endif

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief host callback function.
 *
 * device attach/detach callback function.
 *
 * @param deviceHandle        device handle.
 * @param configurationHandle attached device's configuration descriptor information.
 * @param eventCode           callback event code, please reference to enumeration host_event_t.
 *
 * @retval kStatus_USB_Success              The host is initialized successfully.
 * @retval kStatus_USB_NotSupported         The application don't support the configuration.
 */
static usb_status_t USB_HostEvent(usb_device_handle deviceHandle,
                                  usb_host_configuration_handle configurationHandle,
                                  uint32_t eventCode);

/*!
 * @brief app initialization.
 */
static void USB_HostApplicationInit(void);

static void USB_HostTask(void *param);

static void USB_HostApplicationTask(void *param);

extern void USB_HostClockInit(void);
extern void USB_HostIsrEnable(void);
extern void USB_HostTaskFn(void *param);
void BOARD_InitHardware(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Allocate the memory for the heap. */
#if defined(configAPPLICATION_ALLOCATED_HEAP) && (configAPPLICATION_ALLOCATED_HEAP)
USB_DMA_NONINIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE) uint8_t ucHeap[configTOTAL_HEAP_SIZE];
#endif
/*! @brief USB host msd fatfs instance global variable */
extern usb_host_msd_fatfs_instance_t g_MsdFatfsInstance;
usb_host_handle g_HostHandle;

/*******************************************************************************
 * Code
 ******************************************************************************/

void USB0_IRQHandler(void)
{
    USB_HostKhciIsrFunction(g_HostHandle);
    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
    exception return operation might vector to incorrect interrupt */
    __DSB();
}

void USB_HostClockInit(void)
{
    SystemCoreClockUpdate();
    CLOCK_EnableUsbfs0Clock(kCLOCK_UsbSrcPll0, CLOCK_GetFreq(kCLOCK_PllFllSelClk));
}

void USB_HostIsrEnable(void)
{
    uint8_t irqNumber;

    uint8_t usbHOSTKhciIrq[] = USB_IRQS;
    irqNumber                = usbHOSTKhciIrq[CONTROLLER_ID - kUSB_ControllerKhci0];

/* Install isr, set priority, and enable IRQ. */
#if defined(__GIC_PRIO_BITS)
    GIC_SetPriority((IRQn_Type)irqNumber, USB_HOST_INTERRUPT_PRIORITY);
#else
    NVIC_SetPriority((IRQn_Type)irqNumber, USB_HOST_INTERRUPT_PRIORITY);
#endif
    EnableIRQ((IRQn_Type)irqNumber);
}

void USB_HostTaskFn(void *param)
{
    USB_HostKhciTaskFunction(param);
}

/*!
 * @brief USB isr function.
 */

static usb_status_t USB_HostEvent(usb_device_handle deviceHandle,
                                  usb_host_configuration_handle configurationHandle,
                                  uint32_t eventCode)
{
    usb_status_t status = kStatus_USB_Success;
    switch (eventCode & 0x0000FFFFU)
    {
        case kUSB_HostEventAttach:
            status = USB_HostMsdEvent(deviceHandle, configurationHandle, eventCode);
            break;

        case kUSB_HostEventNotSupported:
            usb_echo("device not supported.\r\n");
            break;

        case kUSB_HostEventEnumerationDone:
            status = USB_HostMsdEvent(deviceHandle, configurationHandle, eventCode);
            break;

        case kUSB_HostEventDetach:
            status = USB_HostMsdEvent(deviceHandle, configurationHandle, eventCode);
            break;

        case kUSB_HostEventEnumerationFail:
            usb_echo("enumeration failed\r\n");
            break;

        default:
            break;
    }
    return status;
}

static void USB_HostApplicationInit(void)
{
    usb_status_t status = kStatus_USB_Success;

    USB_HostClockInit();

#if ((defined FSL_FEATURE_SOC_SYSMPU_COUNT) && (FSL_FEATURE_SOC_SYSMPU_COUNT))
    SYSMPU_Enable(SYSMPU, 0);
#endif /* FSL_FEATURE_SOC_SYSMPU_COUNT */

    status = USB_HostInit(CONTROLLER_ID, &g_HostHandle, USB_HostEvent);
    if (status != kStatus_USB_Success)
    {
        usb_echo("host init error\r\n");
        return;
    }
    USB_HostIsrEnable();

    usb_echo("host init done\r\n");
}

static void USB_HostTask(void *param)
{
    while (1)
    {
        USB_HostTaskFn(param);
    }
}

static void USB_HostApplicationTask(void *param)
{
    while (1)
    {
        USB_HostMsdTask(param);
    }
}

int main2(void)
{
    BOARD_InitPins();
    BOARD_BootClockHSRUN();
    BOARD_InitDebugConsole();

    USB_HostApplicationInit();

    if (xTaskCreate(USB_HostTask, "usb host task", 2*2000L / sizeof(portSTACK_TYPE), g_HostHandle, 4, NULL) != pdPASS)
    {
        usb_echo("create host task error\r\n");
    }
    if (xTaskCreate(USB_HostApplicationTask, "app task", 2*2300L / sizeof(portSTACK_TYPE), &g_MsdFatfsInstance, 3,
                    NULL) != pdPASS)
    {
        usb_echo("create app task error\r\n");
    }

    vTaskStartScheduler();

    while (1)
    {
        ;
    }
}

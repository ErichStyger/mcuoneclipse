/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include <string.h>

#include "serial_manager.h"

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))

#include "generic_list.h"

/*
 * The OSA_USED macro can only be defined when the OSA component is used.
 * If the source code of the OSA component does not exist, the OSA_USED cannot be defined.
 * OR, If OSA component is not added into project event the OSA source code exists, the OSA_USED
 * also cannot be defined.
 * The source code path of the OSA component is <MCUXpresso_SDK>/components/osa.
 *
 */
#if defined(OSA_USED)

#if (defined(SERIAL_MANAGER_USE_COMMON_TASK) && (SERIAL_MANAGER_USE_COMMON_TASK > 0U))
#include "common_task.h"
#else
#include "fsl_os_abstraction.h"
#endif

#endif

#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#ifndef NDEBUG
#if (defined(DEBUG_CONSOLE_ASSERT_DISABLE) && (DEBUG_CONSOLE_ASSERT_DISABLE > 0U))
#undef assert
#define assert(n)
#endif
#endif

#define SERIAL_EVENT_DATA_RECEIVED (1U << 0)
#define SERIAL_EVENT_DATA_SENT (1U << 1)

#define SERIAL_MANAGER_WRITE_TAG 0xAABB5754U
#define SERIAL_MANAGER_READ_TAG 0xBBAA5244U

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
typedef enum _serial_manager_transmission_mode
{
    kSerialManager_TransmissionBlocking = 0x0U,    /*!< Blocking transmission*/
    kSerialManager_TransmissionNonBlocking = 0x1U, /*!< None blocking transmission*/
} serial_manager_transmission_mode_t;

/* TX transfer structure */
typedef struct _serial_manager_transfer
{
    uint8_t *buffer;
    volatile uint32_t length;
    volatile uint32_t soFar;
    serial_manager_transmission_mode_t mode;
    serial_manager_status_t status;
} serial_manager_transfer_t;
#endif

/* write handle structure */
typedef struct _serial_manager_send_handle
{
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    list_element_t link; /*!< list element of the link */
    serial_manager_transfer_t transfer;
#endif
    struct _serial_manager_handle *serialManagerHandle;
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    serial_manager_callback_t callback;
    void *callbackParam;
    uint32_t tag;
#endif
} serial_manager_write_handle_t;

typedef serial_manager_write_handle_t serial_manager_read_handle_t;

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
/* receive state structure */
typedef struct _serial_manager_read_ring_buffer
{
    uint8_t *ringBuffer;
    uint32_t ringBufferSize;
    volatile uint32_t ringHead;
    volatile uint32_t ringTail;
} serial_manager_read_ring_buffer_t;
#endif

#if defined(__CC_ARM)
#pragma anon_unions
#endif
/* The serial manager handle structure */
typedef struct _serial_manager_handle
{
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    list_t runningWriteHandleHead;   /*!< The queue of running write handle */
    list_t completedWriteHandleHead; /*!< The queue of completed write handle */
#endif
    serial_manager_read_handle_t *openedReadHandleHead;
    uint32_t openedWriteHandleCount;
    union
    {
        uint8_t lowLevelhandleBuffer[1];
#if (defined(SERIAL_PORT_TYPE_UART) && (SERIAL_PORT_TYPE_UART > 0U))
        uint8_t uartHandleBuffer[SERIAL_PORT_UART_HANDLE_SIZE];
#endif
#if (defined(SERIAL_PORT_TYPE_USBCDC) && (SERIAL_PORT_TYPE_USBCDC > 0U))
        uint8_t usbcdcHandleBuffer[SERIAL_PORT_USB_CDC_HANDLE_SIZE];
#endif
#if (defined(SERIAL_PORT_TYPE_SWO) && (SERIAL_PORT_TYPE_SWO > 0U))
        uint8_t swoHandleBuffer[SERIAL_PORT_SWO_HANDLE_SIZE];
#endif
    };
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    serial_manager_read_ring_buffer_t ringBuffer;
#endif

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))

#if defined(OSA_USED)

#if (defined(SERIAL_MANAGER_USE_COMMON_TASK) && (SERIAL_MANAGER_USE_COMMON_TASK > 0U))
    common_task_message_t commontaskMsg;
#else
    uint8_t event[OSA_EVENT_HANDLE_SIZE]; /*!< Event instance */
    uint8_t taskId[OSA_TASK_HANDLE_SIZE]; /*!< Task handle */
#endif

#endif

#endif

    serial_port_type_t type;
} serial_manager_handle_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

#if (defined(SERIAL_PORT_TYPE_UART) && (SERIAL_PORT_TYPE_UART > 0U))
serial_manager_status_t Serial_UartInit(serial_handle_t serialHandle, void *config);
serial_manager_status_t Serial_UartDeinit(serial_handle_t serialHandle);
serial_manager_status_t Serial_UartWrite(serial_handle_t serialHandle, uint8_t *buffer, uint32_t length);
#if !(defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
serial_manager_status_t Serial_UartRead(serial_handle_t serialHandle, uint8_t *buffer, uint32_t length);
#endif
serial_manager_status_t Serial_UartCancelWrite(serial_handle_t serialHandle); // @suppress("Unused function declaration")
serial_manager_status_t Serial_UartInstallTxCallback(serial_handle_t serialHandle, // @suppress("Unused function declaration")
                                                     serial_manager_callback_t callback,
                                                     void *callbackParam);
serial_manager_status_t Serial_UartInstallRxCallback(serial_handle_t serialHandle, // @suppress("Unused function declaration")
                                                     serial_manager_callback_t callback,
                                                     void *callbackParam);
void Serial_UartIsrFunction(serial_handle_t serialHandle); // @suppress("Unused function declaration")
#endif

#if (defined(SERIAL_PORT_TYPE_USBCDC) && (SERIAL_PORT_TYPE_USBCDC > 0U))
serial_manager_status_t Serial_UsbCdcInit(serial_handle_t serialHandle, void *config);
serial_manager_status_t Serial_UsbCdcDeinit(serial_handle_t serialHandle);
serial_manager_status_t Serial_UsbCdcWrite(serial_handle_t serialHandle, uint8_t *buffer, uint32_t length);
serial_manager_status_t Serial_UsbCdcCancelWrite(serial_handle_t serialHandle);
serial_manager_status_t Serial_UsbCdcInstallTxCallback(serial_handle_t serialHandle,
                                                       serial_manager_callback_t callback,
                                                       void *callbackParam);
serial_manager_status_t Serial_UsbCdcInstallRxCallback(serial_handle_t serialHandle,
                                                       serial_manager_callback_t callback,
                                                       void *callbackParam);
void Serial_UsbCdcIsrFunction(serial_handle_t serialHandle);
#endif

#if (defined(SERIAL_PORT_TYPE_SWO) && (SERIAL_PORT_TYPE_SWO > 0U))
serial_manager_status_t Serial_SwoInit(serial_handle_t serialHandle, void *config);
serial_manager_status_t Serial_SwoDeinit(serial_handle_t serialHandle);
serial_manager_status_t Serial_SwoWrite(serial_handle_t serialHandle, uint8_t *buffer, uint32_t length);
#if !(defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
serial_manager_status_t Serial_SwoRead(serial_handle_t serialHandle, uint8_t *buffer, uint32_t length);
#endif
serial_manager_status_t Serial_SwoCancelWrite(serial_handle_t serialHandle);
serial_manager_status_t Serial_SwoInstallTxCallback(serial_handle_t serialHandle,
                                                    serial_manager_callback_t callback,
                                                    void *callbackParam);
serial_manager_status_t Serial_SwoInstallRxCallback(serial_handle_t serialHandle,
                                                    serial_manager_callback_t callback,
                                                    void *callbackParam);
void Serial_SwoIsrFunction(serial_handle_t serialHandle);
#endif

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
static void SerialManager_Task(void *param);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))

#if defined(OSA_USED)

#if (defined(SERIAL_MANAGER_USE_COMMON_TASK) && (SERIAL_MANAGER_USE_COMMON_TASK > 0U))

#else
                                          /*
                                           * \brief Defines the serial manager task's stack
                                           */
OSA_TASK_DEFINE(SerialManager_Task, SERIAL_MANAGER_TASK_PRIORITY, 1, SERIAL_MANAGER_TASK_STACK_SIZE, false);
#endif

#endif

#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
static void SerialManager_AddTail(list_t *queue, serial_manager_write_handle_t *node)
{
    LIST_AddTail(queue, &node->link);
}

static void SerialManager_RemoveHead(list_t *queue)
{
    LIST_RemoveHead(queue);
}
#endif

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))

static serial_manager_status_t SerialManager_StartWriting(serial_manager_handle_t *handle)
{
    serial_manager_status_t status = kStatus_SerialManager_Error;
    serial_manager_write_handle_t *writeHandle =
        (serial_manager_write_handle_t *)LIST_GetHead(&handle->runningWriteHandleHead);

    if (writeHandle)
    {
        switch (handle->type)
        {
#if (defined(SERIAL_PORT_TYPE_UART) && (SERIAL_PORT_TYPE_UART > 0U))
            case kSerialPort_Uart:
                status = Serial_UartWrite(((serial_handle_t)&handle->lowLevelhandleBuffer[0]),
                                          writeHandle->transfer.buffer, writeHandle->transfer.length);
                break;
#endif
#if (defined(SERIAL_PORT_TYPE_USBCDC) && (SERIAL_PORT_TYPE_USBCDC > 0U))
            case kSerialPort_UsbCdc:
                status = Serial_UsbCdcWrite(((serial_handle_t)&handle->lowLevelhandleBuffer[0]),
                                            writeHandle->transfer.buffer, writeHandle->transfer.length);
                break;
#endif
#if (defined(SERIAL_PORT_TYPE_SWO) && (SERIAL_PORT_TYPE_SWO > 0U))
            case kSerialPort_Swo:
                status = Serial_SwoWrite(((serial_handle_t)&handle->lowLevelhandleBuffer[0]),
                                         writeHandle->transfer.buffer, writeHandle->transfer.length);
                break;
#endif
            default:
                break;
        }
    }
    return status;
}

#else

static serial_manager_status_t SerialManager_StartWriting(serial_manager_handle_t *handle,
                                                          serial_manager_write_handle_t *writeHandle,
                                                          uint8_t *buffer,
                                                          uint32_t length)
{
    serial_manager_status_t status = kStatus_SerialManager_Error;

    if (writeHandle)
    {
        switch (handle->type)
        {
#if (defined(SERIAL_PORT_TYPE_UART) && (SERIAL_PORT_TYPE_UART > 0U))
            case kSerialPort_Uart:
                status = Serial_UartWrite(((serial_handle_t)&handle->lowLevelhandleBuffer[0]), buffer, length);
                break;
#endif
#if (defined(SERIAL_PORT_TYPE_USBCDC) && (SERIAL_PORT_TYPE_USBCDC > 0U))
            case kSerialPort_UsbCdc:
                status = Serial_UsbCdcWrite(((serial_handle_t)&handle->lowLevelhandleBuffer[0]), buffer, length);
                break;
#endif
#if (defined(SERIAL_PORT_TYPE_SWO) && (SERIAL_PORT_TYPE_SWO > 0U))
            case kSerialPort_Swo:
                status = Serial_SwoWrite(((serial_handle_t)&handle->lowLevelhandleBuffer[0]), buffer, length);
                break;
#endif
            default:
                break;
        }
    }
    return status;
}

static serial_manager_status_t SerialManager_StartReading(serial_manager_handle_t *handle,
                                                          serial_manager_read_handle_t *readHandle,
                                                          uint8_t *buffer,
                                                          uint32_t length)
{
    serial_manager_status_t status = kStatus_SerialManager_Error;

    if (readHandle)
    {
        switch (handle->type)
        {
#if (defined(SERIAL_PORT_TYPE_UART) && (SERIAL_PORT_TYPE_UART > 0U))
            case kSerialPort_Uart:
                status = Serial_UartRead(((serial_handle_t)&handle->lowLevelhandleBuffer[0]), buffer, length);
                break;
#endif
#if (defined(SERIAL_PORT_TYPE_USBCDC) && (SERIAL_PORT_TYPE_USBCDC > 0U))
            case kSerialPort_UsbCdc:
                status = Serial_UsbCdcRead(((serial_handle_t)&handle->lowLevelhandleBuffer[0]), buffer, length);
                break;
#endif
#if (defined(SERIAL_PORT_TYPE_SWO) && (SERIAL_PORT_TYPE_SWO > 0U))
            case kSerialPort_Swo:
                status = Serial_SwoRead(((serial_handle_t)&handle->lowLevelhandleBuffer[0]), buffer, length);
                break;
#endif
            default:
                break;
        }
    }
    return status;
}
#endif

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
static void SerialManager_IsrFunction(serial_manager_handle_t *handle)
{
    uint32_t regPrimask = DisableGlobalIRQ();
    switch (handle->type)
    {
#if (defined(SERIAL_PORT_TYPE_UART) && (SERIAL_PORT_TYPE_UART > 0U))
        case kSerialPort_Uart:
            Serial_UartIsrFunction(((serial_handle_t)&handle->lowLevelhandleBuffer[0]));
            break;
#endif
#if (defined(SERIAL_PORT_TYPE_USBCDC) && (SERIAL_PORT_TYPE_USBCDC > 0U))
        case kSerialPort_UsbCdc:
            Serial_UsbCdcIsrFunction(((serial_handle_t)&handle->lowLevelhandleBuffer[0]));
            break;
#endif
#if (defined(SERIAL_PORT_TYPE_SWO) && (SERIAL_PORT_TYPE_SWO > 0U))
        case kSerialPort_Swo:
            Serial_SwoIsrFunction(((serial_handle_t)&handle->lowLevelhandleBuffer[0]));
            break;
#endif
        default:
            break;
    }
    EnableGlobalIRQ(regPrimask);
}

static void SerialManager_Task(void *param)
{
    serial_manager_handle_t *handle = (serial_manager_handle_t *)param;
    serial_manager_write_handle_t *serialWriteHandle;
    serial_manager_read_handle_t *serialReadHandle;
    serial_manager_callback_message_t msg;
    if (NULL != handle)
    {
#if defined(OSA_USED)

#if (defined(SERIAL_MANAGER_USE_COMMON_TASK) && (SERIAL_MANAGER_USE_COMMON_TASK > 0U))
#else
        osa_event_flags_t ev = 0;

        do
        {
            if (KOSA_StatusSuccess ==
                OSA_EventWait((osa_event_handle_t)handle->event, osaEventFlagsAll_c, false, osaWaitForever_c, &ev))
            {
                if (ev & SERIAL_EVENT_DATA_SENT)
#endif

#endif
        {
            serialWriteHandle = (serial_manager_write_handle_t *)LIST_GetHead(&handle->completedWriteHandleHead);
            while (NULL != serialWriteHandle)
            {
                SerialManager_RemoveHead(&handle->completedWriteHandleHead);
                msg.buffer = serialWriteHandle->transfer.buffer;
                msg.length = serialWriteHandle->transfer.soFar;
                serialWriteHandle->transfer.buffer = NULL;
                if (serialWriteHandle->callback)
                {
                    serialWriteHandle->callback(serialWriteHandle->callbackParam, &msg,
                                                serialWriteHandle->transfer.status);
                }
                serialWriteHandle = (serial_manager_write_handle_t *)LIST_GetHead(&handle->completedWriteHandleHead);
            }
        }
#if defined(OSA_USED)

#if (defined(SERIAL_MANAGER_USE_COMMON_TASK) && (SERIAL_MANAGER_USE_COMMON_TASK > 0U))
#else
                if (ev & SERIAL_EVENT_DATA_RECEIVED)
#endif

#endif
        {
            serialReadHandle = handle->openedReadHandleHead;
            if ((serialReadHandle) && (serialReadHandle->transfer.buffer) &&
                (serialReadHandle->transfer.soFar >= serialReadHandle->transfer.length))
            {
                msg.buffer = serialReadHandle->transfer.buffer;
                msg.length = serialReadHandle->transfer.soFar;
                serialReadHandle->transfer.buffer = NULL;
                if (serialReadHandle->callback)
                {
                    serialReadHandle->callback(serialReadHandle->callbackParam, &msg,
                                               serialReadHandle->transfer.status);
                }
            }
        }
#if defined(OSA_USED)

#if (defined(SERIAL_MANAGER_USE_COMMON_TASK) && (SERIAL_MANAGER_USE_COMMON_TASK > 0U))
#else
            }
        } while (gUseRtos_c);
#endif

#endif
    }
}
#endif

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
static void SerialManager_TxCallback(void *callbackParam,
                                     serial_manager_callback_message_t *message,
                                     serial_manager_status_t status)
{
    serial_manager_handle_t *handle;
    serial_manager_write_handle_t *writeHandle;

    assert(callbackParam);
    assert(message);

    handle = (serial_manager_handle_t *)callbackParam;

    writeHandle = (serial_manager_write_handle_t *)LIST_GetHead(&handle->runningWriteHandleHead);

    if (NULL != writeHandle)
    {
        SerialManager_RemoveHead(&handle->runningWriteHandleHead);
        SerialManager_StartWriting(handle);
        writeHandle->transfer.soFar = message->length;
        writeHandle->transfer.status = status;
        if (kSerialManager_TransmissionNonBlocking == writeHandle->transfer.mode)
        {
            SerialManager_AddTail(&handle->completedWriteHandleHead, writeHandle);
#if defined(OSA_USED)

#if (defined(SERIAL_MANAGER_USE_COMMON_TASK) && (SERIAL_MANAGER_USE_COMMON_TASK > 0U))
            handle->commontaskMsg.callback = SerialManager_Task;
            handle->commontaskMsg.callbackParam = handle;
            COMMON_TASK_post_message(&handle->commontaskMsg);
#else
            (void)OSA_EventSet((osa_event_handle_t)handle->event, SERIAL_EVENT_DATA_SENT);
#endif

#else
            SerialManager_Task(handle);
#endif
        }
        else
        {
            writeHandle->transfer.buffer = NULL;
        }
    }
}

static void SerialManager_RxCallback(void *callbackParam,
                                     serial_manager_callback_message_t *message,
                                     serial_manager_status_t status)
{
    serial_manager_handle_t *handle;
    uint32_t ringBufferLength;

    assert(callbackParam);
    assert(message);

    handle = (serial_manager_handle_t *)callbackParam;

    status = kStatus_SerialManager_Notify;

    for (int i = 0; i < message->length; i++)
    {
        handle->ringBuffer.ringBuffer[handle->ringBuffer.ringHead++] = message->buffer[i];
        if (handle->ringBuffer.ringHead >= handle->ringBuffer.ringBufferSize)
        {
            handle->ringBuffer.ringHead = 0U;
        }
        if (handle->ringBuffer.ringHead == handle->ringBuffer.ringTail)
        {
            status = kStatus_SerialManager_RingBufferOverflow;
            handle->ringBuffer.ringTail++;
            if (handle->ringBuffer.ringTail >= handle->ringBuffer.ringBufferSize)
            {
                handle->ringBuffer.ringTail = 0U;
            }
        }
    }

    ringBufferLength = handle->ringBuffer.ringHead + handle->ringBuffer.ringBufferSize - handle->ringBuffer.ringTail;
    ringBufferLength = ringBufferLength % handle->ringBuffer.ringBufferSize;

    if ((handle->openedReadHandleHead) && (handle->openedReadHandleHead->transfer.buffer))
    {
        if (handle->openedReadHandleHead->transfer.length > handle->openedReadHandleHead->transfer.soFar)
        {
            int remainLength =
                handle->openedReadHandleHead->transfer.length - handle->openedReadHandleHead->transfer.soFar;
            for (int i = 0; i < MIN(ringBufferLength, remainLength); i++)
            {
                handle->openedReadHandleHead->transfer.buffer[handle->openedReadHandleHead->transfer.soFar] =
                    handle->ringBuffer.ringBuffer[handle->ringBuffer.ringTail];
                handle->ringBuffer.ringTail++;
                handle->openedReadHandleHead->transfer.soFar++;
                if (handle->ringBuffer.ringTail >= handle->ringBuffer.ringBufferSize)
                {
                    handle->ringBuffer.ringTail = 0U;
                }
            }
            ringBufferLength = ringBufferLength - MIN(ringBufferLength, remainLength);
        }

        if (handle->openedReadHandleHead->transfer.length > handle->openedReadHandleHead->transfer.soFar)
        {
        }
        else
        {
            if (kSerialManager_TransmissionBlocking == handle->openedReadHandleHead->transfer.mode)
            {
                handle->openedReadHandleHead->transfer.buffer = NULL;
            }
            else
            {
                handle->openedReadHandleHead->transfer.status = kStatus_SerialManager_Success;

#if defined(OSA_USED)

#if (defined(SERIAL_MANAGER_USE_COMMON_TASK) && (SERIAL_MANAGER_USE_COMMON_TASK > 0U))
                handle->commontaskMsg.callback = SerialManager_Task;
                handle->commontaskMsg.callbackParam = handle;
                COMMON_TASK_post_message(&handle->commontaskMsg);
#else
                (void)OSA_EventSet((osa_event_handle_t)handle->event, SERIAL_EVENT_DATA_RECEIVED);
#endif

#else
                SerialManager_Task(handle);
#endif
            }
        }
    }

    if (ringBufferLength)
    {
        message->buffer = NULL;
        message->length = ringBufferLength;
        if ((NULL != handle->openedReadHandleHead->callback))
        {
            handle->openedReadHandleHead->callback(handle->openedReadHandleHead->callbackParam, message, status);
        }
    }
}

static serial_manager_status_t SerialManager_Write(serial_write_handle_t writeHandle,
                                                   uint8_t *buffer,
                                                   uint32_t length,
                                                   serial_manager_transmission_mode_t mode)
{
    serial_manager_write_handle_t *serialWriteHandle;
    serial_manager_handle_t *handle;
    serial_manager_status_t status = kStatus_SerialManager_Success;
    uint32_t primask;
    uint8_t isEmpty = 0U;

    assert(writeHandle);
    assert(buffer);
    assert(length);

    serialWriteHandle = (serial_manager_write_handle_t *)writeHandle;
    handle = serialWriteHandle->serialManagerHandle;

    assert(handle);
    assert(SERIAL_MANAGER_WRITE_TAG == serialWriteHandle->tag);
    assert(!((kSerialManager_TransmissionNonBlocking == mode) && (NULL == serialWriteHandle->callback)));

    primask = DisableGlobalIRQ();
    if (serialWriteHandle->transfer.buffer)
    {
        EnableGlobalIRQ(primask);
        return kStatus_SerialManager_Busy;
    }
    serialWriteHandle->transfer.buffer = buffer;
    serialWriteHandle->transfer.length = length;
    serialWriteHandle->transfer.soFar = 0U;
    serialWriteHandle->transfer.mode = mode;

    if (NULL == LIST_GetHead(&handle->runningWriteHandleHead))
    {
        isEmpty = 1U;
    }
    SerialManager_AddTail(&handle->runningWriteHandleHead, serialWriteHandle);
    EnableGlobalIRQ(primask);

    if (isEmpty)
    {
        status = SerialManager_StartWriting(handle);
        if (kStatus_SerialManager_Success != status)
        {
            return status;
        }
    }

    if (kSerialManager_TransmissionBlocking == mode)
    {
        while (serialWriteHandle->transfer.length > serialWriteHandle->transfer.soFar)
        {
#if defined(__GIC_PRIO_BITS)
            if ((__get_CPSR() & CPSR_M_Msk) == 0x13)
#else
            if (__get_IPSR())
#endif
            {
                SerialManager_IsrFunction(handle);
            }
        }
    }
    return kStatus_SerialManager_Success;
}

static serial_manager_status_t SerialManager_Read(serial_read_handle_t readHandle,
                                                  uint8_t *buffer,
                                                  uint32_t length,
                                                  serial_manager_transmission_mode_t mode,
                                                  uint32_t *receivedLength)
{
    serial_manager_read_handle_t *serialReadHandle;
    serial_manager_handle_t *handle;
    uint32_t dataLength;
    uint32_t primask;

    assert(readHandle);
    assert(buffer);
    assert(length);

    serialReadHandle = (serial_manager_read_handle_t *)readHandle;
    handle = serialReadHandle->serialManagerHandle;

    assert(handle);
    assert(SERIAL_MANAGER_READ_TAG == serialReadHandle->tag);
    assert(!((kSerialManager_TransmissionNonBlocking == mode) && (NULL == serialReadHandle->callback)));

    primask = DisableGlobalIRQ();
    if (serialReadHandle->transfer.buffer)
    {
        EnableGlobalIRQ(primask);
        return kStatus_SerialManager_Busy;
    }
    serialReadHandle->transfer.buffer = buffer;
    serialReadHandle->transfer.length = length;
    serialReadHandle->transfer.soFar = 0U;
    serialReadHandle->transfer.mode = mode;

    dataLength = handle->ringBuffer.ringHead + handle->ringBuffer.ringBufferSize - handle->ringBuffer.ringTail;
    dataLength = dataLength % handle->ringBuffer.ringBufferSize;

    for (; serialReadHandle->transfer.soFar < MIN(dataLength, length); serialReadHandle->transfer.soFar++)
    {
        buffer[serialReadHandle->transfer.soFar] = handle->ringBuffer.ringBuffer[handle->ringBuffer.ringTail];
        handle->ringBuffer.ringTail++;
        if (handle->ringBuffer.ringTail >= handle->ringBuffer.ringBufferSize)
        {
            handle->ringBuffer.ringTail = 0U;
        }
    }
    EnableGlobalIRQ(primask);

    if (receivedLength)
    {
        *receivedLength = serialReadHandle->transfer.soFar;
        serialReadHandle->transfer.buffer = NULL;
    }
    else
    {
        if (serialReadHandle->transfer.soFar >= serialReadHandle->transfer.length)
        {
            serialReadHandle->transfer.buffer = NULL;
            if (kSerialManager_TransmissionNonBlocking == mode)
            {
                if (serialReadHandle->callback)
                {
                    serial_manager_callback_message_t msg;
                    msg.buffer = buffer;
                    msg.length = serialReadHandle->transfer.soFar;
                    serialReadHandle->callback(serialReadHandle->callbackParam, &msg, kStatus_SerialManager_Success);
                }
            }
        }

        if (kSerialManager_TransmissionBlocking == mode)
        {
            while (serialReadHandle->transfer.length > serialReadHandle->transfer.soFar)
            {
            }
        }
    }

    return kStatus_SerialManager_Success;
}

#else

static serial_manager_status_t SerialManager_Write(serial_write_handle_t writeHandle, uint8_t *buffer, uint32_t length)
{
    serial_manager_write_handle_t *serialWriteHandle;
    serial_manager_handle_t *handle;

    assert(writeHandle);
    assert(buffer);
    assert(length);

    serialWriteHandle = (serial_manager_write_handle_t *)writeHandle;
    handle = serialWriteHandle->serialManagerHandle;

    assert(handle);

    return SerialManager_StartWriting(handle, serialWriteHandle, buffer, length);
}

static serial_manager_status_t SerialManager_Read(serial_read_handle_t readHandle, uint8_t *buffer, uint32_t length)
{
    serial_manager_read_handle_t *serialReadHandle;
    serial_manager_handle_t *handle;

    assert(readHandle);
    assert(buffer);
    assert(length);

    serialReadHandle = (serial_manager_read_handle_t *)readHandle;
    handle = serialReadHandle->serialManagerHandle;

    assert(handle);

    return SerialManager_StartReading(handle, serialReadHandle, buffer, length);
}
#endif

serial_manager_status_t SerialManager_Init(serial_handle_t serialHandle, serial_manager_config_t *config)
{
    serial_manager_handle_t *handle;
    serial_manager_status_t status = kStatus_SerialManager_Error;

    assert(config);
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    assert(config->ringBuffer);
    assert(config->ringBufferSize);
#endif
    assert(serialHandle);
    if (SERIAL_MANAGER_HANDLE_SIZE < sizeof(serial_manager_handle_t))
    {
        return kStatus_SerialManager_Error;
    }

    handle = (serial_manager_handle_t *)serialHandle;

    memset(handle, 0, SERIAL_MANAGER_HANDLE_SIZE);

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))

#if defined(OSA_USED)

#if (defined(SERIAL_MANAGER_USE_COMMON_TASK) && (SERIAL_MANAGER_USE_COMMON_TASK > 0U))

    COMMON_TASK_init();

#else
    if (KOSA_StatusSuccess != OSA_EventCreate((osa_event_handle_t)handle->event, true))
    {
        return kStatus_SerialManager_Error;
    }

    if (KOSA_StatusSuccess != OSA_TaskCreate((osa_task_handle_t)handle->taskId, OSA_TASK(SerialManager_Task), handle))
    {
        return kStatus_SerialManager_Error;
    }
#endif

#endif

#endif

    handle->type = config->type;

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    handle->ringBuffer.ringBuffer = config->ringBuffer;
    handle->ringBuffer.ringBufferSize = config->ringBufferSize;
#endif

    switch (config->type)
    {
#if (defined(SERIAL_PORT_TYPE_UART) && (SERIAL_PORT_TYPE_UART > 0U))
        case kSerialPort_Uart:
            status = Serial_UartInit(((serial_handle_t)&handle->lowLevelhandleBuffer[0]), config->portConfig);
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
            if (kStatus_SerialManager_Success == status)
            {
                status = Serial_UartInstallTxCallback(((serial_handle_t)&handle->lowLevelhandleBuffer[0]),
                                                      SerialManager_TxCallback, handle);
                if (kStatus_SerialManager_Success == status)
                {
                    status = Serial_UartInstallRxCallback(((serial_handle_t)&handle->lowLevelhandleBuffer[0]),
                                                          SerialManager_RxCallback, handle);
                }
            }
#endif
            break;
#endif
#if (defined(SERIAL_PORT_TYPE_USBCDC) && (SERIAL_PORT_TYPE_USBCDC > 0U))
        case kSerialPort_UsbCdc:
            status = Serial_UsbCdcInit(((serial_handle_t)&handle->lowLevelhandleBuffer[0]), config->portConfig);
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
            if (kStatus_SerialManager_Success == status)
            {
                status = Serial_UsbCdcInstallTxCallback(((serial_handle_t)&handle->lowLevelhandleBuffer[0]),
                                                        SerialManager_TxCallback, handle);
                if (kStatus_SerialManager_Success == status)
                {
                    status = Serial_UsbCdcInstallRxCallback(((serial_handle_t)&handle->lowLevelhandleBuffer[0]),
                                                            SerialManager_RxCallback, handle);
                }
            }
#endif
            break;
#endif
#if (defined(SERIAL_PORT_TYPE_SWO) && (SERIAL_PORT_TYPE_SWO > 0U))
        case kSerialPort_Swo:
            status = Serial_SwoInit(((serial_handle_t)&handle->lowLevelhandleBuffer[0]), config->portConfig);
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
            if (kStatus_SerialManager_Success == status)
            {
                status = Serial_SwoInstallTxCallback(((serial_handle_t)&handle->lowLevelhandleBuffer[0]),
                                                     SerialManager_TxCallback, handle);
            }
#endif
            break;
#endif
        default:
            break;
    }

    return status;
}

serial_manager_status_t SerialManager_Deinit(serial_handle_t serialHandle)
{
    serial_manager_handle_t *handle;

    assert(serialHandle);

    handle = (serial_manager_handle_t *)serialHandle;

    if ((handle->openedReadHandleHead) || (handle->openedWriteHandleCount))
    {
        return kStatus_SerialManager_Busy;
    }

    switch (handle->type)
    {
#if (defined(SERIAL_PORT_TYPE_UART) && (SERIAL_PORT_TYPE_UART > 0U))
        case kSerialPort_Uart:
            Serial_UartDeinit(((serial_handle_t)&handle->lowLevelhandleBuffer[0]));
            break;
#endif
#if (defined(SERIAL_PORT_TYPE_USBCDC) && (SERIAL_PORT_TYPE_USBCDC > 0U))
        case kSerialPort_UsbCdc:
            Serial_UsbCdcDeinit(((serial_handle_t)&handle->lowLevelhandleBuffer[0]));
            break;
#endif
#if (defined(SERIAL_PORT_TYPE_SWO) && (SERIAL_PORT_TYPE_SWO > 0U))
        case kSerialPort_Swo:
            Serial_SwoDeinit(((serial_handle_t)&handle->lowLevelhandleBuffer[0]));
            break;
#endif
        default:
            break;
    }
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))

#if defined(OSA_USED)

#if (defined(SERIAL_MANAGER_USE_COMMON_TASK) && (SERIAL_MANAGER_USE_COMMON_TASK > 0U))
#else
    OSA_EventDestroy((osa_event_handle_t)handle->event);
    OSA_TaskDestroy((osa_task_handle_t)handle->taskId);
#endif

#endif

#endif

    return kStatus_SerialManager_Success;
}

serial_manager_status_t SerialManager_OpenWriteHandle(serial_handle_t serialHandle, serial_write_handle_t writeHandle)
{
    serial_manager_handle_t *handle;
    serial_manager_write_handle_t *serialWriteHandle;

    assert(serialHandle);
    assert(writeHandle);
    if (SERIAL_MANAGER_WRITE_HANDLE_SIZE < sizeof(serial_manager_write_handle_t))
    {
        return kStatus_SerialManager_Error;
    }
    handle = (serial_manager_handle_t *)serialHandle;
    serialWriteHandle = (serial_manager_write_handle_t *)writeHandle;

    memset(writeHandle, 0, SERIAL_MANAGER_WRITE_HANDLE_SIZE);

    handle->openedWriteHandleCount++;

    serialWriteHandle->serialManagerHandle = handle;
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    serialWriteHandle->tag = SERIAL_MANAGER_WRITE_TAG;
#endif

    return kStatus_SerialManager_Success;
}

serial_manager_status_t SerialManager_CloseWriteHandle(serial_write_handle_t writeHandle)
{
    serial_manager_handle_t *handle;
    serial_manager_write_handle_t *serialWriteHandle;

    assert(writeHandle);

    serialWriteHandle = (serial_manager_write_handle_t *)writeHandle;
    handle = (serial_manager_handle_t *)serialWriteHandle->serialManagerHandle;

    assert(handle);
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    assert(SERIAL_MANAGER_WRITE_TAG == serialWriteHandle->tag);
#endif

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    SerialManager_CancelWriting(writeHandle);
#endif

    handle->openedWriteHandleCount--;
    memset(writeHandle, 0, SERIAL_MANAGER_WRITE_HANDLE_SIZE);

    return kStatus_SerialManager_Success;
}

serial_manager_status_t SerialManager_OpenReadHandle(serial_handle_t serialHandle, serial_read_handle_t readHandle)
{
    serial_manager_handle_t *handle;
    serial_manager_read_handle_t *serialReadHandle;

    assert(serialHandle);
    assert(readHandle);
    if (SERIAL_MANAGER_READ_HANDLE_SIZE < sizeof(serial_manager_read_handle_t))
    {
        return kStatus_SerialManager_Error;
    }
    handle = (serial_manager_handle_t *)serialHandle;
    serialReadHandle = (serial_manager_read_handle_t *)readHandle;

    if (handle->openedReadHandleHead)
    {
        return kStatus_SerialManager_Busy;
    }
    memset(readHandle, 0, SERIAL_MANAGER_READ_HANDLE_SIZE);

    handle->openedReadHandleHead = serialReadHandle;

    serialReadHandle->serialManagerHandle = handle;
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    serialReadHandle->tag = SERIAL_MANAGER_READ_TAG;
#endif

    return kStatus_SerialManager_Success;
}

serial_manager_status_t SerialManager_CloseReadHandle(serial_read_handle_t readHandle)
{
    serial_manager_handle_t *handle;
    serial_manager_read_handle_t *serialReadHandle;

    assert(readHandle);

    serialReadHandle = (serial_manager_read_handle_t *)readHandle;
    handle = (serial_manager_handle_t *)serialReadHandle->serialManagerHandle;

    assert(handle);
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    assert(SERIAL_MANAGER_READ_TAG == serialReadHandle->tag);
#endif

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    SerialManager_CancelReading(readHandle);
#endif

    handle->openedReadHandleHead = NULL;
    memset(readHandle, 0, SERIAL_MANAGER_READ_HANDLE_SIZE);

    return kStatus_SerialManager_Success;
}

serial_manager_status_t SerialManager_WriteBlocking(serial_write_handle_t writeHandle, uint8_t *buffer, uint32_t length)
{
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    return SerialManager_Write(writeHandle, buffer, length, kSerialManager_TransmissionBlocking);
#else
    return SerialManager_Write(writeHandle, buffer, length);
#endif
}

serial_manager_status_t SerialManager_ReadBlocking(serial_read_handle_t readHandle, uint8_t *buffer, uint32_t length)
{
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    return SerialManager_Read(readHandle, buffer, length, kSerialManager_TransmissionBlocking, NULL);
#else
    return SerialManager_Read(readHandle, buffer, length);
#endif
}

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
serial_manager_status_t SerialManager_WriteNonBlocking(serial_write_handle_t writeHandle,
                                                       uint8_t *buffer,
                                                       uint32_t length)
{
    return SerialManager_Write(writeHandle, buffer, length, kSerialManager_TransmissionNonBlocking);
}

serial_manager_status_t SerialManager_ReadNonBlocking(serial_read_handle_t readHandle, uint8_t *buffer, uint32_t length)
{
    return SerialManager_Read(readHandle, buffer, length, kSerialManager_TransmissionNonBlocking, NULL);
}

serial_manager_status_t SerialManager_CancelWriting(serial_write_handle_t writeHandle)
{
    serial_manager_write_handle_t *serialWriteHandle;
    uint32_t primask;
    uint8_t isNotUsed = 0;

    assert(writeHandle);

    serialWriteHandle = (serial_manager_write_handle_t *)writeHandle;

    assert(serialWriteHandle->serialManagerHandle);
    assert(SERIAL_MANAGER_WRITE_TAG == serialWriteHandle->tag);

    if ((serialWriteHandle->transfer.buffer) &&
        (kSerialManager_TransmissionBlocking == serialWriteHandle->transfer.mode))
    {
        return kStatus_SerialManager_Error;
    }

    primask = DisableGlobalIRQ();
    if (serialWriteHandle !=
        (serial_manager_write_handle_t *)LIST_GetHead(&serialWriteHandle->serialManagerHandle->runningWriteHandleHead))
    {
        LIST_RemoveElement(&serialWriteHandle->link);
        isNotUsed = 1;
    }
    EnableGlobalIRQ(primask);

    if (isNotUsed)
    {
        serialWriteHandle->transfer.soFar = 0;
        serialWriteHandle->transfer.status = kStatus_SerialManager_Canceled;

        SerialManager_AddTail(&serialWriteHandle->serialManagerHandle->completedWriteHandleHead, serialWriteHandle);
#if defined(OSA_USED)

#if (defined(SERIAL_MANAGER_USE_COMMON_TASK) && (SERIAL_MANAGER_USE_COMMON_TASK > 0U))
        serialWriteHandle->serialManagerHandle->commontaskMsg.callback = SerialManager_Task;
        serialWriteHandle->serialManagerHandle->commontaskMsg.callbackParam = serialWriteHandle->serialManagerHandle;
        COMMON_TASK_post_message(&serialWriteHandle->serialManagerHandle->commontaskMsg);
#else
        (void)OSA_EventSet((osa_event_handle_t)serialWriteHandle->serialManagerHandle->event, SERIAL_EVENT_DATA_SENT);
#endif

#else
        SerialManager_Task(serialWriteHandle->serialManagerHandle);
#endif
    }
    else
    {
        switch (serialWriteHandle->serialManagerHandle->type)
        {
#if (defined(SERIAL_PORT_TYPE_UART) && (SERIAL_PORT_TYPE_UART > 0U))
            case kSerialPort_Uart:
                Serial_UartCancelWrite(
                    ((serial_handle_t)&serialWriteHandle->serialManagerHandle->lowLevelhandleBuffer[0]));
                break;
#endif
#if (defined(SERIAL_PORT_TYPE_USBCDC) && (SERIAL_PORT_TYPE_USBCDC > 0U))
            case kSerialPort_UsbCdc:
                Serial_UsbCdcCancelWrite(
                    ((serial_handle_t)&serialWriteHandle->serialManagerHandle->lowLevelhandleBuffer[0]));
                break;
#endif
#if (defined(SERIAL_PORT_TYPE_SWO) && (SERIAL_PORT_TYPE_SWO > 0U))
            case kSerialPort_Swo:
                Serial_SwoCancelWrite(
                    ((serial_handle_t)&serialWriteHandle->serialManagerHandle->lowLevelhandleBuffer[0]));
                break;
#endif
            default:
                break;
        }
    }

    SerialManager_StartWriting(serialWriteHandle->serialManagerHandle);

    return kStatus_SerialManager_Success;
}

serial_manager_status_t SerialManager_CancelReading(serial_read_handle_t readHandle)
{
    serial_manager_read_handle_t *serialReadHandle;
    serial_manager_callback_message_t msg;
    uint8_t *buffer;
    uint32_t primask;

    assert(readHandle);

    serialReadHandle = (serial_manager_read_handle_t *)readHandle;

    assert(SERIAL_MANAGER_READ_TAG == serialReadHandle->tag);

    if ((serialReadHandle->transfer.buffer) && (kSerialManager_TransmissionBlocking == serialReadHandle->transfer.mode))
    {
        return kStatus_SerialManager_Error;
    }

    primask = DisableGlobalIRQ();
    buffer = serialReadHandle->transfer.buffer;
    serialReadHandle->transfer.buffer = NULL;
    serialReadHandle->transfer.length = 0;
    msg.buffer = buffer;
    msg.length = serialReadHandle->transfer.soFar;
    EnableGlobalIRQ(primask);

    if (buffer)
    {
        if (serialReadHandle->callback)
        {
            serialReadHandle->callback(serialReadHandle->callbackParam, &msg, kStatus_SerialManager_Canceled);
        }
    }
    return kStatus_SerialManager_Success;
}

serial_manager_status_t SerialManager_TryRead(serial_read_handle_t readHandle,
                                              uint8_t *buffer,
                                              uint32_t length,
                                              uint32_t *receivedLength)
{
    assert(receivedLength);

    return SerialManager_Read(readHandle, buffer, length, kSerialManager_TransmissionBlocking, receivedLength);
}

serial_manager_status_t SerialManager_InstallTxCallback(serial_write_handle_t writeHandle,
                                                        serial_manager_callback_t callback,
                                                        void *callbackParam)
{
    serial_manager_write_handle_t *serialWriteHandle;

    assert(writeHandle);

    serialWriteHandle = (serial_manager_write_handle_t *)writeHandle;

    assert(SERIAL_MANAGER_WRITE_TAG == serialWriteHandle->tag);

    serialWriteHandle->callbackParam = callbackParam;
    serialWriteHandle->callback = callback;

    return kStatus_SerialManager_Success;
}

serial_manager_status_t SerialManager_InstallRxCallback(serial_read_handle_t readHandle,
                                                        serial_manager_callback_t callback,
                                                        void *callbackParam)
{
    serial_manager_read_handle_t *serialReadHandle;

    assert(readHandle);

    serialReadHandle = (serial_manager_read_handle_t *)readHandle;

    assert(SERIAL_MANAGER_READ_TAG == serialReadHandle->tag);

    serialReadHandle->callbackParam = callbackParam;
    serialReadHandle->callback = callback;

    return kStatus_SerialManager_Success;
}
#endif

serial_manager_status_t SerialManager_EnterLowpower(serial_handle_t serialHandle)
{
    assert(serialHandle);

    return kStatus_SerialManager_Success;
}

serial_manager_status_t SerialManager_ExitLowpower(serial_handle_t serialHandle)
{
    assert(serialHandle);

    return kStatus_SerialManager_Success;
}

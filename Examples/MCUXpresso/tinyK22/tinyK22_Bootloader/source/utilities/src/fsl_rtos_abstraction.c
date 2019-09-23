/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "utilities/fsl_assert.h"
#include "bootloader/bl_peripheral_interface.h"
#include "utilities/fsl_rtos_abstraction.h"
#include "fsl_device_registers.h"
#include "microseconds.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

enum _sync_constants
{
    kSyncUnlocked = 0,
    kSyncLocked = 1
};

static lock_object_t lockObject;

static uint64_t s_ticksPerMs = 0;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

/*FUNCTION**********************************************************************
 *
 * Function Name : time_diff
 * Description   : This function gets the difference between two time stamp,
 * time overflow is considered.
 *
 *END**************************************************************************/
static uint32_t ms_diff(uint64_t tickStart, uint64_t tickStop)
{
    return ((tickStop - tickStart) / s_ticksPerMs);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_SemaCreate
 * Description   : This function is used to create a semaphore. Return
 * kStatus_OSA_Success if create successfully, otherwise return kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_SemaCreate(semaphore_t *pSem, uint8_t initValue)
{
    assert(pSem);

    if (!s_ticksPerMs)
    {
        s_ticksPerMs = microseconds_convert_to_ticks(1000);
    }

    pSem->semCount = initValue;
    pSem->isWaiting = false;
    pSem->tickStart = 0u;
    pSem->timeout = 0u;

    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_SemaWait
 * Description   : This function checks the semaphore's counting value, if it is
 * positive, decreases it and returns kStatus_OSA_Success, otherwise, timeout
 * will be used for wait. The parameter timeout indicates how long should wait
 * in milliseconds. Pass kSyncWaitForever to wait indefinitely, pass 0 will
 * return kStatus_OSA_Timeout immediately if semaphore is not positive.
 * This function returns kStatus_OSA_Success if the semaphore is received, returns
 * kStatus_OSA_Timeout if the semaphore is not received within the specified
 * 'timeout', returns kStatus_OSA_Error if any errors occur during waiting,
 * returns kStatus_OSA_Idle if the semaphore is not available and 'timeout' is
 * not exhausted, because wait functions should not block with bare metal.
 *
 *END**************************************************************************/
osa_status_t OSA_SemaWait(semaphore_t *pSem, uint32_t timeout)
{
    uint64_t currentTicks;

    assert(pSem);

    /* Check the sem count first. Deal with timeout only if not already set */
    if (pSem->semCount)
    {
        __disable_irq();
        pSem->semCount--;
        pSem->isWaiting = false;
        __enable_irq();
        return kStatus_OSA_Success;
    }
    else
    {
        if (timeout == 0)
        {
            /* If timeout is 0 and semaphore is not available, return kStatus_OSA_Timeout. */
            return kStatus_OSA_Timeout;
        }
        else if (pSem->isWaiting)
        {
            /* Check for timeout */
            currentTicks = microseconds_get_ticks();
            if (pSem->timeout < ms_diff(pSem->tickStart, currentTicks))
            {
                __disable_irq();
                pSem->isWaiting = false;
                __enable_irq();
                return kStatus_OSA_Timeout;
            }
        }
        else if (timeout != kSyncWaitForever) /* If don't wait forever, start the timer */
        {
            /* Start the timeout counter */
            __disable_irq();
            pSem->isWaiting = true;
            __enable_irq();
            pSem->tickStart = microseconds_get_ticks();
            pSem->timeout = timeout;
        }
    }

    return kStatus_OSA_Idle;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_SemaPost
 * Description   : This function is used to wake up one task that wating on the
 * semaphore. If no task is waiting, increase the semaphore. The function returns
 * kStatus_OSA_Success if the semaphre is post successfully, otherwise returns
 * kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_SemaPost(semaphore_t *pSem)
{
    assert(pSem);
    /* The max value is 0xFF */
    if (pSem->semCount == 0xFF)
    {
        return kStatus_OSA_Error;
    }
    __disable_irq();
    ++pSem->semCount;
    __enable_irq();

    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_SemaDestroy
 * Description   : This function is used to destroy a semaphore.
 * Return kStatus_OSA_Success if the semaphore is destroyed successfully, otherwise
 * return kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_SemaDestroy(semaphore_t *pSem)
{
    assert(pSem);

    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TimeDelay
 * Description   : This function is used to delay for a number of milliseconds.
 *
 *END**************************************************************************/
void OSA_TimeDelay(uint32_t delay)
{
    microseconds_delay(delay * 1000);
}

void sync_init(sync_object_t *obj, bool state)
{
    *obj = state ? kSyncLocked : kSyncUnlocked;
}

bool sync_wait(sync_object_t *obj, uint32_t timeout)
{
    // Increment the object so we can tell if it changes. Because the increment is not
    // atomic (load, add, store), we must disabled interrupts during it.
    __disable_irq();
    ++(*obj);
    __enable_irq();

    // Wait for the object to be unlocked.
    while (*obj != 0)
    {
        // Spin.
    }

    return true;
}

void sync_signal(sync_object_t *obj)
{
    // Atomically unlock the object.
    __disable_irq();
    --(*obj);
    __enable_irq();
}

void sync_reset(sync_object_t *obj)
{
    __disable_irq();
    (*obj) = 0;
    __enable_irq();
}

void lock_init(void)
{
    __disable_irq();
    lockObject = 0;
    __enable_irq();
}

void lock_acquire(void)
{
    // Disable global IRQ until lock_release() is called.
    __disable_irq();
    ++lockObject;
}

void lock_release(void)
{
    // Restore previous state, enable global IRQ if all locks released.
    if (lockObject <= 1)
    {
        lockObject = 0;
        __enable_irq();
    }
    else
    {
        --lockObject;
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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

#include <assert.h>
#include "fsl_os_abstraction.h"
#include "fsl_interrupt_manager.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : sync_create
 * Description   : This function is used to create a sync object. Return
 * kSuccess if create successfully, otherwise return kError.
 *
 *END**************************************************************************/
fsl_rtos_status sync_create(sync_object_t *obj, uint8_t initValue)
{
    obj->timerId = sw_timer_reserve_channel();

    if (kSwTimerChannelNotAvailable == obj->timerId)
    {
        return kError;
    }

    obj->semCount = initValue;
    obj->isWaiting = false;

    return kSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : sync_wait
 * Description   : This function is used to wait a sync object to be signaled.
 * Pass the #kSyncWaitForever constant to wait indefinitely for someone to
 * signal the object. 0 should not be passed to this function.
 * Return kSuccess if the sync object is signaled before the timeout is exhausted,
 * return kTimeout if the sync object has not been signaled  before the timeout
 * is exhausted, return kError if the parameter is valid, return kIdle if the
 * sync object is not signaled.
 *
 *END**************************************************************************/
fsl_rtos_status sync_wait(sync_object_t *obj, uint32_t timeout)
{
    fsl_rtos_status retVal = kIdle;
    uint32_t status;

    /* Check the sem count first. Deal with timeout only if not already set */
    if(obj->semCount)
    {
        interrupt_disable_global();
        obj->semCount --;
        obj->isWaiting = false;
        interrupt_enable_global();
        retVal = kSuccess;
    }
    else
    {
        if(obj->isWaiting)
        {
            /* Check for timeout */
            status = sw_timer_get_channel_status(obj->timerId);
            if(status == kSwTimerChannelExpired)
            {
                interrupt_disable_global();
                obj->isWaiting = false;
                interrupt_enable_global();
                retVal = kTimeout;
            }
        }
        else if(timeout != kSyncWaitForever)    /* If no timeout, don't start the timer */
        {
            /* Start the timeout counter */
            interrupt_disable_global();
            obj->isWaiting = true;
            interrupt_enable_global();
            sw_timer_start_channel(obj->timerId, timeout);
        }
    }
    
    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : sync_poll
 * Description   : This function is used to poll a sync object's status.
 * If the sync object is signaled, this function will return kSuccess and set
 * the object un-signaled. If the object is not signaled, the function will
 * return kIdle immediately.
 *
 *END**************************************************************************/
fsl_rtos_status sync_poll(sync_object_t *obj)
{
    fsl_rtos_status retVal;
        
    /* Always check for the event first. Deal with timeout only if not already set */
    if(obj->semCount)
    {
        /* Event set. Clear it and return success */
        interrupt_disable_global();
        obj->semCount --;
        obj->isWaiting = false;
        interrupt_enable_global();
        retVal = kSuccess;
    }
    else
    {
        retVal = kIdle;
    }
    
    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : sync_signal
 * Description   : This function is used to signal a sync object.
 * Return kSuccess if the sync object is signaled successfully, otherwise
 * return kError.
 * This function should not be called from isr.
 *
 *END**************************************************************************/
fsl_rtos_status sync_signal(sync_object_t *obj)
{
    /* The max value is 0xFF */
    if (0xFF == obj->semCount)
    {
        return kError;
    }
    interrupt_disable_global();
    ++obj->semCount;
    interrupt_enable_global();
    
    return kSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : sync_signal_from_isr
 * Description   : This function is used to signal a sync object.
 * Return kSuccess if the sync object is signaled successfully, otherwise
 * return kError.
 * This function should be called from isr only.
 *
 *END**************************************************************************/
fsl_rtos_status sync_signal_from_isr(sync_object_t *obj)
{
    /* The max value is 0xFF */
    if (0xFF == obj->semCount)
    {
        return kError;
    }
    ++obj->semCount;
    
    return kSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : sync_destroy
 * Description   : This function is used to destroy a sync object.
 * Return kSuccess if the sync object is destroyed successfully, otherwise 
 * return kError.
 *
 *END**************************************************************************/
fsl_rtos_status sync_destroy(sync_object_t *obj)
{
    uint32_t status;
  
    status = sw_timer_release_channel(obj->timerId);
    
    if(status == kSwTimerStatusSuccess)
    {
        return kSuccess;
    }
    else
    {
        return kError;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : lock_create
 * Description   : This function is used to create a lock object.
 * Return kSuccess if create successfully, otherwise return kError.
 *
 *END**************************************************************************/
fsl_rtos_status lock_create(lock_object_t *obj)
{
    obj->timerId = sw_timer_reserve_channel();

    if (kSwTimerChannelNotAvailable == obj->timerId)
    {
        return kError;
    }

    obj->isLocked = false;
    obj->isWaiting = false;
    
    return kSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : lock_wait
 * Description   : This function is used to wait to obtain a lock object.
 * Pass the #kSyncWaitForever constant to wait indefinitely for someone to
 * unlock the object. A value of 0 should not be passed to this function.
 * Return kSuccess if the lock object is obtained before the timeout is exhausted,
 * return kTimeout if has not obtained the lock object before the timeout
 * is exhausted, return kError if the parameter is valid, return kIdle if lock
 * is not available, this is for non-blocking mechanism.
 *
 *END**************************************************************************/
fsl_rtos_status lock_wait(lock_object_t *obj, uint32_t timeout)
{
    fsl_rtos_status retVal;
    uint32_t status;
    
    /* Always check for the event first. Deal with timeout only if not already set */
    if(obj->isLocked == false)
    {
        /* Get the lock and return success */
        interrupt_disable_global();
        obj->isLocked = true;
        obj->isWaiting = false;
        interrupt_enable_global();
        retVal = kSuccess;
    }
    else
    {
        retVal = kIdle;
        
        if(obj->isWaiting)
        {
            /* Check for timeout */
            status = sw_timer_get_channel_status(obj->timerId);
            if(status == kSwTimerChannelExpired)
            {
                interrupt_disable_global();
                obj->isWaiting = false;
                interrupt_enable_global();
                retVal = kTimeout;
            }
        }
        else if(timeout != kSyncWaitForever)    /* If no timeout, don't start the timer */
        {
            /* Start the timeout counter */
            interrupt_disable_global();
            obj->isWaiting = true;
            interrupt_enable_global();
            sw_timer_start_channel(obj->timerId, timeout);
        }
    }
    
    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : lock_poll
 * Description   : This function is used to poll a lock object's status.
 * If the lock object is unlocked, this function will return kSuccess and lock
 * the object. If lock is unavailable, return kIdle.
 *
 *END**************************************************************************/
fsl_rtos_status lock_poll(lock_object_t *obj)
{
    fsl_rtos_status retVal;
        
    /* Always check first. Deal with timeout only if not already set */
    if(obj->isLocked == false)
    {
        /* Lock the object and return success */
        interrupt_disable_global();
        obj->isLocked = true;
        obj->isWaiting = false;
        interrupt_enable_global();
        retVal = kSuccess;
    }
    else
    {
        retVal = kIdle;
    }
    
    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : lock_release
 * Description   : This function is used to unlock a lock object.
 * Return kSuccess if the lock object is unlocked successfully, otherwise
 * return kError.
 *
 *END**************************************************************************/
fsl_rtos_status lock_release(lock_object_t *obj)
{
    interrupt_disable_global();
    obj->isLocked = false;
    interrupt_enable_global();
    
    return kSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : lock_destroy
 * Description   : This function is used to destroy a lock object.
 * Return kSuclock if the lock object is destroyed successfully, otherwise
 * return kError.
 *
 *END**************************************************************************/
fsl_rtos_status lock_destroy(lock_object_t *obj)
{
    uint32_t status;
  
    status = sw_timer_release_channel(obj->timerId);
    
    if(status == kSwTimerStatusSuccess)
    {
        return kSuccess;
    }
    else
    {
        return kError;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : event_create
 * Description   : This function is used to create a event object. Return
 * kSuccess if create successfully, otherwise return kError.
 *
 *END**************************************************************************/
fsl_rtos_status event_create(event_object_t *obj, event_clear_type clearType)
{
    obj->timerId = sw_timer_reserve_channel();

    if (kSwTimerChannelNotAvailable == obj->timerId)
    {
        return kError;
    }

    obj->isWaiting = false;
    obj->flags = 0;
    obj->clearType = clearType;
    
    return kSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : event_wait
 * Description   : This function is used to wait a event.
 * Pass the #kSyncWaitForever constant to wait indefinitely. 0 should not be
 * passed to this function. Return kSuccess if any bit of the event object is
 * set before the timeout is exhausted, return kTimeout if no bit is set before
 * the timeout is exhausted, return kError if the parameter is valid, return kIdle
 * if event not ready, this is only for non-blocking mechanism. The bits that
 * have been set will be get by setFlags.
 *
 *END**************************************************************************/
fsl_rtos_status event_wait(event_object_t *obj, uint32_t timeout, event_group_t *setFlags)
{
    fsl_rtos_status retVal = kIdle;
    uint32_t status;
    
    /* Check the event flag first, if not set, deal with timeout. */
    if (obj->flags)
    {
        interrupt_disable_global();
        obj->isWaiting = false;
        if (setFlags) /* If flag value is needed */
        {
            *setFlags = obj->flags;
        }
        if(kEventAutoClr == obj->clearType)
        {
            obj->flags = 0;
        }
        interrupt_enable_global();
        return kSuccess;
    }
    else
    {
        if (obj->isWaiting)
        {
            /* Check for timeout */
            status = sw_timer_get_channel_status(obj->timerId);
            if(status == kSwTimerChannelExpired)
            {
                interrupt_disable_global();
                obj->isWaiting = false;
                interrupt_enable_global();
                retVal = kTimeout;
            }
        }
        else if(timeout != kSyncWaitForever)    /* If no timeout, don't start the timer */
        {
            /* Start the timeout counter */
            interrupt_disable_global();
            obj->isWaiting = true;
            interrupt_enable_global();
            sw_timer_start_channel(obj->timerId, timeout);
        }
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : event_set
 * Description   : Set one or more events of an event object.
 * Return kSuccess if set successfully, kError if failed.
 * This function should not be called from an ISR.
 *
 *END**************************************************************************/
fsl_rtos_status event_set(event_object_t *obj, event_group_t flags)
{
    /* Set flags ensuring atomic operation */
    interrupt_disable_global();
    obj->flags |= flags;
    interrupt_enable_global();
    
    return kSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : event_set_from_isr
 * Description   : Set one or more events of an event object.
 * Return kSuccess if set successfully, kError if failed.
 * This function should only be called from an ISR.
 *
 *END**************************************************************************/
fsl_rtos_status event_set_from_isr(event_object_t *obj, event_group_t flags)
{
    obj->flags |= flags;
    return kSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : event_clear
 * Description   : Clear one or more events of an event object.
 * Return kSuccess if clear successfully, kError if failed.
 *
 *END**************************************************************************/
fsl_rtos_status event_clear(event_object_t *obj, event_group_t flags)
{
    /* Clear flags ensuring atomic operation */
    interrupt_disable_global();
    obj->flags &= ~flags;
    interrupt_enable_global();
    
    return kSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : event_check_flags
 * Description   : Check the event bit is set or not.
 * Return kFlagSet if any bit is set, otherwise return kFlagNotSet.
 *
 *END**************************************************************************/
event_status event_check_flags(event_object_t *obj, event_group_t flag)
{
    if(obj->flags & flag)
    {
        return kFlagSet;
    }
    else
    {
        return kFlagNotSet;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : event_destroy
 * Description   : This function is used to destroy a event object. Return
 * kSuccess if the event object is destroyed successfully, otherwise return kError.
 *
 *END**************************************************************************/
fsl_rtos_status event_destroy(event_object_t *obj)
{
    if (kSwTimerStatusSuccess == sw_timer_release_channel(obj->timerId))
    {
        return kSuccess;
    }
    else
    {
        return kError;
    }
}

/* poll global variale */
POLL_STRUCT g_poll;
static task_handler_t g_curTask; /* Current task. */

/*FUNCTION**********************************************************************
 *
 * Function Name : POLL_init
 * Description   : This function is used to initialize the POLL_STRUCT, it
 * should be called before creating any tasks.
 *
 *END**************************************************************************/
void POLL_init(void) 
{
    uint32_t i;

    g_poll.registered_no = 0; 
    for (i = 0; i <POLL_MAX_NUM; i++)
    {
        g_poll.p_slot[i].p_func = NULL;
        g_poll.p_slot[i].param = NULL;
    }

}

/*FUNCTION**********************************************************************
 *
 * Function Name : Poll
 * Description   : Every task function registered in the POLL_STRUCT will be
 * called in inturn. This function should be used in a infinite loop in main.
 *
 *END**************************************************************************/
void Poll(void) 
{
    uint32_t i;

    for (i = 0; i < g_poll.registered_no; i++)
    {
        g_curTask = g_poll.p_slot[i].p_func;
        g_curTask(g_poll.p_slot[i].param);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : __task_create
 * Description   : This function will register the task function and parameter
 * to the POLL_STRUCT, so that the task functions can be called by Poll. Return
 * kSuccess if register successfully, otherwise return kError;
 *
 *END**************************************************************************/
fsl_rtos_status __task_create(task_t task, uint8_t *name, uint16_t stackSize,
                              task_stack_t *stackMem, uint16_t priority,
                              void *param, bool usesFloat, task_handler_t *handler)
{
    if (POLL_MAX_NUM <= g_poll.registered_no)
    {
        return kError;
    }
    else
    {
        *handler = task;
        g_poll.p_slot[g_poll.registered_no].p_func = task;
        g_poll.p_slot[g_poll.registered_no].param = param;
        g_poll.registered_no ++;
        return kSuccess;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : task_destroy
 * Description   : This function will unregister the task function and parameter
 * from the POLL_STRUCT, so that the task functions will not called by Poll.
 * Return kSuccess if successfully, otherwise return kError;
 *
 *END**************************************************************************/
fsl_rtos_status task_destroy(task_handler_t handler)
{
    uint32_t i;
    
    if (FSL_RTOS_CURRENT_TASK == handler)
    {
        handler = g_curTask;
    }

    for (i=0; i<g_poll.registered_no; i++)
    {
        /* Find the index in the poll structure. */
        if (handler == g_poll.p_slot[i].p_func)
        {
            break;
        }
    }

    if (i == g_poll.registered_no)
    {
        return kError;
    }
    /* sort the function pointer erray */
    g_poll.registered_no--;
    for( ; i < g_poll.registered_no; i++)
    {
        g_poll.p_slot[i] = g_poll.p_slot[i+1];
    }
    g_poll.p_slot[i].p_func = NULL;
    g_poll.p_slot[i].param  = NULL;
    return kSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : msg_queue_create
 * Description   : This function is used to create a message queue.
 * Return the handle to the message queue if create successfully, other wise
 * return 0.
 *
 *END**************************************************************************/
msg_queue_handler_t msg_queue_create(msg_queue_t *queue, uint16_t number, uint16_t size)
{
    fsl_rtos_status status;
  
    queue->number = number;
    queue->size = size;
    queue->head = 0;
    queue->tail = 0;
    queue->isEmpty = true;
    
    status = sync_create(&queue->queueSync, 0);
    
    if(kSuccess == status)
    {
        return queue;
    }
    else
    {
        return NULL;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : msg_queue_put
 * Description   : This function is used to put a message to a message queue.
 * Return kSuccess if the message is put successfully, other wise return kError.
 *
 *END**************************************************************************/
fsl_rtos_status msg_queue_put(msg_queue_handler_t handler, void *item)
{
    fsl_rtos_status retVal = kError;
    
    /* Check that there is room in the queue */
    if((handler->tail != handler->head) || (handler->isEmpty))
    {
        rtos_enter_critical();
#if (__FSL_RTOS_MSGQ_COPY_MSG__)
        uint32_t *src = (uint32_t*)item;
        uint32_t *dst = &handler->queueMem[handler->tail * handler->size];
        uint16_t msgSize;
        
        /* Copy entire message into the queue, based on the size configured at creation */
        msgSize = handler->size;
        while(msgSize--)
        {
           *dst++ = *src++; 
        }
#else
        /* Store the pointer to the message in the queue */
        handler->queueMem[handler->tail] = item;
#endif
        
        /* Adjust tail pointer and wrap in case the end of the buffer is reached */
        ++handler->tail;
        if(handler->tail == handler->number)
        {
            handler->tail = 0;
        }
        
        /* If queue was empty, clear the empty flag and signal that it is not empty anymore */
        if(handler->isEmpty)
        {
            handler->isEmpty = false;
            sync_signal(&handler->queueSync);
        }
        rtos_exit_critical();

        retVal = kSuccess;
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : msg_queue_get
 * Description   : This function is used to get a message from a message queue.
 * If the message queue is empty, set timeout to 0 to return immediately, set
 * timeout to #kSyncWaitForever to wait indefinitely.
 * Return kSuccess if the message is get before the timeout is exhausted, return
 * kTimeout if no message is get before the timeout is exhausted, return kError
 * if the parameter is invalid.
 * The unit of timeout is millisecond.
 *
 *END**************************************************************************/
fsl_rtos_status msg_queue_get(msg_queue_handler_t handler, void **item, uint32_t timeout)
{
    fsl_rtos_status retVal = kError;
    
    rtos_enter_critical();
    /* Check if the queue is not empty */
    if(!handler->isEmpty)
    {
#if (__FSL_RTOS_MSGQ_COPY_MSG__)
        uint32_t *src = &handler->queueMem[handler->head * handler->size];
        uint32_t *dst = (uint32_t*)(*item);
        uint16_t msgSize;
        
        /* Copy entire message into the queue, based on the size configured at creation */
        msgSize = handler->size;
        while(msgSize--)
        {
           *dst++ = *src++; 
        }
#else
        /* Store the pointer to the message in the queue */
        *item = handler->queueMem[handler->head];
#endif
        
        /* Adjust head pointer and wrap in case the end of the buffer is reached */
        ++handler->head;
        if(handler->head == handler->number)
        {
            handler->head = 0;
        }
        
        /* If queue was empty, clear the empty flag and signal that it is not empty anymore */
        if(handler->head == handler->tail)
        {
            handler->isEmpty = true;
            /* Set sync to 0 because the queue is empty. */
            (void)sync_poll(&handler->queueSync);
        }
        rtos_exit_critical();

        retVal = kSuccess;
    }
    else
    {
        rtos_exit_critical();
        /* Wait for the semaphore if the queue was empty */
        retVal = sync_wait(&handler->queueSync, timeout);
    }
    
    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : msg_queue_flush
 * Description   : This function is used to flush the message queue.
 * Return kSuccess if the message queue is flushed successfully, other wise
 * return kError.
 *
 *END**************************************************************************/
fsl_rtos_status msg_queue_flush(msg_queue_handler_t handler)
{
    /* Reset indexes, set status to empty and consume semaphore in case it was set before */
    handler->head = 0;
    handler->tail = 0;
    handler->isEmpty = true;
    /* Consume the queueSync semaphore and set it to 0. */
    while (kSuccess == sync_poll(&handler->queueSync))
    {
        ;
    }
    
    return kSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : msg_queue_destroy
 * Description   : This function is used to destroy the message queue.
 * Return kSuccess if the message queue is destroied successfully, other wise
 * return kError.
 *
 *END**************************************************************************/
fsl_rtos_status msg_queue_destroy(msg_queue_handler_t handler)
{
    return sync_destroy(&handler->queueSync);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : mem_allocate
 * Description   : This function is used to allocate amount of memory in bytes.
 * Return the pointer to the memory if success, otherwise return NULL;
 *
 *END**************************************************************************/
void * mem_allocate(size_t size)
{
    return malloc(size);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : mem_allocate_zero
 * Description   : This function is used to allocate amount of memory in bytes
 * and initializes it to 0.
 * Return the pointer to the memory if success, otherwise return NULL;
 *
 *END**************************************************************************/
void * mem_allocate_zero(size_t size)
{
    return calloc(1, size);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : mem_free
 * Description   : This function is used to free the memory previously allocated.
 *
 *END**************************************************************************/
fsl_rtos_status mem_free(void *ptr)
{
    free(ptr);
    return kSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : time_delay
 * Description   : This function is used to delay for a number of milliseconds.
 *
 *END**************************************************************************/
void time_delay(uint32_t delay)
{
    uint32_t currTime;
    
    currTime = sw_timer_get_free_counter(); /* Get current time stamp */
    delay += currTime;      /* Delay equals the value of the timer after the delay */
    
    while(currTime != delay)
    {
        currTime = sw_timer_get_free_counter(); /* Get current time stamp */
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : interrupt_handler_register
 * Description   : This function is used to install interrupt handler.
 * For bare metal, this function will always return kSuccess.
 *
 *END**************************************************************************/
fsl_rtos_status interrupt_handler_register(int32_t irqNumber, void (*handler)(void))
{
    interrupt_register_handler((IRQn_Type)irqNumber, handler);

    return kSuccess;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

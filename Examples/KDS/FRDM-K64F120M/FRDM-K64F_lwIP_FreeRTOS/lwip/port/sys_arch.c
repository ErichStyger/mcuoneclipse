/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

#include "sys.h"
#if NO_SYS
#include "fsl_hwtimer.h"
#include "fsl_pit_driver.h"
extern const hwtimer_devif_t kSystickDevif;
extern const hwtimer_devif_t kPitDevif;
#endif

/*
 * Prints an assertion messages and aborts execution.
 */
void
sys_assert( const char *msg )
{

//FSL:only needed for debugging
#ifdef LWIP_DEBUG
    PRINTF(msg);
    PRINTF("\n\r");
#endif

    OSA_EnterCritical(kCriticalDisableInt);
    for(;;);
}

#if !NO_SYS

/* Used internal */
void _mbox_create(msg_queue_handler_t *queueHandle, int size)
{
    msg_queue_t * queue = NULL;
#ifdef FSL_RTOS_UCOSII
    uint32_t * msgs = NULL;
    void * msgTbl = NULL;
    msgTbl = OSA_MemAlloc(size * sizeof(void*));    
    if(msgTbl)
    {
        msgs = OSA_MemAlloc(size * sizeof(uint32_t));
        if(msgs)
        {
            queue = (msg_queue_t*)OSA_MemAlloc(sizeof(msg_queue_t));
            if(queue)
            {
                queue->msgTbl = msgTbl;
                queue->msgs = msgs; 
            }
            else
            {
                OSA_MemFree(msgs);
                OSA_MemFree(msgTbl);
                msgs = NULL;
                msgTbl = NULL;
            }
        }
        else
        {
            OSA_MemFree(msgTbl);
            msgTbl= NULL;
        }
    }

#elif defined(FSL_RTOS_UCOSIII)
    uint32_t * msgs = OSA_MemAlloc(size * sizeof(uint32_t));
    if(msgs)
    {
        queue = (msg_queue_t*)OSA_MemAlloc(sizeof(msg_queue_t));
        if(queue)
        {
            queue->msgs = msgs;
        }
        else
        {
            OSA_MemFree(msgs);
            msgs = NULL;
        }
    } 

#elif defined (FSL_RTOS_MQX)
    queue = (msg_queue_t*)OSA_MemAlloc((SIZE_IN_MMT_UNITS(sizeof(LWMSGQ_STRUCT)) + SIZE_IN_MMT_UNITS(4) * size)*sizeof(msg_queue_t));
#endif
#ifdef FSL_RTOS_FREE_RTOS
    *queueHandle = OSA_MsgQCreate(queue,size,1);
#else
    if(queue)
    {
        *queueHandle = OSA_MsgQCreate(queue,size,1);
    }
    else
    {
        *queueHandle = (msg_queue_handler_t)0;
    }
#endif
}
/*-----------------------------------------------------------------------------------*/
//  Creates an empty mailbox.
err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{
    osa_status_t error;
    msg_queue_handler_t queueHandle ;
    _mbox_create(&queueHandle,size);
    error = OSA_SemaCreate (&(mbox->_semSync) , (uint8_t)0);
    if(error != kStatus_OSA_Success)
        return ERR_MEM;
    OSA_EnterCritical(kCriticalDisableInt);
    mbox->queueHandler = queueHandle ;
    OSA_ExitCritical(kCriticalDisableInt);
    if(queueHandle == (msg_queue_handler_t)0)
        return ERR_MEM;
    else
        return ERR_OK;
}

/*-----------------------------------------------------------------------------------*/
/*
  Deallocates a mailbox. If there are messages still present in the
  mailbox when the mailbox is deallocated, it is an indication of a
  programming error in lwIP and the developer should be notified.
*/
void
sys_mbox_free(sys_mbox_t *mbox)
{
    OSA_MsgQDestroy (mbox->queueHandler);
#ifdef FSL_RTOS_UCOSII
    OSA_MemFree(mbox->queueHandler->msgTbl);
    OSA_MemFree(mbox->queueHandler->msgs);
    OSA_MemFree(mbox->queueHandler);
#elif defined(FSL_RTOS_UCOSIII)
    OSA_MemFree(mbox->queueHandler->msgs);
    OSA_MemFree(mbox->queueHandler);
#elif defined(FSL_RTOS_MQX)
    OSA_MemFree(mbox->queueHandler);
#endif
    OSA_SemaDestroy(&(mbox->_semSync));
}


/*-----------------------------------------------------------------------------------*/
//   Posts the "msg" to the mailbox.
void
sys_mbox_post(sys_mbox_t *mbox, void *msg)
{
    osa_status_t error;
    while(1)
    {
        error = OSA_MsgQPut(mbox->queueHandler,&msg);
	if(error == kStatus_OSA_Success)
            return ;
	OSA_SemaWait (&(mbox->_semSync),OSA_WAIT_FOREVER);
    }
}


/*FSL*/
/*
 *Try to post the "msg" to the mailbox. Returns ERR_MEM if this one
 *is full, else, ERR_OK if the "msg" is posted.
 */
err_t
sys_mbox_trypost( sys_mbox_t *mbox, void *msg )
{
    osa_status_t error;
    error = OSA_MsgQPut(mbox->queueHandler,&msg);
    if(error == kStatus_OSA_Success)
        return ERR_OK;
    else
        return ERR_MEM;
}


/*-----------------------------------------------------------------------------------*/
/*
  Blocks the thread until a message arrives in the mailbox, but does
  not block the thread longer than "timeout" milliseconds (similar to
  the sys_arch_sem_wait() function). The "msg" argument is a result
  parameter that is set by the function (i.e., by doing "*msg =
  ptr"). The "msg" parameter maybe NULL to indicate that the message
  should be dropped.

  The return values are the same as for the sys_arch_sem_wait() function:
  Number of milliseconds spent waiting or SYS_ARCH_TIMEOUT if there was a
  timeout.

  Note that a function with a similar name, sys_mbox_fetch(), is
  implemented by lwIP.
*/
u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout)
{
    osa_status_t error;
    uint32_t timeStart , timeEnd;
    void * dummyptr;
    if( timeout == (u32_t)0)
        timeout = OSA_WAIT_FOREVER ;
    if( msg == 0)
        msg = &dummyptr;

    timeStart = OSA_TimeGetMsec();
    error = OSA_MsgQGet(mbox->queueHandler,&(*msg),(uint32_t)timeout);
    timeEnd = OSA_TimeGetMsec();
    switch(error)
    {
        case kStatus_OSA_Timeout:return SYS_ARCH_TIMEOUT;
	case kStatus_OSA_Success:OSA_SemaPost(&(mbox->_semSync));return (u32_t)(timeEnd-timeStart);
	default : return (u32_t)0;
    }

}

/*-----------------------------------------------------------------------------------*/
//  Creates and returns a new semaphore. The "count" argument specifies
//  the initial state of the semaphore. TBD finish and test
err_t
sys_sem_new(sys_sem_t *sem,u8_t count)
{
    osa_status_t outcome;
    outcome =  OSA_SemaCreate(sem,(uint8_t)count);
    if(outcome == kStatus_OSA_Success)
        return ERR_OK;
    else
	return ERR_VAL;

}


/*-----------------------------------------------------------------------------------*/
/*
  Blocks the thread while waiting for the semaphore to be
  signaled. If the "timeout" argument is non-zero, the thread should
  only be blocked for the specified time (measured in
  milliseconds).

  If the timeout argument is non-zero, the return value is the number of
  milliseconds spent waiting for the semaphore to be signaled. If the
  semaphore wasn't signaled within the specified time, the return value is
  SYS_ARCH_TIMEOUT. If the thread didn't have to wait for the semaphore
  (i.e., it was already signaled), the function may return zero.

  Notice that lwIP implements a function with a similar name,
  sys_sem_wait(), that uses the sys_arch_sem_wait() function.
*/
u32_t
sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{
    osa_status_t error;
    uint32_t timeStart , timeEnd;
    if(timeout == (u32_t)0)
        timeout = OSA_WAIT_FOREVER;
    timeStart = OSA_TimeGetMsec();
    error = OSA_SemaWait(sem,(uint32_t)timeout);
    timeEnd = OSA_TimeGetMsec();
    switch(error)
    {
        case kStatus_OSA_Timeout:return SYS_ARCH_TIMEOUT;
	case kStatus_OSA_Success:return (u32_t)(timeEnd-timeStart);
	default : return (u32_t)0;
    }
}


/*-----------------------------------------------------------------------------------*/
// Signals a semaphore
void
sys_sem_signal(sys_sem_t *sem)
{
    OSA_SemaPost(sem);
}

/*-----------------------------------------------------------------------------------*/
// Deallocates a semaphore
void
sys_sem_free(sys_sem_t *sem)
{
    OSA_SemaDestroy(sem);
}


/** Create a new mutex
 * @param mutex pointer to the mutex to create
 * @return a new mutex */
err_t sys_mutex_new(sys_mutex_t *mutex)
{
    osa_status_t error;
    error = OSA_MutexCreate(mutex);
    return (error == kStatus_OSA_Success) ? ERR_OK :  ERR_MEM ;
}


/** Lock a mutex
 * @param mutex the mutex to lock */
void sys_mutex_lock(sys_mutex_t *mutex)
{
    OSA_MutexLock(mutex,OSA_WAIT_FOREVER);
}


/** Unlock a mutex
 * @param mutex the mutex to unlock */
void sys_mutex_unlock(sys_mutex_t *mutex)
{
    OSA_MutexUnlock(mutex);
}


/** Delete a semaphore
 * @param mutex the mutex to delete */
void sys_mutex_free(sys_mutex_t *mutex)
{
    OSA_MutexDestroy(mutex);
}


/*-----------------------------------------------------------------------------------*/
// Initialize sys arch
void
sys_init(void)
{
    //tasks = NULL;
}



/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
// TBD
/*-----------------------------------------------------------------------------------*/
/*
 * Starts a new thread with priority "prio" that will begin its execution in the
 * function "thread()". The "arg" argument will be passed as an argument to the
 * thread() function. The argument "ssize" is the requested stack size for the
 * new thread. The id of the new thread is returned. Both the id and the
 * priority are system dependent.
 */
sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio)
{
    task_handler_t taskHandler;
    osa_status_t error;
    task_stack_t * stackMem ;
#ifdef FSL_RTOS_UCOSIII
    taskHandler = (task_handler_t)OSA_MemAlloc(sizeof(OS_TCB));
    if(!taskHandler)
    {
        return NULL;
    }
#endif

#if (defined FSL_RTOS_UCOSII) || (defined FSL_RTOS_UCOSIII)
    stackMem =  (task_stack_t *)OSA_MemAlloc((size_t)stacksize);
    if(!stackMem)
    {
        return NULL;
    }
#else
    stackMem = NULL;
#endif
    error = OSA_TaskCreate((task_t)thread ,(uint8_t*) name,(uint16_t) stacksize, stackMem,prio,(task_param_t)arg,false,&taskHandler);
    if(error == kStatus_OSA_Success)
        return taskHandler;
    else
        return (sys_thread_t)0;
}



/*
  This optional function does a "fast" critical region protection and returns
  the previous protection level. This function is only called during very short
  critical regions. An embedded system which supports ISR-based drivers might
  want to implement this function by disabling interrupts. Task-based systems
  might want to implement this by using a mutex or disabling tasking. This
  function should support recursive calls from the same task or interrupt. In
  other words, sys_arch_protect() could be called while already protected. In
  that case the return value indicates that it is already protected.

  sys_arch_protect() is only required if your port is supporting an operating
  system.
*/
sys_prot_t sys_arch_protect(void)
{
    OSA_EnterCritical(kCriticalDisableInt);
    return 1;
}




/*
  This optional function does a "fast" set of critical region protection to the
  value specified by pval. See the documentation for sys_arch_protect() for
  more information. This function is only required if your port is supporting
  an operating system.
*/
void sys_arch_unprotect(sys_prot_t pval)
{
    ( void ) pval;
    OSA_ExitCritical(kCriticalDisableInt);
}

int sys_sem_valid(sys_sem_t *sem)
{
#ifdef FSL_RTOS_UCOSIII
    return (sem->Type == OS_OBJ_TYPE_SEM ? 1 : 0 );
#elif defined(FSL_RTOS_MQX)
    return (sem->VALID != 0 ? 1 : 0 );
#else
    return (*sem != 0 ? 1 : 0);
#endif
}
//  set the sem invalid
void sys_sem_set_invalid(sys_sem_t *sem)
{
#ifdef FSL_RTOS_UCOSIII
    sem->Type = OS_OBJ_TYPE_NONE;
#elif defined(FSL_RTOS_MQX)
    sem->VALID = 0;
#else
    *sem = 0;
#endif
}
int sys_mbox_valid(sys_mbox_t *mbox)
{
    return (mbox->queueHandler != 0 ? 1 : 0);
}
// set the mailbox invalid
void sys_mbox_set_invalid(sys_mbox_t *mbox)
{
    mbox->queueHandler = 0;
}
#else
static uint32_t time_now = 0;
hwtimer_t hwtimer;
void hwtimer_callback(void* data)
{
  time_now++;
}
void time_init(void)
{
#define HWTIMER_LL_DEVIF    kPitDevif      // Use hardware timer PIT
#define HWTIMER_LL_ID       3
#define HWTIMER_PERIOD          1000      // 1 ms interval

  if (kHwtimerSuccess != HWTIMER_SYS_Init(&hwtimer, &HWTIMER_LL_DEVIF, HWTIMER_LL_ID, NULL))
    {
        sys_assert("\r\nError: hwtimer initialization.\r\n");
    }
  NVIC_SetPriority(g_pitIrqId[HWTIMER_LL_ID], 5);
  if (kHwtimerSuccess != HWTIMER_SYS_SetPeriod(&hwtimer, HWTIMER_PERIOD))
    {
        sys_assert("\r\nError: hwtimer set period.\r\n");
    }
  if (kHwtimerSuccess != HWTIMER_SYS_RegisterCallback(&hwtimer, hwtimer_callback, NULL))
    {
        sys_assert("\r\nError: hwtimer callback registration.\r\n");
    }
  if (kHwtimerSuccess != HWTIMER_SYS_Start(&hwtimer))
    {
        sys_assert("\r\nError: hwtimer start.\r\n");
    }

}

#endif
/*
This optional function returns the current time in milliseconds (don't care
  for wraparound, this is only used for time diffs).
  Not implementing this function means you cannot use some modules (e.g. TCP
  timestamps, internal timeouts for NO_SYS==1).
  */

u32_t sys_now(void)
{
    uint32_t curTime;
#if !NO_SYS
    curTime = OSA_TimeGetMsec();
#else
    curTime = time_now;
#endif
    return (u32_t)curTime;
}

/*
 * Copyright (c) 2016, NXP Semiconductor
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
 * o Neither the name of NXP Semiconductor nor the names of its
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
 *
 */
/***********************************************************************/
/* INCLUDES                                                            */
/***********************************************************************/
#include "isr_driver_intern.h"
#include "HAL_timer_driver.h"
/***********************************************************************/
/* DEFINES                                                             */
/***********************************************************************/
#undef ISR_CALLBACK_LIST_BEGIN
#undef ISR_CALLBACK_ENTRY
#undef ISR_CALLBACK_LIST_END

#define ISR_CALLBACK_LIST_BEGIN ISR_CALLBACK_T isr_callback_list[ISR_MAX_CALLBACKS] = {
#define ISR_CALLBACK_ENTRY(label, channel, pin_func)                                                        \
    {                                                                                                       \
        channel, pin_func, ISR_DEFAULT_MODE, ISR_INVALID_HANDLER, ISR_DEFAULT_ARGUMENT, ISR_SEMAPHORE_TAKEN \
    }
#define ISR_CALLBACK_LIST_END \
    }                         \
    ;

/***********************************************************************/
/* TYPES                                                               */
/***********************************************************************/
ISR_CALLBACK_LIST_BEGIN
#include "HAL_ISR_callback_list.h" /* allowed here - generator header */
ISR_CALLBACK_LIST_END

/***********************************************************************/
/* GLOBAL VARIABLES                                                    */
/***********************************************************************/
/***********************************************************************/
/* LOCAL FUNCTION PROTOTYPES                                           */
/***********************************************************************/
/***********************************************************************/
/* GLOBAL FUNCTIONS                                                    */
/***********************************************************************/
void HAL_ISR_RegisterCallback(ISR_SOURCE_T source, ISR_MODE_T mode, ISR_HANDLER_T handler, ISR_ARGUMENT_T arg)
{
    ISR_CALLBACK_T *callback = &isr_callback_list[(size_t)source];

    /* enter critical section */
    disableInterrupt(callback->channel);

    callback->mode = mode;
    callback->handler = handler;
    callback->arg = arg;

    ISR_SEMAPHORE_INIT(callback->sema);

    /* setup interrupt mode */
    setupMode(EXT_INT_FD_PORT, callback->pin_func, callback->mode);

    /* leave critical section */
    enableInterrupt(callback->channel);
}

BOOL HAL_ISR_SleepWithTimeout(ISR_SOURCE_T source, uint32_t timeout_ms)
{
    SELECT_CALLBACK((size_t)source);
    uint32_t current = HAL_Timer_getTime_ms();
    uint32_t until = current + timeout_ms;

    do
    {
        /* start waiting for interrupt */
        enableInterrupt(callback->channel);

        ISR_WAIT_FOR_INTERRUPT();

        /* disable interrupt during check */
        disableInterrupt(callback->channel);
        current = HAL_Timer_getTime_ms();
    } while (ISR_SEMAPHORE_IS_TAKEN(callback->sema) && until > current);

    if (ISR_SEMAPHORE_IS_GIVEN(callback->sema))
    {
        /* reinit mode - necessary for edge sensitive on LPCxxx */
        setupMode(EXT_INT_FD_PORT, callback->pin_func, callback->mode);

        ISR_SEMAPHORE_TAKE(callback->sema);
        return FALSE;
    }

    return TRUE;
}

/***********************************************************************/
/* LOCAL FUNCTIONS                                                     */
/***********************************************************************/
/***********************************************************************/
/* INTERUPT SERVICE ROUTINES                                           */
/***********************************************************************/

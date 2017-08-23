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
#ifndef _ISR_DRIVER_INTERN_H_
#define _ISR_DRIVER_INTERN_H_

/***********************************************************************/
/* INCLUDES                                                            */
/***********************************************************************/
#include "HAL_ISR_driver.h"

#if defined(__LPC8XX__) || defined(__LPC11UXX__) || defined(__LPC11U37H__)
#include "isr_lpc_intern.h"
#endif
#if defined(FRDM_K82F) || defined(FRDM_K64F) || defined(FRDM_KL27Z) || defined(FRDM_KL43Z) || defined(FRDM_K22F) || \
    defined(FRDM_KL02Z) || defined(FRDM_KW41Z)
#include "isr_kinetis_intern.h"
#endif

/***********************************************************************/
/* DEFINES                                                             */
/***********************************************************************/
#define ISR_DEFAULT_MODE ISR_EDGE_RISE

#define SELECT_CALLBACK(index) ISR_CALLBACK_T *callback = &isr_callback_list[index];

#define CHECK_VALID_AND_CALL_HANDLER()            \
    if (callback->handler != ISR_INVALID_HANDLER) \
        callback->handler(callback->arg);

#define WAKEUP_TASKS() ISR_SEMAPHORE_GIVE(callback->sema)

#define DISABLE_INTERRUPT() disableInterrupt(callback->channel)

/***********************************************************************/
/* TYPES                                                               */
/***********************************************************************/
typedef uint32_t ISR_CHANNEL_T;
typedef uint32_t ISR_PIN_FUNC_T;

typedef struct
{
    ISR_CHANNEL_T channel;
    ISR_PIN_FUNC_T pin_func;
    ISR_MODE_T mode;
    ISR_HANDLER_T handler;
    ISR_ARGUMENT_T arg;
    ISR_SEMAPHORE_T sema;
} ISR_CALLBACK_T;

/***********************************************************************/
/* GLOBAL VARIABLES                                                    */
/***********************************************************************/
extern ISR_CALLBACK_T isr_callback_list[];

/***********************************************************************/
/* GLOBAL FUNCTION PROTOTYPES                                          */
/***********************************************************************/
void disableInterrupt(uint32_t channel);
void enableInterrupt(uint32_t channel);
void setupMode(void *port, uint32_t pin, ISR_MODE_T mode);

#endif /* _ISR_DRIVER_INTERN_H_ */

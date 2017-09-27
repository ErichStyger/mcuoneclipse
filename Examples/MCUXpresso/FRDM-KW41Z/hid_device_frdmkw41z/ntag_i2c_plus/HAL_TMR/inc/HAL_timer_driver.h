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
/** @file HAL_timer_driver.h
 * \brief Public interface to access the timing hardware.
 */
#ifndef _HAL_TIMER_DRIVER_H_
#define _HAL_TIMER_DRIVER_H_

/***********************************************************************/
/* INCLUDES                                                            */
/***********************************************************************/
#include "global_types.h"

/***********************************************************************/
/* DEFINES                                                             */
/***********************************************************************/
/***********************************************************************/
/* TYPES                                                               */
/***********************************************************************/
/***********************************************************************/
/* GLOBAL VARIABLES                                                    */
/***********************************************************************/
/***********************************************************************/
/* GLOBAL FUNCTION PROTOTYPES                                          */
/***********************************************************************/

/**
 * \brief initialize the timing hardware
 *
 * This function prepares the timing hardware to points where calling
 * any of the following delay functions guarantees at least the desired delay
 * time while not blocking indefinitely.
 *
 * \return		none
 */
void HAL_Timer_Init(void);

/**
 * \brief wait for the specified number of milliseconds
 *
 * This function delays the current thread of execution for at least the
 * number of specified milliseconds. In tasked or threaded environments
 * this function may additionally yield the CPU.
 *
 * \param	ms	wait time in milliseconds
 * \return		none
 */
void HAL_Timer_delay_ms(uint32_t ms);

/**
 * \brief returns the current time in ms
 *
 * This function returns the current value of the ms tick timer.
 *
 * \return		current time in ms
 */
uint32_t HAL_Timer_getTime_ms(void);

#endif /* _HAL_TIMER_DRIVER_H_ */

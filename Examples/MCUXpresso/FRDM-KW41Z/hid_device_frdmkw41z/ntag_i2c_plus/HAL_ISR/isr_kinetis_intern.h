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
#ifndef _ISR_FRDM_INTERN_H_
#define _ISR_FRDM_INTERN_H_

/***********************************************************************/
/* INCLUDES                                                            */
/***********************************************************************/
#include <board.h>
#include "fsl_gpio.h" // added for NTAG middleware

/***********************************************************************/
/* DEFINES                                                             */
/***********************************************************************/
#if defined(__LPC11UXX__) || defined(__LPC11U37H__)
#define GPIO_PININT_NVIC(channel) (PIN_INT0_IRQn + channel)
#define GPIO_PIN_MIN 0
#define GPIO_NUMBER_PINS 72
#endif /* LPC11U6x */
#if defined(FRDM_K82F)
#define GPIO_PININT_NVIC(channel) ((IRQn_Type)(PORTC_IRQn + channel))
#define EXT_INT_FD_GPIO GPIOC
#define EXT_INT_FD_PORT PORTC
#define EXT_INT_FD_PIN 10U
#endif /* FRDM_K82F */
#if defined(FRDM_K64F)
#define GPIO_PININT_NVIC(channel) ((IRQn_Type)(PORTA_IRQn + channel))
#define EXT_INT_FD_GPIO GPIOA
#define EXT_INT_FD_PORT PORTA
#define EXT_INT_FD_PIN 2U
#endif /* FRDM_K64F */
#if defined(FRDM_KL27Z)
#define GPIO_PININT_NVIC(channel) ((IRQn_Type)(PORTB_PORTC_PORTD_PORTE_IRQn + channel))
#define EXT_INT_FD_GPIO GPIOE
#define EXT_INT_FD_PORT PORTE
#define EXT_INT_FD_PIN 24U
#endif /* FRDM_KL27Z */
#if defined(FRDM_KL43Z)
#define GPIO_PININT_NVIC(channel) ((IRQn_Type)(PORTA_IRQn + channel))
#define EXT_INT_FD_GPIO GPIOA
#define EXT_INT_FD_PORT PORTA
#define EXT_INT_FD_PIN 5U
#endif /* FRDM_KL43Z */
#if defined(FRDM_K22F)
#define GPIO_PININT_NVIC(channel) ((IRQn_Type)(PORTB_IRQn + channel))
#define EXT_INT_FD_GPIO GPIOB
#define EXT_INT_FD_PORT PORTB
#define EXT_INT_FD_PIN 18U
#endif /* FRDM_K22F */
#if defined(FRDM_KL02Z)
#define GPIO_PININT_NVIC(channel) ((IRQn_Type)(PORTA_IRQn + channel))
#define EXT_INT_FD_GPIO GPIOA
#define EXT_INT_FD_PORT PORTA
#define EXT_INT_FD_PIN 12U
#endif /* FRDM_KL02Z */
#if defined(FRDM_KW41Z)
#define GPIO_PININT_NVIC(channel) ((IRQn_Type)(PORTB_PORTC_IRQn + channel))
#define EXT_INT_FD_GPIO GPIOC
#define EXT_INT_FD_PORT PORTC
#define EXT_INT_FD_PIN 17U
#endif /* FRDM_KW41Z */

#define ISR_PIN_FUNC_INVALID 0xFFFFFFFF

#define ISR_SEMAPHORE_GIVEN true
#define ISR_SEMAPHORE_TAKEN false

#define ISR_SEMAPHORE_INIT(x)    \
    do                           \
    {                            \
        x = ISR_SEMAPHORE_TAKEN; \
    } while (0)
#define ISR_SEMAPHORE_GIVE(x)    \
    do                           \
    {                            \
        x = ISR_SEMAPHORE_GIVEN; \
    } while (0)
#define ISR_SEMAPHORE_GIVE_FROM_ISR(x) \
    do                                 \
    {                                  \
        x = ISR_SEMAPHORE_GIVEN;       \
    } while (0)

#define ISR_SEMAPHORE_TAKE(x) \
    do                        \
    {                         \
        x = false;            \
    } while (0)

#define ISR_SEMAPHORE_IS_GIVEN(x) (x == ISR_SEMAPHORE_GIVEN)
#define ISR_SEMAPHORE_IS_TAKEN(x) (x == ISR_SEMAPHORE_TAKEN)

#define ISR_WAIT_FOR_INTERRUPT() __WFI();

/***********************************************************************/
/* TYPES                                                               */
/***********************************************************************/
typedef BOOL ISR_SEMAPHORE_T;

/***********************************************************************/
/* GLOBAL VARIABLES                                                    */
/***********************************************************************/
/***********************************************************************/
/* GLOBAL FUNCTION PROTOTYPES                                          */
/***********************************************************************/
#endif /* _ISR_FRDM_INTERN_H_ */

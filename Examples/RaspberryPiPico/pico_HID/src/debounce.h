/*
 * Copyright (c) 2022-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_

#include <stdint.h>
#include "McuRTOS.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Start debouncing with a set of buttons. Do not call this method from an interrupt.
 *        The application gets notified through events.
 * \param buttons Set of initial buttons pressed
 */
void Debounce_StartDebounce(uint32_t buttons);

/*!
 * \brief Same as Debounce_StartDebounce(), but usable from an interrupt
 * \param buttons Set of initial buttons pressed
 * \param pxHigherPriorityTaskWoken Set to true if a task with a higher priority has been woken up
 */
void Debounce_StartDebounceFromISR(uint32_t buttons, BaseType_t *pxHigherPriorityTaskWoken);

/*!
 * Module de-initialization
 */
void Debounce_Deinit(void);

/*!
 * \brief Module initialization
 */
void Debounce_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* DEBOUNCE_H_ */

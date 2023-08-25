/*
 * Copyright (c) 2021-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "platform.h"
#if PL_CONFIG_USE_BUTTONS
#include <stdbool.h>
#include <stdint.h>
#include "buttons_config.h"

/*!
 * \brief Decides if a button is pressed
 * \param btn Button to check
 * \return true if button is pressed
 */
bool BTN_IsPressed(BTN_Buttons_e btn);

/*!
 * \brief Read the button status from the pins and build a bitmask
 * \return Bitmask of buttons pressed, e.g. BTN_BIT_NAV_UP, see buttons_config.h
 */
uint32_t BTN_GetButtons(void);

/*!
 * \brief Module de-initialization
 */
void BTN_Deinit(void);

/*!
 * \brief Module initialization
 */
void BTN_Init(void);

#endif /* PL_CONFIG_USE_BUTTONS */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* BUTTONS_H_ */

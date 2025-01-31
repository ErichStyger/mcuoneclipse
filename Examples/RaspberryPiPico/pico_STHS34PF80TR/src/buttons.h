/*
 * Copyright (c) 2021-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdbool.h>
#include "buttons_config.h"

/*!
 * \brief Decides if a button is pressed, directly accessing the pin
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
 * \brief Rotates the button orientation based on BTN_CONFIG_ROTATION
 * \param button Button to rotate
 * \return Rotated button
 */
BTN_Buttons_e BTN_RotateButton(BTN_Buttons_e button);

/*!
 * \brief Initializes the buttons
 */
void BTN_Init(void);

/*!
 * \brief Deinitializes the buttons
 */
void BTN_Deinit(void);

#endif /* BUTTONS_H_ */
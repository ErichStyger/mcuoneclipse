/*
 * Copyright (c) 2021-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdbool.h>
#include "buttons_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Decides if a button is pressed, directly accessing the pin
 * \param btn Button to check
 * \return true if button is pressed
 */
bool Buttons_IsPressed(Buttons_e btn);

/*!
 * \brief Read the button status from the pins and build a bitmask
 * \return Bitmask of buttons pressed, e.g. BUTTONS_BIT_NAV_UP, see buttons_config.h
 */
uint32_t Buttons_GetButtons(void);

/*!
 * \brief Rotates the button orientation based on Buttons_CONFIG_ROTATION
 * \param button button pressed
 * \return rotated button
 */
Buttons_e Buttons_RotateButton(Buttons_e button);

/*!
 * \brief Module de-initialization
 */
void Buttons_Deinit(void);

/*!
 * \brief Module initialization
 */
void Buttons_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* BUTTONS_H_ */

/**
 * \file
 * \brief Key debouncing interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements debouncing for multiple keys.
 */

#ifndef KEYDEBOUNCE_H_
#define KEYDEBOUNCE_H_

#include "Platform.h"
#if PL_CONFIG_HAS_DEBOUNCE
/*!
 * \brief Kicks the debouncing state machine.
 */
void KEYDBNC_Process(void);

/*!
 * \brief Driver initialization.
 */
void KEYDBNC_Init(void);

/*!
 * \brief Driver de-initialization.
 */
void KEYDBNC_Deinit(void);
#endif /* PL_CONFIG_HAS_DEBOUNCE */

#endif /* KEYDEBOUNCE_H_ */

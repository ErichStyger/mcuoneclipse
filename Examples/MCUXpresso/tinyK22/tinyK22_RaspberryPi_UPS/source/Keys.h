/**
 * \file
 * \brief Key/switch driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic keyboard driver for up to 4 Keys.
 * It is using macros for maximum flexibility with minimal code overhead.
 */

#ifndef KEYS_H_
#define KEYS_H_

#include "platform.h"

#if PL_CONFIG_HAS_KEYS

typedef enum {
#if PL_CONFIG_NOF_KEYS>=1
  KEY_BTN1, /*!< button 1 */
#endif
#if PL_CONFIG_NOF_KEYS>=2
  KEY_BTN2, /*!< button 2 */
#endif
#if PL_CONFIG_NOF_KEYS>=3
  KEY_BTN3, /*!< button 3 */
#endif
#if PL_CONFIG_NOF_KEYS>=4
  KEY_BTN4, /*!< button 4 */
#endif
#if PL_CONFIG_NOF_KEYS>=5
  KEY_BTN5, /*!< button 5 */
#endif
#if PL_CONFIG_NOF_KEYS>=6
  KEY_BTN6, /*!< button 6 */
#endif
#if PL_CONFIG_NOF_KEYS>=7
  KEY_BTN7, /*!< button 7 */
#endif
  KEY_BTN_LAST /*!< must be last */
} KEY_Buttons;

#include "Debounce.h"
DBNC_KeySet Key_GetKeysBits(void);

#if PL_CONFIG_HAS_KBI
/*!
 * \brief Function called from a keyboard interrupt (if supported).
 * \param button Button for which interrupt has been generated.
 */
void KEY_OnInterrupt(KEY_Buttons button);

/*!
 * \brief Acknowledge any pending interrupt, and enable again keyboard interrupts
 */
void KEY_EnableInterrupts(void);

/*!
 * \brief Acknowledge any pending interrupt, and enable again keyboard interrupts
 */
void KEY_DisableInterrupts(void);

#endif

/*!
 * \brief Checks the key status and generates the events.
 */
void KEY_Scan(void);

/*! \brief Get access to key hardware. Use KEY_Close() afterwards. */
void KEY_Open(void);

/*! \brief Finish access to key hardware. Called after KEY_Open(). */
void KEY_Close(void);

/*! \brief Key driver initialization */
void KEY_Init(void);

/*! \brief Key driver de-initialization */
void KEY_Deinit(void);

#endif /* PL_HAS_KEYS */

#endif /* KEYS_H_ */

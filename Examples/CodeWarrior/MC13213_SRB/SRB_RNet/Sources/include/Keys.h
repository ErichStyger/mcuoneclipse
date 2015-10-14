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

#include "Platform.h"

#if PL_HAS_KEYS

#if PL_HAS_KBI
  #include "KB1.h"

  #define KEY1_Get()  (!(KB1_GetVal()&(1<<0)))
    /*!< Macro which returns TRUE if key 1 is pressed */
  #define KEY2_Get()  (!(KB1_GetVal()&(1<<1)))
    /*!< Macro which returns TRUE if key 2 is pressed */
  #define KEY3_Get()  (!(KB1_GetVal()&(1<<2)))
    /*!< Macro which returns TRUE if key 3 is pressed */
  #define KEY4_Get()  (!(KB1_GetVal()&(1<<3)))
    /*!< Macro which returns TRUE if key 4 is pressed */
#else

#if PL_NOF_KEYS>=1
  #include "SW1.h"

  #define KEY1_Get()  (!(SW1_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY1_Get()  0
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=2
  #include "SW2.h"

  #define KEY2_Get()  (!(SW2_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY2_Get()  0
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=3
  #include "SW3.h"

  #define KEY3_Get()  (!(SW3_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY3_Get()  0
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=4
  #include "SW4.h"

  #define KEY4_Get()  (!(SW4_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY4_Get()  0
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#endif /* PL_HAS_KBI */


#if PL_HAS_KBI
/*!
 * \brief Function called from a keyboard interrupt (if supported).
 */
void KEY_OnInterrupt(void);
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

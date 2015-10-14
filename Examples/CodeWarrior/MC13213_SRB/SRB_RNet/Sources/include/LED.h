/**
 * \file
 * \brief LED driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic LED driver for up to 5 LEDs.
 * It is using macros for maximum flexibility with minimal code overhead.
 */

#ifndef LED_H_
#define LED_H_

#include "Platform.h"
#if PL_NOF_LEDS >= 1
  #include "LED1.h"
#else
  #define LED1_On()     /* do nothing */
    /*!< Turn LED 1 on */
  #define LED1_Off()    /* do nothing */
    /*!< Turn LED 1 off */
  #define LED1_Neg()    /* do nothing */
    /*!< Toggle LED 1 */
  #define LED1_Get()  0 /* do nothing */
    /*!< Return TRUE if LED 1 is on, FALSE otherwise */
  #define LED1_Put(val) /* do nothing */
    /*!< Turn LED 1 on or off */
  #define LED1_Init()   /* do nothing */
    /*!< Initialize LED 1 */
  #define LED1_Deinit() /* do nothing */
    /*!< De-Initialize LED 1 */
#endif

#if PL_NOF_LEDS >= 2
  #include "LED2.h"
#else
  #define LED2_On()     /* do nothing */
    /*!< Turn LED 2 on */
  #define LED2_Off()    /* do nothing */
    /*!< Turn LED 2 off */
  #define LED3_Neg()    /* do nothing */
    /*!< Toggle LED 2 */
  #define LED2_Get()  0 /* do nothing */
    /*!< Return TRUE if LED 2 is on, FALSE otherwise */
  #define LED2_Put(val) /* do nothing */
    /*!< Turn LED 2 on or off */
  #define LED2_Init()   /* do nothing */
    /*!< Initialize LED 2 */
  #define LED2_Deinit() /* do nothing */
    /*!< De-Initialize LED 2 */
#endif

#if PL_NOF_LEDS >= 3
  #include "LED3.h"
#else
  #define LED3_On()     /* do nothing */
    /*!< Turn LED 3 on */
  #define LED3_Off()    /* do nothing */
    /*!< Turn LED 3 off */
  #define LED3_Neg()    /* do nothing */
    /*!< Toggle LED 3 */
  #define LED3_Get()  0 /* do nothing */
    /*!< Return TRUE if LED 3 is on, FALSE otherwise */
  #define LED3_Put(val) /* do nothing */
    /*!< Turn LED 3 on or off */
  #define LED3_Init()   /* do nothing */
    /*!< Initialize LED 3 */
  #define LED3_Deinit() /* do nothing */
    /*!< De-Initialize LED 3 */
#endif

#if PL_NOF_LEDS >= 4
  #include "LED4.h"
#else
  #define LED4_On()     /* do nothing */
    /*!< Turn LED 4 on */
  #define LED4_Off()    /* do nothing */
    /*!< Turn LED 4 off */
  #define LED4_Neg()    /* do nothing */
    /*!< Toggle LED 4 */
  #define LED4_Get()  0 /* do nothing */
    /*!< Return TRUE if LED 4 is on, FALSE otherwise */
  #define LED4_Put(val) /* do nothing */
    /*!< Turn LED 4 on or off */
  #define LED4_Init()   /* do nothing */
    /*!< Initialize LED 4 */
  #define LED4_Deinit() /* do nothing */
    /*!< De-Initialize LED 4 */
#endif

#if PL_NOF_LEDS >= 5
  #include "LED5.h"
#else
  #define LED5_On()     /* do nothing */
    /*!< Turn LED 5 on */
  #define LED5_Off()    /* do nothing */
    /*!< Turn LED 5 off */
  #define LED5_Neg()    /* do nothing */
    /*!< Toggle LED 5 */
  #define LED5_Get()  0 /* do nothing */
    /*!< Return TRUE if LED 1 is on, FALSE otherwise */
  #define LED5_Put(val) /* do nothing */
    /*!< Turn LED 5 on or off */
  #define LED5_Init()   /* do nothing */
    /*!< Initialize LED 5 */
  #define LED5_Deinit()  /* do nothing */
    /*!< De-Initialize LED 5 */
#endif

/*!
 * \brief LED Driver Intialization.
 */
void LED_Init(void);

/*!
 * \brief LED Driver De-Initialization.
 */
void LED_Deinit(void);

#endif /* LED_H_ */

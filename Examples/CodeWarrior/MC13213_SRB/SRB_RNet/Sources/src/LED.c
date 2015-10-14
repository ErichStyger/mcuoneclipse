/**
 * \file
 * \brief LED driver implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic LED driver for up to 5 LEDs.
 * It is using macros for maximum flexibility with minimal code overhead.
 */

#include "Platform.h"
#include "LED.h"

#define LED_TEST_LED  1 
  /*!< Set to 1 if test LED function is available, 0 otherwise */

void LED_Deinit(void) {
  LED1_Deinit();
  LED2_Deinit();
  LED3_Deinit();
  LED4_Deinit();
  LED5_Deinit();
}

void LED_Init(void) {
  LED1_Init();
  LED2_Init();
  LED3_Init();
  LED4_Init();
  LED5_Init();
}

#if LED_TEST_LED
/*!
 * \brief LED test routine.
 * This routine tests if:
 * - we can turn the LEDs properly on and off
 * - if we can negate them
 * - if we can set an LED value
 * - if we can get the LED value
 * If the test fails, the program will hanging in an endless loop
 */
void LED_Test(void) {
  bool isOn = TRUE;
  
  LED1_On();
  LED2_On();
  LED3_On();
  LED4_On();
  LED5_On();

  LED1_Off();
  LED2_Off();
  LED3_Off();
  LED4_Off();
  LED5_Off();

  LED1_Neg();
  LED2_Neg();
  LED3_Neg();
  LED4_Neg();
  LED5_Neg();

  LED1_On();
  if (!LED1_Get()) {
    for(;;){}; /* error */ /*! \todo Need a dedicated error routine */
  }
  LED1_Off();
  if (LED1_Get()) {
    for(;;){}; /* error */
  }
  LED1_Put(isOn);
  if (!LED1_Get()) {
    for(;;){}; /* error */
  }
}
#endif


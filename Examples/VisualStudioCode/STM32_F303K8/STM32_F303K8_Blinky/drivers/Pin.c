/**
 * \file
 * \brief Implementation of a driver for the Pins on the PRG_G board.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements functions for the Pins (switches, push buttons and tilt switch).
 */

#include "Platform.h"
#include "Pin.h"
#include <stdbool.h>
#if PL_CONFIG_BOARD==PL_CONFIG_BOARD_ID_STM32_NUCLEO
  #include "stm32f3xx_hal.h"
#endif

#define SW1_Get()   (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)==GPIO_PIN_SET)
	/*!< returns the status of the SW1 switch */
#define SW2_Get()   (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)==GPIO_PIN_SET)
	/*!< returns the status of the SW2 switch */
#define SW3_Get()   (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==GPIO_PIN_SET)
	/*!< returns the status of the SW3 switch */
#define SW4_Get()   (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)==GPIO_PIN_SET)
	/*!< returns the status of the SW4 switch */
#define SW5_Get()   (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==GPIO_PIN_SET)
	/*!< returns the status of the SW5 switch */
#define SW6_Get()   (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)==GPIO_PIN_SET)
	/*!< returns the status of the SW6 switch */
#define TILT_Get()  (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)==GPIO_PIN_SET)
	/*!< returns the status of the tilt switch */

bool PIN_IsPinHigh(Pin_PinId pin) {
  switch(pin) {
    case PIN_S1: return SW1_Get();
    case PIN_S2: return SW2_Get();
    case PIN_S3: return SW3_Get();
    case PIN_S4: return SW4_Get();
    case PIN_S5: return SW5_Get();
    case PIN_S6: return SW6_Get();
    case PIN_TILT: return TILT_Get();
    default: break;
  }
  return false;
}

void PIN_Init(void) {
  /* nothing required */
}

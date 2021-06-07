/**
 * \file
 * \brief Implementation of a driver for the LEDs on the PRG_G board.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements functions for the LEDs.
 */

#include "Platform.h"
#include "Led.h"
#include <stdbool.h>
#if PL_CONFIG_BOARD==PL_CONFIG_BOARD_ID_STM32_NUCLEO
  #include "stm32f3xx_hal.h"
#endif

#define LED0_On()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,  GPIO_PIN_SET)
	/*!< Turns the LED 0 on */
#define LED1_On()   HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1,  GPIO_PIN_RESET)
	/*!< Turns the LED 1 on */
#define LED2_On()   HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0,  GPIO_PIN_RESET)
	/*!< Turns the LED 2 on */
#define LED3_On()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,  GPIO_PIN_RESET)
	/*!< Turns the LED 3 on */
#define LED4_On()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,  GPIO_PIN_RESET)
	/*!< Turns the LED 4 on */
#define LEDR_On()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9,  GPIO_PIN_SET)
	/*!< Turns the red LED on */
#define LEDG_On()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET)
	/*!< Turns the green LED on */
#define LEDB_On()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET)
	/*!< Turns the blue LED on */

#define LED0_Off()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,  GPIO_PIN_RESET)
	/*!< Turns the LED 0 off */
#define LED1_Off()  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1,  GPIO_PIN_SET)
	/*!< Turns the LED 1 off */
#define LED2_Off()  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0,  GPIO_PIN_SET)
	/*!< Turns the LED 2 off */
#define LED3_Off()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,  GPIO_PIN_SET)
	/*!< Turns the LED 3 off */
#define LED4_Off()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,  GPIO_PIN_SET)
	/*!< Turns the LED 4 off */
#define LEDR_Off()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9,  GPIO_PIN_RESET)
	/*!< Turns the red LED off */
#define LEDG_Off()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET)
	/*!< Turns the green LED off */
#define LEDB_Off()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET)
	/*!< Turns the blue LED off */

#define LED0_Neg()  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3)
	/*!< Negates/toggles the LED 0 */
#define LED1_Neg()  HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_1)
	/*!< Negates/toggles the LED 1 */
#define LED2_Neg()  HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_0)
	/*!< Negates/toggles the LED 2 */
#define LED3_Neg()  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6)
	/*!< Negates/toggles the LED 3 */
#define LED4_Neg()  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7)
	/*!< Negates/toggles the LED 4 */
#define LEDR_Neg()  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9)
	/*!< Negates/toggles the red LED */
#define LEDG_Neg()  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_12)
	/*!< Negates/toggles the green LED */
#define LEDB_Neg()  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10)
	/*!< Negates/toggles the blue LED */

#define LED0_Get()  (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)==GPIO_PIN_SET?true:false)
	/*!< Return true if LED is turned on, false otherwise */
#define LED1_Get()  (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_1)==GPIO_PIN_SET?false:true)
	/*!< Return true if LED is turned on, false otherwise */
#define LED2_Get()  (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_0)==GPIO_PIN_SET?false:true)
	/*!< Return true if LED is turned on, false otherwise */
#define LED3_Get()  (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)==GPIO_PIN_SET?false:true)
	/*!< Return true if LED is turned on, false otherwise */
#define LED4_Get()  (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)==GPIO_PIN_SET?false:true)
	/*!< Return true if LED is turned on, false otherwise */
#define LEDR_Get()  (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==GPIO_PIN_SET?true:false)
	/*!< Return true if LED is turned on, false otherwise */
#define LEDG_Get()  (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12)==GPIO_PIN_SET?true:false)
	/*!< Return true if LED is turned on, false otherwise */
#define LEDB_Get()  (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==GPIO_PIN_SET?true:false)
	/*!< Return true if LED is turned on, false otherwise */

#define LED0_Put(on)  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,  on?GPIO_PIN_SET:GPIO_PIN_RESET)
	/*!< Writes a boolean value to the LED 0 to turn it on or off */
#define LED1_Put(on)  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1,  on?GPIO_PIN_RESET:GPIO_PIN_SET)
	/*!< Writes a boolean value to the LED 1 to turn it on or off */
#define LED2_Put(on)  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0,  on?GPIO_PIN_RESET:GPIO_PIN_SET)
	/*!< Writes a boolean value to the LED 2 to turn it on or off */
#define LED3_Put(on)  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,  on?GPIO_PIN_RESET:GPIO_PIN_SET)
	/*!< Writes a boolean value to the LED 3 to turn it on or off */
#define LED4_Put(on)  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,  on?GPIO_PIN_RESET:GPIO_PIN_SET)
	/*!< Writes a boolean value to the LED 4 to turn it on or off */
#define LEDR_Put(on)  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9,  on?GPIO_PIN_SET:GPIO_PIN_RESET)
	/*!< Writes a boolean value to the red LED to turn it on or off */
#define LEDG_Put(on)  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, on?GPIO_PIN_SET:GPIO_PIN_RESET)
	/*!< Writes a boolean value to the green LED to turn it on or off */
#define LEDB_Put(on)  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, on?GPIO_PIN_SET:GPIO_PIN_RESET)
	/*!< Writes a boolean value to the blue LED to turn it on or off */

void LED_On(LED_LedId led) {
  switch(led) {
    case LED_LED0: LED0_On(); break;
    case LED_LED1: LED1_On(); break;
    case LED_LED2: LED2_On(); break;
    case LED_LED3: LED3_On(); break;
    case LED_LED4: LED4_On(); break;
    case LED_LEDR: LEDR_On(); break;
    case LED_LEDG: LEDG_On(); break;
    case LED_LEDB: LEDB_On(); break;
    default: break;
  }
}

void LED_Off(LED_LedId led) {
  switch(led) {
    case LED_LED0: LED0_Off(); break;
    case LED_LED1: LED1_Off(); break;
    case LED_LED2: LED2_Off(); break;
    case LED_LED3: LED3_Off(); break;
    case LED_LED4: LED4_Off(); break;
    case LED_LEDR: LEDR_Off(); break;
    case LED_LEDG: LEDG_Off(); break;
    case LED_LEDB: LEDB_Off(); break;
    default: break;
  }
}

void LED_Neg(LED_LedId led) {
  switch(led) {
    case LED_LED0: LED0_Neg(); break;
    case LED_LED1: LED1_Neg(); break;
    case LED_LED2: LED2_Neg(); break;
    case LED_LED3: LED3_Neg(); break;
    case LED_LED4: LED4_Neg(); break;
    case LED_LEDR: LEDR_Neg(); break;
    case LED_LEDG: LEDG_Neg(); break;
    case LED_LEDB: LEDB_Neg(); break;
    default: break;
  }
}

bool LED_Get(LED_LedId led) {
  switch(led) {
    case LED_LED0: return LED0_Get(); break;
    case LED_LED1: return LED1_Get(); break;
    case LED_LED2: return LED2_Get(); break;
    case LED_LED3: return LED3_Get(); break;
    case LED_LED4: return LED4_Get(); break;
    case LED_LEDR: return LEDR_Get(); break;
    case LED_LEDG: return LEDG_Get(); break;
    case LED_LEDB: return LEDB_Get(); break;
    default: break;
  }
  return false; /* default, error case */
}

void LED_Put(LED_LedId led, bool on) {
  switch(led) {
    case LED_LED0: LED0_Put(on); break;
    case LED_LED1: LED1_Put(on); break;
    case LED_LED2: LED2_Put(on); break;
    case LED_LED3: LED3_Put(on); break;
    case LED_LED4: LED4_Put(on); break;
    case LED_LEDR: LEDR_Put(on); break;
    case LED_LEDG: LEDG_Put(on); break;
    case LED_LEDB: LEDB_Put(on); break;
    default: break;
  }
}

void LED_Init(void) {
  LED_Off(LED_LED0);
  LED_Off(LED_LED1);
  LED_Off(LED_LED2);
  LED_Off(LED_LED3);
  LED_Off(LED_LED4);
  LED_Off(LED_LEDR);
  LED_Off(LED_LEDG);
  LED_Off(LED_LEDB);
}

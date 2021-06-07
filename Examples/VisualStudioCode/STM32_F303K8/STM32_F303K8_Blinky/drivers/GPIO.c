/**
 * \file
 * \brief Implementation of the GPIO on the PRG_G board.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the GPIO (General Purpose Input/Output) driver.
 */

#include "Platform.h"
#include "GPIO.h"
#include "stm32f3xx_hal.h"

static void MX_GPIO_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE(); /* enable clock for GPIO F */
  __HAL_RCC_GPIOA_CLK_ENABLE(); /* enable clock for GPIO A */
  __HAL_RCC_GPIOB_CLK_ENABLE(); /* enable clock for GPIO B */

  GPIO_InitStruct.Alternate = 0; /* init */

  /* setup initialization structure */
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT; /* configure as push/pull output pin */
  GPIO_InitStruct.Pull = GPIO_NOPULL; /* no pull-up needed */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  /* PA5 and PA6 must be set to high Z (see schematics) */
  GPIO_InitStruct.Pin = GPIO_PIN_5; HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = GPIO_PIN_6; HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  /* ******************* Configure LED's *****************************/
  /* LED0: PB3: Onboard green LED
   * LED1: PF1:
   * LED2: PF0:
   * LED3: PB6:
   * LED4: PB7:
   * LEDR: PA9
   * LEDG: PA12
   * LEDG: PA10
   */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; /* configure as push/pull output pin */
  GPIO_InitStruct.Pull = GPIO_NOPULL; /* no pull-up needed */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  /* write default output level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_SET);
  /* RGB LEDs */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = GPIO_PIN_3; HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = GPIO_PIN_6; HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = GPIO_PIN_7; HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = GPIO_PIN_0; HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = GPIO_PIN_1; HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
  /* RGB */
  GPIO_InitStruct.Pin = GPIO_PIN_9;  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = GPIO_PIN_10; HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = GPIO_PIN_12; HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* ******************* Configure Hall (analog GPIO) ********************/
  /* Hall: PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  /* ******************* Configure Switches and Tilt ********************/
  /* SW1: PB0
   * SW2: PB1
   * SW3: PA8
   * SW4: PA11
   * SW5: PB5
   * SW6: PB4
   * TILT: PA1
   */
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT; /* configure as input pin */
  GPIO_InitStruct.Pull = GPIO_NOPULL; /* we have external pull-ups on the pins */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  GPIO_InitStruct.Pin = GPIO_PIN_0; HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = GPIO_PIN_1; HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = GPIO_PIN_8; HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = GPIO_PIN_11; HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = GPIO_PIN_5; HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = GPIO_PIN_4; HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = GPIO_PIN_1; HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  /* ****************************************************************/
}

void GPIO_Init(void) {
  MX_GPIO_Init();
}

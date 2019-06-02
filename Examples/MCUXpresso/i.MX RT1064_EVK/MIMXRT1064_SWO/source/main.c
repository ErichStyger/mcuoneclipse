/*
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MIMXRT1064xxxxA_swo.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1064.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
#define EXAMPLE_LED_GPIO BOARD_USER_LED_GPIO
#define EXAMPLE_LED_GPIO_PIN BOARD_USER_LED_GPIO_PIN

volatile uint32_t g_systickCounter;
/* The PIN status */
volatile bool g_pinSet = false;

void SysTick_Handler(void) {
  if (g_systickCounter != 0U) {
      g_systickCounter--;
  }
}

void SysTick_DelayTicks(uint32_t n) {
  g_systickCounter = n;
  while(g_systickCounter != 0U)
  {
  }
}

static void blinkFLASH(void) {
  if (g_pinSet) {
    GPIO_PinWrite(EXAMPLE_LED_GPIO, EXAMPLE_LED_GPIO_PIN, 0U);
    g_pinSet = false;
  } else  {
    GPIO_PinWrite(EXAMPLE_LED_GPIO, EXAMPLE_LED_GPIO_PIN, 1U);
    g_pinSet = true;
  }
}

/*
 * @brief   Application entry point.
 */
int main(void) {
  gpio_pin_config_t led_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};

  /* Init board hardware. */
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();
  /* Init FSL debug console. */
  BOARD_InitDebugConsole();

  PRINTF("Hello World\n");

  /* Init output LED GPIO. */
  GPIO_PinInit(EXAMPLE_LED_GPIO, EXAMPLE_LED_GPIO_PIN, &led_config);

  /* Set systick reload value to generate 1ms interrupt */
  if(SysTick_Config(SystemCoreClock / 1000U)) {
     while(1) {
     }
  }
  while (1) {
    /* Delay 1000 ms */
    SysTick_DelayTicks(1000U);
    blinkFLASH();
  }
  return 0 ;
}

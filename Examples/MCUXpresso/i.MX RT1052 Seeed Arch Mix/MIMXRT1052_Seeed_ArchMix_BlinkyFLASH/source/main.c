/*
 * Copyright 2016-2019 NXP
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
 * @file    MIMXRT1052_Seeed_ArchMix_BlinkyFLASH.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1052.h"
#include <stdbool.h>
#include "fsl_gpio.h"

/* The RGB LED connected to the No. 52 pin of RT1052 chip.  */
/* The button connected to the No. 125 pin of RT1052 chip. */
/*
 * __RT1052_PIN(52, GPIO1,  9),    // GPIO_AD_B0_09
 * __RT1052_PIN(125, GPIO5,  0),   // WAKEUP
 * https://github.com/RT-Thread/rt-thread/blob/8ed3470d2a485c49ec4f5d4a5ec53e94edf7a2c8/bsp/imxrt1052-evk/drivers/drv_pin.c#L184
 */
#define EXAMPLE_LED_GPIO        GPIO1
#define EXAMPLE_LED_GPIO_PIN    (9U)

#define EXAMPLE_SW02_GPIO       GPIO5
#define EXAMPLE_SW02_GPIO_PIN   (0U)

/* TODO: insert other definitions and declarations here. */
static volatile uint32_t g_systickCounter;
/* The PIN status */
static volatile bool g_pinSet = false;

void SysTick_Handler(void) {
  if (g_systickCounter != 0U) {
    g_systickCounter--;
  }
}

static void SysTick_DelayTicks(uint32_t n) {
  g_systickCounter = n;
  while(g_systickCounter != 0U)
  {
  }
}

static void blinky(void) {
  int cntr = 0;
  gpio_pin_config_t led_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};
  gpio_pin_config_t sw_config = {kGPIO_DigitalInput, 0, kGPIO_NoIntmode};
  /* Init output LED GPIO. */
  GPIO_PinInit(EXAMPLE_LED_GPIO, EXAMPLE_LED_GPIO_PIN, &led_config);
  GPIO_PinInit(EXAMPLE_SW02_GPIO, EXAMPLE_SW02_GPIO_PIN, &sw_config); /* internal pull-up is enabled in pin mux */

  /* Set systick reload value to generate 1ms interrupt */
  if(SysTick_Config(SystemCoreClock / 1000U)) {
      while(1) {
      }
  }
  while (1) {
    /* Delay 1000 ms */
    SysTick_DelayTicks(1000U);
    if (GPIO_PinRead(EXAMPLE_SW02_GPIO, EXAMPLE_SW02_GPIO_PIN)==0) {
      while(GPIO_PinRead(EXAMPLE_SW02_GPIO, EXAMPLE_SW02_GPIO_PIN)==0) {
        /* wait while pressed */
      }
      cntr--; /* button pressed! */
    } else {
      cntr++; /* button not pressed */
    }
    if (g_pinSet) {
        GPIO_PinWrite(EXAMPLE_LED_GPIO, EXAMPLE_LED_GPIO_PIN, 0U);
        g_pinSet = false;
    } else     {
        GPIO_PinWrite(EXAMPLE_LED_GPIO, EXAMPLE_LED_GPIO_PIN, 1U);
        g_pinSet = true;
    }
  }
}


/*
 * @brief   Application entry point.
 */
int main(void) {
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    printf("Hello World\n");

    blinky();
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        __asm volatile ("nop");
    }
    return 0 ;
}

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
 * @file    tinyK22_Blinky.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK22F51212.h"
/* TODO: insert other include files here. */
#include "fsl_gpio.h"
/* TODO: insert other definitions and declarations here. */

// LPC845:
// :100400 00 94320010C046BD4602B080BD309B0000 53

#if 1 /* startup/safe version */
__attribute__ ((used,section(".FlashConfig"))) const struct {
    unsigned int word1;
    unsigned int word2;
    unsigned int word3;
    unsigned int word4;
} Flash_Config = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFE
};
// :10
//  0400
//  00
//  FF FF FF FF   FF FF FF FF   FF FF FF FF   FE FF FF FF    FD
#elif 1
__attribute__ ((used,section(".FlashConfig"))) const struct {
    unsigned int word1;
    unsigned int word2;
    unsigned int word3;
    unsigned int word4;
} Flash_Config = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFF00
    | NV_FSEC_KEYEN(0b11) /* 0b11: backdoor key enabled */
    | NV_FSEC_MEEN(0b11) /* 0b11: mass erase enabled */
    | NV_FSEC_FSLACC(0b11) /* factory access enabled */
    | NV_FSEC_SEC(0b11)  /* 0b11: secure, 0b10 unsecure  */
};
#else
/* 16 bytes at address 0x400 */
__attribute__((used, section(".FlashConfig"))) const uint32_t FOPTConfig[4] = {
  0xFFFFFFFF,
  0xFFFFFFFF,
  0xFFFFFFFF,
 // 0xFFFF3DFE // boot from FLASH
  0xFFFFBDFE   // boot from ROM, means this will kick in the bootloader by default
};
#endif

#define BOARD_LED_BLUE_GPIO   GPIOC
#define BOARD_LED_BLUE_PORT   PORTC
#define BOARD_LED_BLUE_PIN    2U

static void delay(void) {
	volatile int i = 1000000;
	while(i>0) {
		__asm("nop");
		i--;
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

    //printf("Hello World\n");

    while(1) {
      GPIO_PortSet(BOARD_LED_BLUE_GPIO, (1<<BOARD_LED_BLUE_PIN)); /* led off */
      delay();
      delay();
      GPIO_PortClear(BOARD_LED_BLUE_GPIO, (1<<BOARD_LED_BLUE_PIN)); /* led on */
      delay();
      delay();
    }
    return 0 ;
}

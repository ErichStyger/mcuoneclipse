/*
 * Copyright 2016-2021 NXP
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
 * @file    FRDM-K66_Blinky.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK66F18.h"
#include "fsl_debug_console.h"

#include "McuLib.h"
#include "McuRTOS.h"
#include "McuGPIO.h"
#include "McuLED.h"

#if configUSE_HEAP_SCHEME==5
  /* K22FN512 has two 64K memory banks: upper: 192k, lower 64k  */
  static __attribute__ ((used,section(".noinit.$SRAM_LOWER.Heap5"))) uint8_t heap_sram_lower[64*1024]; /* placed in in no_init section inside SRAM_LOWER */
  static __attribute__ ((used,section(".noinit_Heap5"))) uint8_t heap_sram_upper[16*1024]; /* placed in in no_init section inside SRAM_UPPER */
  static const HeapRegion_t xHeapRegions[] =
  {
   { &heap_sram_lower[0], sizeof(heap_sram_lower)},
   { &heap_sram_upper[0], sizeof(heap_sram_upper)},
   { NULL, 0 } /* << Terminates the array. */
  };
#endif

#define PINS_LEDBLUE_GPIO       GPIOA
#define PINS_LEDBLUE_PORT       PORTA
#define PINS_LEDBLUE_PIN        11U
static McuLED_Handle_t blueLED;

static void InitLibs(void) {
  McuLib_Init();
  McuGPIO_Init();
  McuLED_Init();
  McuRTOS_Init();
#if configUSE_HEAP_SCHEME==5
  vPortDefineHeapRegions(xHeapRegions); /* Pass the array into vPortDefineHeapRegions(). Must be called first! */
#endif

  McuLED_Config_t config;

  McuLED_GetDefaultConfig(&config);
  CLOCK_EnableClock(kCLOCK_PortA); /* LED */
  config.isLowActive = true;
  config.hw.pin = PINS_LEDBLUE_PIN;
  config.hw.port = PINS_LEDBLUE_PORT;
  config.hw.gpio = PINS_LEDBLUE_GPIO;
  blueLED = McuLED_InitLed(&config);
}

static void BlinkyTask(void *pv) {
  for(;;) {
    McuLED_Toggle(blueLED);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

int main(void) {
    /* Init board hardware. */
    BOARD_InitBootPins();
    //BOARD_InitBootClocks(); /* somehow does not work with code generated from clocks tool? */
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    InitLibs();

    if (xTaskCreate(
        BlinkyTask,  /* pointer to the task */
        "Blinky", /* task name for kernel awareness debugging */
        500/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+2,  /* initial priority */
        (TaskHandle_t*)NULL /* optional task handle to create */
      ) != pdPASS) {
       for(;;){} /* error! probably out of memory */
    }

    vTaskStartScheduler();
     while(1) {
         __asm volatile ("nop");
    }
    return 0 ;
}

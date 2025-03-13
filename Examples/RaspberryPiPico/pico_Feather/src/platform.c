/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuRTOS.h"
#include "McuRTT.h"
#include "McuUtility.h"
#include "McuSystemView.h"
#include "McuShellUart.h"
#include "McuGenericI2C.h"
#include "McuGenericSWI2C.h"
#include "McuSSD1306.h"
#include "McuDebounce.h"
#include "McuI2cLib.h"
#include "leds.h"
#include "buttons.h"
#include "debounce.h"
#include "shell.h"

#if PL_CONFIG_USE_NEO_PIXEL_HW
  #include "NeoPixel.h"
  #include "ws2812.h"
  #include "cube.h"
  #include "cubeAnim.h"
#endif
#if PL_CONFIG_USE_TUD_CDC
  #include "McuShellCdcDevice.h"
#endif

#if configUSE_HEAP_SCHEME==5
  static __attribute__ ((used,section(".noinit.$SRAM_LOWER.Heap5"))) uint8_t heap_sram_lower[64*1024]; /* placed in in no_init section inside SRAM_LOWER */
  static __attribute__ ((used,section(".noinit_Heap5"))) uint8_t heap_sram_upper[16*1024]; /* placed in in no_init section inside SRAM_UPPER */
  static const HeapRegion_t xHeapRegions[] =
  {
   { &heap_sram_lower[0], sizeof(heap_sram_lower)},
   { &heap_sram_upper[0], sizeof(heap_sram_upper)},
   { NULL, 0 } /* << Terminates the array. */
  };
#endif

void PL_Init(void) {
  McuLib_Init();
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
  SEGGER_SYSVIEW_Start();
#endif
#if PL_CONFIG_USE_TUD_CDC
  McuShellCdcDevice_Init();
  McuShellCdcDevice_SetBufferRxCharCallback(McuShellCdcDevice_QueueChar);
#endif
#if configUSE_HEAP_SCHEME==5
  vPortDefineHeapRegions(xHeapRegions); /* Pass the array into vPortDefineHeapRegions(). Must be called first! */
#endif
  McuWait_Init();
  McuWait_Waitms(100); /* give OLED time to power on */
  McuGPIO_Init();
  McuLED_Init();
  McuDbnc_Init();
  McuRTOS_Init();
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
  McuGenericI2C_Init(); /* initialize generic I2C module */
  #if PL_CONFIG_USE_HW_I2C
    #if McuLib_CONFIG_CPU_IS_KINETIS
    CLOCK_EnableClock(kCLOCK_PortB); /* I2C pins on Port B, needed for ResetBus() */
    #endif
    McuI2cLib_Init(); /* initialize I2C library */
  #else
    #if McuLib_CONFIG_CPU_IS_KINETIS
    CLOCK_EnableClock(kCLOCK_PortA);
    #endif
    McuGenericSWI2C_Init();
  #endif
  Leds_Init();
#if PL_CONFIG_USE_BUTTONS
  Buttons_Init();
  Debounce_Init();
#endif
#if PL_CONFIG_USE_MININI
  McuMinINI_Init();
#endif
#if PL_CONFIG_USE_NVMC
  McuFlash_Init();
  McuFlash_RegisterMemory((const void*)McuMinINI_CONFIG_FLASH_NVM_ADDR_START, 1*McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE);
#endif
#if PL_CONFIG_USE_NEO_PIXEL_HW
  WS2812_Init();
  NEO_Init();
  Cube_Init();
  CubeAnim_Init();
#endif
}

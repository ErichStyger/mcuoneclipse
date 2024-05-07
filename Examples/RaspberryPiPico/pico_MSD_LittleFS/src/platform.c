/*
 * Copyright (c) 2023-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuLog.h"
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
#if PL_CONFIG_USE_SHELL
  #include "shell.h"
#endif
#if PL_CONFIG_USE_MININI
  #include "McuMinINI.h"
#endif
#if PL_CONFIG_USE_INTERNAL_FLASH
  #include "McuFlash.h"
#endif
#if PL_CONFIG_USE_USB_CDC
  #include "pico/stdio_usb.h"
#endif
#if PL_CONFIG_USE_UART
  #include "pico/stdio_uart.h"
#endif
#if PL_CONFIG_USE_LITTLE_FS
  #include "littleFS/McuLittleFS.h"
#endif
#if PL_CONFIG_USE_TINY_USB
  #include "../msdusb/tusb_config.h"
  #include <tusb.h>
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
  McuLog_Init();
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
  SEGGER_SYSVIEW_Start();
#endif
#if configUSE_HEAP_SCHEME==5
  vPortDefineHeapRegions(xHeapRegions); /* Pass the array into vPortDefineHeapRegions(). Must be called first! */
#endif
  McuWait_Init();
  McuGPIO_Init();
  McuLED_Init();
  McuDbnc_Init();
  McuRTOS_Init();
#if PL_CONFIG_USE_SHELL_UART
  McuShellUart_Init();
#endif
#if PL_CONFIG_USE_TINY_USB
  tud_init(BOARD_TUD_RHPORT);
#endif
#if PL_CONFIG_USE_USB_CDC 
  if (!stdio_usb_init()) {
    for(;;) { /* failed initializing USB */} // GCOVR_EXCL_LINE
  }
#endif
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
#if PL_CONFIG_USE_INTERNAL_FLASH
  McuFlash_Init();
  McuFlash_RegisterMemory((const void*)McuFlash_CONFIG_MEM_START, McuFlash_CONFIG_NOF_BLOCKS*McuFlash_CONFIG_FLASH_BLOCK_SIZE);
#endif
#if PL_CONFIG_USE_MININI
  McuMinINI_Init();
#endif
#if PL_CONFIG_USE_LITTLE_FS
  McuLFS_Init();
#endif
}

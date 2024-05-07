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
#include "McuDebounce.h"
#include "McuI2cLib.h"
#if PL_CONFIG_USE_LEDS
  #include "leds.h"
#endif
#if PL_CONFIG_USE_BUTTONS
  #include "buttons.h"
  #include "debounce.h"
#endif
#if PL_CONFIG_USE_SHELL
  #include "shell.h"
#endif
#if PL_CONFIG_USE_MININI
  #include "McuMinINI.h"
  #include "McuFlash.h"
#endif
#if PL_CONFIG_USE_USB_CDC
  #include "pico/stdio_usb.h"
#endif
#if PL_CONFIG_USE_UART
  #include "pico/stdio_uart.h"
#endif
#if PL_CONFIG_USE_SEMIHOSTING
  #include "pico/stdio_semihosting.h"
#endif
#if PL_CONFIG_USE_NEO_PIXEL_HW
  #include "NeoPixel.h"
  #include "ws2812.h"
#endif
#if PL_CONFIG_USE_NEO_APP
  #include "neoApp.h"
#endif

#if PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_PICO || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_PICO_W
/* https://github.com/raspberrypi/pico-sdk/blob/master/src/rp2_common/pico_stdio_usb/stdio_usb_descriptors.c, around line 147
 * change call of pico_get_unique_board_id_string() to the following:  */
#if 0
  #if 1 /* << EST */
      extern void pico_usb_get_unique_board_id_string(char *id_out, uint len);
      pico_usb_get_unique_board_id_string(usbd_serial_str, sizeof(usbd_serial_str));
  #else
      pico_get_unique_board_id_string(usbd_serial_str, sizeof(usbd_serial_str));
  #endif
#endif

void pico_usb_get_unique_board_id_string(char *id_out, uint len) {
#if 0 /* original version */
  pico_get_unique_board_id_string(id_out, len); /* default */
#else /* use same USB serial number for all boards, so sharing the same COM interface */
  McuUtility_strcpy(id_out, len, "PicoAEMBS");
#endif
}
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
#if PL_CONFIG_USE_USB_CDC 
  if (!stdio_usb_init()) {
    for(;;) { /* failed initializing USB */} // GCOVR_EXCL_LINE
  }
#endif
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
#if PL_CONFIG_USE_LEDS
  LEDS_Init();
#endif
#if PL_CONFIG_USE_BUTTONS
  BTN_Init();
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
#endif
#if PL_CONFIG_USE_NEO_APP
  NeoApp_Init();
#endif
}

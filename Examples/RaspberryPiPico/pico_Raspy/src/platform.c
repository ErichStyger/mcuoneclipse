/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_USB_CDC
  #include "pico/stdlib.h"
#endif
#if PL_CONFIG_USE_WIFI
  #include "PicoWiFi.h"
#elif PL_CONFIG_USE_PICO_W
  #include "pico/cyw43_arch.h" /* must be first, otherwise conflict with lwIP ERR_OK */
#endif
#include "McuLib.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuUtility.h"
#include "McuLog.h"
#if McuLib_CONFIG_SDK_USE_FREERTOS
  #include "McuRTOS.h"
#endif
#if PL_CONFIG_PULL_NAV
  #include "nav.h"
#endif
#if PL_CONFIG_USE_NEO_PIXEL_HW
  #include "NeoPixel.h"
  #include "ws2812.h"
  #include "cube.h"
  #include "cubeAnim.h"
#endif
#if PL_CONFIG_USE_UART
  #include "RaspyUart.h"
#endif
#if PL_CONFIG_USE_I2C
  #include "McuGenericI2C.h"
  #include "McuGenericSWI2C.h"
  #include "McuI2cLib.h"
#endif
#if PL_CONFIG_USE_OLED
  #include "McuSSD1306.h"
  #include "oled.h"
#endif

/* \todo need to have it globally defined, as not present anywhere else */
uint32_t SystemCoreClock = 120000000;

#if McuLib_CONFIG_CPU_IS_RPxxxx
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
  McuUtility_strcpy(id_out, len, "PicoRaspy");
#endif
}
#endif /* McuLib_CONFIG_CPU_IS_RPxxxx */

void PL_Init(void) {
#if PL_CONFIG_USE_USB_CDC
  stdio_init_all(); /* needed for USB CDC, but might cause issues while debugging, because USB traffic might stall */
#endif
  McuLib_Init();
#if McuLib_CONFIG_SDK_USE_FREERTOS
  McuRTOS_Init();
#endif
  McuGPIO_Init();
  McuLED_Init();
  McuLog_Init();
#if PL_CONFIG_USE_WIFI
  PicoWiFi_Init();
#endif
#if PL_CONFIG_PULL_NAV
  Nav_Init();
#endif
#if PL_CONFIG_USE_NEO_PIXEL_HW
  WS2812_Init();
  NEO_Init();
  Cube_Init();
  CubeAnim_Init();
#endif
#if PL_CONFIG_USE_UART
  RaspyUart_Init();
#endif
#if PL_CONFIG_USE_I2C
  #if CONFIG_USE_HW_I2C
    McuI2cLib_Init();
  #else
    McuGenericSWI2C_Init();
  #endif
  McuGenericI2C_Init();
#endif
#if PL_CONFIG_USE_OLED
  OLED_Init();
#endif
}

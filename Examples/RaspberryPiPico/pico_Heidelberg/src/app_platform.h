/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef APP_PLATFORM_H_
#define APP_PLATFORM_H_

/* following items need to be configured in IncludeMcuLibConfig.h:
 * CONFIG_USE_HW_I2C
 * CONFIG_USE_HW_RTC
 */

/* different HW/PCB versions: */
#define PL_CONFIG_HW_VERSION_0_1    (1)  /* V0.1, 65x65mm green PCB with Pico, only with USB battery charger, without road */
#define PL_CONFIG_HW_VERSION_0_2    (2)  /* V0.2, 95x95mm green PCB with Pico, added slots for house and solar connector, without road */
#define PL_CONFIG_HW_VERSION_0_3    (3)  /* V0.3, 165x200 mm green 4-Layer PCB created by Christian Jost, with road */
#define PL_CONFIG_HW_VERSION_0_4    (4)  /* V0.4, 'House of LEDs' */
#define PL_CONFIG_HW_VERSION_0_5    (5)  /* V0.5, new PCB (January 2023) */

/* active PCB/Hardware version */
#define PL_CONFIG_HW_ACTIVE_HW_VERSION  (PL_CONFIG_HW_VERSION_0_3)
/* Note: depending on model, change SSD1306 orientation with McuSSD1306_CONFIG_FIXED_DISPLAY_ORIENTATION in IncludeMcuLibConfig.h */

#define PL_CONFIG_USE_PICO_W          (1) /* if using Pico W with WiFi */
  /* Note:
   * a) enable 'library pico_cyw43_arch_lwip_sys_freertos' in CMakeLists.txt of src folder
   * b) Enable set(PICO_BOARD pico_w) in CMakeLists.txt in project root
   */
#define PL_CONFIG_USE_PING            (1 && PL_CONFIG_USE_PICO_W)
#define PL_CONFIG_USE_NTP_CLIENT      (1 && PL_CONFIG_USE_PICO_W)

#define PL_CONFIG_USE_BUTTONS         (0) /* if using push button/navigation switch */
#define PL_CONFIG_USE_I2C             (0 && (PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_1 || PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_2 || PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_3)) /* if using I2C */
#define PL_CONFIG_USE_GUI             (0) /* if using lvgl GUI or not */
#define PL_CONFIG_USE_GUI_KEY_NAV     (1 && PL_CONFIG_USE_GUI && PL_CONFIG_USE_BUTTONS)
#define PL_CONFIG_USE_OLED            (1 & PL_CONFIG_USE_I2C && !PL_CONFIG_USE_GUI) /* if using OLED module (simple GUI, not lvgl!) */
#define PL_CONFIG_USE_OLED_CLOCK      (1 && PL_CONFIG_USE_OLED) /* if showing clock/time/date on OLED. Note: no true RTC yet! */
#define PL_CONFIG_USE_USB_CDC         (0) /* caution, because issues while debugging! In Termite, need to connect with RTS/CTS! Putty works fine */
#define PL_CONFIG_USE_RTT             (1) /* if using SEGGER RTT */
#define PL_CONFIG_USE_SHELL_UART      (0) /* NYI, using the physical UART */
#define PL_CONFIG_USE_NVMC            (1) /* if using NVMC in Flash, needs to be turned on too */
#define PL_CONFIG_USE_MINI            (1 && PL_CONFIG_USE_NVMC)
#define PL_CONFIG_USE_EXT_FLASH       (0 && !PL_CONFIG_USE_BUTTONS) /* if using externals SPI flash (uses nav switch button pins!) */
#define PL_CONFIG_USE_LITTLE_FS       (0 && PL_CONFIG_USE_EXT_FLASH) /* if using littleFS as file system, not supported yet! */

#define PL_CONFIG_USE_RS485           (0) /* controls RS-485 and Modbus in app_platform.c */
#define PL_CONFIG_USE_RS485_SHELL     (1 && PL_CONFIG_USE_RS485 && McuUart485_CONFIG_USE_RS_485 && !McuModbus_CONFIG_IS_ENABLED)

void PL_Init(void);

#endif /* APP_PLATFORM_H_ */

/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef APP_PLATFORM_H_
#define APP_PLATFORM_H_

#include "IncludeMcuLibConfig.h"
/* following items need to be configured in IncludeMcuLibConfig.h:
 * LIB_CONFIG_HW_VERSION
 * CONFIG_USE_HW_I2C
 * CONFIG_USE_HW_RTC
 */
#define PL_CONFIG_HW_ACTIVE_HW_VERSION  (LIB_CONFIG_HW_VERSION)

#define PL_CONFIG_USE_PICO_W          (1 && PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_6) /* if using Pico W board */
  /* Note:
   * a) enable 'library pico_cyw43_arch_lwip_sys_freertos' in CMakeLists.txt of src folder
   * b) Enable set(PICO_BOARD pico_w) in CMakeLists.txt in project root
   */
#define PL_CONFIG_USE_WIFI            (1 && PL_CONFIG_USE_PICO_W) /* if using WiFi functionality */
#define PL_CONFIG_USE_PING            (1 && PL_CONFIG_USE_WIFI)   /* using ping application */
#define PL_CONFIG_USE_NTP_CLIENT      (1 && PL_CONFIG_USE_WIFI)   /* using ntp application */
#define PL_CONFIG_USE_UDP_SERVER      (0 && PL_CONFIG_USE_WIFI)   /* using udp server application */
#define PL_CONFIG_USE_TCP_SERVER      (0 && PL_CONFIG_USE_WIFI)
#define PL_CONFIG_USE_MQTT_CLIENT     (1 && PL_CONFIG_USE_WIFI)

#define PL_CONFIG_USE_BUTTONS           (1) /* if using push button/navigation switch */
#define PL_CONFIG_USE_BUTTON_NEXT_PREV  (1 && (PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_1 || PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_5)) /* if having 'next' and 'previous' buttons */
#define PL_CONFIG_USE_I2C               (1 && (PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_1 || PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_2 || PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_3 || PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_5 || PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_6)) /* if using I2C */
#define PL_CONFIG_USE_GUI               (1 && PL_CONFIG_USE_I2C) /* if using lvgl GUI or not */
#define PL_CONFIG_USE_GUI_KEY_NAV       (1 && PL_CONFIG_USE_GUI && PL_CONFIG_USE_BUTTONS) /* if using navigation keys for GUI */
#define PL_CONFIG_USE_GUI_ENERGY_DASHBOARD   (1) /* energy flow dashboard */
#define PL_CONFIG_USE_USB_CDC           (1) /* caution, because issues while debugging! In Termite, need to connect with RTS/CTS! Putty works fine */
#define PL_CONFIG_USE_RTT               (1) /* if using SEGGER RTT */
#define PL_CONFIG_USE_NVMC              (1) /* if using NVMC in Flash, needs to be turned on too */
#define PL_CONFIG_USE_MINI              (1 && PL_CONFIG_USE_NVMC)
#define PL_CONFIG_USE_RS485             (1 && (PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_6))

#define PL_CONFIG_USE_EXT_FLASH         (0 && !PL_CONFIG_USE_BUTTONS) /* if using externals SPI flash (uses nav switch button pins!) */
#define PL_CONFIG_USE_LITTLE_FS         (0 && PL_CONFIG_USE_EXT_FLASH) /* if using littleFS as file system, not supported yet! */
#define PL_CONFIG_USE_SHELL_UART        (0) /* NYI, using the physical UART */

#define PL_CONFIG_USE_NEO_PIXEL_HW      (1 && (PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_1 || PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_2 || PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_3 || PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_4 || PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_6)) /* using WS2812B */
#define PL_CONFIG_USE_PWM_LED           (1 && (PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_5)) /* using RGB LEDs with PWM */
#define PL_CONFIG_USE_ADC               (1 && (PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_2 || PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_3 || PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_5)) /* if analog converter is used */
#define PL_CONFIG_USE_SHT31             (0 & PL_CONFIG_USE_I2C) /* if using SHT31 sensor */
#define PL_CONFIG_USE_SHT40             (1 & PL_CONFIG_USE_I2C && PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_5) /* if using SHT31 sensor */
#define PL_CONFIG_USE_ROAD              (1 && (PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_3 || PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_5)) /* if having support for the magnetic/coil road */
#define PL_CONFIG_USE_OLED              (0 & PL_CONFIG_USE_I2C && !PL_CONFIG_USE_GUI) /* if using OLED module (simple GUI, not lvgl!) */
#define PL_CONFIG_USE_OLED_CLOCK        (0 && PL_CONFIG_USE_OLED) /* if showing clock/time/date on OLED. Note: no true RTC yet! */
#define PL_CONFIG_USE_POWER             (1)
#define PL_CONFIG_USE_PCF85063A         (1 && (PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_5)) /* using external RTC */

#define PL_CONFIG_USE_LIGHTS            (1 && (PL_CONFIG_USE_PWM_LED|PL_CONFIG_USE_NEO_PIXEL_HW)) /* VHS house light application */
#define PL_CONFIG_USE_LED_COUNTER_APP   (0 && !PL_CONFIG_USE_LIGHTS && PL_CONFIG_USE_NEO_PIXEL_HW && PL_CONFIG_USE_BUTTONS) /* application to control LEDs with nav switch */

void PL_Init(void);

#endif /* APP_PLATFORM_H_ */

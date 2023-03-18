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

/* picow_ble_temp_reader, acts as client to the server */
#define PL_CONFIG_STANDALONE_BLE_TEMP_SENSOR_CLIENT  (1 /*RUNNING_AS_CLIENT*/)  /* set RUNNING_AS_CLIENT to 1 in src/CMakeLists.txt */

/* picow_ble_temp_sensor acts as Server, providing temperature values: */
#define PL_CONFIG_STANDALONE_BLE_TEMP_SENSOR_SERVER  (1 && !PL_CONFIG_STANDALONE_BLE_TEMP_SENSOR_CLIENT) /* set RUNNING_AS_CLIENT to 0 in src/CMakeLists.txt */

/* different HW/PCB versions: */
#define PL_CONFIG_HW_VERSION_0_1    (1)  /* V0.1, 65x65mm green PCB with Pico, only with USB battery charger, without road */
#define PL_CONFIG_HW_VERSION_0_2    (2)  /* V0.2, 95x95mm green PCB with Pico, added slots for house and solar connector, without road */
#define PL_CONFIG_HW_VERSION_0_3    (3)  /* V0.3, 165x200 mm green 4-Layer PCB created by Christian Jost, with road */
#define PL_CONFIG_HW_VERSION_0_4    (4)  /* V0.4, 'House of LEDs' */

/* active PCB/Hardware version */
#define PL_CONFIG_HW_ACTIVE_HW_VERSION  (PL_CONFIG_HW_VERSION_0_4)

#define PL_CONFIG_USE_PICO_W          (1) /* if using Pico-W */
  /* Note:
   * if using Pico-W:
   * a) enable 'library pico_cyw43_arch_lwip_sys_freertos' in CMakeLists.txt of src folder
   * b) Enable set(PICO_BOARD pico_w) in CMakeLists.txt in project root
   */

#define PL_CONFIG_USE_WIFI            (0 && PL_CONFIG_USE_PICO_W)
#define PL_CONFIG_USE_BLE             (1 && PL_CONFIG_USE_PICO_W)

#define PL_CONFIG_USE_NEO_PIXEL_HW    (0) /* using WS2812B */
#define PL_CONFIG_USE_I2C             (0 && (PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_1 || PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_2)) /* if using I2C */
#define PL_CONFIG_USE_OLED            (0 & PL_CONFIG_USE_I2C) /* if using OLED module */
#define PL_CONFIG_USE_OLED_CLOCK      (0 && PL_CONFIG_USE_OLED) /* if showing clock/time/date on OLED. Note: no true RTC yet! */
#define PL_CONFIG_USE_ADC             (0) /* if analog converter is used */
#define PL_CONFIG_USE_SHT31           (0 & PL_CONFIG_USE_I2C) /* if using SHT31 sensor */
#define PL_CONFIG_USE_BUTTONS         (0) /* if using push button/navigation switch */
#define PL_CONFIG_USE_USB_CDC         (0) /* caution, because issues while debugging! In Termite, need to connect with RTS/CTS! Putty works fine */
#define PL_CONFIG_USE_RTT             (1) /* if using SEGGER RTT */
#define PL_CONFIG_USE_SHELL_UART      (0) /* NYI */
#define PL_CONFIG_USE_ROAD            (0 && PL_CONFIG_HW_ACTIVE_HW_VERSION==PL_CONFIG_HW_VERSION_0_3) /* if having support for the magnetic/coil road */
#define PL_CONFIG_USE_NVMC            (0) /* if using NVMC in Flash, needs to be turned on too */
#define PL_CONFIG_USE_MINI            (0 && PL_CONFIG_USE_NVMC)
#define PL_CONFIG_USE_EXT_FLASH       (0 && !PL_CONFIG_USE_BUTTONS) /* if using externals SPI flash (uses nav switch button pins!) */
#define PL_CONFIG_USE_LITTLE_FS       (0 && PL_CONFIG_USE_EXT_FLASH)

#define PL_CONFIG_USE_LED_DEMO_APP    (0 && PL_CONFIG_USE_NEO_PIXEL)
#define PL_CONFIG_USE_LED_COUNTER_APP (1 && !PL_CONFIG_USE_LED_DEMO_APP && PL_CONFIG_USE_NEO_PIXEL_HW && PL_CONFIG_USE_BUTTONS) /* application to control LEDs with nav switch */

void PL_Init(void);

#endif /* APP_PLATFORM_H_ */

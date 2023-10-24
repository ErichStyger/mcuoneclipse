/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option */

#ifndef MCULIB_CONFIG_CONFIG_H_
#define MCULIB_CONFIG_CONFIG_H_

/* ---------------------------------------------------------------------------------------*/
/* different HW/PCB versions: */
#define PL_CONFIG_HW_ADIS_ESP_ROBO_SHIELD         (1)  /* ESP32 shield on K22FX512 robot */
#define PL_CONFIG_HW_ADIS_PICO_W_CONSOLE_V0_1     (2)  /* Pico-W console board with OLED, sensor, nav switch, 1-Jul-2023 */
#define PL_CONFIG_HW_ADIS_PICO_W_CONSOLE_V0_2     (3)  /* same as PL_CONFIG_HW_ADIS_PICO_W_CONSOLE_V0_1, but with added nRF */
#define PL_CONFIG_HW_ADIS_ESP32_CONSOLE_V0_1      (4)  /* ESP32 DevKitC-32E with OLED, wired PCB, sensor, nav switch and RS-485, 5-Jul-2023, obsolete */
#define PL_CONFIG_HW_ADIS_ESP32_CONSOLE_V0_2      (5)  /* ESP32 DevKitC-32E with OLED, green PCB, sensor, nav switch, RS-485, nRF, 14-Jul-2023 */
#define PL_CONFIG_HW_ADIS_ESP32_CONSOLE_V1_0      (6)  /* ESP32 DevKitC-32E with OLED, black PCB, sensor, nav switch, RS-485, nRF, 07-Aug-2023 */

/* active PCB/Hardware version */
#define PL_CONFIG_HW_VERSION  (PL_CONFIG_HW_ADIS_PICO_W_CONSOLE_V0_2)

/* ---------------------------------------------------------------------------------------*/
/* SDK */
#define McuLib_CONFIG_CPU_IS_KINETIS                (0)
#define McuLib_CONFIG_CORTEX_M                      (0) /* RP2040 is a Cortex-M0+ */
#define McuLib_CONFIG_CPU_IS_RPxxxx                 (1)
#define McuLib_CONFIG_CPU_VARIANT                   McuLib_CONFIG_CPU_VARIANT_RP2040
#define McuLib_CONFIG_SDK_VERSION_USED              McuLib_CONFIG_SDK_RPI_PICO
/* ---------------------------------------------------------------------- */
/* FreeRTOS */
#define McuLib_CONFIG_SDK_USE_FREERTOS              (1)
#define configMINIMAL_STACK_SIZE                    (500)
#define configTOTAL_HEAP_SIZE                       (64*1024)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (0)
#define INCLUDE_vTaskEndScheduler                   (1)
#define configUSE_IDLE_HOOK                         (1)
#define configUSE_TICK_HOOK                         (1)
#define configUSE_MALLOC_FAILED_HOOK                (1)
#define configCHECK_FOR_STACK_OVERFLOW              (1)
/* ---------------------------------------------------------------------------------------*/
/* McuSemihost */
#define McuSemihost_CONFIG_DEBUG_CONNECTION         McuSemihost_DEBUG_CONNECTION_SEGGER
/* ---------------------------------------------------------------------------------------*/
/* McuRdimon */
#define McuRdimon_CONFIG_IS_ENABLED       (1)       /* 1: RdiMon is enabled; 0: RdiMon is disabled*/
/* ---------------------------------------------------------------------------------------*/

#endif /* MCULIB_CONFIG_CONFIG_H_ */

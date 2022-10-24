/*
 * Copyright (c) 2016-2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option
Instructions:
 - Remove the 'Template_' from the name and place this file into your 'src' folder.
 - Include it with the -include compiler option with:  "${ProjDirPath}/source/IncludeMcuLibConfig.h"
 - Add the following to the -I compiler option:
../McuLib
../McuLib/config
../McuLib/config/fonts
../McuLib/fonts
../McuLib/src
../McuLib/FreeRTOS/Source/include
../McuLib/FreeRTOS/Source/portable/GCC/ARM_CM4F
../McuLib/SEGGER_RTT
../McuLib/SEGGER_Sysview
../McuLib/TraceRecorder
../McuLib/TraceRecorder/config
../McuLib/TraceRecorder/include
../McuLib/TraceRecorder/streamports/Jlink_RTT/include
../McuLib/HD44780
../McuLib/FatFS
../McuLib/FatFS/source

if using a CDT Build variable pointing to the library, the following can be used instead:
${MCULIB}
${MCULIB}/config
${MCULIB}/config/fonts
${MCULIB}/fonts
${MCULIB}/src
${MCULIB}/FreeRTOS/Source/include
${MCULIB}/FreeRTOS/Source/portable/GCC/ARM_CM4F
${MCULIB}/SEGGER_RTT
${MCULIB}/SEGGER_Sysview
${MCULIB}/TraceRecorder
${MCULIB}/TraceRecorder/config
${MCULIB}/TraceRecorder/include
${MCULIB}/TraceRecorder/streamports/Jlink_RTT/include
${MCULIB}/HD44780
${MCULIB}/FatFS
${MCULIB}/FatFS/source
 */

/* For ESP32 targets:
  - place the IncludeMcuLibConfig.h into the project 'config' folder
  - copy the template file McuLib\ESP32_CMakeLists.txt and rename it to McuLib\CMakeLists.text
  - add the following to your main CMakeLists.txt, between cmake_minimum_required() and the include():
list(APPEND EXTRA_COMPONENT_DIRS "../McuLib")
  - add the following after the include():
add_compile_options(-I../config)
add_compile_options(-include "../config/IncludeMcuLibConfig.h")

  - It should look similar to this:
    cmake_minimum_required(VERSION 3.5)

    list(APPEND EXTRA_COMPONENT_DIRS "../McuLib")

    include($ENV{IDF_PATH}/tools/cmake/project.cmake)

    add_compile_options(-I../config)
    add_compile_options(-include "../config/IncludeMcuLibConfig.h")

    project(idf-eclipse)

 */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

#define PL_CONFIG_IS_TINY_K22         (0) /* if set to one, run on the tinyK22, otherwise use FRDM-K22F */

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* set the CPU. See McuLibConfig.h for all supported CPUs */
#if 0 /* example configuration for LPC845 */
  #define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
  #define McuLib_CONFIG_CORTEX_M          (0)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
  #define McuLib_CONFIG_CPU_VARIANT       (McuLib_CONFIG_CPU_VARIANT_NXP_LPC845) /* for LPC need to specify the actual device */
#elif 0 /* example configuration for LPC55xx */
  #define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
  #define McuLib_CONFIG_CPU_IS_LPC55xx    (1)  /* LPC55xx */
  #define McuLib_CONFIG_CORTEX_M          (33)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
  #define McuLib_CONFIG_CPU_VARIANT       (McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S69) /* for LPC need to specify the actual device */
#elif 1 /* example configuration for Kinetis K22 */
  #define McuLib_CONFIG_CPU_IS_KINETIS    (1)  /* NXP Kinetis family */
  #define McuLib_CONFIG_CORTEX_M          (4)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
  #define McuLib_CONFIG_CPU_VARIANT       McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
#elif 0 /* example configuration for i.MX RT */
  #define McuLib_CONFIG_CPU_IS_IMXRT      (1)  /* i.MX RT family */
  #define McuLib_CONFIG_CORTEX_M          (7)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#elif 0 /* ESP32 */
  #define McuLib_CONFIG_CPU_IS_ARM_CORTEX_M   (0)  /* ESP32 is detected automatically */
  #define configHEAP_SCHEME_IDENTIFICATION    (0)  /* ESP-IDF RTOS used */
  #define McuCriticalSection_CONFIG_USE_RTOS_CRITICAL_SECTION  (1) /* no native Extensa implementation yet */
#endif
/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS       (1)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS (1)
#define configTOTAL_HEAP_SIZE                (48*1024)
#define configUSE_HEAP_SECTION_NAME          (1)
#define configHEAP_SECTION_NAME_STRING       ".bss.$SRAM_LOWER.FreeRTOS"
/* ------------------- FatFS ---------------------------*/
#define McuLib_CONFIG_USE_FAT_FS             (0)
/* ------------------- McuShell ---------------------------*/
#define McuShell_CONFIG_PROJECT_NAME_STRING              "littleFS with FRDM-K22F"
#define McuShell_CONFIG_MULTI_CMD_ENABLED                (1)
#define McuShell_CONFIG_MULTI_CMD_SIZE                   (48)
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE        (128)
/* ------------------- McuShellUart -----------------------*/
#if PL_CONFIG_IS_TINY_K22
  #define McuShellUart_CONFIG_UART        McuShellUart_CONFIG_UART_K22FN512_LPUART0_C3_C4
#else /* FRDM-K22F */
  #define McuShellUart_CONFIG_UART        McuShellUart_CONFIG_UART_K22FN512_UART1_E1_E0
#endif
/* ------------------- McuLog -----------------------*/
#define McuLog_CONFIG_IS_ENABLED                      (1)
#define McuLog_CONFIG_USE_COLOR                       (0)
#define McuLog_CONFIG_NOF_CONSOLE_LOGGER              (3) /* RTT, UART and USB CDC */
#define McuLog_CONFIG_LOG_TIMESTAMP_DATE              (0)
#define McuLog_CONFIG_USE_RTT_DATA_LOGGER             (0)
#define McuLog_CONFIG_RTT_DATA_LOGGER_BUFFER_SIZE     (128)
/* ------------------- McuTimeDate -------------------*/
#define McuTimeDate_CONFIG_USE_SOFTWARE_RTC                        (1) /* enable software RTC */
//#define McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC                     (0) /* enable external I2C RTC */
//#define McuTimeDate_CONFIG_USE_INTERNAL_HW_RTC                     (0) /* no internal RTC */
#define McuTimeDate_CONFIG_INIT_SOFTWARE_RTC_METHOD                (McuTimeDate_INIT_SOFTWARE_RTC_FROM_DEFAULTS)
//#define McuTimeDate_CONFIG_USE_GET_TIME_DATE_METHOD                (McuTimeDate_GET_TIME_DATE_METHOD_SOFTWARE_RTC)
//#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_SOFTWARE_RTC  (1) /* if using software RTC */
//#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_EXTERNAL_RTC  (1) /* if using external I2C RTC */
//#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_INTERNAL_RTC  (0) /* if using internal HW RTC */
#define McuTimeDate_CONFIG_TICK_TIME_MS    (100)
/* ------------------- McuRTT--------------------------------*/
#define McuRTT_CONFIG_RTT_UP_BUFFER_MODE              (SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP              (1024)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN            (150)
#define McuRTT_CONFIG_BLOCKING_SEND                   (1)
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS        (10)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS           (5)
/* ------------------- McuSPI --------------------------*/
#if PL_CONFIG_IS_TINY_K22
  #define MCUSPI_CONFIG_HW_TEMPLATE               MCUSPI_CONFIG_HW_TEMPLATE_KINETIS_K22_SPI1
#else /* FRDM-K22F */
  #define MCUSPI_CONFIG_HW_TEMPLATE               MCUSPI_CONFIG_HW_TEMPLATE_KINETIS_K22_SPI0
#endif
#define MCUSPI_CONFIG_TRANSFER_BAUDRATE         (4*500000U)
/* -------------------------------------------------*/
/* LittleFS */
#define LITTLEFS_CONFIG_ENABLED                 (1)
#define MCUW25Q128_CONFIG_ENABLED               (1)
#define McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE   McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_WINBOND_W25Q128
/* -------------------------------------------------*/
/* McuFlash */
#define McuFlash_CONFIG_IS_ENABLED              (0)
/* -------------------------------------------------*/
/* McuMinIni */
#define McuMinINI_CONFIG_FS                     McuMinINI_CONFIG_FS_TYPE_LITTLE_FS


#endif /* INCLUDEMCULIBCONFIG_H_ */

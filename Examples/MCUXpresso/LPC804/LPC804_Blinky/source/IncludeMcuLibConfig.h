/*
 * Copyright (c) 2016-2021, Erich Styger
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
 */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* set the CPU. See McuLibConfig.h for all supported CPUs */
#if 1 /* example configuration for LPC845 */
  #define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
  #define McuLib_CONFIG_CORTEX_M          (0)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
  #define McuLib_CONFIG_CPU_VARIANT       McuLib_CONFIG_CPU_VARIANT_NXP_LPC804
#elif 0 /* example configuration for LPC55xx */
  #define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
  #define McuLib_CONFIG_CPU_IS_LPC55xx    (1)  /* LPC55xx */
  #define McuLib_CONFIG_CORTEX_M          (33)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#elif 1 /* example configuration for Kinetis K22 */
  #define McuLib_CONFIG_CPU_IS_KINETIS    (1)  /* NXP Kinetis family */
  #define McuLib_CONFIG_CORTEX_M          (4)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#elif 0 /* example configuration for i.MX RT */
  #define McuLib_CONFIG_CPU_IS_IMXRT      (1)  /* i.MX RT family */
  #define McuLib_CONFIG_CORTEX_M          (7)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#endif

/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS       (1)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS (0)
#define configUSE_HEAP_SCHEME                (4)
#define configTOTAL_HEAP_SIZE                (2750)
#define configSUPPORT_STATIC_ALLOCATION      (0)
#define configCHECK_FOR_STACK_OVERFLOW       (0)
#define configUSE_TIMERS                     (0)
#define INCLUDE_xTimerPendFunctionCall       (0)
#define configUSE_TICKLESS_IDLE              (0)
/* ------------------- FatFS ---------------------------*/
#define McuLib_CONFIG_USE_FAT_FS             (0)
/* -----------------------------------------------------*/
/* Shell */
#define McuShellUart_CONFIG_UART              McuShellUart_CONFIG_UART_NONE
#define McuShell_CONFIG_PROJECT_NAME_STRING  "LPC804"
#define McuShell_CONFIG_PROMPT_STRING        "lpc> "
#define McuShell_CONFIG_ECHO_ENABLED         (0)
#define McuShell_CONFIG_HISTORY_ENABLED      (1)
#define McuShell_CONFIG_HISTORY_NOF_ITEMS    (3)
/* ---------------------------------------------------------------------------------------*/
/* RTT */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP       (64)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN     (32)
#define McuRTT_CONFIG_RTT_MAX_NUM_UP_BUFFERS   (1)
#define McuRTT_CONFIG_RTT_MAX_NUM_DOWN_BUFFERS (1)
/* ---------------------------------------------------------------------------------------*/
/* MinINI */
#define McuMinINI_CONFIG_FS                         (McuMinINI_CONFIG_FS_TYPE_FLASH_FS)
#define McuMinINI_CONFIG_FLASH_NVM_ADDR_START       (0x7f80-(McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS*McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE)) /* program flash goes up to 0x7f80: reduce FLASH by that size! */
#define McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE       (0x400) /* block/sector size is 1k */
#define McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS       (1)
#define McuMinINI_CONFIG_FLASH_NVM_MAX_DATA_SIZE    (64) /* must be 64, 128, 256, ... */

#endif /* INCLUDEMCULIBCONFIG_H_ */

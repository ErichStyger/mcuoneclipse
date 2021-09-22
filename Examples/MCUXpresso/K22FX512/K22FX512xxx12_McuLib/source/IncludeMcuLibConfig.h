/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option */

/* ---------------------------------------------------------------------------------------*/
/* SDK */
#define McuLib_CONFIG_CPU_IS_KINETIS                (1)
#define McuLib_CONFIG_SDK_VERSION_USED              McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* ---------------------------------------------------------------------------------------*/
/* FreeRTOS */
#define McuLib_CONFIG_SDK_USE_FREERTOS              (1)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (1)
#define configTOTAL_HEAP_SIZE                       (54*1024)
#define configUSE_HEAP_SECTION_NAME                 (1)
#define configHEAP_SECTION_NAME_STRING              ".bss.$SRAM_LOWER.FreeRTOS"
#define configQUEUE_REGISTRY_SIZE                   (15)
/* ---------------------------------------------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING         "MK22FX512"
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE   (96)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP            (4096)
/* ---------------------------------------------------------------------------------------*/

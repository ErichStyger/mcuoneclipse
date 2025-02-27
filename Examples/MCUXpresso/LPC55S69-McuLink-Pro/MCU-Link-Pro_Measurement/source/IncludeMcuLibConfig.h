/*
 * IncludeMcuLibConfig.h
 *
 *  Created on: 4 Apr 2022
 *      Author: Peter Allenspach
 * 		For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 * 		Template taken from Erich Styger's McuLib
 */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* set the CPU. See McuLibConfig.h for all supported CPUs */
#if 0                                                                      /* example configuration for LPC845 */
#define McuLib_CONFIG_CPU_IS_LPC (1)                                       /* LPC family */
#define McuLib_CONFIG_CORTEX_M (0)                                         /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#define McuLib_CONFIG_CPU_VARIANT (McuLib_CONFIG_CPU_VARIANT_NXP_LPC845)   /* for LPC need to specify the actual device */
#elif 1                                                                    /* example configuration for LPC55xx */
#define McuLib_CONFIG_CPU_IS_LPC (1)                                       /* LPC family */
#define McuLib_CONFIG_CPU_IS_LPC55xx (1)                                   /* LPC55xx */
#define McuLib_CONFIG_CORTEX_M (33)                                        /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#define McuLib_CONFIG_CPU_VARIANT (McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S69) /* for LPC need to specify the actual device */
#elif 0                                                                    /* example configuration for Kinetis K22 */
#define McuLib_CONFIG_CPU_IS_KINETIS (1)                                   /* NXP Kinetis family */
#define McuLib_CONFIG_CORTEX_M (4)                                         /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#elif 0                                                                    /* example configuration for i.MX RT */
#define McuLib_CONFIG_CPU_IS_IMXRT (1)                                     /* i.MX RT family */
#define McuLib_CONFIG_CORTEX_M (7)                                         /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#elif 0                                                                    /* ESP32 */
#define McuLib_CONFIG_CPU_IS_ARM_CORTEX_M (0)                              /* ESP32 is detected automatically */
#define configHEAP_SCHEME_IDENTIFICATION (0)                               /* ESP-IDF RTOS used */
#define McuCriticalSection_CONFIG_USE_RTOS_CRITICAL_SECTION (1)            /* no native Extensa implementation yet */
#endif
/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS          (0)
/* #define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS (1) */
/* #define configTOTAL_HEAP_SIZE                (24*1024) */
/* #define configUSE_HEAP_SECTION_NAME          (1) */
/* #define configHEAP_SECTION_NAME_STRING       ".bss.$SRAM_LOWER.FreeRTOS" */
/* ------------------- FatFS ---------------------------*/
#define McuLib_CONFIG_USE_FAT_FS (0)

#endif /* INCLUDEMCULIBCONFIG_H_ */

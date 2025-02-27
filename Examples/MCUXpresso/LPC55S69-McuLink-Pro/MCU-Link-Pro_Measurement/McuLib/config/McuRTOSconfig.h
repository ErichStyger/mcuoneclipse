/**
 * \file
 * \brief Configuration header file for FreeRTOS component
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the FreeRTOS module.
 */
 #ifndef __McuRTOS_CONFIG_H
#define __McuRTOS_CONFIG_H

#include "McuLib.h" /* SDK and API used */

/* -------------------------------------------------------------------- */
/* Macros to identify the compiler used: */
#define configCOMPILER_ARM_GCC                    1 /* GNU ARM gcc compiler */
#define configCOMPILER_ARM_IAR                    2 /* IAR ARM compiler */
#define configCOMPILER_ARM_FSL                    3 /* Legacy Freescale ARM compiler */
#define configCOMPILER_ARM_KEIL                   4 /* ARM/Keil compiler */
#define configCOMPILER_S08_FSL                    5 /* Freescale HCS08 compiler */
#define configCOMPILER_S12_FSL                    6 /* Freescale HCS12(X) compiler */
#define configCOMPILER_CF1_FSL                    7 /* Freescale ColdFire V1 compiler */
#define configCOMPILER_CF2_FSL                    8 /* Freescale ColdFire V2 compiler */
#define configCOMPILER_DSC_FSL                    9 /* Freescale DSC compiler */

#define configCOMPILER                            configCOMPILER_ARM_GCC
/* -------------------------------------------------------------------- */
/* CPU family identification */
#define configCPU_FAMILY_S08                      1   /* S08 core */
#define configCPU_FAMILY_S12                      2   /* S12(X) core */
#define configCPU_FAMILY_CF1                      3   /* ColdFire V1 core */
#define configCPU_FAMILY_CF2                      4   /* ColdFire V2 core */
#define configCPU_FAMILY_DSC                      5   /* 56800/DSC */
#define configCPU_FAMILY_ARM_M0P                  6   /* ARM Cortex-M0+ */
#define configCPU_FAMILY_ARM_M3                   7   /* ARM Cortex-M3 */
#define configCPU_FAMILY_ARM_M4                   8   /* ARM Cortex-M4 */
#define configCPU_FAMILY_ARM_M4F                  9   /* ARM Cortex-M4F (with floating point unit) */
#define configCPU_FAMILY_ARM_M7                   10  /* ARM Cortex-M7 */
#define configCPU_FAMILY_ARM_M7F                  11  /* ARM Cortex-M7F (with floating point unit) */
#define configCPU_FAMILY_ARM_M33                  12  /* ARM Cortex-M33 */
#define configCPU_FAMILY_ARM_M33F                 13  /* ARM Cortex-M33F (with floating point unit) */
#define configCPU_FAMILY_RISC_V                   14  /* RISC-V */

/* Macros to identify set of core families */
#define configCPU_FAMILY_IS_ARM_M0(fam)           ((fam)==configCPU_FAMILY_ARM_M0P)
#define configCPU_FAMILY_IS_ARM_M3(fam)           ((fam)==configCPU_FAMILY_ARM_M3)
#define configCPU_FAMILY_IS_ARM_M4(fam)           (((fam)==configCPU_FAMILY_ARM_M4)  || ((fam)==configCPU_FAMILY_ARM_M4F))
#define configCPU_FAMILY_IS_ARM_M7(fam)           (((fam)==configCPU_FAMILY_ARM_M7)  || ((fam)==configCPU_FAMILY_ARM_M7F))
#define configCPU_FAMILY_IS_ARM_M4_M7(fam)        (configCPU_FAMILY_IS_ARM_M4(fam)   || configCPU_FAMILY_IS_ARM_M7(fam))
#define configCPU_FAMILY_IS_ARM_M33(fam)          (((fam)==configCPU_FAMILY_ARM_M33) || ((fam)==configCPU_FAMILY_ARM_M33F))
#define configCPU_FAMILY_IS_ARM_FPU(fam)          (((fam)==configCPU_FAMILY_ARM_M4F) || ((fam)==configCPU_FAMILY_ARM_M7F) || ((fam)==configCPU_FAMILY_ARM_M33F))
#define configCPU_FAMILY_IS_ARM(fam)              (configCPU_FAMILY_IS_ARM_M0(fam) || configCPU_FAMILY_IS_ARM_M4(fam) || configCPU_FAMILY_IS_ARM_M7(fam) || configCPU_FAMILY_IS_ARM_M33(fam))

#if McuLib_CONFIG_CPU_IS_ARM_CORTEX_M
  /* determine core based on library configuration */
  #if McuLib_CONFIG_CORTEX_M==0
    #define configCPU_FAMILY                      configCPU_FAMILY_ARM_M0P
  #elif McuLib_CONFIG_CORTEX_M==3
    #define configCPU_FAMILY                      configCPU_FAMILY_ARM_M3
  #elif McuLib_CONFIG_CORTEX_M==4 && McuLib_CONFIG_FPU_PRESENT
    #define configCPU_FAMILY                      configCPU_FAMILY_ARM_M4F
  #elif McuLib_CONFIG_CORTEX_M==4
    #define configCPU_FAMILY                      configCPU_FAMILY_ARM_M4
  #elif McuLib_CONFIG_CORTEX_M==7 && McuLib_CONFIG_FPU_PRESENT
    #define configCPU_FAMILY                      configCPU_FAMILY_ARM_M7F
  #elif McuLib_CONFIG_CORTEX_M==7
    #define configCPU_FAMILY                      configCPU_FAMILY_ARM_M7
  #elif McuLib_CONFIG_CORTEX_M==33 && McuLib_CONFIG_FPU_PRESENT
    #define configCPU_FAMILY                      configCPU_FAMILY_ARM_M33F
  #elif McuLib_CONFIG_CORTEX_M==33
    #define configCPU_FAMILY                      configCPU_FAMILY_ARM_M33
  #else
    #error "unsupported configuaration!"
  #endif
#elif McuLib_CONFIG_CPU_IS_RISC_V
  #define configCPU_FAMILY                        configCPU_FAMILY_RISC_V
#else /* default CPU family */
  #define configCPU_FAMILY                        configCPU_FAMILY_ARM_M4F
#endif

#ifndef configENABLE_MPU
  #define configENABLE_MPU                        (0 && (configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY)||configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY)))
  /*!< 1: enable MPU support; 0: MPU support is disabled */
#endif

#ifndef configENABLE_FPU
  #define configENABLE_FPU                        (1 && McuLib_CONFIG_FPU_PRESENT)
    /*!< 1: enable FPU support; 0: FPU support is disabled */
#endif

#ifndef configENABLE_TRUSTZONE
  #define configENABLE_TRUSTZONE                  (0 && configCPU_FAMILY_IS_ARM_M33(configCPU_FAMILY))
    /*!< 1: enable ARM TrustZone support; 0: TrustZone support is disabled */
#endif

/*-----------------------------------------------------------
 * GDB backtrace handler support
 * See http://interactive.freertos.org/entries/23468301-Tasks-backtrace-switcher-viewer-snippet-for-debugger-gcc-gdb-ARM-Cortex-M3-MPU-port-Eclipse-support-
 *----------------------------------------------------------*/
#ifndef configGDB_HELPER
  #define configGDB_HELPER                        (0 && configCPU_FAMILY_IS_ARM(configCPU_FAMILY) && (configCOMPILER==configCOMPILER_ARM_GCC))
   /*!< 1: enable special GDB stack backtrace debug helper; 0: disabled */
#endif

#ifndef configLTO_HELPER
  #define configLTO_HELPER                        (1 && configCPU_FAMILY_IS_ARM(configCPU_FAMILY) && (configCOMPILER==configCOMPILER_ARM_GCC))
   /*!< 1: enable special GNU Link Time Optimizer (-lto) debug helper code; 0: disabled */
#endif

#ifndef configHEAP_SCHEME_IDENTIFICATION
  #define configHEAP_SCHEME_IDENTIFICATION        (1 && configCPU_FAMILY_IS_ARM(configCPU_FAMILY))
   /*!< 1: use constant freeRTOSMemoryScheme to identify memory scheme; 0: no constant used */
#endif

#ifndef configUSE_TOP_USED_PRIORITY
  #define configUSE_TOP_USED_PRIORITY             (1 && configCPU_FAMILY_IS_ARM(configCPU_FAMILY))
   /*!< 1: Makes sure uxTopUsedPriority is present (needed for SEGGER and OpenOCD thread aware debugging); 0: no special reference to uxTopUsedPriority */
#endif

#ifndef configLINKER_HEAP_BASE_SYMBOL
#if McuLib_CONFIG_NXP_SDK_USED
  #define configLINKER_HEAP_BASE_SYMBOL           _pvHeapStart
#else
  #define configLINKER_HEAP_BASE_SYMBOL           __HeapBase
#endif
    /*!< Linker symbol used to denote the base address of the heap, used for heap memory scheme 6 (newlib). (KDS: __HeapBase, MCUXpresso: _pvHeapStart)  */
#endif

#ifndef configLINKER_HEAP_LIMIT_SYMBOL
#if McuLib_CONFIG_NXP_SDK_USED
  #define configLINKER_HEAP_LIMIT_SYMBOL          _pvHeapLimit
#else
  #define configLINKER_HEAP_LIMIT_SYMBOL          __HeapLimit
#endif
    /*!< Linker symbol used to denote the limit address of the heap, used for heap memory scheme 6 (newlib). (KDS: __HeapLimit, MCUXpresso: _pvHeapLimit)  */
#endif

#ifndef configLINKER_HEAP_SIZE_SYMBOL
#if McuLib_CONFIG_NXP_SDK_USED
  #define configLINKER_HEAP_SIZE_SYMBOL           _HeapSize
#else
  #define configLINKER_HEAP_SIZE_SYMBOL           __heap_size
#endif
    /*!< Linker symbol used to denote the size of the heap, used for heap memory scheme 6 (newlib). (KDS: __heap_size, MCUXpresso: _HeapSize) */
#endif

#ifndef configUSE_SHELL
  #define configUSE_SHELL                         (1)
   /*!< 1: enable Shell and command line support; 0: disabled */
#endif

#ifndef configRESET_MSP
  #define configRESET_MSP                         (1)
   /*!< 1: reset MSP at scheduler start (Cortex M3/M4/M7 only); 0: do not reset MSP */
#endif

/*-----------------------------------------------------------
 * FreeRTOS Trace hook support
 *----------------------------------------------------------- */
#ifndef configUSE_PERCEPIO_TRACE_HOOKS
  #define configUSE_PERCEPIO_TRACE_HOOKS          0 /* 1: Percepio Trace hooks, 0: not using Percepio Trace hooks */
#endif
#define configUSE_TRACE_HOOKS                     configUSE_PERCEPIO_TRACE_HOOKS /* legacy configUSE_TRACE_HOOKS should not be used any more */

#ifndef configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS    0 /* 1: Segger System Viewer hooks, 0: not using Segger System Viewer hooks */
#endif

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS && configUSE_PERCEPIO_TRACE_HOOKS
  #error "only one trace method can be active!"
#endif
/*----------------------------------------------------------- */

#endif /* __McuRTOS_CONFIG_H */

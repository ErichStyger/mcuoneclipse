/**
 * \file
 * \brief Configuration header file for McuLibConfig
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the McuLibConfig module.
 */

#ifndef __McuLib_CONFIG_H
#define __McuLib_CONFIG_H

/* identification of CPU/core used. __CORTEX_M is defined in CMSIS-Core.
   Otherwise CPU Family is set automatically by Processor Expert: detected: Kinetis (supported: "Kinetis", "S32K", "HCS08")
*/
#if defined(__CORTEX_M)
  #define McuLib_CPU_IS_ARM_CORTEX_M  (1)
#else
  #define McuLib_CPU_IS_ARM_CORTEX_M  (0)
#endif

#ifndef McuLib_CONFIG_CPU_IS_ARM_CORTEX_M
  #define McuLib_CONFIG_CPU_IS_ARM_CORTEX_M             (1 || McuLib_CPU_IS_ARM_CORTEX_M)
    /*!< 1: ARM Cortex-M family, 0 otherwise */
#endif
#ifndef McuLib_CONFIG_CPU_IS_S32K
  #define McuLib_CONFIG_CPU_IS_S32K                     (0 && McuLib_CONFIG_CPU_IS_ARM_CORTEX_M)
    /*!< 1: NXP S32K CPU family, 0: otherwise */
#endif
#ifndef McuLib_CONFIG_CPU_IS_LPC
  #define McuLib_CONFIG_CPU_IS_LPC                      (0 && McuLib_CONFIG_CPU_IS_ARM_CORTEX_M)
   /*!< 1: NXP LPC CPU family, 0: otherwise */
#endif
#ifndef McuLib_CONFIG_CPU_IS_LPC55xx
  #define McuLib_CONFIG_CPU_IS_LP55Cxx                  (0 && McuLib_CONFIG_CPU_IS_ARM_CORTEX_M && McuLib_CONFIG_CPU_IS_LPC)
   /*!< 1: NXP LPC55xx CPU family, 0: otherwise */
#endif
#ifndef McuLib_CONFIG_CPU_IS_STM32
  #define McuLib_CONFIG_CPU_IS_STM32                    (0 && McuLib_CONFIG_CPU_IS_ARM_CORTEX_M)
    /*!< 1: STM32 ARM Cortex CPU family, 0: otherwise */
#endif
#ifndef McuLib_CONFIG_CPU_IS_IMXRT
  #define McuLib_CONFIG_CPU_IS_IMXRT                    (0 && McuLib_CONFIG_CPU_IS_ARM_CORTEX_M)
    /*!< 1: NXP i.Mx RT CPU family, 0: otherwise */
#endif
#ifndef McuLib_CONFIG_CPU_IS_NORDIC_NRF
  #define McuLib_CONFIG_CPU_IS_NORDIC_NRF               (0 && McuLib_CONFIG_CPU_IS_ARM_CORTEX_M)
    /*!< 1: Nordic nRF, 0: otherwise */
#endif
#ifndef McuLib_CONFIG_CPU_IS_HCS08
  #define McuLib_CONFIG_CPU_IS_HCS08                    (0 && !McuLib_CONFIG_CPU_IS_ARM_CORTEX_M)
    /*!< 1: HCS08 CPU family, 0: otherwise */
#endif
#ifndef McuLib_CONFIG_CPU_IS_RISC_V
  #define McuLib_CONFIG_CPU_IS_RISC_V                   (0 && !McuLib_CONFIG_CPU_IS_ARM_CORTEX_M)
    /*!< 1: RISC-V CPU family, 0: otherwise */
#endif
#ifndef McuLib_CONFIG_CPU_IS_RISC_V_RV32M1_RI5CY
  #define McuLib_CONFIG_CPU_IS_RISC_V_RV32M1_RI5CY      (1 && McuLib_CONFIG_CPU_IS_RISC_V)
    /*!< 1: VEGA Board: RISC-V RV32M1 RI5CY, 0: other core */
#endif
#if !defined(McuLib_CONFIG_CPU_IS_ESP32) && !defined(McuLib_CONFIG_CPU_IS_IMXRT) /* i.MX could check on __XTENSA__ in fsl_common.h */
  #ifndef __XTENSA__
    #define __XTENSA__ 0
  #endif
  #define McuLib_CONFIG_CPU_IS_ESP32                    (__XTENSA__)
    /*!< 1: ESP32 CPU family, 0: otherwise. The ESP32 compiler defines __XTENSA__ with a value of 1 */
#endif
#ifndef McuLib_CONFIG_CPU_IS_RPxxxx
  #define McuLib_CONFIG_CPU_IS_RPxxxx                  (0)  /* Raspberry Pi RP, e.g. RP2040 */
#endif

#ifndef McuLib_CONFIG_CPU_IS_KINETIS
  #define McuLib_CONFIG_CPU_IS_KINETIS                 (1 && McuLib_CONFIG_CPU_IS_ARM_CORTEX_M \
                                                            && !(McuLib_CONFIG_CPU_IS_LPC) \
                                                            && !(McuLib_CONFIG_CPU_IS_LPC55xx) \
                                                            && !(McuLib_CONFIG_CPU_IS_IMXRT) \
                                                            && !(McuLib_CONFIG_CPU_IS_STM32) \
                                                            && !(McuLib_CONFIG_CPU_IS_NORDIC_NRF) \
                                                            && !(McuLib_CONFIG_CPU_IS_S32K))
    /*!< 1: NXP Kinetis CPU family, 0: otherwise */
#endif



/* define to identify the CPU variant better */
#define McuLib_CONFIG_CPU_VARIANT_DEFAULT               (0)
#define McuLib_CONFIG_CPU_VARIANT_NXP_K02FN             (1)
#define McuLib_CONFIG_CPU_VARIANT_NXP_K22FN             (2)
#define McuLib_CONFIG_CPU_VARIANT_NXP_K22FX             (3)
#define McuLib_CONFIG_CPU_VARIANT_NXP_KE02              (4)
#define McuLib_CONFIG_CPU_VARIANT_NXP_LPC804            (5)
#define McuLib_CONFIG_CPU_VARIANT_NXP_LPC845            (6)
#define McuLib_CONFIG_CPU_VARIANT_NXP_LPC54608          (7)
#define McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16          (8)
#define McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S69          (9)
#define McuLib_CONFIG_CPU_VARIANT_NXP_IMXRT1064         (10)
#define McuLib_CONFIG_CPU_VARIANT_RP2040                (11)
#define McuLib_CONFIG_CPU_VARIANT_NXP_K64FN             (12)

#ifndef McuLib_CONFIG_CPU_VARIANT
  #define McuLib_CONFIG_CPU_VARIANT  McuLib_CONFIG_CPU_VARIANT_DEFAULT
#endif

#if McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_DEFAULT
  #error "Please specify the LPC CPU variant used"
#endif

#ifndef McuLib_CONFIG_IS_KINETIS_KE
  #define McuLib_CONFIG_IS_KINETIS_KE                   (McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_KE02)
#endif

/* identification of Cortex-M core. __FPU_USED can be defined in CMSIS-Core */
#ifndef McuLib_CONFIG_CORTEX_M
  #define McuLib_CONFIG_CORTEX_M      (4)
    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#endif
#if (1 && !defined(McuLib_CONFIG_FPU_PRESENT) && McuLib_CONFIG_CORTEX_M!=0) || (defined(__FPU_PRESENT) && (__FPU_PRESENT==1)) /* __FPU_PRESENT can be defined in CMSIS-Core */
  #define McuLib_CONFIG_FPU_PRESENT   (1)
#else
  #define McuLib_CONFIG_FPU_PRESENT   (0)
#endif
    /*!< 1: floating point unit present, 0: otherwise */
#if (1 && !defined(McuLib_CONFIG_FPU_USED) && McuLib_CONFIG_CORTEX_M!=0) || (defined(__FPU_USED) && (__FPU_USED==1)) /* __FPU_USED can be defined in CMSIS-Core */
  #define McuLib_CONFIG_FPU_USED      (1)
#else
  #define McuLib_CONFIG_FPU_USED      (0)
#endif
  /*!< 1: using floating point unit, 0: otherwise */

/* macro for little and big endianess. ARM is little endian */
#define McuLib_CONFIG_CPU_IS_LITTLE_ENDIAN   (McuLib_CONFIG_CPU_IS_ARM_CORTEX_M)

/* Identifiers used to identify the SDK */
#define McuLib_CONFIG_SDK_GENERIC             (0)
  /*!< using a generic API/SDK */
#define McuLib_CONFIG_SDK_PROCESSOR_EXPERT    (1)
  /*!< using Processor Expert SDK */
#define McuLib_CONFIG_SDK_KINETIS_1_3         (2)
  /*!< using NXP Kinetis SDK V1.3 */
#define McuLib_CONFIG_SDK_KINETIS_2_0         (3)
  /*!< using NXP Kinetis SDK V2.0 */
#define McuLib_CONFIG_SDK_MCUXPRESSO_2_0      (4)
  /*!< using NXP MCUXpresso SDK V2.x, same as Kinetis SDK v2.0 */
#define McuLib_CONFIG_SDK_S32K                (5)
  /*!< SDK for S32K */
#define McuLib_CONFIG_SDK_NORDIC_NRF5         (6)
  /*!< Nordic nRF5 SDK */
#define McuLib_CONFIG_SDK_RPI_PICO            (7)
  /*!< Raspberry Pi Pico SDK */
#define McuLib_CONFIG_SDK_LINUX               (8)
  /*!< Linux SDK, e.g. Raspberry Pi */

#ifndef McuLib_CONFIG_SDK_VERSION_MAJOR
  #define McuLib_CONFIG_SDK_VERSION_MAJOR   (2)
    /*!< SDK major version number */
#endif

#ifndef McuLib_CONFIG_SDK_VERSION_MINOR
  #define McuLib_CONFIG_SDK_VERSION_MINOR   (5)
    /*!< SDK minor version number */
#endif

#ifndef McuLib_CONFIG_SDK_VERSION_BUILD
  #define McuLib_CONFIG_SDK_VERSION_BUILD   (0)
    /*!< SDK build version number */
#endif

#ifndef McuLib_CONFIG_SDK_VERSION
  #define McuLib_CONFIG_SDK_VERSION        (McuLib_CONFIG_SDK_VERSION_MAJOR*100)+(McuLib_CONFIG_SDK_VERSION_MINOR*10)+McuLib_CONFIG_SDK_VERSION_BUILD
    /*!< Builds a single number with the SDK version (major, minor, build), e.g. 250 for 2.5.0 */
#endif

/* specify the SDK and API used */
#ifndef McuLib_CONFIG_SDK_VERSION_USED
#if McuLib_CONFIG_CPU_IS_ESP32
  #define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_GENERIC
    /*!< identify the version of SDK/API used. For ESP32 we are using a generic SDK (actually the IDF one) */
#elif McuLib_CONFIG_CPU_IS_STM32
  #define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_GENERIC
    /*!< identify the version of SDK/API used. For STM32 we are using a generic SDK (actually the CubeMX one) */
#else
  #define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_PROCESSOR_EXPERT
    /*!< identify the version of SDK/API used */
#endif
#endif


/* *****************   Middleware Configuration *******************/
/* Configuration macro if FreeRTOS is used */
#ifndef McuLib_CONFIG_SDK_USE_FREERTOS
  #define McuLib_CONFIG_SDK_USE_FREERTOS          (1)
    /*!< 1: Use FreeRTOS; 0: no FreeRTOS used */
#endif

/* FatFS */
#ifndef McuLib_CONFIG_SDK_USE_FAT_FS
  #define McuLib_CONFIG_SDK_USE_FAT_FS            (0)
    /*!< 1: Use FatFS; 0: no FatFS used */
#endif
/* ***************************************************************/

/* special macro to identify a set of SDKs used */
#define McuLib_CONFIG_NXP_SDK_USED               (   (McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_KINETIS_1_3) \
                                                  || (McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_KINETIS_2_0) \
                                                  || (McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_MCUXPRESSO_2_0) \
                                                  || (McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_S32K) \
                                                 )
  /*!< Using one of the Freescale/NXP SDKs */

#define McuLib_CONFIG_NXP_SDK_2_0_USED           (   (McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_KINETIS_2_0) \
                                                  || (McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_MCUXPRESSO_2_0) \
                                                 )
  /*!< Using Freescale/NXP SDK V2.0 */

#define McuLib_CONFIG_PEX_SDK_USED               (McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_PROCESSOR_EXPERT)
  /*!< Using Processor Expert API */

/* Compiler identification: */
#define McuLib_CONFIG_COMPILER_GNU            (0)
#define McuLib_CONFIG_COMPILER_IAR            (1)
#define McuLib_CONFIG_COMPILER_KEIL           (2)
#define McuLib_CONFIG_COMPILER_HIWARE         (3)
#define McuLib_CONFIG_COMPILER_METROWERKS     (4)

#ifndef McuLib_CONFIG_COMPILER
  #if defined(__GNUC__)
    #define McuLib_CONFIG_COMPILER                    McuLib_CONFIG_COMPILER_GNU
  #elif defined(__HIWARE__)
    #define McuLib_CONFIG_COMPILER                    McuLib_CONFIG_COMPILER_HIWARE
  #elif defined(__IAR_SYSTEMS_ICC__)
    #define McuLib_CONFIG_COMPILER                    McuLib_CONFIG_COMPILER_IAR
  #elif defined(__CC_ARM)
    #define McuLib_CONFIG_COMPILER                    McuLib_CONFIG_COMPILER_KEIL
  #elif defined(__MWERKS__)
    #define McuLib_CONFIG_COMPILER                    McuLib_CONFIG_COMPILER_METROWERKS
  #else
    #warning "a compiler needs to be defined!"
  #endif
#endif

#endif /* __McuLib_CONFIG_H */


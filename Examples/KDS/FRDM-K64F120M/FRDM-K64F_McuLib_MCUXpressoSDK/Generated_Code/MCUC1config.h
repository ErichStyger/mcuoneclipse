/**
 * \file
 * \brief Configuration header file for McuLibConfig
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the McuLibConfig module.
 */

#ifndef __MCUC1_CONFIG_H
#define __MCUC1_CONFIG_H

/* identification of CPU/core used. __CORTEX_M is defined in CMSIS-Core.
   Otherwise CPU Family is set automatically by Processor Expert: detected: Kinetis (supported: "Kinetis", "S32K", "HCS08")
*/
#if defined(__CORTEX_M)
  #define MCUC1_CPU_IS_ARM_CORTEX_M  (1)
#else
  #define MCUC1_CPU_IS_ARM_CORTEX_M  (0)
#endif

#ifndef MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M
  #define MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M             (1 || MCUC1_CPU_IS_ARM_CORTEX_M)
    /*!< 1: ARM Cortex-M family, 0 otherwise */
#endif
#ifndef MCUC1_CONFIG_CPU_IS_S32K
  #define MCUC1_CONFIG_CPU_IS_S32K                     (0 && MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M)
    /*!< 1: NXP S32K CPU family, 0: otherwise */
#endif
#ifndef MCUC1_CONFIG_CPU_IS_LPC
  #define MCUC1_CONFIG_CPU_IS_LPC                      (0 && MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M)
   /*!< 1: NXP LPC CPU family, 0: otherwise */
#endif
#ifndef MCUC1_CONFIG_CPU_IS_LPC55xx
  #define MCUC1_CONFIG_CPU_IS_LP55Cxx                  (0 && MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M && MCUC1_CONFIG_CPU_IS_LPC)
   /*!< 1: NXP LPC55xx CPU family, 0: otherwise */
#endif
#ifndef MCUC1_CONFIG_CPU_IS_STM32
  #define MCUC1_CONFIG_CPU_IS_STM32                    (0 && MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M)
    /*!< 1: STM32 ARM Cortex CPU family, 0: otherwise */
#endif
#ifndef MCUC1_CONFIG_CPU_IS_IMXRT
  #define MCUC1_CONFIG_CPU_IS_IMXRT                    (0 && MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M)
    /*!< 1: NXP i.Mx RT CPU family, 0: otherwise */
#endif
#ifndef MCUC1_CONFIG_CPU_IS_NORDIC_NRF
  #define MCUC1_CONFIG_CPU_IS_NORDIC_NRF               (0 && MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M)
    /*!< 1: Nordic nRF, 0: otherwise */
#endif
#ifndef MCUC1_CONFIG_CPU_IS_HCS08
  #define MCUC1_CONFIG_CPU_IS_HCS08                    (0 && !MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M)
    /*!< 1: HCS08 CPU family, 0: otherwise */
#endif
#ifndef MCUC1_CONFIG_CPU_IS_RISC_V
  #define MCUC1_CONFIG_CPU_IS_RISC_V                   (0 && !MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M)
    /*!< 1: RISC-V CPU family, 0: otherwise */
#endif
#ifndef MCUC1_CONFIG_CPU_IS_RISC_V_RV32M1_RI5CY
  #define MCUC1_CONFIG_CPU_IS_RISC_V_RV32M1_RI5CY      (1 && MCUC1_CONFIG_CPU_IS_RISC_V)
    /*!< 1: VEGA Board: RISC-V RV32M1 RI5CY, 0: other core */
#endif
#if !defined(MCUC1_CONFIG_CPU_IS_ESP32) && !defined(MCUC1_CONFIG_CPU_IS_IMXRT) /* i.MX could check on __XTENSA__ in fsl_common.h */

  #ifndef __XTENSA__
    #define __XTENSA__ 0
  #endif
  #define MCUC1_CONFIG_CPU_IS_ESP32                    (__XTENSA__)
    /*!< 1: ESP32 CPU family, 0: otherwise. The ESP32 compiler defines __XTENSA__ with a value of 1 */
#endif
#ifndef MCUC1_CONFIG_CPU_IS_RPxxxx
  #define MCUC1_CONFIG_CPU_IS_RPxxxx                  (0)  /* Raspberry Pi RP, e.g. RP2040 */
#endif

#ifndef MCUC1_CONFIG_CPU_IS_KINETIS
  #define MCUC1_CONFIG_CPU_IS_KINETIS                 (1 && MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M \
                                                            && !(MCUC1_CONFIG_CPU_IS_LPC) \
                                                            && !(MCUC1_CONFIG_CPU_IS_LPC55xx) \
                                                            && !(MCUC1_CONFIG_CPU_IS_IMXRT) \
                                                            && !(MCUC1_CONFIG_CPU_IS_STM32) \
                                                            && !(MCUC1_CONFIG_CPU_IS_NORDIC_NRF) \
                                                            && !(MCUC1_CONFIG_CPU_IS_S32K))
    /*!< 1: NXP Kinetis CPU family, 0: otherwise */
#endif



/* define to identify the CPU variant better */
#define MCUC1_CONFIG_CPU_VARIANT_DEFAULT               (0)
#define MCUC1_CONFIG_CPU_VARIANT_NXP_K02FN             (1)
#define MCUC1_CONFIG_CPU_VARIANT_NXP_K22FN             (2)
#define MCUC1_CONFIG_CPU_VARIANT_NXP_K22FX             (3)
#define MCUC1_CONFIG_CPU_VARIANT_NXP_KE02              (4)
#define MCUC1_CONFIG_CPU_VARIANT_NXP_LPC804            (5)
#define MCUC1_CONFIG_CPU_VARIANT_NXP_LPC845            (6)
#define MCUC1_CONFIG_CPU_VARIANT_NXP_LPC54608          (7)
#define MCUC1_CONFIG_CPU_VARIANT_NXP_LPC55S16          (8)
#define MCUC1_CONFIG_CPU_VARIANT_NXP_LPC55S69          (9)
#define MCUC1_CONFIG_CPU_VARIANT_NXP_IMXRT1064         (10)
#define MCUC1_CONFIG_CPU_VARIANT_RP2040                (11)

#ifndef MCUC1_CONFIG_CPU_VARIANT
  #define MCUC1_CONFIG_CPU_VARIANT  MCUC1_CONFIG_CPU_VARIANT_DEFAULT
#endif

#if MCUC1_CONFIG_CPU_IS_LPC && MCUC1_CONFIG_CPU_VARIANT==MCUC1_CONFIG_CPU_VARIANT_DEFAULT
  #error "Please specify the LPC CPU variant used"
#endif

#ifndef MCUC1_CONFIG_IS_KINETIS_KE
  #define MCUC1_CONFIG_IS_KINETIS_KE                   (MCUC1_CONFIG_CPU_VARIANT==MCUC1_CONFIG_CPU_VARIANT_NXP_KE02)
#endif

/* identification of Cortex-M core. __FPU_USED can be defined in CMSIS-Core */
#ifndef MCUC1_CONFIG_CORTEX_M
  #define MCUC1_CONFIG_CORTEX_M      (4)
    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#endif
#if (1 && !defined(MCUC1_CONFIG_FPU_PRESENT) && MCUC1_CONFIG_CORTEX_M!=0) || (defined(__FPU_PRESENT) && (__FPU_PRESENT==1)) /* __FPU_PRESENT can be defined in CMSIS-Core */
  #define MCUC1_CONFIG_FPU_PRESENT   (1)
#else
  #define MCUC1_CONFIG_FPU_PRESENT   (0)
#endif
    /*!< 1: floating point unit present, 0: otherwise */
#if (1 && !defined(MCUC1_CONFIG_FPU_USED) && MCUC1_CONFIG_CORTEX_M!=0) || (defined(__FPU_USED) && (__FPU_USED==1)) /* __FPU_USED can be defined in CMSIS-Core */
  #define MCUC1_CONFIG_FPU_USED      (1)
#else
  #define MCUC1_CONFIG_FPU_USED      (0)
#endif
  /*!< 1: using floating point unit, 0: otherwise */

/* macro for little and big endianess. ARM is little endian */
#define MCUC1_CONFIG_CPU_IS_LITTLE_ENDIAN   (MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M)

/* Identifiers used to identify the SDK */
#define MCUC1_CONFIG_SDK_GENERIC             (0)
  /*!< using a generic API/SDK */
#define MCUC1_CONFIG_SDK_PROCESSOR_EXPERT    (1)
  /*!< using Processor Expert SDK */
#define MCUC1_CONFIG_SDK_KINETIS_1_3         (2)
  /*!< using NXP Kinetis SDK V1.3 */
#define MCUC1_CONFIG_SDK_KINETIS_2_0         (3)
  /*!< using NXP Kinetis SDK V2.0 */
#define MCUC1_CONFIG_SDK_MCUXPRESSO_2_0      (4)
  /*!< using NXP MCUXpresso SDK V2.x, same as Kinetis SDK v2.0 */
#define MCUC1_CONFIG_SDK_S32K                (5)
  /*!< SDK for S32K */
#define MCUC1_CONFIG_SDK_NORDIC_NRF5         (6)
  /*!< Nordic nRF5 SDK */
#define MCUC1_CONFIG_SDK_RPI_PICO            (7)
  /*!< Raspberry Pi Pico SDK */
#define MCUC1_CONFIG_SDK_LINUX               (8)
  /*!< Linux SDK, e.g. Raspberry Pi */

#ifndef MCUC1_CONFIG_SDK_VERSION_MAJOR
  #define MCUC1_CONFIG_SDK_VERSION_MAJOR   (2)
    /*!< SDK major version number */
#endif

#ifndef MCUC1_CONFIG_SDK_VERSION_MINOR
  #define MCUC1_CONFIG_SDK_VERSION_MINOR   (2)
    /*!< SDK minor version number */
#endif

#ifndef MCUC1_CONFIG_SDK_VERSION_BUILD
  #define MCUC1_CONFIG_SDK_VERSION_BUILD   (0)
    /*!< SDK build version number */
#endif

#ifndef MCUC1_CONFIG_SDK_VERSION
  #define MCUC1_CONFIG_SDK_VERSION        (MCUC1_CONFIG_SDK_VERSION_MAJOR*100)+(MCUC1_CONFIG_SDK_VERSION_MINOR*10)+MCUC1_CONFIG_SDK_VERSION_BUILD
    /*!< Builds a single number with the SDK version (major, minor, build), e.g. 250 for 2.5.0 */
#endif

/* specify the SDK and API used */
#ifndef MCUC1_CONFIG_SDK_VERSION_USED
#if MCUC1_CONFIG_CPU_IS_ESP32
  #define MCUC1_CONFIG_SDK_VERSION_USED  MCUC1_CONFIG_SDK_GENERIC
    /*!< identify the version of SDK/API used. For ESP32 we are using a generic SDK (actually the IDF one) */
#elif MCUC1_CONFIG_CPU_IS_STM32
  #define MCUC1_CONFIG_SDK_VERSION_USED  MCUC1_CONFIG_SDK_GENERIC
    /*!< identify the version of SDK/API used. For STM32 we are using a generic SDK (actually the CubeMX one) */
#else
  #define MCUC1_CONFIG_SDK_VERSION_USED  MCUC1_CONFIG_SDK_MCUXPRESSO_2_0
    /*!< identify the version of SDK/API used */
#endif
#endif


/* *****************   Middleware Configuration *******************/
/* Configuration macro if FreeRTOS is used */
#ifndef MCUC1_CONFIG_SDK_USE_FREERTOS
  #define MCUC1_CONFIG_SDK_USE_FREERTOS           (1)
    /*!< 1: Use FreeRTOS; 0: no FreeRTOS used */
#endif

/* FatFS */
#ifndef MCUC1_CONFIG_SDK_USE_FAT_FS
  #define MCUC1_CONFIG_SDK_USE_FAT_FS             (0)
    /*!< 1: Use FatFS; 0: no FatFS used */
#endif
/* ***************************************************************/

/* special macro to identify a set of SDKs used */
#define MCUC1_CONFIG_NXP_SDK_USED                (   (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_KINETIS_1_3) \
                                                  || (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_KINETIS_2_0) \
                                                  || (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_MCUXPRESSO_2_0) \
                                                  || (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_S32K) \
                                                 )
  /*!< Using one of the Freescale/NXP SDKs */

#define MCUC1_CONFIG_NXP_SDK_2_0_USED            (   (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_KINETIS_2_0) \
                                                  || (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_MCUXPRESSO_2_0) \
                                                 )
  /*!< Using Freescale/NXP SDK V2.0 */

#define MCUC1_CONFIG_PEX_SDK_USED                (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_PROCESSOR_EXPERT)
  /*!< Using Processor Expert API */

/* Compiler identification: */
#define MCUC1_CONFIG_COMPILER_GNU            (0)
#define MCUC1_CONFIG_COMPILER_IAR            (1)
#define MCUC1_CONFIG_COMPILER_KEIL           (2)
#define MCUC1_CONFIG_COMPILER_HIWARE         (3)
#define MCUC1_CONFIG_COMPILER_METROWERKS     (4)

#ifndef MCUC1_CONFIG_COMPILER
  #if defined(__GNUC__)
    #define MCUC1_CONFIG_COMPILER                    MCUC1_CONFIG_COMPILER_GNU
  #elif defined(__HIWARE__)
    #define MCUC1_CONFIG_COMPILER                    MCUC1_CONFIG_COMPILER_HIWARE
  #elif defined(__IAR_SYSTEMS_ICC__)
    #define MCUC1_CONFIG_COMPILER                    MCUC1_CONFIG_COMPILER_IAR
  #elif defined(__CC_ARM)
    #define MCUC1_CONFIG_COMPILER                    MCUC1_CONFIG_COMPILER_KEIL
  #elif defined(__MWERKS__)
    #define MCUC1_CONFIG_COMPILER                    MCUC1_CONFIG_COMPILER_METROWERKS
  #else
    #warning "a compiler needs to be defined!"
  #endif
#endif

#endif /* __MCUC1_CONFIG_H */


/*
** ###################################################################
**     Processors:          LPC55S16JBD100
**                          LPC55S16JBD64
**                          LPC55S16JEV59
**                          LPC55S16JEV98
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    LPC55S1x/LPC551x User manual Rev.0.6  15 November 2019
**     Version:             rev. 1.1, 2019-12-03
**     Build:               b240704
**
**     Abstract:
**         CMSIS Peripheral Access Layer for LPC55S16
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2024 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2018-08-22)
**         Initial version based on v0.2UM
**     - rev. 1.1 (2019-12-03)
**         Initial version based on v0.6UM
**
** ###################################################################
*/

/*!
 * @file LPC55S16_COMMON.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for LPC55S16
 *
 * CMSIS Peripheral Access Layer for LPC55S16
 */

#if !defined(LPC55S16_COMMON_H_)
#define LPC55S16_COMMON_H_                       /**< Symbol preventing repeated inclusion */

/** Memory map major version (memory maps with equal major version number are
 * compatible) */
#define MCU_MEM_MAP_VERSION 0x0100U
/** Memory map minor version */
#define MCU_MEM_MAP_VERSION_MINOR 0x0001U


/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
#define NUMBER_OF_INT_VECTORS 77                 /**< Number of interrupts in the Vector table */

typedef enum IRQn {
  /* Auxiliary constants */
  NotAvail_IRQn                = -128,             /**< Not available device specific interrupt */

  /* Core interrupts */
  NonMaskableInt_IRQn          = -14,              /**< Non Maskable Interrupt */
  HardFault_IRQn               = -13,              /**< Cortex-M33 SV Hard Fault Interrupt */
  MemoryManagement_IRQn        = -12,              /**< Cortex-M33 Memory Management Interrupt */
  BusFault_IRQn                = -11,              /**< Cortex-M33 Bus Fault Interrupt */
  UsageFault_IRQn              = -10,              /**< Cortex-M33 Usage Fault Interrupt */
  SecureFault_IRQn             = -9,               /**< Cortex-M33 Secure Fault Interrupt */
  SVCall_IRQn                  = -5,               /**< Cortex-M33 SV Call Interrupt */
  DebugMonitor_IRQn            = -4,               /**< Cortex-M33 Debug Monitor Interrupt */
  PendSV_IRQn                  = -2,               /**< Cortex-M33 Pend SV Interrupt */
  SysTick_IRQn                 = -1,               /**< Cortex-M33 System Tick Interrupt */

  /* Device specific interrupts */
  WDT_BOD_IRQn                 = 0,                /**< Windowed watchdog timer, Brownout detect, Flash interrupt */
  DMA0_IRQn                    = 1,                /**< DMA0 controller */
  GINT0_IRQn                   = 2,                /**< GPIO group 0 */
  GINT1_IRQn                   = 3,                /**< GPIO group 1 */
  PIN_INT0_IRQn                = 4,                /**< Pin interrupt 0 or pattern match engine slice 0 */
  PIN_INT1_IRQn                = 5,                /**< Pin interrupt 1or pattern match engine slice 1 */
  PIN_INT2_IRQn                = 6,                /**< Pin interrupt 2 or pattern match engine slice 2 */
  PIN_INT3_IRQn                = 7,                /**< Pin interrupt 3 or pattern match engine slice 3 */
  UTICK0_IRQn                  = 8,                /**< Micro-tick Timer */
  MRT0_IRQn                    = 9,                /**< Multi-rate timer */
  CTIMER0_IRQn                 = 10,               /**< Standard counter/timer CTIMER0 */
  CTIMER1_IRQn                 = 11,               /**< Standard counter/timer CTIMER1 */
  SCT0_IRQn                    = 12,               /**< SCTimer/PWM */
  CTIMER3_IRQn                 = 13,               /**< Standard counter/timer CTIMER3 */
  FLEXCOMM0_IRQn               = 14,               /**< Flexcomm Interface 0 (USART, SPI, I2C, I2S, FLEXCOMM) */
  FLEXCOMM1_IRQn               = 15,               /**< Flexcomm Interface 1 (USART, SPI, I2C, I2S, FLEXCOMM) */
  FLEXCOMM2_IRQn               = 16,               /**< Flexcomm Interface 2 (USART, SPI, I2C, I2S, FLEXCOMM) */
  FLEXCOMM3_IRQn               = 17,               /**< Flexcomm Interface 3 (USART, SPI, I2C, I2S, FLEXCOMM) */
  FLEXCOMM4_IRQn               = 18,               /**< Flexcomm Interface 4 (USART, SPI, I2C, I2S, FLEXCOMM) */
  FLEXCOMM5_IRQn               = 19,               /**< Flexcomm Interface 5 (USART, SPI, I2C, I2S, FLEXCOMM) */
  FLEXCOMM6_IRQn               = 20,               /**< Flexcomm Interface 6 (USART, SPI, I2C, I2S, FLEXCOMM) */
  FLEXCOMM7_IRQn               = 21,               /**< Flexcomm Interface 7 (USART, SPI, I2C, I2S, FLEXCOMM) */
  ADC0_IRQn                    = 22,               /**< ADC0  */
  Reserved39_IRQn              = 23,               /**< Reserved interrupt */
  ACMP_IRQn                    = 24,               /**< ACMP interrupts */
  Reserved41_IRQn              = 25,               /**< Reserved interrupt */
  Reserved42_IRQn              = 26,               /**< Reserved interrupt */
  USB0_NEEDCLK_IRQn            = 27,               /**< USB Activity Wake-up Interrupt */
  USB0_IRQn                    = 28,               /**< USB device */
  RTC_IRQn                     = 29,               /**< RTC alarm and wake-up interrupts */
  Reserved46_IRQn              = 30,               /**< Reserved interrupt */
  Reserved47_IRQn              = 31,               /**< Reserved interrupt */
  PIN_INT4_IRQn                = 32,               /**< Pin interrupt 4 or pattern match engine slice 4 int */
  PIN_INT5_IRQn                = 33,               /**< Pin interrupt 5 or pattern match engine slice 5 int */
  PIN_INT6_IRQn                = 34,               /**< Pin interrupt 6 or pattern match engine slice 6 int */
  PIN_INT7_IRQn                = 35,               /**< Pin interrupt 7 or pattern match engine slice 7 int */
  CTIMER2_IRQn                 = 36,               /**< Standard counter/timer CTIMER2 */
  CTIMER4_IRQn                 = 37,               /**< Standard counter/timer CTIMER4 */
  OS_EVENT_IRQn                = 38,               /**< OS_EVENT_TIMER and OS_EVENT_WAKEUP interrupts */
  Reserved55_IRQn              = 39,               /**< Reserved interrupt */
  Reserved56_IRQn              = 40,               /**< Reserved interrupt */
  Reserved57_IRQn              = 41,               /**< Reserved interrupt */
  Reserved58_IRQn              = 42,               /**< Reserved interrupt */
  CAN0_IRQ0_IRQn               = 43,               /**< CAN0 interrupt0 */
  CAN0_IRQ1_IRQn               = 44,               /**< CAN0 interrupt1 */
  Reserved61_IRQn              = 45,               /**< Reserved interrupt */
  USB1_PHY_IRQn                = 46,               /**< USB1_PHY */
  USB1_IRQn                    = 47,               /**< USB1 interrupt */
  USB1_NEEDCLK_IRQn            = 48,               /**< USB1 activity */
  SEC_HYPERVISOR_CALL_IRQn     = 49,               /**< SEC_HYPERVISOR_CALL interrupt */
  SEC_GPIO_INT0_IRQ0_IRQn      = 50,               /**< SEC_GPIO_INT0_IRQ0 interrupt */
  SEC_GPIO_INT0_IRQ1_IRQn      = 51,               /**< SEC_GPIO_INT0_IRQ1 interrupt */
  PLU_IRQn                     = 52,               /**< PLU interrupt */
  SEC_VIO_IRQn                 = 53,               /**< SEC_VIO interrupt */
  HASHCRYPT_IRQn               = 54,               /**< SHA interrupt */
  CASER_IRQn                   = 55,               /**< CASPER interrupt */
  PUF_IRQn                     = 56,               /**< PUF interrupt */
  Reserved73_IRQn              = 57,               /**< Reserved interrupt */
  DMA1_IRQn                    = 58,               /**< DMA1 interrupt */
  FLEXCOMM8_IRQn               = 59,               /**< Flexcomm Interface 8 (SPI, , FLEXCOMM) */
  CDOG_IRQn                    = 60                /**< CDOG interrupt */
} IRQn_Type;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */


/* ----------------------------------------------------------------------------
   -- Cortex M33 Core Configuration
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Cortex_Core_Configuration Cortex M33 Core Configuration
 * @{
 */

#define __MPU_PRESENT                  1         /**< Defines if an MPU is present or not */
#define __NVIC_PRIO_BITS               3         /**< Number of priority bits implemented in the NVIC */
#define __Vendor_SysTickConfig         0         /**< Vendor specific implementation of SysTickConfig is defined */
#define __FPU_PRESENT                  1         /**< Defines if an FPU is present or not */
#define __DSP_PRESENT                  1         /**< Defines if Armv8-M Mainline core supports DSP instructions */
#define __SAUREGION_PRESENT            1         /**< Defines if an SAU is present or not */

#include "core_cm33.h"                 /* Core Peripheral Access Layer */
#include "system_LPC55S16.h"           /* Device specific configuration file */

#define LPC55S16_SERIES
/* CPU specific feature definitions */
#include "LPC55S16_features.h"

/*!
 * @}
 */ /* end of group Cortex_Core_Configuration */


/* ADC - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral ADC0 base address */
  #define ADC0_BASE                                (0x500A0000u)
  /** Peripheral ADC0 base address */
  #define ADC0_BASE_NS                             (0x400A0000u)
  /** Peripheral ADC0 base pointer */
  #define ADC0                                     ((ADC_Type *)ADC0_BASE)
  /** Peripheral ADC0 base pointer */
  #define ADC0_NS                                  ((ADC_Type *)ADC0_BASE_NS)
  /** Array initializer of ADC peripheral base addresses */
  #define ADC_BASE_ADDRS                           { ADC0_BASE }
  /** Array initializer of ADC peripheral base pointers */
  #define ADC_BASE_PTRS                            { ADC0 }
  /** Array initializer of ADC peripheral base addresses */
  #define ADC_BASE_ADDRS_NS                        { ADC0_BASE_NS }
  /** Array initializer of ADC peripheral base pointers */
  #define ADC_BASE_PTRS_NS                         { ADC0_NS }
#else
  /** Peripheral ADC0 base address */
  #define ADC0_BASE                                (0x400A0000u)
  /** Peripheral ADC0 base pointer */
  #define ADC0                                     ((ADC_Type *)ADC0_BASE)
  /** Array initializer of ADC peripheral base addresses */
  #define ADC_BASE_ADDRS                           { ADC0_BASE }
  /** Array initializer of ADC peripheral base pointers */
  #define ADC_BASE_PTRS                            { ADC0 }
#endif
/** Interrupt vectors for the ADC peripheral type */
#define ADC_IRQS                                 { ADC0_IRQn }

/* AHB_SECURE_CTRL - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral AHB_SECURE_CTRL base address */
  #define AHB_SECURE_CTRL_BASE                     (0x500AC000u)
  /** Peripheral AHB_SECURE_CTRL base address */
  #define AHB_SECURE_CTRL_BASE_NS                  (0x400AC000u)
  /** Peripheral AHB_SECURE_CTRL base pointer */
  #define AHB_SECURE_CTRL                          ((AHB_SECURE_CTRL_Type *)AHB_SECURE_CTRL_BASE)
  /** Peripheral AHB_SECURE_CTRL base pointer */
  #define AHB_SECURE_CTRL_NS                       ((AHB_SECURE_CTRL_Type *)AHB_SECURE_CTRL_BASE_NS)
  /** Array initializer of AHB_SECURE_CTRL peripheral base addresses */
  #define AHB_SECURE_CTRL_BASE_ADDRS               { AHB_SECURE_CTRL_BASE }
  /** Array initializer of AHB_SECURE_CTRL peripheral base pointers */
  #define AHB_SECURE_CTRL_BASE_PTRS                { AHB_SECURE_CTRL }
  /** Array initializer of AHB_SECURE_CTRL peripheral base addresses */
  #define AHB_SECURE_CTRL_BASE_ADDRS_NS            { AHB_SECURE_CTRL_BASE_NS }
  /** Array initializer of AHB_SECURE_CTRL peripheral base pointers */
  #define AHB_SECURE_CTRL_BASE_PTRS_NS             { AHB_SECURE_CTRL_NS }
#else
  /** Peripheral AHB_SECURE_CTRL base address */
  #define AHB_SECURE_CTRL_BASE                     (0x400AC000u)
  /** Peripheral AHB_SECURE_CTRL base pointer */
  #define AHB_SECURE_CTRL                          ((AHB_SECURE_CTRL_Type *)AHB_SECURE_CTRL_BASE)
  /** Array initializer of AHB_SECURE_CTRL peripheral base addresses */
  #define AHB_SECURE_CTRL_BASE_ADDRS               { AHB_SECURE_CTRL_BASE }
  /** Array initializer of AHB_SECURE_CTRL peripheral base pointers */
  #define AHB_SECURE_CTRL_BASE_PTRS                { AHB_SECURE_CTRL }
#endif
/* AHB_SECURE_CTRL Mirror address */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral AHB_SECURE_CTRL base address */
  #define AHB_SECURE_CTRL_ALIAS1_BASE              (0x500AD000u)
  /** Peripheral AHB_SECURE_CTRL base address */
  #define AHB_SECURE_CTRL_ALIAS1_BASE_NS           (0x400AD000u)
  /** Peripheral AHB_SECURE_CTRL base pointer */
  #define AHB_SECURE_CTRL_ALIAS1                   ((AHB_SECURE_CTRL_Type *)AHB_SECURE_CTRL_ALIAS1_BASE)
  /** Peripheral AHB_SECURE_CTRL base pointer */
  #define AHB_SECURE_CTRL_ALIAS1_NS                ((AHB_SECURE_CTRL_Type *)AHB_SECURE_CTRL_ALIAS1_BASE_NS)
  /** Peripheral AHB_SECURE_CTRL base address */
  #define AHB_SECURE_CTRL_ALIAS2_BASE              (0x500AE000u)
  /** Peripheral AHB_SECURE_CTRL base address */
  #define AHB_SECURE_CTRL_ALIAS2_BASE_NS           (0x400AE000u)
  /** Peripheral AHB_SECURE_CTRL base pointer */
  #define AHB_SECURE_CTRL_ALIAS2                   ((AHB_SECURE_CTRL_Type *)AHB_SECURE_CTRL_ALIAS2_BASE)
  /** Peripheral AHB_SECURE_CTRL base pointer */
  #define AHB_SECURE_CTRL_ALIAS2_NS                ((AHB_SECURE_CTRL_Type *)AHB_SECURE_CTRL_ALIAS2_BASE_NS)
  /** Peripheral AHB_SECURE_CTRL base address */
  #define AHB_SECURE_CTRL_ALIAS3_BASE              (0x500AF000u)
  /** Peripheral AHB_SECURE_CTRL base address */
  #define AHB_SECURE_CTRL_ALIAS3_BASE_NS           (0x400AF000u)
  /** Peripheral AHB_SECURE_CTRL base pointer */
  #define AHB_SECURE_CTRL_ALIAS3                   ((AHB_SECURE_CTRL_Type *)AHB_SECURE_CTRL_ALIAS3_BASE)
  /** Peripheral AHB_SECURE_CTRL base pointer */
  #define AHB_SECURE_CTRL_ALIAS3_NS                ((AHB_SECURE_CTRL_Type *)AHB_SECURE_CTRL_ALIAS3_BASE_NS)
#else
  /** Peripheral AHB_SECURE_CTRL base address */
  #define AHB_SECURE_CTRL_ALIAS1_BASE              (0x400AD000u)
  /** Peripheral AHB_SECURE_CTRL base pointer */
  #define AHB_SECURE_CTRL_ALIAS1                   ((AHB_SECURE_CTRL_Type *)AHB_SECURE_CTRL_ALIAS1_BASE)
  /** Peripheral AHB_SECURE_CTRL base address */
  #define AHB_SECURE_CTRL_ALIAS2_BASE              (0x400AE000u)
  /** Peripheral AHB_SECURE_CTRL base pointer */
  #define AHB_SECURE_CTRL_ALIAS2                   ((AHB_SECURE_CTRL_Type *)AHB_SECURE_CTRL_ALIAS2_BASE)
  /** Peripheral AHB_SECURE_CTRL base address */
  #define AHB_SECURE_CTRL_ALIAS3_BASE              (0x400AF000u)
  /** Peripheral AHB_SECURE_CTRL base pointer */
  #define AHB_SECURE_CTRL_ALIAS3                   ((AHB_SECURE_CTRL_Type *)AHB_SECURE_CTRL_ALIAS3_BASE)
 #endif


/* ANACTRL - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral ANACTRL base address */
  #define ANACTRL_BASE                             (0x50013000u)
  /** Peripheral ANACTRL base address */
  #define ANACTRL_BASE_NS                          (0x40013000u)
  /** Peripheral ANACTRL base pointer */
  #define ANACTRL                                  ((ANACTRL_Type *)ANACTRL_BASE)
  /** Peripheral ANACTRL base pointer */
  #define ANACTRL_NS                               ((ANACTRL_Type *)ANACTRL_BASE_NS)
  /** Array initializer of ANACTRL peripheral base addresses */
  #define ANACTRL_BASE_ADDRS                       { ANACTRL_BASE }
  /** Array initializer of ANACTRL peripheral base pointers */
  #define ANACTRL_BASE_PTRS                        { ANACTRL }
  /** Array initializer of ANACTRL peripheral base addresses */
  #define ANACTRL_BASE_ADDRS_NS                    { ANACTRL_BASE_NS }
  /** Array initializer of ANACTRL peripheral base pointers */
  #define ANACTRL_BASE_PTRS_NS                     { ANACTRL_NS }
#else
  /** Peripheral ANACTRL base address */
  #define ANACTRL_BASE                             (0x40013000u)
  /** Peripheral ANACTRL base pointer */
  #define ANACTRL                                  ((ANACTRL_Type *)ANACTRL_BASE)
  /** Array initializer of ANACTRL peripheral base addresses */
  #define ANACTRL_BASE_ADDRS                       { ANACTRL_BASE }
  /** Array initializer of ANACTRL peripheral base pointers */
  #define ANACTRL_BASE_PTRS                        { ANACTRL }
#endif

/* CAN - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral CAN0 base address */
  #define CAN0_BASE                                (0x5009D000u)
  /** Peripheral CAN0 base address */
  #define CAN0_BASE_NS                             (0x4009D000u)
  /** Peripheral CAN0 base pointer */
  #define CAN0                                     ((CAN_Type *)CAN0_BASE)
  /** Peripheral CAN0 base pointer */
  #define CAN0_NS                                  ((CAN_Type *)CAN0_BASE_NS)
  /** Array initializer of CAN peripheral base addresses */
  #define CAN_BASE_ADDRS                           { CAN0_BASE }
  /** Array initializer of CAN peripheral base pointers */
  #define CAN_BASE_PTRS                            { CAN0 }
  /** Array initializer of CAN peripheral base addresses */
  #define CAN_BASE_ADDRS_NS                        { CAN0_BASE_NS }
  /** Array initializer of CAN peripheral base pointers */
  #define CAN_BASE_PTRS_NS                         { CAN0_NS }
#else
  /** Peripheral CAN0 base address */
  #define CAN0_BASE                                (0x4009D000u)
  /** Peripheral CAN0 base pointer */
  #define CAN0                                     ((CAN_Type *)CAN0_BASE)
  /** Array initializer of CAN peripheral base addresses */
  #define CAN_BASE_ADDRS                           { CAN0_BASE }
  /** Array initializer of CAN peripheral base pointers */
  #define CAN_BASE_PTRS                            { CAN0 }
#endif
/** Interrupt vectors for the CAN peripheral type */
#define CAN_IRQS                                 { { CAN0_IRQ0_IRQn, CAN0_IRQ1_IRQn } }

/* CASPER - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral CASPER base address */
  #define CASPER_BASE                              (0x500A5000u)
  /** Peripheral CASPER base address */
  #define CASPER_BASE_NS                           (0x400A5000u)
  /** Peripheral CASPER base pointer */
  #define CASPER                                   ((CASPER_Type *)CASPER_BASE)
  /** Peripheral CASPER base pointer */
  #define CASPER_NS                                ((CASPER_Type *)CASPER_BASE_NS)
  /** Array initializer of CASPER peripheral base addresses */
  #define CASPER_BASE_ADDRS                        { CASPER_BASE }
  /** Array initializer of CASPER peripheral base pointers */
  #define CASPER_BASE_PTRS                         { CASPER }
  /** Array initializer of CASPER peripheral base addresses */
  #define CASPER_BASE_ADDRS_NS                     { CASPER_BASE_NS }
  /** Array initializer of CASPER peripheral base pointers */
  #define CASPER_BASE_PTRS_NS                      { CASPER_NS }
#else
  /** Peripheral CASPER base address */
  #define CASPER_BASE                              (0x400A5000u)
  /** Peripheral CASPER base pointer */
  #define CASPER                                   ((CASPER_Type *)CASPER_BASE)
  /** Array initializer of CASPER peripheral base addresses */
  #define CASPER_BASE_ADDRS                        { CASPER_BASE }
  /** Array initializer of CASPER peripheral base pointers */
  #define CASPER_BASE_PTRS                         { CASPER }
#endif
/** Interrupt vectors for the CASPER peripheral type */
#define CASPER_IRQS                              { CASER_IRQn }

/* CDOG - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral CDOG base address */
  #define CDOG_BASE                                (0x500A1000u)
  /** Peripheral CDOG base address */
  #define CDOG_BASE_NS                             (0x400A1000u)
  /** Peripheral CDOG base pointer */
  #define CDOG                                     ((CDOG_Type *)CDOG_BASE)
  /** Peripheral CDOG base pointer */
  #define CDOG_NS                                  ((CDOG_Type *)CDOG_BASE_NS)
  /** Array initializer of CDOG peripheral base addresses */
  #define CDOG_BASE_ADDRS                          { CDOG_BASE }
  /** Array initializer of CDOG peripheral base pointers */
  #define CDOG_BASE_PTRS                           { CDOG }
  /** Array initializer of CDOG peripheral base addresses */
  #define CDOG_BASE_ADDRS_NS                       { CDOG_BASE_NS }
  /** Array initializer of CDOG peripheral base pointers */
  #define CDOG_BASE_PTRS_NS                        { CDOG_NS }
#else
  /** Peripheral CDOG base address */
  #define CDOG_BASE                                (0x400A1000u)
  /** Peripheral CDOG base pointer */
  #define CDOG                                     ((CDOG_Type *)CDOG_BASE)
  /** Array initializer of CDOG peripheral base addresses */
  #define CDOG_BASE_ADDRS                          { CDOG_BASE }
  /** Array initializer of CDOG peripheral base pointers */
  #define CDOG_BASE_PTRS                           { CDOG }
#endif
/** Interrupt vectors for the CDOG peripheral type */
#define CDOG_IRQS                                { CDOG_IRQn }

/* CRC - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral CRC_ENGINE base address */
  #define CRC_ENGINE_BASE                          (0x50095000u)
  /** Peripheral CRC_ENGINE base address */
  #define CRC_ENGINE_BASE_NS                       (0x40095000u)
  /** Peripheral CRC_ENGINE base pointer */
  #define CRC_ENGINE                               ((CRC_Type *)CRC_ENGINE_BASE)
  /** Peripheral CRC_ENGINE base pointer */
  #define CRC_ENGINE_NS                            ((CRC_Type *)CRC_ENGINE_BASE_NS)
  /** Array initializer of CRC peripheral base addresses */
  #define CRC_BASE_ADDRS                           { CRC_ENGINE_BASE }
  /** Array initializer of CRC peripheral base pointers */
  #define CRC_BASE_PTRS                            { CRC_ENGINE }
  /** Array initializer of CRC peripheral base addresses */
  #define CRC_BASE_ADDRS_NS                        { CRC_ENGINE_BASE_NS }
  /** Array initializer of CRC peripheral base pointers */
  #define CRC_BASE_PTRS_NS                         { CRC_ENGINE_NS }
#else
  /** Peripheral CRC_ENGINE base address */
  #define CRC_ENGINE_BASE                          (0x40095000u)
  /** Peripheral CRC_ENGINE base pointer */
  #define CRC_ENGINE                               ((CRC_Type *)CRC_ENGINE_BASE)
  /** Array initializer of CRC peripheral base addresses */
  #define CRC_BASE_ADDRS                           { CRC_ENGINE_BASE }
  /** Array initializer of CRC peripheral base pointers */
  #define CRC_BASE_PTRS                            { CRC_ENGINE }
#endif

/* CTIMER - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral CTIMER0 base address */
  #define CTIMER0_BASE                             (0x50008000u)
  /** Peripheral CTIMER0 base address */
  #define CTIMER0_BASE_NS                          (0x40008000u)
  /** Peripheral CTIMER0 base pointer */
  #define CTIMER0                                  ((CTIMER_Type *)CTIMER0_BASE)
  /** Peripheral CTIMER0 base pointer */
  #define CTIMER0_NS                               ((CTIMER_Type *)CTIMER0_BASE_NS)
  /** Peripheral CTIMER1 base address */
  #define CTIMER1_BASE                             (0x50009000u)
  /** Peripheral CTIMER1 base address */
  #define CTIMER1_BASE_NS                          (0x40009000u)
  /** Peripheral CTIMER1 base pointer */
  #define CTIMER1                                  ((CTIMER_Type *)CTIMER1_BASE)
  /** Peripheral CTIMER1 base pointer */
  #define CTIMER1_NS                               ((CTIMER_Type *)CTIMER1_BASE_NS)
  /** Peripheral CTIMER2 base address */
  #define CTIMER2_BASE                             (0x50028000u)
  /** Peripheral CTIMER2 base address */
  #define CTIMER2_BASE_NS                          (0x40028000u)
  /** Peripheral CTIMER2 base pointer */
  #define CTIMER2                                  ((CTIMER_Type *)CTIMER2_BASE)
  /** Peripheral CTIMER2 base pointer */
  #define CTIMER2_NS                               ((CTIMER_Type *)CTIMER2_BASE_NS)
  /** Peripheral CTIMER3 base address */
  #define CTIMER3_BASE                             (0x50029000u)
  /** Peripheral CTIMER3 base address */
  #define CTIMER3_BASE_NS                          (0x40029000u)
  /** Peripheral CTIMER3 base pointer */
  #define CTIMER3                                  ((CTIMER_Type *)CTIMER3_BASE)
  /** Peripheral CTIMER3 base pointer */
  #define CTIMER3_NS                               ((CTIMER_Type *)CTIMER3_BASE_NS)
  /** Peripheral CTIMER4 base address */
  #define CTIMER4_BASE                             (0x5002A000u)
  /** Peripheral CTIMER4 base address */
  #define CTIMER4_BASE_NS                          (0x4002A000u)
  /** Peripheral CTIMER4 base pointer */
  #define CTIMER4                                  ((CTIMER_Type *)CTIMER4_BASE)
  /** Peripheral CTIMER4 base pointer */
  #define CTIMER4_NS                               ((CTIMER_Type *)CTIMER4_BASE_NS)
  /** Array initializer of CTIMER peripheral base addresses */
  #define CTIMER_BASE_ADDRS                        { CTIMER0_BASE, CTIMER1_BASE, CTIMER2_BASE, CTIMER3_BASE, CTIMER4_BASE }
  /** Array initializer of CTIMER peripheral base pointers */
  #define CTIMER_BASE_PTRS                         { CTIMER0, CTIMER1, CTIMER2, CTIMER3, CTIMER4 }
  /** Array initializer of CTIMER peripheral base addresses */
  #define CTIMER_BASE_ADDRS_NS                     { CTIMER0_BASE_NS, CTIMER1_BASE_NS, CTIMER2_BASE_NS, CTIMER3_BASE_NS, CTIMER4_BASE_NS }
  /** Array initializer of CTIMER peripheral base pointers */
  #define CTIMER_BASE_PTRS_NS                      { CTIMER0_NS, CTIMER1_NS, CTIMER2_NS, CTIMER3_NS, CTIMER4_NS }
#else
  /** Peripheral CTIMER0 base address */
  #define CTIMER0_BASE                             (0x40008000u)
  /** Peripheral CTIMER0 base pointer */
  #define CTIMER0                                  ((CTIMER_Type *)CTIMER0_BASE)
  /** Peripheral CTIMER1 base address */
  #define CTIMER1_BASE                             (0x40009000u)
  /** Peripheral CTIMER1 base pointer */
  #define CTIMER1                                  ((CTIMER_Type *)CTIMER1_BASE)
  /** Peripheral CTIMER2 base address */
  #define CTIMER2_BASE                             (0x40028000u)
  /** Peripheral CTIMER2 base pointer */
  #define CTIMER2                                  ((CTIMER_Type *)CTIMER2_BASE)
  /** Peripheral CTIMER3 base address */
  #define CTIMER3_BASE                             (0x40029000u)
  /** Peripheral CTIMER3 base pointer */
  #define CTIMER3                                  ((CTIMER_Type *)CTIMER3_BASE)
  /** Peripheral CTIMER4 base address */
  #define CTIMER4_BASE                             (0x4002A000u)
  /** Peripheral CTIMER4 base pointer */
  #define CTIMER4                                  ((CTIMER_Type *)CTIMER4_BASE)
  /** Array initializer of CTIMER peripheral base addresses */
  #define CTIMER_BASE_ADDRS                        { CTIMER0_BASE, CTIMER1_BASE, CTIMER2_BASE, CTIMER3_BASE, CTIMER4_BASE }
  /** Array initializer of CTIMER peripheral base pointers */
  #define CTIMER_BASE_PTRS                         { CTIMER0, CTIMER1, CTIMER2, CTIMER3, CTIMER4 }
#endif
/** Interrupt vectors for the CTIMER peripheral type */
#define CTIMER_IRQS                              { CTIMER0_IRQn, CTIMER1_IRQn, CTIMER2_IRQn, CTIMER3_IRQn, CTIMER4_IRQn }

/* DBGMAILBOX - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral DBGMAILBOX base address */
  #define DBGMAILBOX_BASE                          (0x5009C000u)
  /** Peripheral DBGMAILBOX base address */
  #define DBGMAILBOX_BASE_NS                       (0x4009C000u)
  /** Peripheral DBGMAILBOX base pointer */
  #define DBGMAILBOX                               ((DBGMAILBOX_Type *)DBGMAILBOX_BASE)
  /** Peripheral DBGMAILBOX base pointer */
  #define DBGMAILBOX_NS                            ((DBGMAILBOX_Type *)DBGMAILBOX_BASE_NS)
  /** Array initializer of DBGMAILBOX peripheral base addresses */
  #define DBGMAILBOX_BASE_ADDRS                    { DBGMAILBOX_BASE }
  /** Array initializer of DBGMAILBOX peripheral base pointers */
  #define DBGMAILBOX_BASE_PTRS                     { DBGMAILBOX }
  /** Array initializer of DBGMAILBOX peripheral base addresses */
  #define DBGMAILBOX_BASE_ADDRS_NS                 { DBGMAILBOX_BASE_NS }
  /** Array initializer of DBGMAILBOX peripheral base pointers */
  #define DBGMAILBOX_BASE_PTRS_NS                  { DBGMAILBOX_NS }
#else
  /** Peripheral DBGMAILBOX base address */
  #define DBGMAILBOX_BASE                          (0x4009C000u)
  /** Peripheral DBGMAILBOX base pointer */
  #define DBGMAILBOX                               ((DBGMAILBOX_Type *)DBGMAILBOX_BASE)
  /** Array initializer of DBGMAILBOX peripheral base addresses */
  #define DBGMAILBOX_BASE_ADDRS                    { DBGMAILBOX_BASE }
  /** Array initializer of DBGMAILBOX peripheral base pointers */
  #define DBGMAILBOX_BASE_PTRS                     { DBGMAILBOX }
#endif

/* DMA - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral DMA0 base address */
  #define DMA0_BASE                                (0x50082000u)
  /** Peripheral DMA0 base address */
  #define DMA0_BASE_NS                             (0x40082000u)
  /** Peripheral DMA0 base pointer */
  #define DMA0                                     ((DMA_Type *)DMA0_BASE)
  /** Peripheral DMA0 base pointer */
  #define DMA0_NS                                  ((DMA_Type *)DMA0_BASE_NS)
  /** Peripheral DMA1 base address */
  #define DMA1_BASE                                (0x500A7000u)
  /** Peripheral DMA1 base address */
  #define DMA1_BASE_NS                             (0x400A7000u)
  /** Peripheral DMA1 base pointer */
  #define DMA1                                     ((DMA_Type *)DMA1_BASE)
  /** Peripheral DMA1 base pointer */
  #define DMA1_NS                                  ((DMA_Type *)DMA1_BASE_NS)
  /** Array initializer of DMA peripheral base addresses */
  #define DMA_BASE_ADDRS                           { DMA0_BASE, DMA1_BASE }
  /** Array initializer of DMA peripheral base pointers */
  #define DMA_BASE_PTRS                            { DMA0, DMA1 }
  /** Array initializer of DMA peripheral base addresses */
  #define DMA_BASE_ADDRS_NS                        { DMA0_BASE_NS, DMA1_BASE_NS }
  /** Array initializer of DMA peripheral base pointers */
  #define DMA_BASE_PTRS_NS                         { DMA0_NS, DMA1_NS }
#else
  /** Peripheral DMA0 base address */
  #define DMA0_BASE                                (0x40082000u)
  /** Peripheral DMA0 base pointer */
  #define DMA0                                     ((DMA_Type *)DMA0_BASE)
  /** Peripheral DMA1 base address */
  #define DMA1_BASE                                (0x400A7000u)
  /** Peripheral DMA1 base pointer */
  #define DMA1                                     ((DMA_Type *)DMA1_BASE)
  /** Array initializer of DMA peripheral base addresses */
  #define DMA_BASE_ADDRS                           { DMA0_BASE, DMA1_BASE }
  /** Array initializer of DMA peripheral base pointers */
  #define DMA_BASE_PTRS                            { DMA0, DMA1 }
#endif
/** Interrupt vectors for the DMA peripheral type */
#define DMA_IRQS                                 { DMA0_IRQn, DMA1_IRQn }

/* FLASH - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral FLASH base address */
  #define FLASH_BASE                               (0x50034000u)
  /** Peripheral FLASH base address */
  #define FLASH_BASE_NS                            (0x40034000u)
  /** Peripheral FLASH base pointer */
  #define FLASH                                    ((FLASH_Type *)FLASH_BASE)
  /** Peripheral FLASH base pointer */
  #define FLASH_NS                                 ((FLASH_Type *)FLASH_BASE_NS)
  /** Array initializer of FLASH peripheral base addresses */
  #define FLASH_BASE_ADDRS                         { FLASH_BASE }
  /** Array initializer of FLASH peripheral base pointers */
  #define FLASH_BASE_PTRS                          { FLASH }
  /** Array initializer of FLASH peripheral base addresses */
  #define FLASH_BASE_ADDRS_NS                      { FLASH_BASE_NS }
  /** Array initializer of FLASH peripheral base pointers */
  #define FLASH_BASE_PTRS_NS                       { FLASH_NS }
#else
  /** Peripheral FLASH base address */
  #define FLASH_BASE                               (0x40034000u)
  /** Peripheral FLASH base pointer */
  #define FLASH                                    ((FLASH_Type *)FLASH_BASE)
  /** Array initializer of FLASH peripheral base addresses */
  #define FLASH_BASE_ADDRS                         { FLASH_BASE }
  /** Array initializer of FLASH peripheral base pointers */
  #define FLASH_BASE_PTRS                          { FLASH }
#endif

/* FLASH_CFPA - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral FLASH_CFPA0 base address */
  #define FLASH_CFPA0_BASE                         (0x1003E000u)
  /** Peripheral FLASH_CFPA0 base address */
  #define FLASH_CFPA0_BASE_NS                      (0x3E000u)
  /** Peripheral FLASH_CFPA0 base pointer */
  #define FLASH_CFPA0                              ((FLASH_CFPA_Type *)FLASH_CFPA0_BASE)
  /** Peripheral FLASH_CFPA0 base pointer */
  #define FLASH_CFPA0_NS                           ((FLASH_CFPA_Type *)FLASH_CFPA0_BASE_NS)
  /** Peripheral FLASH_CFPA1 base address */
  #define FLASH_CFPA1_BASE                         (0x1003E200u)
  /** Peripheral FLASH_CFPA1 base address */
  #define FLASH_CFPA1_BASE_NS                      (0x3E200u)
  /** Peripheral FLASH_CFPA1 base pointer */
  #define FLASH_CFPA1                              ((FLASH_CFPA_Type *)FLASH_CFPA1_BASE)
  /** Peripheral FLASH_CFPA1 base pointer */
  #define FLASH_CFPA1_NS                           ((FLASH_CFPA_Type *)FLASH_CFPA1_BASE_NS)
  /** Peripheral FLASH_CFPA_SCRATCH base address */
  #define FLASH_CFPA_SCRATCH_BASE                  (0x1003DE00u)
  /** Peripheral FLASH_CFPA_SCRATCH base address */
  #define FLASH_CFPA_SCRATCH_BASE_NS               (0x3DE00u)
  /** Peripheral FLASH_CFPA_SCRATCH base pointer */
  #define FLASH_CFPA_SCRATCH                       ((FLASH_CFPA_Type *)FLASH_CFPA_SCRATCH_BASE)
  /** Peripheral FLASH_CFPA_SCRATCH base pointer */
  #define FLASH_CFPA_SCRATCH_NS                    ((FLASH_CFPA_Type *)FLASH_CFPA_SCRATCH_BASE_NS)
  /** Array initializer of FLASH_CFPA peripheral base addresses */
  #define FLASH_CFPA_BASE_ADDRS                    { FLASH_CFPA0_BASE, FLASH_CFPA1_BASE, FLASH_CFPA_SCRATCH_BASE }
  /** Array initializer of FLASH_CFPA peripheral base pointers */
  #define FLASH_CFPA_BASE_PTRS                     { FLASH_CFPA0, FLASH_CFPA1, FLASH_CFPA_SCRATCH }
  /** Array initializer of FLASH_CFPA peripheral base addresses */
  #define FLASH_CFPA_BASE_ADDRS_NS                 { FLASH_CFPA0_BASE_NS, FLASH_CFPA1_BASE_NS, FLASH_CFPA_SCRATCH_BASE_NS }
  /** Array initializer of FLASH_CFPA peripheral base pointers */
  #define FLASH_CFPA_BASE_PTRS_NS                  { FLASH_CFPA0_NS, FLASH_CFPA1_NS, FLASH_CFPA_SCRATCH_NS }
#else
  /** Peripheral FLASH_CFPA0 base address */
  #define FLASH_CFPA0_BASE                         (0x3E000u)
  /** Peripheral FLASH_CFPA0 base pointer */
  #define FLASH_CFPA0                              ((FLASH_CFPA_Type *)FLASH_CFPA0_BASE)
  /** Peripheral FLASH_CFPA1 base address */
  #define FLASH_CFPA1_BASE                         (0x3E200u)
  /** Peripheral FLASH_CFPA1 base pointer */
  #define FLASH_CFPA1                              ((FLASH_CFPA_Type *)FLASH_CFPA1_BASE)
  /** Peripheral FLASH_CFPA_SCRATCH base address */
  #define FLASH_CFPA_SCRATCH_BASE                  (0x3DE00u)
  /** Peripheral FLASH_CFPA_SCRATCH base pointer */
  #define FLASH_CFPA_SCRATCH                       ((FLASH_CFPA_Type *)FLASH_CFPA_SCRATCH_BASE)
  /** Array initializer of FLASH_CFPA peripheral base addresses */
  #define FLASH_CFPA_BASE_ADDRS                    { FLASH_CFPA0_BASE, FLASH_CFPA1_BASE, FLASH_CFPA_SCRATCH_BASE }
  /** Array initializer of FLASH_CFPA peripheral base pointers */
  #define FLASH_CFPA_BASE_PTRS                     { FLASH_CFPA0, FLASH_CFPA1, FLASH_CFPA_SCRATCH }
#endif

/* FLASH_CMPA - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral FLASH_CMPA base address */
  #define FLASH_CMPA_BASE                          (0x1003E400u)
  /** Peripheral FLASH_CMPA base address */
  #define FLASH_CMPA_BASE_NS                       (0x3E400u)
  /** Peripheral FLASH_CMPA base pointer */
  #define FLASH_CMPA                               ((FLASH_CMPA_Type *)FLASH_CMPA_BASE)
  /** Peripheral FLASH_CMPA base pointer */
  #define FLASH_CMPA_NS                            ((FLASH_CMPA_Type *)FLASH_CMPA_BASE_NS)
  /** Array initializer of FLASH_CMPA peripheral base addresses */
  #define FLASH_CMPA_BASE_ADDRS                    { FLASH_CMPA_BASE }
  /** Array initializer of FLASH_CMPA peripheral base pointers */
  #define FLASH_CMPA_BASE_PTRS                     { FLASH_CMPA }
  /** Array initializer of FLASH_CMPA peripheral base addresses */
  #define FLASH_CMPA_BASE_ADDRS_NS                 { FLASH_CMPA_BASE_NS }
  /** Array initializer of FLASH_CMPA peripheral base pointers */
  #define FLASH_CMPA_BASE_PTRS_NS                  { FLASH_CMPA_NS }
#else
  /** Peripheral FLASH_CMPA base address */
  #define FLASH_CMPA_BASE                          (0x3E400u)
  /** Peripheral FLASH_CMPA base pointer */
  #define FLASH_CMPA                               ((FLASH_CMPA_Type *)FLASH_CMPA_BASE)
  /** Array initializer of FLASH_CMPA peripheral base addresses */
  #define FLASH_CMPA_BASE_ADDRS                    { FLASH_CMPA_BASE }
  /** Array initializer of FLASH_CMPA peripheral base pointers */
  #define FLASH_CMPA_BASE_PTRS                     { FLASH_CMPA }
#endif

/* FLASH_KEY_STORE - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral FLASH_KEY_STORE base address */
  #define FLASH_KEY_STORE_BASE                     (0x1003E600u)
  /** Peripheral FLASH_KEY_STORE base address */
  #define FLASH_KEY_STORE_BASE_NS                  (0x3E600u)
  /** Peripheral FLASH_KEY_STORE base pointer */
  #define FLASH_KEY_STORE                          ((FLASH_KEY_STORE_Type *)FLASH_KEY_STORE_BASE)
  /** Peripheral FLASH_KEY_STORE base pointer */
  #define FLASH_KEY_STORE_NS                       ((FLASH_KEY_STORE_Type *)FLASH_KEY_STORE_BASE_NS)
  /** Array initializer of FLASH_KEY_STORE peripheral base addresses */
  #define FLASH_KEY_STORE_BASE_ADDRS               { FLASH_KEY_STORE_BASE }
  /** Array initializer of FLASH_KEY_STORE peripheral base pointers */
  #define FLASH_KEY_STORE_BASE_PTRS                { FLASH_KEY_STORE }
  /** Array initializer of FLASH_KEY_STORE peripheral base addresses */
  #define FLASH_KEY_STORE_BASE_ADDRS_NS            { FLASH_KEY_STORE_BASE_NS }
  /** Array initializer of FLASH_KEY_STORE peripheral base pointers */
  #define FLASH_KEY_STORE_BASE_PTRS_NS             { FLASH_KEY_STORE_NS }
#else
  /** Peripheral FLASH_KEY_STORE base address */
  #define FLASH_KEY_STORE_BASE                     (0x3E600u)
  /** Peripheral FLASH_KEY_STORE base pointer */
  #define FLASH_KEY_STORE                          ((FLASH_KEY_STORE_Type *)FLASH_KEY_STORE_BASE)
  /** Array initializer of FLASH_KEY_STORE peripheral base addresses */
  #define FLASH_KEY_STORE_BASE_ADDRS               { FLASH_KEY_STORE_BASE }
  /** Array initializer of FLASH_KEY_STORE peripheral base pointers */
  #define FLASH_KEY_STORE_BASE_PTRS                { FLASH_KEY_STORE }
#endif

/* FLASH_NMPA - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral FLASH_NMPA base address */
  #define FLASH_NMPA_BASE                          (0x1003FC00u)
  /** Peripheral FLASH_NMPA base address */
  #define FLASH_NMPA_BASE_NS                       (0x3FC00u)
  /** Peripheral FLASH_NMPA base pointer */
  #define FLASH_NMPA                               ((FLASH_NMPA_Type *)FLASH_NMPA_BASE)
  /** Peripheral FLASH_NMPA base pointer */
  #define FLASH_NMPA_NS                            ((FLASH_NMPA_Type *)FLASH_NMPA_BASE_NS)
  /** Array initializer of FLASH_NMPA peripheral base addresses */
  #define FLASH_NMPA_BASE_ADDRS                    { FLASH_NMPA_BASE }
  /** Array initializer of FLASH_NMPA peripheral base pointers */
  #define FLASH_NMPA_BASE_PTRS                     { FLASH_NMPA }
  /** Array initializer of FLASH_NMPA peripheral base addresses */
  #define FLASH_NMPA_BASE_ADDRS_NS                 { FLASH_NMPA_BASE_NS }
  /** Array initializer of FLASH_NMPA peripheral base pointers */
  #define FLASH_NMPA_BASE_PTRS_NS                  { FLASH_NMPA_NS }
#else
  /** Peripheral FLASH_NMPA base address */
  #define FLASH_NMPA_BASE                          (0x3FC00u)
  /** Peripheral FLASH_NMPA base pointer */
  #define FLASH_NMPA                               ((FLASH_NMPA_Type *)FLASH_NMPA_BASE)
  /** Array initializer of FLASH_NMPA peripheral base addresses */
  #define FLASH_NMPA_BASE_ADDRS                    { FLASH_NMPA_BASE }
  /** Array initializer of FLASH_NMPA peripheral base pointers */
  #define FLASH_NMPA_BASE_PTRS                     { FLASH_NMPA }
#endif

/* FLASH_ROMPATCH - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral FLASH_ROMPATCH base address */
  #define FLASH_ROMPATCH_BASE                      (0x1003EC00u)
  /** Peripheral FLASH_ROMPATCH base address */
  #define FLASH_ROMPATCH_BASE_NS                   (0x3EC00u)
  /** Peripheral FLASH_ROMPATCH base pointer */
  #define FLASH_ROMPATCH                           ((FLASH_ROMPATCH_Type *)FLASH_ROMPATCH_BASE)
  /** Peripheral FLASH_ROMPATCH base pointer */
  #define FLASH_ROMPATCH_NS                        ((FLASH_ROMPATCH_Type *)FLASH_ROMPATCH_BASE_NS)
  /** Array initializer of FLASH_ROMPATCH peripheral base addresses */
  #define FLASH_ROMPATCH_BASE_ADDRS                { FLASH_ROMPATCH_BASE }
  /** Array initializer of FLASH_ROMPATCH peripheral base pointers */
  #define FLASH_ROMPATCH_BASE_PTRS                 { FLASH_ROMPATCH }
  /** Array initializer of FLASH_ROMPATCH peripheral base addresses */
  #define FLASH_ROMPATCH_BASE_ADDRS_NS             { FLASH_ROMPATCH_BASE_NS }
  /** Array initializer of FLASH_ROMPATCH peripheral base pointers */
  #define FLASH_ROMPATCH_BASE_PTRS_NS              { FLASH_ROMPATCH_NS }
#else
  /** Peripheral FLASH_ROMPATCH base address */
  #define FLASH_ROMPATCH_BASE                      (0x3EC00u)
  /** Peripheral FLASH_ROMPATCH base pointer */
  #define FLASH_ROMPATCH                           ((FLASH_ROMPATCH_Type *)FLASH_ROMPATCH_BASE)
  /** Array initializer of FLASH_ROMPATCH peripheral base addresses */
  #define FLASH_ROMPATCH_BASE_ADDRS                { FLASH_ROMPATCH_BASE }
  /** Array initializer of FLASH_ROMPATCH peripheral base pointers */
  #define FLASH_ROMPATCH_BASE_PTRS                 { FLASH_ROMPATCH }
#endif

/* FLEXCOMM - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral FLEXCOMM0 base address */
  #define FLEXCOMM0_BASE                           (0x50086000u)
  /** Peripheral FLEXCOMM0 base address */
  #define FLEXCOMM0_BASE_NS                        (0x40086000u)
  /** Peripheral FLEXCOMM0 base pointer */
  #define FLEXCOMM0                                ((FLEXCOMM_Type *)FLEXCOMM0_BASE)
  /** Peripheral FLEXCOMM0 base pointer */
  #define FLEXCOMM0_NS                             ((FLEXCOMM_Type *)FLEXCOMM0_BASE_NS)
  /** Peripheral FLEXCOMM1 base address */
  #define FLEXCOMM1_BASE                           (0x50087000u)
  /** Peripheral FLEXCOMM1 base address */
  #define FLEXCOMM1_BASE_NS                        (0x40087000u)
  /** Peripheral FLEXCOMM1 base pointer */
  #define FLEXCOMM1                                ((FLEXCOMM_Type *)FLEXCOMM1_BASE)
  /** Peripheral FLEXCOMM1 base pointer */
  #define FLEXCOMM1_NS                             ((FLEXCOMM_Type *)FLEXCOMM1_BASE_NS)
  /** Peripheral FLEXCOMM2 base address */
  #define FLEXCOMM2_BASE                           (0x50088000u)
  /** Peripheral FLEXCOMM2 base address */
  #define FLEXCOMM2_BASE_NS                        (0x40088000u)
  /** Peripheral FLEXCOMM2 base pointer */
  #define FLEXCOMM2                                ((FLEXCOMM_Type *)FLEXCOMM2_BASE)
  /** Peripheral FLEXCOMM2 base pointer */
  #define FLEXCOMM2_NS                             ((FLEXCOMM_Type *)FLEXCOMM2_BASE_NS)
  /** Peripheral FLEXCOMM3 base address */
  #define FLEXCOMM3_BASE                           (0x50089000u)
  /** Peripheral FLEXCOMM3 base address */
  #define FLEXCOMM3_BASE_NS                        (0x40089000u)
  /** Peripheral FLEXCOMM3 base pointer */
  #define FLEXCOMM3                                ((FLEXCOMM_Type *)FLEXCOMM3_BASE)
  /** Peripheral FLEXCOMM3 base pointer */
  #define FLEXCOMM3_NS                             ((FLEXCOMM_Type *)FLEXCOMM3_BASE_NS)
  /** Peripheral FLEXCOMM4 base address */
  #define FLEXCOMM4_BASE                           (0x5008A000u)
  /** Peripheral FLEXCOMM4 base address */
  #define FLEXCOMM4_BASE_NS                        (0x4008A000u)
  /** Peripheral FLEXCOMM4 base pointer */
  #define FLEXCOMM4                                ((FLEXCOMM_Type *)FLEXCOMM4_BASE)
  /** Peripheral FLEXCOMM4 base pointer */
  #define FLEXCOMM4_NS                             ((FLEXCOMM_Type *)FLEXCOMM4_BASE_NS)
  /** Peripheral FLEXCOMM5 base address */
  #define FLEXCOMM5_BASE                           (0x50096000u)
  /** Peripheral FLEXCOMM5 base address */
  #define FLEXCOMM5_BASE_NS                        (0x40096000u)
  /** Peripheral FLEXCOMM5 base pointer */
  #define FLEXCOMM5                                ((FLEXCOMM_Type *)FLEXCOMM5_BASE)
  /** Peripheral FLEXCOMM5 base pointer */
  #define FLEXCOMM5_NS                             ((FLEXCOMM_Type *)FLEXCOMM5_BASE_NS)
  /** Peripheral FLEXCOMM6 base address */
  #define FLEXCOMM6_BASE                           (0x50097000u)
  /** Peripheral FLEXCOMM6 base address */
  #define FLEXCOMM6_BASE_NS                        (0x40097000u)
  /** Peripheral FLEXCOMM6 base pointer */
  #define FLEXCOMM6                                ((FLEXCOMM_Type *)FLEXCOMM6_BASE)
  /** Peripheral FLEXCOMM6 base pointer */
  #define FLEXCOMM6_NS                             ((FLEXCOMM_Type *)FLEXCOMM6_BASE_NS)
  /** Peripheral FLEXCOMM7 base address */
  #define FLEXCOMM7_BASE                           (0x50098000u)
  /** Peripheral FLEXCOMM7 base address */
  #define FLEXCOMM7_BASE_NS                        (0x40098000u)
  /** Peripheral FLEXCOMM7 base pointer */
  #define FLEXCOMM7                                ((FLEXCOMM_Type *)FLEXCOMM7_BASE)
  /** Peripheral FLEXCOMM7 base pointer */
  #define FLEXCOMM7_NS                             ((FLEXCOMM_Type *)FLEXCOMM7_BASE_NS)
  /** Peripheral FLEXCOMM8 base address */
  #define FLEXCOMM8_BASE                           (0x5009F000u)
  /** Peripheral FLEXCOMM8 base address */
  #define FLEXCOMM8_BASE_NS                        (0x4009F000u)
  /** Peripheral FLEXCOMM8 base pointer */
  #define FLEXCOMM8                                ((FLEXCOMM_Type *)FLEXCOMM8_BASE)
  /** Peripheral FLEXCOMM8 base pointer */
  #define FLEXCOMM8_NS                             ((FLEXCOMM_Type *)FLEXCOMM8_BASE_NS)
  /** Array initializer of FLEXCOMM peripheral base addresses */
  #define FLEXCOMM_BASE_ADDRS                      { FLEXCOMM0_BASE, FLEXCOMM1_BASE, FLEXCOMM2_BASE, FLEXCOMM3_BASE, FLEXCOMM4_BASE, FLEXCOMM5_BASE, FLEXCOMM6_BASE, FLEXCOMM7_BASE, FLEXCOMM8_BASE }
  /** Array initializer of FLEXCOMM peripheral base pointers */
  #define FLEXCOMM_BASE_PTRS                       { FLEXCOMM0, FLEXCOMM1, FLEXCOMM2, FLEXCOMM3, FLEXCOMM4, FLEXCOMM5, FLEXCOMM6, FLEXCOMM7, FLEXCOMM8 }
  /** Array initializer of FLEXCOMM peripheral base addresses */
  #define FLEXCOMM_BASE_ADDRS_NS                   { FLEXCOMM0_BASE_NS, FLEXCOMM1_BASE_NS, FLEXCOMM2_BASE_NS, FLEXCOMM3_BASE_NS, FLEXCOMM4_BASE_NS, FLEXCOMM5_BASE_NS, FLEXCOMM6_BASE_NS, FLEXCOMM7_BASE_NS, FLEXCOMM8_BASE_NS }
  /** Array initializer of FLEXCOMM peripheral base pointers */
  #define FLEXCOMM_BASE_PTRS_NS                    { FLEXCOMM0_NS, FLEXCOMM1_NS, FLEXCOMM2_NS, FLEXCOMM3_NS, FLEXCOMM4_NS, FLEXCOMM5_NS, FLEXCOMM6_NS, FLEXCOMM7_NS, FLEXCOMM8_NS }
#else
  /** Peripheral FLEXCOMM0 base address */
  #define FLEXCOMM0_BASE                           (0x40086000u)
  /** Peripheral FLEXCOMM0 base pointer */
  #define FLEXCOMM0                                ((FLEXCOMM_Type *)FLEXCOMM0_BASE)
  /** Peripheral FLEXCOMM1 base address */
  #define FLEXCOMM1_BASE                           (0x40087000u)
  /** Peripheral FLEXCOMM1 base pointer */
  #define FLEXCOMM1                                ((FLEXCOMM_Type *)FLEXCOMM1_BASE)
  /** Peripheral FLEXCOMM2 base address */
  #define FLEXCOMM2_BASE                           (0x40088000u)
  /** Peripheral FLEXCOMM2 base pointer */
  #define FLEXCOMM2                                ((FLEXCOMM_Type *)FLEXCOMM2_BASE)
  /** Peripheral FLEXCOMM3 base address */
  #define FLEXCOMM3_BASE                           (0x40089000u)
  /** Peripheral FLEXCOMM3 base pointer */
  #define FLEXCOMM3                                ((FLEXCOMM_Type *)FLEXCOMM3_BASE)
  /** Peripheral FLEXCOMM4 base address */
  #define FLEXCOMM4_BASE                           (0x4008A000u)
  /** Peripheral FLEXCOMM4 base pointer */
  #define FLEXCOMM4                                ((FLEXCOMM_Type *)FLEXCOMM4_BASE)
  /** Peripheral FLEXCOMM5 base address */
  #define FLEXCOMM5_BASE                           (0x40096000u)
  /** Peripheral FLEXCOMM5 base pointer */
  #define FLEXCOMM5                                ((FLEXCOMM_Type *)FLEXCOMM5_BASE)
  /** Peripheral FLEXCOMM6 base address */
  #define FLEXCOMM6_BASE                           (0x40097000u)
  /** Peripheral FLEXCOMM6 base pointer */
  #define FLEXCOMM6                                ((FLEXCOMM_Type *)FLEXCOMM6_BASE)
  /** Peripheral FLEXCOMM7 base address */
  #define FLEXCOMM7_BASE                           (0x40098000u)
  /** Peripheral FLEXCOMM7 base pointer */
  #define FLEXCOMM7                                ((FLEXCOMM_Type *)FLEXCOMM7_BASE)
  /** Peripheral FLEXCOMM8 base address */
  #define FLEXCOMM8_BASE                           (0x4009F000u)
  /** Peripheral FLEXCOMM8 base pointer */
  #define FLEXCOMM8                                ((FLEXCOMM_Type *)FLEXCOMM8_BASE)
  /** Array initializer of FLEXCOMM peripheral base addresses */
  #define FLEXCOMM_BASE_ADDRS                      { FLEXCOMM0_BASE, FLEXCOMM1_BASE, FLEXCOMM2_BASE, FLEXCOMM3_BASE, FLEXCOMM4_BASE, FLEXCOMM5_BASE, FLEXCOMM6_BASE, FLEXCOMM7_BASE, FLEXCOMM8_BASE }
  /** Array initializer of FLEXCOMM peripheral base pointers */
  #define FLEXCOMM_BASE_PTRS                       { FLEXCOMM0, FLEXCOMM1, FLEXCOMM2, FLEXCOMM3, FLEXCOMM4, FLEXCOMM5, FLEXCOMM6, FLEXCOMM7, FLEXCOMM8 }
#endif
/** Interrupt vectors for the FLEXCOMM peripheral type */
#define FLEXCOMM_IRQS                            { FLEXCOMM0_IRQn, FLEXCOMM1_IRQn, FLEXCOMM2_IRQn, FLEXCOMM3_IRQn, FLEXCOMM4_IRQn, FLEXCOMM5_IRQn, FLEXCOMM6_IRQn, FLEXCOMM7_IRQn, FLEXCOMM8_IRQn }

/* GINT - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral GINT0 base address */
  #define GINT0_BASE                               (0x50002000u)
  /** Peripheral GINT0 base address */
  #define GINT0_BASE_NS                            (0x40002000u)
  /** Peripheral GINT0 base pointer */
  #define GINT0                                    ((GINT_Type *)GINT0_BASE)
  /** Peripheral GINT0 base pointer */
  #define GINT0_NS                                 ((GINT_Type *)GINT0_BASE_NS)
  /** Peripheral GINT1 base address */
  #define GINT1_BASE                               (0x50003000u)
  /** Peripheral GINT1 base address */
  #define GINT1_BASE_NS                            (0x40003000u)
  /** Peripheral GINT1 base pointer */
  #define GINT1                                    ((GINT_Type *)GINT1_BASE)
  /** Peripheral GINT1 base pointer */
  #define GINT1_NS                                 ((GINT_Type *)GINT1_BASE_NS)
  /** Array initializer of GINT peripheral base addresses */
  #define GINT_BASE_ADDRS                          { GINT0_BASE, GINT1_BASE }
  /** Array initializer of GINT peripheral base pointers */
  #define GINT_BASE_PTRS                           { GINT0, GINT1 }
  /** Array initializer of GINT peripheral base addresses */
  #define GINT_BASE_ADDRS_NS                       { GINT0_BASE_NS, GINT1_BASE_NS }
  /** Array initializer of GINT peripheral base pointers */
  #define GINT_BASE_PTRS_NS                        { GINT0_NS, GINT1_NS }
#else
  /** Peripheral GINT0 base address */
  #define GINT0_BASE                               (0x40002000u)
  /** Peripheral GINT0 base pointer */
  #define GINT0                                    ((GINT_Type *)GINT0_BASE)
  /** Peripheral GINT1 base address */
  #define GINT1_BASE                               (0x40003000u)
  /** Peripheral GINT1 base pointer */
  #define GINT1                                    ((GINT_Type *)GINT1_BASE)
  /** Array initializer of GINT peripheral base addresses */
  #define GINT_BASE_ADDRS                          { GINT0_BASE, GINT1_BASE }
  /** Array initializer of GINT peripheral base pointers */
  #define GINT_BASE_PTRS                           { GINT0, GINT1 }
#endif
/** Interrupt vectors for the GINT peripheral type */
#define GINT_IRQS                                { GINT0_IRQn, GINT1_IRQn }

/* GPIO - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral GPIO base address */
  #define GPIO_BASE                                (0x5008C000u)
  /** Peripheral GPIO base address */
  #define GPIO_BASE_NS                             (0x4008C000u)
  /** Peripheral GPIO base pointer */
  #define GPIO                                     ((GPIO_Type *)GPIO_BASE)
  /** Peripheral GPIO base pointer */
  #define GPIO_NS                                  ((GPIO_Type *)GPIO_BASE_NS)
  /** Peripheral SECGPIO base address */
  #define SECGPIO_BASE                             (0x500A8000u)
  /** Peripheral SECGPIO base address */
  #define SECGPIO_BASE_NS                          (0x400A8000u)
  /** Peripheral SECGPIO base pointer */
  #define SECGPIO                                  ((GPIO_Type *)SECGPIO_BASE)
  /** Peripheral SECGPIO base pointer */
  #define SECGPIO_NS                               ((GPIO_Type *)SECGPIO_BASE_NS)
  /** Array initializer of GPIO peripheral base addresses */
  #define GPIO_BASE_ADDRS                          { GPIO_BASE, SECGPIO_BASE }
  /** Array initializer of GPIO peripheral base pointers */
  #define GPIO_BASE_PTRS                           { GPIO, SECGPIO }
  /** Array initializer of GPIO peripheral base addresses */
  #define GPIO_BASE_ADDRS_NS                       { GPIO_BASE_NS, SECGPIO_BASE_NS }
  /** Array initializer of GPIO peripheral base pointers */
  #define GPIO_BASE_PTRS_NS                        { GPIO_NS, SECGPIO_NS }
#else
  /** Peripheral GPIO base address */
  #define GPIO_BASE                                (0x4008C000u)
  /** Peripheral GPIO base pointer */
  #define GPIO                                     ((GPIO_Type *)GPIO_BASE)
  /** Peripheral SECGPIO base address */
  #define SECGPIO_BASE                             (0x400A8000u)
  /** Peripheral SECGPIO base pointer */
  #define SECGPIO                                  ((GPIO_Type *)SECGPIO_BASE)
  /** Array initializer of GPIO peripheral base addresses */
  #define GPIO_BASE_ADDRS                          { GPIO_BASE, SECGPIO_BASE }
  /** Array initializer of GPIO peripheral base pointers */
  #define GPIO_BASE_PTRS                           { GPIO, SECGPIO }
#endif

/* HASHCRYPT - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral HASHCRYPT base address */
  #define HASHCRYPT_BASE                           (0x500A4000u)
  /** Peripheral HASHCRYPT base address */
  #define HASHCRYPT_BASE_NS                        (0x400A4000u)
  /** Peripheral HASHCRYPT base pointer */
  #define HASHCRYPT                                ((HASHCRYPT_Type *)HASHCRYPT_BASE)
  /** Peripheral HASHCRYPT base pointer */
  #define HASHCRYPT_NS                             ((HASHCRYPT_Type *)HASHCRYPT_BASE_NS)
  /** Array initializer of HASHCRYPT peripheral base addresses */
  #define HASHCRYPT_BASE_ADDRS                     { HASHCRYPT_BASE }
  /** Array initializer of HASHCRYPT peripheral base pointers */
  #define HASHCRYPT_BASE_PTRS                      { HASHCRYPT }
  /** Array initializer of HASHCRYPT peripheral base addresses */
  #define HASHCRYPT_BASE_ADDRS_NS                  { HASHCRYPT_BASE_NS }
  /** Array initializer of HASHCRYPT peripheral base pointers */
  #define HASHCRYPT_BASE_PTRS_NS                   { HASHCRYPT_NS }
#else
  /** Peripheral HASHCRYPT base address */
  #define HASHCRYPT_BASE                           (0x400A4000u)
  /** Peripheral HASHCRYPT base pointer */
  #define HASHCRYPT                                ((HASHCRYPT_Type *)HASHCRYPT_BASE)
  /** Array initializer of HASHCRYPT peripheral base addresses */
  #define HASHCRYPT_BASE_ADDRS                     { HASHCRYPT_BASE }
  /** Array initializer of HASHCRYPT peripheral base pointers */
  #define HASHCRYPT_BASE_PTRS                      { HASHCRYPT }
#endif

/* I2C - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral I2C0 base address */
  #define I2C0_BASE                                (0x50086000u)
  /** Peripheral I2C0 base address */
  #define I2C0_BASE_NS                             (0x40086000u)
  /** Peripheral I2C0 base pointer */
  #define I2C0                                     ((I2C_Type *)I2C0_BASE)
  /** Peripheral I2C0 base pointer */
  #define I2C0_NS                                  ((I2C_Type *)I2C0_BASE_NS)
  /** Peripheral I2C1 base address */
  #define I2C1_BASE                                (0x50087000u)
  /** Peripheral I2C1 base address */
  #define I2C1_BASE_NS                             (0x40087000u)
  /** Peripheral I2C1 base pointer */
  #define I2C1                                     ((I2C_Type *)I2C1_BASE)
  /** Peripheral I2C1 base pointer */
  #define I2C1_NS                                  ((I2C_Type *)I2C1_BASE_NS)
  /** Peripheral I2C2 base address */
  #define I2C2_BASE                                (0x50088000u)
  /** Peripheral I2C2 base address */
  #define I2C2_BASE_NS                             (0x40088000u)
  /** Peripheral I2C2 base pointer */
  #define I2C2                                     ((I2C_Type *)I2C2_BASE)
  /** Peripheral I2C2 base pointer */
  #define I2C2_NS                                  ((I2C_Type *)I2C2_BASE_NS)
  /** Peripheral I2C3 base address */
  #define I2C3_BASE                                (0x50089000u)
  /** Peripheral I2C3 base address */
  #define I2C3_BASE_NS                             (0x40089000u)
  /** Peripheral I2C3 base pointer */
  #define I2C3                                     ((I2C_Type *)I2C3_BASE)
  /** Peripheral I2C3 base pointer */
  #define I2C3_NS                                  ((I2C_Type *)I2C3_BASE_NS)
  /** Peripheral I2C4 base address */
  #define I2C4_BASE                                (0x5008A000u)
  /** Peripheral I2C4 base address */
  #define I2C4_BASE_NS                             (0x4008A000u)
  /** Peripheral I2C4 base pointer */
  #define I2C4                                     ((I2C_Type *)I2C4_BASE)
  /** Peripheral I2C4 base pointer */
  #define I2C4_NS                                  ((I2C_Type *)I2C4_BASE_NS)
  /** Peripheral I2C5 base address */
  #define I2C5_BASE                                (0x50096000u)
  /** Peripheral I2C5 base address */
  #define I2C5_BASE_NS                             (0x40096000u)
  /** Peripheral I2C5 base pointer */
  #define I2C5                                     ((I2C_Type *)I2C5_BASE)
  /** Peripheral I2C5 base pointer */
  #define I2C5_NS                                  ((I2C_Type *)I2C5_BASE_NS)
  /** Peripheral I2C6 base address */
  #define I2C6_BASE                                (0x50097000u)
  /** Peripheral I2C6 base address */
  #define I2C6_BASE_NS                             (0x40097000u)
  /** Peripheral I2C6 base pointer */
  #define I2C6                                     ((I2C_Type *)I2C6_BASE)
  /** Peripheral I2C6 base pointer */
  #define I2C6_NS                                  ((I2C_Type *)I2C6_BASE_NS)
  /** Peripheral I2C7 base address */
  #define I2C7_BASE                                (0x50098000u)
  /** Peripheral I2C7 base address */
  #define I2C7_BASE_NS                             (0x40098000u)
  /** Peripheral I2C7 base pointer */
  #define I2C7                                     ((I2C_Type *)I2C7_BASE)
  /** Peripheral I2C7 base pointer */
  #define I2C7_NS                                  ((I2C_Type *)I2C7_BASE_NS)
  /** Array initializer of I2C peripheral base addresses */
  #define I2C_BASE_ADDRS                           { I2C0_BASE, I2C1_BASE, I2C2_BASE, I2C3_BASE, I2C4_BASE, I2C5_BASE, I2C6_BASE, I2C7_BASE }
  /** Array initializer of I2C peripheral base pointers */
  #define I2C_BASE_PTRS                            { I2C0, I2C1, I2C2, I2C3, I2C4, I2C5, I2C6, I2C7 }
  /** Array initializer of I2C peripheral base addresses */
  #define I2C_BASE_ADDRS_NS                        { I2C0_BASE_NS, I2C1_BASE_NS, I2C2_BASE_NS, I2C3_BASE_NS, I2C4_BASE_NS, I2C5_BASE_NS, I2C6_BASE_NS, I2C7_BASE_NS }
  /** Array initializer of I2C peripheral base pointers */
  #define I2C_BASE_PTRS_NS                         { I2C0_NS, I2C1_NS, I2C2_NS, I2C3_NS, I2C4_NS, I2C5_NS, I2C6_NS, I2C7_NS }
#else
  /** Peripheral I2C0 base address */
  #define I2C0_BASE                                (0x40086000u)
  /** Peripheral I2C0 base pointer */
  #define I2C0                                     ((I2C_Type *)I2C0_BASE)
  /** Peripheral I2C1 base address */
  #define I2C1_BASE                                (0x40087000u)
  /** Peripheral I2C1 base pointer */
  #define I2C1                                     ((I2C_Type *)I2C1_BASE)
  /** Peripheral I2C2 base address */
  #define I2C2_BASE                                (0x40088000u)
  /** Peripheral I2C2 base pointer */
  #define I2C2                                     ((I2C_Type *)I2C2_BASE)
  /** Peripheral I2C3 base address */
  #define I2C3_BASE                                (0x40089000u)
  /** Peripheral I2C3 base pointer */
  #define I2C3                                     ((I2C_Type *)I2C3_BASE)
  /** Peripheral I2C4 base address */
  #define I2C4_BASE                                (0x4008A000u)
  /** Peripheral I2C4 base pointer */
  #define I2C4                                     ((I2C_Type *)I2C4_BASE)
  /** Peripheral I2C5 base address */
  #define I2C5_BASE                                (0x40096000u)
  /** Peripheral I2C5 base pointer */
  #define I2C5                                     ((I2C_Type *)I2C5_BASE)
  /** Peripheral I2C6 base address */
  #define I2C6_BASE                                (0x40097000u)
  /** Peripheral I2C6 base pointer */
  #define I2C6                                     ((I2C_Type *)I2C6_BASE)
  /** Peripheral I2C7 base address */
  #define I2C7_BASE                                (0x40098000u)
  /** Peripheral I2C7 base pointer */
  #define I2C7                                     ((I2C_Type *)I2C7_BASE)
  /** Array initializer of I2C peripheral base addresses */
  #define I2C_BASE_ADDRS                           { I2C0_BASE, I2C1_BASE, I2C2_BASE, I2C3_BASE, I2C4_BASE, I2C5_BASE, I2C6_BASE, I2C7_BASE }
  /** Array initializer of I2C peripheral base pointers */
  #define I2C_BASE_PTRS                            { I2C0, I2C1, I2C2, I2C3, I2C4, I2C5, I2C6, I2C7 }
#endif
/** Interrupt vectors for the I2C peripheral type */
#define I2C_IRQS                                 { FLEXCOMM0_IRQn, FLEXCOMM1_IRQn, FLEXCOMM2_IRQn, FLEXCOMM3_IRQn, FLEXCOMM4_IRQn, FLEXCOMM5_IRQn, FLEXCOMM6_IRQn, FLEXCOMM7_IRQn }

/* I2S - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral I2S0 base address */
  #define I2S0_BASE                                (0x50086000u)
  /** Peripheral I2S0 base address */
  #define I2S0_BASE_NS                             (0x40086000u)
  /** Peripheral I2S0 base pointer */
  #define I2S0                                     ((I2S_Type *)I2S0_BASE)
  /** Peripheral I2S0 base pointer */
  #define I2S0_NS                                  ((I2S_Type *)I2S0_BASE_NS)
  /** Peripheral I2S1 base address */
  #define I2S1_BASE                                (0x50087000u)
  /** Peripheral I2S1 base address */
  #define I2S1_BASE_NS                             (0x40087000u)
  /** Peripheral I2S1 base pointer */
  #define I2S1                                     ((I2S_Type *)I2S1_BASE)
  /** Peripheral I2S1 base pointer */
  #define I2S1_NS                                  ((I2S_Type *)I2S1_BASE_NS)
  /** Peripheral I2S2 base address */
  #define I2S2_BASE                                (0x50088000u)
  /** Peripheral I2S2 base address */
  #define I2S2_BASE_NS                             (0x40088000u)
  /** Peripheral I2S2 base pointer */
  #define I2S2                                     ((I2S_Type *)I2S2_BASE)
  /** Peripheral I2S2 base pointer */
  #define I2S2_NS                                  ((I2S_Type *)I2S2_BASE_NS)
  /** Peripheral I2S3 base address */
  #define I2S3_BASE                                (0x50089000u)
  /** Peripheral I2S3 base address */
  #define I2S3_BASE_NS                             (0x40089000u)
  /** Peripheral I2S3 base pointer */
  #define I2S3                                     ((I2S_Type *)I2S3_BASE)
  /** Peripheral I2S3 base pointer */
  #define I2S3_NS                                  ((I2S_Type *)I2S3_BASE_NS)
  /** Peripheral I2S4 base address */
  #define I2S4_BASE                                (0x5008A000u)
  /** Peripheral I2S4 base address */
  #define I2S4_BASE_NS                             (0x4008A000u)
  /** Peripheral I2S4 base pointer */
  #define I2S4                                     ((I2S_Type *)I2S4_BASE)
  /** Peripheral I2S4 base pointer */
  #define I2S4_NS                                  ((I2S_Type *)I2S4_BASE_NS)
  /** Peripheral I2S5 base address */
  #define I2S5_BASE                                (0x50096000u)
  /** Peripheral I2S5 base address */
  #define I2S5_BASE_NS                             (0x40096000u)
  /** Peripheral I2S5 base pointer */
  #define I2S5                                     ((I2S_Type *)I2S5_BASE)
  /** Peripheral I2S5 base pointer */
  #define I2S5_NS                                  ((I2S_Type *)I2S5_BASE_NS)
  /** Peripheral I2S6 base address */
  #define I2S6_BASE                                (0x50097000u)
  /** Peripheral I2S6 base address */
  #define I2S6_BASE_NS                             (0x40097000u)
  /** Peripheral I2S6 base pointer */
  #define I2S6                                     ((I2S_Type *)I2S6_BASE)
  /** Peripheral I2S6 base pointer */
  #define I2S6_NS                                  ((I2S_Type *)I2S6_BASE_NS)
  /** Peripheral I2S7 base address */
  #define I2S7_BASE                                (0x50098000u)
  /** Peripheral I2S7 base address */
  #define I2S7_BASE_NS                             (0x40098000u)
  /** Peripheral I2S7 base pointer */
  #define I2S7                                     ((I2S_Type *)I2S7_BASE)
  /** Peripheral I2S7 base pointer */
  #define I2S7_NS                                  ((I2S_Type *)I2S7_BASE_NS)
  /** Array initializer of I2S peripheral base addresses */
  #define I2S_BASE_ADDRS                           { I2S0_BASE, I2S1_BASE, I2S2_BASE, I2S3_BASE, I2S4_BASE, I2S5_BASE, I2S6_BASE, I2S7_BASE }
  /** Array initializer of I2S peripheral base pointers */
  #define I2S_BASE_PTRS                            { I2S0, I2S1, I2S2, I2S3, I2S4, I2S5, I2S6, I2S7 }
  /** Array initializer of I2S peripheral base addresses */
  #define I2S_BASE_ADDRS_NS                        { I2S0_BASE_NS, I2S1_BASE_NS, I2S2_BASE_NS, I2S3_BASE_NS, I2S4_BASE_NS, I2S5_BASE_NS, I2S6_BASE_NS, I2S7_BASE_NS }
  /** Array initializer of I2S peripheral base pointers */
  #define I2S_BASE_PTRS_NS                         { I2S0_NS, I2S1_NS, I2S2_NS, I2S3_NS, I2S4_NS, I2S5_NS, I2S6_NS, I2S7_NS }
#else
  /** Peripheral I2S0 base address */
  #define I2S0_BASE                                (0x40086000u)
  /** Peripheral I2S0 base pointer */
  #define I2S0                                     ((I2S_Type *)I2S0_BASE)
  /** Peripheral I2S1 base address */
  #define I2S1_BASE                                (0x40087000u)
  /** Peripheral I2S1 base pointer */
  #define I2S1                                     ((I2S_Type *)I2S1_BASE)
  /** Peripheral I2S2 base address */
  #define I2S2_BASE                                (0x40088000u)
  /** Peripheral I2S2 base pointer */
  #define I2S2                                     ((I2S_Type *)I2S2_BASE)
  /** Peripheral I2S3 base address */
  #define I2S3_BASE                                (0x40089000u)
  /** Peripheral I2S3 base pointer */
  #define I2S3                                     ((I2S_Type *)I2S3_BASE)
  /** Peripheral I2S4 base address */
  #define I2S4_BASE                                (0x4008A000u)
  /** Peripheral I2S4 base pointer */
  #define I2S4                                     ((I2S_Type *)I2S4_BASE)
  /** Peripheral I2S5 base address */
  #define I2S5_BASE                                (0x40096000u)
  /** Peripheral I2S5 base pointer */
  #define I2S5                                     ((I2S_Type *)I2S5_BASE)
  /** Peripheral I2S6 base address */
  #define I2S6_BASE                                (0x40097000u)
  /** Peripheral I2S6 base pointer */
  #define I2S6                                     ((I2S_Type *)I2S6_BASE)
  /** Peripheral I2S7 base address */
  #define I2S7_BASE                                (0x40098000u)
  /** Peripheral I2S7 base pointer */
  #define I2S7                                     ((I2S_Type *)I2S7_BASE)
  /** Array initializer of I2S peripheral base addresses */
  #define I2S_BASE_ADDRS                           { I2S0_BASE, I2S1_BASE, I2S2_BASE, I2S3_BASE, I2S4_BASE, I2S5_BASE, I2S6_BASE, I2S7_BASE }
  /** Array initializer of I2S peripheral base pointers */
  #define I2S_BASE_PTRS                            { I2S0, I2S1, I2S2, I2S3, I2S4, I2S5, I2S6, I2S7 }
#endif
/** Interrupt vectors for the I2S peripheral type */
#define I2S_IRQS                                 { FLEXCOMM0_IRQn, FLEXCOMM1_IRQn, FLEXCOMM2_IRQn, FLEXCOMM3_IRQn, FLEXCOMM4_IRQn, FLEXCOMM5_IRQn, FLEXCOMM6_IRQn, FLEXCOMM7_IRQn }

/* INPUTMUX - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral INPUTMUX base address */
  #define INPUTMUX_BASE                            (0x50006000u)
  /** Peripheral INPUTMUX base address */
  #define INPUTMUX_BASE_NS                         (0x40006000u)
  /** Peripheral INPUTMUX base pointer */
  #define INPUTMUX                                 ((INPUTMUX_Type *)INPUTMUX_BASE)
  /** Peripheral INPUTMUX base pointer */
  #define INPUTMUX_NS                              ((INPUTMUX_Type *)INPUTMUX_BASE_NS)
  /** Array initializer of INPUTMUX peripheral base addresses */
  #define INPUTMUX_BASE_ADDRS                      { INPUTMUX_BASE }
  /** Array initializer of INPUTMUX peripheral base pointers */
  #define INPUTMUX_BASE_PTRS                       { INPUTMUX }
  /** Array initializer of INPUTMUX peripheral base addresses */
  #define INPUTMUX_BASE_ADDRS_NS                   { INPUTMUX_BASE_NS }
  /** Array initializer of INPUTMUX peripheral base pointers */
  #define INPUTMUX_BASE_PTRS_NS                    { INPUTMUX_NS }
#else
  /** Peripheral INPUTMUX base address */
  #define INPUTMUX_BASE                            (0x40006000u)
  /** Peripheral INPUTMUX base pointer */
  #define INPUTMUX                                 ((INPUTMUX_Type *)INPUTMUX_BASE)
  /** Array initializer of INPUTMUX peripheral base addresses */
  #define INPUTMUX_BASE_ADDRS                      { INPUTMUX_BASE }
  /** Array initializer of INPUTMUX peripheral base pointers */
  #define INPUTMUX_BASE_PTRS                       { INPUTMUX }
#endif

/* IOCON - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral IOCON base address */
  #define IOCON_BASE                               (0x50001000u)
  /** Peripheral IOCON base address */
  #define IOCON_BASE_NS                            (0x40001000u)
  /** Peripheral IOCON base pointer */
  #define IOCON                                    ((IOCON_Type *)IOCON_BASE)
  /** Peripheral IOCON base pointer */
  #define IOCON_NS                                 ((IOCON_Type *)IOCON_BASE_NS)
  /** Array initializer of IOCON peripheral base addresses */
  #define IOCON_BASE_ADDRS                         { IOCON_BASE }
  /** Array initializer of IOCON peripheral base pointers */
  #define IOCON_BASE_PTRS                          { IOCON }
  /** Array initializer of IOCON peripheral base addresses */
  #define IOCON_BASE_ADDRS_NS                      { IOCON_BASE_NS }
  /** Array initializer of IOCON peripheral base pointers */
  #define IOCON_BASE_PTRS_NS                       { IOCON_NS }
#else
  /** Peripheral IOCON base address */
  #define IOCON_BASE                               (0x40001000u)
  /** Peripheral IOCON base pointer */
  #define IOCON                                    ((IOCON_Type *)IOCON_BASE)
  /** Array initializer of IOCON peripheral base addresses */
  #define IOCON_BASE_ADDRS                         { IOCON_BASE }
  /** Array initializer of IOCON peripheral base pointers */
  #define IOCON_BASE_PTRS                          { IOCON }
#endif

/* MRT - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral MRT0 base address */
  #define MRT0_BASE                                (0x5000D000u)
  /** Peripheral MRT0 base address */
  #define MRT0_BASE_NS                             (0x4000D000u)
  /** Peripheral MRT0 base pointer */
  #define MRT0                                     ((MRT_Type *)MRT0_BASE)
  /** Peripheral MRT0 base pointer */
  #define MRT0_NS                                  ((MRT_Type *)MRT0_BASE_NS)
  /** Array initializer of MRT peripheral base addresses */
  #define MRT_BASE_ADDRS                           { MRT0_BASE }
  /** Array initializer of MRT peripheral base pointers */
  #define MRT_BASE_PTRS                            { MRT0 }
  /** Array initializer of MRT peripheral base addresses */
  #define MRT_BASE_ADDRS_NS                        { MRT0_BASE_NS }
  /** Array initializer of MRT peripheral base pointers */
  #define MRT_BASE_PTRS_NS                         { MRT0_NS }
#else
  /** Peripheral MRT0 base address */
  #define MRT0_BASE                                (0x4000D000u)
  /** Peripheral MRT0 base pointer */
  #define MRT0                                     ((MRT_Type *)MRT0_BASE)
  /** Array initializer of MRT peripheral base addresses */
  #define MRT_BASE_ADDRS                           { MRT0_BASE }
  /** Array initializer of MRT peripheral base pointers */
  #define MRT_BASE_PTRS                            { MRT0 }
#endif
/** Interrupt vectors for the MRT peripheral type */
#define MRT_IRQS                                 { MRT0_IRQn }

/* OSTIMER - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral OSTIMER base address */
  #define OSTIMER_BASE                             (0x5002D000u)
  /** Peripheral OSTIMER base address */
  #define OSTIMER_BASE_NS                          (0x4002D000u)
  /** Peripheral OSTIMER base pointer */
  #define OSTIMER                                  ((OSTIMER_Type *)OSTIMER_BASE)
  /** Peripheral OSTIMER base pointer */
  #define OSTIMER_NS                               ((OSTIMER_Type *)OSTIMER_BASE_NS)
  /** Array initializer of OSTIMER peripheral base addresses */
  #define OSTIMER_BASE_ADDRS                       { OSTIMER_BASE }
  /** Array initializer of OSTIMER peripheral base pointers */
  #define OSTIMER_BASE_PTRS                        { OSTIMER }
  /** Array initializer of OSTIMER peripheral base addresses */
  #define OSTIMER_BASE_ADDRS_NS                    { OSTIMER_BASE_NS }
  /** Array initializer of OSTIMER peripheral base pointers */
  #define OSTIMER_BASE_PTRS_NS                     { OSTIMER_NS }
#else
  /** Peripheral OSTIMER base address */
  #define OSTIMER_BASE                             (0x4002D000u)
  /** Peripheral OSTIMER base pointer */
  #define OSTIMER                                  ((OSTIMER_Type *)OSTIMER_BASE)
  /** Array initializer of OSTIMER peripheral base addresses */
  #define OSTIMER_BASE_ADDRS                       { OSTIMER_BASE }
  /** Array initializer of OSTIMER peripheral base pointers */
  #define OSTIMER_BASE_PTRS                        { OSTIMER }
#endif
/** Interrupt vectors for the OSTIMER peripheral type */
#define OSTIMER_IRQS                             { OS_EVENT_IRQn }

/* PINT - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral PINT base address */
  #define PINT_BASE                                (0x50004000u)
  /** Peripheral PINT base address */
  #define PINT_BASE_NS                             (0x40004000u)
  /** Peripheral PINT base pointer */
  #define PINT                                     ((PINT_Type *)PINT_BASE)
  /** Peripheral PINT base pointer */
  #define PINT_NS                                  ((PINT_Type *)PINT_BASE_NS)
  /** Peripheral SECPINT base address */
  #define SECPINT_BASE                             (0x50005000u)
  /** Peripheral SECPINT base address */
  #define SECPINT_BASE_NS                          (0x40005000u)
  /** Peripheral SECPINT base pointer */
  #define SECPINT                                  ((PINT_Type *)SECPINT_BASE)
  /** Peripheral SECPINT base pointer */
  #define SECPINT_NS                               ((PINT_Type *)SECPINT_BASE_NS)
  /** Array initializer of PINT peripheral base addresses */
  #define PINT_BASE_ADDRS                          { PINT_BASE, SECPINT_BASE }
  /** Array initializer of PINT peripheral base pointers */
  #define PINT_BASE_PTRS                           { PINT, SECPINT }
  /** Array initializer of PINT peripheral base addresses */
  #define PINT_BASE_ADDRS_NS                       { PINT_BASE_NS, SECPINT_BASE_NS }
  /** Array initializer of PINT peripheral base pointers */
  #define PINT_BASE_PTRS_NS                        { PINT_NS, SECPINT_NS }
#else
  /** Peripheral PINT base address */
  #define PINT_BASE                                (0x40004000u)
  /** Peripheral PINT base pointer */
  #define PINT                                     ((PINT_Type *)PINT_BASE)
  /** Peripheral SECPINT base address */
  #define SECPINT_BASE                             (0x40005000u)
  /** Peripheral SECPINT base pointer */
  #define SECPINT                                  ((PINT_Type *)SECPINT_BASE)
  /** Array initializer of PINT peripheral base addresses */
  #define PINT_BASE_ADDRS                          { PINT_BASE, SECPINT_BASE }
  /** Array initializer of PINT peripheral base pointers */
  #define PINT_BASE_PTRS                           { PINT, SECPINT }
#endif
/** Interrupt vectors for the PINT peripheral type */
#define PINT_IRQS                                { PIN_INT0_IRQn, PIN_INT1_IRQn, PIN_INT2_IRQn, PIN_INT3_IRQn, PIN_INT4_IRQn, PIN_INT5_IRQn, PIN_INT6_IRQn, PIN_INT7_IRQn, SEC_GPIO_INT0_IRQ0_IRQn, SEC_GPIO_INT0_IRQ1_IRQn }

/* PLU - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral PLU base address */
  #define PLU_BASE                                 (0x5003D000u)
  /** Peripheral PLU base address */
  #define PLU_BASE_NS                              (0x4003D000u)
  /** Peripheral PLU base pointer */
  #define PLU                                      ((PLU_Type *)PLU_BASE)
  /** Peripheral PLU base pointer */
  #define PLU_NS                                   ((PLU_Type *)PLU_BASE_NS)
  /** Array initializer of PLU peripheral base addresses */
  #define PLU_BASE_ADDRS                           { PLU_BASE }
  /** Array initializer of PLU peripheral base pointers */
  #define PLU_BASE_PTRS                            { PLU }
  /** Array initializer of PLU peripheral base addresses */
  #define PLU_BASE_ADDRS_NS                        { PLU_BASE_NS }
  /** Array initializer of PLU peripheral base pointers */
  #define PLU_BASE_PTRS_NS                         { PLU_NS }
#else
  /** Peripheral PLU base address */
  #define PLU_BASE                                 (0x4003D000u)
  /** Peripheral PLU base pointer */
  #define PLU                                      ((PLU_Type *)PLU_BASE)
  /** Array initializer of PLU peripheral base addresses */
  #define PLU_BASE_ADDRS                           { PLU_BASE }
  /** Array initializer of PLU peripheral base pointers */
  #define PLU_BASE_PTRS                            { PLU }
#endif

/* PMC - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral PMC base address */
  #define PMC_BASE                                 (0x50020000u)
  /** Peripheral PMC base address */
  #define PMC_BASE_NS                              (0x40020000u)
  /** Peripheral PMC base pointer */
  #define PMC                                      ((PMC_Type *)PMC_BASE)
  /** Peripheral PMC base pointer */
  #define PMC_NS                                   ((PMC_Type *)PMC_BASE_NS)
  /** Array initializer of PMC peripheral base addresses */
  #define PMC_BASE_ADDRS                           { PMC_BASE }
  /** Array initializer of PMC peripheral base pointers */
  #define PMC_BASE_PTRS                            { PMC }
  /** Array initializer of PMC peripheral base addresses */
  #define PMC_BASE_ADDRS_NS                        { PMC_BASE_NS }
  /** Array initializer of PMC peripheral base pointers */
  #define PMC_BASE_PTRS_NS                         { PMC_NS }
#else
  /** Peripheral PMC base address */
  #define PMC_BASE                                 (0x40020000u)
  /** Peripheral PMC base pointer */
  #define PMC                                      ((PMC_Type *)PMC_BASE)
  /** Array initializer of PMC peripheral base addresses */
  #define PMC_BASE_ADDRS                           { PMC_BASE }
  /** Array initializer of PMC peripheral base pointers */
  #define PMC_BASE_PTRS                            { PMC }
#endif

/* PRINCE - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral PRINCE base address */
  #define PRINCE_BASE                              (0x50035000u)
  /** Peripheral PRINCE base address */
  #define PRINCE_BASE_NS                           (0x40035000u)
  /** Peripheral PRINCE base pointer */
  #define PRINCE                                   ((PRINCE_Type *)PRINCE_BASE)
  /** Peripheral PRINCE base pointer */
  #define PRINCE_NS                                ((PRINCE_Type *)PRINCE_BASE_NS)
  /** Array initializer of PRINCE peripheral base addresses */
  #define PRINCE_BASE_ADDRS                        { PRINCE_BASE }
  /** Array initializer of PRINCE peripheral base pointers */
  #define PRINCE_BASE_PTRS                         { PRINCE }
  /** Array initializer of PRINCE peripheral base addresses */
  #define PRINCE_BASE_ADDRS_NS                     { PRINCE_BASE_NS }
  /** Array initializer of PRINCE peripheral base pointers */
  #define PRINCE_BASE_PTRS_NS                      { PRINCE_NS }
#else
  /** Peripheral PRINCE base address */
  #define PRINCE_BASE                              (0x40035000u)
  /** Peripheral PRINCE base pointer */
  #define PRINCE                                   ((PRINCE_Type *)PRINCE_BASE)
  /** Array initializer of PRINCE peripheral base addresses */
  #define PRINCE_BASE_ADDRS                        { PRINCE_BASE }
  /** Array initializer of PRINCE peripheral base pointers */
  #define PRINCE_BASE_PTRS                         { PRINCE }
#endif

/* PUF - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral PUF base address */
  #define PUF_BASE                                 (0x5003B000u)
  /** Peripheral PUF base address */
  #define PUF_BASE_NS                              (0x4003B000u)
  /** Peripheral PUF base pointer */
  #define PUF                                      ((PUF_Type *)PUF_BASE)
  /** Peripheral PUF base pointer */
  #define PUF_NS                                   ((PUF_Type *)PUF_BASE_NS)
  /** Array initializer of PUF peripheral base addresses */
  #define PUF_BASE_ADDRS                           { PUF_BASE }
  /** Array initializer of PUF peripheral base pointers */
  #define PUF_BASE_PTRS                            { PUF }
  /** Array initializer of PUF peripheral base addresses */
  #define PUF_BASE_ADDRS_NS                        { PUF_BASE_NS }
  /** Array initializer of PUF peripheral base pointers */
  #define PUF_BASE_PTRS_NS                         { PUF_NS }
#else
  /** Peripheral PUF base address */
  #define PUF_BASE                                 (0x4003B000u)
  /** Peripheral PUF base pointer */
  #define PUF                                      ((PUF_Type *)PUF_BASE)
  /** Array initializer of PUF peripheral base addresses */
  #define PUF_BASE_ADDRS                           { PUF_BASE }
  /** Array initializer of PUF peripheral base pointers */
  #define PUF_BASE_PTRS                            { PUF }
#endif
/** Interrupt vectors for the PUF peripheral type */
#define PUF_IRQS                                 { PUF_IRQn }

/* PUF_SRAM_CTRL - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral PUF_SRAM_CTRL base address */
  #define PUF_SRAM_CTRL_BASE                       (0x5003B000u)
  /** Peripheral PUF_SRAM_CTRL base address */
  #define PUF_SRAM_CTRL_BASE_NS                    (0x4003B000u)
  /** Peripheral PUF_SRAM_CTRL base pointer */
  #define PUF_SRAM_CTRL                            ((PUF_SRAM_CTRL_Type *)PUF_SRAM_CTRL_BASE)
  /** Peripheral PUF_SRAM_CTRL base pointer */
  #define PUF_SRAM_CTRL_NS                         ((PUF_SRAM_CTRL_Type *)PUF_SRAM_CTRL_BASE_NS)
  /** Array initializer of PUF_SRAM_CTRL peripheral base addresses */
  #define PUF_SRAM_CTRL_BASE_ADDRS                 { PUF_SRAM_CTRL_BASE }
  /** Array initializer of PUF_SRAM_CTRL peripheral base pointers */
  #define PUF_SRAM_CTRL_BASE_PTRS                  { PUF_SRAM_CTRL }
  /** Array initializer of PUF_SRAM_CTRL peripheral base addresses */
  #define PUF_SRAM_CTRL_BASE_ADDRS_NS              { PUF_SRAM_CTRL_BASE_NS }
  /** Array initializer of PUF_SRAM_CTRL peripheral base pointers */
  #define PUF_SRAM_CTRL_BASE_PTRS_NS               { PUF_SRAM_CTRL_NS }
#else
  /** Peripheral PUF_SRAM_CTRL base address */
  #define PUF_SRAM_CTRL_BASE                       (0x4003B000u)
  /** Peripheral PUF_SRAM_CTRL base pointer */
  #define PUF_SRAM_CTRL                            ((PUF_SRAM_CTRL_Type *)PUF_SRAM_CTRL_BASE)
  /** Array initializer of PUF_SRAM_CTRL peripheral base addresses */
  #define PUF_SRAM_CTRL_BASE_ADDRS                 { PUF_SRAM_CTRL_BASE }
  /** Array initializer of PUF_SRAM_CTRL peripheral base pointers */
  #define PUF_SRAM_CTRL_BASE_PTRS                  { PUF_SRAM_CTRL }
#endif

/* RNG - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral RNG base address */
  #define RNG_BASE                                 (0x5003A000u)
  /** Peripheral RNG base address */
  #define RNG_BASE_NS                              (0x4003A000u)
  /** Peripheral RNG base pointer */
  #define RNG                                      ((RNG_Type *)RNG_BASE)
  /** Peripheral RNG base pointer */
  #define RNG_NS                                   ((RNG_Type *)RNG_BASE_NS)
  /** Array initializer of RNG peripheral base addresses */
  #define RNG_BASE_ADDRS                           { RNG_BASE }
  /** Array initializer of RNG peripheral base pointers */
  #define RNG_BASE_PTRS                            { RNG }
  /** Array initializer of RNG peripheral base addresses */
  #define RNG_BASE_ADDRS_NS                        { RNG_BASE_NS }
  /** Array initializer of RNG peripheral base pointers */
  #define RNG_BASE_PTRS_NS                         { RNG_NS }
#else
  /** Peripheral RNG base address */
  #define RNG_BASE                                 (0x4003A000u)
  /** Peripheral RNG base pointer */
  #define RNG                                      ((RNG_Type *)RNG_BASE)
  /** Array initializer of RNG peripheral base addresses */
  #define RNG_BASE_ADDRS                           { RNG_BASE }
  /** Array initializer of RNG peripheral base pointers */
  #define RNG_BASE_PTRS                            { RNG }
#endif

/* RTC - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral RTC base address */
  #define RTC_BASE                                 (0x5002C000u)
  /** Peripheral RTC base address */
  #define RTC_BASE_NS                              (0x4002C000u)
  /** Peripheral RTC base pointer */
  #define RTC                                      ((RTC_Type *)RTC_BASE)
  /** Peripheral RTC base pointer */
  #define RTC_NS                                   ((RTC_Type *)RTC_BASE_NS)
  /** Array initializer of RTC peripheral base addresses */
  #define RTC_BASE_ADDRS                           { RTC_BASE }
  /** Array initializer of RTC peripheral base pointers */
  #define RTC_BASE_PTRS                            { RTC }
  /** Array initializer of RTC peripheral base addresses */
  #define RTC_BASE_ADDRS_NS                        { RTC_BASE_NS }
  /** Array initializer of RTC peripheral base pointers */
  #define RTC_BASE_PTRS_NS                         { RTC_NS }
#else
  /** Peripheral RTC base address */
  #define RTC_BASE                                 (0x4002C000u)
  /** Peripheral RTC base pointer */
  #define RTC                                      ((RTC_Type *)RTC_BASE)
  /** Array initializer of RTC peripheral base addresses */
  #define RTC_BASE_ADDRS                           { RTC_BASE }
  /** Array initializer of RTC peripheral base pointers */
  #define RTC_BASE_PTRS                            { RTC }
#endif
/** Interrupt vectors for the RTC peripheral type */
#define RTC_IRQS                                 { RTC_IRQn }

/* SCT - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral SCT0 base address */
  #define SCT0_BASE                                (0x50085000u)
  /** Peripheral SCT0 base address */
  #define SCT0_BASE_NS                             (0x40085000u)
  /** Peripheral SCT0 base pointer */
  #define SCT0                                     ((SCT_Type *)SCT0_BASE)
  /** Peripheral SCT0 base pointer */
  #define SCT0_NS                                  ((SCT_Type *)SCT0_BASE_NS)
  /** Array initializer of SCT peripheral base addresses */
  #define SCT_BASE_ADDRS                           { SCT0_BASE }
  /** Array initializer of SCT peripheral base pointers */
  #define SCT_BASE_PTRS                            { SCT0 }
  /** Array initializer of SCT peripheral base addresses */
  #define SCT_BASE_ADDRS_NS                        { SCT0_BASE_NS }
  /** Array initializer of SCT peripheral base pointers */
  #define SCT_BASE_PTRS_NS                         { SCT0_NS }
#else
  /** Peripheral SCT0 base address */
  #define SCT0_BASE                                (0x40085000u)
  /** Peripheral SCT0 base pointer */
  #define SCT0                                     ((SCT_Type *)SCT0_BASE)
  /** Array initializer of SCT peripheral base addresses */
  #define SCT_BASE_ADDRS                           { SCT0_BASE }
  /** Array initializer of SCT peripheral base pointers */
  #define SCT_BASE_PTRS                            { SCT0 }
#endif
/** Interrupt vectors for the SCT peripheral type */
#define SCT_IRQS                                 { SCT0_IRQn }

/* SPI - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral SPI0 base address */
  #define SPI0_BASE                                (0x50086000u)
  /** Peripheral SPI0 base address */
  #define SPI0_BASE_NS                             (0x40086000u)
  /** Peripheral SPI0 base pointer */
  #define SPI0                                     ((SPI_Type *)SPI0_BASE)
  /** Peripheral SPI0 base pointer */
  #define SPI0_NS                                  ((SPI_Type *)SPI0_BASE_NS)
  /** Peripheral SPI1 base address */
  #define SPI1_BASE                                (0x50087000u)
  /** Peripheral SPI1 base address */
  #define SPI1_BASE_NS                             (0x40087000u)
  /** Peripheral SPI1 base pointer */
  #define SPI1                                     ((SPI_Type *)SPI1_BASE)
  /** Peripheral SPI1 base pointer */
  #define SPI1_NS                                  ((SPI_Type *)SPI1_BASE_NS)
  /** Peripheral SPI2 base address */
  #define SPI2_BASE                                (0x50088000u)
  /** Peripheral SPI2 base address */
  #define SPI2_BASE_NS                             (0x40088000u)
  /** Peripheral SPI2 base pointer */
  #define SPI2                                     ((SPI_Type *)SPI2_BASE)
  /** Peripheral SPI2 base pointer */
  #define SPI2_NS                                  ((SPI_Type *)SPI2_BASE_NS)
  /** Peripheral SPI3 base address */
  #define SPI3_BASE                                (0x50089000u)
  /** Peripheral SPI3 base address */
  #define SPI3_BASE_NS                             (0x40089000u)
  /** Peripheral SPI3 base pointer */
  #define SPI3                                     ((SPI_Type *)SPI3_BASE)
  /** Peripheral SPI3 base pointer */
  #define SPI3_NS                                  ((SPI_Type *)SPI3_BASE_NS)
  /** Peripheral SPI4 base address */
  #define SPI4_BASE                                (0x5008A000u)
  /** Peripheral SPI4 base address */
  #define SPI4_BASE_NS                             (0x4008A000u)
  /** Peripheral SPI4 base pointer */
  #define SPI4                                     ((SPI_Type *)SPI4_BASE)
  /** Peripheral SPI4 base pointer */
  #define SPI4_NS                                  ((SPI_Type *)SPI4_BASE_NS)
  /** Peripheral SPI5 base address */
  #define SPI5_BASE                                (0x50096000u)
  /** Peripheral SPI5 base address */
  #define SPI5_BASE_NS                             (0x40096000u)
  /** Peripheral SPI5 base pointer */
  #define SPI5                                     ((SPI_Type *)SPI5_BASE)
  /** Peripheral SPI5 base pointer */
  #define SPI5_NS                                  ((SPI_Type *)SPI5_BASE_NS)
  /** Peripheral SPI6 base address */
  #define SPI6_BASE                                (0x50097000u)
  /** Peripheral SPI6 base address */
  #define SPI6_BASE_NS                             (0x40097000u)
  /** Peripheral SPI6 base pointer */
  #define SPI6                                     ((SPI_Type *)SPI6_BASE)
  /** Peripheral SPI6 base pointer */
  #define SPI6_NS                                  ((SPI_Type *)SPI6_BASE_NS)
  /** Peripheral SPI7 base address */
  #define SPI7_BASE                                (0x50098000u)
  /** Peripheral SPI7 base address */
  #define SPI7_BASE_NS                             (0x40098000u)
  /** Peripheral SPI7 base pointer */
  #define SPI7                                     ((SPI_Type *)SPI7_BASE)
  /** Peripheral SPI7 base pointer */
  #define SPI7_NS                                  ((SPI_Type *)SPI7_BASE_NS)
  /** Peripheral SPI8 base address */
  #define SPI8_BASE                                (0x5009F000u)
  /** Peripheral SPI8 base address */
  #define SPI8_BASE_NS                             (0x4009F000u)
  /** Peripheral SPI8 base pointer */
  #define SPI8                                     ((SPI_Type *)SPI8_BASE)
  /** Peripheral SPI8 base pointer */
  #define SPI8_NS                                  ((SPI_Type *)SPI8_BASE_NS)
  /** Array initializer of SPI peripheral base addresses */
  #define SPI_BASE_ADDRS                           { SPI0_BASE, SPI1_BASE, SPI2_BASE, SPI3_BASE, SPI4_BASE, SPI5_BASE, SPI6_BASE, SPI7_BASE, SPI8_BASE }
  /** Array initializer of SPI peripheral base pointers */
  #define SPI_BASE_PTRS                            { SPI0, SPI1, SPI2, SPI3, SPI4, SPI5, SPI6, SPI7, SPI8 }
  /** Array initializer of SPI peripheral base addresses */
  #define SPI_BASE_ADDRS_NS                        { SPI0_BASE_NS, SPI1_BASE_NS, SPI2_BASE_NS, SPI3_BASE_NS, SPI4_BASE_NS, SPI5_BASE_NS, SPI6_BASE_NS, SPI7_BASE_NS, SPI8_BASE_NS }
  /** Array initializer of SPI peripheral base pointers */
  #define SPI_BASE_PTRS_NS                         { SPI0_NS, SPI1_NS, SPI2_NS, SPI3_NS, SPI4_NS, SPI5_NS, SPI6_NS, SPI7_NS, SPI8_NS }
#else
  /** Peripheral SPI0 base address */
  #define SPI0_BASE                                (0x40086000u)
  /** Peripheral SPI0 base pointer */
  #define SPI0                                     ((SPI_Type *)SPI0_BASE)
  /** Peripheral SPI1 base address */
  #define SPI1_BASE                                (0x40087000u)
  /** Peripheral SPI1 base pointer */
  #define SPI1                                     ((SPI_Type *)SPI1_BASE)
  /** Peripheral SPI2 base address */
  #define SPI2_BASE                                (0x40088000u)
  /** Peripheral SPI2 base pointer */
  #define SPI2                                     ((SPI_Type *)SPI2_BASE)
  /** Peripheral SPI3 base address */
  #define SPI3_BASE                                (0x40089000u)
  /** Peripheral SPI3 base pointer */
  #define SPI3                                     ((SPI_Type *)SPI3_BASE)
  /** Peripheral SPI4 base address */
  #define SPI4_BASE                                (0x4008A000u)
  /** Peripheral SPI4 base pointer */
  #define SPI4                                     ((SPI_Type *)SPI4_BASE)
  /** Peripheral SPI5 base address */
  #define SPI5_BASE                                (0x40096000u)
  /** Peripheral SPI5 base pointer */
  #define SPI5                                     ((SPI_Type *)SPI5_BASE)
  /** Peripheral SPI6 base address */
  #define SPI6_BASE                                (0x40097000u)
  /** Peripheral SPI6 base pointer */
  #define SPI6                                     ((SPI_Type *)SPI6_BASE)
  /** Peripheral SPI7 base address */
  #define SPI7_BASE                                (0x40098000u)
  /** Peripheral SPI7 base pointer */
  #define SPI7                                     ((SPI_Type *)SPI7_BASE)
  /** Peripheral SPI8 base address */
  #define SPI8_BASE                                (0x4009F000u)
  /** Peripheral SPI8 base pointer */
  #define SPI8                                     ((SPI_Type *)SPI8_BASE)
  /** Array initializer of SPI peripheral base addresses */
  #define SPI_BASE_ADDRS                           { SPI0_BASE, SPI1_BASE, SPI2_BASE, SPI3_BASE, SPI4_BASE, SPI5_BASE, SPI6_BASE, SPI7_BASE, SPI8_BASE }
  /** Array initializer of SPI peripheral base pointers */
  #define SPI_BASE_PTRS                            { SPI0, SPI1, SPI2, SPI3, SPI4, SPI5, SPI6, SPI7, SPI8 }
#endif
/** Interrupt vectors for the SPI peripheral type */
#define SPI_IRQS                                 { FLEXCOMM0_IRQn, FLEXCOMM1_IRQn, FLEXCOMM2_IRQn, FLEXCOMM3_IRQn, FLEXCOMM4_IRQn, FLEXCOMM5_IRQn, FLEXCOMM6_IRQn, FLEXCOMM7_IRQn, FLEXCOMM8_IRQn }

/* SYSCON - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral SYSCON base address */
  #define SYSCON_BASE                              (0x50000000u)
  /** Peripheral SYSCON base address */
  #define SYSCON_BASE_NS                           (0x40000000u)
  /** Peripheral SYSCON base pointer */
  #define SYSCON                                   ((SYSCON_Type *)SYSCON_BASE)
  /** Peripheral SYSCON base pointer */
  #define SYSCON_NS                                ((SYSCON_Type *)SYSCON_BASE_NS)
  /** Array initializer of SYSCON peripheral base addresses */
  #define SYSCON_BASE_ADDRS                        { SYSCON_BASE }
  /** Array initializer of SYSCON peripheral base pointers */
  #define SYSCON_BASE_PTRS                         { SYSCON }
  /** Array initializer of SYSCON peripheral base addresses */
  #define SYSCON_BASE_ADDRS_NS                     { SYSCON_BASE_NS }
  /** Array initializer of SYSCON peripheral base pointers */
  #define SYSCON_BASE_PTRS_NS                      { SYSCON_NS }
#else
  /** Peripheral SYSCON base address */
  #define SYSCON_BASE                              (0x40000000u)
  /** Peripheral SYSCON base pointer */
  #define SYSCON                                   ((SYSCON_Type *)SYSCON_BASE)
  /** Array initializer of SYSCON peripheral base addresses */
  #define SYSCON_BASE_ADDRS                        { SYSCON_BASE }
  /** Array initializer of SYSCON peripheral base pointers */
  #define SYSCON_BASE_PTRS                         { SYSCON }
#endif

/* SYSCTL - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral SYSCTL base address */
  #define SYSCTL_BASE                              (0x50023000u)
  /** Peripheral SYSCTL base address */
  #define SYSCTL_BASE_NS                           (0x40023000u)
  /** Peripheral SYSCTL base pointer */
  #define SYSCTL                                   ((SYSCTL_Type *)SYSCTL_BASE)
  /** Peripheral SYSCTL base pointer */
  #define SYSCTL_NS                                ((SYSCTL_Type *)SYSCTL_BASE_NS)
  /** Array initializer of SYSCTL peripheral base addresses */
  #define SYSCTL_BASE_ADDRS                        { SYSCTL_BASE }
  /** Array initializer of SYSCTL peripheral base pointers */
  #define SYSCTL_BASE_PTRS                         { SYSCTL }
  /** Array initializer of SYSCTL peripheral base addresses */
  #define SYSCTL_BASE_ADDRS_NS                     { SYSCTL_BASE_NS }
  /** Array initializer of SYSCTL peripheral base pointers */
  #define SYSCTL_BASE_PTRS_NS                      { SYSCTL_NS }
#else
  /** Peripheral SYSCTL base address */
  #define SYSCTL_BASE                              (0x40023000u)
  /** Peripheral SYSCTL base pointer */
  #define SYSCTL                                   ((SYSCTL_Type *)SYSCTL_BASE)
  /** Array initializer of SYSCTL peripheral base addresses */
  #define SYSCTL_BASE_ADDRS                        { SYSCTL_BASE }
  /** Array initializer of SYSCTL peripheral base pointers */
  #define SYSCTL_BASE_PTRS                         { SYSCTL }
#endif

/* USART - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral USART0 base address */
  #define USART0_BASE                              (0x50086000u)
  /** Peripheral USART0 base address */
  #define USART0_BASE_NS                           (0x40086000u)
  /** Peripheral USART0 base pointer */
  #define USART0                                   ((USART_Type *)USART0_BASE)
  /** Peripheral USART0 base pointer */
  #define USART0_NS                                ((USART_Type *)USART0_BASE_NS)
  /** Peripheral USART1 base address */
  #define USART1_BASE                              (0x50087000u)
  /** Peripheral USART1 base address */
  #define USART1_BASE_NS                           (0x40087000u)
  /** Peripheral USART1 base pointer */
  #define USART1                                   ((USART_Type *)USART1_BASE)
  /** Peripheral USART1 base pointer */
  #define USART1_NS                                ((USART_Type *)USART1_BASE_NS)
  /** Peripheral USART2 base address */
  #define USART2_BASE                              (0x50088000u)
  /** Peripheral USART2 base address */
  #define USART2_BASE_NS                           (0x40088000u)
  /** Peripheral USART2 base pointer */
  #define USART2                                   ((USART_Type *)USART2_BASE)
  /** Peripheral USART2 base pointer */
  #define USART2_NS                                ((USART_Type *)USART2_BASE_NS)
  /** Peripheral USART3 base address */
  #define USART3_BASE                              (0x50089000u)
  /** Peripheral USART3 base address */
  #define USART3_BASE_NS                           (0x40089000u)
  /** Peripheral USART3 base pointer */
  #define USART3                                   ((USART_Type *)USART3_BASE)
  /** Peripheral USART3 base pointer */
  #define USART3_NS                                ((USART_Type *)USART3_BASE_NS)
  /** Peripheral USART4 base address */
  #define USART4_BASE                              (0x5008A000u)
  /** Peripheral USART4 base address */
  #define USART4_BASE_NS                           (0x4008A000u)
  /** Peripheral USART4 base pointer */
  #define USART4                                   ((USART_Type *)USART4_BASE)
  /** Peripheral USART4 base pointer */
  #define USART4_NS                                ((USART_Type *)USART4_BASE_NS)
  /** Peripheral USART5 base address */
  #define USART5_BASE                              (0x50096000u)
  /** Peripheral USART5 base address */
  #define USART5_BASE_NS                           (0x40096000u)
  /** Peripheral USART5 base pointer */
  #define USART5                                   ((USART_Type *)USART5_BASE)
  /** Peripheral USART5 base pointer */
  #define USART5_NS                                ((USART_Type *)USART5_BASE_NS)
  /** Peripheral USART6 base address */
  #define USART6_BASE                              (0x50097000u)
  /** Peripheral USART6 base address */
  #define USART6_BASE_NS                           (0x40097000u)
  /** Peripheral USART6 base pointer */
  #define USART6                                   ((USART_Type *)USART6_BASE)
  /** Peripheral USART6 base pointer */
  #define USART6_NS                                ((USART_Type *)USART6_BASE_NS)
  /** Peripheral USART7 base address */
  #define USART7_BASE                              (0x50098000u)
  /** Peripheral USART7 base address */
  #define USART7_BASE_NS                           (0x40098000u)
  /** Peripheral USART7 base pointer */
  #define USART7                                   ((USART_Type *)USART7_BASE)
  /** Peripheral USART7 base pointer */
  #define USART7_NS                                ((USART_Type *)USART7_BASE_NS)
  /** Array initializer of USART peripheral base addresses */
  #define USART_BASE_ADDRS                         { USART0_BASE, USART1_BASE, USART2_BASE, USART3_BASE, USART4_BASE, USART5_BASE, USART6_BASE, USART7_BASE }
  /** Array initializer of USART peripheral base pointers */
  #define USART_BASE_PTRS                          { USART0, USART1, USART2, USART3, USART4, USART5, USART6, USART7 }
  /** Array initializer of USART peripheral base addresses */
  #define USART_BASE_ADDRS_NS                      { USART0_BASE_NS, USART1_BASE_NS, USART2_BASE_NS, USART3_BASE_NS, USART4_BASE_NS, USART5_BASE_NS, USART6_BASE_NS, USART7_BASE_NS }
  /** Array initializer of USART peripheral base pointers */
  #define USART_BASE_PTRS_NS                       { USART0_NS, USART1_NS, USART2_NS, USART3_NS, USART4_NS, USART5_NS, USART6_NS, USART7_NS }
#else
  /** Peripheral USART0 base address */
  #define USART0_BASE                              (0x40086000u)
  /** Peripheral USART0 base pointer */
  #define USART0                                   ((USART_Type *)USART0_BASE)
  /** Peripheral USART1 base address */
  #define USART1_BASE                              (0x40087000u)
  /** Peripheral USART1 base pointer */
  #define USART1                                   ((USART_Type *)USART1_BASE)
  /** Peripheral USART2 base address */
  #define USART2_BASE                              (0x40088000u)
  /** Peripheral USART2 base pointer */
  #define USART2                                   ((USART_Type *)USART2_BASE)
  /** Peripheral USART3 base address */
  #define USART3_BASE                              (0x40089000u)
  /** Peripheral USART3 base pointer */
  #define USART3                                   ((USART_Type *)USART3_BASE)
  /** Peripheral USART4 base address */
  #define USART4_BASE                              (0x4008A000u)
  /** Peripheral USART4 base pointer */
  #define USART4                                   ((USART_Type *)USART4_BASE)
  /** Peripheral USART5 base address */
  #define USART5_BASE                              (0x40096000u)
  /** Peripheral USART5 base pointer */
  #define USART5                                   ((USART_Type *)USART5_BASE)
  /** Peripheral USART6 base address */
  #define USART6_BASE                              (0x40097000u)
  /** Peripheral USART6 base pointer */
  #define USART6                                   ((USART_Type *)USART6_BASE)
  /** Peripheral USART7 base address */
  #define USART7_BASE                              (0x40098000u)
  /** Peripheral USART7 base pointer */
  #define USART7                                   ((USART_Type *)USART7_BASE)
  /** Array initializer of USART peripheral base addresses */
  #define USART_BASE_ADDRS                         { USART0_BASE, USART1_BASE, USART2_BASE, USART3_BASE, USART4_BASE, USART5_BASE, USART6_BASE, USART7_BASE }
  /** Array initializer of USART peripheral base pointers */
  #define USART_BASE_PTRS                          { USART0, USART1, USART2, USART3, USART4, USART5, USART6, USART7 }
#endif
/** Interrupt vectors for the USART peripheral type */
#define USART_IRQS                               { FLEXCOMM0_IRQn, FLEXCOMM1_IRQn, FLEXCOMM2_IRQn, FLEXCOMM3_IRQn, FLEXCOMM4_IRQn, FLEXCOMM5_IRQn, FLEXCOMM6_IRQn, FLEXCOMM7_IRQn }

/* USB - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral USB0 base address */
  #define USB0_BASE                                (0x50084000u)
  /** Peripheral USB0 base address */
  #define USB0_BASE_NS                             (0x40084000u)
  /** Peripheral USB0 base pointer */
  #define USB0                                     ((USB_Type *)USB0_BASE)
  /** Peripheral USB0 base pointer */
  #define USB0_NS                                  ((USB_Type *)USB0_BASE_NS)
  /** Array initializer of USB peripheral base addresses */
  #define USB_BASE_ADDRS                           { USB0_BASE }
  /** Array initializer of USB peripheral base pointers */
  #define USB_BASE_PTRS                            { USB0 }
  /** Array initializer of USB peripheral base addresses */
  #define USB_BASE_ADDRS_NS                        { USB0_BASE_NS }
  /** Array initializer of USB peripheral base pointers */
  #define USB_BASE_PTRS_NS                         { USB0_NS }
#else
  /** Peripheral USB0 base address */
  #define USB0_BASE                                (0x40084000u)
  /** Peripheral USB0 base pointer */
  #define USB0                                     ((USB_Type *)USB0_BASE)
  /** Array initializer of USB peripheral base addresses */
  #define USB_BASE_ADDRS                           { USB0_BASE }
  /** Array initializer of USB peripheral base pointers */
  #define USB_BASE_PTRS                            { USB0 }
#endif
/** Interrupt vectors for the USB peripheral type */
#define USB_IRQS                                 { USB0_IRQn }
#define USB_NEEDCLK_IRQS                         { USB0_NEEDCLK_IRQn }

/* USBFSH - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral USBFSH base address */
  #define USBFSH_BASE                              (0x500A2000u)
  /** Peripheral USBFSH base address */
  #define USBFSH_BASE_NS                           (0x400A2000u)
  /** Peripheral USBFSH base pointer */
  #define USBFSH                                   ((USBFSH_Type *)USBFSH_BASE)
  /** Peripheral USBFSH base pointer */
  #define USBFSH_NS                                ((USBFSH_Type *)USBFSH_BASE_NS)
  /** Array initializer of USBFSH peripheral base addresses */
  #define USBFSH_BASE_ADDRS                        { USBFSH_BASE }
  /** Array initializer of USBFSH peripheral base pointers */
  #define USBFSH_BASE_PTRS                         { USBFSH }
  /** Array initializer of USBFSH peripheral base addresses */
  #define USBFSH_BASE_ADDRS_NS                     { USBFSH_BASE_NS }
  /** Array initializer of USBFSH peripheral base pointers */
  #define USBFSH_BASE_PTRS_NS                      { USBFSH_NS }
#else
  /** Peripheral USBFSH base address */
  #define USBFSH_BASE                              (0x400A2000u)
  /** Peripheral USBFSH base pointer */
  #define USBFSH                                   ((USBFSH_Type *)USBFSH_BASE)
  /** Array initializer of USBFSH peripheral base addresses */
  #define USBFSH_BASE_ADDRS                        { USBFSH_BASE }
  /** Array initializer of USBFSH peripheral base pointers */
  #define USBFSH_BASE_PTRS                         { USBFSH }
#endif
/** Interrupt vectors for the USBFSH peripheral type */
#define USBFSH_IRQS                              { USB0_IRQn }
#define USBFSH_NEEDCLK_IRQS                      { USB0_NEEDCLK_IRQn }

/* USBHSD - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral USBHSD base address */
  #define USBHSD_BASE                              (0x50094000u)
  /** Peripheral USBHSD base address */
  #define USBHSD_BASE_NS                           (0x40094000u)
  /** Peripheral USBHSD base pointer */
  #define USBHSD                                   ((USBHSD_Type *)USBHSD_BASE)
  /** Peripheral USBHSD base pointer */
  #define USBHSD_NS                                ((USBHSD_Type *)USBHSD_BASE_NS)
  /** Array initializer of USBHSD peripheral base addresses */
  #define USBHSD_BASE_ADDRS                        { USBHSD_BASE }
  /** Array initializer of USBHSD peripheral base pointers */
  #define USBHSD_BASE_PTRS                         { USBHSD }
  /** Array initializer of USBHSD peripheral base addresses */
  #define USBHSD_BASE_ADDRS_NS                     { USBHSD_BASE_NS }
  /** Array initializer of USBHSD peripheral base pointers */
  #define USBHSD_BASE_PTRS_NS                      { USBHSD_NS }
#else
  /** Peripheral USBHSD base address */
  #define USBHSD_BASE                              (0x40094000u)
  /** Peripheral USBHSD base pointer */
  #define USBHSD                                   ((USBHSD_Type *)USBHSD_BASE)
  /** Array initializer of USBHSD peripheral base addresses */
  #define USBHSD_BASE_ADDRS                        { USBHSD_BASE }
  /** Array initializer of USBHSD peripheral base pointers */
  #define USBHSD_BASE_PTRS                         { USBHSD }
#endif
/** Interrupt vectors for the USBHSD peripheral type */
#define USBHSD_IRQS                              { USB1_IRQn }
#define USBHSD_NEEDCLK_IRQS                      { USB1_NEEDCLK_IRQn }

/* USBHSH - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral USBHSH base address */
  #define USBHSH_BASE                              (0x500A3000u)
  /** Peripheral USBHSH base address */
  #define USBHSH_BASE_NS                           (0x400A3000u)
  /** Peripheral USBHSH base pointer */
  #define USBHSH                                   ((USBHSH_Type *)USBHSH_BASE)
  /** Peripheral USBHSH base pointer */
  #define USBHSH_NS                                ((USBHSH_Type *)USBHSH_BASE_NS)
  /** Array initializer of USBHSH peripheral base addresses */
  #define USBHSH_BASE_ADDRS                        { USBHSH_BASE }
  /** Array initializer of USBHSH peripheral base pointers */
  #define USBHSH_BASE_PTRS                         { USBHSH }
  /** Array initializer of USBHSH peripheral base addresses */
  #define USBHSH_BASE_ADDRS_NS                     { USBHSH_BASE_NS }
  /** Array initializer of USBHSH peripheral base pointers */
  #define USBHSH_BASE_PTRS_NS                      { USBHSH_NS }
#else
  /** Peripheral USBHSH base address */
  #define USBHSH_BASE                              (0x400A3000u)
  /** Peripheral USBHSH base pointer */
  #define USBHSH                                   ((USBHSH_Type *)USBHSH_BASE)
  /** Array initializer of USBHSH peripheral base addresses */
  #define USBHSH_BASE_ADDRS                        { USBHSH_BASE }
  /** Array initializer of USBHSH peripheral base pointers */
  #define USBHSH_BASE_PTRS                         { USBHSH }
#endif
/** Interrupt vectors for the USBHSH peripheral type */
#define USBHSH_IRQS                              { USB1_IRQn }
#define USBHSH_NEEDCLK_IRQS                      { USB1_NEEDCLK_IRQn }

/* USBPHY - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral USBPHY base address */
  #define USBPHY_BASE                              (0x50038000u)
  /** Peripheral USBPHY base address */
  #define USBPHY_BASE_NS                           (0x40038000u)
  /** Peripheral USBPHY base pointer */
  #define USBPHY                                   ((USBPHY_Type *)USBPHY_BASE)
  /** Peripheral USBPHY base pointer */
  #define USBPHY_NS                                ((USBPHY_Type *)USBPHY_BASE_NS)
  /** Array initializer of USBPHY peripheral base addresses */
  #define USBPHY_BASE_ADDRS                        { USBPHY_BASE }
  /** Array initializer of USBPHY peripheral base pointers */
  #define USBPHY_BASE_PTRS                         { USBPHY }
  /** Array initializer of USBPHY peripheral base addresses */
  #define USBPHY_BASE_ADDRS_NS                     { USBPHY_BASE_NS }
  /** Array initializer of USBPHY peripheral base pointers */
  #define USBPHY_BASE_PTRS_NS                      { USBPHY_NS }
#else
  /** Peripheral USBPHY base address */
  #define USBPHY_BASE                              (0x40038000u)
  /** Peripheral USBPHY base pointer */
  #define USBPHY                                   ((USBPHY_Type *)USBPHY_BASE)
  /** Array initializer of USBPHY peripheral base addresses */
  #define USBPHY_BASE_ADDRS                        { USBPHY_BASE }
  /** Array initializer of USBPHY peripheral base pointers */
  #define USBPHY_BASE_PTRS                         { USBPHY }
#endif
/** Interrupt vectors for the USBPHY peripheral type */
#define USBPHY_IRQS                              { USB1_PHY_IRQn }

/* UTICK - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral UTICK0 base address */
  #define UTICK0_BASE                              (0x5000E000u)
  /** Peripheral UTICK0 base address */
  #define UTICK0_BASE_NS                           (0x4000E000u)
  /** Peripheral UTICK0 base pointer */
  #define UTICK0                                   ((UTICK_Type *)UTICK0_BASE)
  /** Peripheral UTICK0 base pointer */
  #define UTICK0_NS                                ((UTICK_Type *)UTICK0_BASE_NS)
  /** Array initializer of UTICK peripheral base addresses */
  #define UTICK_BASE_ADDRS                         { UTICK0_BASE }
  /** Array initializer of UTICK peripheral base pointers */
  #define UTICK_BASE_PTRS                          { UTICK0 }
  /** Array initializer of UTICK peripheral base addresses */
  #define UTICK_BASE_ADDRS_NS                      { UTICK0_BASE_NS }
  /** Array initializer of UTICK peripheral base pointers */
  #define UTICK_BASE_PTRS_NS                       { UTICK0_NS }
#else
  /** Peripheral UTICK0 base address */
  #define UTICK0_BASE                              (0x4000E000u)
  /** Peripheral UTICK0 base pointer */
  #define UTICK0                                   ((UTICK_Type *)UTICK0_BASE)
  /** Array initializer of UTICK peripheral base addresses */
  #define UTICK_BASE_ADDRS                         { UTICK0_BASE }
  /** Array initializer of UTICK peripheral base pointers */
  #define UTICK_BASE_PTRS                          { UTICK0 }
#endif
/** Interrupt vectors for the UTICK peripheral type */
#define UTICK_IRQS                               { UTICK0_IRQn }

/* WWDT - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral WWDT base address */
  #define WWDT_BASE                                (0x5000C000u)
  /** Peripheral WWDT base address */
  #define WWDT_BASE_NS                             (0x4000C000u)
  /** Peripheral WWDT base pointer */
  #define WWDT                                     ((WWDT_Type *)WWDT_BASE)
  /** Peripheral WWDT base pointer */
  #define WWDT_NS                                  ((WWDT_Type *)WWDT_BASE_NS)
  /** Array initializer of WWDT peripheral base addresses */
  #define WWDT_BASE_ADDRS                          { WWDT_BASE }
  /** Array initializer of WWDT peripheral base pointers */
  #define WWDT_BASE_PTRS                           { WWDT }
  /** Array initializer of WWDT peripheral base addresses */
  #define WWDT_BASE_ADDRS_NS                       { WWDT_BASE_NS }
  /** Array initializer of WWDT peripheral base pointers */
  #define WWDT_BASE_PTRS_NS                        { WWDT_NS }
#else
  /** Peripheral WWDT base address */
  #define WWDT_BASE                                (0x4000C000u)
  /** Peripheral WWDT base pointer */
  #define WWDT                                     ((WWDT_Type *)WWDT_BASE)
  /** Array initializer of WWDT peripheral base addresses */
  #define WWDT_BASE_ADDRS                          { WWDT_BASE }
  /** Array initializer of WWDT peripheral base pointers */
  #define WWDT_BASE_PTRS                           { WWDT }
#endif
/** Interrupt vectors for the WWDT peripheral type */
#define WWDT_IRQS                                { WDT_BOD_IRQn }

/* ----------------------------------------------------------------------------
   -- Macros for use with bit field definitions (xxx_SHIFT, xxx_MASK).
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Bit_Field_Generic_Macros Macros for use with bit field definitions (xxx_SHIFT, xxx_MASK).
 * @{
 */

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang system_header
  #endif
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma system_include
#endif

/**
 * @brief Mask and left-shift a bit field value for use in a register bit range.
 * @param field Name of the register bit field.
 * @param value Value of the bit field.
 * @return Masked and shifted value.
 */
#define NXP_VAL2FLD(field, value)    (((value) << (field ## _SHIFT)) & (field ## _MASK))
/**
 * @brief Mask and right-shift a register value to extract a bit field value.
 * @param field Name of the register bit field.
 * @param value Value of the register.
 * @return Masked and shifted bit field value.
 */
#define NXP_FLD2VAL(field, value)    (((value) & (field ## _MASK)) >> (field ## _SHIFT))

/*!
 * @}
 */ /* end of group Bit_Field_Generic_Macros */


/* ----------------------------------------------------------------------------
   -- SDK Compatibility
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SDK_Compatibility_Symbols SDK Compatibility
 * @{
 */

/** High Speed SPI (Flexcomm 8) interrupt name */
#define LSPI_HS_IRQn                                FLEXCOMM8_IRQn


/*!
 * @}
 */ /* end of group SDK_Compatibility_Symbols */


#endif  /* LPC55S16_COMMON_H_ */


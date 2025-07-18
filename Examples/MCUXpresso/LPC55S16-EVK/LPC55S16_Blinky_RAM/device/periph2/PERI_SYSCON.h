/*
** ###################################################################
**     Processors:          LPC5512JBD100
**                          LPC5512JBD64
**                          LPC5514JBD100
**                          LPC5514JBD64
**                          LPC5514JEV59
**                          LPC5516JBD100
**                          LPC5516JBD64
**                          LPC5516JEV59
**                          LPC5516JEV98
**                          LPC55S14JBD100
**                          LPC55S14JBD64
**                          LPC55S14JEV59
**                          LPC55S16JBD100
**                          LPC55S16JBD64
**                          LPC55S16JEV59
**                          LPC55S16JEV98
**
**     Version:             rev. 1.1, 2019-12-03
**     Build:               b240704
**
**     Abstract:
**         CMSIS Peripheral Access Layer for SYSCON
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
 * @file SYSCON.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for SYSCON
 *
 * CMSIS Peripheral Access Layer for SYSCON
 */

#if !defined(SYSCON_H_)
#define SYSCON_H_                                /**< Symbol preventing repeated inclusion */

#if (defined(CPU_LPC5512JBD100) || defined(CPU_LPC5512JBD64))
#include "LPC5512_COMMON.h"
#elif (defined(CPU_LPC5514JBD100) || defined(CPU_LPC5514JBD64) || defined(CPU_LPC5514JEV59))
#include "LPC5514_COMMON.h"
#elif (defined(CPU_LPC5516JBD100) || defined(CPU_LPC5516JBD64) || defined(CPU_LPC5516JEV59) || defined(CPU_LPC5516JEV98))
#include "LPC5516_COMMON.h"
#elif (defined(CPU_LPC55S14JBD100) || defined(CPU_LPC55S14JBD64) || defined(CPU_LPC55S14JEV59))
#include "LPC55S14_COMMON.h"
#elif (defined(CPU_LPC55S16JBD100) || defined(CPU_LPC55S16JBD64) || defined(CPU_LPC55S16JEV59) || defined(CPU_LPC55S16JEV98))
#include "LPC55S16_COMMON.h"
#else
  #error "No valid CPU defined!"
#endif

/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
  #else
    #pragma push
    #pragma anon_unions
  #endif
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- SYSCON Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYSCON_Peripheral_Access_Layer SYSCON Peripheral Access Layer
 * @{
 */

/** SYSCON - Size of Registers Arrays */
#define SYSCON_PRESETCTRL_PRESETCTRLX_PRESETCTRLX_COUNT 3u
#define SYSCON_PRESETCTRLSET_COUNT                3u
#define SYSCON_PRESETCTRLCLR_COUNT                3u
#define SYSCON_AHBCLKCTRL_AHBCLKCTRLX_AHBCLKCTRLX_COUNT 3u
#define SYSCON_AHBCLKCTRLSET_COUNT                3u
#define SYSCON_AHBCLKCTRLCLR_COUNT                3u
#define SYSCON_SYSTICKCLKSEL_SYSTICKCLKSELX_SYSTICKCLKSELX_COUNT 1u
#define SYSCON_CTIMERCLKSEL_CTIMERCLKSELX_CTIMERCLKSELX_COUNT 5u
#define SYSCON_FCCLKSEL_FCCLKSELX_FCCLKSELX_COUNT 8u
#define SYSCON_FLEXFRGCTRL_FLEXFRGXCTRL_FLEXFRGXCTRL_COUNT 8u

/** SYSCON - Register Layout Typedef */
typedef struct {
  __IO uint32_t MEMORYREMAP;                       /**< Memory Remap control register, offset: 0x0 */
       uint8_t RESERVED_0[12];
  __IO uint32_t AHBMATPRIO;                        /**< AHB Matrix priority control register Priority values are 3 = highest, 0 = lowest, offset: 0x10 */
       uint8_t RESERVED_1[36];
  __IO uint32_t CPU0STCKCAL;                       /**< System tick calibration for secure part of CPU0, offset: 0x38 */
  __IO uint32_t CPU0NSTCKCAL;                      /**< System tick calibration for non-secure part of CPU0, offset: 0x3C */
       uint8_t RESERVED_2[8];
  __IO uint32_t NMISRC;                            /**< NMI Source Select, offset: 0x48 */
       uint8_t RESERVED_3[180];
  union {                                          /* offset: 0x100 */
    struct {                                         /* offset: 0x100 */
      __IO uint32_t PRESETCTRL0;                       /**< Peripheral reset control 0, offset: 0x100 */
      __IO uint32_t PRESETCTRL1;                       /**< Peripheral reset control 1, offset: 0x104 */
      __IO uint32_t PRESETCTRL2;                       /**< Peripheral reset control 2, offset: 0x108 */
    } PRESETCTRL;
    __IO uint32_t PRESETCTRLX[SYSCON_PRESETCTRL_PRESETCTRLX_PRESETCTRLX_COUNT];   /**< Peripheral reset control register, array offset: 0x100, array step: 0x4 */
  };
       uint8_t RESERVED_4[20];
  __IO uint32_t PRESETCTRLSET[SYSCON_PRESETCTRLSET_COUNT]; /**< Peripheral reset control set register, array offset: 0x120, array step: 0x4 */
       uint8_t RESERVED_5[20];
  __IO uint32_t PRESETCTRLCLR[SYSCON_PRESETCTRLCLR_COUNT]; /**< Peripheral reset control clear register, array offset: 0x140, array step: 0x4 */
       uint8_t RESERVED_6[20];
  __O  uint32_t SWR_RESET;                         /**< generate a software_reset, offset: 0x160 */
       uint8_t RESERVED_7[156];
  union {                                          /* offset: 0x200 */
    struct {                                         /* offset: 0x200 */
      __IO uint32_t AHBCLKCTRL0;                       /**< AHB Clock control 0, offset: 0x200 */
      __IO uint32_t AHBCLKCTRL1;                       /**< AHB Clock control 1, offset: 0x204 */
      __IO uint32_t AHBCLKCTRL2;                       /**< AHB Clock control 2, offset: 0x208 */
    } AHBCLKCTRL;
    __IO uint32_t AHBCLKCTRLX[SYSCON_AHBCLKCTRL_AHBCLKCTRLX_AHBCLKCTRLX_COUNT];   /**< Peripheral reset control register, array offset: 0x200, array step: 0x4 */
  };
       uint8_t RESERVED_8[20];
  __IO uint32_t AHBCLKCTRLSET[SYSCON_AHBCLKCTRLSET_COUNT]; /**< Peripheral reset control register, array offset: 0x220, array step: 0x4 */
       uint8_t RESERVED_9[20];
  __IO uint32_t AHBCLKCTRLCLR[SYSCON_AHBCLKCTRLCLR_COUNT]; /**< Peripheral reset control register, array offset: 0x240, array step: 0x4 */
       uint8_t RESERVED_10[20];
  union {                                          /* offset: 0x260 */
    __IO uint32_t SYSTICKCLKSEL0;                    /**< System Tick Timer for CPU0 source select, offset: 0x260 */
    __IO uint32_t SYSTICKCLKSELX[SYSCON_SYSTICKCLKSEL_SYSTICKCLKSELX_SYSTICKCLKSELX_COUNT];   /**< Peripheral reset control register, array offset: 0x260, array step: 0x4 */
  };
       uint8_t RESERVED_11[4];
  __IO uint32_t TRACECLKSEL;                       /**< Trace clock source select, offset: 0x268 */
  union {                                          /* offset: 0x26C */
    struct {                                         /* offset: 0x26C */
      __IO uint32_t CTIMERCLKSEL0;                     /**< CTimer 0 clock source select, offset: 0x26C */
      __IO uint32_t CTIMERCLKSEL1;                     /**< CTimer 1 clock source select, offset: 0x270 */
      __IO uint32_t CTIMERCLKSEL2;                     /**< CTimer 2 clock source select, offset: 0x274 */
      __IO uint32_t CTIMERCLKSEL3;                     /**< CTimer 3 clock source select, offset: 0x278 */
      __IO uint32_t CTIMERCLKSEL4;                     /**< CTimer 4 clock source select, offset: 0x27C */
    } CTIMERCLKSEL;
    __IO uint32_t CTIMERCLKSELX[SYSCON_CTIMERCLKSEL_CTIMERCLKSELX_CTIMERCLKSELX_COUNT];   /**< Peripheral reset control register, array offset: 0x26C, array step: 0x4 */
  };
  __IO uint32_t MAINCLKSELA;                       /**< Main clock A source select, offset: 0x280 */
  __IO uint32_t MAINCLKSELB;                       /**< Main clock source select, offset: 0x284 */
  __IO uint32_t CLKOUTSEL;                         /**< CLKOUT clock source select, offset: 0x288 */
       uint8_t RESERVED_12[4];
  __IO uint32_t PLL0CLKSEL;                        /**< PLL0 clock source select, offset: 0x290 */
  __IO uint32_t PLL1CLKSEL;                        /**< PLL1 clock source select, offset: 0x294 */
       uint8_t RESERVED_13[8];
  __IO uint32_t CANCLKSEL;                         /**< CAN clock source select, offset: 0x2A0 */
  __IO uint32_t ADCCLKSEL;                         /**< ADC clock source select, offset: 0x2A4 */
  __IO uint32_t USB0CLKSEL;                        /**< FS USB clock source select, offset: 0x2A8 */
  __IO uint32_t CLK32KCLKSEL;                      /**< clock low speed source select for HS USB., offset: 0x2AC */
  union {                                          /* offset: 0x2B0 */
    struct {                                         /* offset: 0x2B0 */
      __IO uint32_t FCCLKSEL0;                         /**< Flexcomm Interface 0 clock source select for Fractional Rate Divider, offset: 0x2B0 */
      __IO uint32_t FCCLKSEL1;                         /**< Flexcomm Interface 1 clock source select for Fractional Rate Divider, offset: 0x2B4 */
      __IO uint32_t FCCLKSEL2;                         /**< Flexcomm Interface 2 clock source select for Fractional Rate Divider, offset: 0x2B8 */
      __IO uint32_t FCCLKSEL3;                         /**< Flexcomm Interface 3 clock source select for Fractional Rate Divider, offset: 0x2BC */
      __IO uint32_t FCCLKSEL4;                         /**< Flexcomm Interface 4 clock source select for Fractional Rate Divider, offset: 0x2C0 */
      __IO uint32_t FCCLKSEL5;                         /**< Flexcomm Interface 5 clock source select for Fractional Rate Divider, offset: 0x2C4 */
      __IO uint32_t FCCLKSEL6;                         /**< Flexcomm Interface 6 clock source select for Fractional Rate Divider, offset: 0x2C8 */
      __IO uint32_t FCCLKSEL7;                         /**< Flexcomm Interface 7 clock source select for Fractional Rate Divider, offset: 0x2CC */
    } FCCLKSEL;
    __IO uint32_t FCCLKSELX[SYSCON_FCCLKSEL_FCCLKSELX_FCCLKSELX_COUNT];   /**< Peripheral reset control register, array offset: 0x2B0, array step: 0x4 */
  };
  __IO uint32_t HSLSPICLKSEL;                      /**< HS LSPI clock source select, offset: 0x2D0 */
       uint8_t RESERVED_14[12];
  __IO uint32_t MCLKCLKSEL;                        /**< MCLK clock source select, offset: 0x2E0 */
       uint8_t RESERVED_15[12];
  __IO uint32_t SCTCLKSEL;                         /**< SCTimer/PWM clock source select, offset: 0x2F0 */
       uint8_t RESERVED_16[12];
  __IO uint32_t SYSTICKCLKDIV0;                    /**< System Tick Timer divider for CPU0, offset: 0x300 */
       uint8_t RESERVED_17[4];
  __IO uint32_t TRACECLKDIV;                       /**< TRACE clock divider, offset: 0x308 */
  __IO uint32_t CANCLKDIV;                         /**< CAN clock divider, offset: 0x30C */
       uint8_t RESERVED_18[16];
  union {                                          /* offset: 0x320 */
    struct {                                         /* offset: 0x320 */
      __IO uint32_t FLEXFRG0CTRL;                      /**< Fractional rate divider for flexcomm 0, offset: 0x320 */
      __IO uint32_t FLEXFRG1CTRL;                      /**< Fractional rate divider for flexcomm 1, offset: 0x324 */
      __IO uint32_t FLEXFRG2CTRL;                      /**< Fractional rate divider for flexcomm 2, offset: 0x328 */
      __IO uint32_t FLEXFRG3CTRL;                      /**< Fractional rate divider for flexcomm 3, offset: 0x32C */
      __IO uint32_t FLEXFRG4CTRL;                      /**< Fractional rate divider for flexcomm 4, offset: 0x330 */
      __IO uint32_t FLEXFRG5CTRL;                      /**< Fractional rate divider for flexcomm 5, offset: 0x334 */
      __IO uint32_t FLEXFRG6CTRL;                      /**< Fractional rate divider for flexcomm 6, offset: 0x338 */
      __IO uint32_t FLEXFRG7CTRL;                      /**< Fractional rate divider for flexcomm 7, offset: 0x33C */
    } FLEXFRGCTRL;
    __IO uint32_t FLEXFRGXCTRL[SYSCON_FLEXFRGCTRL_FLEXFRGXCTRL_FLEXFRGXCTRL_COUNT];   /**< Peripheral reset control register, array offset: 0x320, array step: 0x4 */
  };
       uint8_t RESERVED_19[64];
  __IO uint32_t AHBCLKDIV;                         /**< System clock divider, offset: 0x380 */
  __IO uint32_t CLKOUTDIV;                         /**< CLKOUT clock divider, offset: 0x384 */
  __IO uint32_t FROHFDIV;                          /**< FRO_HF (96MHz) clock divider, offset: 0x388 */
  __IO uint32_t WDTCLKDIV;                         /**< WDT clock divider, offset: 0x38C */
       uint8_t RESERVED_20[4];
  __IO uint32_t ADCCLKDIV;                         /**< ADC clock divider, offset: 0x394 */
  __IO uint32_t USB0CLKDIV;                        /**< USB0-FS Clock divider, offset: 0x398 */
       uint8_t RESERVED_21[4];
  __IO uint32_t FRO1MCLKDIV;                       /**< FRO1MHz Clock divider (FRO1M_divided), offset: 0x3A0 */
       uint8_t RESERVED_22[8];
  __IO uint32_t MCLKDIV;                           /**< I2S MCLK clock divider, offset: 0x3AC */
       uint8_t RESERVED_23[4];
  __IO uint32_t SCTCLKDIV;                         /**< SCT/PWM clock divider, offset: 0x3B4 */
       uint8_t RESERVED_24[12];
  __IO uint32_t PLL0CLKDIV;                        /**< PLL0 clock divider, offset: 0x3C4 */
       uint8_t RESERVED_25[52];
  __IO uint32_t CLOCKGENUPDATELOCKOUT;             /**< Control clock configuration registers access (like xxxDIV, xxxSEL), offset: 0x3FC */
  __IO uint32_t FMCCR;                             /**< FMC configuration register, offset: 0x400 */
       uint8_t RESERVED_26[8];
  __IO uint32_t USB0NEEDCLKCTRL;                   /**< USB0-FS need clock control, offset: 0x40C */
  __I  uint32_t USB0NEEDCLKSTAT;                   /**< USB0-FS need clock status, offset: 0x410 */
       uint8_t RESERVED_27[8];
  __O  uint32_t FMCFLUSH;                          /**< FMCflush control, offset: 0x41C */
  __IO uint32_t MCLKIO;                            /**< MCLK control, offset: 0x420 */
  __IO uint32_t USB1NEEDCLKCTRL;                   /**< USB1-HS need clock control, offset: 0x424 */
  __I  uint32_t USB1NEEDCLKSTAT;                   /**< USB1-HS need clock status, offset: 0x428 */
       uint8_t RESERVED_28[20];
  __IO uint32_t FLASHREMAP_SIZE;                   /**< This 32-bit register contains the size of the image to remap, in bytes. The 12 LSBs are ignored, so the size granularity is 4KB., offset: 0x440 */
  __IO uint32_t FLASHREMAP_SIZE_DP;                /**< This 32-bit register is a duplicate of FLASHREMAPSIZE for increased security., offset: 0x444 */
  __IO uint32_t FLASHREMAP_OFFSET;                 /**< This 32-bit register contains the offset by which the image is to be remapped. The 12 LSBs are ignored, so the remap granularity is 4KB., offset: 0x448 */
  __IO uint32_t FLASHREMAP_OFFSET_DP;              /**< This 32-bit register is a duplicate of FLASHREMAPOFFSET for increased security., offset: 0x44C */
       uint8_t RESERVED_29[12];
  __IO uint32_t FLASHREMAP_LOCK;                   /**< Control write access to FLASHREMAP_SIZE and FLASHREMAP_OFFSET registers., offset: 0x45C */
       uint8_t RESERVED_30[16];
  __IO uint32_t CASPER_CTRL;                       /**< Control CASPER integration., offset: 0x470 */
       uint8_t RESERVED_31[236];
  __IO uint32_t PLL1CTRL;                          /**< PLL1 550m control, offset: 0x560 */
  __I  uint32_t PLL1STAT;                          /**< PLL1 550m status, offset: 0x564 */
  __IO uint32_t PLL1NDEC;                          /**< PLL1 550m N divider, offset: 0x568 */
  __IO uint32_t PLL1MDEC;                          /**< PLL1 550m M divider, offset: 0x56C */
  __IO uint32_t PLL1PDEC;                          /**< PLL1 550m P divider, offset: 0x570 */
       uint8_t RESERVED_32[12];
  __IO uint32_t PLL0CTRL;                          /**< PLL0 550m control, offset: 0x580 */
  __I  uint32_t PLL0STAT;                          /**< PLL0 550m status, offset: 0x584 */
  __IO uint32_t PLL0NDEC;                          /**< PLL0 550m N divider, offset: 0x588 */
  __IO uint32_t PLL0PDEC;                          /**< PLL0 550m P divider, offset: 0x58C */
  __IO uint32_t PLL0SSCG0;                         /**< PLL0 Spread Spectrum Wrapper control register 0, offset: 0x590 */
  __IO uint32_t PLL0SSCG1;                         /**< PLL0 Spread Spectrum Wrapper control register 1, offset: 0x594 */
       uint8_t RESERVED_33[364];
  __IO uint32_t FUNCRETENTIONCTRL;                 /**< Functional retention control register, offset: 0x704 */
       uint8_t RESERVED_34[260];
  __I  uint32_t CPSTAT;                            /**< CPU Status, offset: 0x80C */
       uint8_t RESERVED_35[272];
  __IO uint32_t BOOT_SEED_REG0;                    /**< boot seed (256-bit random value), offset: 0x920 */
  __IO uint32_t BOOT_SEED_REG1;                    /**< boot seed (256-bit random value), offset: 0x924 */
  __IO uint32_t BOOT_SEED_REG2;                    /**< boot seed (256-bit random value), offset: 0x928 */
  __IO uint32_t BOOT_SEED_REG3;                    /**< boot seed (256-bit random value), offset: 0x92C */
  __IO uint32_t BOOT_SEED_REG4;                    /**< boot seed (256-bit random value), offset: 0x930 */
  __IO uint32_t BOOT_SEED_REG5;                    /**< boot seed (256-bit random value), offset: 0x934 */
  __IO uint32_t BOOT_SEED_REG6;                    /**< boot seed (256-bit random value), offset: 0x938 */
  __IO uint32_t BOOT_SEED_REG7;                    /**< boot seed (256-bit random value), offset: 0x93C */
  __IO uint32_t HMAC_REG0;                         /**< HMAC, offset: 0x940 */
  __IO uint32_t HMAC_REG1;                         /**< HMAC, offset: 0x944 */
  __IO uint32_t HMAC_REG2;                         /**< HMAC, offset: 0x948 */
  __IO uint32_t HMAC_REG3;                         /**< HMAC, offset: 0x94C */
  __IO uint32_t HMAC_REG4;                         /**< HMAC, offset: 0x950 */
  __IO uint32_t HMAC_REG5;                         /**< HMAC, offset: 0x954 */
  __IO uint32_t HMAC_REG6;                         /**< HMAC, offset: 0x958 */
  __IO uint32_t HMAC_REG7;                         /**< HMAC, offset: 0x95C */
  __IO uint32_t BOOT_LOCK;                         /**< Control write access to boot seed security registers., offset: 0x960 */
       uint8_t RESERVED_36[180];
  __IO uint32_t CLOCK_CTRL;                        /**< Various system clock controls : Flash clock (48 MHz) control, clocks to Frequency Measures, offset: 0xA18 */
       uint8_t RESERVED_37[244];
  __IO uint32_t COMP_INT_CTRL;                     /**< Comparator Interrupt control, offset: 0xB10 */
  __I  uint32_t COMP_INT_STATUS;                   /**< Comparator Interrupt status, offset: 0xB14 */
       uint8_t RESERVED_38[748];
  __IO uint32_t AUTOCLKGATEOVERRIDE;               /**< Control automatic clock gating, offset: 0xE04 */
  __IO uint32_t GPIOPSYNC;                         /**< Enable bypass of the first stage of synchonization inside GPIO_INT module, offset: 0xE08 */
       uint8_t RESERVED_39[380];
  __IO uint32_t HASHRESTHWKEY;                     /**< Controls whether the HASH AES hardware secret key is restricted to use by secure code, offset: 0xF88 */
       uint8_t RESERVED_40[20];
  __IO uint32_t DEBUG_LOCK_EN;                     /**< Control write access to security registers., offset: 0xFA0 */
  __IO uint32_t DEBUG_FEATURES;                    /**< Cortex debug features control., offset: 0xFA4 */
  __IO uint32_t DEBUG_FEATURES_DP;                 /**< Cortex debug features control. (duplicate), offset: 0xFA8 */
       uint8_t RESERVED_41[8];
  __IO uint32_t SWD_ACCESS_CPU0;                   /**< This register is used by ROM during DEBUG authentication mechanism to enable debug access port for CPU0., offset: 0xFB4 */
       uint8_t RESERVED_42[4];
  __O  uint32_t KEY_BLOCK;                         /**< block quiddikey/PUF all index., offset: 0xFBC */
  __IO uint32_t DEBUG_AUTH_BEACON;                 /**< Debug authentication BEACON register, offset: 0xFC0 */
       uint8_t RESERVED_43[52];
  __I  uint32_t DEVICE_ID0;                        /**< Device ID, offset: 0xFF8 */
  __I  uint32_t DIEID;                             /**< Chip revision ID and Number, offset: 0xFFC */
} SYSCON_Type;

/* ----------------------------------------------------------------------------
   -- SYSCON Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYSCON_Register_Masks SYSCON Register Masks
 * @{
 */

/*! @name MEMORYREMAP - Memory Remap control register */
/*! @{ */

#define SYSCON_MEMORYREMAP_MAP_MASK              (0x3U)
#define SYSCON_MEMORYREMAP_MAP_SHIFT             (0U)
/*! MAP - Select the location of the vector table :.
 *  0b00..Vector Table in ROM.
 *  0b01..Vector Table in RAM.
 *  0b10..Vector Table in Flash.
 *  0b11..Vector Table in Flash.
 */
#define SYSCON_MEMORYREMAP_MAP(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_MEMORYREMAP_MAP_SHIFT)) & SYSCON_MEMORYREMAP_MAP_MASK)
/*! @} */

/*! @name AHBMATPRIO - AHB Matrix priority control register Priority values are 3 = highest, 0 = lowest */
/*! @{ */

#define SYSCON_AHBMATPRIO_PRI_CPU0_CBUS_MASK     (0x3U)
#define SYSCON_AHBMATPRIO_PRI_CPU0_CBUS_SHIFT    (0U)
/*! PRI_CPU0_CBUS - CPU0 C-AHB bus. */
#define SYSCON_AHBMATPRIO_PRI_CPU0_CBUS(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_CPU0_CBUS_SHIFT)) & SYSCON_AHBMATPRIO_PRI_CPU0_CBUS_MASK)

#define SYSCON_AHBMATPRIO_PRI_CPU0_SBUS_MASK     (0xCU)
#define SYSCON_AHBMATPRIO_PRI_CPU0_SBUS_SHIFT    (2U)
/*! PRI_CPU0_SBUS - CPU0 S-AHB bus. */
#define SYSCON_AHBMATPRIO_PRI_CPU0_SBUS(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_CPU0_SBUS_SHIFT)) & SYSCON_AHBMATPRIO_PRI_CPU0_SBUS_MASK)

#define SYSCON_AHBMATPRIO_PRI_SDMA0_MASK         (0x30U)
#define SYSCON_AHBMATPRIO_PRI_SDMA0_SHIFT        (4U)
/*! PRI_SDMA0 - DMA0 controller priority. */
#define SYSCON_AHBMATPRIO_PRI_SDMA0(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_SDMA0_SHIFT)) & SYSCON_AHBMATPRIO_PRI_SDMA0_MASK)

#define SYSCON_AHBMATPRIO_PRI_SDMA1_MASK         (0xC0U)
#define SYSCON_AHBMATPRIO_PRI_SDMA1_SHIFT        (6U)
/*! PRI_SDMA1 - DMA1 controller priority. */
#define SYSCON_AHBMATPRIO_PRI_SDMA1(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_SDMA1_SHIFT)) & SYSCON_AHBMATPRIO_PRI_SDMA1_MASK)

#define SYSCON_AHBMATPRIO_PRI_USB_FSD_MASK       (0x300U)
#define SYSCON_AHBMATPRIO_PRI_USB_FSD_SHIFT      (8U)
/*! PRI_USB_FSD - USB0-FS Device.(USB0) */
#define SYSCON_AHBMATPRIO_PRI_USB_FSD(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_USB_FSD_SHIFT)) & SYSCON_AHBMATPRIO_PRI_USB_FSD_MASK)

#define SYSCON_AHBMATPRIO_PRI_USB_FSH_MASK       (0xC00U)
#define SYSCON_AHBMATPRIO_PRI_USB_FSH_SHIFT      (10U)
/*! PRI_USB_FSH - USB0-FS host.(USB0) */
#define SYSCON_AHBMATPRIO_PRI_USB_FSH(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_USB_FSH_SHIFT)) & SYSCON_AHBMATPRIO_PRI_USB_FSH_MASK)

#define SYSCON_AHBMATPRIO_PRI_HASH_AES_MASK      (0x30000U)
#define SYSCON_AHBMATPRIO_PRI_HASH_AES_SHIFT     (16U)
/*! PRI_HASH_AES - HASH_AES. */
#define SYSCON_AHBMATPRIO_PRI_HASH_AES(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_HASH_AES_SHIFT)) & SYSCON_AHBMATPRIO_PRI_HASH_AES_MASK)

#define SYSCON_AHBMATPRIO_PRI_CANFD_MASK         (0xC0000U)
#define SYSCON_AHBMATPRIO_PRI_CANFD_SHIFT        (18U)
/*! PRI_CANFD - CANFD. */
#define SYSCON_AHBMATPRIO_PRI_CANFD(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_CANFD_SHIFT)) & SYSCON_AHBMATPRIO_PRI_CANFD_MASK)
/*! @} */

/*! @name CPU0STCKCAL - System tick calibration for secure part of CPU0 */
/*! @{ */

#define SYSCON_CPU0STCKCAL_TENMS_MASK            (0xFFFFFFU)
#define SYSCON_CPU0STCKCAL_TENMS_SHIFT           (0U)
/*! TENMS - Reload value for 10ms (100Hz) timing, subject to system clock skew errors. If the value
 *    reads as zero, the calibration value is not known.
 */
#define SYSCON_CPU0STCKCAL_TENMS(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_CPU0STCKCAL_TENMS_SHIFT)) & SYSCON_CPU0STCKCAL_TENMS_MASK)

#define SYSCON_CPU0STCKCAL_SKEW_MASK             (0x1000000U)
#define SYSCON_CPU0STCKCAL_SKEW_SHIFT            (24U)
/*! SKEW - Initial value for the Systick timer. */
#define SYSCON_CPU0STCKCAL_SKEW(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_CPU0STCKCAL_SKEW_SHIFT)) & SYSCON_CPU0STCKCAL_SKEW_MASK)

#define SYSCON_CPU0STCKCAL_NOREF_MASK            (0x2000000U)
#define SYSCON_CPU0STCKCAL_NOREF_SHIFT           (25U)
/*! NOREF - Indicates whether the device provides a reference clock to the processor: 0 = reference
 *    clock provided; 1 = no reference clock provided.
 */
#define SYSCON_CPU0STCKCAL_NOREF(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_CPU0STCKCAL_NOREF_SHIFT)) & SYSCON_CPU0STCKCAL_NOREF_MASK)
/*! @} */

/*! @name CPU0NSTCKCAL - System tick calibration for non-secure part of CPU0 */
/*! @{ */

#define SYSCON_CPU0NSTCKCAL_TENMS_MASK           (0xFFFFFFU)
#define SYSCON_CPU0NSTCKCAL_TENMS_SHIFT          (0U)
/*! TENMS - Reload value for 10 ms (100 Hz) timing, subject to system clock skew errors. If the
 *    value reads as zero, the calibration value is not known.
 */
#define SYSCON_CPU0NSTCKCAL_TENMS(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_CPU0NSTCKCAL_TENMS_SHIFT)) & SYSCON_CPU0NSTCKCAL_TENMS_MASK)

#define SYSCON_CPU0NSTCKCAL_SKEW_MASK            (0x1000000U)
#define SYSCON_CPU0NSTCKCAL_SKEW_SHIFT           (24U)
/*! SKEW - Indicates whether the TENMS value is exact: 0 = TENMS value is exact; 1 = TENMS value is inexact, or not given. */
#define SYSCON_CPU0NSTCKCAL_SKEW(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_CPU0NSTCKCAL_SKEW_SHIFT)) & SYSCON_CPU0NSTCKCAL_SKEW_MASK)

#define SYSCON_CPU0NSTCKCAL_NOREF_MASK           (0x2000000U)
#define SYSCON_CPU0NSTCKCAL_NOREF_SHIFT          (25U)
/*! NOREF - Initial value for the Systick timer. */
#define SYSCON_CPU0NSTCKCAL_NOREF(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_CPU0NSTCKCAL_NOREF_SHIFT)) & SYSCON_CPU0NSTCKCAL_NOREF_MASK)
/*! @} */

/*! @name NMISRC - NMI Source Select */
/*! @{ */

#define SYSCON_NMISRC_IRQCPU0_MASK               (0x3FU)
#define SYSCON_NMISRC_IRQCPU0_SHIFT              (0U)
/*! IRQCPU0 - The IRQ number of the interrupt that acts as the Non-Maskable Interrupt (NMI) for the CPU0, if enabled by NMIENCPU0. */
#define SYSCON_NMISRC_IRQCPU0(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_NMISRC_IRQCPU0_SHIFT)) & SYSCON_NMISRC_IRQCPU0_MASK)

#define SYSCON_NMISRC_NMIENCPU0_MASK             (0x80000000U)
#define SYSCON_NMISRC_NMIENCPU0_SHIFT            (31U)
/*! NMIENCPU0 - Write a 1 to this bit to enable the Non-Maskable Interrupt (NMI) source selected by IRQCPU0. */
#define SYSCON_NMISRC_NMIENCPU0(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_NMISRC_NMIENCPU0_SHIFT)) & SYSCON_NMISRC_NMIENCPU0_MASK)
/*! @} */

/*! @name PRESETCTRL0 - Peripheral reset control 0 */
/*! @{ */

#define SYSCON_PRESETCTRL0_ROM_RST_MASK          (0x2U)
#define SYSCON_PRESETCTRL0_ROM_RST_SHIFT         (1U)
/*! ROM_RST - ROM reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL0_ROM_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_ROM_RST_SHIFT)) & SYSCON_PRESETCTRL0_ROM_RST_MASK)

#define SYSCON_PRESETCTRL0_SRAM_CTRL1_RST_MASK   (0x8U)
#define SYSCON_PRESETCTRL0_SRAM_CTRL1_RST_SHIFT  (3U)
/*! SRAM_CTRL1_RST - SRAM Controller 1 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL0_SRAM_CTRL1_RST(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_SRAM_CTRL1_RST_SHIFT)) & SYSCON_PRESETCTRL0_SRAM_CTRL1_RST_MASK)

#define SYSCON_PRESETCTRL0_SRAM_CTRL2_RST_MASK   (0x10U)
#define SYSCON_PRESETCTRL0_SRAM_CTRL2_RST_SHIFT  (4U)
/*! SRAM_CTRL2_RST - SRAM Controller 2 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL0_SRAM_CTRL2_RST(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_SRAM_CTRL2_RST_SHIFT)) & SYSCON_PRESETCTRL0_SRAM_CTRL2_RST_MASK)

#define SYSCON_PRESETCTRL0_FLASH_RST_MASK        (0x80U)
#define SYSCON_PRESETCTRL0_FLASH_RST_SHIFT       (7U)
/*! FLASH_RST - Flash controller reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL0_FLASH_RST(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_FLASH_RST_SHIFT)) & SYSCON_PRESETCTRL0_FLASH_RST_MASK)

#define SYSCON_PRESETCTRL0_FMC_RST_MASK          (0x100U)
#define SYSCON_PRESETCTRL0_FMC_RST_SHIFT         (8U)
/*! FMC_RST - FMC controller reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL0_FMC_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_FMC_RST_SHIFT)) & SYSCON_PRESETCTRL0_FMC_RST_MASK)

#define SYSCON_PRESETCTRL0_MUX_RST_MASK          (0x800U)
#define SYSCON_PRESETCTRL0_MUX_RST_SHIFT         (11U)
/*! MUX_RST - Input Mux reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL0_MUX_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_MUX_RST_SHIFT)) & SYSCON_PRESETCTRL0_MUX_RST_MASK)

#define SYSCON_PRESETCTRL0_IOCON_RST_MASK        (0x2000U)
#define SYSCON_PRESETCTRL0_IOCON_RST_SHIFT       (13U)
/*! IOCON_RST - I/O controller reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL0_IOCON_RST(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_IOCON_RST_SHIFT)) & SYSCON_PRESETCTRL0_IOCON_RST_MASK)

#define SYSCON_PRESETCTRL0_GPIO0_RST_MASK        (0x4000U)
#define SYSCON_PRESETCTRL0_GPIO0_RST_SHIFT       (14U)
/*! GPIO0_RST - GPIO0 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL0_GPIO0_RST(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_GPIO0_RST_SHIFT)) & SYSCON_PRESETCTRL0_GPIO0_RST_MASK)

#define SYSCON_PRESETCTRL0_GPIO1_RST_MASK        (0x8000U)
#define SYSCON_PRESETCTRL0_GPIO1_RST_SHIFT       (15U)
/*! GPIO1_RST - GPIO1 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL0_GPIO1_RST(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_GPIO1_RST_SHIFT)) & SYSCON_PRESETCTRL0_GPIO1_RST_MASK)

#define SYSCON_PRESETCTRL0_PINT_RST_MASK         (0x40000U)
#define SYSCON_PRESETCTRL0_PINT_RST_SHIFT        (18U)
/*! PINT_RST - Pin interrupt (PINT) reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL0_PINT_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_PINT_RST_SHIFT)) & SYSCON_PRESETCTRL0_PINT_RST_MASK)

#define SYSCON_PRESETCTRL0_GINT_RST_MASK         (0x80000U)
#define SYSCON_PRESETCTRL0_GINT_RST_SHIFT        (19U)
/*! GINT_RST - Group interrupt (GINT) reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL0_GINT_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_GINT_RST_SHIFT)) & SYSCON_PRESETCTRL0_GINT_RST_MASK)

#define SYSCON_PRESETCTRL0_DMA0_RST_MASK         (0x100000U)
#define SYSCON_PRESETCTRL0_DMA0_RST_SHIFT        (20U)
/*! DMA0_RST - DMA0 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL0_DMA0_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_DMA0_RST_SHIFT)) & SYSCON_PRESETCTRL0_DMA0_RST_MASK)

#define SYSCON_PRESETCTRL0_CRCGEN_RST_MASK       (0x200000U)
#define SYSCON_PRESETCTRL0_CRCGEN_RST_SHIFT      (21U)
/*! CRCGEN_RST - CRCGEN reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL0_CRCGEN_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_CRCGEN_RST_SHIFT)) & SYSCON_PRESETCTRL0_CRCGEN_RST_MASK)

#define SYSCON_PRESETCTRL0_WWDT_RST_MASK         (0x400000U)
#define SYSCON_PRESETCTRL0_WWDT_RST_SHIFT        (22U)
/*! WWDT_RST - Watchdog Timer reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL0_WWDT_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_WWDT_RST_SHIFT)) & SYSCON_PRESETCTRL0_WWDT_RST_MASK)

#define SYSCON_PRESETCTRL0_RTC_RST_MASK          (0x800000U)
#define SYSCON_PRESETCTRL0_RTC_RST_SHIFT         (23U)
/*! RTC_RST - Real Time Clock (RTC) reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL0_RTC_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_RTC_RST_SHIFT)) & SYSCON_PRESETCTRL0_RTC_RST_MASK)

#define SYSCON_PRESETCTRL0_MAILBOX_RST_MASK      (0x4000000U)
#define SYSCON_PRESETCTRL0_MAILBOX_RST_SHIFT     (26U)
/*! MAILBOX_RST - Inter CPU communication Mailbox reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL0_MAILBOX_RST(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_MAILBOX_RST_SHIFT)) & SYSCON_PRESETCTRL0_MAILBOX_RST_MASK)

#define SYSCON_PRESETCTRL0_ADC_RST_MASK          (0x8000000U)
#define SYSCON_PRESETCTRL0_ADC_RST_SHIFT         (27U)
/*! ADC_RST - ADC reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL0_ADC_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_ADC_RST_SHIFT)) & SYSCON_PRESETCTRL0_ADC_RST_MASK)
/*! @} */

/*! @name PRESETCTRL1 - Peripheral reset control 1 */
/*! @{ */

#define SYSCON_PRESETCTRL1_MRT_RST_MASK          (0x1U)
#define SYSCON_PRESETCTRL1_MRT_RST_SHIFT         (0U)
/*! MRT_RST - MRT reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL1_MRT_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_MRT_RST_SHIFT)) & SYSCON_PRESETCTRL1_MRT_RST_MASK)

#define SYSCON_PRESETCTRL1_OSTIMER_RST_MASK      (0x2U)
#define SYSCON_PRESETCTRL1_OSTIMER_RST_SHIFT     (1U)
/*! OSTIMER_RST - OS Event Timer reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL1_OSTIMER_RST(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_OSTIMER_RST_SHIFT)) & SYSCON_PRESETCTRL1_OSTIMER_RST_MASK)

#define SYSCON_PRESETCTRL1_SCT_RST_MASK          (0x4U)
#define SYSCON_PRESETCTRL1_SCT_RST_SHIFT         (2U)
/*! SCT_RST - SCT reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL1_SCT_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_SCT_RST_SHIFT)) & SYSCON_PRESETCTRL1_SCT_RST_MASK)

#define SYSCON_PRESETCTRL1_CAN_RST_MASK          (0x80U)
#define SYSCON_PRESETCTRL1_CAN_RST_SHIFT         (7U)
/*! CAN_RST - CAN reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL1_CAN_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_CAN_RST_SHIFT)) & SYSCON_PRESETCTRL1_CAN_RST_MASK)

#define SYSCON_PRESETCTRL1_UTICK_RST_MASK        (0x400U)
#define SYSCON_PRESETCTRL1_UTICK_RST_SHIFT       (10U)
/*! UTICK_RST - UTICK reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL1_UTICK_RST(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_UTICK_RST_SHIFT)) & SYSCON_PRESETCTRL1_UTICK_RST_MASK)

#define SYSCON_PRESETCTRL1_FC0_RST_MASK          (0x800U)
#define SYSCON_PRESETCTRL1_FC0_RST_SHIFT         (11U)
/*! FC0_RST - FC0 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL1_FC0_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_FC0_RST_SHIFT)) & SYSCON_PRESETCTRL1_FC0_RST_MASK)

#define SYSCON_PRESETCTRL1_FC1_RST_MASK          (0x1000U)
#define SYSCON_PRESETCTRL1_FC1_RST_SHIFT         (12U)
/*! FC1_RST - FC1 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL1_FC1_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_FC1_RST_SHIFT)) & SYSCON_PRESETCTRL1_FC1_RST_MASK)

#define SYSCON_PRESETCTRL1_FC2_RST_MASK          (0x2000U)
#define SYSCON_PRESETCTRL1_FC2_RST_SHIFT         (13U)
/*! FC2_RST - FC2 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL1_FC2_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_FC2_RST_SHIFT)) & SYSCON_PRESETCTRL1_FC2_RST_MASK)

#define SYSCON_PRESETCTRL1_FC3_RST_MASK          (0x4000U)
#define SYSCON_PRESETCTRL1_FC3_RST_SHIFT         (14U)
/*! FC3_RST - FC3 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL1_FC3_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_FC3_RST_SHIFT)) & SYSCON_PRESETCTRL1_FC3_RST_MASK)

#define SYSCON_PRESETCTRL1_FC4_RST_MASK          (0x8000U)
#define SYSCON_PRESETCTRL1_FC4_RST_SHIFT         (15U)
/*! FC4_RST - FC4 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL1_FC4_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_FC4_RST_SHIFT)) & SYSCON_PRESETCTRL1_FC4_RST_MASK)

#define SYSCON_PRESETCTRL1_FC5_RST_MASK          (0x10000U)
#define SYSCON_PRESETCTRL1_FC5_RST_SHIFT         (16U)
/*! FC5_RST - FC5 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL1_FC5_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_FC5_RST_SHIFT)) & SYSCON_PRESETCTRL1_FC5_RST_MASK)

#define SYSCON_PRESETCTRL1_FC6_RST_MASK          (0x20000U)
#define SYSCON_PRESETCTRL1_FC6_RST_SHIFT         (17U)
/*! FC6_RST - FC6 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL1_FC6_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_FC6_RST_SHIFT)) & SYSCON_PRESETCTRL1_FC6_RST_MASK)

#define SYSCON_PRESETCTRL1_FC7_RST_MASK          (0x40000U)
#define SYSCON_PRESETCTRL1_FC7_RST_SHIFT         (18U)
/*! FC7_RST - FC7 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL1_FC7_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_FC7_RST_SHIFT)) & SYSCON_PRESETCTRL1_FC7_RST_MASK)

#define SYSCON_PRESETCTRL1_TIMER2_RST_MASK       (0x400000U)
#define SYSCON_PRESETCTRL1_TIMER2_RST_SHIFT      (22U)
/*! TIMER2_RST - Timer 2 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL1_TIMER2_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_TIMER2_RST_SHIFT)) & SYSCON_PRESETCTRL1_TIMER2_RST_MASK)

#define SYSCON_PRESETCTRL1_USB0_DEV_RST_MASK     (0x2000000U)
#define SYSCON_PRESETCTRL1_USB0_DEV_RST_SHIFT    (25U)
/*! USB0_DEV_RST - USB0-FS DEV reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL1_USB0_DEV_RST(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_USB0_DEV_RST_SHIFT)) & SYSCON_PRESETCTRL1_USB0_DEV_RST_MASK)

#define SYSCON_PRESETCTRL1_TIMER0_RST_MASK       (0x4000000U)
#define SYSCON_PRESETCTRL1_TIMER0_RST_SHIFT      (26U)
/*! TIMER0_RST - Timer 0 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL1_TIMER0_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_TIMER0_RST_SHIFT)) & SYSCON_PRESETCTRL1_TIMER0_RST_MASK)

#define SYSCON_PRESETCTRL1_TIMER1_RST_MASK       (0x8000000U)
#define SYSCON_PRESETCTRL1_TIMER1_RST_SHIFT      (27U)
/*! TIMER1_RST - Timer 1 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL1_TIMER1_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_TIMER1_RST_SHIFT)) & SYSCON_PRESETCTRL1_TIMER1_RST_MASK)
/*! @} */

/*! @name PRESETCTRL2 - Peripheral reset control 2 */
/*! @{ */

#define SYSCON_PRESETCTRL2_DMA1_RST_MASK         (0x2U)
#define SYSCON_PRESETCTRL2_DMA1_RST_SHIFT        (1U)
/*! DMA1_RST - DMA1 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_DMA1_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_DMA1_RST_SHIFT)) & SYSCON_PRESETCTRL2_DMA1_RST_MASK)

#define SYSCON_PRESETCTRL2_COMP_RST_MASK         (0x4U)
#define SYSCON_PRESETCTRL2_COMP_RST_SHIFT        (2U)
/*! COMP_RST - Comparator reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_COMP_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_COMP_RST_SHIFT)) & SYSCON_PRESETCTRL2_COMP_RST_MASK)

#define SYSCON_PRESETCTRL2_USB1_HOST_RST_MASK    (0x10U)
#define SYSCON_PRESETCTRL2_USB1_HOST_RST_SHIFT   (4U)
/*! USB1_HOST_RST - USB1-HS Host reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_USB1_HOST_RST(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_USB1_HOST_RST_SHIFT)) & SYSCON_PRESETCTRL2_USB1_HOST_RST_MASK)

#define SYSCON_PRESETCTRL2_USB1_DEV_RST_MASK     (0x20U)
#define SYSCON_PRESETCTRL2_USB1_DEV_RST_SHIFT    (5U)
/*! USB1_DEV_RST - USB1-HS dev reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_USB1_DEV_RST(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_USB1_DEV_RST_SHIFT)) & SYSCON_PRESETCTRL2_USB1_DEV_RST_MASK)

#define SYSCON_PRESETCTRL2_USB1_RAM_RST_MASK     (0x40U)
#define SYSCON_PRESETCTRL2_USB1_RAM_RST_SHIFT    (6U)
/*! USB1_RAM_RST - USB1-HS RAM reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_USB1_RAM_RST(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_USB1_RAM_RST_SHIFT)) & SYSCON_PRESETCTRL2_USB1_RAM_RST_MASK)

#define SYSCON_PRESETCTRL2_USB1_PHY_RST_MASK     (0x80U)
#define SYSCON_PRESETCTRL2_USB1_PHY_RST_SHIFT    (7U)
/*! USB1_PHY_RST - USB1-HS PHY reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_USB1_PHY_RST(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_USB1_PHY_RST_SHIFT)) & SYSCON_PRESETCTRL2_USB1_PHY_RST_MASK)

#define SYSCON_PRESETCTRL2_FREQME_RST_MASK       (0x100U)
#define SYSCON_PRESETCTRL2_FREQME_RST_SHIFT      (8U)
/*! FREQME_RST - Frequency meter reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_FREQME_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_FREQME_RST_SHIFT)) & SYSCON_PRESETCTRL2_FREQME_RST_MASK)

#define SYSCON_PRESETCTRL2_CDOG_RST_MASK         (0x800U)
#define SYSCON_PRESETCTRL2_CDOG_RST_SHIFT        (11U)
/*! CDOG_RST - Code Watchdog reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_CDOG_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_CDOG_RST_SHIFT)) & SYSCON_PRESETCTRL2_CDOG_RST_MASK)

#define SYSCON_PRESETCTRL2_RNG_RST_MASK          (0x2000U)
#define SYSCON_PRESETCTRL2_RNG_RST_SHIFT         (13U)
/*! RNG_RST - RNG reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_RNG_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_RNG_RST_SHIFT)) & SYSCON_PRESETCTRL2_RNG_RST_MASK)

#define SYSCON_PRESETCTRL2_SYSCTL_RST_MASK       (0x8000U)
#define SYSCON_PRESETCTRL2_SYSCTL_RST_SHIFT      (15U)
/*! SYSCTL_RST - SYSCTL Block reset.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_SYSCTL_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_SYSCTL_RST_SHIFT)) & SYSCON_PRESETCTRL2_SYSCTL_RST_MASK)

#define SYSCON_PRESETCTRL2_USB0_HOSTM_RST_MASK   (0x10000U)
#define SYSCON_PRESETCTRL2_USB0_HOSTM_RST_SHIFT  (16U)
/*! USB0_HOSTM_RST - USB0-FS Host Master reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_USB0_HOSTM_RST(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_USB0_HOSTM_RST_SHIFT)) & SYSCON_PRESETCTRL2_USB0_HOSTM_RST_MASK)

#define SYSCON_PRESETCTRL2_USB0_HOSTS_RST_MASK   (0x20000U)
#define SYSCON_PRESETCTRL2_USB0_HOSTS_RST_SHIFT  (17U)
/*! USB0_HOSTS_RST - USB0-FS Host Slave reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_USB0_HOSTS_RST(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_USB0_HOSTS_RST_SHIFT)) & SYSCON_PRESETCTRL2_USB0_HOSTS_RST_MASK)

#define SYSCON_PRESETCTRL2_HASH_AES_RST_MASK     (0x40000U)
#define SYSCON_PRESETCTRL2_HASH_AES_RST_SHIFT    (18U)
/*! HASH_AES_RST - HASH_AES reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_HASH_AES_RST(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_HASH_AES_RST_SHIFT)) & SYSCON_PRESETCTRL2_HASH_AES_RST_MASK)

#define SYSCON_PRESETCTRL2_PLULUT_RST_MASK       (0x100000U)
#define SYSCON_PRESETCTRL2_PLULUT_RST_SHIFT      (20U)
/*! PLULUT_RST - PLU LUT reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_PLULUT_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_PLULUT_RST_SHIFT)) & SYSCON_PRESETCTRL2_PLULUT_RST_MASK)

#define SYSCON_PRESETCTRL2_TIMER3_RST_MASK       (0x200000U)
#define SYSCON_PRESETCTRL2_TIMER3_RST_SHIFT      (21U)
/*! TIMER3_RST - Timer 3 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_TIMER3_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_TIMER3_RST_SHIFT)) & SYSCON_PRESETCTRL2_TIMER3_RST_MASK)

#define SYSCON_PRESETCTRL2_TIMER4_RST_MASK       (0x400000U)
#define SYSCON_PRESETCTRL2_TIMER4_RST_SHIFT      (22U)
/*! TIMER4_RST - Timer 4 reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_TIMER4_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_TIMER4_RST_SHIFT)) & SYSCON_PRESETCTRL2_TIMER4_RST_MASK)

#define SYSCON_PRESETCTRL2_PUF_RST_MASK          (0x800000U)
#define SYSCON_PRESETCTRL2_PUF_RST_SHIFT         (23U)
/*! PUF_RST - PUF reset control reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_PUF_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_PUF_RST_SHIFT)) & SYSCON_PRESETCTRL2_PUF_RST_MASK)

#define SYSCON_PRESETCTRL2_CASPER_RST_MASK       (0x1000000U)
#define SYSCON_PRESETCTRL2_CASPER_RST_SHIFT      (24U)
/*! CASPER_RST - Casper reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_CASPER_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_CASPER_RST_SHIFT)) & SYSCON_PRESETCTRL2_CASPER_RST_MASK)

#define SYSCON_PRESETCTRL2_ANALOG_CTRL_RST_MASK  (0x8000000U)
#define SYSCON_PRESETCTRL2_ANALOG_CTRL_RST_SHIFT (27U)
/*! ANALOG_CTRL_RST - analog control reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_ANALOG_CTRL_RST(x)    (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_ANALOG_CTRL_RST_SHIFT)) & SYSCON_PRESETCTRL2_ANALOG_CTRL_RST_MASK)

#define SYSCON_PRESETCTRL2_HS_LSPI_RST_MASK      (0x10000000U)
#define SYSCON_PRESETCTRL2_HS_LSPI_RST_SHIFT     (28U)
/*! HS_LSPI_RST - HS LSPI reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_HS_LSPI_RST(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_HS_LSPI_RST_SHIFT)) & SYSCON_PRESETCTRL2_HS_LSPI_RST_MASK)

#define SYSCON_PRESETCTRL2_GPIO_SEC_RST_MASK     (0x20000000U)
#define SYSCON_PRESETCTRL2_GPIO_SEC_RST_SHIFT    (29U)
/*! GPIO_SEC_RST - GPIO secure reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_GPIO_SEC_RST(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_GPIO_SEC_RST_SHIFT)) & SYSCON_PRESETCTRL2_GPIO_SEC_RST_MASK)

#define SYSCON_PRESETCTRL2_GPIO_SEC_INT_RST_MASK (0x40000000U)
#define SYSCON_PRESETCTRL2_GPIO_SEC_INT_RST_SHIFT (30U)
/*! GPIO_SEC_INT_RST - GPIO secure int reset control.
 *  0b1..Bloc is reset.
 *  0b0..Bloc is not reset.
 */
#define SYSCON_PRESETCTRL2_GPIO_SEC_INT_RST(x)   (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL2_GPIO_SEC_INT_RST_SHIFT)) & SYSCON_PRESETCTRL2_GPIO_SEC_INT_RST_MASK)
/*! @} */

/*! @name PRESETCTRLX - Peripheral reset control register */
/*! @{ */

#define SYSCON_PRESETCTRLX_DATA_MASK             (0xFFFFFFFFU)
#define SYSCON_PRESETCTRLX_DATA_SHIFT            (0U)
/*! DATA - Data array value */
#define SYSCON_PRESETCTRLX_DATA(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRLX_DATA_SHIFT)) & SYSCON_PRESETCTRLX_DATA_MASK)
/*! @} */

/* The count of SYSCON_PRESETCTRLX */
#define SYSCON_PRESETCTRLX_COUNT                 (3U)

/*! @name PRESETCTRLSET - Peripheral reset control set register */
/*! @{ */

#define SYSCON_PRESETCTRLSET_DATA_MASK           (0xFFFFFFFFU)
#define SYSCON_PRESETCTRLSET_DATA_SHIFT          (0U)
/*! DATA - Data array value */
#define SYSCON_PRESETCTRLSET_DATA(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRLSET_DATA_SHIFT)) & SYSCON_PRESETCTRLSET_DATA_MASK)
/*! @} */

/*! @name PRESETCTRLCLR - Peripheral reset control clear register */
/*! @{ */

#define SYSCON_PRESETCTRLCLR_DATA_MASK           (0xFFFFFFFFU)
#define SYSCON_PRESETCTRLCLR_DATA_SHIFT          (0U)
/*! DATA - Data array value */
#define SYSCON_PRESETCTRLCLR_DATA(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRLCLR_DATA_SHIFT)) & SYSCON_PRESETCTRLCLR_DATA_MASK)
/*! @} */

/*! @name SWR_RESET - generate a software_reset */
/*! @{ */

#define SYSCON_SWR_RESET_SWR_RESET_MASK          (0xFFFFFFFFU)
#define SYSCON_SWR_RESET_SWR_RESET_SHIFT         (0U)
/*! SWR_RESET - Write 0x5A00_0001 to generate a software_reset.
 *  0b01011010000000000000000000000001..Generate a software reset.
 *  0b00000000000000000000000000000000..Bloc is not reset.
 */
#define SYSCON_SWR_RESET_SWR_RESET(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_SWR_RESET_SWR_RESET_SHIFT)) & SYSCON_SWR_RESET_SWR_RESET_MASK)
/*! @} */

/*! @name AHBCLKCTRL0 - AHB Clock control 0 */
/*! @{ */

#define SYSCON_AHBCLKCTRL0_ROM_MASK              (0x2U)
#define SYSCON_AHBCLKCTRL0_ROM_SHIFT             (1U)
/*! ROM - Enables the clock for the ROM.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL0_ROM(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL0_ROM_SHIFT)) & SYSCON_AHBCLKCTRL0_ROM_MASK)

#define SYSCON_AHBCLKCTRL0_SRAM_CTRL1_MASK       (0x8U)
#define SYSCON_AHBCLKCTRL0_SRAM_CTRL1_SHIFT      (3U)
/*! SRAM_CTRL1 - Enables the clock for the SRAM Controller 1.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL0_SRAM_CTRL1(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL0_SRAM_CTRL1_SHIFT)) & SYSCON_AHBCLKCTRL0_SRAM_CTRL1_MASK)

#define SYSCON_AHBCLKCTRL0_SRAM_CTRL2_MASK       (0x10U)
#define SYSCON_AHBCLKCTRL0_SRAM_CTRL2_SHIFT      (4U)
/*! SRAM_CTRL2 - Enables the clock for the SRAM Controller 2.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL0_SRAM_CTRL2(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL0_SRAM_CTRL2_SHIFT)) & SYSCON_AHBCLKCTRL0_SRAM_CTRL2_MASK)

#define SYSCON_AHBCLKCTRL0_FLASH_MASK            (0x80U)
#define SYSCON_AHBCLKCTRL0_FLASH_SHIFT           (7U)
/*! FLASH - Enables the clock for the Flash controller.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL0_FLASH(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL0_FLASH_SHIFT)) & SYSCON_AHBCLKCTRL0_FLASH_MASK)

#define SYSCON_AHBCLKCTRL0_FMC_MASK              (0x100U)
#define SYSCON_AHBCLKCTRL0_FMC_SHIFT             (8U)
/*! FMC - Enables the clock for the FMC controller.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL0_FMC(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL0_FMC_SHIFT)) & SYSCON_AHBCLKCTRL0_FMC_MASK)

#define SYSCON_AHBCLKCTRL0_MUX_MASK              (0x800U)
#define SYSCON_AHBCLKCTRL0_MUX_SHIFT             (11U)
/*! MUX - Enables the clock for the Input Mux.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL0_MUX(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL0_MUX_SHIFT)) & SYSCON_AHBCLKCTRL0_MUX_MASK)

#define SYSCON_AHBCLKCTRL0_IOCON_MASK            (0x2000U)
#define SYSCON_AHBCLKCTRL0_IOCON_SHIFT           (13U)
/*! IOCON - Enables the clock for the I/O controller.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL0_IOCON(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL0_IOCON_SHIFT)) & SYSCON_AHBCLKCTRL0_IOCON_MASK)

#define SYSCON_AHBCLKCTRL0_GPIO0_MASK            (0x4000U)
#define SYSCON_AHBCLKCTRL0_GPIO0_SHIFT           (14U)
/*! GPIO0 - Enables the clock for the GPIO0.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL0_GPIO0(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL0_GPIO0_SHIFT)) & SYSCON_AHBCLKCTRL0_GPIO0_MASK)

#define SYSCON_AHBCLKCTRL0_GPIO1_MASK            (0x8000U)
#define SYSCON_AHBCLKCTRL0_GPIO1_SHIFT           (15U)
/*! GPIO1 - Enables the clock for the GPIO1.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL0_GPIO1(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL0_GPIO1_SHIFT)) & SYSCON_AHBCLKCTRL0_GPIO1_MASK)

#define SYSCON_AHBCLKCTRL0_PINT_MASK             (0x40000U)
#define SYSCON_AHBCLKCTRL0_PINT_SHIFT            (18U)
/*! PINT - Enables the clock for the Pin interrupt (PINT).
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL0_PINT(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL0_PINT_SHIFT)) & SYSCON_AHBCLKCTRL0_PINT_MASK)

#define SYSCON_AHBCLKCTRL0_GINT_MASK             (0x80000U)
#define SYSCON_AHBCLKCTRL0_GINT_SHIFT            (19U)
/*! GINT - Enables the clock for the Group interrupt (GINT).
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL0_GINT(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL0_GINT_SHIFT)) & SYSCON_AHBCLKCTRL0_GINT_MASK)

#define SYSCON_AHBCLKCTRL0_DMA0_MASK             (0x100000U)
#define SYSCON_AHBCLKCTRL0_DMA0_SHIFT            (20U)
/*! DMA0 - Enables the clock for the DMA0.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL0_DMA0(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL0_DMA0_SHIFT)) & SYSCON_AHBCLKCTRL0_DMA0_MASK)

#define SYSCON_AHBCLKCTRL0_CRCGEN_MASK           (0x200000U)
#define SYSCON_AHBCLKCTRL0_CRCGEN_SHIFT          (21U)
/*! CRCGEN - Enables the clock for the CRCGEN.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL0_CRCGEN(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL0_CRCGEN_SHIFT)) & SYSCON_AHBCLKCTRL0_CRCGEN_MASK)

#define SYSCON_AHBCLKCTRL0_WWDT_MASK             (0x400000U)
#define SYSCON_AHBCLKCTRL0_WWDT_SHIFT            (22U)
/*! WWDT - Enables the clock for the Watchdog Timer.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL0_WWDT(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL0_WWDT_SHIFT)) & SYSCON_AHBCLKCTRL0_WWDT_MASK)

#define SYSCON_AHBCLKCTRL0_RTC_MASK              (0x800000U)
#define SYSCON_AHBCLKCTRL0_RTC_SHIFT             (23U)
/*! RTC - Enables the clock for the Real Time Clock (RTC).
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL0_RTC(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL0_RTC_SHIFT)) & SYSCON_AHBCLKCTRL0_RTC_MASK)

#define SYSCON_AHBCLKCTRL0_MAILBOX_MASK          (0x4000000U)
#define SYSCON_AHBCLKCTRL0_MAILBOX_SHIFT         (26U)
/*! MAILBOX - Enables the clock for the Inter CPU communication Mailbox.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL0_MAILBOX(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL0_MAILBOX_SHIFT)) & SYSCON_AHBCLKCTRL0_MAILBOX_MASK)

#define SYSCON_AHBCLKCTRL0_ADC_MASK              (0x8000000U)
#define SYSCON_AHBCLKCTRL0_ADC_SHIFT             (27U)
/*! ADC - Enables the clock for the ADC.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL0_ADC(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL0_ADC_SHIFT)) & SYSCON_AHBCLKCTRL0_ADC_MASK)
/*! @} */

/*! @name AHBCLKCTRL1 - AHB Clock control 1 */
/*! @{ */

#define SYSCON_AHBCLKCTRL1_MRT_MASK              (0x1U)
#define SYSCON_AHBCLKCTRL1_MRT_SHIFT             (0U)
/*! MRT - Enables the clock for the MRT.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL1_MRT(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL1_MRT_SHIFT)) & SYSCON_AHBCLKCTRL1_MRT_MASK)

#define SYSCON_AHBCLKCTRL1_OSTIMER_MASK          (0x2U)
#define SYSCON_AHBCLKCTRL1_OSTIMER_SHIFT         (1U)
/*! OSTIMER - Enables the clock for the OS Event Timer.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL1_OSTIMER(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL1_OSTIMER_SHIFT)) & SYSCON_AHBCLKCTRL1_OSTIMER_MASK)

#define SYSCON_AHBCLKCTRL1_SCT_MASK              (0x4U)
#define SYSCON_AHBCLKCTRL1_SCT_SHIFT             (2U)
/*! SCT - Enables the clock for the SCT.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL1_SCT(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL1_SCT_SHIFT)) & SYSCON_AHBCLKCTRL1_SCT_MASK)

#define SYSCON_AHBCLKCTRL1_CAN_MASK              (0x80U)
#define SYSCON_AHBCLKCTRL1_CAN_SHIFT             (7U)
/*! CAN - Enables the clock for the CAN.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL1_CAN(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL1_CAN_SHIFT)) & SYSCON_AHBCLKCTRL1_CAN_MASK)

#define SYSCON_AHBCLKCTRL1_UTICK_MASK            (0x400U)
#define SYSCON_AHBCLKCTRL1_UTICK_SHIFT           (10U)
/*! UTICK - Enables the clock for the UTICK.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL1_UTICK(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL1_UTICK_SHIFT)) & SYSCON_AHBCLKCTRL1_UTICK_MASK)

#define SYSCON_AHBCLKCTRL1_FC0_MASK              (0x800U)
#define SYSCON_AHBCLKCTRL1_FC0_SHIFT             (11U)
/*! FC0 - Enables the clock for the FC0.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL1_FC0(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL1_FC0_SHIFT)) & SYSCON_AHBCLKCTRL1_FC0_MASK)

#define SYSCON_AHBCLKCTRL1_FC1_MASK              (0x1000U)
#define SYSCON_AHBCLKCTRL1_FC1_SHIFT             (12U)
/*! FC1 - Enables the clock for the FC1.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL1_FC1(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL1_FC1_SHIFT)) & SYSCON_AHBCLKCTRL1_FC1_MASK)

#define SYSCON_AHBCLKCTRL1_FC2_MASK              (0x2000U)
#define SYSCON_AHBCLKCTRL1_FC2_SHIFT             (13U)
/*! FC2 - Enables the clock for the FC2.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL1_FC2(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL1_FC2_SHIFT)) & SYSCON_AHBCLKCTRL1_FC2_MASK)

#define SYSCON_AHBCLKCTRL1_FC3_MASK              (0x4000U)
#define SYSCON_AHBCLKCTRL1_FC3_SHIFT             (14U)
/*! FC3 - Enables the clock for the FC3.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL1_FC3(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL1_FC3_SHIFT)) & SYSCON_AHBCLKCTRL1_FC3_MASK)

#define SYSCON_AHBCLKCTRL1_FC4_MASK              (0x8000U)
#define SYSCON_AHBCLKCTRL1_FC4_SHIFT             (15U)
/*! FC4 - Enables the clock for the FC4.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL1_FC4(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL1_FC4_SHIFT)) & SYSCON_AHBCLKCTRL1_FC4_MASK)

#define SYSCON_AHBCLKCTRL1_FC5_MASK              (0x10000U)
#define SYSCON_AHBCLKCTRL1_FC5_SHIFT             (16U)
/*! FC5 - Enables the clock for the FC5.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL1_FC5(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL1_FC5_SHIFT)) & SYSCON_AHBCLKCTRL1_FC5_MASK)

#define SYSCON_AHBCLKCTRL1_FC6_MASK              (0x20000U)
#define SYSCON_AHBCLKCTRL1_FC6_SHIFT             (17U)
/*! FC6 - Enables the clock for the FC6.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL1_FC6(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL1_FC6_SHIFT)) & SYSCON_AHBCLKCTRL1_FC6_MASK)

#define SYSCON_AHBCLKCTRL1_FC7_MASK              (0x40000U)
#define SYSCON_AHBCLKCTRL1_FC7_SHIFT             (18U)
/*! FC7 - Enables the clock for the FC7.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL1_FC7(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL1_FC7_SHIFT)) & SYSCON_AHBCLKCTRL1_FC7_MASK)

#define SYSCON_AHBCLKCTRL1_TIMER2_MASK           (0x400000U)
#define SYSCON_AHBCLKCTRL1_TIMER2_SHIFT          (22U)
/*! TIMER2 - Enables the clock for the Timer 2.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL1_TIMER2(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL1_TIMER2_SHIFT)) & SYSCON_AHBCLKCTRL1_TIMER2_MASK)

#define SYSCON_AHBCLKCTRL1_USB0_DEV_MASK         (0x2000000U)
#define SYSCON_AHBCLKCTRL1_USB0_DEV_SHIFT        (25U)
/*! USB0_DEV - Enables the clock for the USB0-FS device.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL1_USB0_DEV(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL1_USB0_DEV_SHIFT)) & SYSCON_AHBCLKCTRL1_USB0_DEV_MASK)

#define SYSCON_AHBCLKCTRL1_TIMER0_MASK           (0x4000000U)
#define SYSCON_AHBCLKCTRL1_TIMER0_SHIFT          (26U)
/*! TIMER0 - Enables the clock for the Timer 0.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL1_TIMER0(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL1_TIMER0_SHIFT)) & SYSCON_AHBCLKCTRL1_TIMER0_MASK)

#define SYSCON_AHBCLKCTRL1_TIMER1_MASK           (0x8000000U)
#define SYSCON_AHBCLKCTRL1_TIMER1_SHIFT          (27U)
/*! TIMER1 - Enables the clock for the Timer 1.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL1_TIMER1(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL1_TIMER1_SHIFT)) & SYSCON_AHBCLKCTRL1_TIMER1_MASK)
/*! @} */

/*! @name AHBCLKCTRL2 - AHB Clock control 2 */
/*! @{ */

#define SYSCON_AHBCLKCTRL2_DMA1_MASK             (0x2U)
#define SYSCON_AHBCLKCTRL2_DMA1_SHIFT            (1U)
/*! DMA1 - Enables the clock for the DMA1.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_DMA1(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_DMA1_SHIFT)) & SYSCON_AHBCLKCTRL2_DMA1_MASK)

#define SYSCON_AHBCLKCTRL2_COMP_MASK             (0x4U)
#define SYSCON_AHBCLKCTRL2_COMP_SHIFT            (2U)
/*! COMP - Enables the clock for the Comparator.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_COMP(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_COMP_SHIFT)) & SYSCON_AHBCLKCTRL2_COMP_MASK)

#define SYSCON_AHBCLKCTRL2_USB1_HOST_MASK        (0x10U)
#define SYSCON_AHBCLKCTRL2_USB1_HOST_SHIFT       (4U)
/*! USB1_HOST - Enables the clock for the USB1-HS Host.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_USB1_HOST(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_USB1_HOST_SHIFT)) & SYSCON_AHBCLKCTRL2_USB1_HOST_MASK)

#define SYSCON_AHBCLKCTRL2_USB1_DEV_MASK         (0x20U)
#define SYSCON_AHBCLKCTRL2_USB1_DEV_SHIFT        (5U)
/*! USB1_DEV - Enables the clock for the USB1-HS device.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_USB1_DEV(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_USB1_DEV_SHIFT)) & SYSCON_AHBCLKCTRL2_USB1_DEV_MASK)

#define SYSCON_AHBCLKCTRL2_USB1_RAM_MASK         (0x40U)
#define SYSCON_AHBCLKCTRL2_USB1_RAM_SHIFT        (6U)
/*! USB1_RAM - Enables the clock for the USB1-HS RAM.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_USB1_RAM(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_USB1_RAM_SHIFT)) & SYSCON_AHBCLKCTRL2_USB1_RAM_MASK)

#define SYSCON_AHBCLKCTRL2_USB1_PHY_MASK         (0x80U)
#define SYSCON_AHBCLKCTRL2_USB1_PHY_SHIFT        (7U)
/*! USB1_PHY - Enables the clock for the USB1-HS PHY.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_USB1_PHY(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_USB1_PHY_SHIFT)) & SYSCON_AHBCLKCTRL2_USB1_PHY_MASK)

#define SYSCON_AHBCLKCTRL2_FREQME_MASK           (0x100U)
#define SYSCON_AHBCLKCTRL2_FREQME_SHIFT          (8U)
/*! FREQME - Enables the clock for the Frequency meter.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_FREQME(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_FREQME_SHIFT)) & SYSCON_AHBCLKCTRL2_FREQME_MASK)

#define SYSCON_AHBCLKCTRL2_CDOG_MASK             (0x800U)
#define SYSCON_AHBCLKCTRL2_CDOG_SHIFT            (11U)
/*! CDOG - Enables the clock for the code watchdog.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_CDOG(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_CDOG_SHIFT)) & SYSCON_AHBCLKCTRL2_CDOG_MASK)

#define SYSCON_AHBCLKCTRL2_RNG_MASK              (0x2000U)
#define SYSCON_AHBCLKCTRL2_RNG_SHIFT             (13U)
/*! RNG - Enables the clock for the RNG.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_RNG(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_RNG_SHIFT)) & SYSCON_AHBCLKCTRL2_RNG_MASK)

#define SYSCON_AHBCLKCTRL2_SYSCTL_MASK           (0x8000U)
#define SYSCON_AHBCLKCTRL2_SYSCTL_SHIFT          (15U)
/*! SYSCTL - SYSCTL block clock.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_SYSCTL(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_SYSCTL_SHIFT)) & SYSCON_AHBCLKCTRL2_SYSCTL_MASK)

#define SYSCON_AHBCLKCTRL2_USB0_HOSTM_MASK       (0x10000U)
#define SYSCON_AHBCLKCTRL2_USB0_HOSTM_SHIFT      (16U)
/*! USB0_HOSTM - Enables the clock for the USB0-FS Host Master.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_USB0_HOSTM(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_USB0_HOSTM_SHIFT)) & SYSCON_AHBCLKCTRL2_USB0_HOSTM_MASK)

#define SYSCON_AHBCLKCTRL2_USB0_HOSTS_MASK       (0x20000U)
#define SYSCON_AHBCLKCTRL2_USB0_HOSTS_SHIFT      (17U)
/*! USB0_HOSTS - Enables the clock for the USB0-FS Host Slave.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_USB0_HOSTS(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_USB0_HOSTS_SHIFT)) & SYSCON_AHBCLKCTRL2_USB0_HOSTS_MASK)

#define SYSCON_AHBCLKCTRL2_HASH_AES_MASK         (0x40000U)
#define SYSCON_AHBCLKCTRL2_HASH_AES_SHIFT        (18U)
/*! HASH_AES - Enables the clock for the HASH_AES.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_HASH_AES(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_HASH_AES_SHIFT)) & SYSCON_AHBCLKCTRL2_HASH_AES_MASK)

#define SYSCON_AHBCLKCTRL2_PLULUT_MASK           (0x100000U)
#define SYSCON_AHBCLKCTRL2_PLULUT_SHIFT          (20U)
/*! PLULUT - Enables the clock for the PLU LUT.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_PLULUT(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_PLULUT_SHIFT)) & SYSCON_AHBCLKCTRL2_PLULUT_MASK)

#define SYSCON_AHBCLKCTRL2_TIMER3_MASK           (0x200000U)
#define SYSCON_AHBCLKCTRL2_TIMER3_SHIFT          (21U)
/*! TIMER3 - Enables the clock for the Timer 3.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_TIMER3(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_TIMER3_SHIFT)) & SYSCON_AHBCLKCTRL2_TIMER3_MASK)

#define SYSCON_AHBCLKCTRL2_TIMER4_MASK           (0x400000U)
#define SYSCON_AHBCLKCTRL2_TIMER4_SHIFT          (22U)
/*! TIMER4 - Enables the clock for the Timer 4.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_TIMER4(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_TIMER4_SHIFT)) & SYSCON_AHBCLKCTRL2_TIMER4_MASK)

#define SYSCON_AHBCLKCTRL2_PUF_MASK              (0x800000U)
#define SYSCON_AHBCLKCTRL2_PUF_SHIFT             (23U)
/*! PUF - Enables the clock for the PUF reset control.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_PUF(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_PUF_SHIFT)) & SYSCON_AHBCLKCTRL2_PUF_MASK)

#define SYSCON_AHBCLKCTRL2_CASPER_MASK           (0x1000000U)
#define SYSCON_AHBCLKCTRL2_CASPER_SHIFT          (24U)
/*! CASPER - Enables the clock for the Casper.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_CASPER(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_CASPER_SHIFT)) & SYSCON_AHBCLKCTRL2_CASPER_MASK)

#define SYSCON_AHBCLKCTRL2_ANALOG_CTRL_MASK      (0x8000000U)
#define SYSCON_AHBCLKCTRL2_ANALOG_CTRL_SHIFT     (27U)
/*! ANALOG_CTRL - Enables the clock for the analog control.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_ANALOG_CTRL(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_ANALOG_CTRL_SHIFT)) & SYSCON_AHBCLKCTRL2_ANALOG_CTRL_MASK)

#define SYSCON_AHBCLKCTRL2_HS_LSPI_MASK          (0x10000000U)
#define SYSCON_AHBCLKCTRL2_HS_LSPI_SHIFT         (28U)
/*! HS_LSPI - Enables the clock for the HS LSPI.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_HS_LSPI(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_HS_LSPI_SHIFT)) & SYSCON_AHBCLKCTRL2_HS_LSPI_MASK)

#define SYSCON_AHBCLKCTRL2_GPIO_SEC_MASK         (0x20000000U)
#define SYSCON_AHBCLKCTRL2_GPIO_SEC_SHIFT        (29U)
/*! GPIO_SEC - Enables the clock for the GPIO secure.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_GPIO_SEC(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_GPIO_SEC_SHIFT)) & SYSCON_AHBCLKCTRL2_GPIO_SEC_MASK)

#define SYSCON_AHBCLKCTRL2_GPIO_SEC_INT_MASK     (0x40000000U)
#define SYSCON_AHBCLKCTRL2_GPIO_SEC_INT_SHIFT    (30U)
/*! GPIO_SEC_INT - Enables the clock for the GPIO secure int.
 *  0b1..Enable Clock.
 *  0b0..Disable Clock.
 */
#define SYSCON_AHBCLKCTRL2_GPIO_SEC_INT(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL2_GPIO_SEC_INT_SHIFT)) & SYSCON_AHBCLKCTRL2_GPIO_SEC_INT_MASK)
/*! @} */

/*! @name AHBCLKCTRLX - Peripheral reset control register */
/*! @{ */

#define SYSCON_AHBCLKCTRLX_DATA_MASK             (0xFFFFFFFFU)
#define SYSCON_AHBCLKCTRLX_DATA_SHIFT            (0U)
/*! DATA - Data array value */
#define SYSCON_AHBCLKCTRLX_DATA(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRLX_DATA_SHIFT)) & SYSCON_AHBCLKCTRLX_DATA_MASK)
/*! @} */

/* The count of SYSCON_AHBCLKCTRLX */
#define SYSCON_AHBCLKCTRLX_COUNT                 (3U)

/*! @name AHBCLKCTRLSET - Peripheral reset control register */
/*! @{ */

#define SYSCON_AHBCLKCTRLSET_DATA_MASK           (0xFFFFFFFFU)
#define SYSCON_AHBCLKCTRLSET_DATA_SHIFT          (0U)
/*! DATA - Data array value */
#define SYSCON_AHBCLKCTRLSET_DATA(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRLSET_DATA_SHIFT)) & SYSCON_AHBCLKCTRLSET_DATA_MASK)
/*! @} */

/*! @name AHBCLKCTRLCLR - Peripheral reset control register */
/*! @{ */

#define SYSCON_AHBCLKCTRLCLR_DATA_MASK           (0xFFFFFFFFU)
#define SYSCON_AHBCLKCTRLCLR_DATA_SHIFT          (0U)
/*! DATA - Data array value */
#define SYSCON_AHBCLKCTRLCLR_DATA(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRLCLR_DATA_SHIFT)) & SYSCON_AHBCLKCTRLCLR_DATA_MASK)
/*! @} */

/*! @name SYSTICKCLKSEL0 - System Tick Timer for CPU0 source select */
/*! @{ */

#define SYSCON_SYSTICKCLKSEL0_SEL_MASK           (0x7U)
#define SYSCON_SYSTICKCLKSEL0_SEL_SHIFT          (0U)
/*! SEL - System Tick Timer for CPU0 source select.
 *  0b000..System Tick 0 divided clock.
 *  0b001..FRO 1MHz clock.
 *  0b010..Oscillator 32 kHz clock.
 *  0b011..No clock.
 *  0b100..No clock.
 *  0b101..No clock.
 *  0b110..No clock.
 *  0b111..No clock.
 */
#define SYSCON_SYSTICKCLKSEL0_SEL(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTICKCLKSEL0_SEL_SHIFT)) & SYSCON_SYSTICKCLKSEL0_SEL_MASK)
/*! @} */

/*! @name SYSTICKCLKSELX - Peripheral reset control register */
/*! @{ */

#define SYSCON_SYSTICKCLKSELX_DATA_MASK          (0xFFFFFFFFU)
#define SYSCON_SYSTICKCLKSELX_DATA_SHIFT         (0U)
/*! DATA - Data array value */
#define SYSCON_SYSTICKCLKSELX_DATA(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTICKCLKSELX_DATA_SHIFT)) & SYSCON_SYSTICKCLKSELX_DATA_MASK)
/*! @} */

/* The count of SYSCON_SYSTICKCLKSELX */
#define SYSCON_SYSTICKCLKSELX_COUNT              (1U)

/*! @name TRACECLKSEL - Trace clock source select */
/*! @{ */

#define SYSCON_TRACECLKSEL_SEL_MASK              (0x7U)
#define SYSCON_TRACECLKSEL_SEL_SHIFT             (0U)
/*! SEL - Trace clock source select.
 *  0b000..Trace divided clock.
 *  0b001..FRO 1MHz clock.
 *  0b010..Oscillator 32 kHz clock.
 *  0b011..No clock.
 *  0b100..No clock.
 *  0b101..No clock.
 *  0b110..No clock.
 *  0b111..No clock.
 */
#define SYSCON_TRACECLKSEL_SEL(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_TRACECLKSEL_SEL_SHIFT)) & SYSCON_TRACECLKSEL_SEL_MASK)
/*! @} */

/*! @name CTIMERCLKSEL0 - CTimer 0 clock source select */
/*! @{ */

#define SYSCON_CTIMERCLKSEL0_SEL_MASK            (0x7U)
#define SYSCON_CTIMERCLKSEL0_SEL_SHIFT           (0U)
/*! SEL - CTimer 0 clock source select.
 *  0b000..Main clock.
 *  0b001..PLL0 clock.
 *  0b010..No clock.
 *  0b011..FRO 96 MHz clock.
 *  0b100..FRO 1MHz clock.
 *  0b101..MCLK clock.
 *  0b110..Oscillator 32kHz clock.
 *  0b111..No clock.
 */
#define SYSCON_CTIMERCLKSEL0_SEL(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_CTIMERCLKSEL0_SEL_SHIFT)) & SYSCON_CTIMERCLKSEL0_SEL_MASK)
/*! @} */

/*! @name CTIMERCLKSEL1 - CTimer 1 clock source select */
/*! @{ */

#define SYSCON_CTIMERCLKSEL1_SEL_MASK            (0x7U)
#define SYSCON_CTIMERCLKSEL1_SEL_SHIFT           (0U)
/*! SEL - CTimer 1 clock source select.
 *  0b000..Main clock.
 *  0b001..PLL0 clock.
 *  0b010..No clock.
 *  0b011..FRO 96 MHz clock.
 *  0b100..FRO 1MHz clock.
 *  0b101..MCLK clock.
 *  0b110..Oscillator 32kHz clock.
 *  0b111..No clock.
 */
#define SYSCON_CTIMERCLKSEL1_SEL(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_CTIMERCLKSEL1_SEL_SHIFT)) & SYSCON_CTIMERCLKSEL1_SEL_MASK)
/*! @} */

/*! @name CTIMERCLKSEL2 - CTimer 2 clock source select */
/*! @{ */

#define SYSCON_CTIMERCLKSEL2_SEL_MASK            (0x7U)
#define SYSCON_CTIMERCLKSEL2_SEL_SHIFT           (0U)
/*! SEL - CTimer 2 clock source select.
 *  0b000..Main clock.
 *  0b001..PLL0 clock.
 *  0b010..No clock.
 *  0b011..FRO 96 MHz clock.
 *  0b100..FRO 1MHz clock.
 *  0b101..MCLK clock.
 *  0b110..Oscillator 32kHz clock.
 *  0b111..No clock.
 */
#define SYSCON_CTIMERCLKSEL2_SEL(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_CTIMERCLKSEL2_SEL_SHIFT)) & SYSCON_CTIMERCLKSEL2_SEL_MASK)
/*! @} */

/*! @name CTIMERCLKSEL3 - CTimer 3 clock source select */
/*! @{ */

#define SYSCON_CTIMERCLKSEL3_SEL_MASK            (0x7U)
#define SYSCON_CTIMERCLKSEL3_SEL_SHIFT           (0U)
/*! SEL - CTimer 3 clock source select.
 *  0b000..Main clock.
 *  0b001..PLL0 clock.
 *  0b010..No clock.
 *  0b011..FRO 96 MHz clock.
 *  0b100..FRO 1MHz clock.
 *  0b101..MCLK clock.
 *  0b110..Oscillator 32kHz clock.
 *  0b111..No clock.
 */
#define SYSCON_CTIMERCLKSEL3_SEL(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_CTIMERCLKSEL3_SEL_SHIFT)) & SYSCON_CTIMERCLKSEL3_SEL_MASK)
/*! @} */

/*! @name CTIMERCLKSEL4 - CTimer 4 clock source select */
/*! @{ */

#define SYSCON_CTIMERCLKSEL4_SEL_MASK            (0x7U)
#define SYSCON_CTIMERCLKSEL4_SEL_SHIFT           (0U)
/*! SEL - CTimer 4 clock source select.
 *  0b000..Main clock.
 *  0b001..PLL0 clock.
 *  0b010..No clock.
 *  0b011..FRO 96 MHz clock.
 *  0b100..FRO 1MHz clock.
 *  0b101..MCLK clock.
 *  0b110..Oscillator 32kHz clock.
 *  0b111..No clock.
 */
#define SYSCON_CTIMERCLKSEL4_SEL(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_CTIMERCLKSEL4_SEL_SHIFT)) & SYSCON_CTIMERCLKSEL4_SEL_MASK)
/*! @} */

/*! @name CTIMERCLKSELX - Peripheral reset control register */
/*! @{ */

#define SYSCON_CTIMERCLKSELX_DATA_MASK           (0xFFFFFFFFU)
#define SYSCON_CTIMERCLKSELX_DATA_SHIFT          (0U)
/*! DATA - Data array value */
#define SYSCON_CTIMERCLKSELX_DATA(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_CTIMERCLKSELX_DATA_SHIFT)) & SYSCON_CTIMERCLKSELX_DATA_MASK)
/*! @} */

/* The count of SYSCON_CTIMERCLKSELX */
#define SYSCON_CTIMERCLKSELX_COUNT               (5U)

/*! @name MAINCLKSELA - Main clock A source select */
/*! @{ */

#define SYSCON_MAINCLKSELA_SEL_MASK              (0x7U)
#define SYSCON_MAINCLKSELA_SEL_SHIFT             (0U)
/*! SEL - Main clock A source select.
 *  0b000..FRO 12 MHz clock.
 *  0b001..CLKIN clock.
 *  0b010..FRO 1MHz clock.
 *  0b011..FRO 96 MHz clock.
 *  0b100..Reserved.
 *  0b101..Reserved.
 *  0b110..Reserved.
 *  0b111..Reserved.
 */
#define SYSCON_MAINCLKSELA_SEL(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_MAINCLKSELA_SEL_SHIFT)) & SYSCON_MAINCLKSELA_SEL_MASK)
/*! @} */

/*! @name MAINCLKSELB - Main clock source select */
/*! @{ */

#define SYSCON_MAINCLKSELB_SEL_MASK              (0x7U)
#define SYSCON_MAINCLKSELB_SEL_SHIFT             (0U)
/*! SEL - Main clock source select.
 *  0b000..Main Clock A.
 *  0b001..PLL0 clock.
 *  0b010..PLL1 clock.
 *  0b011..Oscillator 32 kHz clock.
 *  0b100..Reserved.
 *  0b101..Reserved.
 *  0b110..Reserved.
 *  0b111..Reserved.
 */
#define SYSCON_MAINCLKSELB_SEL(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_MAINCLKSELB_SEL_SHIFT)) & SYSCON_MAINCLKSELB_SEL_MASK)
/*! @} */

/*! @name CLKOUTSEL - CLKOUT clock source select */
/*! @{ */

#define SYSCON_CLKOUTSEL_SEL_MASK                (0xFU)
#define SYSCON_CLKOUTSEL_SEL_SHIFT               (0U)
/*! SEL - CLKOUT clock source select.
 *  0b0000..Main clock.
 *  0b0001..PLL0 clock.
 *  0b0010..CLKIN clock.
 *  0b0011..FRO 96 MHz clock.
 *  0b0100..FRO 1MHz clock.
 *  0b0101..PLL1 clock.
 *  0b0110..Oscillator 32kHz clock.
 *  0b0111..No clock.
 *  0b1000..Reserved.
 *  0b1001..Reserved.
 *  0b1010..Reserved.
 *  0b1011..Reserved.
 *  0b1100..No clock.
 *  0b1101..No clock.
 *  0b1110..No clock.
 *  0b1111..No clock.
 */
#define SYSCON_CLKOUTSEL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_CLKOUTSEL_SEL_SHIFT)) & SYSCON_CLKOUTSEL_SEL_MASK)
/*! @} */

/*! @name PLL0CLKSEL - PLL0 clock source select */
/*! @{ */

#define SYSCON_PLL0CLKSEL_SEL_MASK               (0x7U)
#define SYSCON_PLL0CLKSEL_SEL_SHIFT              (0U)
/*! SEL - PLL0 clock source select.
 *  0b000..FRO 12 MHz clock.
 *  0b001..CLKIN clock.
 *  0b010..FRO 1MHz clock.
 *  0b011..Oscillator 32kHz clock.
 *  0b100..No clock.
 *  0b101..No clock.
 *  0b110..No clock.
 *  0b111..No clock.
 */
#define SYSCON_PLL0CLKSEL_SEL(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CLKSEL_SEL_SHIFT)) & SYSCON_PLL0CLKSEL_SEL_MASK)
/*! @} */

/*! @name PLL1CLKSEL - PLL1 clock source select */
/*! @{ */

#define SYSCON_PLL1CLKSEL_SEL_MASK               (0x7U)
#define SYSCON_PLL1CLKSEL_SEL_SHIFT              (0U)
/*! SEL - PLL1 clock source select.
 *  0b000..FRO 12 MHz clock.
 *  0b001..CLKIN clock.
 *  0b010..FRO 1MHz clock.
 *  0b011..Oscillator 32kHz clock.
 *  0b100..No clock.
 *  0b101..No clock.
 *  0b110..No clock.
 *  0b111..No clock.
 */
#define SYSCON_PLL1CLKSEL_SEL(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1CLKSEL_SEL_SHIFT)) & SYSCON_PLL1CLKSEL_SEL_MASK)
/*! @} */

/*! @name CANCLKSEL - CAN clock source select */
/*! @{ */

#define SYSCON_CANCLKSEL_SEL_MASK                (0x7U)
#define SYSCON_CANCLKSEL_SEL_SHIFT               (0U)
/*! SEL - CAN clock source select.
 *  0b000..CAN divided clock.
 *  0b001..FRO 1MHz clock.
 *  0b010..Oscillator 32 kHz clock.
 *  0b011..No clock.
 *  0b100..No clock.
 *  0b101..No clock.
 *  0b110..No clock.
 *  0b111..No clock.
 */
#define SYSCON_CANCLKSEL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_CANCLKSEL_SEL_SHIFT)) & SYSCON_CANCLKSEL_SEL_MASK)
/*! @} */

/*! @name ADCCLKSEL - ADC clock source select */
/*! @{ */

#define SYSCON_ADCCLKSEL_SEL_MASK                (0x7U)
#define SYSCON_ADCCLKSEL_SEL_SHIFT               (0U)
/*! SEL - ADC clock source select.
 *  0b000..Main clock.
 *  0b001..PLL0 clock.
 *  0b010..FRO 96 MHz clock.
 *  0b011..Reserved.
 *  0b100..Xtal clock coming directly.
 *  0b101..No clock.
 *  0b110..No clock.
 *  0b111..No clock.
 */
#define SYSCON_ADCCLKSEL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_ADCCLKSEL_SEL_SHIFT)) & SYSCON_ADCCLKSEL_SEL_MASK)
/*! @} */

/*! @name USB0CLKSEL - FS USB clock source select */
/*! @{ */

#define SYSCON_USB0CLKSEL_SEL_MASK               (0x7U)
#define SYSCON_USB0CLKSEL_SEL_SHIFT              (0U)
/*! SEL - FS USB clock source select.
 *  0b000..Main clock.
 *  0b001..PLL0 clock.
 *  0b010..No clock.
 *  0b011..FRO 96 MHz clock.
 *  0b100..No clock.
 *  0b101..PLL1 clock.
 *  0b110..No clock.
 *  0b111..No clock.
 */
#define SYSCON_USB0CLKSEL_SEL(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0CLKSEL_SEL_SHIFT)) & SYSCON_USB0CLKSEL_SEL_MASK)
/*! @} */

/*! @name CLK32KCLKSEL - clock low speed source select for HS USB. */
/*! @{ */

#define SYSCON_CLK32KCLKSEL_SEL_MASK             (0x8U)
#define SYSCON_CLK32KCLKSEL_SEL_SHIFT            (3U)
/*! SEL - clock low speed source select for HS USB.
 *  0b0..Oscillator 32 kHz clock.
 *  0b1..FRO1MHz_divided clock.
 */
#define SYSCON_CLK32KCLKSEL_SEL(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_CLK32KCLKSEL_SEL_SHIFT)) & SYSCON_CLK32KCLKSEL_SEL_MASK)
/*! @} */

/*! @name FCCLKSEL0 - Flexcomm Interface 0 clock source select for Fractional Rate Divider */
/*! @{ */

#define SYSCON_FCCLKSEL0_SEL_MASK                (0x7U)
#define SYSCON_FCCLKSEL0_SEL_SHIFT               (0U)
/*! SEL - Flexcomm Interface 0 clock source select for Fractional Rate Divider.
 *  0b000..Main clock.
 *  0b001..system PLL divided clock.
 *  0b010..FRO 12 MHz clock.
 *  0b011..FRO 96 MHz clock.
 *  0b100..FRO 1MHz clock.
 *  0b101..MCLK clock.
 *  0b110..Oscillator 32 kHz clock.
 *  0b111..No clock.
 */
#define SYSCON_FCCLKSEL0_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_FCCLKSEL0_SEL_SHIFT)) & SYSCON_FCCLKSEL0_SEL_MASK)
/*! @} */

/*! @name FCCLKSEL1 - Flexcomm Interface 1 clock source select for Fractional Rate Divider */
/*! @{ */

#define SYSCON_FCCLKSEL1_SEL_MASK                (0x7U)
#define SYSCON_FCCLKSEL1_SEL_SHIFT               (0U)
/*! SEL - Flexcomm Interface 1 clock source select for Fractional Rate Divider.
 *  0b000..Main clock.
 *  0b001..system PLL divided clock.
 *  0b010..FRO 12 MHz clock.
 *  0b011..FRO 96 MHz clock.
 *  0b100..FRO 1MHz clock.
 *  0b101..MCLK clock.
 *  0b110..Oscillator 32 kHz clock.
 *  0b111..No clock.
 */
#define SYSCON_FCCLKSEL1_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_FCCLKSEL1_SEL_SHIFT)) & SYSCON_FCCLKSEL1_SEL_MASK)
/*! @} */

/*! @name FCCLKSEL2 - Flexcomm Interface 2 clock source select for Fractional Rate Divider */
/*! @{ */

#define SYSCON_FCCLKSEL2_SEL_MASK                (0x7U)
#define SYSCON_FCCLKSEL2_SEL_SHIFT               (0U)
/*! SEL - Flexcomm Interface 2 clock source select for Fractional Rate Divider.
 *  0b000..Main clock.
 *  0b001..system PLL divided clock.
 *  0b010..FRO 12 MHz clock.
 *  0b011..FRO 96 MHz clock.
 *  0b100..FRO 1MHz clock.
 *  0b101..MCLK clock.
 *  0b110..Oscillator 32 kHz clock.
 *  0b111..No clock.
 */
#define SYSCON_FCCLKSEL2_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_FCCLKSEL2_SEL_SHIFT)) & SYSCON_FCCLKSEL2_SEL_MASK)
/*! @} */

/*! @name FCCLKSEL3 - Flexcomm Interface 3 clock source select for Fractional Rate Divider */
/*! @{ */

#define SYSCON_FCCLKSEL3_SEL_MASK                (0x7U)
#define SYSCON_FCCLKSEL3_SEL_SHIFT               (0U)
/*! SEL - Flexcomm Interface 3 clock source select for Fractional Rate Divider.
 *  0b000..Main clock.
 *  0b001..system PLL divided clock.
 *  0b010..FRO 12 MHz clock.
 *  0b011..FRO 96 MHz clock.
 *  0b100..FRO 1MHz clock.
 *  0b101..MCLK clock.
 *  0b110..Oscillator 32 kHz clock.
 *  0b111..No clock.
 */
#define SYSCON_FCCLKSEL3_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_FCCLKSEL3_SEL_SHIFT)) & SYSCON_FCCLKSEL3_SEL_MASK)
/*! @} */

/*! @name FCCLKSEL4 - Flexcomm Interface 4 clock source select for Fractional Rate Divider */
/*! @{ */

#define SYSCON_FCCLKSEL4_SEL_MASK                (0x7U)
#define SYSCON_FCCLKSEL4_SEL_SHIFT               (0U)
/*! SEL - Flexcomm Interface 4 clock source select for Fractional Rate Divider.
 *  0b000..Main clock.
 *  0b001..system PLL divided clock.
 *  0b010..FRO 12 MHz clock.
 *  0b011..FRO 96 MHz clock.
 *  0b100..FRO 1MHz clock.
 *  0b101..MCLK clock.
 *  0b110..Oscillator 32 kHz clock.
 *  0b111..No clock.
 */
#define SYSCON_FCCLKSEL4_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_FCCLKSEL4_SEL_SHIFT)) & SYSCON_FCCLKSEL4_SEL_MASK)
/*! @} */

/*! @name FCCLKSEL5 - Flexcomm Interface 5 clock source select for Fractional Rate Divider */
/*! @{ */

#define SYSCON_FCCLKSEL5_SEL_MASK                (0x7U)
#define SYSCON_FCCLKSEL5_SEL_SHIFT               (0U)
/*! SEL - Flexcomm Interface 5 clock source select for Fractional Rate Divider.
 *  0b000..Main clock.
 *  0b001..system PLL divided clock.
 *  0b010..FRO 12 MHz clock.
 *  0b011..FRO 96 MHz clock.
 *  0b100..FRO 1MHz clock.
 *  0b101..MCLK clock.
 *  0b110..Oscillator 32 kHz clock.
 *  0b111..No clock.
 */
#define SYSCON_FCCLKSEL5_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_FCCLKSEL5_SEL_SHIFT)) & SYSCON_FCCLKSEL5_SEL_MASK)
/*! @} */

/*! @name FCCLKSEL6 - Flexcomm Interface 6 clock source select for Fractional Rate Divider */
/*! @{ */

#define SYSCON_FCCLKSEL6_SEL_MASK                (0x7U)
#define SYSCON_FCCLKSEL6_SEL_SHIFT               (0U)
/*! SEL - Flexcomm Interface 6 clock source select for Fractional Rate Divider.
 *  0b000..Main clock.
 *  0b001..system PLL divided clock.
 *  0b010..FRO 12 MHz clock.
 *  0b011..FRO 96 MHz clock.
 *  0b100..FRO 1MHz clock.
 *  0b101..MCLK clock.
 *  0b110..Oscillator 32 kHz clock.
 *  0b111..No clock.
 */
#define SYSCON_FCCLKSEL6_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_FCCLKSEL6_SEL_SHIFT)) & SYSCON_FCCLKSEL6_SEL_MASK)
/*! @} */

/*! @name FCCLKSEL7 - Flexcomm Interface 7 clock source select for Fractional Rate Divider */
/*! @{ */

#define SYSCON_FCCLKSEL7_SEL_MASK                (0x7U)
#define SYSCON_FCCLKSEL7_SEL_SHIFT               (0U)
/*! SEL - Flexcomm Interface 7 clock source select for Fractional Rate Divider.
 *  0b000..Main clock.
 *  0b001..system PLL divided clock.
 *  0b010..FRO 12 MHz clock.
 *  0b011..FRO 96 MHz clock.
 *  0b100..FRO 1MHz clock.
 *  0b101..MCLK clock.
 *  0b110..Oscillator 32 kHz clock.
 *  0b111..No clock.
 */
#define SYSCON_FCCLKSEL7_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_FCCLKSEL7_SEL_SHIFT)) & SYSCON_FCCLKSEL7_SEL_MASK)
/*! @} */

/*! @name FCCLKSELX - Peripheral reset control register */
/*! @{ */

#define SYSCON_FCCLKSELX_DATA_MASK               (0xFFFFFFFFU)
#define SYSCON_FCCLKSELX_DATA_SHIFT              (0U)
/*! DATA - Data array value */
#define SYSCON_FCCLKSELX_DATA(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_FCCLKSELX_DATA_SHIFT)) & SYSCON_FCCLKSELX_DATA_MASK)
/*! @} */

/* The count of SYSCON_FCCLKSELX */
#define SYSCON_FCCLKSELX_COUNT                   (8U)

/*! @name HSLSPICLKSEL - HS LSPI clock source select */
/*! @{ */

#define SYSCON_HSLSPICLKSEL_SEL_MASK             (0x7U)
#define SYSCON_HSLSPICLKSEL_SEL_SHIFT            (0U)
/*! SEL - HS LSPI clock source select.
 *  0b000..Main clock.
 *  0b001..system PLL divided clock.
 *  0b010..FRO 12 MHz clock.
 *  0b011..FRO 96 MHz clock.
 *  0b100..FRO 1MHz clock.
 *  0b101..No clock.
 *  0b110..Oscillator 32 kHz clock.
 *  0b111..No clock.
 */
#define SYSCON_HSLSPICLKSEL_SEL(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_HSLSPICLKSEL_SEL_SHIFT)) & SYSCON_HSLSPICLKSEL_SEL_MASK)
/*! @} */

/*! @name MCLKCLKSEL - MCLK clock source select */
/*! @{ */

#define SYSCON_MCLKCLKSEL_SEL_MASK               (0x7U)
#define SYSCON_MCLKCLKSEL_SEL_SHIFT              (0U)
/*! SEL - MCLK clock source select.
 *  0b000..FRO 96 MHz clock.
 *  0b001..PLL0 clock.
 *  0b010..Reserved.
 *  0b011..Reserved.
 *  0b100..No clock.
 *  0b101..No clock.
 *  0b110..No clock.
 *  0b111..No clock.
 */
#define SYSCON_MCLKCLKSEL_SEL(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_MCLKCLKSEL_SEL_SHIFT)) & SYSCON_MCLKCLKSEL_SEL_MASK)
/*! @} */

/*! @name SCTCLKSEL - SCTimer/PWM clock source select */
/*! @{ */

#define SYSCON_SCTCLKSEL_SEL_MASK                (0x7U)
#define SYSCON_SCTCLKSEL_SEL_SHIFT               (0U)
/*! SEL - SCTimer/PWM clock source select.
 *  0b000..Main clock.
 *  0b001..PLL0 clock.
 *  0b010..CLKIN clock.
 *  0b011..FRO 96 MHz clock.
 *  0b100..No clock.
 *  0b101..MCLK clock.
 *  0b110..No clock.
 *  0b111..No clock.
 */
#define SYSCON_SCTCLKSEL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_SCTCLKSEL_SEL_SHIFT)) & SYSCON_SCTCLKSEL_SEL_MASK)
/*! @} */

/*! @name SYSTICKCLKDIV0 - System Tick Timer divider for CPU0 */
/*! @{ */

#define SYSCON_SYSTICKCLKDIV0_DIV_MASK           (0xFFU)
#define SYSCON_SYSTICKCLKDIV0_DIV_SHIFT          (0U)
/*! DIV - Clock divider value. */
#define SYSCON_SYSTICKCLKDIV0_DIV(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTICKCLKDIV0_DIV_SHIFT)) & SYSCON_SYSTICKCLKDIV0_DIV_MASK)

#define SYSCON_SYSTICKCLKDIV0_RESET_MASK         (0x20000000U)
#define SYSCON_SYSTICKCLKDIV0_RESET_SHIFT        (29U)
/*! RESET - Resets the divider counter.
 *  0b1..Divider is reset.
 *  0b0..Divider is not reset.
 */
#define SYSCON_SYSTICKCLKDIV0_RESET(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTICKCLKDIV0_RESET_SHIFT)) & SYSCON_SYSTICKCLKDIV0_RESET_MASK)

#define SYSCON_SYSTICKCLKDIV0_HALT_MASK          (0x40000000U)
#define SYSCON_SYSTICKCLKDIV0_HALT_SHIFT         (30U)
/*! HALT - Halts the divider counter.
 *  0b1..Divider clock is stoped.
 *  0b0..Divider clock is running.
 */
#define SYSCON_SYSTICKCLKDIV0_HALT(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTICKCLKDIV0_HALT_SHIFT)) & SYSCON_SYSTICKCLKDIV0_HALT_MASK)

#define SYSCON_SYSTICKCLKDIV0_REQFLAG_MASK       (0x80000000U)
#define SYSCON_SYSTICKCLKDIV0_REQFLAG_SHIFT      (31U)
/*! REQFLAG - Divider status flag.
 *  0b1..Clock frequency is not stable.
 *  0b0..Divider clock is stable.
 */
#define SYSCON_SYSTICKCLKDIV0_REQFLAG(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTICKCLKDIV0_REQFLAG_SHIFT)) & SYSCON_SYSTICKCLKDIV0_REQFLAG_MASK)
/*! @} */

/*! @name TRACECLKDIV - TRACE clock divider */
/*! @{ */

#define SYSCON_TRACECLKDIV_DIV_MASK              (0xFFU)
#define SYSCON_TRACECLKDIV_DIV_SHIFT             (0U)
/*! DIV - Clock divider value. */
#define SYSCON_TRACECLKDIV_DIV(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_TRACECLKDIV_DIV_SHIFT)) & SYSCON_TRACECLKDIV_DIV_MASK)

#define SYSCON_TRACECLKDIV_RESET_MASK            (0x20000000U)
#define SYSCON_TRACECLKDIV_RESET_SHIFT           (29U)
/*! RESET - Resets the divider counter.
 *  0b1..Divider is reset.
 *  0b0..Divider is not reset.
 */
#define SYSCON_TRACECLKDIV_RESET(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_TRACECLKDIV_RESET_SHIFT)) & SYSCON_TRACECLKDIV_RESET_MASK)

#define SYSCON_TRACECLKDIV_HALT_MASK             (0x40000000U)
#define SYSCON_TRACECLKDIV_HALT_SHIFT            (30U)
/*! HALT - Halts the divider counter.
 *  0b1..Divider clock is stoped.
 *  0b0..Divider clock is running.
 */
#define SYSCON_TRACECLKDIV_HALT(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_TRACECLKDIV_HALT_SHIFT)) & SYSCON_TRACECLKDIV_HALT_MASK)

#define SYSCON_TRACECLKDIV_REQFLAG_MASK          (0x80000000U)
#define SYSCON_TRACECLKDIV_REQFLAG_SHIFT         (31U)
/*! REQFLAG - Divider status flag.
 *  0b1..Clock frequency is not stable.
 *  0b0..Divider clock is stable.
 */
#define SYSCON_TRACECLKDIV_REQFLAG(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_TRACECLKDIV_REQFLAG_SHIFT)) & SYSCON_TRACECLKDIV_REQFLAG_MASK)
/*! @} */

/*! @name CANCLKDIV - CAN clock divider */
/*! @{ */

#define SYSCON_CANCLKDIV_DIV_MASK                (0xFFU)
#define SYSCON_CANCLKDIV_DIV_SHIFT               (0U)
/*! DIV - Clock divider value. */
#define SYSCON_CANCLKDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_CANCLKDIV_DIV_SHIFT)) & SYSCON_CANCLKDIV_DIV_MASK)

#define SYSCON_CANCLKDIV_RESET_MASK              (0x20000000U)
#define SYSCON_CANCLKDIV_RESET_SHIFT             (29U)
/*! RESET - Resets the divider counter.
 *  0b1..Divider is reset.
 *  0b0..Divider is not reset.
 */
#define SYSCON_CANCLKDIV_RESET(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_CANCLKDIV_RESET_SHIFT)) & SYSCON_CANCLKDIV_RESET_MASK)

#define SYSCON_CANCLKDIV_HALT_MASK               (0x40000000U)
#define SYSCON_CANCLKDIV_HALT_SHIFT              (30U)
/*! HALT - Halts the divider counter.
 *  0b1..Divider clock is stoped.
 *  0b0..Divider clock is running.
 */
#define SYSCON_CANCLKDIV_HALT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_CANCLKDIV_HALT_SHIFT)) & SYSCON_CANCLKDIV_HALT_MASK)

#define SYSCON_CANCLKDIV_REQFLAG_MASK            (0x80000000U)
#define SYSCON_CANCLKDIV_REQFLAG_SHIFT           (31U)
/*! REQFLAG - Divider status flag.
 *  0b1..Clock frequency is not stable.
 *  0b0..Divider clock is stable.
 */
#define SYSCON_CANCLKDIV_REQFLAG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_CANCLKDIV_REQFLAG_SHIFT)) & SYSCON_CANCLKDIV_REQFLAG_MASK)
/*! @} */

/*! @name FLEXFRG0CTRL - Fractional rate divider for flexcomm 0 */
/*! @{ */

#define SYSCON_FLEXFRG0CTRL_DIV_MASK             (0xFFU)
#define SYSCON_FLEXFRG0CTRL_DIV_SHIFT            (0U)
/*! DIV - Denominator of the fractional rate divider. */
#define SYSCON_FLEXFRG0CTRL_DIV(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FLEXFRG0CTRL_DIV_SHIFT)) & SYSCON_FLEXFRG0CTRL_DIV_MASK)

#define SYSCON_FLEXFRG0CTRL_MULT_MASK            (0xFF00U)
#define SYSCON_FLEXFRG0CTRL_MULT_SHIFT           (8U)
/*! MULT - Numerator of the fractional rate divider. */
#define SYSCON_FLEXFRG0CTRL_MULT(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FLEXFRG0CTRL_MULT_SHIFT)) & SYSCON_FLEXFRG0CTRL_MULT_MASK)
/*! @} */

/*! @name FLEXFRG1CTRL - Fractional rate divider for flexcomm 1 */
/*! @{ */

#define SYSCON_FLEXFRG1CTRL_DIV_MASK             (0xFFU)
#define SYSCON_FLEXFRG1CTRL_DIV_SHIFT            (0U)
/*! DIV - Denominator of the fractional rate divider. */
#define SYSCON_FLEXFRG1CTRL_DIV(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FLEXFRG1CTRL_DIV_SHIFT)) & SYSCON_FLEXFRG1CTRL_DIV_MASK)

#define SYSCON_FLEXFRG1CTRL_MULT_MASK            (0xFF00U)
#define SYSCON_FLEXFRG1CTRL_MULT_SHIFT           (8U)
/*! MULT - Numerator of the fractional rate divider. */
#define SYSCON_FLEXFRG1CTRL_MULT(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FLEXFRG1CTRL_MULT_SHIFT)) & SYSCON_FLEXFRG1CTRL_MULT_MASK)
/*! @} */

/*! @name FLEXFRG2CTRL - Fractional rate divider for flexcomm 2 */
/*! @{ */

#define SYSCON_FLEXFRG2CTRL_DIV_MASK             (0xFFU)
#define SYSCON_FLEXFRG2CTRL_DIV_SHIFT            (0U)
/*! DIV - Denominator of the fractional rate divider. */
#define SYSCON_FLEXFRG2CTRL_DIV(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FLEXFRG2CTRL_DIV_SHIFT)) & SYSCON_FLEXFRG2CTRL_DIV_MASK)

#define SYSCON_FLEXFRG2CTRL_MULT_MASK            (0xFF00U)
#define SYSCON_FLEXFRG2CTRL_MULT_SHIFT           (8U)
/*! MULT - Numerator of the fractional rate divider. */
#define SYSCON_FLEXFRG2CTRL_MULT(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FLEXFRG2CTRL_MULT_SHIFT)) & SYSCON_FLEXFRG2CTRL_MULT_MASK)
/*! @} */

/*! @name FLEXFRG3CTRL - Fractional rate divider for flexcomm 3 */
/*! @{ */

#define SYSCON_FLEXFRG3CTRL_DIV_MASK             (0xFFU)
#define SYSCON_FLEXFRG3CTRL_DIV_SHIFT            (0U)
/*! DIV - Denominator of the fractional rate divider. */
#define SYSCON_FLEXFRG3CTRL_DIV(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FLEXFRG3CTRL_DIV_SHIFT)) & SYSCON_FLEXFRG3CTRL_DIV_MASK)

#define SYSCON_FLEXFRG3CTRL_MULT_MASK            (0xFF00U)
#define SYSCON_FLEXFRG3CTRL_MULT_SHIFT           (8U)
/*! MULT - Numerator of the fractional rate divider. */
#define SYSCON_FLEXFRG3CTRL_MULT(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FLEXFRG3CTRL_MULT_SHIFT)) & SYSCON_FLEXFRG3CTRL_MULT_MASK)
/*! @} */

/*! @name FLEXFRG4CTRL - Fractional rate divider for flexcomm 4 */
/*! @{ */

#define SYSCON_FLEXFRG4CTRL_DIV_MASK             (0xFFU)
#define SYSCON_FLEXFRG4CTRL_DIV_SHIFT            (0U)
/*! DIV - Denominator of the fractional rate divider. */
#define SYSCON_FLEXFRG4CTRL_DIV(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FLEXFRG4CTRL_DIV_SHIFT)) & SYSCON_FLEXFRG4CTRL_DIV_MASK)

#define SYSCON_FLEXFRG4CTRL_MULT_MASK            (0xFF00U)
#define SYSCON_FLEXFRG4CTRL_MULT_SHIFT           (8U)
/*! MULT - Numerator of the fractional rate divider. */
#define SYSCON_FLEXFRG4CTRL_MULT(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FLEXFRG4CTRL_MULT_SHIFT)) & SYSCON_FLEXFRG4CTRL_MULT_MASK)
/*! @} */

/*! @name FLEXFRG5CTRL - Fractional rate divider for flexcomm 5 */
/*! @{ */

#define SYSCON_FLEXFRG5CTRL_DIV_MASK             (0xFFU)
#define SYSCON_FLEXFRG5CTRL_DIV_SHIFT            (0U)
/*! DIV - Denominator of the fractional rate divider. */
#define SYSCON_FLEXFRG5CTRL_DIV(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FLEXFRG5CTRL_DIV_SHIFT)) & SYSCON_FLEXFRG5CTRL_DIV_MASK)

#define SYSCON_FLEXFRG5CTRL_MULT_MASK            (0xFF00U)
#define SYSCON_FLEXFRG5CTRL_MULT_SHIFT           (8U)
/*! MULT - Numerator of the fractional rate divider. */
#define SYSCON_FLEXFRG5CTRL_MULT(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FLEXFRG5CTRL_MULT_SHIFT)) & SYSCON_FLEXFRG5CTRL_MULT_MASK)
/*! @} */

/*! @name FLEXFRG6CTRL - Fractional rate divider for flexcomm 6 */
/*! @{ */

#define SYSCON_FLEXFRG6CTRL_DIV_MASK             (0xFFU)
#define SYSCON_FLEXFRG6CTRL_DIV_SHIFT            (0U)
/*! DIV - Denominator of the fractional rate divider. */
#define SYSCON_FLEXFRG6CTRL_DIV(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FLEXFRG6CTRL_DIV_SHIFT)) & SYSCON_FLEXFRG6CTRL_DIV_MASK)

#define SYSCON_FLEXFRG6CTRL_MULT_MASK            (0xFF00U)
#define SYSCON_FLEXFRG6CTRL_MULT_SHIFT           (8U)
/*! MULT - Numerator of the fractional rate divider. */
#define SYSCON_FLEXFRG6CTRL_MULT(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FLEXFRG6CTRL_MULT_SHIFT)) & SYSCON_FLEXFRG6CTRL_MULT_MASK)
/*! @} */

/*! @name FLEXFRG7CTRL - Fractional rate divider for flexcomm 7 */
/*! @{ */

#define SYSCON_FLEXFRG7CTRL_DIV_MASK             (0xFFU)
#define SYSCON_FLEXFRG7CTRL_DIV_SHIFT            (0U)
/*! DIV - Denominator of the fractional rate divider. */
#define SYSCON_FLEXFRG7CTRL_DIV(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FLEXFRG7CTRL_DIV_SHIFT)) & SYSCON_FLEXFRG7CTRL_DIV_MASK)

#define SYSCON_FLEXFRG7CTRL_MULT_MASK            (0xFF00U)
#define SYSCON_FLEXFRG7CTRL_MULT_SHIFT           (8U)
/*! MULT - Numerator of the fractional rate divider. */
#define SYSCON_FLEXFRG7CTRL_MULT(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FLEXFRG7CTRL_MULT_SHIFT)) & SYSCON_FLEXFRG7CTRL_MULT_MASK)
/*! @} */

/*! @name FLEXFRGXCTRL - Peripheral reset control register */
/*! @{ */

#define SYSCON_FLEXFRGXCTRL_DATA_MASK            (0xFFFFFFFFU)
#define SYSCON_FLEXFRGXCTRL_DATA_SHIFT           (0U)
/*! DATA - Data array value */
#define SYSCON_FLEXFRGXCTRL_DATA(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FLEXFRGXCTRL_DATA_SHIFT)) & SYSCON_FLEXFRGXCTRL_DATA_MASK)
/*! @} */

/* The count of SYSCON_FLEXFRGXCTRL */
#define SYSCON_FLEXFRGXCTRL_COUNT                (8U)

/*! @name AHBCLKDIV - System clock divider */
/*! @{ */

#define SYSCON_AHBCLKDIV_DIV_MASK                (0xFFU)
#define SYSCON_AHBCLKDIV_DIV_SHIFT               (0U)
/*! DIV - Clock divider value. */
#define SYSCON_AHBCLKDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKDIV_DIV_SHIFT)) & SYSCON_AHBCLKDIV_DIV_MASK)

#define SYSCON_AHBCLKDIV_RESET_MASK              (0x20000000U)
#define SYSCON_AHBCLKDIV_RESET_SHIFT             (29U)
/*! RESET - Resets the divider counter.
 *  0b1..Divider is reset.
 *  0b0..Divider is not reset.
 */
#define SYSCON_AHBCLKDIV_RESET(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKDIV_RESET_SHIFT)) & SYSCON_AHBCLKDIV_RESET_MASK)

#define SYSCON_AHBCLKDIV_HALT_MASK               (0x40000000U)
#define SYSCON_AHBCLKDIV_HALT_SHIFT              (30U)
/*! HALT - Halts the divider counter.
 *  0b1..Divider clock is stoped.
 *  0b0..Divider clock is running.
 */
#define SYSCON_AHBCLKDIV_HALT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKDIV_HALT_SHIFT)) & SYSCON_AHBCLKDIV_HALT_MASK)

#define SYSCON_AHBCLKDIV_REQFLAG_MASK            (0x80000000U)
#define SYSCON_AHBCLKDIV_REQFLAG_SHIFT           (31U)
/*! REQFLAG - Divider status flag.
 *  0b1..Clock frequency is not stable.
 *  0b0..Divider clock is stable.
 */
#define SYSCON_AHBCLKDIV_REQFLAG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKDIV_REQFLAG_SHIFT)) & SYSCON_AHBCLKDIV_REQFLAG_MASK)
/*! @} */

/*! @name CLKOUTDIV - CLKOUT clock divider */
/*! @{ */

#define SYSCON_CLKOUTDIV_DIV_MASK                (0xFFU)
#define SYSCON_CLKOUTDIV_DIV_SHIFT               (0U)
/*! DIV - Clock divider value. */
#define SYSCON_CLKOUTDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_CLKOUTDIV_DIV_SHIFT)) & SYSCON_CLKOUTDIV_DIV_MASK)

#define SYSCON_CLKOUTDIV_RESET_MASK              (0x20000000U)
#define SYSCON_CLKOUTDIV_RESET_SHIFT             (29U)
/*! RESET - Resets the divider counter.
 *  0b1..Divider is reset.
 *  0b0..Divider is not reset.
 */
#define SYSCON_CLKOUTDIV_RESET(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_CLKOUTDIV_RESET_SHIFT)) & SYSCON_CLKOUTDIV_RESET_MASK)

#define SYSCON_CLKOUTDIV_HALT_MASK               (0x40000000U)
#define SYSCON_CLKOUTDIV_HALT_SHIFT              (30U)
/*! HALT - Halts the divider counter.
 *  0b1..Divider clock is stoped.
 *  0b0..Divider clock is running.
 */
#define SYSCON_CLKOUTDIV_HALT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_CLKOUTDIV_HALT_SHIFT)) & SYSCON_CLKOUTDIV_HALT_MASK)

#define SYSCON_CLKOUTDIV_REQFLAG_MASK            (0x80000000U)
#define SYSCON_CLKOUTDIV_REQFLAG_SHIFT           (31U)
/*! REQFLAG - Divider status flag.
 *  0b1..Clock frequency is not stable.
 *  0b0..Divider clock is stable.
 */
#define SYSCON_CLKOUTDIV_REQFLAG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_CLKOUTDIV_REQFLAG_SHIFT)) & SYSCON_CLKOUTDIV_REQFLAG_MASK)
/*! @} */

/*! @name FROHFDIV - FRO_HF (96MHz) clock divider */
/*! @{ */

#define SYSCON_FROHFDIV_DIV_MASK                 (0xFFU)
#define SYSCON_FROHFDIV_DIV_SHIFT                (0U)
/*! DIV - Clock divider value. */
#define SYSCON_FROHFDIV_DIV(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_FROHFDIV_DIV_SHIFT)) & SYSCON_FROHFDIV_DIV_MASK)

#define SYSCON_FROHFDIV_RESET_MASK               (0x20000000U)
#define SYSCON_FROHFDIV_RESET_SHIFT              (29U)
/*! RESET - Resets the divider counter.
 *  0b1..Divider is reset.
 *  0b0..Divider is not reset.
 */
#define SYSCON_FROHFDIV_RESET(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_FROHFDIV_RESET_SHIFT)) & SYSCON_FROHFDIV_RESET_MASK)

#define SYSCON_FROHFDIV_HALT_MASK                (0x40000000U)
#define SYSCON_FROHFDIV_HALT_SHIFT               (30U)
/*! HALT - Halts the divider counter.
 *  0b1..Divider clock is stoped.
 *  0b0..Divider clock is running.
 */
#define SYSCON_FROHFDIV_HALT(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_FROHFDIV_HALT_SHIFT)) & SYSCON_FROHFDIV_HALT_MASK)

#define SYSCON_FROHFDIV_REQFLAG_MASK             (0x80000000U)
#define SYSCON_FROHFDIV_REQFLAG_SHIFT            (31U)
/*! REQFLAG - Divider status flag.
 *  0b1..Clock frequency is not stable.
 *  0b0..Divider clock is stable.
 */
#define SYSCON_FROHFDIV_REQFLAG(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FROHFDIV_REQFLAG_SHIFT)) & SYSCON_FROHFDIV_REQFLAG_MASK)
/*! @} */

/*! @name WDTCLKDIV - WDT clock divider */
/*! @{ */

#define SYSCON_WDTCLKDIV_DIV_MASK                (0x3FU)
#define SYSCON_WDTCLKDIV_DIV_SHIFT               (0U)
/*! DIV - Clock divider value. */
#define SYSCON_WDTCLKDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_WDTCLKDIV_DIV_SHIFT)) & SYSCON_WDTCLKDIV_DIV_MASK)

#define SYSCON_WDTCLKDIV_RESET_MASK              (0x20000000U)
#define SYSCON_WDTCLKDIV_RESET_SHIFT             (29U)
/*! RESET - Resets the divider counter.
 *  0b1..Divider is reset.
 *  0b0..Divider is not reset.
 */
#define SYSCON_WDTCLKDIV_RESET(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_WDTCLKDIV_RESET_SHIFT)) & SYSCON_WDTCLKDIV_RESET_MASK)

#define SYSCON_WDTCLKDIV_HALT_MASK               (0x40000000U)
#define SYSCON_WDTCLKDIV_HALT_SHIFT              (30U)
/*! HALT - Halts the divider counter.
 *  0b1..Divider clock is stoped.
 *  0b0..Divider clock is running.
 */
#define SYSCON_WDTCLKDIV_HALT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_WDTCLKDIV_HALT_SHIFT)) & SYSCON_WDTCLKDIV_HALT_MASK)

#define SYSCON_WDTCLKDIV_REQFLAG_MASK            (0x80000000U)
#define SYSCON_WDTCLKDIV_REQFLAG_SHIFT           (31U)
/*! REQFLAG - Divider status flag.
 *  0b1..Clock frequency is not stable.
 *  0b0..Divider clock is stable.
 */
#define SYSCON_WDTCLKDIV_REQFLAG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_WDTCLKDIV_REQFLAG_SHIFT)) & SYSCON_WDTCLKDIV_REQFLAG_MASK)
/*! @} */

/*! @name ADCCLKDIV - ADC clock divider */
/*! @{ */

#define SYSCON_ADCCLKDIV_DIV_MASK                (0x7U)
#define SYSCON_ADCCLKDIV_DIV_SHIFT               (0U)
/*! DIV - Clock divider value. */
#define SYSCON_ADCCLKDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_ADCCLKDIV_DIV_SHIFT)) & SYSCON_ADCCLKDIV_DIV_MASK)

#define SYSCON_ADCCLKDIV_RESET_MASK              (0x20000000U)
#define SYSCON_ADCCLKDIV_RESET_SHIFT             (29U)
/*! RESET - Resets the divider counter.
 *  0b1..Divider is reset.
 *  0b0..Divider is not reset.
 */
#define SYSCON_ADCCLKDIV_RESET(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_ADCCLKDIV_RESET_SHIFT)) & SYSCON_ADCCLKDIV_RESET_MASK)

#define SYSCON_ADCCLKDIV_HALT_MASK               (0x40000000U)
#define SYSCON_ADCCLKDIV_HALT_SHIFT              (30U)
/*! HALT - Halts the divider counter.
 *  0b1..Divider clock is stoped.
 *  0b0..Divider clock is running.
 */
#define SYSCON_ADCCLKDIV_HALT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_ADCCLKDIV_HALT_SHIFT)) & SYSCON_ADCCLKDIV_HALT_MASK)

#define SYSCON_ADCCLKDIV_REQFLAG_MASK            (0x80000000U)
#define SYSCON_ADCCLKDIV_REQFLAG_SHIFT           (31U)
/*! REQFLAG - Divider status flag.
 *  0b1..Clock frequency is not stable.
 *  0b0..Divider clock is stable.
 */
#define SYSCON_ADCCLKDIV_REQFLAG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_ADCCLKDIV_REQFLAG_SHIFT)) & SYSCON_ADCCLKDIV_REQFLAG_MASK)
/*! @} */

/*! @name USB0CLKDIV - USB0-FS Clock divider */
/*! @{ */

#define SYSCON_USB0CLKDIV_DIV_MASK               (0xFFU)
#define SYSCON_USB0CLKDIV_DIV_SHIFT              (0U)
/*! DIV - Clock divider value. */
#define SYSCON_USB0CLKDIV_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0CLKDIV_DIV_SHIFT)) & SYSCON_USB0CLKDIV_DIV_MASK)

#define SYSCON_USB0CLKDIV_RESET_MASK             (0x20000000U)
#define SYSCON_USB0CLKDIV_RESET_SHIFT            (29U)
/*! RESET - Resets the divider counter.
 *  0b1..Divider is reset.
 *  0b0..Divider is not reset.
 */
#define SYSCON_USB0CLKDIV_RESET(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0CLKDIV_RESET_SHIFT)) & SYSCON_USB0CLKDIV_RESET_MASK)

#define SYSCON_USB0CLKDIV_HALT_MASK              (0x40000000U)
#define SYSCON_USB0CLKDIV_HALT_SHIFT             (30U)
/*! HALT - Halts the divider counter.
 *  0b1..Divider clock is stoped.
 *  0b0..Divider clock is running.
 */
#define SYSCON_USB0CLKDIV_HALT(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0CLKDIV_HALT_SHIFT)) & SYSCON_USB0CLKDIV_HALT_MASK)

#define SYSCON_USB0CLKDIV_REQFLAG_MASK           (0x80000000U)
#define SYSCON_USB0CLKDIV_REQFLAG_SHIFT          (31U)
/*! REQFLAG - Divider status flag.
 *  0b1..Clock frequency is not stable.
 *  0b0..Divider clock is stable.
 */
#define SYSCON_USB0CLKDIV_REQFLAG(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0CLKDIV_REQFLAG_SHIFT)) & SYSCON_USB0CLKDIV_REQFLAG_MASK)
/*! @} */

/*! @name FRO1MCLKDIV - FRO1MHz Clock divider (FRO1M_divided) */
/*! @{ */

#define SYSCON_FRO1MCLKDIV_DIV_MASK              (0xFFU)
#define SYSCON_FRO1MCLKDIV_DIV_SHIFT             (0U)
/*! DIV - Clock divider value. */
#define SYSCON_FRO1MCLKDIV_DIV(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_FRO1MCLKDIV_DIV_SHIFT)) & SYSCON_FRO1MCLKDIV_DIV_MASK)

#define SYSCON_FRO1MCLKDIV_RESET_MASK            (0x20000000U)
#define SYSCON_FRO1MCLKDIV_RESET_SHIFT           (29U)
/*! RESET - Resets the divider counter.
 *  0b1..Divider is reset.
 *  0b0..Divider is not reset.
 */
#define SYSCON_FRO1MCLKDIV_RESET(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FRO1MCLKDIV_RESET_SHIFT)) & SYSCON_FRO1MCLKDIV_RESET_MASK)

#define SYSCON_FRO1MCLKDIV_HALT_MASK             (0x40000000U)
#define SYSCON_FRO1MCLKDIV_HALT_SHIFT            (30U)
/*! HALT - Halts the divider counter.
 *  0b1..Divider clock is stoped.
 *  0b0..Divider clock is running.
 */
#define SYSCON_FRO1MCLKDIV_HALT(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FRO1MCLKDIV_HALT_SHIFT)) & SYSCON_FRO1MCLKDIV_HALT_MASK)

#define SYSCON_FRO1MCLKDIV_REQFLAG_MASK          (0x80000000U)
#define SYSCON_FRO1MCLKDIV_REQFLAG_SHIFT         (31U)
/*! REQFLAG - Divider status flag.
 *  0b1..Clock frequency is not stable.
 *  0b0..Divider clock is stable.
 */
#define SYSCON_FRO1MCLKDIV_REQFLAG(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_FRO1MCLKDIV_REQFLAG_SHIFT)) & SYSCON_FRO1MCLKDIV_REQFLAG_MASK)
/*! @} */

/*! @name MCLKDIV - I2S MCLK clock divider */
/*! @{ */

#define SYSCON_MCLKDIV_DIV_MASK                  (0xFFU)
#define SYSCON_MCLKDIV_DIV_SHIFT                 (0U)
/*! DIV - Clock divider value. */
#define SYSCON_MCLKDIV_DIV(x)                    (((uint32_t)(((uint32_t)(x)) << SYSCON_MCLKDIV_DIV_SHIFT)) & SYSCON_MCLKDIV_DIV_MASK)

#define SYSCON_MCLKDIV_RESET_MASK                (0x20000000U)
#define SYSCON_MCLKDIV_RESET_SHIFT               (29U)
/*! RESET - Resets the divider counter.
 *  0b1..Divider is reset.
 *  0b0..Divider is not reset.
 */
#define SYSCON_MCLKDIV_RESET(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_MCLKDIV_RESET_SHIFT)) & SYSCON_MCLKDIV_RESET_MASK)

#define SYSCON_MCLKDIV_HALT_MASK                 (0x40000000U)
#define SYSCON_MCLKDIV_HALT_SHIFT                (30U)
/*! HALT - Halts the divider counter.
 *  0b1..Divider clock is stoped.
 *  0b0..Divider clock is running.
 */
#define SYSCON_MCLKDIV_HALT(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_MCLKDIV_HALT_SHIFT)) & SYSCON_MCLKDIV_HALT_MASK)

#define SYSCON_MCLKDIV_REQFLAG_MASK              (0x80000000U)
#define SYSCON_MCLKDIV_REQFLAG_SHIFT             (31U)
/*! REQFLAG - Divider status flag.
 *  0b1..Clock frequency is not stable.
 *  0b0..Divider clock is stable.
 */
#define SYSCON_MCLKDIV_REQFLAG(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_MCLKDIV_REQFLAG_SHIFT)) & SYSCON_MCLKDIV_REQFLAG_MASK)
/*! @} */

/*! @name SCTCLKDIV - SCT/PWM clock divider */
/*! @{ */

#define SYSCON_SCTCLKDIV_DIV_MASK                (0xFFU)
#define SYSCON_SCTCLKDIV_DIV_SHIFT               (0U)
/*! DIV - Clock divider value. */
#define SYSCON_SCTCLKDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_SCTCLKDIV_DIV_SHIFT)) & SYSCON_SCTCLKDIV_DIV_MASK)

#define SYSCON_SCTCLKDIV_RESET_MASK              (0x20000000U)
#define SYSCON_SCTCLKDIV_RESET_SHIFT             (29U)
/*! RESET - Resets the divider counter.
 *  0b1..Divider is reset.
 *  0b0..Divider is not reset.
 */
#define SYSCON_SCTCLKDIV_RESET(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SCTCLKDIV_RESET_SHIFT)) & SYSCON_SCTCLKDIV_RESET_MASK)

#define SYSCON_SCTCLKDIV_HALT_MASK               (0x40000000U)
#define SYSCON_SCTCLKDIV_HALT_SHIFT              (30U)
/*! HALT - Halts the divider counter.
 *  0b1..Divider clock is stoped.
 *  0b0..Divider clock is running.
 */
#define SYSCON_SCTCLKDIV_HALT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_SCTCLKDIV_HALT_SHIFT)) & SYSCON_SCTCLKDIV_HALT_MASK)

#define SYSCON_SCTCLKDIV_REQFLAG_MASK            (0x80000000U)
#define SYSCON_SCTCLKDIV_REQFLAG_SHIFT           (31U)
/*! REQFLAG - Divider status flag.
 *  0b1..Clock frequency is not stable.
 *  0b0..Divider clock is stable.
 */
#define SYSCON_SCTCLKDIV_REQFLAG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_SCTCLKDIV_REQFLAG_SHIFT)) & SYSCON_SCTCLKDIV_REQFLAG_MASK)
/*! @} */

/*! @name PLL0CLKDIV - PLL0 clock divider */
/*! @{ */

#define SYSCON_PLL0CLKDIV_DIV_MASK               (0xFFU)
#define SYSCON_PLL0CLKDIV_DIV_SHIFT              (0U)
/*! DIV - Clock divider value. */
#define SYSCON_PLL0CLKDIV_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CLKDIV_DIV_SHIFT)) & SYSCON_PLL0CLKDIV_DIV_MASK)

#define SYSCON_PLL0CLKDIV_RESET_MASK             (0x20000000U)
#define SYSCON_PLL0CLKDIV_RESET_SHIFT            (29U)
/*! RESET - Resets the divider counter.
 *  0b1..Divider is reset.
 *  0b0..Divider is not reset.
 */
#define SYSCON_PLL0CLKDIV_RESET(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CLKDIV_RESET_SHIFT)) & SYSCON_PLL0CLKDIV_RESET_MASK)

#define SYSCON_PLL0CLKDIV_HALT_MASK              (0x40000000U)
#define SYSCON_PLL0CLKDIV_HALT_SHIFT             (30U)
/*! HALT - Halts the divider counter.
 *  0b1..Divider clock is stoped.
 *  0b0..Divider clock is running.
 */
#define SYSCON_PLL0CLKDIV_HALT(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CLKDIV_HALT_SHIFT)) & SYSCON_PLL0CLKDIV_HALT_MASK)

#define SYSCON_PLL0CLKDIV_REQFLAG_MASK           (0x80000000U)
#define SYSCON_PLL0CLKDIV_REQFLAG_SHIFT          (31U)
/*! REQFLAG - Divider status flag.
 *  0b1..Clock frequency is not stable.
 *  0b0..Divider clock is stable.
 */
#define SYSCON_PLL0CLKDIV_REQFLAG(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CLKDIV_REQFLAG_SHIFT)) & SYSCON_PLL0CLKDIV_REQFLAG_MASK)
/*! @} */

/*! @name CLOCKGENUPDATELOCKOUT - Control clock configuration registers access (like xxxDIV, xxxSEL) */
/*! @{ */

#define SYSCON_CLOCKGENUPDATELOCKOUT_CLOCKGENUPDATELOCKOUT_MASK (0xFFFFFFFFU)
#define SYSCON_CLOCKGENUPDATELOCKOUT_CLOCKGENUPDATELOCKOUT_SHIFT (0U)
/*! CLOCKGENUPDATELOCKOUT - Control clock configuration registers access (for example, xxxDIV, xxxSEL).
 *  0b00000000000000000000000000000001..update all clock configuration.
 *  0b00000000000000000000000000000000..all hardware clock configruration are freeze.
 */
#define SYSCON_CLOCKGENUPDATELOCKOUT_CLOCKGENUPDATELOCKOUT(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_CLOCKGENUPDATELOCKOUT_CLOCKGENUPDATELOCKOUT_SHIFT)) & SYSCON_CLOCKGENUPDATELOCKOUT_CLOCKGENUPDATELOCKOUT_MASK)
/*! @} */

/*! @name FMCCR - FMC configuration register */
/*! @{ */

#define SYSCON_FMCCR_FETCHCFG_MASK               (0x3U)
#define SYSCON_FMCCR_FETCHCFG_SHIFT              (0U)
/*! FETCHCFG - Instruction fetch configuration.
 *  0b00..Instruction fetches from flash are not buffered.
 *  0b01..One buffer is used for all instruction fetches.
 *  0b10..All buffers may be used for instruction fetches.
 */
#define SYSCON_FMCCR_FETCHCFG(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_FMCCR_FETCHCFG_SHIFT)) & SYSCON_FMCCR_FETCHCFG_MASK)

#define SYSCON_FMCCR_DATACFG_MASK                (0xCU)
#define SYSCON_FMCCR_DATACFG_SHIFT               (2U)
/*! DATACFG - Data read configuration.
 *  0b00..Data accesses from flash are not buffered.
 *  0b01..One buffer is used for all data accesses.
 *  0b10..All buffers can be used for data accesses.
 */
#define SYSCON_FMCCR_DATACFG(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_FMCCR_DATACFG_SHIFT)) & SYSCON_FMCCR_DATACFG_MASK)

#define SYSCON_FMCCR_ACCEL_MASK                  (0x10U)
#define SYSCON_FMCCR_ACCEL_SHIFT                 (4U)
/*! ACCEL - Acceleration enable.
 *  0b0..Flash acceleration is disabled.
 *  0b1..Flash acceleration is enabled.
 */
#define SYSCON_FMCCR_ACCEL(x)                    (((uint32_t)(((uint32_t)(x)) << SYSCON_FMCCR_ACCEL_SHIFT)) & SYSCON_FMCCR_ACCEL_MASK)

#define SYSCON_FMCCR_PREFEN_MASK                 (0x20U)
#define SYSCON_FMCCR_PREFEN_SHIFT                (5U)
/*! PREFEN - Prefetch enable.
 *  0b0..No instruction prefetch is performed.
 *  0b1..Instruction prefetch is enabled.
 */
#define SYSCON_FMCCR_PREFEN(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_FMCCR_PREFEN_SHIFT)) & SYSCON_FMCCR_PREFEN_MASK)

#define SYSCON_FMCCR_PREFOVR_MASK                (0x40U)
#define SYSCON_FMCCR_PREFOVR_SHIFT               (6U)
/*! PREFOVR - Prefetch override.
 *  0b0..Any previously initiated prefetch will be completed.
 *  0b1..Any previously initiated prefetch will be aborted, and the next flash line following the current
 *       execution address will be prefetched if not already buffered.
 */
#define SYSCON_FMCCR_PREFOVR(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_FMCCR_PREFOVR_SHIFT)) & SYSCON_FMCCR_PREFOVR_MASK)

#define SYSCON_FMCCR_FLASHTIM_MASK               (0xF000U)
#define SYSCON_FMCCR_FLASHTIM_SHIFT              (12U)
/*! FLASHTIM - Flash memory access time.
 *  0b0000..1 system clock flash access time (for system clock rates up to 11 MHz).
 *  0b0001..2 system clocks flash access time (for system clock rates up to 22 MHz).
 *  0b0010..3 system clocks flash access time (for system clock rates up to 33 MHz).
 *  0b0011..4 system clocks flash access time (for system clock rates up to 44 MHz).
 *  0b0100..5 system clocks flash access time (for system clock rates up to 55 MHz).
 *  0b0101..6 system clocks flash access time (for system clock rates up to 66 MHz).
 *  0b0110..7 system clocks flash access time (for system clock rates up to 84 MHz).
 *  0b0111..8 system clocks flash access time (for system clock rates up to 104 MHz).
 *  0b1000..9 system clocks flash access time (for system clock rates up to 119 MHz).
 *  0b1001..10 system clocks flash access time (for system clock rates up to 129 MHz).
 *  0b1010..11 system clocks flash access time (for system clock rates up to 144 MHz).
 *  0b1011..12 system clocks flash access time (for system clock rates up to 150 MHz).
 */
#define SYSCON_FMCCR_FLASHTIM(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_FMCCR_FLASHTIM_SHIFT)) & SYSCON_FMCCR_FLASHTIM_MASK)
/*! @} */

/*! @name USB0NEEDCLKCTRL - USB0-FS need clock control */
/*! @{ */

#define SYSCON_USB0NEEDCLKCTRL_AP_FS_DEV_NEEDCLK_MASK (0x1U)
#define SYSCON_USB0NEEDCLKCTRL_AP_FS_DEV_NEEDCLK_SHIFT (0U)
/*! AP_FS_DEV_NEEDCLK - USB0-FS Device USB0_NEEDCLK signal control:.
 *  0b0..Under hardware control.
 *  0b1..Forced high.
 */
#define SYSCON_USB0NEEDCLKCTRL_AP_FS_DEV_NEEDCLK(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0NEEDCLKCTRL_AP_FS_DEV_NEEDCLK_SHIFT)) & SYSCON_USB0NEEDCLKCTRL_AP_FS_DEV_NEEDCLK_MASK)

#define SYSCON_USB0NEEDCLKCTRL_POL_FS_DEV_NEEDCLK_MASK (0x2U)
#define SYSCON_USB0NEEDCLKCTRL_POL_FS_DEV_NEEDCLK_SHIFT (1U)
/*! POL_FS_DEV_NEEDCLK - USB0-FS Device USB0_NEEDCLK polarity for triggering the USB0-FS wake-up interrupt:.
 *  0b0..Falling edge of device USB0_NEEDCLK triggers wake-up.
 *  0b1..Rising edge of device USB0_NEEDCLK triggers wake-up.
 */
#define SYSCON_USB0NEEDCLKCTRL_POL_FS_DEV_NEEDCLK(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0NEEDCLKCTRL_POL_FS_DEV_NEEDCLK_SHIFT)) & SYSCON_USB0NEEDCLKCTRL_POL_FS_DEV_NEEDCLK_MASK)

#define SYSCON_USB0NEEDCLKCTRL_AP_FS_HOST_NEEDCLK_MASK (0x4U)
#define SYSCON_USB0NEEDCLKCTRL_AP_FS_HOST_NEEDCLK_SHIFT (2U)
/*! AP_FS_HOST_NEEDCLK - USB0-FS Host USB0_NEEDCLK signal control:.
 *  0b0..Under hardware control.
 *  0b1..Forced high.
 */
#define SYSCON_USB0NEEDCLKCTRL_AP_FS_HOST_NEEDCLK(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0NEEDCLKCTRL_AP_FS_HOST_NEEDCLK_SHIFT)) & SYSCON_USB0NEEDCLKCTRL_AP_FS_HOST_NEEDCLK_MASK)

#define SYSCON_USB0NEEDCLKCTRL_POL_FS_HOST_NEEDCLK_MASK (0x8U)
#define SYSCON_USB0NEEDCLKCTRL_POL_FS_HOST_NEEDCLK_SHIFT (3U)
/*! POL_FS_HOST_NEEDCLK - USB0-FS Host USB0_NEEDCLK polarity for triggering the USB0-FS wake-up interrupt:.
 *  0b0..Falling edge of device USB0_NEEDCLK triggers wake-up.
 *  0b1..Rising edge of device USB0_NEEDCLK triggers wake-up.
 */
#define SYSCON_USB0NEEDCLKCTRL_POL_FS_HOST_NEEDCLK(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0NEEDCLKCTRL_POL_FS_HOST_NEEDCLK_SHIFT)) & SYSCON_USB0NEEDCLKCTRL_POL_FS_HOST_NEEDCLK_MASK)
/*! @} */

/*! @name USB0NEEDCLKSTAT - USB0-FS need clock status */
/*! @{ */

#define SYSCON_USB0NEEDCLKSTAT_DEV_NEEDCLK_MASK  (0x1U)
#define SYSCON_USB0NEEDCLKSTAT_DEV_NEEDCLK_SHIFT (0U)
/*! DEV_NEEDCLK - USB0-FS Device USB0_NEEDCLK signal status:.
 *  0b1..USB0-FS Device clock is high.
 *  0b0..USB0-FS Device clock is low.
 */
#define SYSCON_USB0NEEDCLKSTAT_DEV_NEEDCLK(x)    (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0NEEDCLKSTAT_DEV_NEEDCLK_SHIFT)) & SYSCON_USB0NEEDCLKSTAT_DEV_NEEDCLK_MASK)

#define SYSCON_USB0NEEDCLKSTAT_HOST_NEEDCLK_MASK (0x2U)
#define SYSCON_USB0NEEDCLKSTAT_HOST_NEEDCLK_SHIFT (1U)
/*! HOST_NEEDCLK - USB0-FS Host USB0_NEEDCLK signal status:.
 *  0b1..USB0-FS Host clock is high.
 *  0b0..USB0-FS Host clock is low.
 */
#define SYSCON_USB0NEEDCLKSTAT_HOST_NEEDCLK(x)   (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0NEEDCLKSTAT_HOST_NEEDCLK_SHIFT)) & SYSCON_USB0NEEDCLKSTAT_HOST_NEEDCLK_MASK)
/*! @} */

/*! @name FMCFLUSH - FMCflush control */
/*! @{ */

#define SYSCON_FMCFLUSH_FLUSH_MASK               (0x1U)
#define SYSCON_FMCFLUSH_FLUSH_SHIFT              (0U)
/*! FLUSH - Flush control
 *  0b1..Flush the FMC buffer contents.
 *  0b0..No action is performed.
 */
#define SYSCON_FMCFLUSH_FLUSH(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_FMCFLUSH_FLUSH_SHIFT)) & SYSCON_FMCFLUSH_FLUSH_MASK)
/*! @} */

/*! @name MCLKIO - MCLK control */
/*! @{ */

#define SYSCON_MCLKIO_MCLKIO_MASK                (0x1U)
#define SYSCON_MCLKIO_MCLKIO_SHIFT               (0U)
/*! MCLKIO - MCLK control.
 *  0b0..input mode.
 *  0b1..output mode.
 */
#define SYSCON_MCLKIO_MCLKIO(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_MCLKIO_MCLKIO_SHIFT)) & SYSCON_MCLKIO_MCLKIO_MASK)
/*! @} */

/*! @name USB1NEEDCLKCTRL - USB1-HS need clock control */
/*! @{ */

#define SYSCON_USB1NEEDCLKCTRL_AP_HS_DEV_NEEDCLK_MASK (0x1U)
#define SYSCON_USB1NEEDCLKCTRL_AP_HS_DEV_NEEDCLK_SHIFT (0U)
/*! AP_HS_DEV_NEEDCLK - USB1-HS Device need_clock signal control:
 *  0b0..HOST_NEEDCLK is under hardware control.
 *  0b1..HOST_NEEDCLK is forced high.
 */
#define SYSCON_USB1NEEDCLKCTRL_AP_HS_DEV_NEEDCLK(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1NEEDCLKCTRL_AP_HS_DEV_NEEDCLK_SHIFT)) & SYSCON_USB1NEEDCLKCTRL_AP_HS_DEV_NEEDCLK_MASK)

#define SYSCON_USB1NEEDCLKCTRL_POL_HS_DEV_NEEDCLK_MASK (0x2U)
#define SYSCON_USB1NEEDCLKCTRL_POL_HS_DEV_NEEDCLK_SHIFT (1U)
/*! POL_HS_DEV_NEEDCLK - USB1-HS device need clock polarity for triggering the USB1_NEEDCLK wake-up interrupt:
 *  0b0..Falling edge of DEV_NEEDCLK triggers wake-up.
 *  0b1..Rising edge of DEV_NEEDCLK triggers wake-up.
 */
#define SYSCON_USB1NEEDCLKCTRL_POL_HS_DEV_NEEDCLK(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1NEEDCLKCTRL_POL_HS_DEV_NEEDCLK_SHIFT)) & SYSCON_USB1NEEDCLKCTRL_POL_HS_DEV_NEEDCLK_MASK)

#define SYSCON_USB1NEEDCLKCTRL_AP_HS_HOST_NEEDCLK_MASK (0x4U)
#define SYSCON_USB1NEEDCLKCTRL_AP_HS_HOST_NEEDCLK_SHIFT (2U)
/*! AP_HS_HOST_NEEDCLK - USB1-HS Host need clock signal control:
 *  0b0..HOST_NEEDCLK is under hardware control.
 *  0b1..HOST_NEEDCLK is forced high.
 */
#define SYSCON_USB1NEEDCLKCTRL_AP_HS_HOST_NEEDCLK(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1NEEDCLKCTRL_AP_HS_HOST_NEEDCLK_SHIFT)) & SYSCON_USB1NEEDCLKCTRL_AP_HS_HOST_NEEDCLK_MASK)

#define SYSCON_USB1NEEDCLKCTRL_POL_HS_HOST_NEEDCLK_MASK (0x8U)
#define SYSCON_USB1NEEDCLKCTRL_POL_HS_HOST_NEEDCLK_SHIFT (3U)
/*! POL_HS_HOST_NEEDCLK - USB1-HS host need clock polarity for triggering the USB1_NEEDCLK wake-up interrupt.
 *  0b0..Falling edge of HOST_NEEDCLK triggers wake-up.
 *  0b1..Rising edge of HOST_NEEDCLK triggers wake-up.
 */
#define SYSCON_USB1NEEDCLKCTRL_POL_HS_HOST_NEEDCLK(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1NEEDCLKCTRL_POL_HS_HOST_NEEDCLK_SHIFT)) & SYSCON_USB1NEEDCLKCTRL_POL_HS_HOST_NEEDCLK_MASK)

#define SYSCON_USB1NEEDCLKCTRL_HS_DEV_WAKEUP_N_MASK (0x10U)
#define SYSCON_USB1NEEDCLKCTRL_HS_DEV_WAKEUP_N_SHIFT (4U)
/*! HS_DEV_WAKEUP_N - Software override of device controller PHY wake up logic.
 *  0b0..Forces USB1_PHY to wake-up.
 *  0b1..Normal USB1_PHY behavior.
 */
#define SYSCON_USB1NEEDCLKCTRL_HS_DEV_WAKEUP_N(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1NEEDCLKCTRL_HS_DEV_WAKEUP_N_SHIFT)) & SYSCON_USB1NEEDCLKCTRL_HS_DEV_WAKEUP_N_MASK)
/*! @} */

/*! @name USB1NEEDCLKSTAT - USB1-HS need clock status */
/*! @{ */

#define SYSCON_USB1NEEDCLKSTAT_DEV_NEEDCLK_MASK  (0x1U)
#define SYSCON_USB1NEEDCLKSTAT_DEV_NEEDCLK_SHIFT (0U)
/*! DEV_NEEDCLK - USB1-HS Device need_clock signal status:.
 *  0b1..DEV_NEEDCLK is high.
 *  0b0..DEV_NEEDCLK is low.
 */
#define SYSCON_USB1NEEDCLKSTAT_DEV_NEEDCLK(x)    (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1NEEDCLKSTAT_DEV_NEEDCLK_SHIFT)) & SYSCON_USB1NEEDCLKSTAT_DEV_NEEDCLK_MASK)

#define SYSCON_USB1NEEDCLKSTAT_HOST_NEEDCLK_MASK (0x2U)
#define SYSCON_USB1NEEDCLKSTAT_HOST_NEEDCLK_SHIFT (1U)
/*! HOST_NEEDCLK - USB1-HS Host need_clock signal status:.
 *  0b1..HOST_NEEDCLK is high.
 *  0b0..HOST_NEEDCLK is low.
 */
#define SYSCON_USB1NEEDCLKSTAT_HOST_NEEDCLK(x)   (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1NEEDCLKSTAT_HOST_NEEDCLK_SHIFT)) & SYSCON_USB1NEEDCLKSTAT_HOST_NEEDCLK_MASK)
/*! @} */

/*! @name FLASHREMAP_SIZE - This 32-bit register contains the size of the image to remap, in bytes. The 12 LSBs are ignored, so the size granularity is 4KB. */
/*! @{ */

#define SYSCON_FLASHREMAP_SIZE_FLASHREMAP_SIZE_MASK (0xFFFFFFFFU)
#define SYSCON_FLASHREMAP_SIZE_FLASHREMAP_SIZE_SHIFT (0U)
#define SYSCON_FLASHREMAP_SIZE_FLASHREMAP_SIZE(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHREMAP_SIZE_FLASHREMAP_SIZE_SHIFT)) & SYSCON_FLASHREMAP_SIZE_FLASHREMAP_SIZE_MASK)
/*! @} */

/*! @name FLASHREMAP_SIZE_DP - This 32-bit register is a duplicate of FLASHREMAPSIZE for increased security. */
/*! @{ */

#define SYSCON_FLASHREMAP_SIZE_DP_FLASHREMAP_SIZE_MASK (0xFFFFFFFFU)
#define SYSCON_FLASHREMAP_SIZE_DP_FLASHREMAP_SIZE_SHIFT (0U)
#define SYSCON_FLASHREMAP_SIZE_DP_FLASHREMAP_SIZE(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHREMAP_SIZE_DP_FLASHREMAP_SIZE_SHIFT)) & SYSCON_FLASHREMAP_SIZE_DP_FLASHREMAP_SIZE_MASK)
/*! @} */

/*! @name FLASHREMAP_OFFSET - This 32-bit register contains the offset by which the image is to be remapped. The 12 LSBs are ignored, so the remap granularity is 4KB. */
/*! @{ */

#define SYSCON_FLASHREMAP_OFFSET_FLASHREMAP_OFFSET_MASK (0xFFFFFFFFU)
#define SYSCON_FLASHREMAP_OFFSET_FLASHREMAP_OFFSET_SHIFT (0U)
#define SYSCON_FLASHREMAP_OFFSET_FLASHREMAP_OFFSET(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHREMAP_OFFSET_FLASHREMAP_OFFSET_SHIFT)) & SYSCON_FLASHREMAP_OFFSET_FLASHREMAP_OFFSET_MASK)
/*! @} */

/*! @name FLASHREMAP_OFFSET_DP - This 32-bit register is a duplicate of FLASHREMAPOFFSET for increased security. */
/*! @{ */

#define SYSCON_FLASHREMAP_OFFSET_DP_FLASHREMAP_OFFSET_MASK (0xFFFFFFFFU)
#define SYSCON_FLASHREMAP_OFFSET_DP_FLASHREMAP_OFFSET_SHIFT (0U)
#define SYSCON_FLASHREMAP_OFFSET_DP_FLASHREMAP_OFFSET(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHREMAP_OFFSET_DP_FLASHREMAP_OFFSET_SHIFT)) & SYSCON_FLASHREMAP_OFFSET_DP_FLASHREMAP_OFFSET_MASK)
/*! @} */

/*! @name FLASHREMAP_LOCK - Control write access to FLASHREMAP_SIZE and FLASHREMAP_OFFSET registers. */
/*! @{ */

#define SYSCON_FLASHREMAP_LOCK_LOCK_MASK         (0xFFFFFFFFU)
#define SYSCON_FLASHREMAP_LOCK_LOCK_SHIFT        (0U)
/*! LOCK - Control write access to FLASHREMAP_SIZE and FLASHREMAP_OFFSET registers. Any value other
 *    than 0xC33CA55A and 0x3CC35AA5 does not modify the state.
 *  0b00111100110000110101101010100101..Write access to 4 registers FLASHREMAP_SIZE* and FLASHREMAP_OFFSET* is unlocked.
 *  0b11000011001111001010010101011010..Write access to 4 registers FLASHREMAP_SIZE* and FLASHREMAP_OFFSET* is locked.
 */
#define SYSCON_FLASHREMAP_LOCK_LOCK(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHREMAP_LOCK_LOCK_SHIFT)) & SYSCON_FLASHREMAP_LOCK_LOCK_MASK)
/*! @} */

/*! @name CASPER_CTRL - Control CASPER integration. */
/*! @{ */

#define SYSCON_CASPER_CTRL_INTERLEAVE_MASK       (0x1U)
#define SYSCON_CASPER_CTRL_INTERLEAVE_SHIFT      (0U)
/*! INTERLEAVE - Control RAM access for RAMX0 and RAMX1.
 *  0b1..RAM access to RAMX0 and RAMX1 is interleaved.
 *  0b0..RAM access to RAMX0 and RAMX1 is consecutive.
 */
#define SYSCON_CASPER_CTRL_INTERLEAVE(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_CASPER_CTRL_INTERLEAVE_SHIFT)) & SYSCON_CASPER_CTRL_INTERLEAVE_MASK)
/*! @} */

/*! @name PLL1CTRL - PLL1 550m control */
/*! @{ */

#define SYSCON_PLL1CTRL_SELR_MASK                (0xFU)
#define SYSCON_PLL1CTRL_SELR_SHIFT               (0U)
/*! SELR - Bandwidth select R value. */
#define SYSCON_PLL1CTRL_SELR(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1CTRL_SELR_SHIFT)) & SYSCON_PLL1CTRL_SELR_MASK)

#define SYSCON_PLL1CTRL_SELI_MASK                (0x3F0U)
#define SYSCON_PLL1CTRL_SELI_SHIFT               (4U)
/*! SELI - Bandwidth select I value. */
#define SYSCON_PLL1CTRL_SELI(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1CTRL_SELI_SHIFT)) & SYSCON_PLL1CTRL_SELI_MASK)

#define SYSCON_PLL1CTRL_SELP_MASK                (0x7C00U)
#define SYSCON_PLL1CTRL_SELP_SHIFT               (10U)
/*! SELP - Bandwidth select P value. */
#define SYSCON_PLL1CTRL_SELP(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1CTRL_SELP_SHIFT)) & SYSCON_PLL1CTRL_SELP_MASK)

#define SYSCON_PLL1CTRL_BYPASSPLL_MASK           (0x8000U)
#define SYSCON_PLL1CTRL_BYPASSPLL_SHIFT          (15U)
/*! BYPASSPLL - Bypass PLL input clock is sent directly to the PLL output (default).
 *  0b1..PLL input clock is sent directly to the PLL output.
 *  0b0..use PLL.
 */
#define SYSCON_PLL1CTRL_BYPASSPLL(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1CTRL_BYPASSPLL_SHIFT)) & SYSCON_PLL1CTRL_BYPASSPLL_MASK)

#define SYSCON_PLL1CTRL_BYPASSPOSTDIV2_MASK      (0x10000U)
#define SYSCON_PLL1CTRL_BYPASSPOSTDIV2_SHIFT     (16U)
/*! BYPASSPOSTDIV2 - bypass of the divide-by-2 divider in the post-divider.
 *  0b1..bypass of the divide-by-2 divider in the post-divider.
 *  0b0..use the divide-by-2 divider in the post-divider.
 */
#define SYSCON_PLL1CTRL_BYPASSPOSTDIV2(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1CTRL_BYPASSPOSTDIV2_SHIFT)) & SYSCON_PLL1CTRL_BYPASSPOSTDIV2_MASK)

#define SYSCON_PLL1CTRL_LIMUPOFF_MASK            (0x20000U)
#define SYSCON_PLL1CTRL_LIMUPOFF_SHIFT           (17U)
/*! LIMUPOFF - limup_off = 1 in spread spectrum and fractional PLL applications. */
#define SYSCON_PLL1CTRL_LIMUPOFF(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1CTRL_LIMUPOFF_SHIFT)) & SYSCON_PLL1CTRL_LIMUPOFF_MASK)

#define SYSCON_PLL1CTRL_BWDIRECT_MASK            (0x40000U)
#define SYSCON_PLL1CTRL_BWDIRECT_SHIFT           (18U)
/*! BWDIRECT - control of the bandwidth of the PLL.
 *  0b1..modify the bandwidth of the PLL directly.
 *  0b0..the bandwidth is changed synchronously with the feedback-divider.
 */
#define SYSCON_PLL1CTRL_BWDIRECT(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1CTRL_BWDIRECT_SHIFT)) & SYSCON_PLL1CTRL_BWDIRECT_MASK)

#define SYSCON_PLL1CTRL_BYPASSPREDIV_MASK        (0x80000U)
#define SYSCON_PLL1CTRL_BYPASSPREDIV_SHIFT       (19U)
/*! BYPASSPREDIV - bypass of the pre-divider.
 *  0b1..bypass of the pre-divider.
 *  0b0..use the pre-divider.
 */
#define SYSCON_PLL1CTRL_BYPASSPREDIV(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1CTRL_BYPASSPREDIV_SHIFT)) & SYSCON_PLL1CTRL_BYPASSPREDIV_MASK)

#define SYSCON_PLL1CTRL_BYPASSPOSTDIV_MASK       (0x100000U)
#define SYSCON_PLL1CTRL_BYPASSPOSTDIV_SHIFT      (20U)
/*! BYPASSPOSTDIV - bypass of the post-divider.
 *  0b1..bypass of the post-divider.
 *  0b0..use the post-divider.
 */
#define SYSCON_PLL1CTRL_BYPASSPOSTDIV(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1CTRL_BYPASSPOSTDIV_SHIFT)) & SYSCON_PLL1CTRL_BYPASSPOSTDIV_MASK)

#define SYSCON_PLL1CTRL_CLKEN_MASK               (0x200000U)
#define SYSCON_PLL1CTRL_CLKEN_SHIFT              (21U)
/*! CLKEN - enable the output clock.
 *  0b1..Enable the output clock.
 *  0b0..Disable the output clock.
 */
#define SYSCON_PLL1CTRL_CLKEN(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1CTRL_CLKEN_SHIFT)) & SYSCON_PLL1CTRL_CLKEN_MASK)

#define SYSCON_PLL1CTRL_FRMEN_MASK               (0x400000U)
#define SYSCON_PLL1CTRL_FRMEN_SHIFT              (22U)
/*! FRMEN - 1: free running mode. */
#define SYSCON_PLL1CTRL_FRMEN(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1CTRL_FRMEN_SHIFT)) & SYSCON_PLL1CTRL_FRMEN_MASK)

#define SYSCON_PLL1CTRL_FRMCLKSTABLE_MASK        (0x800000U)
#define SYSCON_PLL1CTRL_FRMCLKSTABLE_SHIFT       (23U)
/*! FRMCLKSTABLE - free running mode clockstable: Warning: Only make frm_clockstable = 1 after the PLL output frequency is stable. */
#define SYSCON_PLL1CTRL_FRMCLKSTABLE(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1CTRL_FRMCLKSTABLE_SHIFT)) & SYSCON_PLL1CTRL_FRMCLKSTABLE_MASK)

#define SYSCON_PLL1CTRL_SKEWEN_MASK              (0x1000000U)
#define SYSCON_PLL1CTRL_SKEWEN_SHIFT             (24U)
/*! SKEWEN - Skew mode.
 *  0b1..skewmode is enable.
 *  0b0..skewmode is disable.
 */
#define SYSCON_PLL1CTRL_SKEWEN(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1CTRL_SKEWEN_SHIFT)) & SYSCON_PLL1CTRL_SKEWEN_MASK)
/*! @} */

/*! @name PLL1STAT - PLL1 550m status */
/*! @{ */

#define SYSCON_PLL1STAT_LOCK_MASK                (0x1U)
#define SYSCON_PLL1STAT_LOCK_SHIFT               (0U)
/*! LOCK - lock detector output (active high) Warning: The lock signal is only reliable between fref[2] :100 kHz to 20 MHz. */
#define SYSCON_PLL1STAT_LOCK(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1STAT_LOCK_SHIFT)) & SYSCON_PLL1STAT_LOCK_MASK)

#define SYSCON_PLL1STAT_PREDIVACK_MASK           (0x2U)
#define SYSCON_PLL1STAT_PREDIVACK_SHIFT          (1U)
/*! PREDIVACK - pre-divider ratio change acknowledge. */
#define SYSCON_PLL1STAT_PREDIVACK(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1STAT_PREDIVACK_SHIFT)) & SYSCON_PLL1STAT_PREDIVACK_MASK)

#define SYSCON_PLL1STAT_FEEDDIVACK_MASK          (0x4U)
#define SYSCON_PLL1STAT_FEEDDIVACK_SHIFT         (2U)
/*! FEEDDIVACK - feedback divider ratio change acknowledge. */
#define SYSCON_PLL1STAT_FEEDDIVACK(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1STAT_FEEDDIVACK_SHIFT)) & SYSCON_PLL1STAT_FEEDDIVACK_MASK)

#define SYSCON_PLL1STAT_POSTDIVACK_MASK          (0x8U)
#define SYSCON_PLL1STAT_POSTDIVACK_SHIFT         (3U)
/*! POSTDIVACK - post-divider ratio change acknowledge. */
#define SYSCON_PLL1STAT_POSTDIVACK(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1STAT_POSTDIVACK_SHIFT)) & SYSCON_PLL1STAT_POSTDIVACK_MASK)

#define SYSCON_PLL1STAT_FRMDET_MASK              (0x10U)
#define SYSCON_PLL1STAT_FRMDET_SHIFT             (4U)
/*! FRMDET - free running detector output (active high). */
#define SYSCON_PLL1STAT_FRMDET(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1STAT_FRMDET_SHIFT)) & SYSCON_PLL1STAT_FRMDET_MASK)
/*! @} */

/*! @name PLL1NDEC - PLL1 550m N divider */
/*! @{ */

#define SYSCON_PLL1NDEC_NDIV_MASK                (0xFFU)
#define SYSCON_PLL1NDEC_NDIV_SHIFT               (0U)
/*! NDIV - pre-divider divider ratio (N-divider). */
#define SYSCON_PLL1NDEC_NDIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1NDEC_NDIV_SHIFT)) & SYSCON_PLL1NDEC_NDIV_MASK)

#define SYSCON_PLL1NDEC_NREQ_MASK                (0x100U)
#define SYSCON_PLL1NDEC_NREQ_SHIFT               (8U)
/*! NREQ - pre-divider ratio change request. */
#define SYSCON_PLL1NDEC_NREQ(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1NDEC_NREQ_SHIFT)) & SYSCON_PLL1NDEC_NREQ_MASK)
/*! @} */

/*! @name PLL1MDEC - PLL1 550m M divider */
/*! @{ */

#define SYSCON_PLL1MDEC_MDIV_MASK                (0xFFFFU)
#define SYSCON_PLL1MDEC_MDIV_SHIFT               (0U)
/*! MDIV - feedback divider divider ratio (M-divider). */
#define SYSCON_PLL1MDEC_MDIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1MDEC_MDIV_SHIFT)) & SYSCON_PLL1MDEC_MDIV_MASK)

#define SYSCON_PLL1MDEC_MREQ_MASK                (0x10000U)
#define SYSCON_PLL1MDEC_MREQ_SHIFT               (16U)
/*! MREQ - feedback ratio change request. */
#define SYSCON_PLL1MDEC_MREQ(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1MDEC_MREQ_SHIFT)) & SYSCON_PLL1MDEC_MREQ_MASK)
/*! @} */

/*! @name PLL1PDEC - PLL1 550m P divider */
/*! @{ */

#define SYSCON_PLL1PDEC_PDIV_MASK                (0x1FU)
#define SYSCON_PLL1PDEC_PDIV_SHIFT               (0U)
/*! PDIV - post-divider divider ratio (P-divider) */
#define SYSCON_PLL1PDEC_PDIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1PDEC_PDIV_SHIFT)) & SYSCON_PLL1PDEC_PDIV_MASK)

#define SYSCON_PLL1PDEC_PREQ_MASK                (0x20U)
#define SYSCON_PLL1PDEC_PREQ_SHIFT               (5U)
/*! PREQ - feedback ratio change request. */
#define SYSCON_PLL1PDEC_PREQ(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL1PDEC_PREQ_SHIFT)) & SYSCON_PLL1PDEC_PREQ_MASK)
/*! @} */

/*! @name PLL0CTRL - PLL0 550m control */
/*! @{ */

#define SYSCON_PLL0CTRL_SELR_MASK                (0xFU)
#define SYSCON_PLL0CTRL_SELR_SHIFT               (0U)
/*! SELR - Bandwidth select R value. */
#define SYSCON_PLL0CTRL_SELR(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CTRL_SELR_SHIFT)) & SYSCON_PLL0CTRL_SELR_MASK)

#define SYSCON_PLL0CTRL_SELI_MASK                (0x3F0U)
#define SYSCON_PLL0CTRL_SELI_SHIFT               (4U)
/*! SELI - Bandwidth select I value. */
#define SYSCON_PLL0CTRL_SELI(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CTRL_SELI_SHIFT)) & SYSCON_PLL0CTRL_SELI_MASK)

#define SYSCON_PLL0CTRL_SELP_MASK                (0x7C00U)
#define SYSCON_PLL0CTRL_SELP_SHIFT               (10U)
/*! SELP - Bandwidth select P value. */
#define SYSCON_PLL0CTRL_SELP(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CTRL_SELP_SHIFT)) & SYSCON_PLL0CTRL_SELP_MASK)

#define SYSCON_PLL0CTRL_BYPASSPLL_MASK           (0x8000U)
#define SYSCON_PLL0CTRL_BYPASSPLL_SHIFT          (15U)
/*! BYPASSPLL - Bypass PLL input clock is sent directly to the PLL output (default).
 *  0b1..Bypass PLL input clock is sent directly to the PLL output.
 *  0b0..use PLL.
 */
#define SYSCON_PLL0CTRL_BYPASSPLL(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CTRL_BYPASSPLL_SHIFT)) & SYSCON_PLL0CTRL_BYPASSPLL_MASK)

#define SYSCON_PLL0CTRL_BYPASSPOSTDIV2_MASK      (0x10000U)
#define SYSCON_PLL0CTRL_BYPASSPOSTDIV2_SHIFT     (16U)
/*! BYPASSPOSTDIV2 - bypass of the divide-by-2 divider in the post-divider.
 *  0b1..bypass of the divide-by-2 divider in the post-divider.
 *  0b0..use the divide-by-2 divider in the post-divider.
 */
#define SYSCON_PLL0CTRL_BYPASSPOSTDIV2(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CTRL_BYPASSPOSTDIV2_SHIFT)) & SYSCON_PLL0CTRL_BYPASSPOSTDIV2_MASK)

#define SYSCON_PLL0CTRL_LIMUPOFF_MASK            (0x20000U)
#define SYSCON_PLL0CTRL_LIMUPOFF_SHIFT           (17U)
/*! LIMUPOFF - limup_off = 1 in spread spectrum and fractional PLL applications. */
#define SYSCON_PLL0CTRL_LIMUPOFF(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CTRL_LIMUPOFF_SHIFT)) & SYSCON_PLL0CTRL_LIMUPOFF_MASK)

#define SYSCON_PLL0CTRL_BWDIRECT_MASK            (0x40000U)
#define SYSCON_PLL0CTRL_BWDIRECT_SHIFT           (18U)
/*! BWDIRECT - Control of the bandwidth of the PLL.
 *  0b1..modify the bandwidth of the PLL directly.
 *  0b0..the bandwidth is changed synchronously with the feedback-divider.
 */
#define SYSCON_PLL0CTRL_BWDIRECT(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CTRL_BWDIRECT_SHIFT)) & SYSCON_PLL0CTRL_BWDIRECT_MASK)

#define SYSCON_PLL0CTRL_BYPASSPREDIV_MASK        (0x80000U)
#define SYSCON_PLL0CTRL_BYPASSPREDIV_SHIFT       (19U)
/*! BYPASSPREDIV - bypass of the pre-divider.
 *  0b1..bypass of the pre-divider.
 *  0b0..use the pre-divider.
 */
#define SYSCON_PLL0CTRL_BYPASSPREDIV(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CTRL_BYPASSPREDIV_SHIFT)) & SYSCON_PLL0CTRL_BYPASSPREDIV_MASK)

#define SYSCON_PLL0CTRL_BYPASSPOSTDIV_MASK       (0x100000U)
#define SYSCON_PLL0CTRL_BYPASSPOSTDIV_SHIFT      (20U)
/*! BYPASSPOSTDIV - bypass of the post-divider.
 *  0b1..bypass of the post-divider.
 *  0b0..use the post-divider.
 */
#define SYSCON_PLL0CTRL_BYPASSPOSTDIV(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CTRL_BYPASSPOSTDIV_SHIFT)) & SYSCON_PLL0CTRL_BYPASSPOSTDIV_MASK)

#define SYSCON_PLL0CTRL_CLKEN_MASK               (0x200000U)
#define SYSCON_PLL0CTRL_CLKEN_SHIFT              (21U)
/*! CLKEN - enable the output clock.
 *  0b1..enable the output clock.
 *  0b0..disable the output clock.
 */
#define SYSCON_PLL0CTRL_CLKEN(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CTRL_CLKEN_SHIFT)) & SYSCON_PLL0CTRL_CLKEN_MASK)

#define SYSCON_PLL0CTRL_FRMEN_MASK               (0x400000U)
#define SYSCON_PLL0CTRL_FRMEN_SHIFT              (22U)
/*! FRMEN - free running mode.
 *  0b1..free running mode is enable.
 *  0b0..free running mode is disable.
 */
#define SYSCON_PLL0CTRL_FRMEN(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CTRL_FRMEN_SHIFT)) & SYSCON_PLL0CTRL_FRMEN_MASK)

#define SYSCON_PLL0CTRL_FRMCLKSTABLE_MASK        (0x800000U)
#define SYSCON_PLL0CTRL_FRMCLKSTABLE_SHIFT       (23U)
/*! FRMCLKSTABLE - free running mode clockstable: Warning: Only make frm_clockstable =1 after the PLL output frequency is stable. */
#define SYSCON_PLL0CTRL_FRMCLKSTABLE(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CTRL_FRMCLKSTABLE_SHIFT)) & SYSCON_PLL0CTRL_FRMCLKSTABLE_MASK)

#define SYSCON_PLL0CTRL_SKEWEN_MASK              (0x1000000U)
#define SYSCON_PLL0CTRL_SKEWEN_SHIFT             (24U)
/*! SKEWEN - skew mode.
 *  0b1..skew mode is enable.
 *  0b0..skew mode is disable.
 */
#define SYSCON_PLL0CTRL_SKEWEN(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0CTRL_SKEWEN_SHIFT)) & SYSCON_PLL0CTRL_SKEWEN_MASK)
/*! @} */

/*! @name PLL0STAT - PLL0 550m status */
/*! @{ */

#define SYSCON_PLL0STAT_LOCK_MASK                (0x1U)
#define SYSCON_PLL0STAT_LOCK_SHIFT               (0U)
/*! LOCK - lock detector output (active high) Warning: The lock signal is only reliable between fref[2] :100 kHz to 20 MHz. */
#define SYSCON_PLL0STAT_LOCK(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0STAT_LOCK_SHIFT)) & SYSCON_PLL0STAT_LOCK_MASK)

#define SYSCON_PLL0STAT_PREDIVACK_MASK           (0x2U)
#define SYSCON_PLL0STAT_PREDIVACK_SHIFT          (1U)
/*! PREDIVACK - pre-divider ratio change acknowledge. */
#define SYSCON_PLL0STAT_PREDIVACK(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0STAT_PREDIVACK_SHIFT)) & SYSCON_PLL0STAT_PREDIVACK_MASK)

#define SYSCON_PLL0STAT_FEEDDIVACK_MASK          (0x4U)
#define SYSCON_PLL0STAT_FEEDDIVACK_SHIFT         (2U)
/*! FEEDDIVACK - feedback divider ratio change acknowledge. */
#define SYSCON_PLL0STAT_FEEDDIVACK(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0STAT_FEEDDIVACK_SHIFT)) & SYSCON_PLL0STAT_FEEDDIVACK_MASK)

#define SYSCON_PLL0STAT_POSTDIVACK_MASK          (0x8U)
#define SYSCON_PLL0STAT_POSTDIVACK_SHIFT         (3U)
/*! POSTDIVACK - post-divider ratio change acknowledge. */
#define SYSCON_PLL0STAT_POSTDIVACK(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0STAT_POSTDIVACK_SHIFT)) & SYSCON_PLL0STAT_POSTDIVACK_MASK)

#define SYSCON_PLL0STAT_FRMDET_MASK              (0x10U)
#define SYSCON_PLL0STAT_FRMDET_SHIFT             (4U)
/*! FRMDET - free running detector output (active high). */
#define SYSCON_PLL0STAT_FRMDET(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0STAT_FRMDET_SHIFT)) & SYSCON_PLL0STAT_FRMDET_MASK)
/*! @} */

/*! @name PLL0NDEC - PLL0 550m N divider */
/*! @{ */

#define SYSCON_PLL0NDEC_NDIV_MASK                (0xFFU)
#define SYSCON_PLL0NDEC_NDIV_SHIFT               (0U)
/*! NDIV - pre-divider divider ratio (N-divider). */
#define SYSCON_PLL0NDEC_NDIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0NDEC_NDIV_SHIFT)) & SYSCON_PLL0NDEC_NDIV_MASK)

#define SYSCON_PLL0NDEC_NREQ_MASK                (0x100U)
#define SYSCON_PLL0NDEC_NREQ_SHIFT               (8U)
/*! NREQ - pre-divider ratio change request. */
#define SYSCON_PLL0NDEC_NREQ(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0NDEC_NREQ_SHIFT)) & SYSCON_PLL0NDEC_NREQ_MASK)
/*! @} */

/*! @name PLL0PDEC - PLL0 550m P divider */
/*! @{ */

#define SYSCON_PLL0PDEC_PDIV_MASK                (0x1FU)
#define SYSCON_PLL0PDEC_PDIV_SHIFT               (0U)
/*! PDIV - post-divider divider ratio (P-divider) */
#define SYSCON_PLL0PDEC_PDIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0PDEC_PDIV_SHIFT)) & SYSCON_PLL0PDEC_PDIV_MASK)

#define SYSCON_PLL0PDEC_PREQ_MASK                (0x20U)
#define SYSCON_PLL0PDEC_PREQ_SHIFT               (5U)
/*! PREQ - feedback ratio change request. */
#define SYSCON_PLL0PDEC_PREQ(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0PDEC_PREQ_SHIFT)) & SYSCON_PLL0PDEC_PREQ_MASK)
/*! @} */

/*! @name PLL0SSCG0 - PLL0 Spread Spectrum Wrapper control register 0 */
/*! @{ */

#define SYSCON_PLL0SSCG0_MD_LBS_MASK             (0xFFFFFFFFU)
#define SYSCON_PLL0SSCG0_MD_LBS_SHIFT            (0U)
/*! MD_LBS - input word of the wrapper bit 31 to 0. */
#define SYSCON_PLL0SSCG0_MD_LBS(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0SSCG0_MD_LBS_SHIFT)) & SYSCON_PLL0SSCG0_MD_LBS_MASK)
/*! @} */

/*! @name PLL0SSCG1 - PLL0 Spread Spectrum Wrapper control register 1 */
/*! @{ */

#define SYSCON_PLL0SSCG1_MD_MBS_MASK             (0x1U)
#define SYSCON_PLL0SSCG1_MD_MBS_SHIFT            (0U)
/*! MD_MBS - input word of the wrapper bit 32. */
#define SYSCON_PLL0SSCG1_MD_MBS(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0SSCG1_MD_MBS_SHIFT)) & SYSCON_PLL0SSCG1_MD_MBS_MASK)

#define SYSCON_PLL0SSCG1_MD_REQ_MASK             (0x2U)
#define SYSCON_PLL0SSCG1_MD_REQ_SHIFT            (1U)
/*! MD_REQ - md change request. */
#define SYSCON_PLL0SSCG1_MD_REQ(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0SSCG1_MD_REQ_SHIFT)) & SYSCON_PLL0SSCG1_MD_REQ_MASK)

#define SYSCON_PLL0SSCG1_MF_MASK                 (0x1CU)
#define SYSCON_PLL0SSCG1_MF_SHIFT                (2U)
/*! MF - programmable modulation frequency fm = Fref/Nss mf[2:0] = 000 => Nss=512 (fm ~ 3. */
#define SYSCON_PLL0SSCG1_MF(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0SSCG1_MF_SHIFT)) & SYSCON_PLL0SSCG1_MF_MASK)

#define SYSCON_PLL0SSCG1_MR_MASK                 (0xE0U)
#define SYSCON_PLL0SSCG1_MR_SHIFT                (5U)
/*! MR - programmable frequency modulation depth Dfmodpk-pk = Fref*kss/Fcco = kss/(2*md[32:25]dec)
 *    mr[2:0] = 000 => kss = 0 (no spread spectrum) mr[2:0] = 001 => kss ~ 1 mr[2:0] = 010 => kss ~ 1.
 */
#define SYSCON_PLL0SSCG1_MR(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0SSCG1_MR_SHIFT)) & SYSCON_PLL0SSCG1_MR_MASK)

#define SYSCON_PLL0SSCG1_MC_MASK                 (0x300U)
#define SYSCON_PLL0SSCG1_MC_SHIFT                (8U)
/*! MC - modulation waveform control Compensation for low pass filtering of the PLL to get a
 *    triangular modulation at the output of the PLL, giving a flat frequency spectrum.
 */
#define SYSCON_PLL0SSCG1_MC(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0SSCG1_MC_SHIFT)) & SYSCON_PLL0SSCG1_MC_MASK)

#define SYSCON_PLL0SSCG1_MDIV_EXT_MASK           (0x3FFFC00U)
#define SYSCON_PLL0SSCG1_MDIV_EXT_SHIFT          (10U)
/*! MDIV_EXT - to select an external mdiv value. */
#define SYSCON_PLL0SSCG1_MDIV_EXT(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0SSCG1_MDIV_EXT_SHIFT)) & SYSCON_PLL0SSCG1_MDIV_EXT_MASK)

#define SYSCON_PLL0SSCG1_MREQ_MASK               (0x4000000U)
#define SYSCON_PLL0SSCG1_MREQ_SHIFT              (26U)
/*! MREQ - to select an external mreq value. */
#define SYSCON_PLL0SSCG1_MREQ(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0SSCG1_MREQ_SHIFT)) & SYSCON_PLL0SSCG1_MREQ_MASK)

#define SYSCON_PLL0SSCG1_DITHER_MASK             (0x8000000U)
#define SYSCON_PLL0SSCG1_DITHER_SHIFT            (27U)
/*! DITHER - dithering between two modulation frequencies in a random way or in a pseudo random way
 *    (white noise), in order to decrease the probability that the modulated waveform will occur
 *    with the same phase on a particular point on the screen.
 */
#define SYSCON_PLL0SSCG1_DITHER(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0SSCG1_DITHER_SHIFT)) & SYSCON_PLL0SSCG1_DITHER_MASK)

#define SYSCON_PLL0SSCG1_SEL_EXT_MASK            (0x10000000U)
#define SYSCON_PLL0SSCG1_SEL_EXT_SHIFT           (28U)
/*! SEL_EXT - to select mdiv_ext and mreq_ext sel_ext = 0: mdiv ~ md[32:0], mreq = 1 sel_ext = 1 : mdiv = mdiv_ext, mreq = mreq_ext. */
#define SYSCON_PLL0SSCG1_SEL_EXT(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PLL0SSCG1_SEL_EXT_SHIFT)) & SYSCON_PLL0SSCG1_SEL_EXT_MASK)
/*! @} */

/*! @name FUNCRETENTIONCTRL - Functional retention control register */
/*! @{ */

#define SYSCON_FUNCRETENTIONCTRL_FUNCRETENA_MASK (0x1U)
#define SYSCON_FUNCRETENTIONCTRL_FUNCRETENA_SHIFT (0U)
/*! FUNCRETENA - functional retention in power down only.
 *  0b1..enable functional retention.
 *  0b0..disable functional retention.
 */
#define SYSCON_FUNCRETENTIONCTRL_FUNCRETENA(x)   (((uint32_t)(((uint32_t)(x)) << SYSCON_FUNCRETENTIONCTRL_FUNCRETENA_SHIFT)) & SYSCON_FUNCRETENTIONCTRL_FUNCRETENA_MASK)

#define SYSCON_FUNCRETENTIONCTRL_RET_START_MASK  (0x3FFEU)
#define SYSCON_FUNCRETENTIONCTRL_RET_START_SHIFT (1U)
/*! RET_START - Start address divided by 4 inside SRAMX bank. */
#define SYSCON_FUNCRETENTIONCTRL_RET_START(x)    (((uint32_t)(((uint32_t)(x)) << SYSCON_FUNCRETENTIONCTRL_RET_START_SHIFT)) & SYSCON_FUNCRETENTIONCTRL_RET_START_MASK)

#define SYSCON_FUNCRETENTIONCTRL_RET_LENTH_MASK  (0xFFC000U)
#define SYSCON_FUNCRETENTIONCTRL_RET_LENTH_SHIFT (14U)
/*! RET_LENTH - lenth of Scan chains to save. */
#define SYSCON_FUNCRETENTIONCTRL_RET_LENTH(x)    (((uint32_t)(((uint32_t)(x)) << SYSCON_FUNCRETENTIONCTRL_RET_LENTH_SHIFT)) & SYSCON_FUNCRETENTIONCTRL_RET_LENTH_MASK)
/*! @} */

/*! @name CPSTAT - CPU Status */
/*! @{ */

#define SYSCON_CPSTAT_CPU0SLEEPING_MASK          (0x1U)
#define SYSCON_CPSTAT_CPU0SLEEPING_SHIFT         (0U)
/*! CPU0SLEEPING - The CPU0 sleeping state.
 *  0b1..the CPU is sleeping.
 *  0b0..the CPU is not sleeping.
 */
#define SYSCON_CPSTAT_CPU0SLEEPING(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_CPSTAT_CPU0SLEEPING_SHIFT)) & SYSCON_CPSTAT_CPU0SLEEPING_MASK)

#define SYSCON_CPSTAT_CPU0LOCKUP_MASK            (0x4U)
#define SYSCON_CPSTAT_CPU0LOCKUP_SHIFT           (2U)
/*! CPU0LOCKUP - The CPU0 lockup state.
 *  0b1..the CPU is in lockup.
 *  0b0..the CPU is not in lockup.
 */
#define SYSCON_CPSTAT_CPU0LOCKUP(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_CPSTAT_CPU0LOCKUP_SHIFT)) & SYSCON_CPSTAT_CPU0LOCKUP_MASK)
/*! @} */

/*! @name BOOT_SEED_REG0 - boot seed (256-bit random value) */
/*! @{ */

#define SYSCON_BOOT_SEED_REG0_BOOT_SEED_REG0_MASK (0xFFFFFFFFU)
#define SYSCON_BOOT_SEED_REG0_BOOT_SEED_REG0_SHIFT (0U)
#define SYSCON_BOOT_SEED_REG0_BOOT_SEED_REG0(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_BOOT_SEED_REG0_BOOT_SEED_REG0_SHIFT)) & SYSCON_BOOT_SEED_REG0_BOOT_SEED_REG0_MASK)
/*! @} */

/*! @name BOOT_SEED_REG1 - boot seed (256-bit random value) */
/*! @{ */

#define SYSCON_BOOT_SEED_REG1_BOOT_SEED_REG1_MASK (0xFFFFFFFFU)
#define SYSCON_BOOT_SEED_REG1_BOOT_SEED_REG1_SHIFT (0U)
#define SYSCON_BOOT_SEED_REG1_BOOT_SEED_REG1(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_BOOT_SEED_REG1_BOOT_SEED_REG1_SHIFT)) & SYSCON_BOOT_SEED_REG1_BOOT_SEED_REG1_MASK)
/*! @} */

/*! @name BOOT_SEED_REG2 - boot seed (256-bit random value) */
/*! @{ */

#define SYSCON_BOOT_SEED_REG2_BOOT_SEED_REG2_MASK (0xFFFFFFFFU)
#define SYSCON_BOOT_SEED_REG2_BOOT_SEED_REG2_SHIFT (0U)
#define SYSCON_BOOT_SEED_REG2_BOOT_SEED_REG2(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_BOOT_SEED_REG2_BOOT_SEED_REG2_SHIFT)) & SYSCON_BOOT_SEED_REG2_BOOT_SEED_REG2_MASK)
/*! @} */

/*! @name BOOT_SEED_REG3 - boot seed (256-bit random value) */
/*! @{ */

#define SYSCON_BOOT_SEED_REG3_BOOT_SEED_REG3_MASK (0xFFFFFFFFU)
#define SYSCON_BOOT_SEED_REG3_BOOT_SEED_REG3_SHIFT (0U)
#define SYSCON_BOOT_SEED_REG3_BOOT_SEED_REG3(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_BOOT_SEED_REG3_BOOT_SEED_REG3_SHIFT)) & SYSCON_BOOT_SEED_REG3_BOOT_SEED_REG3_MASK)
/*! @} */

/*! @name BOOT_SEED_REG4 - boot seed (256-bit random value) */
/*! @{ */

#define SYSCON_BOOT_SEED_REG4_BOOT_SEED_REG4_MASK (0xFFFFFFFFU)
#define SYSCON_BOOT_SEED_REG4_BOOT_SEED_REG4_SHIFT (0U)
#define SYSCON_BOOT_SEED_REG4_BOOT_SEED_REG4(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_BOOT_SEED_REG4_BOOT_SEED_REG4_SHIFT)) & SYSCON_BOOT_SEED_REG4_BOOT_SEED_REG4_MASK)
/*! @} */

/*! @name BOOT_SEED_REG5 - boot seed (256-bit random value) */
/*! @{ */

#define SYSCON_BOOT_SEED_REG5_BOOT_SEED_REG5_MASK (0xFFFFFFFFU)
#define SYSCON_BOOT_SEED_REG5_BOOT_SEED_REG5_SHIFT (0U)
#define SYSCON_BOOT_SEED_REG5_BOOT_SEED_REG5(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_BOOT_SEED_REG5_BOOT_SEED_REG5_SHIFT)) & SYSCON_BOOT_SEED_REG5_BOOT_SEED_REG5_MASK)
/*! @} */

/*! @name BOOT_SEED_REG6 - boot seed (256-bit random value) */
/*! @{ */

#define SYSCON_BOOT_SEED_REG6_BOOT_SEED_REG6_MASK (0xFFFFFFFFU)
#define SYSCON_BOOT_SEED_REG6_BOOT_SEED_REG6_SHIFT (0U)
#define SYSCON_BOOT_SEED_REG6_BOOT_SEED_REG6(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_BOOT_SEED_REG6_BOOT_SEED_REG6_SHIFT)) & SYSCON_BOOT_SEED_REG6_BOOT_SEED_REG6_MASK)
/*! @} */

/*! @name BOOT_SEED_REG7 - boot seed (256-bit random value) */
/*! @{ */

#define SYSCON_BOOT_SEED_REG7_BOOT_SEED_REG7_MASK (0xFFFFFFFFU)
#define SYSCON_BOOT_SEED_REG7_BOOT_SEED_REG7_SHIFT (0U)
#define SYSCON_BOOT_SEED_REG7_BOOT_SEED_REG7(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_BOOT_SEED_REG7_BOOT_SEED_REG7_SHIFT)) & SYSCON_BOOT_SEED_REG7_BOOT_SEED_REG7_MASK)
/*! @} */

/*! @name HMAC_REG0 - HMAC */
/*! @{ */

#define SYSCON_HMAC_REG0_HMAC_REG0_MASK          (0xFFFFFFFFU)
#define SYSCON_HMAC_REG0_HMAC_REG0_SHIFT         (0U)
#define SYSCON_HMAC_REG0_HMAC_REG0(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_HMAC_REG0_HMAC_REG0_SHIFT)) & SYSCON_HMAC_REG0_HMAC_REG0_MASK)
/*! @} */

/*! @name HMAC_REG1 - HMAC */
/*! @{ */

#define SYSCON_HMAC_REG1_HMAC_REG1_MASK          (0xFFFFFFFFU)
#define SYSCON_HMAC_REG1_HMAC_REG1_SHIFT         (0U)
#define SYSCON_HMAC_REG1_HMAC_REG1(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_HMAC_REG1_HMAC_REG1_SHIFT)) & SYSCON_HMAC_REG1_HMAC_REG1_MASK)
/*! @} */

/*! @name HMAC_REG2 - HMAC */
/*! @{ */

#define SYSCON_HMAC_REG2_HMAC_REG2_MASK          (0xFFFFFFFFU)
#define SYSCON_HMAC_REG2_HMAC_REG2_SHIFT         (0U)
#define SYSCON_HMAC_REG2_HMAC_REG2(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_HMAC_REG2_HMAC_REG2_SHIFT)) & SYSCON_HMAC_REG2_HMAC_REG2_MASK)
/*! @} */

/*! @name HMAC_REG3 - HMAC */
/*! @{ */

#define SYSCON_HMAC_REG3_HMAC_REG3_MASK          (0xFFFFFFFFU)
#define SYSCON_HMAC_REG3_HMAC_REG3_SHIFT         (0U)
#define SYSCON_HMAC_REG3_HMAC_REG3(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_HMAC_REG3_HMAC_REG3_SHIFT)) & SYSCON_HMAC_REG3_HMAC_REG3_MASK)
/*! @} */

/*! @name HMAC_REG4 - HMAC */
/*! @{ */

#define SYSCON_HMAC_REG4_HMAC_REG4_MASK          (0xFFFFFFFFU)
#define SYSCON_HMAC_REG4_HMAC_REG4_SHIFT         (0U)
#define SYSCON_HMAC_REG4_HMAC_REG4(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_HMAC_REG4_HMAC_REG4_SHIFT)) & SYSCON_HMAC_REG4_HMAC_REG4_MASK)
/*! @} */

/*! @name HMAC_REG5 - HMAC */
/*! @{ */

#define SYSCON_HMAC_REG5_HMAC_REG5_MASK          (0xFFFFFFFFU)
#define SYSCON_HMAC_REG5_HMAC_REG5_SHIFT         (0U)
#define SYSCON_HMAC_REG5_HMAC_REG5(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_HMAC_REG5_HMAC_REG5_SHIFT)) & SYSCON_HMAC_REG5_HMAC_REG5_MASK)
/*! @} */

/*! @name HMAC_REG6 - HMAC */
/*! @{ */

#define SYSCON_HMAC_REG6_HMAC_REG6_MASK          (0xFFFFFFFFU)
#define SYSCON_HMAC_REG6_HMAC_REG6_SHIFT         (0U)
#define SYSCON_HMAC_REG6_HMAC_REG6(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_HMAC_REG6_HMAC_REG6_SHIFT)) & SYSCON_HMAC_REG6_HMAC_REG6_MASK)
/*! @} */

/*! @name HMAC_REG7 - HMAC */
/*! @{ */

#define SYSCON_HMAC_REG7_HMAC_REG7_MASK          (0xFFFFFFFFU)
#define SYSCON_HMAC_REG7_HMAC_REG7_SHIFT         (0U)
#define SYSCON_HMAC_REG7_HMAC_REG7(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_HMAC_REG7_HMAC_REG7_SHIFT)) & SYSCON_HMAC_REG7_HMAC_REG7_MASK)
/*! @} */

/*! @name BOOT_LOCK - Control write access to boot seed security registers. */
/*! @{ */

#define SYSCON_BOOT_LOCK_LOCK_BOOT_SEED_MASK     (0x1U)
#define SYSCON_BOOT_LOCK_LOCK_BOOT_SEED_SHIFT    (0U)
/*! LOCK_BOOT_SEED - Control write access to BOOT_SEED_REG registers.
 *  0b1..write access to all 8 registers BOOT_SEED_REG is locked. This register is write once.
 */
#define SYSCON_BOOT_LOCK_LOCK_BOOT_SEED(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_BOOT_LOCK_LOCK_BOOT_SEED_SHIFT)) & SYSCON_BOOT_LOCK_LOCK_BOOT_SEED_MASK)

#define SYSCON_BOOT_LOCK_LOCK_HMAC_MASK          (0x2U)
#define SYSCON_BOOT_LOCK_LOCK_HMAC_SHIFT         (1U)
/*! LOCK_HMAC - Control write access to HMAC_REG registers.
 *  0b1..write access to all 8 registers HMAC_REG is locked. This register is write once.
 */
#define SYSCON_BOOT_LOCK_LOCK_HMAC(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_BOOT_LOCK_LOCK_HMAC_SHIFT)) & SYSCON_BOOT_LOCK_LOCK_HMAC_MASK)
/*! @} */

/*! @name CLOCK_CTRL - Various system clock controls : Flash clock (48 MHz) control, clocks to Frequency Measures */
/*! @{ */

#define SYSCON_CLOCK_CTRL_XTAL32MHZ_FREQM_ENA_MASK (0x2U)
#define SYSCON_CLOCK_CTRL_XTAL32MHZ_FREQM_ENA_SHIFT (1U)
/*! XTAL32MHZ_FREQM_ENA - Enable XTAL32MHz clock for Frequency Measure module.
 *  0b1..The clock is enabled.
 *  0b0..The clock is not enabled.
 */
#define SYSCON_CLOCK_CTRL_XTAL32MHZ_FREQM_ENA(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_CLOCK_CTRL_XTAL32MHZ_FREQM_ENA_SHIFT)) & SYSCON_CLOCK_CTRL_XTAL32MHZ_FREQM_ENA_MASK)

#define SYSCON_CLOCK_CTRL_FRO1MHZ_UTICK_ENA_MASK (0x4U)
#define SYSCON_CLOCK_CTRL_FRO1MHZ_UTICK_ENA_SHIFT (2U)
/*! FRO1MHZ_UTICK_ENA - Enable FRO 1MHz clock for Frequency Measure module and for UTICK.
 *  0b1..The clock is enabled.
 *  0b0..The clock is not enabled.
 */
#define SYSCON_CLOCK_CTRL_FRO1MHZ_UTICK_ENA(x)   (((uint32_t)(((uint32_t)(x)) << SYSCON_CLOCK_CTRL_FRO1MHZ_UTICK_ENA_SHIFT)) & SYSCON_CLOCK_CTRL_FRO1MHZ_UTICK_ENA_MASK)

#define SYSCON_CLOCK_CTRL_FRO12MHZ_FREQM_ENA_MASK (0x8U)
#define SYSCON_CLOCK_CTRL_FRO12MHZ_FREQM_ENA_SHIFT (3U)
/*! FRO12MHZ_FREQM_ENA - Enable FRO 12MHz clock for Frequency Measure module.
 *  0b1..The clock is enabled.
 *  0b0..The clock is not enabled.
 */
#define SYSCON_CLOCK_CTRL_FRO12MHZ_FREQM_ENA(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_CLOCK_CTRL_FRO12MHZ_FREQM_ENA_SHIFT)) & SYSCON_CLOCK_CTRL_FRO12MHZ_FREQM_ENA_MASK)

#define SYSCON_CLOCK_CTRL_FRO_HF_FREQM_ENA_MASK  (0x10U)
#define SYSCON_CLOCK_CTRL_FRO_HF_FREQM_ENA_SHIFT (4U)
/*! FRO_HF_FREQM_ENA - Enable FRO 96MHz clock for Frequency Measure module.
 *  0b1..The clock is enabled.
 *  0b0..The clock is not enabled.
 */
#define SYSCON_CLOCK_CTRL_FRO_HF_FREQM_ENA(x)    (((uint32_t)(((uint32_t)(x)) << SYSCON_CLOCK_CTRL_FRO_HF_FREQM_ENA_SHIFT)) & SYSCON_CLOCK_CTRL_FRO_HF_FREQM_ENA_MASK)

#define SYSCON_CLOCK_CTRL_CLKIN_ENA_MASK         (0x20U)
#define SYSCON_CLOCK_CTRL_CLKIN_ENA_SHIFT        (5U)
/*! CLKIN_ENA - Enable clock_in clock for clock module.
 *  0b1..The clock is enabled.
 *  0b0..The clock is not enabled.
 */
#define SYSCON_CLOCK_CTRL_CLKIN_ENA(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_CLOCK_CTRL_CLKIN_ENA_SHIFT)) & SYSCON_CLOCK_CTRL_CLKIN_ENA_MASK)

#define SYSCON_CLOCK_CTRL_FRO1MHZ_CLK_ENA_MASK   (0x40U)
#define SYSCON_CLOCK_CTRL_FRO1MHZ_CLK_ENA_SHIFT  (6U)
/*! FRO1MHZ_CLK_ENA - Enable FRO 1MHz clock for clock muxing in clock gen.
 *  0b1..The clock is enabled.
 *  0b0..The clock is not enabled.
 */
#define SYSCON_CLOCK_CTRL_FRO1MHZ_CLK_ENA(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_CLOCK_CTRL_FRO1MHZ_CLK_ENA_SHIFT)) & SYSCON_CLOCK_CTRL_FRO1MHZ_CLK_ENA_MASK)

#define SYSCON_CLOCK_CTRL_ANA_FRO12M_CLK_ENA_MASK (0x80U)
#define SYSCON_CLOCK_CTRL_ANA_FRO12M_CLK_ENA_SHIFT (7U)
/*! ANA_FRO12M_CLK_ENA - Enable FRO 12MHz clock for analog control of the FRO 192MHz.
 *  0b1..The clock is enabled.
 *  0b0..The clock is not enabled.
 */
#define SYSCON_CLOCK_CTRL_ANA_FRO12M_CLK_ENA(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_CLOCK_CTRL_ANA_FRO12M_CLK_ENA_SHIFT)) & SYSCON_CLOCK_CTRL_ANA_FRO12M_CLK_ENA_MASK)

#define SYSCON_CLOCK_CTRL_XO_CAL_CLK_ENA_MASK    (0x100U)
#define SYSCON_CLOCK_CTRL_XO_CAL_CLK_ENA_SHIFT   (8U)
/*! XO_CAL_CLK_ENA - Enable clock for cristal oscilator calibration.
 *  0b1..The clock is enabled.
 *  0b0..The clock is not enabled.
 */
#define SYSCON_CLOCK_CTRL_XO_CAL_CLK_ENA(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_CLOCK_CTRL_XO_CAL_CLK_ENA_SHIFT)) & SYSCON_CLOCK_CTRL_XO_CAL_CLK_ENA_MASK)

#define SYSCON_CLOCK_CTRL_PLU_DEGLITCH_CLK_ENA_MASK (0x200U)
#define SYSCON_CLOCK_CTRL_PLU_DEGLITCH_CLK_ENA_SHIFT (9U)
/*! PLU_DEGLITCH_CLK_ENA - Enable clocks FRO_1MHz and FRO_12MHz for PLU deglitching.
 *  0b1..The clock is enabled.
 *  0b0..The clock is not enabled.
 */
#define SYSCON_CLOCK_CTRL_PLU_DEGLITCH_CLK_ENA(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_CLOCK_CTRL_PLU_DEGLITCH_CLK_ENA_SHIFT)) & SYSCON_CLOCK_CTRL_PLU_DEGLITCH_CLK_ENA_MASK)
/*! @} */

/*! @name COMP_INT_CTRL - Comparator Interrupt control */
/*! @{ */

#define SYSCON_COMP_INT_CTRL_INT_ENABLE_MASK     (0x1U)
#define SYSCON_COMP_INT_CTRL_INT_ENABLE_SHIFT    (0U)
/*! INT_ENABLE - Analog Comparator interrupt enable control:.
 *  0b1..interrupt enable.
 *  0b0..interrupt disable.
 */
#define SYSCON_COMP_INT_CTRL_INT_ENABLE(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_COMP_INT_CTRL_INT_ENABLE_SHIFT)) & SYSCON_COMP_INT_CTRL_INT_ENABLE_MASK)

#define SYSCON_COMP_INT_CTRL_INT_CLEAR_MASK      (0x2U)
#define SYSCON_COMP_INT_CTRL_INT_CLEAR_SHIFT     (1U)
/*! INT_CLEAR - Analog Comparator interrupt clear.
 *  0b0..No effect.
 *  0b1..Clear the interrupt. Self-cleared bit.
 */
#define SYSCON_COMP_INT_CTRL_INT_CLEAR(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_COMP_INT_CTRL_INT_CLEAR_SHIFT)) & SYSCON_COMP_INT_CTRL_INT_CLEAR_MASK)

#define SYSCON_COMP_INT_CTRL_INT_CTRL_MASK       (0x1CU)
#define SYSCON_COMP_INT_CTRL_INT_CTRL_SHIFT      (2U)
/*! INT_CTRL - Comparator interrupt type selector:.
 *  0b000..The analog comparator interrupt edge sensitive is disabled.
 *  0b010..analog comparator interrupt is rising edge sensitive.
 *  0b100..analog comparator interrupt is falling edge sensitive.
 *  0b110..analog comparator interrupt is rising and falling edge sensitive.
 *  0b001..The analog comparator interrupt level sensitive is disabled.
 *  0b011..Analog Comparator interrupt is high level sensitive.
 *  0b101..Analog Comparator interrupt is low level sensitive.
 *  0b111..The analog comparator interrupt level sensitive is disabled.
 */
#define SYSCON_COMP_INT_CTRL_INT_CTRL(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_COMP_INT_CTRL_INT_CTRL_SHIFT)) & SYSCON_COMP_INT_CTRL_INT_CTRL_MASK)

#define SYSCON_COMP_INT_CTRL_INT_SOURCE_MASK     (0x20U)
#define SYSCON_COMP_INT_CTRL_INT_SOURCE_SHIFT    (5U)
/*! INT_SOURCE - Select which Analog comparator output (filtered our un-filtered) is used for interrupt detection.
 *  0b0..Select Analog Comparator filtered output as input for interrupt detection.
 *  0b1..Select Analog Comparator raw output (unfiltered) as input for interrupt detection. Must be used when
 *       Analog comparator is used as wake up source in Power down mode.
 */
#define SYSCON_COMP_INT_CTRL_INT_SOURCE(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_COMP_INT_CTRL_INT_SOURCE_SHIFT)) & SYSCON_COMP_INT_CTRL_INT_SOURCE_MASK)
/*! @} */

/*! @name COMP_INT_STATUS - Comparator Interrupt status */
/*! @{ */

#define SYSCON_COMP_INT_STATUS_STATUS_MASK       (0x1U)
#define SYSCON_COMP_INT_STATUS_STATUS_SHIFT      (0U)
/*! STATUS - Interrupt status BEFORE Interrupt Enable.
 *  0b0..no interrupt pending.
 *  0b1..interrupt pending.
 */
#define SYSCON_COMP_INT_STATUS_STATUS(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_COMP_INT_STATUS_STATUS_SHIFT)) & SYSCON_COMP_INT_STATUS_STATUS_MASK)

#define SYSCON_COMP_INT_STATUS_INT_STATUS_MASK   (0x2U)
#define SYSCON_COMP_INT_STATUS_INT_STATUS_SHIFT  (1U)
/*! INT_STATUS - Interrupt status AFTER Interrupt Enable.
 *  0b0..no interrupt pending.
 *  0b1..interrupt pending.
 */
#define SYSCON_COMP_INT_STATUS_INT_STATUS(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_COMP_INT_STATUS_INT_STATUS_SHIFT)) & SYSCON_COMP_INT_STATUS_INT_STATUS_MASK)

#define SYSCON_COMP_INT_STATUS_VAL_MASK          (0x4U)
#define SYSCON_COMP_INT_STATUS_VAL_SHIFT         (2U)
/*! VAL - comparator analog output.
 *  0b1..P+ is greater than P-.
 *  0b0..P+ is smaller than P-.
 */
#define SYSCON_COMP_INT_STATUS_VAL(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_COMP_INT_STATUS_VAL_SHIFT)) & SYSCON_COMP_INT_STATUS_VAL_MASK)
/*! @} */

/*! @name AUTOCLKGATEOVERRIDE - Control automatic clock gating */
/*! @{ */

#define SYSCON_AUTOCLKGATEOVERRIDE_ROM_MASK      (0x1U)
#define SYSCON_AUTOCLKGATEOVERRIDE_ROM_SHIFT     (0U)
/*! ROM - Control automatic clock gating of ROM controller.
 *  0b1..Automatic clock gating is overridden (Clock gating is disabled).
 *  0b0..Automatic clock gating is not overridden.
 */
#define SYSCON_AUTOCLKGATEOVERRIDE_ROM(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_AUTOCLKGATEOVERRIDE_ROM_SHIFT)) & SYSCON_AUTOCLKGATEOVERRIDE_ROM_MASK)

#define SYSCON_AUTOCLKGATEOVERRIDE_RAMX_CTRL_MASK (0x2U)
#define SYSCON_AUTOCLKGATEOVERRIDE_RAMX_CTRL_SHIFT (1U)
/*! RAMX_CTRL - Control automatic clock gating of RAMX controller.
 *  0b1..Automatic clock gating is overridden (Clock gating is disabled).
 *  0b0..Automatic clock gating is not overridden.
 */
#define SYSCON_AUTOCLKGATEOVERRIDE_RAMX_CTRL(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_AUTOCLKGATEOVERRIDE_RAMX_CTRL_SHIFT)) & SYSCON_AUTOCLKGATEOVERRIDE_RAMX_CTRL_MASK)

#define SYSCON_AUTOCLKGATEOVERRIDE_RAM0_CTRL_MASK (0x4U)
#define SYSCON_AUTOCLKGATEOVERRIDE_RAM0_CTRL_SHIFT (2U)
/*! RAM0_CTRL - Control automatic clock gating of RAM0 controller.
 *  0b1..Automatic clock gating is overridden (Clock gating is disabled).
 *  0b0..Automatic clock gating is not overridden.
 */
#define SYSCON_AUTOCLKGATEOVERRIDE_RAM0_CTRL(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_AUTOCLKGATEOVERRIDE_RAM0_CTRL_SHIFT)) & SYSCON_AUTOCLKGATEOVERRIDE_RAM0_CTRL_MASK)

#define SYSCON_AUTOCLKGATEOVERRIDE_RAM1_CTRL_MASK (0x8U)
#define SYSCON_AUTOCLKGATEOVERRIDE_RAM1_CTRL_SHIFT (3U)
/*! RAM1_CTRL - Control automatic clock gating of RAM1 controller.
 *  0b1..Automatic clock gating is overridden (Clock gating is disabled).
 *  0b0..Automatic clock gating is not overridden.
 */
#define SYSCON_AUTOCLKGATEOVERRIDE_RAM1_CTRL(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_AUTOCLKGATEOVERRIDE_RAM1_CTRL_SHIFT)) & SYSCON_AUTOCLKGATEOVERRIDE_RAM1_CTRL_MASK)

#define SYSCON_AUTOCLKGATEOVERRIDE_RAM2_CTRL_MASK (0x10U)
#define SYSCON_AUTOCLKGATEOVERRIDE_RAM2_CTRL_SHIFT (4U)
/*! RAM2_CTRL - Control automatic clock gating of RAM2 controller.
 *  0b1..Automatic clock gating is overridden (Clock gating is disabled).
 *  0b0..Automatic clock gating is not overridden.
 */
#define SYSCON_AUTOCLKGATEOVERRIDE_RAM2_CTRL(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_AUTOCLKGATEOVERRIDE_RAM2_CTRL_SHIFT)) & SYSCON_AUTOCLKGATEOVERRIDE_RAM2_CTRL_MASK)

#define SYSCON_AUTOCLKGATEOVERRIDE_SYNC0_APB_MASK (0x80U)
#define SYSCON_AUTOCLKGATEOVERRIDE_SYNC0_APB_SHIFT (7U)
/*! SYNC0_APB - Control automatic clock gating of synchronous bridge controller 0.
 *  0b1..Automatic clock gating is overridden (Clock gating is disabled).
 *  0b0..Automatic clock gating is not overridden.
 */
#define SYSCON_AUTOCLKGATEOVERRIDE_SYNC0_APB(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_AUTOCLKGATEOVERRIDE_SYNC0_APB_SHIFT)) & SYSCON_AUTOCLKGATEOVERRIDE_SYNC0_APB_MASK)

#define SYSCON_AUTOCLKGATEOVERRIDE_SYNC1_APB_MASK (0x100U)
#define SYSCON_AUTOCLKGATEOVERRIDE_SYNC1_APB_SHIFT (8U)
/*! SYNC1_APB - Control automatic clock gating of synchronous bridge controller 1.
 *  0b1..Automatic clock gating is overridden (Clock gating is disabled).
 *  0b0..Automatic clock gating is not overridden.
 */
#define SYSCON_AUTOCLKGATEOVERRIDE_SYNC1_APB(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_AUTOCLKGATEOVERRIDE_SYNC1_APB_SHIFT)) & SYSCON_AUTOCLKGATEOVERRIDE_SYNC1_APB_MASK)

#define SYSCON_AUTOCLKGATEOVERRIDE_CRCGEN_MASK   (0x800U)
#define SYSCON_AUTOCLKGATEOVERRIDE_CRCGEN_SHIFT  (11U)
/*! CRCGEN - Control automatic clock gating of CRCGEN controller.
 *  0b1..Automatic clock gating is overridden (Clock gating is disabled).
 *  0b0..Automatic clock gating is not overridden.
 */
#define SYSCON_AUTOCLKGATEOVERRIDE_CRCGEN(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_AUTOCLKGATEOVERRIDE_CRCGEN_SHIFT)) & SYSCON_AUTOCLKGATEOVERRIDE_CRCGEN_MASK)

#define SYSCON_AUTOCLKGATEOVERRIDE_SDMA0_MASK    (0x1000U)
#define SYSCON_AUTOCLKGATEOVERRIDE_SDMA0_SHIFT   (12U)
/*! SDMA0 - Control automatic clock gating of DMA0 controller.
 *  0b1..Automatic clock gating is overridden (Clock gating is disabled).
 *  0b0..Automatic clock gating is not overridden.
 */
#define SYSCON_AUTOCLKGATEOVERRIDE_SDMA0(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_AUTOCLKGATEOVERRIDE_SDMA0_SHIFT)) & SYSCON_AUTOCLKGATEOVERRIDE_SDMA0_MASK)

#define SYSCON_AUTOCLKGATEOVERRIDE_SDMA1_MASK    (0x2000U)
#define SYSCON_AUTOCLKGATEOVERRIDE_SDMA1_SHIFT   (13U)
/*! SDMA1 - Control automatic clock gating of DMA1 controller.
 *  0b1..Automatic clock gating is overridden (Clock gating is disabled).
 *  0b0..Automatic clock gating is not overridden.
 */
#define SYSCON_AUTOCLKGATEOVERRIDE_SDMA1(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_AUTOCLKGATEOVERRIDE_SDMA1_SHIFT)) & SYSCON_AUTOCLKGATEOVERRIDE_SDMA1_MASK)

#define SYSCON_AUTOCLKGATEOVERRIDE_USB0_MASK     (0x4000U)
#define SYSCON_AUTOCLKGATEOVERRIDE_USB0_SHIFT    (14U)
/*! USB0 - Control automatic clock gating of USB controller.
 *  0b1..Automatic clock gating is overridden (Clock gating is disabled).
 *  0b0..Automatic clock gating is not overridden.
 */
#define SYSCON_AUTOCLKGATEOVERRIDE_USB0(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_AUTOCLKGATEOVERRIDE_USB0_SHIFT)) & SYSCON_AUTOCLKGATEOVERRIDE_USB0_MASK)

#define SYSCON_AUTOCLKGATEOVERRIDE_SYSCON_MASK   (0x8000U)
#define SYSCON_AUTOCLKGATEOVERRIDE_SYSCON_SHIFT  (15U)
/*! SYSCON - Control automatic clock gating of synchronous system controller registers bank.
 *  0b1..Automatic clock gating is overridden (Clock gating is disabled).
 *  0b0..Automatic clock gating is not overridden.
 */
#define SYSCON_AUTOCLKGATEOVERRIDE_SYSCON(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_AUTOCLKGATEOVERRIDE_SYSCON_SHIFT)) & SYSCON_AUTOCLKGATEOVERRIDE_SYSCON_MASK)

#define SYSCON_AUTOCLKGATEOVERRIDE_ENABLEUPDATE_MASK (0xFFFF0000U)
#define SYSCON_AUTOCLKGATEOVERRIDE_ENABLEUPDATE_SHIFT (16U)
/*! ENABLEUPDATE - The value 0xC0DE must be written for AUTOCLKGATEOVERRIDE registers fields updates to have effect.
 *  0b1100000011011110..Bit Fields 0 - 15 of this register are updated
 *  0b0000000000000000..Bit Fields 0 - 15 of this register are not updated
 */
#define SYSCON_AUTOCLKGATEOVERRIDE_ENABLEUPDATE(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_AUTOCLKGATEOVERRIDE_ENABLEUPDATE_SHIFT)) & SYSCON_AUTOCLKGATEOVERRIDE_ENABLEUPDATE_MASK)
/*! @} */

/*! @name GPIOPSYNC - Enable bypass of the first stage of synchonization inside GPIO_INT module */
/*! @{ */

#define SYSCON_GPIOPSYNC_PSYNC_MASK              (0x1U)
#define SYSCON_GPIOPSYNC_PSYNC_SHIFT             (0U)
/*! PSYNC - Enable bypass of the first stage of synchonization inside GPIO_INT module.
 *  0b1..bypass of the first stage of synchonization inside GPIO_INT module.
 *  0b0..use the first stage of synchonization inside GPIO_INT module.
 */
#define SYSCON_GPIOPSYNC_PSYNC(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_GPIOPSYNC_PSYNC_SHIFT)) & SYSCON_GPIOPSYNC_PSYNC_MASK)
/*! @} */

/*! @name HASHRESTHWKEY - Controls whether the HASH AES hardware secret key is restricted to use by secure code */
/*! @{ */

#define SYSCON_HASHRESTHWKEY_UNLOCKCODE_MASK     (0xFFFFFFFFU)
#define SYSCON_HASHRESTHWKEY_UNLOCKCODE_SHIFT    (0U)
/*! UNLOCKCODE - Code value that controls whether HASH AES hardware secret key is unlocked
 *  0b11000011001111001010010101011010..HASH AES hardware secret key is unlocked for use by non-secure code. Any
 *                                      other value means that the hardware secret key is restricted to use by
 *                                      secure code only.
 */
#define SYSCON_HASHRESTHWKEY_UNLOCKCODE(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_HASHRESTHWKEY_UNLOCKCODE_SHIFT)) & SYSCON_HASHRESTHWKEY_UNLOCKCODE_MASK)
/*! @} */

/*! @name DEBUG_LOCK_EN - Control write access to security registers. */
/*! @{ */

#define SYSCON_DEBUG_LOCK_EN_LOCK_ALL_MASK       (0xFU)
#define SYSCON_DEBUG_LOCK_EN_LOCK_ALL_SHIFT      (0U)
/*! LOCK_ALL - Control write access to security registers.
 *  0b1010..1010: Enable write access to all registers.
 *  0b0000..Any other value than b1010: disable write access to all registers.
 */
#define SYSCON_DEBUG_LOCK_EN_LOCK_ALL(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_DEBUG_LOCK_EN_LOCK_ALL_SHIFT)) & SYSCON_DEBUG_LOCK_EN_LOCK_ALL_MASK)
/*! @} */

/*! @name DEBUG_FEATURES - Cortex debug features control. */
/*! @{ */

#define SYSCON_DEBUG_FEATURES_CPU0_DBGEN_MASK    (0x3U)
#define SYSCON_DEBUG_FEATURES_CPU0_DBGEN_SHIFT   (0U)
/*! CPU0_DBGEN - CPU0 Invasive debug control:.
 *  0b10..10: Invasive debug is enabled.
 *  0b01..Any other value than b10: invasive debug is disable.
 */
#define SYSCON_DEBUG_FEATURES_CPU0_DBGEN(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_DEBUG_FEATURES_CPU0_DBGEN_SHIFT)) & SYSCON_DEBUG_FEATURES_CPU0_DBGEN_MASK)

#define SYSCON_DEBUG_FEATURES_CPU0_NIDEN_MASK    (0xCU)
#define SYSCON_DEBUG_FEATURES_CPU0_NIDEN_SHIFT   (2U)
/*! CPU0_NIDEN - CPU0 Non Invasive debug control:.
 *  0b10..10: Invasive debug is enabled.
 *  0b01..Any other value than b10: invasive debug is disable.
 */
#define SYSCON_DEBUG_FEATURES_CPU0_NIDEN(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_DEBUG_FEATURES_CPU0_NIDEN_SHIFT)) & SYSCON_DEBUG_FEATURES_CPU0_NIDEN_MASK)

#define SYSCON_DEBUG_FEATURES_CPU0_SPIDEN_MASK   (0x30U)
#define SYSCON_DEBUG_FEATURES_CPU0_SPIDEN_SHIFT  (4U)
/*! CPU0_SPIDEN - CPU0 Secure Invasive debug control:.
 *  0b10..10: Invasive debug is enabled.
 *  0b01..Any other value than b10: invasive debug is disable.
 */
#define SYSCON_DEBUG_FEATURES_CPU0_SPIDEN(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_DEBUG_FEATURES_CPU0_SPIDEN_SHIFT)) & SYSCON_DEBUG_FEATURES_CPU0_SPIDEN_MASK)

#define SYSCON_DEBUG_FEATURES_CPU0_SPNIDEN_MASK  (0xC0U)
#define SYSCON_DEBUG_FEATURES_CPU0_SPNIDEN_SHIFT (6U)
/*! CPU0_SPNIDEN - CPU0 Secure Non Invasive debug control:.
 *  0b10..10: Invasive debug is enabled.
 *  0b01..Any other value than b10: invasive debug is disable.
 */
#define SYSCON_DEBUG_FEATURES_CPU0_SPNIDEN(x)    (((uint32_t)(((uint32_t)(x)) << SYSCON_DEBUG_FEATURES_CPU0_SPNIDEN_SHIFT)) & SYSCON_DEBUG_FEATURES_CPU0_SPNIDEN_MASK)
/*! @} */

/*! @name DEBUG_FEATURES_DP - Cortex debug features control. (duplicate) */
/*! @{ */

#define SYSCON_DEBUG_FEATURES_DP_CPU0_DBGEN_MASK (0x3U)
#define SYSCON_DEBUG_FEATURES_DP_CPU0_DBGEN_SHIFT (0U)
/*! CPU0_DBGEN - CPU0 (CPU0) Invasive debug control:.
 *  0b10..10: Invasive debug is enabled.
 *  0b01..Any other value than b10: invasive debug is disable.
 */
#define SYSCON_DEBUG_FEATURES_DP_CPU0_DBGEN(x)   (((uint32_t)(((uint32_t)(x)) << SYSCON_DEBUG_FEATURES_DP_CPU0_DBGEN_SHIFT)) & SYSCON_DEBUG_FEATURES_DP_CPU0_DBGEN_MASK)

#define SYSCON_DEBUG_FEATURES_DP_CPU0_NIDEN_MASK (0xCU)
#define SYSCON_DEBUG_FEATURES_DP_CPU0_NIDEN_SHIFT (2U)
/*! CPU0_NIDEN - CPU0 Non Invasive debug control:.
 *  0b10..10: Invasive debug is enabled.
 *  0b01..Any other value than b10: invasive debug is disable.
 */
#define SYSCON_DEBUG_FEATURES_DP_CPU0_NIDEN(x)   (((uint32_t)(((uint32_t)(x)) << SYSCON_DEBUG_FEATURES_DP_CPU0_NIDEN_SHIFT)) & SYSCON_DEBUG_FEATURES_DP_CPU0_NIDEN_MASK)

#define SYSCON_DEBUG_FEATURES_DP_CPU0_SPIDEN_MASK (0x30U)
#define SYSCON_DEBUG_FEATURES_DP_CPU0_SPIDEN_SHIFT (4U)
/*! CPU0_SPIDEN - CPU0 Secure Invasive debug control:.
 *  0b10..10: Invasive debug is enabled.
 *  0b01..Any other value than b10: invasive debug is disable.
 */
#define SYSCON_DEBUG_FEATURES_DP_CPU0_SPIDEN(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_DEBUG_FEATURES_DP_CPU0_SPIDEN_SHIFT)) & SYSCON_DEBUG_FEATURES_DP_CPU0_SPIDEN_MASK)

#define SYSCON_DEBUG_FEATURES_DP_CPU0_SPNIDEN_MASK (0xC0U)
#define SYSCON_DEBUG_FEATURES_DP_CPU0_SPNIDEN_SHIFT (6U)
/*! CPU0_SPNIDEN - CPU0 Secure Non Invasive debug control:.
 *  0b10..10: Invasive debug is enabled.
 *  0b01..Any other value than b10: invasive debug is disable.
 */
#define SYSCON_DEBUG_FEATURES_DP_CPU0_SPNIDEN(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_DEBUG_FEATURES_DP_CPU0_SPNIDEN_SHIFT)) & SYSCON_DEBUG_FEATURES_DP_CPU0_SPNIDEN_MASK)
/*! @} */

/*! @name SWD_ACCESS_CPU0 - This register is used by ROM during DEBUG authentication mechanism to enable debug access port for CPU0. */
/*! @{ */

#define SYSCON_SWD_ACCESS_CPU0_SEC_CODE_MASK     (0xFFFFFFFFU)
#define SYSCON_SWD_ACCESS_CPU0_SEC_CODE_SHIFT    (0U)
/*! SEC_CODE - CPU0 SWD-AP: 0x12345678.
 *  0b00010010001101000101011001111000..Value to write to enable CPU0 SWD access. Reading back register will be read as 0xA.
 *  0b00000000000000000000000000000000..CPU0 DAP is not allowed. Reading back register will be read as 0x5.
 */
#define SYSCON_SWD_ACCESS_CPU0_SEC_CODE(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_SWD_ACCESS_CPU0_SEC_CODE_SHIFT)) & SYSCON_SWD_ACCESS_CPU0_SEC_CODE_MASK)
/*! @} */

/*! @name KEY_BLOCK - block quiddikey/PUF all index. */
/*! @{ */

#define SYSCON_KEY_BLOCK_KEY_BLOCK_MASK          (0xFFFFFFFFU)
#define SYSCON_KEY_BLOCK_KEY_BLOCK_SHIFT         (0U)
/*! KEY_BLOCK - Write a value to block quiddikey/PUF all index. */
#define SYSCON_KEY_BLOCK_KEY_BLOCK(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_KEY_BLOCK_KEY_BLOCK_SHIFT)) & SYSCON_KEY_BLOCK_KEY_BLOCK_MASK)
/*! @} */

/*! @name DEBUG_AUTH_BEACON - Debug authentication BEACON register */
/*! @{ */

#define SYSCON_DEBUG_AUTH_BEACON_BEACON_MASK     (0xFFFFFFFFU)
#define SYSCON_DEBUG_AUTH_BEACON_BEACON_SHIFT    (0U)
/*! BEACON - Set by the debug authentication code in ROM to pass the debug beacons (Credential
 *    Beacon and Authentication Beacon) to application code.
 */
#define SYSCON_DEBUG_AUTH_BEACON_BEACON(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_DEBUG_AUTH_BEACON_BEACON_SHIFT)) & SYSCON_DEBUG_AUTH_BEACON_BEACON_MASK)
/*! @} */

/*! @name DEVICE_ID0 - Device ID */
/*! @{ */

#define SYSCON_DEVICE_ID0_ROM_REV_MINOR_MASK     (0xF00000U)
#define SYSCON_DEVICE_ID0_ROM_REV_MINOR_SHIFT    (20U)
/*! ROM_REV_MINOR - ROM revision. */
#define SYSCON_DEVICE_ID0_ROM_REV_MINOR(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_DEVICE_ID0_ROM_REV_MINOR_SHIFT)) & SYSCON_DEVICE_ID0_ROM_REV_MINOR_MASK)
/*! @} */

/*! @name DIEID - Chip revision ID and Number */
/*! @{ */

#define SYSCON_DIEID_REV_ID_MASK                 (0xFU)
#define SYSCON_DIEID_REV_ID_SHIFT                (0U)
/*! REV_ID - Chip Metal Revision ID. */
#define SYSCON_DIEID_REV_ID(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_DIEID_REV_ID_SHIFT)) & SYSCON_DIEID_REV_ID_MASK)

#define SYSCON_DIEID_MCO_NUM_IN_DIE_ID_MASK      (0xFFFFF0U)
#define SYSCON_DIEID_MCO_NUM_IN_DIE_ID_SHIFT     (4U)
/*! MCO_NUM_IN_DIE_ID - Chip Number 0x426B. */
#define SYSCON_DIEID_MCO_NUM_IN_DIE_ID(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_DIEID_MCO_NUM_IN_DIE_ID_SHIFT)) & SYSCON_DIEID_MCO_NUM_IN_DIE_ID_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SYSCON_Register_Masks */


/*!
 * @}
 */ /* end of group SYSCON_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_access_layer */


#endif  /* SYSCON_H_ */


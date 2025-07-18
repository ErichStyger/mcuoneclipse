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
**         CMSIS Peripheral Access Layer for ANACTRL
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
 * @file ANACTRL.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for ANACTRL
 *
 * CMSIS Peripheral Access Layer for ANACTRL
 */

#if !defined(ANACTRL_H_)
#define ANACTRL_H_                               /**< Symbol preventing repeated inclusion */

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
   -- ANACTRL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ANACTRL_Peripheral_Access_Layer ANACTRL Peripheral Access Layer
 * @{
 */

/** ANACTRL - Register Layout Typedef */
typedef struct {
  __IO uint32_t ANALOG_CTRL_CFG;                   /**< Various Analog blocks configuration (like FRO 192MHz trimmings source ...), offset: 0x0 */
  __I  uint32_t ANALOG_CTRL_STATUS;                /**< Analog Macroblock Identity registers, Flash Status registers, offset: 0x4 */
       uint8_t RESERVED_0[4];
  __IO uint32_t FREQ_ME_CTRL;                      /**< Frequency Measure function control register, offset: 0xC */
  __IO uint32_t FRO192M_CTRL;                      /**< 192MHz Free Running OScillator (FRO) Control register, offset: 0x10 */
  __I  uint32_t FRO192M_STATUS;                    /**< 192MHz Free Running OScillator (FRO) Status register, offset: 0x14 */
  __IO uint32_t ADC_CTRL;                          /**< General Purpose ADC VBAT Divider branch control, offset: 0x18 */
       uint8_t RESERVED_1[4];
  __IO uint32_t XO32M_CTRL;                        /**< High speed Crystal Oscillator Control register, offset: 0x20 */
  __I  uint32_t XO32M_STATUS;                      /**< High speed Crystal Oscillator Status register, offset: 0x24 */
       uint8_t RESERVED_2[8];
  __IO uint32_t BOD_DCDC_INT_CTRL;                 /**< Brown Out Detectors (BoDs) & DCDC interrupts generation control register, offset: 0x30 */
  __I  uint32_t BOD_DCDC_INT_STATUS;               /**< BoDs & DCDC interrupts status register, offset: 0x34 */
       uint8_t RESERVED_3[8];
  __IO uint32_t RINGO0_CTRL;                       /**< First Ring Oscillator module control register., offset: 0x40 */
  __IO uint32_t RINGO1_CTRL;                       /**< Second Ring Oscillator module control register., offset: 0x44 */
  __IO uint32_t RINGO2_CTRL;                       /**< Third Ring Oscillator module control register., offset: 0x48 */
       uint8_t RESERVED_4[100];
  __IO uint32_t LDO_XO32M;                         /**< High Speed Crystal Oscillator (12 MHz - 32 MHz) Voltage Source Supply Control register, offset: 0xB0 */
  __IO uint32_t AUX_BIAS;                          /**< AUX_BIAS, offset: 0xB4 */
       uint8_t RESERVED_5[64];
  __IO uint32_t DUMMY_CTRL;                        /**< Dummy Control bus to analog modules, offset: 0xF8 */
       uint8_t RESERVED_6[4];
  __IO uint32_t USBHS_PHY_CTRL;                    /**< USB High Speed Phy Control, offset: 0x100 */
  __IO uint32_t USBHS_PHY_TRIM;                    /**< USB High Speed Phy Trim values, offset: 0x104 */
} ANACTRL_Type;

/* ----------------------------------------------------------------------------
   -- ANACTRL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ANACTRL_Register_Masks ANACTRL Register Masks
 * @{
 */

/*! @name ANALOG_CTRL_CFG - Various Analog blocks configuration (like FRO 192MHz trimmings source ...) */
/*! @{ */

#define ANACTRL_ANALOG_CTRL_CFG_FRO192M_TRIM_SRC_MASK (0x1U)
#define ANACTRL_ANALOG_CTRL_CFG_FRO192M_TRIM_SRC_SHIFT (0U)
/*! FRO192M_TRIM_SRC - FRO192M trimming and 'Enable' source.
 *  0b0..FRO192M trimming and 'Enable' comes from eFUSE.
 *  0b1..FRO192M trimming and 'Enable' comes from FRO192M_CTRL registers.
 */
#define ANACTRL_ANALOG_CTRL_CFG_FRO192M_TRIM_SRC(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_ANALOG_CTRL_CFG_FRO192M_TRIM_SRC_SHIFT)) & ANACTRL_ANALOG_CTRL_CFG_FRO192M_TRIM_SRC_MASK)
/*! @} */

/*! @name ANALOG_CTRL_STATUS - Analog Macroblock Identity registers, Flash Status registers */
/*! @{ */

#define ANACTRL_ANALOG_CTRL_STATUS_FLASH_PWRDWN_MASK (0x1000U)
#define ANACTRL_ANALOG_CTRL_STATUS_FLASH_PWRDWN_SHIFT (12U)
/*! FLASH_PWRDWN - Flash Power Down status.
 *  0b0..Flash is not in power down mode.
 *  0b1..Flash is in power down mode.
 */
#define ANACTRL_ANALOG_CTRL_STATUS_FLASH_PWRDWN(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_ANALOG_CTRL_STATUS_FLASH_PWRDWN_SHIFT)) & ANACTRL_ANALOG_CTRL_STATUS_FLASH_PWRDWN_MASK)

#define ANACTRL_ANALOG_CTRL_STATUS_FLASH_INIT_ERROR_MASK (0x2000U)
#define ANACTRL_ANALOG_CTRL_STATUS_FLASH_INIT_ERROR_SHIFT (13U)
/*! FLASH_INIT_ERROR - Flash initialization error status.
 *  0b0..No error.
 *  0b1..At least one error occured during flash initialization..
 */
#define ANACTRL_ANALOG_CTRL_STATUS_FLASH_INIT_ERROR(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_ANALOG_CTRL_STATUS_FLASH_INIT_ERROR_SHIFT)) & ANACTRL_ANALOG_CTRL_STATUS_FLASH_INIT_ERROR_MASK)
/*! @} */

/*! @name FREQ_ME_CTRL - Frequency Measure function control register */
/*! @{ */

#define ANACTRL_FREQ_ME_CTRL_CAPVAL_SCALE_MASK   (0x7FFFFFFFU)
#define ANACTRL_FREQ_ME_CTRL_CAPVAL_SCALE_SHIFT  (0U)
/*! CAPVAL_SCALE - Frequency measure result /Frequency measur scale */
#define ANACTRL_FREQ_ME_CTRL_CAPVAL_SCALE(x)     (((uint32_t)(((uint32_t)(x)) << ANACTRL_FREQ_ME_CTRL_CAPVAL_SCALE_SHIFT)) & ANACTRL_FREQ_ME_CTRL_CAPVAL_SCALE_MASK)

#define ANACTRL_FREQ_ME_CTRL_PROG_MASK           (0x80000000U)
#define ANACTRL_FREQ_ME_CTRL_PROG_SHIFT          (31U)
/*! PROG - Set this bit to one to initiate a frequency measurement cycle. Hardware clears this bit
 *    when the measurement cycle has completed and there is valid capture data in the CAPVAL field
 *    (bits 30:0).
 */
#define ANACTRL_FREQ_ME_CTRL_PROG(x)             (((uint32_t)(((uint32_t)(x)) << ANACTRL_FREQ_ME_CTRL_PROG_SHIFT)) & ANACTRL_FREQ_ME_CTRL_PROG_MASK)
/*! @} */

/*! @name FRO192M_CTRL - 192MHz Free Running OScillator (FRO) Control register */
/*! @{ */

#define ANACTRL_FRO192M_CTRL_ENA_12MHZCLK_MASK   (0x4000U)
#define ANACTRL_FRO192M_CTRL_ENA_12MHZCLK_SHIFT  (14U)
/*! ENA_12MHZCLK - 12 MHz clock control.
 *  0b0..12 MHz clock is disabled.
 *  0b1..12 MHz clock is enabled.
 */
#define ANACTRL_FRO192M_CTRL_ENA_12MHZCLK(x)     (((uint32_t)(((uint32_t)(x)) << ANACTRL_FRO192M_CTRL_ENA_12MHZCLK_SHIFT)) & ANACTRL_FRO192M_CTRL_ENA_12MHZCLK_MASK)

#define ANACTRL_FRO192M_CTRL_DAC_TRIM_MASK       (0xFF0000U)
#define ANACTRL_FRO192M_CTRL_DAC_TRIM_SHIFT      (16U)
/*! DAC_TRIM - Frequency trim. */
#define ANACTRL_FRO192M_CTRL_DAC_TRIM(x)         (((uint32_t)(((uint32_t)(x)) << ANACTRL_FRO192M_CTRL_DAC_TRIM_SHIFT)) & ANACTRL_FRO192M_CTRL_DAC_TRIM_MASK)

#define ANACTRL_FRO192M_CTRL_USBCLKADJ_MASK      (0x1000000U)
#define ANACTRL_FRO192M_CTRL_USBCLKADJ_SHIFT     (24U)
/*! USBCLKADJ - If this bit is set and the USB peripheral is enabled into full speed device mode,
 *    the USB block will provide FRO clock adjustments to lock it to the host clock using the SOF
 *    packets.
 */
#define ANACTRL_FRO192M_CTRL_USBCLKADJ(x)        (((uint32_t)(((uint32_t)(x)) << ANACTRL_FRO192M_CTRL_USBCLKADJ_SHIFT)) & ANACTRL_FRO192M_CTRL_USBCLKADJ_MASK)

#define ANACTRL_FRO192M_CTRL_USBMODCHG_MASK      (0x2000000U)
#define ANACTRL_FRO192M_CTRL_USBMODCHG_SHIFT     (25U)
/*! USBMODCHG - If it reads as 1 when reading the DAC_TRIM field and USBCLKADJ=1, it should be re-read until it is 0. */
#define ANACTRL_FRO192M_CTRL_USBMODCHG(x)        (((uint32_t)(((uint32_t)(x)) << ANACTRL_FRO192M_CTRL_USBMODCHG_SHIFT)) & ANACTRL_FRO192M_CTRL_USBMODCHG_MASK)

#define ANACTRL_FRO192M_CTRL_ENA_96MHZCLK_MASK   (0x40000000U)
#define ANACTRL_FRO192M_CTRL_ENA_96MHZCLK_SHIFT  (30U)
/*! ENA_96MHZCLK - 96 MHz clock control.
 *  0b0..96 MHz clock is disabled.
 *  0b1..96 MHz clock is enabled.
 */
#define ANACTRL_FRO192M_CTRL_ENA_96MHZCLK(x)     (((uint32_t)(((uint32_t)(x)) << ANACTRL_FRO192M_CTRL_ENA_96MHZCLK_SHIFT)) & ANACTRL_FRO192M_CTRL_ENA_96MHZCLK_MASK)

#define ANACTRL_FRO192M_CTRL_WRTRIM_MASK         (0x80000000U)
#define ANACTRL_FRO192M_CTRL_WRTRIM_SHIFT        (31U)
/*! WRTRIM - This must be written to 1 to modify the BIAS_TRIM and TEMP_TRIM fields. */
#define ANACTRL_FRO192M_CTRL_WRTRIM(x)           (((uint32_t)(((uint32_t)(x)) << ANACTRL_FRO192M_CTRL_WRTRIM_SHIFT)) & ANACTRL_FRO192M_CTRL_WRTRIM_MASK)
/*! @} */

/*! @name FRO192M_STATUS - 192MHz Free Running OScillator (FRO) Status register */
/*! @{ */

#define ANACTRL_FRO192M_STATUS_CLK_VALID_MASK    (0x1U)
#define ANACTRL_FRO192M_STATUS_CLK_VALID_SHIFT   (0U)
/*! CLK_VALID - Output clock valid signal. Indicates that CCO clock has settled.
 *  0b0..No output clock present (None of 12 MHz, 48 MHz or 96 MHz clock is available).
 *  0b1..Clock is present (12 MHz, 48 MHz or 96 MHz can be output if they are enable respectively by
 *       FRO192M_CTRL.ENA_12MHZCLK/ENA_48MHZCLK/ENA_96MHZCLK).
 */
#define ANACTRL_FRO192M_STATUS_CLK_VALID(x)      (((uint32_t)(((uint32_t)(x)) << ANACTRL_FRO192M_STATUS_CLK_VALID_SHIFT)) & ANACTRL_FRO192M_STATUS_CLK_VALID_MASK)

#define ANACTRL_FRO192M_STATUS_ATB_VCTRL_MASK    (0x2U)
#define ANACTRL_FRO192M_STATUS_ATB_VCTRL_SHIFT   (1U)
/*! ATB_VCTRL - CCO threshold voltage detector output (signal vcco_ok). Once the CCO voltage crosses
 *    the threshold voltage of a SLVT transistor, this output signal will go high. It is also
 *    possible to observe the clk_valid signal.
 */
#define ANACTRL_FRO192M_STATUS_ATB_VCTRL(x)      (((uint32_t)(((uint32_t)(x)) << ANACTRL_FRO192M_STATUS_ATB_VCTRL_SHIFT)) & ANACTRL_FRO192M_STATUS_ATB_VCTRL_MASK)
/*! @} */

/*! @name ADC_CTRL - General Purpose ADC VBAT Divider branch control */
/*! @{ */

#define ANACTRL_ADC_CTRL_VBATDIVENABLE_MASK      (0x1U)
#define ANACTRL_ADC_CTRL_VBATDIVENABLE_SHIFT     (0U)
/*! VBATDIVENABLE - Switch On/Off VBAT divider branch.
 *  0b0..VBAT divider branch is disabled.
 *  0b1..VBAT divider branch is enabled.
 */
#define ANACTRL_ADC_CTRL_VBATDIVENABLE(x)        (((uint32_t)(((uint32_t)(x)) << ANACTRL_ADC_CTRL_VBATDIVENABLE_SHIFT)) & ANACTRL_ADC_CTRL_VBATDIVENABLE_MASK)
/*! @} */

/*! @name XO32M_CTRL - High speed Crystal Oscillator Control register */
/*! @{ */

#define ANACTRL_XO32M_CTRL_SLAVE_MASK            (0x10U)
#define ANACTRL_XO32M_CTRL_SLAVE_SHIFT           (4U)
/*! SLAVE - Xo in slave mode. */
#define ANACTRL_XO32M_CTRL_SLAVE(x)              (((uint32_t)(((uint32_t)(x)) << ANACTRL_XO32M_CTRL_SLAVE_SHIFT)) & ANACTRL_XO32M_CTRL_SLAVE_MASK)

#define ANACTRL_XO32M_CTRL_OSC_CAP_IN_MASK       (0x7F00U)
#define ANACTRL_XO32M_CTRL_OSC_CAP_IN_SHIFT      (8U)
/*! OSC_CAP_IN - Tune capa banks of High speed Crystal Oscillator input pin */
#define ANACTRL_XO32M_CTRL_OSC_CAP_IN(x)         (((uint32_t)(((uint32_t)(x)) << ANACTRL_XO32M_CTRL_OSC_CAP_IN_SHIFT)) & ANACTRL_XO32M_CTRL_OSC_CAP_IN_MASK)

#define ANACTRL_XO32M_CTRL_OSC_CAP_OUT_MASK      (0x3F8000U)
#define ANACTRL_XO32M_CTRL_OSC_CAP_OUT_SHIFT     (15U)
/*! OSC_CAP_OUT - Tune capa banks of High speed Crystal Oscillator output pin */
#define ANACTRL_XO32M_CTRL_OSC_CAP_OUT(x)        (((uint32_t)(((uint32_t)(x)) << ANACTRL_XO32M_CTRL_OSC_CAP_OUT_SHIFT)) & ANACTRL_XO32M_CTRL_OSC_CAP_OUT_MASK)

#define ANACTRL_XO32M_CTRL_ACBUF_PASS_ENABLE_MASK (0x400000U)
#define ANACTRL_XO32M_CTRL_ACBUF_PASS_ENABLE_SHIFT (22U)
/*! ACBUF_PASS_ENABLE - Bypass enable of XO AC buffer enable in pll and top level.
 *  0b0..XO AC buffer bypass is disabled.
 *  0b1..XO AC buffer bypass is enabled.
 */
#define ANACTRL_XO32M_CTRL_ACBUF_PASS_ENABLE(x)  (((uint32_t)(((uint32_t)(x)) << ANACTRL_XO32M_CTRL_ACBUF_PASS_ENABLE_SHIFT)) & ANACTRL_XO32M_CTRL_ACBUF_PASS_ENABLE_MASK)

#define ANACTRL_XO32M_CTRL_ENABLE_PLL_USB_OUT_MASK (0x800000U)
#define ANACTRL_XO32M_CTRL_ENABLE_PLL_USB_OUT_SHIFT (23U)
/*! ENABLE_PLL_USB_OUT - Enable High speed Crystal oscillator output to USB HS PLL.
 *  0b0..High speed Crystal oscillator output to USB HS PLL is disabled.
 *  0b1..High speed Crystal oscillator output to USB HS PLL is enabled.
 */
#define ANACTRL_XO32M_CTRL_ENABLE_PLL_USB_OUT(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_XO32M_CTRL_ENABLE_PLL_USB_OUT_SHIFT)) & ANACTRL_XO32M_CTRL_ENABLE_PLL_USB_OUT_MASK)

#define ANACTRL_XO32M_CTRL_ENABLE_SYSTEM_CLK_OUT_MASK (0x1000000U)
#define ANACTRL_XO32M_CTRL_ENABLE_SYSTEM_CLK_OUT_SHIFT (24U)
/*! ENABLE_SYSTEM_CLK_OUT - Enable High speed Crystal oscillator output to CPU system.
 *  0b0..High speed Crystal oscillator output to CPU system is disabled.
 *  0b1..High speed Crystal oscillator output to CPU system is enabled.
 */
#define ANACTRL_XO32M_CTRL_ENABLE_SYSTEM_CLK_OUT(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_XO32M_CTRL_ENABLE_SYSTEM_CLK_OUT_SHIFT)) & ANACTRL_XO32M_CTRL_ENABLE_SYSTEM_CLK_OUT_MASK)
/*! @} */

/*! @name XO32M_STATUS - High speed Crystal Oscillator Status register */
/*! @{ */

#define ANACTRL_XO32M_STATUS_XO_READY_MASK       (0x1U)
#define ANACTRL_XO32M_STATUS_XO_READY_SHIFT      (0U)
/*! XO_READY - Indicates XO out frequency statibilty.
 *  0b0..XO output frequency is not yet stable.
 *  0b1..XO output frequency is stable.
 */
#define ANACTRL_XO32M_STATUS_XO_READY(x)         (((uint32_t)(((uint32_t)(x)) << ANACTRL_XO32M_STATUS_XO_READY_SHIFT)) & ANACTRL_XO32M_STATUS_XO_READY_MASK)
/*! @} */

/*! @name BOD_DCDC_INT_CTRL - Brown Out Detectors (BoDs) & DCDC interrupts generation control register */
/*! @{ */

#define ANACTRL_BOD_DCDC_INT_CTRL_BODVBAT_INT_ENABLE_MASK (0x1U)
#define ANACTRL_BOD_DCDC_INT_CTRL_BODVBAT_INT_ENABLE_SHIFT (0U)
/*! BODVBAT_INT_ENABLE - BOD VBAT interrupt control.
 *  0b0..BOD VBAT interrupt is disabled.
 *  0b1..BOD VBAT interrupt is enabled.
 */
#define ANACTRL_BOD_DCDC_INT_CTRL_BODVBAT_INT_ENABLE(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_BOD_DCDC_INT_CTRL_BODVBAT_INT_ENABLE_SHIFT)) & ANACTRL_BOD_DCDC_INT_CTRL_BODVBAT_INT_ENABLE_MASK)

#define ANACTRL_BOD_DCDC_INT_CTRL_BODVBAT_INT_CLEAR_MASK (0x2U)
#define ANACTRL_BOD_DCDC_INT_CTRL_BODVBAT_INT_CLEAR_SHIFT (1U)
/*! BODVBAT_INT_CLEAR - BOD VBAT interrupt clear.1: Clear the interrupt. Self-cleared bit. */
#define ANACTRL_BOD_DCDC_INT_CTRL_BODVBAT_INT_CLEAR(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_BOD_DCDC_INT_CTRL_BODVBAT_INT_CLEAR_SHIFT)) & ANACTRL_BOD_DCDC_INT_CTRL_BODVBAT_INT_CLEAR_MASK)

#define ANACTRL_BOD_DCDC_INT_CTRL_BODCORE_INT_ENABLE_MASK (0x4U)
#define ANACTRL_BOD_DCDC_INT_CTRL_BODCORE_INT_ENABLE_SHIFT (2U)
/*! BODCORE_INT_ENABLE - BOD CORE interrupt control.
 *  0b0..BOD CORE interrupt is disabled.
 *  0b1..BOD CORE interrupt is enabled.
 */
#define ANACTRL_BOD_DCDC_INT_CTRL_BODCORE_INT_ENABLE(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_BOD_DCDC_INT_CTRL_BODCORE_INT_ENABLE_SHIFT)) & ANACTRL_BOD_DCDC_INT_CTRL_BODCORE_INT_ENABLE_MASK)

#define ANACTRL_BOD_DCDC_INT_CTRL_BODCORE_INT_CLEAR_MASK (0x8U)
#define ANACTRL_BOD_DCDC_INT_CTRL_BODCORE_INT_CLEAR_SHIFT (3U)
/*! BODCORE_INT_CLEAR - BOD CORE interrupt clear.1: Clear the interrupt. Self-cleared bit. */
#define ANACTRL_BOD_DCDC_INT_CTRL_BODCORE_INT_CLEAR(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_BOD_DCDC_INT_CTRL_BODCORE_INT_CLEAR_SHIFT)) & ANACTRL_BOD_DCDC_INT_CTRL_BODCORE_INT_CLEAR_MASK)

#define ANACTRL_BOD_DCDC_INT_CTRL_DCDC_INT_ENABLE_MASK (0x10U)
#define ANACTRL_BOD_DCDC_INT_CTRL_DCDC_INT_ENABLE_SHIFT (4U)
/*! DCDC_INT_ENABLE - DCDC interrupt control.
 *  0b0..DCDC interrupt is disabled.
 *  0b1..DCDC interrupt is enabled.
 */
#define ANACTRL_BOD_DCDC_INT_CTRL_DCDC_INT_ENABLE(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_BOD_DCDC_INT_CTRL_DCDC_INT_ENABLE_SHIFT)) & ANACTRL_BOD_DCDC_INT_CTRL_DCDC_INT_ENABLE_MASK)

#define ANACTRL_BOD_DCDC_INT_CTRL_DCDC_INT_CLEAR_MASK (0x20U)
#define ANACTRL_BOD_DCDC_INT_CTRL_DCDC_INT_CLEAR_SHIFT (5U)
/*! DCDC_INT_CLEAR - DCDC interrupt clear.1: Clear the interrupt. Self-cleared bit. */
#define ANACTRL_BOD_DCDC_INT_CTRL_DCDC_INT_CLEAR(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_BOD_DCDC_INT_CTRL_DCDC_INT_CLEAR_SHIFT)) & ANACTRL_BOD_DCDC_INT_CTRL_DCDC_INT_CLEAR_MASK)
/*! @} */

/*! @name BOD_DCDC_INT_STATUS - BoDs & DCDC interrupts status register */
/*! @{ */

#define ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_STATUS_MASK (0x1U)
#define ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_STATUS_SHIFT (0U)
/*! BODVBAT_STATUS - BOD VBAT Interrupt status before Interrupt Enable.
 *  0b0..No interrupt pending..
 *  0b1..Interrupt pending..
 */
#define ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_STATUS(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_STATUS_SHIFT)) & ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_STATUS_MASK)

#define ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_INT_STATUS_MASK (0x2U)
#define ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_INT_STATUS_SHIFT (1U)
/*! BODVBAT_INT_STATUS - BOD VBAT Interrupt status after Interrupt Enable.
 *  0b0..No interrupt pending..
 *  0b1..Interrupt pending..
 */
#define ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_INT_STATUS(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_INT_STATUS_SHIFT)) & ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_INT_STATUS_MASK)

#define ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_VAL_MASK (0x4U)
#define ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_VAL_SHIFT (2U)
/*! BODVBAT_VAL - Current value of BOD VBAT power status output.
 *  0b0..VBAT voltage level is below the threshold.
 *  0b1..VBAT voltage level is above the threshold.
 */
#define ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_VAL(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_VAL_SHIFT)) & ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_VAL_MASK)

#define ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_STATUS_MASK (0x8U)
#define ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_STATUS_SHIFT (3U)
/*! BODCORE_STATUS - BOD CORE Interrupt status before Interrupt Enable.
 *  0b0..No interrupt pending..
 *  0b1..Interrupt pending..
 */
#define ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_STATUS(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_STATUS_SHIFT)) & ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_STATUS_MASK)

#define ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_INT_STATUS_MASK (0x10U)
#define ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_INT_STATUS_SHIFT (4U)
/*! BODCORE_INT_STATUS - BOD CORE Interrupt status after Interrupt Enable.
 *  0b0..No interrupt pending..
 *  0b1..Interrupt pending..
 */
#define ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_INT_STATUS(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_INT_STATUS_SHIFT)) & ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_INT_STATUS_MASK)

#define ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_VAL_MASK (0x20U)
#define ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_VAL_SHIFT (5U)
/*! BODCORE_VAL - Current value of BOD CORE power status output.
 *  0b0..CORE voltage level is below the threshold.
 *  0b1..CORE voltage level is above the threshold.
 */
#define ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_VAL(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_VAL_SHIFT)) & ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_VAL_MASK)

#define ANACTRL_BOD_DCDC_INT_STATUS_DCDC_STATUS_MASK (0x40U)
#define ANACTRL_BOD_DCDC_INT_STATUS_DCDC_STATUS_SHIFT (6U)
/*! DCDC_STATUS - DCDC Interrupt status before Interrupt Enable.
 *  0b0..No interrupt pending..
 *  0b1..Interrupt pending..
 */
#define ANACTRL_BOD_DCDC_INT_STATUS_DCDC_STATUS(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_BOD_DCDC_INT_STATUS_DCDC_STATUS_SHIFT)) & ANACTRL_BOD_DCDC_INT_STATUS_DCDC_STATUS_MASK)

#define ANACTRL_BOD_DCDC_INT_STATUS_DCDC_INT_STATUS_MASK (0x80U)
#define ANACTRL_BOD_DCDC_INT_STATUS_DCDC_INT_STATUS_SHIFT (7U)
/*! DCDC_INT_STATUS - DCDC Interrupt status after Interrupt Enable.
 *  0b0..No interrupt pending..
 *  0b1..Interrupt pending..
 */
#define ANACTRL_BOD_DCDC_INT_STATUS_DCDC_INT_STATUS(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_BOD_DCDC_INT_STATUS_DCDC_INT_STATUS_SHIFT)) & ANACTRL_BOD_DCDC_INT_STATUS_DCDC_INT_STATUS_MASK)

#define ANACTRL_BOD_DCDC_INT_STATUS_DCDC_VAL_MASK (0x100U)
#define ANACTRL_BOD_DCDC_INT_STATUS_DCDC_VAL_SHIFT (8U)
/*! DCDC_VAL - Current value of DCDC power status output.
 *  0b0..DCDC output Voltage is below the targeted regulation level.
 *  0b1..DCDC output Voltage is above the targeted regulation level.
 */
#define ANACTRL_BOD_DCDC_INT_STATUS_DCDC_VAL(x)  (((uint32_t)(((uint32_t)(x)) << ANACTRL_BOD_DCDC_INT_STATUS_DCDC_VAL_SHIFT)) & ANACTRL_BOD_DCDC_INT_STATUS_DCDC_VAL_MASK)
/*! @} */

/*! @name RINGO0_CTRL - First Ring Oscillator module control register. */
/*! @{ */

#define ANACTRL_RINGO0_CTRL_SL_MASK              (0x1U)
#define ANACTRL_RINGO0_CTRL_SL_SHIFT             (0U)
/*! SL - Select short or long ringo (for all ringos types).
 *  0b0..Select short ringo (few elements).
 *  0b1..Select long ringo (many elements).
 */
#define ANACTRL_RINGO0_CTRL_SL(x)                (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO0_CTRL_SL_SHIFT)) & ANACTRL_RINGO0_CTRL_SL_MASK)

#define ANACTRL_RINGO0_CTRL_FS_MASK              (0x2U)
#define ANACTRL_RINGO0_CTRL_FS_SHIFT             (1U)
/*! FS - Ringo frequency output divider.
 *  0b0..High frequency output (frequency lower than 100 MHz).
 *  0b1..Low frequency output (frequency lower than 10 MHz).
 */
#define ANACTRL_RINGO0_CTRL_FS(x)                (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO0_CTRL_FS_SHIFT)) & ANACTRL_RINGO0_CTRL_FS_MASK)

#define ANACTRL_RINGO0_CTRL_SWN_SWP_MASK         (0xCU)
#define ANACTRL_RINGO0_CTRL_SWN_SWP_SHIFT        (2U)
/*! SWN_SWP - PN-Ringos (P-Transistor and N-Transistor processing) control.
 *  0b00..Normal mode.
 *  0b01..P-Monitor mode. Measure with weak P transistor.
 *  0b10..P-Monitor mode. Measure with weak N transistor.
 *  0b11..Don't use.
 */
#define ANACTRL_RINGO0_CTRL_SWN_SWP(x)           (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO0_CTRL_SWN_SWP_SHIFT)) & ANACTRL_RINGO0_CTRL_SWN_SWP_MASK)

#define ANACTRL_RINGO0_CTRL_PD_MASK              (0x10U)
#define ANACTRL_RINGO0_CTRL_PD_SHIFT             (4U)
/*! PD - Ringo module Power control.
 *  0b0..The Ringo module is enabled.
 *  0b1..The Ringo module is disabled.
 */
#define ANACTRL_RINGO0_CTRL_PD(x)                (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO0_CTRL_PD_SHIFT)) & ANACTRL_RINGO0_CTRL_PD_MASK)

#define ANACTRL_RINGO0_CTRL_E_ND0_MASK           (0x20U)
#define ANACTRL_RINGO0_CTRL_E_ND0_SHIFT          (5U)
/*! E_ND0 - First NAND2-based ringo control.
 *  0b0..First NAND2-based ringo is disabled.
 *  0b1..First NAND2-based ringo is enabled.
 */
#define ANACTRL_RINGO0_CTRL_E_ND0(x)             (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO0_CTRL_E_ND0_SHIFT)) & ANACTRL_RINGO0_CTRL_E_ND0_MASK)

#define ANACTRL_RINGO0_CTRL_E_ND1_MASK           (0x40U)
#define ANACTRL_RINGO0_CTRL_E_ND1_SHIFT          (6U)
/*! E_ND1 - Second NAND2-based ringo control.
 *  0b0..Second NAND2-based ringo is disabled.
 *  0b1..Second NAND2-based ringo is enabled.
 */
#define ANACTRL_RINGO0_CTRL_E_ND1(x)             (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO0_CTRL_E_ND1_SHIFT)) & ANACTRL_RINGO0_CTRL_E_ND1_MASK)

#define ANACTRL_RINGO0_CTRL_E_NR0_MASK           (0x80U)
#define ANACTRL_RINGO0_CTRL_E_NR0_SHIFT          (7U)
/*! E_NR0 - First NOR2-based ringo control.
 *  0b0..First NOR2-based ringo is disabled.
 *  0b1..First NOR2-based ringo is enabled.
 */
#define ANACTRL_RINGO0_CTRL_E_NR0(x)             (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO0_CTRL_E_NR0_SHIFT)) & ANACTRL_RINGO0_CTRL_E_NR0_MASK)

#define ANACTRL_RINGO0_CTRL_E_NR1_MASK           (0x100U)
#define ANACTRL_RINGO0_CTRL_E_NR1_SHIFT          (8U)
/*! E_NR1 - Second NOR2-based ringo control.
 *  0b0..Second NORD2-based ringo is disabled.
 *  0b1..Second NORD2-based ringo is enabled.
 */
#define ANACTRL_RINGO0_CTRL_E_NR1(x)             (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO0_CTRL_E_NR1_SHIFT)) & ANACTRL_RINGO0_CTRL_E_NR1_MASK)

#define ANACTRL_RINGO0_CTRL_E_IV0_MASK           (0x200U)
#define ANACTRL_RINGO0_CTRL_E_IV0_SHIFT          (9U)
/*! E_IV0 - First Inverter-based ringo control.
 *  0b0..First INV-based ringo is disabled.
 *  0b1..First INV-based ringo is enabled.
 */
#define ANACTRL_RINGO0_CTRL_E_IV0(x)             (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO0_CTRL_E_IV0_SHIFT)) & ANACTRL_RINGO0_CTRL_E_IV0_MASK)

#define ANACTRL_RINGO0_CTRL_E_IV1_MASK           (0x400U)
#define ANACTRL_RINGO0_CTRL_E_IV1_SHIFT          (10U)
/*! E_IV1 - Second Inverter-based ringo control.
 *  0b0..Second INV-based ringo is disabled.
 *  0b1..Second INV-based ringo is enabled.
 */
#define ANACTRL_RINGO0_CTRL_E_IV1(x)             (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO0_CTRL_E_IV1_SHIFT)) & ANACTRL_RINGO0_CTRL_E_IV1_MASK)

#define ANACTRL_RINGO0_CTRL_E_PN0_MASK           (0x800U)
#define ANACTRL_RINGO0_CTRL_E_PN0_SHIFT          (11U)
/*! E_PN0 - First PN (P-Transistor and N-Transistor processing) monitor control.
 *  0b0..First PN-based ringo is disabled.
 *  0b1..First PN-based ringo is enabled.
 */
#define ANACTRL_RINGO0_CTRL_E_PN0(x)             (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO0_CTRL_E_PN0_SHIFT)) & ANACTRL_RINGO0_CTRL_E_PN0_MASK)

#define ANACTRL_RINGO0_CTRL_E_PN1_MASK           (0x1000U)
#define ANACTRL_RINGO0_CTRL_E_PN1_SHIFT          (12U)
/*! E_PN1 - Second PN (P-Transistor and N-Transistor processing) monitor control.
 *  0b0..Second PN-based ringo is disabled.
 *  0b1..Second PN-based ringo is enabled.
 */
#define ANACTRL_RINGO0_CTRL_E_PN1(x)             (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO0_CTRL_E_PN1_SHIFT)) & ANACTRL_RINGO0_CTRL_E_PN1_MASK)

#define ANACTRL_RINGO0_CTRL_DIVISOR_MASK         (0xF0000U)
#define ANACTRL_RINGO0_CTRL_DIVISOR_SHIFT        (16U)
/*! DIVISOR - Ringo out Clock divider value. Frequency Output = Frequency input / (DIViSOR+1). (minimum = Frequency input / 16) */
#define ANACTRL_RINGO0_CTRL_DIVISOR(x)           (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO0_CTRL_DIVISOR_SHIFT)) & ANACTRL_RINGO0_CTRL_DIVISOR_MASK)

#define ANACTRL_RINGO0_CTRL_DIV_UPDATE_REQ_MASK  (0x80000000U)
#define ANACTRL_RINGO0_CTRL_DIV_UPDATE_REQ_SHIFT (31U)
/*! DIV_UPDATE_REQ - Ringo clock out Divider status flag. Set when a change is made to the divider
 *    value, cleared when the change is complete.
 */
#define ANACTRL_RINGO0_CTRL_DIV_UPDATE_REQ(x)    (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO0_CTRL_DIV_UPDATE_REQ_SHIFT)) & ANACTRL_RINGO0_CTRL_DIV_UPDATE_REQ_MASK)
/*! @} */

/*! @name RINGO1_CTRL - Second Ring Oscillator module control register. */
/*! @{ */

#define ANACTRL_RINGO1_CTRL_S_MASK               (0x1U)
#define ANACTRL_RINGO1_CTRL_S_SHIFT              (0U)
/*! S - Select short or long ringo (for all ringos types).
 *  0b0..Select short ringo (few elements).
 *  0b1..Select long ringo (many elements).
 */
#define ANACTRL_RINGO1_CTRL_S(x)                 (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO1_CTRL_S_SHIFT)) & ANACTRL_RINGO1_CTRL_S_MASK)

#define ANACTRL_RINGO1_CTRL_FS_MASK              (0x2U)
#define ANACTRL_RINGO1_CTRL_FS_SHIFT             (1U)
/*! FS - Ringo frequency output divider.
 *  0b0..High frequency output (frequency lower than 100 MHz).
 *  0b1..Low frequency output (frequency lower than 10 MHz).
 */
#define ANACTRL_RINGO1_CTRL_FS(x)                (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO1_CTRL_FS_SHIFT)) & ANACTRL_RINGO1_CTRL_FS_MASK)

#define ANACTRL_RINGO1_CTRL_PD_MASK              (0x4U)
#define ANACTRL_RINGO1_CTRL_PD_SHIFT             (2U)
/*! PD - Ringo module Power control.
 *  0b0..The Ringo module is enabled.
 *  0b1..The Ringo module is disabled.
 */
#define ANACTRL_RINGO1_CTRL_PD(x)                (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO1_CTRL_PD_SHIFT)) & ANACTRL_RINGO1_CTRL_PD_MASK)

#define ANACTRL_RINGO1_CTRL_E_R24_MASK           (0x8U)
#define ANACTRL_RINGO1_CTRL_E_R24_SHIFT          (3U)
/*! E_R24 - .
 *  0b0..Ringo is disabled.
 *  0b1..Ringo is enabled.
 */
#define ANACTRL_RINGO1_CTRL_E_R24(x)             (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO1_CTRL_E_R24_SHIFT)) & ANACTRL_RINGO1_CTRL_E_R24_MASK)

#define ANACTRL_RINGO1_CTRL_E_R35_MASK           (0x10U)
#define ANACTRL_RINGO1_CTRL_E_R35_SHIFT          (4U)
/*! E_R35 - .
 *  0b0..Ringo is disabled.
 *  0b1..Ringo is enabled.
 */
#define ANACTRL_RINGO1_CTRL_E_R35(x)             (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO1_CTRL_E_R35_SHIFT)) & ANACTRL_RINGO1_CTRL_E_R35_MASK)

#define ANACTRL_RINGO1_CTRL_E_M2_MASK            (0x20U)
#define ANACTRL_RINGO1_CTRL_E_M2_SHIFT           (5U)
/*! E_M2 - Metal 2 (M2) monitor control.
 *  0b0..Ringo is disabled.
 *  0b1..Ringo is enabled.
 */
#define ANACTRL_RINGO1_CTRL_E_M2(x)              (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO1_CTRL_E_M2_SHIFT)) & ANACTRL_RINGO1_CTRL_E_M2_MASK)

#define ANACTRL_RINGO1_CTRL_E_M3_MASK            (0x40U)
#define ANACTRL_RINGO1_CTRL_E_M3_SHIFT           (6U)
/*! E_M3 - Metal 3 (M3) monitor control.
 *  0b0..Ringo is disabled.
 *  0b1..Ringo is enabled.
 */
#define ANACTRL_RINGO1_CTRL_E_M3(x)              (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO1_CTRL_E_M3_SHIFT)) & ANACTRL_RINGO1_CTRL_E_M3_MASK)

#define ANACTRL_RINGO1_CTRL_E_M4_MASK            (0x80U)
#define ANACTRL_RINGO1_CTRL_E_M4_SHIFT           (7U)
/*! E_M4 - Metal 4 (M4) monitor control.
 *  0b0..Ringo is disabled.
 *  0b1..Ringo is enabled.
 */
#define ANACTRL_RINGO1_CTRL_E_M4(x)              (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO1_CTRL_E_M4_SHIFT)) & ANACTRL_RINGO1_CTRL_E_M4_MASK)

#define ANACTRL_RINGO1_CTRL_E_M5_MASK            (0x100U)
#define ANACTRL_RINGO1_CTRL_E_M5_SHIFT           (8U)
/*! E_M5 - Metal 5 (M5) monitor control.
 *  0b0..Ringo is disabled.
 *  0b1..Ringo is enabled.
 */
#define ANACTRL_RINGO1_CTRL_E_M5(x)              (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO1_CTRL_E_M5_SHIFT)) & ANACTRL_RINGO1_CTRL_E_M5_MASK)

#define ANACTRL_RINGO1_CTRL_DIVISOR_MASK         (0xF0000U)
#define ANACTRL_RINGO1_CTRL_DIVISOR_SHIFT        (16U)
/*! DIVISOR - Ringo out Clock divider value. Frequency Output = Frequency input / (DIViSOR+1). (minimum = Frequency input / 16) */
#define ANACTRL_RINGO1_CTRL_DIVISOR(x)           (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO1_CTRL_DIVISOR_SHIFT)) & ANACTRL_RINGO1_CTRL_DIVISOR_MASK)

#define ANACTRL_RINGO1_CTRL_DIV_UPDATE_REQ_MASK  (0x80000000U)
#define ANACTRL_RINGO1_CTRL_DIV_UPDATE_REQ_SHIFT (31U)
/*! DIV_UPDATE_REQ - Ringo clock out Divider status flag. Set when a change is made to the divider
 *    value, cleared when the change is complete.
 */
#define ANACTRL_RINGO1_CTRL_DIV_UPDATE_REQ(x)    (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO1_CTRL_DIV_UPDATE_REQ_SHIFT)) & ANACTRL_RINGO1_CTRL_DIV_UPDATE_REQ_MASK)
/*! @} */

/*! @name RINGO2_CTRL - Third Ring Oscillator module control register. */
/*! @{ */

#define ANACTRL_RINGO2_CTRL_S_MASK               (0x1U)
#define ANACTRL_RINGO2_CTRL_S_SHIFT              (0U)
/*! S - Select short or long ringo (for all ringos types).
 *  0b0..Select short ringo (few elements).
 *  0b1..Select long ringo (many elements).
 */
#define ANACTRL_RINGO2_CTRL_S(x)                 (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO2_CTRL_S_SHIFT)) & ANACTRL_RINGO2_CTRL_S_MASK)

#define ANACTRL_RINGO2_CTRL_FS_MASK              (0x2U)
#define ANACTRL_RINGO2_CTRL_FS_SHIFT             (1U)
/*! FS - Ringo frequency output divider.
 *  0b0..High frequency output (frequency lower than 100 MHz).
 *  0b1..Low frequency output (frequency lower than 10 MHz).
 */
#define ANACTRL_RINGO2_CTRL_FS(x)                (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO2_CTRL_FS_SHIFT)) & ANACTRL_RINGO2_CTRL_FS_MASK)

#define ANACTRL_RINGO2_CTRL_PD_MASK              (0x4U)
#define ANACTRL_RINGO2_CTRL_PD_SHIFT             (2U)
/*! PD - Ringo module Power control.
 *  0b0..The Ringo module is enabled.
 *  0b1..The Ringo module is disabled.
 */
#define ANACTRL_RINGO2_CTRL_PD(x)                (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO2_CTRL_PD_SHIFT)) & ANACTRL_RINGO2_CTRL_PD_MASK)

#define ANACTRL_RINGO2_CTRL_E_R24_MASK           (0x8U)
#define ANACTRL_RINGO2_CTRL_E_R24_SHIFT          (3U)
/*! E_R24 - .
 *  0b0..Ringo is disabled.
 *  0b1..Ringo is enabled.
 */
#define ANACTRL_RINGO2_CTRL_E_R24(x)             (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO2_CTRL_E_R24_SHIFT)) & ANACTRL_RINGO2_CTRL_E_R24_MASK)

#define ANACTRL_RINGO2_CTRL_E_R35_MASK           (0x10U)
#define ANACTRL_RINGO2_CTRL_E_R35_SHIFT          (4U)
/*! E_R35 - .
 *  0b0..Ringo is disabled.
 *  0b1..Ringo is enabled.
 */
#define ANACTRL_RINGO2_CTRL_E_R35(x)             (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO2_CTRL_E_R35_SHIFT)) & ANACTRL_RINGO2_CTRL_E_R35_MASK)

#define ANACTRL_RINGO2_CTRL_E_M2_MASK            (0x20U)
#define ANACTRL_RINGO2_CTRL_E_M2_SHIFT           (5U)
/*! E_M2 - Metal 2 (M2) monitor control.
 *  0b0..Ringo is disabled.
 *  0b1..Ringo is enabled.
 */
#define ANACTRL_RINGO2_CTRL_E_M2(x)              (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO2_CTRL_E_M2_SHIFT)) & ANACTRL_RINGO2_CTRL_E_M2_MASK)

#define ANACTRL_RINGO2_CTRL_E_M3_MASK            (0x40U)
#define ANACTRL_RINGO2_CTRL_E_M3_SHIFT           (6U)
/*! E_M3 - Metal 3 (M3) monitor control.
 *  0b0..Ringo is disabled.
 *  0b1..Ringo is enabled.
 */
#define ANACTRL_RINGO2_CTRL_E_M3(x)              (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO2_CTRL_E_M3_SHIFT)) & ANACTRL_RINGO2_CTRL_E_M3_MASK)

#define ANACTRL_RINGO2_CTRL_E_M4_MASK            (0x80U)
#define ANACTRL_RINGO2_CTRL_E_M4_SHIFT           (7U)
/*! E_M4 - Metal 4 (M4) monitor control.
 *  0b0..Ringo is disabled.
 *  0b1..Ringo is enabled.
 */
#define ANACTRL_RINGO2_CTRL_E_M4(x)              (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO2_CTRL_E_M4_SHIFT)) & ANACTRL_RINGO2_CTRL_E_M4_MASK)

#define ANACTRL_RINGO2_CTRL_E_M5_MASK            (0x100U)
#define ANACTRL_RINGO2_CTRL_E_M5_SHIFT           (8U)
/*! E_M5 - Metal 5 (M5) monitor control.
 *  0b0..Ringo is disabled.
 *  0b1..Ringo is enabled.
 */
#define ANACTRL_RINGO2_CTRL_E_M5(x)              (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO2_CTRL_E_M5_SHIFT)) & ANACTRL_RINGO2_CTRL_E_M5_MASK)

#define ANACTRL_RINGO2_CTRL_DIVISOR_MASK         (0xF0000U)
#define ANACTRL_RINGO2_CTRL_DIVISOR_SHIFT        (16U)
/*! DIVISOR - Ringo out Clock divider value. Frequency Output = Frequency input / (DIViSOR+1). (minimum = Frequency input / 16) */
#define ANACTRL_RINGO2_CTRL_DIVISOR(x)           (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO2_CTRL_DIVISOR_SHIFT)) & ANACTRL_RINGO2_CTRL_DIVISOR_MASK)

#define ANACTRL_RINGO2_CTRL_DIV_UPDATE_REQ_MASK  (0x80000000U)
#define ANACTRL_RINGO2_CTRL_DIV_UPDATE_REQ_SHIFT (31U)
/*! DIV_UPDATE_REQ - Ringo clock out Divider status flag. Set when a change is made to the divider
 *    value, cleared when the change is complete.
 */
#define ANACTRL_RINGO2_CTRL_DIV_UPDATE_REQ(x)    (((uint32_t)(((uint32_t)(x)) << ANACTRL_RINGO2_CTRL_DIV_UPDATE_REQ_SHIFT)) & ANACTRL_RINGO2_CTRL_DIV_UPDATE_REQ_MASK)
/*! @} */

/*! @name LDO_XO32M - High Speed Crystal Oscillator (12 MHz - 32 MHz) Voltage Source Supply Control register */
/*! @{ */

#define ANACTRL_LDO_XO32M_BYPASS_MASK            (0x2U)
#define ANACTRL_LDO_XO32M_BYPASS_SHIFT           (1U)
/*! BYPASS - Activate LDO bypass.
 *  0b0..Disable bypass mode (for normal operations).
 *  0b1..Activate LDO bypass.
 */
#define ANACTRL_LDO_XO32M_BYPASS(x)              (((uint32_t)(((uint32_t)(x)) << ANACTRL_LDO_XO32M_BYPASS_SHIFT)) & ANACTRL_LDO_XO32M_BYPASS_MASK)

#define ANACTRL_LDO_XO32M_HIGHZ_MASK             (0x4U)
#define ANACTRL_LDO_XO32M_HIGHZ_SHIFT            (2U)
/*! HIGHZ - .
 *  0b0..Output in High normal state.
 *  0b1..Output in High Impedance state.
 */
#define ANACTRL_LDO_XO32M_HIGHZ(x)               (((uint32_t)(((uint32_t)(x)) << ANACTRL_LDO_XO32M_HIGHZ_SHIFT)) & ANACTRL_LDO_XO32M_HIGHZ_MASK)

#define ANACTRL_LDO_XO32M_VOUT_MASK              (0x38U)
#define ANACTRL_LDO_XO32M_VOUT_SHIFT             (3U)
/*! VOUT - Sets the LDO output level.
 *  0b000..0.750 V.
 *  0b001..0.775 V.
 *  0b010..0.800 V.
 *  0b011..0.825 V.
 *  0b100..0.850 V.
 *  0b101..0.875 V.
 *  0b110..0.900 V.
 *  0b111..0.925 V.
 */
#define ANACTRL_LDO_XO32M_VOUT(x)                (((uint32_t)(((uint32_t)(x)) << ANACTRL_LDO_XO32M_VOUT_SHIFT)) & ANACTRL_LDO_XO32M_VOUT_MASK)

#define ANACTRL_LDO_XO32M_IBIAS_MASK             (0xC0U)
#define ANACTRL_LDO_XO32M_IBIAS_SHIFT            (6U)
/*! IBIAS - Adjust the biasing current. */
#define ANACTRL_LDO_XO32M_IBIAS(x)               (((uint32_t)(((uint32_t)(x)) << ANACTRL_LDO_XO32M_IBIAS_SHIFT)) & ANACTRL_LDO_XO32M_IBIAS_MASK)

#define ANACTRL_LDO_XO32M_STABMODE_MASK          (0x300U)
#define ANACTRL_LDO_XO32M_STABMODE_SHIFT         (8U)
/*! STABMODE - Stability configuration. */
#define ANACTRL_LDO_XO32M_STABMODE(x)            (((uint32_t)(((uint32_t)(x)) << ANACTRL_LDO_XO32M_STABMODE_SHIFT)) & ANACTRL_LDO_XO32M_STABMODE_MASK)
/*! @} */

/*! @name AUX_BIAS - AUX_BIAS */
/*! @{ */

#define ANACTRL_AUX_BIAS_VREF1VENABLE_MASK       (0x2U)
#define ANACTRL_AUX_BIAS_VREF1VENABLE_SHIFT      (1U)
/*! VREF1VENABLE - Control output of 1V reference voltage.
 *  0b0..Output of 1V reference voltage buffer is bypassed.
 *  0b1..Output of 1V reference voltage is enabled.
 */
#define ANACTRL_AUX_BIAS_VREF1VENABLE(x)         (((uint32_t)(((uint32_t)(x)) << ANACTRL_AUX_BIAS_VREF1VENABLE_SHIFT)) & ANACTRL_AUX_BIAS_VREF1VENABLE_MASK)

#define ANACTRL_AUX_BIAS_ITRIM_MASK              (0x7CU)
#define ANACTRL_AUX_BIAS_ITRIM_SHIFT             (2U)
/*! ITRIM - current trimming control word. */
#define ANACTRL_AUX_BIAS_ITRIM(x)                (((uint32_t)(((uint32_t)(x)) << ANACTRL_AUX_BIAS_ITRIM_SHIFT)) & ANACTRL_AUX_BIAS_ITRIM_MASK)

#define ANACTRL_AUX_BIAS_PTATITRIM_MASK          (0xF80U)
#define ANACTRL_AUX_BIAS_PTATITRIM_SHIFT         (7U)
/*! PTATITRIM - current trimming control word for ptat current. */
#define ANACTRL_AUX_BIAS_PTATITRIM(x)            (((uint32_t)(((uint32_t)(x)) << ANACTRL_AUX_BIAS_PTATITRIM_SHIFT)) & ANACTRL_AUX_BIAS_PTATITRIM_MASK)

#define ANACTRL_AUX_BIAS_VREF1VTRIM_MASK         (0x1F000U)
#define ANACTRL_AUX_BIAS_VREF1VTRIM_SHIFT        (12U)
/*! VREF1VTRIM - voltage trimming control word. */
#define ANACTRL_AUX_BIAS_VREF1VTRIM(x)           (((uint32_t)(((uint32_t)(x)) << ANACTRL_AUX_BIAS_VREF1VTRIM_SHIFT)) & ANACTRL_AUX_BIAS_VREF1VTRIM_MASK)

#define ANACTRL_AUX_BIAS_VREF1VCURVETRIM_MASK    (0xE0000U)
#define ANACTRL_AUX_BIAS_VREF1VCURVETRIM_SHIFT   (17U)
/*! VREF1VCURVETRIM - Control bit to configure trimming state of mirror. */
#define ANACTRL_AUX_BIAS_VREF1VCURVETRIM(x)      (((uint32_t)(((uint32_t)(x)) << ANACTRL_AUX_BIAS_VREF1VCURVETRIM_SHIFT)) & ANACTRL_AUX_BIAS_VREF1VCURVETRIM_MASK)

#define ANACTRL_AUX_BIAS_ITRIMCTRL0_MASK         (0x100000U)
#define ANACTRL_AUX_BIAS_ITRIMCTRL0_SHIFT        (20U)
/*! ITRIMCTRL0 - Control bit to configure trimming state of mirror. */
#define ANACTRL_AUX_BIAS_ITRIMCTRL0(x)           (((uint32_t)(((uint32_t)(x)) << ANACTRL_AUX_BIAS_ITRIMCTRL0_SHIFT)) & ANACTRL_AUX_BIAS_ITRIMCTRL0_MASK)

#define ANACTRL_AUX_BIAS_ITRIMCTRL1_MASK         (0x200000U)
#define ANACTRL_AUX_BIAS_ITRIMCTRL1_SHIFT        (21U)
/*! ITRIMCTRL1 - Control bit to configure trimming state of mirror. */
#define ANACTRL_AUX_BIAS_ITRIMCTRL1(x)           (((uint32_t)(((uint32_t)(x)) << ANACTRL_AUX_BIAS_ITRIMCTRL1_SHIFT)) & ANACTRL_AUX_BIAS_ITRIMCTRL1_MASK)
/*! @} */

/*! @name DUMMY_CTRL - Dummy Control bus to analog modules */
/*! @{ */

#define ANACTRL_DUMMY_CTRL_XO32M_ADC_CLK_MODE_MASK (0xC00U)
#define ANACTRL_DUMMY_CTRL_XO32M_ADC_CLK_MODE_SHIFT (10U)
/*! XO32M_ADC_CLK_MODE - Control High speed Crystal oscillator mode of the ADC clock.
 *  0b00..High speed Crystal oscillator output to ADC is disabled.
 *  0b01..High speed Crystal oscillator output to ADC is enable.
 */
#define ANACTRL_DUMMY_CTRL_XO32M_ADC_CLK_MODE(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_DUMMY_CTRL_XO32M_ADC_CLK_MODE_SHIFT)) & ANACTRL_DUMMY_CTRL_XO32M_ADC_CLK_MODE_MASK)
/*! @} */

/*! @name USBHS_PHY_CTRL - USB High Speed Phy Control */
/*! @{ */

#define ANACTRL_USBHS_PHY_CTRL_usb_vbusvalid_ext_MASK (0x1U)
#define ANACTRL_USBHS_PHY_CTRL_usb_vbusvalid_ext_SHIFT (0U)
/*! usb_vbusvalid_ext - Override value for Vbus if using external detectors. */
#define ANACTRL_USBHS_PHY_CTRL_usb_vbusvalid_ext(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_USBHS_PHY_CTRL_usb_vbusvalid_ext_SHIFT)) & ANACTRL_USBHS_PHY_CTRL_usb_vbusvalid_ext_MASK)

#define ANACTRL_USBHS_PHY_CTRL_usb_id_ext_MASK   (0x2U)
#define ANACTRL_USBHS_PHY_CTRL_usb_id_ext_SHIFT  (1U)
/*! usb_id_ext - Override value for ID if using external detectors. */
#define ANACTRL_USBHS_PHY_CTRL_usb_id_ext(x)     (((uint32_t)(((uint32_t)(x)) << ANACTRL_USBHS_PHY_CTRL_usb_id_ext_SHIFT)) & ANACTRL_USBHS_PHY_CTRL_usb_id_ext_MASK)

#define ANACTRL_USBHS_PHY_CTRL_iso_atx_MASK      (0x8U)
#define ANACTRL_USBHS_PHY_CTRL_iso_atx_SHIFT     (3U)
/*! iso_atx - . */
#define ANACTRL_USBHS_PHY_CTRL_iso_atx(x)        (((uint32_t)(((uint32_t)(x)) << ANACTRL_USBHS_PHY_CTRL_iso_atx_SHIFT)) & ANACTRL_USBHS_PHY_CTRL_iso_atx_MASK)
/*! @} */

/*! @name USBHS_PHY_TRIM - USB High Speed Phy Trim values */
/*! @{ */

#define ANACTRL_USBHS_PHY_TRIM_trim_usb_reg_env_tail_adj_vd_MASK (0x3U)
#define ANACTRL_USBHS_PHY_TRIM_trim_usb_reg_env_tail_adj_vd_SHIFT (0U)
/*! trim_usb_reg_env_tail_adj_vd - Adjusts time constant of HS RX squelch (envelope) comparator. */
#define ANACTRL_USBHS_PHY_TRIM_trim_usb_reg_env_tail_adj_vd(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_USBHS_PHY_TRIM_trim_usb_reg_env_tail_adj_vd_SHIFT)) & ANACTRL_USBHS_PHY_TRIM_trim_usb_reg_env_tail_adj_vd_MASK)

#define ANACTRL_USBHS_PHY_TRIM_trim_usbphy_tx_d_cal_MASK (0x3CU)
#define ANACTRL_USBHS_PHY_TRIM_trim_usbphy_tx_d_cal_SHIFT (2U)
/*! trim_usbphy_tx_d_cal - . */
#define ANACTRL_USBHS_PHY_TRIM_trim_usbphy_tx_d_cal(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_USBHS_PHY_TRIM_trim_usbphy_tx_d_cal_SHIFT)) & ANACTRL_USBHS_PHY_TRIM_trim_usbphy_tx_d_cal_MASK)

#define ANACTRL_USBHS_PHY_TRIM_trim_usbphy_tx_cal45dp_MASK (0x7C0U)
#define ANACTRL_USBHS_PHY_TRIM_trim_usbphy_tx_cal45dp_SHIFT (6U)
/*! trim_usbphy_tx_cal45dp - . */
#define ANACTRL_USBHS_PHY_TRIM_trim_usbphy_tx_cal45dp(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_USBHS_PHY_TRIM_trim_usbphy_tx_cal45dp_SHIFT)) & ANACTRL_USBHS_PHY_TRIM_trim_usbphy_tx_cal45dp_MASK)

#define ANACTRL_USBHS_PHY_TRIM_trim_usbphy_tx_cal45dm_MASK (0xF800U)
#define ANACTRL_USBHS_PHY_TRIM_trim_usbphy_tx_cal45dm_SHIFT (11U)
/*! trim_usbphy_tx_cal45dm - . */
#define ANACTRL_USBHS_PHY_TRIM_trim_usbphy_tx_cal45dm(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_USBHS_PHY_TRIM_trim_usbphy_tx_cal45dm_SHIFT)) & ANACTRL_USBHS_PHY_TRIM_trim_usbphy_tx_cal45dm_MASK)

#define ANACTRL_USBHS_PHY_TRIM_trim_usb2_refbias_tst_MASK (0x30000U)
#define ANACTRL_USBHS_PHY_TRIM_trim_usb2_refbias_tst_SHIFT (16U)
/*! trim_usb2_refbias_tst - . */
#define ANACTRL_USBHS_PHY_TRIM_trim_usb2_refbias_tst(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_USBHS_PHY_TRIM_trim_usb2_refbias_tst_SHIFT)) & ANACTRL_USBHS_PHY_TRIM_trim_usb2_refbias_tst_MASK)

#define ANACTRL_USBHS_PHY_TRIM_trim_usb2_refbias_vbgadj_MASK (0x1C0000U)
#define ANACTRL_USBHS_PHY_TRIM_trim_usb2_refbias_vbgadj_SHIFT (18U)
/*! trim_usb2_refbias_vbgadj - . */
#define ANACTRL_USBHS_PHY_TRIM_trim_usb2_refbias_vbgadj(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_USBHS_PHY_TRIM_trim_usb2_refbias_vbgadj_SHIFT)) & ANACTRL_USBHS_PHY_TRIM_trim_usb2_refbias_vbgadj_MASK)

#define ANACTRL_USBHS_PHY_TRIM_trim_pll_ctrl0_div_sel_MASK (0xE00000U)
#define ANACTRL_USBHS_PHY_TRIM_trim_pll_ctrl0_div_sel_SHIFT (21U)
/*! trim_pll_ctrl0_div_sel - . */
#define ANACTRL_USBHS_PHY_TRIM_trim_pll_ctrl0_div_sel(x) (((uint32_t)(((uint32_t)(x)) << ANACTRL_USBHS_PHY_TRIM_trim_pll_ctrl0_div_sel_SHIFT)) & ANACTRL_USBHS_PHY_TRIM_trim_pll_ctrl0_div_sel_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group ANACTRL_Register_Masks */


/*!
 * @}
 */ /* end of group ANACTRL_Peripheral_Access_Layer */


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


#endif  /* ANACTRL_H_ */


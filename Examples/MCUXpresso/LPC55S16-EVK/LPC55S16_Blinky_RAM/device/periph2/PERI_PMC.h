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
**         CMSIS Peripheral Access Layer for PMC
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
 * @file PMC.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for PMC
 *
 * CMSIS Peripheral Access Layer for PMC
 */

#if !defined(PMC_H_)
#define PMC_H_                                   /**< Symbol preventing repeated inclusion */

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
   -- PMC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Peripheral_Access_Layer PMC Peripheral Access Layer
 * @{
 */

/** PMC - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[4];
  __I  uint32_t STATUS;                            /**< Power Management Controller FSM (Finite State Machines) status, offset: 0x4 */
  __IO uint32_t RESETCTRL;                         /**< Reset Control [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset], offset: 0x8 */
       uint8_t RESERVED_1[4];
  __IO uint32_t DCDC0;                             /**< DCDC (first) control register [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset], offset: 0x10 */
  __IO uint32_t DCDC1;                             /**< DCDC (second) control register [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset], offset: 0x14 */
       uint8_t RESERVED_2[4];
  __IO uint32_t LDOPMU;                            /**< Power Management Unit (PMU) and Always-On domains LDO control [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset], offset: 0x1C */
       uint8_t RESERVED_3[16];
  __IO uint32_t BODVBAT;                           /**< VBAT Brown Out Dectector (BoD) control register [Reset by: PoR, Pin Reset, Software Reset], offset: 0x30 */
       uint8_t RESERVED_4[12];
  __IO uint32_t REFFASTWKUP;                       /**< Analog References fast wake-up Control register [Reset by: PoR], offset: 0x40 */
       uint8_t RESERVED_5[8];
  __IO uint32_t XTAL32K;                           /**< 32 KHz Crystal oscillator (XTAL) control register [Reset by: PoR, Brown Out Detectors Reset], offset: 0x4C */
  __IO uint32_t COMP;                              /**< Analog Comparator control register [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset], offset: 0x50 */
       uint8_t RESERVED_6[16];
  __IO uint32_t WAKEUPIOCTRL;                      /**< Deep Power Down wake-up source [Reset by: PoR, Pin Reset, Software Reset], offset: 0x64 */
  __IO uint32_t WAKEIOCAUSE;                       /**< Allows to identify the Wake-up I/O source from Deep Power Down mode, offset: 0x68 */
       uint8_t RESERVED_7[8];
  __IO uint32_t STATUSCLK;                         /**< FRO and XTAL status register [Reset by: PoR, Brown Out Detectors Reset], offset: 0x74 */
       uint8_t RESERVED_8[12];
  __IO uint32_t AOREG1;                            /**< General purpose always on domain data storage [Reset by: PoR, Brown Out Detectors Reset], offset: 0x84 */
       uint8_t RESERVED_9[8];
  __IO uint32_t MISCCTRL;                          /**< Dummy Control bus to PMU [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset], offset: 0x90 */
       uint8_t RESERVED_10[4];
  __IO uint32_t RTCOSC32K;                         /**< RTC 1 KHZ and 1 Hz clocks source control register [Reset by: PoR, Brown Out Detectors Reset], offset: 0x98 */
  __IO uint32_t OSTIMERr;                          /**< OS Timer control register [Reset by: PoR, Brown Out Detectors Reset], offset: 0x9C, 'r' suffix has been added to avoid a clash with peripheral base pointer macro 'OSTIMER' */
       uint8_t RESERVED_11[24];
  __IO uint32_t PDRUNCFG0;                         /**< Controls the power to various analog blocks [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset], offset: 0xB8 */
       uint8_t RESERVED_12[4];
  __O  uint32_t PDRUNCFGSET0;                      /**< Controls the power to various analog blocks [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset], offset: 0xC0 */
       uint8_t RESERVED_13[4];
  __O  uint32_t PDRUNCFGCLR0;                      /**< Controls the power to various analog blocks [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset], offset: 0xC8 */
       uint8_t RESERVED_14[8];
  __IO uint32_t SRAMCTRL;                          /**< All SRAMs common control signals [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Software Reset], offset: 0xD4 */
} PMC_Type;

/* ----------------------------------------------------------------------------
   -- PMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Masks PMC Register Masks
 * @{
 */

/*! @name STATUS - Power Management Controller FSM (Finite State Machines) status */
/*! @{ */

#define PMC_STATUS_FSMMAIN_MASK                  (0x7U)
#define PMC_STATUS_FSMMAIN_SHIFT                 (0U)
/*! FSMMAIN - Power Management Controller Main Finite State Machine (FSM) status.
 *  0b000..POWER UP : The IC is powering up.
 *  0b001..ACTIVE : Power up is completed. The IC is in normal functional operation mode.
 *  0b010..POWER DOWN : the IC has entered POWER DOWN mode.
 *  0b011..DEEP SLEEP: The IC has entered DEEP SLEEP mode.
 *  0b110..DEEP POWER DOWN : The IC entred DEEP POWER DOWN mode.
 *  0b111..IC Structural TEST Mode : The IC has entered in IC Test mode.
 */
#define PMC_STATUS_FSMMAIN(x)                    (((uint32_t)(((uint32_t)(x)) << PMC_STATUS_FSMMAIN_SHIFT)) & PMC_STATUS_FSMMAIN_MASK)

#define PMC_STATUS_FSMPWUP_MASK                  (0x78U)
#define PMC_STATUS_FSMPWUP_SHIFT                 (3U)
/*! FSMPWUP - POWER UP Finite State Machine (FSM) status. */
#define PMC_STATUS_FSMPWUP(x)                    (((uint32_t)(((uint32_t)(x)) << PMC_STATUS_FSMPWUP_SHIFT)) & PMC_STATUS_FSMPWUP_MASK)

#define PMC_STATUS_FSMDSLP_MASK                  (0x780U)
#define PMC_STATUS_FSMDSLP_SHIFT                 (7U)
/*! FSMDSLP - DEEP SLEEP Finite State Machine (FSM) status. */
#define PMC_STATUS_FSMDSLP(x)                    (((uint32_t)(((uint32_t)(x)) << PMC_STATUS_FSMDSLP_SHIFT)) & PMC_STATUS_FSMDSLP_MASK)

#define PMC_STATUS_FSMPWDN_MASK                  (0x7800U)
#define PMC_STATUS_FSMPWDN_SHIFT                 (11U)
/*! FSMPWDN - POWER DOWN Finite State Machine (FSM) status. */
#define PMC_STATUS_FSMPWDN(x)                    (((uint32_t)(((uint32_t)(x)) << PMC_STATUS_FSMPWDN_SHIFT)) & PMC_STATUS_FSMPWDN_MASK)

#define PMC_STATUS_FSMDPWD_MASK                  (0x38000U)
#define PMC_STATUS_FSMDPWD_SHIFT                 (15U)
/*! FSMDPWD - DEEP POWER DOWN Finite State Machine (FSM) status. */
#define PMC_STATUS_FSMDPWD(x)                    (((uint32_t)(((uint32_t)(x)) << PMC_STATUS_FSMDPWD_SHIFT)) & PMC_STATUS_FSMDPWD_MASK)

#define PMC_STATUS_BOOTMODE_MASK                 (0xC0000U)
#define PMC_STATUS_BOOTMODE_SHIFT                (18U)
/*! BOOTMODE - Latest IC Boot cause:.
 *  0b00..Latest IC boot was a Full power cycle boot sequence (PoR, Pin Reset, Brown Out Detectors Reset, Software Reset).
 *  0b01..Latest IC boot was from DEEP SLEEP low power mode..
 *  0b10..Latest IC boot was from POWER DOWN low power mode..
 *  0b11..Latest IC boot was from DEEP POWER DOWN low power mode..
 */
#define PMC_STATUS_BOOTMODE(x)                   (((uint32_t)(((uint32_t)(x)) << PMC_STATUS_BOOTMODE_SHIFT)) & PMC_STATUS_BOOTMODE_MASK)

#define PMC_STATUS_WAFERTESTDONEVECT_MASK        (0xF0000000U)
#define PMC_STATUS_WAFERTESTDONEVECT_SHIFT       (28U)
/*! WAFERTESTDONEVECT - Indicates cuurent status of wafer test level. */
#define PMC_STATUS_WAFERTESTDONEVECT(x)          (((uint32_t)(((uint32_t)(x)) << PMC_STATUS_WAFERTESTDONEVECT_SHIFT)) & PMC_STATUS_WAFERTESTDONEVECT_MASK)
/*! @} */

/*! @name RESETCTRL - Reset Control [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset] */
/*! @{ */

#define PMC_RESETCTRL_DPDWAKEUPRESETENABLE_MASK  (0x1U)
#define PMC_RESETCTRL_DPDWAKEUPRESETENABLE_SHIFT (0U)
/*! DPDWAKEUPRESETENABLE - Wake-up from DEEP POWER DOWN reset event (either from wake up I/O or RTC or OS Event Timer).
 *  0b0..Reset event from DEEP POWER DOWN mode is disable.
 *  0b1..Reset event from DEEP POWER DOWN mode is enable.
 */
#define PMC_RESETCTRL_DPDWAKEUPRESETENABLE(x)    (((uint32_t)(((uint32_t)(x)) << PMC_RESETCTRL_DPDWAKEUPRESETENABLE_SHIFT)) & PMC_RESETCTRL_DPDWAKEUPRESETENABLE_MASK)

#define PMC_RESETCTRL_SWRRESETENABLE_MASK        (0x8U)
#define PMC_RESETCTRL_SWRRESETENABLE_SHIFT       (3U)
/*! SWRRESETENABLE - Software reset enable.
 *  0b0..Software reset is disable.
 *  0b1..Software reset is enable.
 */
#define PMC_RESETCTRL_SWRRESETENABLE(x)          (((uint32_t)(((uint32_t)(x)) << PMC_RESETCTRL_SWRRESETENABLE_SHIFT)) & PMC_RESETCTRL_SWRRESETENABLE_MASK)

#define PMC_RESETCTRL_BODVBATRESETENA_SECURE_MASK (0x30U)
#define PMC_RESETCTRL_BODVBATRESETENA_SECURE_SHIFT (4U)
/*! BODVBATRESETENA_SECURE - BOD VBAT reset enable.
 *  0b10..BOD VBAT reset is disable.
 *  0b01..Any other value than b10, BOD VBAT reset is enable.
 */
#define PMC_RESETCTRL_BODVBATRESETENA_SECURE(x)  (((uint32_t)(((uint32_t)(x)) << PMC_RESETCTRL_BODVBATRESETENA_SECURE_SHIFT)) & PMC_RESETCTRL_BODVBATRESETENA_SECURE_MASK)

#define PMC_RESETCTRL_BODCORERESETENA_SECURE_MASK (0xC0U)
#define PMC_RESETCTRL_BODCORERESETENA_SECURE_SHIFT (6U)
/*! BODCORERESETENA_SECURE - BOD Core reset enable.
 *  0b10..BOD Core reset is disable.
 *  0b01..Any other value than b10, BOD Core reset is enable.
 */
#define PMC_RESETCTRL_BODCORERESETENA_SECURE(x)  (((uint32_t)(((uint32_t)(x)) << PMC_RESETCTRL_BODCORERESETENA_SECURE_SHIFT)) & PMC_RESETCTRL_BODCORERESETENA_SECURE_MASK)

#define PMC_RESETCTRL_BODVBATRESETENA_SECURE_DP_MASK (0x30000000U)
#define PMC_RESETCTRL_BODVBATRESETENA_SECURE_DP_SHIFT (28U)
/*! BODVBATRESETENA_SECURE_DP - BOD VBAT reset enable.
 *  0b10..BOD VBAT reset is disable.
 *  0b01..Any other value than b10, BOD VBAT reset is enable.
 */
#define PMC_RESETCTRL_BODVBATRESETENA_SECURE_DP(x) (((uint32_t)(((uint32_t)(x)) << PMC_RESETCTRL_BODVBATRESETENA_SECURE_DP_SHIFT)) & PMC_RESETCTRL_BODVBATRESETENA_SECURE_DP_MASK)

#define PMC_RESETCTRL_BODCORERESETENA_SECURE_DP_MASK (0xC0000000U)
#define PMC_RESETCTRL_BODCORERESETENA_SECURE_DP_SHIFT (30U)
/*! BODCORERESETENA_SECURE_DP - BOD Core reset enable.
 *  0b10..BOD Core reset is disable.
 *  0b01..Any other value than b10, BOD Core reset is enable.
 */
#define PMC_RESETCTRL_BODCORERESETENA_SECURE_DP(x) (((uint32_t)(((uint32_t)(x)) << PMC_RESETCTRL_BODCORERESETENA_SECURE_DP_SHIFT)) & PMC_RESETCTRL_BODCORERESETENA_SECURE_DP_MASK)
/*! @} */

/*! @name DCDC0 - DCDC (first) control register [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset] */
/*! @{ */

#define PMC_DCDC0_RC_MASK                        (0x3FU)
#define PMC_DCDC0_RC_SHIFT                       (0U)
/*! RC - Constant On-Time calibration. */
#define PMC_DCDC0_RC(x)                          (((uint32_t)(((uint32_t)(x)) << PMC_DCDC0_RC_SHIFT)) & PMC_DCDC0_RC_MASK)

#define PMC_DCDC0_ICOMP_MASK                     (0xC0U)
#define PMC_DCDC0_ICOMP_SHIFT                    (6U)
/*! ICOMP - Select the type of ZCD comparator. */
#define PMC_DCDC0_ICOMP(x)                       (((uint32_t)(((uint32_t)(x)) << PMC_DCDC0_ICOMP_SHIFT)) & PMC_DCDC0_ICOMP_MASK)

#define PMC_DCDC0_ISEL_MASK                      (0x300U)
#define PMC_DCDC0_ISEL_SHIFT                     (8U)
/*! ISEL - Alter Internal biasing currents. */
#define PMC_DCDC0_ISEL(x)                        (((uint32_t)(((uint32_t)(x)) << PMC_DCDC0_ISEL_SHIFT)) & PMC_DCDC0_ISEL_MASK)

#define PMC_DCDC0_ICENABLE_MASK                  (0x400U)
#define PMC_DCDC0_ICENABLE_SHIFT                 (10U)
/*! ICENABLE - Selection of auto scaling of COT period with variations in VDD. */
#define PMC_DCDC0_ICENABLE(x)                    (((uint32_t)(((uint32_t)(x)) << PMC_DCDC0_ICENABLE_SHIFT)) & PMC_DCDC0_ICENABLE_MASK)

#define PMC_DCDC0_TMOS_MASK                      (0xF800U)
#define PMC_DCDC0_TMOS_SHIFT                     (11U)
/*! TMOS - One-shot generator reference current trimming signal. */
#define PMC_DCDC0_TMOS(x)                        (((uint32_t)(((uint32_t)(x)) << PMC_DCDC0_TMOS_SHIFT)) & PMC_DCDC0_TMOS_MASK)

#define PMC_DCDC0_DISABLEISENSE_MASK             (0x10000U)
#define PMC_DCDC0_DISABLEISENSE_SHIFT            (16U)
/*! DISABLEISENSE - Disable Current sensing. */
#define PMC_DCDC0_DISABLEISENSE(x)               (((uint32_t)(((uint32_t)(x)) << PMC_DCDC0_DISABLEISENSE_SHIFT)) & PMC_DCDC0_DISABLEISENSE_MASK)

#define PMC_DCDC0_VOUT_MASK                      (0x1E0000U)
#define PMC_DCDC0_VOUT_SHIFT                     (17U)
/*! VOUT - Set output regulation voltage.
 *  0b0000..0.95 V.
 *  0b0001..0.975 V.
 *  0b0010..1 V.
 *  0b0011..1.025 V.
 *  0b0100..1.05 V.
 *  0b0101..1.075 V.
 *  0b0110..1.1 V.
 *  0b0111..1.125 V.
 *  0b1000..1.15 V.
 *  0b1001..1.175 V.
 *  0b1010..1.2 V.
 */
#define PMC_DCDC0_VOUT(x)                        (((uint32_t)(((uint32_t)(x)) << PMC_DCDC0_VOUT_SHIFT)) & PMC_DCDC0_VOUT_MASK)

#define PMC_DCDC0_SLICINGENABLE_MASK             (0x200000U)
#define PMC_DCDC0_SLICINGENABLE_SHIFT            (21U)
/*! SLICINGENABLE - Enable staggered switching of power switches. */
#define PMC_DCDC0_SLICINGENABLE(x)               (((uint32_t)(((uint32_t)(x)) << PMC_DCDC0_SLICINGENABLE_SHIFT)) & PMC_DCDC0_SLICINGENABLE_MASK)

#define PMC_DCDC0_INDUCTORCLAMPENABLE_MASK       (0x400000U)
#define PMC_DCDC0_INDUCTORCLAMPENABLE_SHIFT      (22U)
/*! INDUCTORCLAMPENABLE - Enable shorting of Inductor during PFM idle time. */
#define PMC_DCDC0_INDUCTORCLAMPENABLE(x)         (((uint32_t)(((uint32_t)(x)) << PMC_DCDC0_INDUCTORCLAMPENABLE_SHIFT)) & PMC_DCDC0_INDUCTORCLAMPENABLE_MASK)

#define PMC_DCDC0_VOUT_PWD_MASK                  (0x7800000U)
#define PMC_DCDC0_VOUT_PWD_SHIFT                 (23U)
/*! VOUT_PWD - Set output regulation voltage during Deep Sleep. */
#define PMC_DCDC0_VOUT_PWD(x)                    (((uint32_t)(((uint32_t)(x)) << PMC_DCDC0_VOUT_PWD_SHIFT)) & PMC_DCDC0_VOUT_PWD_MASK)
/*! @} */

/*! @name DCDC1 - DCDC (second) control register [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset] */
/*! @{ */

#define PMC_DCDC1_RTRIMOFFET_MASK                (0xFU)
#define PMC_DCDC1_RTRIMOFFET_SHIFT               (0U)
/*! RTRIMOFFET - Adjust the offset voltage of BJT based comparator. */
#define PMC_DCDC1_RTRIMOFFET(x)                  (((uint32_t)(((uint32_t)(x)) << PMC_DCDC1_RTRIMOFFET_SHIFT)) & PMC_DCDC1_RTRIMOFFET_MASK)

#define PMC_DCDC1_RSENSETRIM_MASK                (0xF0U)
#define PMC_DCDC1_RSENSETRIM_SHIFT               (4U)
/*! RSENSETRIM - Adjust Max inductor peak current limiting. */
#define PMC_DCDC1_RSENSETRIM(x)                  (((uint32_t)(((uint32_t)(x)) << PMC_DCDC1_RSENSETRIM_SHIFT)) & PMC_DCDC1_RSENSETRIM_MASK)

#define PMC_DCDC1_DTESTENABLE_MASK               (0x100U)
#define PMC_DCDC1_DTESTENABLE_SHIFT              (8U)
/*! DTESTENABLE - Enable Digital test signals. */
#define PMC_DCDC1_DTESTENABLE(x)                 (((uint32_t)(((uint32_t)(x)) << PMC_DCDC1_DTESTENABLE_SHIFT)) & PMC_DCDC1_DTESTENABLE_MASK)

#define PMC_DCDC1_SETCURVE_MASK                  (0x600U)
#define PMC_DCDC1_SETCURVE_SHIFT                 (9U)
/*! SETCURVE - Bandgap calibration parameter. */
#define PMC_DCDC1_SETCURVE(x)                    (((uint32_t)(((uint32_t)(x)) << PMC_DCDC1_SETCURVE_SHIFT)) & PMC_DCDC1_SETCURVE_MASK)

#define PMC_DCDC1_SETDC_MASK                     (0x7800U)
#define PMC_DCDC1_SETDC_SHIFT                    (11U)
/*! SETDC - Bandgap calibration parameter. */
#define PMC_DCDC1_SETDC(x)                       (((uint32_t)(((uint32_t)(x)) << PMC_DCDC1_SETDC_SHIFT)) & PMC_DCDC1_SETDC_MASK)

#define PMC_DCDC1_DTESTSEL_MASK                  (0x38000U)
#define PMC_DCDC1_DTESTSEL_SHIFT                 (15U)
/*! DTESTSEL - Select the output signal for test. */
#define PMC_DCDC1_DTESTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << PMC_DCDC1_DTESTSEL_SHIFT)) & PMC_DCDC1_DTESTSEL_MASK)

#define PMC_DCDC1_ISCALEENABLE_MASK              (0x40000U)
#define PMC_DCDC1_ISCALEENABLE_SHIFT             (18U)
/*! ISCALEENABLE - Modify COT behavior. */
#define PMC_DCDC1_ISCALEENABLE(x)                (((uint32_t)(((uint32_t)(x)) << PMC_DCDC1_ISCALEENABLE_SHIFT)) & PMC_DCDC1_ISCALEENABLE_MASK)

#define PMC_DCDC1_FORCEBYPASS_MASK               (0x80000U)
#define PMC_DCDC1_FORCEBYPASS_SHIFT              (19U)
/*! FORCEBYPASS - Force bypass mode. */
#define PMC_DCDC1_FORCEBYPASS(x)                 (((uint32_t)(((uint32_t)(x)) << PMC_DCDC1_FORCEBYPASS_SHIFT)) & PMC_DCDC1_FORCEBYPASS_MASK)

#define PMC_DCDC1_TRIMAUTOCOT_MASK               (0xF00000U)
#define PMC_DCDC1_TRIMAUTOCOT_SHIFT              (20U)
/*! TRIMAUTOCOT - Change the scaling ratio of the feedforward compensation. */
#define PMC_DCDC1_TRIMAUTOCOT(x)                 (((uint32_t)(((uint32_t)(x)) << PMC_DCDC1_TRIMAUTOCOT_SHIFT)) & PMC_DCDC1_TRIMAUTOCOT_MASK)

#define PMC_DCDC1_FORCEFULLCYCLE_MASK            (0x1000000U)
#define PMC_DCDC1_FORCEFULLCYCLE_SHIFT           (24U)
/*! FORCEFULLCYCLE - Force full PFM PMOS and NMOS cycle. */
#define PMC_DCDC1_FORCEFULLCYCLE(x)              (((uint32_t)(((uint32_t)(x)) << PMC_DCDC1_FORCEFULLCYCLE_SHIFT)) & PMC_DCDC1_FORCEFULLCYCLE_MASK)

#define PMC_DCDC1_LCENABLE_MASK                  (0x2000000U)
#define PMC_DCDC1_LCENABLE_SHIFT                 (25U)
/*! LCENABLE - Change the range of the peak detector of current inside the inductor. */
#define PMC_DCDC1_LCENABLE(x)                    (((uint32_t)(((uint32_t)(x)) << PMC_DCDC1_LCENABLE_SHIFT)) & PMC_DCDC1_LCENABLE_MASK)

#define PMC_DCDC1_TOFF_MASK                      (0x7C000000U)
#define PMC_DCDC1_TOFF_SHIFT                     (26U)
/*! TOFF - Constant Off-Time calibration input. */
#define PMC_DCDC1_TOFF(x)                        (((uint32_t)(((uint32_t)(x)) << PMC_DCDC1_TOFF_SHIFT)) & PMC_DCDC1_TOFF_MASK)

#define PMC_DCDC1_TOFFENABLE_MASK                (0x80000000U)
#define PMC_DCDC1_TOFFENABLE_SHIFT               (31U)
/*! TOFFENABLE - Enable Constant Off-Time feature. */
#define PMC_DCDC1_TOFFENABLE(x)                  (((uint32_t)(((uint32_t)(x)) << PMC_DCDC1_TOFFENABLE_SHIFT)) & PMC_DCDC1_TOFFENABLE_MASK)
/*! @} */

/*! @name LDOPMU - Power Management Unit (PMU) and Always-On domains LDO control [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset] */
/*! @{ */

#define PMC_LDOPMU_VADJ_MASK                     (0x1FU)
#define PMC_LDOPMU_VADJ_SHIFT                    (0U)
/*! VADJ - Sets the Always-On domain LDO output level.
 *  0b00000..1.22 V.
 *  0b00001..0.7 V.
 *  0b00010..0.725 V.
 *  0b00011..0.75 V.
 *  0b00100..0.775 V.
 *  0b00101..0.8 V.
 *  0b00110..0.825 V.
 *  0b00111..0.85 V.
 *  0b01000..0.875 V.
 *  0b01001..0.9 V.
 *  0b01010..0.96 V.
 *  0b01011..0.97 V.
 *  0b01100..0.98 V.
 *  0b01101..0.99 V.
 *  0b01110..1 V.
 *  0b01111..1.01 V.
 *  0b10000..1.02 V.
 *  0b10001..1.03 V.
 *  0b10010..1.04 V.
 *  0b10011..1.05 V.
 *  0b10100..1.06 V.
 *  0b10101..1.07 V.
 *  0b10110..1.08 V.
 *  0b10111..1.09 V.
 *  0b11000..1.1 V.
 *  0b11001..1.11 V.
 *  0b11010..1.12 V.
 *  0b11011..1.13 V.
 *  0b11100..1.14 V.
 *  0b11101..1.15 V.
 *  0b11110..1.16 V.
 *  0b11111..1.22 V.
 */
#define PMC_LDOPMU_VADJ(x)                       (((uint32_t)(((uint32_t)(x)) << PMC_LDOPMU_VADJ_SHIFT)) & PMC_LDOPMU_VADJ_MASK)

#define PMC_LDOPMU_VADJ_PWD_MASK                 (0x3E0U)
#define PMC_LDOPMU_VADJ_PWD_SHIFT                (5U)
/*! VADJ_PWD - Sets the Always-On domain LDO output level in all power down modes. */
#define PMC_LDOPMU_VADJ_PWD(x)                   (((uint32_t)(((uint32_t)(x)) << PMC_LDOPMU_VADJ_PWD_SHIFT)) & PMC_LDOPMU_VADJ_PWD_MASK)

#define PMC_LDOPMU_VADJ_BOOST_MASK               (0x7C00U)
#define PMC_LDOPMU_VADJ_BOOST_SHIFT              (10U)
/*! VADJ_BOOST - Sets the Always-On domain LDO Boost output level. */
#define PMC_LDOPMU_VADJ_BOOST(x)                 (((uint32_t)(((uint32_t)(x)) << PMC_LDOPMU_VADJ_BOOST_SHIFT)) & PMC_LDOPMU_VADJ_BOOST_MASK)

#define PMC_LDOPMU_VADJ_BOOST_PWD_MASK           (0xF8000U)
#define PMC_LDOPMU_VADJ_BOOST_PWD_SHIFT          (15U)
/*! VADJ_BOOST_PWD - Sets the Always-On domain LDO Boost output level in all power down modes. */
#define PMC_LDOPMU_VADJ_BOOST_PWD(x)             (((uint32_t)(((uint32_t)(x)) << PMC_LDOPMU_VADJ_BOOST_PWD_SHIFT)) & PMC_LDOPMU_VADJ_BOOST_PWD_MASK)

#define PMC_LDOPMU_BLEED_MASK                    (0x100000U)
#define PMC_LDOPMU_BLEED_SHIFT                   (20U)
/*! BLEED - Controls LDOMEM bleed current.
 *  0b0..Bleed current is disable.
 *  0b1..Bleed current is enable.
 */
#define PMC_LDOPMU_BLEED(x)                      (((uint32_t)(((uint32_t)(x)) << PMC_LDOPMU_BLEED_SHIFT)) & PMC_LDOPMU_BLEED_MASK)

#define PMC_LDOPMU_BOOST_ENA_MASK                (0x1000000U)
#define PMC_LDOPMU_BOOST_ENA_SHIFT               (24U)
/*! BOOST_ENA - Control the LDO AO boost mode in ACTIVE mode.
 *  0b0..LDO AO Boost Mode is disable.
 *  0b1..LDO AO Boost Mode is enable.
 */
#define PMC_LDOPMU_BOOST_ENA(x)                  (((uint32_t)(((uint32_t)(x)) << PMC_LDOPMU_BOOST_ENA_SHIFT)) & PMC_LDOPMU_BOOST_ENA_MASK)

#define PMC_LDOPMU_BOOST_ENA_PWD_MASK            (0x2000000U)
#define PMC_LDOPMU_BOOST_ENA_PWD_SHIFT           (25U)
/*! BOOST_ENA_PWD - Control the LDO AO boost mode in the different low power modes (DEEP SLEEP, POWERDOWN, and DEEP POWER DOWN).
 *  0b0..LDO AO Boost Mode is disable.
 *  0b1..LDO AO Boost Mode is enable.
 */
#define PMC_LDOPMU_BOOST_ENA_PWD(x)              (((uint32_t)(((uint32_t)(x)) << PMC_LDOPMU_BOOST_ENA_PWD_SHIFT)) & PMC_LDOPMU_BOOST_ENA_PWD_MASK)
/*! @} */

/*! @name BODVBAT - VBAT Brown Out Dectector (BoD) control register [Reset by: PoR, Pin Reset, Software Reset] */
/*! @{ */

#define PMC_BODVBAT_TRIGLVL_MASK                 (0x1FU)
#define PMC_BODVBAT_TRIGLVL_SHIFT                (0U)
/*! TRIGLVL - BoD trigger level.
 *  0b00000..1.00 V.
 *  0b00001..1.10 V.
 *  0b00010..1.20 V.
 *  0b00011..1.30 V.
 *  0b00100..1.40 V.
 *  0b00101..1.50 V.
 *  0b00110..1.60 V.
 *  0b00111..1.65 V.
 *  0b01000..1.70 V.
 *  0b01001..1.75 V.
 *  0b01010..1.80 V.
 *  0b01011..1.90 V.
 *  0b01100..2.00 V.
 *  0b01101..2.10 V.
 *  0b01110..2.20 V.
 *  0b01111..2.30 V.
 *  0b10000..2.40 V.
 *  0b10001..2.50 V.
 *  0b10010..2.60 V.
 *  0b10011..2.70 V.
 *  0b10100..2.806 V.
 *  0b10101..2.90 V.
 *  0b10110..3.00 V.
 *  0b10111..3.10 V.
 *  0b11000..3.20 V.
 *  0b11001..3.30 V.
 *  0b11010..3.30 V.
 *  0b11011..3.30 V.
 *  0b11100..3.30 V.
 *  0b11101..3.30 V.
 *  0b11110..3.30 V.
 *  0b11111..3.30 V.
 */
#define PMC_BODVBAT_TRIGLVL(x)                   (((uint32_t)(((uint32_t)(x)) << PMC_BODVBAT_TRIGLVL_SHIFT)) & PMC_BODVBAT_TRIGLVL_MASK)

#define PMC_BODVBAT_HYST_MASK                    (0x60U)
#define PMC_BODVBAT_HYST_SHIFT                   (5U)
/*! HYST - BoD Hysteresis control.
 *  0b00..25 mV.
 *  0b01..50 mV.
 *  0b10..75 mV.
 *  0b11..100 mV.
 */
#define PMC_BODVBAT_HYST(x)                      (((uint32_t)(((uint32_t)(x)) << PMC_BODVBAT_HYST_SHIFT)) & PMC_BODVBAT_HYST_MASK)
/*! @} */

/*! @name REFFASTWKUP - Analog References fast wake-up Control register [Reset by: PoR] */
/*! @{ */

#define PMC_REFFASTWKUP_LPWKUP_MASK              (0x1U)
#define PMC_REFFASTWKUP_LPWKUP_SHIFT             (0U)
/*! LPWKUP - Analog References fast wake-up in case of wake-up from a low power mode (DEEP SLEEP, POWER DOWN and DEEP POWER DOWN): .
 *  0b0..Analog References fast wake-up feature is disabled in case of wake-up from any Low power mode.
 *  0b1..Analog References fast wake-up feature is enabled in case of wake-up from any Low power mode.
 */
#define PMC_REFFASTWKUP_LPWKUP(x)                (((uint32_t)(((uint32_t)(x)) << PMC_REFFASTWKUP_LPWKUP_SHIFT)) & PMC_REFFASTWKUP_LPWKUP_MASK)

#define PMC_REFFASTWKUP_HWWKUP_MASK              (0x2U)
#define PMC_REFFASTWKUP_HWWKUP_SHIFT             (1U)
/*! HWWKUP - Analog References fast wake-up in case of Hardware Pin reset: .
 *  0b0..Analog References fast wake-up feature is disabled in case of Hardware Pin reset.
 *  0b1..Analog References fast wake-up feature is enabled in case of Hardware Pin reset.
 */
#define PMC_REFFASTWKUP_HWWKUP(x)                (((uint32_t)(((uint32_t)(x)) << PMC_REFFASTWKUP_HWWKUP_SHIFT)) & PMC_REFFASTWKUP_HWWKUP_MASK)
/*! @} */

/*! @name XTAL32K - 32 KHz Crystal oscillator (XTAL) control register [Reset by: PoR, Brown Out Detectors Reset] */
/*! @{ */

#define PMC_XTAL32K_IREF_MASK                    (0x6U)
#define PMC_XTAL32K_IREF_SHIFT                   (1U)
/*! IREF - reference output current selection inputs. */
#define PMC_XTAL32K_IREF(x)                      (((uint32_t)(((uint32_t)(x)) << PMC_XTAL32K_IREF_SHIFT)) & PMC_XTAL32K_IREF_MASK)

#define PMC_XTAL32K_TEST_MASK                    (0x8U)
#define PMC_XTAL32K_TEST_SHIFT                   (3U)
/*! TEST - Oscillator Test Mode. */
#define PMC_XTAL32K_TEST(x)                      (((uint32_t)(((uint32_t)(x)) << PMC_XTAL32K_TEST_SHIFT)) & PMC_XTAL32K_TEST_MASK)

#define PMC_XTAL32K_IBIAS_MASK                   (0x30U)
#define PMC_XTAL32K_IBIAS_SHIFT                  (4U)
/*! IBIAS - bias current selection inputs. */
#define PMC_XTAL32K_IBIAS(x)                     (((uint32_t)(((uint32_t)(x)) << PMC_XTAL32K_IBIAS_SHIFT)) & PMC_XTAL32K_IBIAS_MASK)

#define PMC_XTAL32K_AMPL_MASK                    (0xC0U)
#define PMC_XTAL32K_AMPL_SHIFT                   (6U)
/*! AMPL - oscillator amplitude selection inputs. */
#define PMC_XTAL32K_AMPL(x)                      (((uint32_t)(((uint32_t)(x)) << PMC_XTAL32K_AMPL_SHIFT)) & PMC_XTAL32K_AMPL_MASK)

#define PMC_XTAL32K_CAPBANKIN_MASK               (0x7F00U)
#define PMC_XTAL32K_CAPBANKIN_SHIFT              (8U)
/*! CAPBANKIN - Capa bank setting input. */
#define PMC_XTAL32K_CAPBANKIN(x)                 (((uint32_t)(((uint32_t)(x)) << PMC_XTAL32K_CAPBANKIN_SHIFT)) & PMC_XTAL32K_CAPBANKIN_MASK)

#define PMC_XTAL32K_CAPBANKOUT_MASK              (0x3F8000U)
#define PMC_XTAL32K_CAPBANKOUT_SHIFT             (15U)
/*! CAPBANKOUT - Capa bank setting output. */
#define PMC_XTAL32K_CAPBANKOUT(x)                (((uint32_t)(((uint32_t)(x)) << PMC_XTAL32K_CAPBANKOUT_SHIFT)) & PMC_XTAL32K_CAPBANKOUT_MASK)

#define PMC_XTAL32K_CAPTESTSTARTSRCSEL_MASK      (0x400000U)
#define PMC_XTAL32K_CAPTESTSTARTSRCSEL_SHIFT     (22U)
/*! CAPTESTSTARTSRCSEL - Source selection for xo32k_captest_start_ao_set.
 *  0b0..Sourced from CAPTESTSTART.
 *  0b1..Sourced from calibration.
 */
#define PMC_XTAL32K_CAPTESTSTARTSRCSEL(x)        (((uint32_t)(((uint32_t)(x)) << PMC_XTAL32K_CAPTESTSTARTSRCSEL_SHIFT)) & PMC_XTAL32K_CAPTESTSTARTSRCSEL_MASK)

#define PMC_XTAL32K_CAPTESTSTART_MASK            (0x800000U)
#define PMC_XTAL32K_CAPTESTSTART_SHIFT           (23U)
/*! CAPTESTSTART - Start test. */
#define PMC_XTAL32K_CAPTESTSTART(x)              (((uint32_t)(((uint32_t)(x)) << PMC_XTAL32K_CAPTESTSTART_SHIFT)) & PMC_XTAL32K_CAPTESTSTART_MASK)

#define PMC_XTAL32K_CAPTESTENABLE_MASK           (0x1000000U)
#define PMC_XTAL32K_CAPTESTENABLE_SHIFT          (24U)
/*! CAPTESTENABLE - Enable signal for cap test. */
#define PMC_XTAL32K_CAPTESTENABLE(x)             (((uint32_t)(((uint32_t)(x)) << PMC_XTAL32K_CAPTESTENABLE_SHIFT)) & PMC_XTAL32K_CAPTESTENABLE_MASK)

#define PMC_XTAL32K_CAPTESTOSCINSEL_MASK         (0x2000000U)
#define PMC_XTAL32K_CAPTESTOSCINSEL_SHIFT        (25U)
/*! CAPTESTOSCINSEL - Select the input for test.
 *  0b0..Oscillator output pin (osc_out).
 *  0b1..Oscillator input pin (osc_in).
 */
#define PMC_XTAL32K_CAPTESTOSCINSEL(x)           (((uint32_t)(((uint32_t)(x)) << PMC_XTAL32K_CAPTESTOSCINSEL_SHIFT)) & PMC_XTAL32K_CAPTESTOSCINSEL_MASK)
/*! @} */

/*! @name COMP - Analog Comparator control register [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset] */
/*! @{ */

#define PMC_COMP_HYST_MASK                       (0x2U)
#define PMC_COMP_HYST_SHIFT                      (1U)
/*! HYST - Hysteris when hyst = '1'.
 *  0b0..Hysteresis is disable.
 *  0b1..Hysteresis is enable.
 */
#define PMC_COMP_HYST(x)                         (((uint32_t)(((uint32_t)(x)) << PMC_COMP_HYST_SHIFT)) & PMC_COMP_HYST_MASK)

#define PMC_COMP_VREFINPUT_MASK                  (0x4U)
#define PMC_COMP_VREFINPUT_SHIFT                 (2U)
/*! VREFINPUT - Dedicated control bit to select between internal VREF and VDDA (for the resistive ladder).
 *  0b0..Select internal VREF.
 *  0b1..Select VDDA.
 */
#define PMC_COMP_VREFINPUT(x)                    (((uint32_t)(((uint32_t)(x)) << PMC_COMP_VREFINPUT_SHIFT)) & PMC_COMP_VREFINPUT_MASK)

#define PMC_COMP_LOWPOWER_MASK                   (0x8U)
#define PMC_COMP_LOWPOWER_SHIFT                  (3U)
/*! LOWPOWER - Low power mode.
 *  0b0..High speed mode.
 *  0b1..Low power mode (Low speed).
 */
#define PMC_COMP_LOWPOWER(x)                     (((uint32_t)(((uint32_t)(x)) << PMC_COMP_LOWPOWER_SHIFT)) & PMC_COMP_LOWPOWER_MASK)

#define PMC_COMP_PMUX_MASK                       (0x70U)
#define PMC_COMP_PMUX_SHIFT                      (4U)
/*! PMUX - Control word for P multiplexer:.
 *  0b000..VREF (See fiedl VREFINPUT).
 *  0b001..Pin P0_0.
 *  0b010..Pin P0_9.
 *  0b011..Pin P0_18.
 *  0b100..Pin P1_14.
 *  0b101..Pin P2_23.
 */
#define PMC_COMP_PMUX(x)                         (((uint32_t)(((uint32_t)(x)) << PMC_COMP_PMUX_SHIFT)) & PMC_COMP_PMUX_MASK)

#define PMC_COMP_NMUX_MASK                       (0x380U)
#define PMC_COMP_NMUX_SHIFT                      (7U)
/*! NMUX - Control word for N multiplexer:.
 *  0b000..VREF (See field VREFINPUT).
 *  0b001..Pin P0_0.
 *  0b010..Pin P0_9.
 *  0b011..Pin P0_18.
 *  0b100..Pin P1_14.
 *  0b101..Pin P2_23.
 */
#define PMC_COMP_NMUX(x)                         (((uint32_t)(((uint32_t)(x)) << PMC_COMP_NMUX_SHIFT)) & PMC_COMP_NMUX_MASK)

#define PMC_COMP_VREF_MASK                       (0x7C00U)
#define PMC_COMP_VREF_SHIFT                      (10U)
/*! VREF - Control reference voltage step, per steps of (VREFINPUT/31). */
#define PMC_COMP_VREF(x)                         (((uint32_t)(((uint32_t)(x)) << PMC_COMP_VREF_SHIFT)) & PMC_COMP_VREF_MASK)

#define PMC_COMP_FILTERCGF_SAMPLEMODE_MASK       (0x30000U)
#define PMC_COMP_FILTERCGF_SAMPLEMODE_SHIFT      (16U)
/*! FILTERCGF_SAMPLEMODE - Control the filtering of the Analog Comparator output.
 *  0b00..Bypass mode.
 *  0b01..Filter 1 clock period.
 *  0b10..Filter 2 clock period.
 *  0b11..Filter 3 clock period.
 */
#define PMC_COMP_FILTERCGF_SAMPLEMODE(x)         (((uint32_t)(((uint32_t)(x)) << PMC_COMP_FILTERCGF_SAMPLEMODE_SHIFT)) & PMC_COMP_FILTERCGF_SAMPLEMODE_MASK)

#define PMC_COMP_FILTERCGF_CLKDIV_MASK           (0x1C0000U)
#define PMC_COMP_FILTERCGF_CLKDIV_SHIFT          (18U)
/*! FILTERCGF_CLKDIV - Filter Clock divider.
 *  0b000..Filter clock period duration equals 1 Analog Comparator clock period.
 *  0b001..Filter clock period duration equals 2 Analog Comparator clock period.
 *  0b010..Filter clock period duration equals 4 Analog Comparator clock period.
 *  0b011..Filter clock period duration equals 8 Analog Comparator clock period.
 *  0b100..Filter clock period duration equals 16 Analog Comparator clock period.
 *  0b101..Filter clock period duration equals 32 Analog Comparator clock period.
 *  0b110..Filter clock period duration equals 64 Analog Comparator clock period.
 *  0b111..Filter clock period duration equals 128 Analog Comparator clock period.
 */
#define PMC_COMP_FILTERCGF_CLKDIV(x)             (((uint32_t)(((uint32_t)(x)) << PMC_COMP_FILTERCGF_CLKDIV_SHIFT)) & PMC_COMP_FILTERCGF_CLKDIV_MASK)
/*! @} */

/*! @name WAKEUPIOCTRL - Deep Power Down wake-up source [Reset by: PoR, Pin Reset, Software Reset] */
/*! @{ */

#define PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP0_MASK  (0x1U)
#define PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP0_SHIFT (0U)
/*! RISINGEDGEWAKEUP0 - Enable / disable detection of rising edge events on Wake Up 0 pin in Deep Power Down modes:.
 *  0b0..Rising edge detection is disable.
 *  0b1..Rising edge detection is enable.
 */
#define PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP0(x)    (((uint32_t)(((uint32_t)(x)) << PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP0_SHIFT)) & PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP0_MASK)

#define PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP0_MASK (0x2U)
#define PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP0_SHIFT (1U)
/*! FALLINGEDGEWAKEUP0 - Enable / disable detection of falling edge events on Wake Up 0 pin in Deep Power Down modes:.
 *  0b0..Falling edge detection is disable.
 *  0b1..Falling edge detection is enable.
 */
#define PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP0(x)   (((uint32_t)(((uint32_t)(x)) << PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP0_SHIFT)) & PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP0_MASK)

#define PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP1_MASK  (0x4U)
#define PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP1_SHIFT (2U)
/*! RISINGEDGEWAKEUP1 - Enable / disable detection of rising edge events on Wake Up 1 pin in Deep Power Down modes:.
 *  0b0..Rising edge detection is disable.
 *  0b1..Rising edge detection is enable.
 */
#define PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP1(x)    (((uint32_t)(((uint32_t)(x)) << PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP1_SHIFT)) & PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP1_MASK)

#define PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP1_MASK (0x8U)
#define PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP1_SHIFT (3U)
/*! FALLINGEDGEWAKEUP1 - Enable / disable detection of falling edge events on Wake Up 1 pin in Deep Power Down modes:.
 *  0b0..Falling edge detection is disable.
 *  0b1..Falling edge detection is enable.
 */
#define PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP1(x)   (((uint32_t)(((uint32_t)(x)) << PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP1_SHIFT)) & PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP1_MASK)

#define PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP2_MASK  (0x10U)
#define PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP2_SHIFT (4U)
/*! RISINGEDGEWAKEUP2 - Enable / disable detection of rising edge events on Wake Up 2 pin in Deep Power Down modes:.
 *  0b0..Rising edge detection is disable.
 *  0b1..Rising edge detection is enable.
 */
#define PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP2(x)    (((uint32_t)(((uint32_t)(x)) << PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP2_SHIFT)) & PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP2_MASK)

#define PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP2_MASK (0x20U)
#define PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP2_SHIFT (5U)
/*! FALLINGEDGEWAKEUP2 - Enable / disable detection of falling edge events on Wake Up 2 pin in Deep Power Down modes:.
 *  0b0..Falling edge detection is disable.
 *  0b1..Falling edge detection is enable.
 */
#define PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP2(x)   (((uint32_t)(((uint32_t)(x)) << PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP2_SHIFT)) & PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP2_MASK)

#define PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP3_MASK  (0x40U)
#define PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP3_SHIFT (6U)
/*! RISINGEDGEWAKEUP3 - Enable / disable detection of rising edge events on Wake Up 3 pin in Deep Power Down modes:.
 *  0b0..Rising edge detection is disable.
 *  0b1..Rising edge detection is enable.
 */
#define PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP3(x)    (((uint32_t)(((uint32_t)(x)) << PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP3_SHIFT)) & PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP3_MASK)

#define PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP3_MASK (0x80U)
#define PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP3_SHIFT (7U)
/*! FALLINGEDGEWAKEUP3 - Enable / disable detection of falling edge events on Wake Up 3 pin in Deep Power Down modes:.
 *  0b0..Falling edge detection is disable.
 *  0b1..Falling edge detection is enable.
 */
#define PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP3(x)   (((uint32_t)(((uint32_t)(x)) << PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP3_SHIFT)) & PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP3_MASK)

#define PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD0_MASK   (0x3000U)
#define PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD0_SHIFT  (12U)
/*! MODEWAKEUPIOPAD0 - Selects function mode (on-chip pull-up/pull-down resistor control).
 *  0b00..Inactive. Inactive (no pull-down/pull-up resistor enabled).
 *  0b01..Pull-down. Pull-down resistor enabled.
 *  0b10..Pull-up. Pull-up resistor enabled.
 *  0b11..Repeater. Repeater mode.
 */
#define PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD0(x)     (((uint32_t)(((uint32_t)(x)) << PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD0_SHIFT)) & PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD0_MASK)

#define PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD1_MASK   (0xC000U)
#define PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD1_SHIFT  (14U)
/*! MODEWAKEUPIOPAD1 - Selects function mode (on-chip pull-up/pull-down resistor control).
 *  0b00..Inactive. Inactive (no pull-down/pull-up resistor enabled).
 *  0b01..Pull-down. Pull-down resistor enabled.
 *  0b10..Pull-up. Pull-up resistor enabled.
 *  0b11..Repeater. Repeater mode.
 */
#define PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD1(x)     (((uint32_t)(((uint32_t)(x)) << PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD1_SHIFT)) & PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD1_MASK)

#define PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD2_MASK   (0x30000U)
#define PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD2_SHIFT  (16U)
/*! MODEWAKEUPIOPAD2 - Selects function mode (on-chip pull-up/pull-down resistor control).
 *  0b00..Inactive. Inactive (no pull-down/pull-up resistor enabled).
 *  0b01..Pull-down. Pull-down resistor enabled.
 *  0b10..Pull-up. Pull-up resistor enabled.
 *  0b11..Repeater. Repeater mode.
 */
#define PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD2(x)     (((uint32_t)(((uint32_t)(x)) << PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD2_SHIFT)) & PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD2_MASK)

#define PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD3_MASK   (0xC0000U)
#define PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD3_SHIFT  (18U)
/*! MODEWAKEUPIOPAD3 - Selects function mode (on-chip pull-up/pull-down resistor control).
 *  0b00..Inactive. Inactive (no pull-down/pull-up resistor enabled).
 *  0b01..Pull-down. Pull-down resistor enabled.
 *  0b10..Pull-up. Pull-up resistor enabled.
 *  0b11..Repeater. Repeater mode.
 */
#define PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD3(x)     (((uint32_t)(((uint32_t)(x)) << PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD3_SHIFT)) & PMC_WAKEUPIOCTRL_MODEWAKEUPIOPAD3_MASK)

#define PMC_WAKEUPIOCTRL_WAKEUPIO_ENABLE_CTRL_MASK (0x100000U)
#define PMC_WAKEUPIOCTRL_WAKEUPIO_ENABLE_CTRL_SHIFT (20U)
/*! WAKEUPIO_ENABLE_CTRL - Enable WAKEUP IO PAD control from MODEWAKEUPIOPAD (bits 12 to 19).
 *  0b0..WAKEUP IO PAD mode control comes from IOCON.
 *  0b1..WAKEUP IO PAD mode control comes from MODEWAKEUPIOPAD (bits 12 to 19).
 */
#define PMC_WAKEUPIOCTRL_WAKEUPIO_ENABLE_CTRL(x) (((uint32_t)(((uint32_t)(x)) << PMC_WAKEUPIOCTRL_WAKEUPIO_ENABLE_CTRL_SHIFT)) & PMC_WAKEUPIOCTRL_WAKEUPIO_ENABLE_CTRL_MASK)

#define PMC_WAKEUPIOCTRL_WAKEUPIO_RSTN_MASK      (0x200000U)
#define PMC_WAKEUPIOCTRL_WAKEUPIO_RSTN_SHIFT     (21U)
/*! WAKEUPIO_RSTN - WAKEUP IO event detector reset control.
 *  0b0..Bloc is reset.
 *  0b1..Bloc is not reset.
 */
#define PMC_WAKEUPIOCTRL_WAKEUPIO_RSTN(x)        (((uint32_t)(((uint32_t)(x)) << PMC_WAKEUPIOCTRL_WAKEUPIO_RSTN_SHIFT)) & PMC_WAKEUPIOCTRL_WAKEUPIO_RSTN_MASK)
/*! @} */

/*! @name WAKEIOCAUSE - Allows to identify the Wake-up I/O source from Deep Power Down mode */
/*! @{ */

#define PMC_WAKEIOCAUSE_WAKEUP0_MASK             (0x1U)
#define PMC_WAKEIOCAUSE_WAKEUP0_SHIFT            (0U)
/*! WAKEUP0 - Allows to identify Wake up I/O 0 as the wake-up source from Deep Power Down mode.
 *  0b0..Last wake up from Deep Power down mode was NOT triggred by wake up I/O 0.
 *  0b1..Last wake up from Deep Power down mode was triggred by wake up I/O 0.
 */
#define PMC_WAKEIOCAUSE_WAKEUP0(x)               (((uint32_t)(((uint32_t)(x)) << PMC_WAKEIOCAUSE_WAKEUP0_SHIFT)) & PMC_WAKEIOCAUSE_WAKEUP0_MASK)

#define PMC_WAKEIOCAUSE_WAKEUP1_MASK             (0x2U)
#define PMC_WAKEIOCAUSE_WAKEUP1_SHIFT            (1U)
/*! WAKEUP1 - Allows to identify Wake up I/O 1 as the wake-up source from Deep Power Down mode.
 *  0b0..Last wake up from Deep Power down mode was NOT triggred by wake up I/O 1.
 *  0b1..Last wake up from Deep Power down mode was triggred by wake up I/O 1.
 */
#define PMC_WAKEIOCAUSE_WAKEUP1(x)               (((uint32_t)(((uint32_t)(x)) << PMC_WAKEIOCAUSE_WAKEUP1_SHIFT)) & PMC_WAKEIOCAUSE_WAKEUP1_MASK)

#define PMC_WAKEIOCAUSE_WAKEUP2_MASK             (0x4U)
#define PMC_WAKEIOCAUSE_WAKEUP2_SHIFT            (2U)
/*! WAKEUP2 - Allows to identify Wake up I/O 2 as the wake-up source from Deep Power Down mode.
 *  0b0..Last wake up from Deep Power down mode was NOT triggred by wake up I/O 2.
 *  0b1..Last wake up from Deep Power down mode was triggred by wake up I/O 2.
 */
#define PMC_WAKEIOCAUSE_WAKEUP2(x)               (((uint32_t)(((uint32_t)(x)) << PMC_WAKEIOCAUSE_WAKEUP2_SHIFT)) & PMC_WAKEIOCAUSE_WAKEUP2_MASK)

#define PMC_WAKEIOCAUSE_WAKEUP3_MASK             (0x8U)
#define PMC_WAKEIOCAUSE_WAKEUP3_SHIFT            (3U)
/*! WAKEUP3 - Allows to identify Wake up I/O 3 as the wake-up source from Deep Power Down mode.
 *  0b0..Last wake up from Deep Power down mode was NOT triggred by wake up I/O 3.
 *  0b1..Last wake up from Deep Power down mode was triggred by wake up I/O 3.
 */
#define PMC_WAKEIOCAUSE_WAKEUP3(x)               (((uint32_t)(((uint32_t)(x)) << PMC_WAKEIOCAUSE_WAKEUP3_SHIFT)) & PMC_WAKEIOCAUSE_WAKEUP3_MASK)
/*! @} */

/*! @name STATUSCLK - FRO and XTAL status register [Reset by: PoR, Brown Out Detectors Reset] */
/*! @{ */

#define PMC_STATUSCLK_XTAL32KOK_MASK             (0x1U)
#define PMC_STATUSCLK_XTAL32KOK_SHIFT            (0U)
/*! XTAL32KOK - XTAL oscillator 32 K OK signal. */
#define PMC_STATUSCLK_XTAL32KOK(x)               (((uint32_t)(((uint32_t)(x)) << PMC_STATUSCLK_XTAL32KOK_SHIFT)) & PMC_STATUSCLK_XTAL32KOK_MASK)

#define PMC_STATUSCLK_XTAL32KOSCFAILURE_MASK     (0x4U)
#define PMC_STATUSCLK_XTAL32KOSCFAILURE_SHIFT    (2U)
/*! XTAL32KOSCFAILURE - XTAL32 KHZ oscillator oscillation failure detection indicator.
 *  0b0..No oscillation failure has been detetced since the last time this bit has been cleared.
 *  0b1..At least one oscillation failure has been detetced since the last time this bit has been cleared.
 */
#define PMC_STATUSCLK_XTAL32KOSCFAILURE(x)       (((uint32_t)(((uint32_t)(x)) << PMC_STATUSCLK_XTAL32KOSCFAILURE_SHIFT)) & PMC_STATUSCLK_XTAL32KOSCFAILURE_MASK)
/*! @} */

/*! @name AOREG1 - General purpose always on domain data storage [Reset by: PoR, Brown Out Detectors Reset] */
/*! @{ */

#define PMC_AOREG1_POR_MASK                      (0x10U)
#define PMC_AOREG1_POR_SHIFT                     (4U)
/*! POR - The last chip reset was caused by a Power On Reset. */
#define PMC_AOREG1_POR(x)                        (((uint32_t)(((uint32_t)(x)) << PMC_AOREG1_POR_SHIFT)) & PMC_AOREG1_POR_MASK)

#define PMC_AOREG1_PADRESET_MASK                 (0x20U)
#define PMC_AOREG1_PADRESET_SHIFT                (5U)
/*! PADRESET - The last chip reset was caused by a Pin Reset. */
#define PMC_AOREG1_PADRESET(x)                   (((uint32_t)(((uint32_t)(x)) << PMC_AOREG1_PADRESET_SHIFT)) & PMC_AOREG1_PADRESET_MASK)

#define PMC_AOREG1_BODRESET_MASK                 (0x40U)
#define PMC_AOREG1_BODRESET_SHIFT                (6U)
/*! BODRESET - The last chip reset was caused by a Brown Out Detector (BoD), either VBAT BoD or Core Logic BoD. */
#define PMC_AOREG1_BODRESET(x)                   (((uint32_t)(((uint32_t)(x)) << PMC_AOREG1_BODRESET_SHIFT)) & PMC_AOREG1_BODRESET_MASK)

#define PMC_AOREG1_SYSTEMRESET_MASK              (0x80U)
#define PMC_AOREG1_SYSTEMRESET_SHIFT             (7U)
/*! SYSTEMRESET - The last chip reset was caused by a System Reset requested by the ARM CPU. */
#define PMC_AOREG1_SYSTEMRESET(x)                (((uint32_t)(((uint32_t)(x)) << PMC_AOREG1_SYSTEMRESET_SHIFT)) & PMC_AOREG1_SYSTEMRESET_MASK)

#define PMC_AOREG1_WDTRESET_MASK                 (0x100U)
#define PMC_AOREG1_WDTRESET_SHIFT                (8U)
/*! WDTRESET - The last chip reset was caused by the Watchdog Timer. */
#define PMC_AOREG1_WDTRESET(x)                   (((uint32_t)(((uint32_t)(x)) << PMC_AOREG1_WDTRESET_SHIFT)) & PMC_AOREG1_WDTRESET_MASK)

#define PMC_AOREG1_SWRRESET_MASK                 (0x200U)
#define PMC_AOREG1_SWRRESET_SHIFT                (9U)
/*! SWRRESET - The last chip reset was caused by a Software event. */
#define PMC_AOREG1_SWRRESET(x)                   (((uint32_t)(((uint32_t)(x)) << PMC_AOREG1_SWRRESET_SHIFT)) & PMC_AOREG1_SWRRESET_MASK)

#define PMC_AOREG1_DPDRESET_WAKEUPIO_MASK        (0x400U)
#define PMC_AOREG1_DPDRESET_WAKEUPIO_SHIFT       (10U)
/*! DPDRESET_WAKEUPIO - The last chip reset was caused by a Wake-up I/O reset event during a Deep Power-Down mode. */
#define PMC_AOREG1_DPDRESET_WAKEUPIO(x)          (((uint32_t)(((uint32_t)(x)) << PMC_AOREG1_DPDRESET_WAKEUPIO_SHIFT)) & PMC_AOREG1_DPDRESET_WAKEUPIO_MASK)

#define PMC_AOREG1_DPDRESET_RTC_MASK             (0x800U)
#define PMC_AOREG1_DPDRESET_RTC_SHIFT            (11U)
/*! DPDRESET_RTC - The last chip reset was caused by an RTC (either RTC Alarm or RTC wake up) reset event during a Deep Power-Down mode. */
#define PMC_AOREG1_DPDRESET_RTC(x)               (((uint32_t)(((uint32_t)(x)) << PMC_AOREG1_DPDRESET_RTC_SHIFT)) & PMC_AOREG1_DPDRESET_RTC_MASK)

#define PMC_AOREG1_DPDRESET_OSTIMER_MASK         (0x1000U)
#define PMC_AOREG1_DPDRESET_OSTIMER_SHIFT        (12U)
/*! DPDRESET_OSTIMER - The last chip reset was caused by an OS Event Timer reset event during a Deep Power-Down mode. */
#define PMC_AOREG1_DPDRESET_OSTIMER(x)           (((uint32_t)(((uint32_t)(x)) << PMC_AOREG1_DPDRESET_OSTIMER_SHIFT)) & PMC_AOREG1_DPDRESET_OSTIMER_MASK)

#define PMC_AOREG1_CDOGRESET_MASK                (0x2000U)
#define PMC_AOREG1_CDOGRESET_SHIFT               (13U)
/*! CDOGRESET - The last chip reset was caused by the code Watchdog. */
#define PMC_AOREG1_CDOGRESET(x)                  (((uint32_t)(((uint32_t)(x)) << PMC_AOREG1_CDOGRESET_SHIFT)) & PMC_AOREG1_CDOGRESET_MASK)

#define PMC_AOREG1_BOOTERRORCOUNTER_MASK         (0xF0000U)
#define PMC_AOREG1_BOOTERRORCOUNTER_SHIFT        (16U)
/*! BOOTERRORCOUNTER - ROM Boot Fatal Error Counter. */
#define PMC_AOREG1_BOOTERRORCOUNTER(x)           (((uint32_t)(((uint32_t)(x)) << PMC_AOREG1_BOOTERRORCOUNTER_SHIFT)) & PMC_AOREG1_BOOTERRORCOUNTER_MASK)
/*! @} */

/*! @name MISCCTRL - Dummy Control bus to PMU [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset] */
/*! @{ */

#define PMC_MISCCTRL_LDODEEPSLEEPREF_MASK        (0x1U)
#define PMC_MISCCTRL_LDODEEPSLEEPREF_SHIFT       (0U)
/*! LDODEEPSLEEPREF - Select LDO Deep Sleep reference source.
 *  0b0..LDO DEEP Sleep uses Flash buffer biasing as reference.
 *  0b1..LDO DEEP Sleep uses Band Gap 0.8V as reference.
 */
#define PMC_MISCCTRL_LDODEEPSLEEPREF(x)          (((uint32_t)(((uint32_t)(x)) << PMC_MISCCTRL_LDODEEPSLEEPREF_SHIFT)) & PMC_MISCCTRL_LDODEEPSLEEPREF_MASK)

#define PMC_MISCCTRL_LDOMEMHIGHZMODE_MASK        (0x2U)
#define PMC_MISCCTRL_LDOMEMHIGHZMODE_SHIFT       (1U)
/*! LDOMEMHIGHZMODE - Control the activation of LDO MEM High Z mode.
 *  0b0..LDO MEM High Z mode is disabled.
 *  0b1..LDO MEM High Z mode is enabled.
 */
#define PMC_MISCCTRL_LDOMEMHIGHZMODE(x)          (((uint32_t)(((uint32_t)(x)) << PMC_MISCCTRL_LDOMEMHIGHZMODE_SHIFT)) & PMC_MISCCTRL_LDOMEMHIGHZMODE_MASK)

#define PMC_MISCCTRL_LOWPWR_FLASH_BUF_MASK       (0x4U)
#define PMC_MISCCTRL_LOWPWR_FLASH_BUF_SHIFT      (2U)
#define PMC_MISCCTRL_LOWPWR_FLASH_BUF(x)         (((uint32_t)(((uint32_t)(x)) << PMC_MISCCTRL_LOWPWR_FLASH_BUF_SHIFT)) & PMC_MISCCTRL_LOWPWR_FLASH_BUF_MASK)

#define PMC_MISCCTRL_MISCCTRL_3_11_MASK          (0xFF8U)
#define PMC_MISCCTRL_MISCCTRL_3_11_SHIFT         (3U)
/*! MISCCTRL_3_11 - Reserved. */
#define PMC_MISCCTRL_MISCCTRL_3_11(x)            (((uint32_t)(((uint32_t)(x)) << PMC_MISCCTRL_MISCCTRL_3_11_SHIFT)) & PMC_MISCCTRL_MISCCTRL_3_11_MASK)

#define PMC_MISCCTRL_DISABLE_BLEED_MASK          (0x1000U)
#define PMC_MISCCTRL_DISABLE_BLEED_SHIFT         (12U)
/*! DISABLE_BLEED - Controls LDO MEM bleed current. This field is expected to be controlled by the
 *    Low Power Software only in DEEP SLEEP low power mode.
 *  0b0..LDO_MEM bleed current is enabled.
 *  0b1..LDO_MEM bleed current is disabled. Should be set before entering in Deep Sleep low power mode and cleared
 *       after wake up from Deep SLeep low power mode.
 */
#define PMC_MISCCTRL_DISABLE_BLEED(x)            (((uint32_t)(((uint32_t)(x)) << PMC_MISCCTRL_DISABLE_BLEED_SHIFT)) & PMC_MISCCTRL_DISABLE_BLEED_MASK)

#define PMC_MISCCTRL_MISCCTRL_13_15_MASK         (0xE000U)
#define PMC_MISCCTRL_MISCCTRL_13_15_SHIFT        (13U)
/*! MISCCTRL_13_15 - Reserved. */
#define PMC_MISCCTRL_MISCCTRL_13_15(x)           (((uint32_t)(((uint32_t)(x)) << PMC_MISCCTRL_MISCCTRL_13_15_SHIFT)) & PMC_MISCCTRL_MISCCTRL_13_15_MASK)
/*! @} */

/*! @name RTCOSC32K - RTC 1 KHZ and 1 Hz clocks source control register [Reset by: PoR, Brown Out Detectors Reset] */
/*! @{ */

#define PMC_RTCOSC32K_SEL_MASK                   (0x1U)
#define PMC_RTCOSC32K_SEL_SHIFT                  (0U)
/*! SEL - Select the 32K oscillator to be used in Deep Power Down Mode for the RTC (either XTAL32KHz or FRO32KHz) .
 *  0b0..FRO 32 KHz.
 *  0b1..XTAL 32KHz.
 */
#define PMC_RTCOSC32K_SEL(x)                     (((uint32_t)(((uint32_t)(x)) << PMC_RTCOSC32K_SEL_SHIFT)) & PMC_RTCOSC32K_SEL_MASK)

#define PMC_RTCOSC32K_CLK1KHZDIV_MASK            (0xEU)
#define PMC_RTCOSC32K_CLK1KHZDIV_SHIFT           (1U)
/*! CLK1KHZDIV - Actual division ratio is : 28 + CLK1KHZDIV. */
#define PMC_RTCOSC32K_CLK1KHZDIV(x)              (((uint32_t)(((uint32_t)(x)) << PMC_RTCOSC32K_CLK1KHZDIV_SHIFT)) & PMC_RTCOSC32K_CLK1KHZDIV_MASK)

#define PMC_RTCOSC32K_CLK1KHZDIVUPDATEREQ_MASK   (0x8000U)
#define PMC_RTCOSC32K_CLK1KHZDIVUPDATEREQ_SHIFT  (15U)
/*! CLK1KHZDIVUPDATEREQ - RTC 1KHz clock Divider status flag. */
#define PMC_RTCOSC32K_CLK1KHZDIVUPDATEREQ(x)     (((uint32_t)(((uint32_t)(x)) << PMC_RTCOSC32K_CLK1KHZDIVUPDATEREQ_SHIFT)) & PMC_RTCOSC32K_CLK1KHZDIVUPDATEREQ_MASK)

#define PMC_RTCOSC32K_CLK1HZDIV_MASK             (0x7FF0000U)
#define PMC_RTCOSC32K_CLK1HZDIV_SHIFT            (16U)
/*! CLK1HZDIV - Actual division ratio is : 31744 + CLK1HZDIV. */
#define PMC_RTCOSC32K_CLK1HZDIV(x)               (((uint32_t)(((uint32_t)(x)) << PMC_RTCOSC32K_CLK1HZDIV_SHIFT)) & PMC_RTCOSC32K_CLK1HZDIV_MASK)

#define PMC_RTCOSC32K_CLK1HZDIVHALT_MASK         (0x40000000U)
#define PMC_RTCOSC32K_CLK1HZDIVHALT_SHIFT        (30U)
/*! CLK1HZDIVHALT - Halts the divider counter. */
#define PMC_RTCOSC32K_CLK1HZDIVHALT(x)           (((uint32_t)(((uint32_t)(x)) << PMC_RTCOSC32K_CLK1HZDIVHALT_SHIFT)) & PMC_RTCOSC32K_CLK1HZDIVHALT_MASK)

#define PMC_RTCOSC32K_CLK1HZDIVUPDATEREQ_MASK    (0x80000000U)
#define PMC_RTCOSC32K_CLK1HZDIVUPDATEREQ_SHIFT   (31U)
/*! CLK1HZDIVUPDATEREQ - RTC 1Hz Divider status flag. */
#define PMC_RTCOSC32K_CLK1HZDIVUPDATEREQ(x)      (((uint32_t)(((uint32_t)(x)) << PMC_RTCOSC32K_CLK1HZDIVUPDATEREQ_SHIFT)) & PMC_RTCOSC32K_CLK1HZDIVUPDATEREQ_MASK)
/*! @} */

/*! @name OSTIMER - OS Timer control register [Reset by: PoR, Brown Out Detectors Reset] */
/*! @{ */

#define PMC_OSTIMER_SOFTRESET_MASK               (0x1U)
#define PMC_OSTIMER_SOFTRESET_SHIFT              (0U)
/*! SOFTRESET - Active high reset. */
#define PMC_OSTIMER_SOFTRESET(x)                 (((uint32_t)(((uint32_t)(x)) << PMC_OSTIMER_SOFTRESET_SHIFT)) & PMC_OSTIMER_SOFTRESET_MASK)

#define PMC_OSTIMER_CLOCKENABLE_MASK             (0x2U)
#define PMC_OSTIMER_CLOCKENABLE_SHIFT            (1U)
/*! CLOCKENABLE - Enable OS event timer clock. */
#define PMC_OSTIMER_CLOCKENABLE(x)               (((uint32_t)(((uint32_t)(x)) << PMC_OSTIMER_CLOCKENABLE_SHIFT)) & PMC_OSTIMER_CLOCKENABLE_MASK)

#define PMC_OSTIMER_DPDWAKEUPENABLE_MASK         (0x4U)
#define PMC_OSTIMER_DPDWAKEUPENABLE_SHIFT        (2U)
/*! DPDWAKEUPENABLE - Wake up enable in Deep Power Down mode (To be used in Enable Deep Power Down mode). */
#define PMC_OSTIMER_DPDWAKEUPENABLE(x)           (((uint32_t)(((uint32_t)(x)) << PMC_OSTIMER_DPDWAKEUPENABLE_SHIFT)) & PMC_OSTIMER_DPDWAKEUPENABLE_MASK)

#define PMC_OSTIMER_OSC32KPD_MASK                (0x8U)
#define PMC_OSTIMER_OSC32KPD_SHIFT               (3U)
/*! OSC32KPD - Oscilator 32KHz (either FRO32KHz or XTAL32KHz according to RTCOSC32K. */
#define PMC_OSTIMER_OSC32KPD(x)                  (((uint32_t)(((uint32_t)(x)) << PMC_OSTIMER_OSC32KPD_SHIFT)) & PMC_OSTIMER_OSC32KPD_MASK)

#define PMC_OSTIMER_OSTIMERCLKSEL_MASK           (0x30U)
#define PMC_OSTIMER_OSTIMERCLKSEL_SHIFT          (4U)
/*! OSTIMERCLKSEL - OS event timer clock select.
 *  0b00..Oscillator 32 kHz clock.
 *  0b01..FRO 1MHz clock.
 *  0b10..Main clock for OS timer.
 *  0b11..No clock.
 */
#define PMC_OSTIMER_OSTIMERCLKSEL(x)             (((uint32_t)(((uint32_t)(x)) << PMC_OSTIMER_OSTIMERCLKSEL_SHIFT)) & PMC_OSTIMER_OSTIMERCLKSEL_MASK)
/*! @} */

/*! @name PDRUNCFG0 - Controls the power to various analog blocks [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset] */
/*! @{ */

#define PMC_PDRUNCFG0_PDEN_BODVBAT_MASK          (0x8U)
#define PMC_PDRUNCFG0_PDEN_BODVBAT_SHIFT         (3U)
/*! PDEN_BODVBAT - Controls power to VBAT Brown Out Detector (BOD).
 *  0b0..BOD VBAT is powered.
 *  0b1..BOD VBAT is powered down.
 */
#define PMC_PDRUNCFG0_PDEN_BODVBAT(x)            (((uint32_t)(((uint32_t)(x)) << PMC_PDRUNCFG0_PDEN_BODVBAT_SHIFT)) & PMC_PDRUNCFG0_PDEN_BODVBAT_MASK)

#define PMC_PDRUNCFG0_PDEN_FRO32K_MASK           (0x40U)
#define PMC_PDRUNCFG0_PDEN_FRO32K_SHIFT          (6U)
/*! PDEN_FRO32K - Controls power to the Free Running Oscillator (FRO) 32 KHz.
 *  0b0..FRO32KHz is powered.
 *  0b1..FRO32KHz is powered down.
 */
#define PMC_PDRUNCFG0_PDEN_FRO32K(x)             (((uint32_t)(((uint32_t)(x)) << PMC_PDRUNCFG0_PDEN_FRO32K_SHIFT)) & PMC_PDRUNCFG0_PDEN_FRO32K_MASK)

#define PMC_PDRUNCFG0_PDEN_XTAL32K_MASK          (0x80U)
#define PMC_PDRUNCFG0_PDEN_XTAL32K_SHIFT         (7U)
/*! PDEN_XTAL32K - Controls power to crystal 32 KHz.
 *  0b0..Crystal 32KHz is powered.
 *  0b1..Crystal 32KHz is powered down.
 */
#define PMC_PDRUNCFG0_PDEN_XTAL32K(x)            (((uint32_t)(((uint32_t)(x)) << PMC_PDRUNCFG0_PDEN_XTAL32K_SHIFT)) & PMC_PDRUNCFG0_PDEN_XTAL32K_MASK)

#define PMC_PDRUNCFG0_PDEN_XTAL32M_MASK          (0x100U)
#define PMC_PDRUNCFG0_PDEN_XTAL32M_SHIFT         (8U)
/*! PDEN_XTAL32M - Controls power to high speed crystal.
 *  0b0..High speed crystal is powered.
 *  0b1..High speed crystal is powered down.
 */
#define PMC_PDRUNCFG0_PDEN_XTAL32M(x)            (((uint32_t)(((uint32_t)(x)) << PMC_PDRUNCFG0_PDEN_XTAL32M_SHIFT)) & PMC_PDRUNCFG0_PDEN_XTAL32M_MASK)

#define PMC_PDRUNCFG0_PDEN_PLL0_MASK             (0x200U)
#define PMC_PDRUNCFG0_PDEN_PLL0_SHIFT            (9U)
/*! PDEN_PLL0 - Controls power to System PLL (also refered as PLL0).
 *  0b0..PLL0 is powered.
 *  0b1..PLL0 is powered down.
 */
#define PMC_PDRUNCFG0_PDEN_PLL0(x)               (((uint32_t)(((uint32_t)(x)) << PMC_PDRUNCFG0_PDEN_PLL0_SHIFT)) & PMC_PDRUNCFG0_PDEN_PLL0_MASK)

#define PMC_PDRUNCFG0_PDEN_PLL1_MASK             (0x400U)
#define PMC_PDRUNCFG0_PDEN_PLL1_SHIFT            (10U)
/*! PDEN_PLL1 - Controls power to USB PLL (also refered as PLL1).
 *  0b0..PLL1 is powered.
 *  0b1..PLL1 is powered down.
 */
#define PMC_PDRUNCFG0_PDEN_PLL1(x)               (((uint32_t)(((uint32_t)(x)) << PMC_PDRUNCFG0_PDEN_PLL1_SHIFT)) & PMC_PDRUNCFG0_PDEN_PLL1_MASK)

#define PMC_PDRUNCFG0_PDEN_USBFSPHY_MASK         (0x800U)
#define PMC_PDRUNCFG0_PDEN_USBFSPHY_SHIFT        (11U)
/*! PDEN_USBFSPHY - Controls power to USB Full Speed phy.
 *  0b0..USB Full Speed phy is powered.
 *  0b1..USB Full Speed phy is powered down.
 */
#define PMC_PDRUNCFG0_PDEN_USBFSPHY(x)           (((uint32_t)(((uint32_t)(x)) << PMC_PDRUNCFG0_PDEN_USBFSPHY_SHIFT)) & PMC_PDRUNCFG0_PDEN_USBFSPHY_MASK)

#define PMC_PDRUNCFG0_PDEN_USBHSPHY_MASK         (0x1000U)
#define PMC_PDRUNCFG0_PDEN_USBHSPHY_SHIFT        (12U)
/*! PDEN_USBHSPHY - Controls power to USB High Speed Phy.
 *  0b0..USB HS phy is powered.
 *  0b1..USB HS phy is powered down.
 */
#define PMC_PDRUNCFG0_PDEN_USBHSPHY(x)           (((uint32_t)(((uint32_t)(x)) << PMC_PDRUNCFG0_PDEN_USBHSPHY_SHIFT)) & PMC_PDRUNCFG0_PDEN_USBHSPHY_MASK)

#define PMC_PDRUNCFG0_PDEN_COMP_MASK             (0x2000U)
#define PMC_PDRUNCFG0_PDEN_COMP_SHIFT            (13U)
/*! PDEN_COMP - Controls power to Analog Comparator.
 *  0b0..Analog Comparator is powered.
 *  0b1..Analog Comparator is powered down.
 */
#define PMC_PDRUNCFG0_PDEN_COMP(x)               (((uint32_t)(((uint32_t)(x)) << PMC_PDRUNCFG0_PDEN_COMP_SHIFT)) & PMC_PDRUNCFG0_PDEN_COMP_MASK)

#define PMC_PDRUNCFG0_PDEN_LDOUSBHS_MASK         (0x40000U)
#define PMC_PDRUNCFG0_PDEN_LDOUSBHS_SHIFT        (18U)
/*! PDEN_LDOUSBHS - Controls power to USB high speed LDO.
 *  0b0..USB high speed LDO is powered.
 *  0b1..USB high speed LDO is powered down.
 */
#define PMC_PDRUNCFG0_PDEN_LDOUSBHS(x)           (((uint32_t)(((uint32_t)(x)) << PMC_PDRUNCFG0_PDEN_LDOUSBHS_SHIFT)) & PMC_PDRUNCFG0_PDEN_LDOUSBHS_MASK)

#define PMC_PDRUNCFG0_PDEN_AUXBIAS_MASK          (0x80000U)
#define PMC_PDRUNCFG0_PDEN_AUXBIAS_SHIFT         (19U)
/*! PDEN_AUXBIAS - Controls power to auxiliary biasing (AUXBIAS)
 *  0b0..auxiliary biasing is powered.
 *  0b1..auxiliary biasing is powered down.
 */
#define PMC_PDRUNCFG0_PDEN_AUXBIAS(x)            (((uint32_t)(((uint32_t)(x)) << PMC_PDRUNCFG0_PDEN_AUXBIAS_SHIFT)) & PMC_PDRUNCFG0_PDEN_AUXBIAS_MASK)

#define PMC_PDRUNCFG0_PDEN_LDOXO32M_MASK         (0x100000U)
#define PMC_PDRUNCFG0_PDEN_LDOXO32M_SHIFT        (20U)
/*! PDEN_LDOXO32M - Controls power to high speed crystal LDO.
 *  0b0..High speed crystal LDO is powered.
 *  0b1..High speed crystal LDO is powered down.
 */
#define PMC_PDRUNCFG0_PDEN_LDOXO32M(x)           (((uint32_t)(((uint32_t)(x)) << PMC_PDRUNCFG0_PDEN_LDOXO32M_SHIFT)) & PMC_PDRUNCFG0_PDEN_LDOXO32M_MASK)

#define PMC_PDRUNCFG0_PDEN_RNG_MASK              (0x400000U)
#define PMC_PDRUNCFG0_PDEN_RNG_SHIFT             (22U)
/*! PDEN_RNG - Controls power to all True Random Number Genetaor (TRNG) clock sources.
 *  0b0..TRNG clocks are powered.
 *  0b1..TRNG clocks are powered down.
 */
#define PMC_PDRUNCFG0_PDEN_RNG(x)                (((uint32_t)(((uint32_t)(x)) << PMC_PDRUNCFG0_PDEN_RNG_SHIFT)) & PMC_PDRUNCFG0_PDEN_RNG_MASK)

#define PMC_PDRUNCFG0_PDEN_PLL0_SSCG_MASK        (0x800000U)
#define PMC_PDRUNCFG0_PDEN_PLL0_SSCG_SHIFT       (23U)
/*! PDEN_PLL0_SSCG - Controls power to System PLL (PLL0) Spread Spectrum module.
 *  0b0..PLL0 Sread spectrum module is powered.
 *  0b1..PLL0 Sread spectrum module is powered down.
 */
#define PMC_PDRUNCFG0_PDEN_PLL0_SSCG(x)          (((uint32_t)(((uint32_t)(x)) << PMC_PDRUNCFG0_PDEN_PLL0_SSCG_SHIFT)) & PMC_PDRUNCFG0_PDEN_PLL0_SSCG_MASK)
/*! @} */

/*! @name PDRUNCFGSET0 - Controls the power to various analog blocks [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset] */
/*! @{ */

#define PMC_PDRUNCFGSET0_PDRUNCFGSET0_MASK       (0xFFFFFFFFU)
#define PMC_PDRUNCFGSET0_PDRUNCFGSET0_SHIFT      (0U)
/*! PDRUNCFGSET0 - Writing ones to this register sets the corresponding bit or bits in the PDRUNCFG0 register, if they are implemented. */
#define PMC_PDRUNCFGSET0_PDRUNCFGSET0(x)         (((uint32_t)(((uint32_t)(x)) << PMC_PDRUNCFGSET0_PDRUNCFGSET0_SHIFT)) & PMC_PDRUNCFGSET0_PDRUNCFGSET0_MASK)
/*! @} */

/*! @name PDRUNCFGCLR0 - Controls the power to various analog blocks [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Deep Power Down Reset, Software Reset] */
/*! @{ */

#define PMC_PDRUNCFGCLR0_PDRUNCFGCLR0_MASK       (0xFFFFFFFFU)
#define PMC_PDRUNCFGCLR0_PDRUNCFGCLR0_SHIFT      (0U)
/*! PDRUNCFGCLR0 - Writing ones to this register clears the corresponding bit or bits in the PDRUNCFG0 register, if they are implemented. */
#define PMC_PDRUNCFGCLR0_PDRUNCFGCLR0(x)         (((uint32_t)(((uint32_t)(x)) << PMC_PDRUNCFGCLR0_PDRUNCFGCLR0_SHIFT)) & PMC_PDRUNCFGCLR0_PDRUNCFGCLR0_MASK)
/*! @} */

/*! @name SRAMCTRL - All SRAMs common control signals [Reset by: PoR, Pin Reset, Brown Out Detectors Reset, Software Reset] */
/*! @{ */

#define PMC_SRAMCTRL_SMB_MASK                    (0x3U)
#define PMC_SRAMCTRL_SMB_SHIFT                   (0U)
/*! SMB - Source Biasing voltage.
 *  0b00..Low leakage.
 *  0b01..Medium leakage.
 *  0b10..Highest leakage.
 *  0b11..Disable.
 */
#define PMC_SRAMCTRL_SMB(x)                      (((uint32_t)(((uint32_t)(x)) << PMC_SRAMCTRL_SMB_SHIFT)) & PMC_SRAMCTRL_SMB_MASK)

#define PMC_SRAMCTRL_RM_MASK                     (0x1CU)
#define PMC_SRAMCTRL_RM_SHIFT                    (2U)
/*! RM - Read Margin control settings. */
#define PMC_SRAMCTRL_RM(x)                       (((uint32_t)(((uint32_t)(x)) << PMC_SRAMCTRL_RM_SHIFT)) & PMC_SRAMCTRL_RM_MASK)

#define PMC_SRAMCTRL_WM_MASK                     (0xE0U)
#define PMC_SRAMCTRL_WM_SHIFT                    (5U)
/*! WM - Write Margin control settings. */
#define PMC_SRAMCTRL_WM(x)                       (((uint32_t)(((uint32_t)(x)) << PMC_SRAMCTRL_WM_SHIFT)) & PMC_SRAMCTRL_WM_MASK)

#define PMC_SRAMCTRL_WRME_MASK                   (0x100U)
#define PMC_SRAMCTRL_WRME_SHIFT                  (8U)
/*! WRME - Write read margin enable. */
#define PMC_SRAMCTRL_WRME(x)                     (((uint32_t)(((uint32_t)(x)) << PMC_SRAMCTRL_WRME_SHIFT)) & PMC_SRAMCTRL_WRME_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group PMC_Register_Masks */


/*!
 * @}
 */ /* end of group PMC_Peripheral_Access_Layer */


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


#endif  /* PMC_H_ */


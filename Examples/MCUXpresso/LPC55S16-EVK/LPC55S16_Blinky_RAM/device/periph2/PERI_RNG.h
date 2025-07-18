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
**         CMSIS Peripheral Access Layer for RNG
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
 * @file RNG.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for RNG
 *
 * CMSIS Peripheral Access Layer for RNG
 */

#if !defined(RNG_H_)
#define RNG_H_                                   /**< Symbol preventing repeated inclusion */

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
   -- RNG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RNG_Peripheral_Access_Layer RNG Peripheral Access Layer
 * @{
 */

/** RNG - Register Layout Typedef */
typedef struct {
  __I  uint32_t RANDOM_NUMBER;                     /**< This register contains a random 32 bit number which is computed on demand, at each time it is read, offset: 0x0 */
  __IO uint32_t ENCRYPTED_NUMBER;                  /**< This register contains a random 32 bit number which is pre-computed, offset: 0x4 */
  __I  uint32_t COUNTER_VAL;                       /**< offset: 0x8 */
  __IO uint32_t COUNTER_CFG;                       /**< offset: 0xC */
  __IO uint32_t ONLINE_TEST_CFG;                   /**< offset: 0x10 */
  __I  uint32_t ONLINE_TEST_VAL;                   /**< offset: 0x14 */
  __IO uint32_t ENTROPY_INJECT;                    /**< offset: 0x18 */
  __IO uint32_t MISC_CFG;                          /**< offset: 0x1C */
       uint8_t RESERVED_0[4052];
  __IO uint32_t POWERDOWN;                         /**< Powerdown mode (standard but certainly useless here), offset: 0xFF4 */
       uint8_t RESERVED_1[4];
  __I  uint32_t MODULEID;                          /**< IP identifier, offset: 0xFFC */
} RNG_Type;

/* ----------------------------------------------------------------------------
   -- RNG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RNG_Register_Masks RNG Register Masks
 * @{
 */

/*! @name RANDOM_NUMBER - This register contains a random 32 bit number which is computed on demand, at each time it is read */
/*! @{ */

#define RNG_RANDOM_NUMBER_RANDOM_NUMBER_MASK     (0xFFFFFFFFU)
#define RNG_RANDOM_NUMBER_RANDOM_NUMBER_SHIFT    (0U)
/*! RANDOM_NUMBER - This register contains a random 32 bit number which is computed on demand, at each time it is read. */
#define RNG_RANDOM_NUMBER_RANDOM_NUMBER(x)       (((uint32_t)(((uint32_t)(x)) << RNG_RANDOM_NUMBER_RANDOM_NUMBER_SHIFT)) & RNG_RANDOM_NUMBER_RANDOM_NUMBER_MASK)
/*! @} */

/*! @name ENCRYPTED_NUMBER - This register contains a random 32 bit number which is pre-computed */
/*! @{ */

#define RNG_ENCRYPTED_NUMBER_ENCRYPTED_NUMBER_MASK (0xFFFFFFFFU)
#define RNG_ENCRYPTED_NUMBER_ENCRYPTED_NUMBER_SHIFT (0U)
/*! ENCRYPTED_NUMBER - This register contains a random 32 bit number which is pre-computed. */
#define RNG_ENCRYPTED_NUMBER_ENCRYPTED_NUMBER(x) (((uint32_t)(((uint32_t)(x)) << RNG_ENCRYPTED_NUMBER_ENCRYPTED_NUMBER_SHIFT)) & RNG_ENCRYPTED_NUMBER_ENCRYPTED_NUMBER_MASK)
/*! @} */

/*! @name COUNTER_VAL -  */
/*! @{ */

#define RNG_COUNTER_VAL_CLK_RATIO_MASK           (0xFFU)
#define RNG_COUNTER_VAL_CLK_RATIO_SHIFT          (0U)
/*! CLK_RATIO - Gives the ratio between the internal clocks frequencies and the register clock
 *    frequency for evaluation and certification purposes.
 */
#define RNG_COUNTER_VAL_CLK_RATIO(x)             (((uint32_t)(((uint32_t)(x)) << RNG_COUNTER_VAL_CLK_RATIO_SHIFT)) & RNG_COUNTER_VAL_CLK_RATIO_MASK)

#define RNG_COUNTER_VAL_REFRESH_CNT_MASK         (0x3FFF00U)
#define RNG_COUNTER_VAL_REFRESH_CNT_SHIFT        (8U)
/*! REFRESH_CNT - Incremented (till max possible value) each time COUNTER was updated since last reading to any *_NUMBER. */
#define RNG_COUNTER_VAL_REFRESH_CNT(x)           (((uint32_t)(((uint32_t)(x)) << RNG_COUNTER_VAL_REFRESH_CNT_SHIFT)) & RNG_COUNTER_VAL_REFRESH_CNT_MASK)
/*! @} */

/*! @name COUNTER_CFG -  */
/*! @{ */

#define RNG_COUNTER_CFG_MODE_MASK                (0x3U)
#define RNG_COUNTER_CFG_MODE_SHIFT               (0U)
/*! MODE - 00: disabled 01: update once. */
#define RNG_COUNTER_CFG_MODE(x)                  (((uint32_t)(((uint32_t)(x)) << RNG_COUNTER_CFG_MODE_SHIFT)) & RNG_COUNTER_CFG_MODE_MASK)

#define RNG_COUNTER_CFG_CLOCK_SEL_MASK           (0x1CU)
#define RNG_COUNTER_CFG_CLOCK_SEL_SHIFT          (2U)
/*! CLOCK_SEL - Selects the internal clock on which to compute statistics. */
#define RNG_COUNTER_CFG_CLOCK_SEL(x)             (((uint32_t)(((uint32_t)(x)) << RNG_COUNTER_CFG_CLOCK_SEL_SHIFT)) & RNG_COUNTER_CFG_CLOCK_SEL_MASK)

#define RNG_COUNTER_CFG_SHIFT4X_MASK             (0xE0U)
#define RNG_COUNTER_CFG_SHIFT4X_SHIFT            (5U)
/*! SHIFT4X - To be used to add precision to clock_ratio and determine 'entropy refill'. */
#define RNG_COUNTER_CFG_SHIFT4X(x)               (((uint32_t)(((uint32_t)(x)) << RNG_COUNTER_CFG_SHIFT4X_SHIFT)) & RNG_COUNTER_CFG_SHIFT4X_MASK)
/*! @} */

/*! @name ONLINE_TEST_CFG -  */
/*! @{ */

#define RNG_ONLINE_TEST_CFG_ACTIVATE_MASK        (0x1U)
#define RNG_ONLINE_TEST_CFG_ACTIVATE_SHIFT       (0U)
/*! ACTIVATE - 0: disabled 1: activated Update rythm for VAL depends on COUNTER_CFG if data_sel is set to COUNTER. */
#define RNG_ONLINE_TEST_CFG_ACTIVATE(x)          (((uint32_t)(((uint32_t)(x)) << RNG_ONLINE_TEST_CFG_ACTIVATE_SHIFT)) & RNG_ONLINE_TEST_CFG_ACTIVATE_MASK)

#define RNG_ONLINE_TEST_CFG_DATA_SEL_MASK        (0x6U)
#define RNG_ONLINE_TEST_CFG_DATA_SEL_SHIFT       (1U)
/*! DATA_SEL - Selects source on which to apply online test: 00: LSB of COUNTER: raw data from one
 *    or all sources of entropy 01: MSB of COUNTER: raw data from one or all sources of entropy 10:
 *    RANDOM_NUMBER 11: ENCRYPTED_NUMBER 'activate' should be set to 'disabled' before changing this
 *    field.
 */
#define RNG_ONLINE_TEST_CFG_DATA_SEL(x)          (((uint32_t)(((uint32_t)(x)) << RNG_ONLINE_TEST_CFG_DATA_SEL_SHIFT)) & RNG_ONLINE_TEST_CFG_DATA_SEL_MASK)
/*! @} */

/*! @name ONLINE_TEST_VAL -  */
/*! @{ */

#define RNG_ONLINE_TEST_VAL_LIVE_CHI_SQUARED_MASK (0xFU)
#define RNG_ONLINE_TEST_VAL_LIVE_CHI_SQUARED_SHIFT (0U)
/*! LIVE_CHI_SQUARED - This value is updated as described in field 'activate'. */
#define RNG_ONLINE_TEST_VAL_LIVE_CHI_SQUARED(x)  (((uint32_t)(((uint32_t)(x)) << RNG_ONLINE_TEST_VAL_LIVE_CHI_SQUARED_SHIFT)) & RNG_ONLINE_TEST_VAL_LIVE_CHI_SQUARED_MASK)

#define RNG_ONLINE_TEST_VAL_MIN_CHI_SQUARED_MASK (0xF0U)
#define RNG_ONLINE_TEST_VAL_MIN_CHI_SQUARED_SHIFT (4U)
/*! MIN_CHI_SQUARED - This field is reset when 'activate'==0. */
#define RNG_ONLINE_TEST_VAL_MIN_CHI_SQUARED(x)   (((uint32_t)(((uint32_t)(x)) << RNG_ONLINE_TEST_VAL_MIN_CHI_SQUARED_SHIFT)) & RNG_ONLINE_TEST_VAL_MIN_CHI_SQUARED_MASK)

#define RNG_ONLINE_TEST_VAL_MAX_CHI_SQUARED_MASK (0xF00U)
#define RNG_ONLINE_TEST_VAL_MAX_CHI_SQUARED_SHIFT (8U)
/*! MAX_CHI_SQUARED - This field is reset when 'activate'==0. */
#define RNG_ONLINE_TEST_VAL_MAX_CHI_SQUARED(x)   (((uint32_t)(((uint32_t)(x)) << RNG_ONLINE_TEST_VAL_MAX_CHI_SQUARED_SHIFT)) & RNG_ONLINE_TEST_VAL_MAX_CHI_SQUARED_MASK)
/*! @} */

/*! @name ENTROPY_INJECT -  */
/*! @{ */

#define RNG_ENTROPY_INJECT_ENTROPY_MASK          (0xFFFFFFFFU)
#define RNG_ENTROPY_INJECT_ENTROPY_SHIFT         (0U)
/*! ENTROPY - Use this register to inject or restore entropy 32 bits at a time. Writing is blocking
 *    thus see to it to have analog clocks activated. Injection can be usefull to add contribution
 *    from an external source of entropy, like for example LSBs of an ADC or of a temperature sensor.
 *    Restore can be usefull to store N random numbers in central memory before going powerdown
 *    then restore this entropy to RNG IP after power-up. It is useless to inject or restore more than
 *    1*(number of RNGs) 32b words consecutively. Recommendation is to inject 1*(number of RNGs)
 *    words, and possibly later (2*32 clock cycles of slowest analog clock) inject again 1*(number of
 *    RNGs) words. Then maximum capacity of restoration is reached: about 44 bits per RNG (not to be
 *    mistaken with maximum capacity of entropy accumulation which is about 100 bits per RNG). You
 *    can inject less than 32 bits words (let unused bits to 0). Injection cannot degrade overall
 *    performance due to the fact that some internal PRNGs are excluded on purpose from this external
 *    action.
 */
#define RNG_ENTROPY_INJECT_ENTROPY(x)            (((uint32_t)(((uint32_t)(x)) << RNG_ENTROPY_INJECT_ENTROPY_SHIFT)) & RNG_ENTROPY_INJECT_ENTROPY_MASK)
/*! @} */

/*! @name MISC_CFG -  */
/*! @{ */

#define RNG_MISC_CFG_AES_RESEED_MASK             (0x1U)
#define RNG_MISC_CFG_AES_RESEED_SHIFT            (0U)
/*! AES_RESEED - If set, ENCRYPTED_NUMBER generation becomes predictable, provided all secrets and
 *    current internal state are known: independant from entropy source.
 */
#define RNG_MISC_CFG_AES_RESEED(x)               (((uint32_t)(((uint32_t)(x)) << RNG_MISC_CFG_AES_RESEED_SHIFT)) & RNG_MISC_CFG_AES_RESEED_MASK)

#define RNG_MISC_CFG_AES_DT_CFG_MASK             (0x2U)
#define RNG_MISC_CFG_AES_DT_CFG_SHIFT            (1U)
/*! AES_DT_CFG - Set this bit to re-seed AES. */
#define RNG_MISC_CFG_AES_DT_CFG(x)               (((uint32_t)(((uint32_t)(x)) << RNG_MISC_CFG_AES_DT_CFG_SHIFT)) & RNG_MISC_CFG_AES_DT_CFG_MASK)
/*! @} */

/*! @name POWERDOWN - Powerdown mode (standard but certainly useless here) */
/*! @{ */

#define RNG_POWERDOWN_SOFT_RESET_MASK            (0x1U)
#define RNG_POWERDOWN_SOFT_RESET_SHIFT           (0U)
/*! SOFT_RESET - Request softreset that will go low automaticaly after acknowledge from CORE. */
#define RNG_POWERDOWN_SOFT_RESET(x)              (((uint32_t)(((uint32_t)(x)) << RNG_POWERDOWN_SOFT_RESET_SHIFT)) & RNG_POWERDOWN_SOFT_RESET_MASK)

#define RNG_POWERDOWN_FORCE_SOFT_RESET_MASK      (0x2U)
#define RNG_POWERDOWN_FORCE_SOFT_RESET_SHIFT     (1U)
/*! FORCE_SOFT_RESET - When used with softreset it forces CORE_RESETN to low on acknowledge from CORE. */
#define RNG_POWERDOWN_FORCE_SOFT_RESET(x)        (((uint32_t)(((uint32_t)(x)) << RNG_POWERDOWN_FORCE_SOFT_RESET_SHIFT)) & RNG_POWERDOWN_FORCE_SOFT_RESET_MASK)

#define RNG_POWERDOWN_POWERDOWN_MASK             (0x80000000U)
#define RNG_POWERDOWN_POWERDOWN_SHIFT            (31U)
/*! POWERDOWN - When set all accesses to standard registers are blocked. */
#define RNG_POWERDOWN_POWERDOWN(x)               (((uint32_t)(((uint32_t)(x)) << RNG_POWERDOWN_POWERDOWN_SHIFT)) & RNG_POWERDOWN_POWERDOWN_MASK)
/*! @} */

/*! @name MODULEID - IP identifier */
/*! @{ */

#define RNG_MODULEID_APERTURE_MASK               (0xFFU)
#define RNG_MODULEID_APERTURE_SHIFT              (0U)
/*! APERTURE - Aperture i. */
#define RNG_MODULEID_APERTURE(x)                 (((uint32_t)(((uint32_t)(x)) << RNG_MODULEID_APERTURE_SHIFT)) & RNG_MODULEID_APERTURE_MASK)

#define RNG_MODULEID_MIN_REV_MASK                (0xF00U)
#define RNG_MODULEID_MIN_REV_SHIFT               (8U)
/*! MIN_REV - Minor revision i. */
#define RNG_MODULEID_MIN_REV(x)                  (((uint32_t)(((uint32_t)(x)) << RNG_MODULEID_MIN_REV_SHIFT)) & RNG_MODULEID_MIN_REV_MASK)

#define RNG_MODULEID_MAJ_REV_MASK                (0xF000U)
#define RNG_MODULEID_MAJ_REV_SHIFT               (12U)
/*! MAJ_REV - Major revision i. */
#define RNG_MODULEID_MAJ_REV(x)                  (((uint32_t)(((uint32_t)(x)) << RNG_MODULEID_MAJ_REV_SHIFT)) & RNG_MODULEID_MAJ_REV_MASK)

#define RNG_MODULEID_ID_MASK                     (0xFFFF0000U)
#define RNG_MODULEID_ID_SHIFT                    (16U)
/*! ID - Identifier. */
#define RNG_MODULEID_ID(x)                       (((uint32_t)(((uint32_t)(x)) << RNG_MODULEID_ID_SHIFT)) & RNG_MODULEID_ID_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group RNG_Register_Masks */


/*!
 * @}
 */ /* end of group RNG_Peripheral_Access_Layer */


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


#endif  /* RNG_H_ */


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
**         CMSIS Peripheral Access Layer for PLU
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
 * @file PLU.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for PLU
 *
 * CMSIS Peripheral Access Layer for PLU
 */

#if !defined(PLU_H_)
#define PLU_H_                                   /**< Symbol preventing repeated inclusion */

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
   -- PLU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PLU_Peripheral_Access_Layer PLU Peripheral Access Layer
 * @{
 */

/** PLU - Size of Registers Arrays */
#define PLU_LUT_INP_COUNT                         5u
#define PLU_LUT_COUNT                             26u
#define PLU_LUT_T_COUNT                           26u
#define PLU_OUTPUT_MUX_COUNT                      8u

/** PLU - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0x20 */
    __IO uint32_t INP_MUX[PLU_LUT_INP_COUNT];        /**< LUTn input x MUX, array offset: 0x0, array step: index*0x20, index2*0x4 */
         uint8_t RESERVED_0[12];
  } LUT[PLU_LUT_COUNT];
       uint8_t RESERVED_0[1216];
  __IO uint32_t LUT_TRUTH[PLU_LUT_T_COUNT];        /**< Specifies the Truth Table contents for LUT0..Specifies the Truth Table contents for LUT25, array offset: 0x800, array step: 0x4 */
       uint8_t RESERVED_1[152];
  __I  uint32_t OUTPUTS;                           /**< Provides the current state of the 8 designated PLU Outputs., offset: 0x900 */
  __IO uint32_t WAKEINT_CTRL;                      /**< Wakeup interrupt control for PLU, offset: 0x904 */
       uint8_t RESERVED_2[760];
  __IO uint32_t OUTPUT_MUX[PLU_OUTPUT_MUX_COUNT];  /**< Selects the source to be connected to PLU Output 0..Selects the source to be connected to PLU Output 7, array offset: 0xC00, array step: 0x4 */
} PLU_Type;

/* ----------------------------------------------------------------------------
   -- PLU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PLU_Register_Masks PLU Register Masks
 * @{
 */

/*! @name LUT_INP_MUX - LUTn input x MUX */
/*! @{ */

#define PLU_LUT_INP_MUX_LUTn_INPx_MASK           (0x3FU)
#define PLU_LUT_INP_MUX_LUTn_INPx_SHIFT          (0U)
/*! LUTn_INPx - Selects the input source to be connected to LUT25 input4. For each LUT, the slot
 *    associated with the output from LUTn itself is tied low.
 *  0b000000..The PLU primary inputs 0.
 *  0b000001..The PLU primary inputs 1.
 *  0b000010..The PLU primary inputs 2.
 *  0b000011..The PLU primary inputs 3.
 *  0b000100..The PLU primary inputs 4.
 *  0b000101..The PLU primary inputs 5.
 *  0b000110..The output of LUT0.
 *  0b000111..The output of LUT1.
 *  0b001000..The output of LUT2.
 *  0b001001..The output of LUT3.
 *  0b001010..The output of LUT4.
 *  0b001011..The output of LUT5.
 *  0b001100..The output of LUT6.
 *  0b001101..The output of LUT7.
 *  0b001110..The output of LUT8.
 *  0b001111..The output of LUT9.
 *  0b010000..The output of LUT10.
 *  0b010001..The output of LUT11.
 *  0b010010..The output of LUT12.
 *  0b010011..The output of LUT13.
 *  0b010100..The output of LUT14.
 *  0b010101..The output of LUT15.
 *  0b010110..The output of LUT16.
 *  0b010111..The output of LUT17.
 *  0b011000..The output of LUT18.
 *  0b011001..The output of LUT19.
 *  0b011010..The output of LUT20.
 *  0b011011..The output of LUT21.
 *  0b011100..The output of LUT22.
 *  0b011101..The output of LUT23.
 *  0b011110..The output of LUT24.
 *  0b011111..The output of LUT25.
 *  0b100000..state(0).
 *  0b100001..state(1).
 *  0b100010..state(2).
 *  0b100011..state(3).
 */
#define PLU_LUT_INP_MUX_LUTn_INPx(x)             (((uint32_t)(((uint32_t)(x)) << PLU_LUT_INP_MUX_LUTn_INPx_SHIFT)) & PLU_LUT_INP_MUX_LUTn_INPx_MASK)
/*! @} */

/* The count of PLU_LUT_INP_MUX */
#define PLU_LUT_INP_MUX_COUNT                    (26U)

/* The count of PLU_LUT_INP_MUX */
#define PLU_LUT_INP_MUX_COUNT2                   (5U)

/*! @name LUT_TRUTH - Specifies the Truth Table contents for LUT0..Specifies the Truth Table contents for LUT25 */
/*! @{ */

#define PLU_LUT_TRUTH_LUTn_TRUTH_MASK            (0xFFFFFFFFU)
#define PLU_LUT_TRUTH_LUTn_TRUTH_SHIFT           (0U)
/*! LUTn_TRUTH - Specifies the Truth Table contents for LUT25.. */
#define PLU_LUT_TRUTH_LUTn_TRUTH(x)              (((uint32_t)(((uint32_t)(x)) << PLU_LUT_TRUTH_LUTn_TRUTH_SHIFT)) & PLU_LUT_TRUTH_LUTn_TRUTH_MASK)
/*! @} */

/* The count of PLU_LUT_TRUTH */
#define PLU_LUT_TRUTH_COUNT                      (26U)

/*! @name OUTPUTS - Provides the current state of the 8 designated PLU Outputs. */
/*! @{ */

#define PLU_OUTPUTS_OUTPUT_STATE_MASK            (0xFFU)
#define PLU_OUTPUTS_OUTPUT_STATE_SHIFT           (0U)
/*! OUTPUT_STATE - Provides the current state of the 8 designated PLU Outputs.. */
#define PLU_OUTPUTS_OUTPUT_STATE(x)              (((uint32_t)(((uint32_t)(x)) << PLU_OUTPUTS_OUTPUT_STATE_SHIFT)) & PLU_OUTPUTS_OUTPUT_STATE_MASK)
/*! @} */

/*! @name WAKEINT_CTRL - Wakeup interrupt control for PLU */
/*! @{ */

#define PLU_WAKEINT_CTRL_MASK_MASK               (0xFFU)
#define PLU_WAKEINT_CTRL_MASK_SHIFT              (0U)
/*! MASK - Interrupt mask (which of the 8 PLU Outputs contribute to interrupt) */
#define PLU_WAKEINT_CTRL_MASK(x)                 (((uint32_t)(((uint32_t)(x)) << PLU_WAKEINT_CTRL_MASK_SHIFT)) & PLU_WAKEINT_CTRL_MASK_MASK)

#define PLU_WAKEINT_CTRL_FILTER_MODE_MASK        (0x300U)
#define PLU_WAKEINT_CTRL_FILTER_MODE_SHIFT       (8U)
/*! FILTER_MODE - control input of the PLU, add filtering for glitch.
 *  0b00..Bypass mode.
 *  0b01..Filter 1 clock period.
 *  0b10..Filter 2 clock period.
 *  0b11..Filter 3 clock period.
 */
#define PLU_WAKEINT_CTRL_FILTER_MODE(x)          (((uint32_t)(((uint32_t)(x)) << PLU_WAKEINT_CTRL_FILTER_MODE_SHIFT)) & PLU_WAKEINT_CTRL_FILTER_MODE_MASK)

#define PLU_WAKEINT_CTRL_FILTER_CLKSEL_MASK      (0xC00U)
#define PLU_WAKEINT_CTRL_FILTER_CLKSEL_SHIFT     (10U)
/*! FILTER_CLKSEL - hclk is divided by 2**filter_clksel.
 *  0b00..Selects the 1 MHz low-power oscillator as the filter clock.
 *  0b01..Selects the 12 Mhz FRO as the filter clock.
 *  0b10..Selects a third filter clock source, if provided.
 *  0b11..Reserved.
 */
#define PLU_WAKEINT_CTRL_FILTER_CLKSEL(x)        (((uint32_t)(((uint32_t)(x)) << PLU_WAKEINT_CTRL_FILTER_CLKSEL_SHIFT)) & PLU_WAKEINT_CTRL_FILTER_CLKSEL_MASK)

#define PLU_WAKEINT_CTRL_LATCH_ENABLE_MASK       (0x1000U)
#define PLU_WAKEINT_CTRL_LATCH_ENABLE_SHIFT      (12U)
/*! LATCH_ENABLE - latch the interrupt , then can be cleared with next bit INTR_CLEAR */
#define PLU_WAKEINT_CTRL_LATCH_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << PLU_WAKEINT_CTRL_LATCH_ENABLE_SHIFT)) & PLU_WAKEINT_CTRL_LATCH_ENABLE_MASK)

#define PLU_WAKEINT_CTRL_INTR_CLEAR_MASK         (0x2000U)
#define PLU_WAKEINT_CTRL_INTR_CLEAR_SHIFT        (13U)
/*! INTR_CLEAR - Write to clear wakeint_latched */
#define PLU_WAKEINT_CTRL_INTR_CLEAR(x)           (((uint32_t)(((uint32_t)(x)) << PLU_WAKEINT_CTRL_INTR_CLEAR_SHIFT)) & PLU_WAKEINT_CTRL_INTR_CLEAR_MASK)
/*! @} */

/*! @name OUTPUT_MUX - Selects the source to be connected to PLU Output 0..Selects the source to be connected to PLU Output 7 */
/*! @{ */

#define PLU_OUTPUT_MUX_OUTPUTn_MASK              (0x1FU)
#define PLU_OUTPUT_MUX_OUTPUTn_SHIFT             (0U)
/*! OUTPUTn - Selects the source to be connected to PLU Output 7.
 *  0b00000..The PLU output 0.
 *  0b00001..The PLU output 1.
 *  0b00010..The PLU output 2.
 *  0b00011..The PLU output 3.
 *  0b00100..The PLU output 4.
 *  0b00101..The PLU output 5.
 *  0b00110..The PLU output 6.
 *  0b00111..The PLU output 7.
 *  0b01000..The PLU output 8.
 *  0b01001..The PLU output 9.
 *  0b01010..The PLU output 10.
 *  0b01011..The PLU output 11.
 *  0b01100..The PLU output 12.
 *  0b01101..The PLU output 13.
 *  0b01110..The PLU output 14.
 *  0b01111..The PLU output 15.
 *  0b10000..The PLU output 16.
 *  0b10001..The PLU output 17.
 *  0b10010..The PLU output 18.
 *  0b10011..The PLU output 19.
 *  0b10100..The PLU output 20.
 *  0b10101..The PLU output 21.
 *  0b10110..The PLU output 22.
 *  0b10111..The PLU output 23.
 *  0b11000..The PLU output 24.
 *  0b11001..The PLU output 25.
 *  0b11010..state(0).
 *  0b11011..state(1).
 *  0b11100..state(2).
 *  0b11101..state(3).
 */
#define PLU_OUTPUT_MUX_OUTPUTn(x)                (((uint32_t)(((uint32_t)(x)) << PLU_OUTPUT_MUX_OUTPUTn_SHIFT)) & PLU_OUTPUT_MUX_OUTPUTn_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group PLU_Register_Masks */


/*!
 * @}
 */ /* end of group PLU_Peripheral_Access_Layer */


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


#endif  /* PLU_H_ */


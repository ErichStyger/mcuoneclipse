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
**         CMSIS Peripheral Access Layer for CASPER
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
 * @file CASPER.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for CASPER
 *
 * CMSIS Peripheral Access Layer for CASPER
 */

#if !defined(CASPER_H_)
#define CASPER_H_                                /**< Symbol preventing repeated inclusion */

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
   -- CASPER Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CASPER_Peripheral_Access_Layer CASPER Peripheral Access Layer
 * @{
 */

/** CASPER - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL0;                             /**< Contains the offsets of AB and CD in the RAM., offset: 0x0 */
  __IO uint32_t CTRL1;                             /**< Contains the opcode mode, iteration count, and result offset (in RAM) and also launches the accelerator. Note: with CP version: CTRL0 and CRTL1 can be written in one go with MCRR., offset: 0x4 */
  __IO uint32_t LOADER;                            /**< Contains an optional loader to load into CTRL0/1 in steps to perform a set of operations., offset: 0x8 */
  __IO uint32_t STATUS;                            /**< Indicates operational status and would contain the carry bit if used., offset: 0xC */
  __IO uint32_t INTENSET;                          /**< Sets interrupts, offset: 0x10 */
  __IO uint32_t INTENCLR;                          /**< Clears interrupts, offset: 0x14 */
  __I  uint32_t INTSTAT;                           /**< Interrupt status bits (mask of INTENSET and STATUS), offset: 0x18 */
       uint8_t RESERVED_0[4];
  __IO uint32_t AREG;                              /**< A register, offset: 0x20 */
  __IO uint32_t BREG;                              /**< B register, offset: 0x24 */
  __IO uint32_t CREG;                              /**< C register, offset: 0x28 */
  __IO uint32_t DREG;                              /**< D register, offset: 0x2C */
  __IO uint32_t RES0;                              /**< Result register 0, offset: 0x30 */
  __IO uint32_t RES1;                              /**< Result register 1, offset: 0x34 */
  __IO uint32_t RES2;                              /**< Result register 2, offset: 0x38 */
  __IO uint32_t RES3;                              /**< Result register 3, offset: 0x3C */
       uint8_t RESERVED_1[32];
  __IO uint32_t MASK;                              /**< Optional mask register, offset: 0x60 */
  __IO uint32_t REMASK;                            /**< Optional re-mask register, offset: 0x64 */
       uint8_t RESERVED_2[24];
  __IO uint32_t LOCK;                              /**< Security lock register, offset: 0x80 */
} CASPER_Type;

/* ----------------------------------------------------------------------------
   -- CASPER Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CASPER_Register_Masks CASPER Register Masks
 * @{
 */

/*! @name CTRL0 - Contains the offsets of AB and CD in the RAM. */
/*! @{ */

#define CASPER_CTRL0_ABBPAIR_MASK                (0x1U)
#define CASPER_CTRL0_ABBPAIR_SHIFT               (0U)
/*! ABBPAIR - Which bank-pair the offset ABOFF is within. This must be 0 if only 2-up
 *  0b0..Bank-pair 0 (1st)
 *  0b1..Bank-pair 1 (2nd)
 */
#define CASPER_CTRL0_ABBPAIR(x)                  (((uint32_t)(((uint32_t)(x)) << CASPER_CTRL0_ABBPAIR_SHIFT)) & CASPER_CTRL0_ABBPAIR_MASK)

#define CASPER_CTRL0_ABOFF_MASK                  (0x1FFCU)
#define CASPER_CTRL0_ABOFF_SHIFT                 (2U)
/*! ABOFF - Word or DWord Offset of AB values, with B at [2]=0 and A at [2]=1 as far as the code
 *    sees (normally will be an interleaved bank so only sequential to AHB). Word offset only allowed
 *    if 32 bit operation. Ideally not in the same RAM as the CD values if 4-up
 */
#define CASPER_CTRL0_ABOFF(x)                    (((uint32_t)(((uint32_t)(x)) << CASPER_CTRL0_ABOFF_SHIFT)) & CASPER_CTRL0_ABOFF_MASK)

#define CASPER_CTRL0_CDBPAIR_MASK                (0x10000U)
#define CASPER_CTRL0_CDBPAIR_SHIFT               (16U)
/*! CDBPAIR - Which bank-pair the offset CDOFF is within. This must be 0 if only 2-up
 *  0b0..Bank-pair 0 (1st)
 *  0b1..Bank-pair 1 (2nd)
 */
#define CASPER_CTRL0_CDBPAIR(x)                  (((uint32_t)(((uint32_t)(x)) << CASPER_CTRL0_CDBPAIR_SHIFT)) & CASPER_CTRL0_CDBPAIR_MASK)

#define CASPER_CTRL0_CDOFF_MASK                  (0x1FFC0000U)
#define CASPER_CTRL0_CDOFF_SHIFT                 (18U)
/*! CDOFF - Word or DWord Offset of CD, with D at [2]=0 and C at [2]=1 as far as the code sees
 *    (normally will be an interleaved bank so only sequential to AHB). Word offset only allowed if 32
 *    bit operation. Ideally not in the same RAM as the AB values
 */
#define CASPER_CTRL0_CDOFF(x)                    (((uint32_t)(((uint32_t)(x)) << CASPER_CTRL0_CDOFF_SHIFT)) & CASPER_CTRL0_CDOFF_MASK)
/*! @} */

/*! @name CTRL1 - Contains the opcode mode, iteration count, and result offset (in RAM) and also launches the accelerator. Note: with CP version: CTRL0 and CRTL1 can be written in one go with MCRR. */
/*! @{ */

#define CASPER_CTRL1_ITER_MASK                   (0xFFU)
#define CASPER_CTRL1_ITER_SHIFT                  (0U)
/*! ITER - Iteration counter. Is number_cycles - 1. write 0 means Does one cycle - does not iterate. */
#define CASPER_CTRL1_ITER(x)                     (((uint32_t)(((uint32_t)(x)) << CASPER_CTRL1_ITER_SHIFT)) & CASPER_CTRL1_ITER_MASK)

#define CASPER_CTRL1_MODE_MASK                   (0xFF00U)
#define CASPER_CTRL1_MODE_SHIFT                  (8U)
/*! MODE - Operation mode to perform. write 0 means Accelerator is inactive. write others means accelerator is active. */
#define CASPER_CTRL1_MODE(x)                     (((uint32_t)(((uint32_t)(x)) << CASPER_CTRL1_MODE_SHIFT)) & CASPER_CTRL1_MODE_MASK)

#define CASPER_CTRL1_RESBPAIR_MASK               (0x10000U)
#define CASPER_CTRL1_RESBPAIR_SHIFT              (16U)
/*! RESBPAIR - Which bank-pair the offset RESOFF is within. This must be 0 if only 2-up. Ideally
 *    this is not the same bank as ABBPAIR (when 4-up supported)
 *  0b0..Bank-pair 0 (1st)
 *  0b1..Bank-pair 1 (2nd)
 */
#define CASPER_CTRL1_RESBPAIR(x)                 (((uint32_t)(((uint32_t)(x)) << CASPER_CTRL1_RESBPAIR_SHIFT)) & CASPER_CTRL1_RESBPAIR_MASK)

#define CASPER_CTRL1_RESOFF_MASK                 (0x1FFC0000U)
#define CASPER_CTRL1_RESOFF_SHIFT                (18U)
/*! RESOFF - Word or DWord Offset of result. Word offset only allowed if 32 bit operation. Ideally
 *    not in the same RAM as the AB and CD values
 */
#define CASPER_CTRL1_RESOFF(x)                   (((uint32_t)(((uint32_t)(x)) << CASPER_CTRL1_RESOFF_SHIFT)) & CASPER_CTRL1_RESOFF_MASK)

#define CASPER_CTRL1_CSKIP_MASK                  (0xC0000000U)
#define CASPER_CTRL1_CSKIP_SHIFT                 (30U)
/*! CSKIP - Skip rules on Carry if needed. This operation will be skipped based on Carry value (from previous operation) if not 0:
 *  0b00..No Skip
 *  0b01..Skip if Carry is 1
 *  0b10..Skip if Carry is 0
 *  0b11..Set CTRLOFF to CDOFF and Skip
 */
#define CASPER_CTRL1_CSKIP(x)                    (((uint32_t)(((uint32_t)(x)) << CASPER_CTRL1_CSKIP_SHIFT)) & CASPER_CTRL1_CSKIP_MASK)
/*! @} */

/*! @name LOADER - Contains an optional loader to load into CTRL0/1 in steps to perform a set of operations. */
/*! @{ */

#define CASPER_LOADER_COUNT_MASK                 (0xFFU)
#define CASPER_LOADER_COUNT_SHIFT                (0U)
/*! COUNT - Number of control pairs to load 0 relative (so 1 means load 1). write 1 means Does one
 *    op - does not iterate, write N means N control pairs to load
 */
#define CASPER_LOADER_COUNT(x)                   (((uint32_t)(((uint32_t)(x)) << CASPER_LOADER_COUNT_SHIFT)) & CASPER_LOADER_COUNT_MASK)

#define CASPER_LOADER_CTRLBPAIR_MASK             (0x10000U)
#define CASPER_LOADER_CTRLBPAIR_SHIFT            (16U)
/*! CTRLBPAIR - Which bank-pair the offset CTRLOFF is within. This must be 0 if only 2-up. Does not
 *    matter which bank is used as this is loaded when not performing an operation.
 *  0b0..Bank-pair 0 (1st)
 *  0b1..Bank-pair 1 (2nd)
 */
#define CASPER_LOADER_CTRLBPAIR(x)               (((uint32_t)(((uint32_t)(x)) << CASPER_LOADER_CTRLBPAIR_SHIFT)) & CASPER_LOADER_CTRLBPAIR_MASK)

#define CASPER_LOADER_CTRLOFF_MASK               (0x1FFC0000U)
#define CASPER_LOADER_CTRLOFF_SHIFT              (18U)
/*! CTRLOFF - DWord Offset of CTRL pair to load next. */
#define CASPER_LOADER_CTRLOFF(x)                 (((uint32_t)(((uint32_t)(x)) << CASPER_LOADER_CTRLOFF_SHIFT)) & CASPER_LOADER_CTRLOFF_MASK)
/*! @} */

/*! @name STATUS - Indicates operational status and would contain the carry bit if used. */
/*! @{ */

#define CASPER_STATUS_DONE_MASK                  (0x1U)
#define CASPER_STATUS_DONE_SHIFT                 (0U)
/*! DONE - Indicates if the accelerator has finished an operation. Write 1 to clear, or write CTRL1 to clear.
 *  0b0..Busy or just cleared
 *  0b1..Completed last operation
 */
#define CASPER_STATUS_DONE(x)                    (((uint32_t)(((uint32_t)(x)) << CASPER_STATUS_DONE_SHIFT)) & CASPER_STATUS_DONE_MASK)

#define CASPER_STATUS_CARRY_MASK                 (0x10U)
#define CASPER_STATUS_CARRY_SHIFT                (4U)
/*! CARRY - Last carry value if operation produced a carry bit
 *  0b0..Carry was 0 or no carry
 *  0b1..Carry was 1
 */
#define CASPER_STATUS_CARRY(x)                   (((uint32_t)(((uint32_t)(x)) << CASPER_STATUS_CARRY_SHIFT)) & CASPER_STATUS_CARRY_MASK)

#define CASPER_STATUS_BUSY_MASK                  (0x20U)
#define CASPER_STATUS_BUSY_SHIFT                 (5U)
/*! BUSY - Indicates if the accelerator is busy performing an operation
 *  0b0..Not busy - is idle
 *  0b1..Is busy
 */
#define CASPER_STATUS_BUSY(x)                    (((uint32_t)(((uint32_t)(x)) << CASPER_STATUS_BUSY_SHIFT)) & CASPER_STATUS_BUSY_MASK)
/*! @} */

/*! @name INTENSET - Sets interrupts */
/*! @{ */

#define CASPER_INTENSET_DONE_MASK                (0x1U)
#define CASPER_INTENSET_DONE_SHIFT               (0U)
/*! DONE - Set if the accelerator should interrupt when done.
 *  0b0..Do not interrupt when done
 *  0b1..Interrupt when done
 */
#define CASPER_INTENSET_DONE(x)                  (((uint32_t)(((uint32_t)(x)) << CASPER_INTENSET_DONE_SHIFT)) & CASPER_INTENSET_DONE_MASK)
/*! @} */

/*! @name INTENCLR - Clears interrupts */
/*! @{ */

#define CASPER_INTENCLR_DONE_MASK                (0x1U)
#define CASPER_INTENCLR_DONE_SHIFT               (0U)
/*! DONE - Written to clear an interrupt set with INTENSET.
 *  0b0..If written 0, ignored
 *  0b1..If written 1, do not Interrupt when done
 */
#define CASPER_INTENCLR_DONE(x)                  (((uint32_t)(((uint32_t)(x)) << CASPER_INTENCLR_DONE_SHIFT)) & CASPER_INTENCLR_DONE_MASK)
/*! @} */

/*! @name INTSTAT - Interrupt status bits (mask of INTENSET and STATUS) */
/*! @{ */

#define CASPER_INTSTAT_DONE_MASK                 (0x1U)
#define CASPER_INTSTAT_DONE_SHIFT                (0U)
/*! DONE - If set, interrupt is caused by accelerator being done.
 *  0b0..Not caused by accelerator being done
 *  0b1..Caused by accelerator being done
 */
#define CASPER_INTSTAT_DONE(x)                   (((uint32_t)(((uint32_t)(x)) << CASPER_INTSTAT_DONE_SHIFT)) & CASPER_INTSTAT_DONE_MASK)
/*! @} */

/*! @name AREG - A register */
/*! @{ */

#define CASPER_AREG_REG_VALUE_MASK               (0xFFFFFFFFU)
#define CASPER_AREG_REG_VALUE_SHIFT              (0U)
/*! REG_VALUE - Register to be fed into Multiplier. Is not normally written or read by application,
 *    but is available when accelerator not busy.
 */
#define CASPER_AREG_REG_VALUE(x)                 (((uint32_t)(((uint32_t)(x)) << CASPER_AREG_REG_VALUE_SHIFT)) & CASPER_AREG_REG_VALUE_MASK)
/*! @} */

/*! @name BREG - B register */
/*! @{ */

#define CASPER_BREG_REG_VALUE_MASK               (0xFFFFFFFFU)
#define CASPER_BREG_REG_VALUE_SHIFT              (0U)
/*! REG_VALUE - Register to be fed into Multiplier. Is not normally written or read by application,
 *    but is available when accelerator not busy.
 */
#define CASPER_BREG_REG_VALUE(x)                 (((uint32_t)(((uint32_t)(x)) << CASPER_BREG_REG_VALUE_SHIFT)) & CASPER_BREG_REG_VALUE_MASK)
/*! @} */

/*! @name CREG - C register */
/*! @{ */

#define CASPER_CREG_REG_VALUE_MASK               (0xFFFFFFFFU)
#define CASPER_CREG_REG_VALUE_SHIFT              (0U)
/*! REG_VALUE - Register to be fed into Multiplier. Is not normally written or read by application,
 *    but is available when accelerator not busy.
 */
#define CASPER_CREG_REG_VALUE(x)                 (((uint32_t)(((uint32_t)(x)) << CASPER_CREG_REG_VALUE_SHIFT)) & CASPER_CREG_REG_VALUE_MASK)
/*! @} */

/*! @name DREG - D register */
/*! @{ */

#define CASPER_DREG_REG_VALUE_MASK               (0xFFFFFFFFU)
#define CASPER_DREG_REG_VALUE_SHIFT              (0U)
/*! REG_VALUE - Register to be fed into Multiplier. Is not normally written or read by application,
 *    but is available when accelerator not busy.
 */
#define CASPER_DREG_REG_VALUE(x)                 (((uint32_t)(((uint32_t)(x)) << CASPER_DREG_REG_VALUE_SHIFT)) & CASPER_DREG_REG_VALUE_MASK)
/*! @} */

/*! @name RES0 - Result register 0 */
/*! @{ */

#define CASPER_RES0_REG_VALUE_MASK               (0xFFFFFFFFU)
#define CASPER_RES0_REG_VALUE_SHIFT              (0U)
/*! REG_VALUE - Register to hold working result (from multiplier, adder/xor, etc). Is not normally
 *    written or read by application, but is available when accelerator not busy.
 */
#define CASPER_RES0_REG_VALUE(x)                 (((uint32_t)(((uint32_t)(x)) << CASPER_RES0_REG_VALUE_SHIFT)) & CASPER_RES0_REG_VALUE_MASK)
/*! @} */

/*! @name RES1 - Result register 1 */
/*! @{ */

#define CASPER_RES1_REG_VALUE_MASK               (0xFFFFFFFFU)
#define CASPER_RES1_REG_VALUE_SHIFT              (0U)
/*! REG_VALUE - Register to hold working result (from multiplier, adder/xor, etc). Is not normally
 *    written or read by application, but is available when accelerator not busy.
 */
#define CASPER_RES1_REG_VALUE(x)                 (((uint32_t)(((uint32_t)(x)) << CASPER_RES1_REG_VALUE_SHIFT)) & CASPER_RES1_REG_VALUE_MASK)
/*! @} */

/*! @name RES2 - Result register 2 */
/*! @{ */

#define CASPER_RES2_REG_VALUE_MASK               (0xFFFFFFFFU)
#define CASPER_RES2_REG_VALUE_SHIFT              (0U)
/*! REG_VALUE - Register to hold working result (from multiplier, adder/xor, etc). Is not normally
 *    written or read by application, but is available when accelerator not busy.
 */
#define CASPER_RES2_REG_VALUE(x)                 (((uint32_t)(((uint32_t)(x)) << CASPER_RES2_REG_VALUE_SHIFT)) & CASPER_RES2_REG_VALUE_MASK)
/*! @} */

/*! @name RES3 - Result register 3 */
/*! @{ */

#define CASPER_RES3_REG_VALUE_MASK               (0xFFFFFFFFU)
#define CASPER_RES3_REG_VALUE_SHIFT              (0U)
/*! REG_VALUE - Register to hold working result (from multiplier, adder/xor, etc). Is not normally
 *    written or read by application, but is available when accelerator not busy.
 */
#define CASPER_RES3_REG_VALUE(x)                 (((uint32_t)(((uint32_t)(x)) << CASPER_RES3_REG_VALUE_SHIFT)) & CASPER_RES3_REG_VALUE_MASK)
/*! @} */

/*! @name MASK - Optional mask register */
/*! @{ */

#define CASPER_MASK_MASK_MASK                    (0xFFFFFFFFU)
#define CASPER_MASK_MASK_SHIFT                   (0U)
/*! MASK - Mask to apply as side channel countermeasure. 0: No mask to be used. N: Mask to XOR onto values */
#define CASPER_MASK_MASK(x)                      (((uint32_t)(((uint32_t)(x)) << CASPER_MASK_MASK_SHIFT)) & CASPER_MASK_MASK_MASK)
/*! @} */

/*! @name REMASK - Optional re-mask register */
/*! @{ */

#define CASPER_REMASK_MASK_MASK                  (0xFFFFFFFFU)
#define CASPER_REMASK_MASK_SHIFT                 (0U)
/*! MASK - Mask to apply as side channel countermeasure. 0: No mask to be used. N: Mask to XOR onto values */
#define CASPER_REMASK_MASK(x)                    (((uint32_t)(((uint32_t)(x)) << CASPER_REMASK_MASK_SHIFT)) & CASPER_REMASK_MASK_MASK)
/*! @} */

/*! @name LOCK - Security lock register */
/*! @{ */

#define CASPER_LOCK_LOCK_MASK                    (0x1U)
#define CASPER_LOCK_LOCK_SHIFT                   (0U)
/*! LOCK - Reads back with security level locked to, or 0. Writes as 0 to unlock, 1 to lock.
 *  0b0..unlock
 *  0b1..Lock to current security level
 */
#define CASPER_LOCK_LOCK(x)                      (((uint32_t)(((uint32_t)(x)) << CASPER_LOCK_LOCK_SHIFT)) & CASPER_LOCK_LOCK_MASK)

#define CASPER_LOCK_KEY_MASK                     (0x1FFF0U)
#define CASPER_LOCK_KEY_SHIFT                    (4U)
/*! KEY - Must be written as 0x73D to change the register.
 *  0b0011100111101..If set during write, will allow lock or unlock
 */
#define CASPER_LOCK_KEY(x)                       (((uint32_t)(((uint32_t)(x)) << CASPER_LOCK_KEY_SHIFT)) & CASPER_LOCK_KEY_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group CASPER_Register_Masks */


/*!
 * @}
 */ /* end of group CASPER_Peripheral_Access_Layer */


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


#endif  /* CASPER_H_ */


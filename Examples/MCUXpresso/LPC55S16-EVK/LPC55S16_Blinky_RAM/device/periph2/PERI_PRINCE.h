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
**         CMSIS Peripheral Access Layer for PRINCE
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
 * @file PRINCE.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for PRINCE
 *
 * CMSIS Peripheral Access Layer for PRINCE
 */

#if !defined(PRINCE_H_)
#define PRINCE_H_                                /**< Symbol preventing repeated inclusion */

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
   -- PRINCE Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PRINCE_Peripheral_Access_Layer PRINCE Peripheral Access Layer
 * @{
 */

/** PRINCE - Register Layout Typedef */
typedef struct {
  __IO uint32_t ENC_ENABLE;                        /**< Encryption Enable register, offset: 0x0 */
  __O  uint32_t MASK_LSB;                          /**< Data Mask register, 32 Least Significant Bits, offset: 0x4 */
  __O  uint32_t MASK_MSB;                          /**< Data Mask register, 32 Most Significant Bits, offset: 0x8 */
  __IO uint32_t LOCK;                              /**< Lock register, offset: 0xC */
  __O  uint32_t IV_LSB0;                           /**< Initial Vector register for region 0, Least Significant Bits, offset: 0x10 */
  __O  uint32_t IV_MSB0;                           /**< Initial Vector register for region 0, Most Significant Bits, offset: 0x14 */
  __IO uint32_t BASE_ADDR0;                        /**< Base Address for region 0 register, offset: 0x18 */
  __IO uint32_t SR_ENABLE0;                        /**< Sub-Region Enable register for region 0, offset: 0x1C */
  __O  uint32_t IV_LSB1;                           /**< Initial Vector register for region 1, Least Significant Bits, offset: 0x20 */
  __O  uint32_t IV_MSB1;                           /**< Initial Vector register for region 1, Most Significant Bits, offset: 0x24 */
  __IO uint32_t BASE_ADDR1;                        /**< Base Address for region 1 register, offset: 0x28 */
  __IO uint32_t SR_ENABLE1;                        /**< Sub-Region Enable register for region 1, offset: 0x2C */
  __O  uint32_t IV_LSB2;                           /**< Initial Vector register for region 2, Least Significant Bits, offset: 0x30 */
  __O  uint32_t IV_MSB2;                           /**< Initial Vector register for region 2, Most Significant Bits, offset: 0x34 */
  __IO uint32_t BASE_ADDR2;                        /**< Base Address for region 2 register, offset: 0x38 */
  __IO uint32_t SR_ENABLE2;                        /**< Sub-Region Enable register for region 2, offset: 0x3C */
       uint8_t RESERVED_0[80];
  __IO uint32_t ERR;                               /**< Error status register, offset: 0x90 */
} PRINCE_Type;

/* ----------------------------------------------------------------------------
   -- PRINCE Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PRINCE_Register_Masks PRINCE Register Masks
 * @{
 */

/*! @name ENC_ENABLE - Encryption Enable register */
/*! @{ */

#define PRINCE_ENC_ENABLE_EN_MASK                (0x1U)
#define PRINCE_ENC_ENABLE_EN_SHIFT               (0U)
/*! EN - Enables PRINCE encryption for flash programming.
 *  0b0..Encryption of writes to the flash controller DATAW* registers is disabled.
 *  0b1..Encryption of writes to the flash controller DATAW* registers is enabled. Reading of PRINCE-encrypted flash regions is disabled.
 */
#define PRINCE_ENC_ENABLE_EN(x)                  (((uint32_t)(((uint32_t)(x)) << PRINCE_ENC_ENABLE_EN_SHIFT)) & PRINCE_ENC_ENABLE_EN_MASK)
/*! @} */

/*! @name MASK_LSB - Data Mask register, 32 Least Significant Bits */
/*! @{ */

#define PRINCE_MASK_LSB_MASKVAL_MASK             (0xFFFFFFFFU)
#define PRINCE_MASK_LSB_MASKVAL_SHIFT            (0U)
/*! MASKVAL - Value of the 32 Least Significant Bits of the 64-bit data mask. */
#define PRINCE_MASK_LSB_MASKVAL(x)               (((uint32_t)(((uint32_t)(x)) << PRINCE_MASK_LSB_MASKVAL_SHIFT)) & PRINCE_MASK_LSB_MASKVAL_MASK)
/*! @} */

/*! @name MASK_MSB - Data Mask register, 32 Most Significant Bits */
/*! @{ */

#define PRINCE_MASK_MSB_MASKVAL_MASK             (0xFFFFFFFFU)
#define PRINCE_MASK_MSB_MASKVAL_SHIFT            (0U)
/*! MASKVAL - Value of the 32 Most Significant Bits of the 64-bit data mask. */
#define PRINCE_MASK_MSB_MASKVAL(x)               (((uint32_t)(((uint32_t)(x)) << PRINCE_MASK_MSB_MASKVAL_SHIFT)) & PRINCE_MASK_MSB_MASKVAL_MASK)
/*! @} */

/*! @name LOCK - Lock register */
/*! @{ */

#define PRINCE_LOCK_LOCKREG0_MASK                (0x1U)
#define PRINCE_LOCK_LOCKREG0_SHIFT               (0U)
/*! LOCKREG0 - Lock Region 0 registers.
 *  0b0..Disabled. IV_LSB0, IV_MSB0, BASE_ADDR0, and SR_ENABLE0 are writable..
 *  0b1..Enabled. IV_LSB0, IV_MSB0, BASE_ADDR0, and SR_ENABLE0 are not writable..
 */
#define PRINCE_LOCK_LOCKREG0(x)                  (((uint32_t)(((uint32_t)(x)) << PRINCE_LOCK_LOCKREG0_SHIFT)) & PRINCE_LOCK_LOCKREG0_MASK)

#define PRINCE_LOCK_LOCKREG1_MASK                (0x2U)
#define PRINCE_LOCK_LOCKREG1_SHIFT               (1U)
/*! LOCKREG1 - Lock Region 1 registers.
 *  0b0..Disabled. IV_LSB1, IV_MSB1, BASE_ADDR1, and SR_ENABLE1 are writable..
 *  0b1..Enabled. IV_LSB1, IV_MSB1, BASE_ADDR1, and SR_ENABLE1 are not writable..
 */
#define PRINCE_LOCK_LOCKREG1(x)                  (((uint32_t)(((uint32_t)(x)) << PRINCE_LOCK_LOCKREG1_SHIFT)) & PRINCE_LOCK_LOCKREG1_MASK)

#define PRINCE_LOCK_LOCKREG2_MASK                (0x4U)
#define PRINCE_LOCK_LOCKREG2_SHIFT               (2U)
/*! LOCKREG2 - Lock Region 2 registers.
 *  0b0..Disabled. IV_LSB2, IV_MSB2, BASE_ADDR2, and SR_ENABLE2 are writable..
 *  0b1..Enabled. IV_LSB2, IV_MSB2, BASE_ADDR2, and SR_ENABLE2 are not writable..
 */
#define PRINCE_LOCK_LOCKREG2(x)                  (((uint32_t)(((uint32_t)(x)) << PRINCE_LOCK_LOCKREG2_SHIFT)) & PRINCE_LOCK_LOCKREG2_MASK)

#define PRINCE_LOCK_LOCKMASK_MASK                (0x100U)
#define PRINCE_LOCK_LOCKMASK_SHIFT               (8U)
/*! LOCKMASK - Lock the Mask registers.
 *  0b0..Disabled. MASK_LSB, and MASK_MSB are writable..
 *  0b1..Enabled. MASK_LSB, and MASK_MSB are not writable..
 */
#define PRINCE_LOCK_LOCKMASK(x)                  (((uint32_t)(((uint32_t)(x)) << PRINCE_LOCK_LOCKMASK_SHIFT)) & PRINCE_LOCK_LOCKMASK_MASK)
/*! @} */

/*! @name IV_LSB0 - Initial Vector register for region 0, Least Significant Bits */
/*! @{ */

#define PRINCE_IV_LSB0_IVVAL_MASK                (0xFFFFFFFFU)
#define PRINCE_IV_LSB0_IVVAL_SHIFT               (0U)
/*! IVVAL - Initial Vector value for the 32 Least Significant Bits of the 64-bit Initial Vector. */
#define PRINCE_IV_LSB0_IVVAL(x)                  (((uint32_t)(((uint32_t)(x)) << PRINCE_IV_LSB0_IVVAL_SHIFT)) & PRINCE_IV_LSB0_IVVAL_MASK)
/*! @} */

/*! @name IV_MSB0 - Initial Vector register for region 0, Most Significant Bits */
/*! @{ */

#define PRINCE_IV_MSB0_IVVAL_MASK                (0xFFFFFFFFU)
#define PRINCE_IV_MSB0_IVVAL_SHIFT               (0U)
/*! IVVAL - Initial Vector value for the 32 Most Significant Bits of the 64-bit Initial Vector. */
#define PRINCE_IV_MSB0_IVVAL(x)                  (((uint32_t)(((uint32_t)(x)) << PRINCE_IV_MSB0_IVVAL_SHIFT)) & PRINCE_IV_MSB0_IVVAL_MASK)
/*! @} */

/*! @name BASE_ADDR0 - Base Address for region 0 register */
/*! @{ */

#define PRINCE_BASE_ADDR0_ADDR_FIXED_MASK        (0x3FFFFU)
#define PRINCE_BASE_ADDR0_ADDR_FIXED_SHIFT       (0U)
/*! ADDR_FIXED - Fixed portion of the base address of region 0. */
#define PRINCE_BASE_ADDR0_ADDR_FIXED(x)          (((uint32_t)(((uint32_t)(x)) << PRINCE_BASE_ADDR0_ADDR_FIXED_SHIFT)) & PRINCE_BASE_ADDR0_ADDR_FIXED_MASK)

#define PRINCE_BASE_ADDR0_ADDR_PRG_MASK          (0xC0000U)
#define PRINCE_BASE_ADDR0_ADDR_PRG_SHIFT         (18U)
/*! ADDR_PRG - Programmable portion of the base address of region 0. */
#define PRINCE_BASE_ADDR0_ADDR_PRG(x)            (((uint32_t)(((uint32_t)(x)) << PRINCE_BASE_ADDR0_ADDR_PRG_SHIFT)) & PRINCE_BASE_ADDR0_ADDR_PRG_MASK)
/*! @} */

/*! @name SR_ENABLE0 - Sub-Region Enable register for region 0 */
/*! @{ */

#define PRINCE_SR_ENABLE0_EN_MASK                (0xFFFFFFFFU)
#define PRINCE_SR_ENABLE0_EN_SHIFT               (0U)
/*! EN - Each bit in this field enables an 8KB subregion for encryption at offset 8KB*bitnum of region 0. */
#define PRINCE_SR_ENABLE0_EN(x)                  (((uint32_t)(((uint32_t)(x)) << PRINCE_SR_ENABLE0_EN_SHIFT)) & PRINCE_SR_ENABLE0_EN_MASK)
/*! @} */

/*! @name IV_LSB1 - Initial Vector register for region 1, Least Significant Bits */
/*! @{ */

#define PRINCE_IV_LSB1_IVVAL_MASK                (0xFFFFFFFFU)
#define PRINCE_IV_LSB1_IVVAL_SHIFT               (0U)
/*! IVVAL - Initial Vector value for the 32 Least Significant Bits of the 64-bit Initial Vector. */
#define PRINCE_IV_LSB1_IVVAL(x)                  (((uint32_t)(((uint32_t)(x)) << PRINCE_IV_LSB1_IVVAL_SHIFT)) & PRINCE_IV_LSB1_IVVAL_MASK)
/*! @} */

/*! @name IV_MSB1 - Initial Vector register for region 1, Most Significant Bits */
/*! @{ */

#define PRINCE_IV_MSB1_IVVAL_MASK                (0xFFFFFFFFU)
#define PRINCE_IV_MSB1_IVVAL_SHIFT               (0U)
/*! IVVAL - Initial Vector value for the 32 Most Significant Bits of the 64-bit Initial Vector. */
#define PRINCE_IV_MSB1_IVVAL(x)                  (((uint32_t)(((uint32_t)(x)) << PRINCE_IV_MSB1_IVVAL_SHIFT)) & PRINCE_IV_MSB1_IVVAL_MASK)
/*! @} */

/*! @name BASE_ADDR1 - Base Address for region 1 register */
/*! @{ */

#define PRINCE_BASE_ADDR1_ADDR_FIXED_MASK        (0x3FFFFU)
#define PRINCE_BASE_ADDR1_ADDR_FIXED_SHIFT       (0U)
/*! ADDR_FIXED - Fixed portion of the base address of region 1. */
#define PRINCE_BASE_ADDR1_ADDR_FIXED(x)          (((uint32_t)(((uint32_t)(x)) << PRINCE_BASE_ADDR1_ADDR_FIXED_SHIFT)) & PRINCE_BASE_ADDR1_ADDR_FIXED_MASK)

#define PRINCE_BASE_ADDR1_ADDR_PRG_MASK          (0xC0000U)
#define PRINCE_BASE_ADDR1_ADDR_PRG_SHIFT         (18U)
/*! ADDR_PRG - Programmable portion of the base address of region 1. */
#define PRINCE_BASE_ADDR1_ADDR_PRG(x)            (((uint32_t)(((uint32_t)(x)) << PRINCE_BASE_ADDR1_ADDR_PRG_SHIFT)) & PRINCE_BASE_ADDR1_ADDR_PRG_MASK)
/*! @} */

/*! @name SR_ENABLE1 - Sub-Region Enable register for region 1 */
/*! @{ */

#define PRINCE_SR_ENABLE1_EN_MASK                (0xFFFFFFFFU)
#define PRINCE_SR_ENABLE1_EN_SHIFT               (0U)
/*! EN - Each bit in this field enables an 8KB subregion for encryption at offset 8KB*bitnum of region 1. */
#define PRINCE_SR_ENABLE1_EN(x)                  (((uint32_t)(((uint32_t)(x)) << PRINCE_SR_ENABLE1_EN_SHIFT)) & PRINCE_SR_ENABLE1_EN_MASK)
/*! @} */

/*! @name IV_LSB2 - Initial Vector register for region 2, Least Significant Bits */
/*! @{ */

#define PRINCE_IV_LSB2_IVVAL_MASK                (0xFFFFFFFFU)
#define PRINCE_IV_LSB2_IVVAL_SHIFT               (0U)
/*! IVVAL - Initial Vector value for the 32 Least Significant Bits of the 64-bit Initial Vector. */
#define PRINCE_IV_LSB2_IVVAL(x)                  (((uint32_t)(((uint32_t)(x)) << PRINCE_IV_LSB2_IVVAL_SHIFT)) & PRINCE_IV_LSB2_IVVAL_MASK)
/*! @} */

/*! @name IV_MSB2 - Initial Vector register for region 2, Most Significant Bits */
/*! @{ */

#define PRINCE_IV_MSB2_IVVAL_MASK                (0xFFFFFFFFU)
#define PRINCE_IV_MSB2_IVVAL_SHIFT               (0U)
/*! IVVAL - Initial Vector value for the 32 Most Significant Bits of the 64-bit Initial Vector. */
#define PRINCE_IV_MSB2_IVVAL(x)                  (((uint32_t)(((uint32_t)(x)) << PRINCE_IV_MSB2_IVVAL_SHIFT)) & PRINCE_IV_MSB2_IVVAL_MASK)
/*! @} */

/*! @name BASE_ADDR2 - Base Address for region 2 register */
/*! @{ */

#define PRINCE_BASE_ADDR2_ADDR_FIXED_MASK        (0x3FFFFU)
#define PRINCE_BASE_ADDR2_ADDR_FIXED_SHIFT       (0U)
/*! ADDR_FIXED - Fixed portion of the base address of region 2. */
#define PRINCE_BASE_ADDR2_ADDR_FIXED(x)          (((uint32_t)(((uint32_t)(x)) << PRINCE_BASE_ADDR2_ADDR_FIXED_SHIFT)) & PRINCE_BASE_ADDR2_ADDR_FIXED_MASK)

#define PRINCE_BASE_ADDR2_ADDR_PRG_MASK          (0xC0000U)
#define PRINCE_BASE_ADDR2_ADDR_PRG_SHIFT         (18U)
/*! ADDR_PRG - Programmable portion of the base address of region 2. */
#define PRINCE_BASE_ADDR2_ADDR_PRG(x)            (((uint32_t)(((uint32_t)(x)) << PRINCE_BASE_ADDR2_ADDR_PRG_SHIFT)) & PRINCE_BASE_ADDR2_ADDR_PRG_MASK)
/*! @} */

/*! @name SR_ENABLE2 - Sub-Region Enable register for region 2 */
/*! @{ */

#define PRINCE_SR_ENABLE2_EN_MASK                (0xFFFFFFFFU)
#define PRINCE_SR_ENABLE2_EN_SHIFT               (0U)
/*! EN - Each bit in this field enables an 8KB subregion for encryption at offset 8KB*bitnum of region 2. */
#define PRINCE_SR_ENABLE2_EN(x)                  (((uint32_t)(((uint32_t)(x)) << PRINCE_SR_ENABLE2_EN_SHIFT)) & PRINCE_SR_ENABLE2_EN_MASK)
/*! @} */

/*! @name ERR - Error status register */
/*! @{ */

#define PRINCE_ERR_ERRSTAT_MASK                  (0x1U)
#define PRINCE_ERR_ERRSTAT_SHIFT                 (0U)
/*! ERRSTAT - PRINCE Error Status. This bit is write-1 to clear.
 *  0b0..No PRINCE error.
 *  0b1..Error. A read of a PRINCE-encrypted region was attempted while ENC_ENABLE.EN=1.
 */
#define PRINCE_ERR_ERRSTAT(x)                    (((uint32_t)(((uint32_t)(x)) << PRINCE_ERR_ERRSTAT_SHIFT)) & PRINCE_ERR_ERRSTAT_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group PRINCE_Register_Masks */


/*!
 * @}
 */ /* end of group PRINCE_Peripheral_Access_Layer */


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


#endif  /* PRINCE_H_ */


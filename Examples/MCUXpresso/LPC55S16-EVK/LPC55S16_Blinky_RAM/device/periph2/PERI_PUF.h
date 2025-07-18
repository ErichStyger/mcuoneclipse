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
**         CMSIS Peripheral Access Layer for PUF
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
 * @file PUF.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for PUF
 *
 * CMSIS Peripheral Access Layer for PUF
 */

#if !defined(PUF_H_)
#define PUF_H_                                   /**< Symbol preventing repeated inclusion */

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
   -- PUF Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PUF_Peripheral_Access_Layer PUF Peripheral Access Layer
 * @{
 */

/** PUF - Size of Registers Arrays */
#define PUF_KEYMASK_COUNT                         4u

/** PUF - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< PUF Control register, offset: 0x0 */
  __IO uint32_t KEYINDEX;                          /**< PUF Key Index register, offset: 0x4 */
  __IO uint32_t KEYSIZE;                           /**< PUF Key Size register, offset: 0x8 */
       uint8_t RESERVED_0[20];
  __I  uint32_t STAT;                              /**< PUF Status register, offset: 0x20 */
       uint8_t RESERVED_1[4];
  __I  uint32_t ALLOW;                             /**< PUF Allow register, offset: 0x28 */
       uint8_t RESERVED_2[20];
  __O  uint32_t KEYINPUT;                          /**< PUF Key Input register, offset: 0x40 */
  __O  uint32_t CODEINPUT;                         /**< PUF Code Input register, offset: 0x44 */
  __I  uint32_t CODEOUTPUT;                        /**< PUF Code Output register, offset: 0x48 */
       uint8_t RESERVED_3[20];
  __I  uint32_t KEYOUTINDEX;                       /**< PUF Key Output Index register, offset: 0x60 */
  __I  uint32_t KEYOUTPUT;                         /**< PUF Key Output register, offset: 0x64 */
       uint8_t RESERVED_4[116];
  __IO uint32_t IFSTAT;                            /**< PUF Interface Status and clear register, offset: 0xDC */
       uint8_t RESERVED_5[32];
  __IO uint32_t INTEN;                             /**< PUF Interrupt Enable, offset: 0x100 */
  __IO uint32_t INTSTAT;                           /**< PUF interrupt status, offset: 0x104 */
       uint8_t RESERVED_6[4];
  __IO uint32_t CFG;                               /**< PUF config register for block bits, offset: 0x10C */
       uint8_t RESERVED_7[240];
  __IO uint32_t KEYLOCK;                           /**< Only reset in case of full IC reset, offset: 0x200 */
  __IO uint32_t KEYENABLE;                         /**< offset: 0x204 */
  __O  uint32_t KEYRESET;                          /**< Reinitialize Keys shift registers counters, offset: 0x208 */
  __O  uint32_t IDXBLK;                            /**< offset: 0x20C */
  __O  uint32_t IDXBLK_DP;                         /**< offset: 0x210 */
  __O  uint32_t KEYMASK[PUF_KEYMASK_COUNT];        /**< Only reset in case of full IC reset, array offset: 0x214, array step: 0x4 */
       uint8_t RESERVED_8[48];
  __I  uint32_t IDXBLK_STATUS;                     /**< Index block status, offset: 0x254 */
  __I  uint32_t SHIFT_STATUS;                      /**< offset: 0x258 */
} PUF_Type;

/* ----------------------------------------------------------------------------
   -- PUF Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PUF_Register_Masks PUF Register Masks
 * @{
 */

/*! @name CTRL - PUF Control register */
/*! @{ */

#define PUF_CTRL_ZEROIZE_MASK                    (0x1U)
#define PUF_CTRL_ZEROIZE_SHIFT                   (0U)
/*! zeroize - Begin Zeroize operation for PUF and go to Error state */
#define PUF_CTRL_ZEROIZE(x)                      (((uint32_t)(((uint32_t)(x)) << PUF_CTRL_ZEROIZE_SHIFT)) & PUF_CTRL_ZEROIZE_MASK)

#define PUF_CTRL_ENROLL_MASK                     (0x2U)
#define PUF_CTRL_ENROLL_SHIFT                    (1U)
/*! enroll - Begin Enroll operation */
#define PUF_CTRL_ENROLL(x)                       (((uint32_t)(((uint32_t)(x)) << PUF_CTRL_ENROLL_SHIFT)) & PUF_CTRL_ENROLL_MASK)

#define PUF_CTRL_START_MASK                      (0x4U)
#define PUF_CTRL_START_SHIFT                     (2U)
/*! start - Begin Start operation */
#define PUF_CTRL_START(x)                        (((uint32_t)(((uint32_t)(x)) << PUF_CTRL_START_SHIFT)) & PUF_CTRL_START_MASK)

#define PUF_CTRL_GENERATEKEY_MASK                (0x8U)
#define PUF_CTRL_GENERATEKEY_SHIFT               (3U)
/*! GENERATEKEY - Begin Set Intrinsic Key operation */
#define PUF_CTRL_GENERATEKEY(x)                  (((uint32_t)(((uint32_t)(x)) << PUF_CTRL_GENERATEKEY_SHIFT)) & PUF_CTRL_GENERATEKEY_MASK)

#define PUF_CTRL_SETKEY_MASK                     (0x10U)
#define PUF_CTRL_SETKEY_SHIFT                    (4U)
/*! SETKEY - Begin Set User Key operation */
#define PUF_CTRL_SETKEY(x)                       (((uint32_t)(((uint32_t)(x)) << PUF_CTRL_SETKEY_SHIFT)) & PUF_CTRL_SETKEY_MASK)

#define PUF_CTRL_GETKEY_MASK                     (0x40U)
#define PUF_CTRL_GETKEY_SHIFT                    (6U)
/*! GETKEY - Begin Get Key operation */
#define PUF_CTRL_GETKEY(x)                       (((uint32_t)(((uint32_t)(x)) << PUF_CTRL_GETKEY_SHIFT)) & PUF_CTRL_GETKEY_MASK)
/*! @} */

/*! @name KEYINDEX - PUF Key Index register */
/*! @{ */

#define PUF_KEYINDEX_KEYIDX_MASK                 (0xFU)
#define PUF_KEYINDEX_KEYIDX_SHIFT                (0U)
/*! KEYIDX - Key index for Set Key operations */
#define PUF_KEYINDEX_KEYIDX(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_KEYINDEX_KEYIDX_SHIFT)) & PUF_KEYINDEX_KEYIDX_MASK)
/*! @} */

/*! @name KEYSIZE - PUF Key Size register */
/*! @{ */

#define PUF_KEYSIZE_KEYSIZE_MASK                 (0x3FU)
#define PUF_KEYSIZE_KEYSIZE_SHIFT                (0U)
/*! KEYSIZE - Key size for Set Key operations */
#define PUF_KEYSIZE_KEYSIZE(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_KEYSIZE_KEYSIZE_SHIFT)) & PUF_KEYSIZE_KEYSIZE_MASK)
/*! @} */

/*! @name STAT - PUF Status register */
/*! @{ */

#define PUF_STAT_BUSY_MASK                       (0x1U)
#define PUF_STAT_BUSY_SHIFT                      (0U)
/*! busy - Indicates that operation is in progress */
#define PUF_STAT_BUSY(x)                         (((uint32_t)(((uint32_t)(x)) << PUF_STAT_BUSY_SHIFT)) & PUF_STAT_BUSY_MASK)

#define PUF_STAT_SUCCESS_MASK                    (0x2U)
#define PUF_STAT_SUCCESS_SHIFT                   (1U)
/*! SUCCESS - Last operation was successful */
#define PUF_STAT_SUCCESS(x)                      (((uint32_t)(((uint32_t)(x)) << PUF_STAT_SUCCESS_SHIFT)) & PUF_STAT_SUCCESS_MASK)

#define PUF_STAT_ERROR_MASK                      (0x4U)
#define PUF_STAT_ERROR_SHIFT                     (2U)
/*! error - PUF is in the Error state and no operations can be performed */
#define PUF_STAT_ERROR(x)                        (((uint32_t)(((uint32_t)(x)) << PUF_STAT_ERROR_SHIFT)) & PUF_STAT_ERROR_MASK)

#define PUF_STAT_KEYINREQ_MASK                   (0x10U)
#define PUF_STAT_KEYINREQ_SHIFT                  (4U)
/*! KEYINREQ - Request for next part of key */
#define PUF_STAT_KEYINREQ(x)                     (((uint32_t)(((uint32_t)(x)) << PUF_STAT_KEYINREQ_SHIFT)) & PUF_STAT_KEYINREQ_MASK)

#define PUF_STAT_KEYOUTAVAIL_MASK                (0x20U)
#define PUF_STAT_KEYOUTAVAIL_SHIFT               (5U)
/*! KEYOUTAVAIL - Next part of key is available */
#define PUF_STAT_KEYOUTAVAIL(x)                  (((uint32_t)(((uint32_t)(x)) << PUF_STAT_KEYOUTAVAIL_SHIFT)) & PUF_STAT_KEYOUTAVAIL_MASK)

#define PUF_STAT_CODEINREQ_MASK                  (0x40U)
#define PUF_STAT_CODEINREQ_SHIFT                 (6U)
/*! CODEINREQ - Request for next part of AC/KC */
#define PUF_STAT_CODEINREQ(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_STAT_CODEINREQ_SHIFT)) & PUF_STAT_CODEINREQ_MASK)

#define PUF_STAT_CODEOUTAVAIL_MASK               (0x80U)
#define PUF_STAT_CODEOUTAVAIL_SHIFT              (7U)
/*! CODEOUTAVAIL - Next part of AC/KC is available */
#define PUF_STAT_CODEOUTAVAIL(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_STAT_CODEOUTAVAIL_SHIFT)) & PUF_STAT_CODEOUTAVAIL_MASK)
/*! @} */

/*! @name ALLOW - PUF Allow register */
/*! @{ */

#define PUF_ALLOW_ALLOWENROLL_MASK               (0x1U)
#define PUF_ALLOW_ALLOWENROLL_SHIFT              (0U)
/*! ALLOWENROLL - Enroll operation is allowed */
#define PUF_ALLOW_ALLOWENROLL(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_ALLOW_ALLOWENROLL_SHIFT)) & PUF_ALLOW_ALLOWENROLL_MASK)

#define PUF_ALLOW_ALLOWSTART_MASK                (0x2U)
#define PUF_ALLOW_ALLOWSTART_SHIFT               (1U)
/*! ALLOWSTART - Start operation is allowed */
#define PUF_ALLOW_ALLOWSTART(x)                  (((uint32_t)(((uint32_t)(x)) << PUF_ALLOW_ALLOWSTART_SHIFT)) & PUF_ALLOW_ALLOWSTART_MASK)

#define PUF_ALLOW_ALLOWSETKEY_MASK               (0x4U)
#define PUF_ALLOW_ALLOWSETKEY_SHIFT              (2U)
/*! ALLOWSETKEY - Set Key operations are allowed */
#define PUF_ALLOW_ALLOWSETKEY(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_ALLOW_ALLOWSETKEY_SHIFT)) & PUF_ALLOW_ALLOWSETKEY_MASK)

#define PUF_ALLOW_ALLOWGETKEY_MASK               (0x8U)
#define PUF_ALLOW_ALLOWGETKEY_SHIFT              (3U)
/*! ALLOWGETKEY - Get Key operation is allowed */
#define PUF_ALLOW_ALLOWGETKEY(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_ALLOW_ALLOWGETKEY_SHIFT)) & PUF_ALLOW_ALLOWGETKEY_MASK)
/*! @} */

/*! @name KEYINPUT - PUF Key Input register */
/*! @{ */

#define PUF_KEYINPUT_KEYIN_MASK                  (0xFFFFFFFFU)
#define PUF_KEYINPUT_KEYIN_SHIFT                 (0U)
/*! KEYIN - Key input data */
#define PUF_KEYINPUT_KEYIN(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_KEYINPUT_KEYIN_SHIFT)) & PUF_KEYINPUT_KEYIN_MASK)
/*! @} */

/*! @name CODEINPUT - PUF Code Input register */
/*! @{ */

#define PUF_CODEINPUT_CODEIN_MASK                (0xFFFFFFFFU)
#define PUF_CODEINPUT_CODEIN_SHIFT               (0U)
/*! CODEIN - AC/KC input data */
#define PUF_CODEINPUT_CODEIN(x)                  (((uint32_t)(((uint32_t)(x)) << PUF_CODEINPUT_CODEIN_SHIFT)) & PUF_CODEINPUT_CODEIN_MASK)
/*! @} */

/*! @name CODEOUTPUT - PUF Code Output register */
/*! @{ */

#define PUF_CODEOUTPUT_CODEOUT_MASK              (0xFFFFFFFFU)
#define PUF_CODEOUTPUT_CODEOUT_SHIFT             (0U)
/*! CODEOUT - AC/KC output data */
#define PUF_CODEOUTPUT_CODEOUT(x)                (((uint32_t)(((uint32_t)(x)) << PUF_CODEOUTPUT_CODEOUT_SHIFT)) & PUF_CODEOUTPUT_CODEOUT_MASK)
/*! @} */

/*! @name KEYOUTINDEX - PUF Key Output Index register */
/*! @{ */

#define PUF_KEYOUTINDEX_KEYOUTIDX_MASK           (0xFU)
#define PUF_KEYOUTINDEX_KEYOUTIDX_SHIFT          (0U)
/*! KEYOUTIDX - Key index for the key that is currently output via the Key Output register */
#define PUF_KEYOUTINDEX_KEYOUTIDX(x)             (((uint32_t)(((uint32_t)(x)) << PUF_KEYOUTINDEX_KEYOUTIDX_SHIFT)) & PUF_KEYOUTINDEX_KEYOUTIDX_MASK)
/*! @} */

/*! @name KEYOUTPUT - PUF Key Output register */
/*! @{ */

#define PUF_KEYOUTPUT_KEYOUT_MASK                (0xFFFFFFFFU)
#define PUF_KEYOUTPUT_KEYOUT_SHIFT               (0U)
/*! KEYOUT - Key output data */
#define PUF_KEYOUTPUT_KEYOUT(x)                  (((uint32_t)(((uint32_t)(x)) << PUF_KEYOUTPUT_KEYOUT_SHIFT)) & PUF_KEYOUTPUT_KEYOUT_MASK)
/*! @} */

/*! @name IFSTAT - PUF Interface Status and clear register */
/*! @{ */

#define PUF_IFSTAT_ERROR_MASK                    (0x1U)
#define PUF_IFSTAT_ERROR_SHIFT                   (0U)
/*! ERROR - Indicates that an APB error has occurred,Writing logic1 clears the if_error bit */
#define PUF_IFSTAT_ERROR(x)                      (((uint32_t)(((uint32_t)(x)) << PUF_IFSTAT_ERROR_SHIFT)) & PUF_IFSTAT_ERROR_MASK)
/*! @} */

/*! @name INTEN - PUF Interrupt Enable */
/*! @{ */

#define PUF_INTEN_READYEN_MASK                   (0x1U)
#define PUF_INTEN_READYEN_SHIFT                  (0U)
/*! READYEN - Enable corresponding interrupt. Note that bit numbers match those assigned in QK_SR (Quiddikey Status Register) */
#define PUF_INTEN_READYEN(x)                     (((uint32_t)(((uint32_t)(x)) << PUF_INTEN_READYEN_SHIFT)) & PUF_INTEN_READYEN_MASK)

#define PUF_INTEN_SUCCESEN_MASK                  (0x2U)
#define PUF_INTEN_SUCCESEN_SHIFT                 (1U)
/*! SUCCESEN - Enable corresponding interrupt. Note that bit numbers match those assigned in QK_SR (Quiddikey Status Register) */
#define PUF_INTEN_SUCCESEN(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_INTEN_SUCCESEN_SHIFT)) & PUF_INTEN_SUCCESEN_MASK)

#define PUF_INTEN_ERROREN_MASK                   (0x4U)
#define PUF_INTEN_ERROREN_SHIFT                  (2U)
/*! ERROREN - Enable corresponding interrupt. Note that bit numbers match those assigned in QK_SR (Quiddikey Status Register) */
#define PUF_INTEN_ERROREN(x)                     (((uint32_t)(((uint32_t)(x)) << PUF_INTEN_ERROREN_SHIFT)) & PUF_INTEN_ERROREN_MASK)

#define PUF_INTEN_KEYINREQEN_MASK                (0x10U)
#define PUF_INTEN_KEYINREQEN_SHIFT               (4U)
/*! KEYINREQEN - Enable corresponding interrupt. Note that bit numbers match those assigned in QK_SR (Quiddikey Status Register) */
#define PUF_INTEN_KEYINREQEN(x)                  (((uint32_t)(((uint32_t)(x)) << PUF_INTEN_KEYINREQEN_SHIFT)) & PUF_INTEN_KEYINREQEN_MASK)

#define PUF_INTEN_KEYOUTAVAILEN_MASK             (0x20U)
#define PUF_INTEN_KEYOUTAVAILEN_SHIFT            (5U)
/*! KEYOUTAVAILEN - Enable corresponding interrupt. Note that bit numbers match those assigned in QK_SR (Quiddikey Status Register) */
#define PUF_INTEN_KEYOUTAVAILEN(x)               (((uint32_t)(((uint32_t)(x)) << PUF_INTEN_KEYOUTAVAILEN_SHIFT)) & PUF_INTEN_KEYOUTAVAILEN_MASK)

#define PUF_INTEN_CODEINREQEN_MASK               (0x40U)
#define PUF_INTEN_CODEINREQEN_SHIFT              (6U)
/*! CODEINREQEN - Enable corresponding interrupt. Note that bit numbers match those assigned in QK_SR (Quiddikey Status Register) */
#define PUF_INTEN_CODEINREQEN(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_INTEN_CODEINREQEN_SHIFT)) & PUF_INTEN_CODEINREQEN_MASK)

#define PUF_INTEN_CODEOUTAVAILEN_MASK            (0x80U)
#define PUF_INTEN_CODEOUTAVAILEN_SHIFT           (7U)
/*! CODEOUTAVAILEN - Enable corresponding interrupt. Note that bit numbers match those assigned in QK_SR (Quiddikey Status Register) */
#define PUF_INTEN_CODEOUTAVAILEN(x)              (((uint32_t)(((uint32_t)(x)) << PUF_INTEN_CODEOUTAVAILEN_SHIFT)) & PUF_INTEN_CODEOUTAVAILEN_MASK)
/*! @} */

/*! @name INTSTAT - PUF interrupt status */
/*! @{ */

#define PUF_INTSTAT_READY_MASK                   (0x1U)
#define PUF_INTSTAT_READY_SHIFT                  (0U)
/*! READY - Triggers on falling edge of busy, write 1 to clear */
#define PUF_INTSTAT_READY(x)                     (((uint32_t)(((uint32_t)(x)) << PUF_INTSTAT_READY_SHIFT)) & PUF_INTSTAT_READY_MASK)

#define PUF_INTSTAT_SUCCESS_MASK                 (0x2U)
#define PUF_INTSTAT_SUCCESS_SHIFT                (1U)
/*! SUCCESS - Level sensitive interrupt, cleared when interrupt source clears */
#define PUF_INTSTAT_SUCCESS(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_INTSTAT_SUCCESS_SHIFT)) & PUF_INTSTAT_SUCCESS_MASK)

#define PUF_INTSTAT_ERROR_MASK                   (0x4U)
#define PUF_INTSTAT_ERROR_SHIFT                  (2U)
/*! ERROR - Level sensitive interrupt, cleared when interrupt source clears */
#define PUF_INTSTAT_ERROR(x)                     (((uint32_t)(((uint32_t)(x)) << PUF_INTSTAT_ERROR_SHIFT)) & PUF_INTSTAT_ERROR_MASK)

#define PUF_INTSTAT_KEYINREQ_MASK                (0x10U)
#define PUF_INTSTAT_KEYINREQ_SHIFT               (4U)
/*! KEYINREQ - Level sensitive interrupt, cleared when interrupt source clears */
#define PUF_INTSTAT_KEYINREQ(x)                  (((uint32_t)(((uint32_t)(x)) << PUF_INTSTAT_KEYINREQ_SHIFT)) & PUF_INTSTAT_KEYINREQ_MASK)

#define PUF_INTSTAT_KEYOUTAVAIL_MASK             (0x20U)
#define PUF_INTSTAT_KEYOUTAVAIL_SHIFT            (5U)
/*! KEYOUTAVAIL - Level sensitive interrupt, cleared when interrupt source clears */
#define PUF_INTSTAT_KEYOUTAVAIL(x)               (((uint32_t)(((uint32_t)(x)) << PUF_INTSTAT_KEYOUTAVAIL_SHIFT)) & PUF_INTSTAT_KEYOUTAVAIL_MASK)

#define PUF_INTSTAT_CODEINREQ_MASK               (0x40U)
#define PUF_INTSTAT_CODEINREQ_SHIFT              (6U)
/*! CODEINREQ - Level sensitive interrupt, cleared when interrupt source clears */
#define PUF_INTSTAT_CODEINREQ(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_INTSTAT_CODEINREQ_SHIFT)) & PUF_INTSTAT_CODEINREQ_MASK)

#define PUF_INTSTAT_CODEOUTAVAIL_MASK            (0x80U)
#define PUF_INTSTAT_CODEOUTAVAIL_SHIFT           (7U)
/*! CODEOUTAVAIL - Level sensitive interrupt, cleared when interrupt source clears */
#define PUF_INTSTAT_CODEOUTAVAIL(x)              (((uint32_t)(((uint32_t)(x)) << PUF_INTSTAT_CODEOUTAVAIL_SHIFT)) & PUF_INTSTAT_CODEOUTAVAIL_MASK)
/*! @} */

/*! @name CFG - PUF config register for block bits */
/*! @{ */

#define PUF_CFG_BLOCKENROLL_SETKEY_MASK          (0x1U)
#define PUF_CFG_BLOCKENROLL_SETKEY_SHIFT         (0U)
/*! BLOCKENROLL_SETKEY - Block enroll operation. Write 1 to set, cleared on reset. */
#define PUF_CFG_BLOCKENROLL_SETKEY(x)            (((uint32_t)(((uint32_t)(x)) << PUF_CFG_BLOCKENROLL_SETKEY_SHIFT)) & PUF_CFG_BLOCKENROLL_SETKEY_MASK)

#define PUF_CFG_BLOCKKEYOUTPUT_MASK              (0x2U)
#define PUF_CFG_BLOCKKEYOUTPUT_SHIFT             (1U)
/*! BLOCKKEYOUTPUT - Block set key operation. Write 1 to set, cleared on reset. */
#define PUF_CFG_BLOCKKEYOUTPUT(x)                (((uint32_t)(((uint32_t)(x)) << PUF_CFG_BLOCKKEYOUTPUT_SHIFT)) & PUF_CFG_BLOCKKEYOUTPUT_MASK)
/*! @} */

/*! @name KEYLOCK - Only reset in case of full IC reset */
/*! @{ */

#define PUF_KEYLOCK_KEY0_MASK                    (0x3U)
#define PUF_KEYLOCK_KEY0_SHIFT                   (0U)
/*! KEY0 - "10:Write access to KEY0MASK, KEYENABLE.KEY0 and KEYRESET.KEY0 is allowed. 00, 01,
 *    11:Write access to KEY0MASK, KEYENABLE.KEY0 and KEYRESET.KEY0 is NOT allowed. Important Note : Once
 *    this field is written with a value different from '10', its value can no longer be modified
 *    until un Power On Reset occurs."
 */
#define PUF_KEYLOCK_KEY0(x)                      (((uint32_t)(((uint32_t)(x)) << PUF_KEYLOCK_KEY0_SHIFT)) & PUF_KEYLOCK_KEY0_MASK)

#define PUF_KEYLOCK_KEY1_MASK                    (0xCU)
#define PUF_KEYLOCK_KEY1_SHIFT                   (2U)
/*! KEY1 - "10:Write access to KEY1MASK, KEYENABLE.KEY1 and KEYRESET.KEY1 is allowed. 00, 01,
 *    11:Write access to KEY1MASK, KEYENABLE.KEY1 and KEYRESET.KEY1 is NOT allowed. Important Note : Once
 *    this field is written with a value different from '10', its value can no longer be modified
 *    until un Power On Reset occurs."
 */
#define PUF_KEYLOCK_KEY1(x)                      (((uint32_t)(((uint32_t)(x)) << PUF_KEYLOCK_KEY1_SHIFT)) & PUF_KEYLOCK_KEY1_MASK)

#define PUF_KEYLOCK_KEY2_MASK                    (0x30U)
#define PUF_KEYLOCK_KEY2_SHIFT                   (4U)
/*! KEY2 - "10:Write access to KEY2MASK, KEYENABLE.KEY2 and KEYRESET.KEY2 is allowed. 00, 01,
 *    11:Write access to KEY2MASK, KEYENABLE.KEY2 and KEYRESET.KEY2 is NOT allowed. Important Note : Once
 *    this field is written with a value different from '10', its value can no longer be modified
 *    until un Power On Reset occurs."
 */
#define PUF_KEYLOCK_KEY2(x)                      (((uint32_t)(((uint32_t)(x)) << PUF_KEYLOCK_KEY2_SHIFT)) & PUF_KEYLOCK_KEY2_MASK)

#define PUF_KEYLOCK_KEY3_MASK                    (0xC0U)
#define PUF_KEYLOCK_KEY3_SHIFT                   (6U)
/*! KEY3 - "10:Write access to KEY3MASK, KEYENABLE.KEY3 and KEYRESET.KEY3 is allowed. 00, 01,
 *    11:Write access to KEY3MASK, KEYENABLE.KEY3 and KEYRESET.KEY3 is NOT allowed. Important Note : Once
 *    this field is written with a value different from '10', its value can no longer be modified
 *    until un Power On Reset occurs."
 */
#define PUF_KEYLOCK_KEY3(x)                      (((uint32_t)(((uint32_t)(x)) << PUF_KEYLOCK_KEY3_SHIFT)) & PUF_KEYLOCK_KEY3_MASK)
/*! @} */

/*! @name KEYENABLE -  */
/*! @{ */

#define PUF_KEYENABLE_KEY0_MASK                  (0x3U)
#define PUF_KEYENABLE_KEY0_SHIFT                 (0U)
/*! KEY0 - "10: Data coming out from PUF Index 0 interface are shifted in KEY0 register. 00, 01, 11
 *    : Data coming out from PUF Index 0 interface are NOT shifted in KEY0 register."
 */
#define PUF_KEYENABLE_KEY0(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_KEYENABLE_KEY0_SHIFT)) & PUF_KEYENABLE_KEY0_MASK)

#define PUF_KEYENABLE_KEY1_MASK                  (0xCU)
#define PUF_KEYENABLE_KEY1_SHIFT                 (2U)
/*! KEY1 - "10: Data coming out from PUF Index 0 interface are shifted in KEY1 register. 00, 01, 11
 *    : Data coming out from PUF Index 0 interface are NOT shifted in KEY1 register."
 */
#define PUF_KEYENABLE_KEY1(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_KEYENABLE_KEY1_SHIFT)) & PUF_KEYENABLE_KEY1_MASK)

#define PUF_KEYENABLE_KEY2_MASK                  (0x30U)
#define PUF_KEYENABLE_KEY2_SHIFT                 (4U)
/*! KEY2 - "10: Data coming out from PUF Index 0 interface are shifted in KEY2 register. 00, 01, 11
 *    : Data coming out from PUF Index 0 interface are NOT shifted in KEY2 register."
 */
#define PUF_KEYENABLE_KEY2(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_KEYENABLE_KEY2_SHIFT)) & PUF_KEYENABLE_KEY2_MASK)

#define PUF_KEYENABLE_KEY3_MASK                  (0xC0U)
#define PUF_KEYENABLE_KEY3_SHIFT                 (6U)
/*! KEY3 - "10: Data coming out from PUF Index 0 interface are shifted in KEY3 register. 00, 01, 11
 *    : Data coming out from PUF Index 0 interface are NOT shifted in KEY3 register."
 */
#define PUF_KEYENABLE_KEY3(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_KEYENABLE_KEY3_SHIFT)) & PUF_KEYENABLE_KEY3_MASK)
/*! @} */

/*! @name KEYRESET - Reinitialize Keys shift registers counters */
/*! @{ */

#define PUF_KEYRESET_KEY0_MASK                   (0x3U)
#define PUF_KEYRESET_KEY0_SHIFT                  (0U)
/*! KEY0 - 10: Reset KEY0 shift register. Self clearing. Must be done before loading any new key. */
#define PUF_KEYRESET_KEY0(x)                     (((uint32_t)(((uint32_t)(x)) << PUF_KEYRESET_KEY0_SHIFT)) & PUF_KEYRESET_KEY0_MASK)

#define PUF_KEYRESET_KEY1_MASK                   (0xCU)
#define PUF_KEYRESET_KEY1_SHIFT                  (2U)
/*! KEY1 - 10: Reset KEY1 shift register. Self clearing. Must be done before loading any new key. */
#define PUF_KEYRESET_KEY1(x)                     (((uint32_t)(((uint32_t)(x)) << PUF_KEYRESET_KEY1_SHIFT)) & PUF_KEYRESET_KEY1_MASK)

#define PUF_KEYRESET_KEY2_MASK                   (0x30U)
#define PUF_KEYRESET_KEY2_SHIFT                  (4U)
/*! KEY2 - 10: Reset KEY2 shift register. Self clearing. Must be done before loading any new key. */
#define PUF_KEYRESET_KEY2(x)                     (((uint32_t)(((uint32_t)(x)) << PUF_KEYRESET_KEY2_SHIFT)) & PUF_KEYRESET_KEY2_MASK)

#define PUF_KEYRESET_KEY3_MASK                   (0xC0U)
#define PUF_KEYRESET_KEY3_SHIFT                  (6U)
/*! KEY3 - 10: Reset KEY3 shift register. Self clearing. Must be done before loading any new key. */
#define PUF_KEYRESET_KEY3(x)                     (((uint32_t)(((uint32_t)(x)) << PUF_KEYRESET_KEY3_SHIFT)) & PUF_KEYRESET_KEY3_MASK)
/*! @} */

/*! @name IDXBLK -  */
/*! @{ */

#define PUF_IDXBLK_IDX0_MASK                     (0x3U)
#define PUF_IDXBLK_IDX0_SHIFT                    (0U)
/*! IDX0 - Use to block PUF index 0 */
#define PUF_IDXBLK_IDX0(x)                       (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDX0_SHIFT)) & PUF_IDXBLK_IDX0_MASK)

#define PUF_IDXBLK_IDX1_MASK                     (0xCU)
#define PUF_IDXBLK_IDX1_SHIFT                    (2U)
/*! IDX1 - Use to block PUF index 1 */
#define PUF_IDXBLK_IDX1(x)                       (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDX1_SHIFT)) & PUF_IDXBLK_IDX1_MASK)

#define PUF_IDXBLK_IDX2_MASK                     (0x30U)
#define PUF_IDXBLK_IDX2_SHIFT                    (4U)
/*! IDX2 - Use to block PUF index 2 */
#define PUF_IDXBLK_IDX2(x)                       (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDX2_SHIFT)) & PUF_IDXBLK_IDX2_MASK)

#define PUF_IDXBLK_IDX3_MASK                     (0xC0U)
#define PUF_IDXBLK_IDX3_SHIFT                    (6U)
/*! IDX3 - Use to block PUF index 3 */
#define PUF_IDXBLK_IDX3(x)                       (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDX3_SHIFT)) & PUF_IDXBLK_IDX3_MASK)

#define PUF_IDXBLK_IDX4_MASK                     (0x300U)
#define PUF_IDXBLK_IDX4_SHIFT                    (8U)
/*! IDX4 - Use to block PUF index 4 */
#define PUF_IDXBLK_IDX4(x)                       (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDX4_SHIFT)) & PUF_IDXBLK_IDX4_MASK)

#define PUF_IDXBLK_IDX5_MASK                     (0xC00U)
#define PUF_IDXBLK_IDX5_SHIFT                    (10U)
/*! IDX5 - Use to block PUF index 5 */
#define PUF_IDXBLK_IDX5(x)                       (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDX5_SHIFT)) & PUF_IDXBLK_IDX5_MASK)

#define PUF_IDXBLK_IDX6_MASK                     (0x3000U)
#define PUF_IDXBLK_IDX6_SHIFT                    (12U)
/*! IDX6 - Use to block PUF index 6 */
#define PUF_IDXBLK_IDX6(x)                       (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDX6_SHIFT)) & PUF_IDXBLK_IDX6_MASK)

#define PUF_IDXBLK_IDX7_MASK                     (0xC000U)
#define PUF_IDXBLK_IDX7_SHIFT                    (14U)
/*! IDX7 - Use to block PUF index 7 */
#define PUF_IDXBLK_IDX7(x)                       (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDX7_SHIFT)) & PUF_IDXBLK_IDX7_MASK)

#define PUF_IDXBLK_IDX8_MASK                     (0x30000U)
#define PUF_IDXBLK_IDX8_SHIFT                    (16U)
/*! IDX8 - Use to block PUF index 8 */
#define PUF_IDXBLK_IDX8(x)                       (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDX8_SHIFT)) & PUF_IDXBLK_IDX8_MASK)

#define PUF_IDXBLK_IDX9_MASK                     (0xC0000U)
#define PUF_IDXBLK_IDX9_SHIFT                    (18U)
/*! IDX9 - Use to block PUF index 9 */
#define PUF_IDXBLK_IDX9(x)                       (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDX9_SHIFT)) & PUF_IDXBLK_IDX9_MASK)

#define PUF_IDXBLK_IDX10_MASK                    (0x300000U)
#define PUF_IDXBLK_IDX10_SHIFT                   (20U)
/*! IDX10 - Use to block PUF index 10 */
#define PUF_IDXBLK_IDX10(x)                      (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDX10_SHIFT)) & PUF_IDXBLK_IDX10_MASK)

#define PUF_IDXBLK_IDX11_MASK                    (0xC00000U)
#define PUF_IDXBLK_IDX11_SHIFT                   (22U)
/*! IDX11 - Use to block PUF index 11 */
#define PUF_IDXBLK_IDX11(x)                      (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDX11_SHIFT)) & PUF_IDXBLK_IDX11_MASK)

#define PUF_IDXBLK_IDX12_MASK                    (0x3000000U)
#define PUF_IDXBLK_IDX12_SHIFT                   (24U)
/*! IDX12 - Use to block PUF index 12 */
#define PUF_IDXBLK_IDX12(x)                      (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDX12_SHIFT)) & PUF_IDXBLK_IDX12_MASK)

#define PUF_IDXBLK_IDX13_MASK                    (0xC000000U)
#define PUF_IDXBLK_IDX13_SHIFT                   (26U)
/*! IDX13 - Use to block PUF index 13 */
#define PUF_IDXBLK_IDX13(x)                      (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDX13_SHIFT)) & PUF_IDXBLK_IDX13_MASK)

#define PUF_IDXBLK_IDX14_MASK                    (0x30000000U)
#define PUF_IDXBLK_IDX14_SHIFT                   (28U)
/*! IDX14 - Use to block PUF index 14 */
#define PUF_IDXBLK_IDX14(x)                      (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDX14_SHIFT)) & PUF_IDXBLK_IDX14_MASK)

#define PUF_IDXBLK_IDX15_MASK                    (0xC0000000U)
#define PUF_IDXBLK_IDX15_SHIFT                   (30U)
/*! IDX15 - Use to block PUF index 15 */
#define PUF_IDXBLK_IDX15(x)                      (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDX15_SHIFT)) & PUF_IDXBLK_IDX15_MASK)
/*! @} */

/*! @name IDXBLK_DP -  */
/*! @{ */

#define PUF_IDXBLK_DP_IDX0_MASK                  (0x3U)
#define PUF_IDXBLK_DP_IDX0_SHIFT                 (0U)
/*! IDX0 - Use to block PUF index 0 */
#define PUF_IDXBLK_DP_IDX0(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDX0_SHIFT)) & PUF_IDXBLK_DP_IDX0_MASK)

#define PUF_IDXBLK_DP_IDX1_MASK                  (0xCU)
#define PUF_IDXBLK_DP_IDX1_SHIFT                 (2U)
/*! IDX1 - Use to block PUF index 1 */
#define PUF_IDXBLK_DP_IDX1(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDX1_SHIFT)) & PUF_IDXBLK_DP_IDX1_MASK)

#define PUF_IDXBLK_DP_IDX2_MASK                  (0x30U)
#define PUF_IDXBLK_DP_IDX2_SHIFT                 (4U)
/*! IDX2 - Use to block PUF index 2 */
#define PUF_IDXBLK_DP_IDX2(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDX2_SHIFT)) & PUF_IDXBLK_DP_IDX2_MASK)

#define PUF_IDXBLK_DP_IDX3_MASK                  (0xC0U)
#define PUF_IDXBLK_DP_IDX3_SHIFT                 (6U)
/*! IDX3 - Use to block PUF index 3 */
#define PUF_IDXBLK_DP_IDX3(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDX3_SHIFT)) & PUF_IDXBLK_DP_IDX3_MASK)

#define PUF_IDXBLK_DP_IDX4_MASK                  (0x300U)
#define PUF_IDXBLK_DP_IDX4_SHIFT                 (8U)
/*! IDX4 - Use to block PUF index 4 */
#define PUF_IDXBLK_DP_IDX4(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDX4_SHIFT)) & PUF_IDXBLK_DP_IDX4_MASK)

#define PUF_IDXBLK_DP_IDX5_MASK                  (0xC00U)
#define PUF_IDXBLK_DP_IDX5_SHIFT                 (10U)
/*! IDX5 - Use to block PUF index 5 */
#define PUF_IDXBLK_DP_IDX5(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDX5_SHIFT)) & PUF_IDXBLK_DP_IDX5_MASK)

#define PUF_IDXBLK_DP_IDX6_MASK                  (0x3000U)
#define PUF_IDXBLK_DP_IDX6_SHIFT                 (12U)
/*! IDX6 - Use to block PUF index 6 */
#define PUF_IDXBLK_DP_IDX6(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDX6_SHIFT)) & PUF_IDXBLK_DP_IDX6_MASK)

#define PUF_IDXBLK_DP_IDX7_MASK                  (0xC000U)
#define PUF_IDXBLK_DP_IDX7_SHIFT                 (14U)
/*! IDX7 - Use to block PUF index 7 */
#define PUF_IDXBLK_DP_IDX7(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDX7_SHIFT)) & PUF_IDXBLK_DP_IDX7_MASK)

#define PUF_IDXBLK_DP_IDX8_MASK                  (0x30000U)
#define PUF_IDXBLK_DP_IDX8_SHIFT                 (16U)
/*! IDX8 - Use to block PUF index 8 */
#define PUF_IDXBLK_DP_IDX8(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDX8_SHIFT)) & PUF_IDXBLK_DP_IDX8_MASK)

#define PUF_IDXBLK_DP_IDX9_MASK                  (0xC0000U)
#define PUF_IDXBLK_DP_IDX9_SHIFT                 (18U)
/*! IDX9 - Use to block PUF index 9 */
#define PUF_IDXBLK_DP_IDX9(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDX9_SHIFT)) & PUF_IDXBLK_DP_IDX9_MASK)

#define PUF_IDXBLK_DP_IDX10_MASK                 (0x300000U)
#define PUF_IDXBLK_DP_IDX10_SHIFT                (20U)
/*! IDX10 - Use to block PUF index 10 */
#define PUF_IDXBLK_DP_IDX10(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDX10_SHIFT)) & PUF_IDXBLK_DP_IDX10_MASK)

#define PUF_IDXBLK_DP_IDX11_MASK                 (0xC00000U)
#define PUF_IDXBLK_DP_IDX11_SHIFT                (22U)
/*! IDX11 - Use to block PUF index 11 */
#define PUF_IDXBLK_DP_IDX11(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDX11_SHIFT)) & PUF_IDXBLK_DP_IDX11_MASK)

#define PUF_IDXBLK_DP_IDX12_MASK                 (0x3000000U)
#define PUF_IDXBLK_DP_IDX12_SHIFT                (24U)
/*! IDX12 - Use to block PUF index 12 */
#define PUF_IDXBLK_DP_IDX12(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDX12_SHIFT)) & PUF_IDXBLK_DP_IDX12_MASK)

#define PUF_IDXBLK_DP_IDX13_MASK                 (0xC000000U)
#define PUF_IDXBLK_DP_IDX13_SHIFT                (26U)
/*! IDX13 - Use to block PUF index 13 */
#define PUF_IDXBLK_DP_IDX13(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDX13_SHIFT)) & PUF_IDXBLK_DP_IDX13_MASK)

#define PUF_IDXBLK_DP_IDX14_MASK                 (0x30000000U)
#define PUF_IDXBLK_DP_IDX14_SHIFT                (28U)
/*! IDX14 - Use to block PUF index 14 */
#define PUF_IDXBLK_DP_IDX14(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDX14_SHIFT)) & PUF_IDXBLK_DP_IDX14_MASK)

#define PUF_IDXBLK_DP_IDX15_MASK                 (0xC0000000U)
#define PUF_IDXBLK_DP_IDX15_SHIFT                (30U)
/*! IDX15 - Use to block PUF index 15 */
#define PUF_IDXBLK_DP_IDX15(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDX15_SHIFT)) & PUF_IDXBLK_DP_IDX15_MASK)
/*! @} */

/*! @name KEYMASK - Only reset in case of full IC reset */
/*! @{ */

#define PUF_KEYMASK_KEYMASK_MASK                 (0xFFFFFFFFU)
#define PUF_KEYMASK_KEYMASK_SHIFT                (0U)
#define PUF_KEYMASK_KEYMASK(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_KEYMASK_KEYMASK_SHIFT)) & PUF_KEYMASK_KEYMASK_MASK)
/*! @} */

/*! @name IDXBLK_STATUS - Index block status */
/*! @{ */

#define PUF_IDXBLK_STATUS_IDX0_MASK              (0x3U)
#define PUF_IDXBLK_STATUS_IDX0_SHIFT             (0U)
/*! IDX0 - Status block index 0 */
#define PUF_IDXBLK_STATUS_IDX0(x)                (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDX0_SHIFT)) & PUF_IDXBLK_STATUS_IDX0_MASK)

#define PUF_IDXBLK_STATUS_IDX1_MASK              (0xCU)
#define PUF_IDXBLK_STATUS_IDX1_SHIFT             (2U)
/*! IDX1 - Status block index 1 */
#define PUF_IDXBLK_STATUS_IDX1(x)                (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDX1_SHIFT)) & PUF_IDXBLK_STATUS_IDX1_MASK)

#define PUF_IDXBLK_STATUS_IDX2_MASK              (0x30U)
#define PUF_IDXBLK_STATUS_IDX2_SHIFT             (4U)
/*! IDX2 - Status block index 2 */
#define PUF_IDXBLK_STATUS_IDX2(x)                (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDX2_SHIFT)) & PUF_IDXBLK_STATUS_IDX2_MASK)

#define PUF_IDXBLK_STATUS_IDX3_MASK              (0xC0U)
#define PUF_IDXBLK_STATUS_IDX3_SHIFT             (6U)
/*! IDX3 - Status block index 3 */
#define PUF_IDXBLK_STATUS_IDX3(x)                (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDX3_SHIFT)) & PUF_IDXBLK_STATUS_IDX3_MASK)

#define PUF_IDXBLK_STATUS_IDX4_MASK              (0x300U)
#define PUF_IDXBLK_STATUS_IDX4_SHIFT             (8U)
/*! IDX4 - Status block index 4 */
#define PUF_IDXBLK_STATUS_IDX4(x)                (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDX4_SHIFT)) & PUF_IDXBLK_STATUS_IDX4_MASK)

#define PUF_IDXBLK_STATUS_IDX5_MASK              (0xC00U)
#define PUF_IDXBLK_STATUS_IDX5_SHIFT             (10U)
/*! IDX5 - Status block index 5 */
#define PUF_IDXBLK_STATUS_IDX5(x)                (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDX5_SHIFT)) & PUF_IDXBLK_STATUS_IDX5_MASK)

#define PUF_IDXBLK_STATUS_IDX6_MASK              (0x3000U)
#define PUF_IDXBLK_STATUS_IDX6_SHIFT             (12U)
/*! IDX6 - Status block index 6 */
#define PUF_IDXBLK_STATUS_IDX6(x)                (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDX6_SHIFT)) & PUF_IDXBLK_STATUS_IDX6_MASK)

#define PUF_IDXBLK_STATUS_IDX7_MASK              (0xC000U)
#define PUF_IDXBLK_STATUS_IDX7_SHIFT             (14U)
/*! IDX7 - Status block index 7 */
#define PUF_IDXBLK_STATUS_IDX7(x)                (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDX7_SHIFT)) & PUF_IDXBLK_STATUS_IDX7_MASK)

#define PUF_IDXBLK_STATUS_IDX8_MASK              (0x30000U)
#define PUF_IDXBLK_STATUS_IDX8_SHIFT             (16U)
/*! IDX8 - Status block index 8 */
#define PUF_IDXBLK_STATUS_IDX8(x)                (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDX8_SHIFT)) & PUF_IDXBLK_STATUS_IDX8_MASK)

#define PUF_IDXBLK_STATUS_IDX9_MASK              (0xC0000U)
#define PUF_IDXBLK_STATUS_IDX9_SHIFT             (18U)
/*! IDX9 - Status block index 9 */
#define PUF_IDXBLK_STATUS_IDX9(x)                (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDX9_SHIFT)) & PUF_IDXBLK_STATUS_IDX9_MASK)

#define PUF_IDXBLK_STATUS_IDX10_MASK             (0x300000U)
#define PUF_IDXBLK_STATUS_IDX10_SHIFT            (20U)
/*! IDX10 - Status block index 10 */
#define PUF_IDXBLK_STATUS_IDX10(x)               (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDX10_SHIFT)) & PUF_IDXBLK_STATUS_IDX10_MASK)

#define PUF_IDXBLK_STATUS_IDX11_MASK             (0xC00000U)
#define PUF_IDXBLK_STATUS_IDX11_SHIFT            (22U)
/*! IDX11 - Status block index 11 */
#define PUF_IDXBLK_STATUS_IDX11(x)               (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDX11_SHIFT)) & PUF_IDXBLK_STATUS_IDX11_MASK)

#define PUF_IDXBLK_STATUS_IDX12_MASK             (0x3000000U)
#define PUF_IDXBLK_STATUS_IDX12_SHIFT            (24U)
/*! IDX12 - Status block index 12 */
#define PUF_IDXBLK_STATUS_IDX12(x)               (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDX12_SHIFT)) & PUF_IDXBLK_STATUS_IDX12_MASK)

#define PUF_IDXBLK_STATUS_IDX13_MASK             (0xC000000U)
#define PUF_IDXBLK_STATUS_IDX13_SHIFT            (26U)
/*! IDX13 - Status block index 13 */
#define PUF_IDXBLK_STATUS_IDX13(x)               (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDX13_SHIFT)) & PUF_IDXBLK_STATUS_IDX13_MASK)

#define PUF_IDXBLK_STATUS_IDX14_MASK             (0x30000000U)
#define PUF_IDXBLK_STATUS_IDX14_SHIFT            (28U)
/*! IDX14 - Status block index 14 */
#define PUF_IDXBLK_STATUS_IDX14(x)               (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDX14_SHIFT)) & PUF_IDXBLK_STATUS_IDX14_MASK)

#define PUF_IDXBLK_STATUS_IDX15_MASK             (0xC0000000U)
#define PUF_IDXBLK_STATUS_IDX15_SHIFT            (30U)
/*! IDX15 - Status block index 15 */
#define PUF_IDXBLK_STATUS_IDX15(x)               (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDX15_SHIFT)) & PUF_IDXBLK_STATUS_IDX15_MASK)
/*! @} */

/*! @name SHIFT_STATUS -  */
/*! @{ */

#define PUF_SHIFT_STATUS_KEY0_MASK               (0xFU)
#define PUF_SHIFT_STATUS_KEY0_SHIFT              (0U)
/*! KEY0 - Index counter from key 0 shift register */
#define PUF_SHIFT_STATUS_KEY0(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_SHIFT_STATUS_KEY0_SHIFT)) & PUF_SHIFT_STATUS_KEY0_MASK)

#define PUF_SHIFT_STATUS_KEY1_MASK               (0xF0U)
#define PUF_SHIFT_STATUS_KEY1_SHIFT              (4U)
/*! KEY1 - Index counter from key 1 shift register */
#define PUF_SHIFT_STATUS_KEY1(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_SHIFT_STATUS_KEY1_SHIFT)) & PUF_SHIFT_STATUS_KEY1_MASK)

#define PUF_SHIFT_STATUS_KEY2_MASK               (0xF00U)
#define PUF_SHIFT_STATUS_KEY2_SHIFT              (8U)
/*! KEY2 - Index counter from key 2 shift register */
#define PUF_SHIFT_STATUS_KEY2(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_SHIFT_STATUS_KEY2_SHIFT)) & PUF_SHIFT_STATUS_KEY2_MASK)

#define PUF_SHIFT_STATUS_KEY3_MASK               (0xF000U)
#define PUF_SHIFT_STATUS_KEY3_SHIFT              (12U)
/*! KEY3 - Index counter from key 3 shift register */
#define PUF_SHIFT_STATUS_KEY3(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_SHIFT_STATUS_KEY3_SHIFT)) & PUF_SHIFT_STATUS_KEY3_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group PUF_Register_Masks */


/*!
 * @}
 */ /* end of group PUF_Peripheral_Access_Layer */


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


#endif  /* PUF_H_ */


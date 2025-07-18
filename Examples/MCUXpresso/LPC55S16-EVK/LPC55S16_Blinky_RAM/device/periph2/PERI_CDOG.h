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
**         CMSIS Peripheral Access Layer for CDOG
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
 * @file CDOG.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for CDOG
 *
 * CMSIS Peripheral Access Layer for CDOG
 */

#if !defined(CDOG_H_)
#define CDOG_H_                                  /**< Symbol preventing repeated inclusion */

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
   -- CDOG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CDOG_Peripheral_Access_Layer CDOG Peripheral Access Layer
 * @{
 */

/** CDOG - Register Layout Typedef */
typedef struct {
  __IO uint32_t CONTROL;                           /**< The control fields, which constitute CONTROL, control all controllable attributes of the module, including those of CONTROL itself., offset: 0x0 */
  __IO uint32_t RELOAD;                            /**< Instruction timer reload, offset: 0x4 */
  __IO uint32_t INSTRUCTION_TIMER;                 /**< The INSTRUCTION TIMER itself, offset: 0x8 */
  __IO uint32_t SECURE_COUNTER;                    /**< Also known as SEC_CNT, offset: 0xC */
  __I  uint32_t STATUS;                            /**< Status register (1 of 2), offset: 0x10 */
  __I  uint32_t STATUS2;                           /**< STATUS register (2 of 2), offset: 0x14 */
  __IO uint32_t FLAGS;                             /**< Hardware flags, offset: 0x18 */
  __IO uint32_t PERSISTENT;                        /**< Persistent (Ad. Hoc., quasi-NV) data storage, offset: 0x1C */
  __O  uint32_t START;                             /**< Write address for issuing the START command., offset: 0x20 */
  __O  uint32_t STOP;                              /**< Write address for issuing the STOP command., offset: 0x24 */
  __O  uint32_t RESTART;                           /**< Write address for issuing the RESTART command., offset: 0x28 */
  __O  uint32_t ADD;                               /**< Write address for issuing the ADD command., offset: 0x2C */
  __O  uint32_t ADD1;                              /**< Write address for issuing the ADD1 command., offset: 0x30 */
  __O  uint32_t ADD16;                             /**< Write address for issuing the ADD16 command., offset: 0x34 */
  __O  uint32_t ADD256;                            /**< Write address for issuing the ADD16 command., offset: 0x38 */
  __O  uint32_t SUB;                               /**< Write address for issuing the SUB command., offset: 0x3C */
  __O  uint32_t SUB1;                              /**< Write address for issuing the SUB1 command., offset: 0x40 */
  __O  uint32_t SUB16;                             /**< Write address for issuing the SUB16 command., offset: 0x44 */
  __O  uint32_t SUB256;                            /**< Write address for issuing the SUB256 command., offset: 0x48 */
} CDOG_Type;

/* ----------------------------------------------------------------------------
   -- CDOG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CDOG_Register_Masks CDOG Register Masks
 * @{
 */

/*! @name CONTROL - The control fields, which constitute CONTROL, control all controllable attributes of the module, including those of CONTROL itself. */
/*! @{ */

#define CDOG_CONTROL_LOCK_CTRL_MASK              (0x3U)
#define CDOG_CONTROL_LOCK_CTRL_SHIFT             (0U)
/*! LOCK_CTRL - Lock control field */
#define CDOG_CONTROL_LOCK_CTRL(x)                (((uint32_t)(((uint32_t)(x)) << CDOG_CONTROL_LOCK_CTRL_SHIFT)) & CDOG_CONTROL_LOCK_CTRL_MASK)

#define CDOG_CONTROL_TIMEOUT_CTRL_MASK           (0x1CU)
#define CDOG_CONTROL_TIMEOUT_CTRL_SHIFT          (2U)
/*! TIMEOUT_CTRL - TIMEOUT control */
#define CDOG_CONTROL_TIMEOUT_CTRL(x)             (((uint32_t)(((uint32_t)(x)) << CDOG_CONTROL_TIMEOUT_CTRL_SHIFT)) & CDOG_CONTROL_TIMEOUT_CTRL_MASK)

#define CDOG_CONTROL_MISCOMPARE_CTRL_MASK        (0xE0U)
#define CDOG_CONTROL_MISCOMPARE_CTRL_SHIFT       (5U)
/*! MISCOMPARE_CTRL - MISCOMPARE control field */
#define CDOG_CONTROL_MISCOMPARE_CTRL(x)          (((uint32_t)(((uint32_t)(x)) << CDOG_CONTROL_MISCOMPARE_CTRL_SHIFT)) & CDOG_CONTROL_MISCOMPARE_CTRL_MASK)

#define CDOG_CONTROL_SEQUENCE_CTRL_MASK          (0x700U)
#define CDOG_CONTROL_SEQUENCE_CTRL_SHIFT         (8U)
/*! SEQUENCE_CTRL - SEQUENCE control field */
#define CDOG_CONTROL_SEQUENCE_CTRL(x)            (((uint32_t)(((uint32_t)(x)) << CDOG_CONTROL_SEQUENCE_CTRL_SHIFT)) & CDOG_CONTROL_SEQUENCE_CTRL_MASK)

#define CDOG_CONTROL_CONTROL_CTRL_MASK           (0x3800U)
#define CDOG_CONTROL_CONTROL_CTRL_SHIFT          (11U)
/*! CONTROL_CTRL - CONTROL control field */
#define CDOG_CONTROL_CONTROL_CTRL(x)             (((uint32_t)(((uint32_t)(x)) << CDOG_CONTROL_CONTROL_CTRL_SHIFT)) & CDOG_CONTROL_CONTROL_CTRL_MASK)

#define CDOG_CONTROL_STATE_CTRL_MASK             (0x1C000U)
#define CDOG_CONTROL_STATE_CTRL_SHIFT            (14U)
/*! STATE_CTRL - STATE control field */
#define CDOG_CONTROL_STATE_CTRL(x)               (((uint32_t)(((uint32_t)(x)) << CDOG_CONTROL_STATE_CTRL_SHIFT)) & CDOG_CONTROL_STATE_CTRL_MASK)

#define CDOG_CONTROL_ADDRESS_CTRL_MASK           (0xE0000U)
#define CDOG_CONTROL_ADDRESS_CTRL_SHIFT          (17U)
/*! ADDRESS_CTRL - ADDRESS control field */
#define CDOG_CONTROL_ADDRESS_CTRL(x)             (((uint32_t)(((uint32_t)(x)) << CDOG_CONTROL_ADDRESS_CTRL_SHIFT)) & CDOG_CONTROL_ADDRESS_CTRL_MASK)

#define CDOG_CONTROL_Un_Imps_MASK                (0xFF00000U)
#define CDOG_CONTROL_Un_Imps_SHIFT               (20U)
/*! Un_Imps - The un-imps are un-IMPs! */
#define CDOG_CONTROL_Un_Imps(x)                  (((uint32_t)(((uint32_t)(x)) << CDOG_CONTROL_Un_Imps_SHIFT)) & CDOG_CONTROL_Un_Imps_MASK)

#define CDOG_CONTROL_IRQ_PAUSE_MASK              (0x30000000U)
#define CDOG_CONTROL_IRQ_PAUSE_SHIFT             (28U)
/*! IRQ_PAUSE - IRQ pause control field */
#define CDOG_CONTROL_IRQ_PAUSE(x)                (((uint32_t)(((uint32_t)(x)) << CDOG_CONTROL_IRQ_PAUSE_SHIFT)) & CDOG_CONTROL_IRQ_PAUSE_MASK)

#define CDOG_CONTROL_DEBUG_HALT_CTRL_MASK        (0xC0000000U)
#define CDOG_CONTROL_DEBUG_HALT_CTRL_SHIFT       (30U)
/*! DEBUG_HALT_CTRL - DEBUG_HALT control field */
#define CDOG_CONTROL_DEBUG_HALT_CTRL(x)          (((uint32_t)(((uint32_t)(x)) << CDOG_CONTROL_DEBUG_HALT_CTRL_SHIFT)) & CDOG_CONTROL_DEBUG_HALT_CTRL_MASK)
/*! @} */

/*! @name RELOAD - Instruction timer reload */
/*! @{ */

#define CDOG_RELOAD_RLOAD_MASK                   (0xFFFFFFFFU)
#define CDOG_RELOAD_RLOAD_SHIFT                  (0U)
/*! RLOAD - Inst. Timer reload value */
#define CDOG_RELOAD_RLOAD(x)                     (((uint32_t)(((uint32_t)(x)) << CDOG_RELOAD_RLOAD_SHIFT)) & CDOG_RELOAD_RLOAD_MASK)
/*! @} */

/*! @name INSTRUCTION_TIMER - The INSTRUCTION TIMER itself */
/*! @{ */

#define CDOG_INSTRUCTION_TIMER_INSTIM_MASK       (0xFFFFFFFFU)
#define CDOG_INSTRUCTION_TIMER_INSTIM_SHIFT      (0U)
/*! INSTIM - INSTRUCTION TIMER 32-bit value */
#define CDOG_INSTRUCTION_TIMER_INSTIM(x)         (((uint32_t)(((uint32_t)(x)) << CDOG_INSTRUCTION_TIMER_INSTIM_SHIFT)) & CDOG_INSTRUCTION_TIMER_INSTIM_MASK)
/*! @} */

/*! @name SECURE_COUNTER - Also known as SEC_CNT */
/*! @{ */

#define CDOG_SECURE_COUNTER_SECCNT_MASK          (0xFFFFFFFFU)
#define CDOG_SECURE_COUNTER_SECCNT_SHIFT         (0U)
/*! SECCNT - Secure Counter */
#define CDOG_SECURE_COUNTER_SECCNT(x)            (((uint32_t)(((uint32_t)(x)) << CDOG_SECURE_COUNTER_SECCNT_SHIFT)) & CDOG_SECURE_COUNTER_SECCNT_MASK)
/*! @} */

/*! @name STATUS - Status register (1 of 2) */
/*! @{ */

#define CDOG_STATUS_NUMTOF_MASK                  (0xFFU)
#define CDOG_STATUS_NUMTOF_SHIFT                 (0U)
/*! NUMTOF - Number of Timeout Faults */
#define CDOG_STATUS_NUMTOF(x)                    (((uint32_t)(((uint32_t)(x)) << CDOG_STATUS_NUMTOF_SHIFT)) & CDOG_STATUS_NUMTOF_MASK)

#define CDOG_STATUS_NUMMISCOMPF_MASK             (0xFF00U)
#define CDOG_STATUS_NUMMISCOMPF_SHIFT            (8U)
/*! NUMMISCOMPF - Number of Miscompare Faults */
#define CDOG_STATUS_NUMMISCOMPF(x)               (((uint32_t)(((uint32_t)(x)) << CDOG_STATUS_NUMMISCOMPF_SHIFT)) & CDOG_STATUS_NUMMISCOMPF_MASK)

#define CDOG_STATUS_NUMILSEQF_MASK               (0xFF0000U)
#define CDOG_STATUS_NUMILSEQF_SHIFT              (16U)
/*! NUMILSEQF - Number of illegal sequence faults */
#define CDOG_STATUS_NUMILSEQF(x)                 (((uint32_t)(((uint32_t)(x)) << CDOG_STATUS_NUMILSEQF_SHIFT)) & CDOG_STATUS_NUMILSEQF_MASK)

#define CDOG_STATUS_uN_iMps_MASK                 (0xF000000U)
#define CDOG_STATUS_uN_iMps_SHIFT                (24U)
/*! uN_iMps - Un implemented */
#define CDOG_STATUS_uN_iMps(x)                   (((uint32_t)(((uint32_t)(x)) << CDOG_STATUS_uN_iMps_SHIFT)) & CDOG_STATUS_uN_iMps_MASK)

#define CDOG_STATUS_CURST_MASK                   (0xF0000000U)
#define CDOG_STATUS_CURST_SHIFT                  (28U)
/*! CURST - Current State */
#define CDOG_STATUS_CURST(x)                     (((uint32_t)(((uint32_t)(x)) << CDOG_STATUS_CURST_SHIFT)) & CDOG_STATUS_CURST_MASK)
/*! @} */

/*! @name STATUS2 - STATUS register (2 of 2) */
/*! @{ */

#define CDOG_STATUS2_NUMCNTF_MASK                (0xFFU)
#define CDOG_STATUS2_NUMCNTF_SHIFT               (0U)
/*! NUMCNTF - Number (of) control faults */
#define CDOG_STATUS2_NUMCNTF(x)                  (((uint32_t)(((uint32_t)(x)) << CDOG_STATUS2_NUMCNTF_SHIFT)) & CDOG_STATUS2_NUMCNTF_MASK)

#define CDOG_STATUS2_NUMILLSTF_MASK              (0xFF00U)
#define CDOG_STATUS2_NUMILLSTF_SHIFT             (8U)
/*! NUMILLSTF - Number (of) state faults */
#define CDOG_STATUS2_NUMILLSTF(x)                (((uint32_t)(((uint32_t)(x)) << CDOG_STATUS2_NUMILLSTF_SHIFT)) & CDOG_STATUS2_NUMILLSTF_MASK)

#define CDOG_STATUS2_NUMILLA_MASK                (0xFF0000U)
#define CDOG_STATUS2_NUMILLA_SHIFT               (16U)
/*! NUMILLA - Number of (illegal) address faults */
#define CDOG_STATUS2_NUMILLA(x)                  (((uint32_t)(((uint32_t)(x)) << CDOG_STATUS2_NUMILLA_SHIFT)) & CDOG_STATUS2_NUMILLA_MASK)

#define CDOG_STATUS2_un_imPs_MASK                (0xFF000000U)
#define CDOG_STATUS2_un_imPs_SHIFT               (24U)
/*! un_imPs - Unimplemented bits, such as these here, aren't there. */
#define CDOG_STATUS2_un_imPs(x)                  (((uint32_t)(((uint32_t)(x)) << CDOG_STATUS2_un_imPs_SHIFT)) & CDOG_STATUS2_un_imPs_MASK)
/*! @} */

/*! @name FLAGS - Hardware flags */
/*! @{ */

#define CDOG_FLAGS_TO_FLAG_MASK                  (0x1U)
#define CDOG_FLAGS_TO_FLAG_SHIFT                 (0U)
/*! TO_FLAG - Timeout flag */
#define CDOG_FLAGS_TO_FLAG(x)                    (((uint32_t)(((uint32_t)(x)) << CDOG_FLAGS_TO_FLAG_SHIFT)) & CDOG_FLAGS_TO_FLAG_MASK)

#define CDOG_FLAGS_MISCOM_FLAG_MASK              (0x2U)
#define CDOG_FLAGS_MISCOM_FLAG_SHIFT             (1U)
/*! MISCOM_FLAG - Miscompare flag */
#define CDOG_FLAGS_MISCOM_FLAG(x)                (((uint32_t)(((uint32_t)(x)) << CDOG_FLAGS_MISCOM_FLAG_SHIFT)) & CDOG_FLAGS_MISCOM_FLAG_MASK)

#define CDOG_FLAGS_SEQ_FLAG_MASK                 (0x4U)
#define CDOG_FLAGS_SEQ_FLAG_SHIFT                (2U)
/*! SEQ_FLAG - Sequence flag */
#define CDOG_FLAGS_SEQ_FLAG(x)                   (((uint32_t)(((uint32_t)(x)) << CDOG_FLAGS_SEQ_FLAG_SHIFT)) & CDOG_FLAGS_SEQ_FLAG_MASK)

#define CDOG_FLAGS_CNT_FLAG_MASK                 (0x8U)
#define CDOG_FLAGS_CNT_FLAG_SHIFT                (3U)
/*! CNT_FLAG - Control (fault) flag */
#define CDOG_FLAGS_CNT_FLAG(x)                   (((uint32_t)(((uint32_t)(x)) << CDOG_FLAGS_CNT_FLAG_SHIFT)) & CDOG_FLAGS_CNT_FLAG_MASK)

#define CDOG_FLAGS_STATE_FLAG_MASK               (0x10U)
#define CDOG_FLAGS_STATE_FLAG_SHIFT              (4U)
/*! STATE_FLAG - State flag */
#define CDOG_FLAGS_STATE_FLAG(x)                 (((uint32_t)(((uint32_t)(x)) << CDOG_FLAGS_STATE_FLAG_SHIFT)) & CDOG_FLAGS_STATE_FLAG_MASK)

#define CDOG_FLAGS_ADDR_FLAG_MASK                (0x20U)
#define CDOG_FLAGS_ADDR_FLAG_SHIFT               (5U)
/*! ADDR_FLAG - Address flag */
#define CDOG_FLAGS_ADDR_FLAG(x)                  (((uint32_t)(((uint32_t)(x)) << CDOG_FLAGS_ADDR_FLAG_SHIFT)) & CDOG_FLAGS_ADDR_FLAG_MASK)

#define CDOG_FLAGS_POR_FLAG_MASK                 (0x10000U)
#define CDOG_FLAGS_POR_FLAG_SHIFT                (16U)
/*! POR_FLAG - Power-on reset flag */
#define CDOG_FLAGS_POR_FLAG(x)                   (((uint32_t)(((uint32_t)(x)) << CDOG_FLAGS_POR_FLAG_SHIFT)) & CDOG_FLAGS_POR_FLAG_MASK)
/*! @} */

/*! @name PERSISTENT - Persistent (Ad. Hoc., quasi-NV) data storage */
/*! @{ */

#define CDOG_PERSISTENT_PERSIS_MASK              (0xFFFFFFFFU)
#define CDOG_PERSISTENT_PERSIS_SHIFT             (0U)
/*! PERSIS - 32 regs free for user SW to enjoy */
#define CDOG_PERSISTENT_PERSIS(x)                (((uint32_t)(((uint32_t)(x)) << CDOG_PERSISTENT_PERSIS_SHIFT)) & CDOG_PERSISTENT_PERSIS_MASK)
/*! @} */

/*! @name START - Write address for issuing the START command. */
/*! @{ */

#define CDOG_START_STRT_MASK                     (0xFFFFFFFFU)
#define CDOG_START_STRT_SHIFT                    (0U)
/*! STRT - Address of start command access */
#define CDOG_START_STRT(x)                       (((uint32_t)(((uint32_t)(x)) << CDOG_START_STRT_SHIFT)) & CDOG_START_STRT_MASK)
/*! @} */

/*! @name STOP - Write address for issuing the STOP command. */
/*! @{ */

#define CDOG_STOP_STP_MASK                       (0xFFFFFFFFU)
#define CDOG_STOP_STP_SHIFT                      (0U)
/*! STP - Address of stop command access */
#define CDOG_STOP_STP(x)                         (((uint32_t)(((uint32_t)(x)) << CDOG_STOP_STP_SHIFT)) & CDOG_STOP_STP_MASK)
/*! @} */

/*! @name RESTART - Write address for issuing the RESTART command. */
/*! @{ */

#define CDOG_RESTART_RSTRT_MASK                  (0xFFFFFFFFU)
#define CDOG_RESTART_RSTRT_SHIFT                 (0U)
/*! RSTRT - Write address for issuing the RESTART command. */
#define CDOG_RESTART_RSTRT(x)                    (((uint32_t)(((uint32_t)(x)) << CDOG_RESTART_RSTRT_SHIFT)) & CDOG_RESTART_RSTRT_MASK)
/*! @} */

/*! @name ADD - Write address for issuing the ADD command. */
/*! @{ */

#define CDOG_ADD_AD_MASK                         (0xFFFFFFFFU)
#define CDOG_ADD_AD_SHIFT                        (0U)
/*! AD - Address of ADD command */
#define CDOG_ADD_AD(x)                           (((uint32_t)(((uint32_t)(x)) << CDOG_ADD_AD_SHIFT)) & CDOG_ADD_AD_MASK)
/*! @} */

/*! @name ADD1 - Write address for issuing the ADD1 command. */
/*! @{ */

#define CDOG_ADD1_AD1_MASK                       (0xFFFFFFFFU)
#define CDOG_ADD1_AD1_SHIFT                      (0U)
/*! AD1 - Address of ADD1 command. */
#define CDOG_ADD1_AD1(x)                         (((uint32_t)(((uint32_t)(x)) << CDOG_ADD1_AD1_SHIFT)) & CDOG_ADD1_AD1_MASK)
/*! @} */

/*! @name ADD16 - Write address for issuing the ADD16 command. */
/*! @{ */

#define CDOG_ADD16_AD16_MASK                     (0xFFFFFFFFU)
#define CDOG_ADD16_AD16_SHIFT                    (0U)
/*! AD16 - Address of ADD16 */
#define CDOG_ADD16_AD16(x)                       (((uint32_t)(((uint32_t)(x)) << CDOG_ADD16_AD16_SHIFT)) & CDOG_ADD16_AD16_MASK)
/*! @} */

/*! @name ADD256 - Write address for issuing the ADD16 command. */
/*! @{ */

#define CDOG_ADD256_AD256_MASK                   (0xFFFFFFFFU)
#define CDOG_ADD256_AD256_SHIFT                  (0U)
/*! AD256 - Address of ADD256 command */
#define CDOG_ADD256_AD256(x)                     (((uint32_t)(((uint32_t)(x)) << CDOG_ADD256_AD256_SHIFT)) & CDOG_ADD256_AD256_MASK)
/*! @} */

/*! @name SUB - Write address for issuing the SUB command. */
/*! @{ */

#define CDOG_SUB_S0B_MASK                        (0xFFFFFFFFU)
#define CDOG_SUB_S0B_SHIFT                       (0U)
/*! S0B - Address of SUB command. */
#define CDOG_SUB_S0B(x)                          (((uint32_t)(((uint32_t)(x)) << CDOG_SUB_S0B_SHIFT)) & CDOG_SUB_S0B_MASK)
/*! @} */

/*! @name SUB1 - Write address for issuing the SUB1 command. */
/*! @{ */

#define CDOG_SUB1_S1B_MASK                       (0xFFFFFFFFU)
#define CDOG_SUB1_S1B_SHIFT                      (0U)
/*! S1B - Address of SUB1 command. */
#define CDOG_SUB1_S1B(x)                         (((uint32_t)(((uint32_t)(x)) << CDOG_SUB1_S1B_SHIFT)) & CDOG_SUB1_S1B_MASK)
/*! @} */

/*! @name SUB16 - Write address for issuing the SUB16 command. */
/*! @{ */

#define CDOG_SUB16_SB16_MASK                     (0xFFFFFFFFU)
#define CDOG_SUB16_SB16_SHIFT                    (0U)
/*! SB16 - Address of SUB16 command. */
#define CDOG_SUB16_SB16(x)                       (((uint32_t)(((uint32_t)(x)) << CDOG_SUB16_SB16_SHIFT)) & CDOG_SUB16_SB16_MASK)
/*! @} */

/*! @name SUB256 - Write address for issuing the SUB256 command. */
/*! @{ */

#define CDOG_SUB256_SB256_MASK                   (0xFFFFFFFFU)
#define CDOG_SUB256_SB256_SHIFT                  (0U)
/*! SB256 - Address of (you guessed it) SUB256 command. */
#define CDOG_SUB256_SB256(x)                     (((uint32_t)(((uint32_t)(x)) << CDOG_SUB256_SB256_SHIFT)) & CDOG_SUB256_SB256_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group CDOG_Register_Masks */


/*!
 * @}
 */ /* end of group CDOG_Peripheral_Access_Layer */


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


#endif  /* CDOG_H_ */


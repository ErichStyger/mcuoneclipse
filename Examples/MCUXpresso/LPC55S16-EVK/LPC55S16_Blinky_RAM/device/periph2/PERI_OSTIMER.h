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
**         CMSIS Peripheral Access Layer for OSTIMER
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
 * @file OSTIMER.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for OSTIMER
 *
 * CMSIS Peripheral Access Layer for OSTIMER
 */

#if !defined(OSTIMER_H_)
#define OSTIMER_H_                               /**< Symbol preventing repeated inclusion */

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
   -- OSTIMER Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSTIMER_Peripheral_Access_Layer OSTIMER Peripheral Access Layer
 * @{
 */

/** OSTIMER - Register Layout Typedef */
typedef struct {
  __I  uint32_t EVTIMERL;                          /**< EVTIMER Low Register, offset: 0x0 */
  __I  uint32_t EVTIMERH;                          /**< EVTIMER High Register, offset: 0x4 */
  __I  uint32_t CAPTURE_L;                         /**< Capture Low Register, offset: 0x8 */
  __I  uint32_t CAPTURE_H;                         /**< Capture High Register, offset: 0xC */
  __IO uint32_t MATCH_L;                           /**< Match Low Register, offset: 0x10 */
  __IO uint32_t MATCH_H;                           /**< Match High Register, offset: 0x14 */
       uint8_t RESERVED_0[4];
  __IO uint32_t OSEVENT_CTRL;                      /**< OS_EVENT TIMER Control Register, offset: 0x1C */
} OSTIMER_Type;

/* ----------------------------------------------------------------------------
   -- OSTIMER Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSTIMER_Register_Masks OSTIMER Register Masks
 * @{
 */

/*! @name EVTIMERL - EVTIMER Low Register */
/*! @{ */

#define OSTIMER_EVTIMERL_EVTIMER_COUNT_VALUE_MASK (0xFFFFFFFFU)
#define OSTIMER_EVTIMERL_EVTIMER_COUNT_VALUE_SHIFT (0U)
/*! EVTIMER_COUNT_VALUE - A read reflects the current value of the lower 32 bits of the 42-bits
 *    EVTIMER. Note there is only one EVTIMER, readable from all domains.
 */
#define OSTIMER_EVTIMERL_EVTIMER_COUNT_VALUE(x)  (((uint32_t)(((uint32_t)(x)) << OSTIMER_EVTIMERL_EVTIMER_COUNT_VALUE_SHIFT)) & OSTIMER_EVTIMERL_EVTIMER_COUNT_VALUE_MASK)
/*! @} */

/*! @name EVTIMERH - EVTIMER High Register */
/*! @{ */

#define OSTIMER_EVTIMERH_EVTIMER_COUNT_VALUE_MASK (0x3FFU)
#define OSTIMER_EVTIMERH_EVTIMER_COUNT_VALUE_SHIFT (0U)
/*! EVTIMER_COUNT_VALUE - A read reflects the current value of the upper 10 bits of the 42-bits
 *    EVTIMER. Note there is only one EVTIMER, readable from all domains.
 */
#define OSTIMER_EVTIMERH_EVTIMER_COUNT_VALUE(x)  (((uint32_t)(((uint32_t)(x)) << OSTIMER_EVTIMERH_EVTIMER_COUNT_VALUE_SHIFT)) & OSTIMER_EVTIMERH_EVTIMER_COUNT_VALUE_MASK)
/*! @} */

/*! @name CAPTURE_L - Capture Low Register */
/*! @{ */

#define OSTIMER_CAPTURE_L_CAPTURE_VALUE_MASK     (0xFFFFFFFFU)
#define OSTIMER_CAPTURE_L_CAPTURE_VALUE_SHIFT    (0U)
/*! CAPTURE_VALUE - A read reflects the value of the lower 32 bits of the central 42-bits EVTIMER at
 *    the time the last capture signal was generated by the CPU (using CMSIS C function "__SEV();").
 */
#define OSTIMER_CAPTURE_L_CAPTURE_VALUE(x)       (((uint32_t)(((uint32_t)(x)) << OSTIMER_CAPTURE_L_CAPTURE_VALUE_SHIFT)) & OSTIMER_CAPTURE_L_CAPTURE_VALUE_MASK)
/*! @} */

/*! @name CAPTURE_H - Capture High Register */
/*! @{ */

#define OSTIMER_CAPTURE_H_CAPTURE_VALUE_MASK     (0x3FFU)
#define OSTIMER_CAPTURE_H_CAPTURE_VALUE_SHIFT    (0U)
/*! CAPTURE_VALUE - A read reflects the value of the upper 10 bits of the central 42-bits EVTIMER at
 *    the time the last capture signal was generated by the CPU (using CMSIS C function "__SEV();").
 */
#define OSTIMER_CAPTURE_H_CAPTURE_VALUE(x)       (((uint32_t)(((uint32_t)(x)) << OSTIMER_CAPTURE_H_CAPTURE_VALUE_SHIFT)) & OSTIMER_CAPTURE_H_CAPTURE_VALUE_MASK)
/*! @} */

/*! @name MATCH_L - Match Low Register */
/*! @{ */

#define OSTIMER_MATCH_L_MATCH_VALUE_MASK         (0xFFFFFFFFU)
#define OSTIMER_MATCH_L_MATCH_VALUE_SHIFT        (0U)
/*! MATCH_VALUE - The value written to the MATCH (L/H) register pair is compared against the central
 *    EVTIMER. When a match occurs, an interrupt request is generated if enabled.
 */
#define OSTIMER_MATCH_L_MATCH_VALUE(x)           (((uint32_t)(((uint32_t)(x)) << OSTIMER_MATCH_L_MATCH_VALUE_SHIFT)) & OSTIMER_MATCH_L_MATCH_VALUE_MASK)
/*! @} */

/*! @name MATCH_H - Match High Register */
/*! @{ */

#define OSTIMER_MATCH_H_MATCH_VALUE_MASK         (0x3FFU)
#define OSTIMER_MATCH_H_MATCH_VALUE_SHIFT        (0U)
/*! MATCH_VALUE - The value written (upper 10 bits) to the MATCH (L/H) register pair is compared
 *    against the central EVTIMER. When a match occurs, an interrupt request is generated if enabled.
 */
#define OSTIMER_MATCH_H_MATCH_VALUE(x)           (((uint32_t)(((uint32_t)(x)) << OSTIMER_MATCH_H_MATCH_VALUE_SHIFT)) & OSTIMER_MATCH_H_MATCH_VALUE_MASK)
/*! @} */

/*! @name OSEVENT_CTRL - OS_EVENT TIMER Control Register */
/*! @{ */

#define OSTIMER_OSEVENT_CTRL_OSTIMER_INTRFLAG_MASK (0x1U)
#define OSTIMER_OSEVENT_CTRL_OSTIMER_INTRFLAG_SHIFT (0U)
/*! OSTIMER_INTRFLAG - This bit is set when a match occurs between the central 42-bits EVTIMER and
 *    the value programmed in the match-register pair. This bit is cleared by writing a '1'. Writes
 *    to clear this bit are asynchronous. It should be done before a new match value is written into
 *    the MATCH_L/H registers.
 */
#define OSTIMER_OSEVENT_CTRL_OSTIMER_INTRFLAG(x) (((uint32_t)(((uint32_t)(x)) << OSTIMER_OSEVENT_CTRL_OSTIMER_INTRFLAG_SHIFT)) & OSTIMER_OSEVENT_CTRL_OSTIMER_INTRFLAG_MASK)

#define OSTIMER_OSEVENT_CTRL_OSTIMER_INTENA_MASK (0x2U)
#define OSTIMER_OSEVENT_CTRL_OSTIMER_INTENA_SHIFT (1U)
/*! OSTIMER_INTENA - When this bit is '1' an interrupt/wakeup request to the domain processor will
 *    be asserted when the OSTIMER_INTR flag is set. When this bit is '0', interrupt/wakeup requests
 *    due to the OSTIMER_INTR flag are blocked.
 */
#define OSTIMER_OSEVENT_CTRL_OSTIMER_INTENA(x)   (((uint32_t)(((uint32_t)(x)) << OSTIMER_OSEVENT_CTRL_OSTIMER_INTENA_SHIFT)) & OSTIMER_OSEVENT_CTRL_OSTIMER_INTENA_MASK)

#define OSTIMER_OSEVENT_CTRL_MATCH_WR_RDY_MASK   (0x4U)
#define OSTIMER_OSEVENT_CTRL_MATCH_WR_RDY_SHIFT  (2U)
/*! MATCH_WR_RDY - This bit will be low when it is safe to write to reload the Match Registers. In
 *    typical applications it should not be necessary to test this bit. [1]
 */
#define OSTIMER_OSEVENT_CTRL_MATCH_WR_RDY(x)     (((uint32_t)(((uint32_t)(x)) << OSTIMER_OSEVENT_CTRL_MATCH_WR_RDY_SHIFT)) & OSTIMER_OSEVENT_CTRL_MATCH_WR_RDY_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group OSTIMER_Register_Masks */


/*!
 * @}
 */ /* end of group OSTIMER_Peripheral_Access_Layer */


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


#endif  /* OSTIMER_H_ */


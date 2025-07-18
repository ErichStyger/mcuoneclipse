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
**         CMSIS Peripheral Access Layer for FLASH
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
 * @file FLASH.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for FLASH
 *
 * CMSIS Peripheral Access Layer for FLASH
 */

#if !defined(FLASH_H_)
#define FLASH_H_                                 /**< Symbol preventing repeated inclusion */

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
   -- FLASH Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLASH_Peripheral_Access_Layer FLASH Peripheral Access Layer
 * @{
 */

/** FLASH - Size of Registers Arrays */
#define FLASH_DATAW_COUNT                         4u

/** FLASH - Register Layout Typedef */
typedef struct {
  __O  uint32_t CMD;                               /**< command register, offset: 0x0 */
  __O  uint32_t EVENT;                             /**< event register, offset: 0x4 */
       uint8_t RESERVED_0[8];
  __IO uint32_t STARTA;                            /**< start (or only) address for next flash command, offset: 0x10 */
  __IO uint32_t STOPA;                             /**< end address for next flash command, if command operates on address ranges, offset: 0x14 */
       uint8_t RESERVED_1[104];
  __IO uint32_t DATAW[FLASH_DATAW_COUNT];          /**< data register, word 0-7; Memory data, or command parameter, or command result., array offset: 0x80, array step: 0x4 */
       uint8_t RESERVED_2[3912];
  __O  uint32_t INT_CLR_ENABLE;                    /**< Clear interrupt enable bits, offset: 0xFD8 */
  __O  uint32_t INT_SET_ENABLE;                    /**< Set interrupt enable bits, offset: 0xFDC */
  __I  uint32_t INT_STATUS;                        /**< Interrupt status bits, offset: 0xFE0 */
  __I  uint32_t INT_ENABLE;                        /**< Interrupt enable bits, offset: 0xFE4 */
  __O  uint32_t INT_CLR_STATUS;                    /**< Clear interrupt status bits, offset: 0xFE8 */
  __O  uint32_t INT_SET_STATUS;                    /**< Set interrupt status bits, offset: 0xFEC */
       uint8_t RESERVED_3[12];
  __I  uint32_t MODULE_ID;                         /**< Controller+Memory module identification, offset: 0xFFC */
} FLASH_Type;

/* ----------------------------------------------------------------------------
   -- FLASH Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLASH_Register_Masks FLASH Register Masks
 * @{
 */

/*! @name CMD - command register */
/*! @{ */

#define FLASH_CMD_CMD_MASK                       (0xFFFFFFFFU)
#define FLASH_CMD_CMD_SHIFT                      (0U)
/*! CMD - command register. */
#define FLASH_CMD_CMD(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_CMD_CMD_SHIFT)) & FLASH_CMD_CMD_MASK)
/*! @} */

/*! @name EVENT - event register */
/*! @{ */

#define FLASH_EVENT_RST_MASK                     (0x1U)
#define FLASH_EVENT_RST_SHIFT                    (0U)
/*! RST - When bit is set, the controller and flash are reset. */
#define FLASH_EVENT_RST(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_EVENT_RST_SHIFT)) & FLASH_EVENT_RST_MASK)

#define FLASH_EVENT_WAKEUP_MASK                  (0x2U)
#define FLASH_EVENT_WAKEUP_SHIFT                 (1U)
/*! WAKEUP - When bit is set, the controller wakes up from whatever low power or powerdown mode was active. */
#define FLASH_EVENT_WAKEUP(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_EVENT_WAKEUP_SHIFT)) & FLASH_EVENT_WAKEUP_MASK)

#define FLASH_EVENT_ABORT_MASK                   (0x4U)
#define FLASH_EVENT_ABORT_SHIFT                  (2U)
/*! ABORT - When bit is set, a running program/erase command is aborted. */
#define FLASH_EVENT_ABORT(x)                     (((uint32_t)(((uint32_t)(x)) << FLASH_EVENT_ABORT_SHIFT)) & FLASH_EVENT_ABORT_MASK)
/*! @} */

/*! @name STARTA - start (or only) address for next flash command */
/*! @{ */

#define FLASH_STARTA_STARTA_MASK                 (0x3FFFFU)
#define FLASH_STARTA_STARTA_SHIFT                (0U)
/*! STARTA - Address / Start address for commands that take an address (range) as a parameter. */
#define FLASH_STARTA_STARTA(x)                   (((uint32_t)(((uint32_t)(x)) << FLASH_STARTA_STARTA_SHIFT)) & FLASH_STARTA_STARTA_MASK)
/*! @} */

/*! @name STOPA - end address for next flash command, if command operates on address ranges */
/*! @{ */

#define FLASH_STOPA_STOPA_MASK                   (0x3FFFFU)
#define FLASH_STOPA_STOPA_SHIFT                  (0U)
/*! STOPA - Stop address for commands that take an address range as a parameter (the word specified
 *    by STOPA is included in the address range).
 */
#define FLASH_STOPA_STOPA(x)                     (((uint32_t)(((uint32_t)(x)) << FLASH_STOPA_STOPA_SHIFT)) & FLASH_STOPA_STOPA_MASK)
/*! @} */

/*! @name DATAW - data register, word 0-7; Memory data, or command parameter, or command result. */
/*! @{ */

#define FLASH_DATAW_DATAW_MASK                   (0xFFFFFFFFU)
#define FLASH_DATAW_DATAW_SHIFT                  (0U)
#define FLASH_DATAW_DATAW(x)                     (((uint32_t)(((uint32_t)(x)) << FLASH_DATAW_DATAW_SHIFT)) & FLASH_DATAW_DATAW_MASK)
/*! @} */

/*! @name INT_CLR_ENABLE - Clear interrupt enable bits */
/*! @{ */

#define FLASH_INT_CLR_ENABLE_FAIL_MASK           (0x1U)
#define FLASH_INT_CLR_ENABLE_FAIL_SHIFT          (0U)
/*! FAIL - When a CLR_ENABLE bit is written to 1, the corresponding INT_ENABLE bit is cleared. */
#define FLASH_INT_CLR_ENABLE_FAIL(x)             (((uint32_t)(((uint32_t)(x)) << FLASH_INT_CLR_ENABLE_FAIL_SHIFT)) & FLASH_INT_CLR_ENABLE_FAIL_MASK)

#define FLASH_INT_CLR_ENABLE_ERR_MASK            (0x2U)
#define FLASH_INT_CLR_ENABLE_ERR_SHIFT           (1U)
/*! ERR - When a CLR_ENABLE bit is written to 1, the corresponding INT_ENABLE bit is cleared. */
#define FLASH_INT_CLR_ENABLE_ERR(x)              (((uint32_t)(((uint32_t)(x)) << FLASH_INT_CLR_ENABLE_ERR_SHIFT)) & FLASH_INT_CLR_ENABLE_ERR_MASK)

#define FLASH_INT_CLR_ENABLE_DONE_MASK           (0x4U)
#define FLASH_INT_CLR_ENABLE_DONE_SHIFT          (2U)
/*! DONE - When a CLR_ENABLE bit is written to 1, the corresponding INT_ENABLE bit is cleared. */
#define FLASH_INT_CLR_ENABLE_DONE(x)             (((uint32_t)(((uint32_t)(x)) << FLASH_INT_CLR_ENABLE_DONE_SHIFT)) & FLASH_INT_CLR_ENABLE_DONE_MASK)

#define FLASH_INT_CLR_ENABLE_ECC_ERR_MASK        (0x8U)
#define FLASH_INT_CLR_ENABLE_ECC_ERR_SHIFT       (3U)
/*! ECC_ERR - When a CLR_ENABLE bit is written to 1, the corresponding INT_ENABLE bit is cleared. */
#define FLASH_INT_CLR_ENABLE_ECC_ERR(x)          (((uint32_t)(((uint32_t)(x)) << FLASH_INT_CLR_ENABLE_ECC_ERR_SHIFT)) & FLASH_INT_CLR_ENABLE_ECC_ERR_MASK)
/*! @} */

/*! @name INT_SET_ENABLE - Set interrupt enable bits */
/*! @{ */

#define FLASH_INT_SET_ENABLE_FAIL_MASK           (0x1U)
#define FLASH_INT_SET_ENABLE_FAIL_SHIFT          (0U)
/*! FAIL - When a SET_ENABLE bit is written to 1, the corresponding INT_ENABLE bit is set. */
#define FLASH_INT_SET_ENABLE_FAIL(x)             (((uint32_t)(((uint32_t)(x)) << FLASH_INT_SET_ENABLE_FAIL_SHIFT)) & FLASH_INT_SET_ENABLE_FAIL_MASK)

#define FLASH_INT_SET_ENABLE_ERR_MASK            (0x2U)
#define FLASH_INT_SET_ENABLE_ERR_SHIFT           (1U)
/*! ERR - When a SET_ENABLE bit is written to 1, the corresponding INT_ENABLE bit is set. */
#define FLASH_INT_SET_ENABLE_ERR(x)              (((uint32_t)(((uint32_t)(x)) << FLASH_INT_SET_ENABLE_ERR_SHIFT)) & FLASH_INT_SET_ENABLE_ERR_MASK)

#define FLASH_INT_SET_ENABLE_DONE_MASK           (0x4U)
#define FLASH_INT_SET_ENABLE_DONE_SHIFT          (2U)
/*! DONE - When a SET_ENABLE bit is written to 1, the corresponding INT_ENABLE bit is set. */
#define FLASH_INT_SET_ENABLE_DONE(x)             (((uint32_t)(((uint32_t)(x)) << FLASH_INT_SET_ENABLE_DONE_SHIFT)) & FLASH_INT_SET_ENABLE_DONE_MASK)

#define FLASH_INT_SET_ENABLE_ECC_ERR_MASK        (0x8U)
#define FLASH_INT_SET_ENABLE_ECC_ERR_SHIFT       (3U)
/*! ECC_ERR - When a SET_ENABLE bit is written to 1, the corresponding INT_ENABLE bit is set. */
#define FLASH_INT_SET_ENABLE_ECC_ERR(x)          (((uint32_t)(((uint32_t)(x)) << FLASH_INT_SET_ENABLE_ECC_ERR_SHIFT)) & FLASH_INT_SET_ENABLE_ECC_ERR_MASK)
/*! @} */

/*! @name INT_STATUS - Interrupt status bits */
/*! @{ */

#define FLASH_INT_STATUS_FAIL_MASK               (0x1U)
#define FLASH_INT_STATUS_FAIL_SHIFT              (0U)
/*! FAIL - This status bit is set if execution of a (legal) command failed. */
#define FLASH_INT_STATUS_FAIL(x)                 (((uint32_t)(((uint32_t)(x)) << FLASH_INT_STATUS_FAIL_SHIFT)) & FLASH_INT_STATUS_FAIL_MASK)

#define FLASH_INT_STATUS_ERR_MASK                (0x2U)
#define FLASH_INT_STATUS_ERR_SHIFT               (1U)
/*! ERR - This status bit is set if execution of an illegal command is detected. */
#define FLASH_INT_STATUS_ERR(x)                  (((uint32_t)(((uint32_t)(x)) << FLASH_INT_STATUS_ERR_SHIFT)) & FLASH_INT_STATUS_ERR_MASK)

#define FLASH_INT_STATUS_DONE_MASK               (0x4U)
#define FLASH_INT_STATUS_DONE_SHIFT              (2U)
/*! DONE - This status bit is set at the end of command execution. */
#define FLASH_INT_STATUS_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << FLASH_INT_STATUS_DONE_SHIFT)) & FLASH_INT_STATUS_DONE_MASK)

#define FLASH_INT_STATUS_ECC_ERR_MASK            (0x8U)
#define FLASH_INT_STATUS_ECC_ERR_SHIFT           (3U)
/*! ECC_ERR - This status bit is set if, during a memory read operation (either a user-requested
 *    read, or a speculative read, or reads performed by a controller command), a correctable or
 *    uncorrectable error is detected by ECC decoding logic.
 */
#define FLASH_INT_STATUS_ECC_ERR(x)              (((uint32_t)(((uint32_t)(x)) << FLASH_INT_STATUS_ECC_ERR_SHIFT)) & FLASH_INT_STATUS_ECC_ERR_MASK)
/*! @} */

/*! @name INT_ENABLE - Interrupt enable bits */
/*! @{ */

#define FLASH_INT_ENABLE_FAIL_MASK               (0x1U)
#define FLASH_INT_ENABLE_FAIL_SHIFT              (0U)
/*! FAIL - If an INT_ENABLE bit is set, an interrupt request will be generated if the corresponding INT_STATUS bit is high. */
#define FLASH_INT_ENABLE_FAIL(x)                 (((uint32_t)(((uint32_t)(x)) << FLASH_INT_ENABLE_FAIL_SHIFT)) & FLASH_INT_ENABLE_FAIL_MASK)

#define FLASH_INT_ENABLE_ERR_MASK                (0x2U)
#define FLASH_INT_ENABLE_ERR_SHIFT               (1U)
/*! ERR - If an INT_ENABLE bit is set, an interrupt request will be generated if the corresponding INT_STATUS bit is high. */
#define FLASH_INT_ENABLE_ERR(x)                  (((uint32_t)(((uint32_t)(x)) << FLASH_INT_ENABLE_ERR_SHIFT)) & FLASH_INT_ENABLE_ERR_MASK)

#define FLASH_INT_ENABLE_DONE_MASK               (0x4U)
#define FLASH_INT_ENABLE_DONE_SHIFT              (2U)
/*! DONE - If an INT_ENABLE bit is set, an interrupt request will be generated if the corresponding INT_STATUS bit is high. */
#define FLASH_INT_ENABLE_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << FLASH_INT_ENABLE_DONE_SHIFT)) & FLASH_INT_ENABLE_DONE_MASK)

#define FLASH_INT_ENABLE_ECC_ERR_MASK            (0x8U)
#define FLASH_INT_ENABLE_ECC_ERR_SHIFT           (3U)
/*! ECC_ERR - If an INT_ENABLE bit is set, an interrupt request will be generated if the corresponding INT_STATUS bit is high. */
#define FLASH_INT_ENABLE_ECC_ERR(x)              (((uint32_t)(((uint32_t)(x)) << FLASH_INT_ENABLE_ECC_ERR_SHIFT)) & FLASH_INT_ENABLE_ECC_ERR_MASK)
/*! @} */

/*! @name INT_CLR_STATUS - Clear interrupt status bits */
/*! @{ */

#define FLASH_INT_CLR_STATUS_FAIL_MASK           (0x1U)
#define FLASH_INT_CLR_STATUS_FAIL_SHIFT          (0U)
/*! FAIL - When a CLR_STATUS bit is written to 1, the corresponding INT_STATUS bit is cleared. */
#define FLASH_INT_CLR_STATUS_FAIL(x)             (((uint32_t)(((uint32_t)(x)) << FLASH_INT_CLR_STATUS_FAIL_SHIFT)) & FLASH_INT_CLR_STATUS_FAIL_MASK)

#define FLASH_INT_CLR_STATUS_ERR_MASK            (0x2U)
#define FLASH_INT_CLR_STATUS_ERR_SHIFT           (1U)
/*! ERR - When a CLR_STATUS bit is written to 1, the corresponding INT_STATUS bit is cleared. */
#define FLASH_INT_CLR_STATUS_ERR(x)              (((uint32_t)(((uint32_t)(x)) << FLASH_INT_CLR_STATUS_ERR_SHIFT)) & FLASH_INT_CLR_STATUS_ERR_MASK)

#define FLASH_INT_CLR_STATUS_DONE_MASK           (0x4U)
#define FLASH_INT_CLR_STATUS_DONE_SHIFT          (2U)
/*! DONE - When a CLR_STATUS bit is written to 1, the corresponding INT_STATUS bit is cleared. */
#define FLASH_INT_CLR_STATUS_DONE(x)             (((uint32_t)(((uint32_t)(x)) << FLASH_INT_CLR_STATUS_DONE_SHIFT)) & FLASH_INT_CLR_STATUS_DONE_MASK)

#define FLASH_INT_CLR_STATUS_ECC_ERR_MASK        (0x8U)
#define FLASH_INT_CLR_STATUS_ECC_ERR_SHIFT       (3U)
/*! ECC_ERR - When a CLR_STATUS bit is written to 1, the corresponding INT_STATUS bit is cleared. */
#define FLASH_INT_CLR_STATUS_ECC_ERR(x)          (((uint32_t)(((uint32_t)(x)) << FLASH_INT_CLR_STATUS_ECC_ERR_SHIFT)) & FLASH_INT_CLR_STATUS_ECC_ERR_MASK)
/*! @} */

/*! @name INT_SET_STATUS - Set interrupt status bits */
/*! @{ */

#define FLASH_INT_SET_STATUS_FAIL_MASK           (0x1U)
#define FLASH_INT_SET_STATUS_FAIL_SHIFT          (0U)
/*! FAIL - When a SET_STATUS bit is written to 1, the corresponding INT_STATUS bit is set. */
#define FLASH_INT_SET_STATUS_FAIL(x)             (((uint32_t)(((uint32_t)(x)) << FLASH_INT_SET_STATUS_FAIL_SHIFT)) & FLASH_INT_SET_STATUS_FAIL_MASK)

#define FLASH_INT_SET_STATUS_ERR_MASK            (0x2U)
#define FLASH_INT_SET_STATUS_ERR_SHIFT           (1U)
/*! ERR - When a SET_STATUS bit is written to 1, the corresponding INT_STATUS bit is set. */
#define FLASH_INT_SET_STATUS_ERR(x)              (((uint32_t)(((uint32_t)(x)) << FLASH_INT_SET_STATUS_ERR_SHIFT)) & FLASH_INT_SET_STATUS_ERR_MASK)

#define FLASH_INT_SET_STATUS_DONE_MASK           (0x4U)
#define FLASH_INT_SET_STATUS_DONE_SHIFT          (2U)
/*! DONE - When a SET_STATUS bit is written to 1, the corresponding INT_STATUS bit is set. */
#define FLASH_INT_SET_STATUS_DONE(x)             (((uint32_t)(((uint32_t)(x)) << FLASH_INT_SET_STATUS_DONE_SHIFT)) & FLASH_INT_SET_STATUS_DONE_MASK)

#define FLASH_INT_SET_STATUS_ECC_ERR_MASK        (0x8U)
#define FLASH_INT_SET_STATUS_ECC_ERR_SHIFT       (3U)
/*! ECC_ERR - When a SET_STATUS bit is written to 1, the corresponding INT_STATUS bit is set. */
#define FLASH_INT_SET_STATUS_ECC_ERR(x)          (((uint32_t)(((uint32_t)(x)) << FLASH_INT_SET_STATUS_ECC_ERR_SHIFT)) & FLASH_INT_SET_STATUS_ECC_ERR_MASK)
/*! @} */

/*! @name MODULE_ID - Controller+Memory module identification */
/*! @{ */

#define FLASH_MODULE_ID_APERTURE_MASK            (0xFFU)
#define FLASH_MODULE_ID_APERTURE_SHIFT           (0U)
/*! APERTURE - Aperture i. */
#define FLASH_MODULE_ID_APERTURE(x)              (((uint32_t)(((uint32_t)(x)) << FLASH_MODULE_ID_APERTURE_SHIFT)) & FLASH_MODULE_ID_APERTURE_MASK)

#define FLASH_MODULE_ID_MINOR_REV_MASK           (0xF00U)
#define FLASH_MODULE_ID_MINOR_REV_SHIFT          (8U)
/*! MINOR_REV - Minor revision i. */
#define FLASH_MODULE_ID_MINOR_REV(x)             (((uint32_t)(((uint32_t)(x)) << FLASH_MODULE_ID_MINOR_REV_SHIFT)) & FLASH_MODULE_ID_MINOR_REV_MASK)

#define FLASH_MODULE_ID_MAJOR_REV_MASK           (0xF000U)
#define FLASH_MODULE_ID_MAJOR_REV_SHIFT          (12U)
/*! MAJOR_REV - Major revision i. */
#define FLASH_MODULE_ID_MAJOR_REV(x)             (((uint32_t)(((uint32_t)(x)) << FLASH_MODULE_ID_MAJOR_REV_SHIFT)) & FLASH_MODULE_ID_MAJOR_REV_MASK)

#define FLASH_MODULE_ID_ID_MASK                  (0xFFFF0000U)
#define FLASH_MODULE_ID_ID_SHIFT                 (16U)
/*! ID - Identifier. */
#define FLASH_MODULE_ID_ID(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_MODULE_ID_ID_SHIFT)) & FLASH_MODULE_ID_ID_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group FLASH_Register_Masks */


/*!
 * @}
 */ /* end of group FLASH_Peripheral_Access_Layer */


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


#endif  /* FLASH_H_ */


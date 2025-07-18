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
**         CMSIS Peripheral Access Layer for FLASH_ROMPATCH
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
 * @file FLASH_ROMPATCH.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for FLASH_ROMPATCH
 *
 * CMSIS Peripheral Access Layer for FLASH_ROMPATCH
 */

#if !defined(FLASH_ROMPATCH_H_)
#define FLASH_ROMPATCH_H_                        /**< Symbol preventing repeated inclusion */

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
   -- FLASH_ROMPATCH Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLASH_ROMPATCH_Peripheral_Access_Layer FLASH_ROMPATCH Peripheral Access Layer
 * @{
 */

/** FLASH_ROMPATCH - Size of Registers Arrays */
#define FLASH_ROMPATCH_PATCH_COUNT                255u

/** FLASH_ROMPATCH - Register Layout Typedef */
typedef struct {
  __IO uint32_t HEADER;                            /**< ., offset: 0x0 */
  __IO uint32_t PATCH[FLASH_ROMPATCH_PATCH_COUNT]; /**< ., array offset: 0x4, array step: 0x4 */
} FLASH_ROMPATCH_Type;

/* ----------------------------------------------------------------------------
   -- FLASH_ROMPATCH Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLASH_ROMPATCH_Register_Masks FLASH_ROMPATCH Register Masks
 * @{
 */

/*! @name HEADER - . */
/*! @{ */

#define FLASH_ROMPATCH_HEADER_ENTRIES_MASK       (0xFFU)
#define FLASH_ROMPATCH_HEADER_ENTRIES_SHIFT      (0U)
/*! ENTRIES - . */
#define FLASH_ROMPATCH_HEADER_ENTRIES(x)         (((uint32_t)(((uint32_t)(x)) << FLASH_ROMPATCH_HEADER_ENTRIES_SHIFT)) & FLASH_ROMPATCH_HEADER_ENTRIES_MASK)

#define FLASH_ROMPATCH_HEADER_SUB_TYPE_MASK      (0xFF00U)
#define FLASH_ROMPATCH_HEADER_SUB_TYPE_SHIFT     (8U)
/*! SUB_TYPE - . */
#define FLASH_ROMPATCH_HEADER_SUB_TYPE(x)        (((uint32_t)(((uint32_t)(x)) << FLASH_ROMPATCH_HEADER_SUB_TYPE_SHIFT)) & FLASH_ROMPATCH_HEADER_SUB_TYPE_MASK)

#define FLASH_ROMPATCH_HEADER_TYPE_MASK          (0xFF0000U)
#define FLASH_ROMPATCH_HEADER_TYPE_SHIFT         (16U)
/*! TYPE - . */
#define FLASH_ROMPATCH_HEADER_TYPE(x)            (((uint32_t)(((uint32_t)(x)) << FLASH_ROMPATCH_HEADER_TYPE_SHIFT)) & FLASH_ROMPATCH_HEADER_TYPE_MASK)

#define FLASH_ROMPATCH_HEADER_IDENTIFIER_MASK    (0xFF000000U)
#define FLASH_ROMPATCH_HEADER_IDENTIFIER_SHIFT   (24U)
/*! IDENTIFIER - . */
#define FLASH_ROMPATCH_HEADER_IDENTIFIER(x)      (((uint32_t)(((uint32_t)(x)) << FLASH_ROMPATCH_HEADER_IDENTIFIER_SHIFT)) & FLASH_ROMPATCH_HEADER_IDENTIFIER_MASK)
/*! @} */

/*! @name PATCH - . */
/*! @{ */

#define FLASH_ROMPATCH_PATCH_PATCH_MASK          (0xFFFFFFFFU)
#define FLASH_ROMPATCH_PATCH_PATCH_SHIFT         (0U)
/*! PATCH - . */
#define FLASH_ROMPATCH_PATCH_PATCH(x)            (((uint32_t)(((uint32_t)(x)) << FLASH_ROMPATCH_PATCH_PATCH_SHIFT)) & FLASH_ROMPATCH_PATCH_PATCH_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group FLASH_ROMPATCH_Register_Masks */


/*!
 * @}
 */ /* end of group FLASH_ROMPATCH_Peripheral_Access_Layer */


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


#endif  /* FLASH_ROMPATCH_H_ */


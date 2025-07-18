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
**         CMSIS Peripheral Access Layer for FLASH_CFPA
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
 * @file FLASH_CFPA.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for FLASH_CFPA
 *
 * CMSIS Peripheral Access Layer for FLASH_CFPA
 */

#if !defined(FLASH_CFPA_H_)
#define FLASH_CFPA_H_                            /**< Symbol preventing repeated inclusion */

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
   -- FLASH_CFPA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLASH_CFPA_Peripheral_Access_Layer FLASH_CFPA Peripheral Access Layer
 * @{
 */

/** FLASH_CFPA - Size of Registers Arrays */
#define FLASH_CFPA_PRINCE_REGION0_IV_CODE_PRINCE_REGION0_IV_CODE_PRINCE_REGION0_IV_CODE_COUNT 14u
#define FLASH_CFPA_PRINCE_REGION0_IV_CODE_PRINCE_REGION0_IV_CODE_CORE_PRINCE_REGION0_IV_BODY_COUNT 12u
#define FLASH_CFPA_PRINCE_REGION1_IV_CODE_PRINCE_REGION1_IV_CODE_PRINCE_REGION1_IV_CODE_COUNT 14u
#define FLASH_CFPA_PRINCE_REGION1_IV_CODE_PRINCE_REGION1_IV_CODE_CORE_PRINCE_REGION1_IV_BODY_COUNT 12u
#define FLASH_CFPA_PRINCE_REGION2_IV_CODE_PRINCE_REGION2_IV_CODE_PRINCE_REGION2_IV_CODE_COUNT 14u
#define FLASH_CFPA_PRINCE_REGION2_IV_CODE_PRINCE_REGION2_IV_CODE_CORE_PRINCE_REGION2_IV_BODY_COUNT 12u
#define FLASH_CFPA_CUSTOMER_DEFINED_COUNT         56u
#define FLASH_CFPA_SHA256_DIGEST_COUNT            8u

/** FLASH_CFPA - Register Layout Typedef */
typedef struct {
  __IO uint32_t HEADER;                            /**< offset: 0x0 */
  __IO uint32_t VERSION;                           /**< offset: 0x4 */
  __IO uint32_t S_FW_VERSION;                      /**< Secure firmware version (Monotonic counter), offset: 0x8 */
  __IO uint32_t NS_FW_VERSION;                     /**< Non-Secure firmware version (Monotonic counter), offset: 0xC */
  __IO uint32_t IMAGE_KEY_REVOKE;                  /**< Image key revocation ID (Monotonic counter), offset: 0x10 */
       uint8_t RESERVED_0[4];
  __IO uint32_t ROTKH_REVOKE;                      /**< offset: 0x18 */
  __IO uint32_t VENDOR_USAGE;                      /**< offset: 0x1C */
  __IO uint32_t DCFG_CC_SOCU_PIN;                  /**< With TZ-M, the part can be sold by level 1 customers (secure code developer) to level-2 customers who develops non-secure code only. - In this scenario, or easy of development, Level-I customer releases the part to always allow non-secure debug. - To allow level-2 customers to further seal the part DCFG_CC_SOCU_NS is used. - ROM will use this word to further restrict the debug access., offset: 0x20 */
  __IO uint32_t DCFG_CC_SOCU_DFLT;                 /**< With TZ-M, the part can be sold by level 1 customers (secure code developer) to level-2 customers who develops non-secure code only. - In this scenario, or easy of development, Level-I customer releases the part to always allow non-secure debug. - To allow level-2 customers to further seal the part DCFG_CC_SOCU_NS is used. - ROM will use this word to further restrict the debug access., offset: 0x24 */
  __IO uint32_t ENABLE_FA_MODE;                    /**< Enable FA mode. SET_FA_MODE Command should write 0xC33CA55A to this word to indicate boot ROM to enter FA mode., offset: 0x28 */
  __IO uint32_t CMPA_PROG_IN_PROGRESS;             /**< CMPA Page programming on going. This field shall be set to 0x5CC55AA5 in the active CFPA page each time CMPA page programming is going on. It shall always be set to 0x00000000 in the CFPA scratch area., offset: 0x2C */
  union {                                          /* offset: 0x30 */
    __IO uint32_t PRINCE_REGION0_IV_CODE[FLASH_CFPA_PRINCE_REGION0_IV_CODE_PRINCE_REGION0_IV_CODE_PRINCE_REGION0_IV_CODE_COUNT];   /**< array offset: 0x30, array step: 0x4 */
    struct {                                         /* offset: 0x30 */
      __IO uint32_t PRINCE_REGION0_IV_HEADER0;         /**< offset: 0x30 */
      __IO uint32_t PRINCE_REGION0_IV_HEADER1;         /**< offset: 0x34 */
      __IO uint32_t PRINCE_REGION0_IV_BODY[FLASH_CFPA_PRINCE_REGION0_IV_CODE_PRINCE_REGION0_IV_CODE_CORE_PRINCE_REGION0_IV_BODY_COUNT];     /**< array offset: 0x38, array step: 0x4 */
    } PRINCE_REGION0_IV_CODE_CORE;
  };
  union {                                          /* offset: 0x68 */
    __IO uint32_t PRINCE_REGION1_IV_CODE[FLASH_CFPA_PRINCE_REGION1_IV_CODE_PRINCE_REGION1_IV_CODE_PRINCE_REGION1_IV_CODE_COUNT];   /**< array offset: 0x68, array step: 0x4 */
    struct {                                         /* offset: 0x68 */
      __IO uint32_t PRINCE_REGION1_IV_HEADER0;         /**< offset: 0x68 */
      __IO uint32_t PRINCE_REGION1_IV_HEADER1;         /**< offset: 0x6C */
      __IO uint32_t PRINCE_REGION1_IV_BODY[FLASH_CFPA_PRINCE_REGION1_IV_CODE_PRINCE_REGION1_IV_CODE_CORE_PRINCE_REGION1_IV_BODY_COUNT];     /**< array offset: 0x70, array step: 0x4 */
    } PRINCE_REGION1_IV_CODE_CORE;
  };
  union {                                          /* offset: 0xA0 */
    __IO uint32_t PRINCE_REGION2_IV_CODE[FLASH_CFPA_PRINCE_REGION2_IV_CODE_PRINCE_REGION2_IV_CODE_PRINCE_REGION2_IV_CODE_COUNT];   /**< array offset: 0xA0, array step: 0x4 */
    struct {                                         /* offset: 0xA0 */
      __IO uint32_t PRINCE_REGION2_IV_HEADER0;         /**< offset: 0xA0 */
      __IO uint32_t PRINCE_REGION2_IV_HEADER1;         /**< offset: 0xA4 */
      __IO uint32_t PRINCE_REGION2_IV_BODY[FLASH_CFPA_PRINCE_REGION2_IV_CODE_PRINCE_REGION2_IV_CODE_CORE_PRINCE_REGION2_IV_BODY_COUNT];     /**< array offset: 0xA8, array step: 0x4 */
    } PRINCE_REGION2_IV_CODE_CORE;
  };
       uint8_t RESERVED_1[40];
  __IO uint32_t CUSTOMER_DEFINED[FLASH_CFPA_CUSTOMER_DEFINED_COUNT]; /**< Customer Defined (Programable through ROM API), array offset: 0x100, array step: 0x4 */
  __IO uint32_t SHA256_DIGEST[FLASH_CFPA_SHA256_DIGEST_COUNT]; /**< SHA256_DIGEST0 for DIGEST[31:0]..SHA256_DIGEST7 for DIGEST[255:224], array offset: 0x1E0, array step: 0x4 */
} FLASH_CFPA_Type;

/* ----------------------------------------------------------------------------
   -- FLASH_CFPA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLASH_CFPA_Register_Masks FLASH_CFPA Register Masks
 * @{
 */

/*! @name HEADER -  */
/*! @{ */

#define FLASH_CFPA_HEADER_FIELD_MASK             (0xFFFFFFFFU)
#define FLASH_CFPA_HEADER_FIELD_SHIFT            (0U)
#define FLASH_CFPA_HEADER_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_HEADER_FIELD_SHIFT)) & FLASH_CFPA_HEADER_FIELD_MASK)
/*! @} */

/*! @name VERSION -  */
/*! @{ */

#define FLASH_CFPA_VERSION_FIELD_MASK            (0xFFFFFFFFU)
#define FLASH_CFPA_VERSION_FIELD_SHIFT           (0U)
#define FLASH_CFPA_VERSION_FIELD(x)              (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_VERSION_FIELD_SHIFT)) & FLASH_CFPA_VERSION_FIELD_MASK)
/*! @} */

/*! @name S_FW_VERSION - Secure firmware version (Monotonic counter) */
/*! @{ */

#define FLASH_CFPA_S_FW_VERSION_FIELD_MASK       (0xFFFFFFFFU)
#define FLASH_CFPA_S_FW_VERSION_FIELD_SHIFT      (0U)
#define FLASH_CFPA_S_FW_VERSION_FIELD(x)         (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_S_FW_VERSION_FIELD_SHIFT)) & FLASH_CFPA_S_FW_VERSION_FIELD_MASK)
/*! @} */

/*! @name NS_FW_VERSION - Non-Secure firmware version (Monotonic counter) */
/*! @{ */

#define FLASH_CFPA_NS_FW_VERSION_FIELD_MASK      (0xFFFFFFFFU)
#define FLASH_CFPA_NS_FW_VERSION_FIELD_SHIFT     (0U)
#define FLASH_CFPA_NS_FW_VERSION_FIELD(x)        (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_NS_FW_VERSION_FIELD_SHIFT)) & FLASH_CFPA_NS_FW_VERSION_FIELD_MASK)
/*! @} */

/*! @name IMAGE_KEY_REVOKE - Image key revocation ID (Monotonic counter) */
/*! @{ */

#define FLASH_CFPA_IMAGE_KEY_REVOKE_FIELD_MASK   (0xFFFFFFFFU)
#define FLASH_CFPA_IMAGE_KEY_REVOKE_FIELD_SHIFT  (0U)
#define FLASH_CFPA_IMAGE_KEY_REVOKE_FIELD(x)     (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_IMAGE_KEY_REVOKE_FIELD_SHIFT)) & FLASH_CFPA_IMAGE_KEY_REVOKE_FIELD_MASK)
/*! @} */

/*! @name ROTKH_REVOKE -  */
/*! @{ */

#define FLASH_CFPA_ROTKH_REVOKE_RoTK0_EN_MASK    (0x3U)
#define FLASH_CFPA_ROTKH_REVOKE_RoTK0_EN_SHIFT   (0U)
/*! RoTK0_EN - RoT Key 0 enable. 00 - Invalid 01 - Enabled 10, 11 - Key revoked */
#define FLASH_CFPA_ROTKH_REVOKE_RoTK0_EN(x)      (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_ROTKH_REVOKE_RoTK0_EN_SHIFT)) & FLASH_CFPA_ROTKH_REVOKE_RoTK0_EN_MASK)

#define FLASH_CFPA_ROTKH_REVOKE_RoTK1_EN_MASK    (0xCU)
#define FLASH_CFPA_ROTKH_REVOKE_RoTK1_EN_SHIFT   (2U)
/*! RoTK1_EN - RoT Key 1 enable. 00 - Invalid 01 - Enabled 10, 11 - Key revoked */
#define FLASH_CFPA_ROTKH_REVOKE_RoTK1_EN(x)      (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_ROTKH_REVOKE_RoTK1_EN_SHIFT)) & FLASH_CFPA_ROTKH_REVOKE_RoTK1_EN_MASK)

#define FLASH_CFPA_ROTKH_REVOKE_RoTK2_EN_MASK    (0x30U)
#define FLASH_CFPA_ROTKH_REVOKE_RoTK2_EN_SHIFT   (4U)
/*! RoTK2_EN - RoT Key 2 enable. 00 - Invalid 01 - Enabled 10, 11 - Key revoked */
#define FLASH_CFPA_ROTKH_REVOKE_RoTK2_EN(x)      (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_ROTKH_REVOKE_RoTK2_EN_SHIFT)) & FLASH_CFPA_ROTKH_REVOKE_RoTK2_EN_MASK)

#define FLASH_CFPA_ROTKH_REVOKE_RoTK3_EN_MASK    (0xC0U)
#define FLASH_CFPA_ROTKH_REVOKE_RoTK3_EN_SHIFT   (6U)
/*! RoTK3_EN - RoT Key 3 enable. 00 - Invalid 01 - Enabled 10, 11 - Key revoked */
#define FLASH_CFPA_ROTKH_REVOKE_RoTK3_EN(x)      (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_ROTKH_REVOKE_RoTK3_EN_SHIFT)) & FLASH_CFPA_ROTKH_REVOKE_RoTK3_EN_MASK)
/*! @} */

/*! @name VENDOR_USAGE -  */
/*! @{ */

#define FLASH_CFPA_VENDOR_USAGE_DBG_VENDOR_USAGE_MASK (0xFFFFU)
#define FLASH_CFPA_VENDOR_USAGE_DBG_VENDOR_USAGE_SHIFT (0U)
/*! DBG_VENDOR_USAGE - DBG_VENDOR_USAGE. */
#define FLASH_CFPA_VENDOR_USAGE_DBG_VENDOR_USAGE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_VENDOR_USAGE_DBG_VENDOR_USAGE_SHIFT)) & FLASH_CFPA_VENDOR_USAGE_DBG_VENDOR_USAGE_MASK)

#define FLASH_CFPA_VENDOR_USAGE_INVERSE_VALUE_MASK (0xFFFF0000U)
#define FLASH_CFPA_VENDOR_USAGE_INVERSE_VALUE_SHIFT (16U)
/*! INVERSE_VALUE - inverse value of bits [15:0] */
#define FLASH_CFPA_VENDOR_USAGE_INVERSE_VALUE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_VENDOR_USAGE_INVERSE_VALUE_SHIFT)) & FLASH_CFPA_VENDOR_USAGE_INVERSE_VALUE_MASK)
/*! @} */

/*! @name DCFG_CC_SOCU_PIN - With TZ-M, the part can be sold by level 1 customers (secure code developer) to level-2 customers who develops non-secure code only. - In this scenario, or easy of development, Level-I customer releases the part to always allow non-secure debug. - To allow level-2 customers to further seal the part DCFG_CC_SOCU_NS is used. - ROM will use this word to further restrict the debug access. */
/*! @{ */

#define FLASH_CFPA_DCFG_CC_SOCU_PIN_NIDEN_MASK   (0x1U)
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_NIDEN_SHIFT  (0U)
/*! NIDEN - Non Secure non-invasive debug enable
 *  0b0..Use DAP to enable
 *  0b1..Fixed state
 */
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_NIDEN(x)     (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_DCFG_CC_SOCU_PIN_NIDEN_SHIFT)) & FLASH_CFPA_DCFG_CC_SOCU_PIN_NIDEN_MASK)

#define FLASH_CFPA_DCFG_CC_SOCU_PIN_DBGEN_MASK   (0x2U)
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_DBGEN_SHIFT  (1U)
/*! DBGEN - Non Secure debug enable
 *  0b0..Use DAP to enable
 *  0b1..Fixed state
 */
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_DBGEN(x)     (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_DCFG_CC_SOCU_PIN_DBGEN_SHIFT)) & FLASH_CFPA_DCFG_CC_SOCU_PIN_DBGEN_MASK)

#define FLASH_CFPA_DCFG_CC_SOCU_PIN_SPNIDEN_MASK (0x4U)
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_SPNIDEN_SHIFT (2U)
/*! SPNIDEN - Secure non-invasive debug enable
 *  0b0..Use DAP to enable
 *  0b1..Fixed state
 */
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_SPNIDEN(x)   (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_DCFG_CC_SOCU_PIN_SPNIDEN_SHIFT)) & FLASH_CFPA_DCFG_CC_SOCU_PIN_SPNIDEN_MASK)

#define FLASH_CFPA_DCFG_CC_SOCU_PIN_SPIDEN_MASK  (0x8U)
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_SPIDEN_SHIFT (3U)
/*! SPIDEN - Secure invasive debug enable
 *  0b0..Use DAP to enable
 *  0b1..Fixed state
 */
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_SPIDEN(x)    (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_DCFG_CC_SOCU_PIN_SPIDEN_SHIFT)) & FLASH_CFPA_DCFG_CC_SOCU_PIN_SPIDEN_MASK)

#define FLASH_CFPA_DCFG_CC_SOCU_PIN_TAPEN_MASK   (0x10U)
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_TAPEN_SHIFT  (4U)
/*! TAPEN - JTAG TAP enable
 *  0b0..Use DAP to enable
 *  0b1..Fixed state
 */
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_TAPEN(x)     (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_DCFG_CC_SOCU_PIN_TAPEN_SHIFT)) & FLASH_CFPA_DCFG_CC_SOCU_PIN_TAPEN_MASK)

#define FLASH_CFPA_DCFG_CC_SOCU_PIN_ISP_CMD_EN_MASK (0x40U)
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_ISP_CMD_EN_SHIFT (6U)
/*! ISP_CMD_EN - ISP Boot Command enable
 *  0b0..Use DAP to enable
 *  0b1..Fixed state
 */
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_ISP_CMD_EN(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_DCFG_CC_SOCU_PIN_ISP_CMD_EN_SHIFT)) & FLASH_CFPA_DCFG_CC_SOCU_PIN_ISP_CMD_EN_MASK)

#define FLASH_CFPA_DCFG_CC_SOCU_PIN_FA_ME_CMD_EN_MASK (0x80U)
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_FA_ME_CMD_EN_SHIFT (7U)
/*! FA_ME_CMD_EN - FA Command enable
 *  0b0..Use DAP to enable
 *  0b1..Fixed state
 */
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_FA_ME_CMD_EN(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_DCFG_CC_SOCU_PIN_FA_ME_CMD_EN_SHIFT)) & FLASH_CFPA_DCFG_CC_SOCU_PIN_FA_ME_CMD_EN_MASK)

#define FLASH_CFPA_DCFG_CC_SOCU_PIN_UUID_CHECK_MASK (0x8000U)
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_UUID_CHECK_SHIFT (15U)
/*! UUID_CHECK - Enforce UUID match during Debug authentication. */
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_UUID_CHECK(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_DCFG_CC_SOCU_PIN_UUID_CHECK_SHIFT)) & FLASH_CFPA_DCFG_CC_SOCU_PIN_UUID_CHECK_MASK)

#define FLASH_CFPA_DCFG_CC_SOCU_PIN_INVERSE_VALUE_MASK (0xFFFF0000U)
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_INVERSE_VALUE_SHIFT (16U)
/*! INVERSE_VALUE - inverse value of bits [15:0] */
#define FLASH_CFPA_DCFG_CC_SOCU_PIN_INVERSE_VALUE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_DCFG_CC_SOCU_PIN_INVERSE_VALUE_SHIFT)) & FLASH_CFPA_DCFG_CC_SOCU_PIN_INVERSE_VALUE_MASK)
/*! @} */

/*! @name DCFG_CC_SOCU_DFLT - With TZ-M, the part can be sold by level 1 customers (secure code developer) to level-2 customers who develops non-secure code only. - In this scenario, or easy of development, Level-I customer releases the part to always allow non-secure debug. - To allow level-2 customers to further seal the part DCFG_CC_SOCU_NS is used. - ROM will use this word to further restrict the debug access. */
/*! @{ */

#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_NIDEN_MASK  (0x1U)
#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_NIDEN_SHIFT (0U)
/*! NIDEN - Non Secure non-invasive debug fixed state
 *  0b0..Disable
 *  0b1..Enable
 */
#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_NIDEN(x)    (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_DCFG_CC_SOCU_DFLT_NIDEN_SHIFT)) & FLASH_CFPA_DCFG_CC_SOCU_DFLT_NIDEN_MASK)

#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_DBGEN_MASK  (0x2U)
#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_DBGEN_SHIFT (1U)
/*! DBGEN - Non Secure debug fixed state
 *  0b0..Disable
 *  0b1..Enable
 */
#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_DBGEN(x)    (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_DCFG_CC_SOCU_DFLT_DBGEN_SHIFT)) & FLASH_CFPA_DCFG_CC_SOCU_DFLT_DBGEN_MASK)

#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_SPNIDEN_MASK (0x4U)
#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_SPNIDEN_SHIFT (2U)
/*! SPNIDEN - Secure non-invasive debug fixed state
 *  0b0..Disable
 *  0b1..Enable
 */
#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_SPNIDEN(x)  (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_DCFG_CC_SOCU_DFLT_SPNIDEN_SHIFT)) & FLASH_CFPA_DCFG_CC_SOCU_DFLT_SPNIDEN_MASK)

#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_SPIDEN_MASK (0x8U)
#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_SPIDEN_SHIFT (3U)
/*! SPIDEN - Secure invasive debug fixed state
 *  0b0..Disable
 *  0b1..Enable
 */
#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_SPIDEN(x)   (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_DCFG_CC_SOCU_DFLT_SPIDEN_SHIFT)) & FLASH_CFPA_DCFG_CC_SOCU_DFLT_SPIDEN_MASK)

#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_TAPEN_MASK  (0x10U)
#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_TAPEN_SHIFT (4U)
/*! TAPEN - JTAG TAP fixed state
 *  0b0..Disable
 *  0b1..Enable
 */
#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_TAPEN(x)    (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_DCFG_CC_SOCU_DFLT_TAPEN_SHIFT)) & FLASH_CFPA_DCFG_CC_SOCU_DFLT_TAPEN_MASK)

#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_ISP_CMD_EN_MASK (0x40U)
#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_ISP_CMD_EN_SHIFT (6U)
/*! ISP_CMD_EN - ISP Boot Command fixed state
 *  0b0..Disable
 *  0b1..Enable
 */
#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_ISP_CMD_EN(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_DCFG_CC_SOCU_DFLT_ISP_CMD_EN_SHIFT)) & FLASH_CFPA_DCFG_CC_SOCU_DFLT_ISP_CMD_EN_MASK)

#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_FA_ME_CMD_EN_MASK (0x80U)
#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_FA_ME_CMD_EN_SHIFT (7U)
/*! FA_ME_CMD_EN - FA Command fixed state
 *  0b0..Disable
 *  0b1..Enable
 */
#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_FA_ME_CMD_EN(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_DCFG_CC_SOCU_DFLT_FA_ME_CMD_EN_SHIFT)) & FLASH_CFPA_DCFG_CC_SOCU_DFLT_FA_ME_CMD_EN_MASK)

#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_INVERSE_VALUE_MASK (0xFFFF0000U)
#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_INVERSE_VALUE_SHIFT (16U)
/*! INVERSE_VALUE - inverse value of bits [15:0] */
#define FLASH_CFPA_DCFG_CC_SOCU_DFLT_INVERSE_VALUE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_DCFG_CC_SOCU_DFLT_INVERSE_VALUE_SHIFT)) & FLASH_CFPA_DCFG_CC_SOCU_DFLT_INVERSE_VALUE_MASK)
/*! @} */

/*! @name ENABLE_FA_MODE - Enable FA mode. SET_FA_MODE Command should write 0xC33CA55A to this word to indicate boot ROM to enter FA mode. */
/*! @{ */

#define FLASH_CFPA_ENABLE_FA_MODE_FIELD_MASK     (0xFFFFFFFFU)
#define FLASH_CFPA_ENABLE_FA_MODE_FIELD_SHIFT    (0U)
#define FLASH_CFPA_ENABLE_FA_MODE_FIELD(x)       (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_ENABLE_FA_MODE_FIELD_SHIFT)) & FLASH_CFPA_ENABLE_FA_MODE_FIELD_MASK)
/*! @} */

/*! @name CMPA_PROG_IN_PROGRESS - CMPA Page programming on going. This field shall be set to 0x5CC55AA5 in the active CFPA page each time CMPA page programming is going on. It shall always be set to 0x00000000 in the CFPA scratch area. */
/*! @{ */

#define FLASH_CFPA_CMPA_PROG_IN_PROGRESS_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_CFPA_CMPA_PROG_IN_PROGRESS_FIELD_SHIFT (0U)
#define FLASH_CFPA_CMPA_PROG_IN_PROGRESS_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_CMPA_PROG_IN_PROGRESS_FIELD_SHIFT)) & FLASH_CFPA_CMPA_PROG_IN_PROGRESS_FIELD_MASK)
/*! @} */

/*! @name PRINCE_REGION0_IV_CODE -  */
/*! @{ */

#define FLASH_CFPA_PRINCE_REGION0_IV_CODE_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_CFPA_PRINCE_REGION0_IV_CODE_FIELD_SHIFT (0U)
#define FLASH_CFPA_PRINCE_REGION0_IV_CODE_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION0_IV_CODE_FIELD_SHIFT)) & FLASH_CFPA_PRINCE_REGION0_IV_CODE_FIELD_MASK)
/*! @} */

/* The count of FLASH_CFPA_PRINCE_REGION0_IV_CODE */
#define FLASH_CFPA_PRINCE_REGION0_IV_CODE_COUNT  (14U)

/*! @name PRINCE_REGION0_IV_HEADER0 -  */
/*! @{ */

#define FLASH_CFPA_PRINCE_REGION0_IV_HEADER0_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_CFPA_PRINCE_REGION0_IV_HEADER0_FIELD_SHIFT (0U)
#define FLASH_CFPA_PRINCE_REGION0_IV_HEADER0_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION0_IV_HEADER0_FIELD_SHIFT)) & FLASH_CFPA_PRINCE_REGION0_IV_HEADER0_FIELD_MASK)
/*! @} */

/*! @name PRINCE_REGION0_IV_HEADER1 -  */
/*! @{ */

#define FLASH_CFPA_PRINCE_REGION0_IV_HEADER1_TYPE_MASK (0x3U)
#define FLASH_CFPA_PRINCE_REGION0_IV_HEADER1_TYPE_SHIFT (0U)
#define FLASH_CFPA_PRINCE_REGION0_IV_HEADER1_TYPE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION0_IV_HEADER1_TYPE_SHIFT)) & FLASH_CFPA_PRINCE_REGION0_IV_HEADER1_TYPE_MASK)

#define FLASH_CFPA_PRINCE_REGION0_IV_HEADER1_INDEX_MASK (0xF00U)
#define FLASH_CFPA_PRINCE_REGION0_IV_HEADER1_INDEX_SHIFT (8U)
#define FLASH_CFPA_PRINCE_REGION0_IV_HEADER1_INDEX(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION0_IV_HEADER1_INDEX_SHIFT)) & FLASH_CFPA_PRINCE_REGION0_IV_HEADER1_INDEX_MASK)

#define FLASH_CFPA_PRINCE_REGION0_IV_HEADER1_SIZE_MASK (0x3F000000U)
#define FLASH_CFPA_PRINCE_REGION0_IV_HEADER1_SIZE_SHIFT (24U)
#define FLASH_CFPA_PRINCE_REGION0_IV_HEADER1_SIZE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION0_IV_HEADER1_SIZE_SHIFT)) & FLASH_CFPA_PRINCE_REGION0_IV_HEADER1_SIZE_MASK)
/*! @} */

/*! @name PRINCE_REGION0_IV_BODY -  */
/*! @{ */

#define FLASH_CFPA_PRINCE_REGION0_IV_BODY_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_CFPA_PRINCE_REGION0_IV_BODY_FIELD_SHIFT (0U)
#define FLASH_CFPA_PRINCE_REGION0_IV_BODY_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION0_IV_BODY_FIELD_SHIFT)) & FLASH_CFPA_PRINCE_REGION0_IV_BODY_FIELD_MASK)
/*! @} */

/* The count of FLASH_CFPA_PRINCE_REGION0_IV_BODY */
#define FLASH_CFPA_PRINCE_REGION0_IV_BODY_COUNT  (12U)

/*! @name PRINCE_REGION1_IV_CODE -  */
/*! @{ */

#define FLASH_CFPA_PRINCE_REGION1_IV_CODE_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_CFPA_PRINCE_REGION1_IV_CODE_FIELD_SHIFT (0U)
#define FLASH_CFPA_PRINCE_REGION1_IV_CODE_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION1_IV_CODE_FIELD_SHIFT)) & FLASH_CFPA_PRINCE_REGION1_IV_CODE_FIELD_MASK)
/*! @} */

/* The count of FLASH_CFPA_PRINCE_REGION1_IV_CODE */
#define FLASH_CFPA_PRINCE_REGION1_IV_CODE_COUNT  (14U)

/*! @name PRINCE_REGION1_IV_HEADER0 -  */
/*! @{ */

#define FLASH_CFPA_PRINCE_REGION1_IV_HEADER0_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_CFPA_PRINCE_REGION1_IV_HEADER0_FIELD_SHIFT (0U)
#define FLASH_CFPA_PRINCE_REGION1_IV_HEADER0_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION1_IV_HEADER0_FIELD_SHIFT)) & FLASH_CFPA_PRINCE_REGION1_IV_HEADER0_FIELD_MASK)
/*! @} */

/*! @name PRINCE_REGION1_IV_HEADER1 -  */
/*! @{ */

#define FLASH_CFPA_PRINCE_REGION1_IV_HEADER1_TYPE_MASK (0x3U)
#define FLASH_CFPA_PRINCE_REGION1_IV_HEADER1_TYPE_SHIFT (0U)
#define FLASH_CFPA_PRINCE_REGION1_IV_HEADER1_TYPE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION1_IV_HEADER1_TYPE_SHIFT)) & FLASH_CFPA_PRINCE_REGION1_IV_HEADER1_TYPE_MASK)

#define FLASH_CFPA_PRINCE_REGION1_IV_HEADER1_INDEX_MASK (0xF00U)
#define FLASH_CFPA_PRINCE_REGION1_IV_HEADER1_INDEX_SHIFT (8U)
#define FLASH_CFPA_PRINCE_REGION1_IV_HEADER1_INDEX(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION1_IV_HEADER1_INDEX_SHIFT)) & FLASH_CFPA_PRINCE_REGION1_IV_HEADER1_INDEX_MASK)

#define FLASH_CFPA_PRINCE_REGION1_IV_HEADER1_SIZE_MASK (0x3F000000U)
#define FLASH_CFPA_PRINCE_REGION1_IV_HEADER1_SIZE_SHIFT (24U)
#define FLASH_CFPA_PRINCE_REGION1_IV_HEADER1_SIZE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION1_IV_HEADER1_SIZE_SHIFT)) & FLASH_CFPA_PRINCE_REGION1_IV_HEADER1_SIZE_MASK)
/*! @} */

/*! @name PRINCE_REGION1_IV_BODY -  */
/*! @{ */

#define FLASH_CFPA_PRINCE_REGION1_IV_BODY_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_CFPA_PRINCE_REGION1_IV_BODY_FIELD_SHIFT (0U)
#define FLASH_CFPA_PRINCE_REGION1_IV_BODY_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION1_IV_BODY_FIELD_SHIFT)) & FLASH_CFPA_PRINCE_REGION1_IV_BODY_FIELD_MASK)
/*! @} */

/* The count of FLASH_CFPA_PRINCE_REGION1_IV_BODY */
#define FLASH_CFPA_PRINCE_REGION1_IV_BODY_COUNT  (12U)

/*! @name PRINCE_REGION2_IV_CODE -  */
/*! @{ */

#define FLASH_CFPA_PRINCE_REGION2_IV_CODE_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_CFPA_PRINCE_REGION2_IV_CODE_FIELD_SHIFT (0U)
#define FLASH_CFPA_PRINCE_REGION2_IV_CODE_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION2_IV_CODE_FIELD_SHIFT)) & FLASH_CFPA_PRINCE_REGION2_IV_CODE_FIELD_MASK)
/*! @} */

/* The count of FLASH_CFPA_PRINCE_REGION2_IV_CODE */
#define FLASH_CFPA_PRINCE_REGION2_IV_CODE_COUNT  (14U)

/*! @name PRINCE_REGION2_IV_HEADER0 -  */
/*! @{ */

#define FLASH_CFPA_PRINCE_REGION2_IV_HEADER0_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_CFPA_PRINCE_REGION2_IV_HEADER0_FIELD_SHIFT (0U)
#define FLASH_CFPA_PRINCE_REGION2_IV_HEADER0_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION2_IV_HEADER0_FIELD_SHIFT)) & FLASH_CFPA_PRINCE_REGION2_IV_HEADER0_FIELD_MASK)
/*! @} */

/*! @name PRINCE_REGION2_IV_HEADER1 -  */
/*! @{ */

#define FLASH_CFPA_PRINCE_REGION2_IV_HEADER1_TYPE_MASK (0x3U)
#define FLASH_CFPA_PRINCE_REGION2_IV_HEADER1_TYPE_SHIFT (0U)
#define FLASH_CFPA_PRINCE_REGION2_IV_HEADER1_TYPE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION2_IV_HEADER1_TYPE_SHIFT)) & FLASH_CFPA_PRINCE_REGION2_IV_HEADER1_TYPE_MASK)

#define FLASH_CFPA_PRINCE_REGION2_IV_HEADER1_INDEX_MASK (0xF00U)
#define FLASH_CFPA_PRINCE_REGION2_IV_HEADER1_INDEX_SHIFT (8U)
#define FLASH_CFPA_PRINCE_REGION2_IV_HEADER1_INDEX(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION2_IV_HEADER1_INDEX_SHIFT)) & FLASH_CFPA_PRINCE_REGION2_IV_HEADER1_INDEX_MASK)

#define FLASH_CFPA_PRINCE_REGION2_IV_HEADER1_SIZE_MASK (0x3F000000U)
#define FLASH_CFPA_PRINCE_REGION2_IV_HEADER1_SIZE_SHIFT (24U)
#define FLASH_CFPA_PRINCE_REGION2_IV_HEADER1_SIZE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION2_IV_HEADER1_SIZE_SHIFT)) & FLASH_CFPA_PRINCE_REGION2_IV_HEADER1_SIZE_MASK)
/*! @} */

/*! @name PRINCE_REGION2_IV_BODY -  */
/*! @{ */

#define FLASH_CFPA_PRINCE_REGION2_IV_BODY_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_CFPA_PRINCE_REGION2_IV_BODY_FIELD_SHIFT (0U)
#define FLASH_CFPA_PRINCE_REGION2_IV_BODY_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_PRINCE_REGION2_IV_BODY_FIELD_SHIFT)) & FLASH_CFPA_PRINCE_REGION2_IV_BODY_FIELD_MASK)
/*! @} */

/* The count of FLASH_CFPA_PRINCE_REGION2_IV_BODY */
#define FLASH_CFPA_PRINCE_REGION2_IV_BODY_COUNT  (12U)

/*! @name CUSTOMER_DEFINED - Customer Defined (Programable through ROM API) */
/*! @{ */

#define FLASH_CFPA_CUSTOMER_DEFINED_FIELD_MASK   (0xFFFFFFFFU)
#define FLASH_CFPA_CUSTOMER_DEFINED_FIELD_SHIFT  (0U)
#define FLASH_CFPA_CUSTOMER_DEFINED_FIELD(x)     (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_CUSTOMER_DEFINED_FIELD_SHIFT)) & FLASH_CFPA_CUSTOMER_DEFINED_FIELD_MASK)
/*! @} */

/*! @name SHA256_DIGEST - SHA256_DIGEST0 for DIGEST[31:0]..SHA256_DIGEST7 for DIGEST[255:224] */
/*! @{ */

#define FLASH_CFPA_SHA256_DIGEST_FIELD_MASK      (0xFFFFFFFFU)
#define FLASH_CFPA_SHA256_DIGEST_FIELD_SHIFT     (0U)
#define FLASH_CFPA_SHA256_DIGEST_FIELD(x)        (((uint32_t)(((uint32_t)(x)) << FLASH_CFPA_SHA256_DIGEST_FIELD_SHIFT)) & FLASH_CFPA_SHA256_DIGEST_FIELD_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group FLASH_CFPA_Register_Masks */


/*!
 * @}
 */ /* end of group FLASH_CFPA_Peripheral_Access_Layer */


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


#endif  /* FLASH_CFPA_H_ */


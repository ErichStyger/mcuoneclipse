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
**         CMSIS Peripheral Access Layer for FLASH_CMPA
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
 * @file FLASH_CMPA.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for FLASH_CMPA
 *
 * CMSIS Peripheral Access Layer for FLASH_CMPA
 */

#if !defined(FLASH_CMPA_H_)
#define FLASH_CMPA_H_                            /**< Symbol preventing repeated inclusion */

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
   -- FLASH_CMPA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLASH_CMPA_Peripheral_Access_Layer FLASH_CMPA Peripheral Access Layer
 * @{
 */

/** FLASH_CMPA - Size of Registers Arrays */
#define FLASH_CMPA_ROTKH_COUNT                    8u
#define FLASH_CMPA_CUSTOMER_DEFINED_COUNT         56u
#define FLASH_CMPA_SHA256_DIGEST_COUNT            8u

/** FLASH_CMPA - Register Layout Typedef */
typedef struct {
  __IO uint32_t BOOT_CFG;                          /**< offset: 0x0 */
  __IO uint32_t SPI_FLASH_CFG;                     /**< offset: 0x4 */
  __IO uint32_t USB_ID;                            /**< offset: 0x8 */
  __IO uint32_t SDIO_CFG;                          /**< offset: 0xC */
  __IO uint32_t CC_SOCU_PIN;                       /**< offset: 0x10 */
  __IO uint32_t CC_SOCU_DFLT;                      /**< offset: 0x14 */
  __IO uint32_t VENDOR_USAGE;                      /**< offset: 0x18 */
  __IO uint32_t SECURE_BOOT_CFG;                   /**< Secure boot configuration flags., offset: 0x1C */
  __IO uint32_t PRINCE_BASE_ADDR;                  /**< offset: 0x20 */
  __IO uint32_t PRINCE_SR_0;                       /**< Region 0, sub-region enable, offset: 0x24 */
  __IO uint32_t PRINCE_SR_1;                       /**< Region 1, sub-region enable, offset: 0x28 */
  __IO uint32_t PRINCE_SR_2;                       /**< Region 2, sub-region enable, offset: 0x2C */
  __IO uint32_t XTAL_32KHZ_CAPABANK_TRIM;          /**< Xtal 32kHz capabank triming., offset: 0x30 */
  __IO uint32_t XTAL_16MHZ_CAPABANK_TRIM;          /**< Xtal 16MHz capabank triming., offset: 0x34 */
  __IO uint32_t FLASH_REMAP_SIZE;                  /**< This 32-bit register contains the size of the image to remap, in bytes. The 12 LSBs are ignored, so the size granularity is 4KB., offset: 0x38 */
  __IO uint32_t FLASH_REMAP_OFFSET;                /**< This 32-bit register contains the offset by which the image is to be remapped. The 12 LSBs are ignored, so the remap granularity is 4KB., offset: 0x3C */
       uint8_t RESERVED_0[16];
  __IO uint32_t ROTKH[FLASH_CMPA_ROTKH_COUNT];     /**< ROTKH0 for Root of Trust Keys Table hash[255:224]..ROTKH7 for Root of Trust Keys Table hash[31:0], array offset: 0x50, array step: 0x4 */
       uint8_t RESERVED_1[144];
  __IO uint32_t CUSTOMER_DEFINED[FLASH_CMPA_CUSTOMER_DEFINED_COUNT]; /**< Customer Defined (Programable through ROM API), array offset: 0x100, array step: 0x4 */
  __IO uint32_t SHA256_DIGEST[FLASH_CMPA_SHA256_DIGEST_COUNT]; /**< SHA256_DIGEST0 for DIGEST[31:0]..SHA256_DIGEST7 for DIGEST[255:224], array offset: 0x1E0, array step: 0x4 */
} FLASH_CMPA_Type;

/* ----------------------------------------------------------------------------
   -- FLASH_CMPA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLASH_CMPA_Register_Masks FLASH_CMPA Register Masks
 * @{
 */

/*! @name BOOT_CFG -  */
/*! @{ */

#define FLASH_CMPA_BOOT_CFG_DEFAULT_ISP_MODE_MASK (0x70U)
#define FLASH_CMPA_BOOT_CFG_DEFAULT_ISP_MODE_SHIFT (4U)
/*! DEFAULT_ISP_MODE - Default ISP mode:
 *  0b000..Auto ISP
 *  0b001..USB_HID_ISP
 *  0b010..UART ISP
 *  0b011..SPI Slave ISP
 *  0b100..I2C Slave ISP
 *  0b111..Disable ISP fall through
 */
#define FLASH_CMPA_BOOT_CFG_DEFAULT_ISP_MODE(x)  (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_BOOT_CFG_DEFAULT_ISP_MODE_SHIFT)) & FLASH_CMPA_BOOT_CFG_DEFAULT_ISP_MODE_MASK)

#define FLASH_CMPA_BOOT_CFG_BOOT_SPEED_MASK      (0x180U)
#define FLASH_CMPA_BOOT_CFG_BOOT_SPEED_SHIFT     (7U)
/*! BOOT_SPEED - Core clock:
 *  0b00..Defined by NMPA.SYSTEM_SPEED_CODE
 *  0b10..48MHz FRO
 */
#define FLASH_CMPA_BOOT_CFG_BOOT_SPEED(x)        (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_BOOT_CFG_BOOT_SPEED_SHIFT)) & FLASH_CMPA_BOOT_CFG_BOOT_SPEED_MASK)

#define FLASH_CMPA_BOOT_CFG_BOOT_FAILURE_PIN_MASK (0xFF000000U)
#define FLASH_CMPA_BOOT_CFG_BOOT_FAILURE_PIN_SHIFT (24U)
/*! BOOT_FAILURE_PIN - GPIO port and pin number to use for indicating failure reason. The toggle
 *    rate of the pin is used to decode the error type. [2:0] - Defines GPIO port [7:3] - Defines GPIO
 *    pin
 */
#define FLASH_CMPA_BOOT_CFG_BOOT_FAILURE_PIN(x)  (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_BOOT_CFG_BOOT_FAILURE_PIN_SHIFT)) & FLASH_CMPA_BOOT_CFG_BOOT_FAILURE_PIN_MASK)
/*! @} */

/*! @name SPI_FLASH_CFG -  */
/*! @{ */

#define FLASH_CMPA_SPI_FLASH_CFG_SPI_RECOVERY_BOOT_EN_MASK (0x1FU)
#define FLASH_CMPA_SPI_FLASH_CFG_SPI_RECOVERY_BOOT_EN_SHIFT (0U)
/*! SPI_RECOVERY_BOOT_EN - SPI flash recovery boot is enabled, if non-zero value is written to this field. */
#define FLASH_CMPA_SPI_FLASH_CFG_SPI_RECOVERY_BOOT_EN(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_SPI_FLASH_CFG_SPI_RECOVERY_BOOT_EN_SHIFT)) & FLASH_CMPA_SPI_FLASH_CFG_SPI_RECOVERY_BOOT_EN_MASK)
/*! @} */

/*! @name USB_ID -  */
/*! @{ */

#define FLASH_CMPA_USB_ID_USB_VENDOR_ID_MASK     (0xFFFFU)
#define FLASH_CMPA_USB_ID_USB_VENDOR_ID_SHIFT    (0U)
#define FLASH_CMPA_USB_ID_USB_VENDOR_ID(x)       (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_USB_ID_USB_VENDOR_ID_SHIFT)) & FLASH_CMPA_USB_ID_USB_VENDOR_ID_MASK)

#define FLASH_CMPA_USB_ID_USB_PRODUCT_ID_MASK    (0xFFFF0000U)
#define FLASH_CMPA_USB_ID_USB_PRODUCT_ID_SHIFT   (16U)
#define FLASH_CMPA_USB_ID_USB_PRODUCT_ID(x)      (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_USB_ID_USB_PRODUCT_ID_SHIFT)) & FLASH_CMPA_USB_ID_USB_PRODUCT_ID_MASK)
/*! @} */

/*! @name SDIO_CFG -  */
/*! @{ */

#define FLASH_CMPA_SDIO_CFG_FIELD_MASK           (0xFFFFFFFFU)
#define FLASH_CMPA_SDIO_CFG_FIELD_SHIFT          (0U)
#define FLASH_CMPA_SDIO_CFG_FIELD(x)             (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_SDIO_CFG_FIELD_SHIFT)) & FLASH_CMPA_SDIO_CFG_FIELD_MASK)
/*! @} */

/*! @name CC_SOCU_PIN -  */
/*! @{ */

#define FLASH_CMPA_CC_SOCU_PIN_NIDEN_MASK        (0x1U)
#define FLASH_CMPA_CC_SOCU_PIN_NIDEN_SHIFT       (0U)
/*! NIDEN - Non Secure non-invasive debug enable
 *  0b0..Use DAP to enable
 *  0b1..Fixed state
 */
#define FLASH_CMPA_CC_SOCU_PIN_NIDEN(x)          (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CC_SOCU_PIN_NIDEN_SHIFT)) & FLASH_CMPA_CC_SOCU_PIN_NIDEN_MASK)

#define FLASH_CMPA_CC_SOCU_PIN_DBGEN_MASK        (0x2U)
#define FLASH_CMPA_CC_SOCU_PIN_DBGEN_SHIFT       (1U)
/*! DBGEN - Non Secure debug enable
 *  0b0..Use DAP to enable
 *  0b1..Fixed state
 */
#define FLASH_CMPA_CC_SOCU_PIN_DBGEN(x)          (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CC_SOCU_PIN_DBGEN_SHIFT)) & FLASH_CMPA_CC_SOCU_PIN_DBGEN_MASK)

#define FLASH_CMPA_CC_SOCU_PIN_SPNIDEN_MASK      (0x4U)
#define FLASH_CMPA_CC_SOCU_PIN_SPNIDEN_SHIFT     (2U)
/*! SPNIDEN - Secure non-invasive debug enable
 *  0b0..Use DAP to enable
 *  0b1..Fixed state
 */
#define FLASH_CMPA_CC_SOCU_PIN_SPNIDEN(x)        (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CC_SOCU_PIN_SPNIDEN_SHIFT)) & FLASH_CMPA_CC_SOCU_PIN_SPNIDEN_MASK)

#define FLASH_CMPA_CC_SOCU_PIN_SPIDEN_MASK       (0x8U)
#define FLASH_CMPA_CC_SOCU_PIN_SPIDEN_SHIFT      (3U)
/*! SPIDEN - Secure invasive debug enable
 *  0b0..Use DAP to enable
 *  0b1..Fixed state
 */
#define FLASH_CMPA_CC_SOCU_PIN_SPIDEN(x)         (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CC_SOCU_PIN_SPIDEN_SHIFT)) & FLASH_CMPA_CC_SOCU_PIN_SPIDEN_MASK)

#define FLASH_CMPA_CC_SOCU_PIN_TAPEN_MASK        (0x10U)
#define FLASH_CMPA_CC_SOCU_PIN_TAPEN_SHIFT       (4U)
/*! TAPEN - JTAG TAP enable
 *  0b0..Use DAP to enable
 *  0b1..Fixed state
 */
#define FLASH_CMPA_CC_SOCU_PIN_TAPEN(x)          (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CC_SOCU_PIN_TAPEN_SHIFT)) & FLASH_CMPA_CC_SOCU_PIN_TAPEN_MASK)

#define FLASH_CMPA_CC_SOCU_PIN_ISP_CMD_EN_MASK   (0x40U)
#define FLASH_CMPA_CC_SOCU_PIN_ISP_CMD_EN_SHIFT  (6U)
/*! ISP_CMD_EN - ISP Boot Command enable
 *  0b0..Use DAP to enable
 *  0b1..Fixed state
 */
#define FLASH_CMPA_CC_SOCU_PIN_ISP_CMD_EN(x)     (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CC_SOCU_PIN_ISP_CMD_EN_SHIFT)) & FLASH_CMPA_CC_SOCU_PIN_ISP_CMD_EN_MASK)

#define FLASH_CMPA_CC_SOCU_PIN_FA_ME_CMD_EN_MASK (0x80U)
#define FLASH_CMPA_CC_SOCU_PIN_FA_ME_CMD_EN_SHIFT (7U)
/*! FA_ME_CMD_EN - FA Command enable
 *  0b0..Use DAP to enable
 *  0b1..Fixed state
 */
#define FLASH_CMPA_CC_SOCU_PIN_FA_ME_CMD_EN(x)   (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CC_SOCU_PIN_FA_ME_CMD_EN_SHIFT)) & FLASH_CMPA_CC_SOCU_PIN_FA_ME_CMD_EN_MASK)

#define FLASH_CMPA_CC_SOCU_PIN_UUID_CHECK_MASK   (0x8000U)
#define FLASH_CMPA_CC_SOCU_PIN_UUID_CHECK_SHIFT  (15U)
/*! UUID_CHECK - Enforce UUID match during Debug authentication. */
#define FLASH_CMPA_CC_SOCU_PIN_UUID_CHECK(x)     (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CC_SOCU_PIN_UUID_CHECK_SHIFT)) & FLASH_CMPA_CC_SOCU_PIN_UUID_CHECK_MASK)

#define FLASH_CMPA_CC_SOCU_PIN_INVERSE_VALUE_MASK (0xFFFF0000U)
#define FLASH_CMPA_CC_SOCU_PIN_INVERSE_VALUE_SHIFT (16U)
/*! INVERSE_VALUE - inverse value of bits [15:0] */
#define FLASH_CMPA_CC_SOCU_PIN_INVERSE_VALUE(x)  (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CC_SOCU_PIN_INVERSE_VALUE_SHIFT)) & FLASH_CMPA_CC_SOCU_PIN_INVERSE_VALUE_MASK)
/*! @} */

/*! @name CC_SOCU_DFLT -  */
/*! @{ */

#define FLASH_CMPA_CC_SOCU_DFLT_NIDEN_MASK       (0x1U)
#define FLASH_CMPA_CC_SOCU_DFLT_NIDEN_SHIFT      (0U)
/*! NIDEN - Non Secure non-invasive debug fixed state
 *  0b0..Disable
 *  0b1..Enable
 */
#define FLASH_CMPA_CC_SOCU_DFLT_NIDEN(x)         (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CC_SOCU_DFLT_NIDEN_SHIFT)) & FLASH_CMPA_CC_SOCU_DFLT_NIDEN_MASK)

#define FLASH_CMPA_CC_SOCU_DFLT_DBGEN_MASK       (0x2U)
#define FLASH_CMPA_CC_SOCU_DFLT_DBGEN_SHIFT      (1U)
/*! DBGEN - Non Secure debug fixed state
 *  0b0..Disable
 *  0b1..Enable
 */
#define FLASH_CMPA_CC_SOCU_DFLT_DBGEN(x)         (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CC_SOCU_DFLT_DBGEN_SHIFT)) & FLASH_CMPA_CC_SOCU_DFLT_DBGEN_MASK)

#define FLASH_CMPA_CC_SOCU_DFLT_SPNIDEN_MASK     (0x4U)
#define FLASH_CMPA_CC_SOCU_DFLT_SPNIDEN_SHIFT    (2U)
/*! SPNIDEN - Secure non-invasive debug fixed state
 *  0b0..Disable
 *  0b1..Enable
 */
#define FLASH_CMPA_CC_SOCU_DFLT_SPNIDEN(x)       (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CC_SOCU_DFLT_SPNIDEN_SHIFT)) & FLASH_CMPA_CC_SOCU_DFLT_SPNIDEN_MASK)

#define FLASH_CMPA_CC_SOCU_DFLT_SPIDEN_MASK      (0x8U)
#define FLASH_CMPA_CC_SOCU_DFLT_SPIDEN_SHIFT     (3U)
/*! SPIDEN - Secure invasive debug fixed state
 *  0b0..Disable
 *  0b1..Enable
 */
#define FLASH_CMPA_CC_SOCU_DFLT_SPIDEN(x)        (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CC_SOCU_DFLT_SPIDEN_SHIFT)) & FLASH_CMPA_CC_SOCU_DFLT_SPIDEN_MASK)

#define FLASH_CMPA_CC_SOCU_DFLT_TAPEN_MASK       (0x10U)
#define FLASH_CMPA_CC_SOCU_DFLT_TAPEN_SHIFT      (4U)
/*! TAPEN - JTAG TAP fixed state
 *  0b0..Disable
 *  0b1..Enable
 */
#define FLASH_CMPA_CC_SOCU_DFLT_TAPEN(x)         (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CC_SOCU_DFLT_TAPEN_SHIFT)) & FLASH_CMPA_CC_SOCU_DFLT_TAPEN_MASK)

#define FLASH_CMPA_CC_SOCU_DFLT_ISP_CMD_EN_MASK  (0x40U)
#define FLASH_CMPA_CC_SOCU_DFLT_ISP_CMD_EN_SHIFT (6U)
/*! ISP_CMD_EN - ISP Boot Command fixed state
 *  0b0..Disable
 *  0b1..Enable
 */
#define FLASH_CMPA_CC_SOCU_DFLT_ISP_CMD_EN(x)    (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CC_SOCU_DFLT_ISP_CMD_EN_SHIFT)) & FLASH_CMPA_CC_SOCU_DFLT_ISP_CMD_EN_MASK)

#define FLASH_CMPA_CC_SOCU_DFLT_FA_ME_CMD_EN_MASK (0x80U)
#define FLASH_CMPA_CC_SOCU_DFLT_FA_ME_CMD_EN_SHIFT (7U)
/*! FA_ME_CMD_EN - FA Command fixed state
 *  0b0..Disable
 *  0b1..Enable
 */
#define FLASH_CMPA_CC_SOCU_DFLT_FA_ME_CMD_EN(x)  (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CC_SOCU_DFLT_FA_ME_CMD_EN_SHIFT)) & FLASH_CMPA_CC_SOCU_DFLT_FA_ME_CMD_EN_MASK)

#define FLASH_CMPA_CC_SOCU_DFLT_INVERSE_VALUE_MASK (0xFFFF0000U)
#define FLASH_CMPA_CC_SOCU_DFLT_INVERSE_VALUE_SHIFT (16U)
/*! INVERSE_VALUE - inverse value of bits [15:0] */
#define FLASH_CMPA_CC_SOCU_DFLT_INVERSE_VALUE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CC_SOCU_DFLT_INVERSE_VALUE_SHIFT)) & FLASH_CMPA_CC_SOCU_DFLT_INVERSE_VALUE_MASK)
/*! @} */

/*! @name VENDOR_USAGE -  */
/*! @{ */

#define FLASH_CMPA_VENDOR_USAGE_VENDOR_USAGE_MASK (0xFFFF0000U)
#define FLASH_CMPA_VENDOR_USAGE_VENDOR_USAGE_SHIFT (16U)
/*! VENDOR_USAGE - Upper 16 bits of vendor usage field defined in DAP. Lower 16-bits come from customer field area. */
#define FLASH_CMPA_VENDOR_USAGE_VENDOR_USAGE(x)  (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_VENDOR_USAGE_VENDOR_USAGE_SHIFT)) & FLASH_CMPA_VENDOR_USAGE_VENDOR_USAGE_MASK)
/*! @} */

/*! @name SECURE_BOOT_CFG - Secure boot configuration flags. */
/*! @{ */

#define FLASH_CMPA_SECURE_BOOT_CFG_RSA4K_MASK    (0x3U)
#define FLASH_CMPA_SECURE_BOOT_CFG_RSA4K_SHIFT   (0U)
/*! RSA4K - Use RSA4096 keys only.
 *  0b00..Allow RSA2048 and higher
 *  0b01..RSA4096 only
 *  0b10..RSA4096 only
 *  0b11..RSA4096 only
 */
#define FLASH_CMPA_SECURE_BOOT_CFG_RSA4K(x)      (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_SECURE_BOOT_CFG_RSA4K_SHIFT)) & FLASH_CMPA_SECURE_BOOT_CFG_RSA4K_MASK)

#define FLASH_CMPA_SECURE_BOOT_CFG_DICE_INC_NXP_CFG_MASK (0xCU)
#define FLASH_CMPA_SECURE_BOOT_CFG_DICE_INC_NXP_CFG_SHIFT (2U)
/*! DICE_INC_NXP_CFG - Include NXP area in DICE computation.
 *  0b00..not included
 *  0b01..included
 *  0b10..included
 *  0b11..included
 */
#define FLASH_CMPA_SECURE_BOOT_CFG_DICE_INC_NXP_CFG(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_SECURE_BOOT_CFG_DICE_INC_NXP_CFG_SHIFT)) & FLASH_CMPA_SECURE_BOOT_CFG_DICE_INC_NXP_CFG_MASK)

#define FLASH_CMPA_SECURE_BOOT_CFG_DICE_CUST_CFG_MASK (0x30U)
#define FLASH_CMPA_SECURE_BOOT_CFG_DICE_CUST_CFG_SHIFT (4U)
/*! DICE_CUST_CFG - Include Customer factory area (including keys) in DICE computation.
 *  0b00..not included
 *  0b01..included
 *  0b10..included
 *  0b11..included
 */
#define FLASH_CMPA_SECURE_BOOT_CFG_DICE_CUST_CFG(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_SECURE_BOOT_CFG_DICE_CUST_CFG_SHIFT)) & FLASH_CMPA_SECURE_BOOT_CFG_DICE_CUST_CFG_MASK)

#define FLASH_CMPA_SECURE_BOOT_CFG_SKIP_DICE_MASK (0xC0U)
#define FLASH_CMPA_SECURE_BOOT_CFG_SKIP_DICE_SHIFT (6U)
/*! SKIP_DICE - Skip DICE computation
 *  0b00..Enable DICE
 *  0b01..Disable DICE
 *  0b10..Disable DICE
 *  0b11..Disable DICE
 */
#define FLASH_CMPA_SECURE_BOOT_CFG_SKIP_DICE(x)  (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_SECURE_BOOT_CFG_SKIP_DICE_SHIFT)) & FLASH_CMPA_SECURE_BOOT_CFG_SKIP_DICE_MASK)

#define FLASH_CMPA_SECURE_BOOT_CFG_TZM_IMAGE_TYPE_MASK (0x300U)
#define FLASH_CMPA_SECURE_BOOT_CFG_TZM_IMAGE_TYPE_SHIFT (8U)
/*! TZM_IMAGE_TYPE - TrustZone-M mode
 *  0b00..TZ-M image mode is taken from application image header
 *  0b01..TZ-M disabled image, boots to non-secure mode
 *  0b10..TZ-M enabled image, boots to secure mode
 *  0b11..TZ-M enabled image with TZ-M preset, boot to secure mode TZ-M pre-configured by data from application image header
 */
#define FLASH_CMPA_SECURE_BOOT_CFG_TZM_IMAGE_TYPE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_SECURE_BOOT_CFG_TZM_IMAGE_TYPE_SHIFT)) & FLASH_CMPA_SECURE_BOOT_CFG_TZM_IMAGE_TYPE_MASK)

#define FLASH_CMPA_SECURE_BOOT_CFG_BLOCK_SET_KEY_MASK (0xC00U)
#define FLASH_CMPA_SECURE_BOOT_CFG_BLOCK_SET_KEY_SHIFT (10U)
/*! BLOCK_SET_KEY - Block PUF key code generation
 *  0b00..Allow PUF Key Code generation
 *  0b01..Disable PUF Key Code generation
 *  0b10..Disable PUF Key Code generation
 *  0b11..Disable PUF Key Code generation
 */
#define FLASH_CMPA_SECURE_BOOT_CFG_BLOCK_SET_KEY(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_SECURE_BOOT_CFG_BLOCK_SET_KEY_SHIFT)) & FLASH_CMPA_SECURE_BOOT_CFG_BLOCK_SET_KEY_MASK)

#define FLASH_CMPA_SECURE_BOOT_CFG_BLOCK_ENROLL_MASK (0x3000U)
#define FLASH_CMPA_SECURE_BOOT_CFG_BLOCK_ENROLL_SHIFT (12U)
/*! BLOCK_ENROLL - Block PUF enrollement
 *  0b00..Allow PUF enroll operation
 *  0b01..Disable PUF enroll operation
 *  0b10..Disable PUF enroll operation
 *  0b11..Disable PUF enroll operation
 */
#define FLASH_CMPA_SECURE_BOOT_CFG_BLOCK_ENROLL(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_SECURE_BOOT_CFG_BLOCK_ENROLL_SHIFT)) & FLASH_CMPA_SECURE_BOOT_CFG_BLOCK_ENROLL_MASK)

#define FLASH_CMPA_SECURE_BOOT_CFG_DICE_INC_SEC_EPOCH_MASK (0xC000U)
#define FLASH_CMPA_SECURE_BOOT_CFG_DICE_INC_SEC_EPOCH_SHIFT (14U)
/*! DICE_INC_SEC_EPOCH - Include security EPOCH in DICE
 *  0b00..not included
 *  0b01..included
 *  0b10..included
 *  0b11..included
 */
#define FLASH_CMPA_SECURE_BOOT_CFG_DICE_INC_SEC_EPOCH(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_SECURE_BOOT_CFG_DICE_INC_SEC_EPOCH_SHIFT)) & FLASH_CMPA_SECURE_BOOT_CFG_DICE_INC_SEC_EPOCH_MASK)

#define FLASH_CMPA_SECURE_BOOT_CFG_SKIP_BOOT_SEED_MASK (0x30000U)
#define FLASH_CMPA_SECURE_BOOT_CFG_SKIP_BOOT_SEED_SHIFT (16U)
/*! SKIP_BOOT_SEED - Skip boot seed computation
 *  0b00..Enable BOOT_SEED
 *  0b01..Disable BOOT_SEED
 *  0b10..Disable BOOT_SEED
 *  0b11..Disable BOOT_SEED
 */
#define FLASH_CMPA_SECURE_BOOT_CFG_SKIP_BOOT_SEED(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_SECURE_BOOT_CFG_SKIP_BOOT_SEED_SHIFT)) & FLASH_CMPA_SECURE_BOOT_CFG_SKIP_BOOT_SEED_MASK)

#define FLASH_CMPA_SECURE_BOOT_CFG_BOOT_SEED_INC_NXP_CFG_MASK (0xC0000U)
#define FLASH_CMPA_SECURE_BOOT_CFG_BOOT_SEED_INC_NXP_CFG_SHIFT (18U)
/*! BOOT_SEED_INC_NXP_CFG - Include NXP area in BOOT SEED computation
 *  0b00..not included
 *  0b01..included
 *  0b10..included
 *  0b11..included
 */
#define FLASH_CMPA_SECURE_BOOT_CFG_BOOT_SEED_INC_NXP_CFG(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_SECURE_BOOT_CFG_BOOT_SEED_INC_NXP_CFG_SHIFT)) & FLASH_CMPA_SECURE_BOOT_CFG_BOOT_SEED_INC_NXP_CFG_MASK)

#define FLASH_CMPA_SECURE_BOOT_CFG_BOOT_SEED_CUST_CFG_MASK (0x300000U)
#define FLASH_CMPA_SECURE_BOOT_CFG_BOOT_SEED_CUST_CFG_SHIFT (20U)
/*! BOOT_SEED_CUST_CFG - Include CMPA area in BOOT SEED computation
 *  0b00..not included
 *  0b01..included
 *  0b10..included
 *  0b11..included
 */
#define FLASH_CMPA_SECURE_BOOT_CFG_BOOT_SEED_CUST_CFG(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_SECURE_BOOT_CFG_BOOT_SEED_CUST_CFG_SHIFT)) & FLASH_CMPA_SECURE_BOOT_CFG_BOOT_SEED_CUST_CFG_MASK)

#define FLASH_CMPA_SECURE_BOOT_CFG_BOOT_SEED_INC_EPOCH_MASK (0xC00000U)
#define FLASH_CMPA_SECURE_BOOT_CFG_BOOT_SEED_INC_EPOCH_SHIFT (22U)
/*! BOOT_SEED_INC_EPOCH - Include security epoch area in BOOT_SEED computation.
 *  0b00..not included
 *  0b01..included
 *  0b10..included
 *  0b11..included
 */
#define FLASH_CMPA_SECURE_BOOT_CFG_BOOT_SEED_INC_EPOCH(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_SECURE_BOOT_CFG_BOOT_SEED_INC_EPOCH_SHIFT)) & FLASH_CMPA_SECURE_BOOT_CFG_BOOT_SEED_INC_EPOCH_MASK)

#define FLASH_CMPA_SECURE_BOOT_CFG_SEC_BOOT_EN_MASK (0xC0000000U)
#define FLASH_CMPA_SECURE_BOOT_CFG_SEC_BOOT_EN_SHIFT (30U)
/*! SEC_BOOT_EN - Secure boot enable
 *  0b00..Plain image (internal flash with or without CRC)
 *  0b01..Boot signed images. (internal flash, RSA signed)
 *  0b10..Boot signed images. (internal flash, RSA signed)
 *  0b11..Boot signed images. (internal flash, RSA signed)
 */
#define FLASH_CMPA_SECURE_BOOT_CFG_SEC_BOOT_EN(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_SECURE_BOOT_CFG_SEC_BOOT_EN_SHIFT)) & FLASH_CMPA_SECURE_BOOT_CFG_SEC_BOOT_EN_MASK)
/*! @} */

/*! @name PRINCE_BASE_ADDR -  */
/*! @{ */

#define FLASH_CMPA_PRINCE_BASE_ADDR_ADDR0_PRG_MASK (0xFU)
#define FLASH_CMPA_PRINCE_BASE_ADDR_ADDR0_PRG_SHIFT (0U)
/*! ADDR0_PRG - Programmable portion of the base address of region 0 */
#define FLASH_CMPA_PRINCE_BASE_ADDR_ADDR0_PRG(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_PRINCE_BASE_ADDR_ADDR0_PRG_SHIFT)) & FLASH_CMPA_PRINCE_BASE_ADDR_ADDR0_PRG_MASK)

#define FLASH_CMPA_PRINCE_BASE_ADDR_ADDR1_PRG_MASK (0xF0U)
#define FLASH_CMPA_PRINCE_BASE_ADDR_ADDR1_PRG_SHIFT (4U)
/*! ADDR1_PRG - Programmable portion of the base address of region 1 */
#define FLASH_CMPA_PRINCE_BASE_ADDR_ADDR1_PRG(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_PRINCE_BASE_ADDR_ADDR1_PRG_SHIFT)) & FLASH_CMPA_PRINCE_BASE_ADDR_ADDR1_PRG_MASK)

#define FLASH_CMPA_PRINCE_BASE_ADDR_ADDR2_PRG_MASK (0xF00U)
#define FLASH_CMPA_PRINCE_BASE_ADDR_ADDR2_PRG_SHIFT (8U)
/*! ADDR2_PRG - Programmable portion of the base address of region 2 */
#define FLASH_CMPA_PRINCE_BASE_ADDR_ADDR2_PRG(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_PRINCE_BASE_ADDR_ADDR2_PRG_SHIFT)) & FLASH_CMPA_PRINCE_BASE_ADDR_ADDR2_PRG_MASK)

#define FLASH_CMPA_PRINCE_BASE_ADDR_LOCK_REG0_MASK (0xC0000U)
#define FLASH_CMPA_PRINCE_BASE_ADDR_LOCK_REG0_SHIFT (18U)
/*! LOCK_REG0 - Lock PRINCE region0 settings
 *  0b00..Region is not locked
 *  0b01..Region is locked
 *  0b10..Region is locked
 *  0b11..Region is locked
 */
#define FLASH_CMPA_PRINCE_BASE_ADDR_LOCK_REG0(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_PRINCE_BASE_ADDR_LOCK_REG0_SHIFT)) & FLASH_CMPA_PRINCE_BASE_ADDR_LOCK_REG0_MASK)

#define FLASH_CMPA_PRINCE_BASE_ADDR_LOCK_REG1_MASK (0x300000U)
#define FLASH_CMPA_PRINCE_BASE_ADDR_LOCK_REG1_SHIFT (20U)
/*! LOCK_REG1 - Lock PRINCE region1 settings
 *  0b00..Region is not locked
 *  0b01..Region is locked
 *  0b10..Region is locked
 *  0b11..Region is locked
 */
#define FLASH_CMPA_PRINCE_BASE_ADDR_LOCK_REG1(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_PRINCE_BASE_ADDR_LOCK_REG1_SHIFT)) & FLASH_CMPA_PRINCE_BASE_ADDR_LOCK_REG1_MASK)

#define FLASH_CMPA_PRINCE_BASE_ADDR_REG0_ERASE_CHECK_EN_MASK (0x3000000U)
#define FLASH_CMPA_PRINCE_BASE_ADDR_REG0_ERASE_CHECK_EN_SHIFT (24U)
/*! REG0_ERASE_CHECK_EN - For PRINCE region0 enable checking whether all encrypted pages are erased together
 *  0b00..Region is disabled
 *  0b01..Region is enabled
 *  0b10..Region is enabled
 *  0b11..Region is enabled
 */
#define FLASH_CMPA_PRINCE_BASE_ADDR_REG0_ERASE_CHECK_EN(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_PRINCE_BASE_ADDR_REG0_ERASE_CHECK_EN_SHIFT)) & FLASH_CMPA_PRINCE_BASE_ADDR_REG0_ERASE_CHECK_EN_MASK)

#define FLASH_CMPA_PRINCE_BASE_ADDR_REG1_ERASE_CHECK_EN_MASK (0xC000000U)
#define FLASH_CMPA_PRINCE_BASE_ADDR_REG1_ERASE_CHECK_EN_SHIFT (26U)
/*! REG1_ERASE_CHECK_EN - For PRINCE region1 enable checking whether all encrypted pages are erased together
 *  0b00..Region is disabled
 *  0b01..Region is enabled
 *  0b10..Region is enabled
 *  0b11..Region is enabled
 */
#define FLASH_CMPA_PRINCE_BASE_ADDR_REG1_ERASE_CHECK_EN(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_PRINCE_BASE_ADDR_REG1_ERASE_CHECK_EN_SHIFT)) & FLASH_CMPA_PRINCE_BASE_ADDR_REG1_ERASE_CHECK_EN_MASK)

#define FLASH_CMPA_PRINCE_BASE_ADDR_REG2_ERASE_CHECK_EN_MASK (0x30000000U)
#define FLASH_CMPA_PRINCE_BASE_ADDR_REG2_ERASE_CHECK_EN_SHIFT (28U)
/*! REG2_ERASE_CHECK_EN - For PRINCE region2 enable checking whether all encrypted pages are erased together
 *  0b00..Region is disabled
 *  0b01..Region is enabled
 *  0b10..Region is enabled
 *  0b11..Region is enabled
 */
#define FLASH_CMPA_PRINCE_BASE_ADDR_REG2_ERASE_CHECK_EN(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_PRINCE_BASE_ADDR_REG2_ERASE_CHECK_EN_SHIFT)) & FLASH_CMPA_PRINCE_BASE_ADDR_REG2_ERASE_CHECK_EN_MASK)
/*! @} */

/*! @name PRINCE_SR_0 - Region 0, sub-region enable */
/*! @{ */

#define FLASH_CMPA_PRINCE_SR_0_FIELD_MASK        (0xFFFFFFFFU)
#define FLASH_CMPA_PRINCE_SR_0_FIELD_SHIFT       (0U)
#define FLASH_CMPA_PRINCE_SR_0_FIELD(x)          (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_PRINCE_SR_0_FIELD_SHIFT)) & FLASH_CMPA_PRINCE_SR_0_FIELD_MASK)
/*! @} */

/*! @name PRINCE_SR_1 - Region 1, sub-region enable */
/*! @{ */

#define FLASH_CMPA_PRINCE_SR_1_FIELD_MASK        (0xFFFFFFFFU)
#define FLASH_CMPA_PRINCE_SR_1_FIELD_SHIFT       (0U)
#define FLASH_CMPA_PRINCE_SR_1_FIELD(x)          (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_PRINCE_SR_1_FIELD_SHIFT)) & FLASH_CMPA_PRINCE_SR_1_FIELD_MASK)
/*! @} */

/*! @name PRINCE_SR_2 - Region 2, sub-region enable */
/*! @{ */

#define FLASH_CMPA_PRINCE_SR_2_FIELD_MASK        (0xFFFFFFFFU)
#define FLASH_CMPA_PRINCE_SR_2_FIELD_SHIFT       (0U)
#define FLASH_CMPA_PRINCE_SR_2_FIELD(x)          (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_PRINCE_SR_2_FIELD_SHIFT)) & FLASH_CMPA_PRINCE_SR_2_FIELD_MASK)
/*! @} */

/*! @name XTAL_32KHZ_CAPABANK_TRIM - Xtal 32kHz capabank triming. */
/*! @{ */

#define FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_TRIM_VALID_MASK (0x1U)
#define FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_TRIM_VALID_SHIFT (0U)
/*! TRIM_VALID - XTAL 32kHz capa bank trimmings
 *  0b0..Capa Bank trimmings not valid. Default trimmings value are used
 *  0b1..Capa Bank trimmings valid
 */
#define FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_TRIM_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_TRIM_VALID_SHIFT)) & FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_TRIM_VALID_MASK)

#define FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_XTAL_LOAD_CAP_IEC_PF_X100_MASK (0x7FEU)
#define FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_XTAL_LOAD_CAP_IEC_PF_X100_SHIFT (1U)
/*! XTAL_LOAD_CAP_IEC_PF_X100 - Load capacitance, pF x 100. For example, 6pF becomes 600. */
#define FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_XTAL_LOAD_CAP_IEC_PF_X100(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_XTAL_LOAD_CAP_IEC_PF_X100_SHIFT)) & FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_XTAL_LOAD_CAP_IEC_PF_X100_MASK)

#define FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_PCB_XIN_PARA_CAP_PF_X100_MASK (0x1FF800U)
#define FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_PCB_XIN_PARA_CAP_PF_X100_SHIFT (11U)
/*! PCB_XIN_PARA_CAP_PF_X100 - PCB XIN parasitic capacitance, pF x 100. For example, 6pF becomes 600. */
#define FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_PCB_XIN_PARA_CAP_PF_X100(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_PCB_XIN_PARA_CAP_PF_X100_SHIFT)) & FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_PCB_XIN_PARA_CAP_PF_X100_MASK)

#define FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_PCB_XOUT_PARA_CAP_PF_X100_MASK (0x7FE00000U)
#define FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_PCB_XOUT_PARA_CAP_PF_X100_SHIFT (21U)
/*! PCB_XOUT_PARA_CAP_PF_X100 - PCB XOUT parasitic capacitance, pF x 100. For example, 6pF becomes 600. */
#define FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_PCB_XOUT_PARA_CAP_PF_X100(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_PCB_XOUT_PARA_CAP_PF_X100_SHIFT)) & FLASH_CMPA_XTAL_32KHZ_CAPABANK_TRIM_PCB_XOUT_PARA_CAP_PF_X100_MASK)
/*! @} */

/*! @name XTAL_16MHZ_CAPABANK_TRIM - Xtal 16MHz capabank triming. */
/*! @{ */

#define FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_TRIM_VALID_MASK (0x1U)
#define FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_TRIM_VALID_SHIFT (0U)
/*! TRIM_VALID - XTAL 16MHz capa bank trimmings
 *  0b0..Capa Bank trimmings not valid. Default trimmings value are used
 *  0b1..Capa Bank trimmings valid
 */
#define FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_TRIM_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_TRIM_VALID_SHIFT)) & FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_TRIM_VALID_MASK)

#define FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_XTAL_LOAD_CAP_IEC_PF_X100_MASK (0x7FEU)
#define FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_XTAL_LOAD_CAP_IEC_PF_X100_SHIFT (1U)
/*! XTAL_LOAD_CAP_IEC_PF_X100 - Load capacitance, pF x 100. For example, 6pF becomes 600. */
#define FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_XTAL_LOAD_CAP_IEC_PF_X100(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_XTAL_LOAD_CAP_IEC_PF_X100_SHIFT)) & FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_XTAL_LOAD_CAP_IEC_PF_X100_MASK)

#define FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_PCB_XIN_PARA_CAP_PF_X100_MASK (0x1FF800U)
#define FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_PCB_XIN_PARA_CAP_PF_X100_SHIFT (11U)
/*! PCB_XIN_PARA_CAP_PF_X100 - PCB XIN parasitic capacitance, pF x 100. For example, 6pF becomes 600. */
#define FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_PCB_XIN_PARA_CAP_PF_X100(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_PCB_XIN_PARA_CAP_PF_X100_SHIFT)) & FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_PCB_XIN_PARA_CAP_PF_X100_MASK)

#define FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_PCB_XOUT_PARA_CAP_PF_X100_MASK (0x7FE00000U)
#define FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_PCB_XOUT_PARA_CAP_PF_X100_SHIFT (21U)
/*! PCB_XOUT_PARA_CAP_PF_X100 - PCB XOUT parasitic capacitance, pF x 100. For example, 6pF becomes 600. */
#define FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_PCB_XOUT_PARA_CAP_PF_X100(x) (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_PCB_XOUT_PARA_CAP_PF_X100_SHIFT)) & FLASH_CMPA_XTAL_16MHZ_CAPABANK_TRIM_PCB_XOUT_PARA_CAP_PF_X100_MASK)
/*! @} */

/*! @name FLASH_REMAP_SIZE - This 32-bit register contains the size of the image to remap, in bytes. The 12 LSBs are ignored, so the size granularity is 4KB. */
/*! @{ */

#define FLASH_CMPA_FLASH_REMAP_SIZE_FIELD_MASK   (0xFFFFFFFFU)
#define FLASH_CMPA_FLASH_REMAP_SIZE_FIELD_SHIFT  (0U)
#define FLASH_CMPA_FLASH_REMAP_SIZE_FIELD(x)     (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_FLASH_REMAP_SIZE_FIELD_SHIFT)) & FLASH_CMPA_FLASH_REMAP_SIZE_FIELD_MASK)
/*! @} */

/*! @name FLASH_REMAP_OFFSET - This 32-bit register contains the offset by which the image is to be remapped. The 12 LSBs are ignored, so the remap granularity is 4KB. */
/*! @{ */

#define FLASH_CMPA_FLASH_REMAP_OFFSET_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_CMPA_FLASH_REMAP_OFFSET_FIELD_SHIFT (0U)
#define FLASH_CMPA_FLASH_REMAP_OFFSET_FIELD(x)   (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_FLASH_REMAP_OFFSET_FIELD_SHIFT)) & FLASH_CMPA_FLASH_REMAP_OFFSET_FIELD_MASK)
/*! @} */

/*! @name ROTKH - ROTKH0 for Root of Trust Keys Table hash[255:224]..ROTKH7 for Root of Trust Keys Table hash[31:0] */
/*! @{ */

#define FLASH_CMPA_ROTKH_FIELD_MASK              (0xFFFFFFFFU)
#define FLASH_CMPA_ROTKH_FIELD_SHIFT             (0U)
#define FLASH_CMPA_ROTKH_FIELD(x)                (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_ROTKH_FIELD_SHIFT)) & FLASH_CMPA_ROTKH_FIELD_MASK)
/*! @} */

/*! @name CUSTOMER_DEFINED - Customer Defined (Programable through ROM API) */
/*! @{ */

#define FLASH_CMPA_CUSTOMER_DEFINED_FIELD_MASK   (0xFFFFFFFFU)
#define FLASH_CMPA_CUSTOMER_DEFINED_FIELD_SHIFT  (0U)
#define FLASH_CMPA_CUSTOMER_DEFINED_FIELD(x)     (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_CUSTOMER_DEFINED_FIELD_SHIFT)) & FLASH_CMPA_CUSTOMER_DEFINED_FIELD_MASK)
/*! @} */

/*! @name SHA256_DIGEST - SHA256_DIGEST0 for DIGEST[31:0]..SHA256_DIGEST7 for DIGEST[255:224] */
/*! @{ */

#define FLASH_CMPA_SHA256_DIGEST_FIELD_MASK      (0xFFFFFFFFU)
#define FLASH_CMPA_SHA256_DIGEST_FIELD_SHIFT     (0U)
#define FLASH_CMPA_SHA256_DIGEST_FIELD(x)        (((uint32_t)(((uint32_t)(x)) << FLASH_CMPA_SHA256_DIGEST_FIELD_SHIFT)) & FLASH_CMPA_SHA256_DIGEST_FIELD_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group FLASH_CMPA_Register_Masks */


/*!
 * @}
 */ /* end of group FLASH_CMPA_Peripheral_Access_Layer */


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


#endif  /* FLASH_CMPA_H_ */


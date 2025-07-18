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
**         CMSIS Peripheral Access Layer for SYSCTL
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
 * @file SYSCTL.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for SYSCTL
 *
 * CMSIS Peripheral Access Layer for SYSCTL
 */

#if !defined(SYSCTL_H_)
#define SYSCTL_H_                                /**< Symbol preventing repeated inclusion */

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
   -- SYSCTL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYSCTL_Peripheral_Access_Layer SYSCTL Peripheral Access Layer
 * @{
 */

/** SYSCTL - Size of Registers Arrays */
#define SYSCTL_FCCTRLSEL_COUNT                    8u
#define SYSCTL_SHAREDCTRLSET_COUNT                2u

/** SYSCTL - Register Layout Typedef */
typedef struct {
  __IO uint32_t UPDATELCKOUT;                      /**< update lock out control, offset: 0x0 */
       uint8_t RESERVED_0[60];
  __IO uint32_t FCCTRLSEL[SYSCTL_FCCTRLSEL_COUNT]; /**< Selects the source for SCK going into Flexcomm 0..Selects the source for SCK going into Flexcomm 7, array offset: 0x40, array step: 0x4 */
       uint8_t RESERVED_1[32];
  __IO uint32_t SHAREDCTRLSET[SYSCTL_SHAREDCTRLSET_COUNT]; /**< Selects sources and data combinations for shared signal set 0...Selects sources and data combinations for shared signal set 1., array offset: 0x80, array step: 0x4 */
       uint8_t RESERVED_2[120];
  __I  uint32_t USB_HS_STATUS;                     /**< Status register for USB HS, offset: 0x100 */
       uint8_t RESERVED_3[124];
  __IO uint32_t CODE_GRAY_LSB;                     /**< CODE_GRAY LSB input Register, offset: 0x180 */
  __IO uint32_t CODE_GRAY_MSB;                     /**< CODE_GRAY MSB input Register, offset: 0x184 */
  __I  uint32_t CODE_BIN_LSB;                      /**< CODE_BIN LSB output Register, offset: 0x188 */
  __I  uint32_t CODE_BIN_MSB;                      /**< CODE_BIN MSB output Register, offset: 0x18C */
} SYSCTL_Type;

/* ----------------------------------------------------------------------------
   -- SYSCTL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYSCTL_Register_Masks SYSCTL Register Masks
 * @{
 */

/*! @name UPDATELCKOUT - update lock out control */
/*! @{ */

#define SYSCTL_UPDATELCKOUT_UPDATELCKOUT_MASK    (0x1U)
#define SYSCTL_UPDATELCKOUT_UPDATELCKOUT_SHIFT   (0U)
/*! UPDATELCKOUT - All Registers
 *  0b0..Normal Mode. Can be written to.
 *  0b1..Protected Mode. Cannot be written to.
 */
#define SYSCTL_UPDATELCKOUT_UPDATELCKOUT(x)      (((uint32_t)(((uint32_t)(x)) << SYSCTL_UPDATELCKOUT_UPDATELCKOUT_SHIFT)) & SYSCTL_UPDATELCKOUT_UPDATELCKOUT_MASK)
/*! @} */

/*! @name FCCTRLSEL - Selects the source for SCK going into Flexcomm 0..Selects the source for SCK going into Flexcomm 7 */
/*! @{ */

#define SYSCTL_FCCTRLSEL_SCKINSEL_MASK           (0x3U)
#define SYSCTL_FCCTRLSEL_SCKINSEL_SHIFT          (0U)
/*! SCKINSEL - Selects the source for SCK going into this Flexcomm.
 *  0b00..Selects the dedicated FCn_SCK function for this Flexcomm.
 *  0b01..SCK is taken from shared signal set 0 (defined by SHAREDCTRLSET0).
 *  0b10..SCK is taken from shared signal set 1 (defined by SHAREDCTRLSET1).
 *  0b11..Reserved.
 */
#define SYSCTL_FCCTRLSEL_SCKINSEL(x)             (((uint32_t)(((uint32_t)(x)) << SYSCTL_FCCTRLSEL_SCKINSEL_SHIFT)) & SYSCTL_FCCTRLSEL_SCKINSEL_MASK)

#define SYSCTL_FCCTRLSEL_WSINSEL_MASK            (0x300U)
#define SYSCTL_FCCTRLSEL_WSINSEL_SHIFT           (8U)
/*! WSINSEL - Selects the source for WS going into this Flexcomm.
 *  0b00..Selects the dedicated (FCn_TXD_SCL_MISO_WS) function for this Flexcomm.
 *  0b01..WS is taken from shared signal set 0 (defined by SHAREDCTRLSET0).
 *  0b10..WS is taken from shared signal set 1 (defined by SHAREDCTRLSET1).
 *  0b11..Reserved.
 */
#define SYSCTL_FCCTRLSEL_WSINSEL(x)              (((uint32_t)(((uint32_t)(x)) << SYSCTL_FCCTRLSEL_WSINSEL_SHIFT)) & SYSCTL_FCCTRLSEL_WSINSEL_MASK)

#define SYSCTL_FCCTRLSEL_DATAINSEL_MASK          (0x30000U)
#define SYSCTL_FCCTRLSEL_DATAINSEL_SHIFT         (16U)
/*! DATAINSEL - Selects the source for DATA input to this Flexcomm.
 *  0b00..Selects the dedicated FCn_RXD_SDA_MOSI_DATA input for this Flexcomm.
 *  0b01..Input data is taken from shared signal set 0 (defined by SHAREDCTRLSET0).
 *  0b10..Input data is taken from shared signal set 1 (defined by SHAREDCTRLSET1).
 *  0b11..Reserved.
 */
#define SYSCTL_FCCTRLSEL_DATAINSEL(x)            (((uint32_t)(((uint32_t)(x)) << SYSCTL_FCCTRLSEL_DATAINSEL_SHIFT)) & SYSCTL_FCCTRLSEL_DATAINSEL_MASK)

#define SYSCTL_FCCTRLSEL_DATAOUTSEL_MASK         (0x3000000U)
#define SYSCTL_FCCTRLSEL_DATAOUTSEL_SHIFT        (24U)
/*! DATAOUTSEL - Selects the source for DATA output from this Flexcomm.
 *  0b00..Selects the dedicated FCn_RXD_SDA_MOSI_DATA output from this Flexcomm.
 *  0b01..Output data is taken from shared signal set 0 (defined by SHAREDCTRLSET0).
 *  0b10..Output data is taken from shared signal set 1 (defined by SHAREDCTRLSET1).
 *  0b11..Reserved.
 */
#define SYSCTL_FCCTRLSEL_DATAOUTSEL(x)           (((uint32_t)(((uint32_t)(x)) << SYSCTL_FCCTRLSEL_DATAOUTSEL_SHIFT)) & SYSCTL_FCCTRLSEL_DATAOUTSEL_MASK)
/*! @} */

/*! @name SHAREDCTRLSET - Selects sources and data combinations for shared signal set 0...Selects sources and data combinations for shared signal set 1. */
/*! @{ */

#define SYSCTL_SHAREDCTRLSET_SHAREDSCKSEL_MASK   (0x7U)
#define SYSCTL_SHAREDCTRLSET_SHAREDSCKSEL_SHIFT  (0U)
/*! SHAREDSCKSEL - Selects the source for SCK of this shared signal set.
 *  0b000..SCK for this shared signal set comes from Flexcomm 0.
 *  0b001..SCK for this shared signal set comes from Flexcomm 1.
 *  0b010..SCK for this shared signal set comes from Flexcomm 2.
 *  0b011..SCK for this shared signal set comes from Flexcomm 3.
 *  0b100..SCK for this shared signal set comes from Flexcomm 4.
 *  0b101..SCK for this shared signal set comes from Flexcomm 5.
 *  0b110..SCK for this shared signal set comes from Flexcomm 6.
 *  0b111..SCK for this shared signal set comes from Flexcomm 7.
 */
#define SYSCTL_SHAREDCTRLSET_SHAREDSCKSEL(x)     (((uint32_t)(((uint32_t)(x)) << SYSCTL_SHAREDCTRLSET_SHAREDSCKSEL_SHIFT)) & SYSCTL_SHAREDCTRLSET_SHAREDSCKSEL_MASK)

#define SYSCTL_SHAREDCTRLSET_SHAREDWSSEL_MASK    (0x70U)
#define SYSCTL_SHAREDCTRLSET_SHAREDWSSEL_SHIFT   (4U)
/*! SHAREDWSSEL - Selects the source for WS of this shared signal set.
 *  0b000..WS for this shared signal set comes from Flexcomm 0.
 *  0b001..WS for this shared signal set comes from Flexcomm 1.
 *  0b010..WS for this shared signal set comes from Flexcomm 2.
 *  0b011..WS for this shared signal set comes from Flexcomm 3.
 *  0b100..WS for this shared signal set comes from Flexcomm 4.
 *  0b101..WS for this shared signal set comes from Flexcomm 5.
 *  0b110..WS for this shared signal set comes from Flexcomm 6.
 *  0b111..WS for this shared signal set comes from Flexcomm 7.
 */
#define SYSCTL_SHAREDCTRLSET_SHAREDWSSEL(x)      (((uint32_t)(((uint32_t)(x)) << SYSCTL_SHAREDCTRLSET_SHAREDWSSEL_SHIFT)) & SYSCTL_SHAREDCTRLSET_SHAREDWSSEL_MASK)

#define SYSCTL_SHAREDCTRLSET_SHAREDDATASEL_MASK  (0x700U)
#define SYSCTL_SHAREDCTRLSET_SHAREDDATASEL_SHIFT (8U)
/*! SHAREDDATASEL - Selects the source for DATA input for this shared signal set.
 *  0b000..DATA input for this shared signal set comes from Flexcomm 0.
 *  0b001..DATA input for this shared signal set comes from Flexcomm 1.
 *  0b010..DATA input for this shared signal set comes from Flexcomm 2.
 *  0b011..DATA input for this shared signal set comes from Flexcomm 3.
 *  0b100..DATA input for this shared signal set comes from Flexcomm 4.
 *  0b101..DATA input for this shared signal set comes from Flexcomm 5.
 *  0b110..DATA input for this shared signal set comes from Flexcomm 6.
 *  0b111..DATA input for this shared signal set comes from Flexcomm 7.
 */
#define SYSCTL_SHAREDCTRLSET_SHAREDDATASEL(x)    (((uint32_t)(((uint32_t)(x)) << SYSCTL_SHAREDCTRLSET_SHAREDDATASEL_SHIFT)) & SYSCTL_SHAREDCTRLSET_SHAREDDATASEL_MASK)

#define SYSCTL_SHAREDCTRLSET_FC0DATAOUTEN_MASK   (0x10000U)
#define SYSCTL_SHAREDCTRLSET_FC0DATAOUTEN_SHIFT  (16U)
/*! FC0DATAOUTEN - Controls FC0 contribution to SHAREDDATAOUT for this shared set.
 *  0b0..Data output from FC0 does not contribute to this shared set.
 *  0b1..Data output from FC0 does contribute to this shared set.
 */
#define SYSCTL_SHAREDCTRLSET_FC0DATAOUTEN(x)     (((uint32_t)(((uint32_t)(x)) << SYSCTL_SHAREDCTRLSET_FC0DATAOUTEN_SHIFT)) & SYSCTL_SHAREDCTRLSET_FC0DATAOUTEN_MASK)

#define SYSCTL_SHAREDCTRLSET_FC1DATAOUTEN_MASK   (0x20000U)
#define SYSCTL_SHAREDCTRLSET_FC1DATAOUTEN_SHIFT  (17U)
/*! FC1DATAOUTEN - Controls FC1 contribution to SHAREDDATAOUT for this shared set.
 *  0b0..Data output from FC1 does not contribute to this shared set.
 *  0b1..Data output from FC1 does contribute to this shared set.
 */
#define SYSCTL_SHAREDCTRLSET_FC1DATAOUTEN(x)     (((uint32_t)(((uint32_t)(x)) << SYSCTL_SHAREDCTRLSET_FC1DATAOUTEN_SHIFT)) & SYSCTL_SHAREDCTRLSET_FC1DATAOUTEN_MASK)

#define SYSCTL_SHAREDCTRLSET_FC2DATAOUTEN_MASK   (0x40000U)
#define SYSCTL_SHAREDCTRLSET_FC2DATAOUTEN_SHIFT  (18U)
/*! FC2DATAOUTEN - Controls FC2 contribution to SHAREDDATAOUT for this shared set.
 *  0b0..Data output from FC2 does not contribute to this shared set.
 *  0b1..Data output from FC2 does contribute to this shared set.
 */
#define SYSCTL_SHAREDCTRLSET_FC2DATAOUTEN(x)     (((uint32_t)(((uint32_t)(x)) << SYSCTL_SHAREDCTRLSET_FC2DATAOUTEN_SHIFT)) & SYSCTL_SHAREDCTRLSET_FC2DATAOUTEN_MASK)

#define SYSCTL_SHAREDCTRLSET_FC4DATAOUTEN_MASK   (0x100000U)
#define SYSCTL_SHAREDCTRLSET_FC4DATAOUTEN_SHIFT  (20U)
/*! FC4DATAOUTEN - Controls FC4 contribution to SHAREDDATAOUT for this shared set.
 *  0b0..Data output from FC4 does not contribute to this shared set.
 *  0b1..Data output from FC4 does contribute to this shared set.
 */
#define SYSCTL_SHAREDCTRLSET_FC4DATAOUTEN(x)     (((uint32_t)(((uint32_t)(x)) << SYSCTL_SHAREDCTRLSET_FC4DATAOUTEN_SHIFT)) & SYSCTL_SHAREDCTRLSET_FC4DATAOUTEN_MASK)

#define SYSCTL_SHAREDCTRLSET_FC5DATAOUTEN_MASK   (0x200000U)
#define SYSCTL_SHAREDCTRLSET_FC5DATAOUTEN_SHIFT  (21U)
/*! FC5DATAOUTEN - Controls FC5 contribution to SHAREDDATAOUT for this shared set.
 *  0b0..Data output from FC5 does not contribute to this shared set.
 *  0b1..Data output from FC5 does contribute to this shared set.
 */
#define SYSCTL_SHAREDCTRLSET_FC5DATAOUTEN(x)     (((uint32_t)(((uint32_t)(x)) << SYSCTL_SHAREDCTRLSET_FC5DATAOUTEN_SHIFT)) & SYSCTL_SHAREDCTRLSET_FC5DATAOUTEN_MASK)

#define SYSCTL_SHAREDCTRLSET_FC6DATAOUTEN_MASK   (0x400000U)
#define SYSCTL_SHAREDCTRLSET_FC6DATAOUTEN_SHIFT  (22U)
/*! FC6DATAOUTEN - Controls FC6 contribution to SHAREDDATAOUT for this shared set.
 *  0b0..Data output from FC6 does not contribute to this shared set.
 *  0b1..Data output from FC6 does contribute to this shared set.
 */
#define SYSCTL_SHAREDCTRLSET_FC6DATAOUTEN(x)     (((uint32_t)(((uint32_t)(x)) << SYSCTL_SHAREDCTRLSET_FC6DATAOUTEN_SHIFT)) & SYSCTL_SHAREDCTRLSET_FC6DATAOUTEN_MASK)

#define SYSCTL_SHAREDCTRLSET_FC7DATAOUTEN_MASK   (0x800000U)
#define SYSCTL_SHAREDCTRLSET_FC7DATAOUTEN_SHIFT  (23U)
/*! FC7DATAOUTEN - Controls FC7 contribution to SHAREDDATAOUT for this shared set.
 *  0b0..Data output from FC7 does not contribute to this shared set.
 *  0b1..Data output from FC7 does contribute to this shared set.
 */
#define SYSCTL_SHAREDCTRLSET_FC7DATAOUTEN(x)     (((uint32_t)(((uint32_t)(x)) << SYSCTL_SHAREDCTRLSET_FC7DATAOUTEN_SHIFT)) & SYSCTL_SHAREDCTRLSET_FC7DATAOUTEN_MASK)
/*! @} */

/*! @name USB_HS_STATUS - Status register for USB HS */
/*! @{ */

#define SYSCTL_USB_HS_STATUS_USBHS_3V_NOK_MASK   (0x1U)
#define SYSCTL_USB_HS_STATUS_USBHS_3V_NOK_SHIFT  (0U)
/*! USBHS_3V_NOK - USB_HS: Low voltage detection on 3.3V supply.
 *  0b0..3v3 supply is good.
 *  0b1..3v3 supply is too low.
 */
#define SYSCTL_USB_HS_STATUS_USBHS_3V_NOK(x)     (((uint32_t)(((uint32_t)(x)) << SYSCTL_USB_HS_STATUS_USBHS_3V_NOK_SHIFT)) & SYSCTL_USB_HS_STATUS_USBHS_3V_NOK_MASK)
/*! @} */

/*! @name CODE_GRAY_LSB - CODE_GRAY LSB input Register */
/*! @{ */

#define SYSCTL_CODE_GRAY_LSB_CODE_GRAY_LSB_MASK  (0xFFFFFFFFU)
#define SYSCTL_CODE_GRAY_LSB_CODE_GRAY_LSB_SHIFT (0U)
/*! CODE_GRAY_LSB - Gray code (42bits) to be converted back to binary */
#define SYSCTL_CODE_GRAY_LSB_CODE_GRAY_LSB(x)    (((uint32_t)(((uint32_t)(x)) << SYSCTL_CODE_GRAY_LSB_CODE_GRAY_LSB_SHIFT)) & SYSCTL_CODE_GRAY_LSB_CODE_GRAY_LSB_MASK)
/*! @} */

/*! @name CODE_GRAY_MSB - CODE_GRAY MSB input Register */
/*! @{ */

#define SYSCTL_CODE_GRAY_MSB_CODE_GRAY_MSB_MASK  (0x3FFU)
#define SYSCTL_CODE_GRAY_MSB_CODE_GRAY_MSB_SHIFT (0U)
/*! CODE_GRAY_MSB - Gray code (42bits) to be converted back to binary */
#define SYSCTL_CODE_GRAY_MSB_CODE_GRAY_MSB(x)    (((uint32_t)(((uint32_t)(x)) << SYSCTL_CODE_GRAY_MSB_CODE_GRAY_MSB_SHIFT)) & SYSCTL_CODE_GRAY_MSB_CODE_GRAY_MSB_MASK)
/*! @} */

/*! @name CODE_BIN_LSB - CODE_BIN LSB output Register */
/*! @{ */

#define SYSCTL_CODE_BIN_LSB_CODE_BIN_LSB_MASK    (0xFFFFFFFFU)
#define SYSCTL_CODE_BIN_LSB_CODE_BIN_LSB_SHIFT   (0U)
/*! CODE_BIN_LSB - Binary converted code (42bits) */
#define SYSCTL_CODE_BIN_LSB_CODE_BIN_LSB(x)      (((uint32_t)(((uint32_t)(x)) << SYSCTL_CODE_BIN_LSB_CODE_BIN_LSB_SHIFT)) & SYSCTL_CODE_BIN_LSB_CODE_BIN_LSB_MASK)
/*! @} */

/*! @name CODE_BIN_MSB - CODE_BIN MSB output Register */
/*! @{ */

#define SYSCTL_CODE_BIN_MSB_CODE_BIN_MSB_MASK    (0x3FFU)
#define SYSCTL_CODE_BIN_MSB_CODE_BIN_MSB_SHIFT   (0U)
/*! CODE_BIN_MSB - Binary converted code (42bits) */
#define SYSCTL_CODE_BIN_MSB_CODE_BIN_MSB(x)      (((uint32_t)(((uint32_t)(x)) << SYSCTL_CODE_BIN_MSB_CODE_BIN_MSB_SHIFT)) & SYSCTL_CODE_BIN_MSB_CODE_BIN_MSB_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SYSCTL_Register_Masks */


/*!
 * @}
 */ /* end of group SYSCTL_Peripheral_Access_Layer */


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


#endif  /* SYSCTL_H_ */


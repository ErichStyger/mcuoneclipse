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
**         CMSIS Peripheral Access Layer for USBHSD
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
 * @file USBHSD.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for USBHSD
 *
 * CMSIS Peripheral Access Layer for USBHSD
 */

#if !defined(USBHSD_H_)
#define USBHSD_H_                                /**< Symbol preventing repeated inclusion */

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
   -- USBHSD Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBHSD_Peripheral_Access_Layer USBHSD Peripheral Access Layer
 * @{
 */

/** USBHSD - Register Layout Typedef */
typedef struct {
  __IO uint32_t DEVCMDSTAT;                        /**< USB Device Command/Status register, offset: 0x0 */
  __I  uint32_t INFO;                              /**< USB Info register, offset: 0x4 */
  __IO uint32_t EPLISTSTART;                       /**< USB EP Command/Status List start address, offset: 0x8 */
  __IO uint32_t DATABUFSTART;                      /**< USB Data buffer start address, offset: 0xC */
  __IO uint32_t LPM;                               /**< USB Link Power Management register, offset: 0x10 */
  __IO uint32_t EPSKIP;                            /**< USB Endpoint skip, offset: 0x14 */
  __IO uint32_t EPINUSE;                           /**< USB Endpoint Buffer in use, offset: 0x18 */
  __IO uint32_t EPBUFCFG;                          /**< USB Endpoint Buffer Configuration register, offset: 0x1C */
  __IO uint32_t INTSTAT;                           /**< USB interrupt status register, offset: 0x20 */
  __IO uint32_t INTEN;                             /**< USB interrupt enable register, offset: 0x24 */
  __IO uint32_t INTSETSTAT;                        /**< USB set interrupt status register, offset: 0x28 */
       uint8_t RESERVED_0[8];
  __I  uint32_t EPTOGGLE;                          /**< USB Endpoint toggle register, offset: 0x34 */
} USBHSD_Type;

/* ----------------------------------------------------------------------------
   -- USBHSD Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBHSD_Register_Masks USBHSD Register Masks
 * @{
 */

/*! @name DEVCMDSTAT - USB Device Command/Status register */
/*! @{ */

#define USBHSD_DEVCMDSTAT_DEV_ADDR_MASK          (0x7FU)
#define USBHSD_DEVCMDSTAT_DEV_ADDR_SHIFT         (0U)
/*! DEV_ADDR - USB device address. */
#define USBHSD_DEVCMDSTAT_DEV_ADDR(x)            (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_DEV_ADDR_SHIFT)) & USBHSD_DEVCMDSTAT_DEV_ADDR_MASK)

#define USBHSD_DEVCMDSTAT_DEV_EN_MASK            (0x80U)
#define USBHSD_DEVCMDSTAT_DEV_EN_SHIFT           (7U)
/*! DEV_EN - USB device enable. */
#define USBHSD_DEVCMDSTAT_DEV_EN(x)              (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_DEV_EN_SHIFT)) & USBHSD_DEVCMDSTAT_DEV_EN_MASK)

#define USBHSD_DEVCMDSTAT_SETUP_MASK             (0x100U)
#define USBHSD_DEVCMDSTAT_SETUP_SHIFT            (8U)
/*! SETUP - SETUP token received. */
#define USBHSD_DEVCMDSTAT_SETUP(x)               (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_SETUP_SHIFT)) & USBHSD_DEVCMDSTAT_SETUP_MASK)

#define USBHSD_DEVCMDSTAT_FORCE_NEEDCLK_MASK     (0x200U)
#define USBHSD_DEVCMDSTAT_FORCE_NEEDCLK_SHIFT    (9U)
/*! FORCE_NEEDCLK - Forces the NEEDCLK output to always be on:. */
#define USBHSD_DEVCMDSTAT_FORCE_NEEDCLK(x)       (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_FORCE_NEEDCLK_SHIFT)) & USBHSD_DEVCMDSTAT_FORCE_NEEDCLK_MASK)

#define USBHSD_DEVCMDSTAT_LPM_SUP_MASK           (0x800U)
#define USBHSD_DEVCMDSTAT_LPM_SUP_SHIFT          (11U)
/*! LPM_SUP - LPM Supported:. */
#define USBHSD_DEVCMDSTAT_LPM_SUP(x)             (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_LPM_SUP_SHIFT)) & USBHSD_DEVCMDSTAT_LPM_SUP_MASK)

#define USBHSD_DEVCMDSTAT_INTONNAK_AO_MASK       (0x1000U)
#define USBHSD_DEVCMDSTAT_INTONNAK_AO_SHIFT      (12U)
/*! INTONNAK_AO - Interrupt on NAK for interrupt and bulk OUT EP:. */
#define USBHSD_DEVCMDSTAT_INTONNAK_AO(x)         (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_INTONNAK_AO_SHIFT)) & USBHSD_DEVCMDSTAT_INTONNAK_AO_MASK)

#define USBHSD_DEVCMDSTAT_INTONNAK_AI_MASK       (0x2000U)
#define USBHSD_DEVCMDSTAT_INTONNAK_AI_SHIFT      (13U)
/*! INTONNAK_AI - Interrupt on NAK for interrupt and bulk IN EP:. */
#define USBHSD_DEVCMDSTAT_INTONNAK_AI(x)         (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_INTONNAK_AI_SHIFT)) & USBHSD_DEVCMDSTAT_INTONNAK_AI_MASK)

#define USBHSD_DEVCMDSTAT_INTONNAK_CO_MASK       (0x4000U)
#define USBHSD_DEVCMDSTAT_INTONNAK_CO_SHIFT      (14U)
/*! INTONNAK_CO - Interrupt on NAK for control OUT EP:. */
#define USBHSD_DEVCMDSTAT_INTONNAK_CO(x)         (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_INTONNAK_CO_SHIFT)) & USBHSD_DEVCMDSTAT_INTONNAK_CO_MASK)

#define USBHSD_DEVCMDSTAT_INTONNAK_CI_MASK       (0x8000U)
#define USBHSD_DEVCMDSTAT_INTONNAK_CI_SHIFT      (15U)
/*! INTONNAK_CI - Interrupt on NAK for control IN EP:. */
#define USBHSD_DEVCMDSTAT_INTONNAK_CI(x)         (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_INTONNAK_CI_SHIFT)) & USBHSD_DEVCMDSTAT_INTONNAK_CI_MASK)

#define USBHSD_DEVCMDSTAT_DCON_MASK              (0x10000U)
#define USBHSD_DEVCMDSTAT_DCON_SHIFT             (16U)
/*! DCON - Device status - connect. */
#define USBHSD_DEVCMDSTAT_DCON(x)                (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_DCON_SHIFT)) & USBHSD_DEVCMDSTAT_DCON_MASK)

#define USBHSD_DEVCMDSTAT_DSUS_MASK              (0x20000U)
#define USBHSD_DEVCMDSTAT_DSUS_SHIFT             (17U)
/*! DSUS - Device status - suspend. */
#define USBHSD_DEVCMDSTAT_DSUS(x)                (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_DSUS_SHIFT)) & USBHSD_DEVCMDSTAT_DSUS_MASK)

#define USBHSD_DEVCMDSTAT_LPM_SUS_MASK           (0x80000U)
#define USBHSD_DEVCMDSTAT_LPM_SUS_SHIFT          (19U)
/*! LPM_SUS - Device status - LPM Suspend. */
#define USBHSD_DEVCMDSTAT_LPM_SUS(x)             (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_LPM_SUS_SHIFT)) & USBHSD_DEVCMDSTAT_LPM_SUS_MASK)

#define USBHSD_DEVCMDSTAT_LPM_REWP_MASK          (0x100000U)
#define USBHSD_DEVCMDSTAT_LPM_REWP_SHIFT         (20U)
/*! LPM_REWP - LPM Remote Wake-up Enabled by USB host. */
#define USBHSD_DEVCMDSTAT_LPM_REWP(x)            (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_LPM_REWP_SHIFT)) & USBHSD_DEVCMDSTAT_LPM_REWP_MASK)

#define USBHSD_DEVCMDSTAT_Speed_MASK             (0xC00000U)
#define USBHSD_DEVCMDSTAT_Speed_SHIFT            (22U)
/*! Speed - This field indicates the speed at which the device operates: 00b: reserved 01b:
 *    full-speed 10b: high-speed 11b: super-speed (reserved for future use).
 */
#define USBHSD_DEVCMDSTAT_Speed(x)               (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_Speed_SHIFT)) & USBHSD_DEVCMDSTAT_Speed_MASK)

#define USBHSD_DEVCMDSTAT_DCON_C_MASK            (0x1000000U)
#define USBHSD_DEVCMDSTAT_DCON_C_SHIFT           (24U)
/*! DCON_C - Device status - connect change. */
#define USBHSD_DEVCMDSTAT_DCON_C(x)              (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_DCON_C_SHIFT)) & USBHSD_DEVCMDSTAT_DCON_C_MASK)

#define USBHSD_DEVCMDSTAT_DSUS_C_MASK            (0x2000000U)
#define USBHSD_DEVCMDSTAT_DSUS_C_SHIFT           (25U)
/*! DSUS_C - Device status - suspend change. */
#define USBHSD_DEVCMDSTAT_DSUS_C(x)              (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_DSUS_C_SHIFT)) & USBHSD_DEVCMDSTAT_DSUS_C_MASK)

#define USBHSD_DEVCMDSTAT_DRES_C_MASK            (0x4000000U)
#define USBHSD_DEVCMDSTAT_DRES_C_SHIFT           (26U)
/*! DRES_C - Device status - reset change. */
#define USBHSD_DEVCMDSTAT_DRES_C(x)              (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_DRES_C_SHIFT)) & USBHSD_DEVCMDSTAT_DRES_C_MASK)

#define USBHSD_DEVCMDSTAT_VBUS_DEBOUNCED_MASK    (0x10000000U)
#define USBHSD_DEVCMDSTAT_VBUS_DEBOUNCED_SHIFT   (28U)
/*! VBUS_DEBOUNCED - This bit indicates if VBUS is detected or not. */
#define USBHSD_DEVCMDSTAT_VBUS_DEBOUNCED(x)      (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_VBUS_DEBOUNCED_SHIFT)) & USBHSD_DEVCMDSTAT_VBUS_DEBOUNCED_MASK)

#define USBHSD_DEVCMDSTAT_PHY_TEST_MODE_MASK     (0xE0000000U)
#define USBHSD_DEVCMDSTAT_PHY_TEST_MODE_SHIFT    (29U)
/*! PHY_TEST_MODE - This field is written by firmware to put the PHY into a test mode as defined by the USB2.0 specification.
 *  0b000..Test mode disabled.
 *  0b001..Test_J.
 *  0b010..Test_K.
 *  0b011..Test_SE0_NAK.
 *  0b100..Test_Packet.
 *  0b101..Test_Force_Enable.
 */
#define USBHSD_DEVCMDSTAT_PHY_TEST_MODE(x)       (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_PHY_TEST_MODE_SHIFT)) & USBHSD_DEVCMDSTAT_PHY_TEST_MODE_MASK)
/*! @} */

/*! @name INFO - USB Info register */
/*! @{ */

#define USBHSD_INFO_FRAME_NR_MASK                (0x7FFU)
#define USBHSD_INFO_FRAME_NR_SHIFT               (0U)
/*! FRAME_NR - Frame number. */
#define USBHSD_INFO_FRAME_NR(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSD_INFO_FRAME_NR_SHIFT)) & USBHSD_INFO_FRAME_NR_MASK)

#define USBHSD_INFO_ERR_CODE_MASK                (0x7800U)
#define USBHSD_INFO_ERR_CODE_SHIFT               (11U)
/*! ERR_CODE - The error code which last occurred:. */
#define USBHSD_INFO_ERR_CODE(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSD_INFO_ERR_CODE_SHIFT)) & USBHSD_INFO_ERR_CODE_MASK)

#define USBHSD_INFO_MINREV_MASK                  (0xFF0000U)
#define USBHSD_INFO_MINREV_SHIFT                 (16U)
/*! MINREV - Minor revision. */
#define USBHSD_INFO_MINREV(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSD_INFO_MINREV_SHIFT)) & USBHSD_INFO_MINREV_MASK)

#define USBHSD_INFO_MAJREV_MASK                  (0xFF000000U)
#define USBHSD_INFO_MAJREV_SHIFT                 (24U)
/*! MAJREV - Major revision. */
#define USBHSD_INFO_MAJREV(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSD_INFO_MAJREV_SHIFT)) & USBHSD_INFO_MAJREV_MASK)
/*! @} */

/*! @name EPLISTSTART - USB EP Command/Status List start address */
/*! @{ */

#define USBHSD_EPLISTSTART_EP_LIST_PRG_MASK      (0xFFF00U)
#define USBHSD_EPLISTSTART_EP_LIST_PRG_SHIFT     (8U)
/*! EP_LIST_PRG - Programmable portion of the USB EP Command/Status List address. */
#define USBHSD_EPLISTSTART_EP_LIST_PRG(x)        (((uint32_t)(((uint32_t)(x)) << USBHSD_EPLISTSTART_EP_LIST_PRG_SHIFT)) & USBHSD_EPLISTSTART_EP_LIST_PRG_MASK)

#define USBHSD_EPLISTSTART_EP_LIST_FIXED_MASK    (0xFFF00000U)
#define USBHSD_EPLISTSTART_EP_LIST_FIXED_SHIFT   (20U)
/*! EP_LIST_FIXED - Fixed portion of USB EP Command/Status List address. */
#define USBHSD_EPLISTSTART_EP_LIST_FIXED(x)      (((uint32_t)(((uint32_t)(x)) << USBHSD_EPLISTSTART_EP_LIST_FIXED_SHIFT)) & USBHSD_EPLISTSTART_EP_LIST_FIXED_MASK)
/*! @} */

/*! @name DATABUFSTART - USB Data buffer start address */
/*! @{ */

#define USBHSD_DATABUFSTART_DA_BUF_MASK          (0xFFFFFFFFU)
#define USBHSD_DATABUFSTART_DA_BUF_SHIFT         (0U)
/*! DA_BUF - Start address of the memory page where all endpoint data buffers are located. */
#define USBHSD_DATABUFSTART_DA_BUF(x)            (((uint32_t)(((uint32_t)(x)) << USBHSD_DATABUFSTART_DA_BUF_SHIFT)) & USBHSD_DATABUFSTART_DA_BUF_MASK)
/*! @} */

/*! @name LPM - USB Link Power Management register */
/*! @{ */

#define USBHSD_LPM_HIRD_HW_MASK                  (0xFU)
#define USBHSD_LPM_HIRD_HW_SHIFT                 (0U)
/*! HIRD_HW - Host Initiated Resume Duration - HW. */
#define USBHSD_LPM_HIRD_HW(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSD_LPM_HIRD_HW_SHIFT)) & USBHSD_LPM_HIRD_HW_MASK)

#define USBHSD_LPM_HIRD_SW_MASK                  (0xF0U)
#define USBHSD_LPM_HIRD_SW_SHIFT                 (4U)
/*! HIRD_SW - Host Initiated Resume Duration - SW. */
#define USBHSD_LPM_HIRD_SW(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSD_LPM_HIRD_SW_SHIFT)) & USBHSD_LPM_HIRD_SW_MASK)

#define USBHSD_LPM_DATA_PENDING_MASK             (0x100U)
#define USBHSD_LPM_DATA_PENDING_SHIFT            (8U)
/*! DATA_PENDING - As long as this bit is set to one and LPM supported bit is set to one, HW will
 *    return a NYET handshake on every LPM token it receives.
 */
#define USBHSD_LPM_DATA_PENDING(x)               (((uint32_t)(((uint32_t)(x)) << USBHSD_LPM_DATA_PENDING_SHIFT)) & USBHSD_LPM_DATA_PENDING_MASK)
/*! @} */

/*! @name EPSKIP - USB Endpoint skip */
/*! @{ */

#define USBHSD_EPSKIP_SKIP_MASK                  (0xFFFU)
#define USBHSD_EPSKIP_SKIP_SHIFT                 (0U)
/*! SKIP - Endpoint skip: Writing 1 to one of these bits, will indicate to HW that it must
 *    deactivate the buffer assigned to this endpoint and return control back to software.
 */
#define USBHSD_EPSKIP_SKIP(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSD_EPSKIP_SKIP_SHIFT)) & USBHSD_EPSKIP_SKIP_MASK)
/*! @} */

/*! @name EPINUSE - USB Endpoint Buffer in use */
/*! @{ */

#define USBHSD_EPINUSE_BUF_MASK                  (0xFFCU)
#define USBHSD_EPINUSE_BUF_SHIFT                 (2U)
/*! BUF - Buffer in use: This register has one bit per physical endpoint. */
#define USBHSD_EPINUSE_BUF(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSD_EPINUSE_BUF_SHIFT)) & USBHSD_EPINUSE_BUF_MASK)
/*! @} */

/*! @name EPBUFCFG - USB Endpoint Buffer Configuration register */
/*! @{ */

#define USBHSD_EPBUFCFG_BUF_SB_MASK              (0xFFCU)
#define USBHSD_EPBUFCFG_BUF_SB_SHIFT             (2U)
/*! BUF_SB - Buffer usage: This register has one bit per physical endpoint. */
#define USBHSD_EPBUFCFG_BUF_SB(x)                (((uint32_t)(((uint32_t)(x)) << USBHSD_EPBUFCFG_BUF_SB_SHIFT)) & USBHSD_EPBUFCFG_BUF_SB_MASK)
/*! @} */

/*! @name INTSTAT - USB interrupt status register */
/*! @{ */

#define USBHSD_INTSTAT_EP0OUT_MASK               (0x1U)
#define USBHSD_INTSTAT_EP0OUT_SHIFT              (0U)
/*! EP0OUT - Interrupt status register bit for the Control EP0 OUT direction. */
#define USBHSD_INTSTAT_EP0OUT(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP0OUT_SHIFT)) & USBHSD_INTSTAT_EP0OUT_MASK)

#define USBHSD_INTSTAT_EP0IN_MASK                (0x2U)
#define USBHSD_INTSTAT_EP0IN_SHIFT               (1U)
/*! EP0IN - Interrupt status register bit for the Control EP0 IN direction. */
#define USBHSD_INTSTAT_EP0IN(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP0IN_SHIFT)) & USBHSD_INTSTAT_EP0IN_MASK)

#define USBHSD_INTSTAT_EP1OUT_MASK               (0x4U)
#define USBHSD_INTSTAT_EP1OUT_SHIFT              (2U)
/*! EP1OUT - Interrupt status register bit for the EP1 OUT direction. */
#define USBHSD_INTSTAT_EP1OUT(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP1OUT_SHIFT)) & USBHSD_INTSTAT_EP1OUT_MASK)

#define USBHSD_INTSTAT_EP1IN_MASK                (0x8U)
#define USBHSD_INTSTAT_EP1IN_SHIFT               (3U)
/*! EP1IN - Interrupt status register bit for the EP1 IN direction. */
#define USBHSD_INTSTAT_EP1IN(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP1IN_SHIFT)) & USBHSD_INTSTAT_EP1IN_MASK)

#define USBHSD_INTSTAT_EP2OUT_MASK               (0x10U)
#define USBHSD_INTSTAT_EP2OUT_SHIFT              (4U)
/*! EP2OUT - Interrupt status register bit for the EP2 OUT direction. */
#define USBHSD_INTSTAT_EP2OUT(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP2OUT_SHIFT)) & USBHSD_INTSTAT_EP2OUT_MASK)

#define USBHSD_INTSTAT_EP2IN_MASK                (0x20U)
#define USBHSD_INTSTAT_EP2IN_SHIFT               (5U)
/*! EP2IN - Interrupt status register bit for the EP2 IN direction. */
#define USBHSD_INTSTAT_EP2IN(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP2IN_SHIFT)) & USBHSD_INTSTAT_EP2IN_MASK)

#define USBHSD_INTSTAT_EP3OUT_MASK               (0x40U)
#define USBHSD_INTSTAT_EP3OUT_SHIFT              (6U)
/*! EP3OUT - Interrupt status register bit for the EP3 OUT direction. */
#define USBHSD_INTSTAT_EP3OUT(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP3OUT_SHIFT)) & USBHSD_INTSTAT_EP3OUT_MASK)

#define USBHSD_INTSTAT_EP3IN_MASK                (0x80U)
#define USBHSD_INTSTAT_EP3IN_SHIFT               (7U)
/*! EP3IN - Interrupt status register bit for the EP3 IN direction. */
#define USBHSD_INTSTAT_EP3IN(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP3IN_SHIFT)) & USBHSD_INTSTAT_EP3IN_MASK)

#define USBHSD_INTSTAT_EP4OUT_MASK               (0x100U)
#define USBHSD_INTSTAT_EP4OUT_SHIFT              (8U)
/*! EP4OUT - Interrupt status register bit for the EP4 OUT direction. */
#define USBHSD_INTSTAT_EP4OUT(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP4OUT_SHIFT)) & USBHSD_INTSTAT_EP4OUT_MASK)

#define USBHSD_INTSTAT_EP4IN_MASK                (0x200U)
#define USBHSD_INTSTAT_EP4IN_SHIFT               (9U)
/*! EP4IN - Interrupt status register bit for the EP4 IN direction. */
#define USBHSD_INTSTAT_EP4IN(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP4IN_SHIFT)) & USBHSD_INTSTAT_EP4IN_MASK)

#define USBHSD_INTSTAT_EP5OUT_MASK               (0x400U)
#define USBHSD_INTSTAT_EP5OUT_SHIFT              (10U)
/*! EP5OUT - Interrupt status register bit for the EP5 OUT direction. */
#define USBHSD_INTSTAT_EP5OUT(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP5OUT_SHIFT)) & USBHSD_INTSTAT_EP5OUT_MASK)

#define USBHSD_INTSTAT_EP5IN_MASK                (0x800U)
#define USBHSD_INTSTAT_EP5IN_SHIFT               (11U)
/*! EP5IN - Interrupt status register bit for the EP5 IN direction. */
#define USBHSD_INTSTAT_EP5IN(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP5IN_SHIFT)) & USBHSD_INTSTAT_EP5IN_MASK)

#define USBHSD_INTSTAT_FRAME_INT_MASK            (0x40000000U)
#define USBHSD_INTSTAT_FRAME_INT_SHIFT           (30U)
/*! FRAME_INT - Frame interrupt. */
#define USBHSD_INTSTAT_FRAME_INT(x)              (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_FRAME_INT_SHIFT)) & USBHSD_INTSTAT_FRAME_INT_MASK)

#define USBHSD_INTSTAT_DEV_INT_MASK              (0x80000000U)
#define USBHSD_INTSTAT_DEV_INT_SHIFT             (31U)
/*! DEV_INT - Device status interrupt. */
#define USBHSD_INTSTAT_DEV_INT(x)                (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_DEV_INT_SHIFT)) & USBHSD_INTSTAT_DEV_INT_MASK)
/*! @} */

/*! @name INTEN - USB interrupt enable register */
/*! @{ */

#define USBHSD_INTEN_EP_INT_EN_MASK              (0xFFFU)
#define USBHSD_INTEN_EP_INT_EN_SHIFT             (0U)
/*! EP_INT_EN - If this bit is set and the corresponding USB interrupt status bit is set, a HW
 *    interrupt is generated on the interrupt line.
 */
#define USBHSD_INTEN_EP_INT_EN(x)                (((uint32_t)(((uint32_t)(x)) << USBHSD_INTEN_EP_INT_EN_SHIFT)) & USBHSD_INTEN_EP_INT_EN_MASK)

#define USBHSD_INTEN_FRAME_INT_EN_MASK           (0x40000000U)
#define USBHSD_INTEN_FRAME_INT_EN_SHIFT          (30U)
/*! FRAME_INT_EN - If this bit is set and the corresponding USB interrupt status bit is set, a HW
 *    interrupt is generated on the interrupt line.
 */
#define USBHSD_INTEN_FRAME_INT_EN(x)             (((uint32_t)(((uint32_t)(x)) << USBHSD_INTEN_FRAME_INT_EN_SHIFT)) & USBHSD_INTEN_FRAME_INT_EN_MASK)

#define USBHSD_INTEN_DEV_INT_EN_MASK             (0x80000000U)
#define USBHSD_INTEN_DEV_INT_EN_SHIFT            (31U)
/*! DEV_INT_EN - If this bit is set and the corresponding USB interrupt status bit is set, a HW
 *    interrupt is generated on the interrupt line.
 */
#define USBHSD_INTEN_DEV_INT_EN(x)               (((uint32_t)(((uint32_t)(x)) << USBHSD_INTEN_DEV_INT_EN_SHIFT)) & USBHSD_INTEN_DEV_INT_EN_MASK)
/*! @} */

/*! @name INTSETSTAT - USB set interrupt status register */
/*! @{ */

#define USBHSD_INTSETSTAT_EP_SET_INT_MASK        (0xFFFU)
#define USBHSD_INTSETSTAT_EP_SET_INT_SHIFT       (0U)
/*! EP_SET_INT - If software writes a one to one of these bits, the corresponding USB interrupt status bit is set. */
#define USBHSD_INTSETSTAT_EP_SET_INT(x)          (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSETSTAT_EP_SET_INT_SHIFT)) & USBHSD_INTSETSTAT_EP_SET_INT_MASK)

#define USBHSD_INTSETSTAT_FRAME_SET_INT_MASK     (0x40000000U)
#define USBHSD_INTSETSTAT_FRAME_SET_INT_SHIFT    (30U)
/*! FRAME_SET_INT - If software writes a one to one of these bits, the corresponding USB interrupt status bit is set. */
#define USBHSD_INTSETSTAT_FRAME_SET_INT(x)       (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSETSTAT_FRAME_SET_INT_SHIFT)) & USBHSD_INTSETSTAT_FRAME_SET_INT_MASK)

#define USBHSD_INTSETSTAT_DEV_SET_INT_MASK       (0x80000000U)
#define USBHSD_INTSETSTAT_DEV_SET_INT_SHIFT      (31U)
/*! DEV_SET_INT - If software writes a one to one of these bits, the corresponding USB interrupt status bit is set. */
#define USBHSD_INTSETSTAT_DEV_SET_INT(x)         (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSETSTAT_DEV_SET_INT_SHIFT)) & USBHSD_INTSETSTAT_DEV_SET_INT_MASK)
/*! @} */

/*! @name EPTOGGLE - USB Endpoint toggle register */
/*! @{ */

#define USBHSD_EPTOGGLE_TOGGLE_MASK              (0x3FFFFFFFU)
#define USBHSD_EPTOGGLE_TOGGLE_SHIFT             (0U)
/*! TOGGLE - Endpoint data toggle: This field indicates the current value of the data toggle for the corresponding endpoint. */
#define USBHSD_EPTOGGLE_TOGGLE(x)                (((uint32_t)(((uint32_t)(x)) << USBHSD_EPTOGGLE_TOGGLE_SHIFT)) & USBHSD_EPTOGGLE_TOGGLE_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group USBHSD_Register_Masks */


/*!
 * @}
 */ /* end of group USBHSD_Peripheral_Access_Layer */


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


#endif  /* USBHSD_H_ */


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
**         CMSIS Peripheral Access Layer for USBPHY
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
 * @file USBPHY.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for USBPHY
 *
 * CMSIS Peripheral Access Layer for USBPHY
 */

#if !defined(USBPHY_H_)
#define USBPHY_H_                                /**< Symbol preventing repeated inclusion */

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
   -- USBPHY Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBPHY_Peripheral_Access_Layer USBPHY Peripheral Access Layer
 * @{
 */

/** USBPHY - Register Layout Typedef */
typedef struct {
  __IO uint32_t PWD;                               /**< USB PHY Power-Down Register, offset: 0x0 */
  __IO uint32_t PWD_SET;                           /**< USB PHY Power-Down Register, offset: 0x4 */
  __IO uint32_t PWD_CLR;                           /**< USB PHY Power-Down Register, offset: 0x8 */
  __IO uint32_t PWD_TOG;                           /**< USB PHY Power-Down Register, offset: 0xC */
  __IO uint32_t TX;                                /**< USB PHY Transmitter Control Register, offset: 0x10 */
  __IO uint32_t TX_SET;                            /**< USB PHY Transmitter Control Register, offset: 0x14 */
  __IO uint32_t TX_CLR;                            /**< USB PHY Transmitter Control Register, offset: 0x18 */
  __IO uint32_t TX_TOG;                            /**< USB PHY Transmitter Control Register, offset: 0x1C */
  __IO uint32_t RX;                                /**< USB PHY Receiver Control Register, offset: 0x20 */
  __IO uint32_t RX_SET;                            /**< USB PHY Receiver Control Register, offset: 0x24 */
  __IO uint32_t RX_CLR;                            /**< USB PHY Receiver Control Register, offset: 0x28 */
  __IO uint32_t RX_TOG;                            /**< USB PHY Receiver Control Register, offset: 0x2C */
  __IO uint32_t CTRL;                              /**< USB PHY General Control Register, offset: 0x30 */
  __IO uint32_t CTRL_SET;                          /**< USB PHY General Control Register, offset: 0x34 */
  __IO uint32_t CTRL_CLR;                          /**< USB PHY General Control Register, offset: 0x38 */
  __IO uint32_t CTRL_TOG;                          /**< USB PHY General Control Register, offset: 0x3C */
  __I  uint32_t STATUS;                            /**< USB PHY Status Register, offset: 0x40 */
       uint8_t RESERVED_0[92];
  __IO uint32_t PLL_SIC;                           /**< USB PHY PLL Control/Status Register, offset: 0xA0 */
  __IO uint32_t PLL_SIC_SET;                       /**< USB PHY PLL Control/Status Register, offset: 0xA4 */
  __IO uint32_t PLL_SIC_CLR;                       /**< USB PHY PLL Control/Status Register, offset: 0xA8 */
  __IO uint32_t PLL_SIC_TOG;                       /**< USB PHY PLL Control/Status Register, offset: 0xAC */
       uint8_t RESERVED_1[16];
  __IO uint32_t USB1_VBUS_DETECT;                  /**< USB PHY VBUS Detect Control Register, offset: 0xC0 */
  __IO uint32_t USB1_VBUS_DETECT_SET;              /**< USB PHY VBUS Detect Control Register, offset: 0xC4 */
  __IO uint32_t USB1_VBUS_DETECT_CLR;              /**< USB PHY VBUS Detect Control Register, offset: 0xC8 */
  __IO uint32_t USB1_VBUS_DETECT_TOG;              /**< USB PHY VBUS Detect Control Register, offset: 0xCC */
  __I  uint32_t USB1_VBUS_DET_STAT;                /**< USB PHY VBUS Detector Status Register, offset: 0xD0 */
       uint8_t RESERVED_2[44];
  __IO uint32_t ANACTRLr;                          /**< USB PHY Analog Control Register, offset: 0x100, 'r' suffix has been added to avoid a clash with peripheral base pointer macro 'ANACTRL' */
  __IO uint32_t ANACTRL_SET;                       /**< USB PHY Analog Control Register, offset: 0x104 */
  __IO uint32_t ANACTRL_CLR;                       /**< USB PHY Analog Control Register, offset: 0x108 */
  __IO uint32_t ANACTRL_TOG;                       /**< USB PHY Analog Control Register, offset: 0x10C */
} USBPHY_Type;

/* ----------------------------------------------------------------------------
   -- USBPHY Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBPHY_Register_Masks USBPHY Register Masks
 * @{
 */

/*! @name PWD - USB PHY Power-Down Register */
/*! @{ */

#define USBPHY_PWD_TXPWDFS_MASK                  (0x400U)
#define USBPHY_PWD_TXPWDFS_SHIFT                 (10U)
/*! TXPWDFS
 *  0b0..Normal operation.
 *  0b1..Power-down the USB full-speed drivers. This turns off the current starvation sources and puts the
 */
#define USBPHY_PWD_TXPWDFS(x)                    (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TXPWDFS_SHIFT)) & USBPHY_PWD_TXPWDFS_MASK)

#define USBPHY_PWD_TXPWDIBIAS_MASK               (0x800U)
#define USBPHY_PWD_TXPWDIBIAS_SHIFT              (11U)
/*! TXPWDIBIAS
 *  0b0..Normal operation.
 *  0b1..Power-down the USB PHY current bias block for the transmitter. This bit should be set only when the
 */
#define USBPHY_PWD_TXPWDIBIAS(x)                 (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TXPWDIBIAS_SHIFT)) & USBPHY_PWD_TXPWDIBIAS_MASK)

#define USBPHY_PWD_TXPWDV2I_MASK                 (0x1000U)
#define USBPHY_PWD_TXPWDV2I_SHIFT                (12U)
/*! TXPWDV2I
 *  0b0..Normal operation.
 *  0b1..Power-down the USB PHY transmit V-to-I converter and the current mirror
 */
#define USBPHY_PWD_TXPWDV2I(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TXPWDV2I_SHIFT)) & USBPHY_PWD_TXPWDV2I_MASK)

#define USBPHY_PWD_RXPWDENV_MASK                 (0x20000U)
#define USBPHY_PWD_RXPWDENV_SHIFT                (17U)
/*! RXPWDENV
 *  0b0..Normal operation.
 *  0b1..Power-down the USB high-speed receiver envelope detector (squelch signal)
 */
#define USBPHY_PWD_RXPWDENV(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_RXPWDENV_SHIFT)) & USBPHY_PWD_RXPWDENV_MASK)

#define USBPHY_PWD_RXPWD1PT1_MASK                (0x40000U)
#define USBPHY_PWD_RXPWD1PT1_SHIFT               (18U)
/*! RXPWD1PT1
 *  0b0..Normal operation.
 *  0b1..Power-down the USB full-speed differential receiver.
 */
#define USBPHY_PWD_RXPWD1PT1(x)                  (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_RXPWD1PT1_SHIFT)) & USBPHY_PWD_RXPWD1PT1_MASK)

#define USBPHY_PWD_RXPWDDIFF_MASK                (0x80000U)
#define USBPHY_PWD_RXPWDDIFF_SHIFT               (19U)
/*! RXPWDDIFF
 *  0b0..Normal operation.
 *  0b1..Power-down the USB high-speed differential receive
 */
#define USBPHY_PWD_RXPWDDIFF(x)                  (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_RXPWDDIFF_SHIFT)) & USBPHY_PWD_RXPWDDIFF_MASK)

#define USBPHY_PWD_RXPWDRX_MASK                  (0x100000U)
#define USBPHY_PWD_RXPWDRX_SHIFT                 (20U)
/*! RXPWDRX
 *  0b0..Normal operation.
 *  0b1..Power-down the entire USB PHY receiver block except for the full-speed differential receiver
 */
#define USBPHY_PWD_RXPWDRX(x)                    (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_RXPWDRX_SHIFT)) & USBPHY_PWD_RXPWDRX_MASK)
/*! @} */

/*! @name PWD_SET - USB PHY Power-Down Register */
/*! @{ */

#define USBPHY_PWD_SET_TXPWDFS_MASK              (0x400U)
#define USBPHY_PWD_SET_TXPWDFS_SHIFT             (10U)
/*! TXPWDFS
 *  0b0..Normal operation.
 *  0b1..Power-down the USB full-speed drivers. This turns off the current starvation sources and puts the
 */
#define USBPHY_PWD_SET_TXPWDFS(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_SET_TXPWDFS_SHIFT)) & USBPHY_PWD_SET_TXPWDFS_MASK)

#define USBPHY_PWD_SET_TXPWDIBIAS_MASK           (0x800U)
#define USBPHY_PWD_SET_TXPWDIBIAS_SHIFT          (11U)
/*! TXPWDIBIAS
 *  0b0..Normal operation.
 *  0b1..Power-down the USB PHY current bias block for the transmitter. This bit should be set only when the
 */
#define USBPHY_PWD_SET_TXPWDIBIAS(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_SET_TXPWDIBIAS_SHIFT)) & USBPHY_PWD_SET_TXPWDIBIAS_MASK)

#define USBPHY_PWD_SET_TXPWDV2I_MASK             (0x1000U)
#define USBPHY_PWD_SET_TXPWDV2I_SHIFT            (12U)
/*! TXPWDV2I
 *  0b0..Normal operation.
 *  0b1..Power-down the USB PHY transmit V-to-I converter and the current mirror
 */
#define USBPHY_PWD_SET_TXPWDV2I(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_SET_TXPWDV2I_SHIFT)) & USBPHY_PWD_SET_TXPWDV2I_MASK)

#define USBPHY_PWD_SET_RXPWDENV_MASK             (0x20000U)
#define USBPHY_PWD_SET_RXPWDENV_SHIFT            (17U)
/*! RXPWDENV
 *  0b0..Normal operation.
 *  0b1..Power-down the USB high-speed receiver envelope detector (squelch signal)
 */
#define USBPHY_PWD_SET_RXPWDENV(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_SET_RXPWDENV_SHIFT)) & USBPHY_PWD_SET_RXPWDENV_MASK)

#define USBPHY_PWD_SET_RXPWD1PT1_MASK            (0x40000U)
#define USBPHY_PWD_SET_RXPWD1PT1_SHIFT           (18U)
/*! RXPWD1PT1
 *  0b0..Normal operation.
 *  0b1..Power-down the USB full-speed differential receiver.
 */
#define USBPHY_PWD_SET_RXPWD1PT1(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_SET_RXPWD1PT1_SHIFT)) & USBPHY_PWD_SET_RXPWD1PT1_MASK)

#define USBPHY_PWD_SET_RXPWDDIFF_MASK            (0x80000U)
#define USBPHY_PWD_SET_RXPWDDIFF_SHIFT           (19U)
/*! RXPWDDIFF
 *  0b0..Normal operation.
 *  0b1..Power-down the USB high-speed differential receive
 */
#define USBPHY_PWD_SET_RXPWDDIFF(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_SET_RXPWDDIFF_SHIFT)) & USBPHY_PWD_SET_RXPWDDIFF_MASK)

#define USBPHY_PWD_SET_RXPWDRX_MASK              (0x100000U)
#define USBPHY_PWD_SET_RXPWDRX_SHIFT             (20U)
/*! RXPWDRX
 *  0b0..Normal operation.
 *  0b1..Power-down the entire USB PHY receiver block except for the full-speed differential receiver
 */
#define USBPHY_PWD_SET_RXPWDRX(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_SET_RXPWDRX_SHIFT)) & USBPHY_PWD_SET_RXPWDRX_MASK)
/*! @} */

/*! @name PWD_CLR - USB PHY Power-Down Register */
/*! @{ */

#define USBPHY_PWD_CLR_TXPWDFS_MASK              (0x400U)
#define USBPHY_PWD_CLR_TXPWDFS_SHIFT             (10U)
/*! TXPWDFS
 *  0b0..Normal operation.
 *  0b1..Power-down the USB full-speed drivers. This turns off the current starvation sources and puts the
 */
#define USBPHY_PWD_CLR_TXPWDFS(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_CLR_TXPWDFS_SHIFT)) & USBPHY_PWD_CLR_TXPWDFS_MASK)

#define USBPHY_PWD_CLR_TXPWDIBIAS_MASK           (0x800U)
#define USBPHY_PWD_CLR_TXPWDIBIAS_SHIFT          (11U)
/*! TXPWDIBIAS
 *  0b0..Normal operation.
 *  0b1..Power-down the USB PHY current bias block for the transmitter. This bit should be set only when the
 */
#define USBPHY_PWD_CLR_TXPWDIBIAS(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_CLR_TXPWDIBIAS_SHIFT)) & USBPHY_PWD_CLR_TXPWDIBIAS_MASK)

#define USBPHY_PWD_CLR_TXPWDV2I_MASK             (0x1000U)
#define USBPHY_PWD_CLR_TXPWDV2I_SHIFT            (12U)
/*! TXPWDV2I
 *  0b0..Normal operation.
 *  0b1..Power-down the USB PHY transmit V-to-I converter and the current mirror
 */
#define USBPHY_PWD_CLR_TXPWDV2I(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_CLR_TXPWDV2I_SHIFT)) & USBPHY_PWD_CLR_TXPWDV2I_MASK)

#define USBPHY_PWD_CLR_RXPWDENV_MASK             (0x20000U)
#define USBPHY_PWD_CLR_RXPWDENV_SHIFT            (17U)
/*! RXPWDENV
 *  0b0..Normal operation.
 *  0b1..Power-down the USB high-speed receiver envelope detector (squelch signal)
 */
#define USBPHY_PWD_CLR_RXPWDENV(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_CLR_RXPWDENV_SHIFT)) & USBPHY_PWD_CLR_RXPWDENV_MASK)

#define USBPHY_PWD_CLR_RXPWD1PT1_MASK            (0x40000U)
#define USBPHY_PWD_CLR_RXPWD1PT1_SHIFT           (18U)
/*! RXPWD1PT1
 *  0b0..Normal operation.
 *  0b1..Power-down the USB full-speed differential receiver.
 */
#define USBPHY_PWD_CLR_RXPWD1PT1(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_CLR_RXPWD1PT1_SHIFT)) & USBPHY_PWD_CLR_RXPWD1PT1_MASK)

#define USBPHY_PWD_CLR_RXPWDDIFF_MASK            (0x80000U)
#define USBPHY_PWD_CLR_RXPWDDIFF_SHIFT           (19U)
/*! RXPWDDIFF
 *  0b0..Normal operation.
 *  0b1..Power-down the USB high-speed differential receive
 */
#define USBPHY_PWD_CLR_RXPWDDIFF(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_CLR_RXPWDDIFF_SHIFT)) & USBPHY_PWD_CLR_RXPWDDIFF_MASK)

#define USBPHY_PWD_CLR_RXPWDRX_MASK              (0x100000U)
#define USBPHY_PWD_CLR_RXPWDRX_SHIFT             (20U)
/*! RXPWDRX
 *  0b0..Normal operation.
 *  0b1..Power-down the entire USB PHY receiver block except for the full-speed differential receiver
 */
#define USBPHY_PWD_CLR_RXPWDRX(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_CLR_RXPWDRX_SHIFT)) & USBPHY_PWD_CLR_RXPWDRX_MASK)
/*! @} */

/*! @name PWD_TOG - USB PHY Power-Down Register */
/*! @{ */

#define USBPHY_PWD_TOG_TXPWDFS_MASK              (0x400U)
#define USBPHY_PWD_TOG_TXPWDFS_SHIFT             (10U)
/*! TXPWDFS
 *  0b0..Normal operation.
 *  0b1..Power-down the USB full-speed drivers. This turns off the current starvation sources and puts the
 */
#define USBPHY_PWD_TOG_TXPWDFS(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TOG_TXPWDFS_SHIFT)) & USBPHY_PWD_TOG_TXPWDFS_MASK)

#define USBPHY_PWD_TOG_TXPWDIBIAS_MASK           (0x800U)
#define USBPHY_PWD_TOG_TXPWDIBIAS_SHIFT          (11U)
/*! TXPWDIBIAS
 *  0b0..Normal operation.
 *  0b1..Power-down the USB PHY current bias block for the transmitter. This bit should be set only when the
 */
#define USBPHY_PWD_TOG_TXPWDIBIAS(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TOG_TXPWDIBIAS_SHIFT)) & USBPHY_PWD_TOG_TXPWDIBIAS_MASK)

#define USBPHY_PWD_TOG_TXPWDV2I_MASK             (0x1000U)
#define USBPHY_PWD_TOG_TXPWDV2I_SHIFT            (12U)
/*! TXPWDV2I
 *  0b0..Normal operation.
 *  0b1..Power-down the USB PHY transmit V-to-I converter and the current mirror
 */
#define USBPHY_PWD_TOG_TXPWDV2I(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TOG_TXPWDV2I_SHIFT)) & USBPHY_PWD_TOG_TXPWDV2I_MASK)

#define USBPHY_PWD_TOG_RXPWDENV_MASK             (0x20000U)
#define USBPHY_PWD_TOG_RXPWDENV_SHIFT            (17U)
/*! RXPWDENV
 *  0b0..Normal operation.
 *  0b1..Power-down the USB high-speed receiver envelope detector (squelch signal)
 */
#define USBPHY_PWD_TOG_RXPWDENV(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TOG_RXPWDENV_SHIFT)) & USBPHY_PWD_TOG_RXPWDENV_MASK)

#define USBPHY_PWD_TOG_RXPWD1PT1_MASK            (0x40000U)
#define USBPHY_PWD_TOG_RXPWD1PT1_SHIFT           (18U)
/*! RXPWD1PT1
 *  0b0..Normal operation.
 *  0b1..Power-down the USB full-speed differential receiver.
 */
#define USBPHY_PWD_TOG_RXPWD1PT1(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TOG_RXPWD1PT1_SHIFT)) & USBPHY_PWD_TOG_RXPWD1PT1_MASK)

#define USBPHY_PWD_TOG_RXPWDDIFF_MASK            (0x80000U)
#define USBPHY_PWD_TOG_RXPWDDIFF_SHIFT           (19U)
/*! RXPWDDIFF
 *  0b0..Normal operation.
 *  0b1..Power-down the USB high-speed differential receive
 */
#define USBPHY_PWD_TOG_RXPWDDIFF(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TOG_RXPWDDIFF_SHIFT)) & USBPHY_PWD_TOG_RXPWDDIFF_MASK)

#define USBPHY_PWD_TOG_RXPWDRX_MASK              (0x100000U)
#define USBPHY_PWD_TOG_RXPWDRX_SHIFT             (20U)
/*! RXPWDRX
 *  0b0..Normal operation.
 *  0b1..Power-down the entire USB PHY receiver block except for the full-speed differential receiver
 */
#define USBPHY_PWD_TOG_RXPWDRX(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TOG_RXPWDRX_SHIFT)) & USBPHY_PWD_TOG_RXPWDRX_MASK)
/*! @} */

/*! @name TX - USB PHY Transmitter Control Register */
/*! @{ */

#define USBPHY_TX_D_CAL_MASK                     (0xFU)
#define USBPHY_TX_D_CAL_SHIFT                    (0U)
/*! D_CAL
 *  0b0000..Maximum current, approximately 19% above nominal.
 *  0b0111..Nominal
 *  0b1111..Minimum current, approximately 19% below nominal.
 */
#define USBPHY_TX_D_CAL(x)                       (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_D_CAL_SHIFT)) & USBPHY_TX_D_CAL_MASK)

#define USBPHY_TX_TXCAL45DM_MASK                 (0xF00U)
#define USBPHY_TX_TXCAL45DM_SHIFT                (8U)
#define USBPHY_TX_TXCAL45DM(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_TXCAL45DM_SHIFT)) & USBPHY_TX_TXCAL45DM_MASK)

#define USBPHY_TX_TXENCAL45DN_MASK               (0x2000U)
#define USBPHY_TX_TXENCAL45DN_SHIFT              (13U)
#define USBPHY_TX_TXENCAL45DN(x)                 (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_TXENCAL45DN_SHIFT)) & USBPHY_TX_TXENCAL45DN_MASK)

#define USBPHY_TX_TXCAL45DP_MASK                 (0xF0000U)
#define USBPHY_TX_TXCAL45DP_SHIFT                (16U)
#define USBPHY_TX_TXCAL45DP(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_TXCAL45DP_SHIFT)) & USBPHY_TX_TXCAL45DP_MASK)

#define USBPHY_TX_TXENCAL45DP_MASK               (0x200000U)
#define USBPHY_TX_TXENCAL45DP_SHIFT              (21U)
#define USBPHY_TX_TXENCAL45DP(x)                 (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_TXENCAL45DP_SHIFT)) & USBPHY_TX_TXENCAL45DP_MASK)
/*! @} */

/*! @name TX_SET - USB PHY Transmitter Control Register */
/*! @{ */

#define USBPHY_TX_SET_D_CAL_MASK                 (0xFU)
#define USBPHY_TX_SET_D_CAL_SHIFT                (0U)
/*! D_CAL
 *  0b0000..Maximum current, approximately 19% above nominal.
 *  0b0111..Nominal
 *  0b1111..Minimum current, approximately 19% below nominal.
 */
#define USBPHY_TX_SET_D_CAL(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_SET_D_CAL_SHIFT)) & USBPHY_TX_SET_D_CAL_MASK)

#define USBPHY_TX_SET_TXCAL45DM_MASK             (0xF00U)
#define USBPHY_TX_SET_TXCAL45DM_SHIFT            (8U)
#define USBPHY_TX_SET_TXCAL45DM(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_SET_TXCAL45DM_SHIFT)) & USBPHY_TX_SET_TXCAL45DM_MASK)

#define USBPHY_TX_SET_TXENCAL45DN_MASK           (0x2000U)
#define USBPHY_TX_SET_TXENCAL45DN_SHIFT          (13U)
#define USBPHY_TX_SET_TXENCAL45DN(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_SET_TXENCAL45DN_SHIFT)) & USBPHY_TX_SET_TXENCAL45DN_MASK)

#define USBPHY_TX_SET_TXCAL45DP_MASK             (0xF0000U)
#define USBPHY_TX_SET_TXCAL45DP_SHIFT            (16U)
#define USBPHY_TX_SET_TXCAL45DP(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_SET_TXCAL45DP_SHIFT)) & USBPHY_TX_SET_TXCAL45DP_MASK)

#define USBPHY_TX_SET_TXENCAL45DP_MASK           (0x200000U)
#define USBPHY_TX_SET_TXENCAL45DP_SHIFT          (21U)
#define USBPHY_TX_SET_TXENCAL45DP(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_SET_TXENCAL45DP_SHIFT)) & USBPHY_TX_SET_TXENCAL45DP_MASK)
/*! @} */

/*! @name TX_CLR - USB PHY Transmitter Control Register */
/*! @{ */

#define USBPHY_TX_CLR_D_CAL_MASK                 (0xFU)
#define USBPHY_TX_CLR_D_CAL_SHIFT                (0U)
/*! D_CAL
 *  0b0000..Maximum current, approximately 19% above nominal.
 *  0b0111..Nominal
 *  0b1111..Minimum current, approximately 19% below nominal.
 */
#define USBPHY_TX_CLR_D_CAL(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_CLR_D_CAL_SHIFT)) & USBPHY_TX_CLR_D_CAL_MASK)

#define USBPHY_TX_CLR_TXCAL45DM_MASK             (0xF00U)
#define USBPHY_TX_CLR_TXCAL45DM_SHIFT            (8U)
#define USBPHY_TX_CLR_TXCAL45DM(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_CLR_TXCAL45DM_SHIFT)) & USBPHY_TX_CLR_TXCAL45DM_MASK)

#define USBPHY_TX_CLR_TXENCAL45DN_MASK           (0x2000U)
#define USBPHY_TX_CLR_TXENCAL45DN_SHIFT          (13U)
#define USBPHY_TX_CLR_TXENCAL45DN(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_CLR_TXENCAL45DN_SHIFT)) & USBPHY_TX_CLR_TXENCAL45DN_MASK)

#define USBPHY_TX_CLR_TXCAL45DP_MASK             (0xF0000U)
#define USBPHY_TX_CLR_TXCAL45DP_SHIFT            (16U)
#define USBPHY_TX_CLR_TXCAL45DP(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_CLR_TXCAL45DP_SHIFT)) & USBPHY_TX_CLR_TXCAL45DP_MASK)

#define USBPHY_TX_CLR_TXENCAL45DP_MASK           (0x200000U)
#define USBPHY_TX_CLR_TXENCAL45DP_SHIFT          (21U)
#define USBPHY_TX_CLR_TXENCAL45DP(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_CLR_TXENCAL45DP_SHIFT)) & USBPHY_TX_CLR_TXENCAL45DP_MASK)
/*! @} */

/*! @name TX_TOG - USB PHY Transmitter Control Register */
/*! @{ */

#define USBPHY_TX_TOG_D_CAL_MASK                 (0xFU)
#define USBPHY_TX_TOG_D_CAL_SHIFT                (0U)
/*! D_CAL
 *  0b0000..Maximum current, approximately 19% above nominal.
 *  0b0111..Nominal
 *  0b1111..Minimum current, approximately 19% below nominal.
 */
#define USBPHY_TX_TOG_D_CAL(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_TOG_D_CAL_SHIFT)) & USBPHY_TX_TOG_D_CAL_MASK)

#define USBPHY_TX_TOG_TXCAL45DM_MASK             (0xF00U)
#define USBPHY_TX_TOG_TXCAL45DM_SHIFT            (8U)
#define USBPHY_TX_TOG_TXCAL45DM(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_TOG_TXCAL45DM_SHIFT)) & USBPHY_TX_TOG_TXCAL45DM_MASK)

#define USBPHY_TX_TOG_TXENCAL45DN_MASK           (0x2000U)
#define USBPHY_TX_TOG_TXENCAL45DN_SHIFT          (13U)
#define USBPHY_TX_TOG_TXENCAL45DN(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_TOG_TXENCAL45DN_SHIFT)) & USBPHY_TX_TOG_TXENCAL45DN_MASK)

#define USBPHY_TX_TOG_TXCAL45DP_MASK             (0xF0000U)
#define USBPHY_TX_TOG_TXCAL45DP_SHIFT            (16U)
#define USBPHY_TX_TOG_TXCAL45DP(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_TOG_TXCAL45DP_SHIFT)) & USBPHY_TX_TOG_TXCAL45DP_MASK)

#define USBPHY_TX_TOG_TXENCAL45DP_MASK           (0x200000U)
#define USBPHY_TX_TOG_TXENCAL45DP_SHIFT          (21U)
#define USBPHY_TX_TOG_TXENCAL45DP(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_TOG_TXENCAL45DP_SHIFT)) & USBPHY_TX_TOG_TXENCAL45DP_MASK)
/*! @} */

/*! @name RX - USB PHY Receiver Control Register */
/*! @{ */

#define USBPHY_RX_ENVADJ_MASK                    (0x7U)
#define USBPHY_RX_ENVADJ_SHIFT                   (0U)
/*! ENVADJ
 *  0b000..Trip-Level Voltage is 0.1000 V
 *  0b001..Trip-Level Voltage is 0.1125 V
 *  0b010..Trip-Level Voltage is 0.1250 V
 *  0b011..Trip-Level Voltage is 0.0875 V
 *  0b100..reserved
 *  0b101..reserved
 *  0b110..reserved
 *  0b111..reserved
 */
#define USBPHY_RX_ENVADJ(x)                      (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_ENVADJ_SHIFT)) & USBPHY_RX_ENVADJ_MASK)

#define USBPHY_RX_DISCONADJ_MASK                 (0x70U)
#define USBPHY_RX_DISCONADJ_SHIFT                (4U)
/*! DISCONADJ
 *  0b000..Trip-Level Voltage is 0.56875 V
 *  0b001..Trip-Level Voltage is 0.55000 V
 *  0b010..Trip-Level Voltage is 0.58125 V
 *  0b011..Trip-Level Voltage is 0.60000 V
 *  0b100..reserved
 *  0b101..reserved
 *  0b110..reserved
 *  0b111..reserved
 */
#define USBPHY_RX_DISCONADJ(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_DISCONADJ_SHIFT)) & USBPHY_RX_DISCONADJ_MASK)

#define USBPHY_RX_RXDBYPASS_MASK                 (0x400000U)
#define USBPHY_RX_RXDBYPASS_SHIFT                (22U)
/*! RXDBYPASS
 *  0b0..Normal operation.
 *  0b1..Use the output of the USB_DP single-ended receiver in place of the full-speed differential receiver
 */
#define USBPHY_RX_RXDBYPASS(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_RXDBYPASS_SHIFT)) & USBPHY_RX_RXDBYPASS_MASK)
/*! @} */

/*! @name RX_SET - USB PHY Receiver Control Register */
/*! @{ */

#define USBPHY_RX_SET_ENVADJ_MASK                (0x7U)
#define USBPHY_RX_SET_ENVADJ_SHIFT               (0U)
/*! ENVADJ
 *  0b000..Trip-Level Voltage is 0.1000 V
 *  0b001..Trip-Level Voltage is 0.1125 V
 *  0b010..Trip-Level Voltage is 0.1250 V
 *  0b011..Trip-Level Voltage is 0.0875 V
 *  0b100..reserved
 *  0b101..reserved
 *  0b110..reserved
 *  0b111..reserved
 */
#define USBPHY_RX_SET_ENVADJ(x)                  (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_SET_ENVADJ_SHIFT)) & USBPHY_RX_SET_ENVADJ_MASK)

#define USBPHY_RX_SET_DISCONADJ_MASK             (0x70U)
#define USBPHY_RX_SET_DISCONADJ_SHIFT            (4U)
/*! DISCONADJ
 *  0b000..Trip-Level Voltage is 0.56875 V
 *  0b001..Trip-Level Voltage is 0.55000 V
 *  0b010..Trip-Level Voltage is 0.58125 V
 *  0b011..Trip-Level Voltage is 0.60000 V
 *  0b100..reserved
 *  0b101..reserved
 *  0b110..reserved
 *  0b111..reserved
 */
#define USBPHY_RX_SET_DISCONADJ(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_SET_DISCONADJ_SHIFT)) & USBPHY_RX_SET_DISCONADJ_MASK)

#define USBPHY_RX_SET_RXDBYPASS_MASK             (0x400000U)
#define USBPHY_RX_SET_RXDBYPASS_SHIFT            (22U)
/*! RXDBYPASS
 *  0b0..Normal operation.
 *  0b1..Use the output of the USB_DP single-ended receiver in place of the full-speed differential receiver
 */
#define USBPHY_RX_SET_RXDBYPASS(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_SET_RXDBYPASS_SHIFT)) & USBPHY_RX_SET_RXDBYPASS_MASK)
/*! @} */

/*! @name RX_CLR - USB PHY Receiver Control Register */
/*! @{ */

#define USBPHY_RX_CLR_ENVADJ_MASK                (0x7U)
#define USBPHY_RX_CLR_ENVADJ_SHIFT               (0U)
/*! ENVADJ
 *  0b000..Trip-Level Voltage is 0.1000 V
 *  0b001..Trip-Level Voltage is 0.1125 V
 *  0b010..Trip-Level Voltage is 0.1250 V
 *  0b011..Trip-Level Voltage is 0.0875 V
 *  0b100..reserved
 *  0b101..reserved
 *  0b110..reserved
 *  0b111..reserved
 */
#define USBPHY_RX_CLR_ENVADJ(x)                  (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_CLR_ENVADJ_SHIFT)) & USBPHY_RX_CLR_ENVADJ_MASK)

#define USBPHY_RX_CLR_DISCONADJ_MASK             (0x70U)
#define USBPHY_RX_CLR_DISCONADJ_SHIFT            (4U)
/*! DISCONADJ
 *  0b000..Trip-Level Voltage is 0.56875 V
 *  0b001..Trip-Level Voltage is 0.55000 V
 *  0b010..Trip-Level Voltage is 0.58125 V
 *  0b011..Trip-Level Voltage is 0.60000 V
 *  0b100..reserved
 *  0b101..reserved
 *  0b110..reserved
 *  0b111..reserved
 */
#define USBPHY_RX_CLR_DISCONADJ(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_CLR_DISCONADJ_SHIFT)) & USBPHY_RX_CLR_DISCONADJ_MASK)

#define USBPHY_RX_CLR_RXDBYPASS_MASK             (0x400000U)
#define USBPHY_RX_CLR_RXDBYPASS_SHIFT            (22U)
/*! RXDBYPASS
 *  0b0..Normal operation.
 *  0b1..Use the output of the USB_DP single-ended receiver in place of the full-speed differential receiver
 */
#define USBPHY_RX_CLR_RXDBYPASS(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_CLR_RXDBYPASS_SHIFT)) & USBPHY_RX_CLR_RXDBYPASS_MASK)
/*! @} */

/*! @name RX_TOG - USB PHY Receiver Control Register */
/*! @{ */

#define USBPHY_RX_TOG_ENVADJ_MASK                (0x7U)
#define USBPHY_RX_TOG_ENVADJ_SHIFT               (0U)
/*! ENVADJ
 *  0b000..Trip-Level Voltage is 0.1000 V
 *  0b001..Trip-Level Voltage is 0.1125 V
 *  0b010..Trip-Level Voltage is 0.1250 V
 *  0b011..Trip-Level Voltage is 0.0875 V
 *  0b100..reserved
 *  0b101..reserved
 *  0b110..reserved
 *  0b111..reserved
 */
#define USBPHY_RX_TOG_ENVADJ(x)                  (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_TOG_ENVADJ_SHIFT)) & USBPHY_RX_TOG_ENVADJ_MASK)

#define USBPHY_RX_TOG_DISCONADJ_MASK             (0x70U)
#define USBPHY_RX_TOG_DISCONADJ_SHIFT            (4U)
/*! DISCONADJ
 *  0b000..Trip-Level Voltage is 0.56875 V
 *  0b001..Trip-Level Voltage is 0.55000 V
 *  0b010..Trip-Level Voltage is 0.58125 V
 *  0b011..Trip-Level Voltage is 0.60000 V
 *  0b100..reserved
 *  0b101..reserved
 *  0b110..reserved
 *  0b111..reserved
 */
#define USBPHY_RX_TOG_DISCONADJ(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_TOG_DISCONADJ_SHIFT)) & USBPHY_RX_TOG_DISCONADJ_MASK)

#define USBPHY_RX_TOG_RXDBYPASS_MASK             (0x400000U)
#define USBPHY_RX_TOG_RXDBYPASS_SHIFT            (22U)
/*! RXDBYPASS
 *  0b0..Normal operation.
 *  0b1..Use the output of the USB_DP single-ended receiver in place of the full-speed differential receiver
 */
#define USBPHY_RX_TOG_RXDBYPASS(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_TOG_RXDBYPASS_SHIFT)) & USBPHY_RX_TOG_RXDBYPASS_MASK)
/*! @} */

/*! @name CTRL - USB PHY General Control Register */
/*! @{ */

#define USBPHY_CTRL_ENHOSTDISCONDETECT_MASK      (0x2U)
#define USBPHY_CTRL_ENHOSTDISCONDETECT_SHIFT     (1U)
#define USBPHY_CTRL_ENHOSTDISCONDETECT(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENHOSTDISCONDETECT_SHIFT)) & USBPHY_CTRL_ENHOSTDISCONDETECT_MASK)

#define USBPHY_CTRL_ENIRQHOSTDISCON_MASK         (0x4U)
#define USBPHY_CTRL_ENIRQHOSTDISCON_SHIFT        (2U)
#define USBPHY_CTRL_ENIRQHOSTDISCON(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENIRQHOSTDISCON_SHIFT)) & USBPHY_CTRL_ENIRQHOSTDISCON_MASK)

#define USBPHY_CTRL_HOSTDISCONDETECT_IRQ_MASK    (0x8U)
#define USBPHY_CTRL_HOSTDISCONDETECT_IRQ_SHIFT   (3U)
#define USBPHY_CTRL_HOSTDISCONDETECT_IRQ(x)      (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_HOSTDISCONDETECT_IRQ_SHIFT)) & USBPHY_CTRL_HOSTDISCONDETECT_IRQ_MASK)

#define USBPHY_CTRL_ENDEVPLUGINDET_MASK          (0x10U)
#define USBPHY_CTRL_ENDEVPLUGINDET_SHIFT         (4U)
/*! ENDEVPLUGINDET
 *  0b0..Disables 200kohm pullup resistors on USB_DP and USB_DM pins (Default)
 *  0b1..Enables 200kohm pullup resistors on USB_DP and USB_DM pins
 */
#define USBPHY_CTRL_ENDEVPLUGINDET(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENDEVPLUGINDET_SHIFT)) & USBPHY_CTRL_ENDEVPLUGINDET_MASK)

#define USBPHY_CTRL_DEVPLUGIN_POLARITY_MASK      (0x20U)
#define USBPHY_CTRL_DEVPLUGIN_POLARITY_SHIFT     (5U)
#define USBPHY_CTRL_DEVPLUGIN_POLARITY(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_DEVPLUGIN_POLARITY_SHIFT)) & USBPHY_CTRL_DEVPLUGIN_POLARITY_MASK)

#define USBPHY_CTRL_RESUMEIRQSTICKY_MASK         (0x100U)
#define USBPHY_CTRL_RESUMEIRQSTICKY_SHIFT        (8U)
#define USBPHY_CTRL_RESUMEIRQSTICKY(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_RESUMEIRQSTICKY_SHIFT)) & USBPHY_CTRL_RESUMEIRQSTICKY_MASK)

#define USBPHY_CTRL_ENIRQRESUMEDETECT_MASK       (0x200U)
#define USBPHY_CTRL_ENIRQRESUMEDETECT_SHIFT      (9U)
#define USBPHY_CTRL_ENIRQRESUMEDETECT(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENIRQRESUMEDETECT_SHIFT)) & USBPHY_CTRL_ENIRQRESUMEDETECT_MASK)

#define USBPHY_CTRL_RESUME_IRQ_MASK              (0x400U)
#define USBPHY_CTRL_RESUME_IRQ_SHIFT             (10U)
#define USBPHY_CTRL_RESUME_IRQ(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_RESUME_IRQ_SHIFT)) & USBPHY_CTRL_RESUME_IRQ_MASK)

#define USBPHY_CTRL_DEVPLUGIN_IRQ_MASK           (0x1000U)
#define USBPHY_CTRL_DEVPLUGIN_IRQ_SHIFT          (12U)
#define USBPHY_CTRL_DEVPLUGIN_IRQ(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_DEVPLUGIN_IRQ_SHIFT)) & USBPHY_CTRL_DEVPLUGIN_IRQ_MASK)

#define USBPHY_CTRL_ENUTMILEVEL2_MASK            (0x4000U)
#define USBPHY_CTRL_ENUTMILEVEL2_SHIFT           (14U)
#define USBPHY_CTRL_ENUTMILEVEL2(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENUTMILEVEL2_SHIFT)) & USBPHY_CTRL_ENUTMILEVEL2_MASK)

#define USBPHY_CTRL_ENUTMILEVEL3_MASK            (0x8000U)
#define USBPHY_CTRL_ENUTMILEVEL3_SHIFT           (15U)
#define USBPHY_CTRL_ENUTMILEVEL3(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENUTMILEVEL3_SHIFT)) & USBPHY_CTRL_ENUTMILEVEL3_MASK)

#define USBPHY_CTRL_ENIRQWAKEUP_MASK             (0x10000U)
#define USBPHY_CTRL_ENIRQWAKEUP_SHIFT            (16U)
#define USBPHY_CTRL_ENIRQWAKEUP(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENIRQWAKEUP_SHIFT)) & USBPHY_CTRL_ENIRQWAKEUP_MASK)

#define USBPHY_CTRL_WAKEUP_IRQ_MASK              (0x20000U)
#define USBPHY_CTRL_WAKEUP_IRQ_SHIFT             (17U)
#define USBPHY_CTRL_WAKEUP_IRQ(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_WAKEUP_IRQ_SHIFT)) & USBPHY_CTRL_WAKEUP_IRQ_MASK)

#define USBPHY_CTRL_AUTORESUME_EN_MASK           (0x40000U)
#define USBPHY_CTRL_AUTORESUME_EN_SHIFT          (18U)
#define USBPHY_CTRL_AUTORESUME_EN(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_AUTORESUME_EN_SHIFT)) & USBPHY_CTRL_AUTORESUME_EN_MASK)

#define USBPHY_CTRL_ENAUTOCLR_CLKGATE_MASK       (0x80000U)
#define USBPHY_CTRL_ENAUTOCLR_CLKGATE_SHIFT      (19U)
#define USBPHY_CTRL_ENAUTOCLR_CLKGATE(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENAUTOCLR_CLKGATE_SHIFT)) & USBPHY_CTRL_ENAUTOCLR_CLKGATE_MASK)

#define USBPHY_CTRL_ENAUTOCLR_PHY_PWD_MASK       (0x100000U)
#define USBPHY_CTRL_ENAUTOCLR_PHY_PWD_SHIFT      (20U)
#define USBPHY_CTRL_ENAUTOCLR_PHY_PWD(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENAUTOCLR_PHY_PWD_SHIFT)) & USBPHY_CTRL_ENAUTOCLR_PHY_PWD_MASK)

#define USBPHY_CTRL_ENDPDMCHG_WKUP_MASK          (0x200000U)
#define USBPHY_CTRL_ENDPDMCHG_WKUP_SHIFT         (21U)
#define USBPHY_CTRL_ENDPDMCHG_WKUP(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENDPDMCHG_WKUP_SHIFT)) & USBPHY_CTRL_ENDPDMCHG_WKUP_MASK)

#define USBPHY_CTRL_ENVBUSCHG_WKUP_MASK          (0x800000U)
#define USBPHY_CTRL_ENVBUSCHG_WKUP_SHIFT         (23U)
#define USBPHY_CTRL_ENVBUSCHG_WKUP(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENVBUSCHG_WKUP_SHIFT)) & USBPHY_CTRL_ENVBUSCHG_WKUP_MASK)

#define USBPHY_CTRL_ENAUTOCLR_USBCLKGATE_MASK    (0x2000000U)
#define USBPHY_CTRL_ENAUTOCLR_USBCLKGATE_SHIFT   (25U)
#define USBPHY_CTRL_ENAUTOCLR_USBCLKGATE(x)      (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENAUTOCLR_USBCLKGATE_SHIFT)) & USBPHY_CTRL_ENAUTOCLR_USBCLKGATE_MASK)

#define USBPHY_CTRL_ENAUTOSET_USBCLKS_MASK       (0x4000000U)
#define USBPHY_CTRL_ENAUTOSET_USBCLKS_SHIFT      (26U)
#define USBPHY_CTRL_ENAUTOSET_USBCLKS(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENAUTOSET_USBCLKS_SHIFT)) & USBPHY_CTRL_ENAUTOSET_USBCLKS_MASK)

#define USBPHY_CTRL_HOST_FORCE_LS_SE0_MASK       (0x10000000U)
#define USBPHY_CTRL_HOST_FORCE_LS_SE0_SHIFT      (28U)
#define USBPHY_CTRL_HOST_FORCE_LS_SE0(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_HOST_FORCE_LS_SE0_SHIFT)) & USBPHY_CTRL_HOST_FORCE_LS_SE0_MASK)

#define USBPHY_CTRL_UTMI_SUSPENDM_MASK           (0x20000000U)
#define USBPHY_CTRL_UTMI_SUSPENDM_SHIFT          (29U)
#define USBPHY_CTRL_UTMI_SUSPENDM(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_UTMI_SUSPENDM_SHIFT)) & USBPHY_CTRL_UTMI_SUSPENDM_MASK)

#define USBPHY_CTRL_CLKGATE_MASK                 (0x40000000U)
#define USBPHY_CTRL_CLKGATE_SHIFT                (30U)
#define USBPHY_CTRL_CLKGATE(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLKGATE_SHIFT)) & USBPHY_CTRL_CLKGATE_MASK)

#define USBPHY_CTRL_SFTRST_MASK                  (0x80000000U)
#define USBPHY_CTRL_SFTRST_SHIFT                 (31U)
#define USBPHY_CTRL_SFTRST(x)                    (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SFTRST_SHIFT)) & USBPHY_CTRL_SFTRST_MASK)
/*! @} */

/*! @name CTRL_SET - USB PHY General Control Register */
/*! @{ */

#define USBPHY_CTRL_SET_ENHOSTDISCONDETECT_MASK  (0x2U)
#define USBPHY_CTRL_SET_ENHOSTDISCONDETECT_SHIFT (1U)
#define USBPHY_CTRL_SET_ENHOSTDISCONDETECT(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENHOSTDISCONDETECT_SHIFT)) & USBPHY_CTRL_SET_ENHOSTDISCONDETECT_MASK)

#define USBPHY_CTRL_SET_ENIRQHOSTDISCON_MASK     (0x4U)
#define USBPHY_CTRL_SET_ENIRQHOSTDISCON_SHIFT    (2U)
#define USBPHY_CTRL_SET_ENIRQHOSTDISCON(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENIRQHOSTDISCON_SHIFT)) & USBPHY_CTRL_SET_ENIRQHOSTDISCON_MASK)

#define USBPHY_CTRL_SET_HOSTDISCONDETECT_IRQ_MASK (0x8U)
#define USBPHY_CTRL_SET_HOSTDISCONDETECT_IRQ_SHIFT (3U)
#define USBPHY_CTRL_SET_HOSTDISCONDETECT_IRQ(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_HOSTDISCONDETECT_IRQ_SHIFT)) & USBPHY_CTRL_SET_HOSTDISCONDETECT_IRQ_MASK)

#define USBPHY_CTRL_SET_ENDEVPLUGINDET_MASK      (0x10U)
#define USBPHY_CTRL_SET_ENDEVPLUGINDET_SHIFT     (4U)
/*! ENDEVPLUGINDET
 *  0b0..Disables 200kohm pullup resistors on USB_DP and USB_DM pins (Default)
 *  0b1..Enables 200kohm pullup resistors on USB_DP and USB_DM pins
 */
#define USBPHY_CTRL_SET_ENDEVPLUGINDET(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENDEVPLUGINDET_SHIFT)) & USBPHY_CTRL_SET_ENDEVPLUGINDET_MASK)

#define USBPHY_CTRL_SET_DEVPLUGIN_POLARITY_MASK  (0x20U)
#define USBPHY_CTRL_SET_DEVPLUGIN_POLARITY_SHIFT (5U)
#define USBPHY_CTRL_SET_DEVPLUGIN_POLARITY(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_DEVPLUGIN_POLARITY_SHIFT)) & USBPHY_CTRL_SET_DEVPLUGIN_POLARITY_MASK)

#define USBPHY_CTRL_SET_RESUMEIRQSTICKY_MASK     (0x100U)
#define USBPHY_CTRL_SET_RESUMEIRQSTICKY_SHIFT    (8U)
#define USBPHY_CTRL_SET_RESUMEIRQSTICKY(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_RESUMEIRQSTICKY_SHIFT)) & USBPHY_CTRL_SET_RESUMEIRQSTICKY_MASK)

#define USBPHY_CTRL_SET_ENIRQRESUMEDETECT_MASK   (0x200U)
#define USBPHY_CTRL_SET_ENIRQRESUMEDETECT_SHIFT  (9U)
#define USBPHY_CTRL_SET_ENIRQRESUMEDETECT(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENIRQRESUMEDETECT_SHIFT)) & USBPHY_CTRL_SET_ENIRQRESUMEDETECT_MASK)

#define USBPHY_CTRL_SET_RESUME_IRQ_MASK          (0x400U)
#define USBPHY_CTRL_SET_RESUME_IRQ_SHIFT         (10U)
#define USBPHY_CTRL_SET_RESUME_IRQ(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_RESUME_IRQ_SHIFT)) & USBPHY_CTRL_SET_RESUME_IRQ_MASK)

#define USBPHY_CTRL_SET_DEVPLUGIN_IRQ_MASK       (0x1000U)
#define USBPHY_CTRL_SET_DEVPLUGIN_IRQ_SHIFT      (12U)
#define USBPHY_CTRL_SET_DEVPLUGIN_IRQ(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_DEVPLUGIN_IRQ_SHIFT)) & USBPHY_CTRL_SET_DEVPLUGIN_IRQ_MASK)

#define USBPHY_CTRL_SET_ENUTMILEVEL2_MASK        (0x4000U)
#define USBPHY_CTRL_SET_ENUTMILEVEL2_SHIFT       (14U)
#define USBPHY_CTRL_SET_ENUTMILEVEL2(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENUTMILEVEL2_SHIFT)) & USBPHY_CTRL_SET_ENUTMILEVEL2_MASK)

#define USBPHY_CTRL_SET_ENUTMILEVEL3_MASK        (0x8000U)
#define USBPHY_CTRL_SET_ENUTMILEVEL3_SHIFT       (15U)
#define USBPHY_CTRL_SET_ENUTMILEVEL3(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENUTMILEVEL3_SHIFT)) & USBPHY_CTRL_SET_ENUTMILEVEL3_MASK)

#define USBPHY_CTRL_SET_ENIRQWAKEUP_MASK         (0x10000U)
#define USBPHY_CTRL_SET_ENIRQWAKEUP_SHIFT        (16U)
#define USBPHY_CTRL_SET_ENIRQWAKEUP(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENIRQWAKEUP_SHIFT)) & USBPHY_CTRL_SET_ENIRQWAKEUP_MASK)

#define USBPHY_CTRL_SET_WAKEUP_IRQ_MASK          (0x20000U)
#define USBPHY_CTRL_SET_WAKEUP_IRQ_SHIFT         (17U)
#define USBPHY_CTRL_SET_WAKEUP_IRQ(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_WAKEUP_IRQ_SHIFT)) & USBPHY_CTRL_SET_WAKEUP_IRQ_MASK)

#define USBPHY_CTRL_SET_AUTORESUME_EN_MASK       (0x40000U)
#define USBPHY_CTRL_SET_AUTORESUME_EN_SHIFT      (18U)
#define USBPHY_CTRL_SET_AUTORESUME_EN(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_AUTORESUME_EN_SHIFT)) & USBPHY_CTRL_SET_AUTORESUME_EN_MASK)

#define USBPHY_CTRL_SET_ENAUTOCLR_CLKGATE_MASK   (0x80000U)
#define USBPHY_CTRL_SET_ENAUTOCLR_CLKGATE_SHIFT  (19U)
#define USBPHY_CTRL_SET_ENAUTOCLR_CLKGATE(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENAUTOCLR_CLKGATE_SHIFT)) & USBPHY_CTRL_SET_ENAUTOCLR_CLKGATE_MASK)

#define USBPHY_CTRL_SET_ENAUTOCLR_PHY_PWD_MASK   (0x100000U)
#define USBPHY_CTRL_SET_ENAUTOCLR_PHY_PWD_SHIFT  (20U)
#define USBPHY_CTRL_SET_ENAUTOCLR_PHY_PWD(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENAUTOCLR_PHY_PWD_SHIFT)) & USBPHY_CTRL_SET_ENAUTOCLR_PHY_PWD_MASK)

#define USBPHY_CTRL_SET_ENDPDMCHG_WKUP_MASK      (0x200000U)
#define USBPHY_CTRL_SET_ENDPDMCHG_WKUP_SHIFT     (21U)
#define USBPHY_CTRL_SET_ENDPDMCHG_WKUP(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENDPDMCHG_WKUP_SHIFT)) & USBPHY_CTRL_SET_ENDPDMCHG_WKUP_MASK)

#define USBPHY_CTRL_SET_ENVBUSCHG_WKUP_MASK      (0x800000U)
#define USBPHY_CTRL_SET_ENVBUSCHG_WKUP_SHIFT     (23U)
#define USBPHY_CTRL_SET_ENVBUSCHG_WKUP(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENVBUSCHG_WKUP_SHIFT)) & USBPHY_CTRL_SET_ENVBUSCHG_WKUP_MASK)

#define USBPHY_CTRL_SET_ENAUTOCLR_USBCLKGATE_MASK (0x2000000U)
#define USBPHY_CTRL_SET_ENAUTOCLR_USBCLKGATE_SHIFT (25U)
#define USBPHY_CTRL_SET_ENAUTOCLR_USBCLKGATE(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENAUTOCLR_USBCLKGATE_SHIFT)) & USBPHY_CTRL_SET_ENAUTOCLR_USBCLKGATE_MASK)

#define USBPHY_CTRL_SET_ENAUTOSET_USBCLKS_MASK   (0x4000000U)
#define USBPHY_CTRL_SET_ENAUTOSET_USBCLKS_SHIFT  (26U)
#define USBPHY_CTRL_SET_ENAUTOSET_USBCLKS(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENAUTOSET_USBCLKS_SHIFT)) & USBPHY_CTRL_SET_ENAUTOSET_USBCLKS_MASK)

#define USBPHY_CTRL_SET_HOST_FORCE_LS_SE0_MASK   (0x10000000U)
#define USBPHY_CTRL_SET_HOST_FORCE_LS_SE0_SHIFT  (28U)
#define USBPHY_CTRL_SET_HOST_FORCE_LS_SE0(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_HOST_FORCE_LS_SE0_SHIFT)) & USBPHY_CTRL_SET_HOST_FORCE_LS_SE0_MASK)

#define USBPHY_CTRL_SET_UTMI_SUSPENDM_MASK       (0x20000000U)
#define USBPHY_CTRL_SET_UTMI_SUSPENDM_SHIFT      (29U)
#define USBPHY_CTRL_SET_UTMI_SUSPENDM(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_UTMI_SUSPENDM_SHIFT)) & USBPHY_CTRL_SET_UTMI_SUSPENDM_MASK)

#define USBPHY_CTRL_SET_CLKGATE_MASK             (0x40000000U)
#define USBPHY_CTRL_SET_CLKGATE_SHIFT            (30U)
#define USBPHY_CTRL_SET_CLKGATE(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_CLKGATE_SHIFT)) & USBPHY_CTRL_SET_CLKGATE_MASK)

#define USBPHY_CTRL_SET_SFTRST_MASK              (0x80000000U)
#define USBPHY_CTRL_SET_SFTRST_SHIFT             (31U)
#define USBPHY_CTRL_SET_SFTRST(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_SFTRST_SHIFT)) & USBPHY_CTRL_SET_SFTRST_MASK)
/*! @} */

/*! @name CTRL_CLR - USB PHY General Control Register */
/*! @{ */

#define USBPHY_CTRL_CLR_ENHOSTDISCONDETECT_MASK  (0x2U)
#define USBPHY_CTRL_CLR_ENHOSTDISCONDETECT_SHIFT (1U)
#define USBPHY_CTRL_CLR_ENHOSTDISCONDETECT(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENHOSTDISCONDETECT_SHIFT)) & USBPHY_CTRL_CLR_ENHOSTDISCONDETECT_MASK)

#define USBPHY_CTRL_CLR_ENIRQHOSTDISCON_MASK     (0x4U)
#define USBPHY_CTRL_CLR_ENIRQHOSTDISCON_SHIFT    (2U)
#define USBPHY_CTRL_CLR_ENIRQHOSTDISCON(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENIRQHOSTDISCON_SHIFT)) & USBPHY_CTRL_CLR_ENIRQHOSTDISCON_MASK)

#define USBPHY_CTRL_CLR_HOSTDISCONDETECT_IRQ_MASK (0x8U)
#define USBPHY_CTRL_CLR_HOSTDISCONDETECT_IRQ_SHIFT (3U)
#define USBPHY_CTRL_CLR_HOSTDISCONDETECT_IRQ(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_HOSTDISCONDETECT_IRQ_SHIFT)) & USBPHY_CTRL_CLR_HOSTDISCONDETECT_IRQ_MASK)

#define USBPHY_CTRL_CLR_ENDEVPLUGINDET_MASK      (0x10U)
#define USBPHY_CTRL_CLR_ENDEVPLUGINDET_SHIFT     (4U)
/*! ENDEVPLUGINDET
 *  0b0..Disables 200kohm pullup resistors on USB_DP and USB_DM pins (Default)
 *  0b1..Enables 200kohm pullup resistors on USB_DP and USB_DM pins
 */
#define USBPHY_CTRL_CLR_ENDEVPLUGINDET(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENDEVPLUGINDET_SHIFT)) & USBPHY_CTRL_CLR_ENDEVPLUGINDET_MASK)

#define USBPHY_CTRL_CLR_DEVPLUGIN_POLARITY_MASK  (0x20U)
#define USBPHY_CTRL_CLR_DEVPLUGIN_POLARITY_SHIFT (5U)
#define USBPHY_CTRL_CLR_DEVPLUGIN_POLARITY(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_DEVPLUGIN_POLARITY_SHIFT)) & USBPHY_CTRL_CLR_DEVPLUGIN_POLARITY_MASK)

#define USBPHY_CTRL_CLR_RESUMEIRQSTICKY_MASK     (0x100U)
#define USBPHY_CTRL_CLR_RESUMEIRQSTICKY_SHIFT    (8U)
#define USBPHY_CTRL_CLR_RESUMEIRQSTICKY(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_RESUMEIRQSTICKY_SHIFT)) & USBPHY_CTRL_CLR_RESUMEIRQSTICKY_MASK)

#define USBPHY_CTRL_CLR_ENIRQRESUMEDETECT_MASK   (0x200U)
#define USBPHY_CTRL_CLR_ENIRQRESUMEDETECT_SHIFT  (9U)
#define USBPHY_CTRL_CLR_ENIRQRESUMEDETECT(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENIRQRESUMEDETECT_SHIFT)) & USBPHY_CTRL_CLR_ENIRQRESUMEDETECT_MASK)

#define USBPHY_CTRL_CLR_RESUME_IRQ_MASK          (0x400U)
#define USBPHY_CTRL_CLR_RESUME_IRQ_SHIFT         (10U)
#define USBPHY_CTRL_CLR_RESUME_IRQ(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_RESUME_IRQ_SHIFT)) & USBPHY_CTRL_CLR_RESUME_IRQ_MASK)

#define USBPHY_CTRL_CLR_DEVPLUGIN_IRQ_MASK       (0x1000U)
#define USBPHY_CTRL_CLR_DEVPLUGIN_IRQ_SHIFT      (12U)
#define USBPHY_CTRL_CLR_DEVPLUGIN_IRQ(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_DEVPLUGIN_IRQ_SHIFT)) & USBPHY_CTRL_CLR_DEVPLUGIN_IRQ_MASK)

#define USBPHY_CTRL_CLR_ENUTMILEVEL2_MASK        (0x4000U)
#define USBPHY_CTRL_CLR_ENUTMILEVEL2_SHIFT       (14U)
#define USBPHY_CTRL_CLR_ENUTMILEVEL2(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENUTMILEVEL2_SHIFT)) & USBPHY_CTRL_CLR_ENUTMILEVEL2_MASK)

#define USBPHY_CTRL_CLR_ENUTMILEVEL3_MASK        (0x8000U)
#define USBPHY_CTRL_CLR_ENUTMILEVEL3_SHIFT       (15U)
#define USBPHY_CTRL_CLR_ENUTMILEVEL3(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENUTMILEVEL3_SHIFT)) & USBPHY_CTRL_CLR_ENUTMILEVEL3_MASK)

#define USBPHY_CTRL_CLR_ENIRQWAKEUP_MASK         (0x10000U)
#define USBPHY_CTRL_CLR_ENIRQWAKEUP_SHIFT        (16U)
#define USBPHY_CTRL_CLR_ENIRQWAKEUP(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENIRQWAKEUP_SHIFT)) & USBPHY_CTRL_CLR_ENIRQWAKEUP_MASK)

#define USBPHY_CTRL_CLR_WAKEUP_IRQ_MASK          (0x20000U)
#define USBPHY_CTRL_CLR_WAKEUP_IRQ_SHIFT         (17U)
#define USBPHY_CTRL_CLR_WAKEUP_IRQ(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_WAKEUP_IRQ_SHIFT)) & USBPHY_CTRL_CLR_WAKEUP_IRQ_MASK)

#define USBPHY_CTRL_CLR_AUTORESUME_EN_MASK       (0x40000U)
#define USBPHY_CTRL_CLR_AUTORESUME_EN_SHIFT      (18U)
#define USBPHY_CTRL_CLR_AUTORESUME_EN(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_AUTORESUME_EN_SHIFT)) & USBPHY_CTRL_CLR_AUTORESUME_EN_MASK)

#define USBPHY_CTRL_CLR_ENAUTOCLR_CLKGATE_MASK   (0x80000U)
#define USBPHY_CTRL_CLR_ENAUTOCLR_CLKGATE_SHIFT  (19U)
#define USBPHY_CTRL_CLR_ENAUTOCLR_CLKGATE(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENAUTOCLR_CLKGATE_SHIFT)) & USBPHY_CTRL_CLR_ENAUTOCLR_CLKGATE_MASK)

#define USBPHY_CTRL_CLR_ENAUTOCLR_PHY_PWD_MASK   (0x100000U)
#define USBPHY_CTRL_CLR_ENAUTOCLR_PHY_PWD_SHIFT  (20U)
#define USBPHY_CTRL_CLR_ENAUTOCLR_PHY_PWD(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENAUTOCLR_PHY_PWD_SHIFT)) & USBPHY_CTRL_CLR_ENAUTOCLR_PHY_PWD_MASK)

#define USBPHY_CTRL_CLR_ENDPDMCHG_WKUP_MASK      (0x200000U)
#define USBPHY_CTRL_CLR_ENDPDMCHG_WKUP_SHIFT     (21U)
#define USBPHY_CTRL_CLR_ENDPDMCHG_WKUP(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENDPDMCHG_WKUP_SHIFT)) & USBPHY_CTRL_CLR_ENDPDMCHG_WKUP_MASK)

#define USBPHY_CTRL_CLR_ENVBUSCHG_WKUP_MASK      (0x800000U)
#define USBPHY_CTRL_CLR_ENVBUSCHG_WKUP_SHIFT     (23U)
#define USBPHY_CTRL_CLR_ENVBUSCHG_WKUP(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENVBUSCHG_WKUP_SHIFT)) & USBPHY_CTRL_CLR_ENVBUSCHG_WKUP_MASK)

#define USBPHY_CTRL_CLR_ENAUTOCLR_USBCLKGATE_MASK (0x2000000U)
#define USBPHY_CTRL_CLR_ENAUTOCLR_USBCLKGATE_SHIFT (25U)
#define USBPHY_CTRL_CLR_ENAUTOCLR_USBCLKGATE(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENAUTOCLR_USBCLKGATE_SHIFT)) & USBPHY_CTRL_CLR_ENAUTOCLR_USBCLKGATE_MASK)

#define USBPHY_CTRL_CLR_ENAUTOSET_USBCLKS_MASK   (0x4000000U)
#define USBPHY_CTRL_CLR_ENAUTOSET_USBCLKS_SHIFT  (26U)
#define USBPHY_CTRL_CLR_ENAUTOSET_USBCLKS(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENAUTOSET_USBCLKS_SHIFT)) & USBPHY_CTRL_CLR_ENAUTOSET_USBCLKS_MASK)

#define USBPHY_CTRL_CLR_HOST_FORCE_LS_SE0_MASK   (0x10000000U)
#define USBPHY_CTRL_CLR_HOST_FORCE_LS_SE0_SHIFT  (28U)
#define USBPHY_CTRL_CLR_HOST_FORCE_LS_SE0(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_HOST_FORCE_LS_SE0_SHIFT)) & USBPHY_CTRL_CLR_HOST_FORCE_LS_SE0_MASK)

#define USBPHY_CTRL_CLR_UTMI_SUSPENDM_MASK       (0x20000000U)
#define USBPHY_CTRL_CLR_UTMI_SUSPENDM_SHIFT      (29U)
#define USBPHY_CTRL_CLR_UTMI_SUSPENDM(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_UTMI_SUSPENDM_SHIFT)) & USBPHY_CTRL_CLR_UTMI_SUSPENDM_MASK)

#define USBPHY_CTRL_CLR_CLKGATE_MASK             (0x40000000U)
#define USBPHY_CTRL_CLR_CLKGATE_SHIFT            (30U)
#define USBPHY_CTRL_CLR_CLKGATE(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_CLKGATE_SHIFT)) & USBPHY_CTRL_CLR_CLKGATE_MASK)

#define USBPHY_CTRL_CLR_SFTRST_MASK              (0x80000000U)
#define USBPHY_CTRL_CLR_SFTRST_SHIFT             (31U)
#define USBPHY_CTRL_CLR_SFTRST(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_SFTRST_SHIFT)) & USBPHY_CTRL_CLR_SFTRST_MASK)
/*! @} */

/*! @name CTRL_TOG - USB PHY General Control Register */
/*! @{ */

#define USBPHY_CTRL_TOG_ENHOSTDISCONDETECT_MASK  (0x2U)
#define USBPHY_CTRL_TOG_ENHOSTDISCONDETECT_SHIFT (1U)
#define USBPHY_CTRL_TOG_ENHOSTDISCONDETECT(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENHOSTDISCONDETECT_SHIFT)) & USBPHY_CTRL_TOG_ENHOSTDISCONDETECT_MASK)

#define USBPHY_CTRL_TOG_ENIRQHOSTDISCON_MASK     (0x4U)
#define USBPHY_CTRL_TOG_ENIRQHOSTDISCON_SHIFT    (2U)
#define USBPHY_CTRL_TOG_ENIRQHOSTDISCON(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENIRQHOSTDISCON_SHIFT)) & USBPHY_CTRL_TOG_ENIRQHOSTDISCON_MASK)

#define USBPHY_CTRL_TOG_HOSTDISCONDETECT_IRQ_MASK (0x8U)
#define USBPHY_CTRL_TOG_HOSTDISCONDETECT_IRQ_SHIFT (3U)
#define USBPHY_CTRL_TOG_HOSTDISCONDETECT_IRQ(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_HOSTDISCONDETECT_IRQ_SHIFT)) & USBPHY_CTRL_TOG_HOSTDISCONDETECT_IRQ_MASK)

#define USBPHY_CTRL_TOG_ENDEVPLUGINDET_MASK      (0x10U)
#define USBPHY_CTRL_TOG_ENDEVPLUGINDET_SHIFT     (4U)
/*! ENDEVPLUGINDET
 *  0b0..Disables 200kohm pullup resistors on USB_DP and USB_DM pins (Default)
 *  0b1..Enables 200kohm pullup resistors on USB_DP and USB_DM pins
 */
#define USBPHY_CTRL_TOG_ENDEVPLUGINDET(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENDEVPLUGINDET_SHIFT)) & USBPHY_CTRL_TOG_ENDEVPLUGINDET_MASK)

#define USBPHY_CTRL_TOG_DEVPLUGIN_POLARITY_MASK  (0x20U)
#define USBPHY_CTRL_TOG_DEVPLUGIN_POLARITY_SHIFT (5U)
#define USBPHY_CTRL_TOG_DEVPLUGIN_POLARITY(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_DEVPLUGIN_POLARITY_SHIFT)) & USBPHY_CTRL_TOG_DEVPLUGIN_POLARITY_MASK)

#define USBPHY_CTRL_TOG_RESUMEIRQSTICKY_MASK     (0x100U)
#define USBPHY_CTRL_TOG_RESUMEIRQSTICKY_SHIFT    (8U)
#define USBPHY_CTRL_TOG_RESUMEIRQSTICKY(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_RESUMEIRQSTICKY_SHIFT)) & USBPHY_CTRL_TOG_RESUMEIRQSTICKY_MASK)

#define USBPHY_CTRL_TOG_ENIRQRESUMEDETECT_MASK   (0x200U)
#define USBPHY_CTRL_TOG_ENIRQRESUMEDETECT_SHIFT  (9U)
#define USBPHY_CTRL_TOG_ENIRQRESUMEDETECT(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENIRQRESUMEDETECT_SHIFT)) & USBPHY_CTRL_TOG_ENIRQRESUMEDETECT_MASK)

#define USBPHY_CTRL_TOG_RESUME_IRQ_MASK          (0x400U)
#define USBPHY_CTRL_TOG_RESUME_IRQ_SHIFT         (10U)
#define USBPHY_CTRL_TOG_RESUME_IRQ(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_RESUME_IRQ_SHIFT)) & USBPHY_CTRL_TOG_RESUME_IRQ_MASK)

#define USBPHY_CTRL_TOG_DEVPLUGIN_IRQ_MASK       (0x1000U)
#define USBPHY_CTRL_TOG_DEVPLUGIN_IRQ_SHIFT      (12U)
#define USBPHY_CTRL_TOG_DEVPLUGIN_IRQ(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_DEVPLUGIN_IRQ_SHIFT)) & USBPHY_CTRL_TOG_DEVPLUGIN_IRQ_MASK)

#define USBPHY_CTRL_TOG_ENUTMILEVEL2_MASK        (0x4000U)
#define USBPHY_CTRL_TOG_ENUTMILEVEL2_SHIFT       (14U)
#define USBPHY_CTRL_TOG_ENUTMILEVEL2(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENUTMILEVEL2_SHIFT)) & USBPHY_CTRL_TOG_ENUTMILEVEL2_MASK)

#define USBPHY_CTRL_TOG_ENUTMILEVEL3_MASK        (0x8000U)
#define USBPHY_CTRL_TOG_ENUTMILEVEL3_SHIFT       (15U)
#define USBPHY_CTRL_TOG_ENUTMILEVEL3(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENUTMILEVEL3_SHIFT)) & USBPHY_CTRL_TOG_ENUTMILEVEL3_MASK)

#define USBPHY_CTRL_TOG_ENIRQWAKEUP_MASK         (0x10000U)
#define USBPHY_CTRL_TOG_ENIRQWAKEUP_SHIFT        (16U)
#define USBPHY_CTRL_TOG_ENIRQWAKEUP(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENIRQWAKEUP_SHIFT)) & USBPHY_CTRL_TOG_ENIRQWAKEUP_MASK)

#define USBPHY_CTRL_TOG_WAKEUP_IRQ_MASK          (0x20000U)
#define USBPHY_CTRL_TOG_WAKEUP_IRQ_SHIFT         (17U)
#define USBPHY_CTRL_TOG_WAKEUP_IRQ(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_WAKEUP_IRQ_SHIFT)) & USBPHY_CTRL_TOG_WAKEUP_IRQ_MASK)

#define USBPHY_CTRL_TOG_AUTORESUME_EN_MASK       (0x40000U)
#define USBPHY_CTRL_TOG_AUTORESUME_EN_SHIFT      (18U)
#define USBPHY_CTRL_TOG_AUTORESUME_EN(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_AUTORESUME_EN_SHIFT)) & USBPHY_CTRL_TOG_AUTORESUME_EN_MASK)

#define USBPHY_CTRL_TOG_ENAUTOCLR_CLKGATE_MASK   (0x80000U)
#define USBPHY_CTRL_TOG_ENAUTOCLR_CLKGATE_SHIFT  (19U)
#define USBPHY_CTRL_TOG_ENAUTOCLR_CLKGATE(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENAUTOCLR_CLKGATE_SHIFT)) & USBPHY_CTRL_TOG_ENAUTOCLR_CLKGATE_MASK)

#define USBPHY_CTRL_TOG_ENAUTOCLR_PHY_PWD_MASK   (0x100000U)
#define USBPHY_CTRL_TOG_ENAUTOCLR_PHY_PWD_SHIFT  (20U)
#define USBPHY_CTRL_TOG_ENAUTOCLR_PHY_PWD(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENAUTOCLR_PHY_PWD_SHIFT)) & USBPHY_CTRL_TOG_ENAUTOCLR_PHY_PWD_MASK)

#define USBPHY_CTRL_TOG_ENDPDMCHG_WKUP_MASK      (0x200000U)
#define USBPHY_CTRL_TOG_ENDPDMCHG_WKUP_SHIFT     (21U)
#define USBPHY_CTRL_TOG_ENDPDMCHG_WKUP(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENDPDMCHG_WKUP_SHIFT)) & USBPHY_CTRL_TOG_ENDPDMCHG_WKUP_MASK)

#define USBPHY_CTRL_TOG_ENVBUSCHG_WKUP_MASK      (0x800000U)
#define USBPHY_CTRL_TOG_ENVBUSCHG_WKUP_SHIFT     (23U)
#define USBPHY_CTRL_TOG_ENVBUSCHG_WKUP(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENVBUSCHG_WKUP_SHIFT)) & USBPHY_CTRL_TOG_ENVBUSCHG_WKUP_MASK)

#define USBPHY_CTRL_TOG_ENAUTOCLR_USBCLKGATE_MASK (0x2000000U)
#define USBPHY_CTRL_TOG_ENAUTOCLR_USBCLKGATE_SHIFT (25U)
#define USBPHY_CTRL_TOG_ENAUTOCLR_USBCLKGATE(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENAUTOCLR_USBCLKGATE_SHIFT)) & USBPHY_CTRL_TOG_ENAUTOCLR_USBCLKGATE_MASK)

#define USBPHY_CTRL_TOG_ENAUTOSET_USBCLKS_MASK   (0x4000000U)
#define USBPHY_CTRL_TOG_ENAUTOSET_USBCLKS_SHIFT  (26U)
#define USBPHY_CTRL_TOG_ENAUTOSET_USBCLKS(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENAUTOSET_USBCLKS_SHIFT)) & USBPHY_CTRL_TOG_ENAUTOSET_USBCLKS_MASK)

#define USBPHY_CTRL_TOG_HOST_FORCE_LS_SE0_MASK   (0x10000000U)
#define USBPHY_CTRL_TOG_HOST_FORCE_LS_SE0_SHIFT  (28U)
#define USBPHY_CTRL_TOG_HOST_FORCE_LS_SE0(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_HOST_FORCE_LS_SE0_SHIFT)) & USBPHY_CTRL_TOG_HOST_FORCE_LS_SE0_MASK)

#define USBPHY_CTRL_TOG_UTMI_SUSPENDM_MASK       (0x20000000U)
#define USBPHY_CTRL_TOG_UTMI_SUSPENDM_SHIFT      (29U)
#define USBPHY_CTRL_TOG_UTMI_SUSPENDM(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_UTMI_SUSPENDM_SHIFT)) & USBPHY_CTRL_TOG_UTMI_SUSPENDM_MASK)

#define USBPHY_CTRL_TOG_CLKGATE_MASK             (0x40000000U)
#define USBPHY_CTRL_TOG_CLKGATE_SHIFT            (30U)
#define USBPHY_CTRL_TOG_CLKGATE(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_CLKGATE_SHIFT)) & USBPHY_CTRL_TOG_CLKGATE_MASK)

#define USBPHY_CTRL_TOG_SFTRST_MASK              (0x80000000U)
#define USBPHY_CTRL_TOG_SFTRST_SHIFT             (31U)
#define USBPHY_CTRL_TOG_SFTRST(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_SFTRST_SHIFT)) & USBPHY_CTRL_TOG_SFTRST_MASK)
/*! @} */

/*! @name STATUS - USB PHY Status Register */
/*! @{ */

#define USBPHY_STATUS_OK_STATUS_3V_MASK          (0x1U)
#define USBPHY_STATUS_OK_STATUS_3V_SHIFT         (0U)
#define USBPHY_STATUS_OK_STATUS_3V(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_STATUS_OK_STATUS_3V_SHIFT)) & USBPHY_STATUS_OK_STATUS_3V_MASK)

#define USBPHY_STATUS_HOSTDISCONDETECT_STATUS_MASK (0x8U)
#define USBPHY_STATUS_HOSTDISCONDETECT_STATUS_SHIFT (3U)
/*! HOSTDISCONDETECT_STATUS
 *  0b0..USB cable disconnect has not been detected at the local host
 *  0b1..USB cable disconnect has been detected at the local host
 */
#define USBPHY_STATUS_HOSTDISCONDETECT_STATUS(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_STATUS_HOSTDISCONDETECT_STATUS_SHIFT)) & USBPHY_STATUS_HOSTDISCONDETECT_STATUS_MASK)

#define USBPHY_STATUS_DEVPLUGIN_STATUS_MASK      (0x40U)
#define USBPHY_STATUS_DEVPLUGIN_STATUS_SHIFT     (6U)
/*! DEVPLUGIN_STATUS
 *  0b0..No attachment to a USB host is detected
 *  0b1..Cable attachment to a USB host is detected
 */
#define USBPHY_STATUS_DEVPLUGIN_STATUS(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_STATUS_DEVPLUGIN_STATUS_SHIFT)) & USBPHY_STATUS_DEVPLUGIN_STATUS_MASK)

#define USBPHY_STATUS_RESUME_STATUS_MASK         (0x400U)
#define USBPHY_STATUS_RESUME_STATUS_SHIFT        (10U)
#define USBPHY_STATUS_RESUME_STATUS(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_STATUS_RESUME_STATUS_SHIFT)) & USBPHY_STATUS_RESUME_STATUS_MASK)
/*! @} */

/*! @name PLL_SIC - USB PHY PLL Control/Status Register */
/*! @{ */

#define USBPHY_PLL_SIC_PLL_EN_USB_CLKS_MASK      (0x40U)
#define USBPHY_PLL_SIC_PLL_EN_USB_CLKS_SHIFT     (6U)
#define USBPHY_PLL_SIC_PLL_EN_USB_CLKS(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_PLL_EN_USB_CLKS_SHIFT)) & USBPHY_PLL_SIC_PLL_EN_USB_CLKS_MASK)

#define USBPHY_PLL_SIC_PLL_POWER_MASK            (0x1000U)
#define USBPHY_PLL_SIC_PLL_POWER_SHIFT           (12U)
#define USBPHY_PLL_SIC_PLL_POWER(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_PLL_POWER_SHIFT)) & USBPHY_PLL_SIC_PLL_POWER_MASK)

#define USBPHY_PLL_SIC_PLL_ENABLE_MASK           (0x2000U)
#define USBPHY_PLL_SIC_PLL_ENABLE_SHIFT          (13U)
#define USBPHY_PLL_SIC_PLL_ENABLE(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_PLL_ENABLE_SHIFT)) & USBPHY_PLL_SIC_PLL_ENABLE_MASK)

#define USBPHY_PLL_SIC_REFBIAS_PWD_SEL_MASK      (0x80000U)
#define USBPHY_PLL_SIC_REFBIAS_PWD_SEL_SHIFT     (19U)
/*! REFBIAS_PWD_SEL
 *  0b0..Selects PLL_POWER to control the reference bias
 *  0b1..Selects REFBIAS_PWD to control the reference bias
 */
#define USBPHY_PLL_SIC_REFBIAS_PWD_SEL(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_REFBIAS_PWD_SEL_SHIFT)) & USBPHY_PLL_SIC_REFBIAS_PWD_SEL_MASK)

#define USBPHY_PLL_SIC_REFBIAS_PWD_MASK          (0x100000U)
#define USBPHY_PLL_SIC_REFBIAS_PWD_SHIFT         (20U)
#define USBPHY_PLL_SIC_REFBIAS_PWD(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_REFBIAS_PWD_SHIFT)) & USBPHY_PLL_SIC_REFBIAS_PWD_MASK)

#define USBPHY_PLL_SIC_PLL_REG_ENABLE_MASK       (0x200000U)
#define USBPHY_PLL_SIC_PLL_REG_ENABLE_SHIFT      (21U)
#define USBPHY_PLL_SIC_PLL_REG_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_PLL_REG_ENABLE_SHIFT)) & USBPHY_PLL_SIC_PLL_REG_ENABLE_MASK)

#define USBPHY_PLL_SIC_PLL_DIV_SEL_MASK          (0x1C00000U)
#define USBPHY_PLL_SIC_PLL_DIV_SEL_SHIFT         (22U)
/*! PLL_DIV_SEL
 *  0b000..Divide by 13
 *  0b001..Divide by 15
 *  0b010..Divide by 16
 *  0b011..Divide by 20
 *  0b100..Divide by 22
 *  0b101..Divide by 25
 *  0b110..Divide by 30
 *  0b111..Divide by 240
 */
#define USBPHY_PLL_SIC_PLL_DIV_SEL(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_PLL_DIV_SEL_SHIFT)) & USBPHY_PLL_SIC_PLL_DIV_SEL_MASK)

#define USBPHY_PLL_SIC_PLL_PREDIV_MASK           (0x40000000U)
#define USBPHY_PLL_SIC_PLL_PREDIV_SHIFT          (30U)
#define USBPHY_PLL_SIC_PLL_PREDIV(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_PLL_PREDIV_SHIFT)) & USBPHY_PLL_SIC_PLL_PREDIV_MASK)

#define USBPHY_PLL_SIC_PLL_LOCK_MASK             (0x80000000U)
#define USBPHY_PLL_SIC_PLL_LOCK_SHIFT            (31U)
/*! PLL_LOCK
 *  0b0..PLL is not currently locked
 *  0b1..PLL is currently locked
 */
#define USBPHY_PLL_SIC_PLL_LOCK(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_PLL_LOCK_SHIFT)) & USBPHY_PLL_SIC_PLL_LOCK_MASK)
/*! @} */

/*! @name PLL_SIC_SET - USB PHY PLL Control/Status Register */
/*! @{ */

#define USBPHY_PLL_SIC_SET_PLL_EN_USB_CLKS_MASK  (0x40U)
#define USBPHY_PLL_SIC_SET_PLL_EN_USB_CLKS_SHIFT (6U)
#define USBPHY_PLL_SIC_SET_PLL_EN_USB_CLKS(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_PLL_EN_USB_CLKS_SHIFT)) & USBPHY_PLL_SIC_SET_PLL_EN_USB_CLKS_MASK)

#define USBPHY_PLL_SIC_SET_PLL_POWER_MASK        (0x1000U)
#define USBPHY_PLL_SIC_SET_PLL_POWER_SHIFT       (12U)
#define USBPHY_PLL_SIC_SET_PLL_POWER(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_PLL_POWER_SHIFT)) & USBPHY_PLL_SIC_SET_PLL_POWER_MASK)

#define USBPHY_PLL_SIC_SET_PLL_ENABLE_MASK       (0x2000U)
#define USBPHY_PLL_SIC_SET_PLL_ENABLE_SHIFT      (13U)
#define USBPHY_PLL_SIC_SET_PLL_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_PLL_ENABLE_SHIFT)) & USBPHY_PLL_SIC_SET_PLL_ENABLE_MASK)

#define USBPHY_PLL_SIC_SET_REFBIAS_PWD_SEL_MASK  (0x80000U)
#define USBPHY_PLL_SIC_SET_REFBIAS_PWD_SEL_SHIFT (19U)
/*! REFBIAS_PWD_SEL
 *  0b0..Selects PLL_POWER to control the reference bias
 *  0b1..Selects REFBIAS_PWD to control the reference bias
 */
#define USBPHY_PLL_SIC_SET_REFBIAS_PWD_SEL(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_REFBIAS_PWD_SEL_SHIFT)) & USBPHY_PLL_SIC_SET_REFBIAS_PWD_SEL_MASK)

#define USBPHY_PLL_SIC_SET_REFBIAS_PWD_MASK      (0x100000U)
#define USBPHY_PLL_SIC_SET_REFBIAS_PWD_SHIFT     (20U)
#define USBPHY_PLL_SIC_SET_REFBIAS_PWD(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_REFBIAS_PWD_SHIFT)) & USBPHY_PLL_SIC_SET_REFBIAS_PWD_MASK)

#define USBPHY_PLL_SIC_SET_PLL_REG_ENABLE_MASK   (0x200000U)
#define USBPHY_PLL_SIC_SET_PLL_REG_ENABLE_SHIFT  (21U)
#define USBPHY_PLL_SIC_SET_PLL_REG_ENABLE(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_PLL_REG_ENABLE_SHIFT)) & USBPHY_PLL_SIC_SET_PLL_REG_ENABLE_MASK)

#define USBPHY_PLL_SIC_SET_PLL_DIV_SEL_MASK      (0x1C00000U)
#define USBPHY_PLL_SIC_SET_PLL_DIV_SEL_SHIFT     (22U)
/*! PLL_DIV_SEL
 *  0b000..Divide by 13
 *  0b001..Divide by 15
 *  0b010..Divide by 16
 *  0b011..Divide by 20
 *  0b100..Divide by 22
 *  0b101..Divide by 25
 *  0b110..Divide by 30
 *  0b111..Divide by 240
 */
#define USBPHY_PLL_SIC_SET_PLL_DIV_SEL(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_PLL_DIV_SEL_SHIFT)) & USBPHY_PLL_SIC_SET_PLL_DIV_SEL_MASK)

#define USBPHY_PLL_SIC_SET_PLL_PREDIV_MASK       (0x40000000U)
#define USBPHY_PLL_SIC_SET_PLL_PREDIV_SHIFT      (30U)
#define USBPHY_PLL_SIC_SET_PLL_PREDIV(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_PLL_PREDIV_SHIFT)) & USBPHY_PLL_SIC_SET_PLL_PREDIV_MASK)

#define USBPHY_PLL_SIC_SET_PLL_LOCK_MASK         (0x80000000U)
#define USBPHY_PLL_SIC_SET_PLL_LOCK_SHIFT        (31U)
/*! PLL_LOCK
 *  0b0..PLL is not currently locked
 *  0b1..PLL is currently locked
 */
#define USBPHY_PLL_SIC_SET_PLL_LOCK(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_PLL_LOCK_SHIFT)) & USBPHY_PLL_SIC_SET_PLL_LOCK_MASK)
/*! @} */

/*! @name PLL_SIC_CLR - USB PHY PLL Control/Status Register */
/*! @{ */

#define USBPHY_PLL_SIC_CLR_PLL_EN_USB_CLKS_MASK  (0x40U)
#define USBPHY_PLL_SIC_CLR_PLL_EN_USB_CLKS_SHIFT (6U)
#define USBPHY_PLL_SIC_CLR_PLL_EN_USB_CLKS(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_PLL_EN_USB_CLKS_SHIFT)) & USBPHY_PLL_SIC_CLR_PLL_EN_USB_CLKS_MASK)

#define USBPHY_PLL_SIC_CLR_PLL_POWER_MASK        (0x1000U)
#define USBPHY_PLL_SIC_CLR_PLL_POWER_SHIFT       (12U)
#define USBPHY_PLL_SIC_CLR_PLL_POWER(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_PLL_POWER_SHIFT)) & USBPHY_PLL_SIC_CLR_PLL_POWER_MASK)

#define USBPHY_PLL_SIC_CLR_PLL_ENABLE_MASK       (0x2000U)
#define USBPHY_PLL_SIC_CLR_PLL_ENABLE_SHIFT      (13U)
#define USBPHY_PLL_SIC_CLR_PLL_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_PLL_ENABLE_SHIFT)) & USBPHY_PLL_SIC_CLR_PLL_ENABLE_MASK)

#define USBPHY_PLL_SIC_CLR_REFBIAS_PWD_SEL_MASK  (0x80000U)
#define USBPHY_PLL_SIC_CLR_REFBIAS_PWD_SEL_SHIFT (19U)
/*! REFBIAS_PWD_SEL
 *  0b0..Selects PLL_POWER to control the reference bias
 *  0b1..Selects REFBIAS_PWD to control the reference bias
 */
#define USBPHY_PLL_SIC_CLR_REFBIAS_PWD_SEL(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_REFBIAS_PWD_SEL_SHIFT)) & USBPHY_PLL_SIC_CLR_REFBIAS_PWD_SEL_MASK)

#define USBPHY_PLL_SIC_CLR_REFBIAS_PWD_MASK      (0x100000U)
#define USBPHY_PLL_SIC_CLR_REFBIAS_PWD_SHIFT     (20U)
#define USBPHY_PLL_SIC_CLR_REFBIAS_PWD(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_REFBIAS_PWD_SHIFT)) & USBPHY_PLL_SIC_CLR_REFBIAS_PWD_MASK)

#define USBPHY_PLL_SIC_CLR_PLL_REG_ENABLE_MASK   (0x200000U)
#define USBPHY_PLL_SIC_CLR_PLL_REG_ENABLE_SHIFT  (21U)
#define USBPHY_PLL_SIC_CLR_PLL_REG_ENABLE(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_PLL_REG_ENABLE_SHIFT)) & USBPHY_PLL_SIC_CLR_PLL_REG_ENABLE_MASK)

#define USBPHY_PLL_SIC_CLR_PLL_DIV_SEL_MASK      (0x1C00000U)
#define USBPHY_PLL_SIC_CLR_PLL_DIV_SEL_SHIFT     (22U)
/*! PLL_DIV_SEL
 *  0b000..Divide by 13
 *  0b001..Divide by 15
 *  0b010..Divide by 16
 *  0b011..Divide by 20
 *  0b100..Divide by 22
 *  0b101..Divide by 25
 *  0b110..Divide by 30
 *  0b111..Divide by 240
 */
#define USBPHY_PLL_SIC_CLR_PLL_DIV_SEL(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_PLL_DIV_SEL_SHIFT)) & USBPHY_PLL_SIC_CLR_PLL_DIV_SEL_MASK)

#define USBPHY_PLL_SIC_CLR_PLL_PREDIV_MASK       (0x40000000U)
#define USBPHY_PLL_SIC_CLR_PLL_PREDIV_SHIFT      (30U)
#define USBPHY_PLL_SIC_CLR_PLL_PREDIV(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_PLL_PREDIV_SHIFT)) & USBPHY_PLL_SIC_CLR_PLL_PREDIV_MASK)

#define USBPHY_PLL_SIC_CLR_PLL_LOCK_MASK         (0x80000000U)
#define USBPHY_PLL_SIC_CLR_PLL_LOCK_SHIFT        (31U)
/*! PLL_LOCK
 *  0b0..PLL is not currently locked
 *  0b1..PLL is currently locked
 */
#define USBPHY_PLL_SIC_CLR_PLL_LOCK(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_PLL_LOCK_SHIFT)) & USBPHY_PLL_SIC_CLR_PLL_LOCK_MASK)
/*! @} */

/*! @name PLL_SIC_TOG - USB PHY PLL Control/Status Register */
/*! @{ */

#define USBPHY_PLL_SIC_TOG_PLL_EN_USB_CLKS_MASK  (0x40U)
#define USBPHY_PLL_SIC_TOG_PLL_EN_USB_CLKS_SHIFT (6U)
#define USBPHY_PLL_SIC_TOG_PLL_EN_USB_CLKS(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_PLL_EN_USB_CLKS_SHIFT)) & USBPHY_PLL_SIC_TOG_PLL_EN_USB_CLKS_MASK)

#define USBPHY_PLL_SIC_TOG_PLL_POWER_MASK        (0x1000U)
#define USBPHY_PLL_SIC_TOG_PLL_POWER_SHIFT       (12U)
#define USBPHY_PLL_SIC_TOG_PLL_POWER(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_PLL_POWER_SHIFT)) & USBPHY_PLL_SIC_TOG_PLL_POWER_MASK)

#define USBPHY_PLL_SIC_TOG_PLL_ENABLE_MASK       (0x2000U)
#define USBPHY_PLL_SIC_TOG_PLL_ENABLE_SHIFT      (13U)
#define USBPHY_PLL_SIC_TOG_PLL_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_PLL_ENABLE_SHIFT)) & USBPHY_PLL_SIC_TOG_PLL_ENABLE_MASK)

#define USBPHY_PLL_SIC_TOG_REFBIAS_PWD_SEL_MASK  (0x80000U)
#define USBPHY_PLL_SIC_TOG_REFBIAS_PWD_SEL_SHIFT (19U)
/*! REFBIAS_PWD_SEL
 *  0b0..Selects PLL_POWER to control the reference bias
 *  0b1..Selects REFBIAS_PWD to control the reference bias
 */
#define USBPHY_PLL_SIC_TOG_REFBIAS_PWD_SEL(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_REFBIAS_PWD_SEL_SHIFT)) & USBPHY_PLL_SIC_TOG_REFBIAS_PWD_SEL_MASK)

#define USBPHY_PLL_SIC_TOG_REFBIAS_PWD_MASK      (0x100000U)
#define USBPHY_PLL_SIC_TOG_REFBIAS_PWD_SHIFT     (20U)
#define USBPHY_PLL_SIC_TOG_REFBIAS_PWD(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_REFBIAS_PWD_SHIFT)) & USBPHY_PLL_SIC_TOG_REFBIAS_PWD_MASK)

#define USBPHY_PLL_SIC_TOG_PLL_REG_ENABLE_MASK   (0x200000U)
#define USBPHY_PLL_SIC_TOG_PLL_REG_ENABLE_SHIFT  (21U)
#define USBPHY_PLL_SIC_TOG_PLL_REG_ENABLE(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_PLL_REG_ENABLE_SHIFT)) & USBPHY_PLL_SIC_TOG_PLL_REG_ENABLE_MASK)

#define USBPHY_PLL_SIC_TOG_PLL_DIV_SEL_MASK      (0x1C00000U)
#define USBPHY_PLL_SIC_TOG_PLL_DIV_SEL_SHIFT     (22U)
/*! PLL_DIV_SEL
 *  0b000..Divide by 13
 *  0b001..Divide by 15
 *  0b010..Divide by 16
 *  0b011..Divide by 20
 *  0b100..Divide by 22
 *  0b101..Divide by 25
 *  0b110..Divide by 30
 *  0b111..Divide by 240
 */
#define USBPHY_PLL_SIC_TOG_PLL_DIV_SEL(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_PLL_DIV_SEL_SHIFT)) & USBPHY_PLL_SIC_TOG_PLL_DIV_SEL_MASK)

#define USBPHY_PLL_SIC_TOG_PLL_PREDIV_MASK       (0x40000000U)
#define USBPHY_PLL_SIC_TOG_PLL_PREDIV_SHIFT      (30U)
#define USBPHY_PLL_SIC_TOG_PLL_PREDIV(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_PLL_PREDIV_SHIFT)) & USBPHY_PLL_SIC_TOG_PLL_PREDIV_MASK)

#define USBPHY_PLL_SIC_TOG_PLL_LOCK_MASK         (0x80000000U)
#define USBPHY_PLL_SIC_TOG_PLL_LOCK_SHIFT        (31U)
/*! PLL_LOCK
 *  0b0..PLL is not currently locked
 *  0b1..PLL is currently locked
 */
#define USBPHY_PLL_SIC_TOG_PLL_LOCK(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_PLL_LOCK_SHIFT)) & USBPHY_PLL_SIC_TOG_PLL_LOCK_MASK)
/*! @} */

/*! @name USB1_VBUS_DETECT - USB PHY VBUS Detect Control Register */
/*! @{ */

#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_THRESH_MASK (0x7U)
#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_THRESH_SHIFT (0U)
/*! VBUSVALID_THRESH
 *  0b000..4.0V
 *  0b001..4.1V
 *  0b010..4.2V
 *  0b011..4.3V
 *  0b100..4.4V(Default)
 *  0b101..4.5V
 *  0b110..4.6V
 *  0b111..4.7V
 */
#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_THRESH(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_VBUSVALID_THRESH_SHIFT)) & USBPHY_USB1_VBUS_DETECT_VBUSVALID_THRESH_MASK)

#define USBPHY_USB1_VBUS_DETECT_VBUS_OVERRIDE_EN_MASK (0x8U)
#define USBPHY_USB1_VBUS_DETECT_VBUS_OVERRIDE_EN_SHIFT (3U)
/*! VBUS_OVERRIDE_EN
 *  0b0..Use the results of the internal VBUS_VALID and Session Valid comparators for VBUS_VALID, AVALID, BVALID, and SESSEND (Default)
 *  0b1..Use the override values for VBUS_VALID, AVALID, BVALID, and SESSEND
 */
#define USBPHY_USB1_VBUS_DETECT_VBUS_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_VBUS_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_VBUS_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_SESSEND_OVERRIDE_MASK (0x10U)
#define USBPHY_USB1_VBUS_DETECT_SESSEND_OVERRIDE_SHIFT (4U)
#define USBPHY_USB1_VBUS_DETECT_SESSEND_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SESSEND_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SESSEND_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_BVALID_OVERRIDE_MASK (0x20U)
#define USBPHY_USB1_VBUS_DETECT_BVALID_OVERRIDE_SHIFT (5U)
#define USBPHY_USB1_VBUS_DETECT_BVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_BVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_BVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_AVALID_OVERRIDE_MASK (0x40U)
#define USBPHY_USB1_VBUS_DETECT_AVALID_OVERRIDE_SHIFT (6U)
#define USBPHY_USB1_VBUS_DETECT_AVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_AVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_AVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_OVERRIDE_MASK (0x80U)
#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_OVERRIDE_SHIFT (7U)
#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_VBUSVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_VBUSVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_SEL_MASK (0x100U)
#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_SEL_SHIFT (8U)
/*! VBUSVALID_SEL
 *  0b0..Use the VBUS_VALID comparator results for signal reported to the USB controller (Default)
 *  0b1..Use the VBUS_VALID_3V detector results for signal reported to the USB controller
 */
#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_VBUSVALID_SEL_SHIFT)) & USBPHY_USB1_VBUS_DETECT_VBUSVALID_SEL_MASK)

#define USBPHY_USB1_VBUS_DETECT_VBUS_SOURCE_SEL_MASK (0x600U)
#define USBPHY_USB1_VBUS_DETECT_VBUS_SOURCE_SEL_SHIFT (9U)
/*! VBUS_SOURCE_SEL
 *  0b00..Use the VBUS_VALID comparator results for signal reported to the USB controller (Default)
 *  0b01..Use the Session Valid comparator results for signal reported to the USB controller
 *  0b10..Use the Session Valid comparator results for signal reported to the USB controller
 *  0b11..Reserved, do not use
 */
#define USBPHY_USB1_VBUS_DETECT_VBUS_SOURCE_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_VBUS_SOURCE_SEL_SHIFT)) & USBPHY_USB1_VBUS_DETECT_VBUS_SOURCE_SEL_MASK)

#define USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_EN_MASK (0x800U)
#define USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_EN_SHIFT (11U)
#define USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_MASK (0x1000U)
#define USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_SHIFT (12U)
#define USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE(x)   (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_EXT_ID_OVERRIDE_EN_MASK (0x2000U)
#define USBPHY_USB1_VBUS_DETECT_EXT_ID_OVERRIDE_EN_SHIFT (13U)
/*! EXT_ID_OVERRIDE_EN
 *  0b0..Select the Muxed value chosen using ID_OVERRIDE_EN.
 *  0b1..Select the external ID value.
 */
#define USBPHY_USB1_VBUS_DETECT_EXT_ID_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_EXT_ID_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_EXT_ID_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_EXT_VBUS_OVERRIDE_EN_MASK (0x4000U)
#define USBPHY_USB1_VBUS_DETECT_EXT_VBUS_OVERRIDE_EN_SHIFT (14U)
/*! EXT_VBUS_OVERRIDE_EN
 *  0b0..Select the Muxed value chosen using VBUS_OVERRIDE_EN.
 *  0b1..Select the external VBUS VALID value.
 */
#define USBPHY_USB1_VBUS_DETECT_EXT_VBUS_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_EXT_VBUS_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_EXT_VBUS_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_TO_SESSVALID_MASK (0x40000U)
#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_TO_SESSVALID_SHIFT (18U)
/*! VBUSVALID_TO_SESSVALID
 *  0b0..Use the VBUS_VALID comparator for VBUS_VALID results
 *  0b1..Use the Session End comparator for VBUS_VALID results. The Session End threshold is >0.8V and <4.0V.
 */
#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_TO_SESSVALID(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_VBUSVALID_TO_SESSVALID_SHIFT)) & USBPHY_USB1_VBUS_DETECT_VBUSVALID_TO_SESSVALID_MASK)

#define USBPHY_USB1_VBUS_DETECT_PWRUP_CMPS_MASK  (0x700000U)
#define USBPHY_USB1_VBUS_DETECT_PWRUP_CMPS_SHIFT (20U)
/*! PWRUP_CMPS
 *  0b000..Powers down the VBUS_VALID comparator
 *  0b111..Enables the VBUS_VALID comparator (default)
 */
#define USBPHY_USB1_VBUS_DETECT_PWRUP_CMPS(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_PWRUP_CMPS_SHIFT)) & USBPHY_USB1_VBUS_DETECT_PWRUP_CMPS_MASK)

#define USBPHY_USB1_VBUS_DETECT_DISCHARGE_VBUS_MASK (0x4000000U)
#define USBPHY_USB1_VBUS_DETECT_DISCHARGE_VBUS_SHIFT (26U)
/*! DISCHARGE_VBUS
 *  0b0..VBUS discharge resistor is disabled (Default)
 *  0b1..VBUS discharge resistor is enabled
 */
#define USBPHY_USB1_VBUS_DETECT_DISCHARGE_VBUS(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_DISCHARGE_VBUS_SHIFT)) & USBPHY_USB1_VBUS_DETECT_DISCHARGE_VBUS_MASK)
/*! @} */

/*! @name USB1_VBUS_DETECT_SET - USB PHY VBUS Detect Control Register */
/*! @{ */

#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_THRESH_MASK (0x7U)
#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_THRESH_SHIFT (0U)
/*! VBUSVALID_THRESH
 *  0b000..4.0V
 *  0b001..4.1V
 *  0b010..4.2V
 *  0b011..4.3V
 *  0b100..4.4V(Default)
 *  0b101..4.5V
 *  0b110..4.6V
 *  0b111..4.7V
 */
#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_THRESH(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_THRESH_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_THRESH_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_VBUS_OVERRIDE_EN_MASK (0x8U)
#define USBPHY_USB1_VBUS_DETECT_SET_VBUS_OVERRIDE_EN_SHIFT (3U)
/*! VBUS_OVERRIDE_EN
 *  0b0..Use the results of the internal VBUS_VALID and Session Valid comparators for VBUS_VALID, AVALID, BVALID, and SESSEND (Default)
 *  0b1..Use the override values for VBUS_VALID, AVALID, BVALID, and SESSEND
 */
#define USBPHY_USB1_VBUS_DETECT_SET_VBUS_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_VBUS_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_VBUS_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_SESSEND_OVERRIDE_MASK (0x10U)
#define USBPHY_USB1_VBUS_DETECT_SET_SESSEND_OVERRIDE_SHIFT (4U)
#define USBPHY_USB1_VBUS_DETECT_SET_SESSEND_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_SESSEND_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_SESSEND_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_BVALID_OVERRIDE_MASK (0x20U)
#define USBPHY_USB1_VBUS_DETECT_SET_BVALID_OVERRIDE_SHIFT (5U)
#define USBPHY_USB1_VBUS_DETECT_SET_BVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_BVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_BVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_AVALID_OVERRIDE_MASK (0x40U)
#define USBPHY_USB1_VBUS_DETECT_SET_AVALID_OVERRIDE_SHIFT (6U)
#define USBPHY_USB1_VBUS_DETECT_SET_AVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_AVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_AVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_OVERRIDE_MASK (0x80U)
#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_OVERRIDE_SHIFT (7U)
#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_SEL_MASK (0x100U)
#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_SEL_SHIFT (8U)
/*! VBUSVALID_SEL
 *  0b0..Use the VBUS_VALID comparator results for signal reported to the USB controller (Default)
 *  0b1..Use the VBUS_VALID_3V detector results for signal reported to the USB controller
 */
#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_SEL_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_SEL_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_VBUS_SOURCE_SEL_MASK (0x600U)
#define USBPHY_USB1_VBUS_DETECT_SET_VBUS_SOURCE_SEL_SHIFT (9U)
/*! VBUS_SOURCE_SEL
 *  0b00..Use the VBUS_VALID comparator results for signal reported to the USB controller (Default)
 *  0b01..Use the Session Valid comparator results for signal reported to the USB controller
 *  0b10..Use the Session Valid comparator results for signal reported to the USB controller
 *  0b11..Reserved, do not use
 */
#define USBPHY_USB1_VBUS_DETECT_SET_VBUS_SOURCE_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_VBUS_SOURCE_SEL_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_VBUS_SOURCE_SEL_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_EN_MASK (0x800U)
#define USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_EN_SHIFT (11U)
#define USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_MASK (0x1000U)
#define USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_SHIFT (12U)
#define USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_EXT_ID_OVERRIDE_EN_MASK (0x2000U)
#define USBPHY_USB1_VBUS_DETECT_SET_EXT_ID_OVERRIDE_EN_SHIFT (13U)
/*! EXT_ID_OVERRIDE_EN
 *  0b0..Select the Muxed value chosen using ID_OVERRIDE_EN.
 *  0b1..Select the external ID value.
 */
#define USBPHY_USB1_VBUS_DETECT_SET_EXT_ID_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_EXT_ID_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_EXT_ID_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_EXT_VBUS_OVERRIDE_EN_MASK (0x4000U)
#define USBPHY_USB1_VBUS_DETECT_SET_EXT_VBUS_OVERRIDE_EN_SHIFT (14U)
/*! EXT_VBUS_OVERRIDE_EN
 *  0b0..Select the Muxed value chosen using VBUS_OVERRIDE_EN.
 *  0b1..Select the external VBUS VALID value.
 */
#define USBPHY_USB1_VBUS_DETECT_SET_EXT_VBUS_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_EXT_VBUS_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_EXT_VBUS_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_TO_SESSVALID_MASK (0x40000U)
#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_TO_SESSVALID_SHIFT (18U)
/*! VBUSVALID_TO_SESSVALID
 *  0b0..Use the VBUS_VALID comparator for VBUS_VALID results
 *  0b1..Use the Session End comparator for VBUS_VALID results. The Session End threshold is >0.8V and <4.0V.
 */
#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_TO_SESSVALID(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_TO_SESSVALID_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_TO_SESSVALID_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_PWRUP_CMPS_MASK (0x700000U)
#define USBPHY_USB1_VBUS_DETECT_SET_PWRUP_CMPS_SHIFT (20U)
/*! PWRUP_CMPS
 *  0b000..Powers down the VBUS_VALID comparator
 *  0b111..Enables the VBUS_VALID comparator (default)
 */
#define USBPHY_USB1_VBUS_DETECT_SET_PWRUP_CMPS(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_PWRUP_CMPS_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_PWRUP_CMPS_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_DISCHARGE_VBUS_MASK (0x4000000U)
#define USBPHY_USB1_VBUS_DETECT_SET_DISCHARGE_VBUS_SHIFT (26U)
/*! DISCHARGE_VBUS
 *  0b0..VBUS discharge resistor is disabled (Default)
 *  0b1..VBUS discharge resistor is enabled
 */
#define USBPHY_USB1_VBUS_DETECT_SET_DISCHARGE_VBUS(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_DISCHARGE_VBUS_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_DISCHARGE_VBUS_MASK)
/*! @} */

/*! @name USB1_VBUS_DETECT_CLR - USB PHY VBUS Detect Control Register */
/*! @{ */

#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_THRESH_MASK (0x7U)
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_THRESH_SHIFT (0U)
/*! VBUSVALID_THRESH
 *  0b000..4.0V
 *  0b001..4.1V
 *  0b010..4.2V
 *  0b011..4.3V
 *  0b100..4.4V(Default)
 *  0b101..4.5V
 *  0b110..4.6V
 *  0b111..4.7V
 */
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_THRESH(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_THRESH_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_THRESH_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_VBUS_OVERRIDE_EN_MASK (0x8U)
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUS_OVERRIDE_EN_SHIFT (3U)
/*! VBUS_OVERRIDE_EN
 *  0b0..Use the results of the internal VBUS_VALID and Session Valid comparators for VBUS_VALID, AVALID, BVALID, and SESSEND (Default)
 *  0b1..Use the override values for VBUS_VALID, AVALID, BVALID, and SESSEND
 */
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUS_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_VBUS_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_VBUS_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_SESSEND_OVERRIDE_MASK (0x10U)
#define USBPHY_USB1_VBUS_DETECT_CLR_SESSEND_OVERRIDE_SHIFT (4U)
#define USBPHY_USB1_VBUS_DETECT_CLR_SESSEND_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_SESSEND_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_SESSEND_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_BVALID_OVERRIDE_MASK (0x20U)
#define USBPHY_USB1_VBUS_DETECT_CLR_BVALID_OVERRIDE_SHIFT (5U)
#define USBPHY_USB1_VBUS_DETECT_CLR_BVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_BVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_BVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_AVALID_OVERRIDE_MASK (0x40U)
#define USBPHY_USB1_VBUS_DETECT_CLR_AVALID_OVERRIDE_SHIFT (6U)
#define USBPHY_USB1_VBUS_DETECT_CLR_AVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_AVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_AVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_OVERRIDE_MASK (0x80U)
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_OVERRIDE_SHIFT (7U)
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_SEL_MASK (0x100U)
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_SEL_SHIFT (8U)
/*! VBUSVALID_SEL
 *  0b0..Use the VBUS_VALID comparator results for signal reported to the USB controller (Default)
 *  0b1..Use the VBUS_VALID_3V detector results for signal reported to the USB controller
 */
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_SEL_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_SEL_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_VBUS_SOURCE_SEL_MASK (0x600U)
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUS_SOURCE_SEL_SHIFT (9U)
/*! VBUS_SOURCE_SEL
 *  0b00..Use the VBUS_VALID comparator results for signal reported to the USB controller (Default)
 *  0b01..Use the Session Valid comparator results for signal reported to the USB controller
 *  0b10..Use the Session Valid comparator results for signal reported to the USB controller
 *  0b11..Reserved, do not use
 */
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUS_SOURCE_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_VBUS_SOURCE_SEL_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_VBUS_SOURCE_SEL_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_EN_MASK (0x800U)
#define USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_EN_SHIFT (11U)
#define USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_MASK (0x1000U)
#define USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_SHIFT (12U)
#define USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_EXT_ID_OVERRIDE_EN_MASK (0x2000U)
#define USBPHY_USB1_VBUS_DETECT_CLR_EXT_ID_OVERRIDE_EN_SHIFT (13U)
/*! EXT_ID_OVERRIDE_EN
 *  0b0..Select the Muxed value chosen using ID_OVERRIDE_EN.
 *  0b1..Select the external ID value.
 */
#define USBPHY_USB1_VBUS_DETECT_CLR_EXT_ID_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_EXT_ID_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_EXT_ID_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_EXT_VBUS_OVERRIDE_EN_MASK (0x4000U)
#define USBPHY_USB1_VBUS_DETECT_CLR_EXT_VBUS_OVERRIDE_EN_SHIFT (14U)
/*! EXT_VBUS_OVERRIDE_EN
 *  0b0..Select the muxed value chosen using VBUS_OVERRIDE_EN.
 *  0b1..Select the external VBUS VALID value.
 */
#define USBPHY_USB1_VBUS_DETECT_CLR_EXT_VBUS_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_EXT_VBUS_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_EXT_VBUS_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_TO_SESSVALID_MASK (0x40000U)
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_TO_SESSVALID_SHIFT (18U)
/*! VBUSVALID_TO_SESSVALID
 *  0b0..Use the VBUS_VALID comparator for VBUS_VALID results
 *  0b1..Use the Session End comparator for VBUS_VALID results. The Session End threshold is >0.8V and <4.0V.
 */
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_TO_SESSVALID(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_TO_SESSVALID_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_TO_SESSVALID_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_PWRUP_CMPS_MASK (0x700000U)
#define USBPHY_USB1_VBUS_DETECT_CLR_PWRUP_CMPS_SHIFT (20U)
/*! PWRUP_CMPS
 *  0b000..Powers down the VBUS_VALID comparator
 *  0b111..Enables the VBUS_VALID comparator (default)
 */
#define USBPHY_USB1_VBUS_DETECT_CLR_PWRUP_CMPS(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_PWRUP_CMPS_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_PWRUP_CMPS_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_DISCHARGE_VBUS_MASK (0x4000000U)
#define USBPHY_USB1_VBUS_DETECT_CLR_DISCHARGE_VBUS_SHIFT (26U)
/*! DISCHARGE_VBUS
 *  0b0..VBUS discharge resistor is disabled (Default)
 *  0b1..VBUS discharge resistor is enabled
 */
#define USBPHY_USB1_VBUS_DETECT_CLR_DISCHARGE_VBUS(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_DISCHARGE_VBUS_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_DISCHARGE_VBUS_MASK)
/*! @} */

/*! @name USB1_VBUS_DETECT_TOG - USB PHY VBUS Detect Control Register */
/*! @{ */

#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_THRESH_MASK (0x7U)
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_THRESH_SHIFT (0U)
/*! VBUSVALID_THRESH
 *  0b000..4.0V
 *  0b001..4.1V
 *  0b010..4.2V
 *  0b011..4.3V
 *  0b100..4.4V(Default)
 *  0b101..4.5V
 *  0b110..4.6V
 *  0b111..4.7V
 */
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_THRESH(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_THRESH_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_THRESH_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_VBUS_OVERRIDE_EN_MASK (0x8U)
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUS_OVERRIDE_EN_SHIFT (3U)
/*! VBUS_OVERRIDE_EN
 *  0b0..Use the results of the internal VBUS_VALID and Session Valid comparators for VBUS_VALID, AVALID, BVALID, and SESSEND (Default)
 *  0b1..Use the override values for VBUS_VALID, AVALID, BVALID, and SESSEND
 */
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUS_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_VBUS_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_VBUS_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_SESSEND_OVERRIDE_MASK (0x10U)
#define USBPHY_USB1_VBUS_DETECT_TOG_SESSEND_OVERRIDE_SHIFT (4U)
#define USBPHY_USB1_VBUS_DETECT_TOG_SESSEND_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_SESSEND_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_SESSEND_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_BVALID_OVERRIDE_MASK (0x20U)
#define USBPHY_USB1_VBUS_DETECT_TOG_BVALID_OVERRIDE_SHIFT (5U)
#define USBPHY_USB1_VBUS_DETECT_TOG_BVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_BVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_BVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_AVALID_OVERRIDE_MASK (0x40U)
#define USBPHY_USB1_VBUS_DETECT_TOG_AVALID_OVERRIDE_SHIFT (6U)
#define USBPHY_USB1_VBUS_DETECT_TOG_AVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_AVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_AVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_OVERRIDE_MASK (0x80U)
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_OVERRIDE_SHIFT (7U)
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_SEL_MASK (0x100U)
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_SEL_SHIFT (8U)
/*! VBUSVALID_SEL
 *  0b0..Use the VBUS_VALID comparator results for signal reported to the USB controller (Default)
 *  0b1..Use the VBUS_VALID_3V detector results for signal reported to the USB controller
 */
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_SEL_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_SEL_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_VBUS_SOURCE_SEL_MASK (0x600U)
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUS_SOURCE_SEL_SHIFT (9U)
/*! VBUS_SOURCE_SEL
 *  0b00..Use the VBUS_VALID comparator results for signal reported to the USB controller (Default)
 *  0b01..Use the Session Valid comparator results for signal reported to the USB controller
 *  0b10..Use the Session Valid comparator results for signal reported to the USB controller
 *  0b11..Reserved, do not use
 */
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUS_SOURCE_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_VBUS_SOURCE_SEL_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_VBUS_SOURCE_SEL_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_EN_MASK (0x800U)
#define USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_EN_SHIFT (11U)
#define USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_MASK (0x1000U)
#define USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_SHIFT (12U)
#define USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_EXT_ID_OVERRIDE_EN_MASK (0x2000U)
#define USBPHY_USB1_VBUS_DETECT_TOG_EXT_ID_OVERRIDE_EN_SHIFT (13U)
/*! EXT_ID_OVERRIDE_EN
 *  0b0..Select the muxed value chosen using ID_OVERRIDE_EN.
 *  0b1..Select the external ID value.
 */
#define USBPHY_USB1_VBUS_DETECT_TOG_EXT_ID_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_EXT_ID_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_EXT_ID_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_EXT_VBUS_OVERRIDE_EN_MASK (0x4000U)
#define USBPHY_USB1_VBUS_DETECT_TOG_EXT_VBUS_OVERRIDE_EN_SHIFT (14U)
/*! EXT_VBUS_OVERRIDE_EN
 *  0b0..Select the Muxed value chosen using VBUS_OVERRIDE_EN.
 *  0b1..Select the external VBUS VALID value.
 */
#define USBPHY_USB1_VBUS_DETECT_TOG_EXT_VBUS_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_EXT_VBUS_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_EXT_VBUS_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_TO_SESSVALID_MASK (0x40000U)
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_TO_SESSVALID_SHIFT (18U)
/*! VBUSVALID_TO_SESSVALID
 *  0b0..Use the VBUS_VALID comparator for VBUS_VALID results
 *  0b1..Use the Session End comparator for VBUS_VALID results. The Session End threshold is >0.8V and <4.0V.
 */
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_TO_SESSVALID(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_TO_SESSVALID_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_TO_SESSVALID_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_PWRUP_CMPS_MASK (0x700000U)
#define USBPHY_USB1_VBUS_DETECT_TOG_PWRUP_CMPS_SHIFT (20U)
/*! PWRUP_CMPS
 *  0b000..Powers down the VBUS_VALID comparator
 *  0b111..Enables the VBUS_VALID comparator (default)
 */
#define USBPHY_USB1_VBUS_DETECT_TOG_PWRUP_CMPS(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_PWRUP_CMPS_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_PWRUP_CMPS_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_DISCHARGE_VBUS_MASK (0x4000000U)
#define USBPHY_USB1_VBUS_DETECT_TOG_DISCHARGE_VBUS_SHIFT (26U)
/*! DISCHARGE_VBUS
 *  0b0..VBUS discharge resistor is disabled (Default)
 *  0b1..VBUS discharge resistor is enabled
 */
#define USBPHY_USB1_VBUS_DETECT_TOG_DISCHARGE_VBUS(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_DISCHARGE_VBUS_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_DISCHARGE_VBUS_MASK)
/*! @} */

/*! @name USB1_VBUS_DET_STAT - USB PHY VBUS Detector Status Register */
/*! @{ */

#define USBPHY_USB1_VBUS_DET_STAT_SESSEND_MASK   (0x1U)
#define USBPHY_USB1_VBUS_DET_STAT_SESSEND_SHIFT  (0U)
/*! SESSEND
 *  0b0..The VBUS voltage is above the Session Valid threshold
 *  0b1..The VBUS voltage is below the Session Valid threshold
 */
#define USBPHY_USB1_VBUS_DET_STAT_SESSEND(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DET_STAT_SESSEND_SHIFT)) & USBPHY_USB1_VBUS_DET_STAT_SESSEND_MASK)

#define USBPHY_USB1_VBUS_DET_STAT_BVALID_MASK    (0x2U)
#define USBPHY_USB1_VBUS_DET_STAT_BVALID_SHIFT   (1U)
/*! BVALID
 *  0b0..The VBUS voltage is below the Session Valid threshold
 *  0b1..The VBUS voltage is above the Session Valid threshold
 */
#define USBPHY_USB1_VBUS_DET_STAT_BVALID(x)      (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DET_STAT_BVALID_SHIFT)) & USBPHY_USB1_VBUS_DET_STAT_BVALID_MASK)

#define USBPHY_USB1_VBUS_DET_STAT_AVALID_MASK    (0x4U)
#define USBPHY_USB1_VBUS_DET_STAT_AVALID_SHIFT   (2U)
/*! AVALID
 *  0b0..The VBUS voltage is below the Session Valid threshold
 *  0b1..The VBUS voltage is above the Session Valid threshold
 */
#define USBPHY_USB1_VBUS_DET_STAT_AVALID(x)      (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DET_STAT_AVALID_SHIFT)) & USBPHY_USB1_VBUS_DET_STAT_AVALID_MASK)

#define USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_MASK (0x8U)
#define USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_SHIFT (3U)
/*! VBUS_VALID
 *  0b0..VBUS is below the comparator threshold
 *  0b1..VBUS is above the comparator threshold
 */
#define USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_SHIFT)) & USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_MASK)

#define USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_3V_MASK (0x10U)
#define USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_3V_SHIFT (4U)
/*! VBUS_VALID_3V
 *  0b0..VBUS voltage is below VBUS_VALID_3V threshold
 *  0b1..VBUS voltage is above VBUS_VALID_3V threshold
 */
#define USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_3V(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_3V_SHIFT)) & USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_3V_MASK)
/*! @} */

/*! @name ANACTRL - USB PHY Analog Control Register */
/*! @{ */

#define USBPHY_ANACTRL_LVI_EN_MASK               (0x2U)
#define USBPHY_ANACTRL_LVI_EN_SHIFT              (1U)
#define USBPHY_ANACTRL_LVI_EN(x)                 (((uint32_t)(((uint32_t)(x)) << USBPHY_ANACTRL_LVI_EN_SHIFT)) & USBPHY_ANACTRL_LVI_EN_MASK)

#define USBPHY_ANACTRL_PFD_CLK_SEL_MASK          (0xCU)
#define USBPHY_ANACTRL_PFD_CLK_SEL_SHIFT         (2U)
#define USBPHY_ANACTRL_PFD_CLK_SEL(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_ANACTRL_PFD_CLK_SEL_SHIFT)) & USBPHY_ANACTRL_PFD_CLK_SEL_MASK)

#define USBPHY_ANACTRL_DEV_PULLDOWN_MASK         (0x400U)
#define USBPHY_ANACTRL_DEV_PULLDOWN_SHIFT        (10U)
/*! DEV_PULLDOWN
 *  0b0..The 15kohm nominal pulldowns on the USB_DP and USB_DM pinsare disabled in device mode.
 *  0b1..The 15kohm nominal pulldowns on the USB_DP and USB_DM pinsare enabled in device mode.
 */
#define USBPHY_ANACTRL_DEV_PULLDOWN(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_ANACTRL_DEV_PULLDOWN_SHIFT)) & USBPHY_ANACTRL_DEV_PULLDOWN_MASK)
/*! @} */

/*! @name ANACTRL_SET - USB PHY Analog Control Register */
/*! @{ */

#define USBPHY_ANACTRL_SET_LVI_EN_MASK           (0x2U)
#define USBPHY_ANACTRL_SET_LVI_EN_SHIFT          (1U)
#define USBPHY_ANACTRL_SET_LVI_EN(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_ANACTRL_SET_LVI_EN_SHIFT)) & USBPHY_ANACTRL_SET_LVI_EN_MASK)

#define USBPHY_ANACTRL_SET_PFD_CLK_SEL_MASK      (0xCU)
#define USBPHY_ANACTRL_SET_PFD_CLK_SEL_SHIFT     (2U)
#define USBPHY_ANACTRL_SET_PFD_CLK_SEL(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_ANACTRL_SET_PFD_CLK_SEL_SHIFT)) & USBPHY_ANACTRL_SET_PFD_CLK_SEL_MASK)

#define USBPHY_ANACTRL_SET_DEV_PULLDOWN_MASK     (0x400U)
#define USBPHY_ANACTRL_SET_DEV_PULLDOWN_SHIFT    (10U)
/*! DEV_PULLDOWN
 *  0b0..The 15kohm nominal pulldowns on the USB_DP and USB_DM pinsare disabled in device mode.
 *  0b1..The 15kohm nominal pulldowns on the USB_DP and USB_DM pinsare enabled in device mode.
 */
#define USBPHY_ANACTRL_SET_DEV_PULLDOWN(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_ANACTRL_SET_DEV_PULLDOWN_SHIFT)) & USBPHY_ANACTRL_SET_DEV_PULLDOWN_MASK)
/*! @} */

/*! @name ANACTRL_CLR - USB PHY Analog Control Register */
/*! @{ */

#define USBPHY_ANACTRL_CLR_LVI_EN_MASK           (0x2U)
#define USBPHY_ANACTRL_CLR_LVI_EN_SHIFT          (1U)
#define USBPHY_ANACTRL_CLR_LVI_EN(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_ANACTRL_CLR_LVI_EN_SHIFT)) & USBPHY_ANACTRL_CLR_LVI_EN_MASK)

#define USBPHY_ANACTRL_CLR_PFD_CLK_SEL_MASK      (0xCU)
#define USBPHY_ANACTRL_CLR_PFD_CLK_SEL_SHIFT     (2U)
#define USBPHY_ANACTRL_CLR_PFD_CLK_SEL(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_ANACTRL_CLR_PFD_CLK_SEL_SHIFT)) & USBPHY_ANACTRL_CLR_PFD_CLK_SEL_MASK)

#define USBPHY_ANACTRL_CLR_DEV_PULLDOWN_MASK     (0x400U)
#define USBPHY_ANACTRL_CLR_DEV_PULLDOWN_SHIFT    (10U)
/*! DEV_PULLDOWN
 *  0b0..The 15kohm nominal pulldowns on the USB_DP and USB_DM pinsare disabled in device mode.
 *  0b1..The 15kohm nominal pulldowns on the USB_DP and USB_DM pinsare enabled in device mode.
 */
#define USBPHY_ANACTRL_CLR_DEV_PULLDOWN(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_ANACTRL_CLR_DEV_PULLDOWN_SHIFT)) & USBPHY_ANACTRL_CLR_DEV_PULLDOWN_MASK)
/*! @} */

/*! @name ANACTRL_TOG - USB PHY Analog Control Register */
/*! @{ */

#define USBPHY_ANACTRL_TOG_LVI_EN_MASK           (0x2U)
#define USBPHY_ANACTRL_TOG_LVI_EN_SHIFT          (1U)
#define USBPHY_ANACTRL_TOG_LVI_EN(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_ANACTRL_TOG_LVI_EN_SHIFT)) & USBPHY_ANACTRL_TOG_LVI_EN_MASK)

#define USBPHY_ANACTRL_TOG_PFD_CLK_SEL_MASK      (0xCU)
#define USBPHY_ANACTRL_TOG_PFD_CLK_SEL_SHIFT     (2U)
#define USBPHY_ANACTRL_TOG_PFD_CLK_SEL(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_ANACTRL_TOG_PFD_CLK_SEL_SHIFT)) & USBPHY_ANACTRL_TOG_PFD_CLK_SEL_MASK)

#define USBPHY_ANACTRL_TOG_DEV_PULLDOWN_MASK     (0x400U)
#define USBPHY_ANACTRL_TOG_DEV_PULLDOWN_SHIFT    (10U)
/*! DEV_PULLDOWN
 *  0b0..The 15kohm nominal pulldowns on the USB_DP and USB_DM pinsare disabled in device mode.
 *  0b1..The 15kohm nominal pulldowns on the USB_DP and USB_DM pinsare enabled in device mode.
 */
#define USBPHY_ANACTRL_TOG_DEV_PULLDOWN(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_ANACTRL_TOG_DEV_PULLDOWN_SHIFT)) & USBPHY_ANACTRL_TOG_DEV_PULLDOWN_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group USBPHY_Register_Masks */


/*!
 * @}
 */ /* end of group USBPHY_Peripheral_Access_Layer */


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


#endif  /* USBPHY_H_ */


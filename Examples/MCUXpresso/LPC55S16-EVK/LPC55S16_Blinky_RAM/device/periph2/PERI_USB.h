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
**         CMSIS Peripheral Access Layer for USB
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
 * @file USB.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for USB
 *
 * CMSIS Peripheral Access Layer for USB
 */

#if !defined(USB_H_)
#define USB_H_                                   /**< Symbol preventing repeated inclusion */

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
   -- USB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Peripheral_Access_Layer USB Peripheral Access Layer
 * @{
 */

/** USB - Register Layout Typedef */
typedef struct {
  __IO uint32_t DEVCMDSTAT;                        /**< USB Device Command/Status register, offset: 0x0 */
  __IO uint32_t INFO;                              /**< USB Info register, offset: 0x4 */
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
  __IO uint32_t EPTOGGLE;                          /**< USB Endpoint toggle register, offset: 0x34 */
} USB_Type;

/* ----------------------------------------------------------------------------
   -- USB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Register_Masks USB Register Masks
 * @{
 */

/*! @name DEVCMDSTAT - USB Device Command/Status register */
/*! @{ */

#define USB_DEVCMDSTAT_DEV_ADDR_MASK             (0x7FU)
#define USB_DEVCMDSTAT_DEV_ADDR_SHIFT            (0U)
/*! DEV_ADDR - USB device address. After bus reset, the address is reset to 0x00. If the enable bit
 *    is set, the device will respond on packets for function address DEV_ADDR. When receiving a
 *    SetAddress Control Request from the USB host, software must program the new address before
 *    completing the status phase of the SetAddress Control Request.
 */
#define USB_DEVCMDSTAT_DEV_ADDR(x)               (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DEV_ADDR_SHIFT)) & USB_DEVCMDSTAT_DEV_ADDR_MASK)

#define USB_DEVCMDSTAT_DEV_EN_MASK               (0x80U)
#define USB_DEVCMDSTAT_DEV_EN_SHIFT              (7U)
/*! DEV_EN - USB device enable. If this bit is set, the HW will start responding on packets for function address DEV_ADDR. */
#define USB_DEVCMDSTAT_DEV_EN(x)                 (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DEV_EN_SHIFT)) & USB_DEVCMDSTAT_DEV_EN_MASK)

#define USB_DEVCMDSTAT_SETUP_MASK                (0x100U)
#define USB_DEVCMDSTAT_SETUP_SHIFT               (8U)
/*! SETUP - SETUP token received. If a SETUP token is received and acknowledged by the device, this
 *    bit is set. As long as this bit is set all received IN and OUT tokens will be NAKed by HW. SW
 *    must clear this bit by writing a one. If this bit is zero, HW will handle the tokens to the
 *    CTRL EP0 as indicated by the CTRL EP0 IN and OUT data information programmed by SW.
 */
#define USB_DEVCMDSTAT_SETUP(x)                  (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_SETUP_SHIFT)) & USB_DEVCMDSTAT_SETUP_MASK)

#define USB_DEVCMDSTAT_FORCE_NEEDCLK_MASK        (0x200U)
#define USB_DEVCMDSTAT_FORCE_NEEDCLK_SHIFT       (9U)
/*! FORCE_NEEDCLK - Forces the NEEDCLK output to always be on:
 *  0b0..USB_NEEDCLK has normal function.
 *  0b1..USB_NEEDCLK always 1. Clock will not be stopped in case of suspend.
 */
#define USB_DEVCMDSTAT_FORCE_NEEDCLK(x)          (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_FORCE_NEEDCLK_SHIFT)) & USB_DEVCMDSTAT_FORCE_NEEDCLK_MASK)

#define USB_DEVCMDSTAT_LPM_SUP_MASK              (0x800U)
#define USB_DEVCMDSTAT_LPM_SUP_SHIFT             (11U)
/*! LPM_SUP - LPM Supported:
 *  0b0..LPM not supported.
 *  0b1..LPM supported.
 */
#define USB_DEVCMDSTAT_LPM_SUP(x)                (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_LPM_SUP_SHIFT)) & USB_DEVCMDSTAT_LPM_SUP_MASK)

#define USB_DEVCMDSTAT_INTONNAK_AO_MASK          (0x1000U)
#define USB_DEVCMDSTAT_INTONNAK_AO_SHIFT         (12U)
/*! INTONNAK_AO - Interrupt on NAK for interrupt and bulk OUT EP
 *  0b0..Only acknowledged packets generate an interrupt
 *  0b1..Both acknowledged and NAKed packets generate interrupts.
 */
#define USB_DEVCMDSTAT_INTONNAK_AO(x)            (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_INTONNAK_AO_SHIFT)) & USB_DEVCMDSTAT_INTONNAK_AO_MASK)

#define USB_DEVCMDSTAT_INTONNAK_AI_MASK          (0x2000U)
#define USB_DEVCMDSTAT_INTONNAK_AI_SHIFT         (13U)
/*! INTONNAK_AI - Interrupt on NAK for interrupt and bulk IN EP
 *  0b0..Only acknowledged packets generate an interrupt
 *  0b1..Both acknowledged and NAKed packets generate interrupts.
 */
#define USB_DEVCMDSTAT_INTONNAK_AI(x)            (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_INTONNAK_AI_SHIFT)) & USB_DEVCMDSTAT_INTONNAK_AI_MASK)

#define USB_DEVCMDSTAT_INTONNAK_CO_MASK          (0x4000U)
#define USB_DEVCMDSTAT_INTONNAK_CO_SHIFT         (14U)
/*! INTONNAK_CO - Interrupt on NAK for control OUT EP
 *  0b0..Only acknowledged packets generate an interrupt
 *  0b1..Both acknowledged and NAKed packets generate interrupts.
 */
#define USB_DEVCMDSTAT_INTONNAK_CO(x)            (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_INTONNAK_CO_SHIFT)) & USB_DEVCMDSTAT_INTONNAK_CO_MASK)

#define USB_DEVCMDSTAT_INTONNAK_CI_MASK          (0x8000U)
#define USB_DEVCMDSTAT_INTONNAK_CI_SHIFT         (15U)
/*! INTONNAK_CI - Interrupt on NAK for control IN EP
 *  0b0..Only acknowledged packets generate an interrupt
 *  0b1..Both acknowledged and NAKed packets generate interrupts.
 */
#define USB_DEVCMDSTAT_INTONNAK_CI(x)            (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_INTONNAK_CI_SHIFT)) & USB_DEVCMDSTAT_INTONNAK_CI_MASK)

#define USB_DEVCMDSTAT_DCON_MASK                 (0x10000U)
#define USB_DEVCMDSTAT_DCON_SHIFT                (16U)
/*! DCON - Device status - connect. The connect bit must be set by SW to indicate that the device
 *    must signal a connect. The pull-up resistor on USB_DP will be enabled when this bit is set and
 *    the VBUSDEBOUNCED bit is one.
 */
#define USB_DEVCMDSTAT_DCON(x)                   (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DCON_SHIFT)) & USB_DEVCMDSTAT_DCON_MASK)

#define USB_DEVCMDSTAT_DSUS_MASK                 (0x20000U)
#define USB_DEVCMDSTAT_DSUS_SHIFT                (17U)
/*! DSUS - Device status - suspend. The suspend bit indicates the current suspend state. It is set
 *    to 1 when the device hasn't seen any activity on its upstream port for more than 3
 *    milliseconds. It is reset to 0 on any activity. When the device is suspended (Suspend bit DSUS = 1) and
 *    the software writes a 0 to it, the device will generate a remote wake-up. This will only happen
 *    when the device is connected (Connect bit = 1). When the device is not connected or not
 *    suspended, a writing a 0 has no effect. Writing a 1 never has an effect.
 */
#define USB_DEVCMDSTAT_DSUS(x)                   (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DSUS_SHIFT)) & USB_DEVCMDSTAT_DSUS_MASK)

#define USB_DEVCMDSTAT_LPM_SUS_MASK              (0x80000U)
#define USB_DEVCMDSTAT_LPM_SUS_SHIFT             (19U)
/*! LPM_SUS - Device status - LPM Suspend. This bit represents the current LPM suspend state. It is
 *    set to 1 by HW when the device has acknowledged the LPM request from the USB host and the
 *    Token Retry Time of 10 ms has elapsed. When the device is in the LPM suspended state (LPM suspend
 *    bit = 1) and the software writes a zero to this bit, the device will generate a remote
 *    walk-up. Software can only write a zero to this bit when the LPM_REWP bit is set to 1. HW resets this
 *    bit when it receives a host initiated resume. HW only updates the LPM_SUS bit when the
 *    LPM_SUPP bit is equal to one.
 */
#define USB_DEVCMDSTAT_LPM_SUS(x)                (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_LPM_SUS_SHIFT)) & USB_DEVCMDSTAT_LPM_SUS_MASK)

#define USB_DEVCMDSTAT_LPM_REWP_MASK             (0x100000U)
#define USB_DEVCMDSTAT_LPM_REWP_SHIFT            (20U)
/*! LPM_REWP - LPM Remote Wake-up Enabled by USB host. HW sets this bit to one when the bRemoteWake
 *    bit in the LPM extended token is set to 1. HW will reset this bit to 0 when it receives the
 *    host initiated LPM resume, when a remote wake-up is sent by the device or when a USB bus reset
 *    is received. Software can use this bit to check if the remote wake-up feature is enabled by the
 *    host for the LPM transaction.
 */
#define USB_DEVCMDSTAT_LPM_REWP(x)               (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_LPM_REWP_SHIFT)) & USB_DEVCMDSTAT_LPM_REWP_MASK)

#define USB_DEVCMDSTAT_DCON_C_MASK               (0x1000000U)
#define USB_DEVCMDSTAT_DCON_C_SHIFT              (24U)
/*! DCON_C - Device status - connect change. The Connect Change bit is set when the device's pull-up
 *    resistor is disconnected because VBus disappeared. The bit is reset by writing a one to it.
 */
#define USB_DEVCMDSTAT_DCON_C(x)                 (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DCON_C_SHIFT)) & USB_DEVCMDSTAT_DCON_C_MASK)

#define USB_DEVCMDSTAT_DSUS_C_MASK               (0x2000000U)
#define USB_DEVCMDSTAT_DSUS_C_SHIFT              (25U)
/*! DSUS_C - Device status - suspend change. The suspend change bit is set to 1 when the suspend bit
 *    toggles. The suspend bit can toggle because: - The device goes in the suspended state - The
 *    device is disconnected - The device receives resume signaling on its upstream port. The bit is
 *    reset by writing a one to it.
 */
#define USB_DEVCMDSTAT_DSUS_C(x)                 (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DSUS_C_SHIFT)) & USB_DEVCMDSTAT_DSUS_C_MASK)

#define USB_DEVCMDSTAT_DRES_C_MASK               (0x4000000U)
#define USB_DEVCMDSTAT_DRES_C_SHIFT              (26U)
/*! DRES_C - Device status - reset change. This bit is set when the device received a bus reset. On
 *    a bus reset the device will automatically go to the default state (unconfigured and responding
 *    to address 0). The bit is reset by writing a one to it.
 */
#define USB_DEVCMDSTAT_DRES_C(x)                 (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DRES_C_SHIFT)) & USB_DEVCMDSTAT_DRES_C_MASK)

#define USB_DEVCMDSTAT_VBUSDEBOUNCED_MASK        (0x10000000U)
#define USB_DEVCMDSTAT_VBUSDEBOUNCED_SHIFT       (28U)
/*! VBUSDEBOUNCED - This bit indicates if Vbus is detected or not. The bit raises immediately when
 *    Vbus becomes high. It drops to zero if Vbus is low for at least 3 ms. If this bit is high and
 *    the DCon bit is set, the HW will enable the pull-up resistor to signal a connect.
 */
#define USB_DEVCMDSTAT_VBUSDEBOUNCED(x)          (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_VBUSDEBOUNCED_SHIFT)) & USB_DEVCMDSTAT_VBUSDEBOUNCED_MASK)
/*! @} */

/*! @name INFO - USB Info register */
/*! @{ */

#define USB_INFO_FRAME_NR_MASK                   (0x7FFU)
#define USB_INFO_FRAME_NR_SHIFT                  (0U)
/*! FRAME_NR - Frame number. This contains the frame number of the last successfully received SOF.
 *    In case no SOF was received by the device at the beginning of a frame, the frame number
 *    returned is that of the last successfully received SOF. In case the SOF frame number contained a CRC
 *    error, the frame number returned will be the corrupted frame number as received by the device.
 */
#define USB_INFO_FRAME_NR(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INFO_FRAME_NR_SHIFT)) & USB_INFO_FRAME_NR_MASK)

#define USB_INFO_ERR_CODE_MASK                   (0x7800U)
#define USB_INFO_ERR_CODE_SHIFT                  (11U)
/*! ERR_CODE - The error code which last occurred:
 *  0b0000..No error
 *  0b0001..PID encoding error
 *  0b0010..PID unknown
 *  0b0011..Packet unexpected
 *  0b0100..Token CRC error
 *  0b0101..Data CRC error
 *  0b0110..Time out
 *  0b0111..Babble
 *  0b1000..Truncated EOP
 *  0b1001..Sent/Received NAK
 *  0b1010..Sent Stall
 *  0b1011..Overrun
 *  0b1100..Sent empty packet
 *  0b1101..Bitstuff error
 *  0b1110..Sync error
 *  0b1111..Wrong data toggle
 */
#define USB_INFO_ERR_CODE(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INFO_ERR_CODE_SHIFT)) & USB_INFO_ERR_CODE_MASK)

#define USB_INFO_MINREV_MASK                     (0xFF0000U)
#define USB_INFO_MINREV_SHIFT                    (16U)
/*! MINREV - Minor Revision. */
#define USB_INFO_MINREV(x)                       (((uint32_t)(((uint32_t)(x)) << USB_INFO_MINREV_SHIFT)) & USB_INFO_MINREV_MASK)

#define USB_INFO_MAJREV_MASK                     (0xFF000000U)
#define USB_INFO_MAJREV_SHIFT                    (24U)
/*! MAJREV - Major Revision. */
#define USB_INFO_MAJREV(x)                       (((uint32_t)(((uint32_t)(x)) << USB_INFO_MAJREV_SHIFT)) & USB_INFO_MAJREV_MASK)
/*! @} */

/*! @name EPLISTSTART - USB EP Command/Status List start address */
/*! @{ */

#define USB_EPLISTSTART_EP_LIST_MASK             (0xFFFFFF00U)
#define USB_EPLISTSTART_EP_LIST_SHIFT            (8U)
/*! EP_LIST - Start address of the USB EP Command/Status List. */
#define USB_EPLISTSTART_EP_LIST(x)               (((uint32_t)(((uint32_t)(x)) << USB_EPLISTSTART_EP_LIST_SHIFT)) & USB_EPLISTSTART_EP_LIST_MASK)
/*! @} */

/*! @name DATABUFSTART - USB Data buffer start address */
/*! @{ */

#define USB_DATABUFSTART_DA_BUF_MASK             (0xFFC00000U)
#define USB_DATABUFSTART_DA_BUF_SHIFT            (22U)
/*! DA_BUF - Start address of the buffer pointer page where all endpoint data buffers are located. */
#define USB_DATABUFSTART_DA_BUF(x)               (((uint32_t)(((uint32_t)(x)) << USB_DATABUFSTART_DA_BUF_SHIFT)) & USB_DATABUFSTART_DA_BUF_MASK)
/*! @} */

/*! @name LPM - USB Link Power Management register */
/*! @{ */

#define USB_LPM_HIRD_HW_MASK                     (0xFU)
#define USB_LPM_HIRD_HW_SHIFT                    (0U)
/*! HIRD_HW - Host Initiated Resume Duration - HW. This is the HIRD value from the last received LPM token */
#define USB_LPM_HIRD_HW(x)                       (((uint32_t)(((uint32_t)(x)) << USB_LPM_HIRD_HW_SHIFT)) & USB_LPM_HIRD_HW_MASK)

#define USB_LPM_HIRD_SW_MASK                     (0xF0U)
#define USB_LPM_HIRD_SW_SHIFT                    (4U)
/*! HIRD_SW - Host Initiated Resume Duration - SW. This is the time duration required by the USB
 *    device system to come out of LPM initiated suspend after receiving the host initiated LPM resume.
 */
#define USB_LPM_HIRD_SW(x)                       (((uint32_t)(((uint32_t)(x)) << USB_LPM_HIRD_SW_SHIFT)) & USB_LPM_HIRD_SW_MASK)

#define USB_LPM_DATA_PENDING_MASK                (0x100U)
#define USB_LPM_DATA_PENDING_SHIFT               (8U)
/*! DATA_PENDING - As long as this bit is set to one and LPM supported bit is set to one, HW will
 *    return a NYET handshake on every LPM token it receives. If LPM supported bit is set to one and
 *    this bit is zero, HW will return an ACK handshake on every LPM token it receives. If SW has
 *    still data pending and LPM is supported, it must set this bit to 1.
 */
#define USB_LPM_DATA_PENDING(x)                  (((uint32_t)(((uint32_t)(x)) << USB_LPM_DATA_PENDING_SHIFT)) & USB_LPM_DATA_PENDING_MASK)
/*! @} */

/*! @name EPSKIP - USB Endpoint skip */
/*! @{ */

#define USB_EPSKIP_SKIP_MASK                     (0x3FFU)
#define USB_EPSKIP_SKIP_SHIFT                    (0U)
/*! SKIP - Endpoint skip: Writing 1 to one of these bits, will indicate to HW that it must
 *    deactivate the buffer assigned to this endpoint and return control back to software. When HW has
 *    deactivated the endpoint, it will clear this bit, but it will not modify the EPINUSE bit. An
 *    interrupt will be generated when the Active bit goes from 1 to 0. Note: In case of double-buffering,
 *    HW will only clear the Active bit of the buffer indicated by the EPINUSE bit.
 */
#define USB_EPSKIP_SKIP(x)                       (((uint32_t)(((uint32_t)(x)) << USB_EPSKIP_SKIP_SHIFT)) & USB_EPSKIP_SKIP_MASK)
/*! @} */

/*! @name EPINUSE - USB Endpoint Buffer in use */
/*! @{ */

#define USB_EPINUSE_BUF_MASK                     (0x3FCU)
#define USB_EPINUSE_BUF_SHIFT                    (2U)
/*! BUF - Buffer in use: This register has one bit per physical endpoint. 0: HW is accessing buffer
 *    0. 1: HW is accessing buffer 1.
 */
#define USB_EPINUSE_BUF(x)                       (((uint32_t)(((uint32_t)(x)) << USB_EPINUSE_BUF_SHIFT)) & USB_EPINUSE_BUF_MASK)
/*! @} */

/*! @name EPBUFCFG - USB Endpoint Buffer Configuration register */
/*! @{ */

#define USB_EPBUFCFG_BUF_SB_MASK                 (0x3FCU)
#define USB_EPBUFCFG_BUF_SB_SHIFT                (2U)
/*! BUF_SB - Buffer usage: This register has one bit per physical endpoint. 0: Single-buffer. 1:
 *    Double-buffer. If the bit is set to single-buffer (0), it will not toggle the corresponding
 *    EPINUSE bit when it clears the active bit. If the bit is set to double-buffer (1), HW will toggle
 *    the EPINUSE bit when it clears the Active bit for the buffer.
 */
#define USB_EPBUFCFG_BUF_SB(x)                   (((uint32_t)(((uint32_t)(x)) << USB_EPBUFCFG_BUF_SB_SHIFT)) & USB_EPBUFCFG_BUF_SB_MASK)
/*! @} */

/*! @name INTSTAT - USB interrupt status register */
/*! @{ */

#define USB_INTSTAT_EP0OUT_MASK                  (0x1U)
#define USB_INTSTAT_EP0OUT_SHIFT                 (0U)
/*! EP0OUT - Interrupt status register bit for the Control EP0 OUT direction. This bit will be set
 *    if NBytes transitions to zero or the skip bit is set by software or a SETUP packet is
 *    successfully received for the control EP0. If the IntOnNAK_CO is set, this bit will also be set when a
 *    NAK is transmitted for the Control EP0 OUT direction. Software can clear this bit by writing a
 *    one to it.
 */
#define USB_INTSTAT_EP0OUT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP0OUT_SHIFT)) & USB_INTSTAT_EP0OUT_MASK)

#define USB_INTSTAT_EP0IN_MASK                   (0x2U)
#define USB_INTSTAT_EP0IN_SHIFT                  (1U)
/*! EP0IN - Interrupt status register bit for the Control EP0 IN direction. This bit will be set if
 *    NBytes transitions to zero or the skip bit is set by software. If the IntOnNAK_CI is set, this
 *    bit will also be set when a NAK is transmitted for the Control EP0 IN direction. Software can
 *    clear this bit by writing a one to it.
 */
#define USB_INTSTAT_EP0IN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP0IN_SHIFT)) & USB_INTSTAT_EP0IN_MASK)

#define USB_INTSTAT_EP1OUT_MASK                  (0x4U)
#define USB_INTSTAT_EP1OUT_SHIFT                 (2U)
/*! EP1OUT - Interrupt status register bit for the EP1 OUT direction. This bit will be set if the
 *    corresponding Active bit is cleared by HW. This is done in case the programmed NBytes
 *    transitions to zero or the skip bit is set by software. If the IntOnNAK_AO is set, this bit will also be
 *    set when a NAK is transmitted for the EP1 OUT direction. Software can clear this bit by
 *    writing a one to it.
 */
#define USB_INTSTAT_EP1OUT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP1OUT_SHIFT)) & USB_INTSTAT_EP1OUT_MASK)

#define USB_INTSTAT_EP1IN_MASK                   (0x8U)
#define USB_INTSTAT_EP1IN_SHIFT                  (3U)
/*! EP1IN - Interrupt status register bit for the EP1 IN direction. This bit will be set if the
 *    corresponding Active bit is cleared by HW. This is done in case the programmed NBytes transitions
 *    to zero or the skip bit is set by software. If the IntOnNAK_AI is set, this bit will also be
 *    set when a NAK is transmitted for the EP1 IN direction. Software can clear this bit by writing
 *    a one to it.
 */
#define USB_INTSTAT_EP1IN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP1IN_SHIFT)) & USB_INTSTAT_EP1IN_MASK)

#define USB_INTSTAT_EP2OUT_MASK                  (0x10U)
#define USB_INTSTAT_EP2OUT_SHIFT                 (4U)
/*! EP2OUT - Interrupt status register bit for the EP2 OUT direction. This bit will be set if the
 *    corresponding Active bit is cleared by HW. This is done in case the programmed NBytes
 *    transitions to zero or the skip bit is set by software. If the IntOnNAK_AO is set, this bit will also be
 *    set when a NAK is transmitted for the EP2 OUT direction. Software can clear this bit by
 *    writing a one to it.
 */
#define USB_INTSTAT_EP2OUT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP2OUT_SHIFT)) & USB_INTSTAT_EP2OUT_MASK)

#define USB_INTSTAT_EP2IN_MASK                   (0x20U)
#define USB_INTSTAT_EP2IN_SHIFT                  (5U)
/*! EP2IN - Interrupt status register bit for the EP2 IN direction. This bit will be set if the
 *    corresponding Active bit is cleared by HW. This is done in case the programmed NBytes transitions
 *    to zero or the skip bit is set by software. If the IntOnNAK_AI is set, this bit will also be
 *    set when a NAK is transmitted for the EP2 IN direction. Software can clear this bit by writing
 *    a one to it.
 */
#define USB_INTSTAT_EP2IN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP2IN_SHIFT)) & USB_INTSTAT_EP2IN_MASK)

#define USB_INTSTAT_EP3OUT_MASK                  (0x40U)
#define USB_INTSTAT_EP3OUT_SHIFT                 (6U)
/*! EP3OUT - Interrupt status register bit for the EP3 OUT direction. This bit will be set if the
 *    corresponding Active bit is cleared by HW. This is done in case the programmed NBytes
 *    transitions to zero or the skip bit is set by software. If the IntOnNAK_AO is set, this bit will also be
 *    set when a NAK is transmitted for the EP3 OUT direction. Software can clear this bit by
 *    writing a one to it.
 */
#define USB_INTSTAT_EP3OUT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP3OUT_SHIFT)) & USB_INTSTAT_EP3OUT_MASK)

#define USB_INTSTAT_EP3IN_MASK                   (0x80U)
#define USB_INTSTAT_EP3IN_SHIFT                  (7U)
/*! EP3IN - Interrupt status register bit for the EP3 IN direction. This bit will be set if the
 *    corresponding Active bit is cleared by HW. This is done in case the programmed NBytes transitions
 *    to zero or the skip bit is set by software. If the IntOnNAK_AI is set, this bit will also be
 *    set when a NAK is transmitted for the EP3 IN direction. Software can clear this bit by writing
 *    a one to it.
 */
#define USB_INTSTAT_EP3IN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP3IN_SHIFT)) & USB_INTSTAT_EP3IN_MASK)

#define USB_INTSTAT_EP4OUT_MASK                  (0x100U)
#define USB_INTSTAT_EP4OUT_SHIFT                 (8U)
/*! EP4OUT - Interrupt status register bit for the EP4 OUT direction. This bit will be set if the
 *    corresponding Active bit is cleared by HW. This is done in case the programmed NBytes
 *    transitions to zero or the skip bit is set by software. If the IntOnNAK_AO is set, this bit will also be
 *    set when a NAK is transmitted for the EP4 OUT direction. Software can clear this bit by
 *    writing a one to it.
 */
#define USB_INTSTAT_EP4OUT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP4OUT_SHIFT)) & USB_INTSTAT_EP4OUT_MASK)

#define USB_INTSTAT_EP4IN_MASK                   (0x200U)
#define USB_INTSTAT_EP4IN_SHIFT                  (9U)
/*! EP4IN - Interrupt status register bit for the EP4 IN direction. This bit will be set if the
 *    corresponding Active bit is cleared by HW. This is done in case the programmed NBytes transitions
 *    to zero or the skip bit is set by software. If the IntOnNAK_AI is set, this bit will also be
 *    set when a NAK is transmitted for the EP4 IN direction. Software can clear this bit by writing
 *    a one to it.
 */
#define USB_INTSTAT_EP4IN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP4IN_SHIFT)) & USB_INTSTAT_EP4IN_MASK)

#define USB_INTSTAT_FRAME_INT_MASK               (0x40000000U)
#define USB_INTSTAT_FRAME_INT_SHIFT              (30U)
/*! FRAME_INT - Frame interrupt. This bit is set to one every millisecond when the VbusDebounced bit
 *    and the DCON bit are set. This bit can be used by software when handling isochronous
 *    endpoints. Software can clear this bit by writing a one to it.
 */
#define USB_INTSTAT_FRAME_INT(x)                 (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_FRAME_INT_SHIFT)) & USB_INTSTAT_FRAME_INT_MASK)

#define USB_INTSTAT_DEV_INT_MASK                 (0x80000000U)
#define USB_INTSTAT_DEV_INT_SHIFT                (31U)
/*! DEV_INT - Device status interrupt. This bit is set by HW when one of the bits in the Device
 *    Status Change register are set. Software can clear this bit by writing a one to it.
 */
#define USB_INTSTAT_DEV_INT(x)                   (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_DEV_INT_SHIFT)) & USB_INTSTAT_DEV_INT_MASK)
/*! @} */

/*! @name INTEN - USB interrupt enable register */
/*! @{ */

#define USB_INTEN_EP_INT_EN_MASK                 (0x3FFU)
#define USB_INTEN_EP_INT_EN_SHIFT                (0U)
/*! EP_INT_EN - If this bit is set and the corresponding USB interrupt status bit is set, a HW
 *    interrupt is generated on the interrupt line indicated by the corresponding USB interrupt routing
 *    bit.
 */
#define USB_INTEN_EP_INT_EN(x)                   (((uint32_t)(((uint32_t)(x)) << USB_INTEN_EP_INT_EN_SHIFT)) & USB_INTEN_EP_INT_EN_MASK)

#define USB_INTEN_FRAME_INT_EN_MASK              (0x40000000U)
#define USB_INTEN_FRAME_INT_EN_SHIFT             (30U)
/*! FRAME_INT_EN - If this bit is set and the corresponding USB interrupt status bit is set, a HW
 *    interrupt is generated on the interrupt line indicated by the corresponding USB interrupt
 *    routing bit.
 */
#define USB_INTEN_FRAME_INT_EN(x)                (((uint32_t)(((uint32_t)(x)) << USB_INTEN_FRAME_INT_EN_SHIFT)) & USB_INTEN_FRAME_INT_EN_MASK)

#define USB_INTEN_DEV_INT_EN_MASK                (0x80000000U)
#define USB_INTEN_DEV_INT_EN_SHIFT               (31U)
/*! DEV_INT_EN - If this bit is set and the corresponding USB interrupt status bit is set, a HW
 *    interrupt is generated on the interrupt line indicated by the corresponding USB interrupt routing
 *    bit.
 */
#define USB_INTEN_DEV_INT_EN(x)                  (((uint32_t)(((uint32_t)(x)) << USB_INTEN_DEV_INT_EN_SHIFT)) & USB_INTEN_DEV_INT_EN_MASK)
/*! @} */

/*! @name INTSETSTAT - USB set interrupt status register */
/*! @{ */

#define USB_INTSETSTAT_EP_SET_INT_MASK           (0x3FFU)
#define USB_INTSETSTAT_EP_SET_INT_SHIFT          (0U)
/*! EP_SET_INT - If software writes a one to one of these bits, the corresponding USB interrupt
 *    status bit is set. When this register is read, the same value as the USB interrupt status register
 *    is returned.
 */
#define USB_INTSETSTAT_EP_SET_INT(x)             (((uint32_t)(((uint32_t)(x)) << USB_INTSETSTAT_EP_SET_INT_SHIFT)) & USB_INTSETSTAT_EP_SET_INT_MASK)

#define USB_INTSETSTAT_FRAME_SET_INT_MASK        (0x40000000U)
#define USB_INTSETSTAT_FRAME_SET_INT_SHIFT       (30U)
/*! FRAME_SET_INT - If software writes a one to one of these bits, the corresponding USB interrupt
 *    status bit is set. When this register is read, the same value as the USB interrupt status
 *    register is returned.
 */
#define USB_INTSETSTAT_FRAME_SET_INT(x)          (((uint32_t)(((uint32_t)(x)) << USB_INTSETSTAT_FRAME_SET_INT_SHIFT)) & USB_INTSETSTAT_FRAME_SET_INT_MASK)

#define USB_INTSETSTAT_DEV_SET_INT_MASK          (0x80000000U)
#define USB_INTSETSTAT_DEV_SET_INT_SHIFT         (31U)
/*! DEV_SET_INT - If software writes a one to one of these bits, the corresponding USB interrupt
 *    status bit is set. When this register is read, the same value as the USB interrupt status
 *    register is returned.
 */
#define USB_INTSETSTAT_DEV_SET_INT(x)            (((uint32_t)(((uint32_t)(x)) << USB_INTSETSTAT_DEV_SET_INT_SHIFT)) & USB_INTSETSTAT_DEV_SET_INT_MASK)
/*! @} */

/*! @name EPTOGGLE - USB Endpoint toggle register */
/*! @{ */

#define USB_EPTOGGLE_TOGGLE_MASK                 (0x3FFU)
#define USB_EPTOGGLE_TOGGLE_SHIFT                (0U)
/*! TOGGLE - Endpoint data toggle: This field indicates the current value of the data toggle for the corresponding endpoint. */
#define USB_EPTOGGLE_TOGGLE(x)                   (((uint32_t)(((uint32_t)(x)) << USB_EPTOGGLE_TOGGLE_SHIFT)) & USB_EPTOGGLE_TOGGLE_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group USB_Register_Masks */


/*!
 * @}
 */ /* end of group USB_Peripheral_Access_Layer */


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


#endif  /* USB_H_ */


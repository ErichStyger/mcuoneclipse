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
**         CMSIS Peripheral Access Layer for USBFSH
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
 * @file USBFSH.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for USBFSH
 *
 * CMSIS Peripheral Access Layer for USBFSH
 */

#if !defined(USBFSH_H_)
#define USBFSH_H_                                /**< Symbol preventing repeated inclusion */

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
   -- USBFSH Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBFSH_Peripheral_Access_Layer USBFSH Peripheral Access Layer
 * @{
 */

/** USBFSH - Register Layout Typedef */
typedef struct {
  __I  uint32_t HCREVISION;                        /**< BCD representation of the version of the HCI specification that is implemented by the Host Controller (HC), offset: 0x0 */
  __IO uint32_t HCCONTROL;                         /**< Defines the operating modes of the HC, offset: 0x4 */
  __IO uint32_t HCCOMMANDSTATUS;                   /**< This register is used to receive the commands from the Host Controller Driver (HCD), offset: 0x8 */
  __IO uint32_t HCINTERRUPTSTATUS;                 /**< Indicates the status on various events that cause hardware interrupts by setting the appropriate bits, offset: 0xC */
  __IO uint32_t HCINTERRUPTENABLE;                 /**< Controls the bits in the HcInterruptStatus register and indicates which events will generate a hardware interrupt, offset: 0x10 */
  __IO uint32_t HCINTERRUPTDISABLE;                /**< The bits in this register are used to disable corresponding bits in the HCInterruptStatus register and in turn disable that event leading to hardware interrupt, offset: 0x14 */
  __IO uint32_t HCHCCA;                            /**< Contains the physical address of the host controller communication area, offset: 0x18 */
  __I  uint32_t HCPERIODCURRENTED;                 /**< Contains the physical address of the current isochronous or interrupt endpoint descriptor, offset: 0x1C */
  __IO uint32_t HCCONTROLHEADED;                   /**< Contains the physical address of the first endpoint descriptor of the control list, offset: 0x20 */
  __IO uint32_t HCCONTROLCURRENTED;                /**< Contains the physical address of the current endpoint descriptor of the control list, offset: 0x24 */
  __IO uint32_t HCBULKHEADED;                      /**< Contains the physical address of the first endpoint descriptor of the bulk list, offset: 0x28 */
  __IO uint32_t HCBULKCURRENTED;                   /**< Contains the physical address of the current endpoint descriptor of the bulk list, offset: 0x2C */
  __I  uint32_t HCDONEHEAD;                        /**< Contains the physical address of the last transfer descriptor added to the 'Done' queue, offset: 0x30 */
  __IO uint32_t HCFMINTERVAL;                      /**< Defines the bit time interval in a frame and the full speed maximum packet size which would not cause an overrun, offset: 0x34 */
  __I  uint32_t HCFMREMAINING;                     /**< A 14-bit counter showing the bit time remaining in the current frame, offset: 0x38 */
  __I  uint32_t HCFMNUMBER;                        /**< Contains a 16-bit counter and provides the timing reference among events happening in the HC and the HCD, offset: 0x3C */
  __IO uint32_t HCPERIODICSTART;                   /**< Contains a programmable 14-bit value which determines the earliest time HC should start processing a periodic list, offset: 0x40 */
  __IO uint32_t HCLSTHRESHOLD;                     /**< Contains 11-bit value which is used by the HC to determine whether to commit to transfer a maximum of 8-byte LS packet before EOF, offset: 0x44 */
  __IO uint32_t HCRHDESCRIPTORA;                   /**< First of the two registers which describes the characteristics of the root hub, offset: 0x48 */
  __IO uint32_t HCRHDESCRIPTORB;                   /**< Second of the two registers which describes the characteristics of the Root Hub, offset: 0x4C */
  __IO uint32_t HCRHSTATUS;                        /**< This register is divided into two parts, offset: 0x50 */
  __IO uint32_t HCRHPORTSTATUS;                    /**< Controls and reports the port events on a per-port basis, offset: 0x54 */
       uint8_t RESERVED_0[4];
  __IO uint32_t PORTMODE;                          /**< Controls the port if it is attached to the host block or the device block, offset: 0x5C */
} USBFSH_Type;

/* ----------------------------------------------------------------------------
   -- USBFSH Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBFSH_Register_Masks USBFSH Register Masks
 * @{
 */

/*! @name HCREVISION - BCD representation of the version of the HCI specification that is implemented by the Host Controller (HC) */
/*! @{ */

#define USBFSH_HCREVISION_REV_MASK               (0xFFU)
#define USBFSH_HCREVISION_REV_SHIFT              (0U)
/*! REV - Revision. */
#define USBFSH_HCREVISION_REV(x)                 (((uint32_t)(((uint32_t)(x)) << USBFSH_HCREVISION_REV_SHIFT)) & USBFSH_HCREVISION_REV_MASK)
/*! @} */

/*! @name HCCONTROL - Defines the operating modes of the HC */
/*! @{ */

#define USBFSH_HCCONTROL_CBSR_MASK               (0x3U)
#define USBFSH_HCCONTROL_CBSR_SHIFT              (0U)
/*! CBSR - ControlBulkServiceRatio. */
#define USBFSH_HCCONTROL_CBSR(x)                 (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_CBSR_SHIFT)) & USBFSH_HCCONTROL_CBSR_MASK)

#define USBFSH_HCCONTROL_PLE_MASK                (0x4U)
#define USBFSH_HCCONTROL_PLE_SHIFT               (2U)
/*! PLE - PeriodicListEnable. */
#define USBFSH_HCCONTROL_PLE(x)                  (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_PLE_SHIFT)) & USBFSH_HCCONTROL_PLE_MASK)

#define USBFSH_HCCONTROL_IE_MASK                 (0x8U)
#define USBFSH_HCCONTROL_IE_SHIFT                (3U)
/*! IE - IsochronousEnable. */
#define USBFSH_HCCONTROL_IE(x)                   (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_IE_SHIFT)) & USBFSH_HCCONTROL_IE_MASK)

#define USBFSH_HCCONTROL_CLE_MASK                (0x10U)
#define USBFSH_HCCONTROL_CLE_SHIFT               (4U)
/*! CLE - ControlListEnable. */
#define USBFSH_HCCONTROL_CLE(x)                  (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_CLE_SHIFT)) & USBFSH_HCCONTROL_CLE_MASK)

#define USBFSH_HCCONTROL_BLE_MASK                (0x20U)
#define USBFSH_HCCONTROL_BLE_SHIFT               (5U)
/*! BLE - BulkListEnable This bit is set to enable the processing of the Bulk list in the next Frame. */
#define USBFSH_HCCONTROL_BLE(x)                  (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_BLE_SHIFT)) & USBFSH_HCCONTROL_BLE_MASK)

#define USBFSH_HCCONTROL_HCFS_MASK               (0xC0U)
#define USBFSH_HCCONTROL_HCFS_SHIFT              (6U)
/*! HCFS - HostControllerFunctionalState for USB 00b: USBRESET 01b: USBRESUME 10b: USBOPERATIONAL
 *    11b: USBSUSPEND A transition to USBOPERATIONAL from another state causes SOFgeneration to begin
 *    1 ms later.
 */
#define USBFSH_HCCONTROL_HCFS(x)                 (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_HCFS_SHIFT)) & USBFSH_HCCONTROL_HCFS_MASK)

#define USBFSH_HCCONTROL_IR_MASK                 (0x100U)
#define USBFSH_HCCONTROL_IR_SHIFT                (8U)
/*! IR - InterruptRouting This bit determines the routing of interrupts generated by events registered in HcInterruptStatus. */
#define USBFSH_HCCONTROL_IR(x)                   (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_IR_SHIFT)) & USBFSH_HCCONTROL_IR_MASK)

#define USBFSH_HCCONTROL_RWC_MASK                (0x200U)
#define USBFSH_HCCONTROL_RWC_SHIFT               (9U)
/*! RWC - RemoteWakeupConnected This bit indicates whether HC supports remote wake-up signaling. */
#define USBFSH_HCCONTROL_RWC(x)                  (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_RWC_SHIFT)) & USBFSH_HCCONTROL_RWC_MASK)

#define USBFSH_HCCONTROL_RWE_MASK                (0x400U)
#define USBFSH_HCCONTROL_RWE_SHIFT               (10U)
/*! RWE - RemoteWakeupEnable This bit is used by HCD to enable or disable the remote wake-up feature
 *    upon the detection of upstream resume signaling.
 */
#define USBFSH_HCCONTROL_RWE(x)                  (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_RWE_SHIFT)) & USBFSH_HCCONTROL_RWE_MASK)
/*! @} */

/*! @name HCCOMMANDSTATUS - This register is used to receive the commands from the Host Controller Driver (HCD) */
/*! @{ */

#define USBFSH_HCCOMMANDSTATUS_HCR_MASK          (0x1U)
#define USBFSH_HCCOMMANDSTATUS_HCR_SHIFT         (0U)
/*! HCR - HostControllerReset This bit is set by HCD to initiate a software reset of HC. */
#define USBFSH_HCCOMMANDSTATUS_HCR(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCOMMANDSTATUS_HCR_SHIFT)) & USBFSH_HCCOMMANDSTATUS_HCR_MASK)

#define USBFSH_HCCOMMANDSTATUS_CLF_MASK          (0x2U)
#define USBFSH_HCCOMMANDSTATUS_CLF_SHIFT         (1U)
/*! CLF - ControlListFilled This bit is used to indicate whether there are any TDs on the Control list. */
#define USBFSH_HCCOMMANDSTATUS_CLF(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCOMMANDSTATUS_CLF_SHIFT)) & USBFSH_HCCOMMANDSTATUS_CLF_MASK)

#define USBFSH_HCCOMMANDSTATUS_BLF_MASK          (0x4U)
#define USBFSH_HCCOMMANDSTATUS_BLF_SHIFT         (2U)
/*! BLF - BulkListFilled This bit is used to indicate whether there are any TDs on the Bulk list. */
#define USBFSH_HCCOMMANDSTATUS_BLF(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCOMMANDSTATUS_BLF_SHIFT)) & USBFSH_HCCOMMANDSTATUS_BLF_MASK)

#define USBFSH_HCCOMMANDSTATUS_OCR_MASK          (0x8U)
#define USBFSH_HCCOMMANDSTATUS_OCR_SHIFT         (3U)
/*! OCR - OwnershipChangeRequest This bit is set by an OS HCD to request a change of control of the HC. */
#define USBFSH_HCCOMMANDSTATUS_OCR(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCOMMANDSTATUS_OCR_SHIFT)) & USBFSH_HCCOMMANDSTATUS_OCR_MASK)

#define USBFSH_HCCOMMANDSTATUS_SOC_MASK          (0xC0U)
#define USBFSH_HCCOMMANDSTATUS_SOC_SHIFT         (6U)
/*! SOC - SchedulingOverrunCount These bits are incremented on each scheduling overrun error. */
#define USBFSH_HCCOMMANDSTATUS_SOC(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCOMMANDSTATUS_SOC_SHIFT)) & USBFSH_HCCOMMANDSTATUS_SOC_MASK)
/*! @} */

/*! @name HCINTERRUPTSTATUS - Indicates the status on various events that cause hardware interrupts by setting the appropriate bits */
/*! @{ */

#define USBFSH_HCINTERRUPTSTATUS_SO_MASK         (0x1U)
#define USBFSH_HCINTERRUPTSTATUS_SO_SHIFT        (0U)
/*! SO - SchedulingOverrun This bit is set when the USB schedule for the current Frame overruns and
 *    after the update of HccaFrameNumber.
 */
#define USBFSH_HCINTERRUPTSTATUS_SO(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTSTATUS_SO_SHIFT)) & USBFSH_HCINTERRUPTSTATUS_SO_MASK)

#define USBFSH_HCINTERRUPTSTATUS_WDH_MASK        (0x2U)
#define USBFSH_HCINTERRUPTSTATUS_WDH_SHIFT       (1U)
/*! WDH - WritebackDoneHead This bit is set immediately after HC has written HcDoneHead to HccaDoneHead. */
#define USBFSH_HCINTERRUPTSTATUS_WDH(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTSTATUS_WDH_SHIFT)) & USBFSH_HCINTERRUPTSTATUS_WDH_MASK)

#define USBFSH_HCINTERRUPTSTATUS_SF_MASK         (0x4U)
#define USBFSH_HCINTERRUPTSTATUS_SF_SHIFT        (2U)
/*! SF - StartofFrame This bit is set by HC at each start of a frame and after the update of HccaFrameNumber. */
#define USBFSH_HCINTERRUPTSTATUS_SF(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTSTATUS_SF_SHIFT)) & USBFSH_HCINTERRUPTSTATUS_SF_MASK)

#define USBFSH_HCINTERRUPTSTATUS_RD_MASK         (0x8U)
#define USBFSH_HCINTERRUPTSTATUS_RD_SHIFT        (3U)
/*! RD - ResumeDetected This bit is set when HC detects that a device on the USB is asserting resume signaling. */
#define USBFSH_HCINTERRUPTSTATUS_RD(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTSTATUS_RD_SHIFT)) & USBFSH_HCINTERRUPTSTATUS_RD_MASK)

#define USBFSH_HCINTERRUPTSTATUS_UE_MASK         (0x10U)
#define USBFSH_HCINTERRUPTSTATUS_UE_SHIFT        (4U)
/*! UE - UnrecoverableError This bit is set when HC detects a system error not related to USB. */
#define USBFSH_HCINTERRUPTSTATUS_UE(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTSTATUS_UE_SHIFT)) & USBFSH_HCINTERRUPTSTATUS_UE_MASK)

#define USBFSH_HCINTERRUPTSTATUS_FNO_MASK        (0x20U)
#define USBFSH_HCINTERRUPTSTATUS_FNO_SHIFT       (5U)
/*! FNO - FrameNumberOverflow This bit is set when the MSb of HcFmNumber (bit 15) changes value,
 *    from 0 to 1 or from 1 to 0, and after HccaFrameNumber has been updated.
 */
#define USBFSH_HCINTERRUPTSTATUS_FNO(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTSTATUS_FNO_SHIFT)) & USBFSH_HCINTERRUPTSTATUS_FNO_MASK)

#define USBFSH_HCINTERRUPTSTATUS_RHSC_MASK       (0x40U)
#define USBFSH_HCINTERRUPTSTATUS_RHSC_SHIFT      (6U)
/*! RHSC - RootHubStatusChange This bit is set when the content of HcRhStatus or the content of any
 *    of HcRhPortStatus[NumberofDownstreamPort] has changed.
 */
#define USBFSH_HCINTERRUPTSTATUS_RHSC(x)         (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTSTATUS_RHSC_SHIFT)) & USBFSH_HCINTERRUPTSTATUS_RHSC_MASK)

#define USBFSH_HCINTERRUPTSTATUS_OC_MASK         (0xFFFFFC00U)
#define USBFSH_HCINTERRUPTSTATUS_OC_SHIFT        (10U)
/*! OC - OwnershipChange This bit is set by HC when HCD sets the OwnershipChangeRequest field in HcCommandStatus. */
#define USBFSH_HCINTERRUPTSTATUS_OC(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTSTATUS_OC_SHIFT)) & USBFSH_HCINTERRUPTSTATUS_OC_MASK)
/*! @} */

/*! @name HCINTERRUPTENABLE - Controls the bits in the HcInterruptStatus register and indicates which events will generate a hardware interrupt */
/*! @{ */

#define USBFSH_HCINTERRUPTENABLE_SO_MASK         (0x1U)
#define USBFSH_HCINTERRUPTENABLE_SO_SHIFT        (0U)
/*! SO - Scheduling Overrun interrupt. */
#define USBFSH_HCINTERRUPTENABLE_SO(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_SO_SHIFT)) & USBFSH_HCINTERRUPTENABLE_SO_MASK)

#define USBFSH_HCINTERRUPTENABLE_WDH_MASK        (0x2U)
#define USBFSH_HCINTERRUPTENABLE_WDH_SHIFT       (1U)
/*! WDH - HcDoneHead Writeback interrupt. */
#define USBFSH_HCINTERRUPTENABLE_WDH(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_WDH_SHIFT)) & USBFSH_HCINTERRUPTENABLE_WDH_MASK)

#define USBFSH_HCINTERRUPTENABLE_SF_MASK         (0x4U)
#define USBFSH_HCINTERRUPTENABLE_SF_SHIFT        (2U)
/*! SF - Start of Frame interrupt. */
#define USBFSH_HCINTERRUPTENABLE_SF(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_SF_SHIFT)) & USBFSH_HCINTERRUPTENABLE_SF_MASK)

#define USBFSH_HCINTERRUPTENABLE_RD_MASK         (0x8U)
#define USBFSH_HCINTERRUPTENABLE_RD_SHIFT        (3U)
/*! RD - Resume Detect interrupt. */
#define USBFSH_HCINTERRUPTENABLE_RD(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_RD_SHIFT)) & USBFSH_HCINTERRUPTENABLE_RD_MASK)

#define USBFSH_HCINTERRUPTENABLE_UE_MASK         (0x10U)
#define USBFSH_HCINTERRUPTENABLE_UE_SHIFT        (4U)
/*! UE - Unrecoverable Error interrupt. */
#define USBFSH_HCINTERRUPTENABLE_UE(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_UE_SHIFT)) & USBFSH_HCINTERRUPTENABLE_UE_MASK)

#define USBFSH_HCINTERRUPTENABLE_FNO_MASK        (0x20U)
#define USBFSH_HCINTERRUPTENABLE_FNO_SHIFT       (5U)
/*! FNO - Frame Number Overflow interrupt. */
#define USBFSH_HCINTERRUPTENABLE_FNO(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_FNO_SHIFT)) & USBFSH_HCINTERRUPTENABLE_FNO_MASK)

#define USBFSH_HCINTERRUPTENABLE_RHSC_MASK       (0x40U)
#define USBFSH_HCINTERRUPTENABLE_RHSC_SHIFT      (6U)
/*! RHSC - Root Hub Status Change interrupt. */
#define USBFSH_HCINTERRUPTENABLE_RHSC(x)         (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_RHSC_SHIFT)) & USBFSH_HCINTERRUPTENABLE_RHSC_MASK)

#define USBFSH_HCINTERRUPTENABLE_OC_MASK         (0x40000000U)
#define USBFSH_HCINTERRUPTENABLE_OC_SHIFT        (30U)
/*! OC - Ownership Change interrupt. */
#define USBFSH_HCINTERRUPTENABLE_OC(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_OC_SHIFT)) & USBFSH_HCINTERRUPTENABLE_OC_MASK)

#define USBFSH_HCINTERRUPTENABLE_MIE_MASK        (0x80000000U)
#define USBFSH_HCINTERRUPTENABLE_MIE_SHIFT       (31U)
/*! MIE - Master Interrupt Enable. */
#define USBFSH_HCINTERRUPTENABLE_MIE(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_MIE_SHIFT)) & USBFSH_HCINTERRUPTENABLE_MIE_MASK)
/*! @} */

/*! @name HCINTERRUPTDISABLE - The bits in this register are used to disable corresponding bits in the HCInterruptStatus register and in turn disable that event leading to hardware interrupt */
/*! @{ */

#define USBFSH_HCINTERRUPTDISABLE_SO_MASK        (0x1U)
#define USBFSH_HCINTERRUPTDISABLE_SO_SHIFT       (0U)
/*! SO - Scheduling Overrun interrupt. */
#define USBFSH_HCINTERRUPTDISABLE_SO(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_SO_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_SO_MASK)

#define USBFSH_HCINTERRUPTDISABLE_WDH_MASK       (0x2U)
#define USBFSH_HCINTERRUPTDISABLE_WDH_SHIFT      (1U)
/*! WDH - HcDoneHead Writeback interrupt. */
#define USBFSH_HCINTERRUPTDISABLE_WDH(x)         (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_WDH_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_WDH_MASK)

#define USBFSH_HCINTERRUPTDISABLE_SF_MASK        (0x4U)
#define USBFSH_HCINTERRUPTDISABLE_SF_SHIFT       (2U)
/*! SF - Start of Frame interrupt. */
#define USBFSH_HCINTERRUPTDISABLE_SF(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_SF_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_SF_MASK)

#define USBFSH_HCINTERRUPTDISABLE_RD_MASK        (0x8U)
#define USBFSH_HCINTERRUPTDISABLE_RD_SHIFT       (3U)
/*! RD - Resume Detect interrupt. */
#define USBFSH_HCINTERRUPTDISABLE_RD(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_RD_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_RD_MASK)

#define USBFSH_HCINTERRUPTDISABLE_UE_MASK        (0x10U)
#define USBFSH_HCINTERRUPTDISABLE_UE_SHIFT       (4U)
/*! UE - Unrecoverable Error interrupt. */
#define USBFSH_HCINTERRUPTDISABLE_UE(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_UE_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_UE_MASK)

#define USBFSH_HCINTERRUPTDISABLE_FNO_MASK       (0x20U)
#define USBFSH_HCINTERRUPTDISABLE_FNO_SHIFT      (5U)
/*! FNO - Frame Number Overflow interrupt. */
#define USBFSH_HCINTERRUPTDISABLE_FNO(x)         (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_FNO_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_FNO_MASK)

#define USBFSH_HCINTERRUPTDISABLE_RHSC_MASK      (0x40U)
#define USBFSH_HCINTERRUPTDISABLE_RHSC_SHIFT     (6U)
/*! RHSC - Root Hub Status Change interrupt. */
#define USBFSH_HCINTERRUPTDISABLE_RHSC(x)        (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_RHSC_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_RHSC_MASK)

#define USBFSH_HCINTERRUPTDISABLE_OC_MASK        (0x40000000U)
#define USBFSH_HCINTERRUPTDISABLE_OC_SHIFT       (30U)
/*! OC - Ownership Change interrupt. */
#define USBFSH_HCINTERRUPTDISABLE_OC(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_OC_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_OC_MASK)

#define USBFSH_HCINTERRUPTDISABLE_MIE_MASK       (0x80000000U)
#define USBFSH_HCINTERRUPTDISABLE_MIE_SHIFT      (31U)
/*! MIE - A 0 written to this field is ignored by HC. */
#define USBFSH_HCINTERRUPTDISABLE_MIE(x)         (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_MIE_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_MIE_MASK)
/*! @} */

/*! @name HCHCCA - Contains the physical address of the host controller communication area */
/*! @{ */

#define USBFSH_HCHCCA_HCCA_MASK                  (0xFFFFFF00U)
#define USBFSH_HCHCCA_HCCA_SHIFT                 (8U)
/*! HCCA - Base address of the Host Controller Communication Area. */
#define USBFSH_HCHCCA_HCCA(x)                    (((uint32_t)(((uint32_t)(x)) << USBFSH_HCHCCA_HCCA_SHIFT)) & USBFSH_HCHCCA_HCCA_MASK)
/*! @} */

/*! @name HCPERIODCURRENTED - Contains the physical address of the current isochronous or interrupt endpoint descriptor */
/*! @{ */

#define USBFSH_HCPERIODCURRENTED_PCED_MASK       (0xFFFFFFF0U)
#define USBFSH_HCPERIODCURRENTED_PCED_SHIFT      (4U)
/*! PCED - The content of this register is updated by HC after a periodic ED is processed. */
#define USBFSH_HCPERIODCURRENTED_PCED(x)         (((uint32_t)(((uint32_t)(x)) << USBFSH_HCPERIODCURRENTED_PCED_SHIFT)) & USBFSH_HCPERIODCURRENTED_PCED_MASK)
/*! @} */

/*! @name HCCONTROLHEADED - Contains the physical address of the first endpoint descriptor of the control list */
/*! @{ */

#define USBFSH_HCCONTROLHEADED_CHED_MASK         (0xFFFFFFF0U)
#define USBFSH_HCCONTROLHEADED_CHED_SHIFT        (4U)
/*! CHED - HC traverses the Control list starting with the HcControlHeadED pointer. */
#define USBFSH_HCCONTROLHEADED_CHED(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROLHEADED_CHED_SHIFT)) & USBFSH_HCCONTROLHEADED_CHED_MASK)
/*! @} */

/*! @name HCCONTROLCURRENTED - Contains the physical address of the current endpoint descriptor of the control list */
/*! @{ */

#define USBFSH_HCCONTROLCURRENTED_CCED_MASK      (0xFFFFFFF0U)
#define USBFSH_HCCONTROLCURRENTED_CCED_SHIFT     (4U)
/*! CCED - ControlCurrentED. */
#define USBFSH_HCCONTROLCURRENTED_CCED(x)        (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROLCURRENTED_CCED_SHIFT)) & USBFSH_HCCONTROLCURRENTED_CCED_MASK)
/*! @} */

/*! @name HCBULKHEADED - Contains the physical address of the first endpoint descriptor of the bulk list */
/*! @{ */

#define USBFSH_HCBULKHEADED_BHED_MASK            (0xFFFFFFF0U)
#define USBFSH_HCBULKHEADED_BHED_SHIFT           (4U)
/*! BHED - BulkHeadED HC traverses the bulk list starting with the HcBulkHeadED pointer. */
#define USBFSH_HCBULKHEADED_BHED(x)              (((uint32_t)(((uint32_t)(x)) << USBFSH_HCBULKHEADED_BHED_SHIFT)) & USBFSH_HCBULKHEADED_BHED_MASK)
/*! @} */

/*! @name HCBULKCURRENTED - Contains the physical address of the current endpoint descriptor of the bulk list */
/*! @{ */

#define USBFSH_HCBULKCURRENTED_BCED_MASK         (0xFFFFFFF0U)
#define USBFSH_HCBULKCURRENTED_BCED_SHIFT        (4U)
/*! BCED - BulkCurrentED This is advanced to the next ED after the HC has served the current one. */
#define USBFSH_HCBULKCURRENTED_BCED(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCBULKCURRENTED_BCED_SHIFT)) & USBFSH_HCBULKCURRENTED_BCED_MASK)
/*! @} */

/*! @name HCDONEHEAD - Contains the physical address of the last transfer descriptor added to the 'Done' queue */
/*! @{ */

#define USBFSH_HCDONEHEAD_DH_MASK                (0xFFFFFFF0U)
#define USBFSH_HCDONEHEAD_DH_SHIFT               (4U)
/*! DH - DoneHead When a TD is completed, HC writes the content of HcDoneHead to the NextTD field of the TD. */
#define USBFSH_HCDONEHEAD_DH(x)                  (((uint32_t)(((uint32_t)(x)) << USBFSH_HCDONEHEAD_DH_SHIFT)) & USBFSH_HCDONEHEAD_DH_MASK)
/*! @} */

/*! @name HCFMINTERVAL - Defines the bit time interval in a frame and the full speed maximum packet size which would not cause an overrun */
/*! @{ */

#define USBFSH_HCFMINTERVAL_FI_MASK              (0x3FFFU)
#define USBFSH_HCFMINTERVAL_FI_SHIFT             (0U)
/*! FI - FrameInterval This specifies the interval between two consecutive SOFs in bit times. */
#define USBFSH_HCFMINTERVAL_FI(x)                (((uint32_t)(((uint32_t)(x)) << USBFSH_HCFMINTERVAL_FI_SHIFT)) & USBFSH_HCFMINTERVAL_FI_MASK)

#define USBFSH_HCFMINTERVAL_FSMPS_MASK           (0x7FFF0000U)
#define USBFSH_HCFMINTERVAL_FSMPS_SHIFT          (16U)
/*! FSMPS - FSLargestDataPacket This field specifies a value which is loaded into the Largest Data
 *    Packet Counter at the beginning of each frame.
 */
#define USBFSH_HCFMINTERVAL_FSMPS(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCFMINTERVAL_FSMPS_SHIFT)) & USBFSH_HCFMINTERVAL_FSMPS_MASK)

#define USBFSH_HCFMINTERVAL_FIT_MASK             (0x80000000U)
#define USBFSH_HCFMINTERVAL_FIT_SHIFT            (31U)
/*! FIT - FrameIntervalToggle HCD toggles this bit whenever it loads a new value to FrameInterval. */
#define USBFSH_HCFMINTERVAL_FIT(x)               (((uint32_t)(((uint32_t)(x)) << USBFSH_HCFMINTERVAL_FIT_SHIFT)) & USBFSH_HCFMINTERVAL_FIT_MASK)
/*! @} */

/*! @name HCFMREMAINING - A 14-bit counter showing the bit time remaining in the current frame */
/*! @{ */

#define USBFSH_HCFMREMAINING_FR_MASK             (0x3FFFU)
#define USBFSH_HCFMREMAINING_FR_SHIFT            (0U)
/*! FR - FrameRemaining This counter is decremented at each bit time. */
#define USBFSH_HCFMREMAINING_FR(x)               (((uint32_t)(((uint32_t)(x)) << USBFSH_HCFMREMAINING_FR_SHIFT)) & USBFSH_HCFMREMAINING_FR_MASK)

#define USBFSH_HCFMREMAINING_FRT_MASK            (0x80000000U)
#define USBFSH_HCFMREMAINING_FRT_SHIFT           (31U)
/*! FRT - FrameRemainingToggle This bit is loaded from the FrameIntervalToggle field of HcFmInterval
 *    whenever FrameRemaining reaches 0.
 */
#define USBFSH_HCFMREMAINING_FRT(x)              (((uint32_t)(((uint32_t)(x)) << USBFSH_HCFMREMAINING_FRT_SHIFT)) & USBFSH_HCFMREMAINING_FRT_MASK)
/*! @} */

/*! @name HCFMNUMBER - Contains a 16-bit counter and provides the timing reference among events happening in the HC and the HCD */
/*! @{ */

#define USBFSH_HCFMNUMBER_FN_MASK                (0xFFFFU)
#define USBFSH_HCFMNUMBER_FN_SHIFT               (0U)
/*! FN - FrameNumber This is incremented when HcFmRemaining is re-loaded. */
#define USBFSH_HCFMNUMBER_FN(x)                  (((uint32_t)(((uint32_t)(x)) << USBFSH_HCFMNUMBER_FN_SHIFT)) & USBFSH_HCFMNUMBER_FN_MASK)
/*! @} */

/*! @name HCPERIODICSTART - Contains a programmable 14-bit value which determines the earliest time HC should start processing a periodic list */
/*! @{ */

#define USBFSH_HCPERIODICSTART_PS_MASK           (0x3FFFU)
#define USBFSH_HCPERIODICSTART_PS_SHIFT          (0U)
/*! PS - PeriodicStart After a hardware reset, this field is cleared and then set by HCD during the HC initialization. */
#define USBFSH_HCPERIODICSTART_PS(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCPERIODICSTART_PS_SHIFT)) & USBFSH_HCPERIODICSTART_PS_MASK)
/*! @} */

/*! @name HCLSTHRESHOLD - Contains 11-bit value which is used by the HC to determine whether to commit to transfer a maximum of 8-byte LS packet before EOF */
/*! @{ */

#define USBFSH_HCLSTHRESHOLD_LST_MASK            (0xFFFU)
#define USBFSH_HCLSTHRESHOLD_LST_SHIFT           (0U)
/*! LST - LSThreshold This field contains a value which is compared to the FrameRemaining field
 *    prior to initiating a Low Speed transaction.
 */
#define USBFSH_HCLSTHRESHOLD_LST(x)              (((uint32_t)(((uint32_t)(x)) << USBFSH_HCLSTHRESHOLD_LST_SHIFT)) & USBFSH_HCLSTHRESHOLD_LST_MASK)
/*! @} */

/*! @name HCRHDESCRIPTORA - First of the two registers which describes the characteristics of the root hub */
/*! @{ */

#define USBFSH_HCRHDESCRIPTORA_NDP_MASK          (0xFFU)
#define USBFSH_HCRHDESCRIPTORA_NDP_SHIFT         (0U)
/*! NDP - NumberDownstreamPorts These bits specify the number of downstream ports supported by the root hub. */
#define USBFSH_HCRHDESCRIPTORA_NDP(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORA_NDP_SHIFT)) & USBFSH_HCRHDESCRIPTORA_NDP_MASK)

#define USBFSH_HCRHDESCRIPTORA_PSM_MASK          (0x100U)
#define USBFSH_HCRHDESCRIPTORA_PSM_SHIFT         (8U)
/*! PSM - PowerSwitchingMode This bit is used to specify how the power switching of the root hub ports is controlled. */
#define USBFSH_HCRHDESCRIPTORA_PSM(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORA_PSM_SHIFT)) & USBFSH_HCRHDESCRIPTORA_PSM_MASK)

#define USBFSH_HCRHDESCRIPTORA_NPS_MASK          (0x200U)
#define USBFSH_HCRHDESCRIPTORA_NPS_SHIFT         (9U)
/*! NPS - NoPowerSwitching These bits are used to specify whether power switching is supported or port are always powered. */
#define USBFSH_HCRHDESCRIPTORA_NPS(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORA_NPS_SHIFT)) & USBFSH_HCRHDESCRIPTORA_NPS_MASK)

#define USBFSH_HCRHDESCRIPTORA_DT_MASK           (0x400U)
#define USBFSH_HCRHDESCRIPTORA_DT_SHIFT          (10U)
/*! DT - DeviceType This bit specifies that the root hub is not a compound device. */
#define USBFSH_HCRHDESCRIPTORA_DT(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORA_DT_SHIFT)) & USBFSH_HCRHDESCRIPTORA_DT_MASK)

#define USBFSH_HCRHDESCRIPTORA_OCPM_MASK         (0x800U)
#define USBFSH_HCRHDESCRIPTORA_OCPM_SHIFT        (11U)
/*! OCPM - OverCurrentProtectionMode This bit describes how the overcurrent status for the root hub ports are reported. */
#define USBFSH_HCRHDESCRIPTORA_OCPM(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORA_OCPM_SHIFT)) & USBFSH_HCRHDESCRIPTORA_OCPM_MASK)

#define USBFSH_HCRHDESCRIPTORA_NOCP_MASK         (0x1000U)
#define USBFSH_HCRHDESCRIPTORA_NOCP_SHIFT        (12U)
/*! NOCP - NoOverCurrentProtection This bit describes how the overcurrent status for the root hub ports are reported. */
#define USBFSH_HCRHDESCRIPTORA_NOCP(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORA_NOCP_SHIFT)) & USBFSH_HCRHDESCRIPTORA_NOCP_MASK)

#define USBFSH_HCRHDESCRIPTORA_POTPGT_MASK       (0xFF000000U)
#define USBFSH_HCRHDESCRIPTORA_POTPGT_SHIFT      (24U)
/*! POTPGT - PowerOnToPowerGoodTime This byte specifies the duration the HCD has to wait before
 *    accessing a powered-on port of the root hub.
 */
#define USBFSH_HCRHDESCRIPTORA_POTPGT(x)         (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORA_POTPGT_SHIFT)) & USBFSH_HCRHDESCRIPTORA_POTPGT_MASK)
/*! @} */

/*! @name HCRHDESCRIPTORB - Second of the two registers which describes the characteristics of the Root Hub */
/*! @{ */

#define USBFSH_HCRHDESCRIPTORB_DR_MASK           (0xFFFFU)
#define USBFSH_HCRHDESCRIPTORB_DR_SHIFT          (0U)
/*! DR - DeviceRemovable Each bit is dedicated to a port of the Root Hub. */
#define USBFSH_HCRHDESCRIPTORB_DR(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORB_DR_SHIFT)) & USBFSH_HCRHDESCRIPTORB_DR_MASK)

#define USBFSH_HCRHDESCRIPTORB_PPCM_MASK         (0xFFFF0000U)
#define USBFSH_HCRHDESCRIPTORB_PPCM_SHIFT        (16U)
/*! PPCM - PortPowerControlMask Each bit indicates if a port is affected by a global power control
 *    command when PowerSwitchingMode is set.
 */
#define USBFSH_HCRHDESCRIPTORB_PPCM(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORB_PPCM_SHIFT)) & USBFSH_HCRHDESCRIPTORB_PPCM_MASK)
/*! @} */

/*! @name HCRHSTATUS - This register is divided into two parts */
/*! @{ */

#define USBFSH_HCRHSTATUS_LPS_MASK               (0x1U)
#define USBFSH_HCRHSTATUS_LPS_SHIFT              (0U)
/*! LPS - (read) LocalPowerStatus The Root Hub does not support the local power status feature;
 *    thus, this bit is always read as 0.
 */
#define USBFSH_HCRHSTATUS_LPS(x)                 (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHSTATUS_LPS_SHIFT)) & USBFSH_HCRHSTATUS_LPS_MASK)

#define USBFSH_HCRHSTATUS_OCI_MASK               (0x2U)
#define USBFSH_HCRHSTATUS_OCI_SHIFT              (1U)
/*! OCI - OverCurrentIndicator This bit reports overcurrent conditions when the global reporting is implemented. */
#define USBFSH_HCRHSTATUS_OCI(x)                 (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHSTATUS_OCI_SHIFT)) & USBFSH_HCRHSTATUS_OCI_MASK)

#define USBFSH_HCRHSTATUS_DRWE_MASK              (0x8000U)
#define USBFSH_HCRHSTATUS_DRWE_SHIFT             (15U)
/*! DRWE - (read) DeviceRemoteWakeupEnable This bit enables a ConnectStatusChange bit as a resume
 *    event, causing a USBSUSPEND to USBRESUME state transition and setting the ResumeDetected
 *    interrupt.
 */
#define USBFSH_HCRHSTATUS_DRWE(x)                (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHSTATUS_DRWE_SHIFT)) & USBFSH_HCRHSTATUS_DRWE_MASK)

#define USBFSH_HCRHSTATUS_LPSC_MASK              (0x10000U)
#define USBFSH_HCRHSTATUS_LPSC_SHIFT             (16U)
/*! LPSC - (read) LocalPowerStatusChange The root hub does not support the local power status feature. */
#define USBFSH_HCRHSTATUS_LPSC(x)                (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHSTATUS_LPSC_SHIFT)) & USBFSH_HCRHSTATUS_LPSC_MASK)

#define USBFSH_HCRHSTATUS_OCIC_MASK              (0x20000U)
#define USBFSH_HCRHSTATUS_OCIC_SHIFT             (17U)
/*! OCIC - OverCurrentIndicatorChange This bit is set by hardware when a change has occurred to the OCI field of this register. */
#define USBFSH_HCRHSTATUS_OCIC(x)                (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHSTATUS_OCIC_SHIFT)) & USBFSH_HCRHSTATUS_OCIC_MASK)

#define USBFSH_HCRHSTATUS_CRWE_MASK              (0x80000000U)
#define USBFSH_HCRHSTATUS_CRWE_SHIFT             (31U)
/*! CRWE - (write) ClearRemoteWakeupEnable Writing a 1 clears DeviceRemoveWakeupEnable. */
#define USBFSH_HCRHSTATUS_CRWE(x)                (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHSTATUS_CRWE_SHIFT)) & USBFSH_HCRHSTATUS_CRWE_MASK)
/*! @} */

/*! @name HCRHPORTSTATUS - Controls and reports the port events on a per-port basis */
/*! @{ */

#define USBFSH_HCRHPORTSTATUS_CCS_MASK           (0x1U)
#define USBFSH_HCRHPORTSTATUS_CCS_SHIFT          (0U)
/*! CCS - (read) CurrentConnectStatus This bit reflects the current state of the downstream port. */
#define USBFSH_HCRHPORTSTATUS_CCS(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_CCS_SHIFT)) & USBFSH_HCRHPORTSTATUS_CCS_MASK)

#define USBFSH_HCRHPORTSTATUS_PES_MASK           (0x2U)
#define USBFSH_HCRHPORTSTATUS_PES_SHIFT          (1U)
/*! PES - (read) PortEnableStatus This bit indicates whether the port is enabled or disabled. */
#define USBFSH_HCRHPORTSTATUS_PES(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_PES_SHIFT)) & USBFSH_HCRHPORTSTATUS_PES_MASK)

#define USBFSH_HCRHPORTSTATUS_PSS_MASK           (0x4U)
#define USBFSH_HCRHPORTSTATUS_PSS_SHIFT          (2U)
/*! PSS - (read) PortSuspendStatus This bit indicates the port is suspended or in the resume sequence. */
#define USBFSH_HCRHPORTSTATUS_PSS(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_PSS_SHIFT)) & USBFSH_HCRHPORTSTATUS_PSS_MASK)

#define USBFSH_HCRHPORTSTATUS_POCI_MASK          (0x8U)
#define USBFSH_HCRHPORTSTATUS_POCI_SHIFT         (3U)
/*! POCI - (read) PortOverCurrentIndicator This bit is only valid when the Root Hub is configured in
 *    such a way that overcurrent conditions are reported on a per-port basis.
 */
#define USBFSH_HCRHPORTSTATUS_POCI(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_POCI_SHIFT)) & USBFSH_HCRHPORTSTATUS_POCI_MASK)

#define USBFSH_HCRHPORTSTATUS_PRS_MASK           (0x10U)
#define USBFSH_HCRHPORTSTATUS_PRS_SHIFT          (4U)
/*! PRS - (read) PortResetStatus When this bit is set by a write to SetPortReset, port reset signaling is asserted. */
#define USBFSH_HCRHPORTSTATUS_PRS(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_PRS_SHIFT)) & USBFSH_HCRHPORTSTATUS_PRS_MASK)

#define USBFSH_HCRHPORTSTATUS_PPS_MASK           (0x100U)
#define USBFSH_HCRHPORTSTATUS_PPS_SHIFT          (8U)
/*! PPS - (read) PortPowerStatus This bit reflects the porta's power status, regardless of the type
 *    of power switching implemented.
 */
#define USBFSH_HCRHPORTSTATUS_PPS(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_PPS_SHIFT)) & USBFSH_HCRHPORTSTATUS_PPS_MASK)

#define USBFSH_HCRHPORTSTATUS_LSDA_MASK          (0x200U)
#define USBFSH_HCRHPORTSTATUS_LSDA_SHIFT         (9U)
/*! LSDA - (read) LowSpeedDeviceAttached This bit indicates the speed of the device attached to this port. */
#define USBFSH_HCRHPORTSTATUS_LSDA(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_LSDA_SHIFT)) & USBFSH_HCRHPORTSTATUS_LSDA_MASK)

#define USBFSH_HCRHPORTSTATUS_CSC_MASK           (0x10000U)
#define USBFSH_HCRHPORTSTATUS_CSC_SHIFT          (16U)
/*! CSC - ConnectStatusChange This bit is set whenever a connect or disconnect event occurs. */
#define USBFSH_HCRHPORTSTATUS_CSC(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_CSC_SHIFT)) & USBFSH_HCRHPORTSTATUS_CSC_MASK)

#define USBFSH_HCRHPORTSTATUS_PESC_MASK          (0x20000U)
#define USBFSH_HCRHPORTSTATUS_PESC_SHIFT         (17U)
/*! PESC - PortEnableStatusChange This bit is set when hardware events cause the PortEnableStatus bit to be cleared. */
#define USBFSH_HCRHPORTSTATUS_PESC(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_PESC_SHIFT)) & USBFSH_HCRHPORTSTATUS_PESC_MASK)

#define USBFSH_HCRHPORTSTATUS_PSSC_MASK          (0x40000U)
#define USBFSH_HCRHPORTSTATUS_PSSC_SHIFT         (18U)
/*! PSSC - PortSuspendStatusChange This bit is set when the full resume sequence is completed. */
#define USBFSH_HCRHPORTSTATUS_PSSC(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_PSSC_SHIFT)) & USBFSH_HCRHPORTSTATUS_PSSC_MASK)

#define USBFSH_HCRHPORTSTATUS_OCIC_MASK          (0x80000U)
#define USBFSH_HCRHPORTSTATUS_OCIC_SHIFT         (19U)
/*! OCIC - PortOverCurrentIndicatorChange This bit is valid only if overcurrent conditions are reported on a per-port basis. */
#define USBFSH_HCRHPORTSTATUS_OCIC(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_OCIC_SHIFT)) & USBFSH_HCRHPORTSTATUS_OCIC_MASK)

#define USBFSH_HCRHPORTSTATUS_PRSC_MASK          (0x100000U)
#define USBFSH_HCRHPORTSTATUS_PRSC_SHIFT         (20U)
/*! PRSC - PortResetStatusChange This bit is set at the end of the 10 ms port reset signal. */
#define USBFSH_HCRHPORTSTATUS_PRSC(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_PRSC_SHIFT)) & USBFSH_HCRHPORTSTATUS_PRSC_MASK)
/*! @} */

/*! @name PORTMODE - Controls the port if it is attached to the host block or the device block */
/*! @{ */

#define USBFSH_PORTMODE_ID_MASK                  (0x1U)
#define USBFSH_PORTMODE_ID_SHIFT                 (0U)
/*! ID - Port ID pin value. */
#define USBFSH_PORTMODE_ID(x)                    (((uint32_t)(((uint32_t)(x)) << USBFSH_PORTMODE_ID_SHIFT)) & USBFSH_PORTMODE_ID_MASK)

#define USBFSH_PORTMODE_ID_EN_MASK               (0x100U)
#define USBFSH_PORTMODE_ID_EN_SHIFT              (8U)
/*! ID_EN - Port ID pin pull-up enable. */
#define USBFSH_PORTMODE_ID_EN(x)                 (((uint32_t)(((uint32_t)(x)) << USBFSH_PORTMODE_ID_EN_SHIFT)) & USBFSH_PORTMODE_ID_EN_MASK)

#define USBFSH_PORTMODE_DEV_ENABLE_MASK          (0x10000U)
#define USBFSH_PORTMODE_DEV_ENABLE_SHIFT         (16U)
/*! DEV_ENABLE - 1: device 0: host. */
#define USBFSH_PORTMODE_DEV_ENABLE(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_PORTMODE_DEV_ENABLE_SHIFT)) & USBFSH_PORTMODE_DEV_ENABLE_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group USBFSH_Register_Masks */


/*!
 * @}
 */ /* end of group USBFSH_Peripheral_Access_Layer */


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


#endif  /* USBFSH_H_ */


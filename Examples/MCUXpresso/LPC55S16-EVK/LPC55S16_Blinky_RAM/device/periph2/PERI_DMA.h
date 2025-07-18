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
**         CMSIS Peripheral Access Layer for DMA
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
 * @file DMA.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for DMA
 *
 * CMSIS Peripheral Access Layer for DMA
 */

#if !defined(DMA_H_)
#define DMA_H_                                   /**< Symbol preventing repeated inclusion */

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
   -- Mapping Information
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Mapping_Information Mapping Information
 * @{
 */

/** Mapping Information */
#if !defined(DMA_REQUEST_SOURCE_T_)
#define DMA_REQUEST_SOURCE_T_
/*!
 * @addtogroup dma_request
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Structure for the DMA hardware request
 *
 * Defines the structure for the DMA hardware request collections. The user can configure the
 * hardware request to trigger the DMA transfer accordingly. The index
 * of the hardware request varies according  to the to SoC.
 */
typedef enum _dma_request_source
{
    kDma0RequestNoDMARequest1       = 1U,          /**< No DMA request 1 */
    kDma1RequestNoDMARequest1       = 1U,          /**< No DMA request 1 */
    kDma0RequestFlexcomm8Rx         = 2U,          /**< Flexcomm Interface 8 RX */
    kDma1RequestFlexcomm8Rx         = 2U,          /**< Flexcomm Interface 8 RX */
    kDma0RequestFlexcomm8Tx         = 3U,          /**< Flexcomm Interface 8 TX */
    kDma1RequestFlexcomm8Tx         = 3U,          /**< Flexcomm Interface 8 TX */
    kDma0RequestFlexcomm0Rx         = 4U,          /**< Flexcomm Interface 0 RX/I2C Slave */
    kDma1RequestFlexcomm0Rx         = 4U,          /**< Flexcomm Interface 0 RX/I2C Slave */
    kDma0RequestFlexcomm0Tx         = 5U,          /**< Flexcomm Interface 0 TX/I2C Master */
    kDma1RequestFlexcomm0Tx         = 5U,          /**< Flexcomm Interface 0 TX/I2C Master */
    kDma0RequestFlexcomm1Rx         = 6U,          /**< Flexcomm Interface 1 RX/I2C Slave */
    kDma1RequestFlexcomm1Rx         = 6U,          /**< Flexcomm Interface 1 RX/I2C Slave */
    kDma0RequestFlexcomm1Tx         = 7U,          /**< Flexcomm Interface 1 TX/I2C Master */
    kDma1RequestFlexcomm1Tx         = 7U,          /**< Flexcomm Interface 1 TX/I2C Master */
    kDma0RequestFlexcomm3Rx         = 8U,          /**< Flexcomm Interface 3 RX/I2C Slave */
    kDma1RequestFlexcomm3Rx         = 8U,          /**< Flexcomm Interface 3 RX/I2C Slave */
    kDma0RequestFlexcomm3Tx         = 9U,          /**< Flexcomm Interface 3 TX/I2C Master */
    kDma1RequestFlexcomm3Tx         = 9U,          /**< Flexcomm Interface 3 TX/I2C Master */
    kDma0RequestFlexcomm2Rx         = 10U,         /**< Flexcomm Interface 2 RX/I2C Slave */
    kDma0RequestFlexcomm2Tx         = 11U,         /**< Flexcomm Interface 2 TX/I2C Master */
    kDma0RequestFlexcomm4Rx         = 12U,         /**< Flexcomm Interface 4 RX/I2C Slave */
    kDma0RequestFlexcomm4Tx         = 13U,         /**< Flexcomm Interface 4 TX/I2C Master */
    kDma0RequestFlexcomm5Rx         = 14U,         /**< Flexcomm Interface 5 RX/I2C Slave */
    kDma0RequestFlexcomm5Tx         = 15U,         /**< Flexcomm Interface 5 TX/I2C Master */
    kDma0RequestFlexcomm6Rx         = 16U,         /**< Flexcomm Interface 6 RX/I2C Slave */
    kDma0RequestFlexcomm6Tx         = 17U,         /**< Flexcomm Interface 6 TX/I2C Master */
    kDma0RequestFlexcomm7Rx         = 18U,         /**< Flexcomm Interface 7 RX/I2C Slave */
    kDma0RequestFlexcomm7Tx         = 19U,         /**< Flexcomm Interface 7 TX/I2C Master */
    kDma0RequestNoDMARequest20      = 20U,         /**< No DMA request 20 */
    kDma0RequestADC0FIFO0           = 21U,         /**< ADC0 FIFO 0 */
    kDma0RequestADC0FIFO1           = 22U,         /**< ADC0 FIFO 1 */
    kDma0RequestHashCrypt           = 0U,          /**< HashCrypt */
    kDma1RequestHashCrypt           = 0U,          /**< HashCrypt */
} dma_request_source_t;

/* @} */
#endif /* DMA_REQUEST_SOURCE_T_ */


/*!
 * @}
 */ /* end of group Mapping_Information */


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
   -- DMA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Peripheral_Access_Layer DMA Peripheral Access Layer
 * @{
 */

/** DMA - Size of Registers Arrays */
#define DMA_COMMON_COUNT                          1u
#define DMA_CHANNEL_COUNT                         23u

/** DMA - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< DMA control., offset: 0x0 */
  __I  uint32_t INTSTAT;                           /**< Interrupt status., offset: 0x4 */
  __IO uint32_t SRAMBASE;                          /**< SRAM address of the channel configuration table., offset: 0x8 */
       uint8_t RESERVED_0[20];
  struct {                                         /* offset: 0x20, array step: 0x5C */
    __IO uint32_t ENABLESET;                         /**< Channel Enable read and Set for all DMA channels., array offset: 0x20, array step: 0x5C */
         uint8_t RESERVED_0[4];
    __O  uint32_t ENABLECLR;                         /**< Channel Enable Clear for all DMA channels., array offset: 0x28, array step: 0x5C */
         uint8_t RESERVED_1[4];
    __I  uint32_t ACTIVE;                            /**< Channel Active status for all DMA channels., array offset: 0x30, array step: 0x5C */
         uint8_t RESERVED_2[4];
    __I  uint32_t BUSY;                              /**< Channel Busy status for all DMA channels., array offset: 0x38, array step: 0x5C */
         uint8_t RESERVED_3[4];
    __IO uint32_t ERRINT;                            /**< Error Interrupt status for all DMA channels., array offset: 0x40, array step: 0x5C */
         uint8_t RESERVED_4[4];
    __IO uint32_t INTENSET;                          /**< Interrupt Enable read and Set for all DMA channels., array offset: 0x48, array step: 0x5C */
         uint8_t RESERVED_5[4];
    __O  uint32_t INTENCLR;                          /**< Interrupt Enable Clear for all DMA channels., array offset: 0x50, array step: 0x5C */
         uint8_t RESERVED_6[4];
    __IO uint32_t INTA;                              /**< Interrupt A status for all DMA channels., array offset: 0x58, array step: 0x5C */
         uint8_t RESERVED_7[4];
    __IO uint32_t INTB;                              /**< Interrupt B status for all DMA channels., array offset: 0x60, array step: 0x5C */
         uint8_t RESERVED_8[4];
    __O  uint32_t SETVALID;                          /**< Set ValidPending control bits for all DMA channels., array offset: 0x68, array step: 0x5C */
         uint8_t RESERVED_9[4];
    __O  uint32_t SETTRIG;                           /**< Set Trigger control bits for all DMA channels., array offset: 0x70, array step: 0x5C */
         uint8_t RESERVED_10[4];
    __O  uint32_t ABORT;                             /**< Channel Abort control for all DMA channels., array offset: 0x78, array step: 0x5C */
  } COMMON[DMA_COMMON_COUNT];
       uint8_t RESERVED_1[900];
  struct {                                         /* offset: 0x400, array step: 0x10 */
    __IO uint32_t CFG;                               /**< Configuration register for DMA channel ., array offset: 0x400, array step: 0x10, irregular array, not all indices are valid */
    __I  uint32_t CTLSTAT;                           /**< Control and status register for DMA channel ., array offset: 0x404, array step: 0x10, irregular array, not all indices are valid */
    __IO uint32_t XFERCFG;                           /**< Transfer configuration register for DMA channel ., array offset: 0x408, array step: 0x10, irregular array, not all indices are valid */
         uint8_t RESERVED_0[4];
  } CHANNEL[DMA_CHANNEL_COUNT];
} DMA_Type;

/* ----------------------------------------------------------------------------
   -- DMA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Register_Masks DMA Register Masks
 * @{
 */

/*! @name CTRL - DMA control. */
/*! @{ */

#define DMA_CTRL_ENABLE_MASK                     (0x1U)
#define DMA_CTRL_ENABLE_SHIFT                    (0U)
/*! ENABLE - DMA controller master enable.
 *  0b0..Disabled. The DMA controller is disabled. This clears any triggers that were asserted at the point when
 *       disabled, but does not prevent re-triggering when the DMA controller is re-enabled.
 *  0b1..Enabled. The DMA controller is enabled.
 */
#define DMA_CTRL_ENABLE(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_CTRL_ENABLE_SHIFT)) & DMA_CTRL_ENABLE_MASK)
/*! @} */

/*! @name INTSTAT - Interrupt status. */
/*! @{ */

#define DMA_INTSTAT_ACTIVEINT_MASK               (0x2U)
#define DMA_INTSTAT_ACTIVEINT_SHIFT              (1U)
/*! ACTIVEINT - Summarizes whether any enabled interrupts (other than error interrupts) are pending.
 *  0b0..Not pending. No enabled interrupts are pending.
 *  0b1..Pending. At least one enabled interrupt is pending.
 */
#define DMA_INTSTAT_ACTIVEINT(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_INTSTAT_ACTIVEINT_SHIFT)) & DMA_INTSTAT_ACTIVEINT_MASK)

#define DMA_INTSTAT_ACTIVEERRINT_MASK            (0x4U)
#define DMA_INTSTAT_ACTIVEERRINT_SHIFT           (2U)
/*! ACTIVEERRINT - Summarizes whether any error interrupts are pending.
 *  0b0..Not pending. No error interrupts are pending.
 *  0b1..Pending. At least one error interrupt is pending.
 */
#define DMA_INTSTAT_ACTIVEERRINT(x)              (((uint32_t)(((uint32_t)(x)) << DMA_INTSTAT_ACTIVEERRINT_SHIFT)) & DMA_INTSTAT_ACTIVEERRINT_MASK)
/*! @} */

/*! @name SRAMBASE - SRAM address of the channel configuration table. */
/*! @{ */

#define DMA_SRAMBASE_OFFSET_MASK                 (0xFFFFFE00U)
#define DMA_SRAMBASE_OFFSET_SHIFT                (9U)
/*! OFFSET - Address bits 31:9 of the beginning of the DMA descriptor table. For 18 channels, the
 *    table must begin on a 512 byte boundary.
 */
#define DMA_SRAMBASE_OFFSET(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_SRAMBASE_OFFSET_SHIFT)) & DMA_SRAMBASE_OFFSET_MASK)
/*! @} */

/*! @name COMMON_ENABLESET - Channel Enable read and Set for all DMA channels. */
/*! @{ */

#define DMA_COMMON_ENABLESET_ENA_MASK            (0xFFFFFFFFU)
#define DMA_COMMON_ENABLESET_ENA_SHIFT           (0U)
/*! ENA - Enable for DMA channels. Bit n enables or disables DMA channel n. The number of bits =
 *    number of DMA channels in this device. Other bits are reserved. 0 = disabled. 1 = enabled.
 */
#define DMA_COMMON_ENABLESET_ENA(x)              (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_ENABLESET_ENA_SHIFT)) & DMA_COMMON_ENABLESET_ENA_MASK)
/*! @} */

/* The count of DMA_COMMON_ENABLESET */
#define DMA_COMMON_ENABLESET_COUNT               (1U)

/*! @name COMMON_ENABLECLR - Channel Enable Clear for all DMA channels. */
/*! @{ */

#define DMA_COMMON_ENABLECLR_CLR_MASK            (0xFFFFFFFFU)
#define DMA_COMMON_ENABLECLR_CLR_SHIFT           (0U)
/*! CLR - Writing ones to this register clears the corresponding bits in ENABLESET0. Bit n clears
 *    the channel enable bit n. The number of bits = number of DMA channels in this device. Other bits
 *    are reserved.
 */
#define DMA_COMMON_ENABLECLR_CLR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_ENABLECLR_CLR_SHIFT)) & DMA_COMMON_ENABLECLR_CLR_MASK)
/*! @} */

/* The count of DMA_COMMON_ENABLECLR */
#define DMA_COMMON_ENABLECLR_COUNT               (1U)

/*! @name COMMON_ACTIVE - Channel Active status for all DMA channels. */
/*! @{ */

#define DMA_COMMON_ACTIVE_ACT_MASK               (0xFFFFFFFFU)
#define DMA_COMMON_ACTIVE_ACT_SHIFT              (0U)
/*! ACT - Active flag for DMA channel n. Bit n corresponds to DMA channel n. The number of bits =
 *    number of DMA channels in this device. Other bits are reserved. 0 = not active. 1 = active.
 */
#define DMA_COMMON_ACTIVE_ACT(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_ACTIVE_ACT_SHIFT)) & DMA_COMMON_ACTIVE_ACT_MASK)
/*! @} */

/* The count of DMA_COMMON_ACTIVE */
#define DMA_COMMON_ACTIVE_COUNT                  (1U)

/*! @name COMMON_BUSY - Channel Busy status for all DMA channels. */
/*! @{ */

#define DMA_COMMON_BUSY_BSY_MASK                 (0xFFFFFFFFU)
#define DMA_COMMON_BUSY_BSY_SHIFT                (0U)
/*! BSY - Busy flag for DMA channel n. Bit n corresponds to DMA channel n. The number of bits =
 *    number of DMA channels in this device. Other bits are reserved. 0 = not busy. 1 = busy.
 */
#define DMA_COMMON_BUSY_BSY(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_BUSY_BSY_SHIFT)) & DMA_COMMON_BUSY_BSY_MASK)
/*! @} */

/* The count of DMA_COMMON_BUSY */
#define DMA_COMMON_BUSY_COUNT                    (1U)

/*! @name COMMON_ERRINT - Error Interrupt status for all DMA channels. */
/*! @{ */

#define DMA_COMMON_ERRINT_ERR_MASK               (0xFFFFFFFFU)
#define DMA_COMMON_ERRINT_ERR_SHIFT              (0U)
/*! ERR - Error Interrupt flag for DMA channel n. Bit n corresponds to DMA channel n. The number of
 *    bits = number of DMA channels in this device. Other bits are reserved. 0 = error interrupt is
 *    not active. 1 = error interrupt is active.
 */
#define DMA_COMMON_ERRINT_ERR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_ERRINT_ERR_SHIFT)) & DMA_COMMON_ERRINT_ERR_MASK)
/*! @} */

/* The count of DMA_COMMON_ERRINT */
#define DMA_COMMON_ERRINT_COUNT                  (1U)

/*! @name COMMON_INTENSET - Interrupt Enable read and Set for all DMA channels. */
/*! @{ */

#define DMA_COMMON_INTENSET_INTEN_MASK           (0xFFFFFFFFU)
#define DMA_COMMON_INTENSET_INTEN_SHIFT          (0U)
/*! INTEN - Interrupt Enable read and set for DMA channel n. Bit n corresponds to DMA channel n. The
 *    number of bits = number of DMA channels in this device. Other bits are reserved. 0 =
 *    interrupt for DMA channel is disabled. 1 = interrupt for DMA channel is enabled.
 */
#define DMA_COMMON_INTENSET_INTEN(x)             (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_INTENSET_INTEN_SHIFT)) & DMA_COMMON_INTENSET_INTEN_MASK)
/*! @} */

/* The count of DMA_COMMON_INTENSET */
#define DMA_COMMON_INTENSET_COUNT                (1U)

/*! @name COMMON_INTENCLR - Interrupt Enable Clear for all DMA channels. */
/*! @{ */

#define DMA_COMMON_INTENCLR_CLR_MASK             (0xFFFFFFFFU)
#define DMA_COMMON_INTENCLR_CLR_SHIFT            (0U)
/*! CLR - Writing ones to this register clears corresponding bits in the INTENSET0. Bit n
 *    corresponds to DMA channel n. The number of bits = number of DMA channels in this device. Other bits are
 *    reserved.
 */
#define DMA_COMMON_INTENCLR_CLR(x)               (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_INTENCLR_CLR_SHIFT)) & DMA_COMMON_INTENCLR_CLR_MASK)
/*! @} */

/* The count of DMA_COMMON_INTENCLR */
#define DMA_COMMON_INTENCLR_COUNT                (1U)

/*! @name COMMON_INTA - Interrupt A status for all DMA channels. */
/*! @{ */

#define DMA_COMMON_INTA_IA_MASK                  (0xFFFFFFFFU)
#define DMA_COMMON_INTA_IA_SHIFT                 (0U)
/*! IA - Interrupt A status for DMA channel n. Bit n corresponds to DMA channel n. The number of
 *    bits = number of DMA channels in this device. Other bits are reserved. 0 = the DMA channel
 *    interrupt A is not active. 1 = the DMA channel interrupt A is active.
 */
#define DMA_COMMON_INTA_IA(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_INTA_IA_SHIFT)) & DMA_COMMON_INTA_IA_MASK)
/*! @} */

/* The count of DMA_COMMON_INTA */
#define DMA_COMMON_INTA_COUNT                    (1U)

/*! @name COMMON_INTB - Interrupt B status for all DMA channels. */
/*! @{ */

#define DMA_COMMON_INTB_IB_MASK                  (0xFFFFFFFFU)
#define DMA_COMMON_INTB_IB_SHIFT                 (0U)
/*! IB - Interrupt B status for DMA channel n. Bit n corresponds to DMA channel n. The number of
 *    bits = number of DMA channels in this device. Other bits are reserved. 0 = the DMA channel
 *    interrupt B is not active. 1 = the DMA channel interrupt B is active.
 */
#define DMA_COMMON_INTB_IB(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_INTB_IB_SHIFT)) & DMA_COMMON_INTB_IB_MASK)
/*! @} */

/* The count of DMA_COMMON_INTB */
#define DMA_COMMON_INTB_COUNT                    (1U)

/*! @name COMMON_SETVALID - Set ValidPending control bits for all DMA channels. */
/*! @{ */

#define DMA_COMMON_SETVALID_SV_MASK              (0xFFFFFFFFU)
#define DMA_COMMON_SETVALID_SV_SHIFT             (0U)
/*! SV - SETVALID control for DMA channel n. Bit n corresponds to DMA channel n. The number of bits
 *    = number of DMA channels in this device. Other bits are reserved. 0 = no effect. 1 = sets the
 *    VALIDPENDING control bit for DMA channel n
 */
#define DMA_COMMON_SETVALID_SV(x)                (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_SETVALID_SV_SHIFT)) & DMA_COMMON_SETVALID_SV_MASK)
/*! @} */

/* The count of DMA_COMMON_SETVALID */
#define DMA_COMMON_SETVALID_COUNT                (1U)

/*! @name COMMON_SETTRIG - Set Trigger control bits for all DMA channels. */
/*! @{ */

#define DMA_COMMON_SETTRIG_TRIG_MASK             (0xFFFFFFFFU)
#define DMA_COMMON_SETTRIG_TRIG_SHIFT            (0U)
/*! TRIG - Set Trigger control bit for DMA channel 0. Bit n corresponds to DMA channel n. The number
 *    of bits = number of DMA channels in this device. Other bits are reserved. 0 = no effect. 1 =
 *    sets the TRIG bit for DMA channel n.
 */
#define DMA_COMMON_SETTRIG_TRIG(x)               (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_SETTRIG_TRIG_SHIFT)) & DMA_COMMON_SETTRIG_TRIG_MASK)
/*! @} */

/* The count of DMA_COMMON_SETTRIG */
#define DMA_COMMON_SETTRIG_COUNT                 (1U)

/*! @name COMMON_ABORT - Channel Abort control for all DMA channels. */
/*! @{ */

#define DMA_COMMON_ABORT_ABORTCTRL_MASK          (0xFFFFFFFFU)
#define DMA_COMMON_ABORT_ABORTCTRL_SHIFT         (0U)
/*! ABORTCTRL - Abort control for DMA channel 0. Bit n corresponds to DMA channel n. 0 = no effect.
 *    1 = aborts DMA operations on channel n.
 */
#define DMA_COMMON_ABORT_ABORTCTRL(x)            (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_ABORT_ABORTCTRL_SHIFT)) & DMA_COMMON_ABORT_ABORTCTRL_MASK)
/*! @} */

/* The count of DMA_COMMON_ABORT */
#define DMA_COMMON_ABORT_COUNT                   (1U)

/*! @name CHANNEL_CFG - Configuration register for DMA channel . */
/*! @{ */

#define DMA_CHANNEL_CFG_PERIPHREQEN_MASK         (0x1U)
#define DMA_CHANNEL_CFG_PERIPHREQEN_SHIFT        (0U)
/*! PERIPHREQEN - Peripheral request Enable. If a DMA channel is used to perform a memory-to-memory
 *    move, any peripheral DMA request associated with that channel can be disabled to prevent any
 *    interaction between the peripheral and the DMA controller.
 *  0b0..Disabled. Peripheral DMA requests are disabled.
 *  0b1..Enabled. Peripheral DMA requests are enabled.
 */
#define DMA_CHANNEL_CFG_PERIPHREQEN(x)           (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_PERIPHREQEN_SHIFT)) & DMA_CHANNEL_CFG_PERIPHREQEN_MASK)

#define DMA_CHANNEL_CFG_HWTRIGEN_MASK            (0x2U)
#define DMA_CHANNEL_CFG_HWTRIGEN_SHIFT           (1U)
/*! HWTRIGEN - Hardware Triggering Enable for this channel.
 *  0b0..Disabled. Hardware triggering is not used.
 *  0b1..Enabled. Use hardware triggering.
 */
#define DMA_CHANNEL_CFG_HWTRIGEN(x)              (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_HWTRIGEN_SHIFT)) & DMA_CHANNEL_CFG_HWTRIGEN_MASK)

#define DMA_CHANNEL_CFG_TRIGPOL_MASK             (0x10U)
#define DMA_CHANNEL_CFG_TRIGPOL_SHIFT            (4U)
/*! TRIGPOL - Trigger Polarity. Selects the polarity of a hardware trigger for this channel.
 *  0b0..Active low - falling edge. Hardware trigger is active low or falling edge triggered, based on TRIGTYPE.
 *  0b1..Active high - rising edge. Hardware trigger is active high or rising edge triggered, based on TRIGTYPE.
 */
#define DMA_CHANNEL_CFG_TRIGPOL(x)               (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_TRIGPOL_SHIFT)) & DMA_CHANNEL_CFG_TRIGPOL_MASK)

#define DMA_CHANNEL_CFG_TRIGTYPE_MASK            (0x20U)
#define DMA_CHANNEL_CFG_TRIGTYPE_SHIFT           (5U)
/*! TRIGTYPE - Trigger Type. Selects hardware trigger as edge triggered or level triggered.
 *  0b0..Edge. Hardware trigger is edge triggered. Transfers will be initiated and completed, as specified for a single trigger.
 *  0b1..Level. Hardware trigger is level triggered. Note that when level triggering without burst (BURSTPOWER =
 *       0) is selected, only hardware triggers should be used on that channel. Transfers continue as long as the
 *       trigger level is asserted. Once the trigger is de-asserted, the transfer will be paused until the trigger
 *       is, again, asserted. However, the transfer will not be paused until any remaining transfers within the
 *       current BURSTPOWER length are completed.
 */
#define DMA_CHANNEL_CFG_TRIGTYPE(x)              (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_TRIGTYPE_SHIFT)) & DMA_CHANNEL_CFG_TRIGTYPE_MASK)

#define DMA_CHANNEL_CFG_TRIGBURST_MASK           (0x40U)
#define DMA_CHANNEL_CFG_TRIGBURST_SHIFT          (6U)
/*! TRIGBURST - Trigger Burst. Selects whether hardware triggers cause a single or burst transfer.
 *  0b0..Single transfer. Hardware trigger causes a single transfer.
 *  0b1..Burst transfer. When the trigger for this channel is set to edge triggered, a hardware trigger causes a
 *       burst transfer, as defined by BURSTPOWER. When the trigger for this channel is set to level triggered, a
 *       hardware trigger causes transfers to continue as long as the trigger is asserted, unless the transfer is
 *       complete.
 */
#define DMA_CHANNEL_CFG_TRIGBURST(x)             (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_TRIGBURST_SHIFT)) & DMA_CHANNEL_CFG_TRIGBURST_MASK)

#define DMA_CHANNEL_CFG_BURSTPOWER_MASK          (0xF00U)
#define DMA_CHANNEL_CFG_BURSTPOWER_SHIFT         (8U)
/*! BURSTPOWER - Burst Power is used in two ways. It always selects the address wrap size when
 *    SRCBURSTWRAP and/or DSTBURSTWRAP modes are selected (see descriptions elsewhere in this register).
 *    When the TRIGBURST field elsewhere in this register = 1, Burst Power selects how many
 *    transfers are performed for each DMA trigger. This can be used, for example, with peripherals that
 *    contain a FIFO that can initiate a DMA operation when the FIFO reaches a certain level. 0000:
 *    Burst size = 1 (20). 0001: Burst size = 2 (21). 0010: Burst size = 4 (22). 1010: Burst size =
 *    1024 (210). This corresponds to the maximum supported transfer count. others: not supported. The
 *    total transfer length as defined in the XFERCOUNT bits in the XFERCFG register must be an even
 *    multiple of the burst size.
 */
#define DMA_CHANNEL_CFG_BURSTPOWER(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_BURSTPOWER_SHIFT)) & DMA_CHANNEL_CFG_BURSTPOWER_MASK)

#define DMA_CHANNEL_CFG_SRCBURSTWRAP_MASK        (0x4000U)
#define DMA_CHANNEL_CFG_SRCBURSTWRAP_SHIFT       (14U)
/*! SRCBURSTWRAP - Source Burst Wrap. When enabled, the source data address for the DMA is
 *    'wrapped', meaning that the source address range for each burst will be the same. As an example, this
 *    could be used to read several sequential registers from a peripheral for each DMA burst,
 *    reading the same registers again for each burst.
 *  0b0..Disabled. Source burst wrapping is not enabled for this DMA channel.
 *  0b1..Enabled. Source burst wrapping is enabled for this DMA channel.
 */
#define DMA_CHANNEL_CFG_SRCBURSTWRAP(x)          (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_SRCBURSTWRAP_SHIFT)) & DMA_CHANNEL_CFG_SRCBURSTWRAP_MASK)

#define DMA_CHANNEL_CFG_DSTBURSTWRAP_MASK        (0x8000U)
#define DMA_CHANNEL_CFG_DSTBURSTWRAP_SHIFT       (15U)
/*! DSTBURSTWRAP - Destination Burst Wrap. When enabled, the destination data address for the DMA is
 *    'wrapped', meaning that the destination address range for each burst will be the same. As an
 *    example, this could be used to write several sequential registers to a peripheral for each DMA
 *    burst, writing the same registers again for each burst.
 *  0b0..Disabled. Destination burst wrapping is not enabled for this DMA channel.
 *  0b1..Enabled. Destination burst wrapping is enabled for this DMA channel.
 */
#define DMA_CHANNEL_CFG_DSTBURSTWRAP(x)          (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_DSTBURSTWRAP_SHIFT)) & DMA_CHANNEL_CFG_DSTBURSTWRAP_MASK)

#define DMA_CHANNEL_CFG_CHPRIORITY_MASK          (0x70000U)
#define DMA_CHANNEL_CFG_CHPRIORITY_SHIFT         (16U)
/*! CHPRIORITY - Priority of this channel when multiple DMA requests are pending. Eight priority
 *    levels are supported: 0x0 = highest priority. 0x7 = lowest priority.
 */
#define DMA_CHANNEL_CFG_CHPRIORITY(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_CHPRIORITY_SHIFT)) & DMA_CHANNEL_CFG_CHPRIORITY_MASK)
/*! @} */

/* The count of DMA_CHANNEL_CFG */
#define DMA_CHANNEL_CFG_COUNT                    (23U)

/*! @name CHANNEL_CTLSTAT - Control and status register for DMA channel . */
/*! @{ */

#define DMA_CHANNEL_CTLSTAT_VALIDPENDING_MASK    (0x1U)
#define DMA_CHANNEL_CTLSTAT_VALIDPENDING_SHIFT   (0U)
/*! VALIDPENDING - Valid pending flag for this channel. This bit is set when a 1 is written to the
 *    corresponding bit in the related SETVALID register when CFGVALID = 1 for the same channel.
 *  0b0..No effect. No effect on DMA operation.
 *  0b1..Valid pending.
 */
#define DMA_CHANNEL_CTLSTAT_VALIDPENDING(x)      (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CTLSTAT_VALIDPENDING_SHIFT)) & DMA_CHANNEL_CTLSTAT_VALIDPENDING_MASK)

#define DMA_CHANNEL_CTLSTAT_TRIG_MASK            (0x4U)
#define DMA_CHANNEL_CTLSTAT_TRIG_SHIFT           (2U)
/*! TRIG - Trigger flag. Indicates that the trigger for this channel is currently set. This bit is
 *    cleared at the end of an entire transfer or upon reload when CLRTRIG = 1.
 *  0b0..Not triggered. The trigger for this DMA channel is not set. DMA operations will not be carried out.
 *  0b1..Triggered. The trigger for this DMA channel is set. DMA operations will be carried out.
 */
#define DMA_CHANNEL_CTLSTAT_TRIG(x)              (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CTLSTAT_TRIG_SHIFT)) & DMA_CHANNEL_CTLSTAT_TRIG_MASK)
/*! @} */

/* The count of DMA_CHANNEL_CTLSTAT */
#define DMA_CHANNEL_CTLSTAT_COUNT                (23U)

/*! @name CHANNEL_XFERCFG - Transfer configuration register for DMA channel . */
/*! @{ */

#define DMA_CHANNEL_XFERCFG_CFGVALID_MASK        (0x1U)
#define DMA_CHANNEL_XFERCFG_CFGVALID_SHIFT       (0U)
/*! CFGVALID - Configuration Valid flag. This bit indicates whether the current channel descriptor
 *    is valid and can potentially be acted upon, if all other activation criteria are fulfilled.
 *  0b0..Not valid. The channel descriptor is not considered valid until validated by an associated SETVALID0 setting.
 *  0b1..Valid. The current channel descriptor is considered valid.
 */
#define DMA_CHANNEL_XFERCFG_CFGVALID(x)          (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_CFGVALID_SHIFT)) & DMA_CHANNEL_XFERCFG_CFGVALID_MASK)

#define DMA_CHANNEL_XFERCFG_RELOAD_MASK          (0x2U)
#define DMA_CHANNEL_XFERCFG_RELOAD_SHIFT         (1U)
/*! RELOAD - Indicates whether the channel's control structure will be reloaded when the current
 *    descriptor is exhausted. Reloading allows ping-pong and linked transfers.
 *  0b0..Disabled. Do not reload the channels' control structure when the current descriptor is exhausted.
 *  0b1..Enabled. Reload the channels' control structure when the current descriptor is exhausted.
 */
#define DMA_CHANNEL_XFERCFG_RELOAD(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_RELOAD_SHIFT)) & DMA_CHANNEL_XFERCFG_RELOAD_MASK)

#define DMA_CHANNEL_XFERCFG_SWTRIG_MASK          (0x4U)
#define DMA_CHANNEL_XFERCFG_SWTRIG_SHIFT         (2U)
/*! SWTRIG - Software Trigger.
 *  0b0..Not set. When written by software, the trigger for this channel is not set. A new trigger, as defined by
 *       the HWTRIGEN, TRIGPOL, and TRIGTYPE will be needed to start the channel.
 *  0b1..Set. When written by software, the trigger for this channel is set immediately. This feature should not
 *       be used with level triggering when TRIGBURST = 0.
 */
#define DMA_CHANNEL_XFERCFG_SWTRIG(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_SWTRIG_SHIFT)) & DMA_CHANNEL_XFERCFG_SWTRIG_MASK)

#define DMA_CHANNEL_XFERCFG_CLRTRIG_MASK         (0x8U)
#define DMA_CHANNEL_XFERCFG_CLRTRIG_SHIFT        (3U)
/*! CLRTRIG - Clear Trigger.
 *  0b0..Not cleared. The trigger is not cleared when this descriptor is exhausted. If there is a reload, the next descriptor will be started.
 *  0b1..Cleared. The trigger is cleared when this descriptor is exhausted
 */
#define DMA_CHANNEL_XFERCFG_CLRTRIG(x)           (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_CLRTRIG_SHIFT)) & DMA_CHANNEL_XFERCFG_CLRTRIG_MASK)

#define DMA_CHANNEL_XFERCFG_SETINTA_MASK         (0x10U)
#define DMA_CHANNEL_XFERCFG_SETINTA_SHIFT        (4U)
/*! SETINTA - Set Interrupt flag A for this channel. There is no hardware distinction between
 *    interrupt A and B. They can be used by software to assist with more complex descriptor usage. By
 *    convention, interrupt A may be used when only one interrupt flag is needed.
 *  0b0..No effect.
 *  0b1..Set. The INTA flag for this channel will be set when the current descriptor is exhausted.
 */
#define DMA_CHANNEL_XFERCFG_SETINTA(x)           (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_SETINTA_SHIFT)) & DMA_CHANNEL_XFERCFG_SETINTA_MASK)

#define DMA_CHANNEL_XFERCFG_SETINTB_MASK         (0x20U)
#define DMA_CHANNEL_XFERCFG_SETINTB_SHIFT        (5U)
/*! SETINTB - Set Interrupt flag B for this channel. There is no hardware distinction between
 *    interrupt A and B. They can be used by software to assist with more complex descriptor usage. By
 *    convention, interrupt A may be used when only one interrupt flag is needed.
 *  0b0..No effect.
 *  0b1..Set. The INTB flag for this channel will be set when the current descriptor is exhausted.
 */
#define DMA_CHANNEL_XFERCFG_SETINTB(x)           (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_SETINTB_SHIFT)) & DMA_CHANNEL_XFERCFG_SETINTB_MASK)

#define DMA_CHANNEL_XFERCFG_WIDTH_MASK           (0x300U)
#define DMA_CHANNEL_XFERCFG_WIDTH_SHIFT          (8U)
/*! WIDTH - Transfer width used for this DMA channel.
 *  0b00..8-bit. 8-bit transfers are performed (8-bit source reads and destination writes).
 *  0b01..16-bit. 6-bit transfers are performed (16-bit source reads and destination writes).
 *  0b10..32-bit. 32-bit transfers are performed (32-bit source reads and destination writes).
 *  0b11..Reserved. Reserved setting, do not use.
 */
#define DMA_CHANNEL_XFERCFG_WIDTH(x)             (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_WIDTH_SHIFT)) & DMA_CHANNEL_XFERCFG_WIDTH_MASK)

#define DMA_CHANNEL_XFERCFG_SRCINC_MASK          (0x3000U)
#define DMA_CHANNEL_XFERCFG_SRCINC_SHIFT         (12U)
/*! SRCINC - Determines whether the source address is incremented for each DMA transfer.
 *  0b00..No increment. The source address is not incremented for each transfer. This is the usual case when the source is a peripheral device.
 *  0b01..1 x width. The source address is incremented by the amount specified by Width for each transfer. This is
 *        the usual case when the source is memory.
 *  0b10..2 x width. The source address is incremented by 2 times the amount specified by Width for each transfer.
 *  0b11..4 x width. The source address is incremented by 4 times the amount specified by Width for each transfer.
 */
#define DMA_CHANNEL_XFERCFG_SRCINC(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_SRCINC_SHIFT)) & DMA_CHANNEL_XFERCFG_SRCINC_MASK)

#define DMA_CHANNEL_XFERCFG_DSTINC_MASK          (0xC000U)
#define DMA_CHANNEL_XFERCFG_DSTINC_SHIFT         (14U)
/*! DSTINC - Determines whether the destination address is incremented for each DMA transfer.
 *  0b00..No increment. The destination address is not incremented for each transfer. This is the usual case when
 *        the destination is a peripheral device.
 *  0b01..1 x width. The destination address is incremented by the amount specified by Width for each transfer.
 *        This is the usual case when the destination is memory.
 *  0b10..2 x width. The destination address is incremented by 2 times the amount specified by Width for each transfer.
 *  0b11..4 x width. The destination address is incremented by 4 times the amount specified by Width for each transfer.
 */
#define DMA_CHANNEL_XFERCFG_DSTINC(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_DSTINC_SHIFT)) & DMA_CHANNEL_XFERCFG_DSTINC_MASK)

#define DMA_CHANNEL_XFERCFG_XFERCOUNT_MASK       (0x3FF0000U)
#define DMA_CHANNEL_XFERCFG_XFERCOUNT_SHIFT      (16U)
/*! XFERCOUNT - Total number of transfers to be performed, minus 1 encoded. The number of bytes
 *    transferred is: (XFERCOUNT + 1) x data width (as defined by the WIDTH field). The DMA controller
 *    uses this bit field during transfer to count down. Hence, it cannot be used by software to read
 *    back the size of the transfer, for instance, in an interrupt handler. 0x0 = a total of 1
 *    transfer will be performed. 0x1 = a total of 2 transfers will be performed. 0x3FF = a total of
 *    1,024 transfers will be performed.
 */
#define DMA_CHANNEL_XFERCFG_XFERCOUNT(x)         (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_XFERCOUNT_SHIFT)) & DMA_CHANNEL_XFERCFG_XFERCOUNT_MASK)
/*! @} */

/* The count of DMA_CHANNEL_XFERCFG */
#define DMA_CHANNEL_XFERCFG_COUNT                (23U)


/*!
 * @}
 */ /* end of group DMA_Register_Masks */


/*!
 * @}
 */ /* end of group DMA_Peripheral_Access_Layer */


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


#endif  /* DMA_H_ */


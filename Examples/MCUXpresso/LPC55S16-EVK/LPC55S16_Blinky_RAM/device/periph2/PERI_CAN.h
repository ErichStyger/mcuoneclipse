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
**         CMSIS Peripheral Access Layer for CAN
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
 * @file CAN.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for CAN
 *
 * CMSIS Peripheral Access Layer for CAN
 */

#if !defined(CAN_H_)
#define CAN_H_                                   /**< Symbol preventing repeated inclusion */

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
   -- CAN Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAN_Peripheral_Access_Layer CAN Peripheral Access Layer
 * @{
 */

/** CAN - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[12];
  __IO uint32_t DBTP;                              /**< Data Bit Timing Prescaler Register, offset: 0xC */
  __IO uint32_t TEST;                              /**< Test Register, offset: 0x10 */
       uint8_t RESERVED_1[4];
  __IO uint32_t CCCR;                              /**< CC Control Register, offset: 0x18 */
  __IO uint32_t NBTP;                              /**< Nominal Bit Timing and Prescaler Register, offset: 0x1C */
  __IO uint32_t TSCC;                              /**< Timestamp Counter Configuration, offset: 0x20 */
  __I  uint32_t TSCV;                              /**< Timestamp Counter Value, offset: 0x24 */
  __IO uint32_t TOCC;                              /**< Timeout Counter Configuration, offset: 0x28 */
  __I  uint32_t TOCV;                              /**< Timeout Counter Value, offset: 0x2C */
       uint8_t RESERVED_2[16];
  __I  uint32_t ECR;                               /**< Error Counter Register, offset: 0x40 */
  __I  uint32_t PSR;                               /**< Protocol Status Register, offset: 0x44 */
  __IO uint32_t TDCR;                              /**< Transmitter Delay Compensator Register, offset: 0x48 */
       uint8_t RESERVED_3[4];
  __IO uint32_t IR;                                /**< Interrupt Register, offset: 0x50 */
  __IO uint32_t IE;                                /**< Interrupt Enable, offset: 0x54 */
  __IO uint32_t ILS;                               /**< Interrupt Line Select, offset: 0x58 */
  __IO uint32_t ILE;                               /**< Interrupt Line Enable, offset: 0x5C */
       uint8_t RESERVED_4[32];
  __IO uint32_t GFC;                               /**< Global Filter Configuration, offset: 0x80 */
  __IO uint32_t SIDFC;                             /**< Standard ID Filter Configuration, offset: 0x84 */
  __IO uint32_t XIDFC;                             /**< Extended ID Filter Configuration, offset: 0x88 */
       uint8_t RESERVED_5[4];
  __IO uint32_t XIDAM;                             /**< Extended ID AND Mask, offset: 0x90 */
  __I  uint32_t HPMS;                              /**< High Priority Message Status, offset: 0x94 */
  __IO uint32_t NDAT1;                             /**< New Data 1, offset: 0x98 */
  __IO uint32_t NDAT2;                             /**< New Data 2, offset: 0x9C */
  __IO uint32_t RXF0C;                             /**< Rx FIFO 0 Configuration, offset: 0xA0 */
  __I  uint32_t RXF0S;                             /**< Rx FIFO 0 Status, offset: 0xA4 */
  __IO uint32_t RXF0A;                             /**< Rx FIFO 0 Acknowledge, offset: 0xA8 */
  __IO uint32_t RXBC;                              /**< Rx Buffer Configuration, offset: 0xAC */
  __IO uint32_t RXF1C;                             /**< Rx FIFO 1 Configuration, offset: 0xB0 */
  __I  uint32_t RXF1S;                             /**< Rx FIFO 1 Status, offset: 0xB4 */
  __IO uint32_t RXF1A;                             /**< Rx FIFO 1 Acknowledge, offset: 0xB8 */
  __IO uint32_t RXESC;                             /**< Rx Buffer and FIFO Element Size Configuration, offset: 0xBC */
  __IO uint32_t TXBC;                              /**< Tx Buffer Configuration, offset: 0xC0 */
  __IO uint32_t TXFQS;                             /**< Tx FIFO/Queue Status, offset: 0xC4 */
  __IO uint32_t TXESC;                             /**< Tx Buffer Element Size Configuration, offset: 0xC8 */
  __I  uint32_t TXBRP;                             /**< Tx Buffer Request Pending, offset: 0xCC */
  __IO uint32_t TXBAR;                             /**< Tx Buffer Add Request, offset: 0xD0 */
  __IO uint32_t TXBCR;                             /**< Tx Buffer Cancellation Request, offset: 0xD4 */
  __I  uint32_t TXBTO;                             /**< Tx Buffer Transmission Occurred, offset: 0xD8 */
  __I  uint32_t TXBCF;                             /**< Tx Buffer Cancellation Finished, offset: 0xDC */
  __IO uint32_t TXBTIE;                            /**< Tx Buffer Transmission Interrupt Enable, offset: 0xE0 */
  __IO uint32_t TXBCIE;                            /**< Tx Buffer Cancellation Finished Interrupt Enable, offset: 0xE4 */
       uint8_t RESERVED_6[8];
  __IO uint32_t TXEFC;                             /**< Tx Event FIFO Configuration, offset: 0xF0 */
  __I  uint32_t TXEFS;                             /**< Tx Event FIFO Status, offset: 0xF4 */
  __IO uint32_t TXEFA;                             /**< Tx Event FIFO Acknowledge, offset: 0xF8 */
       uint8_t RESERVED_7[260];
  __IO uint32_t MRBA;                              /**< CAN Message RAM Base Address, offset: 0x200 */
       uint8_t RESERVED_8[508];
  __IO uint32_t ETSCC;                             /**< External Timestamp Counter Configuration, offset: 0x400 */
       uint8_t RESERVED_9[508];
  __IO uint32_t ETSCV;                             /**< External Timestamp Counter Value, offset: 0x600 */
} CAN_Type;

/* ----------------------------------------------------------------------------
   -- CAN Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAN_Register_Masks CAN Register Masks
 * @{
 */

/*! @name DBTP - Data Bit Timing Prescaler Register */
/*! @{ */

#define CAN_DBTP_DSJW_MASK                       (0xFU)
#define CAN_DBTP_DSJW_SHIFT                      (0U)
/*! DSJW - Data (re)synchronization jump width. */
#define CAN_DBTP_DSJW(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_DBTP_DSJW_SHIFT)) & CAN_DBTP_DSJW_MASK)

#define CAN_DBTP_DTSEG2_MASK                     (0xF0U)
#define CAN_DBTP_DTSEG2_SHIFT                    (4U)
/*! DTSEG2 - Data time segment after sample point. */
#define CAN_DBTP_DTSEG2(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_DBTP_DTSEG2_SHIFT)) & CAN_DBTP_DTSEG2_MASK)

#define CAN_DBTP_DTSEG1_MASK                     (0x1F00U)
#define CAN_DBTP_DTSEG1_SHIFT                    (8U)
/*! DTSEG1 - Data time segment before sample point. */
#define CAN_DBTP_DTSEG1(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_DBTP_DTSEG1_SHIFT)) & CAN_DBTP_DTSEG1_MASK)

#define CAN_DBTP_DBRP_MASK                       (0x1F0000U)
#define CAN_DBTP_DBRP_SHIFT                      (16U)
/*! DBRP - Data bit rate prescaler. */
#define CAN_DBTP_DBRP(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_DBTP_DBRP_SHIFT)) & CAN_DBTP_DBRP_MASK)

#define CAN_DBTP_TDC_MASK                        (0x800000U)
#define CAN_DBTP_TDC_SHIFT                       (23U)
/*! TDC - Transmitter delay compensation. */
#define CAN_DBTP_TDC(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_DBTP_TDC_SHIFT)) & CAN_DBTP_TDC_MASK)
/*! @} */

/*! @name TEST - Test Register */
/*! @{ */

#define CAN_TEST_LBCK_MASK                       (0x10U)
#define CAN_TEST_LBCK_SHIFT                      (4U)
/*! LBCK - Loop back mode. */
#define CAN_TEST_LBCK(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TEST_LBCK_SHIFT)) & CAN_TEST_LBCK_MASK)

#define CAN_TEST_TX_MASK                         (0x60U)
#define CAN_TEST_TX_SHIFT                        (5U)
/*! TX - Control of transmit pin. */
#define CAN_TEST_TX(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_TEST_TX_SHIFT)) & CAN_TEST_TX_MASK)

#define CAN_TEST_RX_MASK                         (0x80U)
#define CAN_TEST_RX_SHIFT                        (7U)
/*! RX - Monitors the actual value of the CAN_RXD. */
#define CAN_TEST_RX(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_TEST_RX_SHIFT)) & CAN_TEST_RX_MASK)
/*! @} */

/*! @name CCCR - CC Control Register */
/*! @{ */

#define CAN_CCCR_INIT_MASK                       (0x1U)
#define CAN_CCCR_INIT_SHIFT                      (0U)
/*! INIT - Initialization. */
#define CAN_CCCR_INIT(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_INIT_SHIFT)) & CAN_CCCR_INIT_MASK)

#define CAN_CCCR_CCE_MASK                        (0x2U)
#define CAN_CCCR_CCE_SHIFT                       (1U)
/*! CCE - Configuration change enable. */
#define CAN_CCCR_CCE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_CCE_SHIFT)) & CAN_CCCR_CCE_MASK)

#define CAN_CCCR_ASM_MASK                        (0x4U)
#define CAN_CCCR_ASM_SHIFT                       (2U)
/*! ASM - Restricted operational mode. */
#define CAN_CCCR_ASM(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_ASM_SHIFT)) & CAN_CCCR_ASM_MASK)

#define CAN_CCCR_CSA_MASK                        (0x8U)
#define CAN_CCCR_CSA_SHIFT                       (3U)
/*! CSA - Clock Stop Acknowledge. */
#define CAN_CCCR_CSA(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_CSA_SHIFT)) & CAN_CCCR_CSA_MASK)

#define CAN_CCCR_CSR_MASK                        (0x10U)
#define CAN_CCCR_CSR_SHIFT                       (4U)
/*! CSR - Clock Stop Request. */
#define CAN_CCCR_CSR(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_CSR_SHIFT)) & CAN_CCCR_CSR_MASK)

#define CAN_CCCR_MON_MASK                        (0x20U)
#define CAN_CCCR_MON_SHIFT                       (5U)
/*! MON - Bus monitoring mode. */
#define CAN_CCCR_MON(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_MON_SHIFT)) & CAN_CCCR_MON_MASK)

#define CAN_CCCR_DAR_MASK                        (0x40U)
#define CAN_CCCR_DAR_SHIFT                       (6U)
/*! DAR - Disable automatic retransmission. */
#define CAN_CCCR_DAR(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_DAR_SHIFT)) & CAN_CCCR_DAR_MASK)

#define CAN_CCCR_TEST_MASK                       (0x80U)
#define CAN_CCCR_TEST_SHIFT                      (7U)
/*! TEST - Test mode enable. */
#define CAN_CCCR_TEST(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_TEST_SHIFT)) & CAN_CCCR_TEST_MASK)

#define CAN_CCCR_FDOE_MASK                       (0x100U)
#define CAN_CCCR_FDOE_SHIFT                      (8U)
/*! FDOE - CAN FD operation enable. */
#define CAN_CCCR_FDOE(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_FDOE_SHIFT)) & CAN_CCCR_FDOE_MASK)

#define CAN_CCCR_BRSE_MASK                       (0x200U)
#define CAN_CCCR_BRSE_SHIFT                      (9U)
/*! BRSE - When CAN FD operation is disabled, this bit is not evaluated. */
#define CAN_CCCR_BRSE(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_BRSE_SHIFT)) & CAN_CCCR_BRSE_MASK)

#define CAN_CCCR_PXHD_MASK                       (0x1000U)
#define CAN_CCCR_PXHD_SHIFT                      (12U)
/*! PXHD - Protocol exception handling disable. */
#define CAN_CCCR_PXHD(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_PXHD_SHIFT)) & CAN_CCCR_PXHD_MASK)

#define CAN_CCCR_EFBI_MASK                       (0x2000U)
#define CAN_CCCR_EFBI_SHIFT                      (13U)
/*! EFBI - Edge filtering during bus integration. */
#define CAN_CCCR_EFBI(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_EFBI_SHIFT)) & CAN_CCCR_EFBI_MASK)

#define CAN_CCCR_TXP_MASK                        (0x4000U)
#define CAN_CCCR_TXP_SHIFT                       (14U)
/*! TXP - Transmit pause. */
#define CAN_CCCR_TXP(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_TXP_SHIFT)) & CAN_CCCR_TXP_MASK)

#define CAN_CCCR_NISO_MASK                       (0x8000U)
#define CAN_CCCR_NISO_SHIFT                      (15U)
/*! NISO - Non ISO operation. */
#define CAN_CCCR_NISO(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_NISO_SHIFT)) & CAN_CCCR_NISO_MASK)
/*! @} */

/*! @name NBTP - Nominal Bit Timing and Prescaler Register */
/*! @{ */

#define CAN_NBTP_NTSEG2_MASK                     (0x7FU)
#define CAN_NBTP_NTSEG2_SHIFT                    (0U)
/*! NTSEG2 - Nominal time segment after sample point. */
#define CAN_NBTP_NTSEG2(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_NBTP_NTSEG2_SHIFT)) & CAN_NBTP_NTSEG2_MASK)

#define CAN_NBTP_NTSEG1_MASK                     (0xFF00U)
#define CAN_NBTP_NTSEG1_SHIFT                    (8U)
/*! NTSEG1 - Nominal time segment before sample point. */
#define CAN_NBTP_NTSEG1(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_NBTP_NTSEG1_SHIFT)) & CAN_NBTP_NTSEG1_MASK)

#define CAN_NBTP_NBRP_MASK                       (0x1FF0000U)
#define CAN_NBTP_NBRP_SHIFT                      (16U)
/*! NBRP - Nominal bit rate prescaler. */
#define CAN_NBTP_NBRP(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_NBTP_NBRP_SHIFT)) & CAN_NBTP_NBRP_MASK)

#define CAN_NBTP_NSJW_MASK                       (0xFE000000U)
#define CAN_NBTP_NSJW_SHIFT                      (25U)
/*! NSJW - Nominal (re)synchronization jump width. */
#define CAN_NBTP_NSJW(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_NBTP_NSJW_SHIFT)) & CAN_NBTP_NSJW_MASK)
/*! @} */

/*! @name TSCC - Timestamp Counter Configuration */
/*! @{ */

#define CAN_TSCC_TSS_MASK                        (0x3U)
#define CAN_TSCC_TSS_SHIFT                       (0U)
/*! TSS - Timestamp select. */
#define CAN_TSCC_TSS(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TSCC_TSS_SHIFT)) & CAN_TSCC_TSS_MASK)

#define CAN_TSCC_TCP_MASK                        (0xF0000U)
#define CAN_TSCC_TCP_SHIFT                       (16U)
/*! TCP - Timestamp counter prescaler Configures the timestamp and timeout counters time unit in multiple of CAN bit times. */
#define CAN_TSCC_TCP(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TSCC_TCP_SHIFT)) & CAN_TSCC_TCP_MASK)
/*! @} */

/*! @name TSCV - Timestamp Counter Value */
/*! @{ */

#define CAN_TSCV_TSC_MASK                        (0xFFFFU)
#define CAN_TSCV_TSC_SHIFT                       (0U)
/*! TSC - Timestamp counter. */
#define CAN_TSCV_TSC(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TSCV_TSC_SHIFT)) & CAN_TSCV_TSC_MASK)
/*! @} */

/*! @name TOCC - Timeout Counter Configuration */
/*! @{ */

#define CAN_TOCC_ETOC_MASK                       (0x1U)
#define CAN_TOCC_ETOC_SHIFT                      (0U)
/*! ETOC - Enable timeout counter. */
#define CAN_TOCC_ETOC(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TOCC_ETOC_SHIFT)) & CAN_TOCC_ETOC_MASK)

#define CAN_TOCC_TOS_MASK                        (0x6U)
#define CAN_TOCC_TOS_SHIFT                       (1U)
/*! TOS - Timeout select. */
#define CAN_TOCC_TOS(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TOCC_TOS_SHIFT)) & CAN_TOCC_TOS_MASK)

#define CAN_TOCC_TOP_MASK                        (0xFFFF0000U)
#define CAN_TOCC_TOP_SHIFT                       (16U)
/*! TOP - Timeout period. */
#define CAN_TOCC_TOP(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TOCC_TOP_SHIFT)) & CAN_TOCC_TOP_MASK)
/*! @} */

/*! @name TOCV - Timeout Counter Value */
/*! @{ */

#define CAN_TOCV_TOC_MASK                        (0xFFFFU)
#define CAN_TOCV_TOC_SHIFT                       (0U)
/*! TOC - Timeout counter. */
#define CAN_TOCV_TOC(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TOCV_TOC_SHIFT)) & CAN_TOCV_TOC_MASK)
/*! @} */

/*! @name ECR - Error Counter Register */
/*! @{ */

#define CAN_ECR_TEC_MASK                         (0xFFU)
#define CAN_ECR_TEC_SHIFT                        (0U)
/*! TEC - Transmit error counter. */
#define CAN_ECR_TEC(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ECR_TEC_SHIFT)) & CAN_ECR_TEC_MASK)

#define CAN_ECR_REC_MASK                         (0x7F00U)
#define CAN_ECR_REC_SHIFT                        (8U)
/*! REC - Receive error counter. */
#define CAN_ECR_REC(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ECR_REC_SHIFT)) & CAN_ECR_REC_MASK)

#define CAN_ECR_RP_MASK                          (0x8000U)
#define CAN_ECR_RP_SHIFT                         (15U)
/*! RP - Receive error passive. */
#define CAN_ECR_RP(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_ECR_RP_SHIFT)) & CAN_ECR_RP_MASK)

#define CAN_ECR_CEL_MASK                         (0xFF0000U)
#define CAN_ECR_CEL_SHIFT                        (16U)
/*! CEL - CAN error logging. */
#define CAN_ECR_CEL(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ECR_CEL_SHIFT)) & CAN_ECR_CEL_MASK)
/*! @} */

/*! @name PSR - Protocol Status Register */
/*! @{ */

#define CAN_PSR_LEC_MASK                         (0x7U)
#define CAN_PSR_LEC_SHIFT                        (0U)
/*! LEC - Last error code. */
#define CAN_PSR_LEC(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_PSR_LEC_SHIFT)) & CAN_PSR_LEC_MASK)

#define CAN_PSR_ACT_MASK                         (0x18U)
#define CAN_PSR_ACT_SHIFT                        (3U)
/*! ACT - Activity. */
#define CAN_PSR_ACT(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_PSR_ACT_SHIFT)) & CAN_PSR_ACT_MASK)

#define CAN_PSR_EP_MASK                          (0x20U)
#define CAN_PSR_EP_SHIFT                         (5U)
/*! EP - Error Passive. */
#define CAN_PSR_EP(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_PSR_EP_SHIFT)) & CAN_PSR_EP_MASK)

#define CAN_PSR_EW_MASK                          (0x40U)
#define CAN_PSR_EW_SHIFT                         (6U)
/*! EW - Warning status. */
#define CAN_PSR_EW(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_PSR_EW_SHIFT)) & CAN_PSR_EW_MASK)

#define CAN_PSR_BO_MASK                          (0x80U)
#define CAN_PSR_BO_SHIFT                         (7U)
/*! BO - Bus Off Status. */
#define CAN_PSR_BO(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_PSR_BO_SHIFT)) & CAN_PSR_BO_MASK)

#define CAN_PSR_DLEC_MASK                        (0x700U)
#define CAN_PSR_DLEC_SHIFT                       (8U)
/*! DLEC - Data phase last error code. */
#define CAN_PSR_DLEC(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_PSR_DLEC_SHIFT)) & CAN_PSR_DLEC_MASK)

#define CAN_PSR_RESI_MASK                        (0x800U)
#define CAN_PSR_RESI_SHIFT                       (11U)
/*! RESI - ESI flag of the last received CAN FD message. */
#define CAN_PSR_RESI(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_PSR_RESI_SHIFT)) & CAN_PSR_RESI_MASK)

#define CAN_PSR_RBRS_MASK                        (0x1000U)
#define CAN_PSR_RBRS_SHIFT                       (12U)
/*! RBRS - BRS flag of last received CAN FD message. */
#define CAN_PSR_RBRS(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_PSR_RBRS_SHIFT)) & CAN_PSR_RBRS_MASK)

#define CAN_PSR_RFDF_MASK                        (0x2000U)
#define CAN_PSR_RFDF_SHIFT                       (13U)
/*! RFDF - Received a CAN FD message. */
#define CAN_PSR_RFDF(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_PSR_RFDF_SHIFT)) & CAN_PSR_RFDF_MASK)

#define CAN_PSR_PXE_MASK                         (0x4000U)
#define CAN_PSR_PXE_SHIFT                        (14U)
/*! PXE - Protocol exception event. */
#define CAN_PSR_PXE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_PSR_PXE_SHIFT)) & CAN_PSR_PXE_MASK)

#define CAN_PSR_TDCV_MASK                        (0x7F0000U)
#define CAN_PSR_TDCV_SHIFT                       (16U)
/*! TDCV - Transmitter delay compensation value. */
#define CAN_PSR_TDCV(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_PSR_TDCV_SHIFT)) & CAN_PSR_TDCV_MASK)
/*! @} */

/*! @name TDCR - Transmitter Delay Compensator Register */
/*! @{ */

#define CAN_TDCR_TDCF_MASK                       (0x7FU)
#define CAN_TDCR_TDCF_SHIFT                      (0U)
/*! TDCF - Transmitter delay compensation filter window length. */
#define CAN_TDCR_TDCF(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TDCR_TDCF_SHIFT)) & CAN_TDCR_TDCF_MASK)

#define CAN_TDCR_TDCO_MASK                       (0x7F00U)
#define CAN_TDCR_TDCO_SHIFT                      (8U)
/*! TDCO - Transmitter delay compensation offset. */
#define CAN_TDCR_TDCO(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TDCR_TDCO_SHIFT)) & CAN_TDCR_TDCO_MASK)
/*! @} */

/*! @name IR - Interrupt Register */
/*! @{ */

#define CAN_IR_RF0N_MASK                         (0x1U)
#define CAN_IR_RF0N_SHIFT                        (0U)
/*! RF0N - Rx FIFO 0 new message. */
#define CAN_IR_RF0N(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_RF0N_SHIFT)) & CAN_IR_RF0N_MASK)

#define CAN_IR_RF0W_MASK                         (0x2U)
#define CAN_IR_RF0W_SHIFT                        (1U)
/*! RF0W - Rx FIFO 0 watermark reached. */
#define CAN_IR_RF0W(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_RF0W_SHIFT)) & CAN_IR_RF0W_MASK)

#define CAN_IR_RF0F_MASK                         (0x4U)
#define CAN_IR_RF0F_SHIFT                        (2U)
/*! RF0F - Rx FIFO 0 full. */
#define CAN_IR_RF0F(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_RF0F_SHIFT)) & CAN_IR_RF0F_MASK)

#define CAN_IR_RF0L_MASK                         (0x8U)
#define CAN_IR_RF0L_SHIFT                        (3U)
/*! RF0L - Rx FIFO 0 message lost. */
#define CAN_IR_RF0L(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_RF0L_SHIFT)) & CAN_IR_RF0L_MASK)

#define CAN_IR_RF1N_MASK                         (0x10U)
#define CAN_IR_RF1N_SHIFT                        (4U)
/*! RF1N - Rx FIFO 1 new message. */
#define CAN_IR_RF1N(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_RF1N_SHIFT)) & CAN_IR_RF1N_MASK)

#define CAN_IR_RF1W_MASK                         (0x20U)
#define CAN_IR_RF1W_SHIFT                        (5U)
/*! RF1W - Rx FIFO 1 watermark reached. */
#define CAN_IR_RF1W(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_RF1W_SHIFT)) & CAN_IR_RF1W_MASK)

#define CAN_IR_RF1F_MASK                         (0x40U)
#define CAN_IR_RF1F_SHIFT                        (6U)
/*! RF1F - Rx FIFO 1 full. */
#define CAN_IR_RF1F(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_RF1F_SHIFT)) & CAN_IR_RF1F_MASK)

#define CAN_IR_RF1L_MASK                         (0x80U)
#define CAN_IR_RF1L_SHIFT                        (7U)
/*! RF1L - Rx FIFO 1 message lost. */
#define CAN_IR_RF1L(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_RF1L_SHIFT)) & CAN_IR_RF1L_MASK)

#define CAN_IR_HPM_MASK                          (0x100U)
#define CAN_IR_HPM_SHIFT                         (8U)
/*! HPM - High priority message. */
#define CAN_IR_HPM(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_HPM_SHIFT)) & CAN_IR_HPM_MASK)

#define CAN_IR_TC_MASK                           (0x200U)
#define CAN_IR_TC_SHIFT                          (9U)
/*! TC - Transmission completed. */
#define CAN_IR_TC(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_IR_TC_SHIFT)) & CAN_IR_TC_MASK)

#define CAN_IR_TCF_MASK                          (0x400U)
#define CAN_IR_TCF_SHIFT                         (10U)
/*! TCF - Transmission cancellation finished. */
#define CAN_IR_TCF(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_TCF_SHIFT)) & CAN_IR_TCF_MASK)

#define CAN_IR_TFE_MASK                          (0x800U)
#define CAN_IR_TFE_SHIFT                         (11U)
/*! TFE - Tx FIFO empty. */
#define CAN_IR_TFE(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_TFE_SHIFT)) & CAN_IR_TFE_MASK)

#define CAN_IR_TEFN_MASK                         (0x1000U)
#define CAN_IR_TEFN_SHIFT                        (12U)
/*! TEFN - Tx event FIFO new entry. */
#define CAN_IR_TEFN(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_TEFN_SHIFT)) & CAN_IR_TEFN_MASK)

#define CAN_IR_TEFW_MASK                         (0x2000U)
#define CAN_IR_TEFW_SHIFT                        (13U)
/*! TEFW - Tx event FIFO watermark reached. */
#define CAN_IR_TEFW(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_TEFW_SHIFT)) & CAN_IR_TEFW_MASK)

#define CAN_IR_TEFF_MASK                         (0x4000U)
#define CAN_IR_TEFF_SHIFT                        (14U)
/*! TEFF - Tx event FIFO full. */
#define CAN_IR_TEFF(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_TEFF_SHIFT)) & CAN_IR_TEFF_MASK)

#define CAN_IR_TEFL_MASK                         (0x8000U)
#define CAN_IR_TEFL_SHIFT                        (15U)
/*! TEFL - Tx event FIFO element lost. */
#define CAN_IR_TEFL(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_TEFL_SHIFT)) & CAN_IR_TEFL_MASK)

#define CAN_IR_TSW_MASK                          (0x10000U)
#define CAN_IR_TSW_SHIFT                         (16U)
/*! TSW - Timestamp wraparound. */
#define CAN_IR_TSW(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_TSW_SHIFT)) & CAN_IR_TSW_MASK)

#define CAN_IR_MRAF_MASK                         (0x20000U)
#define CAN_IR_MRAF_SHIFT                        (17U)
/*! MRAF - Message RAM access failure. */
#define CAN_IR_MRAF(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_MRAF_SHIFT)) & CAN_IR_MRAF_MASK)

#define CAN_IR_TOO_MASK                          (0x40000U)
#define CAN_IR_TOO_SHIFT                         (18U)
/*! TOO - Timeout occurred. */
#define CAN_IR_TOO(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_TOO_SHIFT)) & CAN_IR_TOO_MASK)

#define CAN_IR_DRX_MASK                          (0x80000U)
#define CAN_IR_DRX_SHIFT                         (19U)
/*! DRX - Message stored in dedicated Rx buffer. */
#define CAN_IR_DRX(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_DRX_SHIFT)) & CAN_IR_DRX_MASK)

#define CAN_IR_BEC_MASK                          (0x100000U)
#define CAN_IR_BEC_SHIFT                         (20U)
/*! BEC - Bit error corrected. */
#define CAN_IR_BEC(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_BEC_SHIFT)) & CAN_IR_BEC_MASK)

#define CAN_IR_BEU_MASK                          (0x200000U)
#define CAN_IR_BEU_SHIFT                         (21U)
/*! BEU - Bit error uncorrected. */
#define CAN_IR_BEU(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_BEU_SHIFT)) & CAN_IR_BEU_MASK)

#define CAN_IR_ELO_MASK                          (0x400000U)
#define CAN_IR_ELO_SHIFT                         (22U)
/*! ELO - Error logging overflow. */
#define CAN_IR_ELO(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_ELO_SHIFT)) & CAN_IR_ELO_MASK)

#define CAN_IR_EP_MASK                           (0x800000U)
#define CAN_IR_EP_SHIFT                          (23U)
/*! EP - Error passive. */
#define CAN_IR_EP(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_IR_EP_SHIFT)) & CAN_IR_EP_MASK)

#define CAN_IR_EW_MASK                           (0x1000000U)
#define CAN_IR_EW_SHIFT                          (24U)
/*! EW - Warning status. */
#define CAN_IR_EW(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_IR_EW_SHIFT)) & CAN_IR_EW_MASK)

#define CAN_IR_BO_MASK                           (0x2000000U)
#define CAN_IR_BO_SHIFT                          (25U)
/*! BO - Bus_Off Status. */
#define CAN_IR_BO(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_IR_BO_SHIFT)) & CAN_IR_BO_MASK)

#define CAN_IR_WDI_MASK                          (0x4000000U)
#define CAN_IR_WDI_SHIFT                         (26U)
/*! WDI - Watchdog interrupt. */
#define CAN_IR_WDI(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_WDI_SHIFT)) & CAN_IR_WDI_MASK)

#define CAN_IR_PEA_MASK                          (0x8000000U)
#define CAN_IR_PEA_SHIFT                         (27U)
/*! PEA - Protocol error in arbitration phase. */
#define CAN_IR_PEA(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_PEA_SHIFT)) & CAN_IR_PEA_MASK)

#define CAN_IR_PED_MASK                          (0x10000000U)
#define CAN_IR_PED_SHIFT                         (28U)
/*! PED - Protocol error in data phase. */
#define CAN_IR_PED(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_PED_SHIFT)) & CAN_IR_PED_MASK)

#define CAN_IR_ARA_MASK                          (0x20000000U)
#define CAN_IR_ARA_SHIFT                         (29U)
/*! ARA - Access to reserved address. */
#define CAN_IR_ARA(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_ARA_SHIFT)) & CAN_IR_ARA_MASK)
/*! @} */

/*! @name IE - Interrupt Enable */
/*! @{ */

#define CAN_IE_RF0NE_MASK                        (0x1U)
#define CAN_IE_RF0NE_SHIFT                       (0U)
/*! RF0NE - Rx FIFO 0 new message interrupt enable. */
#define CAN_IE_RF0NE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_RF0NE_SHIFT)) & CAN_IE_RF0NE_MASK)

#define CAN_IE_RF0WE_MASK                        (0x2U)
#define CAN_IE_RF0WE_SHIFT                       (1U)
/*! RF0WE - Rx FIFO 0 watermark reached interrupt enable. */
#define CAN_IE_RF0WE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_RF0WE_SHIFT)) & CAN_IE_RF0WE_MASK)

#define CAN_IE_RF0FE_MASK                        (0x4U)
#define CAN_IE_RF0FE_SHIFT                       (2U)
/*! RF0FE - Rx FIFO 0 full interrupt enable. */
#define CAN_IE_RF0FE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_RF0FE_SHIFT)) & CAN_IE_RF0FE_MASK)

#define CAN_IE_RF0LE_MASK                        (0x8U)
#define CAN_IE_RF0LE_SHIFT                       (3U)
/*! RF0LE - Rx FIFO 0 message lost interrupt enable. */
#define CAN_IE_RF0LE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_RF0LE_SHIFT)) & CAN_IE_RF0LE_MASK)

#define CAN_IE_RF1NE_MASK                        (0x10U)
#define CAN_IE_RF1NE_SHIFT                       (4U)
/*! RF1NE - Rx FIFO 1 new message interrupt enable. */
#define CAN_IE_RF1NE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_RF1NE_SHIFT)) & CAN_IE_RF1NE_MASK)

#define CAN_IE_RF1WE_MASK                        (0x20U)
#define CAN_IE_RF1WE_SHIFT                       (5U)
/*! RF1WE - Rx FIFO 1 watermark reached interrupt enable. */
#define CAN_IE_RF1WE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_RF1WE_SHIFT)) & CAN_IE_RF1WE_MASK)

#define CAN_IE_RF1FE_MASK                        (0x40U)
#define CAN_IE_RF1FE_SHIFT                       (6U)
/*! RF1FE - Rx FIFO 1 full interrupt enable. */
#define CAN_IE_RF1FE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_RF1FE_SHIFT)) & CAN_IE_RF1FE_MASK)

#define CAN_IE_RF1LE_MASK                        (0x80U)
#define CAN_IE_RF1LE_SHIFT                       (7U)
/*! RF1LE - Rx FIFO 1 message lost interrupt enable. */
#define CAN_IE_RF1LE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_RF1LE_SHIFT)) & CAN_IE_RF1LE_MASK)

#define CAN_IE_HPME_MASK                         (0x100U)
#define CAN_IE_HPME_SHIFT                        (8U)
/*! HPME - High priority message interrupt enable. */
#define CAN_IE_HPME(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_HPME_SHIFT)) & CAN_IE_HPME_MASK)

#define CAN_IE_TCE_MASK                          (0x200U)
#define CAN_IE_TCE_SHIFT                         (9U)
/*! TCE - Transmission completed interrupt enable. */
#define CAN_IE_TCE(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IE_TCE_SHIFT)) & CAN_IE_TCE_MASK)

#define CAN_IE_TCFE_MASK                         (0x400U)
#define CAN_IE_TCFE_SHIFT                        (10U)
/*! TCFE - Transmission cancellation finished interrupt enable. */
#define CAN_IE_TCFE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_TCFE_SHIFT)) & CAN_IE_TCFE_MASK)

#define CAN_IE_TFEE_MASK                         (0x800U)
#define CAN_IE_TFEE_SHIFT                        (11U)
/*! TFEE - Tx FIFO empty interrupt enable. */
#define CAN_IE_TFEE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_TFEE_SHIFT)) & CAN_IE_TFEE_MASK)

#define CAN_IE_TEFNE_MASK                        (0x1000U)
#define CAN_IE_TEFNE_SHIFT                       (12U)
/*! TEFNE - Tx event FIFO new entry interrupt enable. */
#define CAN_IE_TEFNE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_TEFNE_SHIFT)) & CAN_IE_TEFNE_MASK)

#define CAN_IE_TEFWE_MASK                        (0x2000U)
#define CAN_IE_TEFWE_SHIFT                       (13U)
/*! TEFWE - Tx event FIFO watermark reached interrupt enable. */
#define CAN_IE_TEFWE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_TEFWE_SHIFT)) & CAN_IE_TEFWE_MASK)

#define CAN_IE_TEFFE_MASK                        (0x4000U)
#define CAN_IE_TEFFE_SHIFT                       (14U)
/*! TEFFE - Tx event FIFO full interrupt enable. */
#define CAN_IE_TEFFE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_TEFFE_SHIFT)) & CAN_IE_TEFFE_MASK)

#define CAN_IE_TEFLE_MASK                        (0x8000U)
#define CAN_IE_TEFLE_SHIFT                       (15U)
/*! TEFLE - Tx event FIFO element lost interrupt enable. */
#define CAN_IE_TEFLE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_TEFLE_SHIFT)) & CAN_IE_TEFLE_MASK)

#define CAN_IE_TSWE_MASK                         (0x10000U)
#define CAN_IE_TSWE_SHIFT                        (16U)
/*! TSWE - Timestamp wraparound interrupt enable. */
#define CAN_IE_TSWE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_TSWE_SHIFT)) & CAN_IE_TSWE_MASK)

#define CAN_IE_MRAFE_MASK                        (0x20000U)
#define CAN_IE_MRAFE_SHIFT                       (17U)
/*! MRAFE - Message RAM access failure interrupt enable. */
#define CAN_IE_MRAFE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_MRAFE_SHIFT)) & CAN_IE_MRAFE_MASK)

#define CAN_IE_TOOE_MASK                         (0x40000U)
#define CAN_IE_TOOE_SHIFT                        (18U)
/*! TOOE - Timeout occurred interrupt enable. */
#define CAN_IE_TOOE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_TOOE_SHIFT)) & CAN_IE_TOOE_MASK)

#define CAN_IE_DRXE_MASK                         (0x80000U)
#define CAN_IE_DRXE_SHIFT                        (19U)
/*! DRXE - Message stored in dedicated Rx buffer interrupt enable. */
#define CAN_IE_DRXE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_DRXE_SHIFT)) & CAN_IE_DRXE_MASK)

#define CAN_IE_BECE_MASK                         (0x100000U)
#define CAN_IE_BECE_SHIFT                        (20U)
/*! BECE - Bit error corrected interrupt enable. */
#define CAN_IE_BECE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_BECE_SHIFT)) & CAN_IE_BECE_MASK)

#define CAN_IE_BEUE_MASK                         (0x200000U)
#define CAN_IE_BEUE_SHIFT                        (21U)
/*! BEUE - Bit error uncorrected interrupt enable. */
#define CAN_IE_BEUE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_BEUE_SHIFT)) & CAN_IE_BEUE_MASK)

#define CAN_IE_ELOE_MASK                         (0x400000U)
#define CAN_IE_ELOE_SHIFT                        (22U)
/*! ELOE - Error logging overflow interrupt enable. */
#define CAN_IE_ELOE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_ELOE_SHIFT)) & CAN_IE_ELOE_MASK)

#define CAN_IE_EPE_MASK                          (0x800000U)
#define CAN_IE_EPE_SHIFT                         (23U)
/*! EPE - Error passive interrupt enable. */
#define CAN_IE_EPE(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IE_EPE_SHIFT)) & CAN_IE_EPE_MASK)

#define CAN_IE_EWE_MASK                          (0x1000000U)
#define CAN_IE_EWE_SHIFT                         (24U)
/*! EWE - Warning status interrupt enable. */
#define CAN_IE_EWE(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IE_EWE_SHIFT)) & CAN_IE_EWE_MASK)

#define CAN_IE_BOE_MASK                          (0x2000000U)
#define CAN_IE_BOE_SHIFT                         (25U)
/*! BOE - Bus_Off Status interrupt enable. */
#define CAN_IE_BOE(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IE_BOE_SHIFT)) & CAN_IE_BOE_MASK)

#define CAN_IE_WDIE_MASK                         (0x4000000U)
#define CAN_IE_WDIE_SHIFT                        (26U)
/*! WDIE - Watchdog interrupt enable. */
#define CAN_IE_WDIE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_WDIE_SHIFT)) & CAN_IE_WDIE_MASK)

#define CAN_IE_PEAE_MASK                         (0x8000000U)
#define CAN_IE_PEAE_SHIFT                        (27U)
/*! PEAE - Protocol error in arbitration phase interrupt enable. */
#define CAN_IE_PEAE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_PEAE_SHIFT)) & CAN_IE_PEAE_MASK)

#define CAN_IE_PEDE_MASK                         (0x10000000U)
#define CAN_IE_PEDE_SHIFT                        (28U)
/*! PEDE - Protocol error in data phase interrupt enable. */
#define CAN_IE_PEDE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_PEDE_SHIFT)) & CAN_IE_PEDE_MASK)

#define CAN_IE_ARAE_MASK                         (0x20000000U)
#define CAN_IE_ARAE_SHIFT                        (29U)
/*! ARAE - Access to reserved address interrupt enable. */
#define CAN_IE_ARAE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_ARAE_SHIFT)) & CAN_IE_ARAE_MASK)
/*! @} */

/*! @name ILS - Interrupt Line Select */
/*! @{ */

#define CAN_ILS_RF0NL_MASK                       (0x1U)
#define CAN_ILS_RF0NL_SHIFT                      (0U)
/*! RF0NL - Rx FIFO 0 new message interrupt line. */
#define CAN_ILS_RF0NL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_RF0NL_SHIFT)) & CAN_ILS_RF0NL_MASK)

#define CAN_ILS_RF0WL_MASK                       (0x2U)
#define CAN_ILS_RF0WL_SHIFT                      (1U)
/*! RF0WL - Rx FIFO 0 watermark reached interrupt line. */
#define CAN_ILS_RF0WL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_RF0WL_SHIFT)) & CAN_ILS_RF0WL_MASK)

#define CAN_ILS_RF0FL_MASK                       (0x4U)
#define CAN_ILS_RF0FL_SHIFT                      (2U)
/*! RF0FL - Rx FIFO 0 full interrupt line. */
#define CAN_ILS_RF0FL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_RF0FL_SHIFT)) & CAN_ILS_RF0FL_MASK)

#define CAN_ILS_RF0LL_MASK                       (0x8U)
#define CAN_ILS_RF0LL_SHIFT                      (3U)
/*! RF0LL - Rx FIFO 0 message lost interrupt line. */
#define CAN_ILS_RF0LL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_RF0LL_SHIFT)) & CAN_ILS_RF0LL_MASK)

#define CAN_ILS_RF1NL_MASK                       (0x10U)
#define CAN_ILS_RF1NL_SHIFT                      (4U)
/*! RF1NL - Rx FIFO 1 new message interrupt line. */
#define CAN_ILS_RF1NL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_RF1NL_SHIFT)) & CAN_ILS_RF1NL_MASK)

#define CAN_ILS_RF1WL_MASK                       (0x20U)
#define CAN_ILS_RF1WL_SHIFT                      (5U)
/*! RF1WL - Rx FIFO 1 watermark reached interrupt line. */
#define CAN_ILS_RF1WL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_RF1WL_SHIFT)) & CAN_ILS_RF1WL_MASK)

#define CAN_ILS_RF1FL_MASK                       (0x40U)
#define CAN_ILS_RF1FL_SHIFT                      (6U)
/*! RF1FL - Rx FIFO 1 full interrupt line. */
#define CAN_ILS_RF1FL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_RF1FL_SHIFT)) & CAN_ILS_RF1FL_MASK)

#define CAN_ILS_RF1LL_MASK                       (0x80U)
#define CAN_ILS_RF1LL_SHIFT                      (7U)
/*! RF1LL - Rx FIFO 1 message lost interrupt line. */
#define CAN_ILS_RF1LL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_RF1LL_SHIFT)) & CAN_ILS_RF1LL_MASK)

#define CAN_ILS_HPML_MASK                        (0x100U)
#define CAN_ILS_HPML_SHIFT                       (8U)
/*! HPML - High priority message interrupt line. */
#define CAN_ILS_HPML(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_HPML_SHIFT)) & CAN_ILS_HPML_MASK)

#define CAN_ILS_TCL_MASK                         (0x200U)
#define CAN_ILS_TCL_SHIFT                        (9U)
/*! TCL - Transmission completed interrupt line. */
#define CAN_ILS_TCL(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TCL_SHIFT)) & CAN_ILS_TCL_MASK)

#define CAN_ILS_TCFL_MASK                        (0x400U)
#define CAN_ILS_TCFL_SHIFT                       (10U)
/*! TCFL - Transmission cancellation finished interrupt line. */
#define CAN_ILS_TCFL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TCFL_SHIFT)) & CAN_ILS_TCFL_MASK)

#define CAN_ILS_TFEL_MASK                        (0x800U)
#define CAN_ILS_TFEL_SHIFT                       (11U)
/*! TFEL - Tx FIFO empty interrupt line. */
#define CAN_ILS_TFEL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TFEL_SHIFT)) & CAN_ILS_TFEL_MASK)

#define CAN_ILS_TEFNL_MASK                       (0x1000U)
#define CAN_ILS_TEFNL_SHIFT                      (12U)
/*! TEFNL - Tx event FIFO new entry interrupt line. */
#define CAN_ILS_TEFNL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TEFNL_SHIFT)) & CAN_ILS_TEFNL_MASK)

#define CAN_ILS_TEFWL_MASK                       (0x2000U)
#define CAN_ILS_TEFWL_SHIFT                      (13U)
/*! TEFWL - Tx event FIFO watermark reached interrupt line. */
#define CAN_ILS_TEFWL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TEFWL_SHIFT)) & CAN_ILS_TEFWL_MASK)

#define CAN_ILS_TEFFL_MASK                       (0x4000U)
#define CAN_ILS_TEFFL_SHIFT                      (14U)
/*! TEFFL - Tx event FIFO full interrupt line. */
#define CAN_ILS_TEFFL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TEFFL_SHIFT)) & CAN_ILS_TEFFL_MASK)

#define CAN_ILS_TEFLL_MASK                       (0x8000U)
#define CAN_ILS_TEFLL_SHIFT                      (15U)
/*! TEFLL - Tx event FIFO element lost interrupt line. */
#define CAN_ILS_TEFLL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TEFLL_SHIFT)) & CAN_ILS_TEFLL_MASK)

#define CAN_ILS_TSWL_MASK                        (0x10000U)
#define CAN_ILS_TSWL_SHIFT                       (16U)
/*! TSWL - Timestamp wraparound interrupt line. */
#define CAN_ILS_TSWL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TSWL_SHIFT)) & CAN_ILS_TSWL_MASK)

#define CAN_ILS_MRAFL_MASK                       (0x20000U)
#define CAN_ILS_MRAFL_SHIFT                      (17U)
/*! MRAFL - Message RAM access failure interrupt line. */
#define CAN_ILS_MRAFL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_MRAFL_SHIFT)) & CAN_ILS_MRAFL_MASK)

#define CAN_ILS_TOOL_MASK                        (0x40000U)
#define CAN_ILS_TOOL_SHIFT                       (18U)
/*! TOOL - Timeout occurred interrupt line. */
#define CAN_ILS_TOOL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TOOL_SHIFT)) & CAN_ILS_TOOL_MASK)

#define CAN_ILS_DRXL_MASK                        (0x80000U)
#define CAN_ILS_DRXL_SHIFT                       (19U)
/*! DRXL - Message stored in dedicated Rx buffer interrupt line. */
#define CAN_ILS_DRXL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_DRXL_SHIFT)) & CAN_ILS_DRXL_MASK)

#define CAN_ILS_BECL_MASK                        (0x100000U)
#define CAN_ILS_BECL_SHIFT                       (20U)
/*! BECL - Bit error corrected interrupt line. */
#define CAN_ILS_BECL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_BECL_SHIFT)) & CAN_ILS_BECL_MASK)

#define CAN_ILS_BEUL_MASK                        (0x200000U)
#define CAN_ILS_BEUL_SHIFT                       (21U)
/*! BEUL - Bit error uncorrected interrupt line. */
#define CAN_ILS_BEUL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_BEUL_SHIFT)) & CAN_ILS_BEUL_MASK)

#define CAN_ILS_ELOL_MASK                        (0x400000U)
#define CAN_ILS_ELOL_SHIFT                       (22U)
/*! ELOL - Error logging overflow interrupt line. */
#define CAN_ILS_ELOL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_ELOL_SHIFT)) & CAN_ILS_ELOL_MASK)

#define CAN_ILS_EPL_MASK                         (0x800000U)
#define CAN_ILS_EPL_SHIFT                        (23U)
/*! EPL - Error passive interrupt line. */
#define CAN_ILS_EPL(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ILS_EPL_SHIFT)) & CAN_ILS_EPL_MASK)

#define CAN_ILS_EWL_MASK                         (0x1000000U)
#define CAN_ILS_EWL_SHIFT                        (24U)
/*! EWL - Warning status interrupt line. */
#define CAN_ILS_EWL(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ILS_EWL_SHIFT)) & CAN_ILS_EWL_MASK)

#define CAN_ILS_BOL_MASK                         (0x2000000U)
#define CAN_ILS_BOL_SHIFT                        (25U)
/*! BOL - Bus_Off Status interrupt line. */
#define CAN_ILS_BOL(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ILS_BOL_SHIFT)) & CAN_ILS_BOL_MASK)

#define CAN_ILS_WDIL_MASK                        (0x4000000U)
#define CAN_ILS_WDIL_SHIFT                       (26U)
/*! WDIL - Watchdog interrupt line. */
#define CAN_ILS_WDIL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_WDIL_SHIFT)) & CAN_ILS_WDIL_MASK)

#define CAN_ILS_PEAL_MASK                        (0x8000000U)
#define CAN_ILS_PEAL_SHIFT                       (27U)
/*! PEAL - Protocol error in arbitration phase interrupt line. */
#define CAN_ILS_PEAL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_PEAL_SHIFT)) & CAN_ILS_PEAL_MASK)

#define CAN_ILS_PEDL_MASK                        (0x10000000U)
#define CAN_ILS_PEDL_SHIFT                       (28U)
/*! PEDL - Protocol error in data phase interrupt line. */
#define CAN_ILS_PEDL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_PEDL_SHIFT)) & CAN_ILS_PEDL_MASK)

#define CAN_ILS_ARAL_MASK                        (0x20000000U)
#define CAN_ILS_ARAL_SHIFT                       (29U)
/*! ARAL - Access to reserved address interrupt line. */
#define CAN_ILS_ARAL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_ARAL_SHIFT)) & CAN_ILS_ARAL_MASK)
/*! @} */

/*! @name ILE - Interrupt Line Enable */
/*! @{ */

#define CAN_ILE_EINT0_MASK                       (0x1U)
#define CAN_ILE_EINT0_SHIFT                      (0U)
/*! EINT0 - Enable interrupt line 0. */
#define CAN_ILE_EINT0(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILE_EINT0_SHIFT)) & CAN_ILE_EINT0_MASK)

#define CAN_ILE_EINT1_MASK                       (0x2U)
#define CAN_ILE_EINT1_SHIFT                      (1U)
/*! EINT1 - Enable interrupt line 1. */
#define CAN_ILE_EINT1(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILE_EINT1_SHIFT)) & CAN_ILE_EINT1_MASK)
/*! @} */

/*! @name GFC - Global Filter Configuration */
/*! @{ */

#define CAN_GFC_RRFE_MASK                        (0x1U)
#define CAN_GFC_RRFE_SHIFT                       (0U)
/*! RRFE - Reject remote frames extended. */
#define CAN_GFC_RRFE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_GFC_RRFE_SHIFT)) & CAN_GFC_RRFE_MASK)

#define CAN_GFC_RRFS_MASK                        (0x2U)
#define CAN_GFC_RRFS_SHIFT                       (1U)
/*! RRFS - Reject remote frames standard. */
#define CAN_GFC_RRFS(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_GFC_RRFS_SHIFT)) & CAN_GFC_RRFS_MASK)

#define CAN_GFC_ANFE_MASK                        (0xCU)
#define CAN_GFC_ANFE_SHIFT                       (2U)
/*! ANFE - Accept non-matching frames extended. */
#define CAN_GFC_ANFE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_GFC_ANFE_SHIFT)) & CAN_GFC_ANFE_MASK)

#define CAN_GFC_ANFS_MASK                        (0x30U)
#define CAN_GFC_ANFS_SHIFT                       (4U)
/*! ANFS - Accept non-matching frames standard. */
#define CAN_GFC_ANFS(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_GFC_ANFS_SHIFT)) & CAN_GFC_ANFS_MASK)
/*! @} */

/*! @name SIDFC - Standard ID Filter Configuration */
/*! @{ */

#define CAN_SIDFC_FLSSA_MASK                     (0xFFFCU)
#define CAN_SIDFC_FLSSA_SHIFT                    (2U)
/*! FLSSA - Filter list standard start address. */
#define CAN_SIDFC_FLSSA(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_SIDFC_FLSSA_SHIFT)) & CAN_SIDFC_FLSSA_MASK)

#define CAN_SIDFC_LSS_MASK                       (0xFF0000U)
#define CAN_SIDFC_LSS_SHIFT                      (16U)
/*! LSS - List size standard 0 = No standard message ID filter. */
#define CAN_SIDFC_LSS(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_SIDFC_LSS_SHIFT)) & CAN_SIDFC_LSS_MASK)
/*! @} */

/*! @name XIDFC - Extended ID Filter Configuration */
/*! @{ */

#define CAN_XIDFC_FLESA_MASK                     (0xFFFCU)
#define CAN_XIDFC_FLESA_SHIFT                    (2U)
/*! FLESA - Filter list extended start address. */
#define CAN_XIDFC_FLESA(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_XIDFC_FLESA_SHIFT)) & CAN_XIDFC_FLESA_MASK)

#define CAN_XIDFC_LSE_MASK                       (0xFF0000U)
#define CAN_XIDFC_LSE_SHIFT                      (16U)
/*! LSE - List size extended 0 = No extended message ID filter. */
#define CAN_XIDFC_LSE(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_XIDFC_LSE_SHIFT)) & CAN_XIDFC_LSE_MASK)
/*! @} */

/*! @name XIDAM - Extended ID AND Mask */
/*! @{ */

#define CAN_XIDAM_EIDM_MASK                      (0x1FFFFFFFU)
#define CAN_XIDAM_EIDM_SHIFT                     (0U)
/*! EIDM - Extended ID mask. */
#define CAN_XIDAM_EIDM(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_XIDAM_EIDM_SHIFT)) & CAN_XIDAM_EIDM_MASK)
/*! @} */

/*! @name HPMS - High Priority Message Status */
/*! @{ */

#define CAN_HPMS_BIDX_MASK                       (0x3FU)
#define CAN_HPMS_BIDX_SHIFT                      (0U)
/*! BIDX - Buffer index. */
#define CAN_HPMS_BIDX(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_HPMS_BIDX_SHIFT)) & CAN_HPMS_BIDX_MASK)

#define CAN_HPMS_MSI_MASK                        (0xC0U)
#define CAN_HPMS_MSI_SHIFT                       (6U)
/*! MSI - Message storage indicator. */
#define CAN_HPMS_MSI(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_HPMS_MSI_SHIFT)) & CAN_HPMS_MSI_MASK)

#define CAN_HPMS_FIDX_MASK                       (0x7F00U)
#define CAN_HPMS_FIDX_SHIFT                      (8U)
/*! FIDX - Filter index. */
#define CAN_HPMS_FIDX(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_HPMS_FIDX_SHIFT)) & CAN_HPMS_FIDX_MASK)

#define CAN_HPMS_FLST_MASK                       (0x8000U)
#define CAN_HPMS_FLST_SHIFT                      (15U)
/*! FLST - Filter list. */
#define CAN_HPMS_FLST(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_HPMS_FLST_SHIFT)) & CAN_HPMS_FLST_MASK)
/*! @} */

/*! @name NDAT1 - New Data 1 */
/*! @{ */

#define CAN_NDAT1_ND_MASK                        (0xFFFFFFFFU)
#define CAN_NDAT1_ND_SHIFT                       (0U)
/*! ND - New Data. */
#define CAN_NDAT1_ND(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_NDAT1_ND_SHIFT)) & CAN_NDAT1_ND_MASK)
/*! @} */

/*! @name NDAT2 - New Data 2 */
/*! @{ */

#define CAN_NDAT2_ND_MASK                        (0xFFFFFFFFU)
#define CAN_NDAT2_ND_SHIFT                       (0U)
/*! ND - New Data. */
#define CAN_NDAT2_ND(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_NDAT2_ND_SHIFT)) & CAN_NDAT2_ND_MASK)
/*! @} */

/*! @name RXF0C - Rx FIFO 0 Configuration */
/*! @{ */

#define CAN_RXF0C_F0SA_MASK                      (0xFFFCU)
#define CAN_RXF0C_F0SA_SHIFT                     (2U)
/*! F0SA - Rx FIFO 0 start address. */
#define CAN_RXF0C_F0SA(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF0C_F0SA_SHIFT)) & CAN_RXF0C_F0SA_MASK)

#define CAN_RXF0C_F0S_MASK                       (0x7F0000U)
#define CAN_RXF0C_F0S_SHIFT                      (16U)
/*! F0S - Rx FIFO 0 size. */
#define CAN_RXF0C_F0S(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_RXF0C_F0S_SHIFT)) & CAN_RXF0C_F0S_MASK)

#define CAN_RXF0C_F0WM_MASK                      (0x7F000000U)
#define CAN_RXF0C_F0WM_SHIFT                     (24U)
/*! F0WM - Rx FIFO 0 watermark 0 = Watermark interrupt disabled. */
#define CAN_RXF0C_F0WM(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF0C_F0WM_SHIFT)) & CAN_RXF0C_F0WM_MASK)

#define CAN_RXF0C_F0OM_MASK                      (0x80000000U)
#define CAN_RXF0C_F0OM_SHIFT                     (31U)
/*! F0OM - FIFO 0 operation mode. */
#define CAN_RXF0C_F0OM(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF0C_F0OM_SHIFT)) & CAN_RXF0C_F0OM_MASK)
/*! @} */

/*! @name RXF0S - Rx FIFO 0 Status */
/*! @{ */

#define CAN_RXF0S_F0FL_MASK                      (0x7FU)
#define CAN_RXF0S_F0FL_SHIFT                     (0U)
/*! F0FL - Rx FIFO 0 fill level. */
#define CAN_RXF0S_F0FL(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF0S_F0FL_SHIFT)) & CAN_RXF0S_F0FL_MASK)

#define CAN_RXF0S_F0GI_MASK                      (0x3F00U)
#define CAN_RXF0S_F0GI_SHIFT                     (8U)
/*! F0GI - Rx FIFO 0 get index. */
#define CAN_RXF0S_F0GI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF0S_F0GI_SHIFT)) & CAN_RXF0S_F0GI_MASK)

#define CAN_RXF0S_F0PI_MASK                      (0x3F0000U)
#define CAN_RXF0S_F0PI_SHIFT                     (16U)
/*! F0PI - Rx FIFO 0 put index. */
#define CAN_RXF0S_F0PI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF0S_F0PI_SHIFT)) & CAN_RXF0S_F0PI_MASK)

#define CAN_RXF0S_F0F_MASK                       (0x1000000U)
#define CAN_RXF0S_F0F_SHIFT                      (24U)
/*! F0F - Rx FIFO 0 full. */
#define CAN_RXF0S_F0F(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_RXF0S_F0F_SHIFT)) & CAN_RXF0S_F0F_MASK)

#define CAN_RXF0S_RF0L_MASK                      (0x2000000U)
#define CAN_RXF0S_RF0L_SHIFT                     (25U)
/*! RF0L - Rx FIFO 0 message lost. */
#define CAN_RXF0S_RF0L(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF0S_RF0L_SHIFT)) & CAN_RXF0S_RF0L_MASK)
/*! @} */

/*! @name RXF0A - Rx FIFO 0 Acknowledge */
/*! @{ */

#define CAN_RXF0A_F0AI_MASK                      (0x3FU)
#define CAN_RXF0A_F0AI_SHIFT                     (0U)
/*! F0AI - Rx FIFO 0 acknowledge index. */
#define CAN_RXF0A_F0AI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF0A_F0AI_SHIFT)) & CAN_RXF0A_F0AI_MASK)
/*! @} */

/*! @name RXBC - Rx Buffer Configuration */
/*! @{ */

#define CAN_RXBC_RBSA_MASK                       (0xFFFCU)
#define CAN_RXBC_RBSA_SHIFT                      (2U)
/*! RBSA - Rx buffer start address. */
#define CAN_RXBC_RBSA(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_RXBC_RBSA_SHIFT)) & CAN_RXBC_RBSA_MASK)
/*! @} */

/*! @name RXF1C - Rx FIFO 1 Configuration */
/*! @{ */

#define CAN_RXF1C_F1SA_MASK                      (0xFFFCU)
#define CAN_RXF1C_F1SA_SHIFT                     (2U)
/*! F1SA - Rx FIFO 1 start address. */
#define CAN_RXF1C_F1SA(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF1C_F1SA_SHIFT)) & CAN_RXF1C_F1SA_MASK)

#define CAN_RXF1C_F1S_MASK                       (0x7F0000U)
#define CAN_RXF1C_F1S_SHIFT                      (16U)
/*! F1S - Rx FIFO 1 size 0 = No Rx FIFO 1. */
#define CAN_RXF1C_F1S(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_RXF1C_F1S_SHIFT)) & CAN_RXF1C_F1S_MASK)

#define CAN_RXF1C_F1WM_MASK                      (0x7F000000U)
#define CAN_RXF1C_F1WM_SHIFT                     (24U)
/*! F1WM - Rx FIFO 1 watermark 0 = Watermark interrupt disabled. */
#define CAN_RXF1C_F1WM(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF1C_F1WM_SHIFT)) & CAN_RXF1C_F1WM_MASK)

#define CAN_RXF1C_F1OM_MASK                      (0x80000000U)
#define CAN_RXF1C_F1OM_SHIFT                     (31U)
/*! F1OM - FIFO 1 operation mode. */
#define CAN_RXF1C_F1OM(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF1C_F1OM_SHIFT)) & CAN_RXF1C_F1OM_MASK)
/*! @} */

/*! @name RXF1S - Rx FIFO 1 Status */
/*! @{ */

#define CAN_RXF1S_F1FL_MASK                      (0x7FU)
#define CAN_RXF1S_F1FL_SHIFT                     (0U)
/*! F1FL - Rx FIFO 1 fill level. */
#define CAN_RXF1S_F1FL(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF1S_F1FL_SHIFT)) & CAN_RXF1S_F1FL_MASK)

#define CAN_RXF1S_F1GI_MASK                      (0x3F00U)
#define CAN_RXF1S_F1GI_SHIFT                     (8U)
/*! F1GI - Rx FIFO 1 get index. */
#define CAN_RXF1S_F1GI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF1S_F1GI_SHIFT)) & CAN_RXF1S_F1GI_MASK)

#define CAN_RXF1S_F1PI_MASK                      (0x3F0000U)
#define CAN_RXF1S_F1PI_SHIFT                     (16U)
/*! F1PI - Rx FIFO 1 put index. */
#define CAN_RXF1S_F1PI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF1S_F1PI_SHIFT)) & CAN_RXF1S_F1PI_MASK)

#define CAN_RXF1S_F1F_MASK                       (0x1000000U)
#define CAN_RXF1S_F1F_SHIFT                      (24U)
/*! F1F - Rx FIFO 1 full. */
#define CAN_RXF1S_F1F(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_RXF1S_F1F_SHIFT)) & CAN_RXF1S_F1F_MASK)

#define CAN_RXF1S_RF1L_MASK                      (0x2000000U)
#define CAN_RXF1S_RF1L_SHIFT                     (25U)
/*! RF1L - Rx FIFO 1 message lost. */
#define CAN_RXF1S_RF1L(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF1S_RF1L_SHIFT)) & CAN_RXF1S_RF1L_MASK)
/*! @} */

/*! @name RXF1A - Rx FIFO 1 Acknowledge */
/*! @{ */

#define CAN_RXF1A_F1AI_MASK                      (0x3FU)
#define CAN_RXF1A_F1AI_SHIFT                     (0U)
/*! F1AI - Rx FIFO 1 acknowledge index. */
#define CAN_RXF1A_F1AI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF1A_F1AI_SHIFT)) & CAN_RXF1A_F1AI_MASK)
/*! @} */

/*! @name RXESC - Rx Buffer and FIFO Element Size Configuration */
/*! @{ */

#define CAN_RXESC_F0DS_MASK                      (0x7U)
#define CAN_RXESC_F0DS_SHIFT                     (0U)
/*! F0DS - Rx FIFO 0 data field size. */
#define CAN_RXESC_F0DS(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXESC_F0DS_SHIFT)) & CAN_RXESC_F0DS_MASK)

#define CAN_RXESC_F1DS_MASK                      (0x70U)
#define CAN_RXESC_F1DS_SHIFT                     (4U)
/*! F1DS - Rx FIFO 1 data field size. */
#define CAN_RXESC_F1DS(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXESC_F1DS_SHIFT)) & CAN_RXESC_F1DS_MASK)

#define CAN_RXESC_RBDS_MASK                      (0x700U)
#define CAN_RXESC_RBDS_SHIFT                     (8U)
/*! RBDS - . */
#define CAN_RXESC_RBDS(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXESC_RBDS_SHIFT)) & CAN_RXESC_RBDS_MASK)
/*! @} */

/*! @name TXBC - Tx Buffer Configuration */
/*! @{ */

#define CAN_TXBC_TBSA_MASK                       (0xFFFCU)
#define CAN_TXBC_TBSA_SHIFT                      (2U)
/*! TBSA - Tx buffers start address. */
#define CAN_TXBC_TBSA(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TXBC_TBSA_SHIFT)) & CAN_TXBC_TBSA_MASK)

#define CAN_TXBC_NDTB_MASK                       (0x3F0000U)
#define CAN_TXBC_NDTB_SHIFT                      (16U)
/*! NDTB - Number of dedicated transmit buffers 0 = No dedicated Tx buffers. */
#define CAN_TXBC_NDTB(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TXBC_NDTB_SHIFT)) & CAN_TXBC_NDTB_MASK)

#define CAN_TXBC_TFQS_MASK                       (0x3F000000U)
#define CAN_TXBC_TFQS_SHIFT                      (24U)
/*! TFQS - Transmit FIFO/queue size 0 = No tx FIFO/Queue. */
#define CAN_TXBC_TFQS(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TXBC_TFQS_SHIFT)) & CAN_TXBC_TFQS_MASK)

#define CAN_TXBC_TFQM_MASK                       (0x40000000U)
#define CAN_TXBC_TFQM_SHIFT                      (30U)
/*! TFQM - Tx FIFO/queue mode. */
#define CAN_TXBC_TFQM(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TXBC_TFQM_SHIFT)) & CAN_TXBC_TFQM_MASK)
/*! @} */

/*! @name TXFQS - Tx FIFO/Queue Status */
/*! @{ */

#define CAN_TXFQS_TFGI_MASK                      (0x1F00U)
#define CAN_TXFQS_TFGI_SHIFT                     (8U)
/*! TFGI - Tx FIFO get index. */
#define CAN_TXFQS_TFGI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXFQS_TFGI_SHIFT)) & CAN_TXFQS_TFGI_MASK)

#define CAN_TXFQS_TFQPI_MASK                     (0x1F0000U)
#define CAN_TXFQS_TFQPI_SHIFT                    (16U)
/*! TFQPI - Tx FIFO/queue put index. */
#define CAN_TXFQS_TFQPI(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_TXFQS_TFQPI_SHIFT)) & CAN_TXFQS_TFQPI_MASK)

#define CAN_TXFQS_TFQF_MASK                      (0x200000U)
#define CAN_TXFQS_TFQF_SHIFT                     (21U)
/*! TFQF - Tx FIFO/queue full. */
#define CAN_TXFQS_TFQF(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXFQS_TFQF_SHIFT)) & CAN_TXFQS_TFQF_MASK)
/*! @} */

/*! @name TXESC - Tx Buffer Element Size Configuration */
/*! @{ */

#define CAN_TXESC_TBDS_MASK                      (0x7U)
#define CAN_TXESC_TBDS_SHIFT                     (0U)
/*! TBDS - Tx buffer data field size. */
#define CAN_TXESC_TBDS(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXESC_TBDS_SHIFT)) & CAN_TXESC_TBDS_MASK)
/*! @} */

/*! @name TXBRP - Tx Buffer Request Pending */
/*! @{ */

#define CAN_TXBRP_TRP_MASK                       (0xFFFFFFFFU)
#define CAN_TXBRP_TRP_SHIFT                      (0U)
/*! TRP - Transmission request pending. */
#define CAN_TXBRP_TRP(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TXBRP_TRP_SHIFT)) & CAN_TXBRP_TRP_MASK)
/*! @} */

/*! @name TXBAR - Tx Buffer Add Request */
/*! @{ */

#define CAN_TXBAR_AR_MASK                        (0xFFFFFFFFU)
#define CAN_TXBAR_AR_SHIFT                       (0U)
/*! AR - Add request. */
#define CAN_TXBAR_AR(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TXBAR_AR_SHIFT)) & CAN_TXBAR_AR_MASK)
/*! @} */

/*! @name TXBCR - Tx Buffer Cancellation Request */
/*! @{ */

#define CAN_TXBCR_CR_MASK                        (0xFFFFFFFFU)
#define CAN_TXBCR_CR_SHIFT                       (0U)
/*! CR - Cancellation request. */
#define CAN_TXBCR_CR(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TXBCR_CR_SHIFT)) & CAN_TXBCR_CR_MASK)
/*! @} */

/*! @name TXBTO - Tx Buffer Transmission Occurred */
/*! @{ */

#define CAN_TXBTO_TO_MASK                        (0xFFFFFFFFU)
#define CAN_TXBTO_TO_SHIFT                       (0U)
/*! TO - Transmission occurred. */
#define CAN_TXBTO_TO(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TXBTO_TO_SHIFT)) & CAN_TXBTO_TO_MASK)
/*! @} */

/*! @name TXBCF - Tx Buffer Cancellation Finished */
/*! @{ */

#define CAN_TXBCF_TO_MASK                        (0xFFFFFFFFU)
#define CAN_TXBCF_TO_SHIFT                       (0U)
/*! TO - Cancellation finished. */
#define CAN_TXBCF_TO(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TXBCF_TO_SHIFT)) & CAN_TXBCF_TO_MASK)
/*! @} */

/*! @name TXBTIE - Tx Buffer Transmission Interrupt Enable */
/*! @{ */

#define CAN_TXBTIE_TIE_MASK                      (0xFFFFFFFFU)
#define CAN_TXBTIE_TIE_SHIFT                     (0U)
/*! TIE - Transmission interrupt enable. */
#define CAN_TXBTIE_TIE(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXBTIE_TIE_SHIFT)) & CAN_TXBTIE_TIE_MASK)
/*! @} */

/*! @name TXBCIE - Tx Buffer Cancellation Finished Interrupt Enable */
/*! @{ */

#define CAN_TXBCIE_CFIE_MASK                     (0xFFFFFFFFU)
#define CAN_TXBCIE_CFIE_SHIFT                    (0U)
/*! CFIE - Cancellation finished interrupt enable. */
#define CAN_TXBCIE_CFIE(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_TXBCIE_CFIE_SHIFT)) & CAN_TXBCIE_CFIE_MASK)
/*! @} */

/*! @name TXEFC - Tx Event FIFO Configuration */
/*! @{ */

#define CAN_TXEFC_EFSA_MASK                      (0xFFFCU)
#define CAN_TXEFC_EFSA_SHIFT                     (2U)
/*! EFSA - Event FIFO start address. */
#define CAN_TXEFC_EFSA(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXEFC_EFSA_SHIFT)) & CAN_TXEFC_EFSA_MASK)

#define CAN_TXEFC_EFS_MASK                       (0x3F0000U)
#define CAN_TXEFC_EFS_SHIFT                      (16U)
/*! EFS - Event FIFO size 0 = Tx event FIFO disabled. */
#define CAN_TXEFC_EFS(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TXEFC_EFS_SHIFT)) & CAN_TXEFC_EFS_MASK)

#define CAN_TXEFC_EFWM_MASK                      (0x3F000000U)
#define CAN_TXEFC_EFWM_SHIFT                     (24U)
/*! EFWM - Event FIFO watermark 0 = Watermark interrupt disabled. */
#define CAN_TXEFC_EFWM(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXEFC_EFWM_SHIFT)) & CAN_TXEFC_EFWM_MASK)
/*! @} */

/*! @name TXEFS - Tx Event FIFO Status */
/*! @{ */

#define CAN_TXEFS_EFFL_MASK                      (0x3FU)
#define CAN_TXEFS_EFFL_SHIFT                     (0U)
/*! EFFL - Event FIFO fill level. */
#define CAN_TXEFS_EFFL(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXEFS_EFFL_SHIFT)) & CAN_TXEFS_EFFL_MASK)

#define CAN_TXEFS_EFGI_MASK                      (0x1F00U)
#define CAN_TXEFS_EFGI_SHIFT                     (8U)
/*! EFGI - Event FIFO get index. */
#define CAN_TXEFS_EFGI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXEFS_EFGI_SHIFT)) & CAN_TXEFS_EFGI_MASK)

#define CAN_TXEFS_EFPI_MASK                      (0x3F0000U)
#define CAN_TXEFS_EFPI_SHIFT                     (16U)
/*! EFPI - Event FIFO put index. */
#define CAN_TXEFS_EFPI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXEFS_EFPI_SHIFT)) & CAN_TXEFS_EFPI_MASK)

#define CAN_TXEFS_EFF_MASK                       (0x1000000U)
#define CAN_TXEFS_EFF_SHIFT                      (24U)
/*! EFF - Event FIFO full. */
#define CAN_TXEFS_EFF(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TXEFS_EFF_SHIFT)) & CAN_TXEFS_EFF_MASK)

#define CAN_TXEFS_TEFL_MASK                      (0x2000000U)
#define CAN_TXEFS_TEFL_SHIFT                     (25U)
/*! TEFL - Tx event FIFO element lost. */
#define CAN_TXEFS_TEFL(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXEFS_TEFL_SHIFT)) & CAN_TXEFS_TEFL_MASK)
/*! @} */

/*! @name TXEFA - Tx Event FIFO Acknowledge */
/*! @{ */

#define CAN_TXEFA_EFAI_MASK                      (0x1FU)
#define CAN_TXEFA_EFAI_SHIFT                     (0U)
/*! EFAI - Event FIFO acknowledge index. */
#define CAN_TXEFA_EFAI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXEFA_EFAI_SHIFT)) & CAN_TXEFA_EFAI_MASK)
/*! @} */

/*! @name MRBA - CAN Message RAM Base Address */
/*! @{ */

#define CAN_MRBA_BA_MASK                         (0xFFFF0000U)
#define CAN_MRBA_BA_SHIFT                        (16U)
/*! BA - Base address for the message RAM in the chip memory map. */
#define CAN_MRBA_BA(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_MRBA_BA_SHIFT)) & CAN_MRBA_BA_MASK)
/*! @} */

/*! @name ETSCC - External Timestamp Counter Configuration */
/*! @{ */

#define CAN_ETSCC_ETCP_MASK                      (0x7FFU)
#define CAN_ETSCC_ETCP_SHIFT                     (0U)
/*! ETCP - External timestamp prescaler value. */
#define CAN_ETSCC_ETCP(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_ETSCC_ETCP_SHIFT)) & CAN_ETSCC_ETCP_MASK)

#define CAN_ETSCC_ETCE_MASK                      (0x80000000U)
#define CAN_ETSCC_ETCE_SHIFT                     (31U)
/*! ETCE - External timestamp counter enable. */
#define CAN_ETSCC_ETCE(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_ETSCC_ETCE_SHIFT)) & CAN_ETSCC_ETCE_MASK)
/*! @} */

/*! @name ETSCV - External Timestamp Counter Value */
/*! @{ */

#define CAN_ETSCV_ETSC_MASK                      (0xFFFFU)
#define CAN_ETSCV_ETSC_SHIFT                     (0U)
/*! ETSC - External timestamp counter. */
#define CAN_ETSCV_ETSC(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_ETSCV_ETSC_SHIFT)) & CAN_ETSCV_ETSC_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group CAN_Register_Masks */


/*!
 * @}
 */ /* end of group CAN_Peripheral_Access_Layer */


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


#endif  /* CAN_H_ */


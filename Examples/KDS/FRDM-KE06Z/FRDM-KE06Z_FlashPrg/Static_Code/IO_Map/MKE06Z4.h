/*
** ###################################################################
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    MKE06P80M48SF0RM, Rev. 1, May 2014
**     Version:             rev. 1.5, 2015-10-14
**     Build:               b150325
**
**     Abstract:
**         This header file implements peripheral memory map for MKE06Z4
**         processor.
**
**     Copyright (c) 1997 - 2015 Freescale Semiconductor, Inc.
**     All Rights Reserved.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2013-07-30)
**         Initial version.
**     - rev. 1.1 (2013-10-29)
**         Definition of BITBAND macros updated to support peripherals with 32-bit acces disabled.
**     - rev. 1.2 (2013-10-30)
**         Update according to reference manual rev. 1.
**     - rev. 1.3 (2014-01-10)
**         CAN - Corrected address of TSIDR1 register.
**         CAN - Corrected name of MSCAN_TDLR bit DLC to TDLC.
**         FTM0 - Added access macro for EXTTRIG register.
**         NVIC - Registers access macros improved.
**         SCB - Unused bits removed, mask, shift macros improved.
**         Defines of interrupt vectors aligned to RM.
**     - rev. 1.4 (2014-06-18)
**         I2C - Renamed status register S to S1 to match RM naming.
**         Renamed interrupts: INT_PMC to INT_LVD_LVW, INT_ADC to ADC0,INT_WDOG to INT_Watchdog.
**     - rev. 1.5 (2015-10-14)
**         Renamed interrupt INT_Watchdog to INT_WDOG_EWM
**
** ###################################################################
*/

/*!
 * @file MKE06Z4.h
 * @version 1.5
 * @date 2015-10-14
 * @brief Peripheral memory map for MKE06Z4
 *
 * This header file implements peripheral memory map for MKE06Z4 processor.
 */


/* ----------------------------------------------------------------------------
   -- MCU activation
   ---------------------------------------------------------------------------- */

/* Prevention from multiple including the same memory map */
#if !defined(MCU_MKE06Z4)  /* Check if memory map has not been already included */
#define MCU_MKE06Z4

/* Check if another memory map has not been also included */
#if (defined(MCU_ACTIVE))
  #error MKE06Z4 memory map: There is already included another memory map. Only one memory map can be included.
#endif /* (defined(MCU_ACTIVE)) */
#define MCU_ACTIVE

#include <stdint.h>

/** Memory map major version (memory maps with equal major version number are
 * compatible) */
#define MCU_MEM_MAP_VERSION 0x0100u
/** Memory map minor version */
#define MCU_MEM_MAP_VERSION_MINOR 0x0005u


/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
typedef enum {
  INT_Initial_Stack_Pointer    = 0,                /**< Initial Stack Pointer */
  INT_Initial_Program_Counter  = 1,                /**< Initial Program Counter */
  INT_NMI                      = 2,                /**< Non-maskable Interrupt (NMI) */
  INT_Hard_Fault               = 3,                /**< Hard Fault */
  INT_Reserved4                = 4,                /**< Reserved interrupt */
  INT_Reserved5                = 5,                /**< Reserved interrupt */
  INT_Reserved6                = 6,                /**< Reserved interrupt */
  INT_Reserved7                = 7,                /**< Reserved interrupt */
  INT_Reserved8                = 8,                /**< Reserved interrupt */
  INT_Reserved9                = 9,                /**< Reserved interrupt */
  INT_Reserved10               = 10,               /**< Reserved interrupt */
  INT_SVCall                   = 11,               /**< Supervisor call (SVCall) */
  INT_Reserved12               = 12,               /**< Reserved interrupt */
  INT_Reserved13               = 13,               /**< Reserved interrupt */
  INT_PendableSrvReq           = 14,               /**< Pendable request for system service (PendableSrvReq) */
  INT_SysTick                  = 15,               /**< System tick timer (SysTick) */
  INT_Reserved16               = 16,               /**< Reserved interrupt */
  INT_Reserved17               = 17,               /**< Reserved interrupt */
  INT_Reserved18               = 18,               /**< Reserved interrupt */
  INT_Reserved19               = 19,               /**< Reserved interrupt */
  INT_Reserved20               = 20,               /**< Reserved interrupt */
  INT_FTMRE                    = 21,               /**< FTMRE command complete */
  INT_LVD_LLW                  = 22,               /**< Low-voltage warning */
  INT_IRQ                      = 23,               /**< External interrupt */
  INT_I2C0                     = 24,               /**< I2C0 single interrupt vector for all sources */
  INT_I2C1                     = 25,               /**< I2C1 single interrupt vector for all sources */
  INT_SPI0                     = 26,               /**< SPI0 single interrupt vector for all sources */
  INT_SPI1                     = 27,               /**< SPI1 single interrupt vector for all sources */
  INT_UART0                    = 28,               /**< UART0 status and error */
  INT_UART1                    = 29,               /**< UART1 status and error */
  INT_UART2                    = 30,               /**< UART2 status and error */
  INT_ADC0                     = 31,               /**< ADC conversion complete interrupt */
  INT_ACMP0                    = 32,               /**< ACMP0 interrupt */
  INT_FTM0                     = 33,               /**< FTM0 single interrupt vector for all sources */
  INT_FTM1                     = 34,               /**< FTM1 single interrupt vector for all sources */
  INT_FTM2                     = 35,               /**< FTM2 single interrupt vector for all sources */
  INT_RTC                      = 36,               /**< RTC overflow */
  INT_ACMP1                    = 37,               /**< ACMP1 interrupt */
  INT_PIT_CH0                  = 38,               /**< PIT CH0 overflow */
  INT_PIT_CH1                  = 39,               /**< PIT CH1 overflow */
  INT_KBI0                     = 40,               /**< KBI0 interrupt */
  INT_KBI1                     = 41,               /**< KBI1 interrupt */
  INT_Reserved42               = 42,               /**< Reserved interrupt */
  INT_ICS                      = 43,               /**< Clock loss of lock */
  INT_WDOG_EWM                 = 44,               /**< Watchdog timeout */
  INT_PWT                      = 45,               /**< PWT interrupt */
  INT_MSCAN_RX                 = 46,               /**< MSCAN Rx interrupt */
  INT_MSCAN_TX                 = 47                /**< MSCAN Tx, Err and Wake-up interrupt */
} IRQInterruptIndex;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */


/* ----------------------------------------------------------------------------
   -- Peripheral type defines
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_defines Peripheral type defines
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #pragma push
  #pragma anon_unions
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- ACMP
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ACMP_Peripheral ACMP
 * @{
 */

/** ACMP - Peripheral register structure */
typedef struct ACMP_MemMap {
  uint8_t CS;                                      /**< ACMP Control and Status Register, offset: 0x0 */
  uint8_t C0;                                      /**< ACMP Control Register 0, offset: 0x1 */
  uint8_t C1;                                      /**< ACMP Control Register 1, offset: 0x2 */
  uint8_t C2;                                      /**< ACMP Control Register 2, offset: 0x3 */
} volatile *ACMP_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ACMP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ACMP_Register_Accessor_Macros ACMP - Register accessor macros
 * @{
 */


/* ACMP - Register accessors */
#define ACMP_CS_REG(base)                        ((base)->CS)
#define ACMP_C0_REG(base)                        ((base)->C0)
#define ACMP_C1_REG(base)                        ((base)->C1)
#define ACMP_C2_REG(base)                        ((base)->C2)

/*!
 * @}
 */ /* end of group ACMP_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ACMP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ACMP_Register_Masks ACMP Register Masks
 * @{
 */

/* CS Bit Fields */
#define ACMP_CS_ACMOD_MASK                       0x3u
#define ACMP_CS_ACMOD_SHIFT                      0
#define ACMP_CS_ACMOD(x)                         (((uint8_t)(((uint8_t)(x))<<ACMP_CS_ACMOD_SHIFT))&ACMP_CS_ACMOD_MASK)
#define ACMP_CS_ACOPE_MASK                       0x4u
#define ACMP_CS_ACOPE_SHIFT                      2
#define ACMP_CS_ACO_MASK                         0x8u
#define ACMP_CS_ACO_SHIFT                        3
#define ACMP_CS_ACIE_MASK                        0x10u
#define ACMP_CS_ACIE_SHIFT                       4
#define ACMP_CS_ACF_MASK                         0x20u
#define ACMP_CS_ACF_SHIFT                        5
#define ACMP_CS_HYST_MASK                        0x40u
#define ACMP_CS_HYST_SHIFT                       6
#define ACMP_CS_ACE_MASK                         0x80u
#define ACMP_CS_ACE_SHIFT                        7
/* C0 Bit Fields */
#define ACMP_C0_ACNSEL_MASK                      0x3u
#define ACMP_C0_ACNSEL_SHIFT                     0
#define ACMP_C0_ACNSEL(x)                        (((uint8_t)(((uint8_t)(x))<<ACMP_C0_ACNSEL_SHIFT))&ACMP_C0_ACNSEL_MASK)
#define ACMP_C0_ACPSEL_MASK                      0x30u
#define ACMP_C0_ACPSEL_SHIFT                     4
#define ACMP_C0_ACPSEL(x)                        (((uint8_t)(((uint8_t)(x))<<ACMP_C0_ACPSEL_SHIFT))&ACMP_C0_ACPSEL_MASK)
/* C1 Bit Fields */
#define ACMP_C1_DACVAL_MASK                      0x3Fu
#define ACMP_C1_DACVAL_SHIFT                     0
#define ACMP_C1_DACVAL(x)                        (((uint8_t)(((uint8_t)(x))<<ACMP_C1_DACVAL_SHIFT))&ACMP_C1_DACVAL_MASK)
#define ACMP_C1_DACREF_MASK                      0x40u
#define ACMP_C1_DACREF_SHIFT                     6
#define ACMP_C1_DACEN_MASK                       0x80u
#define ACMP_C1_DACEN_SHIFT                      7
/* C2 Bit Fields */
#define ACMP_C2_ACIPE_MASK                       0x7u
#define ACMP_C2_ACIPE_SHIFT                      0
#define ACMP_C2_ACIPE(x)                         (((uint8_t)(((uint8_t)(x))<<ACMP_C2_ACIPE_SHIFT))&ACMP_C2_ACIPE_MASK)

/*!
 * @}
 */ /* end of group ACMP_Register_Masks */


/* ACMP - Peripheral instance base addresses */
/** Peripheral ACMP0 base pointer */
#define ACMP0_BASE_PTR                           ((ACMP_MemMapPtr)0x40073000u)
/** Peripheral ACMP1 base pointer */
#define ACMP1_BASE_PTR                           ((ACMP_MemMapPtr)0x40074000u)
/** Array initializer of ACMP peripheral base pointers */
#define ACMP_BASE_PTRS                           { ACMP0_BASE_PTR, ACMP1_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- ACMP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ACMP_Register_Accessor_Macros ACMP - Register accessor macros
 * @{
 */


/* ACMP - Register instance definitions */
/* ACMP0 */
#define ACMP0_CS                                 ACMP_CS_REG(ACMP0_BASE_PTR)
#define ACMP0_C0                                 ACMP_C0_REG(ACMP0_BASE_PTR)
#define ACMP0_C1                                 ACMP_C1_REG(ACMP0_BASE_PTR)
#define ACMP0_C2                                 ACMP_C2_REG(ACMP0_BASE_PTR)
/* ACMP1 */
#define ACMP1_CS                                 ACMP_CS_REG(ACMP1_BASE_PTR)
#define ACMP1_C0                                 ACMP_C0_REG(ACMP1_BASE_PTR)
#define ACMP1_C1                                 ACMP_C1_REG(ACMP1_BASE_PTR)
#define ACMP1_C2                                 ACMP_C2_REG(ACMP1_BASE_PTR)

/*!
 * @}
 */ /* end of group ACMP_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ACMP_Peripheral */


/* ----------------------------------------------------------------------------
   -- ADC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Peripheral ADC
 * @{
 */

/** ADC - Peripheral register structure */
typedef struct ADC_MemMap {
  uint32_t SC1;                                    /**< Status and Control Register 1, offset: 0x0 */
  uint32_t SC2;                                    /**< Status and Control Register 2, offset: 0x4 */
  uint32_t SC3;                                    /**< Status and Control Register 3, offset: 0x8 */
  uint32_t SC4;                                    /**< Status and Control Register 4, offset: 0xC */
  uint32_t R;                                      /**< Conversion Result Register, offset: 0x10 */
  uint32_t CV;                                     /**< Compare Value Register, offset: 0x14 */
  uint32_t APCTL1;                                 /**< Pin Control 1 Register, offset: 0x18 */
  uint32_t SC5;                                    /**< Status and Control Register 5, offset: 0x1C */
} volatile *ADC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ADC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Accessor_Macros ADC - Register accessor macros
 * @{
 */


/* ADC - Register accessors */
#define ADC_SC1_REG(base)                        ((base)->SC1)
#define ADC_SC2_REG(base)                        ((base)->SC2)
#define ADC_SC3_REG(base)                        ((base)->SC3)
#define ADC_SC4_REG(base)                        ((base)->SC4)
#define ADC_R_REG(base)                          ((base)->R)
#define ADC_CV_REG(base)                         ((base)->CV)
#define ADC_APCTL1_REG(base)                     ((base)->APCTL1)
#define ADC_SC5_REG(base)                        ((base)->SC5)

/*!
 * @}
 */ /* end of group ADC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ADC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Masks ADC Register Masks
 * @{
 */

/* SC1 Bit Fields */
#define ADC_SC1_ADCH_MASK                        0x1Fu
#define ADC_SC1_ADCH_SHIFT                       0
#define ADC_SC1_ADCH(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC1_ADCH_SHIFT))&ADC_SC1_ADCH_MASK)
#define ADC_SC1_ADCO_MASK                        0x20u
#define ADC_SC1_ADCO_SHIFT                       5
#define ADC_SC1_AIEN_MASK                        0x40u
#define ADC_SC1_AIEN_SHIFT                       6
#define ADC_SC1_COCO_MASK                        0x80u
#define ADC_SC1_COCO_SHIFT                       7
/* SC2 Bit Fields */
#define ADC_SC2_REFSEL_MASK                      0x3u
#define ADC_SC2_REFSEL_SHIFT                     0
#define ADC_SC2_REFSEL(x)                        (((uint32_t)(((uint32_t)(x))<<ADC_SC2_REFSEL_SHIFT))&ADC_SC2_REFSEL_MASK)
#define ADC_SC2_FFULL_MASK                       0x4u
#define ADC_SC2_FFULL_SHIFT                      2
#define ADC_SC2_FEMPTY_MASK                      0x8u
#define ADC_SC2_FEMPTY_SHIFT                     3
#define ADC_SC2_ACFGT_MASK                       0x10u
#define ADC_SC2_ACFGT_SHIFT                      4
#define ADC_SC2_ACFE_MASK                        0x20u
#define ADC_SC2_ACFE_SHIFT                       5
#define ADC_SC2_ADTRG_MASK                       0x40u
#define ADC_SC2_ADTRG_SHIFT                      6
#define ADC_SC2_ADACT_MASK                       0x80u
#define ADC_SC2_ADACT_SHIFT                      7
/* SC3 Bit Fields */
#define ADC_SC3_ADICLK_MASK                      0x3u
#define ADC_SC3_ADICLK_SHIFT                     0
#define ADC_SC3_ADICLK(x)                        (((uint32_t)(((uint32_t)(x))<<ADC_SC3_ADICLK_SHIFT))&ADC_SC3_ADICLK_MASK)
#define ADC_SC3_MODE_MASK                        0xCu
#define ADC_SC3_MODE_SHIFT                       2
#define ADC_SC3_MODE(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC3_MODE_SHIFT))&ADC_SC3_MODE_MASK)
#define ADC_SC3_ADLSMP_MASK                      0x10u
#define ADC_SC3_ADLSMP_SHIFT                     4
#define ADC_SC3_ADIV_MASK                        0x60u
#define ADC_SC3_ADIV_SHIFT                       5
#define ADC_SC3_ADIV(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC3_ADIV_SHIFT))&ADC_SC3_ADIV_MASK)
#define ADC_SC3_ADLPC_MASK                       0x80u
#define ADC_SC3_ADLPC_SHIFT                      7
/* SC4 Bit Fields */
#define ADC_SC4_AFDEP_MASK                       0x7u
#define ADC_SC4_AFDEP_SHIFT                      0
#define ADC_SC4_AFDEP(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_SC4_AFDEP_SHIFT))&ADC_SC4_AFDEP_MASK)
#define ADC_SC4_ACFSEL_MASK                      0x20u
#define ADC_SC4_ACFSEL_SHIFT                     5
#define ADC_SC4_ASCANE_MASK                      0x40u
#define ADC_SC4_ASCANE_SHIFT                     6
#define ADC_SC4_HTRGME_MASK                      0x100u
#define ADC_SC4_HTRGME_SHIFT                     8
/* R Bit Fields */
#define ADC_R_ADR_MASK                           0xFFFu
#define ADC_R_ADR_SHIFT                          0
#define ADC_R_ADR(x)                             (((uint32_t)(((uint32_t)(x))<<ADC_R_ADR_SHIFT))&ADC_R_ADR_MASK)
/* CV Bit Fields */
#define ADC_CV_CV_MASK                           0xFFFu
#define ADC_CV_CV_SHIFT                          0
#define ADC_CV_CV(x)                             (((uint32_t)(((uint32_t)(x))<<ADC_CV_CV_SHIFT))&ADC_CV_CV_MASK)
/* APCTL1 Bit Fields */
#define ADC_APCTL1_ADPC_MASK                     0xFFFFu
#define ADC_APCTL1_ADPC_SHIFT                    0
#define ADC_APCTL1_ADPC(x)                       (((uint32_t)(((uint32_t)(x))<<ADC_APCTL1_ADPC_SHIFT))&ADC_APCTL1_ADPC_MASK)
/* SC5 Bit Fields */
#define ADC_SC5_HTRGMASKSEL_MASK                 0x1u
#define ADC_SC5_HTRGMASKSEL_SHIFT                0
#define ADC_SC5_HTRGMASKE_MASK                   0x2u
#define ADC_SC5_HTRGMASKE_SHIFT                  1

/*!
 * @}
 */ /* end of group ADC_Register_Masks */


/* ADC - Peripheral instance base addresses */
/** Peripheral ADC base pointer */
#define ADC_BASE_PTR                             ((ADC_MemMapPtr)0x4003B000u)
/** Array initializer of ADC peripheral base pointers */
#define ADC_BASE_PTRS                            { ADC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- ADC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Accessor_Macros ADC - Register accessor macros
 * @{
 */


/* ADC - Register instance definitions */
/* ADC */
#define ADC_SC1                                  ADC_SC1_REG(ADC_BASE_PTR)
#define ADC_SC2                                  ADC_SC2_REG(ADC_BASE_PTR)
#define ADC_SC3                                  ADC_SC3_REG(ADC_BASE_PTR)
#define ADC_SC4                                  ADC_SC4_REG(ADC_BASE_PTR)
#define ADC_R                                    ADC_R_REG(ADC_BASE_PTR)
#define ADC_CV                                   ADC_CV_REG(ADC_BASE_PTR)
#define ADC_APCTL1                               ADC_APCTL1_REG(ADC_BASE_PTR)
#define ADC_SC5                                  ADC_SC5_REG(ADC_BASE_PTR)

/*!
 * @}
 */ /* end of group ADC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ADC_Peripheral */


/* ----------------------------------------------------------------------------
   -- BP
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BP_Peripheral BP
 * @{
 */

/** BP - Peripheral register structure */
typedef struct BP_MemMap {
  uint32_t CTRL;                                   /**< FlashPatch Control Register, offset: 0x0 */
  uint8_t RESERVED_0[4];
  uint32_t COMP[2];                                /**< FlashPatch Comparator Register 0..FlashPatch Comparator Register 1, array offset: 0x8, array step: 0x4 */
  uint8_t RESERVED_1[4032];
  uint32_t PID4;                                   /**< Peripheral Identification Register 4., offset: 0xFD0 */
  uint32_t PID5;                                   /**< Peripheral Identification Register 5., offset: 0xFD4 */
  uint32_t PID6;                                   /**< Peripheral Identification Register 6., offset: 0xFD8 */
  uint32_t PID7;                                   /**< Peripheral Identification Register 7., offset: 0xFDC */
  uint32_t PID0;                                   /**< Peripheral Identification Register 0., offset: 0xFE0 */
  uint32_t PID1;                                   /**< Peripheral Identification Register 1., offset: 0xFE4 */
  uint32_t PID2;                                   /**< Peripheral Identification Register 2., offset: 0xFE8 */
  uint32_t PID3;                                   /**< Peripheral Identification Register 3., offset: 0xFEC */
  uint32_t CID0;                                   /**< Component Identification Register 0., offset: 0xFF0 */
  uint32_t CID1;                                   /**< Component Identification Register 1., offset: 0xFF4 */
  uint32_t CID2;                                   /**< Component Identification Register 2., offset: 0xFF8 */
  uint32_t CID3;                                   /**< Component Identification Register 3., offset: 0xFFC */
} volatile *BP_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- BP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BP_Register_Accessor_Macros BP - Register accessor macros
 * @{
 */


/* BP - Register accessors */
#define BP_CTRL_REG(base)                        ((base)->CTRL)
#define BP_COMP_REG(base,index)                  ((base)->COMP[index])
#define BP_PID4_REG(base)                        ((base)->PID4)
#define BP_PID5_REG(base)                        ((base)->PID5)
#define BP_PID6_REG(base)                        ((base)->PID6)
#define BP_PID7_REG(base)                        ((base)->PID7)
#define BP_PID0_REG(base)                        ((base)->PID0)
#define BP_PID1_REG(base)                        ((base)->PID1)
#define BP_PID2_REG(base)                        ((base)->PID2)
#define BP_PID3_REG(base)                        ((base)->PID3)
#define BP_CID0_REG(base)                        ((base)->CID0)
#define BP_CID1_REG(base)                        ((base)->CID1)
#define BP_CID2_REG(base)                        ((base)->CID2)
#define BP_CID3_REG(base)                        ((base)->CID3)

/*!
 * @}
 */ /* end of group BP_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- BP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BP_Register_Masks BP Register Masks
 * @{
 */


/*!
 * @}
 */ /* end of group BP_Register_Masks */


/* BP - Peripheral instance base addresses */
/** Peripheral BP base pointer */
#define BP_BASE_PTR                              ((BP_MemMapPtr)0xE0002000u)
/** Array initializer of BP peripheral base pointers */
#define BP_BASE_PTRS                             { BP_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- BP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BP_Register_Accessor_Macros BP - Register accessor macros
 * @{
 */


/* BP - Register instance definitions */
/* BP */
#define BP_CTRL                                  BP_CTRL_REG(BP_BASE_PTR)
#define BP_COMP0                                 BP_COMP_REG(BP_BASE_PTR,0)
#define BP_COMP1                                 BP_COMP_REG(BP_BASE_PTR,1)
#define BP_PID4                                  BP_PID4_REG(BP_BASE_PTR)
#define BP_PID5                                  BP_PID5_REG(BP_BASE_PTR)
#define BP_PID6                                  BP_PID6_REG(BP_BASE_PTR)
#define BP_PID7                                  BP_PID7_REG(BP_BASE_PTR)
#define BP_PID0                                  BP_PID0_REG(BP_BASE_PTR)
#define BP_PID1                                  BP_PID1_REG(BP_BASE_PTR)
#define BP_PID2                                  BP_PID2_REG(BP_BASE_PTR)
#define BP_PID3                                  BP_PID3_REG(BP_BASE_PTR)
#define BP_CID0                                  BP_CID0_REG(BP_BASE_PTR)
#define BP_CID1                                  BP_CID1_REG(BP_BASE_PTR)
#define BP_CID2                                  BP_CID2_REG(BP_BASE_PTR)
#define BP_CID3                                  BP_CID3_REG(BP_BASE_PTR)

/* BP - Register array accessors */
#define BP_COMP(index)                           BP_COMP_REG(BP_BASE_PTR,index)

/*!
 * @}
 */ /* end of group BP_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group BP_Peripheral */


/* ----------------------------------------------------------------------------
   -- CRC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Peripheral CRC
 * @{
 */

/** CRC - Peripheral register structure */
typedef struct CRC_MemMap {
  union {                                          /* offset: 0x0 */
    struct {                                         /* offset: 0x0 */
      uint16_t DATAL;                                  /**< CRC_DATAL register., offset: 0x0 */
      uint16_t DATAH;                                  /**< CRC_DATAH register., offset: 0x2 */
    } ACCESS16BIT;
    uint32_t DATA;                                   /**< CRC Data register, offset: 0x0 */
    struct {                                         /* offset: 0x0 */
      uint8_t DATALL;                                  /**< CRC_DATALL register., offset: 0x0 */
      uint8_t DATALU;                                  /**< CRC_DATALU register., offset: 0x1 */
      uint8_t DATAHL;                                  /**< CRC_DATAHL register., offset: 0x2 */
      uint8_t DATAHU;                                  /**< CRC_DATAHU register., offset: 0x3 */
    } ACCESS8BIT;
  };
  union {                                          /* offset: 0x4 */
    struct {                                         /* offset: 0x4 */
      uint16_t GPOLYL;                                 /**< CRC_GPOLYL register., offset: 0x4 */
      uint16_t GPOLYH;                                 /**< CRC_GPOLYH register., offset: 0x6 */
    } GPOLY_ACCESS16BIT;
    uint32_t GPOLY;                                  /**< CRC Polynomial register, offset: 0x4 */
    struct {                                         /* offset: 0x4 */
      uint8_t GPOLYLL;                                 /**< CRC_GPOLYLL register., offset: 0x4 */
      uint8_t GPOLYLU;                                 /**< CRC_GPOLYLU register., offset: 0x5 */
      uint8_t GPOLYHL;                                 /**< CRC_GPOLYHL register., offset: 0x6 */
      uint8_t GPOLYHU;                                 /**< CRC_GPOLYHU register., offset: 0x7 */
    } GPOLY_ACCESS8BIT;
  };
  union {                                          /* offset: 0x8 */
    uint32_t CTRL;                                   /**< CRC Control register, offset: 0x8 */
    struct {                                         /* offset: 0x8 */
      uint8_t RESERVED_0[3];
      uint8_t CTRLHU;                                  /**< CRC_CTRLHU register., offset: 0xB */
    } CTRL_ACCESS8BIT;
  };
} volatile *CRC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CRC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Register_Accessor_Macros CRC - Register accessor macros
 * @{
 */


/* CRC - Register accessors */
#define CRC_DATAL_REG(base)                      ((base)->ACCESS16BIT.DATAL)
#define CRC_DATAH_REG(base)                      ((base)->ACCESS16BIT.DATAH)
#define CRC_DATA_REG(base)                       ((base)->DATA)
#define CRC_DATALL_REG(base)                     ((base)->ACCESS8BIT.DATALL)
#define CRC_DATALU_REG(base)                     ((base)->ACCESS8BIT.DATALU)
#define CRC_DATAHL_REG(base)                     ((base)->ACCESS8BIT.DATAHL)
#define CRC_DATAHU_REG(base)                     ((base)->ACCESS8BIT.DATAHU)
#define CRC_GPOLYL_REG(base)                     ((base)->GPOLY_ACCESS16BIT.GPOLYL)
#define CRC_GPOLYH_REG(base)                     ((base)->GPOLY_ACCESS16BIT.GPOLYH)
#define CRC_GPOLY_REG(base)                      ((base)->GPOLY)
#define CRC_GPOLYLL_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYLL)
#define CRC_GPOLYLU_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYLU)
#define CRC_GPOLYHL_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYHL)
#define CRC_GPOLYHU_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYHU)
#define CRC_CTRL_REG(base)                       ((base)->CTRL)
#define CRC_CTRLHU_REG(base)                     ((base)->CTRL_ACCESS8BIT.CTRLHU)

/*!
 * @}
 */ /* end of group CRC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- CRC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Register_Masks CRC Register Masks
 * @{
 */

/* DATAL Bit Fields */
#define CRC_DATAL_DATAL_MASK                     0xFFFFu
#define CRC_DATAL_DATAL_SHIFT                    0
#define CRC_DATAL_DATAL(x)                       (((uint16_t)(((uint16_t)(x))<<CRC_DATAL_DATAL_SHIFT))&CRC_DATAL_DATAL_MASK)
/* DATAH Bit Fields */
#define CRC_DATAH_DATAH_MASK                     0xFFFFu
#define CRC_DATAH_DATAH_SHIFT                    0
#define CRC_DATAH_DATAH(x)                       (((uint16_t)(((uint16_t)(x))<<CRC_DATAH_DATAH_SHIFT))&CRC_DATAH_DATAH_MASK)
/* DATA Bit Fields */
#define CRC_DATA_LL_MASK                         0xFFu
#define CRC_DATA_LL_SHIFT                        0
#define CRC_DATA_LL(x)                           (((uint32_t)(((uint32_t)(x))<<CRC_DATA_LL_SHIFT))&CRC_DATA_LL_MASK)
#define CRC_DATA_LU_MASK                         0xFF00u
#define CRC_DATA_LU_SHIFT                        8
#define CRC_DATA_LU(x)                           (((uint32_t)(((uint32_t)(x))<<CRC_DATA_LU_SHIFT))&CRC_DATA_LU_MASK)
#define CRC_DATA_HL_MASK                         0xFF0000u
#define CRC_DATA_HL_SHIFT                        16
#define CRC_DATA_HL(x)                           (((uint32_t)(((uint32_t)(x))<<CRC_DATA_HL_SHIFT))&CRC_DATA_HL_MASK)
#define CRC_DATA_HU_MASK                         0xFF000000u
#define CRC_DATA_HU_SHIFT                        24
#define CRC_DATA_HU(x)                           (((uint32_t)(((uint32_t)(x))<<CRC_DATA_HU_SHIFT))&CRC_DATA_HU_MASK)
/* DATALL Bit Fields */
#define CRC_DATALL_DATALL_MASK                   0xFFu
#define CRC_DATALL_DATALL_SHIFT                  0
#define CRC_DATALL_DATALL(x)                     (((uint8_t)(((uint8_t)(x))<<CRC_DATALL_DATALL_SHIFT))&CRC_DATALL_DATALL_MASK)
/* DATALU Bit Fields */
#define CRC_DATALU_DATALU_MASK                   0xFFu
#define CRC_DATALU_DATALU_SHIFT                  0
#define CRC_DATALU_DATALU(x)                     (((uint8_t)(((uint8_t)(x))<<CRC_DATALU_DATALU_SHIFT))&CRC_DATALU_DATALU_MASK)
/* DATAHL Bit Fields */
#define CRC_DATAHL_DATAHL_MASK                   0xFFu
#define CRC_DATAHL_DATAHL_SHIFT                  0
#define CRC_DATAHL_DATAHL(x)                     (((uint8_t)(((uint8_t)(x))<<CRC_DATAHL_DATAHL_SHIFT))&CRC_DATAHL_DATAHL_MASK)
/* DATAHU Bit Fields */
#define CRC_DATAHU_DATAHU_MASK                   0xFFu
#define CRC_DATAHU_DATAHU_SHIFT                  0
#define CRC_DATAHU_DATAHU(x)                     (((uint8_t)(((uint8_t)(x))<<CRC_DATAHU_DATAHU_SHIFT))&CRC_DATAHU_DATAHU_MASK)
/* GPOLYL Bit Fields */
#define CRC_GPOLYL_GPOLYL_MASK                   0xFFFFu
#define CRC_GPOLYL_GPOLYL_SHIFT                  0
#define CRC_GPOLYL_GPOLYL(x)                     (((uint16_t)(((uint16_t)(x))<<CRC_GPOLYL_GPOLYL_SHIFT))&CRC_GPOLYL_GPOLYL_MASK)
/* GPOLYH Bit Fields */
#define CRC_GPOLYH_GPOLYH_MASK                   0xFFFFu
#define CRC_GPOLYH_GPOLYH_SHIFT                  0
#define CRC_GPOLYH_GPOLYH(x)                     (((uint16_t)(((uint16_t)(x))<<CRC_GPOLYH_GPOLYH_SHIFT))&CRC_GPOLYH_GPOLYH_MASK)
/* GPOLY Bit Fields */
#define CRC_GPOLY_LOW_MASK                       0xFFFFu
#define CRC_GPOLY_LOW_SHIFT                      0
#define CRC_GPOLY_LOW(x)                         (((uint32_t)(((uint32_t)(x))<<CRC_GPOLY_LOW_SHIFT))&CRC_GPOLY_LOW_MASK)
#define CRC_GPOLY_HIGH_MASK                      0xFFFF0000u
#define CRC_GPOLY_HIGH_SHIFT                     16
#define CRC_GPOLY_HIGH(x)                        (((uint32_t)(((uint32_t)(x))<<CRC_GPOLY_HIGH_SHIFT))&CRC_GPOLY_HIGH_MASK)
/* GPOLYLL Bit Fields */
#define CRC_GPOLYLL_GPOLYLL_MASK                 0xFFu
#define CRC_GPOLYLL_GPOLYLL_SHIFT                0
#define CRC_GPOLYLL_GPOLYLL(x)                   (((uint8_t)(((uint8_t)(x))<<CRC_GPOLYLL_GPOLYLL_SHIFT))&CRC_GPOLYLL_GPOLYLL_MASK)
/* GPOLYLU Bit Fields */
#define CRC_GPOLYLU_GPOLYLU_MASK                 0xFFu
#define CRC_GPOLYLU_GPOLYLU_SHIFT                0
#define CRC_GPOLYLU_GPOLYLU(x)                   (((uint8_t)(((uint8_t)(x))<<CRC_GPOLYLU_GPOLYLU_SHIFT))&CRC_GPOLYLU_GPOLYLU_MASK)
/* GPOLYHL Bit Fields */
#define CRC_GPOLYHL_GPOLYHL_MASK                 0xFFu
#define CRC_GPOLYHL_GPOLYHL_SHIFT                0
#define CRC_GPOLYHL_GPOLYHL(x)                   (((uint8_t)(((uint8_t)(x))<<CRC_GPOLYHL_GPOLYHL_SHIFT))&CRC_GPOLYHL_GPOLYHL_MASK)
/* GPOLYHU Bit Fields */
#define CRC_GPOLYHU_GPOLYHU_MASK                 0xFFu
#define CRC_GPOLYHU_GPOLYHU_SHIFT                0
#define CRC_GPOLYHU_GPOLYHU(x)                   (((uint8_t)(((uint8_t)(x))<<CRC_GPOLYHU_GPOLYHU_SHIFT))&CRC_GPOLYHU_GPOLYHU_MASK)
/* CTRL Bit Fields */
#define CRC_CTRL_TCRC_MASK                       0x1000000u
#define CRC_CTRL_TCRC_SHIFT                      24
#define CRC_CTRL_WAS_MASK                        0x2000000u
#define CRC_CTRL_WAS_SHIFT                       25
#define CRC_CTRL_FXOR_MASK                       0x4000000u
#define CRC_CTRL_FXOR_SHIFT                      26
#define CRC_CTRL_TOTR_MASK                       0x30000000u
#define CRC_CTRL_TOTR_SHIFT                      28
#define CRC_CTRL_TOTR(x)                         (((uint32_t)(((uint32_t)(x))<<CRC_CTRL_TOTR_SHIFT))&CRC_CTRL_TOTR_MASK)
#define CRC_CTRL_TOT_MASK                        0xC0000000u
#define CRC_CTRL_TOT_SHIFT                       30
#define CRC_CTRL_TOT(x)                          (((uint32_t)(((uint32_t)(x))<<CRC_CTRL_TOT_SHIFT))&CRC_CTRL_TOT_MASK)
/* CTRLHU Bit Fields */
#define CRC_CTRLHU_TCRC_MASK                     0x1u
#define CRC_CTRLHU_TCRC_SHIFT                    0
#define CRC_CTRLHU_WAS_MASK                      0x2u
#define CRC_CTRLHU_WAS_SHIFT                     1
#define CRC_CTRLHU_FXOR_MASK                     0x4u
#define CRC_CTRLHU_FXOR_SHIFT                    2
#define CRC_CTRLHU_TOTR_MASK                     0x30u
#define CRC_CTRLHU_TOTR_SHIFT                    4
#define CRC_CTRLHU_TOTR(x)                       (((uint8_t)(((uint8_t)(x))<<CRC_CTRLHU_TOTR_SHIFT))&CRC_CTRLHU_TOTR_MASK)
#define CRC_CTRLHU_TOT_MASK                      0xC0u
#define CRC_CTRLHU_TOT_SHIFT                     6
#define CRC_CTRLHU_TOT(x)                        (((uint8_t)(((uint8_t)(x))<<CRC_CTRLHU_TOT_SHIFT))&CRC_CTRLHU_TOT_MASK)

/*!
 * @}
 */ /* end of group CRC_Register_Masks */


/* CRC - Peripheral instance base addresses */
/** Peripheral CRC base pointer */
#define CRC_BASE_PTR                             ((CRC_MemMapPtr)0x40032000u)
/** Array initializer of CRC peripheral base pointers */
#define CRC_BASE_PTRS                            { CRC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- CRC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Register_Accessor_Macros CRC - Register accessor macros
 * @{
 */


/* CRC - Register instance definitions */
/* CRC */
#define CRC_DATA                                 CRC_DATA_REG(CRC_BASE_PTR)
#define CRC_DATAL                                CRC_DATAL_REG(CRC_BASE_PTR)
#define CRC_DATALL                               CRC_DATALL_REG(CRC_BASE_PTR)
#define CRC_DATALU                               CRC_DATALU_REG(CRC_BASE_PTR)
#define CRC_DATAH                                CRC_DATAH_REG(CRC_BASE_PTR)
#define CRC_DATAHL                               CRC_DATAHL_REG(CRC_BASE_PTR)
#define CRC_DATAHU                               CRC_DATAHU_REG(CRC_BASE_PTR)
#define CRC_GPOLY                                CRC_GPOLY_REG(CRC_BASE_PTR)
#define CRC_GPOLYL                               CRC_GPOLYL_REG(CRC_BASE_PTR)
#define CRC_GPOLYLL                              CRC_GPOLYLL_REG(CRC_BASE_PTR)
#define CRC_GPOLYLU                              CRC_GPOLYLU_REG(CRC_BASE_PTR)
#define CRC_GPOLYH                               CRC_GPOLYH_REG(CRC_BASE_PTR)
#define CRC_GPOLYHL                              CRC_GPOLYHL_REG(CRC_BASE_PTR)
#define CRC_GPOLYHU                              CRC_GPOLYHU_REG(CRC_BASE_PTR)
#define CRC_CTRL                                 CRC_CTRL_REG(CRC_BASE_PTR)
#define CRC_CTRLHU                               CRC_CTRLHU_REG(CRC_BASE_PTR)

/*!
 * @}
 */ /* end of group CRC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group CRC_Peripheral */


/* ----------------------------------------------------------------------------
   -- CoreDebug
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CoreDebug_Peripheral CoreDebug
 * @{
 */

/** CoreDebug - Peripheral register structure */
typedef struct CoreDebug_MemMap {
  union {                                          /* offset: 0x0 */
    uint32_t base_DHCSR_Read;                        /**< Debug Halting Control and Status Register, offset: 0x0 */
    uint32_t base_DHCSR_Write;                       /**< Debug Halting Control and Status Register, offset: 0x0 */
  };
  uint32_t base_DCRSR;                             /**< Debug Core Register Selector Register, offset: 0x4 */
  uint32_t base_DCRDR;                             /**< Debug Core Register Data Register, offset: 0x8 */
  uint32_t base_DEMCR;                             /**< Debug Exception and Monitor Control Register, offset: 0xC */
} volatile *CoreDebug_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CoreDebug - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CoreDebug_Register_Accessor_Macros CoreDebug - Register accessor macros
 * @{
 */


/* CoreDebug - Register accessors */
#define CoreDebug_base_DHCSR_Read_REG(base)      ((base)->base_DHCSR_Read)
#define CoreDebug_base_DHCSR_Write_REG(base)     ((base)->base_DHCSR_Write)
#define CoreDebug_base_DCRSR_REG(base)           ((base)->base_DCRSR)
#define CoreDebug_base_DCRDR_REG(base)           ((base)->base_DCRDR)
#define CoreDebug_base_DEMCR_REG(base)           ((base)->base_DEMCR)

/*!
 * @}
 */ /* end of group CoreDebug_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- CoreDebug Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CoreDebug_Register_Masks CoreDebug Register Masks
 * @{
 */


/*!
 * @}
 */ /* end of group CoreDebug_Register_Masks */


/* CoreDebug - Peripheral instance base addresses */
/** Peripheral CoreDebug base pointer */
#define CoreDebug_BASE_PTR                       ((CoreDebug_MemMapPtr)0xE000EDF0u)
/** Array initializer of CoreDebug peripheral base pointers */
#define CoreDebug_BASE_PTRS                      { CoreDebug_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- CoreDebug - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CoreDebug_Register_Accessor_Macros CoreDebug - Register accessor macros
 * @{
 */


/* CoreDebug - Register instance definitions */
/* CoreDebug */
#define DHCSR_Read                               CoreDebug_base_DHCSR_Read_REG(CoreDebug_BASE_PTR)
#define DHCSR_Write                              CoreDebug_base_DHCSR_Write_REG(CoreDebug_BASE_PTR)
#define DCRSR                                    CoreDebug_base_DCRSR_REG(CoreDebug_BASE_PTR)
#define DCRDR                                    CoreDebug_base_DCRDR_REG(CoreDebug_BASE_PTR)
#define DEMCR                                    CoreDebug_base_DEMCR_REG(CoreDebug_BASE_PTR)

/*!
 * @}
 */ /* end of group CoreDebug_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group CoreDebug_Peripheral */


/* ----------------------------------------------------------------------------
   -- DWT
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DWT_Peripheral DWT
 * @{
 */

/** DWT - Peripheral register structure */
typedef struct DWT_MemMap {
  uint32_t CTRL;                                   /**< Control Register, offset: 0x0 */
  uint8_t RESERVED_0[24];
  uint32_t PCSR;                                   /**< Program Counter Sample Register, offset: 0x1C */
  struct {                                         /* offset: 0x20, array step: 0x10 */
    uint32_t COMP;                                   /**< Comparator Register 0..Comparator Register 1, array offset: 0x20, array step: 0x10 */
    uint32_t MASK;                                   /**< Mask Register 0..Mask Register 1, array offset: 0x24, array step: 0x10 */
    uint32_t FUNCTION;                               /**< Function Register 0..Function Register 1, array offset: 0x28, array step: 0x10 */
    uint8_t RESERVED_0[4];
  } COMPARATOR[2];
} volatile *DWT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- DWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DWT_Register_Accessor_Macros DWT - Register accessor macros
 * @{
 */


/* DWT - Register accessors */
#define DWT_CTRL_REG(base)                       ((base)->CTRL)
#define DWT_PCSR_REG(base)                       ((base)->PCSR)
#define DWT_COMP_REG(base,index)                 ((base)->COMPARATOR[index].COMP)
#define DWT_MASK_REG(base,index)                 ((base)->COMPARATOR[index].MASK)
#define DWT_FUNCTION_REG(base,index)             ((base)->COMPARATOR[index].FUNCTION)

/*!
 * @}
 */ /* end of group DWT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- DWT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DWT_Register_Masks DWT Register Masks
 * @{
 */


/*!
 * @}
 */ /* end of group DWT_Register_Masks */


/* DWT - Peripheral instance base addresses */
/** Peripheral DWT base pointer */
#define DWT_BASE_PTR                             ((DWT_MemMapPtr)0xE0001000u)
/** Array initializer of DWT peripheral base pointers */
#define DWT_BASE_PTRS                            { DWT_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- DWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DWT_Register_Accessor_Macros DWT - Register accessor macros
 * @{
 */


/* DWT - Register instance definitions */
/* DWT */
#define DWT_CTRL                                 DWT_CTRL_REG(DWT_BASE_PTR)
#define DWT_PCSR                                 DWT_PCSR_REG(DWT_BASE_PTR)
#define DWT_COMP0                                DWT_COMP_REG(DWT_BASE_PTR,0)
#define DWT_MASK0                                DWT_MASK_REG(DWT_BASE_PTR,0)
#define DWT_FUNCTION0                            DWT_FUNCTION_REG(DWT_BASE_PTR,0)
#define DWT_COMP1                                DWT_COMP_REG(DWT_BASE_PTR,1)
#define DWT_MASK1                                DWT_MASK_REG(DWT_BASE_PTR,1)
#define DWT_FUNCTION1                            DWT_FUNCTION_REG(DWT_BASE_PTR,1)

/* DWT - Register array accessors */
#define DWT_COMP(index)                          DWT_COMP_REG(DWT_BASE_PTR,index)
#define DWT_MASK(index)                          DWT_MASK_REG(DWT_BASE_PTR,index)
#define DWT_FUNCTION(index)                      DWT_FUNCTION_REG(DWT_BASE_PTR,index)

/*!
 * @}
 */ /* end of group DWT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group DWT_Peripheral */


/* ----------------------------------------------------------------------------
   -- FGPIO
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FGPIO_Peripheral FGPIO
 * @{
 */

/** FGPIO - Peripheral register structure */
typedef struct FGPIO_MemMap {
  uint32_t PDOR;                                   /**< Port Data Output Register, offset: 0x0 */
  uint32_t PSOR;                                   /**< Port Set Output Register, offset: 0x4 */
  uint32_t PCOR;                                   /**< Port Clear Output Register, offset: 0x8 */
  uint32_t PTOR;                                   /**< Port Toggle Output Register, offset: 0xC */
  uint32_t PDIR;                                   /**< Port Data Input Register, offset: 0x10 */
  uint32_t PDDR;                                   /**< Port Data Direction Register, offset: 0x14 */
  uint32_t PIDR;                                   /**< Port Input Disable Register, offset: 0x18 */
} volatile *FGPIO_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FGPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FGPIO_Register_Accessor_Macros FGPIO - Register accessor macros
 * @{
 */


/* FGPIO - Register accessors */
#define FGPIO_PDOR_REG(base)                     ((base)->PDOR)
#define FGPIO_PSOR_REG(base)                     ((base)->PSOR)
#define FGPIO_PCOR_REG(base)                     ((base)->PCOR)
#define FGPIO_PTOR_REG(base)                     ((base)->PTOR)
#define FGPIO_PDIR_REG(base)                     ((base)->PDIR)
#define FGPIO_PDDR_REG(base)                     ((base)->PDDR)
#define FGPIO_PIDR_REG(base)                     ((base)->PIDR)

/*!
 * @}
 */ /* end of group FGPIO_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- FGPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FGPIO_Register_Masks FGPIO Register Masks
 * @{
 */

/* PDOR Bit Fields */
#define FGPIO_PDOR_PDO_MASK                      0xFFFFFFFFu
#define FGPIO_PDOR_PDO_SHIFT                     0
#define FGPIO_PDOR_PDO(x)                        (((uint32_t)(((uint32_t)(x))<<FGPIO_PDOR_PDO_SHIFT))&FGPIO_PDOR_PDO_MASK)
/* PSOR Bit Fields */
#define FGPIO_PSOR_PTSO_MASK                     0xFFFFFFFFu
#define FGPIO_PSOR_PTSO_SHIFT                    0
#define FGPIO_PSOR_PTSO(x)                       (((uint32_t)(((uint32_t)(x))<<FGPIO_PSOR_PTSO_SHIFT))&FGPIO_PSOR_PTSO_MASK)
/* PCOR Bit Fields */
#define FGPIO_PCOR_PTCO_MASK                     0xFFFFFFFFu
#define FGPIO_PCOR_PTCO_SHIFT                    0
#define FGPIO_PCOR_PTCO(x)                       (((uint32_t)(((uint32_t)(x))<<FGPIO_PCOR_PTCO_SHIFT))&FGPIO_PCOR_PTCO_MASK)
/* PTOR Bit Fields */
#define FGPIO_PTOR_PTTO_MASK                     0xFFFFFFFFu
#define FGPIO_PTOR_PTTO_SHIFT                    0
#define FGPIO_PTOR_PTTO(x)                       (((uint32_t)(((uint32_t)(x))<<FGPIO_PTOR_PTTO_SHIFT))&FGPIO_PTOR_PTTO_MASK)
/* PDIR Bit Fields */
#define FGPIO_PDIR_PDI_MASK                      0xFFFFFFFFu
#define FGPIO_PDIR_PDI_SHIFT                     0
#define FGPIO_PDIR_PDI(x)                        (((uint32_t)(((uint32_t)(x))<<FGPIO_PDIR_PDI_SHIFT))&FGPIO_PDIR_PDI_MASK)
/* PDDR Bit Fields */
#define FGPIO_PDDR_PDD_MASK                      0xFFFFFFFFu
#define FGPIO_PDDR_PDD_SHIFT                     0
#define FGPIO_PDDR_PDD(x)                        (((uint32_t)(((uint32_t)(x))<<FGPIO_PDDR_PDD_SHIFT))&FGPIO_PDDR_PDD_MASK)
/* PIDR Bit Fields */
#define FGPIO_PIDR_PID_MASK                      0xFFFFFFFFu
#define FGPIO_PIDR_PID_SHIFT                     0
#define FGPIO_PIDR_PID(x)                        (((uint32_t)(((uint32_t)(x))<<FGPIO_PIDR_PID_SHIFT))&FGPIO_PIDR_PID_MASK)

/*!
 * @}
 */ /* end of group FGPIO_Register_Masks */


/* FGPIO - Peripheral instance base addresses */
/** Peripheral FGPIOA base pointer */
#define FGPIOA_BASE_PTR                          ((FGPIO_MemMapPtr)0xF8000000u)
/** Peripheral FGPIOB base pointer */
#define FGPIOB_BASE_PTR                          ((FGPIO_MemMapPtr)0xF8000040u)
/** Peripheral FGPIOC base pointer */
#define FGPIOC_BASE_PTR                          ((FGPIO_MemMapPtr)0xF8000080u)
/** Array initializer of FGPIO peripheral base pointers */
#define FGPIO_BASE_PTRS                          { FGPIOA_BASE_PTR, FGPIOB_BASE_PTR, FGPIOC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- FGPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FGPIO_Register_Accessor_Macros FGPIO - Register accessor macros
 * @{
 */


/* FGPIO - Register instance definitions */
/* FGPIOA */
#define FGPIOA_PDOR                              FGPIO_PDOR_REG(FGPIOA_BASE_PTR)
#define FGPIOA_PSOR                              FGPIO_PSOR_REG(FGPIOA_BASE_PTR)
#define FGPIOA_PCOR                              FGPIO_PCOR_REG(FGPIOA_BASE_PTR)
#define FGPIOA_PTOR                              FGPIO_PTOR_REG(FGPIOA_BASE_PTR)
#define FGPIOA_PDIR                              FGPIO_PDIR_REG(FGPIOA_BASE_PTR)
#define FGPIOA_PDDR                              FGPIO_PDDR_REG(FGPIOA_BASE_PTR)
#define FGPIOA_PIDR                              FGPIO_PIDR_REG(FGPIOA_BASE_PTR)
/* FGPIOB */
#define FGPIOB_PDOR                              FGPIO_PDOR_REG(FGPIOB_BASE_PTR)
#define FGPIOB_PSOR                              FGPIO_PSOR_REG(FGPIOB_BASE_PTR)
#define FGPIOB_PCOR                              FGPIO_PCOR_REG(FGPIOB_BASE_PTR)
#define FGPIOB_PTOR                              FGPIO_PTOR_REG(FGPIOB_BASE_PTR)
#define FGPIOB_PDIR                              FGPIO_PDIR_REG(FGPIOB_BASE_PTR)
#define FGPIOB_PDDR                              FGPIO_PDDR_REG(FGPIOB_BASE_PTR)
#define FGPIOB_PIDR                              FGPIO_PIDR_REG(FGPIOB_BASE_PTR)
/* FGPIOC */
#define FGPIOC_PDOR                              FGPIO_PDOR_REG(FGPIOC_BASE_PTR)
#define FGPIOC_PSOR                              FGPIO_PSOR_REG(FGPIOC_BASE_PTR)
#define FGPIOC_PCOR                              FGPIO_PCOR_REG(FGPIOC_BASE_PTR)
#define FGPIOC_PTOR                              FGPIO_PTOR_REG(FGPIOC_BASE_PTR)
#define FGPIOC_PDIR                              FGPIO_PDIR_REG(FGPIOC_BASE_PTR)
#define FGPIOC_PDDR                              FGPIO_PDDR_REG(FGPIOC_BASE_PTR)
#define FGPIOC_PIDR                              FGPIO_PIDR_REG(FGPIOC_BASE_PTR)

/*!
 * @}
 */ /* end of group FGPIO_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group FGPIO_Peripheral */


/* ----------------------------------------------------------------------------
   -- FTM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Peripheral FTM
 * @{
 */

/** FTM - Peripheral register structure */
typedef struct FTM_MemMap {
  uint32_t SC;                                     /**< Status And Control, offset: 0x0 */
  uint32_t CNT;                                    /**< Counter, offset: 0x4 */
  uint32_t MOD;                                    /**< Modulo, offset: 0x8 */
  struct {                                         /* offset: 0xC, array step: 0x8 */
    uint32_t CnSC;                                   /**< Channel (n) Status And Control, array offset: 0xC, array step: 0x8 */
    uint32_t CnV;                                    /**< Channel (n) Value, array offset: 0x10, array step: 0x8 */
  } CONTROLS[6];
  uint8_t RESERVED_0[16];
  uint32_t CNTIN;                                  /**< Counter Initial Value, offset: 0x4C */
  uint32_t STATUS;                                 /**< Capture And Compare Status, offset: 0x50 */
  uint32_t MODE;                                   /**< Features Mode Selection, offset: 0x54 */
  uint32_t SYNC;                                   /**< Synchronization, offset: 0x58 */
  uint32_t OUTINIT;                                /**< Initial State For Channels Output, offset: 0x5C */
  uint32_t OUTMASK;                                /**< Output Mask, offset: 0x60 */
  uint32_t COMBINE;                                /**< Function For Linked Channels, offset: 0x64 */
  uint32_t DEADTIME;                               /**< Deadtime Insertion Control, offset: 0x68 */
  uint32_t EXTTRIG;                                /**< FTM External Trigger, offset: 0x6C */
  uint32_t POL;                                    /**< Channels Polarity, offset: 0x70 */
  uint32_t FMS;                                    /**< Fault Mode Status, offset: 0x74 */
  uint32_t FILTER;                                 /**< Input Capture Filter Control, offset: 0x78 */
  uint32_t FLTCTRL;                                /**< Fault Control, offset: 0x7C */
  uint8_t RESERVED_1[4];
  uint32_t CONF;                                   /**< Configuration, offset: 0x84 */
  uint32_t FLTPOL;                                 /**< FTM Fault Input Polarity, offset: 0x88 */
  uint32_t SYNCONF;                                /**< Synchronization Configuration, offset: 0x8C */
  uint32_t INVCTRL;                                /**< FTM Inverting Control, offset: 0x90 */
  uint32_t SWOCTRL;                                /**< FTM Software Output Control, offset: 0x94 */
  uint32_t PWMLOAD;                                /**< FTM PWM Load, offset: 0x98 */
} volatile *FTM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FTM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Register_Accessor_Macros FTM - Register accessor macros
 * @{
 */


/* FTM - Register accessors */
#define FTM_SC_REG(base)                         ((base)->SC)
#define FTM_CNT_REG(base)                        ((base)->CNT)
#define FTM_MOD_REG(base)                        ((base)->MOD)
#define FTM_CnSC_REG(base,index)                 ((base)->CONTROLS[index].CnSC)
#define FTM_CnV_REG(base,index)                  ((base)->CONTROLS[index].CnV)
#define FTM_CNTIN_REG(base)                      ((base)->CNTIN)
#define FTM_STATUS_REG(base)                     ((base)->STATUS)
#define FTM_MODE_REG(base)                       ((base)->MODE)
#define FTM_SYNC_REG(base)                       ((base)->SYNC)
#define FTM_OUTINIT_REG(base)                    ((base)->OUTINIT)
#define FTM_OUTMASK_REG(base)                    ((base)->OUTMASK)
#define FTM_COMBINE_REG(base)                    ((base)->COMBINE)
#define FTM_DEADTIME_REG(base)                   ((base)->DEADTIME)
#define FTM_EXTTRIG_REG(base)                    ((base)->EXTTRIG)
#define FTM_POL_REG(base)                        ((base)->POL)
#define FTM_FMS_REG(base)                        ((base)->FMS)
#define FTM_FILTER_REG(base)                     ((base)->FILTER)
#define FTM_FLTCTRL_REG(base)                    ((base)->FLTCTRL)
#define FTM_CONF_REG(base)                       ((base)->CONF)
#define FTM_FLTPOL_REG(base)                     ((base)->FLTPOL)
#define FTM_SYNCONF_REG(base)                    ((base)->SYNCONF)
#define FTM_INVCTRL_REG(base)                    ((base)->INVCTRL)
#define FTM_SWOCTRL_REG(base)                    ((base)->SWOCTRL)
#define FTM_PWMLOAD_REG(base)                    ((base)->PWMLOAD)

/*!
 * @}
 */ /* end of group FTM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- FTM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Register_Masks FTM Register Masks
 * @{
 */

/* SC Bit Fields */
#define FTM_SC_PS_MASK                           0x7u
#define FTM_SC_PS_SHIFT                          0
#define FTM_SC_PS(x)                             (((uint32_t)(((uint32_t)(x))<<FTM_SC_PS_SHIFT))&FTM_SC_PS_MASK)
#define FTM_SC_CLKS_MASK                         0x18u
#define FTM_SC_CLKS_SHIFT                        3
#define FTM_SC_CLKS(x)                           (((uint32_t)(((uint32_t)(x))<<FTM_SC_CLKS_SHIFT))&FTM_SC_CLKS_MASK)
#define FTM_SC_CPWMS_MASK                        0x20u
#define FTM_SC_CPWMS_SHIFT                       5
#define FTM_SC_TOIE_MASK                         0x40u
#define FTM_SC_TOIE_SHIFT                        6
#define FTM_SC_TOF_MASK                          0x80u
#define FTM_SC_TOF_SHIFT                         7
/* CNT Bit Fields */
#define FTM_CNT_COUNT_MASK                       0xFFFFu
#define FTM_CNT_COUNT_SHIFT                      0
#define FTM_CNT_COUNT(x)                         (((uint32_t)(((uint32_t)(x))<<FTM_CNT_COUNT_SHIFT))&FTM_CNT_COUNT_MASK)
/* MOD Bit Fields */
#define FTM_MOD_MOD_MASK                         0xFFFFu
#define FTM_MOD_MOD_SHIFT                        0
#define FTM_MOD_MOD(x)                           (((uint32_t)(((uint32_t)(x))<<FTM_MOD_MOD_SHIFT))&FTM_MOD_MOD_MASK)
/* CnSC Bit Fields */
#define FTM_CnSC_ELSA_MASK                       0x4u
#define FTM_CnSC_ELSA_SHIFT                      2
#define FTM_CnSC_ELSB_MASK                       0x8u
#define FTM_CnSC_ELSB_SHIFT                      3
#define FTM_CnSC_MSA_MASK                        0x10u
#define FTM_CnSC_MSA_SHIFT                       4
#define FTM_CnSC_MSB_MASK                        0x20u
#define FTM_CnSC_MSB_SHIFT                       5
#define FTM_CnSC_CHIE_MASK                       0x40u
#define FTM_CnSC_CHIE_SHIFT                      6
#define FTM_CnSC_CHF_MASK                        0x80u
#define FTM_CnSC_CHF_SHIFT                       7
/* CnV Bit Fields */
#define FTM_CnV_VAL_MASK                         0xFFFFu
#define FTM_CnV_VAL_SHIFT                        0
#define FTM_CnV_VAL(x)                           (((uint32_t)(((uint32_t)(x))<<FTM_CnV_VAL_SHIFT))&FTM_CnV_VAL_MASK)
/* CNTIN Bit Fields */
#define FTM_CNTIN_INIT_MASK                      0xFFFFu
#define FTM_CNTIN_INIT_SHIFT                     0
#define FTM_CNTIN_INIT(x)                        (((uint32_t)(((uint32_t)(x))<<FTM_CNTIN_INIT_SHIFT))&FTM_CNTIN_INIT_MASK)
/* STATUS Bit Fields */
#define FTM_STATUS_CH0F_MASK                     0x1u
#define FTM_STATUS_CH0F_SHIFT                    0
#define FTM_STATUS_CH1F_MASK                     0x2u
#define FTM_STATUS_CH1F_SHIFT                    1
#define FTM_STATUS_CH2F_MASK                     0x4u
#define FTM_STATUS_CH2F_SHIFT                    2
#define FTM_STATUS_CH3F_MASK                     0x8u
#define FTM_STATUS_CH3F_SHIFT                    3
#define FTM_STATUS_CH4F_MASK                     0x10u
#define FTM_STATUS_CH4F_SHIFT                    4
#define FTM_STATUS_CH5F_MASK                     0x20u
#define FTM_STATUS_CH5F_SHIFT                    5
#define FTM_STATUS_CH6F_MASK                     0x40u
#define FTM_STATUS_CH6F_SHIFT                    6
#define FTM_STATUS_CH7F_MASK                     0x80u
#define FTM_STATUS_CH7F_SHIFT                    7
/* MODE Bit Fields */
#define FTM_MODE_FTMEN_MASK                      0x1u
#define FTM_MODE_FTMEN_SHIFT                     0
#define FTM_MODE_INIT_MASK                       0x2u
#define FTM_MODE_INIT_SHIFT                      1
#define FTM_MODE_WPDIS_MASK                      0x4u
#define FTM_MODE_WPDIS_SHIFT                     2
#define FTM_MODE_PWMSYNC_MASK                    0x8u
#define FTM_MODE_PWMSYNC_SHIFT                   3
#define FTM_MODE_CAPTEST_MASK                    0x10u
#define FTM_MODE_CAPTEST_SHIFT                   4
#define FTM_MODE_FAULTM_MASK                     0x60u
#define FTM_MODE_FAULTM_SHIFT                    5
#define FTM_MODE_FAULTM(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_MODE_FAULTM_SHIFT))&FTM_MODE_FAULTM_MASK)
#define FTM_MODE_FAULTIE_MASK                    0x80u
#define FTM_MODE_FAULTIE_SHIFT                   7
/* SYNC Bit Fields */
#define FTM_SYNC_CNTMIN_MASK                     0x1u
#define FTM_SYNC_CNTMIN_SHIFT                    0
#define FTM_SYNC_CNTMAX_MASK                     0x2u
#define FTM_SYNC_CNTMAX_SHIFT                    1
#define FTM_SYNC_REINIT_MASK                     0x4u
#define FTM_SYNC_REINIT_SHIFT                    2
#define FTM_SYNC_SYNCHOM_MASK                    0x8u
#define FTM_SYNC_SYNCHOM_SHIFT                   3
#define FTM_SYNC_TRIG0_MASK                      0x10u
#define FTM_SYNC_TRIG0_SHIFT                     4
#define FTM_SYNC_TRIG1_MASK                      0x20u
#define FTM_SYNC_TRIG1_SHIFT                     5
#define FTM_SYNC_TRIG2_MASK                      0x40u
#define FTM_SYNC_TRIG2_SHIFT                     6
#define FTM_SYNC_SWSYNC_MASK                     0x80u
#define FTM_SYNC_SWSYNC_SHIFT                    7
/* OUTINIT Bit Fields */
#define FTM_OUTINIT_CH0OI_MASK                   0x1u
#define FTM_OUTINIT_CH0OI_SHIFT                  0
#define FTM_OUTINIT_CH1OI_MASK                   0x2u
#define FTM_OUTINIT_CH1OI_SHIFT                  1
#define FTM_OUTINIT_CH2OI_MASK                   0x4u
#define FTM_OUTINIT_CH2OI_SHIFT                  2
#define FTM_OUTINIT_CH3OI_MASK                   0x8u
#define FTM_OUTINIT_CH3OI_SHIFT                  3
#define FTM_OUTINIT_CH4OI_MASK                   0x10u
#define FTM_OUTINIT_CH4OI_SHIFT                  4
#define FTM_OUTINIT_CH5OI_MASK                   0x20u
#define FTM_OUTINIT_CH5OI_SHIFT                  5
#define FTM_OUTINIT_CH6OI_MASK                   0x40u
#define FTM_OUTINIT_CH6OI_SHIFT                  6
#define FTM_OUTINIT_CH7OI_MASK                   0x80u
#define FTM_OUTINIT_CH7OI_SHIFT                  7
/* OUTMASK Bit Fields */
#define FTM_OUTMASK_CH0OM_MASK                   0x1u
#define FTM_OUTMASK_CH0OM_SHIFT                  0
#define FTM_OUTMASK_CH1OM_MASK                   0x2u
#define FTM_OUTMASK_CH1OM_SHIFT                  1
#define FTM_OUTMASK_CH2OM_MASK                   0x4u
#define FTM_OUTMASK_CH2OM_SHIFT                  2
#define FTM_OUTMASK_CH3OM_MASK                   0x8u
#define FTM_OUTMASK_CH3OM_SHIFT                  3
#define FTM_OUTMASK_CH4OM_MASK                   0x10u
#define FTM_OUTMASK_CH4OM_SHIFT                  4
#define FTM_OUTMASK_CH5OM_MASK                   0x20u
#define FTM_OUTMASK_CH5OM_SHIFT                  5
#define FTM_OUTMASK_CH6OM_MASK                   0x40u
#define FTM_OUTMASK_CH6OM_SHIFT                  6
#define FTM_OUTMASK_CH7OM_MASK                   0x80u
#define FTM_OUTMASK_CH7OM_SHIFT                  7
/* COMBINE Bit Fields */
#define FTM_COMBINE_COMBINE0_MASK                0x1u
#define FTM_COMBINE_COMBINE0_SHIFT               0
#define FTM_COMBINE_COMP0_MASK                   0x2u
#define FTM_COMBINE_COMP0_SHIFT                  1
#define FTM_COMBINE_DECAPEN0_MASK                0x4u
#define FTM_COMBINE_DECAPEN0_SHIFT               2
#define FTM_COMBINE_DECAP0_MASK                  0x8u
#define FTM_COMBINE_DECAP0_SHIFT                 3
#define FTM_COMBINE_DTEN0_MASK                   0x10u
#define FTM_COMBINE_DTEN0_SHIFT                  4
#define FTM_COMBINE_SYNCEN0_MASK                 0x20u
#define FTM_COMBINE_SYNCEN0_SHIFT                5
#define FTM_COMBINE_FAULTEN0_MASK                0x40u
#define FTM_COMBINE_FAULTEN0_SHIFT               6
#define FTM_COMBINE_COMBINE1_MASK                0x100u
#define FTM_COMBINE_COMBINE1_SHIFT               8
#define FTM_COMBINE_COMP1_MASK                   0x200u
#define FTM_COMBINE_COMP1_SHIFT                  9
#define FTM_COMBINE_DECAPEN1_MASK                0x400u
#define FTM_COMBINE_DECAPEN1_SHIFT               10
#define FTM_COMBINE_DECAP1_MASK                  0x800u
#define FTM_COMBINE_DECAP1_SHIFT                 11
#define FTM_COMBINE_DTEN1_MASK                   0x1000u
#define FTM_COMBINE_DTEN1_SHIFT                  12
#define FTM_COMBINE_SYNCEN1_MASK                 0x2000u
#define FTM_COMBINE_SYNCEN1_SHIFT                13
#define FTM_COMBINE_FAULTEN1_MASK                0x4000u
#define FTM_COMBINE_FAULTEN1_SHIFT               14
#define FTM_COMBINE_COMBINE2_MASK                0x10000u
#define FTM_COMBINE_COMBINE2_SHIFT               16
#define FTM_COMBINE_COMP2_MASK                   0x20000u
#define FTM_COMBINE_COMP2_SHIFT                  17
#define FTM_COMBINE_DECAPEN2_MASK                0x40000u
#define FTM_COMBINE_DECAPEN2_SHIFT               18
#define FTM_COMBINE_DECAP2_MASK                  0x80000u
#define FTM_COMBINE_DECAP2_SHIFT                 19
#define FTM_COMBINE_DTEN2_MASK                   0x100000u
#define FTM_COMBINE_DTEN2_SHIFT                  20
#define FTM_COMBINE_SYNCEN2_MASK                 0x200000u
#define FTM_COMBINE_SYNCEN2_SHIFT                21
#define FTM_COMBINE_FAULTEN2_MASK                0x400000u
#define FTM_COMBINE_FAULTEN2_SHIFT               22
#define FTM_COMBINE_COMBINE3_MASK                0x1000000u
#define FTM_COMBINE_COMBINE3_SHIFT               24
#define FTM_COMBINE_COMP3_MASK                   0x2000000u
#define FTM_COMBINE_COMP3_SHIFT                  25
#define FTM_COMBINE_DECAPEN3_MASK                0x4000000u
#define FTM_COMBINE_DECAPEN3_SHIFT               26
#define FTM_COMBINE_DECAP3_MASK                  0x8000000u
#define FTM_COMBINE_DECAP3_SHIFT                 27
#define FTM_COMBINE_DTEN3_MASK                   0x10000000u
#define FTM_COMBINE_DTEN3_SHIFT                  28
#define FTM_COMBINE_SYNCEN3_MASK                 0x20000000u
#define FTM_COMBINE_SYNCEN3_SHIFT                29
#define FTM_COMBINE_FAULTEN3_MASK                0x40000000u
#define FTM_COMBINE_FAULTEN3_SHIFT               30
/* DEADTIME Bit Fields */
#define FTM_DEADTIME_DTVAL_MASK                  0x3Fu
#define FTM_DEADTIME_DTVAL_SHIFT                 0
#define FTM_DEADTIME_DTVAL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_DEADTIME_DTVAL_SHIFT))&FTM_DEADTIME_DTVAL_MASK)
#define FTM_DEADTIME_DTPS_MASK                   0xC0u
#define FTM_DEADTIME_DTPS_SHIFT                  6
#define FTM_DEADTIME_DTPS(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_DEADTIME_DTPS_SHIFT))&FTM_DEADTIME_DTPS_MASK)
/* EXTTRIG Bit Fields */
#define FTM_EXTTRIG_CH2TRIG_MASK                 0x1u
#define FTM_EXTTRIG_CH2TRIG_SHIFT                0
#define FTM_EXTTRIG_CH3TRIG_MASK                 0x2u
#define FTM_EXTTRIG_CH3TRIG_SHIFT                1
#define FTM_EXTTRIG_CH4TRIG_MASK                 0x4u
#define FTM_EXTTRIG_CH4TRIG_SHIFT                2
#define FTM_EXTTRIG_CH5TRIG_MASK                 0x8u
#define FTM_EXTTRIG_CH5TRIG_SHIFT                3
#define FTM_EXTTRIG_CH0TRIG_MASK                 0x10u
#define FTM_EXTTRIG_CH0TRIG_SHIFT                4
#define FTM_EXTTRIG_CH1TRIG_MASK                 0x20u
#define FTM_EXTTRIG_CH1TRIG_SHIFT                5
#define FTM_EXTTRIG_INITTRIGEN_MASK              0x40u
#define FTM_EXTTRIG_INITTRIGEN_SHIFT             6
#define FTM_EXTTRIG_TRIGF_MASK                   0x80u
#define FTM_EXTTRIG_TRIGF_SHIFT                  7
/* POL Bit Fields */
#define FTM_POL_POL0_MASK                        0x1u
#define FTM_POL_POL0_SHIFT                       0
#define FTM_POL_POL1_MASK                        0x2u
#define FTM_POL_POL1_SHIFT                       1
#define FTM_POL_POL2_MASK                        0x4u
#define FTM_POL_POL2_SHIFT                       2
#define FTM_POL_POL3_MASK                        0x8u
#define FTM_POL_POL3_SHIFT                       3
#define FTM_POL_POL4_MASK                        0x10u
#define FTM_POL_POL4_SHIFT                       4
#define FTM_POL_POL5_MASK                        0x20u
#define FTM_POL_POL5_SHIFT                       5
#define FTM_POL_POL6_MASK                        0x40u
#define FTM_POL_POL6_SHIFT                       6
#define FTM_POL_POL7_MASK                        0x80u
#define FTM_POL_POL7_SHIFT                       7
/* FMS Bit Fields */
#define FTM_FMS_FAULTF0_MASK                     0x1u
#define FTM_FMS_FAULTF0_SHIFT                    0
#define FTM_FMS_FAULTF1_MASK                     0x2u
#define FTM_FMS_FAULTF1_SHIFT                    1
#define FTM_FMS_FAULTF2_MASK                     0x4u
#define FTM_FMS_FAULTF2_SHIFT                    2
#define FTM_FMS_FAULTF3_MASK                     0x8u
#define FTM_FMS_FAULTF3_SHIFT                    3
#define FTM_FMS_FAULTIN_MASK                     0x20u
#define FTM_FMS_FAULTIN_SHIFT                    5
#define FTM_FMS_WPEN_MASK                        0x40u
#define FTM_FMS_WPEN_SHIFT                       6
#define FTM_FMS_FAULTF_MASK                      0x80u
#define FTM_FMS_FAULTF_SHIFT                     7
/* FILTER Bit Fields */
#define FTM_FILTER_CH0FVAL_MASK                  0xFu
#define FTM_FILTER_CH0FVAL_SHIFT                 0
#define FTM_FILTER_CH0FVAL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_FILTER_CH0FVAL_SHIFT))&FTM_FILTER_CH0FVAL_MASK)
#define FTM_FILTER_CH1FVAL_MASK                  0xF0u
#define FTM_FILTER_CH1FVAL_SHIFT                 4
#define FTM_FILTER_CH1FVAL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_FILTER_CH1FVAL_SHIFT))&FTM_FILTER_CH1FVAL_MASK)
#define FTM_FILTER_CH2FVAL_MASK                  0xF00u
#define FTM_FILTER_CH2FVAL_SHIFT                 8
#define FTM_FILTER_CH2FVAL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_FILTER_CH2FVAL_SHIFT))&FTM_FILTER_CH2FVAL_MASK)
#define FTM_FILTER_CH3FVAL_MASK                  0xF000u
#define FTM_FILTER_CH3FVAL_SHIFT                 12
#define FTM_FILTER_CH3FVAL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_FILTER_CH3FVAL_SHIFT))&FTM_FILTER_CH3FVAL_MASK)
/* FLTCTRL Bit Fields */
#define FTM_FLTCTRL_FAULT0EN_MASK                0x1u
#define FTM_FLTCTRL_FAULT0EN_SHIFT               0
#define FTM_FLTCTRL_FAULT1EN_MASK                0x2u
#define FTM_FLTCTRL_FAULT1EN_SHIFT               1
#define FTM_FLTCTRL_FAULT2EN_MASK                0x4u
#define FTM_FLTCTRL_FAULT2EN_SHIFT               2
#define FTM_FLTCTRL_FAULT3EN_MASK                0x8u
#define FTM_FLTCTRL_FAULT3EN_SHIFT               3
#define FTM_FLTCTRL_FFLTR0EN_MASK                0x10u
#define FTM_FLTCTRL_FFLTR0EN_SHIFT               4
#define FTM_FLTCTRL_FFLTR1EN_MASK                0x20u
#define FTM_FLTCTRL_FFLTR1EN_SHIFT               5
#define FTM_FLTCTRL_FFLTR2EN_MASK                0x40u
#define FTM_FLTCTRL_FFLTR2EN_SHIFT               6
#define FTM_FLTCTRL_FFLTR3EN_MASK                0x80u
#define FTM_FLTCTRL_FFLTR3EN_SHIFT               7
#define FTM_FLTCTRL_FFVAL_MASK                   0xF00u
#define FTM_FLTCTRL_FFVAL_SHIFT                  8
#define FTM_FLTCTRL_FFVAL(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_FLTCTRL_FFVAL_SHIFT))&FTM_FLTCTRL_FFVAL_MASK)
/* CONF Bit Fields */
#define FTM_CONF_NUMTOF_MASK                     0x1Fu
#define FTM_CONF_NUMTOF_SHIFT                    0
#define FTM_CONF_NUMTOF(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_CONF_NUMTOF_SHIFT))&FTM_CONF_NUMTOF_MASK)
#define FTM_CONF_BDMMODE_MASK                    0xC0u
#define FTM_CONF_BDMMODE_SHIFT                   6
#define FTM_CONF_BDMMODE(x)                      (((uint32_t)(((uint32_t)(x))<<FTM_CONF_BDMMODE_SHIFT))&FTM_CONF_BDMMODE_MASK)
#define FTM_CONF_GTBEEN_MASK                     0x200u
#define FTM_CONF_GTBEEN_SHIFT                    9
#define FTM_CONF_GTBEOUT_MASK                    0x400u
#define FTM_CONF_GTBEOUT_SHIFT                   10
/* FLTPOL Bit Fields */
#define FTM_FLTPOL_FLT0POL_MASK                  0x1u
#define FTM_FLTPOL_FLT0POL_SHIFT                 0
#define FTM_FLTPOL_FLT1POL_MASK                  0x2u
#define FTM_FLTPOL_FLT1POL_SHIFT                 1
#define FTM_FLTPOL_FLT2POL_MASK                  0x4u
#define FTM_FLTPOL_FLT2POL_SHIFT                 2
#define FTM_FLTPOL_FLT3POL_MASK                  0x8u
#define FTM_FLTPOL_FLT3POL_SHIFT                 3
/* SYNCONF Bit Fields */
#define FTM_SYNCONF_HWTRIGMODE_MASK              0x1u
#define FTM_SYNCONF_HWTRIGMODE_SHIFT             0
#define FTM_SYNCONF_CNTINC_MASK                  0x4u
#define FTM_SYNCONF_CNTINC_SHIFT                 2
#define FTM_SYNCONF_INVC_MASK                    0x10u
#define FTM_SYNCONF_INVC_SHIFT                   4
#define FTM_SYNCONF_SWOC_MASK                    0x20u
#define FTM_SYNCONF_SWOC_SHIFT                   5
#define FTM_SYNCONF_SYNCMODE_MASK                0x80u
#define FTM_SYNCONF_SYNCMODE_SHIFT               7
#define FTM_SYNCONF_SWRSTCNT_MASK                0x100u
#define FTM_SYNCONF_SWRSTCNT_SHIFT               8
#define FTM_SYNCONF_SWWRBUF_MASK                 0x200u
#define FTM_SYNCONF_SWWRBUF_SHIFT                9
#define FTM_SYNCONF_SWOM_MASK                    0x400u
#define FTM_SYNCONF_SWOM_SHIFT                   10
#define FTM_SYNCONF_SWINVC_MASK                  0x800u
#define FTM_SYNCONF_SWINVC_SHIFT                 11
#define FTM_SYNCONF_SWSOC_MASK                   0x1000u
#define FTM_SYNCONF_SWSOC_SHIFT                  12
#define FTM_SYNCONF_HWRSTCNT_MASK                0x10000u
#define FTM_SYNCONF_HWRSTCNT_SHIFT               16
#define FTM_SYNCONF_HWWRBUF_MASK                 0x20000u
#define FTM_SYNCONF_HWWRBUF_SHIFT                17
#define FTM_SYNCONF_HWOM_MASK                    0x40000u
#define FTM_SYNCONF_HWOM_SHIFT                   18
#define FTM_SYNCONF_HWINVC_MASK                  0x80000u
#define FTM_SYNCONF_HWINVC_SHIFT                 19
#define FTM_SYNCONF_HWSOC_MASK                   0x100000u
#define FTM_SYNCONF_HWSOC_SHIFT                  20
/* INVCTRL Bit Fields */
#define FTM_INVCTRL_INV0EN_MASK                  0x1u
#define FTM_INVCTRL_INV0EN_SHIFT                 0
#define FTM_INVCTRL_INV1EN_MASK                  0x2u
#define FTM_INVCTRL_INV1EN_SHIFT                 1
#define FTM_INVCTRL_INV2EN_MASK                  0x4u
#define FTM_INVCTRL_INV2EN_SHIFT                 2
#define FTM_INVCTRL_INV3EN_MASK                  0x8u
#define FTM_INVCTRL_INV3EN_SHIFT                 3
/* SWOCTRL Bit Fields */
#define FTM_SWOCTRL_CH0OC_MASK                   0x1u
#define FTM_SWOCTRL_CH0OC_SHIFT                  0
#define FTM_SWOCTRL_CH1OC_MASK                   0x2u
#define FTM_SWOCTRL_CH1OC_SHIFT                  1
#define FTM_SWOCTRL_CH2OC_MASK                   0x4u
#define FTM_SWOCTRL_CH2OC_SHIFT                  2
#define FTM_SWOCTRL_CH3OC_MASK                   0x8u
#define FTM_SWOCTRL_CH3OC_SHIFT                  3
#define FTM_SWOCTRL_CH4OC_MASK                   0x10u
#define FTM_SWOCTRL_CH4OC_SHIFT                  4
#define FTM_SWOCTRL_CH5OC_MASK                   0x20u
#define FTM_SWOCTRL_CH5OC_SHIFT                  5
#define FTM_SWOCTRL_CH6OC_MASK                   0x40u
#define FTM_SWOCTRL_CH6OC_SHIFT                  6
#define FTM_SWOCTRL_CH7OC_MASK                   0x80u
#define FTM_SWOCTRL_CH7OC_SHIFT                  7
#define FTM_SWOCTRL_CH0OCV_MASK                  0x100u
#define FTM_SWOCTRL_CH0OCV_SHIFT                 8
#define FTM_SWOCTRL_CH1OCV_MASK                  0x200u
#define FTM_SWOCTRL_CH1OCV_SHIFT                 9
#define FTM_SWOCTRL_CH2OCV_MASK                  0x400u
#define FTM_SWOCTRL_CH2OCV_SHIFT                 10
#define FTM_SWOCTRL_CH3OCV_MASK                  0x800u
#define FTM_SWOCTRL_CH3OCV_SHIFT                 11
#define FTM_SWOCTRL_CH4OCV_MASK                  0x1000u
#define FTM_SWOCTRL_CH4OCV_SHIFT                 12
#define FTM_SWOCTRL_CH5OCV_MASK                  0x2000u
#define FTM_SWOCTRL_CH5OCV_SHIFT                 13
#define FTM_SWOCTRL_CH6OCV_MASK                  0x4000u
#define FTM_SWOCTRL_CH6OCV_SHIFT                 14
#define FTM_SWOCTRL_CH7OCV_MASK                  0x8000u
#define FTM_SWOCTRL_CH7OCV_SHIFT                 15
/* PWMLOAD Bit Fields */
#define FTM_PWMLOAD_CH0SEL_MASK                  0x1u
#define FTM_PWMLOAD_CH0SEL_SHIFT                 0
#define FTM_PWMLOAD_CH1SEL_MASK                  0x2u
#define FTM_PWMLOAD_CH1SEL_SHIFT                 1
#define FTM_PWMLOAD_CH2SEL_MASK                  0x4u
#define FTM_PWMLOAD_CH2SEL_SHIFT                 2
#define FTM_PWMLOAD_CH3SEL_MASK                  0x8u
#define FTM_PWMLOAD_CH3SEL_SHIFT                 3
#define FTM_PWMLOAD_CH4SEL_MASK                  0x10u
#define FTM_PWMLOAD_CH4SEL_SHIFT                 4
#define FTM_PWMLOAD_CH5SEL_MASK                  0x20u
#define FTM_PWMLOAD_CH5SEL_SHIFT                 5
#define FTM_PWMLOAD_CH6SEL_MASK                  0x40u
#define FTM_PWMLOAD_CH6SEL_SHIFT                 6
#define FTM_PWMLOAD_CH7SEL_MASK                  0x80u
#define FTM_PWMLOAD_CH7SEL_SHIFT                 7
#define FTM_PWMLOAD_LDOK_MASK                    0x200u
#define FTM_PWMLOAD_LDOK_SHIFT                   9

/*!
 * @}
 */ /* end of group FTM_Register_Masks */


/* FTM - Peripheral instance base addresses */
/** Peripheral FTM0 base pointer */
#define FTM0_BASE_PTR                            ((FTM_MemMapPtr)0x40038000u)
/** Peripheral FTM1 base pointer */
#define FTM1_BASE_PTR                            ((FTM_MemMapPtr)0x40039000u)
/** Peripheral FTM2 base pointer */
#define FTM2_BASE_PTR                            ((FTM_MemMapPtr)0x4003A000u)
/** Array initializer of FTM peripheral base pointers */
#define FTM_BASE_PTRS                            { FTM0_BASE_PTR, FTM1_BASE_PTR, FTM2_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- FTM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Register_Accessor_Macros FTM - Register accessor macros
 * @{
 */


/* FTM - Register instance definitions */
/* FTM0 */
#define FTM0_SC                                  FTM_SC_REG(FTM0_BASE_PTR)
#define FTM0_CNT                                 FTM_CNT_REG(FTM0_BASE_PTR)
#define FTM0_MOD                                 FTM_MOD_REG(FTM0_BASE_PTR)
#define FTM0_C0SC                                FTM_CnSC_REG(FTM0_BASE_PTR,0)
#define FTM0_C0V                                 FTM_CnV_REG(FTM0_BASE_PTR,0)
#define FTM0_C1SC                                FTM_CnSC_REG(FTM0_BASE_PTR,1)
#define FTM0_C1V                                 FTM_CnV_REG(FTM0_BASE_PTR,1)
#define FTM0_EXTTRIG                             FTM_EXTTRIG_REG(FTM0_BASE_PTR)
/* FTM1 */
#define FTM1_SC                                  FTM_SC_REG(FTM1_BASE_PTR)
#define FTM1_CNT                                 FTM_CNT_REG(FTM1_BASE_PTR)
#define FTM1_MOD                                 FTM_MOD_REG(FTM1_BASE_PTR)
#define FTM1_C0SC                                FTM_CnSC_REG(FTM1_BASE_PTR,0)
#define FTM1_C0V                                 FTM_CnV_REG(FTM1_BASE_PTR,0)
#define FTM1_C1SC                                FTM_CnSC_REG(FTM1_BASE_PTR,1)
#define FTM1_C1V                                 FTM_CnV_REG(FTM1_BASE_PTR,1)
/* FTM2 */
#define FTM2_SC                                  FTM_SC_REG(FTM2_BASE_PTR)
#define FTM2_CNT                                 FTM_CNT_REG(FTM2_BASE_PTR)
#define FTM2_MOD                                 FTM_MOD_REG(FTM2_BASE_PTR)
#define FTM2_C0SC                                FTM_CnSC_REG(FTM2_BASE_PTR,0)
#define FTM2_C0V                                 FTM_CnV_REG(FTM2_BASE_PTR,0)
#define FTM2_C1SC                                FTM_CnSC_REG(FTM2_BASE_PTR,1)
#define FTM2_C1V                                 FTM_CnV_REG(FTM2_BASE_PTR,1)
#define FTM2_C2SC                                FTM_CnSC_REG(FTM2_BASE_PTR,2)
#define FTM2_C2V                                 FTM_CnV_REG(FTM2_BASE_PTR,2)
#define FTM2_C3SC                                FTM_CnSC_REG(FTM2_BASE_PTR,3)
#define FTM2_C3V                                 FTM_CnV_REG(FTM2_BASE_PTR,3)
#define FTM2_C4SC                                FTM_CnSC_REG(FTM2_BASE_PTR,4)
#define FTM2_C4V                                 FTM_CnV_REG(FTM2_BASE_PTR,4)
#define FTM2_C5SC                                FTM_CnSC_REG(FTM2_BASE_PTR,5)
#define FTM2_C5V                                 FTM_CnV_REG(FTM2_BASE_PTR,5)
#define FTM2_CNTIN                               FTM_CNTIN_REG(FTM2_BASE_PTR)
#define FTM2_STATUS                              FTM_STATUS_REG(FTM2_BASE_PTR)
#define FTM2_MODE                                FTM_MODE_REG(FTM2_BASE_PTR)
#define FTM2_SYNC                                FTM_SYNC_REG(FTM2_BASE_PTR)
#define FTM2_OUTINIT                             FTM_OUTINIT_REG(FTM2_BASE_PTR)
#define FTM2_OUTMASK                             FTM_OUTMASK_REG(FTM2_BASE_PTR)
#define FTM2_COMBINE                             FTM_COMBINE_REG(FTM2_BASE_PTR)
#define FTM2_DEADTIME                            FTM_DEADTIME_REG(FTM2_BASE_PTR)
#define FTM2_EXTTRIG                             FTM_EXTTRIG_REG(FTM2_BASE_PTR)
#define FTM2_POL                                 FTM_POL_REG(FTM2_BASE_PTR)
#define FTM2_FMS                                 FTM_FMS_REG(FTM2_BASE_PTR)
#define FTM2_FILTER                              FTM_FILTER_REG(FTM2_BASE_PTR)
#define FTM2_FLTCTRL                             FTM_FLTCTRL_REG(FTM2_BASE_PTR)
#define FTM2_CONF                                FTM_CONF_REG(FTM2_BASE_PTR)
#define FTM2_FLTPOL                              FTM_FLTPOL_REG(FTM2_BASE_PTR)
#define FTM2_SYNCONF                             FTM_SYNCONF_REG(FTM2_BASE_PTR)
#define FTM2_INVCTRL                             FTM_INVCTRL_REG(FTM2_BASE_PTR)
#define FTM2_SWOCTRL                             FTM_SWOCTRL_REG(FTM2_BASE_PTR)
#define FTM2_PWMLOAD                             FTM_PWMLOAD_REG(FTM2_BASE_PTR)

/* FTM - Register array accessors */
#define FTM0_CnSC(index)                         FTM_CnSC_REG(FTM0_BASE_PTR,index)
#define FTM1_CnSC(index)                         FTM_CnSC_REG(FTM1_BASE_PTR,index)
#define FTM2_CnSC(index)                         FTM_CnSC_REG(FTM2_BASE_PTR,index)
#define FTM0_CnV(index)                          FTM_CnV_REG(FTM0_BASE_PTR,index)
#define FTM1_CnV(index)                          FTM_CnV_REG(FTM1_BASE_PTR,index)
#define FTM2_CnV(index)                          FTM_CnV_REG(FTM2_BASE_PTR,index)

/*!
 * @}
 */ /* end of group FTM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group FTM_Peripheral */


/* ----------------------------------------------------------------------------
   -- FTMRE
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTMRE_Peripheral FTMRE
 * @{
 */

/** FTMRE - Peripheral register structure */
typedef struct FTMRE_MemMap {
  uint8_t RESERVED_0[1];
  uint8_t FCCOBIX;                                 /**< Flash CCOB Index Register, offset: 0x1 */
  uint8_t FSEC;                                    /**< Flash Security Register, offset: 0x2 */
  uint8_t FCLKDIV;                                 /**< Flash Clock Divider Register, offset: 0x3 */
  uint8_t RESERVED_1[1];
  uint8_t FSTAT;                                   /**< Flash Status Register, offset: 0x5 */
  uint8_t RESERVED_2[1];
  uint8_t FCNFG;                                   /**< Flash Configuration Register, offset: 0x7 */
  uint8_t FCCOBLO;                                 /**< Flash Common Command Object Register: Low, offset: 0x8 */
  uint8_t FCCOBHI;                                 /**< Flash Common Command Object Register:High, offset: 0x9 */
  uint8_t RESERVED_3[1];
  uint8_t FPROT;                                   /**< Flash Protection Register, offset: 0xB */
  uint8_t RESERVED_4[3];
  uint8_t FOPT;                                    /**< Flash Option Register, offset: 0xF */
} volatile *FTMRE_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FTMRE - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTMRE_Register_Accessor_Macros FTMRE - Register accessor macros
 * @{
 */


/* FTMRE - Register accessors */
#define FTMRE_FCCOBIX_REG(base)                  ((base)->FCCOBIX)
#define FTMRE_FSEC_REG(base)                     ((base)->FSEC)
#define FTMRE_FCLKDIV_REG(base)                  ((base)->FCLKDIV)
#define FTMRE_FSTAT_REG(base)                    ((base)->FSTAT)
#define FTMRE_FCNFG_REG(base)                    ((base)->FCNFG)
#define FTMRE_FCCOBLO_REG(base)                  ((base)->FCCOBLO)
#define FTMRE_FCCOBHI_REG(base)                  ((base)->FCCOBHI)
#define FTMRE_FPROT_REG(base)                    ((base)->FPROT)
#define FTMRE_FOPT_REG(base)                     ((base)->FOPT)

/*!
 * @}
 */ /* end of group FTMRE_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- FTMRE Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTMRE_Register_Masks FTMRE Register Masks
 * @{
 */

/* FCCOBIX Bit Fields */
#define FTMRE_FCCOBIX_CCOBIX_MASK                0x7u
#define FTMRE_FCCOBIX_CCOBIX_SHIFT               0
#define FTMRE_FCCOBIX_CCOBIX(x)                  (((uint8_t)(((uint8_t)(x))<<FTMRE_FCCOBIX_CCOBIX_SHIFT))&FTMRE_FCCOBIX_CCOBIX_MASK)
/* FSEC Bit Fields */
#define FTMRE_FSEC_SEC_MASK                      0x3u
#define FTMRE_FSEC_SEC_SHIFT                     0
#define FTMRE_FSEC_SEC(x)                        (((uint8_t)(((uint8_t)(x))<<FTMRE_FSEC_SEC_SHIFT))&FTMRE_FSEC_SEC_MASK)
#define FTMRE_FSEC_KEYEN_MASK                    0xC0u
#define FTMRE_FSEC_KEYEN_SHIFT                   6
#define FTMRE_FSEC_KEYEN(x)                      (((uint8_t)(((uint8_t)(x))<<FTMRE_FSEC_KEYEN_SHIFT))&FTMRE_FSEC_KEYEN_MASK)
/* FCLKDIV Bit Fields */
#define FTMRE_FCLKDIV_FDIV_MASK                  0x3Fu
#define FTMRE_FCLKDIV_FDIV_SHIFT                 0
#define FTMRE_FCLKDIV_FDIV(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRE_FCLKDIV_FDIV_SHIFT))&FTMRE_FCLKDIV_FDIV_MASK)
#define FTMRE_FCLKDIV_FDIVLCK_MASK               0x40u
#define FTMRE_FCLKDIV_FDIVLCK_SHIFT              6
#define FTMRE_FCLKDIV_FDIVLD_MASK                0x80u
#define FTMRE_FCLKDIV_FDIVLD_SHIFT               7
/* FSTAT Bit Fields */
#define FTMRE_FSTAT_MGSTAT_MASK                  0x3u
#define FTMRE_FSTAT_MGSTAT_SHIFT                 0
#define FTMRE_FSTAT_MGSTAT(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRE_FSTAT_MGSTAT_SHIFT))&FTMRE_FSTAT_MGSTAT_MASK)
#define FTMRE_FSTAT_MGBUSY_MASK                  0x8u
#define FTMRE_FSTAT_MGBUSY_SHIFT                 3
#define FTMRE_FSTAT_FPVIOL_MASK                  0x10u
#define FTMRE_FSTAT_FPVIOL_SHIFT                 4
#define FTMRE_FSTAT_ACCERR_MASK                  0x20u
#define FTMRE_FSTAT_ACCERR_SHIFT                 5
#define FTMRE_FSTAT_CCIF_MASK                    0x80u
#define FTMRE_FSTAT_CCIF_SHIFT                   7
/* FCNFG Bit Fields */
#define FTMRE_FCNFG_ERSAREQ_MASK                 0x20u
#define FTMRE_FCNFG_ERSAREQ_SHIFT                5
#define FTMRE_FCNFG_CCIE_MASK                    0x80u
#define FTMRE_FCNFG_CCIE_SHIFT                   7
/* FCCOBLO Bit Fields */
#define FTMRE_FCCOBLO_CCOB_MASK                  0xFFu
#define FTMRE_FCCOBLO_CCOB_SHIFT                 0
#define FTMRE_FCCOBLO_CCOB(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRE_FCCOBLO_CCOB_SHIFT))&FTMRE_FCCOBLO_CCOB_MASK)
/* FCCOBHI Bit Fields */
#define FTMRE_FCCOBHI_CCOB_MASK                  0xFFu
#define FTMRE_FCCOBHI_CCOB_SHIFT                 0
#define FTMRE_FCCOBHI_CCOB(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRE_FCCOBHI_CCOB_SHIFT))&FTMRE_FCCOBHI_CCOB_MASK)
/* FPROT Bit Fields */
#define FTMRE_FPROT_FPLS_MASK                    0x3u
#define FTMRE_FPROT_FPLS_SHIFT                   0
#define FTMRE_FPROT_FPLS(x)                      (((uint8_t)(((uint8_t)(x))<<FTMRE_FPROT_FPLS_SHIFT))&FTMRE_FPROT_FPLS_MASK)
#define FTMRE_FPROT_FPLDIS_MASK                  0x4u
#define FTMRE_FPROT_FPLDIS_SHIFT                 2
#define FTMRE_FPROT_FPHS_MASK                    0x18u
#define FTMRE_FPROT_FPHS_SHIFT                   3
#define FTMRE_FPROT_FPHS(x)                      (((uint8_t)(((uint8_t)(x))<<FTMRE_FPROT_FPHS_SHIFT))&FTMRE_FPROT_FPHS_MASK)
#define FTMRE_FPROT_FPHDIS_MASK                  0x20u
#define FTMRE_FPROT_FPHDIS_SHIFT                 5
#define FTMRE_FPROT_RNV6_MASK                    0x40u
#define FTMRE_FPROT_RNV6_SHIFT                   6
#define FTMRE_FPROT_FPOPEN_MASK                  0x80u
#define FTMRE_FPROT_FPOPEN_SHIFT                 7
/* FOPT Bit Fields */
#define FTMRE_FOPT_NV_MASK                       0xFFu
#define FTMRE_FOPT_NV_SHIFT                      0
#define FTMRE_FOPT_NV(x)                         (((uint8_t)(((uint8_t)(x))<<FTMRE_FOPT_NV_SHIFT))&FTMRE_FOPT_NV_MASK)

/*!
 * @}
 */ /* end of group FTMRE_Register_Masks */


/* FTMRE - Peripheral instance base addresses */
/** Peripheral FTMRE base pointer */
#define FTMRE_BASE_PTR                           ((FTMRE_MemMapPtr)0x40020000u)
/** Array initializer of FTMRE peripheral base pointers */
#define FTMRE_BASE_PTRS                          { FTMRE_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- FTMRE - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTMRE_Register_Accessor_Macros FTMRE - Register accessor macros
 * @{
 */


/* FTMRE - Register instance definitions */
/* FTMRE */
#define FTMRE_FCCOBIX                            FTMRE_FCCOBIX_REG(FTMRE_BASE_PTR)
#define FTMRE_FSEC                               FTMRE_FSEC_REG(FTMRE_BASE_PTR)
#define FTMRE_FCLKDIV                            FTMRE_FCLKDIV_REG(FTMRE_BASE_PTR)
#define FTMRE_FSTAT                              FTMRE_FSTAT_REG(FTMRE_BASE_PTR)
#define FTMRE_FCNFG                              FTMRE_FCNFG_REG(FTMRE_BASE_PTR)
#define FTMRE_FCCOBLO                            FTMRE_FCCOBLO_REG(FTMRE_BASE_PTR)
#define FTMRE_FCCOBHI                            FTMRE_FCCOBHI_REG(FTMRE_BASE_PTR)
#define FTMRE_FPROT                              FTMRE_FPROT_REG(FTMRE_BASE_PTR)
#define FTMRE_FOPT                               FTMRE_FOPT_REG(FTMRE_BASE_PTR)

/*!
 * @}
 */ /* end of group FTMRE_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group FTMRE_Peripheral */


/* ----------------------------------------------------------------------------
   -- GPIO
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Peripheral GPIO
 * @{
 */

/** GPIO - Peripheral register structure */
typedef struct GPIO_MemMap {
  uint32_t PDOR;                                   /**< Port Data Output Register, offset: 0x0 */
  uint32_t PSOR;                                   /**< Port Set Output Register, offset: 0x4 */
  uint32_t PCOR;                                   /**< Port Clear Output Register, offset: 0x8 */
  uint32_t PTOR;                                   /**< Port Toggle Output Register, offset: 0xC */
  uint32_t PDIR;                                   /**< Port Data Input Register, offset: 0x10 */
  uint32_t PDDR;                                   /**< Port Data Direction Register, offset: 0x14 */
  uint32_t PIDR;                                   /**< Port Input Disable Register, offset: 0x18 */
} volatile *GPIO_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- GPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Accessor_Macros GPIO - Register accessor macros
 * @{
 */


/* GPIO - Register accessors */
#define GPIO_PDOR_REG(base)                      ((base)->PDOR)
#define GPIO_PSOR_REG(base)                      ((base)->PSOR)
#define GPIO_PCOR_REG(base)                      ((base)->PCOR)
#define GPIO_PTOR_REG(base)                      ((base)->PTOR)
#define GPIO_PDIR_REG(base)                      ((base)->PDIR)
#define GPIO_PDDR_REG(base)                      ((base)->PDDR)
#define GPIO_PIDR_REG(base)                      ((base)->PIDR)

/*!
 * @}
 */ /* end of group GPIO_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- GPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Masks GPIO Register Masks
 * @{
 */

/* PDOR Bit Fields */
#define GPIO_PDOR_PDO_MASK                       0xFFFFFFFFu
#define GPIO_PDOR_PDO_SHIFT                      0
#define GPIO_PDOR_PDO(x)                         (((uint32_t)(((uint32_t)(x))<<GPIO_PDOR_PDO_SHIFT))&GPIO_PDOR_PDO_MASK)
/* PSOR Bit Fields */
#define GPIO_PSOR_PTSO_MASK                      0xFFFFFFFFu
#define GPIO_PSOR_PTSO_SHIFT                     0
#define GPIO_PSOR_PTSO(x)                        (((uint32_t)(((uint32_t)(x))<<GPIO_PSOR_PTSO_SHIFT))&GPIO_PSOR_PTSO_MASK)
/* PCOR Bit Fields */
#define GPIO_PCOR_PTCO_MASK                      0xFFFFFFFFu
#define GPIO_PCOR_PTCO_SHIFT                     0
#define GPIO_PCOR_PTCO(x)                        (((uint32_t)(((uint32_t)(x))<<GPIO_PCOR_PTCO_SHIFT))&GPIO_PCOR_PTCO_MASK)
/* PTOR Bit Fields */
#define GPIO_PTOR_PTTO_MASK                      0xFFFFFFFFu
#define GPIO_PTOR_PTTO_SHIFT                     0
#define GPIO_PTOR_PTTO(x)                        (((uint32_t)(((uint32_t)(x))<<GPIO_PTOR_PTTO_SHIFT))&GPIO_PTOR_PTTO_MASK)
/* PDIR Bit Fields */
#define GPIO_PDIR_PDI_MASK                       0xFFFFFFFFu
#define GPIO_PDIR_PDI_SHIFT                      0
#define GPIO_PDIR_PDI(x)                         (((uint32_t)(((uint32_t)(x))<<GPIO_PDIR_PDI_SHIFT))&GPIO_PDIR_PDI_MASK)
/* PDDR Bit Fields */
#define GPIO_PDDR_PDD_MASK                       0xFFFFFFFFu
#define GPIO_PDDR_PDD_SHIFT                      0
#define GPIO_PDDR_PDD(x)                         (((uint32_t)(((uint32_t)(x))<<GPIO_PDDR_PDD_SHIFT))&GPIO_PDDR_PDD_MASK)
/* PIDR Bit Fields */
#define GPIO_PIDR_PID_MASK                       0xFFFFFFFFu
#define GPIO_PIDR_PID_SHIFT                      0
#define GPIO_PIDR_PID(x)                         (((uint32_t)(((uint32_t)(x))<<GPIO_PIDR_PID_SHIFT))&GPIO_PIDR_PID_MASK)

/*!
 * @}
 */ /* end of group GPIO_Register_Masks */


/* GPIO - Peripheral instance base addresses */
/** Peripheral GPIOA base pointer */
#define GPIOA_BASE_PTR                           ((GPIO_MemMapPtr)0x400FF000u)
/** Peripheral GPIOB base pointer */
#define GPIOB_BASE_PTR                           ((GPIO_MemMapPtr)0x400FF040u)
/** Peripheral GPIOC base pointer */
#define GPIOC_BASE_PTR                           ((GPIO_MemMapPtr)0x400FF080u)
/** Array initializer of GPIO peripheral base pointers */
#define GPIO_BASE_PTRS                           { GPIOA_BASE_PTR, GPIOB_BASE_PTR, GPIOC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- GPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Accessor_Macros GPIO - Register accessor macros
 * @{
 */


/* GPIO - Register instance definitions */
/* GPIOA */
#define GPIOA_PDOR                               GPIO_PDOR_REG(GPIOA_BASE_PTR)
#define GPIOA_PSOR                               GPIO_PSOR_REG(GPIOA_BASE_PTR)
#define GPIOA_PCOR                               GPIO_PCOR_REG(GPIOA_BASE_PTR)
#define GPIOA_PTOR                               GPIO_PTOR_REG(GPIOA_BASE_PTR)
#define GPIOA_PDIR                               GPIO_PDIR_REG(GPIOA_BASE_PTR)
#define GPIOA_PDDR                               GPIO_PDDR_REG(GPIOA_BASE_PTR)
#define GPIOA_PIDR                               GPIO_PIDR_REG(GPIOA_BASE_PTR)
/* GPIOB */
#define GPIOB_PDOR                               GPIO_PDOR_REG(GPIOB_BASE_PTR)
#define GPIOB_PSOR                               GPIO_PSOR_REG(GPIOB_BASE_PTR)
#define GPIOB_PCOR                               GPIO_PCOR_REG(GPIOB_BASE_PTR)
#define GPIOB_PTOR                               GPIO_PTOR_REG(GPIOB_BASE_PTR)
#define GPIOB_PDIR                               GPIO_PDIR_REG(GPIOB_BASE_PTR)
#define GPIOB_PDDR                               GPIO_PDDR_REG(GPIOB_BASE_PTR)
#define GPIOB_PIDR                               GPIO_PIDR_REG(GPIOB_BASE_PTR)
/* GPIOC */
#define GPIOC_PDOR                               GPIO_PDOR_REG(GPIOC_BASE_PTR)
#define GPIOC_PSOR                               GPIO_PSOR_REG(GPIOC_BASE_PTR)
#define GPIOC_PCOR                               GPIO_PCOR_REG(GPIOC_BASE_PTR)
#define GPIOC_PTOR                               GPIO_PTOR_REG(GPIOC_BASE_PTR)
#define GPIOC_PDIR                               GPIO_PDIR_REG(GPIOC_BASE_PTR)
#define GPIOC_PDDR                               GPIO_PDDR_REG(GPIOC_BASE_PTR)
#define GPIOC_PIDR                               GPIO_PIDR_REG(GPIOC_BASE_PTR)

/*!
 * @}
 */ /* end of group GPIO_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group GPIO_Peripheral */


/* ----------------------------------------------------------------------------
   -- I2C
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Peripheral I2C
 * @{
 */

/** I2C - Peripheral register structure */
typedef struct I2C_MemMap {
  uint8_t A1;                                      /**< I2C Address Register 1, offset: 0x0 */
  uint8_t F;                                       /**< I2C Frequency Divider register, offset: 0x1 */
  uint8_t C1;                                      /**< I2C Control Register 1, offset: 0x2 */
  uint8_t S1;                                      /**< I2C Status register 1, offset: 0x3 */
  uint8_t D;                                       /**< I2C Data I/O register, offset: 0x4 */
  uint8_t C2;                                      /**< I2C Control Register 2, offset: 0x5 */
  uint8_t FLT;                                     /**< I2C Programmable Input Glitch Filter register, offset: 0x6 */
  uint8_t RA;                                      /**< I2C Range Address register, offset: 0x7 */
  uint8_t SMB;                                     /**< I2C SMBus Control and Status register, offset: 0x8 */
  uint8_t A2;                                      /**< I2C Address Register 2, offset: 0x9 */
  uint8_t SLTH;                                    /**< I2C SCL Low Timeout Register High, offset: 0xA */
  uint8_t SLTL;                                    /**< I2C SCL Low Timeout Register Low, offset: 0xB */
} volatile *I2C_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- I2C - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Accessor_Macros I2C - Register accessor macros
 * @{
 */


/* I2C - Register accessors */
#define I2C_A1_REG(base)                         ((base)->A1)
#define I2C_F_REG(base)                          ((base)->F)
#define I2C_C1_REG(base)                         ((base)->C1)
#define I2C_S1_REG(base)                         ((base)->S1)
#define I2C_D_REG(base)                          ((base)->D)
#define I2C_C2_REG(base)                         ((base)->C2)
#define I2C_FLT_REG(base)                        ((base)->FLT)
#define I2C_RA_REG(base)                         ((base)->RA)
#define I2C_SMB_REG(base)                        ((base)->SMB)
#define I2C_A2_REG(base)                         ((base)->A2)
#define I2C_SLTH_REG(base)                       ((base)->SLTH)
#define I2C_SLTL_REG(base)                       ((base)->SLTL)

/*!
 * @}
 */ /* end of group I2C_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- I2C Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Masks I2C Register Masks
 * @{
 */

/* A1 Bit Fields */
#define I2C_A1_AD_MASK                           0xFEu
#define I2C_A1_AD_SHIFT                          1
#define I2C_A1_AD(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_A1_AD_SHIFT))&I2C_A1_AD_MASK)
/* F Bit Fields */
#define I2C_F_ICR_MASK                           0x3Fu
#define I2C_F_ICR_SHIFT                          0
#define I2C_F_ICR(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_F_ICR_SHIFT))&I2C_F_ICR_MASK)
#define I2C_F_MULT_MASK                          0xC0u
#define I2C_F_MULT_SHIFT                         6
#define I2C_F_MULT(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_F_MULT_SHIFT))&I2C_F_MULT_MASK)
/* C1 Bit Fields */
#define I2C_C1_WUEN_MASK                         0x2u
#define I2C_C1_WUEN_SHIFT                        1
#define I2C_C1_RSTA_MASK                         0x4u
#define I2C_C1_RSTA_SHIFT                        2
#define I2C_C1_TXAK_MASK                         0x8u
#define I2C_C1_TXAK_SHIFT                        3
#define I2C_C1_TX_MASK                           0x10u
#define I2C_C1_TX_SHIFT                          4
#define I2C_C1_MST_MASK                          0x20u
#define I2C_C1_MST_SHIFT                         5
#define I2C_C1_IICIE_MASK                        0x40u
#define I2C_C1_IICIE_SHIFT                       6
#define I2C_C1_IICEN_MASK                        0x80u
#define I2C_C1_IICEN_SHIFT                       7
/* S1 Bit Fields */
#define I2C_S1_RXAK_MASK                         0x1u
#define I2C_S1_RXAK_SHIFT                        0
#define I2C_S1_IICIF_MASK                        0x2u
#define I2C_S1_IICIF_SHIFT                       1
#define I2C_S1_SRW_MASK                          0x4u
#define I2C_S1_SRW_SHIFT                         2
#define I2C_S1_RAM_MASK                          0x8u
#define I2C_S1_RAM_SHIFT                         3
#define I2C_S1_ARBL_MASK                         0x10u
#define I2C_S1_ARBL_SHIFT                        4
#define I2C_S1_BUSY_MASK                         0x20u
#define I2C_S1_BUSY_SHIFT                        5
#define I2C_S1_IAAS_MASK                         0x40u
#define I2C_S1_IAAS_SHIFT                        6
#define I2C_S1_TCF_MASK                          0x80u
#define I2C_S1_TCF_SHIFT                         7
/* D Bit Fields */
#define I2C_D_DATA_MASK                          0xFFu
#define I2C_D_DATA_SHIFT                         0
#define I2C_D_DATA(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_D_DATA_SHIFT))&I2C_D_DATA_MASK)
/* C2 Bit Fields */
#define I2C_C2_AD_MASK                           0x7u
#define I2C_C2_AD_SHIFT                          0
#define I2C_C2_AD(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_C2_AD_SHIFT))&I2C_C2_AD_MASK)
#define I2C_C2_RMEN_MASK                         0x8u
#define I2C_C2_RMEN_SHIFT                        3
#define I2C_C2_SBRC_MASK                         0x10u
#define I2C_C2_SBRC_SHIFT                        4
#define I2C_C2_ADEXT_MASK                        0x40u
#define I2C_C2_ADEXT_SHIFT                       6
#define I2C_C2_GCAEN_MASK                        0x80u
#define I2C_C2_GCAEN_SHIFT                       7
/* FLT Bit Fields */
#define I2C_FLT_FLT_MASK                         0xFu
#define I2C_FLT_FLT_SHIFT                        0
#define I2C_FLT_FLT(x)                           (((uint8_t)(((uint8_t)(x))<<I2C_FLT_FLT_SHIFT))&I2C_FLT_FLT_MASK)
#define I2C_FLT_STARTF_MASK                      0x10u
#define I2C_FLT_STARTF_SHIFT                     4
#define I2C_FLT_SSIE_MASK                        0x20u
#define I2C_FLT_SSIE_SHIFT                       5
#define I2C_FLT_STOPF_MASK                       0x40u
#define I2C_FLT_STOPF_SHIFT                      6
#define I2C_FLT_SHEN_MASK                        0x80u
#define I2C_FLT_SHEN_SHIFT                       7
/* RA Bit Fields */
#define I2C_RA_RAD_MASK                          0xFEu
#define I2C_RA_RAD_SHIFT                         1
#define I2C_RA_RAD(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_RA_RAD_SHIFT))&I2C_RA_RAD_MASK)
/* SMB Bit Fields */
#define I2C_SMB_SHTF2IE_MASK                     0x1u
#define I2C_SMB_SHTF2IE_SHIFT                    0
#define I2C_SMB_SHTF2_MASK                       0x2u
#define I2C_SMB_SHTF2_SHIFT                      1
#define I2C_SMB_SHTF1_MASK                       0x4u
#define I2C_SMB_SHTF1_SHIFT                      2
#define I2C_SMB_SLTF_MASK                        0x8u
#define I2C_SMB_SLTF_SHIFT                       3
#define I2C_SMB_TCKSEL_MASK                      0x10u
#define I2C_SMB_TCKSEL_SHIFT                     4
#define I2C_SMB_SIICAEN_MASK                     0x20u
#define I2C_SMB_SIICAEN_SHIFT                    5
#define I2C_SMB_ALERTEN_MASK                     0x40u
#define I2C_SMB_ALERTEN_SHIFT                    6
#define I2C_SMB_FACK_MASK                        0x80u
#define I2C_SMB_FACK_SHIFT                       7
/* A2 Bit Fields */
#define I2C_A2_SAD_MASK                          0xFEu
#define I2C_A2_SAD_SHIFT                         1
#define I2C_A2_SAD(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_A2_SAD_SHIFT))&I2C_A2_SAD_MASK)
/* SLTH Bit Fields */
#define I2C_SLTH_SSLT_MASK                       0xFFu
#define I2C_SLTH_SSLT_SHIFT                      0
#define I2C_SLTH_SSLT(x)                         (((uint8_t)(((uint8_t)(x))<<I2C_SLTH_SSLT_SHIFT))&I2C_SLTH_SSLT_MASK)
/* SLTL Bit Fields */
#define I2C_SLTL_SSLT_MASK                       0xFFu
#define I2C_SLTL_SSLT_SHIFT                      0
#define I2C_SLTL_SSLT(x)                         (((uint8_t)(((uint8_t)(x))<<I2C_SLTL_SSLT_SHIFT))&I2C_SLTL_SSLT_MASK)

/*!
 * @}
 */ /* end of group I2C_Register_Masks */


/* I2C - Peripheral instance base addresses */
/** Peripheral I2C0 base pointer */
#define I2C0_BASE_PTR                            ((I2C_MemMapPtr)0x40066000u)
/** Peripheral I2C1 base pointer */
#define I2C1_BASE_PTR                            ((I2C_MemMapPtr)0x40067000u)
/** Array initializer of I2C peripheral base pointers */
#define I2C_BASE_PTRS                            { I2C0_BASE_PTR, I2C1_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- I2C - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Accessor_Macros I2C - Register accessor macros
 * @{
 */


/* I2C - Register instance definitions */
/* I2C0 */
#define I2C0_A1                                  I2C_A1_REG(I2C0_BASE_PTR)
#define I2C0_F                                   I2C_F_REG(I2C0_BASE_PTR)
#define I2C0_C1                                  I2C_C1_REG(I2C0_BASE_PTR)
#define I2C0_S1                                  I2C_S1_REG(I2C0_BASE_PTR)
#define I2C0_D                                   I2C_D_REG(I2C0_BASE_PTR)
#define I2C0_C2                                  I2C_C2_REG(I2C0_BASE_PTR)
#define I2C0_FLT                                 I2C_FLT_REG(I2C0_BASE_PTR)
#define I2C0_RA                                  I2C_RA_REG(I2C0_BASE_PTR)
#define I2C0_SMB                                 I2C_SMB_REG(I2C0_BASE_PTR)
#define I2C0_A2                                  I2C_A2_REG(I2C0_BASE_PTR)
#define I2C0_SLTH                                I2C_SLTH_REG(I2C0_BASE_PTR)
#define I2C0_SLTL                                I2C_SLTL_REG(I2C0_BASE_PTR)
/* I2C1 */
#define I2C1_A1                                  I2C_A1_REG(I2C1_BASE_PTR)
#define I2C1_F                                   I2C_F_REG(I2C1_BASE_PTR)
#define I2C1_C1                                  I2C_C1_REG(I2C1_BASE_PTR)
#define I2C1_S1                                  I2C_S1_REG(I2C1_BASE_PTR)
#define I2C1_D                                   I2C_D_REG(I2C1_BASE_PTR)
#define I2C1_C2                                  I2C_C2_REG(I2C1_BASE_PTR)
#define I2C1_FLT                                 I2C_FLT_REG(I2C1_BASE_PTR)
#define I2C1_RA                                  I2C_RA_REG(I2C1_BASE_PTR)
#define I2C1_SMB                                 I2C_SMB_REG(I2C1_BASE_PTR)
#define I2C1_A2                                  I2C_A2_REG(I2C1_BASE_PTR)
#define I2C1_SLTH                                I2C_SLTH_REG(I2C1_BASE_PTR)
#define I2C1_SLTL                                I2C_SLTL_REG(I2C1_BASE_PTR)

/*!
 * @}
 */ /* end of group I2C_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group I2C_Peripheral */


/* ----------------------------------------------------------------------------
   -- ICS
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ICS_Peripheral ICS
 * @{
 */

/** ICS - Peripheral register structure */
typedef struct ICS_MemMap {
  uint8_t C1;                                      /**< ICS Control Register 1, offset: 0x0 */
  uint8_t C2;                                      /**< ICS Control Register 2, offset: 0x1 */
  uint8_t C3;                                      /**< ICS Control Register 3, offset: 0x2 */
  uint8_t C4;                                      /**< ICS Control Register 4, offset: 0x3 */
  uint8_t S;                                       /**< ICS Status Register, offset: 0x4 */
} volatile *ICS_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ICS - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ICS_Register_Accessor_Macros ICS - Register accessor macros
 * @{
 */


/* ICS - Register accessors */
#define ICS_C1_REG(base)                         ((base)->C1)
#define ICS_C2_REG(base)                         ((base)->C2)
#define ICS_C3_REG(base)                         ((base)->C3)
#define ICS_C4_REG(base)                         ((base)->C4)
#define ICS_S_REG(base)                          ((base)->S)

/*!
 * @}
 */ /* end of group ICS_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ICS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ICS_Register_Masks ICS Register Masks
 * @{
 */

/* C1 Bit Fields */
#define ICS_C1_IREFSTEN_MASK                     0x1u
#define ICS_C1_IREFSTEN_SHIFT                    0
#define ICS_C1_IRCLKEN_MASK                      0x2u
#define ICS_C1_IRCLKEN_SHIFT                     1
#define ICS_C1_IREFS_MASK                        0x4u
#define ICS_C1_IREFS_SHIFT                       2
#define ICS_C1_RDIV_MASK                         0x38u
#define ICS_C1_RDIV_SHIFT                        3
#define ICS_C1_RDIV(x)                           (((uint8_t)(((uint8_t)(x))<<ICS_C1_RDIV_SHIFT))&ICS_C1_RDIV_MASK)
#define ICS_C1_CLKS_MASK                         0xC0u
#define ICS_C1_CLKS_SHIFT                        6
#define ICS_C1_CLKS(x)                           (((uint8_t)(((uint8_t)(x))<<ICS_C1_CLKS_SHIFT))&ICS_C1_CLKS_MASK)
/* C2 Bit Fields */
#define ICS_C2_LP_MASK                           0x10u
#define ICS_C2_LP_SHIFT                          4
#define ICS_C2_BDIV_MASK                         0xE0u
#define ICS_C2_BDIV_SHIFT                        5
#define ICS_C2_BDIV(x)                           (((uint8_t)(((uint8_t)(x))<<ICS_C2_BDIV_SHIFT))&ICS_C2_BDIV_MASK)
/* C3 Bit Fields */
#define ICS_C3_SCTRIM_MASK                       0xFFu
#define ICS_C3_SCTRIM_SHIFT                      0
#define ICS_C3_SCTRIM(x)                         (((uint8_t)(((uint8_t)(x))<<ICS_C3_SCTRIM_SHIFT))&ICS_C3_SCTRIM_MASK)
/* C4 Bit Fields */
#define ICS_C4_SCFTRIM_MASK                      0x1u
#define ICS_C4_SCFTRIM_SHIFT                     0
#define ICS_C4_CME_MASK                          0x20u
#define ICS_C4_CME_SHIFT                         5
#define ICS_C4_LOLIE_MASK                        0x80u
#define ICS_C4_LOLIE_SHIFT                       7
/* S Bit Fields */
#define ICS_S_CLKST_MASK                         0xCu
#define ICS_S_CLKST_SHIFT                        2
#define ICS_S_CLKST(x)                           (((uint8_t)(((uint8_t)(x))<<ICS_S_CLKST_SHIFT))&ICS_S_CLKST_MASK)
#define ICS_S_IREFST_MASK                        0x10u
#define ICS_S_IREFST_SHIFT                       4
#define ICS_S_LOCK_MASK                          0x40u
#define ICS_S_LOCK_SHIFT                         6
#define ICS_S_LOLS_MASK                          0x80u
#define ICS_S_LOLS_SHIFT                         7

/*!
 * @}
 */ /* end of group ICS_Register_Masks */


/* ICS - Peripheral instance base addresses */
/** Peripheral ICS base pointer */
#define ICS_BASE_PTR                             ((ICS_MemMapPtr)0x40064000u)
/** Array initializer of ICS peripheral base pointers */
#define ICS_BASE_PTRS                            { ICS_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- ICS - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ICS_Register_Accessor_Macros ICS - Register accessor macros
 * @{
 */


/* ICS - Register instance definitions */
/* ICS */
#define ICS_C1                                   ICS_C1_REG(ICS_BASE_PTR)
#define ICS_C2                                   ICS_C2_REG(ICS_BASE_PTR)
#define ICS_C3                                   ICS_C3_REG(ICS_BASE_PTR)
#define ICS_C4                                   ICS_C4_REG(ICS_BASE_PTR)
#define ICS_S                                    ICS_S_REG(ICS_BASE_PTR)

/*!
 * @}
 */ /* end of group ICS_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ICS_Peripheral */


/* ----------------------------------------------------------------------------
   -- IRQ
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IRQ_Peripheral IRQ
 * @{
 */

/** IRQ - Peripheral register structure */
typedef struct IRQ_MemMap {
  uint8_t SC;                                      /**< Interrupt Pin Request Status and Control Register, offset: 0x0 */
} volatile *IRQ_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- IRQ - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IRQ_Register_Accessor_Macros IRQ - Register accessor macros
 * @{
 */


/* IRQ - Register accessors */
#define IRQ_SC_REG(base)                         ((base)->SC)

/*!
 * @}
 */ /* end of group IRQ_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- IRQ Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IRQ_Register_Masks IRQ Register Masks
 * @{
 */

/* SC Bit Fields */
#define IRQ_SC_IRQMOD_MASK                       0x1u
#define IRQ_SC_IRQMOD_SHIFT                      0
#define IRQ_SC_IRQIE_MASK                        0x2u
#define IRQ_SC_IRQIE_SHIFT                       1
#define IRQ_SC_IRQACK_MASK                       0x4u
#define IRQ_SC_IRQACK_SHIFT                      2
#define IRQ_SC_IRQF_MASK                         0x8u
#define IRQ_SC_IRQF_SHIFT                        3
#define IRQ_SC_IRQPE_MASK                        0x10u
#define IRQ_SC_IRQPE_SHIFT                       4
#define IRQ_SC_IRQEDG_MASK                       0x20u
#define IRQ_SC_IRQEDG_SHIFT                      5
#define IRQ_SC_IRQPDD_MASK                       0x40u
#define IRQ_SC_IRQPDD_SHIFT                      6

/*!
 * @}
 */ /* end of group IRQ_Register_Masks */


/* IRQ - Peripheral instance base addresses */
/** Peripheral IRQ base pointer */
#define IRQ_BASE_PTR                             ((IRQ_MemMapPtr)0x40031000u)
/** Array initializer of IRQ peripheral base pointers */
#define IRQ_BASE_PTRS                            { IRQ_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- IRQ - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IRQ_Register_Accessor_Macros IRQ - Register accessor macros
 * @{
 */


/* IRQ - Register instance definitions */
/* IRQ */
#define IRQ_SC                                   IRQ_SC_REG(IRQ_BASE_PTR)

/*!
 * @}
 */ /* end of group IRQ_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group IRQ_Peripheral */


/* ----------------------------------------------------------------------------
   -- KBI
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup KBI_Peripheral KBI
 * @{
 */

/** KBI - Peripheral register structure */
typedef struct KBI_MemMap {
  uint32_t PE;                                     /**< KBI Pin Enable Register, offset: 0x0 */
  uint32_t ES;                                     /**< KBI Edge Select Register, offset: 0x4 */
  uint32_t SC;                                     /**< KBI Status and Control Register, offset: 0x8 */
  uint32_t SP;                                     /**< KBI Source Pin Register, offset: 0xC */
} volatile *KBI_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- KBI - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup KBI_Register_Accessor_Macros KBI - Register accessor macros
 * @{
 */


/* KBI - Register accessors */
#define KBI_PE_REG(base)                         ((base)->PE)
#define KBI_ES_REG(base)                         ((base)->ES)
#define KBI_SC_REG(base)                         ((base)->SC)
#define KBI_SP_REG(base)                         ((base)->SP)

/*!
 * @}
 */ /* end of group KBI_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- KBI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup KBI_Register_Masks KBI Register Masks
 * @{
 */

/* PE Bit Fields */
#define KBI_PE_KBIPE_MASK                        0xFFFFFFFFu
#define KBI_PE_KBIPE_SHIFT                       0
#define KBI_PE_KBIPE(x)                          (((uint32_t)(((uint32_t)(x))<<KBI_PE_KBIPE_SHIFT))&KBI_PE_KBIPE_MASK)
/* ES Bit Fields */
#define KBI_ES_KBEDG_MASK                        0xFFFFFFFFu
#define KBI_ES_KBEDG_SHIFT                       0
#define KBI_ES_KBEDG(x)                          (((uint32_t)(((uint32_t)(x))<<KBI_ES_KBEDG_SHIFT))&KBI_ES_KBEDG_MASK)
/* SC Bit Fields */
#define KBI_SC_KBMOD_MASK                        0x1u
#define KBI_SC_KBMOD_SHIFT                       0
#define KBI_SC_KBIE_MASK                         0x2u
#define KBI_SC_KBIE_SHIFT                        1
#define KBI_SC_KBACK_MASK                        0x4u
#define KBI_SC_KBACK_SHIFT                       2
#define KBI_SC_KBF_MASK                          0x8u
#define KBI_SC_KBF_SHIFT                         3
#define KBI_SC_KBSPEN_MASK                       0x10u
#define KBI_SC_KBSPEN_SHIFT                      4
#define KBI_SC_RSTKBSP_MASK                      0x20u
#define KBI_SC_RSTKBSP_SHIFT                     5
/* SP Bit Fields */
#define KBI_SP_SP_MASK                           0xFFFFFFFFu
#define KBI_SP_SP_SHIFT                          0
#define KBI_SP_SP(x)                             (((uint32_t)(((uint32_t)(x))<<KBI_SP_SP_SHIFT))&KBI_SP_SP_MASK)

/*!
 * @}
 */ /* end of group KBI_Register_Masks */


/* KBI - Peripheral instance base addresses */
/** Peripheral KBI0 base pointer */
#define KBI0_BASE_PTR                            ((KBI_MemMapPtr)0x40079000u)
/** Peripheral KBI1 base pointer */
#define KBI1_BASE_PTR                            ((KBI_MemMapPtr)0x4007A000u)
/** Array initializer of KBI peripheral base pointers */
#define KBI_BASE_PTRS                            { KBI0_BASE_PTR, KBI1_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- KBI - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup KBI_Register_Accessor_Macros KBI - Register accessor macros
 * @{
 */


/* KBI - Register instance definitions */
/* KBI0 */
#define KBI0_PE                                  KBI_PE_REG(KBI0_BASE_PTR)
#define KBI0_ES                                  KBI_ES_REG(KBI0_BASE_PTR)
#define KBI0_SC                                  KBI_SC_REG(KBI0_BASE_PTR)
#define KBI0_SP                                  KBI_SP_REG(KBI0_BASE_PTR)
/* KBI1 */
#define KBI1_PE                                  KBI_PE_REG(KBI1_BASE_PTR)
#define KBI1_ES                                  KBI_ES_REG(KBI1_BASE_PTR)
#define KBI1_SC                                  KBI_SC_REG(KBI1_BASE_PTR)
#define KBI1_SP                                  KBI_SP_REG(KBI1_BASE_PTR)

/*!
 * @}
 */ /* end of group KBI_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group KBI_Peripheral */


/* ----------------------------------------------------------------------------
   -- MCM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Peripheral MCM
 * @{
 */

/** MCM - Peripheral register structure */
typedef struct MCM_MemMap {
  uint8_t RESERVED_0[8];
  uint16_t PLASC;                                  /**< Crossbar Switch (AXBS) Slave Configuration, offset: 0x8 */
  uint16_t PLAMC;                                  /**< Crossbar Switch (AXBS) Master Configuration, offset: 0xA */
  uint32_t PLACR;                                  /**< Platform Control Register, offset: 0xC */
} volatile *MCM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Accessor_Macros MCM - Register accessor macros
 * @{
 */


/* MCM - Register accessors */
#define MCM_PLASC_REG(base)                      ((base)->PLASC)
#define MCM_PLAMC_REG(base)                      ((base)->PLAMC)
#define MCM_PLACR_REG(base)                      ((base)->PLACR)

/*!
 * @}
 */ /* end of group MCM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- MCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Masks MCM Register Masks
 * @{
 */

/* PLASC Bit Fields */
#define MCM_PLASC_ASC_MASK                       0xFFu
#define MCM_PLASC_ASC_SHIFT                      0
#define MCM_PLASC_ASC(x)                         (((uint16_t)(((uint16_t)(x))<<MCM_PLASC_ASC_SHIFT))&MCM_PLASC_ASC_MASK)
/* PLAMC Bit Fields */
#define MCM_PLAMC_AMC_MASK                       0xFFu
#define MCM_PLAMC_AMC_SHIFT                      0
#define MCM_PLAMC_AMC(x)                         (((uint16_t)(((uint16_t)(x))<<MCM_PLAMC_AMC_SHIFT))&MCM_PLAMC_AMC_MASK)
/* PLACR Bit Fields */
#define MCM_PLACR_CFCC_MASK                      0x400u
#define MCM_PLACR_CFCC_SHIFT                     10
#define MCM_PLACR_DFCDA_MASK                     0x800u
#define MCM_PLACR_DFCDA_SHIFT                    11
#define MCM_PLACR_DFCIC_MASK                     0x1000u
#define MCM_PLACR_DFCIC_SHIFT                    12
#define MCM_PLACR_DFCC_MASK                      0x2000u
#define MCM_PLACR_DFCC_SHIFT                     13
#define MCM_PLACR_EFDS_MASK                      0x4000u
#define MCM_PLACR_EFDS_SHIFT                     14
#define MCM_PLACR_DFCS_MASK                      0x8000u
#define MCM_PLACR_DFCS_SHIFT                     15
#define MCM_PLACR_ESFC_MASK                      0x10000u
#define MCM_PLACR_ESFC_SHIFT                     16

/*!
 * @}
 */ /* end of group MCM_Register_Masks */


/* MCM - Peripheral instance base addresses */
/** Peripheral MCM base pointer */
#define MCM_BASE_PTR                             ((MCM_MemMapPtr)0xF0003000u)
/** Array initializer of MCM peripheral base pointers */
#define MCM_BASE_PTRS                            { MCM_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- MCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Accessor_Macros MCM - Register accessor macros
 * @{
 */


/* MCM - Register instance definitions */
/* MCM */
#define MCM_PLASC                                MCM_PLASC_REG(MCM_BASE_PTR)
#define MCM_PLAMC                                MCM_PLAMC_REG(MCM_BASE_PTR)
#define MCM_PLACR                                MCM_PLACR_REG(MCM_BASE_PTR)

/*!
 * @}
 */ /* end of group MCM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group MCM_Peripheral */


/* ----------------------------------------------------------------------------
   -- MSCAN
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MSCAN_Peripheral MSCAN
 * @{
 */

/** MSCAN - Peripheral register structure */
typedef struct MSCAN_MemMap {
  uint8_t CANCTL0;                                 /**< MSCAN Control Register 0, offset: 0x0 */
  uint8_t CANCTL1;                                 /**< MSCAN Control Register 1, offset: 0x1 */
  uint8_t CANBTR0;                                 /**< MSCAN Bus Timing Register 0, offset: 0x2 */
  uint8_t CANBTR1;                                 /**< MSCAN Bus Timing Register 1, offset: 0x3 */
  uint8_t CANRFLG;                                 /**< MSCAN Receiver Flag Register, offset: 0x4 */
  uint8_t CANRIER;                                 /**< MSCAN Receiver Interrupt Enable Register, offset: 0x5 */
  uint8_t CANTFLG;                                 /**< MSCAN Transmitter Flag Register, offset: 0x6 */
  uint8_t CANTIER;                                 /**< MSCAN Transmitter Interrupt Enable Register, offset: 0x7 */
  uint8_t CANTARQ;                                 /**< MSCAN Transmitter Message Abort Request Register, offset: 0x8 */
  uint8_t CANTAAK;                                 /**< MSCAN Transmitter Message Abort Acknowledge Register, offset: 0x9 */
  uint8_t CANTBSEL;                                /**< MSCAN Transmit Buffer Selection Register, offset: 0xA */
  uint8_t CANIDAC;                                 /**< MSCAN Identifier Acceptance Control Register, offset: 0xB */
  uint8_t RESERVED_0[1];
  uint8_t CANMISC;                                 /**< MSCAN Miscellaneous Register, offset: 0xD */
  uint8_t CANRXERR;                                /**< MSCAN Receive Error Counter, offset: 0xE */
  uint8_t CANTXERR;                                /**< MSCAN Transmit Error Counter, offset: 0xF */
  uint8_t CANIDAR_BANK_1[4];                       /**< MSCAN Identifier Acceptance Register n of First Bank, array offset: 0x10, array step: 0x1 */
  uint8_t CANIDMR_BANK_1[4];                       /**< MSCAN Identifier Mask Register n of First Bank, array offset: 0x14, array step: 0x1 */
  uint8_t CANIDAR_BANK_2[4];                       /**< MSCAN Identifier Acceptance Register n of Second Bank, array offset: 0x18, array step: 0x1 */
  uint8_t CANIDMR_BANK_2[4];                       /**< MSCAN Identifier Mask Register n of Second Bank, array offset: 0x1C, array step: 0x1 */
  union {                                          /* offset: 0x20 */
    uint8_t REIDR0;                                  /**< Receive Extended Identifier Register 0, offset: 0x20 */
    uint8_t RSIDR0;                                  /**< Receive Standard Identifier Register 0, offset: 0x20 */
  };
  union {                                          /* offset: 0x21 */
    uint8_t REIDR1;                                  /**< Receive Extended Identifier Register 1, offset: 0x21 */
    uint8_t RSIDR1;                                  /**< Standard Identifier Register 1, offset: 0x21 */
  };
  uint8_t REIDR2;                                  /**< Receive Extended Identifier Register 2, offset: 0x22 */
  uint8_t REIDR3;                                  /**< Receive Extended Identifier Register 3, offset: 0x23 */
  uint8_t REDSR[8];                                /**< Receive Extended Data Segment Register N, array offset: 0x24, array step: 0x1 */
  uint8_t RDLR;                                    /**< Receive Data Length Register, offset: 0x2C */
  uint8_t RESERVED_1[1];
  uint8_t RTSRH;                                   /**< Receive Time Stamp Register High, offset: 0x2E */
  uint8_t RTSRL;                                   /**< Receive Time Stamp Register Low, offset: 0x2F */
  union {                                          /* offset: 0x30 */
    uint8_t TEIDR0;                                  /**< Transmit Extended Identifier Register 0, offset: 0x30 */
    uint8_t TSIDR0;                                  /**< Transmit Standard Identifier Register 0, offset: 0x30 */
  };
  union {                                          /* offset: 0x31 */
    uint8_t TEIDR1;                                  /**< Transmit Extended Identifier Register 1, offset: 0x31 */
    uint8_t TSIDR1;                                  /**< Transmit Standard Identifier Register 1, offset: 0x31 */
  };
  uint8_t TEIDR2;                                  /**< Transmit Extended Identifier Register 2, offset: 0x32 */
  uint8_t TEIDR3;                                  /**< Transmit Extended Identifier Register 3, offset: 0x33 */
  uint8_t TEDSR[8];                                /**< Transmit Extended Data Segment Register N, array offset: 0x34, array step: 0x1 */
  uint8_t TDLR;                                    /**< This register keeps the data length field of the CAN frame., offset: 0x3C */
  uint8_t TBPR;                                    /**< Transmit Buffer Priority Register, offset: 0x3D */
  uint8_t TTSRH;                                   /**< Transmit Time Stamp Register High, offset: 0x3E */
  uint8_t TTSRL;                                   /**< Transmit Time Stamp Register Low, offset: 0x3F */
} volatile *MSCAN_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MSCAN - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MSCAN_Register_Accessor_Macros MSCAN - Register accessor macros
 * @{
 */


/* MSCAN - Register accessors */
#define MSCAN_CANCTL0_REG(base)                  ((base)->CANCTL0)
#define MSCAN_CANCTL1_REG(base)                  ((base)->CANCTL1)
#define MSCAN_CANBTR0_REG(base)                  ((base)->CANBTR0)
#define MSCAN_CANBTR1_REG(base)                  ((base)->CANBTR1)
#define MSCAN_CANRFLG_REG(base)                  ((base)->CANRFLG)
#define MSCAN_CANRIER_REG(base)                  ((base)->CANRIER)
#define MSCAN_CANTFLG_REG(base)                  ((base)->CANTFLG)
#define MSCAN_CANTIER_REG(base)                  ((base)->CANTIER)
#define MSCAN_CANTARQ_REG(base)                  ((base)->CANTARQ)
#define MSCAN_CANTAAK_REG(base)                  ((base)->CANTAAK)
#define MSCAN_CANTBSEL_REG(base)                 ((base)->CANTBSEL)
#define MSCAN_CANIDAC_REG(base)                  ((base)->CANIDAC)
#define MSCAN_CANMISC_REG(base)                  ((base)->CANMISC)
#define MSCAN_CANRXERR_REG(base)                 ((base)->CANRXERR)
#define MSCAN_CANTXERR_REG(base)                 ((base)->CANTXERR)
#define MSCAN_CANIDAR_BANK_1_REG(base,index)     ((base)->CANIDAR_BANK_1[index])
#define MSCAN_CANIDMR_BANK_1_REG(base,index)     ((base)->CANIDMR_BANK_1[index])
#define MSCAN_CANIDAR_BANK_2_REG(base,index)     ((base)->CANIDAR_BANK_2[index])
#define MSCAN_CANIDMR_BANK_2_REG(base,index)     ((base)->CANIDMR_BANK_2[index])
#define MSCAN_REIDR0_REG(base)                   ((base)->REIDR0)
#define MSCAN_RSIDR0_REG(base)                   ((base)->RSIDR0)
#define MSCAN_REIDR1_REG(base)                   ((base)->REIDR1)
#define MSCAN_RSIDR1_REG(base)                   ((base)->RSIDR1)
#define MSCAN_REIDR2_REG(base)                   ((base)->REIDR2)
#define MSCAN_REIDR3_REG(base)                   ((base)->REIDR3)
#define MSCAN_REDSR_REG(base,index)              ((base)->REDSR[index])
#define MSCAN_RDLR_REG(base)                     ((base)->RDLR)
#define MSCAN_RTSRH_REG(base)                    ((base)->RTSRH)
#define MSCAN_RTSRL_REG(base)                    ((base)->RTSRL)
#define MSCAN_TEIDR0_REG(base)                   ((base)->TEIDR0)
#define MSCAN_TSIDR0_REG(base)                   ((base)->TSIDR0)
#define MSCAN_TEIDR1_REG(base)                   ((base)->TEIDR1)
#define MSCAN_TSIDR1_REG(base)                   ((base)->TSIDR1)
#define MSCAN_TEIDR2_REG(base)                   ((base)->TEIDR2)
#define MSCAN_TEIDR3_REG(base)                   ((base)->TEIDR3)
#define MSCAN_TEDSR_REG(base,index)              ((base)->TEDSR[index])
#define MSCAN_TDLR_REG(base)                     ((base)->TDLR)
#define MSCAN_TBPR_REG(base)                     ((base)->TBPR)
#define MSCAN_TTSRH_REG(base)                    ((base)->TTSRH)
#define MSCAN_TTSRL_REG(base)                    ((base)->TTSRL)

/*!
 * @}
 */ /* end of group MSCAN_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- MSCAN Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MSCAN_Register_Masks MSCAN Register Masks
 * @{
 */

/* CANCTL0 Bit Fields */
#define MSCAN_CANCTL0_INITRQ_MASK                0x1u
#define MSCAN_CANCTL0_INITRQ_SHIFT               0
#define MSCAN_CANCTL0_SLPRQ_MASK                 0x2u
#define MSCAN_CANCTL0_SLPRQ_SHIFT                1
#define MSCAN_CANCTL0_WUPE_MASK                  0x4u
#define MSCAN_CANCTL0_WUPE_SHIFT                 2
#define MSCAN_CANCTL0_TIME_MASK                  0x8u
#define MSCAN_CANCTL0_TIME_SHIFT                 3
#define MSCAN_CANCTL0_SYNCH_MASK                 0x10u
#define MSCAN_CANCTL0_SYNCH_SHIFT                4
#define MSCAN_CANCTL0_CSWAI_MASK                 0x20u
#define MSCAN_CANCTL0_CSWAI_SHIFT                5
#define MSCAN_CANCTL0_RXACT_MASK                 0x40u
#define MSCAN_CANCTL0_RXACT_SHIFT                6
#define MSCAN_CANCTL0_RXFRM_MASK                 0x80u
#define MSCAN_CANCTL0_RXFRM_SHIFT                7
/* CANCTL1 Bit Fields */
#define MSCAN_CANCTL1_INITAK_MASK                0x1u
#define MSCAN_CANCTL1_INITAK_SHIFT               0
#define MSCAN_CANCTL1_SLPAK_MASK                 0x2u
#define MSCAN_CANCTL1_SLPAK_SHIFT                1
#define MSCAN_CANCTL1_WUPM_MASK                  0x4u
#define MSCAN_CANCTL1_WUPM_SHIFT                 2
#define MSCAN_CANCTL1_BORM_MASK                  0x8u
#define MSCAN_CANCTL1_BORM_SHIFT                 3
#define MSCAN_CANCTL1_LISTEN_MASK                0x10u
#define MSCAN_CANCTL1_LISTEN_SHIFT               4
#define MSCAN_CANCTL1_LOOPB_MASK                 0x20u
#define MSCAN_CANCTL1_LOOPB_SHIFT                5
#define MSCAN_CANCTL1_CLKSRC_MASK                0x40u
#define MSCAN_CANCTL1_CLKSRC_SHIFT               6
#define MSCAN_CANCTL1_CANE_MASK                  0x80u
#define MSCAN_CANCTL1_CANE_SHIFT                 7
/* CANBTR0 Bit Fields */
#define MSCAN_CANBTR0_BRP_MASK                   0x3Fu
#define MSCAN_CANBTR0_BRP_SHIFT                  0
#define MSCAN_CANBTR0_BRP(x)                     (((uint8_t)(((uint8_t)(x))<<MSCAN_CANBTR0_BRP_SHIFT))&MSCAN_CANBTR0_BRP_MASK)
#define MSCAN_CANBTR0_SJW_MASK                   0xC0u
#define MSCAN_CANBTR0_SJW_SHIFT                  6
#define MSCAN_CANBTR0_SJW(x)                     (((uint8_t)(((uint8_t)(x))<<MSCAN_CANBTR0_SJW_SHIFT))&MSCAN_CANBTR0_SJW_MASK)
/* CANBTR1 Bit Fields */
#define MSCAN_CANBTR1_TSEG1_MASK                 0xFu
#define MSCAN_CANBTR1_TSEG1_SHIFT                0
#define MSCAN_CANBTR1_TSEG1(x)                   (((uint8_t)(((uint8_t)(x))<<MSCAN_CANBTR1_TSEG1_SHIFT))&MSCAN_CANBTR1_TSEG1_MASK)
#define MSCAN_CANBTR1_TSEG2_MASK                 0x70u
#define MSCAN_CANBTR1_TSEG2_SHIFT                4
#define MSCAN_CANBTR1_TSEG2(x)                   (((uint8_t)(((uint8_t)(x))<<MSCAN_CANBTR1_TSEG2_SHIFT))&MSCAN_CANBTR1_TSEG2_MASK)
#define MSCAN_CANBTR1_SAMP_MASK                  0x80u
#define MSCAN_CANBTR1_SAMP_SHIFT                 7
/* CANRFLG Bit Fields */
#define MSCAN_CANRFLG_RXF_MASK                   0x1u
#define MSCAN_CANRFLG_RXF_SHIFT                  0
#define MSCAN_CANRFLG_OVRIF_MASK                 0x2u
#define MSCAN_CANRFLG_OVRIF_SHIFT                1
#define MSCAN_CANRFLG_TSTAT_MASK                 0xCu
#define MSCAN_CANRFLG_TSTAT_SHIFT                2
#define MSCAN_CANRFLG_TSTAT(x)                   (((uint8_t)(((uint8_t)(x))<<MSCAN_CANRFLG_TSTAT_SHIFT))&MSCAN_CANRFLG_TSTAT_MASK)
#define MSCAN_CANRFLG_RSTAT_MASK                 0x30u
#define MSCAN_CANRFLG_RSTAT_SHIFT                4
#define MSCAN_CANRFLG_RSTAT(x)                   (((uint8_t)(((uint8_t)(x))<<MSCAN_CANRFLG_RSTAT_SHIFT))&MSCAN_CANRFLG_RSTAT_MASK)
#define MSCAN_CANRFLG_CSCIF_MASK                 0x40u
#define MSCAN_CANRFLG_CSCIF_SHIFT                6
#define MSCAN_CANRFLG_WUPIF_MASK                 0x80u
#define MSCAN_CANRFLG_WUPIF_SHIFT                7
/* CANRIER Bit Fields */
#define MSCAN_CANRIER_RXFIE_MASK                 0x1u
#define MSCAN_CANRIER_RXFIE_SHIFT                0
#define MSCAN_CANRIER_OVRIE_MASK                 0x2u
#define MSCAN_CANRIER_OVRIE_SHIFT                1
#define MSCAN_CANRIER_TSTATE_MASK                0xCu
#define MSCAN_CANRIER_TSTATE_SHIFT               2
#define MSCAN_CANRIER_TSTATE(x)                  (((uint8_t)(((uint8_t)(x))<<MSCAN_CANRIER_TSTATE_SHIFT))&MSCAN_CANRIER_TSTATE_MASK)
#define MSCAN_CANRIER_RSTATE_MASK                0x30u
#define MSCAN_CANRIER_RSTATE_SHIFT               4
#define MSCAN_CANRIER_RSTATE(x)                  (((uint8_t)(((uint8_t)(x))<<MSCAN_CANRIER_RSTATE_SHIFT))&MSCAN_CANRIER_RSTATE_MASK)
#define MSCAN_CANRIER_CSCIE_MASK                 0x40u
#define MSCAN_CANRIER_CSCIE_SHIFT                6
#define MSCAN_CANRIER_WUPIE_MASK                 0x80u
#define MSCAN_CANRIER_WUPIE_SHIFT                7
/* CANTFLG Bit Fields */
#define MSCAN_CANTFLG_TXE_MASK                   0x7u
#define MSCAN_CANTFLG_TXE_SHIFT                  0
#define MSCAN_CANTFLG_TXE(x)                     (((uint8_t)(((uint8_t)(x))<<MSCAN_CANTFLG_TXE_SHIFT))&MSCAN_CANTFLG_TXE_MASK)
/* CANTIER Bit Fields */
#define MSCAN_CANTIER_TXEIE_MASK                 0x7u
#define MSCAN_CANTIER_TXEIE_SHIFT                0
#define MSCAN_CANTIER_TXEIE(x)                   (((uint8_t)(((uint8_t)(x))<<MSCAN_CANTIER_TXEIE_SHIFT))&MSCAN_CANTIER_TXEIE_MASK)
/* CANTARQ Bit Fields */
#define MSCAN_CANTARQ_ABTRQ_MASK                 0x7u
#define MSCAN_CANTARQ_ABTRQ_SHIFT                0
#define MSCAN_CANTARQ_ABTRQ(x)                   (((uint8_t)(((uint8_t)(x))<<MSCAN_CANTARQ_ABTRQ_SHIFT))&MSCAN_CANTARQ_ABTRQ_MASK)
/* CANTAAK Bit Fields */
#define MSCAN_CANTAAK_ABTAK_MASK                 0x7u
#define MSCAN_CANTAAK_ABTAK_SHIFT                0
#define MSCAN_CANTAAK_ABTAK(x)                   (((uint8_t)(((uint8_t)(x))<<MSCAN_CANTAAK_ABTAK_SHIFT))&MSCAN_CANTAAK_ABTAK_MASK)
/* CANTBSEL Bit Fields */
#define MSCAN_CANTBSEL_TX_MASK                   0x7u
#define MSCAN_CANTBSEL_TX_SHIFT                  0
#define MSCAN_CANTBSEL_TX(x)                     (((uint8_t)(((uint8_t)(x))<<MSCAN_CANTBSEL_TX_SHIFT))&MSCAN_CANTBSEL_TX_MASK)
/* CANIDAC Bit Fields */
#define MSCAN_CANIDAC_IDHIT_MASK                 0x7u
#define MSCAN_CANIDAC_IDHIT_SHIFT                0
#define MSCAN_CANIDAC_IDHIT(x)                   (((uint8_t)(((uint8_t)(x))<<MSCAN_CANIDAC_IDHIT_SHIFT))&MSCAN_CANIDAC_IDHIT_MASK)
#define MSCAN_CANIDAC_IDAM_MASK                  0x30u
#define MSCAN_CANIDAC_IDAM_SHIFT                 4
#define MSCAN_CANIDAC_IDAM(x)                    (((uint8_t)(((uint8_t)(x))<<MSCAN_CANIDAC_IDAM_SHIFT))&MSCAN_CANIDAC_IDAM_MASK)
/* CANMISC Bit Fields */
#define MSCAN_CANMISC_BOHOLD_MASK                0x1u
#define MSCAN_CANMISC_BOHOLD_SHIFT               0
/* CANRXERR Bit Fields */
#define MSCAN_CANRXERR_RXERR_MASK                0xFFu
#define MSCAN_CANRXERR_RXERR_SHIFT               0
#define MSCAN_CANRXERR_RXERR(x)                  (((uint8_t)(((uint8_t)(x))<<MSCAN_CANRXERR_RXERR_SHIFT))&MSCAN_CANRXERR_RXERR_MASK)
/* CANTXERR Bit Fields */
#define MSCAN_CANTXERR_TXERR_MASK                0xFFu
#define MSCAN_CANTXERR_TXERR_SHIFT               0
#define MSCAN_CANTXERR_TXERR(x)                  (((uint8_t)(((uint8_t)(x))<<MSCAN_CANTXERR_TXERR_SHIFT))&MSCAN_CANTXERR_TXERR_MASK)
/* CANIDAR_BANK_1 Bit Fields */
#define MSCAN_CANIDAR_BANK_1_AC_MASK             0xFFu
#define MSCAN_CANIDAR_BANK_1_AC_SHIFT            0
#define MSCAN_CANIDAR_BANK_1_AC(x)               (((uint8_t)(((uint8_t)(x))<<MSCAN_CANIDAR_BANK_1_AC_SHIFT))&MSCAN_CANIDAR_BANK_1_AC_MASK)
/* CANIDMR_BANK_1 Bit Fields */
#define MSCAN_CANIDMR_BANK_1_AM_MASK             0xFFu
#define MSCAN_CANIDMR_BANK_1_AM_SHIFT            0
#define MSCAN_CANIDMR_BANK_1_AM(x)               (((uint8_t)(((uint8_t)(x))<<MSCAN_CANIDMR_BANK_1_AM_SHIFT))&MSCAN_CANIDMR_BANK_1_AM_MASK)
/* CANIDAR_BANK_2 Bit Fields */
#define MSCAN_CANIDAR_BANK_2_AC_MASK             0xFFu
#define MSCAN_CANIDAR_BANK_2_AC_SHIFT            0
#define MSCAN_CANIDAR_BANK_2_AC(x)               (((uint8_t)(((uint8_t)(x))<<MSCAN_CANIDAR_BANK_2_AC_SHIFT))&MSCAN_CANIDAR_BANK_2_AC_MASK)
/* CANIDMR_BANK_2 Bit Fields */
#define MSCAN_CANIDMR_BANK_2_AM_MASK             0xFFu
#define MSCAN_CANIDMR_BANK_2_AM_SHIFT            0
#define MSCAN_CANIDMR_BANK_2_AM(x)               (((uint8_t)(((uint8_t)(x))<<MSCAN_CANIDMR_BANK_2_AM_SHIFT))&MSCAN_CANIDMR_BANK_2_AM_MASK)
/* REIDR0 Bit Fields */
#define MSCAN_REIDR0_REID28_REID21_MASK          0xFFu
#define MSCAN_REIDR0_REID28_REID21_SHIFT         0
#define MSCAN_REIDR0_REID28_REID21(x)            (((uint8_t)(((uint8_t)(x))<<MSCAN_REIDR0_REID28_REID21_SHIFT))&MSCAN_REIDR0_REID28_REID21_MASK)
/* RSIDR0 Bit Fields */
#define MSCAN_RSIDR0_RSID10_RSID3_MASK           0xFFu
#define MSCAN_RSIDR0_RSID10_RSID3_SHIFT          0
#define MSCAN_RSIDR0_RSID10_RSID3(x)             (((uint8_t)(((uint8_t)(x))<<MSCAN_RSIDR0_RSID10_RSID3_SHIFT))&MSCAN_RSIDR0_RSID10_RSID3_MASK)
/* REIDR1 Bit Fields */
#define MSCAN_REIDR1_REID17_REID15_MASK          0x7u
#define MSCAN_REIDR1_REID17_REID15_SHIFT         0
#define MSCAN_REIDR1_REID17_REID15(x)            (((uint8_t)(((uint8_t)(x))<<MSCAN_REIDR1_REID17_REID15_SHIFT))&MSCAN_REIDR1_REID17_REID15_MASK)
#define MSCAN_REIDR1_REIDE_MASK                  0x8u
#define MSCAN_REIDR1_REIDE_SHIFT                 3
#define MSCAN_REIDR1_RSRR_MASK                   0x10u
#define MSCAN_REIDR1_RSRR_SHIFT                  4
#define MSCAN_REIDR1_REID20_REID18_MASK          0xE0u
#define MSCAN_REIDR1_REID20_REID18_SHIFT         5
#define MSCAN_REIDR1_REID20_REID18(x)            (((uint8_t)(((uint8_t)(x))<<MSCAN_REIDR1_REID20_REID18_SHIFT))&MSCAN_REIDR1_REID20_REID18_MASK)
/* RSIDR1 Bit Fields */
#define MSCAN_RSIDR1_RSIDE_MASK                  0x8u
#define MSCAN_RSIDR1_RSIDE_SHIFT                 3
#define MSCAN_RSIDR1_RSRTR_MASK                  0x10u
#define MSCAN_RSIDR1_RSRTR_SHIFT                 4
#define MSCAN_RSIDR1_RSID2_RSID0_MASK            0xE0u
#define MSCAN_RSIDR1_RSID2_RSID0_SHIFT           5
#define MSCAN_RSIDR1_RSID2_RSID0(x)              (((uint8_t)(((uint8_t)(x))<<MSCAN_RSIDR1_RSID2_RSID0_SHIFT))&MSCAN_RSIDR1_RSID2_RSID0_MASK)
/* REIDR2 Bit Fields */
#define MSCAN_REIDR2_REID14_REID7_MASK           0xFFu
#define MSCAN_REIDR2_REID14_REID7_SHIFT          0
#define MSCAN_REIDR2_REID14_REID7(x)             (((uint8_t)(((uint8_t)(x))<<MSCAN_REIDR2_REID14_REID7_SHIFT))&MSCAN_REIDR2_REID14_REID7_MASK)
/* REIDR3 Bit Fields */
#define MSCAN_REIDR3_RERTR_MASK                  0x1u
#define MSCAN_REIDR3_RERTR_SHIFT                 0
#define MSCAN_REIDR3_REID6_REID0_MASK            0xFEu
#define MSCAN_REIDR3_REID6_REID0_SHIFT           1
#define MSCAN_REIDR3_REID6_REID0(x)              (((uint8_t)(((uint8_t)(x))<<MSCAN_REIDR3_REID6_REID0_SHIFT))&MSCAN_REIDR3_REID6_REID0_MASK)
/* REDSR Bit Fields */
#define MSCAN_REDSR_RDB_MASK                     0xFFu
#define MSCAN_REDSR_RDB_SHIFT                    0
#define MSCAN_REDSR_RDB(x)                       (((uint8_t)(((uint8_t)(x))<<MSCAN_REDSR_RDB_SHIFT))&MSCAN_REDSR_RDB_MASK)
/* RDLR Bit Fields */
#define MSCAN_RDLR_RDLC_MASK                     0xFu
#define MSCAN_RDLR_RDLC_SHIFT                    0
#define MSCAN_RDLR_RDLC(x)                       (((uint8_t)(((uint8_t)(x))<<MSCAN_RDLR_RDLC_SHIFT))&MSCAN_RDLR_RDLC_MASK)
/* RTSRH Bit Fields */
#define MSCAN_RTSRH_RTS_MASK                     0xFFu
#define MSCAN_RTSRH_RTS_SHIFT                    0
#define MSCAN_RTSRH_RTS(x)                       (((uint8_t)(((uint8_t)(x))<<MSCAN_RTSRH_RTS_SHIFT))&MSCAN_RTSRH_RTS_MASK)
/* RTSRL Bit Fields */
#define MSCAN_RTSRL_RTS_MASK                     0xFFu
#define MSCAN_RTSRL_RTS_SHIFT                    0
#define MSCAN_RTSRL_RTS(x)                       (((uint8_t)(((uint8_t)(x))<<MSCAN_RTSRL_RTS_SHIFT))&MSCAN_RTSRL_RTS_MASK)
/* TEIDR0 Bit Fields */
#define MSCAN_TEIDR0_TEID28_TEID21_MASK          0xFFu
#define MSCAN_TEIDR0_TEID28_TEID21_SHIFT         0
#define MSCAN_TEIDR0_TEID28_TEID21(x)            (((uint8_t)(((uint8_t)(x))<<MSCAN_TEIDR0_TEID28_TEID21_SHIFT))&MSCAN_TEIDR0_TEID28_TEID21_MASK)
/* TSIDR0 Bit Fields */
#define MSCAN_TSIDR0_TSID10_TSID3_MASK           0xFFu
#define MSCAN_TSIDR0_TSID10_TSID3_SHIFT          0
#define MSCAN_TSIDR0_TSID10_TSID3(x)             (((uint8_t)(((uint8_t)(x))<<MSCAN_TSIDR0_TSID10_TSID3_SHIFT))&MSCAN_TSIDR0_TSID10_TSID3_MASK)
/* TEIDR1 Bit Fields */
#define MSCAN_TEIDR1_TEID17_TEID15_MASK          0x7u
#define MSCAN_TEIDR1_TEID17_TEID15_SHIFT         0
#define MSCAN_TEIDR1_TEID17_TEID15(x)            (((uint8_t)(((uint8_t)(x))<<MSCAN_TEIDR1_TEID17_TEID15_SHIFT))&MSCAN_TEIDR1_TEID17_TEID15_MASK)
#define MSCAN_TEIDR1_TEIDE_MASK                  0x8u
#define MSCAN_TEIDR1_TEIDE_SHIFT                 3
#define MSCAN_TEIDR1_TSRR_MASK                   0x10u
#define MSCAN_TEIDR1_TSRR_SHIFT                  4
#define MSCAN_TEIDR1_TEID20_TEID18_MASK          0xE0u
#define MSCAN_TEIDR1_TEID20_TEID18_SHIFT         5
#define MSCAN_TEIDR1_TEID20_TEID18(x)            (((uint8_t)(((uint8_t)(x))<<MSCAN_TEIDR1_TEID20_TEID18_SHIFT))&MSCAN_TEIDR1_TEID20_TEID18_MASK)
/* TSIDR1 Bit Fields */
#define MSCAN_TSIDR1_TSIDE_MASK                  0x8u
#define MSCAN_TSIDR1_TSIDE_SHIFT                 3
#define MSCAN_TSIDR1_TSRTR_MASK                  0x10u
#define MSCAN_TSIDR1_TSRTR_SHIFT                 4
#define MSCAN_TSIDR1_TSID2_TSID0_MASK            0xE0u
#define MSCAN_TSIDR1_TSID2_TSID0_SHIFT           5
#define MSCAN_TSIDR1_TSID2_TSID0(x)              (((uint8_t)(((uint8_t)(x))<<MSCAN_TSIDR1_TSID2_TSID0_SHIFT))&MSCAN_TSIDR1_TSID2_TSID0_MASK)
/* TEIDR2 Bit Fields */
#define MSCAN_TEIDR2_TEID14_TEID7_MASK           0xFFu
#define MSCAN_TEIDR2_TEID14_TEID7_SHIFT          0
#define MSCAN_TEIDR2_TEID14_TEID7(x)             (((uint8_t)(((uint8_t)(x))<<MSCAN_TEIDR2_TEID14_TEID7_SHIFT))&MSCAN_TEIDR2_TEID14_TEID7_MASK)
/* TEIDR3 Bit Fields */
#define MSCAN_TEIDR3_TERTR_MASK                  0x1u
#define MSCAN_TEIDR3_TERTR_SHIFT                 0
#define MSCAN_TEIDR3_TEID6_TEID0_MASK            0xFEu
#define MSCAN_TEIDR3_TEID6_TEID0_SHIFT           1
#define MSCAN_TEIDR3_TEID6_TEID0(x)              (((uint8_t)(((uint8_t)(x))<<MSCAN_TEIDR3_TEID6_TEID0_SHIFT))&MSCAN_TEIDR3_TEID6_TEID0_MASK)
/* TEDSR Bit Fields */
#define MSCAN_TEDSR_TDB_MASK                     0xFFu
#define MSCAN_TEDSR_TDB_SHIFT                    0
#define MSCAN_TEDSR_TDB(x)                       (((uint8_t)(((uint8_t)(x))<<MSCAN_TEDSR_TDB_SHIFT))&MSCAN_TEDSR_TDB_MASK)
/* TDLR Bit Fields */
#define MSCAN_TDLR_TDLC_MASK                     0xFu
#define MSCAN_TDLR_TDLC_SHIFT                    0
#define MSCAN_TDLR_TDLC(x)                       (((uint8_t)(((uint8_t)(x))<<MSCAN_TDLR_TDLC_SHIFT))&MSCAN_TDLR_TDLC_MASK)
/* TBPR Bit Fields */
#define MSCAN_TBPR_PRIO_MASK                     0xFFu
#define MSCAN_TBPR_PRIO_SHIFT                    0
#define MSCAN_TBPR_PRIO(x)                       (((uint8_t)(((uint8_t)(x))<<MSCAN_TBPR_PRIO_SHIFT))&MSCAN_TBPR_PRIO_MASK)
/* TTSRH Bit Fields */
#define MSCAN_TTSRH_TTS_MASK                     0xFFu
#define MSCAN_TTSRH_TTS_SHIFT                    0
#define MSCAN_TTSRH_TTS(x)                       (((uint8_t)(((uint8_t)(x))<<MSCAN_TTSRH_TTS_SHIFT))&MSCAN_TTSRH_TTS_MASK)
/* TTSRL Bit Fields */
#define MSCAN_TTSRL_TTS_MASK                     0xFFu
#define MSCAN_TTSRL_TTS_SHIFT                    0
#define MSCAN_TTSRL_TTS(x)                       (((uint8_t)(((uint8_t)(x))<<MSCAN_TTSRL_TTS_SHIFT))&MSCAN_TTSRL_TTS_MASK)

/*!
 * @}
 */ /* end of group MSCAN_Register_Masks */


/* MSCAN - Peripheral instance base addresses */
/** Peripheral MSCAN base pointer */
#define MSCAN_BASE_PTR                           ((MSCAN_MemMapPtr)0x40024000u)
/** Array initializer of MSCAN peripheral base pointers */
#define MSCAN_BASE_PTRS                          { MSCAN_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- MSCAN - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MSCAN_Register_Accessor_Macros MSCAN - Register accessor macros
 * @{
 */


/* MSCAN - Register instance definitions */
/* MSCAN */
#define MSCAN_CANCTL0                            MSCAN_CANCTL0_REG(MSCAN_BASE_PTR)
#define MSCAN_CANCTL1                            MSCAN_CANCTL1_REG(MSCAN_BASE_PTR)
#define MSCAN_CANBTR0                            MSCAN_CANBTR0_REG(MSCAN_BASE_PTR)
#define MSCAN_CANBTR1                            MSCAN_CANBTR1_REG(MSCAN_BASE_PTR)
#define MSCAN_CANRFLG                            MSCAN_CANRFLG_REG(MSCAN_BASE_PTR)
#define MSCAN_CANRIER                            MSCAN_CANRIER_REG(MSCAN_BASE_PTR)
#define MSCAN_CANTFLG                            MSCAN_CANTFLG_REG(MSCAN_BASE_PTR)
#define MSCAN_CANTIER                            MSCAN_CANTIER_REG(MSCAN_BASE_PTR)
#define MSCAN_CANTARQ                            MSCAN_CANTARQ_REG(MSCAN_BASE_PTR)
#define MSCAN_CANTAAK                            MSCAN_CANTAAK_REG(MSCAN_BASE_PTR)
#define MSCAN_CANTBSEL                           MSCAN_CANTBSEL_REG(MSCAN_BASE_PTR)
#define MSCAN_CANIDAC                            MSCAN_CANIDAC_REG(MSCAN_BASE_PTR)
#define MSCAN_CANMISC                            MSCAN_CANMISC_REG(MSCAN_BASE_PTR)
#define MSCAN_CANRXERR                           MSCAN_CANRXERR_REG(MSCAN_BASE_PTR)
#define MSCAN_CANTXERR                           MSCAN_CANTXERR_REG(MSCAN_BASE_PTR)
#define MSCAN_CANIDAR0                           MSCAN_CANIDAR_BANK_1_REG(MSCAN_BASE_PTR,0)
#define MSCAN_CANIDAR1                           MSCAN_CANIDAR_BANK_1_REG(MSCAN_BASE_PTR,1)
#define MSCAN_CANIDAR2                           MSCAN_CANIDAR_BANK_1_REG(MSCAN_BASE_PTR,2)
#define MSCAN_CANIDAR3                           MSCAN_CANIDAR_BANK_1_REG(MSCAN_BASE_PTR,3)
#define MSCAN_CANIDMR0                           MSCAN_CANIDMR_BANK_1_REG(MSCAN_BASE_PTR,0)
#define MSCAN_CANIDMR1                           MSCAN_CANIDMR_BANK_1_REG(MSCAN_BASE_PTR,1)
#define MSCAN_CANIDMR2                           MSCAN_CANIDMR_BANK_1_REG(MSCAN_BASE_PTR,2)
#define MSCAN_CANIDMR3                           MSCAN_CANIDMR_BANK_1_REG(MSCAN_BASE_PTR,3)
#define MSCAN_CANIDAR4                           MSCAN_CANIDAR_BANK_2_REG(MSCAN_BASE_PTR,0)
#define MSCAN_CANIDAR5                           MSCAN_CANIDAR_BANK_2_REG(MSCAN_BASE_PTR,1)
#define MSCAN_CANIDAR6                           MSCAN_CANIDAR_BANK_2_REG(MSCAN_BASE_PTR,2)
#define MSCAN_CANIDAR7                           MSCAN_CANIDAR_BANK_2_REG(MSCAN_BASE_PTR,3)
#define MSCAN_CANIDMR4                           MSCAN_CANIDMR_BANK_2_REG(MSCAN_BASE_PTR,0)
#define MSCAN_CANIDMR5                           MSCAN_CANIDMR_BANK_2_REG(MSCAN_BASE_PTR,1)
#define MSCAN_CANIDMR6                           MSCAN_CANIDMR_BANK_2_REG(MSCAN_BASE_PTR,2)
#define MSCAN_CANIDMR7                           MSCAN_CANIDMR_BANK_2_REG(MSCAN_BASE_PTR,3)
#define MSCAN_REIDR0                             MSCAN_REIDR0_REG(MSCAN_BASE_PTR)
#define MSCAN_RSIDR0                             MSCAN_RSIDR0_REG(MSCAN_BASE_PTR)
#define MSCAN_REIDR1                             MSCAN_REIDR1_REG(MSCAN_BASE_PTR)
#define MSCAN_RSIDR1                             MSCAN_RSIDR1_REG(MSCAN_BASE_PTR)
#define MSCAN_REIDR2                             MSCAN_REIDR2_REG(MSCAN_BASE_PTR)
#define MSCAN_REIDR3                             MSCAN_REIDR3_REG(MSCAN_BASE_PTR)
#define MSCAN_REDSR0                             MSCAN_REDSR_REG(MSCAN_BASE_PTR,0)
#define MSCAN_REDSR1                             MSCAN_REDSR_REG(MSCAN_BASE_PTR,1)
#define MSCAN_REDSR2                             MSCAN_REDSR_REG(MSCAN_BASE_PTR,2)
#define MSCAN_REDSR3                             MSCAN_REDSR_REG(MSCAN_BASE_PTR,3)
#define MSCAN_REDSR4                             MSCAN_REDSR_REG(MSCAN_BASE_PTR,4)
#define MSCAN_REDSR5                             MSCAN_REDSR_REG(MSCAN_BASE_PTR,5)
#define MSCAN_REDSR6                             MSCAN_REDSR_REG(MSCAN_BASE_PTR,6)
#define MSCAN_REDSR7                             MSCAN_REDSR_REG(MSCAN_BASE_PTR,7)
#define MSCAN_RDLR                               MSCAN_RDLR_REG(MSCAN_BASE_PTR)
#define MSCAN_RTSRH                              MSCAN_RTSRH_REG(MSCAN_BASE_PTR)
#define MSCAN_RTSRL                              MSCAN_RTSRL_REG(MSCAN_BASE_PTR)
#define MSCAN_TEIDR0                             MSCAN_TEIDR0_REG(MSCAN_BASE_PTR)
#define MSCAN_TSIDR0                             MSCAN_TSIDR0_REG(MSCAN_BASE_PTR)
#define MSCAN_TEIDR1                             MSCAN_TEIDR1_REG(MSCAN_BASE_PTR)
#define MSCAN_TSIDR1                             MSCAN_TSIDR1_REG(MSCAN_BASE_PTR)
#define MSCAN_TEIDR2                             MSCAN_TEIDR2_REG(MSCAN_BASE_PTR)
#define MSCAN_TEIDR3                             MSCAN_TEIDR3_REG(MSCAN_BASE_PTR)
#define MSCAN_TEDSR0                             MSCAN_TEDSR_REG(MSCAN_BASE_PTR,0)
#define MSCAN_TEDSR1                             MSCAN_TEDSR_REG(MSCAN_BASE_PTR,1)
#define MSCAN_TEDSR2                             MSCAN_TEDSR_REG(MSCAN_BASE_PTR,2)
#define MSCAN_TEDSR3                             MSCAN_TEDSR_REG(MSCAN_BASE_PTR,3)
#define MSCAN_TEDSR4                             MSCAN_TEDSR_REG(MSCAN_BASE_PTR,4)
#define MSCAN_TEDSR5                             MSCAN_TEDSR_REG(MSCAN_BASE_PTR,5)
#define MSCAN_TEDSR6                             MSCAN_TEDSR_REG(MSCAN_BASE_PTR,6)
#define MSCAN_TEDSR7                             MSCAN_TEDSR_REG(MSCAN_BASE_PTR,7)
#define MSCAN_TDLR                               MSCAN_TDLR_REG(MSCAN_BASE_PTR)
#define MSCAN_TBPR                               MSCAN_TBPR_REG(MSCAN_BASE_PTR)
#define MSCAN_TTSRH                              MSCAN_TTSRH_REG(MSCAN_BASE_PTR)
#define MSCAN_TTSRL                              MSCAN_TTSRL_REG(MSCAN_BASE_PTR)

/* MSCAN - Register array accessors */
#define MSCAN_CANIDAR_BANK_1(index)              MSCAN_CANIDAR_BANK_1_REG(MSCAN_BASE_PTR,index)
#define MSCAN_CANIDMR_BANK_1(index)              MSCAN_CANIDMR_BANK_1_REG(MSCAN_BASE_PTR,index)
#define MSCAN_CANIDAR_BANK_2(index)              MSCAN_CANIDAR_BANK_2_REG(MSCAN_BASE_PTR,index)
#define MSCAN_CANIDMR_BANK_2(index)              MSCAN_CANIDMR_BANK_2_REG(MSCAN_BASE_PTR,index)
#define MSCAN_REDSR(index)                       MSCAN_REDSR_REG(MSCAN_BASE_PTR,index)
#define MSCAN_TEDSR(index)                       MSCAN_TEDSR_REG(MSCAN_BASE_PTR,index)

/*!
 * @}
 */ /* end of group MSCAN_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group MSCAN_Peripheral */


/* ----------------------------------------------------------------------------
   -- NV
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Peripheral NV
 * @{
 */

/** NV - Peripheral register structure */
typedef struct NV_MemMap {
  uint8_t BACKKEY0;                                /**< Backdoor Comparison Key 0, offset: 0x0 */
  uint8_t BACKKEY1;                                /**< Backdoor Comparison Key 1, offset: 0x1 */
  uint8_t BACKKEY2;                                /**< Backdoor Comparison Key 2, offset: 0x2 */
  uint8_t BACKKEY3;                                /**< Backdoor Comparison Key 3, offset: 0x3 */
  uint8_t BACKKEY4;                                /**< Backdoor Comparison Key 4, offset: 0x4 */
  uint8_t BACKKEY5;                                /**< Backdoor Comparison Key 5, offset: 0x5 */
  uint8_t BACKKEY6;                                /**< Backdoor Comparison Key 6, offset: 0x6 */
  uint8_t BACKKEY7;                                /**< Backdoor Comparison Key 7, offset: 0x7 */
  uint8_t RESERVED_0[5];
  uint8_t FPROT;                                   /**< Non-volatile P-Flash Protection Register, offset: 0xD */
  uint8_t FSEC;                                    /**< Non-volatile Flash Security Register, offset: 0xE */
  uint8_t FOPT;                                    /**< Non-volatile Flash Option Register, offset: 0xF */
} volatile *NV_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- NV - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Accessor_Macros NV - Register accessor macros
 * @{
 */


/* NV - Register accessors */
#define NV_BACKKEY0_REG(base)                    ((base)->BACKKEY0)
#define NV_BACKKEY1_REG(base)                    ((base)->BACKKEY1)
#define NV_BACKKEY2_REG(base)                    ((base)->BACKKEY2)
#define NV_BACKKEY3_REG(base)                    ((base)->BACKKEY3)
#define NV_BACKKEY4_REG(base)                    ((base)->BACKKEY4)
#define NV_BACKKEY5_REG(base)                    ((base)->BACKKEY5)
#define NV_BACKKEY6_REG(base)                    ((base)->BACKKEY6)
#define NV_BACKKEY7_REG(base)                    ((base)->BACKKEY7)
#define NV_FPROT_REG(base)                       ((base)->FPROT)
#define NV_FSEC_REG(base)                        ((base)->FSEC)
#define NV_FOPT_REG(base)                        ((base)->FOPT)

/*!
 * @}
 */ /* end of group NV_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- NV Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Masks NV Register Masks
 * @{
 */

/* BACKKEY0 Bit Fields */
#define NV_BACKKEY0_KEY_MASK                     0xFFu
#define NV_BACKKEY0_KEY_SHIFT                    0
#define NV_BACKKEY0_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY0_KEY_SHIFT))&NV_BACKKEY0_KEY_MASK)
/* BACKKEY1 Bit Fields */
#define NV_BACKKEY1_KEY_MASK                     0xFFu
#define NV_BACKKEY1_KEY_SHIFT                    0
#define NV_BACKKEY1_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY1_KEY_SHIFT))&NV_BACKKEY1_KEY_MASK)
/* BACKKEY2 Bit Fields */
#define NV_BACKKEY2_KEY_MASK                     0xFFu
#define NV_BACKKEY2_KEY_SHIFT                    0
#define NV_BACKKEY2_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY2_KEY_SHIFT))&NV_BACKKEY2_KEY_MASK)
/* BACKKEY3 Bit Fields */
#define NV_BACKKEY3_KEY_MASK                     0xFFu
#define NV_BACKKEY3_KEY_SHIFT                    0
#define NV_BACKKEY3_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY3_KEY_SHIFT))&NV_BACKKEY3_KEY_MASK)
/* BACKKEY4 Bit Fields */
#define NV_BACKKEY4_KEY_MASK                     0xFFu
#define NV_BACKKEY4_KEY_SHIFT                    0
#define NV_BACKKEY4_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY4_KEY_SHIFT))&NV_BACKKEY4_KEY_MASK)
/* BACKKEY5 Bit Fields */
#define NV_BACKKEY5_KEY_MASK                     0xFFu
#define NV_BACKKEY5_KEY_SHIFT                    0
#define NV_BACKKEY5_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY5_KEY_SHIFT))&NV_BACKKEY5_KEY_MASK)
/* BACKKEY6 Bit Fields */
#define NV_BACKKEY6_KEY_MASK                     0xFFu
#define NV_BACKKEY6_KEY_SHIFT                    0
#define NV_BACKKEY6_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY6_KEY_SHIFT))&NV_BACKKEY6_KEY_MASK)
/* BACKKEY7 Bit Fields */
#define NV_BACKKEY7_KEY_MASK                     0xFFu
#define NV_BACKKEY7_KEY_SHIFT                    0
#define NV_BACKKEY7_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY7_KEY_SHIFT))&NV_BACKKEY7_KEY_MASK)
/* FPROT Bit Fields */
#define NV_FPROT_FPLS_MASK                       0x3u
#define NV_FPROT_FPLS_SHIFT                      0
#define NV_FPROT_FPLS(x)                         (((uint8_t)(((uint8_t)(x))<<NV_FPROT_FPLS_SHIFT))&NV_FPROT_FPLS_MASK)
#define NV_FPROT_FPLDIS_MASK                     0x4u
#define NV_FPROT_FPLDIS_SHIFT                    2
#define NV_FPROT_FPHS_MASK                       0x18u
#define NV_FPROT_FPHS_SHIFT                      3
#define NV_FPROT_FPHS(x)                         (((uint8_t)(((uint8_t)(x))<<NV_FPROT_FPHS_SHIFT))&NV_FPROT_FPHS_MASK)
#define NV_FPROT_FPHDIS_MASK                     0x20u
#define NV_FPROT_FPHDIS_SHIFT                    5
#define NV_FPROT_FPOPEN_MASK                     0x80u
#define NV_FPROT_FPOPEN_SHIFT                    7
/* FSEC Bit Fields */
#define NV_FSEC_SEC_MASK                         0x3u
#define NV_FSEC_SEC_SHIFT                        0
#define NV_FSEC_SEC(x)                           (((uint8_t)(((uint8_t)(x))<<NV_FSEC_SEC_SHIFT))&NV_FSEC_SEC_MASK)
#define NV_FSEC_KEYEN_MASK                       0xC0u
#define NV_FSEC_KEYEN_SHIFT                      6
#define NV_FSEC_KEYEN(x)                         (((uint8_t)(((uint8_t)(x))<<NV_FSEC_KEYEN_SHIFT))&NV_FSEC_KEYEN_MASK)

/*!
 * @}
 */ /* end of group NV_Register_Masks */


/* NV - Peripheral instance base addresses */
/** Peripheral FTMRE_FlashConfig base pointer */
#define FTMRE_FlashConfig_BASE_PTR               ((NV_MemMapPtr)0x400u)
/** Array initializer of NV peripheral base pointers */
#define NV_BASE_PTRS                             { FTMRE_FlashConfig_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- NV - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Accessor_Macros NV - Register accessor macros
 * @{
 */


/* NV - Register instance definitions */
/* FTMRE_FlashConfig */
#define NV_BACKKEY0                              NV_BACKKEY0_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_BACKKEY1                              NV_BACKKEY1_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_BACKKEY2                              NV_BACKKEY2_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_BACKKEY3                              NV_BACKKEY3_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_BACKKEY4                              NV_BACKKEY4_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_BACKKEY5                              NV_BACKKEY5_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_BACKKEY6                              NV_BACKKEY6_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_BACKKEY7                              NV_BACKKEY7_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_FPROT                                 NV_FPROT_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_FSEC                                  NV_FSEC_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_FOPT                                  NV_FOPT_REG(FTMRE_FlashConfig_BASE_PTR)

/*!
 * @}
 */ /* end of group NV_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group NV_Peripheral */


/* ----------------------------------------------------------------------------
   -- NVIC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NVIC_Peripheral NVIC
 * @{
 */

/** NVIC - Peripheral register structure */
typedef struct NVIC_MemMap {
  uint32_t ISER;                                   /**< Interrupt Set Enable Register, offset: 0x0 */
  uint8_t RESERVED_0[124];
  uint32_t ICER;                                   /**< Interrupt Clear Enable Register, offset: 0x80 */
  uint8_t RESERVED_1[124];
  uint32_t ISPR;                                   /**< Interrupt Set Pending Register, offset: 0x100 */
  uint8_t RESERVED_2[124];
  uint32_t ICPR;                                   /**< Interrupt Clear Pending Register, offset: 0x180 */
  uint8_t RESERVED_3[380];
  uint32_t IP[8];                                  /**< Interrupt Priority Register 0..Interrupt Priority Register 7, array offset: 0x300, array step: 0x4 */
} volatile *NVIC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- NVIC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NVIC_Register_Accessor_Macros NVIC - Register accessor macros
 * @{
 */


/* NVIC - Register accessors */
#define NVIC_ISER_REG(base)                      ((base)->ISER)
#define NVIC_ICER_REG(base)                      ((base)->ICER)
#define NVIC_ISPR_REG(base)                      ((base)->ISPR)
#define NVIC_ICPR_REG(base)                      ((base)->ICPR)
#define NVIC_IP_REG(base,index)                  ((base)->IP[index])

/*!
 * @}
 */ /* end of group NVIC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- NVIC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NVIC_Register_Masks NVIC Register Masks
 * @{
 */

/* ISER Bit Fields */
#define NVIC_ISER_SETENA0_MASK                   0x1u
#define NVIC_ISER_SETENA0_SHIFT                  0
#define NVIC_ISER_SETENA1_MASK                   0x2u
#define NVIC_ISER_SETENA1_SHIFT                  1
#define NVIC_ISER_SETENA2_MASK                   0x4u
#define NVIC_ISER_SETENA2_SHIFT                  2
#define NVIC_ISER_SETENA3_MASK                   0x8u
#define NVIC_ISER_SETENA3_SHIFT                  3
#define NVIC_ISER_SETENA4_MASK                   0x10u
#define NVIC_ISER_SETENA4_SHIFT                  4
#define NVIC_ISER_SETENA5_MASK                   0x20u
#define NVIC_ISER_SETENA5_SHIFT                  5
#define NVIC_ISER_SETENA6_MASK                   0x40u
#define NVIC_ISER_SETENA6_SHIFT                  6
#define NVIC_ISER_SETENA7_MASK                   0x80u
#define NVIC_ISER_SETENA7_SHIFT                  7
#define NVIC_ISER_SETENA8_MASK                   0x100u
#define NVIC_ISER_SETENA8_SHIFT                  8
#define NVIC_ISER_SETENA9_MASK                   0x200u
#define NVIC_ISER_SETENA9_SHIFT                  9
#define NVIC_ISER_SETENA10_MASK                  0x400u
#define NVIC_ISER_SETENA10_SHIFT                 10
#define NVIC_ISER_SETENA11_MASK                  0x800u
#define NVIC_ISER_SETENA11_SHIFT                 11
#define NVIC_ISER_SETENA12_MASK                  0x1000u
#define NVIC_ISER_SETENA12_SHIFT                 12
#define NVIC_ISER_SETENA13_MASK                  0x2000u
#define NVIC_ISER_SETENA13_SHIFT                 13
#define NVIC_ISER_SETENA14_MASK                  0x4000u
#define NVIC_ISER_SETENA14_SHIFT                 14
#define NVIC_ISER_SETENA15_MASK                  0x8000u
#define NVIC_ISER_SETENA15_SHIFT                 15
#define NVIC_ISER_SETENA16_MASK                  0x10000u
#define NVIC_ISER_SETENA16_SHIFT                 16
#define NVIC_ISER_SETENA17_MASK                  0x20000u
#define NVIC_ISER_SETENA17_SHIFT                 17
#define NVIC_ISER_SETENA18_MASK                  0x40000u
#define NVIC_ISER_SETENA18_SHIFT                 18
#define NVIC_ISER_SETENA19_MASK                  0x80000u
#define NVIC_ISER_SETENA19_SHIFT                 19
#define NVIC_ISER_SETENA20_MASK                  0x100000u
#define NVIC_ISER_SETENA20_SHIFT                 20
#define NVIC_ISER_SETENA21_MASK                  0x200000u
#define NVIC_ISER_SETENA21_SHIFT                 21
#define NVIC_ISER_SETENA22_MASK                  0x400000u
#define NVIC_ISER_SETENA22_SHIFT                 22
#define NVIC_ISER_SETENA23_MASK                  0x800000u
#define NVIC_ISER_SETENA23_SHIFT                 23
#define NVIC_ISER_SETENA24_MASK                  0x1000000u
#define NVIC_ISER_SETENA24_SHIFT                 24
#define NVIC_ISER_SETENA25_MASK                  0x2000000u
#define NVIC_ISER_SETENA25_SHIFT                 25
#define NVIC_ISER_SETENA26_MASK                  0x4000000u
#define NVIC_ISER_SETENA26_SHIFT                 26
#define NVIC_ISER_SETENA27_MASK                  0x8000000u
#define NVIC_ISER_SETENA27_SHIFT                 27
#define NVIC_ISER_SETENA28_MASK                  0x10000000u
#define NVIC_ISER_SETENA28_SHIFT                 28
#define NVIC_ISER_SETENA29_MASK                  0x20000000u
#define NVIC_ISER_SETENA29_SHIFT                 29
#define NVIC_ISER_SETENA30_MASK                  0x40000000u
#define NVIC_ISER_SETENA30_SHIFT                 30
#define NVIC_ISER_SETENA31_MASK                  0x80000000u
#define NVIC_ISER_SETENA31_SHIFT                 31
/* ICER Bit Fields */
#define NVIC_ICER_CLRENA0_MASK                   0x1u
#define NVIC_ICER_CLRENA0_SHIFT                  0
#define NVIC_ICER_CLRENA1_MASK                   0x2u
#define NVIC_ICER_CLRENA1_SHIFT                  1
#define NVIC_ICER_CLRENA2_MASK                   0x4u
#define NVIC_ICER_CLRENA2_SHIFT                  2
#define NVIC_ICER_CLRENA3_MASK                   0x8u
#define NVIC_ICER_CLRENA3_SHIFT                  3
#define NVIC_ICER_CLRENA4_MASK                   0x10u
#define NVIC_ICER_CLRENA4_SHIFT                  4
#define NVIC_ICER_CLRENA5_MASK                   0x20u
#define NVIC_ICER_CLRENA5_SHIFT                  5
#define NVIC_ICER_CLRENA6_MASK                   0x40u
#define NVIC_ICER_CLRENA6_SHIFT                  6
#define NVIC_ICER_CLRENA7_MASK                   0x80u
#define NVIC_ICER_CLRENA7_SHIFT                  7
#define NVIC_ICER_CLRENA8_MASK                   0x100u
#define NVIC_ICER_CLRENA8_SHIFT                  8
#define NVIC_ICER_CLRENA9_MASK                   0x200u
#define NVIC_ICER_CLRENA9_SHIFT                  9
#define NVIC_ICER_CLRENA10_MASK                  0x400u
#define NVIC_ICER_CLRENA10_SHIFT                 10
#define NVIC_ICER_CLRENA11_MASK                  0x800u
#define NVIC_ICER_CLRENA11_SHIFT                 11
#define NVIC_ICER_CLRENA12_MASK                  0x1000u
#define NVIC_ICER_CLRENA12_SHIFT                 12
#define NVIC_ICER_CLRENA13_MASK                  0x2000u
#define NVIC_ICER_CLRENA13_SHIFT                 13
#define NVIC_ICER_CLRENA14_MASK                  0x4000u
#define NVIC_ICER_CLRENA14_SHIFT                 14
#define NVIC_ICER_CLRENA15_MASK                  0x8000u
#define NVIC_ICER_CLRENA15_SHIFT                 15
#define NVIC_ICER_CLRENA16_MASK                  0x10000u
#define NVIC_ICER_CLRENA16_SHIFT                 16
#define NVIC_ICER_CLRENA17_MASK                  0x20000u
#define NVIC_ICER_CLRENA17_SHIFT                 17
#define NVIC_ICER_CLRENA18_MASK                  0x40000u
#define NVIC_ICER_CLRENA18_SHIFT                 18
#define NVIC_ICER_CLRENA19_MASK                  0x80000u
#define NVIC_ICER_CLRENA19_SHIFT                 19
#define NVIC_ICER_CLRENA20_MASK                  0x100000u
#define NVIC_ICER_CLRENA20_SHIFT                 20
#define NVIC_ICER_CLRENA21_MASK                  0x200000u
#define NVIC_ICER_CLRENA21_SHIFT                 21
#define NVIC_ICER_CLRENA22_MASK                  0x400000u
#define NVIC_ICER_CLRENA22_SHIFT                 22
#define NVIC_ICER_CLRENA23_MASK                  0x800000u
#define NVIC_ICER_CLRENA23_SHIFT                 23
#define NVIC_ICER_CLRENA24_MASK                  0x1000000u
#define NVIC_ICER_CLRENA24_SHIFT                 24
#define NVIC_ICER_CLRENA25_MASK                  0x2000000u
#define NVIC_ICER_CLRENA25_SHIFT                 25
#define NVIC_ICER_CLRENA26_MASK                  0x4000000u
#define NVIC_ICER_CLRENA26_SHIFT                 26
#define NVIC_ICER_CLRENA27_MASK                  0x8000000u
#define NVIC_ICER_CLRENA27_SHIFT                 27
#define NVIC_ICER_CLRENA28_MASK                  0x10000000u
#define NVIC_ICER_CLRENA28_SHIFT                 28
#define NVIC_ICER_CLRENA29_MASK                  0x20000000u
#define NVIC_ICER_CLRENA29_SHIFT                 29
#define NVIC_ICER_CLRENA30_MASK                  0x40000000u
#define NVIC_ICER_CLRENA30_SHIFT                 30
#define NVIC_ICER_CLRENA31_MASK                  0x80000000u
#define NVIC_ICER_CLRENA31_SHIFT                 31
/* ISPR Bit Fields */
#define NVIC_ISPR_SETPEND0_MASK                  0x1u
#define NVIC_ISPR_SETPEND0_SHIFT                 0
#define NVIC_ISPR_SETPEND1_MASK                  0x2u
#define NVIC_ISPR_SETPEND1_SHIFT                 1
#define NVIC_ISPR_SETPEND2_MASK                  0x4u
#define NVIC_ISPR_SETPEND2_SHIFT                 2
#define NVIC_ISPR_SETPEND3_MASK                  0x8u
#define NVIC_ISPR_SETPEND3_SHIFT                 3
#define NVIC_ISPR_SETPEND4_MASK                  0x10u
#define NVIC_ISPR_SETPEND4_SHIFT                 4
#define NVIC_ISPR_SETPEND5_MASK                  0x20u
#define NVIC_ISPR_SETPEND5_SHIFT                 5
#define NVIC_ISPR_SETPEND6_MASK                  0x40u
#define NVIC_ISPR_SETPEND6_SHIFT                 6
#define NVIC_ISPR_SETPEND7_MASK                  0x80u
#define NVIC_ISPR_SETPEND7_SHIFT                 7
#define NVIC_ISPR_SETPEND8_MASK                  0x100u
#define NVIC_ISPR_SETPEND8_SHIFT                 8
#define NVIC_ISPR_SETPEND9_MASK                  0x200u
#define NVIC_ISPR_SETPEND9_SHIFT                 9
#define NVIC_ISPR_SETPEND10_MASK                 0x400u
#define NVIC_ISPR_SETPEND10_SHIFT                10
#define NVIC_ISPR_SETPEND11_MASK                 0x800u
#define NVIC_ISPR_SETPEND11_SHIFT                11
#define NVIC_ISPR_SETPEND12_MASK                 0x1000u
#define NVIC_ISPR_SETPEND12_SHIFT                12
#define NVIC_ISPR_SETPEND13_MASK                 0x2000u
#define NVIC_ISPR_SETPEND13_SHIFT                13
#define NVIC_ISPR_SETPEND14_MASK                 0x4000u
#define NVIC_ISPR_SETPEND14_SHIFT                14
#define NVIC_ISPR_SETPEND15_MASK                 0x8000u
#define NVIC_ISPR_SETPEND15_SHIFT                15
#define NVIC_ISPR_SETPEND16_MASK                 0x10000u
#define NVIC_ISPR_SETPEND16_SHIFT                16
#define NVIC_ISPR_SETPEND17_MASK                 0x20000u
#define NVIC_ISPR_SETPEND17_SHIFT                17
#define NVIC_ISPR_SETPEND18_MASK                 0x40000u
#define NVIC_ISPR_SETPEND18_SHIFT                18
#define NVIC_ISPR_SETPEND19_MASK                 0x80000u
#define NVIC_ISPR_SETPEND19_SHIFT                19
#define NVIC_ISPR_SETPEND20_MASK                 0x100000u
#define NVIC_ISPR_SETPEND20_SHIFT                20
#define NVIC_ISPR_SETPEND21_MASK                 0x200000u
#define NVIC_ISPR_SETPEND21_SHIFT                21
#define NVIC_ISPR_SETPEND22_MASK                 0x400000u
#define NVIC_ISPR_SETPEND22_SHIFT                22
#define NVIC_ISPR_SETPEND23_MASK                 0x800000u
#define NVIC_ISPR_SETPEND23_SHIFT                23
#define NVIC_ISPR_SETPEND24_MASK                 0x1000000u
#define NVIC_ISPR_SETPEND24_SHIFT                24
#define NVIC_ISPR_SETPEND25_MASK                 0x2000000u
#define NVIC_ISPR_SETPEND25_SHIFT                25
#define NVIC_ISPR_SETPEND26_MASK                 0x4000000u
#define NVIC_ISPR_SETPEND26_SHIFT                26
#define NVIC_ISPR_SETPEND27_MASK                 0x8000000u
#define NVIC_ISPR_SETPEND27_SHIFT                27
#define NVIC_ISPR_SETPEND28_MASK                 0x10000000u
#define NVIC_ISPR_SETPEND28_SHIFT                28
#define NVIC_ISPR_SETPEND29_MASK                 0x20000000u
#define NVIC_ISPR_SETPEND29_SHIFT                29
#define NVIC_ISPR_SETPEND30_MASK                 0x40000000u
#define NVIC_ISPR_SETPEND30_SHIFT                30
#define NVIC_ISPR_SETPEND31_MASK                 0x80000000u
#define NVIC_ISPR_SETPEND31_SHIFT                31
/* ICPR Bit Fields */
#define NVIC_ICPR_CLRPEND0_MASK                  0x1u
#define NVIC_ICPR_CLRPEND0_SHIFT                 0
#define NVIC_ICPR_CLRPEND1_MASK                  0x2u
#define NVIC_ICPR_CLRPEND1_SHIFT                 1
#define NVIC_ICPR_CLRPEND2_MASK                  0x4u
#define NVIC_ICPR_CLRPEND2_SHIFT                 2
#define NVIC_ICPR_CLRPEND3_MASK                  0x8u
#define NVIC_ICPR_CLRPEND3_SHIFT                 3
#define NVIC_ICPR_CLRPEND4_MASK                  0x10u
#define NVIC_ICPR_CLRPEND4_SHIFT                 4
#define NVIC_ICPR_CLRPEND5_MASK                  0x20u
#define NVIC_ICPR_CLRPEND5_SHIFT                 5
#define NVIC_ICPR_CLRPEND6_MASK                  0x40u
#define NVIC_ICPR_CLRPEND6_SHIFT                 6
#define NVIC_ICPR_CLRPEND7_MASK                  0x80u
#define NVIC_ICPR_CLRPEND7_SHIFT                 7
#define NVIC_ICPR_CLRPEND8_MASK                  0x100u
#define NVIC_ICPR_CLRPEND8_SHIFT                 8
#define NVIC_ICPR_CLRPEND9_MASK                  0x200u
#define NVIC_ICPR_CLRPEND9_SHIFT                 9
#define NVIC_ICPR_CLRPEND10_MASK                 0x400u
#define NVIC_ICPR_CLRPEND10_SHIFT                10
#define NVIC_ICPR_CLRPEND11_MASK                 0x800u
#define NVIC_ICPR_CLRPEND11_SHIFT                11
#define NVIC_ICPR_CLRPEND12_MASK                 0x1000u
#define NVIC_ICPR_CLRPEND12_SHIFT                12
#define NVIC_ICPR_CLRPEND13_MASK                 0x2000u
#define NVIC_ICPR_CLRPEND13_SHIFT                13
#define NVIC_ICPR_CLRPEND14_MASK                 0x4000u
#define NVIC_ICPR_CLRPEND14_SHIFT                14
#define NVIC_ICPR_CLRPEND15_MASK                 0x8000u
#define NVIC_ICPR_CLRPEND15_SHIFT                15
#define NVIC_ICPR_CLRPEND16_MASK                 0x10000u
#define NVIC_ICPR_CLRPEND16_SHIFT                16
#define NVIC_ICPR_CLRPEND17_MASK                 0x20000u
#define NVIC_ICPR_CLRPEND17_SHIFT                17
#define NVIC_ICPR_CLRPEND18_MASK                 0x40000u
#define NVIC_ICPR_CLRPEND18_SHIFT                18
#define NVIC_ICPR_CLRPEND19_MASK                 0x80000u
#define NVIC_ICPR_CLRPEND19_SHIFT                19
#define NVIC_ICPR_CLRPEND20_MASK                 0x100000u
#define NVIC_ICPR_CLRPEND20_SHIFT                20
#define NVIC_ICPR_CLRPEND21_MASK                 0x200000u
#define NVIC_ICPR_CLRPEND21_SHIFT                21
#define NVIC_ICPR_CLRPEND22_MASK                 0x400000u
#define NVIC_ICPR_CLRPEND22_SHIFT                22
#define NVIC_ICPR_CLRPEND23_MASK                 0x800000u
#define NVIC_ICPR_CLRPEND23_SHIFT                23
#define NVIC_ICPR_CLRPEND24_MASK                 0x1000000u
#define NVIC_ICPR_CLRPEND24_SHIFT                24
#define NVIC_ICPR_CLRPEND25_MASK                 0x2000000u
#define NVIC_ICPR_CLRPEND25_SHIFT                25
#define NVIC_ICPR_CLRPEND26_MASK                 0x4000000u
#define NVIC_ICPR_CLRPEND26_SHIFT                26
#define NVIC_ICPR_CLRPEND27_MASK                 0x8000000u
#define NVIC_ICPR_CLRPEND27_SHIFT                27
#define NVIC_ICPR_CLRPEND28_MASK                 0x10000000u
#define NVIC_ICPR_CLRPEND28_SHIFT                28
#define NVIC_ICPR_CLRPEND29_MASK                 0x20000000u
#define NVIC_ICPR_CLRPEND29_SHIFT                29
#define NVIC_ICPR_CLRPEND30_MASK                 0x40000000u
#define NVIC_ICPR_CLRPEND30_SHIFT                30
#define NVIC_ICPR_CLRPEND31_MASK                 0x80000000u
#define NVIC_ICPR_CLRPEND31_SHIFT                31
/* IP Bit Fields */
#define NVIC_IP_PRI_0_MASK                       0xC0u
#define NVIC_IP_PRI_0_SHIFT                      6
#define NVIC_IP_PRI_0(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_0_SHIFT))&NVIC_IP_PRI_0_MASK)
#define NVIC_IP_PRI_28_MASK                      0xC0u
#define NVIC_IP_PRI_28_SHIFT                     6
#define NVIC_IP_PRI_28(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_28_SHIFT))&NVIC_IP_PRI_28_MASK)
#define NVIC_IP_PRI_24_MASK                      0xC0u
#define NVIC_IP_PRI_24_SHIFT                     6
#define NVIC_IP_PRI_24(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_24_SHIFT))&NVIC_IP_PRI_24_MASK)
#define NVIC_IP_PRI_20_MASK                      0xC0u
#define NVIC_IP_PRI_20_SHIFT                     6
#define NVIC_IP_PRI_20(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_20_SHIFT))&NVIC_IP_PRI_20_MASK)
#define NVIC_IP_PRI_4_MASK                       0xC0u
#define NVIC_IP_PRI_4_SHIFT                      6
#define NVIC_IP_PRI_4(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_4_SHIFT))&NVIC_IP_PRI_4_MASK)
#define NVIC_IP_PRI_16_MASK                      0xC0u
#define NVIC_IP_PRI_16_SHIFT                     6
#define NVIC_IP_PRI_16(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_16_SHIFT))&NVIC_IP_PRI_16_MASK)
#define NVIC_IP_PRI_12_MASK                      0xC0u
#define NVIC_IP_PRI_12_SHIFT                     6
#define NVIC_IP_PRI_12(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_12_SHIFT))&NVIC_IP_PRI_12_MASK)
#define NVIC_IP_PRI_8_MASK                       0xC0u
#define NVIC_IP_PRI_8_SHIFT                      6
#define NVIC_IP_PRI_8(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_8_SHIFT))&NVIC_IP_PRI_8_MASK)
#define NVIC_IP_PRI_13_MASK                      0xC000u
#define NVIC_IP_PRI_13_SHIFT                     14
#define NVIC_IP_PRI_13(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_13_SHIFT))&NVIC_IP_PRI_13_MASK)
#define NVIC_IP_PRI_21_MASK                      0xC000u
#define NVIC_IP_PRI_21_SHIFT                     14
#define NVIC_IP_PRI_21(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_21_SHIFT))&NVIC_IP_PRI_21_MASK)
#define NVIC_IP_PRI_29_MASK                      0xC000u
#define NVIC_IP_PRI_29_SHIFT                     14
#define NVIC_IP_PRI_29(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_29_SHIFT))&NVIC_IP_PRI_29_MASK)
#define NVIC_IP_PRI_1_MASK                       0xC000u
#define NVIC_IP_PRI_1_SHIFT                      14
#define NVIC_IP_PRI_1(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_1_SHIFT))&NVIC_IP_PRI_1_MASK)
#define NVIC_IP_PRI_9_MASK                       0xC000u
#define NVIC_IP_PRI_9_SHIFT                      14
#define NVIC_IP_PRI_9(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_9_SHIFT))&NVIC_IP_PRI_9_MASK)
#define NVIC_IP_PRI_17_MASK                      0xC000u
#define NVIC_IP_PRI_17_SHIFT                     14
#define NVIC_IP_PRI_17(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_17_SHIFT))&NVIC_IP_PRI_17_MASK)
#define NVIC_IP_PRI_25_MASK                      0xC000u
#define NVIC_IP_PRI_25_SHIFT                     14
#define NVIC_IP_PRI_25(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_25_SHIFT))&NVIC_IP_PRI_25_MASK)
#define NVIC_IP_PRI_5_MASK                       0xC000u
#define NVIC_IP_PRI_5_SHIFT                      14
#define NVIC_IP_PRI_5(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_5_SHIFT))&NVIC_IP_PRI_5_MASK)
#define NVIC_IP_PRI_2_MASK                       0xC00000u
#define NVIC_IP_PRI_2_SHIFT                      22
#define NVIC_IP_PRI_2(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_2_SHIFT))&NVIC_IP_PRI_2_MASK)
#define NVIC_IP_PRI_26_MASK                      0xC00000u
#define NVIC_IP_PRI_26_SHIFT                     22
#define NVIC_IP_PRI_26(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_26_SHIFT))&NVIC_IP_PRI_26_MASK)
#define NVIC_IP_PRI_18_MASK                      0xC00000u
#define NVIC_IP_PRI_18_SHIFT                     22
#define NVIC_IP_PRI_18(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_18_SHIFT))&NVIC_IP_PRI_18_MASK)
#define NVIC_IP_PRI_14_MASK                      0xC00000u
#define NVIC_IP_PRI_14_SHIFT                     22
#define NVIC_IP_PRI_14(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_14_SHIFT))&NVIC_IP_PRI_14_MASK)
#define NVIC_IP_PRI_6_MASK                       0xC00000u
#define NVIC_IP_PRI_6_SHIFT                      22
#define NVIC_IP_PRI_6(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_6_SHIFT))&NVIC_IP_PRI_6_MASK)
#define NVIC_IP_PRI_30_MASK                      0xC00000u
#define NVIC_IP_PRI_30_SHIFT                     22
#define NVIC_IP_PRI_30(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_30_SHIFT))&NVIC_IP_PRI_30_MASK)
#define NVIC_IP_PRI_22_MASK                      0xC00000u
#define NVIC_IP_PRI_22_SHIFT                     22
#define NVIC_IP_PRI_22(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_22_SHIFT))&NVIC_IP_PRI_22_MASK)
#define NVIC_IP_PRI_10_MASK                      0xC00000u
#define NVIC_IP_PRI_10_SHIFT                     22
#define NVIC_IP_PRI_10(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_10_SHIFT))&NVIC_IP_PRI_10_MASK)
#define NVIC_IP_PRI_31_MASK                      0xC0000000u
#define NVIC_IP_PRI_31_SHIFT                     30
#define NVIC_IP_PRI_31(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_31_SHIFT))&NVIC_IP_PRI_31_MASK)
#define NVIC_IP_PRI_27_MASK                      0xC0000000u
#define NVIC_IP_PRI_27_SHIFT                     30
#define NVIC_IP_PRI_27(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_27_SHIFT))&NVIC_IP_PRI_27_MASK)
#define NVIC_IP_PRI_23_MASK                      0xC0000000u
#define NVIC_IP_PRI_23_SHIFT                     30
#define NVIC_IP_PRI_23(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_23_SHIFT))&NVIC_IP_PRI_23_MASK)
#define NVIC_IP_PRI_3_MASK                       0xC0000000u
#define NVIC_IP_PRI_3_SHIFT                      30
#define NVIC_IP_PRI_3(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_3_SHIFT))&NVIC_IP_PRI_3_MASK)
#define NVIC_IP_PRI_19_MASK                      0xC0000000u
#define NVIC_IP_PRI_19_SHIFT                     30
#define NVIC_IP_PRI_19(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_19_SHIFT))&NVIC_IP_PRI_19_MASK)
#define NVIC_IP_PRI_15_MASK                      0xC0000000u
#define NVIC_IP_PRI_15_SHIFT                     30
#define NVIC_IP_PRI_15(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_15_SHIFT))&NVIC_IP_PRI_15_MASK)
#define NVIC_IP_PRI_11_MASK                      0xC0000000u
#define NVIC_IP_PRI_11_SHIFT                     30
#define NVIC_IP_PRI_11(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_11_SHIFT))&NVIC_IP_PRI_11_MASK)
#define NVIC_IP_PRI_7_MASK                       0xC0000000u
#define NVIC_IP_PRI_7_SHIFT                      30
#define NVIC_IP_PRI_7(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_7_SHIFT))&NVIC_IP_PRI_7_MASK)

/*!
 * @}
 */ /* end of group NVIC_Register_Masks */


/* NVIC - Peripheral instance base addresses */
/** Peripheral NVIC base pointer */
#define NVIC_BASE_PTR                            ((NVIC_MemMapPtr)0xE000E100u)
/** Array initializer of NVIC peripheral base pointers */
#define NVIC_BASE_PTRS                           { NVIC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- NVIC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NVIC_Register_Accessor_Macros NVIC - Register accessor macros
 * @{
 */


/* NVIC - Register instance definitions */
/* NVIC */
#define NVIC_ISER                                NVIC_ISER_REG(NVIC_BASE_PTR)
#define NVIC_ICER                                NVIC_ICER_REG(NVIC_BASE_PTR)
#define NVIC_ISPR                                NVIC_ISPR_REG(NVIC_BASE_PTR)
#define NVIC_ICPR                                NVIC_ICPR_REG(NVIC_BASE_PTR)
#define NVIC_IPR0                                NVIC_IP_REG(NVIC_BASE_PTR,0)
#define NVIC_IPR1                                NVIC_IP_REG(NVIC_BASE_PTR,1)
#define NVIC_IPR2                                NVIC_IP_REG(NVIC_BASE_PTR,2)
#define NVIC_IPR3                                NVIC_IP_REG(NVIC_BASE_PTR,3)
#define NVIC_IPR4                                NVIC_IP_REG(NVIC_BASE_PTR,4)
#define NVIC_IPR5                                NVIC_IP_REG(NVIC_BASE_PTR,5)
#define NVIC_IPR6                                NVIC_IP_REG(NVIC_BASE_PTR,6)
#define NVIC_IPR7                                NVIC_IP_REG(NVIC_BASE_PTR,7)

/* NVIC - Register array accessors */
#define NVIC_IP(index)                           NVIC_IP_REG(NVIC_BASE_PTR,index)

/*!
 * @}
 */ /* end of group NVIC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group NVIC_Peripheral */


/* ----------------------------------------------------------------------------
   -- OSC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Peripheral OSC
 * @{
 */

/** OSC - Peripheral register structure */
typedef struct OSC_MemMap {
  uint8_t CR;                                      /**< OSC Control Register, offset: 0x0 */
} volatile *OSC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- OSC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Accessor_Macros OSC - Register accessor macros
 * @{
 */


/* OSC - Register accessors */
#define OSC_CR_REG(base)                         ((base)->CR)

/*!
 * @}
 */ /* end of group OSC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- OSC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Masks OSC Register Masks
 * @{
 */

/* CR Bit Fields */
#define OSC_CR_OSCINIT_MASK                      0x1u
#define OSC_CR_OSCINIT_SHIFT                     0
#define OSC_CR_HGO_MASK                          0x2u
#define OSC_CR_HGO_SHIFT                         1
#define OSC_CR_RANGE_MASK                        0x4u
#define OSC_CR_RANGE_SHIFT                       2
#define OSC_CR_OSCOS_MASK                        0x10u
#define OSC_CR_OSCOS_SHIFT                       4
#define OSC_CR_OSCSTEN_MASK                      0x20u
#define OSC_CR_OSCSTEN_SHIFT                     5
#define OSC_CR_OSCEN_MASK                        0x80u
#define OSC_CR_OSCEN_SHIFT                       7

/*!
 * @}
 */ /* end of group OSC_Register_Masks */


/* OSC - Peripheral instance base addresses */
/** Peripheral OSC base pointer */
#define OSC_BASE_PTR                             ((OSC_MemMapPtr)0x40065000u)
/** Array initializer of OSC peripheral base pointers */
#define OSC_BASE_PTRS                            { OSC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- OSC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Accessor_Macros OSC - Register accessor macros
 * @{
 */


/* OSC - Register instance definitions */
/* OSC */
#define OSC_CR                                   OSC_CR_REG(OSC_BASE_PTR)

/*!
 * @}
 */ /* end of group OSC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group OSC_Peripheral */


/* ----------------------------------------------------------------------------
   -- PIT
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Peripheral PIT
 * @{
 */

/** PIT - Peripheral register structure */
typedef struct PIT_MemMap {
  uint32_t MCR;                                    /**< PIT Module Control Register, offset: 0x0 */
  uint8_t RESERVED_0[252];
  struct {                                         /* offset: 0x100, array step: 0x10 */
    uint32_t LDVAL;                                  /**< Timer Load Value Register, array offset: 0x100, array step: 0x10 */
    uint32_t CVAL;                                   /**< Current Timer Value Register, array offset: 0x104, array step: 0x10 */
    uint32_t TCTRL;                                  /**< Timer Control Register, array offset: 0x108, array step: 0x10 */
    uint32_t TFLG;                                   /**< Timer Flag Register, array offset: 0x10C, array step: 0x10 */
  } CHANNEL[2];
} volatile *PIT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PIT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Accessor_Macros PIT - Register accessor macros
 * @{
 */


/* PIT - Register accessors */
#define PIT_MCR_REG(base)                        ((base)->MCR)
#define PIT_LDVAL_REG(base,index)                ((base)->CHANNEL[index].LDVAL)
#define PIT_CVAL_REG(base,index)                 ((base)->CHANNEL[index].CVAL)
#define PIT_TCTRL_REG(base,index)                ((base)->CHANNEL[index].TCTRL)
#define PIT_TFLG_REG(base,index)                 ((base)->CHANNEL[index].TFLG)

/*!
 * @}
 */ /* end of group PIT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PIT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Masks PIT Register Masks
 * @{
 */

/* MCR Bit Fields */
#define PIT_MCR_FRZ_MASK                         0x1u
#define PIT_MCR_FRZ_SHIFT                        0
#define PIT_MCR_MDIS_MASK                        0x2u
#define PIT_MCR_MDIS_SHIFT                       1
/* LDVAL Bit Fields */
#define PIT_LDVAL_TSV_MASK                       0xFFFFFFFFu
#define PIT_LDVAL_TSV_SHIFT                      0
#define PIT_LDVAL_TSV(x)                         (((uint32_t)(((uint32_t)(x))<<PIT_LDVAL_TSV_SHIFT))&PIT_LDVAL_TSV_MASK)
/* CVAL Bit Fields */
#define PIT_CVAL_TVL_MASK                        0xFFFFFFFFu
#define PIT_CVAL_TVL_SHIFT                       0
#define PIT_CVAL_TVL(x)                          (((uint32_t)(((uint32_t)(x))<<PIT_CVAL_TVL_SHIFT))&PIT_CVAL_TVL_MASK)
/* TCTRL Bit Fields */
#define PIT_TCTRL_TEN_MASK                       0x1u
#define PIT_TCTRL_TEN_SHIFT                      0
#define PIT_TCTRL_TIE_MASK                       0x2u
#define PIT_TCTRL_TIE_SHIFT                      1
#define PIT_TCTRL_CHN_MASK                       0x4u
#define PIT_TCTRL_CHN_SHIFT                      2
/* TFLG Bit Fields */
#define PIT_TFLG_TIF_MASK                        0x1u
#define PIT_TFLG_TIF_SHIFT                       0

/*!
 * @}
 */ /* end of group PIT_Register_Masks */


/* PIT - Peripheral instance base addresses */
/** Peripheral PIT base pointer */
#define PIT_BASE_PTR                             ((PIT_MemMapPtr)0x40037000u)
/** Array initializer of PIT peripheral base pointers */
#define PIT_BASE_PTRS                            { PIT_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- PIT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Accessor_Macros PIT - Register accessor macros
 * @{
 */


/* PIT - Register instance definitions */
/* PIT */
#define PIT_MCR                                  PIT_MCR_REG(PIT_BASE_PTR)
#define PIT_LDVAL0                               PIT_LDVAL_REG(PIT_BASE_PTR,0)
#define PIT_CVAL0                                PIT_CVAL_REG(PIT_BASE_PTR,0)
#define PIT_TCTRL0                               PIT_TCTRL_REG(PIT_BASE_PTR,0)
#define PIT_TFLG0                                PIT_TFLG_REG(PIT_BASE_PTR,0)
#define PIT_LDVAL1                               PIT_LDVAL_REG(PIT_BASE_PTR,1)
#define PIT_CVAL1                                PIT_CVAL_REG(PIT_BASE_PTR,1)
#define PIT_TCTRL1                               PIT_TCTRL_REG(PIT_BASE_PTR,1)
#define PIT_TFLG1                                PIT_TFLG_REG(PIT_BASE_PTR,1)

/* PIT - Register array accessors */
#define PIT_LDVAL(index)                         PIT_LDVAL_REG(PIT_BASE_PTR,index)
#define PIT_CVAL(index)                          PIT_CVAL_REG(PIT_BASE_PTR,index)
#define PIT_TCTRL(index)                         PIT_TCTRL_REG(PIT_BASE_PTR,index)
#define PIT_TFLG(index)                          PIT_TFLG_REG(PIT_BASE_PTR,index)

/*!
 * @}
 */ /* end of group PIT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group PIT_Peripheral */


/* ----------------------------------------------------------------------------
   -- PMC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Peripheral PMC
 * @{
 */

/** PMC - Peripheral register structure */
typedef struct PMC_MemMap {
  uint8_t SPMSC1;                                  /**< System Power Management Status and Control 1 Register, offset: 0x0 */
  uint8_t SPMSC2;                                  /**< System Power Management Status and Control 2 Register, offset: 0x1 */
} volatile *PMC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Accessor_Macros PMC - Register accessor macros
 * @{
 */


/* PMC - Register accessors */
#define PMC_SPMSC1_REG(base)                     ((base)->SPMSC1)
#define PMC_SPMSC2_REG(base)                     ((base)->SPMSC2)

/*!
 * @}
 */ /* end of group PMC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Masks PMC Register Masks
 * @{
 */

/* SPMSC1 Bit Fields */
#define PMC_SPMSC1_BGBE_MASK                     0x1u
#define PMC_SPMSC1_BGBE_SHIFT                    0
#define PMC_SPMSC1_LVDE_MASK                     0x4u
#define PMC_SPMSC1_LVDE_SHIFT                    2
#define PMC_SPMSC1_LVDSE_MASK                    0x8u
#define PMC_SPMSC1_LVDSE_SHIFT                   3
#define PMC_SPMSC1_LVDRE_MASK                    0x10u
#define PMC_SPMSC1_LVDRE_SHIFT                   4
#define PMC_SPMSC1_LVWIE_MASK                    0x20u
#define PMC_SPMSC1_LVWIE_SHIFT                   5
#define PMC_SPMSC1_LVWACK_MASK                   0x40u
#define PMC_SPMSC1_LVWACK_SHIFT                  6
#define PMC_SPMSC1_LVWF_MASK                     0x80u
#define PMC_SPMSC1_LVWF_SHIFT                    7
/* SPMSC2 Bit Fields */
#define PMC_SPMSC2_LVWV_MASK                     0x30u
#define PMC_SPMSC2_LVWV_SHIFT                    4
#define PMC_SPMSC2_LVWV(x)                       (((uint8_t)(((uint8_t)(x))<<PMC_SPMSC2_LVWV_SHIFT))&PMC_SPMSC2_LVWV_MASK)
#define PMC_SPMSC2_LVDV_MASK                     0x40u
#define PMC_SPMSC2_LVDV_SHIFT                    6

/*!
 * @}
 */ /* end of group PMC_Register_Masks */


/* PMC - Peripheral instance base addresses */
/** Peripheral PMC base pointer */
#define PMC_BASE_PTR                             ((PMC_MemMapPtr)0x4007D000u)
/** Array initializer of PMC peripheral base pointers */
#define PMC_BASE_PTRS                            { PMC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- PMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Accessor_Macros PMC - Register accessor macros
 * @{
 */


/* PMC - Register instance definitions */
/* PMC */
#define PMC_SPMSC1                               PMC_SPMSC1_REG(PMC_BASE_PTR)
#define PMC_SPMSC2                               PMC_SPMSC2_REG(PMC_BASE_PTR)

/*!
 * @}
 */ /* end of group PMC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group PMC_Peripheral */


/* ----------------------------------------------------------------------------
   -- PORT
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Peripheral PORT
 * @{
 */

/** PORT - Peripheral register structure */
typedef struct PORT_MemMap {
  uint32_t IOFLT0;                                 /**< Port Filter Register 0, offset: 0x0 */
  uint32_t IOFLT1;                                 /**< Port Filter Register 1, offset: 0x4 */
  uint32_t PUE0;                                   /**< Port Pullup Enable Register 0, offset: 0x8 */
  uint32_t PUE1;                                   /**< Port Pullup Enable Register 1, offset: 0xC */
  uint32_t PUE2;                                   /**< Port Pullup Enable Register 2, offset: 0x10 */
  uint32_t HDRVE;                                  /**< Port High Drive Enable Register, offset: 0x14 */
} volatile *PORT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PORT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Accessor_Macros PORT - Register accessor macros
 * @{
 */


/* PORT - Register accessors */
#define PORT_IOFLT0_REG(base)                    ((base)->IOFLT0)
#define PORT_IOFLT1_REG(base)                    ((base)->IOFLT1)
#define PORT_PUE0_REG(base)                      ((base)->PUE0)
#define PORT_PUE1_REG(base)                      ((base)->PUE1)
#define PORT_PUE2_REG(base)                      ((base)->PUE2)
#define PORT_HDRVE_REG(base)                     ((base)->HDRVE)

/*!
 * @}
 */ /* end of group PORT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PORT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Masks PORT Register Masks
 * @{
 */

/* IOFLT0 Bit Fields */
#define PORT_IOFLT0_FLTA_MASK                    0x3u
#define PORT_IOFLT0_FLTA_SHIFT                   0
#define PORT_IOFLT0_FLTA(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTA_SHIFT))&PORT_IOFLT0_FLTA_MASK)
#define PORT_IOFLT0_FLTB_MASK                    0xCu
#define PORT_IOFLT0_FLTB_SHIFT                   2
#define PORT_IOFLT0_FLTB(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTB_SHIFT))&PORT_IOFLT0_FLTB_MASK)
#define PORT_IOFLT0_FLTC_MASK                    0x30u
#define PORT_IOFLT0_FLTC_SHIFT                   4
#define PORT_IOFLT0_FLTC(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTC_SHIFT))&PORT_IOFLT0_FLTC_MASK)
#define PORT_IOFLT0_FLTD_MASK                    0xC0u
#define PORT_IOFLT0_FLTD_SHIFT                   6
#define PORT_IOFLT0_FLTD(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTD_SHIFT))&PORT_IOFLT0_FLTD_MASK)
#define PORT_IOFLT0_FLTE_MASK                    0x300u
#define PORT_IOFLT0_FLTE_SHIFT                   8
#define PORT_IOFLT0_FLTE(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTE_SHIFT))&PORT_IOFLT0_FLTE_MASK)
#define PORT_IOFLT0_FLTF_MASK                    0xC00u
#define PORT_IOFLT0_FLTF_SHIFT                   10
#define PORT_IOFLT0_FLTF(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTF_SHIFT))&PORT_IOFLT0_FLTF_MASK)
#define PORT_IOFLT0_FLTG_MASK                    0x3000u
#define PORT_IOFLT0_FLTG_SHIFT                   12
#define PORT_IOFLT0_FLTG(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTG_SHIFT))&PORT_IOFLT0_FLTG_MASK)
#define PORT_IOFLT0_FLTH_MASK                    0xC000u
#define PORT_IOFLT0_FLTH_SHIFT                   14
#define PORT_IOFLT0_FLTH(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTH_SHIFT))&PORT_IOFLT0_FLTH_MASK)
#define PORT_IOFLT0_FLTRST_MASK                  0x30000u
#define PORT_IOFLT0_FLTRST_SHIFT                 16
#define PORT_IOFLT0_FLTRST(x)                    (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTRST_SHIFT))&PORT_IOFLT0_FLTRST_MASK)
#define PORT_IOFLT0_FLTKBI0_MASK                 0xC0000u
#define PORT_IOFLT0_FLTKBI0_SHIFT                18
#define PORT_IOFLT0_FLTKBI0(x)                   (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTKBI0_SHIFT))&PORT_IOFLT0_FLTKBI0_MASK)
#define PORT_IOFLT0_FLTKBI1_MASK                 0x300000u
#define PORT_IOFLT0_FLTKBI1_SHIFT                20
#define PORT_IOFLT0_FLTKBI1(x)                   (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTKBI1_SHIFT))&PORT_IOFLT0_FLTKBI1_MASK)
#define PORT_IOFLT0_FLTNMI_MASK                  0xC00000u
#define PORT_IOFLT0_FLTNMI_SHIFT                 22
#define PORT_IOFLT0_FLTNMI(x)                    (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTNMI_SHIFT))&PORT_IOFLT0_FLTNMI_MASK)
#define PORT_IOFLT0_FLTDIV1_MASK                 0x3000000u
#define PORT_IOFLT0_FLTDIV1_SHIFT                24
#define PORT_IOFLT0_FLTDIV1(x)                   (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTDIV1_SHIFT))&PORT_IOFLT0_FLTDIV1_MASK)
#define PORT_IOFLT0_FLTDIV2_MASK                 0x1C000000u
#define PORT_IOFLT0_FLTDIV2_SHIFT                26
#define PORT_IOFLT0_FLTDIV2(x)                   (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTDIV2_SHIFT))&PORT_IOFLT0_FLTDIV2_MASK)
#define PORT_IOFLT0_FLTDIV3_MASK                 0xE0000000u
#define PORT_IOFLT0_FLTDIV3_SHIFT                29
#define PORT_IOFLT0_FLTDIV3(x)                   (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTDIV3_SHIFT))&PORT_IOFLT0_FLTDIV3_MASK)
/* IOFLT1 Bit Fields */
#define PORT_IOFLT1_FLTI_MASK                    0x3u
#define PORT_IOFLT1_FLTI_SHIFT                   0
#define PORT_IOFLT1_FLTI(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT1_FLTI_SHIFT))&PORT_IOFLT1_FLTI_MASK)
#define PORT_IOFLT1_FLTIRQ_MASK                  0x30u
#define PORT_IOFLT1_FLTIRQ_SHIFT                 4
#define PORT_IOFLT1_FLTIRQ(x)                    (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT1_FLTIRQ_SHIFT))&PORT_IOFLT1_FLTIRQ_MASK)
#define PORT_IOFLT1_FLTFTM0_MASK                 0xC0u
#define PORT_IOFLT1_FLTFTM0_SHIFT                6
#define PORT_IOFLT1_FLTFTM0(x)                   (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT1_FLTFTM0_SHIFT))&PORT_IOFLT1_FLTFTM0_MASK)
#define PORT_IOFLT1_FLTFTM1_MASK                 0x300u
#define PORT_IOFLT1_FLTFTM1_SHIFT                8
#define PORT_IOFLT1_FLTFTM1(x)                   (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT1_FLTFTM1_SHIFT))&PORT_IOFLT1_FLTFTM1_MASK)
#define PORT_IOFLT1_FLTPWT_MASK                  0xC00u
#define PORT_IOFLT1_FLTPWT_SHIFT                 10
#define PORT_IOFLT1_FLTPWT(x)                    (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT1_FLTPWT_SHIFT))&PORT_IOFLT1_FLTPWT_MASK)
#define PORT_IOFLT1_FLTI2C0_MASK                 0x3000u
#define PORT_IOFLT1_FLTI2C0_SHIFT                12
#define PORT_IOFLT1_FLTI2C0(x)                   (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT1_FLTI2C0_SHIFT))&PORT_IOFLT1_FLTI2C0_MASK)
#define PORT_IOFLT1_FLTI2C1_MASK                 0xC000u
#define PORT_IOFLT1_FLTI2C1_SHIFT                14
#define PORT_IOFLT1_FLTI2C1(x)                   (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT1_FLTI2C1_SHIFT))&PORT_IOFLT1_FLTI2C1_MASK)
/* PUE0 Bit Fields */
#define PORT_PUE0_PTAPE0_MASK                    0x1u
#define PORT_PUE0_PTAPE0_SHIFT                   0
#define PORT_PUE0_PTAPE1_MASK                    0x2u
#define PORT_PUE0_PTAPE1_SHIFT                   1
#define PORT_PUE0_PTAPE2_MASK                    0x4u
#define PORT_PUE0_PTAPE2_SHIFT                   2
#define PORT_PUE0_PTAPE3_MASK                    0x8u
#define PORT_PUE0_PTAPE3_SHIFT                   3
#define PORT_PUE0_PTAPE4_MASK                    0x10u
#define PORT_PUE0_PTAPE4_SHIFT                   4
#define PORT_PUE0_PTAPE5_MASK                    0x20u
#define PORT_PUE0_PTAPE5_SHIFT                   5
#define PORT_PUE0_PTAPE6_MASK                    0x40u
#define PORT_PUE0_PTAPE6_SHIFT                   6
#define PORT_PUE0_PTAPE7_MASK                    0x80u
#define PORT_PUE0_PTAPE7_SHIFT                   7
#define PORT_PUE0_PTBPE0_MASK                    0x100u
#define PORT_PUE0_PTBPE0_SHIFT                   8
#define PORT_PUE0_PTBPE1_MASK                    0x200u
#define PORT_PUE0_PTBPE1_SHIFT                   9
#define PORT_PUE0_PTBPE2_MASK                    0x400u
#define PORT_PUE0_PTBPE2_SHIFT                   10
#define PORT_PUE0_PTBPE3_MASK                    0x800u
#define PORT_PUE0_PTBPE3_SHIFT                   11
#define PORT_PUE0_PTBPE4_MASK                    0x1000u
#define PORT_PUE0_PTBPE4_SHIFT                   12
#define PORT_PUE0_PTBPE5_MASK                    0x2000u
#define PORT_PUE0_PTBPE5_SHIFT                   13
#define PORT_PUE0_PTBPE6_MASK                    0x4000u
#define PORT_PUE0_PTBPE6_SHIFT                   14
#define PORT_PUE0_PTBPE7_MASK                    0x8000u
#define PORT_PUE0_PTBPE7_SHIFT                   15
#define PORT_PUE0_PTCPE0_MASK                    0x10000u
#define PORT_PUE0_PTCPE0_SHIFT                   16
#define PORT_PUE0_PTCPE1_MASK                    0x20000u
#define PORT_PUE0_PTCPE1_SHIFT                   17
#define PORT_PUE0_PTCPE2_MASK                    0x40000u
#define PORT_PUE0_PTCPE2_SHIFT                   18
#define PORT_PUE0_PTCPE3_MASK                    0x80000u
#define PORT_PUE0_PTCPE3_SHIFT                   19
#define PORT_PUE0_PTCPE4_MASK                    0x100000u
#define PORT_PUE0_PTCPE4_SHIFT                   20
#define PORT_PUE0_PTCPE5_MASK                    0x200000u
#define PORT_PUE0_PTCPE5_SHIFT                   21
#define PORT_PUE0_PTCPE6_MASK                    0x400000u
#define PORT_PUE0_PTCPE6_SHIFT                   22
#define PORT_PUE0_PTCPE7_MASK                    0x800000u
#define PORT_PUE0_PTCPE7_SHIFT                   23
#define PORT_PUE0_PTDPE0_MASK                    0x1000000u
#define PORT_PUE0_PTDPE0_SHIFT                   24
#define PORT_PUE0_PTDPE1_MASK                    0x2000000u
#define PORT_PUE0_PTDPE1_SHIFT                   25
#define PORT_PUE0_PTDPE2_MASK                    0x4000000u
#define PORT_PUE0_PTDPE2_SHIFT                   26
#define PORT_PUE0_PTDPE3_MASK                    0x8000000u
#define PORT_PUE0_PTDPE3_SHIFT                   27
#define PORT_PUE0_PTDPE4_MASK                    0x10000000u
#define PORT_PUE0_PTDPE4_SHIFT                   28
#define PORT_PUE0_PTDPE5_MASK                    0x20000000u
#define PORT_PUE0_PTDPE5_SHIFT                   29
#define PORT_PUE0_PTDPE6_MASK                    0x40000000u
#define PORT_PUE0_PTDPE6_SHIFT                   30
#define PORT_PUE0_PTDPE7_MASK                    0x80000000u
#define PORT_PUE0_PTDPE7_SHIFT                   31
/* PUE1 Bit Fields */
#define PORT_PUE1_PTEPE0_MASK                    0x1u
#define PORT_PUE1_PTEPE0_SHIFT                   0
#define PORT_PUE1_PTEPE1_MASK                    0x2u
#define PORT_PUE1_PTEPE1_SHIFT                   1
#define PORT_PUE1_PTEPE2_MASK                    0x4u
#define PORT_PUE1_PTEPE2_SHIFT                   2
#define PORT_PUE1_PTEPE3_MASK                    0x8u
#define PORT_PUE1_PTEPE3_SHIFT                   3
#define PORT_PUE1_PTEPE4_MASK                    0x10u
#define PORT_PUE1_PTEPE4_SHIFT                   4
#define PORT_PUE1_PTEPE5_MASK                    0x20u
#define PORT_PUE1_PTEPE5_SHIFT                   5
#define PORT_PUE1_PTEPE6_MASK                    0x40u
#define PORT_PUE1_PTEPE6_SHIFT                   6
#define PORT_PUE1_PTEPE7_MASK                    0x80u
#define PORT_PUE1_PTEPE7_SHIFT                   7
#define PORT_PUE1_PTFPE0_MASK                    0x100u
#define PORT_PUE1_PTFPE0_SHIFT                   8
#define PORT_PUE1_PTFPE1_MASK                    0x200u
#define PORT_PUE1_PTFPE1_SHIFT                   9
#define PORT_PUE1_PTFPE2_MASK                    0x400u
#define PORT_PUE1_PTFPE2_SHIFT                   10
#define PORT_PUE1_PTFPE3_MASK                    0x800u
#define PORT_PUE1_PTFPE3_SHIFT                   11
#define PORT_PUE1_PTFPE4_MASK                    0x1000u
#define PORT_PUE1_PTFPE4_SHIFT                   12
#define PORT_PUE1_PTFPE5_MASK                    0x2000u
#define PORT_PUE1_PTFPE5_SHIFT                   13
#define PORT_PUE1_PTFPE6_MASK                    0x4000u
#define PORT_PUE1_PTFPE6_SHIFT                   14
#define PORT_PUE1_PTFPE7_MASK                    0x8000u
#define PORT_PUE1_PTFPE7_SHIFT                   15
#define PORT_PUE1_PTGPE0_MASK                    0x10000u
#define PORT_PUE1_PTGPE0_SHIFT                   16
#define PORT_PUE1_PTGPE1_MASK                    0x20000u
#define PORT_PUE1_PTGPE1_SHIFT                   17
#define PORT_PUE1_PTGPE2_MASK                    0x40000u
#define PORT_PUE1_PTGPE2_SHIFT                   18
#define PORT_PUE1_PTGPE3_MASK                    0x80000u
#define PORT_PUE1_PTGPE3_SHIFT                   19
#define PORT_PUE1_PTGPE4_MASK                    0x100000u
#define PORT_PUE1_PTGPE4_SHIFT                   20
#define PORT_PUE1_PTGPE5_MASK                    0x200000u
#define PORT_PUE1_PTGPE5_SHIFT                   21
#define PORT_PUE1_PTGPE6_MASK                    0x400000u
#define PORT_PUE1_PTGPE6_SHIFT                   22
#define PORT_PUE1_PTGPE7_MASK                    0x800000u
#define PORT_PUE1_PTGPE7_SHIFT                   23
#define PORT_PUE1_PTHPE0_MASK                    0x1000000u
#define PORT_PUE1_PTHPE0_SHIFT                   24
#define PORT_PUE1_PTHPE1_MASK                    0x2000000u
#define PORT_PUE1_PTHPE1_SHIFT                   25
#define PORT_PUE1_PTHPE2_MASK                    0x4000000u
#define PORT_PUE1_PTHPE2_SHIFT                   26
#define PORT_PUE1_PTHPE3_MASK                    0x8000000u
#define PORT_PUE1_PTHPE3_SHIFT                   27
#define PORT_PUE1_PTHPE4_MASK                    0x10000000u
#define PORT_PUE1_PTHPE4_SHIFT                   28
#define PORT_PUE1_PTHPE5_MASK                    0x20000000u
#define PORT_PUE1_PTHPE5_SHIFT                   29
#define PORT_PUE1_PTHPE6_MASK                    0x40000000u
#define PORT_PUE1_PTHPE6_SHIFT                   30
#define PORT_PUE1_PTHPE7_MASK                    0x80000000u
#define PORT_PUE1_PTHPE7_SHIFT                   31
/* PUE2 Bit Fields */
#define PORT_PUE2_PTIPE0_MASK                    0x1u
#define PORT_PUE2_PTIPE0_SHIFT                   0
#define PORT_PUE2_PTIPE1_MASK                    0x2u
#define PORT_PUE2_PTIPE1_SHIFT                   1
#define PORT_PUE2_PTIPE2_MASK                    0x4u
#define PORT_PUE2_PTIPE2_SHIFT                   2
#define PORT_PUE2_PTIPE3_MASK                    0x8u
#define PORT_PUE2_PTIPE3_SHIFT                   3
#define PORT_PUE2_PTIPE4_MASK                    0x10u
#define PORT_PUE2_PTIPE4_SHIFT                   4
#define PORT_PUE2_PTIPE5_MASK                    0x20u
#define PORT_PUE2_PTIPE5_SHIFT                   5
#define PORT_PUE2_PTIPE6_MASK                    0x40u
#define PORT_PUE2_PTIPE6_SHIFT                   6
/* HDRVE Bit Fields */
#define PORT_HDRVE_PTB4_MASK                     0x1u
#define PORT_HDRVE_PTB4_SHIFT                    0
#define PORT_HDRVE_PTB5_MASK                     0x2u
#define PORT_HDRVE_PTB5_SHIFT                    1
#define PORT_HDRVE_PTD0_MASK                     0x4u
#define PORT_HDRVE_PTD0_SHIFT                    2
#define PORT_HDRVE_PTD1_MASK                     0x8u
#define PORT_HDRVE_PTD1_SHIFT                    3
#define PORT_HDRVE_PTE0_MASK                     0x10u
#define PORT_HDRVE_PTE0_SHIFT                    4
#define PORT_HDRVE_PTE1_MASK                     0x20u
#define PORT_HDRVE_PTE1_SHIFT                    5
#define PORT_HDRVE_PTH0_MASK                     0x40u
#define PORT_HDRVE_PTH0_SHIFT                    6
#define PORT_HDRVE_PTH1_MASK                     0x80u
#define PORT_HDRVE_PTH1_SHIFT                    7

/*!
 * @}
 */ /* end of group PORT_Register_Masks */


/* PORT - Peripheral instance base addresses */
/** Peripheral PORT base pointer */
#define PORT_BASE_PTR                            ((PORT_MemMapPtr)0x40049000u)
/** Array initializer of PORT peripheral base pointers */
#define PORT_BASE_PTRS                           { PORT_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- PORT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Accessor_Macros PORT - Register accessor macros
 * @{
 */


/* PORT - Register instance definitions */
/* PORT */
#define PORT_IOFLT0                              PORT_IOFLT0_REG(PORT_BASE_PTR)
#define PORT_IOFLT1                              PORT_IOFLT1_REG(PORT_BASE_PTR)
#define PORT_PUE0                                PORT_PUE0_REG(PORT_BASE_PTR)
#define PORT_PUE1                                PORT_PUE1_REG(PORT_BASE_PTR)
#define PORT_PUE2                                PORT_PUE2_REG(PORT_BASE_PTR)
#define PORT_HDRVE                               PORT_HDRVE_REG(PORT_BASE_PTR)

/*!
 * @}
 */ /* end of group PORT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group PORT_Peripheral */


/* ----------------------------------------------------------------------------
   -- PWT
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PWT_Peripheral PWT
 * @{
 */

/** PWT - Peripheral register structure */
typedef struct PWT_MemMap {
  uint32_t R1;                                     /**< Pulse Width Timer Register 1, offset: 0x0 */
  uint32_t R2;                                     /**< Pulse Width Timer Register 2, offset: 0x4 */
} volatile *PWT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PWT_Register_Accessor_Macros PWT - Register accessor macros
 * @{
 */


/* PWT - Register accessors */
#define PWT_R1_REG(base)                         ((base)->R1)
#define PWT_R2_REG(base)                         ((base)->R2)

/*!
 * @}
 */ /* end of group PWT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PWT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PWT_Register_Masks PWT Register Masks
 * @{
 */

/* R1 Bit Fields */
#define PWT_R1_PWTOV_MASK                        0x1u
#define PWT_R1_PWTOV_SHIFT                       0
#define PWT_R1_PWTRDY_MASK                       0x2u
#define PWT_R1_PWTRDY_SHIFT                      1
#define PWT_R1_PWTSR_MASK                        0x8u
#define PWT_R1_PWTSR_SHIFT                       3
#define PWT_R1_POVIE_MASK                        0x10u
#define PWT_R1_POVIE_SHIFT                       4
#define PWT_R1_PRDYIE_MASK                       0x20u
#define PWT_R1_PRDYIE_SHIFT                      5
#define PWT_R1_PWTIE_MASK                        0x40u
#define PWT_R1_PWTIE_SHIFT                       6
#define PWT_R1_PWTEN_MASK                        0x80u
#define PWT_R1_PWTEN_SHIFT                       7
#define PWT_R1_PRE_MASK                          0x700u
#define PWT_R1_PRE_SHIFT                         8
#define PWT_R1_PRE(x)                            (((uint32_t)(((uint32_t)(x))<<PWT_R1_PRE_SHIFT))&PWT_R1_PRE_MASK)
#define PWT_R1_EDGE_MASK                         0x1800u
#define PWT_R1_EDGE_SHIFT                        11
#define PWT_R1_EDGE(x)                           (((uint32_t)(((uint32_t)(x))<<PWT_R1_EDGE_SHIFT))&PWT_R1_EDGE_MASK)
#define PWT_R1_PINSEL_MASK                       0x6000u
#define PWT_R1_PINSEL_SHIFT                      13
#define PWT_R1_PINSEL(x)                         (((uint32_t)(((uint32_t)(x))<<PWT_R1_PINSEL_SHIFT))&PWT_R1_PINSEL_MASK)
#define PWT_R1_PCLKS_MASK                        0x8000u
#define PWT_R1_PCLKS_SHIFT                       15
#define PWT_R1_PPW_MASK                          0xFFFF0000u
#define PWT_R1_PPW_SHIFT                         16
#define PWT_R1_PPW(x)                            (((uint32_t)(((uint32_t)(x))<<PWT_R1_PPW_SHIFT))&PWT_R1_PPW_MASK)
/* R2 Bit Fields */
#define PWT_R2_NPW_MASK                          0xFFFFu
#define PWT_R2_NPW_SHIFT                         0
#define PWT_R2_NPW(x)                            (((uint32_t)(((uint32_t)(x))<<PWT_R2_NPW_SHIFT))&PWT_R2_NPW_MASK)
#define PWT_R2_PWTC_MASK                         0xFFFF0000u
#define PWT_R2_PWTC_SHIFT                        16
#define PWT_R2_PWTC(x)                           (((uint32_t)(((uint32_t)(x))<<PWT_R2_PWTC_SHIFT))&PWT_R2_PWTC_MASK)

/*!
 * @}
 */ /* end of group PWT_Register_Masks */


/* PWT - Peripheral instance base addresses */
/** Peripheral PWT base pointer */
#define PWT_BASE_PTR                             ((PWT_MemMapPtr)0x40033000u)
/** Array initializer of PWT peripheral base pointers */
#define PWT_BASE_PTRS                            { PWT_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- PWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PWT_Register_Accessor_Macros PWT - Register accessor macros
 * @{
 */


/* PWT - Register instance definitions */
/* PWT */
#define PWT_R1                                   PWT_R1_REG(PWT_BASE_PTR)
#define PWT_R2                                   PWT_R2_REG(PWT_BASE_PTR)

/*!
 * @}
 */ /* end of group PWT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group PWT_Peripheral */


/* ----------------------------------------------------------------------------
   -- ROM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Peripheral ROM
 * @{
 */

/** ROM - Peripheral register structure */
typedef struct ROM_MemMap {
  uint32_t ENTRY[1];                               /**< Entry, array offset: 0x0, array step: 0x4 */
  uint32_t TABLEMARK;                              /**< End of Table Marker Register, offset: 0x4 */
  uint8_t RESERVED_0[4036];
  uint32_t SYSACCESS;                              /**< System Access Register, offset: 0xFCC */
  uint32_t PERIPHID4;                              /**< Peripheral ID Register, offset: 0xFD0 */
  uint32_t PERIPHID5;                              /**< Peripheral ID Register, offset: 0xFD4 */
  uint32_t PERIPHID6;                              /**< Peripheral ID Register, offset: 0xFD8 */
  uint32_t PERIPHID7;                              /**< Peripheral ID Register, offset: 0xFDC */
  uint32_t PERIPHID0;                              /**< Peripheral ID Register, offset: 0xFE0 */
  uint32_t PERIPHID1;                              /**< Peripheral ID Register, offset: 0xFE4 */
  uint32_t PERIPHID2;                              /**< Peripheral ID Register, offset: 0xFE8 */
  uint32_t PERIPHID3;                              /**< Peripheral ID Register, offset: 0xFEC */
  uint32_t COMPID[4];                              /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} volatile *ROM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ROM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Register_Accessor_Macros ROM - Register accessor macros
 * @{
 */


/* ROM - Register accessors */
#define ROM_ENTRY_REG(base,index)                ((base)->ENTRY[index])
#define ROM_TABLEMARK_REG(base)                  ((base)->TABLEMARK)
#define ROM_SYSACCESS_REG(base)                  ((base)->SYSACCESS)
#define ROM_PERIPHID4_REG(base)                  ((base)->PERIPHID4)
#define ROM_PERIPHID5_REG(base)                  ((base)->PERIPHID5)
#define ROM_PERIPHID6_REG(base)                  ((base)->PERIPHID6)
#define ROM_PERIPHID7_REG(base)                  ((base)->PERIPHID7)
#define ROM_PERIPHID0_REG(base)                  ((base)->PERIPHID0)
#define ROM_PERIPHID1_REG(base)                  ((base)->PERIPHID1)
#define ROM_PERIPHID2_REG(base)                  ((base)->PERIPHID2)
#define ROM_PERIPHID3_REG(base)                  ((base)->PERIPHID3)
#define ROM_COMPID_REG(base,index)               ((base)->COMPID[index])

/*!
 * @}
 */ /* end of group ROM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ROM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Register_Masks ROM Register Masks
 * @{
 */

/* ENTRY Bit Fields */
#define ROM_ENTRY_ENTRY_MASK                     0xFFFFFFFFu
#define ROM_ENTRY_ENTRY_SHIFT                    0
#define ROM_ENTRY_ENTRY(x)                       (((uint32_t)(((uint32_t)(x))<<ROM_ENTRY_ENTRY_SHIFT))&ROM_ENTRY_ENTRY_MASK)
/* TABLEMARK Bit Fields */
#define ROM_TABLEMARK_MARK_MASK                  0xFFFFFFFFu
#define ROM_TABLEMARK_MARK_SHIFT                 0
#define ROM_TABLEMARK_MARK(x)                    (((uint32_t)(((uint32_t)(x))<<ROM_TABLEMARK_MARK_SHIFT))&ROM_TABLEMARK_MARK_MASK)
/* SYSACCESS Bit Fields */
#define ROM_SYSACCESS_SYSACCESS_MASK             0xFFFFFFFFu
#define ROM_SYSACCESS_SYSACCESS_SHIFT            0
#define ROM_SYSACCESS_SYSACCESS(x)               (((uint32_t)(((uint32_t)(x))<<ROM_SYSACCESS_SYSACCESS_SHIFT))&ROM_SYSACCESS_SYSACCESS_MASK)
/* PERIPHID4 Bit Fields */
#define ROM_PERIPHID4_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID4_PERIPHID_SHIFT             0
#define ROM_PERIPHID4_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID4_PERIPHID_SHIFT))&ROM_PERIPHID4_PERIPHID_MASK)
/* PERIPHID5 Bit Fields */
#define ROM_PERIPHID5_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID5_PERIPHID_SHIFT             0
#define ROM_PERIPHID5_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID5_PERIPHID_SHIFT))&ROM_PERIPHID5_PERIPHID_MASK)
/* PERIPHID6 Bit Fields */
#define ROM_PERIPHID6_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID6_PERIPHID_SHIFT             0
#define ROM_PERIPHID6_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID6_PERIPHID_SHIFT))&ROM_PERIPHID6_PERIPHID_MASK)
/* PERIPHID7 Bit Fields */
#define ROM_PERIPHID7_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID7_PERIPHID_SHIFT             0
#define ROM_PERIPHID7_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID7_PERIPHID_SHIFT))&ROM_PERIPHID7_PERIPHID_MASK)
/* PERIPHID0 Bit Fields */
#define ROM_PERIPHID0_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID0_PERIPHID_SHIFT             0
#define ROM_PERIPHID0_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID0_PERIPHID_SHIFT))&ROM_PERIPHID0_PERIPHID_MASK)
/* PERIPHID1 Bit Fields */
#define ROM_PERIPHID1_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID1_PERIPHID_SHIFT             0
#define ROM_PERIPHID1_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID1_PERIPHID_SHIFT))&ROM_PERIPHID1_PERIPHID_MASK)
/* PERIPHID2 Bit Fields */
#define ROM_PERIPHID2_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID2_PERIPHID_SHIFT             0
#define ROM_PERIPHID2_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID2_PERIPHID_SHIFT))&ROM_PERIPHID2_PERIPHID_MASK)
/* PERIPHID3 Bit Fields */
#define ROM_PERIPHID3_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID3_PERIPHID_SHIFT             0
#define ROM_PERIPHID3_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID3_PERIPHID_SHIFT))&ROM_PERIPHID3_PERIPHID_MASK)
/* COMPID Bit Fields */
#define ROM_COMPID_COMPID_MASK                   0xFFFFFFFFu
#define ROM_COMPID_COMPID_SHIFT                  0
#define ROM_COMPID_COMPID(x)                     (((uint32_t)(((uint32_t)(x))<<ROM_COMPID_COMPID_SHIFT))&ROM_COMPID_COMPID_MASK)

/*!
 * @}
 */ /* end of group ROM_Register_Masks */


/* ROM - Peripheral instance base addresses */
/** Peripheral ROM base pointer */
#define ROM_BASE_PTR                             ((ROM_MemMapPtr)0xF0002000u)
/** Array initializer of ROM peripheral base pointers */
#define ROM_BASE_PTRS                            { ROM_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- ROM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Register_Accessor_Macros ROM - Register accessor macros
 * @{
 */


/* ROM - Register instance definitions */
/* ROM */
#define ROM_ENTRY0                               ROM_ENTRY_REG(ROM_BASE_PTR,0)
#define ROM_TABLEMARK                            ROM_TABLEMARK_REG(ROM_BASE_PTR)
#define ROM_SYSACCESS                            ROM_SYSACCESS_REG(ROM_BASE_PTR)
#define ROM_PERIPHID4                            ROM_PERIPHID4_REG(ROM_BASE_PTR)
#define ROM_PERIPHID5                            ROM_PERIPHID5_REG(ROM_BASE_PTR)
#define ROM_PERIPHID6                            ROM_PERIPHID6_REG(ROM_BASE_PTR)
#define ROM_PERIPHID7                            ROM_PERIPHID7_REG(ROM_BASE_PTR)
#define ROM_PERIPHID0                            ROM_PERIPHID0_REG(ROM_BASE_PTR)
#define ROM_PERIPHID1                            ROM_PERIPHID1_REG(ROM_BASE_PTR)
#define ROM_PERIPHID2                            ROM_PERIPHID2_REG(ROM_BASE_PTR)
#define ROM_PERIPHID3                            ROM_PERIPHID3_REG(ROM_BASE_PTR)
#define ROM_COMPID0                              ROM_COMPID_REG(ROM_BASE_PTR,0)
#define ROM_COMPID1                              ROM_COMPID_REG(ROM_BASE_PTR,1)
#define ROM_COMPID2                              ROM_COMPID_REG(ROM_BASE_PTR,2)
#define ROM_COMPID3                              ROM_COMPID_REG(ROM_BASE_PTR,3)

/* ROM - Register array accessors */
#define ROM_ENTRY(index)                         ROM_ENTRY_REG(ROM_BASE_PTR,index)
#define ROM_COMPID(index)                        ROM_COMPID_REG(ROM_BASE_PTR,index)

/*!
 * @}
 */ /* end of group ROM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ROM_Peripheral */


/* ----------------------------------------------------------------------------
   -- RTC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Peripheral RTC
 * @{
 */

/** RTC - Peripheral register structure */
typedef struct RTC_MemMap {
  uint32_t SC;                                     /**< RTC Status and Control Register, offset: 0x0 */
  uint32_t MOD;                                    /**< RTC Modulo Register, offset: 0x4 */
  uint32_t CNT;                                    /**< RTC Counter Register, offset: 0x8 */
} volatile *RTC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- RTC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Accessor_Macros RTC - Register accessor macros
 * @{
 */


/* RTC - Register accessors */
#define RTC_SC_REG(base)                         ((base)->SC)
#define RTC_MOD_REG(base)                        ((base)->MOD)
#define RTC_CNT_REG(base)                        ((base)->CNT)

/*!
 * @}
 */ /* end of group RTC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- RTC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Masks RTC Register Masks
 * @{
 */

/* SC Bit Fields */
#define RTC_SC_RTCO_MASK                         0x10u
#define RTC_SC_RTCO_SHIFT                        4
#define RTC_SC_RTIE_MASK                         0x40u
#define RTC_SC_RTIE_SHIFT                        6
#define RTC_SC_RTIF_MASK                         0x80u
#define RTC_SC_RTIF_SHIFT                        7
#define RTC_SC_RTCPS_MASK                        0x700u
#define RTC_SC_RTCPS_SHIFT                       8
#define RTC_SC_RTCPS(x)                          (((uint32_t)(((uint32_t)(x))<<RTC_SC_RTCPS_SHIFT))&RTC_SC_RTCPS_MASK)
#define RTC_SC_RTCLKS_MASK                       0xC000u
#define RTC_SC_RTCLKS_SHIFT                      14
#define RTC_SC_RTCLKS(x)                         (((uint32_t)(((uint32_t)(x))<<RTC_SC_RTCLKS_SHIFT))&RTC_SC_RTCLKS_MASK)
/* MOD Bit Fields */
#define RTC_MOD_MOD_MASK                         0xFFFFu
#define RTC_MOD_MOD_SHIFT                        0
#define RTC_MOD_MOD(x)                           (((uint32_t)(((uint32_t)(x))<<RTC_MOD_MOD_SHIFT))&RTC_MOD_MOD_MASK)
/* CNT Bit Fields */
#define RTC_CNT_CNT_MASK                         0xFFFFu
#define RTC_CNT_CNT_SHIFT                        0
#define RTC_CNT_CNT(x)                           (((uint32_t)(((uint32_t)(x))<<RTC_CNT_CNT_SHIFT))&RTC_CNT_CNT_MASK)

/*!
 * @}
 */ /* end of group RTC_Register_Masks */


/* RTC - Peripheral instance base addresses */
/** Peripheral RTC base pointer */
#define RTC_BASE_PTR                             ((RTC_MemMapPtr)0x4003D000u)
/** Array initializer of RTC peripheral base pointers */
#define RTC_BASE_PTRS                            { RTC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- RTC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Accessor_Macros RTC - Register accessor macros
 * @{
 */


/* RTC - Register instance definitions */
/* RTC */
#define RTC_SC                                   RTC_SC_REG(RTC_BASE_PTR)
#define RTC_MOD                                  RTC_MOD_REG(RTC_BASE_PTR)
#define RTC_CNT                                  RTC_CNT_REG(RTC_BASE_PTR)

/*!
 * @}
 */ /* end of group RTC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group RTC_Peripheral */


/* ----------------------------------------------------------------------------
   -- SCB
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Peripheral SCB
 * @{
 */

/** SCB - Peripheral register structure */
typedef struct SCB_MemMap {
  uint8_t RESERVED_0[8];
  uint32_t ACTLR;                                  /**< Auxiliary Control Register,, offset: 0x8 */
  uint8_t RESERVED_1[3316];
  uint32_t CPUID;                                  /**< CPUID Base Register, offset: 0xD00 */
  uint32_t ICSR;                                   /**< Interrupt Control and State Register, offset: 0xD04 */
  uint32_t VTOR;                                   /**< Vector Table Offset Register, offset: 0xD08 */
  uint32_t AIRCR;                                  /**< Application Interrupt and Reset Control Register, offset: 0xD0C */
  uint32_t SCR;                                    /**< System Control Register, offset: 0xD10 */
  uint32_t CCR;                                    /**< Configuration and Control Register, offset: 0xD14 */
  uint8_t RESERVED_2[4];
  uint32_t SHPR2;                                  /**< System Handler Priority Register 2, offset: 0xD1C */
  uint32_t SHPR3;                                  /**< System Handler Priority Register 3, offset: 0xD20 */
  uint32_t SHCSR;                                  /**< System Handler Control and State Register, offset: 0xD24 */
  uint8_t RESERVED_3[8];
  uint32_t DFSR;                                   /**< Debug Fault Status Register, offset: 0xD30 */
} volatile *SCB_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SCB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Register_Accessor_Macros SCB - Register accessor macros
 * @{
 */


/* SCB - Register accessors */
#define SCB_ACTLR_REG(base)                      ((base)->ACTLR)
#define SCB_CPUID_REG(base)                      ((base)->CPUID)
#define SCB_ICSR_REG(base)                       ((base)->ICSR)
#define SCB_VTOR_REG(base)                       ((base)->VTOR)
#define SCB_AIRCR_REG(base)                      ((base)->AIRCR)
#define SCB_SCR_REG(base)                        ((base)->SCR)
#define SCB_CCR_REG(base)                        ((base)->CCR)
#define SCB_SHPR2_REG(base)                      ((base)->SHPR2)
#define SCB_SHPR3_REG(base)                      ((base)->SHPR3)
#define SCB_SHCSR_REG(base)                      ((base)->SHCSR)
#define SCB_DFSR_REG(base)                       ((base)->DFSR)

/*!
 * @}
 */ /* end of group SCB_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SCB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Register_Masks SCB Register Masks
 * @{
 */

/* CPUID Bit Fields */
#define SCB_CPUID_REVISION_MASK                  0xFu
#define SCB_CPUID_REVISION_SHIFT                 0
#define SCB_CPUID_REVISION(x)                    (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_REVISION_SHIFT))&SCB_CPUID_REVISION_MASK)
#define SCB_CPUID_PARTNO_MASK                    0xFFF0u
#define SCB_CPUID_PARTNO_SHIFT                   4
#define SCB_CPUID_PARTNO(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_PARTNO_SHIFT))&SCB_CPUID_PARTNO_MASK)
#define SCB_CPUID_VARIANT_MASK                   0xF00000u
#define SCB_CPUID_VARIANT_SHIFT                  20
#define SCB_CPUID_VARIANT(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_VARIANT_SHIFT))&SCB_CPUID_VARIANT_MASK)
#define SCB_CPUID_IMPLEMENTER_MASK               0xFF000000u
#define SCB_CPUID_IMPLEMENTER_SHIFT              24
#define SCB_CPUID_IMPLEMENTER(x)                 (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_IMPLEMENTER_SHIFT))&SCB_CPUID_IMPLEMENTER_MASK)
/* ICSR Bit Fields */
#define SCB_ICSR_VECTPENDING_MASK                0x3F000u
#define SCB_ICSR_VECTPENDING_SHIFT               12
#define SCB_ICSR_VECTPENDING(x)                  (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_VECTPENDING_SHIFT))&SCB_ICSR_VECTPENDING_MASK)
#define SCB_ICSR_PENDSTCLR_MASK                  0x2000000u
#define SCB_ICSR_PENDSTCLR_SHIFT                 25
#define SCB_ICSR_PENDSTSET_MASK                  0x4000000u
#define SCB_ICSR_PENDSTSET_SHIFT                 26
#define SCB_ICSR_PENDSVCLR_MASK                  0x8000000u
#define SCB_ICSR_PENDSVCLR_SHIFT                 27
#define SCB_ICSR_PENDSVSET_MASK                  0x10000000u
#define SCB_ICSR_PENDSVSET_SHIFT                 28
#define SCB_ICSR_NMIPENDSET_MASK                 0x80000000u
#define SCB_ICSR_NMIPENDSET_SHIFT                31
/* VTOR Bit Fields */
#define SCB_VTOR_TBLOFF_MASK                     0xFFFFFF80u
#define SCB_VTOR_TBLOFF_SHIFT                    7
#define SCB_VTOR_TBLOFF(x)                       (((uint32_t)(((uint32_t)(x))<<SCB_VTOR_TBLOFF_SHIFT))&SCB_VTOR_TBLOFF_MASK)
/* AIRCR Bit Fields */
#define SCB_AIRCR_VECTCLRACTIVE_MASK             0x2u
#define SCB_AIRCR_VECTCLRACTIVE_SHIFT            1
#define SCB_AIRCR_SYSRESETREQ_MASK               0x4u
#define SCB_AIRCR_SYSRESETREQ_SHIFT              2
#define SCB_AIRCR_ENDIANNESS_MASK                0x8000u
#define SCB_AIRCR_ENDIANNESS_SHIFT               15
#define SCB_AIRCR_VECTKEY_MASK                   0xFFFF0000u
#define SCB_AIRCR_VECTKEY_SHIFT                  16
#define SCB_AIRCR_VECTKEY(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_AIRCR_VECTKEY_SHIFT))&SCB_AIRCR_VECTKEY_MASK)
/* SCR Bit Fields */
#define SCB_SCR_SLEEPONEXIT_MASK                 0x2u
#define SCB_SCR_SLEEPONEXIT_SHIFT                1
#define SCB_SCR_SLEEPDEEP_MASK                   0x4u
#define SCB_SCR_SLEEPDEEP_SHIFT                  2
#define SCB_SCR_SEVONPEND_MASK                   0x10u
#define SCB_SCR_SEVONPEND_SHIFT                  4
/* CCR Bit Fields */
#define SCB_CCR_UNALIGN_TRP_MASK                 0x8u
#define SCB_CCR_UNALIGN_TRP_SHIFT                3
#define SCB_CCR_STKALIGN_MASK                    0x200u
#define SCB_CCR_STKALIGN_SHIFT                   9
/* SHPR2 Bit Fields */
#define SCB_SHPR2_PRI_11_MASK                    0xC0000000u
#define SCB_SHPR2_PRI_11_SHIFT                   30
#define SCB_SHPR2_PRI_11(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_SHPR2_PRI_11_SHIFT))&SCB_SHPR2_PRI_11_MASK)
/* SHPR3 Bit Fields */
#define SCB_SHPR3_PRI_14_MASK                    0xC00000u
#define SCB_SHPR3_PRI_14_SHIFT                   22
#define SCB_SHPR3_PRI_14(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_SHPR3_PRI_14_SHIFT))&SCB_SHPR3_PRI_14_MASK)
#define SCB_SHPR3_PRI_15_MASK                    0xC0000000u
#define SCB_SHPR3_PRI_15_SHIFT                   30
#define SCB_SHPR3_PRI_15(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_SHPR3_PRI_15_SHIFT))&SCB_SHPR3_PRI_15_MASK)
/* SHCSR Bit Fields */
#define SCB_SHCSR_SVCALLPENDED_MASK              0x8000u
#define SCB_SHCSR_SVCALLPENDED_SHIFT             15
/* DFSR Bit Fields */
#define SCB_DFSR_HALTED_MASK                     0x1u
#define SCB_DFSR_HALTED_SHIFT                    0
#define SCB_DFSR_BKPT_MASK                       0x2u
#define SCB_DFSR_BKPT_SHIFT                      1
#define SCB_DFSR_DWTTRAP_MASK                    0x4u
#define SCB_DFSR_DWTTRAP_SHIFT                   2
#define SCB_DFSR_VCATCH_MASK                     0x8u
#define SCB_DFSR_VCATCH_SHIFT                    3
#define SCB_DFSR_EXTERNAL_MASK                   0x10u
#define SCB_DFSR_EXTERNAL_SHIFT                  4

/*!
 * @}
 */ /* end of group SCB_Register_Masks */


/* SCB - Peripheral instance base addresses */
/** Peripheral SystemControl base pointer */
#define SystemControl_BASE_PTR                   ((SCB_MemMapPtr)0xE000E000u)
/** Array initializer of SCB peripheral base pointers */
#define SCB_BASE_PTRS                            { SystemControl_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- SCB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Register_Accessor_Macros SCB - Register accessor macros
 * @{
 */


/* SCB - Register instance definitions */
/* SystemControl */
#define SCB_ACTLR                                SCB_ACTLR_REG(SystemControl_BASE_PTR)
#define SCB_CPUID                                SCB_CPUID_REG(SystemControl_BASE_PTR)
#define SCB_ICSR                                 SCB_ICSR_REG(SystemControl_BASE_PTR)
#define SCB_VTOR                                 SCB_VTOR_REG(SystemControl_BASE_PTR)
#define SCB_AIRCR                                SCB_AIRCR_REG(SystemControl_BASE_PTR)
#define SCB_SCR                                  SCB_SCR_REG(SystemControl_BASE_PTR)
#define SCB_CCR                                  SCB_CCR_REG(SystemControl_BASE_PTR)
#define SCB_SHPR2                                SCB_SHPR2_REG(SystemControl_BASE_PTR)
#define SCB_SHPR3                                SCB_SHPR3_REG(SystemControl_BASE_PTR)
#define SCB_SHCSR                                SCB_SHCSR_REG(SystemControl_BASE_PTR)
#define SCB_DFSR                                 SCB_DFSR_REG(SystemControl_BASE_PTR)

/*!
 * @}
 */ /* end of group SCB_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group SCB_Peripheral */


/* ----------------------------------------------------------------------------
   -- SIM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Peripheral SIM
 * @{
 */

/** SIM - Peripheral register structure */
typedef struct SIM_MemMap {
  uint32_t SRSID;                                  /**< System Reset Status and ID Register, offset: 0x0 */
  uint32_t SOPT0;                                  /**< System Options Register 0, offset: 0x4 */
  uint32_t SOPT1;                                  /**< System Options Register, offset: 0x8 */
  uint32_t PINSEL;                                 /**< Pin Selection Register 0, offset: 0xC */
  uint32_t PINSEL1;                                /**< Pin Selection Register 1, offset: 0x10 */
  uint32_t SCGC;                                   /**< System Clock Gating Control Register, offset: 0x14 */
  uint32_t UUIDL;                                  /**< Universally Unique Identifier Low Register, offset: 0x18 */
  uint32_t UUIDML;                                 /**< Universally Unique Identifier Middle Low Register, offset: 0x1C */
  uint32_t UUIDMH;                                 /**< Universally Unique Identifier Middle High Register, offset: 0x20 */
  uint32_t CLKDIV;                                 /**< Clock Divider Register, offset: 0x24 */
} volatile *SIM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SIM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Accessor_Macros SIM - Register accessor macros
 * @{
 */


/* SIM - Register accessors */
#define SIM_SRSID_REG(base)                      ((base)->SRSID)
#define SIM_SOPT0_REG(base)                      ((base)->SOPT0)
#define SIM_SOPT1_REG(base)                      ((base)->SOPT1)
#define SIM_PINSEL_REG(base)                     ((base)->PINSEL)
#define SIM_PINSEL1_REG(base)                    ((base)->PINSEL1)
#define SIM_SCGC_REG(base)                       ((base)->SCGC)
#define SIM_UUIDL_REG(base)                      ((base)->UUIDL)
#define SIM_UUIDML_REG(base)                     ((base)->UUIDML)
#define SIM_UUIDMH_REG(base)                     ((base)->UUIDMH)
#define SIM_CLKDIV_REG(base)                     ((base)->CLKDIV)

/*!
 * @}
 */ /* end of group SIM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SIM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Masks SIM Register Masks
 * @{
 */

/* SRSID Bit Fields */
#define SIM_SRSID_LVD_MASK                       0x2u
#define SIM_SRSID_LVD_SHIFT                      1
#define SIM_SRSID_LOC_MASK                       0x4u
#define SIM_SRSID_LOC_SHIFT                      2
#define SIM_SRSID_WDOG_MASK                      0x20u
#define SIM_SRSID_WDOG_SHIFT                     5
#define SIM_SRSID_PIN_MASK                       0x40u
#define SIM_SRSID_PIN_SHIFT                      6
#define SIM_SRSID_POR_MASK                       0x80u
#define SIM_SRSID_POR_SHIFT                      7
#define SIM_SRSID_LOCKUP_MASK                    0x200u
#define SIM_SRSID_LOCKUP_SHIFT                   9
#define SIM_SRSID_SW_MASK                        0x400u
#define SIM_SRSID_SW_SHIFT                       10
#define SIM_SRSID_MDMAP_MASK                     0x800u
#define SIM_SRSID_MDMAP_SHIFT                    11
#define SIM_SRSID_SACKERR_MASK                   0x2000u
#define SIM_SRSID_SACKERR_SHIFT                  13
#define SIM_SRSID_PINID_MASK                     0xF0000u
#define SIM_SRSID_PINID_SHIFT                    16
#define SIM_SRSID_PINID(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_PINID_SHIFT))&SIM_SRSID_PINID_MASK)
#define SIM_SRSID_RevID_MASK                     0xF00000u
#define SIM_SRSID_RevID_SHIFT                    20
#define SIM_SRSID_RevID(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_RevID_SHIFT))&SIM_SRSID_RevID_MASK)
#define SIM_SRSID_SUBFAMID_MASK                  0xF000000u
#define SIM_SRSID_SUBFAMID_SHIFT                 24
#define SIM_SRSID_SUBFAMID(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_SUBFAMID_SHIFT))&SIM_SRSID_SUBFAMID_MASK)
#define SIM_SRSID_FAMID_MASK                     0xF0000000u
#define SIM_SRSID_FAMID_SHIFT                    28
#define SIM_SRSID_FAMID(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_FAMID_SHIFT))&SIM_SRSID_FAMID_MASK)
/* SOPT0 Bit Fields */
#define SIM_SOPT0_NMIE_MASK                      0x2u
#define SIM_SOPT0_NMIE_SHIFT                     1
#define SIM_SOPT0_RSTPE_MASK                     0x4u
#define SIM_SOPT0_RSTPE_SHIFT                    2
#define SIM_SOPT0_SWDE_MASK                      0x8u
#define SIM_SOPT0_SWDE_SHIFT                     3
#define SIM_SOPT0_ACTRG_MASK                     0x20u
#define SIM_SOPT0_ACTRG_SHIFT                    5
#define SIM_SOPT0_RXDFE_MASK                     0x300u
#define SIM_SOPT0_RXDFE_SHIFT                    8
#define SIM_SOPT0_RXDFE(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SOPT0_RXDFE_SHIFT))&SIM_SOPT0_RXDFE_MASK)
#define SIM_SOPT0_RTCC_MASK                      0x400u
#define SIM_SOPT0_RTCC_SHIFT                     10
#define SIM_SOPT0_ACIC_MASK                      0x800u
#define SIM_SOPT0_ACIC_SHIFT                     11
#define SIM_SOPT0_RXDCE_MASK                     0x1000u
#define SIM_SOPT0_RXDCE_SHIFT                    12
#define SIM_SOPT0_FTMSYNC_MASK                   0x4000u
#define SIM_SOPT0_FTMSYNC_SHIFT                  14
#define SIM_SOPT0_TXDME_MASK                     0x8000u
#define SIM_SOPT0_TXDME_SHIFT                    15
#define SIM_SOPT0_BUSREF_MASK                    0x70000u
#define SIM_SOPT0_BUSREF_SHIFT                   16
#define SIM_SOPT0_BUSREF(x)                      (((uint32_t)(((uint32_t)(x))<<SIM_SOPT0_BUSREF_SHIFT))&SIM_SOPT0_BUSREF_MASK)
#define SIM_SOPT0_CLKOE_MASK                     0x80000u
#define SIM_SOPT0_CLKOE_SHIFT                    19
#define SIM_SOPT0_ADHWT_MASK                     0x700000u
#define SIM_SOPT0_ADHWT_SHIFT                    20
#define SIM_SOPT0_ADHWT(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SOPT0_ADHWT_SHIFT))&SIM_SOPT0_ADHWT_MASK)
#define SIM_SOPT0_DLYACT_MASK                    0x800000u
#define SIM_SOPT0_DLYACT_SHIFT                   23
#define SIM_SOPT0_DELAY_MASK                     0xFF000000u
#define SIM_SOPT0_DELAY_SHIFT                    24
#define SIM_SOPT0_DELAY(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SOPT0_DELAY_SHIFT))&SIM_SOPT0_DELAY_MASK)
/* SOPT1 Bit Fields */
#define SIM_SOPT1_I2C04WEN_MASK                  0x1u
#define SIM_SOPT1_I2C04WEN_SHIFT                 0
#define SIM_SOPT1_I2C0OINV_MASK                  0x2u
#define SIM_SOPT1_I2C0OINV_SHIFT                 1
#define SIM_SOPT1_ACPWTS_MASK                    0x8u
#define SIM_SOPT1_ACPWTS_SHIFT                   3
#define SIM_SOPT1_UARTPWTS_MASK                  0x30u
#define SIM_SOPT1_UARTPWTS_SHIFT                 4
#define SIM_SOPT1_UARTPWTS(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_SOPT1_UARTPWTS_SHIFT))&SIM_SOPT1_UARTPWTS_MASK)
/* PINSEL Bit Fields */
#define SIM_PINSEL_IRQPS_MASK                    0x7u
#define SIM_PINSEL_IRQPS_SHIFT                   0
#define SIM_PINSEL_IRQPS(x)                      (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL_IRQPS_SHIFT))&SIM_PINSEL_IRQPS_MASK)
#define SIM_PINSEL_RTCPS_MASK                    0x10u
#define SIM_PINSEL_RTCPS_SHIFT                   4
#define SIM_PINSEL_I2C0PS_MASK                   0x20u
#define SIM_PINSEL_I2C0PS_SHIFT                  5
#define SIM_PINSEL_SPI0PS_MASK                   0x40u
#define SIM_PINSEL_SPI0PS_SHIFT                  6
#define SIM_PINSEL_UART0PS_MASK                  0x80u
#define SIM_PINSEL_UART0PS_SHIFT                 7
#define SIM_PINSEL_FTM0PS0_MASK                  0x100u
#define SIM_PINSEL_FTM0PS0_SHIFT                 8
#define SIM_PINSEL_FTM0PS1_MASK                  0x200u
#define SIM_PINSEL_FTM0PS1_SHIFT                 9
#define SIM_PINSEL_FTM1PS0_MASK                  0x400u
#define SIM_PINSEL_FTM1PS0_SHIFT                 10
#define SIM_PINSEL_FTM1PS1_MASK                  0x800u
#define SIM_PINSEL_FTM1PS1_SHIFT                 11
#define SIM_PINSEL_FTM0CLKPS_MASK                0x3000000u
#define SIM_PINSEL_FTM0CLKPS_SHIFT               24
#define SIM_PINSEL_FTM0CLKPS(x)                  (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL_FTM0CLKPS_SHIFT))&SIM_PINSEL_FTM0CLKPS_MASK)
#define SIM_PINSEL_FTM1CLKPS_MASK                0xC000000u
#define SIM_PINSEL_FTM1CLKPS_SHIFT               26
#define SIM_PINSEL_FTM1CLKPS(x)                  (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL_FTM1CLKPS_SHIFT))&SIM_PINSEL_FTM1CLKPS_MASK)
#define SIM_PINSEL_FTM2CLKPS_MASK                0x30000000u
#define SIM_PINSEL_FTM2CLKPS_SHIFT               28
#define SIM_PINSEL_FTM2CLKPS(x)                  (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL_FTM2CLKPS_SHIFT))&SIM_PINSEL_FTM2CLKPS_MASK)
#define SIM_PINSEL_PWTCLKPS_MASK                 0xC0000000u
#define SIM_PINSEL_PWTCLKPS_SHIFT                30
#define SIM_PINSEL_PWTCLKPS(x)                   (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL_PWTCLKPS_SHIFT))&SIM_PINSEL_PWTCLKPS_MASK)
/* PINSEL1 Bit Fields */
#define SIM_PINSEL1_FTM2PS0_MASK                 0x3u
#define SIM_PINSEL1_FTM2PS0_SHIFT                0
#define SIM_PINSEL1_FTM2PS0(x)                   (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL1_FTM2PS0_SHIFT))&SIM_PINSEL1_FTM2PS0_MASK)
#define SIM_PINSEL1_FTM2PS1_MASK                 0xCu
#define SIM_PINSEL1_FTM2PS1_SHIFT                2
#define SIM_PINSEL1_FTM2PS1(x)                   (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL1_FTM2PS1_SHIFT))&SIM_PINSEL1_FTM2PS1_MASK)
#define SIM_PINSEL1_FTM2PS2_MASK                 0x30u
#define SIM_PINSEL1_FTM2PS2_SHIFT                4
#define SIM_PINSEL1_FTM2PS2(x)                   (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL1_FTM2PS2_SHIFT))&SIM_PINSEL1_FTM2PS2_MASK)
#define SIM_PINSEL1_FTM2PS3_MASK                 0xC0u
#define SIM_PINSEL1_FTM2PS3_SHIFT                6
#define SIM_PINSEL1_FTM2PS3(x)                   (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL1_FTM2PS3_SHIFT))&SIM_PINSEL1_FTM2PS3_MASK)
#define SIM_PINSEL1_FTM2PS4_MASK                 0x100u
#define SIM_PINSEL1_FTM2PS4_SHIFT                8
#define SIM_PINSEL1_FTM2PS5_MASK                 0x200u
#define SIM_PINSEL1_FTM2PS5_SHIFT                9
#define SIM_PINSEL1_I2C1PS_MASK                  0x400u
#define SIM_PINSEL1_I2C1PS_SHIFT                 10
#define SIM_PINSEL1_SPI1PS_MASK                  0x800u
#define SIM_PINSEL1_SPI1PS_SHIFT                 11
#define SIM_PINSEL1_UART1PS_MASK                 0x1000u
#define SIM_PINSEL1_UART1PS_SHIFT                12
#define SIM_PINSEL1_UART2PS_MASK                 0x2000u
#define SIM_PINSEL1_UART2PS_SHIFT                13
#define SIM_PINSEL1_PWTIN0PS_MASK                0x4000u
#define SIM_PINSEL1_PWTIN0PS_SHIFT               14
#define SIM_PINSEL1_PWTIN1PS_MASK                0x8000u
#define SIM_PINSEL1_PWTIN1PS_SHIFT               15
#define SIM_PINSEL1_MSCANPS_MASK                 0x10000u
#define SIM_PINSEL1_MSCANPS_SHIFT                16
/* SCGC Bit Fields */
#define SIM_SCGC_RTC_MASK                        0x1u
#define SIM_SCGC_RTC_SHIFT                       0
#define SIM_SCGC_PIT_MASK                        0x2u
#define SIM_SCGC_PIT_SHIFT                       1
#define SIM_SCGC_PWT_MASK                        0x10u
#define SIM_SCGC_PWT_SHIFT                       4
#define SIM_SCGC_FTM0_MASK                       0x20u
#define SIM_SCGC_FTM0_SHIFT                      5
#define SIM_SCGC_FTM1_MASK                       0x40u
#define SIM_SCGC_FTM1_SHIFT                      6
#define SIM_SCGC_FTM2_MASK                       0x80u
#define SIM_SCGC_FTM2_SHIFT                      7
#define SIM_SCGC_CRC_MASK                        0x400u
#define SIM_SCGC_CRC_SHIFT                       10
#define SIM_SCGC_FLASH_MASK                      0x1000u
#define SIM_SCGC_FLASH_SHIFT                     12
#define SIM_SCGC_SWD_MASK                        0x2000u
#define SIM_SCGC_SWD_SHIFT                       13
#define SIM_SCGC_MSCAN_MASK                      0x8000u
#define SIM_SCGC_MSCAN_SHIFT                     15
#define SIM_SCGC_I2C0_MASK                       0x10000u
#define SIM_SCGC_I2C0_SHIFT                      16
#define SIM_SCGC_I2C1_MASK                       0x20000u
#define SIM_SCGC_I2C1_SHIFT                      17
#define SIM_SCGC_SPI0_MASK                       0x40000u
#define SIM_SCGC_SPI0_SHIFT                      18
#define SIM_SCGC_SPI1_MASK                       0x80000u
#define SIM_SCGC_SPI1_SHIFT                      19
#define SIM_SCGC_UART0_MASK                      0x100000u
#define SIM_SCGC_UART0_SHIFT                     20
#define SIM_SCGC_UART1_MASK                      0x200000u
#define SIM_SCGC_UART1_SHIFT                     21
#define SIM_SCGC_UART2_MASK                      0x400000u
#define SIM_SCGC_UART2_SHIFT                     22
#define SIM_SCGC_KBI0_MASK                       0x1000000u
#define SIM_SCGC_KBI0_SHIFT                      24
#define SIM_SCGC_KBI1_MASK                       0x2000000u
#define SIM_SCGC_KBI1_SHIFT                      25
#define SIM_SCGC_IRQ_MASK                        0x8000000u
#define SIM_SCGC_IRQ_SHIFT                       27
#define SIM_SCGC_ADC_MASK                        0x20000000u
#define SIM_SCGC_ADC_SHIFT                       29
#define SIM_SCGC_ACMP0_MASK                      0x40000000u
#define SIM_SCGC_ACMP0_SHIFT                     30
#define SIM_SCGC_ACMP1_MASK                      0x80000000u
#define SIM_SCGC_ACMP1_SHIFT                     31
/* UUIDL Bit Fields */
#define SIM_UUIDL_ID_MASK                        0xFFFFFFFFu
#define SIM_UUIDL_ID_SHIFT                       0
#define SIM_UUIDL_ID(x)                          (((uint32_t)(((uint32_t)(x))<<SIM_UUIDL_ID_SHIFT))&SIM_UUIDL_ID_MASK)
/* UUIDML Bit Fields */
#define SIM_UUIDML_ID_MASK                       0xFFFFFFFFu
#define SIM_UUIDML_ID_SHIFT                      0
#define SIM_UUIDML_ID(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_UUIDML_ID_SHIFT))&SIM_UUIDML_ID_MASK)
/* UUIDMH Bit Fields */
#define SIM_UUIDMH_ID_MASK                       0xFFFFu
#define SIM_UUIDMH_ID_SHIFT                      0
#define SIM_UUIDMH_ID(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_UUIDMH_ID_SHIFT))&SIM_UUIDMH_ID_MASK)
/* CLKDIV Bit Fields */
#define SIM_CLKDIV_OUTDIV3_MASK                  0x100000u
#define SIM_CLKDIV_OUTDIV3_SHIFT                 20
#define SIM_CLKDIV_OUTDIV2_MASK                  0x1000000u
#define SIM_CLKDIV_OUTDIV2_SHIFT                 24
#define SIM_CLKDIV_OUTDIV1_MASK                  0x30000000u
#define SIM_CLKDIV_OUTDIV1_SHIFT                 28
#define SIM_CLKDIV_OUTDIV1(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_CLKDIV_OUTDIV1_SHIFT))&SIM_CLKDIV_OUTDIV1_MASK)

/*!
 * @}
 */ /* end of group SIM_Register_Masks */


/* SIM - Peripheral instance base addresses */
/** Peripheral SIM base pointer */
#define SIM_BASE_PTR                             ((SIM_MemMapPtr)0x40048000u)
/** Array initializer of SIM peripheral base pointers */
#define SIM_BASE_PTRS                            { SIM_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- SIM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Accessor_Macros SIM - Register accessor macros
 * @{
 */


/* SIM - Register instance definitions */
/* SIM */
#define SIM_SRSID                                SIM_SRSID_REG(SIM_BASE_PTR)
#define SIM_SOPT0                                SIM_SOPT0_REG(SIM_BASE_PTR)
#define SIM_SOPT1                                SIM_SOPT1_REG(SIM_BASE_PTR)
#define SIM_PINSEL0                              SIM_PINSEL_REG(SIM_BASE_PTR)
#define SIM_PINSEL1                              SIM_PINSEL1_REG(SIM_BASE_PTR)
#define SIM_SCGC                                 SIM_SCGC_REG(SIM_BASE_PTR)
#define SIM_UUIDL                                SIM_UUIDL_REG(SIM_BASE_PTR)
#define SIM_UUIDML                               SIM_UUIDML_REG(SIM_BASE_PTR)
#define SIM_UUIDMH                               SIM_UUIDMH_REG(SIM_BASE_PTR)
#define SIM_CLKDIV                               SIM_CLKDIV_REG(SIM_BASE_PTR)

/*!
 * @}
 */ /* end of group SIM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group SIM_Peripheral */


/* ----------------------------------------------------------------------------
   -- SPI
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Peripheral SPI
 * @{
 */

/** SPI - Peripheral register structure */
typedef struct SPI_MemMap {
  uint8_t C1;                                      /**< SPI Control Register 1, offset: 0x0 */
  uint8_t C2;                                      /**< SPI Control Register 2, offset: 0x1 */
  uint8_t BR;                                      /**< SPI Baud Rate Register, offset: 0x2 */
  uint8_t S;                                       /**< SPI Status Register, offset: 0x3 */
  uint8_t RESERVED_0[1];
  uint8_t D;                                       /**< SPI Data Register, offset: 0x5 */
  uint8_t RESERVED_1[1];
  uint8_t M;                                       /**< SPI Match Register, offset: 0x7 */
} volatile *SPI_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SPI - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Accessor_Macros SPI - Register accessor macros
 * @{
 */


/* SPI - Register accessors */
#define SPI_C1_REG(base)                         ((base)->C1)
#define SPI_C2_REG(base)                         ((base)->C2)
#define SPI_BR_REG(base)                         ((base)->BR)
#define SPI_S_REG(base)                          ((base)->S)
#define SPI_D_REG(base)                          ((base)->D)
#define SPI_M_REG(base)                          ((base)->M)

/*!
 * @}
 */ /* end of group SPI_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SPI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Masks SPI Register Masks
 * @{
 */

/* C1 Bit Fields */
#define SPI_C1_LSBFE_MASK                        0x1u
#define SPI_C1_LSBFE_SHIFT                       0
#define SPI_C1_SSOE_MASK                         0x2u
#define SPI_C1_SSOE_SHIFT                        1
#define SPI_C1_CPHA_MASK                         0x4u
#define SPI_C1_CPHA_SHIFT                        2
#define SPI_C1_CPOL_MASK                         0x8u
#define SPI_C1_CPOL_SHIFT                        3
#define SPI_C1_MSTR_MASK                         0x10u
#define SPI_C1_MSTR_SHIFT                        4
#define SPI_C1_SPTIE_MASK                        0x20u
#define SPI_C1_SPTIE_SHIFT                       5
#define SPI_C1_SPE_MASK                          0x40u
#define SPI_C1_SPE_SHIFT                         6
#define SPI_C1_SPIE_MASK                         0x80u
#define SPI_C1_SPIE_SHIFT                        7
/* C2 Bit Fields */
#define SPI_C2_SPC0_MASK                         0x1u
#define SPI_C2_SPC0_SHIFT                        0
#define SPI_C2_SPISWAI_MASK                      0x2u
#define SPI_C2_SPISWAI_SHIFT                     1
#define SPI_C2_BIDIROE_MASK                      0x8u
#define SPI_C2_BIDIROE_SHIFT                     3
#define SPI_C2_MODFEN_MASK                       0x10u
#define SPI_C2_MODFEN_SHIFT                      4
#define SPI_C2_SPMIE_MASK                        0x80u
#define SPI_C2_SPMIE_SHIFT                       7
/* BR Bit Fields */
#define SPI_BR_SPR_MASK                          0xFu
#define SPI_BR_SPR_SHIFT                         0
#define SPI_BR_SPR(x)                            (((uint8_t)(((uint8_t)(x))<<SPI_BR_SPR_SHIFT))&SPI_BR_SPR_MASK)
#define SPI_BR_SPPR_MASK                         0x70u
#define SPI_BR_SPPR_SHIFT                        4
#define SPI_BR_SPPR(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_BR_SPPR_SHIFT))&SPI_BR_SPPR_MASK)
/* S Bit Fields */
#define SPI_S_MODF_MASK                          0x10u
#define SPI_S_MODF_SHIFT                         4
#define SPI_S_SPTEF_MASK                         0x20u
#define SPI_S_SPTEF_SHIFT                        5
#define SPI_S_SPMF_MASK                          0x40u
#define SPI_S_SPMF_SHIFT                         6
#define SPI_S_SPRF_MASK                          0x80u
#define SPI_S_SPRF_SHIFT                         7
/* D Bit Fields */
#define SPI_D_Bits_MASK                          0xFFu
#define SPI_D_Bits_SHIFT                         0
#define SPI_D_Bits(x)                            (((uint8_t)(((uint8_t)(x))<<SPI_D_Bits_SHIFT))&SPI_D_Bits_MASK)
/* M Bit Fields */
#define SPI_M_Bits_MASK                          0xFFu
#define SPI_M_Bits_SHIFT                         0
#define SPI_M_Bits(x)                            (((uint8_t)(((uint8_t)(x))<<SPI_M_Bits_SHIFT))&SPI_M_Bits_MASK)

/*!
 * @}
 */ /* end of group SPI_Register_Masks */


/* SPI - Peripheral instance base addresses */
/** Peripheral SPI0 base pointer */
#define SPI0_BASE_PTR                            ((SPI_MemMapPtr)0x40076000u)
/** Peripheral SPI1 base pointer */
#define SPI1_BASE_PTR                            ((SPI_MemMapPtr)0x40077000u)
/** Array initializer of SPI peripheral base pointers */
#define SPI_BASE_PTRS                            { SPI0_BASE_PTR, SPI1_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- SPI - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Accessor_Macros SPI - Register accessor macros
 * @{
 */


/* SPI - Register instance definitions */
/* SPI0 */
#define SPI0_C1                                  SPI_C1_REG(SPI0_BASE_PTR)
#define SPI0_C2                                  SPI_C2_REG(SPI0_BASE_PTR)
#define SPI0_BR                                  SPI_BR_REG(SPI0_BASE_PTR)
#define SPI0_S                                   SPI_S_REG(SPI0_BASE_PTR)
#define SPI0_D                                   SPI_D_REG(SPI0_BASE_PTR)
#define SPI0_M                                   SPI_M_REG(SPI0_BASE_PTR)
/* SPI1 */
#define SPI1_C1                                  SPI_C1_REG(SPI1_BASE_PTR)
#define SPI1_C2                                  SPI_C2_REG(SPI1_BASE_PTR)
#define SPI1_BR                                  SPI_BR_REG(SPI1_BASE_PTR)
#define SPI1_S                                   SPI_S_REG(SPI1_BASE_PTR)
#define SPI1_D                                   SPI_D_REG(SPI1_BASE_PTR)
#define SPI1_M                                   SPI_M_REG(SPI1_BASE_PTR)

/*!
 * @}
 */ /* end of group SPI_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group SPI_Peripheral */


/* ----------------------------------------------------------------------------
   -- SysTick
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SysTick_Peripheral SysTick
 * @{
 */

/** SysTick - Peripheral register structure */
typedef struct SysTick_MemMap {
  uint32_t CSR;                                    /**< SysTick Control and Status Register, offset: 0x0 */
  uint32_t RVR;                                    /**< SysTick Reload Value Register, offset: 0x4 */
  uint32_t CVR;                                    /**< SysTick Current Value Register, offset: 0x8 */
  uint32_t CALIB;                                  /**< SysTick Calibration Value Register, offset: 0xC */
} volatile *SysTick_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SysTick - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SysTick_Register_Accessor_Macros SysTick - Register accessor macros
 * @{
 */


/* SysTick - Register accessors */
#define SysTick_CSR_REG(base)                    ((base)->CSR)
#define SysTick_RVR_REG(base)                    ((base)->RVR)
#define SysTick_CVR_REG(base)                    ((base)->CVR)
#define SysTick_CALIB_REG(base)                  ((base)->CALIB)

/*!
 * @}
 */ /* end of group SysTick_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SysTick Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SysTick_Register_Masks SysTick Register Masks
 * @{
 */

/* CSR Bit Fields */
#define SysTick_CSR_ENABLE_MASK                  0x1u
#define SysTick_CSR_ENABLE_SHIFT                 0
#define SysTick_CSR_TICKINT_MASK                 0x2u
#define SysTick_CSR_TICKINT_SHIFT                1
#define SysTick_CSR_CLKSOURCE_MASK               0x4u
#define SysTick_CSR_CLKSOURCE_SHIFT              2
#define SysTick_CSR_COUNTFLAG_MASK               0x10000u
#define SysTick_CSR_COUNTFLAG_SHIFT              16
/* RVR Bit Fields */
#define SysTick_RVR_RELOAD_MASK                  0xFFFFFFu
#define SysTick_RVR_RELOAD_SHIFT                 0
#define SysTick_RVR_RELOAD(x)                    (((uint32_t)(((uint32_t)(x))<<SysTick_RVR_RELOAD_SHIFT))&SysTick_RVR_RELOAD_MASK)
/* CVR Bit Fields */
#define SysTick_CVR_CURRENT_MASK                 0xFFFFFFu
#define SysTick_CVR_CURRENT_SHIFT                0
#define SysTick_CVR_CURRENT(x)                   (((uint32_t)(((uint32_t)(x))<<SysTick_CVR_CURRENT_SHIFT))&SysTick_CVR_CURRENT_MASK)
/* CALIB Bit Fields */
#define SysTick_CALIB_TENMS_MASK                 0xFFFFFFu
#define SysTick_CALIB_TENMS_SHIFT                0
#define SysTick_CALIB_TENMS(x)                   (((uint32_t)(((uint32_t)(x))<<SysTick_CALIB_TENMS_SHIFT))&SysTick_CALIB_TENMS_MASK)
#define SysTick_CALIB_SKEW_MASK                  0x40000000u
#define SysTick_CALIB_SKEW_SHIFT                 30
#define SysTick_CALIB_NOREF_MASK                 0x80000000u
#define SysTick_CALIB_NOREF_SHIFT                31

/*!
 * @}
 */ /* end of group SysTick_Register_Masks */


/* SysTick - Peripheral instance base addresses */
/** Peripheral SysTick base pointer */
#define SysTick_BASE_PTR                         ((SysTick_MemMapPtr)0xE000E010u)
/** Array initializer of SysTick peripheral base pointers */
#define SysTick_BASE_PTRS                        { SysTick_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- SysTick - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SysTick_Register_Accessor_Macros SysTick - Register accessor macros
 * @{
 */


/* SysTick - Register instance definitions */
/* SysTick */
#define SYST_CSR                                 SysTick_CSR_REG(SysTick_BASE_PTR)
#define SYST_RVR                                 SysTick_RVR_REG(SysTick_BASE_PTR)
#define SYST_CVR                                 SysTick_CVR_REG(SysTick_BASE_PTR)
#define SYST_CALIB                               SysTick_CALIB_REG(SysTick_BASE_PTR)

/*!
 * @}
 */ /* end of group SysTick_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group SysTick_Peripheral */


/* ----------------------------------------------------------------------------
   -- UART
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Peripheral UART
 * @{
 */

/** UART - Peripheral register structure */
typedef struct UART_MemMap {
  uint8_t BDH;                                     /**< UART Baud Rate Register: High, offset: 0x0 */
  uint8_t BDL;                                     /**< UART Baud Rate Register: Low, offset: 0x1 */
  uint8_t C1;                                      /**< UART Control Register 1, offset: 0x2 */
  uint8_t C2;                                      /**< UART Control Register 2, offset: 0x3 */
  uint8_t S1;                                      /**< UART Status Register 1, offset: 0x4 */
  uint8_t S2;                                      /**< UART Status Register 2, offset: 0x5 */
  uint8_t C3;                                      /**< UART Control Register 3, offset: 0x6 */
  uint8_t D;                                       /**< UART Data Register, offset: 0x7 */
} volatile *UART_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- UART - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Accessor_Macros UART - Register accessor macros
 * @{
 */


/* UART - Register accessors */
#define UART_BDH_REG(base)                       ((base)->BDH)
#define UART_BDL_REG(base)                       ((base)->BDL)
#define UART_C1_REG(base)                        ((base)->C1)
#define UART_C2_REG(base)                        ((base)->C2)
#define UART_S1_REG(base)                        ((base)->S1)
#define UART_S2_REG(base)                        ((base)->S2)
#define UART_C3_REG(base)                        ((base)->C3)
#define UART_D_REG(base)                         ((base)->D)

/*!
 * @}
 */ /* end of group UART_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- UART Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Masks UART Register Masks
 * @{
 */

/* BDH Bit Fields */
#define UART_BDH_SBR_MASK                        0x1Fu
#define UART_BDH_SBR_SHIFT                       0
#define UART_BDH_SBR(x)                          (((uint8_t)(((uint8_t)(x))<<UART_BDH_SBR_SHIFT))&UART_BDH_SBR_MASK)
#define UART_BDH_SBNS_MASK                       0x20u
#define UART_BDH_SBNS_SHIFT                      5
#define UART_BDH_RXEDGIE_MASK                    0x40u
#define UART_BDH_RXEDGIE_SHIFT                   6
#define UART_BDH_LBKDIE_MASK                     0x80u
#define UART_BDH_LBKDIE_SHIFT                    7
/* BDL Bit Fields */
#define UART_BDL_SBR_MASK                        0xFFu
#define UART_BDL_SBR_SHIFT                       0
#define UART_BDL_SBR(x)                          (((uint8_t)(((uint8_t)(x))<<UART_BDL_SBR_SHIFT))&UART_BDL_SBR_MASK)
/* C1 Bit Fields */
#define UART_C1_PT_MASK                          0x1u
#define UART_C1_PT_SHIFT                         0
#define UART_C1_PE_MASK                          0x2u
#define UART_C1_PE_SHIFT                         1
#define UART_C1_ILT_MASK                         0x4u
#define UART_C1_ILT_SHIFT                        2
#define UART_C1_WAKE_MASK                        0x8u
#define UART_C1_WAKE_SHIFT                       3
#define UART_C1_M_MASK                           0x10u
#define UART_C1_M_SHIFT                          4
#define UART_C1_RSRC_MASK                        0x20u
#define UART_C1_RSRC_SHIFT                       5
#define UART_C1_UARTSWAI_MASK                    0x40u
#define UART_C1_UARTSWAI_SHIFT                   6
#define UART_C1_LOOPS_MASK                       0x80u
#define UART_C1_LOOPS_SHIFT                      7
/* C2 Bit Fields */
#define UART_C2_SBK_MASK                         0x1u
#define UART_C2_SBK_SHIFT                        0
#define UART_C2_RWU_MASK                         0x2u
#define UART_C2_RWU_SHIFT                        1
#define UART_C2_RE_MASK                          0x4u
#define UART_C2_RE_SHIFT                         2
#define UART_C2_TE_MASK                          0x8u
#define UART_C2_TE_SHIFT                         3
#define UART_C2_ILIE_MASK                        0x10u
#define UART_C2_ILIE_SHIFT                       4
#define UART_C2_RIE_MASK                         0x20u
#define UART_C2_RIE_SHIFT                        5
#define UART_C2_TCIE_MASK                        0x40u
#define UART_C2_TCIE_SHIFT                       6
#define UART_C2_TIE_MASK                         0x80u
#define UART_C2_TIE_SHIFT                        7
/* S1 Bit Fields */
#define UART_S1_PF_MASK                          0x1u
#define UART_S1_PF_SHIFT                         0
#define UART_S1_FE_MASK                          0x2u
#define UART_S1_FE_SHIFT                         1
#define UART_S1_NF_MASK                          0x4u
#define UART_S1_NF_SHIFT                         2
#define UART_S1_OR_MASK                          0x8u
#define UART_S1_OR_SHIFT                         3
#define UART_S1_IDLE_MASK                        0x10u
#define UART_S1_IDLE_SHIFT                       4
#define UART_S1_RDRF_MASK                        0x20u
#define UART_S1_RDRF_SHIFT                       5
#define UART_S1_TC_MASK                          0x40u
#define UART_S1_TC_SHIFT                         6
#define UART_S1_TDRE_MASK                        0x80u
#define UART_S1_TDRE_SHIFT                       7
/* S2 Bit Fields */
#define UART_S2_RAF_MASK                         0x1u
#define UART_S2_RAF_SHIFT                        0
#define UART_S2_LBKDE_MASK                       0x2u
#define UART_S2_LBKDE_SHIFT                      1
#define UART_S2_BRK13_MASK                       0x4u
#define UART_S2_BRK13_SHIFT                      2
#define UART_S2_RWUID_MASK                       0x8u
#define UART_S2_RWUID_SHIFT                      3
#define UART_S2_RXINV_MASK                       0x10u
#define UART_S2_RXINV_SHIFT                      4
#define UART_S2_RXEDGIF_MASK                     0x40u
#define UART_S2_RXEDGIF_SHIFT                    6
#define UART_S2_LBKDIF_MASK                      0x80u
#define UART_S2_LBKDIF_SHIFT                     7
/* C3 Bit Fields */
#define UART_C3_PEIE_MASK                        0x1u
#define UART_C3_PEIE_SHIFT                       0
#define UART_C3_FEIE_MASK                        0x2u
#define UART_C3_FEIE_SHIFT                       1
#define UART_C3_NEIE_MASK                        0x4u
#define UART_C3_NEIE_SHIFT                       2
#define UART_C3_ORIE_MASK                        0x8u
#define UART_C3_ORIE_SHIFT                       3
#define UART_C3_TXINV_MASK                       0x10u
#define UART_C3_TXINV_SHIFT                      4
#define UART_C3_TXDIR_MASK                       0x20u
#define UART_C3_TXDIR_SHIFT                      5
#define UART_C3_T8_MASK                          0x40u
#define UART_C3_T8_SHIFT                         6
#define UART_C3_R8_MASK                          0x80u
#define UART_C3_R8_SHIFT                         7
/* D Bit Fields */
#define UART_D_R0T0_MASK                         0x1u
#define UART_D_R0T0_SHIFT                        0
#define UART_D_R1T1_MASK                         0x2u
#define UART_D_R1T1_SHIFT                        1
#define UART_D_R2T2_MASK                         0x4u
#define UART_D_R2T2_SHIFT                        2
#define UART_D_R3T3_MASK                         0x8u
#define UART_D_R3T3_SHIFT                        3
#define UART_D_R4T4_MASK                         0x10u
#define UART_D_R4T4_SHIFT                        4
#define UART_D_R5T5_MASK                         0x20u
#define UART_D_R5T5_SHIFT                        5
#define UART_D_R6T6_MASK                         0x40u
#define UART_D_R6T6_SHIFT                        6
#define UART_D_R7T7_MASK                         0x80u
#define UART_D_R7T7_SHIFT                        7

/*!
 * @}
 */ /* end of group UART_Register_Masks */


/* UART - Peripheral instance base addresses */
/** Peripheral UART0 base pointer */
#define UART0_BASE_PTR                           ((UART_MemMapPtr)0x4006A000u)
/** Peripheral UART1 base pointer */
#define UART1_BASE_PTR                           ((UART_MemMapPtr)0x4006B000u)
/** Peripheral UART2 base pointer */
#define UART2_BASE_PTR                           ((UART_MemMapPtr)0x4006C000u)
/** Array initializer of UART peripheral base pointers */
#define UART_BASE_PTRS                           { UART0_BASE_PTR, UART1_BASE_PTR, UART2_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- UART - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Accessor_Macros UART - Register accessor macros
 * @{
 */


/* UART - Register instance definitions */
/* UART0 */
#define UART0_BDH                                UART_BDH_REG(UART0_BASE_PTR)
#define UART0_BDL                                UART_BDL_REG(UART0_BASE_PTR)
#define UART0_C1                                 UART_C1_REG(UART0_BASE_PTR)
#define UART0_C2                                 UART_C2_REG(UART0_BASE_PTR)
#define UART0_S1                                 UART_S1_REG(UART0_BASE_PTR)
#define UART0_S2                                 UART_S2_REG(UART0_BASE_PTR)
#define UART0_C3                                 UART_C3_REG(UART0_BASE_PTR)
#define UART0_D                                  UART_D_REG(UART0_BASE_PTR)
/* UART1 */
#define UART1_BDH                                UART_BDH_REG(UART1_BASE_PTR)
#define UART1_BDL                                UART_BDL_REG(UART1_BASE_PTR)
#define UART1_C1                                 UART_C1_REG(UART1_BASE_PTR)
#define UART1_C2                                 UART_C2_REG(UART1_BASE_PTR)
#define UART1_S1                                 UART_S1_REG(UART1_BASE_PTR)
#define UART1_S2                                 UART_S2_REG(UART1_BASE_PTR)
#define UART1_C3                                 UART_C3_REG(UART1_BASE_PTR)
#define UART1_D                                  UART_D_REG(UART1_BASE_PTR)
/* UART2 */
#define UART2_BDH                                UART_BDH_REG(UART2_BASE_PTR)
#define UART2_BDL                                UART_BDL_REG(UART2_BASE_PTR)
#define UART2_C1                                 UART_C1_REG(UART2_BASE_PTR)
#define UART2_C2                                 UART_C2_REG(UART2_BASE_PTR)
#define UART2_S1                                 UART_S1_REG(UART2_BASE_PTR)
#define UART2_S2                                 UART_S2_REG(UART2_BASE_PTR)
#define UART2_C3                                 UART_C3_REG(UART2_BASE_PTR)
#define UART2_D                                  UART_D_REG(UART2_BASE_PTR)

/*!
 * @}
 */ /* end of group UART_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group UART_Peripheral */


/* ----------------------------------------------------------------------------
   -- WDOG
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Peripheral WDOG
 * @{
 */

/** WDOG - Peripheral register structure */
typedef struct WDOG_MemMap {
  uint8_t CS1;                                     /**< Watchdog Control and Status Register 1, offset: 0x0 */
  uint8_t CS2;                                     /**< Watchdog Control and Status Register 2, offset: 0x1 */
  union {                                          /* offset: 0x2 */
    uint16_t CNT;                                    /**< Watchdog Counter Register., offset: 0x2 */
    struct {                                         /* offset: 0x2 */
      uint8_t CNTH;                                    /**< Watchdog Counter Register: High, offset: 0x2 */
      uint8_t CNTL;                                    /**< Watchdog Counter Register: Low, offset: 0x3 */
    } CNT8B;
  };
  union {                                          /* offset: 0x4 */
    uint16_t TOVAL;                                  /**< Watchdog Timeout Value Register., offset: 0x4 */
    struct {                                         /* offset: 0x4 */
      uint8_t TOVALH;                                  /**< Watchdog Timeout Value Register: High, offset: 0x4 */
      uint8_t TOVALL;                                  /**< Watchdog Timeout Value Register: Low, offset: 0x5 */
    } TOVAL8B;
  };
  union {                                          /* offset: 0x6 */
    uint16_t WIN;                                    /**< Watchdog Window Register., offset: 0x6 */
    struct {                                         /* offset: 0x6 */
      uint8_t WINH;                                    /**< Watchdog Window Register: High, offset: 0x6 */
      uint8_t WINL;                                    /**< Watchdog Window Register: Low, offset: 0x7 */
    } WIN8B;
  };
} volatile *WDOG_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- WDOG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Accessor_Macros WDOG - Register accessor macros
 * @{
 */


/* WDOG - Register accessors */
#define WDOG_CS1_REG(base)                       ((base)->CS1)
#define WDOG_CS2_REG(base)                       ((base)->CS2)
#define WDOG_CNT_REG(base)                       ((base)->CNT)
#define WDOG_CNTH_REG(base)                      ((base)->CNT8B.CNTH)
#define WDOG_CNTL_REG(base)                      ((base)->CNT8B.CNTL)
#define WDOG_TOVAL_REG(base)                     ((base)->TOVAL)
#define WDOG_TOVALH_REG(base)                    ((base)->TOVAL8B.TOVALH)
#define WDOG_TOVALL_REG(base)                    ((base)->TOVAL8B.TOVALL)
#define WDOG_WIN_REG(base)                       ((base)->WIN)
#define WDOG_WINH_REG(base)                      ((base)->WIN8B.WINH)
#define WDOG_WINL_REG(base)                      ((base)->WIN8B.WINL)

/*!
 * @}
 */ /* end of group WDOG_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- WDOG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Masks WDOG Register Masks
 * @{
 */

/* CS1 Bit Fields */
#define WDOG_CS1_STOP_MASK                       0x1u
#define WDOG_CS1_STOP_SHIFT                      0
#define WDOG_CS1_WAIT_MASK                       0x2u
#define WDOG_CS1_WAIT_SHIFT                      1
#define WDOG_CS1_DBG_MASK                        0x4u
#define WDOG_CS1_DBG_SHIFT                       2
#define WDOG_CS1_TST_MASK                        0x18u
#define WDOG_CS1_TST_SHIFT                       3
#define WDOG_CS1_TST(x)                          (((uint8_t)(((uint8_t)(x))<<WDOG_CS1_TST_SHIFT))&WDOG_CS1_TST_MASK)
#define WDOG_CS1_UPDATE_MASK                     0x20u
#define WDOG_CS1_UPDATE_SHIFT                    5
#define WDOG_CS1_INT_MASK                        0x40u
#define WDOG_CS1_INT_SHIFT                       6
#define WDOG_CS1_EN_MASK                         0x80u
#define WDOG_CS1_EN_SHIFT                        7
/* CS2 Bit Fields */
#define WDOG_CS2_CLK_MASK                        0x3u
#define WDOG_CS2_CLK_SHIFT                       0
#define WDOG_CS2_CLK(x)                          (((uint8_t)(((uint8_t)(x))<<WDOG_CS2_CLK_SHIFT))&WDOG_CS2_CLK_MASK)
#define WDOG_CS2_PRES_MASK                       0x10u
#define WDOG_CS2_PRES_SHIFT                      4
#define WDOG_CS2_FLG_MASK                        0x40u
#define WDOG_CS2_FLG_SHIFT                       6
#define WDOG_CS2_WIN_MASK                        0x80u
#define WDOG_CS2_WIN_SHIFT                       7
/* CNT Bit Fields */
#define WDOG_CNT_CNT_MASK                        0xFFFFu
#define WDOG_CNT_CNT_SHIFT                       0
#define WDOG_CNT_CNT(x)                          (((uint16_t)(((uint16_t)(x))<<WDOG_CNT_CNT_SHIFT))&WDOG_CNT_CNT_MASK)
/* CNTH Bit Fields */
#define WDOG_CNTH_CNTHIGH_MASK                   0xFFu
#define WDOG_CNTH_CNTHIGH_SHIFT                  0
#define WDOG_CNTH_CNTHIGH(x)                     (((uint8_t)(((uint8_t)(x))<<WDOG_CNTH_CNTHIGH_SHIFT))&WDOG_CNTH_CNTHIGH_MASK)
/* CNTL Bit Fields */
#define WDOG_CNTL_CNTLOW_MASK                    0xFFu
#define WDOG_CNTL_CNTLOW_SHIFT                   0
#define WDOG_CNTL_CNTLOW(x)                      (((uint8_t)(((uint8_t)(x))<<WDOG_CNTL_CNTLOW_SHIFT))&WDOG_CNTL_CNTLOW_MASK)
/* TOVAL Bit Fields */
#define WDOG_TOVAL_TOVAL_MASK                    0xFFFFu
#define WDOG_TOVAL_TOVAL_SHIFT                   0
#define WDOG_TOVAL_TOVAL(x)                      (((uint16_t)(((uint16_t)(x))<<WDOG_TOVAL_TOVAL_SHIFT))&WDOG_TOVAL_TOVAL_MASK)
/* TOVALH Bit Fields */
#define WDOG_TOVALH_TOVALHIGH_MASK               0xFFu
#define WDOG_TOVALH_TOVALHIGH_SHIFT              0
#define WDOG_TOVALH_TOVALHIGH(x)                 (((uint8_t)(((uint8_t)(x))<<WDOG_TOVALH_TOVALHIGH_SHIFT))&WDOG_TOVALH_TOVALHIGH_MASK)
/* TOVALL Bit Fields */
#define WDOG_TOVALL_TOVALLOW_MASK                0xFFu
#define WDOG_TOVALL_TOVALLOW_SHIFT               0
#define WDOG_TOVALL_TOVALLOW(x)                  (((uint8_t)(((uint8_t)(x))<<WDOG_TOVALL_TOVALLOW_SHIFT))&WDOG_TOVALL_TOVALLOW_MASK)
/* WIN Bit Fields */
#define WDOG_WIN_WIN_MASK                        0xFFFFu
#define WDOG_WIN_WIN_SHIFT                       0
#define WDOG_WIN_WIN(x)                          (((uint16_t)(((uint16_t)(x))<<WDOG_WIN_WIN_SHIFT))&WDOG_WIN_WIN_MASK)
/* WINH Bit Fields */
#define WDOG_WINH_WINHIGH_MASK                   0xFFu
#define WDOG_WINH_WINHIGH_SHIFT                  0
#define WDOG_WINH_WINHIGH(x)                     (((uint8_t)(((uint8_t)(x))<<WDOG_WINH_WINHIGH_SHIFT))&WDOG_WINH_WINHIGH_MASK)
/* WINL Bit Fields */
#define WDOG_WINL_WINLOW_MASK                    0xFFu
#define WDOG_WINL_WINLOW_SHIFT                   0
#define WDOG_WINL_WINLOW(x)                      (((uint8_t)(((uint8_t)(x))<<WDOG_WINL_WINLOW_SHIFT))&WDOG_WINL_WINLOW_MASK)

/*!
 * @}
 */ /* end of group WDOG_Register_Masks */


/* WDOG - Peripheral instance base addresses */
/** Peripheral WDOG base pointer */
#define WDOG_BASE_PTR                            ((WDOG_MemMapPtr)0x40052000u)
/** Array initializer of WDOG peripheral base pointers */
#define WDOG_BASE_PTRS                           { WDOG_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- WDOG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Accessor_Macros WDOG - Register accessor macros
 * @{
 */


/* WDOG - Register instance definitions */
/* WDOG */
#define WDOG_CS1                                 WDOG_CS1_REG(WDOG_BASE_PTR)
#define WDOG_CS2                                 WDOG_CS2_REG(WDOG_BASE_PTR)
#define WDOG_CNT                                 WDOG_CNT_REG(WDOG_BASE_PTR)
#define WDOG_CNTH                                WDOG_CNTH_REG(WDOG_BASE_PTR)
#define WDOG_CNTL                                WDOG_CNTL_REG(WDOG_BASE_PTR)
#define WDOG_TOVAL                               WDOG_TOVAL_REG(WDOG_BASE_PTR)
#define WDOG_TOVALH                              WDOG_TOVALH_REG(WDOG_BASE_PTR)
#define WDOG_TOVALL                              WDOG_TOVALL_REG(WDOG_BASE_PTR)
#define WDOG_WIN                                 WDOG_WIN_REG(WDOG_BASE_PTR)
#define WDOG_WINH                                WDOG_WINH_REG(WDOG_BASE_PTR)
#define WDOG_WINL                                WDOG_WINL_REG(WDOG_BASE_PTR)

/*!
 * @}
 */ /* end of group WDOG_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group WDOG_Peripheral */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #pragma pop
#elif defined(__CWCC__)
  #pragma pop
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_defines */


/* ----------------------------------------------------------------------------
   -- Backward Compatibility
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Backward_Compatibility_Symbols Backward Compatibility
 * @{
 */

#define NVIC_ISER_SETENA_MASK        This_symbol_has_been_deprecated
#define NVIC_ISER_SETENA_SHIFT       This_symbol_has_been_deprecated
#define NVIC_ISER_SETENA(x)          This_symbol_has_been_deprecated
#define NVIC_ICER_CLRENA_MASK        This_symbol_has_been_deprecated
#define NVIC_ICER_CLRENA_SHIFT       This_symbol_has_been_deprecated
#define NVIC_ICER_CLRENA(x)          This_symbol_has_been_deprecated
#define NVIC_ISPR_SETPEND_MASK       This_symbol_has_been_deprecated
#define NVIC_ISPR_SETPEND_SHIFT      This_symbol_has_been_deprecated
#define NVIC_ISPR_SETPEND(x)         This_symbol_has_been_deprecated
#define NVIC_ICPR_CLRPEND_MASK       This_symbol_has_been_deprecated
#define NVIC_ICPR_CLRPEND_SHIFT      This_symbol_has_been_deprecated
#define NVIC_ICPR_CLRPEND(x)         This_symbol_has_been_deprecated
#define SCB_ICSR_VECTACTIVE_MASK     This_symbol_has_been_deprecated
#define SCB_ICSR_VECTACTIVE_SHIFT    This_symbol_has_been_deprecated
#define SCB_ICSR_VECTACTIVE(x)       This_symbol_has_been_deprecated
#define SCB_ICSR_ISRPENDING_MASK     This_symbol_has_been_deprecated
#define SCB_ICSR_ISRPENDING_SHIFT    This_symbol_has_been_deprecated
#define INT_LVD_LVW                  INT_PMC
#define INT_ADC0                     INT_ADC
#define MSCAN_TDLR_DLC_MASK          MSCAN_TDLR_TDLC_MASK
#define MSCAN_TDLR_DLC_SHIFT         MSCAN_TDLR_TDLC_SHIFT
#define MSCAN_TDLR_DLC(x)            MSCAN_TDLR_TDLC(x)
#define I2C_S_REG(base)              I2C_S1_REG(base)
#define I2C_S_RXAK_MASK              I2C_S1_RXAK_MASK
#define I2C_S_RXAK_SHIFT             I2C_S1_RXAK_SHIFT
#define I2C_S_IICIF_MASK             I2C_S1_IICIF_MASK
#define I2C_S_IICIF_SHIFT            I2C_S1_IICIF_SHIFT
#define I2C_S_SRW_MASK               I2C_S1_SRW_MASK
#define I2C_S_SRW_SHIFT              I2C_S1_SRW_SHIFT
#define I2C_S_RAM_MASK               I2C_S1_RAM_MASK
#define I2C_S_RAM_SHIFT              I2C_S1_RAM_SHIFT
#define I2C_S_ARBL_MASK              I2C_S1_ARBL_MASK
#define I2C_S_ARBL_SHIFT             I2C_S1_ARBL_SHIFT
#define I2C_S_BUSY_MASK              I2C_S1_BUSY_MASK
#define I2C_S_BUSY_SHIFT             I2C_S1_BUSY_SHIFT
#define I2C_S_IAAS_MASK              I2C_S1_IAAS_MASK
#define I2C_S_IAAS_SHIFT             I2C_S1_IAAS_SHIFT
#define I2C_S_TCF_MASK               I2C_S1_TCF_MASK
#define I2C_S_TCF_SHIFT              I2C_S1_TCF_SHIFT
#define INT_PMC                      INT_LVD_LVW
#define INT_ADC                      INT_ADC0
#define INT_WDOG                     INT_WDOG_EWM
#define INT_Watchdog                 INT_WDOG_EWM

/*!
 * @}
 */ /* end of group Backward_Compatibility_Symbols */


#else /* #if !defined(MCU_MKE06Z4) */
  /* There is already included the same memory map. Check if it is compatible (has the same major version) */
  #if (MCU_MEM_MAP_VERSION != 0x0100u)
    #if (!defined(MCU_MEM_MAP_SUPPRESS_VERSION_WARNING))
      #warning There are included two not compatible versions of memory maps. Please check possible differences.
    #endif /* (!defined(MCU_MEM_MAP_SUPPRESS_VERSION_WARNING)) */
  #endif /* (MCU_MEM_MAP_VERSION != 0x0100u) */
#endif  /* #if !defined(MCU_MKE06Z4) */

/* MKE06Z4.h, eof. */

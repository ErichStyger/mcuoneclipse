/*
** ###################################################################
**     Processors:          MKV58F1M0VLL24
**                          MKV58F1M0VLQ24
**                          MKV58F1M0VMD24
**                          MKV58F512VLL24
**                          MKV58F512VLQ24
**                          MKV58F512VMD24
**
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    KV5XP144M240RM Rev. 3, 02/2016
**     Version:             rev. 0.3, 2016-02-29
**     Build:               b160318
**
**     Abstract:
**         CMSIS Peripheral Access Layer for MKV58F24
**
**     Copyright (c) 1997 - 2016 Freescale Semiconductor, Inc.
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 0.1 (2015-02-24)
**         Initial version.
**     - rev. 0.2 (2015-10-21)
**         UART0 - removed LON functionality.
**         FMC - corrected base address.
**     - rev. 0.3 (2016-02-29)
**         PORT - removed registers GICLR, GICHR.
**
** ###################################################################
*/

/*!
 * @file MKV58F24.h
 * @version 0.3
 * @date 2016-02-29
 * @brief CMSIS Peripheral Access Layer for MKV58F24
 *
 * CMSIS Peripheral Access Layer for MKV58F24
 */

#ifndef _MKV58F24_H_
#define _MKV58F24_H_                             /**< Symbol preventing repeated inclusion */

/** Memory map major version (memory maps with equal major version number are
 * compatible) */
#define MCU_MEM_MAP_VERSION 0x0000U
/** Memory map minor version */
#define MCU_MEM_MAP_VERSION_MINOR 0x0003U

/**
 * @brief Macro to calculate address of an aliased word in the peripheral
 *        bitband area for a peripheral register and bit (bit band region 0x40000000 to
 *        0x400FFFFF).
 * @param Reg Register to access.
 * @param Bit Bit number to access.
 * @return  Address of the aliased word in the peripheral bitband area.
 */
#define BITBAND_REGADDR(Reg,Bit) (0x42000000u + (32u*((uint32_t)&(Reg) - (uint32_t)0x40000000u)) + (4u*((uint32_t)(Bit))))
/**
 * @brief Macro to access a single bit of a peripheral register (bit band region
 *        0x40000000 to 0x400FFFFF) using the bit-band alias region access. Can
 *        be used for peripherals with 32bit access allowed.
 * @param Reg Register to access.
 * @param Bit Bit number to access.
 * @return Value of the targeted bit in the bit band region.
 */
#define BITBAND_REG32(Reg,Bit) (*((uint32_t volatile*)(BITBAND_REGADDR((Reg),(Bit)))))
#define BITBAND_REG(Reg,Bit) (BITBAND_REG32((Reg),(Bit)))
/**
 * @brief Macro to access a single bit of a peripheral register (bit band region
 *        0x40000000 to 0x400FFFFF) using the bit-band alias region access. Can
 *        be used for peripherals with 16bit access allowed.
 * @param Reg Register to access.
 * @param Bit Bit number to access.
 * @return Value of the targeted bit in the bit band region.
 */
#define BITBAND_REG16(Reg,Bit) (*((uint16_t volatile*)(BITBAND_REGADDR((Reg),(Bit)))))
/**
 * @brief Macro to access a single bit of a peripheral register (bit band region
 *        0x40000000 to 0x400FFFFF) using the bit-band alias region access. Can
 *        be used for peripherals with 8bit access allowed.
 * @param Reg Register to access.
 * @param Bit Bit number to access.
 * @return Value of the targeted bit in the bit band region.
 */
#define BITBAND_REG8(Reg,Bit) (*((uint8_t volatile*)(BITBAND_REGADDR((Reg),(Bit)))))

/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
#define NUMBER_OF_INT_VECTORS 137                /**< Number of interrupts in the Vector table */

typedef enum IRQn {
  /* Auxiliary constants */
  NotAvail_IRQn                = -128,             /**< Not available device specific interrupt */

  /* Core interrupts */
  NonMaskableInt_IRQn          = -14,              /**< Non Maskable Interrupt */
  HardFault_IRQn               = -13,              /**< Cortex-M7 SV Hard Fault Interrupt */
  MemoryManagement_IRQn        = -12,              /**< Cortex-M7 Memory Management Interrupt */
  BusFault_IRQn                = -11,              /**< Cortex-M7 Bus Fault Interrupt */
  UsageFault_IRQn              = -10,              /**< Cortex-M7 Usage Fault Interrupt */
  SVCall_IRQn                  = -5,               /**< Cortex-M7 SV Call Interrupt */
  DebugMonitor_IRQn            = -4,               /**< Cortex-M7 Debug Monitor Interrupt */
  PendSV_IRQn                  = -2,               /**< Cortex-M7 Pend SV Interrupt */
  SysTick_IRQn                 = -1,               /**< Cortex-M7 System Tick Interrupt */

  /* Device specific interrupts */
  DMA0_DMA16_IRQn              = 0,                /**< DMA channel 0/16 transfer complete */
  DMA1_DMA17_IRQn              = 1,                /**< DMA channel 1/17 transfer complete */
  DMA2_DMA18_IRQn              = 2,                /**< DMA channel 2/18 transfer complete */
  DMA3_DMA19_IRQn              = 3,                /**< DMA channel 3/19 transfer complete */
  DMA4_DMA20_IRQn              = 4,                /**< DMA channel 4/20 transfer complete */
  DMA5_DMA21_IRQn              = 5,                /**< DMA channel 5/21 transfer complete */
  DMA6_DMA22_IRQn              = 6,                /**< DMA channel 6/22 transfer complete */
  DMA7_DMA23_IRQn              = 7,                /**< DMA channel 7/23 transfer complete */
  DMA8_DMA24_IRQn              = 8,                /**< DMA channel 8/24 transfer complete */
  DMA9_DMA25_IRQn              = 9,                /**< DMA channel 9/25 transfer complete */
  DMA10_DMA26_IRQn             = 10,               /**< DMA channel 10/26 transfer complete */
  DMA11_DMA27_IRQn             = 11,               /**< DMA channel 11/27 transfer complete */
  DMA12_DMA28_IRQn             = 12,               /**< DMA channel 12/28 transfer complete */
  DMA13_DMA29_IRQn             = 13,               /**< DMA channel 13/29 transfer complete */
  DMA14_DMA30_IRQn             = 14,               /**< DMA channel 14/30 transfer complete */
  DMA15_DMA31_IRQn             = 15,               /**< DMA channel 15/31 transfer complete */
  DMA_Error_IRQn               = 16,               /**< DMA error interrupt channels 0-31 */
  MCM_IRQn                     = 17,               /**< MCM normal interrupt */
  FTFE_IRQn                    = 18,               /**< FTFL command complete */
  Read_Collision_IRQn          = 19,               /**< FTFL read collision */
  PMC_IRQn                     = 20,               /**< PMC controller low-voltage detect, low-voltage warning */
  LLWU_IRQn                    = 21,               /**< Low leakage wakeup */
  WDOG_EWM_IRQn                = 22,               /**< Single interrupt vector for  WDOG and EWM */
  TRNG0_IRQn                   = 23,               /**< True randon number generator */
  I2C0_IRQn                    = 24,               /**< Inter-integrated circuit 0 */
  I2C1_IRQn                    = 25,               /**< Inter-integrated circuit 1 */
  SPI0_IRQn                    = 26,               /**< Serial peripheral Interface 0 */
  SPI1_IRQn                    = 27,               /**< Serial peripheral Interface 1 */
  UART5_RX_TX_IRQn             = 28,               /**< UART5 receive/transmit interrupt */
  UART5_ERR_IRQn               = 29,               /**< UART5 error interrupt */
  Reserved46_IRQn              = 30,               /**< Reserved interrupt */
  UART0_RX_TX_IRQn             = 31,               /**< UART0 receive/transmit interrupt */
  UART0_ERR_IRQn               = 32,               /**< UART0 error interrupt */
  UART1_RX_TX_IRQn             = 33,               /**< UART1 receive/transmit interrupt */
  UART1_ERR_IRQn               = 34,               /**< UART1 error interrupt */
  UART2_RX_TX_IRQn             = 35,               /**< UART2 receive/transmit interrupt */
  UART2_ERR_IRQn               = 36,               /**< UART2 error interrupt */
  ADC0_IRQn                    = 37,               /**< Analog-to-digital converter 0 */
  HSADC_ERR_IRQn               = 38,               /**< High speed analog-to-digital converter zero cross */
  HSADC0_CCA_IRQn              = 39,               /**< High speed analog-to-digital converter 0 submodule A scan complete */
  CMP0_IRQn                    = 40,               /**< Comparator 0 */
  CMP1_IRQn                    = 41,               /**< Comparator 1 */
  FTM0_IRQn                    = 42,               /**< FlexTimer module 0 fault, overflow and channels interrupt */
  FTM1_IRQn                    = 43,               /**< FlexTimer module 1 fault, overflow and channels interrupt */
  UART3_RX_TX_IRQn             = 44,               /**< UART3 receive/transmit interrupt */
  UART3_ERR_IRQn               = 45,               /**< UART3 error interrupt */
  UART4_RX_TX_IRQn             = 46,               /**< UART4 receive/transmit interrupt */
  UART4_ERR_IRQn               = 47,               /**< UART4 error interrupt */
  PIT0_IRQn                    = 48,               /**< Periodic interrupt timer channel 0 */
  PIT1_IRQn                    = 49,               /**< Periodic interrupt timer channel 1 */
  PIT2_IRQn                    = 50,               /**< Periodic interrupt timer channel 2 */
  PIT3_IRQn                    = 51,               /**< Periodic interrupt timer channel 3 */
  PDB0_IRQn                    = 52,               /**< Programmable delay block 0 */
  FTM2_IRQn                    = 53,               /**< FlexTimer module 2 fault, overflow and channels interrupt */
  XBARA_IRQn                   = 54,               /**< Inter-peripheral crossbar switch A */
  PDB1_IRQn                    = 55,               /**< Programmable delay block 1 */
  DAC0_IRQn                    = 56,               /**< Digital-to-analog converter 0 */
  MCG_IRQn                     = 57,               /**< Multipurpose clock generator */
  LPTMR0_IRQn                  = 58,               /**< Low power timer interrupt */
  PORTA_IRQn                   = 59,               /**< Port A interrupt */
  PORTB_IRQn                   = 60,               /**< Port B interrupt */
  PORTC_IRQn                   = 61,               /**< Port C interrupt */
  PORTD_IRQn                   = 62,               /**< Port D interrupt */
  PORTE_IRQn                   = 63,               /**< Port E interrupt */
  SWI_IRQn                     = 64,               /**< Software interrupt */
  SPI2_IRQn                    = 65,               /**< Serial peripheral Interface 2 */
  ENC_COMPARE_IRQn             = 66,               /**< ENC Compare */
  ENC_HOME_IRQn                = 67,               /**< ENC Home */
  ENC_WDOG_SAB_IRQn            = 68,               /**< ENC Wdog/SAB */
  ENC_INDEX_IRQn               = 69,               /**< ENC Index/Roll over/Roll Under */
  CMP2_IRQn                    = 70,               /**< Comparator 2 */
  FTM3_IRQn                    = 71,               /**< FlexTimer module 3 fault, overflow and channels */
  Reserved88_IRQn              = 72,               /**< Reserved interrupt */
  HSADC0_CCB_IRQn              = 73,               /**< High speed analog-to-digital converter 0 submodule B scan complete */
  HSADC1_CCA_IRQn              = 74,               /**< High speed analog-to-digital converter 1 submodule A scan complete */
  CAN0_ORed_Message_buffer_IRQn = 75,              /**< Flex controller area network 0 message buffer */
  CAN0_Bus_Off_IRQn            = 76,               /**< Flex controller area network 0 bus off */
  CAN0_Error_IRQn              = 77,               /**< Flex controller area network 0 error */
  CAN0_Tx_Warning_IRQn         = 78,               /**< Flex controller area network 0 transmit */
  CAN0_Rx_Warning_IRQn         = 79,               /**< Flex controller area network 0 receive */
  CAN0_Wake_Up_IRQn            = 80,               /**< Flex controller area network 0 wake up */
  PWM0_CMP0_IRQn               = 81,               /**< Pulse width modulator 0 channel 0 compare */
  PWM0_RELOAD0_IRQn            = 82,               /**< Pulse width modulator 0 channel 0 reload */
  PWM0_CMP1_IRQn               = 83,               /**< Pulse width modulator 0 channel 1 compare */
  PWM0_RELOAD1_IRQn            = 84,               /**< Pulse width modulator 0 channel 1 reload */
  PWM0_CMP2_IRQn               = 85,               /**< Pulse width modulator 0 channel 2 compare */
  PWM0_RELOAD2_IRQn            = 86,               /**< Pulse width modulator 0 channel 2 reload */
  PWM0_CMP3_IRQn               = 87,               /**< Pulse width modulator 0 channel 3 compare */
  PWM0_RELOAD3_IRQn            = 88,               /**< Pulse width modulator 0 channel 3 reload */
  PWM0_CAP_IRQn                = 89,               /**< Pulse width modulator 0 capture */
  PWM0_RERR_IRQn               = 90,               /**< Pulse width modulator 0 reload error */
  PWM0_FAULT_IRQn              = 91,               /**< Pulse width modulator 0 fault */
  CMP3_IRQn                    = 92,               /**< Comparator 3 */
  HSADC1_CCB_IRQn              = 93,               /**< High speed analog-to-digital converter 1 submodule B scan complete */
  CAN1_ORed_Message_buffer_IRQn = 94,              /**< Flex controller area network 1 message buffer */
  CAN1_Bus_Off_IRQn            = 95,               /**< Flex controller area network 1 bus off */
  CAN1_Error_IRQn              = 96,               /**< Flex controller area network 1 error */
  CAN1_Tx_Warning_IRQn         = 97,               /**< Flex controller area network 1 transmit */
  CAN1_Rx_Warning_IRQn         = 98,               /**< Flex controller area network 1 receive */
  CAN1_Wake_Up_IRQn            = 99,               /**< Flex controller area network 1 wake up */
  ENET_1588_Timer_IRQn         = 100,              /**< Ethernet MAC IEEE 1588 timer */
  ENET_Transmit_IRQn           = 101,              /**< Ethernet MAC transmit */
  ENET_Receive_IRQn            = 102,              /**< Ethernet MAC receive */
  ENET_Error_IRQn              = 103,              /**< Ethernet MAC error and miscelaneous */
  PWM1_CMP0_IRQn               = 104,              /**< Pulse width modulator 1 channel 0 compare */
  PWM1_RELOAD0_IRQn            = 105,              /**< Pulse width modulator 1 channel 0 reload */
  PWM1_CMP1_IRQn               = 106,              /**< Pulse width modulator 1 channel 1 compare */
  PWM1_RELOAD1_IRQn            = 107,              /**< Pulse width modulator 1 channel 1 reload */
  PWM1_CMP2_IRQn               = 108,              /**< Pulse width modulator 1 channel 2 compare */
  PWM1_RELOAD2_IRQn            = 109,              /**< Pulse width modulator 1 channel 2 reload */
  PWM1_CMP3_IRQn               = 110,              /**< Pulse width modulator 1 channel 3 compare */
  PWM1_RELOAD3_IRQn            = 111,              /**< Pulse width modulator 1 channel 3 reload */
  PWM1_CAP_IRQn                = 112,              /**< Pulse width modulator 1 capture */
  PWM1_RERR_IRQn               = 113,              /**< Pulse width modulator 1 reload error */
  PWM1_FAULT_IRQn              = 114,              /**< Pulse width modulator 1 fault */
  CAN2_ORed_Message_buffer_IRQn = 115,             /**< Flex controller area network 2 message buffer */
  CAN2_Bus_Off_IRQn            = 116,              /**< Flex controller area network 2 bus off */
  CAN2_Error_IRQn              = 117,              /**< Flex controller area network 2 error */
  CAN2_Tx_Warning_IRQn         = 118,              /**< Flex controller area network 2 transmit */
  CAN2_Rx_Warning_IRQn         = 119,              /**< Flex controller area network 2 receive */
  CAN2_Wake_Up_IRQn            = 120               /**< Flex controller area network 2 wake up */
} IRQn_Type;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */


/* ----------------------------------------------------------------------------
   -- Cortex M7 Core Configuration
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Cortex_Core_Configuration Cortex M7 Core Configuration
 * @{
 */

#define __MPU_PRESENT                  0         /**< Defines if an MPU is present or not */
#define __ICACHE_PRESENT               1         /**< Defines if an ICACHE is present or not */
#define __DCACHE_PRESENT               1         /**< Defines if an DCACHE is present or not */
#define __DTCM_PRESENT                 1         /**< Defines if an DTCM is present or not */
#define __NVIC_PRIO_BITS               4         /**< Number of priority bits implemented in the NVIC */
#define __Vendor_SysTickConfig         0         /**< Vendor specific implementation of SysTickConfig is defined */
#define __FPU_PRESENT                  1         /**< Defines if an FPU is present or not */

#include "core_cm7.h"                  /* Core Peripheral Access Layer */
#include "system_MKV58F24.h"           /* Device specific configuration file */

/*!
 * @}
 */ /* end of group Cortex_Core_Configuration */


/* ----------------------------------------------------------------------------
   -- Mapping Information
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Mapping_Information Mapping Information
 * @{
 */

/** Mapping Information */
/*!
 * @addtogroup edma_request
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Structure for the DMA hardware request
 *
 * Defines the structure for the DMA hardware request collections. The user can configure the
 * hardware request into DMAMUX to trigger the DMA transfer accordingly. The index
 * of the hardware request varies according  to the to SoC.
 */
typedef enum _dma_request_source
{
    kDmaRequestMux0Disable          = 0|0x100U,    /**< DMAMUX TriggerDisabled. */
    kDmaRequestMux0Reserved1        = 1|0x100U,    /**< Reserved1 */
    kDmaRequestMux0UART0Rx          = 2|0x100U,    /**< UART0 Receive. */
    kDmaRequestMux0UART0Tx          = 3|0x100U,    /**< UART0 Transmit. */
    kDmaRequestMux0UART1Rx          = 4|0x100U,    /**< UART1 Receive. */
    kDmaRequestMux0UART1Tx          = 5|0x100U,    /**< UART1 Transmit. */
    kDmaRequestMux0PWM0WR0          = 6|0x100U,    /**< PWM0 Write Request 0. */
    kDmaRequestMux0PWM0WR1          = 7|0x100U,    /**< PWM0 Write Request 1. */
    kDmaRequestMux0PWM0WR2          = 8|0x100U,    /**< PWM0 Write Request 2. */
    kDmaRequestMux0PWM0WR3          = 9|0x100U,    /**< PWM0 Write Request 3. */
    kDmaRequestMux0PWM0CP0          = 10|0x100U,   /**< PWM0 Capture 0. */
    kDmaRequestMux0PWM0CP1          = 11|0x100U,   /**< PWM0 Capture 1. */
    kDmaRequestMux0PWM0CP2          = 12|0x100U,   /**< PWM0 Capture 2. */
    kDmaRequestMux0PWM0CP3          = 13|0x100U,   /**< PWM0 Capture 3. */
    kDmaRequestMux0CAN0             = 14|0x100U,   /**< CAN0. */
    kDmaRequestMux0CAN1             = 15|0x100U,   /**< CAN1. */
    kDmaRequestMux0SPI0Rx           = 16|0x100U,   /**< SPI0 Receive. */
    kDmaRequestMux0SPI0Tx           = 17|0x100U,   /**< SPI0 Transmit. */
    kDmaRequestMux0XBARAOUT0        = 18|0x100U,   /**< XBARA Output 0. */
    kDmaRequestMux0XBARAOUT1        = 19|0x100U,   /**< XBARA Output 1. */
    kDmaRequestMux0XBARAOUT2        = 20|0x100U,   /**< XBARA Output 2. */
    kDmaRequestMux0XBARAOUT3        = 21|0x100U,   /**< XBARA Output 3. */
    kDmaRequestMux0I2C0             = 22|0x100U,   /**< I2C0. */
    kDmaRequestMux0Reserved23       = 23|0x100U,   /**< Reserved23 */
    kDmaRequestMux0FTM0Channel0     = 24|0x100U,   /**< FTM0 C0V. */
    kDmaRequestMux0FTM0Channel1     = 25|0x100U,   /**< FTM0 C1V. */
    kDmaRequestMux0FTM0Channel2     = 26|0x100U,   /**< FTM0 C2V. */
    kDmaRequestMux0FTM0Channel3     = 27|0x100U,   /**< FTM0 C3V. */
    kDmaRequestMux0FTM0Channel4     = 28|0x100U,   /**< FTM0 C4V. */
    kDmaRequestMux0FTM0Channel5     = 29|0x100U,   /**< FTM0 C5V. */
    kDmaRequestMux0FTM0Channel6     = 30|0x100U,   /**< FTM0 C6V. */
    kDmaRequestMux0FTM0Channel7     = 31|0x100U,   /**< FTM0 C7V. */
    kDmaRequestMux0FTM1Channel0     = 32|0x100U,   /**< FTM1 C0V. */
    kDmaRequestMux0FTM1Channel1     = 33|0x100U,   /**< FTM1 C1V. */
    kDmaRequestMux0CMP3             = 34|0x100U,   /**< CMP3. */
    kDmaRequestMux0Reserved35       = 35|0x100U,   /**< Reserved35 */
    kDmaRequestMux0FTM3Channel0     = 36|0x100U,   /**< FTM3 C0V. */
    kDmaRequestMux0FTM3Channel1     = 37|0x100U,   /**< FTM3 C1V. */
    kDmaRequestMux0FTM3Channel2     = 38|0x100U,   /**< FTM3 C2V. */
    kDmaRequestMux0FTM3Channel3     = 39|0x100U,   /**< FTM3 C3V. */
    kDmaRequestMux0HSADC0A          = 40|0x100U,   /**< HSADC0. */
    kDmaRequestMux0HSADC0B          = 41|0x100U,   /**< HSADC0. */
    kDmaRequestMux0CMP0             = 42|0x100U,   /**< CMP0. */
    kDmaRequestMux0CMP1             = 43|0x100U,   /**< CMP1. */
    kDmaRequestMux0CMP2             = 44|0x100U,   /**< CMP2. */
    kDmaRequestMux0DAC0             = 45|0x100U,   /**< DAC0. */
    kDmaRequestMux0Reserved46       = 46|0x100U,   /**< Reserved46 */
    kDmaRequestMux0PDB1             = 47|0x100U,   /**< PDB1. */
    kDmaRequestMux0PDB0             = 48|0x100U,   /**< PDB0. */
    kDmaRequestMux0PortA            = 49|0x100U,   /**< PTA. */
    kDmaRequestMux0PortB            = 50|0x100U,   /**< PTB. */
    kDmaRequestMux0PortC            = 51|0x100U,   /**< PTC. */
    kDmaRequestMux0PortD            = 52|0x100U,   /**< PTD. */
    kDmaRequestMux0PortE            = 53|0x100U,   /**< PTE. */
    kDmaRequestMux0FTM3Channel4     = 54|0x100U,   /**< FTM3 C4V. */
    kDmaRequestMux0FTM3Channel5     = 55|0x100U,   /**< FTM3 C5V. */
    kDmaRequestMux0FTM3Channel6     = 56|0x100U,   /**< FTM3 C6V. */
    kDmaRequestMux0FTM3Channel7     = 57|0x100U,   /**< FTM3 C7V. */
    kDmaRequestMux0Reserved58       = 58|0x100U,   /**< Reserved58 */
    kDmaRequestMux0Reserved59       = 59|0x100U,   /**< Reserved59 */
    kDmaRequestMux0AlwaysOn60       = 60|0x100U,   /**< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn61       = 61|0x100U,   /**< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn62       = 62|0x100U,   /**< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn63       = 63|0x100U,   /**< DMAMUX Always Enabled slot. */
    kDmaRequestMux0Group1Disable    = 0|0x200U,    /**< DMAMUX TriggerDisabled. */
    kDmaRequestMux0Group1Reserved1  = 1|0x200U,    /**< Reserved1 */
    kDmaRequestMux0Group1UART2Rx    = 2|0x200U,    /**< UART2 Receive. */
    kDmaRequestMux0Group1UART2Tx    = 3|0x200U,    /**< UART2 Transmit. */
    kDmaRequestMux0Group1UART3Rx    = 4|0x200U,    /**< UART3 Receive. */
    kDmaRequestMux0Group1UART3Tx    = 5|0x200U,    /**< UART3 Transmit. */
    kDmaRequestMux0Group1PWM1WR0    = 6|0x200U,    /**< PWM1 Write Request 0. */
    kDmaRequestMux0Group1PWM1WR1    = 7|0x200U,    /**< PWM1 Write Request 1. */
    kDmaRequestMux0Group1PWM1WR2    = 8|0x200U,    /**< PWM1 Write Request 2. */
    kDmaRequestMux0Group1PWM1WR3    = 9|0x200U,    /**< PWM1 Write Request 3. */
    kDmaRequestMux0Group1PWM1CP0    = 10|0x200U,   /**< PWM1 Capture 0. */
    kDmaRequestMux0Group1PWM1CP1    = 11|0x200U,   /**< PWM1 Capture 1. */
    kDmaRequestMux0Group1PWM1CP2    = 12|0x200U,   /**< PWM1 Capture 2. */
    kDmaRequestMux0Group1PWM1CP3    = 13|0x200U,   /**< PWM1 Capture 3. */
    kDmaRequestMux0Group1CAN2       = 14|0x200U,   /**< CAN2. */
    kDmaRequestMux0Group1Reserved15 = 15|0x200U,   /**< Reserved15 */
    kDmaRequestMux0Group1SPI1Rx     = 16|0x200U,   /**< SPI1 Receive. */
    kDmaRequestMux0Group1SPI1Tx     = 17|0x200U,   /**< SPI1 Transmit. */
    kDmaRequestMux0Group1Reserved18 = 18|0x200U,   /**< Reserved18 */
    kDmaRequestMux0Group1Reserved19 = 19|0x200U,   /**< Reserved19 */
    kDmaRequestMux0Group1Reserved20 = 20|0x200U,   /**< Reserved20 */
    kDmaRequestMux0Group1Reserved21 = 21|0x200U,   /**< Reserved21 */
    kDmaRequestMux0Group1I2C1       = 22|0x200U,   /**< I2C1. */
    kDmaRequestMux0Group1Reserved23 = 23|0x200U,   /**< Reserved23 */
    kDmaRequestMux0Group1Reserved24 = 24|0x200U,   /**< Reserved24 */
    kDmaRequestMux0Group1Reserved25 = 25|0x200U,   /**< Reserved25 */
    kDmaRequestMux0Group1Reserved26 = 26|0x200U,   /**< Reserved26 */
    kDmaRequestMux0Group1Reserved27 = 27|0x200U,   /**< Reserved27 */
    kDmaRequestMux0Group1Reserved28 = 28|0x200U,   /**< Reserved28 */
    kDmaRequestMux0Group1Reserved29 = 29|0x200U,   /**< Reserved29 */
    kDmaRequestMux0Group1Reserved30 = 30|0x200U,   /**< Reserved30 */
    kDmaRequestMux0Group1Reserved31 = 31|0x200U,   /**< Reserved31 */
    kDmaRequestMux0Group1FTM2Channel0 = 32|0x200U, /**< FTM2 C0V. */
    kDmaRequestMux0Group1FTM2Channel1 = 33|0x200U, /**< FTM2 C1V. */
    kDmaRequestMux0Group1SPI2Rx     = 34|0x200U,   /**< SPI2 Receive. */
    kDmaRequestMux0Group1SPI2Tx     = 35|0x200U,   /**< SPI2 Transmit. */
    kDmaRequestMux0Group1IEEE1588Timer0 = 36|0x200U, /**< ENET IEEE 1588 timer 0. */
    kDmaRequestMux0Group1IEEE1588Timer1 = 37|0x200U, /**< ENET IEEE 1588 timer 1. */
    kDmaRequestMux0Group1IEEE1588Timer2 = 38|0x200U, /**< ENET IEEE 1588 timer 2. */
    kDmaRequestMux0Group1IEEE1588Timer3 = 39|0x200U, /**< ENET IEEE 1588 timer 3. */
    kDmaRequestMux0Group1HSADC1A    = 40|0x200U,   /**< HSADC1. */
    kDmaRequestMux0Group1HSADC1B    = 41|0x200U,   /**< HSADC1. */
    kDmaRequestMux0Group1Reserved42 = 42|0x200U,   /**< Reserved42 */
    kDmaRequestMux0Group1Reserved43 = 43|0x200U,   /**< Reserved43 */
    kDmaRequestMux0Group1Reserved44 = 44|0x200U,   /**< Reserved44 */
    kDmaRequestMux0Group1ADC0       = 45|0x200U,   /**< ADC0. */
    kDmaRequestMux0Group1Reserved46 = 46|0x200U,   /**< Reserved46 */
    kDmaRequestMux0Group1Reserved47 = 47|0x200U,   /**< Reserved47 */
    kDmaRequestMux0Group1Reserved48 = 48|0x200U,   /**< Reserved48 */
    kDmaRequestMux0Group1Reserved49 = 49|0x200U,   /**< Reserved49 */
    kDmaRequestMux0Group1Reserved50 = 50|0x200U,   /**< Reserved50 */
    kDmaRequestMux0Group1Reserved51 = 51|0x200U,   /**< Reserved51 */
    kDmaRequestMux0Group1Reserved52 = 52|0x200U,   /**< Reserved52 */
    kDmaRequestMux0Group1Reserved53 = 53|0x200U,   /**< Reserved53 */
    kDmaRequestMux0Group1UART4Rx    = 54|0x200U,   /**< UART4 Receive. */
    kDmaRequestMux0Group1UART4Tx    = 55|0x200U,   /**< UART4 Transmit. */
    kDmaRequestMux0Group1UART5Rx    = 56|0x200U,   /**< UART5 Receive. */
    kDmaRequestMux0Group1UART5Tx    = 57|0x200U,   /**< UART5 Transmit. */
    kDmaRequestMux0Group1Reserved58 = 58|0x200U,   /**< Reserved58 */
    kDmaRequestMux0Group1Reserved59 = 59|0x200U,   /**< Reserved59 */
    kDmaRequestMux0Group1AlwaysOn60 = 60|0x200U,   /**< DMAMUX Always Enabled slot. */
    kDmaRequestMux0Group1AlwaysOn61 = 61|0x200U,   /**< DMAMUX Always Enabled slot. */
    kDmaRequestMux0Group1AlwaysOn62 = 62|0x200U,   /**< DMAMUX Always Enabled slot. */
    kDmaRequestMux0Group1AlwaysOn63 = 63|0x200U,   /**< DMAMUX Always Enabled slot. */
} dma_request_source_t;

/* @} */

typedef enum _xbar_input_signal
{
    kXBARA_InputVss                 = 0|0x100U,    /**< Logic zero output assigned to XBARA_IN0 input. */
    kXBARA_InputVdd                 = 1|0x100U,    /**< Logic one output assigned to XBARA_IN1 input. */
    kXBARA_InputXbarIn2             = 2|0x100U,    /**< XBAR0_IN2 input pin output assigned to XBARA_IN2 input. */
    kXBARA_InputXbarIn3             = 3|0x100U,    /**< XBAR0_IN3 input pin output assigned to XBARA_IN3 input. */
    kXBARA_InputXbarIn4             = 4|0x100U,    /**< XBAR0_IN4 input pin output assigned to XBARA_IN4 input. */
    kXBARA_InputXbarIn5             = 5|0x100U,    /**< XBAR0_IN5 input pin output assigned to XBARA_IN5 input. */
    kXBARA_InputXbarIn6             = 6|0x100U,    /**< XBAR0_IN6 input pin output assigned to XBARA_IN6 input. */
    kXBARA_InputXbarIn7             = 7|0x100U,    /**< XBAR0_IN7 input pin output assigned to XBARA_IN7 input. */
    kXBARA_InputXbarIn8             = 8|0x100U,    /**< XBAR0_IN8 input pin output assigned to XBARA_IN8 input. */
    kXBARA_InputXbarIn9             = 9|0x100U,    /**< XBAR0_IN9 input pin output assigned to XBARA_IN9 input. */
    kXBARA_InputXbarIn10            = 10|0x100U,   /**< XBAR0_IN10 input pin output assigned to XBARA_IN10 input. */
    kXBARA_InputXbarIn11            = 11|0x100U,   /**< XBAR0_IN11 input pin output assigned to XBARA_IN11 input. */
    kXBARA_InputCmp0Output          = 12|0x100U,   /**< CMP0 Output output assigned to XBARA_IN12 input. */
    kXBARA_InputCmp1Output          = 13|0x100U,   /**< CMP1 Output output assigned to XBARA_IN13 input. */
    kXBARA_InputCmp2Output          = 14|0x100U,   /**< CMP2 Output output assigned to XBARA_IN14 input. */
    kXBARA_InputCmp3Output          = 15|0x100U,   /**< CMP3 Output output assigned to XBARA_IN15 input. */
    kXBARA_InputFtm0Match           = 16|0x100U,   /**< FTM0 all channels output compare ORed together output assigned to XBARA_IN16 input. */
    kXBARA_InputFtm0Extrig          = 17|0x100U,   /**< FTM0 all channels counter init ORed together output assigned to XBARA_IN17 input. */
    kXBARA_InputFtm3Match           = 18|0x100U,   /**< FTM3 all channels output compare ORed together output assigned to XBARA_IN18 input. */
    kXBARA_InputFtm3Extrig          = 19|0x100U,   /**< FTM3 all channels counter init ORed together output assigned to XBARA_IN19 input. */
    kXBARA_InputPwm0Ch0Trg0         = 20|0x100U,   /**< PWMA channel 0 trigger 0 output assigned to XBARA_IN20 input. */
    kXBARA_InputPwm0Ch0Trg1         = 21|0x100U,   /**< PWMA channel 0 trigger 1 output assigned to XBARA_IN21 input. */
    kXBARA_InputPwm0Ch1Trg0         = 22|0x100U,   /**< PWMA channel 1 trigger 0 output assigned to XBARA_IN22 input. */
    kXBARA_InputPwm0Ch1Trg1         = 23|0x100U,   /**< PWMA channel 1 trigger 1 output assigned to XBARA_IN23 input. */
    kXBARA_InputPwm0Ch2Trg0         = 24|0x100U,   /**< PWMA channel 2 trigger 0 output assigned to XBARA_IN24 input. */
    kXBARA_InputPwm0Ch2Trg1         = 25|0x100U,   /**< PWMA channel 2 trigger 1 output assigned to XBARA_IN25 input. */
    kXBARA_InputPwm0Ch3Trg0         = 26|0x100U,   /**< PWMA channel 3 trigger 0 output assigned to XBARA_IN26 input. */
    kXBARA_InputPwm0Ch3Trg1         = 27|0x100U,   /**< PWMA channel 3 trigger 1 output assigned to XBARA_IN27 input. */
    kXBARA_InputPdb0Ch1Output       = 28|0x100U,   /**< PDB0 channel 1 output trigger output assigned to XBARA_IN28 input. */
    kXBARA_InputPdb0Ch0Output       = 29|0x100U,   /**< PDB0 channel 0 output trigger output assigned to XBARA_IN29 input. */
    kXBARA_InputPdb1Ch1Output       = 30|0x100U,   /**< PDB1 channel 1 output trigger output assigned to XBARA_IN30 input. */
    kXBARA_InputPdb1Ch0Output       = 31|0x100U,   /**< PDB1 channel 0 output trigger output assigned to XBARA_IN31 input. */
    kXBARA_InputHsadc1Cca           = 32|0x100U,   /**< High Speed Analog-to-Digital Converter 1 conversion A complete output assigned to XBARA_IN32 input. */
    kXBARA_InputHsadc0Cca           = 33|0x100U,   /**< High Speed Analog-to-Digital Converter 0 conversion A complete output assigned to XBARA_IN33 input. */
    kXBARA_InputHsadc1Ccb           = 34|0x100U,   /**< High Speed Analog-to-Digital Converter 1 conversion B complete output assigned to XBARA_IN34 input. */
    kXBARA_InputHsadc0Ccb           = 35|0x100U,   /**< High Speed Analog-to-Digital Converter 0 conversion B complete output assigned to XBARA_IN35 input. */
    kXBARA_InputFtm1Match           = 36|0x100U,   /**< FTM1 all channels output compare ORed together output assigned to XBARA_IN36 input. */
    kXBARA_InputFtm1Extrig          = 37|0x100U,   /**< FTM1 all channels counter init ORed together output assigned to XBARA_IN37 input. */
    kXBARA_InputDmaCh0Done          = 38|0x100U,   /**< DMA channel 0 done output assigned to XBARA_IN38 input. */
    kXBARA_InputDmaCh1Done          = 39|0x100U,   /**< DMA channel 1 done output assigned to XBARA_IN39 input. */
    kXBARA_InputDmaCh6Done          = 40|0x100U,   /**< DMA channel 6 done output assigned to XBARA_IN40 input. */
    kXBARA_InputDmaCh7Done          = 41|0x100U,   /**< DMA channel 7 done output assigned to XBARA_IN41 input. */
    kXBARA_InputPitTrigger0         = 42|0x100U,   /**< PIT trigger 0 output assigned to XBARA_IN42 input. */
    kXBARA_InputPitTrigger1         = 43|0x100U,   /**< PIT trigger 1 output assigned to XBARA_IN43 input. */
    kXBARA_InputAdc0Coco            = 44|0x100U,   /**< Analog-to-Digital Converter 0 conversion complete output assigned to XBARA_IN44 input. */
    kXBARA_InputEncCmpPosMatch      = 45|0x100U,   /**< ENC compare trigger and position match output assigned to XBARA_IN45 input. */
    kXBARA_InputAndOrInvert0        = 46|0x100U,   /**< AOI output 0 output assigned to XBARA_IN46 input. */
    kXBARA_InputAndOrInvert1        = 47|0x100U,   /**< AOI output 1 output assigned to XBARA_IN47 input. */
    kXBARA_InputAndOrInvert2        = 48|0x100U,   /**< AOI output 2 output assigned to XBARA_IN48 input. */
    kXBARA_InputAndOrInvert3        = 49|0x100U,   /**< AOI output 3 output assigned to XBARA_IN49 input. */
    kXBARA_InputPitTrigger2         = 50|0x100U,   /**< PIT trigger 2 output assigned to XBARA_IN50 input. */
    kXBARA_InputPitTrigger3         = 51|0x100U,   /**< PIT trigger 3 output assigned to XBARA_IN51 input. */
    kXBARA_InputPwm1Ch0Trg0OrTrg1   = 52|0x100U,   /**< PWMB channel 0 trigger 0 or trigger 1 output assigned to XBARA_IN52 input. */
    kXBARA_InputPwm1Ch1Trg0OrTrg1   = 53|0x100U,   /**< PWMB channel 1 trigger 0 or trigger 1 output assigned to XBARA_IN53 input. */
    kXBARA_InputPwm1Ch2Trg0OrTrg1   = 54|0x100U,   /**< PWMB channel 2 trigger 0 or trigger 1 output assigned to XBARA_IN54 input. */
    kXBARA_InputPwm1Ch3Trg0OrTrg1   = 55|0x100U,   /**< PWMB channel 3 trigger 0 or trigger 1 output assigned to XBARA_IN55 input. */
    kXBARA_InputFtm2Match           = 56|0x100U,   /**< FTM2 all channels output compare ORed together output assigned to XBARA_IN56 input. */
    kXBARA_InputFtm2Extrig          = 57|0x100U,   /**< FTM2 all channels counter init ORed together output assigned to XBARA_IN57 input. */
    kXBARB_InputCmp0Output          = 0|0x200U,    /**< CMP0 Output output assigned to XBARB_IN0 input. */
    kXBARB_InputCmp1Output          = 1|0x200U,    /**< CMP1 Output output assigned to XBARB_IN1 input. */
    kXBARB_InputCmp2Output          = 2|0x200U,    /**< CMP2 Output output assigned to XBARB_IN2 input. */
    kXBARB_InputCmp3Output          = 3|0x200U,    /**< CMP3 Output output assigned to XBARB_IN3 input. */
    kXBARB_InputFtm0Match           = 4|0x200U,    /**< FTM0 all channels output compare ORed together output assigned to XBARB_IN4 input. */
    kXBARB_InputFtm0Extrig          = 5|0x200U,    /**< FTM0 all channels counter init ORed together output assigned to XBARB_IN5 input. */
    kXBARB_InputFtm3Match           = 6|0x200U,    /**< FTM3 all channels output compare ORed together output assigned to XBARB_IN6 input. */
    kXBARB_InputFtm3Extrig          = 7|0x200U,    /**< FTM3 all channels counter init ORed together output assigned to XBARB_IN7 input. */
    kXBARB_InputPwm0Ch0Trg0         = 8|0x200U,    /**< PWMA channel 0 trigger 0 output assigned to XBARB_IN8 input. */
    kXBARB_InputPwm0Ch1Trg0         = 9|0x200U,    /**< PWMA channel 1 trigger 0 output assigned to XBARB_IN9 input. */
    kXBARB_InputPwm0Ch2Trg0         = 10|0x200U,   /**< PWMA channel 2 trigger 0 output assigned to XBARB_IN10 input. */
    kXBARB_InputPwm0Ch3Trg0         = 11|0x200U,   /**< PWMA channel 3 trigger 0 output assigned to XBARB_IN11 input. */
    kXBARB_InputPdb0Ch0Output       = 12|0x200U,   /**< PDB0 channel 0 output trigger output assigned to XBARB_IN12 input. */
    kXBARB_InputHsadc0Cca           = 13|0x200U,   /**< High Speed Analog-to-Digital Converter 0 conversion A complete output assigned to XBARB_IN13 input. */
    kXBARB_InputXbarIn2             = 14|0x200U,   /**< XBAR0_IN2 input pin output assigned to XBARB_IN14 input. */
    kXBARB_InputXbarIn3             = 15|0x200U,   /**< XBAR0_IN3 input pin output assigned to XBARB_IN15 input. */
    kXBARB_InputFtm1Match           = 16|0x200U,   /**< FTM1 all channels output compare ORed together output assigned to XBARB_IN16 input. */
    kXBARB_InputFtm1Extrig          = 17|0x200U,   /**< FTM1 all channels counter init ORed together output assigned to XBARB_IN17 input. */
    kXBARB_InputDmaCh0Done          = 18|0x200U,   /**< DMA channel 0 done output assigned to XBARB_IN18 input. */
    kXBARB_InputDmaCh1Done          = 19|0x200U,   /**< DMA channel 1 done output assigned to XBARB_IN19 input. */
    kXBARB_InputXbarIn10            = 20|0x200U,   /**< XBAR0_IN10 input pin output assigned to XBARB_IN20 input. */
    kXBARB_InputXbarIn11            = 21|0x200U,   /**< XBAR0_IN11 input pin output assigned to XBARB_IN21 input. */
    kXBARB_InputDmaCh6Done          = 22|0x200U,   /**< DMA channel 6 done output assigned to XBARB_IN22 input. */
    kXBARB_InputDmaCh7Done          = 23|0x200U,   /**< DMA channel 7 done output assigned to XBARB_IN23 input. */
    kXBARB_InputPitTrigger0         = 24|0x200U,   /**< PIT trigger 0 output assigned to XBARB_IN24 input. */
    kXBARB_InputPitTrigger1         = 25|0x200U,   /**< PIT trigger 1 output assigned to XBARB_IN25 input. */
    kXBARB_InputPdb1Ch0Output       = 26|0x200U,   /**< PDB1 channel 0 output trigger output assigned to XBARB_IN26 input. */
    kXBARB_InputHsadc0Ccb           = 27|0x200U,   /**< High Speed Analog-to-Digital Converter 0 conversion B complete output assigned to XBARB_IN27 input. */
    kXBARB_InputPwm1Ch0Trg0OrTrg1   = 28|0x200U,   /**< PWMB channel 0 trigger 0 or trigger 1 output assigned to XBARB_IN28 input. */
    kXBARB_InputPwm1Ch1Trg0OrTrg1   = 29|0x200U,   /**< PWMB channel 1 trigger 0 or trigger 1 output assigned to XBARB_IN29 input. */
    kXBARB_InputPwm1Ch2Trg0OrTrg1   = 30|0x200U,   /**< PWMB channel 2 trigger 0 or trigger 1 output assigned to XBARB_IN30 input. */
    kXBARB_InputPwm1Ch3Trg0OrTrg1   = 31|0x200U,   /**< PWMB channel 3 trigger 0 or trigger 1 output assigned to XBARB_IN31 input. */
    kXBARB_InputFtm2Match           = 32|0x200U,   /**< FTM2 all channels output compare ORed together output assigned to XBARB_IN32 input. */
    kXBARB_InputFtm2Extrig          = 33|0x200U,   /**< FTM2 all channels counter init ORed together output assigned to XBARB_IN33 input. */
    kXBARB_InputPdb0Ch1Output       = 34|0x200U,   /**< PDB0 channel 1 output trigger output assigned to XBARB_IN34 input. */
    kXBARB_InputPdb1Ch1Output       = 35|0x200U,   /**< PDB1 channel 1 output trigger output assigned to XBARB_IN35 input. */
    kXBARB_InputHsadc1Cca           = 36|0x200U,   /**< High Speed Analog-to-Digital Converter 1 conversion A complete output assigned to XBARB_IN36 input. */
    kXBARB_InputHsadc1Ccb           = 37|0x200U,   /**< High Speed Analog-to-Digital Converter 1 conversion B complete output assigned to XBARB_IN37 input. */
    kXBARB_InputAdc0Coco            = 38|0x200U,   /**< Analog-to-Digital Converter 0 conversion complete output assigned to XBARB_IN38 input. */
} xbar_input_signal_t;

typedef enum _xbar_output_signal
{
    kXBARA_OutputDmamux18           = 0|0x100U,    /**< XBARA_OUT0 output assigned to DMAMUX slot 18 */
    kXBARA_OutputDmamux19           = 1|0x100U,    /**< XBARA_OUT1 output assigned to DMAMUX slot 19 */
    kXBARA_OutputDmamux20           = 2|0x100U,    /**< XBARA_OUT2 output assigned to DMAMUX slot 20 */
    kXBARA_OutputDmamux21           = 3|0x100U,    /**< XBARA_OUT3 output assigned to DMAMUX slot 21 */
    kXBARA_OutputXbOut4             = 4|0x100U,    /**< XBARA_OUT4 output assigned to XBAROUT4 output pin */
    kXBARA_OutputXbOut5             = 5|0x100U,    /**< XBARA_OUT5 output assigned to XBAROUT5 output pin */
    kXBARA_OutputXbOut6             = 6|0x100U,    /**< XBARA_OUT6 output assigned to XBAROUT6 output pin */
    kXBARA_OutputXbOut7             = 7|0x100U,    /**< XBARA_OUT7 output assigned to XBAROUT7 output pin */
    kXBARA_OutputXbOut8             = 8|0x100U,    /**< XBARA_OUT8 output assigned to XBAROUT8 output pin */
    kXBARA_OutputXbOut9             = 9|0x100U,    /**< XBARA_OUT9 output assigned to XBAROUT9 output pin */
    kXBARA_OutputXbOut10            = 10|0x100U,   /**< XBARA_OUT10 output assigned to XBAROUT10 output pin */
    kXBARA_OutputXbOut11            = 11|0x100U,   /**< XBARA_OUT11 output assigned to XBAROUT11 output pin */
    kXBARA_OutputHsadc0ATrig        = 12|0x100U,   /**< XBARA_OUT12 output assigned to HSADC0 converter A trigger */
    kXBARA_OutputHsadc0BTrig        = 13|0x100U,   /**< XBARA_OUT13 output assigned to HSADC0 converter B trigger */
    kXBARA_OutputRESERVED14         = 14|0x100U,   /**< XBARA_OUT14 output is reserved. */
    kXBARA_OutputDac12bSync         = 15|0x100U,   /**< XBARA_OUT15 output assigned to DAC synchronisation trigger */
    kXBARA_OutputCmp0               = 16|0x100U,   /**< XBARA_OUT16 output assigned to CMP0 window/sample */
    kXBARA_OutputCmp1               = 17|0x100U,   /**< XBARA_OUT17 output assigned to CMP1 window/sample */
    kXBARA_OutputCmp2               = 18|0x100U,   /**< XBARA_OUT18 output assigned to CMP2 window/sample */
    kXBARA_OutputCmp3               = 19|0x100U,   /**< XBARA_OUT19 output assigned to CMP3 window/sample */
    kXBARA_OutputPwmCh0ExtA         = 20|0x100U,   /**< XBARA_OUT20 output assigned to PWM0 and PWM1 channel 0 external control A */
    kXBARA_OutputPwmCh1ExtA         = 21|0x100U,   /**< XBARA_OUT21 output assigned to PWM0 and PWM1 channel 1 external control A */
    kXBARA_OutputPwmCh2ExtA         = 22|0x100U,   /**< XBARA_OUT22 output assigned to PWM0 and PWM1 channel 2 external control A */
    kXBARA_OutputPwmCh3ExtA         = 23|0x100U,   /**< XBARA_OUT23 output assigned to PWM0 and PWM1 channel 3 external control A */
    kXBARA_OutputPwm0Ch0ExtSync     = 24|0x100U,   /**< XBARA_OUT24 output assigned to PWM0 channel 0 external synchronization */
    kXBARA_OutputPwm0Ch1ExtSync     = 25|0x100U,   /**< XBARA_OUT25 output assigned to PWM0 channel 1 external synchronization */
    kXBARA_OutputPwm0Ch2ExtSync     = 26|0x100U,   /**< XBARA_OUT26 output assigned to PWM0 channel 2 external synchronization */
    kXBARA_OutputPwm0Ch3ExtSync     = 27|0x100U,   /**< XBARA_OUT27 output assigned to PWM0 channel 3 external synchronization */
    kXBARA_OutputPwmExtClk          = 28|0x100U,   /**< XBARA_OUT28 output assigned to PWM0 and PWM1 external clock */
    kXBARA_OutputPwm0Fault0         = 29|0x100U,   /**< XBARA_OUT29 output assigned to PWM0 and PWM1 fault 0 */
    kXBARA_OutputPwm0Fault1         = 30|0x100U,   /**< XBARA_OUT30 output assigned to PWM0 and PWM1 fault 1 */
    kXBARA_OutputPwm0Fault2         = 31|0x100U,   /**< XBARA_OUT31 output assigned to PWM0 and PWM1 fault 2 */
    kXBARA_OutputPwm0Fault3         = 32|0x100U,   /**< XBARA_OUT32 output assigned to PWM0 and PWM1 fault 3 */
    kXBARA_OutputPwm0Force          = 33|0x100U,   /**< XBARA_OUT33 output assigned to PWM0 external output force */
    kXBARA_OutputFtm0Trig2          = 34|0x100U,   /**< XBARA_OUT34 output assigned to FTM0 hardware trigger 2 */
    kXBARA_OutputFtm1Trig2          = 35|0x100U,   /**< XBARA_OUT35 output assigned to FTM1 hardware trigger 2 */
    kXBARA_OutputFtm2Trig2          = 36|0x100U,   /**< XBARA_OUT36 output assigned to FTM2 hardware trigger 2 */
    kXBARA_OutputFtm3Trig2          = 37|0x100U,   /**< XBARA_OUT37 output assigned to FTM3 hardware trigger 2 */
    kXBARA_OutputPdb0InCh12         = 38|0x100U,   /**< XBARA_OUT38 output assigned to PDB0 trigger option 12 */
    kXBARA_OutputAdc0Hdwt           = 39|0x100U,   /**< XBARA_OUT39 output assigned to ADC0 hardware trigger */
    kXBARA_OutputRESERVED40         = 40|0x100U,   /**< XBARA_OUT40 output is reserved. */
    kXBARA_OutputPdb1InCh12         = 41|0x100U,   /**< XBARA_OUT41 output assigned to PDB1 trigger option 12 */
    kXBARA_OutputHsadc1ATrig        = 42|0x100U,   /**< XBARA_OUT42 output assigned to HSADC1 converter A trigger and FTM1 channel 1 signal XOR input */
    kXBARA_OutputHsadc1BTrig        = 43|0x100U,   /**< XBARA_OUT43 output assigned to HSADC1 converter B trigger */
    kXBARA_OutputEncPhA             = 44|0x100U,   /**< XBARA_OUT44 output assigned to ENC quadrature waveform phase A */
    kXBARA_OutputEncPhB             = 45|0x100U,   /**< XBARA_OUT45 output assigned to ENC quadrature waveform phase B */
    kXBARA_OutputEncIndex           = 46|0x100U,   /**< XBARA_OUT46 output assigned to ENC refresh/reload */
    kXBARA_OutputEncHome            = 47|0x100U,   /**< XBARA_OUT47 output assigned to ENC home position */
    kXBARA_OutputEncCapTrigger      = 48|0x100U,   /**< XBARA_OUT48 output assigned to ENC clear/snapshot */
    kXBARA_OutputFtm0Fault3         = 49|0x100U,   /**< XBARA_OUT49 output assigned to FTM0 fault 3 */
    kXBARA_OutputFtm1Fault1         = 50|0x100U,   /**< XBARA_OUT50 output assigned to FTM1 fault 1 */
    kXBARA_OutputFtm2Fault1         = 51|0x100U,   /**< XBARA_OUT51 output assigned to FTM2 fault 1 */
    kXBARA_OutputFtm3Fault3         = 52|0x100U,   /**< XBARA_OUT52 output assigned to FTM3 fault 3 */
    kXBARA_OutputPwm1Ch0ExtSync     = 53|0x100U,   /**< XBARA_OUT53 output assigned to PWM0 and PWM1 channel 0 external synchronization */
    kXBARA_OutputPwm1Ch1ExtSync     = 54|0x100U,   /**< XBARA_OUT54 output assigned to PWM0 and PWM1 channel 1 external synchronization */
    kXBARA_OutputPwm1Ch2ExtSync     = 55|0x100U,   /**< XBARA_OUT55 output assigned to PWM0 and PWM1 channel 2 external synchronization */
    kXBARA_OutputPwm1Ch3ExtSync     = 56|0x100U,   /**< XBARA_OUT56 output assigned to PWM0 and PWM1 channel 3 external synchronization */
    kXBARA_OutputPwm1Force          = 57|0x100U,   /**< XBARA_OUT57 output assigned to PWM1 external output force */
    kXBARA_OutputEwmIn              = 58|0x100U,   /**< XBARA_OUT58 output assigned to EWM input */
    kXBARB_OutputAoiIn0             = 0|0x200U,    /**< XBARB_OUT0 output assigned to AOI input0 */
    kXBARB_OutputAoiIn1             = 1|0x200U,    /**< XBARB_OUT1 output assigned to AOI input1 */
    kXBARB_OutputAoiIn2             = 2|0x200U,    /**< XBARB_OUT2 output assigned to AOI input2 */
    kXBARB_OutputAoiIn3             = 3|0x200U,    /**< XBARB_OUT3 output assigned to AOI input3 */
    kXBARB_OutputAoiIn4             = 4|0x200U,    /**< XBARB_OUT4 output assigned to AOI input4 */
    kXBARB_OutputAoiIn5             = 5|0x200U,    /**< XBARB_OUT5 output assigned to AOI input5 */
    kXBARB_OutputAoiIn6             = 6|0x200U,    /**< XBARB_OUT6 output assigned to AOI input6 */
    kXBARB_OutputAoiIn7             = 7|0x200U,    /**< XBARB_OUT7 output assigned to AOI input7 */
    kXBARB_OutputAoiIn8             = 8|0x200U,    /**< XBARB_OUT8 output assigned to AOI input8 */
    kXBARB_OutputAoiIn9             = 9|0x200U,    /**< XBARB_OUT9 output assigned to AOI input9 */
    kXBARB_OutputAoiIn10            = 10|0x200U,   /**< XBARB_OUT10 output assigned to AOI input10 */
    kXBARB_OutputAoiIn11            = 11|0x200U,   /**< XBARB_OUT11 output assigned to AOI input11 */
    kXBARB_OutputAoiIn12            = 12|0x200U,   /**< XBARB_OUT12 output assigned to AOI input12 */
    kXBARB_OutputAoiIn13            = 13|0x200U,   /**< XBARB_OUT13 output assigned to AOI input13 */
    kXBARB_OutputAoiIn14            = 14|0x200U,   /**< XBARB_OUT14 output assigned to AOI input14 */
    kXBARB_OutputAoiIn15            = 15|0x200U,   /**< XBARB_OUT15 output assigned to AOI input15 */
} xbar_output_signal_t;


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
   -- ADC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Peripheral_Access_Layer ADC Peripheral Access Layer
 * @{
 */

/** ADC - Register Layout Typedef */
typedef struct {
  __IO uint32_t SC1[2];                            /**< ADC Status and Control Registers 1, array offset: 0x0, array step: 0x4 */
  __IO uint32_t CFG1;                              /**< ADC Configuration Register 1, offset: 0x8 */
  __IO uint32_t CFG2;                              /**< ADC Configuration Register 2, offset: 0xC */
  __I  uint32_t R[2];                              /**< ADC Data Result Register, array offset: 0x10, array step: 0x4 */
  __IO uint32_t CV1;                               /**< Compare Value Registers, offset: 0x18 */
  __IO uint32_t CV2;                               /**< Compare Value Registers, offset: 0x1C */
  __IO uint32_t SC2;                               /**< Status and Control Register 2, offset: 0x20 */
  __IO uint32_t SC3;                               /**< Status and Control Register 3, offset: 0x24 */
  __IO uint32_t OFS;                               /**< ADC Offset Correction Register, offset: 0x28 */
  __IO uint32_t PG;                                /**< ADC Plus-Side Gain Register, offset: 0x2C */
  __IO uint32_t MG;                                /**< ADC Minus-Side Gain Register, offset: 0x30 */
  __IO uint32_t CLPD;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x34 */
  __IO uint32_t CLPS;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x38 */
  __IO uint32_t CLP4;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x3C */
  __IO uint32_t CLP3;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x40 */
  __IO uint32_t CLP2;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x44 */
  __IO uint32_t CLP1;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x48 */
  __IO uint32_t CLP0;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x4C */
       uint8_t RESERVED_0[4];
  __IO uint32_t CLMD;                              /**< ADC Minus-Side General Calibration Value Register, offset: 0x54 */
  __IO uint32_t CLMS;                              /**< ADC Minus-Side General Calibration Value Register, offset: 0x58 */
  __IO uint32_t CLM4;                              /**< ADC Minus-Side General Calibration Value Register, offset: 0x5C */
  __IO uint32_t CLM3;                              /**< ADC Minus-Side General Calibration Value Register, offset: 0x60 */
  __IO uint32_t CLM2;                              /**< ADC Minus-Side General Calibration Value Register, offset: 0x64 */
  __IO uint32_t CLM1;                              /**< ADC Minus-Side General Calibration Value Register, offset: 0x68 */
  __IO uint32_t CLM0;                              /**< ADC Minus-Side General Calibration Value Register, offset: 0x6C */
} ADC_Type;

/* ----------------------------------------------------------------------------
   -- ADC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Masks ADC Register Masks
 * @{
 */

/*! @name SC1 - ADC Status and Control Registers 1 */
#define ADC_SC1_ADCH_MASK                        (0x1FU)
#define ADC_SC1_ADCH_SHIFT                       (0U)
#define ADC_SC1_ADCH(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC1_ADCH_SHIFT)) & ADC_SC1_ADCH_MASK)
#define ADC_SC1_DIFF_MASK                        (0x20U)
#define ADC_SC1_DIFF_SHIFT                       (5U)
#define ADC_SC1_DIFF(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC1_DIFF_SHIFT)) & ADC_SC1_DIFF_MASK)
#define ADC_SC1_AIEN_MASK                        (0x40U)
#define ADC_SC1_AIEN_SHIFT                       (6U)
#define ADC_SC1_AIEN(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC1_AIEN_SHIFT)) & ADC_SC1_AIEN_MASK)
#define ADC_SC1_COCO_MASK                        (0x80U)
#define ADC_SC1_COCO_SHIFT                       (7U)
#define ADC_SC1_COCO(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC1_COCO_SHIFT)) & ADC_SC1_COCO_MASK)

/* The count of ADC_SC1 */
#define ADC_SC1_COUNT                            (2U)

/*! @name CFG1 - ADC Configuration Register 1 */
#define ADC_CFG1_ADICLK_MASK                     (0x3U)
#define ADC_CFG1_ADICLK_SHIFT                    (0U)
#define ADC_CFG1_ADICLK(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_ADICLK_SHIFT)) & ADC_CFG1_ADICLK_MASK)
#define ADC_CFG1_MODE_MASK                       (0xCU)
#define ADC_CFG1_MODE_SHIFT                      (2U)
#define ADC_CFG1_MODE(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_MODE_SHIFT)) & ADC_CFG1_MODE_MASK)
#define ADC_CFG1_ADLSMP_MASK                     (0x10U)
#define ADC_CFG1_ADLSMP_SHIFT                    (4U)
#define ADC_CFG1_ADLSMP(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_ADLSMP_SHIFT)) & ADC_CFG1_ADLSMP_MASK)
#define ADC_CFG1_ADIV_MASK                       (0x60U)
#define ADC_CFG1_ADIV_SHIFT                      (5U)
#define ADC_CFG1_ADIV(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_ADIV_SHIFT)) & ADC_CFG1_ADIV_MASK)
#define ADC_CFG1_ADLPC_MASK                      (0x80U)
#define ADC_CFG1_ADLPC_SHIFT                     (7U)
#define ADC_CFG1_ADLPC(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_ADLPC_SHIFT)) & ADC_CFG1_ADLPC_MASK)

/*! @name CFG2 - ADC Configuration Register 2 */
#define ADC_CFG2_ADLSTS_MASK                     (0x3U)
#define ADC_CFG2_ADLSTS_SHIFT                    (0U)
#define ADC_CFG2_ADLSTS(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_CFG2_ADLSTS_SHIFT)) & ADC_CFG2_ADLSTS_MASK)
#define ADC_CFG2_ADHSC_MASK                      (0x4U)
#define ADC_CFG2_ADHSC_SHIFT                     (2U)
#define ADC_CFG2_ADHSC(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_CFG2_ADHSC_SHIFT)) & ADC_CFG2_ADHSC_MASK)
#define ADC_CFG2_ADACKEN_MASK                    (0x8U)
#define ADC_CFG2_ADACKEN_SHIFT                   (3U)
#define ADC_CFG2_ADACKEN(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_CFG2_ADACKEN_SHIFT)) & ADC_CFG2_ADACKEN_MASK)
#define ADC_CFG2_MUXSEL_MASK                     (0x10U)
#define ADC_CFG2_MUXSEL_SHIFT                    (4U)
#define ADC_CFG2_MUXSEL(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_CFG2_MUXSEL_SHIFT)) & ADC_CFG2_MUXSEL_MASK)

/*! @name R - ADC Data Result Register */
#define ADC_R_D_MASK                             (0xFFFFU)
#define ADC_R_D_SHIFT                            (0U)
#define ADC_R_D(x)                               (((uint32_t)(((uint32_t)(x)) << ADC_R_D_SHIFT)) & ADC_R_D_MASK)

/* The count of ADC_R */
#define ADC_R_COUNT                              (2U)

/*! @name CV1 - Compare Value Registers */
#define ADC_CV1_CV_MASK                          (0xFFFFU)
#define ADC_CV1_CV_SHIFT                         (0U)
#define ADC_CV1_CV(x)                            (((uint32_t)(((uint32_t)(x)) << ADC_CV1_CV_SHIFT)) & ADC_CV1_CV_MASK)

/*! @name CV2 - Compare Value Registers */
#define ADC_CV2_CV_MASK                          (0xFFFFU)
#define ADC_CV2_CV_SHIFT                         (0U)
#define ADC_CV2_CV(x)                            (((uint32_t)(((uint32_t)(x)) << ADC_CV2_CV_SHIFT)) & ADC_CV2_CV_MASK)

/*! @name SC2 - Status and Control Register 2 */
#define ADC_SC2_REFSEL_MASK                      (0x3U)
#define ADC_SC2_REFSEL_SHIFT                     (0U)
#define ADC_SC2_REFSEL(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_SC2_REFSEL_SHIFT)) & ADC_SC2_REFSEL_MASK)
#define ADC_SC2_DMAEN_MASK                       (0x4U)
#define ADC_SC2_DMAEN_SHIFT                      (2U)
#define ADC_SC2_DMAEN(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_SC2_DMAEN_SHIFT)) & ADC_SC2_DMAEN_MASK)
#define ADC_SC2_ACREN_MASK                       (0x8U)
#define ADC_SC2_ACREN_SHIFT                      (3U)
#define ADC_SC2_ACREN(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ACREN_SHIFT)) & ADC_SC2_ACREN_MASK)
#define ADC_SC2_ACFGT_MASK                       (0x10U)
#define ADC_SC2_ACFGT_SHIFT                      (4U)
#define ADC_SC2_ACFGT(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ACFGT_SHIFT)) & ADC_SC2_ACFGT_MASK)
#define ADC_SC2_ACFE_MASK                        (0x20U)
#define ADC_SC2_ACFE_SHIFT                       (5U)
#define ADC_SC2_ACFE(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ACFE_SHIFT)) & ADC_SC2_ACFE_MASK)
#define ADC_SC2_ADTRG_MASK                       (0x40U)
#define ADC_SC2_ADTRG_SHIFT                      (6U)
#define ADC_SC2_ADTRG(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ADTRG_SHIFT)) & ADC_SC2_ADTRG_MASK)
#define ADC_SC2_ADACT_MASK                       (0x80U)
#define ADC_SC2_ADACT_SHIFT                      (7U)
#define ADC_SC2_ADACT(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ADACT_SHIFT)) & ADC_SC2_ADACT_MASK)

/*! @name SC3 - Status and Control Register 3 */
#define ADC_SC3_AVGS_MASK                        (0x3U)
#define ADC_SC3_AVGS_SHIFT                       (0U)
#define ADC_SC3_AVGS(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC3_AVGS_SHIFT)) & ADC_SC3_AVGS_MASK)
#define ADC_SC3_AVGE_MASK                        (0x4U)
#define ADC_SC3_AVGE_SHIFT                       (2U)
#define ADC_SC3_AVGE(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC3_AVGE_SHIFT)) & ADC_SC3_AVGE_MASK)
#define ADC_SC3_ADCO_MASK                        (0x8U)
#define ADC_SC3_ADCO_SHIFT                       (3U)
#define ADC_SC3_ADCO(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC3_ADCO_SHIFT)) & ADC_SC3_ADCO_MASK)
#define ADC_SC3_CALF_MASK                        (0x40U)
#define ADC_SC3_CALF_SHIFT                       (6U)
#define ADC_SC3_CALF(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC3_CALF_SHIFT)) & ADC_SC3_CALF_MASK)
#define ADC_SC3_CAL_MASK                         (0x80U)
#define ADC_SC3_CAL_SHIFT                        (7U)
#define ADC_SC3_CAL(x)                           (((uint32_t)(((uint32_t)(x)) << ADC_SC3_CAL_SHIFT)) & ADC_SC3_CAL_MASK)

/*! @name OFS - ADC Offset Correction Register */
#define ADC_OFS_OFS_MASK                         (0xFFFFU)
#define ADC_OFS_OFS_SHIFT                        (0U)
#define ADC_OFS_OFS(x)                           (((uint32_t)(((uint32_t)(x)) << ADC_OFS_OFS_SHIFT)) & ADC_OFS_OFS_MASK)

/*! @name PG - ADC Plus-Side Gain Register */
#define ADC_PG_PG_MASK                           (0xFFFFU)
#define ADC_PG_PG_SHIFT                          (0U)
#define ADC_PG_PG(x)                             (((uint32_t)(((uint32_t)(x)) << ADC_PG_PG_SHIFT)) & ADC_PG_PG_MASK)

/*! @name MG - ADC Minus-Side Gain Register */
#define ADC_MG_MG_MASK                           (0xFFFFU)
#define ADC_MG_MG_SHIFT                          (0U)
#define ADC_MG_MG(x)                             (((uint32_t)(((uint32_t)(x)) << ADC_MG_MG_SHIFT)) & ADC_MG_MG_MASK)

/*! @name CLPD - ADC Plus-Side General Calibration Value Register */
#define ADC_CLPD_CLPD_MASK                       (0x3FU)
#define ADC_CLPD_CLPD_SHIFT                      (0U)
#define ADC_CLPD_CLPD(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLPD_CLPD_SHIFT)) & ADC_CLPD_CLPD_MASK)

/*! @name CLPS - ADC Plus-Side General Calibration Value Register */
#define ADC_CLPS_CLPS_MASK                       (0x3FU)
#define ADC_CLPS_CLPS_SHIFT                      (0U)
#define ADC_CLPS_CLPS(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLPS_CLPS_SHIFT)) & ADC_CLPS_CLPS_MASK)

/*! @name CLP4 - ADC Plus-Side General Calibration Value Register */
#define ADC_CLP4_CLP4_MASK                       (0x3FFU)
#define ADC_CLP4_CLP4_SHIFT                      (0U)
#define ADC_CLP4_CLP4(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLP4_CLP4_SHIFT)) & ADC_CLP4_CLP4_MASK)

/*! @name CLP3 - ADC Plus-Side General Calibration Value Register */
#define ADC_CLP3_CLP3_MASK                       (0x1FFU)
#define ADC_CLP3_CLP3_SHIFT                      (0U)
#define ADC_CLP3_CLP3(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLP3_CLP3_SHIFT)) & ADC_CLP3_CLP3_MASK)

/*! @name CLP2 - ADC Plus-Side General Calibration Value Register */
#define ADC_CLP2_CLP2_MASK                       (0xFFU)
#define ADC_CLP2_CLP2_SHIFT                      (0U)
#define ADC_CLP2_CLP2(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLP2_CLP2_SHIFT)) & ADC_CLP2_CLP2_MASK)

/*! @name CLP1 - ADC Plus-Side General Calibration Value Register */
#define ADC_CLP1_CLP1_MASK                       (0x7FU)
#define ADC_CLP1_CLP1_SHIFT                      (0U)
#define ADC_CLP1_CLP1(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLP1_CLP1_SHIFT)) & ADC_CLP1_CLP1_MASK)

/*! @name CLP0 - ADC Plus-Side General Calibration Value Register */
#define ADC_CLP0_CLP0_MASK                       (0x3FU)
#define ADC_CLP0_CLP0_SHIFT                      (0U)
#define ADC_CLP0_CLP0(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLP0_CLP0_SHIFT)) & ADC_CLP0_CLP0_MASK)

/*! @name CLMD - ADC Minus-Side General Calibration Value Register */
#define ADC_CLMD_CLMD_MASK                       (0x3FU)
#define ADC_CLMD_CLMD_SHIFT                      (0U)
#define ADC_CLMD_CLMD(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLMD_CLMD_SHIFT)) & ADC_CLMD_CLMD_MASK)

/*! @name CLMS - ADC Minus-Side General Calibration Value Register */
#define ADC_CLMS_CLMS_MASK                       (0x3FU)
#define ADC_CLMS_CLMS_SHIFT                      (0U)
#define ADC_CLMS_CLMS(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLMS_CLMS_SHIFT)) & ADC_CLMS_CLMS_MASK)

/*! @name CLM4 - ADC Minus-Side General Calibration Value Register */
#define ADC_CLM4_CLM4_MASK                       (0x3FFU)
#define ADC_CLM4_CLM4_SHIFT                      (0U)
#define ADC_CLM4_CLM4(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLM4_CLM4_SHIFT)) & ADC_CLM4_CLM4_MASK)

/*! @name CLM3 - ADC Minus-Side General Calibration Value Register */
#define ADC_CLM3_CLM3_MASK                       (0x1FFU)
#define ADC_CLM3_CLM3_SHIFT                      (0U)
#define ADC_CLM3_CLM3(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLM3_CLM3_SHIFT)) & ADC_CLM3_CLM3_MASK)

/*! @name CLM2 - ADC Minus-Side General Calibration Value Register */
#define ADC_CLM2_CLM2_MASK                       (0xFFU)
#define ADC_CLM2_CLM2_SHIFT                      (0U)
#define ADC_CLM2_CLM2(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLM2_CLM2_SHIFT)) & ADC_CLM2_CLM2_MASK)

/*! @name CLM1 - ADC Minus-Side General Calibration Value Register */
#define ADC_CLM1_CLM1_MASK                       (0x7FU)
#define ADC_CLM1_CLM1_SHIFT                      (0U)
#define ADC_CLM1_CLM1(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLM1_CLM1_SHIFT)) & ADC_CLM1_CLM1_MASK)

/*! @name CLM0 - ADC Minus-Side General Calibration Value Register */
#define ADC_CLM0_CLM0_MASK                       (0x3FU)
#define ADC_CLM0_CLM0_SHIFT                      (0U)
#define ADC_CLM0_CLM0(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLM0_CLM0_SHIFT)) & ADC_CLM0_CLM0_MASK)


/*!
 * @}
 */ /* end of group ADC_Register_Masks */


/* ADC - Peripheral instance base addresses */
/** Peripheral ADC0 base address */
#define ADC0_BASE                                (0x4003B000u)
/** Peripheral ADC0 base pointer */
#define ADC0                                     ((ADC_Type *)ADC0_BASE)
/** Array initializer of ADC peripheral base addresses */
#define ADC_BASE_ADDRS                           { ADC0_BASE }
/** Array initializer of ADC peripheral base pointers */
#define ADC_BASE_PTRS                            { ADC0 }
/** Interrupt vectors for the ADC peripheral type */
#define ADC_IRQS                                 { ADC0_IRQn }

/*!
 * @}
 */ /* end of group ADC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- AIPS Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AIPS_Peripheral_Access_Layer AIPS Peripheral Access Layer
 * @{
 */

/** AIPS - Register Layout Typedef */
typedef struct {
  __IO uint32_t MPRA;                              /**< Master Privilege Register A, offset: 0x0 */
       uint8_t RESERVED_0[28];
  __IO uint32_t PACRA;                             /**< Peripheral Access Control Register, offset: 0x20 */
  __IO uint32_t PACRB;                             /**< Peripheral Access Control Register, offset: 0x24 */
  __IO uint32_t PACRC;                             /**< Peripheral Access Control Register, offset: 0x28 */
  __IO uint32_t PACRD;                             /**< Peripheral Access Control Register, offset: 0x2C */
       uint8_t RESERVED_1[16];
  __IO uint32_t PACRE;                             /**< Peripheral Access Control Register, offset: 0x40 */
  __IO uint32_t PACRF;                             /**< Peripheral Access Control Register, offset: 0x44 */
  __IO uint32_t PACRG;                             /**< Peripheral Access Control Register, offset: 0x48 */
  __IO uint32_t PACRH;                             /**< Peripheral Access Control Register, offset: 0x4C */
  __IO uint32_t PACRI;                             /**< Peripheral Access Control Register, offset: 0x50 */
  __IO uint32_t PACRJ;                             /**< Peripheral Access Control Register, offset: 0x54 */
  __IO uint32_t PACRK;                             /**< Peripheral Access Control Register, offset: 0x58 */
  __IO uint32_t PACRL;                             /**< Peripheral Access Control Register, offset: 0x5C */
  __IO uint32_t PACRM;                             /**< Peripheral Access Control Register, offset: 0x60 */
  __IO uint32_t PACRN;                             /**< Peripheral Access Control Register, offset: 0x64 */
  __IO uint32_t PACRO;                             /**< Peripheral Access Control Register, offset: 0x68 */
  __IO uint32_t PACRP;                             /**< Peripheral Access Control Register, offset: 0x6C */
} AIPS_Type;

/* ----------------------------------------------------------------------------
   -- AIPS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AIPS_Register_Masks AIPS Register Masks
 * @{
 */

/*! @name MPRA - Master Privilege Register A */
#define AIPS_MPRA_MPL3_MASK                      (0x10000U)
#define AIPS_MPRA_MPL3_SHIFT                     (16U)
#define AIPS_MPRA_MPL3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_MPRA_MPL3_SHIFT)) & AIPS_MPRA_MPL3_MASK)
#define AIPS_MPRA_MTW3_MASK                      (0x20000U)
#define AIPS_MPRA_MTW3_SHIFT                     (17U)
#define AIPS_MPRA_MTW3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_MPRA_MTW3_SHIFT)) & AIPS_MPRA_MTW3_MASK)
#define AIPS_MPRA_MTR3_MASK                      (0x40000U)
#define AIPS_MPRA_MTR3_SHIFT                     (18U)
#define AIPS_MPRA_MTR3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_MPRA_MTR3_SHIFT)) & AIPS_MPRA_MTR3_MASK)
#define AIPS_MPRA_MPL2_MASK                      (0x100000U)
#define AIPS_MPRA_MPL2_SHIFT                     (20U)
#define AIPS_MPRA_MPL2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_MPRA_MPL2_SHIFT)) & AIPS_MPRA_MPL2_MASK)
#define AIPS_MPRA_MTW2_MASK                      (0x200000U)
#define AIPS_MPRA_MTW2_SHIFT                     (21U)
#define AIPS_MPRA_MTW2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_MPRA_MTW2_SHIFT)) & AIPS_MPRA_MTW2_MASK)
#define AIPS_MPRA_MTR2_MASK                      (0x400000U)
#define AIPS_MPRA_MTR2_SHIFT                     (22U)
#define AIPS_MPRA_MTR2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_MPRA_MTR2_SHIFT)) & AIPS_MPRA_MTR2_MASK)
#define AIPS_MPRA_MPL1_MASK                      (0x1000000U)
#define AIPS_MPRA_MPL1_SHIFT                     (24U)
#define AIPS_MPRA_MPL1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_MPRA_MPL1_SHIFT)) & AIPS_MPRA_MPL1_MASK)
#define AIPS_MPRA_MTW1_MASK                      (0x2000000U)
#define AIPS_MPRA_MTW1_SHIFT                     (25U)
#define AIPS_MPRA_MTW1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_MPRA_MTW1_SHIFT)) & AIPS_MPRA_MTW1_MASK)
#define AIPS_MPRA_MTR1_MASK                      (0x4000000U)
#define AIPS_MPRA_MTR1_SHIFT                     (26U)
#define AIPS_MPRA_MTR1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_MPRA_MTR1_SHIFT)) & AIPS_MPRA_MTR1_MASK)
#define AIPS_MPRA_MPL0_MASK                      (0x10000000U)
#define AIPS_MPRA_MPL0_SHIFT                     (28U)
#define AIPS_MPRA_MPL0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_MPRA_MPL0_SHIFT)) & AIPS_MPRA_MPL0_MASK)
#define AIPS_MPRA_MTW0_MASK                      (0x20000000U)
#define AIPS_MPRA_MTW0_SHIFT                     (29U)
#define AIPS_MPRA_MTW0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_MPRA_MTW0_SHIFT)) & AIPS_MPRA_MTW0_MASK)
#define AIPS_MPRA_MTR0_MASK                      (0x40000000U)
#define AIPS_MPRA_MTR0_SHIFT                     (30U)
#define AIPS_MPRA_MTR0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_MPRA_MTR0_SHIFT)) & AIPS_MPRA_MTR0_MASK)

/*! @name PACRA - Peripheral Access Control Register */
#define AIPS_PACRA_TP7_MASK                      (0x1U)
#define AIPS_PACRA_TP7_SHIFT                     (0U)
#define AIPS_PACRA_TP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_TP7_SHIFT)) & AIPS_PACRA_TP7_MASK)
#define AIPS_PACRA_WP7_MASK                      (0x2U)
#define AIPS_PACRA_WP7_SHIFT                     (1U)
#define AIPS_PACRA_WP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_WP7_SHIFT)) & AIPS_PACRA_WP7_MASK)
#define AIPS_PACRA_SP7_MASK                      (0x4U)
#define AIPS_PACRA_SP7_SHIFT                     (2U)
#define AIPS_PACRA_SP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_SP7_SHIFT)) & AIPS_PACRA_SP7_MASK)
#define AIPS_PACRA_TP6_MASK                      (0x10U)
#define AIPS_PACRA_TP6_SHIFT                     (4U)
#define AIPS_PACRA_TP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_TP6_SHIFT)) & AIPS_PACRA_TP6_MASK)
#define AIPS_PACRA_WP6_MASK                      (0x20U)
#define AIPS_PACRA_WP6_SHIFT                     (5U)
#define AIPS_PACRA_WP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_WP6_SHIFT)) & AIPS_PACRA_WP6_MASK)
#define AIPS_PACRA_SP6_MASK                      (0x40U)
#define AIPS_PACRA_SP6_SHIFT                     (6U)
#define AIPS_PACRA_SP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_SP6_SHIFT)) & AIPS_PACRA_SP6_MASK)
#define AIPS_PACRA_TP5_MASK                      (0x100U)
#define AIPS_PACRA_TP5_SHIFT                     (8U)
#define AIPS_PACRA_TP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_TP5_SHIFT)) & AIPS_PACRA_TP5_MASK)
#define AIPS_PACRA_WP5_MASK                      (0x200U)
#define AIPS_PACRA_WP5_SHIFT                     (9U)
#define AIPS_PACRA_WP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_WP5_SHIFT)) & AIPS_PACRA_WP5_MASK)
#define AIPS_PACRA_SP5_MASK                      (0x400U)
#define AIPS_PACRA_SP5_SHIFT                     (10U)
#define AIPS_PACRA_SP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_SP5_SHIFT)) & AIPS_PACRA_SP5_MASK)
#define AIPS_PACRA_TP4_MASK                      (0x1000U)
#define AIPS_PACRA_TP4_SHIFT                     (12U)
#define AIPS_PACRA_TP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_TP4_SHIFT)) & AIPS_PACRA_TP4_MASK)
#define AIPS_PACRA_WP4_MASK                      (0x2000U)
#define AIPS_PACRA_WP4_SHIFT                     (13U)
#define AIPS_PACRA_WP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_WP4_SHIFT)) & AIPS_PACRA_WP4_MASK)
#define AIPS_PACRA_SP4_MASK                      (0x4000U)
#define AIPS_PACRA_SP4_SHIFT                     (14U)
#define AIPS_PACRA_SP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_SP4_SHIFT)) & AIPS_PACRA_SP4_MASK)
#define AIPS_PACRA_TP3_MASK                      (0x10000U)
#define AIPS_PACRA_TP3_SHIFT                     (16U)
#define AIPS_PACRA_TP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_TP3_SHIFT)) & AIPS_PACRA_TP3_MASK)
#define AIPS_PACRA_WP3_MASK                      (0x20000U)
#define AIPS_PACRA_WP3_SHIFT                     (17U)
#define AIPS_PACRA_WP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_WP3_SHIFT)) & AIPS_PACRA_WP3_MASK)
#define AIPS_PACRA_SP3_MASK                      (0x40000U)
#define AIPS_PACRA_SP3_SHIFT                     (18U)
#define AIPS_PACRA_SP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_SP3_SHIFT)) & AIPS_PACRA_SP3_MASK)
#define AIPS_PACRA_TP2_MASK                      (0x100000U)
#define AIPS_PACRA_TP2_SHIFT                     (20U)
#define AIPS_PACRA_TP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_TP2_SHIFT)) & AIPS_PACRA_TP2_MASK)
#define AIPS_PACRA_WP2_MASK                      (0x200000U)
#define AIPS_PACRA_WP2_SHIFT                     (21U)
#define AIPS_PACRA_WP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_WP2_SHIFT)) & AIPS_PACRA_WP2_MASK)
#define AIPS_PACRA_SP2_MASK                      (0x400000U)
#define AIPS_PACRA_SP2_SHIFT                     (22U)
#define AIPS_PACRA_SP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_SP2_SHIFT)) & AIPS_PACRA_SP2_MASK)
#define AIPS_PACRA_TP1_MASK                      (0x1000000U)
#define AIPS_PACRA_TP1_SHIFT                     (24U)
#define AIPS_PACRA_TP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_TP1_SHIFT)) & AIPS_PACRA_TP1_MASK)
#define AIPS_PACRA_WP1_MASK                      (0x2000000U)
#define AIPS_PACRA_WP1_SHIFT                     (25U)
#define AIPS_PACRA_WP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_WP1_SHIFT)) & AIPS_PACRA_WP1_MASK)
#define AIPS_PACRA_SP1_MASK                      (0x4000000U)
#define AIPS_PACRA_SP1_SHIFT                     (26U)
#define AIPS_PACRA_SP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_SP1_SHIFT)) & AIPS_PACRA_SP1_MASK)
#define AIPS_PACRA_TP0_MASK                      (0x10000000U)
#define AIPS_PACRA_TP0_SHIFT                     (28U)
#define AIPS_PACRA_TP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_TP0_SHIFT)) & AIPS_PACRA_TP0_MASK)
#define AIPS_PACRA_WP0_MASK                      (0x20000000U)
#define AIPS_PACRA_WP0_SHIFT                     (29U)
#define AIPS_PACRA_WP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_WP0_SHIFT)) & AIPS_PACRA_WP0_MASK)
#define AIPS_PACRA_SP0_MASK                      (0x40000000U)
#define AIPS_PACRA_SP0_SHIFT                     (30U)
#define AIPS_PACRA_SP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_SP0_SHIFT)) & AIPS_PACRA_SP0_MASK)

/*! @name PACRB - Peripheral Access Control Register */
#define AIPS_PACRB_TP7_MASK                      (0x1U)
#define AIPS_PACRB_TP7_SHIFT                     (0U)
#define AIPS_PACRB_TP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_TP7_SHIFT)) & AIPS_PACRB_TP7_MASK)
#define AIPS_PACRB_WP7_MASK                      (0x2U)
#define AIPS_PACRB_WP7_SHIFT                     (1U)
#define AIPS_PACRB_WP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_WP7_SHIFT)) & AIPS_PACRB_WP7_MASK)
#define AIPS_PACRB_SP7_MASK                      (0x4U)
#define AIPS_PACRB_SP7_SHIFT                     (2U)
#define AIPS_PACRB_SP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_SP7_SHIFT)) & AIPS_PACRB_SP7_MASK)
#define AIPS_PACRB_TP6_MASK                      (0x10U)
#define AIPS_PACRB_TP6_SHIFT                     (4U)
#define AIPS_PACRB_TP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_TP6_SHIFT)) & AIPS_PACRB_TP6_MASK)
#define AIPS_PACRB_WP6_MASK                      (0x20U)
#define AIPS_PACRB_WP6_SHIFT                     (5U)
#define AIPS_PACRB_WP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_WP6_SHIFT)) & AIPS_PACRB_WP6_MASK)
#define AIPS_PACRB_SP6_MASK                      (0x40U)
#define AIPS_PACRB_SP6_SHIFT                     (6U)
#define AIPS_PACRB_SP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_SP6_SHIFT)) & AIPS_PACRB_SP6_MASK)
#define AIPS_PACRB_TP5_MASK                      (0x100U)
#define AIPS_PACRB_TP5_SHIFT                     (8U)
#define AIPS_PACRB_TP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_TP5_SHIFT)) & AIPS_PACRB_TP5_MASK)
#define AIPS_PACRB_WP5_MASK                      (0x200U)
#define AIPS_PACRB_WP5_SHIFT                     (9U)
#define AIPS_PACRB_WP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_WP5_SHIFT)) & AIPS_PACRB_WP5_MASK)
#define AIPS_PACRB_SP5_MASK                      (0x400U)
#define AIPS_PACRB_SP5_SHIFT                     (10U)
#define AIPS_PACRB_SP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_SP5_SHIFT)) & AIPS_PACRB_SP5_MASK)
#define AIPS_PACRB_TP4_MASK                      (0x1000U)
#define AIPS_PACRB_TP4_SHIFT                     (12U)
#define AIPS_PACRB_TP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_TP4_SHIFT)) & AIPS_PACRB_TP4_MASK)
#define AIPS_PACRB_WP4_MASK                      (0x2000U)
#define AIPS_PACRB_WP4_SHIFT                     (13U)
#define AIPS_PACRB_WP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_WP4_SHIFT)) & AIPS_PACRB_WP4_MASK)
#define AIPS_PACRB_SP4_MASK                      (0x4000U)
#define AIPS_PACRB_SP4_SHIFT                     (14U)
#define AIPS_PACRB_SP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_SP4_SHIFT)) & AIPS_PACRB_SP4_MASK)
#define AIPS_PACRB_TP3_MASK                      (0x10000U)
#define AIPS_PACRB_TP3_SHIFT                     (16U)
#define AIPS_PACRB_TP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_TP3_SHIFT)) & AIPS_PACRB_TP3_MASK)
#define AIPS_PACRB_WP3_MASK                      (0x20000U)
#define AIPS_PACRB_WP3_SHIFT                     (17U)
#define AIPS_PACRB_WP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_WP3_SHIFT)) & AIPS_PACRB_WP3_MASK)
#define AIPS_PACRB_SP3_MASK                      (0x40000U)
#define AIPS_PACRB_SP3_SHIFT                     (18U)
#define AIPS_PACRB_SP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_SP3_SHIFT)) & AIPS_PACRB_SP3_MASK)
#define AIPS_PACRB_TP2_MASK                      (0x100000U)
#define AIPS_PACRB_TP2_SHIFT                     (20U)
#define AIPS_PACRB_TP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_TP2_SHIFT)) & AIPS_PACRB_TP2_MASK)
#define AIPS_PACRB_WP2_MASK                      (0x200000U)
#define AIPS_PACRB_WP2_SHIFT                     (21U)
#define AIPS_PACRB_WP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_WP2_SHIFT)) & AIPS_PACRB_WP2_MASK)
#define AIPS_PACRB_SP2_MASK                      (0x400000U)
#define AIPS_PACRB_SP2_SHIFT                     (22U)
#define AIPS_PACRB_SP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_SP2_SHIFT)) & AIPS_PACRB_SP2_MASK)
#define AIPS_PACRB_TP1_MASK                      (0x1000000U)
#define AIPS_PACRB_TP1_SHIFT                     (24U)
#define AIPS_PACRB_TP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_TP1_SHIFT)) & AIPS_PACRB_TP1_MASK)
#define AIPS_PACRB_WP1_MASK                      (0x2000000U)
#define AIPS_PACRB_WP1_SHIFT                     (25U)
#define AIPS_PACRB_WP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_WP1_SHIFT)) & AIPS_PACRB_WP1_MASK)
#define AIPS_PACRB_SP1_MASK                      (0x4000000U)
#define AIPS_PACRB_SP1_SHIFT                     (26U)
#define AIPS_PACRB_SP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_SP1_SHIFT)) & AIPS_PACRB_SP1_MASK)
#define AIPS_PACRB_TP0_MASK                      (0x10000000U)
#define AIPS_PACRB_TP0_SHIFT                     (28U)
#define AIPS_PACRB_TP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_TP0_SHIFT)) & AIPS_PACRB_TP0_MASK)
#define AIPS_PACRB_WP0_MASK                      (0x20000000U)
#define AIPS_PACRB_WP0_SHIFT                     (29U)
#define AIPS_PACRB_WP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_WP0_SHIFT)) & AIPS_PACRB_WP0_MASK)
#define AIPS_PACRB_SP0_MASK                      (0x40000000U)
#define AIPS_PACRB_SP0_SHIFT                     (30U)
#define AIPS_PACRB_SP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_SP0_SHIFT)) & AIPS_PACRB_SP0_MASK)

/*! @name PACRC - Peripheral Access Control Register */
#define AIPS_PACRC_TP7_MASK                      (0x1U)
#define AIPS_PACRC_TP7_SHIFT                     (0U)
#define AIPS_PACRC_TP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_TP7_SHIFT)) & AIPS_PACRC_TP7_MASK)
#define AIPS_PACRC_WP7_MASK                      (0x2U)
#define AIPS_PACRC_WP7_SHIFT                     (1U)
#define AIPS_PACRC_WP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_WP7_SHIFT)) & AIPS_PACRC_WP7_MASK)
#define AIPS_PACRC_SP7_MASK                      (0x4U)
#define AIPS_PACRC_SP7_SHIFT                     (2U)
#define AIPS_PACRC_SP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_SP7_SHIFT)) & AIPS_PACRC_SP7_MASK)
#define AIPS_PACRC_TP6_MASK                      (0x10U)
#define AIPS_PACRC_TP6_SHIFT                     (4U)
#define AIPS_PACRC_TP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_TP6_SHIFT)) & AIPS_PACRC_TP6_MASK)
#define AIPS_PACRC_WP6_MASK                      (0x20U)
#define AIPS_PACRC_WP6_SHIFT                     (5U)
#define AIPS_PACRC_WP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_WP6_SHIFT)) & AIPS_PACRC_WP6_MASK)
#define AIPS_PACRC_SP6_MASK                      (0x40U)
#define AIPS_PACRC_SP6_SHIFT                     (6U)
#define AIPS_PACRC_SP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_SP6_SHIFT)) & AIPS_PACRC_SP6_MASK)
#define AIPS_PACRC_TP5_MASK                      (0x100U)
#define AIPS_PACRC_TP5_SHIFT                     (8U)
#define AIPS_PACRC_TP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_TP5_SHIFT)) & AIPS_PACRC_TP5_MASK)
#define AIPS_PACRC_WP5_MASK                      (0x200U)
#define AIPS_PACRC_WP5_SHIFT                     (9U)
#define AIPS_PACRC_WP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_WP5_SHIFT)) & AIPS_PACRC_WP5_MASK)
#define AIPS_PACRC_SP5_MASK                      (0x400U)
#define AIPS_PACRC_SP5_SHIFT                     (10U)
#define AIPS_PACRC_SP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_SP5_SHIFT)) & AIPS_PACRC_SP5_MASK)
#define AIPS_PACRC_TP4_MASK                      (0x1000U)
#define AIPS_PACRC_TP4_SHIFT                     (12U)
#define AIPS_PACRC_TP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_TP4_SHIFT)) & AIPS_PACRC_TP4_MASK)
#define AIPS_PACRC_WP4_MASK                      (0x2000U)
#define AIPS_PACRC_WP4_SHIFT                     (13U)
#define AIPS_PACRC_WP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_WP4_SHIFT)) & AIPS_PACRC_WP4_MASK)
#define AIPS_PACRC_SP4_MASK                      (0x4000U)
#define AIPS_PACRC_SP4_SHIFT                     (14U)
#define AIPS_PACRC_SP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_SP4_SHIFT)) & AIPS_PACRC_SP4_MASK)
#define AIPS_PACRC_TP3_MASK                      (0x10000U)
#define AIPS_PACRC_TP3_SHIFT                     (16U)
#define AIPS_PACRC_TP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_TP3_SHIFT)) & AIPS_PACRC_TP3_MASK)
#define AIPS_PACRC_WP3_MASK                      (0x20000U)
#define AIPS_PACRC_WP3_SHIFT                     (17U)
#define AIPS_PACRC_WP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_WP3_SHIFT)) & AIPS_PACRC_WP3_MASK)
#define AIPS_PACRC_SP3_MASK                      (0x40000U)
#define AIPS_PACRC_SP3_SHIFT                     (18U)
#define AIPS_PACRC_SP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_SP3_SHIFT)) & AIPS_PACRC_SP3_MASK)
#define AIPS_PACRC_TP2_MASK                      (0x100000U)
#define AIPS_PACRC_TP2_SHIFT                     (20U)
#define AIPS_PACRC_TP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_TP2_SHIFT)) & AIPS_PACRC_TP2_MASK)
#define AIPS_PACRC_WP2_MASK                      (0x200000U)
#define AIPS_PACRC_WP2_SHIFT                     (21U)
#define AIPS_PACRC_WP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_WP2_SHIFT)) & AIPS_PACRC_WP2_MASK)
#define AIPS_PACRC_SP2_MASK                      (0x400000U)
#define AIPS_PACRC_SP2_SHIFT                     (22U)
#define AIPS_PACRC_SP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_SP2_SHIFT)) & AIPS_PACRC_SP2_MASK)
#define AIPS_PACRC_TP1_MASK                      (0x1000000U)
#define AIPS_PACRC_TP1_SHIFT                     (24U)
#define AIPS_PACRC_TP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_TP1_SHIFT)) & AIPS_PACRC_TP1_MASK)
#define AIPS_PACRC_WP1_MASK                      (0x2000000U)
#define AIPS_PACRC_WP1_SHIFT                     (25U)
#define AIPS_PACRC_WP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_WP1_SHIFT)) & AIPS_PACRC_WP1_MASK)
#define AIPS_PACRC_SP1_MASK                      (0x4000000U)
#define AIPS_PACRC_SP1_SHIFT                     (26U)
#define AIPS_PACRC_SP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_SP1_SHIFT)) & AIPS_PACRC_SP1_MASK)
#define AIPS_PACRC_TP0_MASK                      (0x10000000U)
#define AIPS_PACRC_TP0_SHIFT                     (28U)
#define AIPS_PACRC_TP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_TP0_SHIFT)) & AIPS_PACRC_TP0_MASK)
#define AIPS_PACRC_WP0_MASK                      (0x20000000U)
#define AIPS_PACRC_WP0_SHIFT                     (29U)
#define AIPS_PACRC_WP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_WP0_SHIFT)) & AIPS_PACRC_WP0_MASK)
#define AIPS_PACRC_SP0_MASK                      (0x40000000U)
#define AIPS_PACRC_SP0_SHIFT                     (30U)
#define AIPS_PACRC_SP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRC_SP0_SHIFT)) & AIPS_PACRC_SP0_MASK)

/*! @name PACRD - Peripheral Access Control Register */
#define AIPS_PACRD_TP7_MASK                      (0x1U)
#define AIPS_PACRD_TP7_SHIFT                     (0U)
#define AIPS_PACRD_TP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_TP7_SHIFT)) & AIPS_PACRD_TP7_MASK)
#define AIPS_PACRD_WP7_MASK                      (0x2U)
#define AIPS_PACRD_WP7_SHIFT                     (1U)
#define AIPS_PACRD_WP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_WP7_SHIFT)) & AIPS_PACRD_WP7_MASK)
#define AIPS_PACRD_SP7_MASK                      (0x4U)
#define AIPS_PACRD_SP7_SHIFT                     (2U)
#define AIPS_PACRD_SP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_SP7_SHIFT)) & AIPS_PACRD_SP7_MASK)
#define AIPS_PACRD_TP6_MASK                      (0x10U)
#define AIPS_PACRD_TP6_SHIFT                     (4U)
#define AIPS_PACRD_TP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_TP6_SHIFT)) & AIPS_PACRD_TP6_MASK)
#define AIPS_PACRD_WP6_MASK                      (0x20U)
#define AIPS_PACRD_WP6_SHIFT                     (5U)
#define AIPS_PACRD_WP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_WP6_SHIFT)) & AIPS_PACRD_WP6_MASK)
#define AIPS_PACRD_SP6_MASK                      (0x40U)
#define AIPS_PACRD_SP6_SHIFT                     (6U)
#define AIPS_PACRD_SP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_SP6_SHIFT)) & AIPS_PACRD_SP6_MASK)
#define AIPS_PACRD_TP5_MASK                      (0x100U)
#define AIPS_PACRD_TP5_SHIFT                     (8U)
#define AIPS_PACRD_TP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_TP5_SHIFT)) & AIPS_PACRD_TP5_MASK)
#define AIPS_PACRD_WP5_MASK                      (0x200U)
#define AIPS_PACRD_WP5_SHIFT                     (9U)
#define AIPS_PACRD_WP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_WP5_SHIFT)) & AIPS_PACRD_WP5_MASK)
#define AIPS_PACRD_SP5_MASK                      (0x400U)
#define AIPS_PACRD_SP5_SHIFT                     (10U)
#define AIPS_PACRD_SP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_SP5_SHIFT)) & AIPS_PACRD_SP5_MASK)
#define AIPS_PACRD_TP4_MASK                      (0x1000U)
#define AIPS_PACRD_TP4_SHIFT                     (12U)
#define AIPS_PACRD_TP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_TP4_SHIFT)) & AIPS_PACRD_TP4_MASK)
#define AIPS_PACRD_WP4_MASK                      (0x2000U)
#define AIPS_PACRD_WP4_SHIFT                     (13U)
#define AIPS_PACRD_WP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_WP4_SHIFT)) & AIPS_PACRD_WP4_MASK)
#define AIPS_PACRD_SP4_MASK                      (0x4000U)
#define AIPS_PACRD_SP4_SHIFT                     (14U)
#define AIPS_PACRD_SP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_SP4_SHIFT)) & AIPS_PACRD_SP4_MASK)
#define AIPS_PACRD_TP3_MASK                      (0x10000U)
#define AIPS_PACRD_TP3_SHIFT                     (16U)
#define AIPS_PACRD_TP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_TP3_SHIFT)) & AIPS_PACRD_TP3_MASK)
#define AIPS_PACRD_WP3_MASK                      (0x20000U)
#define AIPS_PACRD_WP3_SHIFT                     (17U)
#define AIPS_PACRD_WP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_WP3_SHIFT)) & AIPS_PACRD_WP3_MASK)
#define AIPS_PACRD_SP3_MASK                      (0x40000U)
#define AIPS_PACRD_SP3_SHIFT                     (18U)
#define AIPS_PACRD_SP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_SP3_SHIFT)) & AIPS_PACRD_SP3_MASK)
#define AIPS_PACRD_TP2_MASK                      (0x100000U)
#define AIPS_PACRD_TP2_SHIFT                     (20U)
#define AIPS_PACRD_TP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_TP2_SHIFT)) & AIPS_PACRD_TP2_MASK)
#define AIPS_PACRD_WP2_MASK                      (0x200000U)
#define AIPS_PACRD_WP2_SHIFT                     (21U)
#define AIPS_PACRD_WP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_WP2_SHIFT)) & AIPS_PACRD_WP2_MASK)
#define AIPS_PACRD_SP2_MASK                      (0x400000U)
#define AIPS_PACRD_SP2_SHIFT                     (22U)
#define AIPS_PACRD_SP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_SP2_SHIFT)) & AIPS_PACRD_SP2_MASK)
#define AIPS_PACRD_TP1_MASK                      (0x1000000U)
#define AIPS_PACRD_TP1_SHIFT                     (24U)
#define AIPS_PACRD_TP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_TP1_SHIFT)) & AIPS_PACRD_TP1_MASK)
#define AIPS_PACRD_WP1_MASK                      (0x2000000U)
#define AIPS_PACRD_WP1_SHIFT                     (25U)
#define AIPS_PACRD_WP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_WP1_SHIFT)) & AIPS_PACRD_WP1_MASK)
#define AIPS_PACRD_SP1_MASK                      (0x4000000U)
#define AIPS_PACRD_SP1_SHIFT                     (26U)
#define AIPS_PACRD_SP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_SP1_SHIFT)) & AIPS_PACRD_SP1_MASK)
#define AIPS_PACRD_TP0_MASK                      (0x10000000U)
#define AIPS_PACRD_TP0_SHIFT                     (28U)
#define AIPS_PACRD_TP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_TP0_SHIFT)) & AIPS_PACRD_TP0_MASK)
#define AIPS_PACRD_WP0_MASK                      (0x20000000U)
#define AIPS_PACRD_WP0_SHIFT                     (29U)
#define AIPS_PACRD_WP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_WP0_SHIFT)) & AIPS_PACRD_WP0_MASK)
#define AIPS_PACRD_SP0_MASK                      (0x40000000U)
#define AIPS_PACRD_SP0_SHIFT                     (30U)
#define AIPS_PACRD_SP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRD_SP0_SHIFT)) & AIPS_PACRD_SP0_MASK)

/*! @name PACRE - Peripheral Access Control Register */
#define AIPS_PACRE_TP7_MASK                      (0x1U)
#define AIPS_PACRE_TP7_SHIFT                     (0U)
#define AIPS_PACRE_TP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_TP7_SHIFT)) & AIPS_PACRE_TP7_MASK)
#define AIPS_PACRE_WP7_MASK                      (0x2U)
#define AIPS_PACRE_WP7_SHIFT                     (1U)
#define AIPS_PACRE_WP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_WP7_SHIFT)) & AIPS_PACRE_WP7_MASK)
#define AIPS_PACRE_SP7_MASK                      (0x4U)
#define AIPS_PACRE_SP7_SHIFT                     (2U)
#define AIPS_PACRE_SP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_SP7_SHIFT)) & AIPS_PACRE_SP7_MASK)
#define AIPS_PACRE_TP6_MASK                      (0x10U)
#define AIPS_PACRE_TP6_SHIFT                     (4U)
#define AIPS_PACRE_TP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_TP6_SHIFT)) & AIPS_PACRE_TP6_MASK)
#define AIPS_PACRE_WP6_MASK                      (0x20U)
#define AIPS_PACRE_WP6_SHIFT                     (5U)
#define AIPS_PACRE_WP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_WP6_SHIFT)) & AIPS_PACRE_WP6_MASK)
#define AIPS_PACRE_SP6_MASK                      (0x40U)
#define AIPS_PACRE_SP6_SHIFT                     (6U)
#define AIPS_PACRE_SP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_SP6_SHIFT)) & AIPS_PACRE_SP6_MASK)
#define AIPS_PACRE_TP5_MASK                      (0x100U)
#define AIPS_PACRE_TP5_SHIFT                     (8U)
#define AIPS_PACRE_TP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_TP5_SHIFT)) & AIPS_PACRE_TP5_MASK)
#define AIPS_PACRE_WP5_MASK                      (0x200U)
#define AIPS_PACRE_WP5_SHIFT                     (9U)
#define AIPS_PACRE_WP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_WP5_SHIFT)) & AIPS_PACRE_WP5_MASK)
#define AIPS_PACRE_SP5_MASK                      (0x400U)
#define AIPS_PACRE_SP5_SHIFT                     (10U)
#define AIPS_PACRE_SP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_SP5_SHIFT)) & AIPS_PACRE_SP5_MASK)
#define AIPS_PACRE_TP4_MASK                      (0x1000U)
#define AIPS_PACRE_TP4_SHIFT                     (12U)
#define AIPS_PACRE_TP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_TP4_SHIFT)) & AIPS_PACRE_TP4_MASK)
#define AIPS_PACRE_WP4_MASK                      (0x2000U)
#define AIPS_PACRE_WP4_SHIFT                     (13U)
#define AIPS_PACRE_WP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_WP4_SHIFT)) & AIPS_PACRE_WP4_MASK)
#define AIPS_PACRE_SP4_MASK                      (0x4000U)
#define AIPS_PACRE_SP4_SHIFT                     (14U)
#define AIPS_PACRE_SP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_SP4_SHIFT)) & AIPS_PACRE_SP4_MASK)
#define AIPS_PACRE_TP3_MASK                      (0x10000U)
#define AIPS_PACRE_TP3_SHIFT                     (16U)
#define AIPS_PACRE_TP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_TP3_SHIFT)) & AIPS_PACRE_TP3_MASK)
#define AIPS_PACRE_WP3_MASK                      (0x20000U)
#define AIPS_PACRE_WP3_SHIFT                     (17U)
#define AIPS_PACRE_WP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_WP3_SHIFT)) & AIPS_PACRE_WP3_MASK)
#define AIPS_PACRE_SP3_MASK                      (0x40000U)
#define AIPS_PACRE_SP3_SHIFT                     (18U)
#define AIPS_PACRE_SP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_SP3_SHIFT)) & AIPS_PACRE_SP3_MASK)
#define AIPS_PACRE_TP2_MASK                      (0x100000U)
#define AIPS_PACRE_TP2_SHIFT                     (20U)
#define AIPS_PACRE_TP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_TP2_SHIFT)) & AIPS_PACRE_TP2_MASK)
#define AIPS_PACRE_WP2_MASK                      (0x200000U)
#define AIPS_PACRE_WP2_SHIFT                     (21U)
#define AIPS_PACRE_WP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_WP2_SHIFT)) & AIPS_PACRE_WP2_MASK)
#define AIPS_PACRE_SP2_MASK                      (0x400000U)
#define AIPS_PACRE_SP2_SHIFT                     (22U)
#define AIPS_PACRE_SP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_SP2_SHIFT)) & AIPS_PACRE_SP2_MASK)
#define AIPS_PACRE_TP1_MASK                      (0x1000000U)
#define AIPS_PACRE_TP1_SHIFT                     (24U)
#define AIPS_PACRE_TP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_TP1_SHIFT)) & AIPS_PACRE_TP1_MASK)
#define AIPS_PACRE_WP1_MASK                      (0x2000000U)
#define AIPS_PACRE_WP1_SHIFT                     (25U)
#define AIPS_PACRE_WP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_WP1_SHIFT)) & AIPS_PACRE_WP1_MASK)
#define AIPS_PACRE_SP1_MASK                      (0x4000000U)
#define AIPS_PACRE_SP1_SHIFT                     (26U)
#define AIPS_PACRE_SP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_SP1_SHIFT)) & AIPS_PACRE_SP1_MASK)
#define AIPS_PACRE_TP0_MASK                      (0x10000000U)
#define AIPS_PACRE_TP0_SHIFT                     (28U)
#define AIPS_PACRE_TP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_TP0_SHIFT)) & AIPS_PACRE_TP0_MASK)
#define AIPS_PACRE_WP0_MASK                      (0x20000000U)
#define AIPS_PACRE_WP0_SHIFT                     (29U)
#define AIPS_PACRE_WP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_WP0_SHIFT)) & AIPS_PACRE_WP0_MASK)
#define AIPS_PACRE_SP0_MASK                      (0x40000000U)
#define AIPS_PACRE_SP0_SHIFT                     (30U)
#define AIPS_PACRE_SP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_SP0_SHIFT)) & AIPS_PACRE_SP0_MASK)

/*! @name PACRF - Peripheral Access Control Register */
#define AIPS_PACRF_TP7_MASK                      (0x1U)
#define AIPS_PACRF_TP7_SHIFT                     (0U)
#define AIPS_PACRF_TP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_TP7_SHIFT)) & AIPS_PACRF_TP7_MASK)
#define AIPS_PACRF_WP7_MASK                      (0x2U)
#define AIPS_PACRF_WP7_SHIFT                     (1U)
#define AIPS_PACRF_WP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_WP7_SHIFT)) & AIPS_PACRF_WP7_MASK)
#define AIPS_PACRF_SP7_MASK                      (0x4U)
#define AIPS_PACRF_SP7_SHIFT                     (2U)
#define AIPS_PACRF_SP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_SP7_SHIFT)) & AIPS_PACRF_SP7_MASK)
#define AIPS_PACRF_TP6_MASK                      (0x10U)
#define AIPS_PACRF_TP6_SHIFT                     (4U)
#define AIPS_PACRF_TP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_TP6_SHIFT)) & AIPS_PACRF_TP6_MASK)
#define AIPS_PACRF_WP6_MASK                      (0x20U)
#define AIPS_PACRF_WP6_SHIFT                     (5U)
#define AIPS_PACRF_WP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_WP6_SHIFT)) & AIPS_PACRF_WP6_MASK)
#define AIPS_PACRF_SP6_MASK                      (0x40U)
#define AIPS_PACRF_SP6_SHIFT                     (6U)
#define AIPS_PACRF_SP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_SP6_SHIFT)) & AIPS_PACRF_SP6_MASK)
#define AIPS_PACRF_TP5_MASK                      (0x100U)
#define AIPS_PACRF_TP5_SHIFT                     (8U)
#define AIPS_PACRF_TP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_TP5_SHIFT)) & AIPS_PACRF_TP5_MASK)
#define AIPS_PACRF_WP5_MASK                      (0x200U)
#define AIPS_PACRF_WP5_SHIFT                     (9U)
#define AIPS_PACRF_WP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_WP5_SHIFT)) & AIPS_PACRF_WP5_MASK)
#define AIPS_PACRF_SP5_MASK                      (0x400U)
#define AIPS_PACRF_SP5_SHIFT                     (10U)
#define AIPS_PACRF_SP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_SP5_SHIFT)) & AIPS_PACRF_SP5_MASK)
#define AIPS_PACRF_TP4_MASK                      (0x1000U)
#define AIPS_PACRF_TP4_SHIFT                     (12U)
#define AIPS_PACRF_TP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_TP4_SHIFT)) & AIPS_PACRF_TP4_MASK)
#define AIPS_PACRF_WP4_MASK                      (0x2000U)
#define AIPS_PACRF_WP4_SHIFT                     (13U)
#define AIPS_PACRF_WP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_WP4_SHIFT)) & AIPS_PACRF_WP4_MASK)
#define AIPS_PACRF_SP4_MASK                      (0x4000U)
#define AIPS_PACRF_SP4_SHIFT                     (14U)
#define AIPS_PACRF_SP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_SP4_SHIFT)) & AIPS_PACRF_SP4_MASK)
#define AIPS_PACRF_TP3_MASK                      (0x10000U)
#define AIPS_PACRF_TP3_SHIFT                     (16U)
#define AIPS_PACRF_TP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_TP3_SHIFT)) & AIPS_PACRF_TP3_MASK)
#define AIPS_PACRF_WP3_MASK                      (0x20000U)
#define AIPS_PACRF_WP3_SHIFT                     (17U)
#define AIPS_PACRF_WP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_WP3_SHIFT)) & AIPS_PACRF_WP3_MASK)
#define AIPS_PACRF_SP3_MASK                      (0x40000U)
#define AIPS_PACRF_SP3_SHIFT                     (18U)
#define AIPS_PACRF_SP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_SP3_SHIFT)) & AIPS_PACRF_SP3_MASK)
#define AIPS_PACRF_TP2_MASK                      (0x100000U)
#define AIPS_PACRF_TP2_SHIFT                     (20U)
#define AIPS_PACRF_TP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_TP2_SHIFT)) & AIPS_PACRF_TP2_MASK)
#define AIPS_PACRF_WP2_MASK                      (0x200000U)
#define AIPS_PACRF_WP2_SHIFT                     (21U)
#define AIPS_PACRF_WP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_WP2_SHIFT)) & AIPS_PACRF_WP2_MASK)
#define AIPS_PACRF_SP2_MASK                      (0x400000U)
#define AIPS_PACRF_SP2_SHIFT                     (22U)
#define AIPS_PACRF_SP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_SP2_SHIFT)) & AIPS_PACRF_SP2_MASK)
#define AIPS_PACRF_TP1_MASK                      (0x1000000U)
#define AIPS_PACRF_TP1_SHIFT                     (24U)
#define AIPS_PACRF_TP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_TP1_SHIFT)) & AIPS_PACRF_TP1_MASK)
#define AIPS_PACRF_WP1_MASK                      (0x2000000U)
#define AIPS_PACRF_WP1_SHIFT                     (25U)
#define AIPS_PACRF_WP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_WP1_SHIFT)) & AIPS_PACRF_WP1_MASK)
#define AIPS_PACRF_SP1_MASK                      (0x4000000U)
#define AIPS_PACRF_SP1_SHIFT                     (26U)
#define AIPS_PACRF_SP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_SP1_SHIFT)) & AIPS_PACRF_SP1_MASK)
#define AIPS_PACRF_TP0_MASK                      (0x10000000U)
#define AIPS_PACRF_TP0_SHIFT                     (28U)
#define AIPS_PACRF_TP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_TP0_SHIFT)) & AIPS_PACRF_TP0_MASK)
#define AIPS_PACRF_WP0_MASK                      (0x20000000U)
#define AIPS_PACRF_WP0_SHIFT                     (29U)
#define AIPS_PACRF_WP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_WP0_SHIFT)) & AIPS_PACRF_WP0_MASK)
#define AIPS_PACRF_SP0_MASK                      (0x40000000U)
#define AIPS_PACRF_SP0_SHIFT                     (30U)
#define AIPS_PACRF_SP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_SP0_SHIFT)) & AIPS_PACRF_SP0_MASK)

/*! @name PACRG - Peripheral Access Control Register */
#define AIPS_PACRG_TP7_MASK                      (0x1U)
#define AIPS_PACRG_TP7_SHIFT                     (0U)
#define AIPS_PACRG_TP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_TP7_SHIFT)) & AIPS_PACRG_TP7_MASK)
#define AIPS_PACRG_WP7_MASK                      (0x2U)
#define AIPS_PACRG_WP7_SHIFT                     (1U)
#define AIPS_PACRG_WP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_WP7_SHIFT)) & AIPS_PACRG_WP7_MASK)
#define AIPS_PACRG_SP7_MASK                      (0x4U)
#define AIPS_PACRG_SP7_SHIFT                     (2U)
#define AIPS_PACRG_SP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_SP7_SHIFT)) & AIPS_PACRG_SP7_MASK)
#define AIPS_PACRG_TP6_MASK                      (0x10U)
#define AIPS_PACRG_TP6_SHIFT                     (4U)
#define AIPS_PACRG_TP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_TP6_SHIFT)) & AIPS_PACRG_TP6_MASK)
#define AIPS_PACRG_WP6_MASK                      (0x20U)
#define AIPS_PACRG_WP6_SHIFT                     (5U)
#define AIPS_PACRG_WP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_WP6_SHIFT)) & AIPS_PACRG_WP6_MASK)
#define AIPS_PACRG_SP6_MASK                      (0x40U)
#define AIPS_PACRG_SP6_SHIFT                     (6U)
#define AIPS_PACRG_SP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_SP6_SHIFT)) & AIPS_PACRG_SP6_MASK)
#define AIPS_PACRG_TP5_MASK                      (0x100U)
#define AIPS_PACRG_TP5_SHIFT                     (8U)
#define AIPS_PACRG_TP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_TP5_SHIFT)) & AIPS_PACRG_TP5_MASK)
#define AIPS_PACRG_WP5_MASK                      (0x200U)
#define AIPS_PACRG_WP5_SHIFT                     (9U)
#define AIPS_PACRG_WP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_WP5_SHIFT)) & AIPS_PACRG_WP5_MASK)
#define AIPS_PACRG_SP5_MASK                      (0x400U)
#define AIPS_PACRG_SP5_SHIFT                     (10U)
#define AIPS_PACRG_SP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_SP5_SHIFT)) & AIPS_PACRG_SP5_MASK)
#define AIPS_PACRG_TP4_MASK                      (0x1000U)
#define AIPS_PACRG_TP4_SHIFT                     (12U)
#define AIPS_PACRG_TP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_TP4_SHIFT)) & AIPS_PACRG_TP4_MASK)
#define AIPS_PACRG_WP4_MASK                      (0x2000U)
#define AIPS_PACRG_WP4_SHIFT                     (13U)
#define AIPS_PACRG_WP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_WP4_SHIFT)) & AIPS_PACRG_WP4_MASK)
#define AIPS_PACRG_SP4_MASK                      (0x4000U)
#define AIPS_PACRG_SP4_SHIFT                     (14U)
#define AIPS_PACRG_SP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_SP4_SHIFT)) & AIPS_PACRG_SP4_MASK)
#define AIPS_PACRG_TP3_MASK                      (0x10000U)
#define AIPS_PACRG_TP3_SHIFT                     (16U)
#define AIPS_PACRG_TP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_TP3_SHIFT)) & AIPS_PACRG_TP3_MASK)
#define AIPS_PACRG_WP3_MASK                      (0x20000U)
#define AIPS_PACRG_WP3_SHIFT                     (17U)
#define AIPS_PACRG_WP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_WP3_SHIFT)) & AIPS_PACRG_WP3_MASK)
#define AIPS_PACRG_SP3_MASK                      (0x40000U)
#define AIPS_PACRG_SP3_SHIFT                     (18U)
#define AIPS_PACRG_SP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_SP3_SHIFT)) & AIPS_PACRG_SP3_MASK)
#define AIPS_PACRG_TP2_MASK                      (0x100000U)
#define AIPS_PACRG_TP2_SHIFT                     (20U)
#define AIPS_PACRG_TP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_TP2_SHIFT)) & AIPS_PACRG_TP2_MASK)
#define AIPS_PACRG_WP2_MASK                      (0x200000U)
#define AIPS_PACRG_WP2_SHIFT                     (21U)
#define AIPS_PACRG_WP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_WP2_SHIFT)) & AIPS_PACRG_WP2_MASK)
#define AIPS_PACRG_SP2_MASK                      (0x400000U)
#define AIPS_PACRG_SP2_SHIFT                     (22U)
#define AIPS_PACRG_SP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_SP2_SHIFT)) & AIPS_PACRG_SP2_MASK)
#define AIPS_PACRG_TP1_MASK                      (0x1000000U)
#define AIPS_PACRG_TP1_SHIFT                     (24U)
#define AIPS_PACRG_TP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_TP1_SHIFT)) & AIPS_PACRG_TP1_MASK)
#define AIPS_PACRG_WP1_MASK                      (0x2000000U)
#define AIPS_PACRG_WP1_SHIFT                     (25U)
#define AIPS_PACRG_WP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_WP1_SHIFT)) & AIPS_PACRG_WP1_MASK)
#define AIPS_PACRG_SP1_MASK                      (0x4000000U)
#define AIPS_PACRG_SP1_SHIFT                     (26U)
#define AIPS_PACRG_SP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_SP1_SHIFT)) & AIPS_PACRG_SP1_MASK)
#define AIPS_PACRG_TP0_MASK                      (0x10000000U)
#define AIPS_PACRG_TP0_SHIFT                     (28U)
#define AIPS_PACRG_TP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_TP0_SHIFT)) & AIPS_PACRG_TP0_MASK)
#define AIPS_PACRG_WP0_MASK                      (0x20000000U)
#define AIPS_PACRG_WP0_SHIFT                     (29U)
#define AIPS_PACRG_WP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_WP0_SHIFT)) & AIPS_PACRG_WP0_MASK)
#define AIPS_PACRG_SP0_MASK                      (0x40000000U)
#define AIPS_PACRG_SP0_SHIFT                     (30U)
#define AIPS_PACRG_SP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_SP0_SHIFT)) & AIPS_PACRG_SP0_MASK)

/*! @name PACRH - Peripheral Access Control Register */
#define AIPS_PACRH_TP7_MASK                      (0x1U)
#define AIPS_PACRH_TP7_SHIFT                     (0U)
#define AIPS_PACRH_TP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_TP7_SHIFT)) & AIPS_PACRH_TP7_MASK)
#define AIPS_PACRH_WP7_MASK                      (0x2U)
#define AIPS_PACRH_WP7_SHIFT                     (1U)
#define AIPS_PACRH_WP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_WP7_SHIFT)) & AIPS_PACRH_WP7_MASK)
#define AIPS_PACRH_SP7_MASK                      (0x4U)
#define AIPS_PACRH_SP7_SHIFT                     (2U)
#define AIPS_PACRH_SP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_SP7_SHIFT)) & AIPS_PACRH_SP7_MASK)
#define AIPS_PACRH_TP6_MASK                      (0x10U)
#define AIPS_PACRH_TP6_SHIFT                     (4U)
#define AIPS_PACRH_TP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_TP6_SHIFT)) & AIPS_PACRH_TP6_MASK)
#define AIPS_PACRH_WP6_MASK                      (0x20U)
#define AIPS_PACRH_WP6_SHIFT                     (5U)
#define AIPS_PACRH_WP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_WP6_SHIFT)) & AIPS_PACRH_WP6_MASK)
#define AIPS_PACRH_SP6_MASK                      (0x40U)
#define AIPS_PACRH_SP6_SHIFT                     (6U)
#define AIPS_PACRH_SP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_SP6_SHIFT)) & AIPS_PACRH_SP6_MASK)
#define AIPS_PACRH_TP5_MASK                      (0x100U)
#define AIPS_PACRH_TP5_SHIFT                     (8U)
#define AIPS_PACRH_TP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_TP5_SHIFT)) & AIPS_PACRH_TP5_MASK)
#define AIPS_PACRH_WP5_MASK                      (0x200U)
#define AIPS_PACRH_WP5_SHIFT                     (9U)
#define AIPS_PACRH_WP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_WP5_SHIFT)) & AIPS_PACRH_WP5_MASK)
#define AIPS_PACRH_SP5_MASK                      (0x400U)
#define AIPS_PACRH_SP5_SHIFT                     (10U)
#define AIPS_PACRH_SP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_SP5_SHIFT)) & AIPS_PACRH_SP5_MASK)
#define AIPS_PACRH_TP4_MASK                      (0x1000U)
#define AIPS_PACRH_TP4_SHIFT                     (12U)
#define AIPS_PACRH_TP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_TP4_SHIFT)) & AIPS_PACRH_TP4_MASK)
#define AIPS_PACRH_WP4_MASK                      (0x2000U)
#define AIPS_PACRH_WP4_SHIFT                     (13U)
#define AIPS_PACRH_WP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_WP4_SHIFT)) & AIPS_PACRH_WP4_MASK)
#define AIPS_PACRH_SP4_MASK                      (0x4000U)
#define AIPS_PACRH_SP4_SHIFT                     (14U)
#define AIPS_PACRH_SP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_SP4_SHIFT)) & AIPS_PACRH_SP4_MASK)
#define AIPS_PACRH_TP3_MASK                      (0x10000U)
#define AIPS_PACRH_TP3_SHIFT                     (16U)
#define AIPS_PACRH_TP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_TP3_SHIFT)) & AIPS_PACRH_TP3_MASK)
#define AIPS_PACRH_WP3_MASK                      (0x20000U)
#define AIPS_PACRH_WP3_SHIFT                     (17U)
#define AIPS_PACRH_WP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_WP3_SHIFT)) & AIPS_PACRH_WP3_MASK)
#define AIPS_PACRH_SP3_MASK                      (0x40000U)
#define AIPS_PACRH_SP3_SHIFT                     (18U)
#define AIPS_PACRH_SP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_SP3_SHIFT)) & AIPS_PACRH_SP3_MASK)
#define AIPS_PACRH_TP2_MASK                      (0x100000U)
#define AIPS_PACRH_TP2_SHIFT                     (20U)
#define AIPS_PACRH_TP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_TP2_SHIFT)) & AIPS_PACRH_TP2_MASK)
#define AIPS_PACRH_WP2_MASK                      (0x200000U)
#define AIPS_PACRH_WP2_SHIFT                     (21U)
#define AIPS_PACRH_WP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_WP2_SHIFT)) & AIPS_PACRH_WP2_MASK)
#define AIPS_PACRH_SP2_MASK                      (0x400000U)
#define AIPS_PACRH_SP2_SHIFT                     (22U)
#define AIPS_PACRH_SP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_SP2_SHIFT)) & AIPS_PACRH_SP2_MASK)
#define AIPS_PACRH_TP1_MASK                      (0x1000000U)
#define AIPS_PACRH_TP1_SHIFT                     (24U)
#define AIPS_PACRH_TP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_TP1_SHIFT)) & AIPS_PACRH_TP1_MASK)
#define AIPS_PACRH_WP1_MASK                      (0x2000000U)
#define AIPS_PACRH_WP1_SHIFT                     (25U)
#define AIPS_PACRH_WP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_WP1_SHIFT)) & AIPS_PACRH_WP1_MASK)
#define AIPS_PACRH_SP1_MASK                      (0x4000000U)
#define AIPS_PACRH_SP1_SHIFT                     (26U)
#define AIPS_PACRH_SP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_SP1_SHIFT)) & AIPS_PACRH_SP1_MASK)
#define AIPS_PACRH_TP0_MASK                      (0x10000000U)
#define AIPS_PACRH_TP0_SHIFT                     (28U)
#define AIPS_PACRH_TP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_TP0_SHIFT)) & AIPS_PACRH_TP0_MASK)
#define AIPS_PACRH_WP0_MASK                      (0x20000000U)
#define AIPS_PACRH_WP0_SHIFT                     (29U)
#define AIPS_PACRH_WP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_WP0_SHIFT)) & AIPS_PACRH_WP0_MASK)
#define AIPS_PACRH_SP0_MASK                      (0x40000000U)
#define AIPS_PACRH_SP0_SHIFT                     (30U)
#define AIPS_PACRH_SP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_SP0_SHIFT)) & AIPS_PACRH_SP0_MASK)

/*! @name PACRI - Peripheral Access Control Register */
#define AIPS_PACRI_TP7_MASK                      (0x1U)
#define AIPS_PACRI_TP7_SHIFT                     (0U)
#define AIPS_PACRI_TP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_TP7_SHIFT)) & AIPS_PACRI_TP7_MASK)
#define AIPS_PACRI_WP7_MASK                      (0x2U)
#define AIPS_PACRI_WP7_SHIFT                     (1U)
#define AIPS_PACRI_WP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_WP7_SHIFT)) & AIPS_PACRI_WP7_MASK)
#define AIPS_PACRI_SP7_MASK                      (0x4U)
#define AIPS_PACRI_SP7_SHIFT                     (2U)
#define AIPS_PACRI_SP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_SP7_SHIFT)) & AIPS_PACRI_SP7_MASK)
#define AIPS_PACRI_TP6_MASK                      (0x10U)
#define AIPS_PACRI_TP6_SHIFT                     (4U)
#define AIPS_PACRI_TP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_TP6_SHIFT)) & AIPS_PACRI_TP6_MASK)
#define AIPS_PACRI_WP6_MASK                      (0x20U)
#define AIPS_PACRI_WP6_SHIFT                     (5U)
#define AIPS_PACRI_WP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_WP6_SHIFT)) & AIPS_PACRI_WP6_MASK)
#define AIPS_PACRI_SP6_MASK                      (0x40U)
#define AIPS_PACRI_SP6_SHIFT                     (6U)
#define AIPS_PACRI_SP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_SP6_SHIFT)) & AIPS_PACRI_SP6_MASK)
#define AIPS_PACRI_TP5_MASK                      (0x100U)
#define AIPS_PACRI_TP5_SHIFT                     (8U)
#define AIPS_PACRI_TP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_TP5_SHIFT)) & AIPS_PACRI_TP5_MASK)
#define AIPS_PACRI_WP5_MASK                      (0x200U)
#define AIPS_PACRI_WP5_SHIFT                     (9U)
#define AIPS_PACRI_WP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_WP5_SHIFT)) & AIPS_PACRI_WP5_MASK)
#define AIPS_PACRI_SP5_MASK                      (0x400U)
#define AIPS_PACRI_SP5_SHIFT                     (10U)
#define AIPS_PACRI_SP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_SP5_SHIFT)) & AIPS_PACRI_SP5_MASK)
#define AIPS_PACRI_TP4_MASK                      (0x1000U)
#define AIPS_PACRI_TP4_SHIFT                     (12U)
#define AIPS_PACRI_TP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_TP4_SHIFT)) & AIPS_PACRI_TP4_MASK)
#define AIPS_PACRI_WP4_MASK                      (0x2000U)
#define AIPS_PACRI_WP4_SHIFT                     (13U)
#define AIPS_PACRI_WP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_WP4_SHIFT)) & AIPS_PACRI_WP4_MASK)
#define AIPS_PACRI_SP4_MASK                      (0x4000U)
#define AIPS_PACRI_SP4_SHIFT                     (14U)
#define AIPS_PACRI_SP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_SP4_SHIFT)) & AIPS_PACRI_SP4_MASK)
#define AIPS_PACRI_TP3_MASK                      (0x10000U)
#define AIPS_PACRI_TP3_SHIFT                     (16U)
#define AIPS_PACRI_TP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_TP3_SHIFT)) & AIPS_PACRI_TP3_MASK)
#define AIPS_PACRI_WP3_MASK                      (0x20000U)
#define AIPS_PACRI_WP3_SHIFT                     (17U)
#define AIPS_PACRI_WP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_WP3_SHIFT)) & AIPS_PACRI_WP3_MASK)
#define AIPS_PACRI_SP3_MASK                      (0x40000U)
#define AIPS_PACRI_SP3_SHIFT                     (18U)
#define AIPS_PACRI_SP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_SP3_SHIFT)) & AIPS_PACRI_SP3_MASK)
#define AIPS_PACRI_TP2_MASK                      (0x100000U)
#define AIPS_PACRI_TP2_SHIFT                     (20U)
#define AIPS_PACRI_TP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_TP2_SHIFT)) & AIPS_PACRI_TP2_MASK)
#define AIPS_PACRI_WP2_MASK                      (0x200000U)
#define AIPS_PACRI_WP2_SHIFT                     (21U)
#define AIPS_PACRI_WP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_WP2_SHIFT)) & AIPS_PACRI_WP2_MASK)
#define AIPS_PACRI_SP2_MASK                      (0x400000U)
#define AIPS_PACRI_SP2_SHIFT                     (22U)
#define AIPS_PACRI_SP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_SP2_SHIFT)) & AIPS_PACRI_SP2_MASK)
#define AIPS_PACRI_TP1_MASK                      (0x1000000U)
#define AIPS_PACRI_TP1_SHIFT                     (24U)
#define AIPS_PACRI_TP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_TP1_SHIFT)) & AIPS_PACRI_TP1_MASK)
#define AIPS_PACRI_WP1_MASK                      (0x2000000U)
#define AIPS_PACRI_WP1_SHIFT                     (25U)
#define AIPS_PACRI_WP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_WP1_SHIFT)) & AIPS_PACRI_WP1_MASK)
#define AIPS_PACRI_SP1_MASK                      (0x4000000U)
#define AIPS_PACRI_SP1_SHIFT                     (26U)
#define AIPS_PACRI_SP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_SP1_SHIFT)) & AIPS_PACRI_SP1_MASK)
#define AIPS_PACRI_TP0_MASK                      (0x10000000U)
#define AIPS_PACRI_TP0_SHIFT                     (28U)
#define AIPS_PACRI_TP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_TP0_SHIFT)) & AIPS_PACRI_TP0_MASK)
#define AIPS_PACRI_WP0_MASK                      (0x20000000U)
#define AIPS_PACRI_WP0_SHIFT                     (29U)
#define AIPS_PACRI_WP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_WP0_SHIFT)) & AIPS_PACRI_WP0_MASK)
#define AIPS_PACRI_SP0_MASK                      (0x40000000U)
#define AIPS_PACRI_SP0_SHIFT                     (30U)
#define AIPS_PACRI_SP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_SP0_SHIFT)) & AIPS_PACRI_SP0_MASK)

/*! @name PACRJ - Peripheral Access Control Register */
#define AIPS_PACRJ_TP7_MASK                      (0x1U)
#define AIPS_PACRJ_TP7_SHIFT                     (0U)
#define AIPS_PACRJ_TP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_TP7_SHIFT)) & AIPS_PACRJ_TP7_MASK)
#define AIPS_PACRJ_WP7_MASK                      (0x2U)
#define AIPS_PACRJ_WP7_SHIFT                     (1U)
#define AIPS_PACRJ_WP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_WP7_SHIFT)) & AIPS_PACRJ_WP7_MASK)
#define AIPS_PACRJ_SP7_MASK                      (0x4U)
#define AIPS_PACRJ_SP7_SHIFT                     (2U)
#define AIPS_PACRJ_SP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_SP7_SHIFT)) & AIPS_PACRJ_SP7_MASK)
#define AIPS_PACRJ_TP6_MASK                      (0x10U)
#define AIPS_PACRJ_TP6_SHIFT                     (4U)
#define AIPS_PACRJ_TP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_TP6_SHIFT)) & AIPS_PACRJ_TP6_MASK)
#define AIPS_PACRJ_WP6_MASK                      (0x20U)
#define AIPS_PACRJ_WP6_SHIFT                     (5U)
#define AIPS_PACRJ_WP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_WP6_SHIFT)) & AIPS_PACRJ_WP6_MASK)
#define AIPS_PACRJ_SP6_MASK                      (0x40U)
#define AIPS_PACRJ_SP6_SHIFT                     (6U)
#define AIPS_PACRJ_SP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_SP6_SHIFT)) & AIPS_PACRJ_SP6_MASK)
#define AIPS_PACRJ_TP5_MASK                      (0x100U)
#define AIPS_PACRJ_TP5_SHIFT                     (8U)
#define AIPS_PACRJ_TP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_TP5_SHIFT)) & AIPS_PACRJ_TP5_MASK)
#define AIPS_PACRJ_WP5_MASK                      (0x200U)
#define AIPS_PACRJ_WP5_SHIFT                     (9U)
#define AIPS_PACRJ_WP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_WP5_SHIFT)) & AIPS_PACRJ_WP5_MASK)
#define AIPS_PACRJ_SP5_MASK                      (0x400U)
#define AIPS_PACRJ_SP5_SHIFT                     (10U)
#define AIPS_PACRJ_SP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_SP5_SHIFT)) & AIPS_PACRJ_SP5_MASK)
#define AIPS_PACRJ_TP4_MASK                      (0x1000U)
#define AIPS_PACRJ_TP4_SHIFT                     (12U)
#define AIPS_PACRJ_TP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_TP4_SHIFT)) & AIPS_PACRJ_TP4_MASK)
#define AIPS_PACRJ_WP4_MASK                      (0x2000U)
#define AIPS_PACRJ_WP4_SHIFT                     (13U)
#define AIPS_PACRJ_WP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_WP4_SHIFT)) & AIPS_PACRJ_WP4_MASK)
#define AIPS_PACRJ_SP4_MASK                      (0x4000U)
#define AIPS_PACRJ_SP4_SHIFT                     (14U)
#define AIPS_PACRJ_SP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_SP4_SHIFT)) & AIPS_PACRJ_SP4_MASK)
#define AIPS_PACRJ_TP3_MASK                      (0x10000U)
#define AIPS_PACRJ_TP3_SHIFT                     (16U)
#define AIPS_PACRJ_TP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_TP3_SHIFT)) & AIPS_PACRJ_TP3_MASK)
#define AIPS_PACRJ_WP3_MASK                      (0x20000U)
#define AIPS_PACRJ_WP3_SHIFT                     (17U)
#define AIPS_PACRJ_WP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_WP3_SHIFT)) & AIPS_PACRJ_WP3_MASK)
#define AIPS_PACRJ_SP3_MASK                      (0x40000U)
#define AIPS_PACRJ_SP3_SHIFT                     (18U)
#define AIPS_PACRJ_SP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_SP3_SHIFT)) & AIPS_PACRJ_SP3_MASK)
#define AIPS_PACRJ_TP2_MASK                      (0x100000U)
#define AIPS_PACRJ_TP2_SHIFT                     (20U)
#define AIPS_PACRJ_TP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_TP2_SHIFT)) & AIPS_PACRJ_TP2_MASK)
#define AIPS_PACRJ_WP2_MASK                      (0x200000U)
#define AIPS_PACRJ_WP2_SHIFT                     (21U)
#define AIPS_PACRJ_WP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_WP2_SHIFT)) & AIPS_PACRJ_WP2_MASK)
#define AIPS_PACRJ_SP2_MASK                      (0x400000U)
#define AIPS_PACRJ_SP2_SHIFT                     (22U)
#define AIPS_PACRJ_SP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_SP2_SHIFT)) & AIPS_PACRJ_SP2_MASK)
#define AIPS_PACRJ_TP1_MASK                      (0x1000000U)
#define AIPS_PACRJ_TP1_SHIFT                     (24U)
#define AIPS_PACRJ_TP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_TP1_SHIFT)) & AIPS_PACRJ_TP1_MASK)
#define AIPS_PACRJ_WP1_MASK                      (0x2000000U)
#define AIPS_PACRJ_WP1_SHIFT                     (25U)
#define AIPS_PACRJ_WP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_WP1_SHIFT)) & AIPS_PACRJ_WP1_MASK)
#define AIPS_PACRJ_SP1_MASK                      (0x4000000U)
#define AIPS_PACRJ_SP1_SHIFT                     (26U)
#define AIPS_PACRJ_SP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_SP1_SHIFT)) & AIPS_PACRJ_SP1_MASK)
#define AIPS_PACRJ_TP0_MASK                      (0x10000000U)
#define AIPS_PACRJ_TP0_SHIFT                     (28U)
#define AIPS_PACRJ_TP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_TP0_SHIFT)) & AIPS_PACRJ_TP0_MASK)
#define AIPS_PACRJ_WP0_MASK                      (0x20000000U)
#define AIPS_PACRJ_WP0_SHIFT                     (29U)
#define AIPS_PACRJ_WP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_WP0_SHIFT)) & AIPS_PACRJ_WP0_MASK)
#define AIPS_PACRJ_SP0_MASK                      (0x40000000U)
#define AIPS_PACRJ_SP0_SHIFT                     (30U)
#define AIPS_PACRJ_SP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_SP0_SHIFT)) & AIPS_PACRJ_SP0_MASK)

/*! @name PACRK - Peripheral Access Control Register */
#define AIPS_PACRK_TP7_MASK                      (0x1U)
#define AIPS_PACRK_TP7_SHIFT                     (0U)
#define AIPS_PACRK_TP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_TP7_SHIFT)) & AIPS_PACRK_TP7_MASK)
#define AIPS_PACRK_WP7_MASK                      (0x2U)
#define AIPS_PACRK_WP7_SHIFT                     (1U)
#define AIPS_PACRK_WP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_WP7_SHIFT)) & AIPS_PACRK_WP7_MASK)
#define AIPS_PACRK_SP7_MASK                      (0x4U)
#define AIPS_PACRK_SP7_SHIFT                     (2U)
#define AIPS_PACRK_SP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_SP7_SHIFT)) & AIPS_PACRK_SP7_MASK)
#define AIPS_PACRK_TP6_MASK                      (0x10U)
#define AIPS_PACRK_TP6_SHIFT                     (4U)
#define AIPS_PACRK_TP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_TP6_SHIFT)) & AIPS_PACRK_TP6_MASK)
#define AIPS_PACRK_WP6_MASK                      (0x20U)
#define AIPS_PACRK_WP6_SHIFT                     (5U)
#define AIPS_PACRK_WP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_WP6_SHIFT)) & AIPS_PACRK_WP6_MASK)
#define AIPS_PACRK_SP6_MASK                      (0x40U)
#define AIPS_PACRK_SP6_SHIFT                     (6U)
#define AIPS_PACRK_SP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_SP6_SHIFT)) & AIPS_PACRK_SP6_MASK)
#define AIPS_PACRK_TP5_MASK                      (0x100U)
#define AIPS_PACRK_TP5_SHIFT                     (8U)
#define AIPS_PACRK_TP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_TP5_SHIFT)) & AIPS_PACRK_TP5_MASK)
#define AIPS_PACRK_WP5_MASK                      (0x200U)
#define AIPS_PACRK_WP5_SHIFT                     (9U)
#define AIPS_PACRK_WP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_WP5_SHIFT)) & AIPS_PACRK_WP5_MASK)
#define AIPS_PACRK_SP5_MASK                      (0x400U)
#define AIPS_PACRK_SP5_SHIFT                     (10U)
#define AIPS_PACRK_SP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_SP5_SHIFT)) & AIPS_PACRK_SP5_MASK)
#define AIPS_PACRK_TP4_MASK                      (0x1000U)
#define AIPS_PACRK_TP4_SHIFT                     (12U)
#define AIPS_PACRK_TP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_TP4_SHIFT)) & AIPS_PACRK_TP4_MASK)
#define AIPS_PACRK_WP4_MASK                      (0x2000U)
#define AIPS_PACRK_WP4_SHIFT                     (13U)
#define AIPS_PACRK_WP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_WP4_SHIFT)) & AIPS_PACRK_WP4_MASK)
#define AIPS_PACRK_SP4_MASK                      (0x4000U)
#define AIPS_PACRK_SP4_SHIFT                     (14U)
#define AIPS_PACRK_SP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_SP4_SHIFT)) & AIPS_PACRK_SP4_MASK)
#define AIPS_PACRK_TP3_MASK                      (0x10000U)
#define AIPS_PACRK_TP3_SHIFT                     (16U)
#define AIPS_PACRK_TP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_TP3_SHIFT)) & AIPS_PACRK_TP3_MASK)
#define AIPS_PACRK_WP3_MASK                      (0x20000U)
#define AIPS_PACRK_WP3_SHIFT                     (17U)
#define AIPS_PACRK_WP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_WP3_SHIFT)) & AIPS_PACRK_WP3_MASK)
#define AIPS_PACRK_SP3_MASK                      (0x40000U)
#define AIPS_PACRK_SP3_SHIFT                     (18U)
#define AIPS_PACRK_SP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_SP3_SHIFT)) & AIPS_PACRK_SP3_MASK)
#define AIPS_PACRK_TP2_MASK                      (0x100000U)
#define AIPS_PACRK_TP2_SHIFT                     (20U)
#define AIPS_PACRK_TP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_TP2_SHIFT)) & AIPS_PACRK_TP2_MASK)
#define AIPS_PACRK_WP2_MASK                      (0x200000U)
#define AIPS_PACRK_WP2_SHIFT                     (21U)
#define AIPS_PACRK_WP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_WP2_SHIFT)) & AIPS_PACRK_WP2_MASK)
#define AIPS_PACRK_SP2_MASK                      (0x400000U)
#define AIPS_PACRK_SP2_SHIFT                     (22U)
#define AIPS_PACRK_SP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_SP2_SHIFT)) & AIPS_PACRK_SP2_MASK)
#define AIPS_PACRK_TP1_MASK                      (0x1000000U)
#define AIPS_PACRK_TP1_SHIFT                     (24U)
#define AIPS_PACRK_TP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_TP1_SHIFT)) & AIPS_PACRK_TP1_MASK)
#define AIPS_PACRK_WP1_MASK                      (0x2000000U)
#define AIPS_PACRK_WP1_SHIFT                     (25U)
#define AIPS_PACRK_WP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_WP1_SHIFT)) & AIPS_PACRK_WP1_MASK)
#define AIPS_PACRK_SP1_MASK                      (0x4000000U)
#define AIPS_PACRK_SP1_SHIFT                     (26U)
#define AIPS_PACRK_SP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_SP1_SHIFT)) & AIPS_PACRK_SP1_MASK)
#define AIPS_PACRK_TP0_MASK                      (0x10000000U)
#define AIPS_PACRK_TP0_SHIFT                     (28U)
#define AIPS_PACRK_TP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_TP0_SHIFT)) & AIPS_PACRK_TP0_MASK)
#define AIPS_PACRK_WP0_MASK                      (0x20000000U)
#define AIPS_PACRK_WP0_SHIFT                     (29U)
#define AIPS_PACRK_WP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_WP0_SHIFT)) & AIPS_PACRK_WP0_MASK)
#define AIPS_PACRK_SP0_MASK                      (0x40000000U)
#define AIPS_PACRK_SP0_SHIFT                     (30U)
#define AIPS_PACRK_SP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_SP0_SHIFT)) & AIPS_PACRK_SP0_MASK)

/*! @name PACRL - Peripheral Access Control Register */
#define AIPS_PACRL_TP7_MASK                      (0x1U)
#define AIPS_PACRL_TP7_SHIFT                     (0U)
#define AIPS_PACRL_TP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_TP7_SHIFT)) & AIPS_PACRL_TP7_MASK)
#define AIPS_PACRL_WP7_MASK                      (0x2U)
#define AIPS_PACRL_WP7_SHIFT                     (1U)
#define AIPS_PACRL_WP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_WP7_SHIFT)) & AIPS_PACRL_WP7_MASK)
#define AIPS_PACRL_SP7_MASK                      (0x4U)
#define AIPS_PACRL_SP7_SHIFT                     (2U)
#define AIPS_PACRL_SP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_SP7_SHIFT)) & AIPS_PACRL_SP7_MASK)
#define AIPS_PACRL_TP6_MASK                      (0x10U)
#define AIPS_PACRL_TP6_SHIFT                     (4U)
#define AIPS_PACRL_TP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_TP6_SHIFT)) & AIPS_PACRL_TP6_MASK)
#define AIPS_PACRL_WP6_MASK                      (0x20U)
#define AIPS_PACRL_WP6_SHIFT                     (5U)
#define AIPS_PACRL_WP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_WP6_SHIFT)) & AIPS_PACRL_WP6_MASK)
#define AIPS_PACRL_SP6_MASK                      (0x40U)
#define AIPS_PACRL_SP6_SHIFT                     (6U)
#define AIPS_PACRL_SP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_SP6_SHIFT)) & AIPS_PACRL_SP6_MASK)
#define AIPS_PACRL_TP5_MASK                      (0x100U)
#define AIPS_PACRL_TP5_SHIFT                     (8U)
#define AIPS_PACRL_TP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_TP5_SHIFT)) & AIPS_PACRL_TP5_MASK)
#define AIPS_PACRL_WP5_MASK                      (0x200U)
#define AIPS_PACRL_WP5_SHIFT                     (9U)
#define AIPS_PACRL_WP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_WP5_SHIFT)) & AIPS_PACRL_WP5_MASK)
#define AIPS_PACRL_SP5_MASK                      (0x400U)
#define AIPS_PACRL_SP5_SHIFT                     (10U)
#define AIPS_PACRL_SP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_SP5_SHIFT)) & AIPS_PACRL_SP5_MASK)
#define AIPS_PACRL_TP4_MASK                      (0x1000U)
#define AIPS_PACRL_TP4_SHIFT                     (12U)
#define AIPS_PACRL_TP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_TP4_SHIFT)) & AIPS_PACRL_TP4_MASK)
#define AIPS_PACRL_WP4_MASK                      (0x2000U)
#define AIPS_PACRL_WP4_SHIFT                     (13U)
#define AIPS_PACRL_WP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_WP4_SHIFT)) & AIPS_PACRL_WP4_MASK)
#define AIPS_PACRL_SP4_MASK                      (0x4000U)
#define AIPS_PACRL_SP4_SHIFT                     (14U)
#define AIPS_PACRL_SP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_SP4_SHIFT)) & AIPS_PACRL_SP4_MASK)
#define AIPS_PACRL_TP3_MASK                      (0x10000U)
#define AIPS_PACRL_TP3_SHIFT                     (16U)
#define AIPS_PACRL_TP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_TP3_SHIFT)) & AIPS_PACRL_TP3_MASK)
#define AIPS_PACRL_WP3_MASK                      (0x20000U)
#define AIPS_PACRL_WP3_SHIFT                     (17U)
#define AIPS_PACRL_WP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_WP3_SHIFT)) & AIPS_PACRL_WP3_MASK)
#define AIPS_PACRL_SP3_MASK                      (0x40000U)
#define AIPS_PACRL_SP3_SHIFT                     (18U)
#define AIPS_PACRL_SP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_SP3_SHIFT)) & AIPS_PACRL_SP3_MASK)
#define AIPS_PACRL_TP2_MASK                      (0x100000U)
#define AIPS_PACRL_TP2_SHIFT                     (20U)
#define AIPS_PACRL_TP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_TP2_SHIFT)) & AIPS_PACRL_TP2_MASK)
#define AIPS_PACRL_WP2_MASK                      (0x200000U)
#define AIPS_PACRL_WP2_SHIFT                     (21U)
#define AIPS_PACRL_WP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_WP2_SHIFT)) & AIPS_PACRL_WP2_MASK)
#define AIPS_PACRL_SP2_MASK                      (0x400000U)
#define AIPS_PACRL_SP2_SHIFT                     (22U)
#define AIPS_PACRL_SP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_SP2_SHIFT)) & AIPS_PACRL_SP2_MASK)
#define AIPS_PACRL_TP1_MASK                      (0x1000000U)
#define AIPS_PACRL_TP1_SHIFT                     (24U)
#define AIPS_PACRL_TP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_TP1_SHIFT)) & AIPS_PACRL_TP1_MASK)
#define AIPS_PACRL_WP1_MASK                      (0x2000000U)
#define AIPS_PACRL_WP1_SHIFT                     (25U)
#define AIPS_PACRL_WP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_WP1_SHIFT)) & AIPS_PACRL_WP1_MASK)
#define AIPS_PACRL_SP1_MASK                      (0x4000000U)
#define AIPS_PACRL_SP1_SHIFT                     (26U)
#define AIPS_PACRL_SP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_SP1_SHIFT)) & AIPS_PACRL_SP1_MASK)
#define AIPS_PACRL_TP0_MASK                      (0x10000000U)
#define AIPS_PACRL_TP0_SHIFT                     (28U)
#define AIPS_PACRL_TP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_TP0_SHIFT)) & AIPS_PACRL_TP0_MASK)
#define AIPS_PACRL_WP0_MASK                      (0x20000000U)
#define AIPS_PACRL_WP0_SHIFT                     (29U)
#define AIPS_PACRL_WP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_WP0_SHIFT)) & AIPS_PACRL_WP0_MASK)
#define AIPS_PACRL_SP0_MASK                      (0x40000000U)
#define AIPS_PACRL_SP0_SHIFT                     (30U)
#define AIPS_PACRL_SP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_SP0_SHIFT)) & AIPS_PACRL_SP0_MASK)

/*! @name PACRM - Peripheral Access Control Register */
#define AIPS_PACRM_TP7_MASK                      (0x1U)
#define AIPS_PACRM_TP7_SHIFT                     (0U)
#define AIPS_PACRM_TP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_TP7_SHIFT)) & AIPS_PACRM_TP7_MASK)
#define AIPS_PACRM_WP7_MASK                      (0x2U)
#define AIPS_PACRM_WP7_SHIFT                     (1U)
#define AIPS_PACRM_WP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_WP7_SHIFT)) & AIPS_PACRM_WP7_MASK)
#define AIPS_PACRM_SP7_MASK                      (0x4U)
#define AIPS_PACRM_SP7_SHIFT                     (2U)
#define AIPS_PACRM_SP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_SP7_SHIFT)) & AIPS_PACRM_SP7_MASK)
#define AIPS_PACRM_TP6_MASK                      (0x10U)
#define AIPS_PACRM_TP6_SHIFT                     (4U)
#define AIPS_PACRM_TP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_TP6_SHIFT)) & AIPS_PACRM_TP6_MASK)
#define AIPS_PACRM_WP6_MASK                      (0x20U)
#define AIPS_PACRM_WP6_SHIFT                     (5U)
#define AIPS_PACRM_WP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_WP6_SHIFT)) & AIPS_PACRM_WP6_MASK)
#define AIPS_PACRM_SP6_MASK                      (0x40U)
#define AIPS_PACRM_SP6_SHIFT                     (6U)
#define AIPS_PACRM_SP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_SP6_SHIFT)) & AIPS_PACRM_SP6_MASK)
#define AIPS_PACRM_TP5_MASK                      (0x100U)
#define AIPS_PACRM_TP5_SHIFT                     (8U)
#define AIPS_PACRM_TP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_TP5_SHIFT)) & AIPS_PACRM_TP5_MASK)
#define AIPS_PACRM_WP5_MASK                      (0x200U)
#define AIPS_PACRM_WP5_SHIFT                     (9U)
#define AIPS_PACRM_WP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_WP5_SHIFT)) & AIPS_PACRM_WP5_MASK)
#define AIPS_PACRM_SP5_MASK                      (0x400U)
#define AIPS_PACRM_SP5_SHIFT                     (10U)
#define AIPS_PACRM_SP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_SP5_SHIFT)) & AIPS_PACRM_SP5_MASK)
#define AIPS_PACRM_TP4_MASK                      (0x1000U)
#define AIPS_PACRM_TP4_SHIFT                     (12U)
#define AIPS_PACRM_TP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_TP4_SHIFT)) & AIPS_PACRM_TP4_MASK)
#define AIPS_PACRM_WP4_MASK                      (0x2000U)
#define AIPS_PACRM_WP4_SHIFT                     (13U)
#define AIPS_PACRM_WP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_WP4_SHIFT)) & AIPS_PACRM_WP4_MASK)
#define AIPS_PACRM_SP4_MASK                      (0x4000U)
#define AIPS_PACRM_SP4_SHIFT                     (14U)
#define AIPS_PACRM_SP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_SP4_SHIFT)) & AIPS_PACRM_SP4_MASK)
#define AIPS_PACRM_TP3_MASK                      (0x10000U)
#define AIPS_PACRM_TP3_SHIFT                     (16U)
#define AIPS_PACRM_TP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_TP3_SHIFT)) & AIPS_PACRM_TP3_MASK)
#define AIPS_PACRM_WP3_MASK                      (0x20000U)
#define AIPS_PACRM_WP3_SHIFT                     (17U)
#define AIPS_PACRM_WP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_WP3_SHIFT)) & AIPS_PACRM_WP3_MASK)
#define AIPS_PACRM_SP3_MASK                      (0x40000U)
#define AIPS_PACRM_SP3_SHIFT                     (18U)
#define AIPS_PACRM_SP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_SP3_SHIFT)) & AIPS_PACRM_SP3_MASK)
#define AIPS_PACRM_TP2_MASK                      (0x100000U)
#define AIPS_PACRM_TP2_SHIFT                     (20U)
#define AIPS_PACRM_TP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_TP2_SHIFT)) & AIPS_PACRM_TP2_MASK)
#define AIPS_PACRM_WP2_MASK                      (0x200000U)
#define AIPS_PACRM_WP2_SHIFT                     (21U)
#define AIPS_PACRM_WP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_WP2_SHIFT)) & AIPS_PACRM_WP2_MASK)
#define AIPS_PACRM_SP2_MASK                      (0x400000U)
#define AIPS_PACRM_SP2_SHIFT                     (22U)
#define AIPS_PACRM_SP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_SP2_SHIFT)) & AIPS_PACRM_SP2_MASK)
#define AIPS_PACRM_TP1_MASK                      (0x1000000U)
#define AIPS_PACRM_TP1_SHIFT                     (24U)
#define AIPS_PACRM_TP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_TP1_SHIFT)) & AIPS_PACRM_TP1_MASK)
#define AIPS_PACRM_WP1_MASK                      (0x2000000U)
#define AIPS_PACRM_WP1_SHIFT                     (25U)
#define AIPS_PACRM_WP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_WP1_SHIFT)) & AIPS_PACRM_WP1_MASK)
#define AIPS_PACRM_SP1_MASK                      (0x4000000U)
#define AIPS_PACRM_SP1_SHIFT                     (26U)
#define AIPS_PACRM_SP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_SP1_SHIFT)) & AIPS_PACRM_SP1_MASK)
#define AIPS_PACRM_TP0_MASK                      (0x10000000U)
#define AIPS_PACRM_TP0_SHIFT                     (28U)
#define AIPS_PACRM_TP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_TP0_SHIFT)) & AIPS_PACRM_TP0_MASK)
#define AIPS_PACRM_WP0_MASK                      (0x20000000U)
#define AIPS_PACRM_WP0_SHIFT                     (29U)
#define AIPS_PACRM_WP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_WP0_SHIFT)) & AIPS_PACRM_WP0_MASK)
#define AIPS_PACRM_SP0_MASK                      (0x40000000U)
#define AIPS_PACRM_SP0_SHIFT                     (30U)
#define AIPS_PACRM_SP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_SP0_SHIFT)) & AIPS_PACRM_SP0_MASK)

/*! @name PACRN - Peripheral Access Control Register */
#define AIPS_PACRN_TP7_MASK                      (0x1U)
#define AIPS_PACRN_TP7_SHIFT                     (0U)
#define AIPS_PACRN_TP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_TP7_SHIFT)) & AIPS_PACRN_TP7_MASK)
#define AIPS_PACRN_WP7_MASK                      (0x2U)
#define AIPS_PACRN_WP7_SHIFT                     (1U)
#define AIPS_PACRN_WP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_WP7_SHIFT)) & AIPS_PACRN_WP7_MASK)
#define AIPS_PACRN_SP7_MASK                      (0x4U)
#define AIPS_PACRN_SP7_SHIFT                     (2U)
#define AIPS_PACRN_SP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_SP7_SHIFT)) & AIPS_PACRN_SP7_MASK)
#define AIPS_PACRN_TP6_MASK                      (0x10U)
#define AIPS_PACRN_TP6_SHIFT                     (4U)
#define AIPS_PACRN_TP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_TP6_SHIFT)) & AIPS_PACRN_TP6_MASK)
#define AIPS_PACRN_WP6_MASK                      (0x20U)
#define AIPS_PACRN_WP6_SHIFT                     (5U)
#define AIPS_PACRN_WP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_WP6_SHIFT)) & AIPS_PACRN_WP6_MASK)
#define AIPS_PACRN_SP6_MASK                      (0x40U)
#define AIPS_PACRN_SP6_SHIFT                     (6U)
#define AIPS_PACRN_SP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_SP6_SHIFT)) & AIPS_PACRN_SP6_MASK)
#define AIPS_PACRN_TP5_MASK                      (0x100U)
#define AIPS_PACRN_TP5_SHIFT                     (8U)
#define AIPS_PACRN_TP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_TP5_SHIFT)) & AIPS_PACRN_TP5_MASK)
#define AIPS_PACRN_WP5_MASK                      (0x200U)
#define AIPS_PACRN_WP5_SHIFT                     (9U)
#define AIPS_PACRN_WP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_WP5_SHIFT)) & AIPS_PACRN_WP5_MASK)
#define AIPS_PACRN_SP5_MASK                      (0x400U)
#define AIPS_PACRN_SP5_SHIFT                     (10U)
#define AIPS_PACRN_SP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_SP5_SHIFT)) & AIPS_PACRN_SP5_MASK)
#define AIPS_PACRN_TP4_MASK                      (0x1000U)
#define AIPS_PACRN_TP4_SHIFT                     (12U)
#define AIPS_PACRN_TP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_TP4_SHIFT)) & AIPS_PACRN_TP4_MASK)
#define AIPS_PACRN_WP4_MASK                      (0x2000U)
#define AIPS_PACRN_WP4_SHIFT                     (13U)
#define AIPS_PACRN_WP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_WP4_SHIFT)) & AIPS_PACRN_WP4_MASK)
#define AIPS_PACRN_SP4_MASK                      (0x4000U)
#define AIPS_PACRN_SP4_SHIFT                     (14U)
#define AIPS_PACRN_SP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_SP4_SHIFT)) & AIPS_PACRN_SP4_MASK)
#define AIPS_PACRN_TP3_MASK                      (0x10000U)
#define AIPS_PACRN_TP3_SHIFT                     (16U)
#define AIPS_PACRN_TP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_TP3_SHIFT)) & AIPS_PACRN_TP3_MASK)
#define AIPS_PACRN_WP3_MASK                      (0x20000U)
#define AIPS_PACRN_WP3_SHIFT                     (17U)
#define AIPS_PACRN_WP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_WP3_SHIFT)) & AIPS_PACRN_WP3_MASK)
#define AIPS_PACRN_SP3_MASK                      (0x40000U)
#define AIPS_PACRN_SP3_SHIFT                     (18U)
#define AIPS_PACRN_SP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_SP3_SHIFT)) & AIPS_PACRN_SP3_MASK)
#define AIPS_PACRN_TP2_MASK                      (0x100000U)
#define AIPS_PACRN_TP2_SHIFT                     (20U)
#define AIPS_PACRN_TP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_TP2_SHIFT)) & AIPS_PACRN_TP2_MASK)
#define AIPS_PACRN_WP2_MASK                      (0x200000U)
#define AIPS_PACRN_WP2_SHIFT                     (21U)
#define AIPS_PACRN_WP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_WP2_SHIFT)) & AIPS_PACRN_WP2_MASK)
#define AIPS_PACRN_SP2_MASK                      (0x400000U)
#define AIPS_PACRN_SP2_SHIFT                     (22U)
#define AIPS_PACRN_SP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_SP2_SHIFT)) & AIPS_PACRN_SP2_MASK)
#define AIPS_PACRN_TP1_MASK                      (0x1000000U)
#define AIPS_PACRN_TP1_SHIFT                     (24U)
#define AIPS_PACRN_TP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_TP1_SHIFT)) & AIPS_PACRN_TP1_MASK)
#define AIPS_PACRN_WP1_MASK                      (0x2000000U)
#define AIPS_PACRN_WP1_SHIFT                     (25U)
#define AIPS_PACRN_WP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_WP1_SHIFT)) & AIPS_PACRN_WP1_MASK)
#define AIPS_PACRN_SP1_MASK                      (0x4000000U)
#define AIPS_PACRN_SP1_SHIFT                     (26U)
#define AIPS_PACRN_SP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_SP1_SHIFT)) & AIPS_PACRN_SP1_MASK)
#define AIPS_PACRN_TP0_MASK                      (0x10000000U)
#define AIPS_PACRN_TP0_SHIFT                     (28U)
#define AIPS_PACRN_TP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_TP0_SHIFT)) & AIPS_PACRN_TP0_MASK)
#define AIPS_PACRN_WP0_MASK                      (0x20000000U)
#define AIPS_PACRN_WP0_SHIFT                     (29U)
#define AIPS_PACRN_WP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_WP0_SHIFT)) & AIPS_PACRN_WP0_MASK)
#define AIPS_PACRN_SP0_MASK                      (0x40000000U)
#define AIPS_PACRN_SP0_SHIFT                     (30U)
#define AIPS_PACRN_SP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_SP0_SHIFT)) & AIPS_PACRN_SP0_MASK)

/*! @name PACRO - Peripheral Access Control Register */
#define AIPS_PACRO_TP7_MASK                      (0x1U)
#define AIPS_PACRO_TP7_SHIFT                     (0U)
#define AIPS_PACRO_TP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_TP7_SHIFT)) & AIPS_PACRO_TP7_MASK)
#define AIPS_PACRO_WP7_MASK                      (0x2U)
#define AIPS_PACRO_WP7_SHIFT                     (1U)
#define AIPS_PACRO_WP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_WP7_SHIFT)) & AIPS_PACRO_WP7_MASK)
#define AIPS_PACRO_SP7_MASK                      (0x4U)
#define AIPS_PACRO_SP7_SHIFT                     (2U)
#define AIPS_PACRO_SP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_SP7_SHIFT)) & AIPS_PACRO_SP7_MASK)
#define AIPS_PACRO_TP6_MASK                      (0x10U)
#define AIPS_PACRO_TP6_SHIFT                     (4U)
#define AIPS_PACRO_TP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_TP6_SHIFT)) & AIPS_PACRO_TP6_MASK)
#define AIPS_PACRO_WP6_MASK                      (0x20U)
#define AIPS_PACRO_WP6_SHIFT                     (5U)
#define AIPS_PACRO_WP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_WP6_SHIFT)) & AIPS_PACRO_WP6_MASK)
#define AIPS_PACRO_SP6_MASK                      (0x40U)
#define AIPS_PACRO_SP6_SHIFT                     (6U)
#define AIPS_PACRO_SP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_SP6_SHIFT)) & AIPS_PACRO_SP6_MASK)
#define AIPS_PACRO_TP5_MASK                      (0x100U)
#define AIPS_PACRO_TP5_SHIFT                     (8U)
#define AIPS_PACRO_TP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_TP5_SHIFT)) & AIPS_PACRO_TP5_MASK)
#define AIPS_PACRO_WP5_MASK                      (0x200U)
#define AIPS_PACRO_WP5_SHIFT                     (9U)
#define AIPS_PACRO_WP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_WP5_SHIFT)) & AIPS_PACRO_WP5_MASK)
#define AIPS_PACRO_SP5_MASK                      (0x400U)
#define AIPS_PACRO_SP5_SHIFT                     (10U)
#define AIPS_PACRO_SP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_SP5_SHIFT)) & AIPS_PACRO_SP5_MASK)
#define AIPS_PACRO_TP4_MASK                      (0x1000U)
#define AIPS_PACRO_TP4_SHIFT                     (12U)
#define AIPS_PACRO_TP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_TP4_SHIFT)) & AIPS_PACRO_TP4_MASK)
#define AIPS_PACRO_WP4_MASK                      (0x2000U)
#define AIPS_PACRO_WP4_SHIFT                     (13U)
#define AIPS_PACRO_WP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_WP4_SHIFT)) & AIPS_PACRO_WP4_MASK)
#define AIPS_PACRO_SP4_MASK                      (0x4000U)
#define AIPS_PACRO_SP4_SHIFT                     (14U)
#define AIPS_PACRO_SP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_SP4_SHIFT)) & AIPS_PACRO_SP4_MASK)
#define AIPS_PACRO_TP3_MASK                      (0x10000U)
#define AIPS_PACRO_TP3_SHIFT                     (16U)
#define AIPS_PACRO_TP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_TP3_SHIFT)) & AIPS_PACRO_TP3_MASK)
#define AIPS_PACRO_WP3_MASK                      (0x20000U)
#define AIPS_PACRO_WP3_SHIFT                     (17U)
#define AIPS_PACRO_WP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_WP3_SHIFT)) & AIPS_PACRO_WP3_MASK)
#define AIPS_PACRO_SP3_MASK                      (0x40000U)
#define AIPS_PACRO_SP3_SHIFT                     (18U)
#define AIPS_PACRO_SP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_SP3_SHIFT)) & AIPS_PACRO_SP3_MASK)
#define AIPS_PACRO_TP2_MASK                      (0x100000U)
#define AIPS_PACRO_TP2_SHIFT                     (20U)
#define AIPS_PACRO_TP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_TP2_SHIFT)) & AIPS_PACRO_TP2_MASK)
#define AIPS_PACRO_WP2_MASK                      (0x200000U)
#define AIPS_PACRO_WP2_SHIFT                     (21U)
#define AIPS_PACRO_WP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_WP2_SHIFT)) & AIPS_PACRO_WP2_MASK)
#define AIPS_PACRO_SP2_MASK                      (0x400000U)
#define AIPS_PACRO_SP2_SHIFT                     (22U)
#define AIPS_PACRO_SP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_SP2_SHIFT)) & AIPS_PACRO_SP2_MASK)
#define AIPS_PACRO_TP1_MASK                      (0x1000000U)
#define AIPS_PACRO_TP1_SHIFT                     (24U)
#define AIPS_PACRO_TP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_TP1_SHIFT)) & AIPS_PACRO_TP1_MASK)
#define AIPS_PACRO_WP1_MASK                      (0x2000000U)
#define AIPS_PACRO_WP1_SHIFT                     (25U)
#define AIPS_PACRO_WP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_WP1_SHIFT)) & AIPS_PACRO_WP1_MASK)
#define AIPS_PACRO_SP1_MASK                      (0x4000000U)
#define AIPS_PACRO_SP1_SHIFT                     (26U)
#define AIPS_PACRO_SP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_SP1_SHIFT)) & AIPS_PACRO_SP1_MASK)
#define AIPS_PACRO_TP0_MASK                      (0x10000000U)
#define AIPS_PACRO_TP0_SHIFT                     (28U)
#define AIPS_PACRO_TP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_TP0_SHIFT)) & AIPS_PACRO_TP0_MASK)
#define AIPS_PACRO_WP0_MASK                      (0x20000000U)
#define AIPS_PACRO_WP0_SHIFT                     (29U)
#define AIPS_PACRO_WP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_WP0_SHIFT)) & AIPS_PACRO_WP0_MASK)
#define AIPS_PACRO_SP0_MASK                      (0x40000000U)
#define AIPS_PACRO_SP0_SHIFT                     (30U)
#define AIPS_PACRO_SP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_SP0_SHIFT)) & AIPS_PACRO_SP0_MASK)

/*! @name PACRP - Peripheral Access Control Register */
#define AIPS_PACRP_TP7_MASK                      (0x1U)
#define AIPS_PACRP_TP7_SHIFT                     (0U)
#define AIPS_PACRP_TP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_TP7_SHIFT)) & AIPS_PACRP_TP7_MASK)
#define AIPS_PACRP_WP7_MASK                      (0x2U)
#define AIPS_PACRP_WP7_SHIFT                     (1U)
#define AIPS_PACRP_WP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_WP7_SHIFT)) & AIPS_PACRP_WP7_MASK)
#define AIPS_PACRP_SP7_MASK                      (0x4U)
#define AIPS_PACRP_SP7_SHIFT                     (2U)
#define AIPS_PACRP_SP7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_SP7_SHIFT)) & AIPS_PACRP_SP7_MASK)
#define AIPS_PACRP_TP6_MASK                      (0x10U)
#define AIPS_PACRP_TP6_SHIFT                     (4U)
#define AIPS_PACRP_TP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_TP6_SHIFT)) & AIPS_PACRP_TP6_MASK)
#define AIPS_PACRP_WP6_MASK                      (0x20U)
#define AIPS_PACRP_WP6_SHIFT                     (5U)
#define AIPS_PACRP_WP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_WP6_SHIFT)) & AIPS_PACRP_WP6_MASK)
#define AIPS_PACRP_SP6_MASK                      (0x40U)
#define AIPS_PACRP_SP6_SHIFT                     (6U)
#define AIPS_PACRP_SP6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_SP6_SHIFT)) & AIPS_PACRP_SP6_MASK)
#define AIPS_PACRP_TP5_MASK                      (0x100U)
#define AIPS_PACRP_TP5_SHIFT                     (8U)
#define AIPS_PACRP_TP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_TP5_SHIFT)) & AIPS_PACRP_TP5_MASK)
#define AIPS_PACRP_WP5_MASK                      (0x200U)
#define AIPS_PACRP_WP5_SHIFT                     (9U)
#define AIPS_PACRP_WP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_WP5_SHIFT)) & AIPS_PACRP_WP5_MASK)
#define AIPS_PACRP_SP5_MASK                      (0x400U)
#define AIPS_PACRP_SP5_SHIFT                     (10U)
#define AIPS_PACRP_SP5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_SP5_SHIFT)) & AIPS_PACRP_SP5_MASK)
#define AIPS_PACRP_TP4_MASK                      (0x1000U)
#define AIPS_PACRP_TP4_SHIFT                     (12U)
#define AIPS_PACRP_TP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_TP4_SHIFT)) & AIPS_PACRP_TP4_MASK)
#define AIPS_PACRP_WP4_MASK                      (0x2000U)
#define AIPS_PACRP_WP4_SHIFT                     (13U)
#define AIPS_PACRP_WP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_WP4_SHIFT)) & AIPS_PACRP_WP4_MASK)
#define AIPS_PACRP_SP4_MASK                      (0x4000U)
#define AIPS_PACRP_SP4_SHIFT                     (14U)
#define AIPS_PACRP_SP4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_SP4_SHIFT)) & AIPS_PACRP_SP4_MASK)
#define AIPS_PACRP_TP3_MASK                      (0x10000U)
#define AIPS_PACRP_TP3_SHIFT                     (16U)
#define AIPS_PACRP_TP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_TP3_SHIFT)) & AIPS_PACRP_TP3_MASK)
#define AIPS_PACRP_WP3_MASK                      (0x20000U)
#define AIPS_PACRP_WP3_SHIFT                     (17U)
#define AIPS_PACRP_WP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_WP3_SHIFT)) & AIPS_PACRP_WP3_MASK)
#define AIPS_PACRP_SP3_MASK                      (0x40000U)
#define AIPS_PACRP_SP3_SHIFT                     (18U)
#define AIPS_PACRP_SP3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_SP3_SHIFT)) & AIPS_PACRP_SP3_MASK)
#define AIPS_PACRP_TP2_MASK                      (0x100000U)
#define AIPS_PACRP_TP2_SHIFT                     (20U)
#define AIPS_PACRP_TP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_TP2_SHIFT)) & AIPS_PACRP_TP2_MASK)
#define AIPS_PACRP_WP2_MASK                      (0x200000U)
#define AIPS_PACRP_WP2_SHIFT                     (21U)
#define AIPS_PACRP_WP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_WP2_SHIFT)) & AIPS_PACRP_WP2_MASK)
#define AIPS_PACRP_SP2_MASK                      (0x400000U)
#define AIPS_PACRP_SP2_SHIFT                     (22U)
#define AIPS_PACRP_SP2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_SP2_SHIFT)) & AIPS_PACRP_SP2_MASK)
#define AIPS_PACRP_TP1_MASK                      (0x1000000U)
#define AIPS_PACRP_TP1_SHIFT                     (24U)
#define AIPS_PACRP_TP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_TP1_SHIFT)) & AIPS_PACRP_TP1_MASK)
#define AIPS_PACRP_WP1_MASK                      (0x2000000U)
#define AIPS_PACRP_WP1_SHIFT                     (25U)
#define AIPS_PACRP_WP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_WP1_SHIFT)) & AIPS_PACRP_WP1_MASK)
#define AIPS_PACRP_SP1_MASK                      (0x4000000U)
#define AIPS_PACRP_SP1_SHIFT                     (26U)
#define AIPS_PACRP_SP1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_SP1_SHIFT)) & AIPS_PACRP_SP1_MASK)
#define AIPS_PACRP_TP0_MASK                      (0x10000000U)
#define AIPS_PACRP_TP0_SHIFT                     (28U)
#define AIPS_PACRP_TP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_TP0_SHIFT)) & AIPS_PACRP_TP0_MASK)
#define AIPS_PACRP_WP0_MASK                      (0x20000000U)
#define AIPS_PACRP_WP0_SHIFT                     (29U)
#define AIPS_PACRP_WP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_WP0_SHIFT)) & AIPS_PACRP_WP0_MASK)
#define AIPS_PACRP_SP0_MASK                      (0x40000000U)
#define AIPS_PACRP_SP0_SHIFT                     (30U)
#define AIPS_PACRP_SP0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_SP0_SHIFT)) & AIPS_PACRP_SP0_MASK)


/*!
 * @}
 */ /* end of group AIPS_Register_Masks */


/* AIPS - Peripheral instance base addresses */
/** Peripheral AIPS0 base address */
#define AIPS0_BASE                               (0x40000000u)
/** Peripheral AIPS0 base pointer */
#define AIPS0                                    ((AIPS_Type *)AIPS0_BASE)
/** Peripheral AIPS1 base address */
#define AIPS1_BASE                               (0x40080000u)
/** Peripheral AIPS1 base pointer */
#define AIPS1                                    ((AIPS_Type *)AIPS1_BASE)
/** Array initializer of AIPS peripheral base addresses */
#define AIPS_BASE_ADDRS                          { AIPS0_BASE, AIPS1_BASE }
/** Array initializer of AIPS peripheral base pointers */
#define AIPS_BASE_PTRS                           { AIPS0, AIPS1 }

/*!
 * @}
 */ /* end of group AIPS_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- AOI Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AOI_Peripheral_Access_Layer AOI Peripheral Access Layer
 * @{
 */

/** AOI - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0x4 */
    __IO uint16_t BFCRT01;                           /**< Boolean Function Term 0 and 1 Configuration Register for EVENTn, array offset: 0x0, array step: 0x4 */
    __IO uint16_t BFCRT23;                           /**< Boolean Function Term 2 and 3 Configuration Register for EVENTn, array offset: 0x2, array step: 0x4 */
  } BFCRT[4];
} AOI_Type;

/* ----------------------------------------------------------------------------
   -- AOI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AOI_Register_Masks AOI Register Masks
 * @{
 */

/*! @name BFCRT01 - Boolean Function Term 0 and 1 Configuration Register for EVENTn */
#define AOI_BFCRT01_PT1_DC_MASK                  (0x3U)
#define AOI_BFCRT01_PT1_DC_SHIFT                 (0U)
#define AOI_BFCRT01_PT1_DC(x)                    (((uint16_t)(((uint16_t)(x)) << AOI_BFCRT01_PT1_DC_SHIFT)) & AOI_BFCRT01_PT1_DC_MASK)
#define AOI_BFCRT01_PT1_CC_MASK                  (0xCU)
#define AOI_BFCRT01_PT1_CC_SHIFT                 (2U)
#define AOI_BFCRT01_PT1_CC(x)                    (((uint16_t)(((uint16_t)(x)) << AOI_BFCRT01_PT1_CC_SHIFT)) & AOI_BFCRT01_PT1_CC_MASK)
#define AOI_BFCRT01_PT1_BC_MASK                  (0x30U)
#define AOI_BFCRT01_PT1_BC_SHIFT                 (4U)
#define AOI_BFCRT01_PT1_BC(x)                    (((uint16_t)(((uint16_t)(x)) << AOI_BFCRT01_PT1_BC_SHIFT)) & AOI_BFCRT01_PT1_BC_MASK)
#define AOI_BFCRT01_PT1_AC_MASK                  (0xC0U)
#define AOI_BFCRT01_PT1_AC_SHIFT                 (6U)
#define AOI_BFCRT01_PT1_AC(x)                    (((uint16_t)(((uint16_t)(x)) << AOI_BFCRT01_PT1_AC_SHIFT)) & AOI_BFCRT01_PT1_AC_MASK)
#define AOI_BFCRT01_PT0_DC_MASK                  (0x300U)
#define AOI_BFCRT01_PT0_DC_SHIFT                 (8U)
#define AOI_BFCRT01_PT0_DC(x)                    (((uint16_t)(((uint16_t)(x)) << AOI_BFCRT01_PT0_DC_SHIFT)) & AOI_BFCRT01_PT0_DC_MASK)
#define AOI_BFCRT01_PT0_CC_MASK                  (0xC00U)
#define AOI_BFCRT01_PT0_CC_SHIFT                 (10U)
#define AOI_BFCRT01_PT0_CC(x)                    (((uint16_t)(((uint16_t)(x)) << AOI_BFCRT01_PT0_CC_SHIFT)) & AOI_BFCRT01_PT0_CC_MASK)
#define AOI_BFCRT01_PT0_BC_MASK                  (0x3000U)
#define AOI_BFCRT01_PT0_BC_SHIFT                 (12U)
#define AOI_BFCRT01_PT0_BC(x)                    (((uint16_t)(((uint16_t)(x)) << AOI_BFCRT01_PT0_BC_SHIFT)) & AOI_BFCRT01_PT0_BC_MASK)
#define AOI_BFCRT01_PT0_AC_MASK                  (0xC000U)
#define AOI_BFCRT01_PT0_AC_SHIFT                 (14U)
#define AOI_BFCRT01_PT0_AC(x)                    (((uint16_t)(((uint16_t)(x)) << AOI_BFCRT01_PT0_AC_SHIFT)) & AOI_BFCRT01_PT0_AC_MASK)

/* The count of AOI_BFCRT01 */
#define AOI_BFCRT01_COUNT                        (4U)

/*! @name BFCRT23 - Boolean Function Term 2 and 3 Configuration Register for EVENTn */
#define AOI_BFCRT23_PT3_DC_MASK                  (0x3U)
#define AOI_BFCRT23_PT3_DC_SHIFT                 (0U)
#define AOI_BFCRT23_PT3_DC(x)                    (((uint16_t)(((uint16_t)(x)) << AOI_BFCRT23_PT3_DC_SHIFT)) & AOI_BFCRT23_PT3_DC_MASK)
#define AOI_BFCRT23_PT3_CC_MASK                  (0xCU)
#define AOI_BFCRT23_PT3_CC_SHIFT                 (2U)
#define AOI_BFCRT23_PT3_CC(x)                    (((uint16_t)(((uint16_t)(x)) << AOI_BFCRT23_PT3_CC_SHIFT)) & AOI_BFCRT23_PT3_CC_MASK)
#define AOI_BFCRT23_PT3_BC_MASK                  (0x30U)
#define AOI_BFCRT23_PT3_BC_SHIFT                 (4U)
#define AOI_BFCRT23_PT3_BC(x)                    (((uint16_t)(((uint16_t)(x)) << AOI_BFCRT23_PT3_BC_SHIFT)) & AOI_BFCRT23_PT3_BC_MASK)
#define AOI_BFCRT23_PT3_AC_MASK                  (0xC0U)
#define AOI_BFCRT23_PT3_AC_SHIFT                 (6U)
#define AOI_BFCRT23_PT3_AC(x)                    (((uint16_t)(((uint16_t)(x)) << AOI_BFCRT23_PT3_AC_SHIFT)) & AOI_BFCRT23_PT3_AC_MASK)
#define AOI_BFCRT23_PT2_DC_MASK                  (0x300U)
#define AOI_BFCRT23_PT2_DC_SHIFT                 (8U)
#define AOI_BFCRT23_PT2_DC(x)                    (((uint16_t)(((uint16_t)(x)) << AOI_BFCRT23_PT2_DC_SHIFT)) & AOI_BFCRT23_PT2_DC_MASK)
#define AOI_BFCRT23_PT2_CC_MASK                  (0xC00U)
#define AOI_BFCRT23_PT2_CC_SHIFT                 (10U)
#define AOI_BFCRT23_PT2_CC(x)                    (((uint16_t)(((uint16_t)(x)) << AOI_BFCRT23_PT2_CC_SHIFT)) & AOI_BFCRT23_PT2_CC_MASK)
#define AOI_BFCRT23_PT2_BC_MASK                  (0x3000U)
#define AOI_BFCRT23_PT2_BC_SHIFT                 (12U)
#define AOI_BFCRT23_PT2_BC(x)                    (((uint16_t)(((uint16_t)(x)) << AOI_BFCRT23_PT2_BC_SHIFT)) & AOI_BFCRT23_PT2_BC_MASK)
#define AOI_BFCRT23_PT2_AC_MASK                  (0xC000U)
#define AOI_BFCRT23_PT2_AC_SHIFT                 (14U)
#define AOI_BFCRT23_PT2_AC(x)                    (((uint16_t)(((uint16_t)(x)) << AOI_BFCRT23_PT2_AC_SHIFT)) & AOI_BFCRT23_PT2_AC_MASK)

/* The count of AOI_BFCRT23 */
#define AOI_BFCRT23_COUNT                        (4U)


/*!
 * @}
 */ /* end of group AOI_Register_Masks */


/* AOI - Peripheral instance base addresses */
/** Peripheral AOI0 base address */
#define AOI0_BASE                                (0x4005B000u)
/** Peripheral AOI0 base pointer */
#define AOI0                                     ((AOI_Type *)AOI0_BASE)
/** Array initializer of AOI peripheral base addresses */
#define AOI_BASE_ADDRS                           { AOI0_BASE }
/** Array initializer of AOI peripheral base pointers */
#define AOI_BASE_PTRS                            { AOI0 }

/*!
 * @}
 */ /* end of group AOI_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- AXBS Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AXBS_Peripheral_Access_Layer AXBS Peripheral Access Layer
 * @{
 */

/** AXBS - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0x100 */
    __IO uint32_t PRS;                               /**< Priority Registers Slave, array offset: 0x0, array step: 0x100 */
         uint8_t RESERVED_0[12];
    __IO uint32_t CRS;                               /**< Control Register, array offset: 0x10, array step: 0x100 */
         uint8_t RESERVED_1[236];
  } SLAVE[7];
       uint8_t RESERVED_0[256];
  __IO uint32_t MGPCR0;                            /**< Master General Purpose Control Register, offset: 0x800 */
       uint8_t RESERVED_1[252];
  __IO uint32_t MGPCR1;                            /**< Master General Purpose Control Register, offset: 0x900 */
       uint8_t RESERVED_2[252];
  __IO uint32_t MGPCR2;                            /**< Master General Purpose Control Register, offset: 0xA00 */
       uint8_t RESERVED_3[252];
  __IO uint32_t MGPCR3;                            /**< Master General Purpose Control Register, offset: 0xB00 */
} AXBS_Type;

/* ----------------------------------------------------------------------------
   -- AXBS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AXBS_Register_Masks AXBS Register Masks
 * @{
 */

/*! @name PRS - Priority Registers Slave */
#define AXBS_PRS_M0_MASK                         (0x7U)
#define AXBS_PRS_M0_SHIFT                        (0U)
#define AXBS_PRS_M0(x)                           (((uint32_t)(((uint32_t)(x)) << AXBS_PRS_M0_SHIFT)) & AXBS_PRS_M0_MASK)
#define AXBS_PRS_M1_MASK                         (0x70U)
#define AXBS_PRS_M1_SHIFT                        (4U)
#define AXBS_PRS_M1(x)                           (((uint32_t)(((uint32_t)(x)) << AXBS_PRS_M1_SHIFT)) & AXBS_PRS_M1_MASK)
#define AXBS_PRS_M2_MASK                         (0x700U)
#define AXBS_PRS_M2_SHIFT                        (8U)
#define AXBS_PRS_M2(x)                           (((uint32_t)(((uint32_t)(x)) << AXBS_PRS_M2_SHIFT)) & AXBS_PRS_M2_MASK)
#define AXBS_PRS_M3_MASK                         (0x7000U)
#define AXBS_PRS_M3_SHIFT                        (12U)
#define AXBS_PRS_M3(x)                           (((uint32_t)(((uint32_t)(x)) << AXBS_PRS_M3_SHIFT)) & AXBS_PRS_M3_MASK)

/* The count of AXBS_PRS */
#define AXBS_PRS_COUNT                           (7U)

/*! @name CRS - Control Register */
#define AXBS_CRS_PARK_MASK                       (0x7U)
#define AXBS_CRS_PARK_SHIFT                      (0U)
#define AXBS_CRS_PARK(x)                         (((uint32_t)(((uint32_t)(x)) << AXBS_CRS_PARK_SHIFT)) & AXBS_CRS_PARK_MASK)
#define AXBS_CRS_PCTL_MASK                       (0x30U)
#define AXBS_CRS_PCTL_SHIFT                      (4U)
#define AXBS_CRS_PCTL(x)                         (((uint32_t)(((uint32_t)(x)) << AXBS_CRS_PCTL_SHIFT)) & AXBS_CRS_PCTL_MASK)
#define AXBS_CRS_ARB_MASK                        (0x300U)
#define AXBS_CRS_ARB_SHIFT                       (8U)
#define AXBS_CRS_ARB(x)                          (((uint32_t)(((uint32_t)(x)) << AXBS_CRS_ARB_SHIFT)) & AXBS_CRS_ARB_MASK)
#define AXBS_CRS_HLP_MASK                        (0x40000000U)
#define AXBS_CRS_HLP_SHIFT                       (30U)
#define AXBS_CRS_HLP(x)                          (((uint32_t)(((uint32_t)(x)) << AXBS_CRS_HLP_SHIFT)) & AXBS_CRS_HLP_MASK)
#define AXBS_CRS_RO_MASK                         (0x80000000U)
#define AXBS_CRS_RO_SHIFT                        (31U)
#define AXBS_CRS_RO(x)                           (((uint32_t)(((uint32_t)(x)) << AXBS_CRS_RO_SHIFT)) & AXBS_CRS_RO_MASK)

/* The count of AXBS_CRS */
#define AXBS_CRS_COUNT                           (7U)

/*! @name MGPCR0 - Master General Purpose Control Register */
#define AXBS_MGPCR0_AULB_MASK                    (0x7U)
#define AXBS_MGPCR0_AULB_SHIFT                   (0U)
#define AXBS_MGPCR0_AULB(x)                      (((uint32_t)(((uint32_t)(x)) << AXBS_MGPCR0_AULB_SHIFT)) & AXBS_MGPCR0_AULB_MASK)

/*! @name MGPCR1 - Master General Purpose Control Register */
#define AXBS_MGPCR1_AULB_MASK                    (0x7U)
#define AXBS_MGPCR1_AULB_SHIFT                   (0U)
#define AXBS_MGPCR1_AULB(x)                      (((uint32_t)(((uint32_t)(x)) << AXBS_MGPCR1_AULB_SHIFT)) & AXBS_MGPCR1_AULB_MASK)

/*! @name MGPCR2 - Master General Purpose Control Register */
#define AXBS_MGPCR2_AULB_MASK                    (0x7U)
#define AXBS_MGPCR2_AULB_SHIFT                   (0U)
#define AXBS_MGPCR2_AULB(x)                      (((uint32_t)(((uint32_t)(x)) << AXBS_MGPCR2_AULB_SHIFT)) & AXBS_MGPCR2_AULB_MASK)

/*! @name MGPCR3 - Master General Purpose Control Register */
#define AXBS_MGPCR3_AULB_MASK                    (0x7U)
#define AXBS_MGPCR3_AULB_SHIFT                   (0U)
#define AXBS_MGPCR3_AULB(x)                      (((uint32_t)(((uint32_t)(x)) << AXBS_MGPCR3_AULB_SHIFT)) & AXBS_MGPCR3_AULB_MASK)


/*!
 * @}
 */ /* end of group AXBS_Register_Masks */


/* AXBS - Peripheral instance base addresses */
/** Peripheral AXBS base address */
#define AXBS_BASE                                (0x40004000u)
/** Peripheral AXBS base pointer */
#define AXBS                                     ((AXBS_Type *)AXBS_BASE)
/** Array initializer of AXBS peripheral base addresses */
#define AXBS_BASE_ADDRS                          { AXBS_BASE }
/** Array initializer of AXBS peripheral base pointers */
#define AXBS_BASE_PTRS                           { AXBS }

/*!
 * @}
 */ /* end of group AXBS_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- CAN Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAN_Peripheral_Access_Layer CAN Peripheral Access Layer
 * @{
 */

/** CAN - Register Layout Typedef */
typedef struct {
  __IO uint32_t MCR;                               /**< Module Configuration Register, offset: 0x0 */
  __IO uint32_t CTRL1;                             /**< Control 1 register, offset: 0x4 */
  __IO uint32_t TIMER;                             /**< Free Running Timer, offset: 0x8 */
       uint8_t RESERVED_0[4];
  __IO uint32_t RXMGMASK;                          /**< Rx Mailboxes Global Mask Register, offset: 0x10 */
  __IO uint32_t RX14MASK;                          /**< Rx 14 Mask register, offset: 0x14 */
  __IO uint32_t RX15MASK;                          /**< Rx 15 Mask register, offset: 0x18 */
  __IO uint32_t ECR;                               /**< Error Counter, offset: 0x1C */
  __IO uint32_t ESR1;                              /**< Error and Status 1 register, offset: 0x20 */
       uint8_t RESERVED_1[4];
  __IO uint32_t IMASK1;                            /**< Interrupt Masks 1 register, offset: 0x28 */
       uint8_t RESERVED_2[4];
  __IO uint32_t IFLAG1;                            /**< Interrupt Flags 1 register, offset: 0x30 */
  __IO uint32_t CTRL2;                             /**< Control 2 register, offset: 0x34 */
  __I  uint32_t ESR2;                              /**< Error and Status 2 register, offset: 0x38 */
       uint8_t RESERVED_3[8];
  __I  uint32_t CRCR;                              /**< CRC Register, offset: 0x44 */
  __IO uint32_t RXFGMASK;                          /**< Rx FIFO Global Mask register, offset: 0x48 */
  __I  uint32_t RXFIR;                             /**< Rx FIFO Information Register, offset: 0x4C */
  __IO uint32_t CBT;                               /**< CAN Bit Timing Register, offset: 0x50 */
       uint8_t RESERVED_4[44];
  struct {                                         /* offset: 0x80, array step: 0x10 */
    __IO uint32_t CS;                                /**< Message Buffer 0 CS Register..Message Buffer 15 CS Register, array offset: 0x80, array step: 0x10 */
    __IO uint32_t ID;                                /**< Message Buffer 0 ID Register..Message Buffer 15 ID Register, array offset: 0x84, array step: 0x10 */
    __IO uint32_t WORD0;                             /**< Message Buffer 0 WORD0 Register..Message Buffer 15 WORD0 Register, array offset: 0x88, array step: 0x10 */
    __IO uint32_t WORD1;                             /**< Message Buffer 0 WORD1 Register..Message Buffer 15 WORD1 Register, array offset: 0x8C, array step: 0x10 */
  } MB[16];
       uint8_t RESERVED_5[1792];
  __IO uint32_t RXIMR[16];                         /**< Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 */
} CAN_Type;

/* ----------------------------------------------------------------------------
   -- CAN Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAN_Register_Masks CAN Register Masks
 * @{
 */

/*! @name MCR - Module Configuration Register */
#define CAN_MCR_MAXMB_MASK                       (0x7FU)
#define CAN_MCR_MAXMB_SHIFT                      (0U)
#define CAN_MCR_MAXMB(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_MCR_MAXMB_SHIFT)) & CAN_MCR_MAXMB_MASK)
#define CAN_MCR_IDAM_MASK                        (0x300U)
#define CAN_MCR_IDAM_SHIFT                       (8U)
#define CAN_MCR_IDAM(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_MCR_IDAM_SHIFT)) & CAN_MCR_IDAM_MASK)
#define CAN_MCR_AEN_MASK                         (0x1000U)
#define CAN_MCR_AEN_SHIFT                        (12U)
#define CAN_MCR_AEN(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_MCR_AEN_SHIFT)) & CAN_MCR_AEN_MASK)
#define CAN_MCR_LPRIOEN_MASK                     (0x2000U)
#define CAN_MCR_LPRIOEN_SHIFT                    (13U)
#define CAN_MCR_LPRIOEN(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_MCR_LPRIOEN_SHIFT)) & CAN_MCR_LPRIOEN_MASK)
#define CAN_MCR_DMA_MASK                         (0x8000U)
#define CAN_MCR_DMA_SHIFT                        (15U)
#define CAN_MCR_DMA(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_MCR_DMA_SHIFT)) & CAN_MCR_DMA_MASK)
#define CAN_MCR_IRMQ_MASK                        (0x10000U)
#define CAN_MCR_IRMQ_SHIFT                       (16U)
#define CAN_MCR_IRMQ(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_MCR_IRMQ_SHIFT)) & CAN_MCR_IRMQ_MASK)
#define CAN_MCR_SRXDIS_MASK                      (0x20000U)
#define CAN_MCR_SRXDIS_SHIFT                     (17U)
#define CAN_MCR_SRXDIS(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_MCR_SRXDIS_SHIFT)) & CAN_MCR_SRXDIS_MASK)
#define CAN_MCR_DOZE_MASK                        (0x40000U)
#define CAN_MCR_DOZE_SHIFT                       (18U)
#define CAN_MCR_DOZE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_MCR_DOZE_SHIFT)) & CAN_MCR_DOZE_MASK)
#define CAN_MCR_WAKSRC_MASK                      (0x80000U)
#define CAN_MCR_WAKSRC_SHIFT                     (19U)
#define CAN_MCR_WAKSRC(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_MCR_WAKSRC_SHIFT)) & CAN_MCR_WAKSRC_MASK)
#define CAN_MCR_LPMACK_MASK                      (0x100000U)
#define CAN_MCR_LPMACK_SHIFT                     (20U)
#define CAN_MCR_LPMACK(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_MCR_LPMACK_SHIFT)) & CAN_MCR_LPMACK_MASK)
#define CAN_MCR_WRNEN_MASK                       (0x200000U)
#define CAN_MCR_WRNEN_SHIFT                      (21U)
#define CAN_MCR_WRNEN(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_MCR_WRNEN_SHIFT)) & CAN_MCR_WRNEN_MASK)
#define CAN_MCR_SLFWAK_MASK                      (0x400000U)
#define CAN_MCR_SLFWAK_SHIFT                     (22U)
#define CAN_MCR_SLFWAK(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_MCR_SLFWAK_SHIFT)) & CAN_MCR_SLFWAK_MASK)
#define CAN_MCR_SUPV_MASK                        (0x800000U)
#define CAN_MCR_SUPV_SHIFT                       (23U)
#define CAN_MCR_SUPV(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_MCR_SUPV_SHIFT)) & CAN_MCR_SUPV_MASK)
#define CAN_MCR_FRZACK_MASK                      (0x1000000U)
#define CAN_MCR_FRZACK_SHIFT                     (24U)
#define CAN_MCR_FRZACK(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_MCR_FRZACK_SHIFT)) & CAN_MCR_FRZACK_MASK)
#define CAN_MCR_SOFTRST_MASK                     (0x2000000U)
#define CAN_MCR_SOFTRST_SHIFT                    (25U)
#define CAN_MCR_SOFTRST(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_MCR_SOFTRST_SHIFT)) & CAN_MCR_SOFTRST_MASK)
#define CAN_MCR_WAKMSK_MASK                      (0x4000000U)
#define CAN_MCR_WAKMSK_SHIFT                     (26U)
#define CAN_MCR_WAKMSK(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_MCR_WAKMSK_SHIFT)) & CAN_MCR_WAKMSK_MASK)
#define CAN_MCR_NOTRDY_MASK                      (0x8000000U)
#define CAN_MCR_NOTRDY_SHIFT                     (27U)
#define CAN_MCR_NOTRDY(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_MCR_NOTRDY_SHIFT)) & CAN_MCR_NOTRDY_MASK)
#define CAN_MCR_HALT_MASK                        (0x10000000U)
#define CAN_MCR_HALT_SHIFT                       (28U)
#define CAN_MCR_HALT(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_MCR_HALT_SHIFT)) & CAN_MCR_HALT_MASK)
#define CAN_MCR_RFEN_MASK                        (0x20000000U)
#define CAN_MCR_RFEN_SHIFT                       (29U)
#define CAN_MCR_RFEN(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_MCR_RFEN_SHIFT)) & CAN_MCR_RFEN_MASK)
#define CAN_MCR_FRZ_MASK                         (0x40000000U)
#define CAN_MCR_FRZ_SHIFT                        (30U)
#define CAN_MCR_FRZ(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_MCR_FRZ_SHIFT)) & CAN_MCR_FRZ_MASK)
#define CAN_MCR_MDIS_MASK                        (0x80000000U)
#define CAN_MCR_MDIS_SHIFT                       (31U)
#define CAN_MCR_MDIS(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_MCR_MDIS_SHIFT)) & CAN_MCR_MDIS_MASK)

/*! @name CTRL1 - Control 1 register */
#define CAN_CTRL1_PROPSEG_MASK                   (0x7U)
#define CAN_CTRL1_PROPSEG_SHIFT                  (0U)
#define CAN_CTRL1_PROPSEG(x)                     (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_PROPSEG_SHIFT)) & CAN_CTRL1_PROPSEG_MASK)
#define CAN_CTRL1_LOM_MASK                       (0x8U)
#define CAN_CTRL1_LOM_SHIFT                      (3U)
#define CAN_CTRL1_LOM(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_LOM_SHIFT)) & CAN_CTRL1_LOM_MASK)
#define CAN_CTRL1_LBUF_MASK                      (0x10U)
#define CAN_CTRL1_LBUF_SHIFT                     (4U)
#define CAN_CTRL1_LBUF(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_LBUF_SHIFT)) & CAN_CTRL1_LBUF_MASK)
#define CAN_CTRL1_TSYN_MASK                      (0x20U)
#define CAN_CTRL1_TSYN_SHIFT                     (5U)
#define CAN_CTRL1_TSYN(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_TSYN_SHIFT)) & CAN_CTRL1_TSYN_MASK)
#define CAN_CTRL1_BOFFREC_MASK                   (0x40U)
#define CAN_CTRL1_BOFFREC_SHIFT                  (6U)
#define CAN_CTRL1_BOFFREC(x)                     (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_BOFFREC_SHIFT)) & CAN_CTRL1_BOFFREC_MASK)
#define CAN_CTRL1_SMP_MASK                       (0x80U)
#define CAN_CTRL1_SMP_SHIFT                      (7U)
#define CAN_CTRL1_SMP(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_SMP_SHIFT)) & CAN_CTRL1_SMP_MASK)
#define CAN_CTRL1_RWRNMSK_MASK                   (0x400U)
#define CAN_CTRL1_RWRNMSK_SHIFT                  (10U)
#define CAN_CTRL1_RWRNMSK(x)                     (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_RWRNMSK_SHIFT)) & CAN_CTRL1_RWRNMSK_MASK)
#define CAN_CTRL1_TWRNMSK_MASK                   (0x800U)
#define CAN_CTRL1_TWRNMSK_SHIFT                  (11U)
#define CAN_CTRL1_TWRNMSK(x)                     (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_TWRNMSK_SHIFT)) & CAN_CTRL1_TWRNMSK_MASK)
#define CAN_CTRL1_LPB_MASK                       (0x1000U)
#define CAN_CTRL1_LPB_SHIFT                      (12U)
#define CAN_CTRL1_LPB(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_LPB_SHIFT)) & CAN_CTRL1_LPB_MASK)
#define CAN_CTRL1_CLKSRC_MASK                    (0x2000U)
#define CAN_CTRL1_CLKSRC_SHIFT                   (13U)
#define CAN_CTRL1_CLKSRC(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_CLKSRC_SHIFT)) & CAN_CTRL1_CLKSRC_MASK)
#define CAN_CTRL1_ERRMSK_MASK                    (0x4000U)
#define CAN_CTRL1_ERRMSK_SHIFT                   (14U)
#define CAN_CTRL1_ERRMSK(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_ERRMSK_SHIFT)) & CAN_CTRL1_ERRMSK_MASK)
#define CAN_CTRL1_BOFFMSK_MASK                   (0x8000U)
#define CAN_CTRL1_BOFFMSK_SHIFT                  (15U)
#define CAN_CTRL1_BOFFMSK(x)                     (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_BOFFMSK_SHIFT)) & CAN_CTRL1_BOFFMSK_MASK)
#define CAN_CTRL1_PSEG2_MASK                     (0x70000U)
#define CAN_CTRL1_PSEG2_SHIFT                    (16U)
#define CAN_CTRL1_PSEG2(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_PSEG2_SHIFT)) & CAN_CTRL1_PSEG2_MASK)
#define CAN_CTRL1_PSEG1_MASK                     (0x380000U)
#define CAN_CTRL1_PSEG1_SHIFT                    (19U)
#define CAN_CTRL1_PSEG1(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_PSEG1_SHIFT)) & CAN_CTRL1_PSEG1_MASK)
#define CAN_CTRL1_RJW_MASK                       (0xC00000U)
#define CAN_CTRL1_RJW_SHIFT                      (22U)
#define CAN_CTRL1_RJW(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_RJW_SHIFT)) & CAN_CTRL1_RJW_MASK)
#define CAN_CTRL1_PRESDIV_MASK                   (0xFF000000U)
#define CAN_CTRL1_PRESDIV_SHIFT                  (24U)
#define CAN_CTRL1_PRESDIV(x)                     (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_PRESDIV_SHIFT)) & CAN_CTRL1_PRESDIV_MASK)

/*! @name TIMER - Free Running Timer */
#define CAN_TIMER_TIMER_MASK                     (0xFFFFU)
#define CAN_TIMER_TIMER_SHIFT                    (0U)
#define CAN_TIMER_TIMER(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_TIMER_TIMER_SHIFT)) & CAN_TIMER_TIMER_MASK)

/*! @name RXMGMASK - Rx Mailboxes Global Mask Register */
#define CAN_RXMGMASK_MG_MASK                     (0xFFFFFFFFU)
#define CAN_RXMGMASK_MG_SHIFT                    (0U)
#define CAN_RXMGMASK_MG(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_RXMGMASK_MG_SHIFT)) & CAN_RXMGMASK_MG_MASK)

/*! @name RX14MASK - Rx 14 Mask register */
#define CAN_RX14MASK_RX14M_MASK                  (0xFFFFFFFFU)
#define CAN_RX14MASK_RX14M_SHIFT                 (0U)
#define CAN_RX14MASK_RX14M(x)                    (((uint32_t)(((uint32_t)(x)) << CAN_RX14MASK_RX14M_SHIFT)) & CAN_RX14MASK_RX14M_MASK)

/*! @name RX15MASK - Rx 15 Mask register */
#define CAN_RX15MASK_RX15M_MASK                  (0xFFFFFFFFU)
#define CAN_RX15MASK_RX15M_SHIFT                 (0U)
#define CAN_RX15MASK_RX15M(x)                    (((uint32_t)(((uint32_t)(x)) << CAN_RX15MASK_RX15M_SHIFT)) & CAN_RX15MASK_RX15M_MASK)

/*! @name ECR - Error Counter */
#define CAN_ECR_TXERRCNT_MASK                    (0xFFU)
#define CAN_ECR_TXERRCNT_SHIFT                   (0U)
#define CAN_ECR_TXERRCNT(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_ECR_TXERRCNT_SHIFT)) & CAN_ECR_TXERRCNT_MASK)
#define CAN_ECR_RXERRCNT_MASK                    (0xFF00U)
#define CAN_ECR_RXERRCNT_SHIFT                   (8U)
#define CAN_ECR_RXERRCNT(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_ECR_RXERRCNT_SHIFT)) & CAN_ECR_RXERRCNT_MASK)

/*! @name ESR1 - Error and Status 1 register */
#define CAN_ESR1_WAKINT_MASK                     (0x1U)
#define CAN_ESR1_WAKINT_SHIFT                    (0U)
#define CAN_ESR1_WAKINT(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_WAKINT_SHIFT)) & CAN_ESR1_WAKINT_MASK)
#define CAN_ESR1_ERRINT_MASK                     (0x2U)
#define CAN_ESR1_ERRINT_SHIFT                    (1U)
#define CAN_ESR1_ERRINT(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_ERRINT_SHIFT)) & CAN_ESR1_ERRINT_MASK)
#define CAN_ESR1_BOFFINT_MASK                    (0x4U)
#define CAN_ESR1_BOFFINT_SHIFT                   (2U)
#define CAN_ESR1_BOFFINT(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_BOFFINT_SHIFT)) & CAN_ESR1_BOFFINT_MASK)
#define CAN_ESR1_RX_MASK                         (0x8U)
#define CAN_ESR1_RX_SHIFT                        (3U)
#define CAN_ESR1_RX(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_RX_SHIFT)) & CAN_ESR1_RX_MASK)
#define CAN_ESR1_FLTCONF_MASK                    (0x30U)
#define CAN_ESR1_FLTCONF_SHIFT                   (4U)
#define CAN_ESR1_FLTCONF(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_FLTCONF_SHIFT)) & CAN_ESR1_FLTCONF_MASK)
#define CAN_ESR1_TX_MASK                         (0x40U)
#define CAN_ESR1_TX_SHIFT                        (6U)
#define CAN_ESR1_TX(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_TX_SHIFT)) & CAN_ESR1_TX_MASK)
#define CAN_ESR1_IDLE_MASK                       (0x80U)
#define CAN_ESR1_IDLE_SHIFT                      (7U)
#define CAN_ESR1_IDLE(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_IDLE_SHIFT)) & CAN_ESR1_IDLE_MASK)
#define CAN_ESR1_RXWRN_MASK                      (0x100U)
#define CAN_ESR1_RXWRN_SHIFT                     (8U)
#define CAN_ESR1_RXWRN(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_RXWRN_SHIFT)) & CAN_ESR1_RXWRN_MASK)
#define CAN_ESR1_TXWRN_MASK                      (0x200U)
#define CAN_ESR1_TXWRN_SHIFT                     (9U)
#define CAN_ESR1_TXWRN(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_TXWRN_SHIFT)) & CAN_ESR1_TXWRN_MASK)
#define CAN_ESR1_STFERR_MASK                     (0x400U)
#define CAN_ESR1_STFERR_SHIFT                    (10U)
#define CAN_ESR1_STFERR(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_STFERR_SHIFT)) & CAN_ESR1_STFERR_MASK)
#define CAN_ESR1_FRMERR_MASK                     (0x800U)
#define CAN_ESR1_FRMERR_SHIFT                    (11U)
#define CAN_ESR1_FRMERR(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_FRMERR_SHIFT)) & CAN_ESR1_FRMERR_MASK)
#define CAN_ESR1_CRCERR_MASK                     (0x1000U)
#define CAN_ESR1_CRCERR_SHIFT                    (12U)
#define CAN_ESR1_CRCERR(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_CRCERR_SHIFT)) & CAN_ESR1_CRCERR_MASK)
#define CAN_ESR1_ACKERR_MASK                     (0x2000U)
#define CAN_ESR1_ACKERR_SHIFT                    (13U)
#define CAN_ESR1_ACKERR(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_ACKERR_SHIFT)) & CAN_ESR1_ACKERR_MASK)
#define CAN_ESR1_BIT0ERR_MASK                    (0x4000U)
#define CAN_ESR1_BIT0ERR_SHIFT                   (14U)
#define CAN_ESR1_BIT0ERR(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_BIT0ERR_SHIFT)) & CAN_ESR1_BIT0ERR_MASK)
#define CAN_ESR1_BIT1ERR_MASK                    (0x8000U)
#define CAN_ESR1_BIT1ERR_SHIFT                   (15U)
#define CAN_ESR1_BIT1ERR(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_BIT1ERR_SHIFT)) & CAN_ESR1_BIT1ERR_MASK)
#define CAN_ESR1_RWRNINT_MASK                    (0x10000U)
#define CAN_ESR1_RWRNINT_SHIFT                   (16U)
#define CAN_ESR1_RWRNINT(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_RWRNINT_SHIFT)) & CAN_ESR1_RWRNINT_MASK)
#define CAN_ESR1_TWRNINT_MASK                    (0x20000U)
#define CAN_ESR1_TWRNINT_SHIFT                   (17U)
#define CAN_ESR1_TWRNINT(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_TWRNINT_SHIFT)) & CAN_ESR1_TWRNINT_MASK)
#define CAN_ESR1_SYNCH_MASK                      (0x40000U)
#define CAN_ESR1_SYNCH_SHIFT                     (18U)
#define CAN_ESR1_SYNCH(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_SYNCH_SHIFT)) & CAN_ESR1_SYNCH_MASK)
#define CAN_ESR1_BOFFDONEINT_MASK                (0x80000U)
#define CAN_ESR1_BOFFDONEINT_SHIFT               (19U)
#define CAN_ESR1_BOFFDONEINT(x)                  (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_BOFFDONEINT_SHIFT)) & CAN_ESR1_BOFFDONEINT_MASK)
#define CAN_ESR1_ERROVR_MASK                     (0x200000U)
#define CAN_ESR1_ERROVR_SHIFT                    (21U)
#define CAN_ESR1_ERROVR(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_ERROVR_SHIFT)) & CAN_ESR1_ERROVR_MASK)

/*! @name IMASK1 - Interrupt Masks 1 register */
#define CAN_IMASK1_BUF31TO0M_MASK                (0xFFFFFFFFU)
#define CAN_IMASK1_BUF31TO0M_SHIFT               (0U)
#define CAN_IMASK1_BUF31TO0M(x)                  (((uint32_t)(((uint32_t)(x)) << CAN_IMASK1_BUF31TO0M_SHIFT)) & CAN_IMASK1_BUF31TO0M_MASK)

/*! @name IFLAG1 - Interrupt Flags 1 register */
#define CAN_IFLAG1_BUF0I_MASK                    (0x1U)
#define CAN_IFLAG1_BUF0I_SHIFT                   (0U)
#define CAN_IFLAG1_BUF0I(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_IFLAG1_BUF0I_SHIFT)) & CAN_IFLAG1_BUF0I_MASK)
#define CAN_IFLAG1_BUF4TO1I_MASK                 (0x1EU)
#define CAN_IFLAG1_BUF4TO1I_SHIFT                (1U)
#define CAN_IFLAG1_BUF4TO1I(x)                   (((uint32_t)(((uint32_t)(x)) << CAN_IFLAG1_BUF4TO1I_SHIFT)) & CAN_IFLAG1_BUF4TO1I_MASK)
#define CAN_IFLAG1_BUF5I_MASK                    (0x20U)
#define CAN_IFLAG1_BUF5I_SHIFT                   (5U)
#define CAN_IFLAG1_BUF5I(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_IFLAG1_BUF5I_SHIFT)) & CAN_IFLAG1_BUF5I_MASK)
#define CAN_IFLAG1_BUF6I_MASK                    (0x40U)
#define CAN_IFLAG1_BUF6I_SHIFT                   (6U)
#define CAN_IFLAG1_BUF6I(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_IFLAG1_BUF6I_SHIFT)) & CAN_IFLAG1_BUF6I_MASK)
#define CAN_IFLAG1_BUF7I_MASK                    (0x80U)
#define CAN_IFLAG1_BUF7I_SHIFT                   (7U)
#define CAN_IFLAG1_BUF7I(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_IFLAG1_BUF7I_SHIFT)) & CAN_IFLAG1_BUF7I_MASK)
#define CAN_IFLAG1_BUF31TO8I_MASK                (0xFFFFFF00U)
#define CAN_IFLAG1_BUF31TO8I_SHIFT               (8U)
#define CAN_IFLAG1_BUF31TO8I(x)                  (((uint32_t)(((uint32_t)(x)) << CAN_IFLAG1_BUF31TO8I_SHIFT)) & CAN_IFLAG1_BUF31TO8I_MASK)

/*! @name CTRL2 - Control 2 register */
#define CAN_CTRL2_EACEN_MASK                     (0x10000U)
#define CAN_CTRL2_EACEN_SHIFT                    (16U)
#define CAN_CTRL2_EACEN(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_EACEN_SHIFT)) & CAN_CTRL2_EACEN_MASK)
#define CAN_CTRL2_RRS_MASK                       (0x20000U)
#define CAN_CTRL2_RRS_SHIFT                      (17U)
#define CAN_CTRL2_RRS(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_RRS_SHIFT)) & CAN_CTRL2_RRS_MASK)
#define CAN_CTRL2_MRP_MASK                       (0x40000U)
#define CAN_CTRL2_MRP_SHIFT                      (18U)
#define CAN_CTRL2_MRP(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_MRP_SHIFT)) & CAN_CTRL2_MRP_MASK)
#define CAN_CTRL2_TASD_MASK                      (0xF80000U)
#define CAN_CTRL2_TASD_SHIFT                     (19U)
#define CAN_CTRL2_TASD(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_TASD_SHIFT)) & CAN_CTRL2_TASD_MASK)
#define CAN_CTRL2_RFFN_MASK                      (0xF000000U)
#define CAN_CTRL2_RFFN_SHIFT                     (24U)
#define CAN_CTRL2_RFFN(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_RFFN_SHIFT)) & CAN_CTRL2_RFFN_MASK)
#define CAN_CTRL2_BOFFDONEMSK_MASK               (0x40000000U)
#define CAN_CTRL2_BOFFDONEMSK_SHIFT              (30U)
#define CAN_CTRL2_BOFFDONEMSK(x)                 (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_BOFFDONEMSK_SHIFT)) & CAN_CTRL2_BOFFDONEMSK_MASK)

/*! @name ESR2 - Error and Status 2 register */
#define CAN_ESR2_IMB_MASK                        (0x2000U)
#define CAN_ESR2_IMB_SHIFT                       (13U)
#define CAN_ESR2_IMB(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ESR2_IMB_SHIFT)) & CAN_ESR2_IMB_MASK)
#define CAN_ESR2_VPS_MASK                        (0x4000U)
#define CAN_ESR2_VPS_SHIFT                       (14U)
#define CAN_ESR2_VPS(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ESR2_VPS_SHIFT)) & CAN_ESR2_VPS_MASK)
#define CAN_ESR2_LPTM_MASK                       (0x7F0000U)
#define CAN_ESR2_LPTM_SHIFT                      (16U)
#define CAN_ESR2_LPTM(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ESR2_LPTM_SHIFT)) & CAN_ESR2_LPTM_MASK)

/*! @name CRCR - CRC Register */
#define CAN_CRCR_TXCRC_MASK                      (0x7FFFU)
#define CAN_CRCR_TXCRC_SHIFT                     (0U)
#define CAN_CRCR_TXCRC(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_CRCR_TXCRC_SHIFT)) & CAN_CRCR_TXCRC_MASK)
#define CAN_CRCR_MBCRC_MASK                      (0x7F0000U)
#define CAN_CRCR_MBCRC_SHIFT                     (16U)
#define CAN_CRCR_MBCRC(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_CRCR_MBCRC_SHIFT)) & CAN_CRCR_MBCRC_MASK)

/*! @name RXFGMASK - Rx FIFO Global Mask register */
#define CAN_RXFGMASK_FGM_MASK                    (0xFFFFFFFFU)
#define CAN_RXFGMASK_FGM_SHIFT                   (0U)
#define CAN_RXFGMASK_FGM(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_RXFGMASK_FGM_SHIFT)) & CAN_RXFGMASK_FGM_MASK)

/*! @name RXFIR - Rx FIFO Information Register */
#define CAN_RXFIR_IDHIT_MASK                     (0x1FFU)
#define CAN_RXFIR_IDHIT_SHIFT                    (0U)
#define CAN_RXFIR_IDHIT(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_RXFIR_IDHIT_SHIFT)) & CAN_RXFIR_IDHIT_MASK)

/*! @name CBT - CAN Bit Timing Register */
#define CAN_CBT_EPSEG2_MASK                      (0x1FU)
#define CAN_CBT_EPSEG2_SHIFT                     (0U)
#define CAN_CBT_EPSEG2(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_CBT_EPSEG2_SHIFT)) & CAN_CBT_EPSEG2_MASK)
#define CAN_CBT_EPSEG1_MASK                      (0x3E0U)
#define CAN_CBT_EPSEG1_SHIFT                     (5U)
#define CAN_CBT_EPSEG1(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_CBT_EPSEG1_SHIFT)) & CAN_CBT_EPSEG1_MASK)
#define CAN_CBT_EPROPSEG_MASK                    (0xFC00U)
#define CAN_CBT_EPROPSEG_SHIFT                   (10U)
#define CAN_CBT_EPROPSEG(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_CBT_EPROPSEG_SHIFT)) & CAN_CBT_EPROPSEG_MASK)
#define CAN_CBT_ERJW_MASK                        (0xF0000U)
#define CAN_CBT_ERJW_SHIFT                       (16U)
#define CAN_CBT_ERJW(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CBT_ERJW_SHIFT)) & CAN_CBT_ERJW_MASK)
#define CAN_CBT_EPRESDIV_MASK                    (0x7FE00000U)
#define CAN_CBT_EPRESDIV_SHIFT                   (21U)
#define CAN_CBT_EPRESDIV(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_CBT_EPRESDIV_SHIFT)) & CAN_CBT_EPRESDIV_MASK)
#define CAN_CBT_BTF_MASK                         (0x80000000U)
#define CAN_CBT_BTF_SHIFT                        (31U)
#define CAN_CBT_BTF(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_CBT_BTF_SHIFT)) & CAN_CBT_BTF_MASK)

/*! @name CS - Message Buffer 0 CS Register..Message Buffer 15 CS Register */
#define CAN_CS_TIME_STAMP_MASK                   (0xFFFFU)
#define CAN_CS_TIME_STAMP_SHIFT                  (0U)
#define CAN_CS_TIME_STAMP(x)                     (((uint32_t)(((uint32_t)(x)) << CAN_CS_TIME_STAMP_SHIFT)) & CAN_CS_TIME_STAMP_MASK)
#define CAN_CS_DLC_MASK                          (0xF0000U)
#define CAN_CS_DLC_SHIFT                         (16U)
#define CAN_CS_DLC(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_CS_DLC_SHIFT)) & CAN_CS_DLC_MASK)
#define CAN_CS_RTR_MASK                          (0x100000U)
#define CAN_CS_RTR_SHIFT                         (20U)
#define CAN_CS_RTR(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_CS_RTR_SHIFT)) & CAN_CS_RTR_MASK)
#define CAN_CS_IDE_MASK                          (0x200000U)
#define CAN_CS_IDE_SHIFT                         (21U)
#define CAN_CS_IDE(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_CS_IDE_SHIFT)) & CAN_CS_IDE_MASK)
#define CAN_CS_SRR_MASK                          (0x400000U)
#define CAN_CS_SRR_SHIFT                         (22U)
#define CAN_CS_SRR(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_CS_SRR_SHIFT)) & CAN_CS_SRR_MASK)
#define CAN_CS_CODE_MASK                         (0xF000000U)
#define CAN_CS_CODE_SHIFT                        (24U)
#define CAN_CS_CODE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_CS_CODE_SHIFT)) & CAN_CS_CODE_MASK)
#define CAN_CS_ESI_MASK                          (0x20000000U)
#define CAN_CS_ESI_SHIFT                         (29U)
#define CAN_CS_ESI(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_CS_ESI_SHIFT)) & CAN_CS_ESI_MASK)
#define CAN_CS_BRS_MASK                          (0x40000000U)
#define CAN_CS_BRS_SHIFT                         (30U)
#define CAN_CS_BRS(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_CS_BRS_SHIFT)) & CAN_CS_BRS_MASK)
#define CAN_CS_EDL_MASK                          (0x80000000U)
#define CAN_CS_EDL_SHIFT                         (31U)
#define CAN_CS_EDL(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_CS_EDL_SHIFT)) & CAN_CS_EDL_MASK)

/* The count of CAN_CS */
#define CAN_CS_COUNT                             (16U)

/*! @name ID - Message Buffer 0 ID Register..Message Buffer 15 ID Register */
#define CAN_ID_EXT_MASK                          (0x3FFFFU)
#define CAN_ID_EXT_SHIFT                         (0U)
#define CAN_ID_EXT(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_ID_EXT_SHIFT)) & CAN_ID_EXT_MASK)
#define CAN_ID_STD_MASK                          (0x1FFC0000U)
#define CAN_ID_STD_SHIFT                         (18U)
#define CAN_ID_STD(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_ID_STD_SHIFT)) & CAN_ID_STD_MASK)
#define CAN_ID_PRIO_MASK                         (0xE0000000U)
#define CAN_ID_PRIO_SHIFT                        (29U)
#define CAN_ID_PRIO(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ID_PRIO_SHIFT)) & CAN_ID_PRIO_MASK)

/* The count of CAN_ID */
#define CAN_ID_COUNT                             (16U)

/*! @name WORD0 - Message Buffer 0 WORD0 Register..Message Buffer 15 WORD0 Register */
#define CAN_WORD0_DATA_BYTE_3_MASK               (0xFFU)
#define CAN_WORD0_DATA_BYTE_3_SHIFT              (0U)
#define CAN_WORD0_DATA_BYTE_3(x)                 (((uint32_t)(((uint32_t)(x)) << CAN_WORD0_DATA_BYTE_3_SHIFT)) & CAN_WORD0_DATA_BYTE_3_MASK)
#define CAN_WORD0_DATA_BYTE_2_MASK               (0xFF00U)
#define CAN_WORD0_DATA_BYTE_2_SHIFT              (8U)
#define CAN_WORD0_DATA_BYTE_2(x)                 (((uint32_t)(((uint32_t)(x)) << CAN_WORD0_DATA_BYTE_2_SHIFT)) & CAN_WORD0_DATA_BYTE_2_MASK)
#define CAN_WORD0_DATA_BYTE_1_MASK               (0xFF0000U)
#define CAN_WORD0_DATA_BYTE_1_SHIFT              (16U)
#define CAN_WORD0_DATA_BYTE_1(x)                 (((uint32_t)(((uint32_t)(x)) << CAN_WORD0_DATA_BYTE_1_SHIFT)) & CAN_WORD0_DATA_BYTE_1_MASK)
#define CAN_WORD0_DATA_BYTE_0_MASK               (0xFF000000U)
#define CAN_WORD0_DATA_BYTE_0_SHIFT              (24U)
#define CAN_WORD0_DATA_BYTE_0(x)                 (((uint32_t)(((uint32_t)(x)) << CAN_WORD0_DATA_BYTE_0_SHIFT)) & CAN_WORD0_DATA_BYTE_0_MASK)

/* The count of CAN_WORD0 */
#define CAN_WORD0_COUNT                          (16U)

/*! @name WORD1 - Message Buffer 0 WORD1 Register..Message Buffer 15 WORD1 Register */
#define CAN_WORD1_DATA_BYTE_7_MASK               (0xFFU)
#define CAN_WORD1_DATA_BYTE_7_SHIFT              (0U)
#define CAN_WORD1_DATA_BYTE_7(x)                 (((uint32_t)(((uint32_t)(x)) << CAN_WORD1_DATA_BYTE_7_SHIFT)) & CAN_WORD1_DATA_BYTE_7_MASK)
#define CAN_WORD1_DATA_BYTE_6_MASK               (0xFF00U)
#define CAN_WORD1_DATA_BYTE_6_SHIFT              (8U)
#define CAN_WORD1_DATA_BYTE_6(x)                 (((uint32_t)(((uint32_t)(x)) << CAN_WORD1_DATA_BYTE_6_SHIFT)) & CAN_WORD1_DATA_BYTE_6_MASK)
#define CAN_WORD1_DATA_BYTE_5_MASK               (0xFF0000U)
#define CAN_WORD1_DATA_BYTE_5_SHIFT              (16U)
#define CAN_WORD1_DATA_BYTE_5(x)                 (((uint32_t)(((uint32_t)(x)) << CAN_WORD1_DATA_BYTE_5_SHIFT)) & CAN_WORD1_DATA_BYTE_5_MASK)
#define CAN_WORD1_DATA_BYTE_4_MASK               (0xFF000000U)
#define CAN_WORD1_DATA_BYTE_4_SHIFT              (24U)
#define CAN_WORD1_DATA_BYTE_4(x)                 (((uint32_t)(((uint32_t)(x)) << CAN_WORD1_DATA_BYTE_4_SHIFT)) & CAN_WORD1_DATA_BYTE_4_MASK)

/* The count of CAN_WORD1 */
#define CAN_WORD1_COUNT                          (16U)

/*! @name RXIMR - Rx Individual Mask Registers */
#define CAN_RXIMR_MI_MASK                        (0xFFFFFFFFU)
#define CAN_RXIMR_MI_SHIFT                       (0U)
#define CAN_RXIMR_MI(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_RXIMR_MI_SHIFT)) & CAN_RXIMR_MI_MASK)

/* The count of CAN_RXIMR */
#define CAN_RXIMR_COUNT                          (16U)


/*!
 * @}
 */ /* end of group CAN_Register_Masks */


/* CAN - Peripheral instance base addresses */
/** Peripheral CAN0 base address */
#define CAN0_BASE                                (0x40024000u)
/** Peripheral CAN0 base pointer */
#define CAN0                                     ((CAN_Type *)CAN0_BASE)
/** Peripheral CAN1 base address */
#define CAN1_BASE                                (0x40025000u)
/** Peripheral CAN1 base pointer */
#define CAN1                                     ((CAN_Type *)CAN1_BASE)
/** Peripheral CAN2 base address */
#define CAN2_BASE                                (0x400A4000u)
/** Peripheral CAN2 base pointer */
#define CAN2                                     ((CAN_Type *)CAN2_BASE)
/** Array initializer of CAN peripheral base addresses */
#define CAN_BASE_ADDRS                           { CAN0_BASE, CAN1_BASE, CAN2_BASE }
/** Array initializer of CAN peripheral base pointers */
#define CAN_BASE_PTRS                            { CAN0, CAN1, CAN2 }
/** Interrupt vectors for the CAN peripheral type */
#define CAN_Rx_Warning_IRQS                      { CAN0_Rx_Warning_IRQn, CAN1_Rx_Warning_IRQn, CAN2_Rx_Warning_IRQn }
#define CAN_Tx_Warning_IRQS                      { CAN0_Tx_Warning_IRQn, CAN1_Tx_Warning_IRQn, CAN2_Tx_Warning_IRQn }
#define CAN_Wake_Up_IRQS                         { CAN0_Wake_Up_IRQn, CAN1_Wake_Up_IRQn, CAN2_Wake_Up_IRQn }
#define CAN_Error_IRQS                           { CAN0_Error_IRQn, CAN1_Error_IRQn, CAN2_Error_IRQn }
#define CAN_Bus_Off_IRQS                         { CAN0_Bus_Off_IRQn, CAN1_Bus_Off_IRQn, CAN2_Bus_Off_IRQn }
#define CAN_ORed_Message_buffer_IRQS             { CAN0_ORed_Message_buffer_IRQn, CAN1_ORed_Message_buffer_IRQn, CAN2_ORed_Message_buffer_IRQn }
#define CAN_IMASK1_BUFLM_MASK                    CAN_IMASK1_BUF31TO0M_MASK
#define CAN_IMASK1_BUFLM_SHIFT                   CAN_IMASK1_BUF31TO0M_SHIFT
#define CAN_IMASK1_BUFLM_WIDTH                   CAN_IMASK1_BUF31TO0M_WIDTH
#define CAN_IMASK1_BUFLM(x)                      CAN_IMASK1_BUF31TO0M(x)


/*!
 * @}
 */ /* end of group CAN_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- CAU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAU_Peripheral_Access_Layer CAU Peripheral Access Layer
 * @{
 */

/** CAU - Register Layout Typedef */
typedef struct {
  __O  uint32_t DIRECT[16];                        /**< Direct access register 0..Direct access register 15, array offset: 0x0, array step: 0x4 */
       uint8_t RESERVED_0[2048];
  __O  uint32_t LDR_CASR;                          /**< Status register - Load Register command, offset: 0x840 */
  __O  uint32_t LDR_CAA;                           /**< Accumulator register - Load Register command, offset: 0x844 */
  __O  uint32_t LDR_CA[9];                         /**< General Purpose Register 0 - Load Register command..General Purpose Register 8 - Load Register command, array offset: 0x848, array step: 0x4 */
       uint8_t RESERVED_1[20];
  __I  uint32_t STR_CASR;                          /**< Status register - Store Register command, offset: 0x880 */
  __I  uint32_t STR_CAA;                           /**< Accumulator register - Store Register command, offset: 0x884 */
  __I  uint32_t STR_CA[9];                         /**< General Purpose Register 0 - Store Register command..General Purpose Register 8 - Store Register command, array offset: 0x888, array step: 0x4 */
       uint8_t RESERVED_2[20];
  __O  uint32_t ADR_CASR;                          /**< Status register - Add Register command, offset: 0x8C0 */
  __O  uint32_t ADR_CAA;                           /**< Accumulator register - Add to register command, offset: 0x8C4 */
  __O  uint32_t ADR_CA[9];                         /**< General Purpose Register 0 - Add to register command..General Purpose Register 8 - Add to register command, array offset: 0x8C8, array step: 0x4 */
       uint8_t RESERVED_3[20];
  __O  uint32_t RADR_CASR;                         /**< Status register - Reverse and Add to Register command, offset: 0x900 */
  __O  uint32_t RADR_CAA;                          /**< Accumulator register - Reverse and Add to Register command, offset: 0x904 */
  __O  uint32_t RADR_CA[9];                        /**< General Purpose Register 0 - Reverse and Add to Register command..General Purpose Register 8 - Reverse and Add to Register command, array offset: 0x908, array step: 0x4 */
       uint8_t RESERVED_4[84];
  __O  uint32_t XOR_CASR;                          /**< Status register - Exclusive Or command, offset: 0x980 */
  __O  uint32_t XOR_CAA;                           /**< Accumulator register - Exclusive Or command, offset: 0x984 */
  __O  uint32_t XOR_CA[9];                         /**< General Purpose Register 0 - Exclusive Or command..General Purpose Register 8 - Exclusive Or command, array offset: 0x988, array step: 0x4 */
       uint8_t RESERVED_5[20];
  __O  uint32_t ROTL_CASR;                         /**< Status register - Rotate Left command, offset: 0x9C0 */
  __O  uint32_t ROTL_CAA;                          /**< Accumulator register - Rotate Left command, offset: 0x9C4 */
  __O  uint32_t ROTL_CA[9];                        /**< General Purpose Register 0 - Rotate Left command..General Purpose Register 8 - Rotate Left command, array offset: 0x9C8, array step: 0x4 */
       uint8_t RESERVED_6[276];
  __O  uint32_t AESC_CASR;                         /**< Status register - AES Column Operation command, offset: 0xB00 */
  __O  uint32_t AESC_CAA;                          /**< Accumulator register - AES Column Operation command, offset: 0xB04 */
  __O  uint32_t AESC_CA[9];                        /**< General Purpose Register 0 - AES Column Operation command..General Purpose Register 8 - AES Column Operation command, array offset: 0xB08, array step: 0x4 */
       uint8_t RESERVED_7[20];
  __O  uint32_t AESIC_CASR;                        /**< Status register - AES Inverse Column Operation command, offset: 0xB40 */
  __O  uint32_t AESIC_CAA;                         /**< Accumulator register - AES Inverse Column Operation command, offset: 0xB44 */
  __O  uint32_t AESIC_CA[9];                       /**< General Purpose Register 0 - AES Inverse Column Operation command..General Purpose Register 8 - AES Inverse Column Operation command, array offset: 0xB48, array step: 0x4 */
} CAU_Type;

/* ----------------------------------------------------------------------------
   -- CAU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAU_Register_Masks CAU Register Masks
 * @{
 */

/*! @name DIRECT - Direct access register 0..Direct access register 15 */
#define CAU_DIRECT_CAU_DIRECT0_MASK              (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT0_SHIFT             (0U)
#define CAU_DIRECT_CAU_DIRECT0(x)                (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT0_SHIFT)) & CAU_DIRECT_CAU_DIRECT0_MASK)
#define CAU_DIRECT_CAU_DIRECT1_MASK              (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT1_SHIFT             (0U)
#define CAU_DIRECT_CAU_DIRECT1(x)                (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT1_SHIFT)) & CAU_DIRECT_CAU_DIRECT1_MASK)
#define CAU_DIRECT_CAU_DIRECT2_MASK              (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT2_SHIFT             (0U)
#define CAU_DIRECT_CAU_DIRECT2(x)                (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT2_SHIFT)) & CAU_DIRECT_CAU_DIRECT2_MASK)
#define CAU_DIRECT_CAU_DIRECT3_MASK              (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT3_SHIFT             (0U)
#define CAU_DIRECT_CAU_DIRECT3(x)                (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT3_SHIFT)) & CAU_DIRECT_CAU_DIRECT3_MASK)
#define CAU_DIRECT_CAU_DIRECT4_MASK              (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT4_SHIFT             (0U)
#define CAU_DIRECT_CAU_DIRECT4(x)                (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT4_SHIFT)) & CAU_DIRECT_CAU_DIRECT4_MASK)
#define CAU_DIRECT_CAU_DIRECT5_MASK              (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT5_SHIFT             (0U)
#define CAU_DIRECT_CAU_DIRECT5(x)                (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT5_SHIFT)) & CAU_DIRECT_CAU_DIRECT5_MASK)
#define CAU_DIRECT_CAU_DIRECT6_MASK              (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT6_SHIFT             (0U)
#define CAU_DIRECT_CAU_DIRECT6(x)                (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT6_SHIFT)) & CAU_DIRECT_CAU_DIRECT6_MASK)
#define CAU_DIRECT_CAU_DIRECT7_MASK              (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT7_SHIFT             (0U)
#define CAU_DIRECT_CAU_DIRECT7(x)                (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT7_SHIFT)) & CAU_DIRECT_CAU_DIRECT7_MASK)
#define CAU_DIRECT_CAU_DIRECT8_MASK              (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT8_SHIFT             (0U)
#define CAU_DIRECT_CAU_DIRECT8(x)                (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT8_SHIFT)) & CAU_DIRECT_CAU_DIRECT8_MASK)
#define CAU_DIRECT_CAU_DIRECT9_MASK              (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT9_SHIFT             (0U)
#define CAU_DIRECT_CAU_DIRECT9(x)                (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT9_SHIFT)) & CAU_DIRECT_CAU_DIRECT9_MASK)
#define CAU_DIRECT_CAU_DIRECT10_MASK             (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT10_SHIFT            (0U)
#define CAU_DIRECT_CAU_DIRECT10(x)               (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT10_SHIFT)) & CAU_DIRECT_CAU_DIRECT10_MASK)
#define CAU_DIRECT_CAU_DIRECT11_MASK             (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT11_SHIFT            (0U)
#define CAU_DIRECT_CAU_DIRECT11(x)               (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT11_SHIFT)) & CAU_DIRECT_CAU_DIRECT11_MASK)
#define CAU_DIRECT_CAU_DIRECT12_MASK             (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT12_SHIFT            (0U)
#define CAU_DIRECT_CAU_DIRECT12(x)               (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT12_SHIFT)) & CAU_DIRECT_CAU_DIRECT12_MASK)
#define CAU_DIRECT_CAU_DIRECT13_MASK             (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT13_SHIFT            (0U)
#define CAU_DIRECT_CAU_DIRECT13(x)               (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT13_SHIFT)) & CAU_DIRECT_CAU_DIRECT13_MASK)
#define CAU_DIRECT_CAU_DIRECT14_MASK             (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT14_SHIFT            (0U)
#define CAU_DIRECT_CAU_DIRECT14(x)               (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT14_SHIFT)) & CAU_DIRECT_CAU_DIRECT14_MASK)
#define CAU_DIRECT_CAU_DIRECT15_MASK             (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT15_SHIFT            (0U)
#define CAU_DIRECT_CAU_DIRECT15(x)               (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT15_SHIFT)) & CAU_DIRECT_CAU_DIRECT15_MASK)

/* The count of CAU_DIRECT */
#define CAU_DIRECT_COUNT                         (16U)

/*! @name LDR_CASR - Status register - Load Register command */
#define CAU_LDR_CASR_IC_MASK                     (0x1U)
#define CAU_LDR_CASR_IC_SHIFT                    (0U)
#define CAU_LDR_CASR_IC(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CASR_IC_SHIFT)) & CAU_LDR_CASR_IC_MASK)
#define CAU_LDR_CASR_DPE_MASK                    (0x2U)
#define CAU_LDR_CASR_DPE_SHIFT                   (1U)
#define CAU_LDR_CASR_DPE(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CASR_DPE_SHIFT)) & CAU_LDR_CASR_DPE_MASK)
#define CAU_LDR_CASR_VER_MASK                    (0xF0000000U)
#define CAU_LDR_CASR_VER_SHIFT                   (28U)
#define CAU_LDR_CASR_VER(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CASR_VER_SHIFT)) & CAU_LDR_CASR_VER_MASK)

/*! @name LDR_CAA - Accumulator register - Load Register command */
#define CAU_LDR_CAA_ACC_MASK                     (0xFFFFFFFFU)
#define CAU_LDR_CAA_ACC_SHIFT                    (0U)
#define CAU_LDR_CAA_ACC(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CAA_ACC_SHIFT)) & CAU_LDR_CAA_ACC_MASK)

/*! @name LDR_CA - General Purpose Register 0 - Load Register command..General Purpose Register 8 - Load Register command */
#define CAU_LDR_CA_CA0_MASK                      (0xFFFFFFFFU)
#define CAU_LDR_CA_CA0_SHIFT                     (0U)
#define CAU_LDR_CA_CA0(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA0_SHIFT)) & CAU_LDR_CA_CA0_MASK)
#define CAU_LDR_CA_CA1_MASK                      (0xFFFFFFFFU)
#define CAU_LDR_CA_CA1_SHIFT                     (0U)
#define CAU_LDR_CA_CA1(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA1_SHIFT)) & CAU_LDR_CA_CA1_MASK)
#define CAU_LDR_CA_CA2_MASK                      (0xFFFFFFFFU)
#define CAU_LDR_CA_CA2_SHIFT                     (0U)
#define CAU_LDR_CA_CA2(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA2_SHIFT)) & CAU_LDR_CA_CA2_MASK)
#define CAU_LDR_CA_CA3_MASK                      (0xFFFFFFFFU)
#define CAU_LDR_CA_CA3_SHIFT                     (0U)
#define CAU_LDR_CA_CA3(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA3_SHIFT)) & CAU_LDR_CA_CA3_MASK)
#define CAU_LDR_CA_CA4_MASK                      (0xFFFFFFFFU)
#define CAU_LDR_CA_CA4_SHIFT                     (0U)
#define CAU_LDR_CA_CA4(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA4_SHIFT)) & CAU_LDR_CA_CA4_MASK)
#define CAU_LDR_CA_CA5_MASK                      (0xFFFFFFFFU)
#define CAU_LDR_CA_CA5_SHIFT                     (0U)
#define CAU_LDR_CA_CA5(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA5_SHIFT)) & CAU_LDR_CA_CA5_MASK)
#define CAU_LDR_CA_CA6_MASK                      (0xFFFFFFFFU)
#define CAU_LDR_CA_CA6_SHIFT                     (0U)
#define CAU_LDR_CA_CA6(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA6_SHIFT)) & CAU_LDR_CA_CA6_MASK)
#define CAU_LDR_CA_CA7_MASK                      (0xFFFFFFFFU)
#define CAU_LDR_CA_CA7_SHIFT                     (0U)
#define CAU_LDR_CA_CA7(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA7_SHIFT)) & CAU_LDR_CA_CA7_MASK)
#define CAU_LDR_CA_CA8_MASK                      (0xFFFFFFFFU)
#define CAU_LDR_CA_CA8_SHIFT                     (0U)
#define CAU_LDR_CA_CA8(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA8_SHIFT)) & CAU_LDR_CA_CA8_MASK)

/* The count of CAU_LDR_CA */
#define CAU_LDR_CA_COUNT                         (9U)

/*! @name STR_CASR - Status register - Store Register command */
#define CAU_STR_CASR_IC_MASK                     (0x1U)
#define CAU_STR_CASR_IC_SHIFT                    (0U)
#define CAU_STR_CASR_IC(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_STR_CASR_IC_SHIFT)) & CAU_STR_CASR_IC_MASK)
#define CAU_STR_CASR_DPE_MASK                    (0x2U)
#define CAU_STR_CASR_DPE_SHIFT                   (1U)
#define CAU_STR_CASR_DPE(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_STR_CASR_DPE_SHIFT)) & CAU_STR_CASR_DPE_MASK)
#define CAU_STR_CASR_VER_MASK                    (0xF0000000U)
#define CAU_STR_CASR_VER_SHIFT                   (28U)
#define CAU_STR_CASR_VER(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_STR_CASR_VER_SHIFT)) & CAU_STR_CASR_VER_MASK)

/*! @name STR_CAA - Accumulator register - Store Register command */
#define CAU_STR_CAA_ACC_MASK                     (0xFFFFFFFFU)
#define CAU_STR_CAA_ACC_SHIFT                    (0U)
#define CAU_STR_CAA_ACC(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_STR_CAA_ACC_SHIFT)) & CAU_STR_CAA_ACC_MASK)

/*! @name STR_CA - General Purpose Register 0 - Store Register command..General Purpose Register 8 - Store Register command */
#define CAU_STR_CA_CA0_MASK                      (0xFFFFFFFFU)
#define CAU_STR_CA_CA0_SHIFT                     (0U)
#define CAU_STR_CA_CA0(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA0_SHIFT)) & CAU_STR_CA_CA0_MASK)
#define CAU_STR_CA_CA1_MASK                      (0xFFFFFFFFU)
#define CAU_STR_CA_CA1_SHIFT                     (0U)
#define CAU_STR_CA_CA1(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA1_SHIFT)) & CAU_STR_CA_CA1_MASK)
#define CAU_STR_CA_CA2_MASK                      (0xFFFFFFFFU)
#define CAU_STR_CA_CA2_SHIFT                     (0U)
#define CAU_STR_CA_CA2(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA2_SHIFT)) & CAU_STR_CA_CA2_MASK)
#define CAU_STR_CA_CA3_MASK                      (0xFFFFFFFFU)
#define CAU_STR_CA_CA3_SHIFT                     (0U)
#define CAU_STR_CA_CA3(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA3_SHIFT)) & CAU_STR_CA_CA3_MASK)
#define CAU_STR_CA_CA4_MASK                      (0xFFFFFFFFU)
#define CAU_STR_CA_CA4_SHIFT                     (0U)
#define CAU_STR_CA_CA4(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA4_SHIFT)) & CAU_STR_CA_CA4_MASK)
#define CAU_STR_CA_CA5_MASK                      (0xFFFFFFFFU)
#define CAU_STR_CA_CA5_SHIFT                     (0U)
#define CAU_STR_CA_CA5(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA5_SHIFT)) & CAU_STR_CA_CA5_MASK)
#define CAU_STR_CA_CA6_MASK                      (0xFFFFFFFFU)
#define CAU_STR_CA_CA6_SHIFT                     (0U)
#define CAU_STR_CA_CA6(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA6_SHIFT)) & CAU_STR_CA_CA6_MASK)
#define CAU_STR_CA_CA7_MASK                      (0xFFFFFFFFU)
#define CAU_STR_CA_CA7_SHIFT                     (0U)
#define CAU_STR_CA_CA7(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA7_SHIFT)) & CAU_STR_CA_CA7_MASK)
#define CAU_STR_CA_CA8_MASK                      (0xFFFFFFFFU)
#define CAU_STR_CA_CA8_SHIFT                     (0U)
#define CAU_STR_CA_CA8(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA8_SHIFT)) & CAU_STR_CA_CA8_MASK)

/* The count of CAU_STR_CA */
#define CAU_STR_CA_COUNT                         (9U)

/*! @name ADR_CASR - Status register - Add Register command */
#define CAU_ADR_CASR_IC_MASK                     (0x1U)
#define CAU_ADR_CASR_IC_SHIFT                    (0U)
#define CAU_ADR_CASR_IC(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CASR_IC_SHIFT)) & CAU_ADR_CASR_IC_MASK)
#define CAU_ADR_CASR_DPE_MASK                    (0x2U)
#define CAU_ADR_CASR_DPE_SHIFT                   (1U)
#define CAU_ADR_CASR_DPE(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CASR_DPE_SHIFT)) & CAU_ADR_CASR_DPE_MASK)
#define CAU_ADR_CASR_VER_MASK                    (0xF0000000U)
#define CAU_ADR_CASR_VER_SHIFT                   (28U)
#define CAU_ADR_CASR_VER(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CASR_VER_SHIFT)) & CAU_ADR_CASR_VER_MASK)

/*! @name ADR_CAA - Accumulator register - Add to register command */
#define CAU_ADR_CAA_ACC_MASK                     (0xFFFFFFFFU)
#define CAU_ADR_CAA_ACC_SHIFT                    (0U)
#define CAU_ADR_CAA_ACC(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CAA_ACC_SHIFT)) & CAU_ADR_CAA_ACC_MASK)

/*! @name ADR_CA - General Purpose Register 0 - Add to register command..General Purpose Register 8 - Add to register command */
#define CAU_ADR_CA_CA0_MASK                      (0xFFFFFFFFU)
#define CAU_ADR_CA_CA0_SHIFT                     (0U)
#define CAU_ADR_CA_CA0(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA0_SHIFT)) & CAU_ADR_CA_CA0_MASK)
#define CAU_ADR_CA_CA1_MASK                      (0xFFFFFFFFU)
#define CAU_ADR_CA_CA1_SHIFT                     (0U)
#define CAU_ADR_CA_CA1(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA1_SHIFT)) & CAU_ADR_CA_CA1_MASK)
#define CAU_ADR_CA_CA2_MASK                      (0xFFFFFFFFU)
#define CAU_ADR_CA_CA2_SHIFT                     (0U)
#define CAU_ADR_CA_CA2(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA2_SHIFT)) & CAU_ADR_CA_CA2_MASK)
#define CAU_ADR_CA_CA3_MASK                      (0xFFFFFFFFU)
#define CAU_ADR_CA_CA3_SHIFT                     (0U)
#define CAU_ADR_CA_CA3(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA3_SHIFT)) & CAU_ADR_CA_CA3_MASK)
#define CAU_ADR_CA_CA4_MASK                      (0xFFFFFFFFU)
#define CAU_ADR_CA_CA4_SHIFT                     (0U)
#define CAU_ADR_CA_CA4(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA4_SHIFT)) & CAU_ADR_CA_CA4_MASK)
#define CAU_ADR_CA_CA5_MASK                      (0xFFFFFFFFU)
#define CAU_ADR_CA_CA5_SHIFT                     (0U)
#define CAU_ADR_CA_CA5(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA5_SHIFT)) & CAU_ADR_CA_CA5_MASK)
#define CAU_ADR_CA_CA6_MASK                      (0xFFFFFFFFU)
#define CAU_ADR_CA_CA6_SHIFT                     (0U)
#define CAU_ADR_CA_CA6(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA6_SHIFT)) & CAU_ADR_CA_CA6_MASK)
#define CAU_ADR_CA_CA7_MASK                      (0xFFFFFFFFU)
#define CAU_ADR_CA_CA7_SHIFT                     (0U)
#define CAU_ADR_CA_CA7(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA7_SHIFT)) & CAU_ADR_CA_CA7_MASK)
#define CAU_ADR_CA_CA8_MASK                      (0xFFFFFFFFU)
#define CAU_ADR_CA_CA8_SHIFT                     (0U)
#define CAU_ADR_CA_CA8(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA8_SHIFT)) & CAU_ADR_CA_CA8_MASK)

/* The count of CAU_ADR_CA */
#define CAU_ADR_CA_COUNT                         (9U)

/*! @name RADR_CASR - Status register - Reverse and Add to Register command */
#define CAU_RADR_CASR_IC_MASK                    (0x1U)
#define CAU_RADR_CASR_IC_SHIFT                   (0U)
#define CAU_RADR_CASR_IC(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CASR_IC_SHIFT)) & CAU_RADR_CASR_IC_MASK)
#define CAU_RADR_CASR_DPE_MASK                   (0x2U)
#define CAU_RADR_CASR_DPE_SHIFT                  (1U)
#define CAU_RADR_CASR_DPE(x)                     (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CASR_DPE_SHIFT)) & CAU_RADR_CASR_DPE_MASK)
#define CAU_RADR_CASR_VER_MASK                   (0xF0000000U)
#define CAU_RADR_CASR_VER_SHIFT                  (28U)
#define CAU_RADR_CASR_VER(x)                     (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CASR_VER_SHIFT)) & CAU_RADR_CASR_VER_MASK)

/*! @name RADR_CAA - Accumulator register - Reverse and Add to Register command */
#define CAU_RADR_CAA_ACC_MASK                    (0xFFFFFFFFU)
#define CAU_RADR_CAA_ACC_SHIFT                   (0U)
#define CAU_RADR_CAA_ACC(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CAA_ACC_SHIFT)) & CAU_RADR_CAA_ACC_MASK)

/*! @name RADR_CA - General Purpose Register 0 - Reverse and Add to Register command..General Purpose Register 8 - Reverse and Add to Register command */
#define CAU_RADR_CA_CA0_MASK                     (0xFFFFFFFFU)
#define CAU_RADR_CA_CA0_SHIFT                    (0U)
#define CAU_RADR_CA_CA0(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA0_SHIFT)) & CAU_RADR_CA_CA0_MASK)
#define CAU_RADR_CA_CA1_MASK                     (0xFFFFFFFFU)
#define CAU_RADR_CA_CA1_SHIFT                    (0U)
#define CAU_RADR_CA_CA1(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA1_SHIFT)) & CAU_RADR_CA_CA1_MASK)
#define CAU_RADR_CA_CA2_MASK                     (0xFFFFFFFFU)
#define CAU_RADR_CA_CA2_SHIFT                    (0U)
#define CAU_RADR_CA_CA2(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA2_SHIFT)) & CAU_RADR_CA_CA2_MASK)
#define CAU_RADR_CA_CA3_MASK                     (0xFFFFFFFFU)
#define CAU_RADR_CA_CA3_SHIFT                    (0U)
#define CAU_RADR_CA_CA3(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA3_SHIFT)) & CAU_RADR_CA_CA3_MASK)
#define CAU_RADR_CA_CA4_MASK                     (0xFFFFFFFFU)
#define CAU_RADR_CA_CA4_SHIFT                    (0U)
#define CAU_RADR_CA_CA4(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA4_SHIFT)) & CAU_RADR_CA_CA4_MASK)
#define CAU_RADR_CA_CA5_MASK                     (0xFFFFFFFFU)
#define CAU_RADR_CA_CA5_SHIFT                    (0U)
#define CAU_RADR_CA_CA5(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA5_SHIFT)) & CAU_RADR_CA_CA5_MASK)
#define CAU_RADR_CA_CA6_MASK                     (0xFFFFFFFFU)
#define CAU_RADR_CA_CA6_SHIFT                    (0U)
#define CAU_RADR_CA_CA6(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA6_SHIFT)) & CAU_RADR_CA_CA6_MASK)
#define CAU_RADR_CA_CA7_MASK                     (0xFFFFFFFFU)
#define CAU_RADR_CA_CA7_SHIFT                    (0U)
#define CAU_RADR_CA_CA7(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA7_SHIFT)) & CAU_RADR_CA_CA7_MASK)
#define CAU_RADR_CA_CA8_MASK                     (0xFFFFFFFFU)
#define CAU_RADR_CA_CA8_SHIFT                    (0U)
#define CAU_RADR_CA_CA8(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA8_SHIFT)) & CAU_RADR_CA_CA8_MASK)

/* The count of CAU_RADR_CA */
#define CAU_RADR_CA_COUNT                        (9U)

/*! @name XOR_CASR - Status register - Exclusive Or command */
#define CAU_XOR_CASR_IC_MASK                     (0x1U)
#define CAU_XOR_CASR_IC_SHIFT                    (0U)
#define CAU_XOR_CASR_IC(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CASR_IC_SHIFT)) & CAU_XOR_CASR_IC_MASK)
#define CAU_XOR_CASR_DPE_MASK                    (0x2U)
#define CAU_XOR_CASR_DPE_SHIFT                   (1U)
#define CAU_XOR_CASR_DPE(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CASR_DPE_SHIFT)) & CAU_XOR_CASR_DPE_MASK)
#define CAU_XOR_CASR_VER_MASK                    (0xF0000000U)
#define CAU_XOR_CASR_VER_SHIFT                   (28U)
#define CAU_XOR_CASR_VER(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CASR_VER_SHIFT)) & CAU_XOR_CASR_VER_MASK)

/*! @name XOR_CAA - Accumulator register - Exclusive Or command */
#define CAU_XOR_CAA_ACC_MASK                     (0xFFFFFFFFU)
#define CAU_XOR_CAA_ACC_SHIFT                    (0U)
#define CAU_XOR_CAA_ACC(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CAA_ACC_SHIFT)) & CAU_XOR_CAA_ACC_MASK)

/*! @name XOR_CA - General Purpose Register 0 - Exclusive Or command..General Purpose Register 8 - Exclusive Or command */
#define CAU_XOR_CA_CA0_MASK                      (0xFFFFFFFFU)
#define CAU_XOR_CA_CA0_SHIFT                     (0U)
#define CAU_XOR_CA_CA0(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA0_SHIFT)) & CAU_XOR_CA_CA0_MASK)
#define CAU_XOR_CA_CA1_MASK                      (0xFFFFFFFFU)
#define CAU_XOR_CA_CA1_SHIFT                     (0U)
#define CAU_XOR_CA_CA1(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA1_SHIFT)) & CAU_XOR_CA_CA1_MASK)
#define CAU_XOR_CA_CA2_MASK                      (0xFFFFFFFFU)
#define CAU_XOR_CA_CA2_SHIFT                     (0U)
#define CAU_XOR_CA_CA2(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA2_SHIFT)) & CAU_XOR_CA_CA2_MASK)
#define CAU_XOR_CA_CA3_MASK                      (0xFFFFFFFFU)
#define CAU_XOR_CA_CA3_SHIFT                     (0U)
#define CAU_XOR_CA_CA3(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA3_SHIFT)) & CAU_XOR_CA_CA3_MASK)
#define CAU_XOR_CA_CA4_MASK                      (0xFFFFFFFFU)
#define CAU_XOR_CA_CA4_SHIFT                     (0U)
#define CAU_XOR_CA_CA4(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA4_SHIFT)) & CAU_XOR_CA_CA4_MASK)
#define CAU_XOR_CA_CA5_MASK                      (0xFFFFFFFFU)
#define CAU_XOR_CA_CA5_SHIFT                     (0U)
#define CAU_XOR_CA_CA5(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA5_SHIFT)) & CAU_XOR_CA_CA5_MASK)
#define CAU_XOR_CA_CA6_MASK                      (0xFFFFFFFFU)
#define CAU_XOR_CA_CA6_SHIFT                     (0U)
#define CAU_XOR_CA_CA6(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA6_SHIFT)) & CAU_XOR_CA_CA6_MASK)
#define CAU_XOR_CA_CA7_MASK                      (0xFFFFFFFFU)
#define CAU_XOR_CA_CA7_SHIFT                     (0U)
#define CAU_XOR_CA_CA7(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA7_SHIFT)) & CAU_XOR_CA_CA7_MASK)
#define CAU_XOR_CA_CA8_MASK                      (0xFFFFFFFFU)
#define CAU_XOR_CA_CA8_SHIFT                     (0U)
#define CAU_XOR_CA_CA8(x)                        (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA8_SHIFT)) & CAU_XOR_CA_CA8_MASK)

/* The count of CAU_XOR_CA */
#define CAU_XOR_CA_COUNT                         (9U)

/*! @name ROTL_CASR - Status register - Rotate Left command */
#define CAU_ROTL_CASR_IC_MASK                    (0x1U)
#define CAU_ROTL_CASR_IC_SHIFT                   (0U)
#define CAU_ROTL_CASR_IC(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CASR_IC_SHIFT)) & CAU_ROTL_CASR_IC_MASK)
#define CAU_ROTL_CASR_DPE_MASK                   (0x2U)
#define CAU_ROTL_CASR_DPE_SHIFT                  (1U)
#define CAU_ROTL_CASR_DPE(x)                     (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CASR_DPE_SHIFT)) & CAU_ROTL_CASR_DPE_MASK)
#define CAU_ROTL_CASR_VER_MASK                   (0xF0000000U)
#define CAU_ROTL_CASR_VER_SHIFT                  (28U)
#define CAU_ROTL_CASR_VER(x)                     (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CASR_VER_SHIFT)) & CAU_ROTL_CASR_VER_MASK)

/*! @name ROTL_CAA - Accumulator register - Rotate Left command */
#define CAU_ROTL_CAA_ACC_MASK                    (0xFFFFFFFFU)
#define CAU_ROTL_CAA_ACC_SHIFT                   (0U)
#define CAU_ROTL_CAA_ACC(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CAA_ACC_SHIFT)) & CAU_ROTL_CAA_ACC_MASK)

/*! @name ROTL_CA - General Purpose Register 0 - Rotate Left command..General Purpose Register 8 - Rotate Left command */
#define CAU_ROTL_CA_CA0_MASK                     (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA0_SHIFT                    (0U)
#define CAU_ROTL_CA_CA0(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA0_SHIFT)) & CAU_ROTL_CA_CA0_MASK)
#define CAU_ROTL_CA_CA1_MASK                     (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA1_SHIFT                    (0U)
#define CAU_ROTL_CA_CA1(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA1_SHIFT)) & CAU_ROTL_CA_CA1_MASK)
#define CAU_ROTL_CA_CA2_MASK                     (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA2_SHIFT                    (0U)
#define CAU_ROTL_CA_CA2(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA2_SHIFT)) & CAU_ROTL_CA_CA2_MASK)
#define CAU_ROTL_CA_CA3_MASK                     (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA3_SHIFT                    (0U)
#define CAU_ROTL_CA_CA3(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA3_SHIFT)) & CAU_ROTL_CA_CA3_MASK)
#define CAU_ROTL_CA_CA4_MASK                     (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA4_SHIFT                    (0U)
#define CAU_ROTL_CA_CA4(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA4_SHIFT)) & CAU_ROTL_CA_CA4_MASK)
#define CAU_ROTL_CA_CA5_MASK                     (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA5_SHIFT                    (0U)
#define CAU_ROTL_CA_CA5(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA5_SHIFT)) & CAU_ROTL_CA_CA5_MASK)
#define CAU_ROTL_CA_CA6_MASK                     (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA6_SHIFT                    (0U)
#define CAU_ROTL_CA_CA6(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA6_SHIFT)) & CAU_ROTL_CA_CA6_MASK)
#define CAU_ROTL_CA_CA7_MASK                     (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA7_SHIFT                    (0U)
#define CAU_ROTL_CA_CA7(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA7_SHIFT)) & CAU_ROTL_CA_CA7_MASK)
#define CAU_ROTL_CA_CA8_MASK                     (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA8_SHIFT                    (0U)
#define CAU_ROTL_CA_CA8(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA8_SHIFT)) & CAU_ROTL_CA_CA8_MASK)

/* The count of CAU_ROTL_CA */
#define CAU_ROTL_CA_COUNT                        (9U)

/*! @name AESC_CASR - Status register - AES Column Operation command */
#define CAU_AESC_CASR_IC_MASK                    (0x1U)
#define CAU_AESC_CASR_IC_SHIFT                   (0U)
#define CAU_AESC_CASR_IC(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CASR_IC_SHIFT)) & CAU_AESC_CASR_IC_MASK)
#define CAU_AESC_CASR_DPE_MASK                   (0x2U)
#define CAU_AESC_CASR_DPE_SHIFT                  (1U)
#define CAU_AESC_CASR_DPE(x)                     (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CASR_DPE_SHIFT)) & CAU_AESC_CASR_DPE_MASK)
#define CAU_AESC_CASR_VER_MASK                   (0xF0000000U)
#define CAU_AESC_CASR_VER_SHIFT                  (28U)
#define CAU_AESC_CASR_VER(x)                     (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CASR_VER_SHIFT)) & CAU_AESC_CASR_VER_MASK)

/*! @name AESC_CAA - Accumulator register - AES Column Operation command */
#define CAU_AESC_CAA_ACC_MASK                    (0xFFFFFFFFU)
#define CAU_AESC_CAA_ACC_SHIFT                   (0U)
#define CAU_AESC_CAA_ACC(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CAA_ACC_SHIFT)) & CAU_AESC_CAA_ACC_MASK)

/*! @name AESC_CA - General Purpose Register 0 - AES Column Operation command..General Purpose Register 8 - AES Column Operation command */
#define CAU_AESC_CA_CA0_MASK                     (0xFFFFFFFFU)
#define CAU_AESC_CA_CA0_SHIFT                    (0U)
#define CAU_AESC_CA_CA0(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA0_SHIFT)) & CAU_AESC_CA_CA0_MASK)
#define CAU_AESC_CA_CA1_MASK                     (0xFFFFFFFFU)
#define CAU_AESC_CA_CA1_SHIFT                    (0U)
#define CAU_AESC_CA_CA1(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA1_SHIFT)) & CAU_AESC_CA_CA1_MASK)
#define CAU_AESC_CA_CA2_MASK                     (0xFFFFFFFFU)
#define CAU_AESC_CA_CA2_SHIFT                    (0U)
#define CAU_AESC_CA_CA2(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA2_SHIFT)) & CAU_AESC_CA_CA2_MASK)
#define CAU_AESC_CA_CA3_MASK                     (0xFFFFFFFFU)
#define CAU_AESC_CA_CA3_SHIFT                    (0U)
#define CAU_AESC_CA_CA3(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA3_SHIFT)) & CAU_AESC_CA_CA3_MASK)
#define CAU_AESC_CA_CA4_MASK                     (0xFFFFFFFFU)
#define CAU_AESC_CA_CA4_SHIFT                    (0U)
#define CAU_AESC_CA_CA4(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA4_SHIFT)) & CAU_AESC_CA_CA4_MASK)
#define CAU_AESC_CA_CA5_MASK                     (0xFFFFFFFFU)
#define CAU_AESC_CA_CA5_SHIFT                    (0U)
#define CAU_AESC_CA_CA5(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA5_SHIFT)) & CAU_AESC_CA_CA5_MASK)
#define CAU_AESC_CA_CA6_MASK                     (0xFFFFFFFFU)
#define CAU_AESC_CA_CA6_SHIFT                    (0U)
#define CAU_AESC_CA_CA6(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA6_SHIFT)) & CAU_AESC_CA_CA6_MASK)
#define CAU_AESC_CA_CA7_MASK                     (0xFFFFFFFFU)
#define CAU_AESC_CA_CA7_SHIFT                    (0U)
#define CAU_AESC_CA_CA7(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA7_SHIFT)) & CAU_AESC_CA_CA7_MASK)
#define CAU_AESC_CA_CA8_MASK                     (0xFFFFFFFFU)
#define CAU_AESC_CA_CA8_SHIFT                    (0U)
#define CAU_AESC_CA_CA8(x)                       (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA8_SHIFT)) & CAU_AESC_CA_CA8_MASK)

/* The count of CAU_AESC_CA */
#define CAU_AESC_CA_COUNT                        (9U)

/*! @name AESIC_CASR - Status register - AES Inverse Column Operation command */
#define CAU_AESIC_CASR_IC_MASK                   (0x1U)
#define CAU_AESIC_CASR_IC_SHIFT                  (0U)
#define CAU_AESIC_CASR_IC(x)                     (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CASR_IC_SHIFT)) & CAU_AESIC_CASR_IC_MASK)
#define CAU_AESIC_CASR_DPE_MASK                  (0x2U)
#define CAU_AESIC_CASR_DPE_SHIFT                 (1U)
#define CAU_AESIC_CASR_DPE(x)                    (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CASR_DPE_SHIFT)) & CAU_AESIC_CASR_DPE_MASK)
#define CAU_AESIC_CASR_VER_MASK                  (0xF0000000U)
#define CAU_AESIC_CASR_VER_SHIFT                 (28U)
#define CAU_AESIC_CASR_VER(x)                    (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CASR_VER_SHIFT)) & CAU_AESIC_CASR_VER_MASK)

/*! @name AESIC_CAA - Accumulator register - AES Inverse Column Operation command */
#define CAU_AESIC_CAA_ACC_MASK                   (0xFFFFFFFFU)
#define CAU_AESIC_CAA_ACC_SHIFT                  (0U)
#define CAU_AESIC_CAA_ACC(x)                     (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CAA_ACC_SHIFT)) & CAU_AESIC_CAA_ACC_MASK)

/*! @name AESIC_CA - General Purpose Register 0 - AES Inverse Column Operation command..General Purpose Register 8 - AES Inverse Column Operation command */
#define CAU_AESIC_CA_CA0_MASK                    (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA0_SHIFT                   (0U)
#define CAU_AESIC_CA_CA0(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA0_SHIFT)) & CAU_AESIC_CA_CA0_MASK)
#define CAU_AESIC_CA_CA1_MASK                    (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA1_SHIFT                   (0U)
#define CAU_AESIC_CA_CA1(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA1_SHIFT)) & CAU_AESIC_CA_CA1_MASK)
#define CAU_AESIC_CA_CA2_MASK                    (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA2_SHIFT                   (0U)
#define CAU_AESIC_CA_CA2(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA2_SHIFT)) & CAU_AESIC_CA_CA2_MASK)
#define CAU_AESIC_CA_CA3_MASK                    (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA3_SHIFT                   (0U)
#define CAU_AESIC_CA_CA3(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA3_SHIFT)) & CAU_AESIC_CA_CA3_MASK)
#define CAU_AESIC_CA_CA4_MASK                    (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA4_SHIFT                   (0U)
#define CAU_AESIC_CA_CA4(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA4_SHIFT)) & CAU_AESIC_CA_CA4_MASK)
#define CAU_AESIC_CA_CA5_MASK                    (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA5_SHIFT                   (0U)
#define CAU_AESIC_CA_CA5(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA5_SHIFT)) & CAU_AESIC_CA_CA5_MASK)
#define CAU_AESIC_CA_CA6_MASK                    (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA6_SHIFT                   (0U)
#define CAU_AESIC_CA_CA6(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA6_SHIFT)) & CAU_AESIC_CA_CA6_MASK)
#define CAU_AESIC_CA_CA7_MASK                    (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA7_SHIFT                   (0U)
#define CAU_AESIC_CA_CA7(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA7_SHIFT)) & CAU_AESIC_CA_CA7_MASK)
#define CAU_AESIC_CA_CA8_MASK                    (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA8_SHIFT                   (0U)
#define CAU_AESIC_CA_CA8(x)                      (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA8_SHIFT)) & CAU_AESIC_CA_CA8_MASK)

/* The count of CAU_AESIC_CA */
#define CAU_AESIC_CA_COUNT                       (9U)


/*!
 * @}
 */ /* end of group CAU_Register_Masks */


/* CAU - Peripheral instance base addresses */
/** Peripheral CAU base address */
#define CAU_BASE                                 (0xE0081000u)
/** Peripheral CAU base pointer */
#define CAU                                      ((CAU_Type *)CAU_BASE)
/** Array initializer of CAU peripheral base addresses */
#define CAU_BASE_ADDRS                           { CAU_BASE }
/** Array initializer of CAU peripheral base pointers */
#define CAU_BASE_PTRS                            { CAU }

/*!
 * @}
 */ /* end of group CAU_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- CMP Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMP_Peripheral_Access_Layer CMP Peripheral Access Layer
 * @{
 */

/** CMP - Register Layout Typedef */
typedef struct {
  __IO uint8_t CR0;                                /**< CMP Control Register 0, offset: 0x0 */
  __IO uint8_t CR1;                                /**< CMP Control Register 1, offset: 0x1 */
  __IO uint8_t FPR;                                /**< CMP Filter Period Register, offset: 0x2 */
  __IO uint8_t SCR;                                /**< CMP Status and Control Register, offset: 0x3 */
  __IO uint8_t DACCR;                              /**< DAC Control Register, offset: 0x4 */
  __IO uint8_t MUXCR;                              /**< MUX Control Register, offset: 0x5 */
} CMP_Type;

/* ----------------------------------------------------------------------------
   -- CMP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMP_Register_Masks CMP Register Masks
 * @{
 */

/*! @name CR0 - CMP Control Register 0 */
#define CMP_CR0_HYSTCTR_MASK                     (0x3U)
#define CMP_CR0_HYSTCTR_SHIFT                    (0U)
#define CMP_CR0_HYSTCTR(x)                       (((uint8_t)(((uint8_t)(x)) << CMP_CR0_HYSTCTR_SHIFT)) & CMP_CR0_HYSTCTR_MASK)
#define CMP_CR0_FILTER_CNT_MASK                  (0x70U)
#define CMP_CR0_FILTER_CNT_SHIFT                 (4U)
#define CMP_CR0_FILTER_CNT(x)                    (((uint8_t)(((uint8_t)(x)) << CMP_CR0_FILTER_CNT_SHIFT)) & CMP_CR0_FILTER_CNT_MASK)

/*! @name CR1 - CMP Control Register 1 */
#define CMP_CR1_EN_MASK                          (0x1U)
#define CMP_CR1_EN_SHIFT                         (0U)
#define CMP_CR1_EN(x)                            (((uint8_t)(((uint8_t)(x)) << CMP_CR1_EN_SHIFT)) & CMP_CR1_EN_MASK)
#define CMP_CR1_OPE_MASK                         (0x2U)
#define CMP_CR1_OPE_SHIFT                        (1U)
#define CMP_CR1_OPE(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_CR1_OPE_SHIFT)) & CMP_CR1_OPE_MASK)
#define CMP_CR1_COS_MASK                         (0x4U)
#define CMP_CR1_COS_SHIFT                        (2U)
#define CMP_CR1_COS(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_CR1_COS_SHIFT)) & CMP_CR1_COS_MASK)
#define CMP_CR1_INV_MASK                         (0x8U)
#define CMP_CR1_INV_SHIFT                        (3U)
#define CMP_CR1_INV(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_CR1_INV_SHIFT)) & CMP_CR1_INV_MASK)
#define CMP_CR1_PMODE_MASK                       (0x10U)
#define CMP_CR1_PMODE_SHIFT                      (4U)
#define CMP_CR1_PMODE(x)                         (((uint8_t)(((uint8_t)(x)) << CMP_CR1_PMODE_SHIFT)) & CMP_CR1_PMODE_MASK)
#define CMP_CR1_TRIGM_MASK                       (0x20U)
#define CMP_CR1_TRIGM_SHIFT                      (5U)
#define CMP_CR1_TRIGM(x)                         (((uint8_t)(((uint8_t)(x)) << CMP_CR1_TRIGM_SHIFT)) & CMP_CR1_TRIGM_MASK)
#define CMP_CR1_WE_MASK                          (0x40U)
#define CMP_CR1_WE_SHIFT                         (6U)
#define CMP_CR1_WE(x)                            (((uint8_t)(((uint8_t)(x)) << CMP_CR1_WE_SHIFT)) & CMP_CR1_WE_MASK)
#define CMP_CR1_SE_MASK                          (0x80U)
#define CMP_CR1_SE_SHIFT                         (7U)
#define CMP_CR1_SE(x)                            (((uint8_t)(((uint8_t)(x)) << CMP_CR1_SE_SHIFT)) & CMP_CR1_SE_MASK)

/*! @name FPR - CMP Filter Period Register */
#define CMP_FPR_FILT_PER_MASK                    (0xFFU)
#define CMP_FPR_FILT_PER_SHIFT                   (0U)
#define CMP_FPR_FILT_PER(x)                      (((uint8_t)(((uint8_t)(x)) << CMP_FPR_FILT_PER_SHIFT)) & CMP_FPR_FILT_PER_MASK)

/*! @name SCR - CMP Status and Control Register */
#define CMP_SCR_COUT_MASK                        (0x1U)
#define CMP_SCR_COUT_SHIFT                       (0U)
#define CMP_SCR_COUT(x)                          (((uint8_t)(((uint8_t)(x)) << CMP_SCR_COUT_SHIFT)) & CMP_SCR_COUT_MASK)
#define CMP_SCR_CFF_MASK                         (0x2U)
#define CMP_SCR_CFF_SHIFT                        (1U)
#define CMP_SCR_CFF(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_SCR_CFF_SHIFT)) & CMP_SCR_CFF_MASK)
#define CMP_SCR_CFR_MASK                         (0x4U)
#define CMP_SCR_CFR_SHIFT                        (2U)
#define CMP_SCR_CFR(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_SCR_CFR_SHIFT)) & CMP_SCR_CFR_MASK)
#define CMP_SCR_IEF_MASK                         (0x8U)
#define CMP_SCR_IEF_SHIFT                        (3U)
#define CMP_SCR_IEF(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_SCR_IEF_SHIFT)) & CMP_SCR_IEF_MASK)
#define CMP_SCR_IER_MASK                         (0x10U)
#define CMP_SCR_IER_SHIFT                        (4U)
#define CMP_SCR_IER(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_SCR_IER_SHIFT)) & CMP_SCR_IER_MASK)
#define CMP_SCR_DMAEN_MASK                       (0x40U)
#define CMP_SCR_DMAEN_SHIFT                      (6U)
#define CMP_SCR_DMAEN(x)                         (((uint8_t)(((uint8_t)(x)) << CMP_SCR_DMAEN_SHIFT)) & CMP_SCR_DMAEN_MASK)

/*! @name DACCR - DAC Control Register */
#define CMP_DACCR_VOSEL_MASK                     (0x3FU)
#define CMP_DACCR_VOSEL_SHIFT                    (0U)
#define CMP_DACCR_VOSEL(x)                       (((uint8_t)(((uint8_t)(x)) << CMP_DACCR_VOSEL_SHIFT)) & CMP_DACCR_VOSEL_MASK)
#define CMP_DACCR_VRSEL_MASK                     (0x40U)
#define CMP_DACCR_VRSEL_SHIFT                    (6U)
#define CMP_DACCR_VRSEL(x)                       (((uint8_t)(((uint8_t)(x)) << CMP_DACCR_VRSEL_SHIFT)) & CMP_DACCR_VRSEL_MASK)
#define CMP_DACCR_DACEN_MASK                     (0x80U)
#define CMP_DACCR_DACEN_SHIFT                    (7U)
#define CMP_DACCR_DACEN(x)                       (((uint8_t)(((uint8_t)(x)) << CMP_DACCR_DACEN_SHIFT)) & CMP_DACCR_DACEN_MASK)

/*! @name MUXCR - MUX Control Register */
#define CMP_MUXCR_MSEL_MASK                      (0x7U)
#define CMP_MUXCR_MSEL_SHIFT                     (0U)
#define CMP_MUXCR_MSEL(x)                        (((uint8_t)(((uint8_t)(x)) << CMP_MUXCR_MSEL_SHIFT)) & CMP_MUXCR_MSEL_MASK)
#define CMP_MUXCR_PSEL_MASK                      (0x38U)
#define CMP_MUXCR_PSEL_SHIFT                     (3U)
#define CMP_MUXCR_PSEL(x)                        (((uint8_t)(((uint8_t)(x)) << CMP_MUXCR_PSEL_SHIFT)) & CMP_MUXCR_PSEL_MASK)


/*!
 * @}
 */ /* end of group CMP_Register_Masks */


/* CMP - Peripheral instance base addresses */
/** Peripheral CMP0 base address */
#define CMP0_BASE                                (0x40073000u)
/** Peripheral CMP0 base pointer */
#define CMP0                                     ((CMP_Type *)CMP0_BASE)
/** Peripheral CMP1 base address */
#define CMP1_BASE                                (0x40073008u)
/** Peripheral CMP1 base pointer */
#define CMP1                                     ((CMP_Type *)CMP1_BASE)
/** Peripheral CMP2 base address */
#define CMP2_BASE                                (0x40073010u)
/** Peripheral CMP2 base pointer */
#define CMP2                                     ((CMP_Type *)CMP2_BASE)
/** Peripheral CMP3 base address */
#define CMP3_BASE                                (0x40073018u)
/** Peripheral CMP3 base pointer */
#define CMP3                                     ((CMP_Type *)CMP3_BASE)
/** Array initializer of CMP peripheral base addresses */
#define CMP_BASE_ADDRS                           { CMP0_BASE, CMP1_BASE, CMP2_BASE, CMP3_BASE }
/** Array initializer of CMP peripheral base pointers */
#define CMP_BASE_PTRS                            { CMP0, CMP1, CMP2, CMP3 }
/** Interrupt vectors for the CMP peripheral type */
#define CMP_IRQS                                 { CMP0_IRQn, CMP1_IRQn, CMP2_IRQn, CMP3_IRQn }

/*!
 * @}
 */ /* end of group CMP_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- CRC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Peripheral_Access_Layer CRC Peripheral Access Layer
 * @{
 */

/** CRC - Register Layout Typedef */
typedef struct {
  union {                                          /* offset: 0x0 */
    struct {                                         /* offset: 0x0 */
      __IO uint16_t DATAL;                             /**< CRC_DATAL register., offset: 0x0 */
      __IO uint16_t DATAH;                             /**< CRC_DATAH register., offset: 0x2 */
    } ACCESS16BIT;
    __IO uint32_t DATA;                              /**< CRC Data register, offset: 0x0 */
    struct {                                         /* offset: 0x0 */
      __IO uint8_t DATALL;                             /**< CRC_DATALL register., offset: 0x0 */
      __IO uint8_t DATALU;                             /**< CRC_DATALU register., offset: 0x1 */
      __IO uint8_t DATAHL;                             /**< CRC_DATAHL register., offset: 0x2 */
      __IO uint8_t DATAHU;                             /**< CRC_DATAHU register., offset: 0x3 */
    } ACCESS8BIT;
  };
  union {                                          /* offset: 0x4 */
    struct {                                         /* offset: 0x4 */
      __IO uint16_t GPOLYL;                            /**< CRC_GPOLYL register., offset: 0x4 */
      __IO uint16_t GPOLYH;                            /**< CRC_GPOLYH register., offset: 0x6 */
    } GPOLY_ACCESS16BIT;
    __IO uint32_t GPOLY;                             /**< CRC Polynomial register, offset: 0x4 */
    struct {                                         /* offset: 0x4 */
      __IO uint8_t GPOLYLL;                            /**< CRC_GPOLYLL register., offset: 0x4 */
      __IO uint8_t GPOLYLU;                            /**< CRC_GPOLYLU register., offset: 0x5 */
      __IO uint8_t GPOLYHL;                            /**< CRC_GPOLYHL register., offset: 0x6 */
      __IO uint8_t GPOLYHU;                            /**< CRC_GPOLYHU register., offset: 0x7 */
    } GPOLY_ACCESS8BIT;
  };
  union {                                          /* offset: 0x8 */
    __IO uint32_t CTRL;                              /**< CRC Control register, offset: 0x8 */
    struct {                                         /* offset: 0x8 */
           uint8_t RESERVED_0[3];
      __IO uint8_t CTRLHU;                             /**< CRC_CTRLHU register., offset: 0xB */
    } CTRL_ACCESS8BIT;
  };
} CRC_Type;

/* ----------------------------------------------------------------------------
   -- CRC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Register_Masks CRC Register Masks
 * @{
 */

/*! @name DATAL - CRC_DATAL register. */
#define CRC_DATAL_DATAL_MASK                     (0xFFFFU)
#define CRC_DATAL_DATAL_SHIFT                    (0U)
#define CRC_DATAL_DATAL(x)                       (((uint16_t)(((uint16_t)(x)) << CRC_DATAL_DATAL_SHIFT)) & CRC_DATAL_DATAL_MASK)

/*! @name DATAH - CRC_DATAH register. */
#define CRC_DATAH_DATAH_MASK                     (0xFFFFU)
#define CRC_DATAH_DATAH_SHIFT                    (0U)
#define CRC_DATAH_DATAH(x)                       (((uint16_t)(((uint16_t)(x)) << CRC_DATAH_DATAH_SHIFT)) & CRC_DATAH_DATAH_MASK)

/*! @name DATA - CRC Data register */
#define CRC_DATA_LL_MASK                         (0xFFU)
#define CRC_DATA_LL_SHIFT                        (0U)
#define CRC_DATA_LL(x)                           (((uint32_t)(((uint32_t)(x)) << CRC_DATA_LL_SHIFT)) & CRC_DATA_LL_MASK)
#define CRC_DATA_LU_MASK                         (0xFF00U)
#define CRC_DATA_LU_SHIFT                        (8U)
#define CRC_DATA_LU(x)                           (((uint32_t)(((uint32_t)(x)) << CRC_DATA_LU_SHIFT)) & CRC_DATA_LU_MASK)
#define CRC_DATA_HL_MASK                         (0xFF0000U)
#define CRC_DATA_HL_SHIFT                        (16U)
#define CRC_DATA_HL(x)                           (((uint32_t)(((uint32_t)(x)) << CRC_DATA_HL_SHIFT)) & CRC_DATA_HL_MASK)
#define CRC_DATA_HU_MASK                         (0xFF000000U)
#define CRC_DATA_HU_SHIFT                        (24U)
#define CRC_DATA_HU(x)                           (((uint32_t)(((uint32_t)(x)) << CRC_DATA_HU_SHIFT)) & CRC_DATA_HU_MASK)

/*! @name DATALL - CRC_DATALL register. */
#define CRC_DATALL_DATALL_MASK                   (0xFFU)
#define CRC_DATALL_DATALL_SHIFT                  (0U)
#define CRC_DATALL_DATALL(x)                     (((uint8_t)(((uint8_t)(x)) << CRC_DATALL_DATALL_SHIFT)) & CRC_DATALL_DATALL_MASK)

/*! @name DATALU - CRC_DATALU register. */
#define CRC_DATALU_DATALU_MASK                   (0xFFU)
#define CRC_DATALU_DATALU_SHIFT                  (0U)
#define CRC_DATALU_DATALU(x)                     (((uint8_t)(((uint8_t)(x)) << CRC_DATALU_DATALU_SHIFT)) & CRC_DATALU_DATALU_MASK)

/*! @name DATAHL - CRC_DATAHL register. */
#define CRC_DATAHL_DATAHL_MASK                   (0xFFU)
#define CRC_DATAHL_DATAHL_SHIFT                  (0U)
#define CRC_DATAHL_DATAHL(x)                     (((uint8_t)(((uint8_t)(x)) << CRC_DATAHL_DATAHL_SHIFT)) & CRC_DATAHL_DATAHL_MASK)

/*! @name DATAHU - CRC_DATAHU register. */
#define CRC_DATAHU_DATAHU_MASK                   (0xFFU)
#define CRC_DATAHU_DATAHU_SHIFT                  (0U)
#define CRC_DATAHU_DATAHU(x)                     (((uint8_t)(((uint8_t)(x)) << CRC_DATAHU_DATAHU_SHIFT)) & CRC_DATAHU_DATAHU_MASK)

/*! @name GPOLYL - CRC_GPOLYL register. */
#define CRC_GPOLYL_GPOLYL_MASK                   (0xFFFFU)
#define CRC_GPOLYL_GPOLYL_SHIFT                  (0U)
#define CRC_GPOLYL_GPOLYL(x)                     (((uint16_t)(((uint16_t)(x)) << CRC_GPOLYL_GPOLYL_SHIFT)) & CRC_GPOLYL_GPOLYL_MASK)

/*! @name GPOLYH - CRC_GPOLYH register. */
#define CRC_GPOLYH_GPOLYH_MASK                   (0xFFFFU)
#define CRC_GPOLYH_GPOLYH_SHIFT                  (0U)
#define CRC_GPOLYH_GPOLYH(x)                     (((uint16_t)(((uint16_t)(x)) << CRC_GPOLYH_GPOLYH_SHIFT)) & CRC_GPOLYH_GPOLYH_MASK)

/*! @name GPOLY - CRC Polynomial register */
#define CRC_GPOLY_LOW_MASK                       (0xFFFFU)
#define CRC_GPOLY_LOW_SHIFT                      (0U)
#define CRC_GPOLY_LOW(x)                         (((uint32_t)(((uint32_t)(x)) << CRC_GPOLY_LOW_SHIFT)) & CRC_GPOLY_LOW_MASK)
#define CRC_GPOLY_HIGH_MASK                      (0xFFFF0000U)
#define CRC_GPOLY_HIGH_SHIFT                     (16U)
#define CRC_GPOLY_HIGH(x)                        (((uint32_t)(((uint32_t)(x)) << CRC_GPOLY_HIGH_SHIFT)) & CRC_GPOLY_HIGH_MASK)

/*! @name GPOLYLL - CRC_GPOLYLL register. */
#define CRC_GPOLYLL_GPOLYLL_MASK                 (0xFFU)
#define CRC_GPOLYLL_GPOLYLL_SHIFT                (0U)
#define CRC_GPOLYLL_GPOLYLL(x)                   (((uint8_t)(((uint8_t)(x)) << CRC_GPOLYLL_GPOLYLL_SHIFT)) & CRC_GPOLYLL_GPOLYLL_MASK)

/*! @name GPOLYLU - CRC_GPOLYLU register. */
#define CRC_GPOLYLU_GPOLYLU_MASK                 (0xFFU)
#define CRC_GPOLYLU_GPOLYLU_SHIFT                (0U)
#define CRC_GPOLYLU_GPOLYLU(x)                   (((uint8_t)(((uint8_t)(x)) << CRC_GPOLYLU_GPOLYLU_SHIFT)) & CRC_GPOLYLU_GPOLYLU_MASK)

/*! @name GPOLYHL - CRC_GPOLYHL register. */
#define CRC_GPOLYHL_GPOLYHL_MASK                 (0xFFU)
#define CRC_GPOLYHL_GPOLYHL_SHIFT                (0U)
#define CRC_GPOLYHL_GPOLYHL(x)                   (((uint8_t)(((uint8_t)(x)) << CRC_GPOLYHL_GPOLYHL_SHIFT)) & CRC_GPOLYHL_GPOLYHL_MASK)

/*! @name GPOLYHU - CRC_GPOLYHU register. */
#define CRC_GPOLYHU_GPOLYHU_MASK                 (0xFFU)
#define CRC_GPOLYHU_GPOLYHU_SHIFT                (0U)
#define CRC_GPOLYHU_GPOLYHU(x)                   (((uint8_t)(((uint8_t)(x)) << CRC_GPOLYHU_GPOLYHU_SHIFT)) & CRC_GPOLYHU_GPOLYHU_MASK)

/*! @name CTRL - CRC Control register */
#define CRC_CTRL_TCRC_MASK                       (0x1000000U)
#define CRC_CTRL_TCRC_SHIFT                      (24U)
#define CRC_CTRL_TCRC(x)                         (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_TCRC_SHIFT)) & CRC_CTRL_TCRC_MASK)
#define CRC_CTRL_WAS_MASK                        (0x2000000U)
#define CRC_CTRL_WAS_SHIFT                       (25U)
#define CRC_CTRL_WAS(x)                          (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_WAS_SHIFT)) & CRC_CTRL_WAS_MASK)
#define CRC_CTRL_FXOR_MASK                       (0x4000000U)
#define CRC_CTRL_FXOR_SHIFT                      (26U)
#define CRC_CTRL_FXOR(x)                         (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_FXOR_SHIFT)) & CRC_CTRL_FXOR_MASK)
#define CRC_CTRL_TOTR_MASK                       (0x30000000U)
#define CRC_CTRL_TOTR_SHIFT                      (28U)
#define CRC_CTRL_TOTR(x)                         (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_TOTR_SHIFT)) & CRC_CTRL_TOTR_MASK)
#define CRC_CTRL_TOT_MASK                        (0xC0000000U)
#define CRC_CTRL_TOT_SHIFT                       (30U)
#define CRC_CTRL_TOT(x)                          (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_TOT_SHIFT)) & CRC_CTRL_TOT_MASK)

/*! @name CTRLHU - CRC_CTRLHU register. */
#define CRC_CTRLHU_TCRC_MASK                     (0x1U)
#define CRC_CTRLHU_TCRC_SHIFT                    (0U)
#define CRC_CTRLHU_TCRC(x)                       (((uint8_t)(((uint8_t)(x)) << CRC_CTRLHU_TCRC_SHIFT)) & CRC_CTRLHU_TCRC_MASK)
#define CRC_CTRLHU_WAS_MASK                      (0x2U)
#define CRC_CTRLHU_WAS_SHIFT                     (1U)
#define CRC_CTRLHU_WAS(x)                        (((uint8_t)(((uint8_t)(x)) << CRC_CTRLHU_WAS_SHIFT)) & CRC_CTRLHU_WAS_MASK)
#define CRC_CTRLHU_FXOR_MASK                     (0x4U)
#define CRC_CTRLHU_FXOR_SHIFT                    (2U)
#define CRC_CTRLHU_FXOR(x)                       (((uint8_t)(((uint8_t)(x)) << CRC_CTRLHU_FXOR_SHIFT)) & CRC_CTRLHU_FXOR_MASK)
#define CRC_CTRLHU_TOTR_MASK                     (0x30U)
#define CRC_CTRLHU_TOTR_SHIFT                    (4U)
#define CRC_CTRLHU_TOTR(x)                       (((uint8_t)(((uint8_t)(x)) << CRC_CTRLHU_TOTR_SHIFT)) & CRC_CTRLHU_TOTR_MASK)
#define CRC_CTRLHU_TOT_MASK                      (0xC0U)
#define CRC_CTRLHU_TOT_SHIFT                     (6U)
#define CRC_CTRLHU_TOT(x)                        (((uint8_t)(((uint8_t)(x)) << CRC_CTRLHU_TOT_SHIFT)) & CRC_CTRLHU_TOT_MASK)


/*!
 * @}
 */ /* end of group CRC_Register_Masks */


/* CRC - Peripheral instance base addresses */
/** Peripheral CRC base address */
#define CRC_BASE                                 (0x40032000u)
/** Peripheral CRC base pointer */
#define CRC0                                     ((CRC_Type *)CRC_BASE)
/** Array initializer of CRC peripheral base addresses */
#define CRC_BASE_ADDRS                           { CRC_BASE }
/** Array initializer of CRC peripheral base pointers */
#define CRC_BASE_PTRS                            { CRC0 }

/*!
 * @}
 */ /* end of group CRC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- DAC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DAC_Peripheral_Access_Layer DAC Peripheral Access Layer
 * @{
 */

/** DAC - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0x2 */
    __IO uint8_t DATL;                               /**< DAC Data Low Register, array offset: 0x0, array step: 0x2 */
    __IO uint8_t DATH;                               /**< DAC Data High Register, array offset: 0x1, array step: 0x2 */
  } DAT[16];
  __IO uint8_t SR;                                 /**< DAC Status Register, offset: 0x20 */
  __IO uint8_t C0;                                 /**< DAC Control Register, offset: 0x21 */
  __IO uint8_t C1;                                 /**< DAC Control Register 1, offset: 0x22 */
  __IO uint8_t C2;                                 /**< DAC Control Register 2, offset: 0x23 */
} DAC_Type;

/* ----------------------------------------------------------------------------
   -- DAC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DAC_Register_Masks DAC Register Masks
 * @{
 */

/*! @name DATL - DAC Data Low Register */
#define DAC_DATL_DATA0_MASK                      (0xFFU)
#define DAC_DATL_DATA0_SHIFT                     (0U)
#define DAC_DATL_DATA0(x)                        (((uint8_t)(((uint8_t)(x)) << DAC_DATL_DATA0_SHIFT)) & DAC_DATL_DATA0_MASK)

/* The count of DAC_DATL */
#define DAC_DATL_COUNT                           (16U)

/*! @name DATH - DAC Data High Register */
#define DAC_DATH_DATA1_MASK                      (0xFU)
#define DAC_DATH_DATA1_SHIFT                     (0U)
#define DAC_DATH_DATA1(x)                        (((uint8_t)(((uint8_t)(x)) << DAC_DATH_DATA1_SHIFT)) & DAC_DATH_DATA1_MASK)

/* The count of DAC_DATH */
#define DAC_DATH_COUNT                           (16U)

/*! @name SR - DAC Status Register */
#define DAC_SR_DACBFRPBF_MASK                    (0x1U)
#define DAC_SR_DACBFRPBF_SHIFT                   (0U)
#define DAC_SR_DACBFRPBF(x)                      (((uint8_t)(((uint8_t)(x)) << DAC_SR_DACBFRPBF_SHIFT)) & DAC_SR_DACBFRPBF_MASK)
#define DAC_SR_DACBFRPTF_MASK                    (0x2U)
#define DAC_SR_DACBFRPTF_SHIFT                   (1U)
#define DAC_SR_DACBFRPTF(x)                      (((uint8_t)(((uint8_t)(x)) << DAC_SR_DACBFRPTF_SHIFT)) & DAC_SR_DACBFRPTF_MASK)
#define DAC_SR_DACBFWMF_MASK                     (0x4U)
#define DAC_SR_DACBFWMF_SHIFT                    (2U)
#define DAC_SR_DACBFWMF(x)                       (((uint8_t)(((uint8_t)(x)) << DAC_SR_DACBFWMF_SHIFT)) & DAC_SR_DACBFWMF_MASK)

/*! @name C0 - DAC Control Register */
#define DAC_C0_DACBBIEN_MASK                     (0x1U)
#define DAC_C0_DACBBIEN_SHIFT                    (0U)
#define DAC_C0_DACBBIEN(x)                       (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACBBIEN_SHIFT)) & DAC_C0_DACBBIEN_MASK)
#define DAC_C0_DACBTIEN_MASK                     (0x2U)
#define DAC_C0_DACBTIEN_SHIFT                    (1U)
#define DAC_C0_DACBTIEN(x)                       (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACBTIEN_SHIFT)) & DAC_C0_DACBTIEN_MASK)
#define DAC_C0_DACBWIEN_MASK                     (0x4U)
#define DAC_C0_DACBWIEN_SHIFT                    (2U)
#define DAC_C0_DACBWIEN(x)                       (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACBWIEN_SHIFT)) & DAC_C0_DACBWIEN_MASK)
#define DAC_C0_LPEN_MASK                         (0x8U)
#define DAC_C0_LPEN_SHIFT                        (3U)
#define DAC_C0_LPEN(x)                           (((uint8_t)(((uint8_t)(x)) << DAC_C0_LPEN_SHIFT)) & DAC_C0_LPEN_MASK)
#define DAC_C0_DACSWTRG_MASK                     (0x10U)
#define DAC_C0_DACSWTRG_SHIFT                    (4U)
#define DAC_C0_DACSWTRG(x)                       (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACSWTRG_SHIFT)) & DAC_C0_DACSWTRG_MASK)
#define DAC_C0_DACTRGSEL_MASK                    (0x20U)
#define DAC_C0_DACTRGSEL_SHIFT                   (5U)
#define DAC_C0_DACTRGSEL(x)                      (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACTRGSEL_SHIFT)) & DAC_C0_DACTRGSEL_MASK)
#define DAC_C0_DACRFS_MASK                       (0x40U)
#define DAC_C0_DACRFS_SHIFT                      (6U)
#define DAC_C0_DACRFS(x)                         (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACRFS_SHIFT)) & DAC_C0_DACRFS_MASK)
#define DAC_C0_DACEN_MASK                        (0x80U)
#define DAC_C0_DACEN_SHIFT                       (7U)
#define DAC_C0_DACEN(x)                          (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACEN_SHIFT)) & DAC_C0_DACEN_MASK)

/*! @name C1 - DAC Control Register 1 */
#define DAC_C1_DACBFEN_MASK                      (0x1U)
#define DAC_C1_DACBFEN_SHIFT                     (0U)
#define DAC_C1_DACBFEN(x)                        (((uint8_t)(((uint8_t)(x)) << DAC_C1_DACBFEN_SHIFT)) & DAC_C1_DACBFEN_MASK)
#define DAC_C1_DACBFMD_MASK                      (0x6U)
#define DAC_C1_DACBFMD_SHIFT                     (1U)
#define DAC_C1_DACBFMD(x)                        (((uint8_t)(((uint8_t)(x)) << DAC_C1_DACBFMD_SHIFT)) & DAC_C1_DACBFMD_MASK)
#define DAC_C1_DACBFWM_MASK                      (0x18U)
#define DAC_C1_DACBFWM_SHIFT                     (3U)
#define DAC_C1_DACBFWM(x)                        (((uint8_t)(((uint8_t)(x)) << DAC_C1_DACBFWM_SHIFT)) & DAC_C1_DACBFWM_MASK)
#define DAC_C1_DMAEN_MASK                        (0x80U)
#define DAC_C1_DMAEN_SHIFT                       (7U)
#define DAC_C1_DMAEN(x)                          (((uint8_t)(((uint8_t)(x)) << DAC_C1_DMAEN_SHIFT)) & DAC_C1_DMAEN_MASK)

/*! @name C2 - DAC Control Register 2 */
#define DAC_C2_DACBFUP_MASK                      (0xFU)
#define DAC_C2_DACBFUP_SHIFT                     (0U)
#define DAC_C2_DACBFUP(x)                        (((uint8_t)(((uint8_t)(x)) << DAC_C2_DACBFUP_SHIFT)) & DAC_C2_DACBFUP_MASK)
#define DAC_C2_DACBFRP_MASK                      (0xF0U)
#define DAC_C2_DACBFRP_SHIFT                     (4U)
#define DAC_C2_DACBFRP(x)                        (((uint8_t)(((uint8_t)(x)) << DAC_C2_DACBFRP_SHIFT)) & DAC_C2_DACBFRP_MASK)


/*!
 * @}
 */ /* end of group DAC_Register_Masks */


/* DAC - Peripheral instance base addresses */
/** Peripheral DAC0 base address */
#define DAC0_BASE                                (0x4003F000u)
/** Peripheral DAC0 base pointer */
#define DAC0                                     ((DAC_Type *)DAC0_BASE)
/** Array initializer of DAC peripheral base addresses */
#define DAC_BASE_ADDRS                           { DAC0_BASE }
/** Array initializer of DAC peripheral base pointers */
#define DAC_BASE_PTRS                            { DAC0 }
/** Interrupt vectors for the DAC peripheral type */
#define DAC_IRQS                                 { DAC0_IRQn }

/*!
 * @}
 */ /* end of group DAC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- DMA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Peripheral_Access_Layer DMA Peripheral Access Layer
 * @{
 */

/** DMA - Register Layout Typedef */
typedef struct {
  __IO uint32_t CR;                                /**< Control Register, offset: 0x0 */
  __I  uint32_t ES;                                /**< Error Status Register, offset: 0x4 */
       uint8_t RESERVED_0[4];
  __IO uint32_t ERQ;                               /**< Enable Request Register, offset: 0xC */
       uint8_t RESERVED_1[4];
  __IO uint32_t EEI;                               /**< Enable Error Interrupt Register, offset: 0x14 */
  __O  uint8_t CEEI;                               /**< Clear Enable Error Interrupt Register, offset: 0x18 */
  __O  uint8_t SEEI;                               /**< Set Enable Error Interrupt Register, offset: 0x19 */
  __O  uint8_t CERQ;                               /**< Clear Enable Request Register, offset: 0x1A */
  __O  uint8_t SERQ;                               /**< Set Enable Request Register, offset: 0x1B */
  __O  uint8_t CDNE;                               /**< Clear DONE Status Bit Register, offset: 0x1C */
  __O  uint8_t SSRT;                               /**< Set START Bit Register, offset: 0x1D */
  __O  uint8_t CERR;                               /**< Clear Error Register, offset: 0x1E */
  __O  uint8_t CINT;                               /**< Clear Interrupt Request Register, offset: 0x1F */
       uint8_t RESERVED_2[4];
  __IO uint32_t INT;                               /**< Interrupt Request Register, offset: 0x24 */
       uint8_t RESERVED_3[4];
  __IO uint32_t ERR;                               /**< Error Register, offset: 0x2C */
       uint8_t RESERVED_4[4];
  __I  uint32_t HRS;                               /**< Hardware Request Status Register, offset: 0x34 */
       uint8_t RESERVED_5[12];
  __IO uint32_t EARS;                              /**< Enable Asynchronous Request in Stop Register, offset: 0x44 */
       uint8_t RESERVED_6[184];
  __IO uint8_t DCHPRI3;                            /**< Channel n Priority Register, offset: 0x100 */
  __IO uint8_t DCHPRI2;                            /**< Channel n Priority Register, offset: 0x101 */
  __IO uint8_t DCHPRI1;                            /**< Channel n Priority Register, offset: 0x102 */
  __IO uint8_t DCHPRI0;                            /**< Channel n Priority Register, offset: 0x103 */
  __IO uint8_t DCHPRI7;                            /**< Channel n Priority Register, offset: 0x104 */
  __IO uint8_t DCHPRI6;                            /**< Channel n Priority Register, offset: 0x105 */
  __IO uint8_t DCHPRI5;                            /**< Channel n Priority Register, offset: 0x106 */
  __IO uint8_t DCHPRI4;                            /**< Channel n Priority Register, offset: 0x107 */
  __IO uint8_t DCHPRI11;                           /**< Channel n Priority Register, offset: 0x108 */
  __IO uint8_t DCHPRI10;                           /**< Channel n Priority Register, offset: 0x109 */
  __IO uint8_t DCHPRI9;                            /**< Channel n Priority Register, offset: 0x10A */
  __IO uint8_t DCHPRI8;                            /**< Channel n Priority Register, offset: 0x10B */
  __IO uint8_t DCHPRI15;                           /**< Channel n Priority Register, offset: 0x10C */
  __IO uint8_t DCHPRI14;                           /**< Channel n Priority Register, offset: 0x10D */
  __IO uint8_t DCHPRI13;                           /**< Channel n Priority Register, offset: 0x10E */
  __IO uint8_t DCHPRI12;                           /**< Channel n Priority Register, offset: 0x10F */
  __IO uint8_t DCHPRI19;                           /**< Channel n Priority Register, offset: 0x110 */
  __IO uint8_t DCHPRI18;                           /**< Channel n Priority Register, offset: 0x111 */
  __IO uint8_t DCHPRI17;                           /**< Channel n Priority Register, offset: 0x112 */
  __IO uint8_t DCHPRI16;                           /**< Channel n Priority Register, offset: 0x113 */
  __IO uint8_t DCHPRI23;                           /**< Channel n Priority Register, offset: 0x114 */
  __IO uint8_t DCHPRI22;                           /**< Channel n Priority Register, offset: 0x115 */
  __IO uint8_t DCHPRI21;                           /**< Channel n Priority Register, offset: 0x116 */
  __IO uint8_t DCHPRI20;                           /**< Channel n Priority Register, offset: 0x117 */
  __IO uint8_t DCHPRI27;                           /**< Channel n Priority Register, offset: 0x118 */
  __IO uint8_t DCHPRI26;                           /**< Channel n Priority Register, offset: 0x119 */
  __IO uint8_t DCHPRI25;                           /**< Channel n Priority Register, offset: 0x11A */
  __IO uint8_t DCHPRI24;                           /**< Channel n Priority Register, offset: 0x11B */
  __IO uint8_t DCHPRI31;                           /**< Channel n Priority Register, offset: 0x11C */
  __IO uint8_t DCHPRI30;                           /**< Channel n Priority Register, offset: 0x11D */
  __IO uint8_t DCHPRI29;                           /**< Channel n Priority Register, offset: 0x11E */
  __IO uint8_t DCHPRI28;                           /**< Channel n Priority Register, offset: 0x11F */
       uint8_t RESERVED_7[3808];
  struct {                                         /* offset: 0x1000, array step: 0x20 */
    __IO uint32_t SADDR;                             /**< TCD Source Address, array offset: 0x1000, array step: 0x20 */
    __IO uint16_t SOFF;                              /**< TCD Signed Source Address Offset, array offset: 0x1004, array step: 0x20 */
    __IO uint16_t ATTR;                              /**< TCD Transfer Attributes, array offset: 0x1006, array step: 0x20 */
    union {                                          /* offset: 0x1008, array step: 0x20 */
      __IO uint32_t NBYTES_MLNO;                       /**< TCD Minor Byte Count (Minor Loop Mapping Disabled), array offset: 0x1008, array step: 0x20 */
      __IO uint32_t NBYTES_MLOFFNO;                    /**< TCD Signed Minor Loop Offset (Minor Loop Mapping Enabled and Offset Disabled), array offset: 0x1008, array step: 0x20 */
      __IO uint32_t NBYTES_MLOFFYES;                   /**< TCD Signed Minor Loop Offset (Minor Loop Mapping and Offset Enabled), array offset: 0x1008, array step: 0x20 */
    };
    __IO uint32_t SLAST;                             /**< TCD Last Source Address Adjustment, array offset: 0x100C, array step: 0x20 */
    __IO uint32_t DADDR;                             /**< TCD Destination Address, array offset: 0x1010, array step: 0x20 */
    __IO uint16_t DOFF;                              /**< TCD Signed Destination Address Offset, array offset: 0x1014, array step: 0x20 */
    union {                                          /* offset: 0x1016, array step: 0x20 */
      __IO uint16_t CITER_ELINKNO;                     /**< TCD Current Minor Loop Link, Major Loop Count (Channel Linking Disabled), array offset: 0x1016, array step: 0x20 */
      __IO uint16_t CITER_ELINKYES;                    /**< TCD Current Minor Loop Link, Major Loop Count (Channel Linking Enabled), array offset: 0x1016, array step: 0x20 */
    };
    __IO uint32_t DLAST_SGA;                         /**< TCD Last Destination Address Adjustment/Scatter Gather Address, array offset: 0x1018, array step: 0x20 */
    __IO uint16_t CSR;                               /**< TCD Control and Status, array offset: 0x101C, array step: 0x20 */
    union {                                          /* offset: 0x101E, array step: 0x20 */
      __IO uint16_t BITER_ELINKNO;                     /**< TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Disabled), array offset: 0x101E, array step: 0x20 */
      __IO uint16_t BITER_ELINKYES;                    /**< TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Enabled), array offset: 0x101E, array step: 0x20 */
    };
  } TCD[32];
} DMA_Type;

/* ----------------------------------------------------------------------------
   -- DMA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Register_Masks DMA Register Masks
 * @{
 */

/*! @name CR - Control Register */
#define DMA_CR_EDBG_MASK                         (0x2U)
#define DMA_CR_EDBG_SHIFT                        (1U)
#define DMA_CR_EDBG(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_CR_EDBG_SHIFT)) & DMA_CR_EDBG_MASK)
#define DMA_CR_ERCA_MASK                         (0x4U)
#define DMA_CR_ERCA_SHIFT                        (2U)
#define DMA_CR_ERCA(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_CR_ERCA_SHIFT)) & DMA_CR_ERCA_MASK)
#define DMA_CR_ERGA_MASK                         (0x8U)
#define DMA_CR_ERGA_SHIFT                        (3U)
#define DMA_CR_ERGA(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_CR_ERGA_SHIFT)) & DMA_CR_ERGA_MASK)
#define DMA_CR_HOE_MASK                          (0x10U)
#define DMA_CR_HOE_SHIFT                         (4U)
#define DMA_CR_HOE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_CR_HOE_SHIFT)) & DMA_CR_HOE_MASK)
#define DMA_CR_HALT_MASK                         (0x20U)
#define DMA_CR_HALT_SHIFT                        (5U)
#define DMA_CR_HALT(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_CR_HALT_SHIFT)) & DMA_CR_HALT_MASK)
#define DMA_CR_CLM_MASK                          (0x40U)
#define DMA_CR_CLM_SHIFT                         (6U)
#define DMA_CR_CLM(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_CR_CLM_SHIFT)) & DMA_CR_CLM_MASK)
#define DMA_CR_EMLM_MASK                         (0x80U)
#define DMA_CR_EMLM_SHIFT                        (7U)
#define DMA_CR_EMLM(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_CR_EMLM_SHIFT)) & DMA_CR_EMLM_MASK)
#define DMA_CR_GRP0PRI_MASK                      (0x100U)
#define DMA_CR_GRP0PRI_SHIFT                     (8U)
#define DMA_CR_GRP0PRI(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_CR_GRP0PRI_SHIFT)) & DMA_CR_GRP0PRI_MASK)
#define DMA_CR_GRP1PRI_MASK                      (0x400U)
#define DMA_CR_GRP1PRI_SHIFT                     (10U)
#define DMA_CR_GRP1PRI(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_CR_GRP1PRI_SHIFT)) & DMA_CR_GRP1PRI_MASK)
#define DMA_CR_ECX_MASK                          (0x10000U)
#define DMA_CR_ECX_SHIFT                         (16U)
#define DMA_CR_ECX(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_CR_ECX_SHIFT)) & DMA_CR_ECX_MASK)
#define DMA_CR_CX_MASK                           (0x20000U)
#define DMA_CR_CX_SHIFT                          (17U)
#define DMA_CR_CX(x)                             (((uint32_t)(((uint32_t)(x)) << DMA_CR_CX_SHIFT)) & DMA_CR_CX_MASK)

/*! @name ES - Error Status Register */
#define DMA_ES_DBE_MASK                          (0x1U)
#define DMA_ES_DBE_SHIFT                         (0U)
#define DMA_ES_DBE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_DBE_SHIFT)) & DMA_ES_DBE_MASK)
#define DMA_ES_SBE_MASK                          (0x2U)
#define DMA_ES_SBE_SHIFT                         (1U)
#define DMA_ES_SBE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_SBE_SHIFT)) & DMA_ES_SBE_MASK)
#define DMA_ES_SGE_MASK                          (0x4U)
#define DMA_ES_SGE_SHIFT                         (2U)
#define DMA_ES_SGE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_SGE_SHIFT)) & DMA_ES_SGE_MASK)
#define DMA_ES_NCE_MASK                          (0x8U)
#define DMA_ES_NCE_SHIFT                         (3U)
#define DMA_ES_NCE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_NCE_SHIFT)) & DMA_ES_NCE_MASK)
#define DMA_ES_DOE_MASK                          (0x10U)
#define DMA_ES_DOE_SHIFT                         (4U)
#define DMA_ES_DOE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_DOE_SHIFT)) & DMA_ES_DOE_MASK)
#define DMA_ES_DAE_MASK                          (0x20U)
#define DMA_ES_DAE_SHIFT                         (5U)
#define DMA_ES_DAE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_DAE_SHIFT)) & DMA_ES_DAE_MASK)
#define DMA_ES_SOE_MASK                          (0x40U)
#define DMA_ES_SOE_SHIFT                         (6U)
#define DMA_ES_SOE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_SOE_SHIFT)) & DMA_ES_SOE_MASK)
#define DMA_ES_SAE_MASK                          (0x80U)
#define DMA_ES_SAE_SHIFT                         (7U)
#define DMA_ES_SAE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_SAE_SHIFT)) & DMA_ES_SAE_MASK)
#define DMA_ES_ERRCHN_MASK                       (0x1F00U)
#define DMA_ES_ERRCHN_SHIFT                      (8U)
#define DMA_ES_ERRCHN(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ES_ERRCHN_SHIFT)) & DMA_ES_ERRCHN_MASK)
#define DMA_ES_CPE_MASK                          (0x4000U)
#define DMA_ES_CPE_SHIFT                         (14U)
#define DMA_ES_CPE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_CPE_SHIFT)) & DMA_ES_CPE_MASK)
#define DMA_ES_GPE_MASK                          (0x8000U)
#define DMA_ES_GPE_SHIFT                         (15U)
#define DMA_ES_GPE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_GPE_SHIFT)) & DMA_ES_GPE_MASK)
#define DMA_ES_ECX_MASK                          (0x10000U)
#define DMA_ES_ECX_SHIFT                         (16U)
#define DMA_ES_ECX(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_ECX_SHIFT)) & DMA_ES_ECX_MASK)
#define DMA_ES_VLD_MASK                          (0x80000000U)
#define DMA_ES_VLD_SHIFT                         (31U)
#define DMA_ES_VLD(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_VLD_SHIFT)) & DMA_ES_VLD_MASK)

/*! @name ERQ - Enable Request Register */
#define DMA_ERQ_ERQ0_MASK                        (0x1U)
#define DMA_ERQ_ERQ0_SHIFT                       (0U)
#define DMA_ERQ_ERQ0(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ0_SHIFT)) & DMA_ERQ_ERQ0_MASK)
#define DMA_ERQ_ERQ1_MASK                        (0x2U)
#define DMA_ERQ_ERQ1_SHIFT                       (1U)
#define DMA_ERQ_ERQ1(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ1_SHIFT)) & DMA_ERQ_ERQ1_MASK)
#define DMA_ERQ_ERQ2_MASK                        (0x4U)
#define DMA_ERQ_ERQ2_SHIFT                       (2U)
#define DMA_ERQ_ERQ2(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ2_SHIFT)) & DMA_ERQ_ERQ2_MASK)
#define DMA_ERQ_ERQ3_MASK                        (0x8U)
#define DMA_ERQ_ERQ3_SHIFT                       (3U)
#define DMA_ERQ_ERQ3(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ3_SHIFT)) & DMA_ERQ_ERQ3_MASK)
#define DMA_ERQ_ERQ4_MASK                        (0x10U)
#define DMA_ERQ_ERQ4_SHIFT                       (4U)
#define DMA_ERQ_ERQ4(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ4_SHIFT)) & DMA_ERQ_ERQ4_MASK)
#define DMA_ERQ_ERQ5_MASK                        (0x20U)
#define DMA_ERQ_ERQ5_SHIFT                       (5U)
#define DMA_ERQ_ERQ5(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ5_SHIFT)) & DMA_ERQ_ERQ5_MASK)
#define DMA_ERQ_ERQ6_MASK                        (0x40U)
#define DMA_ERQ_ERQ6_SHIFT                       (6U)
#define DMA_ERQ_ERQ6(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ6_SHIFT)) & DMA_ERQ_ERQ6_MASK)
#define DMA_ERQ_ERQ7_MASK                        (0x80U)
#define DMA_ERQ_ERQ7_SHIFT                       (7U)
#define DMA_ERQ_ERQ7(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ7_SHIFT)) & DMA_ERQ_ERQ7_MASK)
#define DMA_ERQ_ERQ8_MASK                        (0x100U)
#define DMA_ERQ_ERQ8_SHIFT                       (8U)
#define DMA_ERQ_ERQ8(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ8_SHIFT)) & DMA_ERQ_ERQ8_MASK)
#define DMA_ERQ_ERQ9_MASK                        (0x200U)
#define DMA_ERQ_ERQ9_SHIFT                       (9U)
#define DMA_ERQ_ERQ9(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ9_SHIFT)) & DMA_ERQ_ERQ9_MASK)
#define DMA_ERQ_ERQ10_MASK                       (0x400U)
#define DMA_ERQ_ERQ10_SHIFT                      (10U)
#define DMA_ERQ_ERQ10(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ10_SHIFT)) & DMA_ERQ_ERQ10_MASK)
#define DMA_ERQ_ERQ11_MASK                       (0x800U)
#define DMA_ERQ_ERQ11_SHIFT                      (11U)
#define DMA_ERQ_ERQ11(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ11_SHIFT)) & DMA_ERQ_ERQ11_MASK)
#define DMA_ERQ_ERQ12_MASK                       (0x1000U)
#define DMA_ERQ_ERQ12_SHIFT                      (12U)
#define DMA_ERQ_ERQ12(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ12_SHIFT)) & DMA_ERQ_ERQ12_MASK)
#define DMA_ERQ_ERQ13_MASK                       (0x2000U)
#define DMA_ERQ_ERQ13_SHIFT                      (13U)
#define DMA_ERQ_ERQ13(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ13_SHIFT)) & DMA_ERQ_ERQ13_MASK)
#define DMA_ERQ_ERQ14_MASK                       (0x4000U)
#define DMA_ERQ_ERQ14_SHIFT                      (14U)
#define DMA_ERQ_ERQ14(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ14_SHIFT)) & DMA_ERQ_ERQ14_MASK)
#define DMA_ERQ_ERQ15_MASK                       (0x8000U)
#define DMA_ERQ_ERQ15_SHIFT                      (15U)
#define DMA_ERQ_ERQ15(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ15_SHIFT)) & DMA_ERQ_ERQ15_MASK)
#define DMA_ERQ_ERQ16_MASK                       (0x10000U)
#define DMA_ERQ_ERQ16_SHIFT                      (16U)
#define DMA_ERQ_ERQ16(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ16_SHIFT)) & DMA_ERQ_ERQ16_MASK)
#define DMA_ERQ_ERQ17_MASK                       (0x20000U)
#define DMA_ERQ_ERQ17_SHIFT                      (17U)
#define DMA_ERQ_ERQ17(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ17_SHIFT)) & DMA_ERQ_ERQ17_MASK)
#define DMA_ERQ_ERQ18_MASK                       (0x40000U)
#define DMA_ERQ_ERQ18_SHIFT                      (18U)
#define DMA_ERQ_ERQ18(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ18_SHIFT)) & DMA_ERQ_ERQ18_MASK)
#define DMA_ERQ_ERQ19_MASK                       (0x80000U)
#define DMA_ERQ_ERQ19_SHIFT                      (19U)
#define DMA_ERQ_ERQ19(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ19_SHIFT)) & DMA_ERQ_ERQ19_MASK)
#define DMA_ERQ_ERQ20_MASK                       (0x100000U)
#define DMA_ERQ_ERQ20_SHIFT                      (20U)
#define DMA_ERQ_ERQ20(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ20_SHIFT)) & DMA_ERQ_ERQ20_MASK)
#define DMA_ERQ_ERQ21_MASK                       (0x200000U)
#define DMA_ERQ_ERQ21_SHIFT                      (21U)
#define DMA_ERQ_ERQ21(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ21_SHIFT)) & DMA_ERQ_ERQ21_MASK)
#define DMA_ERQ_ERQ22_MASK                       (0x400000U)
#define DMA_ERQ_ERQ22_SHIFT                      (22U)
#define DMA_ERQ_ERQ22(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ22_SHIFT)) & DMA_ERQ_ERQ22_MASK)
#define DMA_ERQ_ERQ23_MASK                       (0x800000U)
#define DMA_ERQ_ERQ23_SHIFT                      (23U)
#define DMA_ERQ_ERQ23(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ23_SHIFT)) & DMA_ERQ_ERQ23_MASK)
#define DMA_ERQ_ERQ24_MASK                       (0x1000000U)
#define DMA_ERQ_ERQ24_SHIFT                      (24U)
#define DMA_ERQ_ERQ24(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ24_SHIFT)) & DMA_ERQ_ERQ24_MASK)
#define DMA_ERQ_ERQ25_MASK                       (0x2000000U)
#define DMA_ERQ_ERQ25_SHIFT                      (25U)
#define DMA_ERQ_ERQ25(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ25_SHIFT)) & DMA_ERQ_ERQ25_MASK)
#define DMA_ERQ_ERQ26_MASK                       (0x4000000U)
#define DMA_ERQ_ERQ26_SHIFT                      (26U)
#define DMA_ERQ_ERQ26(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ26_SHIFT)) & DMA_ERQ_ERQ26_MASK)
#define DMA_ERQ_ERQ27_MASK                       (0x8000000U)
#define DMA_ERQ_ERQ27_SHIFT                      (27U)
#define DMA_ERQ_ERQ27(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ27_SHIFT)) & DMA_ERQ_ERQ27_MASK)
#define DMA_ERQ_ERQ28_MASK                       (0x10000000U)
#define DMA_ERQ_ERQ28_SHIFT                      (28U)
#define DMA_ERQ_ERQ28(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ28_SHIFT)) & DMA_ERQ_ERQ28_MASK)
#define DMA_ERQ_ERQ29_MASK                       (0x20000000U)
#define DMA_ERQ_ERQ29_SHIFT                      (29U)
#define DMA_ERQ_ERQ29(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ29_SHIFT)) & DMA_ERQ_ERQ29_MASK)
#define DMA_ERQ_ERQ30_MASK                       (0x40000000U)
#define DMA_ERQ_ERQ30_SHIFT                      (30U)
#define DMA_ERQ_ERQ30(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ30_SHIFT)) & DMA_ERQ_ERQ30_MASK)
#define DMA_ERQ_ERQ31_MASK                       (0x80000000U)
#define DMA_ERQ_ERQ31_SHIFT                      (31U)
#define DMA_ERQ_ERQ31(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ31_SHIFT)) & DMA_ERQ_ERQ31_MASK)

/*! @name EEI - Enable Error Interrupt Register */
#define DMA_EEI_EEI0_MASK                        (0x1U)
#define DMA_EEI_EEI0_SHIFT                       (0U)
#define DMA_EEI_EEI0(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI0_SHIFT)) & DMA_EEI_EEI0_MASK)
#define DMA_EEI_EEI1_MASK                        (0x2U)
#define DMA_EEI_EEI1_SHIFT                       (1U)
#define DMA_EEI_EEI1(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI1_SHIFT)) & DMA_EEI_EEI1_MASK)
#define DMA_EEI_EEI2_MASK                        (0x4U)
#define DMA_EEI_EEI2_SHIFT                       (2U)
#define DMA_EEI_EEI2(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI2_SHIFT)) & DMA_EEI_EEI2_MASK)
#define DMA_EEI_EEI3_MASK                        (0x8U)
#define DMA_EEI_EEI3_SHIFT                       (3U)
#define DMA_EEI_EEI3(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI3_SHIFT)) & DMA_EEI_EEI3_MASK)
#define DMA_EEI_EEI4_MASK                        (0x10U)
#define DMA_EEI_EEI4_SHIFT                       (4U)
#define DMA_EEI_EEI4(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI4_SHIFT)) & DMA_EEI_EEI4_MASK)
#define DMA_EEI_EEI5_MASK                        (0x20U)
#define DMA_EEI_EEI5_SHIFT                       (5U)
#define DMA_EEI_EEI5(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI5_SHIFT)) & DMA_EEI_EEI5_MASK)
#define DMA_EEI_EEI6_MASK                        (0x40U)
#define DMA_EEI_EEI6_SHIFT                       (6U)
#define DMA_EEI_EEI6(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI6_SHIFT)) & DMA_EEI_EEI6_MASK)
#define DMA_EEI_EEI7_MASK                        (0x80U)
#define DMA_EEI_EEI7_SHIFT                       (7U)
#define DMA_EEI_EEI7(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI7_SHIFT)) & DMA_EEI_EEI7_MASK)
#define DMA_EEI_EEI8_MASK                        (0x100U)
#define DMA_EEI_EEI8_SHIFT                       (8U)
#define DMA_EEI_EEI8(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI8_SHIFT)) & DMA_EEI_EEI8_MASK)
#define DMA_EEI_EEI9_MASK                        (0x200U)
#define DMA_EEI_EEI9_SHIFT                       (9U)
#define DMA_EEI_EEI9(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI9_SHIFT)) & DMA_EEI_EEI9_MASK)
#define DMA_EEI_EEI10_MASK                       (0x400U)
#define DMA_EEI_EEI10_SHIFT                      (10U)
#define DMA_EEI_EEI10(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI10_SHIFT)) & DMA_EEI_EEI10_MASK)
#define DMA_EEI_EEI11_MASK                       (0x800U)
#define DMA_EEI_EEI11_SHIFT                      (11U)
#define DMA_EEI_EEI11(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI11_SHIFT)) & DMA_EEI_EEI11_MASK)
#define DMA_EEI_EEI12_MASK                       (0x1000U)
#define DMA_EEI_EEI12_SHIFT                      (12U)
#define DMA_EEI_EEI12(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI12_SHIFT)) & DMA_EEI_EEI12_MASK)
#define DMA_EEI_EEI13_MASK                       (0x2000U)
#define DMA_EEI_EEI13_SHIFT                      (13U)
#define DMA_EEI_EEI13(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI13_SHIFT)) & DMA_EEI_EEI13_MASK)
#define DMA_EEI_EEI14_MASK                       (0x4000U)
#define DMA_EEI_EEI14_SHIFT                      (14U)
#define DMA_EEI_EEI14(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI14_SHIFT)) & DMA_EEI_EEI14_MASK)
#define DMA_EEI_EEI15_MASK                       (0x8000U)
#define DMA_EEI_EEI15_SHIFT                      (15U)
#define DMA_EEI_EEI15(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI15_SHIFT)) & DMA_EEI_EEI15_MASK)
#define DMA_EEI_EEI16_MASK                       (0x10000U)
#define DMA_EEI_EEI16_SHIFT                      (16U)
#define DMA_EEI_EEI16(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI16_SHIFT)) & DMA_EEI_EEI16_MASK)
#define DMA_EEI_EEI17_MASK                       (0x20000U)
#define DMA_EEI_EEI17_SHIFT                      (17U)
#define DMA_EEI_EEI17(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI17_SHIFT)) & DMA_EEI_EEI17_MASK)
#define DMA_EEI_EEI18_MASK                       (0x40000U)
#define DMA_EEI_EEI18_SHIFT                      (18U)
#define DMA_EEI_EEI18(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI18_SHIFT)) & DMA_EEI_EEI18_MASK)
#define DMA_EEI_EEI19_MASK                       (0x80000U)
#define DMA_EEI_EEI19_SHIFT                      (19U)
#define DMA_EEI_EEI19(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI19_SHIFT)) & DMA_EEI_EEI19_MASK)
#define DMA_EEI_EEI20_MASK                       (0x100000U)
#define DMA_EEI_EEI20_SHIFT                      (20U)
#define DMA_EEI_EEI20(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI20_SHIFT)) & DMA_EEI_EEI20_MASK)
#define DMA_EEI_EEI21_MASK                       (0x200000U)
#define DMA_EEI_EEI21_SHIFT                      (21U)
#define DMA_EEI_EEI21(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI21_SHIFT)) & DMA_EEI_EEI21_MASK)
#define DMA_EEI_EEI22_MASK                       (0x400000U)
#define DMA_EEI_EEI22_SHIFT                      (22U)
#define DMA_EEI_EEI22(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI22_SHIFT)) & DMA_EEI_EEI22_MASK)
#define DMA_EEI_EEI23_MASK                       (0x800000U)
#define DMA_EEI_EEI23_SHIFT                      (23U)
#define DMA_EEI_EEI23(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI23_SHIFT)) & DMA_EEI_EEI23_MASK)
#define DMA_EEI_EEI24_MASK                       (0x1000000U)
#define DMA_EEI_EEI24_SHIFT                      (24U)
#define DMA_EEI_EEI24(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI24_SHIFT)) & DMA_EEI_EEI24_MASK)
#define DMA_EEI_EEI25_MASK                       (0x2000000U)
#define DMA_EEI_EEI25_SHIFT                      (25U)
#define DMA_EEI_EEI25(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI25_SHIFT)) & DMA_EEI_EEI25_MASK)
#define DMA_EEI_EEI26_MASK                       (0x4000000U)
#define DMA_EEI_EEI26_SHIFT                      (26U)
#define DMA_EEI_EEI26(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI26_SHIFT)) & DMA_EEI_EEI26_MASK)
#define DMA_EEI_EEI27_MASK                       (0x8000000U)
#define DMA_EEI_EEI27_SHIFT                      (27U)
#define DMA_EEI_EEI27(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI27_SHIFT)) & DMA_EEI_EEI27_MASK)
#define DMA_EEI_EEI28_MASK                       (0x10000000U)
#define DMA_EEI_EEI28_SHIFT                      (28U)
#define DMA_EEI_EEI28(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI28_SHIFT)) & DMA_EEI_EEI28_MASK)
#define DMA_EEI_EEI29_MASK                       (0x20000000U)
#define DMA_EEI_EEI29_SHIFT                      (29U)
#define DMA_EEI_EEI29(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI29_SHIFT)) & DMA_EEI_EEI29_MASK)
#define DMA_EEI_EEI30_MASK                       (0x40000000U)
#define DMA_EEI_EEI30_SHIFT                      (30U)
#define DMA_EEI_EEI30(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI30_SHIFT)) & DMA_EEI_EEI30_MASK)
#define DMA_EEI_EEI31_MASK                       (0x80000000U)
#define DMA_EEI_EEI31_SHIFT                      (31U)
#define DMA_EEI_EEI31(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI31_SHIFT)) & DMA_EEI_EEI31_MASK)

/*! @name CEEI - Clear Enable Error Interrupt Register */
#define DMA_CEEI_CEEI_MASK                       (0x1FU)
#define DMA_CEEI_CEEI_SHIFT                      (0U)
#define DMA_CEEI_CEEI(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CEEI_CEEI_SHIFT)) & DMA_CEEI_CEEI_MASK)
#define DMA_CEEI_CAEE_MASK                       (0x40U)
#define DMA_CEEI_CAEE_SHIFT                      (6U)
#define DMA_CEEI_CAEE(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CEEI_CAEE_SHIFT)) & DMA_CEEI_CAEE_MASK)
#define DMA_CEEI_NOP_MASK                        (0x80U)
#define DMA_CEEI_NOP_SHIFT                       (7U)
#define DMA_CEEI_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_CEEI_NOP_SHIFT)) & DMA_CEEI_NOP_MASK)

/*! @name SEEI - Set Enable Error Interrupt Register */
#define DMA_SEEI_SEEI_MASK                       (0x1FU)
#define DMA_SEEI_SEEI_SHIFT                      (0U)
#define DMA_SEEI_SEEI(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SEEI_SEEI_SHIFT)) & DMA_SEEI_SEEI_MASK)
#define DMA_SEEI_SAEE_MASK                       (0x40U)
#define DMA_SEEI_SAEE_SHIFT                      (6U)
#define DMA_SEEI_SAEE(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SEEI_SAEE_SHIFT)) & DMA_SEEI_SAEE_MASK)
#define DMA_SEEI_NOP_MASK                        (0x80U)
#define DMA_SEEI_NOP_SHIFT                       (7U)
#define DMA_SEEI_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_SEEI_NOP_SHIFT)) & DMA_SEEI_NOP_MASK)

/*! @name CERQ - Clear Enable Request Register */
#define DMA_CERQ_CERQ_MASK                       (0x1FU)
#define DMA_CERQ_CERQ_SHIFT                      (0U)
#define DMA_CERQ_CERQ(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CERQ_CERQ_SHIFT)) & DMA_CERQ_CERQ_MASK)
#define DMA_CERQ_CAER_MASK                       (0x40U)
#define DMA_CERQ_CAER_SHIFT                      (6U)
#define DMA_CERQ_CAER(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CERQ_CAER_SHIFT)) & DMA_CERQ_CAER_MASK)
#define DMA_CERQ_NOP_MASK                        (0x80U)
#define DMA_CERQ_NOP_SHIFT                       (7U)
#define DMA_CERQ_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_CERQ_NOP_SHIFT)) & DMA_CERQ_NOP_MASK)

/*! @name SERQ - Set Enable Request Register */
#define DMA_SERQ_SERQ_MASK                       (0x1FU)
#define DMA_SERQ_SERQ_SHIFT                      (0U)
#define DMA_SERQ_SERQ(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SERQ_SERQ_SHIFT)) & DMA_SERQ_SERQ_MASK)
#define DMA_SERQ_SAER_MASK                       (0x40U)
#define DMA_SERQ_SAER_SHIFT                      (6U)
#define DMA_SERQ_SAER(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SERQ_SAER_SHIFT)) & DMA_SERQ_SAER_MASK)
#define DMA_SERQ_NOP_MASK                        (0x80U)
#define DMA_SERQ_NOP_SHIFT                       (7U)
#define DMA_SERQ_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_SERQ_NOP_SHIFT)) & DMA_SERQ_NOP_MASK)

/*! @name CDNE - Clear DONE Status Bit Register */
#define DMA_CDNE_CDNE_MASK                       (0x1FU)
#define DMA_CDNE_CDNE_SHIFT                      (0U)
#define DMA_CDNE_CDNE(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CDNE_CDNE_SHIFT)) & DMA_CDNE_CDNE_MASK)
#define DMA_CDNE_CADN_MASK                       (0x40U)
#define DMA_CDNE_CADN_SHIFT                      (6U)
#define DMA_CDNE_CADN(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CDNE_CADN_SHIFT)) & DMA_CDNE_CADN_MASK)
#define DMA_CDNE_NOP_MASK                        (0x80U)
#define DMA_CDNE_NOP_SHIFT                       (7U)
#define DMA_CDNE_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_CDNE_NOP_SHIFT)) & DMA_CDNE_NOP_MASK)

/*! @name SSRT - Set START Bit Register */
#define DMA_SSRT_SSRT_MASK                       (0x1FU)
#define DMA_SSRT_SSRT_SHIFT                      (0U)
#define DMA_SSRT_SSRT(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SSRT_SSRT_SHIFT)) & DMA_SSRT_SSRT_MASK)
#define DMA_SSRT_SAST_MASK                       (0x40U)
#define DMA_SSRT_SAST_SHIFT                      (6U)
#define DMA_SSRT_SAST(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SSRT_SAST_SHIFT)) & DMA_SSRT_SAST_MASK)
#define DMA_SSRT_NOP_MASK                        (0x80U)
#define DMA_SSRT_NOP_SHIFT                       (7U)
#define DMA_SSRT_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_SSRT_NOP_SHIFT)) & DMA_SSRT_NOP_MASK)

/*! @name CERR - Clear Error Register */
#define DMA_CERR_CERR_MASK                       (0x1FU)
#define DMA_CERR_CERR_SHIFT                      (0U)
#define DMA_CERR_CERR(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CERR_CERR_SHIFT)) & DMA_CERR_CERR_MASK)
#define DMA_CERR_CAEI_MASK                       (0x40U)
#define DMA_CERR_CAEI_SHIFT                      (6U)
#define DMA_CERR_CAEI(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CERR_CAEI_SHIFT)) & DMA_CERR_CAEI_MASK)
#define DMA_CERR_NOP_MASK                        (0x80U)
#define DMA_CERR_NOP_SHIFT                       (7U)
#define DMA_CERR_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_CERR_NOP_SHIFT)) & DMA_CERR_NOP_MASK)

/*! @name CINT - Clear Interrupt Request Register */
#define DMA_CINT_CINT_MASK                       (0x1FU)
#define DMA_CINT_CINT_SHIFT                      (0U)
#define DMA_CINT_CINT(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CINT_CINT_SHIFT)) & DMA_CINT_CINT_MASK)
#define DMA_CINT_CAIR_MASK                       (0x40U)
#define DMA_CINT_CAIR_SHIFT                      (6U)
#define DMA_CINT_CAIR(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CINT_CAIR_SHIFT)) & DMA_CINT_CAIR_MASK)
#define DMA_CINT_NOP_MASK                        (0x80U)
#define DMA_CINT_NOP_SHIFT                       (7U)
#define DMA_CINT_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_CINT_NOP_SHIFT)) & DMA_CINT_NOP_MASK)

/*! @name INT - Interrupt Request Register */
#define DMA_INT_INT0_MASK                        (0x1U)
#define DMA_INT_INT0_SHIFT                       (0U)
#define DMA_INT_INT0(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT0_SHIFT)) & DMA_INT_INT0_MASK)
#define DMA_INT_INT1_MASK                        (0x2U)
#define DMA_INT_INT1_SHIFT                       (1U)
#define DMA_INT_INT1(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT1_SHIFT)) & DMA_INT_INT1_MASK)
#define DMA_INT_INT2_MASK                        (0x4U)
#define DMA_INT_INT2_SHIFT                       (2U)
#define DMA_INT_INT2(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT2_SHIFT)) & DMA_INT_INT2_MASK)
#define DMA_INT_INT3_MASK                        (0x8U)
#define DMA_INT_INT3_SHIFT                       (3U)
#define DMA_INT_INT3(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT3_SHIFT)) & DMA_INT_INT3_MASK)
#define DMA_INT_INT4_MASK                        (0x10U)
#define DMA_INT_INT4_SHIFT                       (4U)
#define DMA_INT_INT4(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT4_SHIFT)) & DMA_INT_INT4_MASK)
#define DMA_INT_INT5_MASK                        (0x20U)
#define DMA_INT_INT5_SHIFT                       (5U)
#define DMA_INT_INT5(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT5_SHIFT)) & DMA_INT_INT5_MASK)
#define DMA_INT_INT6_MASK                        (0x40U)
#define DMA_INT_INT6_SHIFT                       (6U)
#define DMA_INT_INT6(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT6_SHIFT)) & DMA_INT_INT6_MASK)
#define DMA_INT_INT7_MASK                        (0x80U)
#define DMA_INT_INT7_SHIFT                       (7U)
#define DMA_INT_INT7(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT7_SHIFT)) & DMA_INT_INT7_MASK)
#define DMA_INT_INT8_MASK                        (0x100U)
#define DMA_INT_INT8_SHIFT                       (8U)
#define DMA_INT_INT8(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT8_SHIFT)) & DMA_INT_INT8_MASK)
#define DMA_INT_INT9_MASK                        (0x200U)
#define DMA_INT_INT9_SHIFT                       (9U)
#define DMA_INT_INT9(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT9_SHIFT)) & DMA_INT_INT9_MASK)
#define DMA_INT_INT10_MASK                       (0x400U)
#define DMA_INT_INT10_SHIFT                      (10U)
#define DMA_INT_INT10(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT10_SHIFT)) & DMA_INT_INT10_MASK)
#define DMA_INT_INT11_MASK                       (0x800U)
#define DMA_INT_INT11_SHIFT                      (11U)
#define DMA_INT_INT11(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT11_SHIFT)) & DMA_INT_INT11_MASK)
#define DMA_INT_INT12_MASK                       (0x1000U)
#define DMA_INT_INT12_SHIFT                      (12U)
#define DMA_INT_INT12(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT12_SHIFT)) & DMA_INT_INT12_MASK)
#define DMA_INT_INT13_MASK                       (0x2000U)
#define DMA_INT_INT13_SHIFT                      (13U)
#define DMA_INT_INT13(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT13_SHIFT)) & DMA_INT_INT13_MASK)
#define DMA_INT_INT14_MASK                       (0x4000U)
#define DMA_INT_INT14_SHIFT                      (14U)
#define DMA_INT_INT14(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT14_SHIFT)) & DMA_INT_INT14_MASK)
#define DMA_INT_INT15_MASK                       (0x8000U)
#define DMA_INT_INT15_SHIFT                      (15U)
#define DMA_INT_INT15(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT15_SHIFT)) & DMA_INT_INT15_MASK)
#define DMA_INT_INT16_MASK                       (0x10000U)
#define DMA_INT_INT16_SHIFT                      (16U)
#define DMA_INT_INT16(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT16_SHIFT)) & DMA_INT_INT16_MASK)
#define DMA_INT_INT17_MASK                       (0x20000U)
#define DMA_INT_INT17_SHIFT                      (17U)
#define DMA_INT_INT17(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT17_SHIFT)) & DMA_INT_INT17_MASK)
#define DMA_INT_INT18_MASK                       (0x40000U)
#define DMA_INT_INT18_SHIFT                      (18U)
#define DMA_INT_INT18(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT18_SHIFT)) & DMA_INT_INT18_MASK)
#define DMA_INT_INT19_MASK                       (0x80000U)
#define DMA_INT_INT19_SHIFT                      (19U)
#define DMA_INT_INT19(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT19_SHIFT)) & DMA_INT_INT19_MASK)
#define DMA_INT_INT20_MASK                       (0x100000U)
#define DMA_INT_INT20_SHIFT                      (20U)
#define DMA_INT_INT20(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT20_SHIFT)) & DMA_INT_INT20_MASK)
#define DMA_INT_INT21_MASK                       (0x200000U)
#define DMA_INT_INT21_SHIFT                      (21U)
#define DMA_INT_INT21(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT21_SHIFT)) & DMA_INT_INT21_MASK)
#define DMA_INT_INT22_MASK                       (0x400000U)
#define DMA_INT_INT22_SHIFT                      (22U)
#define DMA_INT_INT22(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT22_SHIFT)) & DMA_INT_INT22_MASK)
#define DMA_INT_INT23_MASK                       (0x800000U)
#define DMA_INT_INT23_SHIFT                      (23U)
#define DMA_INT_INT23(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT23_SHIFT)) & DMA_INT_INT23_MASK)
#define DMA_INT_INT24_MASK                       (0x1000000U)
#define DMA_INT_INT24_SHIFT                      (24U)
#define DMA_INT_INT24(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT24_SHIFT)) & DMA_INT_INT24_MASK)
#define DMA_INT_INT25_MASK                       (0x2000000U)
#define DMA_INT_INT25_SHIFT                      (25U)
#define DMA_INT_INT25(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT25_SHIFT)) & DMA_INT_INT25_MASK)
#define DMA_INT_INT26_MASK                       (0x4000000U)
#define DMA_INT_INT26_SHIFT                      (26U)
#define DMA_INT_INT26(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT26_SHIFT)) & DMA_INT_INT26_MASK)
#define DMA_INT_INT27_MASK                       (0x8000000U)
#define DMA_INT_INT27_SHIFT                      (27U)
#define DMA_INT_INT27(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT27_SHIFT)) & DMA_INT_INT27_MASK)
#define DMA_INT_INT28_MASK                       (0x10000000U)
#define DMA_INT_INT28_SHIFT                      (28U)
#define DMA_INT_INT28(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT28_SHIFT)) & DMA_INT_INT28_MASK)
#define DMA_INT_INT29_MASK                       (0x20000000U)
#define DMA_INT_INT29_SHIFT                      (29U)
#define DMA_INT_INT29(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT29_SHIFT)) & DMA_INT_INT29_MASK)
#define DMA_INT_INT30_MASK                       (0x40000000U)
#define DMA_INT_INT30_SHIFT                      (30U)
#define DMA_INT_INT30(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT30_SHIFT)) & DMA_INT_INT30_MASK)
#define DMA_INT_INT31_MASK                       (0x80000000U)
#define DMA_INT_INT31_SHIFT                      (31U)
#define DMA_INT_INT31(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT31_SHIFT)) & DMA_INT_INT31_MASK)

/*! @name ERR - Error Register */
#define DMA_ERR_ERR0_MASK                        (0x1U)
#define DMA_ERR_ERR0_SHIFT                       (0U)
#define DMA_ERR_ERR0(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR0_SHIFT)) & DMA_ERR_ERR0_MASK)
#define DMA_ERR_ERR1_MASK                        (0x2U)
#define DMA_ERR_ERR1_SHIFT                       (1U)
#define DMA_ERR_ERR1(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR1_SHIFT)) & DMA_ERR_ERR1_MASK)
#define DMA_ERR_ERR2_MASK                        (0x4U)
#define DMA_ERR_ERR2_SHIFT                       (2U)
#define DMA_ERR_ERR2(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR2_SHIFT)) & DMA_ERR_ERR2_MASK)
#define DMA_ERR_ERR3_MASK                        (0x8U)
#define DMA_ERR_ERR3_SHIFT                       (3U)
#define DMA_ERR_ERR3(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR3_SHIFT)) & DMA_ERR_ERR3_MASK)
#define DMA_ERR_ERR4_MASK                        (0x10U)
#define DMA_ERR_ERR4_SHIFT                       (4U)
#define DMA_ERR_ERR4(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR4_SHIFT)) & DMA_ERR_ERR4_MASK)
#define DMA_ERR_ERR5_MASK                        (0x20U)
#define DMA_ERR_ERR5_SHIFT                       (5U)
#define DMA_ERR_ERR5(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR5_SHIFT)) & DMA_ERR_ERR5_MASK)
#define DMA_ERR_ERR6_MASK                        (0x40U)
#define DMA_ERR_ERR6_SHIFT                       (6U)
#define DMA_ERR_ERR6(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR6_SHIFT)) & DMA_ERR_ERR6_MASK)
#define DMA_ERR_ERR7_MASK                        (0x80U)
#define DMA_ERR_ERR7_SHIFT                       (7U)
#define DMA_ERR_ERR7(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR7_SHIFT)) & DMA_ERR_ERR7_MASK)
#define DMA_ERR_ERR8_MASK                        (0x100U)
#define DMA_ERR_ERR8_SHIFT                       (8U)
#define DMA_ERR_ERR8(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR8_SHIFT)) & DMA_ERR_ERR8_MASK)
#define DMA_ERR_ERR9_MASK                        (0x200U)
#define DMA_ERR_ERR9_SHIFT                       (9U)
#define DMA_ERR_ERR9(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR9_SHIFT)) & DMA_ERR_ERR9_MASK)
#define DMA_ERR_ERR10_MASK                       (0x400U)
#define DMA_ERR_ERR10_SHIFT                      (10U)
#define DMA_ERR_ERR10(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR10_SHIFT)) & DMA_ERR_ERR10_MASK)
#define DMA_ERR_ERR11_MASK                       (0x800U)
#define DMA_ERR_ERR11_SHIFT                      (11U)
#define DMA_ERR_ERR11(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR11_SHIFT)) & DMA_ERR_ERR11_MASK)
#define DMA_ERR_ERR12_MASK                       (0x1000U)
#define DMA_ERR_ERR12_SHIFT                      (12U)
#define DMA_ERR_ERR12(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR12_SHIFT)) & DMA_ERR_ERR12_MASK)
#define DMA_ERR_ERR13_MASK                       (0x2000U)
#define DMA_ERR_ERR13_SHIFT                      (13U)
#define DMA_ERR_ERR13(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR13_SHIFT)) & DMA_ERR_ERR13_MASK)
#define DMA_ERR_ERR14_MASK                       (0x4000U)
#define DMA_ERR_ERR14_SHIFT                      (14U)
#define DMA_ERR_ERR14(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR14_SHIFT)) & DMA_ERR_ERR14_MASK)
#define DMA_ERR_ERR15_MASK                       (0x8000U)
#define DMA_ERR_ERR15_SHIFT                      (15U)
#define DMA_ERR_ERR15(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR15_SHIFT)) & DMA_ERR_ERR15_MASK)
#define DMA_ERR_ERR16_MASK                       (0x10000U)
#define DMA_ERR_ERR16_SHIFT                      (16U)
#define DMA_ERR_ERR16(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR16_SHIFT)) & DMA_ERR_ERR16_MASK)
#define DMA_ERR_ERR17_MASK                       (0x20000U)
#define DMA_ERR_ERR17_SHIFT                      (17U)
#define DMA_ERR_ERR17(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR17_SHIFT)) & DMA_ERR_ERR17_MASK)
#define DMA_ERR_ERR18_MASK                       (0x40000U)
#define DMA_ERR_ERR18_SHIFT                      (18U)
#define DMA_ERR_ERR18(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR18_SHIFT)) & DMA_ERR_ERR18_MASK)
#define DMA_ERR_ERR19_MASK                       (0x80000U)
#define DMA_ERR_ERR19_SHIFT                      (19U)
#define DMA_ERR_ERR19(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR19_SHIFT)) & DMA_ERR_ERR19_MASK)
#define DMA_ERR_ERR20_MASK                       (0x100000U)
#define DMA_ERR_ERR20_SHIFT                      (20U)
#define DMA_ERR_ERR20(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR20_SHIFT)) & DMA_ERR_ERR20_MASK)
#define DMA_ERR_ERR21_MASK                       (0x200000U)
#define DMA_ERR_ERR21_SHIFT                      (21U)
#define DMA_ERR_ERR21(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR21_SHIFT)) & DMA_ERR_ERR21_MASK)
#define DMA_ERR_ERR22_MASK                       (0x400000U)
#define DMA_ERR_ERR22_SHIFT                      (22U)
#define DMA_ERR_ERR22(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR22_SHIFT)) & DMA_ERR_ERR22_MASK)
#define DMA_ERR_ERR23_MASK                       (0x800000U)
#define DMA_ERR_ERR23_SHIFT                      (23U)
#define DMA_ERR_ERR23(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR23_SHIFT)) & DMA_ERR_ERR23_MASK)
#define DMA_ERR_ERR24_MASK                       (0x1000000U)
#define DMA_ERR_ERR24_SHIFT                      (24U)
#define DMA_ERR_ERR24(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR24_SHIFT)) & DMA_ERR_ERR24_MASK)
#define DMA_ERR_ERR25_MASK                       (0x2000000U)
#define DMA_ERR_ERR25_SHIFT                      (25U)
#define DMA_ERR_ERR25(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR25_SHIFT)) & DMA_ERR_ERR25_MASK)
#define DMA_ERR_ERR26_MASK                       (0x4000000U)
#define DMA_ERR_ERR26_SHIFT                      (26U)
#define DMA_ERR_ERR26(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR26_SHIFT)) & DMA_ERR_ERR26_MASK)
#define DMA_ERR_ERR27_MASK                       (0x8000000U)
#define DMA_ERR_ERR27_SHIFT                      (27U)
#define DMA_ERR_ERR27(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR27_SHIFT)) & DMA_ERR_ERR27_MASK)
#define DMA_ERR_ERR28_MASK                       (0x10000000U)
#define DMA_ERR_ERR28_SHIFT                      (28U)
#define DMA_ERR_ERR28(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR28_SHIFT)) & DMA_ERR_ERR28_MASK)
#define DMA_ERR_ERR29_MASK                       (0x20000000U)
#define DMA_ERR_ERR29_SHIFT                      (29U)
#define DMA_ERR_ERR29(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR29_SHIFT)) & DMA_ERR_ERR29_MASK)
#define DMA_ERR_ERR30_MASK                       (0x40000000U)
#define DMA_ERR_ERR30_SHIFT                      (30U)
#define DMA_ERR_ERR30(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR30_SHIFT)) & DMA_ERR_ERR30_MASK)
#define DMA_ERR_ERR31_MASK                       (0x80000000U)
#define DMA_ERR_ERR31_SHIFT                      (31U)
#define DMA_ERR_ERR31(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR31_SHIFT)) & DMA_ERR_ERR31_MASK)

/*! @name HRS - Hardware Request Status Register */
#define DMA_HRS_HRS0_MASK                        (0x1U)
#define DMA_HRS_HRS0_SHIFT                       (0U)
#define DMA_HRS_HRS0(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS0_SHIFT)) & DMA_HRS_HRS0_MASK)
#define DMA_HRS_HRS1_MASK                        (0x2U)
#define DMA_HRS_HRS1_SHIFT                       (1U)
#define DMA_HRS_HRS1(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS1_SHIFT)) & DMA_HRS_HRS1_MASK)
#define DMA_HRS_HRS2_MASK                        (0x4U)
#define DMA_HRS_HRS2_SHIFT                       (2U)
#define DMA_HRS_HRS2(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS2_SHIFT)) & DMA_HRS_HRS2_MASK)
#define DMA_HRS_HRS3_MASK                        (0x8U)
#define DMA_HRS_HRS3_SHIFT                       (3U)
#define DMA_HRS_HRS3(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS3_SHIFT)) & DMA_HRS_HRS3_MASK)
#define DMA_HRS_HRS4_MASK                        (0x10U)
#define DMA_HRS_HRS4_SHIFT                       (4U)
#define DMA_HRS_HRS4(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS4_SHIFT)) & DMA_HRS_HRS4_MASK)
#define DMA_HRS_HRS5_MASK                        (0x20U)
#define DMA_HRS_HRS5_SHIFT                       (5U)
#define DMA_HRS_HRS5(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS5_SHIFT)) & DMA_HRS_HRS5_MASK)
#define DMA_HRS_HRS6_MASK                        (0x40U)
#define DMA_HRS_HRS6_SHIFT                       (6U)
#define DMA_HRS_HRS6(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS6_SHIFT)) & DMA_HRS_HRS6_MASK)
#define DMA_HRS_HRS7_MASK                        (0x80U)
#define DMA_HRS_HRS7_SHIFT                       (7U)
#define DMA_HRS_HRS7(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS7_SHIFT)) & DMA_HRS_HRS7_MASK)
#define DMA_HRS_HRS8_MASK                        (0x100U)
#define DMA_HRS_HRS8_SHIFT                       (8U)
#define DMA_HRS_HRS8(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS8_SHIFT)) & DMA_HRS_HRS8_MASK)
#define DMA_HRS_HRS9_MASK                        (0x200U)
#define DMA_HRS_HRS9_SHIFT                       (9U)
#define DMA_HRS_HRS9(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS9_SHIFT)) & DMA_HRS_HRS9_MASK)
#define DMA_HRS_HRS10_MASK                       (0x400U)
#define DMA_HRS_HRS10_SHIFT                      (10U)
#define DMA_HRS_HRS10(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS10_SHIFT)) & DMA_HRS_HRS10_MASK)
#define DMA_HRS_HRS11_MASK                       (0x800U)
#define DMA_HRS_HRS11_SHIFT                      (11U)
#define DMA_HRS_HRS11(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS11_SHIFT)) & DMA_HRS_HRS11_MASK)
#define DMA_HRS_HRS12_MASK                       (0x1000U)
#define DMA_HRS_HRS12_SHIFT                      (12U)
#define DMA_HRS_HRS12(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS12_SHIFT)) & DMA_HRS_HRS12_MASK)
#define DMA_HRS_HRS13_MASK                       (0x2000U)
#define DMA_HRS_HRS13_SHIFT                      (13U)
#define DMA_HRS_HRS13(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS13_SHIFT)) & DMA_HRS_HRS13_MASK)
#define DMA_HRS_HRS14_MASK                       (0x4000U)
#define DMA_HRS_HRS14_SHIFT                      (14U)
#define DMA_HRS_HRS14(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS14_SHIFT)) & DMA_HRS_HRS14_MASK)
#define DMA_HRS_HRS15_MASK                       (0x8000U)
#define DMA_HRS_HRS15_SHIFT                      (15U)
#define DMA_HRS_HRS15(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS15_SHIFT)) & DMA_HRS_HRS15_MASK)
#define DMA_HRS_HRS16_MASK                       (0x10000U)
#define DMA_HRS_HRS16_SHIFT                      (16U)
#define DMA_HRS_HRS16(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS16_SHIFT)) & DMA_HRS_HRS16_MASK)
#define DMA_HRS_HRS17_MASK                       (0x20000U)
#define DMA_HRS_HRS17_SHIFT                      (17U)
#define DMA_HRS_HRS17(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS17_SHIFT)) & DMA_HRS_HRS17_MASK)
#define DMA_HRS_HRS18_MASK                       (0x40000U)
#define DMA_HRS_HRS18_SHIFT                      (18U)
#define DMA_HRS_HRS18(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS18_SHIFT)) & DMA_HRS_HRS18_MASK)
#define DMA_HRS_HRS19_MASK                       (0x80000U)
#define DMA_HRS_HRS19_SHIFT                      (19U)
#define DMA_HRS_HRS19(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS19_SHIFT)) & DMA_HRS_HRS19_MASK)
#define DMA_HRS_HRS20_MASK                       (0x100000U)
#define DMA_HRS_HRS20_SHIFT                      (20U)
#define DMA_HRS_HRS20(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS20_SHIFT)) & DMA_HRS_HRS20_MASK)
#define DMA_HRS_HRS21_MASK                       (0x200000U)
#define DMA_HRS_HRS21_SHIFT                      (21U)
#define DMA_HRS_HRS21(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS21_SHIFT)) & DMA_HRS_HRS21_MASK)
#define DMA_HRS_HRS22_MASK                       (0x400000U)
#define DMA_HRS_HRS22_SHIFT                      (22U)
#define DMA_HRS_HRS22(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS22_SHIFT)) & DMA_HRS_HRS22_MASK)
#define DMA_HRS_HRS23_MASK                       (0x800000U)
#define DMA_HRS_HRS23_SHIFT                      (23U)
#define DMA_HRS_HRS23(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS23_SHIFT)) & DMA_HRS_HRS23_MASK)
#define DMA_HRS_HRS24_MASK                       (0x1000000U)
#define DMA_HRS_HRS24_SHIFT                      (24U)
#define DMA_HRS_HRS24(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS24_SHIFT)) & DMA_HRS_HRS24_MASK)
#define DMA_HRS_HRS25_MASK                       (0x2000000U)
#define DMA_HRS_HRS25_SHIFT                      (25U)
#define DMA_HRS_HRS25(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS25_SHIFT)) & DMA_HRS_HRS25_MASK)
#define DMA_HRS_HRS26_MASK                       (0x4000000U)
#define DMA_HRS_HRS26_SHIFT                      (26U)
#define DMA_HRS_HRS26(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS26_SHIFT)) & DMA_HRS_HRS26_MASK)
#define DMA_HRS_HRS27_MASK                       (0x8000000U)
#define DMA_HRS_HRS27_SHIFT                      (27U)
#define DMA_HRS_HRS27(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS27_SHIFT)) & DMA_HRS_HRS27_MASK)
#define DMA_HRS_HRS28_MASK                       (0x10000000U)
#define DMA_HRS_HRS28_SHIFT                      (28U)
#define DMA_HRS_HRS28(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS28_SHIFT)) & DMA_HRS_HRS28_MASK)
#define DMA_HRS_HRS29_MASK                       (0x20000000U)
#define DMA_HRS_HRS29_SHIFT                      (29U)
#define DMA_HRS_HRS29(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS29_SHIFT)) & DMA_HRS_HRS29_MASK)
#define DMA_HRS_HRS30_MASK                       (0x40000000U)
#define DMA_HRS_HRS30_SHIFT                      (30U)
#define DMA_HRS_HRS30(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS30_SHIFT)) & DMA_HRS_HRS30_MASK)
#define DMA_HRS_HRS31_MASK                       (0x80000000U)
#define DMA_HRS_HRS31_SHIFT                      (31U)
#define DMA_HRS_HRS31(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS31_SHIFT)) & DMA_HRS_HRS31_MASK)

/*! @name EARS - Enable Asynchronous Request in Stop Register */
#define DMA_EARS_EDREQ_0_MASK                    (0x1U)
#define DMA_EARS_EDREQ_0_SHIFT                   (0U)
#define DMA_EARS_EDREQ_0(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_0_SHIFT)) & DMA_EARS_EDREQ_0_MASK)
#define DMA_EARS_EDREQ_1_MASK                    (0x2U)
#define DMA_EARS_EDREQ_1_SHIFT                   (1U)
#define DMA_EARS_EDREQ_1(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_1_SHIFT)) & DMA_EARS_EDREQ_1_MASK)
#define DMA_EARS_EDREQ_2_MASK                    (0x4U)
#define DMA_EARS_EDREQ_2_SHIFT                   (2U)
#define DMA_EARS_EDREQ_2(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_2_SHIFT)) & DMA_EARS_EDREQ_2_MASK)
#define DMA_EARS_EDREQ_3_MASK                    (0x8U)
#define DMA_EARS_EDREQ_3_SHIFT                   (3U)
#define DMA_EARS_EDREQ_3(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_3_SHIFT)) & DMA_EARS_EDREQ_3_MASK)
#define DMA_EARS_EDREQ_4_MASK                    (0x10U)
#define DMA_EARS_EDREQ_4_SHIFT                   (4U)
#define DMA_EARS_EDREQ_4(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_4_SHIFT)) & DMA_EARS_EDREQ_4_MASK)
#define DMA_EARS_EDREQ_5_MASK                    (0x20U)
#define DMA_EARS_EDREQ_5_SHIFT                   (5U)
#define DMA_EARS_EDREQ_5(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_5_SHIFT)) & DMA_EARS_EDREQ_5_MASK)
#define DMA_EARS_EDREQ_6_MASK                    (0x40U)
#define DMA_EARS_EDREQ_6_SHIFT                   (6U)
#define DMA_EARS_EDREQ_6(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_6_SHIFT)) & DMA_EARS_EDREQ_6_MASK)
#define DMA_EARS_EDREQ_7_MASK                    (0x80U)
#define DMA_EARS_EDREQ_7_SHIFT                   (7U)
#define DMA_EARS_EDREQ_7(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_7_SHIFT)) & DMA_EARS_EDREQ_7_MASK)
#define DMA_EARS_EDREQ_8_MASK                    (0x100U)
#define DMA_EARS_EDREQ_8_SHIFT                   (8U)
#define DMA_EARS_EDREQ_8(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_8_SHIFT)) & DMA_EARS_EDREQ_8_MASK)
#define DMA_EARS_EDREQ_9_MASK                    (0x200U)
#define DMA_EARS_EDREQ_9_SHIFT                   (9U)
#define DMA_EARS_EDREQ_9(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_9_SHIFT)) & DMA_EARS_EDREQ_9_MASK)
#define DMA_EARS_EDREQ_10_MASK                   (0x400U)
#define DMA_EARS_EDREQ_10_SHIFT                  (10U)
#define DMA_EARS_EDREQ_10(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_10_SHIFT)) & DMA_EARS_EDREQ_10_MASK)
#define DMA_EARS_EDREQ_11_MASK                   (0x800U)
#define DMA_EARS_EDREQ_11_SHIFT                  (11U)
#define DMA_EARS_EDREQ_11(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_11_SHIFT)) & DMA_EARS_EDREQ_11_MASK)
#define DMA_EARS_EDREQ_12_MASK                   (0x1000U)
#define DMA_EARS_EDREQ_12_SHIFT                  (12U)
#define DMA_EARS_EDREQ_12(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_12_SHIFT)) & DMA_EARS_EDREQ_12_MASK)
#define DMA_EARS_EDREQ_13_MASK                   (0x2000U)
#define DMA_EARS_EDREQ_13_SHIFT                  (13U)
#define DMA_EARS_EDREQ_13(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_13_SHIFT)) & DMA_EARS_EDREQ_13_MASK)
#define DMA_EARS_EDREQ_14_MASK                   (0x4000U)
#define DMA_EARS_EDREQ_14_SHIFT                  (14U)
#define DMA_EARS_EDREQ_14(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_14_SHIFT)) & DMA_EARS_EDREQ_14_MASK)
#define DMA_EARS_EDREQ_15_MASK                   (0x8000U)
#define DMA_EARS_EDREQ_15_SHIFT                  (15U)
#define DMA_EARS_EDREQ_15(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_15_SHIFT)) & DMA_EARS_EDREQ_15_MASK)
#define DMA_EARS_EDREQ_16_MASK                   (0x10000U)
#define DMA_EARS_EDREQ_16_SHIFT                  (16U)
#define DMA_EARS_EDREQ_16(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_16_SHIFT)) & DMA_EARS_EDREQ_16_MASK)
#define DMA_EARS_EDREQ_17_MASK                   (0x20000U)
#define DMA_EARS_EDREQ_17_SHIFT                  (17U)
#define DMA_EARS_EDREQ_17(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_17_SHIFT)) & DMA_EARS_EDREQ_17_MASK)
#define DMA_EARS_EDREQ_18_MASK                   (0x40000U)
#define DMA_EARS_EDREQ_18_SHIFT                  (18U)
#define DMA_EARS_EDREQ_18(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_18_SHIFT)) & DMA_EARS_EDREQ_18_MASK)
#define DMA_EARS_EDREQ_19_MASK                   (0x80000U)
#define DMA_EARS_EDREQ_19_SHIFT                  (19U)
#define DMA_EARS_EDREQ_19(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_19_SHIFT)) & DMA_EARS_EDREQ_19_MASK)
#define DMA_EARS_EDREQ_20_MASK                   (0x100000U)
#define DMA_EARS_EDREQ_20_SHIFT                  (20U)
#define DMA_EARS_EDREQ_20(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_20_SHIFT)) & DMA_EARS_EDREQ_20_MASK)
#define DMA_EARS_EDREQ_21_MASK                   (0x200000U)
#define DMA_EARS_EDREQ_21_SHIFT                  (21U)
#define DMA_EARS_EDREQ_21(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_21_SHIFT)) & DMA_EARS_EDREQ_21_MASK)
#define DMA_EARS_EDREQ_22_MASK                   (0x400000U)
#define DMA_EARS_EDREQ_22_SHIFT                  (22U)
#define DMA_EARS_EDREQ_22(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_22_SHIFT)) & DMA_EARS_EDREQ_22_MASK)
#define DMA_EARS_EDREQ_23_MASK                   (0x800000U)
#define DMA_EARS_EDREQ_23_SHIFT                  (23U)
#define DMA_EARS_EDREQ_23(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_23_SHIFT)) & DMA_EARS_EDREQ_23_MASK)
#define DMA_EARS_EDREQ_24_MASK                   (0x1000000U)
#define DMA_EARS_EDREQ_24_SHIFT                  (24U)
#define DMA_EARS_EDREQ_24(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_24_SHIFT)) & DMA_EARS_EDREQ_24_MASK)
#define DMA_EARS_EDREQ_25_MASK                   (0x2000000U)
#define DMA_EARS_EDREQ_25_SHIFT                  (25U)
#define DMA_EARS_EDREQ_25(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_25_SHIFT)) & DMA_EARS_EDREQ_25_MASK)
#define DMA_EARS_EDREQ_26_MASK                   (0x4000000U)
#define DMA_EARS_EDREQ_26_SHIFT                  (26U)
#define DMA_EARS_EDREQ_26(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_26_SHIFT)) & DMA_EARS_EDREQ_26_MASK)
#define DMA_EARS_EDREQ_27_MASK                   (0x8000000U)
#define DMA_EARS_EDREQ_27_SHIFT                  (27U)
#define DMA_EARS_EDREQ_27(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_27_SHIFT)) & DMA_EARS_EDREQ_27_MASK)
#define DMA_EARS_EDREQ_28_MASK                   (0x10000000U)
#define DMA_EARS_EDREQ_28_SHIFT                  (28U)
#define DMA_EARS_EDREQ_28(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_28_SHIFT)) & DMA_EARS_EDREQ_28_MASK)
#define DMA_EARS_EDREQ_29_MASK                   (0x20000000U)
#define DMA_EARS_EDREQ_29_SHIFT                  (29U)
#define DMA_EARS_EDREQ_29(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_29_SHIFT)) & DMA_EARS_EDREQ_29_MASK)
#define DMA_EARS_EDREQ_30_MASK                   (0x40000000U)
#define DMA_EARS_EDREQ_30_SHIFT                  (30U)
#define DMA_EARS_EDREQ_30(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_30_SHIFT)) & DMA_EARS_EDREQ_30_MASK)
#define DMA_EARS_EDREQ_31_MASK                   (0x80000000U)
#define DMA_EARS_EDREQ_31_SHIFT                  (31U)
#define DMA_EARS_EDREQ_31(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_31_SHIFT)) & DMA_EARS_EDREQ_31_MASK)

/*! @name DCHPRI3 - Channel n Priority Register */
#define DMA_DCHPRI3_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI3_CHPRI_SHIFT                  (0U)
#define DMA_DCHPRI3_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI3_CHPRI_SHIFT)) & DMA_DCHPRI3_CHPRI_MASK)
#define DMA_DCHPRI3_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI3_GRPPRI_SHIFT                 (4U)
#define DMA_DCHPRI3_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI3_GRPPRI_SHIFT)) & DMA_DCHPRI3_GRPPRI_MASK)
#define DMA_DCHPRI3_DPA_MASK                     (0x40U)
#define DMA_DCHPRI3_DPA_SHIFT                    (6U)
#define DMA_DCHPRI3_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI3_DPA_SHIFT)) & DMA_DCHPRI3_DPA_MASK)
#define DMA_DCHPRI3_ECP_MASK                     (0x80U)
#define DMA_DCHPRI3_ECP_SHIFT                    (7U)
#define DMA_DCHPRI3_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI3_ECP_SHIFT)) & DMA_DCHPRI3_ECP_MASK)

/*! @name DCHPRI2 - Channel n Priority Register */
#define DMA_DCHPRI2_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI2_CHPRI_SHIFT                  (0U)
#define DMA_DCHPRI2_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI2_CHPRI_SHIFT)) & DMA_DCHPRI2_CHPRI_MASK)
#define DMA_DCHPRI2_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI2_GRPPRI_SHIFT                 (4U)
#define DMA_DCHPRI2_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI2_GRPPRI_SHIFT)) & DMA_DCHPRI2_GRPPRI_MASK)
#define DMA_DCHPRI2_DPA_MASK                     (0x40U)
#define DMA_DCHPRI2_DPA_SHIFT                    (6U)
#define DMA_DCHPRI2_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI2_DPA_SHIFT)) & DMA_DCHPRI2_DPA_MASK)
#define DMA_DCHPRI2_ECP_MASK                     (0x80U)
#define DMA_DCHPRI2_ECP_SHIFT                    (7U)
#define DMA_DCHPRI2_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI2_ECP_SHIFT)) & DMA_DCHPRI2_ECP_MASK)

/*! @name DCHPRI1 - Channel n Priority Register */
#define DMA_DCHPRI1_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI1_CHPRI_SHIFT                  (0U)
#define DMA_DCHPRI1_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI1_CHPRI_SHIFT)) & DMA_DCHPRI1_CHPRI_MASK)
#define DMA_DCHPRI1_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI1_GRPPRI_SHIFT                 (4U)
#define DMA_DCHPRI1_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI1_GRPPRI_SHIFT)) & DMA_DCHPRI1_GRPPRI_MASK)
#define DMA_DCHPRI1_DPA_MASK                     (0x40U)
#define DMA_DCHPRI1_DPA_SHIFT                    (6U)
#define DMA_DCHPRI1_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI1_DPA_SHIFT)) & DMA_DCHPRI1_DPA_MASK)
#define DMA_DCHPRI1_ECP_MASK                     (0x80U)
#define DMA_DCHPRI1_ECP_SHIFT                    (7U)
#define DMA_DCHPRI1_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI1_ECP_SHIFT)) & DMA_DCHPRI1_ECP_MASK)

/*! @name DCHPRI0 - Channel n Priority Register */
#define DMA_DCHPRI0_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI0_CHPRI_SHIFT                  (0U)
#define DMA_DCHPRI0_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI0_CHPRI_SHIFT)) & DMA_DCHPRI0_CHPRI_MASK)
#define DMA_DCHPRI0_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI0_GRPPRI_SHIFT                 (4U)
#define DMA_DCHPRI0_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI0_GRPPRI_SHIFT)) & DMA_DCHPRI0_GRPPRI_MASK)
#define DMA_DCHPRI0_DPA_MASK                     (0x40U)
#define DMA_DCHPRI0_DPA_SHIFT                    (6U)
#define DMA_DCHPRI0_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI0_DPA_SHIFT)) & DMA_DCHPRI0_DPA_MASK)
#define DMA_DCHPRI0_ECP_MASK                     (0x80U)
#define DMA_DCHPRI0_ECP_SHIFT                    (7U)
#define DMA_DCHPRI0_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI0_ECP_SHIFT)) & DMA_DCHPRI0_ECP_MASK)

/*! @name DCHPRI7 - Channel n Priority Register */
#define DMA_DCHPRI7_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI7_CHPRI_SHIFT                  (0U)
#define DMA_DCHPRI7_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI7_CHPRI_SHIFT)) & DMA_DCHPRI7_CHPRI_MASK)
#define DMA_DCHPRI7_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI7_GRPPRI_SHIFT                 (4U)
#define DMA_DCHPRI7_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI7_GRPPRI_SHIFT)) & DMA_DCHPRI7_GRPPRI_MASK)
#define DMA_DCHPRI7_DPA_MASK                     (0x40U)
#define DMA_DCHPRI7_DPA_SHIFT                    (6U)
#define DMA_DCHPRI7_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI7_DPA_SHIFT)) & DMA_DCHPRI7_DPA_MASK)
#define DMA_DCHPRI7_ECP_MASK                     (0x80U)
#define DMA_DCHPRI7_ECP_SHIFT                    (7U)
#define DMA_DCHPRI7_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI7_ECP_SHIFT)) & DMA_DCHPRI7_ECP_MASK)

/*! @name DCHPRI6 - Channel n Priority Register */
#define DMA_DCHPRI6_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI6_CHPRI_SHIFT                  (0U)
#define DMA_DCHPRI6_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI6_CHPRI_SHIFT)) & DMA_DCHPRI6_CHPRI_MASK)
#define DMA_DCHPRI6_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI6_GRPPRI_SHIFT                 (4U)
#define DMA_DCHPRI6_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI6_GRPPRI_SHIFT)) & DMA_DCHPRI6_GRPPRI_MASK)
#define DMA_DCHPRI6_DPA_MASK                     (0x40U)
#define DMA_DCHPRI6_DPA_SHIFT                    (6U)
#define DMA_DCHPRI6_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI6_DPA_SHIFT)) & DMA_DCHPRI6_DPA_MASK)
#define DMA_DCHPRI6_ECP_MASK                     (0x80U)
#define DMA_DCHPRI6_ECP_SHIFT                    (7U)
#define DMA_DCHPRI6_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI6_ECP_SHIFT)) & DMA_DCHPRI6_ECP_MASK)

/*! @name DCHPRI5 - Channel n Priority Register */
#define DMA_DCHPRI5_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI5_CHPRI_SHIFT                  (0U)
#define DMA_DCHPRI5_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI5_CHPRI_SHIFT)) & DMA_DCHPRI5_CHPRI_MASK)
#define DMA_DCHPRI5_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI5_GRPPRI_SHIFT                 (4U)
#define DMA_DCHPRI5_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI5_GRPPRI_SHIFT)) & DMA_DCHPRI5_GRPPRI_MASK)
#define DMA_DCHPRI5_DPA_MASK                     (0x40U)
#define DMA_DCHPRI5_DPA_SHIFT                    (6U)
#define DMA_DCHPRI5_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI5_DPA_SHIFT)) & DMA_DCHPRI5_DPA_MASK)
#define DMA_DCHPRI5_ECP_MASK                     (0x80U)
#define DMA_DCHPRI5_ECP_SHIFT                    (7U)
#define DMA_DCHPRI5_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI5_ECP_SHIFT)) & DMA_DCHPRI5_ECP_MASK)

/*! @name DCHPRI4 - Channel n Priority Register */
#define DMA_DCHPRI4_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI4_CHPRI_SHIFT                  (0U)
#define DMA_DCHPRI4_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI4_CHPRI_SHIFT)) & DMA_DCHPRI4_CHPRI_MASK)
#define DMA_DCHPRI4_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI4_GRPPRI_SHIFT                 (4U)
#define DMA_DCHPRI4_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI4_GRPPRI_SHIFT)) & DMA_DCHPRI4_GRPPRI_MASK)
#define DMA_DCHPRI4_DPA_MASK                     (0x40U)
#define DMA_DCHPRI4_DPA_SHIFT                    (6U)
#define DMA_DCHPRI4_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI4_DPA_SHIFT)) & DMA_DCHPRI4_DPA_MASK)
#define DMA_DCHPRI4_ECP_MASK                     (0x80U)
#define DMA_DCHPRI4_ECP_SHIFT                    (7U)
#define DMA_DCHPRI4_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI4_ECP_SHIFT)) & DMA_DCHPRI4_ECP_MASK)

/*! @name DCHPRI11 - Channel n Priority Register */
#define DMA_DCHPRI11_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI11_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI11_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI11_CHPRI_SHIFT)) & DMA_DCHPRI11_CHPRI_MASK)
#define DMA_DCHPRI11_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI11_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI11_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI11_GRPPRI_SHIFT)) & DMA_DCHPRI11_GRPPRI_MASK)
#define DMA_DCHPRI11_DPA_MASK                    (0x40U)
#define DMA_DCHPRI11_DPA_SHIFT                   (6U)
#define DMA_DCHPRI11_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI11_DPA_SHIFT)) & DMA_DCHPRI11_DPA_MASK)
#define DMA_DCHPRI11_ECP_MASK                    (0x80U)
#define DMA_DCHPRI11_ECP_SHIFT                   (7U)
#define DMA_DCHPRI11_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI11_ECP_SHIFT)) & DMA_DCHPRI11_ECP_MASK)

/*! @name DCHPRI10 - Channel n Priority Register */
#define DMA_DCHPRI10_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI10_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI10_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI10_CHPRI_SHIFT)) & DMA_DCHPRI10_CHPRI_MASK)
#define DMA_DCHPRI10_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI10_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI10_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI10_GRPPRI_SHIFT)) & DMA_DCHPRI10_GRPPRI_MASK)
#define DMA_DCHPRI10_DPA_MASK                    (0x40U)
#define DMA_DCHPRI10_DPA_SHIFT                   (6U)
#define DMA_DCHPRI10_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI10_DPA_SHIFT)) & DMA_DCHPRI10_DPA_MASK)
#define DMA_DCHPRI10_ECP_MASK                    (0x80U)
#define DMA_DCHPRI10_ECP_SHIFT                   (7U)
#define DMA_DCHPRI10_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI10_ECP_SHIFT)) & DMA_DCHPRI10_ECP_MASK)

/*! @name DCHPRI9 - Channel n Priority Register */
#define DMA_DCHPRI9_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI9_CHPRI_SHIFT                  (0U)
#define DMA_DCHPRI9_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI9_CHPRI_SHIFT)) & DMA_DCHPRI9_CHPRI_MASK)
#define DMA_DCHPRI9_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI9_GRPPRI_SHIFT                 (4U)
#define DMA_DCHPRI9_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI9_GRPPRI_SHIFT)) & DMA_DCHPRI9_GRPPRI_MASK)
#define DMA_DCHPRI9_DPA_MASK                     (0x40U)
#define DMA_DCHPRI9_DPA_SHIFT                    (6U)
#define DMA_DCHPRI9_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI9_DPA_SHIFT)) & DMA_DCHPRI9_DPA_MASK)
#define DMA_DCHPRI9_ECP_MASK                     (0x80U)
#define DMA_DCHPRI9_ECP_SHIFT                    (7U)
#define DMA_DCHPRI9_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI9_ECP_SHIFT)) & DMA_DCHPRI9_ECP_MASK)

/*! @name DCHPRI8 - Channel n Priority Register */
#define DMA_DCHPRI8_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI8_CHPRI_SHIFT                  (0U)
#define DMA_DCHPRI8_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI8_CHPRI_SHIFT)) & DMA_DCHPRI8_CHPRI_MASK)
#define DMA_DCHPRI8_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI8_GRPPRI_SHIFT                 (4U)
#define DMA_DCHPRI8_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI8_GRPPRI_SHIFT)) & DMA_DCHPRI8_GRPPRI_MASK)
#define DMA_DCHPRI8_DPA_MASK                     (0x40U)
#define DMA_DCHPRI8_DPA_SHIFT                    (6U)
#define DMA_DCHPRI8_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI8_DPA_SHIFT)) & DMA_DCHPRI8_DPA_MASK)
#define DMA_DCHPRI8_ECP_MASK                     (0x80U)
#define DMA_DCHPRI8_ECP_SHIFT                    (7U)
#define DMA_DCHPRI8_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI8_ECP_SHIFT)) & DMA_DCHPRI8_ECP_MASK)

/*! @name DCHPRI15 - Channel n Priority Register */
#define DMA_DCHPRI15_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI15_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI15_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI15_CHPRI_SHIFT)) & DMA_DCHPRI15_CHPRI_MASK)
#define DMA_DCHPRI15_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI15_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI15_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI15_GRPPRI_SHIFT)) & DMA_DCHPRI15_GRPPRI_MASK)
#define DMA_DCHPRI15_DPA_MASK                    (0x40U)
#define DMA_DCHPRI15_DPA_SHIFT                   (6U)
#define DMA_DCHPRI15_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI15_DPA_SHIFT)) & DMA_DCHPRI15_DPA_MASK)
#define DMA_DCHPRI15_ECP_MASK                    (0x80U)
#define DMA_DCHPRI15_ECP_SHIFT                   (7U)
#define DMA_DCHPRI15_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI15_ECP_SHIFT)) & DMA_DCHPRI15_ECP_MASK)

/*! @name DCHPRI14 - Channel n Priority Register */
#define DMA_DCHPRI14_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI14_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI14_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI14_CHPRI_SHIFT)) & DMA_DCHPRI14_CHPRI_MASK)
#define DMA_DCHPRI14_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI14_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI14_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI14_GRPPRI_SHIFT)) & DMA_DCHPRI14_GRPPRI_MASK)
#define DMA_DCHPRI14_DPA_MASK                    (0x40U)
#define DMA_DCHPRI14_DPA_SHIFT                   (6U)
#define DMA_DCHPRI14_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI14_DPA_SHIFT)) & DMA_DCHPRI14_DPA_MASK)
#define DMA_DCHPRI14_ECP_MASK                    (0x80U)
#define DMA_DCHPRI14_ECP_SHIFT                   (7U)
#define DMA_DCHPRI14_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI14_ECP_SHIFT)) & DMA_DCHPRI14_ECP_MASK)

/*! @name DCHPRI13 - Channel n Priority Register */
#define DMA_DCHPRI13_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI13_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI13_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI13_CHPRI_SHIFT)) & DMA_DCHPRI13_CHPRI_MASK)
#define DMA_DCHPRI13_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI13_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI13_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI13_GRPPRI_SHIFT)) & DMA_DCHPRI13_GRPPRI_MASK)
#define DMA_DCHPRI13_DPA_MASK                    (0x40U)
#define DMA_DCHPRI13_DPA_SHIFT                   (6U)
#define DMA_DCHPRI13_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI13_DPA_SHIFT)) & DMA_DCHPRI13_DPA_MASK)
#define DMA_DCHPRI13_ECP_MASK                    (0x80U)
#define DMA_DCHPRI13_ECP_SHIFT                   (7U)
#define DMA_DCHPRI13_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI13_ECP_SHIFT)) & DMA_DCHPRI13_ECP_MASK)

/*! @name DCHPRI12 - Channel n Priority Register */
#define DMA_DCHPRI12_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI12_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI12_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI12_CHPRI_SHIFT)) & DMA_DCHPRI12_CHPRI_MASK)
#define DMA_DCHPRI12_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI12_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI12_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI12_GRPPRI_SHIFT)) & DMA_DCHPRI12_GRPPRI_MASK)
#define DMA_DCHPRI12_DPA_MASK                    (0x40U)
#define DMA_DCHPRI12_DPA_SHIFT                   (6U)
#define DMA_DCHPRI12_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI12_DPA_SHIFT)) & DMA_DCHPRI12_DPA_MASK)
#define DMA_DCHPRI12_ECP_MASK                    (0x80U)
#define DMA_DCHPRI12_ECP_SHIFT                   (7U)
#define DMA_DCHPRI12_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI12_ECP_SHIFT)) & DMA_DCHPRI12_ECP_MASK)

/*! @name DCHPRI19 - Channel n Priority Register */
#define DMA_DCHPRI19_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI19_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI19_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI19_CHPRI_SHIFT)) & DMA_DCHPRI19_CHPRI_MASK)
#define DMA_DCHPRI19_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI19_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI19_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI19_GRPPRI_SHIFT)) & DMA_DCHPRI19_GRPPRI_MASK)
#define DMA_DCHPRI19_DPA_MASK                    (0x40U)
#define DMA_DCHPRI19_DPA_SHIFT                   (6U)
#define DMA_DCHPRI19_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI19_DPA_SHIFT)) & DMA_DCHPRI19_DPA_MASK)
#define DMA_DCHPRI19_ECP_MASK                    (0x80U)
#define DMA_DCHPRI19_ECP_SHIFT                   (7U)
#define DMA_DCHPRI19_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI19_ECP_SHIFT)) & DMA_DCHPRI19_ECP_MASK)

/*! @name DCHPRI18 - Channel n Priority Register */
#define DMA_DCHPRI18_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI18_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI18_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI18_CHPRI_SHIFT)) & DMA_DCHPRI18_CHPRI_MASK)
#define DMA_DCHPRI18_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI18_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI18_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI18_GRPPRI_SHIFT)) & DMA_DCHPRI18_GRPPRI_MASK)
#define DMA_DCHPRI18_DPA_MASK                    (0x40U)
#define DMA_DCHPRI18_DPA_SHIFT                   (6U)
#define DMA_DCHPRI18_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI18_DPA_SHIFT)) & DMA_DCHPRI18_DPA_MASK)
#define DMA_DCHPRI18_ECP_MASK                    (0x80U)
#define DMA_DCHPRI18_ECP_SHIFT                   (7U)
#define DMA_DCHPRI18_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI18_ECP_SHIFT)) & DMA_DCHPRI18_ECP_MASK)

/*! @name DCHPRI17 - Channel n Priority Register */
#define DMA_DCHPRI17_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI17_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI17_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI17_CHPRI_SHIFT)) & DMA_DCHPRI17_CHPRI_MASK)
#define DMA_DCHPRI17_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI17_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI17_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI17_GRPPRI_SHIFT)) & DMA_DCHPRI17_GRPPRI_MASK)
#define DMA_DCHPRI17_DPA_MASK                    (0x40U)
#define DMA_DCHPRI17_DPA_SHIFT                   (6U)
#define DMA_DCHPRI17_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI17_DPA_SHIFT)) & DMA_DCHPRI17_DPA_MASK)
#define DMA_DCHPRI17_ECP_MASK                    (0x80U)
#define DMA_DCHPRI17_ECP_SHIFT                   (7U)
#define DMA_DCHPRI17_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI17_ECP_SHIFT)) & DMA_DCHPRI17_ECP_MASK)

/*! @name DCHPRI16 - Channel n Priority Register */
#define DMA_DCHPRI16_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI16_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI16_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI16_CHPRI_SHIFT)) & DMA_DCHPRI16_CHPRI_MASK)
#define DMA_DCHPRI16_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI16_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI16_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI16_GRPPRI_SHIFT)) & DMA_DCHPRI16_GRPPRI_MASK)
#define DMA_DCHPRI16_DPA_MASK                    (0x40U)
#define DMA_DCHPRI16_DPA_SHIFT                   (6U)
#define DMA_DCHPRI16_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI16_DPA_SHIFT)) & DMA_DCHPRI16_DPA_MASK)
#define DMA_DCHPRI16_ECP_MASK                    (0x80U)
#define DMA_DCHPRI16_ECP_SHIFT                   (7U)
#define DMA_DCHPRI16_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI16_ECP_SHIFT)) & DMA_DCHPRI16_ECP_MASK)

/*! @name DCHPRI23 - Channel n Priority Register */
#define DMA_DCHPRI23_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI23_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI23_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI23_CHPRI_SHIFT)) & DMA_DCHPRI23_CHPRI_MASK)
#define DMA_DCHPRI23_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI23_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI23_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI23_GRPPRI_SHIFT)) & DMA_DCHPRI23_GRPPRI_MASK)
#define DMA_DCHPRI23_DPA_MASK                    (0x40U)
#define DMA_DCHPRI23_DPA_SHIFT                   (6U)
#define DMA_DCHPRI23_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI23_DPA_SHIFT)) & DMA_DCHPRI23_DPA_MASK)
#define DMA_DCHPRI23_ECP_MASK                    (0x80U)
#define DMA_DCHPRI23_ECP_SHIFT                   (7U)
#define DMA_DCHPRI23_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI23_ECP_SHIFT)) & DMA_DCHPRI23_ECP_MASK)

/*! @name DCHPRI22 - Channel n Priority Register */
#define DMA_DCHPRI22_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI22_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI22_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI22_CHPRI_SHIFT)) & DMA_DCHPRI22_CHPRI_MASK)
#define DMA_DCHPRI22_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI22_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI22_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI22_GRPPRI_SHIFT)) & DMA_DCHPRI22_GRPPRI_MASK)
#define DMA_DCHPRI22_DPA_MASK                    (0x40U)
#define DMA_DCHPRI22_DPA_SHIFT                   (6U)
#define DMA_DCHPRI22_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI22_DPA_SHIFT)) & DMA_DCHPRI22_DPA_MASK)
#define DMA_DCHPRI22_ECP_MASK                    (0x80U)
#define DMA_DCHPRI22_ECP_SHIFT                   (7U)
#define DMA_DCHPRI22_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI22_ECP_SHIFT)) & DMA_DCHPRI22_ECP_MASK)

/*! @name DCHPRI21 - Channel n Priority Register */
#define DMA_DCHPRI21_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI21_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI21_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI21_CHPRI_SHIFT)) & DMA_DCHPRI21_CHPRI_MASK)
#define DMA_DCHPRI21_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI21_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI21_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI21_GRPPRI_SHIFT)) & DMA_DCHPRI21_GRPPRI_MASK)
#define DMA_DCHPRI21_DPA_MASK                    (0x40U)
#define DMA_DCHPRI21_DPA_SHIFT                   (6U)
#define DMA_DCHPRI21_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI21_DPA_SHIFT)) & DMA_DCHPRI21_DPA_MASK)
#define DMA_DCHPRI21_ECP_MASK                    (0x80U)
#define DMA_DCHPRI21_ECP_SHIFT                   (7U)
#define DMA_DCHPRI21_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI21_ECP_SHIFT)) & DMA_DCHPRI21_ECP_MASK)

/*! @name DCHPRI20 - Channel n Priority Register */
#define DMA_DCHPRI20_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI20_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI20_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI20_CHPRI_SHIFT)) & DMA_DCHPRI20_CHPRI_MASK)
#define DMA_DCHPRI20_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI20_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI20_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI20_GRPPRI_SHIFT)) & DMA_DCHPRI20_GRPPRI_MASK)
#define DMA_DCHPRI20_DPA_MASK                    (0x40U)
#define DMA_DCHPRI20_DPA_SHIFT                   (6U)
#define DMA_DCHPRI20_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI20_DPA_SHIFT)) & DMA_DCHPRI20_DPA_MASK)
#define DMA_DCHPRI20_ECP_MASK                    (0x80U)
#define DMA_DCHPRI20_ECP_SHIFT                   (7U)
#define DMA_DCHPRI20_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI20_ECP_SHIFT)) & DMA_DCHPRI20_ECP_MASK)

/*! @name DCHPRI27 - Channel n Priority Register */
#define DMA_DCHPRI27_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI27_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI27_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI27_CHPRI_SHIFT)) & DMA_DCHPRI27_CHPRI_MASK)
#define DMA_DCHPRI27_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI27_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI27_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI27_GRPPRI_SHIFT)) & DMA_DCHPRI27_GRPPRI_MASK)
#define DMA_DCHPRI27_DPA_MASK                    (0x40U)
#define DMA_DCHPRI27_DPA_SHIFT                   (6U)
#define DMA_DCHPRI27_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI27_DPA_SHIFT)) & DMA_DCHPRI27_DPA_MASK)
#define DMA_DCHPRI27_ECP_MASK                    (0x80U)
#define DMA_DCHPRI27_ECP_SHIFT                   (7U)
#define DMA_DCHPRI27_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI27_ECP_SHIFT)) & DMA_DCHPRI27_ECP_MASK)

/*! @name DCHPRI26 - Channel n Priority Register */
#define DMA_DCHPRI26_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI26_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI26_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI26_CHPRI_SHIFT)) & DMA_DCHPRI26_CHPRI_MASK)
#define DMA_DCHPRI26_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI26_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI26_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI26_GRPPRI_SHIFT)) & DMA_DCHPRI26_GRPPRI_MASK)
#define DMA_DCHPRI26_DPA_MASK                    (0x40U)
#define DMA_DCHPRI26_DPA_SHIFT                   (6U)
#define DMA_DCHPRI26_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI26_DPA_SHIFT)) & DMA_DCHPRI26_DPA_MASK)
#define DMA_DCHPRI26_ECP_MASK                    (0x80U)
#define DMA_DCHPRI26_ECP_SHIFT                   (7U)
#define DMA_DCHPRI26_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI26_ECP_SHIFT)) & DMA_DCHPRI26_ECP_MASK)

/*! @name DCHPRI25 - Channel n Priority Register */
#define DMA_DCHPRI25_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI25_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI25_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI25_CHPRI_SHIFT)) & DMA_DCHPRI25_CHPRI_MASK)
#define DMA_DCHPRI25_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI25_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI25_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI25_GRPPRI_SHIFT)) & DMA_DCHPRI25_GRPPRI_MASK)
#define DMA_DCHPRI25_DPA_MASK                    (0x40U)
#define DMA_DCHPRI25_DPA_SHIFT                   (6U)
#define DMA_DCHPRI25_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI25_DPA_SHIFT)) & DMA_DCHPRI25_DPA_MASK)
#define DMA_DCHPRI25_ECP_MASK                    (0x80U)
#define DMA_DCHPRI25_ECP_SHIFT                   (7U)
#define DMA_DCHPRI25_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI25_ECP_SHIFT)) & DMA_DCHPRI25_ECP_MASK)

/*! @name DCHPRI24 - Channel n Priority Register */
#define DMA_DCHPRI24_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI24_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI24_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI24_CHPRI_SHIFT)) & DMA_DCHPRI24_CHPRI_MASK)
#define DMA_DCHPRI24_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI24_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI24_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI24_GRPPRI_SHIFT)) & DMA_DCHPRI24_GRPPRI_MASK)
#define DMA_DCHPRI24_DPA_MASK                    (0x40U)
#define DMA_DCHPRI24_DPA_SHIFT                   (6U)
#define DMA_DCHPRI24_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI24_DPA_SHIFT)) & DMA_DCHPRI24_DPA_MASK)
#define DMA_DCHPRI24_ECP_MASK                    (0x80U)
#define DMA_DCHPRI24_ECP_SHIFT                   (7U)
#define DMA_DCHPRI24_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI24_ECP_SHIFT)) & DMA_DCHPRI24_ECP_MASK)

/*! @name DCHPRI31 - Channel n Priority Register */
#define DMA_DCHPRI31_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI31_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI31_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI31_CHPRI_SHIFT)) & DMA_DCHPRI31_CHPRI_MASK)
#define DMA_DCHPRI31_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI31_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI31_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI31_GRPPRI_SHIFT)) & DMA_DCHPRI31_GRPPRI_MASK)
#define DMA_DCHPRI31_DPA_MASK                    (0x40U)
#define DMA_DCHPRI31_DPA_SHIFT                   (6U)
#define DMA_DCHPRI31_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI31_DPA_SHIFT)) & DMA_DCHPRI31_DPA_MASK)
#define DMA_DCHPRI31_ECP_MASK                    (0x80U)
#define DMA_DCHPRI31_ECP_SHIFT                   (7U)
#define DMA_DCHPRI31_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI31_ECP_SHIFT)) & DMA_DCHPRI31_ECP_MASK)

/*! @name DCHPRI30 - Channel n Priority Register */
#define DMA_DCHPRI30_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI30_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI30_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI30_CHPRI_SHIFT)) & DMA_DCHPRI30_CHPRI_MASK)
#define DMA_DCHPRI30_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI30_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI30_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI30_GRPPRI_SHIFT)) & DMA_DCHPRI30_GRPPRI_MASK)
#define DMA_DCHPRI30_DPA_MASK                    (0x40U)
#define DMA_DCHPRI30_DPA_SHIFT                   (6U)
#define DMA_DCHPRI30_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI30_DPA_SHIFT)) & DMA_DCHPRI30_DPA_MASK)
#define DMA_DCHPRI30_ECP_MASK                    (0x80U)
#define DMA_DCHPRI30_ECP_SHIFT                   (7U)
#define DMA_DCHPRI30_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI30_ECP_SHIFT)) & DMA_DCHPRI30_ECP_MASK)

/*! @name DCHPRI29 - Channel n Priority Register */
#define DMA_DCHPRI29_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI29_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI29_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI29_CHPRI_SHIFT)) & DMA_DCHPRI29_CHPRI_MASK)
#define DMA_DCHPRI29_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI29_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI29_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI29_GRPPRI_SHIFT)) & DMA_DCHPRI29_GRPPRI_MASK)
#define DMA_DCHPRI29_DPA_MASK                    (0x40U)
#define DMA_DCHPRI29_DPA_SHIFT                   (6U)
#define DMA_DCHPRI29_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI29_DPA_SHIFT)) & DMA_DCHPRI29_DPA_MASK)
#define DMA_DCHPRI29_ECP_MASK                    (0x80U)
#define DMA_DCHPRI29_ECP_SHIFT                   (7U)
#define DMA_DCHPRI29_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI29_ECP_SHIFT)) & DMA_DCHPRI29_ECP_MASK)

/*! @name DCHPRI28 - Channel n Priority Register */
#define DMA_DCHPRI28_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI28_CHPRI_SHIFT                 (0U)
#define DMA_DCHPRI28_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI28_CHPRI_SHIFT)) & DMA_DCHPRI28_CHPRI_MASK)
#define DMA_DCHPRI28_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI28_GRPPRI_SHIFT                (4U)
#define DMA_DCHPRI28_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI28_GRPPRI_SHIFT)) & DMA_DCHPRI28_GRPPRI_MASK)
#define DMA_DCHPRI28_DPA_MASK                    (0x40U)
#define DMA_DCHPRI28_DPA_SHIFT                   (6U)
#define DMA_DCHPRI28_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI28_DPA_SHIFT)) & DMA_DCHPRI28_DPA_MASK)
#define DMA_DCHPRI28_ECP_MASK                    (0x80U)
#define DMA_DCHPRI28_ECP_SHIFT                   (7U)
#define DMA_DCHPRI28_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI28_ECP_SHIFT)) & DMA_DCHPRI28_ECP_MASK)

/*! @name SADDR - TCD Source Address */
#define DMA_SADDR_SADDR_MASK                     (0xFFFFFFFFU)
#define DMA_SADDR_SADDR_SHIFT                    (0U)
#define DMA_SADDR_SADDR(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_SADDR_SADDR_SHIFT)) & DMA_SADDR_SADDR_MASK)

/* The count of DMA_SADDR */
#define DMA_SADDR_COUNT                          (32U)

/*! @name SOFF - TCD Signed Source Address Offset */
#define DMA_SOFF_SOFF_MASK                       (0xFFFFU)
#define DMA_SOFF_SOFF_SHIFT                      (0U)
#define DMA_SOFF_SOFF(x)                         (((uint16_t)(((uint16_t)(x)) << DMA_SOFF_SOFF_SHIFT)) & DMA_SOFF_SOFF_MASK)

/* The count of DMA_SOFF */
#define DMA_SOFF_COUNT                           (32U)

/*! @name ATTR - TCD Transfer Attributes */
#define DMA_ATTR_DSIZE_MASK                      (0x7U)
#define DMA_ATTR_DSIZE_SHIFT                     (0U)
#define DMA_ATTR_DSIZE(x)                        (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_DSIZE_SHIFT)) & DMA_ATTR_DSIZE_MASK)
#define DMA_ATTR_DMOD_MASK                       (0xF8U)
#define DMA_ATTR_DMOD_SHIFT                      (3U)
#define DMA_ATTR_DMOD(x)                         (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_DMOD_SHIFT)) & DMA_ATTR_DMOD_MASK)
#define DMA_ATTR_SSIZE_MASK                      (0x700U)
#define DMA_ATTR_SSIZE_SHIFT                     (8U)
#define DMA_ATTR_SSIZE(x)                        (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_SSIZE_SHIFT)) & DMA_ATTR_SSIZE_MASK)
#define DMA_ATTR_SMOD_MASK                       (0xF800U)
#define DMA_ATTR_SMOD_SHIFT                      (11U)
#define DMA_ATTR_SMOD(x)                         (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_SMOD_SHIFT)) & DMA_ATTR_SMOD_MASK)

/* The count of DMA_ATTR */
#define DMA_ATTR_COUNT                           (32U)

/*! @name NBYTES_MLNO - TCD Minor Byte Count (Minor Loop Mapping Disabled) */
#define DMA_NBYTES_MLNO_NBYTES_MASK              (0xFFFFFFFFU)
#define DMA_NBYTES_MLNO_NBYTES_SHIFT             (0U)
#define DMA_NBYTES_MLNO_NBYTES(x)                (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLNO_NBYTES_SHIFT)) & DMA_NBYTES_MLNO_NBYTES_MASK)

/* The count of DMA_NBYTES_MLNO */
#define DMA_NBYTES_MLNO_COUNT                    (32U)

/*! @name NBYTES_MLOFFNO - TCD Signed Minor Loop Offset (Minor Loop Mapping Enabled and Offset Disabled) */
#define DMA_NBYTES_MLOFFNO_NBYTES_MASK           (0x3FFFFFFFU)
#define DMA_NBYTES_MLOFFNO_NBYTES_SHIFT          (0U)
#define DMA_NBYTES_MLOFFNO_NBYTES(x)             (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_NBYTES_MLOFFNO_NBYTES_MASK)
#define DMA_NBYTES_MLOFFNO_DMLOE_MASK            (0x40000000U)
#define DMA_NBYTES_MLOFFNO_DMLOE_SHIFT           (30U)
#define DMA_NBYTES_MLOFFNO_DMLOE(x)              (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_NBYTES_MLOFFNO_DMLOE_MASK)
#define DMA_NBYTES_MLOFFNO_SMLOE_MASK            (0x80000000U)
#define DMA_NBYTES_MLOFFNO_SMLOE_SHIFT           (31U)
#define DMA_NBYTES_MLOFFNO_SMLOE(x)              (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_NBYTES_MLOFFNO_SMLOE_MASK)

/* The count of DMA_NBYTES_MLOFFNO */
#define DMA_NBYTES_MLOFFNO_COUNT                 (32U)

/*! @name NBYTES_MLOFFYES - TCD Signed Minor Loop Offset (Minor Loop Mapping and Offset Enabled) */
#define DMA_NBYTES_MLOFFYES_NBYTES_MASK          (0x3FFU)
#define DMA_NBYTES_MLOFFYES_NBYTES_SHIFT         (0U)
#define DMA_NBYTES_MLOFFYES_NBYTES(x)            (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_NBYTES_MLOFFYES_NBYTES_MASK)
#define DMA_NBYTES_MLOFFYES_MLOFF_MASK           (0x3FFFFC00U)
#define DMA_NBYTES_MLOFFYES_MLOFF_SHIFT          (10U)
#define DMA_NBYTES_MLOFFYES_MLOFF(x)             (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_NBYTES_MLOFFYES_MLOFF_MASK)
#define DMA_NBYTES_MLOFFYES_DMLOE_MASK           (0x40000000U)
#define DMA_NBYTES_MLOFFYES_DMLOE_SHIFT          (30U)
#define DMA_NBYTES_MLOFFYES_DMLOE(x)             (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_NBYTES_MLOFFYES_DMLOE_MASK)
#define DMA_NBYTES_MLOFFYES_SMLOE_MASK           (0x80000000U)
#define DMA_NBYTES_MLOFFYES_SMLOE_SHIFT          (31U)
#define DMA_NBYTES_MLOFFYES_SMLOE(x)             (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_NBYTES_MLOFFYES_SMLOE_MASK)

/* The count of DMA_NBYTES_MLOFFYES */
#define DMA_NBYTES_MLOFFYES_COUNT                (32U)

/*! @name SLAST - TCD Last Source Address Adjustment */
#define DMA_SLAST_SLAST_MASK                     (0xFFFFFFFFU)
#define DMA_SLAST_SLAST_SHIFT                    (0U)
#define DMA_SLAST_SLAST(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_SLAST_SLAST_SHIFT)) & DMA_SLAST_SLAST_MASK)

/* The count of DMA_SLAST */
#define DMA_SLAST_COUNT                          (32U)

/*! @name DADDR - TCD Destination Address */
#define DMA_DADDR_DADDR_MASK                     (0xFFFFFFFFU)
#define DMA_DADDR_DADDR_SHIFT                    (0U)
#define DMA_DADDR_DADDR(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_DADDR_DADDR_SHIFT)) & DMA_DADDR_DADDR_MASK)

/* The count of DMA_DADDR */
#define DMA_DADDR_COUNT                          (32U)

/*! @name DOFF - TCD Signed Destination Address Offset */
#define DMA_DOFF_DOFF_MASK                       (0xFFFFU)
#define DMA_DOFF_DOFF_SHIFT                      (0U)
#define DMA_DOFF_DOFF(x)                         (((uint16_t)(((uint16_t)(x)) << DMA_DOFF_DOFF_SHIFT)) & DMA_DOFF_DOFF_MASK)

/* The count of DMA_DOFF */
#define DMA_DOFF_COUNT                           (32U)

/*! @name CITER_ELINKNO - TCD Current Minor Loop Link, Major Loop Count (Channel Linking Disabled) */
#define DMA_CITER_ELINKNO_CITER_MASK             (0x7FFFU)
#define DMA_CITER_ELINKNO_CITER_SHIFT            (0U)
#define DMA_CITER_ELINKNO_CITER(x)               (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKNO_CITER_SHIFT)) & DMA_CITER_ELINKNO_CITER_MASK)
#define DMA_CITER_ELINKNO_ELINK_MASK             (0x8000U)
#define DMA_CITER_ELINKNO_ELINK_SHIFT            (15U)
#define DMA_CITER_ELINKNO_ELINK(x)               (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKNO_ELINK_SHIFT)) & DMA_CITER_ELINKNO_ELINK_MASK)

/* The count of DMA_CITER_ELINKNO */
#define DMA_CITER_ELINKNO_COUNT                  (32U)

/*! @name CITER_ELINKYES - TCD Current Minor Loop Link, Major Loop Count (Channel Linking Enabled) */
#define DMA_CITER_ELINKYES_CITER_MASK            (0x1FFU)
#define DMA_CITER_ELINKYES_CITER_SHIFT           (0U)
#define DMA_CITER_ELINKYES_CITER(x)              (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKYES_CITER_SHIFT)) & DMA_CITER_ELINKYES_CITER_MASK)
#define DMA_CITER_ELINKYES_LINKCH_MASK           (0x3E00U)
#define DMA_CITER_ELINKYES_LINKCH_SHIFT          (9U)
#define DMA_CITER_ELINKYES_LINKCH(x)             (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_CITER_ELINKYES_LINKCH_MASK)
#define DMA_CITER_ELINKYES_ELINK_MASK            (0x8000U)
#define DMA_CITER_ELINKYES_ELINK_SHIFT           (15U)
#define DMA_CITER_ELINKYES_ELINK(x)              (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKYES_ELINK_SHIFT)) & DMA_CITER_ELINKYES_ELINK_MASK)

/* The count of DMA_CITER_ELINKYES */
#define DMA_CITER_ELINKYES_COUNT                 (32U)

/*! @name DLAST_SGA - TCD Last Destination Address Adjustment/Scatter Gather Address */
#define DMA_DLAST_SGA_DLASTSGA_MASK              (0xFFFFFFFFU)
#define DMA_DLAST_SGA_DLASTSGA_SHIFT             (0U)
#define DMA_DLAST_SGA_DLASTSGA(x)                (((uint32_t)(((uint32_t)(x)) << DMA_DLAST_SGA_DLASTSGA_SHIFT)) & DMA_DLAST_SGA_DLASTSGA_MASK)

/* The count of DMA_DLAST_SGA */
#define DMA_DLAST_SGA_COUNT                      (32U)

/*! @name CSR - TCD Control and Status */
#define DMA_CSR_START_MASK                       (0x1U)
#define DMA_CSR_START_SHIFT                      (0U)
#define DMA_CSR_START(x)                         (((uint16_t)(((uint16_t)(x)) << DMA_CSR_START_SHIFT)) & DMA_CSR_START_MASK)
#define DMA_CSR_INTMAJOR_MASK                    (0x2U)
#define DMA_CSR_INTMAJOR_SHIFT                   (1U)
#define DMA_CSR_INTMAJOR(x)                      (((uint16_t)(((uint16_t)(x)) << DMA_CSR_INTMAJOR_SHIFT)) & DMA_CSR_INTMAJOR_MASK)
#define DMA_CSR_INTHALF_MASK                     (0x4U)
#define DMA_CSR_INTHALF_SHIFT                    (2U)
#define DMA_CSR_INTHALF(x)                       (((uint16_t)(((uint16_t)(x)) << DMA_CSR_INTHALF_SHIFT)) & DMA_CSR_INTHALF_MASK)
#define DMA_CSR_DREQ_MASK                        (0x8U)
#define DMA_CSR_DREQ_SHIFT                       (3U)
#define DMA_CSR_DREQ(x)                          (((uint16_t)(((uint16_t)(x)) << DMA_CSR_DREQ_SHIFT)) & DMA_CSR_DREQ_MASK)
#define DMA_CSR_ESG_MASK                         (0x10U)
#define DMA_CSR_ESG_SHIFT                        (4U)
#define DMA_CSR_ESG(x)                           (((uint16_t)(((uint16_t)(x)) << DMA_CSR_ESG_SHIFT)) & DMA_CSR_ESG_MASK)
#define DMA_CSR_MAJORELINK_MASK                  (0x20U)
#define DMA_CSR_MAJORELINK_SHIFT                 (5U)
#define DMA_CSR_MAJORELINK(x)                    (((uint16_t)(((uint16_t)(x)) << DMA_CSR_MAJORELINK_SHIFT)) & DMA_CSR_MAJORELINK_MASK)
#define DMA_CSR_ACTIVE_MASK                      (0x40U)
#define DMA_CSR_ACTIVE_SHIFT                     (6U)
#define DMA_CSR_ACTIVE(x)                        (((uint16_t)(((uint16_t)(x)) << DMA_CSR_ACTIVE_SHIFT)) & DMA_CSR_ACTIVE_MASK)
#define DMA_CSR_DONE_MASK                        (0x80U)
#define DMA_CSR_DONE_SHIFT                       (7U)
#define DMA_CSR_DONE(x)                          (((uint16_t)(((uint16_t)(x)) << DMA_CSR_DONE_SHIFT)) & DMA_CSR_DONE_MASK)
#define DMA_CSR_MAJORLINKCH_MASK                 (0x1F00U)
#define DMA_CSR_MAJORLINKCH_SHIFT                (8U)
#define DMA_CSR_MAJORLINKCH(x)                   (((uint16_t)(((uint16_t)(x)) << DMA_CSR_MAJORLINKCH_SHIFT)) & DMA_CSR_MAJORLINKCH_MASK)
#define DMA_CSR_BWC_MASK                         (0xC000U)
#define DMA_CSR_BWC_SHIFT                        (14U)
#define DMA_CSR_BWC(x)                           (((uint16_t)(((uint16_t)(x)) << DMA_CSR_BWC_SHIFT)) & DMA_CSR_BWC_MASK)

/* The count of DMA_CSR */
#define DMA_CSR_COUNT                            (32U)

/*! @name BITER_ELINKNO - TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Disabled) */
#define DMA_BITER_ELINKNO_BITER_MASK             (0x7FFFU)
#define DMA_BITER_ELINKNO_BITER_SHIFT            (0U)
#define DMA_BITER_ELINKNO_BITER(x)               (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKNO_BITER_SHIFT)) & DMA_BITER_ELINKNO_BITER_MASK)
#define DMA_BITER_ELINKNO_ELINK_MASK             (0x8000U)
#define DMA_BITER_ELINKNO_ELINK_SHIFT            (15U)
#define DMA_BITER_ELINKNO_ELINK(x)               (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKNO_ELINK_SHIFT)) & DMA_BITER_ELINKNO_ELINK_MASK)

/* The count of DMA_BITER_ELINKNO */
#define DMA_BITER_ELINKNO_COUNT                  (32U)

/*! @name BITER_ELINKYES - TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Enabled) */
#define DMA_BITER_ELINKYES_BITER_MASK            (0x1FFU)
#define DMA_BITER_ELINKYES_BITER_SHIFT           (0U)
#define DMA_BITER_ELINKYES_BITER(x)              (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKYES_BITER_SHIFT)) & DMA_BITER_ELINKYES_BITER_MASK)
#define DMA_BITER_ELINKYES_LINKCH_MASK           (0x3E00U)
#define DMA_BITER_ELINKYES_LINKCH_SHIFT          (9U)
#define DMA_BITER_ELINKYES_LINKCH(x)             (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_BITER_ELINKYES_LINKCH_MASK)
#define DMA_BITER_ELINKYES_ELINK_MASK            (0x8000U)
#define DMA_BITER_ELINKYES_ELINK_SHIFT           (15U)
#define DMA_BITER_ELINKYES_ELINK(x)              (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKYES_ELINK_SHIFT)) & DMA_BITER_ELINKYES_ELINK_MASK)

/* The count of DMA_BITER_ELINKYES */
#define DMA_BITER_ELINKYES_COUNT                 (32U)


/*!
 * @}
 */ /* end of group DMA_Register_Masks */


/* DMA - Peripheral instance base addresses */
/** Peripheral DMA base address */
#define DMA_BASE                                 (0x40008000u)
/** Peripheral DMA base pointer */
#define DMA0                                     ((DMA_Type *)DMA_BASE)
/** Array initializer of DMA peripheral base addresses */
#define DMA_BASE_ADDRS                           { DMA_BASE }
/** Array initializer of DMA peripheral base pointers */
#define DMA_BASE_PTRS                            { DMA0 }
/** Interrupt vectors for the DMA peripheral type */
#define DMA_CHN_IRQS                             { DMA0_DMA16_IRQn, DMA1_DMA17_IRQn, DMA2_DMA18_IRQn, DMA3_DMA19_IRQn, DMA4_DMA20_IRQn, DMA5_DMA21_IRQn, DMA6_DMA22_IRQn, DMA7_DMA23_IRQn, DMA8_DMA24_IRQn, DMA9_DMA25_IRQn, DMA10_DMA26_IRQn, DMA11_DMA27_IRQn, DMA12_DMA28_IRQn, DMA13_DMA29_IRQn, DMA14_DMA30_IRQn, DMA15_DMA31_IRQn, DMA0_DMA16_IRQn, DMA1_DMA17_IRQn, DMA2_DMA18_IRQn, DMA3_DMA19_IRQn, DMA4_DMA20_IRQn, DMA5_DMA21_IRQn, DMA6_DMA22_IRQn, DMA7_DMA23_IRQn, DMA8_DMA24_IRQn, DMA9_DMA25_IRQn, DMA10_DMA26_IRQn, DMA11_DMA27_IRQn, DMA12_DMA28_IRQn, DMA13_DMA29_IRQn, DMA14_DMA30_IRQn, DMA15_DMA31_IRQn }
#define DMA_ERROR_IRQS                           { DMA_Error_IRQn }

/*!
 * @}
 */ /* end of group DMA_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- DMAMUX Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMAMUX_Peripheral_Access_Layer DMAMUX Peripheral Access Layer
 * @{
 */

/** DMAMUX - Register Layout Typedef */
typedef struct {
  __IO uint8_t CHCFG[32];                          /**< Channel Configuration register, array offset: 0x0, array step: 0x1 */
} DMAMUX_Type;

/* ----------------------------------------------------------------------------
   -- DMAMUX Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMAMUX_Register_Masks DMAMUX Register Masks
 * @{
 */

/*! @name CHCFG - Channel Configuration register */
#define DMAMUX_CHCFG_SOURCE_MASK                 (0x3FU)
#define DMAMUX_CHCFG_SOURCE_SHIFT                (0U)
#define DMAMUX_CHCFG_SOURCE(x)                   (((uint8_t)(((uint8_t)(x)) << DMAMUX_CHCFG_SOURCE_SHIFT)) & DMAMUX_CHCFG_SOURCE_MASK)
#define DMAMUX_CHCFG_TRIG_MASK                   (0x40U)
#define DMAMUX_CHCFG_TRIG_SHIFT                  (6U)
#define DMAMUX_CHCFG_TRIG(x)                     (((uint8_t)(((uint8_t)(x)) << DMAMUX_CHCFG_TRIG_SHIFT)) & DMAMUX_CHCFG_TRIG_MASK)
#define DMAMUX_CHCFG_ENBL_MASK                   (0x80U)
#define DMAMUX_CHCFG_ENBL_SHIFT                  (7U)
#define DMAMUX_CHCFG_ENBL(x)                     (((uint8_t)(((uint8_t)(x)) << DMAMUX_CHCFG_ENBL_SHIFT)) & DMAMUX_CHCFG_ENBL_MASK)

/* The count of DMAMUX_CHCFG */
#define DMAMUX_CHCFG_COUNT                       (32U)


/*!
 * @}
 */ /* end of group DMAMUX_Register_Masks */


/* DMAMUX - Peripheral instance base addresses */
/** Peripheral DMAMUX base address */
#define DMAMUX_BASE                              (0x40021000u)
/** Peripheral DMAMUX base pointer */
#define DMAMUX                                   ((DMAMUX_Type *)DMAMUX_BASE)
/** Array initializer of DMAMUX peripheral base addresses */
#define DMAMUX_BASE_ADDRS                        { DMAMUX_BASE }
/** Array initializer of DMAMUX peripheral base pointers */
#define DMAMUX_BASE_PTRS                         { DMAMUX }

/*!
 * @}
 */ /* end of group DMAMUX_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- ENC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ENC_Peripheral_Access_Layer ENC Peripheral Access Layer
 * @{
 */

/** ENC - Register Layout Typedef */
typedef struct {
  __IO uint16_t CTRL;                              /**< Control Register, offset: 0x0 */
  __IO uint16_t FILT;                              /**< Input Filter Register, offset: 0x2 */
  __IO uint16_t WTR;                               /**< Watchdog Timeout Register, offset: 0x4 */
  __IO uint16_t POSD;                              /**< Position Difference Counter Register, offset: 0x6 */
  __I  uint16_t POSDH;                             /**< Position Difference Hold Register, offset: 0x8 */
  __IO uint16_t REV;                               /**< Revolution Counter Register, offset: 0xA */
  __I  uint16_t REVH;                              /**< Revolution Hold Register, offset: 0xC */
  __IO uint16_t UPOS;                              /**< Upper Position Counter Register, offset: 0xE */
  __IO uint16_t LPOS;                              /**< Lower Position Counter Register, offset: 0x10 */
  __I  uint16_t UPOSH;                             /**< Upper Position Hold Register, offset: 0x12 */
  __I  uint16_t LPOSH;                             /**< Lower Position Hold Register, offset: 0x14 */
  __IO uint16_t UINIT;                             /**< Upper Initialization Register, offset: 0x16 */
  __IO uint16_t LINIT;                             /**< Lower Initialization Register, offset: 0x18 */
  __I  uint16_t IMR;                               /**< Input Monitor Register, offset: 0x1A */
  __IO uint16_t TST;                               /**< Test Register, offset: 0x1C */
  __IO uint16_t CTRL2;                             /**< Control 2 Register, offset: 0x1E */
  __IO uint16_t UMOD;                              /**< Upper Modulus Register, offset: 0x20 */
  __IO uint16_t LMOD;                              /**< Lower Modulus Register, offset: 0x22 */
  __IO uint16_t UCOMP;                             /**< Upper Position Compare Register, offset: 0x24 */
  __IO uint16_t LCOMP;                             /**< Lower Position Compare Register, offset: 0x26 */
} ENC_Type;

/* ----------------------------------------------------------------------------
   -- ENC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ENC_Register_Masks ENC Register Masks
 * @{
 */

/*! @name CTRL - Control Register */
#define ENC_CTRL_CMPIE_MASK                      (0x1U)
#define ENC_CTRL_CMPIE_SHIFT                     (0U)
#define ENC_CTRL_CMPIE(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_CMPIE_SHIFT)) & ENC_CTRL_CMPIE_MASK)
#define ENC_CTRL_CMPIRQ_MASK                     (0x2U)
#define ENC_CTRL_CMPIRQ_SHIFT                    (1U)
#define ENC_CTRL_CMPIRQ(x)                       (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_CMPIRQ_SHIFT)) & ENC_CTRL_CMPIRQ_MASK)
#define ENC_CTRL_WDE_MASK                        (0x4U)
#define ENC_CTRL_WDE_SHIFT                       (2U)
#define ENC_CTRL_WDE(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_WDE_SHIFT)) & ENC_CTRL_WDE_MASK)
#define ENC_CTRL_DIE_MASK                        (0x8U)
#define ENC_CTRL_DIE_SHIFT                       (3U)
#define ENC_CTRL_DIE(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_DIE_SHIFT)) & ENC_CTRL_DIE_MASK)
#define ENC_CTRL_DIRQ_MASK                       (0x10U)
#define ENC_CTRL_DIRQ_SHIFT                      (4U)
#define ENC_CTRL_DIRQ(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_DIRQ_SHIFT)) & ENC_CTRL_DIRQ_MASK)
#define ENC_CTRL_XNE_MASK                        (0x20U)
#define ENC_CTRL_XNE_SHIFT                       (5U)
#define ENC_CTRL_XNE(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_XNE_SHIFT)) & ENC_CTRL_XNE_MASK)
#define ENC_CTRL_XIP_MASK                        (0x40U)
#define ENC_CTRL_XIP_SHIFT                       (6U)
#define ENC_CTRL_XIP(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_XIP_SHIFT)) & ENC_CTRL_XIP_MASK)
#define ENC_CTRL_XIE_MASK                        (0x80U)
#define ENC_CTRL_XIE_SHIFT                       (7U)
#define ENC_CTRL_XIE(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_XIE_SHIFT)) & ENC_CTRL_XIE_MASK)
#define ENC_CTRL_XIRQ_MASK                       (0x100U)
#define ENC_CTRL_XIRQ_SHIFT                      (8U)
#define ENC_CTRL_XIRQ(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_XIRQ_SHIFT)) & ENC_CTRL_XIRQ_MASK)
#define ENC_CTRL_PH1_MASK                        (0x200U)
#define ENC_CTRL_PH1_SHIFT                       (9U)
#define ENC_CTRL_PH1(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_PH1_SHIFT)) & ENC_CTRL_PH1_MASK)
#define ENC_CTRL_REV_MASK                        (0x400U)
#define ENC_CTRL_REV_SHIFT                       (10U)
#define ENC_CTRL_REV(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_REV_SHIFT)) & ENC_CTRL_REV_MASK)
#define ENC_CTRL_SWIP_MASK                       (0x800U)
#define ENC_CTRL_SWIP_SHIFT                      (11U)
#define ENC_CTRL_SWIP(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_SWIP_SHIFT)) & ENC_CTRL_SWIP_MASK)
#define ENC_CTRL_HNE_MASK                        (0x1000U)
#define ENC_CTRL_HNE_SHIFT                       (12U)
#define ENC_CTRL_HNE(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_HNE_SHIFT)) & ENC_CTRL_HNE_MASK)
#define ENC_CTRL_HIP_MASK                        (0x2000U)
#define ENC_CTRL_HIP_SHIFT                       (13U)
#define ENC_CTRL_HIP(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_HIP_SHIFT)) & ENC_CTRL_HIP_MASK)
#define ENC_CTRL_HIE_MASK                        (0x4000U)
#define ENC_CTRL_HIE_SHIFT                       (14U)
#define ENC_CTRL_HIE(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_HIE_SHIFT)) & ENC_CTRL_HIE_MASK)
#define ENC_CTRL_HIRQ_MASK                       (0x8000U)
#define ENC_CTRL_HIRQ_SHIFT                      (15U)
#define ENC_CTRL_HIRQ(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_HIRQ_SHIFT)) & ENC_CTRL_HIRQ_MASK)

/*! @name FILT - Input Filter Register */
#define ENC_FILT_FILT_PER_MASK                   (0xFFU)
#define ENC_FILT_FILT_PER_SHIFT                  (0U)
#define ENC_FILT_FILT_PER(x)                     (((uint16_t)(((uint16_t)(x)) << ENC_FILT_FILT_PER_SHIFT)) & ENC_FILT_FILT_PER_MASK)
#define ENC_FILT_FILT_CNT_MASK                   (0x700U)
#define ENC_FILT_FILT_CNT_SHIFT                  (8U)
#define ENC_FILT_FILT_CNT(x)                     (((uint16_t)(((uint16_t)(x)) << ENC_FILT_FILT_CNT_SHIFT)) & ENC_FILT_FILT_CNT_MASK)

/*! @name WTR - Watchdog Timeout Register */
#define ENC_WTR_WDOG_MASK                        (0xFFFFU)
#define ENC_WTR_WDOG_SHIFT                       (0U)
#define ENC_WTR_WDOG(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_WTR_WDOG_SHIFT)) & ENC_WTR_WDOG_MASK)

/*! @name POSD - Position Difference Counter Register */
#define ENC_POSD_POSD_MASK                       (0xFFFFU)
#define ENC_POSD_POSD_SHIFT                      (0U)
#define ENC_POSD_POSD(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_POSD_POSD_SHIFT)) & ENC_POSD_POSD_MASK)

/*! @name POSDH - Position Difference Hold Register */
#define ENC_POSDH_POSDH_MASK                     (0xFFFFU)
#define ENC_POSDH_POSDH_SHIFT                    (0U)
#define ENC_POSDH_POSDH(x)                       (((uint16_t)(((uint16_t)(x)) << ENC_POSDH_POSDH_SHIFT)) & ENC_POSDH_POSDH_MASK)

/*! @name REV - Revolution Counter Register */
#define ENC_REV_REV_MASK                         (0xFFFFU)
#define ENC_REV_REV_SHIFT                        (0U)
#define ENC_REV_REV(x)                           (((uint16_t)(((uint16_t)(x)) << ENC_REV_REV_SHIFT)) & ENC_REV_REV_MASK)

/*! @name REVH - Revolution Hold Register */
#define ENC_REVH_REVH_MASK                       (0xFFFFU)
#define ENC_REVH_REVH_SHIFT                      (0U)
#define ENC_REVH_REVH(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_REVH_REVH_SHIFT)) & ENC_REVH_REVH_MASK)

/*! @name UPOS - Upper Position Counter Register */
#define ENC_UPOS_POS_MASK                        (0xFFFFU)
#define ENC_UPOS_POS_SHIFT                       (0U)
#define ENC_UPOS_POS(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_UPOS_POS_SHIFT)) & ENC_UPOS_POS_MASK)

/*! @name LPOS - Lower Position Counter Register */
#define ENC_LPOS_POS_MASK                        (0xFFFFU)
#define ENC_LPOS_POS_SHIFT                       (0U)
#define ENC_LPOS_POS(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_LPOS_POS_SHIFT)) & ENC_LPOS_POS_MASK)

/*! @name UPOSH - Upper Position Hold Register */
#define ENC_UPOSH_POSH_MASK                      (0xFFFFU)
#define ENC_UPOSH_POSH_SHIFT                     (0U)
#define ENC_UPOSH_POSH(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_UPOSH_POSH_SHIFT)) & ENC_UPOSH_POSH_MASK)

/*! @name LPOSH - Lower Position Hold Register */
#define ENC_LPOSH_POSH_MASK                      (0xFFFFU)
#define ENC_LPOSH_POSH_SHIFT                     (0U)
#define ENC_LPOSH_POSH(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_LPOSH_POSH_SHIFT)) & ENC_LPOSH_POSH_MASK)

/*! @name UINIT - Upper Initialization Register */
#define ENC_UINIT_INIT_MASK                      (0xFFFFU)
#define ENC_UINIT_INIT_SHIFT                     (0U)
#define ENC_UINIT_INIT(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_UINIT_INIT_SHIFT)) & ENC_UINIT_INIT_MASK)

/*! @name LINIT - Lower Initialization Register */
#define ENC_LINIT_INIT_MASK                      (0xFFFFU)
#define ENC_LINIT_INIT_SHIFT                     (0U)
#define ENC_LINIT_INIT(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_LINIT_INIT_SHIFT)) & ENC_LINIT_INIT_MASK)

/*! @name IMR - Input Monitor Register */
#define ENC_IMR_HOME_MASK                        (0x1U)
#define ENC_IMR_HOME_SHIFT                       (0U)
#define ENC_IMR_HOME(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_IMR_HOME_SHIFT)) & ENC_IMR_HOME_MASK)
#define ENC_IMR_INDEX_MASK                       (0x2U)
#define ENC_IMR_INDEX_SHIFT                      (1U)
#define ENC_IMR_INDEX(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_IMR_INDEX_SHIFT)) & ENC_IMR_INDEX_MASK)
#define ENC_IMR_PHB_MASK                         (0x4U)
#define ENC_IMR_PHB_SHIFT                        (2U)
#define ENC_IMR_PHB(x)                           (((uint16_t)(((uint16_t)(x)) << ENC_IMR_PHB_SHIFT)) & ENC_IMR_PHB_MASK)
#define ENC_IMR_PHA_MASK                         (0x8U)
#define ENC_IMR_PHA_SHIFT                        (3U)
#define ENC_IMR_PHA(x)                           (((uint16_t)(((uint16_t)(x)) << ENC_IMR_PHA_SHIFT)) & ENC_IMR_PHA_MASK)
#define ENC_IMR_FHOM_MASK                        (0x10U)
#define ENC_IMR_FHOM_SHIFT                       (4U)
#define ENC_IMR_FHOM(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_IMR_FHOM_SHIFT)) & ENC_IMR_FHOM_MASK)
#define ENC_IMR_FIND_MASK                        (0x20U)
#define ENC_IMR_FIND_SHIFT                       (5U)
#define ENC_IMR_FIND(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_IMR_FIND_SHIFT)) & ENC_IMR_FIND_MASK)
#define ENC_IMR_FPHB_MASK                        (0x40U)
#define ENC_IMR_FPHB_SHIFT                       (6U)
#define ENC_IMR_FPHB(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_IMR_FPHB_SHIFT)) & ENC_IMR_FPHB_MASK)
#define ENC_IMR_FPHA_MASK                        (0x80U)
#define ENC_IMR_FPHA_SHIFT                       (7U)
#define ENC_IMR_FPHA(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_IMR_FPHA_SHIFT)) & ENC_IMR_FPHA_MASK)

/*! @name TST - Test Register */
#define ENC_TST_TEST_COUNT_MASK                  (0xFFU)
#define ENC_TST_TEST_COUNT_SHIFT                 (0U)
#define ENC_TST_TEST_COUNT(x)                    (((uint16_t)(((uint16_t)(x)) << ENC_TST_TEST_COUNT_SHIFT)) & ENC_TST_TEST_COUNT_MASK)
#define ENC_TST_TEST_PERIOD_MASK                 (0x1F00U)
#define ENC_TST_TEST_PERIOD_SHIFT                (8U)
#define ENC_TST_TEST_PERIOD(x)                   (((uint16_t)(((uint16_t)(x)) << ENC_TST_TEST_PERIOD_SHIFT)) & ENC_TST_TEST_PERIOD_MASK)
#define ENC_TST_QDN_MASK                         (0x2000U)
#define ENC_TST_QDN_SHIFT                        (13U)
#define ENC_TST_QDN(x)                           (((uint16_t)(((uint16_t)(x)) << ENC_TST_QDN_SHIFT)) & ENC_TST_QDN_MASK)
#define ENC_TST_TCE_MASK                         (0x4000U)
#define ENC_TST_TCE_SHIFT                        (14U)
#define ENC_TST_TCE(x)                           (((uint16_t)(((uint16_t)(x)) << ENC_TST_TCE_SHIFT)) & ENC_TST_TCE_MASK)
#define ENC_TST_TEN_MASK                         (0x8000U)
#define ENC_TST_TEN_SHIFT                        (15U)
#define ENC_TST_TEN(x)                           (((uint16_t)(((uint16_t)(x)) << ENC_TST_TEN_SHIFT)) & ENC_TST_TEN_MASK)

/*! @name CTRL2 - Control 2 Register */
#define ENC_CTRL2_UPDHLD_MASK                    (0x1U)
#define ENC_CTRL2_UPDHLD_SHIFT                   (0U)
#define ENC_CTRL2_UPDHLD(x)                      (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_UPDHLD_SHIFT)) & ENC_CTRL2_UPDHLD_MASK)
#define ENC_CTRL2_UPDPOS_MASK                    (0x2U)
#define ENC_CTRL2_UPDPOS_SHIFT                   (1U)
#define ENC_CTRL2_UPDPOS(x)                      (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_UPDPOS_SHIFT)) & ENC_CTRL2_UPDPOS_MASK)
#define ENC_CTRL2_MOD_MASK                       (0x4U)
#define ENC_CTRL2_MOD_SHIFT                      (2U)
#define ENC_CTRL2_MOD(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_MOD_SHIFT)) & ENC_CTRL2_MOD_MASK)
#define ENC_CTRL2_DIR_MASK                       (0x8U)
#define ENC_CTRL2_DIR_SHIFT                      (3U)
#define ENC_CTRL2_DIR(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_DIR_SHIFT)) & ENC_CTRL2_DIR_MASK)
#define ENC_CTRL2_RUIE_MASK                      (0x10U)
#define ENC_CTRL2_RUIE_SHIFT                     (4U)
#define ENC_CTRL2_RUIE(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_RUIE_SHIFT)) & ENC_CTRL2_RUIE_MASK)
#define ENC_CTRL2_RUIRQ_MASK                     (0x20U)
#define ENC_CTRL2_RUIRQ_SHIFT                    (5U)
#define ENC_CTRL2_RUIRQ(x)                       (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_RUIRQ_SHIFT)) & ENC_CTRL2_RUIRQ_MASK)
#define ENC_CTRL2_ROIE_MASK                      (0x40U)
#define ENC_CTRL2_ROIE_SHIFT                     (6U)
#define ENC_CTRL2_ROIE(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_ROIE_SHIFT)) & ENC_CTRL2_ROIE_MASK)
#define ENC_CTRL2_ROIRQ_MASK                     (0x80U)
#define ENC_CTRL2_ROIRQ_SHIFT                    (7U)
#define ENC_CTRL2_ROIRQ(x)                       (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_ROIRQ_SHIFT)) & ENC_CTRL2_ROIRQ_MASK)
#define ENC_CTRL2_REVMOD_MASK                    (0x100U)
#define ENC_CTRL2_REVMOD_SHIFT                   (8U)
#define ENC_CTRL2_REVMOD(x)                      (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_REVMOD_SHIFT)) & ENC_CTRL2_REVMOD_MASK)
#define ENC_CTRL2_OUTCTL_MASK                    (0x200U)
#define ENC_CTRL2_OUTCTL_SHIFT                   (9U)
#define ENC_CTRL2_OUTCTL(x)                      (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_OUTCTL_SHIFT)) & ENC_CTRL2_OUTCTL_MASK)
#define ENC_CTRL2_SABIE_MASK                     (0x400U)
#define ENC_CTRL2_SABIE_SHIFT                    (10U)
#define ENC_CTRL2_SABIE(x)                       (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_SABIE_SHIFT)) & ENC_CTRL2_SABIE_MASK)
#define ENC_CTRL2_SABIRQ_MASK                    (0x800U)
#define ENC_CTRL2_SABIRQ_SHIFT                   (11U)
#define ENC_CTRL2_SABIRQ(x)                      (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_SABIRQ_SHIFT)) & ENC_CTRL2_SABIRQ_MASK)

/*! @name UMOD - Upper Modulus Register */
#define ENC_UMOD_MOD_MASK                        (0xFFFFU)
#define ENC_UMOD_MOD_SHIFT                       (0U)
#define ENC_UMOD_MOD(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_UMOD_MOD_SHIFT)) & ENC_UMOD_MOD_MASK)

/*! @name LMOD - Lower Modulus Register */
#define ENC_LMOD_MOD_MASK                        (0xFFFFU)
#define ENC_LMOD_MOD_SHIFT                       (0U)
#define ENC_LMOD_MOD(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_LMOD_MOD_SHIFT)) & ENC_LMOD_MOD_MASK)

/*! @name UCOMP - Upper Position Compare Register */
#define ENC_UCOMP_COMP_MASK                      (0xFFFFU)
#define ENC_UCOMP_COMP_SHIFT                     (0U)
#define ENC_UCOMP_COMP(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_UCOMP_COMP_SHIFT)) & ENC_UCOMP_COMP_MASK)

/*! @name LCOMP - Lower Position Compare Register */
#define ENC_LCOMP_COMP_MASK                      (0xFFFFU)
#define ENC_LCOMP_COMP_SHIFT                     (0U)
#define ENC_LCOMP_COMP(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_LCOMP_COMP_SHIFT)) & ENC_LCOMP_COMP_MASK)


/*!
 * @}
 */ /* end of group ENC_Register_Masks */


/* ENC - Peripheral instance base addresses */
/** Peripheral ENC base address */
#define ENC_BASE                                 (0x40055000u)
/** Peripheral ENC base pointer */
#define ENC                                      ((ENC_Type *)ENC_BASE)
/** Array initializer of ENC peripheral base addresses */
#define ENC_BASE_ADDRS                           { ENC_BASE }
/** Array initializer of ENC peripheral base pointers */
#define ENC_BASE_PTRS                            { ENC }
/** Interrupt vectors for the ENC peripheral type */
#define ENC_COMPARE_IRQS                         { ENC_COMPARE_IRQn }
#define ENC_HOME_IRQS                            { ENC_HOME_IRQn }
#define ENC_WDOG_IRQS                            { ENC_WDOG_SAB_IRQn }
#define ENC_INDEX_IRQS                           { ENC_INDEX_IRQn }

/*!
 * @}
 */ /* end of group ENC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- ENET Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ENET_Peripheral_Access_Layer ENET Peripheral Access Layer
 * @{
 */

/** ENET - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[4];
  __IO uint32_t EIR;                               /**< Interrupt Event Register, offset: 0x4 */
  __IO uint32_t EIMR;                              /**< Interrupt Mask Register, offset: 0x8 */
       uint8_t RESERVED_1[4];
  __IO uint32_t RDAR;                              /**< Receive Descriptor Active Register, offset: 0x10 */
  __IO uint32_t TDAR;                              /**< Transmit Descriptor Active Register, offset: 0x14 */
       uint8_t RESERVED_2[12];
  __IO uint32_t ECR;                               /**< Ethernet Control Register, offset: 0x24 */
       uint8_t RESERVED_3[24];
  __IO uint32_t MMFR;                              /**< MII Management Frame Register, offset: 0x40 */
  __IO uint32_t MSCR;                              /**< MII Speed Control Register, offset: 0x44 */
       uint8_t RESERVED_4[28];
  __IO uint32_t MIBC;                              /**< MIB Control Register, offset: 0x64 */
       uint8_t RESERVED_5[28];
  __IO uint32_t RCR;                               /**< Receive Control Register, offset: 0x84 */
       uint8_t RESERVED_6[60];
  __IO uint32_t TCR;                               /**< Transmit Control Register, offset: 0xC4 */
       uint8_t RESERVED_7[28];
  __IO uint32_t PALR;                              /**< Physical Address Lower Register, offset: 0xE4 */
  __IO uint32_t PAUR;                              /**< Physical Address Upper Register, offset: 0xE8 */
  __IO uint32_t OPD;                               /**< Opcode/Pause Duration Register, offset: 0xEC */
       uint8_t RESERVED_8[40];
  __IO uint32_t IAUR;                              /**< Descriptor Individual Upper Address Register, offset: 0x118 */
  __IO uint32_t IALR;                              /**< Descriptor Individual Lower Address Register, offset: 0x11C */
  __IO uint32_t GAUR;                              /**< Descriptor Group Upper Address Register, offset: 0x120 */
  __IO uint32_t GALR;                              /**< Descriptor Group Lower Address Register, offset: 0x124 */
       uint8_t RESERVED_9[28];
  __IO uint32_t TFWR;                              /**< Transmit FIFO Watermark Register, offset: 0x144 */
       uint8_t RESERVED_10[56];
  __IO uint32_t RDSR;                              /**< Receive Descriptor Ring Start Register, offset: 0x180 */
  __IO uint32_t TDSR;                              /**< Transmit Buffer Descriptor Ring Start Register, offset: 0x184 */
  __IO uint32_t MRBR;                              /**< Maximum Receive Buffer Size Register, offset: 0x188 */
       uint8_t RESERVED_11[4];
  __IO uint32_t RSFL;                              /**< Receive FIFO Section Full Threshold, offset: 0x190 */
  __IO uint32_t RSEM;                              /**< Receive FIFO Section Empty Threshold, offset: 0x194 */
  __IO uint32_t RAEM;                              /**< Receive FIFO Almost Empty Threshold, offset: 0x198 */
  __IO uint32_t RAFL;                              /**< Receive FIFO Almost Full Threshold, offset: 0x19C */
  __IO uint32_t TSEM;                              /**< Transmit FIFO Section Empty Threshold, offset: 0x1A0 */
  __IO uint32_t TAEM;                              /**< Transmit FIFO Almost Empty Threshold, offset: 0x1A4 */
  __IO uint32_t TAFL;                              /**< Transmit FIFO Almost Full Threshold, offset: 0x1A8 */
  __IO uint32_t TIPG;                              /**< Transmit Inter-Packet Gap, offset: 0x1AC */
  __IO uint32_t FTRL;                              /**< Frame Truncation Length, offset: 0x1B0 */
       uint8_t RESERVED_12[12];
  __IO uint32_t TACC;                              /**< Transmit Accelerator Function Configuration, offset: 0x1C0 */
  __IO uint32_t RACC;                              /**< Receive Accelerator Function Configuration, offset: 0x1C4 */
       uint8_t RESERVED_13[56];
  __I  uint32_t RMON_T_DROP;                       /**< Reserved Statistic Register, offset: 0x200 */
  __I  uint32_t RMON_T_PACKETS;                    /**< Tx Packet Count Statistic Register, offset: 0x204 */
  __I  uint32_t RMON_T_BC_PKT;                     /**< Tx Broadcast Packets Statistic Register, offset: 0x208 */
  __I  uint32_t RMON_T_MC_PKT;                     /**< Tx Multicast Packets Statistic Register, offset: 0x20C */
  __I  uint32_t RMON_T_CRC_ALIGN;                  /**< Tx Packets with CRC/Align Error Statistic Register, offset: 0x210 */
  __I  uint32_t RMON_T_UNDERSIZE;                  /**< Tx Packets Less Than Bytes and Good CRC Statistic Register, offset: 0x214 */
  __I  uint32_t RMON_T_OVERSIZE;                   /**< Tx Packets GT MAX_FL bytes and Good CRC Statistic Register, offset: 0x218 */
  __I  uint32_t RMON_T_FRAG;                       /**< Tx Packets Less Than 64 Bytes and Bad CRC Statistic Register, offset: 0x21C */
  __I  uint32_t RMON_T_JAB;                        /**< Tx Packets Greater Than MAX_FL bytes and Bad CRC Statistic Register, offset: 0x220 */
  __I  uint32_t RMON_T_COL;                        /**< Tx Collision Count Statistic Register, offset: 0x224 */
  __I  uint32_t RMON_T_P64;                        /**< Tx 64-Byte Packets Statistic Register, offset: 0x228 */
  __I  uint32_t RMON_T_P65TO127;                   /**< Tx 65- to 127-byte Packets Statistic Register, offset: 0x22C */
  __I  uint32_t RMON_T_P128TO255;                  /**< Tx 128- to 255-byte Packets Statistic Register, offset: 0x230 */
  __I  uint32_t RMON_T_P256TO511;                  /**< Tx 256- to 511-byte Packets Statistic Register, offset: 0x234 */
  __I  uint32_t RMON_T_P512TO1023;                 /**< Tx 512- to 1023-byte Packets Statistic Register, offset: 0x238 */
  __I  uint32_t RMON_T_P1024TO2047;                /**< Tx 1024- to 2047-byte Packets Statistic Register, offset: 0x23C */
  __I  uint32_t RMON_T_P_GTE2048;                  /**< Tx Packets Greater Than 2048 Bytes Statistic Register, offset: 0x240 */
  __I  uint32_t RMON_T_OCTETS;                     /**< Tx Octets Statistic Register, offset: 0x244 */
  __I  uint32_t IEEE_T_DROP;                       /**< Reserved Statistic Register, offset: 0x248 */
  __I  uint32_t IEEE_T_FRAME_OK;                   /**< Frames Transmitted OK Statistic Register, offset: 0x24C */
  __I  uint32_t IEEE_T_1COL;                       /**< Frames Transmitted with Single Collision Statistic Register, offset: 0x250 */
  __I  uint32_t IEEE_T_MCOL;                       /**< Frames Transmitted with Multiple Collisions Statistic Register, offset: 0x254 */
  __I  uint32_t IEEE_T_DEF;                        /**< Frames Transmitted after Deferral Delay Statistic Register, offset: 0x258 */
  __I  uint32_t IEEE_T_LCOL;                       /**< Frames Transmitted with Late Collision Statistic Register, offset: 0x25C */
  __I  uint32_t IEEE_T_EXCOL;                      /**< Frames Transmitted with Excessive Collisions Statistic Register, offset: 0x260 */
  __I  uint32_t IEEE_T_MACERR;                     /**< Frames Transmitted with Tx FIFO Underrun Statistic Register, offset: 0x264 */
  __I  uint32_t IEEE_T_CSERR;                      /**< Frames Transmitted with Carrier Sense Error Statistic Register, offset: 0x268 */
  __I  uint32_t IEEE_T_SQE;                        /**< Reserved Statistic Register, offset: 0x26C */
  __I  uint32_t IEEE_T_FDXFC;                      /**< Flow Control Pause Frames Transmitted Statistic Register, offset: 0x270 */
  __I  uint32_t IEEE_T_OCTETS_OK;                  /**< Octet Count for Frames Transmitted w/o Error Statistic Register, offset: 0x274 */
       uint8_t RESERVED_14[12];
  __I  uint32_t RMON_R_PACKETS;                    /**< Rx Packet Count Statistic Register, offset: 0x284 */
  __I  uint32_t RMON_R_BC_PKT;                     /**< Rx Broadcast Packets Statistic Register, offset: 0x288 */
  __I  uint32_t RMON_R_MC_PKT;                     /**< Rx Multicast Packets Statistic Register, offset: 0x28C */
  __I  uint32_t RMON_R_CRC_ALIGN;                  /**< Rx Packets with CRC/Align Error Statistic Register, offset: 0x290 */
  __I  uint32_t RMON_R_UNDERSIZE;                  /**< Rx Packets with Less Than 64 Bytes and Good CRC Statistic Register, offset: 0x294 */
  __I  uint32_t RMON_R_OVERSIZE;                   /**< Rx Packets Greater Than MAX_FL and Good CRC Statistic Register, offset: 0x298 */
  __I  uint32_t RMON_R_FRAG;                       /**< Rx Packets Less Than 64 Bytes and Bad CRC Statistic Register, offset: 0x29C */
  __I  uint32_t RMON_R_JAB;                        /**< Rx Packets Greater Than MAX_FL Bytes and Bad CRC Statistic Register, offset: 0x2A0 */
  __I  uint32_t RMON_R_RESVD_0;                    /**< Reserved Statistic Register, offset: 0x2A4 */
  __I  uint32_t RMON_R_P64;                        /**< Rx 64-Byte Packets Statistic Register, offset: 0x2A8 */
  __I  uint32_t RMON_R_P65TO127;                   /**< Rx 65- to 127-Byte Packets Statistic Register, offset: 0x2AC */
  __I  uint32_t RMON_R_P128TO255;                  /**< Rx 128- to 255-Byte Packets Statistic Register, offset: 0x2B0 */
  __I  uint32_t RMON_R_P256TO511;                  /**< Rx 256- to 511-Byte Packets Statistic Register, offset: 0x2B4 */
  __I  uint32_t RMON_R_P512TO1023;                 /**< Rx 512- to 1023-Byte Packets Statistic Register, offset: 0x2B8 */
  __I  uint32_t RMON_R_P1024TO2047;                /**< Rx 1024- to 2047-Byte Packets Statistic Register, offset: 0x2BC */
  __I  uint32_t RMON_R_P_GTE2048;                  /**< Rx Packets Greater than 2048 Bytes Statistic Register, offset: 0x2C0 */
  __I  uint32_t RMON_R_OCTETS;                     /**< Rx Octets Statistic Register, offset: 0x2C4 */
  __I  uint32_t IEEE_R_DROP;                       /**< Frames not Counted Correctly Statistic Register, offset: 0x2C8 */
  __I  uint32_t IEEE_R_FRAME_OK;                   /**< Frames Received OK Statistic Register, offset: 0x2CC */
  __I  uint32_t IEEE_R_CRC;                        /**< Frames Received with CRC Error Statistic Register, offset: 0x2D0 */
  __I  uint32_t IEEE_R_ALIGN;                      /**< Frames Received with Alignment Error Statistic Register, offset: 0x2D4 */
  __I  uint32_t IEEE_R_MACERR;                     /**< Receive FIFO Overflow Count Statistic Register, offset: 0x2D8 */
  __I  uint32_t IEEE_R_FDXFC;                      /**< Flow Control Pause Frames Received Statistic Register, offset: 0x2DC */
  __I  uint32_t IEEE_R_OCTETS_OK;                  /**< Octet Count for Frames Received without Error Statistic Register, offset: 0x2E0 */
       uint8_t RESERVED_15[284];
  __IO uint32_t ATCR;                              /**< Adjustable Timer Control Register, offset: 0x400 */
  __IO uint32_t ATVR;                              /**< Timer Value Register, offset: 0x404 */
  __IO uint32_t ATOFF;                             /**< Timer Offset Register, offset: 0x408 */
  __IO uint32_t ATPER;                             /**< Timer Period Register, offset: 0x40C */
  __IO uint32_t ATCOR;                             /**< Timer Correction Register, offset: 0x410 */
  __IO uint32_t ATINC;                             /**< Time-Stamping Clock Period Register, offset: 0x414 */
  __I  uint32_t ATSTMP;                            /**< Timestamp of Last Transmitted Frame, offset: 0x418 */
       uint8_t RESERVED_16[488];
  __IO uint32_t TGSR;                              /**< Timer Global Status Register, offset: 0x604 */
  struct {                                         /* offset: 0x608, array step: 0x8 */
    __IO uint32_t TCSR;                              /**< Timer Control Status Register, array offset: 0x608, array step: 0x8 */
    __IO uint32_t TCCR;                              /**< Timer Compare Capture Register, array offset: 0x60C, array step: 0x8 */
  } CHANNEL[4];
} ENET_Type;

/* ----------------------------------------------------------------------------
   -- ENET Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ENET_Register_Masks ENET Register Masks
 * @{
 */

/*! @name EIR - Interrupt Event Register */
#define ENET_EIR_TS_TIMER_MASK                   (0x8000U)
#define ENET_EIR_TS_TIMER_SHIFT                  (15U)
#define ENET_EIR_TS_TIMER(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_EIR_TS_TIMER_SHIFT)) & ENET_EIR_TS_TIMER_MASK)
#define ENET_EIR_TS_AVAIL_MASK                   (0x10000U)
#define ENET_EIR_TS_AVAIL_SHIFT                  (16U)
#define ENET_EIR_TS_AVAIL(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_EIR_TS_AVAIL_SHIFT)) & ENET_EIR_TS_AVAIL_MASK)
#define ENET_EIR_WAKEUP_MASK                     (0x20000U)
#define ENET_EIR_WAKEUP_SHIFT                    (17U)
#define ENET_EIR_WAKEUP(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_EIR_WAKEUP_SHIFT)) & ENET_EIR_WAKEUP_MASK)
#define ENET_EIR_PLR_MASK                        (0x40000U)
#define ENET_EIR_PLR_SHIFT                       (18U)
#define ENET_EIR_PLR(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIR_PLR_SHIFT)) & ENET_EIR_PLR_MASK)
#define ENET_EIR_UN_MASK                         (0x80000U)
#define ENET_EIR_UN_SHIFT                        (19U)
#define ENET_EIR_UN(x)                           (((uint32_t)(((uint32_t)(x)) << ENET_EIR_UN_SHIFT)) & ENET_EIR_UN_MASK)
#define ENET_EIR_RL_MASK                         (0x100000U)
#define ENET_EIR_RL_SHIFT                        (20U)
#define ENET_EIR_RL(x)                           (((uint32_t)(((uint32_t)(x)) << ENET_EIR_RL_SHIFT)) & ENET_EIR_RL_MASK)
#define ENET_EIR_LC_MASK                         (0x200000U)
#define ENET_EIR_LC_SHIFT                        (21U)
#define ENET_EIR_LC(x)                           (((uint32_t)(((uint32_t)(x)) << ENET_EIR_LC_SHIFT)) & ENET_EIR_LC_MASK)
#define ENET_EIR_EBERR_MASK                      (0x400000U)
#define ENET_EIR_EBERR_SHIFT                     (22U)
#define ENET_EIR_EBERR(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_EIR_EBERR_SHIFT)) & ENET_EIR_EBERR_MASK)
#define ENET_EIR_MII_MASK                        (0x800000U)
#define ENET_EIR_MII_SHIFT                       (23U)
#define ENET_EIR_MII(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIR_MII_SHIFT)) & ENET_EIR_MII_MASK)
#define ENET_EIR_RXB_MASK                        (0x1000000U)
#define ENET_EIR_RXB_SHIFT                       (24U)
#define ENET_EIR_RXB(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIR_RXB_SHIFT)) & ENET_EIR_RXB_MASK)
#define ENET_EIR_RXF_MASK                        (0x2000000U)
#define ENET_EIR_RXF_SHIFT                       (25U)
#define ENET_EIR_RXF(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIR_RXF_SHIFT)) & ENET_EIR_RXF_MASK)
#define ENET_EIR_TXB_MASK                        (0x4000000U)
#define ENET_EIR_TXB_SHIFT                       (26U)
#define ENET_EIR_TXB(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIR_TXB_SHIFT)) & ENET_EIR_TXB_MASK)
#define ENET_EIR_TXF_MASK                        (0x8000000U)
#define ENET_EIR_TXF_SHIFT                       (27U)
#define ENET_EIR_TXF(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIR_TXF_SHIFT)) & ENET_EIR_TXF_MASK)
#define ENET_EIR_GRA_MASK                        (0x10000000U)
#define ENET_EIR_GRA_SHIFT                       (28U)
#define ENET_EIR_GRA(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIR_GRA_SHIFT)) & ENET_EIR_GRA_MASK)
#define ENET_EIR_BABT_MASK                       (0x20000000U)
#define ENET_EIR_BABT_SHIFT                      (29U)
#define ENET_EIR_BABT(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIR_BABT_SHIFT)) & ENET_EIR_BABT_MASK)
#define ENET_EIR_BABR_MASK                       (0x40000000U)
#define ENET_EIR_BABR_SHIFT                      (30U)
#define ENET_EIR_BABR(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIR_BABR_SHIFT)) & ENET_EIR_BABR_MASK)

/*! @name EIMR - Interrupt Mask Register */
#define ENET_EIMR_TS_TIMER_MASK                  (0x8000U)
#define ENET_EIMR_TS_TIMER_SHIFT                 (15U)
#define ENET_EIMR_TS_TIMER(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_TS_TIMER_SHIFT)) & ENET_EIMR_TS_TIMER_MASK)
#define ENET_EIMR_TS_AVAIL_MASK                  (0x10000U)
#define ENET_EIMR_TS_AVAIL_SHIFT                 (16U)
#define ENET_EIMR_TS_AVAIL(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_TS_AVAIL_SHIFT)) & ENET_EIMR_TS_AVAIL_MASK)
#define ENET_EIMR_WAKEUP_MASK                    (0x20000U)
#define ENET_EIMR_WAKEUP_SHIFT                   (17U)
#define ENET_EIMR_WAKEUP(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_WAKEUP_SHIFT)) & ENET_EIMR_WAKEUP_MASK)
#define ENET_EIMR_PLR_MASK                       (0x40000U)
#define ENET_EIMR_PLR_SHIFT                      (18U)
#define ENET_EIMR_PLR(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_PLR_SHIFT)) & ENET_EIMR_PLR_MASK)
#define ENET_EIMR_UN_MASK                        (0x80000U)
#define ENET_EIMR_UN_SHIFT                       (19U)
#define ENET_EIMR_UN(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_UN_SHIFT)) & ENET_EIMR_UN_MASK)
#define ENET_EIMR_RL_MASK                        (0x100000U)
#define ENET_EIMR_RL_SHIFT                       (20U)
#define ENET_EIMR_RL(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_RL_SHIFT)) & ENET_EIMR_RL_MASK)
#define ENET_EIMR_LC_MASK                        (0x200000U)
#define ENET_EIMR_LC_SHIFT                       (21U)
#define ENET_EIMR_LC(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_LC_SHIFT)) & ENET_EIMR_LC_MASK)
#define ENET_EIMR_EBERR_MASK                     (0x400000U)
#define ENET_EIMR_EBERR_SHIFT                    (22U)
#define ENET_EIMR_EBERR(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_EBERR_SHIFT)) & ENET_EIMR_EBERR_MASK)
#define ENET_EIMR_MII_MASK                       (0x800000U)
#define ENET_EIMR_MII_SHIFT                      (23U)
#define ENET_EIMR_MII(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_MII_SHIFT)) & ENET_EIMR_MII_MASK)
#define ENET_EIMR_RXB_MASK                       (0x1000000U)
#define ENET_EIMR_RXB_SHIFT                      (24U)
#define ENET_EIMR_RXB(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_RXB_SHIFT)) & ENET_EIMR_RXB_MASK)
#define ENET_EIMR_RXF_MASK                       (0x2000000U)
#define ENET_EIMR_RXF_SHIFT                      (25U)
#define ENET_EIMR_RXF(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_RXF_SHIFT)) & ENET_EIMR_RXF_MASK)
#define ENET_EIMR_TXB_MASK                       (0x4000000U)
#define ENET_EIMR_TXB_SHIFT                      (26U)
#define ENET_EIMR_TXB(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_TXB_SHIFT)) & ENET_EIMR_TXB_MASK)
#define ENET_EIMR_TXF_MASK                       (0x8000000U)
#define ENET_EIMR_TXF_SHIFT                      (27U)
#define ENET_EIMR_TXF(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_TXF_SHIFT)) & ENET_EIMR_TXF_MASK)
#define ENET_EIMR_GRA_MASK                       (0x10000000U)
#define ENET_EIMR_GRA_SHIFT                      (28U)
#define ENET_EIMR_GRA(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_GRA_SHIFT)) & ENET_EIMR_GRA_MASK)
#define ENET_EIMR_BABT_MASK                      (0x20000000U)
#define ENET_EIMR_BABT_SHIFT                     (29U)
#define ENET_EIMR_BABT(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_BABT_SHIFT)) & ENET_EIMR_BABT_MASK)
#define ENET_EIMR_BABR_MASK                      (0x40000000U)
#define ENET_EIMR_BABR_SHIFT                     (30U)
#define ENET_EIMR_BABR(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_BABR_SHIFT)) & ENET_EIMR_BABR_MASK)

/*! @name RDAR - Receive Descriptor Active Register */
#define ENET_RDAR_RDAR_MASK                      (0x1000000U)
#define ENET_RDAR_RDAR_SHIFT                     (24U)
#define ENET_RDAR_RDAR(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_RDAR_RDAR_SHIFT)) & ENET_RDAR_RDAR_MASK)

/*! @name TDAR - Transmit Descriptor Active Register */
#define ENET_TDAR_TDAR_MASK                      (0x1000000U)
#define ENET_TDAR_TDAR_SHIFT                     (24U)
#define ENET_TDAR_TDAR(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_TDAR_TDAR_SHIFT)) & ENET_TDAR_TDAR_MASK)

/*! @name ECR - Ethernet Control Register */
#define ENET_ECR_RESET_MASK                      (0x1U)
#define ENET_ECR_RESET_SHIFT                     (0U)
#define ENET_ECR_RESET(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_ECR_RESET_SHIFT)) & ENET_ECR_RESET_MASK)
#define ENET_ECR_ETHEREN_MASK                    (0x2U)
#define ENET_ECR_ETHEREN_SHIFT                   (1U)
#define ENET_ECR_ETHEREN(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_ECR_ETHEREN_SHIFT)) & ENET_ECR_ETHEREN_MASK)
#define ENET_ECR_MAGICEN_MASK                    (0x4U)
#define ENET_ECR_MAGICEN_SHIFT                   (2U)
#define ENET_ECR_MAGICEN(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_ECR_MAGICEN_SHIFT)) & ENET_ECR_MAGICEN_MASK)
#define ENET_ECR_SLEEP_MASK                      (0x8U)
#define ENET_ECR_SLEEP_SHIFT                     (3U)
#define ENET_ECR_SLEEP(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_ECR_SLEEP_SHIFT)) & ENET_ECR_SLEEP_MASK)
#define ENET_ECR_EN1588_MASK                     (0x10U)
#define ENET_ECR_EN1588_SHIFT                    (4U)
#define ENET_ECR_EN1588(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_ECR_EN1588_SHIFT)) & ENET_ECR_EN1588_MASK)
#define ENET_ECR_DBGEN_MASK                      (0x40U)
#define ENET_ECR_DBGEN_SHIFT                     (6U)
#define ENET_ECR_DBGEN(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_ECR_DBGEN_SHIFT)) & ENET_ECR_DBGEN_MASK)
#define ENET_ECR_STOPEN_MASK                     (0x80U)
#define ENET_ECR_STOPEN_SHIFT                    (7U)
#define ENET_ECR_STOPEN(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_ECR_STOPEN_SHIFT)) & ENET_ECR_STOPEN_MASK)
#define ENET_ECR_DBSWP_MASK                      (0x100U)
#define ENET_ECR_DBSWP_SHIFT                     (8U)
#define ENET_ECR_DBSWP(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_ECR_DBSWP_SHIFT)) & ENET_ECR_DBSWP_MASK)

/*! @name MMFR - MII Management Frame Register */
#define ENET_MMFR_DATA_MASK                      (0xFFFFU)
#define ENET_MMFR_DATA_SHIFT                     (0U)
#define ENET_MMFR_DATA(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_MMFR_DATA_SHIFT)) & ENET_MMFR_DATA_MASK)
#define ENET_MMFR_TA_MASK                        (0x30000U)
#define ENET_MMFR_TA_SHIFT                       (16U)
#define ENET_MMFR_TA(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_MMFR_TA_SHIFT)) & ENET_MMFR_TA_MASK)
#define ENET_MMFR_RA_MASK                        (0x7C0000U)
#define ENET_MMFR_RA_SHIFT                       (18U)
#define ENET_MMFR_RA(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_MMFR_RA_SHIFT)) & ENET_MMFR_RA_MASK)
#define ENET_MMFR_PA_MASK                        (0xF800000U)
#define ENET_MMFR_PA_SHIFT                       (23U)
#define ENET_MMFR_PA(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_MMFR_PA_SHIFT)) & ENET_MMFR_PA_MASK)
#define ENET_MMFR_OP_MASK                        (0x30000000U)
#define ENET_MMFR_OP_SHIFT                       (28U)
#define ENET_MMFR_OP(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_MMFR_OP_SHIFT)) & ENET_MMFR_OP_MASK)
#define ENET_MMFR_ST_MASK                        (0xC0000000U)
#define ENET_MMFR_ST_SHIFT                       (30U)
#define ENET_MMFR_ST(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_MMFR_ST_SHIFT)) & ENET_MMFR_ST_MASK)

/*! @name MSCR - MII Speed Control Register */
#define ENET_MSCR_MII_SPEED_MASK                 (0x7EU)
#define ENET_MSCR_MII_SPEED_SHIFT                (1U)
#define ENET_MSCR_MII_SPEED(x)                   (((uint32_t)(((uint32_t)(x)) << ENET_MSCR_MII_SPEED_SHIFT)) & ENET_MSCR_MII_SPEED_MASK)
#define ENET_MSCR_DIS_PRE_MASK                   (0x80U)
#define ENET_MSCR_DIS_PRE_SHIFT                  (7U)
#define ENET_MSCR_DIS_PRE(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_MSCR_DIS_PRE_SHIFT)) & ENET_MSCR_DIS_PRE_MASK)
#define ENET_MSCR_HOLDTIME_MASK                  (0x700U)
#define ENET_MSCR_HOLDTIME_SHIFT                 (8U)
#define ENET_MSCR_HOLDTIME(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_MSCR_HOLDTIME_SHIFT)) & ENET_MSCR_HOLDTIME_MASK)

/*! @name MIBC - MIB Control Register */
#define ENET_MIBC_MIB_CLEAR_MASK                 (0x20000000U)
#define ENET_MIBC_MIB_CLEAR_SHIFT                (29U)
#define ENET_MIBC_MIB_CLEAR(x)                   (((uint32_t)(((uint32_t)(x)) << ENET_MIBC_MIB_CLEAR_SHIFT)) & ENET_MIBC_MIB_CLEAR_MASK)
#define ENET_MIBC_MIB_IDLE_MASK                  (0x40000000U)
#define ENET_MIBC_MIB_IDLE_SHIFT                 (30U)
#define ENET_MIBC_MIB_IDLE(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_MIBC_MIB_IDLE_SHIFT)) & ENET_MIBC_MIB_IDLE_MASK)
#define ENET_MIBC_MIB_DIS_MASK                   (0x80000000U)
#define ENET_MIBC_MIB_DIS_SHIFT                  (31U)
#define ENET_MIBC_MIB_DIS(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_MIBC_MIB_DIS_SHIFT)) & ENET_MIBC_MIB_DIS_MASK)

/*! @name RCR - Receive Control Register */
#define ENET_RCR_LOOP_MASK                       (0x1U)
#define ENET_RCR_LOOP_SHIFT                      (0U)
#define ENET_RCR_LOOP(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_RCR_LOOP_SHIFT)) & ENET_RCR_LOOP_MASK)
#define ENET_RCR_DRT_MASK                        (0x2U)
#define ENET_RCR_DRT_SHIFT                       (1U)
#define ENET_RCR_DRT(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_RCR_DRT_SHIFT)) & ENET_RCR_DRT_MASK)
#define ENET_RCR_MII_MODE_MASK                   (0x4U)
#define ENET_RCR_MII_MODE_SHIFT                  (2U)
#define ENET_RCR_MII_MODE(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_RCR_MII_MODE_SHIFT)) & ENET_RCR_MII_MODE_MASK)
#define ENET_RCR_PROM_MASK                       (0x8U)
#define ENET_RCR_PROM_SHIFT                      (3U)
#define ENET_RCR_PROM(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_RCR_PROM_SHIFT)) & ENET_RCR_PROM_MASK)
#define ENET_RCR_BC_REJ_MASK                     (0x10U)
#define ENET_RCR_BC_REJ_SHIFT                    (4U)
#define ENET_RCR_BC_REJ(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_RCR_BC_REJ_SHIFT)) & ENET_RCR_BC_REJ_MASK)
#define ENET_RCR_FCE_MASK                        (0x20U)
#define ENET_RCR_FCE_SHIFT                       (5U)
#define ENET_RCR_FCE(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_RCR_FCE_SHIFT)) & ENET_RCR_FCE_MASK)
#define ENET_RCR_RMII_MODE_MASK                  (0x100U)
#define ENET_RCR_RMII_MODE_SHIFT                 (8U)
#define ENET_RCR_RMII_MODE(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_RCR_RMII_MODE_SHIFT)) & ENET_RCR_RMII_MODE_MASK)
#define ENET_RCR_RMII_10T_MASK                   (0x200U)
#define ENET_RCR_RMII_10T_SHIFT                  (9U)
#define ENET_RCR_RMII_10T(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_RCR_RMII_10T_SHIFT)) & ENET_RCR_RMII_10T_MASK)
#define ENET_RCR_PADEN_MASK                      (0x1000U)
#define ENET_RCR_PADEN_SHIFT                     (12U)
#define ENET_RCR_PADEN(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_RCR_PADEN_SHIFT)) & ENET_RCR_PADEN_MASK)
#define ENET_RCR_PAUFWD_MASK                     (0x2000U)
#define ENET_RCR_PAUFWD_SHIFT                    (13U)
#define ENET_RCR_PAUFWD(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_RCR_PAUFWD_SHIFT)) & ENET_RCR_PAUFWD_MASK)
#define ENET_RCR_CRCFWD_MASK                     (0x4000U)
#define ENET_RCR_CRCFWD_SHIFT                    (14U)
#define ENET_RCR_CRCFWD(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_RCR_CRCFWD_SHIFT)) & ENET_RCR_CRCFWD_MASK)
#define ENET_RCR_CFEN_MASK                       (0x8000U)
#define ENET_RCR_CFEN_SHIFT                      (15U)
#define ENET_RCR_CFEN(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_RCR_CFEN_SHIFT)) & ENET_RCR_CFEN_MASK)
#define ENET_RCR_MAX_FL_MASK                     (0x3FFF0000U)
#define ENET_RCR_MAX_FL_SHIFT                    (16U)
#define ENET_RCR_MAX_FL(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_RCR_MAX_FL_SHIFT)) & ENET_RCR_MAX_FL_MASK)
#define ENET_RCR_NLC_MASK                        (0x40000000U)
#define ENET_RCR_NLC_SHIFT                       (30U)
#define ENET_RCR_NLC(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_RCR_NLC_SHIFT)) & ENET_RCR_NLC_MASK)
#define ENET_RCR_GRS_MASK                        (0x80000000U)
#define ENET_RCR_GRS_SHIFT                       (31U)
#define ENET_RCR_GRS(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_RCR_GRS_SHIFT)) & ENET_RCR_GRS_MASK)

/*! @name TCR - Transmit Control Register */
#define ENET_TCR_GTS_MASK                        (0x1U)
#define ENET_TCR_GTS_SHIFT                       (0U)
#define ENET_TCR_GTS(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_TCR_GTS_SHIFT)) & ENET_TCR_GTS_MASK)
#define ENET_TCR_FDEN_MASK                       (0x4U)
#define ENET_TCR_FDEN_SHIFT                      (2U)
#define ENET_TCR_FDEN(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_TCR_FDEN_SHIFT)) & ENET_TCR_FDEN_MASK)
#define ENET_TCR_TFC_PAUSE_MASK                  (0x8U)
#define ENET_TCR_TFC_PAUSE_SHIFT                 (3U)
#define ENET_TCR_TFC_PAUSE(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_TCR_TFC_PAUSE_SHIFT)) & ENET_TCR_TFC_PAUSE_MASK)
#define ENET_TCR_RFC_PAUSE_MASK                  (0x10U)
#define ENET_TCR_RFC_PAUSE_SHIFT                 (4U)
#define ENET_TCR_RFC_PAUSE(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_TCR_RFC_PAUSE_SHIFT)) & ENET_TCR_RFC_PAUSE_MASK)
#define ENET_TCR_ADDSEL_MASK                     (0xE0U)
#define ENET_TCR_ADDSEL_SHIFT                    (5U)
#define ENET_TCR_ADDSEL(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_TCR_ADDSEL_SHIFT)) & ENET_TCR_ADDSEL_MASK)
#define ENET_TCR_ADDINS_MASK                     (0x100U)
#define ENET_TCR_ADDINS_SHIFT                    (8U)
#define ENET_TCR_ADDINS(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_TCR_ADDINS_SHIFT)) & ENET_TCR_ADDINS_MASK)
#define ENET_TCR_CRCFWD_MASK                     (0x200U)
#define ENET_TCR_CRCFWD_SHIFT                    (9U)
#define ENET_TCR_CRCFWD(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_TCR_CRCFWD_SHIFT)) & ENET_TCR_CRCFWD_MASK)

/*! @name PALR - Physical Address Lower Register */
#define ENET_PALR_PADDR1_MASK                    (0xFFFFFFFFU)
#define ENET_PALR_PADDR1_SHIFT                   (0U)
#define ENET_PALR_PADDR1(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_PALR_PADDR1_SHIFT)) & ENET_PALR_PADDR1_MASK)

/*! @name PAUR - Physical Address Upper Register */
#define ENET_PAUR_TYPE_MASK                      (0xFFFFU)
#define ENET_PAUR_TYPE_SHIFT                     (0U)
#define ENET_PAUR_TYPE(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_PAUR_TYPE_SHIFT)) & ENET_PAUR_TYPE_MASK)
#define ENET_PAUR_PADDR2_MASK                    (0xFFFF0000U)
#define ENET_PAUR_PADDR2_SHIFT                   (16U)
#define ENET_PAUR_PADDR2(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_PAUR_PADDR2_SHIFT)) & ENET_PAUR_PADDR2_MASK)

/*! @name OPD - Opcode/Pause Duration Register */
#define ENET_OPD_PAUSE_DUR_MASK                  (0xFFFFU)
#define ENET_OPD_PAUSE_DUR_SHIFT                 (0U)
#define ENET_OPD_PAUSE_DUR(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_OPD_PAUSE_DUR_SHIFT)) & ENET_OPD_PAUSE_DUR_MASK)
#define ENET_OPD_OPCODE_MASK                     (0xFFFF0000U)
#define ENET_OPD_OPCODE_SHIFT                    (16U)
#define ENET_OPD_OPCODE(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_OPD_OPCODE_SHIFT)) & ENET_OPD_OPCODE_MASK)

/*! @name IAUR - Descriptor Individual Upper Address Register */
#define ENET_IAUR_IADDR1_MASK                    (0xFFFFFFFFU)
#define ENET_IAUR_IADDR1_SHIFT                   (0U)
#define ENET_IAUR_IADDR1(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_IAUR_IADDR1_SHIFT)) & ENET_IAUR_IADDR1_MASK)

/*! @name IALR - Descriptor Individual Lower Address Register */
#define ENET_IALR_IADDR2_MASK                    (0xFFFFFFFFU)
#define ENET_IALR_IADDR2_SHIFT                   (0U)
#define ENET_IALR_IADDR2(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_IALR_IADDR2_SHIFT)) & ENET_IALR_IADDR2_MASK)

/*! @name GAUR - Descriptor Group Upper Address Register */
#define ENET_GAUR_GADDR1_MASK                    (0xFFFFFFFFU)
#define ENET_GAUR_GADDR1_SHIFT                   (0U)
#define ENET_GAUR_GADDR1(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_GAUR_GADDR1_SHIFT)) & ENET_GAUR_GADDR1_MASK)

/*! @name GALR - Descriptor Group Lower Address Register */
#define ENET_GALR_GADDR2_MASK                    (0xFFFFFFFFU)
#define ENET_GALR_GADDR2_SHIFT                   (0U)
#define ENET_GALR_GADDR2(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_GALR_GADDR2_SHIFT)) & ENET_GALR_GADDR2_MASK)

/*! @name TFWR - Transmit FIFO Watermark Register */
#define ENET_TFWR_TFWR_MASK                      (0x3FU)
#define ENET_TFWR_TFWR_SHIFT                     (0U)
#define ENET_TFWR_TFWR(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_TFWR_TFWR_SHIFT)) & ENET_TFWR_TFWR_MASK)
#define ENET_TFWR_STRFWD_MASK                    (0x100U)
#define ENET_TFWR_STRFWD_SHIFT                   (8U)
#define ENET_TFWR_STRFWD(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_TFWR_STRFWD_SHIFT)) & ENET_TFWR_STRFWD_MASK)

/*! @name RDSR - Receive Descriptor Ring Start Register */
#define ENET_RDSR_R_DES_START_MASK               (0xFFFFFFF8U)
#define ENET_RDSR_R_DES_START_SHIFT              (3U)
#define ENET_RDSR_R_DES_START(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_RDSR_R_DES_START_SHIFT)) & ENET_RDSR_R_DES_START_MASK)

/*! @name TDSR - Transmit Buffer Descriptor Ring Start Register */
#define ENET_TDSR_X_DES_START_MASK               (0xFFFFFFF8U)
#define ENET_TDSR_X_DES_START_SHIFT              (3U)
#define ENET_TDSR_X_DES_START(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_TDSR_X_DES_START_SHIFT)) & ENET_TDSR_X_DES_START_MASK)

/*! @name MRBR - Maximum Receive Buffer Size Register */
#define ENET_MRBR_R_BUF_SIZE_MASK                (0x7F0U)
#define ENET_MRBR_R_BUF_SIZE_SHIFT               (4U)
#define ENET_MRBR_R_BUF_SIZE(x)                  (((uint32_t)(((uint32_t)(x)) << ENET_MRBR_R_BUF_SIZE_SHIFT)) & ENET_MRBR_R_BUF_SIZE_MASK)

/*! @name RSFL - Receive FIFO Section Full Threshold */
#define ENET_RSFL_RX_SECTION_FULL_MASK           (0xFFU)
#define ENET_RSFL_RX_SECTION_FULL_SHIFT          (0U)
#define ENET_RSFL_RX_SECTION_FULL(x)             (((uint32_t)(((uint32_t)(x)) << ENET_RSFL_RX_SECTION_FULL_SHIFT)) & ENET_RSFL_RX_SECTION_FULL_MASK)

/*! @name RSEM - Receive FIFO Section Empty Threshold */
#define ENET_RSEM_RX_SECTION_EMPTY_MASK          (0xFFU)
#define ENET_RSEM_RX_SECTION_EMPTY_SHIFT         (0U)
#define ENET_RSEM_RX_SECTION_EMPTY(x)            (((uint32_t)(((uint32_t)(x)) << ENET_RSEM_RX_SECTION_EMPTY_SHIFT)) & ENET_RSEM_RX_SECTION_EMPTY_MASK)
#define ENET_RSEM_STAT_SECTION_EMPTY_MASK        (0x1F0000U)
#define ENET_RSEM_STAT_SECTION_EMPTY_SHIFT       (16U)
#define ENET_RSEM_STAT_SECTION_EMPTY(x)          (((uint32_t)(((uint32_t)(x)) << ENET_RSEM_STAT_SECTION_EMPTY_SHIFT)) & ENET_RSEM_STAT_SECTION_EMPTY_MASK)

/*! @name RAEM - Receive FIFO Almost Empty Threshold */
#define ENET_RAEM_RX_ALMOST_EMPTY_MASK           (0xFFU)
#define ENET_RAEM_RX_ALMOST_EMPTY_SHIFT          (0U)
#define ENET_RAEM_RX_ALMOST_EMPTY(x)             (((uint32_t)(((uint32_t)(x)) << ENET_RAEM_RX_ALMOST_EMPTY_SHIFT)) & ENET_RAEM_RX_ALMOST_EMPTY_MASK)

/*! @name RAFL - Receive FIFO Almost Full Threshold */
#define ENET_RAFL_RX_ALMOST_FULL_MASK            (0xFFU)
#define ENET_RAFL_RX_ALMOST_FULL_SHIFT           (0U)
#define ENET_RAFL_RX_ALMOST_FULL(x)              (((uint32_t)(((uint32_t)(x)) << ENET_RAFL_RX_ALMOST_FULL_SHIFT)) & ENET_RAFL_RX_ALMOST_FULL_MASK)

/*! @name TSEM - Transmit FIFO Section Empty Threshold */
#define ENET_TSEM_TX_SECTION_EMPTY_MASK          (0xFFU)
#define ENET_TSEM_TX_SECTION_EMPTY_SHIFT         (0U)
#define ENET_TSEM_TX_SECTION_EMPTY(x)            (((uint32_t)(((uint32_t)(x)) << ENET_TSEM_TX_SECTION_EMPTY_SHIFT)) & ENET_TSEM_TX_SECTION_EMPTY_MASK)

/*! @name TAEM - Transmit FIFO Almost Empty Threshold */
#define ENET_TAEM_TX_ALMOST_EMPTY_MASK           (0xFFU)
#define ENET_TAEM_TX_ALMOST_EMPTY_SHIFT          (0U)
#define ENET_TAEM_TX_ALMOST_EMPTY(x)             (((uint32_t)(((uint32_t)(x)) << ENET_TAEM_TX_ALMOST_EMPTY_SHIFT)) & ENET_TAEM_TX_ALMOST_EMPTY_MASK)

/*! @name TAFL - Transmit FIFO Almost Full Threshold */
#define ENET_TAFL_TX_ALMOST_FULL_MASK            (0xFFU)
#define ENET_TAFL_TX_ALMOST_FULL_SHIFT           (0U)
#define ENET_TAFL_TX_ALMOST_FULL(x)              (((uint32_t)(((uint32_t)(x)) << ENET_TAFL_TX_ALMOST_FULL_SHIFT)) & ENET_TAFL_TX_ALMOST_FULL_MASK)

/*! @name TIPG - Transmit Inter-Packet Gap */
#define ENET_TIPG_IPG_MASK                       (0x1FU)
#define ENET_TIPG_IPG_SHIFT                      (0U)
#define ENET_TIPG_IPG(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_TIPG_IPG_SHIFT)) & ENET_TIPG_IPG_MASK)

/*! @name FTRL - Frame Truncation Length */
#define ENET_FTRL_TRUNC_FL_MASK                  (0x3FFFU)
#define ENET_FTRL_TRUNC_FL_SHIFT                 (0U)
#define ENET_FTRL_TRUNC_FL(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_FTRL_TRUNC_FL_SHIFT)) & ENET_FTRL_TRUNC_FL_MASK)

/*! @name TACC - Transmit Accelerator Function Configuration */
#define ENET_TACC_SHIFT16_MASK                   (0x1U)
#define ENET_TACC_SHIFT16_SHIFT                  (0U)
#define ENET_TACC_SHIFT16(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_TACC_SHIFT16_SHIFT)) & ENET_TACC_SHIFT16_MASK)
#define ENET_TACC_IPCHK_MASK                     (0x8U)
#define ENET_TACC_IPCHK_SHIFT                    (3U)
#define ENET_TACC_IPCHK(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_TACC_IPCHK_SHIFT)) & ENET_TACC_IPCHK_MASK)
#define ENET_TACC_PROCHK_MASK                    (0x10U)
#define ENET_TACC_PROCHK_SHIFT                   (4U)
#define ENET_TACC_PROCHK(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_TACC_PROCHK_SHIFT)) & ENET_TACC_PROCHK_MASK)

/*! @name RACC - Receive Accelerator Function Configuration */
#define ENET_RACC_PADREM_MASK                    (0x1U)
#define ENET_RACC_PADREM_SHIFT                   (0U)
#define ENET_RACC_PADREM(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_RACC_PADREM_SHIFT)) & ENET_RACC_PADREM_MASK)
#define ENET_RACC_IPDIS_MASK                     (0x2U)
#define ENET_RACC_IPDIS_SHIFT                    (1U)
#define ENET_RACC_IPDIS(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_RACC_IPDIS_SHIFT)) & ENET_RACC_IPDIS_MASK)
#define ENET_RACC_PRODIS_MASK                    (0x4U)
#define ENET_RACC_PRODIS_SHIFT                   (2U)
#define ENET_RACC_PRODIS(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_RACC_PRODIS_SHIFT)) & ENET_RACC_PRODIS_MASK)
#define ENET_RACC_LINEDIS_MASK                   (0x40U)
#define ENET_RACC_LINEDIS_SHIFT                  (6U)
#define ENET_RACC_LINEDIS(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_RACC_LINEDIS_SHIFT)) & ENET_RACC_LINEDIS_MASK)
#define ENET_RACC_SHIFT16_MASK                   (0x80U)
#define ENET_RACC_SHIFT16_SHIFT                  (7U)
#define ENET_RACC_SHIFT16(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_RACC_SHIFT16_SHIFT)) & ENET_RACC_SHIFT16_MASK)

/*! @name RMON_T_PACKETS - Tx Packet Count Statistic Register */
#define ENET_RMON_T_PACKETS_TXPKTS_MASK          (0xFFFFU)
#define ENET_RMON_T_PACKETS_TXPKTS_SHIFT         (0U)
#define ENET_RMON_T_PACKETS_TXPKTS(x)            (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_PACKETS_TXPKTS_SHIFT)) & ENET_RMON_T_PACKETS_TXPKTS_MASK)

/*! @name RMON_T_BC_PKT - Tx Broadcast Packets Statistic Register */
#define ENET_RMON_T_BC_PKT_TXPKTS_MASK           (0xFFFFU)
#define ENET_RMON_T_BC_PKT_TXPKTS_SHIFT          (0U)
#define ENET_RMON_T_BC_PKT_TXPKTS(x)             (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_BC_PKT_TXPKTS_SHIFT)) & ENET_RMON_T_BC_PKT_TXPKTS_MASK)

/*! @name RMON_T_MC_PKT - Tx Multicast Packets Statistic Register */
#define ENET_RMON_T_MC_PKT_TXPKTS_MASK           (0xFFFFU)
#define ENET_RMON_T_MC_PKT_TXPKTS_SHIFT          (0U)
#define ENET_RMON_T_MC_PKT_TXPKTS(x)             (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_MC_PKT_TXPKTS_SHIFT)) & ENET_RMON_T_MC_PKT_TXPKTS_MASK)

/*! @name RMON_T_CRC_ALIGN - Tx Packets with CRC/Align Error Statistic Register */
#define ENET_RMON_T_CRC_ALIGN_TXPKTS_MASK        (0xFFFFU)
#define ENET_RMON_T_CRC_ALIGN_TXPKTS_SHIFT       (0U)
#define ENET_RMON_T_CRC_ALIGN_TXPKTS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_CRC_ALIGN_TXPKTS_SHIFT)) & ENET_RMON_T_CRC_ALIGN_TXPKTS_MASK)

/*! @name RMON_T_UNDERSIZE - Tx Packets Less Than Bytes and Good CRC Statistic Register */
#define ENET_RMON_T_UNDERSIZE_TXPKTS_MASK        (0xFFFFU)
#define ENET_RMON_T_UNDERSIZE_TXPKTS_SHIFT       (0U)
#define ENET_RMON_T_UNDERSIZE_TXPKTS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_UNDERSIZE_TXPKTS_SHIFT)) & ENET_RMON_T_UNDERSIZE_TXPKTS_MASK)

/*! @name RMON_T_OVERSIZE - Tx Packets GT MAX_FL bytes and Good CRC Statistic Register */
#define ENET_RMON_T_OVERSIZE_TXPKTS_MASK         (0xFFFFU)
#define ENET_RMON_T_OVERSIZE_TXPKTS_SHIFT        (0U)
#define ENET_RMON_T_OVERSIZE_TXPKTS(x)           (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_OVERSIZE_TXPKTS_SHIFT)) & ENET_RMON_T_OVERSIZE_TXPKTS_MASK)

/*! @name RMON_T_FRAG - Tx Packets Less Than 64 Bytes and Bad CRC Statistic Register */
#define ENET_RMON_T_FRAG_TXPKTS_MASK             (0xFFFFU)
#define ENET_RMON_T_FRAG_TXPKTS_SHIFT            (0U)
#define ENET_RMON_T_FRAG_TXPKTS(x)               (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_FRAG_TXPKTS_SHIFT)) & ENET_RMON_T_FRAG_TXPKTS_MASK)

/*! @name RMON_T_JAB - Tx Packets Greater Than MAX_FL bytes and Bad CRC Statistic Register */
#define ENET_RMON_T_JAB_TXPKTS_MASK              (0xFFFFU)
#define ENET_RMON_T_JAB_TXPKTS_SHIFT             (0U)
#define ENET_RMON_T_JAB_TXPKTS(x)                (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_JAB_TXPKTS_SHIFT)) & ENET_RMON_T_JAB_TXPKTS_MASK)

/*! @name RMON_T_COL - Tx Collision Count Statistic Register */
#define ENET_RMON_T_COL_TXPKTS_MASK              (0xFFFFU)
#define ENET_RMON_T_COL_TXPKTS_SHIFT             (0U)
#define ENET_RMON_T_COL_TXPKTS(x)                (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_COL_TXPKTS_SHIFT)) & ENET_RMON_T_COL_TXPKTS_MASK)

/*! @name RMON_T_P64 - Tx 64-Byte Packets Statistic Register */
#define ENET_RMON_T_P64_TXPKTS_MASK              (0xFFFFU)
#define ENET_RMON_T_P64_TXPKTS_SHIFT             (0U)
#define ENET_RMON_T_P64_TXPKTS(x)                (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_P64_TXPKTS_SHIFT)) & ENET_RMON_T_P64_TXPKTS_MASK)

/*! @name RMON_T_P65TO127 - Tx 65- to 127-byte Packets Statistic Register */
#define ENET_RMON_T_P65TO127_TXPKTS_MASK         (0xFFFFU)
#define ENET_RMON_T_P65TO127_TXPKTS_SHIFT        (0U)
#define ENET_RMON_T_P65TO127_TXPKTS(x)           (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_P65TO127_TXPKTS_SHIFT)) & ENET_RMON_T_P65TO127_TXPKTS_MASK)

/*! @name RMON_T_P128TO255 - Tx 128- to 255-byte Packets Statistic Register */
#define ENET_RMON_T_P128TO255_TXPKTS_MASK        (0xFFFFU)
#define ENET_RMON_T_P128TO255_TXPKTS_SHIFT       (0U)
#define ENET_RMON_T_P128TO255_TXPKTS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_P128TO255_TXPKTS_SHIFT)) & ENET_RMON_T_P128TO255_TXPKTS_MASK)

/*! @name RMON_T_P256TO511 - Tx 256- to 511-byte Packets Statistic Register */
#define ENET_RMON_T_P256TO511_TXPKTS_MASK        (0xFFFFU)
#define ENET_RMON_T_P256TO511_TXPKTS_SHIFT       (0U)
#define ENET_RMON_T_P256TO511_TXPKTS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_P256TO511_TXPKTS_SHIFT)) & ENET_RMON_T_P256TO511_TXPKTS_MASK)

/*! @name RMON_T_P512TO1023 - Tx 512- to 1023-byte Packets Statistic Register */
#define ENET_RMON_T_P512TO1023_TXPKTS_MASK       (0xFFFFU)
#define ENET_RMON_T_P512TO1023_TXPKTS_SHIFT      (0U)
#define ENET_RMON_T_P512TO1023_TXPKTS(x)         (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_P512TO1023_TXPKTS_SHIFT)) & ENET_RMON_T_P512TO1023_TXPKTS_MASK)

/*! @name RMON_T_P1024TO2047 - Tx 1024- to 2047-byte Packets Statistic Register */
#define ENET_RMON_T_P1024TO2047_TXPKTS_MASK      (0xFFFFU)
#define ENET_RMON_T_P1024TO2047_TXPKTS_SHIFT     (0U)
#define ENET_RMON_T_P1024TO2047_TXPKTS(x)        (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_P1024TO2047_TXPKTS_SHIFT)) & ENET_RMON_T_P1024TO2047_TXPKTS_MASK)

/*! @name RMON_T_P_GTE2048 - Tx Packets Greater Than 2048 Bytes Statistic Register */
#define ENET_RMON_T_P_GTE2048_TXPKTS_MASK        (0xFFFFU)
#define ENET_RMON_T_P_GTE2048_TXPKTS_SHIFT       (0U)
#define ENET_RMON_T_P_GTE2048_TXPKTS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_P_GTE2048_TXPKTS_SHIFT)) & ENET_RMON_T_P_GTE2048_TXPKTS_MASK)

/*! @name RMON_T_OCTETS - Tx Octets Statistic Register */
#define ENET_RMON_T_OCTETS_TXOCTS_MASK           (0xFFFFFFFFU)
#define ENET_RMON_T_OCTETS_TXOCTS_SHIFT          (0U)
#define ENET_RMON_T_OCTETS_TXOCTS(x)             (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_OCTETS_TXOCTS_SHIFT)) & ENET_RMON_T_OCTETS_TXOCTS_MASK)

/*! @name IEEE_T_FRAME_OK - Frames Transmitted OK Statistic Register */
#define ENET_IEEE_T_FRAME_OK_COUNT_MASK          (0xFFFFU)
#define ENET_IEEE_T_FRAME_OK_COUNT_SHIFT         (0U)
#define ENET_IEEE_T_FRAME_OK_COUNT(x)            (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_FRAME_OK_COUNT_SHIFT)) & ENET_IEEE_T_FRAME_OK_COUNT_MASK)

/*! @name IEEE_T_1COL - Frames Transmitted with Single Collision Statistic Register */
#define ENET_IEEE_T_1COL_COUNT_MASK              (0xFFFFU)
#define ENET_IEEE_T_1COL_COUNT_SHIFT             (0U)
#define ENET_IEEE_T_1COL_COUNT(x)                (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_1COL_COUNT_SHIFT)) & ENET_IEEE_T_1COL_COUNT_MASK)

/*! @name IEEE_T_MCOL - Frames Transmitted with Multiple Collisions Statistic Register */
#define ENET_IEEE_T_MCOL_COUNT_MASK              (0xFFFFU)
#define ENET_IEEE_T_MCOL_COUNT_SHIFT             (0U)
#define ENET_IEEE_T_MCOL_COUNT(x)                (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_MCOL_COUNT_SHIFT)) & ENET_IEEE_T_MCOL_COUNT_MASK)

/*! @name IEEE_T_DEF - Frames Transmitted after Deferral Delay Statistic Register */
#define ENET_IEEE_T_DEF_COUNT_MASK               (0xFFFFU)
#define ENET_IEEE_T_DEF_COUNT_SHIFT              (0U)
#define ENET_IEEE_T_DEF_COUNT(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_DEF_COUNT_SHIFT)) & ENET_IEEE_T_DEF_COUNT_MASK)

/*! @name IEEE_T_LCOL - Frames Transmitted with Late Collision Statistic Register */
#define ENET_IEEE_T_LCOL_COUNT_MASK              (0xFFFFU)
#define ENET_IEEE_T_LCOL_COUNT_SHIFT             (0U)
#define ENET_IEEE_T_LCOL_COUNT(x)                (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_LCOL_COUNT_SHIFT)) & ENET_IEEE_T_LCOL_COUNT_MASK)

/*! @name IEEE_T_EXCOL - Frames Transmitted with Excessive Collisions Statistic Register */
#define ENET_IEEE_T_EXCOL_COUNT_MASK             (0xFFFFU)
#define ENET_IEEE_T_EXCOL_COUNT_SHIFT            (0U)
#define ENET_IEEE_T_EXCOL_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_EXCOL_COUNT_SHIFT)) & ENET_IEEE_T_EXCOL_COUNT_MASK)

/*! @name IEEE_T_MACERR - Frames Transmitted with Tx FIFO Underrun Statistic Register */
#define ENET_IEEE_T_MACERR_COUNT_MASK            (0xFFFFU)
#define ENET_IEEE_T_MACERR_COUNT_SHIFT           (0U)
#define ENET_IEEE_T_MACERR_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_MACERR_COUNT_SHIFT)) & ENET_IEEE_T_MACERR_COUNT_MASK)

/*! @name IEEE_T_CSERR - Frames Transmitted with Carrier Sense Error Statistic Register */
#define ENET_IEEE_T_CSERR_COUNT_MASK             (0xFFFFU)
#define ENET_IEEE_T_CSERR_COUNT_SHIFT            (0U)
#define ENET_IEEE_T_CSERR_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_CSERR_COUNT_SHIFT)) & ENET_IEEE_T_CSERR_COUNT_MASK)

/*! @name IEEE_T_SQE - Reserved Statistic Register */
#define ENET_IEEE_T_SQE_COUNT_MASK               (0xFFFFU)
#define ENET_IEEE_T_SQE_COUNT_SHIFT              (0U)
#define ENET_IEEE_T_SQE_COUNT(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_SQE_COUNT_SHIFT)) & ENET_IEEE_T_SQE_COUNT_MASK)

/*! @name IEEE_T_FDXFC - Flow Control Pause Frames Transmitted Statistic Register */
#define ENET_IEEE_T_FDXFC_COUNT_MASK             (0xFFFFU)
#define ENET_IEEE_T_FDXFC_COUNT_SHIFT            (0U)
#define ENET_IEEE_T_FDXFC_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_FDXFC_COUNT_SHIFT)) & ENET_IEEE_T_FDXFC_COUNT_MASK)

/*! @name IEEE_T_OCTETS_OK - Octet Count for Frames Transmitted w/o Error Statistic Register */
#define ENET_IEEE_T_OCTETS_OK_COUNT_MASK         (0xFFFFFFFFU)
#define ENET_IEEE_T_OCTETS_OK_COUNT_SHIFT        (0U)
#define ENET_IEEE_T_OCTETS_OK_COUNT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_OCTETS_OK_COUNT_SHIFT)) & ENET_IEEE_T_OCTETS_OK_COUNT_MASK)

/*! @name RMON_R_PACKETS - Rx Packet Count Statistic Register */
#define ENET_RMON_R_PACKETS_COUNT_MASK           (0xFFFFU)
#define ENET_RMON_R_PACKETS_COUNT_SHIFT          (0U)
#define ENET_RMON_R_PACKETS_COUNT(x)             (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_PACKETS_COUNT_SHIFT)) & ENET_RMON_R_PACKETS_COUNT_MASK)

/*! @name RMON_R_BC_PKT - Rx Broadcast Packets Statistic Register */
#define ENET_RMON_R_BC_PKT_COUNT_MASK            (0xFFFFU)
#define ENET_RMON_R_BC_PKT_COUNT_SHIFT           (0U)
#define ENET_RMON_R_BC_PKT_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_BC_PKT_COUNT_SHIFT)) & ENET_RMON_R_BC_PKT_COUNT_MASK)

/*! @name RMON_R_MC_PKT - Rx Multicast Packets Statistic Register */
#define ENET_RMON_R_MC_PKT_COUNT_MASK            (0xFFFFU)
#define ENET_RMON_R_MC_PKT_COUNT_SHIFT           (0U)
#define ENET_RMON_R_MC_PKT_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_MC_PKT_COUNT_SHIFT)) & ENET_RMON_R_MC_PKT_COUNT_MASK)

/*! @name RMON_R_CRC_ALIGN - Rx Packets with CRC/Align Error Statistic Register */
#define ENET_RMON_R_CRC_ALIGN_COUNT_MASK         (0xFFFFU)
#define ENET_RMON_R_CRC_ALIGN_COUNT_SHIFT        (0U)
#define ENET_RMON_R_CRC_ALIGN_COUNT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_CRC_ALIGN_COUNT_SHIFT)) & ENET_RMON_R_CRC_ALIGN_COUNT_MASK)

/*! @name RMON_R_UNDERSIZE - Rx Packets with Less Than 64 Bytes and Good CRC Statistic Register */
#define ENET_RMON_R_UNDERSIZE_COUNT_MASK         (0xFFFFU)
#define ENET_RMON_R_UNDERSIZE_COUNT_SHIFT        (0U)
#define ENET_RMON_R_UNDERSIZE_COUNT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_UNDERSIZE_COUNT_SHIFT)) & ENET_RMON_R_UNDERSIZE_COUNT_MASK)

/*! @name RMON_R_OVERSIZE - Rx Packets Greater Than MAX_FL and Good CRC Statistic Register */
#define ENET_RMON_R_OVERSIZE_COUNT_MASK          (0xFFFFU)
#define ENET_RMON_R_OVERSIZE_COUNT_SHIFT         (0U)
#define ENET_RMON_R_OVERSIZE_COUNT(x)            (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_OVERSIZE_COUNT_SHIFT)) & ENET_RMON_R_OVERSIZE_COUNT_MASK)

/*! @name RMON_R_FRAG - Rx Packets Less Than 64 Bytes and Bad CRC Statistic Register */
#define ENET_RMON_R_FRAG_COUNT_MASK              (0xFFFFU)
#define ENET_RMON_R_FRAG_COUNT_SHIFT             (0U)
#define ENET_RMON_R_FRAG_COUNT(x)                (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_FRAG_COUNT_SHIFT)) & ENET_RMON_R_FRAG_COUNT_MASK)

/*! @name RMON_R_JAB - Rx Packets Greater Than MAX_FL Bytes and Bad CRC Statistic Register */
#define ENET_RMON_R_JAB_COUNT_MASK               (0xFFFFU)
#define ENET_RMON_R_JAB_COUNT_SHIFT              (0U)
#define ENET_RMON_R_JAB_COUNT(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_JAB_COUNT_SHIFT)) & ENET_RMON_R_JAB_COUNT_MASK)

/*! @name RMON_R_P64 - Rx 64-Byte Packets Statistic Register */
#define ENET_RMON_R_P64_COUNT_MASK               (0xFFFFU)
#define ENET_RMON_R_P64_COUNT_SHIFT              (0U)
#define ENET_RMON_R_P64_COUNT(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_P64_COUNT_SHIFT)) & ENET_RMON_R_P64_COUNT_MASK)

/*! @name RMON_R_P65TO127 - Rx 65- to 127-Byte Packets Statistic Register */
#define ENET_RMON_R_P65TO127_COUNT_MASK          (0xFFFFU)
#define ENET_RMON_R_P65TO127_COUNT_SHIFT         (0U)
#define ENET_RMON_R_P65TO127_COUNT(x)            (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_P65TO127_COUNT_SHIFT)) & ENET_RMON_R_P65TO127_COUNT_MASK)

/*! @name RMON_R_P128TO255 - Rx 128- to 255-Byte Packets Statistic Register */
#define ENET_RMON_R_P128TO255_COUNT_MASK         (0xFFFFU)
#define ENET_RMON_R_P128TO255_COUNT_SHIFT        (0U)
#define ENET_RMON_R_P128TO255_COUNT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_P128TO255_COUNT_SHIFT)) & ENET_RMON_R_P128TO255_COUNT_MASK)

/*! @name RMON_R_P256TO511 - Rx 256- to 511-Byte Packets Statistic Register */
#define ENET_RMON_R_P256TO511_COUNT_MASK         (0xFFFFU)
#define ENET_RMON_R_P256TO511_COUNT_SHIFT        (0U)
#define ENET_RMON_R_P256TO511_COUNT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_P256TO511_COUNT_SHIFT)) & ENET_RMON_R_P256TO511_COUNT_MASK)

/*! @name RMON_R_P512TO1023 - Rx 512- to 1023-Byte Packets Statistic Register */
#define ENET_RMON_R_P512TO1023_COUNT_MASK        (0xFFFFU)
#define ENET_RMON_R_P512TO1023_COUNT_SHIFT       (0U)
#define ENET_RMON_R_P512TO1023_COUNT(x)          (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_P512TO1023_COUNT_SHIFT)) & ENET_RMON_R_P512TO1023_COUNT_MASK)

/*! @name RMON_R_P1024TO2047 - Rx 1024- to 2047-Byte Packets Statistic Register */
#define ENET_RMON_R_P1024TO2047_COUNT_MASK       (0xFFFFU)
#define ENET_RMON_R_P1024TO2047_COUNT_SHIFT      (0U)
#define ENET_RMON_R_P1024TO2047_COUNT(x)         (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_P1024TO2047_COUNT_SHIFT)) & ENET_RMON_R_P1024TO2047_COUNT_MASK)

/*! @name RMON_R_P_GTE2048 - Rx Packets Greater than 2048 Bytes Statistic Register */
#define ENET_RMON_R_P_GTE2048_COUNT_MASK         (0xFFFFU)
#define ENET_RMON_R_P_GTE2048_COUNT_SHIFT        (0U)
#define ENET_RMON_R_P_GTE2048_COUNT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_P_GTE2048_COUNT_SHIFT)) & ENET_RMON_R_P_GTE2048_COUNT_MASK)

/*! @name RMON_R_OCTETS - Rx Octets Statistic Register */
#define ENET_RMON_R_OCTETS_COUNT_MASK            (0xFFFFFFFFU)
#define ENET_RMON_R_OCTETS_COUNT_SHIFT           (0U)
#define ENET_RMON_R_OCTETS_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_OCTETS_COUNT_SHIFT)) & ENET_RMON_R_OCTETS_COUNT_MASK)

/*! @name IEEE_R_DROP - Frames not Counted Correctly Statistic Register */
#define ENET_IEEE_R_DROP_COUNT_MASK              (0xFFFFU)
#define ENET_IEEE_R_DROP_COUNT_SHIFT             (0U)
#define ENET_IEEE_R_DROP_COUNT(x)                (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_R_DROP_COUNT_SHIFT)) & ENET_IEEE_R_DROP_COUNT_MASK)

/*! @name IEEE_R_FRAME_OK - Frames Received OK Statistic Register */
#define ENET_IEEE_R_FRAME_OK_COUNT_MASK          (0xFFFFU)
#define ENET_IEEE_R_FRAME_OK_COUNT_SHIFT         (0U)
#define ENET_IEEE_R_FRAME_OK_COUNT(x)            (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_R_FRAME_OK_COUNT_SHIFT)) & ENET_IEEE_R_FRAME_OK_COUNT_MASK)

/*! @name IEEE_R_CRC - Frames Received with CRC Error Statistic Register */
#define ENET_IEEE_R_CRC_COUNT_MASK               (0xFFFFU)
#define ENET_IEEE_R_CRC_COUNT_SHIFT              (0U)
#define ENET_IEEE_R_CRC_COUNT(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_R_CRC_COUNT_SHIFT)) & ENET_IEEE_R_CRC_COUNT_MASK)

/*! @name IEEE_R_ALIGN - Frames Received with Alignment Error Statistic Register */
#define ENET_IEEE_R_ALIGN_COUNT_MASK             (0xFFFFU)
#define ENET_IEEE_R_ALIGN_COUNT_SHIFT            (0U)
#define ENET_IEEE_R_ALIGN_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_R_ALIGN_COUNT_SHIFT)) & ENET_IEEE_R_ALIGN_COUNT_MASK)

/*! @name IEEE_R_MACERR - Receive FIFO Overflow Count Statistic Register */
#define ENET_IEEE_R_MACERR_COUNT_MASK            (0xFFFFU)
#define ENET_IEEE_R_MACERR_COUNT_SHIFT           (0U)
#define ENET_IEEE_R_MACERR_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_R_MACERR_COUNT_SHIFT)) & ENET_IEEE_R_MACERR_COUNT_MASK)

/*! @name IEEE_R_FDXFC - Flow Control Pause Frames Received Statistic Register */
#define ENET_IEEE_R_FDXFC_COUNT_MASK             (0xFFFFU)
#define ENET_IEEE_R_FDXFC_COUNT_SHIFT            (0U)
#define ENET_IEEE_R_FDXFC_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_R_FDXFC_COUNT_SHIFT)) & ENET_IEEE_R_FDXFC_COUNT_MASK)

/*! @name IEEE_R_OCTETS_OK - Octet Count for Frames Received without Error Statistic Register */
#define ENET_IEEE_R_OCTETS_OK_COUNT_MASK         (0xFFFFFFFFU)
#define ENET_IEEE_R_OCTETS_OK_COUNT_SHIFT        (0U)
#define ENET_IEEE_R_OCTETS_OK_COUNT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_R_OCTETS_OK_COUNT_SHIFT)) & ENET_IEEE_R_OCTETS_OK_COUNT_MASK)

/*! @name ATCR - Adjustable Timer Control Register */
#define ENET_ATCR_EN_MASK                        (0x1U)
#define ENET_ATCR_EN_SHIFT                       (0U)
#define ENET_ATCR_EN(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_ATCR_EN_SHIFT)) & ENET_ATCR_EN_MASK)
#define ENET_ATCR_OFFEN_MASK                     (0x4U)
#define ENET_ATCR_OFFEN_SHIFT                    (2U)
#define ENET_ATCR_OFFEN(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_ATCR_OFFEN_SHIFT)) & ENET_ATCR_OFFEN_MASK)
#define ENET_ATCR_OFFRST_MASK                    (0x8U)
#define ENET_ATCR_OFFRST_SHIFT                   (3U)
#define ENET_ATCR_OFFRST(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_ATCR_OFFRST_SHIFT)) & ENET_ATCR_OFFRST_MASK)
#define ENET_ATCR_PEREN_MASK                     (0x10U)
#define ENET_ATCR_PEREN_SHIFT                    (4U)
#define ENET_ATCR_PEREN(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_ATCR_PEREN_SHIFT)) & ENET_ATCR_PEREN_MASK)
#define ENET_ATCR_PINPER_MASK                    (0x80U)
#define ENET_ATCR_PINPER_SHIFT                   (7U)
#define ENET_ATCR_PINPER(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_ATCR_PINPER_SHIFT)) & ENET_ATCR_PINPER_MASK)
#define ENET_ATCR_RESTART_MASK                   (0x200U)
#define ENET_ATCR_RESTART_SHIFT                  (9U)
#define ENET_ATCR_RESTART(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_ATCR_RESTART_SHIFT)) & ENET_ATCR_RESTART_MASK)
#define ENET_ATCR_CAPTURE_MASK                   (0x800U)
#define ENET_ATCR_CAPTURE_SHIFT                  (11U)
#define ENET_ATCR_CAPTURE(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_ATCR_CAPTURE_SHIFT)) & ENET_ATCR_CAPTURE_MASK)
#define ENET_ATCR_SLAVE_MASK                     (0x2000U)
#define ENET_ATCR_SLAVE_SHIFT                    (13U)
#define ENET_ATCR_SLAVE(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_ATCR_SLAVE_SHIFT)) & ENET_ATCR_SLAVE_MASK)

/*! @name ATVR - Timer Value Register */
#define ENET_ATVR_ATIME_MASK                     (0xFFFFFFFFU)
#define ENET_ATVR_ATIME_SHIFT                    (0U)
#define ENET_ATVR_ATIME(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_ATVR_ATIME_SHIFT)) & ENET_ATVR_ATIME_MASK)

/*! @name ATOFF - Timer Offset Register */
#define ENET_ATOFF_OFFSET_MASK                   (0xFFFFFFFFU)
#define ENET_ATOFF_OFFSET_SHIFT                  (0U)
#define ENET_ATOFF_OFFSET(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_ATOFF_OFFSET_SHIFT)) & ENET_ATOFF_OFFSET_MASK)

/*! @name ATPER - Timer Period Register */
#define ENET_ATPER_PERIOD_MASK                   (0xFFFFFFFFU)
#define ENET_ATPER_PERIOD_SHIFT                  (0U)
#define ENET_ATPER_PERIOD(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_ATPER_PERIOD_SHIFT)) & ENET_ATPER_PERIOD_MASK)

/*! @name ATCOR - Timer Correction Register */
#define ENET_ATCOR_COR_MASK                      (0x7FFFFFFFU)
#define ENET_ATCOR_COR_SHIFT                     (0U)
#define ENET_ATCOR_COR(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_ATCOR_COR_SHIFT)) & ENET_ATCOR_COR_MASK)

/*! @name ATINC - Time-Stamping Clock Period Register */
#define ENET_ATINC_INC_MASK                      (0x7FU)
#define ENET_ATINC_INC_SHIFT                     (0U)
#define ENET_ATINC_INC(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_ATINC_INC_SHIFT)) & ENET_ATINC_INC_MASK)
#define ENET_ATINC_INC_CORR_MASK                 (0x7F00U)
#define ENET_ATINC_INC_CORR_SHIFT                (8U)
#define ENET_ATINC_INC_CORR(x)                   (((uint32_t)(((uint32_t)(x)) << ENET_ATINC_INC_CORR_SHIFT)) & ENET_ATINC_INC_CORR_MASK)

/*! @name ATSTMP - Timestamp of Last Transmitted Frame */
#define ENET_ATSTMP_TIMESTAMP_MASK               (0xFFFFFFFFU)
#define ENET_ATSTMP_TIMESTAMP_SHIFT              (0U)
#define ENET_ATSTMP_TIMESTAMP(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_ATSTMP_TIMESTAMP_SHIFT)) & ENET_ATSTMP_TIMESTAMP_MASK)

/*! @name TGSR - Timer Global Status Register */
#define ENET_TGSR_TF0_MASK                       (0x1U)
#define ENET_TGSR_TF0_SHIFT                      (0U)
#define ENET_TGSR_TF0(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_TGSR_TF0_SHIFT)) & ENET_TGSR_TF0_MASK)
#define ENET_TGSR_TF1_MASK                       (0x2U)
#define ENET_TGSR_TF1_SHIFT                      (1U)
#define ENET_TGSR_TF1(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_TGSR_TF1_SHIFT)) & ENET_TGSR_TF1_MASK)
#define ENET_TGSR_TF2_MASK                       (0x4U)
#define ENET_TGSR_TF2_SHIFT                      (2U)
#define ENET_TGSR_TF2(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_TGSR_TF2_SHIFT)) & ENET_TGSR_TF2_MASK)
#define ENET_TGSR_TF3_MASK                       (0x8U)
#define ENET_TGSR_TF3_SHIFT                      (3U)
#define ENET_TGSR_TF3(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_TGSR_TF3_SHIFT)) & ENET_TGSR_TF3_MASK)

/*! @name TCSR - Timer Control Status Register */
#define ENET_TCSR_TDRE_MASK                      (0x1U)
#define ENET_TCSR_TDRE_SHIFT                     (0U)
#define ENET_TCSR_TDRE(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_TCSR_TDRE_SHIFT)) & ENET_TCSR_TDRE_MASK)
#define ENET_TCSR_TMODE_MASK                     (0x3CU)
#define ENET_TCSR_TMODE_SHIFT                    (2U)
#define ENET_TCSR_TMODE(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_TCSR_TMODE_SHIFT)) & ENET_TCSR_TMODE_MASK)
#define ENET_TCSR_TIE_MASK                       (0x40U)
#define ENET_TCSR_TIE_SHIFT                      (6U)
#define ENET_TCSR_TIE(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_TCSR_TIE_SHIFT)) & ENET_TCSR_TIE_MASK)
#define ENET_TCSR_TF_MASK                        (0x80U)
#define ENET_TCSR_TF_SHIFT                       (7U)
#define ENET_TCSR_TF(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_TCSR_TF_SHIFT)) & ENET_TCSR_TF_MASK)

/* The count of ENET_TCSR */
#define ENET_TCSR_COUNT                          (4U)

/*! @name TCCR - Timer Compare Capture Register */
#define ENET_TCCR_TCC_MASK                       (0xFFFFFFFFU)
#define ENET_TCCR_TCC_SHIFT                      (0U)
#define ENET_TCCR_TCC(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_TCCR_TCC_SHIFT)) & ENET_TCCR_TCC_MASK)

/* The count of ENET_TCCR */
#define ENET_TCCR_COUNT                          (4U)


/*!
 * @}
 */ /* end of group ENET_Register_Masks */


/* ENET - Peripheral instance base addresses */
/** Peripheral ENET base address */
#define ENET_BASE                                (0x400C0000u)
/** Peripheral ENET base pointer */
#define ENET                                     ((ENET_Type *)ENET_BASE)
/** Array initializer of ENET peripheral base addresses */
#define ENET_BASE_ADDRS                          { ENET_BASE }
/** Array initializer of ENET peripheral base pointers */
#define ENET_BASE_PTRS                           { ENET }
/** Interrupt vectors for the ENET peripheral type */
#define ENET_Transmit_IRQS                       { ENET_Transmit_IRQn }
#define ENET_Receive_IRQS                        { ENET_Receive_IRQn }
#define ENET_Error_IRQS                          { ENET_Error_IRQn }
#define ENET_1588_Timer_IRQS                     { ENET_1588_Timer_IRQn }

/*!
 * @}
 */ /* end of group ENET_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- EWM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EWM_Peripheral_Access_Layer EWM Peripheral Access Layer
 * @{
 */

/** EWM - Register Layout Typedef */
typedef struct {
  __IO uint8_t CTRL;                               /**< Control Register, offset: 0x0 */
  __O  uint8_t SERV;                               /**< Service Register, offset: 0x1 */
  __IO uint8_t CMPL;                               /**< Compare Low Register, offset: 0x2 */
  __IO uint8_t CMPH;                               /**< Compare High Register, offset: 0x3 */
  __IO uint8_t CLKCTRL;                            /**< Clock Control Register, offset: 0x4 */
  __IO uint8_t CLKPRESCALER;                       /**< Clock Prescaler Register, offset: 0x5 */
} EWM_Type;

/* ----------------------------------------------------------------------------
   -- EWM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EWM_Register_Masks EWM Register Masks
 * @{
 */

/*! @name CTRL - Control Register */
#define EWM_CTRL_EWMEN_MASK                      (0x1U)
#define EWM_CTRL_EWMEN_SHIFT                     (0U)
#define EWM_CTRL_EWMEN(x)                        (((uint8_t)(((uint8_t)(x)) << EWM_CTRL_EWMEN_SHIFT)) & EWM_CTRL_EWMEN_MASK)
#define EWM_CTRL_ASSIN_MASK                      (0x2U)
#define EWM_CTRL_ASSIN_SHIFT                     (1U)
#define EWM_CTRL_ASSIN(x)                        (((uint8_t)(((uint8_t)(x)) << EWM_CTRL_ASSIN_SHIFT)) & EWM_CTRL_ASSIN_MASK)
#define EWM_CTRL_INEN_MASK                       (0x4U)
#define EWM_CTRL_INEN_SHIFT                      (2U)
#define EWM_CTRL_INEN(x)                         (((uint8_t)(((uint8_t)(x)) << EWM_CTRL_INEN_SHIFT)) & EWM_CTRL_INEN_MASK)
#define EWM_CTRL_INTEN_MASK                      (0x8U)
#define EWM_CTRL_INTEN_SHIFT                     (3U)
#define EWM_CTRL_INTEN(x)                        (((uint8_t)(((uint8_t)(x)) << EWM_CTRL_INTEN_SHIFT)) & EWM_CTRL_INTEN_MASK)

/*! @name SERV - Service Register */
#define EWM_SERV_SERVICE_MASK                    (0xFFU)
#define EWM_SERV_SERVICE_SHIFT                   (0U)
#define EWM_SERV_SERVICE(x)                      (((uint8_t)(((uint8_t)(x)) << EWM_SERV_SERVICE_SHIFT)) & EWM_SERV_SERVICE_MASK)

/*! @name CMPL - Compare Low Register */
#define EWM_CMPL_COMPAREL_MASK                   (0xFFU)
#define EWM_CMPL_COMPAREL_SHIFT                  (0U)
#define EWM_CMPL_COMPAREL(x)                     (((uint8_t)(((uint8_t)(x)) << EWM_CMPL_COMPAREL_SHIFT)) & EWM_CMPL_COMPAREL_MASK)

/*! @name CMPH - Compare High Register */
#define EWM_CMPH_COMPAREH_MASK                   (0xFFU)
#define EWM_CMPH_COMPAREH_SHIFT                  (0U)
#define EWM_CMPH_COMPAREH(x)                     (((uint8_t)(((uint8_t)(x)) << EWM_CMPH_COMPAREH_SHIFT)) & EWM_CMPH_COMPAREH_MASK)

/*! @name CLKCTRL - Clock Control Register */
#define EWM_CLKCTRL_CLKSEL_MASK                  (0x3U)
#define EWM_CLKCTRL_CLKSEL_SHIFT                 (0U)
#define EWM_CLKCTRL_CLKSEL(x)                    (((uint8_t)(((uint8_t)(x)) << EWM_CLKCTRL_CLKSEL_SHIFT)) & EWM_CLKCTRL_CLKSEL_MASK)

/*! @name CLKPRESCALER - Clock Prescaler Register */
#define EWM_CLKPRESCALER_CLK_DIV_MASK            (0xFFU)
#define EWM_CLKPRESCALER_CLK_DIV_SHIFT           (0U)
#define EWM_CLKPRESCALER_CLK_DIV(x)              (((uint8_t)(((uint8_t)(x)) << EWM_CLKPRESCALER_CLK_DIV_SHIFT)) & EWM_CLKPRESCALER_CLK_DIV_MASK)


/*!
 * @}
 */ /* end of group EWM_Register_Masks */


/* EWM - Peripheral instance base addresses */
/** Peripheral EWM base address */
#define EWM_BASE                                 (0x40061000u)
/** Peripheral EWM base pointer */
#define EWM                                      ((EWM_Type *)EWM_BASE)
/** Array initializer of EWM peripheral base addresses */
#define EWM_BASE_ADDRS                           { EWM_BASE }
/** Array initializer of EWM peripheral base pointers */
#define EWM_BASE_PTRS                            { EWM }
/** Interrupt vectors for the EWM peripheral type */
#define EWM_IRQS                                 { WDOG_EWM_IRQn }

/*!
 * @}
 */ /* end of group EWM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- FB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FB_Peripheral_Access_Layer FB Peripheral Access Layer
 * @{
 */

/** FB - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0xC */
    __IO uint32_t CSAR;                              /**< Chip Select Address Register, array offset: 0x0, array step: 0xC */
    __IO uint32_t CSMR;                              /**< Chip Select Mask Register, array offset: 0x4, array step: 0xC */
    __IO uint32_t CSCR;                              /**< Chip Select Control Register, array offset: 0x8, array step: 0xC */
  } CS[6];
       uint8_t RESERVED_0[24];
  __IO uint32_t CSPMCR;                            /**< Chip Select port Multiplexing Control Register, offset: 0x60 */
} FB_Type;

/* ----------------------------------------------------------------------------
   -- FB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FB_Register_Masks FB Register Masks
 * @{
 */

/*! @name CSAR - Chip Select Address Register */
#define FB_CSAR_BA_MASK                          (0xFFFF0000U)
#define FB_CSAR_BA_SHIFT                         (16U)
#define FB_CSAR_BA(x)                            (((uint32_t)(((uint32_t)(x)) << FB_CSAR_BA_SHIFT)) & FB_CSAR_BA_MASK)

/* The count of FB_CSAR */
#define FB_CSAR_COUNT                            (6U)

/*! @name CSMR - Chip Select Mask Register */
#define FB_CSMR_V_MASK                           (0x1U)
#define FB_CSMR_V_SHIFT                          (0U)
#define FB_CSMR_V(x)                             (((uint32_t)(((uint32_t)(x)) << FB_CSMR_V_SHIFT)) & FB_CSMR_V_MASK)
#define FB_CSMR_WP_MASK                          (0x100U)
#define FB_CSMR_WP_SHIFT                         (8U)
#define FB_CSMR_WP(x)                            (((uint32_t)(((uint32_t)(x)) << FB_CSMR_WP_SHIFT)) & FB_CSMR_WP_MASK)
#define FB_CSMR_BAM_MASK                         (0xFFFF0000U)
#define FB_CSMR_BAM_SHIFT                        (16U)
#define FB_CSMR_BAM(x)                           (((uint32_t)(((uint32_t)(x)) << FB_CSMR_BAM_SHIFT)) & FB_CSMR_BAM_MASK)

/* The count of FB_CSMR */
#define FB_CSMR_COUNT                            (6U)

/*! @name CSCR - Chip Select Control Register */
#define FB_CSCR_BSTW_MASK                        (0x8U)
#define FB_CSCR_BSTW_SHIFT                       (3U)
#define FB_CSCR_BSTW(x)                          (((uint32_t)(((uint32_t)(x)) << FB_CSCR_BSTW_SHIFT)) & FB_CSCR_BSTW_MASK)
#define FB_CSCR_BSTR_MASK                        (0x10U)
#define FB_CSCR_BSTR_SHIFT                       (4U)
#define FB_CSCR_BSTR(x)                          (((uint32_t)(((uint32_t)(x)) << FB_CSCR_BSTR_SHIFT)) & FB_CSCR_BSTR_MASK)
#define FB_CSCR_BEM_MASK                         (0x20U)
#define FB_CSCR_BEM_SHIFT                        (5U)
#define FB_CSCR_BEM(x)                           (((uint32_t)(((uint32_t)(x)) << FB_CSCR_BEM_SHIFT)) & FB_CSCR_BEM_MASK)
#define FB_CSCR_PS_MASK                          (0xC0U)
#define FB_CSCR_PS_SHIFT                         (6U)
#define FB_CSCR_PS(x)                            (((uint32_t)(((uint32_t)(x)) << FB_CSCR_PS_SHIFT)) & FB_CSCR_PS_MASK)
#define FB_CSCR_AA_MASK                          (0x100U)
#define FB_CSCR_AA_SHIFT                         (8U)
#define FB_CSCR_AA(x)                            (((uint32_t)(((uint32_t)(x)) << FB_CSCR_AA_SHIFT)) & FB_CSCR_AA_MASK)
#define FB_CSCR_BLS_MASK                         (0x200U)
#define FB_CSCR_BLS_SHIFT                        (9U)
#define FB_CSCR_BLS(x)                           (((uint32_t)(((uint32_t)(x)) << FB_CSCR_BLS_SHIFT)) & FB_CSCR_BLS_MASK)
#define FB_CSCR_WS_MASK                          (0xFC00U)
#define FB_CSCR_WS_SHIFT                         (10U)
#define FB_CSCR_WS(x)                            (((uint32_t)(((uint32_t)(x)) << FB_CSCR_WS_SHIFT)) & FB_CSCR_WS_MASK)
#define FB_CSCR_WRAH_MASK                        (0x30000U)
#define FB_CSCR_WRAH_SHIFT                       (16U)
#define FB_CSCR_WRAH(x)                          (((uint32_t)(((uint32_t)(x)) << FB_CSCR_WRAH_SHIFT)) & FB_CSCR_WRAH_MASK)
#define FB_CSCR_RDAH_MASK                        (0xC0000U)
#define FB_CSCR_RDAH_SHIFT                       (18U)
#define FB_CSCR_RDAH(x)                          (((uint32_t)(((uint32_t)(x)) << FB_CSCR_RDAH_SHIFT)) & FB_CSCR_RDAH_MASK)
#define FB_CSCR_ASET_MASK                        (0x300000U)
#define FB_CSCR_ASET_SHIFT                       (20U)
#define FB_CSCR_ASET(x)                          (((uint32_t)(((uint32_t)(x)) << FB_CSCR_ASET_SHIFT)) & FB_CSCR_ASET_MASK)
#define FB_CSCR_EXTS_MASK                        (0x400000U)
#define FB_CSCR_EXTS_SHIFT                       (22U)
#define FB_CSCR_EXTS(x)                          (((uint32_t)(((uint32_t)(x)) << FB_CSCR_EXTS_SHIFT)) & FB_CSCR_EXTS_MASK)
#define FB_CSCR_SWSEN_MASK                       (0x800000U)
#define FB_CSCR_SWSEN_SHIFT                      (23U)
#define FB_CSCR_SWSEN(x)                         (((uint32_t)(((uint32_t)(x)) << FB_CSCR_SWSEN_SHIFT)) & FB_CSCR_SWSEN_MASK)
#define FB_CSCR_SWS_MASK                         (0xFC000000U)
#define FB_CSCR_SWS_SHIFT                        (26U)
#define FB_CSCR_SWS(x)                           (((uint32_t)(((uint32_t)(x)) << FB_CSCR_SWS_SHIFT)) & FB_CSCR_SWS_MASK)

/* The count of FB_CSCR */
#define FB_CSCR_COUNT                            (6U)

/*! @name CSPMCR - Chip Select port Multiplexing Control Register */
#define FB_CSPMCR_GROUP5_MASK                    (0xF000U)
#define FB_CSPMCR_GROUP5_SHIFT                   (12U)
#define FB_CSPMCR_GROUP5(x)                      (((uint32_t)(((uint32_t)(x)) << FB_CSPMCR_GROUP5_SHIFT)) & FB_CSPMCR_GROUP5_MASK)
#define FB_CSPMCR_GROUP4_MASK                    (0xF0000U)
#define FB_CSPMCR_GROUP4_SHIFT                   (16U)
#define FB_CSPMCR_GROUP4(x)                      (((uint32_t)(((uint32_t)(x)) << FB_CSPMCR_GROUP4_SHIFT)) & FB_CSPMCR_GROUP4_MASK)
#define FB_CSPMCR_GROUP3_MASK                    (0xF00000U)
#define FB_CSPMCR_GROUP3_SHIFT                   (20U)
#define FB_CSPMCR_GROUP3(x)                      (((uint32_t)(((uint32_t)(x)) << FB_CSPMCR_GROUP3_SHIFT)) & FB_CSPMCR_GROUP3_MASK)
#define FB_CSPMCR_GROUP2_MASK                    (0xF000000U)
#define FB_CSPMCR_GROUP2_SHIFT                   (24U)
#define FB_CSPMCR_GROUP2(x)                      (((uint32_t)(((uint32_t)(x)) << FB_CSPMCR_GROUP2_SHIFT)) & FB_CSPMCR_GROUP2_MASK)
#define FB_CSPMCR_GROUP1_MASK                    (0xF0000000U)
#define FB_CSPMCR_GROUP1_SHIFT                   (28U)
#define FB_CSPMCR_GROUP1(x)                      (((uint32_t)(((uint32_t)(x)) << FB_CSPMCR_GROUP1_SHIFT)) & FB_CSPMCR_GROUP1_MASK)


/*!
 * @}
 */ /* end of group FB_Register_Masks */


/* FB - Peripheral instance base addresses */
/** Peripheral FB base address */
#define FB_BASE                                  (0x4000C000u)
/** Peripheral FB base pointer */
#define FB                                       ((FB_Type *)FB_BASE)
/** Array initializer of FB peripheral base addresses */
#define FB_BASE_ADDRS                            { FB_BASE }
/** Array initializer of FB peripheral base pointers */
#define FB_BASE_PTRS                             { FB }

/*!
 * @}
 */ /* end of group FB_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- FMC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FMC_Peripheral_Access_Layer FMC Peripheral Access Layer
 * @{
 */

/** FMC - Register Layout Typedef */
typedef struct {
  __IO uint32_t PFAPR;                             /**< Flash Access Protection Register, offset: 0x0 */
  __IO uint32_t PFB0CR;                            /**< Flash Bank 0 Control Register, offset: 0x4 */
} FMC_Type;

/* ----------------------------------------------------------------------------
   -- FMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FMC_Register_Masks FMC Register Masks
 * @{
 */

/*! @name PFAPR - Flash Access Protection Register */
#define FMC_PFAPR_M0AP_MASK                      (0x3U)
#define FMC_PFAPR_M0AP_SHIFT                     (0U)
#define FMC_PFAPR_M0AP(x)                        (((uint32_t)(((uint32_t)(x)) << FMC_PFAPR_M0AP_SHIFT)) & FMC_PFAPR_M0AP_MASK)
#define FMC_PFAPR_M1AP_MASK                      (0xCU)
#define FMC_PFAPR_M1AP_SHIFT                     (2U)
#define FMC_PFAPR_M1AP(x)                        (((uint32_t)(((uint32_t)(x)) << FMC_PFAPR_M1AP_SHIFT)) & FMC_PFAPR_M1AP_MASK)
#define FMC_PFAPR_M2AP_MASK                      (0x30U)
#define FMC_PFAPR_M2AP_SHIFT                     (4U)
#define FMC_PFAPR_M2AP(x)                        (((uint32_t)(((uint32_t)(x)) << FMC_PFAPR_M2AP_SHIFT)) & FMC_PFAPR_M2AP_MASK)
#define FMC_PFAPR_M3AP_MASK                      (0xC0U)
#define FMC_PFAPR_M3AP_SHIFT                     (6U)
#define FMC_PFAPR_M3AP(x)                        (((uint32_t)(((uint32_t)(x)) << FMC_PFAPR_M3AP_SHIFT)) & FMC_PFAPR_M3AP_MASK)
#define FMC_PFAPR_M0PFD_MASK                     (0x10000U)
#define FMC_PFAPR_M0PFD_SHIFT                    (16U)
#define FMC_PFAPR_M0PFD(x)                       (((uint32_t)(((uint32_t)(x)) << FMC_PFAPR_M0PFD_SHIFT)) & FMC_PFAPR_M0PFD_MASK)
#define FMC_PFAPR_M1PFD_MASK                     (0x20000U)
#define FMC_PFAPR_M1PFD_SHIFT                    (17U)
#define FMC_PFAPR_M1PFD(x)                       (((uint32_t)(((uint32_t)(x)) << FMC_PFAPR_M1PFD_SHIFT)) & FMC_PFAPR_M1PFD_MASK)
#define FMC_PFAPR_M2PFD_MASK                     (0x40000U)
#define FMC_PFAPR_M2PFD_SHIFT                    (18U)
#define FMC_PFAPR_M2PFD(x)                       (((uint32_t)(((uint32_t)(x)) << FMC_PFAPR_M2PFD_SHIFT)) & FMC_PFAPR_M2PFD_MASK)
#define FMC_PFAPR_M3PFD_MASK                     (0x80000U)
#define FMC_PFAPR_M3PFD_SHIFT                    (19U)
#define FMC_PFAPR_M3PFD(x)                       (((uint32_t)(((uint32_t)(x)) << FMC_PFAPR_M3PFD_SHIFT)) & FMC_PFAPR_M3PFD_MASK)

/*! @name PFB0CR - Flash Bank 0 Control Register */
#define FMC_PFB0CR_B0IPE_MASK                    (0x2U)
#define FMC_PFB0CR_B0IPE_SHIFT                   (1U)
#define FMC_PFB0CR_B0IPE(x)                      (((uint32_t)(((uint32_t)(x)) << FMC_PFB0CR_B0IPE_SHIFT)) & FMC_PFB0CR_B0IPE_MASK)
#define FMC_PFB0CR_B0DPE_MASK                    (0x4U)
#define FMC_PFB0CR_B0DPE_SHIFT                   (2U)
#define FMC_PFB0CR_B0DPE(x)                      (((uint32_t)(((uint32_t)(x)) << FMC_PFB0CR_B0DPE_SHIFT)) & FMC_PFB0CR_B0DPE_MASK)
#define FMC_PFB0CR_B0MW_MASK                     (0x60000U)
#define FMC_PFB0CR_B0MW_SHIFT                    (17U)
#define FMC_PFB0CR_B0MW(x)                       (((uint32_t)(((uint32_t)(x)) << FMC_PFB0CR_B0MW_SHIFT)) & FMC_PFB0CR_B0MW_MASK)
#define FMC_PFB0CR_S_INV_MASK                    (0x80000U)
#define FMC_PFB0CR_S_INV_SHIFT                   (19U)
#define FMC_PFB0CR_S_INV(x)                      (((uint32_t)(((uint32_t)(x)) << FMC_PFB0CR_S_INV_SHIFT)) & FMC_PFB0CR_S_INV_MASK)
#define FMC_PFB0CR_B0RWSC_MASK                   (0xF0000000U)
#define FMC_PFB0CR_B0RWSC_SHIFT                  (28U)
#define FMC_PFB0CR_B0RWSC(x)                     (((uint32_t)(((uint32_t)(x)) << FMC_PFB0CR_B0RWSC_SHIFT)) & FMC_PFB0CR_B0RWSC_MASK)


/*!
 * @}
 */ /* end of group FMC_Register_Masks */


/* FMC - Peripheral instance base addresses */
/** Peripheral FMC base address */
#define FMC_BASE                                 (0x4001F000u)
/** Peripheral FMC base pointer */
#define FMC                                      ((FMC_Type *)FMC_BASE)
/** Array initializer of FMC peripheral base addresses */
#define FMC_BASE_ADDRS                           { FMC_BASE }
/** Array initializer of FMC peripheral base pointers */
#define FMC_BASE_PTRS                            { FMC }

/*!
 * @}
 */ /* end of group FMC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- FTFE Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFE_Peripheral_Access_Layer FTFE Peripheral Access Layer
 * @{
 */

/** FTFE - Register Layout Typedef */
typedef struct {
  __IO uint8_t FSTAT;                              /**< Flash Status Register, offset: 0x0 */
  __IO uint8_t FCNFG;                              /**< Flash Configuration Register, offset: 0x1 */
  __I  uint8_t FSEC;                               /**< Flash Security Register, offset: 0x2 */
  __I  uint8_t FOPT;                               /**< Flash Option Register, offset: 0x3 */
  __IO uint8_t FCCOB3;                             /**< Flash Common Command Object Registers, offset: 0x4 */
  __IO uint8_t FCCOB2;                             /**< Flash Common Command Object Registers, offset: 0x5 */
  __IO uint8_t FCCOB1;                             /**< Flash Common Command Object Registers, offset: 0x6 */
  __IO uint8_t FCCOB0;                             /**< Flash Common Command Object Registers, offset: 0x7 */
  __IO uint8_t FCCOB7;                             /**< Flash Common Command Object Registers, offset: 0x8 */
  __IO uint8_t FCCOB6;                             /**< Flash Common Command Object Registers, offset: 0x9 */
  __IO uint8_t FCCOB5;                             /**< Flash Common Command Object Registers, offset: 0xA */
  __IO uint8_t FCCOB4;                             /**< Flash Common Command Object Registers, offset: 0xB */
  __IO uint8_t FCCOBB;                             /**< Flash Common Command Object Registers, offset: 0xC */
  __IO uint8_t FCCOBA;                             /**< Flash Common Command Object Registers, offset: 0xD */
  __IO uint8_t FCCOB9;                             /**< Flash Common Command Object Registers, offset: 0xE */
  __IO uint8_t FCCOB8;                             /**< Flash Common Command Object Registers, offset: 0xF */
  __IO uint8_t FPROT3;                             /**< Program Flash Protection Registers, offset: 0x10 */
  __IO uint8_t FPROT2;                             /**< Program Flash Protection Registers, offset: 0x11 */
  __IO uint8_t FPROT1;                             /**< Program Flash Protection Registers, offset: 0x12 */
  __IO uint8_t FPROT0;                             /**< Program Flash Protection Registers, offset: 0x13 */
} FTFE_Type;

/* ----------------------------------------------------------------------------
   -- FTFE Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFE_Register_Masks FTFE Register Masks
 * @{
 */

/*! @name FSTAT - Flash Status Register */
#define FTFE_FSTAT_MGSTAT0_MASK                  (0x1U)
#define FTFE_FSTAT_MGSTAT0_SHIFT                 (0U)
#define FTFE_FSTAT_MGSTAT0(x)                    (((uint8_t)(((uint8_t)(x)) << FTFE_FSTAT_MGSTAT0_SHIFT)) & FTFE_FSTAT_MGSTAT0_MASK)
#define FTFE_FSTAT_FPVIOL_MASK                   (0x10U)
#define FTFE_FSTAT_FPVIOL_SHIFT                  (4U)
#define FTFE_FSTAT_FPVIOL(x)                     (((uint8_t)(((uint8_t)(x)) << FTFE_FSTAT_FPVIOL_SHIFT)) & FTFE_FSTAT_FPVIOL_MASK)
#define FTFE_FSTAT_ACCERR_MASK                   (0x20U)
#define FTFE_FSTAT_ACCERR_SHIFT                  (5U)
#define FTFE_FSTAT_ACCERR(x)                     (((uint8_t)(((uint8_t)(x)) << FTFE_FSTAT_ACCERR_SHIFT)) & FTFE_FSTAT_ACCERR_MASK)
#define FTFE_FSTAT_RDCOLERR_MASK                 (0x40U)
#define FTFE_FSTAT_RDCOLERR_SHIFT                (6U)
#define FTFE_FSTAT_RDCOLERR(x)                   (((uint8_t)(((uint8_t)(x)) << FTFE_FSTAT_RDCOLERR_SHIFT)) & FTFE_FSTAT_RDCOLERR_MASK)
#define FTFE_FSTAT_CCIF_MASK                     (0x80U)
#define FTFE_FSTAT_CCIF_SHIFT                    (7U)
#define FTFE_FSTAT_CCIF(x)                       (((uint8_t)(((uint8_t)(x)) << FTFE_FSTAT_CCIF_SHIFT)) & FTFE_FSTAT_CCIF_MASK)

/*! @name FCNFG - Flash Configuration Register */
#define FTFE_FCNFG_EEERDY_MASK                   (0x1U)
#define FTFE_FCNFG_EEERDY_SHIFT                  (0U)
#define FTFE_FCNFG_EEERDY(x)                     (((uint8_t)(((uint8_t)(x)) << FTFE_FCNFG_EEERDY_SHIFT)) & FTFE_FCNFG_EEERDY_MASK)
#define FTFE_FCNFG_RAMRDY_MASK                   (0x2U)
#define FTFE_FCNFG_RAMRDY_SHIFT                  (1U)
#define FTFE_FCNFG_RAMRDY(x)                     (((uint8_t)(((uint8_t)(x)) << FTFE_FCNFG_RAMRDY_SHIFT)) & FTFE_FCNFG_RAMRDY_MASK)
#define FTFE_FCNFG_PFLSH_MASK                    (0x4U)
#define FTFE_FCNFG_PFLSH_SHIFT                   (2U)
#define FTFE_FCNFG_PFLSH(x)                      (((uint8_t)(((uint8_t)(x)) << FTFE_FCNFG_PFLSH_SHIFT)) & FTFE_FCNFG_PFLSH_MASK)
#define FTFE_FCNFG_ERSSUSP_MASK                  (0x10U)
#define FTFE_FCNFG_ERSSUSP_SHIFT                 (4U)
#define FTFE_FCNFG_ERSSUSP(x)                    (((uint8_t)(((uint8_t)(x)) << FTFE_FCNFG_ERSSUSP_SHIFT)) & FTFE_FCNFG_ERSSUSP_MASK)
#define FTFE_FCNFG_ERSAREQ_MASK                  (0x20U)
#define FTFE_FCNFG_ERSAREQ_SHIFT                 (5U)
#define FTFE_FCNFG_ERSAREQ(x)                    (((uint8_t)(((uint8_t)(x)) << FTFE_FCNFG_ERSAREQ_SHIFT)) & FTFE_FCNFG_ERSAREQ_MASK)
#define FTFE_FCNFG_RDCOLLIE_MASK                 (0x40U)
#define FTFE_FCNFG_RDCOLLIE_SHIFT                (6U)
#define FTFE_FCNFG_RDCOLLIE(x)                   (((uint8_t)(((uint8_t)(x)) << FTFE_FCNFG_RDCOLLIE_SHIFT)) & FTFE_FCNFG_RDCOLLIE_MASK)
#define FTFE_FCNFG_CCIE_MASK                     (0x80U)
#define FTFE_FCNFG_CCIE_SHIFT                    (7U)
#define FTFE_FCNFG_CCIE(x)                       (((uint8_t)(((uint8_t)(x)) << FTFE_FCNFG_CCIE_SHIFT)) & FTFE_FCNFG_CCIE_MASK)

/*! @name FSEC - Flash Security Register */
#define FTFE_FSEC_SEC_MASK                       (0x3U)
#define FTFE_FSEC_SEC_SHIFT                      (0U)
#define FTFE_FSEC_SEC(x)                         (((uint8_t)(((uint8_t)(x)) << FTFE_FSEC_SEC_SHIFT)) & FTFE_FSEC_SEC_MASK)
#define FTFE_FSEC_FSLACC_MASK                    (0xCU)
#define FTFE_FSEC_FSLACC_SHIFT                   (2U)
#define FTFE_FSEC_FSLACC(x)                      (((uint8_t)(((uint8_t)(x)) << FTFE_FSEC_FSLACC_SHIFT)) & FTFE_FSEC_FSLACC_MASK)
#define FTFE_FSEC_MEEN_MASK                      (0x30U)
#define FTFE_FSEC_MEEN_SHIFT                     (4U)
#define FTFE_FSEC_MEEN(x)                        (((uint8_t)(((uint8_t)(x)) << FTFE_FSEC_MEEN_SHIFT)) & FTFE_FSEC_MEEN_MASK)
#define FTFE_FSEC_KEYEN_MASK                     (0xC0U)
#define FTFE_FSEC_KEYEN_SHIFT                    (6U)
#define FTFE_FSEC_KEYEN(x)                       (((uint8_t)(((uint8_t)(x)) << FTFE_FSEC_KEYEN_SHIFT)) & FTFE_FSEC_KEYEN_MASK)

/*! @name FOPT - Flash Option Register */
#define FTFE_FOPT_OPT_MASK                       (0xFFU)
#define FTFE_FOPT_OPT_SHIFT                      (0U)
#define FTFE_FOPT_OPT(x)                         (((uint8_t)(((uint8_t)(x)) << FTFE_FOPT_OPT_SHIFT)) & FTFE_FOPT_OPT_MASK)

/*! @name FCCOB3 - Flash Common Command Object Registers */
#define FTFE_FCCOB3_CCOBn_MASK                   (0xFFU)
#define FTFE_FCCOB3_CCOBn_SHIFT                  (0U)
#define FTFE_FCCOB3_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFE_FCCOB3_CCOBn_SHIFT)) & FTFE_FCCOB3_CCOBn_MASK)

/*! @name FCCOB2 - Flash Common Command Object Registers */
#define FTFE_FCCOB2_CCOBn_MASK                   (0xFFU)
#define FTFE_FCCOB2_CCOBn_SHIFT                  (0U)
#define FTFE_FCCOB2_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFE_FCCOB2_CCOBn_SHIFT)) & FTFE_FCCOB2_CCOBn_MASK)

/*! @name FCCOB1 - Flash Common Command Object Registers */
#define FTFE_FCCOB1_CCOBn_MASK                   (0xFFU)
#define FTFE_FCCOB1_CCOBn_SHIFT                  (0U)
#define FTFE_FCCOB1_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFE_FCCOB1_CCOBn_SHIFT)) & FTFE_FCCOB1_CCOBn_MASK)

/*! @name FCCOB0 - Flash Common Command Object Registers */
#define FTFE_FCCOB0_CCOBn_MASK                   (0xFFU)
#define FTFE_FCCOB0_CCOBn_SHIFT                  (0U)
#define FTFE_FCCOB0_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFE_FCCOB0_CCOBn_SHIFT)) & FTFE_FCCOB0_CCOBn_MASK)

/*! @name FCCOB7 - Flash Common Command Object Registers */
#define FTFE_FCCOB7_CCOBn_MASK                   (0xFFU)
#define FTFE_FCCOB7_CCOBn_SHIFT                  (0U)
#define FTFE_FCCOB7_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFE_FCCOB7_CCOBn_SHIFT)) & FTFE_FCCOB7_CCOBn_MASK)

/*! @name FCCOB6 - Flash Common Command Object Registers */
#define FTFE_FCCOB6_CCOBn_MASK                   (0xFFU)
#define FTFE_FCCOB6_CCOBn_SHIFT                  (0U)
#define FTFE_FCCOB6_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFE_FCCOB6_CCOBn_SHIFT)) & FTFE_FCCOB6_CCOBn_MASK)

/*! @name FCCOB5 - Flash Common Command Object Registers */
#define FTFE_FCCOB5_CCOBn_MASK                   (0xFFU)
#define FTFE_FCCOB5_CCOBn_SHIFT                  (0U)
#define FTFE_FCCOB5_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFE_FCCOB5_CCOBn_SHIFT)) & FTFE_FCCOB5_CCOBn_MASK)

/*! @name FCCOB4 - Flash Common Command Object Registers */
#define FTFE_FCCOB4_CCOBn_MASK                   (0xFFU)
#define FTFE_FCCOB4_CCOBn_SHIFT                  (0U)
#define FTFE_FCCOB4_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFE_FCCOB4_CCOBn_SHIFT)) & FTFE_FCCOB4_CCOBn_MASK)

/*! @name FCCOBB - Flash Common Command Object Registers */
#define FTFE_FCCOBB_CCOBn_MASK                   (0xFFU)
#define FTFE_FCCOBB_CCOBn_SHIFT                  (0U)
#define FTFE_FCCOBB_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFE_FCCOBB_CCOBn_SHIFT)) & FTFE_FCCOBB_CCOBn_MASK)

/*! @name FCCOBA - Flash Common Command Object Registers */
#define FTFE_FCCOBA_CCOBn_MASK                   (0xFFU)
#define FTFE_FCCOBA_CCOBn_SHIFT                  (0U)
#define FTFE_FCCOBA_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFE_FCCOBA_CCOBn_SHIFT)) & FTFE_FCCOBA_CCOBn_MASK)

/*! @name FCCOB9 - Flash Common Command Object Registers */
#define FTFE_FCCOB9_CCOBn_MASK                   (0xFFU)
#define FTFE_FCCOB9_CCOBn_SHIFT                  (0U)
#define FTFE_FCCOB9_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFE_FCCOB9_CCOBn_SHIFT)) & FTFE_FCCOB9_CCOBn_MASK)

/*! @name FCCOB8 - Flash Common Command Object Registers */
#define FTFE_FCCOB8_CCOBn_MASK                   (0xFFU)
#define FTFE_FCCOB8_CCOBn_SHIFT                  (0U)
#define FTFE_FCCOB8_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFE_FCCOB8_CCOBn_SHIFT)) & FTFE_FCCOB8_CCOBn_MASK)

/*! @name FPROT3 - Program Flash Protection Registers */
#define FTFE_FPROT3_PROT_MASK                    (0xFFU)
#define FTFE_FPROT3_PROT_SHIFT                   (0U)
#define FTFE_FPROT3_PROT(x)                      (((uint8_t)(((uint8_t)(x)) << FTFE_FPROT3_PROT_SHIFT)) & FTFE_FPROT3_PROT_MASK)

/*! @name FPROT2 - Program Flash Protection Registers */
#define FTFE_FPROT2_PROT_MASK                    (0xFFU)
#define FTFE_FPROT2_PROT_SHIFT                   (0U)
#define FTFE_FPROT2_PROT(x)                      (((uint8_t)(((uint8_t)(x)) << FTFE_FPROT2_PROT_SHIFT)) & FTFE_FPROT2_PROT_MASK)

/*! @name FPROT1 - Program Flash Protection Registers */
#define FTFE_FPROT1_PROT_MASK                    (0xFFU)
#define FTFE_FPROT1_PROT_SHIFT                   (0U)
#define FTFE_FPROT1_PROT(x)                      (((uint8_t)(((uint8_t)(x)) << FTFE_FPROT1_PROT_SHIFT)) & FTFE_FPROT1_PROT_MASK)

/*! @name FPROT0 - Program Flash Protection Registers */
#define FTFE_FPROT0_PROT_MASK                    (0xFFU)
#define FTFE_FPROT0_PROT_SHIFT                   (0U)
#define FTFE_FPROT0_PROT(x)                      (((uint8_t)(((uint8_t)(x)) << FTFE_FPROT0_PROT_SHIFT)) & FTFE_FPROT0_PROT_MASK)


/*!
 * @}
 */ /* end of group FTFE_Register_Masks */


/* FTFE - Peripheral instance base addresses */
/** Peripheral FTFE base address */
#define FTFE_BASE                                (0x40020000u)
/** Peripheral FTFE base pointer */
#define FTFE                                     ((FTFE_Type *)FTFE_BASE)
/** Array initializer of FTFE peripheral base addresses */
#define FTFE_BASE_ADDRS                          { FTFE_BASE }
/** Array initializer of FTFE peripheral base pointers */
#define FTFE_BASE_PTRS                           { FTFE }
/** Interrupt vectors for the FTFE peripheral type */
#define FTFE_COMMAND_COMPLETE_IRQS               { FTFE_IRQn }
#define FTFE_READ_COLLISION_IRQS                 { Read_Collision_IRQn }

/*!
 * @}
 */ /* end of group FTFE_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- FTM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Peripheral_Access_Layer FTM Peripheral Access Layer
 * @{
 */

/** FTM - Register Layout Typedef */
typedef struct {
  __IO uint32_t SC;                                /**< Status And Control, offset: 0x0 */
  __IO uint32_t CNT;                               /**< Counter, offset: 0x4 */
  __IO uint32_t MOD;                               /**< Modulo, offset: 0x8 */
  struct {                                         /* offset: 0xC, array step: 0x8 */
    __IO uint32_t CnSC;                              /**< Channel (n) Status And Control, array offset: 0xC, array step: 0x8 */
    __IO uint32_t CnV;                               /**< Channel (n) Value, array offset: 0x10, array step: 0x8 */
  } CONTROLS[8];
  __IO uint32_t CNTIN;                             /**< Counter Initial Value, offset: 0x4C */
  __IO uint32_t STATUS;                            /**< Capture And Compare Status, offset: 0x50 */
  __IO uint32_t MODE;                              /**< Features Mode Selection, offset: 0x54 */
  __IO uint32_t SYNC;                              /**< Synchronization, offset: 0x58 */
  __IO uint32_t OUTINIT;                           /**< Initial State For Channels Output, offset: 0x5C */
  __IO uint32_t OUTMASK;                           /**< Output Mask, offset: 0x60 */
  __IO uint32_t COMBINE;                           /**< Function For Linked Channels, offset: 0x64 */
  __IO uint32_t DEADTIME;                          /**< Deadtime Insertion Control, offset: 0x68 */
  __IO uint32_t EXTTRIG;                           /**< FTM External Trigger, offset: 0x6C */
  __IO uint32_t POL;                               /**< Channels Polarity, offset: 0x70 */
  __IO uint32_t FMS;                               /**< Fault Mode Status, offset: 0x74 */
  __IO uint32_t FILTER;                            /**< Input Capture Filter Control, offset: 0x78 */
  __IO uint32_t FLTCTRL;                           /**< Fault Control, offset: 0x7C */
  __IO uint32_t QDCTRL;                            /**< Quadrature Decoder Control And Status, offset: 0x80 */
  __IO uint32_t CONF;                              /**< Configuration, offset: 0x84 */
  __IO uint32_t FLTPOL;                            /**< FTM Fault Input Polarity, offset: 0x88 */
  __IO uint32_t SYNCONF;                           /**< Synchronization Configuration, offset: 0x8C */
  __IO uint32_t INVCTRL;                           /**< FTM Inverting Control, offset: 0x90 */
  __IO uint32_t SWOCTRL;                           /**< FTM Software Output Control, offset: 0x94 */
  __IO uint32_t PWMLOAD;                           /**< FTM PWM Load, offset: 0x98 */
} FTM_Type;

/* ----------------------------------------------------------------------------
   -- FTM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Register_Masks FTM Register Masks
 * @{
 */

/*! @name SC - Status And Control */
#define FTM_SC_PS_MASK                           (0x7U)
#define FTM_SC_PS_SHIFT                          (0U)
#define FTM_SC_PS(x)                             (((uint32_t)(((uint32_t)(x)) << FTM_SC_PS_SHIFT)) & FTM_SC_PS_MASK)
#define FTM_SC_CLKS_MASK                         (0x18U)
#define FTM_SC_CLKS_SHIFT                        (3U)
#define FTM_SC_CLKS(x)                           (((uint32_t)(((uint32_t)(x)) << FTM_SC_CLKS_SHIFT)) & FTM_SC_CLKS_MASK)
#define FTM_SC_CPWMS_MASK                        (0x20U)
#define FTM_SC_CPWMS_SHIFT                       (5U)
#define FTM_SC_CPWMS(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_SC_CPWMS_SHIFT)) & FTM_SC_CPWMS_MASK)
#define FTM_SC_TOIE_MASK                         (0x40U)
#define FTM_SC_TOIE_SHIFT                        (6U)
#define FTM_SC_TOIE(x)                           (((uint32_t)(((uint32_t)(x)) << FTM_SC_TOIE_SHIFT)) & FTM_SC_TOIE_MASK)
#define FTM_SC_TOF_MASK                          (0x80U)
#define FTM_SC_TOF_SHIFT                         (7U)
#define FTM_SC_TOF(x)                            (((uint32_t)(((uint32_t)(x)) << FTM_SC_TOF_SHIFT)) & FTM_SC_TOF_MASK)

/*! @name CNT - Counter */
#define FTM_CNT_COUNT_MASK                       (0xFFFFU)
#define FTM_CNT_COUNT_SHIFT                      (0U)
#define FTM_CNT_COUNT(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_CNT_COUNT_SHIFT)) & FTM_CNT_COUNT_MASK)

/*! @name MOD - Modulo */
#define FTM_MOD_MOD_MASK                         (0xFFFFU)
#define FTM_MOD_MOD_SHIFT                        (0U)
#define FTM_MOD_MOD(x)                           (((uint32_t)(((uint32_t)(x)) << FTM_MOD_MOD_SHIFT)) & FTM_MOD_MOD_MASK)

/*! @name CnSC - Channel (n) Status And Control */
#define FTM_CnSC_DMA_MASK                        (0x1U)
#define FTM_CnSC_DMA_SHIFT                       (0U)
#define FTM_CnSC_DMA(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_CnSC_DMA_SHIFT)) & FTM_CnSC_DMA_MASK)
#define FTM_CnSC_ICRST_MASK                      (0x2U)
#define FTM_CnSC_ICRST_SHIFT                     (1U)
#define FTM_CnSC_ICRST(x)                        (((uint32_t)(((uint32_t)(x)) << FTM_CnSC_ICRST_SHIFT)) & FTM_CnSC_ICRST_MASK)
#define FTM_CnSC_ELSA_MASK                       (0x4U)
#define FTM_CnSC_ELSA_SHIFT                      (2U)
#define FTM_CnSC_ELSA(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_CnSC_ELSA_SHIFT)) & FTM_CnSC_ELSA_MASK)
#define FTM_CnSC_ELSB_MASK                       (0x8U)
#define FTM_CnSC_ELSB_SHIFT                      (3U)
#define FTM_CnSC_ELSB(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_CnSC_ELSB_SHIFT)) & FTM_CnSC_ELSB_MASK)
#define FTM_CnSC_MSA_MASK                        (0x10U)
#define FTM_CnSC_MSA_SHIFT                       (4U)
#define FTM_CnSC_MSA(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_CnSC_MSA_SHIFT)) & FTM_CnSC_MSA_MASK)
#define FTM_CnSC_MSB_MASK                        (0x20U)
#define FTM_CnSC_MSB_SHIFT                       (5U)
#define FTM_CnSC_MSB(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_CnSC_MSB_SHIFT)) & FTM_CnSC_MSB_MASK)
#define FTM_CnSC_CHIE_MASK                       (0x40U)
#define FTM_CnSC_CHIE_SHIFT                      (6U)
#define FTM_CnSC_CHIE(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_CnSC_CHIE_SHIFT)) & FTM_CnSC_CHIE_MASK)
#define FTM_CnSC_CHF_MASK                        (0x80U)
#define FTM_CnSC_CHF_SHIFT                       (7U)
#define FTM_CnSC_CHF(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_CnSC_CHF_SHIFT)) & FTM_CnSC_CHF_MASK)

/* The count of FTM_CnSC */
#define FTM_CnSC_COUNT                           (8U)

/*! @name CnV - Channel (n) Value */
#define FTM_CnV_VAL_MASK                         (0xFFFFU)
#define FTM_CnV_VAL_SHIFT                        (0U)
#define FTM_CnV_VAL(x)                           (((uint32_t)(((uint32_t)(x)) << FTM_CnV_VAL_SHIFT)) & FTM_CnV_VAL_MASK)

/* The count of FTM_CnV */
#define FTM_CnV_COUNT                            (8U)

/*! @name CNTIN - Counter Initial Value */
#define FTM_CNTIN_INIT_MASK                      (0xFFFFU)
#define FTM_CNTIN_INIT_SHIFT                     (0U)
#define FTM_CNTIN_INIT(x)                        (((uint32_t)(((uint32_t)(x)) << FTM_CNTIN_INIT_SHIFT)) & FTM_CNTIN_INIT_MASK)

/*! @name STATUS - Capture And Compare Status */
#define FTM_STATUS_CH0F_MASK                     (0x1U)
#define FTM_STATUS_CH0F_SHIFT                    (0U)
#define FTM_STATUS_CH0F(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_STATUS_CH0F_SHIFT)) & FTM_STATUS_CH0F_MASK)
#define FTM_STATUS_CH1F_MASK                     (0x2U)
#define FTM_STATUS_CH1F_SHIFT                    (1U)
#define FTM_STATUS_CH1F(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_STATUS_CH1F_SHIFT)) & FTM_STATUS_CH1F_MASK)
#define FTM_STATUS_CH2F_MASK                     (0x4U)
#define FTM_STATUS_CH2F_SHIFT                    (2U)
#define FTM_STATUS_CH2F(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_STATUS_CH2F_SHIFT)) & FTM_STATUS_CH2F_MASK)
#define FTM_STATUS_CH3F_MASK                     (0x8U)
#define FTM_STATUS_CH3F_SHIFT                    (3U)
#define FTM_STATUS_CH3F(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_STATUS_CH3F_SHIFT)) & FTM_STATUS_CH3F_MASK)
#define FTM_STATUS_CH4F_MASK                     (0x10U)
#define FTM_STATUS_CH4F_SHIFT                    (4U)
#define FTM_STATUS_CH4F(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_STATUS_CH4F_SHIFT)) & FTM_STATUS_CH4F_MASK)
#define FTM_STATUS_CH5F_MASK                     (0x20U)
#define FTM_STATUS_CH5F_SHIFT                    (5U)
#define FTM_STATUS_CH5F(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_STATUS_CH5F_SHIFT)) & FTM_STATUS_CH5F_MASK)
#define FTM_STATUS_CH6F_MASK                     (0x40U)
#define FTM_STATUS_CH6F_SHIFT                    (6U)
#define FTM_STATUS_CH6F(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_STATUS_CH6F_SHIFT)) & FTM_STATUS_CH6F_MASK)
#define FTM_STATUS_CH7F_MASK                     (0x80U)
#define FTM_STATUS_CH7F_SHIFT                    (7U)
#define FTM_STATUS_CH7F(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_STATUS_CH7F_SHIFT)) & FTM_STATUS_CH7F_MASK)

/*! @name MODE - Features Mode Selection */
#define FTM_MODE_FTMEN_MASK                      (0x1U)
#define FTM_MODE_FTMEN_SHIFT                     (0U)
#define FTM_MODE_FTMEN(x)                        (((uint32_t)(((uint32_t)(x)) << FTM_MODE_FTMEN_SHIFT)) & FTM_MODE_FTMEN_MASK)
#define FTM_MODE_INIT_MASK                       (0x2U)
#define FTM_MODE_INIT_SHIFT                      (1U)
#define FTM_MODE_INIT(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_MODE_INIT_SHIFT)) & FTM_MODE_INIT_MASK)
#define FTM_MODE_WPDIS_MASK                      (0x4U)
#define FTM_MODE_WPDIS_SHIFT                     (2U)
#define FTM_MODE_WPDIS(x)                        (((uint32_t)(((uint32_t)(x)) << FTM_MODE_WPDIS_SHIFT)) & FTM_MODE_WPDIS_MASK)
#define FTM_MODE_PWMSYNC_MASK                    (0x8U)
#define FTM_MODE_PWMSYNC_SHIFT                   (3U)
#define FTM_MODE_PWMSYNC(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_MODE_PWMSYNC_SHIFT)) & FTM_MODE_PWMSYNC_MASK)
#define FTM_MODE_CAPTEST_MASK                    (0x10U)
#define FTM_MODE_CAPTEST_SHIFT                   (4U)
#define FTM_MODE_CAPTEST(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_MODE_CAPTEST_SHIFT)) & FTM_MODE_CAPTEST_MASK)
#define FTM_MODE_FAULTM_MASK                     (0x60U)
#define FTM_MODE_FAULTM_SHIFT                    (5U)
#define FTM_MODE_FAULTM(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_MODE_FAULTM_SHIFT)) & FTM_MODE_FAULTM_MASK)
#define FTM_MODE_FAULTIE_MASK                    (0x80U)
#define FTM_MODE_FAULTIE_SHIFT                   (7U)
#define FTM_MODE_FAULTIE(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_MODE_FAULTIE_SHIFT)) & FTM_MODE_FAULTIE_MASK)

/*! @name SYNC - Synchronization */
#define FTM_SYNC_CNTMIN_MASK                     (0x1U)
#define FTM_SYNC_CNTMIN_SHIFT                    (0U)
#define FTM_SYNC_CNTMIN(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_SYNC_CNTMIN_SHIFT)) & FTM_SYNC_CNTMIN_MASK)
#define FTM_SYNC_CNTMAX_MASK                     (0x2U)
#define FTM_SYNC_CNTMAX_SHIFT                    (1U)
#define FTM_SYNC_CNTMAX(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_SYNC_CNTMAX_SHIFT)) & FTM_SYNC_CNTMAX_MASK)
#define FTM_SYNC_REINIT_MASK                     (0x4U)
#define FTM_SYNC_REINIT_SHIFT                    (2U)
#define FTM_SYNC_REINIT(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_SYNC_REINIT_SHIFT)) & FTM_SYNC_REINIT_MASK)
#define FTM_SYNC_SYNCHOM_MASK                    (0x8U)
#define FTM_SYNC_SYNCHOM_SHIFT                   (3U)
#define FTM_SYNC_SYNCHOM(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_SYNC_SYNCHOM_SHIFT)) & FTM_SYNC_SYNCHOM_MASK)
#define FTM_SYNC_TRIG0_MASK                      (0x10U)
#define FTM_SYNC_TRIG0_SHIFT                     (4U)
#define FTM_SYNC_TRIG0(x)                        (((uint32_t)(((uint32_t)(x)) << FTM_SYNC_TRIG0_SHIFT)) & FTM_SYNC_TRIG0_MASK)
#define FTM_SYNC_TRIG1_MASK                      (0x20U)
#define FTM_SYNC_TRIG1_SHIFT                     (5U)
#define FTM_SYNC_TRIG1(x)                        (((uint32_t)(((uint32_t)(x)) << FTM_SYNC_TRIG1_SHIFT)) & FTM_SYNC_TRIG1_MASK)
#define FTM_SYNC_TRIG2_MASK                      (0x40U)
#define FTM_SYNC_TRIG2_SHIFT                     (6U)
#define FTM_SYNC_TRIG2(x)                        (((uint32_t)(((uint32_t)(x)) << FTM_SYNC_TRIG2_SHIFT)) & FTM_SYNC_TRIG2_MASK)
#define FTM_SYNC_SWSYNC_MASK                     (0x80U)
#define FTM_SYNC_SWSYNC_SHIFT                    (7U)
#define FTM_SYNC_SWSYNC(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_SYNC_SWSYNC_SHIFT)) & FTM_SYNC_SWSYNC_MASK)

/*! @name OUTINIT - Initial State For Channels Output */
#define FTM_OUTINIT_CH0OI_MASK                   (0x1U)
#define FTM_OUTINIT_CH0OI_SHIFT                  (0U)
#define FTM_OUTINIT_CH0OI(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTINIT_CH0OI_SHIFT)) & FTM_OUTINIT_CH0OI_MASK)
#define FTM_OUTINIT_CH1OI_MASK                   (0x2U)
#define FTM_OUTINIT_CH1OI_SHIFT                  (1U)
#define FTM_OUTINIT_CH1OI(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTINIT_CH1OI_SHIFT)) & FTM_OUTINIT_CH1OI_MASK)
#define FTM_OUTINIT_CH2OI_MASK                   (0x4U)
#define FTM_OUTINIT_CH2OI_SHIFT                  (2U)
#define FTM_OUTINIT_CH2OI(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTINIT_CH2OI_SHIFT)) & FTM_OUTINIT_CH2OI_MASK)
#define FTM_OUTINIT_CH3OI_MASK                   (0x8U)
#define FTM_OUTINIT_CH3OI_SHIFT                  (3U)
#define FTM_OUTINIT_CH3OI(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTINIT_CH3OI_SHIFT)) & FTM_OUTINIT_CH3OI_MASK)
#define FTM_OUTINIT_CH4OI_MASK                   (0x10U)
#define FTM_OUTINIT_CH4OI_SHIFT                  (4U)
#define FTM_OUTINIT_CH4OI(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTINIT_CH4OI_SHIFT)) & FTM_OUTINIT_CH4OI_MASK)
#define FTM_OUTINIT_CH5OI_MASK                   (0x20U)
#define FTM_OUTINIT_CH5OI_SHIFT                  (5U)
#define FTM_OUTINIT_CH5OI(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTINIT_CH5OI_SHIFT)) & FTM_OUTINIT_CH5OI_MASK)
#define FTM_OUTINIT_CH6OI_MASK                   (0x40U)
#define FTM_OUTINIT_CH6OI_SHIFT                  (6U)
#define FTM_OUTINIT_CH6OI(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTINIT_CH6OI_SHIFT)) & FTM_OUTINIT_CH6OI_MASK)
#define FTM_OUTINIT_CH7OI_MASK                   (0x80U)
#define FTM_OUTINIT_CH7OI_SHIFT                  (7U)
#define FTM_OUTINIT_CH7OI(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTINIT_CH7OI_SHIFT)) & FTM_OUTINIT_CH7OI_MASK)

/*! @name OUTMASK - Output Mask */
#define FTM_OUTMASK_CH0OM_MASK                   (0x1U)
#define FTM_OUTMASK_CH0OM_SHIFT                  (0U)
#define FTM_OUTMASK_CH0OM(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTMASK_CH0OM_SHIFT)) & FTM_OUTMASK_CH0OM_MASK)
#define FTM_OUTMASK_CH1OM_MASK                   (0x2U)
#define FTM_OUTMASK_CH1OM_SHIFT                  (1U)
#define FTM_OUTMASK_CH1OM(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTMASK_CH1OM_SHIFT)) & FTM_OUTMASK_CH1OM_MASK)
#define FTM_OUTMASK_CH2OM_MASK                   (0x4U)
#define FTM_OUTMASK_CH2OM_SHIFT                  (2U)
#define FTM_OUTMASK_CH2OM(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTMASK_CH2OM_SHIFT)) & FTM_OUTMASK_CH2OM_MASK)
#define FTM_OUTMASK_CH3OM_MASK                   (0x8U)
#define FTM_OUTMASK_CH3OM_SHIFT                  (3U)
#define FTM_OUTMASK_CH3OM(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTMASK_CH3OM_SHIFT)) & FTM_OUTMASK_CH3OM_MASK)
#define FTM_OUTMASK_CH4OM_MASK                   (0x10U)
#define FTM_OUTMASK_CH4OM_SHIFT                  (4U)
#define FTM_OUTMASK_CH4OM(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTMASK_CH4OM_SHIFT)) & FTM_OUTMASK_CH4OM_MASK)
#define FTM_OUTMASK_CH5OM_MASK                   (0x20U)
#define FTM_OUTMASK_CH5OM_SHIFT                  (5U)
#define FTM_OUTMASK_CH5OM(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTMASK_CH5OM_SHIFT)) & FTM_OUTMASK_CH5OM_MASK)
#define FTM_OUTMASK_CH6OM_MASK                   (0x40U)
#define FTM_OUTMASK_CH6OM_SHIFT                  (6U)
#define FTM_OUTMASK_CH6OM(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTMASK_CH6OM_SHIFT)) & FTM_OUTMASK_CH6OM_MASK)
#define FTM_OUTMASK_CH7OM_MASK                   (0x80U)
#define FTM_OUTMASK_CH7OM_SHIFT                  (7U)
#define FTM_OUTMASK_CH7OM(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTMASK_CH7OM_SHIFT)) & FTM_OUTMASK_CH7OM_MASK)

/*! @name COMBINE - Function For Linked Channels */
#define FTM_COMBINE_COMBINE0_MASK                (0x1U)
#define FTM_COMBINE_COMBINE0_SHIFT               (0U)
#define FTM_COMBINE_COMBINE0(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_COMBINE0_SHIFT)) & FTM_COMBINE_COMBINE0_MASK)
#define FTM_COMBINE_COMP0_MASK                   (0x2U)
#define FTM_COMBINE_COMP0_SHIFT                  (1U)
#define FTM_COMBINE_COMP0(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_COMP0_SHIFT)) & FTM_COMBINE_COMP0_MASK)
#define FTM_COMBINE_DECAPEN0_MASK                (0x4U)
#define FTM_COMBINE_DECAPEN0_SHIFT               (2U)
#define FTM_COMBINE_DECAPEN0(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DECAPEN0_SHIFT)) & FTM_COMBINE_DECAPEN0_MASK)
#define FTM_COMBINE_DECAP0_MASK                  (0x8U)
#define FTM_COMBINE_DECAP0_SHIFT                 (3U)
#define FTM_COMBINE_DECAP0(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DECAP0_SHIFT)) & FTM_COMBINE_DECAP0_MASK)
#define FTM_COMBINE_DTEN0_MASK                   (0x10U)
#define FTM_COMBINE_DTEN0_SHIFT                  (4U)
#define FTM_COMBINE_DTEN0(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DTEN0_SHIFT)) & FTM_COMBINE_DTEN0_MASK)
#define FTM_COMBINE_SYNCEN0_MASK                 (0x20U)
#define FTM_COMBINE_SYNCEN0_SHIFT                (5U)
#define FTM_COMBINE_SYNCEN0(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_SYNCEN0_SHIFT)) & FTM_COMBINE_SYNCEN0_MASK)
#define FTM_COMBINE_FAULTEN0_MASK                (0x40U)
#define FTM_COMBINE_FAULTEN0_SHIFT               (6U)
#define FTM_COMBINE_FAULTEN0(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_FAULTEN0_SHIFT)) & FTM_COMBINE_FAULTEN0_MASK)
#define FTM_COMBINE_COMBINE1_MASK                (0x100U)
#define FTM_COMBINE_COMBINE1_SHIFT               (8U)
#define FTM_COMBINE_COMBINE1(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_COMBINE1_SHIFT)) & FTM_COMBINE_COMBINE1_MASK)
#define FTM_COMBINE_COMP1_MASK                   (0x200U)
#define FTM_COMBINE_COMP1_SHIFT                  (9U)
#define FTM_COMBINE_COMP1(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_COMP1_SHIFT)) & FTM_COMBINE_COMP1_MASK)
#define FTM_COMBINE_DECAPEN1_MASK                (0x400U)
#define FTM_COMBINE_DECAPEN1_SHIFT               (10U)
#define FTM_COMBINE_DECAPEN1(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DECAPEN1_SHIFT)) & FTM_COMBINE_DECAPEN1_MASK)
#define FTM_COMBINE_DECAP1_MASK                  (0x800U)
#define FTM_COMBINE_DECAP1_SHIFT                 (11U)
#define FTM_COMBINE_DECAP1(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DECAP1_SHIFT)) & FTM_COMBINE_DECAP1_MASK)
#define FTM_COMBINE_DTEN1_MASK                   (0x1000U)
#define FTM_COMBINE_DTEN1_SHIFT                  (12U)
#define FTM_COMBINE_DTEN1(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DTEN1_SHIFT)) & FTM_COMBINE_DTEN1_MASK)
#define FTM_COMBINE_SYNCEN1_MASK                 (0x2000U)
#define FTM_COMBINE_SYNCEN1_SHIFT                (13U)
#define FTM_COMBINE_SYNCEN1(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_SYNCEN1_SHIFT)) & FTM_COMBINE_SYNCEN1_MASK)
#define FTM_COMBINE_FAULTEN1_MASK                (0x4000U)
#define FTM_COMBINE_FAULTEN1_SHIFT               (14U)
#define FTM_COMBINE_FAULTEN1(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_FAULTEN1_SHIFT)) & FTM_COMBINE_FAULTEN1_MASK)
#define FTM_COMBINE_COMBINE2_MASK                (0x10000U)
#define FTM_COMBINE_COMBINE2_SHIFT               (16U)
#define FTM_COMBINE_COMBINE2(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_COMBINE2_SHIFT)) & FTM_COMBINE_COMBINE2_MASK)
#define FTM_COMBINE_COMP2_MASK                   (0x20000U)
#define FTM_COMBINE_COMP2_SHIFT                  (17U)
#define FTM_COMBINE_COMP2(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_COMP2_SHIFT)) & FTM_COMBINE_COMP2_MASK)
#define FTM_COMBINE_DECAPEN2_MASK                (0x40000U)
#define FTM_COMBINE_DECAPEN2_SHIFT               (18U)
#define FTM_COMBINE_DECAPEN2(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DECAPEN2_SHIFT)) & FTM_COMBINE_DECAPEN2_MASK)
#define FTM_COMBINE_DECAP2_MASK                  (0x80000U)
#define FTM_COMBINE_DECAP2_SHIFT                 (19U)
#define FTM_COMBINE_DECAP2(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DECAP2_SHIFT)) & FTM_COMBINE_DECAP2_MASK)
#define FTM_COMBINE_DTEN2_MASK                   (0x100000U)
#define FTM_COMBINE_DTEN2_SHIFT                  (20U)
#define FTM_COMBINE_DTEN2(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DTEN2_SHIFT)) & FTM_COMBINE_DTEN2_MASK)
#define FTM_COMBINE_SYNCEN2_MASK                 (0x200000U)
#define FTM_COMBINE_SYNCEN2_SHIFT                (21U)
#define FTM_COMBINE_SYNCEN2(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_SYNCEN2_SHIFT)) & FTM_COMBINE_SYNCEN2_MASK)
#define FTM_COMBINE_FAULTEN2_MASK                (0x400000U)
#define FTM_COMBINE_FAULTEN2_SHIFT               (22U)
#define FTM_COMBINE_FAULTEN2(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_FAULTEN2_SHIFT)) & FTM_COMBINE_FAULTEN2_MASK)
#define FTM_COMBINE_COMBINE3_MASK                (0x1000000U)
#define FTM_COMBINE_COMBINE3_SHIFT               (24U)
#define FTM_COMBINE_COMBINE3(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_COMBINE3_SHIFT)) & FTM_COMBINE_COMBINE3_MASK)
#define FTM_COMBINE_COMP3_MASK                   (0x2000000U)
#define FTM_COMBINE_COMP3_SHIFT                  (25U)
#define FTM_COMBINE_COMP3(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_COMP3_SHIFT)) & FTM_COMBINE_COMP3_MASK)
#define FTM_COMBINE_DECAPEN3_MASK                (0x4000000U)
#define FTM_COMBINE_DECAPEN3_SHIFT               (26U)
#define FTM_COMBINE_DECAPEN3(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DECAPEN3_SHIFT)) & FTM_COMBINE_DECAPEN3_MASK)
#define FTM_COMBINE_DECAP3_MASK                  (0x8000000U)
#define FTM_COMBINE_DECAP3_SHIFT                 (27U)
#define FTM_COMBINE_DECAP3(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DECAP3_SHIFT)) & FTM_COMBINE_DECAP3_MASK)
#define FTM_COMBINE_DTEN3_MASK                   (0x10000000U)
#define FTM_COMBINE_DTEN3_SHIFT                  (28U)
#define FTM_COMBINE_DTEN3(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DTEN3_SHIFT)) & FTM_COMBINE_DTEN3_MASK)
#define FTM_COMBINE_SYNCEN3_MASK                 (0x20000000U)
#define FTM_COMBINE_SYNCEN3_SHIFT                (29U)
#define FTM_COMBINE_SYNCEN3(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_SYNCEN3_SHIFT)) & FTM_COMBINE_SYNCEN3_MASK)
#define FTM_COMBINE_FAULTEN3_MASK                (0x40000000U)
#define FTM_COMBINE_FAULTEN3_SHIFT               (30U)
#define FTM_COMBINE_FAULTEN3(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_FAULTEN3_SHIFT)) & FTM_COMBINE_FAULTEN3_MASK)

/*! @name DEADTIME - Deadtime Insertion Control */
#define FTM_DEADTIME_DTVAL_MASK                  (0x3FU)
#define FTM_DEADTIME_DTVAL_SHIFT                 (0U)
#define FTM_DEADTIME_DTVAL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_DEADTIME_DTVAL_SHIFT)) & FTM_DEADTIME_DTVAL_MASK)
#define FTM_DEADTIME_DTPS_MASK                   (0xC0U)
#define FTM_DEADTIME_DTPS_SHIFT                  (6U)
#define FTM_DEADTIME_DTPS(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_DEADTIME_DTPS_SHIFT)) & FTM_DEADTIME_DTPS_MASK)

/*! @name EXTTRIG - FTM External Trigger */
#define FTM_EXTTRIG_CH2TRIG_MASK                 (0x1U)
#define FTM_EXTTRIG_CH2TRIG_SHIFT                (0U)
#define FTM_EXTTRIG_CH2TRIG(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_CH2TRIG_SHIFT)) & FTM_EXTTRIG_CH2TRIG_MASK)
#define FTM_EXTTRIG_CH3TRIG_MASK                 (0x2U)
#define FTM_EXTTRIG_CH3TRIG_SHIFT                (1U)
#define FTM_EXTTRIG_CH3TRIG(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_CH3TRIG_SHIFT)) & FTM_EXTTRIG_CH3TRIG_MASK)
#define FTM_EXTTRIG_CH4TRIG_MASK                 (0x4U)
#define FTM_EXTTRIG_CH4TRIG_SHIFT                (2U)
#define FTM_EXTTRIG_CH4TRIG(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_CH4TRIG_SHIFT)) & FTM_EXTTRIG_CH4TRIG_MASK)
#define FTM_EXTTRIG_CH5TRIG_MASK                 (0x8U)
#define FTM_EXTTRIG_CH5TRIG_SHIFT                (3U)
#define FTM_EXTTRIG_CH5TRIG(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_CH5TRIG_SHIFT)) & FTM_EXTTRIG_CH5TRIG_MASK)
#define FTM_EXTTRIG_CH0TRIG_MASK                 (0x10U)
#define FTM_EXTTRIG_CH0TRIG_SHIFT                (4U)
#define FTM_EXTTRIG_CH0TRIG(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_CH0TRIG_SHIFT)) & FTM_EXTTRIG_CH0TRIG_MASK)
#define FTM_EXTTRIG_CH1TRIG_MASK                 (0x20U)
#define FTM_EXTTRIG_CH1TRIG_SHIFT                (5U)
#define FTM_EXTTRIG_CH1TRIG(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_CH1TRIG_SHIFT)) & FTM_EXTTRIG_CH1TRIG_MASK)
#define FTM_EXTTRIG_INITTRIGEN_MASK              (0x40U)
#define FTM_EXTTRIG_INITTRIGEN_SHIFT             (6U)
#define FTM_EXTTRIG_INITTRIGEN(x)                (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_INITTRIGEN_SHIFT)) & FTM_EXTTRIG_INITTRIGEN_MASK)
#define FTM_EXTTRIG_TRIGF_MASK                   (0x80U)
#define FTM_EXTTRIG_TRIGF_SHIFT                  (7U)
#define FTM_EXTTRIG_TRIGF(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_TRIGF_SHIFT)) & FTM_EXTTRIG_TRIGF_MASK)

/*! @name POL - Channels Polarity */
#define FTM_POL_POL0_MASK                        (0x1U)
#define FTM_POL_POL0_SHIFT                       (0U)
#define FTM_POL_POL0(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_POL_POL0_SHIFT)) & FTM_POL_POL0_MASK)
#define FTM_POL_POL1_MASK                        (0x2U)
#define FTM_POL_POL1_SHIFT                       (1U)
#define FTM_POL_POL1(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_POL_POL1_SHIFT)) & FTM_POL_POL1_MASK)
#define FTM_POL_POL2_MASK                        (0x4U)
#define FTM_POL_POL2_SHIFT                       (2U)
#define FTM_POL_POL2(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_POL_POL2_SHIFT)) & FTM_POL_POL2_MASK)
#define FTM_POL_POL3_MASK                        (0x8U)
#define FTM_POL_POL3_SHIFT                       (3U)
#define FTM_POL_POL3(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_POL_POL3_SHIFT)) & FTM_POL_POL3_MASK)
#define FTM_POL_POL4_MASK                        (0x10U)
#define FTM_POL_POL4_SHIFT                       (4U)
#define FTM_POL_POL4(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_POL_POL4_SHIFT)) & FTM_POL_POL4_MASK)
#define FTM_POL_POL5_MASK                        (0x20U)
#define FTM_POL_POL5_SHIFT                       (5U)
#define FTM_POL_POL5(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_POL_POL5_SHIFT)) & FTM_POL_POL5_MASK)
#define FTM_POL_POL6_MASK                        (0x40U)
#define FTM_POL_POL6_SHIFT                       (6U)
#define FTM_POL_POL6(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_POL_POL6_SHIFT)) & FTM_POL_POL6_MASK)
#define FTM_POL_POL7_MASK                        (0x80U)
#define FTM_POL_POL7_SHIFT                       (7U)
#define FTM_POL_POL7(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_POL_POL7_SHIFT)) & FTM_POL_POL7_MASK)

/*! @name FMS - Fault Mode Status */
#define FTM_FMS_FAULTF0_MASK                     (0x1U)
#define FTM_FMS_FAULTF0_SHIFT                    (0U)
#define FTM_FMS_FAULTF0(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_FMS_FAULTF0_SHIFT)) & FTM_FMS_FAULTF0_MASK)
#define FTM_FMS_FAULTF1_MASK                     (0x2U)
#define FTM_FMS_FAULTF1_SHIFT                    (1U)
#define FTM_FMS_FAULTF1(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_FMS_FAULTF1_SHIFT)) & FTM_FMS_FAULTF1_MASK)
#define FTM_FMS_FAULTF2_MASK                     (0x4U)
#define FTM_FMS_FAULTF2_SHIFT                    (2U)
#define FTM_FMS_FAULTF2(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_FMS_FAULTF2_SHIFT)) & FTM_FMS_FAULTF2_MASK)
#define FTM_FMS_FAULTF3_MASK                     (0x8U)
#define FTM_FMS_FAULTF3_SHIFT                    (3U)
#define FTM_FMS_FAULTF3(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_FMS_FAULTF3_SHIFT)) & FTM_FMS_FAULTF3_MASK)
#define FTM_FMS_FAULTIN_MASK                     (0x20U)
#define FTM_FMS_FAULTIN_SHIFT                    (5U)
#define FTM_FMS_FAULTIN(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_FMS_FAULTIN_SHIFT)) & FTM_FMS_FAULTIN_MASK)
#define FTM_FMS_WPEN_MASK                        (0x40U)
#define FTM_FMS_WPEN_SHIFT                       (6U)
#define FTM_FMS_WPEN(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_FMS_WPEN_SHIFT)) & FTM_FMS_WPEN_MASK)
#define FTM_FMS_FAULTF_MASK                      (0x80U)
#define FTM_FMS_FAULTF_SHIFT                     (7U)
#define FTM_FMS_FAULTF(x)                        (((uint32_t)(((uint32_t)(x)) << FTM_FMS_FAULTF_SHIFT)) & FTM_FMS_FAULTF_MASK)

/*! @name FILTER - Input Capture Filter Control */
#define FTM_FILTER_CH0FVAL_MASK                  (0xFU)
#define FTM_FILTER_CH0FVAL_SHIFT                 (0U)
#define FTM_FILTER_CH0FVAL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_FILTER_CH0FVAL_SHIFT)) & FTM_FILTER_CH0FVAL_MASK)
#define FTM_FILTER_CH1FVAL_MASK                  (0xF0U)
#define FTM_FILTER_CH1FVAL_SHIFT                 (4U)
#define FTM_FILTER_CH1FVAL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_FILTER_CH1FVAL_SHIFT)) & FTM_FILTER_CH1FVAL_MASK)
#define FTM_FILTER_CH2FVAL_MASK                  (0xF00U)
#define FTM_FILTER_CH2FVAL_SHIFT                 (8U)
#define FTM_FILTER_CH2FVAL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_FILTER_CH2FVAL_SHIFT)) & FTM_FILTER_CH2FVAL_MASK)
#define FTM_FILTER_CH3FVAL_MASK                  (0xF000U)
#define FTM_FILTER_CH3FVAL_SHIFT                 (12U)
#define FTM_FILTER_CH3FVAL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_FILTER_CH3FVAL_SHIFT)) & FTM_FILTER_CH3FVAL_MASK)

/*! @name FLTCTRL - Fault Control */
#define FTM_FLTCTRL_FAULT0EN_MASK                (0x1U)
#define FTM_FLTCTRL_FAULT0EN_SHIFT               (0U)
#define FTM_FLTCTRL_FAULT0EN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FAULT0EN_SHIFT)) & FTM_FLTCTRL_FAULT0EN_MASK)
#define FTM_FLTCTRL_FAULT1EN_MASK                (0x2U)
#define FTM_FLTCTRL_FAULT1EN_SHIFT               (1U)
#define FTM_FLTCTRL_FAULT1EN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FAULT1EN_SHIFT)) & FTM_FLTCTRL_FAULT1EN_MASK)
#define FTM_FLTCTRL_FAULT2EN_MASK                (0x4U)
#define FTM_FLTCTRL_FAULT2EN_SHIFT               (2U)
#define FTM_FLTCTRL_FAULT2EN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FAULT2EN_SHIFT)) & FTM_FLTCTRL_FAULT2EN_MASK)
#define FTM_FLTCTRL_FAULT3EN_MASK                (0x8U)
#define FTM_FLTCTRL_FAULT3EN_SHIFT               (3U)
#define FTM_FLTCTRL_FAULT3EN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FAULT3EN_SHIFT)) & FTM_FLTCTRL_FAULT3EN_MASK)
#define FTM_FLTCTRL_FFLTR0EN_MASK                (0x10U)
#define FTM_FLTCTRL_FFLTR0EN_SHIFT               (4U)
#define FTM_FLTCTRL_FFLTR0EN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FFLTR0EN_SHIFT)) & FTM_FLTCTRL_FFLTR0EN_MASK)
#define FTM_FLTCTRL_FFLTR1EN_MASK                (0x20U)
#define FTM_FLTCTRL_FFLTR1EN_SHIFT               (5U)
#define FTM_FLTCTRL_FFLTR1EN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FFLTR1EN_SHIFT)) & FTM_FLTCTRL_FFLTR1EN_MASK)
#define FTM_FLTCTRL_FFLTR2EN_MASK                (0x40U)
#define FTM_FLTCTRL_FFLTR2EN_SHIFT               (6U)
#define FTM_FLTCTRL_FFLTR2EN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FFLTR2EN_SHIFT)) & FTM_FLTCTRL_FFLTR2EN_MASK)
#define FTM_FLTCTRL_FFLTR3EN_MASK                (0x80U)
#define FTM_FLTCTRL_FFLTR3EN_SHIFT               (7U)
#define FTM_FLTCTRL_FFLTR3EN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FFLTR3EN_SHIFT)) & FTM_FLTCTRL_FFLTR3EN_MASK)
#define FTM_FLTCTRL_FFVAL_MASK                   (0xF00U)
#define FTM_FLTCTRL_FFVAL_SHIFT                  (8U)
#define FTM_FLTCTRL_FFVAL(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FFVAL_SHIFT)) & FTM_FLTCTRL_FFVAL_MASK)

/*! @name QDCTRL - Quadrature Decoder Control And Status */
#define FTM_QDCTRL_QUADEN_MASK                   (0x1U)
#define FTM_QDCTRL_QUADEN_SHIFT                  (0U)
#define FTM_QDCTRL_QUADEN(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_QDCTRL_QUADEN_SHIFT)) & FTM_QDCTRL_QUADEN_MASK)
#define FTM_QDCTRL_TOFDIR_MASK                   (0x2U)
#define FTM_QDCTRL_TOFDIR_SHIFT                  (1U)
#define FTM_QDCTRL_TOFDIR(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_QDCTRL_TOFDIR_SHIFT)) & FTM_QDCTRL_TOFDIR_MASK)
#define FTM_QDCTRL_QUADIR_MASK                   (0x4U)
#define FTM_QDCTRL_QUADIR_SHIFT                  (2U)
#define FTM_QDCTRL_QUADIR(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_QDCTRL_QUADIR_SHIFT)) & FTM_QDCTRL_QUADIR_MASK)
#define FTM_QDCTRL_QUADMODE_MASK                 (0x8U)
#define FTM_QDCTRL_QUADMODE_SHIFT                (3U)
#define FTM_QDCTRL_QUADMODE(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_QDCTRL_QUADMODE_SHIFT)) & FTM_QDCTRL_QUADMODE_MASK)
#define FTM_QDCTRL_PHBPOL_MASK                   (0x10U)
#define FTM_QDCTRL_PHBPOL_SHIFT                  (4U)
#define FTM_QDCTRL_PHBPOL(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_QDCTRL_PHBPOL_SHIFT)) & FTM_QDCTRL_PHBPOL_MASK)
#define FTM_QDCTRL_PHAPOL_MASK                   (0x20U)
#define FTM_QDCTRL_PHAPOL_SHIFT                  (5U)
#define FTM_QDCTRL_PHAPOL(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_QDCTRL_PHAPOL_SHIFT)) & FTM_QDCTRL_PHAPOL_MASK)
#define FTM_QDCTRL_PHBFLTREN_MASK                (0x40U)
#define FTM_QDCTRL_PHBFLTREN_SHIFT               (6U)
#define FTM_QDCTRL_PHBFLTREN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_QDCTRL_PHBFLTREN_SHIFT)) & FTM_QDCTRL_PHBFLTREN_MASK)
#define FTM_QDCTRL_PHAFLTREN_MASK                (0x80U)
#define FTM_QDCTRL_PHAFLTREN_SHIFT               (7U)
#define FTM_QDCTRL_PHAFLTREN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_QDCTRL_PHAFLTREN_SHIFT)) & FTM_QDCTRL_PHAFLTREN_MASK)

/*! @name CONF - Configuration */
#define FTM_CONF_NUMTOF_MASK                     (0x1FU)
#define FTM_CONF_NUMTOF_SHIFT                    (0U)
#define FTM_CONF_NUMTOF(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_CONF_NUMTOF_SHIFT)) & FTM_CONF_NUMTOF_MASK)
#define FTM_CONF_BDMMODE_MASK                    (0xC0U)
#define FTM_CONF_BDMMODE_SHIFT                   (6U)
#define FTM_CONF_BDMMODE(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_CONF_BDMMODE_SHIFT)) & FTM_CONF_BDMMODE_MASK)
#define FTM_CONF_GTBEEN_MASK                     (0x200U)
#define FTM_CONF_GTBEEN_SHIFT                    (9U)
#define FTM_CONF_GTBEEN(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_CONF_GTBEEN_SHIFT)) & FTM_CONF_GTBEEN_MASK)
#define FTM_CONF_GTBEOUT_MASK                    (0x400U)
#define FTM_CONF_GTBEOUT_SHIFT                   (10U)
#define FTM_CONF_GTBEOUT(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_CONF_GTBEOUT_SHIFT)) & FTM_CONF_GTBEOUT_MASK)

/*! @name FLTPOL - FTM Fault Input Polarity */
#define FTM_FLTPOL_FLT0POL_MASK                  (0x1U)
#define FTM_FLTPOL_FLT0POL_SHIFT                 (0U)
#define FTM_FLTPOL_FLT0POL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_FLTPOL_FLT0POL_SHIFT)) & FTM_FLTPOL_FLT0POL_MASK)
#define FTM_FLTPOL_FLT1POL_MASK                  (0x2U)
#define FTM_FLTPOL_FLT1POL_SHIFT                 (1U)
#define FTM_FLTPOL_FLT1POL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_FLTPOL_FLT1POL_SHIFT)) & FTM_FLTPOL_FLT1POL_MASK)
#define FTM_FLTPOL_FLT2POL_MASK                  (0x4U)
#define FTM_FLTPOL_FLT2POL_SHIFT                 (2U)
#define FTM_FLTPOL_FLT2POL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_FLTPOL_FLT2POL_SHIFT)) & FTM_FLTPOL_FLT2POL_MASK)
#define FTM_FLTPOL_FLT3POL_MASK                  (0x8U)
#define FTM_FLTPOL_FLT3POL_SHIFT                 (3U)
#define FTM_FLTPOL_FLT3POL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_FLTPOL_FLT3POL_SHIFT)) & FTM_FLTPOL_FLT3POL_MASK)

/*! @name SYNCONF - Synchronization Configuration */
#define FTM_SYNCONF_HWTRIGMODE_MASK              (0x1U)
#define FTM_SYNCONF_HWTRIGMODE_SHIFT             (0U)
#define FTM_SYNCONF_HWTRIGMODE(x)                (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_HWTRIGMODE_SHIFT)) & FTM_SYNCONF_HWTRIGMODE_MASK)
#define FTM_SYNCONF_CNTINC_MASK                  (0x4U)
#define FTM_SYNCONF_CNTINC_SHIFT                 (2U)
#define FTM_SYNCONF_CNTINC(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_CNTINC_SHIFT)) & FTM_SYNCONF_CNTINC_MASK)
#define FTM_SYNCONF_INVC_MASK                    (0x10U)
#define FTM_SYNCONF_INVC_SHIFT                   (4U)
#define FTM_SYNCONF_INVC(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_INVC_SHIFT)) & FTM_SYNCONF_INVC_MASK)
#define FTM_SYNCONF_SWOC_MASK                    (0x20U)
#define FTM_SYNCONF_SWOC_SHIFT                   (5U)
#define FTM_SYNCONF_SWOC(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_SWOC_SHIFT)) & FTM_SYNCONF_SWOC_MASK)
#define FTM_SYNCONF_SYNCMODE_MASK                (0x80U)
#define FTM_SYNCONF_SYNCMODE_SHIFT               (7U)
#define FTM_SYNCONF_SYNCMODE(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_SYNCMODE_SHIFT)) & FTM_SYNCONF_SYNCMODE_MASK)
#define FTM_SYNCONF_SWRSTCNT_MASK                (0x100U)
#define FTM_SYNCONF_SWRSTCNT_SHIFT               (8U)
#define FTM_SYNCONF_SWRSTCNT(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_SWRSTCNT_SHIFT)) & FTM_SYNCONF_SWRSTCNT_MASK)
#define FTM_SYNCONF_SWWRBUF_MASK                 (0x200U)
#define FTM_SYNCONF_SWWRBUF_SHIFT                (9U)
#define FTM_SYNCONF_SWWRBUF(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_SWWRBUF_SHIFT)) & FTM_SYNCONF_SWWRBUF_MASK)
#define FTM_SYNCONF_SWOM_MASK                    (0x400U)
#define FTM_SYNCONF_SWOM_SHIFT                   (10U)
#define FTM_SYNCONF_SWOM(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_SWOM_SHIFT)) & FTM_SYNCONF_SWOM_MASK)
#define FTM_SYNCONF_SWINVC_MASK                  (0x800U)
#define FTM_SYNCONF_SWINVC_SHIFT                 (11U)
#define FTM_SYNCONF_SWINVC(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_SWINVC_SHIFT)) & FTM_SYNCONF_SWINVC_MASK)
#define FTM_SYNCONF_SWSOC_MASK                   (0x1000U)
#define FTM_SYNCONF_SWSOC_SHIFT                  (12U)
#define FTM_SYNCONF_SWSOC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_SWSOC_SHIFT)) & FTM_SYNCONF_SWSOC_MASK)
#define FTM_SYNCONF_HWRSTCNT_MASK                (0x10000U)
#define FTM_SYNCONF_HWRSTCNT_SHIFT               (16U)
#define FTM_SYNCONF_HWRSTCNT(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_HWRSTCNT_SHIFT)) & FTM_SYNCONF_HWRSTCNT_MASK)
#define FTM_SYNCONF_HWWRBUF_MASK                 (0x20000U)
#define FTM_SYNCONF_HWWRBUF_SHIFT                (17U)
#define FTM_SYNCONF_HWWRBUF(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_HWWRBUF_SHIFT)) & FTM_SYNCONF_HWWRBUF_MASK)
#define FTM_SYNCONF_HWOM_MASK                    (0x40000U)
#define FTM_SYNCONF_HWOM_SHIFT                   (18U)
#define FTM_SYNCONF_HWOM(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_HWOM_SHIFT)) & FTM_SYNCONF_HWOM_MASK)
#define FTM_SYNCONF_HWINVC_MASK                  (0x80000U)
#define FTM_SYNCONF_HWINVC_SHIFT                 (19U)
#define FTM_SYNCONF_HWINVC(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_HWINVC_SHIFT)) & FTM_SYNCONF_HWINVC_MASK)
#define FTM_SYNCONF_HWSOC_MASK                   (0x100000U)
#define FTM_SYNCONF_HWSOC_SHIFT                  (20U)
#define FTM_SYNCONF_HWSOC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_HWSOC_SHIFT)) & FTM_SYNCONF_HWSOC_MASK)

/*! @name INVCTRL - FTM Inverting Control */
#define FTM_INVCTRL_INV0EN_MASK                  (0x1U)
#define FTM_INVCTRL_INV0EN_SHIFT                 (0U)
#define FTM_INVCTRL_INV0EN(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_INVCTRL_INV0EN_SHIFT)) & FTM_INVCTRL_INV0EN_MASK)
#define FTM_INVCTRL_INV1EN_MASK                  (0x2U)
#define FTM_INVCTRL_INV1EN_SHIFT                 (1U)
#define FTM_INVCTRL_INV1EN(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_INVCTRL_INV1EN_SHIFT)) & FTM_INVCTRL_INV1EN_MASK)
#define FTM_INVCTRL_INV2EN_MASK                  (0x4U)
#define FTM_INVCTRL_INV2EN_SHIFT                 (2U)
#define FTM_INVCTRL_INV2EN(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_INVCTRL_INV2EN_SHIFT)) & FTM_INVCTRL_INV2EN_MASK)
#define FTM_INVCTRL_INV3EN_MASK                  (0x8U)
#define FTM_INVCTRL_INV3EN_SHIFT                 (3U)
#define FTM_INVCTRL_INV3EN(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_INVCTRL_INV3EN_SHIFT)) & FTM_INVCTRL_INV3EN_MASK)

/*! @name SWOCTRL - FTM Software Output Control */
#define FTM_SWOCTRL_CH0OC_MASK                   (0x1U)
#define FTM_SWOCTRL_CH0OC_SHIFT                  (0U)
#define FTM_SWOCTRL_CH0OC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH0OC_SHIFT)) & FTM_SWOCTRL_CH0OC_MASK)
#define FTM_SWOCTRL_CH1OC_MASK                   (0x2U)
#define FTM_SWOCTRL_CH1OC_SHIFT                  (1U)
#define FTM_SWOCTRL_CH1OC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH1OC_SHIFT)) & FTM_SWOCTRL_CH1OC_MASK)
#define FTM_SWOCTRL_CH2OC_MASK                   (0x4U)
#define FTM_SWOCTRL_CH2OC_SHIFT                  (2U)
#define FTM_SWOCTRL_CH2OC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH2OC_SHIFT)) & FTM_SWOCTRL_CH2OC_MASK)
#define FTM_SWOCTRL_CH3OC_MASK                   (0x8U)
#define FTM_SWOCTRL_CH3OC_SHIFT                  (3U)
#define FTM_SWOCTRL_CH3OC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH3OC_SHIFT)) & FTM_SWOCTRL_CH3OC_MASK)
#define FTM_SWOCTRL_CH4OC_MASK                   (0x10U)
#define FTM_SWOCTRL_CH4OC_SHIFT                  (4U)
#define FTM_SWOCTRL_CH4OC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH4OC_SHIFT)) & FTM_SWOCTRL_CH4OC_MASK)
#define FTM_SWOCTRL_CH5OC_MASK                   (0x20U)
#define FTM_SWOCTRL_CH5OC_SHIFT                  (5U)
#define FTM_SWOCTRL_CH5OC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH5OC_SHIFT)) & FTM_SWOCTRL_CH5OC_MASK)
#define FTM_SWOCTRL_CH6OC_MASK                   (0x40U)
#define FTM_SWOCTRL_CH6OC_SHIFT                  (6U)
#define FTM_SWOCTRL_CH6OC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH6OC_SHIFT)) & FTM_SWOCTRL_CH6OC_MASK)
#define FTM_SWOCTRL_CH7OC_MASK                   (0x80U)
#define FTM_SWOCTRL_CH7OC_SHIFT                  (7U)
#define FTM_SWOCTRL_CH7OC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH7OC_SHIFT)) & FTM_SWOCTRL_CH7OC_MASK)
#define FTM_SWOCTRL_CH0OCV_MASK                  (0x100U)
#define FTM_SWOCTRL_CH0OCV_SHIFT                 (8U)
#define FTM_SWOCTRL_CH0OCV(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH0OCV_SHIFT)) & FTM_SWOCTRL_CH0OCV_MASK)
#define FTM_SWOCTRL_CH1OCV_MASK                  (0x200U)
#define FTM_SWOCTRL_CH1OCV_SHIFT                 (9U)
#define FTM_SWOCTRL_CH1OCV(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH1OCV_SHIFT)) & FTM_SWOCTRL_CH1OCV_MASK)
#define FTM_SWOCTRL_CH2OCV_MASK                  (0x400U)
#define FTM_SWOCTRL_CH2OCV_SHIFT                 (10U)
#define FTM_SWOCTRL_CH2OCV(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH2OCV_SHIFT)) & FTM_SWOCTRL_CH2OCV_MASK)
#define FTM_SWOCTRL_CH3OCV_MASK                  (0x800U)
#define FTM_SWOCTRL_CH3OCV_SHIFT                 (11U)
#define FTM_SWOCTRL_CH3OCV(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH3OCV_SHIFT)) & FTM_SWOCTRL_CH3OCV_MASK)
#define FTM_SWOCTRL_CH4OCV_MASK                  (0x1000U)
#define FTM_SWOCTRL_CH4OCV_SHIFT                 (12U)
#define FTM_SWOCTRL_CH4OCV(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH4OCV_SHIFT)) & FTM_SWOCTRL_CH4OCV_MASK)
#define FTM_SWOCTRL_CH5OCV_MASK                  (0x2000U)
#define FTM_SWOCTRL_CH5OCV_SHIFT                 (13U)
#define FTM_SWOCTRL_CH5OCV(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH5OCV_SHIFT)) & FTM_SWOCTRL_CH5OCV_MASK)
#define FTM_SWOCTRL_CH6OCV_MASK                  (0x4000U)
#define FTM_SWOCTRL_CH6OCV_SHIFT                 (14U)
#define FTM_SWOCTRL_CH6OCV(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH6OCV_SHIFT)) & FTM_SWOCTRL_CH6OCV_MASK)
#define FTM_SWOCTRL_CH7OCV_MASK                  (0x8000U)
#define FTM_SWOCTRL_CH7OCV_SHIFT                 (15U)
#define FTM_SWOCTRL_CH7OCV(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH7OCV_SHIFT)) & FTM_SWOCTRL_CH7OCV_MASK)

/*! @name PWMLOAD - FTM PWM Load */
#define FTM_PWMLOAD_CH0SEL_MASK                  (0x1U)
#define FTM_PWMLOAD_CH0SEL_SHIFT                 (0U)
#define FTM_PWMLOAD_CH0SEL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_CH0SEL_SHIFT)) & FTM_PWMLOAD_CH0SEL_MASK)
#define FTM_PWMLOAD_CH1SEL_MASK                  (0x2U)
#define FTM_PWMLOAD_CH1SEL_SHIFT                 (1U)
#define FTM_PWMLOAD_CH1SEL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_CH1SEL_SHIFT)) & FTM_PWMLOAD_CH1SEL_MASK)
#define FTM_PWMLOAD_CH2SEL_MASK                  (0x4U)
#define FTM_PWMLOAD_CH2SEL_SHIFT                 (2U)
#define FTM_PWMLOAD_CH2SEL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_CH2SEL_SHIFT)) & FTM_PWMLOAD_CH2SEL_MASK)
#define FTM_PWMLOAD_CH3SEL_MASK                  (0x8U)
#define FTM_PWMLOAD_CH3SEL_SHIFT                 (3U)
#define FTM_PWMLOAD_CH3SEL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_CH3SEL_SHIFT)) & FTM_PWMLOAD_CH3SEL_MASK)
#define FTM_PWMLOAD_CH4SEL_MASK                  (0x10U)
#define FTM_PWMLOAD_CH4SEL_SHIFT                 (4U)
#define FTM_PWMLOAD_CH4SEL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_CH4SEL_SHIFT)) & FTM_PWMLOAD_CH4SEL_MASK)
#define FTM_PWMLOAD_CH5SEL_MASK                  (0x20U)
#define FTM_PWMLOAD_CH5SEL_SHIFT                 (5U)
#define FTM_PWMLOAD_CH5SEL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_CH5SEL_SHIFT)) & FTM_PWMLOAD_CH5SEL_MASK)
#define FTM_PWMLOAD_CH6SEL_MASK                  (0x40U)
#define FTM_PWMLOAD_CH6SEL_SHIFT                 (6U)
#define FTM_PWMLOAD_CH6SEL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_CH6SEL_SHIFT)) & FTM_PWMLOAD_CH6SEL_MASK)
#define FTM_PWMLOAD_CH7SEL_MASK                  (0x80U)
#define FTM_PWMLOAD_CH7SEL_SHIFT                 (7U)
#define FTM_PWMLOAD_CH7SEL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_CH7SEL_SHIFT)) & FTM_PWMLOAD_CH7SEL_MASK)
#define FTM_PWMLOAD_LDOK_MASK                    (0x200U)
#define FTM_PWMLOAD_LDOK_SHIFT                   (9U)
#define FTM_PWMLOAD_LDOK(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_LDOK_SHIFT)) & FTM_PWMLOAD_LDOK_MASK)


/*!
 * @}
 */ /* end of group FTM_Register_Masks */


/* FTM - Peripheral instance base addresses */
/** Peripheral FTM0 base address */
#define FTM0_BASE                                (0x40038000u)
/** Peripheral FTM0 base pointer */
#define FTM0                                     ((FTM_Type *)FTM0_BASE)
/** Peripheral FTM1 base address */
#define FTM1_BASE                                (0x40039000u)
/** Peripheral FTM1 base pointer */
#define FTM1                                     ((FTM_Type *)FTM1_BASE)
/** Peripheral FTM2 base address */
#define FTM2_BASE                                (0x4003A000u)
/** Peripheral FTM2 base pointer */
#define FTM2                                     ((FTM_Type *)FTM2_BASE)
/** Peripheral FTM3 base address */
#define FTM3_BASE                                (0x40026000u)
/** Peripheral FTM3 base pointer */
#define FTM3                                     ((FTM_Type *)FTM3_BASE)
/** Array initializer of FTM peripheral base addresses */
#define FTM_BASE_ADDRS                           { FTM0_BASE, FTM1_BASE, FTM2_BASE, FTM3_BASE }
/** Array initializer of FTM peripheral base pointers */
#define FTM_BASE_PTRS                            { FTM0, FTM1, FTM2, FTM3 }
/** Interrupt vectors for the FTM peripheral type */
#define FTM_IRQS                                 { FTM0_IRQn, FTM1_IRQn, FTM2_IRQn, FTM3_IRQn }

/*!
 * @}
 */ /* end of group FTM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- GPIO Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Peripheral_Access_Layer GPIO Peripheral Access Layer
 * @{
 */

/** GPIO - Register Layout Typedef */
typedef struct {
  __IO uint32_t PDOR;                              /**< Port Data Output Register, offset: 0x0 */
  __O  uint32_t PSOR;                              /**< Port Set Output Register, offset: 0x4 */
  __O  uint32_t PCOR;                              /**< Port Clear Output Register, offset: 0x8 */
  __O  uint32_t PTOR;                              /**< Port Toggle Output Register, offset: 0xC */
  __I  uint32_t PDIR;                              /**< Port Data Input Register, offset: 0x10 */
  __IO uint32_t PDDR;                              /**< Port Data Direction Register, offset: 0x14 */
} GPIO_Type;

/* ----------------------------------------------------------------------------
   -- GPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Masks GPIO Register Masks
 * @{
 */

/*! @name PDOR - Port Data Output Register */
#define GPIO_PDOR_PDO_MASK                       (0xFFFFFFFFU)
#define GPIO_PDOR_PDO_SHIFT                      (0U)
#define GPIO_PDOR_PDO(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_PDOR_PDO_SHIFT)) & GPIO_PDOR_PDO_MASK)

/*! @name PSOR - Port Set Output Register */
#define GPIO_PSOR_PTSO_MASK                      (0xFFFFFFFFU)
#define GPIO_PSOR_PTSO_SHIFT                     (0U)
#define GPIO_PSOR_PTSO(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_PSOR_PTSO_SHIFT)) & GPIO_PSOR_PTSO_MASK)

/*! @name PCOR - Port Clear Output Register */
#define GPIO_PCOR_PTCO_MASK                      (0xFFFFFFFFU)
#define GPIO_PCOR_PTCO_SHIFT                     (0U)
#define GPIO_PCOR_PTCO(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_PCOR_PTCO_SHIFT)) & GPIO_PCOR_PTCO_MASK)

/*! @name PTOR - Port Toggle Output Register */
#define GPIO_PTOR_PTTO_MASK                      (0xFFFFFFFFU)
#define GPIO_PTOR_PTTO_SHIFT                     (0U)
#define GPIO_PTOR_PTTO(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_PTOR_PTTO_SHIFT)) & GPIO_PTOR_PTTO_MASK)

/*! @name PDIR - Port Data Input Register */
#define GPIO_PDIR_PDI_MASK                       (0xFFFFFFFFU)
#define GPIO_PDIR_PDI_SHIFT                      (0U)
#define GPIO_PDIR_PDI(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_PDIR_PDI_SHIFT)) & GPIO_PDIR_PDI_MASK)

/*! @name PDDR - Port Data Direction Register */
#define GPIO_PDDR_PDD_MASK                       (0xFFFFFFFFU)
#define GPIO_PDDR_PDD_SHIFT                      (0U)
#define GPIO_PDDR_PDD(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_PDDR_PDD_SHIFT)) & GPIO_PDDR_PDD_MASK)


/*!
 * @}
 */ /* end of group GPIO_Register_Masks */


/* GPIO - Peripheral instance base addresses */
/** Peripheral GPIOA base address */
#define GPIOA_BASE                               (0x400FF000u)
/** Peripheral GPIOA base pointer */
#define GPIOA                                    ((GPIO_Type *)GPIOA_BASE)
/** Peripheral GPIOB base address */
#define GPIOB_BASE                               (0x400FF040u)
/** Peripheral GPIOB base pointer */
#define GPIOB                                    ((GPIO_Type *)GPIOB_BASE)
/** Peripheral GPIOC base address */
#define GPIOC_BASE                               (0x400FF080u)
/** Peripheral GPIOC base pointer */
#define GPIOC                                    ((GPIO_Type *)GPIOC_BASE)
/** Peripheral GPIOD base address */
#define GPIOD_BASE                               (0x400FF0C0u)
/** Peripheral GPIOD base pointer */
#define GPIOD                                    ((GPIO_Type *)GPIOD_BASE)
/** Peripheral GPIOE base address */
#define GPIOE_BASE                               (0x400FF100u)
/** Peripheral GPIOE base pointer */
#define GPIOE                                    ((GPIO_Type *)GPIOE_BASE)
/** Array initializer of GPIO peripheral base addresses */
#define GPIO_BASE_ADDRS                          { GPIOA_BASE, GPIOB_BASE, GPIOC_BASE, GPIOD_BASE, GPIOE_BASE }
/** Array initializer of GPIO peripheral base pointers */
#define GPIO_BASE_PTRS                           { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE }

/*!
 * @}
 */ /* end of group GPIO_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- HSADC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup HSADC_Peripheral_Access_Layer HSADC Peripheral Access Layer
 * @{
 */

/** HSADC - Register Layout Typedef */
typedef struct {
  __IO uint16_t CTRL1;                             /**< HSADC Control Register 1, offset: 0x0 */
  __IO uint16_t CTRL2;                             /**< HSADC Control Register 2, offset: 0x2 */
  __IO uint16_t ZXCTRL1;                           /**< HSADC Zero Crossing Control 1 Register, offset: 0x4 */
  __IO uint16_t ZXCTRL2;                           /**< HSADC Zero Crossing Control 2 Register, offset: 0x6 */
  __IO uint16_t CLIST1;                            /**< HSADC Channel List Register 1, offset: 0x8 */
  __IO uint16_t CLIST2;                            /**< HSADC Channel List Register 2, offset: 0xA */
  __IO uint16_t CLIST3;                            /**< HSADC Channel List Register 3, offset: 0xC */
  __IO uint16_t CLIST4;                            /**< HSADC Channel List Register 4, offset: 0xE */
  __IO uint16_t SDIS;                              /**< HSADC Sample Disable Register, offset: 0x10 */
  __IO uint16_t STAT;                              /**< HSADC Status Register, offset: 0x12 */
  __I  uint16_t RDY;                               /**< HSADC Ready Register, offset: 0x14 */
  __IO uint16_t LOLIMSTAT;                         /**< HSADC Low Limit Status Register, offset: 0x16 */
  __IO uint16_t HILIMSTAT;                         /**< HSADC High Limit Status Register, offset: 0x18 */
  __IO uint16_t ZXSTAT;                            /**< HSADC Zero Crossing Status Register, offset: 0x1A */
  __IO uint16_t RSLT[16];                          /**< HSADC Result Registers with sign extension, array offset: 0x1C, array step: 0x2 */
  __IO uint16_t LOLIM[16];                         /**< HSADC Low Limit Registers, array offset: 0x3C, array step: 0x2 */
  __IO uint16_t HILIM[16];                         /**< HSADC High Limit Registers, array offset: 0x5C, array step: 0x2 */
  __IO uint16_t OFFST[16];                         /**< HSADC Offset Register, array offset: 0x7C, array step: 0x2 */
  __IO uint16_t PWR;                               /**< HSADC Power Control Register, offset: 0x9C */
       uint8_t RESERVED_0[6];
  __IO uint16_t SCTRL;                             /**< HSADC Scan Control Register, offset: 0xA4 */
  __IO uint16_t PWR2;                              /**< HSADC Power Control Register 2, offset: 0xA6 */
  __IO uint16_t CTRL3;                             /**< HSADC Control Register 3, offset: 0xA8 */
  __IO uint16_t SCINTEN;                           /**< HSADC Scan Interrupt Enable Register, offset: 0xAA */
  __IO uint16_t SAMPTIM;                           /**< HSADC Sampling Time Configuration Register, offset: 0xAC */
  __IO uint16_t CALIB;                             /**< HSADCs Calibration Configuration, offset: 0xAE */
  __IO uint16_t CALVAL_A;                          /**< Calibration Values for ADCA Register, offset: 0xB0 */
  __IO uint16_t CALVAL_B;                          /**< Calibration Values for ADCB Register, offset: 0xB2 */
       uint8_t RESERVED_1[6];
  __IO uint16_t MUX67_SEL;                         /**< MUX6_7 Selection Controls Register, offset: 0xBA */
} HSADC_Type;

/* ----------------------------------------------------------------------------
   -- HSADC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup HSADC_Register_Masks HSADC Register Masks
 * @{
 */

/*! @name CTRL1 - HSADC Control Register 1 */
#define HSADC_CTRL1_SMODE_MASK                   (0x7U)
#define HSADC_CTRL1_SMODE_SHIFT                  (0U)
#define HSADC_CTRL1_SMODE(x)                     (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL1_SMODE_SHIFT)) & HSADC_CTRL1_SMODE_MASK)
#define HSADC_CTRL1_CHNCFG_L_MASK                (0xF0U)
#define HSADC_CTRL1_CHNCFG_L_SHIFT               (4U)
#define HSADC_CTRL1_CHNCFG_L(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL1_CHNCFG_L_SHIFT)) & HSADC_CTRL1_CHNCFG_L_MASK)
#define HSADC_CTRL1_HLMTIE_MASK                  (0x100U)
#define HSADC_CTRL1_HLMTIE_SHIFT                 (8U)
#define HSADC_CTRL1_HLMTIE(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL1_HLMTIE_SHIFT)) & HSADC_CTRL1_HLMTIE_MASK)
#define HSADC_CTRL1_LLMTIE_MASK                  (0x200U)
#define HSADC_CTRL1_LLMTIE_SHIFT                 (9U)
#define HSADC_CTRL1_LLMTIE(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL1_LLMTIE_SHIFT)) & HSADC_CTRL1_LLMTIE_MASK)
#define HSADC_CTRL1_ZCIE_MASK                    (0x400U)
#define HSADC_CTRL1_ZCIE_SHIFT                   (10U)
#define HSADC_CTRL1_ZCIE(x)                      (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL1_ZCIE_SHIFT)) & HSADC_CTRL1_ZCIE_MASK)
#define HSADC_CTRL1_EOSIEA_MASK                  (0x800U)
#define HSADC_CTRL1_EOSIEA_SHIFT                 (11U)
#define HSADC_CTRL1_EOSIEA(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL1_EOSIEA_SHIFT)) & HSADC_CTRL1_EOSIEA_MASK)
#define HSADC_CTRL1_SYNCA_MASK                   (0x1000U)
#define HSADC_CTRL1_SYNCA_SHIFT                  (12U)
#define HSADC_CTRL1_SYNCA(x)                     (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL1_SYNCA_SHIFT)) & HSADC_CTRL1_SYNCA_MASK)
#define HSADC_CTRL1_STARTA_MASK                  (0x2000U)
#define HSADC_CTRL1_STARTA_SHIFT                 (13U)
#define HSADC_CTRL1_STARTA(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL1_STARTA_SHIFT)) & HSADC_CTRL1_STARTA_MASK)
#define HSADC_CTRL1_STOPA_MASK                   (0x4000U)
#define HSADC_CTRL1_STOPA_SHIFT                  (14U)
#define HSADC_CTRL1_STOPA(x)                     (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL1_STOPA_SHIFT)) & HSADC_CTRL1_STOPA_MASK)
#define HSADC_CTRL1_DMAENA_MASK                  (0x8000U)
#define HSADC_CTRL1_DMAENA_SHIFT                 (15U)
#define HSADC_CTRL1_DMAENA(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL1_DMAENA_SHIFT)) & HSADC_CTRL1_DMAENA_MASK)

/*! @name CTRL2 - HSADC Control Register 2 */
#define HSADC_CTRL2_DIVA_MASK                    (0x3FU)
#define HSADC_CTRL2_DIVA_SHIFT                   (0U)
#define HSADC_CTRL2_DIVA(x)                      (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL2_DIVA_SHIFT)) & HSADC_CTRL2_DIVA_MASK)
#define HSADC_CTRL2_SIMULT_MASK                  (0x40U)
#define HSADC_CTRL2_SIMULT_SHIFT                 (6U)
#define HSADC_CTRL2_SIMULT(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL2_SIMULT_SHIFT)) & HSADC_CTRL2_SIMULT_MASK)
#define HSADC_CTRL2_CHNCFG_H_MASK                (0x780U)
#define HSADC_CTRL2_CHNCFG_H_SHIFT               (7U)
#define HSADC_CTRL2_CHNCFG_H(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL2_CHNCFG_H_SHIFT)) & HSADC_CTRL2_CHNCFG_H_MASK)
#define HSADC_CTRL2_EOSIEB_MASK                  (0x800U)
#define HSADC_CTRL2_EOSIEB_SHIFT                 (11U)
#define HSADC_CTRL2_EOSIEB(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL2_EOSIEB_SHIFT)) & HSADC_CTRL2_EOSIEB_MASK)
#define HSADC_CTRL2_SYNCB_MASK                   (0x1000U)
#define HSADC_CTRL2_SYNCB_SHIFT                  (12U)
#define HSADC_CTRL2_SYNCB(x)                     (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL2_SYNCB_SHIFT)) & HSADC_CTRL2_SYNCB_MASK)
#define HSADC_CTRL2_STARTB_MASK                  (0x2000U)
#define HSADC_CTRL2_STARTB_SHIFT                 (13U)
#define HSADC_CTRL2_STARTB(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL2_STARTB_SHIFT)) & HSADC_CTRL2_STARTB_MASK)
#define HSADC_CTRL2_STOPB_MASK                   (0x4000U)
#define HSADC_CTRL2_STOPB_SHIFT                  (14U)
#define HSADC_CTRL2_STOPB(x)                     (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL2_STOPB_SHIFT)) & HSADC_CTRL2_STOPB_MASK)
#define HSADC_CTRL2_DMAENB_MASK                  (0x8000U)
#define HSADC_CTRL2_DMAENB_SHIFT                 (15U)
#define HSADC_CTRL2_DMAENB(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL2_DMAENB_SHIFT)) & HSADC_CTRL2_DMAENB_MASK)

/*! @name ZXCTRL1 - HSADC Zero Crossing Control 1 Register */
#define HSADC_ZXCTRL1_ZCE0_MASK                  (0x3U)
#define HSADC_ZXCTRL1_ZCE0_SHIFT                 (0U)
#define HSADC_ZXCTRL1_ZCE0(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_ZXCTRL1_ZCE0_SHIFT)) & HSADC_ZXCTRL1_ZCE0_MASK)
#define HSADC_ZXCTRL1_ZCE1_MASK                  (0xCU)
#define HSADC_ZXCTRL1_ZCE1_SHIFT                 (2U)
#define HSADC_ZXCTRL1_ZCE1(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_ZXCTRL1_ZCE1_SHIFT)) & HSADC_ZXCTRL1_ZCE1_MASK)
#define HSADC_ZXCTRL1_ZCE2_MASK                  (0x30U)
#define HSADC_ZXCTRL1_ZCE2_SHIFT                 (4U)
#define HSADC_ZXCTRL1_ZCE2(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_ZXCTRL1_ZCE2_SHIFT)) & HSADC_ZXCTRL1_ZCE2_MASK)
#define HSADC_ZXCTRL1_ZCE3_MASK                  (0xC0U)
#define HSADC_ZXCTRL1_ZCE3_SHIFT                 (6U)
#define HSADC_ZXCTRL1_ZCE3(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_ZXCTRL1_ZCE3_SHIFT)) & HSADC_ZXCTRL1_ZCE3_MASK)
#define HSADC_ZXCTRL1_ZCE4_MASK                  (0x300U)
#define HSADC_ZXCTRL1_ZCE4_SHIFT                 (8U)
#define HSADC_ZXCTRL1_ZCE4(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_ZXCTRL1_ZCE4_SHIFT)) & HSADC_ZXCTRL1_ZCE4_MASK)
#define HSADC_ZXCTRL1_ZCE5_MASK                  (0xC00U)
#define HSADC_ZXCTRL1_ZCE5_SHIFT                 (10U)
#define HSADC_ZXCTRL1_ZCE5(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_ZXCTRL1_ZCE5_SHIFT)) & HSADC_ZXCTRL1_ZCE5_MASK)
#define HSADC_ZXCTRL1_ZCE6_MASK                  (0x3000U)
#define HSADC_ZXCTRL1_ZCE6_SHIFT                 (12U)
#define HSADC_ZXCTRL1_ZCE6(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_ZXCTRL1_ZCE6_SHIFT)) & HSADC_ZXCTRL1_ZCE6_MASK)
#define HSADC_ZXCTRL1_ZCE7_MASK                  (0xC000U)
#define HSADC_ZXCTRL1_ZCE7_SHIFT                 (14U)
#define HSADC_ZXCTRL1_ZCE7(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_ZXCTRL1_ZCE7_SHIFT)) & HSADC_ZXCTRL1_ZCE7_MASK)

/*! @name ZXCTRL2 - HSADC Zero Crossing Control 2 Register */
#define HSADC_ZXCTRL2_ZCE8_MASK                  (0x3U)
#define HSADC_ZXCTRL2_ZCE8_SHIFT                 (0U)
#define HSADC_ZXCTRL2_ZCE8(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_ZXCTRL2_ZCE8_SHIFT)) & HSADC_ZXCTRL2_ZCE8_MASK)
#define HSADC_ZXCTRL2_ZCE9_MASK                  (0xCU)
#define HSADC_ZXCTRL2_ZCE9_SHIFT                 (2U)
#define HSADC_ZXCTRL2_ZCE9(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_ZXCTRL2_ZCE9_SHIFT)) & HSADC_ZXCTRL2_ZCE9_MASK)
#define HSADC_ZXCTRL2_ZCE10_MASK                 (0x30U)
#define HSADC_ZXCTRL2_ZCE10_SHIFT                (4U)
#define HSADC_ZXCTRL2_ZCE10(x)                   (((uint16_t)(((uint16_t)(x)) << HSADC_ZXCTRL2_ZCE10_SHIFT)) & HSADC_ZXCTRL2_ZCE10_MASK)
#define HSADC_ZXCTRL2_ZCE11_MASK                 (0xC0U)
#define HSADC_ZXCTRL2_ZCE11_SHIFT                (6U)
#define HSADC_ZXCTRL2_ZCE11(x)                   (((uint16_t)(((uint16_t)(x)) << HSADC_ZXCTRL2_ZCE11_SHIFT)) & HSADC_ZXCTRL2_ZCE11_MASK)
#define HSADC_ZXCTRL2_ZCE12_MASK                 (0x300U)
#define HSADC_ZXCTRL2_ZCE12_SHIFT                (8U)
#define HSADC_ZXCTRL2_ZCE12(x)                   (((uint16_t)(((uint16_t)(x)) << HSADC_ZXCTRL2_ZCE12_SHIFT)) & HSADC_ZXCTRL2_ZCE12_MASK)
#define HSADC_ZXCTRL2_ZCE13_MASK                 (0xC00U)
#define HSADC_ZXCTRL2_ZCE13_SHIFT                (10U)
#define HSADC_ZXCTRL2_ZCE13(x)                   (((uint16_t)(((uint16_t)(x)) << HSADC_ZXCTRL2_ZCE13_SHIFT)) & HSADC_ZXCTRL2_ZCE13_MASK)
#define HSADC_ZXCTRL2_ZCE14_MASK                 (0x3000U)
#define HSADC_ZXCTRL2_ZCE14_SHIFT                (12U)
#define HSADC_ZXCTRL2_ZCE14(x)                   (((uint16_t)(((uint16_t)(x)) << HSADC_ZXCTRL2_ZCE14_SHIFT)) & HSADC_ZXCTRL2_ZCE14_MASK)
#define HSADC_ZXCTRL2_ZCE15_MASK                 (0xC000U)
#define HSADC_ZXCTRL2_ZCE15_SHIFT                (14U)
#define HSADC_ZXCTRL2_ZCE15(x)                   (((uint16_t)(((uint16_t)(x)) << HSADC_ZXCTRL2_ZCE15_SHIFT)) & HSADC_ZXCTRL2_ZCE15_MASK)

/*! @name CLIST1 - HSADC Channel List Register 1 */
#define HSADC_CLIST1_SAMPLE0_MASK                (0xFU)
#define HSADC_CLIST1_SAMPLE0_SHIFT               (0U)
#define HSADC_CLIST1_SAMPLE0(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CLIST1_SAMPLE0_SHIFT)) & HSADC_CLIST1_SAMPLE0_MASK)
#define HSADC_CLIST1_SAMPLE1_MASK                (0xF0U)
#define HSADC_CLIST1_SAMPLE1_SHIFT               (4U)
#define HSADC_CLIST1_SAMPLE1(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CLIST1_SAMPLE1_SHIFT)) & HSADC_CLIST1_SAMPLE1_MASK)
#define HSADC_CLIST1_SAMPLE2_MASK                (0xF00U)
#define HSADC_CLIST1_SAMPLE2_SHIFT               (8U)
#define HSADC_CLIST1_SAMPLE2(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CLIST1_SAMPLE2_SHIFT)) & HSADC_CLIST1_SAMPLE2_MASK)
#define HSADC_CLIST1_SAMPLE3_MASK                (0xF000U)
#define HSADC_CLIST1_SAMPLE3_SHIFT               (12U)
#define HSADC_CLIST1_SAMPLE3(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CLIST1_SAMPLE3_SHIFT)) & HSADC_CLIST1_SAMPLE3_MASK)

/*! @name CLIST2 - HSADC Channel List Register 2 */
#define HSADC_CLIST2_SAMPLE4_MASK                (0xFU)
#define HSADC_CLIST2_SAMPLE4_SHIFT               (0U)
#define HSADC_CLIST2_SAMPLE4(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CLIST2_SAMPLE4_SHIFT)) & HSADC_CLIST2_SAMPLE4_MASK)
#define HSADC_CLIST2_SAMPLE5_MASK                (0xF0U)
#define HSADC_CLIST2_SAMPLE5_SHIFT               (4U)
#define HSADC_CLIST2_SAMPLE5(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CLIST2_SAMPLE5_SHIFT)) & HSADC_CLIST2_SAMPLE5_MASK)
#define HSADC_CLIST2_SAMPLE6_MASK                (0xF00U)
#define HSADC_CLIST2_SAMPLE6_SHIFT               (8U)
#define HSADC_CLIST2_SAMPLE6(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CLIST2_SAMPLE6_SHIFT)) & HSADC_CLIST2_SAMPLE6_MASK)
#define HSADC_CLIST2_SAMPLE7_MASK                (0xF000U)
#define HSADC_CLIST2_SAMPLE7_SHIFT               (12U)
#define HSADC_CLIST2_SAMPLE7(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CLIST2_SAMPLE7_SHIFT)) & HSADC_CLIST2_SAMPLE7_MASK)

/*! @name CLIST3 - HSADC Channel List Register 3 */
#define HSADC_CLIST3_SAMPLE8_MASK                (0xFU)
#define HSADC_CLIST3_SAMPLE8_SHIFT               (0U)
#define HSADC_CLIST3_SAMPLE8(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CLIST3_SAMPLE8_SHIFT)) & HSADC_CLIST3_SAMPLE8_MASK)
#define HSADC_CLIST3_SAMPLE9_MASK                (0xF0U)
#define HSADC_CLIST3_SAMPLE9_SHIFT               (4U)
#define HSADC_CLIST3_SAMPLE9(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CLIST3_SAMPLE9_SHIFT)) & HSADC_CLIST3_SAMPLE9_MASK)
#define HSADC_CLIST3_SAMPLE10_MASK               (0xF00U)
#define HSADC_CLIST3_SAMPLE10_SHIFT              (8U)
#define HSADC_CLIST3_SAMPLE10(x)                 (((uint16_t)(((uint16_t)(x)) << HSADC_CLIST3_SAMPLE10_SHIFT)) & HSADC_CLIST3_SAMPLE10_MASK)
#define HSADC_CLIST3_SAMPLE11_MASK               (0xF000U)
#define HSADC_CLIST3_SAMPLE11_SHIFT              (12U)
#define HSADC_CLIST3_SAMPLE11(x)                 (((uint16_t)(((uint16_t)(x)) << HSADC_CLIST3_SAMPLE11_SHIFT)) & HSADC_CLIST3_SAMPLE11_MASK)

/*! @name CLIST4 - HSADC Channel List Register 4 */
#define HSADC_CLIST4_SAMPLE12_MASK               (0xFU)
#define HSADC_CLIST4_SAMPLE12_SHIFT              (0U)
#define HSADC_CLIST4_SAMPLE12(x)                 (((uint16_t)(((uint16_t)(x)) << HSADC_CLIST4_SAMPLE12_SHIFT)) & HSADC_CLIST4_SAMPLE12_MASK)
#define HSADC_CLIST4_SAMPLE13_MASK               (0xF0U)
#define HSADC_CLIST4_SAMPLE13_SHIFT              (4U)
#define HSADC_CLIST4_SAMPLE13(x)                 (((uint16_t)(((uint16_t)(x)) << HSADC_CLIST4_SAMPLE13_SHIFT)) & HSADC_CLIST4_SAMPLE13_MASK)
#define HSADC_CLIST4_SAMPLE14_MASK               (0xF00U)
#define HSADC_CLIST4_SAMPLE14_SHIFT              (8U)
#define HSADC_CLIST4_SAMPLE14(x)                 (((uint16_t)(((uint16_t)(x)) << HSADC_CLIST4_SAMPLE14_SHIFT)) & HSADC_CLIST4_SAMPLE14_MASK)
#define HSADC_CLIST4_SAMPLE15_MASK               (0xF000U)
#define HSADC_CLIST4_SAMPLE15_SHIFT              (12U)
#define HSADC_CLIST4_SAMPLE15(x)                 (((uint16_t)(((uint16_t)(x)) << HSADC_CLIST4_SAMPLE15_SHIFT)) & HSADC_CLIST4_SAMPLE15_MASK)

/*! @name SDIS - HSADC Sample Disable Register */
#define HSADC_SDIS_DS_MASK                       (0xFFFFU)
#define HSADC_SDIS_DS_SHIFT                      (0U)
#define HSADC_SDIS_DS(x)                         (((uint16_t)(((uint16_t)(x)) << HSADC_SDIS_DS_SHIFT)) & HSADC_SDIS_DS_MASK)

/*! @name STAT - HSADC Status Register */
#define HSADC_STAT_CALONA_MASK                   (0x1U)
#define HSADC_STAT_CALONA_SHIFT                  (0U)
#define HSADC_STAT_CALONA(x)                     (((uint16_t)(((uint16_t)(x)) << HSADC_STAT_CALONA_SHIFT)) & HSADC_STAT_CALONA_MASK)
#define HSADC_STAT_CALONB_MASK                   (0x2U)
#define HSADC_STAT_CALONB_SHIFT                  (1U)
#define HSADC_STAT_CALONB(x)                     (((uint16_t)(((uint16_t)(x)) << HSADC_STAT_CALONB_SHIFT)) & HSADC_STAT_CALONB_MASK)
#define HSADC_STAT_DUMMYA_MASK                   (0x4U)
#define HSADC_STAT_DUMMYA_SHIFT                  (2U)
#define HSADC_STAT_DUMMYA(x)                     (((uint16_t)(((uint16_t)(x)) << HSADC_STAT_DUMMYA_SHIFT)) & HSADC_STAT_DUMMYA_MASK)
#define HSADC_STAT_DUMMYB_MASK                   (0x8U)
#define HSADC_STAT_DUMMYB_SHIFT                  (3U)
#define HSADC_STAT_DUMMYB(x)                     (((uint16_t)(((uint16_t)(x)) << HSADC_STAT_DUMMYB_SHIFT)) & HSADC_STAT_DUMMYB_MASK)
#define HSADC_STAT_EOCALIA_MASK                  (0x10U)
#define HSADC_STAT_EOCALIA_SHIFT                 (4U)
#define HSADC_STAT_EOCALIA(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_STAT_EOCALIA_SHIFT)) & HSADC_STAT_EOCALIA_MASK)
#define HSADC_STAT_EOCALIB_MASK                  (0x20U)
#define HSADC_STAT_EOCALIB_SHIFT                 (5U)
#define HSADC_STAT_EOCALIB(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_STAT_EOCALIB_SHIFT)) & HSADC_STAT_EOCALIB_MASK)
#define HSADC_STAT_HLMTI_MASK                    (0x100U)
#define HSADC_STAT_HLMTI_SHIFT                   (8U)
#define HSADC_STAT_HLMTI(x)                      (((uint16_t)(((uint16_t)(x)) << HSADC_STAT_HLMTI_SHIFT)) & HSADC_STAT_HLMTI_MASK)
#define HSADC_STAT_LLMTI_MASK                    (0x200U)
#define HSADC_STAT_LLMTI_SHIFT                   (9U)
#define HSADC_STAT_LLMTI(x)                      (((uint16_t)(((uint16_t)(x)) << HSADC_STAT_LLMTI_SHIFT)) & HSADC_STAT_LLMTI_MASK)
#define HSADC_STAT_ZCI_MASK                      (0x400U)
#define HSADC_STAT_ZCI_SHIFT                     (10U)
#define HSADC_STAT_ZCI(x)                        (((uint16_t)(((uint16_t)(x)) << HSADC_STAT_ZCI_SHIFT)) & HSADC_STAT_ZCI_MASK)
#define HSADC_STAT_EOSIA_MASK                    (0x800U)
#define HSADC_STAT_EOSIA_SHIFT                   (11U)
#define HSADC_STAT_EOSIA(x)                      (((uint16_t)(((uint16_t)(x)) << HSADC_STAT_EOSIA_SHIFT)) & HSADC_STAT_EOSIA_MASK)
#define HSADC_STAT_EOSIB_MASK                    (0x1000U)
#define HSADC_STAT_EOSIB_SHIFT                   (12U)
#define HSADC_STAT_EOSIB(x)                      (((uint16_t)(((uint16_t)(x)) << HSADC_STAT_EOSIB_SHIFT)) & HSADC_STAT_EOSIB_MASK)
#define HSADC_STAT_CIPB_MASK                     (0x4000U)
#define HSADC_STAT_CIPB_SHIFT                    (14U)
#define HSADC_STAT_CIPB(x)                       (((uint16_t)(((uint16_t)(x)) << HSADC_STAT_CIPB_SHIFT)) & HSADC_STAT_CIPB_MASK)
#define HSADC_STAT_CIPA_MASK                     (0x8000U)
#define HSADC_STAT_CIPA_SHIFT                    (15U)
#define HSADC_STAT_CIPA(x)                       (((uint16_t)(((uint16_t)(x)) << HSADC_STAT_CIPA_SHIFT)) & HSADC_STAT_CIPA_MASK)

/*! @name RDY - HSADC Ready Register */
#define HSADC_RDY_RDY_MASK                       (0xFFFFU)
#define HSADC_RDY_RDY_SHIFT                      (0U)
#define HSADC_RDY_RDY(x)                         (((uint16_t)(((uint16_t)(x)) << HSADC_RDY_RDY_SHIFT)) & HSADC_RDY_RDY_MASK)

/*! @name LOLIMSTAT - HSADC Low Limit Status Register */
#define HSADC_LOLIMSTAT_LLS_MASK                 (0xFFFFU)
#define HSADC_LOLIMSTAT_LLS_SHIFT                (0U)
#define HSADC_LOLIMSTAT_LLS(x)                   (((uint16_t)(((uint16_t)(x)) << HSADC_LOLIMSTAT_LLS_SHIFT)) & HSADC_LOLIMSTAT_LLS_MASK)

/*! @name HILIMSTAT - HSADC High Limit Status Register */
#define HSADC_HILIMSTAT_HLS_MASK                 (0xFFFFU)
#define HSADC_HILIMSTAT_HLS_SHIFT                (0U)
#define HSADC_HILIMSTAT_HLS(x)                   (((uint16_t)(((uint16_t)(x)) << HSADC_HILIMSTAT_HLS_SHIFT)) & HSADC_HILIMSTAT_HLS_MASK)

/*! @name ZXSTAT - HSADC Zero Crossing Status Register */
#define HSADC_ZXSTAT_ZCS_MASK                    (0xFFFFU)
#define HSADC_ZXSTAT_ZCS_SHIFT                   (0U)
#define HSADC_ZXSTAT_ZCS(x)                      (((uint16_t)(((uint16_t)(x)) << HSADC_ZXSTAT_ZCS_SHIFT)) & HSADC_ZXSTAT_ZCS_MASK)

/*! @name RSLT - HSADC Result Registers with sign extension */
#define HSADC_RSLT_RSLT_MASK                     (0x7FF8U)
#define HSADC_RSLT_RSLT_SHIFT                    (3U)
#define HSADC_RSLT_RSLT(x)                       (((uint16_t)(((uint16_t)(x)) << HSADC_RSLT_RSLT_SHIFT)) & HSADC_RSLT_RSLT_MASK)
#define HSADC_RSLT_SEXT_MASK                     (0x8000U)
#define HSADC_RSLT_SEXT_SHIFT                    (15U)
#define HSADC_RSLT_SEXT(x)                       (((uint16_t)(((uint16_t)(x)) << HSADC_RSLT_SEXT_SHIFT)) & HSADC_RSLT_SEXT_MASK)

/* The count of HSADC_RSLT */
#define HSADC_RSLT_COUNT                         (16U)

/*! @name LOLIM - HSADC Low Limit Registers */
#define HSADC_LOLIM_LLMT_MASK                    (0x7FF8U)
#define HSADC_LOLIM_LLMT_SHIFT                   (3U)
#define HSADC_LOLIM_LLMT(x)                      (((uint16_t)(((uint16_t)(x)) << HSADC_LOLIM_LLMT_SHIFT)) & HSADC_LOLIM_LLMT_MASK)

/* The count of HSADC_LOLIM */
#define HSADC_LOLIM_COUNT                        (16U)

/*! @name HILIM - HSADC High Limit Registers */
#define HSADC_HILIM_HLMT_MASK                    (0x7FF8U)
#define HSADC_HILIM_HLMT_SHIFT                   (3U)
#define HSADC_HILIM_HLMT(x)                      (((uint16_t)(((uint16_t)(x)) << HSADC_HILIM_HLMT_SHIFT)) & HSADC_HILIM_HLMT_MASK)

/* The count of HSADC_HILIM */
#define HSADC_HILIM_COUNT                        (16U)

/*! @name OFFST - HSADC Offset Register */
#define HSADC_OFFST_OFFSET_MASK                  (0x7FF8U)
#define HSADC_OFFST_OFFSET_SHIFT                 (3U)
#define HSADC_OFFST_OFFSET(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_OFFST_OFFSET_SHIFT)) & HSADC_OFFST_OFFSET_MASK)

/* The count of HSADC_OFFST */
#define HSADC_OFFST_COUNT                        (16U)

/*! @name PWR - HSADC Power Control Register */
#define HSADC_PWR_PDA_MASK                       (0x1U)
#define HSADC_PWR_PDA_SHIFT                      (0U)
#define HSADC_PWR_PDA(x)                         (((uint16_t)(((uint16_t)(x)) << HSADC_PWR_PDA_SHIFT)) & HSADC_PWR_PDA_MASK)
#define HSADC_PWR_PDB_MASK                       (0x2U)
#define HSADC_PWR_PDB_SHIFT                      (1U)
#define HSADC_PWR_PDB(x)                         (((uint16_t)(((uint16_t)(x)) << HSADC_PWR_PDB_SHIFT)) & HSADC_PWR_PDB_MASK)
#define HSADC_PWR_APD_MASK                       (0x8U)
#define HSADC_PWR_APD_SHIFT                      (3U)
#define HSADC_PWR_APD(x)                         (((uint16_t)(((uint16_t)(x)) << HSADC_PWR_APD_SHIFT)) & HSADC_PWR_APD_MASK)
#define HSADC_PWR_PUDELAY_MASK                   (0x3F0U)
#define HSADC_PWR_PUDELAY_SHIFT                  (4U)
#define HSADC_PWR_PUDELAY(x)                     (((uint16_t)(((uint16_t)(x)) << HSADC_PWR_PUDELAY_SHIFT)) & HSADC_PWR_PUDELAY_MASK)
#define HSADC_PWR_PSTSA_MASK                     (0x400U)
#define HSADC_PWR_PSTSA_SHIFT                    (10U)
#define HSADC_PWR_PSTSA(x)                       (((uint16_t)(((uint16_t)(x)) << HSADC_PWR_PSTSA_SHIFT)) & HSADC_PWR_PSTSA_MASK)
#define HSADC_PWR_PSTSB_MASK                     (0x800U)
#define HSADC_PWR_PSTSB_SHIFT                    (11U)
#define HSADC_PWR_PSTSB(x)                       (((uint16_t)(((uint16_t)(x)) << HSADC_PWR_PSTSB_SHIFT)) & HSADC_PWR_PSTSB_MASK)
#define HSADC_PWR_ASB_MASK                       (0x8000U)
#define HSADC_PWR_ASB_SHIFT                      (15U)
#define HSADC_PWR_ASB(x)                         (((uint16_t)(((uint16_t)(x)) << HSADC_PWR_ASB_SHIFT)) & HSADC_PWR_ASB_MASK)

/*! @name SCTRL - HSADC Scan Control Register */
#define HSADC_SCTRL_SC_MASK                      (0xFFFFU)
#define HSADC_SCTRL_SC_SHIFT                     (0U)
#define HSADC_SCTRL_SC(x)                        (((uint16_t)(((uint16_t)(x)) << HSADC_SCTRL_SC_SHIFT)) & HSADC_SCTRL_SC_MASK)

/*! @name PWR2 - HSADC Power Control Register 2 */
#define HSADC_PWR2_DIVB_MASK                     (0x3F00U)
#define HSADC_PWR2_DIVB_SHIFT                    (8U)
#define HSADC_PWR2_DIVB(x)                       (((uint16_t)(((uint16_t)(x)) << HSADC_PWR2_DIVB_SHIFT)) & HSADC_PWR2_DIVB_MASK)

/*! @name CTRL3 - HSADC Control Register 3 */
#define HSADC_CTRL3_DMASRC_MASK                  (0x40U)
#define HSADC_CTRL3_DMASRC_SHIFT                 (6U)
#define HSADC_CTRL3_DMASRC(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL3_DMASRC_SHIFT)) & HSADC_CTRL3_DMASRC_MASK)
#define HSADC_CTRL3_ADCRES_MASK                  (0x300U)
#define HSADC_CTRL3_ADCRES_SHIFT                 (8U)
#define HSADC_CTRL3_ADCRES(x)                    (((uint16_t)(((uint16_t)(x)) << HSADC_CTRL3_ADCRES_SHIFT)) & HSADC_CTRL3_ADCRES_MASK)

/*! @name SCINTEN - HSADC Scan Interrupt Enable Register */
#define HSADC_SCINTEN_SCINTEN_MASK               (0xFFFFU)
#define HSADC_SCINTEN_SCINTEN_SHIFT              (0U)
#define HSADC_SCINTEN_SCINTEN(x)                 (((uint16_t)(((uint16_t)(x)) << HSADC_SCINTEN_SCINTEN_SHIFT)) & HSADC_SCINTEN_SCINTEN_MASK)

/*! @name SAMPTIM - HSADC Sampling Time Configuration Register */
#define HSADC_SAMPTIM_SAMPT_A_MASK               (0xFFU)
#define HSADC_SAMPTIM_SAMPT_A_SHIFT              (0U)
#define HSADC_SAMPTIM_SAMPT_A(x)                 (((uint16_t)(((uint16_t)(x)) << HSADC_SAMPTIM_SAMPT_A_SHIFT)) & HSADC_SAMPTIM_SAMPT_A_MASK)
#define HSADC_SAMPTIM_SAMPT_B_MASK               (0xFF00U)
#define HSADC_SAMPTIM_SAMPT_B_SHIFT              (8U)
#define HSADC_SAMPTIM_SAMPT_B(x)                 (((uint16_t)(((uint16_t)(x)) << HSADC_SAMPTIM_SAMPT_B_SHIFT)) & HSADC_SAMPTIM_SAMPT_B_MASK)

/*! @name CALIB - HSADCs Calibration Configuration */
#define HSADC_CALIB_REQSINGA_MASK                (0x1U)
#define HSADC_CALIB_REQSINGA_SHIFT               (0U)
#define HSADC_CALIB_REQSINGA(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CALIB_REQSINGA_SHIFT)) & HSADC_CALIB_REQSINGA_MASK)
#define HSADC_CALIB_REQDIFA_MASK                 (0x2U)
#define HSADC_CALIB_REQDIFA_SHIFT                (1U)
#define HSADC_CALIB_REQDIFA(x)                   (((uint16_t)(((uint16_t)(x)) << HSADC_CALIB_REQDIFA_SHIFT)) & HSADC_CALIB_REQDIFA_MASK)
#define HSADC_CALIB_BYPA_MASK                    (0x4U)
#define HSADC_CALIB_BYPA_SHIFT                   (2U)
#define HSADC_CALIB_BYPA(x)                      (((uint16_t)(((uint16_t)(x)) << HSADC_CALIB_BYPA_SHIFT)) & HSADC_CALIB_BYPA_MASK)
#define HSADC_CALIB_CAL_REQA_MASK                (0x8U)
#define HSADC_CALIB_CAL_REQA_SHIFT               (3U)
#define HSADC_CALIB_CAL_REQA(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CALIB_CAL_REQA_SHIFT)) & HSADC_CALIB_CAL_REQA_MASK)
#define HSADC_CALIB_REQSINGB_MASK                (0x10U)
#define HSADC_CALIB_REQSINGB_SHIFT               (4U)
#define HSADC_CALIB_REQSINGB(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CALIB_REQSINGB_SHIFT)) & HSADC_CALIB_REQSINGB_MASK)
#define HSADC_CALIB_REQDIFB_MASK                 (0x20U)
#define HSADC_CALIB_REQDIFB_SHIFT                (5U)
#define HSADC_CALIB_REQDIFB(x)                   (((uint16_t)(((uint16_t)(x)) << HSADC_CALIB_REQDIFB_SHIFT)) & HSADC_CALIB_REQDIFB_MASK)
#define HSADC_CALIB_BYPB_MASK                    (0x40U)
#define HSADC_CALIB_BYPB_SHIFT                   (6U)
#define HSADC_CALIB_BYPB(x)                      (((uint16_t)(((uint16_t)(x)) << HSADC_CALIB_BYPB_SHIFT)) & HSADC_CALIB_BYPB_MASK)
#define HSADC_CALIB_CAL_REQB_MASK                (0x80U)
#define HSADC_CALIB_CAL_REQB_SHIFT               (7U)
#define HSADC_CALIB_CAL_REQB(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CALIB_CAL_REQB_SHIFT)) & HSADC_CALIB_CAL_REQB_MASK)
#define HSADC_CALIB_EOCALIEA_MASK                (0x100U)
#define HSADC_CALIB_EOCALIEA_SHIFT               (8U)
#define HSADC_CALIB_EOCALIEA(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CALIB_EOCALIEA_SHIFT)) & HSADC_CALIB_EOCALIEA_MASK)
#define HSADC_CALIB_EOCALIEB_MASK                (0x200U)
#define HSADC_CALIB_EOCALIEB_SHIFT               (9U)
#define HSADC_CALIB_EOCALIEB(x)                  (((uint16_t)(((uint16_t)(x)) << HSADC_CALIB_EOCALIEB_SHIFT)) & HSADC_CALIB_EOCALIEB_MASK)

/*! @name CALVAL_A - Calibration Values for ADCA Register */
#define HSADC_CALVAL_A_CALVSING_MASK             (0x7FU)
#define HSADC_CALVAL_A_CALVSING_SHIFT            (0U)
#define HSADC_CALVAL_A_CALVSING(x)               (((uint16_t)(((uint16_t)(x)) << HSADC_CALVAL_A_CALVSING_SHIFT)) & HSADC_CALVAL_A_CALVSING_MASK)
#define HSADC_CALVAL_A_CALVDIF_MASK              (0x7F00U)
#define HSADC_CALVAL_A_CALVDIF_SHIFT             (8U)
#define HSADC_CALVAL_A_CALVDIF(x)                (((uint16_t)(((uint16_t)(x)) << HSADC_CALVAL_A_CALVDIF_SHIFT)) & HSADC_CALVAL_A_CALVDIF_MASK)

/*! @name CALVAL_B - Calibration Values for ADCB Register */
#define HSADC_CALVAL_B_CALVSING_MASK             (0x7FU)
#define HSADC_CALVAL_B_CALVSING_SHIFT            (0U)
#define HSADC_CALVAL_B_CALVSING(x)               (((uint16_t)(((uint16_t)(x)) << HSADC_CALVAL_B_CALVSING_SHIFT)) & HSADC_CALVAL_B_CALVSING_MASK)
#define HSADC_CALVAL_B_CALVDIF_MASK              (0x7F00U)
#define HSADC_CALVAL_B_CALVDIF_SHIFT             (8U)
#define HSADC_CALVAL_B_CALVDIF(x)                (((uint16_t)(((uint16_t)(x)) << HSADC_CALVAL_B_CALVDIF_SHIFT)) & HSADC_CALVAL_B_CALVDIF_MASK)

/*! @name MUX67_SEL - MUX6_7 Selection Controls Register */
#define HSADC_MUX67_SEL_CH6_SELA_MASK            (0x7U)
#define HSADC_MUX67_SEL_CH6_SELA_SHIFT           (0U)
#define HSADC_MUX67_SEL_CH6_SELA(x)              (((uint16_t)(((uint16_t)(x)) << HSADC_MUX67_SEL_CH6_SELA_SHIFT)) & HSADC_MUX67_SEL_CH6_SELA_MASK)
#define HSADC_MUX67_SEL_CH7_SELA_MASK            (0x70U)
#define HSADC_MUX67_SEL_CH7_SELA_SHIFT           (4U)
#define HSADC_MUX67_SEL_CH7_SELA(x)              (((uint16_t)(((uint16_t)(x)) << HSADC_MUX67_SEL_CH7_SELA_SHIFT)) & HSADC_MUX67_SEL_CH7_SELA_MASK)
#define HSADC_MUX67_SEL_CH6_SELB_MASK            (0x700U)
#define HSADC_MUX67_SEL_CH6_SELB_SHIFT           (8U)
#define HSADC_MUX67_SEL_CH6_SELB(x)              (((uint16_t)(((uint16_t)(x)) << HSADC_MUX67_SEL_CH6_SELB_SHIFT)) & HSADC_MUX67_SEL_CH6_SELB_MASK)
#define HSADC_MUX67_SEL_CH7_SELB_MASK            (0x7000U)
#define HSADC_MUX67_SEL_CH7_SELB_SHIFT           (12U)
#define HSADC_MUX67_SEL_CH7_SELB(x)              (((uint16_t)(((uint16_t)(x)) << HSADC_MUX67_SEL_CH7_SELB_SHIFT)) & HSADC_MUX67_SEL_CH7_SELB_MASK)


/*!
 * @}
 */ /* end of group HSADC_Register_Masks */


/* HSADC - Peripheral instance base addresses */
/** Peripheral HSADC0 base address */
#define HSADC0_BASE                              (0x4005C000u)
/** Peripheral HSADC0 base pointer */
#define HSADC0                                   ((HSADC_Type *)HSADC0_BASE)
/** Peripheral HSADC1 base address */
#define HSADC1_BASE                              (0x400DC000u)
/** Peripheral HSADC1 base pointer */
#define HSADC1                                   ((HSADC_Type *)HSADC1_BASE)
/** Array initializer of HSADC peripheral base addresses */
#define HSADC_BASE_ADDRS                         { HSADC0_BASE, HSADC1_BASE }
/** Array initializer of HSADC peripheral base pointers */
#define HSADC_BASE_PTRS                          { HSADC0, HSADC1 }
/** Interrupt vectors for the HSADC peripheral type */
#define HSADC_IRQS                               { { HSADC0_CCA_IRQn, HSADC0_CCB_IRQn }, { HSADC1_CCA_IRQn, HSADC1_CCB_IRQn } }
#define HSADC_ERR_IRQS                           { HSADC_ERR_IRQn, HSADC_ERR_IRQn }

/*!
 * @}
 */ /* end of group HSADC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- I2C Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Peripheral_Access_Layer I2C Peripheral Access Layer
 * @{
 */

/** I2C - Register Layout Typedef */
typedef struct {
  __IO uint8_t A1;                                 /**< I2C Address Register 1, offset: 0x0 */
  __IO uint8_t F;                                  /**< I2C Frequency Divider register, offset: 0x1 */
  __IO uint8_t C1;                                 /**< I2C Control Register 1, offset: 0x2 */
  __IO uint8_t S;                                  /**< I2C Status register, offset: 0x3 */
  __IO uint8_t D;                                  /**< I2C Data I/O register, offset: 0x4 */
  __IO uint8_t C2;                                 /**< I2C Control Register 2, offset: 0x5 */
  __IO uint8_t FLT;                                /**< I2C Programmable Input Glitch Filter Register, offset: 0x6 */
  __IO uint8_t RA;                                 /**< I2C Range Address register, offset: 0x7 */
  __IO uint8_t SMB;                                /**< I2C SMBus Control and Status register, offset: 0x8 */
  __IO uint8_t A2;                                 /**< I2C Address Register 2, offset: 0x9 */
  __IO uint8_t SLTH;                               /**< I2C SCL Low Timeout Register High, offset: 0xA */
  __IO uint8_t SLTL;                               /**< I2C SCL Low Timeout Register Low, offset: 0xB */
} I2C_Type;

/* ----------------------------------------------------------------------------
   -- I2C Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Masks I2C Register Masks
 * @{
 */

/*! @name A1 - I2C Address Register 1 */
#define I2C_A1_AD_MASK                           (0xFEU)
#define I2C_A1_AD_SHIFT                          (1U)
#define I2C_A1_AD(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_A1_AD_SHIFT)) & I2C_A1_AD_MASK)

/*! @name F - I2C Frequency Divider register */
#define I2C_F_ICR_MASK                           (0x3FU)
#define I2C_F_ICR_SHIFT                          (0U)
#define I2C_F_ICR(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_F_ICR_SHIFT)) & I2C_F_ICR_MASK)
#define I2C_F_MULT_MASK                          (0xC0U)
#define I2C_F_MULT_SHIFT                         (6U)
#define I2C_F_MULT(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_F_MULT_SHIFT)) & I2C_F_MULT_MASK)

/*! @name C1 - I2C Control Register 1 */
#define I2C_C1_DMAEN_MASK                        (0x1U)
#define I2C_C1_DMAEN_SHIFT                       (0U)
#define I2C_C1_DMAEN(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_C1_DMAEN_SHIFT)) & I2C_C1_DMAEN_MASK)
#define I2C_C1_WUEN_MASK                         (0x2U)
#define I2C_C1_WUEN_SHIFT                        (1U)
#define I2C_C1_WUEN(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C1_WUEN_SHIFT)) & I2C_C1_WUEN_MASK)
#define I2C_C1_RSTA_MASK                         (0x4U)
#define I2C_C1_RSTA_SHIFT                        (2U)
#define I2C_C1_RSTA(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C1_RSTA_SHIFT)) & I2C_C1_RSTA_MASK)
#define I2C_C1_TXAK_MASK                         (0x8U)
#define I2C_C1_TXAK_SHIFT                        (3U)
#define I2C_C1_TXAK(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C1_TXAK_SHIFT)) & I2C_C1_TXAK_MASK)
#define I2C_C1_TX_MASK                           (0x10U)
#define I2C_C1_TX_SHIFT                          (4U)
#define I2C_C1_TX(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_C1_TX_SHIFT)) & I2C_C1_TX_MASK)
#define I2C_C1_MST_MASK                          (0x20U)
#define I2C_C1_MST_SHIFT                         (5U)
#define I2C_C1_MST(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_C1_MST_SHIFT)) & I2C_C1_MST_MASK)
#define I2C_C1_IICIE_MASK                        (0x40U)
#define I2C_C1_IICIE_SHIFT                       (6U)
#define I2C_C1_IICIE(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_C1_IICIE_SHIFT)) & I2C_C1_IICIE_MASK)
#define I2C_C1_IICEN_MASK                        (0x80U)
#define I2C_C1_IICEN_SHIFT                       (7U)
#define I2C_C1_IICEN(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_C1_IICEN_SHIFT)) & I2C_C1_IICEN_MASK)

/*! @name S - I2C Status register */
#define I2C_S_RXAK_MASK                          (0x1U)
#define I2C_S_RXAK_SHIFT                         (0U)
#define I2C_S_RXAK(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_S_RXAK_SHIFT)) & I2C_S_RXAK_MASK)
#define I2C_S_IICIF_MASK                         (0x2U)
#define I2C_S_IICIF_SHIFT                        (1U)
#define I2C_S_IICIF(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_S_IICIF_SHIFT)) & I2C_S_IICIF_MASK)
#define I2C_S_SRW_MASK                           (0x4U)
#define I2C_S_SRW_SHIFT                          (2U)
#define I2C_S_SRW(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_S_SRW_SHIFT)) & I2C_S_SRW_MASK)
#define I2C_S_RAM_MASK                           (0x8U)
#define I2C_S_RAM_SHIFT                          (3U)
#define I2C_S_RAM(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_S_RAM_SHIFT)) & I2C_S_RAM_MASK)
#define I2C_S_ARBL_MASK                          (0x10U)
#define I2C_S_ARBL_SHIFT                         (4U)
#define I2C_S_ARBL(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_S_ARBL_SHIFT)) & I2C_S_ARBL_MASK)
#define I2C_S_BUSY_MASK                          (0x20U)
#define I2C_S_BUSY_SHIFT                         (5U)
#define I2C_S_BUSY(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_S_BUSY_SHIFT)) & I2C_S_BUSY_MASK)
#define I2C_S_IAAS_MASK                          (0x40U)
#define I2C_S_IAAS_SHIFT                         (6U)
#define I2C_S_IAAS(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_S_IAAS_SHIFT)) & I2C_S_IAAS_MASK)
#define I2C_S_TCF_MASK                           (0x80U)
#define I2C_S_TCF_SHIFT                          (7U)
#define I2C_S_TCF(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_S_TCF_SHIFT)) & I2C_S_TCF_MASK)

/*! @name D - I2C Data I/O register */
#define I2C_D_DATA_MASK                          (0xFFU)
#define I2C_D_DATA_SHIFT                         (0U)
#define I2C_D_DATA(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_D_DATA_SHIFT)) & I2C_D_DATA_MASK)

/*! @name C2 - I2C Control Register 2 */
#define I2C_C2_AD_MASK                           (0x7U)
#define I2C_C2_AD_SHIFT                          (0U)
#define I2C_C2_AD(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_C2_AD_SHIFT)) & I2C_C2_AD_MASK)
#define I2C_C2_RMEN_MASK                         (0x8U)
#define I2C_C2_RMEN_SHIFT                        (3U)
#define I2C_C2_RMEN(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C2_RMEN_SHIFT)) & I2C_C2_RMEN_MASK)
#define I2C_C2_SBRC_MASK                         (0x10U)
#define I2C_C2_SBRC_SHIFT                        (4U)
#define I2C_C2_SBRC(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C2_SBRC_SHIFT)) & I2C_C2_SBRC_MASK)
#define I2C_C2_HDRS_MASK                         (0x20U)
#define I2C_C2_HDRS_SHIFT                        (5U)
#define I2C_C2_HDRS(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C2_HDRS_SHIFT)) & I2C_C2_HDRS_MASK)
#define I2C_C2_ADEXT_MASK                        (0x40U)
#define I2C_C2_ADEXT_SHIFT                       (6U)
#define I2C_C2_ADEXT(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_C2_ADEXT_SHIFT)) & I2C_C2_ADEXT_MASK)
#define I2C_C2_GCAEN_MASK                        (0x80U)
#define I2C_C2_GCAEN_SHIFT                       (7U)
#define I2C_C2_GCAEN(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_C2_GCAEN_SHIFT)) & I2C_C2_GCAEN_MASK)

/*! @name FLT - I2C Programmable Input Glitch Filter Register */
#define I2C_FLT_FLT_MASK                         (0xFU)
#define I2C_FLT_FLT_SHIFT                        (0U)
#define I2C_FLT_FLT(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_FLT_FLT_SHIFT)) & I2C_FLT_FLT_MASK)
#define I2C_FLT_STARTF_MASK                      (0x10U)
#define I2C_FLT_STARTF_SHIFT                     (4U)
#define I2C_FLT_STARTF(x)                        (((uint8_t)(((uint8_t)(x)) << I2C_FLT_STARTF_SHIFT)) & I2C_FLT_STARTF_MASK)
#define I2C_FLT_SSIE_MASK                        (0x20U)
#define I2C_FLT_SSIE_SHIFT                       (5U)
#define I2C_FLT_SSIE(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_FLT_SSIE_SHIFT)) & I2C_FLT_SSIE_MASK)
#define I2C_FLT_STOPF_MASK                       (0x40U)
#define I2C_FLT_STOPF_SHIFT                      (6U)
#define I2C_FLT_STOPF(x)                         (((uint8_t)(((uint8_t)(x)) << I2C_FLT_STOPF_SHIFT)) & I2C_FLT_STOPF_MASK)
#define I2C_FLT_SHEN_MASK                        (0x80U)
#define I2C_FLT_SHEN_SHIFT                       (7U)
#define I2C_FLT_SHEN(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_FLT_SHEN_SHIFT)) & I2C_FLT_SHEN_MASK)

/*! @name RA - I2C Range Address register */
#define I2C_RA_RAD_MASK                          (0xFEU)
#define I2C_RA_RAD_SHIFT                         (1U)
#define I2C_RA_RAD(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_RA_RAD_SHIFT)) & I2C_RA_RAD_MASK)

/*! @name SMB - I2C SMBus Control and Status register */
#define I2C_SMB_SHTF2IE_MASK                     (0x1U)
#define I2C_SMB_SHTF2IE_SHIFT                    (0U)
#define I2C_SMB_SHTF2IE(x)                       (((uint8_t)(((uint8_t)(x)) << I2C_SMB_SHTF2IE_SHIFT)) & I2C_SMB_SHTF2IE_MASK)
#define I2C_SMB_SHTF2_MASK                       (0x2U)
#define I2C_SMB_SHTF2_SHIFT                      (1U)
#define I2C_SMB_SHTF2(x)                         (((uint8_t)(((uint8_t)(x)) << I2C_SMB_SHTF2_SHIFT)) & I2C_SMB_SHTF2_MASK)
#define I2C_SMB_SHTF1_MASK                       (0x4U)
#define I2C_SMB_SHTF1_SHIFT                      (2U)
#define I2C_SMB_SHTF1(x)                         (((uint8_t)(((uint8_t)(x)) << I2C_SMB_SHTF1_SHIFT)) & I2C_SMB_SHTF1_MASK)
#define I2C_SMB_SLTF_MASK                        (0x8U)
#define I2C_SMB_SLTF_SHIFT                       (3U)
#define I2C_SMB_SLTF(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_SMB_SLTF_SHIFT)) & I2C_SMB_SLTF_MASK)
#define I2C_SMB_TCKSEL_MASK                      (0x10U)
#define I2C_SMB_TCKSEL_SHIFT                     (4U)
#define I2C_SMB_TCKSEL(x)                        (((uint8_t)(((uint8_t)(x)) << I2C_SMB_TCKSEL_SHIFT)) & I2C_SMB_TCKSEL_MASK)
#define I2C_SMB_SIICAEN_MASK                     (0x20U)
#define I2C_SMB_SIICAEN_SHIFT                    (5U)
#define I2C_SMB_SIICAEN(x)                       (((uint8_t)(((uint8_t)(x)) << I2C_SMB_SIICAEN_SHIFT)) & I2C_SMB_SIICAEN_MASK)
#define I2C_SMB_ALERTEN_MASK                     (0x40U)
#define I2C_SMB_ALERTEN_SHIFT                    (6U)
#define I2C_SMB_ALERTEN(x)                       (((uint8_t)(((uint8_t)(x)) << I2C_SMB_ALERTEN_SHIFT)) & I2C_SMB_ALERTEN_MASK)
#define I2C_SMB_FACK_MASK                        (0x80U)
#define I2C_SMB_FACK_SHIFT                       (7U)
#define I2C_SMB_FACK(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_SMB_FACK_SHIFT)) & I2C_SMB_FACK_MASK)

/*! @name A2 - I2C Address Register 2 */
#define I2C_A2_SAD_MASK                          (0xFEU)
#define I2C_A2_SAD_SHIFT                         (1U)
#define I2C_A2_SAD(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_A2_SAD_SHIFT)) & I2C_A2_SAD_MASK)

/*! @name SLTH - I2C SCL Low Timeout Register High */
#define I2C_SLTH_SSLT_MASK                       (0xFFU)
#define I2C_SLTH_SSLT_SHIFT                      (0U)
#define I2C_SLTH_SSLT(x)                         (((uint8_t)(((uint8_t)(x)) << I2C_SLTH_SSLT_SHIFT)) & I2C_SLTH_SSLT_MASK)

/*! @name SLTL - I2C SCL Low Timeout Register Low */
#define I2C_SLTL_SSLT_MASK                       (0xFFU)
#define I2C_SLTL_SSLT_SHIFT                      (0U)
#define I2C_SLTL_SSLT(x)                         (((uint8_t)(((uint8_t)(x)) << I2C_SLTL_SSLT_SHIFT)) & I2C_SLTL_SSLT_MASK)


/*!
 * @}
 */ /* end of group I2C_Register_Masks */


/* I2C - Peripheral instance base addresses */
/** Peripheral I2C0 base address */
#define I2C0_BASE                                (0x40066000u)
/** Peripheral I2C0 base pointer */
#define I2C0                                     ((I2C_Type *)I2C0_BASE)
/** Peripheral I2C1 base address */
#define I2C1_BASE                                (0x40067000u)
/** Peripheral I2C1 base pointer */
#define I2C1                                     ((I2C_Type *)I2C1_BASE)
/** Array initializer of I2C peripheral base addresses */
#define I2C_BASE_ADDRS                           { I2C0_BASE, I2C1_BASE }
/** Array initializer of I2C peripheral base pointers */
#define I2C_BASE_PTRS                            { I2C0, I2C1 }
/** Interrupt vectors for the I2C peripheral type */
#define I2C_IRQS                                 { I2C0_IRQn, I2C1_IRQn }

/*!
 * @}
 */ /* end of group I2C_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- LLWU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LLWU_Peripheral_Access_Layer LLWU Peripheral Access Layer
 * @{
 */

/** LLWU - Register Layout Typedef */
typedef struct {
  __IO uint8_t PE1;                                /**< LLWU Pin Enable 1 register, offset: 0x0 */
  __IO uint8_t PE2;                                /**< LLWU Pin Enable 2 register, offset: 0x1 */
  __IO uint8_t PE3;                                /**< LLWU Pin Enable 3 register, offset: 0x2 */
  __IO uint8_t PE4;                                /**< LLWU Pin Enable 4 register, offset: 0x3 */
  __IO uint8_t PE5;                                /**< LLWU Pin Enable 5 register, offset: 0x4 */
  __IO uint8_t PE6;                                /**< LLWU Pin Enable 6 register, offset: 0x5 */
  __IO uint8_t PE7;                                /**< LLWU Pin Enable 7 register, offset: 0x6 */
  __IO uint8_t PE8;                                /**< LLWU Pin Enable 8 register, offset: 0x7 */
  __IO uint8_t ME;                                 /**< LLWU Module Enable register, offset: 0x8 */
  __IO uint8_t PF1;                                /**< LLWU Pin Flag 1 register, offset: 0x9 */
  __IO uint8_t PF2;                                /**< LLWU Pin Flag 2 register, offset: 0xA */
  __IO uint8_t PF3;                                /**< LLWU Pin Flag 3 register, offset: 0xB */
  __IO uint8_t PF4;                                /**< LLWU Pin Flag 4 register, offset: 0xC */
  __I  uint8_t MF5;                                /**< LLWU Module Flag 5 register, offset: 0xD */
  __IO uint8_t FILT1;                              /**< LLWU Pin Filter 1 register, offset: 0xE */
  __IO uint8_t FILT2;                              /**< LLWU Pin Filter 2 register, offset: 0xF */
} LLWU_Type;

/* ----------------------------------------------------------------------------
   -- LLWU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LLWU_Register_Masks LLWU Register Masks
 * @{
 */

/*! @name PE1 - LLWU Pin Enable 1 register */
#define LLWU_PE1_WUPE0_MASK                      (0x3U)
#define LLWU_PE1_WUPE0_SHIFT                     (0U)
#define LLWU_PE1_WUPE0(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE1_WUPE0_SHIFT)) & LLWU_PE1_WUPE0_MASK)
#define LLWU_PE1_WUPE1_MASK                      (0xCU)
#define LLWU_PE1_WUPE1_SHIFT                     (2U)
#define LLWU_PE1_WUPE1(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE1_WUPE1_SHIFT)) & LLWU_PE1_WUPE1_MASK)
#define LLWU_PE1_WUPE2_MASK                      (0x30U)
#define LLWU_PE1_WUPE2_SHIFT                     (4U)
#define LLWU_PE1_WUPE2(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE1_WUPE2_SHIFT)) & LLWU_PE1_WUPE2_MASK)
#define LLWU_PE1_WUPE3_MASK                      (0xC0U)
#define LLWU_PE1_WUPE3_SHIFT                     (6U)
#define LLWU_PE1_WUPE3(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE1_WUPE3_SHIFT)) & LLWU_PE1_WUPE3_MASK)

/*! @name PE2 - LLWU Pin Enable 2 register */
#define LLWU_PE2_WUPE4_MASK                      (0x3U)
#define LLWU_PE2_WUPE4_SHIFT                     (0U)
#define LLWU_PE2_WUPE4(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE2_WUPE4_SHIFT)) & LLWU_PE2_WUPE4_MASK)
#define LLWU_PE2_WUPE5_MASK                      (0xCU)
#define LLWU_PE2_WUPE5_SHIFT                     (2U)
#define LLWU_PE2_WUPE5(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE2_WUPE5_SHIFT)) & LLWU_PE2_WUPE5_MASK)
#define LLWU_PE2_WUPE6_MASK                      (0x30U)
#define LLWU_PE2_WUPE6_SHIFT                     (4U)
#define LLWU_PE2_WUPE6(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE2_WUPE6_SHIFT)) & LLWU_PE2_WUPE6_MASK)
#define LLWU_PE2_WUPE7_MASK                      (0xC0U)
#define LLWU_PE2_WUPE7_SHIFT                     (6U)
#define LLWU_PE2_WUPE7(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE2_WUPE7_SHIFT)) & LLWU_PE2_WUPE7_MASK)

/*! @name PE3 - LLWU Pin Enable 3 register */
#define LLWU_PE3_WUPE8_MASK                      (0x3U)
#define LLWU_PE3_WUPE8_SHIFT                     (0U)
#define LLWU_PE3_WUPE8(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE3_WUPE8_SHIFT)) & LLWU_PE3_WUPE8_MASK)
#define LLWU_PE3_WUPE9_MASK                      (0xCU)
#define LLWU_PE3_WUPE9_SHIFT                     (2U)
#define LLWU_PE3_WUPE9(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE3_WUPE9_SHIFT)) & LLWU_PE3_WUPE9_MASK)
#define LLWU_PE3_WUPE10_MASK                     (0x30U)
#define LLWU_PE3_WUPE10_SHIFT                    (4U)
#define LLWU_PE3_WUPE10(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE3_WUPE10_SHIFT)) & LLWU_PE3_WUPE10_MASK)
#define LLWU_PE3_WUPE11_MASK                     (0xC0U)
#define LLWU_PE3_WUPE11_SHIFT                    (6U)
#define LLWU_PE3_WUPE11(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE3_WUPE11_SHIFT)) & LLWU_PE3_WUPE11_MASK)

/*! @name PE4 - LLWU Pin Enable 4 register */
#define LLWU_PE4_WUPE12_MASK                     (0x3U)
#define LLWU_PE4_WUPE12_SHIFT                    (0U)
#define LLWU_PE4_WUPE12(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE4_WUPE12_SHIFT)) & LLWU_PE4_WUPE12_MASK)
#define LLWU_PE4_WUPE13_MASK                     (0xCU)
#define LLWU_PE4_WUPE13_SHIFT                    (2U)
#define LLWU_PE4_WUPE13(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE4_WUPE13_SHIFT)) & LLWU_PE4_WUPE13_MASK)
#define LLWU_PE4_WUPE14_MASK                     (0x30U)
#define LLWU_PE4_WUPE14_SHIFT                    (4U)
#define LLWU_PE4_WUPE14(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE4_WUPE14_SHIFT)) & LLWU_PE4_WUPE14_MASK)
#define LLWU_PE4_WUPE15_MASK                     (0xC0U)
#define LLWU_PE4_WUPE15_SHIFT                    (6U)
#define LLWU_PE4_WUPE15(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE4_WUPE15_SHIFT)) & LLWU_PE4_WUPE15_MASK)

/*! @name PE5 - LLWU Pin Enable 5 register */
#define LLWU_PE5_WUPE16_MASK                     (0x3U)
#define LLWU_PE5_WUPE16_SHIFT                    (0U)
#define LLWU_PE5_WUPE16(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE5_WUPE16_SHIFT)) & LLWU_PE5_WUPE16_MASK)
#define LLWU_PE5_WUPE17_MASK                     (0xCU)
#define LLWU_PE5_WUPE17_SHIFT                    (2U)
#define LLWU_PE5_WUPE17(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE5_WUPE17_SHIFT)) & LLWU_PE5_WUPE17_MASK)
#define LLWU_PE5_WUPE18_MASK                     (0x30U)
#define LLWU_PE5_WUPE18_SHIFT                    (4U)
#define LLWU_PE5_WUPE18(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE5_WUPE18_SHIFT)) & LLWU_PE5_WUPE18_MASK)
#define LLWU_PE5_WUPE19_MASK                     (0xC0U)
#define LLWU_PE5_WUPE19_SHIFT                    (6U)
#define LLWU_PE5_WUPE19(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE5_WUPE19_SHIFT)) & LLWU_PE5_WUPE19_MASK)

/*! @name PE6 - LLWU Pin Enable 6 register */
#define LLWU_PE6_WUPE20_MASK                     (0x3U)
#define LLWU_PE6_WUPE20_SHIFT                    (0U)
#define LLWU_PE6_WUPE20(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE6_WUPE20_SHIFT)) & LLWU_PE6_WUPE20_MASK)
#define LLWU_PE6_WUPE21_MASK                     (0xCU)
#define LLWU_PE6_WUPE21_SHIFT                    (2U)
#define LLWU_PE6_WUPE21(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE6_WUPE21_SHIFT)) & LLWU_PE6_WUPE21_MASK)
#define LLWU_PE6_WUPE22_MASK                     (0x30U)
#define LLWU_PE6_WUPE22_SHIFT                    (4U)
#define LLWU_PE6_WUPE22(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE6_WUPE22_SHIFT)) & LLWU_PE6_WUPE22_MASK)
#define LLWU_PE6_WUPE23_MASK                     (0xC0U)
#define LLWU_PE6_WUPE23_SHIFT                    (6U)
#define LLWU_PE6_WUPE23(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE6_WUPE23_SHIFT)) & LLWU_PE6_WUPE23_MASK)

/*! @name PE7 - LLWU Pin Enable 7 register */
#define LLWU_PE7_WUPE24_MASK                     (0x3U)
#define LLWU_PE7_WUPE24_SHIFT                    (0U)
#define LLWU_PE7_WUPE24(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE7_WUPE24_SHIFT)) & LLWU_PE7_WUPE24_MASK)
#define LLWU_PE7_WUPE25_MASK                     (0xCU)
#define LLWU_PE7_WUPE25_SHIFT                    (2U)
#define LLWU_PE7_WUPE25(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE7_WUPE25_SHIFT)) & LLWU_PE7_WUPE25_MASK)
#define LLWU_PE7_WUPE26_MASK                     (0x30U)
#define LLWU_PE7_WUPE26_SHIFT                    (4U)
#define LLWU_PE7_WUPE26(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE7_WUPE26_SHIFT)) & LLWU_PE7_WUPE26_MASK)
#define LLWU_PE7_WUPE27_MASK                     (0xC0U)
#define LLWU_PE7_WUPE27_SHIFT                    (6U)
#define LLWU_PE7_WUPE27(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE7_WUPE27_SHIFT)) & LLWU_PE7_WUPE27_MASK)

/*! @name PE8 - LLWU Pin Enable 8 register */
#define LLWU_PE8_WUPE28_MASK                     (0x3U)
#define LLWU_PE8_WUPE28_SHIFT                    (0U)
#define LLWU_PE8_WUPE28(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE8_WUPE28_SHIFT)) & LLWU_PE8_WUPE28_MASK)
#define LLWU_PE8_WUPE29_MASK                     (0xCU)
#define LLWU_PE8_WUPE29_SHIFT                    (2U)
#define LLWU_PE8_WUPE29(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE8_WUPE29_SHIFT)) & LLWU_PE8_WUPE29_MASK)
#define LLWU_PE8_WUPE30_MASK                     (0x30U)
#define LLWU_PE8_WUPE30_SHIFT                    (4U)
#define LLWU_PE8_WUPE30(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE8_WUPE30_SHIFT)) & LLWU_PE8_WUPE30_MASK)
#define LLWU_PE8_WUPE31_MASK                     (0xC0U)
#define LLWU_PE8_WUPE31_SHIFT                    (6U)
#define LLWU_PE8_WUPE31(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE8_WUPE31_SHIFT)) & LLWU_PE8_WUPE31_MASK)

/*! @name ME - LLWU Module Enable register */
#define LLWU_ME_WUME0_MASK                       (0x1U)
#define LLWU_ME_WUME0_SHIFT                      (0U)
#define LLWU_ME_WUME0(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME0_SHIFT)) & LLWU_ME_WUME0_MASK)
#define LLWU_ME_WUME1_MASK                       (0x2U)
#define LLWU_ME_WUME1_SHIFT                      (1U)
#define LLWU_ME_WUME1(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME1_SHIFT)) & LLWU_ME_WUME1_MASK)
#define LLWU_ME_WUME2_MASK                       (0x4U)
#define LLWU_ME_WUME2_SHIFT                      (2U)
#define LLWU_ME_WUME2(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME2_SHIFT)) & LLWU_ME_WUME2_MASK)
#define LLWU_ME_WUME3_MASK                       (0x8U)
#define LLWU_ME_WUME3_SHIFT                      (3U)
#define LLWU_ME_WUME3(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME3_SHIFT)) & LLWU_ME_WUME3_MASK)
#define LLWU_ME_WUME4_MASK                       (0x10U)
#define LLWU_ME_WUME4_SHIFT                      (4U)
#define LLWU_ME_WUME4(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME4_SHIFT)) & LLWU_ME_WUME4_MASK)
#define LLWU_ME_WUME5_MASK                       (0x20U)
#define LLWU_ME_WUME5_SHIFT                      (5U)
#define LLWU_ME_WUME5(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME5_SHIFT)) & LLWU_ME_WUME5_MASK)
#define LLWU_ME_WUME6_MASK                       (0x40U)
#define LLWU_ME_WUME6_SHIFT                      (6U)
#define LLWU_ME_WUME6(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME6_SHIFT)) & LLWU_ME_WUME6_MASK)
#define LLWU_ME_WUME7_MASK                       (0x80U)
#define LLWU_ME_WUME7_SHIFT                      (7U)
#define LLWU_ME_WUME7(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME7_SHIFT)) & LLWU_ME_WUME7_MASK)

/*! @name PF1 - LLWU Pin Flag 1 register */
#define LLWU_PF1_WUF0_MASK                       (0x1U)
#define LLWU_PF1_WUF0_SHIFT                      (0U)
#define LLWU_PF1_WUF0(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_PF1_WUF0_SHIFT)) & LLWU_PF1_WUF0_MASK)
#define LLWU_PF1_WUF1_MASK                       (0x2U)
#define LLWU_PF1_WUF1_SHIFT                      (1U)
#define LLWU_PF1_WUF1(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_PF1_WUF1_SHIFT)) & LLWU_PF1_WUF1_MASK)
#define LLWU_PF1_WUF2_MASK                       (0x4U)
#define LLWU_PF1_WUF2_SHIFT                      (2U)
#define LLWU_PF1_WUF2(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_PF1_WUF2_SHIFT)) & LLWU_PF1_WUF2_MASK)
#define LLWU_PF1_WUF3_MASK                       (0x8U)
#define LLWU_PF1_WUF3_SHIFT                      (3U)
#define LLWU_PF1_WUF3(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_PF1_WUF3_SHIFT)) & LLWU_PF1_WUF3_MASK)
#define LLWU_PF1_WUF4_MASK                       (0x10U)
#define LLWU_PF1_WUF4_SHIFT                      (4U)
#define LLWU_PF1_WUF4(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_PF1_WUF4_SHIFT)) & LLWU_PF1_WUF4_MASK)
#define LLWU_PF1_WUF5_MASK                       (0x20U)
#define LLWU_PF1_WUF5_SHIFT                      (5U)
#define LLWU_PF1_WUF5(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_PF1_WUF5_SHIFT)) & LLWU_PF1_WUF5_MASK)
#define LLWU_PF1_WUF6_MASK                       (0x40U)
#define LLWU_PF1_WUF6_SHIFT                      (6U)
#define LLWU_PF1_WUF6(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_PF1_WUF6_SHIFT)) & LLWU_PF1_WUF6_MASK)
#define LLWU_PF1_WUF7_MASK                       (0x80U)
#define LLWU_PF1_WUF7_SHIFT                      (7U)
#define LLWU_PF1_WUF7(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_PF1_WUF7_SHIFT)) & LLWU_PF1_WUF7_MASK)

/*! @name PF2 - LLWU Pin Flag 2 register */
#define LLWU_PF2_WUF8_MASK                       (0x1U)
#define LLWU_PF2_WUF8_SHIFT                      (0U)
#define LLWU_PF2_WUF8(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_PF2_WUF8_SHIFT)) & LLWU_PF2_WUF8_MASK)
#define LLWU_PF2_WUF9_MASK                       (0x2U)
#define LLWU_PF2_WUF9_SHIFT                      (1U)
#define LLWU_PF2_WUF9(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_PF2_WUF9_SHIFT)) & LLWU_PF2_WUF9_MASK)
#define LLWU_PF2_WUF10_MASK                      (0x4U)
#define LLWU_PF2_WUF10_SHIFT                     (2U)
#define LLWU_PF2_WUF10(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF2_WUF10_SHIFT)) & LLWU_PF2_WUF10_MASK)
#define LLWU_PF2_WUF11_MASK                      (0x8U)
#define LLWU_PF2_WUF11_SHIFT                     (3U)
#define LLWU_PF2_WUF11(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF2_WUF11_SHIFT)) & LLWU_PF2_WUF11_MASK)
#define LLWU_PF2_WUF12_MASK                      (0x10U)
#define LLWU_PF2_WUF12_SHIFT                     (4U)
#define LLWU_PF2_WUF12(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF2_WUF12_SHIFT)) & LLWU_PF2_WUF12_MASK)
#define LLWU_PF2_WUF13_MASK                      (0x20U)
#define LLWU_PF2_WUF13_SHIFT                     (5U)
#define LLWU_PF2_WUF13(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF2_WUF13_SHIFT)) & LLWU_PF2_WUF13_MASK)
#define LLWU_PF2_WUF14_MASK                      (0x40U)
#define LLWU_PF2_WUF14_SHIFT                     (6U)
#define LLWU_PF2_WUF14(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF2_WUF14_SHIFT)) & LLWU_PF2_WUF14_MASK)
#define LLWU_PF2_WUF15_MASK                      (0x80U)
#define LLWU_PF2_WUF15_SHIFT                     (7U)
#define LLWU_PF2_WUF15(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF2_WUF15_SHIFT)) & LLWU_PF2_WUF15_MASK)

/*! @name PF3 - LLWU Pin Flag 3 register */
#define LLWU_PF3_WUF16_MASK                      (0x1U)
#define LLWU_PF3_WUF16_SHIFT                     (0U)
#define LLWU_PF3_WUF16(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF3_WUF16_SHIFT)) & LLWU_PF3_WUF16_MASK)
#define LLWU_PF3_WUF17_MASK                      (0x2U)
#define LLWU_PF3_WUF17_SHIFT                     (1U)
#define LLWU_PF3_WUF17(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF3_WUF17_SHIFT)) & LLWU_PF3_WUF17_MASK)
#define LLWU_PF3_WUF18_MASK                      (0x4U)
#define LLWU_PF3_WUF18_SHIFT                     (2U)
#define LLWU_PF3_WUF18(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF3_WUF18_SHIFT)) & LLWU_PF3_WUF18_MASK)
#define LLWU_PF3_WUF19_MASK                      (0x8U)
#define LLWU_PF3_WUF19_SHIFT                     (3U)
#define LLWU_PF3_WUF19(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF3_WUF19_SHIFT)) & LLWU_PF3_WUF19_MASK)
#define LLWU_PF3_WUF20_MASK                      (0x10U)
#define LLWU_PF3_WUF20_SHIFT                     (4U)
#define LLWU_PF3_WUF20(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF3_WUF20_SHIFT)) & LLWU_PF3_WUF20_MASK)
#define LLWU_PF3_WUF21_MASK                      (0x20U)
#define LLWU_PF3_WUF21_SHIFT                     (5U)
#define LLWU_PF3_WUF21(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF3_WUF21_SHIFT)) & LLWU_PF3_WUF21_MASK)
#define LLWU_PF3_WUF22_MASK                      (0x40U)
#define LLWU_PF3_WUF22_SHIFT                     (6U)
#define LLWU_PF3_WUF22(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF3_WUF22_SHIFT)) & LLWU_PF3_WUF22_MASK)
#define LLWU_PF3_WUF23_MASK                      (0x80U)
#define LLWU_PF3_WUF23_SHIFT                     (7U)
#define LLWU_PF3_WUF23(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF3_WUF23_SHIFT)) & LLWU_PF3_WUF23_MASK)

/*! @name PF4 - LLWU Pin Flag 4 register */
#define LLWU_PF4_WUF24_MASK                      (0x1U)
#define LLWU_PF4_WUF24_SHIFT                     (0U)
#define LLWU_PF4_WUF24(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF4_WUF24_SHIFT)) & LLWU_PF4_WUF24_MASK)
#define LLWU_PF4_WUF25_MASK                      (0x2U)
#define LLWU_PF4_WUF25_SHIFT                     (1U)
#define LLWU_PF4_WUF25(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF4_WUF25_SHIFT)) & LLWU_PF4_WUF25_MASK)
#define LLWU_PF4_WUF26_MASK                      (0x4U)
#define LLWU_PF4_WUF26_SHIFT                     (2U)
#define LLWU_PF4_WUF26(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF4_WUF26_SHIFT)) & LLWU_PF4_WUF26_MASK)
#define LLWU_PF4_WUF27_MASK                      (0x8U)
#define LLWU_PF4_WUF27_SHIFT                     (3U)
#define LLWU_PF4_WUF27(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF4_WUF27_SHIFT)) & LLWU_PF4_WUF27_MASK)
#define LLWU_PF4_WUF28_MASK                      (0x10U)
#define LLWU_PF4_WUF28_SHIFT                     (4U)
#define LLWU_PF4_WUF28(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF4_WUF28_SHIFT)) & LLWU_PF4_WUF28_MASK)
#define LLWU_PF4_WUF29_MASK                      (0x20U)
#define LLWU_PF4_WUF29_SHIFT                     (5U)
#define LLWU_PF4_WUF29(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF4_WUF29_SHIFT)) & LLWU_PF4_WUF29_MASK)
#define LLWU_PF4_WUF30_MASK                      (0x40U)
#define LLWU_PF4_WUF30_SHIFT                     (6U)
#define LLWU_PF4_WUF30(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF4_WUF30_SHIFT)) & LLWU_PF4_WUF30_MASK)
#define LLWU_PF4_WUF31_MASK                      (0x80U)
#define LLWU_PF4_WUF31_SHIFT                     (7U)
#define LLWU_PF4_WUF31(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PF4_WUF31_SHIFT)) & LLWU_PF4_WUF31_MASK)

/*! @name MF5 - LLWU Module Flag 5 register */
#define LLWU_MF5_MWUF0_MASK                      (0x1U)
#define LLWU_MF5_MWUF0_SHIFT                     (0U)
#define LLWU_MF5_MWUF0(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_MF5_MWUF0_SHIFT)) & LLWU_MF5_MWUF0_MASK)
#define LLWU_MF5_MWUF1_MASK                      (0x2U)
#define LLWU_MF5_MWUF1_SHIFT                     (1U)
#define LLWU_MF5_MWUF1(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_MF5_MWUF1_SHIFT)) & LLWU_MF5_MWUF1_MASK)
#define LLWU_MF5_MWUF2_MASK                      (0x4U)
#define LLWU_MF5_MWUF2_SHIFT                     (2U)
#define LLWU_MF5_MWUF2(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_MF5_MWUF2_SHIFT)) & LLWU_MF5_MWUF2_MASK)
#define LLWU_MF5_MWUF3_MASK                      (0x8U)
#define LLWU_MF5_MWUF3_SHIFT                     (3U)
#define LLWU_MF5_MWUF3(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_MF5_MWUF3_SHIFT)) & LLWU_MF5_MWUF3_MASK)
#define LLWU_MF5_MWUF4_MASK                      (0x10U)
#define LLWU_MF5_MWUF4_SHIFT                     (4U)
#define LLWU_MF5_MWUF4(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_MF5_MWUF4_SHIFT)) & LLWU_MF5_MWUF4_MASK)
#define LLWU_MF5_MWUF5_MASK                      (0x20U)
#define LLWU_MF5_MWUF5_SHIFT                     (5U)
#define LLWU_MF5_MWUF5(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_MF5_MWUF5_SHIFT)) & LLWU_MF5_MWUF5_MASK)
#define LLWU_MF5_MWUF6_MASK                      (0x40U)
#define LLWU_MF5_MWUF6_SHIFT                     (6U)
#define LLWU_MF5_MWUF6(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_MF5_MWUF6_SHIFT)) & LLWU_MF5_MWUF6_MASK)
#define LLWU_MF5_MWUF7_MASK                      (0x80U)
#define LLWU_MF5_MWUF7_SHIFT                     (7U)
#define LLWU_MF5_MWUF7(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_MF5_MWUF7_SHIFT)) & LLWU_MF5_MWUF7_MASK)

/*! @name FILT1 - LLWU Pin Filter 1 register */
#define LLWU_FILT1_FILTSEL_MASK                  (0x1FU)
#define LLWU_FILT1_FILTSEL_SHIFT                 (0U)
#define LLWU_FILT1_FILTSEL(x)                    (((uint8_t)(((uint8_t)(x)) << LLWU_FILT1_FILTSEL_SHIFT)) & LLWU_FILT1_FILTSEL_MASK)
#define LLWU_FILT1_FILTE_MASK                    (0x60U)
#define LLWU_FILT1_FILTE_SHIFT                   (5U)
#define LLWU_FILT1_FILTE(x)                      (((uint8_t)(((uint8_t)(x)) << LLWU_FILT1_FILTE_SHIFT)) & LLWU_FILT1_FILTE_MASK)
#define LLWU_FILT1_FILTF_MASK                    (0x80U)
#define LLWU_FILT1_FILTF_SHIFT                   (7U)
#define LLWU_FILT1_FILTF(x)                      (((uint8_t)(((uint8_t)(x)) << LLWU_FILT1_FILTF_SHIFT)) & LLWU_FILT1_FILTF_MASK)

/*! @name FILT2 - LLWU Pin Filter 2 register */
#define LLWU_FILT2_FILTSEL_MASK                  (0x1FU)
#define LLWU_FILT2_FILTSEL_SHIFT                 (0U)
#define LLWU_FILT2_FILTSEL(x)                    (((uint8_t)(((uint8_t)(x)) << LLWU_FILT2_FILTSEL_SHIFT)) & LLWU_FILT2_FILTSEL_MASK)
#define LLWU_FILT2_FILTE_MASK                    (0x60U)
#define LLWU_FILT2_FILTE_SHIFT                   (5U)
#define LLWU_FILT2_FILTE(x)                      (((uint8_t)(((uint8_t)(x)) << LLWU_FILT2_FILTE_SHIFT)) & LLWU_FILT2_FILTE_MASK)
#define LLWU_FILT2_FILTF_MASK                    (0x80U)
#define LLWU_FILT2_FILTF_SHIFT                   (7U)
#define LLWU_FILT2_FILTF(x)                      (((uint8_t)(((uint8_t)(x)) << LLWU_FILT2_FILTF_SHIFT)) & LLWU_FILT2_FILTF_MASK)


/*!
 * @}
 */ /* end of group LLWU_Register_Masks */


/* LLWU - Peripheral instance base addresses */
/** Peripheral LLWU base address */
#define LLWU_BASE                                (0x4007C000u)
/** Peripheral LLWU base pointer */
#define LLWU                                     ((LLWU_Type *)LLWU_BASE)
/** Array initializer of LLWU peripheral base addresses */
#define LLWU_BASE_ADDRS                          { LLWU_BASE }
/** Array initializer of LLWU peripheral base pointers */
#define LLWU_BASE_PTRS                           { LLWU }
/** Interrupt vectors for the LLWU peripheral type */
#define LLWU_IRQS                                { LLWU_IRQn }

/*!
 * @}
 */ /* end of group LLWU_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- LPTMR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPTMR_Peripheral_Access_Layer LPTMR Peripheral Access Layer
 * @{
 */

/** LPTMR - Register Layout Typedef */
typedef struct {
  __IO uint32_t CSR;                               /**< Low Power Timer Control Status Register, offset: 0x0 */
  __IO uint32_t PSR;                               /**< Low Power Timer Prescale Register, offset: 0x4 */
  __IO uint32_t CMR;                               /**< Low Power Timer Compare Register, offset: 0x8 */
  __IO uint32_t CNR;                               /**< Low Power Timer Counter Register, offset: 0xC */
} LPTMR_Type;

/* ----------------------------------------------------------------------------
   -- LPTMR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPTMR_Register_Masks LPTMR Register Masks
 * @{
 */

/*! @name CSR - Low Power Timer Control Status Register */
#define LPTMR_CSR_TEN_MASK                       (0x1U)
#define LPTMR_CSR_TEN_SHIFT                      (0U)
#define LPTMR_CSR_TEN(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TEN_SHIFT)) & LPTMR_CSR_TEN_MASK)
#define LPTMR_CSR_TMS_MASK                       (0x2U)
#define LPTMR_CSR_TMS_SHIFT                      (1U)
#define LPTMR_CSR_TMS(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TMS_SHIFT)) & LPTMR_CSR_TMS_MASK)
#define LPTMR_CSR_TFC_MASK                       (0x4U)
#define LPTMR_CSR_TFC_SHIFT                      (2U)
#define LPTMR_CSR_TFC(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TFC_SHIFT)) & LPTMR_CSR_TFC_MASK)
#define LPTMR_CSR_TPP_MASK                       (0x8U)
#define LPTMR_CSR_TPP_SHIFT                      (3U)
#define LPTMR_CSR_TPP(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TPP_SHIFT)) & LPTMR_CSR_TPP_MASK)
#define LPTMR_CSR_TPS_MASK                       (0x30U)
#define LPTMR_CSR_TPS_SHIFT                      (4U)
#define LPTMR_CSR_TPS(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TPS_SHIFT)) & LPTMR_CSR_TPS_MASK)
#define LPTMR_CSR_TIE_MASK                       (0x40U)
#define LPTMR_CSR_TIE_SHIFT                      (6U)
#define LPTMR_CSR_TIE(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TIE_SHIFT)) & LPTMR_CSR_TIE_MASK)
#define LPTMR_CSR_TCF_MASK                       (0x80U)
#define LPTMR_CSR_TCF_SHIFT                      (7U)
#define LPTMR_CSR_TCF(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TCF_SHIFT)) & LPTMR_CSR_TCF_MASK)

/*! @name PSR - Low Power Timer Prescale Register */
#define LPTMR_PSR_PCS_MASK                       (0x3U)
#define LPTMR_PSR_PCS_SHIFT                      (0U)
#define LPTMR_PSR_PCS(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_PSR_PCS_SHIFT)) & LPTMR_PSR_PCS_MASK)
#define LPTMR_PSR_PBYP_MASK                      (0x4U)
#define LPTMR_PSR_PBYP_SHIFT                     (2U)
#define LPTMR_PSR_PBYP(x)                        (((uint32_t)(((uint32_t)(x)) << LPTMR_PSR_PBYP_SHIFT)) & LPTMR_PSR_PBYP_MASK)
#define LPTMR_PSR_PRESCALE_MASK                  (0x78U)
#define LPTMR_PSR_PRESCALE_SHIFT                 (3U)
#define LPTMR_PSR_PRESCALE(x)                    (((uint32_t)(((uint32_t)(x)) << LPTMR_PSR_PRESCALE_SHIFT)) & LPTMR_PSR_PRESCALE_MASK)

/*! @name CMR - Low Power Timer Compare Register */
#define LPTMR_CMR_COMPARE_MASK                   (0xFFFFU)
#define LPTMR_CMR_COMPARE_SHIFT                  (0U)
#define LPTMR_CMR_COMPARE(x)                     (((uint32_t)(((uint32_t)(x)) << LPTMR_CMR_COMPARE_SHIFT)) & LPTMR_CMR_COMPARE_MASK)

/*! @name CNR - Low Power Timer Counter Register */
#define LPTMR_CNR_COUNTER_MASK                   (0xFFFFU)
#define LPTMR_CNR_COUNTER_SHIFT                  (0U)
#define LPTMR_CNR_COUNTER(x)                     (((uint32_t)(((uint32_t)(x)) << LPTMR_CNR_COUNTER_SHIFT)) & LPTMR_CNR_COUNTER_MASK)


/*!
 * @}
 */ /* end of group LPTMR_Register_Masks */


/* LPTMR - Peripheral instance base addresses */
/** Peripheral LPTMR0 base address */
#define LPTMR0_BASE                              (0x40040000u)
/** Peripheral LPTMR0 base pointer */
#define LPTMR0                                   ((LPTMR_Type *)LPTMR0_BASE)
/** Array initializer of LPTMR peripheral base addresses */
#define LPTMR_BASE_ADDRS                         { LPTMR0_BASE }
/** Array initializer of LPTMR peripheral base pointers */
#define LPTMR_BASE_PTRS                          { LPTMR0 }
/** Interrupt vectors for the LPTMR peripheral type */
#define LPTMR_IRQS                               { LPTMR0_IRQn }

/*!
 * @}
 */ /* end of group LPTMR_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- MCG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCG_Peripheral_Access_Layer MCG Peripheral Access Layer
 * @{
 */

/** MCG - Register Layout Typedef */
typedef struct {
  __IO uint8_t C1;                                 /**< MCG Control 1 Register, offset: 0x0 */
  __IO uint8_t C2;                                 /**< MCG Control 2 Register, offset: 0x1 */
  __IO uint8_t C3;                                 /**< MCG Control 3 Register, offset: 0x2 */
  __IO uint8_t C4;                                 /**< MCG Control 4 Register, offset: 0x3 */
  __IO uint8_t C5;                                 /**< MCG Control 5 Register, offset: 0x4 */
  __IO uint8_t C6;                                 /**< MCG Control 6 Register, offset: 0x5 */
  __IO uint8_t S;                                  /**< MCG Status Register, offset: 0x6 */
       uint8_t RESERVED_0[1];
  __IO uint8_t SC;                                 /**< MCG Status and Control Register, offset: 0x8 */
       uint8_t RESERVED_1[1];
  __IO uint8_t ATCVH;                              /**< MCG Auto Trim Compare Value High Register, offset: 0xA */
  __IO uint8_t ATCVL;                              /**< MCG Auto Trim Compare Value Low Register, offset: 0xB */
       uint8_t RESERVED_2[1];
  __IO uint8_t C8;                                 /**< MCG Control 8 Register, offset: 0xD */
} MCG_Type;

/* ----------------------------------------------------------------------------
   -- MCG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCG_Register_Masks MCG Register Masks
 * @{
 */

/*! @name C1 - MCG Control 1 Register */
#define MCG_C1_IREFSTEN_MASK                     (0x1U)
#define MCG_C1_IREFSTEN_SHIFT                    (0U)
#define MCG_C1_IREFSTEN(x)                       (((uint8_t)(((uint8_t)(x)) << MCG_C1_IREFSTEN_SHIFT)) & MCG_C1_IREFSTEN_MASK)
#define MCG_C1_IRCLKEN_MASK                      (0x2U)
#define MCG_C1_IRCLKEN_SHIFT                     (1U)
#define MCG_C1_IRCLKEN(x)                        (((uint8_t)(((uint8_t)(x)) << MCG_C1_IRCLKEN_SHIFT)) & MCG_C1_IRCLKEN_MASK)
#define MCG_C1_IREFS_MASK                        (0x4U)
#define MCG_C1_IREFS_SHIFT                       (2U)
#define MCG_C1_IREFS(x)                          (((uint8_t)(((uint8_t)(x)) << MCG_C1_IREFS_SHIFT)) & MCG_C1_IREFS_MASK)
#define MCG_C1_FRDIV_MASK                        (0x38U)
#define MCG_C1_FRDIV_SHIFT                       (3U)
#define MCG_C1_FRDIV(x)                          (((uint8_t)(((uint8_t)(x)) << MCG_C1_FRDIV_SHIFT)) & MCG_C1_FRDIV_MASK)
#define MCG_C1_CLKS_MASK                         (0xC0U)
#define MCG_C1_CLKS_SHIFT                        (6U)
#define MCG_C1_CLKS(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_C1_CLKS_SHIFT)) & MCG_C1_CLKS_MASK)

/*! @name C2 - MCG Control 2 Register */
#define MCG_C2_IRCS_MASK                         (0x1U)
#define MCG_C2_IRCS_SHIFT                        (0U)
#define MCG_C2_IRCS(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_C2_IRCS_SHIFT)) & MCG_C2_IRCS_MASK)
#define MCG_C2_LP_MASK                           (0x2U)
#define MCG_C2_LP_SHIFT                          (1U)
#define MCG_C2_LP(x)                             (((uint8_t)(((uint8_t)(x)) << MCG_C2_LP_SHIFT)) & MCG_C2_LP_MASK)
#define MCG_C2_EREFS_MASK                        (0x4U)
#define MCG_C2_EREFS_SHIFT                       (2U)
#define MCG_C2_EREFS(x)                          (((uint8_t)(((uint8_t)(x)) << MCG_C2_EREFS_SHIFT)) & MCG_C2_EREFS_MASK)
#define MCG_C2_HGO_MASK                          (0x8U)
#define MCG_C2_HGO_SHIFT                         (3U)
#define MCG_C2_HGO(x)                            (((uint8_t)(((uint8_t)(x)) << MCG_C2_HGO_SHIFT)) & MCG_C2_HGO_MASK)
#define MCG_C2_RANGE_MASK                        (0x30U)
#define MCG_C2_RANGE_SHIFT                       (4U)
#define MCG_C2_RANGE(x)                          (((uint8_t)(((uint8_t)(x)) << MCG_C2_RANGE_SHIFT)) & MCG_C2_RANGE_MASK)
#define MCG_C2_FCFTRIM_MASK                      (0x40U)
#define MCG_C2_FCFTRIM_SHIFT                     (6U)
#define MCG_C2_FCFTRIM(x)                        (((uint8_t)(((uint8_t)(x)) << MCG_C2_FCFTRIM_SHIFT)) & MCG_C2_FCFTRIM_MASK)
#define MCG_C2_LOCRE0_MASK                       (0x80U)
#define MCG_C2_LOCRE0_SHIFT                      (7U)
#define MCG_C2_LOCRE0(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_C2_LOCRE0_SHIFT)) & MCG_C2_LOCRE0_MASK)

/*! @name C3 - MCG Control 3 Register */
#define MCG_C3_SCTRIM_MASK                       (0xFFU)
#define MCG_C3_SCTRIM_SHIFT                      (0U)
#define MCG_C3_SCTRIM(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_C3_SCTRIM_SHIFT)) & MCG_C3_SCTRIM_MASK)

/*! @name C4 - MCG Control 4 Register */
#define MCG_C4_SCFTRIM_MASK                      (0x1U)
#define MCG_C4_SCFTRIM_SHIFT                     (0U)
#define MCG_C4_SCFTRIM(x)                        (((uint8_t)(((uint8_t)(x)) << MCG_C4_SCFTRIM_SHIFT)) & MCG_C4_SCFTRIM_MASK)
#define MCG_C4_FCTRIM_MASK                       (0x1EU)
#define MCG_C4_FCTRIM_SHIFT                      (1U)
#define MCG_C4_FCTRIM(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_C4_FCTRIM_SHIFT)) & MCG_C4_FCTRIM_MASK)
#define MCG_C4_DRST_DRS_MASK                     (0x60U)
#define MCG_C4_DRST_DRS_SHIFT                    (5U)
#define MCG_C4_DRST_DRS(x)                       (((uint8_t)(((uint8_t)(x)) << MCG_C4_DRST_DRS_SHIFT)) & MCG_C4_DRST_DRS_MASK)
#define MCG_C4_DMX32_MASK                        (0x80U)
#define MCG_C4_DMX32_SHIFT                       (7U)
#define MCG_C4_DMX32(x)                          (((uint8_t)(((uint8_t)(x)) << MCG_C4_DMX32_SHIFT)) & MCG_C4_DMX32_MASK)

/*! @name C5 - MCG Control 5 Register */
#define MCG_C5_PRDIV_MASK                        (0x7U)
#define MCG_C5_PRDIV_SHIFT                       (0U)
#define MCG_C5_PRDIV(x)                          (((uint8_t)(((uint8_t)(x)) << MCG_C5_PRDIV_SHIFT)) & MCG_C5_PRDIV_MASK)
#define MCG_C5_PLLSTEN_MASK                      (0x20U)
#define MCG_C5_PLLSTEN_SHIFT                     (5U)
#define MCG_C5_PLLSTEN(x)                        (((uint8_t)(((uint8_t)(x)) << MCG_C5_PLLSTEN_SHIFT)) & MCG_C5_PLLSTEN_MASK)
#define MCG_C5_PLLCLKEN_MASK                     (0x40U)
#define MCG_C5_PLLCLKEN_SHIFT                    (6U)
#define MCG_C5_PLLCLKEN(x)                       (((uint8_t)(((uint8_t)(x)) << MCG_C5_PLLCLKEN_SHIFT)) & MCG_C5_PLLCLKEN_MASK)

/*! @name C6 - MCG Control 6 Register */
#define MCG_C6_VDIV_MASK                         (0x1FU)
#define MCG_C6_VDIV_SHIFT                        (0U)
#define MCG_C6_VDIV(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_C6_VDIV_SHIFT)) & MCG_C6_VDIV_MASK)
#define MCG_C6_CME0_MASK                         (0x20U)
#define MCG_C6_CME0_SHIFT                        (5U)
#define MCG_C6_CME0(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_C6_CME0_SHIFT)) & MCG_C6_CME0_MASK)
#define MCG_C6_PLLS_MASK                         (0x40U)
#define MCG_C6_PLLS_SHIFT                        (6U)
#define MCG_C6_PLLS(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_C6_PLLS_SHIFT)) & MCG_C6_PLLS_MASK)
#define MCG_C6_LOLIE0_MASK                       (0x80U)
#define MCG_C6_LOLIE0_SHIFT                      (7U)
#define MCG_C6_LOLIE0(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_C6_LOLIE0_SHIFT)) & MCG_C6_LOLIE0_MASK)

/*! @name S - MCG Status Register */
#define MCG_S_IRCST_MASK                         (0x1U)
#define MCG_S_IRCST_SHIFT                        (0U)
#define MCG_S_IRCST(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_S_IRCST_SHIFT)) & MCG_S_IRCST_MASK)
#define MCG_S_OSCINIT0_MASK                      (0x2U)
#define MCG_S_OSCINIT0_SHIFT                     (1U)
#define MCG_S_OSCINIT0(x)                        (((uint8_t)(((uint8_t)(x)) << MCG_S_OSCINIT0_SHIFT)) & MCG_S_OSCINIT0_MASK)
#define MCG_S_CLKST_MASK                         (0xCU)
#define MCG_S_CLKST_SHIFT                        (2U)
#define MCG_S_CLKST(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_S_CLKST_SHIFT)) & MCG_S_CLKST_MASK)
#define MCG_S_IREFST_MASK                        (0x10U)
#define MCG_S_IREFST_SHIFT                       (4U)
#define MCG_S_IREFST(x)                          (((uint8_t)(((uint8_t)(x)) << MCG_S_IREFST_SHIFT)) & MCG_S_IREFST_MASK)
#define MCG_S_PLLST_MASK                         (0x20U)
#define MCG_S_PLLST_SHIFT                        (5U)
#define MCG_S_PLLST(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_S_PLLST_SHIFT)) & MCG_S_PLLST_MASK)
#define MCG_S_LOCK0_MASK                         (0x40U)
#define MCG_S_LOCK0_SHIFT                        (6U)
#define MCG_S_LOCK0(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_S_LOCK0_SHIFT)) & MCG_S_LOCK0_MASK)
#define MCG_S_LOLS0_MASK                         (0x80U)
#define MCG_S_LOLS0_SHIFT                        (7U)
#define MCG_S_LOLS0(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_S_LOLS0_SHIFT)) & MCG_S_LOLS0_MASK)

/*! @name SC - MCG Status and Control Register */
#define MCG_SC_LOCS0_MASK                        (0x1U)
#define MCG_SC_LOCS0_SHIFT                       (0U)
#define MCG_SC_LOCS0(x)                          (((uint8_t)(((uint8_t)(x)) << MCG_SC_LOCS0_SHIFT)) & MCG_SC_LOCS0_MASK)
#define MCG_SC_FCRDIV_MASK                       (0xEU)
#define MCG_SC_FCRDIV_SHIFT                      (1U)
#define MCG_SC_FCRDIV(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_SC_FCRDIV_SHIFT)) & MCG_SC_FCRDIV_MASK)
#define MCG_SC_FLTPRSRV_MASK                     (0x10U)
#define MCG_SC_FLTPRSRV_SHIFT                    (4U)
#define MCG_SC_FLTPRSRV(x)                       (((uint8_t)(((uint8_t)(x)) << MCG_SC_FLTPRSRV_SHIFT)) & MCG_SC_FLTPRSRV_MASK)
#define MCG_SC_ATMF_MASK                         (0x20U)
#define MCG_SC_ATMF_SHIFT                        (5U)
#define MCG_SC_ATMF(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_SC_ATMF_SHIFT)) & MCG_SC_ATMF_MASK)
#define MCG_SC_ATMS_MASK                         (0x40U)
#define MCG_SC_ATMS_SHIFT                        (6U)
#define MCG_SC_ATMS(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_SC_ATMS_SHIFT)) & MCG_SC_ATMS_MASK)
#define MCG_SC_ATME_MASK                         (0x80U)
#define MCG_SC_ATME_SHIFT                        (7U)
#define MCG_SC_ATME(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_SC_ATME_SHIFT)) & MCG_SC_ATME_MASK)

/*! @name ATCVH - MCG Auto Trim Compare Value High Register */
#define MCG_ATCVH_ATCVH_MASK                     (0xFFU)
#define MCG_ATCVH_ATCVH_SHIFT                    (0U)
#define MCG_ATCVH_ATCVH(x)                       (((uint8_t)(((uint8_t)(x)) << MCG_ATCVH_ATCVH_SHIFT)) & MCG_ATCVH_ATCVH_MASK)

/*! @name ATCVL - MCG Auto Trim Compare Value Low Register */
#define MCG_ATCVL_ATCVL_MASK                     (0xFFU)
#define MCG_ATCVL_ATCVL_SHIFT                    (0U)
#define MCG_ATCVL_ATCVL(x)                       (((uint8_t)(((uint8_t)(x)) << MCG_ATCVL_ATCVL_SHIFT)) & MCG_ATCVL_ATCVL_MASK)

/*! @name C8 - MCG Control 8 Register */
#define MCG_C8_LOLRE_MASK                        (0x40U)
#define MCG_C8_LOLRE_SHIFT                       (6U)
#define MCG_C8_LOLRE(x)                          (((uint8_t)(((uint8_t)(x)) << MCG_C8_LOLRE_SHIFT)) & MCG_C8_LOLRE_MASK)


/*!
 * @}
 */ /* end of group MCG_Register_Masks */


/* MCG - Peripheral instance base addresses */
/** Peripheral MCG base address */
#define MCG_BASE                                 (0x40064000u)
/** Peripheral MCG base pointer */
#define MCG                                      ((MCG_Type *)MCG_BASE)
/** Array initializer of MCG peripheral base addresses */
#define MCG_BASE_ADDRS                           { MCG_BASE }
/** Array initializer of MCG peripheral base pointers */
#define MCG_BASE_PTRS                            { MCG }
/** Interrupt vectors for the MCG peripheral type */
#define MCG_IRQS                                 { MCG_IRQn }
/* MCG C5[PLLCLKEN0] backward compatibility */
#define MCG_C5_PLLCLKEN0_MASK         (MCG_C5_PLLCLKEN_MASK)
#define MCG_C5_PLLCLKEN0_SHIFT        (MCG_C5_PLLCLKEN_SHIFT)
#define MCG_C5_PLLCLKEN0_WIDTH        (MCG_C5_PLLCLKEN_WIDTH)
#define MCG_C5_PLLCLKEN0(x)           (MCG_C5_PLLCLKEN(x))

/* MCG C5[PLLSTEN0] backward compatibility */
#define MCG_C5_PLLSTEN0_MASK         (MCG_C5_PLLSTEN_MASK)
#define MCG_C5_PLLSTEN0_SHIFT        (MCG_C5_PLLSTEN_SHIFT)
#define MCG_C5_PLLSTEN0_WIDTH        (MCG_C5_PLLSTEN_WIDTH)
#define MCG_C5_PLLSTEN0(x)           (MCG_C5_PLLSTEN(x))

/* MCG C5[PRDIV0] backward compatibility */
#define MCG_C5_PRDIV0_MASK         (MCG_C5_PRDIV_MASK)
#define MCG_C5_PRDIV0_SHIFT        (MCG_C5_PRDIV_SHIFT)
#define MCG_C5_PRDIV0_WIDTH        (MCG_C5_PRDIV_WIDTH)
#define MCG_C5_PRDIV0(x)           (MCG_C5_PRDIV(x))

/* MCG C6[VDIV0] backward compatibility */
#define MCG_C6_VDIV0_MASK         (MCG_C6_VDIV_MASK)
#define MCG_C6_VDIV0_SHIFT        (MCG_C6_VDIV_SHIFT)
#define MCG_C6_VDIV0_WIDTH        (MCG_C6_VDIV_WIDTH)
#define MCG_C6_VDIV0(x)           (MCG_C6_VDIV(x))


/*!
 * @}
 */ /* end of group MCG_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- MCM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Peripheral_Access_Layer MCM Peripheral Access Layer
 * @{
 */

/** MCM - Register Layout Typedef */
typedef struct {
  __I  uint32_t PCT;                               /**< Processor core type, offset: 0x0 */
       uint8_t RESERVED_0[8];
  __IO uint32_t CR;                                /**< Control Register, offset: 0xC */
  __IO uint32_t ISCR;                              /**< Interrupt Status and Control Register, offset: 0x10 */
       uint8_t RESERVED_1[32];
  __IO uint32_t CPO;                               /**< Compute Only Operation Control Register, offset: 0x34 */
       uint8_t RESERVED_2[968];
  __I  uint32_t LMEM[5];                           /**< Local Memory General Descriptor Register, array offset: 0x400, array step: 0x4 */
} MCM_Type;

/* ----------------------------------------------------------------------------
   -- MCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Masks MCM Register Masks
 * @{
 */

/*! @name PCT - Processor core type */
#define MCM_PCT_PLREV_MASK                       (0xFFFFU)
#define MCM_PCT_PLREV_SHIFT                      (0U)
#define MCM_PCT_PLREV(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_PCT_PLREV_SHIFT)) & MCM_PCT_PLREV_MASK)
#define MCM_PCT_PCT_MASK                         (0xFFFF0000U)
#define MCM_PCT_PCT_SHIFT                        (16U)
#define MCM_PCT_PCT(x)                           (((uint32_t)(((uint32_t)(x)) << MCM_PCT_PCT_SHIFT)) & MCM_PCT_PCT_MASK)

/*! @name CR - Control Register */
#define MCM_CR_AHBSPRI_MASK                      (0x8000000U)
#define MCM_CR_AHBSPRI_SHIFT                     (27U)
#define MCM_CR_AHBSPRI(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_CR_AHBSPRI_SHIFT)) & MCM_CR_AHBSPRI_MASK)

/*! @name ISCR - Interrupt Status and Control Register */
#define MCM_ISCR_FIOC_MASK                       (0x100U)
#define MCM_ISCR_FIOC_SHIFT                      (8U)
#define MCM_ISCR_FIOC(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FIOC_SHIFT)) & MCM_ISCR_FIOC_MASK)
#define MCM_ISCR_FDZC_MASK                       (0x200U)
#define MCM_ISCR_FDZC_SHIFT                      (9U)
#define MCM_ISCR_FDZC(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FDZC_SHIFT)) & MCM_ISCR_FDZC_MASK)
#define MCM_ISCR_FOFC_MASK                       (0x400U)
#define MCM_ISCR_FOFC_SHIFT                      (10U)
#define MCM_ISCR_FOFC(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FOFC_SHIFT)) & MCM_ISCR_FOFC_MASK)
#define MCM_ISCR_FUFC_MASK                       (0x800U)
#define MCM_ISCR_FUFC_SHIFT                      (11U)
#define MCM_ISCR_FUFC(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FUFC_SHIFT)) & MCM_ISCR_FUFC_MASK)
#define MCM_ISCR_FIXC_MASK                       (0x1000U)
#define MCM_ISCR_FIXC_SHIFT                      (12U)
#define MCM_ISCR_FIXC(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FIXC_SHIFT)) & MCM_ISCR_FIXC_MASK)
#define MCM_ISCR_FIDC_MASK                       (0x8000U)
#define MCM_ISCR_FIDC_SHIFT                      (15U)
#define MCM_ISCR_FIDC(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FIDC_SHIFT)) & MCM_ISCR_FIDC_MASK)
#define MCM_ISCR_FIOCE_MASK                      (0x1000000U)
#define MCM_ISCR_FIOCE_SHIFT                     (24U)
#define MCM_ISCR_FIOCE(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FIOCE_SHIFT)) & MCM_ISCR_FIOCE_MASK)
#define MCM_ISCR_FDZCE_MASK                      (0x2000000U)
#define MCM_ISCR_FDZCE_SHIFT                     (25U)
#define MCM_ISCR_FDZCE(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FDZCE_SHIFT)) & MCM_ISCR_FDZCE_MASK)
#define MCM_ISCR_FOFCE_MASK                      (0x4000000U)
#define MCM_ISCR_FOFCE_SHIFT                     (26U)
#define MCM_ISCR_FOFCE(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FOFCE_SHIFT)) & MCM_ISCR_FOFCE_MASK)
#define MCM_ISCR_FUFCE_MASK                      (0x8000000U)
#define MCM_ISCR_FUFCE_SHIFT                     (27U)
#define MCM_ISCR_FUFCE(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FUFCE_SHIFT)) & MCM_ISCR_FUFCE_MASK)
#define MCM_ISCR_FIXCE_MASK                      (0x10000000U)
#define MCM_ISCR_FIXCE_SHIFT                     (28U)
#define MCM_ISCR_FIXCE(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FIXCE_SHIFT)) & MCM_ISCR_FIXCE_MASK)
#define MCM_ISCR_FIDCE_MASK                      (0x80000000U)
#define MCM_ISCR_FIDCE_SHIFT                     (31U)
#define MCM_ISCR_FIDCE(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FIDCE_SHIFT)) & MCM_ISCR_FIDCE_MASK)

/*! @name CPO - Compute Only Operation Control Register */
#define MCM_CPO_CPOREQ_MASK                      (0x1U)
#define MCM_CPO_CPOREQ_SHIFT                     (0U)
#define MCM_CPO_CPOREQ(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_CPO_CPOREQ_SHIFT)) & MCM_CPO_CPOREQ_MASK)
#define MCM_CPO_CPOACK_MASK                      (0x2U)
#define MCM_CPO_CPOACK_SHIFT                     (1U)
#define MCM_CPO_CPOACK(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_CPO_CPOACK_SHIFT)) & MCM_CPO_CPOACK_MASK)

/*! @name LMEM - Local Memory General Descriptor Register */
#define MCM_LMEM_LMEM_Type_MASK                  (0xE000U)
#define MCM_LMEM_LMEM_Type_SHIFT                 (13U)
#define MCM_LMEM_LMEM_Type(x)                    (((uint32_t)(((uint32_t)(x)) << MCM_LMEM_LMEM_Type_SHIFT)) & MCM_LMEM_LMEM_Type_MASK)
#define MCM_LMEM_LMEM_Width_MASK                 (0xE0000U)
#define MCM_LMEM_LMEM_Width_SHIFT                (17U)
#define MCM_LMEM_LMEM_Width(x)                   (((uint32_t)(((uint32_t)(x)) << MCM_LMEM_LMEM_Width_SHIFT)) & MCM_LMEM_LMEM_Width_MASK)
#define MCM_LMEM_LMEM_Ways_MASK                  (0xF00000U)
#define MCM_LMEM_LMEM_Ways_SHIFT                 (20U)
#define MCM_LMEM_LMEM_Ways(x)                    (((uint32_t)(((uint32_t)(x)) << MCM_LMEM_LMEM_Ways_SHIFT)) & MCM_LMEM_LMEM_Ways_MASK)
#define MCM_LMEM_LMEM_Size_MASK                  (0xF000000U)
#define MCM_LMEM_LMEM_Size_SHIFT                 (24U)
#define MCM_LMEM_LMEM_Size(x)                    (((uint32_t)(((uint32_t)(x)) << MCM_LMEM_LMEM_Size_SHIFT)) & MCM_LMEM_LMEM_Size_MASK)
#define MCM_LMEM_LMEM_Valid_MASK                 (0x80000000U)
#define MCM_LMEM_LMEM_Valid_SHIFT                (31U)
#define MCM_LMEM_LMEM_Valid(x)                   (((uint32_t)(((uint32_t)(x)) << MCM_LMEM_LMEM_Valid_SHIFT)) & MCM_LMEM_LMEM_Valid_MASK)

/* The count of MCM_LMEM */
#define MCM_LMEM_COUNT                           (5U)


/*!
 * @}
 */ /* end of group MCM_Register_Masks */


/* MCM - Peripheral instance base addresses */
/** Peripheral MCM base address */
#define MCM_BASE                                 (0xE0080000u)
/** Peripheral MCM base pointer */
#define MCM                                      ((MCM_Type *)MCM_BASE)
/** Array initializer of MCM peripheral base addresses */
#define MCM_BASE_ADDRS                           { MCM_BASE }
/** Array initializer of MCM peripheral base pointers */
#define MCM_BASE_PTRS                            { MCM }
/** Interrupt vectors for the MCM peripheral type */
#define MCM_IRQS                                 { MCM_IRQn }

/*!
 * @}
 */ /* end of group MCM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- MPU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MPU_Peripheral_Access_Layer MPU Peripheral Access Layer
 * @{
 */

/** MPU - Register Layout Typedef */
typedef struct {
  __IO uint32_t CESR;                              /**< Control/Error Status Register, offset: 0x0 */
       uint8_t RESERVED_0[12];
  struct {                                         /* offset: 0x10, array step: 0x8 */
    __I  uint32_t EAR;                               /**< Error Address Register, slave port n, array offset: 0x10, array step: 0x8 */
    __I  uint32_t EDR;                               /**< Error Detail Register, slave port n, array offset: 0x14, array step: 0x8 */
  } SP[5];
       uint8_t RESERVED_1[968];
  __IO uint32_t WORD[12][4];                       /**< Region Descriptor n, Word 0..Region Descriptor n, Word 3, array offset: 0x400, array step: index*0x10, index2*0x4 */
       uint8_t RESERVED_2[832];
  __IO uint32_t RGDAAC[12];                        /**< Region Descriptor Alternate Access Control n, array offset: 0x800, array step: 0x4 */
} MPU_Type;

/* ----------------------------------------------------------------------------
   -- MPU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MPU_Register_Masks MPU Register Masks
 * @{
 */

/*! @name CESR - Control/Error Status Register */
#define MPU_CESR_VLD_MASK                        (0x1U)
#define MPU_CESR_VLD_SHIFT                       (0U)
#define MPU_CESR_VLD(x)                          (((uint32_t)(((uint32_t)(x)) << MPU_CESR_VLD_SHIFT)) & MPU_CESR_VLD_MASK)
#define MPU_CESR_NRGD_MASK                       (0xF00U)
#define MPU_CESR_NRGD_SHIFT                      (8U)
#define MPU_CESR_NRGD(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_CESR_NRGD_SHIFT)) & MPU_CESR_NRGD_MASK)
#define MPU_CESR_NSP_MASK                        (0xF000U)
#define MPU_CESR_NSP_SHIFT                       (12U)
#define MPU_CESR_NSP(x)                          (((uint32_t)(((uint32_t)(x)) << MPU_CESR_NSP_SHIFT)) & MPU_CESR_NSP_MASK)
#define MPU_CESR_HRL_MASK                        (0xF0000U)
#define MPU_CESR_HRL_SHIFT                       (16U)
#define MPU_CESR_HRL(x)                          (((uint32_t)(((uint32_t)(x)) << MPU_CESR_HRL_SHIFT)) & MPU_CESR_HRL_MASK)
#define MPU_CESR_SPERR_MASK                      (0xF8000000U)
#define MPU_CESR_SPERR_SHIFT                     (27U)
#define MPU_CESR_SPERR(x)                        (((uint32_t)(((uint32_t)(x)) << MPU_CESR_SPERR_SHIFT)) & MPU_CESR_SPERR_MASK)

/*! @name EAR - Error Address Register, slave port n */
#define MPU_EAR_EADDR_MASK                       (0xFFFFFFFFU)
#define MPU_EAR_EADDR_SHIFT                      (0U)
#define MPU_EAR_EADDR(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_EAR_EADDR_SHIFT)) & MPU_EAR_EADDR_MASK)

/* The count of MPU_EAR */
#define MPU_EAR_COUNT                            (5U)

/*! @name EDR - Error Detail Register, slave port n */
#define MPU_EDR_ERW_MASK                         (0x1U)
#define MPU_EDR_ERW_SHIFT                        (0U)
#define MPU_EDR_ERW(x)                           (((uint32_t)(((uint32_t)(x)) << MPU_EDR_ERW_SHIFT)) & MPU_EDR_ERW_MASK)
#define MPU_EDR_EATTR_MASK                       (0xEU)
#define MPU_EDR_EATTR_SHIFT                      (1U)
#define MPU_EDR_EATTR(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_EDR_EATTR_SHIFT)) & MPU_EDR_EATTR_MASK)
#define MPU_EDR_EMN_MASK                         (0xF0U)
#define MPU_EDR_EMN_SHIFT                        (4U)
#define MPU_EDR_EMN(x)                           (((uint32_t)(((uint32_t)(x)) << MPU_EDR_EMN_SHIFT)) & MPU_EDR_EMN_MASK)
#define MPU_EDR_EPID_MASK                        (0xFF00U)
#define MPU_EDR_EPID_SHIFT                       (8U)
#define MPU_EDR_EPID(x)                          (((uint32_t)(((uint32_t)(x)) << MPU_EDR_EPID_SHIFT)) & MPU_EDR_EPID_MASK)
#define MPU_EDR_EACD_MASK                        (0xFFFF0000U)
#define MPU_EDR_EACD_SHIFT                       (16U)
#define MPU_EDR_EACD(x)                          (((uint32_t)(((uint32_t)(x)) << MPU_EDR_EACD_SHIFT)) & MPU_EDR_EACD_MASK)

/* The count of MPU_EDR */
#define MPU_EDR_COUNT                            (5U)

/*! @name WORD - Region Descriptor n, Word 0..Region Descriptor n, Word 3 */
#define MPU_WORD_VLD_MASK                        (0x1U)
#define MPU_WORD_VLD_SHIFT                       (0U)
#define MPU_WORD_VLD(x)                          (((uint32_t)(((uint32_t)(x)) << MPU_WORD_VLD_SHIFT)) & MPU_WORD_VLD_MASK)
#define MPU_WORD_M0UM_MASK                       (0x7U)
#define MPU_WORD_M0UM_SHIFT                      (0U)
#define MPU_WORD_M0UM(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M0UM_SHIFT)) & MPU_WORD_M0UM_MASK)
#define MPU_WORD_M0SM_MASK                       (0x18U)
#define MPU_WORD_M0SM_SHIFT                      (3U)
#define MPU_WORD_M0SM(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M0SM_SHIFT)) & MPU_WORD_M0SM_MASK)
#define MPU_WORD_M0PE_MASK                       (0x20U)
#define MPU_WORD_M0PE_SHIFT                      (5U)
#define MPU_WORD_M0PE(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M0PE_SHIFT)) & MPU_WORD_M0PE_MASK)
#define MPU_WORD_ENDADDR_MASK                    (0xFFFFFFE0U)
#define MPU_WORD_ENDADDR_SHIFT                   (5U)
#define MPU_WORD_ENDADDR(x)                      (((uint32_t)(((uint32_t)(x)) << MPU_WORD_ENDADDR_SHIFT)) & MPU_WORD_ENDADDR_MASK)
#define MPU_WORD_SRTADDR_MASK                    (0xFFFFFFE0U)
#define MPU_WORD_SRTADDR_SHIFT                   (5U)
#define MPU_WORD_SRTADDR(x)                      (((uint32_t)(((uint32_t)(x)) << MPU_WORD_SRTADDR_SHIFT)) & MPU_WORD_SRTADDR_MASK)
#define MPU_WORD_M1UM_MASK                       (0x1C0U)
#define MPU_WORD_M1UM_SHIFT                      (6U)
#define MPU_WORD_M1UM(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M1UM_SHIFT)) & MPU_WORD_M1UM_MASK)
#define MPU_WORD_M1SM_MASK                       (0x600U)
#define MPU_WORD_M1SM_SHIFT                      (9U)
#define MPU_WORD_M1SM(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M1SM_SHIFT)) & MPU_WORD_M1SM_MASK)
#define MPU_WORD_M1PE_MASK                       (0x800U)
#define MPU_WORD_M1PE_SHIFT                      (11U)
#define MPU_WORD_M1PE(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M1PE_SHIFT)) & MPU_WORD_M1PE_MASK)
#define MPU_WORD_M2UM_MASK                       (0x7000U)
#define MPU_WORD_M2UM_SHIFT                      (12U)
#define MPU_WORD_M2UM(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M2UM_SHIFT)) & MPU_WORD_M2UM_MASK)
#define MPU_WORD_M2SM_MASK                       (0x18000U)
#define MPU_WORD_M2SM_SHIFT                      (15U)
#define MPU_WORD_M2SM(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M2SM_SHIFT)) & MPU_WORD_M2SM_MASK)
#define MPU_WORD_PIDMASK_MASK                    (0xFF0000U)
#define MPU_WORD_PIDMASK_SHIFT                   (16U)
#define MPU_WORD_PIDMASK(x)                      (((uint32_t)(((uint32_t)(x)) << MPU_WORD_PIDMASK_SHIFT)) & MPU_WORD_PIDMASK_MASK)
#define MPU_WORD_M2PE_MASK                       (0x20000U)
#define MPU_WORD_M2PE_SHIFT                      (17U)
#define MPU_WORD_M2PE(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M2PE_SHIFT)) & MPU_WORD_M2PE_MASK)
#define MPU_WORD_M3UM_MASK                       (0x1C0000U)
#define MPU_WORD_M3UM_SHIFT                      (18U)
#define MPU_WORD_M3UM(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M3UM_SHIFT)) & MPU_WORD_M3UM_MASK)
#define MPU_WORD_M3SM_MASK                       (0x600000U)
#define MPU_WORD_M3SM_SHIFT                      (21U)
#define MPU_WORD_M3SM(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M3SM_SHIFT)) & MPU_WORD_M3SM_MASK)
#define MPU_WORD_M3PE_MASK                       (0x800000U)
#define MPU_WORD_M3PE_SHIFT                      (23U)
#define MPU_WORD_M3PE(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M3PE_SHIFT)) & MPU_WORD_M3PE_MASK)
#define MPU_WORD_PID_MASK                        (0xFF000000U)
#define MPU_WORD_PID_SHIFT                       (24U)
#define MPU_WORD_PID(x)                          (((uint32_t)(((uint32_t)(x)) << MPU_WORD_PID_SHIFT)) & MPU_WORD_PID_MASK)
#define MPU_WORD_M4WE_MASK                       (0x1000000U)
#define MPU_WORD_M4WE_SHIFT                      (24U)
#define MPU_WORD_M4WE(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M4WE_SHIFT)) & MPU_WORD_M4WE_MASK)
#define MPU_WORD_M4RE_MASK                       (0x2000000U)
#define MPU_WORD_M4RE_SHIFT                      (25U)
#define MPU_WORD_M4RE(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M4RE_SHIFT)) & MPU_WORD_M4RE_MASK)
#define MPU_WORD_M5WE_MASK                       (0x4000000U)
#define MPU_WORD_M5WE_SHIFT                      (26U)
#define MPU_WORD_M5WE(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M5WE_SHIFT)) & MPU_WORD_M5WE_MASK)
#define MPU_WORD_M5RE_MASK                       (0x8000000U)
#define MPU_WORD_M5RE_SHIFT                      (27U)
#define MPU_WORD_M5RE(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M5RE_SHIFT)) & MPU_WORD_M5RE_MASK)
#define MPU_WORD_M6WE_MASK                       (0x10000000U)
#define MPU_WORD_M6WE_SHIFT                      (28U)
#define MPU_WORD_M6WE(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M6WE_SHIFT)) & MPU_WORD_M6WE_MASK)
#define MPU_WORD_M6RE_MASK                       (0x20000000U)
#define MPU_WORD_M6RE_SHIFT                      (29U)
#define MPU_WORD_M6RE(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M6RE_SHIFT)) & MPU_WORD_M6RE_MASK)
#define MPU_WORD_M7WE_MASK                       (0x40000000U)
#define MPU_WORD_M7WE_SHIFT                      (30U)
#define MPU_WORD_M7WE(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M7WE_SHIFT)) & MPU_WORD_M7WE_MASK)
#define MPU_WORD_M7RE_MASK                       (0x80000000U)
#define MPU_WORD_M7RE_SHIFT                      (31U)
#define MPU_WORD_M7RE(x)                         (((uint32_t)(((uint32_t)(x)) << MPU_WORD_M7RE_SHIFT)) & MPU_WORD_M7RE_MASK)

/* The count of MPU_WORD */
#define MPU_WORD_COUNT                           (12U)

/* The count of MPU_WORD */
#define MPU_WORD_COUNT2                          (4U)

/*! @name RGDAAC - Region Descriptor Alternate Access Control n */
#define MPU_RGDAAC_M0UM_MASK                     (0x7U)
#define MPU_RGDAAC_M0UM_SHIFT                    (0U)
#define MPU_RGDAAC_M0UM(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M0UM_SHIFT)) & MPU_RGDAAC_M0UM_MASK)
#define MPU_RGDAAC_M0SM_MASK                     (0x18U)
#define MPU_RGDAAC_M0SM_SHIFT                    (3U)
#define MPU_RGDAAC_M0SM(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M0SM_SHIFT)) & MPU_RGDAAC_M0SM_MASK)
#define MPU_RGDAAC_M0PE_MASK                     (0x20U)
#define MPU_RGDAAC_M0PE_SHIFT                    (5U)
#define MPU_RGDAAC_M0PE(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M0PE_SHIFT)) & MPU_RGDAAC_M0PE_MASK)
#define MPU_RGDAAC_M1UM_MASK                     (0x1C0U)
#define MPU_RGDAAC_M1UM_SHIFT                    (6U)
#define MPU_RGDAAC_M1UM(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M1UM_SHIFT)) & MPU_RGDAAC_M1UM_MASK)
#define MPU_RGDAAC_M1SM_MASK                     (0x600U)
#define MPU_RGDAAC_M1SM_SHIFT                    (9U)
#define MPU_RGDAAC_M1SM(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M1SM_SHIFT)) & MPU_RGDAAC_M1SM_MASK)
#define MPU_RGDAAC_M1PE_MASK                     (0x800U)
#define MPU_RGDAAC_M1PE_SHIFT                    (11U)
#define MPU_RGDAAC_M1PE(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M1PE_SHIFT)) & MPU_RGDAAC_M1PE_MASK)
#define MPU_RGDAAC_M2UM_MASK                     (0x7000U)
#define MPU_RGDAAC_M2UM_SHIFT                    (12U)
#define MPU_RGDAAC_M2UM(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M2UM_SHIFT)) & MPU_RGDAAC_M2UM_MASK)
#define MPU_RGDAAC_M2SM_MASK                     (0x18000U)
#define MPU_RGDAAC_M2SM_SHIFT                    (15U)
#define MPU_RGDAAC_M2SM(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M2SM_SHIFT)) & MPU_RGDAAC_M2SM_MASK)
#define MPU_RGDAAC_M2PE_MASK                     (0x20000U)
#define MPU_RGDAAC_M2PE_SHIFT                    (17U)
#define MPU_RGDAAC_M2PE(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M2PE_SHIFT)) & MPU_RGDAAC_M2PE_MASK)
#define MPU_RGDAAC_M3UM_MASK                     (0x1C0000U)
#define MPU_RGDAAC_M3UM_SHIFT                    (18U)
#define MPU_RGDAAC_M3UM(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M3UM_SHIFT)) & MPU_RGDAAC_M3UM_MASK)
#define MPU_RGDAAC_M3SM_MASK                     (0x600000U)
#define MPU_RGDAAC_M3SM_SHIFT                    (21U)
#define MPU_RGDAAC_M3SM(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M3SM_SHIFT)) & MPU_RGDAAC_M3SM_MASK)
#define MPU_RGDAAC_M3PE_MASK                     (0x800000U)
#define MPU_RGDAAC_M3PE_SHIFT                    (23U)
#define MPU_RGDAAC_M3PE(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M3PE_SHIFT)) & MPU_RGDAAC_M3PE_MASK)
#define MPU_RGDAAC_M4WE_MASK                     (0x1000000U)
#define MPU_RGDAAC_M4WE_SHIFT                    (24U)
#define MPU_RGDAAC_M4WE(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M4WE_SHIFT)) & MPU_RGDAAC_M4WE_MASK)
#define MPU_RGDAAC_M4RE_MASK                     (0x2000000U)
#define MPU_RGDAAC_M4RE_SHIFT                    (25U)
#define MPU_RGDAAC_M4RE(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M4RE_SHIFT)) & MPU_RGDAAC_M4RE_MASK)
#define MPU_RGDAAC_M5WE_MASK                     (0x4000000U)
#define MPU_RGDAAC_M5WE_SHIFT                    (26U)
#define MPU_RGDAAC_M5WE(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M5WE_SHIFT)) & MPU_RGDAAC_M5WE_MASK)
#define MPU_RGDAAC_M5RE_MASK                     (0x8000000U)
#define MPU_RGDAAC_M5RE_SHIFT                    (27U)
#define MPU_RGDAAC_M5RE(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M5RE_SHIFT)) & MPU_RGDAAC_M5RE_MASK)
#define MPU_RGDAAC_M6WE_MASK                     (0x10000000U)
#define MPU_RGDAAC_M6WE_SHIFT                    (28U)
#define MPU_RGDAAC_M6WE(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M6WE_SHIFT)) & MPU_RGDAAC_M6WE_MASK)
#define MPU_RGDAAC_M6RE_MASK                     (0x20000000U)
#define MPU_RGDAAC_M6RE_SHIFT                    (29U)
#define MPU_RGDAAC_M6RE(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M6RE_SHIFT)) & MPU_RGDAAC_M6RE_MASK)
#define MPU_RGDAAC_M7WE_MASK                     (0x40000000U)
#define MPU_RGDAAC_M7WE_SHIFT                    (30U)
#define MPU_RGDAAC_M7WE(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M7WE_SHIFT)) & MPU_RGDAAC_M7WE_MASK)
#define MPU_RGDAAC_M7RE_MASK                     (0x80000000U)
#define MPU_RGDAAC_M7RE_SHIFT                    (31U)
#define MPU_RGDAAC_M7RE(x)                       (((uint32_t)(((uint32_t)(x)) << MPU_RGDAAC_M7RE_SHIFT)) & MPU_RGDAAC_M7RE_MASK)

/* The count of MPU_RGDAAC */
#define MPU_RGDAAC_COUNT                         (12U)


/*!
 * @}
 */ /* end of group MPU_Register_Masks */


/* MPU - Peripheral instance base addresses */
/** Peripheral MPU base address */
#define MPU_BASE                                 (0x4000D000u)
/** Peripheral MPU base pointer */
#define MPU                                      ((MPU_Type *)MPU_BASE)
/** Array initializer of MPU peripheral base addresses */
#define MPU_BASE_ADDRS                           { MPU_BASE }
/** Array initializer of MPU peripheral base pointers */
#define MPU_BASE_PTRS                            { MPU }

/*!
 * @}
 */ /* end of group MPU_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- MSCM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MSCM_Peripheral_Access_Layer MSCM Peripheral Access Layer
 * @{
 */

/** MSCM - Register Layout Typedef */
typedef struct {
  __I  uint32_t CPxTYPE;                           /**< Processor X Type Register, offset: 0x0 */
  __I  uint32_t CPxNUM;                            /**< Processor X Number Register, offset: 0x4 */
  __I  uint32_t CPxMASTER;                         /**< Processor X Master Register, offset: 0x8 */
  __I  uint32_t CPxCOUNT;                          /**< Processor X Count Register, offset: 0xC */
       uint8_t RESERVED_0[4];
  __I  uint32_t CPxCFG1;                           /**< Processor X Configuration 1 Register, offset: 0x14 */
       uint8_t RESERVED_1[4];
  __I  uint32_t CPxCFG3;                           /**< Processor X Configuration 3 Register, offset: 0x1C */
  struct {                                         /* offset: 0x20, array step: 0x20 */
    __I  uint32_t TYPE;                              /**< Processor 0 Type Register..Processor 1 Type Register, array offset: 0x20, array step: 0x20 */
    __I  uint32_t NUM;                               /**< Processor 0 Number Register..Processor 1 Number Register, array offset: 0x24, array step: 0x20 */
    __I  uint32_t MASTER;                            /**< Processor 0 Master Register..Processor 1 Master Register, array offset: 0x28, array step: 0x20 */
    __I  uint32_t COUNT;                             /**< Processor 0 Count Register..Processor 1 Count Register, array offset: 0x2C, array step: 0x20 */
         uint8_t RESERVED_0[4];
    __I  uint32_t CFG1;                              /**< Processor 0 Configuration 1 Register..Processor 1 Configuration 1 Register, array offset: 0x34, array step: 0x20 */
         uint8_t RESERVED_1[4];
    __I  uint32_t CFG3;                              /**< Processor 0 Configuration 3 Register..Processor 1 Configuration 3 Register, array offset: 0x3C, array step: 0x20 */
  } CP[2];
       uint8_t RESERVED_2[928];
  __I  uint32_t OCMDR[3];                          /**< On-Chip Memory Descriptor Register, array offset: 0x400, array step: 0x4 */
} MSCM_Type;

/* ----------------------------------------------------------------------------
   -- MSCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MSCM_Register_Masks MSCM Register Masks
 * @{
 */

/*! @name CPxTYPE - Processor X Type Register */
#define MSCM_CPxTYPE_RYPZ_MASK                   (0xFFU)
#define MSCM_CPxTYPE_RYPZ_SHIFT                  (0U)
#define MSCM_CPxTYPE_RYPZ(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CPxTYPE_RYPZ_SHIFT)) & MSCM_CPxTYPE_RYPZ_MASK)
#define MSCM_CPxTYPE_PERSONALITY_MASK            (0xFFFFFF00U)
#define MSCM_CPxTYPE_PERSONALITY_SHIFT           (8U)
#define MSCM_CPxTYPE_PERSONALITY(x)              (((uint32_t)(((uint32_t)(x)) << MSCM_CPxTYPE_PERSONALITY_SHIFT)) & MSCM_CPxTYPE_PERSONALITY_MASK)

/*! @name CPxNUM - Processor X Number Register */
#define MSCM_CPxNUM_CPN_MASK                     (0x1U)
#define MSCM_CPxNUM_CPN_SHIFT                    (0U)
#define MSCM_CPxNUM_CPN(x)                       (((uint32_t)(((uint32_t)(x)) << MSCM_CPxNUM_CPN_SHIFT)) & MSCM_CPxNUM_CPN_MASK)

/*! @name CPxMASTER - Processor X Master Register */
#define MSCM_CPxMASTER_PPN_MASK                  (0x3FU)
#define MSCM_CPxMASTER_PPN_SHIFT                 (0U)
#define MSCM_CPxMASTER_PPN(x)                    (((uint32_t)(((uint32_t)(x)) << MSCM_CPxMASTER_PPN_SHIFT)) & MSCM_CPxMASTER_PPN_MASK)

/*! @name CPxCOUNT - Processor X Count Register */
#define MSCM_CPxCOUNT_PCNT_MASK                  (0x3U)
#define MSCM_CPxCOUNT_PCNT_SHIFT                 (0U)
#define MSCM_CPxCOUNT_PCNT(x)                    (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCOUNT_PCNT_SHIFT)) & MSCM_CPxCOUNT_PCNT_MASK)

/*! @name CPxCFG1 - Processor X Configuration 1 Register */
#define MSCM_CPxCFG1_L2WY_MASK                   (0xFF0000U)
#define MSCM_CPxCFG1_L2WY_SHIFT                  (16U)
#define MSCM_CPxCFG1_L2WY(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG1_L2WY_SHIFT)) & MSCM_CPxCFG1_L2WY_MASK)
#define MSCM_CPxCFG1_L2SZ_MASK                   (0xFF000000U)
#define MSCM_CPxCFG1_L2SZ_SHIFT                  (24U)
#define MSCM_CPxCFG1_L2SZ(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG1_L2SZ_SHIFT)) & MSCM_CPxCFG1_L2SZ_MASK)

/*! @name CPxCFG3 - Processor X Configuration 3 Register */
#define MSCM_CPxCFG3_FPU_MASK                    (0x1U)
#define MSCM_CPxCFG3_FPU_SHIFT                   (0U)
#define MSCM_CPxCFG3_FPU(x)                      (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG3_FPU_SHIFT)) & MSCM_CPxCFG3_FPU_MASK)
#define MSCM_CPxCFG3_SIMD_MASK                   (0x2U)
#define MSCM_CPxCFG3_SIMD_SHIFT                  (1U)
#define MSCM_CPxCFG3_SIMD(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG3_SIMD_SHIFT)) & MSCM_CPxCFG3_SIMD_MASK)
#define MSCM_CPxCFG3_JAZ_MASK                    (0x4U)
#define MSCM_CPxCFG3_JAZ_SHIFT                   (2U)
#define MSCM_CPxCFG3_JAZ(x)                      (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG3_JAZ_SHIFT)) & MSCM_CPxCFG3_JAZ_MASK)
#define MSCM_CPxCFG3_MMU_MASK                    (0x8U)
#define MSCM_CPxCFG3_MMU_SHIFT                   (3U)
#define MSCM_CPxCFG3_MMU(x)                      (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG3_MMU_SHIFT)) & MSCM_CPxCFG3_MMU_MASK)
#define MSCM_CPxCFG3_TZ_MASK                     (0x10U)
#define MSCM_CPxCFG3_TZ_SHIFT                    (4U)
#define MSCM_CPxCFG3_TZ(x)                       (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG3_TZ_SHIFT)) & MSCM_CPxCFG3_TZ_MASK)
#define MSCM_CPxCFG3_CMP_MASK                    (0x20U)
#define MSCM_CPxCFG3_CMP_SHIFT                   (5U)
#define MSCM_CPxCFG3_CMP(x)                      (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG3_CMP_SHIFT)) & MSCM_CPxCFG3_CMP_MASK)
#define MSCM_CPxCFG3_BB_MASK                     (0x40U)
#define MSCM_CPxCFG3_BB_SHIFT                    (6U)
#define MSCM_CPxCFG3_BB(x)                       (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG3_BB_SHIFT)) & MSCM_CPxCFG3_BB_MASK)
#define MSCM_CPxCFG3_SBP_MASK                    (0x300U)
#define MSCM_CPxCFG3_SBP_SHIFT                   (8U)
#define MSCM_CPxCFG3_SBP(x)                      (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG3_SBP_SHIFT)) & MSCM_CPxCFG3_SBP_MASK)

/*! @name TYPE - Processor 0 Type Register..Processor 1 Type Register */
#define MSCM_TYPE_RYPZ_MASK                      (0xFFU)
#define MSCM_TYPE_RYPZ_SHIFT                     (0U)
#define MSCM_TYPE_RYPZ(x)                        (((uint32_t)(((uint32_t)(x)) << MSCM_TYPE_RYPZ_SHIFT)) & MSCM_TYPE_RYPZ_MASK)
#define MSCM_TYPE_PERSONALITY_MASK               (0xFFFFFF00U)
#define MSCM_TYPE_PERSONALITY_SHIFT              (8U)
#define MSCM_TYPE_PERSONALITY(x)                 (((uint32_t)(((uint32_t)(x)) << MSCM_TYPE_PERSONALITY_SHIFT)) & MSCM_TYPE_PERSONALITY_MASK)

/* The count of MSCM_TYPE */
#define MSCM_TYPE_COUNT                          (2U)

/*! @name NUM - Processor 0 Number Register..Processor 1 Number Register */
#define MSCM_NUM_CPN_MASK                        (0x1U)
#define MSCM_NUM_CPN_SHIFT                       (0U)
#define MSCM_NUM_CPN(x)                          (((uint32_t)(((uint32_t)(x)) << MSCM_NUM_CPN_SHIFT)) & MSCM_NUM_CPN_MASK)

/* The count of MSCM_NUM */
#define MSCM_NUM_COUNT                           (2U)

/*! @name MASTER - Processor 0 Master Register..Processor 1 Master Register */
#define MSCM_MASTER_PPN_MASK                     (0x3FU)
#define MSCM_MASTER_PPN_SHIFT                    (0U)
#define MSCM_MASTER_PPN(x)                       (((uint32_t)(((uint32_t)(x)) << MSCM_MASTER_PPN_SHIFT)) & MSCM_MASTER_PPN_MASK)

/* The count of MSCM_MASTER */
#define MSCM_MASTER_COUNT                        (2U)

/*! @name COUNT - Processor 0 Count Register..Processor 1 Count Register */
#define MSCM_COUNT_PCNT_MASK                     (0x3U)
#define MSCM_COUNT_PCNT_SHIFT                    (0U)
#define MSCM_COUNT_PCNT(x)                       (((uint32_t)(((uint32_t)(x)) << MSCM_COUNT_PCNT_SHIFT)) & MSCM_COUNT_PCNT_MASK)

/* The count of MSCM_COUNT */
#define MSCM_COUNT_COUNT                         (2U)

/*! @name CFG1 - Processor 0 Configuration 1 Register..Processor 1 Configuration 1 Register */
#define MSCM_CFG1_L2WY_MASK                      (0xFF0000U)
#define MSCM_CFG1_L2WY_SHIFT                     (16U)
#define MSCM_CFG1_L2WY(x)                        (((uint32_t)(((uint32_t)(x)) << MSCM_CFG1_L2WY_SHIFT)) & MSCM_CFG1_L2WY_MASK)
#define MSCM_CFG1_L2SZ_MASK                      (0xFF000000U)
#define MSCM_CFG1_L2SZ_SHIFT                     (24U)
#define MSCM_CFG1_L2SZ(x)                        (((uint32_t)(((uint32_t)(x)) << MSCM_CFG1_L2SZ_SHIFT)) & MSCM_CFG1_L2SZ_MASK)

/* The count of MSCM_CFG1 */
#define MSCM_CFG1_COUNT                          (2U)

/*! @name CFG3 - Processor 0 Configuration 3 Register..Processor 1 Configuration 3 Register */
#define MSCM_CFG3_FPU_MASK                       (0x1U)
#define MSCM_CFG3_FPU_SHIFT                      (0U)
#define MSCM_CFG3_FPU(x)                         (((uint32_t)(((uint32_t)(x)) << MSCM_CFG3_FPU_SHIFT)) & MSCM_CFG3_FPU_MASK)
#define MSCM_CFG3_SIMD_MASK                      (0x2U)
#define MSCM_CFG3_SIMD_SHIFT                     (1U)
#define MSCM_CFG3_SIMD(x)                        (((uint32_t)(((uint32_t)(x)) << MSCM_CFG3_SIMD_SHIFT)) & MSCM_CFG3_SIMD_MASK)
#define MSCM_CFG3_JAZ_MASK                       (0x4U)
#define MSCM_CFG3_JAZ_SHIFT                      (2U)
#define MSCM_CFG3_JAZ(x)                         (((uint32_t)(((uint32_t)(x)) << MSCM_CFG3_JAZ_SHIFT)) & MSCM_CFG3_JAZ_MASK)
#define MSCM_CFG3_MMU_MASK                       (0x8U)
#define MSCM_CFG3_MMU_SHIFT                      (3U)
#define MSCM_CFG3_MMU(x)                         (((uint32_t)(((uint32_t)(x)) << MSCM_CFG3_MMU_SHIFT)) & MSCM_CFG3_MMU_MASK)
#define MSCM_CFG3_TZ_MASK                        (0x10U)
#define MSCM_CFG3_TZ_SHIFT                       (4U)
#define MSCM_CFG3_TZ(x)                          (((uint32_t)(((uint32_t)(x)) << MSCM_CFG3_TZ_SHIFT)) & MSCM_CFG3_TZ_MASK)
#define MSCM_CFG3_CMP_MASK                       (0x20U)
#define MSCM_CFG3_CMP_SHIFT                      (5U)
#define MSCM_CFG3_CMP(x)                         (((uint32_t)(((uint32_t)(x)) << MSCM_CFG3_CMP_SHIFT)) & MSCM_CFG3_CMP_MASK)
#define MSCM_CFG3_BB_MASK                        (0x40U)
#define MSCM_CFG3_BB_SHIFT                       (6U)
#define MSCM_CFG3_BB(x)                          (((uint32_t)(((uint32_t)(x)) << MSCM_CFG3_BB_SHIFT)) & MSCM_CFG3_BB_MASK)
#define MSCM_CFG3_SBP_MASK                       (0x300U)
#define MSCM_CFG3_SBP_SHIFT                      (8U)
#define MSCM_CFG3_SBP(x)                         (((uint32_t)(((uint32_t)(x)) << MSCM_CFG3_SBP_SHIFT)) & MSCM_CFG3_SBP_MASK)

/* The count of MSCM_CFG3 */
#define MSCM_CFG3_COUNT                          (2U)

/*! @name OCMDR - On-Chip Memory Descriptor Register */
#define MSCM_OCMDR_OCMPU_MASK                    (0x1000U)
#define MSCM_OCMDR_OCMPU_SHIFT                   (12U)
#define MSCM_OCMDR_OCMPU(x)                      (((uint32_t)(((uint32_t)(x)) << MSCM_OCMDR_OCMPU_SHIFT)) & MSCM_OCMDR_OCMPU_MASK)
#define MSCM_OCMDR_OCMT_MASK                     (0xE000U)
#define MSCM_OCMDR_OCMT_SHIFT                    (13U)
#define MSCM_OCMDR_OCMT(x)                       (((uint32_t)(((uint32_t)(x)) << MSCM_OCMDR_OCMT_SHIFT)) & MSCM_OCMDR_OCMT_MASK)
#define MSCM_OCMDR_OCMW_MASK                     (0xE0000U)
#define MSCM_OCMDR_OCMW_SHIFT                    (17U)
#define MSCM_OCMDR_OCMW(x)                       (((uint32_t)(((uint32_t)(x)) << MSCM_OCMDR_OCMW_SHIFT)) & MSCM_OCMDR_OCMW_MASK)
#define MSCM_OCMDR_OCMSZ_MASK                    (0xF000000U)
#define MSCM_OCMDR_OCMSZ_SHIFT                   (24U)
#define MSCM_OCMDR_OCMSZ(x)                      (((uint32_t)(((uint32_t)(x)) << MSCM_OCMDR_OCMSZ_SHIFT)) & MSCM_OCMDR_OCMSZ_MASK)
#define MSCM_OCMDR_OCMSZH_MASK                   (0x10000000U)
#define MSCM_OCMDR_OCMSZH_SHIFT                  (28U)
#define MSCM_OCMDR_OCMSZH(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_OCMDR_OCMSZH_SHIFT)) & MSCM_OCMDR_OCMSZH_MASK)
#define MSCM_OCMDR_FMT_MASK                      (0x40000000U)
#define MSCM_OCMDR_FMT_SHIFT                     (30U)
#define MSCM_OCMDR_FMT(x)                        (((uint32_t)(((uint32_t)(x)) << MSCM_OCMDR_FMT_SHIFT)) & MSCM_OCMDR_FMT_MASK)
#define MSCM_OCMDR_V_MASK                        (0x80000000U)
#define MSCM_OCMDR_V_SHIFT                       (31U)
#define MSCM_OCMDR_V(x)                          (((uint32_t)(((uint32_t)(x)) << MSCM_OCMDR_V_SHIFT)) & MSCM_OCMDR_V_MASK)

/* The count of MSCM_OCMDR */
#define MSCM_OCMDR_COUNT                         (3U)


/*!
 * @}
 */ /* end of group MSCM_Register_Masks */


/* MSCM - Peripheral instance base addresses */
/** Peripheral MSCM base address */
#define MSCM_BASE                                (0x40001000u)
/** Peripheral MSCM base pointer */
#define MSCM                                     ((MSCM_Type *)MSCM_BASE)
/** Array initializer of MSCM peripheral base addresses */
#define MSCM_BASE_ADDRS                          { MSCM_BASE }
/** Array initializer of MSCM peripheral base pointers */
#define MSCM_BASE_PTRS                           { MSCM }

/*!
 * @}
 */ /* end of group MSCM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- NV Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Peripheral_Access_Layer NV Peripheral Access Layer
 * @{
 */

/** NV - Register Layout Typedef */
typedef struct {
  __I  uint8_t BACKKEY3;                           /**< Backdoor Comparison Key 3., offset: 0x0 */
  __I  uint8_t BACKKEY2;                           /**< Backdoor Comparison Key 2., offset: 0x1 */
  __I  uint8_t BACKKEY1;                           /**< Backdoor Comparison Key 1., offset: 0x2 */
  __I  uint8_t BACKKEY0;                           /**< Backdoor Comparison Key 0., offset: 0x3 */
  __I  uint8_t BACKKEY7;                           /**< Backdoor Comparison Key 7., offset: 0x4 */
  __I  uint8_t BACKKEY6;                           /**< Backdoor Comparison Key 6., offset: 0x5 */
  __I  uint8_t BACKKEY5;                           /**< Backdoor Comparison Key 5., offset: 0x6 */
  __I  uint8_t BACKKEY4;                           /**< Backdoor Comparison Key 4., offset: 0x7 */
  __I  uint8_t FPROT3;                             /**< Non-volatile P-Flash Protection 1 - Low Register, offset: 0x8 */
  __I  uint8_t FPROT2;                             /**< Non-volatile P-Flash Protection 1 - High Register, offset: 0x9 */
  __I  uint8_t FPROT1;                             /**< Non-volatile P-Flash Protection 0 - Low Register, offset: 0xA */
  __I  uint8_t FPROT0;                             /**< Non-volatile P-Flash Protection 0 - High Register, offset: 0xB */
  __I  uint8_t FSEC;                               /**< Non-volatile Flash Security Register, offset: 0xC */
  __I  uint8_t FOPT;                               /**< Non-volatile Flash Option Register, offset: 0xD */
} NV_Type;

/* ----------------------------------------------------------------------------
   -- NV Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Masks NV Register Masks
 * @{
 */

/*! @name BACKKEY3 - Backdoor Comparison Key 3. */
#define NV_BACKKEY3_KEY_MASK                     (0xFFU)
#define NV_BACKKEY3_KEY_SHIFT                    (0U)
#define NV_BACKKEY3_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY3_KEY_SHIFT)) & NV_BACKKEY3_KEY_MASK)

/*! @name BACKKEY2 - Backdoor Comparison Key 2. */
#define NV_BACKKEY2_KEY_MASK                     (0xFFU)
#define NV_BACKKEY2_KEY_SHIFT                    (0U)
#define NV_BACKKEY2_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY2_KEY_SHIFT)) & NV_BACKKEY2_KEY_MASK)

/*! @name BACKKEY1 - Backdoor Comparison Key 1. */
#define NV_BACKKEY1_KEY_MASK                     (0xFFU)
#define NV_BACKKEY1_KEY_SHIFT                    (0U)
#define NV_BACKKEY1_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY1_KEY_SHIFT)) & NV_BACKKEY1_KEY_MASK)

/*! @name BACKKEY0 - Backdoor Comparison Key 0. */
#define NV_BACKKEY0_KEY_MASK                     (0xFFU)
#define NV_BACKKEY0_KEY_SHIFT                    (0U)
#define NV_BACKKEY0_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY0_KEY_SHIFT)) & NV_BACKKEY0_KEY_MASK)

/*! @name BACKKEY7 - Backdoor Comparison Key 7. */
#define NV_BACKKEY7_KEY_MASK                     (0xFFU)
#define NV_BACKKEY7_KEY_SHIFT                    (0U)
#define NV_BACKKEY7_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY7_KEY_SHIFT)) & NV_BACKKEY7_KEY_MASK)

/*! @name BACKKEY6 - Backdoor Comparison Key 6. */
#define NV_BACKKEY6_KEY_MASK                     (0xFFU)
#define NV_BACKKEY6_KEY_SHIFT                    (0U)
#define NV_BACKKEY6_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY6_KEY_SHIFT)) & NV_BACKKEY6_KEY_MASK)

/*! @name BACKKEY5 - Backdoor Comparison Key 5. */
#define NV_BACKKEY5_KEY_MASK                     (0xFFU)
#define NV_BACKKEY5_KEY_SHIFT                    (0U)
#define NV_BACKKEY5_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY5_KEY_SHIFT)) & NV_BACKKEY5_KEY_MASK)

/*! @name BACKKEY4 - Backdoor Comparison Key 4. */
#define NV_BACKKEY4_KEY_MASK                     (0xFFU)
#define NV_BACKKEY4_KEY_SHIFT                    (0U)
#define NV_BACKKEY4_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY4_KEY_SHIFT)) & NV_BACKKEY4_KEY_MASK)

/*! @name FPROT3 - Non-volatile P-Flash Protection 1 - Low Register */
#define NV_FPROT3_PROT_MASK                      (0xFFU)
#define NV_FPROT3_PROT_SHIFT                     (0U)
#define NV_FPROT3_PROT(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FPROT3_PROT_SHIFT)) & NV_FPROT3_PROT_MASK)

/*! @name FPROT2 - Non-volatile P-Flash Protection 1 - High Register */
#define NV_FPROT2_PROT_MASK                      (0xFFU)
#define NV_FPROT2_PROT_SHIFT                     (0U)
#define NV_FPROT2_PROT(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FPROT2_PROT_SHIFT)) & NV_FPROT2_PROT_MASK)

/*! @name FPROT1 - Non-volatile P-Flash Protection 0 - Low Register */
#define NV_FPROT1_PROT_MASK                      (0xFFU)
#define NV_FPROT1_PROT_SHIFT                     (0U)
#define NV_FPROT1_PROT(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FPROT1_PROT_SHIFT)) & NV_FPROT1_PROT_MASK)

/*! @name FPROT0 - Non-volatile P-Flash Protection 0 - High Register */
#define NV_FPROT0_PROT_MASK                      (0xFFU)
#define NV_FPROT0_PROT_SHIFT                     (0U)
#define NV_FPROT0_PROT(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FPROT0_PROT_SHIFT)) & NV_FPROT0_PROT_MASK)

/*! @name FSEC - Non-volatile Flash Security Register */
#define NV_FSEC_SEC_MASK                         (0x3U)
#define NV_FSEC_SEC_SHIFT                        (0U)
#define NV_FSEC_SEC(x)                           (((uint8_t)(((uint8_t)(x)) << NV_FSEC_SEC_SHIFT)) & NV_FSEC_SEC_MASK)
#define NV_FSEC_FSLACC_MASK                      (0xCU)
#define NV_FSEC_FSLACC_SHIFT                     (2U)
#define NV_FSEC_FSLACC(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FSEC_FSLACC_SHIFT)) & NV_FSEC_FSLACC_MASK)
#define NV_FSEC_MEEN_MASK                        (0x30U)
#define NV_FSEC_MEEN_SHIFT                       (4U)
#define NV_FSEC_MEEN(x)                          (((uint8_t)(((uint8_t)(x)) << NV_FSEC_MEEN_SHIFT)) & NV_FSEC_MEEN_MASK)
#define NV_FSEC_KEYEN_MASK                       (0xC0U)
#define NV_FSEC_KEYEN_SHIFT                      (6U)
#define NV_FSEC_KEYEN(x)                         (((uint8_t)(((uint8_t)(x)) << NV_FSEC_KEYEN_SHIFT)) & NV_FSEC_KEYEN_MASK)

/*! @name FOPT - Non-volatile Flash Option Register */
#define NV_FOPT_LPBOOT_MASK                      (0x1U)
#define NV_FOPT_LPBOOT_SHIFT                     (0U)
#define NV_FOPT_LPBOOT(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FOPT_LPBOOT_SHIFT)) & NV_FOPT_LPBOOT_MASK)
#define NV_FOPT_NMI_DIS_MASK                     (0x4U)
#define NV_FOPT_NMI_DIS_SHIFT                    (2U)
#define NV_FOPT_NMI_DIS(x)                       (((uint8_t)(((uint8_t)(x)) << NV_FOPT_NMI_DIS_SHIFT)) & NV_FOPT_NMI_DIS_MASK)
#define NV_FOPT_FAST_INIT_MASK                   (0x20U)
#define NV_FOPT_FAST_INIT_SHIFT                  (5U)
#define NV_FOPT_FAST_INIT(x)                     (((uint8_t)(((uint8_t)(x)) << NV_FOPT_FAST_INIT_SHIFT)) & NV_FOPT_FAST_INIT_MASK)


/*!
 * @}
 */ /* end of group NV_Register_Masks */


/* NV - Peripheral instance base addresses */
/** Peripheral FTFL_FlashConfig base address */
#define FTFL_FlashConfig_BASE                    (0x400u)
/** Peripheral FTFL_FlashConfig base pointer */
#define FTFL_FlashConfig                         ((NV_Type *)FTFL_FlashConfig_BASE)
/** Array initializer of NV peripheral base addresses */
#define NV_BASE_ADDRS                            { FTFL_FlashConfig_BASE }
/** Array initializer of NV peripheral base pointers */
#define NV_BASE_PTRS                             { FTFL_FlashConfig }

/*!
 * @}
 */ /* end of group NV_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- OSC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Peripheral_Access_Layer OSC Peripheral Access Layer
 * @{
 */

/** OSC - Register Layout Typedef */
typedef struct {
  __IO uint8_t CR;                                 /**< OSC Control Register, offset: 0x0 */
       uint8_t RESERVED_0[1];
  __IO uint8_t DIV;                                /**< OSC_DIV, offset: 0x2 */
} OSC_Type;

/* ----------------------------------------------------------------------------
   -- OSC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Masks OSC Register Masks
 * @{
 */

/*! @name CR - OSC Control Register */
#define OSC_CR_SC16P_MASK                        (0x1U)
#define OSC_CR_SC16P_SHIFT                       (0U)
#define OSC_CR_SC16P(x)                          (((uint8_t)(((uint8_t)(x)) << OSC_CR_SC16P_SHIFT)) & OSC_CR_SC16P_MASK)
#define OSC_CR_SC8P_MASK                         (0x2U)
#define OSC_CR_SC8P_SHIFT                        (1U)
#define OSC_CR_SC8P(x)                           (((uint8_t)(((uint8_t)(x)) << OSC_CR_SC8P_SHIFT)) & OSC_CR_SC8P_MASK)
#define OSC_CR_SC4P_MASK                         (0x4U)
#define OSC_CR_SC4P_SHIFT                        (2U)
#define OSC_CR_SC4P(x)                           (((uint8_t)(((uint8_t)(x)) << OSC_CR_SC4P_SHIFT)) & OSC_CR_SC4P_MASK)
#define OSC_CR_SC2P_MASK                         (0x8U)
#define OSC_CR_SC2P_SHIFT                        (3U)
#define OSC_CR_SC2P(x)                           (((uint8_t)(((uint8_t)(x)) << OSC_CR_SC2P_SHIFT)) & OSC_CR_SC2P_MASK)
#define OSC_CR_EREFSTEN_MASK                     (0x20U)
#define OSC_CR_EREFSTEN_SHIFT                    (5U)
#define OSC_CR_EREFSTEN(x)                       (((uint8_t)(((uint8_t)(x)) << OSC_CR_EREFSTEN_SHIFT)) & OSC_CR_EREFSTEN_MASK)
#define OSC_CR_ERCLKEN_MASK                      (0x80U)
#define OSC_CR_ERCLKEN_SHIFT                     (7U)
#define OSC_CR_ERCLKEN(x)                        (((uint8_t)(((uint8_t)(x)) << OSC_CR_ERCLKEN_SHIFT)) & OSC_CR_ERCLKEN_MASK)

/*! @name DIV - OSC_DIV */
#define OSC_DIV_ERPS_MASK                        (0xC0U)
#define OSC_DIV_ERPS_SHIFT                       (6U)
#define OSC_DIV_ERPS(x)                          (((uint8_t)(((uint8_t)(x)) << OSC_DIV_ERPS_SHIFT)) & OSC_DIV_ERPS_MASK)


/*!
 * @}
 */ /* end of group OSC_Register_Masks */


/* OSC - Peripheral instance base addresses */
/** Peripheral OSC0 base address */
#define OSC0_BASE                                (0x40065000u)
/** Peripheral OSC0 base pointer */
#define OSC0                                     ((OSC_Type *)OSC0_BASE)
/** Array initializer of OSC peripheral base addresses */
#define OSC_BASE_ADDRS                           { OSC0_BASE }
/** Array initializer of OSC peripheral base pointers */
#define OSC_BASE_PTRS                            { OSC0 }

/*!
 * @}
 */ /* end of group OSC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- PDB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PDB_Peripheral_Access_Layer PDB Peripheral Access Layer
 * @{
 */

/** PDB - Register Layout Typedef */
typedef struct {
  __IO uint32_t SC;                                /**< Status and Control register, offset: 0x0 */
  __IO uint32_t MOD;                               /**< Modulus register, offset: 0x4 */
  __I  uint32_t CNT;                               /**< Counter register, offset: 0x8 */
  __IO uint32_t IDLY;                              /**< Interrupt Delay register, offset: 0xC */
  struct {                                         /* offset: 0x10, array step: 0x28 */
    __IO uint32_t C1;                                /**< Channel n Control register 1, array offset: 0x10, array step: 0x28 */
    __IO uint32_t S;                                 /**< Channel n Status register, array offset: 0x14, array step: 0x28 */
    __IO uint32_t DLY[2];                            /**< Channel n Delay 0 register..Channel n Delay 1 register, array offset: 0x18, array step: index*0x28, index2*0x4 */
         uint8_t RESERVED_0[24];
  } CH[2];
       uint8_t RESERVED_0[240];
  struct {                                         /* offset: 0x150, array step: 0x8 */
    __IO uint32_t INTC;                              /**< DAC Interval Trigger n Control register, array offset: 0x150, array step: 0x8 */
    __IO uint32_t INT;                               /**< DAC Interval n register, array offset: 0x154, array step: 0x8 */
  } DAC[1];
       uint8_t RESERVED_1[56];
  __IO uint32_t POEN;                              /**< Pulse-Out n Enable register, offset: 0x190 */
  __IO uint32_t PODLY[2];                          /**< Pulse-Out n Delay register, array offset: 0x194, array step: 0x4 */
} PDB_Type;

/* ----------------------------------------------------------------------------
   -- PDB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PDB_Register_Masks PDB Register Masks
 * @{
 */

/*! @name SC - Status and Control register */
#define PDB_SC_LDOK_MASK                         (0x1U)
#define PDB_SC_LDOK_SHIFT                        (0U)
#define PDB_SC_LDOK(x)                           (((uint32_t)(((uint32_t)(x)) << PDB_SC_LDOK_SHIFT)) & PDB_SC_LDOK_MASK)
#define PDB_SC_CONT_MASK                         (0x2U)
#define PDB_SC_CONT_SHIFT                        (1U)
#define PDB_SC_CONT(x)                           (((uint32_t)(((uint32_t)(x)) << PDB_SC_CONT_SHIFT)) & PDB_SC_CONT_MASK)
#define PDB_SC_MULT_MASK                         (0xCU)
#define PDB_SC_MULT_SHIFT                        (2U)
#define PDB_SC_MULT(x)                           (((uint32_t)(((uint32_t)(x)) << PDB_SC_MULT_SHIFT)) & PDB_SC_MULT_MASK)
#define PDB_SC_PDBIE_MASK                        (0x20U)
#define PDB_SC_PDBIE_SHIFT                       (5U)
#define PDB_SC_PDBIE(x)                          (((uint32_t)(((uint32_t)(x)) << PDB_SC_PDBIE_SHIFT)) & PDB_SC_PDBIE_MASK)
#define PDB_SC_PDBIF_MASK                        (0x40U)
#define PDB_SC_PDBIF_SHIFT                       (6U)
#define PDB_SC_PDBIF(x)                          (((uint32_t)(((uint32_t)(x)) << PDB_SC_PDBIF_SHIFT)) & PDB_SC_PDBIF_MASK)
#define PDB_SC_PDBEN_MASK                        (0x80U)
#define PDB_SC_PDBEN_SHIFT                       (7U)
#define PDB_SC_PDBEN(x)                          (((uint32_t)(((uint32_t)(x)) << PDB_SC_PDBEN_SHIFT)) & PDB_SC_PDBEN_MASK)
#define PDB_SC_TRGSEL_MASK                       (0xF00U)
#define PDB_SC_TRGSEL_SHIFT                      (8U)
#define PDB_SC_TRGSEL(x)                         (((uint32_t)(((uint32_t)(x)) << PDB_SC_TRGSEL_SHIFT)) & PDB_SC_TRGSEL_MASK)
#define PDB_SC_PRESCALER_MASK                    (0x7000U)
#define PDB_SC_PRESCALER_SHIFT                   (12U)
#define PDB_SC_PRESCALER(x)                      (((uint32_t)(((uint32_t)(x)) << PDB_SC_PRESCALER_SHIFT)) & PDB_SC_PRESCALER_MASK)
#define PDB_SC_DMAEN_MASK                        (0x8000U)
#define PDB_SC_DMAEN_SHIFT                       (15U)
#define PDB_SC_DMAEN(x)                          (((uint32_t)(((uint32_t)(x)) << PDB_SC_DMAEN_SHIFT)) & PDB_SC_DMAEN_MASK)
#define PDB_SC_SWTRIG_MASK                       (0x10000U)
#define PDB_SC_SWTRIG_SHIFT                      (16U)
#define PDB_SC_SWTRIG(x)                         (((uint32_t)(((uint32_t)(x)) << PDB_SC_SWTRIG_SHIFT)) & PDB_SC_SWTRIG_MASK)
#define PDB_SC_PDBEIE_MASK                       (0x20000U)
#define PDB_SC_PDBEIE_SHIFT                      (17U)
#define PDB_SC_PDBEIE(x)                         (((uint32_t)(((uint32_t)(x)) << PDB_SC_PDBEIE_SHIFT)) & PDB_SC_PDBEIE_MASK)
#define PDB_SC_LDMOD_MASK                        (0xC0000U)
#define PDB_SC_LDMOD_SHIFT                       (18U)
#define PDB_SC_LDMOD(x)                          (((uint32_t)(((uint32_t)(x)) << PDB_SC_LDMOD_SHIFT)) & PDB_SC_LDMOD_MASK)

/*! @name MOD - Modulus register */
#define PDB_MOD_MOD_MASK                         (0xFFFFU)
#define PDB_MOD_MOD_SHIFT                        (0U)
#define PDB_MOD_MOD(x)                           (((uint32_t)(((uint32_t)(x)) << PDB_MOD_MOD_SHIFT)) & PDB_MOD_MOD_MASK)

/*! @name CNT - Counter register */
#define PDB_CNT_CNT_MASK                         (0xFFFFU)
#define PDB_CNT_CNT_SHIFT                        (0U)
#define PDB_CNT_CNT(x)                           (((uint32_t)(((uint32_t)(x)) << PDB_CNT_CNT_SHIFT)) & PDB_CNT_CNT_MASK)

/*! @name IDLY - Interrupt Delay register */
#define PDB_IDLY_IDLY_MASK                       (0xFFFFU)
#define PDB_IDLY_IDLY_SHIFT                      (0U)
#define PDB_IDLY_IDLY(x)                         (((uint32_t)(((uint32_t)(x)) << PDB_IDLY_IDLY_SHIFT)) & PDB_IDLY_IDLY_MASK)

/*! @name C1 - Channel n Control register 1 */
#define PDB_C1_EN_MASK                           (0xFFU)
#define PDB_C1_EN_SHIFT                          (0U)
#define PDB_C1_EN(x)                             (((uint32_t)(((uint32_t)(x)) << PDB_C1_EN_SHIFT)) & PDB_C1_EN_MASK)
#define PDB_C1_TOS_MASK                          (0xFF00U)
#define PDB_C1_TOS_SHIFT                         (8U)
#define PDB_C1_TOS(x)                            (((uint32_t)(((uint32_t)(x)) << PDB_C1_TOS_SHIFT)) & PDB_C1_TOS_MASK)
#define PDB_C1_BB_MASK                           (0xFF0000U)
#define PDB_C1_BB_SHIFT                          (16U)
#define PDB_C1_BB(x)                             (((uint32_t)(((uint32_t)(x)) << PDB_C1_BB_SHIFT)) & PDB_C1_BB_MASK)

/* The count of PDB_C1 */
#define PDB_C1_COUNT                             (2U)

/*! @name S - Channel n Status register */
#define PDB_S_ERR_MASK                           (0xFFU)
#define PDB_S_ERR_SHIFT                          (0U)
#define PDB_S_ERR(x)                             (((uint32_t)(((uint32_t)(x)) << PDB_S_ERR_SHIFT)) & PDB_S_ERR_MASK)
#define PDB_S_CF_MASK                            (0xFF0000U)
#define PDB_S_CF_SHIFT                           (16U)
#define PDB_S_CF(x)                              (((uint32_t)(((uint32_t)(x)) << PDB_S_CF_SHIFT)) & PDB_S_CF_MASK)

/* The count of PDB_S */
#define PDB_S_COUNT                              (2U)

/*! @name DLY - Channel n Delay 0 register..Channel n Delay 1 register */
#define PDB_DLY_DLY_MASK                         (0xFFFFU)
#define PDB_DLY_DLY_SHIFT                        (0U)
#define PDB_DLY_DLY(x)                           (((uint32_t)(((uint32_t)(x)) << PDB_DLY_DLY_SHIFT)) & PDB_DLY_DLY_MASK)

/* The count of PDB_DLY */
#define PDB_DLY_COUNT                            (2U)

/* The count of PDB_DLY */
#define PDB_DLY_COUNT2                           (2U)

/*! @name INTC - DAC Interval Trigger n Control register */
#define PDB_INTC_TOE_MASK                        (0x1U)
#define PDB_INTC_TOE_SHIFT                       (0U)
#define PDB_INTC_TOE(x)                          (((uint32_t)(((uint32_t)(x)) << PDB_INTC_TOE_SHIFT)) & PDB_INTC_TOE_MASK)
#define PDB_INTC_EXT_MASK                        (0x2U)
#define PDB_INTC_EXT_SHIFT                       (1U)
#define PDB_INTC_EXT(x)                          (((uint32_t)(((uint32_t)(x)) << PDB_INTC_EXT_SHIFT)) & PDB_INTC_EXT_MASK)

/* The count of PDB_INTC */
#define PDB_INTC_COUNT                           (1U)

/*! @name INT - DAC Interval n register */
#define PDB_INT_INT_MASK                         (0xFFFFU)
#define PDB_INT_INT_SHIFT                        (0U)
#define PDB_INT_INT(x)                           (((uint32_t)(((uint32_t)(x)) << PDB_INT_INT_SHIFT)) & PDB_INT_INT_MASK)

/* The count of PDB_INT */
#define PDB_INT_COUNT                            (1U)

/*! @name POEN - Pulse-Out n Enable register */
#define PDB_POEN_POEN_MASK                       (0xFFU)
#define PDB_POEN_POEN_SHIFT                      (0U)
#define PDB_POEN_POEN(x)                         (((uint32_t)(((uint32_t)(x)) << PDB_POEN_POEN_SHIFT)) & PDB_POEN_POEN_MASK)

/*! @name PODLY - Pulse-Out n Delay register */
#define PDB_PODLY_DLY2_MASK                      (0xFFFFU)
#define PDB_PODLY_DLY2_SHIFT                     (0U)
#define PDB_PODLY_DLY2(x)                        (((uint32_t)(((uint32_t)(x)) << PDB_PODLY_DLY2_SHIFT)) & PDB_PODLY_DLY2_MASK)
#define PDB_PODLY_DLY1_MASK                      (0xFFFF0000U)
#define PDB_PODLY_DLY1_SHIFT                     (16U)
#define PDB_PODLY_DLY1(x)                        (((uint32_t)(((uint32_t)(x)) << PDB_PODLY_DLY1_SHIFT)) & PDB_PODLY_DLY1_MASK)

/* The count of PDB_PODLY */
#define PDB_PODLY_COUNT                          (2U)


/*!
 * @}
 */ /* end of group PDB_Register_Masks */


/* PDB - Peripheral instance base addresses */
/** Peripheral PDB0 base address */
#define PDB0_BASE                                (0x40036000u)
/** Peripheral PDB0 base pointer */
#define PDB0                                     ((PDB_Type *)PDB0_BASE)
/** Peripheral PDB1 base address */
#define PDB1_BASE                                (0x40031000u)
/** Peripheral PDB1 base pointer */
#define PDB1                                     ((PDB_Type *)PDB1_BASE)
/** Array initializer of PDB peripheral base addresses */
#define PDB_BASE_ADDRS                           { PDB0_BASE, PDB1_BASE }
/** Array initializer of PDB peripheral base pointers */
#define PDB_BASE_PTRS                            { PDB0, PDB1 }
/** Interrupt vectors for the PDB peripheral type */
#define PDB_IRQS                                 { PDB0_IRQn, PDB1_IRQn }

/*!
 * @}
 */ /* end of group PDB_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- PIT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Peripheral_Access_Layer PIT Peripheral Access Layer
 * @{
 */

/** PIT - Register Layout Typedef */
typedef struct {
  __IO uint32_t MCR;                               /**< PIT Module Control Register, offset: 0x0 */
       uint8_t RESERVED_0[220];
  __I  uint32_t LTMR64H;                           /**< PIT Upper Lifetime Timer Register, offset: 0xE0 */
  __I  uint32_t LTMR64L;                           /**< PIT Lower Lifetime Timer Register, offset: 0xE4 */
       uint8_t RESERVED_1[24];
  struct {                                         /* offset: 0x100, array step: 0x10 */
    __IO uint32_t LDVAL;                             /**< Timer Load Value Register, array offset: 0x100, array step: 0x10 */
    __I  uint32_t CVAL;                              /**< Current Timer Value Register, array offset: 0x104, array step: 0x10 */
    __IO uint32_t TCTRL;                             /**< Timer Control Register, array offset: 0x108, array step: 0x10 */
    __IO uint32_t TFLG;                              /**< Timer Flag Register, array offset: 0x10C, array step: 0x10 */
  } CHANNEL[4];
} PIT_Type;

/* ----------------------------------------------------------------------------
   -- PIT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Masks PIT Register Masks
 * @{
 */

/*! @name MCR - PIT Module Control Register */
#define PIT_MCR_FRZ_MASK                         (0x1U)
#define PIT_MCR_FRZ_SHIFT                        (0U)
#define PIT_MCR_FRZ(x)                           (((uint32_t)(((uint32_t)(x)) << PIT_MCR_FRZ_SHIFT)) & PIT_MCR_FRZ_MASK)
#define PIT_MCR_MDIS_MASK                        (0x2U)
#define PIT_MCR_MDIS_SHIFT                       (1U)
#define PIT_MCR_MDIS(x)                          (((uint32_t)(((uint32_t)(x)) << PIT_MCR_MDIS_SHIFT)) & PIT_MCR_MDIS_MASK)

/*! @name LTMR64H - PIT Upper Lifetime Timer Register */
#define PIT_LTMR64H_LTH_MASK                     (0xFFFFFFFFU)
#define PIT_LTMR64H_LTH_SHIFT                    (0U)
#define PIT_LTMR64H_LTH(x)                       (((uint32_t)(((uint32_t)(x)) << PIT_LTMR64H_LTH_SHIFT)) & PIT_LTMR64H_LTH_MASK)

/*! @name LTMR64L - PIT Lower Lifetime Timer Register */
#define PIT_LTMR64L_LTL_MASK                     (0xFFFFFFFFU)
#define PIT_LTMR64L_LTL_SHIFT                    (0U)
#define PIT_LTMR64L_LTL(x)                       (((uint32_t)(((uint32_t)(x)) << PIT_LTMR64L_LTL_SHIFT)) & PIT_LTMR64L_LTL_MASK)

/*! @name LDVAL - Timer Load Value Register */
#define PIT_LDVAL_TSV_MASK                       (0xFFFFFFFFU)
#define PIT_LDVAL_TSV_SHIFT                      (0U)
#define PIT_LDVAL_TSV(x)                         (((uint32_t)(((uint32_t)(x)) << PIT_LDVAL_TSV_SHIFT)) & PIT_LDVAL_TSV_MASK)

/* The count of PIT_LDVAL */
#define PIT_LDVAL_COUNT                          (4U)

/*! @name CVAL - Current Timer Value Register */
#define PIT_CVAL_TVL_MASK                        (0xFFFFFFFFU)
#define PIT_CVAL_TVL_SHIFT                       (0U)
#define PIT_CVAL_TVL(x)                          (((uint32_t)(((uint32_t)(x)) << PIT_CVAL_TVL_SHIFT)) & PIT_CVAL_TVL_MASK)

/* The count of PIT_CVAL */
#define PIT_CVAL_COUNT                           (4U)

/*! @name TCTRL - Timer Control Register */
#define PIT_TCTRL_TEN_MASK                       (0x1U)
#define PIT_TCTRL_TEN_SHIFT                      (0U)
#define PIT_TCTRL_TEN(x)                         (((uint32_t)(((uint32_t)(x)) << PIT_TCTRL_TEN_SHIFT)) & PIT_TCTRL_TEN_MASK)
#define PIT_TCTRL_TIE_MASK                       (0x2U)
#define PIT_TCTRL_TIE_SHIFT                      (1U)
#define PIT_TCTRL_TIE(x)                         (((uint32_t)(((uint32_t)(x)) << PIT_TCTRL_TIE_SHIFT)) & PIT_TCTRL_TIE_MASK)
#define PIT_TCTRL_CHN_MASK                       (0x4U)
#define PIT_TCTRL_CHN_SHIFT                      (2U)
#define PIT_TCTRL_CHN(x)                         (((uint32_t)(((uint32_t)(x)) << PIT_TCTRL_CHN_SHIFT)) & PIT_TCTRL_CHN_MASK)

/* The count of PIT_TCTRL */
#define PIT_TCTRL_COUNT                          (4U)

/*! @name TFLG - Timer Flag Register */
#define PIT_TFLG_TIF_MASK                        (0x1U)
#define PIT_TFLG_TIF_SHIFT                       (0U)
#define PIT_TFLG_TIF(x)                          (((uint32_t)(((uint32_t)(x)) << PIT_TFLG_TIF_SHIFT)) & PIT_TFLG_TIF_MASK)

/* The count of PIT_TFLG */
#define PIT_TFLG_COUNT                           (4U)


/*!
 * @}
 */ /* end of group PIT_Register_Masks */


/* PIT - Peripheral instance base addresses */
/** Peripheral PIT base address */
#define PIT_BASE                                 (0x40037000u)
/** Peripheral PIT base pointer */
#define PIT                                      ((PIT_Type *)PIT_BASE)
/** Array initializer of PIT peripheral base addresses */
#define PIT_BASE_ADDRS                           { PIT_BASE }
/** Array initializer of PIT peripheral base pointers */
#define PIT_BASE_PTRS                            { PIT }
/** Interrupt vectors for the PIT peripheral type */
#define PIT_IRQS                                 { PIT0_IRQn, PIT1_IRQn, PIT2_IRQn, PIT3_IRQn }

/*!
 * @}
 */ /* end of group PIT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- PMC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Peripheral_Access_Layer PMC Peripheral Access Layer
 * @{
 */

/** PMC - Register Layout Typedef */
typedef struct {
  __IO uint8_t LVDSC1;                             /**< Low Voltage Detect Status And Control 1 register, offset: 0x0 */
  __IO uint8_t LVDSC2;                             /**< Low Voltage Detect Status And Control 2 register, offset: 0x1 */
  __IO uint8_t REGSC;                              /**< Regulator Status And Control register, offset: 0x2 */
       uint8_t RESERVED_0[8];
  __IO uint8_t HVDSC1;                             /**< High Voltage Detect Status And Control 1 register, offset: 0xB */
} PMC_Type;

/* ----------------------------------------------------------------------------
   -- PMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Masks PMC Register Masks
 * @{
 */

/*! @name LVDSC1 - Low Voltage Detect Status And Control 1 register */
#define PMC_LVDSC1_LVDV_MASK                     (0x3U)
#define PMC_LVDSC1_LVDV_SHIFT                    (0U)
#define PMC_LVDSC1_LVDV(x)                       (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC1_LVDV_SHIFT)) & PMC_LVDSC1_LVDV_MASK)
#define PMC_LVDSC1_LVDRE_MASK                    (0x10U)
#define PMC_LVDSC1_LVDRE_SHIFT                   (4U)
#define PMC_LVDSC1_LVDRE(x)                      (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC1_LVDRE_SHIFT)) & PMC_LVDSC1_LVDRE_MASK)
#define PMC_LVDSC1_LVDIE_MASK                    (0x20U)
#define PMC_LVDSC1_LVDIE_SHIFT                   (5U)
#define PMC_LVDSC1_LVDIE(x)                      (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC1_LVDIE_SHIFT)) & PMC_LVDSC1_LVDIE_MASK)
#define PMC_LVDSC1_LVDACK_MASK                   (0x40U)
#define PMC_LVDSC1_LVDACK_SHIFT                  (6U)
#define PMC_LVDSC1_LVDACK(x)                     (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC1_LVDACK_SHIFT)) & PMC_LVDSC1_LVDACK_MASK)
#define PMC_LVDSC1_LVDF_MASK                     (0x80U)
#define PMC_LVDSC1_LVDF_SHIFT                    (7U)
#define PMC_LVDSC1_LVDF(x)                       (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC1_LVDF_SHIFT)) & PMC_LVDSC1_LVDF_MASK)

/*! @name LVDSC2 - Low Voltage Detect Status And Control 2 register */
#define PMC_LVDSC2_LVWV_MASK                     (0x3U)
#define PMC_LVDSC2_LVWV_SHIFT                    (0U)
#define PMC_LVDSC2_LVWV(x)                       (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC2_LVWV_SHIFT)) & PMC_LVDSC2_LVWV_MASK)
#define PMC_LVDSC2_LVWIE_MASK                    (0x20U)
#define PMC_LVDSC2_LVWIE_SHIFT                   (5U)
#define PMC_LVDSC2_LVWIE(x)                      (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC2_LVWIE_SHIFT)) & PMC_LVDSC2_LVWIE_MASK)
#define PMC_LVDSC2_LVWACK_MASK                   (0x40U)
#define PMC_LVDSC2_LVWACK_SHIFT                  (6U)
#define PMC_LVDSC2_LVWACK(x)                     (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC2_LVWACK_SHIFT)) & PMC_LVDSC2_LVWACK_MASK)
#define PMC_LVDSC2_LVWF_MASK                     (0x80U)
#define PMC_LVDSC2_LVWF_SHIFT                    (7U)
#define PMC_LVDSC2_LVWF(x)                       (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC2_LVWF_SHIFT)) & PMC_LVDSC2_LVWF_MASK)

/*! @name REGSC - Regulator Status And Control register */
#define PMC_REGSC_BGBE_MASK                      (0x1U)
#define PMC_REGSC_BGBE_SHIFT                     (0U)
#define PMC_REGSC_BGBE(x)                        (((uint8_t)(((uint8_t)(x)) << PMC_REGSC_BGBE_SHIFT)) & PMC_REGSC_BGBE_MASK)
#define PMC_REGSC_REGONS_MASK                    (0x4U)
#define PMC_REGSC_REGONS_SHIFT                   (2U)
#define PMC_REGSC_REGONS(x)                      (((uint8_t)(((uint8_t)(x)) << PMC_REGSC_REGONS_SHIFT)) & PMC_REGSC_REGONS_MASK)
#define PMC_REGSC_ACKISO_MASK                    (0x8U)
#define PMC_REGSC_ACKISO_SHIFT                   (3U)
#define PMC_REGSC_ACKISO(x)                      (((uint8_t)(((uint8_t)(x)) << PMC_REGSC_ACKISO_SHIFT)) & PMC_REGSC_ACKISO_MASK)
#define PMC_REGSC_BGEN_MASK                      (0x10U)
#define PMC_REGSC_BGEN_SHIFT                     (4U)
#define PMC_REGSC_BGEN(x)                        (((uint8_t)(((uint8_t)(x)) << PMC_REGSC_BGEN_SHIFT)) & PMC_REGSC_BGEN_MASK)

/*! @name HVDSC1 - High Voltage Detect Status And Control 1 register */
#define PMC_HVDSC1_HVDV_MASK                     (0x1U)
#define PMC_HVDSC1_HVDV_SHIFT                    (0U)
#define PMC_HVDSC1_HVDV(x)                       (((uint8_t)(((uint8_t)(x)) << PMC_HVDSC1_HVDV_SHIFT)) & PMC_HVDSC1_HVDV_MASK)
#define PMC_HVDSC1_HVDRE_MASK                    (0x10U)
#define PMC_HVDSC1_HVDRE_SHIFT                   (4U)
#define PMC_HVDSC1_HVDRE(x)                      (((uint8_t)(((uint8_t)(x)) << PMC_HVDSC1_HVDRE_SHIFT)) & PMC_HVDSC1_HVDRE_MASK)
#define PMC_HVDSC1_HVDIE_MASK                    (0x20U)
#define PMC_HVDSC1_HVDIE_SHIFT                   (5U)
#define PMC_HVDSC1_HVDIE(x)                      (((uint8_t)(((uint8_t)(x)) << PMC_HVDSC1_HVDIE_SHIFT)) & PMC_HVDSC1_HVDIE_MASK)
#define PMC_HVDSC1_HVDACK_MASK                   (0x40U)
#define PMC_HVDSC1_HVDACK_SHIFT                  (6U)
#define PMC_HVDSC1_HVDACK(x)                     (((uint8_t)(((uint8_t)(x)) << PMC_HVDSC1_HVDACK_SHIFT)) & PMC_HVDSC1_HVDACK_MASK)
#define PMC_HVDSC1_HVDF_MASK                     (0x80U)
#define PMC_HVDSC1_HVDF_SHIFT                    (7U)
#define PMC_HVDSC1_HVDF(x)                       (((uint8_t)(((uint8_t)(x)) << PMC_HVDSC1_HVDF_SHIFT)) & PMC_HVDSC1_HVDF_MASK)


/*!
 * @}
 */ /* end of group PMC_Register_Masks */


/* PMC - Peripheral instance base addresses */
/** Peripheral PMC base address */
#define PMC_BASE                                 (0x4007D000u)
/** Peripheral PMC base pointer */
#define PMC                                      ((PMC_Type *)PMC_BASE)
/** Array initializer of PMC peripheral base addresses */
#define PMC_BASE_ADDRS                           { PMC_BASE }
/** Array initializer of PMC peripheral base pointers */
#define PMC_BASE_PTRS                            { PMC }
/** Interrupt vectors for the PMC peripheral type */
#define PMC_IRQS                                 { PMC_IRQn }

/*!
 * @}
 */ /* end of group PMC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- PORT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Peripheral_Access_Layer PORT Peripheral Access Layer
 * @{
 */

/** PORT - Register Layout Typedef */
typedef struct {
  __IO uint32_t PCR[32];                           /**< Pin Control Register n, array offset: 0x0, array step: 0x4 */
  __O  uint32_t GPCLR;                             /**< Global Pin Control Low Register, offset: 0x80 */
  __O  uint32_t GPCHR;                             /**< Global Pin Control High Register, offset: 0x84 */
       uint8_t RESERVED_0[24];
  __IO uint32_t ISFR;                              /**< Interrupt Status Flag Register, offset: 0xA0 */
       uint8_t RESERVED_1[28];
  __IO uint32_t DFER;                              /**< Digital Filter Enable Register, offset: 0xC0 */
  __IO uint32_t DFCR;                              /**< Digital Filter Clock Register, offset: 0xC4 */
  __IO uint32_t DFWR;                              /**< Digital Filter Width Register, offset: 0xC8 */
} PORT_Type;

/* ----------------------------------------------------------------------------
   -- PORT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Masks PORT Register Masks
 * @{
 */

/*! @name PCR - Pin Control Register n */
#define PORT_PCR_PS_MASK                         (0x1U)
#define PORT_PCR_PS_SHIFT                        (0U)
#define PORT_PCR_PS(x)                           (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PS_SHIFT)) & PORT_PCR_PS_MASK)
#define PORT_PCR_PE_MASK                         (0x2U)
#define PORT_PCR_PE_SHIFT                        (1U)
#define PORT_PCR_PE(x)                           (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PE_SHIFT)) & PORT_PCR_PE_MASK)
#define PORT_PCR_SRE_MASK                        (0x4U)
#define PORT_PCR_SRE_SHIFT                       (2U)
#define PORT_PCR_SRE(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_SRE_SHIFT)) & PORT_PCR_SRE_MASK)
#define PORT_PCR_PFE_MASK                        (0x10U)
#define PORT_PCR_PFE_SHIFT                       (4U)
#define PORT_PCR_PFE(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PFE_SHIFT)) & PORT_PCR_PFE_MASK)
#define PORT_PCR_ODE_MASK                        (0x20U)
#define PORT_PCR_ODE_SHIFT                       (5U)
#define PORT_PCR_ODE(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_ODE_SHIFT)) & PORT_PCR_ODE_MASK)
#define PORT_PCR_DSE_MASK                        (0x40U)
#define PORT_PCR_DSE_SHIFT                       (6U)
#define PORT_PCR_DSE(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_DSE_SHIFT)) & PORT_PCR_DSE_MASK)
#define PORT_PCR_MUX_MASK                        (0xF00U)
#define PORT_PCR_MUX_SHIFT                       (8U)
#define PORT_PCR_MUX(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_MUX_SHIFT)) & PORT_PCR_MUX_MASK)
#define PORT_PCR_LK_MASK                         (0x8000U)
#define PORT_PCR_LK_SHIFT                        (15U)
#define PORT_PCR_LK(x)                           (((uint32_t)(((uint32_t)(x)) << PORT_PCR_LK_SHIFT)) & PORT_PCR_LK_MASK)
#define PORT_PCR_IRQC_MASK                       (0xF0000U)
#define PORT_PCR_IRQC_SHIFT                      (16U)
#define PORT_PCR_IRQC(x)                         (((uint32_t)(((uint32_t)(x)) << PORT_PCR_IRQC_SHIFT)) & PORT_PCR_IRQC_MASK)
#define PORT_PCR_ISF_MASK                        (0x1000000U)
#define PORT_PCR_ISF_SHIFT                       (24U)
#define PORT_PCR_ISF(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_ISF_SHIFT)) & PORT_PCR_ISF_MASK)

/* The count of PORT_PCR */
#define PORT_PCR_COUNT                           (32U)

/*! @name GPCLR - Global Pin Control Low Register */
#define PORT_GPCLR_GPWD_MASK                     (0xFFFFU)
#define PORT_GPCLR_GPWD_SHIFT                    (0U)
#define PORT_GPCLR_GPWD(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCLR_GPWD_SHIFT)) & PORT_GPCLR_GPWD_MASK)
#define PORT_GPCLR_GPWE_MASK                     (0xFFFF0000U)
#define PORT_GPCLR_GPWE_SHIFT                    (16U)
#define PORT_GPCLR_GPWE(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCLR_GPWE_SHIFT)) & PORT_GPCLR_GPWE_MASK)

/*! @name GPCHR - Global Pin Control High Register */
#define PORT_GPCHR_GPWD_MASK                     (0xFFFFU)
#define PORT_GPCHR_GPWD_SHIFT                    (0U)
#define PORT_GPCHR_GPWD(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCHR_GPWD_SHIFT)) & PORT_GPCHR_GPWD_MASK)
#define PORT_GPCHR_GPWE_MASK                     (0xFFFF0000U)
#define PORT_GPCHR_GPWE_SHIFT                    (16U)
#define PORT_GPCHR_GPWE(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCHR_GPWE_SHIFT)) & PORT_GPCHR_GPWE_MASK)

/*! @name ISFR - Interrupt Status Flag Register */
#define PORT_ISFR_ISF_MASK                       (0xFFFFFFFFU)
#define PORT_ISFR_ISF_SHIFT                      (0U)
#define PORT_ISFR_ISF(x)                         (((uint32_t)(((uint32_t)(x)) << PORT_ISFR_ISF_SHIFT)) & PORT_ISFR_ISF_MASK)

/*! @name DFER - Digital Filter Enable Register */
#define PORT_DFER_DFE_MASK                       (0xFFFFFFFFU)
#define PORT_DFER_DFE_SHIFT                      (0U)
#define PORT_DFER_DFE(x)                         (((uint32_t)(((uint32_t)(x)) << PORT_DFER_DFE_SHIFT)) & PORT_DFER_DFE_MASK)

/*! @name DFCR - Digital Filter Clock Register */
#define PORT_DFCR_CS_MASK                        (0x1U)
#define PORT_DFCR_CS_SHIFT                       (0U)
#define PORT_DFCR_CS(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_DFCR_CS_SHIFT)) & PORT_DFCR_CS_MASK)

/*! @name DFWR - Digital Filter Width Register */
#define PORT_DFWR_FILT_MASK                      (0x1FU)
#define PORT_DFWR_FILT_SHIFT                     (0U)
#define PORT_DFWR_FILT(x)                        (((uint32_t)(((uint32_t)(x)) << PORT_DFWR_FILT_SHIFT)) & PORT_DFWR_FILT_MASK)


/*!
 * @}
 */ /* end of group PORT_Register_Masks */


/* PORT - Peripheral instance base addresses */
/** Peripheral PORTA base address */
#define PORTA_BASE                               (0x40049000u)
/** Peripheral PORTA base pointer */
#define PORTA                                    ((PORT_Type *)PORTA_BASE)
/** Peripheral PORTB base address */
#define PORTB_BASE                               (0x4004A000u)
/** Peripheral PORTB base pointer */
#define PORTB                                    ((PORT_Type *)PORTB_BASE)
/** Peripheral PORTC base address */
#define PORTC_BASE                               (0x4004B000u)
/** Peripheral PORTC base pointer */
#define PORTC                                    ((PORT_Type *)PORTC_BASE)
/** Peripheral PORTD base address */
#define PORTD_BASE                               (0x4004C000u)
/** Peripheral PORTD base pointer */
#define PORTD                                    ((PORT_Type *)PORTD_BASE)
/** Peripheral PORTE base address */
#define PORTE_BASE                               (0x4004D000u)
/** Peripheral PORTE base pointer */
#define PORTE                                    ((PORT_Type *)PORTE_BASE)
/** Array initializer of PORT peripheral base addresses */
#define PORT_BASE_ADDRS                          { PORTA_BASE, PORTB_BASE, PORTC_BASE, PORTD_BASE, PORTE_BASE }
/** Array initializer of PORT peripheral base pointers */
#define PORT_BASE_PTRS                           { PORTA, PORTB, PORTC, PORTD, PORTE }
/** Interrupt vectors for the PORT peripheral type */
#define PORT_IRQS                                { PORTA_IRQn, PORTB_IRQn, PORTC_IRQn, PORTD_IRQn, PORTE_IRQn }

/*!
 * @}
 */ /* end of group PORT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- PWM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PWM_Peripheral_Access_Layer PWM Peripheral Access Layer
 * @{
 */

/** PWM - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0x60 */
    __I  uint16_t CNT;                               /**< Counter Register, array offset: 0x0, array step: 0x60 */
    __IO uint16_t INIT;                              /**< Initial Count Register, array offset: 0x2, array step: 0x60 */
    __IO uint16_t CTRL2;                             /**< Control 2 Register, array offset: 0x4, array step: 0x60 */
    __IO uint16_t CTRL;                              /**< Control Register, array offset: 0x6, array step: 0x60 */
         uint8_t RESERVED_0[2];
    __IO uint16_t VAL0;                              /**< Value Register 0, array offset: 0xA, array step: 0x60 */
    __IO uint16_t FRACVAL1;                          /**< Fractional Value Register 1, array offset: 0xC, array step: 0x60 */
    __IO uint16_t VAL1;                              /**< Value Register 1, array offset: 0xE, array step: 0x60 */
    __IO uint16_t FRACVAL2;                          /**< Fractional Value Register 2, array offset: 0x10, array step: 0x60 */
    __IO uint16_t VAL2;                              /**< Value Register 2, array offset: 0x12, array step: 0x60 */
    __IO uint16_t FRACVAL3;                          /**< Fractional Value Register 3, array offset: 0x14, array step: 0x60 */
    __IO uint16_t VAL3;                              /**< Value Register 3, array offset: 0x16, array step: 0x60 */
    __IO uint16_t FRACVAL4;                          /**< Fractional Value Register 4, array offset: 0x18, array step: 0x60 */
    __IO uint16_t VAL4;                              /**< Value Register 4, array offset: 0x1A, array step: 0x60 */
    __IO uint16_t FRACVAL5;                          /**< Fractional Value Register 5, array offset: 0x1C, array step: 0x60 */
    __IO uint16_t VAL5;                              /**< Value Register 5, array offset: 0x1E, array step: 0x60 */
    __IO uint16_t FRCTRL;                            /**< Fractional Control Register, array offset: 0x20, array step: 0x60 */
    __IO uint16_t OCTRL;                             /**< Output Control Register, array offset: 0x22, array step: 0x60 */
    __IO uint16_t STS;                               /**< Status Register, array offset: 0x24, array step: 0x60 */
    __IO uint16_t INTEN;                             /**< Interrupt Enable Register, array offset: 0x26, array step: 0x60 */
    __IO uint16_t DMAEN;                             /**< DMA Enable Register, array offset: 0x28, array step: 0x60 */
    __IO uint16_t TCTRL;                             /**< Output Trigger Control Register, array offset: 0x2A, array step: 0x60 */
    __IO uint16_t DISMAP[1];                         /**< Fault Disable Mapping Register 0, array offset: 0x2C, array step: index*0x60, index2*0x2 */
         uint8_t RESERVED_1[2];
    __IO uint16_t DTCNT0;                            /**< Deadtime Count Register 0, array offset: 0x30, array step: 0x60 */
    __IO uint16_t DTCNT1;                            /**< Deadtime Count Register 1, array offset: 0x32, array step: 0x60 */
    __IO uint16_t CAPTCTRLA;                         /**< Capture Control A Register, array offset: 0x34, array step: 0x60 */
    __IO uint16_t CAPTCOMPA;                         /**< Capture Compare A Register, array offset: 0x36, array step: 0x60 */
    __IO uint16_t CAPTCTRLB;                         /**< Capture Control B Register, array offset: 0x38, array step: 0x60 */
    __IO uint16_t CAPTCOMPB;                         /**< Capture Compare B Register, array offset: 0x3A, array step: 0x60 */
    __IO uint16_t CAPTCTRLX;                         /**< Capture Control X Register, array offset: 0x3C, array step: 0x60 */
    __IO uint16_t CAPTCOMPX;                         /**< Capture Compare X Register, array offset: 0x3E, array step: 0x60 */
    __I  uint16_t CVAL0;                             /**< Capture Value 0 Register, array offset: 0x40, array step: 0x60 */
    __I  uint16_t CVAL0CYC;                          /**< Capture Value 0 Cycle Register, array offset: 0x42, array step: 0x60 */
    __I  uint16_t CVAL1;                             /**< Capture Value 1 Register, array offset: 0x44, array step: 0x60 */
    __I  uint16_t CVAL1CYC;                          /**< Capture Value 1 Cycle Register, array offset: 0x46, array step: 0x60 */
    __I  uint16_t CVAL2;                             /**< Capture Value 2 Register, array offset: 0x48, array step: 0x60 */
    __I  uint16_t CVAL2CYC;                          /**< Capture Value 2 Cycle Register, array offset: 0x4A, array step: 0x60 */
    __I  uint16_t CVAL3;                             /**< Capture Value 3 Register, array offset: 0x4C, array step: 0x60 */
    __I  uint16_t CVAL3CYC;                          /**< Capture Value 3 Cycle Register, array offset: 0x4E, array step: 0x60 */
    __I  uint16_t CVAL4;                             /**< Capture Value 4 Register, array offset: 0x50, array step: 0x60 */
    __I  uint16_t CVAL4CYC;                          /**< Capture Value 4 Cycle Register, array offset: 0x52, array step: 0x60 */
    __I  uint16_t CVAL5;                             /**< Capture Value 5 Register, array offset: 0x54, array step: 0x60 */
    __I  uint16_t CVAL5CYC;                          /**< Capture Value 5 Cycle Register, array offset: 0x56, array step: 0x60 */
         uint8_t RESERVED_2[8];
  } SM[4];
  __IO uint16_t OUTEN;                             /**< Output Enable Register, offset: 0x180 */
  __IO uint16_t MASK;                              /**< Mask Register, offset: 0x182 */
  __IO uint16_t SWCOUT;                            /**< Software Controlled Output Register, offset: 0x184 */
  __IO uint16_t DTSRCSEL;                          /**< PWM Source Select Register, offset: 0x186 */
  __IO uint16_t MCTRL;                             /**< Master Control Register 0, offset: 0x188 */
  __IO uint16_t MCTRL2;                            /**< Master Control Register 1, offset: 0x18A */
  __IO uint16_t FCTRL;                             /**< Fault Control Register, offset: 0x18C */
  __IO uint16_t FSTS;                              /**< Fault Status Register, offset: 0x18E */
  __IO uint16_t FFILT;                             /**< Fault Filter Register, offset: 0x190 */
  __IO uint16_t FTST;                              /**< Fault Test Register, offset: 0x192 */
  __IO uint16_t FCTRL2;                            /**< Fault Control 2 Register, offset: 0x194 */
} PWM_Type;

/* ----------------------------------------------------------------------------
   -- PWM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PWM_Register_Masks PWM Register Masks
 * @{
 */

/*! @name CNT - Counter Register */
#define PWM_CNT_CNT_MASK                         (0xFFFFU)
#define PWM_CNT_CNT_SHIFT                        (0U)
#define PWM_CNT_CNT(x)                           (((uint16_t)(((uint16_t)(x)) << PWM_CNT_CNT_SHIFT)) & PWM_CNT_CNT_MASK)

/* The count of PWM_CNT */
#define PWM_CNT_COUNT                            (4U)

/*! @name INIT - Initial Count Register */
#define PWM_INIT_INIT_MASK                       (0xFFFFU)
#define PWM_INIT_INIT_SHIFT                      (0U)
#define PWM_INIT_INIT(x)                         (((uint16_t)(((uint16_t)(x)) << PWM_INIT_INIT_SHIFT)) & PWM_INIT_INIT_MASK)

/* The count of PWM_INIT */
#define PWM_INIT_COUNT                           (4U)

/*! @name CTRL2 - Control 2 Register */
#define PWM_CTRL2_CLK_SEL_MASK                   (0x3U)
#define PWM_CTRL2_CLK_SEL_SHIFT                  (0U)
#define PWM_CTRL2_CLK_SEL(x)                     (((uint16_t)(((uint16_t)(x)) << PWM_CTRL2_CLK_SEL_SHIFT)) & PWM_CTRL2_CLK_SEL_MASK)
#define PWM_CTRL2_RELOAD_SEL_MASK                (0x4U)
#define PWM_CTRL2_RELOAD_SEL_SHIFT               (2U)
#define PWM_CTRL2_RELOAD_SEL(x)                  (((uint16_t)(((uint16_t)(x)) << PWM_CTRL2_RELOAD_SEL_SHIFT)) & PWM_CTRL2_RELOAD_SEL_MASK)
#define PWM_CTRL2_FORCE_SEL_MASK                 (0x38U)
#define PWM_CTRL2_FORCE_SEL_SHIFT                (3U)
#define PWM_CTRL2_FORCE_SEL(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_CTRL2_FORCE_SEL_SHIFT)) & PWM_CTRL2_FORCE_SEL_MASK)
#define PWM_CTRL2_FORCE_MASK                     (0x40U)
#define PWM_CTRL2_FORCE_SHIFT                    (6U)
#define PWM_CTRL2_FORCE(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_CTRL2_FORCE_SHIFT)) & PWM_CTRL2_FORCE_MASK)
#define PWM_CTRL2_FRCEN_MASK                     (0x80U)
#define PWM_CTRL2_FRCEN_SHIFT                    (7U)
#define PWM_CTRL2_FRCEN(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_CTRL2_FRCEN_SHIFT)) & PWM_CTRL2_FRCEN_MASK)
#define PWM_CTRL2_INIT_SEL_MASK                  (0x300U)
#define PWM_CTRL2_INIT_SEL_SHIFT                 (8U)
#define PWM_CTRL2_INIT_SEL(x)                    (((uint16_t)(((uint16_t)(x)) << PWM_CTRL2_INIT_SEL_SHIFT)) & PWM_CTRL2_INIT_SEL_MASK)
#define PWM_CTRL2_PWMX_INIT_MASK                 (0x400U)
#define PWM_CTRL2_PWMX_INIT_SHIFT                (10U)
#define PWM_CTRL2_PWMX_INIT(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_CTRL2_PWMX_INIT_SHIFT)) & PWM_CTRL2_PWMX_INIT_MASK)
#define PWM_CTRL2_PWM45_INIT_MASK                (0x800U)
#define PWM_CTRL2_PWM45_INIT_SHIFT               (11U)
#define PWM_CTRL2_PWM45_INIT(x)                  (((uint16_t)(((uint16_t)(x)) << PWM_CTRL2_PWM45_INIT_SHIFT)) & PWM_CTRL2_PWM45_INIT_MASK)
#define PWM_CTRL2_PWM23_INIT_MASK                (0x1000U)
#define PWM_CTRL2_PWM23_INIT_SHIFT               (12U)
#define PWM_CTRL2_PWM23_INIT(x)                  (((uint16_t)(((uint16_t)(x)) << PWM_CTRL2_PWM23_INIT_SHIFT)) & PWM_CTRL2_PWM23_INIT_MASK)
#define PWM_CTRL2_INDEP_MASK                     (0x2000U)
#define PWM_CTRL2_INDEP_SHIFT                    (13U)
#define PWM_CTRL2_INDEP(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_CTRL2_INDEP_SHIFT)) & PWM_CTRL2_INDEP_MASK)
#define PWM_CTRL2_WAITEN_MASK                    (0x4000U)
#define PWM_CTRL2_WAITEN_SHIFT                   (14U)
#define PWM_CTRL2_WAITEN(x)                      (((uint16_t)(((uint16_t)(x)) << PWM_CTRL2_WAITEN_SHIFT)) & PWM_CTRL2_WAITEN_MASK)
#define PWM_CTRL2_DBGEN_MASK                     (0x8000U)
#define PWM_CTRL2_DBGEN_SHIFT                    (15U)
#define PWM_CTRL2_DBGEN(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_CTRL2_DBGEN_SHIFT)) & PWM_CTRL2_DBGEN_MASK)

/* The count of PWM_CTRL2 */
#define PWM_CTRL2_COUNT                          (4U)

/*! @name CTRL - Control Register */
#define PWM_CTRL_DBLEN_MASK                      (0x1U)
#define PWM_CTRL_DBLEN_SHIFT                     (0U)
#define PWM_CTRL_DBLEN(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_CTRL_DBLEN_SHIFT)) & PWM_CTRL_DBLEN_MASK)
#define PWM_CTRL_DBLX_MASK                       (0x2U)
#define PWM_CTRL_DBLX_SHIFT                      (1U)
#define PWM_CTRL_DBLX(x)                         (((uint16_t)(((uint16_t)(x)) << PWM_CTRL_DBLX_SHIFT)) & PWM_CTRL_DBLX_MASK)
#define PWM_CTRL_LDMOD_MASK                      (0x4U)
#define PWM_CTRL_LDMOD_SHIFT                     (2U)
#define PWM_CTRL_LDMOD(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_CTRL_LDMOD_SHIFT)) & PWM_CTRL_LDMOD_MASK)
#define PWM_CTRL_PRSC_MASK                       (0x70U)
#define PWM_CTRL_PRSC_SHIFT                      (4U)
#define PWM_CTRL_PRSC(x)                         (((uint16_t)(((uint16_t)(x)) << PWM_CTRL_PRSC_SHIFT)) & PWM_CTRL_PRSC_MASK)
#define PWM_CTRL_DT_MASK                         (0x300U)
#define PWM_CTRL_DT_SHIFT                        (8U)
#define PWM_CTRL_DT(x)                           (((uint16_t)(((uint16_t)(x)) << PWM_CTRL_DT_SHIFT)) & PWM_CTRL_DT_MASK)
#define PWM_CTRL_FULL_MASK                       (0x400U)
#define PWM_CTRL_FULL_SHIFT                      (10U)
#define PWM_CTRL_FULL(x)                         (((uint16_t)(((uint16_t)(x)) << PWM_CTRL_FULL_SHIFT)) & PWM_CTRL_FULL_MASK)
#define PWM_CTRL_HALF_MASK                       (0x800U)
#define PWM_CTRL_HALF_SHIFT                      (11U)
#define PWM_CTRL_HALF(x)                         (((uint16_t)(((uint16_t)(x)) << PWM_CTRL_HALF_SHIFT)) & PWM_CTRL_HALF_MASK)
#define PWM_CTRL_LDFQ_MASK                       (0xF000U)
#define PWM_CTRL_LDFQ_SHIFT                      (12U)
#define PWM_CTRL_LDFQ(x)                         (((uint16_t)(((uint16_t)(x)) << PWM_CTRL_LDFQ_SHIFT)) & PWM_CTRL_LDFQ_MASK)

/* The count of PWM_CTRL */
#define PWM_CTRL_COUNT                           (4U)

/*! @name VAL0 - Value Register 0 */
#define PWM_VAL0_VAL0_MASK                       (0xFFFFU)
#define PWM_VAL0_VAL0_SHIFT                      (0U)
#define PWM_VAL0_VAL0(x)                         (((uint16_t)(((uint16_t)(x)) << PWM_VAL0_VAL0_SHIFT)) & PWM_VAL0_VAL0_MASK)

/* The count of PWM_VAL0 */
#define PWM_VAL0_COUNT                           (4U)

/*! @name FRACVAL1 - Fractional Value Register 1 */
#define PWM_FRACVAL1_FRACVAL1_MASK               (0xF800U)
#define PWM_FRACVAL1_FRACVAL1_SHIFT              (11U)
#define PWM_FRACVAL1_FRACVAL1(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_FRACVAL1_FRACVAL1_SHIFT)) & PWM_FRACVAL1_FRACVAL1_MASK)

/* The count of PWM_FRACVAL1 */
#define PWM_FRACVAL1_COUNT                       (4U)

/*! @name VAL1 - Value Register 1 */
#define PWM_VAL1_VAL1_MASK                       (0xFFFFU)
#define PWM_VAL1_VAL1_SHIFT                      (0U)
#define PWM_VAL1_VAL1(x)                         (((uint16_t)(((uint16_t)(x)) << PWM_VAL1_VAL1_SHIFT)) & PWM_VAL1_VAL1_MASK)

/* The count of PWM_VAL1 */
#define PWM_VAL1_COUNT                           (4U)

/*! @name FRACVAL2 - Fractional Value Register 2 */
#define PWM_FRACVAL2_FRACVAL2_MASK               (0xF800U)
#define PWM_FRACVAL2_FRACVAL2_SHIFT              (11U)
#define PWM_FRACVAL2_FRACVAL2(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_FRACVAL2_FRACVAL2_SHIFT)) & PWM_FRACVAL2_FRACVAL2_MASK)

/* The count of PWM_FRACVAL2 */
#define PWM_FRACVAL2_COUNT                       (4U)

/*! @name VAL2 - Value Register 2 */
#define PWM_VAL2_VAL2_MASK                       (0xFFFFU)
#define PWM_VAL2_VAL2_SHIFT                      (0U)
#define PWM_VAL2_VAL2(x)                         (((uint16_t)(((uint16_t)(x)) << PWM_VAL2_VAL2_SHIFT)) & PWM_VAL2_VAL2_MASK)

/* The count of PWM_VAL2 */
#define PWM_VAL2_COUNT                           (4U)

/*! @name FRACVAL3 - Fractional Value Register 3 */
#define PWM_FRACVAL3_FRACVAL3_MASK               (0xF800U)
#define PWM_FRACVAL3_FRACVAL3_SHIFT              (11U)
#define PWM_FRACVAL3_FRACVAL3(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_FRACVAL3_FRACVAL3_SHIFT)) & PWM_FRACVAL3_FRACVAL3_MASK)

/* The count of PWM_FRACVAL3 */
#define PWM_FRACVAL3_COUNT                       (4U)

/*! @name VAL3 - Value Register 3 */
#define PWM_VAL3_VAL3_MASK                       (0xFFFFU)
#define PWM_VAL3_VAL3_SHIFT                      (0U)
#define PWM_VAL3_VAL3(x)                         (((uint16_t)(((uint16_t)(x)) << PWM_VAL3_VAL3_SHIFT)) & PWM_VAL3_VAL3_MASK)

/* The count of PWM_VAL3 */
#define PWM_VAL3_COUNT                           (4U)

/*! @name FRACVAL4 - Fractional Value Register 4 */
#define PWM_FRACVAL4_FRACVAL4_MASK               (0xF800U)
#define PWM_FRACVAL4_FRACVAL4_SHIFT              (11U)
#define PWM_FRACVAL4_FRACVAL4(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_FRACVAL4_FRACVAL4_SHIFT)) & PWM_FRACVAL4_FRACVAL4_MASK)

/* The count of PWM_FRACVAL4 */
#define PWM_FRACVAL4_COUNT                       (4U)

/*! @name VAL4 - Value Register 4 */
#define PWM_VAL4_VAL4_MASK                       (0xFFFFU)
#define PWM_VAL4_VAL4_SHIFT                      (0U)
#define PWM_VAL4_VAL4(x)                         (((uint16_t)(((uint16_t)(x)) << PWM_VAL4_VAL4_SHIFT)) & PWM_VAL4_VAL4_MASK)

/* The count of PWM_VAL4 */
#define PWM_VAL4_COUNT                           (4U)

/*! @name FRACVAL5 - Fractional Value Register 5 */
#define PWM_FRACVAL5_FRACVAL5_MASK               (0xF800U)
#define PWM_FRACVAL5_FRACVAL5_SHIFT              (11U)
#define PWM_FRACVAL5_FRACVAL5(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_FRACVAL5_FRACVAL5_SHIFT)) & PWM_FRACVAL5_FRACVAL5_MASK)

/* The count of PWM_FRACVAL5 */
#define PWM_FRACVAL5_COUNT                       (4U)

/*! @name VAL5 - Value Register 5 */
#define PWM_VAL5_VAL5_MASK                       (0xFFFFU)
#define PWM_VAL5_VAL5_SHIFT                      (0U)
#define PWM_VAL5_VAL5(x)                         (((uint16_t)(((uint16_t)(x)) << PWM_VAL5_VAL5_SHIFT)) & PWM_VAL5_VAL5_MASK)

/* The count of PWM_VAL5 */
#define PWM_VAL5_COUNT                           (4U)

/*! @name FRCTRL - Fractional Control Register */
#define PWM_FRCTRL_FRAC1_EN_MASK                 (0x2U)
#define PWM_FRCTRL_FRAC1_EN_SHIFT                (1U)
#define PWM_FRCTRL_FRAC1_EN(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_FRCTRL_FRAC1_EN_SHIFT)) & PWM_FRCTRL_FRAC1_EN_MASK)
#define PWM_FRCTRL_FRAC23_EN_MASK                (0x4U)
#define PWM_FRCTRL_FRAC23_EN_SHIFT               (2U)
#define PWM_FRCTRL_FRAC23_EN(x)                  (((uint16_t)(((uint16_t)(x)) << PWM_FRCTRL_FRAC23_EN_SHIFT)) & PWM_FRCTRL_FRAC23_EN_MASK)
#define PWM_FRCTRL_FRAC45_EN_MASK                (0x10U)
#define PWM_FRCTRL_FRAC45_EN_SHIFT               (4U)
#define PWM_FRCTRL_FRAC45_EN(x)                  (((uint16_t)(((uint16_t)(x)) << PWM_FRCTRL_FRAC45_EN_SHIFT)) & PWM_FRCTRL_FRAC45_EN_MASK)
#define PWM_FRCTRL_FRAC_PU_MASK                  (0x100U)
#define PWM_FRCTRL_FRAC_PU_SHIFT                 (8U)
#define PWM_FRCTRL_FRAC_PU(x)                    (((uint16_t)(((uint16_t)(x)) << PWM_FRCTRL_FRAC_PU_SHIFT)) & PWM_FRCTRL_FRAC_PU_MASK)
#define PWM_FRCTRL_TEST_MASK                     (0x8000U)
#define PWM_FRCTRL_TEST_SHIFT                    (15U)
#define PWM_FRCTRL_TEST(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_FRCTRL_TEST_SHIFT)) & PWM_FRCTRL_TEST_MASK)

/* The count of PWM_FRCTRL */
#define PWM_FRCTRL_COUNT                         (4U)

/*! @name OCTRL - Output Control Register */
#define PWM_OCTRL_PWMXFS_MASK                    (0x3U)
#define PWM_OCTRL_PWMXFS_SHIFT                   (0U)
#define PWM_OCTRL_PWMXFS(x)                      (((uint16_t)(((uint16_t)(x)) << PWM_OCTRL_PWMXFS_SHIFT)) & PWM_OCTRL_PWMXFS_MASK)
#define PWM_OCTRL_PWMBFS_MASK                    (0xCU)
#define PWM_OCTRL_PWMBFS_SHIFT                   (2U)
#define PWM_OCTRL_PWMBFS(x)                      (((uint16_t)(((uint16_t)(x)) << PWM_OCTRL_PWMBFS_SHIFT)) & PWM_OCTRL_PWMBFS_MASK)
#define PWM_OCTRL_PWMAFS_MASK                    (0x30U)
#define PWM_OCTRL_PWMAFS_SHIFT                   (4U)
#define PWM_OCTRL_PWMAFS(x)                      (((uint16_t)(((uint16_t)(x)) << PWM_OCTRL_PWMAFS_SHIFT)) & PWM_OCTRL_PWMAFS_MASK)
#define PWM_OCTRL_POLX_MASK                      (0x100U)
#define PWM_OCTRL_POLX_SHIFT                     (8U)
#define PWM_OCTRL_POLX(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_OCTRL_POLX_SHIFT)) & PWM_OCTRL_POLX_MASK)
#define PWM_OCTRL_POLB_MASK                      (0x200U)
#define PWM_OCTRL_POLB_SHIFT                     (9U)
#define PWM_OCTRL_POLB(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_OCTRL_POLB_SHIFT)) & PWM_OCTRL_POLB_MASK)
#define PWM_OCTRL_POLA_MASK                      (0x400U)
#define PWM_OCTRL_POLA_SHIFT                     (10U)
#define PWM_OCTRL_POLA(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_OCTRL_POLA_SHIFT)) & PWM_OCTRL_POLA_MASK)
#define PWM_OCTRL_PWMX_IN_MASK                   (0x2000U)
#define PWM_OCTRL_PWMX_IN_SHIFT                  (13U)
#define PWM_OCTRL_PWMX_IN(x)                     (((uint16_t)(((uint16_t)(x)) << PWM_OCTRL_PWMX_IN_SHIFT)) & PWM_OCTRL_PWMX_IN_MASK)
#define PWM_OCTRL_PWMB_IN_MASK                   (0x4000U)
#define PWM_OCTRL_PWMB_IN_SHIFT                  (14U)
#define PWM_OCTRL_PWMB_IN(x)                     (((uint16_t)(((uint16_t)(x)) << PWM_OCTRL_PWMB_IN_SHIFT)) & PWM_OCTRL_PWMB_IN_MASK)
#define PWM_OCTRL_PWMA_IN_MASK                   (0x8000U)
#define PWM_OCTRL_PWMA_IN_SHIFT                  (15U)
#define PWM_OCTRL_PWMA_IN(x)                     (((uint16_t)(((uint16_t)(x)) << PWM_OCTRL_PWMA_IN_SHIFT)) & PWM_OCTRL_PWMA_IN_MASK)

/* The count of PWM_OCTRL */
#define PWM_OCTRL_COUNT                          (4U)

/*! @name STS - Status Register */
#define PWM_STS_CMPF_MASK                        (0x3FU)
#define PWM_STS_CMPF_SHIFT                       (0U)
#define PWM_STS_CMPF(x)                          (((uint16_t)(((uint16_t)(x)) << PWM_STS_CMPF_SHIFT)) & PWM_STS_CMPF_MASK)
#define PWM_STS_CFX0_MASK                        (0x40U)
#define PWM_STS_CFX0_SHIFT                       (6U)
#define PWM_STS_CFX0(x)                          (((uint16_t)(((uint16_t)(x)) << PWM_STS_CFX0_SHIFT)) & PWM_STS_CFX0_MASK)
#define PWM_STS_CFX1_MASK                        (0x80U)
#define PWM_STS_CFX1_SHIFT                       (7U)
#define PWM_STS_CFX1(x)                          (((uint16_t)(((uint16_t)(x)) << PWM_STS_CFX1_SHIFT)) & PWM_STS_CFX1_MASK)
#define PWM_STS_CFB0_MASK                        (0x100U)
#define PWM_STS_CFB0_SHIFT                       (8U)
#define PWM_STS_CFB0(x)                          (((uint16_t)(((uint16_t)(x)) << PWM_STS_CFB0_SHIFT)) & PWM_STS_CFB0_MASK)
#define PWM_STS_CFB1_MASK                        (0x200U)
#define PWM_STS_CFB1_SHIFT                       (9U)
#define PWM_STS_CFB1(x)                          (((uint16_t)(((uint16_t)(x)) << PWM_STS_CFB1_SHIFT)) & PWM_STS_CFB1_MASK)
#define PWM_STS_CFA0_MASK                        (0x400U)
#define PWM_STS_CFA0_SHIFT                       (10U)
#define PWM_STS_CFA0(x)                          (((uint16_t)(((uint16_t)(x)) << PWM_STS_CFA0_SHIFT)) & PWM_STS_CFA0_MASK)
#define PWM_STS_CFA1_MASK                        (0x800U)
#define PWM_STS_CFA1_SHIFT                       (11U)
#define PWM_STS_CFA1(x)                          (((uint16_t)(((uint16_t)(x)) << PWM_STS_CFA1_SHIFT)) & PWM_STS_CFA1_MASK)
#define PWM_STS_RF_MASK                          (0x1000U)
#define PWM_STS_RF_SHIFT                         (12U)
#define PWM_STS_RF(x)                            (((uint16_t)(((uint16_t)(x)) << PWM_STS_RF_SHIFT)) & PWM_STS_RF_MASK)
#define PWM_STS_REF_MASK                         (0x2000U)
#define PWM_STS_REF_SHIFT                        (13U)
#define PWM_STS_REF(x)                           (((uint16_t)(((uint16_t)(x)) << PWM_STS_REF_SHIFT)) & PWM_STS_REF_MASK)
#define PWM_STS_RUF_MASK                         (0x4000U)
#define PWM_STS_RUF_SHIFT                        (14U)
#define PWM_STS_RUF(x)                           (((uint16_t)(((uint16_t)(x)) << PWM_STS_RUF_SHIFT)) & PWM_STS_RUF_MASK)

/* The count of PWM_STS */
#define PWM_STS_COUNT                            (4U)

/*! @name INTEN - Interrupt Enable Register */
#define PWM_INTEN_CMPIE_MASK                     (0x3FU)
#define PWM_INTEN_CMPIE_SHIFT                    (0U)
#define PWM_INTEN_CMPIE(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_INTEN_CMPIE_SHIFT)) & PWM_INTEN_CMPIE_MASK)
#define PWM_INTEN_CX0IE_MASK                     (0x40U)
#define PWM_INTEN_CX0IE_SHIFT                    (6U)
#define PWM_INTEN_CX0IE(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_INTEN_CX0IE_SHIFT)) & PWM_INTEN_CX0IE_MASK)
#define PWM_INTEN_CX1IE_MASK                     (0x80U)
#define PWM_INTEN_CX1IE_SHIFT                    (7U)
#define PWM_INTEN_CX1IE(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_INTEN_CX1IE_SHIFT)) & PWM_INTEN_CX1IE_MASK)
#define PWM_INTEN_CB0IE_MASK                     (0x100U)
#define PWM_INTEN_CB0IE_SHIFT                    (8U)
#define PWM_INTEN_CB0IE(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_INTEN_CB0IE_SHIFT)) & PWM_INTEN_CB0IE_MASK)
#define PWM_INTEN_CB1IE_MASK                     (0x200U)
#define PWM_INTEN_CB1IE_SHIFT                    (9U)
#define PWM_INTEN_CB1IE(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_INTEN_CB1IE_SHIFT)) & PWM_INTEN_CB1IE_MASK)
#define PWM_INTEN_CA0IE_MASK                     (0x400U)
#define PWM_INTEN_CA0IE_SHIFT                    (10U)
#define PWM_INTEN_CA0IE(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_INTEN_CA0IE_SHIFT)) & PWM_INTEN_CA0IE_MASK)
#define PWM_INTEN_CA1IE_MASK                     (0x800U)
#define PWM_INTEN_CA1IE_SHIFT                    (11U)
#define PWM_INTEN_CA1IE(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_INTEN_CA1IE_SHIFT)) & PWM_INTEN_CA1IE_MASK)
#define PWM_INTEN_RIE_MASK                       (0x1000U)
#define PWM_INTEN_RIE_SHIFT                      (12U)
#define PWM_INTEN_RIE(x)                         (((uint16_t)(((uint16_t)(x)) << PWM_INTEN_RIE_SHIFT)) & PWM_INTEN_RIE_MASK)
#define PWM_INTEN_REIE_MASK                      (0x2000U)
#define PWM_INTEN_REIE_SHIFT                     (13U)
#define PWM_INTEN_REIE(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_INTEN_REIE_SHIFT)) & PWM_INTEN_REIE_MASK)

/* The count of PWM_INTEN */
#define PWM_INTEN_COUNT                          (4U)

/*! @name DMAEN - DMA Enable Register */
#define PWM_DMAEN_CX0DE_MASK                     (0x1U)
#define PWM_DMAEN_CX0DE_SHIFT                    (0U)
#define PWM_DMAEN_CX0DE(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_DMAEN_CX0DE_SHIFT)) & PWM_DMAEN_CX0DE_MASK)
#define PWM_DMAEN_CX1DE_MASK                     (0x2U)
#define PWM_DMAEN_CX1DE_SHIFT                    (1U)
#define PWM_DMAEN_CX1DE(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_DMAEN_CX1DE_SHIFT)) & PWM_DMAEN_CX1DE_MASK)
#define PWM_DMAEN_CB0DE_MASK                     (0x4U)
#define PWM_DMAEN_CB0DE_SHIFT                    (2U)
#define PWM_DMAEN_CB0DE(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_DMAEN_CB0DE_SHIFT)) & PWM_DMAEN_CB0DE_MASK)
#define PWM_DMAEN_CB1DE_MASK                     (0x8U)
#define PWM_DMAEN_CB1DE_SHIFT                    (3U)
#define PWM_DMAEN_CB1DE(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_DMAEN_CB1DE_SHIFT)) & PWM_DMAEN_CB1DE_MASK)
#define PWM_DMAEN_CA0DE_MASK                     (0x10U)
#define PWM_DMAEN_CA0DE_SHIFT                    (4U)
#define PWM_DMAEN_CA0DE(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_DMAEN_CA0DE_SHIFT)) & PWM_DMAEN_CA0DE_MASK)
#define PWM_DMAEN_CA1DE_MASK                     (0x20U)
#define PWM_DMAEN_CA1DE_SHIFT                    (5U)
#define PWM_DMAEN_CA1DE(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_DMAEN_CA1DE_SHIFT)) & PWM_DMAEN_CA1DE_MASK)
#define PWM_DMAEN_CAPTDE_MASK                    (0xC0U)
#define PWM_DMAEN_CAPTDE_SHIFT                   (6U)
#define PWM_DMAEN_CAPTDE(x)                      (((uint16_t)(((uint16_t)(x)) << PWM_DMAEN_CAPTDE_SHIFT)) & PWM_DMAEN_CAPTDE_MASK)
#define PWM_DMAEN_FAND_MASK                      (0x100U)
#define PWM_DMAEN_FAND_SHIFT                     (8U)
#define PWM_DMAEN_FAND(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_DMAEN_FAND_SHIFT)) & PWM_DMAEN_FAND_MASK)
#define PWM_DMAEN_VALDE_MASK                     (0x200U)
#define PWM_DMAEN_VALDE_SHIFT                    (9U)
#define PWM_DMAEN_VALDE(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_DMAEN_VALDE_SHIFT)) & PWM_DMAEN_VALDE_MASK)

/* The count of PWM_DMAEN */
#define PWM_DMAEN_COUNT                          (4U)

/*! @name TCTRL - Output Trigger Control Register */
#define PWM_TCTRL_OUT_TRIG_EN_MASK               (0x3FU)
#define PWM_TCTRL_OUT_TRIG_EN_SHIFT              (0U)
#define PWM_TCTRL_OUT_TRIG_EN(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_TCTRL_OUT_TRIG_EN_SHIFT)) & PWM_TCTRL_OUT_TRIG_EN_MASK)
#define PWM_TCTRL_TRGFRQ_MASK                    (0x1000U)
#define PWM_TCTRL_TRGFRQ_SHIFT                   (12U)
#define PWM_TCTRL_TRGFRQ(x)                      (((uint16_t)(((uint16_t)(x)) << PWM_TCTRL_TRGFRQ_SHIFT)) & PWM_TCTRL_TRGFRQ_MASK)
#define PWM_TCTRL_PWBOT1_MASK                    (0x4000U)
#define PWM_TCTRL_PWBOT1_SHIFT                   (14U)
#define PWM_TCTRL_PWBOT1(x)                      (((uint16_t)(((uint16_t)(x)) << PWM_TCTRL_PWBOT1_SHIFT)) & PWM_TCTRL_PWBOT1_MASK)
#define PWM_TCTRL_PWAOT0_MASK                    (0x8000U)
#define PWM_TCTRL_PWAOT0_SHIFT                   (15U)
#define PWM_TCTRL_PWAOT0(x)                      (((uint16_t)(((uint16_t)(x)) << PWM_TCTRL_PWAOT0_SHIFT)) & PWM_TCTRL_PWAOT0_MASK)

/* The count of PWM_TCTRL */
#define PWM_TCTRL_COUNT                          (4U)

/*! @name DISMAP - Fault Disable Mapping Register 0 */
#define PWM_DISMAP_DIS0A_MASK                    (0xFU)
#define PWM_DISMAP_DIS0A_SHIFT                   (0U)
#define PWM_DISMAP_DIS0A(x)                      (((uint16_t)(((uint16_t)(x)) << PWM_DISMAP_DIS0A_SHIFT)) & PWM_DISMAP_DIS0A_MASK)
#define PWM_DISMAP_DIS0B_MASK                    (0xF0U)
#define PWM_DISMAP_DIS0B_SHIFT                   (4U)
#define PWM_DISMAP_DIS0B(x)                      (((uint16_t)(((uint16_t)(x)) << PWM_DISMAP_DIS0B_SHIFT)) & PWM_DISMAP_DIS0B_MASK)
#define PWM_DISMAP_DIS0X_MASK                    (0xF00U)
#define PWM_DISMAP_DIS0X_SHIFT                   (8U)
#define PWM_DISMAP_DIS0X(x)                      (((uint16_t)(((uint16_t)(x)) << PWM_DISMAP_DIS0X_SHIFT)) & PWM_DISMAP_DIS0X_MASK)

/* The count of PWM_DISMAP */
#define PWM_DISMAP_COUNT                         (4U)

/* The count of PWM_DISMAP */
#define PWM_DISMAP_COUNT2                        (1U)

/*! @name DTCNT0 - Deadtime Count Register 0 */
#define PWM_DTCNT0_DTCNT0_MASK                   (0xFFFFU)
#define PWM_DTCNT0_DTCNT0_SHIFT                  (0U)
#define PWM_DTCNT0_DTCNT0(x)                     (((uint16_t)(((uint16_t)(x)) << PWM_DTCNT0_DTCNT0_SHIFT)) & PWM_DTCNT0_DTCNT0_MASK)

/* The count of PWM_DTCNT0 */
#define PWM_DTCNT0_COUNT                         (4U)

/*! @name DTCNT1 - Deadtime Count Register 1 */
#define PWM_DTCNT1_DTCNT1_MASK                   (0xFFFFU)
#define PWM_DTCNT1_DTCNT1_SHIFT                  (0U)
#define PWM_DTCNT1_DTCNT1(x)                     (((uint16_t)(((uint16_t)(x)) << PWM_DTCNT1_DTCNT1_SHIFT)) & PWM_DTCNT1_DTCNT1_MASK)

/* The count of PWM_DTCNT1 */
#define PWM_DTCNT1_COUNT                         (4U)

/*! @name CAPTCTRLA - Capture Control A Register */
#define PWM_CAPTCTRLA_ARMA_MASK                  (0x1U)
#define PWM_CAPTCTRLA_ARMA_SHIFT                 (0U)
#define PWM_CAPTCTRLA_ARMA(x)                    (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLA_ARMA_SHIFT)) & PWM_CAPTCTRLA_ARMA_MASK)
#define PWM_CAPTCTRLA_ONESHOTA_MASK              (0x2U)
#define PWM_CAPTCTRLA_ONESHOTA_SHIFT             (1U)
#define PWM_CAPTCTRLA_ONESHOTA(x)                (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLA_ONESHOTA_SHIFT)) & PWM_CAPTCTRLA_ONESHOTA_MASK)
#define PWM_CAPTCTRLA_EDGA0_MASK                 (0xCU)
#define PWM_CAPTCTRLA_EDGA0_SHIFT                (2U)
#define PWM_CAPTCTRLA_EDGA0(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLA_EDGA0_SHIFT)) & PWM_CAPTCTRLA_EDGA0_MASK)
#define PWM_CAPTCTRLA_EDGA1_MASK                 (0x30U)
#define PWM_CAPTCTRLA_EDGA1_SHIFT                (4U)
#define PWM_CAPTCTRLA_EDGA1(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLA_EDGA1_SHIFT)) & PWM_CAPTCTRLA_EDGA1_MASK)
#define PWM_CAPTCTRLA_INP_SELA_MASK              (0x40U)
#define PWM_CAPTCTRLA_INP_SELA_SHIFT             (6U)
#define PWM_CAPTCTRLA_INP_SELA(x)                (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLA_INP_SELA_SHIFT)) & PWM_CAPTCTRLA_INP_SELA_MASK)
#define PWM_CAPTCTRLA_EDGCNTA_EN_MASK            (0x80U)
#define PWM_CAPTCTRLA_EDGCNTA_EN_SHIFT           (7U)
#define PWM_CAPTCTRLA_EDGCNTA_EN(x)              (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLA_EDGCNTA_EN_SHIFT)) & PWM_CAPTCTRLA_EDGCNTA_EN_MASK)
#define PWM_CAPTCTRLA_CFAWM_MASK                 (0x300U)
#define PWM_CAPTCTRLA_CFAWM_SHIFT                (8U)
#define PWM_CAPTCTRLA_CFAWM(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLA_CFAWM_SHIFT)) & PWM_CAPTCTRLA_CFAWM_MASK)
#define PWM_CAPTCTRLA_CA0CNT_MASK                (0x1C00U)
#define PWM_CAPTCTRLA_CA0CNT_SHIFT               (10U)
#define PWM_CAPTCTRLA_CA0CNT(x)                  (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLA_CA0CNT_SHIFT)) & PWM_CAPTCTRLA_CA0CNT_MASK)
#define PWM_CAPTCTRLA_CA1CNT_MASK                (0xE000U)
#define PWM_CAPTCTRLA_CA1CNT_SHIFT               (13U)
#define PWM_CAPTCTRLA_CA1CNT(x)                  (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLA_CA1CNT_SHIFT)) & PWM_CAPTCTRLA_CA1CNT_MASK)

/* The count of PWM_CAPTCTRLA */
#define PWM_CAPTCTRLA_COUNT                      (4U)

/*! @name CAPTCOMPA - Capture Compare A Register */
#define PWM_CAPTCOMPA_EDGCMPA_MASK               (0xFFU)
#define PWM_CAPTCOMPA_EDGCMPA_SHIFT              (0U)
#define PWM_CAPTCOMPA_EDGCMPA(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCOMPA_EDGCMPA_SHIFT)) & PWM_CAPTCOMPA_EDGCMPA_MASK)
#define PWM_CAPTCOMPA_EDGCNTA_MASK               (0xFF00U)
#define PWM_CAPTCOMPA_EDGCNTA_SHIFT              (8U)
#define PWM_CAPTCOMPA_EDGCNTA(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCOMPA_EDGCNTA_SHIFT)) & PWM_CAPTCOMPA_EDGCNTA_MASK)

/* The count of PWM_CAPTCOMPA */
#define PWM_CAPTCOMPA_COUNT                      (4U)

/*! @name CAPTCTRLB - Capture Control B Register */
#define PWM_CAPTCTRLB_ARMB_MASK                  (0x1U)
#define PWM_CAPTCTRLB_ARMB_SHIFT                 (0U)
#define PWM_CAPTCTRLB_ARMB(x)                    (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLB_ARMB_SHIFT)) & PWM_CAPTCTRLB_ARMB_MASK)
#define PWM_CAPTCTRLB_ONESHOTB_MASK              (0x2U)
#define PWM_CAPTCTRLB_ONESHOTB_SHIFT             (1U)
#define PWM_CAPTCTRLB_ONESHOTB(x)                (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLB_ONESHOTB_SHIFT)) & PWM_CAPTCTRLB_ONESHOTB_MASK)
#define PWM_CAPTCTRLB_EDGB0_MASK                 (0xCU)
#define PWM_CAPTCTRLB_EDGB0_SHIFT                (2U)
#define PWM_CAPTCTRLB_EDGB0(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLB_EDGB0_SHIFT)) & PWM_CAPTCTRLB_EDGB0_MASK)
#define PWM_CAPTCTRLB_EDGB1_MASK                 (0x30U)
#define PWM_CAPTCTRLB_EDGB1_SHIFT                (4U)
#define PWM_CAPTCTRLB_EDGB1(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLB_EDGB1_SHIFT)) & PWM_CAPTCTRLB_EDGB1_MASK)
#define PWM_CAPTCTRLB_INP_SELB_MASK              (0x40U)
#define PWM_CAPTCTRLB_INP_SELB_SHIFT             (6U)
#define PWM_CAPTCTRLB_INP_SELB(x)                (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLB_INP_SELB_SHIFT)) & PWM_CAPTCTRLB_INP_SELB_MASK)
#define PWM_CAPTCTRLB_EDGCNTB_EN_MASK            (0x80U)
#define PWM_CAPTCTRLB_EDGCNTB_EN_SHIFT           (7U)
#define PWM_CAPTCTRLB_EDGCNTB_EN(x)              (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLB_EDGCNTB_EN_SHIFT)) & PWM_CAPTCTRLB_EDGCNTB_EN_MASK)
#define PWM_CAPTCTRLB_CFBWM_MASK                 (0x300U)
#define PWM_CAPTCTRLB_CFBWM_SHIFT                (8U)
#define PWM_CAPTCTRLB_CFBWM(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLB_CFBWM_SHIFT)) & PWM_CAPTCTRLB_CFBWM_MASK)
#define PWM_CAPTCTRLB_CB0CNT_MASK                (0x1C00U)
#define PWM_CAPTCTRLB_CB0CNT_SHIFT               (10U)
#define PWM_CAPTCTRLB_CB0CNT(x)                  (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLB_CB0CNT_SHIFT)) & PWM_CAPTCTRLB_CB0CNT_MASK)
#define PWM_CAPTCTRLB_CB1CNT_MASK                (0xE000U)
#define PWM_CAPTCTRLB_CB1CNT_SHIFT               (13U)
#define PWM_CAPTCTRLB_CB1CNT(x)                  (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLB_CB1CNT_SHIFT)) & PWM_CAPTCTRLB_CB1CNT_MASK)

/* The count of PWM_CAPTCTRLB */
#define PWM_CAPTCTRLB_COUNT                      (4U)

/*! @name CAPTCOMPB - Capture Compare B Register */
#define PWM_CAPTCOMPB_EDGCMPB_MASK               (0xFFU)
#define PWM_CAPTCOMPB_EDGCMPB_SHIFT              (0U)
#define PWM_CAPTCOMPB_EDGCMPB(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCOMPB_EDGCMPB_SHIFT)) & PWM_CAPTCOMPB_EDGCMPB_MASK)
#define PWM_CAPTCOMPB_EDGCNTB_MASK               (0xFF00U)
#define PWM_CAPTCOMPB_EDGCNTB_SHIFT              (8U)
#define PWM_CAPTCOMPB_EDGCNTB(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCOMPB_EDGCNTB_SHIFT)) & PWM_CAPTCOMPB_EDGCNTB_MASK)

/* The count of PWM_CAPTCOMPB */
#define PWM_CAPTCOMPB_COUNT                      (4U)

/*! @name CAPTCTRLX - Capture Control X Register */
#define PWM_CAPTCTRLX_ARMX_MASK                  (0x1U)
#define PWM_CAPTCTRLX_ARMX_SHIFT                 (0U)
#define PWM_CAPTCTRLX_ARMX(x)                    (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLX_ARMX_SHIFT)) & PWM_CAPTCTRLX_ARMX_MASK)
#define PWM_CAPTCTRLX_ONESHOTX_MASK              (0x2U)
#define PWM_CAPTCTRLX_ONESHOTX_SHIFT             (1U)
#define PWM_CAPTCTRLX_ONESHOTX(x)                (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLX_ONESHOTX_SHIFT)) & PWM_CAPTCTRLX_ONESHOTX_MASK)
#define PWM_CAPTCTRLX_EDGX0_MASK                 (0xCU)
#define PWM_CAPTCTRLX_EDGX0_SHIFT                (2U)
#define PWM_CAPTCTRLX_EDGX0(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLX_EDGX0_SHIFT)) & PWM_CAPTCTRLX_EDGX0_MASK)
#define PWM_CAPTCTRLX_EDGX1_MASK                 (0x30U)
#define PWM_CAPTCTRLX_EDGX1_SHIFT                (4U)
#define PWM_CAPTCTRLX_EDGX1(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLX_EDGX1_SHIFT)) & PWM_CAPTCTRLX_EDGX1_MASK)
#define PWM_CAPTCTRLX_INP_SELX_MASK              (0x40U)
#define PWM_CAPTCTRLX_INP_SELX_SHIFT             (6U)
#define PWM_CAPTCTRLX_INP_SELX(x)                (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLX_INP_SELX_SHIFT)) & PWM_CAPTCTRLX_INP_SELX_MASK)
#define PWM_CAPTCTRLX_EDGCNTX_EN_MASK            (0x80U)
#define PWM_CAPTCTRLX_EDGCNTX_EN_SHIFT           (7U)
#define PWM_CAPTCTRLX_EDGCNTX_EN(x)              (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLX_EDGCNTX_EN_SHIFT)) & PWM_CAPTCTRLX_EDGCNTX_EN_MASK)
#define PWM_CAPTCTRLX_CFXWM_MASK                 (0x300U)
#define PWM_CAPTCTRLX_CFXWM_SHIFT                (8U)
#define PWM_CAPTCTRLX_CFXWM(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLX_CFXWM_SHIFT)) & PWM_CAPTCTRLX_CFXWM_MASK)
#define PWM_CAPTCTRLX_CX0CNT_MASK                (0x1C00U)
#define PWM_CAPTCTRLX_CX0CNT_SHIFT               (10U)
#define PWM_CAPTCTRLX_CX0CNT(x)                  (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLX_CX0CNT_SHIFT)) & PWM_CAPTCTRLX_CX0CNT_MASK)
#define PWM_CAPTCTRLX_CX1CNT_MASK                (0xE000U)
#define PWM_CAPTCTRLX_CX1CNT_SHIFT               (13U)
#define PWM_CAPTCTRLX_CX1CNT(x)                  (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCTRLX_CX1CNT_SHIFT)) & PWM_CAPTCTRLX_CX1CNT_MASK)

/* The count of PWM_CAPTCTRLX */
#define PWM_CAPTCTRLX_COUNT                      (4U)

/*! @name CAPTCOMPX - Capture Compare X Register */
#define PWM_CAPTCOMPX_EDGCMPX_MASK               (0xFFU)
#define PWM_CAPTCOMPX_EDGCMPX_SHIFT              (0U)
#define PWM_CAPTCOMPX_EDGCMPX(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCOMPX_EDGCMPX_SHIFT)) & PWM_CAPTCOMPX_EDGCMPX_MASK)
#define PWM_CAPTCOMPX_EDGCNTX_MASK               (0xFF00U)
#define PWM_CAPTCOMPX_EDGCNTX_SHIFT              (8U)
#define PWM_CAPTCOMPX_EDGCNTX(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_CAPTCOMPX_EDGCNTX_SHIFT)) & PWM_CAPTCOMPX_EDGCNTX_MASK)

/* The count of PWM_CAPTCOMPX */
#define PWM_CAPTCOMPX_COUNT                      (4U)

/*! @name CVAL0 - Capture Value 0 Register */
#define PWM_CVAL0_CAPTVAL0_MASK                  (0xFFFFU)
#define PWM_CVAL0_CAPTVAL0_SHIFT                 (0U)
#define PWM_CVAL0_CAPTVAL0(x)                    (((uint16_t)(((uint16_t)(x)) << PWM_CVAL0_CAPTVAL0_SHIFT)) & PWM_CVAL0_CAPTVAL0_MASK)

/* The count of PWM_CVAL0 */
#define PWM_CVAL0_COUNT                          (4U)

/*! @name CVAL0CYC - Capture Value 0 Cycle Register */
#define PWM_CVAL0CYC_CVAL0CYC_MASK               (0xFU)
#define PWM_CVAL0CYC_CVAL0CYC_SHIFT              (0U)
#define PWM_CVAL0CYC_CVAL0CYC(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_CVAL0CYC_CVAL0CYC_SHIFT)) & PWM_CVAL0CYC_CVAL0CYC_MASK)

/* The count of PWM_CVAL0CYC */
#define PWM_CVAL0CYC_COUNT                       (4U)

/*! @name CVAL1 - Capture Value 1 Register */
#define PWM_CVAL1_CAPTVAL1_MASK                  (0xFFFFU)
#define PWM_CVAL1_CAPTVAL1_SHIFT                 (0U)
#define PWM_CVAL1_CAPTVAL1(x)                    (((uint16_t)(((uint16_t)(x)) << PWM_CVAL1_CAPTVAL1_SHIFT)) & PWM_CVAL1_CAPTVAL1_MASK)

/* The count of PWM_CVAL1 */
#define PWM_CVAL1_COUNT                          (4U)

/*! @name CVAL1CYC - Capture Value 1 Cycle Register */
#define PWM_CVAL1CYC_CVAL1CYC_MASK               (0xFU)
#define PWM_CVAL1CYC_CVAL1CYC_SHIFT              (0U)
#define PWM_CVAL1CYC_CVAL1CYC(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_CVAL1CYC_CVAL1CYC_SHIFT)) & PWM_CVAL1CYC_CVAL1CYC_MASK)

/* The count of PWM_CVAL1CYC */
#define PWM_CVAL1CYC_COUNT                       (4U)

/*! @name CVAL2 - Capture Value 2 Register */
#define PWM_CVAL2_CAPTVAL2_MASK                  (0xFFFFU)
#define PWM_CVAL2_CAPTVAL2_SHIFT                 (0U)
#define PWM_CVAL2_CAPTVAL2(x)                    (((uint16_t)(((uint16_t)(x)) << PWM_CVAL2_CAPTVAL2_SHIFT)) & PWM_CVAL2_CAPTVAL2_MASK)

/* The count of PWM_CVAL2 */
#define PWM_CVAL2_COUNT                          (4U)

/*! @name CVAL2CYC - Capture Value 2 Cycle Register */
#define PWM_CVAL2CYC_CVAL2CYC_MASK               (0xFU)
#define PWM_CVAL2CYC_CVAL2CYC_SHIFT              (0U)
#define PWM_CVAL2CYC_CVAL2CYC(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_CVAL2CYC_CVAL2CYC_SHIFT)) & PWM_CVAL2CYC_CVAL2CYC_MASK)

/* The count of PWM_CVAL2CYC */
#define PWM_CVAL2CYC_COUNT                       (4U)

/*! @name CVAL3 - Capture Value 3 Register */
#define PWM_CVAL3_CAPTVAL3_MASK                  (0xFFFFU)
#define PWM_CVAL3_CAPTVAL3_SHIFT                 (0U)
#define PWM_CVAL3_CAPTVAL3(x)                    (((uint16_t)(((uint16_t)(x)) << PWM_CVAL3_CAPTVAL3_SHIFT)) & PWM_CVAL3_CAPTVAL3_MASK)

/* The count of PWM_CVAL3 */
#define PWM_CVAL3_COUNT                          (4U)

/*! @name CVAL3CYC - Capture Value 3 Cycle Register */
#define PWM_CVAL3CYC_CVAL3CYC_MASK               (0xFU)
#define PWM_CVAL3CYC_CVAL3CYC_SHIFT              (0U)
#define PWM_CVAL3CYC_CVAL3CYC(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_CVAL3CYC_CVAL3CYC_SHIFT)) & PWM_CVAL3CYC_CVAL3CYC_MASK)

/* The count of PWM_CVAL3CYC */
#define PWM_CVAL3CYC_COUNT                       (4U)

/*! @name CVAL4 - Capture Value 4 Register */
#define PWM_CVAL4_CAPTVAL4_MASK                  (0xFFFFU)
#define PWM_CVAL4_CAPTVAL4_SHIFT                 (0U)
#define PWM_CVAL4_CAPTVAL4(x)                    (((uint16_t)(((uint16_t)(x)) << PWM_CVAL4_CAPTVAL4_SHIFT)) & PWM_CVAL4_CAPTVAL4_MASK)

/* The count of PWM_CVAL4 */
#define PWM_CVAL4_COUNT                          (4U)

/*! @name CVAL4CYC - Capture Value 4 Cycle Register */
#define PWM_CVAL4CYC_CVAL4CYC_MASK               (0xFU)
#define PWM_CVAL4CYC_CVAL4CYC_SHIFT              (0U)
#define PWM_CVAL4CYC_CVAL4CYC(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_CVAL4CYC_CVAL4CYC_SHIFT)) & PWM_CVAL4CYC_CVAL4CYC_MASK)

/* The count of PWM_CVAL4CYC */
#define PWM_CVAL4CYC_COUNT                       (4U)

/*! @name CVAL5 - Capture Value 5 Register */
#define PWM_CVAL5_CAPTVAL5_MASK                  (0xFFFFU)
#define PWM_CVAL5_CAPTVAL5_SHIFT                 (0U)
#define PWM_CVAL5_CAPTVAL5(x)                    (((uint16_t)(((uint16_t)(x)) << PWM_CVAL5_CAPTVAL5_SHIFT)) & PWM_CVAL5_CAPTVAL5_MASK)

/* The count of PWM_CVAL5 */
#define PWM_CVAL5_COUNT                          (4U)

/*! @name CVAL5CYC - Capture Value 5 Cycle Register */
#define PWM_CVAL5CYC_CVAL5CYC_MASK               (0xFU)
#define PWM_CVAL5CYC_CVAL5CYC_SHIFT              (0U)
#define PWM_CVAL5CYC_CVAL5CYC(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_CVAL5CYC_CVAL5CYC_SHIFT)) & PWM_CVAL5CYC_CVAL5CYC_MASK)

/* The count of PWM_CVAL5CYC */
#define PWM_CVAL5CYC_COUNT                       (4U)

/*! @name OUTEN - Output Enable Register */
#define PWM_OUTEN_PWMX_EN_MASK                   (0xFU)
#define PWM_OUTEN_PWMX_EN_SHIFT                  (0U)
#define PWM_OUTEN_PWMX_EN(x)                     (((uint16_t)(((uint16_t)(x)) << PWM_OUTEN_PWMX_EN_SHIFT)) & PWM_OUTEN_PWMX_EN_MASK)
#define PWM_OUTEN_PWMB_EN_MASK                   (0xF0U)
#define PWM_OUTEN_PWMB_EN_SHIFT                  (4U)
#define PWM_OUTEN_PWMB_EN(x)                     (((uint16_t)(((uint16_t)(x)) << PWM_OUTEN_PWMB_EN_SHIFT)) & PWM_OUTEN_PWMB_EN_MASK)
#define PWM_OUTEN_PWMA_EN_MASK                   (0xF00U)
#define PWM_OUTEN_PWMA_EN_SHIFT                  (8U)
#define PWM_OUTEN_PWMA_EN(x)                     (((uint16_t)(((uint16_t)(x)) << PWM_OUTEN_PWMA_EN_SHIFT)) & PWM_OUTEN_PWMA_EN_MASK)

/*! @name MASK - Mask Register */
#define PWM_MASK_MASKX_MASK                      (0xFU)
#define PWM_MASK_MASKX_SHIFT                     (0U)
#define PWM_MASK_MASKX(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_MASK_MASKX_SHIFT)) & PWM_MASK_MASKX_MASK)
#define PWM_MASK_MASKB_MASK                      (0xF0U)
#define PWM_MASK_MASKB_SHIFT                     (4U)
#define PWM_MASK_MASKB(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_MASK_MASKB_SHIFT)) & PWM_MASK_MASKB_MASK)
#define PWM_MASK_MASKA_MASK                      (0xF00U)
#define PWM_MASK_MASKA_SHIFT                     (8U)
#define PWM_MASK_MASKA(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_MASK_MASKA_SHIFT)) & PWM_MASK_MASKA_MASK)
#define PWM_MASK_UPDATE_MASK_MASK                (0xF000U)
#define PWM_MASK_UPDATE_MASK_SHIFT               (12U)
#define PWM_MASK_UPDATE_MASK(x)                  (((uint16_t)(((uint16_t)(x)) << PWM_MASK_UPDATE_MASK_SHIFT)) & PWM_MASK_UPDATE_MASK_MASK)

/*! @name SWCOUT - Software Controlled Output Register */
#define PWM_SWCOUT_SM0OUT45_MASK                 (0x1U)
#define PWM_SWCOUT_SM0OUT45_SHIFT                (0U)
#define PWM_SWCOUT_SM0OUT45(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_SWCOUT_SM0OUT45_SHIFT)) & PWM_SWCOUT_SM0OUT45_MASK)
#define PWM_SWCOUT_SM0OUT23_MASK                 (0x2U)
#define PWM_SWCOUT_SM0OUT23_SHIFT                (1U)
#define PWM_SWCOUT_SM0OUT23(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_SWCOUT_SM0OUT23_SHIFT)) & PWM_SWCOUT_SM0OUT23_MASK)
#define PWM_SWCOUT_SM1OUT45_MASK                 (0x4U)
#define PWM_SWCOUT_SM1OUT45_SHIFT                (2U)
#define PWM_SWCOUT_SM1OUT45(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_SWCOUT_SM1OUT45_SHIFT)) & PWM_SWCOUT_SM1OUT45_MASK)
#define PWM_SWCOUT_SM1OUT23_MASK                 (0x8U)
#define PWM_SWCOUT_SM1OUT23_SHIFT                (3U)
#define PWM_SWCOUT_SM1OUT23(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_SWCOUT_SM1OUT23_SHIFT)) & PWM_SWCOUT_SM1OUT23_MASK)
#define PWM_SWCOUT_SM2OUT45_MASK                 (0x10U)
#define PWM_SWCOUT_SM2OUT45_SHIFT                (4U)
#define PWM_SWCOUT_SM2OUT45(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_SWCOUT_SM2OUT45_SHIFT)) & PWM_SWCOUT_SM2OUT45_MASK)
#define PWM_SWCOUT_SM2OUT23_MASK                 (0x20U)
#define PWM_SWCOUT_SM2OUT23_SHIFT                (5U)
#define PWM_SWCOUT_SM2OUT23(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_SWCOUT_SM2OUT23_SHIFT)) & PWM_SWCOUT_SM2OUT23_MASK)
#define PWM_SWCOUT_SM3OUT45_MASK                 (0x40U)
#define PWM_SWCOUT_SM3OUT45_SHIFT                (6U)
#define PWM_SWCOUT_SM3OUT45(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_SWCOUT_SM3OUT45_SHIFT)) & PWM_SWCOUT_SM3OUT45_MASK)
#define PWM_SWCOUT_SM3OUT23_MASK                 (0x80U)
#define PWM_SWCOUT_SM3OUT23_SHIFT                (7U)
#define PWM_SWCOUT_SM3OUT23(x)                   (((uint16_t)(((uint16_t)(x)) << PWM_SWCOUT_SM3OUT23_SHIFT)) & PWM_SWCOUT_SM3OUT23_MASK)

/*! @name DTSRCSEL - PWM Source Select Register */
#define PWM_DTSRCSEL_SM0SEL45_MASK               (0x3U)
#define PWM_DTSRCSEL_SM0SEL45_SHIFT              (0U)
#define PWM_DTSRCSEL_SM0SEL45(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_DTSRCSEL_SM0SEL45_SHIFT)) & PWM_DTSRCSEL_SM0SEL45_MASK)
#define PWM_DTSRCSEL_SM0SEL23_MASK               (0xCU)
#define PWM_DTSRCSEL_SM0SEL23_SHIFT              (2U)
#define PWM_DTSRCSEL_SM0SEL23(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_DTSRCSEL_SM0SEL23_SHIFT)) & PWM_DTSRCSEL_SM0SEL23_MASK)
#define PWM_DTSRCSEL_SM1SEL45_MASK               (0x30U)
#define PWM_DTSRCSEL_SM1SEL45_SHIFT              (4U)
#define PWM_DTSRCSEL_SM1SEL45(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_DTSRCSEL_SM1SEL45_SHIFT)) & PWM_DTSRCSEL_SM1SEL45_MASK)
#define PWM_DTSRCSEL_SM1SEL23_MASK               (0xC0U)
#define PWM_DTSRCSEL_SM1SEL23_SHIFT              (6U)
#define PWM_DTSRCSEL_SM1SEL23(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_DTSRCSEL_SM1SEL23_SHIFT)) & PWM_DTSRCSEL_SM1SEL23_MASK)
#define PWM_DTSRCSEL_SM2SEL45_MASK               (0x300U)
#define PWM_DTSRCSEL_SM2SEL45_SHIFT              (8U)
#define PWM_DTSRCSEL_SM2SEL45(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_DTSRCSEL_SM2SEL45_SHIFT)) & PWM_DTSRCSEL_SM2SEL45_MASK)
#define PWM_DTSRCSEL_SM2SEL23_MASK               (0xC00U)
#define PWM_DTSRCSEL_SM2SEL23_SHIFT              (10U)
#define PWM_DTSRCSEL_SM2SEL23(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_DTSRCSEL_SM2SEL23_SHIFT)) & PWM_DTSRCSEL_SM2SEL23_MASK)
#define PWM_DTSRCSEL_SM3SEL45_MASK               (0x3000U)
#define PWM_DTSRCSEL_SM3SEL45_SHIFT              (12U)
#define PWM_DTSRCSEL_SM3SEL45(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_DTSRCSEL_SM3SEL45_SHIFT)) & PWM_DTSRCSEL_SM3SEL45_MASK)
#define PWM_DTSRCSEL_SM3SEL23_MASK               (0xC000U)
#define PWM_DTSRCSEL_SM3SEL23_SHIFT              (14U)
#define PWM_DTSRCSEL_SM3SEL23(x)                 (((uint16_t)(((uint16_t)(x)) << PWM_DTSRCSEL_SM3SEL23_SHIFT)) & PWM_DTSRCSEL_SM3SEL23_MASK)

/*! @name MCTRL - Master Control Register 0 */
#define PWM_MCTRL_LDOK_MASK                      (0xFU)
#define PWM_MCTRL_LDOK_SHIFT                     (0U)
#define PWM_MCTRL_LDOK(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_MCTRL_LDOK_SHIFT)) & PWM_MCTRL_LDOK_MASK)
#define PWM_MCTRL_CLDOK_MASK                     (0xF0U)
#define PWM_MCTRL_CLDOK_SHIFT                    (4U)
#define PWM_MCTRL_CLDOK(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_MCTRL_CLDOK_SHIFT)) & PWM_MCTRL_CLDOK_MASK)
#define PWM_MCTRL_RUN_MASK                       (0xF00U)
#define PWM_MCTRL_RUN_SHIFT                      (8U)
#define PWM_MCTRL_RUN(x)                         (((uint16_t)(((uint16_t)(x)) << PWM_MCTRL_RUN_SHIFT)) & PWM_MCTRL_RUN_MASK)
#define PWM_MCTRL_IPOL_MASK                      (0xF000U)
#define PWM_MCTRL_IPOL_SHIFT                     (12U)
#define PWM_MCTRL_IPOL(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_MCTRL_IPOL_SHIFT)) & PWM_MCTRL_IPOL_MASK)

/*! @name MCTRL2 - Master Control Register 1 */
#define PWM_MCTRL2_MONPLL_MASK                   (0x3U)
#define PWM_MCTRL2_MONPLL_SHIFT                  (0U)
#define PWM_MCTRL2_MONPLL(x)                     (((uint16_t)(((uint16_t)(x)) << PWM_MCTRL2_MONPLL_SHIFT)) & PWM_MCTRL2_MONPLL_MASK)

/*! @name FCTRL - Fault Control Register */
#define PWM_FCTRL_FIE_MASK                       (0xFU)
#define PWM_FCTRL_FIE_SHIFT                      (0U)
#define PWM_FCTRL_FIE(x)                         (((uint16_t)(((uint16_t)(x)) << PWM_FCTRL_FIE_SHIFT)) & PWM_FCTRL_FIE_MASK)
#define PWM_FCTRL_FSAFE_MASK                     (0xF0U)
#define PWM_FCTRL_FSAFE_SHIFT                    (4U)
#define PWM_FCTRL_FSAFE(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_FCTRL_FSAFE_SHIFT)) & PWM_FCTRL_FSAFE_MASK)
#define PWM_FCTRL_FAUTO_MASK                     (0xF00U)
#define PWM_FCTRL_FAUTO_SHIFT                    (8U)
#define PWM_FCTRL_FAUTO(x)                       (((uint16_t)(((uint16_t)(x)) << PWM_FCTRL_FAUTO_SHIFT)) & PWM_FCTRL_FAUTO_MASK)
#define PWM_FCTRL_FLVL_MASK                      (0xF000U)
#define PWM_FCTRL_FLVL_SHIFT                     (12U)
#define PWM_FCTRL_FLVL(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_FCTRL_FLVL_SHIFT)) & PWM_FCTRL_FLVL_MASK)

/*! @name FSTS - Fault Status Register */
#define PWM_FSTS_FFLAG_MASK                      (0xFU)
#define PWM_FSTS_FFLAG_SHIFT                     (0U)
#define PWM_FSTS_FFLAG(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_FSTS_FFLAG_SHIFT)) & PWM_FSTS_FFLAG_MASK)
#define PWM_FSTS_FFULL_MASK                      (0xF0U)
#define PWM_FSTS_FFULL_SHIFT                     (4U)
#define PWM_FSTS_FFULL(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_FSTS_FFULL_SHIFT)) & PWM_FSTS_FFULL_MASK)
#define PWM_FSTS_FFPIN_MASK                      (0xF00U)
#define PWM_FSTS_FFPIN_SHIFT                     (8U)
#define PWM_FSTS_FFPIN(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_FSTS_FFPIN_SHIFT)) & PWM_FSTS_FFPIN_MASK)
#define PWM_FSTS_FHALF_MASK                      (0xF000U)
#define PWM_FSTS_FHALF_SHIFT                     (12U)
#define PWM_FSTS_FHALF(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_FSTS_FHALF_SHIFT)) & PWM_FSTS_FHALF_MASK)

/*! @name FFILT - Fault Filter Register */
#define PWM_FFILT_FILT_PER_MASK                  (0xFFU)
#define PWM_FFILT_FILT_PER_SHIFT                 (0U)
#define PWM_FFILT_FILT_PER(x)                    (((uint16_t)(((uint16_t)(x)) << PWM_FFILT_FILT_PER_SHIFT)) & PWM_FFILT_FILT_PER_MASK)
#define PWM_FFILT_FILT_CNT_MASK                  (0x700U)
#define PWM_FFILT_FILT_CNT_SHIFT                 (8U)
#define PWM_FFILT_FILT_CNT(x)                    (((uint16_t)(((uint16_t)(x)) << PWM_FFILT_FILT_CNT_SHIFT)) & PWM_FFILT_FILT_CNT_MASK)
#define PWM_FFILT_GSTR_MASK                      (0x8000U)
#define PWM_FFILT_GSTR_SHIFT                     (15U)
#define PWM_FFILT_GSTR(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_FFILT_GSTR_SHIFT)) & PWM_FFILT_GSTR_MASK)

/*! @name FTST - Fault Test Register */
#define PWM_FTST_FTEST_MASK                      (0x1U)
#define PWM_FTST_FTEST_SHIFT                     (0U)
#define PWM_FTST_FTEST(x)                        (((uint16_t)(((uint16_t)(x)) << PWM_FTST_FTEST_SHIFT)) & PWM_FTST_FTEST_MASK)

/*! @name FCTRL2 - Fault Control 2 Register */
#define PWM_FCTRL2_NOCOMB_MASK                   (0xFU)
#define PWM_FCTRL2_NOCOMB_SHIFT                  (0U)
#define PWM_FCTRL2_NOCOMB(x)                     (((uint16_t)(((uint16_t)(x)) << PWM_FCTRL2_NOCOMB_SHIFT)) & PWM_FCTRL2_NOCOMB_MASK)


/*!
 * @}
 */ /* end of group PWM_Register_Masks */


/* PWM - Peripheral instance base addresses */
/** Peripheral PWM0 base address */
#define PWM0_BASE                                (0x40033000u)
/** Peripheral PWM0 base pointer */
#define PWM0                                     ((PWM_Type *)PWM0_BASE)
/** Peripheral PWM1 base address */
#define PWM1_BASE                                (0x400B3000u)
/** Peripheral PWM1 base pointer */
#define PWM1                                     ((PWM_Type *)PWM1_BASE)
/** Array initializer of PWM peripheral base addresses */
#define PWM_BASE_ADDRS                           { PWM0_BASE, PWM1_BASE }
/** Array initializer of PWM peripheral base pointers */
#define PWM_BASE_PTRS                            { PWM0, PWM1 }
/** Interrupt vectors for the PWM peripheral type */
#define PWM_CMP_IRQS                             { { PWM0_CMP0_IRQn, PWM0_CMP1_IRQn, PWM0_CMP2_IRQn, PWM0_CMP3_IRQn }, { PWM1_CMP0_IRQn, PWM1_CMP1_IRQn, PWM1_CMP2_IRQn, PWM1_CMP3_IRQn } }
#define PWM_RELOAD_IRQS                          { { PWM0_RELOAD0_IRQn, PWM0_RELOAD1_IRQn, PWM0_RELOAD2_IRQn, PWM0_RELOAD3_IRQn }, { PWM1_RELOAD0_IRQn, PWM1_RELOAD1_IRQn, PWM1_RELOAD2_IRQn, PWM1_RELOAD3_IRQn } }
#define PWM_CAP_IRQS                             { PWM0_CAP_IRQn, PWM1_CAP_IRQn }
#define PWM_RERR_IRQS                            { PWM0_RERR_IRQn, PWM1_RERR_IRQn }
#define PWM_FAULT_IRQS                           { PWM0_FAULT_IRQn, PWM1_FAULT_IRQn }

/*!
 * @}
 */ /* end of group PWM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- RCM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RCM_Peripheral_Access_Layer RCM Peripheral Access Layer
 * @{
 */

/** RCM - Register Layout Typedef */
typedef struct {
  __I  uint8_t SRS0;                               /**< System Reset Status Register 0, offset: 0x0 */
  __I  uint8_t SRS1;                               /**< System Reset Status Register 1, offset: 0x1 */
       uint8_t RESERVED_0[2];
  __IO uint8_t RPFC;                               /**< Reset Pin Filter Control register, offset: 0x4 */
  __IO uint8_t RPFW;                               /**< Reset Pin Filter Width register, offset: 0x5 */
       uint8_t RESERVED_1[2];
  __IO uint8_t SSRS0;                              /**< Sticky System Reset Status Register 0, offset: 0x8 */
  __IO uint8_t SSRS1;                              /**< Sticky System Reset Status Register 1, offset: 0x9 */
} RCM_Type;

/* ----------------------------------------------------------------------------
   -- RCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RCM_Register_Masks RCM Register Masks
 * @{
 */

/*! @name SRS0 - System Reset Status Register 0 */
#define RCM_SRS0_WAKEUP_MASK                     (0x1U)
#define RCM_SRS0_WAKEUP_SHIFT                    (0U)
#define RCM_SRS0_WAKEUP(x)                       (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_WAKEUP_SHIFT)) & RCM_SRS0_WAKEUP_MASK)
#define RCM_SRS0_LVD_MASK                        (0x2U)
#define RCM_SRS0_LVD_SHIFT                       (1U)
#define RCM_SRS0_LVD(x)                          (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_LVD_SHIFT)) & RCM_SRS0_LVD_MASK)
#define RCM_SRS0_LOC_MASK                        (0x4U)
#define RCM_SRS0_LOC_SHIFT                       (2U)
#define RCM_SRS0_LOC(x)                          (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_LOC_SHIFT)) & RCM_SRS0_LOC_MASK)
#define RCM_SRS0_LOL_MASK                        (0x8U)
#define RCM_SRS0_LOL_SHIFT                       (3U)
#define RCM_SRS0_LOL(x)                          (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_LOL_SHIFT)) & RCM_SRS0_LOL_MASK)
#define RCM_SRS0_WDOG_MASK                       (0x20U)
#define RCM_SRS0_WDOG_SHIFT                      (5U)
#define RCM_SRS0_WDOG(x)                         (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_WDOG_SHIFT)) & RCM_SRS0_WDOG_MASK)
#define RCM_SRS0_PIN_MASK                        (0x40U)
#define RCM_SRS0_PIN_SHIFT                       (6U)
#define RCM_SRS0_PIN(x)                          (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_PIN_SHIFT)) & RCM_SRS0_PIN_MASK)
#define RCM_SRS0_POR_MASK                        (0x80U)
#define RCM_SRS0_POR_SHIFT                       (7U)
#define RCM_SRS0_POR(x)                          (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_POR_SHIFT)) & RCM_SRS0_POR_MASK)

/*! @name SRS1 - System Reset Status Register 1 */
#define RCM_SRS1_JTAG_MASK                       (0x1U)
#define RCM_SRS1_JTAG_SHIFT                      (0U)
#define RCM_SRS1_JTAG(x)                         (((uint8_t)(((uint8_t)(x)) << RCM_SRS1_JTAG_SHIFT)) & RCM_SRS1_JTAG_MASK)
#define RCM_SRS1_LOCKUP_MASK                     (0x2U)
#define RCM_SRS1_LOCKUP_SHIFT                    (1U)
#define RCM_SRS1_LOCKUP(x)                       (((uint8_t)(((uint8_t)(x)) << RCM_SRS1_LOCKUP_SHIFT)) & RCM_SRS1_LOCKUP_MASK)
#define RCM_SRS1_SW_MASK                         (0x4U)
#define RCM_SRS1_SW_SHIFT                        (2U)
#define RCM_SRS1_SW(x)                           (((uint8_t)(((uint8_t)(x)) << RCM_SRS1_SW_SHIFT)) & RCM_SRS1_SW_MASK)
#define RCM_SRS1_MDM_AP_MASK                     (0x8U)
#define RCM_SRS1_MDM_AP_SHIFT                    (3U)
#define RCM_SRS1_MDM_AP(x)                       (((uint8_t)(((uint8_t)(x)) << RCM_SRS1_MDM_AP_SHIFT)) & RCM_SRS1_MDM_AP_MASK)
#define RCM_SRS1_SACKERR_MASK                    (0x20U)
#define RCM_SRS1_SACKERR_SHIFT                   (5U)
#define RCM_SRS1_SACKERR(x)                      (((uint8_t)(((uint8_t)(x)) << RCM_SRS1_SACKERR_SHIFT)) & RCM_SRS1_SACKERR_MASK)

/*! @name RPFC - Reset Pin Filter Control register */
#define RCM_RPFC_RSTFLTSRW_MASK                  (0x3U)
#define RCM_RPFC_RSTFLTSRW_SHIFT                 (0U)
#define RCM_RPFC_RSTFLTSRW(x)                    (((uint8_t)(((uint8_t)(x)) << RCM_RPFC_RSTFLTSRW_SHIFT)) & RCM_RPFC_RSTFLTSRW_MASK)
#define RCM_RPFC_RSTFLTSS_MASK                   (0x4U)
#define RCM_RPFC_RSTFLTSS_SHIFT                  (2U)
#define RCM_RPFC_RSTFLTSS(x)                     (((uint8_t)(((uint8_t)(x)) << RCM_RPFC_RSTFLTSS_SHIFT)) & RCM_RPFC_RSTFLTSS_MASK)

/*! @name RPFW - Reset Pin Filter Width register */
#define RCM_RPFW_RSTFLTSEL_MASK                  (0x1FU)
#define RCM_RPFW_RSTFLTSEL_SHIFT                 (0U)
#define RCM_RPFW_RSTFLTSEL(x)                    (((uint8_t)(((uint8_t)(x)) << RCM_RPFW_RSTFLTSEL_SHIFT)) & RCM_RPFW_RSTFLTSEL_MASK)

/*! @name SSRS0 - Sticky System Reset Status Register 0 */
#define RCM_SSRS0_SWAKEUP_MASK                   (0x1U)
#define RCM_SSRS0_SWAKEUP_SHIFT                  (0U)
#define RCM_SSRS0_SWAKEUP(x)                     (((uint8_t)(((uint8_t)(x)) << RCM_SSRS0_SWAKEUP_SHIFT)) & RCM_SSRS0_SWAKEUP_MASK)
#define RCM_SSRS0_SLVD_MASK                      (0x2U)
#define RCM_SSRS0_SLVD_SHIFT                     (1U)
#define RCM_SSRS0_SLVD(x)                        (((uint8_t)(((uint8_t)(x)) << RCM_SSRS0_SLVD_SHIFT)) & RCM_SSRS0_SLVD_MASK)
#define RCM_SSRS0_SLOC_MASK                      (0x4U)
#define RCM_SSRS0_SLOC_SHIFT                     (2U)
#define RCM_SSRS0_SLOC(x)                        (((uint8_t)(((uint8_t)(x)) << RCM_SSRS0_SLOC_SHIFT)) & RCM_SSRS0_SLOC_MASK)
#define RCM_SSRS0_SLOL_MASK                      (0x8U)
#define RCM_SSRS0_SLOL_SHIFT                     (3U)
#define RCM_SSRS0_SLOL(x)                        (((uint8_t)(((uint8_t)(x)) << RCM_SSRS0_SLOL_SHIFT)) & RCM_SSRS0_SLOL_MASK)
#define RCM_SSRS0_SWDOG_MASK                     (0x20U)
#define RCM_SSRS0_SWDOG_SHIFT                    (5U)
#define RCM_SSRS0_SWDOG(x)                       (((uint8_t)(((uint8_t)(x)) << RCM_SSRS0_SWDOG_SHIFT)) & RCM_SSRS0_SWDOG_MASK)
#define RCM_SSRS0_SPIN_MASK                      (0x40U)
#define RCM_SSRS0_SPIN_SHIFT                     (6U)
#define RCM_SSRS0_SPIN(x)                        (((uint8_t)(((uint8_t)(x)) << RCM_SSRS0_SPIN_SHIFT)) & RCM_SSRS0_SPIN_MASK)
#define RCM_SSRS0_SPOR_MASK                      (0x80U)
#define RCM_SSRS0_SPOR_SHIFT                     (7U)
#define RCM_SSRS0_SPOR(x)                        (((uint8_t)(((uint8_t)(x)) << RCM_SSRS0_SPOR_SHIFT)) & RCM_SSRS0_SPOR_MASK)

/*! @name SSRS1 - Sticky System Reset Status Register 1 */
#define RCM_SSRS1_SJTAG_MASK                     (0x1U)
#define RCM_SSRS1_SJTAG_SHIFT                    (0U)
#define RCM_SSRS1_SJTAG(x)                       (((uint8_t)(((uint8_t)(x)) << RCM_SSRS1_SJTAG_SHIFT)) & RCM_SSRS1_SJTAG_MASK)
#define RCM_SSRS1_SLOCKUP_MASK                   (0x2U)
#define RCM_SSRS1_SLOCKUP_SHIFT                  (1U)
#define RCM_SSRS1_SLOCKUP(x)                     (((uint8_t)(((uint8_t)(x)) << RCM_SSRS1_SLOCKUP_SHIFT)) & RCM_SSRS1_SLOCKUP_MASK)
#define RCM_SSRS1_SSW_MASK                       (0x4U)
#define RCM_SSRS1_SSW_SHIFT                      (2U)
#define RCM_SSRS1_SSW(x)                         (((uint8_t)(((uint8_t)(x)) << RCM_SSRS1_SSW_SHIFT)) & RCM_SSRS1_SSW_MASK)
#define RCM_SSRS1_SMDM_AP_MASK                   (0x8U)
#define RCM_SSRS1_SMDM_AP_SHIFT                  (3U)
#define RCM_SSRS1_SMDM_AP(x)                     (((uint8_t)(((uint8_t)(x)) << RCM_SSRS1_SMDM_AP_SHIFT)) & RCM_SSRS1_SMDM_AP_MASK)
#define RCM_SSRS1_SSACKERR_MASK                  (0x20U)
#define RCM_SSRS1_SSACKERR_SHIFT                 (5U)
#define RCM_SSRS1_SSACKERR(x)                    (((uint8_t)(((uint8_t)(x)) << RCM_SSRS1_SSACKERR_SHIFT)) & RCM_SSRS1_SSACKERR_MASK)


/*!
 * @}
 */ /* end of group RCM_Register_Masks */


/* RCM - Peripheral instance base addresses */
/** Peripheral RCM base address */
#define RCM_BASE                                 (0x4007F000u)
/** Peripheral RCM base pointer */
#define RCM                                      ((RCM_Type *)RCM_BASE)
/** Array initializer of RCM peripheral base addresses */
#define RCM_BASE_ADDRS                           { RCM_BASE }
/** Array initializer of RCM peripheral base pointers */
#define RCM_BASE_PTRS                            { RCM }

/*!
 * @}
 */ /* end of group RCM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- RFSYS Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RFSYS_Peripheral_Access_Layer RFSYS Peripheral Access Layer
 * @{
 */

/** RFSYS - Register Layout Typedef */
typedef struct {
  __IO uint32_t REG[8];                            /**< Register file register, array offset: 0x0, array step: 0x4 */
} RFSYS_Type;

/* ----------------------------------------------------------------------------
   -- RFSYS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RFSYS_Register_Masks RFSYS Register Masks
 * @{
 */

/*! @name REG - Register file register */
#define RFSYS_REG_LL_MASK                        (0xFFU)
#define RFSYS_REG_LL_SHIFT                       (0U)
#define RFSYS_REG_LL(x)                          (((uint32_t)(((uint32_t)(x)) << RFSYS_REG_LL_SHIFT)) & RFSYS_REG_LL_MASK)
#define RFSYS_REG_LH_MASK                        (0xFF00U)
#define RFSYS_REG_LH_SHIFT                       (8U)
#define RFSYS_REG_LH(x)                          (((uint32_t)(((uint32_t)(x)) << RFSYS_REG_LH_SHIFT)) & RFSYS_REG_LH_MASK)
#define RFSYS_REG_HL_MASK                        (0xFF0000U)
#define RFSYS_REG_HL_SHIFT                       (16U)
#define RFSYS_REG_HL(x)                          (((uint32_t)(((uint32_t)(x)) << RFSYS_REG_HL_SHIFT)) & RFSYS_REG_HL_MASK)
#define RFSYS_REG_HH_MASK                        (0xFF000000U)
#define RFSYS_REG_HH_SHIFT                       (24U)
#define RFSYS_REG_HH(x)                          (((uint32_t)(((uint32_t)(x)) << RFSYS_REG_HH_SHIFT)) & RFSYS_REG_HH_MASK)

/* The count of RFSYS_REG */
#define RFSYS_REG_COUNT                          (8U)


/*!
 * @}
 */ /* end of group RFSYS_Register_Masks */


/* RFSYS - Peripheral instance base addresses */
/** Peripheral RFSYS base address */
#define RFSYS_BASE                               (0x40041000u)
/** Peripheral RFSYS base pointer */
#define RFSYS                                    ((RFSYS_Type *)RFSYS_BASE)
/** Array initializer of RFSYS peripheral base addresses */
#define RFSYS_BASE_ADDRS                         { RFSYS_BASE }
/** Array initializer of RFSYS peripheral base pointers */
#define RFSYS_BASE_PTRS                          { RFSYS }

/*!
 * @}
 */ /* end of group RFSYS_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- RFVBAT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RFVBAT_Peripheral_Access_Layer RFVBAT Peripheral Access Layer
 * @{
 */

/** RFVBAT - Register Layout Typedef */
typedef struct {
  __IO uint32_t REG[8];                            /**< VBAT register file register, array offset: 0x0, array step: 0x4 */
} RFVBAT_Type;

/* ----------------------------------------------------------------------------
   -- RFVBAT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RFVBAT_Register_Masks RFVBAT Register Masks
 * @{
 */

/*! @name REG - VBAT register file register */
#define RFVBAT_REG_LL_MASK                       (0xFFU)
#define RFVBAT_REG_LL_SHIFT                      (0U)
#define RFVBAT_REG_LL(x)                         (((uint32_t)(((uint32_t)(x)) << RFVBAT_REG_LL_SHIFT)) & RFVBAT_REG_LL_MASK)
#define RFVBAT_REG_LH_MASK                       (0xFF00U)
#define RFVBAT_REG_LH_SHIFT                      (8U)
#define RFVBAT_REG_LH(x)                         (((uint32_t)(((uint32_t)(x)) << RFVBAT_REG_LH_SHIFT)) & RFVBAT_REG_LH_MASK)
#define RFVBAT_REG_HL_MASK                       (0xFF0000U)
#define RFVBAT_REG_HL_SHIFT                      (16U)
#define RFVBAT_REG_HL(x)                         (((uint32_t)(((uint32_t)(x)) << RFVBAT_REG_HL_SHIFT)) & RFVBAT_REG_HL_MASK)
#define RFVBAT_REG_HH_MASK                       (0xFF000000U)
#define RFVBAT_REG_HH_SHIFT                      (24U)
#define RFVBAT_REG_HH(x)                         (((uint32_t)(((uint32_t)(x)) << RFVBAT_REG_HH_SHIFT)) & RFVBAT_REG_HH_MASK)

/* The count of RFVBAT_REG */
#define RFVBAT_REG_COUNT                         (8U)


/*!
 * @}
 */ /* end of group RFVBAT_Register_Masks */


/* RFVBAT - Peripheral instance base addresses */
/** Peripheral RFVBAT base address */
#define RFVBAT_BASE                              (0x4003E000u)
/** Peripheral RFVBAT base pointer */
#define RFVBAT                                   ((RFVBAT_Type *)RFVBAT_BASE)
/** Array initializer of RFVBAT peripheral base addresses */
#define RFVBAT_BASE_ADDRS                        { RFVBAT_BASE }
/** Array initializer of RFVBAT peripheral base pointers */
#define RFVBAT_BASE_PTRS                         { RFVBAT }

/*!
 * @}
 */ /* end of group RFVBAT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SIM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Peripheral_Access_Layer SIM Peripheral Access Layer
 * @{
 */

/** SIM - Register Layout Typedef */
typedef struct {
  __IO uint32_t SOPT1;                             /**< System Options Register 1, offset: 0x0 */
       uint8_t RESERVED_0[4096];
  __IO uint32_t SOPT2;                             /**< System Options Register 2, offset: 0x1004 */
       uint8_t RESERVED_1[4];
  __IO uint32_t SOPT4;                             /**< System Options Register 4, offset: 0x100C */
  __IO uint32_t SOPT5;                             /**< System Options Register 5, offset: 0x1010 */
       uint8_t RESERVED_2[4];
  __IO uint32_t SOPT7;                             /**< System Options Register 7, offset: 0x1018 */
  __IO uint32_t SOPT8;                             /**< System Options Register 8, offset: 0x101C */
  __IO uint32_t SOPT9;                             /**< System Options Register 9, offset: 0x1020 */
  __I  uint32_t SDID;                              /**< System Device Identification Register, offset: 0x1024 */
  __IO uint32_t SCGC1;                             /**< System Clock Gating Control Register 1, offset: 0x1028 */
  __IO uint32_t SCGC2;                             /**< System Clock Gating Control Register 2, offset: 0x102C */
  __IO uint32_t SCGC3;                             /**< System Clock Gating Control Register 3, offset: 0x1030 */
  __IO uint32_t SCGC4;                             /**< System Clock Gating Control Register 4, offset: 0x1034 */
  __IO uint32_t SCGC5;                             /**< System Clock Gating Control Register 5, offset: 0x1038 */
  __IO uint32_t SCGC6;                             /**< System Clock Gating Control Register 6, offset: 0x103C */
  __IO uint32_t SCGC7;                             /**< System Clock Gating Control Register 7, offset: 0x1040 */
  __IO uint32_t CLKDIV1;                           /**< System Clock Divider Register 1, offset: 0x1044 */
       uint8_t RESERVED_3[4];
  __IO uint32_t FCFG1;                             /**< Flash Configuration Register 1, offset: 0x104C */
  __I  uint32_t FCFG2;                             /**< Flash Configuration Register 2, offset: 0x1050 */
  __I  uint32_t UIDH;                              /**< Unique Identification Register High, offset: 0x1054 */
  __I  uint32_t UIDMH;                             /**< Unique Identification Register Mid-High, offset: 0x1058 */
  __I  uint32_t UIDML;                             /**< Unique Identification Register Mid Low, offset: 0x105C */
  __I  uint32_t UIDL;                              /**< Unique Identification Register Low, offset: 0x1060 */
       uint8_t RESERVED_4[4];
  __IO uint32_t CLKDIV4;                           /**< System Clock Divider Register 4, offset: 0x1068 */
  __IO uint32_t MISCTRL0;                          /**< Miscellaneous Control Register 0, offset: 0x106C */
  __IO uint32_t MISCTRL1;                          /**< Miscellaneous Control Register 1, offset: 0x1070 */
       uint8_t RESERVED_5[140];
  __IO uint32_t WDOGC;                             /**< WDOG Control Register, offset: 0x1100 */
  __IO uint32_t PWRC;                              /**< Power Control Register, offset: 0x1104 */
  __IO uint32_t ADCOPT;                            /**< ADC Additional Option Register, offset: 0x1108 */
} SIM_Type;

/* ----------------------------------------------------------------------------
   -- SIM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Masks SIM Register Masks
 * @{
 */

/*! @name SOPT1 - System Options Register 1 */
#define SIM_SOPT1_RAMSIZE_MASK                   (0xF000U)
#define SIM_SOPT1_RAMSIZE_SHIFT                  (12U)
#define SIM_SOPT1_RAMSIZE(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_RAMSIZE_SHIFT)) & SIM_SOPT1_RAMSIZE_MASK)
#define SIM_SOPT1_OSC32KSEL_MASK                 (0xC0000U)
#define SIM_SOPT1_OSC32KSEL_SHIFT                (18U)
#define SIM_SOPT1_OSC32KSEL(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_OSC32KSEL_SHIFT)) & SIM_SOPT1_OSC32KSEL_MASK)

/*! @name SOPT2 - System Options Register 2 */
#define SIM_SOPT2_CLKOUTSEL_MASK                 (0xE0U)
#define SIM_SOPT2_CLKOUTSEL_SHIFT                (5U)
#define SIM_SOPT2_CLKOUTSEL(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_SOPT2_CLKOUTSEL_SHIFT)) & SIM_SOPT2_CLKOUTSEL_MASK)
#define SIM_SOPT2_FBSL_MASK                      (0x300U)
#define SIM_SOPT2_FBSL_SHIFT                     (8U)
#define SIM_SOPT2_FBSL(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SOPT2_FBSL_SHIFT)) & SIM_SOPT2_FBSL_MASK)
#define SIM_SOPT2_TRACECLKSEL_MASK               (0x1000U)
#define SIM_SOPT2_TRACECLKSEL_SHIFT              (12U)
#define SIM_SOPT2_TRACECLKSEL(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT2_TRACECLKSEL_SHIFT)) & SIM_SOPT2_TRACECLKSEL_MASK)
#define SIM_SOPT2_PLLFLLSEL_MASK                 (0x30000U)
#define SIM_SOPT2_PLLFLLSEL_SHIFT                (16U)
#define SIM_SOPT2_PLLFLLSEL(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_SOPT2_PLLFLLSEL_SHIFT)) & SIM_SOPT2_PLLFLLSEL_MASK)
#define SIM_SOPT2_RMIISRC_MASK                   (0x80000U)
#define SIM_SOPT2_RMIISRC_SHIFT                  (19U)
#define SIM_SOPT2_RMIISRC(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SOPT2_RMIISRC_SHIFT)) & SIM_SOPT2_RMIISRC_MASK)
#define SIM_SOPT2_TIMESRC_MASK                   (0x300000U)
#define SIM_SOPT2_TIMESRC_SHIFT                  (20U)
#define SIM_SOPT2_TIMESRC(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SOPT2_TIMESRC_SHIFT)) & SIM_SOPT2_TIMESRC_MASK)

/*! @name SOPT4 - System Options Register 4 */
#define SIM_SOPT4_FTM0FLT0_MASK                  (0x1U)
#define SIM_SOPT4_FTM0FLT0_SHIFT                 (0U)
#define SIM_SOPT4_FTM0FLT0(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_FTM0FLT0_SHIFT)) & SIM_SOPT4_FTM0FLT0_MASK)
#define SIM_SOPT4_FTM0FLT1_MASK                  (0x2U)
#define SIM_SOPT4_FTM0FLT1_SHIFT                 (1U)
#define SIM_SOPT4_FTM0FLT1(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_FTM0FLT1_SHIFT)) & SIM_SOPT4_FTM0FLT1_MASK)
#define SIM_SOPT4_FTM0FLT2_MASK                  (0x4U)
#define SIM_SOPT4_FTM0FLT2_SHIFT                 (2U)
#define SIM_SOPT4_FTM0FLT2(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_FTM0FLT2_SHIFT)) & SIM_SOPT4_FTM0FLT2_MASK)
#define SIM_SOPT4_FTM0FLT3_MASK                  (0x8U)
#define SIM_SOPT4_FTM0FLT3_SHIFT                 (3U)
#define SIM_SOPT4_FTM0FLT3(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_FTM0FLT3_SHIFT)) & SIM_SOPT4_FTM0FLT3_MASK)
#define SIM_SOPT4_FTM1FLT0_MASK                  (0x10U)
#define SIM_SOPT4_FTM1FLT0_SHIFT                 (4U)
#define SIM_SOPT4_FTM1FLT0(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_FTM1FLT0_SHIFT)) & SIM_SOPT4_FTM1FLT0_MASK)
#define SIM_SOPT4_FTM2FLT0_MASK                  (0x100U)
#define SIM_SOPT4_FTM2FLT0_SHIFT                 (8U)
#define SIM_SOPT4_FTM2FLT0(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_FTM2FLT0_SHIFT)) & SIM_SOPT4_FTM2FLT0_MASK)
#define SIM_SOPT4_FTM3FLT0_MASK                  (0x1000U)
#define SIM_SOPT4_FTM3FLT0_SHIFT                 (12U)
#define SIM_SOPT4_FTM3FLT0(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_FTM3FLT0_SHIFT)) & SIM_SOPT4_FTM3FLT0_MASK)
#define SIM_SOPT4_FTM0TRG0SRC_MASK               (0x10000U)
#define SIM_SOPT4_FTM0TRG0SRC_SHIFT              (16U)
#define SIM_SOPT4_FTM0TRG0SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_FTM0TRG0SRC_SHIFT)) & SIM_SOPT4_FTM0TRG0SRC_MASK)
#define SIM_SOPT4_FTM0TRG1SRC_MASK               (0x20000U)
#define SIM_SOPT4_FTM0TRG1SRC_SHIFT              (17U)
#define SIM_SOPT4_FTM0TRG1SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_FTM0TRG1SRC_SHIFT)) & SIM_SOPT4_FTM0TRG1SRC_MASK)
#define SIM_SOPT4_FTM0TRG2SRC_MASK               (0x40000U)
#define SIM_SOPT4_FTM0TRG2SRC_SHIFT              (18U)
#define SIM_SOPT4_FTM0TRG2SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_FTM0TRG2SRC_SHIFT)) & SIM_SOPT4_FTM0TRG2SRC_MASK)
#define SIM_SOPT4_FTM1TRG0SRC_MASK               (0x100000U)
#define SIM_SOPT4_FTM1TRG0SRC_SHIFT              (20U)
#define SIM_SOPT4_FTM1TRG0SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_FTM1TRG0SRC_SHIFT)) & SIM_SOPT4_FTM1TRG0SRC_MASK)
#define SIM_SOPT4_FTM1TRG2SRC_MASK               (0x400000U)
#define SIM_SOPT4_FTM1TRG2SRC_SHIFT              (22U)
#define SIM_SOPT4_FTM1TRG2SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_FTM1TRG2SRC_SHIFT)) & SIM_SOPT4_FTM1TRG2SRC_MASK)
#define SIM_SOPT4_FTM2TRG0SRC_MASK               (0x1000000U)
#define SIM_SOPT4_FTM2TRG0SRC_SHIFT              (24U)
#define SIM_SOPT4_FTM2TRG0SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_FTM2TRG0SRC_SHIFT)) & SIM_SOPT4_FTM2TRG0SRC_MASK)
#define SIM_SOPT4_FTM2TRG2SRC_MASK               (0x4000000U)
#define SIM_SOPT4_FTM2TRG2SRC_SHIFT              (26U)
#define SIM_SOPT4_FTM2TRG2SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_FTM2TRG2SRC_SHIFT)) & SIM_SOPT4_FTM2TRG2SRC_MASK)
#define SIM_SOPT4_FTM3TRG0SRC_MASK               (0x10000000U)
#define SIM_SOPT4_FTM3TRG0SRC_SHIFT              (28U)
#define SIM_SOPT4_FTM3TRG0SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_FTM3TRG0SRC_SHIFT)) & SIM_SOPT4_FTM3TRG0SRC_MASK)
#define SIM_SOPT4_FTM3TRG1SRC_MASK               (0x20000000U)
#define SIM_SOPT4_FTM3TRG1SRC_SHIFT              (29U)
#define SIM_SOPT4_FTM3TRG1SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_FTM3TRG1SRC_SHIFT)) & SIM_SOPT4_FTM3TRG1SRC_MASK)
#define SIM_SOPT4_FTM3TRG2SRC_MASK               (0x40000000U)
#define SIM_SOPT4_FTM3TRG2SRC_SHIFT              (30U)
#define SIM_SOPT4_FTM3TRG2SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_FTM3TRG2SRC_SHIFT)) & SIM_SOPT4_FTM3TRG2SRC_MASK)

/*! @name SOPT5 - System Options Register 5 */
#define SIM_SOPT5_UART0TXSRC_MASK                (0x3U)
#define SIM_SOPT5_UART0TXSRC_SHIFT               (0U)
#define SIM_SOPT5_UART0TXSRC(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT5_UART0TXSRC_SHIFT)) & SIM_SOPT5_UART0TXSRC_MASK)
#define SIM_SOPT5_UART0RXSRC_MASK                (0xCU)
#define SIM_SOPT5_UART0RXSRC_SHIFT               (2U)
#define SIM_SOPT5_UART0RXSRC(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT5_UART0RXSRC_SHIFT)) & SIM_SOPT5_UART0RXSRC_MASK)
#define SIM_SOPT5_UART1TXSRC_MASK                (0x30U)
#define SIM_SOPT5_UART1TXSRC_SHIFT               (4U)
#define SIM_SOPT5_UART1TXSRC(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT5_UART1TXSRC_SHIFT)) & SIM_SOPT5_UART1TXSRC_MASK)
#define SIM_SOPT5_UART1RXSRC_MASK                (0xC0U)
#define SIM_SOPT5_UART1RXSRC_SHIFT               (6U)
#define SIM_SOPT5_UART1RXSRC(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT5_UART1RXSRC_SHIFT)) & SIM_SOPT5_UART1RXSRC_MASK)

/*! @name SOPT7 - System Options Register 7 */
#define SIM_SOPT7_HSADC0ATRGSEL_MASK             (0xFU)
#define SIM_SOPT7_HSADC0ATRGSEL_SHIFT            (0U)
#define SIM_SOPT7_HSADC0ATRGSEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_SOPT7_HSADC0ATRGSEL_SHIFT)) & SIM_SOPT7_HSADC0ATRGSEL_MASK)
#define SIM_SOPT7_HSADC0AALTTRGEN_MASK           (0xC0U)
#define SIM_SOPT7_HSADC0AALTTRGEN_SHIFT          (6U)
#define SIM_SOPT7_HSADC0AALTTRGEN(x)             (((uint32_t)(((uint32_t)(x)) << SIM_SOPT7_HSADC0AALTTRGEN_SHIFT)) & SIM_SOPT7_HSADC0AALTTRGEN_MASK)
#define SIM_SOPT7_HSADC0BTRGSEL_MASK             (0xF00U)
#define SIM_SOPT7_HSADC0BTRGSEL_SHIFT            (8U)
#define SIM_SOPT7_HSADC0BTRGSEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_SOPT7_HSADC0BTRGSEL_SHIFT)) & SIM_SOPT7_HSADC0BTRGSEL_MASK)
#define SIM_SOPT7_HSADC0BALTTRGEN_MASK           (0xC000U)
#define SIM_SOPT7_HSADC0BALTTRGEN_SHIFT          (14U)
#define SIM_SOPT7_HSADC0BALTTRGEN(x)             (((uint32_t)(((uint32_t)(x)) << SIM_SOPT7_HSADC0BALTTRGEN_SHIFT)) & SIM_SOPT7_HSADC0BALTTRGEN_MASK)
#define SIM_SOPT7_HSADC1ATRGSEL_MASK             (0xF0000U)
#define SIM_SOPT7_HSADC1ATRGSEL_SHIFT            (16U)
#define SIM_SOPT7_HSADC1ATRGSEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_SOPT7_HSADC1ATRGSEL_SHIFT)) & SIM_SOPT7_HSADC1ATRGSEL_MASK)
#define SIM_SOPT7_HSADC1AALTTRGEN_MASK           (0xC00000U)
#define SIM_SOPT7_HSADC1AALTTRGEN_SHIFT          (22U)
#define SIM_SOPT7_HSADC1AALTTRGEN(x)             (((uint32_t)(((uint32_t)(x)) << SIM_SOPT7_HSADC1AALTTRGEN_SHIFT)) & SIM_SOPT7_HSADC1AALTTRGEN_MASK)
#define SIM_SOPT7_HSADC1BTRGSEL_MASK             (0xF000000U)
#define SIM_SOPT7_HSADC1BTRGSEL_SHIFT            (24U)
#define SIM_SOPT7_HSADC1BTRGSEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_SOPT7_HSADC1BTRGSEL_SHIFT)) & SIM_SOPT7_HSADC1BTRGSEL_MASK)
#define SIM_SOPT7_HSADC1BALTTRGEN_MASK           (0xC0000000U)
#define SIM_SOPT7_HSADC1BALTTRGEN_SHIFT          (30U)
#define SIM_SOPT7_HSADC1BALTTRGEN(x)             (((uint32_t)(((uint32_t)(x)) << SIM_SOPT7_HSADC1BALTTRGEN_SHIFT)) & SIM_SOPT7_HSADC1BALTTRGEN_MASK)

/*! @name SOPT8 - System Options Register 8 */
#define SIM_SOPT8_FTM0SYNCBIT_MASK               (0x1U)
#define SIM_SOPT8_FTM0SYNCBIT_SHIFT              (0U)
#define SIM_SOPT8_FTM0SYNCBIT(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM0SYNCBIT_SHIFT)) & SIM_SOPT8_FTM0SYNCBIT_MASK)
#define SIM_SOPT8_FTM1SYNCBIT_MASK               (0x2U)
#define SIM_SOPT8_FTM1SYNCBIT_SHIFT              (1U)
#define SIM_SOPT8_FTM1SYNCBIT(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM1SYNCBIT_SHIFT)) & SIM_SOPT8_FTM1SYNCBIT_MASK)
#define SIM_SOPT8_FTM2SYNCBIT_MASK               (0x4U)
#define SIM_SOPT8_FTM2SYNCBIT_SHIFT              (2U)
#define SIM_SOPT8_FTM2SYNCBIT(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM2SYNCBIT_SHIFT)) & SIM_SOPT8_FTM2SYNCBIT_MASK)
#define SIM_SOPT8_FTM3SYNCBIT_MASK               (0x8U)
#define SIM_SOPT8_FTM3SYNCBIT_SHIFT              (3U)
#define SIM_SOPT8_FTM3SYNCBIT(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM3SYNCBIT_SHIFT)) & SIM_SOPT8_FTM3SYNCBIT_MASK)
#define SIM_SOPT8_FTM0CFSEL_MASK                 (0x100U)
#define SIM_SOPT8_FTM0CFSEL_SHIFT                (8U)
#define SIM_SOPT8_FTM0CFSEL(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM0CFSEL_SHIFT)) & SIM_SOPT8_FTM0CFSEL_MASK)
#define SIM_SOPT8_FTM3CFSEL_MASK                 (0x200U)
#define SIM_SOPT8_FTM3CFSEL_SHIFT                (9U)
#define SIM_SOPT8_FTM3CFSEL(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM3CFSEL_SHIFT)) & SIM_SOPT8_FTM3CFSEL_MASK)
#define SIM_SOPT8_FTM0OCH0SRC_MASK               (0x10000U)
#define SIM_SOPT8_FTM0OCH0SRC_SHIFT              (16U)
#define SIM_SOPT8_FTM0OCH0SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM0OCH0SRC_SHIFT)) & SIM_SOPT8_FTM0OCH0SRC_MASK)
#define SIM_SOPT8_FTM0OCH1SRC_MASK               (0x20000U)
#define SIM_SOPT8_FTM0OCH1SRC_SHIFT              (17U)
#define SIM_SOPT8_FTM0OCH1SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM0OCH1SRC_SHIFT)) & SIM_SOPT8_FTM0OCH1SRC_MASK)
#define SIM_SOPT8_FTM0OCH2SRC_MASK               (0x40000U)
#define SIM_SOPT8_FTM0OCH2SRC_SHIFT              (18U)
#define SIM_SOPT8_FTM0OCH2SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM0OCH2SRC_SHIFT)) & SIM_SOPT8_FTM0OCH2SRC_MASK)
#define SIM_SOPT8_FTM0OCH3SRC_MASK               (0x80000U)
#define SIM_SOPT8_FTM0OCH3SRC_SHIFT              (19U)
#define SIM_SOPT8_FTM0OCH3SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM0OCH3SRC_SHIFT)) & SIM_SOPT8_FTM0OCH3SRC_MASK)
#define SIM_SOPT8_FTM0OCH4SRC_MASK               (0x100000U)
#define SIM_SOPT8_FTM0OCH4SRC_SHIFT              (20U)
#define SIM_SOPT8_FTM0OCH4SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM0OCH4SRC_SHIFT)) & SIM_SOPT8_FTM0OCH4SRC_MASK)
#define SIM_SOPT8_FTM0OCH5SRC_MASK               (0x200000U)
#define SIM_SOPT8_FTM0OCH5SRC_SHIFT              (21U)
#define SIM_SOPT8_FTM0OCH5SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM0OCH5SRC_SHIFT)) & SIM_SOPT8_FTM0OCH5SRC_MASK)
#define SIM_SOPT8_FTM0OCH6SRC_MASK               (0x400000U)
#define SIM_SOPT8_FTM0OCH6SRC_SHIFT              (22U)
#define SIM_SOPT8_FTM0OCH6SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM0OCH6SRC_SHIFT)) & SIM_SOPT8_FTM0OCH6SRC_MASK)
#define SIM_SOPT8_FTM0OCH7SRC_MASK               (0x800000U)
#define SIM_SOPT8_FTM0OCH7SRC_SHIFT              (23U)
#define SIM_SOPT8_FTM0OCH7SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM0OCH7SRC_SHIFT)) & SIM_SOPT8_FTM0OCH7SRC_MASK)
#define SIM_SOPT8_FTM3OCH0SRC_MASK               (0x1000000U)
#define SIM_SOPT8_FTM3OCH0SRC_SHIFT              (24U)
#define SIM_SOPT8_FTM3OCH0SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM3OCH0SRC_SHIFT)) & SIM_SOPT8_FTM3OCH0SRC_MASK)
#define SIM_SOPT8_FTM3OCH1SRC_MASK               (0x2000000U)
#define SIM_SOPT8_FTM3OCH1SRC_SHIFT              (25U)
#define SIM_SOPT8_FTM3OCH1SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM3OCH1SRC_SHIFT)) & SIM_SOPT8_FTM3OCH1SRC_MASK)
#define SIM_SOPT8_FTM3OCH2SRC_MASK               (0x4000000U)
#define SIM_SOPT8_FTM3OCH2SRC_SHIFT              (26U)
#define SIM_SOPT8_FTM3OCH2SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM3OCH2SRC_SHIFT)) & SIM_SOPT8_FTM3OCH2SRC_MASK)
#define SIM_SOPT8_FTM3OCH3SRC_MASK               (0x8000000U)
#define SIM_SOPT8_FTM3OCH3SRC_SHIFT              (27U)
#define SIM_SOPT8_FTM3OCH3SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM3OCH3SRC_SHIFT)) & SIM_SOPT8_FTM3OCH3SRC_MASK)
#define SIM_SOPT8_FTM3OCH4SRC_MASK               (0x10000000U)
#define SIM_SOPT8_FTM3OCH4SRC_SHIFT              (28U)
#define SIM_SOPT8_FTM3OCH4SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM3OCH4SRC_SHIFT)) & SIM_SOPT8_FTM3OCH4SRC_MASK)
#define SIM_SOPT8_FTM3OCH5SRC_MASK               (0x20000000U)
#define SIM_SOPT8_FTM3OCH5SRC_SHIFT              (29U)
#define SIM_SOPT8_FTM3OCH5SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM3OCH5SRC_SHIFT)) & SIM_SOPT8_FTM3OCH5SRC_MASK)
#define SIM_SOPT8_FTM3OCH6SRC_MASK               (0x40000000U)
#define SIM_SOPT8_FTM3OCH6SRC_SHIFT              (30U)
#define SIM_SOPT8_FTM3OCH6SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM3OCH6SRC_SHIFT)) & SIM_SOPT8_FTM3OCH6SRC_MASK)
#define SIM_SOPT8_FTM3OCH7SRC_MASK               (0x80000000U)
#define SIM_SOPT8_FTM3OCH7SRC_SHIFT              (31U)
#define SIM_SOPT8_FTM3OCH7SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT8_FTM3OCH7SRC_SHIFT)) & SIM_SOPT8_FTM3OCH7SRC_MASK)

/*! @name SOPT9 - System Options Register 9 */
#define SIM_SOPT9_FTM1ICH0SRC_MASK               (0x30U)
#define SIM_SOPT9_FTM1ICH0SRC_SHIFT              (4U)
#define SIM_SOPT9_FTM1ICH0SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT9_FTM1ICH0SRC_SHIFT)) & SIM_SOPT9_FTM1ICH0SRC_MASK)
#define SIM_SOPT9_FTM1ICH1SRC_MASK               (0x40U)
#define SIM_SOPT9_FTM1ICH1SRC_SHIFT              (6U)
#define SIM_SOPT9_FTM1ICH1SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT9_FTM1ICH1SRC_SHIFT)) & SIM_SOPT9_FTM1ICH1SRC_MASK)
#define SIM_SOPT9_FTM2ICH0SRC_MASK               (0x300U)
#define SIM_SOPT9_FTM2ICH0SRC_SHIFT              (8U)
#define SIM_SOPT9_FTM2ICH0SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT9_FTM2ICH0SRC_SHIFT)) & SIM_SOPT9_FTM2ICH0SRC_MASK)
#define SIM_SOPT9_FTM2ICH1SRC_MASK               (0x400U)
#define SIM_SOPT9_FTM2ICH1SRC_SHIFT              (10U)
#define SIM_SOPT9_FTM2ICH1SRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT9_FTM2ICH1SRC_SHIFT)) & SIM_SOPT9_FTM2ICH1SRC_MASK)
#define SIM_SOPT9_FTM0CLKSEL_MASK                (0x3000000U)
#define SIM_SOPT9_FTM0CLKSEL_SHIFT               (24U)
#define SIM_SOPT9_FTM0CLKSEL(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT9_FTM0CLKSEL_SHIFT)) & SIM_SOPT9_FTM0CLKSEL_MASK)
#define SIM_SOPT9_FTM1CLKSEL_MASK                (0xC000000U)
#define SIM_SOPT9_FTM1CLKSEL_SHIFT               (26U)
#define SIM_SOPT9_FTM1CLKSEL(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT9_FTM1CLKSEL_SHIFT)) & SIM_SOPT9_FTM1CLKSEL_MASK)
#define SIM_SOPT9_FTM2CLKSEL_MASK                (0x30000000U)
#define SIM_SOPT9_FTM2CLKSEL_SHIFT               (28U)
#define SIM_SOPT9_FTM2CLKSEL(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT9_FTM2CLKSEL_SHIFT)) & SIM_SOPT9_FTM2CLKSEL_MASK)
#define SIM_SOPT9_FTM3CLKSEL_MASK                (0xC0000000U)
#define SIM_SOPT9_FTM3CLKSEL_SHIFT               (30U)
#define SIM_SOPT9_FTM3CLKSEL(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT9_FTM3CLKSEL_SHIFT)) & SIM_SOPT9_FTM3CLKSEL_MASK)

/*! @name SDID - System Device Identification Register */
#define SIM_SDID_PINID_MASK                      (0xFU)
#define SIM_SDID_PINID_SHIFT                     (0U)
#define SIM_SDID_PINID(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SDID_PINID_SHIFT)) & SIM_SDID_PINID_MASK)
#define SIM_SDID_DIEID_MASK                      (0xF80U)
#define SIM_SDID_DIEID_SHIFT                     (7U)
#define SIM_SDID_DIEID(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SDID_DIEID_SHIFT)) & SIM_SDID_DIEID_MASK)
#define SIM_SDID_REVID_MASK                      (0xF000U)
#define SIM_SDID_REVID_SHIFT                     (12U)
#define SIM_SDID_REVID(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SDID_REVID_SHIFT)) & SIM_SDID_REVID_MASK)
#define SIM_SDID_SERIESID_MASK                   (0xF00000U)
#define SIM_SDID_SERIESID_SHIFT                  (20U)
#define SIM_SDID_SERIESID(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SDID_SERIESID_SHIFT)) & SIM_SDID_SERIESID_MASK)
#define SIM_SDID_SUBFAMID_MASK                   (0xF000000U)
#define SIM_SDID_SUBFAMID_SHIFT                  (24U)
#define SIM_SDID_SUBFAMID(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SDID_SUBFAMID_SHIFT)) & SIM_SDID_SUBFAMID_MASK)
#define SIM_SDID_FAMILYID_MASK                   (0xF0000000U)
#define SIM_SDID_FAMILYID_SHIFT                  (28U)
#define SIM_SDID_FAMILYID(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SDID_FAMILYID_SHIFT)) & SIM_SDID_FAMILYID_MASK)

/*! @name SCGC1 - System Clock Gating Control Register 1 */
#define SIM_SCGC1_UART4_MASK                     (0x400U)
#define SIM_SCGC1_UART4_SHIFT                    (10U)
#define SIM_SCGC1_UART4(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC1_UART4_SHIFT)) & SIM_SCGC1_UART4_MASK)
#define SIM_SCGC1_UART5_MASK                     (0x800U)
#define SIM_SCGC1_UART5_SHIFT                    (11U)
#define SIM_SCGC1_UART5(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC1_UART5_SHIFT)) & SIM_SCGC1_UART5_MASK)
#define SIM_SCGC1_PWM1_SM0_MASK                  (0x1000000U)
#define SIM_SCGC1_PWM1_SM0_SHIFT                 (24U)
#define SIM_SCGC1_PWM1_SM0(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SCGC1_PWM1_SM0_SHIFT)) & SIM_SCGC1_PWM1_SM0_MASK)
#define SIM_SCGC1_PWM1_SM1_MASK                  (0x2000000U)
#define SIM_SCGC1_PWM1_SM1_SHIFT                 (25U)
#define SIM_SCGC1_PWM1_SM1(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SCGC1_PWM1_SM1_SHIFT)) & SIM_SCGC1_PWM1_SM1_MASK)
#define SIM_SCGC1_PWM1_SM2_MASK                  (0x4000000U)
#define SIM_SCGC1_PWM1_SM2_SHIFT                 (26U)
#define SIM_SCGC1_PWM1_SM2(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SCGC1_PWM1_SM2_SHIFT)) & SIM_SCGC1_PWM1_SM2_MASK)
#define SIM_SCGC1_PWM1_SM3_MASK                  (0x8000000U)
#define SIM_SCGC1_PWM1_SM3_SHIFT                 (27U)
#define SIM_SCGC1_PWM1_SM3(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SCGC1_PWM1_SM3_SHIFT)) & SIM_SCGC1_PWM1_SM3_MASK)

/*! @name SCGC2 - System Clock Gating Control Register 2 */
#define SIM_SCGC2_ENET_MASK                      (0x1U)
#define SIM_SCGC2_ENET_SHIFT                     (0U)
#define SIM_SCGC2_ENET(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC2_ENET_SHIFT)) & SIM_SCGC2_ENET_MASK)
#define SIM_SCGC2_HSADC1_MASK                    (0x10000000U)
#define SIM_SCGC2_HSADC1_SHIFT                   (28U)
#define SIM_SCGC2_HSADC1(x)                      (((uint32_t)(((uint32_t)(x)) << SIM_SCGC2_HSADC1_SHIFT)) & SIM_SCGC2_HSADC1_MASK)

/*! @name SCGC3 - System Clock Gating Control Register 3 */
#define SIM_SCGC3_TRNG_MASK                      (0x1U)
#define SIM_SCGC3_TRNG_SHIFT                     (0U)
#define SIM_SCGC3_TRNG(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC3_TRNG_SHIFT)) & SIM_SCGC3_TRNG_MASK)
#define SIM_SCGC3_FLEXCAN2_MASK                  (0x10U)
#define SIM_SCGC3_FLEXCAN2_SHIFT                 (4U)
#define SIM_SCGC3_FLEXCAN2(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SCGC3_FLEXCAN2_SHIFT)) & SIM_SCGC3_FLEXCAN2_MASK)
#define SIM_SCGC3_SPI2_MASK                      (0x1000U)
#define SIM_SCGC3_SPI2_SHIFT                     (12U)
#define SIM_SCGC3_SPI2(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC3_SPI2_SHIFT)) & SIM_SCGC3_SPI2_MASK)

/*! @name SCGC4 - System Clock Gating Control Register 4 */
#define SIM_SCGC4_EWM_MASK                       (0x2U)
#define SIM_SCGC4_EWM_SHIFT                      (1U)
#define SIM_SCGC4_EWM(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_EWM_SHIFT)) & SIM_SCGC4_EWM_MASK)
#define SIM_SCGC4_I2C0_MASK                      (0x40U)
#define SIM_SCGC4_I2C0_SHIFT                     (6U)
#define SIM_SCGC4_I2C0(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_I2C0_SHIFT)) & SIM_SCGC4_I2C0_MASK)
#define SIM_SCGC4_I2C1_MASK                      (0x80U)
#define SIM_SCGC4_I2C1_SHIFT                     (7U)
#define SIM_SCGC4_I2C1(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_I2C1_SHIFT)) & SIM_SCGC4_I2C1_MASK)
#define SIM_SCGC4_UART0_MASK                     (0x400U)
#define SIM_SCGC4_UART0_SHIFT                    (10U)
#define SIM_SCGC4_UART0(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_UART0_SHIFT)) & SIM_SCGC4_UART0_MASK)
#define SIM_SCGC4_UART1_MASK                     (0x800U)
#define SIM_SCGC4_UART1_SHIFT                    (11U)
#define SIM_SCGC4_UART1(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_UART1_SHIFT)) & SIM_SCGC4_UART1_MASK)
#define SIM_SCGC4_UART2_MASK                     (0x1000U)
#define SIM_SCGC4_UART2_SHIFT                    (12U)
#define SIM_SCGC4_UART2(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_UART2_SHIFT)) & SIM_SCGC4_UART2_MASK)
#define SIM_SCGC4_UART3_MASK                     (0x2000U)
#define SIM_SCGC4_UART3_SHIFT                    (13U)
#define SIM_SCGC4_UART3(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_UART3_SHIFT)) & SIM_SCGC4_UART3_MASK)
#define SIM_SCGC4_CMP_MASK                       (0x80000U)
#define SIM_SCGC4_CMP_SHIFT                      (19U)
#define SIM_SCGC4_CMP(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_CMP_SHIFT)) & SIM_SCGC4_CMP_MASK)
#define SIM_SCGC4_PWM0_SM0_MASK                  (0x1000000U)
#define SIM_SCGC4_PWM0_SM0_SHIFT                 (24U)
#define SIM_SCGC4_PWM0_SM0(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_PWM0_SM0_SHIFT)) & SIM_SCGC4_PWM0_SM0_MASK)
#define SIM_SCGC4_PWM0_SM1_MASK                  (0x2000000U)
#define SIM_SCGC4_PWM0_SM1_SHIFT                 (25U)
#define SIM_SCGC4_PWM0_SM1(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_PWM0_SM1_SHIFT)) & SIM_SCGC4_PWM0_SM1_MASK)
#define SIM_SCGC4_PWM0_SM2_MASK                  (0x4000000U)
#define SIM_SCGC4_PWM0_SM2_SHIFT                 (26U)
#define SIM_SCGC4_PWM0_SM2(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_PWM0_SM2_SHIFT)) & SIM_SCGC4_PWM0_SM2_MASK)
#define SIM_SCGC4_PWM0_SM3_MASK                  (0x8000000U)
#define SIM_SCGC4_PWM0_SM3_SHIFT                 (27U)
#define SIM_SCGC4_PWM0_SM3(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_PWM0_SM3_SHIFT)) & SIM_SCGC4_PWM0_SM3_MASK)

/*! @name SCGC5 - System Clock Gating Control Register 5 */
#define SIM_SCGC5_LPTMR_MASK                     (0x1U)
#define SIM_SCGC5_LPTMR_SHIFT                    (0U)
#define SIM_SCGC5_LPTMR(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_LPTMR_SHIFT)) & SIM_SCGC5_LPTMR_MASK)
#define SIM_SCGC5_PORTA_MASK                     (0x200U)
#define SIM_SCGC5_PORTA_SHIFT                    (9U)
#define SIM_SCGC5_PORTA(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTA_SHIFT)) & SIM_SCGC5_PORTA_MASK)
#define SIM_SCGC5_PORTB_MASK                     (0x400U)
#define SIM_SCGC5_PORTB_SHIFT                    (10U)
#define SIM_SCGC5_PORTB(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTB_SHIFT)) & SIM_SCGC5_PORTB_MASK)
#define SIM_SCGC5_PORTC_MASK                     (0x800U)
#define SIM_SCGC5_PORTC_SHIFT                    (11U)
#define SIM_SCGC5_PORTC(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTC_SHIFT)) & SIM_SCGC5_PORTC_MASK)
#define SIM_SCGC5_PORTD_MASK                     (0x1000U)
#define SIM_SCGC5_PORTD_SHIFT                    (12U)
#define SIM_SCGC5_PORTD(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTD_SHIFT)) & SIM_SCGC5_PORTD_MASK)
#define SIM_SCGC5_PORTE_MASK                     (0x2000U)
#define SIM_SCGC5_PORTE_SHIFT                    (13U)
#define SIM_SCGC5_PORTE(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTE_SHIFT)) & SIM_SCGC5_PORTE_MASK)
#define SIM_SCGC5_ENC_MASK                       (0x200000U)
#define SIM_SCGC5_ENC_SHIFT                      (21U)
#define SIM_SCGC5_ENC(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_ENC_SHIFT)) & SIM_SCGC5_ENC_MASK)
#define SIM_SCGC5_XBARA_MASK                     (0x2000000U)
#define SIM_SCGC5_XBARA_SHIFT                    (25U)
#define SIM_SCGC5_XBARA(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_XBARA_SHIFT)) & SIM_SCGC5_XBARA_MASK)
#define SIM_SCGC5_XBARB_MASK                     (0x4000000U)
#define SIM_SCGC5_XBARB_SHIFT                    (26U)
#define SIM_SCGC5_XBARB(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_XBARB_SHIFT)) & SIM_SCGC5_XBARB_MASK)
#define SIM_SCGC5_AOI_MASK                       (0x8000000U)
#define SIM_SCGC5_AOI_SHIFT                      (27U)
#define SIM_SCGC5_AOI(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_AOI_SHIFT)) & SIM_SCGC5_AOI_MASK)
#define SIM_SCGC5_HSADC0_MASK                    (0x10000000U)
#define SIM_SCGC5_HSADC0_SHIFT                   (28U)
#define SIM_SCGC5_HSADC0(x)                      (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_HSADC0_SHIFT)) & SIM_SCGC5_HSADC0_MASK)

/*! @name SCGC6 - System Clock Gating Control Register 6 */
#define SIM_SCGC6_FTF_MASK                       (0x1U)
#define SIM_SCGC6_FTF_SHIFT                      (0U)
#define SIM_SCGC6_FTF(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_FTF_SHIFT)) & SIM_SCGC6_FTF_MASK)
#define SIM_SCGC6_DMAMUX_MASK                    (0x2U)
#define SIM_SCGC6_DMAMUX_SHIFT                   (1U)
#define SIM_SCGC6_DMAMUX(x)                      (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_DMAMUX_SHIFT)) & SIM_SCGC6_DMAMUX_MASK)
#define SIM_SCGC6_FLEXCAN0_MASK                  (0x10U)
#define SIM_SCGC6_FLEXCAN0_SHIFT                 (4U)
#define SIM_SCGC6_FLEXCAN0(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_FLEXCAN0_SHIFT)) & SIM_SCGC6_FLEXCAN0_MASK)
#define SIM_SCGC6_FLEXCAN1_MASK                  (0x20U)
#define SIM_SCGC6_FLEXCAN1_SHIFT                 (5U)
#define SIM_SCGC6_FLEXCAN1(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_FLEXCAN1_SHIFT)) & SIM_SCGC6_FLEXCAN1_MASK)
#define SIM_SCGC6_FTM3_MASK                      (0x40U)
#define SIM_SCGC6_FTM3_SHIFT                     (6U)
#define SIM_SCGC6_FTM3(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_FTM3_SHIFT)) & SIM_SCGC6_FTM3_MASK)
#define SIM_SCGC6_SPI0_MASK                      (0x1000U)
#define SIM_SCGC6_SPI0_SHIFT                     (12U)
#define SIM_SCGC6_SPI0(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_SPI0_SHIFT)) & SIM_SCGC6_SPI0_MASK)
#define SIM_SCGC6_SPI1_MASK                      (0x2000U)
#define SIM_SCGC6_SPI1_SHIFT                     (13U)
#define SIM_SCGC6_SPI1(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_SPI1_SHIFT)) & SIM_SCGC6_SPI1_MASK)
#define SIM_SCGC6_PDB1_MASK                      (0x20000U)
#define SIM_SCGC6_PDB1_SHIFT                     (17U)
#define SIM_SCGC6_PDB1(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_PDB1_SHIFT)) & SIM_SCGC6_PDB1_MASK)
#define SIM_SCGC6_CRC_MASK                       (0x40000U)
#define SIM_SCGC6_CRC_SHIFT                      (18U)
#define SIM_SCGC6_CRC(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_CRC_SHIFT)) & SIM_SCGC6_CRC_MASK)
#define SIM_SCGC6_PDB0_MASK                      (0x400000U)
#define SIM_SCGC6_PDB0_SHIFT                     (22U)
#define SIM_SCGC6_PDB0(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_PDB0_SHIFT)) & SIM_SCGC6_PDB0_MASK)
#define SIM_SCGC6_PIT_MASK                       (0x800000U)
#define SIM_SCGC6_PIT_SHIFT                      (23U)
#define SIM_SCGC6_PIT(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_PIT_SHIFT)) & SIM_SCGC6_PIT_MASK)
#define SIM_SCGC6_FTM0_MASK                      (0x1000000U)
#define SIM_SCGC6_FTM0_SHIFT                     (24U)
#define SIM_SCGC6_FTM0(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_FTM0_SHIFT)) & SIM_SCGC6_FTM0_MASK)
#define SIM_SCGC6_FTM1_MASK                      (0x2000000U)
#define SIM_SCGC6_FTM1_SHIFT                     (25U)
#define SIM_SCGC6_FTM1(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_FTM1_SHIFT)) & SIM_SCGC6_FTM1_MASK)
#define SIM_SCGC6_FTM2_MASK                      (0x4000000U)
#define SIM_SCGC6_FTM2_SHIFT                     (26U)
#define SIM_SCGC6_FTM2(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_FTM2_SHIFT)) & SIM_SCGC6_FTM2_MASK)
#define SIM_SCGC6_ADC0_MASK                      (0x8000000U)
#define SIM_SCGC6_ADC0_SHIFT                     (27U)
#define SIM_SCGC6_ADC0(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_ADC0_SHIFT)) & SIM_SCGC6_ADC0_MASK)
#define SIM_SCGC6_DAC0_MASK                      (0x80000000U)
#define SIM_SCGC6_DAC0_SHIFT                     (31U)
#define SIM_SCGC6_DAC0(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_DAC0_SHIFT)) & SIM_SCGC6_DAC0_MASK)

/*! @name SCGC7 - System Clock Gating Control Register 7 */
#define SIM_SCGC7_FLEXBUS_MASK                   (0x1U)
#define SIM_SCGC7_FLEXBUS_SHIFT                  (0U)
#define SIM_SCGC7_FLEXBUS(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SCGC7_FLEXBUS_SHIFT)) & SIM_SCGC7_FLEXBUS_MASK)
#define SIM_SCGC7_SMPU_MASK                      (0x4U)
#define SIM_SCGC7_SMPU_SHIFT                     (2U)
#define SIM_SCGC7_SMPU(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC7_SMPU_SHIFT)) & SIM_SCGC7_SMPU_MASK)
#define SIM_SCGC7_DMA_MASK                       (0x100U)
#define SIM_SCGC7_DMA_SHIFT                      (8U)
#define SIM_SCGC7_DMA(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC7_DMA_SHIFT)) & SIM_SCGC7_DMA_MASK)

/*! @name CLKDIV1 - System Clock Divider Register 1 */
#define SIM_CLKDIV1_OUTDIV4_MASK                 (0xF0000U)
#define SIM_CLKDIV1_OUTDIV4_SHIFT                (16U)
#define SIM_CLKDIV1_OUTDIV4(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_CLKDIV1_OUTDIV4_SHIFT)) & SIM_CLKDIV1_OUTDIV4_MASK)
#define SIM_CLKDIV1_OUTDIV3_MASK                 (0xF00000U)
#define SIM_CLKDIV1_OUTDIV3_SHIFT                (20U)
#define SIM_CLKDIV1_OUTDIV3(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_CLKDIV1_OUTDIV3_SHIFT)) & SIM_CLKDIV1_OUTDIV3_MASK)
#define SIM_CLKDIV1_OUTDIV2_MASK                 (0xF000000U)
#define SIM_CLKDIV1_OUTDIV2_SHIFT                (24U)
#define SIM_CLKDIV1_OUTDIV2(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_CLKDIV1_OUTDIV2_SHIFT)) & SIM_CLKDIV1_OUTDIV2_MASK)
#define SIM_CLKDIV1_OUTDIV1_MASK                 (0xF0000000U)
#define SIM_CLKDIV1_OUTDIV1_SHIFT                (28U)
#define SIM_CLKDIV1_OUTDIV1(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_CLKDIV1_OUTDIV1_SHIFT)) & SIM_CLKDIV1_OUTDIV1_MASK)

/*! @name FCFG1 - Flash Configuration Register 1 */
#define SIM_FCFG1_FLASHDIS_MASK                  (0x1U)
#define SIM_FCFG1_FLASHDIS_SHIFT                 (0U)
#define SIM_FCFG1_FLASHDIS(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_FCFG1_FLASHDIS_SHIFT)) & SIM_FCFG1_FLASHDIS_MASK)
#define SIM_FCFG1_FLASHDOZE_MASK                 (0x2U)
#define SIM_FCFG1_FLASHDOZE_SHIFT                (1U)
#define SIM_FCFG1_FLASHDOZE(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_FCFG1_FLASHDOZE_SHIFT)) & SIM_FCFG1_FLASHDOZE_MASK)
#define SIM_FCFG1_PFSIZE_MASK                    (0xF000000U)
#define SIM_FCFG1_PFSIZE_SHIFT                   (24U)
#define SIM_FCFG1_PFSIZE(x)                      (((uint32_t)(((uint32_t)(x)) << SIM_FCFG1_PFSIZE_SHIFT)) & SIM_FCFG1_PFSIZE_MASK)

/*! @name FCFG2 - Flash Configuration Register 2 */
#define SIM_FCFG2_MAXADDR0_MASK                  (0x7F000000U)
#define SIM_FCFG2_MAXADDR0_SHIFT                 (24U)
#define SIM_FCFG2_MAXADDR0(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_FCFG2_MAXADDR0_SHIFT)) & SIM_FCFG2_MAXADDR0_MASK)

/*! @name UIDH - Unique Identification Register High */
#define SIM_UIDH_UID_MASK                        (0xFFFFFFFFU)
#define SIM_UIDH_UID_SHIFT                       (0U)
#define SIM_UIDH_UID(x)                          (((uint32_t)(((uint32_t)(x)) << SIM_UIDH_UID_SHIFT)) & SIM_UIDH_UID_MASK)

/*! @name UIDMH - Unique Identification Register Mid-High */
#define SIM_UIDMH_UID_MASK                       (0xFFFFFFFFU)
#define SIM_UIDMH_UID_SHIFT                      (0U)
#define SIM_UIDMH_UID(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_UIDMH_UID_SHIFT)) & SIM_UIDMH_UID_MASK)

/*! @name UIDML - Unique Identification Register Mid Low */
#define SIM_UIDML_UID_MASK                       (0xFFFFFFFFU)
#define SIM_UIDML_UID_SHIFT                      (0U)
#define SIM_UIDML_UID(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_UIDML_UID_SHIFT)) & SIM_UIDML_UID_MASK)

/*! @name UIDL - Unique Identification Register Low */
#define SIM_UIDL_UID_MASK                        (0xFFFFFFFFU)
#define SIM_UIDL_UID_SHIFT                       (0U)
#define SIM_UIDL_UID(x)                          (((uint32_t)(((uint32_t)(x)) << SIM_UIDL_UID_SHIFT)) & SIM_UIDL_UID_MASK)

/*! @name CLKDIV4 - System Clock Divider Register 4 */
#define SIM_CLKDIV4_TRACEFRAC_MASK               (0x1U)
#define SIM_CLKDIV4_TRACEFRAC_SHIFT              (0U)
#define SIM_CLKDIV4_TRACEFRAC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_CLKDIV4_TRACEFRAC_SHIFT)) & SIM_CLKDIV4_TRACEFRAC_MASK)
#define SIM_CLKDIV4_TRACEDIV_MASK                (0xEU)
#define SIM_CLKDIV4_TRACEDIV_SHIFT               (1U)
#define SIM_CLKDIV4_TRACEDIV(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_CLKDIV4_TRACEDIV_SHIFT)) & SIM_CLKDIV4_TRACEDIV_MASK)
#define SIM_CLKDIV4_TRACEDIVEN_MASK              (0x10000000U)
#define SIM_CLKDIV4_TRACEDIVEN_SHIFT             (28U)
#define SIM_CLKDIV4_TRACEDIVEN(x)                (((uint32_t)(((uint32_t)(x)) << SIM_CLKDIV4_TRACEDIVEN_SHIFT)) & SIM_CLKDIV4_TRACEDIVEN_MASK)

/*! @name MISCTRL0 - Miscellaneous Control Register 0 */
#define SIM_MISCTRL0_CMPWIN0SRC_MASK             (0x300U)
#define SIM_MISCTRL0_CMPWIN0SRC_SHIFT            (8U)
#define SIM_MISCTRL0_CMPWIN0SRC(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL0_CMPWIN0SRC_SHIFT)) & SIM_MISCTRL0_CMPWIN0SRC_MASK)
#define SIM_MISCTRL0_CMPWIN1SRC_MASK             (0xC00U)
#define SIM_MISCTRL0_CMPWIN1SRC_SHIFT            (10U)
#define SIM_MISCTRL0_CMPWIN1SRC(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL0_CMPWIN1SRC_SHIFT)) & SIM_MISCTRL0_CMPWIN1SRC_MASK)
#define SIM_MISCTRL0_CMPWIN2SRC_MASK             (0x3000U)
#define SIM_MISCTRL0_CMPWIN2SRC_SHIFT            (12U)
#define SIM_MISCTRL0_CMPWIN2SRC(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL0_CMPWIN2SRC_SHIFT)) & SIM_MISCTRL0_CMPWIN2SRC_MASK)
#define SIM_MISCTRL0_CMPWIN3SRC_MASK             (0xC000U)
#define SIM_MISCTRL0_CMPWIN3SRC_SHIFT            (14U)
#define SIM_MISCTRL0_CMPWIN3SRC(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL0_CMPWIN3SRC_SHIFT)) & SIM_MISCTRL0_CMPWIN3SRC_MASK)
#define SIM_MISCTRL0_EWMINSRC_MASK               (0x10000U)
#define SIM_MISCTRL0_EWMINSRC_SHIFT              (16U)
#define SIM_MISCTRL0_EWMINSRC(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL0_EWMINSRC_SHIFT)) & SIM_MISCTRL0_EWMINSRC_MASK)
#define SIM_MISCTRL0_DACTRIGSRC_MASK             (0xC0000U)
#define SIM_MISCTRL0_DACTRIGSRC_SHIFT            (18U)
#define SIM_MISCTRL0_DACTRIGSRC(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL0_DACTRIGSRC_SHIFT)) & SIM_MISCTRL0_DACTRIGSRC_MASK)

/*! @name MISCTRL1 - Miscellaneous Control Register 1 */
#define SIM_MISCTRL1_SYNCXBARAPITTRIG0_MASK      (0x100U)
#define SIM_MISCTRL1_SYNCXBARAPITTRIG0_SHIFT     (8U)
#define SIM_MISCTRL1_SYNCXBARAPITTRIG0(x)        (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL1_SYNCXBARAPITTRIG0_SHIFT)) & SIM_MISCTRL1_SYNCXBARAPITTRIG0_MASK)
#define SIM_MISCTRL1_SYNCXBARAPITTRIG1_MASK      (0x200U)
#define SIM_MISCTRL1_SYNCXBARAPITTRIG1_SHIFT     (9U)
#define SIM_MISCTRL1_SYNCXBARAPITTRIG1(x)        (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL1_SYNCXBARAPITTRIG1_SHIFT)) & SIM_MISCTRL1_SYNCXBARAPITTRIG1_MASK)
#define SIM_MISCTRL1_SYNCXBARAPITTRIG2_MASK      (0x400U)
#define SIM_MISCTRL1_SYNCXBARAPITTRIG2_SHIFT     (10U)
#define SIM_MISCTRL1_SYNCXBARAPITTRIG2(x)        (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL1_SYNCXBARAPITTRIG2_SHIFT)) & SIM_MISCTRL1_SYNCXBARAPITTRIG2_MASK)
#define SIM_MISCTRL1_SYNCXBARAPITTRIG3_MASK      (0x800U)
#define SIM_MISCTRL1_SYNCXBARAPITTRIG3_SHIFT     (11U)
#define SIM_MISCTRL1_SYNCXBARAPITTRIG3(x)        (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL1_SYNCXBARAPITTRIG3_SHIFT)) & SIM_MISCTRL1_SYNCXBARAPITTRIG3_MASK)
#define SIM_MISCTRL1_SYNCXBARBPITTRIG0_MASK      (0x1000U)
#define SIM_MISCTRL1_SYNCXBARBPITTRIG0_SHIFT     (12U)
#define SIM_MISCTRL1_SYNCXBARBPITTRIG0(x)        (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL1_SYNCXBARBPITTRIG0_SHIFT)) & SIM_MISCTRL1_SYNCXBARBPITTRIG0_MASK)
#define SIM_MISCTRL1_SYNCXBARBPITTRIG1_MASK      (0x2000U)
#define SIM_MISCTRL1_SYNCXBARBPITTRIG1_SHIFT     (13U)
#define SIM_MISCTRL1_SYNCXBARBPITTRIG1(x)        (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL1_SYNCXBARBPITTRIG1_SHIFT)) & SIM_MISCTRL1_SYNCXBARBPITTRIG1_MASK)
#define SIM_MISCTRL1_SYNCDACHWTRIG_MASK          (0x10000U)
#define SIM_MISCTRL1_SYNCDACHWTRIG_SHIFT         (16U)
#define SIM_MISCTRL1_SYNCDACHWTRIG(x)            (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL1_SYNCDACHWTRIG_SHIFT)) & SIM_MISCTRL1_SYNCDACHWTRIG_MASK)
#define SIM_MISCTRL1_SYNCEWMIN_MASK              (0x20000U)
#define SIM_MISCTRL1_SYNCEWMIN_SHIFT             (17U)
#define SIM_MISCTRL1_SYNCEWMIN(x)                (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL1_SYNCEWMIN_SHIFT)) & SIM_MISCTRL1_SYNCEWMIN_MASK)
#define SIM_MISCTRL1_SYNCCMP0SAMPLEWIN_MASK      (0x100000U)
#define SIM_MISCTRL1_SYNCCMP0SAMPLEWIN_SHIFT     (20U)
#define SIM_MISCTRL1_SYNCCMP0SAMPLEWIN(x)        (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL1_SYNCCMP0SAMPLEWIN_SHIFT)) & SIM_MISCTRL1_SYNCCMP0SAMPLEWIN_MASK)
#define SIM_MISCTRL1_SYNCCMP1SAMPLEWIN_MASK      (0x200000U)
#define SIM_MISCTRL1_SYNCCMP1SAMPLEWIN_SHIFT     (21U)
#define SIM_MISCTRL1_SYNCCMP1SAMPLEWIN(x)        (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL1_SYNCCMP1SAMPLEWIN_SHIFT)) & SIM_MISCTRL1_SYNCCMP1SAMPLEWIN_MASK)
#define SIM_MISCTRL1_SYNCCMP2SAMPLEWIN_MASK      (0x400000U)
#define SIM_MISCTRL1_SYNCCMP2SAMPLEWIN_SHIFT     (22U)
#define SIM_MISCTRL1_SYNCCMP2SAMPLEWIN(x)        (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL1_SYNCCMP2SAMPLEWIN_SHIFT)) & SIM_MISCTRL1_SYNCCMP2SAMPLEWIN_MASK)
#define SIM_MISCTRL1_SYNCCMP3SAMPLEWIN_MASK      (0x800000U)
#define SIM_MISCTRL1_SYNCCMP3SAMPLEWIN_SHIFT     (23U)
#define SIM_MISCTRL1_SYNCCMP3SAMPLEWIN(x)        (((uint32_t)(((uint32_t)(x)) << SIM_MISCTRL1_SYNCCMP3SAMPLEWIN_SHIFT)) & SIM_MISCTRL1_SYNCCMP3SAMPLEWIN_MASK)

/*! @name WDOGC - WDOG Control Register */
#define SIM_WDOGC_WDOGCLKS_MASK                  (0x2U)
#define SIM_WDOGC_WDOGCLKS_SHIFT                 (1U)
#define SIM_WDOGC_WDOGCLKS(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_WDOGC_WDOGCLKS_SHIFT)) & SIM_WDOGC_WDOGCLKS_MASK)

/*! @name PWRC - Power Control Register */
#define SIM_PWRC_SRPDN_MASK                      (0x3U)
#define SIM_PWRC_SRPDN_SHIFT                     (0U)
#define SIM_PWRC_SRPDN(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_PWRC_SRPDN_SHIFT)) & SIM_PWRC_SRPDN_MASK)
#define SIM_PWRC_SR27STDBY_MASK                  (0xCU)
#define SIM_PWRC_SR27STDBY_SHIFT                 (2U)
#define SIM_PWRC_SR27STDBY(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_PWRC_SR27STDBY_SHIFT)) & SIM_PWRC_SR27STDBY_MASK)
#define SIM_PWRC_SR12STDBY_MASK                  (0xC0U)
#define SIM_PWRC_SR12STDBY_SHIFT                 (6U)
#define SIM_PWRC_SR12STDBY(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_PWRC_SR12STDBY_SHIFT)) & SIM_PWRC_SR12STDBY_MASK)
#define SIM_PWRC_SRPWRDETEN_MASK                 (0x100U)
#define SIM_PWRC_SRPWRDETEN_SHIFT                (8U)
#define SIM_PWRC_SRPWRDETEN(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_PWRC_SRPWRDETEN_SHIFT)) & SIM_PWRC_SRPWRDETEN_MASK)
#define SIM_PWRC_SRPWRRDY_MASK                   (0x200U)
#define SIM_PWRC_SRPWRRDY_SHIFT                  (9U)
#define SIM_PWRC_SRPWRRDY(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_PWRC_SRPWRRDY_SHIFT)) & SIM_PWRC_SRPWRRDY_MASK)
#define SIM_PWRC_SRPWROK_MASK                    (0x10000U)
#define SIM_PWRC_SRPWROK_SHIFT                   (16U)
#define SIM_PWRC_SRPWROK(x)                      (((uint32_t)(((uint32_t)(x)) << SIM_PWRC_SRPWROK_SHIFT)) & SIM_PWRC_SRPWROK_MASK)

/*! @name ADCOPT - ADC Additional Option Register */
#define SIM_ADCOPT_ADC0TRGSEL_MASK               (0xF0000U)
#define SIM_ADCOPT_ADC0TRGSEL_SHIFT              (16U)
#define SIM_ADCOPT_ADC0TRGSEL(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_ADCOPT_ADC0TRGSEL_SHIFT)) & SIM_ADCOPT_ADC0TRGSEL_MASK)
#define SIM_ADCOPT_ADC0PRETRGSEL_MASK            (0x100000U)
#define SIM_ADCOPT_ADC0PRETRGSEL_SHIFT           (20U)
#define SIM_ADCOPT_ADC0PRETRGSEL(x)              (((uint32_t)(((uint32_t)(x)) << SIM_ADCOPT_ADC0PRETRGSEL_SHIFT)) & SIM_ADCOPT_ADC0PRETRGSEL_MASK)
#define SIM_ADCOPT_ADC0ALTTRGEN_MASK             (0xC00000U)
#define SIM_ADCOPT_ADC0ALTTRGEN_SHIFT            (22U)
#define SIM_ADCOPT_ADC0ALTTRGEN(x)               (((uint32_t)(((uint32_t)(x)) << SIM_ADCOPT_ADC0ALTTRGEN_SHIFT)) & SIM_ADCOPT_ADC0ALTTRGEN_MASK)
#define SIM_ADCOPT_HSADCIRCLK_MASK               (0x2000000U)
#define SIM_ADCOPT_HSADCIRCLK_SHIFT              (25U)
#define SIM_ADCOPT_HSADCIRCLK(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_ADCOPT_HSADCIRCLK_SHIFT)) & SIM_ADCOPT_HSADCIRCLK_MASK)
#define SIM_ADCOPT_HSADCSTOPEN_MASK              (0x4000000U)
#define SIM_ADCOPT_HSADCSTOPEN_SHIFT             (26U)
#define SIM_ADCOPT_HSADCSTOPEN(x)                (((uint32_t)(((uint32_t)(x)) << SIM_ADCOPT_HSADCSTOPEN_SHIFT)) & SIM_ADCOPT_HSADCSTOPEN_MASK)


/*!
 * @}
 */ /* end of group SIM_Register_Masks */


/* SIM - Peripheral instance base addresses */
/** Peripheral SIM base address */
#define SIM_BASE                                 (0x40047000u)
/** Peripheral SIM base pointer */
#define SIM                                      ((SIM_Type *)SIM_BASE)
/** Array initializer of SIM peripheral base addresses */
#define SIM_BASE_ADDRS                           { SIM_BASE }
/** Array initializer of SIM peripheral base pointers */
#define SIM_BASE_PTRS                            { SIM }

/*!
 * @}
 */ /* end of group SIM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SMC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SMC_Peripheral_Access_Layer SMC Peripheral Access Layer
 * @{
 */

/** SMC - Register Layout Typedef */
typedef struct {
  __IO uint8_t PMPROT;                             /**< Power Mode Protection register, offset: 0x0 */
  __IO uint8_t PMCTRL;                             /**< Power Mode Control register, offset: 0x1 */
  __IO uint8_t STOPCTRL;                           /**< Stop Control Register, offset: 0x2 */
  __I  uint8_t PMSTAT;                             /**< Power Mode Status register, offset: 0x3 */
} SMC_Type;

/* ----------------------------------------------------------------------------
   -- SMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SMC_Register_Masks SMC Register Masks
 * @{
 */

/*! @name PMPROT - Power Mode Protection register */
#define SMC_PMPROT_AVLLS_MASK                    (0x2U)
#define SMC_PMPROT_AVLLS_SHIFT                   (1U)
#define SMC_PMPROT_AVLLS(x)                      (((uint8_t)(((uint8_t)(x)) << SMC_PMPROT_AVLLS_SHIFT)) & SMC_PMPROT_AVLLS_MASK)
#define SMC_PMPROT_AVLP_MASK                     (0x20U)
#define SMC_PMPROT_AVLP_SHIFT                    (5U)
#define SMC_PMPROT_AVLP(x)                       (((uint8_t)(((uint8_t)(x)) << SMC_PMPROT_AVLP_SHIFT)) & SMC_PMPROT_AVLP_MASK)
#define SMC_PMPROT_AHSRUN_MASK                   (0x80U)
#define SMC_PMPROT_AHSRUN_SHIFT                  (7U)
#define SMC_PMPROT_AHSRUN(x)                     (((uint8_t)(((uint8_t)(x)) << SMC_PMPROT_AHSRUN_SHIFT)) & SMC_PMPROT_AHSRUN_MASK)

/*! @name PMCTRL - Power Mode Control register */
#define SMC_PMCTRL_STOPM_MASK                    (0x7U)
#define SMC_PMCTRL_STOPM_SHIFT                   (0U)
#define SMC_PMCTRL_STOPM(x)                      (((uint8_t)(((uint8_t)(x)) << SMC_PMCTRL_STOPM_SHIFT)) & SMC_PMCTRL_STOPM_MASK)
#define SMC_PMCTRL_STOPA_MASK                    (0x8U)
#define SMC_PMCTRL_STOPA_SHIFT                   (3U)
#define SMC_PMCTRL_STOPA(x)                      (((uint8_t)(((uint8_t)(x)) << SMC_PMCTRL_STOPA_SHIFT)) & SMC_PMCTRL_STOPA_MASK)
#define SMC_PMCTRL_RUNM_MASK                     (0x60U)
#define SMC_PMCTRL_RUNM_SHIFT                    (5U)
#define SMC_PMCTRL_RUNM(x)                       (((uint8_t)(((uint8_t)(x)) << SMC_PMCTRL_RUNM_SHIFT)) & SMC_PMCTRL_RUNM_MASK)

/*! @name STOPCTRL - Stop Control Register */
#define SMC_STOPCTRL_VLLSM_MASK                  (0x7U)
#define SMC_STOPCTRL_VLLSM_SHIFT                 (0U)
#define SMC_STOPCTRL_VLLSM(x)                    (((uint8_t)(((uint8_t)(x)) << SMC_STOPCTRL_VLLSM_SHIFT)) & SMC_STOPCTRL_VLLSM_MASK)
#define SMC_STOPCTRL_LPOPO_MASK                  (0x8U)
#define SMC_STOPCTRL_LPOPO_SHIFT                 (3U)
#define SMC_STOPCTRL_LPOPO(x)                    (((uint8_t)(((uint8_t)(x)) << SMC_STOPCTRL_LPOPO_SHIFT)) & SMC_STOPCTRL_LPOPO_MASK)
#define SMC_STOPCTRL_RAM2PO_MASK                 (0x10U)
#define SMC_STOPCTRL_RAM2PO_SHIFT                (4U)
#define SMC_STOPCTRL_RAM2PO(x)                   (((uint8_t)(((uint8_t)(x)) << SMC_STOPCTRL_RAM2PO_SHIFT)) & SMC_STOPCTRL_RAM2PO_MASK)
#define SMC_STOPCTRL_PORPO_MASK                  (0x20U)
#define SMC_STOPCTRL_PORPO_SHIFT                 (5U)
#define SMC_STOPCTRL_PORPO(x)                    (((uint8_t)(((uint8_t)(x)) << SMC_STOPCTRL_PORPO_SHIFT)) & SMC_STOPCTRL_PORPO_MASK)
#define SMC_STOPCTRL_PSTOPO_MASK                 (0xC0U)
#define SMC_STOPCTRL_PSTOPO_SHIFT                (6U)
#define SMC_STOPCTRL_PSTOPO(x)                   (((uint8_t)(((uint8_t)(x)) << SMC_STOPCTRL_PSTOPO_SHIFT)) & SMC_STOPCTRL_PSTOPO_MASK)

/*! @name PMSTAT - Power Mode Status register */
#define SMC_PMSTAT_PMSTAT_MASK                   (0xFFU)
#define SMC_PMSTAT_PMSTAT_SHIFT                  (0U)
#define SMC_PMSTAT_PMSTAT(x)                     (((uint8_t)(((uint8_t)(x)) << SMC_PMSTAT_PMSTAT_SHIFT)) & SMC_PMSTAT_PMSTAT_MASK)


/*!
 * @}
 */ /* end of group SMC_Register_Masks */


/* SMC - Peripheral instance base addresses */
/** Peripheral SMC base address */
#define SMC_BASE                                 (0x4007E000u)
/** Peripheral SMC base pointer */
#define SMC                                      ((SMC_Type *)SMC_BASE)
/** Array initializer of SMC peripheral base addresses */
#define SMC_BASE_ADDRS                           { SMC_BASE }
/** Array initializer of SMC peripheral base pointers */
#define SMC_BASE_PTRS                            { SMC }

/*!
 * @}
 */ /* end of group SMC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SPI Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Peripheral_Access_Layer SPI Peripheral Access Layer
 * @{
 */

/** SPI - Register Layout Typedef */
typedef struct {
  __IO uint32_t MCR;                               /**< Module Configuration Register, offset: 0x0 */
       uint8_t RESERVED_0[4];
  __IO uint32_t TCR;                               /**< Transfer Count Register, offset: 0x8 */
  union {                                          /* offset: 0xC */
    __IO uint32_t CTAR[2];                           /**< Clock and Transfer Attributes Register (In Master Mode), array offset: 0xC, array step: 0x4 */
    __IO uint32_t CTAR_SLAVE[1];                     /**< Clock and Transfer Attributes Register (In Slave Mode), array offset: 0xC, array step: 0x4 */
  };
       uint8_t RESERVED_1[24];
  __IO uint32_t SR;                                /**< Status Register, offset: 0x2C */
  __IO uint32_t RSER;                              /**< DMA/Interrupt Request Select and Enable Register, offset: 0x30 */
  union {                                          /* offset: 0x34 */
    __IO uint32_t PUSHR;                             /**< PUSH TX FIFO Register In Master Mode, offset: 0x34 */
    __IO uint32_t PUSHR_SLAVE;                       /**< PUSH TX FIFO Register In Slave Mode, offset: 0x34 */
  };
  __I  uint32_t POPR;                              /**< POP RX FIFO Register, offset: 0x38 */
  __I  uint32_t TXFR0;                             /**< Transmit FIFO Registers, offset: 0x3C */
  __I  uint32_t TXFR1;                             /**< Transmit FIFO Registers, offset: 0x40 */
  __I  uint32_t TXFR2;                             /**< Transmit FIFO Registers, offset: 0x44 */
  __I  uint32_t TXFR3;                             /**< Transmit FIFO Registers, offset: 0x48 */
       uint8_t RESERVED_2[48];
  __I  uint32_t RXFR0;                             /**< Receive FIFO Registers, offset: 0x7C */
  __I  uint32_t RXFR1;                             /**< Receive FIFO Registers, offset: 0x80 */
  __I  uint32_t RXFR2;                             /**< Receive FIFO Registers, offset: 0x84 */
  __I  uint32_t RXFR3;                             /**< Receive FIFO Registers, offset: 0x88 */
} SPI_Type;

/* ----------------------------------------------------------------------------
   -- SPI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Masks SPI Register Masks
 * @{
 */

/*! @name MCR - Module Configuration Register */
#define SPI_MCR_HALT_MASK                        (0x1U)
#define SPI_MCR_HALT_SHIFT                       (0U)
#define SPI_MCR_HALT(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_MCR_HALT_SHIFT)) & SPI_MCR_HALT_MASK)
#define SPI_MCR_SMPL_PT_MASK                     (0x300U)
#define SPI_MCR_SMPL_PT_SHIFT                    (8U)
#define SPI_MCR_SMPL_PT(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_MCR_SMPL_PT_SHIFT)) & SPI_MCR_SMPL_PT_MASK)
#define SPI_MCR_CLR_RXF_MASK                     (0x400U)
#define SPI_MCR_CLR_RXF_SHIFT                    (10U)
#define SPI_MCR_CLR_RXF(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_MCR_CLR_RXF_SHIFT)) & SPI_MCR_CLR_RXF_MASK)
#define SPI_MCR_CLR_TXF_MASK                     (0x800U)
#define SPI_MCR_CLR_TXF_SHIFT                    (11U)
#define SPI_MCR_CLR_TXF(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_MCR_CLR_TXF_SHIFT)) & SPI_MCR_CLR_TXF_MASK)
#define SPI_MCR_DIS_RXF_MASK                     (0x1000U)
#define SPI_MCR_DIS_RXF_SHIFT                    (12U)
#define SPI_MCR_DIS_RXF(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_MCR_DIS_RXF_SHIFT)) & SPI_MCR_DIS_RXF_MASK)
#define SPI_MCR_DIS_TXF_MASK                     (0x2000U)
#define SPI_MCR_DIS_TXF_SHIFT                    (13U)
#define SPI_MCR_DIS_TXF(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_MCR_DIS_TXF_SHIFT)) & SPI_MCR_DIS_TXF_MASK)
#define SPI_MCR_MDIS_MASK                        (0x4000U)
#define SPI_MCR_MDIS_SHIFT                       (14U)
#define SPI_MCR_MDIS(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_MCR_MDIS_SHIFT)) & SPI_MCR_MDIS_MASK)
#define SPI_MCR_DOZE_MASK                        (0x8000U)
#define SPI_MCR_DOZE_SHIFT                       (15U)
#define SPI_MCR_DOZE(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_MCR_DOZE_SHIFT)) & SPI_MCR_DOZE_MASK)
#define SPI_MCR_PCSIS_MASK                       (0x3F0000U)
#define SPI_MCR_PCSIS_SHIFT                      (16U)
#define SPI_MCR_PCSIS(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_MCR_PCSIS_SHIFT)) & SPI_MCR_PCSIS_MASK)
#define SPI_MCR_ROOE_MASK                        (0x1000000U)
#define SPI_MCR_ROOE_SHIFT                       (24U)
#define SPI_MCR_ROOE(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_MCR_ROOE_SHIFT)) & SPI_MCR_ROOE_MASK)
#define SPI_MCR_PCSSE_MASK                       (0x2000000U)
#define SPI_MCR_PCSSE_SHIFT                      (25U)
#define SPI_MCR_PCSSE(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_MCR_PCSSE_SHIFT)) & SPI_MCR_PCSSE_MASK)
#define SPI_MCR_MTFE_MASK                        (0x4000000U)
#define SPI_MCR_MTFE_SHIFT                       (26U)
#define SPI_MCR_MTFE(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_MCR_MTFE_SHIFT)) & SPI_MCR_MTFE_MASK)
#define SPI_MCR_FRZ_MASK                         (0x8000000U)
#define SPI_MCR_FRZ_SHIFT                        (27U)
#define SPI_MCR_FRZ(x)                           (((uint32_t)(((uint32_t)(x)) << SPI_MCR_FRZ_SHIFT)) & SPI_MCR_FRZ_MASK)
#define SPI_MCR_DCONF_MASK                       (0x30000000U)
#define SPI_MCR_DCONF_SHIFT                      (28U)
#define SPI_MCR_DCONF(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_MCR_DCONF_SHIFT)) & SPI_MCR_DCONF_MASK)
#define SPI_MCR_CONT_SCKE_MASK                   (0x40000000U)
#define SPI_MCR_CONT_SCKE_SHIFT                  (30U)
#define SPI_MCR_CONT_SCKE(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_MCR_CONT_SCKE_SHIFT)) & SPI_MCR_CONT_SCKE_MASK)
#define SPI_MCR_MSTR_MASK                        (0x80000000U)
#define SPI_MCR_MSTR_SHIFT                       (31U)
#define SPI_MCR_MSTR(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_MCR_MSTR_SHIFT)) & SPI_MCR_MSTR_MASK)

/*! @name TCR - Transfer Count Register */
#define SPI_TCR_SPI_TCNT_MASK                    (0xFFFF0000U)
#define SPI_TCR_SPI_TCNT_SHIFT                   (16U)
#define SPI_TCR_SPI_TCNT(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_TCR_SPI_TCNT_SHIFT)) & SPI_TCR_SPI_TCNT_MASK)

/*! @name CTAR - Clock and Transfer Attributes Register (In Master Mode) */
#define SPI_CTAR_BR_MASK                         (0xFU)
#define SPI_CTAR_BR_SHIFT                        (0U)
#define SPI_CTAR_BR(x)                           (((uint32_t)(((uint32_t)(x)) << SPI_CTAR_BR_SHIFT)) & SPI_CTAR_BR_MASK)
#define SPI_CTAR_DT_MASK                         (0xF0U)
#define SPI_CTAR_DT_SHIFT                        (4U)
#define SPI_CTAR_DT(x)                           (((uint32_t)(((uint32_t)(x)) << SPI_CTAR_DT_SHIFT)) & SPI_CTAR_DT_MASK)
#define SPI_CTAR_ASC_MASK                        (0xF00U)
#define SPI_CTAR_ASC_SHIFT                       (8U)
#define SPI_CTAR_ASC(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_CTAR_ASC_SHIFT)) & SPI_CTAR_ASC_MASK)
#define SPI_CTAR_CSSCK_MASK                      (0xF000U)
#define SPI_CTAR_CSSCK_SHIFT                     (12U)
#define SPI_CTAR_CSSCK(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_CTAR_CSSCK_SHIFT)) & SPI_CTAR_CSSCK_MASK)
#define SPI_CTAR_PBR_MASK                        (0x30000U)
#define SPI_CTAR_PBR_SHIFT                       (16U)
#define SPI_CTAR_PBR(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_CTAR_PBR_SHIFT)) & SPI_CTAR_PBR_MASK)
#define SPI_CTAR_PDT_MASK                        (0xC0000U)
#define SPI_CTAR_PDT_SHIFT                       (18U)
#define SPI_CTAR_PDT(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_CTAR_PDT_SHIFT)) & SPI_CTAR_PDT_MASK)
#define SPI_CTAR_PASC_MASK                       (0x300000U)
#define SPI_CTAR_PASC_SHIFT                      (20U)
#define SPI_CTAR_PASC(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_CTAR_PASC_SHIFT)) & SPI_CTAR_PASC_MASK)
#define SPI_CTAR_PCSSCK_MASK                     (0xC00000U)
#define SPI_CTAR_PCSSCK_SHIFT                    (22U)
#define SPI_CTAR_PCSSCK(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_CTAR_PCSSCK_SHIFT)) & SPI_CTAR_PCSSCK_MASK)
#define SPI_CTAR_LSBFE_MASK                      (0x1000000U)
#define SPI_CTAR_LSBFE_SHIFT                     (24U)
#define SPI_CTAR_LSBFE(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_CTAR_LSBFE_SHIFT)) & SPI_CTAR_LSBFE_MASK)
#define SPI_CTAR_CPHA_MASK                       (0x2000000U)
#define SPI_CTAR_CPHA_SHIFT                      (25U)
#define SPI_CTAR_CPHA(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_CTAR_CPHA_SHIFT)) & SPI_CTAR_CPHA_MASK)
#define SPI_CTAR_CPOL_MASK                       (0x4000000U)
#define SPI_CTAR_CPOL_SHIFT                      (26U)
#define SPI_CTAR_CPOL(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_CTAR_CPOL_SHIFT)) & SPI_CTAR_CPOL_MASK)
#define SPI_CTAR_FMSZ_MASK                       (0x78000000U)
#define SPI_CTAR_FMSZ_SHIFT                      (27U)
#define SPI_CTAR_FMSZ(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_CTAR_FMSZ_SHIFT)) & SPI_CTAR_FMSZ_MASK)
#define SPI_CTAR_DBR_MASK                        (0x80000000U)
#define SPI_CTAR_DBR_SHIFT                       (31U)
#define SPI_CTAR_DBR(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_CTAR_DBR_SHIFT)) & SPI_CTAR_DBR_MASK)

/* The count of SPI_CTAR */
#define SPI_CTAR_COUNT                           (2U)

/*! @name CTAR_SLAVE - Clock and Transfer Attributes Register (In Slave Mode) */
#define SPI_CTAR_SLAVE_CPHA_MASK                 (0x2000000U)
#define SPI_CTAR_SLAVE_CPHA_SHIFT                (25U)
#define SPI_CTAR_SLAVE_CPHA(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_CTAR_SLAVE_CPHA_SHIFT)) & SPI_CTAR_SLAVE_CPHA_MASK)
#define SPI_CTAR_SLAVE_CPOL_MASK                 (0x4000000U)
#define SPI_CTAR_SLAVE_CPOL_SHIFT                (26U)
#define SPI_CTAR_SLAVE_CPOL(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_CTAR_SLAVE_CPOL_SHIFT)) & SPI_CTAR_SLAVE_CPOL_MASK)
#define SPI_CTAR_SLAVE_FMSZ_MASK                 (0x78000000U)
#define SPI_CTAR_SLAVE_FMSZ_SHIFT                (27U)
#define SPI_CTAR_SLAVE_FMSZ(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_CTAR_SLAVE_FMSZ_SHIFT)) & SPI_CTAR_SLAVE_FMSZ_MASK)

/* The count of SPI_CTAR_SLAVE */
#define SPI_CTAR_SLAVE_COUNT                     (1U)

/*! @name SR - Status Register */
#define SPI_SR_POPNXTPTR_MASK                    (0xFU)
#define SPI_SR_POPNXTPTR_SHIFT                   (0U)
#define SPI_SR_POPNXTPTR(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_SR_POPNXTPTR_SHIFT)) & SPI_SR_POPNXTPTR_MASK)
#define SPI_SR_RXCTR_MASK                        (0xF0U)
#define SPI_SR_RXCTR_SHIFT                       (4U)
#define SPI_SR_RXCTR(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_SR_RXCTR_SHIFT)) & SPI_SR_RXCTR_MASK)
#define SPI_SR_TXNXTPTR_MASK                     (0xF00U)
#define SPI_SR_TXNXTPTR_SHIFT                    (8U)
#define SPI_SR_TXNXTPTR(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_SR_TXNXTPTR_SHIFT)) & SPI_SR_TXNXTPTR_MASK)
#define SPI_SR_TXCTR_MASK                        (0xF000U)
#define SPI_SR_TXCTR_SHIFT                       (12U)
#define SPI_SR_TXCTR(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_SR_TXCTR_SHIFT)) & SPI_SR_TXCTR_MASK)
#define SPI_SR_RFDF_MASK                         (0x20000U)
#define SPI_SR_RFDF_SHIFT                        (17U)
#define SPI_SR_RFDF(x)                           (((uint32_t)(((uint32_t)(x)) << SPI_SR_RFDF_SHIFT)) & SPI_SR_RFDF_MASK)
#define SPI_SR_RFOF_MASK                         (0x80000U)
#define SPI_SR_RFOF_SHIFT                        (19U)
#define SPI_SR_RFOF(x)                           (((uint32_t)(((uint32_t)(x)) << SPI_SR_RFOF_SHIFT)) & SPI_SR_RFOF_MASK)
#define SPI_SR_TFFF_MASK                         (0x2000000U)
#define SPI_SR_TFFF_SHIFT                        (25U)
#define SPI_SR_TFFF(x)                           (((uint32_t)(((uint32_t)(x)) << SPI_SR_TFFF_SHIFT)) & SPI_SR_TFFF_MASK)
#define SPI_SR_TFUF_MASK                         (0x8000000U)
#define SPI_SR_TFUF_SHIFT                        (27U)
#define SPI_SR_TFUF(x)                           (((uint32_t)(((uint32_t)(x)) << SPI_SR_TFUF_SHIFT)) & SPI_SR_TFUF_MASK)
#define SPI_SR_EOQF_MASK                         (0x10000000U)
#define SPI_SR_EOQF_SHIFT                        (28U)
#define SPI_SR_EOQF(x)                           (((uint32_t)(((uint32_t)(x)) << SPI_SR_EOQF_SHIFT)) & SPI_SR_EOQF_MASK)
#define SPI_SR_TXRXS_MASK                        (0x40000000U)
#define SPI_SR_TXRXS_SHIFT                       (30U)
#define SPI_SR_TXRXS(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_SR_TXRXS_SHIFT)) & SPI_SR_TXRXS_MASK)
#define SPI_SR_TCF_MASK                          (0x80000000U)
#define SPI_SR_TCF_SHIFT                         (31U)
#define SPI_SR_TCF(x)                            (((uint32_t)(((uint32_t)(x)) << SPI_SR_TCF_SHIFT)) & SPI_SR_TCF_MASK)

/*! @name RSER - DMA/Interrupt Request Select and Enable Register */
#define SPI_RSER_RFDF_DIRS_MASK                  (0x10000U)
#define SPI_RSER_RFDF_DIRS_SHIFT                 (16U)
#define SPI_RSER_RFDF_DIRS(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_RSER_RFDF_DIRS_SHIFT)) & SPI_RSER_RFDF_DIRS_MASK)
#define SPI_RSER_RFDF_RE_MASK                    (0x20000U)
#define SPI_RSER_RFDF_RE_SHIFT                   (17U)
#define SPI_RSER_RFDF_RE(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_RSER_RFDF_RE_SHIFT)) & SPI_RSER_RFDF_RE_MASK)
#define SPI_RSER_RFOF_RE_MASK                    (0x80000U)
#define SPI_RSER_RFOF_RE_SHIFT                   (19U)
#define SPI_RSER_RFOF_RE(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_RSER_RFOF_RE_SHIFT)) & SPI_RSER_RFOF_RE_MASK)
#define SPI_RSER_TFFF_DIRS_MASK                  (0x1000000U)
#define SPI_RSER_TFFF_DIRS_SHIFT                 (24U)
#define SPI_RSER_TFFF_DIRS(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_RSER_TFFF_DIRS_SHIFT)) & SPI_RSER_TFFF_DIRS_MASK)
#define SPI_RSER_TFFF_RE_MASK                    (0x2000000U)
#define SPI_RSER_TFFF_RE_SHIFT                   (25U)
#define SPI_RSER_TFFF_RE(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_RSER_TFFF_RE_SHIFT)) & SPI_RSER_TFFF_RE_MASK)
#define SPI_RSER_TFUF_RE_MASK                    (0x8000000U)
#define SPI_RSER_TFUF_RE_SHIFT                   (27U)
#define SPI_RSER_TFUF_RE(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_RSER_TFUF_RE_SHIFT)) & SPI_RSER_TFUF_RE_MASK)
#define SPI_RSER_EOQF_RE_MASK                    (0x10000000U)
#define SPI_RSER_EOQF_RE_SHIFT                   (28U)
#define SPI_RSER_EOQF_RE(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_RSER_EOQF_RE_SHIFT)) & SPI_RSER_EOQF_RE_MASK)
#define SPI_RSER_TCF_RE_MASK                     (0x80000000U)
#define SPI_RSER_TCF_RE_SHIFT                    (31U)
#define SPI_RSER_TCF_RE(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_RSER_TCF_RE_SHIFT)) & SPI_RSER_TCF_RE_MASK)

/*! @name PUSHR - PUSH TX FIFO Register In Master Mode */
#define SPI_PUSHR_TXDATA_MASK                    (0xFFFFU)
#define SPI_PUSHR_TXDATA_SHIFT                   (0U)
#define SPI_PUSHR_TXDATA(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_PUSHR_TXDATA_SHIFT)) & SPI_PUSHR_TXDATA_MASK)
#define SPI_PUSHR_PCS_MASK                       (0x3F0000U)
#define SPI_PUSHR_PCS_SHIFT                      (16U)
#define SPI_PUSHR_PCS(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_PUSHR_PCS_SHIFT)) & SPI_PUSHR_PCS_MASK)
#define SPI_PUSHR_CTCNT_MASK                     (0x4000000U)
#define SPI_PUSHR_CTCNT_SHIFT                    (26U)
#define SPI_PUSHR_CTCNT(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_PUSHR_CTCNT_SHIFT)) & SPI_PUSHR_CTCNT_MASK)
#define SPI_PUSHR_EOQ_MASK                       (0x8000000U)
#define SPI_PUSHR_EOQ_SHIFT                      (27U)
#define SPI_PUSHR_EOQ(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_PUSHR_EOQ_SHIFT)) & SPI_PUSHR_EOQ_MASK)
#define SPI_PUSHR_CTAS_MASK                      (0x70000000U)
#define SPI_PUSHR_CTAS_SHIFT                     (28U)
#define SPI_PUSHR_CTAS(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_PUSHR_CTAS_SHIFT)) & SPI_PUSHR_CTAS_MASK)
#define SPI_PUSHR_CONT_MASK                      (0x80000000U)
#define SPI_PUSHR_CONT_SHIFT                     (31U)
#define SPI_PUSHR_CONT(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_PUSHR_CONT_SHIFT)) & SPI_PUSHR_CONT_MASK)

/*! @name PUSHR_SLAVE - PUSH TX FIFO Register In Slave Mode */
#define SPI_PUSHR_SLAVE_TXDATA_MASK              (0xFFFFU)
#define SPI_PUSHR_SLAVE_TXDATA_SHIFT             (0U)
#define SPI_PUSHR_SLAVE_TXDATA(x)                (((uint32_t)(((uint32_t)(x)) << SPI_PUSHR_SLAVE_TXDATA_SHIFT)) & SPI_PUSHR_SLAVE_TXDATA_MASK)

/*! @name POPR - POP RX FIFO Register */
#define SPI_POPR_RXDATA_MASK                     (0xFFFFFFFFU)
#define SPI_POPR_RXDATA_SHIFT                    (0U)
#define SPI_POPR_RXDATA(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_POPR_RXDATA_SHIFT)) & SPI_POPR_RXDATA_MASK)

/*! @name TXFR0 - Transmit FIFO Registers */
#define SPI_TXFR0_TXDATA_MASK                    (0xFFFFU)
#define SPI_TXFR0_TXDATA_SHIFT                   (0U)
#define SPI_TXFR0_TXDATA(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_TXFR0_TXDATA_SHIFT)) & SPI_TXFR0_TXDATA_MASK)
#define SPI_TXFR0_TXCMD_TXDATA_MASK              (0xFFFF0000U)
#define SPI_TXFR0_TXCMD_TXDATA_SHIFT             (16U)
#define SPI_TXFR0_TXCMD_TXDATA(x)                (((uint32_t)(((uint32_t)(x)) << SPI_TXFR0_TXCMD_TXDATA_SHIFT)) & SPI_TXFR0_TXCMD_TXDATA_MASK)

/*! @name TXFR1 - Transmit FIFO Registers */
#define SPI_TXFR1_TXDATA_MASK                    (0xFFFFU)
#define SPI_TXFR1_TXDATA_SHIFT                   (0U)
#define SPI_TXFR1_TXDATA(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_TXFR1_TXDATA_SHIFT)) & SPI_TXFR1_TXDATA_MASK)
#define SPI_TXFR1_TXCMD_TXDATA_MASK              (0xFFFF0000U)
#define SPI_TXFR1_TXCMD_TXDATA_SHIFT             (16U)
#define SPI_TXFR1_TXCMD_TXDATA(x)                (((uint32_t)(((uint32_t)(x)) << SPI_TXFR1_TXCMD_TXDATA_SHIFT)) & SPI_TXFR1_TXCMD_TXDATA_MASK)

/*! @name TXFR2 - Transmit FIFO Registers */
#define SPI_TXFR2_TXDATA_MASK                    (0xFFFFU)
#define SPI_TXFR2_TXDATA_SHIFT                   (0U)
#define SPI_TXFR2_TXDATA(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_TXFR2_TXDATA_SHIFT)) & SPI_TXFR2_TXDATA_MASK)
#define SPI_TXFR2_TXCMD_TXDATA_MASK              (0xFFFF0000U)
#define SPI_TXFR2_TXCMD_TXDATA_SHIFT             (16U)
#define SPI_TXFR2_TXCMD_TXDATA(x)                (((uint32_t)(((uint32_t)(x)) << SPI_TXFR2_TXCMD_TXDATA_SHIFT)) & SPI_TXFR2_TXCMD_TXDATA_MASK)

/*! @name TXFR3 - Transmit FIFO Registers */
#define SPI_TXFR3_TXDATA_MASK                    (0xFFFFU)
#define SPI_TXFR3_TXDATA_SHIFT                   (0U)
#define SPI_TXFR3_TXDATA(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_TXFR3_TXDATA_SHIFT)) & SPI_TXFR3_TXDATA_MASK)
#define SPI_TXFR3_TXCMD_TXDATA_MASK              (0xFFFF0000U)
#define SPI_TXFR3_TXCMD_TXDATA_SHIFT             (16U)
#define SPI_TXFR3_TXCMD_TXDATA(x)                (((uint32_t)(((uint32_t)(x)) << SPI_TXFR3_TXCMD_TXDATA_SHIFT)) & SPI_TXFR3_TXCMD_TXDATA_MASK)

/*! @name RXFR0 - Receive FIFO Registers */
#define SPI_RXFR0_RXDATA_MASK                    (0xFFFFFFFFU)
#define SPI_RXFR0_RXDATA_SHIFT                   (0U)
#define SPI_RXFR0_RXDATA(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_RXFR0_RXDATA_SHIFT)) & SPI_RXFR0_RXDATA_MASK)

/*! @name RXFR1 - Receive FIFO Registers */
#define SPI_RXFR1_RXDATA_MASK                    (0xFFFFFFFFU)
#define SPI_RXFR1_RXDATA_SHIFT                   (0U)
#define SPI_RXFR1_RXDATA(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_RXFR1_RXDATA_SHIFT)) & SPI_RXFR1_RXDATA_MASK)

/*! @name RXFR2 - Receive FIFO Registers */
#define SPI_RXFR2_RXDATA_MASK                    (0xFFFFFFFFU)
#define SPI_RXFR2_RXDATA_SHIFT                   (0U)
#define SPI_RXFR2_RXDATA(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_RXFR2_RXDATA_SHIFT)) & SPI_RXFR2_RXDATA_MASK)

/*! @name RXFR3 - Receive FIFO Registers */
#define SPI_RXFR3_RXDATA_MASK                    (0xFFFFFFFFU)
#define SPI_RXFR3_RXDATA_SHIFT                   (0U)
#define SPI_RXFR3_RXDATA(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_RXFR3_RXDATA_SHIFT)) & SPI_RXFR3_RXDATA_MASK)


/*!
 * @}
 */ /* end of group SPI_Register_Masks */


/* SPI - Peripheral instance base addresses */
/** Peripheral SPI0 base address */
#define SPI0_BASE                                (0x4002C000u)
/** Peripheral SPI0 base pointer */
#define SPI0                                     ((SPI_Type *)SPI0_BASE)
/** Peripheral SPI1 base address */
#define SPI1_BASE                                (0x4002D000u)
/** Peripheral SPI1 base pointer */
#define SPI1                                     ((SPI_Type *)SPI1_BASE)
/** Peripheral SPI2 base address */
#define SPI2_BASE                                (0x400AC000u)
/** Peripheral SPI2 base pointer */
#define SPI2                                     ((SPI_Type *)SPI2_BASE)
/** Array initializer of SPI peripheral base addresses */
#define SPI_BASE_ADDRS                           { SPI0_BASE, SPI1_BASE, SPI2_BASE }
/** Array initializer of SPI peripheral base pointers */
#define SPI_BASE_PTRS                            { SPI0, SPI1, SPI2 }
/** Interrupt vectors for the SPI peripheral type */
#define SPI_IRQS                                 { SPI0_IRQn, SPI1_IRQn, SPI2_IRQn }

/*!
 * @}
 */ /* end of group SPI_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- TRNG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TRNG_Peripheral_Access_Layer TRNG Peripheral Access Layer
 * @{
 */

/** TRNG - Register Layout Typedef */
typedef struct {
  __IO uint32_t MCTL;                              /**< RNG Miscellaneous Control Register, offset: 0x0 */
  __IO uint32_t SCMISC;                            /**< RNG Statistical Check Miscellaneous Register, offset: 0x4 */
  __IO uint32_t PKRRNG;                            /**< RNG Poker Range Register, offset: 0x8 */
  union {                                          /* offset: 0xC */
    __IO uint32_t PKRMAX;                            /**< RNG Poker Maximum Limit Register, offset: 0xC */
    __I  uint32_t PKRSQ;                             /**< RNG Poker Square Calculation Result Register, offset: 0xC */
  };
  __IO uint32_t SDCTL;                             /**< RNG Seed Control Register, offset: 0x10 */
  union {                                          /* offset: 0x14 */
    __IO uint32_t SBLIM;                             /**< RNG Sparse Bit Limit Register, offset: 0x14 */
    __I  uint32_t TOTSAM;                            /**< RNG Total Samples Register, offset: 0x14 */
  };
  __IO uint32_t FRQMIN;                            /**< RNG Frequency Count Minimum Limit Register, offset: 0x18 */
  union {                                          /* offset: 0x1C */
    __I  uint32_t FRQCNT;                            /**< RNG Frequency Count Register, offset: 0x1C */
    __IO uint32_t FRQMAX;                            /**< RNG Frequency Count Maximum Limit Register, offset: 0x1C */
  };
  union {                                          /* offset: 0x20 */
    __I  uint32_t SCMC;                              /**< RNG Statistical Check Monobit Count Register, offset: 0x20 */
    __IO uint32_t SCML;                              /**< RNG Statistical Check Monobit Limit Register, offset: 0x20 */
  };
  union {                                          /* offset: 0x24 */
    __I  uint32_t SCR1C;                             /**< RNG Statistical Check Run Length 1 Count Register, offset: 0x24 */
    __IO uint32_t SCR1L;                             /**< RNG Statistical Check Run Length 1 Limit Register, offset: 0x24 */
  };
  union {                                          /* offset: 0x28 */
    __I  uint32_t SCR2C;                             /**< RNG Statistical Check Run Length 2 Count Register, offset: 0x28 */
    __IO uint32_t SCR2L;                             /**< RNG Statistical Check Run Length 2 Limit Register, offset: 0x28 */
  };
  union {                                          /* offset: 0x2C */
    __I  uint32_t SCR3C;                             /**< RNG Statistical Check Run Length 3 Count Register, offset: 0x2C */
    __IO uint32_t SCR3L;                             /**< RNG Statistical Check Run Length 3 Limit Register, offset: 0x2C */
  };
  union {                                          /* offset: 0x30 */
    __I  uint32_t SCR4C;                             /**< RNG Statistical Check Run Length 4 Count Register, offset: 0x30 */
    __IO uint32_t SCR4L;                             /**< RNG Statistical Check Run Length 4 Limit Register, offset: 0x30 */
  };
  union {                                          /* offset: 0x34 */
    __I  uint32_t SCR5C;                             /**< RNG Statistical Check Run Length 5 Count Register, offset: 0x34 */
    __IO uint32_t SCR5L;                             /**< RNG Statistical Check Run Length 5 Limit Register, offset: 0x34 */
  };
  union {                                          /* offset: 0x38 */
    __I  uint32_t SCR6PC;                            /**< RNG Statistical Check Run Length 6+ Count Register, offset: 0x38 */
    __IO uint32_t SCR6PL;                            /**< RNG Statistical Check Run Length 6+ Limit Register, offset: 0x38 */
  };
  __I  uint32_t STATUS;                            /**< RNG Status Register, offset: 0x3C */
  __I  uint32_t ENT[16];                           /**< RNG TRNG Entropy Read Register, array offset: 0x40, array step: 0x4 */
  __I  uint32_t PKRCNT10;                          /**< RNG Statistical Check Poker Count 1 and 0 Register, offset: 0x80 */
  __I  uint32_t PKRCNT32;                          /**< RNG Statistical Check Poker Count 3 and 2 Register, offset: 0x84 */
  __I  uint32_t PKRCNT54;                          /**< RNG Statistical Check Poker Count 5 and 4 Register, offset: 0x88 */
  __I  uint32_t PKRCNT76;                          /**< RNG Statistical Check Poker Count 7 and 6 Register, offset: 0x8C */
  __I  uint32_t PKRCNT98;                          /**< RNG Statistical Check Poker Count 9 and 8 Register, offset: 0x90 */
  __I  uint32_t PKRCNTBA;                          /**< RNG Statistical Check Poker Count B and A Register, offset: 0x94 */
  __I  uint32_t PKRCNTDC;                          /**< RNG Statistical Check Poker Count D and C Register, offset: 0x98 */
  __I  uint32_t PKRCNTFE;                          /**< RNG Statistical Check Poker Count F and E Register, offset: 0x9C */
       uint8_t RESERVED_0[16];
  __IO uint32_t SEC_CFG;                           /**< RNG Security Configuration Register, offset: 0xB0 */
  __IO uint32_t INT_CTRL;                          /**< RNG Interrupt Control Register, offset: 0xB4 */
  __IO uint32_t INT_MASK;                          /**< RNG Mask Register, offset: 0xB8 */
  __IO uint32_t INT_STATUS;                        /**< RNG Interrupt Status Register, offset: 0xBC */
       uint8_t RESERVED_1[48];
  __I  uint32_t VID1;                              /**< RNG Version ID Register (MS), offset: 0xF0 */
  __I  uint32_t VID2;                              /**< RNG Version ID Register (LS), offset: 0xF4 */
} TRNG_Type;

/* ----------------------------------------------------------------------------
   -- TRNG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TRNG_Register_Masks TRNG Register Masks
 * @{
 */

/*! @name MCTL - RNG Miscellaneous Control Register */
#define TRNG_MCTL_SAMP_MODE_MASK                 (0x3U)
#define TRNG_MCTL_SAMP_MODE_SHIFT                (0U)
#define TRNG_MCTL_SAMP_MODE(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_SAMP_MODE_SHIFT)) & TRNG_MCTL_SAMP_MODE_MASK)
#define TRNG_MCTL_OSC_DIV_MASK                   (0xCU)
#define TRNG_MCTL_OSC_DIV_SHIFT                  (2U)
#define TRNG_MCTL_OSC_DIV(x)                     (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_OSC_DIV_SHIFT)) & TRNG_MCTL_OSC_DIV_MASK)
#define TRNG_MCTL_UNUSED_MASK                    (0x10U)
#define TRNG_MCTL_UNUSED_SHIFT                   (4U)
#define TRNG_MCTL_UNUSED(x)                      (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_UNUSED_SHIFT)) & TRNG_MCTL_UNUSED_MASK)
#define TRNG_MCTL_TRNG_ACC_MASK                  (0x20U)
#define TRNG_MCTL_TRNG_ACC_SHIFT                 (5U)
#define TRNG_MCTL_TRNG_ACC(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_TRNG_ACC_SHIFT)) & TRNG_MCTL_TRNG_ACC_MASK)
#define TRNG_MCTL_RST_DEF_MASK                   (0x40U)
#define TRNG_MCTL_RST_DEF_SHIFT                  (6U)
#define TRNG_MCTL_RST_DEF(x)                     (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_RST_DEF_SHIFT)) & TRNG_MCTL_RST_DEF_MASK)
#define TRNG_MCTL_FOR_SCLK_MASK                  (0x80U)
#define TRNG_MCTL_FOR_SCLK_SHIFT                 (7U)
#define TRNG_MCTL_FOR_SCLK(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_FOR_SCLK_SHIFT)) & TRNG_MCTL_FOR_SCLK_MASK)
#define TRNG_MCTL_FCT_FAIL_MASK                  (0x100U)
#define TRNG_MCTL_FCT_FAIL_SHIFT                 (8U)
#define TRNG_MCTL_FCT_FAIL(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_FCT_FAIL_SHIFT)) & TRNG_MCTL_FCT_FAIL_MASK)
#define TRNG_MCTL_FCT_VAL_MASK                   (0x200U)
#define TRNG_MCTL_FCT_VAL_SHIFT                  (9U)
#define TRNG_MCTL_FCT_VAL(x)                     (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_FCT_VAL_SHIFT)) & TRNG_MCTL_FCT_VAL_MASK)
#define TRNG_MCTL_ENT_VAL_MASK                   (0x400U)
#define TRNG_MCTL_ENT_VAL_SHIFT                  (10U)
#define TRNG_MCTL_ENT_VAL(x)                     (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_ENT_VAL_SHIFT)) & TRNG_MCTL_ENT_VAL_MASK)
#define TRNG_MCTL_TST_OUT_MASK                   (0x800U)
#define TRNG_MCTL_TST_OUT_SHIFT                  (11U)
#define TRNG_MCTL_TST_OUT(x)                     (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_TST_OUT_SHIFT)) & TRNG_MCTL_TST_OUT_MASK)
#define TRNG_MCTL_ERR_MASK                       (0x1000U)
#define TRNG_MCTL_ERR_SHIFT                      (12U)
#define TRNG_MCTL_ERR(x)                         (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_ERR_SHIFT)) & TRNG_MCTL_ERR_MASK)
#define TRNG_MCTL_TSTOP_OK_MASK                  (0x2000U)
#define TRNG_MCTL_TSTOP_OK_SHIFT                 (13U)
#define TRNG_MCTL_TSTOP_OK(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_TSTOP_OK_SHIFT)) & TRNG_MCTL_TSTOP_OK_MASK)
#define TRNG_MCTL_PRGM_MASK                      (0x10000U)
#define TRNG_MCTL_PRGM_SHIFT                     (16U)
#define TRNG_MCTL_PRGM(x)                        (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_PRGM_SHIFT)) & TRNG_MCTL_PRGM_MASK)

/*! @name SCMISC - RNG Statistical Check Miscellaneous Register */
#define TRNG_SCMISC_LRUN_MAX_MASK                (0xFFU)
#define TRNG_SCMISC_LRUN_MAX_SHIFT               (0U)
#define TRNG_SCMISC_LRUN_MAX(x)                  (((uint32_t)(((uint32_t)(x)) << TRNG_SCMISC_LRUN_MAX_SHIFT)) & TRNG_SCMISC_LRUN_MAX_MASK)
#define TRNG_SCMISC_RTY_CT_MASK                  (0xF0000U)
#define TRNG_SCMISC_RTY_CT_SHIFT                 (16U)
#define TRNG_SCMISC_RTY_CT(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_SCMISC_RTY_CT_SHIFT)) & TRNG_SCMISC_RTY_CT_MASK)

/*! @name PKRRNG - RNG Poker Range Register */
#define TRNG_PKRRNG_PKR_RNG_MASK                 (0xFFFFU)
#define TRNG_PKRRNG_PKR_RNG_SHIFT                (0U)
#define TRNG_PKRRNG_PKR_RNG(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_PKRRNG_PKR_RNG_SHIFT)) & TRNG_PKRRNG_PKR_RNG_MASK)

/*! @name PKRMAX - RNG Poker Maximum Limit Register */
#define TRNG_PKRMAX_PKR_MAX_MASK                 (0xFFFFFFU)
#define TRNG_PKRMAX_PKR_MAX_SHIFT                (0U)
#define TRNG_PKRMAX_PKR_MAX(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_PKRMAX_PKR_MAX_SHIFT)) & TRNG_PKRMAX_PKR_MAX_MASK)

/*! @name PKRSQ - RNG Poker Square Calculation Result Register */
#define TRNG_PKRSQ_PKR_SQ_MASK                   (0xFFFFFFU)
#define TRNG_PKRSQ_PKR_SQ_SHIFT                  (0U)
#define TRNG_PKRSQ_PKR_SQ(x)                     (((uint32_t)(((uint32_t)(x)) << TRNG_PKRSQ_PKR_SQ_SHIFT)) & TRNG_PKRSQ_PKR_SQ_MASK)

/*! @name SDCTL - RNG Seed Control Register */
#define TRNG_SDCTL_SAMP_SIZE_MASK                (0xFFFFU)
#define TRNG_SDCTL_SAMP_SIZE_SHIFT               (0U)
#define TRNG_SDCTL_SAMP_SIZE(x)                  (((uint32_t)(((uint32_t)(x)) << TRNG_SDCTL_SAMP_SIZE_SHIFT)) & TRNG_SDCTL_SAMP_SIZE_MASK)
#define TRNG_SDCTL_ENT_DLY_MASK                  (0xFFFF0000U)
#define TRNG_SDCTL_ENT_DLY_SHIFT                 (16U)
#define TRNG_SDCTL_ENT_DLY(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_SDCTL_ENT_DLY_SHIFT)) & TRNG_SDCTL_ENT_DLY_MASK)

/*! @name SBLIM - RNG Sparse Bit Limit Register */
#define TRNG_SBLIM_SB_LIM_MASK                   (0x3FFU)
#define TRNG_SBLIM_SB_LIM_SHIFT                  (0U)
#define TRNG_SBLIM_SB_LIM(x)                     (((uint32_t)(((uint32_t)(x)) << TRNG_SBLIM_SB_LIM_SHIFT)) & TRNG_SBLIM_SB_LIM_MASK)

/*! @name TOTSAM - RNG Total Samples Register */
#define TRNG_TOTSAM_TOT_SAM_MASK                 (0xFFFFFU)
#define TRNG_TOTSAM_TOT_SAM_SHIFT                (0U)
#define TRNG_TOTSAM_TOT_SAM(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_TOTSAM_TOT_SAM_SHIFT)) & TRNG_TOTSAM_TOT_SAM_MASK)

/*! @name FRQMIN - RNG Frequency Count Minimum Limit Register */
#define TRNG_FRQMIN_FRQ_MIN_MASK                 (0x3FFFFFU)
#define TRNG_FRQMIN_FRQ_MIN_SHIFT                (0U)
#define TRNG_FRQMIN_FRQ_MIN(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_FRQMIN_FRQ_MIN_SHIFT)) & TRNG_FRQMIN_FRQ_MIN_MASK)

/*! @name FRQCNT - RNG Frequency Count Register */
#define TRNG_FRQCNT_FRQ_CT_MASK                  (0x3FFFFFU)
#define TRNG_FRQCNT_FRQ_CT_SHIFT                 (0U)
#define TRNG_FRQCNT_FRQ_CT(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_FRQCNT_FRQ_CT_SHIFT)) & TRNG_FRQCNT_FRQ_CT_MASK)

/*! @name FRQMAX - RNG Frequency Count Maximum Limit Register */
#define TRNG_FRQMAX_FRQ_MAX_MASK                 (0x3FFFFFU)
#define TRNG_FRQMAX_FRQ_MAX_SHIFT                (0U)
#define TRNG_FRQMAX_FRQ_MAX(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_FRQMAX_FRQ_MAX_SHIFT)) & TRNG_FRQMAX_FRQ_MAX_MASK)

/*! @name SCMC - RNG Statistical Check Monobit Count Register */
#define TRNG_SCMC_MONO_CT_MASK                   (0xFFFFU)
#define TRNG_SCMC_MONO_CT_SHIFT                  (0U)
#define TRNG_SCMC_MONO_CT(x)                     (((uint32_t)(((uint32_t)(x)) << TRNG_SCMC_MONO_CT_SHIFT)) & TRNG_SCMC_MONO_CT_MASK)

/*! @name SCML - RNG Statistical Check Monobit Limit Register */
#define TRNG_SCML_MONO_MAX_MASK                  (0xFFFFU)
#define TRNG_SCML_MONO_MAX_SHIFT                 (0U)
#define TRNG_SCML_MONO_MAX(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_SCML_MONO_MAX_SHIFT)) & TRNG_SCML_MONO_MAX_MASK)
#define TRNG_SCML_MONO_RNG_MASK                  (0xFFFF0000U)
#define TRNG_SCML_MONO_RNG_SHIFT                 (16U)
#define TRNG_SCML_MONO_RNG(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_SCML_MONO_RNG_SHIFT)) & TRNG_SCML_MONO_RNG_MASK)

/*! @name SCR1C - RNG Statistical Check Run Length 1 Count Register */
#define TRNG_SCR1C_R1_0_CT_MASK                  (0x7FFFU)
#define TRNG_SCR1C_R1_0_CT_SHIFT                 (0U)
#define TRNG_SCR1C_R1_0_CT(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_SCR1C_R1_0_CT_SHIFT)) & TRNG_SCR1C_R1_0_CT_MASK)
#define TRNG_SCR1C_R1_1_CT_MASK                  (0x7FFF0000U)
#define TRNG_SCR1C_R1_1_CT_SHIFT                 (16U)
#define TRNG_SCR1C_R1_1_CT(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_SCR1C_R1_1_CT_SHIFT)) & TRNG_SCR1C_R1_1_CT_MASK)

/*! @name SCR1L - RNG Statistical Check Run Length 1 Limit Register */
#define TRNG_SCR1L_RUN1_MAX_MASK                 (0x7FFFU)
#define TRNG_SCR1L_RUN1_MAX_SHIFT                (0U)
#define TRNG_SCR1L_RUN1_MAX(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_SCR1L_RUN1_MAX_SHIFT)) & TRNG_SCR1L_RUN1_MAX_MASK)
#define TRNG_SCR1L_RUN1_RNG_MASK                 (0x7FFF0000U)
#define TRNG_SCR1L_RUN1_RNG_SHIFT                (16U)
#define TRNG_SCR1L_RUN1_RNG(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_SCR1L_RUN1_RNG_SHIFT)) & TRNG_SCR1L_RUN1_RNG_MASK)

/*! @name SCR2C - RNG Statistical Check Run Length 2 Count Register */
#define TRNG_SCR2C_R2_0_CT_MASK                  (0x3FFFU)
#define TRNG_SCR2C_R2_0_CT_SHIFT                 (0U)
#define TRNG_SCR2C_R2_0_CT(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_SCR2C_R2_0_CT_SHIFT)) & TRNG_SCR2C_R2_0_CT_MASK)
#define TRNG_SCR2C_R2_1_CT_MASK                  (0x3FFF0000U)
#define TRNG_SCR2C_R2_1_CT_SHIFT                 (16U)
#define TRNG_SCR2C_R2_1_CT(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_SCR2C_R2_1_CT_SHIFT)) & TRNG_SCR2C_R2_1_CT_MASK)

/*! @name SCR2L - RNG Statistical Check Run Length 2 Limit Register */
#define TRNG_SCR2L_RUN2_MAX_MASK                 (0x3FFFU)
#define TRNG_SCR2L_RUN2_MAX_SHIFT                (0U)
#define TRNG_SCR2L_RUN2_MAX(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_SCR2L_RUN2_MAX_SHIFT)) & TRNG_SCR2L_RUN2_MAX_MASK)
#define TRNG_SCR2L_RUN2_RNG_MASK                 (0x3FFF0000U)
#define TRNG_SCR2L_RUN2_RNG_SHIFT                (16U)
#define TRNG_SCR2L_RUN2_RNG(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_SCR2L_RUN2_RNG_SHIFT)) & TRNG_SCR2L_RUN2_RNG_MASK)

/*! @name SCR3C - RNG Statistical Check Run Length 3 Count Register */
#define TRNG_SCR3C_R3_0_CT_MASK                  (0x1FFFU)
#define TRNG_SCR3C_R3_0_CT_SHIFT                 (0U)
#define TRNG_SCR3C_R3_0_CT(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_SCR3C_R3_0_CT_SHIFT)) & TRNG_SCR3C_R3_0_CT_MASK)
#define TRNG_SCR3C_R3_1_CT_MASK                  (0x1FFF0000U)
#define TRNG_SCR3C_R3_1_CT_SHIFT                 (16U)
#define TRNG_SCR3C_R3_1_CT(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_SCR3C_R3_1_CT_SHIFT)) & TRNG_SCR3C_R3_1_CT_MASK)

/*! @name SCR3L - RNG Statistical Check Run Length 3 Limit Register */
#define TRNG_SCR3L_RUN3_MAX_MASK                 (0x1FFFU)
#define TRNG_SCR3L_RUN3_MAX_SHIFT                (0U)
#define TRNG_SCR3L_RUN3_MAX(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_SCR3L_RUN3_MAX_SHIFT)) & TRNG_SCR3L_RUN3_MAX_MASK)
#define TRNG_SCR3L_RUN3_RNG_MASK                 (0x1FFF0000U)
#define TRNG_SCR3L_RUN3_RNG_SHIFT                (16U)
#define TRNG_SCR3L_RUN3_RNG(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_SCR3L_RUN3_RNG_SHIFT)) & TRNG_SCR3L_RUN3_RNG_MASK)

/*! @name SCR4C - RNG Statistical Check Run Length 4 Count Register */
#define TRNG_SCR4C_R4_0_CT_MASK                  (0xFFFU)
#define TRNG_SCR4C_R4_0_CT_SHIFT                 (0U)
#define TRNG_SCR4C_R4_0_CT(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_SCR4C_R4_0_CT_SHIFT)) & TRNG_SCR4C_R4_0_CT_MASK)
#define TRNG_SCR4C_R4_1_CT_MASK                  (0xFFF0000U)
#define TRNG_SCR4C_R4_1_CT_SHIFT                 (16U)
#define TRNG_SCR4C_R4_1_CT(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_SCR4C_R4_1_CT_SHIFT)) & TRNG_SCR4C_R4_1_CT_MASK)

/*! @name SCR4L - RNG Statistical Check Run Length 4 Limit Register */
#define TRNG_SCR4L_RUN4_MAX_MASK                 (0xFFFU)
#define TRNG_SCR4L_RUN4_MAX_SHIFT                (0U)
#define TRNG_SCR4L_RUN4_MAX(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_SCR4L_RUN4_MAX_SHIFT)) & TRNG_SCR4L_RUN4_MAX_MASK)
#define TRNG_SCR4L_RUN4_RNG_MASK                 (0xFFF0000U)
#define TRNG_SCR4L_RUN4_RNG_SHIFT                (16U)
#define TRNG_SCR4L_RUN4_RNG(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_SCR4L_RUN4_RNG_SHIFT)) & TRNG_SCR4L_RUN4_RNG_MASK)

/*! @name SCR5C - RNG Statistical Check Run Length 5 Count Register */
#define TRNG_SCR5C_R5_0_CT_MASK                  (0x7FFU)
#define TRNG_SCR5C_R5_0_CT_SHIFT                 (0U)
#define TRNG_SCR5C_R5_0_CT(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_SCR5C_R5_0_CT_SHIFT)) & TRNG_SCR5C_R5_0_CT_MASK)
#define TRNG_SCR5C_R5_1_CT_MASK                  (0x7FF0000U)
#define TRNG_SCR5C_R5_1_CT_SHIFT                 (16U)
#define TRNG_SCR5C_R5_1_CT(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_SCR5C_R5_1_CT_SHIFT)) & TRNG_SCR5C_R5_1_CT_MASK)

/*! @name SCR5L - RNG Statistical Check Run Length 5 Limit Register */
#define TRNG_SCR5L_RUN5_MAX_MASK                 (0x7FFU)
#define TRNG_SCR5L_RUN5_MAX_SHIFT                (0U)
#define TRNG_SCR5L_RUN5_MAX(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_SCR5L_RUN5_MAX_SHIFT)) & TRNG_SCR5L_RUN5_MAX_MASK)
#define TRNG_SCR5L_RUN5_RNG_MASK                 (0x7FF0000U)
#define TRNG_SCR5L_RUN5_RNG_SHIFT                (16U)
#define TRNG_SCR5L_RUN5_RNG(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_SCR5L_RUN5_RNG_SHIFT)) & TRNG_SCR5L_RUN5_RNG_MASK)

/*! @name SCR6PC - RNG Statistical Check Run Length 6+ Count Register */
#define TRNG_SCR6PC_R6P_0_CT_MASK                (0x7FFU)
#define TRNG_SCR6PC_R6P_0_CT_SHIFT               (0U)
#define TRNG_SCR6PC_R6P_0_CT(x)                  (((uint32_t)(((uint32_t)(x)) << TRNG_SCR6PC_R6P_0_CT_SHIFT)) & TRNG_SCR6PC_R6P_0_CT_MASK)
#define TRNG_SCR6PC_R6P_1_CT_MASK                (0x7FF0000U)
#define TRNG_SCR6PC_R6P_1_CT_SHIFT               (16U)
#define TRNG_SCR6PC_R6P_1_CT(x)                  (((uint32_t)(((uint32_t)(x)) << TRNG_SCR6PC_R6P_1_CT_SHIFT)) & TRNG_SCR6PC_R6P_1_CT_MASK)

/*! @name SCR6PL - RNG Statistical Check Run Length 6+ Limit Register */
#define TRNG_SCR6PL_RUN6P_MAX_MASK               (0x7FFU)
#define TRNG_SCR6PL_RUN6P_MAX_SHIFT              (0U)
#define TRNG_SCR6PL_RUN6P_MAX(x)                 (((uint32_t)(((uint32_t)(x)) << TRNG_SCR6PL_RUN6P_MAX_SHIFT)) & TRNG_SCR6PL_RUN6P_MAX_MASK)
#define TRNG_SCR6PL_RUN6P_RNG_MASK               (0x7FF0000U)
#define TRNG_SCR6PL_RUN6P_RNG_SHIFT              (16U)
#define TRNG_SCR6PL_RUN6P_RNG(x)                 (((uint32_t)(((uint32_t)(x)) << TRNG_SCR6PL_RUN6P_RNG_SHIFT)) & TRNG_SCR6PL_RUN6P_RNG_MASK)

/*! @name STATUS - RNG Status Register */
#define TRNG_STATUS_TF1BR0_MASK                  (0x1U)
#define TRNG_STATUS_TF1BR0_SHIFT                 (0U)
#define TRNG_STATUS_TF1BR0(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF1BR0_SHIFT)) & TRNG_STATUS_TF1BR0_MASK)
#define TRNG_STATUS_TF1BR1_MASK                  (0x2U)
#define TRNG_STATUS_TF1BR1_SHIFT                 (1U)
#define TRNG_STATUS_TF1BR1(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF1BR1_SHIFT)) & TRNG_STATUS_TF1BR1_MASK)
#define TRNG_STATUS_TF2BR0_MASK                  (0x4U)
#define TRNG_STATUS_TF2BR0_SHIFT                 (2U)
#define TRNG_STATUS_TF2BR0(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF2BR0_SHIFT)) & TRNG_STATUS_TF2BR0_MASK)
#define TRNG_STATUS_TF2BR1_MASK                  (0x8U)
#define TRNG_STATUS_TF2BR1_SHIFT                 (3U)
#define TRNG_STATUS_TF2BR1(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF2BR1_SHIFT)) & TRNG_STATUS_TF2BR1_MASK)
#define TRNG_STATUS_TF3BR0_MASK                  (0x10U)
#define TRNG_STATUS_TF3BR0_SHIFT                 (4U)
#define TRNG_STATUS_TF3BR0(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF3BR0_SHIFT)) & TRNG_STATUS_TF3BR0_MASK)
#define TRNG_STATUS_TF3BR1_MASK                  (0x20U)
#define TRNG_STATUS_TF3BR1_SHIFT                 (5U)
#define TRNG_STATUS_TF3BR1(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF3BR1_SHIFT)) & TRNG_STATUS_TF3BR1_MASK)
#define TRNG_STATUS_TF4BR0_MASK                  (0x40U)
#define TRNG_STATUS_TF4BR0_SHIFT                 (6U)
#define TRNG_STATUS_TF4BR0(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF4BR0_SHIFT)) & TRNG_STATUS_TF4BR0_MASK)
#define TRNG_STATUS_TF4BR1_MASK                  (0x80U)
#define TRNG_STATUS_TF4BR1_SHIFT                 (7U)
#define TRNG_STATUS_TF4BR1(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF4BR1_SHIFT)) & TRNG_STATUS_TF4BR1_MASK)
#define TRNG_STATUS_TF5BR0_MASK                  (0x100U)
#define TRNG_STATUS_TF5BR0_SHIFT                 (8U)
#define TRNG_STATUS_TF5BR0(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF5BR0_SHIFT)) & TRNG_STATUS_TF5BR0_MASK)
#define TRNG_STATUS_TF5BR1_MASK                  (0x200U)
#define TRNG_STATUS_TF5BR1_SHIFT                 (9U)
#define TRNG_STATUS_TF5BR1(x)                    (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF5BR1_SHIFT)) & TRNG_STATUS_TF5BR1_MASK)
#define TRNG_STATUS_TF6PBR0_MASK                 (0x400U)
#define TRNG_STATUS_TF6PBR0_SHIFT                (10U)
#define TRNG_STATUS_TF6PBR0(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF6PBR0_SHIFT)) & TRNG_STATUS_TF6PBR0_MASK)
#define TRNG_STATUS_TF6PBR1_MASK                 (0x800U)
#define TRNG_STATUS_TF6PBR1_SHIFT                (11U)
#define TRNG_STATUS_TF6PBR1(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF6PBR1_SHIFT)) & TRNG_STATUS_TF6PBR1_MASK)
#define TRNG_STATUS_TFSB_MASK                    (0x1000U)
#define TRNG_STATUS_TFSB_SHIFT                   (12U)
#define TRNG_STATUS_TFSB(x)                      (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TFSB_SHIFT)) & TRNG_STATUS_TFSB_MASK)
#define TRNG_STATUS_TFLR_MASK                    (0x2000U)
#define TRNG_STATUS_TFLR_SHIFT                   (13U)
#define TRNG_STATUS_TFLR(x)                      (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TFLR_SHIFT)) & TRNG_STATUS_TFLR_MASK)
#define TRNG_STATUS_TFP_MASK                     (0x4000U)
#define TRNG_STATUS_TFP_SHIFT                    (14U)
#define TRNG_STATUS_TFP(x)                       (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TFP_SHIFT)) & TRNG_STATUS_TFP_MASK)
#define TRNG_STATUS_TFMB_MASK                    (0x8000U)
#define TRNG_STATUS_TFMB_SHIFT                   (15U)
#define TRNG_STATUS_TFMB(x)                      (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TFMB_SHIFT)) & TRNG_STATUS_TFMB_MASK)
#define TRNG_STATUS_RETRY_CT_MASK                (0xF0000U)
#define TRNG_STATUS_RETRY_CT_SHIFT               (16U)
#define TRNG_STATUS_RETRY_CT(x)                  (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_RETRY_CT_SHIFT)) & TRNG_STATUS_RETRY_CT_MASK)

/*! @name ENT - RNG TRNG Entropy Read Register */
#define TRNG_ENT_ENT_MASK                        (0xFFFFFFFFU)
#define TRNG_ENT_ENT_SHIFT                       (0U)
#define TRNG_ENT_ENT(x)                          (((uint32_t)(((uint32_t)(x)) << TRNG_ENT_ENT_SHIFT)) & TRNG_ENT_ENT_MASK)

/* The count of TRNG_ENT */
#define TRNG_ENT_COUNT                           (16U)

/*! @name PKRCNT10 - RNG Statistical Check Poker Count 1 and 0 Register */
#define TRNG_PKRCNT10_PKR_0_CT_MASK              (0xFFFFU)
#define TRNG_PKRCNT10_PKR_0_CT_SHIFT             (0U)
#define TRNG_PKRCNT10_PKR_0_CT(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT10_PKR_0_CT_SHIFT)) & TRNG_PKRCNT10_PKR_0_CT_MASK)
#define TRNG_PKRCNT10_PKR_1_CT_MASK              (0xFFFF0000U)
#define TRNG_PKRCNT10_PKR_1_CT_SHIFT             (16U)
#define TRNG_PKRCNT10_PKR_1_CT(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT10_PKR_1_CT_SHIFT)) & TRNG_PKRCNT10_PKR_1_CT_MASK)

/*! @name PKRCNT32 - RNG Statistical Check Poker Count 3 and 2 Register */
#define TRNG_PKRCNT32_PKR_2_CT_MASK              (0xFFFFU)
#define TRNG_PKRCNT32_PKR_2_CT_SHIFT             (0U)
#define TRNG_PKRCNT32_PKR_2_CT(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT32_PKR_2_CT_SHIFT)) & TRNG_PKRCNT32_PKR_2_CT_MASK)
#define TRNG_PKRCNT32_PKR_3_CT_MASK              (0xFFFF0000U)
#define TRNG_PKRCNT32_PKR_3_CT_SHIFT             (16U)
#define TRNG_PKRCNT32_PKR_3_CT(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT32_PKR_3_CT_SHIFT)) & TRNG_PKRCNT32_PKR_3_CT_MASK)

/*! @name PKRCNT54 - RNG Statistical Check Poker Count 5 and 4 Register */
#define TRNG_PKRCNT54_PKR_4_CT_MASK              (0xFFFFU)
#define TRNG_PKRCNT54_PKR_4_CT_SHIFT             (0U)
#define TRNG_PKRCNT54_PKR_4_CT(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT54_PKR_4_CT_SHIFT)) & TRNG_PKRCNT54_PKR_4_CT_MASK)
#define TRNG_PKRCNT54_PKR_5_CT_MASK              (0xFFFF0000U)
#define TRNG_PKRCNT54_PKR_5_CT_SHIFT             (16U)
#define TRNG_PKRCNT54_PKR_5_CT(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT54_PKR_5_CT_SHIFT)) & TRNG_PKRCNT54_PKR_5_CT_MASK)

/*! @name PKRCNT76 - RNG Statistical Check Poker Count 7 and 6 Register */
#define TRNG_PKRCNT76_PKR_6_CT_MASK              (0xFFFFU)
#define TRNG_PKRCNT76_PKR_6_CT_SHIFT             (0U)
#define TRNG_PKRCNT76_PKR_6_CT(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT76_PKR_6_CT_SHIFT)) & TRNG_PKRCNT76_PKR_6_CT_MASK)
#define TRNG_PKRCNT76_PKR_7_CT_MASK              (0xFFFF0000U)
#define TRNG_PKRCNT76_PKR_7_CT_SHIFT             (16U)
#define TRNG_PKRCNT76_PKR_7_CT(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT76_PKR_7_CT_SHIFT)) & TRNG_PKRCNT76_PKR_7_CT_MASK)

/*! @name PKRCNT98 - RNG Statistical Check Poker Count 9 and 8 Register */
#define TRNG_PKRCNT98_PKR_8_CT_MASK              (0xFFFFU)
#define TRNG_PKRCNT98_PKR_8_CT_SHIFT             (0U)
#define TRNG_PKRCNT98_PKR_8_CT(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT98_PKR_8_CT_SHIFT)) & TRNG_PKRCNT98_PKR_8_CT_MASK)
#define TRNG_PKRCNT98_PKR_9_CT_MASK              (0xFFFF0000U)
#define TRNG_PKRCNT98_PKR_9_CT_SHIFT             (16U)
#define TRNG_PKRCNT98_PKR_9_CT(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT98_PKR_9_CT_SHIFT)) & TRNG_PKRCNT98_PKR_9_CT_MASK)

/*! @name PKRCNTBA - RNG Statistical Check Poker Count B and A Register */
#define TRNG_PKRCNTBA_PKR_A_CT_MASK              (0xFFFFU)
#define TRNG_PKRCNTBA_PKR_A_CT_SHIFT             (0U)
#define TRNG_PKRCNTBA_PKR_A_CT(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNTBA_PKR_A_CT_SHIFT)) & TRNG_PKRCNTBA_PKR_A_CT_MASK)
#define TRNG_PKRCNTBA_PKR_B_CT_MASK              (0xFFFF0000U)
#define TRNG_PKRCNTBA_PKR_B_CT_SHIFT             (16U)
#define TRNG_PKRCNTBA_PKR_B_CT(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNTBA_PKR_B_CT_SHIFT)) & TRNG_PKRCNTBA_PKR_B_CT_MASK)

/*! @name PKRCNTDC - RNG Statistical Check Poker Count D and C Register */
#define TRNG_PKRCNTDC_PKR_C_CT_MASK              (0xFFFFU)
#define TRNG_PKRCNTDC_PKR_C_CT_SHIFT             (0U)
#define TRNG_PKRCNTDC_PKR_C_CT(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNTDC_PKR_C_CT_SHIFT)) & TRNG_PKRCNTDC_PKR_C_CT_MASK)
#define TRNG_PKRCNTDC_PKR_D_CT_MASK              (0xFFFF0000U)
#define TRNG_PKRCNTDC_PKR_D_CT_SHIFT             (16U)
#define TRNG_PKRCNTDC_PKR_D_CT(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNTDC_PKR_D_CT_SHIFT)) & TRNG_PKRCNTDC_PKR_D_CT_MASK)

/*! @name PKRCNTFE - RNG Statistical Check Poker Count F and E Register */
#define TRNG_PKRCNTFE_PKR_E_CT_MASK              (0xFFFFU)
#define TRNG_PKRCNTFE_PKR_E_CT_SHIFT             (0U)
#define TRNG_PKRCNTFE_PKR_E_CT(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNTFE_PKR_E_CT_SHIFT)) & TRNG_PKRCNTFE_PKR_E_CT_MASK)
#define TRNG_PKRCNTFE_PKR_F_CT_MASK              (0xFFFF0000U)
#define TRNG_PKRCNTFE_PKR_F_CT_SHIFT             (16U)
#define TRNG_PKRCNTFE_PKR_F_CT(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNTFE_PKR_F_CT_SHIFT)) & TRNG_PKRCNTFE_PKR_F_CT_MASK)

/*! @name SEC_CFG - RNG Security Configuration Register */
#define TRNG_SEC_CFG_SH0_MASK                    (0x1U)
#define TRNG_SEC_CFG_SH0_SHIFT                   (0U)
#define TRNG_SEC_CFG_SH0(x)                      (((uint32_t)(((uint32_t)(x)) << TRNG_SEC_CFG_SH0_SHIFT)) & TRNG_SEC_CFG_SH0_MASK)
#define TRNG_SEC_CFG_NO_PRGM_MASK                (0x2U)
#define TRNG_SEC_CFG_NO_PRGM_SHIFT               (1U)
#define TRNG_SEC_CFG_NO_PRGM(x)                  (((uint32_t)(((uint32_t)(x)) << TRNG_SEC_CFG_NO_PRGM_SHIFT)) & TRNG_SEC_CFG_NO_PRGM_MASK)
#define TRNG_SEC_CFG_SK_VAL_MASK                 (0x4U)
#define TRNG_SEC_CFG_SK_VAL_SHIFT                (2U)
#define TRNG_SEC_CFG_SK_VAL(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_SEC_CFG_SK_VAL_SHIFT)) & TRNG_SEC_CFG_SK_VAL_MASK)

/*! @name INT_CTRL - RNG Interrupt Control Register */
#define TRNG_INT_CTRL_HW_ERR_MASK                (0x1U)
#define TRNG_INT_CTRL_HW_ERR_SHIFT               (0U)
#define TRNG_INT_CTRL_HW_ERR(x)                  (((uint32_t)(((uint32_t)(x)) << TRNG_INT_CTRL_HW_ERR_SHIFT)) & TRNG_INT_CTRL_HW_ERR_MASK)
#define TRNG_INT_CTRL_ENT_VAL_MASK               (0x2U)
#define TRNG_INT_CTRL_ENT_VAL_SHIFT              (1U)
#define TRNG_INT_CTRL_ENT_VAL(x)                 (((uint32_t)(((uint32_t)(x)) << TRNG_INT_CTRL_ENT_VAL_SHIFT)) & TRNG_INT_CTRL_ENT_VAL_MASK)
#define TRNG_INT_CTRL_FRQ_CT_FAIL_MASK           (0x4U)
#define TRNG_INT_CTRL_FRQ_CT_FAIL_SHIFT          (2U)
#define TRNG_INT_CTRL_FRQ_CT_FAIL(x)             (((uint32_t)(((uint32_t)(x)) << TRNG_INT_CTRL_FRQ_CT_FAIL_SHIFT)) & TRNG_INT_CTRL_FRQ_CT_FAIL_MASK)
#define TRNG_INT_CTRL_UNUSED_MASK                (0xFFFFFFF8U)
#define TRNG_INT_CTRL_UNUSED_SHIFT               (3U)
#define TRNG_INT_CTRL_UNUSED(x)                  (((uint32_t)(((uint32_t)(x)) << TRNG_INT_CTRL_UNUSED_SHIFT)) & TRNG_INT_CTRL_UNUSED_MASK)

/*! @name INT_MASK - RNG Mask Register */
#define TRNG_INT_MASK_HW_ERR_MASK                (0x1U)
#define TRNG_INT_MASK_HW_ERR_SHIFT               (0U)
#define TRNG_INT_MASK_HW_ERR(x)                  (((uint32_t)(((uint32_t)(x)) << TRNG_INT_MASK_HW_ERR_SHIFT)) & TRNG_INT_MASK_HW_ERR_MASK)
#define TRNG_INT_MASK_ENT_VAL_MASK               (0x2U)
#define TRNG_INT_MASK_ENT_VAL_SHIFT              (1U)
#define TRNG_INT_MASK_ENT_VAL(x)                 (((uint32_t)(((uint32_t)(x)) << TRNG_INT_MASK_ENT_VAL_SHIFT)) & TRNG_INT_MASK_ENT_VAL_MASK)
#define TRNG_INT_MASK_FRQ_CT_FAIL_MASK           (0x4U)
#define TRNG_INT_MASK_FRQ_CT_FAIL_SHIFT          (2U)
#define TRNG_INT_MASK_FRQ_CT_FAIL(x)             (((uint32_t)(((uint32_t)(x)) << TRNG_INT_MASK_FRQ_CT_FAIL_SHIFT)) & TRNG_INT_MASK_FRQ_CT_FAIL_MASK)

/*! @name INT_STATUS - RNG Interrupt Status Register */
#define TRNG_INT_STATUS_HW_ERR_MASK              (0x1U)
#define TRNG_INT_STATUS_HW_ERR_SHIFT             (0U)
#define TRNG_INT_STATUS_HW_ERR(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_INT_STATUS_HW_ERR_SHIFT)) & TRNG_INT_STATUS_HW_ERR_MASK)
#define TRNG_INT_STATUS_ENT_VAL_MASK             (0x2U)
#define TRNG_INT_STATUS_ENT_VAL_SHIFT            (1U)
#define TRNG_INT_STATUS_ENT_VAL(x)               (((uint32_t)(((uint32_t)(x)) << TRNG_INT_STATUS_ENT_VAL_SHIFT)) & TRNG_INT_STATUS_ENT_VAL_MASK)
#define TRNG_INT_STATUS_FRQ_CT_FAIL_MASK         (0x4U)
#define TRNG_INT_STATUS_FRQ_CT_FAIL_SHIFT        (2U)
#define TRNG_INT_STATUS_FRQ_CT_FAIL(x)           (((uint32_t)(((uint32_t)(x)) << TRNG_INT_STATUS_FRQ_CT_FAIL_SHIFT)) & TRNG_INT_STATUS_FRQ_CT_FAIL_MASK)

/*! @name VID1 - RNG Version ID Register (MS) */
#define TRNG_VID1_RNG_MIN_REV_MASK               (0xFFU)
#define TRNG_VID1_RNG_MIN_REV_SHIFT              (0U)
#define TRNG_VID1_RNG_MIN_REV(x)                 (((uint32_t)(((uint32_t)(x)) << TRNG_VID1_RNG_MIN_REV_SHIFT)) & TRNG_VID1_RNG_MIN_REV_MASK)
#define TRNG_VID1_RNG_MAJ_REV_MASK               (0xFF00U)
#define TRNG_VID1_RNG_MAJ_REV_SHIFT              (8U)
#define TRNG_VID1_RNG_MAJ_REV(x)                 (((uint32_t)(((uint32_t)(x)) << TRNG_VID1_RNG_MAJ_REV_SHIFT)) & TRNG_VID1_RNG_MAJ_REV_MASK)
#define TRNG_VID1_RNG_IP_ID_MASK                 (0xFFFF0000U)
#define TRNG_VID1_RNG_IP_ID_SHIFT                (16U)
#define TRNG_VID1_RNG_IP_ID(x)                   (((uint32_t)(((uint32_t)(x)) << TRNG_VID1_RNG_IP_ID_SHIFT)) & TRNG_VID1_RNG_IP_ID_MASK)

/*! @name VID2 - RNG Version ID Register (LS) */
#define TRNG_VID2_RNG_CONFIG_OPT_MASK            (0xFFU)
#define TRNG_VID2_RNG_CONFIG_OPT_SHIFT           (0U)
#define TRNG_VID2_RNG_CONFIG_OPT(x)              (((uint32_t)(((uint32_t)(x)) << TRNG_VID2_RNG_CONFIG_OPT_SHIFT)) & TRNG_VID2_RNG_CONFIG_OPT_MASK)
#define TRNG_VID2_RNG_ECO_REV_MASK               (0xFF00U)
#define TRNG_VID2_RNG_ECO_REV_SHIFT              (8U)
#define TRNG_VID2_RNG_ECO_REV(x)                 (((uint32_t)(((uint32_t)(x)) << TRNG_VID2_RNG_ECO_REV_SHIFT)) & TRNG_VID2_RNG_ECO_REV_MASK)
#define TRNG_VID2_RNG_INTG_OPT_MASK              (0xFF0000U)
#define TRNG_VID2_RNG_INTG_OPT_SHIFT             (16U)
#define TRNG_VID2_RNG_INTG_OPT(x)                (((uint32_t)(((uint32_t)(x)) << TRNG_VID2_RNG_INTG_OPT_SHIFT)) & TRNG_VID2_RNG_INTG_OPT_MASK)
#define TRNG_VID2_RNG_ERA_MASK                   (0xFF000000U)
#define TRNG_VID2_RNG_ERA_SHIFT                  (24U)
#define TRNG_VID2_RNG_ERA(x)                     (((uint32_t)(((uint32_t)(x)) << TRNG_VID2_RNG_ERA_SHIFT)) & TRNG_VID2_RNG_ERA_MASK)


/*!
 * @}
 */ /* end of group TRNG_Register_Masks */


/* TRNG - Peripheral instance base addresses */
/** Peripheral TRNG0 base address */
#define TRNG0_BASE                               (0x400A0000u)
/** Peripheral TRNG0 base pointer */
#define TRNG0                                    ((TRNG_Type *)TRNG0_BASE)
/** Array initializer of TRNG peripheral base addresses */
#define TRNG_BASE_ADDRS                          { TRNG0_BASE }
/** Array initializer of TRNG peripheral base pointers */
#define TRNG_BASE_PTRS                           { TRNG0 }
/** Interrupt vectors for the TRNG peripheral type */
#define TRNG_IRQS                                { TRNG0_IRQn }

/*!
 * @}
 */ /* end of group TRNG_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- UART Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Peripheral_Access_Layer UART Peripheral Access Layer
 * @{
 */

/** UART - Register Layout Typedef */
typedef struct {
  __IO uint8_t BDH;                                /**< UART Baud Rate Registers: High, offset: 0x0 */
  __IO uint8_t BDL;                                /**< UART Baud Rate Registers: Low, offset: 0x1 */
  __IO uint8_t C1;                                 /**< UART Control Register 1, offset: 0x2 */
  __IO uint8_t C2;                                 /**< UART Control Register 2, offset: 0x3 */
  __I  uint8_t S1;                                 /**< UART Status Register 1, offset: 0x4 */
  __IO uint8_t S2;                                 /**< UART Status Register 2, offset: 0x5 */
  __IO uint8_t C3;                                 /**< UART Control Register 3, offset: 0x6 */
  __IO uint8_t D;                                  /**< UART Data Register, offset: 0x7 */
  __IO uint8_t MA1;                                /**< UART Match Address Registers 1, offset: 0x8 */
  __IO uint8_t MA2;                                /**< UART Match Address Registers 2, offset: 0x9 */
  __IO uint8_t C4;                                 /**< UART Control Register 4, offset: 0xA */
  __IO uint8_t C5;                                 /**< UART Control Register 5, offset: 0xB */
  __I  uint8_t ED;                                 /**< UART Extended Data Register, offset: 0xC */
  __IO uint8_t MODEM;                              /**< UART Modem Register, offset: 0xD */
  __IO uint8_t IR;                                 /**< UART Infrared Register, offset: 0xE */
       uint8_t RESERVED_0[1];
  __IO uint8_t PFIFO;                              /**< UART FIFO Parameters, offset: 0x10 */
  __IO uint8_t CFIFO;                              /**< UART FIFO Control Register, offset: 0x11 */
  __IO uint8_t SFIFO;                              /**< UART FIFO Status Register, offset: 0x12 */
  __IO uint8_t TWFIFO;                             /**< UART FIFO Transmit Watermark, offset: 0x13 */
  __I  uint8_t TCFIFO;                             /**< UART FIFO Transmit Count, offset: 0x14 */
  __IO uint8_t RWFIFO;                             /**< UART FIFO Receive Watermark, offset: 0x15 */
  __I  uint8_t RCFIFO;                             /**< UART FIFO Receive Count, offset: 0x16 */
       uint8_t RESERVED_1[1];
  __IO uint8_t C7816;                              /**< UART 7816 Control Register, offset: 0x18 */
  __IO uint8_t IE7816;                             /**< UART 7816 Interrupt Enable Register, offset: 0x19 */
  __IO uint8_t IS7816;                             /**< UART 7816 Interrupt Status Register, offset: 0x1A */
  __IO uint8_t WP7816;                             /**< UART 7816 Wait Parameter Register, offset: 0x1B */
  __IO uint8_t WN7816;                             /**< UART 7816 Wait N Register, offset: 0x1C */
  __IO uint8_t WF7816;                             /**< UART 7816 Wait FD Register, offset: 0x1D */
  __IO uint8_t ET7816;                             /**< UART 7816 Error Threshold Register, offset: 0x1E */
  __IO uint8_t TL7816;                             /**< UART 7816 Transmit Length Register, offset: 0x1F */
       uint8_t RESERVED_2[26];
  __IO uint8_t AP7816A_T0;                         /**< UART 7816 ATR Duration Timer Register A, offset: 0x3A */
  __IO uint8_t AP7816B_T0;                         /**< UART 7816 ATR Duration Timer Register B, offset: 0x3B */
  union {                                          /* offset: 0x3C */
    struct {                                         /* offset: 0x3C */
      __IO uint8_t WP7816A_T0;                         /**< UART 7816 Wait Parameter Register A, offset: 0x3C */
      __IO uint8_t WP7816B_T0;                         /**< UART 7816 Wait Parameter Register B, offset: 0x3D */
    } TYPE0;
    struct {                                         /* offset: 0x3C */
      __IO uint8_t WP7816A_T1;                         /**< UART 7816 Wait Parameter Register A, offset: 0x3C */
      __IO uint8_t WP7816B_T1;                         /**< UART 7816 Wait Parameter Register B, offset: 0x3D */
    } TYPE1;
  };
  __IO uint8_t WGP7816_T1;                         /**< UART 7816 Wait and Guard Parameter Register, offset: 0x3E */
  __IO uint8_t WP7816C_T1;                         /**< UART 7816 Wait Parameter Register C, offset: 0x3F */
} UART_Type;

/* ----------------------------------------------------------------------------
   -- UART Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Masks UART Register Masks
 * @{
 */

/*! @name BDH - UART Baud Rate Registers: High */
#define UART_BDH_SBR_MASK                        (0x1FU)
#define UART_BDH_SBR_SHIFT                       (0U)
#define UART_BDH_SBR(x)                          (((uint8_t)(((uint8_t)(x)) << UART_BDH_SBR_SHIFT)) & UART_BDH_SBR_MASK)
#define UART_BDH_SBNS_MASK                       (0x20U)
#define UART_BDH_SBNS_SHIFT                      (5U)
#define UART_BDH_SBNS(x)                         (((uint8_t)(((uint8_t)(x)) << UART_BDH_SBNS_SHIFT)) & UART_BDH_SBNS_MASK)
#define UART_BDH_RXEDGIE_MASK                    (0x40U)
#define UART_BDH_RXEDGIE_SHIFT                   (6U)
#define UART_BDH_RXEDGIE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_BDH_RXEDGIE_SHIFT)) & UART_BDH_RXEDGIE_MASK)
#define UART_BDH_LBKDIE_MASK                     (0x80U)
#define UART_BDH_LBKDIE_SHIFT                    (7U)
#define UART_BDH_LBKDIE(x)                       (((uint8_t)(((uint8_t)(x)) << UART_BDH_LBKDIE_SHIFT)) & UART_BDH_LBKDIE_MASK)

/*! @name BDL - UART Baud Rate Registers: Low */
#define UART_BDL_SBR_MASK                        (0xFFU)
#define UART_BDL_SBR_SHIFT                       (0U)
#define UART_BDL_SBR(x)                          (((uint8_t)(((uint8_t)(x)) << UART_BDL_SBR_SHIFT)) & UART_BDL_SBR_MASK)

/*! @name C1 - UART Control Register 1 */
#define UART_C1_PT_MASK                          (0x1U)
#define UART_C1_PT_SHIFT                         (0U)
#define UART_C1_PT(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C1_PT_SHIFT)) & UART_C1_PT_MASK)
#define UART_C1_PE_MASK                          (0x2U)
#define UART_C1_PE_SHIFT                         (1U)
#define UART_C1_PE(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C1_PE_SHIFT)) & UART_C1_PE_MASK)
#define UART_C1_ILT_MASK                         (0x4U)
#define UART_C1_ILT_SHIFT                        (2U)
#define UART_C1_ILT(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C1_ILT_SHIFT)) & UART_C1_ILT_MASK)
#define UART_C1_WAKE_MASK                        (0x8U)
#define UART_C1_WAKE_SHIFT                       (3U)
#define UART_C1_WAKE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C1_WAKE_SHIFT)) & UART_C1_WAKE_MASK)
#define UART_C1_M_MASK                           (0x10U)
#define UART_C1_M_SHIFT                          (4U)
#define UART_C1_M(x)                             (((uint8_t)(((uint8_t)(x)) << UART_C1_M_SHIFT)) & UART_C1_M_MASK)
#define UART_C1_RSRC_MASK                        (0x20U)
#define UART_C1_RSRC_SHIFT                       (5U)
#define UART_C1_RSRC(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C1_RSRC_SHIFT)) & UART_C1_RSRC_MASK)
#define UART_C1_UARTSWAI_MASK                    (0x40U)
#define UART_C1_UARTSWAI_SHIFT                   (6U)
#define UART_C1_UARTSWAI(x)                      (((uint8_t)(((uint8_t)(x)) << UART_C1_UARTSWAI_SHIFT)) & UART_C1_UARTSWAI_MASK)
#define UART_C1_LOOPS_MASK                       (0x80U)
#define UART_C1_LOOPS_SHIFT                      (7U)
#define UART_C1_LOOPS(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C1_LOOPS_SHIFT)) & UART_C1_LOOPS_MASK)

/*! @name C2 - UART Control Register 2 */
#define UART_C2_SBK_MASK                         (0x1U)
#define UART_C2_SBK_SHIFT                        (0U)
#define UART_C2_SBK(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C2_SBK_SHIFT)) & UART_C2_SBK_MASK)
#define UART_C2_RWU_MASK                         (0x2U)
#define UART_C2_RWU_SHIFT                        (1U)
#define UART_C2_RWU(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C2_RWU_SHIFT)) & UART_C2_RWU_MASK)
#define UART_C2_RE_MASK                          (0x4U)
#define UART_C2_RE_SHIFT                         (2U)
#define UART_C2_RE(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C2_RE_SHIFT)) & UART_C2_RE_MASK)
#define UART_C2_TE_MASK                          (0x8U)
#define UART_C2_TE_SHIFT                         (3U)
#define UART_C2_TE(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C2_TE_SHIFT)) & UART_C2_TE_MASK)
#define UART_C2_ILIE_MASK                        (0x10U)
#define UART_C2_ILIE_SHIFT                       (4U)
#define UART_C2_ILIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C2_ILIE_SHIFT)) & UART_C2_ILIE_MASK)
#define UART_C2_RIE_MASK                         (0x20U)
#define UART_C2_RIE_SHIFT                        (5U)
#define UART_C2_RIE(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C2_RIE_SHIFT)) & UART_C2_RIE_MASK)
#define UART_C2_TCIE_MASK                        (0x40U)
#define UART_C2_TCIE_SHIFT                       (6U)
#define UART_C2_TCIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C2_TCIE_SHIFT)) & UART_C2_TCIE_MASK)
#define UART_C2_TIE_MASK                         (0x80U)
#define UART_C2_TIE_SHIFT                        (7U)
#define UART_C2_TIE(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C2_TIE_SHIFT)) & UART_C2_TIE_MASK)

/*! @name S1 - UART Status Register 1 */
#define UART_S1_PF_MASK                          (0x1U)
#define UART_S1_PF_SHIFT                         (0U)
#define UART_S1_PF(x)                            (((uint8_t)(((uint8_t)(x)) << UART_S1_PF_SHIFT)) & UART_S1_PF_MASK)
#define UART_S1_FE_MASK                          (0x2U)
#define UART_S1_FE_SHIFT                         (1U)
#define UART_S1_FE(x)                            (((uint8_t)(((uint8_t)(x)) << UART_S1_FE_SHIFT)) & UART_S1_FE_MASK)
#define UART_S1_NF_MASK                          (0x4U)
#define UART_S1_NF_SHIFT                         (2U)
#define UART_S1_NF(x)                            (((uint8_t)(((uint8_t)(x)) << UART_S1_NF_SHIFT)) & UART_S1_NF_MASK)
#define UART_S1_OR_MASK                          (0x8U)
#define UART_S1_OR_SHIFT                         (3U)
#define UART_S1_OR(x)                            (((uint8_t)(((uint8_t)(x)) << UART_S1_OR_SHIFT)) & UART_S1_OR_MASK)
#define UART_S1_IDLE_MASK                        (0x10U)
#define UART_S1_IDLE_SHIFT                       (4U)
#define UART_S1_IDLE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_S1_IDLE_SHIFT)) & UART_S1_IDLE_MASK)
#define UART_S1_RDRF_MASK                        (0x20U)
#define UART_S1_RDRF_SHIFT                       (5U)
#define UART_S1_RDRF(x)                          (((uint8_t)(((uint8_t)(x)) << UART_S1_RDRF_SHIFT)) & UART_S1_RDRF_MASK)
#define UART_S1_TC_MASK                          (0x40U)
#define UART_S1_TC_SHIFT                         (6U)
#define UART_S1_TC(x)                            (((uint8_t)(((uint8_t)(x)) << UART_S1_TC_SHIFT)) & UART_S1_TC_MASK)
#define UART_S1_TDRE_MASK                        (0x80U)
#define UART_S1_TDRE_SHIFT                       (7U)
#define UART_S1_TDRE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_S1_TDRE_SHIFT)) & UART_S1_TDRE_MASK)

/*! @name S2 - UART Status Register 2 */
#define UART_S2_RAF_MASK                         (0x1U)
#define UART_S2_RAF_SHIFT                        (0U)
#define UART_S2_RAF(x)                           (((uint8_t)(((uint8_t)(x)) << UART_S2_RAF_SHIFT)) & UART_S2_RAF_MASK)
#define UART_S2_LBKDE_MASK                       (0x2U)
#define UART_S2_LBKDE_SHIFT                      (1U)
#define UART_S2_LBKDE(x)                         (((uint8_t)(((uint8_t)(x)) << UART_S2_LBKDE_SHIFT)) & UART_S2_LBKDE_MASK)
#define UART_S2_BRK13_MASK                       (0x4U)
#define UART_S2_BRK13_SHIFT                      (2U)
#define UART_S2_BRK13(x)                         (((uint8_t)(((uint8_t)(x)) << UART_S2_BRK13_SHIFT)) & UART_S2_BRK13_MASK)
#define UART_S2_RWUID_MASK                       (0x8U)
#define UART_S2_RWUID_SHIFT                      (3U)
#define UART_S2_RWUID(x)                         (((uint8_t)(((uint8_t)(x)) << UART_S2_RWUID_SHIFT)) & UART_S2_RWUID_MASK)
#define UART_S2_RXINV_MASK                       (0x10U)
#define UART_S2_RXINV_SHIFT                      (4U)
#define UART_S2_RXINV(x)                         (((uint8_t)(((uint8_t)(x)) << UART_S2_RXINV_SHIFT)) & UART_S2_RXINV_MASK)
#define UART_S2_MSBF_MASK                        (0x20U)
#define UART_S2_MSBF_SHIFT                       (5U)
#define UART_S2_MSBF(x)                          (((uint8_t)(((uint8_t)(x)) << UART_S2_MSBF_SHIFT)) & UART_S2_MSBF_MASK)
#define UART_S2_RXEDGIF_MASK                     (0x40U)
#define UART_S2_RXEDGIF_SHIFT                    (6U)
#define UART_S2_RXEDGIF(x)                       (((uint8_t)(((uint8_t)(x)) << UART_S2_RXEDGIF_SHIFT)) & UART_S2_RXEDGIF_MASK)
#define UART_S2_LBKDIF_MASK                      (0x80U)
#define UART_S2_LBKDIF_SHIFT                     (7U)
#define UART_S2_LBKDIF(x)                        (((uint8_t)(((uint8_t)(x)) << UART_S2_LBKDIF_SHIFT)) & UART_S2_LBKDIF_MASK)

/*! @name C3 - UART Control Register 3 */
#define UART_C3_PEIE_MASK                        (0x1U)
#define UART_C3_PEIE_SHIFT                       (0U)
#define UART_C3_PEIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C3_PEIE_SHIFT)) & UART_C3_PEIE_MASK)
#define UART_C3_FEIE_MASK                        (0x2U)
#define UART_C3_FEIE_SHIFT                       (1U)
#define UART_C3_FEIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C3_FEIE_SHIFT)) & UART_C3_FEIE_MASK)
#define UART_C3_NEIE_MASK                        (0x4U)
#define UART_C3_NEIE_SHIFT                       (2U)
#define UART_C3_NEIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C3_NEIE_SHIFT)) & UART_C3_NEIE_MASK)
#define UART_C3_ORIE_MASK                        (0x8U)
#define UART_C3_ORIE_SHIFT                       (3U)
#define UART_C3_ORIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C3_ORIE_SHIFT)) & UART_C3_ORIE_MASK)
#define UART_C3_TXINV_MASK                       (0x10U)
#define UART_C3_TXINV_SHIFT                      (4U)
#define UART_C3_TXINV(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C3_TXINV_SHIFT)) & UART_C3_TXINV_MASK)
#define UART_C3_TXDIR_MASK                       (0x20U)
#define UART_C3_TXDIR_SHIFT                      (5U)
#define UART_C3_TXDIR(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C3_TXDIR_SHIFT)) & UART_C3_TXDIR_MASK)
#define UART_C3_T8_MASK                          (0x40U)
#define UART_C3_T8_SHIFT                         (6U)
#define UART_C3_T8(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C3_T8_SHIFT)) & UART_C3_T8_MASK)
#define UART_C3_R8_MASK                          (0x80U)
#define UART_C3_R8_SHIFT                         (7U)
#define UART_C3_R8(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C3_R8_SHIFT)) & UART_C3_R8_MASK)

/*! @name D - UART Data Register */
#define UART_D_RT_MASK                           (0xFFU)
#define UART_D_RT_SHIFT                          (0U)
#define UART_D_RT(x)                             (((uint8_t)(((uint8_t)(x)) << UART_D_RT_SHIFT)) & UART_D_RT_MASK)

/*! @name MA1 - UART Match Address Registers 1 */
#define UART_MA1_MA_MASK                         (0xFFU)
#define UART_MA1_MA_SHIFT                        (0U)
#define UART_MA1_MA(x)                           (((uint8_t)(((uint8_t)(x)) << UART_MA1_MA_SHIFT)) & UART_MA1_MA_MASK)

/*! @name MA2 - UART Match Address Registers 2 */
#define UART_MA2_MA_MASK                         (0xFFU)
#define UART_MA2_MA_SHIFT                        (0U)
#define UART_MA2_MA(x)                           (((uint8_t)(((uint8_t)(x)) << UART_MA2_MA_SHIFT)) & UART_MA2_MA_MASK)

/*! @name C4 - UART Control Register 4 */
#define UART_C4_BRFA_MASK                        (0x1FU)
#define UART_C4_BRFA_SHIFT                       (0U)
#define UART_C4_BRFA(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C4_BRFA_SHIFT)) & UART_C4_BRFA_MASK)
#define UART_C4_M10_MASK                         (0x20U)
#define UART_C4_M10_SHIFT                        (5U)
#define UART_C4_M10(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C4_M10_SHIFT)) & UART_C4_M10_MASK)
#define UART_C4_MAEN2_MASK                       (0x40U)
#define UART_C4_MAEN2_SHIFT                      (6U)
#define UART_C4_MAEN2(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C4_MAEN2_SHIFT)) & UART_C4_MAEN2_MASK)
#define UART_C4_MAEN1_MASK                       (0x80U)
#define UART_C4_MAEN1_SHIFT                      (7U)
#define UART_C4_MAEN1(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C4_MAEN1_SHIFT)) & UART_C4_MAEN1_MASK)

/*! @name C5 - UART Control Register 5 */
#define UART_C5_LBKDDMAS_MASK                    (0x8U)
#define UART_C5_LBKDDMAS_SHIFT                   (3U)
#define UART_C5_LBKDDMAS(x)                      (((uint8_t)(((uint8_t)(x)) << UART_C5_LBKDDMAS_SHIFT)) & UART_C5_LBKDDMAS_MASK)
#define UART_C5_RDMAS_MASK                       (0x20U)
#define UART_C5_RDMAS_SHIFT                      (5U)
#define UART_C5_RDMAS(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C5_RDMAS_SHIFT)) & UART_C5_RDMAS_MASK)
#define UART_C5_TDMAS_MASK                       (0x80U)
#define UART_C5_TDMAS_SHIFT                      (7U)
#define UART_C5_TDMAS(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C5_TDMAS_SHIFT)) & UART_C5_TDMAS_MASK)

/*! @name ED - UART Extended Data Register */
#define UART_ED_PARITYE_MASK                     (0x40U)
#define UART_ED_PARITYE_SHIFT                    (6U)
#define UART_ED_PARITYE(x)                       (((uint8_t)(((uint8_t)(x)) << UART_ED_PARITYE_SHIFT)) & UART_ED_PARITYE_MASK)
#define UART_ED_NOISY_MASK                       (0x80U)
#define UART_ED_NOISY_SHIFT                      (7U)
#define UART_ED_NOISY(x)                         (((uint8_t)(((uint8_t)(x)) << UART_ED_NOISY_SHIFT)) & UART_ED_NOISY_MASK)

/*! @name MODEM - UART Modem Register */
#define UART_MODEM_TXCTSE_MASK                   (0x1U)
#define UART_MODEM_TXCTSE_SHIFT                  (0U)
#define UART_MODEM_TXCTSE(x)                     (((uint8_t)(((uint8_t)(x)) << UART_MODEM_TXCTSE_SHIFT)) & UART_MODEM_TXCTSE_MASK)
#define UART_MODEM_TXRTSE_MASK                   (0x2U)
#define UART_MODEM_TXRTSE_SHIFT                  (1U)
#define UART_MODEM_TXRTSE(x)                     (((uint8_t)(((uint8_t)(x)) << UART_MODEM_TXRTSE_SHIFT)) & UART_MODEM_TXRTSE_MASK)
#define UART_MODEM_TXRTSPOL_MASK                 (0x4U)
#define UART_MODEM_TXRTSPOL_SHIFT                (2U)
#define UART_MODEM_TXRTSPOL(x)                   (((uint8_t)(((uint8_t)(x)) << UART_MODEM_TXRTSPOL_SHIFT)) & UART_MODEM_TXRTSPOL_MASK)
#define UART_MODEM_RXRTSE_MASK                   (0x8U)
#define UART_MODEM_RXRTSE_SHIFT                  (3U)
#define UART_MODEM_RXRTSE(x)                     (((uint8_t)(((uint8_t)(x)) << UART_MODEM_RXRTSE_SHIFT)) & UART_MODEM_RXRTSE_MASK)

/*! @name IR - UART Infrared Register */
#define UART_IR_TNP_MASK                         (0x3U)
#define UART_IR_TNP_SHIFT                        (0U)
#define UART_IR_TNP(x)                           (((uint8_t)(((uint8_t)(x)) << UART_IR_TNP_SHIFT)) & UART_IR_TNP_MASK)
#define UART_IR_IREN_MASK                        (0x4U)
#define UART_IR_IREN_SHIFT                       (2U)
#define UART_IR_IREN(x)                          (((uint8_t)(((uint8_t)(x)) << UART_IR_IREN_SHIFT)) & UART_IR_IREN_MASK)

/*! @name PFIFO - UART FIFO Parameters */
#define UART_PFIFO_RXFIFOSIZE_MASK               (0x7U)
#define UART_PFIFO_RXFIFOSIZE_SHIFT              (0U)
#define UART_PFIFO_RXFIFOSIZE(x)                 (((uint8_t)(((uint8_t)(x)) << UART_PFIFO_RXFIFOSIZE_SHIFT)) & UART_PFIFO_RXFIFOSIZE_MASK)
#define UART_PFIFO_RXFE_MASK                     (0x8U)
#define UART_PFIFO_RXFE_SHIFT                    (3U)
#define UART_PFIFO_RXFE(x)                       (((uint8_t)(((uint8_t)(x)) << UART_PFIFO_RXFE_SHIFT)) & UART_PFIFO_RXFE_MASK)
#define UART_PFIFO_TXFIFOSIZE_MASK               (0x70U)
#define UART_PFIFO_TXFIFOSIZE_SHIFT              (4U)
#define UART_PFIFO_TXFIFOSIZE(x)                 (((uint8_t)(((uint8_t)(x)) << UART_PFIFO_TXFIFOSIZE_SHIFT)) & UART_PFIFO_TXFIFOSIZE_MASK)
#define UART_PFIFO_TXFE_MASK                     (0x80U)
#define UART_PFIFO_TXFE_SHIFT                    (7U)
#define UART_PFIFO_TXFE(x)                       (((uint8_t)(((uint8_t)(x)) << UART_PFIFO_TXFE_SHIFT)) & UART_PFIFO_TXFE_MASK)

/*! @name CFIFO - UART FIFO Control Register */
#define UART_CFIFO_RXUFE_MASK                    (0x1U)
#define UART_CFIFO_RXUFE_SHIFT                   (0U)
#define UART_CFIFO_RXUFE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_CFIFO_RXUFE_SHIFT)) & UART_CFIFO_RXUFE_MASK)
#define UART_CFIFO_TXOFE_MASK                    (0x2U)
#define UART_CFIFO_TXOFE_SHIFT                   (1U)
#define UART_CFIFO_TXOFE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_CFIFO_TXOFE_SHIFT)) & UART_CFIFO_TXOFE_MASK)
#define UART_CFIFO_RXOFE_MASK                    (0x4U)
#define UART_CFIFO_RXOFE_SHIFT                   (2U)
#define UART_CFIFO_RXOFE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_CFIFO_RXOFE_SHIFT)) & UART_CFIFO_RXOFE_MASK)
#define UART_CFIFO_RXFLUSH_MASK                  (0x40U)
#define UART_CFIFO_RXFLUSH_SHIFT                 (6U)
#define UART_CFIFO_RXFLUSH(x)                    (((uint8_t)(((uint8_t)(x)) << UART_CFIFO_RXFLUSH_SHIFT)) & UART_CFIFO_RXFLUSH_MASK)
#define UART_CFIFO_TXFLUSH_MASK                  (0x80U)
#define UART_CFIFO_TXFLUSH_SHIFT                 (7U)
#define UART_CFIFO_TXFLUSH(x)                    (((uint8_t)(((uint8_t)(x)) << UART_CFIFO_TXFLUSH_SHIFT)) & UART_CFIFO_TXFLUSH_MASK)

/*! @name SFIFO - UART FIFO Status Register */
#define UART_SFIFO_RXUF_MASK                     (0x1U)
#define UART_SFIFO_RXUF_SHIFT                    (0U)
#define UART_SFIFO_RXUF(x)                       (((uint8_t)(((uint8_t)(x)) << UART_SFIFO_RXUF_SHIFT)) & UART_SFIFO_RXUF_MASK)
#define UART_SFIFO_TXOF_MASK                     (0x2U)
#define UART_SFIFO_TXOF_SHIFT                    (1U)
#define UART_SFIFO_TXOF(x)                       (((uint8_t)(((uint8_t)(x)) << UART_SFIFO_TXOF_SHIFT)) & UART_SFIFO_TXOF_MASK)
#define UART_SFIFO_RXOF_MASK                     (0x4U)
#define UART_SFIFO_RXOF_SHIFT                    (2U)
#define UART_SFIFO_RXOF(x)                       (((uint8_t)(((uint8_t)(x)) << UART_SFIFO_RXOF_SHIFT)) & UART_SFIFO_RXOF_MASK)
#define UART_SFIFO_RXEMPT_MASK                   (0x40U)
#define UART_SFIFO_RXEMPT_SHIFT                  (6U)
#define UART_SFIFO_RXEMPT(x)                     (((uint8_t)(((uint8_t)(x)) << UART_SFIFO_RXEMPT_SHIFT)) & UART_SFIFO_RXEMPT_MASK)
#define UART_SFIFO_TXEMPT_MASK                   (0x80U)
#define UART_SFIFO_TXEMPT_SHIFT                  (7U)
#define UART_SFIFO_TXEMPT(x)                     (((uint8_t)(((uint8_t)(x)) << UART_SFIFO_TXEMPT_SHIFT)) & UART_SFIFO_TXEMPT_MASK)

/*! @name TWFIFO - UART FIFO Transmit Watermark */
#define UART_TWFIFO_TXWATER_MASK                 (0xFFU)
#define UART_TWFIFO_TXWATER_SHIFT                (0U)
#define UART_TWFIFO_TXWATER(x)                   (((uint8_t)(((uint8_t)(x)) << UART_TWFIFO_TXWATER_SHIFT)) & UART_TWFIFO_TXWATER_MASK)

/*! @name TCFIFO - UART FIFO Transmit Count */
#define UART_TCFIFO_TXCOUNT_MASK                 (0xFFU)
#define UART_TCFIFO_TXCOUNT_SHIFT                (0U)
#define UART_TCFIFO_TXCOUNT(x)                   (((uint8_t)(((uint8_t)(x)) << UART_TCFIFO_TXCOUNT_SHIFT)) & UART_TCFIFO_TXCOUNT_MASK)

/*! @name RWFIFO - UART FIFO Receive Watermark */
#define UART_RWFIFO_RXWATER_MASK                 (0xFFU)
#define UART_RWFIFO_RXWATER_SHIFT                (0U)
#define UART_RWFIFO_RXWATER(x)                   (((uint8_t)(((uint8_t)(x)) << UART_RWFIFO_RXWATER_SHIFT)) & UART_RWFIFO_RXWATER_MASK)

/*! @name RCFIFO - UART FIFO Receive Count */
#define UART_RCFIFO_RXCOUNT_MASK                 (0xFFU)
#define UART_RCFIFO_RXCOUNT_SHIFT                (0U)
#define UART_RCFIFO_RXCOUNT(x)                   (((uint8_t)(((uint8_t)(x)) << UART_RCFIFO_RXCOUNT_SHIFT)) & UART_RCFIFO_RXCOUNT_MASK)

/*! @name C7816 - UART 7816 Control Register */
#define UART_C7816_ISO_7816E_MASK                (0x1U)
#define UART_C7816_ISO_7816E_SHIFT               (0U)
#define UART_C7816_ISO_7816E(x)                  (((uint8_t)(((uint8_t)(x)) << UART_C7816_ISO_7816E_SHIFT)) & UART_C7816_ISO_7816E_MASK)
#define UART_C7816_TTYPE_MASK                    (0x2U)
#define UART_C7816_TTYPE_SHIFT                   (1U)
#define UART_C7816_TTYPE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_C7816_TTYPE_SHIFT)) & UART_C7816_TTYPE_MASK)
#define UART_C7816_INIT_MASK                     (0x4U)
#define UART_C7816_INIT_SHIFT                    (2U)
#define UART_C7816_INIT(x)                       (((uint8_t)(((uint8_t)(x)) << UART_C7816_INIT_SHIFT)) & UART_C7816_INIT_MASK)
#define UART_C7816_ANACK_MASK                    (0x8U)
#define UART_C7816_ANACK_SHIFT                   (3U)
#define UART_C7816_ANACK(x)                      (((uint8_t)(((uint8_t)(x)) << UART_C7816_ANACK_SHIFT)) & UART_C7816_ANACK_MASK)
#define UART_C7816_ONACK_MASK                    (0x10U)
#define UART_C7816_ONACK_SHIFT                   (4U)
#define UART_C7816_ONACK(x)                      (((uint8_t)(((uint8_t)(x)) << UART_C7816_ONACK_SHIFT)) & UART_C7816_ONACK_MASK)

/*! @name IE7816 - UART 7816 Interrupt Enable Register */
#define UART_IE7816_RXTE_MASK                    (0x1U)
#define UART_IE7816_RXTE_SHIFT                   (0U)
#define UART_IE7816_RXTE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_IE7816_RXTE_SHIFT)) & UART_IE7816_RXTE_MASK)
#define UART_IE7816_TXTE_MASK                    (0x2U)
#define UART_IE7816_TXTE_SHIFT                   (1U)
#define UART_IE7816_TXTE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_IE7816_TXTE_SHIFT)) & UART_IE7816_TXTE_MASK)
#define UART_IE7816_GTVE_MASK                    (0x4U)
#define UART_IE7816_GTVE_SHIFT                   (2U)
#define UART_IE7816_GTVE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_IE7816_GTVE_SHIFT)) & UART_IE7816_GTVE_MASK)
#define UART_IE7816_ADTE_MASK                    (0x8U)
#define UART_IE7816_ADTE_SHIFT                   (3U)
#define UART_IE7816_ADTE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_IE7816_ADTE_SHIFT)) & UART_IE7816_ADTE_MASK)
#define UART_IE7816_INITDE_MASK                  (0x10U)
#define UART_IE7816_INITDE_SHIFT                 (4U)
#define UART_IE7816_INITDE(x)                    (((uint8_t)(((uint8_t)(x)) << UART_IE7816_INITDE_SHIFT)) & UART_IE7816_INITDE_MASK)
#define UART_IE7816_BWTE_MASK                    (0x20U)
#define UART_IE7816_BWTE_SHIFT                   (5U)
#define UART_IE7816_BWTE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_IE7816_BWTE_SHIFT)) & UART_IE7816_BWTE_MASK)
#define UART_IE7816_CWTE_MASK                    (0x40U)
#define UART_IE7816_CWTE_SHIFT                   (6U)
#define UART_IE7816_CWTE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_IE7816_CWTE_SHIFT)) & UART_IE7816_CWTE_MASK)
#define UART_IE7816_WTE_MASK                     (0x80U)
#define UART_IE7816_WTE_SHIFT                    (7U)
#define UART_IE7816_WTE(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IE7816_WTE_SHIFT)) & UART_IE7816_WTE_MASK)

/*! @name IS7816 - UART 7816 Interrupt Status Register */
#define UART_IS7816_RXT_MASK                     (0x1U)
#define UART_IS7816_RXT_SHIFT                    (0U)
#define UART_IS7816_RXT(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IS7816_RXT_SHIFT)) & UART_IS7816_RXT_MASK)
#define UART_IS7816_TXT_MASK                     (0x2U)
#define UART_IS7816_TXT_SHIFT                    (1U)
#define UART_IS7816_TXT(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IS7816_TXT_SHIFT)) & UART_IS7816_TXT_MASK)
#define UART_IS7816_GTV_MASK                     (0x4U)
#define UART_IS7816_GTV_SHIFT                    (2U)
#define UART_IS7816_GTV(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IS7816_GTV_SHIFT)) & UART_IS7816_GTV_MASK)
#define UART_IS7816_ADT_MASK                     (0x8U)
#define UART_IS7816_ADT_SHIFT                    (3U)
#define UART_IS7816_ADT(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IS7816_ADT_SHIFT)) & UART_IS7816_ADT_MASK)
#define UART_IS7816_INITD_MASK                   (0x10U)
#define UART_IS7816_INITD_SHIFT                  (4U)
#define UART_IS7816_INITD(x)                     (((uint8_t)(((uint8_t)(x)) << UART_IS7816_INITD_SHIFT)) & UART_IS7816_INITD_MASK)
#define UART_IS7816_BWT_MASK                     (0x20U)
#define UART_IS7816_BWT_SHIFT                    (5U)
#define UART_IS7816_BWT(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IS7816_BWT_SHIFT)) & UART_IS7816_BWT_MASK)
#define UART_IS7816_CWT_MASK                     (0x40U)
#define UART_IS7816_CWT_SHIFT                    (6U)
#define UART_IS7816_CWT(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IS7816_CWT_SHIFT)) & UART_IS7816_CWT_MASK)
#define UART_IS7816_WT_MASK                      (0x80U)
#define UART_IS7816_WT_SHIFT                     (7U)
#define UART_IS7816_WT(x)                        (((uint8_t)(((uint8_t)(x)) << UART_IS7816_WT_SHIFT)) & UART_IS7816_WT_MASK)

/*! @name WP7816 - UART 7816 Wait Parameter Register */
#define UART_WP7816_WTX_MASK                     (0xFFU)
#define UART_WP7816_WTX_SHIFT                    (0U)
#define UART_WP7816_WTX(x)                       (((uint8_t)(((uint8_t)(x)) << UART_WP7816_WTX_SHIFT)) & UART_WP7816_WTX_MASK)

/*! @name WN7816 - UART 7816 Wait N Register */
#define UART_WN7816_GTN_MASK                     (0xFFU)
#define UART_WN7816_GTN_SHIFT                    (0U)
#define UART_WN7816_GTN(x)                       (((uint8_t)(((uint8_t)(x)) << UART_WN7816_GTN_SHIFT)) & UART_WN7816_GTN_MASK)

/*! @name WF7816 - UART 7816 Wait FD Register */
#define UART_WF7816_GTFD_MASK                    (0xFFU)
#define UART_WF7816_GTFD_SHIFT                   (0U)
#define UART_WF7816_GTFD(x)                      (((uint8_t)(((uint8_t)(x)) << UART_WF7816_GTFD_SHIFT)) & UART_WF7816_GTFD_MASK)

/*! @name ET7816 - UART 7816 Error Threshold Register */
#define UART_ET7816_RXTHRESHOLD_MASK             (0xFU)
#define UART_ET7816_RXTHRESHOLD_SHIFT            (0U)
#define UART_ET7816_RXTHRESHOLD(x)               (((uint8_t)(((uint8_t)(x)) << UART_ET7816_RXTHRESHOLD_SHIFT)) & UART_ET7816_RXTHRESHOLD_MASK)
#define UART_ET7816_TXTHRESHOLD_MASK             (0xF0U)
#define UART_ET7816_TXTHRESHOLD_SHIFT            (4U)
#define UART_ET7816_TXTHRESHOLD(x)               (((uint8_t)(((uint8_t)(x)) << UART_ET7816_TXTHRESHOLD_SHIFT)) & UART_ET7816_TXTHRESHOLD_MASK)

/*! @name TL7816 - UART 7816 Transmit Length Register */
#define UART_TL7816_TLEN_MASK                    (0xFFU)
#define UART_TL7816_TLEN_SHIFT                   (0U)
#define UART_TL7816_TLEN(x)                      (((uint8_t)(((uint8_t)(x)) << UART_TL7816_TLEN_SHIFT)) & UART_TL7816_TLEN_MASK)

/*! @name AP7816A_T0 - UART 7816 ATR Duration Timer Register A */
#define UART_AP7816A_T0_ADTI_H_MASK              (0xFFU)
#define UART_AP7816A_T0_ADTI_H_SHIFT             (0U)
#define UART_AP7816A_T0_ADTI_H(x)                (((uint8_t)(((uint8_t)(x)) << UART_AP7816A_T0_ADTI_H_SHIFT)) & UART_AP7816A_T0_ADTI_H_MASK)

/*! @name AP7816B_T0 - UART 7816 ATR Duration Timer Register B */
#define UART_AP7816B_T0_ADTI_L_MASK              (0xFFU)
#define UART_AP7816B_T0_ADTI_L_SHIFT             (0U)
#define UART_AP7816B_T0_ADTI_L(x)                (((uint8_t)(((uint8_t)(x)) << UART_AP7816B_T0_ADTI_L_SHIFT)) & UART_AP7816B_T0_ADTI_L_MASK)

/*! @name WP7816A_T0 - UART 7816 Wait Parameter Register A */
#define UART_WP7816A_T0_WI_H_MASK                (0xFFU)
#define UART_WP7816A_T0_WI_H_SHIFT               (0U)
#define UART_WP7816A_T0_WI_H(x)                  (((uint8_t)(((uint8_t)(x)) << UART_WP7816A_T0_WI_H_SHIFT)) & UART_WP7816A_T0_WI_H_MASK)

/*! @name WP7816B_T0 - UART 7816 Wait Parameter Register B */
#define UART_WP7816B_T0_WI_L_MASK                (0xFFU)
#define UART_WP7816B_T0_WI_L_SHIFT               (0U)
#define UART_WP7816B_T0_WI_L(x)                  (((uint8_t)(((uint8_t)(x)) << UART_WP7816B_T0_WI_L_SHIFT)) & UART_WP7816B_T0_WI_L_MASK)

/*! @name WP7816A_T1 - UART 7816 Wait Parameter Register A */
#define UART_WP7816A_T1_BWI_H_MASK               (0xFFU)
#define UART_WP7816A_T1_BWI_H_SHIFT              (0U)
#define UART_WP7816A_T1_BWI_H(x)                 (((uint8_t)(((uint8_t)(x)) << UART_WP7816A_T1_BWI_H_SHIFT)) & UART_WP7816A_T1_BWI_H_MASK)

/*! @name WP7816B_T1 - UART 7816 Wait Parameter Register B */
#define UART_WP7816B_T1_BWI_L_MASK               (0xFFU)
#define UART_WP7816B_T1_BWI_L_SHIFT              (0U)
#define UART_WP7816B_T1_BWI_L(x)                 (((uint8_t)(((uint8_t)(x)) << UART_WP7816B_T1_BWI_L_SHIFT)) & UART_WP7816B_T1_BWI_L_MASK)

/*! @name WGP7816_T1 - UART 7816 Wait and Guard Parameter Register */
#define UART_WGP7816_T1_BGI_MASK                 (0xFU)
#define UART_WGP7816_T1_BGI_SHIFT                (0U)
#define UART_WGP7816_T1_BGI(x)                   (((uint8_t)(((uint8_t)(x)) << UART_WGP7816_T1_BGI_SHIFT)) & UART_WGP7816_T1_BGI_MASK)
#define UART_WGP7816_T1_CWI1_MASK                (0xF0U)
#define UART_WGP7816_T1_CWI1_SHIFT               (4U)
#define UART_WGP7816_T1_CWI1(x)                  (((uint8_t)(((uint8_t)(x)) << UART_WGP7816_T1_CWI1_SHIFT)) & UART_WGP7816_T1_CWI1_MASK)

/*! @name WP7816C_T1 - UART 7816 Wait Parameter Register C */
#define UART_WP7816C_T1_CWI2_MASK                (0x1FU)
#define UART_WP7816C_T1_CWI2_SHIFT               (0U)
#define UART_WP7816C_T1_CWI2(x)                  (((uint8_t)(((uint8_t)(x)) << UART_WP7816C_T1_CWI2_SHIFT)) & UART_WP7816C_T1_CWI2_MASK)


/*!
 * @}
 */ /* end of group UART_Register_Masks */


/* UART - Peripheral instance base addresses */
/** Peripheral UART0 base address */
#define UART0_BASE                               (0x4006A000u)
/** Peripheral UART0 base pointer */
#define UART0                                    ((UART_Type *)UART0_BASE)
/** Peripheral UART1 base address */
#define UART1_BASE                               (0x4006B000u)
/** Peripheral UART1 base pointer */
#define UART1                                    ((UART_Type *)UART1_BASE)
/** Peripheral UART2 base address */
#define UART2_BASE                               (0x4006C000u)
/** Peripheral UART2 base pointer */
#define UART2                                    ((UART_Type *)UART2_BASE)
/** Peripheral UART3 base address */
#define UART3_BASE                               (0x4006D000u)
/** Peripheral UART3 base pointer */
#define UART3                                    ((UART_Type *)UART3_BASE)
/** Peripheral UART4 base address */
#define UART4_BASE                               (0x400EA000u)
/** Peripheral UART4 base pointer */
#define UART4                                    ((UART_Type *)UART4_BASE)
/** Peripheral UART5 base address */
#define UART5_BASE                               (0x400EB000u)
/** Peripheral UART5 base pointer */
#define UART5                                    ((UART_Type *)UART5_BASE)
/** Array initializer of UART peripheral base addresses */
#define UART_BASE_ADDRS                          { UART0_BASE, UART1_BASE, UART2_BASE, UART3_BASE, UART4_BASE, UART5_BASE }
/** Array initializer of UART peripheral base pointers */
#define UART_BASE_PTRS                           { UART0, UART1, UART2, UART3, UART4, UART5 }
/** Interrupt vectors for the UART peripheral type */
#define UART_RX_TX_IRQS                          { UART0_RX_TX_IRQn, UART1_RX_TX_IRQn, UART2_RX_TX_IRQn, UART3_RX_TX_IRQn, UART4_RX_TX_IRQn, UART5_RX_TX_IRQn }
#define UART_ERR_IRQS                            { UART0_ERR_IRQn, UART1_ERR_IRQn, UART2_ERR_IRQn, UART3_ERR_IRQn, UART4_ERR_IRQn, UART5_ERR_IRQn }

/*!
 * @}
 */ /* end of group UART_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- WDOG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Peripheral_Access_Layer WDOG Peripheral Access Layer
 * @{
 */

/** WDOG - Register Layout Typedef */
typedef struct {
  __IO uint16_t STCTRLH;                           /**< Watchdog Status and Control Register High, offset: 0x0 */
  __IO uint16_t STCTRLL;                           /**< Watchdog Status and Control Register Low, offset: 0x2 */
  __IO uint16_t TOVALH;                            /**< Watchdog Time-out Value Register High, offset: 0x4 */
  __IO uint16_t TOVALL;                            /**< Watchdog Time-out Value Register Low, offset: 0x6 */
  __IO uint16_t WINH;                              /**< Watchdog Window Register High, offset: 0x8 */
  __IO uint16_t WINL;                              /**< Watchdog Window Register Low, offset: 0xA */
  __IO uint16_t REFRESH;                           /**< Watchdog Refresh register, offset: 0xC */
  __IO uint16_t UNLOCK;                            /**< Watchdog Unlock register, offset: 0xE */
  __IO uint16_t TMROUTH;                           /**< Watchdog Timer Output Register High, offset: 0x10 */
  __IO uint16_t TMROUTL;                           /**< Watchdog Timer Output Register Low, offset: 0x12 */
  __IO uint16_t RSTCNT;                            /**< Watchdog Reset Count register, offset: 0x14 */
  __IO uint16_t PRESC;                             /**< Watchdog Prescaler register, offset: 0x16 */
} WDOG_Type;

/* ----------------------------------------------------------------------------
   -- WDOG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Masks WDOG Register Masks
 * @{
 */

/*! @name STCTRLH - Watchdog Status and Control Register High */
#define WDOG_STCTRLH_WDOGEN_MASK                 (0x1U)
#define WDOG_STCTRLH_WDOGEN_SHIFT                (0U)
#define WDOG_STCTRLH_WDOGEN(x)                   (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_WDOGEN_SHIFT)) & WDOG_STCTRLH_WDOGEN_MASK)
#define WDOG_STCTRLH_CLKSRC_MASK                 (0x2U)
#define WDOG_STCTRLH_CLKSRC_SHIFT                (1U)
#define WDOG_STCTRLH_CLKSRC(x)                   (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_CLKSRC_SHIFT)) & WDOG_STCTRLH_CLKSRC_MASK)
#define WDOG_STCTRLH_IRQRSTEN_MASK               (0x4U)
#define WDOG_STCTRLH_IRQRSTEN_SHIFT              (2U)
#define WDOG_STCTRLH_IRQRSTEN(x)                 (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_IRQRSTEN_SHIFT)) & WDOG_STCTRLH_IRQRSTEN_MASK)
#define WDOG_STCTRLH_WINEN_MASK                  (0x8U)
#define WDOG_STCTRLH_WINEN_SHIFT                 (3U)
#define WDOG_STCTRLH_WINEN(x)                    (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_WINEN_SHIFT)) & WDOG_STCTRLH_WINEN_MASK)
#define WDOG_STCTRLH_ALLOWUPDATE_MASK            (0x10U)
#define WDOG_STCTRLH_ALLOWUPDATE_SHIFT           (4U)
#define WDOG_STCTRLH_ALLOWUPDATE(x)              (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_ALLOWUPDATE_SHIFT)) & WDOG_STCTRLH_ALLOWUPDATE_MASK)
#define WDOG_STCTRLH_DBGEN_MASK                  (0x20U)
#define WDOG_STCTRLH_DBGEN_SHIFT                 (5U)
#define WDOG_STCTRLH_DBGEN(x)                    (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_DBGEN_SHIFT)) & WDOG_STCTRLH_DBGEN_MASK)
#define WDOG_STCTRLH_STOPEN_MASK                 (0x40U)
#define WDOG_STCTRLH_STOPEN_SHIFT                (6U)
#define WDOG_STCTRLH_STOPEN(x)                   (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_STOPEN_SHIFT)) & WDOG_STCTRLH_STOPEN_MASK)
#define WDOG_STCTRLH_WAITEN_MASK                 (0x80U)
#define WDOG_STCTRLH_WAITEN_SHIFT                (7U)
#define WDOG_STCTRLH_WAITEN(x)                   (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_WAITEN_SHIFT)) & WDOG_STCTRLH_WAITEN_MASK)
#define WDOG_STCTRLH_TESTWDOG_MASK               (0x400U)
#define WDOG_STCTRLH_TESTWDOG_SHIFT              (10U)
#define WDOG_STCTRLH_TESTWDOG(x)                 (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_TESTWDOG_SHIFT)) & WDOG_STCTRLH_TESTWDOG_MASK)
#define WDOG_STCTRLH_TESTSEL_MASK                (0x800U)
#define WDOG_STCTRLH_TESTSEL_SHIFT               (11U)
#define WDOG_STCTRLH_TESTSEL(x)                  (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_TESTSEL_SHIFT)) & WDOG_STCTRLH_TESTSEL_MASK)
#define WDOG_STCTRLH_BYTESEL_MASK                (0x3000U)
#define WDOG_STCTRLH_BYTESEL_SHIFT               (12U)
#define WDOG_STCTRLH_BYTESEL(x)                  (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_BYTESEL_SHIFT)) & WDOG_STCTRLH_BYTESEL_MASK)
#define WDOG_STCTRLH_DISTESTWDOG_MASK            (0x4000U)
#define WDOG_STCTRLH_DISTESTWDOG_SHIFT           (14U)
#define WDOG_STCTRLH_DISTESTWDOG(x)              (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_DISTESTWDOG_SHIFT)) & WDOG_STCTRLH_DISTESTWDOG_MASK)

/*! @name STCTRLL - Watchdog Status and Control Register Low */
#define WDOG_STCTRLL_INTFLG_MASK                 (0x8000U)
#define WDOG_STCTRLL_INTFLG_SHIFT                (15U)
#define WDOG_STCTRLL_INTFLG(x)                   (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLL_INTFLG_SHIFT)) & WDOG_STCTRLL_INTFLG_MASK)

/*! @name TOVALH - Watchdog Time-out Value Register High */
#define WDOG_TOVALH_TOVALHIGH_MASK               (0xFFFFU)
#define WDOG_TOVALH_TOVALHIGH_SHIFT              (0U)
#define WDOG_TOVALH_TOVALHIGH(x)                 (((uint16_t)(((uint16_t)(x)) << WDOG_TOVALH_TOVALHIGH_SHIFT)) & WDOG_TOVALH_TOVALHIGH_MASK)

/*! @name TOVALL - Watchdog Time-out Value Register Low */
#define WDOG_TOVALL_TOVALLOW_MASK                (0xFFFFU)
#define WDOG_TOVALL_TOVALLOW_SHIFT               (0U)
#define WDOG_TOVALL_TOVALLOW(x)                  (((uint16_t)(((uint16_t)(x)) << WDOG_TOVALL_TOVALLOW_SHIFT)) & WDOG_TOVALL_TOVALLOW_MASK)

/*! @name WINH - Watchdog Window Register High */
#define WDOG_WINH_WINHIGH_MASK                   (0xFFFFU)
#define WDOG_WINH_WINHIGH_SHIFT                  (0U)
#define WDOG_WINH_WINHIGH(x)                     (((uint16_t)(((uint16_t)(x)) << WDOG_WINH_WINHIGH_SHIFT)) & WDOG_WINH_WINHIGH_MASK)

/*! @name WINL - Watchdog Window Register Low */
#define WDOG_WINL_WINLOW_MASK                    (0xFFFFU)
#define WDOG_WINL_WINLOW_SHIFT                   (0U)
#define WDOG_WINL_WINLOW(x)                      (((uint16_t)(((uint16_t)(x)) << WDOG_WINL_WINLOW_SHIFT)) & WDOG_WINL_WINLOW_MASK)

/*! @name REFRESH - Watchdog Refresh register */
#define WDOG_REFRESH_WDOGREFRESH_MASK            (0xFFFFU)
#define WDOG_REFRESH_WDOGREFRESH_SHIFT           (0U)
#define WDOG_REFRESH_WDOGREFRESH(x)              (((uint16_t)(((uint16_t)(x)) << WDOG_REFRESH_WDOGREFRESH_SHIFT)) & WDOG_REFRESH_WDOGREFRESH_MASK)

/*! @name UNLOCK - Watchdog Unlock register */
#define WDOG_UNLOCK_WDOGUNLOCK_MASK              (0xFFFFU)
#define WDOG_UNLOCK_WDOGUNLOCK_SHIFT             (0U)
#define WDOG_UNLOCK_WDOGUNLOCK(x)                (((uint16_t)(((uint16_t)(x)) << WDOG_UNLOCK_WDOGUNLOCK_SHIFT)) & WDOG_UNLOCK_WDOGUNLOCK_MASK)

/*! @name TMROUTH - Watchdog Timer Output Register High */
#define WDOG_TMROUTH_TIMEROUTHIGH_MASK           (0xFFFFU)
#define WDOG_TMROUTH_TIMEROUTHIGH_SHIFT          (0U)
#define WDOG_TMROUTH_TIMEROUTHIGH(x)             (((uint16_t)(((uint16_t)(x)) << WDOG_TMROUTH_TIMEROUTHIGH_SHIFT)) & WDOG_TMROUTH_TIMEROUTHIGH_MASK)

/*! @name TMROUTL - Watchdog Timer Output Register Low */
#define WDOG_TMROUTL_TIMEROUTLOW_MASK            (0xFFFFU)
#define WDOG_TMROUTL_TIMEROUTLOW_SHIFT           (0U)
#define WDOG_TMROUTL_TIMEROUTLOW(x)              (((uint16_t)(((uint16_t)(x)) << WDOG_TMROUTL_TIMEROUTLOW_SHIFT)) & WDOG_TMROUTL_TIMEROUTLOW_MASK)

/*! @name RSTCNT - Watchdog Reset Count register */
#define WDOG_RSTCNT_RSTCNT_MASK                  (0xFFFFU)
#define WDOG_RSTCNT_RSTCNT_SHIFT                 (0U)
#define WDOG_RSTCNT_RSTCNT(x)                    (((uint16_t)(((uint16_t)(x)) << WDOG_RSTCNT_RSTCNT_SHIFT)) & WDOG_RSTCNT_RSTCNT_MASK)

/*! @name PRESC - Watchdog Prescaler register */
#define WDOG_PRESC_PRESCVAL_MASK                 (0x700U)
#define WDOG_PRESC_PRESCVAL_SHIFT                (8U)
#define WDOG_PRESC_PRESCVAL(x)                   (((uint16_t)(((uint16_t)(x)) << WDOG_PRESC_PRESCVAL_SHIFT)) & WDOG_PRESC_PRESCVAL_MASK)


/*!
 * @}
 */ /* end of group WDOG_Register_Masks */


/* WDOG - Peripheral instance base addresses */
/** Peripheral WDOG base address */
#define WDOG_BASE                                (0x40052000u)
/** Peripheral WDOG base pointer */
#define WDOG                                     ((WDOG_Type *)WDOG_BASE)
/** Array initializer of WDOG peripheral base addresses */
#define WDOG_BASE_ADDRS                          { WDOG_BASE }
/** Array initializer of WDOG peripheral base pointers */
#define WDOG_BASE_PTRS                           { WDOG }
/** Interrupt vectors for the WDOG peripheral type */
#define WDOG_IRQS                                { WDOG_EWM_IRQn }

/*!
 * @}
 */ /* end of group WDOG_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- XBARA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XBARA_Peripheral_Access_Layer XBARA Peripheral Access Layer
 * @{
 */

/** XBARA - Register Layout Typedef */
typedef struct {
  __IO uint16_t SEL0;                              /**< Crossbar A Select Register 0, offset: 0x0 */
  __IO uint16_t SEL1;                              /**< Crossbar A Select Register 1, offset: 0x2 */
  __IO uint16_t SEL2;                              /**< Crossbar A Select Register 2, offset: 0x4 */
  __IO uint16_t SEL3;                              /**< Crossbar A Select Register 3, offset: 0x6 */
  __IO uint16_t SEL4;                              /**< Crossbar A Select Register 4, offset: 0x8 */
  __IO uint16_t SEL5;                              /**< Crossbar A Select Register 5, offset: 0xA */
  __IO uint16_t SEL6;                              /**< Crossbar A Select Register 6, offset: 0xC */
  __IO uint16_t SEL7;                              /**< Crossbar A Select Register 7, offset: 0xE */
  __IO uint16_t SEL8;                              /**< Crossbar A Select Register 8, offset: 0x10 */
  __IO uint16_t SEL9;                              /**< Crossbar A Select Register 9, offset: 0x12 */
  __IO uint16_t SEL10;                             /**< Crossbar A Select Register 10, offset: 0x14 */
  __IO uint16_t SEL11;                             /**< Crossbar A Select Register 11, offset: 0x16 */
  __IO uint16_t SEL12;                             /**< Crossbar A Select Register 12, offset: 0x18 */
  __IO uint16_t SEL13;                             /**< Crossbar A Select Register 13, offset: 0x1A */
  __IO uint16_t SEL14;                             /**< Crossbar A Select Register 14, offset: 0x1C */
  __IO uint16_t SEL15;                             /**< Crossbar A Select Register 15, offset: 0x1E */
  __IO uint16_t SEL16;                             /**< Crossbar A Select Register 16, offset: 0x20 */
  __IO uint16_t SEL17;                             /**< Crossbar A Select Register 17, offset: 0x22 */
  __IO uint16_t SEL18;                             /**< Crossbar A Select Register 18, offset: 0x24 */
  __IO uint16_t SEL19;                             /**< Crossbar A Select Register 19, offset: 0x26 */
  __IO uint16_t SEL20;                             /**< Crossbar A Select Register 20, offset: 0x28 */
  __IO uint16_t SEL21;                             /**< Crossbar A Select Register 21, offset: 0x2A */
  __IO uint16_t SEL22;                             /**< Crossbar A Select Register 22, offset: 0x2C */
  __IO uint16_t SEL23;                             /**< Crossbar A Select Register 23, offset: 0x2E */
  __IO uint16_t SEL24;                             /**< Crossbar A Select Register 24, offset: 0x30 */
  __IO uint16_t SEL25;                             /**< Crossbar A Select Register 25, offset: 0x32 */
  __IO uint16_t SEL26;                             /**< Crossbar A Select Register 26, offset: 0x34 */
  __IO uint16_t SEL27;                             /**< Crossbar A Select Register 27, offset: 0x36 */
  __IO uint16_t SEL28;                             /**< Crossbar A Select Register 28, offset: 0x38 */
  __IO uint16_t SEL29;                             /**< Crossbar A Select Register 29, offset: 0x3A */
  __IO uint16_t CTRL0;                             /**< Crossbar A Control Register 0, offset: 0x3C */
  __IO uint16_t CTRL1;                             /**< Crossbar A Control Register 1, offset: 0x3E */
} XBARA_Type;

/* ----------------------------------------------------------------------------
   -- XBARA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XBARA_Register_Masks XBARA Register Masks
 * @{
 */

/*! @name SEL0 - Crossbar A Select Register 0 */
#define XBARA_SEL0_SEL0_MASK                     (0x3FU)
#define XBARA_SEL0_SEL0_SHIFT                    (0U)
#define XBARA_SEL0_SEL0(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL0_SEL0_SHIFT)) & XBARA_SEL0_SEL0_MASK)
#define XBARA_SEL0_SEL1_MASK                     (0x3F00U)
#define XBARA_SEL0_SEL1_SHIFT                    (8U)
#define XBARA_SEL0_SEL1(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL0_SEL1_SHIFT)) & XBARA_SEL0_SEL1_MASK)

/*! @name SEL1 - Crossbar A Select Register 1 */
#define XBARA_SEL1_SEL2_MASK                     (0x3FU)
#define XBARA_SEL1_SEL2_SHIFT                    (0U)
#define XBARA_SEL1_SEL2(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL1_SEL2_SHIFT)) & XBARA_SEL1_SEL2_MASK)
#define XBARA_SEL1_SEL3_MASK                     (0x3F00U)
#define XBARA_SEL1_SEL3_SHIFT                    (8U)
#define XBARA_SEL1_SEL3(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL1_SEL3_SHIFT)) & XBARA_SEL1_SEL3_MASK)

/*! @name SEL2 - Crossbar A Select Register 2 */
#define XBARA_SEL2_SEL4_MASK                     (0x3FU)
#define XBARA_SEL2_SEL4_SHIFT                    (0U)
#define XBARA_SEL2_SEL4(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL2_SEL4_SHIFT)) & XBARA_SEL2_SEL4_MASK)
#define XBARA_SEL2_SEL5_MASK                     (0x3F00U)
#define XBARA_SEL2_SEL5_SHIFT                    (8U)
#define XBARA_SEL2_SEL5(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL2_SEL5_SHIFT)) & XBARA_SEL2_SEL5_MASK)

/*! @name SEL3 - Crossbar A Select Register 3 */
#define XBARA_SEL3_SEL6_MASK                     (0x3FU)
#define XBARA_SEL3_SEL6_SHIFT                    (0U)
#define XBARA_SEL3_SEL6(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL3_SEL6_SHIFT)) & XBARA_SEL3_SEL6_MASK)
#define XBARA_SEL3_SEL7_MASK                     (0x3F00U)
#define XBARA_SEL3_SEL7_SHIFT                    (8U)
#define XBARA_SEL3_SEL7(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL3_SEL7_SHIFT)) & XBARA_SEL3_SEL7_MASK)

/*! @name SEL4 - Crossbar A Select Register 4 */
#define XBARA_SEL4_SEL8_MASK                     (0x3FU)
#define XBARA_SEL4_SEL8_SHIFT                    (0U)
#define XBARA_SEL4_SEL8(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL4_SEL8_SHIFT)) & XBARA_SEL4_SEL8_MASK)
#define XBARA_SEL4_SEL9_MASK                     (0x3F00U)
#define XBARA_SEL4_SEL9_SHIFT                    (8U)
#define XBARA_SEL4_SEL9(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL4_SEL9_SHIFT)) & XBARA_SEL4_SEL9_MASK)

/*! @name SEL5 - Crossbar A Select Register 5 */
#define XBARA_SEL5_SEL10_MASK                    (0x3FU)
#define XBARA_SEL5_SEL10_SHIFT                   (0U)
#define XBARA_SEL5_SEL10(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL5_SEL10_SHIFT)) & XBARA_SEL5_SEL10_MASK)
#define XBARA_SEL5_SEL11_MASK                    (0x3F00U)
#define XBARA_SEL5_SEL11_SHIFT                   (8U)
#define XBARA_SEL5_SEL11(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL5_SEL11_SHIFT)) & XBARA_SEL5_SEL11_MASK)

/*! @name SEL6 - Crossbar A Select Register 6 */
#define XBARA_SEL6_SEL12_MASK                    (0x3FU)
#define XBARA_SEL6_SEL12_SHIFT                   (0U)
#define XBARA_SEL6_SEL12(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL6_SEL12_SHIFT)) & XBARA_SEL6_SEL12_MASK)
#define XBARA_SEL6_SEL13_MASK                    (0x3F00U)
#define XBARA_SEL6_SEL13_SHIFT                   (8U)
#define XBARA_SEL6_SEL13(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL6_SEL13_SHIFT)) & XBARA_SEL6_SEL13_MASK)

/*! @name SEL7 - Crossbar A Select Register 7 */
#define XBARA_SEL7_SEL14_MASK                    (0x3FU)
#define XBARA_SEL7_SEL14_SHIFT                   (0U)
#define XBARA_SEL7_SEL14(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL7_SEL14_SHIFT)) & XBARA_SEL7_SEL14_MASK)
#define XBARA_SEL7_SEL15_MASK                    (0x3F00U)
#define XBARA_SEL7_SEL15_SHIFT                   (8U)
#define XBARA_SEL7_SEL15(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL7_SEL15_SHIFT)) & XBARA_SEL7_SEL15_MASK)

/*! @name SEL8 - Crossbar A Select Register 8 */
#define XBARA_SEL8_SEL16_MASK                    (0x3FU)
#define XBARA_SEL8_SEL16_SHIFT                   (0U)
#define XBARA_SEL8_SEL16(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL8_SEL16_SHIFT)) & XBARA_SEL8_SEL16_MASK)
#define XBARA_SEL8_SEL17_MASK                    (0x3F00U)
#define XBARA_SEL8_SEL17_SHIFT                   (8U)
#define XBARA_SEL8_SEL17(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL8_SEL17_SHIFT)) & XBARA_SEL8_SEL17_MASK)

/*! @name SEL9 - Crossbar A Select Register 9 */
#define XBARA_SEL9_SEL18_MASK                    (0x3FU)
#define XBARA_SEL9_SEL18_SHIFT                   (0U)
#define XBARA_SEL9_SEL18(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL9_SEL18_SHIFT)) & XBARA_SEL9_SEL18_MASK)
#define XBARA_SEL9_SEL19_MASK                    (0x3F00U)
#define XBARA_SEL9_SEL19_SHIFT                   (8U)
#define XBARA_SEL9_SEL19(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL9_SEL19_SHIFT)) & XBARA_SEL9_SEL19_MASK)

/*! @name SEL10 - Crossbar A Select Register 10 */
#define XBARA_SEL10_SEL20_MASK                   (0x3FU)
#define XBARA_SEL10_SEL20_SHIFT                  (0U)
#define XBARA_SEL10_SEL20(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL10_SEL20_SHIFT)) & XBARA_SEL10_SEL20_MASK)
#define XBARA_SEL10_SEL21_MASK                   (0x3F00U)
#define XBARA_SEL10_SEL21_SHIFT                  (8U)
#define XBARA_SEL10_SEL21(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL10_SEL21_SHIFT)) & XBARA_SEL10_SEL21_MASK)

/*! @name SEL11 - Crossbar A Select Register 11 */
#define XBARA_SEL11_SEL22_MASK                   (0x3FU)
#define XBARA_SEL11_SEL22_SHIFT                  (0U)
#define XBARA_SEL11_SEL22(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL11_SEL22_SHIFT)) & XBARA_SEL11_SEL22_MASK)
#define XBARA_SEL11_SEL23_MASK                   (0x3F00U)
#define XBARA_SEL11_SEL23_SHIFT                  (8U)
#define XBARA_SEL11_SEL23(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL11_SEL23_SHIFT)) & XBARA_SEL11_SEL23_MASK)

/*! @name SEL12 - Crossbar A Select Register 12 */
#define XBARA_SEL12_SEL24_MASK                   (0x3FU)
#define XBARA_SEL12_SEL24_SHIFT                  (0U)
#define XBARA_SEL12_SEL24(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL12_SEL24_SHIFT)) & XBARA_SEL12_SEL24_MASK)
#define XBARA_SEL12_SEL25_MASK                   (0x3F00U)
#define XBARA_SEL12_SEL25_SHIFT                  (8U)
#define XBARA_SEL12_SEL25(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL12_SEL25_SHIFT)) & XBARA_SEL12_SEL25_MASK)

/*! @name SEL13 - Crossbar A Select Register 13 */
#define XBARA_SEL13_SEL26_MASK                   (0x3FU)
#define XBARA_SEL13_SEL26_SHIFT                  (0U)
#define XBARA_SEL13_SEL26(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL13_SEL26_SHIFT)) & XBARA_SEL13_SEL26_MASK)
#define XBARA_SEL13_SEL27_MASK                   (0x3F00U)
#define XBARA_SEL13_SEL27_SHIFT                  (8U)
#define XBARA_SEL13_SEL27(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL13_SEL27_SHIFT)) & XBARA_SEL13_SEL27_MASK)

/*! @name SEL14 - Crossbar A Select Register 14 */
#define XBARA_SEL14_SEL28_MASK                   (0x3FU)
#define XBARA_SEL14_SEL28_SHIFT                  (0U)
#define XBARA_SEL14_SEL28(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL14_SEL28_SHIFT)) & XBARA_SEL14_SEL28_MASK)
#define XBARA_SEL14_SEL29_MASK                   (0x3F00U)
#define XBARA_SEL14_SEL29_SHIFT                  (8U)
#define XBARA_SEL14_SEL29(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL14_SEL29_SHIFT)) & XBARA_SEL14_SEL29_MASK)

/*! @name SEL15 - Crossbar A Select Register 15 */
#define XBARA_SEL15_SEL30_MASK                   (0x3FU)
#define XBARA_SEL15_SEL30_SHIFT                  (0U)
#define XBARA_SEL15_SEL30(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL15_SEL30_SHIFT)) & XBARA_SEL15_SEL30_MASK)
#define XBARA_SEL15_SEL31_MASK                   (0x3F00U)
#define XBARA_SEL15_SEL31_SHIFT                  (8U)
#define XBARA_SEL15_SEL31(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL15_SEL31_SHIFT)) & XBARA_SEL15_SEL31_MASK)

/*! @name SEL16 - Crossbar A Select Register 16 */
#define XBARA_SEL16_SEL32_MASK                   (0x3FU)
#define XBARA_SEL16_SEL32_SHIFT                  (0U)
#define XBARA_SEL16_SEL32(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL16_SEL32_SHIFT)) & XBARA_SEL16_SEL32_MASK)
#define XBARA_SEL16_SEL33_MASK                   (0x3F00U)
#define XBARA_SEL16_SEL33_SHIFT                  (8U)
#define XBARA_SEL16_SEL33(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL16_SEL33_SHIFT)) & XBARA_SEL16_SEL33_MASK)

/*! @name SEL17 - Crossbar A Select Register 17 */
#define XBARA_SEL17_SEL34_MASK                   (0x3FU)
#define XBARA_SEL17_SEL34_SHIFT                  (0U)
#define XBARA_SEL17_SEL34(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL17_SEL34_SHIFT)) & XBARA_SEL17_SEL34_MASK)
#define XBARA_SEL17_SEL35_MASK                   (0x3F00U)
#define XBARA_SEL17_SEL35_SHIFT                  (8U)
#define XBARA_SEL17_SEL35(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL17_SEL35_SHIFT)) & XBARA_SEL17_SEL35_MASK)

/*! @name SEL18 - Crossbar A Select Register 18 */
#define XBARA_SEL18_SEL36_MASK                   (0x3FU)
#define XBARA_SEL18_SEL36_SHIFT                  (0U)
#define XBARA_SEL18_SEL36(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL18_SEL36_SHIFT)) & XBARA_SEL18_SEL36_MASK)
#define XBARA_SEL18_SEL37_MASK                   (0x3F00U)
#define XBARA_SEL18_SEL37_SHIFT                  (8U)
#define XBARA_SEL18_SEL37(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL18_SEL37_SHIFT)) & XBARA_SEL18_SEL37_MASK)

/*! @name SEL19 - Crossbar A Select Register 19 */
#define XBARA_SEL19_SEL38_MASK                   (0x3FU)
#define XBARA_SEL19_SEL38_SHIFT                  (0U)
#define XBARA_SEL19_SEL38(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL19_SEL38_SHIFT)) & XBARA_SEL19_SEL38_MASK)
#define XBARA_SEL19_SEL39_MASK                   (0x3F00U)
#define XBARA_SEL19_SEL39_SHIFT                  (8U)
#define XBARA_SEL19_SEL39(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL19_SEL39_SHIFT)) & XBARA_SEL19_SEL39_MASK)

/*! @name SEL20 - Crossbar A Select Register 20 */
#define XBARA_SEL20_SEL40_MASK                   (0x3FU)
#define XBARA_SEL20_SEL40_SHIFT                  (0U)
#define XBARA_SEL20_SEL40(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL20_SEL40_SHIFT)) & XBARA_SEL20_SEL40_MASK)
#define XBARA_SEL20_SEL41_MASK                   (0x3F00U)
#define XBARA_SEL20_SEL41_SHIFT                  (8U)
#define XBARA_SEL20_SEL41(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL20_SEL41_SHIFT)) & XBARA_SEL20_SEL41_MASK)

/*! @name SEL21 - Crossbar A Select Register 21 */
#define XBARA_SEL21_SEL42_MASK                   (0x3FU)
#define XBARA_SEL21_SEL42_SHIFT                  (0U)
#define XBARA_SEL21_SEL42(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL21_SEL42_SHIFT)) & XBARA_SEL21_SEL42_MASK)
#define XBARA_SEL21_SEL43_MASK                   (0x3F00U)
#define XBARA_SEL21_SEL43_SHIFT                  (8U)
#define XBARA_SEL21_SEL43(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL21_SEL43_SHIFT)) & XBARA_SEL21_SEL43_MASK)

/*! @name SEL22 - Crossbar A Select Register 22 */
#define XBARA_SEL22_SEL44_MASK                   (0x3FU)
#define XBARA_SEL22_SEL44_SHIFT                  (0U)
#define XBARA_SEL22_SEL44(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL22_SEL44_SHIFT)) & XBARA_SEL22_SEL44_MASK)
#define XBARA_SEL22_SEL45_MASK                   (0x3F00U)
#define XBARA_SEL22_SEL45_SHIFT                  (8U)
#define XBARA_SEL22_SEL45(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL22_SEL45_SHIFT)) & XBARA_SEL22_SEL45_MASK)

/*! @name SEL23 - Crossbar A Select Register 23 */
#define XBARA_SEL23_SEL46_MASK                   (0x3FU)
#define XBARA_SEL23_SEL46_SHIFT                  (0U)
#define XBARA_SEL23_SEL46(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL23_SEL46_SHIFT)) & XBARA_SEL23_SEL46_MASK)
#define XBARA_SEL23_SEL47_MASK                   (0x3F00U)
#define XBARA_SEL23_SEL47_SHIFT                  (8U)
#define XBARA_SEL23_SEL47(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL23_SEL47_SHIFT)) & XBARA_SEL23_SEL47_MASK)

/*! @name SEL24 - Crossbar A Select Register 24 */
#define XBARA_SEL24_SEL48_MASK                   (0x3FU)
#define XBARA_SEL24_SEL48_SHIFT                  (0U)
#define XBARA_SEL24_SEL48(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL24_SEL48_SHIFT)) & XBARA_SEL24_SEL48_MASK)
#define XBARA_SEL24_SEL49_MASK                   (0x3F00U)
#define XBARA_SEL24_SEL49_SHIFT                  (8U)
#define XBARA_SEL24_SEL49(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL24_SEL49_SHIFT)) & XBARA_SEL24_SEL49_MASK)

/*! @name SEL25 - Crossbar A Select Register 25 */
#define XBARA_SEL25_SEL50_MASK                   (0x3FU)
#define XBARA_SEL25_SEL50_SHIFT                  (0U)
#define XBARA_SEL25_SEL50(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL25_SEL50_SHIFT)) & XBARA_SEL25_SEL50_MASK)
#define XBARA_SEL25_SEL51_MASK                   (0x3F00U)
#define XBARA_SEL25_SEL51_SHIFT                  (8U)
#define XBARA_SEL25_SEL51(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL25_SEL51_SHIFT)) & XBARA_SEL25_SEL51_MASK)

/*! @name SEL26 - Crossbar A Select Register 26 */
#define XBARA_SEL26_SEL52_MASK                   (0x3FU)
#define XBARA_SEL26_SEL52_SHIFT                  (0U)
#define XBARA_SEL26_SEL52(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL26_SEL52_SHIFT)) & XBARA_SEL26_SEL52_MASK)
#define XBARA_SEL26_SEL53_MASK                   (0x3F00U)
#define XBARA_SEL26_SEL53_SHIFT                  (8U)
#define XBARA_SEL26_SEL53(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL26_SEL53_SHIFT)) & XBARA_SEL26_SEL53_MASK)

/*! @name SEL27 - Crossbar A Select Register 27 */
#define XBARA_SEL27_SEL54_MASK                   (0x3FU)
#define XBARA_SEL27_SEL54_SHIFT                  (0U)
#define XBARA_SEL27_SEL54(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL27_SEL54_SHIFT)) & XBARA_SEL27_SEL54_MASK)
#define XBARA_SEL27_SEL55_MASK                   (0x3F00U)
#define XBARA_SEL27_SEL55_SHIFT                  (8U)
#define XBARA_SEL27_SEL55(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL27_SEL55_SHIFT)) & XBARA_SEL27_SEL55_MASK)

/*! @name SEL28 - Crossbar A Select Register 28 */
#define XBARA_SEL28_SEL56_MASK                   (0x3FU)
#define XBARA_SEL28_SEL56_SHIFT                  (0U)
#define XBARA_SEL28_SEL56(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL28_SEL56_SHIFT)) & XBARA_SEL28_SEL56_MASK)
#define XBARA_SEL28_SEL57_MASK                   (0x3F00U)
#define XBARA_SEL28_SEL57_SHIFT                  (8U)
#define XBARA_SEL28_SEL57(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL28_SEL57_SHIFT)) & XBARA_SEL28_SEL57_MASK)

/*! @name SEL29 - Crossbar A Select Register 29 */
#define XBARA_SEL29_SEL58_MASK                   (0x3FU)
#define XBARA_SEL29_SEL58_SHIFT                  (0U)
#define XBARA_SEL29_SEL58(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL29_SEL58_SHIFT)) & XBARA_SEL29_SEL58_MASK)

/*! @name CTRL0 - Crossbar A Control Register 0 */
#define XBARA_CTRL0_DEN0_MASK                    (0x1U)
#define XBARA_CTRL0_DEN0_SHIFT                   (0U)
#define XBARA_CTRL0_DEN0(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL0_DEN0_SHIFT)) & XBARA_CTRL0_DEN0_MASK)
#define XBARA_CTRL0_IEN0_MASK                    (0x2U)
#define XBARA_CTRL0_IEN0_SHIFT                   (1U)
#define XBARA_CTRL0_IEN0(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL0_IEN0_SHIFT)) & XBARA_CTRL0_IEN0_MASK)
#define XBARA_CTRL0_EDGE0_MASK                   (0xCU)
#define XBARA_CTRL0_EDGE0_SHIFT                  (2U)
#define XBARA_CTRL0_EDGE0(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL0_EDGE0_SHIFT)) & XBARA_CTRL0_EDGE0_MASK)
#define XBARA_CTRL0_STS0_MASK                    (0x10U)
#define XBARA_CTRL0_STS0_SHIFT                   (4U)
#define XBARA_CTRL0_STS0(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL0_STS0_SHIFT)) & XBARA_CTRL0_STS0_MASK)
#define XBARA_CTRL0_DEN1_MASK                    (0x100U)
#define XBARA_CTRL0_DEN1_SHIFT                   (8U)
#define XBARA_CTRL0_DEN1(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL0_DEN1_SHIFT)) & XBARA_CTRL0_DEN1_MASK)
#define XBARA_CTRL0_IEN1_MASK                    (0x200U)
#define XBARA_CTRL0_IEN1_SHIFT                   (9U)
#define XBARA_CTRL0_IEN1(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL0_IEN1_SHIFT)) & XBARA_CTRL0_IEN1_MASK)
#define XBARA_CTRL0_EDGE1_MASK                   (0xC00U)
#define XBARA_CTRL0_EDGE1_SHIFT                  (10U)
#define XBARA_CTRL0_EDGE1(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL0_EDGE1_SHIFT)) & XBARA_CTRL0_EDGE1_MASK)
#define XBARA_CTRL0_STS1_MASK                    (0x1000U)
#define XBARA_CTRL0_STS1_SHIFT                   (12U)
#define XBARA_CTRL0_STS1(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL0_STS1_SHIFT)) & XBARA_CTRL0_STS1_MASK)

/*! @name CTRL1 - Crossbar A Control Register 1 */
#define XBARA_CTRL1_DEN2_MASK                    (0x1U)
#define XBARA_CTRL1_DEN2_SHIFT                   (0U)
#define XBARA_CTRL1_DEN2(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL1_DEN2_SHIFT)) & XBARA_CTRL1_DEN2_MASK)
#define XBARA_CTRL1_IEN2_MASK                    (0x2U)
#define XBARA_CTRL1_IEN2_SHIFT                   (1U)
#define XBARA_CTRL1_IEN2(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL1_IEN2_SHIFT)) & XBARA_CTRL1_IEN2_MASK)
#define XBARA_CTRL1_EDGE2_MASK                   (0xCU)
#define XBARA_CTRL1_EDGE2_SHIFT                  (2U)
#define XBARA_CTRL1_EDGE2(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL1_EDGE2_SHIFT)) & XBARA_CTRL1_EDGE2_MASK)
#define XBARA_CTRL1_STS2_MASK                    (0x10U)
#define XBARA_CTRL1_STS2_SHIFT                   (4U)
#define XBARA_CTRL1_STS2(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL1_STS2_SHIFT)) & XBARA_CTRL1_STS2_MASK)
#define XBARA_CTRL1_DEN3_MASK                    (0x100U)
#define XBARA_CTRL1_DEN3_SHIFT                   (8U)
#define XBARA_CTRL1_DEN3(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL1_DEN3_SHIFT)) & XBARA_CTRL1_DEN3_MASK)
#define XBARA_CTRL1_IEN3_MASK                    (0x200U)
#define XBARA_CTRL1_IEN3_SHIFT                   (9U)
#define XBARA_CTRL1_IEN3(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL1_IEN3_SHIFT)) & XBARA_CTRL1_IEN3_MASK)
#define XBARA_CTRL1_EDGE3_MASK                   (0xC00U)
#define XBARA_CTRL1_EDGE3_SHIFT                  (10U)
#define XBARA_CTRL1_EDGE3(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL1_EDGE3_SHIFT)) & XBARA_CTRL1_EDGE3_MASK)
#define XBARA_CTRL1_STS3_MASK                    (0x1000U)
#define XBARA_CTRL1_STS3_SHIFT                   (12U)
#define XBARA_CTRL1_STS3(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL1_STS3_SHIFT)) & XBARA_CTRL1_STS3_MASK)


/*!
 * @}
 */ /* end of group XBARA_Register_Masks */


/* XBARA - Peripheral instance base addresses */
/** Peripheral XBARA base address */
#define XBARA_BASE                               (0x40059000u)
/** Peripheral XBARA base pointer */
#define XBARA                                    ((XBARA_Type *)XBARA_BASE)
/** Array initializer of XBARA peripheral base addresses */
#define XBARA_BASE_ADDRS                         { XBARA_BASE }
/** Array initializer of XBARA peripheral base pointers */
#define XBARA_BASE_PTRS                          { XBARA }
/** Interrupt vectors for the XBARA peripheral type */
#define XBARA_IRQS                               { XBARA_IRQn }

/*!
 * @}
 */ /* end of group XBARA_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- XBARB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XBARB_Peripheral_Access_Layer XBARB Peripheral Access Layer
 * @{
 */

/** XBARB - Register Layout Typedef */
typedef struct {
  __IO uint16_t SEL0;                              /**< Crossbar B Select Register 0, offset: 0x0 */
  __IO uint16_t SEL1;                              /**< Crossbar B Select Register 1, offset: 0x2 */
  __IO uint16_t SEL2;                              /**< Crossbar B Select Register 2, offset: 0x4 */
  __IO uint16_t SEL3;                              /**< Crossbar B Select Register 3, offset: 0x6 */
  __IO uint16_t SEL4;                              /**< Crossbar B Select Register 4, offset: 0x8 */
  __IO uint16_t SEL5;                              /**< Crossbar B Select Register 5, offset: 0xA */
  __IO uint16_t SEL6;                              /**< Crossbar B Select Register 6, offset: 0xC */
  __IO uint16_t SEL7;                              /**< Crossbar B Select Register 7, offset: 0xE */
} XBARB_Type;

/* ----------------------------------------------------------------------------
   -- XBARB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XBARB_Register_Masks XBARB Register Masks
 * @{
 */

/*! @name SEL0 - Crossbar B Select Register 0 */
#define XBARB_SEL0_SEL0_MASK                     (0x3FU)
#define XBARB_SEL0_SEL0_SHIFT                    (0U)
#define XBARB_SEL0_SEL0(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL0_SEL0_SHIFT)) & XBARB_SEL0_SEL0_MASK)
#define XBARB_SEL0_SEL1_MASK                     (0x3F00U)
#define XBARB_SEL0_SEL1_SHIFT                    (8U)
#define XBARB_SEL0_SEL1(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL0_SEL1_SHIFT)) & XBARB_SEL0_SEL1_MASK)

/*! @name SEL1 - Crossbar B Select Register 1 */
#define XBARB_SEL1_SEL2_MASK                     (0x3FU)
#define XBARB_SEL1_SEL2_SHIFT                    (0U)
#define XBARB_SEL1_SEL2(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL1_SEL2_SHIFT)) & XBARB_SEL1_SEL2_MASK)
#define XBARB_SEL1_SEL3_MASK                     (0x3F00U)
#define XBARB_SEL1_SEL3_SHIFT                    (8U)
#define XBARB_SEL1_SEL3(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL1_SEL3_SHIFT)) & XBARB_SEL1_SEL3_MASK)

/*! @name SEL2 - Crossbar B Select Register 2 */
#define XBARB_SEL2_SEL4_MASK                     (0x3FU)
#define XBARB_SEL2_SEL4_SHIFT                    (0U)
#define XBARB_SEL2_SEL4(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL2_SEL4_SHIFT)) & XBARB_SEL2_SEL4_MASK)
#define XBARB_SEL2_SEL5_MASK                     (0x3F00U)
#define XBARB_SEL2_SEL5_SHIFT                    (8U)
#define XBARB_SEL2_SEL5(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL2_SEL5_SHIFT)) & XBARB_SEL2_SEL5_MASK)

/*! @name SEL3 - Crossbar B Select Register 3 */
#define XBARB_SEL3_SEL6_MASK                     (0x3FU)
#define XBARB_SEL3_SEL6_SHIFT                    (0U)
#define XBARB_SEL3_SEL6(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL3_SEL6_SHIFT)) & XBARB_SEL3_SEL6_MASK)
#define XBARB_SEL3_SEL7_MASK                     (0x3F00U)
#define XBARB_SEL3_SEL7_SHIFT                    (8U)
#define XBARB_SEL3_SEL7(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL3_SEL7_SHIFT)) & XBARB_SEL3_SEL7_MASK)

/*! @name SEL4 - Crossbar B Select Register 4 */
#define XBARB_SEL4_SEL8_MASK                     (0x3FU)
#define XBARB_SEL4_SEL8_SHIFT                    (0U)
#define XBARB_SEL4_SEL8(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL4_SEL8_SHIFT)) & XBARB_SEL4_SEL8_MASK)
#define XBARB_SEL4_SEL9_MASK                     (0x3F00U)
#define XBARB_SEL4_SEL9_SHIFT                    (8U)
#define XBARB_SEL4_SEL9(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL4_SEL9_SHIFT)) & XBARB_SEL4_SEL9_MASK)

/*! @name SEL5 - Crossbar B Select Register 5 */
#define XBARB_SEL5_SEL10_MASK                    (0x3FU)
#define XBARB_SEL5_SEL10_SHIFT                   (0U)
#define XBARB_SEL5_SEL10(x)                      (((uint16_t)(((uint16_t)(x)) << XBARB_SEL5_SEL10_SHIFT)) & XBARB_SEL5_SEL10_MASK)
#define XBARB_SEL5_SEL11_MASK                    (0x3F00U)
#define XBARB_SEL5_SEL11_SHIFT                   (8U)
#define XBARB_SEL5_SEL11(x)                      (((uint16_t)(((uint16_t)(x)) << XBARB_SEL5_SEL11_SHIFT)) & XBARB_SEL5_SEL11_MASK)

/*! @name SEL6 - Crossbar B Select Register 6 */
#define XBARB_SEL6_SEL12_MASK                    (0x3FU)
#define XBARB_SEL6_SEL12_SHIFT                   (0U)
#define XBARB_SEL6_SEL12(x)                      (((uint16_t)(((uint16_t)(x)) << XBARB_SEL6_SEL12_SHIFT)) & XBARB_SEL6_SEL12_MASK)
#define XBARB_SEL6_SEL13_MASK                    (0x3F00U)
#define XBARB_SEL6_SEL13_SHIFT                   (8U)
#define XBARB_SEL6_SEL13(x)                      (((uint16_t)(((uint16_t)(x)) << XBARB_SEL6_SEL13_SHIFT)) & XBARB_SEL6_SEL13_MASK)

/*! @name SEL7 - Crossbar B Select Register 7 */
#define XBARB_SEL7_SEL14_MASK                    (0x3FU)
#define XBARB_SEL7_SEL14_SHIFT                   (0U)
#define XBARB_SEL7_SEL14(x)                      (((uint16_t)(((uint16_t)(x)) << XBARB_SEL7_SEL14_SHIFT)) & XBARB_SEL7_SEL14_MASK)
#define XBARB_SEL7_SEL15_MASK                    (0x3F00U)
#define XBARB_SEL7_SEL15_SHIFT                   (8U)
#define XBARB_SEL7_SEL15(x)                      (((uint16_t)(((uint16_t)(x)) << XBARB_SEL7_SEL15_SHIFT)) & XBARB_SEL7_SEL15_MASK)


/*!
 * @}
 */ /* end of group XBARB_Register_Masks */


/* XBARB - Peripheral instance base addresses */
/** Peripheral XBARB base address */
#define XBARB_BASE                               (0x4005A000u)
/** Peripheral XBARB base pointer */
#define XBARB                                    ((XBARB_Type *)XBARB_BASE)
/** Array initializer of XBARB peripheral base addresses */
#define XBARB_BASE_ADDRS                         { XBARB_BASE }
/** Array initializer of XBARB peripheral base pointers */
#define XBARB_BASE_PTRS                          { XBARB }

/*!
 * @}
 */ /* end of group XBARB_Peripheral_Access_Layer */


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
 */ /* end of group Peripheral_access_layer */


/* ----------------------------------------------------------------------------
   -- SDK Compatibility
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SDK_Compatibility_Symbols SDK Compatibility
 * @{
 */

#define DSPI0                     SPI0
#define DSPI1                     SPI1
#define DSPI2                     SPI2
#define FLEXCAN0                  CAN0
#define FLEXCAN1                  CAN1
#define FLEXCAN2                  CAN2
#define DMAMUX0                   DMAMUX

/*!
 * @}
 */ /* end of group SDK_Compatibility_Symbols */


#endif  /* _MKV58F24_H_ */


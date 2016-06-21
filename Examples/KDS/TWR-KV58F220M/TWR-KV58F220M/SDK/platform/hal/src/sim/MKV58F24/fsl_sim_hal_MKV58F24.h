/*
 * Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#if !defined(__FSL_SIM_HAL_MKV58F24_H__)
#define __FSL_SIM_HAL_MKV58F24_H__

/*! @addtogroup sim_hal_kv58f24*/
/*! @{*/
#include "fsl_sim_hal.h"
/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief WDOG clock source select */
typedef enum _clock_wdog_src_t
{
    kClockWdogSrcLpoClk,       /*!< LPO                                          */
    kClockWdogSrcAltClk,       /*!< Alternative clock, for K64F12 it is Bus clock. */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_wdog_src_kv58f24_t;
#else
} clock_wdog_src_t;
#endif


/*! @brief Debug trace clock source select */
typedef enum _clock_trace_src_t
{
    kClockTraceSrcMcgoutClk,       /*!< MCG out clock  */
    kClockTraceSrcCoreClk,         /*!< core clock     */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_trace_src_kv58f24_t;
#else
} clock_trace_src_t;
#endif

/*! @brief Debug trace clock source select */
typedef enum _clock_nanoedge_clk2x_src
{
    kClockNanoedgeSrcMcgPllClk,       /*!< MCG out clock  */
    kClockNanoedgeSrcMcgPllClk2x,         /*!< core clock     */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_nanoedge_clk2x_src_kv58f24;
#else
} clock_nanoedge_clk2x_src;
#endif

/*! @brief SIM OSC32KSEL clock source select */
typedef enum _sim_osc32k_clock_sel
{
    kSimOsc32kSelOsc32k,      /* OSC 32k clock */
    kSimOsc32kSelReserved,    /* Reserved */
    kSimOsc32kSelReserved1,   /* Reserved */
    kSimOsc32kSelLpo          /* LPO clock */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_osc32k_clock_sel_kv58f24_t;
#else
} sim_osc32k_clock_sel_t;
#endif

/*! @brief SIM NANOEDGECLK2XSEL clock source select */
typedef enum _sim_nanoedge_clock_sel
{
    kSimNanoEdgeMcgPllClk,    /* MCG PLL clock */
    kSimNanoEdgeMcgPll2xClk,  /* MCG PLL 2X clock */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_nanoedge_clock_sel_kv58f24_t;
#else
} sim_nanoedge_clock_sel_t;
#endif

/*! @brief SIM TRACECLKSEL clock source select */
typedef enum _sim_trace_clock_sel
{
    kSimTraceMcgoutClk,       /* MCG out clock */
    kSimTraceCoreClk          /* core clock */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_trace_clock_sel_kv58f24_t;
#else
} sim_trace_clock_sel_t;
#endif

/*! @brief SIM HSADC trigger select */
typedef enum _sim_hsadc_trg_sel
{
    kSimHsadcTrgselPdb0Ext        = 0U,    /* PDB0_EXTRG for HSADC0A and HSADC1B                        */
    kSimHsadcTrgSelHighSpeedComp0 = 1U,    /* High speed comparator 0 output                            */
    kSimHsadcTrgSelHighSpeedComp1 = 2U,    /* High speed comparator 1 output                            */
    kSimHsadcTrgSelHighSpeedComp2 = 3U,    /* High speed comparator 2 output                            */
    kSimHsadcTrgSelPit0           = 4U,    /* PIT trigger 0                                             */
    kSimHsadcTrgSelPit1           = 5U,    /* PIT trigger 1                                             */
    kSimHsadcTrgSelPit2           = 6U,    /* PIT trigger 2                                             */
    kSimHsadcTrgSelPit3           = 7U,    /* PIT trigger 3                                             */
    kSimHsadcTrgSelFtm0           = 8U,    /* FTM0 trigger                                              */
    kSimHsadcTrgSelFtm1           = 9U,    /* FTM1 trigger                                              */
    kSimHsadcTrgSelFtm2           = 10U,   /* FTM2 trigger                                              */
    kSimHsadcTrgSelFtm3           = 11U,   /* FTM3 trigger                                              */
    kSimHsadcTrgSelxbaraout       = 12U,   /* XBARAOUT38 for HSADC0A, 1B and XBARAOUT41 for HSADC0B, 1A */
    kSimHsadcTrgSelLptimer        = 14U,   /* Low-power timer trigger                                   */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_hsadc_trg_sel_kv58f24_t;
#else
} sim_hsadc_trg_sel_t;
#endif

/*! @brief SIM ADCx trigger select */
typedef enum _sim_adc_trg_sel
{
    kSimAdcTrgselPdb0Ext          = 0U,    /*!< PDB0_EXTRG external trigger    */
    kSimAdcTrgSelHighSpeedComp0   = 1U,    /*!< High speed comparator 0 output */
    kSimAdcTrgSelHighSpeedComp1   = 2U,    /*!< High speed comparator 1 output */
    kSimAdcTrgSelHighSpeedComp2   = 3U,    /*!< High speed comparator 2 output */
    kSimAdcTrgSelPit0             = 4U,    /*!< PIT trigger 0                  */
    kSimAdcTrgSelPit1             = 5U,    /*!< PIT trigger 1                  */
    kSimAdcTrgSelPit2             = 6U,    /*!< PIT trigger 2                  */
    kSimAdcTrgSelPit3             = 7U,    /*!< PIT trigger 3                  */
    kSimAdcTrgSelFtm0             = 8U,    /*!< FTM0 trigger                   */
    kSimAdcTrgSelFtm1             = 9U,    /*!< FTM1 trigger                   */
    kSimAdcTrgSelFtm2             = 10U,   /*!< FTM2 trigger                   */
    kSimAdcTrgSelFtm3             = 11U,   /*!< FTM3 trigger                   */
    kSimAdcTrgSelxbaraout         = 12U,   /*!< XBARAOUT38                     */
    kSimAdcTrgSelLptimer          = 14U,   /*!< Low-power timer trigger        */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_adc_trg_sel_kv58f24_t;
#else
} sim_adc_trg_sel_t;
#endif

/*!
 * @brief Defines the type of enumerating HSADC converter's ID.
 */
typedef enum _sim_hsadc_conv_id
{
    kSimHsadcConvA = 0U,/*!< ID for HSADC converter A. */
    kSimHsadcConvB = 1U /*!< ID for HSADC converter B. */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_hsadc_conv_id_kv58f24_t;
#else
} sim_hsadc_conv_id_t;
#endif

/*! @brief SIM HSADC alternate trigger enable */
typedef enum _sim_hsadc_alttrg_sel_t
{
    kSimHsadcTrgenXbarout        = 0U,    /* XBARAOUT12, 13, 42, 43 for HSADC0A, 0B, 1A, 1B    */
    kSimHsadcTrgenPdb            = 1U,    /* PDB0CH0, 1CH1, 1CH1, 0Ch1 for HSADC0A, 0B, 1A, 1B */
    kSimHsadcTrgselALT           = 2U     /* alternate trigger                                 */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_hsadc_alttrg_sel_kv58f24_t;
#else
} sim_hsadc_alttrg_sel_t;
#endif

/*! @brief SIM SIM ADCx alternative conversion trigger select */
typedef enum _sim_adc_alttrg_sel
{
    kSimAdcAltTrgselXbarout    = 0U,  /*!< XBARAOUT29          */
    kSimAdcAltTrgselPDB0       = 1U,  /*!< PDB0 channel 1      */
    kSimAdcAltTrgselPDB1       = 2U,  /*!< PDB1 channel 0      */
    kSimAdcAltTrgselALT        = 3U,  /*!< Alternative trigger */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_adc_alttrg_sel_kv58f24_t;
#else
} sim_adc_alttrg_sel_t;
#endif

/*! @brief SIM ADCx pre-trigger select */
typedef enum _sim_adc_pretrg_sel
{
    kSimAdcPretrgselA,              /*!< Pre-trigger A selected for ADCx */
    kSimAdcPretrgselB               /*!< Pre-trigger B selected for ADCx */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_adc_pretrg_sel_kv58f24_t;
#else
} sim_adc_pretrg_sel_t;
#endif

/*! @brief DAC0 Hardware Trigger Input Source */
typedef enum _sim_dac_hw_trg_sel
{
    kSimDacHwTrgSelXbarout15   = 0U,    /* XBARA output 15  */
    kSimDacHwTrgSelPdb01Int    = 1U,    /* both PDB0 interval trigger 0 and PDB1 interval trigger 0  */
    kSimDacHwTrgSelPdb0Int     = 2U,    /* PDB0 interval trigger 0  */
    kSimDacHwTrgSelPdb1Int     = 3U,    /* PDB1 interval trigger 0  */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_dac_hw_trg_sel_kv58f24;
#else
} sim_dac_hw_trg_sel;
#endif

/*! @brief the ewm_in source of EWM module. */
typedef enum _sim_ewm_in_src
{
    kSimDacHwTrgSelXbarout58   = 0U,    /* XBARA output 58  */
    kSimDacHwTrgSelEwnInPin    = 1U,    /* EWM_IN Pin  */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_ewm_in_src_kv58f24;
#else
} sim_ewm_in_src;
#endif

/*! @brief CMP Sample/Window Input X Source*/
typedef enum _sim_cmp_win_in_src
{
    kSimCmpWinInSrcXbarout   = 0U,    /* XBARA output - Refer RM for specific module  */
    kSimCmpWinInSrcPdb01Int  = 1U,    /* CMP0 Sample/Window input driven by both PDB0 and PDB1 pulse-out channel 0  */
    kSimCmpWinInSrcPdb0Int   = 2U,    /* PDB0 interval trigger 0  */
    kSimCmpWinInSrcPdb1Int   = 3U,    /* PDB1 interval trigger 0  */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_cmp_win_in_src_kv58f24;
#else
} sim_cmp_win_in_src;
#endif

/*! @brief LPTMR clock source select */
typedef enum _clock_lptmr_src_t
{
    kClockLptmrSrcMcgIrClk,        /*!< MCGIRCLK  */
    kClockLptmrSrcLpoClk,          /*!< LPO clock      */
    kClockLptmrSrcEr32kClk,        /*!< ERCLK32K clock */
    kClockLptmrSrcOsc0erClkUndiv,  /*!< OSCERCLK_UNDIV clock */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_lptmr_src_kv58f24_t;
#else
} clock_lptmr_src_t;
#endif

/*! @brief SIM PLLFLLSEL clock source select */
typedef enum _clock_pllfll_sel
{
    kClockPllFllSelFll     = 0U,    /*!< Fll clock  */
    kClockPllFllSelPll     = 1U     /*!< Pll0 clock */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_pllfll_sel_kv58f24_t;
#else
} clock_pllfll_sel_t;
#endif

/*! @brief SIM external reference clock source select (OSC32KSEL). */
typedef enum _clock_er32k_src
{
    kClockEr32kSrcOsc0 = 0U, /*!< OSC0 clock (OSC032KCLK).  */
    kClockEr32kSrcLpo  = 3U, /*!< LPO clock.                */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_er32k_src_kv58f24_t;
#else
} clock_er32k_src_t;
#endif

/*! @brief SIM CLKOUT_SEL clock source select */
typedef enum _clock_clkout_src
{
    kClockClkoutSelFlexbusClk     = 0U,  /*!< Flexbus clock        */
    kClockClkoutSelFlashClk       = 2U,  /*!< Flash clock          */
    kClockClkoutSelLpoClk         = 3U,  /*!< LPO clock            */
    kClockClkoutSelMcgIrClk       = 4U,  /*!< MCGIRCLK             */
    kClockClkoutSelOsc0erClkUndiv = 5U,  /*!< OSCERCLK_UNDIV clock */
    kClockClkoutSelOsc0erClk      = 6U,  /*!< OSC0ERCLK            */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_clkout_src_kv58f24_t;
#else
} clock_clkout_src_t;
#endif

/*! @brief SIM timestamp clock source */
typedef enum _clock_time_src
{
    kClockTimeSrcCoreSysClk,  /*!< Core/system clock                       */
    kClockTimeSrcPllFllSel,   /*!< clock as selected by SOPT2[PLLFLLSEL].  */
    kClockTimeSrcOsc0erClk,   /*!< OSCERCLK clock                          */
    kClockTimeSrcExt          /*!< ENET 1588 clock in (ENET_1588_CLKIN)    */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_time_src_kv58f24_t;
#else
} clock_time_src_t;
#endif

/*! @brief SIM RMII clock source */
typedef enum _clock_rmii_src
{
    kClockRmiiSrcExtalClk,    /*!< EXTAL Clock                           */
    kClockRmiiSrcExt          /*!< ENET 1588 clock in (ENET_1588_CLKIN)  */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_rmii_src_kv58f24_t;
#else
} clock_rmii_src_t;
#endif

/*! @brief FLEXCAN clock source select */
typedef enum _clock_flexcan_src_t
{
    kClockFlexcanSrcOsc0erClk,    /*!< OSCERCLK  */
    kClockFlexcanSrcBusClk        /*!< Bus clock */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_flexcan_src_kv58f24_t;
#else
} clock_flexcan_src_t;
#endif

/*! @brief SIM SCGC bit index. */
#define FSL_SIM_SCGC_BIT(SCGCx, n) (((SCGCx-1U)<<5U) + n)

/*! @brief Clock gate name used for SIM_HAL_EnableClock/SIM_HAL_DisableClock. */
typedef enum _sim_clock_gate_name
{
    kSimClockGateUart4     = FSL_SIM_SCGC_BIT(1U, 10U),
    kSimClockGateUart5     = FSL_SIM_SCGC_BIT(1U, 11U),
    kSimClockGatePwm0      = FSL_SIM_SCGC_BIT(1U, 24U),
    kSimClockGatePwmB1     = FSL_SIM_SCGC_BIT(1U, 25U),
    kSimClockGatePwmB2     = FSL_SIM_SCGC_BIT(1U, 26U),
    kSimClockGatePwmB3     = FSL_SIM_SCGC_BIT(1U, 27U),

    kSimClockGateEnet0      = FSL_SIM_SCGC_BIT(2U, 0U),
    kSimClockGateHsadc1    = FSL_SIM_SCGC_BIT(2U, 28U),

    kSimClockGateTrng      = FSL_SIM_SCGC_BIT(3U, 0U),
    kSimClockGateFlexcan2  = FSL_SIM_SCGC_BIT(3U, 4U),
    kSimClockGateSpi2      = FSL_SIM_SCGC_BIT(3U, 12U),

    kSimClockGateEwm0      = FSL_SIM_SCGC_BIT(4U, 1U),
    kSimClockGateI2c0      = FSL_SIM_SCGC_BIT(4U, 6U),
    kSimClockGateI2c1      = FSL_SIM_SCGC_BIT(4U, 7U),
    kSimClockGateUart0     = FSL_SIM_SCGC_BIT(4U, 10U),
    kSimClockGateUart1     = FSL_SIM_SCGC_BIT(4U, 11U),
    kSimClockGateUart2     = FSL_SIM_SCGC_BIT(4U, 12U),
    kSimClockGateUart3     = FSL_SIM_SCGC_BIT(4U, 13U),
    kSimClockGateCmp       = FSL_SIM_SCGC_BIT(4U, 19U),
    kSimClockGatePwmA0     = FSL_SIM_SCGC_BIT(4U, 24U),
    kSimClockGatePwmA1     = FSL_SIM_SCGC_BIT(4U, 25U),
    kSimClockGatePwmA2     = FSL_SIM_SCGC_BIT(4U, 26U),
    kSimClockGatePwmA3     = FSL_SIM_SCGC_BIT(4U, 27U),

    kSimClockGateLptmr0    = FSL_SIM_SCGC_BIT(5U, 0U),
    kSimClockGatePortA     = FSL_SIM_SCGC_BIT(5U, 9U),
    kSimClockGatePortB     = FSL_SIM_SCGC_BIT(5U, 10U),
    kSimClockGatePortC     = FSL_SIM_SCGC_BIT(5U, 11U),
    kSimClockGatePortD     = FSL_SIM_SCGC_BIT(5U, 12U),
    kSimClockGatePortE     = FSL_SIM_SCGC_BIT(5U, 13U),
    kSimClockGateEnc0      = FSL_SIM_SCGC_BIT(5U, 21U),
    kSimClockGateXbarA     = FSL_SIM_SCGC_BIT(5U, 25U),
    kSimClockGateXbarB     = FSL_SIM_SCGC_BIT(5U, 26U),
    kSimClockGateAoi0      = FSL_SIM_SCGC_BIT(5U, 27U),
    kSimClockGateHsadc0    = FSL_SIM_SCGC_BIT(5U, 28U),

    kSimClockGateFtf0      = FSL_SIM_SCGC_BIT(6U, 0U),
    kSimClockGateDmamux0   = FSL_SIM_SCGC_BIT(6U, 1U),
    kSimClockGateFlexcan0  = FSL_SIM_SCGC_BIT(6U, 4U),
    kSimClockGateFlexcan1  = FSL_SIM_SCGC_BIT(6U, 5U),
    kSimClockGateFtm3      = FSL_SIM_SCGC_BIT(6U, 6U),
    kSimClockGateSpi0      = FSL_SIM_SCGC_BIT(6U, 12U),
    kSimClockGateSpi1      = FSL_SIM_SCGC_BIT(6U, 13U),
    kSimClockGatePdb1      = FSL_SIM_SCGC_BIT(6U, 17U),
    kSimClockGateCrc0      = FSL_SIM_SCGC_BIT(6U, 18U),
    kSimClockGatePdb0      = FSL_SIM_SCGC_BIT(6U, 22U),
    kSimClockGatePit0      = FSL_SIM_SCGC_BIT(6U, 23U),
    kSimClockGateFtm0      = FSL_SIM_SCGC_BIT(6U, 24U),
    kSimClockGateFtm1      = FSL_SIM_SCGC_BIT(6U, 25U),
    kSimClockGateFtm2      = FSL_SIM_SCGC_BIT(6U, 26U),
    kSimClockGateAdc0      = FSL_SIM_SCGC_BIT(6U, 27U),
    kSimClockGateDac0      = FSL_SIM_SCGC_BIT(6U, 31U),

    kSimClockGateDma0      = FSL_SIM_SCGC_BIT(7U, 8U),
    kSimClockGateMPU       = FSL_SIM_SCGC_BIT(7U, 2U),
    kSimClockGateFlexbus0   = FSL_SIM_SCGC_BIT(7U, 0U),
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_clock_gate_name_kv58f24_t;
#else
} sim_clock_gate_name_t;
#endif


/*! @brief SIM USB voltage regulator in standby mode setting during stop modes */
typedef enum _sim_usbsstby_stop
{
    kSimUsbsstbyNoRegulator,        /* regulator not in standby during Stop modes */
    kSimUsbsstbyWithRegulator       /* regulator in standby during Stop modes */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_usbsstby_stop_kv58f24_t;
#else
} sim_usbsstby_stop_t;
#endif

/*! @brief SIM USB voltage regulator in standby mode setting during VLPR and VLPW modes */
typedef enum _sim_usbvstby_stop
{
    kSimUsbvstbyNoRegulator,        /* regulator not in standby during VLPR and VLPW modes */
    kSimUsbvstbyWithRegulator       /* regulator in standby during VLPR and VLPW modes */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_usbvstby_stop_kv58f24_t;
#else
} sim_usbvstby_stop_t;
#endif

/*! @brief SIM CMT/UART pad drive strength */
typedef enum _sim_cmtuartpad_strengh
{
    kSimCmtuartSinglePad,           /* Single-pad drive strength for CMT IRO or UART0_TXD */
    kSimCmtuartDualPad              /* Dual-pad drive strength for CMT IRO or UART0_TXD */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_cmtuartpad_strengh_kv58f24_t;
#else
} sim_cmtuartpad_strengh_t;
#endif

/*! @brief SIM PTD7 pad drive strength */
typedef enum _sim_ptd7pad_strengh
{
    kSimPtd7padSinglePad,           /* Single-pad drive strength for PTD7 */
    kSimPtd7padDualPad              /* Dual-pad drive strength for PTD7 */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_ptd7pad_strengh_kv58f24_t;
#else
} sim_ptd7pad_strengh_t;
#endif

/*! @brief SIM FlexBus security level */
typedef enum _sim_flexbus_security_level
{
    kSimFbslLevel0,                 /* All off-chip accesses (op code and data) via the FlexBus */
                                    /* and DDR controller are disallowed */
    kSimFbslLevel1,                 /* Undefined */
    kSimFbslLevel2,                 /* Off-chip op code accesses are disallowed. Data accesses */
                                    /* are allowed */
    kSimFbslLevel3                  /* Off-chip op code accesses and data accesses are allowed */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_flexbus_security_level_kv58f24_t;
#else
} sim_flexbus_security_level_t;
#endif


/*! @brief SIM UART receive data source select */
typedef enum _sim_uart_rxsrc
{
    kSimUartRxsrcPin,               /* UARTx_RX Pin */
    kSimUartRxsrcCmp0,              /* CMP0 */
    kSimUartRxsrcCmp1,              /* CMP1 */
    kSimUartRxsrcReserved           /* Reserved */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_uart_rxsrc_kv58f24_t;
#else
} sim_uart_rxsrc_t;
#endif

/*! @brief SIM UART transmit data source select */
typedef enum _sim_uart_txsrc
{
    kSimUartTxsrcPin,    /* UARTx_TX Pin */
    kSimUartTxsrcFtm1,   /* UARTx_TX pin modulated with FTM1 channel 0 output */
    kSimUartTxsrcFtm2    /* UARTx_TX pin modulated with FTM2 channel 0 output */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_uart_txsrc_kv58f24_t;
#else
} sim_uart_txsrc_t;
#endif

/*! @brief SIM FlexTimer x trigger y select */
typedef enum _sim_ftm_trg_src
{
    kSimFtmTrgSrc0,                 /* FlexTimer x trigger y select 0 */
    kSimFtmTrgSrc1                  /* FlexTimer x trigger y select 1 */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_ftm_trg_src_kv58f24_t;
#else
} sim_ftm_trg_src_t;
#endif

/*! @brief SIM FlexTimer external clock select */
typedef enum _sim_ftm_clk_sel
{
    kSimFtmClkSel0,                 /* FTM CLKIN0 pin. */
    kSimFtmClkSel1,                 /* FTM CLKIN1 pin. */
    kSimFtmClkSel2                  /* FTM CLKIN2 pin. */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_ftm_clk_sel_kv58f24_t;
#else
} sim_ftm_clk_sel_t;
#endif

/*! @brief SIM FlexTimer x channel y input capture source select */
typedef enum _sim_ftm_ch_src
{
    kSimFtmChSrc0,                 /* See RM for details of each selection for each channel */
    kSimFtmChSrc1,                 /* See RM for details of each selection for each channel */
    kSimFtmChSrc2,                 /* See RM for details of each selection for each channel */
    kSimFtmChSrc3                  /* See RM for details of each selection for each channel */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_ftm_ch_src_kv58f24_t;
#else
} sim_ftm_ch_src_t;
#endif

/*! @brief SIM FlexTimer x channel y output source select */
typedef enum _sim_ftm_ch_out_src
{
    kSimFtmChOutSrc0,
    kSimFtmChOutSrc1,
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_ftm_ch_out_src_kv58f24_t;
#else
} sim_ftm_ch_out_src_t;
#endif

/*! @brief SIM FlexTimer x Fault y select */
typedef enum _sim_ftm_flt_sel
{
    kSimFtmFltSel0,                 /* FlexTimer x fault y select 0 */
    kSimFtmFltSel1                  /* FlexTimer x fault y select 1 */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_ftm_flt_sel_kv58f24_t;
#else
} sim_ftm_flt_sel_t;
#endif

/*! @brief SIM Timer/PWM external clock select */
typedef enum _sim_tpm_clk_sel
{
    kSimTpmClkSel0,                 /* Timer/PWM TPM_CLKIN0 pin. */
    kSimTpmClkSel1                  /* Timer/PWM TPM_CLKIN1 pin. */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_tpm_clk_sel_kv58f24_t;
#else
} sim_tpm_clk_sel_t;
#endif

/*! @brief SIM Timer/PWM x channel y input capture source select */
typedef enum _sim_tpm_ch_src
{
    kSimTpmChSrc0,                 /* TPMx_CH0 signal */
    kSimTpmChSrc1                  /* CMP0 output */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_tpm_ch_src_kv58f24_t;
#else
} sim_tpm_ch_src_t;
#endif

/*! @} */
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @addtogroup sim_hal
 * @{
 */

/*!
 * @brief Sets the clock out dividers setting.
 *
 * This function sets the setting for all clock out dividers at the same time.
 *
 * @param base     Base address for current SIM instance.
 * @param outdiv1      Outdivider1 setting
 * @param outdiv2      Outdivider2 setting
 * @param outdiv3      Outdivider3 setting
 * @param outdiv4      Outdivider4 setting
 */
void CLOCK_HAL_SetOutDiv(SIM_Type * base,
                       uint8_t outdiv1,
                       uint8_t outdiv2,
                       uint8_t outdiv3,
                       uint8_t outdiv4);

/*!
 * @brief Gets the clock out dividers setting.
 *
 * This function gets the setting for all clock out dividers at the same time.
 *
 * @param base     Base address for current SIM instance.
 * @param outdiv1      Outdivider1 setting
 * @param outdiv2      Outdivider2 setting
 * @param outdiv3      Outdivider3 setting
 * @param outdiv4      Outdivider4 setting
 */
void CLOCK_HAL_GetOutDiv(SIM_Type * base,
                         uint8_t *outdiv1,
                         uint8_t *outdiv2,
                         uint8_t *outdiv3,
                         uint8_t *outdiv4);

/*@}*/

/*! @name individual field access APIs*/
/*@{*/

#if FSL_FEATURE_SIM_OPT_HAS_RAMSIZE
/*!
 * @brief Gets RAM size.
 *
 * This function gets the RAM size. The field specifies the amount of system RAM
 * available on the device.
 *
 * @param base     Base address for current SIM instance.
 * @return size  RAM size on the device
 */
static inline uint32_t SIM_HAL_GetRamSize(SIM_Type* base)
{
    return SIM_BRD_SOPT1_RAMSIZE(base);
}
#endif /* FSL_FEATURE_SIM_OPT_HAS_RAMSIZE */

#if FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR
/*!
 * @brief Sets the USB voltage regulator enabled setting.
 *
 * This function  controls whether the USB voltage regulator is enabled. This bit
 * can only be written when the SOPT1CFG[URWE] bit is set. 
 *
 * @param base     Base address for current SIM instance.
 * @param enable   USB voltage regulator enable setting
 *                  - true: USB voltage regulator is enabled.
 *                  - false: USB voltage regulator is disabled.
 */
static inline void SIM_HAL_SetUsbVoltRegulatorCmd(SIM_Type* base, bool enable)
{
    SIM_BWR_SOPT1_USBREGEN(base, enable ? 1 : 0);
}

/*!
 * @brief Gets the USB voltage regulator enabled setting.
 *
 * This function  gets the USB voltage regulator enabled setting.
 *
 * @param base     Base address for current SIM instance.
 * @return enabled True if the USB voltage regulator is enabled.
 */
static inline bool SIM_HAL_GetUsbVoltRegulatorCmd(SIM_Type* base)
{
    return SIM_BRD_SOPT1_USBREGEN(base);
}

/*!
 * @brief Sets the USB voltage regulator in a standby mode setting during Stop, VLPS, LLS, and VLLS.
 *
 * This function  controls whether the USB voltage regulator is placed in a standby
 * mode during Stop, VLPS, LLS, and VLLS modes. This bit can only be written when the
 * SOPT1CFG[USSWE] bit is set.
 *
 * @param base     Base address for current SIM instance.
 * @param setting   USB voltage regulator in standby mode setting
 *                  - 0: USB voltage regulator not in standby during Stop, VLPS, LLS and
 *                       VLLS modes.
 *                  - 1: USB voltage regulator in standby during Stop, VLPS, LLS and VLLS
 *                       modes.
 */
static inline void SIM_HAL_SetUsbVoltRegulatorInStdbyDuringStopMode(SIM_Type* base,
                                                                    sim_usbsstby_stop_t setting)
{
    SIM_BWR_SOPT1_USBSSTBY(base, setting);
}

/*!
 * @brief Gets the USB voltage regulator in a standby mode setting.
 *
 * This function  gets the USB voltage regulator in a standby mode setting.
 *
 * @param base     Base address for current SIM instance.
 * @return setting  USB voltage regulator in a standby mode setting
 */
static inline sim_usbsstby_stop_t SIM_HAL_GetUsbVoltRegulatorInStdbyDuringStopMode(SIM_Type* base)
{
    return (sim_usbsstby_stop_t)SIM_BRD_SOPT1_USBSSTBY(base);
}

/*!
 * @brief Sets the USB voltage regulator in a standby mode during the VLPR or the VLPW.
 *
 * This function  controls whether the USB voltage regulator is placed in a standby
 * mode during the VLPR and the VLPW modes. This bit can only be written when the
 * SOPT1CFG[UVSWE] bit is set.
 *
 * @param base     Base address for current SIM instance.
 * @param setting   USB voltage regulator in standby mode setting
 *                  - 0: USB voltage regulator not in standby during VLPR and VLPW modes.
 *                  - 1: USB voltage regulator in standby during VLPR and VLPW modes.
 */
static inline void SIM_HAL_SetUsbVoltRegulatorInStdbyDuringVlprwMode(SIM_Type* base,
                                                                     sim_usbvstby_stop_t setting)
{
    SIM_BWR_SOPT1_USBVSTBY(base, setting);
}

/*!
 * @brief Gets the USB voltage regulator in a standby mode during the VLPR or the VLPW.
 *
 * This function  gets the USB voltage regulator in a standby mode during the VLPR or the VLPW.
 *
 * @param base     Base address for current SIM instance.
 * @return setting  USB voltage regulator in a standby mode during the VLPR or the VLPW
 */
static inline sim_usbvstby_stop_t SIM_HAL_GetUsbVoltRegulatorInStdbyDuringVlprwMode(SIM_Type* base)
{
    return (sim_usbvstby_stop_t)SIM_BRD_SOPT1_USBVSTBY(base);
}

/*!
 * @brief Sets the USB voltage regulator stop standby write enable setting.
 *
 * This function  controls whether the USB voltage regulator stop  standby write
 * feature is enabled. Writing one to this bit allows the SOPT1[USBSSTBY] bit to be written. This
 * register bit clears after a write to SOPT1[USBSSTBY].
 *
 * @param base     Base address for current SIM instance.
 * @param enable  USB voltage regulator stop standby write enable setting
 *                  - true: SOPT1[USBSSTBY] can be written.
 *                  - false: SOPT1[USBSSTBY] cannot be written.
 */
static inline void SIM_HAL_SetUsbVoltRegulatorInStdbyDuringStopCmd(SIM_Type* base, bool enable)
{
    SIM_BWR_SOPT1CFG_USSWE(base, enable ? 1 : 0);
}

/*!
 * @brief Gets the USB voltage regulator stop standby write enable setting.
 *
 * This function  gets the USB voltage regulator stop standby write enable setting.
 *
 * @param base     Base address for current SIM instance.
 * @return enabled True if the USB voltage regulator stop standby write is enabled.
 */
static inline bool SIM_HAL_GetUsbVoltRegulatorInStdbyDuringStopCmd(SIM_Type* base)
{
    return SIM_BRD_SOPT1CFG_USSWE(base);
}

/*!
 * @brief Sets the USB voltage regulator VLP standby write enable setting.
 *
 * This function  controls whether USB voltage regulator VLP standby write
 * feature is enabled. Writing one to this bit allows the SOPT1[USBVSTBY] bit to be written. This
 * register bit clears after a write to SOPT1[USBVSTBY].
 *
 * @param base     Base address for current SIM instance.
 * @param enable   USB voltage regulator VLP standby write enable setting
 *                  - true: SOPT1[USBSSTBY] can be written.
 *                  - false: SOPT1[USBSSTBY] cannot be written.
 */
static inline void SIM_HAL_SetUsbVoltRegulatorInStdbyDuringVlprwCmd(SIM_Type* base, bool enable)
{
    SIM_BWR_SOPT1CFG_UVSWE(base, enable ? 1 : 0);
}

/*!
 * @brief Gets the USB voltage regulator VLP standby write enable setting.
 *
 * This function  gets the USB voltage regulator VLP standby write enable setting.
 *
 * @param base     Base address for current SIM instance.
 * @return enabled True if the USB voltage regulator VLP standby write is enabled.
 */
static inline bool SIM_HAL_GetUsbVoltRegulatorInStdbyDuringVlprwCmd(SIM_Type* base)
{
    return SIM_BRD_SOPT1CFG_UVSWE(base);
}

/*!
 * @brief Sets the USB voltage regulator enable write enable setting.
 *
 * This function  controls whether the USB voltage regulator write enable
 * feature is enabled. Writing one to this bit allows the SOPT1[USBREGEN] bit to be written.
 * This register bit clears after a write to SOPT1[USBREGEN].
 *
 * @param base     Base address for current SIM instance.
 * @param enable   USB voltage regulator enable write enable setting
 *                  - true: SOPT1[USBSSTBY] can be written.
 *                  - false: SOPT1[USBSSTBY] cannot be written.
 */
static inline void SIM_HAL_SetUsbVoltRegulatorWriteCmd(SIM_Type* base, bool enable)
{
    SIM_BWR_SOPT1CFG_URWE(base, enable ? 1 : 0);
}

/*!
 * @brief Gets the USB voltage regulator enable write enable setting.
 *
 * This function  gets the USB voltage regulator enable write enable setting.
 *
 * @param base     Base address for current SIM instance.
 * @return enabled True if USB voltage regulator enable write is enabled.
 */
static inline bool SIM_HAL_GetUsbVoltRegulatorWriteCmd(SIM_Type* base)
{
    return SIM_BRD_SOPT1CFG_URWE(base);
}
#endif

#if FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD
/*!
 * @brief Sets the CMT/UART pad drive strength setting.
 *
 * This function  controls the output drive strength of the CMT IRO signal or
 * UART0_TXD signal on PTD7 pin by selecting either one or two pads to drive it.
 *
 * @param base     Base address for current SIM instance.
 * @param setting   CMT/UART pad drive strength setting
 *                  - 0: Single-pad drive strength for CMT IRO or UART0_TXD.
 *                  - 1: Dual-pad drive strength for CMT IRO or UART0_TXD.
 */
static inline void SIM_HAL_SetCmtUartPadDriveStrengthMode(SIM_Type* base,
                                                          sim_cmtuartpad_strengh_t setting)
{
    SIM_BWR_SOPT2_CMTUARTPAD(base, setting);
}

/*!
 * @brief Gets the CMT/UART pad drive strength setting.
 *
 * This function  gets the CMT/UART pad drive strength setting.
 *
 * @param base     Base address for current SIM instance.
 * @return setting CMT/UART pad drive strength setting
 */
static inline sim_cmtuartpad_strengh_t SIM_HAL_GetCmtUartPadDriveStrengthMode(SIM_Type* base)
{
    return (sim_cmtuartpad_strengh_t)SIM_BRD_SOPT2_CMTUARTPAD(base);
}
#endif /* FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD */

#if FSL_FEATURE_SIM_OPT_HAS_TIMESRC
/*!
 * @brief Set the ethernet timestamp clock source selection.
 *
 * This function sets the ethernet timestamp clock source selection.
 *
 * @param base Base address for current SIM instance.
 * @param instance IP instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetTimeSrc(SIM_Type * base,
                                        uint32_t instance,
                                        clock_time_src_t setting)
{
    SIM_BWR_SOPT2_TIMESRC(base, setting);
}

/*!
 * @brief Get the ethernet timestamp clock source selection.
 *
 * This function gets the ethernet timestamp clock source selection.
 *
 * @param base Base address for current SIM instance.
 * @param instance IP instance.
 * @return Current selection.
 */
static inline clock_time_src_t CLOCK_HAL_GetTimeSrc(SIM_Type * base,
                                                    uint32_t  instance)
{
    return (clock_time_src_t)SIM_BRD_SOPT2_TIMESRC(base);
}
#endif /* FSL_FEATURE_SIM_OPT_HAS_TIMESRC */

#if FSL_FEATURE_SIM_OPT_HAS_RMIISRC
/*!
 * @brief Set the Ethernet RMII interface clock source selection.
 *
 * This function sets the Ethernet RMII interface clock source selection.
 *
 * @param base Base address for current SIM instance.
 * @param instance IP instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetRmiiSrc(SIM_Type * base,
                                        uint32_t instance,
                                        clock_rmii_src_t setting)
{
    SIM_BWR_SOPT2_RMIISRC(base, setting);
}

/*!
 * @brief Get the Ethernet RMII interface clock source selection.
 *
 * This function gets the Ethernet RMII interface clock source selection.
 *
 * @param base Base address for current SIM instance.
 * @param instance IP instance.
 * @return Current selection.
 */
static inline clock_rmii_src_t CLOCK_HAL_GetRmiiSrc(SIM_Type * base,
                                                    uint32_t instance)
{
    return (clock_rmii_src_t)SIM_BRD_SOPT2_RMIISRC(base);
}
#endif /* FSL_FEATURE_SIM_OPT_HAS_RMIISRC */

#if FSL_FEATURE_SIM_OPT_HAS_FBSL
/*!
 * @brief Sets the FlexBus security level setting.
 *
 * This function  sets the FlexBus security level setting. If the security is enabled,
 * this field affects which CPU operations can access the off-chip via the FlexBus
 * and DDR controller interfaces. This field has no effect if the security is not enabled.
 *
 * @param base     Base address for current SIM instance.
 * @param setting   FlexBus security level setting
 *                  - 00: All off-chip accesses (op code and data) via the FlexBus and
 *                        DDR controller are disallowed.
 *                  - 10: Off-chip op code accesses are disallowed. Data accesses are
 *                        allowed.
 *                  - 11: Off-chip op code accesses and data accesses are allowed.
 */
static inline void SIM_HAL_SetFlexbusSecurityLevelMode(SIM_Type* base,
                                                       sim_flexbus_security_level_t setting)
{
    SIM_BWR_SOPT2_FBSL(base, setting);
}

/*!
 * @brief Gets the FlexBus security level setting.
 *
 * This function  gets the FlexBus security level setting.
 *
 * @param base     Base address for current SIM instance.
 * @return setting FlexBus security level setting
 */
static inline sim_flexbus_security_level_t SIM_HAL_GetFlexbusSecurityLevelMode(SIM_Type* base)
{
    return (sim_flexbus_security_level_t)SIM_BRD_SOPT2_FBSL(base);
}
#endif /* FSL_FEATURE_SIM_OPT_HAS_FBSL */

#if FSL_FEATURE_SIM_OPT_HAS_PCR
/*!
 * @brief Sets the PCR setting.
 *
 * This function  sets the PCR setting. This is the FlexBus hold cycles before
 * FlexBus can release bus to NFC or to IDLE.
 *
 * @param base     Base address for current SIM instance.
 * @param setting   PCR setting
 */
static inline void SIM_HAL_SetFlexbusHoldCycles(SIM_Type* base, uint32_t setting)
{
    SIM_BWR_SOPT6_PCR(base, setting);
}

/*!
 * @brief Gets the PCR setting.
 *
 * This function  gets the PCR setting.
 *
 * @param base     Base address for current SIM instance.
 * @return setting PCR setting
 */
static inline uint32_t SIM_HAL_GetFlexbusHoldCycles(SIM_Type* base)
{
    return SIM_BRD_SOPT6_PCR(base);
}
#endif /* FSL_FEATURE_SIM_OPT_HAS_PCR */

#if FSL_FEATURE_SIM_OPT_HAS_MCC
/*!
 * @brief Sets the MCC setting.
 *
 * This function  sets  the MCC setting. This is the NFC hold cycle in case the
 * FlexBus request during NFC is granted.
 *
 * @param base     Base address for current SIM instance.
 * @param setting   MCC setting
 */
static inline void SIM_HAL_SetNandFlashControllerHoldCycles(SIM_Type* base, uint32_t setting)
{
    SIM_BWR_SOPT6_MCC(base, setting);
}

/*!
 * @brief Gets the MCC setting.
 *
 * This function  gets the MCC setting.
 *
 * @param base     Base address for current SIM instance.
 * @return setting MCC setting
 */
static inline uint32_t SIM_HAL_GetNandFlashControllerHoldCycles(SIM_Type* base)
{
    return SIM_BRD_SOPT6_MCC(base);
}
#endif /* FSL_FEATURE_SIM_OPT_HAS_MCC */

/*!
 * @brief Sets the FlexTimer x external clock pin select setting.
 *
 * This function  selects the source of FTMx external clock pin select.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select FTMx external clock pin select
 *               - 0: FTMx external clock driven by FTM CLKIN0 pin.
 *               - 1: FTMx external clock driven by FTM CLKIN1 pin.
 */
void SIM_HAL_SetFtmExternalClkPinMode(SIM_Type* base,
                                      uint32_t instance,
                                      sim_ftm_clk_sel_t select);

/*!
 * @brief Gets the FlexTimer x external clock pin select setting.
 *
 * This function gets the FlexTimer x external clock pin select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select      FlexTimer x external clock pin select setting
 */
sim_ftm_clk_sel_t SIM_HAL_GetFtmExternalClkPinMode(SIM_Type* base,
                                                   uint32_t instance);

/*!
 * @brief Sets the FlexTimer x channel y input capture source select setting.
 *
 * This function  selects the FlexTimer x channel y input capture source.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param channel      FlexTimer channel y
 * @param select       FlexTimer x channel y input capture source
 */
void SIM_HAL_SetFtmChSrcMode(SIM_Type* base,
                             uint32_t instance,
                             uint8_t channel,
                             sim_ftm_ch_src_t select);

/*!
 * @brief Gets the FlexTimer x channel y input capture source select setting.
 *
 * This function gets the FlexTimer x channel y input capture
 * source select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param channel      FlexTimer channel y
 * @return select      FlexTimer x channel y input capture source select setting
 */
sim_ftm_ch_src_t SIM_HAL_GetFtmChSrcMode(SIM_Type* base,
                                         uint32_t instance,
                                         uint8_t channel);

/*!
 * @brief Sets the FlexTimer x channel y output source select setting.
 *
 * This function  selects the FlexTimer x channel y output source.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param channel      FlexTimer channel y
 * @param select       FlexTimer x channel y output source
 */
void SIM_HAL_SetFtmChOutSrcMode(SIM_Type* base,
                                uint32_t instance,
                                uint8_t channel,
                                sim_ftm_ch_out_src_t select);

/*!
 * @brief Gets the FlexTimer x channel y output source select setting.
 *
 * This function gets the FlexTimer x channel y output
 * source select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param channel      FlexTimer channel y
 * @return select      FlexTimer x channel y output source select setting
 */
sim_ftm_ch_out_src_t SIM_HAL_GetFtmChOutSrcMode(SIM_Type* base,
                                                uint32_t instance,
                                                uint8_t channel);

/*!
 * @brief sets FlexTimer x carrier frequency selection setting
 *
 * This function  sets the FTMx output channel carrier frequency selection setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param ftmcarrierfreqsrc         FTMx output channel carrier frequency selection
 */
void SIM_HAL_SetFtmCarrierFreqCmd(SIM_Type* base, uint32_t instance, bool ftmcarrierfreqsrc);

/*!
 * @brief Gets the  FlexTimer x carrier frequency selection setting.
 *
 * This function  gets the  FTMx output channel carrier frequency selection setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return value       indicates FTMx output channel carrier frequency selection
 */
bool SIM_HAL_GetFtmCarrierFreqCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief sets FlexTimer x hardware trigger 0 software synchronization
 *
 * This function  enables/disables the alternative hardware triggers for FTMx.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param sync         assert TRIG0 input to FTM0
 */
void SIM_HAL_SetFtmSyncCmd(SIM_Type* base, uint32_t instance, bool sync);

/*!
 * @brief Sets the HSADCx alternate trigger enable setting.
 *
 * This function selects the alternative conversion triggers for HSADCx.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param convId       Selection of ID for HSADC converter.
 * @param select alternative conversion triggers for HSADCx
 */
void SIM_HAL_SetHsadcAlternativeTriggerMode(SIM_Type* base, uint32_t instance, sim_hsadc_conv_id_t convId, sim_hsadc_alttrg_sel_t select);

/*!
 * @brief Gets the  HSADCx alternate trigger enable setting.
 *
 * This function  gets the  HSADCx alternate trigger selects setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param convId       Selection of ID for HSADC converter.
 * @return selected HSADCx alternate trigger select setting
 */
sim_hsadc_alttrg_sel_t SIM_HAL_GetHsadcAlternativeTriggerMode(SIM_Type* base, uint32_t instance, sim_hsadc_conv_id_t convId);

/*!
 * @brief Sets the ADCx alternate trigger select setting.
 *
 * This function selects the alternative conversion triggers for ADCx.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select alternative conversion triggers for ADCx
 */
void SIM_HAL_SetAdcAlternativeTriggerMode(SIM_Type * base,
                                         uint32_t instance,
                                         sim_adc_alttrg_sel_t select);

/*!
 * @brief Gets the ADCx alternate trigger select setting.
 *
 * This function gets the ADCx alternate trigger select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return selected ADCx alternate trigger select setting
 */
sim_adc_alttrg_sel_t SIM_HAL_GetAdcAlternativeTriggerMode(SIM_Type * base, uint32_t instance);

/*!
 * @brief Sets the ADCx pre-trigger select setting.
 *
 * This function selects the ADCx pre-trigger source when the alternative
 * triggers are enabled through ADCxALTTRGEN.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select pre-trigger select setting for ADCx
 */
void SIM_HAL_SetAdcPreTriggerMode(SIM_Type * base,
                                  uint32_t instance,
                                  sim_adc_pretrg_sel_t select);

/*!
 * @brief Gets the ADCx pre-trigger select setting.
 *
 * This function  gets the ADCx pre-trigger select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select ADCx pre-trigger select setting
 */
sim_adc_pretrg_sel_t SIM_HAL_GetAdcPreTriggerMode(SIM_Type * base,
                                                  uint32_t instance);

/*!
 * @brief Sets the HSADCx trigger select setting.
 *
 * This function  selects the HSADCx trigger source when alternative triggers
 * are enabled through HSADCxALTTRGEN.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param convId       Selection of ID for HSADC converter.
 * @param select       trigger select setting for HSADCx
*/
void SIM_HAL_SetHsadcTriggerMode(SIM_Type* base, uint32_t instance, sim_hsadc_conv_id_t convId, sim_hsadc_trg_sel_t select);

/*!
 * @brief Gets the HSADCx trigger select setting.
 *
 * This function  gets the HSADCx trigger select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param convId       Selection of ID for HSADC converter.
 * @return select      HSADCx trigger select setting
 */
sim_hsadc_trg_sel_t SIM_HAL_GetHsadcTriggerMode(SIM_Type* base, uint32_t instance, sim_hsadc_conv_id_t convId);

/*!
 * @brief Sets the ADCx trigger select setting.
 *
 * This function  selects the ADCx trigger source when alternative triggers
 * are enabled through ADCxALTTRGEN.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select       trigger select setting for ADCx
*/
void SIM_HAL_SetAdcTriggerMode(SIM_Type * base,
                               uint32_t instance,
                               sim_adc_trg_sel_t select);

/*!
 * @brief Gets the ADCx trigger select setting.
 *
 * This function  gets the ADCx trigger select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return ADCx trigger select setting
 */
sim_adc_trg_sel_t SIM_HAL_GetAdcTriggerMode(SIM_Type * base,
                                             uint32_t instance);

/*!
 * @brief Set HSADCx trigger setting.
 *
 * This function sets HSADC alternate trigger and trigger mode.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param convId     device instance.
 * @param altTrigSel   Alternative trigger mode.
 * @param trigSel      Trigger mode.
 *END**************************************************************************/
void SIM_HAL_SetHsadcTriggerModeOneStep(SIM_Type* base,
                                      uint32_t instance,
									  sim_hsadc_conv_id_t convId,
									  sim_hsadc_alttrg_sel_t altTrigSel,
									  sim_hsadc_trg_sel_t trigSel);

/*!
 * @brief Sets the ADCx trigger select setting in one function.
 *
 * This function sets ADC alternate trigger mode, pre-trigger mode and trigger mode.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param altTrigSel   Alternative trigger mode.
 * @param preTrigSel   Pre-trigger mode.
 * @param trigSel      Trigger mode.
*/
void SIM_HAL_SetAdcTriggerModeOneStep(SIM_Type * base,
                                      uint32_t instance,
                                      sim_adc_alttrg_sel_t altTrigSel,
                                      sim_adc_pretrg_sel_t preTrigSel,
                                      sim_adc_trg_sel_t trigSel);

/*!
 * @brief Sets the UARTx receive data source select setting.
 *
 * This function  selects the source for the UARTx receive data.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select the source for the UARTx receive data
 *               - 00: UARTx_RX pin.
 *               - 01: CMP0.
 *               - 10: CMP1.
 *               - 11: Reserved.
 */
void SIM_HAL_SetUartRxSrcMode(SIM_Type* base, uint32_t instance, sim_uart_rxsrc_t select);

/*!
 * @brief Gets the UARTx receive data source select setting.
 *
 * This function  gets the UARTx receive data source select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select UARTx receive data source select setting
 */
sim_uart_rxsrc_t SIM_HAL_GetUartRxSrcMode(SIM_Type* base, uint32_t instance);

/*!
 * @brief Sets the UARTx transmit data source select setting.
 *
 * This function  selects the source for the UARTx transmit data.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select the source for the UARTx transmit data
 *               - 00: UARTx_TX pin.
 *               - 01: UARTx_TX pin modulated with FTM1 channel 0 output.
 *               - 10: UARTx_TX pin modulated with FTM2 channel 0 output.
 *               - 11: Reserved.
 */
void SIM_HAL_SetUartTxSrcMode(SIM_Type* base, uint32_t instance, sim_uart_txsrc_t select);

/*!
 * @brief Gets the UARTx transmit data source select setting.
 *
 * This function  gets the UARTx transmit data source select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select UARTx transmit data source select setting
 */
sim_uart_txsrc_t SIM_HAL_GetUartTxSrcMode(SIM_Type* base, uint32_t instance);

#if FSL_FEATURE_SIM_OPT_HAS_ODE
/*!
 * @brief Sets the UARTx Open Drain Enable setting.
 *
 * This function  enables/disables the UARTx Open Drain.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param enable Enable/disable UARTx Open Drain
 *               - True: Enable UARTx Open Drain
 *               - False: Disable UARTx Open Drain
 */
void SIM_HAL_SetUartOpenDrainCmd(SIM_Type* base, uint8_t instance, bool enable);

/*!
 * @brief Gets the UARTx Open Drain Enable setting.
 *
 * This function  gets the UARTx Open Drain Enable setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return enabled True if UARTx Open Drain is enabled.
 */
bool SIM_HAL_GetUartOpenDrainCmd(SIM_Type* base, uint8_t instance);
#endif

#if FSL_FEATURE_SIM_OPT_HAS_FTM
/*!
 * @brief Sets the FlexTimer x hardware trigger y source select setting.
 *
 * This function  selects  the source of FTMx hardware trigger y.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param trigger      hardware trigger y
 * @param select FlexTimer x hardware trigger y
 */
void SIM_HAL_SetFtmTriggerSrcMode(SIM_Type* base,
                                  uint32_t instance,
                                  uint8_t trigger,
                                  sim_ftm_trg_src_t select);

/*!
 * @brief Gets the FlexTimer x hardware trigger y source select setting.
 *
 * This function  gets the FlexTimer x hardware trigger y source select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param trigger      hardware trigger y
 * @return select FlexTimer x hardware trigger y source select setting
 */
sim_ftm_trg_src_t SIM_HAL_GetFtmTriggerSrcMode(SIM_Type* base, uint32_t instance, uint8_t trigger);

/*!
 * @brief Sets the FlexTimer x fault y select setting.
 *
 * This function  sets the FlexTimer x fault y select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param fault        fault y
 * @param select FlexTimer x fault y select setting
 *               - 0: FlexTimer x fault y select 0.
 *               - 1: FlexTimer x fault y select 1.
 */
void SIM_HAL_SetFtmFaultSelMode(SIM_Type* base, uint8_t instance, uint8_t fault, sim_ftm_flt_sel_t select);

/*!
 * @brief Gets the FlexTimer x fault y select setting.
 *
 * This function  gets the FlexTimer x fault y select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param fault        fault y
 * @return select FlexTimer x fault y select setting
 */
sim_ftm_flt_sel_t SIM_HAL_GetFtmFaultSelMode(SIM_Type* base, uint8_t instance, uint8_t fault);
#endif

#if FSL_FEATURE_SIM_OPT_HAS_TPM
/*!
 * @brief Sets the Timer/PWM x external clock pin select setting.
 *
 * This function  selects the source of the Timer/PWM x external clock pin select.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select Timer/PWM x external clock pin select
 *               - 0: Timer/PWM x external clock driven by the TPM_CLKIN0 pin.
 *               - 1: Timer/PWM x external clock driven by the TPM_CLKIN1 pin.
 */
void SIM_HAL_SetTpmExternalClkPinSelMode(SIM_Type* base, uint8_t instance, sim_tpm_clk_sel_t select);

/*!
 * @brief Gets the Timer/PWM x external clock pin select setting.
 *
 * This function  gets the Timer/PWM x external clock pin select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select Timer/PWM x external clock pin select setting
 */
sim_tpm_clk_sel_t SIM_HAL_GetTpmExternalClkPinSelMode(SIM_Type* base, uint8_t instance);

/*!
 * @brief Sets the Timer/PWM x channel y input capture source select setting.
 *
 * This function  selects the Timer/PWM x channel y input capture source.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param channel      TPM channel y
 * @param select Timer/PWM x channel y input capture source
 *               - 0: TPMx_CH0 signal
 *               - 1: CMP0 output
 */
void SIM_HAL_SetTpmChSrcMode(SIM_Type* base, uint8_t instance, uint8_t channel, sim_tpm_ch_src_t select);

/*!
 * @brief Gets the Timer/PWM x channel y input capture source select setting.
 *
 * This function  gets the Timer/PWM x channel y input capture source select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param channel      Tpm channel y
 * @return select Timer/PWM x channel y input capture source select setting
 */
sim_tpm_ch_src_t SIM_HAL_GetTpmChSrcMode(SIM_Type* base, uint8_t instance, uint8_t channel);
#endif

#if FSL_FEATURE_SIM_SDID_HAS_FAMILYID
/*!
 * @brief Gets the Kinetis Family ID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Family ID in the System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis Family ID
 */
static inline uint32_t SIM_HAL_GetFamilyId(SIM_Type* base)
{
    return SIM_BRD_SDID_FAMILYID(base);
}
#endif

#if FSL_FEATURE_SIM_SDID_HAS_SUBFAMID
/*!
 * @brief Gets the Kinetis Sub-Family ID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Sub-Family ID in System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis Sub-Family ID
 */
static inline uint32_t SIM_HAL_GetSubFamilyId(SIM_Type* base)
{
    return SIM_BRD_SDID_SUBFAMID(base);
}
#endif

#if FSL_FEATURE_SIM_SDID_HAS_SERIESID
/*!
 * @brief Gets the Kinetis SeriesID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Series ID in System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis Series ID
 */
static inline uint32_t SIM_HAL_GetSeriesId(SIM_Type* base)
{
    return SIM_BRD_SDID_SERIESID(base);
}
#endif

#if FSL_FEATURE_SIM_SDID_HAS_FAMID
/*!
 * @brief Gets the Kinetis Fam ID in System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Fam ID in System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis Fam ID
 */
static inline uint32_t SIM_HAL_GetFamId(SIM_Type* base)
{
    return SIM_BRD_SDID_FAMID(base);
}
#endif

/*!
 * @brief Gets the Kinetis Pincount ID in System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Pincount ID in System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis Pincount ID
 */
static inline uint32_t SIM_HAL_GetPinCntId(SIM_Type* base)
{
    return SIM_BRD_SDID_PINID(base);
}

/*!
 * @brief Gets the Kinetis Revision ID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Revision ID in System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis Revision ID
 */
static inline uint32_t SIM_HAL_GetRevId(SIM_Type* base)
{
    return SIM_BRD_SDID_REVID(base);
}

#if FSL_FEATURE_SIM_SDID_HAS_DIEID
/*!
 * @brief Gets the Kinetis Die ID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Die ID in System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis Die ID
 */
static inline uint32_t SIM_HAL_GetDieId(SIM_Type* base)
{
    return SIM_BRD_SDID_DIEID(base);
}
#endif

#if FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE
/*!
 * @brief Gets the Kinetis SRAM size in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis SRAM Size in System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis SRAM Size
 */
static inline uint32_t SIM_HAL_GetSramSize(SIM_Type* base)
{
    return SIM_BRD_SDID_SRAMSIZE(base);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE
/*!
 * @brief Gets the FlexNVM size in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  gets the FlexNVM size in the Flash Configuration Register 1.
 *
 * @param base     Base address for current SIM instance.
 * @return size FlexNVM Size
 */
static inline uint32_t SIM_HAL_GetFlexnvmSize(SIM_Type* base)
{
    return SIM_BRD_FCFG1_NVMSIZE(base);
}
#endif

/*!
 * @brief Gets the program flash size in  the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  gets the program flash size in the Flash Configuration Register 1.
 *
 * @param base     Base address for current SIM instance.
 * @return size Program flash Size
 */
static inline uint32_t SIM_HAL_GetProgramFlashSize(SIM_Type* base)
{
    return SIM_BRD_FCFG1_PFSIZE(base);
}

#if FSL_FEATURE_SIM_FCFG_HAS_EESIZE
/*!
 * @brief Gets the EEProm size in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  gets the EEProm size in the Flash Configuration Register 1.
 *
 * @param base     Base address for current SIM instance.
 * @return size EEProm Size
 */
static inline uint32_t SIM_HAL_GetEepromSize(SIM_Type* base)
{
    return SIM_BRD_FCFG1_EESIZE(base);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_DEPART
/*!
 * @brief Gets the FlexNVM partition in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  gets the FlexNVM partition in the Flash Configuration Register 1
 *
 * @param base     Base address for current SIM instance.
 * @return setting FlexNVM partition setting
 */
static inline uint32_t SIM_HAL_GetFlexnvmPartition(SIM_Type* base)
{
    return SIM_BRD_FCFG1_DEPART(base);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE
/*!
 * @brief Sets the Flash Doze in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  sets the Flash Doze in the Flash Configuration Register 1.
 *
 * @param base     Base address for current SIM instance.
 * @param setting Flash Doze setting
 */
static inline void SIM_HAL_SetFlashDoze(SIM_Type* base, uint32_t setting)
{
    SIM_BWR_FCFG1_FLASHDOZE(base, setting);
}

/*!
 * @brief Gets the Flash Doze in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  gets the Flash Doze in the Flash Configuration Register 1.
 *
 * @param base     Base address for current SIM instance.
 * @return setting Flash Doze setting
 */
static inline uint32_t SIM_HAL_GetFlashDoze(SIM_Type* base)
{
    return SIM_BRD_FCFG1_FLASHDOZE(base);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS
/*!
 * @brief Sets the Flash disable setting in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  sets the Flash disable setting in the Flash Configuration Register 1.
 *
 * @param base     Base address for current SIM instance.
 * @param disable Flash disable setting
 */
static inline void SIM_HAL_SetFlashDisableCmd(SIM_Type* base, bool disable)
{
    SIM_BWR_FCFG1_FLASHDIS(base, disable);
}

/*!
 * @brief Gets the Flash disable setting in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  gets the Flash disable setting in the Flash Configuration Register 1.
 *
 * @param base     Base address for current SIM instance.
 * @return setting Flash disable setting
 */
static inline bool SIM_HAL_GetFlashDisableCmd(SIM_Type* base)
{
    return (bool)SIM_BRD_FCFG1_FLASHDIS(base);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0
/*!
 * @brief Gets the Flash maximum address block 0 in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  gets the Flash maximum block 0 in Flash Configuration Register 2.
 *
 * @param base     Base address for current SIM instance.
 * @return address Flash maximum block 0 address
 */
static inline uint32_t SIM_HAL_GetFlashMaxAddrBlock0(SIM_Type* base)
{
    return SIM_BRD_FCFG2_MAXADDR0(base);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1
/*!
 * @brief Gets the Flash maximum address block 1 in Flash Configuration Register 2.
 *
 * This function  gets the Flash maximum block 1 in Flash Configuration Register 1.
 *
 * @param base     Base address for current SIM instance.
 * @return address Flash maximum block 0 address
 */
static inline uint32_t SIM_HAL_GetFlashMaxAddrBlock1(SIM_Type* base)
{
    return SIM_BRD_FCFG2_MAXADDR1(base);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01
/*!
 * @brief Gets the Flash maximum address block 0 in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  gets the Flash maximum block 0 in Flash Configuration Register 2.
 *
 * @param base     Base address for current SIM instance.
 * @return address Flash maximum block 0 address
 */
static inline uint32_t SIM_HAL_GetFlashMaxAddrBlock01(SIM_Type* base)
{
    return SIM_BRD_FCFG2_MAXADDR01(base);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23
/*!
 * @brief Gets the Flash maximum address block 1 in the Flash Configuration Register 2.
 *
 * This function  gets the Flash maximum block 1 in Flash Configuration Register 1.
 *
 * @param base Base address for current SIM instance.
 * @return address Flash maximum block 0 address
 */
static inline uint32_t SIM_HAL_GetFlashMaxAddrBlock23(SIM_Type* base)
{
    return SIM_BRD_FCFG2_MAXADDR23(base);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_PFLSH
/*!
 * @brief Gets the program flash in the Flash Configuration Register 2.
 *
 * This function  gets the program flash maximum block 0 in Flash Configuration Register 1.
 *
 * @param base Base address for current SIM instance.
 * @return status program flash status
 */
static inline uint32_t SIM_HAL_GetProgramFlashCmd(SIM_Type* base)
{
    return SIM_BRD_FCFG2_PFLSH(base);
}
#endif

/*!
 * @brief Sets the Debug Trace Divider Control.
 *
 * This function  sets the Debug Trace Divider enable setting.
 *
 * @param base     Base address for current SIM instance.
 * @param enable       Debug trace divider control enable setting
 */
static inline void SIM_HAL_SetDebugTraceDivEnCmd(SIM_Type* base, bool enable)
{
    SIM_BWR_CLKDIV4_TRACEDIVEN(base, enable);
}

/*!
 * @brief Gets the Debug Trace Divider Control.
 *
 * This function  gets the Debug Trace Divider enable setting.
 *
 * @param base     Base address for current SIM instance.
 * @return enable      Debug trace divider control enable setting
 */
static inline bool SIM_HAL_GetDebugTraceDivEnCmd(SIM_Type* base)
{
    return (bool)SIM_BRD_CLKDIV4_TRACEDIVEN(base);
}

/*!
 * @brief Sets the Debug Trace Divider Divisor.
 *
 * This function  sets the Debug Trace Divider Divisor value.
 *
 * @param base     Base address for current SIM instance.
 * @param divisor_value       divide value for the fractional clock divider
 */
static inline void SIM_HAL_SetDebugTraceDivDivisor(SIM_Type* base, uint8_t divisor_value)
{
    SIM_BWR_CLKDIV4_TRACEDIV(base, divisor_value);
}

/*!
 * @brief Gets the Debug Trace Divider Divisor value.
 *
 * This function  gets the Debug Trace Divider enable setting.
 *
 * @param base     Base address for current SIM instance.
 * @return divisor_value      divide value for the fractional clock divider
 */
static inline uint8_t SIM_HAL_GetDebugTraceDivDivisor(SIM_Type* base)
{
    return (bool)SIM_BRD_CLKDIV4_TRACEDIV(base);
}

/*!
 * @brief Sets the Debug Trace Divider Divisor.
 *
 * This function  sets the Debug Trace Divider Divisor value.
 *
 * @param base     Base address for current SIM instance.
 * @param divisor_frac_value       divide value for the fractional clock divider
 */
static inline void SIM_HAL_SetDebugTraceFracDivDivisor(SIM_Type* base, bool divisor_frac_value)
{
    SIM_BWR_CLKDIV4_TRACEFRAC(base, divisor_frac_value);
}

/*!
 * @brief Gets the Debug Trace Divider Divisor value.
 *
 * This function  gets the Debug Trace Divider enable setting.
 *
 * @param base     Base address for current SIM instance.
 * @return divisor_frac_value      divide value for the fractional clock divider
 */
static inline uint8_t SIM_HAL_GetDebugTraceFracDivDivisor(SIM_Type* base)
{
    return (bool)SIM_BRD_CLKDIV4_TRACEFRAC(base);
}

/*!
 * @brief Enable the clock for specific module.
 *
 * This function enables the clock for specific module.
 *
 * @param base Base address for current SIM instance.
 * @param name Name of the module to enable.
 */
static inline void SIM_HAL_EnableClock(SIM_Type* base, sim_clock_gate_name_t name)
{
    SIM_BWR_SCGC_BIT(base, name, 1U);
}

/*!
 * @brief Disable the clock for specific module.
 *
 * This function disables the clock for specific module.
 *
 * @param base Base address for current SIM instance.
 * @param name Name of the module to disable.
 */
static inline void SIM_HAL_DisableClock(SIM_Type* base, sim_clock_gate_name_t name)
{
    SIM_BWR_SCGC_BIT(base, name, 0U);
}

/*!
 * @brief Get the the clock gate state for specific module.
 *
 * This function will get the clock gate state for specific module.
 *
 * @param base Base address for current SIM instance.
 * @param name Name of the module to get.
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool SIM_HAL_GetGateCmd(SIM_Type* base, sim_clock_gate_name_t name)
{
    return (bool)SIM_BRD_SCGC_BIT(base, name);
}

/*! @name IP related clock feature APIs*/
/*@{*/
/*!
 * @brief Set OUTDIV1.
 *
 * This function sets divide value OUTDIV1.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetOutDiv1(SIM_Type* base, uint8_t setting)
{
    SIM_BWR_CLKDIV1_OUTDIV1(base, setting);
}

/*!
 * @brief Get OUTDIV1.
 *
 * This function gets divide value OUTDIV1.
 *
 * @param base Base address for current SIM instance.
 * @return Current divide value.
 */
static inline uint8_t CLOCK_HAL_GetOutDiv1(SIM_Type* base)
{
    return SIM_BRD_CLKDIV1_OUTDIV1(base);
}

/*!
 * @brief Set OUTDIV2.
 *
 * This function sets divide value OUTDIV2.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetOutDiv2(SIM_Type* base, uint8_t setting)
{
    SIM_BWR_CLKDIV1_OUTDIV2(base, setting);
}

/*!
 * @brief Get OUTDIV2.
 *
 * This function gets divide value OUTDIV2.
 *
 * @param base Base address for current SIM instance.
 * @return Current divide value.
 */
static inline uint8_t CLOCK_HAL_GetOutDiv2(SIM_Type* base)
{
    return SIM_BRD_CLKDIV1_OUTDIV2(base);
}

/*!
 * @brief Set OUTDIV3.
 *
 * This function sets divide value OUTDIV3.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetOutDiv3(SIM_Type* base, uint8_t setting)
{
    SIM_BWR_CLKDIV1_OUTDIV3(base, setting);
}

/*!
 * @brief Get OUTDIV3.
 *
 * This function gets divide value OUTDIV3.
 *
 * @param base Base address for current SIM instance.
 * @return Current divide value.
 */
static inline uint8_t CLOCK_HAL_GetOutDiv3(SIM_Type* base)
{
    return SIM_BRD_CLKDIV1_OUTDIV3(base);
}

/*!
 * @brief Set OUTDIV4.
 *
 * This function sets divide value OUTDIV4.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetOutDiv4(SIM_Type* base, uint8_t setting)
{
    SIM_BWR_CLKDIV1_OUTDIV4(base, setting);
}

/*!
 * @brief Get OUTDIV4.
 *
 * This function gets divide value OUTDIV4.
 *
 * @param base Base address for current SIM instance.
 * @return Current divide value.
 */
static inline uint8_t CLOCK_HAL_GetOutDiv4(SIM_Type* base)
{
    return SIM_BRD_CLKDIV1_OUTDIV4(base);
}

/*!
 * @brief Enable the clock for DMA module.
 *
 * This function enables the clock for DMA module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableDmaClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for DMA module.
 *
 * This function disables the clock for DMA module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableDmaClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for DMA module.
 *
 * This function will get the clock gate state for DMA module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetDmaGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for DMAMUX module.
 *
 * This function enables the clock for DMAMUX module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableDmamuxClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for DMAMUX module.
 *
 * This function disables the clock for DMAMUX module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableDmamuxClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for DMAMUX module.
 *
 * This function will get the clock gate state for DMAMUX module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetDmamuxGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for PORT module.
 *
 * This function enables the clock for PORT module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnablePortClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for PORT module.
 *
 * This function disables the clock for PORT module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisablePortClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for PORT module.
 *
 * This function will get the clock gate state for PORT module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetPortGateCmd(SIM_Type* base, uint32_t instance);


/*!
 * @brief Enable the clock for EWM module.
 *
 * This function enables the clock for EWM module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableEwmClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for EWM module.
 *
 * This function disables the clock for EWM module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableEwmClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for EWM module.
 *
 * This function will get the clock gate state for EWM module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetEwmGateCmd(SIM_Type* base, uint32_t instance);


/*!
 * @brief Enable the clock for FTF module.
 *
 * This function enables the clock for FTF module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableFtfClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for FTF module.
 *
 * This function disables the clock for FTF module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableFtfClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for FTF module.
 *
 * This function will get the clock gate state for FTF module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetFtfGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for CRC module.
 *
 * This function enables the clock for CRC module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableCrcClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for CRC module.
 *
 * This function disables the clock for CRC module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableCrcClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for CRC module.
 *
 * This function will get the clock gate state for CRC module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetCrcGateCmd(SIM_Type* base, uint32_t instance);


/*!
 * @brief Enable the clock for ADC module.
 *
 * This function enables the clock for ADC module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableAdcClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for ADC module.
 *
 * This function disables the clock for ADC module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableAdcClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for ADC module.
 *
 * This function will get the clock gate state for ADC module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetAdcGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for CMP module.
 *
 * This function enables the clock for CMP module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableCmpClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for CMP module.
 *
 * This function disables the clock for CMP module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableCmpClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for CMP module.
 *
 * This function will get the clock gate state for CMP module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetCmpGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for DAC module.
 *
 * This function enables the clock for DAC module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableDacClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for DAC module.
 *
 * This function disables the clock for DAC module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableDacClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for DAC module.
 *
 * This function will get the clock gate state for DAC module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetDacGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for PDB module.
 *
 * This function enables the clock for PDB module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnablePdbClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for PDB module.
 *
 * This function disables the clock for PDB module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisablePdbClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for PDB module.
 *
 * This function will get the clock gate state for PDB module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetPdbGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for FTM module.
 *
 * This function enables the clock for FTM module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableFtmClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for FTM module.
 *
 * This function disables the clock for FTM module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableFtmClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for FTM module.
 *
 * This function will get the clock gate state for FTM module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetFtmGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Set Nanoedge Regulator 1.2 V Supply Standby Control
 *
 * This function controls the standby mode of the 1.2 V supply from the nanoedge voltage regulator.
 *
 * @param base Base address for current SIM instance.
 * @param select:
 * 00 Nanoedge regulator 1.2 V supply placed in normal mode
 * 01 Nanoedge regulator 1.2 V supply placed in standby mode.
 * 10 Nanoedge regulator 1.2 V supply placed in normal mode and SR12STDBY is write protected until
 * chip reset.
 * 11 Nanoedge regulator 1.2 V supply placed in standby mode and SR12STDBY is write protected until
 * chip reset.
 *
 *END**************************************************************************/
void SIM_HAL_SetNanoedgeRegulator12SupStdbyControl(SIM_Type* base, uint8_t select);

/*!
 *
 * @brief Get Nanoedge Regulator 1.2 V Supply Standby Control
 *
 * This function will get the standby mode of the 1.2 V supply from the nanoedge voltage regulator
 * @param base Base address for current SIM instance.
 * @return select:
 * 00 Nanoedge regulator 1.2 V supply placed in normal mode
 * 01 Nanoedge regulator 1.2 V supply placed in standby mode.
 * 10 Nanoedge regulator 1.2 V supply placed in normal mode and SR12STDBY is write protected until
 * chip reset.
 * 11 Nanoedge regulator 1.2 V supply placed in standby mode and SR12STDBY is write protected until
 * chip reset.
 *
 *END**************************************************************************/
uint8_t SIM_HAL_GetNanoedgeRegulator12SupStdbyControl(SIM_Type* base);

/*!
 * @brief Set Nanoedge Regulator 2.7 V Supply Standby Control
 *
 * This function controls the standby mode of the 2.7 V supply from the nanoedge voltage regulator.
 * 
 * @param base Base address for current SIM instance.
 * @param select:
 * 00 Nanoedge regulator 2.7 V supply placed in normal mode
 * 01 Nanoedge regulator 2.7 V supply placed in standby mode.
 * 10 Nanoedge regulator 2.7 V supply placed in normal mode and SR12STDBY is write protected until
 * chip reset.
 * 11 Nanoedge regulator 2.7 V supply placed in standby mode and SR12STDBY is write protected until
 * chip reset.
 *
 *
 *END**************************************************************************/
void SIM_HAL_SetNanoedgeRegulator27SupStdbyControl(SIM_Type* base, uint8_t select);

/*!
 * @brief Get Nanoedge Regulator 2.7 V Supply Standby Control
 *
 * This function will get the standby mode of the 2.7 V supply from the nanoedge voltage regulator.
 * 
 * @param base Base address for current SIM instance.
 * @return select:
 * 00 Nanoedge regulator 2.7 V supply placed in normal mode
 * 01 Nanoedge regulator 2.7 V supply placed in standby mode.
 * 10 Nanoedge regulator 2.7 V supply placed in normal mode and SR12STDBY is write protected until
 * chip reset.
 * 11 Nanoedge regulator 2.7 V supply placed in standby mode and SR12STDBY is write protected until
 * chip reset.
 *
 *
 *END**************************************************************************/
uint8_t SIM_HAL_GetNanoedgeRegulator27SupStdbyControl(SIM_Type* base);

/*!
 *
 * @brief Set Nanoedge Regulator 2.7V and 1.2V Supply Powerdown Control
 *
 * This function controls the powerdown mode of the 2.7V and 1.2V supply from the nanoedge voltage regulator
 * 
 * @param base Base address for current SIM instance.
 * @param select:
 * 00 Nanoedge regulator placed in normal mode.
 * 01 Nanoedge regulator placed in powerdown mode.
 * 10 Nanoedge regulator placed in normal mode and SRPDN is write protected until chip reset.
 * 11 Nanoedge regulator placed in powerdown mode and SRPDN is write protected until chip reset.
 *
 *END**************************************************************************/
void SIM_HAL_SetNanoedgeReg27n12SupPwrdwnControl(SIM_Type* base, uint8_t select);

/*!
 *
 * @brief Get Nanoedge Regulator 2.7V and 1.2V Supply Powerdown Control
 *
 * This function gets the the powerdown mode of the 2.7V and 1.2V supply from the nanoedge voltage regulator
 * 
 * @param base Base address for current SIM instance.
 * @return select:
 * 00 Nanoedge regulator placed in normal mode.
 * 01 Nanoedge regulator placed in powerdown mode.
 * 10 Nanoedge regulator placed in normal mode and SRPDN is write protected until chip reset.
 * 11 Nanoedge regulator placed in powerdown mode and SRPDN is write protected until chip reset.
 *
 *END**************************************************************************/
uint8_t SIM_HAL_GetNanoedgeReg27n12SupPwrdwnControl(SIM_Type* base);

/*!
 *
 * @brief WDOG Clock Select
 *
 * This function selects the clock source of the WDOG2008 watchdog.
 * 
 * @param base Base address for current SIM instance.
 * @param select:
 * 0 Internal 1 kHz clock is source to WDOG2008
 * 1 MCGIRCLK is source to WDOG2008
 *
 *END**************************************************************************/
void SIM_HAL_SetWdogClkSrc(SIM_Type* base, bool select);

/*!
 *
 * @brief Get WDOG Clock Src
 *
 * This function gets the clock source of the WDOG2008 watchdog.
 * 
 * @param base Base address for current SIM instance.
 * @return select:
 * 0 Internal 1 kHz clock is source to WDOG2008
 * 1 MCGIRCLK is source to WDOG2008
 *
 *END**************************************************************************/
bool SIM_HAL_GetWdogClkSrc(SIM_Type* base);

/*!
 *
 * @brief Synchronize XBARA's Input PIT Trigger X with fast clock 
 * 
 * This function enables the synchronizer between PIT trigger X and XBARA's input.
 *
 * @param base Base address for current SIM instance.
 * @param instance Pit trigger number
 *END**************************************************************************/
void SIM_HAL_EnableSyncXbarAPittrigX(SIM_Type* base, uint32_t instance);

/*!
 *
 * @brief Synchronize XBARA's Input PIT Trigger X with fast clock 
 * 
 * This function disables the synchronizer between PIT trigger X and XBARA's input.
 *
 * @param base Base address for current SIM instance.
 * @param instance Pit trigger number
 *END**************************************************************************/
void SIM_HAL_DisableSyncXbarAPittrigX(SIM_Type* base, uint32_t instance);

/*!
 *
 * @brief get Synchronization of XBARA's Input PIT Trigger X with fast clock 
 * 
 * This function returns the status of the synchronizer between PIT trigger X and XBARA's input.
 *
 * @param base Base address for current SIM instance.
 * @param instance Pit trigger number
 * @return 0 - Not synchronizeed, 1- Synchronized
 *END**************************************************************************/
bool SIM_HAL_GetSyncXbarAPittrigXcmd(SIM_Type* base, uint32_t instance);

/*!
 *
 * @brief Synchronize XBARB's Input PIT Trigger X with fast clock 
 * 
 * This function enables the synchronizer between PIT trigger X and XBARB's input.
 *
 * @param base Base address for current SIM instance.
 * @param instance Pit trigger number
 *END**************************************************************************/
void SIM_HAL_EnableSyncXbarBPittrigX(SIM_Type* base, uint32_t instance);

/*!
 *
 * @brief Synchronize XBARB's Input PIT Trigger X with fast clock 
 * 
 * This function disables the synchronizer between PIT trigger X and XBARB's input.
 *
 * @param base Base address for current SIM instance.
 * @param instance Pit trigger number
 *END**************************************************************************/
void SIM_HAL_DisableSyncXbarBPittrigX(SIM_Type* base, uint32_t instance);

/*!
 *
 * @brief get Synchronization of XBARB's Input PIT Trigger X with fast clock 
 * 
 * This function returns the status of the synchronizer between PIT trigger X and XBARB's input.
 *
 * @param base Base address for current SIM instance.
 * @param instance Pit trigger number
 * @return 0 - Not synchronizeed, 1- Synchronized
 *END**************************************************************************/
bool SIM_HAL_GetSyncXbarBPittrigXcmd(SIM_Type* base, uint32_t instance);

/*!
 *
 * @brief Synchronize XBARA's output for DAC Hardware Trigger with flash/slow clock
 *
 * This function controls the synchronizer between XBARA's output and DAC hardware trigger.
 *
 * @param base Base address for current SIM instance.
 *END**************************************************************************/
void SIM_HAL_EnableSyncXbarDac(SIM_Type* base);

/*!
 *
 * @brief Synchronize XBARA's output for DAC Hardware Trigger with flash/slow clock
 *
 * This function Disables  the synchronizer  between XBARA's output and DAC hardware trigger
 *
 * @param base Base address for current SIM instance.
 *END**************************************************************************/
void SIM_HAL_DisableSyncXbarDac(SIM_Type* base);

/*!
 *
 * @brief Get the synchronizer cmd between XBARA's output and DAC hardware trigger
 *
 * @param base Base address for current SIM instance.
 * @return state true - synchronizer enabled, false - synchronizer disabled
 *END**************************************************************************/
bool SIM_HAL_GetSyncXbarDaccmd(SIM_Type* base);

/*!
 *
 * @brief Get the synchronizer cmd between XBARA's output  and EWM's ewm_in
 *
 * This function enables the synchronizer between XBARA's output and EWM's ewm_in
 *
 * @param base Base address for current SIM instance.
 *END**************************************************************************/
void SIM_HAL_EnableSyncXbarEwmin(SIM_Type* base);

/*!
 *
 * @brief Disable  the synchronizer  between XBARA's output and EWM's ewm_in
 *
 * This function Disables  the synchronizer  between XBARA's output and EWM's ewm_in
 *
 * @param base Base address for current SIM instance.
 *END**************************************************************************/
void SIM_HAL_DisableSyncXbarEwmin(SIM_Type* base);

/*!
 *
 * @brief Get the synchronizer cmd between XBARA's output  and EWM's ewm_in
 *
 * @param base Base address for current SIM instance.
 * @return state true - synchronizer enabled, false - synchronizer disabled
 *END**************************************************************************/
bool SIM_HAL_GetSyncXbarEwmincmd(SIM_Type* base);

/*!
 *
 * @brief Enable the the synchronizer between XBARA's output and CMPx's sample/window input
 *
 * This function enables the the synchronizer between XBARA's output and CMPx's sample/window input
 *
 * @param base Base address for current SIM instance.
 * @param instance comparator instance  
 *END**************************************************************************/
void SIM_HAL_EnableSyncXbarCmpX(SIM_Type* base, uint32_t instance);

/*!
 *
 * @brief Disable the synchronizer between XBARA's output and CMP3's sample/window input
 *
 * This function Disables the synchronizer between XBARA's output and CMP3's sample/window input
 *
 * @param base Base address for current SIM instance.
 * @param instance comparator instance  
 *END**************************************************************************/
void SIM_HAL_DisableSyncXbarCmpX(SIM_Type* base, uint32_t instance);

/*!
 *
 * @brief  Get the synchronizer cmd between XBARA's output and CMP3's sample/window input
 *
 * @param base Base address for current SIM instance.
 * @param instance comparator instance
 * @return state true - synchronizer enabled, false - synchronizer disabled
 *END**************************************************************************/
bool SIM_HAL_GetSyncXbarCmpXcmd(SIM_Type* base, uint32_t instance);

/*!
 *
 * @brief Set CMP Sample/Window Input X Source
 *
 * This function controls the sample/window source of CMP module
 *
 * @param base Base address for current SIM instance.
 * @param instance comparator instance 
 * @param select CMP Sample/Window Input X Source
 * 00 XBARA output - refer RM for specific cmp instance
 * 01 CMPx Sample/Window input is driven by both PDB0 and PDB1 pulse-out channel 0.
 * 10 PDB0 pulse-out channel 0.
 * 11 PDB1 pulse-out channel 0.
 *END**************************************************************************/
void SIM_HAL_SetCmpWinxSrc(SIM_Type* base, uint32_t instance,
                                      sim_cmp_win_in_src select);

/*!
 *
 * @brief Get CMP Sample/Window Input X Source
 *
 * This function will get the sample/window source of CMP module
 *
 * @param base Base address for current SIM instance.
 * @param instance comparator instance 
 * @return select CMP Sample/Window Input X Source
 * 00 XBARA output - refer RM for specific cmp instance
 * 01 CMPx Sample/Window input is driven by both PDB0 and PDB1 pulse-out channel 0.
 * 10 PDB0 pulse-out channel 0.
 * 11 PDB1 pulse-out channel 0.
 *END**************************************************************************/
sim_cmp_win_in_src SIM_HAL_GetCmpWinxSrc(SIM_Type* base, uint32_t instance);

/*!
 *
 * @brief Set EWM_IN source setting
 *
 * This function controls the ewm_in source of EWM module
 *
 * @param base Base address for current SIM instance.
 * @param select EWM_IN source , 0-XBARA output 58, 1-EWM_IN pin
 * 
 *END**************************************************************************/
void SIM_HAL_SetEwmInSrc(SIM_Type* base, sim_ewm_in_src select);

/*!
 *
 * @brief Get EWM_IN source setting
 *
 * This function will get the ewm_in source of EWM module 
 * @param base Base address for current SIM instance.
 * @return select EWM_IN source , 0-XBARA output 58, 1-EWM_IN pin
 *
 *END**************************************************************************/
sim_ewm_in_src SIM_HAL_GetEwmInSrc(SIM_Type* base);

/*!
 *
 * @brief Set DAC x Hardware trigger source setting
 *
 * This function will select the DAC0 Hardware Trigger Input Source
 *
 * @param base Base address for current SIM instance.
 * @param select DAC0 Hardware Trigger Input Source
 * 00 XBARA output 15.
 * 01 DAC0 can be triggered by both PDB0 interval trigger 0 and PDB1 interval trigger 0.
 * 10 PDB0 interval trigger 0
 * 11 PDB1 interval trigger 0
 *END**************************************************************************/
void SIM_HAL_SetDacHwTrigSrc(SIM_Type* base,sim_dac_hw_trg_sel select);

/*!
 *
 * @brief Get DAC x Hardware trigger source setting
 *
 * This function will get the DAC0 Hardware Trigger Input Source
 *
 * @param base Base address for current SIM instance.
 * @param instance DAC instance.
 * @return select DAC0 Hardware Trigger Input Source
 * 00 XBARA output 15.
 * 01 DAC0 can be triggered by both PDB0 interval trigger 0 and PDB1 interval trigger 0.
 * 10 PDB0 interval trigger 0
 * 11 PDB1 interval trigger 0
 *END**************************************************************************/
sim_dac_hw_trg_sel SIM_HAL_GetDacHwTrigSrc(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for PIT module.
 *
 * This function enables the clock for PIT module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnablePitClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for PIT module.
 *
 * This function disables the clock for PIT module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisablePitClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for PIT module.
 *
 * This function will get the clock gate state for PIT module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetPitGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for LPTIMER module.
 *
 * This function enables the clock for LPTIMER module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableLptmrClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for LPTIMER module.
 *
 * This function disables the clock for LPTIMER module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableLptmrClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for LPTIMER module.
 *
 * This function will get the clock gate state for LPTIMER module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetLptmrGateCmd(SIM_Type* base, uint32_t instance);


/*!
 * @brief Enable the clock for FLEXCAN module.
 *
 * This function enables the clock for FLEXCAN module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableFlexcanClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for FLEXCAN module.
 *
 * This function disables the clock for FLEXCAN module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableFlexcanClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for FLEXCAN module.
 *
 * This function will get the clock gate state for FLEXCAN module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetFlexcanGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for SPI module.
 *
 * This function enables the clock for SPI module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableSpiClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for SPI module.
 *
 * This function disables the clock for SPI module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableSpiClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for SPI module.
 *
 * This function will get the clock gate state for SPI module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetSpiGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for I2C module.
 *
 * This function enables the clock for I2C module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableI2cClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for I2C module.
 *
 * This function disables the clock for I2C module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableI2cClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for I2C module.
 *
 * This function will get the clock gate state for I2C module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetI2cGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for UART module.
 *
 * This function enables the clock for UART module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableUartClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for UART module.
 *
 * This function disables the clock for UART module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableUartClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for UART module.
 *
 * This function will get the clock gate state for UART module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetUartGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for eFlexPWM module.
 *
 * This function enables the clock for eFlexPWM module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @param channel PWM module channel
 */
void SIM_HAL_EnablePwmClock(SIM_Type* base, uint32_t instance, uint8_t channel);

/*!
 * @brief Disable the clock for eFlexPWM module.
 *
 * This function disables the clock for eFlexPWM module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @param channel PWM module channel
 */
void SIM_HAL_DisablePwmClock(SIM_Type* base, uint32_t instance, uint8_t channel);

/*!
 * @brief Get the the clock gate state for eFlexPWM module.
 *
 * This function will get the clock gate state for eFlexPWM module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @param channel PWM module channel
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetPwmGateCmd(SIM_Type* base, uint32_t instance, uint8_t channel);

/*!
 * @brief Enable the clock for AOI module.
 *
 * This function enables the clock for AOI module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableAoiClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for AOI module.
 *
 * This function disables the clock for AOI module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableAoiClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for AOI module.
 *
 * This function will get the clock gate state for AOI module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetAoiGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for XBAR module.
 *
 * This function enables the clock for XBAR module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableXbarClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for XBAR module.
 *
 * This function disables the clock for XBAR module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableXbarClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for XBAR module.
 *
 * This function will get the clock gate state for XBAR module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetXbarGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for ENC module.
 *
 * This function enables the clock for ENC module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableEncClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for ENC module.
 *
 * This function disables the clock for ENC module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableEncClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for ENC module.
 *
 * This function will get the clock gate state for ENC module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetEncGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for FLEXBUS module.
 *
 * This function enables the clock for FLEXBUS module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableFlexbusClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for FLEXBUS module.
 *
 * This function disables the clock for FLEXBUS module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableFlexbusClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for FLEXBUS module.
 *
 * This function will get the clock gate state for FLEXBUS module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetFlexbusGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for HSADC module.
 *
 * This function enables the clock for HSADC module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableHsadcClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for HSADC module.
 *
 * This function disables the clock for HSADC module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableHsadcClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for HSADC module.
 *
 * This function will get the clock gate state for HSADC module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetHsadcGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for ENET module.
 *
 * This function enables the clock for ENET module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableEnetClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for ENET module.
 *
 * This function disables the clock for ENET module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableEnetClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for ENET module.
 *
 * This function will get the clock gate state for ENET module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetEnetGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for MPU module.
 *
 * This function enables the clock for MPU module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableMpuClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for MPU module.
 *
 * This function disables the clock for MPU module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableMpuClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for MPU module.
 *
 * This function will get the clock gate state for MPU module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetMpuGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Enable the clock for TRNG module.
 *
 * This function enables the clock for TRNG module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableTrngClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Disable the clock for TRNG module.
 *
 * This function disables the clock for TRNG module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableTrngClock(SIM_Type* base, uint32_t instance);

/*!
 * @brief Get the the clock gate state for TRNG module.
 *
 * This function will get the clock gate state for TRNG module.
 *
 * @param base Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetTrngGateCmd(SIM_Type* base, uint32_t instance);

/*!
 * @brief Set the clock selection of ERCLK32K.
 *
 * This function sets the clock selection of ERCLK32K.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetExternalRefClock32kSrc(SIM_Type* base,
                                                       clock_er32k_src_t setting)
{
    SIM_BWR_SOPT1_OSC32KSEL(base, setting);
}

/*!
 * @brief Get the clock selection of ERCLK32K.
 *
 * This function gets the clock selection of ERCLK32K.
 *
 * @param base Base address for current SIM instance.
 * @return Current selection.
 */
static inline clock_er32k_src_t CLOCK_HAL_GetExternalRefClock32kSrc(SIM_Type* base)
{
    return (clock_er32k_src_t)SIM_BRD_SOPT1_OSC32KSEL(base);
}
/*!
 * @brief Set PLL/FLL clock selection.
 *
 * This function sets the selection of the high frequency clock for
 * various peripheral clocking options
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetPllfllSel(SIM_Type * base,
                                          clock_pllfll_sel_t setting)
{
    SIM_BWR_SOPT2_PLLFLLSEL(base, setting);
}

/*!
 * @brief Get PLL/FLL clock selection.
 *
 * This function gets the selection of the high frequency clock for
 * various peripheral clocking options
 *
 * @param base Base address for current SIM instance.
 * @return Current selection.
 */
static inline clock_pllfll_sel_t CLOCK_HAL_GetPllfllSel(SIM_Type * base)
{
    return (clock_pllfll_sel_t)SIM_BRD_SOPT2_PLLFLLSEL(base);
}

/*!
 * @brief Set CLKOUTSEL selection.
 *
 * This function sets the selection of the clock to output on the CLKOUT pin.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetClkOutSel(SIM_Type * base, clock_clkout_src_t setting)
{
    SIM_BWR_SOPT2_CLKOUTSEL(base, setting);
}

/*!
 * @brief Get CLKOUTSEL selection.
 *
 * This function gets the selection of the clock to output on the CLKOUT pin.
 *
 * @param base Base address for current SIM instance.
 * @return Current selection.
 */
static inline clock_clkout_src_t CLOCK_HAL_GetClkOutSel(SIM_Type * base)
{
    return (clock_clkout_src_t)SIM_BRD_SOPT2_CLKOUTSEL(base);
}

/*!
 * @brief Set debug trace clock selection.
 *
 * This function sets debug trace clock selection.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetTraceClkSrc(SIM_Type* base, clock_trace_src_t setting)
{
    SIM_BWR_SOPT2_TRACECLKSEL(base, setting);
}

/*!
 * @brief Get debug trace clock selection.
 *
 * This function gets debug trace clock selection.
 *
 * @param base Base address for current SIM instance.
 * @return Current selection.
 */
static inline clock_trace_src_t CLOCK_HAL_GetTraceClkSrc(SIM_Type* base)
{
    return (clock_trace_src_t)SIM_BRD_SOPT2_TRACECLKSEL(base);
}

/*!
 * @brief Get Nanoedge PMC Status
 *
 * This function gets Nanoedge power supply status.
 *
 * @param base Base address for current SIM instance.
 * @return power supply status.
 */
static inline bool CLOCK_HAL_GetNanoedgePMCStatus(SIM_Type* base)
{
    return (bool)SIM_BRD_PWRC_SRPWROK(base);
}
/*@}*/

/*!
 * @brief Set Nanoedge PMC POWER Ready
 *
 * This function sets soft control to indicate nanoedge PMC is ready,
 * when PMC Power dectect is disabled by SRPWRDETEN
 * @param base Base address for current SIM instance.
 * @param select power supply status.
 */
static inline void CLOCK_HAL_SetNanoedgePMCPwrRdy(SIM_Type* base, bool select)
{
    SIM_BWR_PWRC_SRPWRRDY(base, select);
}

/*!
 * @brief Get Nanoedge PMC POWER Ready
 *
 * This function gets soft control to indicate nanoedge PMC is ready.
 *
 * @param base Base address for current SIM instance.
 * @return power supply status.
 */
static inline bool CLOCK_HAL_GetNanoedgePMCPwrRdy(SIM_Type* base)
{
    return (bool)SIM_BRD_PWRC_SRPWRRDY(base);
}
/*@}*/

/*!
 * @brief Nanoedge PMC POWER Dectect Enable
 *
 * enable Nanoedge PMC power dectect to assert PMC ready signal when PMC is stable.
 *
 * @param base Base address for current SIM instance.
 * 
 */
static inline void CLOCK_HAL_EnableNanoedgePmcPowerDectect (SIM_Type* base)
{
    SIM_BWR_PWRC_SRPWRDETEN(base, 1);
}

/*!
 * @brief Nanoedge PMC POWER Dectect Disable
 *
 * disable Nanoedge PMC power dectect to assert PMC ready signal when PMC is stable.
 *
 * @param base Base address for current SIM instance.
 * 
 */
static inline void CLOCK_HAL_DisableNanoedgePmcPowerDectect (SIM_Type* base)
{
    SIM_BWR_PWRC_SRPWRDETEN(base, 0);
}

/*!
 * @brief Get Nanoedge PMC POWER Dectect
 *
 * This function gets Nanoedge PMC power dectect to assert PMC ready signal when PMC is stable
 *
 * @param base Base address for current SIM instance.
 * @return PMC power dectect status.
 */
static inline bool CLOCK_HAL_GetNanoedgePmcPowerDectectcmd(SIM_Type* base)
{
    return (bool)SIM_BRD_PWRC_SRPWRDETEN(base);
}

/*!
 * @brief Get HSADC Clock Status
 *
 * This function returns which clock is fed in HSADC.
 * 0 HSADC clock is fast peripherial clock.
 * 1 HSADC clock is MCGIRCLK.
 *
 * @param base Base address for current SIM instance.
 * @return HSADC Clock Status.
 */
static inline bool CLOCK_HAL_GetHsadcClkStatus(SIM_Type* base)
{
    return (bool)SIM_BRD_ADCOPT_HSADCIRCLK(base);
}

/*!
 * @brief Enable HSADC low current Mode
 *
 * Control HSADC low current mode in STOP and VLPS mode.
 *
 * @param base Base address for current SIM instance.
 * 
 */
static inline void CLOCK_HAL_EnableHsadcLowCurrentMode(SIM_Type* base)
{
    SIM_BWR_ADCOPT_HSADCSTOPEN(base, 1);
}

/*!
 * @brief Disable HSADC low current Mode
 *
 * Control HSADC low current mode in STOP and VLPS mode.
 *
 * @param base Base address for current SIM instance.
 * 
 */
static inline void CLOCK_HAL_DisableHsadcLowCurrentMode(SIM_Type* base)
{
    SIM_BWR_ADCOPT_HSADCSTOPEN(base, 0);
}

/*!
 * @brief Get HSADC low current Mode
 *
 * This function gets HSADC low current mode in STOP and VLPS mode.
 *
 * @param base Base address for current SIM instance.
 * @return HSADC low current mode status.
 */
static inline bool CLOCK_HAL_GetHsadcLowCurrentModecmd(SIM_Type* base)
{
    return (bool)SIM_BRD_ADCOPT_HSADCSTOPEN(base);
}
/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/


/*! @}*/

#endif /* __FSL_SIM_HAL_MKV58F24_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/


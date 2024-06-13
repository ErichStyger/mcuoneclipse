/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2020, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_clock.h"
#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.clock"
#endif

#define OTP_INIT_API      ((void (*)(uint32_t src_clk_freq))FSL_ROM_OTP_INIT_ADDR)
#define OTP_DEINIT_API    ((void (*)(void))FSL_ROM_OTP_DEINIT_ADDR)
#define OTP_FUSE_READ_API ((void (*)(uint32_t addr, uint32_t * data)) FSL_ROM_OTP_FUSE_READ_ADDR)
/* OTP fuse index. */
#define FFRO_STABLE_TIME       12
#define SFRO_STABLE_TIME       13
#define FIRC_48MHZ_TRIM_TEMPCO 48
#define FIRC_48MHZ_TRIM_COARSE 49
#define FIRC_48MHZ_TRIM_FINE   50
#define FIRC_60MHZ_TRIM_TEMPCO 51
#define FIRC_60MHZ_TRIM_COARSE 52
#define FIRC_60MHZ_TRIM_FINE   53
/*******************************************************************************
 * Variables
 ******************************************************************************/

/* External XTAL (OSC) clock frequency. */
volatile uint32_t g_xtalFreq = 0U;
/* External CLK_IN pin clock frequency. */
volatile uint32_t g_clkinFreq = 0U;
/* External MCLK in (mclk_in) clock frequency. If not used,
   set this to 0. Otherwise, set it to the exact rate in Hz this pin is
   being driven at.*/
volatile uint32_t g_mclkFreq = 0U;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* Clock Selection for IP */
/**
 * brief   Configure the clock selection muxes.
 * param   connection  : Clock to be configured.
 * return  Nothing
 */
void CLOCK_AttachClk(clock_attach_id_t connection)
{
    bool final_descriptor = false;
    uint32_t i;
    volatile uint32_t *pClkSel;

    for (i = 0U; (i < 2U) && (!final_descriptor); i++)
    {
        connection =
            (clock_attach_id_t)(uint32_t)(((uint32_t)connection) >> (i * 16U)); /*!<  pick up next descriptor */

        if (((((uint32_t)connection) & 0x80000000U) | ((((uint32_t)connection) & 0x8000U))) != 0UL)
        {
            pClkSel = CLKCTL_TUPLE_REG(CLKCTL1, connection);
        }
        else
        {
            pClkSel = CLKCTL_TUPLE_REG(CLKCTL0, connection);
        }

        if ((((uint32_t)connection) & 0xfffU) != 0UL)
        {
            *pClkSel = CLKCTL_TUPLE_SEL(connection);
        }
        else
        {
            final_descriptor = true;
        }
    }
}
/* Set IP Clock divider */
/**
 * brief   Setup peripheral clock dividers.
 * param   div_name    : Clock divider name
 * param   divider     : Value to be divided. Divided clock frequency = Undivided clock frequency / divider.
 * return  Nothing
 */
void CLOCK_SetClkDiv(clock_div_name_t div_name, uint32_t divider)
{
    volatile uint32_t *pClkDiv;

    if ((((uint32_t)div_name) & 0x80000000U) != 0UL)
    {
        pClkDiv = CLKCTL_TUPLE_REG(CLKCTL1, div_name);
    }
    else
    {
        pClkDiv = CLKCTL_TUPLE_REG(CLKCTL0, div_name);
    }
    /* Reset the divider counter */
    *pClkDiv |= 1UL << 29U;

    if (divider == 0U) /*!<  halt */
    {
        *pClkDiv |= 1UL << 30U;
    }
    else
    {
        *pClkDiv = divider - 1U;

        while (((*pClkDiv) & 0x80000000U) != 0UL)
        {
        }
    }
}
/*! @brief  Return Frequency of High-Freq output of FRO
 *  @return Frequency of High-Freq output of FRO
 */
uint32_t CLOCK_GetFFroFreq(void)
{
    uint32_t freq = 0U;
    /* FFROCTL0 should not be touched by application */
    switch ((CLKCTL0->FFROCTL0) & CLKCTL0_FFROCTL0_TRIM_RANGE_MASK)
    {
        case CLKCTL0_FFROCTL0_TRIM_RANGE(0):
            freq = CLK_FRO_48MHZ;
            break;
        case CLKCTL0_FFROCTL0_TRIM_RANGE(3):
            freq = CLK_FRO_60MHZ;
            break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}
/* Get SYSTEM PLL Clk */
/*! brief  Return Frequency of SYSPLL
 *  return Frequency of SYSPLL
 */
uint32_t CLOCK_GetSysPllFreq(void)
{
    uint32_t freq = 0U;
    uint64_t freqTmp;

    switch ((CLKCTL0->SYSPLL0CLKSEL) & CLKCTL0_SYSPLL0CLKSEL_SEL_MASK)
    {
        case CLKCTL0_SYSPLL0CLKSEL_SEL(0):
            freq = CLOCK_GetSFroFreq();
            break;
        case CLKCTL0_SYSPLL0CLKSEL_SEL(1):
            freq = CLOCK_GetXtalInClkFreq();
            break;
        case CLKCTL0_SYSPLL0CLKSEL_SEL(2):
            freq = CLOCK_GetFFroFreq() / 2U;
            break;
        default:
            /* Added comments to prevent the violation of MISRA C-2012 rule. */
            break;
    }

    if (((CLKCTL0->SYSPLL0CTL0) & CLKCTL0_SYSPLL0CTL0_BYPASS_MASK) == 0U)
    {
        /* PLL output frequency = Fref * (DIV_SELECT + NUM/DENOM). */
        freqTmp = ((uint64_t)freq * ((uint64_t)(CLKCTL0->SYSPLL0NUM))) / ((uint64_t)(CLKCTL0->SYSPLL0DENOM));
        freq *= ((CLKCTL0->SYSPLL0CTL0) & CLKCTL0_SYSPLL0CTL0_MULT_MASK) >> CLKCTL0_SYSPLL0CTL0_MULT_SHIFT;
        freq += (uint32_t)freqTmp;
    }
    return freq;
}
/* Get SYSTEM PLL PFDn Clk */
/*! brief  Get current output frequency of specific System PLL PFD.
 *  param   pfd    : pfd name to get frequency.
 *  return  Frequency of SYSPLL PFD.
 */
uint32_t CLOCK_GetSysPfdFreq(clock_pfd_t pfd)
{
    uint32_t freq = CLOCK_GetSysPllFreq();

    if (((CLKCTL0->SYSPLL0CTL0) & CLKCTL0_SYSPLL0CTL0_BYPASS_MASK) == 0U)
    {
        switch (pfd)
        {
            case kCLOCK_Pfd0:
                freq =
                    (uint32_t)((uint64_t)freq * 18ULL /
                               ((CLKCTL0->SYSPLL0PFD & CLKCTL0_SYSPLL0PFD_PFD0_MASK) >> CLKCTL0_SYSPLL0PFD_PFD0_SHIFT));
                break;

            case kCLOCK_Pfd1:
                freq =
                    (uint32_t)((uint64_t)freq * 18ULL /
                               ((CLKCTL0->SYSPLL0PFD & CLKCTL0_SYSPLL0PFD_PFD1_MASK) >> CLKCTL0_SYSPLL0PFD_PFD1_SHIFT));
                break;

            case kCLOCK_Pfd2:
                freq =
                    (uint32_t)((uint64_t)freq * 18ULL /
                               ((CLKCTL0->SYSPLL0PFD & CLKCTL0_SYSPLL0PFD_PFD2_MASK) >> CLKCTL0_SYSPLL0PFD_PFD2_SHIFT));
                break;

            case kCLOCK_Pfd3:
                freq =
                    (uint32_t)((uint64_t)freq * 18ULL /
                               ((CLKCTL0->SYSPLL0PFD & CLKCTL0_SYSPLL0PFD_PFD3_MASK) >> CLKCTL0_SYSPLL0PFD_PFD3_SHIFT));
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq;
}
static uint32_t CLOCK_GetMainPllClkFreq(void)
{
    return CLOCK_GetSysPfdFreq(kCLOCK_Pfd0) / ((CLKCTL0->MAINPLLCLKDIV & CLKCTL0_MAINPLLCLKDIV_DIV_MASK) + 1U);
}
static uint32_t CLOCK_GetDspPllClkFreq(void)
{
    return CLOCK_GetSysPfdFreq(kCLOCK_Pfd1) / ((CLKCTL0->DSPPLLCLKDIV & CLKCTL0_DSPPLLCLKDIV_DIV_MASK) + 1U);
}
static uint32_t CLOCK_GetAux0PllClkFreq(void)
{
    return CLOCK_GetSysPfdFreq(kCLOCK_Pfd2) / ((CLKCTL0->AUX0PLLCLKDIV & CLKCTL0_AUX0PLLCLKDIV_DIV_MASK) + 1U);
}
static uint32_t CLOCK_GetAux1PllClkFreq(void)
{
    return CLOCK_GetSysPfdFreq(kCLOCK_Pfd3) / ((CLKCTL0->AUX1PLLCLKDIV & CLKCTL0_AUX1PLLCLKDIV_DIV_MASK) + 1U);
}
/* Get AUDIO PLL Clk */
/*! brief  Return Frequency of AUDIO PLL
 *  return Frequency of AUDIO PLL
 */
uint32_t CLOCK_GetAudioPllFreq(void)
{
    uint32_t freq = 0U;
    uint64_t freqTmp;

    switch ((CLKCTL1->AUDIOPLL0CLKSEL) & CLKCTL1_AUDIOPLL0CLKSEL_SEL_MASK)
    {
        case CLKCTL1_AUDIOPLL0CLKSEL_SEL(0):
            freq = CLOCK_GetSFroFreq();
            break;
        case CLKCTL1_AUDIOPLL0CLKSEL_SEL(1):
            freq = CLOCK_GetXtalInClkFreq();
            break;
        case CLKCTL1_AUDIOPLL0CLKSEL_SEL(2):
            freq = CLOCK_GetFFroFreq() / 2U;
            break;
        default:
            freq = 0U;
            break;
    }

    if (((CLKCTL1->AUDIOPLL0CTL0) & CLKCTL1_AUDIOPLL0CTL0_BYPASS_MASK) == 0UL)
    {
        /* PLL output frequency = Fref * (DIV_SELECT + NUM/DENOM). */
        freqTmp = ((uint64_t)freq * ((uint64_t)(CLKCTL1->AUDIOPLL0NUM))) / ((uint64_t)(CLKCTL1->AUDIOPLL0DENOM));
        freq *= ((CLKCTL1->AUDIOPLL0CTL0) & CLKCTL1_AUDIOPLL0CTL0_MULT_MASK) >> CLKCTL1_AUDIOPLL0CTL0_MULT_SHIFT;
        freq += (uint32_t)freqTmp;
    }
    return freq;
}
/* Get AUDIO PLL PFDn Clk */
/*! brief  Get current output frequency of specific Audio PLL PFD.
 *  param   pfd    : pfd name to get frequency.
 *  return  Frequency of AUDIO PLL PFD.
 */
uint32_t CLOCK_GetAudioPfdFreq(clock_pfd_t pfd)
{
    uint32_t freq = CLOCK_GetAudioPllFreq();

    if (((CLKCTL1->AUDIOPLL0CTL0) & CLKCTL1_AUDIOPLL0CTL0_BYPASS_MASK) == 0UL)
    {
        switch (pfd)
        {
            case kCLOCK_Pfd0:
                freq = (uint32_t)(
                    (uint64_t)freq * 18ULL /
                    ((CLKCTL1->AUDIOPLL0PFD & CLKCTL1_AUDIOPLL0PFD_PFD0_MASK) >> CLKCTL1_AUDIOPLL0PFD_PFD0_SHIFT));
                break;

            case kCLOCK_Pfd1:
                freq = (uint32_t)(
                    (uint64_t)freq * 18ULL /
                    ((CLKCTL1->AUDIOPLL0PFD & CLKCTL1_AUDIOPLL0PFD_PFD1_MASK) >> CLKCTL1_AUDIOPLL0PFD_PFD1_SHIFT));
                break;

            case kCLOCK_Pfd2:
                freq = (uint32_t)(
                    (uint64_t)freq * 18ULL /
                    ((CLKCTL1->AUDIOPLL0PFD & CLKCTL1_AUDIOPLL0PFD_PFD2_MASK) >> CLKCTL1_AUDIOPLL0PFD_PFD2_SHIFT));
                break;

            case kCLOCK_Pfd3:
                freq = (uint32_t)(
                    (uint64_t)freq * 18ULL /
                    ((CLKCTL1->AUDIOPLL0PFD & CLKCTL1_AUDIOPLL0PFD_PFD3_MASK) >> CLKCTL1_AUDIOPLL0PFD_PFD3_SHIFT));
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq;
}
static uint32_t CLOCK_GetAudioPllClkFreq(void)
{
    return CLOCK_GetAudioPfdFreq(kCLOCK_Pfd0) / ((CLKCTL1->AUDIOPLLCLKDIV & CLKCTL1_AUDIOPLLCLKDIV_DIV_MASK) + 1U);
}
/* Get MAIN Clk */
/*! brief  Return Frequency of main clk
 *  return Frequency of main clk
 */
uint32_t CLOCK_GetMainClkFreq(void)
{
    uint32_t freq = 0U;

    switch ((CLKCTL0->MAINCLKSELB) & CLKCTL0_MAINCLKSELB_SEL_MASK)
    {
        case CLKCTL0_MAINCLKSELB_SEL(0):
            switch ((CLKCTL0->MAINCLKSELA) & CLKCTL0_MAINCLKSELA_SEL_MASK)
            {
                case CLKCTL0_MAINCLKSELA_SEL(0):
                    freq = CLOCK_GetFFroFreq() / 4U;
                    break;
                case CLKCTL0_MAINCLKSELA_SEL(1):
                    freq = CLOCK_GetXtalInClkFreq();
                    break;
                case CLKCTL0_MAINCLKSELA_SEL(2):
                    freq = CLOCK_GetLpOscFreq();
                    break;
                case CLKCTL0_MAINCLKSELA_SEL(3):
                    freq = CLOCK_GetFFroFreq();
                    break;
                default:
                    freq = 0U;
                    break;
            }
            break;

        case CLKCTL0_MAINCLKSELB_SEL(1):
            freq = CLOCK_GetSFroFreq();
            break;

        case CLKCTL0_MAINCLKSELB_SEL(2):
            freq = CLOCK_GetMainPllClkFreq();
            break;

        case CLKCTL0_MAINCLKSELB_SEL(3):
            freq = CLOCK_GetOsc32KFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    return freq;
}
/* Get DSP MAIN Clk */
/*! brief  Return Frequency of DSP main clk
 *  return Frequency of DSP main clk
 */
uint32_t CLOCK_GetDspMainClkFreq(void)
{
    uint32_t freq = 0U;

    switch ((CLKCTL1->DSPCPUCLKSELB) & CLKCTL1_DSPCPUCLKSELB_SEL_MASK)
    {
        case CLKCTL1_DSPCPUCLKSELB_SEL(0):
            switch ((CLKCTL1->DSPCPUCLKSELA) & CLKCTL1_DSPCPUCLKSELA_SEL_MASK)
            {
                case CLKCTL1_DSPCPUCLKSELA_SEL(0):
                    freq = CLOCK_GetFFroFreq();
                    break;
                case CLKCTL1_DSPCPUCLKSELA_SEL(1):
                    freq = CLOCK_GetXtalInClkFreq();
                    break;
                case CLKCTL1_DSPCPUCLKSELA_SEL(2):
                    freq = CLOCK_GetLpOscFreq();
                    break;
                case CLKCTL1_DSPCPUCLKSELA_SEL(3):
                    freq = CLOCK_GetSFroFreq();
                    break;
                default:
                    freq = 0U;
                    break;
            }
            break;

        case CLKCTL1_DSPCPUCLKSELB_SEL(1):
            freq = CLOCK_GetMainPllClkFreq();
            break;

        case CLKCTL1_DSPCPUCLKSELB_SEL(2):
            freq = CLOCK_GetDspPllClkFreq();
            break;

        case CLKCTL1_DSPCPUCLKSELB_SEL(3):
            freq = CLOCK_GetOsc32KFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    return freq;
}
/* Get ADC Clk */
/*! brief  Return Frequency of Adc Clock
 *  return Frequency of Adc Clock.
 */
uint32_t CLOCK_GetAdcClkFreq(void)
{
    uint32_t freq = 0U;

    switch ((CLKCTL0->ADC0FCLKSEL1) & CLKCTL0_ADC0FCLKSEL1_SEL_MASK)
    {
        case CLKCTL0_ADC0FCLKSEL1_SEL(0):
            switch ((CLKCTL0->ADC0FCLKSEL0) & CLKCTL0_ADC0FCLKSEL0_SEL_MASK)
            {
                case CLKCTL0_ADC0FCLKSEL0_SEL(0):
                    freq = CLOCK_GetSFroFreq();
                    break;
                case CLKCTL0_ADC0FCLKSEL0_SEL(1):
                    freq = CLOCK_GetXtalInClkFreq();
                    break;
                case CLKCTL0_ADC0FCLKSEL0_SEL(2):
                    freq = CLOCK_GetLpOscFreq();
                    break;
                case CLKCTL0_ADC0FCLKSEL0_SEL(3):
                    freq = CLOCK_GetFFroFreq();
                    break;
                default:
                    freq = 0U;
                    break;
            }
            break;

        case CLKCTL0_ADC0FCLKSEL1_SEL(1):
            freq = CLOCK_GetMainPllClkFreq();
            break;

        case CLKCTL0_ADC0FCLKSEL1_SEL(3):
            freq = CLOCK_GetAux0PllClkFreq();
            break;

        case CLKCTL0_ADC0FCLKSEL1_SEL(5):
            freq = CLOCK_GetAux1PllClkFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    return freq / ((CLKCTL0->ADC0FCLKDIV & CLKCTL0_ADC0FCLKDIV_DIV_MASK) + 1U);
}
/* Get CLOCK OUT Clk */
/*! brief  Return Frequency of ClockOut
 *  return Frequency of ClockOut
 */
uint32_t CLOCK_GetClockOutClkFreq(void)
{
    uint32_t freq = 0U;

    switch ((CLKCTL1->CLKOUTSEL1) & CLKCTL1_CLKOUTSEL1_SEL_MASK)
    {
        case CLKCTL1_CLKOUTSEL1_SEL(0):
            switch ((CLKCTL1->CLKOUTSEL0) & CLKCTL1_CLKOUTSEL0_SEL_MASK)
            {
                case CLKCTL1_CLKOUTSEL0_SEL(0):
                    freq = CLOCK_GetSFroFreq();
                    break;
                case CLKCTL1_CLKOUTSEL0_SEL(1):
                    freq = CLOCK_GetXtalInClkFreq();
                    break;
                case CLKCTL1_CLKOUTSEL0_SEL(2):
                    freq = CLOCK_GetLpOscFreq();
                    break;
                case CLKCTL1_CLKOUTSEL0_SEL(3):
                    freq = CLOCK_GetFFroFreq();
                    break;
                case CLKCTL1_CLKOUTSEL0_SEL(4):
                    freq = CLOCK_GetMainClkFreq();
                    break;
                case CLKCTL1_CLKOUTSEL0_SEL(6):
                    freq = CLOCK_GetDspMainClkFreq();
                    break;
                default:
                    freq = 0U;
                    break;
            }
            break;

        case CLKCTL1_CLKOUTSEL1_SEL(1):
            freq = CLOCK_GetMainPllClkFreq();
            break;

        case CLKCTL1_CLKOUTSEL1_SEL(2):
            freq = CLOCK_GetAux0PllClkFreq();
            break;

        case CLKCTL1_CLKOUTSEL1_SEL(3):
            freq = CLOCK_GetDspPllClkFreq();
            break;

        case CLKCTL1_CLKOUTSEL1_SEL(4):
            freq = CLOCK_GetAux1PllClkFreq();
            break;

        case CLKCTL1_CLKOUTSEL1_SEL(5):
            freq = CLOCK_GetAudioPllClkFreq();
            break;

        case CLKCTL1_CLKOUTSEL1_SEL(6):
            freq = CLOCK_GetOsc32KFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    return freq / ((CLKCTL1->CLKOUTDIV & CLKCTL1_CLKOUTDIV_DIV_MASK) + 1U);
}
/* Get FRG Clk */
/*! brief  Return Input frequency for the Fractional baud rate generator
 *  return Input Frequency for FRG
 */
uint32_t CLOCK_GetFRGClock(uint32_t id)
{
    uint32_t freq      = 0U;
    uint32_t frgPllDiv = 1U;
    uint32_t clkSel    = 0U;
    uint32_t frgDiv    = 0U;
    uint32_t frgMul    = 0U;

    if (id <= 7UL)
    {
        clkSel = CLKCTL1->FLEXCOMM[id].FRGCLKSEL & CLKCTL1_FRGCLKSEL_SEL_MASK;
        frgMul = ((CLKCTL1->FLEXCOMM[id].FRGCTL) & CLKCTL1_FRGCTL_MULT_MASK) >> CLKCTL1_FRGCTL_MULT_SHIFT;
        frgDiv = ((CLKCTL1->FLEXCOMM[id].FRGCTL) & CLKCTL1_FRGCTL_DIV_MASK) >> CLKCTL1_FRGCTL_DIV_SHIFT;
    }
    else if (id == 14UL)
    {
        clkSel = CLKCTL1->FRG14CLKSEL & CLKCTL1_FRG14CLKSEL_SEL_MASK;
        frgMul = ((CLKCTL1->FRG14CTL) & CLKCTL1_FRGCTL_MULT_MASK) >> CLKCTL1_FRGCTL_MULT_SHIFT;
        frgDiv = ((CLKCTL1->FRG14CTL) & CLKCTL1_FRGCTL_DIV_MASK) >> CLKCTL1_FRGCTL_DIV_SHIFT;
    }
    else if (id == 15UL)
    {
        clkSel = CLKCTL1->FRG15CLKSEL & CLKCTL1_FRG14CLKSEL_SEL_MASK;
        frgMul = ((CLKCTL1->FRG15CTL) & CLKCTL1_FRGCTL_MULT_MASK) >> CLKCTL1_FRGCTL_MULT_SHIFT;
        frgDiv = ((CLKCTL1->FRG15CTL) & CLKCTL1_FRGCTL_DIV_MASK) >> CLKCTL1_FRGCTL_DIV_SHIFT;
    }
    else
    {
        assert(false);
    }

    switch (clkSel)
    {
        case CLKCTL1_FRGCLKSEL_SEL(0):
            freq = CLOCK_GetMainClkFreq();
            break;

        case CLKCTL1_FRGCLKSEL_SEL(1):
            frgPllDiv = (CLKCTL1->FRGPLLCLKDIV & CLKCTL1_FRGPLLCLKDIV_DIV_MASK) + 1U;
            freq      = CLOCK_GetMainPllClkFreq() / frgPllDiv;
            break;

        case CLKCTL1_FRGCLKSEL_SEL(2):
            freq = CLOCK_GetSFroFreq();
            break;

        case CLKCTL1_FRGCLKSEL_SEL(3):
            freq = CLOCK_GetFFroFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    return (uint32_t)(((uint64_t)freq * ((uint64_t)frgDiv + 1ULL)) / (frgMul + frgDiv + 1UL));
}
/* Get FLEXCOMM Clk */
/*! brief  Return Frequency of Flexcomm functional Clock
 *  param   id    : flexcomm index to get frequency.
 *  return Frequency of Flexcomm functional Clock
 */
uint32_t CLOCK_GetFlexCommClkFreq(uint32_t id)
{
    uint32_t freq   = 0U;
    uint32_t clkSel = 0U;

    if (id <= 7UL)
    {
        clkSel = CLKCTL1->FLEXCOMM[id].FCFCLKSEL;
    }
    else if (id == 14UL)
    {
        clkSel = CLKCTL1->FC14FCLKSEL;
    }
    else if (id == 15UL)
    {
        clkSel = CLKCTL1->FC15FCLKSEL;
    }
    else
    {
        assert(false);
    }

    switch (clkSel)
    {
        case CLKCTL1_FCFCLKSEL_SEL(0):
            freq = CLOCK_GetSFroFreq();
            break;

        case CLKCTL1_FCFCLKSEL_SEL(1):
            freq = CLOCK_GetFFroFreq();
            break;

        case CLKCTL1_FCFCLKSEL_SEL(2):
            freq = CLOCK_GetAudioPllClkFreq();
            break;

        case CLKCTL1_FCFCLKSEL_SEL(3):
            freq = CLOCK_GetMclkInClkFreq();
            break;

        case CLKCTL1_FCFCLKSEL_SEL(4):
            freq = CLOCK_GetFRGClock(id);
            break;

        default:
            freq = 0U;
            break;
    }

    return freq;
}
/* Get CTIMER Clk */
/*! brief  Return Frequency of Ctimer Clock
 *  param   id    : ctimer index to get frequency.
 *  return Frequency of Ctimer Clock
 */
uint32_t CLOCK_GetCtimerClkFreq(uint32_t id)
{
    uint32_t freq = 0U;

    switch ((CLKCTL1->CT32BITFCLKSEL[id]) & CLKCTL1_CT32BITFCLKSEL_SEL_MASK)
    {
        case CLKCTL1_CT32BITFCLKSEL_SEL(0):
            freq = CLOCK_GetMainClkFreq();
            break;

        case CLKCTL1_CT32BITFCLKSEL_SEL(1):
            freq = CLOCK_GetSFroFreq();
            break;

        case CLKCTL1_CT32BITFCLKSEL_SEL(2):
            freq = CLOCK_GetFFroFreq();
            break;

        case CLKCTL1_CT32BITFCLKSEL_SEL(3):
            freq = CLOCK_GetAudioPllClkFreq();
            break;

        case CLKCTL1_CT32BITFCLKSEL_SEL(4):
            freq = CLOCK_GetMclkInClkFreq();
            break;

        case CLKCTL1_CT32BITFCLKSEL_SEL(5):
            freq = CLOCK_GetLpOscFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    return freq;
}
/* Get FLEXSPI Clk */
/*! brief  Return Frequency of FLEXSPI Clock
 *  return Frequency of FLEXSPI.
 */
uint32_t CLOCK_GetFlexspiClkFreq(void)
{
    uint32_t freq = 0U;

    switch ((CLKCTL0->FLEXSPIFCLKSEL) & CLKCTL0_FLEXSPIFCLKSEL_SEL_MASK)
    {
        case CLKCTL0_FLEXSPIFCLKSEL_SEL(0):
            freq = CLOCK_GetMainClkFreq();
            break;

        case CLKCTL0_FLEXSPIFCLKSEL_SEL(1):
            freq = CLOCK_GetMainPllClkFreq();
            break;

        case CLKCTL0_FLEXSPIFCLKSEL_SEL(2):
            freq = CLOCK_GetAux0PllClkFreq();
            break;

        case CLKCTL0_FLEXSPIFCLKSEL_SEL(3):
            freq = CLOCK_GetFFroFreq();
            break;

        case CLKCTL0_FLEXSPIFCLKSEL_SEL(4):
            freq = CLOCK_GetAux1PllClkFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    return freq / ((CLKCTL0->FLEXSPIFCLKDIV & CLKCTL0_FLEXSPIFCLKDIV_DIV_MASK) + 1U);
}

/* Get SCT Clk */
/*! brief  Return Frequency of sct
 *  return Frequency of sct clk
 */
uint32_t CLOCK_GetSctClkFreq(void)
{
    uint32_t freq = 0U;

    switch ((CLKCTL0->SCTFCLKSEL) & CLKCTL0_SCTFCLKSEL_SEL_MASK)
    {
        case CLKCTL0_SCTFCLKSEL_SEL(0):
            freq = CLOCK_GetMainClkFreq();
            break;

        case CLKCTL0_SCTFCLKSEL_SEL(1):
            freq = CLOCK_GetMainPllClkFreq();
            break;

        case CLKCTL0_SCTFCLKSEL_SEL(2):
            freq = CLOCK_GetAux0PllClkFreq();
            break;

        case CLKCTL0_SCTFCLKSEL_SEL(3):
            freq = CLOCK_GetFFroFreq();
            break;

        case CLKCTL0_SCTFCLKSEL_SEL(4):
            freq = CLOCK_GetAux1PllClkFreq();
            break;

        case CLKCTL0_SCTFCLKSEL_SEL(5):
            freq = CLOCK_GetAudioPllClkFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    return freq / ((CLKCTL0->SCTFCLKDIV & CLKCTL0_SCTFCLKDIV_DIV_MASK) + 1U);
}

/*! brief  Return Frequency of mclk Out
 *  return Frequency of mclk Out clk
 */
uint32_t CLOCK_GetMclkClkFreq(void)
{
    uint32_t freq = 0U;

    if (CLKCTL1->AUDIOMCLKSEL == 0U)
    {
        freq = CLOCK_GetFFroFreq();
    }
    else if (CLKCTL1->AUDIOMCLKSEL == 1U)
    {
        freq = CLOCK_GetAudioPllClkFreq();
    }
    else
    {
        /* Added comments to prevent the violation of MISRA C-2012 rule 15.7. */
    }

    return freq / ((CLKCTL1->AUDIOMCLKDIV & CLKCTL1_AUDIOMCLKDIV_DIV_MASK) + 1U);
}

/*! @brief  Return Frequency of WDT clk
 *  @param  id : WDT index to get frequency.
 *  @return Frequency of WDT clk
 */
uint32_t CLOCK_GetWdtClkFreq(uint32_t id)
{
    uint32_t freq = 0U;

    assert(id <= 1UL);

    if (id == 0UL)
    {
        if ((CLKCTL0->WDT0FCLKSEL & CLKCTL0_WDT0FCLKSEL_SEL_MASK) == CLKCTL0_WDT0FCLKSEL_SEL(0))
        {
            freq = CLOCK_GetLpOscFreq();
        }
        else
        {
            freq = CLOCK_GetMainClkFreq();
        }
    }
    else
    {
        if ((CLKCTL1->WDT1FCLKSEL & CLKCTL1_WDT1FCLKSEL_SEL_MASK) == CLKCTL1_WDT1FCLKSEL_SEL(0))
        {
            freq = CLOCK_GetLpOscFreq();
        }
        else
        {
            freq = CLOCK_GetMainClkFreq();
        }
    }

    return freq;
}

/*! brief  Return Frequency of systick clk
 *  return Frequency of systick clk
 */
uint32_t CLOCK_GetSystickClkFreq(void)
{
    uint32_t freq = 0U;

    switch (CLKCTL0->SYSTICKFCLKSEL)
    {
        case CLKCTL0_SYSTICKFCLKSEL_SEL(0):
            freq = CLOCK_GetMainClkFreq() / ((CLKCTL0->SYSTICKFCLKDIV & CLKCTL0_SYSTICKFCLKDIV_DIV_MASK) + 1U);
            break;

        case CLKCTL0_SYSTICKFCLKSEL_SEL(1):
            freq = CLOCK_GetLpOscFreq();
            break;

        case CLKCTL0_SYSTICKFCLKSEL_SEL(2):
            freq = CLOCK_GetOsc32KFreq();
            break;

        case CLKCTL0_SYSTICKFCLKSEL_SEL(3):
            freq = CLOCK_GetSFroFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*! brief  Return Frequency of SDIO clk
 *  param id : SDIO index to get frequency.
 *  return Frequency of SDIO clk
 */
uint32_t CLOCK_GetSdioClkFreq(uint32_t id)
{
    uint32_t freq = 0U;
    volatile uint32_t *pClkSel;
    volatile uint32_t *pClkDiv;

    assert(id <= 1U);

    if (id == 0UL)
    {
        pClkSel = &CLKCTL0->SDIO0FCLKSEL;
        pClkDiv = &CLKCTL0->SDIO0FCLKDIV;
    }
    else
    {
        pClkSel = &CLKCTL0->SDIO1FCLKSEL;
        pClkDiv = &CLKCTL0->SDIO1FCLKDIV;
    }

    switch ((*pClkSel) & CLKCTL0_SDIO0FCLKSEL_SEL_MASK)
    {
        case CLKCTL0_SDIO0FCLKSEL_SEL(0):
            freq = CLOCK_GetMainClkFreq();
            break;

        case CLKCTL0_SDIO0FCLKSEL_SEL(1):
            freq = CLOCK_GetMainPllClkFreq();
            break;

        case CLKCTL0_SDIO0FCLKSEL_SEL(2):
            freq = CLOCK_GetAux0PllClkFreq();
            break;

        case CLKCTL0_SDIO0FCLKSEL_SEL(3):
            freq = CLOCK_GetFFroFreq();
            break;

        case CLKCTL0_SDIO0FCLKSEL_SEL(4):
            freq = CLOCK_GetAux1PllClkFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    return freq / (((*pClkDiv) & CLKCTL0_SDIO0FCLKDIV_DIV_MASK) + 1U);
}

/*! @brief  Return Frequency of I3C clk
 *  @return Frequency of I3C clk
 */
uint32_t CLOCK_GetI3cClkFreq(void)
{
    uint32_t freq = 0U;

    switch ((CLKCTL1->I3C0FCLKSEL) & CLKCTL1_I3C0FCLKSEL_SEL_MASK)
    {
        case CLKCTL1_I3C0FCLKSEL_SEL(0):
            freq = CLOCK_GetMainClkFreq();
            break;

        case CLKCTL1_I3C0FCLKSEL_SEL(1):
            freq = CLOCK_GetFFroFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    return freq / ((CLKCTL1->I3C0FCLKDIV & CLKCTL1_I3C0FCLKDIV_DIV_MASK) + 1U);
}

/*! brief  Return Frequency of USB clk
 *  return Frequency of USB clk
 */
uint32_t CLOCK_GetUsbClkFreq(void)
{
    uint32_t freq = 0U;

    if (CLKCTL0->USBHSFCLKSEL == 0U)
    {
        freq = CLOCK_GetXtalInClkFreq();
    }
    else if (CLKCTL0->USBHSFCLKSEL == 1U)
    {
        freq = CLOCK_GetMainClkFreq();
    }
    else
    {
        /* Add comments to prevent the violation of MISRA C-2012 rule 15.7 */
    }

    return freq / ((CLKCTL0->USBHSFCLKDIV & 0xffU) + 1U);
}

/*! brief  Return Frequency of DMIC clk
 *  return Frequency of DMIC clk
 */
uint32_t CLOCK_GetDmicClkFreq(void)
{
    uint32_t freq = 0U;

    switch ((CLKCTL1->DMIC0FCLKSEL) & CLKCTL1_DMIC0FCLKSEL_SEL_MASK)
    {
        case CLKCTL1_DMIC0FCLKSEL_SEL(0):
            freq = CLOCK_GetSFroFreq();
            break;

        case CLKCTL1_DMIC0FCLKSEL_SEL(1):
            freq = CLOCK_GetFFroFreq();
            break;

        case CLKCTL1_DMIC0FCLKSEL_SEL(2):
            freq = CLOCK_GetAudioPllClkFreq();
            break;

        case CLKCTL1_DMIC0FCLKSEL_SEL(3):
            freq = CLOCK_GetMclkInClkFreq();
            break;

        case CLKCTL1_DMIC0FCLKSEL_SEL(4):
            freq = CLOCK_GetLpOscFreq();
            break;

        case CLKCTL1_DMIC0FCLKSEL_SEL(5):
            freq = CLOCK_GetWakeClk32KFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    return freq / ((CLKCTL1->DMIC0FCLKDIV & 0xffU) + 1U);
}

/*! brief  Return Frequency of ACMP clk
 *  return Frequency of ACMP clk
 */
uint32_t CLOCK_GetAcmpClkFreq(void)
{
    uint32_t freq = 0U;

    switch ((CLKCTL1->ACMP0FCLKSEL) & CLKCTL1_ACMP0FCLKSEL_SEL_MASK)
    {
        case CLKCTL1_ACMP0FCLKSEL_SEL(0):
            freq = CLOCK_GetMainClkFreq();
            break;

        case CLKCTL1_ACMP0FCLKSEL_SEL(1):
            freq = CLOCK_GetSFroFreq();
            break;

        case CLKCTL1_ACMP0FCLKSEL_SEL(2):
            freq = CLOCK_GetFFroFreq();
            break;

        case CLKCTL1_ACMP0FCLKSEL_SEL(3):
            freq = CLOCK_GetAux0PllClkFreq();
            break;

        case CLKCTL1_ACMP0FCLKSEL_SEL(4):
            freq = CLOCK_GetAux1PllClkFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    return freq / ((CLKCTL1->ACMP0FCLKDIV & CLKCTL1_ACMP0FCLKDIV_DIV_MASK) + 1U);
}

/* Get IP Clk */
/*! brief  Return Frequency of selected clock
 *  return Frequency of selected clock
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName)
{
    uint32_t freq = 0U;

    switch (clockName)
    {
        case kCLOCK_CoreSysClk:
        case kCLOCK_BusClk:
            freq = CLOCK_GetMainClkFreq() / ((CLKCTL0->SYSCPUAHBCLKDIV & CLKCTL0_SYSCPUAHBCLKDIV_DIV_MASK) + 1U);
            break;
        case kCLOCK_MclkClk:
            freq = CLOCK_GetMclkClkFreq();
            break;
        case kCLOCK_ClockOutClk:
            freq = CLOCK_GetClockOutClkFreq();
            break;
        case kCLOCK_AdcClk:
            freq = CLOCK_GetAdcClkFreq();
            break;
        case kCLOCK_FlexspiClk:
            freq = CLOCK_GetFlexspiClkFreq();
            break;
        case kCLOCK_SctClk:
            freq = CLOCK_GetSctClkFreq();
            break;
        case kCLOCK_Wdt0Clk:
            freq = CLOCK_GetWdtClkFreq(0U);
            break;
        case kCLOCK_Wdt1Clk:
            freq = CLOCK_GetWdtClkFreq(1U);
            break;
        case kCLOCK_SystickClk:
            freq = CLOCK_GetSystickClkFreq();
            break;
        case kCLOCK_Sdio0Clk:
            freq = CLOCK_GetSdioClkFreq(0U);
            break;
        case kCLOCK_Sdio1Clk:
            freq = CLOCK_GetSdioClkFreq(1U);
            break;
        case kCLOCK_I3cClk:
            freq = CLOCK_GetI3cClkFreq();
            break;
        case kCLOCK_UsbClk:
            freq = CLOCK_GetUsbClkFreq();
            break;
        case kCLOCK_DmicClk:
            freq = CLOCK_GetDmicClkFreq();
            break;
        case kCLOCK_DspCpuClk:
            freq = CLOCK_GetDspMainClkFreq() / ((CLKCTL1->DSPCPUCLKDIV & CLKCTL1_DSPCPUCLKDIV_DIV_MASK) + 1U);
            break;
        case kCLOCK_AcmpClk:
            freq = CLOCK_GetAcmpClkFreq();
            break;
        case kCLOCK_Flexcomm0Clk:
            freq = CLOCK_GetFlexCommClkFreq(0U);
            break;
        case kCLOCK_Flexcomm1Clk:
            freq = CLOCK_GetFlexCommClkFreq(1U);
            break;
        case kCLOCK_Flexcomm2Clk:
            freq = CLOCK_GetFlexCommClkFreq(2U);
            break;
        case kCLOCK_Flexcomm3Clk:
            freq = CLOCK_GetFlexCommClkFreq(3U);
            break;
        case kCLOCK_Flexcomm4Clk:
            freq = CLOCK_GetFlexCommClkFreq(4U);
            break;
        case kCLOCK_Flexcomm5Clk:
            freq = CLOCK_GetFlexCommClkFreq(5U);
            break;
        case kCLOCK_Flexcomm6Clk:
            freq = CLOCK_GetFlexCommClkFreq(6U);
            break;
        case kCLOCK_Flexcomm7Clk:
            freq = CLOCK_GetFlexCommClkFreq(7U);
            break;
        case kCLOCK_Flexcomm14Clk:
            freq = CLOCK_GetFlexCommClkFreq(14U);
            break;
        case kCLOCK_Flexcomm15Clk:
            freq = CLOCK_GetFlexCommClkFreq(15U);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/* Set FRG Clk */
/*! brief  Set output of the Fractional baud rate generator
 * param   config    : Configuration to set to FRGn clock.
 */
void CLOCK_SetFRGClock(const clock_frg_clk_config_t *config)
{
    uint32_t i = config->num;

    assert(i <= 15U);
    assert(config->divider == 255U); /* Always set to 0xFF to use with the fractional baudrate generator.*/

    if (i <= 7UL)
    {
        CLKCTL1->FLEXCOMM[i].FRGCLKSEL = (uint32_t)config->sfg_clock_src;
        CLKCTL1->FLEXCOMM[i].FRGCTL    = (CLKCTL1_FRGCTL_MULT(config->mult) | CLKCTL1_FRGCTL_DIV(config->divider));
    }
    else if (i == 14UL)
    {
        CLKCTL1->FRG14CLKSEL = (uint32_t)config->sfg_clock_src;
        CLKCTL1->FRG14CTL    = (CLKCTL1_FRGCTL_MULT(config->mult) | CLKCTL1_FRGCTL_DIV(config->divider));
    }
    else if (i == 15UL)
    {
        CLKCTL1->FRG15CLKSEL = (uint32_t)config->sfg_clock_src;
        CLKCTL1->FRG15CTL    = (CLKCTL1_FRGCTL_MULT(config->mult) | CLKCTL1_FRGCTL_DIV(config->divider));
    }
    else
    {
        assert(false);
    }
}

#ifndef __XTENSA__
/**
 * brief  Enable FFRO 48M/60M clock.
 * Note   Need to make sure FFRO and ROM has power(PDRUNCFG0[16] and PDRUNCFG1[28] = 0U) before calling this API
 *
 * param  ffroFreq : target fro frequency.
 * return Nothing
 */
void CLOCK_EnableFfroClk(clock_ffro_freq_t ffroFreq)
{
    uint32_t tempco     = 0U;
    uint32_t coarse     = 0U;
    uint32_t fine       = 0U;
    uint32_t ffro_delay = 0U;

    assert(((SYSCTL0->PDRUNCFG0 & SYSCTL0_PDRUNCFG0_FFRO_PD_MASK) == 0UL) &&
           ((SYSCTL0->PDRUNCFG1 & SYSCTL0_PDRUNCFG1_ROM_PD_MASK) == 0UL));

    /* FFROCTL0, FFROCTL1 and the otp trim value should not be touched by application */
    CLKCTL0->FFROCTL1 |= CLKCTL0_FFROCTL1_UPDATE_MASK;
    OTP_INIT_API(CLOCK_GetMainClkFreq() / ((CLKCTL0->SYSCPUAHBCLKDIV & CLKCTL0_SYSCPUAHBCLKDIV_DIV_MASK) + 1U));
    if (ffroFreq == kCLOCK_Ffro48M)
    {
        /* Read 48M FFRO clock Trim settings from fuse. */
        OTP_FUSE_READ_API(FIRC_48MHZ_TRIM_TEMPCO, &tempco);
        OTP_FUSE_READ_API(FIRC_48MHZ_TRIM_COARSE, &coarse);
        OTP_FUSE_READ_API(FIRC_48MHZ_TRIM_FINE, &fine);
    }
    else
    {
        /* Read 60M FFRO clock Trim settings from fuse. */
        OTP_FUSE_READ_API(FIRC_60MHZ_TRIM_TEMPCO, &tempco);
        OTP_FUSE_READ_API(FIRC_60MHZ_TRIM_COARSE, &coarse);
        OTP_FUSE_READ_API(FIRC_60MHZ_TRIM_FINE, &fine);
    }
    /* Read FFRO stable time from fuse. */
    OTP_FUSE_READ_API(FFRO_STABLE_TIME, &ffro_delay);
    OTP_DEINIT_API();
    CLKCTL0->FFROCTL0 = CLKCTL0_FFROCTL0_TRIM_TEMPCO(tempco) | CLKCTL0_FFROCTL0_TRIM_COARSE(coarse) |
                        CLKCTL0_FFROCTL0_TRIM_FINE(fine) |
                        CLKCTL0_FFROCTL0_TRIM_RANGE((ffroFreq == kCLOCK_Ffro48M) ? 0 : 3);
    CLKCTL0->FFROCTL1 &= ~CLKCTL0_FFROCTL1_UPDATE_MASK;
    /* No FFRO enable/disable control in CLKCTL. Just wait FFRO stable in case FFRO just get powered on. */
    SDK_DelayAtLeastUs(ffro_delay, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
}
/**
 * brief   Enable SFRO clock.
 * Note    Need to make sure SFRO and ROM has power(PDRUNCFG0[15] and PDRUNCFG1[28] = 0U) before calling this API
 *
 * param   Nothing
 * return  Nothing
 */

void CLOCK_EnableSfroClk(void)
{
    uint32_t sfro_delay = 0U;

    assert(((SYSCTL0->PDRUNCFG0 & SYSCTL0_PDRUNCFG0_SFRO_PD_MASK) == 0UL) &&
           ((SYSCTL0->PDRUNCFG1 & SYSCTL0_PDRUNCFG1_ROM_PD_MASK) == 0UL));
    /* The otp trim value should not be touched by application */
    OTP_INIT_API(CLOCK_GetMainClkFreq() / ((CLKCTL0->SYSCPUAHBCLKDIV & CLKCTL0_SYSCPUAHBCLKDIV_DIV_MASK) + 1U));
    /* Read SFRO stable time from fuse. */
    OTP_FUSE_READ_API(SFRO_STABLE_TIME, &sfro_delay);
    OTP_DEINIT_API();
    /* No SFRO enable/disable control in CLKCTL. Just wait SFRO stable in case SFRO just get powered on. */
    SDK_DelayAtLeastUs(sfro_delay, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
}
#endif /* __XTENSA__ */

/* Initialize the SYSTEM PLL Clk */
/*! brief  Initialize the System PLL.
 *  param  config    : Configuration to set to PLL.
 */
void CLOCK_InitSysPll(const clock_sys_pll_config_t *config)
{
    /* Power down SYSPLL before change fractional settings */
    SYSCTL0->PDRUNCFG0_SET = SYSCTL0_PDRUNCFG0_SYSPLLLDO_PD_MASK | SYSCTL0_PDRUNCFG0_SYSPLLANA_PD_MASK;

    CLKCTL0->SYSPLL0CLKSEL = (uint32_t)config->sys_pll_src;
    CLKCTL0->SYSPLL0NUM    = config->numerator;
    CLKCTL0->SYSPLL0DENOM  = config->denominator;
    switch (config->sys_pll_mult)
    {
        case kCLOCK_SysPllMult16:
            CLKCTL0->SYSPLL0CTL0 =
                (CLKCTL0->SYSPLL0CTL0 & ~CLKCTL0_SYSPLL0CTL0_MULT_MASK) | CLKCTL0_SYSPLL0CTL0_MULT(16);
            break;
        case kCLOCK_SysPllMult17:
            CLKCTL0->SYSPLL0CTL0 =
                (CLKCTL0->SYSPLL0CTL0 & ~CLKCTL0_SYSPLL0CTL0_MULT_MASK) | CLKCTL0_SYSPLL0CTL0_MULT(17);
            break;
        case kCLOCK_SysPllMult18:
            CLKCTL0->SYSPLL0CTL0 =
                (CLKCTL0->SYSPLL0CTL0 & ~CLKCTL0_SYSPLL0CTL0_MULT_MASK) | CLKCTL0_SYSPLL0CTL0_MULT(18);
            break;
        case kCLOCK_SysPllMult19:
            CLKCTL0->SYSPLL0CTL0 =
                (CLKCTL0->SYSPLL0CTL0 & ~CLKCTL0_SYSPLL0CTL0_MULT_MASK) | CLKCTL0_SYSPLL0CTL0_MULT(19);
            break;
        case kCLOCK_SysPllMult20:
            CLKCTL0->SYSPLL0CTL0 =
                (CLKCTL0->SYSPLL0CTL0 & ~CLKCTL0_SYSPLL0CTL0_MULT_MASK) | CLKCTL0_SYSPLL0CTL0_MULT(20);
            break;
        case kCLOCK_SysPllMult21:
            CLKCTL0->SYSPLL0CTL0 =
                (CLKCTL0->SYSPLL0CTL0 & ~CLKCTL0_SYSPLL0CTL0_MULT_MASK) | CLKCTL0_SYSPLL0CTL0_MULT(21);
            break;
        case kCLOCK_SysPllMult22:
            CLKCTL0->SYSPLL0CTL0 =
                (CLKCTL0->SYSPLL0CTL0 & ~CLKCTL0_SYSPLL0CTL0_MULT_MASK) | CLKCTL0_SYSPLL0CTL0_MULT(22);
            break;
        default:
            /* Added comments to prevent the violation of MISRA rule. */
            break;
    }
    /* Clear System PLL reset*/
    CLKCTL0->SYSPLL0CTL0 &= ~CLKCTL0_SYSPLL0CTL0_RESET_MASK;
    /* Power up SYSPLL*/
    SYSCTL0->PDRUNCFG0_CLR = SYSCTL0_PDRUNCFG0_SYSPLLLDO_PD_MASK | SYSCTL0_PDRUNCFG0_SYSPLLANA_PD_MASK;
    SDK_DelayAtLeastUs((CLKCTL0->SYSPLL0LOCKTIMEDIV2 & CLKCTL0_SYSPLL0LOCKTIMEDIV2_LOCKTIMEDIV2_MASK) / 2UL,
                       SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    /* Set System PLL HOLDRINGOFF_ENA */
    CLKCTL0->SYSPLL0CTL0 |= CLKCTL0_SYSPLL0CTL0_HOLDRINGOFF_ENA_MASK;
    SDK_DelayAtLeastUs((CLKCTL0->SYSPLL0LOCKTIMEDIV2 & CLKCTL0_SYSPLL0LOCKTIMEDIV2_LOCKTIMEDIV2_MASK) / 6UL,
                       SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    /* Clear System PLL HOLDRINGOFF_ENA*/
    CLKCTL0->SYSPLL0CTL0 &= ~CLKCTL0_SYSPLL0CTL0_HOLDRINGOFF_ENA_MASK;
    SDK_DelayAtLeastUs((CLKCTL0->SYSPLL0LOCKTIMEDIV2 & CLKCTL0_SYSPLL0LOCKTIMEDIV2_LOCKTIMEDIV2_MASK) / 3UL,
                       SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
}
/* Initialize the System PLL PFD */
/*! brief Initialize the System PLL PFD.
 *  param pfd    : Which PFD clock to enable.
 *  param divider    : The PFD divider value.
 *  note It is recommended that PFD settings are kept between 12-35.
 */
void CLOCK_InitSysPfd(clock_pfd_t pfd, uint8_t divider)
{
    uint32_t pfdIndex = (uint32_t)pfd;
    uint32_t syspfd;

    syspfd = CLKCTL0->SYSPLL0PFD &
             ~(((uint32_t)CLKCTL0_SYSPLL0PFD_PFD0_CLKGATE_MASK | (uint32_t)CLKCTL0_SYSPLL0PFD_PFD0_MASK)
               << (8UL * pfdIndex));

    /* Disable the clock output first. */
    CLKCTL0->SYSPLL0PFD = syspfd | ((uint32_t)CLKCTL0_SYSPLL0PFD_PFD0_CLKGATE_MASK << (8UL * pfdIndex));

    /* Set the new value and enable output. */
    CLKCTL0->SYSPLL0PFD = syspfd | (CLKCTL0_SYSPLL0PFD_PFD0(divider) << (8UL * pfdIndex));
    /* Wait for output becomes stable. */
    while ((CLKCTL0->SYSPLL0PFD & ((uint32_t)CLKCTL0_SYSPLL0PFD_PFD0_CLKRDY_MASK << (8UL * pfdIndex))) == 0UL)
    {
    }
    /* Clear ready status flag. */
    CLKCTL0->SYSPLL0PFD |= ((uint32_t)CLKCTL0_SYSPLL0PFD_PFD0_CLKRDY_MASK << (8UL * pfdIndex));
}
/* Initialize the Audio PLL Clk */
/*! brief  Initialize the audio PLL.
 *  param  config    : Configuration to set to PLL.
 */
void CLOCK_InitAudioPll(const clock_audio_pll_config_t *config)
{
    /* Power down Audio PLL before change fractional settings */
    SYSCTL0->PDRUNCFG0_SET = SYSCTL0_PDRUNCFG0_AUDPLLLDO_PD_MASK | SYSCTL0_PDRUNCFG0_AUDPLLANA_PD_MASK;

    CLKCTL1->AUDIOPLL0CLKSEL = (uint32_t)(config->audio_pll_src);
    CLKCTL1->AUDIOPLL0NUM    = config->numerator;
    CLKCTL1->AUDIOPLL0DENOM  = config->denominator;
    switch (config->audio_pll_mult)
    {
        case kCLOCK_AudioPllMult16:
            CLKCTL1->AUDIOPLL0CTL0 =
                (CLKCTL1->AUDIOPLL0CTL0 & ~CLKCTL1_AUDIOPLL0CTL0_MULT_MASK) | CLKCTL1_AUDIOPLL0CTL0_MULT(16);
            break;
        case kCLOCK_AudioPllMult17:
            CLKCTL1->AUDIOPLL0CTL0 =
                (CLKCTL1->AUDIOPLL0CTL0 & ~CLKCTL1_AUDIOPLL0CTL0_MULT_MASK) | CLKCTL1_AUDIOPLL0CTL0_MULT(17);
            break;
        case kCLOCK_AudioPllMult18:
            CLKCTL1->AUDIOPLL0CTL0 =
                (CLKCTL1->AUDIOPLL0CTL0 & ~CLKCTL1_AUDIOPLL0CTL0_MULT_MASK) | CLKCTL1_AUDIOPLL0CTL0_MULT(18);
            break;
        case kCLOCK_AudioPllMult19:
            CLKCTL1->AUDIOPLL0CTL0 =
                (CLKCTL1->AUDIOPLL0CTL0 & ~CLKCTL1_AUDIOPLL0CTL0_MULT_MASK) | CLKCTL1_AUDIOPLL0CTL0_MULT(19);
            break;
        case kCLOCK_AudioPllMult20:
            CLKCTL1->AUDIOPLL0CTL0 =
                (CLKCTL1->AUDIOPLL0CTL0 & ~CLKCTL1_AUDIOPLL0CTL0_MULT_MASK) | CLKCTL1_AUDIOPLL0CTL0_MULT(20);
            break;
        case kCLOCK_AudioPllMult21:
            CLKCTL1->AUDIOPLL0CTL0 =
                (CLKCTL1->AUDIOPLL0CTL0 & ~CLKCTL1_AUDIOPLL0CTL0_MULT_MASK) | CLKCTL1_AUDIOPLL0CTL0_MULT(21);
            break;
        case kCLOCK_AudioPllMult22:
            CLKCTL1->AUDIOPLL0CTL0 =
                (CLKCTL1->AUDIOPLL0CTL0 & ~CLKCTL1_AUDIOPLL0CTL0_MULT_MASK) | CLKCTL1_AUDIOPLL0CTL0_MULT(22);
            break;
        default:
            /* Added comments to prevent the violation of MISRA C-2012 rule */
            break;
    }

    /* Clear Audio PLL reset*/
    CLKCTL1->AUDIOPLL0CTL0 &= ~CLKCTL1_AUDIOPLL0CTL0_RESET_MASK;
    /* Power up Audio PLL*/
    SYSCTL0->PDRUNCFG0_CLR = SYSCTL0_PDRUNCFG0_AUDPLLLDO_PD_MASK | SYSCTL0_PDRUNCFG0_AUDPLLANA_PD_MASK;
    SDK_DelayAtLeastUs((CLKCTL1->AUDIOPLL0LOCKTIMEDIV2 & CLKCTL1_AUDIOPLL0LOCKTIMEDIV2_LOCKTIMEDIV2_MASK) / 2UL,
                       SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    /* Set Audio PLL HOLDRINGOFF_ENA */
    CLKCTL1->AUDIOPLL0CTL0 |= CLKCTL1_AUDIOPLL0CTL0_HOLDRINGOFF_ENA_MASK;
    SDK_DelayAtLeastUs((CLKCTL1->AUDIOPLL0LOCKTIMEDIV2 & CLKCTL1_AUDIOPLL0LOCKTIMEDIV2_LOCKTIMEDIV2_MASK) / 6UL,
                       SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    /* Clear Audio PLL HOLDRINGOFF_ENA*/
    CLKCTL1->AUDIOPLL0CTL0 &= ~CLKCTL1_AUDIOPLL0CTL0_HOLDRINGOFF_ENA_MASK;
    SDK_DelayAtLeastUs((CLKCTL1->AUDIOPLL0LOCKTIMEDIV2 & CLKCTL1_AUDIOPLL0LOCKTIMEDIV2_LOCKTIMEDIV2_MASK) / 3UL,
                       SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
}
/* Initialize the Audio PLL PFD */
/*! brief Initialize the audio PLL PFD.
 *  param pfd    : Which PFD clock to enable.
 *  param divider    : The PFD divider value.
 *  note It is recommended that PFD settings are kept between 12-35.
 */
void CLOCK_InitAudioPfd(clock_pfd_t pfd, uint8_t divider)
{
    uint32_t pfdIndex = (uint32_t)pfd;
    uint32_t syspfd;

    syspfd = CLKCTL1->AUDIOPLL0PFD &
             ~(((uint32_t)CLKCTL1_AUDIOPLL0PFD_PFD0_CLKGATE_MASK | (uint32_t)CLKCTL1_AUDIOPLL0PFD_PFD0_MASK)
               << (8UL * pfdIndex));

    /* Disable the clock output first. */
    CLKCTL1->AUDIOPLL0PFD = syspfd | ((uint32_t)CLKCTL1_AUDIOPLL0PFD_PFD0_CLKGATE_MASK << (8UL * pfdIndex));

    /* Set the new value and enable output. */
    CLKCTL1->AUDIOPLL0PFD = syspfd | (CLKCTL1_AUDIOPLL0PFD_PFD0(divider) << (8UL * pfdIndex));
    /* Wait for output becomes stable. */
    while ((CLKCTL1->AUDIOPLL0PFD & ((uint32_t)CLKCTL1_AUDIOPLL0PFD_PFD0_CLKRDY_MASK << (8UL * pfdIndex))) == 0UL)
    {
    }
    /* Clear ready status flag. */
    CLKCTL1->AUDIOPLL0PFD |= ((uint32_t)CLKCTL1_AUDIOPLL0PFD_PFD0_CLKRDY_MASK << (8UL * pfdIndex));
}
/*! @brief  Enable/Disable sys osc clock from external crystal clock.
 *  @param  enable : true to enable system osc clock, false to bypass system osc.
 *  @param  enableLowPower : true to enable low power mode, false to enable high gain mode.
 *  @param  delay_us : Delay time after OSC power up.
 */
void CLOCK_EnableSysOscClk(bool enable, bool enableLowPower, uint32_t delay_us)
{
    uint32_t ctrl = enableLowPower ? CLKCTL0_SYSOSCCTL0_LP_ENABLE_MASK : 0U;

    if (enable)
    {
        CLKCTL0->SYSOSCCTL0   = ctrl;
        CLKCTL0->SYSOSCBYPASS = 0;
        SDK_DelayAtLeastUs(delay_us, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
    else
    {
        CLKCTL0->SYSOSCCTL0 = ctrl | CLKCTL0_SYSOSCCTL0_BYPASS_ENABLE_MASK;
    }
}
/*! @brief Enable USB HS device clock.
 *
 * This function enables USB HS device clock.
 */
void CLOCK_EnableUsbhsDeviceClock(void)
{
    CLOCK_EnableClock(kCLOCK_UsbhsPhy);
    /* Enable usbhs device and ram clock */
    CLOCK_EnableClock(kCLOCK_UsbhsDevice);
    CLOCK_EnableClock(kCLOCK_UsbhsSram);
}

/*! @brief Enable USB HS host clock.
 *
 * This function enables USB HS host clock.
 */
void CLOCK_EnableUsbhsHostClock(void)
{
    CLOCK_EnableClock(kCLOCK_UsbhsPhy);
    /* Enable usbhs host and ram clock */
    CLOCK_EnableClock(kCLOCK_UsbhsHost);
    CLOCK_EnableClock(kCLOCK_UsbhsSram);
}

/*! brief Enable USB hs0PhyPll clock.
 *
 * param src  USB HS clock source.
 * param freq The frequency specified by src.
 * retval true The clock is set successfully.
 * retval false The clock source is invalid to get proper USB HS clock.
 */
bool CLOCK_EnableUsbHs0PhyPllClock(clock_attach_id_t src, uint32_t freq)
{
    uint32_t phyPllDiv  = 0U;
    uint32_t multiplier = 0U;
    bool retVal         = true;

    USBPHY->CTRL_CLR = USBPHY_CTRL_SFTRST_MASK;

    uint32_t delay = 100000;
    while ((delay--) != 0UL)
    {
        __NOP();
    }

    multiplier = 480000000UL / freq;

    switch (multiplier)
    {
        case 13:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(0U);
            break;
        }
        case 15:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(1U);
            break;
        }
        case 16:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(2U);
            break;
        }
        case 20:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(3U);
            break;
        }
        case 22:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(4U);
            break;
        }
        case 25:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(5U);
            break;
        }
        case 30:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(6U);
            break;
        }
        case 240:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(7U);
            break;
        }
        default:
        {
            retVal = false;
            break;
        }
    }

    if (retVal)
    {
        USBPHY->PLL_SIC_SET = (USBPHY_PLL_SIC_PLL_POWER(1) | USBPHY_PLL_SIC_PLL_REG_ENABLE_MASK);
        USBPHY->PLL_SIC     = (USBPHY->PLL_SIC & ~(USBPHY_PLL_SIC_PLL_DIV_SEL_MASK)) | phyPllDiv;
        USBPHY->PLL_SIC_CLR = USBPHY_PLL_SIC_PLL_BYPASS_MASK;
        USBPHY->PLL_SIC_SET = (USBPHY_PLL_SIC_PLL_EN_USB_CLKS_MASK);

        USBPHY->CTRL_CLR = USBPHY_CTRL_CLR_CLKGATE_MASK;

        while (0UL == (USBPHY->PLL_SIC & USBPHY_PLL_SIC_PLL_LOCK_MASK))
        {
        }
    }

    return retVal;
}

/*
 * Copyright 2018-2021, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_common.h"
#include "fsl_power.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
AT_QUICKACCESS_SECTION_DATA(static uint32_t oscSettlingTime);
AT_QUICKACCESS_SECTION_DATA(static uint32_t pmicVddcoreRecoveryTime);
AT_QUICKACCESS_SECTION_DATA(static uint32_t lvdChangeFlag);
AT_QUICKACCESS_SECTION_DATA(static uint32_t s_pmicCfg);

#define MEGA (1000000U)

static const uint32_t powerLowCm33FreqLevel[2][3] = {
    /* For part 0C - 85C */
    {220U * MEGA, 150U * MEGA, 70U * MEGA},
    /* For part -20C - 85C */
    {215U * MEGA, 140U * MEGA, 60U * MEGA}};

static const uint32_t powerLowDspFreqLevel[2][3] = {
    /* For part 0C - 85C */
    {375U * MEGA, 260U * MEGA, 115U * MEGA},
    /* For part -20C - 85C */
    {355U * MEGA, 235U * MEGA, 95U * MEGA}};

static const uint32_t powerFullCm33FreqLevel[2][5] = {
    /* For part 0C - 85C */
    {300U * MEGA, 275U * MEGA, 210U * MEGA, 140U * MEGA, 65U * MEGA},
    /* For part -20C - 85C */
    {300U * MEGA, 270U * MEGA, 200U * MEGA, 135U * MEGA, 50U * MEGA}};

static const uint32_t powerFullDspFreqLevel[2][5] = {
    /* For part 0C - 85C */
    {600U * MEGA, 480U * MEGA, 300U * MEGA, 195U * MEGA, 70U * MEGA},
    /* For part -20C - 85C */
    {550U * MEGA, 440U * MEGA, 285U * MEGA, 170U * MEGA, 55U * MEGA}};

static const uint32_t powerLdoVoltLevel[5] = {
    0x32U, /* 1.13V */
    0x26U, /* 1.0V */
    0x1DU, /* 0.9V */
    0x13U, /* 0.8V */
    0x0AU, /* 0.7V */
};

static const uint32_t powerLdoMilliVolt[5] = {
    1130U, /* 1.13V */
    1000U, /* 1.0V */
    900U,  /* 0.9V */
    800U,  /* 0.8V */
    700U,  /* 0.7V */
};

static power_vddcore_src_t vddCoreSrc;
static power_vddcore_set_func_t vddCoreSetCb = NULL;

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.power"
#endif

/* Default configuring PMC to respond changes on pdruncfg[2:1] (PMIC mode select pin values) like below:
 *  0b00    run mode, all supplies on.
 *  0b01    deep sleep mode, all supplies on.
 *  0b10    deep powerdown mode, vddcore off.
 *  0b11    full deep powerdown mode vdd1v8 and vddcore off. */
#define PMICCFG_DEFAULT_VALUE (0x73U)

#define PCFG0_XBB_MASK (SYSCTL0_PDSLEEPCFG0_RBB_PD_MASK | SYSCTL0_PDSLEEPCFG0_FBB_PD_MASK)

/* DeepSleep PDSLEEP0 */
#define PCFG0_DEEP_SLEEP                                                                                             \
    (SYSCTL0_PDSLEEPCFG0_MAINCLK_SHUTOFF_MASK | SYSCTL0_PDSLEEPCFG0_VDDCOREREG_LP_MASK |                             \
     SYSCTL0_PDSLEEPCFG0_PMCREF_LP_MASK | SYSCTL0_PDSLEEPCFG0_HVD1V8_PD_MASK | SYSCTL0_PDSLEEPCFG0_PORCORE_LP_MASK | \
     SYSCTL0_PDSLEEPCFG0_LVDCORE_LP_MASK | SYSCTL0_PDSLEEPCFG0_HVDCORE_PD_MASK | SYSCTL0_PDSLEEPCFG0_RBB_PD_MASK |   \
     SYSCTL0_PDSLEEPCFG0_FBB_PD_MASK | SYSCTL0_PDSLEEPCFG0_SYSXTAL_PD_MASK | SYSCTL0_PDSLEEPCFG0_LPOSC_PD_MASK |     \
     SYSCTL0_PDSLEEPCFG0_SFRO_PD_MASK | SYSCTL0_PDSLEEPCFG0_FFRO_PD_MASK | SYSCTL0_PDSLEEPCFG0_SYSPLLLDO_PD_MASK |   \
     SYSCTL0_PDSLEEPCFG0_SYSPLLANA_PD_MASK | SYSCTL0_PDSLEEPCFG0_AUDPLLLDO_PD_MASK |                                 \
     SYSCTL0_PDSLEEPCFG0_AUDPLLANA_PD_MASK | SYSCTL0_PDSLEEPCFG0_ADC_PD_MASK | SYSCTL0_PDSLEEPCFG0_ADC_LP_MASK |     \
     SYSCTL0_PDSLEEPCFG0_ADCTEMPSNS_PD_MASK | SYSCTL0_PDSLEEPCFG0_ACMP_PD_MASK |                                     \
     SYSCTL0_PDSLEEPCFG0_HSPAD0_VDET_LP_MASK | SYSCTL0_PDSLEEPCFG0_HSPAD0_REF_PD_MASK |                              \
     SYSCTL0_PDSLEEPCFG0_HSPAD2_VDET_LP_MASK | SYSCTL0_PDSLEEPCFG0_HSPAD2_REF_PD_MASK)

/* DeepSleep PDSLEEP1 */
#define PCFG1_DEEP_SLEEP                                                                       \
    (SYSCTL0_PDSLEEPCFG1_PQ_SRAM_APD_MASK | SYSCTL0_PDSLEEPCFG1_PQ_SRAM_PPD_MASK |             \
     SYSCTL0_PDSLEEPCFG1_FLEXSPI_SRAM_APD_MASK | SYSCTL0_PDSLEEPCFG1_FLEXSPI_SRAM_PPD_MASK |   \
     SYSCTL0_PDSLEEPCFG1_USBHS_SRAM_APD_MASK | SYSCTL0_PDSLEEPCFG1_USBHS_SRAM_PPD_MASK |       \
     SYSCTL0_PDSLEEPCFG1_USDHC0_SRAM_APD_MASK | SYSCTL0_PDSLEEPCFG1_USDHC0_SRAM_PPD_MASK |     \
     SYSCTL0_PDSLEEPCFG1_USDHC1_SRAM_APD_MASK | SYSCTL0_PDSLEEPCFG1_USDHC1_SRAM_PPD_MASK |     \
     SYSCTL0_PDSLEEPCFG1_CASPER_SRAM_APD_MASK | SYSCTL0_PDSLEEPCFG1_CASPER_SRAM_PPD_MASK |     \
     SYSCTL0_PDSLEEPCFG1_DSPCACHE_REGF_APD_MASK | SYSCTL0_PDSLEEPCFG1_DSPCACHE_REGF_PPD_MASK | \
     SYSCTL0_PDSLEEPCFG1_DSPTCM_REGF_APD_MASK | SYSCTL0_PDSLEEPCFG1_DSPTCM_REGF_PPD_MASK |     \
     SYSCTL0_PDSLEEPCFG1_ROM_PD_MASK | SYSCTL0_PDSLEEPCFG1_SRAM_SLEEP_MASK)

/* DeepSleep PDSLEEP2 */
#define PCFG2_DEEP_SLEEP 0x3FFFFFFFU

/* DeepSleep PDSLEEP3 */
#define PCFG3_DEEP_SLEEP 0x3FFFFFFFU

/*System PLL PFD mask*/
#define SYSPLL0PFD_PFD_MASK                                                                       \
    (CLKCTL0_SYSPLL0PFD_PFD0_MASK | CLKCTL0_SYSPLL0PFD_PFD1_MASK | CLKCTL0_SYSPLL0PFD_PFD2_MASK | \
     CLKCTL0_SYSPLL0PFD_PFD3_MASK)
#define SYSPLL0PFD_PFD_CLKRDY_MASK                                                                                     \
    (CLKCTL0_SYSPLL0PFD_PFD0_CLKRDY_MASK | CLKCTL0_SYSPLL0PFD_PFD1_CLKRDY_MASK | CLKCTL0_SYSPLL0PFD_PFD2_CLKRDY_MASK | \
     CLKCTL0_SYSPLL0PFD_PFD3_CLKRDY_MASK)
#define SYSPLL0PFD_PFD_CLKGATE_MASK                                                \
    (CLKCTL0_SYSPLL0PFD_PFD0_CLKGATE_MASK | CLKCTL0_SYSPLL0PFD_PFD1_CLKGATE_MASK | \
     CLKCTL0_SYSPLL0PFD_PFD2_CLKGATE_MASK | CLKCTL0_SYSPLL0PFD_PFD3_CLKGATE_MASK)

/*Audio PLL PFD mask*/
#define AUDIOPLL0PFD_PFD_MASK                                                                           \
    (CLKCTL1_AUDIOPLL0PFD_PFD0_MASK | CLKCTL1_AUDIOPLL0PFD_PFD1_MASK | CLKCTL1_AUDIOPLL0PFD_PFD2_MASK | \
     CLKCTL1_AUDIOPLL0PFD_PFD3_MASK)
#define AUDIOPLL0PFD_PFD_CLKRDY_MASK                                                 \
    (CLKCTL1_AUDIOPLL0PFD_PFD0_CLKRDY_MASK | CLKCTL1_AUDIOPLL0PFD_PFD1_CLKRDY_MASK | \
     CLKCTL1_AUDIOPLL0PFD_PFD2_CLKRDY_MASK | CLKCTL1_AUDIOPLL0PFD_PFD3_CLKRDY_MASK)
#define AUDIOPLL0PFD_PFD_CLKGATE_MASK                                                  \
    (CLKCTL1_AUDIOPLL0PFD_PFD0_CLKGATE_MASK | CLKCTL1_AUDIOPLL0PFD_PFD1_CLKGATE_MASK | \
     CLKCTL1_AUDIOPLL0PFD_PFD2_CLKGATE_MASK | CLKCTL1_AUDIOPLL0PFD_PFD3_CLKGATE_MASK)

#define IS_SYSPLL_ON(pdruncfg) \
    (((pdruncfg) & (SYSCTL0_PDRUNCFG0_SYSPLLLDO_PD_MASK | SYSCTL0_PDRUNCFG0_SYSPLLANA_PD_MASK)) == 0U)
#define IS_AUDPLL_ON(pdruncfg) \
    (((pdruncfg) & (SYSCTL0_PDRUNCFG0_AUDPLLLDO_PD_MASK | SYSCTL0_PDRUNCFG0_AUDPLLANA_PD_MASK)) == 0U)

/* CPU running at 12 or 15 MHz, max 15 instructions per us, each loop includes 4 instructions. max 4 loops per us. */
#define US2LOOP(x) ((x) * ((CLKCTL0->FFROCTL0 & CLKCTL0_FFROCTL0_TRIM_RANGE_MASK) == 0U ? 3U : 4U))
/* Calculate the microsecond period with the maximum CPU frequency 300MHz. */
#define US2FASTLOOP(x) ((x)*300U / 4U)

#define IS_XIP_FLEXSPI()                                                                      \
    ((((uint32_t)POWER_ApplyPD >= 0x08000000U) && ((uint32_t)POWER_ApplyPD < 0x10000000U)) || \
     (((uint32_t)POWER_ApplyPD >= 0x18000000U) && ((uint32_t)POWER_ApplyPD < 0x20000000U)))
#define FLEXSPI_DLL_LOCK_RETRY (10U)

#define PMC_DECREASE_LVD_LEVEL_IF_HIGHER_THAN(level)                                                     \
    do                                                                                                   \
    {                                                                                                    \
        if (((PMC->LVDCORECTRL & PMC_LVDCORECTRL_LVDCORELVL_MASK) >> PMC_LVDCORECTRL_LVDCORELVL_SHIFT) > \
            ((uint32_t)(level)))                                                                         \
        {                                                                                                \
            PMC->LVDCORECTRL = PMC_LVDCORECTRL_LVDCORELVL(kLvdFallingTripVol_720);                       \
        }                                                                                                \
    } while (false)

#define PMC_REG(off) (*((volatile uint32_t *)(void *)PMC + (off) / 4))

#define PMU_MIN_CLOCK_MHZ (13U)
/* Turn on all partitions in parallel.
 * Be cautious to change the PMC_MEM_SEQ_NUM. To save code size, countPartitionSwitches() counted with 0x3F.
 */
#define PMC_MEM_SEQ_NUM                 (0x3FU)
#define SYSCTL0_PDRUNCFG1_MEM_BITS_MASK (0x1F000FFFU)
#define SYSCTL0_PDRUNCFG2_BITS_MASK     (0x3FFFFFFFU)
#define SYSCTL0_PDRUNCFG3_BITS_MASK     (0x3FFFFFFFU)

/*! Invalid voltage level. */
#define POWER_INVALID_VOLT_LEVEL (0xFFFFFFFFU)
/*******************************************************************************
 * Codes
 ******************************************************************************/
void POWER_PmicPowerModeSelectControl(uint32_t vddSelect)
{
    /* VDD1V8M0 and VDDCOREM0 is expected to be 1 during active mode otherwise a POR will be triggered. */
    s_pmicCfg = vddSelect | 0x11U;
}

/*!
 * @brief Configure bias voltage level and enable/disable pull-down.
 *
 * This function change the RBB&FBB voltage level and RBB pull-down.
 */
AT_QUICKACCESS_SECTION_CODE(static void POWER_SetBiasConfig(void))
{
    if (PMC_REG(0x20) != 0x04040808U)
    {
        PMC_REG(0x20) = 0x04040808U;
    }
    if (PMC->SLEEPCTRL != PMC_SLEEPCTRL_CORELVL(0xA))
    {
        /* Deep sleep core voltage 0.7V */
        PMC->SLEEPCTRL = PMC_SLEEPCTRL_CORELVL(0xA);
    }
}

static uint32_t POWER_CalcVoltLevel(const uint32_t *freqLevels, uint32_t num, uint32_t freq, uint32_t mini_volt)
{
    uint32_t i;
    uint32_t index;

    mini_volt = mini_volt < 700U ? 700U : mini_volt;

    for (i = 0U; i < num; i++)
    {
        if ((freq > freqLevels[i]) || (powerLdoMilliVolt[i + ARRAY_SIZE(powerLdoVoltLevel) - num] < mini_volt))
        {
            break;
        }
    }

    if (i == 0U) /* Frequency exceed max supported */
    {
        index = POWER_INVALID_VOLT_LEVEL;
    }
    else
    {
        index = i + ARRAY_SIZE(powerLdoVoltLevel) - num - 1U;
    }

    return index;
}

void POWER_DisableLVD(void)
{
    if ((PMC->CTRL & (PMC_CTRL_LVDCORERE_MASK | PMC_CTRL_LVDCOREIE_MASK)) != 0U)
    {
        lvdChangeFlag = PMC->CTRL & (PMC_CTRL_LVDCORERE_MASK | PMC_CTRL_LVDCOREIE_MASK);
        PMC->CTRL &= ~(PMC_CTRL_LVDCORERE_MASK | PMC_CTRL_LVDCOREIE_MASK);
    }
}

void POWER_RestoreLVD(void)
{
    PMC->CTRL |= lvdChangeFlag & (PMC_CTRL_LVDCORERE_MASK | PMC_CTRL_LVDCOREIE_MASK);
    lvdChangeFlag = 0;
}

/**
 * @brief  API to update XTAL oscillator settling time .
 * @param  osc_delay : OSC stabilization time in unit of microsecond
 */
void POWER_UpdateOscSettlingTime(uint32_t osc_delay)
{
    oscSettlingTime = osc_delay;
}

/**
 * @brief  API to update on-board PMIC vddcore recovery time.
 * @param  pmic_delay : PMIC stabilization time in unit of microsecond
 */
void POWER_UpdatePmicRecoveryTime(uint32_t pmic_delay)
{
    pmicVddcoreRecoveryTime = pmic_delay;
}

/**
 * @brief  API to apply updated PMC PDRUNCFG bits in the Sysctl0.
 */
void POWER_ApplyPD(void)
{
    /* Cannot set APPLYCFG when ACTIVEFSM is 1 */
    while ((PMC->STATUS & PMC_STATUS_ACTIVEFSM_MASK) != 0U)
    {
    }
    PMC->CTRL |= PMC_CTRL_APPLYCFG_MASK;
    /* Wait all PMC finite state machines finished. */
    while ((PMC->STATUS & PMC_STATUS_ACTIVEFSM_MASK) != 0U)
    {
    }
}

/**
 * @brief   Clears the PMC event flags state.
 * @param   statusMask : A bitmask of event flags that are to be cleared.
 */
void POWER_ClearEventFlags(uint32_t statusMask)
{
    PMC->FLAGS = statusMask;
}

/**
 * @brief   Get the PMC event flags state.
 * @return  PMC FLAGS register value
 */
uint32_t POWER_GetEventFlags(void)
{
    return PMC->FLAGS;
}

/**
 * @brief   Enable the PMC interrupt requests.
 * @param   interruptMask : A bitmask of of interrupts to enable.
 */
void POWER_EnableInterrupts(uint32_t interruptMask)
{
    PMC->CTRL |= interruptMask;
}

/**
 * @brief   Disable the PMC interrupt requests.
 * @param   interruptMask : A bitmask of of interrupts to disable.
 */
void POWER_DisableInterrupts(uint32_t interruptMask)
{
    PMC->CTRL &= ~interruptMask;
}

/**
 * @brief   Set the PMC analog buffer for references or ATX2.
 * @param   enable : Set true to enable analog buffer for references or ATX2, false to disable.
 */
void POWER_SetAnalogBuffer(bool enable)
{
    if (enable)
    {
        PMC->CTRL |= PMC_CTRL_BUFEN_MASK;
    }
    else
    {
        PMC->CTRL &= ~PMC_CTRL_BUFEN_MASK;
    }
}

/*!
 * @brief Configure pad voltage level. Wide voltage range cost more power due to enabled voltage detector.
 *
 * NOTE: BE CAUTIOUS TO CALL THIS API. IF THE PAD SUPPLY IS BEYOND THE SET RANGE, SILICON MIGHT BE DAMAGED.
 *
 * @param config pad voltage range configuration.
 */
void POWER_SetPadVolRange(const power_pad_vrange_t *config)
{
    PMC->PADVRANGE = (*((const uint32_t *)(const void *)config)) & 0x3FU;
}

/**
 * @brief    PMC Enter Rbb mode function call
 * @return   nothing
 */

void POWER_EnterRbb(void)
{
    uint32_t pmsk;
    bool irqEnabled;
    uint32_t pmc_ctrl;
    pmsk = __get_PRIMASK();
    __disable_irq();
    POWER_SetBiasConfig();
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    irqEnabled = NVIC_GetEnableIRQ(PMC_PMIC_IRQn) != 0U;
    /* MAINCLK_SHUTOFF=1, RBB_PD=0 */
    SYSCTL0->PDSLEEPCFG0 =
        (SYSCTL0->PDRUNCFG0 | SYSCTL0_PDSLEEPCFG0_MAINCLK_SHUTOFF_MASK) & ~SYSCTL0_PDSLEEPCFG0_RBB_PD_MASK;
    SYSCTL0->PDSLEEPCFG1 = SYSCTL0->PDRUNCFG1;
    SYSCTL0->PDSLEEPCFG2 = SYSCTL0->PDRUNCFG2;
    SYSCTL0->PDSLEEPCFG3 = SYSCTL0->PDRUNCFG3;
    SYSCTL0->PDWAKECFG   = SYSCTL0_PDWAKECFG_RBBKEEPST_MASK;
    /* Add PMC count delay before auto wakeup (clocked by the PMC 16MHz oscillator) */
    PMC->AUTOWKUP = 0x800;
    /* Disable LVD core reset and eanbel PMC auto wakeup interrupt */
    pmc_ctrl              = PMC->CTRL;
    PMC->CTRL             = (pmc_ctrl | PMC_CTRL_AUTOWKEN_MASK) & ~(PMC_CTRL_LVDCORERE_MASK | PMC_CTRL_LVDCOREIE_MASK);
    SYSCTL0->STARTEN1_SET = 1UL << ((uint32_t)PMC_PMIC_IRQn - 32U);
    if (!irqEnabled)
    {
        NVIC_EnableIRQ(PMC_PMIC_IRQn);
    }
    __WFI();
    /* Restore PMC setting, clear interrupt flag */
    PMC->CTRL             = pmc_ctrl;
    PMC->FLAGS            = PMC_FLAGS_AUTOWKF_MASK;
    SYSCTL0->STARTEN1_CLR = 1UL << ((uint32_t)PMC_PMIC_IRQn - 32U);
    SYSCTL0->PDWAKECFG    = 0;
    NVIC_ClearPendingIRQ(PMC_PMIC_IRQn);
    if (!irqEnabled)
    {
        /* Recover NVIC state. */
        NVIC_DisableIRQ(PMC_PMIC_IRQn);
    }
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    __set_PRIMASK(pmsk);
}
/**
 * @brief    PMC Enter Fbb mode function call
 * @return   nothing
 */

void POWER_EnterFbb(void)
{
    uint32_t pmsk;
    bool irqEnabled;
    uint32_t pmc_ctrl;
    pmsk = __get_PRIMASK();
    __disable_irq();
    POWER_SetBiasConfig();
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    irqEnabled = NVIC_GetEnableIRQ(PMC_PMIC_IRQn) != 0U;
    /* MAINCLK_SHUTOFF=1, FBB_PD=0 */
    SYSCTL0->PDSLEEPCFG0 =
        (SYSCTL0->PDRUNCFG0 | SYSCTL0_PDSLEEPCFG0_MAINCLK_SHUTOFF_MASK) & ~SYSCTL0_PDSLEEPCFG0_FBB_PD_MASK;
    SYSCTL0->PDSLEEPCFG1 = SYSCTL0->PDRUNCFG1;
    SYSCTL0->PDSLEEPCFG2 = SYSCTL0->PDRUNCFG2;
    SYSCTL0->PDSLEEPCFG3 = SYSCTL0->PDRUNCFG3;
    SYSCTL0->PDWAKECFG   = SYSCTL0_PDWAKECFG_FBBKEEPST_MASK;
    /* Add PMC count delay before auto wakeup (clocked by the PMC 16MHz oscillator) */
    PMC->AUTOWKUP = 0x800;
    /* Disable LVD core reset and eanbel PMC auto wakeup interrupt */
    pmc_ctrl              = PMC->CTRL;
    PMC->CTRL             = (pmc_ctrl | PMC_CTRL_AUTOWKEN_MASK) & ~(PMC_CTRL_LVDCORERE_MASK | PMC_CTRL_LVDCOREIE_MASK);
    SYSCTL0->STARTEN1_SET = 1UL << ((uint32_t)PMC_PMIC_IRQn - 32U);
    if (!irqEnabled)
    {
        NVIC_EnableIRQ(PMC_PMIC_IRQn);
    }
    __WFI();
    /* Restore PMC setting, clear interrupt flag */
    PMC->CTRL             = pmc_ctrl;
    PMC->FLAGS            = PMC_FLAGS_AUTOWKF_MASK;
    SYSCTL0->STARTEN1_CLR = 1UL << ((uint32_t)PMC_PMIC_IRQn - 32U);
    SYSCTL0->PDWAKECFG    = 0;
    NVIC_ClearPendingIRQ(PMC_PMIC_IRQn);
    if (!irqEnabled)
    {
        /* Recover NVIC state. */
        NVIC_DisableIRQ(PMC_PMIC_IRQn);
    }
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    __set_PRIMASK(pmsk);
}
/**
 * @brief    PMC exit Rbb & Fbb mode function call
 * @return   nothing
 */

void POWER_EnterNbb(void)
{
    uint32_t pmsk;
    bool irqEnabled;
    uint32_t pmc_ctrl;
    pmsk = __get_PRIMASK();
    __disable_irq();
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    irqEnabled = NVIC_GetEnableIRQ(PMC_PMIC_IRQn) != 0U;
    /* MAINCLK_SHUTOFF=1, RBB_PD=1 FBB_PD=1 */
    SYSCTL0->PDSLEEPCFG0 = SYSCTL0->PDRUNCFG0 | SYSCTL0_PDSLEEPCFG0_MAINCLK_SHUTOFF_MASK |
                           SYSCTL0_PDSLEEPCFG0_RBB_PD_MASK | SYSCTL0_PDSLEEPCFG0_FBB_PD_MASK;
    SYSCTL0->PDSLEEPCFG1 = SYSCTL0->PDRUNCFG1;
    SYSCTL0->PDSLEEPCFG2 = SYSCTL0->PDRUNCFG2;
    SYSCTL0->PDSLEEPCFG3 = SYSCTL0->PDRUNCFG3;
    SYSCTL0->PDWAKECFG   = SYSCTL0_PDWAKECFG_RBBKEEPST_MASK | SYSCTL0_PDWAKECFG_FBBKEEPST_MASK;
    /* Add PMC count delay before auto wakeup (clocked by the PMC 16MHz oscillator) */
    PMC->AUTOWKUP = 0x800;
    /* Disable LVD core reset and eanbel PMC auto wakeup interrupt */
    pmc_ctrl              = PMC->CTRL;
    PMC->CTRL             = (pmc_ctrl | PMC_CTRL_AUTOWKEN_MASK) & ~(PMC_CTRL_LVDCORERE_MASK | PMC_CTRL_LVDCOREIE_MASK);
    SYSCTL0->STARTEN1_SET = 1UL << ((uint32_t)PMC_PMIC_IRQn - 32U);
    if (!irqEnabled)
    {
        NVIC_EnableIRQ(PMC_PMIC_IRQn);
    }
    __WFI();
    /* Restore PMC setting, clear interrupt flag */
    PMC->CTRL             = pmc_ctrl;
    PMC->FLAGS            = PMC_FLAGS_AUTOWKF_MASK;
    SYSCTL0->STARTEN1_CLR = 1UL << ((uint32_t)PMC_PMIC_IRQn - 32U);
    SYSCTL0->PDWAKECFG    = 0;
    NVIC_ClearPendingIRQ(PMC_PMIC_IRQn);
    if (!irqEnabled)
    {
        /* Recover NVIC state. */
        NVIC_DisableIRQ(PMC_PMIC_IRQn);
    }
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    __set_PRIMASK(pmsk);
}

/**
 * @brief    PMC set Ldo volatage function call
 * @return   true for success.
 */
bool POWER_SetLdoVoltageForFreq(power_part_temp_range_t tempRange,
                                power_volt_op_range_t voltOpRange,
                                uint32_t cm33Freq,
                                uint32_t dspFreq)
{
    if (vddCoreSrc == kVddCoreSrc_LDO)
    {
        return POWER_SetVoltageForFreq(tempRange, voltOpRange, cm33Freq, dspFreq, 0U);
    }
    else
    {
        return false;
    }
}

void POWER_SetVddCoreSupplySrc(power_vddcore_src_t src)
{
    vddCoreSrc = src;
}

void POWER_SetPmicCoreSupplyFunc(power_vddcore_set_func_t func)
{
    vddCoreSetCb = func;
}

bool POWER_SetVoltageForFreq(power_part_temp_range_t tempRange,
                             power_volt_op_range_t voltOpRange,
                             uint32_t cm33Freq,
                             uint32_t dspFreq,
                             uint32_t mini_volt)
{
    uint32_t pmsk;
    uint32_t idx = (uint32_t)tempRange;
    uint32_t cm33VoltIdx, dspVoltIdx, voltIdx;
    bool ret;

    pmsk = __get_PRIMASK();

    if (vddCoreSrc == kVddCoreSrc_LDO)
    {
        __disable_irq();
    }

    /* Enter FBB mode first */
    if (POWER_GetBodyBiasMode(kCfg_Run) != kPmu_Fbb)
    {
        POWER_EnterFbb();
    }

    if (voltOpRange == kVoltOpLowRange)
    {
        cm33VoltIdx = POWER_CalcVoltLevel(&powerLowCm33FreqLevel[idx][0], 3U, cm33Freq, mini_volt);
        dspVoltIdx  = POWER_CalcVoltLevel(&powerLowDspFreqLevel[idx][0], 3U, dspFreq, mini_volt);
    }
    else
    {
        cm33VoltIdx = POWER_CalcVoltLevel(&powerFullCm33FreqLevel[idx][0], 5U, cm33Freq, mini_volt);
        dspVoltIdx  = POWER_CalcVoltLevel(&powerFullDspFreqLevel[idx][0], 5U, dspFreq, mini_volt);
    }
    voltIdx = MIN(cm33VoltIdx, dspVoltIdx);
    ret     = voltIdx < ARRAY_SIZE(powerLdoVoltLevel);

    if (ret)
    {
        if (powerLdoVoltLevel[voltIdx] < 0x13U) /* < 0.8V */
        {
            POWER_DisableLVD();
        }
        else
        {
            if (powerLdoVoltLevel[voltIdx] < 0x1DU) /* < 0.9V */
            {
                PMC_DECREASE_LVD_LEVEL_IF_HIGHER_THAN(kLvdFallingTripVol_795);
            }
            else if (powerLdoVoltLevel[voltIdx] < 0x26U) /* < 1.0V */
            {
                PMC_DECREASE_LVD_LEVEL_IF_HIGHER_THAN(kLvdFallingTripVol_885);
            }
            else
            {
                /* Do nothing */
            }
        }

        if (vddCoreSrc == kVddCoreSrc_LDO)
        {
            /* Configure vddcore voltage value */
            PMC->RUNCTRL = powerLdoVoltLevel[voltIdx];
            POWER_ApplyPD();
        }
        else
        {
            if (vddCoreSetCb != NULL)
            {
                /* Call PMIC callback function to set VDDCORE. */
                vddCoreSetCb(powerLdoMilliVolt[voltIdx]);
            }
            else
            {
                ret = false;
            }
        }

        if (powerLdoVoltLevel[voltIdx] >= 0x13U) /* >= 0.8V */
        {
            POWER_RestoreLVD();
        }
    }

    if (vddCoreSrc == kVddCoreSrc_LDO)
    {
        __set_PRIMASK(pmsk);
    }

    return ret;
}

void POWER_SetLvdFallingTripVoltage(power_lvd_falling_trip_vol_val_t volt)
{
    PMC->LVDCORECTRL = PMC_LVDCORECTRL_LVDCORELVL(volt);
    POWER_ApplyPD();
}

power_lvd_falling_trip_vol_val_t POWER_GetLvdFallingTripVoltage(void)
{
    return (power_lvd_falling_trip_vol_val_t)(uint32_t)((PMC->LVDCORECTRL & PMC_LVDCORECTRL_LVDCORELVL_MASK) >>
                                                        PMC_LVDCORECTRL_LVDCORELVL_SHIFT);
}

AT_QUICKACCESS_SECTION_CODE(static void delay(uint32_t count))
{
    uint32_t i = 0U;
    for (i = 0U; i < count; ++i)
    {
        __NOP();
    }
}

AT_QUICKACCESS_SECTION_CODE(static void deinitXip(void))
{
    if (IS_XIP_FLEXSPI())
    { /* FlexSPI */
        /* Wait until FLEXSPI is not busy */
        while (!(((FLEXSPI->STS0 & FLEXSPI_STS0_ARBIDLE_MASK) != 0U) &&
                 ((FLEXSPI->STS0 & FLEXSPI_STS0_SEQIDLE_MASK) != 0U)))
        {
        }
        /* Disable module. */
        FLEXSPI->MCR0 |= FLEXSPI_MCR0_MDIS_MASK;
        /* Disable clock. */
        CLKCTL0->PSCCTL0_CLR = CLKCTL0_PSCCTL0_CLR_FLEXSPI_OTFAD_CLK_MASK;
    }
}

AT_QUICKACCESS_SECTION_CODE(static void initFlexSPI(FLEXSPI_Type *base))
{
    uint32_t status;
    uint32_t lastStatus;
    uint32_t retry;
    uint32_t mask = 0;

    /* Enable FLEXSPI module */
    base->MCR0 &= ~FLEXSPI_MCR0_MDIS_MASK;

    base->MCR0 |= FLEXSPI_MCR0_SWRESET_MASK;
    while ((base->MCR0 & FLEXSPI_MCR0_SWRESET_MASK) != 0U)
    {
    }

    /* Need to wait DLL locked if DLL enabled */
    if (0U != (base->DLLCR[0] & FLEXSPI_DLLCR_DLLEN_MASK))
    {
        lastStatus = base->STS2;
        retry      = FLEXSPI_DLL_LOCK_RETRY;
        /* Flash on port A */
        if (((base->FLSHCR0[0] & FLEXSPI_FLSHCR0_FLSHSZ_MASK) > 0U) ||
            ((base->FLSHCR0[1] & FLEXSPI_FLSHCR0_FLSHSZ_MASK) > 0U))
        {
            mask |= FLEXSPI_STS2_AREFLOCK_MASK | FLEXSPI_STS2_ASLVLOCK_MASK;
        }
        /* Flash on port B */
        if (((base->FLSHCR0[2] & FLEXSPI_FLSHCR0_FLSHSZ_MASK) > 0U) ||
            ((base->FLSHCR0[3] & FLEXSPI_FLSHCR0_FLSHSZ_MASK) > 0U))
        {
            mask |= FLEXSPI_STS2_BREFLOCK_MASK | FLEXSPI_STS2_BSLVLOCK_MASK;
        }
        /* Wait slave delay line locked and slave reference delay line locked. */
        do
        {
            status = base->STS2;
            if ((status & mask) == mask)
            {
                /* Locked */
                retry = 100;
                break;
            }
            else if (status == lastStatus)
            {
                /* Same delay cell number in calibration */
                retry--;
            }
            else
            {
                retry      = FLEXSPI_DLL_LOCK_RETRY;
                lastStatus = status;
            }
        } while (retry > 0U);
        /* According to ERR011377, need to delay at least 100 NOPs to ensure the DLL is locked. */
        for (; retry > 0U; retry--)
        {
            __NOP();
        }
    }
}

AT_QUICKACCESS_SECTION_CODE(static void initXip(void))
{
    if (IS_XIP_FLEXSPI())
    { /* FlexSPI */
        /* Enable FLEXSPI clock again */
        CLKCTL0->PSCCTL0_SET = CLKCTL0_PSCCTL0_SET_FLEXSPI_OTFAD_CLK_MASK;
        /* Re-enable FLEXSPI module */
        initFlexSPI(FLEXSPI);
    }
}

AT_QUICKACCESS_SECTION_CODE(static uint32_t countPartitionSwitches(uint32_t numPerSwitch))
{
    (void)numPerSwitch;

    /* Find if there's memory is powered on in PDRUNCFGn but powered down in PDSLEEPCFGn */
    if ((((SYSCTL0->PDRUNCFG1 ^ SYSCTL0_PDRUNCFG1_MEM_BITS_MASK) &
          (SYSCTL0->PDSLEEPCFG1 & SYSCTL0_PDRUNCFG1_MEM_BITS_MASK)) != 0U) ||
        (((SYSCTL0->PDRUNCFG2 ^ SYSCTL0_PDRUNCFG2_BITS_MASK) & (SYSCTL0->PDSLEEPCFG2 & SYSCTL0_PDRUNCFG2_BITS_MASK)) !=
         0U) ||
        (((SYSCTL0->PDRUNCFG3 ^ SYSCTL0_PDRUNCFG3_BITS_MASK) & (SYSCTL0->PDSLEEPCFG3 & SYSCTL0_PDRUNCFG3_BITS_MASK)) !=
         0U))
    {
        /* All partitions are turned on in parallel */
        return 1U;
    }
    else
    {
        /* No partition power change */
        return 0U;
    };
}

AT_QUICKACCESS_SECTION_CODE(static uint32_t POWER_CalculateSafetyCount(void))
{
    uint32_t ns = 0U;
    bool flag;
    uint32_t temp, groups, switches;

    ns += 200U;                      /* PMU clock startup */
    ns += 2000U / PMU_MIN_CLOCK_MHZ; /* Wakeup sync */
    ns += 1000U / PMU_MIN_CLOCK_MHZ; /* Senquencer start */
    /* Bandgap to HP mode */
    flag = ((SYSCTL0->PDSLEEPCFG0 & 0x10017D0U) == 0x10017D0U);
    ns += (flag ? 7000UL : 1000UL) / PMU_MIN_CLOCK_MHZ + (flag ? 9000UL : 0UL);

    if (pmicVddcoreRecoveryTime == 0U)
    {
        /* Application uses internal LDO */
        flag = (SYSCTL0->PDSLEEPCFG0 & 0x10U) == 0x10U;
        ns += (flag ? 47000UL : 1000UL) / PMU_MIN_CLOCK_MHZ + (flag ? 1000UL : 0UL); /* Core Regulator LP to HP */
        switches = (PMC->RUNCTRL & PMC_RUNCTRL_CORELVL_MASK) - (PMC->SLEEPCTRL & PMC_SLEEPCTRL_CORELVL_MASK);
        ns += (switches * 32000U + 1000U) / PMU_MIN_CLOCK_MHZ + switches * 600U; /* Core Regulator Voltage adj */
        ns += ((SYSCTL0->PDRUNCFG0 & 0x10U) == 0x10U ? 43000UL : 1000UL) / PMU_MIN_CLOCK_MHZ; /* Core Regulator mode */
    }
    else
    {
        /* Application uses on-board PMIC */
        ns += 2000U / PMU_MIN_CLOCK_MHZ;
        if (pmicVddcoreRecoveryTime != PMIC_VDDCORE_RECOVERY_TIME_IGNORE)
        {
            /* Application uses on-board PMIC */
            ns += (((SYSCTL0->PDSLEEPCFG0 & 0x200U) == 0x200U) ? 39000U : 1300U) +
                  pmicVddcoreRecoveryTime * 1000U; /* PMIC vddcore recovery */
        }
    }

    ns += 1000U / PMU_MIN_CLOCK_MHZ; /* ISO disable */

    flag = (SYSCTL0->PDSLEEPCFG0 & 0x800U) == 0U;
    ns += (flag ? 6000U : (((SYSCTL0->PDSLEEPCFG0 & 0x1000U) == 0U) ? 88000U : 1000U)) / PMU_MIN_CLOCK_MHZ +
          (flag ? 26000U : 0U); /* Body Bias disable */

    /* SRAM power switches */
    groups   = (41U + PMC_MEM_SEQ_NUM - 1U) / PMC_MEM_SEQ_NUM;
    switches = countPartitionSwitches(PMC_MEM_SEQ_NUM);
    ns += (1000U + 47000U * switches +
           (((SYSCTL0->PDSLEEPCFG1 & (1UL << 31)) != 0U) ? 8000U : 1000U) * (groups - switches)) /
          PMU_MIN_CLOCK_MHZ;

    ns += 1000U / PMU_MIN_CLOCK_MHZ; /* Monitor change */

    /* Body Bias change */
    if (((SYSCTL0->PDRUNCFG0 & 0x800U) == 0U) ||
        (((SYSCTL0->PDSLEEPCFG0 & 0x800U) == 0U) && ((SYSCTL0->PDWAKECFG & SYSCTL0_PDWAKECFG_RBBKEEPST_MASK) != 0U)))
    {
        temp = 5000U;
        ns += 251000U;
    }
    else if (((SYSCTL0->PDRUNCFG0 & 0x1000U) == 0U) ||
             (((SYSCTL0->PDSLEEPCFG0 & 0x1000U) == 0U) &&
              ((SYSCTL0->PDWAKECFG & SYSCTL0_PDWAKECFG_FBBKEEPST_MASK) != 0U)))
    {
        temp = 312000U;
    }
    else
    {
        temp = 1000U;
    }
    ns += temp / PMU_MIN_CLOCK_MHZ;

    ns += 1000U / PMU_MIN_CLOCK_MHZ; /* ISO change */

    /* Bandgap mode */
    if (((SYSCTL0->PDRUNCFG0 & 0x10017D0U) == 0x10017D0U) &&
        (((SYSCTL0->PDSLEEPCFG0 & 0x1000U) == 0x1000U) ||
         (SYSCTL0->PDWAKECFG & SYSCTL0_PDWAKECFG_FBBKEEPST_MASK) == 0U))
    {
        ns += 7000U / PMU_MIN_CLOCK_MHZ + 50U;
    }
    else
    {
        ns += 1000U / PMU_MIN_CLOCK_MHZ;
    }

    /* FFRO/4 = 12 or 15MHz depending on trim range. */
    temp = (CLKCTL0->FFROCTL0 & CLKCTL0_FFROCTL0_TRIM_RANGE_MASK) == 0U ? 12U : 15U;
    return (ns * temp + 999U) / 1000U;
}

/**
 * @brief    PMC Sleep function call
 * @return   nothing
 */

void POWER_EnterSleep(void)
{
    uint32_t pmsk;
    pmsk = __get_PRIMASK();
    __disable_irq();
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    __WFI();
    __set_PRIMASK(pmsk);
}

/**
 * @brief    PMC Deep Sleep function call
 * @return   nothing
 */

void POWER_EnterDeepSleep(const uint32_t exclude_from_pd[4])
{
    uint32_t cpu_div;
    uint32_t mainclk_sel[2];
    uint32_t dspclk_sel[2];
    uint32_t pmsk = __get_PRIMASK();
    uint32_t pll_need_pd;
    uint32_t pll_need_rst[2];
    uint32_t pfd_need_gate[2];
    bool dsp_state  = false;
    bool ffro_state = true;
    uint32_t pmc_ctrl;
    uint32_t pmicMode;

    __disable_irq();
    POWER_SetBiasConfig();
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    mainclk_sel[0] = CLKCTL0->MAINCLKSELA;
    mainclk_sel[1] = CLKCTL0->MAINCLKSELB;
    dspclk_sel[0]  = CLKCTL1->DSPCPUCLKSELA;
    dspclk_sel[1]  = CLKCTL1->DSPCPUCLKSELB;
    cpu_div        = CLKCTL0->SYSCPUAHBCLKDIV;

    /* Power on mask bit correspond modules during Deep Sleep mode*/
    SYSCTL0->PDSLEEPCFG0 = (PCFG0_DEEP_SLEEP & ~exclude_from_pd[0]) |
                           (SYSCTL0->PDRUNCFG0 & ~exclude_from_pd[0] &
                            ~(SYSCTL0_PDSLEEPCFG0_PMIC_MODE0_MASK | SYSCTL0_PDSLEEPCFG0_PMIC_MODE1_MASK));
    SYSCTL0->PDSLEEPCFG1 = (PCFG1_DEEP_SLEEP & ~exclude_from_pd[1]) | (SYSCTL0->PDRUNCFG1 & ~exclude_from_pd[1]);
    SYSCTL0->PDSLEEPCFG2 = (PCFG2_DEEP_SLEEP & ~exclude_from_pd[2]) | (SYSCTL0->PDRUNCFG2 & ~exclude_from_pd[2]);
    SYSCTL0->PDSLEEPCFG3 = (PCFG3_DEEP_SLEEP & ~exclude_from_pd[3]) | (SYSCTL0->PDRUNCFG3 & ~exclude_from_pd[3]);

    PMC->PMICCFG = (s_pmicCfg == 0U) ? PMICCFG_DEFAULT_VALUE : s_pmicCfg;
    pmicMode     = (exclude_from_pd[0] & (SYSCTL0_PDSLEEPCFG0_PMIC_MODE0_MASK | SYSCTL0_PDSLEEPCFG0_PMIC_MODE1_MASK)) >>
               SYSCTL0_PDSLEEPCFG0_PMIC_MODE0_SHIFT;
    if (pmicMode == 0U) /* Use default PMIC Mode configuration. */
    {
        /* Set PMIC mode pin as 0b01 to let PMC turn on vdd1v8 and vddcore*/
        SYSCTL0->PDSLEEPCFG0 |= SYSCTL0_PDSLEEPCFG0_PMIC_MODE0(1) | SYSCTL0_PDSLEEPCFG0_PMIC_MODE1(0);
    }
    else /* User defined PMIC mode. */
    {
        SYSCTL0->PDSLEEPCFG0 |= pmicMode << SYSCTL0_PDSLEEPCFG0_PMIC_MODE0_SHIFT;
    }

    /* Stall DSP if shut off main clock*/
    if (((SYSCTL0->PDSLEEPCFG0 & SYSCTL0_PDSLEEPCFG0_MAINCLK_SHUTOFF_MASK) != 0U) && (SYSCTL0->DSPSTALL == 0U))
    {
        SYSCTL0->DSPSTALL = SYSCTL0_DSPSTALL_DSPSTALL_MASK;
        dsp_state         = true;
    }
    /* Clear all event flags before enter deep sleep */
    PMC->FLAGS = PMC->FLAGS;
    /* Turn on all memory partitions simultaneously. */
    PMC->MEMSEQCTRL = (PMC->MEMSEQCTRL & ~PMC_MEMSEQCTRL_MEMSEQNUM_MASK) | PMC_MEMSEQCTRL_MEMSEQNUM(PMC_MEM_SEQ_NUM);

    /* Disable LVD core reset. */
    pmc_ctrl  = PMC->CTRL;
    PMC->CTRL = pmc_ctrl & ~(PMC_CTRL_LVDCORERE_MASK | PMC_CTRL_LVDCOREIE_MASK);

    /* Make sure ffro clock be power up*/
    if ((SYSCTL0->PDRUNCFG0 & SYSCTL0_PDRUNCFG0_FFRO_PD_MASK) != 0U)
    {
        SYSCTL0->PDRUNCFG0_CLR = SYSCTL0_PDRUNCFG0_CLR_FFRO_PD_MASK;
        ffro_state             = false;
        /* Delay at least 32us */
        delay(US2FASTLOOP(32U));
    }

    /* Workaround for artf704338 */
    if ((SYSCTL0->PDSLEEPCFG0 & SYSCTL0_PDSLEEPCFG0_FFRO_PD_MASK) == 0U)
    {
        /* Main clock source FFRO remains on in deep sleep */
        SYSCTL0->MAINCLKSAFETY = POWER_CalculateSafetyCount();
    }
    else
    {
        SYSCTL0->MAINCLKSAFETY = 0U;
    }

    /* Deinit FlexSPI interface in case XIP */
    deinitXip();
    /* Let CPU/DSP run on ffro/4 before enter Deep Sleep mode*/
    CLKCTL0->MAINCLKSELA     = CLKCTL0_MAINCLKSELA_SEL(0);
    CLKCTL0->MAINCLKSELB     = CLKCTL0_MAINCLKSELB_SEL(0);
    CLKCTL1->DSPCPUCLKSELA   = CLKCTL1_DSPCPUCLKSELA_SEL(0);
    CLKCTL1->DSPCPUCLKSELB   = CLKCTL1_DSPCPUCLKSELB_SEL(0);
    CLKCTL0->SYSCPUAHBCLKDIV = 0;
    while ((CLKCTL0->SYSCPUAHBCLKDIV & CLKCTL0_SYSCPUAHBCLKDIV_REQFLAG_MASK) != 0U)
    {
    }

    /* PLL power down should not rely on PD_SLEEP_CFG auto loading.*/
    pll_need_pd = (SYSCTL0->PDRUNCFG0 ^ SYSCTL0->PDSLEEPCFG0) &
                  (SYSCTL0_PDRUNCFG0_SYSPLLLDO_PD_MASK | SYSCTL0_PDRUNCFG0_SYSPLLANA_PD_MASK |
                   SYSCTL0_PDRUNCFG0_AUDPLLLDO_PD_MASK | SYSCTL0_PDRUNCFG0_AUDPLLANA_PD_MASK);
    pll_need_rst[0] =
        IS_SYSPLL_ON(pll_need_pd) ? 0U : (CLKCTL0_SYSPLL0CTL0_RESET_MASK | CLKCTL0_SYSPLL0CTL0_HOLDRINGOFF_ENA_MASK);
    pll_need_rst[1] = IS_AUDPLL_ON(pll_need_pd) ?
                          0U :
                          (CLKCTL1_AUDIOPLL0CTL0_RESET_MASK | CLKCTL1_AUDIOPLL0CTL0_HOLDRINGOFF_ENA_MASK);
    pfd_need_gate[0] = IS_SYSPLL_ON(pll_need_pd) ? 0U : ((~CLKCTL0->SYSPLL0PFD) & SYSPLL0PFD_PFD_CLKGATE_MASK);
    pfd_need_gate[1] = IS_AUDPLL_ON(pll_need_pd) ? 0U : ((~CLKCTL1->AUDIOPLL0PFD) & AUDIOPLL0PFD_PFD_CLKGATE_MASK);
    /* Disable the PFD clock output first. */
    CLKCTL0->SYSPLL0PFD |= pfd_need_gate[0];
    CLKCTL1->AUDIOPLL0PFD |= pfd_need_gate[1];
    /* Set the PLL RESET and HOLDRINGOFF_ENA bits. */
    CLKCTL0->SYSPLL0CTL0 |= pll_need_rst[0];
    CLKCTL1->AUDIOPLL0CTL0 |= pll_need_rst[1];
    /* Power down the PLLs */
    SYSCTL0->PDRUNCFG0_SET = pll_need_pd;

    /* Enter deep sleep mode */
    __WFI();

    /* Wait OSC clock stable */
    if (((SYSCTL0->PDRUNCFG0 ^ SYSCTL0->PDSLEEPCFG0) & SYSCTL0_PDRUNCFG0_SYSXTAL_PD_MASK) != 0U)
    {
        delay(US2LOOP(oscSettlingTime));
    }

    /* Restore PLL state*/
    if (pll_need_pd != 0U)
    {
        /* Power up the PLLs */
        SYSCTL0->PDRUNCFG0_CLR = pll_need_pd;
        /* Delay (CLKCTL0-> SYSPLL0LOCKTIMEDIV2 / 2) us */
        delay(US2LOOP((CLKCTL0->SYSPLL0LOCKTIMEDIV2 & CLKCTL0_SYSPLL0LOCKTIMEDIV2_LOCKTIMEDIV2_MASK) / 2U));

        /* Clear System & Audio PLL reset with hold ring off enable*/
        CLKCTL0->SYSPLL0CTL0 &= ~(pll_need_rst[0] & CLKCTL0_SYSPLL0CTL0_RESET_MASK);
        CLKCTL1->AUDIOPLL0CTL0 &= ~(pll_need_rst[1] & CLKCTL1_AUDIOPLL0CTL0_RESET_MASK);
        /* Delay (CLKCTL0-> SYSPLL0LOCKTIMEDIV2 / 6) us */
        delay(US2LOOP((CLKCTL0->SYSPLL0LOCKTIMEDIV2 & CLKCTL0_SYSPLL0LOCKTIMEDIV2_LOCKTIMEDIV2_MASK) / 6U));

        /* Clear System PLL HOLDRINGOFF_ENA*/
        CLKCTL0->SYSPLL0CTL0 &= ~(pll_need_rst[0] & CLKCTL0_SYSPLL0CTL0_HOLDRINGOFF_ENA_MASK);
        /* Clear Audio PLL HOLDRINGOFF_ENA*/
        CLKCTL1->AUDIOPLL0CTL0 &= ~(pll_need_rst[1] & CLKCTL1_AUDIOPLL0CTL0_HOLDRINGOFF_ENA_MASK);
        /* Make sure PLL's output is stable, delay (CLKCTL0-> SYSPLL0LOCKTIMEDIV2 / 3) us */
        delay(US2LOOP((CLKCTL0->SYSPLL0LOCKTIMEDIV2 & CLKCTL0_SYSPLL0LOCKTIMEDIV2_LOCKTIMEDIV2_MASK) / 3U));

        if (pfd_need_gate[0] != 0U)
        {
            /* Clear ready status flag and restore PFD output status. */
            CLKCTL0->SYSPLL0PFD &= ~pfd_need_gate[0];
            /* Wait for output becomes stable. */
            while ((CLKCTL0->SYSPLL0PFD & SYSPLL0PFD_PFD_CLKRDY_MASK) != (pfd_need_gate[0] >> 1U))
            {
            }
        }

        if (pfd_need_gate[1] != 0U)
        {
            /* Clear ready status flag and restore PFD output status. */
            CLKCTL1->AUDIOPLL0PFD &= ~pfd_need_gate[1];
            /* Wait for output becomes stable. */
            while ((CLKCTL1->AUDIOPLL0PFD & AUDIOPLL0PFD_PFD_CLKRDY_MASK) != (pfd_need_gate[1] >> 1U))
            {
            }
        }
    }

    /* Restore CPU DIV clock configure*/
    CLKCTL0->SYSCPUAHBCLKDIV = cpu_div;
    while ((CLKCTL0->SYSCPUAHBCLKDIV & CLKCTL0_SYSCPUAHBCLKDIV_REQFLAG_MASK) != 0U)
    {
    }
    /* Restore CPU/DSP clock configure*/
    CLKCTL0->MAINCLKSELA   = mainclk_sel[0] & CLKCTL0_MAINCLKSELA_SEL_MASK;
    CLKCTL0->MAINCLKSELB   = mainclk_sel[1] & CLKCTL0_MAINCLKSELB_SEL_MASK;
    CLKCTL1->DSPCPUCLKSELA = dspclk_sel[0] & CLKCTL1_DSPCPUCLKSELA_SEL_MASK;
    CLKCTL1->DSPCPUCLKSELB = dspclk_sel[1] & CLKCTL1_DSPCPUCLKSELB_SEL_MASK;

    /* Restore ffro clock state*/
    if (!ffro_state)
    {
        SYSCTL0->PDRUNCFG0_SET = SYSCTL0_PDRUNCFG0_SET_FFRO_PD_MASK;
    }
    /* Init FlexSPI in case XIP */
    initXip();

    /* Restore PMC LVD core reset setting */
    PMC->CTRL = pmc_ctrl;

    /* Restore DSP stall status */
    if (dsp_state)
    {
        SYSCTL0->DSPSTALL &= ~SYSCTL0_DSPSTALL_DSPSTALL_MASK;
    }

    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    __set_PRIMASK(pmsk);
}

/**
 * @brief    PMC Deep Sleep Power Down function call
 * @return   nothing
 */

void POWER_EnterDeepPowerDown(const uint32_t exclude_from_pd[4])
{
    uint32_t state;
    uint32_t pmicMode;

    state = DisableGlobalIRQ();
    POWER_EnableDeepSleep();

    /* Set mask bit before enter Deep Power Down mode.*/
    SYSCTL0->PDSLEEPCFG0 |= (~exclude_from_pd[0] & PCFG0_DEEP_SLEEP);
    SYSCTL0->PDSLEEPCFG1 |= (~exclude_from_pd[1] & PCFG1_DEEP_SLEEP);
    SYSCTL0->PDSLEEPCFG2 |= (~exclude_from_pd[2] & PCFG2_DEEP_SLEEP);
    SYSCTL0->PDSLEEPCFG3 |= (~exclude_from_pd[3] & PCFG3_DEEP_SLEEP);

    /* Set DEEPPD bit in PDSLEEPCFG0*/
    SYSCTL0->PDSLEEPCFG0 |= SYSCTL0_PDSLEEPCFG0_DEEP_PD_MASK;

    PMC->PMICCFG = (s_pmicCfg == 0U) ? PMICCFG_DEFAULT_VALUE : s_pmicCfg;
    pmicMode     = (exclude_from_pd[0] & (SYSCTL0_PDSLEEPCFG0_PMIC_MODE0_MASK | SYSCTL0_PDSLEEPCFG0_PMIC_MODE1_MASK)) >>
               SYSCTL0_PDSLEEPCFG0_PMIC_MODE0_SHIFT;
    if (pmicMode == 0U) /* Use default PMIC Mode configuration. */
    {
        /* Set PMIC mode pin as 0b10 to let PMC trun off VDDCORE */
        POWER_SetPmicMode(0x2U, kCfg_Sleep);
    }
    else /* User defined PMIC mode. */
    {
        POWER_SetPmicMode(pmicMode, kCfg_Sleep);
    }

    /* Clear all event flags before enter deep powerdown */
    PMC->FLAGS = PMC->FLAGS;
    /* Enter deep powerdown mode */
    __WFI();

    /* Note that this code is never reached because we re-boot */
    EnableGlobalIRQ(state);
}

/**
 * @brief    PMC Full Deep Sleep Power Down function call
 * @return   nothing
 */

void POWER_EnterFullDeepPowerDown(const uint32_t exclude_from_pd[4])
{
    uint32_t state;
    uint32_t pmicMode;

    state = DisableGlobalIRQ();
    POWER_EnableDeepSleep();

    /* Set mask bit before enter Full Deep Power Down mode.*/
    SYSCTL0->PDSLEEPCFG0 |= (~exclude_from_pd[0] & PCFG0_DEEP_SLEEP);
    SYSCTL0->PDSLEEPCFG1 |= (~exclude_from_pd[1] & PCFG1_DEEP_SLEEP);
    SYSCTL0->PDSLEEPCFG2 |= (~exclude_from_pd[2] & PCFG2_DEEP_SLEEP);
    SYSCTL0->PDSLEEPCFG3 |= (~exclude_from_pd[3] & PCFG3_DEEP_SLEEP);

    /* Set DEEPPD bit in PDSLEEPCFG0*/
    SYSCTL0->PDSLEEPCFG0 |= SYSCTL0_PDSLEEPCFG0_DEEP_PD_MASK;

    PMC->PMICCFG = (s_pmicCfg == 0U) ? PMICCFG_DEFAULT_VALUE : s_pmicCfg;
    pmicMode     = (exclude_from_pd[0] & (SYSCTL0_PDSLEEPCFG0_PMIC_MODE0_MASK | SYSCTL0_PDSLEEPCFG0_PMIC_MODE1_MASK)) >>
               SYSCTL0_PDSLEEPCFG0_PMIC_MODE0_SHIFT;
    if (pmicMode == 0U) /* Use default PMIC Mode configuration. */
    {
        /* Set PMIC mode pin as 0b11 to let PMC trun off VDDCORE and VDD1V8*/
        POWER_SetPmicMode(0x3U, kCfg_Sleep);
    }
    else /* User defined PMIC mode. */
    {
        POWER_SetPmicMode(pmicMode, kCfg_Sleep);
    }

    /* Clear all event flags before enter full deep powerdown */
    PMC->FLAGS = PMC->FLAGS;
    /* Enter full deep powerdown mode */
    __WFI();

    /* Note that this code is never reached because we re-boot */
    EnableGlobalIRQ(state);
}

/* Enter Power mode */
void POWER_EnterPowerMode(power_mode_cfg_t mode, const uint32_t exclude_from_pd[4])
{
    switch (mode)
    {
        case kPmu_Sleep:
            POWER_EnterSleep();
            break;

        case kPmu_Deep_Sleep:
            POWER_EnterDeepSleep(exclude_from_pd);
            break;

        case kPmu_Deep_PowerDown:
            POWER_EnterDeepPowerDown(exclude_from_pd);
            break;

        case kPmu_Full_Deep_PowerDown:
            POWER_EnterFullDeepPowerDown(exclude_from_pd);
            break;

        default:
            assert(false);
            break;
    }
}

void POWER_SetPmicMode(uint32_t mode, pmic_mode_reg_t reg)
{
    __disable_irq();

    SYSCTL0_TUPLE_REG(reg) =
        (SYSCTL0_TUPLE_REG(reg) & ~(SYSCTL0_PDRUNCFG0_PMIC_MODE1_MASK | SYSCTL0_PDRUNCFG0_PMIC_MODE0_MASK)) |
        (mode << SYSCTL0_PDRUNCFG0_PMIC_MODE0_SHIFT);

    __enable_irq();
}

void EnableDeepSleepIRQ(IRQn_Type interrupt)
{
    uint32_t intNumber = (uint32_t)interrupt;

    if (intNumber >= 32U)
    {
        /* enable interrupt wake up in the STARTEN1 register */
        SYSCTL0->STARTEN1_SET = 1UL << (intNumber - 32U);
    }
    else
    {
        /* enable interrupt wake up in the STARTEN0 register */
        SYSCTL0->STARTEN0_SET = 1UL << intNumber;
    }
    /* also enable interrupt at NVIC */
    (void)EnableIRQ(interrupt);
}

void DisableDeepSleepIRQ(IRQn_Type interrupt)
{
    uint32_t intNumber = (uint32_t)interrupt;

    /* also disable interrupt at NVIC */
    (void)DisableIRQ(interrupt);

    if (intNumber >= 32U)
    {
        /* disable interrupt wake up in the STARTEN1 register */
        SYSCTL0->STARTEN1_CLR = 1UL << (intNumber - 32U);
    }
    else
    {
        /* disable interrupt wake up in the STARTEN0 register */
        SYSCTL0->STARTEN0_CLR = 1UL << intNumber;
    }
}

/* Get power lib version */
uint32_t POWER_GetLibVersion(void)
{
    return (uint32_t)FSL_POWER_DRIVER_VERSION;
}

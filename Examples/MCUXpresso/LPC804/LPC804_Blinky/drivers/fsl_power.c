/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2018, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_power.h"
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.power_no_lib"
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief API to enter sleep power mode.
 *
 * return none
 */
void POWER_EnterSleep(void)
{
    uint32_t pmsk;

    pmsk = __get_PRIMASK();
    __disable_irq();

    /* sleep mode */
    PMU->PCON &= ~PMU_PCON_PM_MASK;
    /* disable Deepsleep mode in the ARM-CORTEX M0+ SCR register */
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;

    /* Enter powerdown mode */
    __WFI();

    __set_PRIMASK(pmsk);   

}

/*!
 * brief API to enter deep sleep power mode.
 *
 * param activePart: should be a single or combine value of _power_deep_sleep_active .
 * return none
 */
void POWER_EnterDeepSleep(uint32_t activePart)
{
    assert((SYSCON->MAINCLKSEL & SYSCON_MAINCLKSEL_SEL_MASK) == 0U);

    uint32_t pmsk;

    pmsk = __get_PRIMASK();
    __disable_irq();

    PMU->PCON = (PMU->PCON & (~PMU_PCON_PM_MASK)) | PMU_PCON_PM(kPmu_Deep_Sleep);

    /* remain active during power down mode */
    SYSCON->PDSLEEPCFG &= ~activePart;
    
    /* enable Deepsleep mode in the ARM-CORTEX M0+ SCR register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Enter powerdown mode */
    __WFI();

    /* disable Deepsleep mode in the ARM-CORTEX M0+ SCR register */
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    __set_PRIMASK(pmsk);   
}

/*!
 * brief API to enter power down mode.
 *
 * param activePart: should be a single or combine value of _power_deep_sleep_active .
 * return none
 */
void POWER_EnterPowerDown(uint32_t activePart)
{
    assert((SYSCON->MAINCLKSEL & SYSCON_MAINCLKSEL_SEL_MASK) == 0U);

    uint32_t pmsk;

    pmsk = __get_PRIMASK();
    __disable_irq();

    PMU->PCON = (PMU->PCON & (~PMU_PCON_PM_MASK)) | PMU_PCON_PM(kPmu_PowerDown);

    /* remain active during power down mode */
    SYSCON->PDSLEEPCFG &= ~activePart;
   
    /* enable Deepsleep mode in the ARM-CORTEX M0+ SCR register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Enter powerdown mode */
    __WFI();

    /* disable Deepsleep mode in the ARM-CORTEX M0+ SCR register */
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    __set_PRIMASK(pmsk);   
}

/*!
 * brief API to enter deep power down mode.
 *
 * return none
 */
void POWER_EnterDeepPowerDownMode(void)
{
    uint32_t pmsk;

    pmsk = __get_PRIMASK();
    __disable_irq();

    /* make sure NODPD is cleared  */
    PMU->PCON = (PMU->PCON & (~(PMU_PCON_PM_MASK | PMU_PCON_NODPD_MASK))) | PMU_PCON_PM(kPmu_Deep_PowerDown);
    
    /* enable Deepsleep mode in the ARM-CORTEX M0+ SCR register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /*clear wake up pin status flag*/
    PMU->WUSRCREG |= PMU_WUSRCREG_WUSRCREG_MASK;

    /* Enter powerdown mode */
    __WFI();

    /* disable Deepsleep mode in the ARM-CORTEX M0+ SCR register */
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    __set_PRIMASK(pmsk);   
}

void EnableDeepSleepIRQ(IRQn_Type interrupt)
{
    uint32_t intNumber = (uint32_t)interrupt;
	
    if(intNumber >= 24u) 
    {
        /* enable pin interrupt wake up in the STARTERP0 register */
        SYSCON->STARTERP0 |= 1UL << (intNumber - 24u); 
    }        
    else
    {
        /* enable interrupt wake up in the STARTERP1 register */	 
        SYSCON->STARTERP1 |= 1UL << intNumber;          
    }
    /* also enable interrupt at NVIC */
    (void)EnableIRQ(interrupt); 
}

void DisableDeepSleepIRQ(IRQn_Type interrupt)
{
    uint32_t intNumber = (uint32_t)interrupt;
	
    /* also disable interrupt at NVIC */
    (void)DisableIRQ(interrupt); 
	
    if(intNumber >= 24u) 
    {
        /* disable pin interrupt wake up in the STARTERP0 register */
        SYSCON->STARTERP0 &= ~(1UL << (intNumber - 24u)); 
    }  
    else
    {
        /* disable interrupt wake up in the STARTERP1 register */	
        SYSCON->STARTERP1 &= ~(1UL << intNumber);         
    }
}

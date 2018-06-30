/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 11.1, Conversions shall not be performed
 * between a pointer to a function and any other type.
 * This is required in order to read/write from vector table memory.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 11.6, A cast shall not be performed
 * between pointer to void and an arithmetic type.
 * The address of hardware modules is provided as integer so
 * it needs to be cast to pointer.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 11.4, A conversion should not be performed
 * between a pointer to object and an integer type.
 * The address of hardware modules is provided as integer so
 * a conversion between a pointer and an integer has to be performed.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.9, An object should be defined at block scope
 * if its identifier only appears in a single function.
 * __VECTOR_RAM variable is not an object with static storage duration, it needs to be
 * declared as extern.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, External could be made static.
 * Function is defined for usage by application code.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 15.5, Return statement before end of function.
 * The return statement before end of function is used for simpler code structure
 * and better readability.
 *
 */

 /*! @file interrupt_manager.c */

#include "interrupt_manager.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Counter to manage the nested callings of global disable/enable interrupt.
 */
static int32_t g_interruptDisableCount = 0;

/*!
 * @brief Declaration of vector table.
 * FEATURE_INTERRUPT_IRQ_MAX is the highest interrupt request number.
 * 16 is the maximum number of exceptions
 */
extern uint32_t __VECTOR_RAM[((uint32_t)(FEATURE_INTERRUPT_IRQ_MAX)) + 16U + 1U];

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_InstallHandler
 * Description   : Install an interrupt handler routine for a given IRQ number
 * This function will let application register/replace the interrupt
 * handler for specified IRQ number. IRQ number is different than Vector
 * number. IRQ 0 will start from Vector 16 address. Refer to reference
 * manual for details. Also refer to startup_<CPU>.s file for each chip
 * family to find out the default interrupt handler for each device. This
 * function will convert the IRQ number to vector number by adding 16 to
 * it.
 *
 * Note          : This method is applicable only if interrupt vector is
 *                 copied in RAM, __flash_vector_table__ symbol is used to
 *                 control this from linker options.
 * Implements INT_SYS_InstallHandler_Activity
 *
 *END**************************************************************************/
void INT_SYS_InstallHandler(IRQn_Type irqNumber,
                            const isr_t newHandler,
                            isr_t* const oldHandler)
{

#if (defined(DEV_ERROR_DETECT) || defined(CUSTOM_DEVASSERT))

    /* Check IRQ number */
    int32_t dev_irqNumber = (int32_t)irqNumber;
    DEV_ASSERT(FEATURE_INTERRUPT_IRQ_MIN <= irqNumber);
    DEV_ASSERT(dev_irqNumber <= (int32_t)FEATURE_INTERRUPT_IRQ_MAX);
    DEV_ASSERT(__VECTOR_RAM != 0U);
    /* Check whether there is vector table in RAM */
    DEV_ASSERT((uint32_t)__VECTOR_RAM == S32_SCB->VTOR);

#endif /*(defined(DEV_ERROR_DETECT) || defined(CUSTOM_DEVASSERT)) */

    /* Save the former handler pointer */
    if (oldHandler != (isr_t *) 0)
    {
        *oldHandler = (isr_t)__VECTOR_RAM[((int32_t)irqNumber) + 16];
    }

#if FEATURE_MSCM_HAS_INTERRUPT_ROUTER

    #if (defined(DEV_ERROR_DETECT) || defined(CUSTOM_DEVASSERT))

        DEV_ASSERT((uint32_t)irqNumber < MSCM_IRSPRC_COUNT);
        /* Check routing is not read-only in case it needs to be written */
        uint16_t cpu_enable = (uint16_t)(1UL << (MSCM->CPXNUM));
        if ((MSCM->IRSPRC[irqNumber] & cpu_enable) == 0U)
        {
            DEV_ASSERT((MSCM->IRSPRC[irqNumber] & (uint16_t)(MSCM_IRSPRC_RO_MASK)) == (uint16_t)MSCM_IRSPRC_RO(0));
        }

    #endif /*(defined(DEV_ERROR_DETECT) || defined(CUSTOM_DEVASSERT)) */

#endif /* FEATURE_MSCM_HAS_INTERRUPT_ROUTER */

    /* Set handler into vector table */
#if defined (__ARMCC_VERSION)
	uint32_t  vector_ram    = __VECTOR_RAM;
	uint32_t * vector_ram_address =*(uint32_t * )vector_ram;
    vector_ram_address[((int32_t)irqNumber) + 16] = (uint32_t)newHandler;
#else
   __VECTOR_RAM[((int32_t)irqNumber) + 16] = (uint32_t)newHandler;
#endif

}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_EnableIRQ
 * Description   : Enables an interrupt for a given IRQ number.
 * It calls the system NVIC API to access the interrupt control
 * register and MSCM (if available) API for interrupt routing.
 * The input IRQ number does not include the core interrupt, only
 * the peripheral interrupt, from 0 to a maximum supported IRQ.
 * Implements INT_SYS_EnableIRQ_Activity
 *END**************************************************************************/
void INT_SYS_EnableIRQ(IRQn_Type irqNumber)
{

    /* Check IRQ number */
    DEV_ASSERT(0 <= (int32_t)irqNumber);
    DEV_ASSERT((uint32_t)irqNumber <= (uint32_t)FEATURE_INTERRUPT_IRQ_MAX);

    /* Enable interrupt */
    S32_NVIC->ISER[(uint32_t)(irqNumber) >> 5U] = (uint32_t)(1UL << ((uint32_t)(irqNumber) & (uint32_t)0x1FU));

#if FEATURE_MSCM_HAS_INTERRUPT_ROUTER

    /* Enable routing to current CPU */
    uint16_t cpu_enable = (uint16_t)(1UL << (MSCM->CPXNUM));
    MSCM->IRSPRC[irqNumber] |= cpu_enable;

#endif /* FEATURE_MSCM_HAS_INTERRUPT_ROUTER */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_DisableIRQ
 * Description   : Disable individual interrupt for a specified IRQ
 * It  calls the system NVIC API to access the interrupt control register
 * and MSCM (if available) API for interrupt routing.
 * Implements INT_SYS_DisableIRQ_Activity
 *
 *END**************************************************************************/
void INT_SYS_DisableIRQ(IRQn_Type irqNumber)
{

    /* Check IRQ number */
    DEV_ASSERT(0 <= (int32_t)irqNumber);
    DEV_ASSERT((uint32_t)irqNumber <= (uint32_t)FEATURE_INTERRUPT_IRQ_MAX);

    /* Disable interrupt */
    S32_NVIC->ICER[((uint32_t)(irqNumber) >> 5U)] = (uint32_t)(1UL << ((uint32_t)(irqNumber) & (uint32_t)0x1FU));

#if FEATURE_MSCM_HAS_INTERRUPT_ROUTER

    /* Disable routing to current CPU */
    uint16_t cpu_enable = (uint16_t)(1UL << (MSCM->CPXNUM));
    MSCM->IRSPRC[irqNumber] &= (uint16_t)~(cpu_enable);

#endif /* FEATURE_MSCM_HAS_INTERRUPT_ROUTER */

}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_EnableIRQGlobal
 * Description   : Enable system interrupt
 * This function will enable the global interrupt by calling the core API
 * Implements INT_SYS_EnableIRQGlobal_Activity
 *
 *END**************************************************************************/
void INT_SYS_EnableIRQGlobal(void)
{
    /* Check and update */
    if (g_interruptDisableCount > 0)
    {
        g_interruptDisableCount--;

        if (g_interruptDisableCount <= 0)
        {
            /* Enable the global interrupt*/
            ENABLE_INTERRUPTS();
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_DisableIRQGlobal
 * Description   : Disable system interrupt
 * This function will disable the global interrupt by calling the core API
 * Implements INT_SYS_DisableIRQGlobal_Activity
 *
 *END**************************************************************************/
void INT_SYS_DisableIRQGlobal(void)
{
    /* Disable the global interrupt */
    DISABLE_INTERRUPTS();

    /* Update counter*/
    g_interruptDisableCount++;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_SetPriority
 * Description   : Set the priority of an interrupt
 * This function will set the priority of an interrupt.
 * Note: The priority cannot be set for every core interrupt.
 * Implements INT_SYS_SetPriority_Activity
 *
 *END**************************************************************************/
void INT_SYS_SetPriority(IRQn_Type irqNumber, uint8_t priority)
{

#if (defined(DEV_ERROR_DETECT) || defined(CUSTOM_DEVASSERT))

    /* Check IRQ number and priority. */
    int32_t dev_irqNumber = (int32_t)irqNumber;
    DEV_ASSERT(dev_irqNumber <= (int32_t)FEATURE_INTERRUPT_IRQ_MAX);
    DEV_ASSERT(priority < (uint8_t)(1U << FEATURE_NVIC_PRIO_BITS));

#endif /*(defined(DEV_ERROR_DETECT) || defined(CUSTOM_DEVASSERT)) */

    uint8_t shift = (uint8_t) (8U - FEATURE_NVIC_PRIO_BITS);

    if ((int32_t)irqNumber < 0)
    {
        uint32_t intVectorId = ((uint32_t)(irqNumber) & 0xFU);
        uint32_t regId = intVectorId / 4U;
        /* Compute pointer to SHPR register - avoid MISRA violation. */
        volatile uint8_t * shpr_reg_ptr = ((regId == 1U) ? (volatile uint8_t *)&S32_SCB->SHPR1 : ((regId == 2U) ? (volatile uint8_t *)&S32_SCB->SHPR2 : (volatile uint8_t *)&S32_SCB->SHPR3));
        /* Set Priority for Cortex-M  System Interrupts */
        shpr_reg_ptr[intVectorId % 4U] = (uint8_t)(((((uint32_t)priority) << shift)) & 0xffUL);
    }
    else
    {
        /* Set Priority for device specific Interrupts */
        S32_NVIC->IP[(uint32_t)(irqNumber)] =  (uint8_t)(((((uint32_t)priority) << shift)) & 0xFFUL);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_GetPriority
 * Description   : Get the priority of an interrupt
 * This function will get the priority of an interrupt.
 * Note: The priority cannot be obtained for every core interrupt.
 * Implements INT_SYS_GetPriority_Activity
 *
 *END**************************************************************************/
uint8_t INT_SYS_GetPriority(IRQn_Type irqNumber)
{

#if (defined(DEV_ERROR_DETECT) || defined(CUSTOM_DEVASSERT))

    /* Check IRQ number. */
    int32_t dev_irqNumber = (int32_t)irqNumber;
    DEV_ASSERT(dev_irqNumber <= (int32_t)FEATURE_INTERRUPT_IRQ_MAX);

#endif /*(defined(DEV_ERROR_DETECT) || defined(CUSTOM_DEVASSERT)) */

    uint8_t priority = 0U;
    uint8_t shift = (uint8_t) (8U - FEATURE_NVIC_PRIO_BITS);

    if ((int32_t)irqNumber < 0)
    {
        uint32_t intVectorId = ((uint32_t)(irqNumber) & 0xFU);
        uint32_t regId = intVectorId / 4U;

        /* Compute pointer to SHPR register - avoid MISRA violation. */
        volatile const uint8_t * shpr_reg_ptr = ((regId == 1U) ? (volatile uint8_t *)&S32_SCB->SHPR1 : ((regId == 2U) ? (volatile uint8_t *)&S32_SCB->SHPR2 : (volatile uint8_t *)&S32_SCB->SHPR3));
        /* Get Priority from Cortex-M  System Interrupts */
        priority = (uint8_t)(shpr_reg_ptr[intVectorId % 4U] >> (shift));
    }
    else
    {
        /* Get Priority for device specific Interrupts  */
        priority = (uint8_t)(S32_NVIC->IP[(uint32_t)(irqNumber)] >> shift);
    }

    return priority;
}

#if FEATURE_INTERRUPT_HAS_PENDING_STATE
/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_ClearPending
 * Description   : Clear Pending Interrupt
 * This function clears the pending bit of a peripheral interrupt
 * or a directed interrupt to this CPU (if available).
 * Implements INT_SYS_ClearPending_Activity
 *
 *END**************************************************************************/
void INT_SYS_ClearPending(IRQn_Type irqNumber)
{

    /* Check IRQ number */
    DEV_ASSERT(0 <= (int32_t)irqNumber);
    DEV_ASSERT((uint32_t)irqNumber <= (uint32_t)FEATURE_INTERRUPT_IRQ_MAX);

#if FEATURE_MSCM_HAS_CPU_INTERRUPT_ROUTER

    if ((FEATURE_DIRECTED_CPU_INT_MIN <= irqNumber) && (irqNumber <= FEATURE_DIRECTED_CPU_INT_MAX))
    {
        /* Clear Directed CPU Pending Interrupt */
        switch (MSCM->CPXNUM)
        {
            case 0:
                MSCM->IRCP0IR |= (1UL << ((uint32_t)irqNumber - (uint32_t)FEATURE_DIRECTED_CPU_INT_MIN));
                break;
            default:
                MSCM->IRCP1IR |= (1UL << ((uint32_t)irqNumber - (uint32_t)FEATURE_DIRECTED_CPU_INT_MIN));
                break;
        }
        return;
    }

#endif /* FEATURE_MSCM_HAS_CPU_INTERRUPT_ROUTER */

    /* Clear Pending Interrupt */
    S32_NVIC->ICPR[(uint32_t)(irqNumber) >> 5U] = (uint32_t)(1UL << ((uint32_t)(irqNumber) & (uint32_t)0x1FU));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_SetPending
 * Description   : Set Pending Interrupt
 * This function configures the pending bit of a peripheral interrupt.
 * Implements INT_SYS_SetPending_Activity
 *
 *END**************************************************************************/
void INT_SYS_SetPending(IRQn_Type irqNumber)
{

    /* Check IRQ number */
    DEV_ASSERT(0 <= (int32_t)irqNumber);
    DEV_ASSERT((uint32_t)irqNumber <= (uint32_t)FEATURE_INTERRUPT_IRQ_MAX);

    /* Set Pending Interrupt */
    S32_NVIC->ISPR[(uint32_t)(irqNumber) >> 5U] = (uint32_t)(1UL << ((uint32_t)(irqNumber) & (uint32_t)0x1FU));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_GetPending
 * Description   : Get Pending Interrupt
 * This function gets the pending bit of a peripheral interrupt or a directed
 * interrupt to this CPU (if available).
 * Implements INT_SYS_GetPending_Activity
 *
 *END**************************************************************************/
uint32_t INT_SYS_GetPending(IRQn_Type irqNumber)
{

    /* Check IRQ number */
    DEV_ASSERT(0 <= (int32_t)irqNumber);
    DEV_ASSERT((uint32_t)irqNumber <= (uint32_t)FEATURE_INTERRUPT_IRQ_MAX);

#if FEATURE_MSCM_HAS_CPU_INTERRUPT_ROUTER

    /* Get Directed CPU Pending Interrupt */
    if ((FEATURE_DIRECTED_CPU_INT_MIN <= irqNumber) && (irqNumber <= FEATURE_DIRECTED_CPU_INT_MAX))
    {
        return (((((MSCM->CPXNUM != 0UL) ? MSCM->IRCP1IR : MSCM->IRCP0IR) &
                  (1UL << ((uint32_t)irqNumber - (uint32_t)FEATURE_DIRECTED_CPU_INT_MIN))) != 0UL) ? 1UL : 0UL);
    }

#endif /* FEATURE_MSCM_HAS_CPU_INTERRUPT_ROUTER */

    /* Get Pending Interrupt */
    return ((uint32_t)(((S32_NVIC->ISPR[(((uint32_t)irqNumber) >> 5UL)] & (1UL << (((uint32_t)irqNumber) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
}
#endif /* FEATURE_INTERRUPT_HAS_PENDING_STATE */

#if FEATURE_INTERRUPT_HAS_ACTIVE_STATE
/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_GetActive
 * Description   : Get active state of a peripheral interrupt
 * This function gets the active state of a peripheral interrupt.
 * Implements INT_SYS_GetActive_Activity
 *
 *END**************************************************************************/
uint32_t INT_SYS_GetActive(IRQn_Type irqNumber)
{

    /* Check IRQ number */
    DEV_ASSERT(0 <= (int32_t)irqNumber);
    DEV_ASSERT((uint32_t)irqNumber <= (uint32_t)FEATURE_INTERRUPT_IRQ_MAX);

    /* Get Active Interrupt */
    return ((uint32_t)(((S32_NVIC->IABR[(((uint32_t)irqNumber) >> 5UL)] & (1UL << (((uint32_t)irqNumber) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
}
#endif /* FEATURE_INTERRUPT_HAS_ACTIVE_STATE */

#if FEATURE_MSCM_HAS_CPU_INTERRUPT_ROUTER

/*!
 * @brief Generate Directed CPU Interrupt
 *
 * The function generates a directed interrupt to (one or more) CPUs defined by target.
 * Implements INT_SYS_GenerateDirectedCpuInterrupt_Activity
 *
 * @param irqNumber  IRQ number
 * @param cpu_target Target CPUs for the directed interrupt
 */
/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_GenerateDirectedCpuInterrupt
 * Description   : Get active state of a peripheral interrupt
 * This function gets the active state of a peripheral interrupt.
 * Implements INT_SYS_GenerateDirectedCpuInterrupt_Activity
 *
 *END**************************************************************************/
void INT_SYS_GenerateDirectedCpuInterrupt(IRQn_Type irqNumber, interrupt_manager_cpu_targets_t cpu_target)
{

    /* Check IRQ number */
    DEV_ASSERT(FEATURE_DIRECTED_CPU_INT_MIN <= irqNumber);
    DEV_ASSERT(irqNumber <= FEATURE_DIRECTED_CPU_INT_MAX);

    uint32_t reg_val = MSCM_IRCPGIR_INTID((uint32_t)irqNumber - (uint32_t)FEATURE_DIRECTED_CPU_INT_MIN);

    switch (cpu_target)
    {
        case INTERRUPT_MANAGER_TARGET_SELF:
            reg_val |= MSCM_IRCPGIR_TLF(2);
            break;
        case INTERRUPT_MANAGER_TARGET_OTHERS:
            reg_val |= MSCM_IRCPGIR_TLF(1);
            break;
        case INTERRUPT_MANAGER_TARGET_NONE:
        case INTERRUPT_MANAGER_TARGET_CP0:
        case INTERRUPT_MANAGER_TARGET_CP1:
        case INTERRUPT_MANAGER_TARGET_CP0_CP1:
            reg_val |= (MSCM_IRCPGIR_TLF(0) | MSCM_IRCPGIR_CPUTL(cpu_target));
            break;
        default:
            /* Not treated case ? */
            break;
    }

    /* Generate Directed CPU Interrupt */
    MSCM->IRCPGIR = reg_val;
}

#endif /* FEATURE_MSCM_HAS_CPU_INTERRUPT_ROUTER */

/*******************************************************************************
 * EOF
 ******************************************************************************/

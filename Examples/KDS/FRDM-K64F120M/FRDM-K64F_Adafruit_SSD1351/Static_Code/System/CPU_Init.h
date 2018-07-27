/** ###################################################################
**      Filename    : CPU_Init.h
**      Processor   : MK64FN1M0VLL12
**      Version     : 1.0
** 
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
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
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file CPU_Init.h                                                  
** @version 01.00
*/         
/*!
**  @addtogroup CPU_Init_module CPU_Init module documentation
**  @{
*/         

#ifndef __CPU_Init_H
#define __CPU_Init_H

/* MODULE CPU_Init.h */

#include "CPU_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Global variables */
extern volatile uint8_t SR_reg;        /* Current FAULTMASK register */
extern volatile uint8_t SR_lock;       /* Lock */

/* Interrupt vector table type definition */
typedef void (*const tIsrFunc)(void);
typedef struct {
  void * __ptr;
  tIsrFunc __fun[0x65];
} tVectorTable;

#if defined(__IAR_SYSTEMS_ICC__)
extern const tVectorTable __vector_table;
extern const tVectorTable __vect_table;
#else
extern const tVectorTable __vect_table;
#endif

/*
** ===================================================================
**     Method      :  __init_hardware (component MK64FN1M0LL12)
**
**     Description :
**         This method is called from the __thumb_startup() function and 
**         provides necessary system initialization such as PLL, and 
**         external bus. Function of this name is used when GCC or ARM 
**         Keil compiler is used. IAR compiler uses function 
**         __low_level_init().
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void __init_hardware(void);

/*
** ===================================================================
**     Method      :  PE_low_level_init (component MK64FN1M0LL12)
**
**     Description :
**         Initializes components and provides common register 
**         initialization. The method is called automatically as a part 
**         of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void PE_low_level_init(void);

void CPU_SetClockConfigGenMode(LDD_TClockConfiguration ConfigID);

/*
** ===================================================================
**     Method      :  Cpu_SetClockConfiguration (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         Calling of this method will cause the clock configuration
**         change and reconfiguration of all components according to
**         the requested clock configuration setting.
**     @param
**         ModeID          - Clock configuration identifier
**     @return
**                         - ERR_OK - OK.
**                           ERR_RANGE - Mode parameter out of range
*/
/* ===================================================================*/
#if CPU_SET_CLOCK_CONFIGURATION
LDD_TError CPU_SetClockConfiguration(LDD_TClockConfiguration ModeID);
#endif /* CPU_SET_CLOCK_CONFIGURATION */

/*
** ===================================================================
**     Method      :  Cpu_GetClockConfiguration (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         Returns the active clock configuration identifier. The
**         method is automatically enabled if more than one clock
**         configuration is enabled in the component.
**     @return
**                         - Active clock configuration identifier
*/
/* ===================================================================*/
#if CPU_GET_CLOCK_CONFIGURATION
uint8_t CPU_GetClockConfiguration(void);
#endif /* CPU_GET_CLOCK_CONFIGURATION */

/*
** ===================================================================
**     Method      :  Cpu_SetOperationMode (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         This method requests to change the component's operation
**         mode (RUN, WAIT, SLEEP, STOP). The target operation mode
**         will be entered immediately. 
**         See [Operation mode settings] for further details of the
**         operation modes mapping to low power modes of the cpu.
**     @param
**         OperationMode   - Requested driver
**                           operation mode
**     @param
**         ModeChangeCallback - Callback to
**                           notify the upper layer once a mode has been
**                           changed. Parameter is ignored, only for
**                           compatibility of API with other components.
**     @param
**         ModeChangeCallbackParamPtr 
**                           - Pointer to callback parameter to notify
**                           the upper layer once a mode has been
**                           changed. Parameter is ignored, only for
**                           compatibility of API with other components.
**     @return
**                         - Error code
**                           ERR_OK - OK
**                           ERR_PARAM_MODE - Invalid operation mode
*/
/* ===================================================================*/
#if CPU_SET_OPERATION_MODE
LDD_TError CPU_SetOperationMode(LDD_TDriverOperationMode OperationMode, LDD_TCallback ModeChangeCallback, LDD_TCallbackParam *ModeChangeCallbackParamPtr);
#endif /* CPU_SET_OPERATION_MODE */

/*
** ===================================================================
**     Method      :  Cpu_EnableInt (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         Enables all maskable interrupts.
*/
/* ===================================================================*/
#if CPU_ENABLE_INT
void CPU_EnableInt(void);
#endif /* CPU_ENABLE_INT */

/*
** ===================================================================
**     Method      :  Cpu_DisableInt (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         Disables all maskable interrupts.
*/
/* ===================================================================*/
#if CPU_DISABLE_INT
void CPU_DisableInt(void);
#endif /* CPU_DISABLE_INT */

/*
** ===================================================================
**     Method      :  Cpu_MCGAutoTrim (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         This method uses MCG auto trim feature to trim internal
**         reference clock. This method can be used only in a clock
**         configuration which derives its bus clock from external
**         reference clock ([MCG mode] must be one of the following
**         modes - FEE, FBE, BLPE, PEE, PBE) and if value of [Bus clock]
**         is in the range <8; 16>MHz.
**         The slow internal reference clock is trimmed to the value
**         selected by [Slow internal reference clock [kHz]] property. 
**         The fast internal reference clock will be trimmed to value
**         4MHz.
**     @param
**         ClockSelect     - Selects which internal
**                           reference clock will be trimmed.
**                           0 ... slow (32kHz) internal reference clock
**                           will be trimmed
**                           > 0 ... fast (4MHz) internal reference
**                           clock will be trimmed
**     @return
**                         - Error code
**                           ERR_OK - OK
**                           ERR_SPEED - The method does not work in the
**                           active clock configuration.
**                           ERR_FAILED - Autotrim process failed.
*/
/* ===================================================================*/
#if CPU_MCG_AUTO_TRIM
LDD_TError CPU_MCGAutoTrim(uint8_t ClockSelect);
#endif /* CPU_MCG_AUTO_TRIM */

/*
** ===================================================================
**     Method      :  Cpu_VLPModeEnable (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         This method enables Very Low Power (VLP) mode in the active
**         clock configuration. To enable the VLP mode the active clock
**         configuration has to have the [Very low power mode] property
**         enabled. The method waits until the entry to the VLP mode is
**         confirmed by a power management module status register.
**         This method can be enabled only when one of the clock
**         configurations modes have the [Very low power mode] property
**         enabled.
**     @return
**                         - Error code 
**                           ERR_OK - OK
**                           ERR_SPEED - the Very Low Power mode is not
**                           supported in the active clock configuration.
*/
/* ===================================================================*/
#if CPU_VLP_MODE_ENABLE
LDD_TError CPU_VLPModeEnable(void);
#endif /* CPU_VLP_MODE_ENABLE */

/*
** ===================================================================
**     Method      :  Cpu_VLPModeDisable (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         This method disables the Very Low Power (VLP) mode in the
**         active clock configuration. The method waits until the exit
**         of the VLP mode is confirmed by a power management module
**         status register.
**         This method can be enabled only when one of the clock
**         configurations have the [Very low power mode] property
**         enabled.
**     @return
**                         - Error code 
**                           ERR_OK - OK
**                           ERR_SPEED - the Very Low Power mode is not
**                           supported in the active clock configuration.
*/
/* ===================================================================*/
#if CPU_VLP_MODE_DISABLE
LDD_TError CPU_VLPModeDisable(void);
#endif /* CPU_VLP_MODE_DISABLE */

/*
** ===================================================================
**     Method      :  Cpu_SystemReset (component MK64FN1M0LL12)
*/
/*!
**     @brief
**         This method initiates a system reset request to reset the
**         CPU.
*/
/* ===================================================================*/
#if CPU_SYSTEM_RESET
void CPU_SystemReset(void);
#endif /* CPU_SYSTEM_RESET */

#ifdef __cplusplus
}
#endif

/* END CPU_Init.h */

#endif /* __CPU_Init_H */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file is a part of Processor Expert static initialization
**     library for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

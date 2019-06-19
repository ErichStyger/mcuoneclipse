/** ###################################################################
**      Filename    : CPU_Init.h
**      Processor   : MKE06Z128VLK4
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
  tIsrFunc __fun[0x2F];
} tVectorTable;

#if defined(__IAR_SYSTEMS_ICC__)
extern const tVectorTable __vector_table;
extern const tVectorTable __vect_table;
#else
extern const tVectorTable __vect_table;
#endif

/*
** ===================================================================
**     Method      :  __init_hardware (component MKE06Z128LK4)
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
**     Method      :  PE_low_level_init (component MKE06Z128LK4)
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
**     Method      :  Cpu_SetClockConfiguration (component MKE06Z128LK4)
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
**     Method      :  Cpu_GetClockConfiguration (component MKE06Z128LK4)
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
**     Method      :  Cpu_SetOperationMode (component MKE06Z128LK4)
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
**     Method      :  Cpu_EnableInt (component MKE06Z128LK4)
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
**     Method      :  Cpu_DisableInt (component MKE06Z128LK4)
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
**     Method      :  Cpu_SystemReset (component MKE06Z128LK4)
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
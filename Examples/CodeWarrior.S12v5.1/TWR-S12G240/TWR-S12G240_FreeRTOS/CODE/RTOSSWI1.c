/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : RTOSSWI1.c
**     Project   : TWR_S12G240_FreeRTOS
**     Processor : MC9S12G240CLL
**     Component : InterruptVector
**     Version   : Component 02.023, Driver 01.06, CPU db: 3.00.010
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 04.09.2018, 14:00
**     Abstract  :
**         This component "InterruptVector" gives an access to interrupt vector.
**         The purpose of this component is to allocate the interrupt vector
**         in the vector table. Additionally it can provide settings of
**         the interrupt priority register.
**         The interrupt handling routines must be implemented by the user.
**     Settings  :
**         Interrupt vector            : Vswi
**         Handle name                 : vPortYieldISR
**     Contents  :
**         No public methods
**
**     Copyright : 1997 - 2011 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE RTOSSWI1. */

/*
** ###################################################################
**
**  The interrupt service routine(s) must be implemented
**  by user in one of the following user modules.
**
**  If the "Generate ISR" option is enabled, Processor Expert generates
**  ISR templates in the CPU event module.
**
**  User modules:
**      TWR_S12G240_FreeRTOS.c
**      Events.c
**
** ###################################################################
#pragma CODE_SEG __NEAR_SEG NON_BANKED
ISR(vPortYieldISR)
{
}
#pragma CODE_SEG DEFAULT
*/

/* END RTOSSWI1. */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.03 [04.46]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
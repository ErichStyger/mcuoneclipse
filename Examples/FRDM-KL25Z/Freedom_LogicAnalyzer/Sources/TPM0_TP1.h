/** ###################################################################
**     Filename    : TPM1_TP1.h
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Component   : Init_TPM
**     Version     : Component 01.000, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-03-19, 16:32, # CodeGen: 40
**     Abstract    :
**          This file implements the TPM (TPM1) module initialization
**          according to the Peripheral Initialization settings, and
**          defines interrupt service routines prototypes.
**     Settings    :
**          Component name                                 : TP1
**          Device                                         : TPM1
**          Settings                                       : 
**            Clock gate                                   : Enabled
**            Clock settings                               : 
**              Clock source                               : Counter clock
**              Prescaler                                  : divide by 1
**              Modulo counter                             : 0
**              Period                                     : (1 * 65536) / External Clock Source
**            BDM mode                                     : TPM counter running; output pins operational
**            Global time base                             : Enabled
**            Counter reload on trigger                    : Enabled
**            Counter start on trigger                     : Disabled
**            Counter stop on overflow                     : Disabled
**          Channels                                       : 
**            Channel 0                                    : Enabled
**              Channel mode                               : Output compare
**                Output action                            : Toggle output
**                Channel value register                   : 0
**              Pin                                        : Enabled
**                Pin                                      : PTA12/TPM1_CH0
**                Pin signal                               : 
**              Interrupt/DMA                              : 
**                Interrupt                                : INT_TPM1
**                Channel interrupt                        : Disabled
**                DMA request                              : Enabled
**            Channel 1                                    : Disabled
**          Pins                                           : 
**            External clock pin                           : Disabled
**            HW Synchronization trigger                   : Disabled
**          Interrupts                                     : 
**            Channels / Timer overflow / Fault            : 
**              Interrupt                                  : INT_TPM1
**              Interrupt request                          : Disabled
**              Interrupt priority                         : 0 (Highest)
**              ISR Name                                   : 
**              Channels interrupt/DMA                     : See the respective Channel settings
**              Timer overflow interrupt                   : Disabled
**          Initialization                                 : 
**            Call Init method                             : yes
**     Contents    :
**         Init - void TP1_Init(void);
**
**     Copyright : 1997 - 2012 Freescale, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef TPM0_H_
#define TPM0_H_

/* MODULE TP1. */

/* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

LDD_TDeviceData* TP1_initTimer(void);
void TP1_disableTimer(LDD_TDeviceData *DMAT1Handl);
void TP1_enableTimer(LDD_TDeviceData *DMAT1Handl);
LDD_TError TP1_setTimerValue(LDD_TDeviceData *DMAT1Handl, uint32_t brg);


/* END TP1. */
#endif /* #ifndef __TPM0_H_ */
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.0 [05.03]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

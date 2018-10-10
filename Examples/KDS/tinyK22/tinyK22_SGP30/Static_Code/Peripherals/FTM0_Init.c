/** ###################################################################
 **     Filename    : FTM0_Init.c
 **     Processor   : MK22FN512LH12
 **     Abstract    :
 **          This file implements the FTM0 module initialization
 **          according to the Peripheral Initialization settings, and
 **          defines interrupt service routines prototypes.
 **
 **     Contents    :
 **         Int   - void FTM0_Init(void);
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
 * @file FTM0_Init.c
 * @brief This file implements the FTM0 module initialization according to the
 *        Peripheral Initialization settings, and defines interrupt service
 *        routines prototypes.
 */


/* MODULE FTM0_Init. */

#include "FTM0_Init.h"
#include "MK22F51212.h"
#include "Init_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

void FTM0_Init(void) {
  (void)FTM0_SC;  /* Dummy read of the Control Status register to clear the interrupt flag */
  FTM0_SC = 0;  /* Stop the counter */
  #ifdef FTM0_C0SC
  (void)FTM0_C0SC; /* Dummy read of the Channel Status and Control 0 register to clear the interrupt flag */
  #endif
  #ifdef FTM0_C1SC
  (void)FTM0_C1SC; /* Dummy read of the Channel Status and Control 1 register to clear the interrupt flag */
  #endif
  #ifdef FTM0_C2SC
  (void)FTM0_C2SC; /* Dummy read of the Channel Status and Control 2 register to clear the interrupt flag */
  #endif
  #ifdef FTM0_C3SC
  (void)FTM0_C3SC; /* Dummy read of the Channel Status and Control 3 register to clear the interrupt flag */
  #endif
  #ifdef FTM0_C4SC
  (void)FTM0_C4SC; /* Dummy read of the Channel Status and Control 4 register to clear the interrupt flag */
  #endif
  #ifdef FTM0_C5SC
  (void)FTM0_C5SC; /* Dummy read of the Channel Status and Control 5 register to clear the interrupt flag */
  #endif
  #ifdef FTM0_C6SC
  (void)FTM0_C6SC; /* Dummy read of the Channel Status and Control 6 register to clear the interrupt flag */
  #endif
  #ifdef FTM0_C7SC
  (void)FTM0_C7SC; /* Dummy read of the Channel Status and Control 7 register to clear the interrupt flag */
  #endif
  #ifdef FTM0_MODE_VALUE_1
  FTM0_MODE |= FTM0_MODE_VALUE_1; /* Disable write protection */
  #endif

  FTM0_C0SC = 0;

  FTM0_C1SC = 0;

  FTM0_C2SC = 0;

  FTM0_C3SC = 0;

  FTM0_C4SC = 0;

  FTM0_C5SC = 0;

  FTM0_C6SC = 0;

  FTM0_C7SC = 0;

  /* Register 'FTM0_SC' initialization */
  #if FTM0_SC_MASK_2
    #if FTM0_SC_MASK_2 == 0xFFFFFFFF
  FTM0_SC = FTM0_SC_VALUE_2;
    #elif FTM0_SC_MASK_2 == FTM0_SC_VALUE_2
  FTM0_SC |= FTM0_SC_VALUE_2;
    #elif FTM0_SC_VALUE_2 == 0
  FTM0_SC &= ~FTM0_SC_MASK_2;
    #else
  FTM0_SC = (FTM0_SC & (~FTM0_SC_MASK_2)) | FTM0_SC_VALUE_2;
    #endif
  #elif defined(FTM0_SC_VALUE_2)
  FTM0_SC = FTM0_SC_VALUE_2;
  #endif

  /* Register 'FTM0_MODE' initialization */
  #if FTM0_MODE_MASK_2
    #if FTM0_MODE_MASK_2 == 0xFFFFFFFF
  FTM0_MODE = FTM0_MODE_VALUE_2;
    #elif FTM0_MODE_MASK_2 == FTM0_MODE_VALUE_2
  FTM0_MODE |= FTM0_MODE_VALUE_2;
    #elif FTM0_MODE_VALUE_2 == 0
  FTM0_MODE &= ~FTM0_MODE_MASK_2;
    #else
  FTM0_MODE = (FTM0_MODE & (~FTM0_MODE_MASK_2)) | FTM0_MODE_VALUE_2;
    #endif
  #elif defined(FTM0_MODE_VALUE_2)
  FTM0_MODE = FTM0_MODE_VALUE_2;
  #endif

  /* Register 'FTM0_COMBINE' initialization */
  #if FTM0_COMBINE_MASK
    #if FTM0_COMBINE_MASK == 0xFFFFFFFF
  FTM0_COMBINE = FTM0_COMBINE_VALUE;
    #elif FTM0_COMBINE_MASK == FTM0_COMBINE_VALUE
  FTM0_COMBINE |= FTM0_COMBINE_VALUE;
    #elif FTM0_COMBINE_VALUE == 0
  FTM0_COMBINE &= ~FTM0_COMBINE_MASK;
    #else
  FTM0_COMBINE = (FTM0_COMBINE & (~FTM0_COMBINE_MASK)) | FTM0_COMBINE_VALUE;
    #endif
  #elif defined(FTM0_COMBINE_VALUE)
  FTM0_COMBINE = FTM0_COMBINE_VALUE;
  #endif

  /* Register 'FTM0_INVCTRL' initialization */
  #if FTM0_INVCTRL_MASK
    #if FTM0_INVCTRL_MASK == 0xFFFFFFFF
  FTM0_INVCTRL = FTM0_INVCTRL_VALUE;
    #elif FTM0_INVCTRL_MASK == FTM0_INVCTRL_VALUE
  FTM0_INVCTRL |= FTM0_INVCTRL_VALUE;
    #elif FTM0_INVCTRL_VALUE == 0
  FTM0_INVCTRL &= ~FTM0_INVCTRL_MASK;
    #else
  FTM0_INVCTRL = (FTM0_INVCTRL & (~FTM0_INVCTRL_MASK)) | FTM0_INVCTRL_VALUE;
    #endif
  #elif defined(FTM0_INVCTRL_VALUE)
  FTM0_INVCTRL = FTM0_INVCTRL_VALUE;
  #endif

  /* Register 'FTM0_C0SC' initialization */
  #if FTM0_C0SC_MASK
    #if FTM0_C0SC_MASK == 0xFFFFFFFF
  FTM0_C0SC = FTM0_C0SC_VALUE;
    #elif FTM0_C0SC_MASK == FTM0_C0SC_VALUE
  FTM0_C0SC |= FTM0_C0SC_VALUE;
    #elif FTM0_C0SC_VALUE == 0
  FTM0_C0SC &= ~FTM0_C0SC_MASK;
    #else
  FTM0_C0SC = (FTM0_C0SC & (~FTM0_C0SC_MASK)) | FTM0_C0SC_VALUE;
    #endif
  #elif defined(FTM0_C0SC_VALUE)
  FTM0_C0SC = FTM0_C0SC_VALUE;
  #endif

  /* Register 'FTM0_C1SC' initialization */
  #if FTM0_C1SC_MASK
    #if FTM0_C1SC_MASK == 0xFFFFFFFF
  FTM0_C1SC = FTM0_C1SC_VALUE;
    #elif FTM0_C1SC_MASK == FTM0_C1SC_VALUE
  FTM0_C1SC |= FTM0_C1SC_VALUE;
    #elif FTM0_C1SC_VALUE == 0
  FTM0_C1SC &= ~FTM0_C1SC_MASK;
    #else
  FTM0_C1SC = (FTM0_C1SC & (~FTM0_C1SC_MASK)) | FTM0_C1SC_VALUE;
    #endif
  #elif defined(FTM0_C1SC_VALUE)
  FTM0_C1SC = FTM0_C1SC_VALUE;
  #endif

  /* Register 'FTM0_C2SC' initialization */
  #if FTM0_C2SC_MASK
    #if FTM0_C2SC_MASK == 0xFFFFFFFF
  FTM0_C2SC = FTM0_C2SC_VALUE;
    #elif FTM0_C2SC_MASK == FTM0_C2SC_VALUE
  FTM0_C2SC |= FTM0_C2SC_VALUE;
    #elif FTM0_C2SC_VALUE == 0
  FTM0_C2SC &= ~FTM0_C2SC_MASK;
    #else
  FTM0_C2SC = (FTM0_C2SC & (~FTM0_C2SC_MASK)) | FTM0_C2SC_VALUE;
    #endif
  #elif defined(FTM0_C2SC_VALUE)
  FTM0_C2SC = FTM0_C2SC_VALUE;
  #endif

  /* Register 'FTM0_C3SC' initialization */
  #if FTM0_C3SC_MASK
    #if FTM0_C3SC_MASK == 0xFFFFFFFF
  FTM0_C3SC = FTM0_C3SC_VALUE;
    #elif FTM0_C3SC_MASK == FTM0_C3SC_VALUE
  FTM0_C3SC |= FTM0_C3SC_VALUE;
    #elif FTM0_C3SC_VALUE == 0
  FTM0_C3SC &= ~FTM0_C3SC_MASK;
    #else
  FTM0_C3SC = (FTM0_C3SC & (~FTM0_C3SC_MASK)) | FTM0_C3SC_VALUE;
    #endif
  #elif defined(FTM0_C3SC_VALUE)
  FTM0_C3SC = FTM0_C3SC_VALUE;
  #endif

  /* Register 'FTM0_C4SC' initialization */
  #if FTM0_C4SC_MASK
    #if FTM0_C4SC_MASK == 0xFFFFFFFF
  FTM0_C4SC = FTM0_C4SC_VALUE;
    #elif FTM0_C4SC_MASK == FTM0_C4SC_VALUE
  FTM0_C4SC |= FTM0_C4SC_VALUE;
    #elif FTM0_C4SC_VALUE == 0
  FTM0_C4SC &= ~FTM0_C4SC_MASK;
    #else
  FTM0_C4SC = (FTM0_C4SC & (~FTM0_C4SC_MASK)) | FTM0_C4SC_VALUE;
    #endif
  #elif defined(FTM0_C4SC_VALUE)
  FTM0_C4SC = FTM0_C4SC_VALUE;
  #endif

  /* Register 'FTM0_C5SC' initialization */
  #if FTM0_C5SC_MASK
    #if FTM0_C5SC_MASK == 0xFFFFFFFF
  FTM0_C5SC = FTM0_C5SC_VALUE;
    #elif FTM0_C5SC_MASK == FTM0_C5SC_VALUE
  FTM0_C5SC |= FTM0_C5SC_VALUE;
    #elif FTM0_C5SC_VALUE == 0
  FTM0_C5SC &= ~FTM0_C5SC_MASK;
    #else
  FTM0_C5SC = (FTM0_C5SC & (~FTM0_C5SC_MASK)) | FTM0_C5SC_VALUE;
    #endif
  #elif defined(FTM0_C5SC_VALUE)
  FTM0_C5SC = FTM0_C5SC_VALUE;
  #endif

  /* Register 'FTM0_C6SC' initialization */
  #if FTM0_C6SC_MASK
    #if FTM0_C6SC_MASK == 0xFFFFFFFF
  FTM0_C6SC = FTM0_C6SC_VALUE;
    #elif FTM0_C6SC_MASK == FTM0_C6SC_VALUE
  FTM0_C6SC |= FTM0_C6SC_VALUE;
    #elif FTM0_C6SC_VALUE == 0
  FTM0_C6SC &= ~FTM0_C6SC_MASK;
    #else
  FTM0_C6SC = (FTM0_C6SC & (~FTM0_C6SC_MASK)) | FTM0_C6SC_VALUE;
    #endif
  #elif defined(FTM0_C6SC_VALUE)
  FTM0_C6SC = FTM0_C6SC_VALUE;
  #endif

  /* Register 'FTM0_C7SC' initialization */
  #if FTM0_C7SC_MASK
    #if FTM0_C7SC_MASK == 0xFFFFFFFF
  FTM0_C7SC = FTM0_C7SC_VALUE;
    #elif FTM0_C7SC_MASK == FTM0_C7SC_VALUE
  FTM0_C7SC |= FTM0_C7SC_VALUE;
    #elif FTM0_C7SC_VALUE == 0
  FTM0_C7SC &= ~FTM0_C7SC_MASK;
    #else
  FTM0_C7SC = (FTM0_C7SC & (~FTM0_C7SC_MASK)) | FTM0_C7SC_VALUE;
    #endif
  #elif defined(FTM0_C7SC_VALUE)
  FTM0_C7SC = FTM0_C7SC_VALUE;
  #endif

  /* Register 'FTM0_C0V' initialization */
  #if FTM0_C0V_MASK
    #if FTM0_C0V_MASK == 0xFFFFFFFF
  FTM0_C0V = FTM0_C0V_VALUE;
    #elif FTM0_C0V_MASK == FTM0_C0V_VALUE
  FTM0_C0V |= FTM0_C0V_VALUE;
    #elif FTM0_C0V_VALUE == 0
  FTM0_C0V &= ~FTM0_C0V_MASK;
    #else
  FTM0_C0V = (FTM0_C0V & (~FTM0_C0V_MASK)) | FTM0_C0V_VALUE;
    #endif
  #elif defined(FTM0_C0V_VALUE)
  FTM0_C0V = FTM0_C0V_VALUE;
  #endif

  /* Register 'FTM0_C1V' initialization */
  #if FTM0_C1V_MASK
    #if FTM0_C1V_MASK == 0xFFFFFFFF
  FTM0_C1V = FTM0_C1V_VALUE;
    #elif FTM0_C1V_MASK == FTM0_C1V_VALUE
  FTM0_C1V |= FTM0_C1V_VALUE;
    #elif FTM0_C1V_VALUE == 0
  FTM0_C1V &= ~FTM0_C1V_MASK;
    #else
  FTM0_C1V = (FTM0_C1V & (~FTM0_C1V_MASK)) | FTM0_C1V_VALUE;
    #endif
  #elif defined(FTM0_C1V_VALUE)
  FTM0_C1V = FTM0_C1V_VALUE;
  #endif

  /* Register 'FTM0_C2V' initialization */
  #if FTM0_C2V_MASK
    #if FTM0_C2V_MASK == 0xFFFFFFFF
  FTM0_C2V = FTM0_C2V_VALUE;
    #elif FTM0_C2V_MASK == FTM0_C2V_VALUE
  FTM0_C2V |= FTM0_C2V_VALUE;
    #elif FTM0_C2V_VALUE == 0
  FTM0_C2V &= ~FTM0_C2V_MASK;
    #else
  FTM0_C2V = (FTM0_C2V & (~FTM0_C2V_MASK)) | FTM0_C2V_VALUE;
    #endif
  #elif defined(FTM0_C2V_VALUE)
  FTM0_C2V = FTM0_C2V_VALUE;
  #endif

  /* Register 'FTM0_C3V' initialization */
  #if FTM0_C3V_MASK
    #if FTM0_C3V_MASK == 0xFFFFFFFF
  FTM0_C3V = FTM0_C3V_VALUE;
    #elif FTM0_C3V_MASK == FTM0_C3V_VALUE
  FTM0_C3V |= FTM0_C3V_VALUE;
    #elif FTM0_C3V_VALUE == 0
  FTM0_C3V &= ~FTM0_C3V_MASK;
    #else
  FTM0_C3V = (FTM0_C3V & (~FTM0_C3V_MASK)) | FTM0_C3V_VALUE;
    #endif
  #elif defined(FTM0_C3V_VALUE)
  FTM0_C3V = FTM0_C3V_VALUE;
  #endif

  /* Register 'FTM0_C4V' initialization */
  #if FTM0_C4V_MASK
    #if FTM0_C4V_MASK == 0xFFFFFFFF
  FTM0_C4V = FTM0_C4V_VALUE;
    #elif FTM0_C4V_MASK == FTM0_C4V_VALUE
  FTM0_C4V |= FTM0_C4V_VALUE;
    #elif FTM0_C4V_VALUE == 0
  FTM0_C4V &= ~FTM0_C4V_MASK;
    #else
  FTM0_C4V = (FTM0_C4V & (~FTM0_C4V_MASK)) | FTM0_C4V_VALUE;
    #endif
  #elif defined(FTM0_C4V_VALUE)
  FTM0_C4V = FTM0_C4V_VALUE;
  #endif

  /* Register 'FTM0_C5V' initialization */
  #if FTM0_C5V_MASK
    #if FTM0_C5V_MASK == 0xFFFFFFFF
  FTM0_C5V = FTM0_C5V_VALUE;
    #elif FTM0_C5V_MASK == FTM0_C5V_VALUE
  FTM0_C5V |= FTM0_C5V_VALUE;
    #elif FTM0_C5V_VALUE == 0
  FTM0_C5V &= ~FTM0_C5V_MASK;
    #else
  FTM0_C5V = (FTM0_C5V & (~FTM0_C5V_MASK)) | FTM0_C5V_VALUE;
    #endif
  #elif defined(FTM0_C5V_VALUE)
  FTM0_C5V = FTM0_C5V_VALUE;
  #endif

  /* Register 'FTM0_C6V' initialization */
  #if FTM0_C6V_MASK
    #if FTM0_C6V_MASK == 0xFFFFFFFF
  FTM0_C6V = FTM0_C6V_VALUE;
    #elif FTM0_C6V_MASK == FTM0_C6V_VALUE
  FTM0_C6V |= FTM0_C6V_VALUE;
    #elif FTM0_C6V_VALUE == 0
  FTM0_C6V &= ~FTM0_C6V_MASK;
    #else
  FTM0_C6V = (FTM0_C6V & (~FTM0_C6V_MASK)) | FTM0_C6V_VALUE;
    #endif
  #elif defined(FTM0_C6V_VALUE)
  FTM0_C6V = FTM0_C6V_VALUE;
  #endif

  /* Register 'FTM0_C7V' initialization */
  #if FTM0_C7V_MASK
    #if FTM0_C7V_MASK == 0xFFFFFFFF
  FTM0_C7V = FTM0_C7V_VALUE;
    #elif FTM0_C7V_MASK == FTM0_C7V_VALUE
  FTM0_C7V |= FTM0_C7V_VALUE;
    #elif FTM0_C7V_VALUE == 0
  FTM0_C7V &= ~FTM0_C7V_MASK;
    #else
  FTM0_C7V = (FTM0_C7V & (~FTM0_C7V_MASK)) | FTM0_C7V_VALUE;
    #endif
  #elif defined(FTM0_C7V_VALUE)
  FTM0_C7V = FTM0_C7V_VALUE;
  #endif

  /* Register 'FTM0_POL' initialization */
  #if FTM0_POL_MASK
    #if FTM0_POL_MASK == 0xFFFFFFFF
  FTM0_POL = FTM0_POL_VALUE;
    #elif FTM0_POL_MASK == FTM0_POL_VALUE
  FTM0_POL |= FTM0_POL_VALUE;
    #elif FTM0_POL_VALUE == 0
  FTM0_POL &= ~FTM0_POL_MASK;
    #else
  FTM0_POL = (FTM0_POL & (~FTM0_POL_MASK)) | FTM0_POL_VALUE;
    #endif
  #elif defined(FTM0_POL_VALUE)
  FTM0_POL = FTM0_POL_VALUE;
  #endif

  /* Register 'FTM0_FILTER' initialization */
  #if FTM0_FILTER_MASK
    #if FTM0_FILTER_MASK == 0xFFFFFFFF
  FTM0_FILTER = FTM0_FILTER_VALUE;
    #elif FTM0_FILTER_MASK == FTM0_FILTER_VALUE
  FTM0_FILTER |= FTM0_FILTER_VALUE;
    #elif FTM0_FILTER_VALUE == 0
  FTM0_FILTER &= ~FTM0_FILTER_MASK;
    #else
  FTM0_FILTER = (FTM0_FILTER & (~FTM0_FILTER_MASK)) | FTM0_FILTER_VALUE;
    #endif
  #elif defined(FTM0_FILTER_VALUE)
  FTM0_FILTER = FTM0_FILTER_VALUE;
  #endif

  /* Register 'FTM0_OUTINIT' initialization */
  #if FTM0_OUTINIT_MASK
    #if FTM0_OUTINIT_MASK == 0xFFFFFFFF
  FTM0_OUTINIT = FTM0_OUTINIT_VALUE;
    #elif FTM0_OUTINIT_MASK == FTM0_OUTINIT_VALUE
  FTM0_OUTINIT |= FTM0_OUTINIT_VALUE;
    #elif FTM0_OUTINIT_VALUE == 0
  FTM0_OUTINIT &= ~FTM0_OUTINIT_MASK;
    #else
  FTM0_OUTINIT = (FTM0_OUTINIT & (~FTM0_OUTINIT_MASK)) | FTM0_OUTINIT_VALUE;
    #endif
  #elif defined(FTM0_OUTINIT_VALUE)
  FTM0_OUTINIT = FTM0_OUTINIT_VALUE;
  #endif

  /* Register 'FTM0_OUTMASK' initialization */
  #if FTM0_OUTMASK_MASK
    #if FTM0_OUTMASK_MASK == 0xFFFFFFFF
  FTM0_OUTMASK = FTM0_OUTMASK_VALUE;
    #elif FTM0_OUTMASK_MASK == FTM0_OUTMASK_VALUE
  FTM0_OUTMASK |= FTM0_OUTMASK_VALUE;
    #elif FTM0_OUTMASK_VALUE == 0
  FTM0_OUTMASK &= ~FTM0_OUTMASK_MASK;
    #else
  FTM0_OUTMASK = (FTM0_OUTMASK & (~FTM0_OUTMASK_MASK)) | FTM0_OUTMASK_VALUE;
    #endif
  #elif defined(FTM0_OUTMASK_VALUE)
  FTM0_OUTMASK = FTM0_OUTMASK_VALUE;
  #endif

  /* Register 'FTM0_FLTCTRL' initialization */
  #if FTM0_FLTCTRL_MASK_1
    #if FTM0_FLTCTRL_MASK_1 == 0xFFFFFFFF
  FTM0_FLTCTRL = FTM0_FLTCTRL_VALUE_1;
    #elif FTM0_FLTCTRL_MASK_1 == FTM0_FLTCTRL_VALUE_1
  FTM0_FLTCTRL |= FTM0_FLTCTRL_VALUE_1;
    #elif FTM0_FLTCTRL_VALUE_1 == 0
  FTM0_FLTCTRL &= ~FTM0_FLTCTRL_MASK_1;
    #else
  FTM0_FLTCTRL = (FTM0_FLTCTRL & (~FTM0_FLTCTRL_MASK_1)) | FTM0_FLTCTRL_VALUE_1;
    #endif
  #elif defined(FTM0_FLTCTRL_VALUE_1)
  FTM0_FLTCTRL = FTM0_FLTCTRL_VALUE_1;
  #endif

  /* Register 'FTM0_FLTPOL' initialization */
  #if FTM0_FLTPOL_MASK
    #if FTM0_FLTPOL_MASK == 0xFFFFFFFF
  FTM0_FLTPOL = FTM0_FLTPOL_VALUE;
    #elif FTM0_FLTPOL_MASK == FTM0_FLTPOL_VALUE
  FTM0_FLTPOL |= FTM0_FLTPOL_VALUE;
    #elif FTM0_FLTPOL_VALUE == 0
  FTM0_FLTPOL &= ~FTM0_FLTPOL_MASK;
    #else
  FTM0_FLTPOL = (FTM0_FLTPOL & (~FTM0_FLTPOL_MASK)) | FTM0_FLTPOL_VALUE;
    #endif
  #elif defined(FTM0_FLTPOL_VALUE)
  FTM0_FLTPOL = FTM0_FLTPOL_VALUE;
  #endif

  /* Register 'FTM0_FLTCTRL' initialization */
  #if FTM0_FLTCTRL_MASK_2
    #if FTM0_FLTCTRL_MASK_2 == 0xFFFFFFFF
  FTM0_FLTCTRL = FTM0_FLTCTRL_VALUE_2;
    #elif FTM0_FLTCTRL_MASK_2 == FTM0_FLTCTRL_VALUE_2
  FTM0_FLTCTRL |= FTM0_FLTCTRL_VALUE_2;
    #elif FTM0_FLTCTRL_VALUE_2 == 0
  FTM0_FLTCTRL &= ~FTM0_FLTCTRL_MASK_2;
    #else
  FTM0_FLTCTRL = (FTM0_FLTCTRL & (~FTM0_FLTCTRL_MASK_2)) | FTM0_FLTCTRL_VALUE_2;
    #endif
  #elif defined(FTM0_FLTCTRL_VALUE_2)
  FTM0_FLTCTRL = FTM0_FLTCTRL_VALUE_2;
  #endif

  /* Register 'FTM0_SYNC' initialization */
  #if FTM0_SYNC_MASK
    #if FTM0_SYNC_MASK == 0xFFFFFFFF
  FTM0_SYNC = FTM0_SYNC_VALUE;
    #elif FTM0_SYNC_MASK == FTM0_SYNC_VALUE
  FTM0_SYNC |= FTM0_SYNC_VALUE;
    #elif FTM0_SYNC_VALUE == 0
  FTM0_SYNC &= ~FTM0_SYNC_MASK;
    #else
  FTM0_SYNC = (FTM0_SYNC & (~FTM0_SYNC_MASK)) | FTM0_SYNC_VALUE;
    #endif
  #elif defined(FTM0_SYNC_VALUE)
  FTM0_SYNC = FTM0_SYNC_VALUE;
  #endif

  /* Register 'FTM0_EXTTRIG' initialization */
  #if FTM0_EXTTRIG_MASK
    #if FTM0_EXTTRIG_MASK == 0xFFFFFFFF
  FTM0_EXTTRIG = FTM0_EXTTRIG_VALUE;
    #elif FTM0_EXTTRIG_MASK == FTM0_EXTTRIG_VALUE
  FTM0_EXTTRIG |= FTM0_EXTTRIG_VALUE;
    #elif FTM0_EXTTRIG_VALUE == 0
  FTM0_EXTTRIG &= ~FTM0_EXTTRIG_MASK;
    #else
  FTM0_EXTTRIG = (FTM0_EXTTRIG & (~FTM0_EXTTRIG_MASK)) | FTM0_EXTTRIG_VALUE;
    #endif
  #elif defined(FTM0_EXTTRIG_VALUE)
  FTM0_EXTTRIG = FTM0_EXTTRIG_VALUE;
  #endif

  /* Register 'FTM0_MOD' initialization */
  #if FTM0_MOD_MASK
    #if FTM0_MOD_MASK == 0xFFFFFFFF
  FTM0_MOD = FTM0_MOD_VALUE;
    #elif FTM0_MOD_MASK == FTM0_MOD_VALUE
  FTM0_MOD |= FTM0_MOD_VALUE;
    #elif FTM0_MOD_VALUE == 0
  FTM0_MOD &= ~FTM0_MOD_MASK;
    #else
  FTM0_MOD = (FTM0_MOD & (~FTM0_MOD_MASK)) | FTM0_MOD_VALUE;
    #endif
  #elif defined(FTM0_MOD_VALUE)
  FTM0_MOD = FTM0_MOD_VALUE;
  #endif

  /* Register 'FTM0_CNTIN' initialization */
  #if FTM0_CNTIN_MASK
    #if FTM0_CNTIN_MASK == 0xFFFFFFFF
  FTM0_CNTIN = FTM0_CNTIN_VALUE;
    #elif FTM0_CNTIN_MASK == FTM0_CNTIN_VALUE
  FTM0_CNTIN |= FTM0_CNTIN_VALUE;
    #elif FTM0_CNTIN_VALUE == 0
  FTM0_CNTIN &= ~FTM0_CNTIN_MASK;
    #else
  FTM0_CNTIN = (FTM0_CNTIN & (~FTM0_CNTIN_MASK)) | FTM0_CNTIN_VALUE;
    #endif
  #elif defined(FTM0_CNTIN_VALUE)
  FTM0_CNTIN = FTM0_CNTIN_VALUE;
  #endif

  /* Register 'FTM0_DEADTIME' initialization */
  #if FTM0_DEADTIME_MASK
    #if FTM0_DEADTIME_MASK == 0xFFFFFFFF
  FTM0_DEADTIME = FTM0_DEADTIME_VALUE;
    #elif FTM0_DEADTIME_MASK == FTM0_DEADTIME_VALUE
  FTM0_DEADTIME |= FTM0_DEADTIME_VALUE;
    #elif FTM0_DEADTIME_VALUE == 0
  FTM0_DEADTIME &= ~FTM0_DEADTIME_MASK;
    #else
  FTM0_DEADTIME = (FTM0_DEADTIME & (~FTM0_DEADTIME_MASK)) | FTM0_DEADTIME_VALUE;
    #endif
  #elif defined(FTM0_DEADTIME_VALUE)
  FTM0_DEADTIME = FTM0_DEADTIME_VALUE;
  #endif

  FTM0_CNT &= ~0xFFFF;

  /* Register 'FTM0_MODE' initialization */
  #if FTM0_MODE_MASK_3
    #if FTM0_MODE_MASK_3 == 0xFFFFFFFF
  FTM0_MODE = FTM0_MODE_VALUE_3;
    #elif FTM0_MODE_MASK_3 == FTM0_MODE_VALUE_3
  FTM0_MODE |= FTM0_MODE_VALUE_3;
    #elif FTM0_MODE_VALUE_3 == 0
  FTM0_MODE &= ~FTM0_MODE_MASK_3;
    #else
  FTM0_MODE = (FTM0_MODE & (~FTM0_MODE_MASK_3)) | FTM0_MODE_VALUE_3;
    #endif
  #elif defined(FTM0_MODE_VALUE_3)
  FTM0_MODE = FTM0_MODE_VALUE_3;
  #endif

  /* Register 'FTM0_SYNCONF' initialization */
  #if FTM0_SYNCONF_MASK
    #if FTM0_SYNCONF_MASK == 0xFFFFFFFF
  FTM0_SYNCONF = FTM0_SYNCONF_VALUE;
    #elif FTM0_SYNCONF_MASK == FTM0_SYNCONF_VALUE
  FTM0_SYNCONF |= FTM0_SYNCONF_VALUE;
    #elif FTM0_SYNCONF_VALUE == 0
  FTM0_SYNCONF &= ~FTM0_SYNCONF_MASK;
    #else
  FTM0_SYNCONF = (FTM0_SYNCONF & (~FTM0_SYNCONF_MASK)) | FTM0_SYNCONF_VALUE;
    #endif
  #elif defined(FTM0_SYNCONF_VALUE)
  FTM0_SYNCONF = FTM0_SYNCONF_VALUE;
  #endif

  /* Register 'FTM0_SC' initialization */
  #if FTM0_SC_MASK_3
    #if FTM0_SC_MASK_3 == 0xFFFFFFFF
  FTM0_SC = FTM0_SC_VALUE_3;
    #elif FTM0_SC_MASK_3 == FTM0_SC_VALUE_3
  FTM0_SC |= FTM0_SC_VALUE_3;
    #elif FTM0_SC_VALUE_3 == 0
  FTM0_SC &= ~FTM0_SC_MASK_3;
    #else
  FTM0_SC = (FTM0_SC & (~FTM0_SC_MASK_3)) | FTM0_SC_VALUE_3;
    #endif
  #elif defined(FTM0_SC_VALUE_3)
  FTM0_SC = FTM0_SC_VALUE_3;
  #endif

  /* Register 'FTM0_FMS' initialization */
  #if FTM0_FMS_MASK
    #if FTM0_FMS_MASK == 0xFFFFFFFF
  FTM0_FMS = FTM0_FMS_VALUE;
    #elif FTM0_FMS_MASK == FTM0_FMS_VALUE
  FTM0_FMS |= FTM0_FMS_VALUE;
    #elif FTM0_FMS_VALUE == 0
  FTM0_FMS &= ~FTM0_FMS_MASK;
    #else
  FTM0_FMS = (FTM0_FMS & (~FTM0_FMS_MASK)) | FTM0_FMS_VALUE;
    #endif
  #elif defined(FTM0_FMS_VALUE)
  FTM0_FMS = FTM0_FMS_VALUE;
  #endif

  /* Register 'FTM0_SWOCTRL' initialization */
  #if FTM0_SWOCTRL_MASK
    #if FTM0_SWOCTRL_MASK == 0xFFFFFFFF
  FTM0_SWOCTRL = FTM0_SWOCTRL_VALUE;
    #elif FTM0_SWOCTRL_MASK == FTM0_SWOCTRL_VALUE
  FTM0_SWOCTRL |= FTM0_SWOCTRL_VALUE;
    #elif FTM0_SWOCTRL_VALUE == 0
  FTM0_SWOCTRL &= ~FTM0_SWOCTRL_MASK;
    #else
  FTM0_SWOCTRL = (FTM0_SWOCTRL & (~FTM0_SWOCTRL_MASK)) | FTM0_SWOCTRL_VALUE;
    #endif
  #elif defined(FTM0_SWOCTRL_VALUE)
  FTM0_SWOCTRL = FTM0_SWOCTRL_VALUE;
  #endif

  /* Register 'FTM0_CONF' initialization */
  #if FTM0_CONF_MASK
    #if FTM0_CONF_MASK == 0xFFFFFFFF
  FTM0_CONF = FTM0_CONF_VALUE;
    #elif FTM0_CONF_MASK == FTM0_CONF_VALUE
  FTM0_CONF |= FTM0_CONF_VALUE;
    #elif FTM0_CONF_VALUE == 0
  FTM0_CONF &= ~FTM0_CONF_MASK;
    #else
  FTM0_CONF = (FTM0_CONF & (~FTM0_CONF_MASK)) | FTM0_CONF_VALUE;
    #endif
  #elif defined(FTM0_CONF_VALUE)
  FTM0_CONF = FTM0_CONF_VALUE;
  #endif

  /* Register 'FTM0_PWMLOAD' initialization */
  #if FTM0_PWMLOAD_MASK
    #if FTM0_PWMLOAD_MASK == 0xFFFFFFFF
  FTM0_PWMLOAD = FTM0_PWMLOAD_VALUE;
    #elif FTM0_PWMLOAD_MASK == FTM0_PWMLOAD_VALUE
  FTM0_PWMLOAD |= FTM0_PWMLOAD_VALUE;
    #elif FTM0_PWMLOAD_VALUE == 0
  FTM0_PWMLOAD &= ~FTM0_PWMLOAD_MASK;
    #else
  FTM0_PWMLOAD = (FTM0_PWMLOAD & (~FTM0_PWMLOAD_MASK)) | FTM0_PWMLOAD_VALUE;
    #endif
  #elif defined(FTM0_PWMLOAD_VALUE)
  FTM0_PWMLOAD = FTM0_PWMLOAD_VALUE;
  #endif
}

#ifdef __cplusplus
}
#endif

/* END FTM0_Init. */

/** ###################################################################
 **
 **     This file is a part of Processor Expert static initialization
 **     library for Freescale microcontrollers.
 **
 ** ################################################################### */

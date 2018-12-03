/** ###################################################################
 **     Filename    : PTE_Init.c
 **     Processor   : MK64FN1M0LQ12
 **     Abstract    :
 **          This file implements the PTE module initialization
 **          according to the Peripheral Initialization settings, and
 **          defines interrupt service routines prototypes.
 **
 **     Contents    :
 **         Int   - void PTE_Init(void);
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
 * @file PTE_Init.c
 * @brief This file implements the PTE module initialization according to the
 *        Peripheral Initialization settings, and defines interrupt service
 *        routines prototypes.
 */


/* MODULE PTE_Init. */

#include "PTE_Init.h"
#include "MK64F12.h"
#include "Init_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

void PTE_Init(void) {

  /* Register 'GPIOE_PSOR' initialization */
  #if GPIOE_PSOR_MASK
    #if GPIOE_PSOR_MASK == 0xFFFFFFFF
  GPIOE_PSOR = GPIOE_PSOR_VALUE;
    #elif GPIOE_PSOR_MASK == GPIOE_PSOR_VALUE
  GPIOE_PSOR |= GPIOE_PSOR_VALUE;
    #elif GPIOE_PSOR_VALUE == 0
  GPIOE_PSOR &= ~GPIOE_PSOR_MASK;
    #else
  GPIOE_PSOR = (GPIOE_PSOR & (~GPIOE_PSOR_MASK)) | GPIOE_PSOR_VALUE;
    #endif
  #elif defined(GPIOE_PSOR_VALUE)
  GPIOE_PSOR = GPIOE_PSOR_VALUE;
  #endif

  /* Register 'GPIOE_PCOR' initialization */
  #if GPIOE_PCOR_MASK
    #if GPIOE_PCOR_MASK == 0xFFFFFFFF
  GPIOE_PCOR = GPIOE_PCOR_VALUE;
    #elif GPIOE_PCOR_MASK == GPIOE_PCOR_VALUE
  GPIOE_PCOR |= GPIOE_PCOR_VALUE;
    #elif GPIOE_PCOR_VALUE == 0
  GPIOE_PCOR &= ~GPIOE_PCOR_MASK;
    #else
  GPIOE_PCOR = (GPIOE_PCOR & (~GPIOE_PCOR_MASK)) | GPIOE_PCOR_VALUE;
    #endif
  #elif defined(GPIOE_PCOR_VALUE)
  GPIOE_PCOR = GPIOE_PCOR_VALUE;
  #endif

  /* Register 'GPIOE_PDDR' initialization */
  #if GPIOE_PDDR_MASK
    #if GPIOE_PDDR_MASK == 0xFFFFFFFF
  GPIOE_PDDR = GPIOE_PDDR_VALUE;
    #elif GPIOE_PDDR_MASK == GPIOE_PDDR_VALUE
  GPIOE_PDDR |= GPIOE_PDDR_VALUE;
    #elif GPIOE_PDDR_VALUE == 0
  GPIOE_PDDR &= ~GPIOE_PDDR_MASK;
    #else
  GPIOE_PDDR = (GPIOE_PDDR & (~GPIOE_PDDR_MASK)) | GPIOE_PDDR_VALUE;
    #endif
  #elif defined(GPIOE_PDDR_VALUE)
  GPIOE_PDDR = GPIOE_PDDR_VALUE;
  #endif


}

#ifdef __cplusplus
}
#endif

/* END PTE_Init. */

/** ###################################################################
 **
 **     This file is a part of Processor Expert static initialization
 **     library for Freescale microcontrollers.
 **
 ** ################################################################### */

/** ###################################################################
 **     Filename    : PTA_Init.c
 **     Processor   : MK22FN512LH12
 **     Abstract    :
 **          This file implements the PTA module initialization
 **          according to the Peripheral Initialization settings, and
 **          defines interrupt service routines prototypes.
 **
 **     Contents    :
 **         Int   - void PTA_Init(void);
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
 * @file PTA_Init.c
 * @brief This file implements the PTA module initialization according to the
 *        Peripheral Initialization settings, and defines interrupt service
 *        routines prototypes.
 */


/* MODULE PTA_Init. */

#include "PTA_Init.h"
#include "MK22F51212.h"
#include "Init_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

void PTA_Init(void) {

  /* Register 'GPIOA_PSOR' initialization */
  #if GPIOA_PSOR_MASK
    #if GPIOA_PSOR_MASK == 0xFFFFFFFF
  GPIOA_PSOR = GPIOA_PSOR_VALUE;
    #elif GPIOA_PSOR_MASK == GPIOA_PSOR_VALUE
  GPIOA_PSOR |= GPIOA_PSOR_VALUE;
    #elif GPIOA_PSOR_VALUE == 0
  GPIOA_PSOR &= ~GPIOA_PSOR_MASK;
    #else
  GPIOA_PSOR = (GPIOA_PSOR & (~GPIOA_PSOR_MASK)) | GPIOA_PSOR_VALUE;
    #endif
  #elif defined(GPIOA_PSOR_VALUE)
  GPIOA_PSOR = GPIOA_PSOR_VALUE;
  #endif

  /* Register 'GPIOA_PCOR' initialization */
  #if GPIOA_PCOR_MASK
    #if GPIOA_PCOR_MASK == 0xFFFFFFFF
  GPIOA_PCOR = GPIOA_PCOR_VALUE;
    #elif GPIOA_PCOR_MASK == GPIOA_PCOR_VALUE
  GPIOA_PCOR |= GPIOA_PCOR_VALUE;
    #elif GPIOA_PCOR_VALUE == 0
  GPIOA_PCOR &= ~GPIOA_PCOR_MASK;
    #else
  GPIOA_PCOR = (GPIOA_PCOR & (~GPIOA_PCOR_MASK)) | GPIOA_PCOR_VALUE;
    #endif
  #elif defined(GPIOA_PCOR_VALUE)
  GPIOA_PCOR = GPIOA_PCOR_VALUE;
  #endif

  /* Register 'GPIOA_PDDR' initialization */
  #if GPIOA_PDDR_MASK
    #if GPIOA_PDDR_MASK == 0xFFFFFFFF
  GPIOA_PDDR = GPIOA_PDDR_VALUE;
    #elif GPIOA_PDDR_MASK == GPIOA_PDDR_VALUE
  GPIOA_PDDR |= GPIOA_PDDR_VALUE;
    #elif GPIOA_PDDR_VALUE == 0
  GPIOA_PDDR &= ~GPIOA_PDDR_MASK;
    #else
  GPIOA_PDDR = (GPIOA_PDDR & (~GPIOA_PDDR_MASK)) | GPIOA_PDDR_VALUE;
    #endif
  #elif defined(GPIOA_PDDR_VALUE)
  GPIOA_PDDR = GPIOA_PDDR_VALUE;
  #endif


}

#ifdef __cplusplus
}
#endif

/* END PTA_Init. */

/** ###################################################################
 **
 **     This file is a part of Processor Expert static initialization
 **     library for Freescale microcontrollers.
 **
 ** ################################################################### */

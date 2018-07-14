/** ###################################################################
 **     Filename    : PTD_Init.c
 **     Processor   : MK22FN512DC12
 **     Abstract    :
 **          This file implements the PTD module initialization
 **          according to the Peripheral Initialization settings, and
 **          defines interrupt service routines prototypes.
 **
 **     Contents    :
 **         Int   - void PTD_Init(void);
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
 * @file PTD_Init.c
 * @brief This file implements the PTD module initialization according to the
 *        Peripheral Initialization settings, and defines interrupt service
 *        routines prototypes.
 */


/* MODULE PTD_Init. */

#include "PTD_Init.h"
#include "MK22F51212.h"
#include "Init_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

void PTD_Init(void) {

  /* Register 'GPIOD_PSOR' initialization */
  #if GPIOD_PSOR_MASK
    #if GPIOD_PSOR_MASK == 0xFFFFFFFF
  GPIOD_PSOR = GPIOD_PSOR_VALUE;
    #elif GPIOD_PSOR_MASK == GPIOD_PSOR_VALUE
  GPIOD_PSOR |= GPIOD_PSOR_VALUE;
    #elif GPIOD_PSOR_VALUE == 0
  GPIOD_PSOR &= ~GPIOD_PSOR_MASK;
    #else
  GPIOD_PSOR = (GPIOD_PSOR & (~GPIOD_PSOR_MASK)) | GPIOD_PSOR_VALUE;
    #endif
  #elif defined(GPIOD_PSOR_VALUE)
  GPIOD_PSOR = GPIOD_PSOR_VALUE;
  #endif

  /* Register 'GPIOD_PCOR' initialization */
  #if GPIOD_PCOR_MASK
    #if GPIOD_PCOR_MASK == 0xFFFFFFFF
  GPIOD_PCOR = GPIOD_PCOR_VALUE;
    #elif GPIOD_PCOR_MASK == GPIOD_PCOR_VALUE
  GPIOD_PCOR |= GPIOD_PCOR_VALUE;
    #elif GPIOD_PCOR_VALUE == 0
  GPIOD_PCOR &= ~GPIOD_PCOR_MASK;
    #else
  GPIOD_PCOR = (GPIOD_PCOR & (~GPIOD_PCOR_MASK)) | GPIOD_PCOR_VALUE;
    #endif
  #elif defined(GPIOD_PCOR_VALUE)
  GPIOD_PCOR = GPIOD_PCOR_VALUE;
  #endif

  /* Register 'GPIOD_PDDR' initialization */
  #if GPIOD_PDDR_MASK
    #if GPIOD_PDDR_MASK == 0xFFFFFFFF
  GPIOD_PDDR = GPIOD_PDDR_VALUE;
    #elif GPIOD_PDDR_MASK == GPIOD_PDDR_VALUE
  GPIOD_PDDR |= GPIOD_PDDR_VALUE;
    #elif GPIOD_PDDR_VALUE == 0
  GPIOD_PDDR &= ~GPIOD_PDDR_MASK;
    #else
  GPIOD_PDDR = (GPIOD_PDDR & (~GPIOD_PDDR_MASK)) | GPIOD_PDDR_VALUE;
    #endif
  #elif defined(GPIOD_PDDR_VALUE)
  GPIOD_PDDR = GPIOD_PDDR_VALUE;
  #endif


}

#ifdef __cplusplus
}
#endif

/* END PTD_Init. */

/** ###################################################################
 **
 **     This file is a part of Processor Expert static initialization
 **     library for Freescale microcontrollers.
 **
 ** ################################################################### */

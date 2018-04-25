/** ###################################################################
 **     Filename    : USB0_Init.c
 **     Processor   : MK22FN512LH12
 **     Abstract    :
 **          This file implements the USB0 module initialization
 **          according to the Peripheral Initialization settings, and
 **          defines interrupt service routines prototypes.
 **
 **     Contents    :
 **         Int   - void USB0_Init(void);
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
 * @file USB0_Init.c
 * @brief This file implements the USB0 module initialization according to the
 *        Peripheral Initialization settings, and defines interrupt service
 *        routines prototypes.
 */


/* MODULE USB0_Init. */

#include "USB0_Init.h"
#include "MK22F51212.h"
#include "Init_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

void USB0_Init(void) {

  /* Register 'USB0_CTL' initialization */
  #if USB0_CTL_MASK_1
    #if USB0_CTL_MASK_1 == 0xFF
  USB0_CTL = USB0_CTL_VALUE_1;
    #elif USB0_CTL_MASK_1 == USB0_CTL_VALUE_1
  USB0_CTL |= USB0_CTL_VALUE_1;
    #elif USB0_CTL_VALUE_1 == 0
  USB0_CTL &= ~USB0_CTL_MASK_1;
    #else
  USB0_CTL = (USB0_CTL & (~USB0_CTL_MASK_1)) | USB0_CTL_VALUE_1;
    #endif
  #elif defined(USB0_CTL_VALUE_1)
  USB0_CTL = USB0_CTL_VALUE_1;
  #endif

  /* Register 'USB0_CLK_RECOVER_IRC_EN' initialization */
  #if USB0_CLK_RECOVER_IRC_EN_MASK
    #if USB0_CLK_RECOVER_IRC_EN_MASK == 0xFF
  USB0_CLK_RECOVER_IRC_EN = USB0_CLK_RECOVER_IRC_EN_VALUE;
    #elif USB0_CLK_RECOVER_IRC_EN_MASK == USB0_CLK_RECOVER_IRC_EN_VALUE
  USB0_CLK_RECOVER_IRC_EN |= USB0_CLK_RECOVER_IRC_EN_VALUE;
    #elif USB0_CLK_RECOVER_IRC_EN_VALUE == 0
  USB0_CLK_RECOVER_IRC_EN &= ~USB0_CLK_RECOVER_IRC_EN_MASK;
    #else
  USB0_CLK_RECOVER_IRC_EN = (USB0_CLK_RECOVER_IRC_EN & (~USB0_CLK_RECOVER_IRC_EN_MASK)) | USB0_CLK_RECOVER_IRC_EN_VALUE;
    #endif
  #elif defined(USB0_CLK_RECOVER_IRC_EN_VALUE)
  USB0_CLK_RECOVER_IRC_EN = USB0_CLK_RECOVER_IRC_EN_VALUE;
  #endif

  /* Register 'USB0_CLK_RECOVER_CTRL' initialization */
  #if USB0_CLK_RECOVER_CTRL_MASK
    #if USB0_CLK_RECOVER_CTRL_MASK == 0xFF
  USB0_CLK_RECOVER_CTRL = USB0_CLK_RECOVER_CTRL_VALUE;
    #elif USB0_CLK_RECOVER_CTRL_MASK == USB0_CLK_RECOVER_CTRL_VALUE
  USB0_CLK_RECOVER_CTRL |= USB0_CLK_RECOVER_CTRL_VALUE;
    #elif USB0_CLK_RECOVER_CTRL_VALUE == 0
  USB0_CLK_RECOVER_CTRL &= ~USB0_CLK_RECOVER_CTRL_MASK;
    #else
  USB0_CLK_RECOVER_CTRL = (USB0_CLK_RECOVER_CTRL & (~USB0_CLK_RECOVER_CTRL_MASK)) | USB0_CLK_RECOVER_CTRL_VALUE;
    #endif
  #elif defined(USB0_CLK_RECOVER_CTRL_VALUE)
  USB0_CLK_RECOVER_CTRL = USB0_CLK_RECOVER_CTRL_VALUE;
  #endif

  /* Register 'USB0_USBCTRL' initialization */
  #ifdef USB0_USBCTRL_VALUE
  USB0_USBCTRL = USB0_USBCTRL_VALUE;
  #endif

  /* Register 'USB0_OTGISTAT' initialization */
  #ifdef USB0_OTGISTAT_VALUE
  USB0_OTGISTAT = USB0_OTGISTAT_VALUE;
  #endif

  /* Register 'USB0_ISTAT' initialization */
  #ifdef USB0_ISTAT_VALUE
  USB0_ISTAT = USB0_ISTAT_VALUE;
  #endif

  /* Register 'USB0_ERRSTAT' initialization */
  #ifdef USB0_ERRSTAT_VALUE
  USB0_ERRSTAT = USB0_ERRSTAT_VALUE;
  #endif

  /* Register 'USB0_INTEN' initialization */
  #ifdef USB0_INTEN_VALUE
  USB0_INTEN = USB0_INTEN_VALUE;
  #endif

  /* Register 'USB0_ERREN' initialization */
  #ifdef USB0_ERREN_VALUE
  USB0_ERREN = USB0_ERREN_VALUE;
  #endif

  /* Register 'USB0_USBTRC0' initialization */
  #ifdef USB0_USBTRC0_VALUE
  USB0_USBTRC0 = USB0_USBTRC0_VALUE;
  #endif

  /* Register 'USB0_OTGICR' initialization */
  #ifdef USB0_OTGICR_VALUE
  USB0_OTGICR = USB0_OTGICR_VALUE;
  #endif

  USB0_ADDR = 0;

  /* Register 'USB0_ENDPT0' initialization */
  #ifdef USB0_ENDPT0_VALUE
  USB0_ENDPT0 = USB0_ENDPT0_VALUE;
  #endif

  /* Register 'USB0_ENDPT1' initialization */
  #ifdef USB0_ENDPT1_VALUE
  USB0_ENDPT1 = USB0_ENDPT1_VALUE;
  #endif

  /* Register 'USB0_ENDPT2' initialization */
  #ifdef USB0_ENDPT2_VALUE
  USB0_ENDPT2 = USB0_ENDPT2_VALUE;
  #endif

  /* Register 'USB0_ENDPT3' initialization */
  #ifdef USB0_ENDPT3_VALUE
  USB0_ENDPT3 = USB0_ENDPT3_VALUE;
  #endif

  /* Register 'USB0_ENDPT4' initialization */
  #ifdef USB0_ENDPT4_VALUE
  USB0_ENDPT4 = USB0_ENDPT4_VALUE;
  #endif

  /* Register 'USB0_ENDPT5' initialization */
  #ifdef USB0_ENDPT5_VALUE
  USB0_ENDPT5 = USB0_ENDPT5_VALUE;
  #endif

  /* Register 'USB0_ENDPT6' initialization */
  #ifdef USB0_ENDPT6_VALUE
  USB0_ENDPT6 = USB0_ENDPT6_VALUE;
  #endif

  /* Register 'USB0_ENDPT7' initialization */
  #ifdef USB0_ENDPT7_VALUE
  USB0_ENDPT7 = USB0_ENDPT7_VALUE;
  #endif

  /* Register 'USB0_ENDPT8' initialization */
  #ifdef USB0_ENDPT8_VALUE
  USB0_ENDPT8 = USB0_ENDPT8_VALUE;
  #endif

  /* Register 'USB0_ENDPT9' initialization */
  #ifdef USB0_ENDPT9_VALUE
  USB0_ENDPT9 = USB0_ENDPT9_VALUE;
  #endif

  /* Register 'USB0_ENDPT10' initialization */
  #ifdef USB0_ENDPT10_VALUE
  USB0_ENDPT10 = USB0_ENDPT10_VALUE;
  #endif

  /* Register 'USB0_ENDPT11' initialization */
  #ifdef USB0_ENDPT11_VALUE
  USB0_ENDPT11 = USB0_ENDPT11_VALUE;
  #endif

  /* Register 'USB0_ENDPT12' initialization */
  #ifdef USB0_ENDPT12_VALUE
  USB0_ENDPT12 = USB0_ENDPT12_VALUE;
  #endif

  /* Register 'USB0_ENDPT13' initialization */
  #ifdef USB0_ENDPT13_VALUE
  USB0_ENDPT13 = USB0_ENDPT13_VALUE;
  #endif

  /* Register 'USB0_ENDPT14' initialization */
  #ifdef USB0_ENDPT14_VALUE
  USB0_ENDPT14 = USB0_ENDPT14_VALUE;
  #endif

  /* Register 'USB0_ENDPT15' initialization */
  #ifdef USB0_ENDPT15_VALUE
  USB0_ENDPT15 = USB0_ENDPT15_VALUE;
  #endif

  #ifdef USB0_BDTPAGE1_VALUE
  USB0_BDTPAGE1 = USB0_BDTPAGE1_VALUE;
  #endif

  #ifdef USB0_BDTPAGE2_VALUE
  USB0_BDTPAGE2 = USB0_BDTPAGE2_VALUE;
  #endif

  #ifdef USB0_BDTPAGE3_VALUE
  USB0_BDTPAGE3 = USB0_BDTPAGE3_VALUE;
  #endif

  /* Register 'USB0_SOFTHLD' initialization */
  #ifdef USB0_SOFTHLD_VALUE
  USB0_SOFTHLD = USB0_SOFTHLD_VALUE;
  #endif

  /* Register 'USB0_OTGCTL' initialization */
  #ifdef USB0_OTGCTL_VALUE
  USB0_OTGCTL = USB0_OTGCTL_VALUE;
  #endif

  /* Register 'USB0_CONTROL' initialization */
  #ifdef USB0_CONTROL_VALUE
  USB0_CONTROL = USB0_CONTROL_VALUE;
  #endif

  /* Register 'USB0_CTL' initialization */
  #if USB0_CTL_MASK_2
    #if USB0_CTL_MASK_2 == 0xFF
  USB0_CTL = USB0_CTL_VALUE_2;
    #elif USB0_CTL_MASK_2 == USB0_CTL_VALUE_2
  USB0_CTL |= USB0_CTL_VALUE_2;
    #elif USB0_CTL_VALUE_2 == 0
  USB0_CTL &= ~USB0_CTL_MASK_2;
    #else
  USB0_CTL = (USB0_CTL & (~USB0_CTL_MASK_2)) | USB0_CTL_VALUE_2;
    #endif
  #elif defined(USB0_CTL_VALUE_2)
  USB0_CTL = USB0_CTL_VALUE_2;
  #endif
}

#ifdef __cplusplus
}
#endif

/* END USB0_Init. */

/** ###################################################################
 **
 **     This file is a part of Processor Expert static initialization
 **     library for Freescale microcontrollers.
 **
 ** ################################################################### */

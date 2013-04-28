/*
 * Note: This file is recreated by the project wizard whenever the MCU is
 *       changed and should not be edited by hand
 */

/* Include the derivative-specific header file */
#if 0 /* << EST */
  #include <MCF52259.h>
#else
  #include "%ProcessorModule.h"
#endif
#include "psptypes.h"
#define _Stop asm ( mov3q #4,d0; bclr.b d0,SOPT1; stop #0x2000; )
  /*!< Macro to enter stop modes, STOPE bit in SOPT1 register must be set prior to executing this macro */

#define _Wait asm ( mov3q #4,d0; bset.b d0,SOPT1; nop; stop #0x2000; )
  /*!< Macro to enter wait mode */
#define __RESET_WATCHDOG() (void)(MCF_BWT_WSR = 0x5555, MCF_BWT_WSR = 0xAAAA)

#define USB_ISR_SRC    53
#define PIT1_ISR_SRC   56


#define PIT1_INT_CNTL   0   /* Coresponding assigned interrupt controller */
#define USB_INT_CNTL    0   /* Coresponding assigned interrupt controller */
	  
#define USE_POLL

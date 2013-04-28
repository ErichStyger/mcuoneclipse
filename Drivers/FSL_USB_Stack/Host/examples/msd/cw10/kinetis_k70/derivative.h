/*
 * Note: This file is recreated by the project wizard whenever the MCU is
 *       changed and should not be edited by hand
 */

/* Include the derivative-specific header file */
#if 0 /* << EST */
  #include <MK70F12.h>
#else
  #include "%ProcessorModule.h"
#endif

#define _MK_xxx_H_
#define USE_POLL
#define USE_PIT1

#define printf printf_kinetis
#define sprintf sprintf_kinetis
#define malloc malloc_aligned

#define ASYNCH_MODE    /* PLL1 is source for MCGCLKOUT and DDR controller */

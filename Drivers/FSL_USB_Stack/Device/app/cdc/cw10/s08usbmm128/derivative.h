/*
 * Note: This file is recreated by the project wizard whenever the MCU is
 *       changed and should not be edited by hand
 */

/* Include the derivative-specific header file */
#if 0 /* << EST */
#include <MC9S08MM128.h>
#else
  #include "%ProcessorModule.h"
#endif

#define _Stop asm ( stop; )
  /*!< Macro to enter stop modes, STOPE bit in SOPT1 register must be set prior to executing this macro */

#define _Wait asm ( wait; )
  /*!< Macro to enter wait mode */



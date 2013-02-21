/******************************************************/
/**
* @file hidef.h
* Machine/compiler dependent declarations.
*/
/*----------------------------------------------------
   Copyright (c) Freescale DevTech
               All rights reserved
                  Do not modify!
 *****************************************************/

#ifndef _H_HIDEF_
#define _H_HIDEF_

#ifdef __cplusplus
extern "C" {
#endif

#pragma gcc_extensions on

/**** Version for ColFire V1 */
#include <stddef.h>
#include "types.h"

#define EnableInterrupts asm { move.w SR,D0; andi.l #0xF8FF,D0; move.w D0,SR;  }
  /*!< Macro to enable all interrupts. */

#define DisableInterrupts asm { move.w SR,D0; ori.l #0x0700,D0; move.w D0,SR;  }
  /*!< Macro to disable all interrupts. */
  
#ifdef __cplusplus
 }
#endif

#endif

/*****************************************************/
/* end hidef.h */

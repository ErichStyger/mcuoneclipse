/** ###################################################################
**
**     (c) Freescale Semiconductor
**     2004 All Rights Reserved
**
**
**     Copyright : 1997 - 2012 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/*********************************************************
* This assert macro may be disabled and all generated code
* removed by uncommenting the
*
*               #define NO_ASSERT
*
* line in this file and recompiling all files using this
* macro including the SDK libraries. This technique may be
* used to reduce the overall program memory size once the
* application has been tested and is ready for production.
* The assumption is that this assert macro was used to flag
* invalid conditions such as bad function parameter values
* that have been verified not to exist through unit and
* integration testing. Since the assert mechanism only works
* when running in a debugging mode, it is safe to remove this
* code from a released application as it will not halt the
* system anyway. Applications should be retested after
* assertions are removed as the overall timing of the system
* will be affected by the removal of the associated code.
**********************************************************/
#ifndef __ASSERT_H
#define __ASSERT_H

/* #define NO_ASSERT */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************
* Replace MSL assert in order to bypass link bug
*******************************************************/

#ifdef assert
#undef assert
#endif



#ifdef NO_ASSERT
#  define assert(assertion)
#else
#  define assert(assertion){if (!(assertion)) asm(debughlt);}
#endif


#ifdef __cplusplus
}
#endif

#endif

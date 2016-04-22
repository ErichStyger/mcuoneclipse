/** ###################################################################
**
**     (c) Freescale Semiconductor, Inc.
**     2004 All Rights Reserved
**
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
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

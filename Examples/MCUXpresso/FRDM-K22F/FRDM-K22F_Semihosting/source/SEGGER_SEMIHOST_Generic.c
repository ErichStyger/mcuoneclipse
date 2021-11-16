/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*            (c) 2019 SEGGER Microcontroller GmbH                    *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* condition is met:                                                  *
*                                                                    *
* o Redistributions of source code must retain the above copyright   *
*   notice, this condition and the following disclaimer.             *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED. IN NO EVENT SHALL SEGGER Microcontroller BE LIABLE FOR *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : SEGGER_SEMIHOST_Generic.c
Purpose : Semihosting handler implementation for any device,
          using a common location for the debugger to set a breakpoint.
*/

#include "SEGGER_SEMIHOST.h"

int SEGGER_SEMIHOST_DebugHalt(int, int);

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

/*********************************************************************
*
*       SEGGER_SEMIHOST_X_Request()
*
*  Function description
*    Notify the debugger host about the semihosting request
*
*  Parameters
*    Op:         Operation.
*    pPara:      Pointer to parameter block.
*
*  Return value
*    Operation-specific return value, set by the debugger in R0.
*/

int BKPT(int op, void *p1, void *p2) {
  register int r0 asm("r0");
  register int r1 asm("r1") __attribute__((unused));
  register int r2 asm("r2") __attribute__((unused));

  r0 = op;
  r1 = (int) p1;
  r2 = (int) p2;

  asm volatile(
      " bkpt 0xAB \n"
      : "=r"(r0) // out
      :// in
      :// clobber
  );
  return r0;
}


int SEGGER_SEMIHOST_X_Request(int Op, SEGGER_SEMIHOST_PARA* pPara) {
  int r0;

  //r0 = SEGGER_SEMIHOST_DebugHalt((int)Op, (int)pPara);
  r0 = BKPT(Op, pPara, 0);
  return r0;
}

/*************************** End of file ****************************/

/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_device_registers.h"
#include "UTIL1.h"

static int i = 0;
#include "SEGGER_RTT.h"
#include "SEGGER_SYSVIEW.h"
#include "SEGGER_SYSVIEW_Config.h"

unsigned int myGlobal = 5;

static void _Delay(int period) {
  int i = 100000*period;
  do { ; } while (i--);
}

int main(void)
{

    /* Write your code here */

    /* This for loop should be replaced. By default this loop allows a single stepping. */
  SEGGER_SYSVIEW_Conf();
  for(;;) {
    uint8_t buf[64];

    SEGGER_SYSVIEW_OnUserStart(0);
    SEGGER_RTT_WriteString(0, "Hello World from SEGGER RTT!\r\n");
    UTIL1_Num32uToStr(buf, sizeof(buf), myGlobal);
    SEGGER_RTT_WriteString(0, (const char*)buf);
    SEGGER_RTT_WriteString(0, "\r\n");
    myGlobal++;
    SEGGER_SYSVIEW_OnUserStop(0);
//    WAIT1_Waitms(500);
    _Delay(50);
  }
    for (;;) {
        i++;
    }
    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

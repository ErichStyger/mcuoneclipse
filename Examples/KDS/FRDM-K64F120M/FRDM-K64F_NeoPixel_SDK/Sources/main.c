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
#include "DMAPixel.h"

#define NEO_NOF_PIXEL       3
#define NEO_NOF_BITS_PIXEL 24
static uint8_t transmitBuf[NEO_NOF_PIXEL*NEO_NOF_BITS_PIXEL] =
    {
        /* pixel 0: */
        1, 1, 1, 1, 1, 1, 1, 1, /* green */
        0, 0, 0, 0, 0, 0, 0, 0, /* red */
        0, 0, 0, 0, 0, 0, 0, 0, /* blue */
        /* pixel 1: */
        0, 0, 0, 0, 0, 0, 0, 0, /* green */
        1, 1, 1, 1, 1, 1, 1, 1, /* red */
        0, 0, 0, 0, 0, 0, 0, 0,  /* blue */
        /* pixel 0: */
        0, 0, 0, 0, 0, 0, 0, 0, /* green */
        0, 0, 0, 0, 0, 0, 0, 0, /* red */
        1, 1, 1, 1, 1, 1, 1, 1  /* blue */
    };

int main(void) {
  uint8_t red, green, blue;

  DMA_Init();
  for (;;) {
    DMA_Transfer(transmitBuf, sizeof(transmitBuf));
  }
  /* Never leave main */
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

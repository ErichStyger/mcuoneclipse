/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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
#include <stdio.h>
#include <stdint.h>

static int i = 0;

#pragma RETAIN(keepMe)
extern const int my_var;
static const int *const __attribute__((used)) keepMe  = &my_var;
const uint8_t *p;// = &keepMe;

#if 0
const char New[] =    "ch";
#define r(a,b)        #b " " #a
#define d(a,b,c,d,e)  c##b##d \
                      ##a##e##c
#define o(a, b)       b##a
const char Happy[] =  {'R','e','a'};
const char Gipfel[] = "Gipfel";
const char im        = 'i';
const char D         = 'D';
int Ye(void)          { return 061; }
int a(int a)          { return (a<<4) + 021; }

void reason(int r) {
  d(in, p, f, r, t)(o(out, std), "%s%sed " "%i" "! Make %d "  r(again, great) "%c %si %cm %c%d!\r\n", Happy, New, Ye(), a(r), '!',
      Gipfel, im, D, 300
   );
}
#endif

int main(void) {
  /* Write your code here */
  /* semihosting tests */
  //setvbuf(stdout, NULL, _IOFBF, 0);
  //setvbuf(stderr, NULL, _IOFBF, 0);
  i = *p;

  //reason(0x7d);
  printf("hello world!\r\n");
  fprintf(stdout, "Stdout output: %d\r\n", i);
  fprintf(stderr, "StdErr output: %d\r\n", i);

  /* This for loop should be replaced. By default this loop allows a single stepping. */
  for (;;) {
      i++;
  }
  /* Never leave main */
  return 0;
}
const int my_var;
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

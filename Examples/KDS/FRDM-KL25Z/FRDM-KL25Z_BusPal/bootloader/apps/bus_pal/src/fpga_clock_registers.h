/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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

#if !defined(__FPGA_CLOCK_REGISTERS_H__)
#define __FPGA_CLOCK_REGISTERS_H__

#define CY22393_ADDR 0x69

// REG
#define CY22393_REG_CLKA_DIVIDE (0x08) // divsel:0
#define CY22393_REG_CLKB_DIVIDE (0x0A) // divsel:0
#define CY22393_REG_CLKC_DIVIDE (0x0C) // CLKC
#define CY22393_REG_CLKD_DIVIDE (0x0D) // CLKD

#define CY22393_REG_SOURCE 0x0E

#define CY22393_REG_AC 0x0F
#define CY22393_REG_DC 0x10

#define CY22393_REG_CLKA_DIV 0x08
#define CY22393_REG_PLL3Q 0x14
#define CY22393_REG_PLL3P 0x15
#define CY22393_REG_PLL3E 0x16

// This is the low register value of the lower bank
#define CY22393_REG_LOW 0x08
// This is the high register value of the high bank
#define CY22393_REG_HIGH 0x17

#define CY22393_AC 0x55
#define CY22393_DC 0x55

#define CY22393_DIVIDE_OFF 0 // close clk ouput

// Maximum post div value when using VCO frequency above 333 MHZ
#define CY22393_POSTDIV_MAX_VAL 31

// Reference clock to cypress chip
#define CY22393_REF_CLK 24000000

// This is the minimum value that Reference divided by Q can be equal to
#define CY22393_MIN_REF_DIV_Q 250000

// Max clock frequency the chip supports, for CY22393 it is 200Mhz
#define CY22393_MAX_OUTPUT_CLK 200000000

// Max VCO clock frequency the chip supports, for CY22393 it is 375Mhz
#define CY22393_MAX_VCO_CLK 375000000

#endif // __FPGA_CLOCK_REGISTERS_H__

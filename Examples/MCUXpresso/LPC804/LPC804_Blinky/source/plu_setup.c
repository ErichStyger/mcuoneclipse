/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include <stdint.h>
#include "plu_setup.h"
#include "LPC804.h"

void PLU_setup(void) {
  SYSCON->SYSAHBCLKCTRL1 |= SYSCON_SYSAHBCLKCTRL1_PLU(1); /* enable PLU clock */

  SYSCON->PRESETCTRL1 &= ~SYSCON_PRESETCTRL1_PLU_RST_N(1); /* reset PLU ... */
  SYSCON->PRESETCTRL1 |= SYSCON_PRESETCTRL1_PLU_RST_N(1);  /* ... release PLU reset */

  SYSCON->SYSAHBCLKCTRL0 |= SYSCON_SYSAHBCLKCTRL0_SWM(1); /* enable switch matrix clock */

	/* LUT 0 Config Value */
	/* PIO0_9 PIO0_11 FF0 FF1 FF2|FF0 */
	/* --0-1|1 */
	/* --01-|1 */
	/* 110--|1 */
	*(uint32_t *)0x40028800 = 0x0f0f0f08UL; /*PLU*/
	/* LUT 1 Config Value */
	/* FF0 FF1 FF2|FF1 */
	/* 01-|1 */
	/* 100|1 */
	*(uint32_t *)0x40028804 = 0x00000046UL; /*PLU*/
	/* LUT 2 Config Value */
	/* PIO0_9 PIO0_11 FF0 FF1 FF2|FF2 */
	/* --0-1|1 */
	/* 1000-|1 */
	*(uint32_t *)0x40028808 = 0x0f0f0002UL; /*PLU*/
	/* LUT 4 Config Value */
	/* FF0 FF1 FF2|PIO0_8 */
	/* 0-1|1 */
	/* 01-|1 */
	/* 100|1 */
	*(uint32_t *)0x40028810 = 0x00000056UL; /*PLU*/

	/* PIO0_9 --> PLUINPUT1 */
	SWM0->PINASSIGNFIXED0 = (SWM0->PINASSIGNFIXED0 & ~SWM_PINASSIGNFIXED0_PLU_INPUT1_MASK) | SWM_PINASSIGNFIXED0_PLU_INPUT1(1);

	/* PIO0_11 --> PLUINPUT3 */
  SWM0->PINASSIGNFIXED0 = (SWM0->PINASSIGNFIXED0 & ~SWM_PINASSIGNFIXED0_PLU_INPUT3_MASK) | SWM_PINASSIGNFIXED0_PLU_INPUT3(1);

	/* PLUOUT1 --> PIO0_8 */
  SWM0->PINASSIGNFIXED0 = (SWM0->PINASSIGNFIXED0 & ~SWM_PINASSIGNFIXED0_PLU_OUT1_MASK) | SWM_PINASSIGNFIXED0_PLU_OUT1(0);

	/* PLUINPUT1 --> LUT0_INP0 */
	*(uint32_t *)0x40028000 = 0x00000001UL; /*PLU*/
	/* PLUINPUT3 --> LUT0_INP1 */
	*(uint32_t *)0x40028004 = 0x00000003UL; /*PLU*/
	/* FF0 --> LUT0_INP2 */
	*(uint32_t *)0x40028008 = 0x00000020UL; /*PLU*/
	/* FF1 --> LUT0_INP3 */
	*(uint32_t *)0x4002800c = 0x00000021UL; /*PLU*/
	/* FF2 --> LUT0_INP4 */
	*(uint32_t *)0x40028010 = 0x00000022UL; /*PLU*/
	/* FF0 --> LUT1_INP0 */
	*(uint32_t *)0x40028020 = 0x00000020UL; /*PLU*/
	/* FF1 --> LUT1_INP1 */
	*(uint32_t *)0x40028024 = 0x00000021UL; /*PLU*/
	/* FF2 --> LUT1_INP2 */
	*(uint32_t *)0x40028028 = 0x00000022UL; /*PLU*/
	/* PLUINPUT1 --> LUT2_INP0 */
	*(uint32_t *)0x40028040 = 0x00000001UL; /*PLU*/
	/* PLUINPUT3 --> LUT2_INP1 */
	*(uint32_t *)0x40028044 = 0x00000003UL; /*PLU*/
	/* FF0 --> LUT2_INP2 */
	*(uint32_t *)0x40028048 = 0x00000020UL; /*PLU*/
	/* FF1 --> LUT2_INP3 */
	*(uint32_t *)0x4002804c = 0x00000021UL; /*PLU*/
	/* FF2 --> LUT2_INP4 */
	*(uint32_t *)0x40028050 = 0x00000022UL; /*PLU*/
	/* FF0 --> LUT4_INP0 */
	*(uint32_t *)0x40028080 = 0x00000020UL; /*PLU*/
	/* FF1 --> LUT4_INP1 */
	*(uint32_t *)0x40028084 = 0x00000021UL; /*PLU*/
	/* FF2 --> LUT4_INP2 */
	*(uint32_t *)0x40028088 = 0x00000022UL; /*PLU*/
	/* LUT4 --> PLUOUT1 */
	*(uint32_t *)0x40028c04 = 0x00000004UL; /*PLU*/
	/* LUT0 --> FF0 */
	/* LUT1 --> FF1 */
	/* LUT2 --> FF2 */

	/* PIO0_30 --> PLU_CLKIN */
	*(uint32_t *)0x4000c01c &= ~0xff000000UL; *(uint32_t *)0x4000c01c |= 0x1e000000UL; /*SWM*/

	/* CLKOUT --> PIO0_30 */
	*(uint32_t *)0x4000c014 &= ~0xff000000UL; *(uint32_t *)0x4000c014 |= 0x1e000000UL; /*SWM*/

	/* CLKOUT clock source select register: Select main clock */
	SYSCON->CLKOUTSEL = SYSCON_CLKOUTSEL_SEL(1);

	/* CLKOUT clock divider register: Divide by 6 */
	SYSCON->CLKOUTDIV = SYSCON_CLKOUTDIV_DIV(6);
}

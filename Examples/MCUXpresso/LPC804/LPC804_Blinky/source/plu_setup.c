/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "plu_setup.h"
#include "fsl_plu.h"
#include "fsl_swm.h"

void PLU_setup(void) {
  /* LUT 0 Configuration Value */
  PLU->LUT[0].INP_MUX[0] = 0x00000001; /* IN1 (SCK), PLUINPUT1 --> LUT0_INP0 */
  PLU->LUT[0].INP_MUX[1] = 0x00000003; /* IN3 (MOSI), PLUINPUT3 --> LUT0_INP1 */
  PLU->LUT[0].INP_MUX[2] = 0x00000020; /* FF0 (FF0), FF0 --> LUT0_INP2 */
  PLU->LUT[0].INP_MUX[3] = 0x00000021; /* FF1 (FF1), FF1 --> LUT0_INP3 */
  PLU->LUT[0].INP_MUX[4] = 0x00000022; /* FF2 (FF2), FF2 --> LUT0_INP4 */
  /* PIO0_9 CLK, PIO0_11 MOSI */
	/* PIO0_9 PIO0_11 FF0 FF1 FF2|FF0 */
	/* --0-1|1 */
	/* --01-|1 */
	/* 110--|1 */
  PLU->LUT_TRUTH[0] = 0x0f0f0f08UL;

	/* LUT 1 Configuration Value */
  PLU->LUT[1].INP_MUX[0] = 0x00000020; /* FF0 (FF0), FF0 --> LUT1_INP0 */
  PLU->LUT[1].INP_MUX[1] = 0x00000021; /* FF1 (FF1), FF1 --> LUT1_INP1 */
  PLU->LUT[1].INP_MUX[2] = 0x00000022; /* FF2 (FF2), FF2 --> LUT1_INP2 */
  PLU->LUT[1].INP_MUX[3] = 0x0000003F; /* default */
  PLU->LUT[1].INP_MUX[4] = 0x0000003F; /* default */
	/* FF0 FF1 FF2|FF1 */
	/* 01-|1 */
	/* 100|1 */
  PLU->LUT_TRUTH[1] = 0x00000046UL;

	/* LUT 2 Configuration Value */
  PLU->LUT[2].INP_MUX[0] = 0x00000001; /* IN1 (SCK), PLUINPUT1 --> LUT2_INP0 */
  PLU->LUT[2].INP_MUX[1] = 0x00000003; /* IN3 (MOSI), PLUINPUT3 --> LUT2_INP1 */
  PLU->LUT[2].INP_MUX[2] = 0x00000020; /* FF0 (FF0), FF0 --> LUT2_INP2 */
  PLU->LUT[2].INP_MUX[3] = 0x00000021; /* FF1 (FF1), FF1 --> LUT2_INP3 */
  PLU->LUT[2].INP_MUX[4] = 0x00000022; /* FF2 (FF2), FF2 --> LUT2_INP4 */

	/* PIO0_9 PIO0_11 FF0 FF1 FF2|FF2 */
	/* --0-1|1 */
	/* 1000-|1 */
  PLU->LUT_TRUTH[2] = 0x0f0f0002UL;

	/* LUT 4 Configuration Value */
  PLU->LUT[4].INP_MUX[0] = 0x00000020; /* FF0 (FF0), FF0 --> LUT4_INP0 */
  PLU->LUT[4].INP_MUX[1] = 0x00000021; /* FF1 (FF1), FF1 --> LUT4_INP1 */
  PLU->LUT[4].INP_MUX[2] = 0x00000022; /* FF2 (FF2), FF2 --> LUT4_INP2 */
  PLU->LUT[4].INP_MUX[3] = 0x0000003F; /* default */
  PLU->LUT[4].INP_MUX[4] = 0x0000003F; /* default */
	/* FF0 FF1 FF2|PIO0_8 */
	/* 0-1|1 */
	/* 01-|1 */
	/* 100|1 */
  PLU->LUT_TRUTH[4] = 0x00000056UL;
  PLU->OUTPUT_MUX[1] = 0x00000004; /* LUT4 (LUT4) -> WS2812B */

	/* default forced LUT to FF assignments: */
	/* LUT0 --> FF0 */
	/* LUT1 --> FF1 */
	/* LUT2 --> FF2 */

	/* ************** Switch matrix configuration ******************* */
  CLOCK_EnableClock(kCLOCK_Swm); /* enable switch matrix clock */
  SWM_SetFixedMovablePinSelect(SWM0, kSWM_PLU_INPUT1, kSWM_PLU_INPUT1_PortPin_P0_9); /* PIO0_9 (SPI CLK) --> PLUINPUT1 */
  SWM_SetFixedMovablePinSelect(SWM0, kSWM_PLU_INPUT3, kSWM_PLU_INPUT3_PortPin_P0_11); /* PIO0_11 (SPI MOSI) --> PLUINPUT3 */
  SWM_SetFixedMovablePinSelect(SWM0, kSWM_PLU_OUT1, kSWM_PLU_OUT1_PortPin_P0_8); /* PLUOUT1 --> PIO0_8 */
  /* an external clock must be applied to the PLU_CLKIN input when using FFs! */
  SWM_SetMovablePinSelect(SWM0, kSWM_PLU_CLKIN_IN, kSWM_PortPin_P0_30); /* PIO0_30 --> PLU_CLKIN */
  SWM_SetMovablePinSelect(SWM0, kSWM_CLKOUT, kSWM_PortPin_P0_30); /* CLKOUT --> PIO0_30 */
  CLOCK_DisableClock(kCLOCK_Swm); /* disable switch matrix clock */
  /* **************************************************************** */

  /* CLKOUT clock source select register: Select main clock (15 MHz) */
  SYSCON->CLKOUTSEL = SYSCON_CLKOUTSEL_SEL(1);
  /* CLKOUT clock divider register: Divide by 6 => 2.5 MHz */
  SYSCON->CLKOUTDIV = SYSCON_CLKOUTDIV_DIV(6);
}

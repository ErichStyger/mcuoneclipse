/*
 * timers.c
 *
 * Created on: 24 May 2022
 *     Author: Peter Allenspach
 *     For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

#include "mytimer.h"
#include "fsl_ctimer.h"
#include "lpadc.h"
#include "LPC55S69_cm33_core0.h"
#include <stdio.h>

#include "SEGGER_RTT.h"

static void timer0_callback(uint32_t flags)
{
	SEGGER_printf("\n%d", get_LPADC0B_res());
	LPADC_DoSoftwareTrigger(LPADC_BASE, 1U);
}

void init_MeasurementTimer(void)
{

	ctimer_config_t t0_config;
	ctimer_match_config_t matchConfig;
	// initialize 100us_timer

	CTIMER_GetDefaultConfig(&t0_config); // default config should be good
	CTIMER_Init(CTIMER0, &t0_config);

	matchConfig.enableCounterReset = true;
	matchConfig.enableCounterStop = false;
	matchConfig.matchValue = 15000; // 150MHz / 15000 = 100us
	//	matchConfig.matchValue = 1500000; // 100ms match for testing
	matchConfig.outControl = kCTIMER_Output_NoAction;
	matchConfig.outPinInitState = false;
	matchConfig.enableInterrupt = true;

	static ctimer_callback_t ctimer_callback = timer0_callback;
	CTIMER_RegisterCallBack(CTIMER0, &ctimer_callback, kCTIMER_SingleCallback);
	CTIMER_SetupMatch(CTIMER0, kCTIMER_Match_1, &matchConfig);
	// CTIMER_StartTimer(CTIMER0); // don't start timer from init
}

void MeasurementTimer_start(void)
{
	CTIMER_StartTimer(CTIMER0);
}

void MeasurementTimer_stop(void)
{
	CTIMER_StopTimer(CTIMER0);
}

static void timer1_callback(uint32_t flags)
{
	SEGGER_printf("Hello");
}

/* This function is currently unused
 * It would have been used in the Trigger processing functions
 */
/*
void init_TriggerCommandTimer(void)
{

	ctimer_config_t t1_config;
	CTIMER_GetDefaultConfig(&t1_config);
	CTIMER_Init(CTIMER1, &t1_config);
	ctimer_match_config_t matchConfig;
	// initialize 100us_timer

	matchConfig.enableCounterReset = true;
	matchConfig.enableCounterStop = false;
	// matchConfig.matchValue         = 15000; // 150MHz / 15000 = 100us
	matchConfig.matchValue = 150000000;
	matchConfig.outControl = kCTIMER_Output_NoAction;
	matchConfig.outPinInitState = false;
	matchConfig.enableInterrupt = true;

	static ctimer_callback_t ctimer_callback = timer1_callback;
	CTIMER_RegisterCallBack(CTIMER1, &ctimer_callback, kCTIMER_SingleCallback);
	CTIMER_SetupMatch(CTIMER1, kCTIMER_Match_2, &matchConfig);
	CTIMER_StartTimer(CTIMER1);
}

*/

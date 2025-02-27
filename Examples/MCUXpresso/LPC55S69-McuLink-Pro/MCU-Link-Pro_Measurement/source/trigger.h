/*
 * trigger.h
 *
 *  Created on: 18 May 2022
 *      Author: Peter Allenspach
 * 		For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

#ifndef TRIGGER
#include <stdio.h>
#include "fsl_common.h"

/* This file currently has no use
 * It is a relic of trying to implement an UART-like soft-interface
 * This would have been the command sending logic
 * to be used in the device under test
 */

void mcul_trigger_start(uint16_t number);
void mcul_trigger_stop(uint16_t number);

#define TRIGGER
#endif

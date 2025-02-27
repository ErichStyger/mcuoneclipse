/*
 * trigger_api.c
 *
 *  Created on: 18 May 2022
 *      Author: Peter Allenspach
 * 		For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

#include "trigger_api.h"
#include <stdio.h>

/* This file currently has no use
 * It is a relic of trying to implement an UART-like soft-interface
 * This would have been the API for a device under test
 * to be used in the device under test
 */

/* Implement functions that do the needed task here:
 * mcul_delay_10us: delay (busy wait) for 10us
 * mcul_pin_set: set the trigger pin
 * mcul_pin_reset: reset the trigger pin
 * mcul_pin_init: initialize the trigger pin
 */
#if MCUL_DUT
void mcul_delay_10us(void)
{
}
void mcul_pin_set(void)
{
}
void mcul_pin_reset(void)
{
}
void mcul_pin_init(void)
{
}
#endif
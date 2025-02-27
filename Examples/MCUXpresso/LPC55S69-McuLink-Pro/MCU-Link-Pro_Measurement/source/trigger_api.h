/*
 * trigger_api.h
 *
 *  Created on: 18 May 2022
 *      Author: Peter Allenspach
 * 		For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

#ifndef TRIGGER_API

/* This file currently has no use
 * It is a relic of trying to implement an UART-like soft-interface
 * This would have been the API for a device under test
 * to be used in the device under test
 */

#define MCUL_DUT (0)

void mcul_delay_10us(void);
void mcul_pin_set(void);
void mcul_pin_reset(void);
void mcul_pin_init(void);

#define TRIGGER_API
#endif

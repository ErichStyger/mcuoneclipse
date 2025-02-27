/*
 * trigger.c
 *
 *  Created on: 18 May 2022
 *      Author: Peter Allenspach
 * 		For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

#include "trigger.h"
#include "trigger_api.h"
#include <stdio.h>

/* This file currently has no use
 * It is a relic of trying to implement an UART-like soft-interface
 * This would have been the command sending logic
 * to be used in the device under test
 */

// void mcul_trigger(uint8_t number){
//     for(uint8_t i = 0; i < 8){
//         if ((number>>i) % 2){
//             mcul_pin_set();
//         } else{
//             mcul_pin_reset();
//         }
//         mcul_delay_10us();
//     }
//     mcul_pin_reset();
// }
//
// void mcul_trigger_start(uint8_t number){
//     mcul_pin_set();
//     mcul_delay_10us();
//     mcul_delay_10us();
//     mcul_trigger(number);
// }
//
// void mcul_trigger_stop(uint8_t number){
//     mcul_pin_set();
//     mcul_delay_10us();
//     mcul_pin_reset();
//     mcul_delay_10us();
//     mcul_trigger(number);
//
// }

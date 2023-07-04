/*
 * Hue Apple IR Remote
 * Author: 	Joshua Wyss
 * Date: 	24.11.2022
 *
 */

#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "MyPlatform.h"
#include "McuRTOS.h"

int main(void) {
    MyPL_Init(); //Initialize everything
    //main action happens in MainTask.c
    vTaskStartScheduler(); //Start the scheduler
    //code never cums here
    return 0;
}

// file end
//=================================================================================


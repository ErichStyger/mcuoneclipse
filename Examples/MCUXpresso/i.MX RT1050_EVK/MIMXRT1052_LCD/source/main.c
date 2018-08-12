/*
 * The Clear BSD License
 * Copyright (c) 2017, NXP Semiconductors, Inc.
 * All rights reserved.
 *
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
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
#include "Platform.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"

#include "pin_mux.h"
#include "board.h"
#include "fsl_gpio.h"
#include "clock_config.h"

#include "GDisp1.h"
#include "FreeRTOS.h"
#include "task.h"
#if PL_CONFIG_USE_LCD
  #include "lcd.h"
#endif
#if PL_CONFIG_USE_ACCEL
  #include "accel/accel.h"
#endif
#if PL_CONFIG_USE_GUI
  #include "lv.h"
  #include "lvgl.h"
  #include "gui.h"
  #include "touch.h"
#endif
#if PL_CONFIG_EYE_DEMO
  #include "uncannyEyes.h"
#endif
#include "LED.h"


static void AppTask(void *p) {
#if PL_CONFIG_EYE_DEMO
    EYES_Init();
    GDisp1_UpdateFull(); /* show black screen */
    EYES_ShowLogo();
	for(;;) {
		//vTaskDelay(pdMS_TO_TICKS(100));
    	EYES_Run();
	}
#elif PL_CONFIG_USE_GUI
	vTaskDelay(pdMS_TO_TICKS(100));
	GUI_Init();
    for(;;) {
    	LED_Toggle();
    	vTaskDelay(pdMS_TO_TICKS(500));
	}
#else
    for(;;) {
		vTaskDelay(pdMS_TO_TICKS(10));
	}
#endif
}

/*!
 * @brief Main function
 */
int main(void) {
    BOARD_ConfigMPU();
    BOARD_BootClockRUN(); /* configure clocks for normal run mode */
    BOARD_InitPins();  /* configure common pins */
#if PL_CONFIG_USE_I2C
    BOARD_InitI2C1Pins(); /* I2C pins for touch and accel/compass */
#endif
    BOARD_InitSemcPins(); /* smart memory controller */
    BOARD_InitDebugConsole(); /* using debug console with PRINTF */
    LED_Init();
#if PL_CONFIG_USE_LCD
    LCD_Init();
#endif
#if PL_CONFIG_USE_TOUCH
    TOUCH_Init();
#endif
#if PL_CONFIG_USE_ACCEL
    if (ACCEL_Init()!=0) {
    	for(;;) {
    		/* failed */
    	}
    }
#endif
//    PRINTF("LCD example start...\r\n");
    xTaskCreate(/* The function that implements the task. */
                AppTask,
                /* Text name for the task, just to help debugging. */
                "App",
                /* The size (in words) of the stack that should be created
                for the task. */
                configMINIMAL_STACK_SIZE + 800,
                /* A parameter that can be passed into the task.  Not used
                in this simple demo. */
                NULL,
                /* The priority to assign to the task.  tskIDLE_PRIORITY
                (which is 0) is the lowest priority.  configMAX_PRIORITIES - 1
                is the highest priority. */
                1,
                /* Used to obtain a handle to the created task.  Not used in
                this simple demo, so set to NULL. */
                NULL);
    vTaskStartScheduler();
    for(;;) {} /* should never get here */
}

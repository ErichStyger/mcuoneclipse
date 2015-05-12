/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#include "Platform.h"
#include "fsl_device_registers.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "board.h"
#include "Utility.h"
#include "fsl_debug_console.h"
#include "FreeRTOS_Trace.h"
#if PL_HAS_SHELL_QUEUE
  #include "ShellQueue.h"
#endif

static int i = 0;

// Define gpio input pin config structure SW.
gpio_input_pin_user_config_t inputPin[] = {
    {
        .pinName                       = BOARD_SW_GPIO,
        .config.isPullEnable           = true,
#if FSL_FEATURE_PORT_HAS_PULL_SELECTION
        .config.pullSelect             = kPortPullUp,
#endif
#if FSL_FEATURE_PORT_HAS_PASSIVE_FILTER
        .config.isPassiveFilterEnabled = false,
#endif
#if FSL_FEATURE_PORT_HAS_DIGITAL_FILTER
        .config.isDigitalFilterEnabled = false,
#endif
        .config.interrupt              = kPortIntFallingEdge,
    },
    {
        .pinName = GPIO_PINS_OUT_OF_RANGE,
    }
};

// Define gpio output pin config structure LED1.
gpio_output_pin_user_config_t outputPin[] = {
    {
        .pinName              = kGpioLED1,
        .config.outputLogic   = 0,
#if FSL_FEATURE_PORT_HAS_SLEW_RATE
        .config.slewRate      = kPortFastSlewRate,
#endif
#if FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH
        .config.driveStrength = kPortHighDriveStrength,
#endif
    },
    {
        .pinName              = kGpioLED2,
        .config.outputLogic   = 0,
#if FSL_FEATURE_PORT_HAS_SLEW_RATE
        .config.slewRate      = kPortFastSlewRate,
#endif
#if FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH
        .config.driveStrength = kPortHighDriveStrength,
#endif
    },
    {
        .pinName              = kGpioLED3,
        .config.outputLogic   = 0,
#if FSL_FEATURE_PORT_HAS_SLEW_RATE
        .config.slewRate      = kPortFastSlewRate,
#endif
#if FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH
        .config.driveStrength = kPortHighDriveStrength,
#endif
    },
    {
        .pinName = GPIO_PINS_OUT_OF_RANGE,
    }
};


#if PL_USE_SW_TIMERS
static xTimerHandle timerHndl;
#define SW_TIMER_PERIOD_MS 50

static void vTimerCallback(xTimerHandle pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
    GPIO_DRV_TogglePinOutput(kGpioLED2); /* toggle red LED */
}
#endif

static void busydelay(uint32_t val) {
	while(val>0) {
		val--;
		__asm("nop");
	}
}

static void shell_task(void *param) {
  (void)param;
  for(;;) {
#if PL_HAS_SHELL_QUEUE
    {
      /*! \todo Handle shell queue */
      unsigned char ch;

      while((ch=SQUEUE_ReceiveChar()) && ch!='\0') {
    	  debug_putchar(ch);
      }
    }
#endif
    vTaskDelay(50/portTICK_RATE_MS); /* wait for 500 ms */
  } /* for */
}


static void blinky_task(void *param) {
  (void)param;
  for(;;) {
    GPIO_DRV_TogglePinOutput(kGpioLED1); /* toggle green LED */
    busydelay(100000);
    vTaskDelay(500/portTICK_RATE_MS); /* wait for 500 ms */
  } /* for */
}

#if 0
  float f=3.5, g;
  double d, dd;
#endif

int main(void) {
	hardware_init();
	/* !\todo add serial console */
#if configUSE_TRACE_HOOKS
	RTOSTRC_Init();
#endif
#if PL_HAS_SHELL_QUEUE
	SQUEUE_Init();
#endif
#if 0
	f++;
	g = f/2;
	d = 37.5;
	dd = d/55;
	memset(0, 5, 70);
	dd++;
#endif
	// Init LED1, SW1.
    GPIO_DRV_Init(inputPin, outputPin);
    // Turn LED1 on.
    GPIO_DRV_SetPinOutput(kGpioLED1); /* turn Green LED off */
    GPIO_DRV_ClearPinOutput(kGpioLED1); /* turn Green led on */
    GPIO_DRV_SetPinOutput(kGpioLED1); /* turn Green LED off */

    GPIO_DRV_ClearPinOutput(kGpioLED2);
    GPIO_DRV_ClearPinOutput(kGpioLED3);
    GPIO_DRV_SetPinOutput(kGpioLED2);
    GPIO_DRV_SetPinOutput(kGpioLED3);

    debug_printf("hello world\r\n");

#if PL_USE_SW_TIMERS /* create software timer */
  timerHndl = xTimerCreate("timer0", SW_TIMER_PERIOD_MS/portTICK_RATE_MS, pdTRUE, (void *)0, vTimerCallback);
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) {
    for(;;); /* failure! */
  }
#endif
	 if (xTaskCreate(blinky_task, "Blinky", configMINIMAL_STACK_SIZE,
		  NULL,
		  tskIDLE_PRIORITY,
		  NULL
		) != pdPASS) {
		for(;;){} /* error! probably out of memory */
	  }
	 if (xTaskCreate(shell_task, "Shell", configMINIMAL_STACK_SIZE,
	      NULL,
	      tskIDLE_PRIORITY,
	      NULL
	    ) != pdPASS) {
	    for(;;){} /* error! probably out of memory */
	  }


    vTaskStartScheduler();
    /* This for loop should be replaced. By default this loop allows a single stepping. */
    for (;;) {
        i++;
    }
    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

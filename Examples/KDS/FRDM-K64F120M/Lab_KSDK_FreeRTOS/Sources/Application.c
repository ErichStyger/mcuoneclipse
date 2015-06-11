/*
 * Application.c
 *
 *  Created on: 09.06.2015
 *      Author: tastyger
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
#include "Application.h"

typedef enum {
	RGB_LED_RED = (1<<0),
	RGB_LED_GREEN = (1<<1),
	RGB_LED_BLUE = (1<<2)
} RGB_LED_Kind;

static RGB_LED_Kind whichLED = RGB_LED_RED;

#if PL_USE_SW_TIMERS
static xTimerHandle timerHndl;
#define SW_TIMER_PERIOD_MS 50

static void vTimerCallback(xTimerHandle pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
  //GPIO_DRV_TogglePinOutput(kGpioLED2); /* toggle red LED */
}
#endif

static void busydelay(uint32_t val) {
	while(val>0) {
		val--;
		__asm("nop");
	}
}

static void app_task(void *param) {
  (void)param;
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(500)); /* wait for 500 ms */
	if (GPIO_DRV_ReadPinInput(kGpioSW2)==0) { /* pressed */
	  busydelay(10000); /* debounce */
	  while (GPIO_DRV_ReadPinInput(kGpioSW2)==0) {
		/* wait until released */
	  }
	  SQUEUE_SendString("SW2 has been pressed!\r\n");
	  whichLED <<= 1;
	  if (whichLED>RGB_LED_BLUE) {
		whichLED = RGB_LED_RED;
	  }
	}
	if (GPIO_DRV_ReadPinInput(kGpioSW3)==0) { /* pressed */
	  busydelay(10000); /* debounce */
	  while (GPIO_DRV_ReadPinInput(kGpioSW3)==0) {
		/* wait until released */
	  }
	  SQUEUE_SendString("SW3 has been pressed!\r\n");
	  whichLED >>= 1;
	  if (whichLED<RGB_LED_RED) {
		whichLED = RGB_LED_BLUE;
	  }
	}
  } /* for */
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
    vTaskDelay(pdMS_TO_TICKS(50)); /* wait for 500 ms */
  } /* for */
}

static void blinky_task(void *param) {
  (void)param;
  for(;;) {
	switch(whichLED) {
	case RGB_LED_GREEN:
	    SQUEUE_SendString("Blinking GREEN RGB LED\r\n");
	    GPIO_DRV_TogglePinOutput(kGpioLED1);
	    GPIO_DRV_SetPinOutput(kGpioLED2);
	    GPIO_DRV_SetPinOutput(kGpioLED3);
		break;
	case RGB_LED_RED:
	    SQUEUE_SendString("Blinking GREEN RED LED\r\n");
		GPIO_DRV_SetPinOutput(kGpioLED1);
	    GPIO_DRV_TogglePinOutput(kGpioLED2);
	    GPIO_DRV_SetPinOutput(kGpioLED3);
		break;
	case RGB_LED_BLUE:
	    SQUEUE_SendString("Blinking GREEN BLUE LED\r\n");
		GPIO_DRV_SetPinOutput(kGpioLED1);
	    GPIO_DRV_SetPinOutput(kGpioLED2);
	    GPIO_DRV_TogglePinOutput(kGpioLED3);
		break;
	}
    vTaskDelay(pdMS_TO_TICKS(500)); /* wait for 500 ms */
  } /* for */
}

void APP_Run(void) {
	hardware_init();
#if configUSE_TRACE_HOOKS
	RTOSTRC_Init();
#endif
#if PL_HAS_SHELL_QUEUE
	SQUEUE_Init();
#endif
	/* Init LED1, SW1.*/

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
 if (xTaskCreate(app_task, "App", configMINIMAL_STACK_SIZE,
	  NULL,
	  tskIDLE_PRIORITY,
	  NULL
	) != pdPASS) {
	for(;;){} /* error! probably out of memory */
  }
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
}


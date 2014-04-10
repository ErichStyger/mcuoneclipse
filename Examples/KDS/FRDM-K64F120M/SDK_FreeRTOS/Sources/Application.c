/**
 * \file
 * \brief Demo application using FreeRTOS with the Kinetis SDK
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 */

//#include <board.h> /* board configuration */
#include <fsl_os_abstraction.h> /* SDK RTOS abstraction */
#include "board.h"
//#include "LED_RGB.h" /* RGB LED */
#include "gpio_pins.h"
#include "FreeRTOS.h" /* FreeRTOS interface */

/*--------------------------------------------------------------------------*/
/* Kinetis SDK Task variables and defines */
#define SDK_TASK_STACK_SIZE  200 /* Task size (in 32bit units) */
#define SDK_TASK_PRIO        0 /* task priority */
static void sdk_task(void *param); /* prototype of the task */
FSL_RTOS_TASK_DEFINE(sdk_task, SDK_TASK_STACK_SIZE, "sdk", false);
static task_handler_t sdk_task_hdl; /* task handle */

static void sdk_task(void *param) {
  (void)param;
  for(;;) {
    gpio_toggle_pin_output(kGpioLED3);
	  time_delay(1000);
  }
}

static void SDK_CreateTask(void) {
  if (task_create(sdk_task, SDK_TASK_PRIO, NULL, &sdk_task_hdl)!=kSuccess) {
    for(;;); /* error! */
  }
}

/*--------------------------------------------------------------------------*/
/* traditional FreeRTOS task */
static xTaskHandle mainTaskHndl;

static void main_task(void *param) {
  (void)param;
  for(;;) {
    gpio_toggle_pin_output(kGpioLED1);
    vTaskDelay(1000/portTICK_RATE_MS);
  } /* for */
}

static void CreateTask(void) {
    if (xTaskCreate(
        main_task,  /* task function */
        "Main", /* task name for kernel awareness */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        &mainTaskHndl /* task handle */
      ) != pdPASS) {
      for(;;){} /* error! probably out of memory */
    }
}

//void SystemCoreClockUpdate(void);

void APP_Start (void) {
  hardware_init();

//  SystemCoreClockUpdate();

  /* Initialize the pins used input and output */
  gpio_init(NULL, ledPins);

  /* turn off LEDs */
  //gpio_set_pin_output(LED_RED);
  //gpio_set_pin_output(LED_GREEN);
  //gpio_set_pin_output(LED_BLUE);
  //gpio_toggle_pin_output(LED_RED);
	//gpio_toggle_pin_output(LED_GREEN);
	//gpio_toggle_pin_output(LED_BLUE);

	/* create tasks */
	CreateTask();
	SDK_CreateTask();

	/* start the scheduler */
  vTaskStartScheduler(); /* does usually not return! */
}

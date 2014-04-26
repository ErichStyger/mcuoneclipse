/**
 * \file
 * \brief Demo application using FreeRTOS with the Kinetis SDK
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 */

#include <board.h> /* board configuration */
#include <fsl_os_abstraction.h> /* SDK RTOS abstraction */
#include "LED_RGB.h" /* RGB LED */
#include "FreeRTOS.h" /* FreeRTOS interface */
#include "RTOSTRC1.h"

#define USE_SDK_RTOS   0

/*--------------------------------------------------------------------------*/
#if USE_SDK_RTOS
/* Kinetis SDK Task variables and defines */
#define SDK_TASK_STACK_SIZE  200 /* Task size (in 32bit units) */
#define SDK_TASK_PRIO        3 /* task priority */
static void sdk_task(void *param); /* prototype of the task */
FSL_RTOS_TASK_DEFINE(sdk_task, SDK_TASK_STACK_SIZE, "sdk", false);
static task_handler_t sdk_task_hdl; /* task handle */

static void sdk_task(void *param) {
  (void)param;
  for(;;) {
    gpio_toggle_pin_output(LED_BLUE);
	  time_delay(1000);
  }
}

static void SDK_CreateTask(void) {
  if (task_create(sdk_task, SDK_TASK_PRIO, NULL, &sdk_task_hdl)!=kSuccess) {
    for(;;); /* error! */
  }
}
#endif /* USE_SDK_RTOS */
/*--------------------------------------------------------------------------*/
/* traditional FreeRTOS task */
static xTaskHandle mainTaskHndl;

static void main_task(void *param) {
  (void)param;
  for(;;) {
    gpio_toggle_pin_output(LED_RED);
    vTaskDelay(1000/portTICK_RATE_MS);
  } /* for */
}

static void CreateTask(void) {
    if (xTaskCreate(
        main_task,  /* task function */
        "Main", /* task name for kernel awareness */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        &mainTaskHndl /* task handle */
      ) != pdPASS) {
      for(;;){} /* error! probably out of memory */
    }
}

void APP_Start (void) {
  //hardware_init();
  /* turn off LEDs */
  gpio_set_pin_output(LED_RED);
  gpio_set_pin_output(LED_GREEN);
  gpio_set_pin_output(LED_BLUE);
  //gpio_toggle_pin_output(LED_RED);
	//gpio_toggle_pin_output(LED_GREEN);
	//gpio_toggle_pin_output(LED_BLUE);

  /* enable trace */
#if 1
  if(RTOSTRC1_uiTraceStart()!=1) {
    for(;;){} /* failure? */
  }
#endif
	/* create tasks */
	CreateTask(); /* normal FreeRTOS tasks */
#if USE_SDK_RTOS
	SDK_CreateTask(); /* using SDK API */
#endif

	/* start the scheduler */
  vTaskStartScheduler(); /* does usually not return! */
}

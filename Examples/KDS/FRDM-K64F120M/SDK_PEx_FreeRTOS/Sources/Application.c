/**
 * \file
 * \brief Demo application using FreeRTOS with the Kinetis SDK
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 */

#include <fsl_os_abstraction.h> /* SDK RTOS abstraction */
#include "board.h" /* board header file */
#include "gpio1.h" /* General purpose I/O pins */
#include "FreeRTOS.h" /* FreeRTOS interface */
#include "RTOSTRC1.h"

#define USE_SDK_RTOS  0 /* for now, cannot use RTOS in SDK as PEx assumes 'bare'? */
/*--------------------------------------------------------------------------*/
#if USE_SDK_RTOS
/* Kinetis SDK Task variables and defines */
#define SDK_TASK_STACK_SIZE  200 /* Task stack size (in 32bit units) */
#define SDK_TASK_PRIO        0 /* task priority */
static void sdk_task(void *param); /* prototype of the task */
FSL_RTOS_TASK_DEFINE(sdk_task, SDK_TASK_STACK_SIZE, "sdk", false);
static task_handler_t sdk_task_hdl; /* task handle */

/*!
 * \brief Kinetis SDK task, toggles a LED every 1 second.
 * \param param task parameter
 */
static void sdk_task(void *param) {
  (void)param; /* unused parameter */
  for(;;) {
    gpio_toggle_pin_output(kGpioLED3); /* toggle blue LED */
	time_delay(1000); /* wait 1000 ms */
  }
}

/*!
 * \brief Creates a task using the Kinetis SDK API
 */
static void SDK_CreateTask(void) {
  if (task_create(sdk_task, SDK_TASK_PRIO, NULL, &sdk_task_hdl)!=kSuccess) {
    for(;;); /* error! */
  }
}
#endif /* USE_SDK_RTOS */

/*--------------------------------------------------------------------------*/
/* traditional FreeRTOS task API */
static xTaskHandle mainTaskHndl;

static void main_task(void *param) {
  (void)param;
  for(;;) {
    gpio_toggle_pin_output(kGpioLED2); /* toggle green LED */
    vTaskDelay(500/portTICK_RATE_MS); /* wait for 500 ms */
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

void APP_Start (void) {
  hardware_init(); /* initialize the hardware */

#if 1 /* Percipio Trace */
  if(RTOSTRC1_uiTraceStart()!=1) {
    for(;;){} /* failure? */
  }
#endif

  /* create tasks */
  CreateTask(); /* create a task with the 'traditional' FreeRTOS API */
#if USE_SDK_RTOS
  SDK_CreateTask(); /* create a task with the Kinetis SDK API */
#endif

  vTaskStartScheduler(); /* start FreeRTOS scheduler, does usually not return! */
}

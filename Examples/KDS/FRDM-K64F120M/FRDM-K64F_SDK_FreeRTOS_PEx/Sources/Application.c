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

#define USE_SDK_RTOS  1 /* Using the SDK RTOS API or not */
/*--------------------------------------------------------------------------*/
#if USE_SDK_RTOS
/* Kinetis SDK Task variables and defines */
//#define SDK_TASK_STACK_SIZE  200 /* Task stack size (in 32bit units) */
#define SDK_TASK_PRIO        0 /* task priority */
static void sdk_task(void *param); /* prototype of the task */
//FSL_RTOS_TASK_DEFINE(sdk_task, SDK_TASK_STACK_SIZE, "sdk", false);
static task_handler_t sdk_task_hdl; /* task handle */

/*!
 * \brief Kinetis SDK task, toggles a LED every 1 second.
 * \param param task parameter
 */
static void sdk_task(void *param) {
  (void)param; /* unused parameter */
  for(;;) {
    GPIO_DRV_TogglePinOutput(LED_RED); /* toggle blue LED */
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
#else /* USE_SDK_RTOS */
/*--------------------------------------------------------------------------*/
/* traditional FreeRTOS task API */
static xTaskHandle mainTaskHndl;

static void main_task(void *param) {
  (void)param;
  for(;;) {
    GPIO_DRV_TogglePinOutput(LED_RED); /* toggle red LED */
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
#endif /* USE_SDK_RTOS */

void APP_Start (void) {
  hardware_init(); /* initialize the hardware */
  /* create tasks */
#if USE_SDK_RTOS
  SDK_CreateTask(); /* create a task with the Kinetis SDK API */
#else
  CreateTask(); /* create a task with the 'traditional' FreeRTOS API */
#endif
  vTaskStartScheduler(); /* start FreeRTOS scheduler, does usually not return! */
}

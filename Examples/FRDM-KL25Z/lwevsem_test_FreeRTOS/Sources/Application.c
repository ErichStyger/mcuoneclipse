/*
 * Application.c
 *
 *  Created on: Apr 18, 2013
 */
#include "Application.h"
#include "FRTOS1.h"
#include "LED1.h"
#include <stdio.h>
#include "TI1.h"
#include "TI2.h"

#define USE_PRINTF    0 /* if using printf(), then change librarian to 'ewl_hosted', otherwise 'ewl_noio' */
#define REPORT_STACK  (0 && USE_PRINTF) /* need to enable 'Trace Facility' in FreeRTOS for this */

/* stack sizes for reference. These are stack units (so 4 bytes each) */
#define STACK_SIZE_IDLE   (configMINIMAL_STACK_SIZE)    /* 30 */
#define STACK_SIZE_TASK   (configMINIMAL_STACK_SIZE+10)
#if USE_PRINTF 
  #define STACK_SIZE_TASK_PRINTF (170)
#else
  #define STACK_SIZE_TASK_PRINTF (STACK_SIZE_TASK)
#endif
/* heap settings: 
 * with printf(): 1900
 * without printf(): 1220 (reduced by printf() stack size 
 */


int task1_counter;
xSemaphoreHandle sem;
LDD_TDeviceData   * ti1_device_data;

static portTASK_FUNCTION(Task1, pvParameters) {
  (void)pvParameters; /* parameter not used */
  FRTOS1_vSemaphoreCreateBinary(sem);
  if (sem==NULL) { /* semaphore creation failed */
    for(;;){} /* error */
  }
  ti1_device_data = TI1_Init(NULL);
  for(;;) {
    task1_counter++;
    FRTOS1_xSemaphoreTake(sem, 100);
    LED1_NegVal(NULL);
  }
}

int task2_counter;
xQueueHandle eventHandle;
LDD_TDeviceData * ti2_device_data;

static portTASK_FUNCTION(Task2, pvParameters) {
  (void)pvParameters; /* parameter not used */
  eventHandle = FRTOS1_xQueueCreate(1, 0);
  ti2_device_data = TI2_Init(NULL);
  for(;;) {
    FRTOS1_xQueueReceive(eventHandle, NULL, portMAX_DELAY);
    task2_counter++;
  }
}

#if REPORT_STACK
static unsigned char buf[5*40];
#endif

int task3_counter;
static portTASK_FUNCTION(Task3, pvParameters) {
  (void)pvParameters; /* parameter not used */
#if USE_PRINTF
  printf("Starting Task 3\n");
#endif
  for(;;) {
    FRTOS1_vTaskDelay(100);
#if  USE_PRINTF
    printf("%d\n",task3_counter++);
#endif
#if REPORT_STACK
    FRTOS1_vTaskList(buf, sizeof(buf));
    printf((char*)buf);
    printf("\r\nheap: %d\r\n", FRTOS1_xPortGetFreeHeapSize());
#endif
  }
}

int task4_counter;
static portTASK_FUNCTION(Task4, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    task4_counter++;
    FRTOS1_vTaskDelay(200);
  }
}

void APP_Init(void) {
  if (FRTOS1_xTaskCreate(
        Task1,  /* pointer to the task */
        (signed char *)"T1", /* task name for kernel awareness debugging */
        STACK_SIZE_TASK, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
  if (FRTOS1_xTaskCreate(
        Task2,  /* pointer to the task */
        (signed char *)"T2", /* task name for kernel awareness debugging */
        STACK_SIZE_TASK, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
  if (FRTOS1_xTaskCreate(
        Task3,  /* pointer to the task */
        (signed char *)"T3", /* task name for kernel awareness debugging */
        STACK_SIZE_TASK_PRINTF, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
#if 0
  if (FRTOS1_xTaskCreate(
        Task4,  /* pointer to the task */
        (signed char *)"T4", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
#endif
}

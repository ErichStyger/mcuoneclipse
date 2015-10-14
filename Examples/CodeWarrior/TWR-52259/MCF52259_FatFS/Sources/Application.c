/*
 * Application.c
 *      Author: Erich Styger
 */

#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "LED4.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "WAIT1.h"

static portTASK_FUNCTION(Task1, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
}

static portTASK_FUNCTION(Task2, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED2_Neg();
    FRTOS1_vTaskDelay(200/portTICK_RATE_MS);
  }
}

static portTASK_FUNCTION(Task3, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED3_Neg();
    FRTOS1_vTaskDelay(400/portTICK_RATE_MS);
  }
}

static portTASK_FUNCTION(Task4, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED4_Neg();
    FRTOS1_vTaskDelay(800/portTICK_RATE_MS);
  }
}

void APP_Run(void) {
  uint16_t i;

  for(i=0;i<16;i++) {
    LED1_Neg();
    LED2_Neg();
    LED3_Neg();
    LED4_Neg();
    WAIT1_Waitms(50);
  }
  SHELL_Init();
  if (FRTOS1_xTaskCreate(
        Task1,  /* pointer to the task */
        "Task1", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  if (FRTOS1_xTaskCreate(
        Task2,  /* pointer to the task */
        "Task2", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  if (FRTOS1_xTaskCreate(
        Task3,  /* pointer to the task */
        "Task3", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  if (FRTOS1_xTaskCreate(
        Task4,  /* pointer to the task */
        "Task4", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  FRTOS1_vTaskStartScheduler();
}

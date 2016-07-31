/*
 * application.c
 *
 *  Created on: 28.07.2016
 *      Author: Erich Styger Local
 */

#include "application.h"
#include "FreeRTOS.h"
#include "task.h"
#include "fsl_gpio.h"
#include "PTRC1.h"
#include "RTT1.h"

#define LED_RED_BIT     11 /* PTE11 */
#define LED_GREEN_BIT   12 /* PTE12 */
#define LED_ORANGE_BIT  30 /* PTE30 */
#define LED_BLUE_BIT    29 /* PTE29 */

static const gpio_pin_config_t LED_configOutput = {
    kGPIO_DigitalOutput,  /* use as output pin */
  1,  /* initial value */
};


static void blinky_task2(void *param) {
  (void)param;
  for(;;) {
    GPIO_TogglePinsOutput(GPIOE, 1<<LED_RED_BIT);
    vTaskDelay(100/portTICK_RATE_MS);
    GPIO_TogglePinsOutput(GPIOE, 1<<LED_RED_BIT);

    GPIO_TogglePinsOutput(GPIOE, 1<<LED_GREEN_BIT);
    vTaskDelay(100/portTICK_RATE_MS);
    GPIO_TogglePinsOutput(GPIOE, 1<<LED_GREEN_BIT);
  } /* for */
}

static void blinky_task1(void *param) {
  (void)param;
  for(;;) {
    GPIO_TogglePinsOutput(GPIOE, 1<<LED_ORANGE_BIT);
    vTaskDelay(50/portTICK_RATE_MS);
    GPIO_TogglePinsOutput(GPIOE, 1<<LED_ORANGE_BIT);

    GPIO_TogglePinsOutput(GPIOE, 1<<LED_BLUE_BIT);
    vTaskDelay(50/portTICK_RATE_MS);
    GPIO_TogglePinsOutput(GPIOE, 1<<LED_BLUE_BIT);
  } /* for */
}

/*!
 * @brief Initialize GPIO.
 */
static void InitGPIO(void) {
  GPIO_PinInit(GPIOE, LED_RED_BIT, &LED_configOutput);
  GPIO_PinInit(GPIOE, LED_GREEN_BIT, &LED_configOutput);
  GPIO_PinInit(GPIOE, LED_ORANGE_BIT, &LED_configOutput);
  GPIO_PinInit(GPIOE, LED_BLUE_BIT, &LED_configOutput);
}


void APP_Run(void) {
  RTT1_Init();
#if configUSE_TRACE_HOOKS
  vTraceInitTraceData();
#endif
  InitGPIO();
  if (xTaskCreate(
      blinky_task1,  /* task function */
      "Blinky1", /* task name for kernel awareness */
      configMINIMAL_STACK_SIZE, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY,  /* initial priority */
      NULL /* task handle */
    ) != pdPASS) {
    for(;;){} /* error! probably out of memory */
  }
  if (xTaskCreate(
      blinky_task2,  /* task function */
      "Blinky2", /* task name for kernel awareness */
      configMINIMAL_STACK_SIZE, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY,  /* initial priority */
      NULL /* task handle */
    ) != pdPASS) {
    for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
}


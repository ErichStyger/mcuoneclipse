/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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
#if 1
#include "fsl_port_hal.h"
#include "fsl_gpio_driver.h"
#include "fsl_os_abstraction_free_rtos.h"

#define USE_RTOS (FSL_RTOS_SELECTED == FSL_RTOS_FREE_RTOS) /* enable first RTOS in the abstraction layer fsl_rtos_abstraction.h, otherwise build will fail */
enum _gpio_pins
{
    kGpioRLED  = 0x0,  //!< Red LED.
    kGpioGLED  = 0x1,  //!< Green LED.
    kGpioBLED  = 0x2,  //!< Blue LED.
};

/*!
 * \brief Initialize the hardware so we can use the LEDs.
 */

#if USE_RTOS
static sync_object_declare(lockObject);
static event_object_t eventObject;

static xTaskHandle redTaskHandle, greenTaskHandle;

static portTASK_FUNCTION(redTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    (void)sync_signal(&lockObject); /* do not check result: give token even if already given */
    gpio_toggle_pin_output(kGpioRLED);
    vTaskDelay(1000/portTICK_RATE_MS);
  }
}

static portTASK_FUNCTION(greenTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    if (sync_wait(&lockObject, 2000/portTICK_RATE_MS)==kSuccess) { /* sync with timeout on token */
      /* received object */
      gpio_toggle_pin_output(kGpioGLED);
    }
    vTaskDelay(1200/portTICK_RATE_MS); /* wait time, so the other task can give token */
    if (sync_poll(&lockObject)==kSuccess) { /* poll token */
      gpio_toggle_pin_output(kGpioGLED);
    }
  }
}

static void Finish(void) {
  if (redTaskHandle!=NULL) {
    if (task_destroy(redTaskHandle)!=kSuccess) {
      for(;;);
    }
  }
  if (greenTaskHandle!=NULL) {
    if (task_destroy(greenTaskHandle)!=kSuccess) {
      for(;;);
    }
  }
}

FSL_RTOS_TASK_DEFINE(redTask, configMINIMAL_STACK_SIZE+50, "Red", FALSE);
FSL_RTOS_TASK_DEFINE(greenTask, configMINIMAL_STACK_SIZE+100, "Green", FALSE);

static void TestEvents(void) {
  event_group_t waitFlags;

  if (event_create(eventObject, kEventAutoClr)!=kSuccess) {
    for(;;){} /* creation of sync objec failed */
  }
  if (event_set(&eventObject, 0x13)!=kSuccess) {
    for(;;){} /* setting event flag failed? */
  }
  if (event_clear(&eventObject, 0x13)!=kSuccess) {
    for(;;){} /* clearing event flag failed? */
  }
  if (event_set(&eventObject, 0x2)!=kSuccess) {
    for(;;){} /* setting event flag failed? */
  }
  if (event_check_flags(&eventObject, 0x2)!=kFlagSet) {
    for(;;){} /* flag should be set! */
  }
  if (event_check_flags(&eventObject, 0x4)!=kFlagNotSet) {
    for(;;){} /* flag should NOT be set! */
  }
  waitFlags = 0x2;
  if (event_wait(&eventObject, 500, &waitFlags)!=kSuccess) {
    for(;;){} /* setting event flag failed? */
  }
}

static MSG_QUEUE_DECLARE(myQueue, 8, 4);

static void TestQueues(void) {
  msg_queue_handler_t queue;
  int item = 5;
  int *p = &item;
  int *q;

  queue = msg_queue_create(&myQueue, 8, sizeof(int*));
  if (msg_queue_put(queue, &p)!=kSuccess) { /* put pointer to object into queue */
    for(;;){} /* failed? */
  }
  if (msg_queue_get(queue, (msg_queue_item_t*)&q, 0)!=kSuccess) {
    for(;;){} /* failed? */
  }
  if (q!=&item || *q!=5) {
    for(;;){} /* failed? */
  }
}

void RTOS_Test(void) {
  if (sync_create(lockObject)!=kSuccess) {
    for(;;){} /* creation of sync objec failed */
  }

  TestEvents();
  TestQueues();

  if (task_create(redTask, tskIDLE_PRIORITY, NULL, &redTaskHandle)!=kSuccess) {
    for(;;){} /* error creating task */
  }
  if (task_create(greenTask, tskIDLE_PRIORITY, NULL, &greenTaskHandle)!=kSuccess) {
    for(;;){} /* error creating task */
  }
  vTaskStartScheduler(); /* does not return unless scheduler gets terminated */
  Finish();
}
#endif /* USE_RTOS */

#endif

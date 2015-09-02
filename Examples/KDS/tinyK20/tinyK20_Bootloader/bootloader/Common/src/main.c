/* CMSIS-DAP Interface Firmware
 * Copyright (c) 2009-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <RTL.h>
#include <rl_usb.h>
#if 1 /* << EST */
#include "FreeRTOS.h"
#include "event_groups.h"
#endif

#include <stdint.h>

#include "tasks.h"
#include "flash_hal.h"
#include "main.h"
#include "gpio.h"
#include "version.h"
#include "vector_table.h"

// Reference to our main task
#if 0 /* << EST */
OS_TID mainTask, ledTask;
#else
EventGroupHandle_t transferEventGroup;
#endif

#define INITIAL_SP      (*(uint32_t *)(START_APP_ADDRESS))
#define RESET_HANDLER   (*(uint32_t *)(START_APP_ADDRESS + 4))

#if 0 /* << EST moved to main.h */
#define TRANSFER_FINISHED_SUCCESS       (1 << 0)
#define TRANSFER_FINISHED_FAIL          (1 << 1)
#endif

void main_transfer_finished(uint8_t success) {
#if 0 /* << EST */
    if (success) {
        isr_evt_set(TRANSFER_FINISHED_SUCCESS, mainTask);
    } else {
        isr_evt_set(TRANSFER_FINISHED_FAIL, mainTask);
    }
#else
    if (success) {
      xEventGroupSetBitsFromISR(transferEventGroup, TRANSFER_FINISHED_SUCCESS, NULL);
    } else {
      xEventGroupSetBitsFromISR(transferEventGroup, TRANSFER_FINISHED_FAIL, NULL);
    }
#endif
}

#if 0 /* << EST */
__asm void modify_stack_pointer_and_start_app(uint32_t r0_sp, uint32_t r1_pc) {
    MOV SP, R0
    BX R1
}
#endif

#if 0 /* << EST */
__task void led_task(void) {
    BOOL led_state = __FALSE;
    os_itv_set(100); // 100mS

    while(1) {
        gpio_set_cdc_led(led_state);
        led_state = !led_state;
        os_itv_wait();
    }
}
#else
static void led_task(void *param) {
  uint8_t led_state = 0;

  (void)param; /* not used */
  for(;;) {
    gpio_set_cdc_led(led_state);
    led_state = !led_state;
    vTaskDelay(pdMS_TO_TICKS(100));
  } /* for */
}
#endif

#if 0 /* << EST */
__task void main_task(void) {
    BOOL led_state = __FALSE;
    uint8_t flags, time_blink_led;
    
	mainTask=os_tsk_self();
	ledTask = os_tsk_create(led_task, LED_TASK_PRIORITY);

    update_html_file();

    usbd_init();
    usbd_connect(__TRUE);

    os_evt_wait_or(TRANSFER_FINISHED_SUCCESS | TRANSFER_FINISHED_FAIL, NO_TIMEOUT);

    os_dly_wait(200);

    usbd_connect(__FALSE);

    // Find out what event happened
    flags = os_evt_get();
	
    time_blink_led = (flags & TRANSFER_FINISHED_SUCCESS) ? 10 : 50;
	// if we blink here, dont do it in a thread
	os_tsk_delete(ledTask);
	
    while(1) {
        gpio_set_msd_led(led_state);
        led_state = !led_state;
        os_dly_wait(time_blink_led);
    }
}
#else
static void main_task(void *param) {
  uint8_t led_state = 0;
  uint8_t time_blink_led;
  EventBits_t flags;
  TaskHandle_t ledTask;

  (void)param; /* not used */
  transferEventGroup = xEventGroupCreate();
  if (transferEventGroup==NULL) {
    for(;;); /* failed? */
  }
  if (xTaskCreate(led_task, "Led", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIORITY, &ledTask) != pdPASS) {
    for(;;){} /* error! probably out of memory */
  }

  update_html_file();

  usbd_init();
  usbd_connect(__TRUE);

  /* wait for any of the bits, do not clear them */
  (void)xEventGroupWaitBits(transferEventGroup, TRANSFER_FINISHED_SUCCESS|TRANSFER_FINISHED_FAIL, pdFALSE, pdFALSE, 0);

  vTaskDelay(pdMS_TO_TICKS(200));

  usbd_connect(__FALSE);

  // Find out what event happened
  flags = xEventGroupGetBits(transferEventGroup);

  time_blink_led = (flags & TRANSFER_FINISHED_SUCCESS) ? 10 : 50;
  // if we blink here, don't do it in a thread
  vTaskDelete(ledTask);
  for(;;) {
    gpio_set_msd_led(led_state);
    led_state = !led_state;
    vTaskDelay(pdMS_TO_TICKS(time_blink_led));
  }
}
#endif

// Main Program
int main (void)
{	
    gpio_init();

#if 0 /* << EST */
    if (!gpio_get_pin_loader_state()) {
#else
    {
#endif
#if 0 /* << EST */
        os_sys_init(main_task);
#else
        if (xTaskCreate(main_task, "Main", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
          for(;;){} /* error! probably out of memory */
        }
        vTaskStartScheduler(); /* start scheduler */
#endif
    }

    relocate_vector_table();

    // modify stack pointer and start app
#if 0 /* << EST */ /* \todo EST modify_stack_pointer_and_start_app() */
    modify_stack_pointer_and_start_app(INITIAL_SP, RESET_HANDLER);
#endif
}

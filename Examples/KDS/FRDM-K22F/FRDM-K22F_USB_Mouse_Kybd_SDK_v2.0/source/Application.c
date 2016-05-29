/*
 * Application.c
 *
 *  Created on: 08.05.2016
 *      Author: Erich Styger
 */

#include "Application.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "fsl_gpio.h"
#include "UTIL1.h"
#include "ShellQueue.h"
#include "fsl_debug_console.h"

/* tracing ISR in USB0_IRQHandler() */

xSemaphoreHandle semSW2, semSW3, semLED, semMouse, semKbd;
#define BUFFER_SIZE   256

void vApplicationMallocFailedHook(void) {
  taskDISABLE_INTERRUPTS();
  for(;;) {}
}

void vApplicationStackOverflowHook(xTaskHandle pxTask, char *pcTaskName)
{
  /* This will get called if a stack overflow is detected during the context
     switch.  Set configCHECK_FOR_STACK_OVERFLOWS to 2 to also check for stack
     problems within nested interrupts, but only do this for debug purposes as
     it will increase the context switch time. */
  (void)pxTask;
  (void)pcTaskName;
  taskDISABLE_INTERRUPTS();
  for(;;) {}
}

static void PrintButtonPressed(uint16_t whichButton, bool pressed) {
  unsigned char buffer[BUFFER_SIZE];

  UTIL1_strcpy(buffer, sizeof(buffer), (uint8_t*)"Push button SW");
  UTIL1_strcatNum16u(buffer, sizeof(buffer), whichButton);
  if (pressed) {
    UTIL1_strcat(buffer, sizeof(buffer), (uint8_t*)" pressed\r\n!");
  } else {
    UTIL1_strcat(buffer, sizeof(buffer), (uint8_t*)" released\r\n!");
  }
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SEGGER_SYSVIEW_Print((const char*)buffer);
#endif
#if PL_CONFIG_HAS_SHELL_QUEUE
  SQUEUE_SendString(buffer);
#endif
}

void PrintDebugMessage(const unsigned char *msg) {
  DbgConsole_Printf((char*)msg);
  vPortFree((void*)msg); /*! \todo 8 Fix Memory leak */
}

void vMainConfigureTimerForRunTimeStats(void) {
}

unsigned int ulMainGetRunTimeCounterValue(void) {
  return xTaskGetTickCountFromISR();
}

static bool SW2IsPressed(void) {
  return GPIO_ReadPinInput(GPIOC, 1u)==0; /* SW2 on PTC1 */
}

static bool SW3IsPressed(void) {
  return GPIO_ReadPinInput(GPIOB, 17u)==0; /* SW3 on PTB17 */
}

/* SW2: PTC1 (near USB)
 * SW3: PTB17
 */
static void ButtonTask(void *pvParameters) {
  (void)pvParameters;
  /* TODO this is the normal way */
  /* todo this is another to-do */
  /*! \todo this is a doxygen to-do */
  for(;;) {
    if (SW2IsPressed()) { /* SW2 pressed */
      PrintButtonPressed(2, TRUE);
      vTaskDelay(pdMS_TO_TICKS(50)); /* debounce */
      while(SW2IsPressed()) { /* wait until released */
        vTaskDelay(pdMS_TO_TICKS(50)); /*! \todo 4 Add delay of 50 ms */
      }
      PrintButtonPressed(2, FALSE);
      (void)xSemaphoreGive(semSW2); /* send message to toggle USB */
      (void)xSemaphoreGive(semMouse); /* send message to toggle USB */
      (void)xSemaphoreGive(semKbd); /* send message to toggle USB */
    }
    if (SW3IsPressed()) { /* SW3 pressed */
      PrintButtonPressed(3, TRUE);
      vTaskDelay(pdMS_TO_TICKS(50)); /* debounce */
      while(SW3IsPressed()) { /* wait until released */
        vTaskDelay(pdMS_TO_TICKS(50)); /*! \todo 5 Add delay of 50 ms */
      }
      PrintButtonPressed(3, FALSE);
      (void)xSemaphoreGive(semSW3); /* send message */
      (void)xSemaphoreGive(semLED); /* send message to change LED */
    }
    vTaskDelay(pdMS_TO_TICKS(10)); /*! \todo 2 Add delay of 10 ms */
  }
}

#define DEBUG_PRINT  1 /*! \todo 7 Set macro value to 1 to enable debug printing */

static void AppTask(void *pvParameters) {
  (void)pvParameters;
  for(;;) {
#if DEBUG_PRINT && PL_CONFIG_HAS_SHELL_QUEUE
    {
      const unsigned char *msg;

      msg = SQUEUE_ReceiveMessage();
      if (msg!=NULL) {
        PrintDebugMessage(msg);
      }
    }
#endif /* PL_CONFIG_HAS_SHELL_QUEUE */
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

void APP_Init(void) {
  //DbgConsole_Printf("hello world.\r\n");
#if PL_CONFIG_HAS_SHELL_QUEUE
  SQUEUE_Init();
#endif
  semSW2 = xSemaphoreCreateBinary();
  if (semSW2==NULL) { /* semaphore creation failed */
    for(;;){} /* error */
  }
  vQueueAddToRegistry(semSW2, "Sem_SW2");

  semSW3 = xSemaphoreCreateBinary();
  if (semSW3==NULL) { /* semaphore creation failed */
    for(;;){} /* error */
  }
  vQueueAddToRegistry(semSW3, "Sem_SW3");

  semLED = xSemaphoreCreateBinary();
  if (semLED==NULL) { /* semaphore creation failed */
    for(;;){} /* error */
  }
  vQueueAddToRegistry(semLED, "Sem_LED");

  semMouse = xSemaphoreCreateBinary();
  if (semMouse==NULL) { /* semaphore creation failed */
    for(;;){} /* error */
  }
  vQueueAddToRegistry(semMouse, "Sem_Mouse");

  semKbd = xSemaphoreCreateBinary();
  if (semKbd==NULL) { /* semaphore creation failed */
    for(;;){} /* error */
  }
  vQueueAddToRegistry(semKbd, "Sem_Kbd");
#if 1  /*! \todo 1 Increase stack size by 100 */
  if (xTaskCreate(ButtonTask, "Buttons", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
#else
    if (xTaskCreate(ButtonTask, "Buttons", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
#endif
    for(;;){} /* error */
  }
  if (xTaskCreate(AppTask, "App", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#if configUSE_TRACE_HOOKS
  vTraceSetISRProperties("ISR_USB", TRACE_PRIO_ISR_USB);
#endif
}

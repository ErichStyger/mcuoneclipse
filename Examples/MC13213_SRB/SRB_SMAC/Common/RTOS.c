/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_HAS_RTOS
#include "RTOS.h"
#include "FRTOS1.h"
#include "Event.h"
#include "Mealy.h"
#include "Application.h"
#include "Keys.h"
#include "LED.h"
#if PL_HAS_RTOS_TRACE
  #include "Ptrc1.h"
  #include "ISRtrace.h"
#endif
#if PL_HAS_RADIO
  #include "Radio.h"
#endif

#define USE_TEST_TASKS  1


#if USE_TEST_TASKS
static portTASK_FUNCTION(Task1, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    //FRTOS1_vTaskSuspendAll();
    FRTOS1_taskENTER_CRITICAL();
    //FRTOS1_taskDISABLE_INTERRUPTS();
    LED1_Neg();
    //FRTOS1_taskENABLE_INTERRUPTS();
    FRTOS1_taskEXIT_CRITICAL();
    //(void)FRTOS1_xTaskResumeAll();
    //FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
    FRTOS1_taskYIELD();
  }
}

static portTASK_FUNCTION(Task2, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    //FRTOS1_vTaskSuspendAll();
    FRTOS1_taskENTER_CRITICAL();
    //FRTOS1_taskDISABLE_INTERRUPTS();
    LED2_Neg();
    //FRTOS1_taskENABLE_INTERRUPTS();
    FRTOS1_taskEXIT_CRITICAL();
    //(void)FRTOS1_xTaskResumeAll();
    //FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
    FRTOS1_taskYIELD();
  }
}
#endif

static portTASK_FUNCTION(MainTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
#if PL_POLL_KEYS
    KEY_Scan();
#endif
#if PL_HAS_MEALY
    MEALY_Run();
#endif
#if PL_HAS_EVENTS
    EVNT_HandleEvent(APP_HandleEvent);
#endif
#if PL_HAS_RADIO
    RADIO_Handle();
#endif
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
    //WAIT1_Waitms(10);
  }
}

#if PL_HAS_RTOS_TRACE
void DBGU_Print_Ascii(char * buffer);

void DBGU_Print_Ascii(char * buffer) {
  CLS1_SendStr((unsigned char*)buffer, CLS1_GetStdio()->stdOut);
}
#endif


void RTOS_Run(void) {
  if (FRTOS1_xTaskCreate(
        MainTask,  /* pointer to the task */
        (signed portCHAR *)"Main", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE+100, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
#if USE_TEST_TASKS
  if (FRTOS1_xTaskCreate(
        Task1,  /* pointer to the task */
        (signed portCHAR *)"Task1", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE+100, /* task stack size */
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
        (signed portCHAR *)"Task2", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE+100, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
#endif
  FRTOS1_vTaskStartScheduler();
}

#endif /* PL_HAS_RTOS */

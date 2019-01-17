/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM-K64F_FreeRTOS
**     Processor   : MK64FN1M0VLL12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-16, 16:44, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "FRTOS1.h"
#include "RTOSCNTRLDD1.h"
#include "MCUC1.h"
#include "UTIL1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "RTT1.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "CS1.h"
#include "XF1.h"
#include "SYS1.h"
#include "HF1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#define USE_HEAP_INDICATOR  1
#if configUSE_HEAP_SCHEME == 5
static uint8_t heapRegion1[1000];
static uint8_t heapRegion2[1000];
static uint8_t heapRegion3[2000];

static HeapRegion_t xHeapRegions[] =
{
  {(uint8_t*) heapRegion1, sizeof(heapRegion1) }, /* Defines the block with start address and size */
  {(uint8_t*) heapRegion2, sizeof(heapRegion1) }, /* Defines the block with start address and size */
  {(uint8_t*) heapRegion3, sizeof(heapRegion3) }, /* Defines the block with start address and size */
  {NULL, 0}  /* Terminates the array. */
};
#endif
#if USE_HEAP_INDICATOR
  const uint8_t freeRTOSMemoryScheme = configUSE_HEAP_SCHEME;
#endif

static SemaphoreHandle_t sem = NULL;
static xQueueHandle queue = NULL;

static void LedTask(void *param) {
  uint8_t cntr;

  for(;;) {
    LED1_On();
    vTaskDelay(pdMS_TO_TICKS(10));
    LED1_Off();
    vTaskDelay(pdMS_TO_TICKS(10));
    xQueueReceive(queue, &cntr, pdMS_TO_TICKS(1000));
  }
}

static void MainTask(void *param) {
  uint8_t cntr = 0;
  for(;;) {
    cntr++;
    LED1_Neg();
    xQueueSendToBack(queue, &cntr, pdMS_TO_TICKS(100));
    vTaskDelay(pdMS_TO_TICKS(500));
    vTaskEndScheduler();
  }
}

int Test2(int a, int b) {
  return a+b;
}

void Test(int a) {
  a = Test2(a, 5);
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  unsigned int checkers[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

#if configUSE_HEAP_SCHEME == 5
  vPortDefineHeapRegions(xHeapRegions);
#endif
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  sem = xSemaphoreCreateBinary();
  if (sem==NULL) { /* semaphore creation failed */
    for(;;){} /* error */
  }
  vQueueAddToRegistry(sem, "MySemaphore");
  queue = xQueueCreate(32, sizeof(uint8_t));
  if (queue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(queue, "ShellQueue");
  if (xTaskCreate(
      MainTask,  /* pointer to the task */
      "Main", /* task name for kernel awareness debugging */
      100, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
    /*lint -e527 */
     for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
  if (xTaskCreate(
      LedTask,  /* pointer to the task */
      "Led", /* task name for kernel awareness debugging */
      100, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+1,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
    /*lint -e527 */
     for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
  vTaskStartScheduler();
  Test(checkers[0]);
  for(;;) {}
#if USE_HEAP_INDICATOR
  if (freeRTOSMemoryScheme==0) { /* reference the variable */
    for(;;);
  }
#endif
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

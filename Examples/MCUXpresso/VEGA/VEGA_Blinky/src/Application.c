/*
 * Application.c
 *
 *  Created on: 13.03.2019
 *      Author: Erich Styger Local
 */

#include "Application.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuLED1.h"
#include "McuLED2.h"
#include "McuLED3.h"
#include "McuLED4.h"
#include "McuRTOS.h"
#include "FreeRTOS.h"
#include "task.h"

#include "fsl_clock.h"

void vPortSetupTimerInterrupt( void ) {
  extern void SystemSetupSystick(uint32_t tickRateHz, uint32_t intPriority );

  /* No CLINT so use the LPIT (Low Power Interrupt Timer) to generate the tick interrupt. */
  CLOCK_SetIpSrc(kCLOCK_Lpit0, kCLOCK_IpSrcFircAsync);
  SystemSetupSystick(configTICK_RATE_HZ, configKERNEL_INTERRUPT_PRIORITY-1);
}

/*-----------------------------------------------------------*/

void LPIT0_IRQHandler( void )
{
BaseType_t xTaskIncrementTick( void );
void vTaskSwitchContext( void );

#warning requires critical section if interrpt nesting is used.

  /* vPortSetupTimerInterrupt() uses LPIT0 to generate the tick interrupt. */
  if( xTaskIncrementTick() != 0 )
  {
    vTaskSwitchContext();
  }

  /* Clear LPIT0 interrupt. */
  LPIT0->MSR = 1U;
}
/*-----------------------------------------------------------*/

/* At the time of writing, interrupt nesting is not supported, so do not use
the default SystemIrqHandler() implementation as that enables interrupts.  A
version that does not enable interrupts is provided below.  THIS INTERRUPT
HANDLER IS SPECIFIC TO THE VEGA BOARD WHICH DOES NOT INCLUDE A CLINT! */
void SystemIrqHandler( uint32_t mcause )
{
uint32_t ulInterruptNumber;
typedef void ( * irq_handler_t )( void );
extern const irq_handler_t isrTable[];

  ulInterruptNumber = mcause & 0x1FUL;

  /* Clear pending flag in EVENT unit .*/
  EVENT_UNIT->INTPTPENDCLEAR = ( 1U << ulInterruptNumber );

  /* Read back to make sure write finished. */
  (void)(EVENT_UNIT->INTPTPENDCLEAR);

  /* Now call the real irq handler for ulInterruptNumber */
  isrTable[ ulInterruptNumber ]();
}

//void freertos_risc_v_trap_handler(void) {
//  for(;;){}
//}


static void AppTask(void *pv) {
	for(;;) {
		McuLED4_Neg();
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void APP_Run(void) {
  /* initialize McuLib drivers */
  McuLib_Init();
//  McuRTOS_Init();
  McuWait_Init();
  McuLED1_Init(); /* red */
  McuLED2_Init(); /* green */
  McuLED3_Init(); /* blue */
  McuLED4_Init(); /* red status */

//  wait();
  /* test the LEDs */
  McuLED1_On();
  McuLED1_Off();
  McuLED2_On();
  McuLED2_Off();
  McuLED3_On();
  McuLED3_Off();
  McuLED4_On();
  McuLED4_Off();

  if (xTaskCreate(AppTask, "App", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  vTaskStartScheduler();

  for(;;) {
	  McuWait_Waitms(950);
	  McuLED1_On();
	  McuWait_Waitms(50);
	  McuLED1_Off();
  }
}

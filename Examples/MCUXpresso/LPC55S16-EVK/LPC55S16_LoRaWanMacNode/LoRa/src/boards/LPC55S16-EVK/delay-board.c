/*!
 * \file      delay-board.c
 *
 * \brief     Target board delay implementation
 * 
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \author    Diego Bienz (HSLU)
 * \author    Erich Styger (HSLU)
 */

#include "board.h"
#include "delay-board.h"
#include "clock_config.h"
#include "McuLib.h"
#include "McuRTOS.h"
#include "McuWait.h"

void DelayMsMcu(uint32_t ms) {
#if McuLib_CONFIG_SDK_USE_FREERTOS
  if (xTaskGetSchedulerState()!=taskSCHEDULER_RUNNING) {
    McuWait_Waitms(ms); /* if scheduler is not yet running */
  } else { /* use RTOS wait */
    TickType_t xTicks = pdMS_TO_TICKS(ms);
    if (xTicks==0) {
      xTicks = 1; /* wait at least one tick */
    }
    vTaskDelay(xTicks);
  }
#else
  uint32_t ticks = 0UL;
	uint32_t count = ms;

	/* Make a 1 milliseconds counter. */
	ticks = SystemCoreClock / 1000UL;
	assert((ticks - 1UL) <= SysTick_LOAD_RELOAD_Msk);

	/* Enable the SysTick for counting. */
	SysTick->LOAD = (uint32_t) (ticks - 1UL);
	SysTick->VAL = 0UL;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

	for (; count > 0U; count--) {
		/* Wait for the SysTick counter reach 0. */
		while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)) {
		}
	}

	/* Disable SysTick. */
	SysTick->CTRL &= ~(SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);
	SysTick->LOAD = 0UL;
	SysTick->VAL = 0UL;
#endif
}

/*
 * WatchDog.c
 *
 *  Created on: 12.10.2011
 *      Author: Erich Styger
 */
#include "platform.h"
#if PL_HAS_WATCHDOG
#include "WatchDog.h"
#include "WDog1.h"

void WDOG_Clear(void) {
  WDog1_Clear();
}
#endif /* PL_HAS_WATCHDOG */

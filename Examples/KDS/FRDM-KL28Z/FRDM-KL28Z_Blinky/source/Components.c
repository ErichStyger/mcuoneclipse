/*
 * Components.c
 *
 *  Created on: 21.03.2017
 *      Author: Erich Styger Local
 */

#include "Platform.h"
#include "Components.h"
#include "LEDR.h"
#include "LEDG.h"
#include "LEDB.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#if PL_CONFIG_HAS_TIME_DATE
  #include "Shell.h"
  #include "CLS1.h"
  #include "Console.h"
#endif
#if PL_CONFIG_HAS_RTT
  #include "RTT1.h"
#endif
#if PL_CONFIG_HAS_TIME_DATE
  #include "TmDt1.h"
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "SYS1.h"
#endif
#if configUSE_TRACE_HOOKS
  #include "PTRC1.h"
#endif
#if PL_CONFIG_HAS_I2C
  #include "GI2C1.h"
  #include "I2C1.h"
#endif
#if PL_CONFIG_HAS_I2CSPY
  #include "I2CSPY1.h"
#endif
#if PL_CONFIG_HAS_ACCEL
  #include "MMA1.h"
#endif
#if PL_CONFIG_HAS_SPI
  #include "SPI1.h"
#endif
#include "fsl_port.h"

void InitComponents(void) {
  /* Initialize modules */
  CLOCK_EnableClock(kCLOCK_PortC); /* Green led on PTC4 */
  CLOCK_EnableClock(kCLOCK_PortE); /* red LED on PTE29 and blue on PTE31 */

  FRTOS1_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SYS1_Init();
#elif configUSE_TRACE_HOOKS
  PTRC1_Startup();
#endif
  WAIT1_Init();
  LEDR_Init();
  LEDG_Init();
  LEDB_Init();
#if PL_CONFIG_HAS_RTT
  RTT1_Init();
#endif
#if PL_CONFIG_HAS_SHELL
  CLS1_Init();
  SHELL_Init();
  CONSOLE_Init();
#endif
#if PL_CONFIG_HAS_TIME_DATE
  TmDt1_Init();
#endif
#if PL_CONFIG_HAS_I2C
  GI2C1_Init();
  I2C1_Init();
#endif
#if PL_CONFIG_HAS_I2CSPY
  I2CSPY1_Init();
#endif
#if PL_CONFIG_HAS_ACCEL
  (void)MMA1_Init();
#endif
#if PL_CONFIG_HAS_SPI
  SPI1_Init();
#endif
}



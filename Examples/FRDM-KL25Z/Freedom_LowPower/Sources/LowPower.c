/**
 * \file
 * \brief Platform configuration file.
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 */

#include "Platform.h"
#if PL_HAS_LOW_POWER
#include "LowPower.h"
#include "Cpu.h"
#include "FreeRTOS.h"
#if PL_HAS_SHELL
  #include "CLS1.h"
#endif
#if PL_HAS_LED
  #include "LED3.h"
#endif
#include "UTIL1.h"
#include "FRTOS1.h"

#define LP_CAN_CHANGE_CLOCK  0

static bool LP_EnableSTOP;
static LP_PowerMode LP_mode;
#if LP_CAN_CHANGE_CLOCK
static LP_ClockMode LP_clock;
#endif

#include "AS1.h"
/*!
 * \brief Callback called by the RTOS from the IDLE task to know if it can go into tickless idle mode.
 * \return pdTRUE if RTOS can enter tickless idle mode, pdFALSE otherwise.
 */
BaseType_t LP_EnterTicklessIdle(void) {
#if PL_HAS_SHELL
  static TickType_t tickCnt;
  TickType_t newTickCnt;  
  
  if (AS1_GetCharsInRxBuf()!=0) {
    tickCnt = FRTOS1_xTaskGetTickCount();
    return pdFALSE;
  }
  if (AS1_GetCharsInTxBuf()!=0) {
    tickCnt = FRTOS1_xTaskGetTickCount();
    return pdFALSE;
  }
  newTickCnt = FRTOS1_xTaskGetTickCount();
  if (((newTickCnt-tickCnt)*portTICK_RATE_MS)<250) { /* wait 250ms after last activity */
    return pdFALSE;
  }
  return pdTRUE; /* yes, enter tickless idle mode */
#else
  return pdTRUE;
#endif
}


#if LP_CAN_CHANGE_CLOCK
static void LP_ChangeClock(LP_ClockMode mode) {
  LP_clock = mode;
  if (LP_clock==LP_SPEED_FAST) {
    (void)Cpu_SetClockConfiguration(CPU_CLOCK_CONFIG_0);
  } else if (LP_clock==LP_SPEED_MEDIUM) {
    (void)Cpu_SetClockConfiguration(CPU_CLOCK_CONFIG_1);
  }
}
#endif

#if PL_HAS_SHELL
static void PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char *)"LowPower", (unsigned char *)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char *)"  Mode", (unsigned char *)"", io->stdOut);
  if (LP_mode==LP_RUN) {
    CLS1_SendStr((unsigned char *)"RUN\r\n", io->stdOut);
  } else if (LP_mode==LP_WAIT) {
    CLS1_SendStr((unsigned char *)"WAIT\r\n", io->stdOut);
  } else if (LP_mode==LP_SLEEP) {
    CLS1_SendStr((unsigned char *)"SLEEP\r\n", io->stdOut);
  } else if (LP_mode==LP_STOP) {
    CLS1_SendStr((unsigned char *)"STOP\r\n", io->stdOut);
  } else {
    CLS1_SendStr((unsigned char *)"UNKNOWN\r\n", io->stdOut);
  }
#if LP_CAN_CHANGE_CLOCK
  CLS1_SendStatusStr((unsigned char *)"  Speed", (unsigned char *)"", io->stdOut);
  if (LP_clock==LP_SPEED_FAST) {
    CLS1_SendStr((unsigned char *)"FAST\r\n", io->stdOut);
  } else if (LP_clock==LP_SPEED_MEDIUM) {
    CLS1_SendStr((unsigned char *)"MEDIUM\r\n", io->stdOut);
  } else if (LP_clock==LP_SPEED_SLOW) {
    CLS1_SendStr((unsigned char *)"SLOW\r\n", io->stdOut);
  } else {
    CLS1_SendStr((unsigned char *)"UNKNOWN\r\n", io->stdOut);
  }
#endif
}

/*! 
 * \brief Prints the help text to the console
 * \param io I/O channel to be used
 */
static void PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char *)"LowPower", (unsigned char *)"Group of LowPower commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char *)"  help|status", (unsigned char *)"Shows help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char *)"  mode run|wait|sleep|stop", (unsigned char *)"Set low power mode\r\n", io->stdOut);
#if LP_CAN_CHANGE_CLOCK
  CLS1_SendHelpStr((unsigned char *)"  clock fast|medium|slow", (unsigned char *)"Set clock speed mode\r\n", io->stdOut);
#endif
}

uint8_t LP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"LowPower help")==0) {
    PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"LowPower status")==0) {
    PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"LowPower mode run")==0) {
    *handled = TRUE;
    LP_mode = LP_RUN;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"LowPower mode wait")==0) {
    *handled = TRUE;
    LP_mode = LP_WAIT;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"LowPower mode sleep")==0) {
    *handled = TRUE;
    LP_mode = LP_SLEEP;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"LowPower mode stop")==0) {
    *handled = TRUE;
    LP_mode = LP_STOP;
#if LP_CAN_CHANGE_CLOCK
  } else if (UTIL1_strcmp((char*)cmd, (char*)"LowPower clock fast")==0) {
    *handled = TRUE;
    LP_ChangeClock(LP_SPEED_FAST);
  } else if (UTIL1_strcmp((char*)cmd, (char*)"LowPower clock medium")==0) {
    *handled = TRUE;
    LP_ChangeClock(LP_SPEED_MEDIUM);
  } else if (UTIL1_strcmp((char*)cmd, (char*)"LowPower clock slow")==0) {
    *handled = TRUE;
    LP_ChangeClock(LP_SPEED_SLOW);
#endif
  }
  return ERR_OK;
}
#endif

void LP_EnterPowerMode(LP_PowerMode mode) {
  LP_mode = mode;
#if configUSE_TICKLESS_IDLE
  if (LP_mode==LP_RUN) { /* need to wait for interrupt! */
    __asm volatile("dsb");
    __asm volatile("wfi"); /* wait for interrupt */
    __asm volatile("isb");  
  } else 
#endif
  if (LP_mode==LP_WAIT) {
#if PL_HAS_CLOCK_CONFIG 
    Cpu_SetClockConfiguration(CPU_CLOCK_CONFIG_1); /* go into slow speed */
#endif
    Cpu_SetOperationMode(DOM_WAIT, NULL, NULL); /* next interrupt will wake us up */
#if PL_HAS_CLOCK_CONFIG 
    Cpu_SetClockConfiguration(CPU_CLOCK_CONFIG_0); /* go back to normal speed */
#endif
  } else if (LP_mode==LP_SLEEP) {
    Cpu_SetOperationMode(DOM_SLEEP, NULL, NULL); /* next interrupt will wake us up */
  } else if (LP_mode==LP_STOP) {
    if (LP_EnableSTOP) {
      Cpu_SetOperationMode(DOM_STOP, NULL, NULL); /* next interrupt will wake us up */
    } else {
#if 1 /* go at least into WAIT mode */
      Cpu_SetOperationMode(DOM_STOP, NULL, NULL); /* next interrupt will wake us up */
#else
      __asm volatile("dsb");
      __asm volatile("wfi"); /* wait for interrupt */
      __asm volatile("isb");
#endif
    }
  }
  /* interrupt will wake us up, and we are back in RUN mode */
}

void LP_EnterLowPower(void) {
  LP_EnterPowerMode(LP_mode);
}

void LP_SetStopMode(bool enable) {
  LP_EnableSTOP = enable;
}

void LP_Deinit(void) {
  /* nothing to do */
}

void LP_Init(void) {
  LP_mode = LP_WAIT;
//  LP_mode = LP_STOP;
#if LP_CAN_CHANGE_CLOCK
  LP_clock = LP_SPEED_FAST;
#endif
  LP_EnableSTOP = (LP_mode==LP_STOP);
}
#endif /* PL_HAS_LOW_POWER */

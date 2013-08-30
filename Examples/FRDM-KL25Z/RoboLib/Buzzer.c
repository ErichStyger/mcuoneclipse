/*
 * Buzzer.c
 *
 *  Created on: Aug 29, 2013
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_HAS_BUZZER
#include "Buzzer.h"
#include "BUZ1.h"
#include "TRG1.h"
#include "UTIL1.h"

static volatile uint16_t buzIterationCntr, buzPeriodTicks; /* used for buzzer trigger */

static void BUZ_Toggle(void) {
  if (buzIterationCntr==0) {
    BUZ1_ClrVal(); /* turn buzzer off */
  } else {
    buzIterationCntr--;
    BUZ1_NegVal();
    (void)TRG1_AddTrigger(TRG1_SND_OFF, buzPeriodTicks, BUZ_Toggle);
  }
}

uint8_t BUZ_Beep(uint16_t freqHz, uint16_t durationMs) {
  if (buzIterationCntr==0) { /* only if no buzzer is running right now */
    BUZ1_SetVal(); /* turn buzzer on */
    buzPeriodTicks = (1000*TRG1_TICK_PERIOD_MS)/freqHz;
    buzIterationCntr = durationMs/TRG1_TICK_PERIOD_MS/buzPeriodTicks;
    (void)TRG1_AddTrigger(TRG1_SND_OFF, buzPeriodTicks, BUZ_Toggle);
  } else {
    return ERR_BUSY;
  }
  return ERR_OK;
}

static uint8_t BUZ_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"buzzer", (unsigned char*)"Group of buzzer commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows radio help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  buz <freq> <time>", (unsigned char*)"Beep for time (ms) and frequency (kHz)\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t BUZ_PrintStatus(const CLS1_StdIOType *io) {
  //CLS1_SendStatusStr((unsigned char*)"buzz", (unsigned char*)"\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t BUZ_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  const unsigned char *p;
  uint16_t freq, duration;
  
  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"buzzer help")==0) {
    *handled = TRUE;
    return BUZ_PrintHelp(io);
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"buzzer status")==0) {
    *handled = TRUE;
    return BUZ_PrintStatus(io);
  } else if (UTIL1_strncmp((char*)cmd, (char*)"buzzer buz ", sizeof("buzzer buz ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("buzzer buz ")-1;
    if (UTIL1_ScanDecimal16uNumber(&p, &freq)==ERR_OK && UTIL1_ScanDecimal16uNumber(&p, &duration)==ERR_OK) {
      if (BUZ_Beep(freq, duration)!=ERR_OK) {
        CLS1_SendStr((unsigned char*)"Starting buzzer failed\r\n", io->stdErr);
        return ERR_FAILED;
      }
      return ERR_OK;
    }
  }
  return ERR_OK;
}

void BUZ_Init(void) {
}

#endif /* PL_HAS_BUZZER */

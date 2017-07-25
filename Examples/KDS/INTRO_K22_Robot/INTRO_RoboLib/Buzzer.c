/**
 * \file
 * \brief Buzzer driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for the buzzer.
 */

#include "Platform.h"
#if PL_CONFIG_HAS_BUZZER
#include "Buzzer.h"
#include "BUZ1.h"
#include "Trigger.h"
#include "UTIL1.h"
#if PL_CONFIG_HAS_SHELL
  #include "CLS1.h"
#endif

typedef struct {
  uint16_t buzPeriodTicks; /*!< number of trigger ticks for a PWM period */
  uint16_t buzIterationCntr; /*!< number of iterations */
} BUZ_TrgInfo;

static volatile BUZ_TrgInfo trgInfo;

typedef struct {
  int freq; /* frequency */
  int ms; /* milliseconds */
} BUZ_Tune;

static const BUZ_Tune MelodyWelcome[] =
{ /* freq, ms */
    {300,500},
    {500,200},
    {300,100},
    {200,300},
    {500,400},
    {300,100},
    {200,300},
    {300,100},
    {200,300},
    {500,400},
};

static const BUZ_Tune MelodyButton[] =
{ /* freq, ms */
    {200,100},
    {600,100},
};

static const BUZ_Tune MelodyButtonLong[] =
{ /* freq, ms */
    {500,50},
    {100,100},
    {300,50},
    {150,50},
    {450,50},
    {500,50},
    {250,200},
};

typedef struct {
  int idx; /* current index */
  int maxIdx; /* maximum index */
  BUZ_TrgInfo trgInfo;
  const BUZ_Tune *melody;
} MelodyDesc;

static MelodyDesc BUZ_Melodies[] = {
  {0, sizeof(MelodyWelcome)/sizeof(MelodyWelcome[0]),         {0, 0}, MelodyWelcome}, /* BUZ_TUNE_WELCOME */
  {0, sizeof(MelodyButton)/sizeof(MelodyButton[0]),           {0, 0}, MelodyButton}, /* BUZ_TUNE_BUTTON */
  {0, sizeof(MelodyButtonLong)/sizeof(MelodyButtonLong[0]),   {0, 0}, MelodyButtonLong}, /* BUZ_TUNE_BUTTON_LONG */
};

static void BUZ_Toggle(void *dataPtr) {
  BUZ_TrgInfo *trgInfo = (BUZ_TrgInfo *)dataPtr;

  if (trgInfo->buzIterationCntr==0) {
    BUZ1_ClrVal(); /* turn buzzer off */
  } else {
    trgInfo->buzIterationCntr--;
    BUZ1_NegVal();
    (void)TRG_SetTrigger(TRG_BUZ_BEEP, trgInfo->buzPeriodTicks, BUZ_Toggle, trgInfo);
  }
}

uint8_t BUZ_Beep(uint16_t freq, uint16_t durationMs) {
  if (trgInfo.buzIterationCntr==0) { /* only if buzzer is not running right now */
    BUZ1_SetVal(); /* turn buzzer on */
    trgInfo.buzPeriodTicks = (1000*TRG_TICKS_MS)/freq;
    trgInfo.buzIterationCntr = durationMs/TRG_TICKS_MS/trgInfo.buzPeriodTicks;
    return TRG_SetTrigger(TRG_BUZ_BEEP, trgInfo.buzPeriodTicks, BUZ_Toggle, (void*)&trgInfo);
  } else {
    return ERR_BUSY;
  }
}

static void BUZ_Play(void *dataPtr) {
  MelodyDesc *melody = (MelodyDesc*)dataPtr;

  BUZ_Beep(melody->melody[melody->idx].freq, melody->melody[melody->idx].ms);
  melody->idx++;
  if (melody->idx<melody->maxIdx) {
    TRG_SetTrigger(TRG_BUZ_TUNE, melody->melody[melody->idx-1].ms/TRG_TICKS_MS, BUZ_Play, (void*)melody);
  }
}

void BUZ_StopTune(void) {
  TRG_StopTrigger(TRG_BUZ_TUNE);
}

void BUZ_StopBeep(void) {
  trgInfo.buzIterationCntr = 0;
  TRG_StopTrigger(TRG_BUZ_BEEP);
}

uint8_t BUZ_PlayTune(BUZ_Tunes tune) {
  if (tune>=BUZ_TUNE_NOF_TUNES) {
    return ERR_OVERFLOW;
  }
  BUZ_Melodies[tune].idx = 0; /* reset index */
  return TRG_SetTrigger(TRG_BUZ_TUNE, 0, BUZ_Play, (void*)&BUZ_Melodies[tune]);
}


#if PL_CONFIG_HAS_SHELL
static uint8_t BUZ_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"buzzer", (unsigned char*)"Group of buzzer commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows radio help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  buz <freq> <time>", (unsigned char*)"Beep for time (ms) and frequency (kHz)\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  play tune", (unsigned char*)"Play tune\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t BUZ_PrintStatus(const CLS1_StdIOType *io) {
  (void)io; /* not used */
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
  } else if (UTIL1_strcmp((char*)cmd, (char*)"buzzer play tune")==0) {
    *handled = TRUE;
    return BUZ_PlayTune(BUZ_TUNE_WELCOME);
  }
  return ERR_OK;
}
#endif /* PL_CONFIG_HAS_SHELL */

void BUZ_Deinit(void) {
  /* nothing to do */
}

void BUZ_Init(void) {
  BUZ1_SetVal(); /* turn buzzer off */
  trgInfo.buzPeriodTicks = 0;
  trgInfo.buzIterationCntr = 0;
}
#endif /* PL_CONFIG_HAS_BUZZER */

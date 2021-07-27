/*
 * stepper.c
 *
 *  Created on: 08.08.2019
 *      Author: Erich Styger
 */

#include "platform.h"
#if PL_CONFIG_USE_STEPPER
#include "stepper.h"
#include "McuULN2003.h"
#include "magnets.h"

static McuULN2003_Handle_t motorMinute;
static McuULN2003_Handle_t motorHour;

static TimerHandle_t timerHndl;
#define TIMER_PERIOD_MS   1
#define STEPPER_CLOCK_360_STEPS_HH   (385u) /* number of steps for a full turn on the clock for the hours */
#define STEPPER_CLOCK_360_STEPS_MM   (385u) /* number of steps for a full turn on the clock for the minutes */

#define STEPPER_CLOCK_HH_ZERO_OFFSET (13)   /* offset from the zero position */
#define STEPPER_CLOCK_MM_ZERO_OFFSET (8)   /* offset from the zero position */

typedef struct {
  int32_t targetPos;
  uint32_t delayMs;
  McuULN2003_Handle_t motor;
} StepperMover_t;

static int32_t targetPosHour = 0;
static int32_t targetPosMinute = 0;

static void vTimerCallback(TimerHandle_t pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
  bool finished0, finished1;

  finished0 = McuULN2003_MoveCallback(motorHour, targetPosHour);
  finished1 = McuULN2003_MoveCallback(motorMinute, targetPosMinute);
  if (finished0 && finished1) {
    (void)xTimerStop(timerHndl, 0);
  }
}

void STEPPER_ShowTime(uint8_t hour, uint8_t minute) {
  int32_t posHour, posMinute;

  posMinute = (minute*STEPPER_CLOCK_360_STEPS_MM)/60;
  posHour = (hour*STEPPER_CLOCK_360_STEPS_HH)/12 + (minute*STEPPER_CLOCK_360_STEPS_HH/(12*60));
  targetPosHour = posHour;
  targetPosMinute = posMinute;
  (void)xTimerStart(timerHndl, 0);
}

void STEPPER_Deint(void) {
  motorHour = McuULN2003_DeinitMotor(motorHour);
  motorMinute = McuULN2003_DeinitMotor(motorMinute);
}

uint8_t STEPPER_ZeroHourHand(void) {
  int i;
  uint8_t res = ERR_FAILED;

  while(MAG_TriggeredHH()) {
    McuULN2003_IncStep(motorHour);
  }
  McuULN2003_Step(motorHour, STEPPER_CLOCK_360_STEPS_HH/3);
  for(i=0; i<STEPPER_CLOCK_360_STEPS_HH+(STEPPER_CLOCK_360_STEPS_HH/50); i++) {
    McuULN2003_IncStep(motorHour);
    if (MAG_TriggeredHH()) {
      res = ERR_OK;
      McuULN2003_Step(motorHour, STEPPER_CLOCK_HH_ZERO_OFFSET);
      McuULN2003_SetPos(motorHour, 0);
      break;
    }
  }
  McuULN2003_PowerOff(motorHour);
  return res;
}


uint8_t STEPPER_ZeroMinuteHand(void) {
  int i;
  uint8_t res = ERR_FAILED;

  while(MAG_TriggeredMM()) {
    McuULN2003_IncStep(motorMinute);
  }
  McuULN2003_Step(motorMinute, STEPPER_CLOCK_360_STEPS_MM/3);
  for(i=0; i<STEPPER_CLOCK_360_STEPS_MM+(STEPPER_CLOCK_360_STEPS_MM/50); i++) {
    McuULN2003_IncStep(motorMinute);
    if (MAG_TriggeredMM()) {
      res = ERR_OK;
      McuULN2003_Step(motorMinute, STEPPER_CLOCK_MM_ZERO_OFFSET);
      McuULN2003_SetPos(motorMinute, 0);
      break;
    }
  }
  McuULN2003_PowerOff(motorMinute);
  return res;
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[64];
  int32_t val, pos;

  McuShell_SendStatusStr((unsigned char*)"stepper", (unsigned char*)"\r\n", io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"h: ");
  McuUtility_strcatNum32s(buf, sizeof(buf), STEPPER_CLOCK_360_STEPS_HH);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", m: ");
  McuUtility_strcatNum32s(buf, sizeof(buf), STEPPER_CLOCK_360_STEPS_MM);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  360 steps", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"curr pos: ");
  McuUtility_strcatNum32s(buf, sizeof(buf), McuULN2003_GetPos(motorHour));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", goto pos: ");
  McuUtility_strcatNum32s(buf, sizeof(buf), targetPosHour);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  h pos", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"curr pos: ");
  McuUtility_strcatNum32s(buf, sizeof(buf), McuULN2003_GetPos(motorMinute));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", goto pos: ");
  McuUtility_strcatNum32s(buf, sizeof(buf), targetPosMinute);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  m pos", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"step mode: 1/");
  McuUtility_strcatNum32s(buf, sizeof(buf), McuULN2003_GetStepMode(motorHour));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  h motor", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"step mode: 1/");
  McuUtility_strcatNum32s(buf, sizeof(buf), McuULN2003_GetStepMode(motorMinute));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  m motor", buf, io->stdOut);

  buf[0] = '\0';
  pos = McuULN2003_GetPos(motorHour);
  pos %= STEPPER_CLOCK_360_STEPS_HH;
  val = pos/(STEPPER_CLOCK_360_STEPS_HH/12);
  McuUtility_strcatNum32sFormatted(buf, sizeof(buf), val, '0', 2);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)":");
  pos = McuULN2003_GetPos(motorMinute);
  pos %= STEPPER_CLOCK_360_STEPS_MM;
  val = pos/(STEPPER_CLOCK_360_STEPS_MM/60);
  McuUtility_strcatNum32sFormatted(buf, sizeof(buf), val, '0', 2);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  time", buf, io->stdOut);

  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"stepper", (unsigned char*)"Group of stepper commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  reset", (unsigned char*)"Set stepper pos to zero (12:00 position)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  show <time>", (unsigned char*)"Show time on clock\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  step (h|m) <steps>", (unsigned char*)"perform a number of incremental steps for hour or minute\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  goto (h|m) <pos>", (unsigned char*)"background goto position for hour or minute\r\n", io->stdOut);
#if PL_CONFIG_USE_HALL_SENSOR
  McuShell_SendHelpStr((unsigned char*)"  zero (h|m)", (unsigned char*)"Move hour or minute to zero position\r\n", io->stdOut);
#endif
  return ERR_OK;
}

uint8_t STEPPER_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;
  uint8_t res = ERR_OK;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "stepper help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "stepper status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "stepper reset")==0) {
    *handled = TRUE;
    McuULN2003_SetPos(motorHour, 0);
    McuULN2003_SetPos(motorMinute, 0);
    return ERR_OK;
#if PL_CONFIG_USE_HALL_SENSOR
  } else if (McuUtility_strcmp((char*)cmd, "stepper zero h")==0) {
    *handled = TRUE;
    res = STEPPER_ZeroHourHand();
    if (res!=ERR_OK) {
      McuShell_SendStr((unsigned char*)"failed to find zero position\r\n", io->stdErr);
    }
  } else if (McuUtility_strcmp((char*)cmd, "stepper zero m")==0) {
    *handled = TRUE;
    res = STEPPER_ZeroMinuteHand();
    if (res!=ERR_OK) {
      McuShell_SendStr((unsigned char*)"failed to find zero position\r\n", io->stdErr);
    }
#endif
  } else if (McuUtility_strncmp((char*)cmd, "stepper show ", sizeof("stepper show ")-1)==0) {
    uint8_t hour, minute, second, hsec;

    *handled = TRUE;
    p = cmd + sizeof("stepper show ")-1;
    if (McuUtility_ScanTime(&p, &hour, &minute, &second, &hsec)==ERR_OK) {
      *handled = TRUE;
      STEPPER_ShowTime(hour, minute);
    } else {
      return ERR_FAILED;
    }
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "stepper step ", sizeof("stepper step ")-1)==0) {
    McuULN2003_Handle_t motor = NULL;
    int32_t steps;

    p = cmd + sizeof("stepper step ")-1;
    if (*p=='h') {
      motor = motorHour;
    } else if (*p=='m') {
      motor = motorMinute;
    } else {
      return ERR_FAILED;
    }
    p++;
    if (McuUtility_xatoi(&p, &steps)==ERR_OK) {
      McuULN2003_Step(motor, steps);
      McuULN2003_PowerOff(motor);
    }
    *handled = TRUE;
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "stepper goto ", sizeof("stepper goto ")-1)==0) {
    int32_t *posP = NULL;
    int32_t pos;

    p = cmd + sizeof("stepper goto ")-1;
    if (*p=='h') {
      posP = &targetPosHour;
    } else if (*p=='s') {
      posP = &targetPosMinute;
    } else {
      return ERR_FAILED;
    }
    p++;
    if (McuUtility_xatoi(&p, &pos)==ERR_OK) {
      *posP = pos;
      (void)xTimerStart(timerHndl, 0);
    }
    *handled = TRUE;
    return ERR_OK;
  }
  return res;
}

void STEPPER_Init(void) {
  McuULN2003_Config_t config;

  McuULN2003_GetDefaultConfig(&config);
  config.hw[0].gpio = GPIO;
  config.hw[0].port = 0U;
  config.hw[0].pin = 29U;

  config.hw[1].gpio = GPIO;
  config.hw[1].port = 0U;
  config.hw[1].pin = 28U;

  config.hw[2].gpio = GPIO;
  config.hw[2].port = 0U;
  config.hw[2].pin = 27U;

  config.hw[3].gpio = GPIO;
  config.hw[3].port = 0U;
  config.hw[3].pin = 26U;
  motorMinute = McuULN2003_InitMotor(&config);

  config.hw[0].gpio = GPIO;
  config.hw[0].port = 0U;
  config.hw[0].pin = 23U;

  config.hw[1].gpio = GPIO;
  config.hw[1].port = 0U;
  config.hw[1].pin = 22U;

  config.hw[2].gpio = GPIO;
  config.hw[2].port = 0U;
  config.hw[2].pin = 21U;

  config.hw[3].gpio = GPIO;
  config.hw[3].port = 0U;
  config.hw[3].pin = 20U;
  config.inverted = true;
  motorHour = McuULN2003_InitMotor(&config);

  McuULN2003_PowerOff(motorMinute);
  McuULN2003_PowerOff(motorHour);

  timerHndl = xTimerCreate("stepper", pdMS_TO_TICKS(TIMER_PERIOD_MS), pdTRUE, (void*)0, vTimerCallback);
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) {
    for(;;); /* failure! */
  }
}
#endif /* PL_CONFIG_USE_STEPPER */

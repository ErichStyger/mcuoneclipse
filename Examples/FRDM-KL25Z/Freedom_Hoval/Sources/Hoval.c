/*
 * Hoval.c
 *
 *  Created on: Jul 7, 2013
 *      Author: Erich Styger
 */
#include "Hoval.h"
#include "CLS1.h"
#include "LEDR.h"
#include "FRTOS1.h"
#include "Relay1.h"
#include "Relay2.h"
#include "RTC1.h"
#include "SD_GreenLed.h"
#include "SD_RedLed.h"
#include "SW1.h"
#include "SW2.h"

#define PL_HAS_DATE_SUPPORT        0    /* RTC has not enough RAM to hold date! */
#define HOVAL_CYCLE_TIME_SECONDS   (150*60) /* Cylce after 150 minutes. We need to press the 'manual' button again, as there is a timeout of 180 minutes on Hoval */

/* Relays are LOW active: the relay closes with Low level (red LED turned on) 
 * http://yourduino.com/sunshop2/index.php?l=product_detail&p=218
 */
static bool isRelay1on = FALSE, isRelay2on = FALSE; /* status of the two relays */
static bool isPumpOn = FALSE; /* if the pump (floor/storage) is on */
static bool isHovalManualMode = FALSE; /* status Button on the Hoval heat pump, if it is in manual mode or not */

typedef struct {
  struct {
    uint8_t hour, min, sec;
  } time;
#if PL_HAS_DATE_SUPPORT
  struct {
    uint16_t year;
    uint8_t month, day;
  } date;
#endif
} ScheduleTimeDate;

typedef struct {
  ScheduleTimeDate on, off; /* switch on and off time */
  bool isSchedulerOn; /* If the scheduler is enabled/running */
} Schedule_t;

static Schedule_t mySchedule;

static void StrCatDate(unsigned char *buf, size_t bufSize, uint8_t day, uint8_t month, uint16_t year) {
  UTIL1_strcatNum16uFormatted(buf, bufSize, day, '0', 2);
  UTIL1_chcat(buf, bufSize, '.');
  UTIL1_strcatNum16uFormatted(buf, bufSize, month, '0', 2);
  UTIL1_chcat(buf, bufSize, '.');
  UTIL1_strcatNum16uFormatted(buf, bufSize, year, '0', 4);
}

static void StrCatTime(unsigned char *buf, size_t bufSize, uint8_t hour, uint8_t minute, uint8_t second) {
  UTIL1_strcatNum16uFormatted(buf, bufSize, hour, '0', 2);
  UTIL1_chcat(buf, bufSize, ':');
  UTIL1_strcatNum16uFormatted(buf, bufSize, minute, '0', 2);
  UTIL1_chcat(buf, bufSize, ':');
  UTIL1_strcatNum16uFormatted(buf, bufSize, second, '0', 2);
}

static void Log(unsigned char *msg, const CLS1_StdIOType *io) {
  RTC1_TTIME currTime;
  RTC1_TDATE currDate;
  unsigned char buf[32];

  if (RTC1_GetRTCDate(&currDate)!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"*** Failed to get RTC date\r\n", io->stdErr);
  } else {
    buf[0] = '\0';
    StrCatDate(buf, sizeof(buf), currDate.day, currDate.month, currDate.year+2000);
    CLS1_SendStr(buf, io->stdOut);
  }
  if (RTC1_GetRTCTime(&currTime)!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"*** Failed to get RTC time\r\n", io->stdErr);
  } else {
    buf[0] = '\0';
    UTIL1_chcat(buf, sizeof(buf), ' ');
    StrCatTime(buf, sizeof(buf), currTime.hour, currTime.min, currTime.sec);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)": ");
    CLS1_SendStr(buf, io->stdOut);
  }
  CLS1_SendStr(msg, io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
}

static uint8_t GetRTCData(Schedule_t *schedule) {
  return RTC1_ReadBlock(0, (uint8_t*)schedule, sizeof(Schedule_t));
}

static uint8_t PutRTCData(Schedule_t *schedule) {
  return RTC1_WriteBlock(0, (uint8_t*)schedule, sizeof(Schedule_t));
}

static uint8_t SetOnTime(uint8_t hour, uint8_t minute, uint8_t second) {
  mySchedule.on.time.hour = hour;
  mySchedule.on.time.min = minute;
  mySchedule.on.time.sec = second;
  return PutRTCData(&mySchedule);
}

static uint8_t SetOffTime(uint8_t hour, uint8_t minute, uint8_t second) {
  mySchedule.off.time.hour = hour;
  mySchedule.off.time.min = minute;
  mySchedule.off.time.sec = second;
  return PutRTCData(&mySchedule);
}

#if PL_HAS_DATE_SUPPORT
static uint8_t SetOnDate(uint8_t day, uint8_t month, uint16_t year) {
  mySchedule.on.date.day = day;
  mySchedule.on.date.month = month;
  mySchedule.on.date.year = year;
  return PutRTCData(&mySchedule);
}

static uint8_t SetOffDate(uint8_t day, uint8_t month, uint16_t year) {
  mySchedule.off.date.day = day;
  mySchedule.off.date.month = month;
  mySchedule.off.date.year = year;
  return PutRTCData(&mySchedule);
}
#endif

/* This is the 'manual' button on the Hoval */
static void Button_On(bool on, const CLS1_StdIOType *io) {
  if (on) {
    Log((unsigned char*)"Manual button press", io);
    Relay1_ClrVal();
  } else {
    Log((unsigned char*)"Manual button release", io);
    Relay1_SetVal();
  }
  isRelay1on = on;
}

static void Pump_On(bool on, const CLS1_StdIOType *io) {
  if (on) {
    Log((unsigned char*)"Pump on", io);
    Relay2_ClrVal();
  } else {
    Log((unsigned char*)"Pump off", io);
    Relay2_SetVal();
  }
  isRelay2on = on;
}

static uint32_t TimeToSeconds(uint8_t hours, uint8_t minutes, uint8_t seconds) {
  return hours*3600+minutes*60+seconds;
}

#if PL_HAS_DATE_SUPPORT
static bool isInDateRange(ScheduleTimeDate *begin, ScheduleTimeDate *end) {
  RTC1_TDATE currDate;
  uint16_t beginDayOfYear, endDayOfYear, currDayOfYear;

  if (RTC1_GetRTCDate(&currDate)!=ERR_OK) {
    return FALSE; /* error */
  }
  if (2000+currDate.year<begin->date.year) {
    return FALSE; /* not reached year yet */
  }
  beginDayOfYear = begin->date.month*31+begin->date.day;
  endDayOfYear = end->date.month*31+end->date.day;
  currDayOfYear = currDate.month*31+currDate.day;
  if (beginDayOfYear<=endDayOfYear) { /* normal case, not crossing year boundary */
    return currDayOfYear>=beginDayOfYear && currDayOfYear<=endDayOfYear;
  } else { /* crossing midnight */
    return currDayOfYear<=endDayOfYear || currDayOfYear>=beginDayOfYear;
  }
}
#endif

static bool isInRange(ScheduleTimeDate *begin, ScheduleTimeDate *end) {
  RTC1_TTIME currTime;
  uint32_t beginSeconds, endSeconds, currSeconds;
  
#if PL_HAS_DATE_SUPPORT
  /* check date */
  if (!isInDateRange(begin, end)) {
    return FALSE;
  }
#endif
  /* check time */
  if (RTC1_GetRTCTime(&currTime)!=ERR_OK) {
    return FALSE; /* error case */
  }
  beginSeconds = TimeToSeconds(begin->time.hour, begin->time.min, begin->time.sec);
  endSeconds = TimeToSeconds(end->time.hour, end->time.min, end->time.sec);
  currSeconds = TimeToSeconds(currTime.hour, currTime.min, currTime.sec);
  if (beginSeconds<=endSeconds) { /* normal case, not crossing midnight */
    return currSeconds>=beginSeconds && currSeconds<=endSeconds;
  } else { /* crossing midnight */
    return currSeconds<=endSeconds || currSeconds>=beginSeconds;
  }
}

static void HovalManualButton(bool toManualMode, const CLS1_StdIOType *io) {
  /* press the 'manual' button for a short time */
  if (toManualMode!=isHovalManualMode) {
    Log((unsigned char*)"Toggle manual button", io);
    Button_On(TRUE, io);
    FRTOS1_vTaskDelay(250/portTICK_RATE_MS);
    Button_On(FALSE, io);
    isHovalManualMode = !isHovalManualMode;
    if (isHovalManualMode) {
      Log((unsigned char*)"Manual mode is ON", io);
    } else {
      Log((unsigned char*)"Manual mode is OFF", io);
    }
  }
}

static void SetCooling(bool on, const CLS1_StdIOType *io) {
  if (on) {
    isPumpOn = TRUE;
    HovalManualButton(TRUE, io); /* enable 'manual' mode, Hoval running for 180 minutes */
    /* turn pump on */
    Pump_On(TRUE, io);
  } else {
    isPumpOn = FALSE;
    HovalManualButton(FALSE, io); /* disable manual mode */
    /* now we should be in 'normal' mode, Hoval not running */
    /* turn pump off */
    Pump_On(FALSE, io);
  }
}

static void DisableScheduler(const CLS1_StdIOType *io) {
  if (mySchedule.isSchedulerOn) {
    CLS1_SendStr((unsigned char*)"Disabling scheduler because of shell command\r\n", io->stdOut);
    mySchedule.isSchedulerOn = FALSE;
  }
  HovalManualButton(FALSE, io); /* disable manual mode */
}

static portTASK_FUNCTION(Button, pvParameters) {
  CLS1_ConstStdIOType *io = CLS1_GetStdio();

  (void)pvParameters; /* parameter not used */
  for(;;) {
    /* check push button switch: turns on/off cooling immediately */
    if (SW2_GetVal()==0) { /* button pressed */
      FRTOS1_vTaskDelay(10/portTICK_RATE_MS); /* debounce */
      if (SW2_GetVal()==0) { /* still pressed */
        while(SW2_GetVal()==0) {
          /* wait until released */
          FRTOS1_vTaskDelay(10/portTICK_RATE_MS); /* debounce */
        }
        DisableScheduler(io);
        if (isPumpOn) { /* pump is on, toggle it */
          SetCooling(FALSE, io); /* turn cooling off */
          mySchedule.isSchedulerOn = TRUE; /* turn scheduler on again */
        } else {
          SetCooling(TRUE, io); /* turn cooling on */
        }
      }
    }
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  } /* for */
}

static portTASK_FUNCTION(Hoval, pvParameters) {
  /* LED status:
   * Green: 1 Hz Heartbeat
   * Red: On: pump is on
   *      1 Hz: Scheduler enabled
   *      Off: no scheduler
   */
  CLS1_ConstStdIOType *io = CLS1_GetStdio();
  bool isEnabled = SW1_GetVal()==0; /* initial SW1 status */
  uint16_t secondsOn; /* number of seconds turned on */
  
  (void)pvParameters; /* parameter not used */
  if (GetRTCData(&mySchedule)!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"*** Failed getting RTC data\r\n", io->stdErr);
    for(;;); /* cannot operate like this! */
  }
  isPumpOn = FALSE;
  for(;;) {
    /* check mode switch: turns scheduler on/off */
    if (!isEnabled && SW1_GetVal()==0) {
      Log((unsigned char*)"Switch changed to ON position", io);
    } else if (isEnabled && SW1_GetVal()!=0) {
      Log((unsigned char*)"Switch changed to OFF position", io);
    }
    isEnabled = SW1_GetVal()==0; /* Switch in ON position */

    /* check schedule */
    if (isEnabled && mySchedule.isSchedulerOn) {
      if (!isPumpOn) { /* pump is off, check if we need to turn it on */
        if (isInRange(&mySchedule.on, &mySchedule.off)) {
          SetCooling(TRUE, io);
        }
      } else { /* pump is on, check if we have to turn it off */
        if (!isInRange(&mySchedule.on, &mySchedule.off)) {
          SetCooling(FALSE, io);
        }
      }
    }
    if (isPumpOn) { /* check if we need to toggle the button on the Hoval to avoid timeout */
      secondsOn++;
      if (secondsOn>HOVAL_CYCLE_TIME_SECONDS) {
        Log((unsigned char*)"Toggle manual button to avoid timeout...", io);
        SetCooling(FALSE, io);
        FRTOS1_vTaskDelay(5000/portTICK_RATE_MS); /* wait some time until re-enable manual mode again */
        SetCooling(TRUE, io);
        secondsOn = 0; /* restart counter */
      }
    }
    /* show status LED */
    SD_GreenLed_Neg(); /* 1 Hz heartbeat LED */
    if (isPumpOn) { /* steady red LED if pump is on for cooling */
      SD_RedLed_On();
      LEDR_On();
    } else if (isEnabled && mySchedule.isSchedulerOn) { /* blinking red LED for enabled scheduler */
      SD_RedLed_Put(SD_GreenLed_Get()); /* blink red led in sync with green one */
      LEDR_Put(SD_GreenLed_Get());
    } else {
      SD_RedLed_Off(); /* no red LED if not cooling and no schedule */
      LEDR_Off();
    }
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  }
}

static byte PrintStatus(CLS1_ConstStdIOType *io) {
  uint8_t buf[48];
  
  CLS1_SendStatusStr((unsigned char*)"Hoval", (const unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  Scheduler", mySchedule.isSchedulerOn ? (const unsigned char*)"on\r\n":(const unsigned char*)"off\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  Switch", SW1_GetVal()==0 ? (const unsigned char*)"ON\r\n":(const unsigned char*)"OFF\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  Hoval", isHovalManualMode ? (const unsigned char*)"manual mode on\r\n":(const unsigned char*)"manual mode off\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  Pump", isPumpOn ? (const unsigned char*)"on\r\n":(const unsigned char*)"off\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  Relay 1", isRelay1on ? (const unsigned char*)"on (button)\r\n":(const unsigned char*)"off (pump)\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  Relay 2", isRelay2on ? (const unsigned char*)"on (pump)\r\n":(const unsigned char*)"off (manual mode)\r\n", io->stdOut);

  buf[0]='\0';
#if PL_HAS_DATE_SUPPORT
  StrCatDate(buf, sizeof(buf), mySchedule.on.date.day, mySchedule.on.date.month, mySchedule.on.date.year);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)", ");
#endif
  StrCatTime(buf, sizeof(buf), mySchedule.on.time.hour, mySchedule.on.time.min, mySchedule.on.time.sec);
  UTIL1_chcat(buf, sizeof(buf), '-');
#if PL_HAS_DATE_SUPPORT
  StrCatDate(buf, sizeof(buf), mySchedule.off.date.day, mySchedule.off.date.month, mySchedule.off.date.year);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)", ");
#endif
  StrCatTime(buf, sizeof(buf), mySchedule.off.time.hour, mySchedule.off.time.min, mySchedule.off.time.sec);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  time on", (unsigned char*)buf, io->stdOut);
  return ERR_OK;
}

static uint8_t TimeOnCmd(const unsigned char *cmd, CLS1_ConstStdIOType *io) {
  uint8_t hour, minute, second, hSecond;
  const unsigned char *p;

  p = cmd;
  /* format is <starttime> <stoptime>, e.g. "22:05:00 2:00:00" to start at 22:05 until 2 am */
  if (UTIL1_ScanTime(&p, &hour, &minute, &second, &hSecond)!=ERR_OK) { /* format fine */
    CLS1_SendStr((unsigned char*)"*** Error while reading start time: ", io->stdErr);
    CLS1_SendStr(cmd, io->stdErr);
    CLS1_SendStr((unsigned char*)"\r\n", io->stdErr);
    return ERR_FAILED;
  }
  if (SetOnTime(hour, minute, second)!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"*** Failed to set start time!\r\n", io->stdErr);
  }
  if (UTIL1_ScanTime(&p, &hour, &minute, &second, &hSecond)!=ERR_OK) { /* format fine */
    CLS1_SendStr((unsigned char*)"*** Error while reading end time: ", io->stdErr);
    CLS1_SendStr(cmd, io->stdErr);
    CLS1_SendStr((unsigned char*)"\r\n", io->stdErr);
    return ERR_FAILED;
  }
  if (SetOffTime(hour, minute, second)!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"*** Failed to set end time!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  return ERR_OK;
}

#if PL_HAS_DATE_SUPPORT
static uint8_t DateCmd(const unsigned char *cmd, CLS1_ConstStdIOType *io) {
  uint8_t day, month;
  uint16_t year;
  const unsigned char *p;
  uint8_t res = ERR_OK;
  bool isOn;

  p = cmd;
  if (UTIL1_strncmp((char*)cmd, " on ", sizeof(" on ")-1)==0) {
    isOn = TRUE;
    p += sizeof(" on ")-1;
  } else if (UTIL1_strncmp((char*)cmd, " off ", sizeof(" off ")-1)==0) {
    isOn = FALSE;
    p += sizeof(" off ")-1;
  } else {
    CLS1_SendStr((unsigned char*)"*** 'on' or 'off' expected\r\n", io->stdErr);
    return ERR_FAILED; /* wrong format */
  }
  if (UTIL1_ScanDate(&p, &day, &month, &year)==ERR_OK) { /* format fine */
    if (isOn) {
      res = SetOnDate(day, month, year);
    } else {
      res = SetOffDate(day, month, year);
    }
    if (res != ERR_OK) {
      CLS1_SendStr((unsigned char*)"*** Failure setting schedule time\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else {
    CLS1_SendStr((unsigned char*)"*** Error while reading command: ", io->stdErr);
    CLS1_SendStr(cmd, io->stdErr);
    CLS1_SendStr((unsigned char*)"\r\n", io->stdErr);
    res = ERR_FAILED;
  }
  return res;
}
#endif

byte HOVAL_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "Hoval help")==0) {
    CLS1_SendHelpStr((unsigned char*)"Hoval", (const unsigned char*)"Group of Hoval commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  scheduler (on|off)", (const unsigned char*)"Turns time scheduler on or off\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  time <start> <end>", (const unsigned char*)"Sets the 'on' time, e.g. '21:00:00 21:30:00'\r\n", io->stdOut);
#if PL_HAS_DATE_SUPPORT
    CLS1_SendHelpStr((unsigned char*)"  date (on|off) <date>", (const unsigned char*)"Sets the on and off date\r\n", io->stdOut);
#endif
#if 0
    CLS1_SendHelpStr((unsigned char*)"  relay (1|2) (on|off)", (const unsigned char*)"Turn relay on or off\r\n", io->stdOut);
#endif
    CLS1_SendHelpStr((unsigned char*)"  pump (on|off)", (const unsigned char*)"Turn pump on or off\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  cooling (on|off)", (const unsigned char*)"Turns cooling on or off\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "Hoval status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "Hoval relay 1 on")==0) {
    DisableScheduler(io);
    Button_On(TRUE, io);
    *handled = TRUE;
    return ERR_OK;
#if 0
  } else if (UTIL1_strcmp((char*)cmd, "Hoval relay 1 off")==0) {
    DisableScheduler(io);
    Button_On(FALSE, io);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "Hoval relay 2 on")==0) {
    DisableScheduler(io);
    Pump_On(TRUE, io);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "Hoval relay 2 off")==0) {
    DisableScheduler(io);
    Button_On(FALSE, io);
    *handled = TRUE;
    return ERR_OK;
#endif
  } else if (UTIL1_strcmp((char*)cmd, "Hoval pump on")==0) {
    DisableScheduler(io);
    SetCooling(TRUE, io);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "Hoval pump off")==0) {
    DisableScheduler(io);
    SetCooling(FALSE, io);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "Hoval scheduler on")==0) {
    mySchedule.isSchedulerOn = TRUE;
    if (PutRTCData(&mySchedule)!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"*** Failure setting schedule data\r\n", io->stdErr);
      return ERR_FAILED;
    }
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "Hoval scheduler off")==0) {
    mySchedule.isSchedulerOn = FALSE;
    if (PutRTCData(&mySchedule)!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"*** Failure setting schedule data\r\n", io->stdErr);
      return ERR_FAILED;
    }
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "Hoval cooling on")==0) {
    DisableScheduler(io);
    SetCooling(TRUE, io);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "Hoval cooling off")==0) {
    SetCooling(FALSE, io);
    DisableScheduler(io);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strncmp((char*)cmd, "Hoval time", sizeof("Hoval time")-1)==0) {
    *handled = TRUE;
    return TimeOnCmd(cmd+sizeof("Hoval time")-1, io);
#if PL_HAS_DATE_SUPPORT
  } else if (UTIL1_strncmp((char*)cmd, "Hoval date", sizeof("Hoval date")-1)==0) {
    *handled = TRUE;
    return DateCmd(cmd+sizeof("Hoval date")-1, io);
#endif
  }
  return ERR_OK;
}

void HOVAL_Init(void) {
  if (FRTOS1_xTaskCreate(
        Hoval,  /* pointer to the task */
        (signed char *)"Hoval", /* task name for kernel awareness debugging */
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
        Button,  /* pointer to the task */
        (signed char *)"Button", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}

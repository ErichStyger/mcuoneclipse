/*
 * Copyright (c) 2019, 2020, Erich Styger
  *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "clock.h"
#if PL_CONFIG_USE_CLOCK
#include "McuWait.h"
#include "McuRTOS.h"
#if PL_CONFIG_HAS_BUTTONS
  #include "buttons.h"
  #include "McuButton.h"
#endif
#include "leds.h"
#if PL_CONFIG_USE_SHELL
  #include "McuShell.h"
  #include "Shell.h"
  #include "McuShellUart.h"
#endif
#include "McuTimeDate.h"
#if PL_CONFIG_USE_NVMC
  #if McuLib_CONFIG_CPU_IS_LPC  /* LPC845-BRK */
  #include "fsl_iap.h"
  #elif McuLib_CONFIG_CPU_IS_KINETIS /* K22FN512 */
  #include "fsl_flash.h"
  #endif
#endif
#if PL_CONFIG_USE_WDT
  #include "watchdog.h"
#endif
#if PL_CONFIG_USE_RTC
  #include "McuExtRTC.h"
#endif
#include "application.h"
#include "McuLog.h"
#include "flipdot.h"

static bool CLOCK_ClockIsOn = true;
static bool CLOCK_ClockIs24h = true; /* if showing time in 24h format (17:35) or 12h format (5:35) */

/* direct task notification messages: */
#define CLOCK_TASK_NOTIFY_PARK_ON             (1<<0) /* request to park the motors */
#define CLOCK_TASK_NOTIFY_PARK_OFF            (1<<1) /* request to un-park the motors */
#define CLOCK_TASK_NOTIFY_PARK_TOGGLE         (1<<2) /* request to toggle parking */
#define CLOCK_TASK_NOTIFY_CLOCK_ON            (1<<3) /* request to turn the clock on */
#define CLOCK_TASK_NOTIFY_CLOCK_OFF           (1<<4) /* request to turn the clock off */
#define CLOCK_TASK_NOTIFY_CLOCK_TOGGLE        (1<<5) /* request to toggle clock on/off */
#define CLOCK_TASK_NOTIFY_BUTTON_USR          (1<<6) /* request to toggle clock on/off */
#define CLOCK_TASK_NOTIFY_BUTTON_USR_LONG     (1<<7) /* request to toggle clock on/off */
#if PL_CONFIG_HAS_SWITCH_7WAY
#define CLOCK_TASK_NOTIFY_BUTTON_UP           (1<<8) /* up button */
#define CLOCK_TASK_NOTIFY_BUTTON_DOWN         (1<<9) /* down button */
#define CLOCK_TASK_NOTIFY_BUTTON_LEFT         (1<<10) /* left button */
#define CLOCK_TASK_NOTIFY_BUTTON_RIGHT        (1<<11) /* right button */
#define CLOCK_TASK_NOTIFY_BUTTON_MID          (1<<12) /* middle button */
#define CLOCK_TASK_NOTIFY_BUTTON_RST          (1<<13) /* reset button */
#define CLOCK_TASK_NOTIFY_BUTTON_SET          (1<<14) /* set button */
#define CLOCK_TASK_NOTIFY_ALL                ((1<<15)-1) /* all notification bits */
#else
#define CLOCK_TASK_NOTIFY_ALL                 ((1<<8)-1) /* all notification bits */
#endif

static TaskHandle_t clockTaskHndl;

bool CLOCK_GetClockIsOn(void) {
  return CLOCK_ClockIsOn;
}

static void CLOCK_ShowTimeDate(TIMEREC *time, DATEREC *date) {
  McuLog_info("Time: %02d:%02d, Date: %02d-%02d-%04d", time->Hour, time->Min, date->Day, date->Month, date->Year);
  FlipDot_ClearAllDots();
  if (CLOCK_ClockIs24h) {
    FlipDot_DrawTime3x5(1, 1, time->Hour, time->Min);
  } else {
    int hour = time->Hour%12;
    if (hour==0) {
      hour = 12;
    }
    FlipDot_DrawTime3x5(1, 1, hour, time->Min);
  }
  FlipDot_DrawDate3x5(0, 8, date->Day, date->Month, date->Year);
  FlipDot_SendDots();
}

#if PL_CONFIG_HAS_SWITCH_7WAY
static void GetTimeString(unsigned char *buf, size_t bufSize, TIMEREC *time, DATEREC *date) {
  buf[0] = '\0';
  McuTimeDate_AddDateString(buf, bufSize, date, (unsigned char*)McuTimeDate_CONFIG_DEFAULT_DATE_FORMAT_STR);
  McuUtility_chcat(buf, bufSize, ' ');
  McuTimeDate_AddTimeString(buf, bufSize, time, (unsigned char*)McuTimeDate_CONFIG_DEFAULT_TIME_FORMAT_STR);
}

static void CLOCK_ButtonMenu(uint32_t notification) {
  static int8_t currDigit = -1;
  TIMEREC time;
  DATEREC date;
  uint8_t buf[24];
  static uint32_t seconds;

  if (notification&CLOCK_TASK_NOTIFY_BUTTON_RST) {
    if (CLOCK_GetClockIsOn()) {
      CLOCK_ClockIsOn = false; /* disable clock */
    }
    McuTimeDate_GetTimeDate(&time, &date);
    CLOCK_ShowTimeDate(&time, &date);
    seconds = McuTimeDate_TimeDateToUnixSeconds(&time, &date, 0);
    currDigit = 3;
    GetTimeString(buf, sizeof(buf), &time, &date);
    McuLog_info("Start setting time: %s", buf);
  } else if (currDigit>=0 && notification&CLOCK_TASK_NOTIFY_BUTTON_UP) {
    switch(currDigit) {
      case 0: seconds += 10*60*60; break; /* 1x:xx (10x hour) */
      case 1: seconds += 60*60; break;    /* x1:xx (hour) */
      case 2: seconds += 10*60; break;    /* xx:1x (10x Minute) */
      case 3: seconds += 60; break;       /* xx:x1 (minute) */
      default: break;
    }
    McuTimeDate_UnixSecondsToTimeDate(seconds, 0, &time, &date);
    GetTimeString(buf, sizeof(buf), &time, &date);
    McuLog_info("Incremented: %s", buf);
    CLOCK_ShowTimeDate(&time, &date);
  } else if (currDigit>=0 && notification&CLOCK_TASK_NOTIFY_BUTTON_DOWN) {
    switch(currDigit) {
      case 0: seconds -= 10*60*60; break; /* 1x:xx (10x hour) */
      case 1: seconds -= 60*60; break;    /* x1:xx (hour) */
      case 2: seconds -= 10*60; break;    /* xx:1x (10x Minute) */
      case 3: seconds -= 60; break;       /* xx:x1 (minute) */
      default: break;
    }
    McuTimeDate_UnixSecondsToTimeDate(seconds, 0, &time, &date);
    GetTimeString(buf, sizeof(buf), &time, &date);
    McuLog_info("Decremented: %s", buf);
    CLOCK_ShowTimeDate(&time, &date);
  } else if (currDigit>=0 && notification&CLOCK_TASK_NOTIFY_BUTTON_LEFT) {
    currDigit--;
    currDigit %= 4;
    McuLog_info("Digit pos: %d", currDigit);
  } else if (currDigit>=0 && notification&CLOCK_TASK_NOTIFY_BUTTON_RIGHT) {
    currDigit++;
    currDigit %= 4;
    McuLog_info("Digit pos: %d", currDigit);
  } else if (currDigit>=0 && notification&CLOCK_TASK_NOTIFY_BUTTON_SET) { /* store it */
    McuTimeDate_UnixSecondsToTimeDate(seconds, 0, &time, &date);
    GetTimeString(buf, sizeof(buf), &time, &date);
    McuLog_info("Storing time: %s", buf);
    McuTimeDate_SetTimeDate(&time, &date);
    CLOCK_ClockIsOn = true; /* enable clock */
    currDigit = -1;
  }
}
#endif /* #if PL_CONFIG_HAS_SWITCH_7WAY */

#if PL_CONFIG_HAS_BUTTONS
void CLOCK_ButtonHandler(McuDbnc_EventKinds event, uint32_t buttons) {
  switch(event) {
    case MCUDBNC_EVENT_PRESSED:
      break;

    case MCUDBNC_EVENT_PRESSED_REPEAT:
      break;

    case MCUDBNC_EVENT_LONG_PRESSED:
      break;

    case MCUDBNC_EVENT_LONG_PRESSED_REPEAT:
      break;

    case MCUDBNC_EVENT_RELEASED:
      if (buttons&BTN_BIT_USER) {
        CLOCK_Notify(CLOCK_NOTIFY_BUTTON_PRESSED_USR);
      }
   #if PL_CONFIG_HAS_SWITCH_7WAY
      if (buttons&BTN_BIT_RST) {
        CLOCK_Notify(CLOCK_NOTIFY_BUTTON_PRESSED_RST);
      }
      if (buttons&BTN_BIT_UP) {
        CLOCK_Notify(CLOCK_NOTIFY_BUTTON_PRESSED_UP);
      }
      if (buttons&BTN_BIT_DOWN) {
        CLOCK_Notify(CLOCK_NOTIFY_BUTTON_PRESSED_DOWN);
      }
      if (buttons&BTN_BIT_LEFT) {
        CLOCK_Notify(CLOCK_NOTIFY_BUTTON_PRESSED_LEFT);
      }
      if (buttons&BTN_BIT_RIGHT) {
        CLOCK_Notify(CLOCK_NOTIFY_BUTTON_PRESSED_RIGHT);
      }
      if (buttons&BTN_BIT_MID) {
        CLOCK_Notify(CLOCK_NOTIFY_BUTTON_PRESSED_MID);
      }
      if (buttons&BTN_BIT_SET) {
        CLOCK_Notify(CLOCK_NOTIFY_BUTTON_PRESSED_SET);
      }
   #endif /* PL_CONFIG_HAS_SWITCH_7WAY */
      break;

    case MCUDBNC_EVENT_LONG_RELEASED:
      if (buttons&BTN_BIT_USER) {
        CLOCK_Notify(CLOCK_NOTIFY_BUTTON_PRESSED_USR_LONG);
      }
      break;

    default:
      break;
  }
}
#endif

void CLOCK_Notify(CLOCK_Notify_e msg) {
  switch(msg) {
    case CLOCK_NOTIFY_BUTTON_PRESSED_USR:
      (void)xTaskNotify(clockTaskHndl, CLOCK_TASK_NOTIFY_BUTTON_USR, eSetBits);
      break;
    case CLOCK_NOTIFY_BUTTON_PRESSED_USR_LONG:
      (void)xTaskNotify(clockTaskHndl, CLOCK_TASK_NOTIFY_BUTTON_USR_LONG, eSetBits);
      break;
#if PL_CONFIG_HAS_SWITCH_7WAY
    case CLOCK_NOTIFY_BUTTON_PRESSED_RST:
      (void)xTaskNotify(clockTaskHndl, CLOCK_TASK_NOTIFY_BUTTON_RST, eSetBits);
      break;
    case CLOCK_NOTIFY_BUTTON_PRESSED_UP:
      (void)xTaskNotify(clockTaskHndl, CLOCK_TASK_NOTIFY_BUTTON_UP, eSetBits);
      break;
    case CLOCK_NOTIFY_BUTTON_PRESSED_DOWN:
      (void)xTaskNotify(clockTaskHndl, CLOCK_TASK_NOTIFY_BUTTON_DOWN, eSetBits);
      break;
    case CLOCK_NOTIFY_BUTTON_PRESSED_LEFT:
      (void)xTaskNotify(clockTaskHndl, CLOCK_TASK_NOTIFY_BUTTON_LEFT, eSetBits);
      break;
    case CLOCK_NOTIFY_BUTTON_PRESSED_RIGHT:
      (void)xTaskNotify(clockTaskHndl, CLOCK_TASK_NOTIFY_BUTTON_RIGHT, eSetBits);
      break;
    case CLOCK_NOTIFY_BUTTON_PRESSED_MID:
      (void)xTaskNotify(clockTaskHndl, CLOCK_TASK_NOTIFY_BUTTON_MID, eSetBits);
      break;
    case CLOCK_NOTIFY_BUTTON_PRESSED_SET:
      (void)xTaskNotify(clockTaskHndl, CLOCK_TASK_NOTIFY_BUTTON_SET, eSetBits);
      break;
#endif
    default:
      break;
  }
}

void CLOCK_On(CLOCK_Mode_e mode) {
  switch(mode) {
    case CLOCK_MODE_ON:       (void)xTaskNotify(clockTaskHndl, CLOCK_TASK_NOTIFY_CLOCK_ON, eSetBits); break;
    case CLOCK_MODE_OFF:      (void)xTaskNotify(clockTaskHndl, CLOCK_TASK_NOTIFY_CLOCK_OFF, eSetBits); break;
    case CLOCK_MODE_TOGGLE:
      if (CLOCK_ClockIsOn) {
        (void)xTaskNotify(clockTaskHndl, CLOCK_TASK_NOTIFY_CLOCK_OFF, eSetBits);
      } else {
        (void)xTaskNotify(clockTaskHndl, CLOCK_TASK_NOTIFY_CLOCK_ON, eSetBits);
      }
      break;
    default: break;
  }
}

#if PL_CONFIG_USE_SHELL
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  McuShell_SendStatusStr((unsigned char*)"clock", (unsigned char*)"Clock settings\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  clock", CLOCK_GetClockIsOn()?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);

  McuShell_SendStatusStr((unsigned char*)"  24h", CLOCK_ClockIs24h?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);

#if PL_CONFIG_USE_NVMC
#if McuLib_CONFIG_CPU_IS_LPC  /* LPC845-BRK */
  uint32_t val;
  uint32_t id[4];

  res = IAP_ReadPartID(&val);
  if (res == kStatus_IAP_Success) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
    McuUtility_strcatNum32Hex(buf, sizeof(buf), val);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  PartID", buf, io->stdOut);

  res = IAP_ReadUniqueID(&id[0]);  /* \todo in McuArmTools now, could be removed */
  if (res == kStatus_IAP_Success) {
    buf[0] = '\0';
    for(int i=0; i<sizeof(id)/sizeof(id[0]); i++) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"0x");
      McuUtility_strcatNum32Hex(buf, sizeof(buf), id[i]);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" ");
    }
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  UID", buf, io->stdOut);

  res = IAP_ReadBootCodeVersion(&val);
  if (res == kStatus_IAP_Success) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"Version 0x");
    McuUtility_strcatNum32Hex(buf, sizeof(buf), val);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  BootCode", buf, io->stdOut);
  #endif
#endif
  return res;
}
#endif

#if PL_CONFIG_USE_SHELL
static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"clock", (unsigned char*)"Group of clock commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  on|off|toggle", (unsigned char*)"Enable or disable the clock\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  24h on|off", (unsigned char*)"Show time in 24h (17:35) or 12h (5:35) format\r\n", io->stdOut);
  return ERR_OK;
}
#endif

#if PL_CONFIG_USE_SHELL
uint8_t CLOCK_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "clock help")==0) {
    *handled = true;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "clock status")==0)) {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "clock on")==0) {
    *handled = true;
    CLOCK_On(CLOCK_MODE_ON);
  } else if (McuUtility_strcmp((char*)cmd, "clock off")==0) {
    *handled = true;
    CLOCK_On(CLOCK_MODE_OFF);
  } else if (McuUtility_strcmp((char*)cmd, "clock 24h on")==0) {
    *handled = true;
    CLOCK_ClockIs24h = true;
  } else if (McuUtility_strcmp((char*)cmd, "clock 24h off")==0) {
    *handled = true;
    CLOCK_ClockIs24h = false;
  } else if (McuUtility_strcmp((char*)cmd, "clock toggle")==0) {
    *handled = true;
    CLOCK_On(CLOCK_MODE_TOGGLE);
  }
  return ERR_OK;
}
#endif /* #if PL_CONFIG_USE_SHELL */

static void ClockTask(void *pv) {
  uint8_t res;
  int32_t prevClockUpdateTimestampSec = 0; /* time of previous clock update time stamp, seconds since 1972 */
  TIMEREC time;
  DATEREC date;
  TickType_t lastUpdateFromRTCtickCount; /* time stamp when last time the SW RTC has been update from HW RTC: it gets updated every hour */
  uint32_t ulNotificationValue;

  res = McuTimeDate_Init();
  if(res==ERR_OK) { /* initialize time from external RTC if configured with McuTimeDate_INIT_SOFTWARE_RTC_FROM_EXTERNAL_RTC */
    lastUpdateFromRTCtickCount = xTaskGetTickCount(); /* remember last time we updated the RTC */
  } else{
    McuLog_error("Failed initializing time from RTC!");
    lastUpdateFromRTCtickCount = 0; /* set it to zero: will retry in the main loop below */
  }
  McuLog_trace("Starting Clock Task");
#if PL_CONFIG_USE_WDT
  WDT_SetTaskHandle(WDT_REPORT_ID_TASK_CLOCK, xTaskGetCurrentTaskHandle());
#endif
  vTaskDelay(pdMS_TO_TICKS(2000)); /* give external RTC and hardware time to power up */
#if PL_CONFIG_USE_WDT
  WDT_Report(WDT_REPORT_ID_TASK_CLOCK, 2000);
#endif

  vTaskDelay(pdMS_TO_TICKS(10000)); /* wait some time to give flipdot hardware to run through self-test */
#if PL_CONFIG_USE_RTC
  /* set new random seed based temperature */
  float temperature;

  if (McuExtRTC_GetTemperature(&temperature)!=ERR_OK) {
    McuLog_error("failed getting RTC temperature");
  } else {
    uint32_t seed;

    seed = (((int)temperature)<<16)+(int)(temperature)*64;
    McuUtility_randomSetSeed(seed);
  }
#endif
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(200));
  #if PL_CONFIG_USE_WDT
    WDT_Report(WDT_REPORT_ID_TASK_CLOCK, 200);
  #endif
    /* check task notifications */
    res = xTaskNotifyWait(
       0, /* do not clear anything on enter */
       CLOCK_TASK_NOTIFY_ALL, /* clear all bits on exit */
       &ulNotificationValue,
       0);
    if (res==pdTRUE) { /* notification received */
      if (ulNotificationValue&CLOCK_TASK_NOTIFY_BUTTON_USR) {
        McuLog_info("Notification: button pressed");
        SHELL_ParseCommand((unsigned char*)"clock toggle", McuShell_GetStdio(), true);
      }
      if (ulNotificationValue&CLOCK_TASK_NOTIFY_BUTTON_USR_LONG) {
        McuLog_info("Notification: button pressed long");
        SHELL_ParseCommand((unsigned char*)"intermezzo toggle", McuShell_GetStdio(), true);
      }

      if (ulNotificationValue&CLOCK_TASK_NOTIFY_CLOCK_ON) {
        McuLog_info("Clock on");
        CLOCK_ClockIsOn = true; /* enable clock */
        prevClockUpdateTimestampSec = 0; /* to make sure it will update */
      }
      if (ulNotificationValue&CLOCK_TASK_NOTIFY_CLOCK_OFF) {
        McuLog_info("Clock off");
        CLOCK_ClockIsOn = false; /* disable clock */
        prevClockUpdateTimestampSec = 0;
      }
      if (ulNotificationValue&CLOCK_TASK_NOTIFY_CLOCK_TOGGLE) {
        McuLog_info("Clock toggle");
        CLOCK_ClockIsOn = !CLOCK_ClockIsOn; /* toggle clock */
        prevClockUpdateTimestampSec = 0; /* to make sure it will update */
      }
  #if PL_CONFIG_HAS_SWITCH_7WAY
      CLOCK_ButtonMenu(ulNotificationValue);
  #endif /* PL_CONFIG_HAS_SWITCH_7WAY */
    } /* if notification received */
  #if PL_CONFIG_USE_RTC
    /* ----------------------------------------------------------------------------------*/
    /* Because the SW RTC might run off, we update the SW RTC from the HW RTC every hour */
    TickType_t tickCount = xTaskGetTickCount();
    /* update SW RTC from external RTC */
    if ((tickCount-lastUpdateFromRTCtickCount) > pdMS_TO_TICKS(60*60*1000)) { /* every hour */
      McuLog_info("Updating RTC from external RTC");
      res = McuTimeDate_SyncWithExternalRTC(); /* update SW RTC with external HW RTC to avoid too much clock drift */
      if (res!=ERR_OK) {
        McuLog_error("Updating RTC from external RTC");
      }
      lastUpdateFromRTCtickCount = tickCount;
    }
    /* ----------------------------------------------------------------------------------*/
    /* Clock */
    /* ----------------------------------------------------------------------------------*/
    if (CLOCK_ClockIsOn) { /* show time */
      res = McuTimeDate_GetTimeDate(&time, &date);
    #if PL_CONFIG_USE_NEO_PIXEL_HW
      ShowSeconds(&time);
    #endif
      if (res==ERR_OK && (McuTimeDate_TimeDateToUnixSeconds(&time, &date, 0) >= prevClockUpdateTimestampSec+60)) {
        FlipDot_Test();
        vTaskDelay(pdMS_TO_TICKS(1000));
        CLOCK_ShowTimeDate(&time, &date);
        prevClockUpdateTimestampSec = McuTimeDate_TimeDateToUnixSeconds(&time, &date, 0);
      #if PL_CONFIG_USE_INTERMEZZO /* show intermezzo? */
        lastClockUpdateTickCount = xTaskGetTickCount();
        intermezzoShown = false;
      #endif
        McuLog_info("finished showing clock");
      } /* if */
    } /* if clock is on */
  #endif /* PL_CONFIG_USE_RTC */
  } /* for */
}

void CLOCK_Init(void) {
  if (xTaskCreate(
      ClockTask,  /* pointer to the task */
      "Clock", /* task name for kernel awareness debugging */
      2500/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+1,  /* initial priority */
      &clockTaskHndl /* optional task handle to create */
    ) != pdPASS) {
     McuLog_fatal("failed creating Clock task");
     for(;;){} /* error! probably out of memory */
  }
}

#endif /* PL_CONFIG_USE_CLOCK */

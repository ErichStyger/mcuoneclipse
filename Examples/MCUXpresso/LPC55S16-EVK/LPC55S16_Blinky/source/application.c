/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "board.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuLED.h"
#include "McuRTOS.h"
#include "McuShellUart.h"
#include "McuShell.h"
#include "McuRTT.h"
#include "McuSystemView.h"
#include "McuLog.h"
#include "McuTimeDate.h"
#include "McuDebounce.h"
#include "leds.h"
#include "buttons.h"
#include "Shell.h"
#include "disk.h"

void __assertion_failed(char *_Expr) {
  for(;;) {
    __asm("nop");
  }
}

static SemaphoreHandle_t mutex;

static void AppOnDebounceEvent(McuDbnc_EventKinds event, uint32_t buttons) {
  switch(event) {
    case MCUDBNC_EVENT_PRESSED:
      McuLog_info("Dbnc pressed: %d", buttons);
      break;

    case MCUDBNC_EVENT_PRESSED_REPEAT:
      McuLog_info("Dbnc repeat: %d", buttons);
      break;

    case MCUDBNC_EVENT_LONG_PRESSED:
      McuLog_info("Dbnc long pressed: %d", buttons);
      break;

    case MCUDBNC_EVENT_LONG_PRESSED_REPEAT:
      McuLog_info("Dbnc pressed repeat: %d", buttons);
      break;

    case MCUDBNC_EVENT_RELEASED:
      McuLog_info("Dbnc released: %d", buttons);
      break;

    default:
    case MCUDBNC_EVENT_END:
      McuLog_info("Dbnc end: %d", buttons);
      break;
  }
}

static void AppTask(void *pv) {
#if PL_CONFIG_USE_SD_CARD
  bool sdDiskPresent = false;
  bool present;
#endif

  McuLog_info("App Task started.");
  BTN_RegisterAppCallback(AppOnDebounceEvent);
  for(;;) {
#if PL_CONFIG_USE_SD_CARD
    present = DISK_IsInserted((unsigned char*)DISK_DRIVE_SD_CARD);
    if (!sdDiskPresent && present) {
      DISK_SendEvent(DISK_EVENT_SD_CARD_INSERTED);
      sdDiskPresent = true;
    } else if (sdDiskPresent && !present) {
      DISK_SendEvent(DISK_EVENT_SD_CARD_REMOVED);
      sdDiskPresent = false;
    }
#endif
    if (BTN_IsPressed(BTN_UP)) {
      McuLog_info("User Up pressed.");
      LEDS_Neg(LEDS_BLUE);
    }
#if 1
    BTN_PollDebounce(); /* check and debounce */
#else /* simply button polling */
    if (BTN_IsPressed(BTN_USER)) {
      McuLog_info("User Button pressed.");
      LEDS_Neg(LEDS_BLUE);
    }
    if (BTN_IsPressed(BTN_WAKEUP)) {
      McuLog_info("Wakeup Button pressed.");
      LEDS_Neg(LEDS_GREEN);
    }
#endif
    LEDS_Neg(LEDS_RED);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static TimerHandle_t timerHndl;
#define TIMER_PERIOD_MS    McuTimeDate_CONFIG_TICK_TIME_MS

static void vTimerCallback(TimerHandle_t pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
  McuTimeDate_AddTick();
}

#if PL_CONFIG_USE_SWO
/*!
 * \brief Initialize the SWO trace port for debug message printing
 * \param portBits Port bit mask to be configured
 * \param cpuCoreFreqHz CPU core clock frequency in Hz
 */
void SWO_Init(uint32_t portBits, uint32_t cpuCoreFreqHz) {
  uint32_t SWOSpeed = 64000; /* default 64k baud rate */
  uint32_t SWOPrescaler = (cpuCoreFreqHz / SWOSpeed) - 1; /* SWOSpeed in Hz, note that cpuCoreFreqHz is expected to be match the CPU core clock */

  /*!< Switch TRACE to TRACE_DIV */
  CLOCK_AttachClk(kTRACE_DIV_to_TRACE);

  CoreDebug->DEMCR = CoreDebug_DEMCR_TRCENA_Msk; /* enable trace in core debug */
  *((volatile unsigned *)(ITM_BASE + 0x400F0)) = 0x00000002; /* "Selected PIN Protocol Register": Select which protocol to use for trace output (2: SWO NRZ, 1: SWO Manchester encoding) */
  *((volatile unsigned *)(ITM_BASE + 0x40010)) = SWOPrescaler; /* "Async Clock Prescaler Register". Scale the baud rate of the asynchronous output */
  *((volatile unsigned *)(ITM_BASE + 0x00FB0)) = 0xC5ACCE55; /* ITM Lock Access Register, C5ACCE55 enables more write access to Control Register 0xE00 :: 0xFFC */
  ITM->TCR = ITM_TCR_TRACEBUSID_Msk | ITM_TCR_SWOENA_Msk | ITM_TCR_SYNCENA_Msk | ITM_TCR_ITMENA_Msk; /* ITM Trace Control Register */
  ITM->TPR = ITM_TPR_PRIVMASK_Msk; /* ITM Trace Privilege Register */
  ITM->TER = portBits; /* ITM Trace Enable Register. Enabled tracing on stimulus ports. One bit per stimulus port. */
  *((volatile unsigned *)(ITM_BASE + 0x01000)) = 0x400003FE; /* DWT_CTRL */
  *((volatile unsigned *)(ITM_BASE + 0x40304)) = 0x00000100; /* Formatter and Flush Control Register */
}
#endif /* PL_CONFIG_USE_SWO */

#if PL_CONFIG_USE_SWO
/*!
 * \brief Sends a character over the SWO channel
 * \param c Character to be sent
 * \param portNo SWO channel number, value in the range of 0 to 31
 */
void SWO_PrintChar(char c, uint8_t portNo) {
  volatile int timeout;

  /* Check if Trace Control Register (ITM->TCR at 0xE0000E80) is set */
  if ((ITM->TCR&ITM_TCR_ITMENA_Msk) == 0) { /* check Trace Control Register if ITM trace is enabled*/
    return; /* not enabled? */
  }
  /* Check if the requested channel stimulus port (ITM->TER at 0xE0000E00) is enabled */
  if ((ITM->TER & (1ul<<portNo))==0) { /* check Trace Enable Register if requested port is enabled */
    return; /* requested port not enabled? */
  }
  timeout = 5000; /* arbitrary timeout value */
  while (ITM->PORT[0].u32 == 0) {
    /* Wait until STIMx is ready, then send data */
    timeout--;
    if (timeout==0) {
      return; /* not able to send */
    }
  }
  ITM->PORT[0].u8 = c;
}
#endif /* PL_CONFIG_USE_SWO */

#if PL_CONFIG_USE_SWO
/*!
 * \brief Sends a string over SWO to the host
 * \param s String to send
 * \param portNumber Port number, 0-31, use 0 for normal debug strings
 */
void SWO_PrintString(const char *s, uint8_t portNumber) {
  while (*s!='\0') {
    SWO_PrintChar(*s++, portNumber);
  }
}
#endif /* PL_CONFIG_USE_SWO */


void APP_Run(void) {
  PL_Init(); /* init modules */
#if PL_CONFIG_USE_SWO
  SWO_Init(0, SystemCoreClock); /* if initialization is not done by the debugger, need to do it manually here */
#endif

  for(int i=0;i<2;i++) {
  //for(;;) {
#if PL_CONFIG_USE_SWO
    SWO_PrintString("hello world using ITM console.\n", 0);
#endif
    LEDS_On(LEDS_RED);
    McuWait_Waitms(100);
    LEDS_Off(LEDS_RED);
    McuWait_Waitms(100);
    LEDS_On(LEDS_GREEN);
    McuWait_Waitms(100);
    LEDS_Off(LEDS_GREEN);
    McuWait_Waitms(100);
    LEDS_On(LEDS_BLUE);
    McuWait_Waitms(100);
    LEDS_Off(LEDS_BLUE);
    McuWait_Waitms(100);
    if (BTN_IsPressed(BTN_USER)) {
      LEDS_On(LEDS_RED);
      McuWait_Waitms(100);
      LEDS_Off(LEDS_RED);
    }
  } /* for */
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      700/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  timerHndl = xTimerCreate("timer0", pdMS_TO_TICKS(TIMER_PERIOD_MS), pdTRUE, (void *)0, vTimerCallback);
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) {
    for(;;); /* failure! */
  }
  mutex = xSemaphoreCreateMutex();
  if (mutex!=NULL) {
    vQueueAddToRegistry(mutex, "Mutex");
  }
  vTaskStartScheduler();
  for(;;) { /* should not get here */ }
}

/**
 * \file
 * \brief Application module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the main application.
 */
#include "Platform.h"
#include "Application.h"
#include "WAIT1.h"
#if PL_HAS_LED
  #include "LED.h"
#endif
#if PL_HAS_SHELL
  #include "Shell.h"
  #include "CLS1.h"
#endif
#if PL_HAS_KEYBOARD
  #include "Keys.h"
#endif
#if PL_HAS_MEALY
  #include "Mealy.h"
#endif
#if PL_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_HAS_TRIGGER
  #include "Trigger.h"
#endif
#if PL_HAS_SOUNDER
  #include "Sounder.h"
#endif
#if PL_HAS_RTOS
  #include "RTOS.h"
#endif
#if PL_HAS_MOTOR
  #include "Motor.h"
#endif
#if PL_HAS_MOTOR_PID
  #include "PID.h"
#endif
#if PL_HAS_RADIO
  #include "Radio.h"
#endif
#if PL_HAS_CONTEST
  #include "Quiz.h"
#endif

#if PL_HAS_EVENTS
void APP_HandleEvent(EVNT_Handle event) {
  /*! \todo Need to handle your events here */
#if PL_HAS_MOTOR_PID
  char buf[16];
#endif
  #define KEY_PRESS_BEEP_MS 100 /* beep time for key press */

  switch(event) {
    case EVNT_INIT:
#if PL_HAS_SOUNDER
      SND_Beep(KEY_PRESS_BEEP_MS, 200);
#endif
#if PL_HAS_LED
      LED1_On(); LED2_On(); LED3_On(); LED4_On();
      WAIT1_WaitOSms(500);
      LED1_Off(); LED2_Off(); LED3_Off(); LED4_Off();
#endif
      break;
    case EVNT_SW1_PRESSED:
#if PL_HAS_SOUNDER
      SND_Beep(KEY_PRESS_BEEP_MS, 300);
#endif
      SHELL_SendMessage("SW1 pressed!\r\n");
#if PL_HAS_MOTOR_PID
      PID_SetPoint(PID_GetPoint()+1000);
      UTIL1_strcpy(buf, sizeof(buf), "set: ");
      UTIL1_strcatNum32s(buf, sizeof(buf), PID_GetPoint());
      UTIL1_strcat(buf, sizeof(buf), "\r\n");
      SHELL_SendMessage(buf);
#elif PL_HAS_MOTOR_SIGNALS
      MOT_ChangeSpeedPercent(5);
#endif
#if PL_HAS_CONTEST
      RADIO_SendString("Reply with xxx and Name!");
      /* expected: xxx Hans Muster */
#endif
      break;
    case EVNT_SW2_PRESSED:
#if PL_HAS_SOUNDER
      SND_Beep(KEY_PRESS_BEEP_MS, 400);
#endif
      SHELL_SendMessage("SW2 pressed!\r\n");
#if PL_HAS_MOTOR_PID
      PID_SetPoint(PID_GetPoint()-1000);
      UTIL1_strcpy(buf, sizeof(buf), "set: ");
      UTIL1_strcatNum32s(buf, sizeof(buf), PID_GetPoint());
      UTIL1_strcat(buf, sizeof(buf), "\r\n");
      SHELL_SendMessage(buf);
#elif PL_HAS_MOTOR_SIGNALS
      MOT_ChangeSpeedPercent(-5);
#endif
      break;
    case EVNT_SW3_PRESSED:
#if PL_HAS_SOUNDER
      SND_Beep(KEY_PRESS_BEEP_MS, 500);
#endif
      SHELL_SendMessage("SW3 pressed!\r\n");
      break;
    case EVNT_SW4_PRESSED:
#if PL_HAS_SOUNDER
      SND_Beep(KEY_PRESS_BEEP_MS, 600);
#endif
      SHELL_SendMessage("SW4 pressed!\r\n");
      break;
    case EVNT_SW1_LPRESSED:
#if PL_HAS_SOUNDER
      SND_Beep(KEY_PRESS_BEEP_MS, 300);
#endif
      SHELL_SendMessage("SW1 long pressed!\r\n");
#if PL_HAS_MOTOR_PID
      PID_SetPoint(PID_GetPoint()+5000);
      UTIL1_strcpy(buf, sizeof(buf), "set: ");
      UTIL1_strcatNum32s(buf, sizeof(buf), PID_GetPoint());
      UTIL1_strcat(buf, sizeof(buf), "\r\n");
      CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
#elif PL_HAS_MOTOR_SIGNALS
      MOT_ChangeSpeedPercent(10);
#endif
      break;
    case EVNT_SW2_LPRESSED:
#if PL_HAS_SOUNDER
      SND_Beep(KEY_PRESS_BEEP_MS, 400);
#endif
      SHELL_SendMessage("SW2 long pressed!\r\n");
#if PL_HAS_MOTOR_PID
      PID_SetPoint(PID_GetPoint()-5000);
      UTIL1_strcpy(buf, sizeof(buf), "set: ");
      UTIL1_strcatNum32s(buf, sizeof(buf), PID_GetPoint());
      UTIL1_strcat(buf, sizeof(buf), "\r\n");
      SHELL_SendMessage(buf);
#elif PL_HAS_MOTOR_SIGNALS
      MOT_ChangeSpeedPercent(-10);
#endif
      break;
    case EVNT_SW3_LPRESSED:
#if PL_HAS_SOUNDER
      SND_Beep(KEY_PRESS_BEEP_MS, 500);
#endif
      SHELL_SendMessage("SW3 long pressed!\r\n");
      break;
    case EVNT_SW4_LPRESSED:
#if PL_HAS_SOUNDER
      SND_Beep(KEY_PRESS_BEEP_MS, 600);
#endif
      SHELL_SendMessage("SW4 long pressed!\r\n");
      break;
    case EVNT_SW1_RELEASED:
      SHELL_SendMessage("SW1 released!\r\n");
      break;
    case EVNT_SW2_RELEASED:
      SHELL_SendMessage("SW2 released!\r\n");
      break;
    case EVNT_SW3_RELEASED:
      SHELL_SendMessage("SW3 released!\r\n");
      break;
    case EVNT_SW4_RELEASED:
      SHELL_SendMessage("SW4 released!\r\n");
      break;
#if PL_HAS_LED_HEARTBEAT
    case EVNT_LED_HEARTBEAT:
      LED1_Neg();
      break;
#endif
    case EVNT_SW12_LPRESSED:
      SHELL_SendMessage("SW1+2 long pressed!\r\n");
      break;
    case EVNT_SW23_LPRESSED:
      SHELL_SendMessage("SW2+3 long pressed!\r\n");
      break;
    case EVNT_SW34_LPRESSED:
      SHELL_SendMessage("SW3+4 long pressed!\r\n");
      break;
#if PL_HAS_RADIO
    default:
      RADIO_AppHandleEvent(event); /* call radio event handler */
#endif
  } /* switch */
}
#endif /* PL_HAS_EVENTS */

#if PL_HAS_TRIGGER
static void LED_HeartBeat(void *p) {
  (void)p; /* avoid compiler warning */
  LED2_Neg();
  (void)TRG_SetTrigger(TRG_LED_BLINK, 1000/TRG_TICKS_MS, LED_HeartBeat, 0);
}
#endif

#if 0 && PL_HAS_LED && PL_HAS_TRIGGER
static void LED_Blink(void *p) {
  if (*((uint8_t*)p)==0) {
    LED1_Neg();
    (*(uint8_t*)p)++;
  } else if (*((uint8_t*)p)==1) {
    LED2_Neg();
    (*(uint8_t*)p)=0;
  }
  (void)TRG_SetTrigger(TRG_LED_BLINK, 1000/TRG_TICKS_MS, LED_Blink, p);
}
#endif

static void APP_Run(void) {
  /* \todo Do whatever you need to do... */
#if PL_HAS_TRIGGER
  (void)TRG_SetTrigger(TRG_LED_BLINK, 500/TRG_TICKS_MS, LED_HeartBeat, 0);
#endif
#if PL_HAS_RTOS
  RTOS_Run();
#else
#if PL_USE_USB_SCI
  //SHELL_WaitForCDCenumeration(); /* not doing this, otherwise it will block */
#endif
#if PL_HAS_SHELL && !PL_USE_USB_SCI
  SHELL_ParseLine(CLS1_CMD_HELP); /* print help and prints as well the prompt */
#endif
  for(;;) {
    //LED1_Neg();
    //WAIT1_Waitms(50);
  #if PL_POLL_KEYS || (PL_HAS_EVENTS && !PL_HAS_KBI && !PL_HAS_DEBOUNCE) 
    /* poll keys if we do not have interrupts, or as long we have not implemented debouncing */
    KEY_Scan();
  #endif
  #if PL_HAS_MEALY
    MEALY_Run();
  #endif
  #if PL_HAS_SHELL    
    SHELL_ReadAndParseLine();
  #endif
  #if PL_HAS_EVENTS
    EVNT_HandleEvent(APP_HandleEvent);
  #endif
  }
#endif
}

/*! \brief Application initialization routine. It calls as well all the used platform drivers.  */ 
void APP_Init(void) {
  PL_Init(); /* initialize hardware */
  APP_Run(); /* run the application */
}

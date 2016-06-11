/**
 * \file
 * \brief Main Application Module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module is the main application module. 
 * From here the application runs and performs all tasks.
 */
#include "Platform.h"
#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "timers.h"
#include "TMOUT1.h"
#include "UTIL1.h"
#if PL_HAS_RADIO
  #include "RNet_App.h"
#endif
#if PL_HAS_KEYS
  #include "KEY1.h"
#endif
#if PL_HAS_ACCELEROMETER
  #include "FX1.h"
#endif
#if PL_HAS_RTOS_TRACE
  #include "RTOSTRC1.h"
#endif
#if PL_HAS_MINI_INI
  #include "MINI1.h"
#endif
#if PL_HAS_SD_CARD
  #include "TmDt1.h"
#endif
#if PL_HAS_FLOPPY
  #include "Floppy.h"
#endif
#if PL_HAS_MIDI
  #include "MidiMusic.h"
#endif

static xTimerHandle timerHndl;
#define TIMER_PERIOD_MS TMOUT1_TICK_PERIOD_MS

#if PL_HAS_KEYS
void APP_OnKeyPressed(uint8_t keys) {
  if (keys&1) {
    CLS1_SendStr((uint8_t*)"SW3 pressed!\r\n", CLS1_GetStdio()->stdOut);
  } else if (keys&2) {
    CLS1_SendStr((uint8_t*)"SW2 pressed!\r\n", CLS1_GetStdio()->stdOut);
  }
}

void APP_OnKeyReleased(uint8_t keys) {
  if (keys&1) {
    CLS1_SendStr((uint8_t*)"SW3 released!\r\n", CLS1_GetStdio()->stdOut);
  } else if (keys&2) {
    CLS1_SendStr((uint8_t*)"SW2 released!\r\n", CLS1_GetStdio()->stdOut);
  }
}

void APP_OnKeyReleasedLong(uint8_t keys) {
  if (keys&1) {
    CLS1_SendStr((uint8_t*)"SW3 long released!\r\n", CLS1_GetStdio()->stdOut);
  } else if (keys&2) {
    CLS1_SendStr((uint8_t*)"SW2 long released!\r\n", CLS1_GetStdio()->stdOut);
  }
}
#endif /* PL_HAS_KEYS */

static void vTimerCallback(xTimerHandle pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
  TMOUT1_AddTick();
  TRG1_AddTick();
#if PL_HAS_SD_CARD
  TmDt1_AddTick();
#endif
}

#if PL_HAS_DEBUG_PRINT
void APP_DebugPrint(unsigned char *str) {
  CLS1_SendStr(str, CLS1_GetStdio()->stdOut);
}
#endif

#if PL_HAS_MINI_INI
#define sizearray(a)  (sizeof(a) / sizeof((a)[0]))
static const char inifile[] = "test.ini";
/* content of inifile:
[First]
String=noot # trailing commment
Val=1

[Second]
Val = 2
#comment=3
String = mies
 */
static const char inifile2[] = "testpl.ini"; /* must be 8.3 format */
/* content of inifile2:
String=noot # trailing commment
#comment=3
Val=1
 */

int Callback(const char *section, const char *key, const char *value, const void *userdata)
{
  (void)userdata; /* this parameter is not used in this example */
  SHELL_SendString((unsigned char*)"    [");
  SHELL_SendString((unsigned char*)section);
  SHELL_SendString((unsigned char*)"]\t");
  SHELL_SendString((unsigned char*)key);
  SHELL_SendString((unsigned char*)"=");
  SHELL_SendString((unsigned char*)value);
  SHELL_SendString((unsigned char*)"\r\n");
  return 1;
}

void Check(bool ok) {
  if (!ok) {
    SHELL_SendString((unsigned char*)"MinINI ERR: Failed!\r\n");
  }
}

int TestMiniIni(void) {
  char str[100];
  long n;
  int s, k;
  char section[50];

  /* string reading */
  n = ini_gets("first", "string", "dummy", str, sizearray(str), inifile);
  Check(n==4 && UTIL1_strcmp(str,"noot")==0);
  n = ini_gets("second", "string", "dummy", str, sizearray(str), inifile);
  Check(n==4 && UTIL1_strcmp(str,"mies")==0);
  n = ini_gets("first", "undefined", "dummy", str, sizearray(str), inifile);
  Check(n==5 && UTIL1_strcmp(str,"dummy")==0);
  /* ----- */
  n = ini_gets("", "string", "dummy", str, sizearray(str), inifile2);
  Check(n==4 && UTIL1_strcmp(str,"noot")==0);
  n = ini_gets(NULL, "string", "dummy", str, sizearray(str), inifile2);
  Check(n==4 && UTIL1_strcmp(str,"noot")==0);
  /* ----- */
  SHELL_SendString((unsigned char*)"1. String reading tests passed\n");

  /* value reading */
  n = ini_getl("first", "val", -1, inifile);
  Check(n==1);
  n = ini_getl("second", "val", -1, inifile);
  Check(n==2);
  n = ini_getl("first", "undefined", -1, inifile);
  Check(n==-1);
  /* ----- */
  n = ini_getl(NULL, "val", -1, inifile2);
  Check(n==1);
  /* ----- */
  SHELL_SendString((unsigned char*)"2. Value reading tests passed\n");

  /* string writing */
  n = ini_puts("first", "alt", "flagged as \"correct\"", inifile);
  Check(n==1);
  n = ini_gets("first", "alt", "dummy", str, sizearray(str), inifile);
  Check(n==20 && UTIL1_strcmp(str,"flagged as \"correct\"")==0);
  /* ----- */
  n = ini_puts("second", "alt", "correct", inifile);
  Check(n==1);
  n = ini_gets("second", "alt", "dummy", str, sizearray(str), inifile);
  Check(n==7 && UTIL1_strcmp(str,"correct")==0);
  /* ----- */
  n = ini_puts("third", "test", "correct", inifile);
  Check(n==1);
  n = ini_gets("third", "test", "dummy", str, sizearray(str), inifile);
  Check(n==7 && UTIL1_strcmp(str,"correct")==0);
  /* ----- */
  n = ini_puts("second", "alt", "overwrite", inifile);
  Check(n==1);
  n = ini_gets("second", "alt", "dummy", str, sizearray(str), inifile);
  Check(n==9 && UTIL1_strcmp(str,"overwrite")==0);
  /* ----- */
  n = ini_puts(NULL, "alt", "correct", inifile2);
  Check(n==1);
  n = ini_gets(NULL, "alt", "dummy", str, sizearray(str), inifile2);
  Check(n==7 && UTIL1_strcmp(str,"correct")==0);
  /* ----- */
  SHELL_SendString((unsigned char*)"3. String writing tests passed\n");

  /* section/key enumeration */
  SHELL_SendString((unsigned char*)"4. Section/key enumeration, file contents follows\n");
  for (s = 0; ini_getsection(s, section, sizearray(section), inifile) > 0; s++) {
    SHELL_SendString((unsigned char*)"    [");
    SHELL_SendString((unsigned char*)section);
    SHELL_SendString((unsigned char*)"]\r\n");
    for (k = 0; ini_getkey(section, k, str, sizearray(str), inifile) > 0; k++) {
      SHELL_SendString((unsigned char*)"\t");
      SHELL_SendString((unsigned char*)str);
      SHELL_SendString((unsigned char*)"\r\n");
    } /* for */
  } /* for */

  /* browsing through the file */
  SHELL_SendString((unsigned char*)"5. browse through all settings, file contents follows\n");
  ini_browse(Callback, NULL, inifile);

  /* string deletion */
  n = ini_puts("first", "alt", NULL, inifile);
  Check(n==1);
  n = ini_puts("second", "alt", NULL, inifile);
  Check(n==1);
  n = ini_puts("third", NULL, NULL, inifile);
  Check(n==1);
  /* ----- */
  n = ini_puts(NULL, "alt", NULL, inifile2);
  Check(n==1);
  SHELL_SendString((unsigned char*)"6. String deletion tests passed\n");

  return 0;
}

#endif

static portTASK_FUNCTION(MainTask, pvParameters) {
#if PL_HAS_ACCELEROMETER
  int16_t xmg, ymg;
#endif

  (void)pvParameters; /* parameter not used */
#if 0 && PL_HAS_MINI_INI
  TestMiniIni();
#endif
  for(;;) {
#if PL_HAS_ACCELEROMETER
    xmg = FX1_GetXmg();
    ymg = FX1_GetYmg();
    LED1_Put(xmg>100||xmg<-100||ymg>100||ymg<-100);
    LED2_Put(xmg>500||xmg<-500||ymg>500||ymg<-500);
#endif
    LED3_Neg();
#if PL_HAS_KEYS
    KEY1_ScanKeys();
#endif
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
}

void APP_Start(void) {
#if PL_HAS_RTOS_TRACE
  if(RTOSTRC1_uiTraceStart()!=1) {
    for(;;){} /* failure? */
  }
#endif
#if PL_HAS_RADIO
  RNETA_Init();
#endif
#if PL_HAS_FLOPPY
  FLOPPY_Init();
#endif
#if PL_HAS_MIDI
  MM_Init();
#endif
  SHELL_Init();
  if (FRTOS1_xTaskCreate(
      MainTask,  /* pointer to the task */
      "Main", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE+500, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
  /*lint -e527 */
     for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
  timerHndl = xTimerCreate("timer0", TIMER_PERIOD_MS/portTICK_RATE_MS, pdTRUE, (void *)0, vTimerCallback);
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) {
    for(;;); /* failure! */
  }
  FRTOS1_vTaskStartScheduler();
}

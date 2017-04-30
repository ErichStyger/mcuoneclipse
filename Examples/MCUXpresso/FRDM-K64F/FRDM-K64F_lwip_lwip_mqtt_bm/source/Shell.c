/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "config.h"
#if CONFIG_USE_SHELL
#include "Shell.h"
#include "Console.h"
#include "CLS1.h"
#if CONFIG_USE_DHCP
  #include "app_dhcp.h"
#endif
#if CONFIG_USE_SNTP
  #include "app_sntp.h"
#endif
#if CONFIG_USE_FREERTOS
  #include "FRTOS1.h"
#endif
#include "TmDt1.h"
#include "RTT1.h"
#include "lwip_mqtt_bm.h"

/* ******************************************************************
 * SHELL Standard I/O
 * ******************************************************************/
static void SHELL_SendChar(uint8_t ch) {
#if 0
  CLS1_SendCharFct(ch, RTT1_SendChar); /* blocking version with timeout */
#endif
  CLS1_SendCharFct(ch, CONSOLE_SendChar); /* blocking version with timeout */
}

static void SHELL_ReadChar(uint8_t *p) {
  *p = '\0'; /* default, nothing available */
#if 0
  if (RTT1_stdio.keyPressed()) {
    RTT1_stdio.stdIn(p);
    return;
  }
#endif
  if (CONSOLE_GetStdio()->keyPressed()) {
    CONSOLE_GetStdio()->stdIn(p);
    return;
  }
}

static bool SHELL_KeyPressed(void) {
#if 0
  if (RTT1_stdio.keyPressed()) {
    return TRUE;
  }
#endif
  if (CONSOLE_GetStdio()->keyPressed()) {
    return TRUE;
  }
  return FALSE;
}

CLS1_ConstStdIOType SHELL_stdio =
{
  (CLS1_StdIO_In_FctType)SHELL_ReadChar, /* stdin */
  (CLS1_StdIO_OutErr_FctType)SHELL_SendChar, /* stdout */
  (CLS1_StdIO_OutErr_FctType)SHELL_SendChar, /* stderr */
  SHELL_KeyPressed /* if input is not empty */
};

static uint8_t SHELL_DefaultShellBuffer[CLS1_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */

CLS1_ConstStdIOType *SHELL_GetStdio(void) {
  return &SHELL_stdio;
}

typedef struct {
  CLS1_ConstStdIOType *stdio;
  unsigned char *buf;
  size_t bufSize;
} SHELL_IODesc;

static const SHELL_IODesc ios[] =
{
  {&SHELL_stdio, SHELL_DefaultShellBuffer, sizeof(SHELL_DefaultShellBuffer)},
#if 1
  {&RTT1_stdio, RTT1_DefaultShellBuffer, sizeof(RTT1_DefaultShellBuffer)},
#endif
  /*! \todo Extend as needed */
};

void SHELL_SendString(unsigned char *msg) {
  CLS1_SendStr(msg, CLS1_GetStdio()->stdOut);
}

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if CONFIG_USE_FREERTOS
  FRTOS1_ParseCommand,
#endif
#if CONFIG_USE_DHCP
  DHCP_ParseCommand,
#endif
#if CONFIG_USE_SNTP
  SNTP_ParseCommand,
#endif
  TmDt1_ParseCommand,
  MQTT_ParseCommand,
  NULL /* Sentinel */
};

void SHELL_Process(void) {
  int i;

  /* process all I/Os */
  for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    (void)CLS1_ReadAndParseWithCommandTable(ios[i].buf, ios[i].bufSize, ios[i].stdio, CmdParserTable);
  }
}

void SHELL_Init(void) {
  CONSOLE_Init();
  CLS1_DefaultShellBuffer[0] = '\0';
  CLS1_SetStdio(&SHELL_stdio);
  CLS1_Init();
}

void SHELL_Deinit(void) {
  CLS1_SetStdio(NULL);
  CLS1_DefaultShellBuffer[0] = '\0';
  CLS1_Deinit();
}
#endif /* PL_CONFIG_HAS_SHELL */

/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */

#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "LEDR.h"
#include "LEDG.h"
#include "LEDB.h"
#include "MMA1.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if LEDR_PARSE_COMMAND_ENABLED
  LEDR_ParseCommand,
#endif
#if LEDG_PARSE_COMMAND_ENABLED
  LEDG_ParseCommand,
#endif
#if LEDB_PARSE_COMMAND_ENABLED
  LEDB_ParseCommand,
#endif
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
#if MMA1_PARSE_COMMAND_ENABLED
  MMA1_ParseCommand,
#endif
  NULL /* sentinel */
};

#if 1 /* XFormat test code */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "XF1.h"

static void MyPutChar(void *arg, char c) {
  CLS1_StdIO_OutErr_FctType fct = arg;
  
  fct(c);
}

unsigned int MyXprintf(const char *fmt, ...) {
  va_list args;
  unsigned int count;

  va_start(args,fmt);
  count = XF1_xvformat(MyPutChar, CLS1_GetStdio()->stdOut, fmt, args);
  va_end(args);
  return count;
}

static void TestXprintf(void) {
  (void)MyXprintf("Hello world\r\n");
  (void)MyXprintf("Hello %s\r\n","World");
  (void)MyXprintf("Not valid type %q\r\n");
  (void)MyXprintf("integer %05d %d %d\r\n",-7,7,-7);
  (void)MyXprintf("Unsigned %u %lu\r\n",123,123Lu);
  (void)MyXprintf("Octal %o %lo\r\n",123,123456L);
  (void)MyXprintf("Hex %x %X %lX\r\n",0x1234,0xf0ad,0xf2345678L);
#if XF1_XCFG_FORMAT_FLOAT
  (void)MyXprintf("Floating %6.2f\r\n",22.0/7.0);
  (void)MyXprintf("Floating %6.2f\r\n",-22.0/7.0);
  (void)MyXprintf("Floating %6.1f %6.2f\r\n",3.999,-3.999);
  (void)MyXprintf("Floating %6.1f %6.0f\r\n",3.999,-3.999);
#endif
}

static void TestXsprintf(void) {
  char buf[64];
  
  XF1_xsprintf(buf, "Hello world\r\n");
  CLS1_SendStr((unsigned char*)buf, CLS1_GetStdio()->stdOut);
  XF1_xsprintf(buf, "Hello %s\r\n","World");
  CLS1_SendStr((unsigned char*)buf, CLS1_GetStdio()->stdOut);
  XF1_xsprintf(buf, "Not valid type %q\r\n");
  CLS1_SendStr((unsigned char*)buf, CLS1_GetStdio()->stdOut);
  XF1_xsprintf(buf, "integer %05d %d %d\r\n",-7,7,-7);
  CLS1_SendStr((unsigned char*)buf, CLS1_GetStdio()->stdOut);
  XF1_xsprintf(buf, "Unsigned %u %lu\r\n",123,123Lu);
  CLS1_SendStr((unsigned char*)buf, CLS1_GetStdio()->stdOut);
  XF1_xsprintf(buf, "Octal %o %lo\r\n",123,123456L);
  CLS1_SendStr((unsigned char*)buf, CLS1_GetStdio()->stdOut);
  XF1_xsprintf(buf, "Hex %x %X %lX\r\n",0x1234,0xf0ad,0xf2345678L);
  CLS1_SendStr((unsigned char*)buf, CLS1_GetStdio()->stdOut);
#if XF1_XCFG_FORMAT_FLOAT
  XF1_xsprintf(buf, "Floating %6.2f\r\n",22.0/7.0);
  CLS1_SendStr((unsigned char*)buf, CLS1_GetStdio()->stdOut);
  XF1_xsprintf(buf, "Floating %6.2f\r\n",-22.0/7.0);
  CLS1_SendStr((unsigned char*)buf, CLS1_GetStdio()->stdOut);
  XF1_xsprintf(buf, "Floating %6.1f %6.2f\r\n",3.999,-3.999);
  CLS1_SendStr((unsigned char*)buf, CLS1_GetStdio()->stdOut);
  XF1_xsprintf(buf, "Floating %6.1f %6.0f\r\n",3.999,-3.999);
  CLS1_SendStr((unsigned char*)buf, CLS1_GetStdio()->stdOut);
#endif
}

#endif

static portTASK_FUNCTION(ShellTask, pvParameters) {
  unsigned char buf[48];

  (void)pvParameters; /* not used */
  buf[0] = '\0';
  TestXprintf();
  TestXsprintf();
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
    LEDG_Neg();
  }
}

void SHELL_Init(void) {
  if (FRTOS1_xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+200, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}


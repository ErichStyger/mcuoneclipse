/*
 * Application.c
 *
 *  Created on: 04.03.2016
 *      Author: Erich Styger
 */

#include "Application.h"
#include "CLS1.h"
#include "LED1.h"
#include "Shell.h"
#include "WAIT1.h"
#include "fs.h"

void APP_Start(void) {
  SHELL_Init();
  if (FS_Init()!=ERR_OK) {
    CLS1_SendStr("ERROR: Failed FS_Init()\r\n", CLS1_GetStdio()->stdErr);
    for(;;) {}
  }
  CLS1_SendStr("\r\n*****************************\r\nLittleFS with tinyK20\r\n*****************************\r\n", CLS1_GetStdio()->stdOut);
  for(;;) { /* main loop */
    LED1_Neg();
    WAIT1_Waitms(50);
    SHELL_Parse(); /* call command line parser */
  }
}

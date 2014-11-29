/*
 * Application.c
 *
 *      Author: Erich Styger
 */
#include "PE_Types.h"
#include "CLS1.h"
#include "WAIT1.h"
#include "Shell.h"
#include "ESP8266.h"

void APP_Run(void) {
  CLS1_ConstStdIOType *io;

  WAIT1_Waitms(1000); /* wait after power-on */
  ESP_Init();
  SHELL_Init();

  io = CLS1_GetStdio();
  CLS1_SendStr("\r\n------------------------------------------\r\n", io->stdOut);
  CLS1_SendStr("ESP8266 with FRDM-KL25Z\r\n", io->stdOut);
  CLS1_SendStr("------------------------------------------\r\n", io->stdOut);
  CLS1_PrintPrompt(io);
  for(;;) {
    ESP_Process();
    SHELL_Parse();
    WAIT1_Waitms(10);
  }
}

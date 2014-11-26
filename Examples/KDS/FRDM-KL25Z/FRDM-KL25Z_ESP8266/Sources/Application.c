/*
 * Application.c
 *
 *  Created on: 15.10.2014
 *      Author: tastyger
 */
#include "PE_Types.h"
#include "CLS1.h"
#include "WAIT1.h"
#include "AS2.h"
#include "UTIL1.h"
#include "Shell.h"
#include "ESP8266.h"

void APP_Run(void) {
  CLS1_ConstStdIOType *io;
  uint8_t buf[32];

  WAIT1_Waitms(1000); /* wait after restart */
  ESP_Init();
  SHELL_Init();

  io = CLS1_GetStdio();
  CLS1_SendStr("\r\n------------------------------------------\r\n", io->stdOut);
  CLS1_SendStr("ESP8266 with FRDM-KL25Z\r\n", io->stdOut);
  CLS1_SendStr("------------------------------------------\r\n", io->stdOut);

  if (ESP_Test()!=ERR_OK) {
    CLS1_SendStr("TEST failed!\r\n", io->stdErr);
  } else {
    CLS1_SendStr("TEST ok!\r\n", io->stdOut);
  }
  if (ESP_ConnectWiFi("ESP8266", "MyESP8266", 5, io)!=ERR_OK) {
    CLS1_SendStr("connection to WiFi FAILED!\r\n", io->stdErr);
  } else {
    CLS1_SendStr("connected to WiFi!\r\n", io->stdErr);
  }

  CLS1_PrintPrompt(io);
  for(;;) {
    ESP_Process();
    SHELL_Parse();
    WAIT1_Waitms(10);
  }
}

/*
 * Serial.c
 *
 *  Created on: 17.08.2010
 *      Author: Erich Styger
 */
#include "Platform.h"
#if PL_HAS_SHELL
#include "Serial.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#include <string.h>
#include "FSSH1.h"
#include <stdio.h>

/*! \brief Prints the help text to the console */
static void PrintHelp(const FSSH1_StdIOType *io) {
  (void)io;
  //FSSH1_SendStr("No help\r\n", io->stdOut);
}

static void PrintStatus(const FSSH1_StdIOType *io) {
  (void)io;
  //FSSH1_SendStr("Status       : ***** NO *****\r\n", io->stdOut); 
}

static byte ParseCommand(const unsigned char *cmd, bool *handled, const FSSH1_StdIOType *io) {
  if (strcmp((char*)cmd, FSSH1_CMD_HELP)==0) { /* help is handled locally as well in shell module */
    PrintHelp(io);
    *handled = TRUE;
  } else if (strcmp((char*)cmd, FSSH1_CMD_STATUS)==0) {
    PrintStatus(io);
    *handled = TRUE;
  }
  return ERR_OK;
}

/** 
 * \brief FreeRTOS task
 */
static portTASK_FUNCTION(ShellTask, pvParameters) {
  unsigned char cmd_buf[48];
  
  (void)pvParameters; /* parameter not used */
  cmd_buf[0] = '\0';
  (void)FSSH1_ParseCommand((unsigned char*)FSSH1_CMD_HELP, FSSH1_GetStdio(), ParseCommand); /* print help and prints as well the prompt */
  for(;;) {
    (void)FSSH1_ReadAndParseLine(cmd_buf, sizeof(cmd_buf), FSSH1_GetStdio(), ParseCommand);
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
}

void SERIAL_Start(void) {
  FSSH1_Init(); /* create mutex/semaphore */
  if (FRTOS1_xTaskCreate(
        ShellTask,  /* pointer to the task */
        (signed char*)"Shell", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE+350, /* task stack size */ /* note: 250 without shell 'copy' command */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) 
  {
    for(;;){}; /* error! probably out of memory */
  }
}
#endif /* PL_HAS_SHELL */

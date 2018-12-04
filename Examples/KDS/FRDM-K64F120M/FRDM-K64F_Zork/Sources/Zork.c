/*
 * Zork.c
 *
 *  Created on: 14.11.2018
 *      Author: Erich Styger Local
 */

#include <stdio.h>
#include "Zork.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "UTIL1.h"
#include "Zork/zork_config.h"

TaskHandle_t ZorkTaskHandle = NULL;

static void ZorkTask(void *pvParameters) {
  (void)pvParameters; /* not used */
  vTaskSuspend(NULL); /* suspend this task, until it gets waken up */
  vTaskDelay(pdMS_TO_TICKS(100)); /* give back some time to other tasks */
  UTIL1_randomSetSeed(xTaskGetTickCount()); /* initialize rand() with seed */
  zork_config(); /* initializes the game */
  if (run_zork_game()!=0) { /* run the game, does not return while it is running */
    CLS1_SendStr((uint8_t*)"Failed initializing game!\r\n", CLS1_GetStdio()->stdErr);
    vTaskResume(ShellTaskHandle); /* resume shell */
  }
  CLS1_SendStr((uint8_t*)"I know now why you cry. But it's something I can never do. Goodbye.\r\n", CLS1_GetStdio()->stdErr);
  vTaskDelay(pdMS_TO_TICKS(500)); /* give back some time to other tasks */
  ZORK_Init(); /* create new task, ready to run for a new game */
  vTaskDelete(NULL);  /* Hasta la vista, baby!  */
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((uint8_t*)"Zork", (uint8_t*)"Zork commands\r\n", io->stdOut);
  CLS1_SendHelpStr((uint8_t*)"  help", (uint8_t*)"Print help\r\n", io->stdOut);
  CLS1_SendHelpStr((uint8_t*)"  play", (uint8_t*)"Play Zork game\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t ZORK_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "Zork help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (UTIL1_strcmp((char*)cmd, "Zork play")==0) {
	  vTaskResume(ZorkTaskHandle); /* run the game */
	  vTaskSuspend(NULL); /* suspend the shell */
    *handled = TRUE;
    return ERR_OK;
  }
  return ERR_OK;
}

void ZORK_Deinit(void) {
  vTaskDelete(ZorkTaskHandle); /* bye, bye! */
}

void ZORK_Init(void) {
  if (xTaskCreate(ZorkTask, "Zork", 900/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, &ZorkTaskHandle) != pdPASS) {
	  for(;;){} /* error */
  }
}

void _exit(int i) { /* own exit routine */
  extern FILE *dbfile;
  if (dbfile!=NULL) {
	  fclose(dbfile); /* close the data file if it was open */
  }
  CLS1_SendStr((uint8_t*)"exit Zork program\r\n", CLS1_GetStdio()->stdErr);
  ZORK_Init(); /* create new sleeping task */
  vTaskResume(ShellTaskHandle); /* resume shell */
  vTaskDelete(NULL); /* kill current instance */
}

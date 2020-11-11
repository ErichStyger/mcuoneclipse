/*
 * Zork.c
 *
 *  Created on: 14.11.2018
 *      Author: Erich Styger Local
 */

#include <stdio.h>
#include "Shell.h"
#include "Zork/zork_config.h"
#include "Zork.h"
#include "McuShell.h"
#include "McuRTOS.h"
#include "McuUtility.h"

TaskHandle_t ZorkTaskHandle = NULL;

static void ZorkTask(void *pvParameters) {
  (void)pvParameters; /* not used */
  vTaskSuspend(NULL); /* suspend this task, until it gets waken up */
  vTaskDelay(pdMS_TO_TICKS(100)); /* give back some time to other tasks */
  zork_config(); /* initializes the game */
  if (run_zork_game()!=0) { /* run the game, does not return while it is running */
	McuShell_SendStr((uint8_t*)"Failed initializing game!\r\n", McuShell_GetStdio()->stdErr);
	vTaskResume(ShellTaskHandle); /* resume shell */
  }
  McuShell_SendStr((uint8_t*)"I know now why you cry. But it's something I can never do. Goodbye.\r\n", McuShell_GetStdio()->stdErr);
  vTaskDelay(pdMS_TO_TICKS(500)); /* give back some time to other tasks */
  ZORK_Init(); /* create new task, ready to run for a new game */
  vTaskDelete(NULL);  /* Hasta la vista, baby!  */
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((uint8_t*)"Zork", (uint8_t*)"Zork commands\r\n", io->stdOut);
  McuShell_SendHelpStr((uint8_t*)"  help", (uint8_t*)"Print help\r\n", io->stdOut);
  McuShell_SendHelpStr((uint8_t*)"  play", (uint8_t*)"Play Zork game\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t ZORK_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "Zork help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (McuUtility_strcmp((char*)cmd, "Zork play")==0) {
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
  McuUtility_randomSetSeed(1234);
}

void _exit(int i) { /* own exit routine */
  extern FILE *dbfile;
  if (dbfile!=NULL) {
	fclose(dbfile); /* close the data file if it was open */
  }
  McuShell_SendStr((uint8_t*)"exit Zork program\r\n", McuShell_GetStdio()->stdErr);
  ZORK_Init(); /* create new sleeping task */
  vTaskResume(ShellTaskHandle); /* resume shell */
  vTaskDelete(NULL); /* kill current instance */
}

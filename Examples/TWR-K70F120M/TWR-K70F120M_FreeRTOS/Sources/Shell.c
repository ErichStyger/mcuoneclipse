/*
 * Shell.c
 *
 *  Created on: 23.05.2011
 *      Author: Erich Styger
 */

#include "Shell.h"
#include "FRTOS1.h"
#include "FSSH1.h"
#include <string.h>

/*!
 * \brief Send a string to the stdio channel. 
 */
void SHELL_SendStr(const unsigned char *str) {
  FSSH1_SendStr(str, FSSH1_GetStdio()->stdOut);
}

/*! 
 * \brief Prints the help text to the console
 * \param io I/O channel to be used
 */
static void PrintHelp(const FSSH1_StdIOType *io) {
  /* list your local help here */
  (void)io;
}

/*! 
 * \brief Prints the status text to the console
 * \param io I/O channel to be used
 */
static void PrintStatus(const FSSH1_StdIOType *io) {
  /* list your local status here */
 (void)io;
}

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
static uint8_t ParseCommand(const unsigned char *cmd, bool *handled, const FSSH1_StdIOType *io) {
  /* handling our own commands */
  if (strcmp((const char*)cmd, (const char*)FSSH1_CMD_HELP)==0) {
    PrintHelp(io);
    *handled = TRUE;
  } else if (strcmp((const char*)cmd, (const char*)FSSH1_CMD_STATUS)==0) {
    PrintStatus(io);
    *handled = TRUE;
  }
  return ERR_OK;
}

static portTASK_FUNCTION(ShellTask, pvParameters) {
  unsigned char cmd_buf[32];

  (void)pvParameters;
  FSSH1_Init();
  cmd_buf[0] = '\0';
  (void)FSSH1_ParseCommand((const unsigned char*)FSSH1_CMD_HELP, FSSH1_GetStdio(), ParseCommand); 
  for(;;) {
    (void)FSSH1_ReadAndParseLine(cmd_buf, sizeof(cmd_buf), FSSH1_GetStdio(), ParseCommand /* local cmd parser */);
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
    LED2_Neg();
  }
}

void SHELL_Init(void) {
  if (FRTOS1_xTaskCreate(ShellTask, (signed char *)"Shell", configMINIMAL_STACK_SIZE+150, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}


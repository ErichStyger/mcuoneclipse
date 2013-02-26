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

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
static uint8_t ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  /* handling our own commands */
  return ERR_OK;
}

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
#if RTC1_PARSE_COMMAND_ENABLED
  RTC1_ParseCommand,
#endif
#if FAT1_PARSE_COMMAND_ENABLED
  FAT1_ParseCommand,
#endif
  ParseCommand,
  NULL /* sentinel */
};

static portTASK_FUNCTION(ShellTask, pvParameters) {
  unsigned char buf[48];

  (void)pvParameters; /* not used */
  buf[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
    LEDG_Neg();
  }
}

void SHELL_Init(void) {
  if (FRTOS1_xTaskCreate(ShellTask, (signed portCHAR *)"Shell", configMINIMAL_STACK_SIZE+200, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}


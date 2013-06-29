/**
 * \file
 * \brief This is the implementation module of the Shell console
 *
 * This interface file is used for a console and terminal.
 * That way we can interact with the target and change settings using a shell implementation
 */
#include "Shell.h"
#include "CLS1.h"
#include "FRTOS1.h"
#include <string.h> /* for strcmp() */
#include "USB1.h"
#include "LED1.h"

/*!
 * \brief Prints the help text to the console
 * \param io I/O channel to be used
 */
static void PrintHelp(const CLS1_StdIOType *io) {
  /* list your local help here */
  CLS1_SendHelpStr((unsigned char*)"my help", (unsigned char*)"My help text\r\n", io->stdOut);
}

/*!
 * \brief Prints the status text to the console
 * \param io I/O channel to be used
 */
static void PrintStatus(const CLS1_StdIOType *io) {
  /* list your local status here */
  CLS1_SendStatusStr((unsigned char*)"my status", (unsigned char*)"My status text\r\n", io->stdOut);
}

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
static uint8_t ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  /* handling our own commands */
  if (strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0) {
    PrintHelp(io);
    *handled = TRUE;
  } else if (strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0) {
    PrintStatus(io);
    *handled = TRUE;
  }
  /*! \todo Handle here the additional parsers */
  return ERR_OK;
}

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  ParseCommand,
  NULL /* Sentinel */
};

static portTASK_FUNCTION(ShellTask, pvParameters) {
  static unsigned char cmd_buf[32];
  uint8_t buf[USB1_DATA_BUFF_SIZE];
  bool startup = TRUE;

  (void)pvParameters;
  cmd_buf[0]='\0';
  for(;;) {
    if (CDC1_App_Task(buf, sizeof(buf))!=ERR_OK) {
      /* Call the USB application task, wait until enumeration has finished */
      while(CDC1_App_Task(buf, sizeof(buf))!=ERR_OK) {
        LED1_Neg(); /* flash LED fast to indicate that we are not communicating */
        FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
      }
    }
    LED1_Neg();
    (void)CLS1_ReadAndParseWithCommandTable(cmd_buf, sizeof(cmd_buf), CLS1_GetStdio(), CmdParserTable);
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
}

void SHELL_Init(void) {
  CLS1_Init(); /* create mutex/semaphore */
  if (FRTOS1_xTaskCreate(ShellTask, (signed portCHAR *)"Shell", configMINIMAL_STACK_SIZE+150, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

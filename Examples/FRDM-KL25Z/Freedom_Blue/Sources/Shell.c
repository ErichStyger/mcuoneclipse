/**
 * \file
 * \brief This is the implementation module of the Serial console
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This interface file is used for a console and terminal.
 * That way we can interact with the target and change settings using a shell implementation
 */
#include "Shell.h"
#include "FSSH1.h"
#include "UTIL1.h"
#include "Application.h"

/*!
 * \brief Prints the help text to the console
 * \param io I/O channel to be used
 */
static void PrintHelp(const FSSH1_StdIOType *io) {
  /* list your local help here */
#if 0
  FSSH1_SendHelpStr((unsigned char*)"shell", (unsigned char*)"Group of shell commands\r\n", io->stdOut);
  FSSH1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows trace help or status\r\n", io->stdOut);
  FSSH1_SendHelpStr((unsigned char*)"  i2c cmd on|off", (unsigned char*)"Receive command strings through I2C\r\n", io->stdOut);
#else
  (void)io;
#endif
}

/*!
 * \brief Prints the status text to the console
 * \param io I/O channel to be used
 */
static void PrintStatus(const FSSH1_StdIOType *io) {
  /* list your local status here */
#if 0
  FSSH1_SendStatusStr((unsigned char*)"shell", (unsigned char*)"\r\n", io->stdOut);
  if (SHELL_i2Commands) {
    FSSH1_SendStatusStr((unsigned char*)"  i2c cmd", (unsigned char*)"yes\r\n", io->stdOut);
  } else {
    FSSH1_SendStatusStr((unsigned char*)"  i2c cmd", (unsigned char*)"no\r\n", io->stdOut);
  }
#else
  (void)io;
#endif
}

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
static uint8_t SHELL_ParseCommand(const unsigned char *cmd, bool *handled, const FSSH1_StdIOType *io) {
  /* handling our own commands */
  if (UTIL1_strcmp((char*)cmd, FSSH1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "shell help")==0) {
    PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, FSSH1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, "shell status")==0) {
    PrintStatus(io);
    *handled = TRUE;
#if 0
  } else if (UTIL1_strcmp((char*)cmd, "shell i2c cmd on")==0) {
    SHELL_i2Commands = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "shell i2c cmd off")==0) {
    SHELL_i2Commands = FALSE;
    *handled = TRUE;
#endif
  }
  return ERR_OK;
}

static FSSH1_ParseCommandCallback ShellParsers[] =
{
  APP_ParseCommand,
  SHELL_ParseCommand
};

static uint8_t ParseCommand(const unsigned char *cmd, bool *handled, const FSSH1_StdIOType *io) {
  int i;

  /* iterate through all parser functions in table */
  for(i=0;i<sizeof(ShellParsers)/sizeof(FSSH1_ParseCommandCallback);i++) {
    if (ShellParsers[i](cmd, handled, io)!=ERR_OK) {
      return ERR_FAILED;
    }
  }
  return ERR_OK;
}

#if PL_HAS_RTOS
static portTASK_FUNCTION(ShellTask, pvParameters) {
  static unsigned char cmd_buf[48];

  (void)pvParameters;
  (void)FSSH1_ParseCommand((unsigned char*)FSSH1_CMD_HELP, FSSH1_GetStdio(), ParseCommand); /* print help and prints as well the prompt */
  cmd_buf[0] = '\0';
  for(;;) {
#if PL_USE_USB_SCI
    static char_t usb_tx_buf[USB1_DATA_BUFF_SIZE];
    (void)CDC1_App_Task(usb_tx_buf, sizeof(usb_tx_buf)); /* Call the USB application task */
#endif
    (void)FSSH1_ReadAndParseLine(cmd_buf, sizeof(cmd_buf), FSSH1_GetStdio(), ParseCommand);
#if PL_HAS_QUEUE
  #if QUEUE_SINGLE_CHAR
    {
      unsigned char ch;
      FSSH1_StdIO_OutErr_FctType io = FSSH1_GetStdio()->stdOut;

      while((ch=QUEUE_ReceiveChar()) && ch!='\0') {
        io(ch);
      }
    }
  #else
    {
      const unsigned char *msg;

      msg = QUEUE_ReceiveMessage();
      if (msg!=NULL) {
        FSSH1_SendStr(msg, FSSH1_GetStdio()->stdOut);
        FRTOS1_vPortFree((void*)msg);
      }
    }
  #endif
#endif
#if PL_HAS_I2C
    if (SHELL_i2Commands && I2C_ReceiveCommand(cmd_buf, sizeof(cmd_buf))==ERR_OK) {
      bool handled = FALSE;

      (void)ParseCommand(cmd_buf, &handled, FSSH1_GetStdio());
    }
#endif
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  }
}
#endif /* PL_HAS_RTOS */


void SHELL_ParseLine(const unsigned char *cmd) {
  (void)FSSH1_ParseCommand(cmd, FSSH1_GetStdio(), ParseCommand); /* print help and prints as well the prompt */
}

void SHELL_ReadAndParseLine(unsigned char *buf, size_t bufSize) {
  (void)FSSH1_ReadAndParseLine(buf, bufSize, FSSH1_GetStdio(), ParseCommand);
}

void SHELL_Init(void) {
  FSSH1_Init(); /* create mutex/semaphore */
#if PL_HAS_RTOS
  if (FRTOS1_xTaskCreate(ShellTask, (signed portCHAR *)"Shell", configMINIMAL_STACK_SIZE+150, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
}

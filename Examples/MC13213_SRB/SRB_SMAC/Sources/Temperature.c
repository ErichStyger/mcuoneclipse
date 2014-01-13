/**
 * \file
 * \brief Temperature driver module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a driver for the temperature sensor present on the SRB board
 */

#include "Platform.h"
#if PL_HAS_TEMPERATURE
#include "Temperature.h"
#include "TEMP1.h"
#if PL_HAS_SHELL
  #include "CLS1.h"
#endif
#include "UTIL1.h"

#if PL_HAS_SHELL
static void PrintStatus(const CLS1_StdIOType *io) {
  /* list your local status here */
#if PL_HAS_TEMPERATURE
  CLS1_SendStatusStr("Temperature", "", io->stdOut);
  TEMP1_Measure();
  CLS1_SendNum8s(TEMP1_ReadTemperature(), io->stdOut);  
  CLS1_SendStr(" C\r\n", io->stdOut);
#else
  (void)io;
#endif
}
#endif /*PL_HAS_SHELL*/

#if PL_HAS_SHELL
/*! 
 * \brief Prints the help text to the console
 * \param io I/O channel to be used
 */
static void PrintHelp(const CLS1_StdIOType *io) {
  /* list your local help here */
  CLS1_SendHelpStr("temp", "Group of Temperature commands\r\n", io->stdOut);
  CLS1_SendHelpStr("  status", "Print status information\r\n", io->stdOut);
}
#endif /*PL_HAS_SHELL*/

#if PL_HAS_SHELL
/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t TEMP_ParseCommand(const char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp(cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp(cmd, "temp status")==0) {
    PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp(cmd, "temp help")==0) {
    PrintHelp(io);
    *handled = TRUE;
  }
  return ERR_OK;
}
#endif /*PL_HAS_SHELL*/


void TEMP_Init(void) {
  /* nothing for now */
}

#endif /* PL_HAS_TEMPERATURE */


/**
 * \file
 * \brief Accelerometer Module
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module to calculate the speed based on the quadrature counter.
 */

#include "Platform.h" /* interface to the platform */

#if PL_HAS_ACCEL
#include "Accel.h"    /* our own interface */
#include "UTIL1.h"
#include "ACCEL1.h"
#include "CLS1.h"

void ACCEL_GetValues(int16_t *x, int16_t *y, int16_t *z) {
  *x = ACCEL1_GetXmg();
  *y = ACCEL1_GetYmg();
  *z = ACCEL1_GetZmg();
}

/*!
 * \brief Prints the system low power status
 * \param io I/O channel to use for printing status
 */
static void ACCEL_PrintStatus(const CLS1_StdIOType *io) {
  char buf[8];
  uint16_t val;
  
  CLS1_SendStatusStr("Accel", "\r\n", io->stdOut);

  CLS1_SendStatusStr("  raw", "0x", io->stdOut);
  val = ACCEL1_MeasureGetRawX();
  buf[0] = '\0';
  UTIL1_strcatNum16Hex(buf, sizeof(buf), (uint16_t)val);
  CLS1_SendStr(buf, io->stdOut);
  CLS1_SendStr(" (", io->stdOut);
  CLS1_SendNum16u(val, io->stdOut);
  CLS1_SendStr("), 0x", io->stdOut);

  val = ACCEL1_MeasureGetRawY();
  buf[0] = '\0';
  UTIL1_strcatNum16Hex(buf, sizeof(buf), (uint16_t)val);
  CLS1_SendStr(buf, io->stdOut);
  CLS1_SendStr(" (", io->stdOut);
  CLS1_SendNum16u(val, io->stdOut);
  CLS1_SendStr("), 0x", io->stdOut);
  
  val = ACCEL1_MeasureGetRawZ();
  buf[0] = '\0';
  UTIL1_strcatNum16Hex(buf, sizeof(buf), (uint16_t)val);
  CLS1_SendStr(buf, io->stdOut);
  CLS1_SendStr(" (", io->stdOut);
  CLS1_SendNum16u(val, io->stdOut);
  CLS1_SendStr(")\r\n", io->stdOut);

  CLS1_SendStatusStr("  milli-g", "", io->stdOut);
  CLS1_SendNum16s(ACCEL1_GetXmg(), io->stdOut);
  CLS1_SendStr(" ", io->stdOut);
  CLS1_SendNum16s(ACCEL1_GetYmg(), io->stdOut);
  CLS1_SendStr(" ", io->stdOut);
  CLS1_SendNum16s(ACCEL1_GetZmg(), io->stdOut);
  CLS1_SendStr("\r\n", io->stdOut);

  CLS1_SendStatusStr("  raw+offset", "", io->stdOut);
  CLS1_SendNum16s(ACCEL1_GetX(), io->stdOut);
  CLS1_SendStr(" ", io->stdOut);
  CLS1_SendNum16s(ACCEL1_GetY(), io->stdOut);
  CLS1_SendStr(" ", io->stdOut);
  CLS1_SendNum16s(ACCEL1_GetZ(), io->stdOut);
  CLS1_SendStr("\r\n", io->stdOut);
  
  CLS1_SendStatusStr("  calibOffset", "", io->stdOut);
  CLS1_SendNum16s(ACCEL1_GetXOffset(), io->stdOut);
  CLS1_SendStr(" ", io->stdOut);
  CLS1_SendNum16s(ACCEL1_GetYOffset(), io->stdOut);
  CLS1_SendStr(" ", io->stdOut);
  CLS1_SendNum16s(ACCEL1_GetZOffset(), io->stdOut);
  CLS1_SendStr("\r\n", io->stdOut);
  
  CLS1_SendStatusStr("  calib 1g", "", io->stdOut);
  CLS1_SendNum16s(ACCEL1_GetX1gValue(), io->stdOut);
  CLS1_SendStr(" ", io->stdOut);
  CLS1_SendNum16s(ACCEL1_GetY1gValue(), io->stdOut);
  CLS1_SendStr(" ", io->stdOut);
  CLS1_SendNum16s(ACCEL1_GetZ1gValue(), io->stdOut);
  CLS1_SendStr("\r\n", io->stdOut);
}

/*! 
 * \brief Prints the help text to the console
 * \param io I/O channel to be used
 */
static void ACCEL_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr("accel", "Group of accelerometer commands\r\n", io->stdOut);
  CLS1_SendHelpStr("  help|status", "Shows accelerometer help or status\r\n", io->stdOut);
  CLS1_SendHelpStr("  calibrate x|y|z", "Performs accelerometer calibration\r\n", io->stdOut);
}

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t ACCEL_ParseCommand(const char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp(cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp(cmd, "accel help")==0) {
    ACCEL_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp(cmd, "accel status")==0) {
    ACCEL_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, "accel calibrate x")==0) {
    ACCEL1_CalibrateX1g();
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, "accel calibrate y")==0) {
    ACCEL1_CalibrateY1g();
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, "accel calibrate z")==0) {
    ACCEL1_CalibrateZ1g();
    *handled = TRUE;
  }
  return ERR_OK;
}

/*! \brief Initializes module */
void ACCEL_Init(void) {
  /*! \todo Think about a useful initialization (calibration?) of the sensor */
  ACCEL1_CalibrateZ1g(); /* assume device is flat during reset/power-up */
}
#endif /* PL_HAS_ACCEL */


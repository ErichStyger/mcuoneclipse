/**
 * \file
 * \brief Reflectance sensor driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a driver for the reflectance sensor array.
 */

#ifndef REFLECTANCE_H_
#define REFLECTANCE_H_

#include "Platform.h"
#if PL_CONFIG_HAS_REFLECTANCE

#define REF_NOF_SENSORS 6
#define REF_MIDDLE_LINE_VALUE  ((REF_NOF_SENSORS+1)*1000/2)
#define REF_MAX_LINE_VALUE     ((REF_NOF_SENSORS-1)*1000) /* maximum value for REF_GetLine() */

typedef enum {
  REF_LINE_NONE=0,     /* no line, sensors do not see a line */
  REF_LINE_STRAIGHT=1, /* forward line |, sensors see a line underneath */
  REF_LINE_LEFT=2,     /* left half of sensors see line */
  REF_LINE_RIGHT=3,    /* right half of sensors see line */
  REF_LINE_FULL=4,     /* all sensors see a line */
  REF_NOF_LINES        /* Sentinel */
} REF_LineKind;

REF_LineKind REF_GetLineKind(void);

void REF_GetSensorValues(uint16_t *values, int nofValues);

#if PL_CONFIG_HAS_SHELL
  #include "CLS1.h"
  
  /*!
   * \brief Shell parser routine.
   * \param cmd Pointer to command line string.
   * \param handled Pointer to status if command has been handled. Set to TRUE if command was understood.
   * \param io Pointer to stdio handle
   * \return Error code, ERR_OK if everything was ok.
   */
  uint8_t REF_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

  #define REF_PARSE_COMMAND_ENABLED 1
#else
  #define REF_PARSE_COMMAND_ENABLED 0
#endif

/*!
 * \brief Starts or stops the calibration.
 */
void REF_CalibrateStartStop(void);

/*!
 * \brief returns the current line value (weighted average).
 */
uint16_t REF_GetLineValue(void);

/*!
 * \brief Determines if the line sensor is calibrated or not
 * \return TRUE if calibrated.
 */
bool REF_IsReady(void);

/*!
 * \brief Driver Deinitialization.
 */
void REF_Deinit(void);

/*!
 * \brief Driver Initialization.
 */
void REF_Init(void);

#endif /* PL_CONFIG_HAS_REFLECTANCE */

#endif /* REFLECTANCE_H_ */

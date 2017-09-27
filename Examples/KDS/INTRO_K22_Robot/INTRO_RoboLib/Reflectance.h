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
#if PL_HAS_LINE_SENSOR
#if PL_IS_ZUMO_ROBOT
  #define REF_SENSOR1_IS_LEFT        0   /* if sensor 1 is on the left side */
  #define REF_MIN_LINE_VAL        0x60   /* minimum value indicating a line */
  #define REF_MIN_NOISE_VAL       0x40   /* values below this are not added to the weighted sum */
  #define REF_SENSOR_TIMEOUT_US   1200   /* after this time, consider no reflection (black) */
#elif PL_IS_ROUND_ROBOT
  #define REF_SENSOR1_IS_LEFT    0   /* if sensor 1 is on the left side */
  #define REF_MIN_LINE_VAL    0x20   /* minimum value indicating a line */
  #define REF_MIN_NOISE_VAL   0x0F   /* values below this are not added to the weighted sum */
  #define REF_SENSOR_TIMEOUT_US  3000  /* after this time, consider no reflection (black) */
#elif PL_IS_TRACK_ROBOT
  #define REF_SENSOR1_IS_LEFT    1   /* if sensor 1 is on the left side */
  #define REF_MIN_LINE_VAL    0x20   /* minimum value indicating a line */
  #define REF_MIN_NOISE_VAL   0x0F   /* values below this are not added to the weighted sum */
  #define REF_SENSOR_TIMEOUT_US  3000  /* after this time, consider no reflection (black) */
#elif PL_IS_INTRO_ZUMO_ROBOT
  #define REF_SENSOR1_IS_LEFT    1   /* if sensor 1 is on the left side */
  #define REF_MIN_LINE_VAL    0x20   /* minimum value indicating a line */
  #define REF_MIN_NOISE_VAL   0x10   /* values below this are not added to the weighted sum */
  #define REF_SENSOR_TIMEOUT_US  3000   /* after this time, consider no reflection (black) */
#elif PL_IS_INTRO_ZUMO_ROBOT2 || PL_IS_INTRO_ZUMO_K22
  #define REF_SENSOR1_IS_LEFT       1   /* if sensor 1 is on the left side */
#if PL_DO_MINT /* different color/reflection for MINT environment */
  #define REF_MIN_LINE_VAL      0x120   /* minimum value indicating a line */
  #define REF_MIN_NOISE_VAL      0x80   /* values below this are not added to the weighted sum */
#else
  #define REF_MIN_LINE_VAL       0x80   /* minimum value indicating a line */
  #define REF_MIN_NOISE_VAL      0x40   /* values below this are not added to the weighted sum */
#endif
  #define REF_SENSOR_TIMEOUT_US  1500   /* after this time, consider no reflection (black). Must be smaller than the timeout period of the RefCnt timer! */
#else
  #error "unknown configuration!"
#endif

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
#endif

#if (PL_IS_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT2 || PL_IS_INTRO_ZUMO_K22)
  #define REF_NOF_SENSORS 6
#elif (PL_IS_ROUND_ROBOT || PL_IS_TRACK_ROBOT)
  #define REF_NOF_SENSORS 8
#else
  #error "unknown configuration!"
#endif

#define REF_MIDDLE_LINE_VALUE  ((REF_NOF_SENSORS+1)*1000/2)
#define REF_MAX_LINE_VALUE     ((REF_NOF_SENSORS+1)*1000) /* maximum value for REF_GetLine() */

typedef enum {
  REF_LINE_NONE=0,     /* no line, sensors do not see a line */
  REF_LINE_STRAIGHT=1, /* forward line |, sensors see a line underneath */
  REF_LINE_LEFT=2,     /* left half of sensors see line */
  REF_LINE_RIGHT=3,    /* right half of sensors see line */
  REF_LINE_FULL=4,     /* all sensors see a line */
  REF_LINE_AIR=5,      /* all sensors have a timeout value. Robot is not on ground at all? */
  REF_NOF_LINES        /* Sentinel */
} REF_LineKind;


typedef enum {
  REF_LINE_KIND_MODE_LINE_FOLLOW,   /* returns REF_LINE_NONE, REF_LINE_STRAIGHT or REF_LINE_FULL */
  REF_LINE_KIND_MODE_ALL,          /* returns all different line kinds */
  REF_LINE_KIND_MODE_MAZE,          /* returns all different line kinds */
  REF_LINE_KIND_MODE_SUMO,          /* returns all different line kinds */
} REF_LineKindMode;

REF_LineKind REF_GetLineKind(REF_LineKindMode mode);

void REF_DumpCalibrated(void);

unsigned char *REF_LineKindStr(REF_LineKind line);

uint16_t REF_GetLineValue(bool *onLine);
uint16_t REF_LineWidth(void);

void REF_GetSensorValues(uint16_t *values, int nofValues);

/*!
 * \brief Starts or stops the calibration.
 */
void REF_CalibrateStartStop(void);

/*!
 * \brief Function to find out if we can use the sensor (means: it is calibrated and not currently calibrating)
 * \return TRUE if the sensor is ready.
 */
bool REF_CanUseSensor(void);

/*!
 * \brief Driver Deinitialization.
 */
void REF_Deinit(void);

/*!
 * \brief Driver Initialization.
 */
void REF_Init(void);

#endif /* PL_HAS_LINE_SENSOR */

#endif /* REFLECTANCE_H_ */

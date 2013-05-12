/*
 * Turn.h
 *
 *  Created on: Mar 11, 2013
 *      Author: Erich Styger
 */

#ifndef TURN_H_
#define TURN_H_

#include "Platform.h"
#if PL_HAS_LINE_SENSOR

#include "CLS1.h"
#include "Reflectance.h"

typedef enum {
  TURN_LEFT90,   /* turn 90 degree left and stop */
  TURN_RIGHT90, /* turn 90 degree right and stop */
  TURN_LEFT180, /* turn 180 degree counterclockwise and stop */
  TURN_RIGHT180, /* turn 180 degree clockwise and stop */
  TURN_STRAIGHT, /* don't turn */
  TURN_STEP_FW, /* make a step forward and stop */
  TURN_STEP_BW, /* make a step backward and stop */
  TURN_FINISHED, /* stepped into finish! */
  TURN_STOP     /* stop */
} TURN_Kind;

/*!
 * \brief Translate a turn kind into a string
 * \return String, like "STOP"
 */
const unsigned char *TURN_TurnKindStr(TURN_Kind kind);

/*!
 * \brief Turns the robot.
 * \param kind How much the robot has to turn.
 */
void TURN_Turn(TURN_Kind kind);

/*!
 * \brief Shell command line parser.
 * \param[in] cmd Pointer to command string
 * \param[out] handled If command is handled by the parser
 * \param[in] io Std I/O handler of shell
 */
uint8_t TURN_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

/*!
 * \brief Initializes the module.
 */
void TURN_Init(void);
#endif /* PL_HAS_LINE_SENSOR */

#endif /* TURN_H_ */

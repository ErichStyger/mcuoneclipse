/*
 * Turn.h
 *
 *  Created on: Mar 11, 2013
 *      Author: Erich Styger
 */

#ifndef TURN_H_
#define TURN_H_

#include "CLS1.h"
#include "Reflectance.h"

typedef enum {
  TURN_LEFT90,   /* turn 90 degree left */
  TURN_RIGHT90, /* turn 90 degree right */
  TURN_LEFT180, /* turn 180 degree counterclockwise */
  TURN_RIGHT180, /* turn 180 degree clockwise */
  TURN_STRAIGHT, /* don't turn */
  TURN_STOP     /* stop it */
} TURN_Kind;


/*!
 * \brief Selects a turning depending on the current line kind.
 * @param line Current line kind
 * @return New turn, e.g TURN_AROUND if we passed a dead end.
 */
TURN_Kind TURN_SelectTurn(REF_LineKind line);

/*!
 * \brief Turns the robot.
 * \param kind How much the robot has to turn.
 */
void TURN_Turn(TURN_Kind kind);

/*!
 * \brief Moves the robot about one inch backward
 */
void TURN_StepBackward(void);

/*!
 * \brief Moves the robot about one inch forward
 */
void TURN_StepForward(void);

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

#endif /* TURN_H_ */

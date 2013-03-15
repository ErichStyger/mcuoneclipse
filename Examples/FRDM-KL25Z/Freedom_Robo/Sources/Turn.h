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
  TURN_LEFT,   /* turn 90 degree left */
  TURN_RIGHT, /* turn 90 degree right */
  TURN_AROUND, /* turn 180 degree */
  TURN_STRAIGHT, /* don't turn */
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

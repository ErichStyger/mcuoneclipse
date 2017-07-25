/**
 * \file
 * \brief Robot turning interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements turning of the robot.
 */

#ifndef TURN_H_
#define TURN_H_

#include "Platform.h"
#if PL_HAS_MOTOR

#include "Reflectance.h"

typedef enum {
  TURN_LEFT45,   /* turn 45 degree left and stop */
  TURN_LEFT90,   /* turn 90 degree left and stop */
  TURN_RIGHT45, /* turn 90 degree right and stop */
  TURN_RIGHT90, /* turn 90 degree right and stop */
  TURN_LEFT180, /* turn 180 degree counterclockwise and stop */
  TURN_RIGHT180, /* turn 180 degree clockwise and stop */
  TURN_STRAIGHT, /* don't turn */
  TURN_STEP_LINE_FW, /* make a step forward over the line */
  TURN_STEP_LINE_FW_POST_LINE, /* make a step forward over the line and post the line for a turn */
  TURN_STEP_LINE_BW_POST_LINE, /* make a step backward over the line and post the line for a turn */
  TURN_STEP_LINE_BW, /* make a step backward over the line */
  TURN_STEP_BORDER_BW, /* step back from Sumo border */
  TURN_STEP_POST_LINE_FW, /* step past to line, before a turn */
  TURN_STEP_POST_LINE_BW, /* same as TURN_STEP_POST_LINE_FW, but backwards */
  TURN_FINISHED, /* stepped into finish! */
  TURN_STOP_LEFT,   /* stop left motor */
  TURN_STOP_RIGHT,  /* stop right motor */
  TURN_STOP     /* stop */
} TURN_Kind;

/*! \brief Callback type function to stop process or turning */
typedef bool (*TURN_StopFct)(void);

/*!
 * \brief Translate a turn kind into a string
 * \return String, like "STOP"
 */
const unsigned char *TURN_TurnKindStr(TURN_Kind kind);

#if !PL_HAS_QUADRATURE
/*!
 * \brief Sets a new turn duty in percent.
 * \param duty New duty.
 * \return Previous duty value.
 */
uint8_t TURN_SetDutyPercent(uint8_t duty);
#endif
    
/*!
 * \brief Turns the robot.
 * \param kind How much the robot has to turn.
 */
void TURN_Turn(TURN_Kind kind, TURN_StopFct stopIt);

/*!
 * \brief Turn robot into position.
 * \param targetLPos Left wheel position.
 * \param targetRPos Right wheel position.
 * \param wait Wait until it is in position.
 * \param stopIt Callback to stop turning, or NULL.
 * \param timeoutMs Timout value in milliseconds for turning operation.
 */
void TURN_MoveToPos(int32_t targetLPos, int32_t targetRPos, bool wait, TURN_StopFct stopIt, int32_t timeoutMs);

/*!
 * \brief Turn by angle
 * \param angle Angle, negative angle means left turn, positive means right turn
 */
void TURN_TurnAngle(int16_t angle, TURN_StopFct stopIt);

void TURN_SetStepsLine(int32_t stepsLine, int32_t stepsPostLine);

#if PL_CONFIG_HAS_SHELL
#include "CLS1.h"
/*!
 * \brief Shell command line parser.
 * \param[in] cmd Pointer to command string
 * \param[out] handled If command is handled by the parser
 * \param[in] io Std I/O handler of shell
 */
uint8_t TURN_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

/*!
 * \brief Initializes the module.
 */
void TURN_Init(void);
#endif /* PL_HAS_LINE_SENSOR */

#endif /* TURN_H_ */

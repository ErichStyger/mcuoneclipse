/*
 * ESC.h
 *
 *  Created on: 20.09.2015
 *      Author: tastyger
 */

#ifndef SOURCES_ESC_H_
#define SOURCES_ESC_H_

#include "Platform.h"

#if PL_HAS_SHELL
#include "CLS1.h"
/*!
 * \brief Shell command line parser.
 * \param[in] cmd Pointer to command string
 * \param[out] handled If command is handled by the parser
 * \param[in] io Std I/O handler of shell
 */
uint8_t ESC_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif /* PL_HAS_SHELL */

typedef enum {
  ESC_MOTOR_FRONT_LEFT,
  ESC_MOTOR_FRONT_RIGHT,
  ESC_MOTOR_BACK_RIGHT,
  ESC_MOTOR_BACK_LEFT,
  ESC_MOTOR_NOF /* 4 */
} ESC_MotorID;

typedef void *MOT_MotorHandle;

MOT_MotorHandle MOT_GetMotorHandle(ESC_MotorID motor);
uint8_t ESC_SetDutyUS(MOT_MotorHandle motorHandle, uint16_t us);

void ESC_Init(void);


#endif /* SOURCES_ESC_H_ */

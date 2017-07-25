/*
 * MintLed.h
 *
 *  Created on: 22.08.2016
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_INTRO_ROBOLIB_MINTLED_H_
#define SOURCES_INTRO_ROBOLIB_MINTLED_H_

#include "CLS1.h"

typedef enum {
  MINTLED_MODE_NONE,          /* not doing anything */
  MINTLED_MODE_ERROR,          /* error mode */
  MINTLED_MODE_TEST,          /* testing mode */
  MINTLED_MODE_JOYSTICK,      /* joystick driving mode */
  MINTLED_MODE_AUTOMATIC,        /* automatic mode */
  MINTLED_MODE_BALL_REQUESTD, /* ball shall be loaded into robot */
  MINTLED_MODE_BALL_LOADED, /* ball is loaded in robot */
  MINTLED_MODE_WAIT_BALL_REMOVAL, /* ball is loaded in robot */
  MINTLED_MODE_GOTO_START,      /* goto start */
  MINTLED_MODE_GOTO_FINISH,      /* goto finish */
  MINTLED_MODE_STANDBY,      /* robot is in standby */
  MINTLED_MODE_MANUAL_ON_START,  /* manual driving, and reached start area */
  MINTLED_MODE_MANUAL_ON_FINISH,  /* manual driving, and reached finish area */
  MINTLED_MODE_NOF_MODES   /* sentinel */
} MINTLED_ModeType;

uint8_t MINTLED_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void MINTLED_SetMode(MINTLED_ModeType mode);

void MINTLED_Init(void);


#endif /* SOURCES_INTRO_ROBOLIB_MINTLED_H_ */

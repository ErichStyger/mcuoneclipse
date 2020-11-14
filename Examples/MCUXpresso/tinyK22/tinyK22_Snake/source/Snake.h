/**
 * \file
 * \brief Snake game
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a classic Nokia phone game: the Snake game.
 */

#ifndef SNAKE_H_
#define SNAKE_H_

#include "McuRTOS.h"

typedef enum {
  SNAKE_NO_EVENT,
  SNAKE_UP_EVENT,
  SNAKE_DOWN_EVENT,
  SNAKE_LEFT_EVENT,
  SNAKE_RIGHT_EVENT,
  SNAKE_ENTER_EVENT,
  SNAKE_START_STOP_EVENT,
  SNAKE_RESUME_GAME,
  SNAKE_SUSPEND_GAME
} SNAKE_Event;

BaseType_t SNAKE_SendButtonEventFromISR(SNAKE_Event event, BaseType_t *pxHigherPriorityTaskWoken);
void SNAKE_SendEvent(SNAKE_Event event);
bool SNAKE_GameIsRunning(void);

/*!
 * \brief Driver de-initialization.
 */
void SNAKE_Deinit(void);

/*!
 * \brief Driver initialization.
 */
void SNAKE_Init(void);

#endif /* SNAKE_H_ */

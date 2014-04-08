/*
 * Application.h
 *
 *  Created on: Apr 7, 2014
 *      Author: tastyger
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Platform.h"

void APP_OnKeyPressed(uint8_t keys);
void APP_OnKeyReleasedLong(uint8_t keys);
void APP_OnKeyReleased(uint8_t keys);

void APP_HandleEvent(uint8_t event);

void APP_DebugPrint(unsigned char*);

void APP_Run(void);

#endif /* APPLICATION_H_ */

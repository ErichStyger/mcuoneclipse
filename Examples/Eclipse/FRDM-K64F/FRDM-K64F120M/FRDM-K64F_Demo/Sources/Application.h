/**
 * \file
 * \brief Main Application Interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Interface to the main application module. 
 * From here the application runs and performs all tasks.
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "PE_Types.h"

void APP_OnKeyPressed(uint8_t keys);
void APP_OnKeyReleased(uint8_t keys);
void APP_OnKeyReleasedLong(uint8_t keys);

void APP_DebugPrint(unsigned char *str);

/*!
 * \brief Application main start and main routine 
 */
void APP_Start(void);

#endif /* APPLICATION_H_ */

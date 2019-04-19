/*
 * shutdown.h
 *
 *  Created on: 11.04.2019
 *      Author: Erich Styger
 */

#ifndef SHUTDOWN_H_
#define SHUTDOWN_H_

#include <stdbool.h>

bool SHUTDOWN_UserPowerOffRequested(void);

void SHUTDOWN_RequestPowerOff(void);

void SHUTDOWN_Init(void);
void SHUTDOWN_Deinit(void);

#endif /* SHUTDOWN_H_ */

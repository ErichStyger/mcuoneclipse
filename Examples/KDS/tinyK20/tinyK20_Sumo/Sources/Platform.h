/*
 * Platform.h
 *
 *  Created on: 17.07.2017
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_PLATFORM_H_
#define SOURCES_PLATFORM_H_

#include "MCUC1.h" /* common types for all modules */

#define PL_CONFIG_HAS_SHELL   (1)
#define PL_CONFIG_HAS_MOTOR   (1)

void PL_Init(void);

#endif /* SOURCES_PLATFORM_H_ */

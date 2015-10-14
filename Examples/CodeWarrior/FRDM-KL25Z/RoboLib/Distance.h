/*
 * Distance.h
 *
 *  Created on: Jun 23, 2013
 *      Author: Erich Styger
 */

#ifndef DISTANCE_H_
#define DISTANCE_H_

#include "Platform.h"
#if PL_HAS_DISTANCE_SENSOR
#include "CLS1.h"

uint8_t DIST_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

bool DIST_5cmLeftOn(void);
bool DIST_5cmRightOn(void);
bool DIST_10cmLeftOn(void);
bool DIST_10cmRightOn(void);

/*!
 * \brief Driver initialization.
 */
void DIST_Init(void);

/*!
 * \brief Driver de-initialization.
 */
void DIST_Deinit(void);

#endif /* PL_HAS_DISTANCE_SENSOR */

#endif /* DISTANCE_H_ */

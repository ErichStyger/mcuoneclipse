/*
 * MazeRace.h
 *
 *  Created on: 15.12.2015
 *      Author: tastyger
 */

#ifndef SOURCES_MAZERACE_H_
#define SOURCES_MAZERACE_H_

#include "CLS1.h"

uint8_t MR_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

typedef enum {
  MR_EVENT_START,
  MR_EVENT_TRGA,
  MR_EVENT_TRGB
} MR_Event;

void MR_DoEvent(MR_Event event);

#endif /* SOURCES_MAZERACE_H_ */

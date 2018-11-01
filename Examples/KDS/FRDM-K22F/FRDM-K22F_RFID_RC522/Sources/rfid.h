/*
 * rfid.h
 *
 */

#ifndef SOURCES_RC522_RFID_H_
#define SOURCES_RC522_RFID_H_

#include <stdint.h>
#include <stdbool.h>
#include "CLS1.h"

uint8_t RFID_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io);

void RFID_Init(void);

#endif /* SOURCES_RC522_RFID_H_ */

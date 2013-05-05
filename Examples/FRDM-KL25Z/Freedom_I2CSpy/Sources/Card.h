/*
 * Card.h
 *
 *  Created on: May 1, 2013
 *      Author: Erich Styger
 */

#ifndef CARD_H_
#define CARD_H_

#include "CLS1.h"

uint8_t CARD_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

#endif /* CARD_H_ */

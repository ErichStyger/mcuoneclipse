/*
 * MPC4728.h
 *
 *  Created on: Jan 30, 2014
 *      Author: tastyger
 */
#ifndef _MPC4728_H__
#define _MPC4728_H__

#include "CLS1.h"

byte MPC4728_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void MPC4728_Deinit(void);

void MPC4728_Init(void);


#endif /* _MPC4728_H__ */

/*
 * Test.h
 *
 *  Created on: Oct 6, 2013
 *      Author: tastyger
 */

#ifndef TEST_H_
#define TEST_H_

#include "Platform.h"
#if PL_HAS_TEST
#include "CLS1.h"

uint8_t TEST_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

/*!
 * \brief Driver initialization.
 */
void TEST_Init(void);

/*!
 * \brief Driver de-initialization.
 */
void TEST_Deinit(void);

#endif /* PL_HAS_TEST */

#endif /* TEST_H_ */

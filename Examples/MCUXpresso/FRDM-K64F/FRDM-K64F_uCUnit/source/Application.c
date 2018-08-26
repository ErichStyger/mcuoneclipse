/*
 * Application.c
 *
 *  Created on: 25.08.2018
 *      Author: Erich Styger
 */

#include "Application.h"
#include "uCUnit.h"



void APP_Run(void) {
	UCUNIT_Init();

	UCUNIT_TestcaseBegin("first test case.");

	UCUNIT_Shutdown();
}

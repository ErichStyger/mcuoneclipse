/*
 * Application.c
 *
 *  Created on: 25.08.2018
 *      Author: Erich Styger
 */

#include "Application.h"
#include "uCUnit.h"



typedef enum {
	Unknown,
	Hydrogen, /* H */
	Helium,   /* He */
	Oxygen,   /* O */
	Oxygen2,  /* O2 */
	Water,    /* H2O */
} Chem_t;

Chem_t crazyScientist(Chem_t a, Chem_t b) {
	if (a==Oxygen && b==Oxygen) {
		return Oxygen2;
	}
	if (a==Hydrogen && b==Oxygen2) {
		return Water;
	}
	return Unknown;
}


void APP_Run(void) {
	Chem_t res;
	UCUNIT_Init(); /* initialize framework */

	/* start test case */
	UCUNIT_TestcaseBegin("My test case");
	res = crazyScientist(Oxygen, Oxygen);
    UCUNIT_CheckIsEqual(res, Oxygen2);
    UCUNIT_CheckIsEqual(Unknown, crazyScientist(Water, Helium));
    UCUNIT_CheckIsEqual(Water, crazyScientist(Hydrogen, Oxygen2));
    UCUNIT_CheckIsEqual(Water, crazyScientist(Oxygen2, Hydrogen));
	UCUNIT_TestcaseEnd();

	/* finish all the tests */
	UCUNIT_WriteSummary();
	UCUNIT_Shutdown();
}

/*
 * Application.c
 *
 *  Created on: 25.08.2018
 *      Author: Erich Styger
 */

#include "Application.h"
#include "uCUnit.h"
#include "fsl_debug_console.h"

int checkedDivide(int a, int b) {
	if (b==0) {
		UCUNIT_Tracepoint(0); /* mark trace point */
		PRINTF("division by zero is not defined!\n");
		return 0;
	}
	return a/b;
}

char *endOfString(char *str) {
	if (str==NULL) {
		return NULL;
	}
	while(*str!='\0') {
		str++;
	}
	return str;
}


typedef enum {
	Unknown,  /* first, generic item */
	Hydrogen, /* H */
	Helium,   /* He */
	Oxygen,   /* O */
	Oxygen2,  /* O2 */
	Water,    /* H2O */
	ChemLast  /* last, sentinel */
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
	int i;
	char *str;
	UCUNIT_Init(); /* initialize framework */

	UCUNIT_TestcaseBegin("Cracy Scientist");
	res = crazyScientist(Oxygen, Oxygen);
    UCUNIT_CheckIsEqual(res, Oxygen2);
    UCUNIT_CheckIsEqual(Unknown, crazyScientist(Water, Helium));
    UCUNIT_CheckIsEqual(Water, crazyScientist(Hydrogen, Oxygen2));
    UCUNIT_CheckIsEqual(Water, crazyScientist(Oxygen2, Hydrogen));
    UCUNIT_CheckIsInRange(crazyScientist(Unknown, Unknown), Unknown, ChemLast);
	UCUNIT_TestcaseEnd();

	UCUNIT_TestcaseBegin("Checked Divide");
	UCUNIT_CheckIsEqual(100/5, checkedDivide(100,5));
	UCUNIT_ResetTracepointCoverage(); /* start tracking */
	UCUNIT_CheckIsEqual(0, checkedDivide(1024,0));
	UCUNIT_CheckTracepointCoverage(0); /* check coverage of point 0 */
	UCUNIT_TestcaseEnd();

	UCUNIT_TestcaseBegin("Strings");
	UCUNIT_CheckIsNull(endOfString(NULL));
	str = endOfString("abc");
	UCUNIT_Check(
			(str!=NULL), /* condition to check */
			"string shall be not NULL", /* message */
			"str" /* argument as string */
			);
	UCUNIT_CheckIsEqual('\0', *endOfString(""));
	UCUNIT_CheckIsEqual('\0', *endOfString("hello"));
	str = endOfString("world");
	UCUNIT_CheckIsNotNull(str);
	UCUNIT_CheckIsEqual('\0', *str);
	UCUNIT_TestcaseEnd();

	/* finish all the tests */
	UCUNIT_WriteSummary();
	UCUNIT_Shutdown();
}

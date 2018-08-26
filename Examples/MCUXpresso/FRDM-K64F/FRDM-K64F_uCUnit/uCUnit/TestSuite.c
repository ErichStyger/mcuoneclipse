/*
 * TestSuite.c
 */

#include "uCUnit-v1.0.h"
#include "TestSuite.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

static void ExampleTestCase(void) {
	UCUNIT_TestcaseBegin("simple tests"); /* open test case */

	UCUNIT_CheckIsEqual(3, 0);

	UCUNIT_TestcaseEnd(); /* close test case */
}

void Testsuite_RunTests(void) {
	UCUNIT_Init(); /* initialize test framework */

	/*! \todo add more test cases */
	ExampleTestCase(); /* example test case */

	UCUNIT_WriteSummary();

	UCUNIT_Shutdown();
}

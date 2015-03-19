/**
 * \file
 * \brief Interface to demo functions to test the profile/function recorder.
 * \author Erich Styger
 */

#ifndef DEMO_H_
#define DEMO_H_

/*!
 * \brief Function to return the function names.
 * \param addr Address of function.
 * \return Returns a string identifying the function.
 */
const char *DEMO_getFuncName(void *addr);

/*!
 * \brief Demo function.
 * \return integral value, just for testing.
 */
int DEMO_Run(void);

/*!
 * Initialization function for the demo.
 */
void DEMO_Init(void);

#endif /* DEMO_H_ */

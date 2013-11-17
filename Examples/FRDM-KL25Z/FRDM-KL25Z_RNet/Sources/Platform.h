/*
 * Platform.h
 *
 *  Created on: Nov 15, 2013
 *      Author: tastyger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "PE_Types.h" /* types like uint8_t */
#include "PE_Error.h" /* PEx error codes */
#include <stddef.h> /* for size_t */

#define PL_HAS_RADIO   1 /* set to one to enable the RADIO */
#define PL_HAS_SHELL   0 /* set to one if we have a shell */
#define PL_HAS_RSTDIO  0

#endif /* PLATFORM_H_ */

/**
 * \file
 * \brief Platform configuration file
 * \author Erich Styger
 *
 * This header file provides an interface to the underlying hardware platform and includes common header files.
 * Additionally it is used to configure the application features and behavior.
  */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "PE_Types.h" /* types like uint8_t */
#include "PE_Error.h" /* PEx error codes */
#include <stddef.h>   /* for size_t */

#define PL_HAS_RADIO   (1) 
  /*!< set to one to include the radio stack */
#define PL_HAS_SHELL   (1)
  /*!< set to one if we have a Shell */
#define PL_HAS_RSTDIO  (0) 
  /*!< set to one if we use remote stdio */

#endif /* PLATFORM_H_ */

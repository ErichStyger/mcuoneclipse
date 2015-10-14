/**
 * \file
 * \brief Application main interface.
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This header file defines the interface to the main application.
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Platform.h"

#if PL_HAS_DEBUG_PRINT
  void APP_DebugPrint(unsigned char *str);
#else
  #define APP_DebugPrint(str) /*nothing */
#endif

/*! 
 * \brief Run the application main loop.
 */
void APP_Run(void);

#endif /* APPLICATION_H_ */

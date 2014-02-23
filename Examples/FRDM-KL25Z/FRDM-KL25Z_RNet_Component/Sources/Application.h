/*
 * Application.h
 *
 *  Created on: Feb 22, 2014
 *      Author: tastyger
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Platform.h"

#if PL_HAS_DEBUG_PRINT
  void APP_DebugPrint(unsigned char *str);
#else
  #define APP_DebugPrint(str) /*nothing */
#endif

  
void APP_Run(void);

#endif /* APPLICATION_H_ */

/*
 * CygProfile.h
 *
 *  Created on: 15.03.2015
 *      Author: tastyger
 */

#ifndef CYGPROFILE_H_
#define CYGPROFILE_H_

#define CYG_FUNC_TRACE_ENABLED        (1)
  /*!< 1: Trace enabled, 0: trace disabled */

#define CYG_FUNC_TRACE_NAMES_ENABLED  (1 && CYG_FUNC_TRACE_ENABLED)
  /*!< 1: Trace with symbolic names enabled, 0: disabled */

typedef const char *(*CYG_GetFuncNameFct)(void *addr);
  /*!< Function prototype to get the name for function (start) address */

/*!
 * \brief Print the call trace to the terminal.
 */
void CYG_PrintCallTrace(void);

/*!
 * \brief Driver Initialization.
 */
void CYG_Init(void);

/*!
 * \brief Driver De-Initialization.
 */
void CYG_Deinit(void);

#endif /* CYGPROFILE_H_ */

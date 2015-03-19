/**
 * \file
 * \brief Interface to profile/function recorder.
 * \author Erich Styger
 *
 * With -finstrument-functions compiler option, each function entry and exit function
 * will call the hooks __cyg_profile_func_enter() and __cyg_profile_func_exit() which
 * can be used to trace function calls.
 * Functions which shall *not* be profiled/recorded need __attribute__((no_instrument_function)).
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

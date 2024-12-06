/**
 * Copyright (c) 2017 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `McuLog.c` for details.
 */

/* Original source is from https://github.com/rxi/log.c
 * McuLib integration and extensions: Copyright (c) 2020 Erich Styger
 */

#ifndef MCULOG_H
#define MCULOG_H

#include "McuLogconfig.h"
#ifdef __cplusplus
extern "C" {
#endif

#if McuLog_CONFIG_IS_ENABLED

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include "McuShell.h"
#if McuLog_CONFIG_USE_FILE
  #include "McuFatFS.h"
#endif

#define McuLog_VERSION "0.1.2"

#define McuLog_RTT_DATA_LOGGER_CHANNEL   (1) /* channel used for the RTT data logger */

typedef enum { McuLog_TRACE, McuLog_DEBUG, McuLog_INFO, McuLog_WARN, McuLog_ERROR, McuLog_FATAL } McuLog_Levels_e;

/* note: gcc supports __BASE_FILE__ instead of __FILE__ */
#ifndef __BASE_FILE__
  #define __BASE_FILE__ __FILE__
#endif
#define McuLog_trace(...) McuLog_log(McuLog_TRACE, __BASE_FILE__, __LINE__, __VA_ARGS__)
#define McuLog_debug(...) McuLog_log(McuLog_DEBUG, __BASE_FILE__, __LINE__, __VA_ARGS__)
#define McuLog_info(...)  McuLog_log(McuLog_INFO,  __BASE_FILE__, __LINE__, __VA_ARGS__)
#define McuLog_warn(...)  McuLog_log(McuLog_WARN,  __BASE_FILE__, __LINE__, __VA_ARGS__)
#define McuLog_error(...) McuLog_log(McuLog_ERROR, __BASE_FILE__, __LINE__, __VA_ARGS__)
#define McuLog_fatal(...) McuLog_log(McuLog_FATAL, __BASE_FILE__, __LINE__, __VA_ARGS__)

#define McuLog_traceString(str) McuLog_logString(McuLog_TRACE, __BASE_FILE__, __LINE__, str)
#define McuLog_debugString(str) McuLog_logString(McuLog_DEBUG, __BASE_FILE__, __LINE__, str)
#define McuLog_infoString(str) McuLog_logString(McuLog_INFO, __BASE_FILE__, __LINE__, str)
#define McuLog_warnString(str) McuLog_logString(McuLog_WARN, __BASE_FILE__, __LINE__, str)
#define McuLog_errorString(str) McuLog_logString(McuLog_ERROR, __BASE_FILE__, __LINE__, str)
#define McuLog_fatalString(str) McuLog_logString(McuLog_FATAL, __BASE_FILE__, __LINE__, str)

void McuLog_set_console(McuShell_ConstStdIOType *io, uint8_t index);

#if McuLog_CONFIG_USE_MUTEX
  typedef void (*log_LockFn)(void *udata, bool lock);
  void McuLog_set_lock(log_LockFn fn);
  void McuLog_set_udata(void *udata);
#endif

  #if McuLog_CONFIG_USE_FILE
  void McuLog_set_fp(McuFatFS_FIL *fp);
  int McuLog_open_logfile(const unsigned char *logFileName); /* returns 0 on success */
  int McuLog_close_logfile(void); /* returns 0 on success */
#endif
void McuLog_set_level(McuLog_Levels_e level);
void McuLog_set_quiet(bool enable);

#if McuLog_CONFIG_USE_COLOR
void McuLog_set_color(bool enable);
#endif

#if McuLog_CONFIG_USE_PRINTF_STYLE
  void McuLog_log(McuLog_Levels_e level, const char *file, int line, const char *fmt, ...);
  void McuLog_ChannelLog(uint8_t channel, McuLog_Levels_e level, const char *file, int line, const char *fmt, ...);
#endif

void McuLog_logString(McuLog_Levels_e level, const char *file, int line, const char *str);

#if McuLog_CONFIG_PARSE_COMMAND_ENABLED
uint8_t McuLog_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);
#endif

void McuLog_Init(void);
void McuLog_Deinit(void);

#else /* not enabled: do not add anything to the code */
  /* dummy implementation to 'nothing' */
  #define McuLog_traceString(str) do{}while(0)
  #define McuLog_debugString(str) do{}while(0)
  #define McuLog_infoString(str)  do{}while(0)
  #define McuLog_warnString(str)  do{}while(0)
  #define McuLog_errorString(str) do{}while(0)
  #define McuLog_fatalString(str) do{}while(0)

  #define McuLog_trace(...) do{}while(0)
  #define McuLog_debug(...) do{}while(0)
  #define McuLog_info(...)  do{}while(0)
  #define McuLog_warn(...)  do{}while(0)
  #define McuLog_error(...) do{}while(0)
  #define McuLog_fatal(...) do{}while(0)

  #define McuLog_set_console(io,ch)                 do{}while(0)
  #define McuLog_set_udata(udata)                   do{}while(0)
  #define McuLog_set_lock(fn)                       do{}while(0)
  #define McuLog_set_fp(fp)                         do{}while(0)
  #define McuLog_set_level(level)                   do{}while(0)
  #define McuLog_set_quiet(enable)                  do{}while(0)
  #define McuLog_set_color(enable)                  do{}while(0)
  #define McuLog_log(level, file, line, fmt, ...)   do{}while(0)

  #define McuLog_Init()   do{}while(0)
  #define McuLog_Deinit() do{}while(0)
#endif /* McuLog_CONFIG_IS_ENABLED */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCULOG_H */



/**
 * Copyright (c) 2017 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

/* Original source is on https://github.com/rxi/log.c */

#ifndef MCULOG_H
#define MCULOG_H

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include "McuLogconfig.h"
#include "McuShell.h"
#if MCULOG_CONFIG_USE_FILE
  #include "McuFatFS.h"
#endif

#define MCULOG_VERSION "0.1.1"

typedef void (*log_LockFn)(void *udata, int lock);

typedef enum { MCULOG_TRACE, MCULOG_DEBUG, MCULOG_INFO, MCULOG_WARN, MCULOG_ERROR, MCULOG_FATAL } McuLog_Levels_e;

/* note: gcc supports __BASE_FILE__ */
#define McuLog_trace(...) McuLog_log(MCULOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define McuLog_debug(...) McuLog_log(MCULOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define McuLog_info(...)  McuLog_log(MCULOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define McuLog_warn(...)  McuLog_log(MCULOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define McuLog_error(...) McuLog_log(MCULOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define McuLog_fatal(...) McuLog_log(MCULOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

void McuLog_set_console(McuShell_ConstStdIOType *io);
void McuLog_set_udata(void *udata);
void McuLog_set_lock(log_LockFn fn);
#if MCULOG_CONFIG_USE_FILE
void McuLog_set_fp(McuFatFS_FIL *fp);
#endif
void McuLog_set_level(McuLog_Levels_e level);
void McuLog_set_quiet(bool enable);

#if MCULOG_CONFIG_USE_COLOR
void McuLog_set_color(bool enable);
#endif

void McuLog_log(McuLog_Levels_e level, const char *file, int line, const char *fmt, ...);

#if MCULOG_CONFIG_PARSE_COMMAND_ENABLED
uint8_t McuLog_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);
#endif

void McuLog_Init(void);
void McuLog_Deinit(void);

#endif

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
#include <stdarg.h>
#include "McuLogconfig.h"

#define MCULOG_VERSION "0.1.1"

typedef void (*log_LockFn)(void *udata, int lock);

enum { MCULOG_TRACE, MCULOG_DEBUG, MCULOG_INFO, MCULOG_WARN, MCULOG_ERROR, MCULOG_FATAL };

/* note: gcc supports __BASE_FILE__ */
#define McuLog_trace(...) McuLog_log(MCULOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define McuLog_debug(...) McuLog_log(MCULOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define McuLog_info(...)  McuLog_log(MCULOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define McuLog_warn(...)  McuLog_log(MCULOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define McuLog_error(...) McuLog_log(MCULOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define McuLog_fatal(...) McuLog_log(MCULOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

void McuLog_set_udata(void *udata);
void McuLog_set_lock(log_LockFn fn);
void McuLog_set_fp(FILE *fp);
void McuLog_set_level(int level);
void McuLog_set_quiet(int enable);

void McuLog_log(int level, const char *file, int line, const char *fmt, ...);

void McuLog_Init(void);
void McuLog_Deinit(void);

#endif

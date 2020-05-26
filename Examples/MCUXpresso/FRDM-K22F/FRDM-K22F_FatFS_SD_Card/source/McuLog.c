/*
 * Copyright (c) 2017 rxi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/* original source is on https://github.com/rxi/log.c */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "McuLog.h"
#include "McuTimeDate.h"
#include "McuUtility.h"
#include "McuXFormat.h"
#include "McuRTT.h"
#include "McuShell.h"

static struct {
  void *udata;
  log_LockFn lock;
  FILE *fp;
  int level;
  int quiet;
} L;


static const char *level_names[] = {
  "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

#if MCULOG_USE_COLOR
static const char *level_colors[] = {
#if MCULOG_USE_RTT_COLOR
    RTT_CTRL_TEXT_BRIGHT_BLUE, RTT_CTRL_TEXT_BRIGHT_GREEN, RTT_CTRL_TEXT_BRIGHT_CYAN, RTT_CTRL_TEXT_BRIGHT_YELLOW, RTT_CTRL_TEXT_BRIGHT_RED, RTT_CTRL_TEXT_BRIGHT_MAGENTA
#else
  "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
#endif
};
#endif


static void lock(void)   {
  if (L.lock) {
    L.lock(L.udata, 1);
  }
}


static void unlock(void) {
  if (L.lock) {
    L.lock(L.udata, 0);
  }
}


void McuLog_set_udata(void *udata) {
  L.udata = udata;
}


void McuLog_set_lock(log_LockFn fn) {
  L.lock = fn;
}


void McuLog_set_fp(FILE *fp) {
  L.fp = fp;
}


void McuLog_set_level(int level) {
  L.level = level;
}


void McuLog_set_quiet(int enable) {
  L.quiet = enable ? 1 : 0;
}

static void OutputCharFct(void *p, char c) {
  McuShell_StdIO_OutErr_FctType io = (McuShell_StdIO_OutErr_FctType)p;

  io(c);
}

static void PrintFileName(const char *fileName, McuShell_ConstStdIOType *io) {
  const unsigned char *p;

  p = (const unsigned char*)fileName;
  while(*p==' ' || *p=='.') {
    p++; /* skip leading spaces or dots */
  }
  McuShell_SendStr(p, io->stdErr);
}

void McuLog_log(int level, const char *file, int line, const char *fmt, ...) {
  if (level < L.level) {
    return;
  }

  /* Acquire lock */
  lock();

  /* Get current time */
  TIMEREC time;

  (void)McuTimeDate_GetTime(&time);

  /* Log to stderr */
  if (!L.quiet) {
    unsigned char buf[32];

    buf[0] = '\0';
    McuTimeDate_AddTimeString(buf, sizeof(buf), &time, (unsigned char*)McuTimeDate_CONFIG_DEFAULT_TIME_FORMAT_STR);

    //McuShell_ConstStdIOType *io = McuRTT_GetStdio(); /* only log to RTT */
    McuShell_ConstStdIOType *io = McuShell_GetStdio();

    McuShell_SendStr(buf, io->stdErr); /* timestamp */
    McuShell_SendStr((unsigned char *)" ", io->stdErr);
#if MCULOG_USE_COLOR
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)level_colors[level]);
    McuUtility_strcatPad(buf, sizeof(buf), (unsigned char*)level_names[level], ' ', sizeof("DEBUG ")-1);
#else
    buf[0] = '\0';
    McuUtility_strcatPad(buf, sizeof(buf), (unsigned char*)level_names[level], ' ', sizeof("DEBUG ")-1);
#endif
#if MCULOG_USE_COLOR
    //McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\x1b[0m \x1b[90m");
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)RTT_CTRL_RESET);
#endif
    McuShell_SendStr(buf, io->stdErr); /* log level */
    PrintFileName(file, io);
    McuShell_SendStr((unsigned char *)":", io->stdErr);
    McuShell_SendNum32u(line, io->stdErr);
    McuShell_SendStr((unsigned char *)": ", io->stdErr);
    McuXFormat_xformat(OutputCharFct, io->stdErr, fmt);
    McuShell_SendStr((unsigned char *)"\n", io->stdErr);
  }

  /* Log to file */
  if (L.fp) {
    va_list args;
    char buf[32];
    McuTimeDate_AddTimeString((unsigned char*)buf, sizeof(buf), &time, (unsigned char*)McuTimeDate_CONFIG_DEFAULT_TIME_FORMAT_STR);
//    buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", lt)] = '\0';
    fprintf(L.fp, "%s %-5s %s:%d: ", buf, level_names[level], file, line);
    va_start(args, fmt);
    vfprintf(L.fp, fmt, args);
    va_end(args);
    fprintf(L.fp, "\n");
    fflush(L.fp);
  }

  /* Release lock */
  unlock();
}

#include "McuRTOS.h"

static SemaphoreHandle_t McuLog_Mutex;

static void LockUnlockCallback(void *data, int lock) {
  if (lock) {
    (void)xSemaphoreTakeRecursive(McuLog_Mutex, portMAX_DELAY);
  } else {
    (void)xSemaphoreGiveRecursive(McuLog_Mutex);
  }
}

void McuLog_Init(void) {
  McuLog_Mutex = xSemaphoreCreateRecursiveMutex();
  if (McuLog_Mutex==NULL) { /* semaphore creation failed */
    for(;;) {} /* error, not enough memory? */
  }
  vQueueAddToRegistry(McuLog_Mutex, "McuLog_Mutex");
  McuLog_set_lock(LockUnlockCallback);
}

void McuLog_Deinit(void) {
  vSemaphoreDelete(McuLog_Mutex);
  McuLog_Mutex = NULL;
  McuLog_set_lock(NULL);
}


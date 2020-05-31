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

/* Credits: original source is on https://github.com/rxi/log.c
 * McuLib integration: Copyright (c) 2020 Erich Styger
 */

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
#if MCULOG_CONFIG_USE_MUTEX
  #include "McuRTOS.h"
#endif
#if MCULOG_CONFIG_USE_FILE
  #include "McuFatFS.h"
#endif

static struct {
  void *udata;  /* optional data for mutex */
  log_LockFn lock; /* mutex */
  McuShell_ConstStdIOType *consoleIo; /* I/O for console logging */
#if MCULOG_CONFIG_USE_FILE
  McuFatFS_FIL *fp; /* logging to file */
#endif
  McuLog_Levels_e level; /* 0 (TRACE) to 5 (FATAL) */
  bool quiet; /* if logging is silent/quiet */
#if MCULOG_CONFIG_USE_COLOR
  bool color; /* if using color for terminal */
#endif
#if MCULOG_CONFIG_USE_MUTEX
  SemaphoreHandle_t McuLog_Mutex;
#endif
} L;

static const char *level_names[] = {
  "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

#if MCULOG_CONFIG_USE_COLOR
static const char *level_colors[] = {
  McuShell_ANSI_COLOR_TEXT_BRIGHT_BLUE,     /* trace */
  McuShell_ANSI_COLOR_TEXT_BRIGHT_GREEN,    /* debug */
  McuShell_ANSI_COLOR_TEXT_BRIGHT_CYAN,     /* info */
  McuShell_ANSI_COLOR_TEXT_BRIGHT_YELLOW,   /* warn */
  McuShell_ANSI_COLOR_TEXT_BRIGHT_RED,      /* error */
  McuShell_ANSI_COLOR_TEXT_BRIGHT_MAGENTA   /* fatal */
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

void McuLog_set_console(McuShell_ConstStdIOType *io) {
  L.consoleIo = io;
}

void McuLog_set_udata(void *udata) {
  L.udata = udata;
}

void McuLog_set_lock(log_LockFn fn) {
  L.lock = fn;
}

#if MCULOG_CONFIG_USE_FILE
void McuLog_set_fp(McuFatFS_FIL *fp) {
  L.fp = fp;
}
#endif

void McuLog_set_level(McuLog_Levels_e level) {
  L.level = level;
}

#if MCULOG_CONFIG_USE_COLOR
void McuLog_set_quiet(bool enable) {
  L.quiet = enable;
}
#endif

void McuLog_set_color(bool enable) {
  L.color = enable;
}

static void OutputCharFctConsole(void *p, char c) {
  McuShell_StdIO_OutErr_FctType io = (McuShell_StdIO_OutErr_FctType)p;

  io(c);
}

#if MCULOG_CONFIG_USE_FILE
static void OutputCharFctFile(void *p, char c) {
  McuFatFS_FIL *fp = (McuFatFS_FIL*)p;

  f_putc(c, fp);
}
#endif

static void PrintFileName(const char *fileName, McuShell_StdIO_OutErr_FctType out) {
  const unsigned char *p;

  p = (const unsigned char*)fileName;
  while(*p==' ' || *p=='.') {
    p++; /* skip leading spaces or dots */
  }
  McuShell_SendStr(p, out);
}

void McuLog_log(McuLog_Levels_e level, const char *file, int line, const char *fmt, ...) {
  if (level < L.level) {
    return;
  }

  /* Acquire lock */
  lock();

  /* Get current time */
  TIMEREC time;

  (void)McuTimeDate_GetTime(&time);

  /* Log to stderr */
  if (!L.quiet && L.consoleIo!=NULL) {
    unsigned char buf[32];

    buf[0] = '\0';
    McuTimeDate_AddTimeString(buf, sizeof(buf), &time, (unsigned char*)McuTimeDate_CONFIG_DEFAULT_TIME_FORMAT_STR);
    McuShell_SendStr(buf, L.consoleIo->stdErr); /* timestamp */
    McuShell_SendStr((unsigned char *)" ", L.consoleIo->stdErr);
    buf[0] = '\0';
#if MCULOG_CONFIG_USE_COLOR
    if (L.color) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)level_colors[level]);
    }
#endif
    McuUtility_strcatPad(buf, sizeof(buf), (unsigned char*)level_names[level], ' ', sizeof("DEBUG ")-1);
#if MCULOG_CONFIG_USE_COLOR
    if (L.color) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)McuShell_ANSI_CONTROL_RESET);
    }
#endif
    McuShell_SendStr(buf, L.consoleIo->stdErr); /* log level */
    PrintFileName(file, L.consoleIo->stdErr);
    McuShell_SendStr((unsigned char *)":", L.consoleIo->stdErr);
    McuShell_SendNum32u(line, L.consoleIo->stdErr);
    McuShell_SendStr((unsigned char *)": ", L.consoleIo->stdErr);

    va_list list;

    va_start(list,fmt);
    McuXFormat_xvformat(OutputCharFctConsole, L.consoleIo->stdErr, fmt, list);
    va_end(list);;
    McuShell_SendStr((unsigned char *)"\n", L.consoleIo->stdErr);
  }

#if MCULOG_CONFIG_USE_FILE
  /* Log to file */
  if (L.fp) {
    va_list list;

    char buf[32];

    buf[0] = '\0';
    McuTimeDate_AddTimeString((unsigned char*)buf, sizeof(buf), &time, (unsigned char*)McuTimeDate_CONFIG_DEFAULT_TIME_FORMAT_STR);
    f_printf(L.fp, "%s %-5s %s:%d: ", buf, level_names[level], file, line);

    va_start(list, fmt);
    McuXFormat_xvformat(OutputCharFctFile, L.fp, fmt, list);
    va_end(list);

    f_printf(L.fp, "\n");
    f_sync(L.fp);
  }
#endif
  /* Release lock */
  unlock();
}

#if MCULOG_CONFIG_USE_MUTEX
static void LockUnlockCallback(void *data, int lock) {
  if (lock) {
    (void)xSemaphoreTakeRecursive(L.McuLog_Mutex, portMAX_DELAY);
  } else {
    (void)xSemaphoreGiveRecursive(L.McuLog_Mutex);
  }
}
#endif

#if MCULOG_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  McuShell_SendStatusStr((unsigned char*)"McuLog", (unsigned char*)"Log status\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  level", (unsigned char*)level_names[L.level], io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  lock", L.lock!=NULL?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
#if MCULOG_CONFIG_USE_FILE
  McuShell_SendStatusStr((unsigned char*)"  file", L.fp!=NULL?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
#endif
  McuShell_SendStr((unsigned char*)" (", io->stdOut);
  McuShell_SendNum8u(L.level, io->stdOut);
  McuShell_SendStr((unsigned char*)"), logging for this level and higher\r\n", io->stdOut);
#if MCULOG_CONFIG_USE_COLOR
  McuShell_SendStatusStr((unsigned char*)"  color", L.color?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
#endif
  return ERR_OK;
}
#endif /* MCULOG_CONFIG_PARSE_COMMAND_ENABLED */

#if MCULOG_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"McuLog", (unsigned char*)"Group of McuLog commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  level <level>", (unsigned char*)"Set log level (0-5)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  quiet <on|off>", (unsigned char*)"Set quiet mode\r\n", io->stdOut);
#if MCULOG_CONFIG_USE_COLOR
  McuShell_SendHelpStr((unsigned char*)"  color <on|off>", (unsigned char*)"Set color mode\r\n", io->stdOut);
#endif
  return ERR_OK;
}
#endif /* MCULOG_CONFIG_PARSE_COMMAND_ENABLED */

#if MCULOG_CONFIG_PARSE_COMMAND_ENABLED
uint8_t McuLog_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;
  const unsigned char *p;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "McuLog help") == 0)
  {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "McuLog status")==0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "McuLog quiet on")==0) {
    *handled = TRUE;
    McuLog_set_quiet(true);
  } else if (McuUtility_strcmp((char*)cmd, "McuLog quiet off")==0) {
    *handled = TRUE;
    McuLog_set_quiet(false);
#if MCULOG_CONFIG_USE_COLOR
  } else if (McuUtility_strcmp((char*)cmd, "McuLog color on")==0) {
    *handled = TRUE;
    McuLog_set_color(true);
  } else if (McuUtility_strcmp((char*)cmd, "McuLog color off")==0) {
    *handled = TRUE;
    McuLog_set_color(false);
#endif
    } else if (McuUtility_strncmp((char*)cmd, "McuLog level ", sizeof("McuLog level ")-1)==0) {
    uint8_t level;

    *handled = TRUE;
    p = cmd+sizeof("McuLog level ")-1;
    if (McuUtility_ScanDecimal8uNumber(&p, &level)==ERR_OK && level<=MCULOG_FATAL) {
      McuLog_set_level(level);
    }
  }
  return res;
}
#endif /* MCULOG_CONFIG_PARSE_COMMAND_ENABLED */

void McuLog_Init(void) {
#if MCULOG_CONFIG_USE_MUTEX
  L.McuLog_Mutex = xSemaphoreCreateRecursiveMutex();
  if (L.McuLog_Mutex==NULL) { /* semaphore creation failed */
    for(;;) {} /* error, not enough memory? */
  }
  vQueueAddToRegistry(L.McuLog_Mutex, "McuLog_Mutex");
  McuLog_set_lock(LockUnlockCallback);
#endif
#if MCULOG_CONFIG_USE_COLOR
  McuLog_set_color(true);
#endif
  L.consoleIo = McuShell_GetStdio();
}

void McuLog_Deinit(void) {
#if MCULOG_CONFIG_USE_MUTEX
  vSemaphoreDelete(L.McuLog_Mutex);
  L.McuLog_Mutex = NULL;
  McuLog_set_lock(NULL);
#endif
}


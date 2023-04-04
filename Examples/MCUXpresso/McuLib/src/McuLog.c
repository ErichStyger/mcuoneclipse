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

/* Original source is from https://github.com/rxi/log.c
 * McuLib integration and extensions: Copyright (c) 2020 Erich Styger
 */

#include "McuLog.h"
#if McuLog_CONFIG_IS_ENABLED

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "McuTimeDate.h"
#include "McuUtility.h"
#include "McuXFormat.h"
#include "McuShell.h"
#if McuLog_CONFIG_USE_MUTEX
  #include "McuRTOS.h"
#endif
#if McuLog_CONFIG_USE_FILE
  #include "McuFatFS.h"
#endif
#if McuLog_CONFIG_USE_RTT_DATA_LOGGER || McuLog_CONFIG_USE_RTT_CONSOLE
  #include "McuRTT.h"
#endif

static struct {
  McuLog_Levels_e level; /* 0 (TRACE) to 5 (FATAL) */
#if McuLog_CONFIG_USE_MUTEX
  SemaphoreHandle_t McuLog_Mutex; /* built-in FreeRTOS mutex used for lock below */
#endif
#if McuLog_CONFIG_USE_MUTEX
  log_LockFn lock; /* user mutex for synchronization */
  void *udata;  /* optional data for lock */
#endif
  McuShell_ConstStdIOType *consoleIo[McuLog_CONFIG_NOF_CONSOLE_LOGGER]; /* I/O for console logging */
  bool quiet; /* if console logging is silent/quiet */
#if McuLog_CONFIG_USE_COLOR
  bool color; /* if using color for terminal */
#endif
#if McuLog_CONFIG_USE_FILE
  McuFatFS_FIL *fp; /* file handle */
  McuFatFS_FIL logFile; /* FatFS log file descriptor */
#endif
#if McuLog_CONFIG_USE_RTT_DATA_LOGGER
  bool rttDataLogger;
#endif
} McuLog_ConfigData;

static const char *const level_names[] = {
  "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

#if McuLog_CONFIG_USE_COLOR
static const char *const level_colors[] = { /* color codes for messages */
  McuShell_ANSI_COLOR_TEXT_BRIGHT_BLUE,     /* trace */
  McuShell_ANSI_COLOR_TEXT_BRIGHT_GREEN,    /* debug */
  McuShell_ANSI_COLOR_TEXT_BRIGHT_CYAN,     /* info */
  McuShell_ANSI_COLOR_TEXT_BRIGHT_YELLOW,   /* warn */
  McuShell_ANSI_COLOR_TEXT_BRIGHT_RED,      /* error */
  McuShell_ANSI_COLOR_TEXT_BRIGHT_MAGENTA   /* fatal */
};
#endif

#if McuLog_CONFIG_USE_MUTEX
static void lock(void)   {
  if (McuLog_ConfigData.lock!=NULL) {
    McuLog_ConfigData.lock(McuLog_ConfigData.udata, true);
  }
}
#endif

#if McuLog_CONFIG_USE_MUTEX
static void unlock(void) {
  if (McuLog_ConfigData.lock!=NULL) {
    McuLog_ConfigData.lock(McuLog_ConfigData.udata, false);
  }
}
#endif

void McuLog_set_console(McuShell_ConstStdIOType *io, uint8_t index) {
  assert(index<McuLog_CONFIG_NOF_CONSOLE_LOGGER);
  McuLog_ConfigData.consoleIo[index] = io;
}

#if McuLog_CONFIG_USE_MUTEX
void McuLog_set_udata(void *udata) {
  McuLog_ConfigData.udata = udata;
}
#endif

#if McuLog_CONFIG_USE_MUTEX
void McuLog_set_lock(log_LockFn fn) {
  McuLog_ConfigData.lock = fn;
}
#endif

#if McuLog_CONFIG_USE_FILE
void McuLog_set_fp(McuFatFS_FIL *fp) {
  McuLog_ConfigData.fp = fp;
}
#endif

#if McuLog_CONFIG_USE_FILE
int McuLog_open_logfile(const unsigned char *logFileName) {
  McuFatFS_FRESULT fres;

  fres = f_open(&McuLog_ConfigData.logFile, (const TCHAR*)logFileName, FA_WRITE|FA_OPEN_APPEND);
  if (fres != FR_OK) {
    McuLog_set_fp(NULL);
    return -1; /* failed */
  }
  McuLog_set_fp(&McuLog_ConfigData.logFile);
  return 0; /* success */
}
#endif

#if McuLog_CONFIG_USE_FILE
int McuLog_close_logfile(void) {
  McuFatFS_FRESULT fres;

  fres = f_close(McuLog_ConfigData.fp);
  McuLog_set_fp(NULL);
  if (fres != FR_OK) {
    return -1; /* failed */
  }
  return 0; /* success */
}
#endif

void McuLog_set_level(McuLog_Levels_e level) {
  McuLog_ConfigData.level = level;
}

void McuLog_set_quiet(bool enable) {
  McuLog_ConfigData.quiet = enable;
}

#if McuLog_CONFIG_USE_COLOR
void McuLog_set_color(bool enable) {
  McuLog_ConfigData.color = enable;
}
#endif

static void OutputCharFctConsole(void *p, char ch) {
  McuShell_StdIO_OutErr_FctType io = (McuShell_StdIO_OutErr_FctType)p;

#if McuLog_CONFIG_USE_RTT_CONSOLE
  if (io==McuRTT_StdIOSendChar) { /* using RTT: check first if we are able to send */
    unsigned int rttUpSize = SEGGER_RTT_GetUpBufferFreeSize(0);
    if (rttUpSize<1) { /* there is NOT enough space available in the RTT up buffer */
      return; /* do not send :-( */
    }
  }
#endif
  io(ch);
}

#if McuLog_CONFIG_USE_FILE
static void OutputCharFctFile(void *p, char ch) {
  McuFatFS_FIL *fp = (McuFatFS_FIL*)p;

  f_putc(ch, fp);
}
#endif

#if McuLog_CONFIG_USE_RTT_DATA_LOGGER
void McuLog_set_rtt_logger(bool enable) {
  McuLog_ConfigData.rttDataLogger = enable;
}
#endif

#if McuLog_CONFIG_USE_RTT_DATA_LOGGER
static void OutputCharRttLoggerFct(void *p, char ch) {
  McuRTT_Write(McuLog_RTT_DATA_LOGGER_CHANNEL, (const char*)&ch, sizeof(char));
}
#endif

static void OutString(const unsigned char *str, void (*outchar)(void *,char), void *p) {
  while(*str!='\0') {
    outchar(p, *str);
    str++;
  }
}

static void LogHeader(DATEREC *date, TIMEREC *time, McuLog_Levels_e level, bool supportColor, const char *file, int line, void (*outchar)(void *,char), void *param) {
  unsigned char buf[32];

#if McuLog_CONFIG_LOG_TIMESTAMP_DATE || McuLog_CONFIG_LOG_TIMESTAMP_TIME
  /* date/time */
  buf[0] = '\0';
#if McuLog_CONFIG_LOG_TIMESTAMP_DATE
  McuTimeDate_AddDateString((unsigned char*)buf, sizeof(buf), date, (unsigned char*)McuTimeDate_CONFIG_DEFAULT_DATE_FORMAT_STR);
  McuUtility_chcat(buf, sizeof(buf), ' ');
#endif
#if McuLog_CONFIG_LOG_TIMESTAMP_TIME
  McuTimeDate_AddTimeString((unsigned char*)buf, sizeof(buf), time, (unsigned char*)McuTimeDate_CONFIG_DEFAULT_TIME_FORMAT_STR);
  McuUtility_chcat(buf, sizeof(buf), ' ');
#endif
  OutString(buf, outchar, param);
#endif

  /* level */
  buf[0] = '\0';
#if McuLog_CONFIG_USE_COLOR
  if (supportColor && McuLog_ConfigData.color) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)level_colors[level]);
  }
#endif
  McuUtility_strcatPad(buf, sizeof(buf), (unsigned char*)level_names[level], ' ', sizeof("DEBUG ")-1);
#if McuLog_CONFIG_USE_COLOR
  if (supportColor && McuLog_ConfigData.color) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)McuShell_ANSI_CONTROL_RESET);
  }
#endif
  OutString(buf, outchar, param);

#if McuLog_CONFIG_LOG_STRIP_FILENAME_PATH
  /* file name */
  const unsigned char *p;

  p = (const unsigned char*)file;
  if (*p=='.') { /* relative */
    while(*p==' ' || *p=='.') {
      p++; /* skip leading spaces or dots */
    }
  } else { /* scan for separator */
    size_t pos;
    pos = McuUtility_strlen(file)-1; /* end of the string */
    while(pos>1 && !(file[pos-1]=='/' || file[pos-1]=='\\')) { /* scan back to find the last separator */
      pos--;
    }
    if (pos==1 && !(file[pos-1]=='/' || file[pos-1]=='\\')) { /* no separator at all? */
      pos = 0; /* no separator, start from the beginning */
    }
    p = (const unsigned char*)&file[pos];
  }
  OutString(p, outchar, param);
#else
  OutString((unsigned char*)file, outchar, param);
#endif

  /* line number */
  buf[0] = '\0';
  McuUtility_chcat(buf, sizeof(buf), ':');
  McuUtility_strcatNum32u(buf,  sizeof(buf), line);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)": ");
  OutString(buf, outchar, param);
}

#if McuLog_CONFIG_USE_PRINTF_STYLE
void McuLog_log(McuLog_Levels_e level, const char *file, int line, const char *fmt, ...) {
#if McuLog_CONFIG_LOG_TIMESTAMP_DATE
  DATEREC date;
  #define DATE_PTR  &date
#else
  #define DATE_PTR  NULL
#endif
#if McuLog_CONFIG_LOG_TIMESTAMP_TIME
  TIMEREC time;
  #define TIME_PTR  &time
#else
  #define TIME_PTR  NULL
#endif
  va_list list;

  if (level < McuLog_ConfigData.level) {
    return;
  }
#if McuLog_CONFIG_USE_MUTEX
  lock(); /* Acquire lock */
#endif
#if McuLog_CONFIG_LOG_TIMESTAMP_DATE || McuLog_CONFIG_LOG_TIMESTAMP_TIME
  (void)McuTimeDate_GetTimeDate(TIME_PTR, DATE_PTR); /* Get current date and time */
#endif
  if (!McuLog_ConfigData.quiet) {
    for(int i=0; i<McuLog_CONFIG_NOF_CONSOLE_LOGGER; i++) {
      if(McuLog_ConfigData.consoleIo[i]!=NULL) { /* log to console */
        LogHeader(DATE_PTR, TIME_PTR, level, true, file, line, OutputCharFctConsole, McuLog_ConfigData.consoleIo[i]->stdErr);
        /* open argument list */
        va_start(list, fmt);
        McuXFormat_xvformat(OutputCharFctConsole, McuLog_ConfigData.consoleIo[i]->stdErr, fmt, list);
        va_end(list);
        OutString((unsigned char *)"\n", OutputCharFctConsole, McuLog_ConfigData.consoleIo[i]->stdErr);
      }
    } /* for */
  }

#if McuLog_CONFIG_USE_RTT_DATA_LOGGER
  /* log to RTT Data Logger */
  if (McuLog_ConfigData.rttDataLogger) {
    LogHeader(DATE_PTR, TIME_PTR, level, false, file, line, OutputCharRttLoggerFct, NULL);
    /* open argument list */
    va_start(list, fmt);
    McuXFormat_xvformat(OutputCharRttLoggerFct, NULL, fmt, list);
    va_end(list);
    OutString((unsigned char *)"\n", OutputCharRttLoggerFct, NULL);
  }
#endif

#if McuLog_CONFIG_USE_FILE
  /* Log to file */
  if (McuLog_ConfigData.fp) {
    LogHeader(DATE_PTR, &time, level, false, file, line, OutputCharFctFile, McuLog_ConfigData.fp);
    /* open argument list */
    va_start(list, fmt);
    McuXFormat_xvformat(OutputCharFctFile, McuLog_ConfigData.fp, fmt, list);
    va_end(list);
    OutString((unsigned char *)"\n", OutputCharFctFile, McuLog_ConfigData.fp);
    f_sync(McuLog_ConfigData.fp);
  }
#endif
#if McuLog_CONFIG_USE_MUTEX
  unlock(); /* Release lock */
#endif
}
#endif

void McuLog_logString(McuLog_Levels_e level, const char *file, int line, const char *str) {
#if McuLog_CONFIG_LOG_TIMESTAMP_DATE
  DATEREC date;
  #define DATE_PTR  &date
#else
  #define DATE_PTR  NULL
#endif
#if McuLog_CONFIG_LOG_TIMESTAMP_TIME
  TIMEREC time;
  #define TIME_PTR  &time
#else
  #define TIME_PTR  NULL
#endif

  if (level < McuLog_ConfigData.level) {
    return;
  }
#if McuLog_CONFIG_USE_MUTEX
  lock(); /* Acquire lock */
#endif
#if McuLog_CONFIG_LOG_TIMESTAMP_DATE || McuLog_CONFIG_LOG_TIMESTAMP_TIME
  (void)McuTimeDate_GetTimeDate(TIME_PTR, DATE_PTR); /* Get current date and time */
#endif
  if (!McuLog_ConfigData.quiet) {
    for(int i=0; i<McuLog_CONFIG_NOF_CONSOLE_LOGGER; i++) {
      if(McuLog_ConfigData.consoleIo[i]!=NULL) { /* log to console */
        LogHeader(DATE_PTR, TIME_PTR, level, true, file, line, OutputCharFctConsole, McuLog_ConfigData.consoleIo[i]->stdErr);
        OutString((unsigned char *)str, OutputCharFctConsole, McuLog_ConfigData.consoleIo[i]->stdErr);
        OutString((unsigned char *)"\n", OutputCharFctConsole, McuLog_ConfigData.consoleIo[i]->stdErr);
      }
    } /* for */
  }

#if McuLog_CONFIG_USE_RTT_DATA_LOGGER
  /* log to RTT Data Logger */
  if (McuLog_ConfigData.rttDataLogger) {
    LogHeader(DATE_PTR, TIME_PTR, level, false, file, line, OutputCharRttLoggerFct, NULL);
    OutString((unsigned char *)str, OutputCharRttLoggerFct, NULL);
    OutString((unsigned char *)"\n", OutputCharRttLoggerFct, NULL);
  }
#endif

#if McuLog_CONFIG_USE_FILE
  /* Log to file */
  if (McuLog_ConfigData.fp) {
    LogHeader(DATE_PTR, &time, level, false, file, line, OutputCharFctFile, McuLog_ConfigData.fp);
    OutString((unsigned char *)str, OutputCharFctFile, McuLog_ConfigData.fp);
    OutString((unsigned char *)"\n", OutputCharFctFile, McuLog_ConfigData.fp);
    f_sync(McuLog_ConfigData.fp);
  }
#endif
#if McuLog_CONFIG_USE_MUTEX
  unlock(); /* Release lock */
#endif
}

#if McuLog_CONFIG_USE_MUTEX
static void LockUnlockCallback(void *data, bool lock) {
  (void)data; /* unused */
  if (lock) {
    (void)xSemaphoreTakeRecursive(McuLog_ConfigData.McuLog_Mutex, portMAX_DELAY);
  } else {
    (void)xSemaphoreGiveRecursive(McuLog_ConfigData.McuLog_Mutex);
  }
}
#endif

#if McuLog_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[8];

  McuShell_SendStatusStr((unsigned char*)"McuLog", (unsigned char*)"Log status\r\n", io->stdOut);
  McuUtility_Num8uToStr(buf, sizeof(buf), McuLog_CONFIG_NOF_CONSOLE_LOGGER);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  console", buf, io->stdOut);
#if McuLog_CONFIG_USE_FILE
  McuShell_SendStatusStr((unsigned char*)"  file", McuLog_ConfigData.fp!=NULL?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
#endif
#if McuLog_CONFIG_USE_RTT_DATA_LOGGER
  McuShell_SendStatusStr((unsigned char*)"  rttlogger", McuLog_ConfigData.rttDataLogger?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
#endif
#if McuLog_CONFIG_USE_MUTEX
  McuShell_SendStatusStr((unsigned char*)"  lock", McuLog_ConfigData.lock!=NULL?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
#endif
  McuShell_SendStatusStr((unsigned char*)"  level", (unsigned char*)level_names[McuLog_ConfigData.level], io->stdOut);
  McuShell_SendStr((unsigned char*)" (", io->stdOut);
  McuShell_SendNum8u(McuLog_ConfigData.level, io->stdOut);
  McuShell_SendStr((unsigned char*)"), logging for this level and higher\r\n", io->stdOut);
#if McuLog_CONFIG_USE_COLOR
  McuShell_SendStatusStr((unsigned char*)"  color", McuLog_ConfigData.color?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
#endif
  return ERR_OK;
}
#endif /* McuLog_CONFIG_PARSE_COMMAND_ENABLED */

#if McuLog_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"McuLog", (unsigned char*)"Group of McuLog commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  level <level>", (unsigned char*)"Set log level, 0 (TRACE), 1 (DEBUG), 2 (INFO), 3 (WARN), 4 (ERROR), 5 (FATAL)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  quiet <on|off>", (unsigned char*)"Set quiet mode for console\r\n", io->stdOut);
#if McuLog_CONFIG_USE_COLOR
  McuShell_SendHelpStr((unsigned char*)"  color <on|off>", (unsigned char*)"Set color mode\r\n", io->stdOut);
#endif
#if McuLog_CONFIG_USE_RTT_DATA_LOGGER
  McuShell_SendHelpStr((unsigned char*)"  rttlogger <on|off>", (unsigned char*)"Set rtt data logger mode\r\n", io->stdOut);
#endif
  return ERR_OK;
}
#endif /* McuLog_CONFIG_PARSE_COMMAND_ENABLED */

#if McuLog_CONFIG_PARSE_COMMAND_ENABLED
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
#if McuLog_CONFIG_USE_COLOR
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
    if (McuUtility_ScanDecimal8uNumber(&p, &level)==ERR_OK && level<=McuLog_FATAL) {
      McuLog_set_level(level);
    }
  }
  return res;
}
#endif /* McuLog_CONFIG_PARSE_COMMAND_ENABLED */


#if McuLog_CONFIG_USE_RTT_DATA_LOGGER
static char McuLog_RttUpBuffer[McuLog_CONFIG_RTT_DATA_LOGGER_BUFFER_SIZE];
#endif

void McuLog_Init(void) {
#if McuLog_CONFIG_USE_MUTEX
  McuLog_ConfigData.McuLog_Mutex = xSemaphoreCreateRecursiveMutex();
  if (McuLog_ConfigData.McuLog_Mutex==NULL) { /* semaphore creation failed */
    for(;;) {} /* error, not enough memory? */
  }
  vQueueAddToRegistry(McuLog_ConfigData.McuLog_Mutex, "McuLog_Mutex");
  McuLog_set_lock(LockUnlockCallback);
#endif
#if McuLog_CONFIG_USE_COLOR
  McuLog_set_color(true);
#endif
#if McuLog_CONFIG_USE_RTT_DATA_LOGGER
  McuLog_set_rtt_logger(true);
#endif
  McuLog_ConfigData.consoleIo[0] = McuShell_GetStdio(); /* default */
  McuLog_set_level(McuLog_CONFIG_DEFAULT_LEVEL); /* default level */
#if McuLog_CONFIG_USE_RTT_DATA_LOGGER
  #if McuLib_CONFIG_SDK_USE_FREERTOS && configUSE_SEGGER_SYSTEM_VIEWER_HOOKS && McuSystemView_CONFIG_RTT_CHANNEL==McuLog_RTT_DATA_LOGGER_CHANNEL
    #error "Both RTT Logger and SystemViewer are using the same channel! Change McuSystemView_CONFIG_RTT_CHANNEL to a different value."
  #endif
  SEGGER_RTT_ConfigUpBuffer(McuLog_RTT_DATA_LOGGER_CHANNEL, "Logger", &McuLog_RttUpBuffer[0], sizeof(McuLog_RttUpBuffer), McuLog_CONFIG_RTT_DATA_LOGGER_CHANNEL_MODE);
#endif
}

void McuLog_Deinit(void) {
#if McuLog_CONFIG_USE_MUTEX
  vSemaphoreDelete(McuLog_ConfigData.McuLog_Mutex);
  McuLog_ConfigData.McuLog_Mutex = NULL;
  McuLog_set_lock(NULL);
#endif
}

#endif /* McuLog_CONFIG_IS_ENABLED */


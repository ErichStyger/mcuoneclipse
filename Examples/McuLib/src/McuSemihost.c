/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuSemihost.h"
#include "McuUtility.h"
#include "McuTimeDate.h"
#include "McuXFormat.h"
#include "McuLib.h"
#include "McuShell.h"
#include <stdio.h>

#if McuSemihost_CONFIG_IS_ENABLED
/*
 * ARM Semihosting operations, see https://developer.arm.com/documentation/dui0471/g/Semihosting
 * See https://github.com/cnoviello/mastering-stm32/blob/master/nucleo-f411RE/system/include/arm/semihosting.h
 * See https://wiki.segger.com/Semihosting
 * "SEGGER J-Link GDB Server V7.86c" has been used.
 */
typedef enum McuSemihost_Op_e {
  McuSemihost_Op_SYS_OPEN         = 0x01, /* open a file */
  McuSemihost_Op_SYS_CLOSE        = 0x02, /* close a file */
  McuSemihost_Op_SYS_WRITEC       = 0x03, /* write a character byte, pointed to by R1: not implemented by PEMICRO */
  McuSemihost_Op_SYS_WRITE0       = 0x04, /* writes a null terminated string. R1 points to the first byte, not supported by PEMICRO */
  McuSemihost_Op_SYS_WRITE        = 0x05, /* write data to a file */
  McuSemihost_Op_SYS_READ         = 0x06, /* read data from a file: not implemented reading from stdin by PEMICRO */
  McuSemihost_Op_SYS_READC        = 0x07, /* read a character from stdin: not implemented by PEMICRO */
  McuSemihost_Op_SYS_ISERROR      = 0x08, /* Determines whether the return code from another semihosting call is an error status or not.  */
  McuSemihost_Op_SYS_ISTTY        = 0x09, /* check if it is a TTY */
  McuSemihost_Op_SYS_SEEK         = 0x0A, /* move current file position */

  McuSemihost_Op_SYS_FLEN         = 0x0C, /* tell the file length */
#if McuSemihost_CONFIG_HAS_SYS_TMPNAME
  McuSemihost_Op_SYS_TMPNAME      = 0x0D, /* get a temporary file handle. Not implemented by SEGGER for security reasons. */
#endif
#if McuSemihost_CONFIG_HAS_SYS_REMOVE
  McuSemihost_Op_SYS_REMOVE       = 0x0E, /* remove a file. Not implemented by SEGGER for security reasons. */
#endif
#if McuSemihost_CONFIG_HAS_SYS_RENAME
  McuSemihost_Op_SYS_RENAME       = 0x0F, /* rename a file. Not implemented by SEGGER for security reasons. */
#endif
  McuSemihost_Op_SYS_CLOCK        = 0x10, /* returns the number of centi-seconds since execution started */
  McuSemihost_Op_SYS_TIME         = 0x11, /* time in seconds since Jan 1st 1970 */
#if !(McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_SEGGER)
  McuSemihost_Op_SYS_SYSTEM       = 0x12, /* Passes a command to the host command-line interpreter. Not implemented by SEGGER for security reasons. */
#endif
  McuSemihost_Op_SYS_ERRNO        = 0x13, /* get the current error number*/

  McuSemihost_Op_SYS_GET_CMDLINE  = 0x15, /* Returns the command line used for the call to the executable */
  McuSemihost_Op_SYS_HEAPINFO     = 0x16, /* Returns the system stack and heap parameters. */
  McuSemihost_Op_SYS_ENTER_SVC    = 0x17, /* Sets the processor to Supervisor mode and disables all interrupts */
  McuSemihost_Op_SYS_EXCEPTION    = 0x18, /* Exit application */

  McuSemihost_Op_SYS_ELLAPSED     = 0x30, /* Returns the number of elapsed target ticks since execution started. */
  McuSemihost_Op_SYS_TICKFREQ     = 0x31, /* Returns the tick frequency. */

#if McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_SEGGER
  McuSemihost_Op_SYS_IS_CONNECTED = 0x00, /* check if debugger is connected: note that this is not implemented with GDB server */
#endif
#if 0 && McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_SEGGER /* documented by SEGGER, but not implemented? */
  McuSemihost_Op_SYS_WRITEF       = 0x40, /* write a printf-style string, but formatting is on the host: seems not be implemented with GDB server */
#endif
} McuSemihost_Op_e;

#define McuSemihost_STDIN           0 /*!< handle for standard input */
#define McuSemihost_STDOUT          1 /*!< handle for standard output */
#define McuSemihost_STDERR          2 /*!< handle for standard error */

#if McuSemihost_CONFIG_INIT_STDIO_HANDLES
  static int McuSemihost_tty_handles[3]; /* stdin, stdout and stderr */
#endif

bool McuSemihost_StdIOKeyPressed(void) {
  return false; /* \todo */
}

void McuSemihost_StdIOReadChar(uint8_t *ch) {
  int res;

  res = McuSemihost_SysReadC();
  if (res==-1) { /* no character present */
    *ch = '\0';
  } else {
    *ch = (uint8_t)res; /* return character */
  }
}

#if McuSemihost_CONFIG_USE_BUFFERED_IO
  static unsigned char io_buf[McuSemihost_CONFIG_BUFFER_IO_SIZE] = "";
  static size_t io_bufIdx = 0; /* index into io_buf */
#endif
uint8_t McuSemihost_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */

/* default standard I/O struct */
McuShell_ConstStdIOType McuSemihost_stdio = {
    (McuShell_StdIO_In_FctType)McuSemihost_StdIOReadChar, /* stdin */
    (McuShell_StdIO_OutErr_FctType)McuSemihost_StdIOSendChar, /* stdout */
    (McuShell_StdIO_OutErr_FctType)McuSemihost_StdIOSendChar, /* stderr */
    McuSemihost_StdIOKeyPressed /* if input is not empty */
  };

void McuSemihost_StdIOFlush(void) {
  io_buf[io_bufIdx] = '\0';
#if McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_PYOCD
  McuSemihost_SysFileWrite(McuSemihost_STDOUT+1, io_buf, io_bufIdx); /* for pyOCD, need to write to handle 2???? */
#else
  McuSemihost_WriteString0(io_buf);
#endif
  io_bufIdx = 0;
}

void McuSemihost_StdIOSendChar(uint8_t ch) {
#if McuSemihost_CONFIG_USE_BUFFERED_IO
  io_buf[io_bufIdx++] = ch;
  if ( io_bufIdx==sizeof(io_buf)-1 /* buffer full */
    #if !McuSemihost_CONFIG_BUFFER_IO_FLUSH
      || ch=='\n' /* newline: flush buffer */
    #endif
     )
  {
    McuSemihost_StdIOFlush();
  }
#else
  (void)McuSemihost_WriteChar(ch);
#endif
}

McuShell_ConstStdIOTypePtr McuSemihost_GetStdio(void) {
  return &McuSemihost_stdio;
}

int McuSemihost_WriteChar(char ch) {
  McuSemihost_StdIOSendChar(ch);
  return 0; /* success */
}

static inline int __attribute__ ((always_inline)) McuSemihost_HostRequest(int reason, void *arg) {
  int value;
  __asm volatile (
      "mov r0, %[rsn] \n" /* place semihost operation code into R0 */
      "mov r1, %[arg] \n" /* R1 points to the argument array */
    #if 0 && McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_SEGGER
      "mov r2, #0     \n" /* J-Link needs R2 initialized too? */
    #endif
      "bkpt 0xAB      \n" /* call debugger */
      "mov %[val], r0 \n" /* debugger has stored result code in R0 */

      : [val] "=r" (value) /* outputs */
      : [rsn] "r" (reason), [arg] "r" (arg) /* inputs */
      : "r0", "r1", "r2", "r3", "ip", "lr", "memory", "cc" /* clobber */
  );
  return value; /* return result code, stored in R0 */
}

#if McuSemihost_CONFIG_DEBUG_CONNECTION == McuSemihost_DEBUG_CONNECTION_SEGGER
/*!
 * \brief Checks if the debugger is connected. Only supported for SEGGER
 * \return true if a J-Link is connected
 */
int McuSemihost_SeggerIsConnected(void) {
  /* note: SEGGER documents the op code 0x0 (SysIsConnected), but with V7.68 it reports that it is not supported?
   * WARNING: Unsupported semihosting functionality (R0 = 0x00).
   */
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_IS_CONNECTED, NULL)==1; /* result is 1 if connected */
}
#endif

int McuSemihost_SysHostTime(void) {
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_TIME, NULL);
}

int McuSemihost_SysHostClock(void) {
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_CLOCK, NULL);
}

int McuSemihost_SysFileOpen(const unsigned char *filename, int mode) {
  int32_t param[3];

  param[0] = (int32_t)filename;
  param[1] = mode;
  param[2] = McuUtility_strlen((char*)filename);
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_OPEN, &param[0]);
}

int McuSemihost_SysFileClose(int fh) {
  int32_t param;

  param = fh;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_CLOSE, &param);
}

int McuSemihost_SysFileRead(int fh, unsigned char *data, size_t nofBytes) {
  int32_t param[3];

  param[0] = fh;
  param[1] = (int32_t)data;
  param[2] = nofBytes;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_READ, &param[0]);
}

int McuSemihost_SysFileWrite(int fh, const unsigned char *data, size_t nofBytes) {
  int32_t param[3];

  param[0] = fh;
  param[1] = (int32_t)data;
  param[2] = nofBytes;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_WRITE, &param[0]);
}

#if McuSemihost_CONFIG_HAS_SYS_REMOVE
/* J-Link denies this with
 * ERROR: Semi hosting error: SYS_REMOVE: Target tries to remove file. Declined for security reasons.
 * PyOCD reports:
 *  0039753 W Semihost: unimplemented request pc=3120 r0=e r1=2000fef4 [semihost]
 */
int McuSemihost_SysFileRemove(const unsigned char *filePath) {
  int32_t param[2];

  param[0] = (int32_t)filePath;
  param[1] = McuUtility_strlen((char*)filePath);
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_REMOVE, &param[0]);
}
#endif

#if McuSemihost_CONFIG_HAS_SYS_RENAME
/* J-Link denies this with
 *  ERROR: Semi hosting error: SYS_RENAME: Target tries to rename file. Declined for security reasons.
 * PyOCD reports:
 *  0039579 W Semihost: unimplemented request pc=316a r0=f r1=2000feec [semihost]
 */
int McuSemihost_SysFileRename(const unsigned char *filePath, const unsigned char *fileNewPath) {
  int32_t param[4];

  param[0] = (int32_t)filePath;
  param[1] = McuUtility_strlen((char*)filePath);
  param[2] = (int32_t)fileNewPath;
  param[3] = McuUtility_strlen((char*)fileNewPath);
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_RENAME, &param[0]);
}
#endif

int McuSemihost_SysFileLen(int fh) {
  int32_t param;

  param = fh;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_FLEN, &param);
}

int McuSemihost_SysFileSeek(int fh, int pos) {
  int32_t param[2];

  param[0] = fh;
  param[1] = pos;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_SEEK, &param[0]);
}

#if McuSemihost_CONFIG_HAS_SYS_TMPNAME
int McuSemihost_SysTmpName(uint8_t fileID, unsigned char *buffer, size_t bufSize) {
  int32_t param[3];

  param[0] = (int32_t)buffer;
  param[1] = fileID;
  param[2] = bufSize;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_TMPNAME, &param[0]);
}
#endif

int McuSemihost_SysReadC(void) {
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_READC, NULL);
}

int McuSemihost_SysWriteC(char ch) {
  int32_t param = ch;
  (void)McuSemihost_HostRequest(McuSemihost_Op_SYS_WRITEC, &param); /* does not return valid value, R0 is corrupted */
  return 0; /* success */
}

int McuSemihost_SysIsTTY(int fh) {
  int32_t param = fh;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_ISTTY, &param);
}

int McuSemihost_SysIsError(int32_t errorCode) {
  int32_t param = errorCode;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_ISERROR, &param); /* LinkServer fails? */
}

int McuSemihost_SysErrNo(void) {
  int32_t param = 0;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_ERRNO, &param);
}

int McuSemihost_SysGetCmdLine(unsigned char *cmd, size_t cmdSize) {
  int32_t param[2];

  param[0] = (int32_t)cmd;
  param[1] = cmdSize;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_GET_CMDLINE, &param[0]);
}

int McuSemihost_SysHeapInfo(McuSemihost_HeapInfo_t *heapInfo) {
  int32_t param;

  param = (int32_t)heapInfo;
  (void)McuSemihost_HostRequest(McuSemihost_Op_SYS_HEAPINFO, &param);
  /* https://github.com/ARM-software/abi-aa/blob/main/semihosting/semihosting.rst#sys-heapinfo-0x16
   * On exit, the PARAMETER REGISTER is unchanged and the data block has been updated. */
  return 0; /* success: caller would have to inspect the heapinfo values. */
}

int McuSemihost_SysEnterSVC(void) {
  int32_t param = 0; /* not used */
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_ENTER_SVC, &param);
}

int McuSemihost_SysException(McuSemihost_Exception_e exception) {
  int32_t param = exception; /* not used */
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_EXCEPTION, &param);
}

#if McuSemihost_CONFIG_DEBUG_CONNECTION!=McuSemihost_DEBUG_CONNECTION_SEGGER
/* SEGGER: ERROR: Semi hosting error: SYS_TICKFREQ is not supported by GDB Server. */
int McuSemihost_SysTickFreq(void) {
  int32_t param = 0; /* must be zero */
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_TICKFREQ, &param);
}
#endif

int McuSemihost_WriteString(const unsigned char *str) {
  McuShell_SendStr(str, McuSemihost_stdio.stdOut); /* buffer it, then write to a file during flush */
  return ERR_OK;
}

int McuSemihost_WriteString0(const unsigned char *str) {
  /* R1 to point to the first byte of the string */
#if McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_PEMICRO /* WRITE0 does nothing with PEMCIRO? */
  return McuSemihost_SysFileWrite(McuSemihost_STDOUT, str, strlen((char*)str));
#elif McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_PYOCD /* PyOCD only supports WRITEC */
  McuShell_SendStr(str, McuSemihost_stdio.stdOut); /* buffer it, then write to a file during flush */
  return ERR_OK;
#else
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_WRITE0, (void*)str);
#endif
}

#if McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_SEGGER
#if 0 /* not implemented by SEGGER */
/*!
 * \brief Write a printf-style string, with formatting done on the host
 * \param format Format string
 * \param arg Argument list
 * \return Number of bytes printed (>=0), negative for error
 */
int McuSemihost_WriteF(const unsigned char *format, va_list *arg) {
  int32_t param[2];

  param[0] = (int32_t)format;
  param[1] = (int32_t)arg;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_WRITEF, &param[0]);
}
#endif
#endif

#if 0 && McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_SEGGER /* SEGGER has not implemented this */
int McuSemihost_WriteFormatted(const unsigned char *format, ...) {
  va_list va;
  int res;

  va_start(va, format);
  res = McuSemihost_WriteF(format, &va);
  va_end(va);
  return res;
}
#endif

unsigned McuSemihost_printf(const char *fmt, ...) {
  va_list args;
  unsigned int count = 0;

  va_start(args,fmt);
  count = McuXFormat_xvformat(McuShell_printfPutChar, (void*)McuSemihost_GetStdio()->stdOut, fmt, args);
  va_end(args);
  return count;
}

uint8_t McuSemihost_GetTimeDateFromHost(TIMEREC *time, DATEREC *date, int offsetHour) {
  int secs = McuSemihost_SysHostTime(); /* using SYS_TIME */
  if (secs<=0) {
    return ERR_FAILED;
  }
  McuTimeDate_UnixSecondsToTimeDateCustom(secs, offsetHour, time, date, 1970);
  return ERR_OK;
}

/*------------------------------------------------------------------------------*/
static int TestFileOperations(void) {
  int fh;
  char buf[24];
  unsigned char data[32];
  const unsigned char *testFileName = (const unsigned char*)"c:\\tmp\\semihosting.txt";
  int res = 0; /* 0: ok, -1: failed */

  McuSemihost_WriteString((unsigned char*)"SYS_OPEN: Open and create file ");
  McuSemihost_WriteString((unsigned char*)testFileName);
  McuSemihost_WriteString((unsigned char*)"\n");
  fh = McuSemihost_SysFileOpen(testFileName, SYS_FILE_MODE_WRITEREADBINARY);
  if (fh == -1) {
    McuSemihost_WriteString((unsigned char*)"SYS_OPEN: failed\n");
    res = -1; /* failed */
  } else {
    if (McuSemihost_SysErrNo()) { /* SYS_OPEN was successful, so should not report an error here */
      McuSemihost_WriteString((unsigned char*)"Failed SYS_ERRNO after file operation\n");
      res = -1; /* failed */
    }
    if (McuSemihost_SysIsTTY(fh)) {
      McuSemihost_WriteString((unsigned char*)"Failed SYS_ISTTY for a file\n");
      res = -1; /* failed */
    }
    McuSemihost_WriteString((unsigned char*)"SYS_OPEN: OK\n");
    if (McuSemihost_SysIsTTY(fh)==0) {
      McuSemihost_WriteString((unsigned char*)"SYS_ISTTY: OK\n");
    } else {
      McuSemihost_WriteString((unsigned char*)"SYS_ISTTY: failed\n");
      res = -1; /* failed */
    }
    if (McuSemihost_SysFileClose(fh)==0) {
      McuSemihost_WriteString((unsigned char*)"SYS_CLOSE: OK\n");
    } else {
      McuSemihost_WriteString((unsigned char*)"SYS_CLOSE: Failed\n");
      res = -1; /* failed */
    }
  }

  /* writing to file */
  McuSemihost_WriteString((unsigned char*)"SYS_WRITE: Write to file ");
  McuSemihost_WriteString((unsigned char*)testFileName);
  McuSemihost_WriteString((unsigned char*)"\n");
  fh = McuSemihost_SysFileOpen(testFileName, SYS_FILE_MODE_WRITEREADBINARY);
  if (fh == -1) {
    McuSemihost_WriteString((unsigned char*)"SYS_OPEN: failed\n");
  } else {
    const unsigned char *msg = (const unsigned char*)"test file write 0123456789ABCDEF Hello World!";
    if (McuSemihost_SysFileWrite(fh, msg, strlen((char*)msg)) != 0) {
      McuSemihost_WriteString((unsigned char*)"SYS_WRITE: failed\n");
      res = -1; /* failed */
    } else {
      McuSemihost_WriteString((unsigned char*)"SYS_WRITE OK\n");
    }
    McuSemihost_SysFileClose(fh);
  }

  /* read from file */
  McuSemihost_WriteString((unsigned char*)"SYS_READ: Read from file ");
  McuSemihost_WriteString((unsigned char*)testFileName);
  McuSemihost_WriteString((unsigned char*)"\n");
  fh = McuSemihost_SysFileOpen(testFileName, SYS_FILE_MODE_READ);
  if (fh == -1) {
    McuSemihost_WriteString((unsigned char*)"SYS_OPEN failed\n");
    res = -1; /* failed */
  } else {
    int r;

    memset(data, 0, sizeof(data)); /* initialize data */
    r = McuSemihost_SysFileRead(fh, data, sizeof(data));
    if (r==0) { /* success */
      unsigned char b[8];
      McuSemihost_WriteString((unsigned char*)"SYS_READ: OK, data:\n");
      for(int i=0; i<sizeof(data); i++) {
        McuUtility_strcpy(b, sizeof(b), (unsigned char*)"0x");
        McuUtility_strcatNum8Hex(b, sizeof(b), data[i]);
        McuUtility_chcat(b, sizeof(b), ' ');
        McuUtility_chcat(b, sizeof(b), data[i]);
        McuUtility_chcat(b, sizeof(b), ' ');
        McuSemihost_WriteString(b);
      }
      McuSemihost_WriteString((unsigned char*)"\n");
    } else if (r < 0) {
      McuSemihost_WriteString((unsigned char*)"SYS_READ failed\n");
      res = -1; /* failed */
    } else if (r == sizeof(buf)) {
      McuSemihost_WriteString((unsigned char*)"SYS_READ: failed, reading EOF\n");
      res = -1; /* failed */
    } else { /* unknown return code? */
      McuSemihost_printf("SYS_READ: failed with return code %d\n");
      res = -1; /* failed */
    }
    McuSemihost_SysFileClose(fh);
  }

  /* seek position in file, length of a file */
  McuSemihost_WriteString((unsigned char*)"SYS_FLEN: Size of file ");
  McuSemihost_WriteString((unsigned char*)testFileName);
  McuSemihost_WriteString((unsigned char*)"\n");
  fh = McuSemihost_SysFileOpen(testFileName, SYS_FILE_MODE_READ);
  if (fh == -1) {
    McuSemihost_WriteString((unsigned char*)"SYS_OPEN: failed\n");
    res = -1; /* failed */
  } else {
    int r;

    r = McuSemihost_SysFileSeek(fh, 6); /* go to pos 6 or enlarge file to 6 bytes */
    if (r != 0) {
      McuSemihost_WriteString((unsigned char*)"SYS_SEEK failed\n");
      res = -1; /* failed */
    } else {
      McuSemihost_WriteString((unsigned char*)"SYS_SEEK: OK\n");
    }
    /* file length */
    r = McuSemihost_SysFileLen(fh);
    if (r >= 0) {
      McuSemihost_printf("SYS_FLEN: file size: %d\n", r);
    } else {
      McuSemihost_WriteString((unsigned char*)"SYS_FLEN failed\n");
      res = -1; /* failed */
    }
    McuSemihost_SysFileClose(fh);
  }

#if McuSemihost_CONFIG_HAS_SYS_RENAME
  {
    const unsigned char *newFileName = (const unsigned char*)"c:\\tmp\\copy.txt";
    /* renaming a file */
    McuSemihost_WriteString((unsigned char*)"SYS_RENAME: rename file ");
    McuSemihost_WriteString((unsigned char*)testFileName);
    McuSemihost_WriteString((unsigned char*)" to ");
    McuSemihost_WriteString((unsigned char*)newFileName);
    McuSemihost_WriteString((unsigned char*)"\n");
    if (McuSemihost_SysFileRename(testFileName, newFileName) != 0) {
      McuSemihost_WriteString((unsigned char*)"SYS_RENAME failed\n");
    } else {
      McuSemihost_WriteString((unsigned char*)"SYS_RENAME OK\n");
    }
  }
#endif

#if McuSemihost_CONFIG_HAS_SYS_REMOVE
  {
    const unsigned char *newFileName = (const unsigned char*)"c:\\tmp\\testremove.txt";
    /* removing a file */
    McuSemihost_WriteString((unsigned char*)"SYS_REMOVE: remove file ");
    McuSemihost_WriteString((unsigned char*)newFileName);
    McuSemihost_WriteString((unsigned char*)"\n");
    fh = McuSemihost_SysFileOpen(newFileName, SYS_FILE_MODE_WRITEREADBINARY); /* create file, if it does not exist */
    if (fh == -1) {
      McuSemihost_WriteString((unsigned char*)"SYS_OPEN: failed\n");
      res = -1; /* failed */
    } else {
      if (McuSemihost_SysFileClose(fh)!=0) { /* close the file we have open above */
        McuSemihost_WriteString((unsigned char*)"failed closing file\n");
        res = -1; /* failed */
      }
      if (McuSemihost_SysFileRemove(newFileName) != 0) {
        McuSemihost_WriteString((unsigned char*)"SYS_REMOVE failed\n");
      } else {
        McuSemihost_WriteString((unsigned char*)"SYS_REMOVE OK\n");
      }
    }
  }
#endif

#if McuSemihost_CONFIG_INIT_STDIO_HANDLES
  /* writing to stdout */
  McuSemihost_WriteString((unsigned char*)"Writing to stdout:\n");
  const unsigned char *testString = (const unsigned char*)"this is a test\n";
  if (McuSemihost_SysFileWrite(McuSemihost_tty_handles[McuSemihost_STDOUT], testString, McuUtility_strlen((char*)testString))!=0) {
    McuSemihost_WriteString((unsigned char*)"Failed writing to stdout!\n");
    res = -1;
  }

  /* writing to stderr */
  McuSemihost_WriteString((unsigned char*)"Writing to stderr:\n");
  if (McuSemihost_SysFileWrite(McuSemihost_tty_handles[McuSemihost_STDERR], testString, McuUtility_strlen((char*)testString))!=0) {
    McuSemihost_WriteString((unsigned char*)"Failed writing to stderr!\n");
    res = -1;
  }
  /* reading from stdin */
#if McuSemihost_CONFIG_DEBUG_CONNECTION!=McuSemihost_DEBUG_CONNECTION_PEMICRO
  McuSemihost_WriteString((unsigned char*)"Reading from stdin: enter 3 character\n");
  if (McuSemihost_SysFileRead(McuSemihost_tty_handles[McuSemihost_STDIN], data, 3)!=0) {
    McuSemihost_WriteString((unsigned char*)"Failed reading from stdin!\n");
    res = -1;
  } else {
    McuSemihost_WriteString((unsigned char*)"you entered: ");
    McuSemihost_WriteChar(data[0]);
    McuSemihost_WriteChar(data[1]);
    McuSemihost_WriteChar(data[2]);
    McuSemihost_WriteChar('\n');
  }
#else
  McuSemihost_WriteString((unsigned char*)"Reading from stdin: not implemented by PEMICRO\n");
#endif

#endif

#if McuSemihost_CONFIG_HAS_SYS_TMPNAME
  {
    unsigned char buffer[64];

    res = McuSemihost_SysTmpName(0, buffer, sizeof(buffer)); /* note: Ozone declines this operation for security reasons */
  }
#endif
  return res;
}

static int ConsoleInputOutput(void) {
  /* test of console input and output */
  int res = 0;

#if McuSemihost_CONFIG_INIT_STDIO_HANDLES
  /* Note:
   * J-Link returns -256 for all handles, but 0, 1 and 2 are used
   * Linkserver returns 0, 1 and 2
   * PyPCD returns 1, 2, and 3 and expects them
   */
  const int expectedHandles[3] = {
    #if McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_PYOCD
      1, 2, 3
    #else
      0, 1, 2
    #endif
  };
  if (McuSemihost_tty_handles[McuSemihost_STDIN]!=expectedHandles[McuSemihost_STDIN]) {
    McuSemihost_printf("Expecting %d for stdin handle, but is %d?\n", McuSemihost_STDIN, McuSemihost_tty_handles[McuSemihost_STDIN]);
    res = -1; /* failed */
  }
  if (McuSemihost_tty_handles[McuSemihost_STDOUT]!=expectedHandles[McuSemihost_STDOUT]) {
    McuSemihost_printf("Expecting %d for stdout handle, but is %d?\n", McuSemihost_STDOUT, McuSemihost_tty_handles[McuSemihost_STDOUT]);
    res = -1; /* failed */
  }
  if (McuSemihost_tty_handles[McuSemihost_STDERR]!=expectedHandles[McuSemihost_STDERR]) {
    McuSemihost_printf("Expecting %d for stderr handle, but is %d?\n", McuSemihost_STDERR, McuSemihost_tty_handles[McuSemihost_STDERR]);
    res = -1; /* failed */
  }
  for(int i=0; i<sizeof(McuSemihost_tty_handles)/sizeof(McuSemihost_tty_handles[0]); i++) {
    int res = McuSemihost_SysIsTTY(McuSemihost_tty_handles[i]);
    if (res==1) {
      McuSemihost_printf("SYS_ISTTY: handle %d OK\n", McuSemihost_tty_handles[i]);
    } else {
      McuSemihost_printf("SYS_ISTTY: handle %d failed, res: %d\n", McuSemihost_tty_handles[i], res);
      res = -1; /* failed */
    }
  }
#endif
#if   McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_PEMICRO /* SYS_READ_C not implemented by PEMICRO */ \
   || McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_LINKSERVER /* fails in MCUXpresso 11.7.0, check with later versions */
    McuSemihost_WriteString((unsigned char*)"McuSemihost: SYS_READC does not work? Check for a newer release than 11.7.0\n");
#else
  int c;

  McuSemihost_WriteString((unsigned char*)"SYS_READC: Please type a character and press <ENTER>:\n"); /* writing zero terminated string */
  do {
    c = McuSemihost_SysReadC();
  } while(c<0);
  McuSemihost_WriteString((unsigned char*)"You typed: ");
  McuSemihost_WriteChar(c);
  McuSemihost_WriteChar('\n');
#if McuSemihost_CONFIG_INIT_STDIO_HANDLES
  unsigned char dummy[16]; /* the input is buffered and delivered only if the user presses enter. So there might be more characters in the stream: read them */
  (void)McuSemihost_SysFileRead(McuSemihost_tty_handles[McuSemihost_STDIN], dummy, sizeof(dummy));
#endif

#endif
  return res;
}

int McuSemiHost_Test(void) {
  unsigned char buf[64];
  TIMEREC time;
  DATEREC date;
  int value;
  int result = 0;

#if McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_GENERIC
  McuSemihost_WriteString((unsigned char*)"Connection: Generic\n");
#elif McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_SEGGER
  McuSemihost_WriteString((unsigned char*)"Connection: SEGGER J-Link\n");
#elif McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_LINKSERVER
  McuSemihost_WriteString((unsigned char*)"Connection: NXP Linkserver\n");
#elif McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_PEMICRO
  McuSemihost_WriteString((unsigned char*)"Connection: PEMICRO\n");
#elif McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_PYOCD
  McuSemihost_WriteString((unsigned char*)"Connection: PyOCD\n");
#else
  #error "unknown connection"
#endif
#if McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_SEGGER
  if (McuSemihost_SeggerIsConnected()) { /* SEGGER specific extension */
    McuSemihost_WriteString((unsigned char*)"SYS_IS_CONNECTED: J-Link connected\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"SYS_IS_CONNECTED: J-Link NOT connected, failed\n");
    result = -1; /* failed */
  }
#endif

  McuSemihost_WriteString((unsigned char*)"SYS_WRITE0 with strings:\n");
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"hello world with SYS_WRITE0\n");
  McuSemihost_WriteString0(buf);
  /* empty string */
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)" deadbeef\n");
  buf[0] = '\0';
  McuSemihost_WriteString0(buf); /* SYS_WRITE0 with a empty string fails for J-LINK */


  const unsigned char *txt = (unsigned char*)"SYS_WRITEC test\n";

  while(*txt!='\0') {
    McuSemihost_SysWriteC(*txt); /* using SYS_WRITEC */
    txt++;
  }

  int secs = McuSemihost_SysHostTime(); /* using SYS_TIME */
  McuTimeDate_UnixSecondsToTimeDateCustom(secs, -1 /* winter time */, &time, &date, 1970);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"SYS_TIME: time: ");
  McuTimeDate_AddTimeString(buf, sizeof(buf), &time, (unsigned char*)McuTimeDate_CONFIG_DEFAULT_TIME_FORMAT_STR);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" ");
  McuTimeDate_AddDateString(buf, sizeof(buf), &date, (unsigned char*)McuTimeDate_CONFIG_DEFAULT_DATE_FORMAT_STR);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\n");
  McuSemihost_WriteString(buf);

  value = McuSemihost_SysHostClock(); /* using SYS_CLOCK */
  if (value>=0) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char *)"SYS_CLOCK: Execution time: ");
    McuUtility_strcatNum32s(buf, sizeof(buf), value);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char *)" centi-seconds\n");
    McuSemihost_WriteString(buf);
  } else {
    McuSemihost_WriteString((unsigned char*)"SYS_CLOCK: failed\n");
    result = -1; /* failed */
  }
  if (ConsoleInputOutput()!=0) {
    McuSemihost_WriteString((unsigned char*)"McuSemihost console I/O operations: FAILED!\n");
    result = -1; /* failed */
  }
  if (TestFileOperations()!=0) {
    McuSemihost_WriteString((unsigned char*)"McuSemihost file operations: FAILED!\n");
    result = -1; /* failed */
  }

  if (McuSemihost_SysIsError(0)!=0) { /* returns 0 for 'no error' */
    McuSemihost_WriteString((unsigned char*)"SYS_ERRNO: 0 should not be error!\n");
    result = -1; /* failed */
  }
  if (!McuSemihost_SysIsError(1)) { /* returns 0 for 'no error' */
    McuSemihost_WriteString((unsigned char*)"SYS_ERRNO: 1 should be error!\n");
    result = -1; /* failed */
  }
  if (!McuSemihost_SysIsError(-1)) { /* returns 0 for 'no error' */
    McuSemihost_WriteString((unsigned char*)"SYS_ERRNO: -1 should be error!\n");
    result = -1; /* failed */
  }

  memset(buf, 0, sizeof(buf)); /* init buffer */
  if (McuSemihost_SysGetCmdLine(buf, sizeof(buf))==0) {
    McuSemihost_WriteString((unsigned char*)"arg: ");
    McuSemihost_WriteString(buf);
    McuSemihost_WriteString((unsigned char*)"\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"SYS_GET_CMDLINE FAILED!\n");
  }

  {
    McuSemihost_HeapInfo_t heapInfo;

    if (McuSemihost_SysHeapInfo(&heapInfo)!=0) {
      McuSemihost_WriteString((unsigned char*)"SYS_HEAPINFO FAILED\n");
    } else {
      McuSemihost_WriteString((unsigned char*)"SYS_HEAPINFO success!\n");
    }
  }
#if McuSemihost_CONFIG_DEBUG_CONNECTION!=McuSemihost_DEBUG_CONNECTION_SEGGER
  {
    int freq = McuSemihost_SysTickFreq();
    if (freq==-1) {
      McuSemihost_WriteString((unsigned char*)"McuSemihost SYS_TICKFREQ: debugger does not know it.\n");
    } else {
      McuSemihost_printf("McuSemihost SYS_TICKFREQ: %d\n", freq);
    }
  }
#endif
#if   McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_SEGGER \
   || McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_LINKSERVER
    /* not supported by SEGGER and LinkServer */
#else
  {
    int32_t val = McuSemihost_SysEnterSVC();
    if (val!=0) {
      McuSemihost_WriteString((unsigned char*)"McuSemihost ENTER_SVC failed?!\n");
    }
  }
#endif

  if (result!=0) {
    McuSemihost_WriteString((unsigned char*)"McuSemihost test FAILED!\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"McuSemihost test OK!\n");
  }

#if McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_LINKSERVER /* fails in MCUXpresso 11.7.0, check with later versions */
  McuSemihost_WriteString((unsigned char*)"McuSemihost: SYS_EXCEPTION does not work with LinkServer\n");
#else
  McuSemihost_WriteString((unsigned char*)"McuSemihost: SYS_EXCEPTION, going to exit debugger!\n");
  McuSemihost_SysException(McuSemihost_ADP_Stopped_ApplicationExit); /* note: will exit application! */
#endif
  return result;
}
/*--------------------------------------------------------------------------------------*/

void McuSemiHost_Deinit(void) {
#if McuSemihost_CONFIG_INIT_STDIO_HANDLES
#if McuSemihost_CONFIG_DEBUG_CONNECTION!=McuSemihost_DEBUG_CONNECTION_SEGGER /* SEGGER does not really allocate those handles? So cannot close them. */
  for(int i=0; i<sizeof(McuSemihost_tty_handles)/sizeof(McuSemihost_tty_handles[0]); i++) {
    McuSemihost_SysFileClose(McuSemihost_tty_handles[i]);
  }
#endif
#endif
}

void McuSemiHost_Init(void) {
#if McuSemihost_CONFIG_INIT_STDIO_HANDLES /* cannot open it twice (restart)? */
  /* initialize standard I/O handler, see https://developer.arm.com/documentation/dui0471/g/Semihosting/SYS-OPEN--0x01- */
  McuSemihost_tty_handles[McuSemihost_STDIN] = McuSemihost_SysFileOpen((unsigned char*)":tt", SYS_FILE_MODE_READ); /* stdin */
  McuSemihost_tty_handles[McuSemihost_STDOUT] = McuSemihost_SysFileOpen((unsigned char*)":tt", SYS_FILE_MODE_WRITE); /* stdout */
  McuSemihost_tty_handles[McuSemihost_STDERR] = McuSemihost_SysFileOpen((unsigned char*)":tt", SYS_FILE_MODE_APPEND); /* stderr */
#if McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_SEGGER
  /* SEGGER always returns -256 for stdin, stdout and stderr file handles. Fix them: */
  McuSemihost_tty_handles[McuSemihost_STDIN] = McuSemihost_STDIN;
  McuSemihost_tty_handles[McuSemihost_STDOUT] = McuSemihost_STDOUT;
  McuSemihost_tty_handles[McuSemihost_STDERR] = McuSemihost_STDERR;
#endif
#endif
}

#endif /* McuSemihost_CONFIG_IS_ENABLED */

/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuSemihost.h"
#include "McuUtility.h"
#include "McuTimeDate.h"
#include "McuXFormat.h"
#include "McuWait.h"
#include <stdio.h>

/*
 * ARM Semihosting operations, see https://developer.arm.com/documentation/dui0471/g/Semihosting
 * See https://github.com/cnoviello/mastering-stm32/blob/master/nucleo-f411RE/system/include/arm/semihosting.h
 * See https://wiki.segger.com/Semihosting
 */
typedef enum McuSemihost_Op_e {
  McuSemihost_Op_SYS_OPEN         = 0x01, /* open a file */
  McuSemihost_Op_SYS_CLOSE        = 0x02, /* close a file */
  McuSemihost_Op_SYS_WRITEC       = 0x03, /* write a character byte, pointed to by R1 */
  McuSemihost_Op_SYS_WRITE0       = 0x04, /* writes a null terminated string. R1 points to the first byte */
  McuSemihost_Op_SYS_WRITE        = 0x05, /* write data to a file */
  McuSemihost_Op_SYS_READ         = 0x06, /* read data from a file */
  McuSemihost_Op_SYS_READC        = 0x07, /* read a character from stdin */
  McuSemihost_Op_SYS_ISERROR      = 0x08,
  McuSemihost_Op_SYS_ISTTY        = 0x09,
  McuSemihost_Op_SYS_SEEK         = 0x0A,
  /* 0x0B ? */
  McuSemihost_Op_SYS_FLEN         = 0x0C,
  McuSemihost_Op_SYS_TMPNAME      = 0x0D,
  McuSemihost_Op_SYS_REMOVE       = 0x0E,
  McuSemihost_Op_SYS_RENAME       = 0x0F,
  McuSemihost_Op_SYS_CLOCK        = 0x10, /* returns the number of centi-seconds since execution started */
  McuSemihost_Op_SYS_TIME         = 0x11, /* time in seconds since Jan 1st 1970 */
  McuSemihost_Op_SYS_SYSTEM       = 0x12,
  McuSemihost_Op_SYS_ERRNO        = 0x13,
  /* 0x14? */
  McuSemihost_Op_SYS_GET_CMDLINE  = 0x15,
  McuSemihost_Op_SYS_HEAPINFO     = 0x16,
  McuSemihost_Op_SYS_ENTER_SVC    = 0x17,
  McuSemihost_Op_SYS_EXCEPTION    = 0x18, /* Exit */

  McuSemihost_Op_SYS_ELLAPSED     = 0x30,
  McuSemihost_Op_SYS_TICKFREQ     = 0x31,

#if McuSemihost_CONFIG_DEBUG_PROBE==McuSemihost_DEBUG_PROBE_SEGGER
  McuSemihost_Op_SYS_IS_CONNECTED = 0x00, /* check if debugger is connected */
  McuSemihost_Op_SYS_WRITEF       = 0x40, /* write a printf-style string, but formatting is on the host */
#endif
} McuSemihost_Op_e;

#define McuSemihost_STDIN           0
#define McuSemihost_STDOUT          1
#define McuSemihost_STDERR          2

#if McuSemihost_CONFIG_INIT_STDIO_HANDLES
static int McuSemihost_tty_handles[3]; /* stdin, stdout and stderr */
#endif

/* File modes for McuSemihost_Op_SYS_OPEN */
#define SYS_FILE_MODE_READ              0   /* Open the file for reading "r" */
#define SYS_FILE_MODE_READBINARY        1   /* Open the file for reading "rb" */
#define SYS_FILE_MODE_READWRITE         2   /* Open the file for reading and writing "r+" */
#define SYS_FILE_MODE_READWRITEBINARY   3   /* Open the file for reading and writing "r+" */
#define SYS_FILE_MODE_WRITE             4   /* Open and truncate or create the file for writing "w" */
#define SYS_FILE_MODE_WRITEBINARY       5   /* Open and truncate or create the file for writing "wb" */
#define SYS_FILE_MODE_WRITEREAD         6   /* Open and truncate or create the file for writing and reading "w+" */
#define SYS_FILE_MODE_WRITEREADBINARY   7   /* Open and truncate or create the file for writing and reading "w+b" */
#define SYS_FILE_MODE_APPEND            8   /* Open or create the file for writing "a" */
#define SYS_FILE_MODE_APPENDBINARY      9   /* Open or create the file for writing "ab" */
#define SYS_FILE_MODE_APPENDREAD        10  /* Open or create the file for writing and reading "a+" */
#define SYS_FILE_MODE_APPENDREADBINARY  11  /* Open or create the file for writing and reading "a+b" */

static inline
int
__attribute__ ((always_inline))
McuSemihost_HostRequest(int reason, void *arg)
{
  int value;
  asm volatile (
      " mov r0, %[rsn] \n"
      " mov r1, %[arg] \n"
      " nop \n"
      " bkpt 0xAB      \n"
      " mov %[val], r0"

      : [val] "=r" (value) /* outputs */
      : [rsn] "r" (reason), [arg] "r" (arg) /* inputs */
      : "r0", "r1", "r2", "r3", "ip", "lr", "memory", "cc" /* clobber */
  );
  return value;
}

#if McuSemihost_CONFIG_DEBUG_PROBE == McuSemihost_DEBUG_PROBE_SEGGER
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
#endif /* McuSemihost_CONFIG_DEBUG_PROBE */
/*!
 * \brief Return the current system time
 * \return System time in seconds since 1970
 */
int McuSemihost_HostTime(void) {
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_TIME, NULL);
}

/*!
 * \brief Return the number of centi-seconds the executable is running
 * \return -1 for error, otherwise the number of centi-seconds of the execution
 */
int McuSemihost_HostClock(void) {
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_CLOCK, NULL);
}

/*!
 * \brief Open a file on the host
 * \param filename
 * \param mode
 * \param fileNameLenght
 * \return -1 if failed, otherwise file handle
 */
int McuSemihost_FileOpen(const unsigned char *filename, int mode) {
  int32_t param[3];

  param[0] = (int32_t)filename;
  param[1] = mode;
  param[2] = McuUtility_strlen((char*)filename);
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_OPEN, &param[0]);
}

/*!
 * \brief Closes a file handle
 * \param fh File handle previously opened
 * \return 0: ok, otherwise -1 if failed
 */
int McuSemihost_FileClose(int fh) {
  int32_t param;

  param = fh;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_CLOSE, &param);
}

/*!
 * \brief Read from a file
 * \param fh File handle
 * \param data Pointer where to store the data
 * \param nofBytes Number of bytes to read
 * \return 0: success. If it is nofBytes, then the call has failed and the end of the file has been reached. If smaller than nofBytes, then the buffer has not been filled.
 */
int McuSemihost_FileRead(int fh, unsigned char *data, size_t nofBytes) {
  int32_t param[3];

  param[0] = fh;
  param[1] = (int32_t)data;
  param[2] = nofBytes;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_READ, &param[0]);
}

int McuSemihost_FileWrite(int fh, const unsigned char *data, size_t nofBytes) {
  int32_t param[3];

  param[0] = fh;
  param[1] = (int32_t)data;
  param[2] = nofBytes;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_WRITE, &param[0]);
}

#if McuSemihost_CONFIG_DEBUG_PROBE!=McuSemihost_DEBUG_PROBE_SEGGER
/* J-Link denies this with
 * ERROR: Semi hosting error: SYS_REMOVE: Target tries to remove file. Declined for security reasons.
 */
int McuSemihost_FileRemove(const unsigned char *filePath) {
  int32_t param[2];

  param[0] = (int32_t)filePath;
  param[1] = McuUtility_strlen((char*)filePath);
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_REMOVE, &param[0]);
}
#endif

#if McuSemihost_CONFIG_DEBUG_PROBE!=McuSemihost_DEBUG_PROBE_SEGGER
/* J-Link denies this with
 * ERROR: Semi hosting error: SYS_RENAME: Target tries to rename file. Declined for security reasons.
 */
int McuSemihost_FileRename(const unsigned char *filePath, const unsigned char *fileNewPath) {
  int32_t param[4];

  param[0] = (int32_t)filePath;
  param[1] = McuUtility_strlen((char*)filePath);
  param[0] = (int32_t)fileNewPath;
  param[1] = McuUtility_strlen((char*)fileNewPath);
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_RENAME, &param[0]);
}
#endif

/*!
 * \brief Return the length of a file
 * \param fh File handle
 * \return Current length of the file, -1 for an error
 */
int McuSemihost_FileLen(int fh) {
  int32_t param;

  param = fh;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_FLEN, &param);
}

/*!
 * \brief Seeks for a specified position in a file
 * \param fh File handle
 * \param pos Target position. Seeking outside of the size of the file is undefined
 * \return 0 for success, negative for an error. McuSemihost_Op_SYS_ERRNO can be used to read the error value.
 */
int McuSemihost_FileSeek(int fh, int pos) {
  int32_t param[2];

  param[0] = fh;
  param[1] = pos;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_SEEK, &param[0]);
}

/*!
 * \brief Read a character from the console or stdin
 * \return The character read
 */
int McuSemihost_ReadChar(void) {
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_READC, NULL);
}

/*!
 * \brief Write a character to the stdout console.
 * \param ch Character to write
 * \return always zero for success
 */
int McuSemihost_WriteChar(char ch) {
  int32_t param = ch; /* need to store it here into a 32bit variable, otherwise don't work? */
  /* Write a character byte, pointed to by R1 */
  (void)McuSemihost_HostRequest(McuSemihost_Op_SYS_WRITEC, &param); /* does not return valid value, R0 is corrupted */
  return 0; /* success */
}

/*!
 * \brief Decides if a file handle is a standard io handle or not.
 * \param fg File handle
 * \return 1 if it a interactive device, 0 if not, any other value is an error
 */
int McuSemihost_IsTTY(int fh) {
  int32_t param = fh;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_ISTTY, &param);
}

/*!
 * \brief Write a zero byte terminated character array (string) to stdout
 * \param str String, zero byte terminated
 * \return 0: ok, -1 error
 */
int McuSemihost_WriteString(const unsigned char *str) {
  /* R1 to point to the first byte of the string */
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_WRITE0, (void*)str);
}

#if McuSemihost_CONFIG_DEBUG_PROBE==McuSemihost_DEBUG_PROBE_SEGGER
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

#if McuSemihost_CONFIG_DEBUG_PROBE==McuSemihost_DEBUG_PROBE_SEGGER
int McuSemihost_WriteFormatted(const unsigned char *format, ...) {
  va_list va;
  int res;

  va_start(va, format);
  res = McuSemihost_WriteF(format, &va);
  va_end(va);
  return res;
}
#endif

bool McuSemihost_StdIOKeyPressed(void) {
  return false; /* \todo */
}

void McuSemihost_StdIOReadChar(uint8_t *ch) {
  int res;

  res = McuSemihost_ReadChar();
  if (res==-1) { /* no character present */
    *ch = '\0';
  } else {
    *ch = (uint8_t)res; /* return character */
  }
}

void McuSemihost_StdIOSendChar(uint8_t ch) {
  (void)McuSemihost_WriteChar(ch);
}

/* default standard I/O struct */
McuShell_ConstStdIOType McuSemihost_stdio = {
    (McuShell_StdIO_In_FctType)McuSemihost_StdIOReadChar, /* stdin */
    (McuShell_StdIO_OutErr_FctType)McuSemihost_StdIOSendChar, /* stdout */
    (McuShell_StdIO_OutErr_FctType)McuSemihost_StdIOSendChar, /* stderr */
    McuSemihost_StdIOKeyPressed /* if input is not empty */
  };
uint8_t McuSemihost_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */

McuShell_ConstStdIOTypePtr McuSemihost_GetStdio(void) {
  return &McuSemihost_stdio;
}

unsigned McuSemihost_printf(const char *fmt, ...) {
  va_list args;
  unsigned int count = 0;

  va_start(args,fmt);
  count = McuXFormat_xvformat(McuShell_printfPutChar, (void*)McuSemihost_GetStdio()->stdOut, fmt, args);
  va_end(args);
  return count;
}

//////////////////////////////////////////////////////////////////////////////////////////////
static int TestFileOperations(void) {
  int fh;
  char buf[24];
  unsigned char data[32];
  const unsigned char *testFileName = (const unsigned char*)"c:\\tmp\\semihosting.txt";
  int res = 0; /* 0: ok, -1: failed */

#if 0
  /* quick test */
  /* Note: file will be created as C:\NXP\MCUXpressoIDE_11.7.0_9198\ide\test.txt */
  fh = McuSemihost_FileOpen("test.txt", SYS_FILE_MODE_WRITEREADBINARY, strlen("test.txt"));
  if (fh == -1) {
    McuSemihost_WriteString((unsigned char*)"Failed\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"OK\n");
    McuSemihost_FileClose(fh);
  }
#endif
  McuSemihost_WriteString((unsigned char*)"SYS_OPEN: Open and create file ");
  McuSemihost_WriteString((unsigned char*)testFileName);
  McuSemihost_WriteString((unsigned char*)"\n");
  fh = McuSemihost_FileOpen(testFileName, SYS_FILE_MODE_WRITEREADBINARY);
  if (fh == -1) {
    McuSemihost_WriteString((unsigned char*)"SYS_OPEN: failed\n");
    res = -1; /* failed */
  } else {
    McuSemihost_WriteString((unsigned char*)"SYS_OPEN: OK\n");
    if (McuSemihost_IsTTY(fh)==0) {
      McuSemihost_WriteString((unsigned char*)"SYS_ISTTY: OK\n");
    } else {
      McuSemihost_WriteString((unsigned char*)"SYS_ISTTY: failed\n");
      res = -1; /* failed */
    }
    if (McuSemihost_FileClose(fh)==0) {
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
  fh = McuSemihost_FileOpen(testFileName, SYS_FILE_MODE_WRITEREADBINARY);
  if (fh == -1) {
    McuSemihost_WriteString((unsigned char*)"SYS_OPEN: failed\n");
  } else {
    const unsigned char *msg = (const unsigned char*)"test file write 0123456789ABCDEF Hello World!";
    if (McuSemihost_FileWrite(fh, msg, strlen((char*)msg)) != 0) {
      McuSemihost_WriteString((unsigned char*)"SYS_WRITE: failed\n");
      res = -1; /* failed */
    } else {
      McuSemihost_WriteString((unsigned char*)"SYS_WRITE OK\n");
    }
    McuSemihost_FileClose(fh);
  }

  /* read from file */
  McuSemihost_WriteString((unsigned char*)"SYS_READ: Read from file ");
  McuSemihost_WriteString((unsigned char*)testFileName);
  McuSemihost_WriteString((unsigned char*)"\n");
  fh = McuSemihost_FileOpen(testFileName, SYS_FILE_MODE_READ);
  if (fh == -1) {
    McuSemihost_WriteString((unsigned char*)"SYS_OPEN failed\n");
    res = -1; /* failed */
  } else {
    int r;

    memset(data, 0, sizeof(data)); /* initialize data */
    r = McuSemihost_FileRead(fh, data, sizeof(data));
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
    McuSemihost_FileClose(fh);
  }

  /* seek position in file, length of a file */
  McuSemihost_WriteString((unsigned char*)"SYS_FLEN: Size of file ");
  McuSemihost_WriteString((unsigned char*)testFileName);
  McuSemihost_WriteString((unsigned char*)"\n");
  fh = McuSemihost_FileOpen(testFileName, SYS_FILE_MODE_READ);
  if (fh == -1) {
    McuSemihost_WriteString((unsigned char*)"SYS_OPEN: failed\n");
    res = -1; /* failed */
  } else {
    int r;

    r = McuSemihost_FileSeek(fh, 6); /* go to pos 6 or enlarge file to 6 bytes */
    if (r != 0) {
      McuSemihost_WriteString((unsigned char*)"SYS_SEEK failed\n");
      res = -1; /* failed */
    } else {
      McuSemihost_WriteString((unsigned char*)"SYS_SEEK: OK\n");
    }
    /* file length */
    r = McuSemihost_FileLen(fh);
    if (r >= 0) {
      McuSemihost_printf("SYS_FLEN: file size: %d\n", r);
    } else {
      McuSemihost_WriteString((unsigned char*)"SYS_FLEN failed\n");
      res = -1; /* failed */
    }
    McuSemihost_FileClose(fh);
  }

#if McuSemihost_CONFIG_DEBUG_PROBE!=McuSemihost_DEBUG_PROBE_SEGGER
  const unsigned char *newFileName = (const unsigned char*)"c:\\tmp\\copy.txt";
  /* renaming a file */
  McuSemihost_WriteString((unsigned char*)"SYS_RENAME: rename file ");
  McuSemihost_WriteString((unsigned char*)testFileName);
  McuSemihost_WriteString((unsigned char*)" to ");
  McuSemihost_WriteString((unsigned char*)newFileName);
  McuSemihost_WriteString((unsigned char*)"\n");
  if (McuSemihost_FileRename(testFileName, newFileName) != 0) {
    McuSemihost_WriteString((unsigned char*)"SYS_RENAME failed\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"SYS_RENAME OK\n");
  }
#else
  McuSemihost_WriteString((unsigned char*)"SYS_RENAME not supported by J-Link for security reasons.\n");
#endif

#if McuSemihost_CONFIG_DEBUG_PROBE!=McuSemihost_DEBUG_PROBE_SEGGER
  /* removing a file */
  McuSemihost_WriteString((unsigned char*)"SYS_REMOVE: delete file ");
  McuSemihost_WriteString((unsigned char*)newFileName);
  McuSemihost_WriteString((unsigned char*)"\n");
  if (McuSemihost_FileRemove(copyFileName) != 0) {
    McuSemihost_WriteString((unsigned char*)"SYS_REMOVE failed\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"SYS_REMOVE OK\n");
  }
#else
  McuSemihost_WriteString((unsigned char*)"SYS_REMOVE not supported by J-Link for security reasons.\n");
#endif

  /* writing to stdout */
  //McuSemihost_FileWrite((int)stdout, buf, sizeof(buf)-r);
  //McuSemihost_WriteString((unsigned char*)"\n");
  return res;
}

static int ConsoleInputOutput(void) {
  /* test of console input and output */
  int c;
  int res = 0;

#if McuSemihost_CONFIG_INIT_STDIO_HANDLES
  for(int i=0; i<sizeof(McuSemihost_tty_handles)/sizeof(McuSemihost_tty_handles[0]); i++) {
    if (McuSemihost_IsTTY(McuSemihost_tty_handles[i])==1) {
      McuSemihost_printf("SYS_ISTTY: handle %d OK\n", McuSemihost_tty_handles[i]);
    } else {
      McuSemihost_printf("SYS_ISTTY: handle %d failed\n", McuSemihost_tty_handles[i]);
      res = -1; /* failed */
    }
  }
#endif
  McuSemihost_WriteString((unsigned char*)"READ_C: Please type a character and press <ENTER>:\n"); /* writing zero terminated string */
  do {
    c = McuSemihost_ReadChar();
  } while(c<0);
  McuSemihost_printf("You typed: %c\n", c);
  return res;
}

int McuSemiHost_Test(void) {
  unsigned char buf[64];
  TIMEREC time;
  DATEREC date;
  int value;
  int result = 0;

#if McuSemihost_CONFIG_DEBUG_PROBE==McuSemihost_DEBUG_PROBE_SEGGER
  if (McuSemihost_SeggerIsConnected()) { /* \todo: always returns 0? Should be supported, but is not with gdb? */
    McuSemihost_WriteString((unsigned char*)"SYS_IS_CONNECTED: J-Link connected\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"SYS_IS_CONNECTED: J-Link NOT connected, failed\n");
    result = -1; /* failed */
  }
#endif

  const unsigned char *txt = (unsigned char*)"This is a SYS_WRITEC test\n";

  while(*txt!='\0') {
    McuSemihost_WriteChar(*txt); /* using SYS_WRITEC */
    txt++;
  }
  McuSemihost_WriteString((unsigned char*)"This is a SYS_WRITE0 test\n"); /* using SYS_WRITE0 */

  int secs = McuSemihost_HostTime(); /* using SYS_TIME */
  McuTimeDate_UnixSecondsToTimeDateCustom(secs, -1 /* winter time */, &time, &date, 1970);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"SYS_TIME: time: ");
  McuTimeDate_AddTimeString(buf, sizeof(buf), &time, (unsigned char*)McuTimeDate_CONFIG_DEFAULT_TIME_FORMAT_STR);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" ");
  McuTimeDate_AddDateString(buf, sizeof(buf), &date, (unsigned char*)McuTimeDate_CONFIG_DEFAULT_DATE_FORMAT_STR);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\n");
  McuSemihost_WriteString(buf);

  value = McuSemihost_HostClock(); /* using SYS_CLOCK */
  if (value>=0) {
    McuSemihost_printf("SYS_CLOCK: Execution time: %d centi-seconds\n", value);
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
  if (result!=0) {
    McuSemihost_WriteString((unsigned char*)"McuSemihost test FAILED!\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"McuSemihost test OK!\n");
  }
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////

void McuSemiHost_Deinit(void) {
#if McuSemihost_CONFIG_INIT_STDIO_HANDLES
  for(int i=0; i<sizeof(McuSemihost_tty_handles)/sizeof(McuSemihost_tty_handles[0]); i++) {
    McuSemihost_FileClose(McuSemihost_tty_handles[i]);
  }
#endif
}

void McuSemiHost_Init(void) {
#if McuSemihost_CONFIG_INIT_STDIO_HANDLES /* cannot open it twice (restart)? */
  /* initialize standard I/O handler, see https://developer.arm.com/documentation/dui0471/g/Semihosting/SYS-OPEN--0x01- */
  McuSemihost_tty_handles[0] = McuSemihost_FileOpen((unsigned char*)":tt", SYS_FILE_MODE_READ); /* stdin */
  McuSemihost_tty_handles[1] = McuSemihost_FileOpen((unsigned char*)":tt", SYS_FILE_MODE_WRITE); /* stdout */
  McuSemihost_tty_handles[2] = McuSemihost_FileOpen((unsigned char*)":tt", SYS_FILE_MODE_APPEND); /* stderr */
#endif
}

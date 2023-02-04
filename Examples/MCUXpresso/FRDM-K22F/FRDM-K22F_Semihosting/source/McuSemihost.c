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
  McuSemihost_Op_SYS_IS_CONNECTED = 0x00, /* SEGGER specific */
  McuSemihost_Op_SYS_OPEN         = 0x01,
  McuSemihost_Op_SYS_CLOSE        = 0x02,
  McuSemihost_Op_SYS_WRITEC       = 0x03, /* write a character byte, pointed to by R1 */
  McuSemihost_Op_SYS_WRITE0       = 0x04, /* writes a null terminated string. R1 points to the first byte */
  McuSemihost_Op_SYS_WRITE        = 0x05,
  McuSemihost_Op_SYS_READ         = 0x06,
  McuSemihost_Op_SYS_READC        = 0x07,
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

  McuSemihost_Op_SYS_WRITEF       = 0x40, /* SEGGER specific */
} McuSemihost_Op_e;

#define McuSemihost_STDIN           0
#define McuSemihost_STDOUT          1
#define McuSemihost_ERROUT          2

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

//static inline
int
//__attribute__ ((always_inline))
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

int McuSemihost_CallHost_other(int op, void *p1, void *p2) {
  register int r0 asm("r0");
  register int r1 asm("r1") __attribute__((unused));
  register int r2 asm("r2") __attribute__((unused));

  r0 = op;
  r1 = (int) p1;
  r2 = (int) p2;

  asm volatile(
      " bkpt 0xAB \n"
      : "=r"(r0) // out
      :// in
      :// clobber
  );
  return r0;
}

//static int McuSemihost_HostRequest(McuSemihost_Op_e op, void *param) {
//  return McuSemihost_CallHost(op, param);
  //return McuSemihost_CallHost(op, param, 0); /* SEGGER way */
//}

/*!
 * \brief Return the current system time
 * \return System time in seconds since 1970
 */
int McuSemihost_HostTime(void) {
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_TIME, NULL);
}

/*!
 * \brief Return the number of centi-seconds the executable is running
 * \return -1 for error, otherwise the number of centiseconds of the execution
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
int McuSemihost_FileRead(int fh, const char *data, size_t nofBytes) {
  int32_t param[3];

  param[0] = fh;
  param[1] = (int32_t)data;
  param[2] = nofBytes;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_READ, &param[0]);
}

int McuSemihost_FileWrite(int fh, const char *data, size_t nofBytes) {
  int32_t param[3];

  param[0] = fh;
  param[1] = (int32_t)data;
  param[2] = nofBytes;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_WRITE, &param[0]);
}

int McuSemihost_FileRemove(const unsigned char *filePath) {
  int32_t param[2];

  param[0] = (int32_t)filePath;
  param[1] = McuUtility_strlen((char*)filePath);
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_REMOVE, &param[0]);
}

int McuSemihost_FileRename(const unsigned char *filePath, const unsigned char *fileNewPath) {
  int32_t param[4];

  param[0] = (int32_t)filePath;
  param[1] = McuUtility_strlen((char*)filePath);
  param[0] = (int32_t)fileNewPath;
  param[1] = McuUtility_strlen((char*)fileNewPath);
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_RENAME, &param[0]);
}

int McuSemihost_FileLen(int fh) {
  int32_t param;

  param = fh;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_FLEN, &param);
}

int McuSemihost_FileSeek(int fh, int pos) {
  int32_t param[2];

  param[0] = fh;
  param[1] = pos;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_FLEN, &param[0]);
}

int McuSemihost_ReadChar(void) {
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_READC, NULL);
}

int McuSemihost_WriteChar(char ch) {
  int32_t param = ch; /* need to store it here into a 32bit variable, otherwise don't work? */
  /* Write a character byte, pointed to by R1 */
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_WRITEC, &param);
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

int McuSemihost_WriteFormatted(const unsigned char *format, va_list *arg) {
  int32_t param[2];

  param[0] = (int32_t)format;
  param[1] = (int32_t)arg;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_WRITEF, &param[0]);
}

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
static void TestFileOperations(void) {
  int hFile;
  int r;
  char buf[24];
  const unsigned char *testFileName = (const unsigned char*)"c:\\tmp\\semihosting.txt";
  const unsigned char *copyFileName = (const unsigned char*)"c:\\tmp\\copy.txt";

#if 0
  /* quick test */
  /* Note: file will be created as C:\NXP\MCUXpressoIDE_11.7.0_9198\ide\test.txt */
  hFile = McuSemihost_FileOpen("test.txt", SYS_FILE_MODE_WRITEREADBINARY, strlen("test.txt"));
  if (hFile == -1) {
    McuSemihost_WriteString((unsigned char*)"Failed\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"OK\n");
    McuSemihost_FileClose(hFile);
  }
#endif
  McuSemihost_WriteString((unsigned char*)"SYS_OPEN: Open and create file ");
  McuSemihost_WriteString((unsigned char*)testFileName);
  McuSemihost_WriteString((unsigned char*)"\n");
  hFile = McuSemihost_FileOpen(testFileName, SYS_FILE_MODE_WRITEREADBINARY);
  if (hFile == -1) {
    McuSemihost_WriteString((unsigned char*)"SYS_OPEN: Failed\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"SYS_OPEN: OK\n");
    if (McuSemihost_FileClose(hFile)==0) {
      McuSemihost_WriteString((unsigned char*)"SYS_CLOSE: OK\n");
    } else {
      McuSemihost_WriteString((unsigned char*)"SYS_CLOSE: Failed\n");
    }
  }

  /* writing to file */
  McuSemihost_WriteString((unsigned char*)"SYS_WRITE: Write to file ");
  McuSemihost_WriteString((unsigned char*)testFileName);
  McuSemihost_WriteString((unsigned char*)"\n");
  hFile = McuSemihost_FileOpen(testFileName, SYS_FILE_MODE_WRITEREADBINARY);
  if (hFile == -1) {
    McuSemihost_WriteString((unsigned char*)"SYS_OPEN failed\n");
  } else {
    const char *msg = "test file write 0123456789ABCDEF Hello World!";
    r = McuSemihost_FileWrite(hFile, msg, strlen(msg));
    if (r != 0) {
      McuSemihost_WriteString((unsigned char*)"SYS_WRITE Failed\n");
    } else {
      McuSemihost_WriteString((unsigned char*)"SYS_WRITE OK\n");
    }
    McuSemihost_FileClose(hFile);
  }

  /* reading from file */
  McuSemihost_WriteString((unsigned char*)"SYS_READ: Read from file ");
  McuSemihost_WriteString((unsigned char*)testFileName);
  McuSemihost_WriteString((unsigned char*)"\n");
  hFile = McuSemihost_FileOpen(testFileName, SYS_FILE_MODE_WRITEREADBINARY);
  if (hFile == -1) {
    McuSemihost_WriteString((unsigned char*)"SYS_OPEN failed\n");
  } else {
    memset(buf, 0, sizeof(buf));
    r = McuSemihost_FileRead(hFile, buf, sizeof(buf));
    if (r < 0) {
      McuSemihost_WriteString((unsigned char*)"Failed\n");
    } else if (r == sizeof(buf)) {
      McuSemihost_WriteString((unsigned char*)"Failed. Read EOF\n");
    } else {
      McuSemihost_FileWrite((int)stdout, buf, sizeof(buf) - r);
      McuSemihost_WriteString((unsigned char*)"\n");
      snprintf(buf, sizeof(buf), "Read %d bytes\n", sizeof(buf) - r);
      McuSemihost_WriteString((unsigned char*)buf);
      McuSemihost_WriteString((unsigned char*)"OK");
    }
    McuSemihost_FileClose(hFile);
  }

  /* seek position in file */
  McuSemihost_WriteString((unsigned char*)"SYS_FLEN: Size of file ");
  McuSemihost_WriteString((unsigned char*)testFileName);
  McuSemihost_WriteString((unsigned char*)"\n");
  hFile = McuSemihost_FileOpen(testFileName, SYS_FILE_MODE_WRITEREADBINARY);
  if (hFile == -1) {
    McuSemihost_WriteString((unsigned char*)"SYS_OPEN failed\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"OK\n");
    r = McuSemihost_FileSeek(hFile, 6);
    if (r != 0) {
      McuSemihost_WriteString((unsigned char*)"SYS_FLEN failed\n");
    } else {
      McuSemihost_WriteString((unsigned char*)"SYS_FLEN OK\n");
    }
    /* file length */
    r = McuSemihost_FileLen(hFile);
    if (r >= 0) {
      snprintf(buf, sizeof(buf), "File size: %d\n", r);
      McuSemihost_WriteString((unsigned char*)buf);
    } else {
      McuSemihost_WriteString((unsigned char*)"Failed\n");
    }
    McuSemihost_FileClose(hFile);
  }

  /* renaming a file */
  McuSemihost_WriteString((unsigned char*)"SYS_RENAME: rename file ");
  McuSemihost_WriteString((unsigned char*)testFileName);
  McuSemihost_WriteString((unsigned char*)" to ");
  McuSemihost_WriteString((unsigned char*)copyFileName);
  McuSemihost_WriteString((unsigned char*)"\n");
  r = McuSemihost_FileRename(testFileName, copyFileName);
  if (r != 0) {
    McuSemihost_WriteString((unsigned char*)"SYS_RENAME failed\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"SYS_RENAME OK\n");
  }

  /* removing a file */
  McuSemihost_WriteString((unsigned char*)"SYS_REMOVE: delete file ");
  McuSemihost_WriteString((unsigned char*)copyFileName);
  McuSemihost_WriteString((unsigned char*)"\n");
  r = McuSemihost_FileRemove(copyFileName);
  if (r != 0) {
    McuSemihost_WriteString((unsigned char*)"SYS_REMOVE failed\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"SYS_REMOVE OK\n");
  }
}

static void ConsoleInputOutput(void) {
  /* test of console input and output */
  int c;

  McuSemihost_WriteString((unsigned char*)"READ_C: Please type a character and press <ENTER>:\n"); /* writing zero terminated string */
  do {
    c = McuSemihost_ReadChar();
  } while(c<0);
  McuSemihost_printf("You typed: %c\n", c);
}

void McuSemiHost_Test(void) {
  unsigned char buf[64];
  TIMEREC time;
  DATEREC date;
  int value;

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
  McuSemihost_printf("SYS_CLOCK: Execution time: %d centi-seconds\n", value); /* test with printf and SYS_WRITE_C */

  ConsoleInputOutput();
  TestFileOperations();
  McuSemihost_WriteString((unsigned char*)"McuSemihost testing done!\n");
}
//////////////////////////////////////////////////////////////////////////////////////////////

void McuSemiHost_Deinit(void) {
  /* \todo */
}

void McuSemiHost_Init(void) {
#if McuSemihost_CONFIG_INIT_STDIO_HANDLES /* cannot open it twice (restart)? */
  /* initialize standard I/O handler, see https://developer.arm.com/documentation/dui0471/g/Semihosting/SYS-OPEN--0x01- */
  int fh;
  fh = McuSemihost_FileOpen(":tt", SYS_FILE_MODE_READ, strlen(":tt")); /* stdin */
  if (fh!=McuSemihost_STDIN) {
    for(;;) {}
  }
  fh = McuSemihost_FileOpen(":tt", SYS_FILE_MODE_WRITE, strlen(":tt")); /* stdout */
  if (fh!=McuSemihost_STDOUT) {
    for(;;) {}
  }
  fh = McuSemihost_FileOpen(":tt", SYS_FILE_MODE_APPEND, strlen(":tt")); /* stderr */
  if (fh!=McuSemihost_STDERR) {
    for(;;) {}
  }
#endif
}

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
  McuSemihost_Op_SYS_WRITEC       = 0x03,
  McuSemihost_Op_SYS_WRITE0       = 0x04,
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
  McuSemihost_Op_SYS_CLOCK        = 0x10,
  McuSemihost_Op_SYS_TIME         = 0x11, /* time in seconds since 1970 */
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
#define SYS_FILE_MODE_READ              0   // Open the file for reading "r"
#define SYS_FILE_MODE_READBINARY        1   // Open the file for reading "rb"
#define SYS_FILE_MODE_READWRITE         2   // Open the file for reading and writing "r+"
#define SYS_FILE_MODE_READWRITEBINARY   3   // Open the file for reading and writing "r+"
#define SYS_FILE_MODE_WRITE             4   // Open and truncate or create the file for writing "w"
#define SYS_FILE_MODE_WRITEBINARY       5   // Open and truncate or create the file for writing "wb"
#define SYS_FILE_MODE_WRITEREAD         6   // Open and truncate or create the file for writing and reading "w+"
#define SYS_FILE_MODE_WRITEREADBINARY   7   // Open and truncate or create the file for writing and reading "w+b"
#define SYS_FILE_MODE_APPEND            8   // Open or create the file for writing "a"
#define SYS_FILE_MODE_APPENDBINARY      9   // Open or create the file for writing "ab"
#define SYS_FILE_MODE_APPENDREAD        10  // Open or create the file for writing and reading "a+"
#define SYS_FILE_MODE_APPENDREADBINARY  11  // Open or create the file for writing and reading "a+b"


/* notify the debugger with a breakpoint */
static inline int __attribute__ ((always_inline)) McuSemihost_CallHost(int op, void *p1, void *p2) {
  register int r0 asm("r0");
  register int r1 asm("r1") __attribute__((unused));
  register int r2 asm("r2") __attribute__((unused));

  r0 = op;
  r1 = (int)p1;
  r2 = (int)p2;
  __asm volatile(
      " bkpt 0xAB\n"
      : "=r"(r0) /* outputs */
      : /* input */
      : /* clobber */
  );
  return r0;
}

// SWI numbers and reason codes for RDI (Angel) monitors.
#define AngelSWI_ARM                    0x123456
#ifdef __thumb__
#define AngelSWI                        0xAB
#else
#define AngelSWI                        AngelSWI_ARM
#endif
// For thumb only architectures use the BKPT instruction instead of SWI.
#if defined(__ARM_ARCH_7M__)     \
    || defined(__ARM_ARCH_7EM__) \
    || defined(__ARM_ARCH_6M__)
#define AngelSWIInsn                    "bkpt"
#define AngelSWIAsm                     bkpt
#else
#define AngelSWIInsn                    "swi"
#define AngelSWIAsm                     swi
#endif

#if defined(OS_DEBUG_SEMIHOSTING_FAULTS)
// Testing the local semihosting handler cannot use another BKPT, since this
// configuration cannot trigger HaedFault exceptions while the debugger is
// connected, so we use an illegal op code, that will trigger an
// UsageFault exception.
#define AngelSWITestFault       "setend be"
#define AngelSWITestFaultOpCode (0xB658)
#endif

//static inline
int
//__attribute__ ((always_inline))
call_host (int reason, void *arg)
{
  int value;
  asm volatile (
      " mov r0, %[rsn]  \n"
      " mov r1, %[arg]  \n"
#if defined(OS_DEBUG_SEMIHOSTING_FAULTS)
      " " AngelSWITestFault " \n"
#else
      " " AngelSWIInsn " %[swi] \n"
#endif
      " mov %[val], r0"

      : [val] "=r" (value) /* Outputs */
      : [rsn] "r" (reason), [arg] "r" (arg), [swi] "i" (AngelSWI) /* Inputs */
      : "r0", "r1", "r2", "r3", "ip", "lr", "memory", "cc"
      // Clobbers r0 and r1, and lr if in supervisor mode
  );

  // Accordingly to page 13-77 of ARM DUI 0040D other registers
  // can also be clobbered. Some memory positions may also be
  // changed by a system call, so they should not be kept in
  // registers. Note: we are assuming the manual is right and
  // Angel is respecting the APCS.
  return value;
}


static int McuSemihost_HostRequest(McuSemihost_Op_e op, void *param) {
  return call_host(op, param);
  //return McuSemihost_CallHost(op, param, 0);
}

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
int McuSemihost_FileOpen(const char *filename, int mode, int fileNameLenght) {
  int32_t param[3];

  param[0] = (int32_t)filename;
  param[1] = mode;
  param[2] = fileNameLenght;
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

int McuSemihost_FileRemove(const unsigned char *filePath, size_t numBytesFilePath) {
  int32_t param[2];

  param[0] = (int32_t)filePath;
  param[1] = numBytesFilePath;
  return McuSemihost_HostRequest(McuSemihost_Op_SYS_REMOVE, &param[0]);
}

int McuSemihost_FileRename(const unsigned char *filePath, size_t numBytesFilePath, const unsigned char *fileNewPath, size_t numBytesNewFilePath) {
  int32_t param[4];

  param[0] = (int32_t)filePath;
  param[1] = numBytesFilePath;
  param[0] = (int32_t)fileNewPath;
  param[1] = numBytesNewFilePath;
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
  int32_t param = ch; /* address must be aligned, so we are using a 32bit value here */
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
#define _FILENAME_OPEN    "c:\\tmp\\test_semihosting2.txt"
#define _FILENAME_RENAME  "c:\\tmp\\test_semihosting_renamed.txt"
#define _FILENAME_REMOVE  "c:\\tmp\\test_semihosting_removed.txt"

static void TestFileOperations(void) {
  int hFile;
  int r;
  char buf[24];

  printf("hello semihosting\n");
  /* quick test */
  hFile = McuSemihost_FileOpen("testxx.txt", SYS_FILE_MODE_WRITEREADBINARY, strlen("testxx.txt"));
  if (hFile == -1) {
    McuSemihost_WriteString((unsigned char*)"Failed\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"OK\n");
    McuSemihost_FileClose(hFile);
  }

  McuSemihost_WriteString((unsigned char*)"Open and create file on host system (SYS_OPEN):");
  McuSemihost_WriteString((unsigned char*)_FILENAME_OPEN);
  McuSemihost_WriteString((unsigned char*)"\n");
  hFile = McuSemihost_FileOpen(_FILENAME_OPEN, SYS_FILE_MODE_WRITEREADBINARY, strlen(_FILENAME_OPEN));
  if (hFile == -1) {
    McuSemihost_WriteString((unsigned char*)"Open: Failed\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"Open: OK\n");
    McuSemihost_FileClose(hFile);
  }

  /* writing to file */
  const char *msg = "test file write 0123456789ABCDEF Hello Worlds";

  hFile = McuSemihost_FileOpen(_FILENAME_OPEN, SYS_FILE_MODE_WRITEREADBINARY, strlen(_FILENAME_OPEN));
  if (hFile == -1) {
    McuSemihost_WriteString((unsigned char*)"Failed\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"OK\n");
    r = McuSemihost_FileWrite(hFile, msg, strlen(msg));
    if (r != 0) {
      McuSemihost_WriteString((unsigned char*)"Failed\n");
    } else {
      McuSemihost_WriteString((unsigned char*)"OK\n");
    }
    McuSemihost_FileClose(hFile);
  }

  /* reading from file */
  hFile = McuSemihost_FileOpen(_FILENAME_OPEN, SYS_FILE_MODE_WRITEREADBINARY, strlen(_FILENAME_OPEN));
  if (hFile == -1) {
    McuSemihost_WriteString((unsigned char*)"Failed\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"OK\n");
  }
  McuSemihost_WriteString((unsigned char*)"Reading from file:\n");
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

  /* seek position in file */
  hFile = McuSemihost_FileOpen(_FILENAME_OPEN, SYS_FILE_MODE_WRITEREADBINARY, strlen(_FILENAME_OPEN));
  if (hFile == -1) {
    McuSemihost_WriteString((unsigned char*)"Failed\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"OK\n");
  }
  r = McuSemihost_FileSeek(hFile, 6);
   if (r != 0) {
     McuSemihost_WriteString((unsigned char*)"Failed\n");
   } else {
     McuSemihost_WriteString((unsigned char*)"OK\n");
   }
   /* file len */
   r = McuSemihost_FileLen(hFile);
    if (r >= 0) {
      snprintf(buf, sizeof(buf), "Filesize: %d\n", r);
      McuSemihost_WriteString((unsigned char*)buf);
      McuSemihost_WriteString((unsigned char*)"OK\n");
    } else {
      McuSemihost_WriteString((unsigned char*)"Failed\n");
    }
    McuSemihost_FileClose(hFile);

  /* removing a file */
  hFile = McuSemihost_FileOpen(_FILENAME_REMOVE, SYS_FILE_MODE_WRITEBINARY, strlen(_FILENAME_REMOVE));
  if (hFile == -1) {
    McuSemihost_WriteString((unsigned char*)"Failed to create file\n");
  } else {
    McuSemihost_FileClose(hFile);
  }

  r = McuSemihost_FileRemove((unsigned char*)_FILENAME_REMOVE, strlen(_FILENAME_REMOVE));
  if (r != 0) {
    McuSemihost_WriteString((unsigned char*)"Failed\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"OK\n");
  }

   /* renaming a file ==> fails? */
  r = McuSemihost_FileRename((unsigned char*)_FILENAME_OPEN, strlen(_FILENAME_OPEN), (unsigned char*)_FILENAME_RENAME, strlen(_FILENAME_RENAME));
  if (r != 0) {
    McuSemihost_WriteString((unsigned char*)"Failed\n");
  } else {
    McuSemihost_WriteString((unsigned char*)"OK\n");
  }
}

#if 0
static void ConsoleInputOutput(void) {
  /* test of console input and output */
  int c;

  McuSemihost_WriteString((unsigned char*)"Please type a character and press <ENTER>:\n"); /* writing zero terminated string */
  do {
    c = McuSemihost_ReadChar();
  } while(c<0);
  McuSemihost_printf("You entered: %c\n", c);
}
#endif


void McuSemiHost_Init(void) {
  unsigned char buf[64];
  TIMEREC time;
  DATEREC date;
  int value;

  McuSemihost_WriteString((unsigned char*)"McuSemihost testing start...\n");
  int secs = McuSemihost_HostTime();
  McuTimeDate_UnixSecondsToTimeDateCustom(secs, -1 /* winter time */, &time, &date, 1970);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"host time: ");
  McuTimeDate_AddTimeString(buf, sizeof(buf), &time, (unsigned char*)McuTimeDate_CONFIG_DEFAULT_TIME_FORMAT_STR);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" ");
  McuTimeDate_AddDateString(buf, sizeof(buf), &date, (unsigned char*)McuTimeDate_CONFIG_DEFAULT_DATE_FORMAT_STR);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\n");
  McuSemihost_WriteString(buf);

  value = McuSemihost_HostClock();
  McuSemihost_printf("Execution time: %d centi-seconds\n", value);

//  ConsoleInputOutput();
  TestFileOperations();
  McuSemihost_WriteString((unsigned char*)"McuSemihost testing done!\n");
}
//////////////////////////////////////////////////////////////////////////////////////////////

void McuSemiHost_Deinit(void) {
  /* \todo */
}

void McuSemiHost_Init(void) {
#if 0 /* cannot open it twice (restart)? */
  /* initialize standard I/O handler, see https://developer.arm.com/documentation/dui0471/g/Semihosting/SYS-OPEN--0x01- */
  (void)McuSemihost_FileOpen(":tt", SYS_FILE_MODE_READ, strlen(":tt")); /* stdin */
  (void)McuSemihost_FileOpen(":tt", SYS_FILE_MODE_WRITE, strlen(":tt")); /* stdout */
  (void)McuSemihost_FileOpen(":tt", SYS_FILE_MODE_APPEND, strlen(":tt")); /* stderr */
#endif
}

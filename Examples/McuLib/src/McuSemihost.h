/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUSEMIHOST_H_
#define MCUSEMIHOST_H_

#include "McuSemihost_config.h"

#include <stdbool.h>
#include <stdint.h>
#include "McuTimeDate.h"
#include "McuShell.h"

#ifdef __cplusplus
extern "C" {
#endif

#define McuSemihost_STDIN           0 /*!< handle for standard input */
#define McuSemihost_STDOUT          1 /*!< handle for standard output */
#define McuSemihost_STDERR          2 /*!< handle for standard error */

extern int McuSemihost_Read(int handle, unsigned char *data, size_t nofBytes);

extern uint8_t McuSemihost_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE];
  /*!< default buffer which can be used by the application or shell */

extern McuShell_ConstStdIOType McuSemihost_stdio;
  /*!< Default standard I/O handler, can be used for a shell intergration */

/*!
 * \brief Return the SWO stdio handle
 * \return Standard I/O handle
 */
McuShell_ConstStdIOTypePtr McuSemihost_GetStdio(void);

/*!
 * \brief Flush the standard I/O output. Needed if using McuSemihost_CONFIG_BUFFER_IO_FLUSH.
 */
void McuSemihost_StdIOFlush(void);

/*!
 * \brief Write a character to the stdout console.
 * \param ch Character to write
 * \return always zero for success
 */
int McuSemihost_WriteChar(char ch);

/*!
 * \brief Return the current system time
 * \return System time in seconds since 1970
 */
int McuSemihost_SysHostTime(void);

/*!
 * \brief Return the number of centi-seconds the executable is running
 * \return -1 for error, otherwise the number of centi-seconds of the execution
 */
int McuSemihost_SysHostClock(void);

/* File modes for McuSemihost_FileOpen() */
#define SYS_FILE_MODE_READ              0   /* Open the file for reading "r" */
#define SYS_FILE_MODE_READBINARY        1   /* Open the file for reading "rb" */
#define SYS_FILE_MODE_READWRITE         2   /* Open the file for reading and writing "r+" */
#define SYS_FILE_MODE_READWRITEBINARY   3   /* Open the file for reading and writing "r+b" */
#define SYS_FILE_MODE_WRITE             4   /* Open and truncate or create the file for writing "w" */
#define SYS_FILE_MODE_WRITEBINARY       5   /* Open and truncate or create the file for writing "wb" */
#define SYS_FILE_MODE_WRITEREAD         6   /* Open and truncate or create the file for writing and reading "w+" */
#define SYS_FILE_MODE_WRITEREADBINARY   7   /* Open and truncate or create the file for writing and reading "w+b" */
#define SYS_FILE_MODE_APPEND            8   /* Open or create the file for writing "a" */
#define SYS_FILE_MODE_APPENDBINARY      9   /* Open or create the file for writing "ab" */
#define SYS_FILE_MODE_APPENDREAD        10  /* Open or create the file for writing and reading "a+" */
#define SYS_FILE_MODE_APPENDREADBINARY  11  /* Open or create the file for writing and reading "a+b" */

/*!
 * \brief Open a file on the host
 * \param filename
 * \param mode
 * \return -1 if failed, otherwise file handle
 */
int McuSemihost_SysFileOpen(const unsigned char *filename, int mode);

/*!
 * \brief Closes a file handle
 * \param fh File handle previously opened
 * \return 0: ok, otherwise -1 if failed
 */
int McuSemihost_SysFileClose(int fh);

/*!
 * \brief Read from a file
 * \param fh File handle
 * \param data Pointer where to store the data
 * \param nofBytes Number of bytes to read
 * \return 0: success. If it is nofBytes, then the call has failed and the end of the file has been reached. If smaller than nofBytes, then the buffer has not been filled.
 */
int McuSemihost_SysFileRead(int fh, unsigned char *data, size_t nofBytes);

/*!
 * \brief Write data to a file
 * \param fh File handle
 * \param data Pointer to data
 * \param nofBytes Number of data bytes to write
 * \return 0 for success, in error case the number of bytes not written
 */
int McuSemihost_SysFileWrite(int fh, const unsigned char *data, size_t nofBytes);

#if McuSemihost_CONFIG_HAS_SYS_REMOVE
/*!
 * \brief Remove a file on the host
 * \param filePath Name and path of the file to remove
 */
int McuSemihost_SysFileRemove(const unsigned char *filePath);
#endif

#if McuSemihost_CONFIG_HAS_SYS_RENAME
/*!
 * \brief Rename a file on the host
 * \param filePath Name and path of the source file
 * \param fileNewPath Name and path of new file
 */
int McuSemihost_SysFileRename(const unsigned char *filePath, const unsigned char *fileNewPath);
#endif

/*!
 * \brief Return the length of a file
 * \param fh File handle
 * \return Current length of the file, -1 for an error
 */
int McuSemihost_SysFileLen(int fh);

/*!
 * \brief Seeks for a specified position in a file
 * \param fh File handle
 * \param pos Target position. Seeking outside of the size of the file is undefined
 * \return 0 for success, negative for an error. McuSemihost_Op_SYS_ERRNO can be used to read the error value.
 */
int McuSemihost_SysFileSeek(int fh, int pos);

#if McuSemihost_CONFIG_HAS_SYS_TMPNAME
/*!
 * \brief Returns a temporary name for a file identified by a system file identifier.
 * \param fileID target identifier for the file name. Must be in the range 0..255
 * \param buffer Pointer where to store the file name
 * \param bufSize Buffer size in bytes
 * \return 0 for success, -1 for an error
 */
int McuSemihost_SysTmpName(uint8_t fileID, unsigned char *buffer, size_t bufSize);
#endif

/*!
 * \brief Read a character using SYS_READC
 * \return The character read
 */
int McuSemihost_SysReadC(void);

/*!
 * \brief Write a character using the SYS_WRITEC call.
 * \param ch Character to write
 * \return zero for success
 */
int McuSemihost_SysWriteC(char ch);


/*!
 * \brief Decides if a file handle is a standard io handle or not.
 * \param fg File handle
 * \return 1 if it a interactive device, 0 if not, any other value is an error
 */
int McuSemihost_SysIsTTY(int fh);

/*!
 * \brief Determines whether the return code from another semihosting call is an error status or not.
 * \param errorCode Return code from a previous semihosting call
 * \return 0 if it is not an error, non-zero if it is an error
 */
int McuSemihost_SysIsError(int32_t errorCode);

/*!
 * \brief Returns the value of the C library errno variable associated with the host implementation of the semihosting.
 *        The errno variable gets set by calls file operations, but others too.
 * \return The value of the host errno variable.
 */
int McuSemihost_SysErrNo(void);

/*!
 * \brief Returns the command line used for the call to the executable, that is, argc and argv.
 * \return 0 for success, -1 for error
 */
int McuSemihost_SysGetCmdLine(unsigned char *cmd, size_t cmdSize);

typedef struct McuSemihost_HeapInfo_t {
  uint32_t heap_base;
  uint32_t heap_limit;
  uint32_t stack_base;
  uint32_t stack_limit;
} McuSemihost_HeapInfo_t;

/*!
 * \brief Returns the system stack and heap parameters.
 * \param heapInfo Pointer to heap info to be filled in
 * \return 0 for success, non-zero otherwise
 */
int McuSemihost_SysHeapInfo(McuSemihost_HeapInfo_t *heapInfo);

/*!
 * \brief Sets the processor to supervisor mode and disables all interrupts
 * \return address to be called to return to user mode.
 */
int McuSemihost_SysEnterSVC(void);

typedef enum McuSemihost_Exception_e {
  McuSemihost_ADP_Stopped_ApplicationExit = 0x20026, /* exit target application */
} McuSemihost_Exception_e;

/*!
 * \brief Raises one of predefined excetptions to the debugger
 * \param exception Exception to be raised
 * \return 0 for success, non-zero otherwise
 */
int McuSemihost_SysException(McuSemihost_Exception_e exception);

/*!
 * \brief Return the tick frequency
 * \return Tick frequency, -1 if debugger does not know the value of one tick
 */
int McuSemihost_SysTickFreq(void);

/*!
 * \brief Reads a line from user input. Call is blocking, and user has to press enter. Buffer will be always zero terminated.
 * \param buf Buffer to store the user input. If buffer is too small, excess characters are not stored in it and discarded.
 * \param bufSize Size of the buffer
 * \return Number of characters stored in the buffer.
 */
int McuSemihost_ReadLine(unsigned char *buf, size_t bufSize);

/*!
 * \brief Write a zero byte terminated character array (string) to stdout, using buffering.
 * \param str String, zero byte terminated
 * \return 0: ok, -1 error
 */
int McuSemihost_WriteString(const unsigned char *str);

/*!
 * \brief Write a zero byte terminated character array without buffering directly to the debugger.
 * \param str String, zero byte terminated
 * \return 0: ok, -1 error
 */
int McuSemihost_WriteString0(const unsigned char *str);

/*!
 * \brief Sending a character to the SWO/ITM console
 * \param ch Character to send
 */
void McuSemihost_StdIOSendChar(uint8_t ch);

/*!
 * \brief Reads a character from the standard input
 * \param ch Pointer where to store the character, stores '\0' if no character was received
 */
void McuSemihost_StdIOReadChar(uint8_t *ch);

/*!
 * \brief Checks if there is input from SWO/ITM console
 * \return true if there is input, false otherwise
 */
bool McuSemihost_StdIOKeyPressed(void);

/*!
 * \brief 'printf'-style writing with semihosting
 * \param fmt Format string
 * \return Number of characters written
 */
unsigned McuSemihost_printf(const char *fmt, ...);

/*!
 * \brief Get the date and time from the host
 * \param time Pointer to where to store the time information
 * \param date Pointer to where to store the date information
 * \param offsetHour Pass -1 if during wintertime
 * \return ERR_OK if ok, error code otherwise
 */
uint8_t McuSemihost_GetTimeDateFromHost(TIMEREC *time, DATEREC *date, int offsetHour);

/*!
 * \brief Testing the semihost functionality and API
 * \return 0 for success, -1 for error
 */
int McuSemiHost_Test(void);

/*!
 * \brief Module de-initialization
 */
void McuSemiHost_Deinit(void);

/*!
 * \brief Module initialization
 */
void McuSemiHost_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCUSEMIHOST_H_ */

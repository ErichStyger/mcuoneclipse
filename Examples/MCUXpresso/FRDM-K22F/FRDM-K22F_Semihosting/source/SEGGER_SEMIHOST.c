/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*            (c) 2019 SEGGER Microcontroller GmbH                    *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* condition is met:                                                  *
*                                                                    *
* o Redistributions of source code must retain the above copyright   *
*   notice, this condition and the following disclaimer.             *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED. IN NO EVENT SHALL SEGGER Microcontroller BE LIABLE FOR *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : SEGGER_SEMIHOST.c
Purpose : Semihosting implementation for standard I/O functions,
          such as terminal input and output according to the SEGGER 
          semihosting specification.
Literature:
  [1]  https://wiki.segger.com/SEGGER_Semihosting
  [2]  https://wiki.segger.com/Semihosting

*/

#define SEGGER_SEMIHOST_C       // Used to control "extern" statements of global variables specified by this module
#include "SEGGER_SEMIHOST.h"

//
// Semihosting operations,
// compatible to operations defined by ARM
//
#define SYS_OPEN                        0x01
#define SYS_CLOSE                       0x02
#define SYS_WRITEC                      0x03
#define SYS_WRITE0                      0x04
#define SYS_WRITE                       0x05
#define SYS_READ                        0x06
#define SYS_READC                       0x07
#define SYS_ISERROR                     0x08
#define SYS_ISTTY                       0x09
#define SYS_SEEK                        0x0A

#define SYS_FLEN                        0x0C
#define SYS_TMPNAME                     0x0D
#define SYS_REMOVE                      0x0E
#define SYS_RENAME                      0x0F
#define SYS_CLOCK                       0x10
#define SYS_TIME                        0x11
#define SYS_SYSTEM                      0x12
#define SYS_ERRNO                       0x13

#define SYS_GET_CMDLINE                 0x15
#define SYS_HEAPINFO                    0x16

#define SYS_EXIT                        0x18 // ARM's operation name: angel_SWIreason_ReportException

#define SYS_ELAPSED                     0x30
#define SYS_TICKFREQ                    0x31
//
// SEGGER Extensions
//
#define SYS_IS_CONNECTED                0x00
#define SYS_WRITEF                      0x40

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/
/*********************************************************************
*
*       SEGGER_SEMIHOST_Open()
*
*  Function description
*    Open a file on the host system.
*
*  Parameters
*    sFilename:     Pointer to the null-terminated filename.
*    Mode:          The opening mode. (See SYS_FILE_MODE_*).
*    LenFilename:   Length of the filename without the terminating 0.
*
*  Return value
*     = -1: Error. Call not successful.
*    !=  0: OK. File handle.
*/
int SEGGER_SEMIHOST_Open(const char* sFilename, int Mode, int LenFilename) {
  SEGGER_SEMIHOST_PARA  aPara[3];
  int                   r;
  
  aPara[0].cpC  = sFilename;
  aPara[1].I    = Mode;
  aPara[2].I    = LenFilename;
  r = SEGGER_SEMIHOST_X_Request(SYS_OPEN, aPara);
  
  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_Close()
*
*  Function description
*    Close an open file on the host system.
*
*  Parameters
*    hFile:     Handle to the open file.
*
*  Return value
*    =  0: OK.
*    = -1: Error. Call not successful.
*/
int SEGGER_SEMIHOST_Close(int hFile) {
  SEGGER_SEMIHOST_PARA  Para; 
  int                   r;
  
  Para.pV = (void*)hFile;
  r = SEGGER_SEMIHOST_X_Request(SYS_CLOSE, &Para);

  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_WriteC()
*
*  Function description
*    Write one character to the debug channel on the host system.
*
*  Parameters
*    c:   Character to write
*
*  Return value
*     = -1: Error.
*/
int SEGGER_SEMIHOST_WriteC(char c) {
  int r;

  r = SEGGER_SEMIHOST_X_Request(SYS_WRITEC, (SEGGER_SEMIHOST_PARA*)&c);
  
  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_Write0()
*
*  Function description
*    Write a 0-terminated string to debug channel on the host system.
*
*  Parameters
*    s:     Pointer to 0-terminated string.
*
*  Return value
*     = -1: Error.
*/
int SEGGER_SEMIHOST_Write0(const char* s) {
  int r;

  r = SEGGER_SEMIHOST_X_Request(SYS_WRITE0, (SEGGER_SEMIHOST_PARA*)s);
  
  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_Write()
*
*  Function description
*    Write Bytes to file on the host system.
*
*  Parameters
*    hFile:            Handle to the open file.
*    pBuffer:          Pointer to buffer to be written.
*    NumBytesToRead:   Number of Bytes in the buffer.
*
*  Return value
*     = -1: Error.
*     =  0: OK.
*    !=  0: Number of bytes remaining in the buffer.
*/
int SEGGER_SEMIHOST_Write(int hFile, const char* pBuffer, int NumBytesToWrite) {
  SEGGER_SEMIHOST_PARA  aPara[3];
  int                   r;
  
  aPara[0].I    = hFile;
  aPara[1].cpC  = pBuffer;
  aPara[2].I    = NumBytesToWrite;
  r = SEGGER_SEMIHOST_X_Request(SYS_WRITE, aPara);

  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_Writef()
*
*  Function description
*    Write a formatted string to debug channel on the host system.
*    The string is formatted on the host.
*
*  Parameters
*    pFormat:   Pointer to string to be formatted and printed.
*    aArg:      Arguments
*
*  Return value
*     = -1: Error.
*    >=  0: OK. Number of bytes printed.
*
*  Additional information
*    int myprintf(const char* s, ...) {
*      va_list List;
*    
*      va_start(List, s);
*      SEGGER_SEMIHOST_Writef(s, &List);
*      va_end(List);
*    
*      return 0;
*    }
*    
*/
int SEGGER_SEMIHOST_Writef(const char* pFormat, va_list* pArg) {
  SEGGER_SEMIHOST_PARA  aPara[2];
  int                   r;

  aPara[0].cpC = pFormat;
  aPara[1].pV  = (void*)pArg;
  r = SEGGER_SEMIHOST_X_Request(SYS_WRITEF, aPara);

  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_Read()
*
*  Function description
*    Read Bytes from a file into buffer.
*
*  Parameters
*    hFile:            Handle to the open file.
*    pBuffer:          Pointer to the buffer
*    NumBytesToRead:   Number of bytes to wanted to read.
*
*  Return value
*     = -1: Error.
*     =  0:               OK.
*    ==  NumBytesToRead:  Failed to read. EOF assumed.
*     <  NumBytesToRead:  Partially OK. Number of bytes free.
*/
int SEGGER_SEMIHOST_Read(int hFile, char* pBuffer, int NumBytesToRead) {
  SEGGER_SEMIHOST_PARA  aPara[3];
  int                   r;
  
  aPara[0].I  = hFile;
  aPara[1].pC = pBuffer;
  aPara[2].I  = NumBytesToRead;
  r = SEGGER_SEMIHOST_X_Request(SYS_READ, aPara);

  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_ReadC()
*
*  Function description
*    Reads a byte from console of the host.
*
*  Return value
*     = -1: Error.
*    != -1: Byte read from the console.
*/
int SEGGER_SEMIHOST_ReadC(void) {
  int   r;
  
  r = SEGGER_SEMIHOST_X_Request(SYS_READC, (SEGGER_SEMIHOST_PARA*)0);

  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_IsTTY()
*
*  Function description
*    Checks if a file handle belongs to an interactive terminal.
*
*  Parameters
*    hFile:            Handle to the open file.
*
*  Return value
*     = -1:     Error.
*    =  1:      Interactive terminal identified.
*    =  0:      File identified.
*    Else:      Error.
*/
int SEGGER_SEMIHOST_IsTTY(int hFile) {
  SEGGER_SEMIHOST_PARA  Para;
  int   r;
  
  Para.I = hFile;
  r = SEGGER_SEMIHOST_X_Request(SYS_ISTTY, &Para);

  return r;	
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_Seek()
*
*  Function description
*    Set file cursor to position offset (from file start).
*
*  Parameters
*    hFile:            Handle to the open file.
*    Pos:              Position offset.
*
*  Return value
*    = 0: OK.
*    < 0: Error.
*/
int SEGGER_SEMIHOST_Seek(int hFile, int Pos) {
  SEGGER_SEMIHOST_PARA  aPara[2];
  int                   r;
  
  aPara[0].I = hFile;
  aPara[1].I = Pos;
  r = SEGGER_SEMIHOST_X_Request(SYS_SEEK, aPara);

  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_FLen()
*
*  Function description
*    Get the length of a file.
*
*  Parameters
*    hFile:            Handle to the open file.
*    
*  Return value
*    >= 0:  OK. Length of the file.
*    -1:    Error.
*/
int SEGGER_SEMIHOST_FLen(int hFile) {
  SEGGER_SEMIHOST_PARA  Para;
  int                   r;
  
  Para.I = hFile;
  r = SEGGER_SEMIHOST_X_Request(SYS_FLEN, &Para);

  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_GetCmdLine()
*
*  Function description
*    Get command line for executable called 
*
*  Parameters
*    pBuffer:           Pointer to buffer to store command line.
*    psCmdLine:         Pointer to store pointer to command line to.
*    pNumBytesCmdLine:  [In]  Number of bytes in the buffer. 
*                       [Out] Lenght of the command line pointed to by psCmdLine.
*
*  Return value
*     = 0:  OK.
*     = -1: Error. Call not successful.
*/
int SEGGER_SEMIHOST_GetCmdLine(char* pBuffer, char** psCmdLine, int* pNumBytesCmdLine) {
  SEGGER_SEMIHOST_PARA  aPara[2];
  int                   r;
  
  aPara[0].pC = (void*)pBuffer;
  aPara[1].pV = (void*)(*pNumBytesCmdLine);
  r = SEGGER_SEMIHOST_X_Request(SYS_GET_CMDLINE, aPara);
  
  if (r == 0) {
    *psCmdLine        = aPara[0].pC;
    *pNumBytesCmdLine = aPara[1].I;
  }
  
  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_TmpName()
*
*  Function description
*    Get a temporary file name.
*
*  Parameters
*    pBuffer:           [IN]  Pointer to buffer for the file name.
*                       [OUT] Pointer to the absolute filename path.
*    FileId:            ID of the temporary file to get (0-255)
*    NumBytesBuffer:    Size of the buffer.
*
*  Return value
*     = 0:  OK.
*     = -1: Error. Call not successful.
*/
int SEGGER_SEMIHOST_TmpName(char* pBuffer, int FileId, int NumBytesBuffer) {
  SEGGER_SEMIHOST_PARA  aPara[3];
  int                   r;
  
  aPara[0].pC = pBuffer;
  aPara[1].I  = FileId;
  aPara[2].I  = NumBytesBuffer;
  r = SEGGER_SEMIHOST_X_Request(SYS_TMPNAME, aPara);
  
  if (r == 0) {
    pBuffer = aPara[0].pC;
  }
  
  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_Remove()
*
*  Function description
*    Deletes file on host system
*
*  Parameters
*    pPath:         Pointer to the path of file to be deleted(null-terminated).
*    NumBytesPath:  Length of path string.
*
*  Return value
*     =  0: OK. Delete successful.
*    !=  0: Error.
*/
int SEGGER_SEMIHOST_Remove(const char* pPath, int NumBytesPath) {
  SEGGER_SEMIHOST_PARA  aPara[2];
  int                   r;
  
  aPara[0].cpC  = pPath;
  aPara[1].I    = NumBytesPath;
  r = SEGGER_SEMIHOST_X_Request(SYS_REMOVE, aPara);
  
  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_Rename()
*
*  Function description
*    Renames file
*
*  Parameters
*    pFileName:         Pointer to the name of file to be changed(null-terminated).
*    NumBytesFileName:  Length of file name string.
*    pNewName:          Pointer to the wanted name of file(null-terminated).
*    NumBytesNewName:   Length of new name string.
*
*  Return value
*     =  0: OK.
*    !=  0: Error.
*/
int SEGGER_SEMIHOST_Rename(const char* pFileName, int NumBytesFileName, const char* pNewName, int NumBytesNewName) {
  SEGGER_SEMIHOST_PARA  aPara[4];
  int                   r;
  
  aPara[0].cpC  = pFileName;
  aPara[1].I    = NumBytesFileName;
  aPara[2].cpC  = pNewName;
  aPara[3].I    = NumBytesNewName;
  r = SEGGER_SEMIHOST_X_Request(SYS_RENAME, aPara);
  
  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_Clock()
*
*  Function description
*    Returns the number of centiseconds this executable is running.
*    (R1 must contain zero).
*
*  Return value
*     = -1: Error.
*    != -1: Number of centiseconds the execution runs.
*/
int SEGGER_SEMIHOST_Clock(void) {
  int   r;
  
  r = SEGGER_SEMIHOST_X_Request(SYS_CLOCK, (SEGGER_SEMIHOST_PARA*)0);
  
  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_Time()
*
*  Function description
*    Returns UNIX timestamp.
*
*  Return value
*    !=  0: Number of seconds.
*/
int SEGGER_SEMIHOST_Time(void) {
  int   r;
  
  r = SEGGER_SEMIHOST_X_Request(SYS_TIME, (SEGGER_SEMIHOST_PARA*)0);
  
  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_System()
*
*  Function description
*    Host command-line interpreter.
*
*  Parameters
*    pCommand:         Pointer to the command string.
*    NumBytesCommand:  Length of command string.
*
*  Return value
*    Return status of command.
*/
int SEGGER_SEMIHOST_System(const char* pCommand, int NumBytesCommand) {
  SEGGER_SEMIHOST_PARA  aPara[2];
  int                   r;
  
  aPara[0].cpC  = pCommand;
  aPara[1].I    = NumBytesCommand;

  r = SEGGER_SEMIHOST_X_Request(SYS_SYSTEM, aPara);
  
  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_Errno()
*
*  Function description
*    Returns value of C Library 'errno' of host.
*
*
*  Return value
*    return calue of C library errno
*/
int SEGGER_SEMIHOST_Errno(void) {
  int   r;

  r = SEGGER_SEMIHOST_X_Request(SYS_ERRNO, (SEGGER_SEMIHOST_PARA*)0);
  
  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_Exit()
*
*  Function description
*    Reports exit of the application to terminate the debug session.
*
*  Parameters
*    ExitCode:         Return value of the application.
*                      Typically >= 0: no error, < 0: Error
*  Return value
*     Do not care.
*/
int SEGGER_SEMIHOST_Exit(int ExitCode) {
  SEGGER_SEMIHOST_PARA  Para;
  int                   r;
  
  Para.I = ExitCode;
  r = SEGGER_SEMIHOST_X_Request(SYS_EXIT, &Para);

  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_IsConnected()
*
*  Function description
*    Check whether a semihost handling debugger is connected or not.
*
*  Return value
*    != 1: No debugger connected.
*    == 1: Debugger connected.
*/
int SEGGER_SEMIHOST_IsConnected(void) {
  int r;

  r = SEGGER_SEMIHOST_X_Request(SYS_IS_CONNECTED, (SEGGER_SEMIHOST_PARA*)0);

  return r;
}

/*********************************************************************
*
*       SEGGER_SEMIHOST_DebugHalt()
*
*  Function description
*    Dummy call for generic implementation.
*    The debugger may set a breakpoint on this function, 
*    handle the semihosting request,
*    and return to the caller.
*
*  Return value
*    Return parameter r0 if debugger is not connected.
*/
int __attribute__((noinline)) SEGGER_SEMIHOST_DebugHalt(int r0, int r1) {
  (void)r1;   // Avoid unused parameter warning
  return r0;
}

/*************************** End of file ****************************/

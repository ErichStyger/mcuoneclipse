/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    FRDM-K22F_Semihosting.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK22F51212.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "SEGGER_SEMIHOST.h"

#define _FILENAME_OPEN    "c:\\tmp\\test_semihosting.txt"
#define _FILENAME_RENAME  "c:\\tmp\\test_semihosting_renamed.txt"
#define _FILENAME_REMOVE  "c:\\tmp\\test_semihosting_removed.txt"

static int FileOpen(void) {
  int hFile;
  int r;
  char buf[24];

  SEGGER_SEMIHOST_Write0("Opening file on host system (SYS_OPEN)):\n");
  SEGGER_SEMIHOST_Write0(_FILENAME_OPEN);
  SEGGER_SEMIHOST_Write0("\n");
  hFile = SEGGER_SEMIHOST_Open(_FILENAME_OPEN, SYS_FILE_MODE_WRITEREADBINARY, strlen(_FILENAME_OPEN));
  if (hFile == -1) {
    SEGGER_SEMIHOST_Write0("Failed");
  } else {
    SEGGER_SEMIHOST_Write0("OK");
  }
  SEGGER_SEMIHOST_Close(hFile);

  /* writing to file */
  const char *msg = "test file write";

  hFile = SEGGER_SEMIHOST_Open(_FILENAME_OPEN, SYS_FILE_MODE_WRITEREADBINARY, strlen(_FILENAME_OPEN));
  if (hFile == -1) {
    SEGGER_SEMIHOST_Write0("Failed");
  } else {
    SEGGER_SEMIHOST_Write0("OK");
  }
  r = SEGGER_SEMIHOST_Write(hFile, msg, strlen(msg));
  if (r != 0) {
   SEGGER_SEMIHOST_Write0("Failed");
  } else {
   SEGGER_SEMIHOST_Write0("OK");
  }
  SEGGER_SEMIHOST_Close(hFile);

  /* reading from file */

  hFile = SEGGER_SEMIHOST_Open(_FILENAME_OPEN, SYS_FILE_MODE_WRITEREADBINARY, strlen(_FILENAME_OPEN));
  if (hFile == -1) {
    SEGGER_SEMIHOST_Write0("Failed");
  } else {
    SEGGER_SEMIHOST_Write0("OK");
  }
  SEGGER_SEMIHOST_Write0("Reading from file:\n");
  memset(buf, 0, sizeof(buf));
  r = SEGGER_SEMIHOST_Read(hFile, buf, sizeof(buf));
  if (r < 0) {
    SEGGER_SEMIHOST_Write0("Failed");
  } else if (r == sizeof(buf)) {
    SEGGER_SEMIHOST_Write0("Failed. Read EOF");
  } else {
    SEGGER_SEMIHOST_Write((int)stdout, buf, sizeof(buf) - r);
    SEGGER_SEMIHOST_Write0("\n");
    snprintf(buf, sizeof(buf), "Read %d bytes\n", sizeof(buf) - r);
    SEGGER_SEMIHOST_Write0(buf);
    SEGGER_SEMIHOST_Write0("OK");
  }
  SEGGER_SEMIHOST_Close(hFile);

  /* seek position in file */
  hFile = SEGGER_SEMIHOST_Open(_FILENAME_OPEN, SYS_FILE_MODE_WRITEREADBINARY, strlen(_FILENAME_OPEN));
  if (hFile == -1) {
    SEGGER_SEMIHOST_Write0("Failed");
  } else {
    SEGGER_SEMIHOST_Write0("OK");
  }
  r = SEGGER_SEMIHOST_Seek(hFile, 6);
   if (r != 0) {
     SEGGER_SEMIHOST_Write0("Failed");
   } else {
     SEGGER_SEMIHOST_Write0("OK");
   }
   /* file len */
   r = SEGGER_SEMIHOST_FLen(hFile);
    if (r >= 0) {
      snprintf(buf, sizeof(buf), "Filesize: %d\n", r);
      SEGGER_SEMIHOST_Write0(buf);
      SEGGER_SEMIHOST_Write0("OK");
    } else {
      SEGGER_SEMIHOST_Write0("Failed");
    }
    SEGGER_SEMIHOST_Close(hFile);



  /* removing a file */
  hFile = SEGGER_SEMIHOST_Open(_FILENAME_REMOVE, SYS_FILE_MODE_WRITEBINARY, strlen(_FILENAME_REMOVE));
  if (hFile == -1) {
    SEGGER_SEMIHOST_Write0("Failed to create file");
  } else {
    SEGGER_SEMIHOST_Close(hFile);
  }

  r = SEGGER_SEMIHOST_Remove(_FILENAME_REMOVE, strlen(_FILENAME_REMOVE));
  if (r != 0) {
    SEGGER_SEMIHOST_Write0("Failed");
  } else {
    SEGGER_SEMIHOST_Write0("OK");
  }
  SEGGER_SEMIHOST_Close(hFile);

   /* renaming a file */
  r = SEGGER_SEMIHOST_Rename(_FILENAME_OPEN, strlen(_FILENAME_OPEN), _FILENAME_RENAME, strlen(_FILENAME_RENAME));
  if (r != 0) {
    SEGGER_SEMIHOST_Write0("Failed");
  } else {
    SEGGER_SEMIHOST_Write0("OK");
  }


  return hFile;
}

static void WriteString(const char *str) {
  /* writing string character by character */
  while(*str!='\0') {
    SEGGER_SEMIHOST_WriteC(*str);
    str++;
  }
}

static void various(void) {
  int val;

  val = SEGGER_SEMIHOST_IsConnected();
  if (val==1) {
    printf("Debugger is connected\n");
  } else {
    printf("Debugger is connected\n");
  }
  val = SEGGER_SEMIHOST_Clock(); /* always 1? */
  printf("Centiseconds target is running: %d\n", val);

  val = SEGGER_SEMIHOST_Time();
  printf("host Unix time stamp (seconds): %d\n", val);

  val = SEGGER_SEMIHOST_Errno();
  printf("errno on the host: %d\n", val);

  val = SEGGER_SEMIHOST_System("cmd.exe", sizeof("cmd.exe")-1); /* fails? */
  printf("system call return code: %d\n", val);

  (void)SEGGER_SEMIHOST_Exit(1); /* close debug session */
}

static void SysWrite(void) {
  char* sMsg;

  sMsg = "Writing string (SYS_WRITE):\n";
  SEGGER_SEMIHOST_Write(SEGGER_SEMIHOST_STDOUT, sMsg, strlen(sMsg)); /* does not work? */
  sMsg = "This string is written to errout\n";
  SEGGER_SEMIHOST_Write(SEGGER_SEMIHOST_ERROUT, sMsg, strlen(sMsg)); /* does not work? */
  SEGGER_SEMIHOST_Write0("OK\n");
  SEGGER_SEMIHOST_Write0("=============================\n");
}

static int myPrintf(const char* s, ...) {
  va_list List;

  va_start(List, s);
  SEGGER_SEMIHOST_Writef(s, &List); /* format parsing is done on the host! */
  va_end(List);

  return 0;
}

static void _Test_SYS_WRITEF(const char* sFmt, ...) {
  va_list List;
  int     r;

  va_start(List, sFmt);

  SEGGER_SEMIHOST_Write0("Writing host-formatted string (SYS_WRITEF):\n");
  r =SEGGER_SEMIHOST_Writef(sFmt, &List);
  if (r < 0) {
    SEGGER_SEMIHOST_Write0("Failed.\n");
  } else {
    SEGGER_SEMIHOST_Write0("OK\n");
  }
  SEGGER_SEMIHOST_Write0("=============================\n");

  va_end(List);
}

static void ReadUserInputString(void) {
  char buf[32];
  int res;

  SEGGER_SEMIHOST_Write0("Please enter some text and press <ENTER>):\n");
  memset(buf, 0, sizeof(buf)); /* init */
  res = SEGGER_SEMIHOST_Read(SEGGER_SEMIHOST_STDIN, buf, sizeof(buf)); /* does not work */
  if (res<0) {
    SEGGER_SEMIHOST_Write0("Failed\n");
  } else {
    SEGGER_SEMIHOST_Write0("You entered:\n");
    SEGGER_SEMIHOST_Write(SEGGER_SEMIHOST_STDOUT, buf, sizeof(buf) - res); /* does not work */
  }
}

static void ConsoleInputOutput(void) {
  /* test of console input and output */
  int c;

  SEGGER_SEMIHOST_Write0("Please enter a key (and press <ENTER>):\n"); /* writing zero terminated string */
  do {
    c = SEGGER_SEMIHOST_ReadC();
  } while(c==EOF);
  printf("You entered: %c\n", c);
}

int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    ConsoleInputOutput();
    ReadUserInputString();
    SysWrite();
    FileOpen();
    WriteString("hello world!\n");
    _Test_SYS_WRITEF("Value is '%d'\n", 1234); /* fails */
    various();

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}

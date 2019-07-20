/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*            (c) 1995 - 2018 SEGGER Microcontroller GmbH             *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER RTT * Real Time Transfer for embedded targets         *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* SEGGER strongly recommends to not make any changes                 *
* to or modify the source code of this software in order to stay     *
* compatible with the RTT protocol and J-Link.                       *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* conditions are met:                                                *
*                                                                    *
* o Redistributions of source code must retain the above copyright   *
*   notice, this list of conditions and the following disclaimer.    *
*                                                                    *
* o Redistributions in binary form must reproduce the above          *
*   copyright notice, this list of conditions and the following      *
*   disclaimer in the documentation and/or other materials provided  *
*   with the distribution.                                           *
*                                                                    *
* o Neither the name of SEGGER Microcontroller GmbH         *
*   nor the names of its contributors may be used to endorse or      *
*   promote products derived from this software without specific     *
*   prior written permission.                                        *
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
*                                                                    *
*       RTT version: 6.32b                                           *
*                                                                    *
**********************************************************************
---------------------------END-OF-HEADER------------------------------
File    : SEGGER_RTT_Syscalls_GCC.c
Purpose : Low-level functions for using printf() via RTT in GCC.
          To use RTT for printf output, include this file in your 
          application.
Revision: $Rev: 9599 $
----------------------------------------------------------------------
*/
#if (defined __GNUC__) && !(defined __SES_ARM) && !(defined __CROSSWORKS_ARM)

#if 0 /* << EST moved to below */
#include <reent.h>  // required for _write_r
#endif
#include "SEGGER_RTT.h"

#if RTT1_CONFIG_PROVIDE_SYSCALLS /* << EST */
#include <stdio.h> /* for EOF */ /* << EST */
#include <reent.h>  // required for _write_r  // << EST moved from above

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
//
// If necessary define the _reent struct 
// to match the one passed by the used standard library.
//
struct _reent;

/*********************************************************************
*
*       Function prototypes
*
**********************************************************************
*/
#if 0
int _write(int file, char *ptr, int len);
int _write_r(struct _reent *r, int file, const void *ptr, int len);
#else /* << EST */
extern int _write(int file, char *ptr, int len);
extern _ssize_t  _write_r(struct _reent *r, int file, const void *ptr, size_t len);
#endif

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

/*********************************************************************
*
*       _write()
*
* Function description
*   Low-level write function.
*   libc subroutines will use this system routine for output to all files,
*   including stdout.
*   Write data via RTT.
*/
int _write(int file, char *ptr, int len) {
  (void) file;  /* Not used, avoid warning */
  SEGGER_RTT_Write(0, ptr, len);
  return len;
}

/*********************************************************************
*
*       _write_r()
*
* Function description
*   Low-level reentrant write function.
*   libc subroutines will use this system routine for output to all files,
*   including stdout.
*   Write data via RTT.
*/
#if 0
int _write_r(struct _reent *r, int file, const void *ptr, int len) {
#else /* << EST */
_ssize_t  _write_r(struct _reent *r, int file, const void *ptr, size_t len) {
#endif
  (void) file;  /* Not used, avoid warning */
  (void) r;     /* Not used, avoid warning */
  SEGGER_RTT_Write(0, ptr, len);
  return len;
}

int _putc(int c, __FILE *fp) { /* << EST */
  char ch = c;
  (void)fp;  /* Not used, avoid warning */
  SEGGER_RTT_Write(0, &ch, 1);
  return 1;
}

int _putchar(int c) { /* << EST */
  char ch = c;
  SEGGER_RTT_Write(0, &ch, 1);
  return 1;
}

int _getc(__FILE *fp) { /* << EST */
  char ch;
  (void)fp;  /* Not used, avoid warning */
  if (SEGGER_RTT_Read(0, &ch, 1)==0) {
    return EOF;
  }
  return ch;
}

int _read(void) {
  uint8_t ch;
  if (SEGGER_RTT_Read(0, &ch, 1)==0) {
    return EOF;
  }
  return (int)ch;
}

int __attribute__((weak)) _isatty(int file __attribute__((unused))) {
  return 1;
}

int __attribute__((weak)) _close(int fildes __attribute__((unused))) {
  return -1;
}

int __attribute__((weak)) _lseek(int file __attribute__((unused)), int ptr __attribute__((unused)), int dir __attribute__((unused))) {
  return -1;
}

#if 0
int __attribute__((weak)) _fstat (int fd __attribute__((unused)), struct stat *st)
{
  memset (st, 0, sizeof(*st));
  st->st_mode = S_IFCHR;
  return 0;
}
#endif


#endif /* RTT1_CONFIG_PROVIDE_SYSCALLS */ /* << EST */

#endif
/****** End Of File *************************************************/


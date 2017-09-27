/*----------------------------------------------------------------------------/
/  FatFs - FAT file system module  R0.12                 (C)ChaN, 2016        /
/-----------------------------------------------------------------------------/
/ FatFs module is a free software that opened under license policy of
/ following conditions.
/
/ Copyright (C) 2016, ChaN, all right reserved.
/
/ 1. Redistributions of source code must retain the above copyright notice,
/    this condition and the following disclaimer.
/
/ This software is provided by the copyright holder and contributors "AS IS"
/ and any warranties related to this software are DISCLAIMED.
/ The copyright owner or contributors be NOT LIABLE for any damages caused
/ by use of this software.
/----------------------------------------------------------------------------*/


#include "ff.h"     /* Declarations of FatFs API */
#include "diskio.h"   /* Declarations of disk I/O functions */

#ifdef __HIWARE__ /* << EST supress warning for C89 compilers */
  /* switching off some warnings */
  #pragma MESSAGE DISABLE C5909 /* assignment in condition */
  #pragma MESSAGE DISABLE C2705 /* possible loss of data */
  #pragma MESSAGE DISABLE C4000 /* condition always is false */
  #pragma MESSAGE DISABLE C4001 /* condition always is true */
  #pragma MESSAGE DISABLE C5703 /* parameter declared but not used */
  #pragma MESSAGE DISABLE C5904 /* Division by one */
  #pragma MESSAGE DISABLE C5905 /* Multiplication with one */
  #pragma MESSAGE DISABLE C5917 /* Removed dead assignment */
#endif

/*--------------------------------------------------------------------------

   Module Private Definitions

---------------------------------------------------------------------------*/

#if _FATFS != 88100 /* Revision ID */
#error Wrong include file (ff.h).
#endif


/* Reentrancy related */
#if _FS_REENTRANT
#if _USE_LFN == 1
#error Static LFN work area cannot be used at thread-safe configuration
#endif
#define ENTER_FF(fs)    { if (!lock_fs(fs)) return FR_TIMEOUT; }
#define LEAVE_FF(fs, res) { unlock_fs(fs, res); return res; }
#else
#define ENTER_FF(fs)
#define LEAVE_FF(fs, res) return res
#endif

#define ABORT(fs, res)    { fp->err = (BYTE)(res); LEAVE_FF(fs, res); }


/* Definitions of sector size */
#if (_MAX_SS < _MIN_SS) || (_MAX_SS != 512 && _MAX_SS != 1024 && _MAX_SS != 2048 && _MAX_SS != 4096) || (_MIN_SS != 512 && _MIN_SS != 1024 && _MIN_SS != 2048 && _MIN_SS != 4096)
#error Wrong sector size configuration
#endif
#if _MAX_SS == _MIN_SS
#define SS(fs)  ((UINT)_MAX_SS) /* Fixed sector size */
#else
#define SS(fs)  ((fs)->ssize) /* Variable sector size */
#endif


/* Timestamp */
#if _FS_NORTC == 1
#if _NORTC_YEAR < 1980 || _NORTC_YEAR > 2107 || _NORTC_MON < 1 || _NORTC_MON > 12 || _NORTC_MDAY < 1 || _NORTC_MDAY > 31
#error Invalid _FS_NORTC settings
#endif
#define GET_FATTIME() ((DWORD)(_NORTC_YEAR - 1980) << 25 | (DWORD)_NORTC_MON << 21 | (DWORD)_NORTC_MDAY << 16)
#else
#define GET_FATTIME() get_fattime()
#endif


/* File lock controls */
#if _FS_LOCK != 0
#if _FS_READONLY
#error _FS_LOCK must be 0 at read-only configuration
#endif
typedef struct {
  FATFS *fs;    /* Object ID 1, volume (NULL:blank entry) */
  DWORD clu;    /* Object ID 2, directory (0:root) */
  DWORD ofs;    /* Object ID 3, directory offset */
  WORD ctr;   /* Object open counter, 0:none, 0x01..0xFF:read mode open count, 0x100:write mode */
} FILESEM;
#endif



/* DBCS code ranges and SBCS upper conversion tables */

#if _CODE_PAGE == 932 /* Japanese Shift-JIS */
#define _DF1S 0x81  /* DBC 1st byte range 1 start */
#define _DF1E 0x9F  /* DBC 1st byte range 1 end */
#define _DF2S 0xE0  /* DBC 1st byte range 2 start */
#define _DF2E 0xFC  /* DBC 1st byte range 2 end */
#define _DS1S 0x40  /* DBC 2nd byte range 1 start */
#define _DS1E 0x7E  /* DBC 2nd byte range 1 end */
#define _DS2S 0x80  /* DBC 2nd byte range 2 start */
#define _DS2E 0xFC  /* DBC 2nd byte range 2 end */

#elif _CODE_PAGE == 936 /* Simplified Chinese GBK */
#define _DF1S 0x81
#define _DF1E 0xFE
#define _DS1S 0x40
#define _DS1E 0x7E
#define _DS2S 0x80
#define _DS2E 0xFE

#elif _CODE_PAGE == 949 /* Korean */
#define _DF1S 0x81
#define _DF1E 0xFE
#define _DS1S 0x41
#define _DS1E 0x5A
#define _DS2S 0x61
#define _DS2E 0x7A
#define _DS3S 0x81
#define _DS3E 0xFE

#elif _CODE_PAGE == 950 /* Traditional Chinese Big5 */
#define _DF1S 0x81
#define _DF1E 0xFE
#define _DS1S 0x40
#define _DS1E 0x7E
#define _DS2S 0xA1
#define _DS2E 0xFE

#elif _CODE_PAGE == 437 /* U.S. */
#define _DF1S 0
#define _EXCVT {0x80,0x9A,0x45,0x41,0x8E,0x41,0x8F,0x80,0x45,0x45,0x45,0x49,0x49,0x49,0x8E,0x8F, \
        0x90,0x92,0x92,0x4F,0x99,0x4F,0x55,0x55,0x59,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
        0x41,0x49,0x4F,0x55,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

#elif _CODE_PAGE == 720 /* Arabic */
#define _DF1S 0
#define _EXCVT {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

#elif _CODE_PAGE == 737 /* Greek */
#define _DF1S 0
#define _EXCVT {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
        0x90,0x92,0x92,0x93,0x94,0x95,0x96,0x97,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87, \
        0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,0x90,0x91,0xAA,0x92,0x93,0x94,0x95,0x96, \
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
        0x97,0xEA,0xEB,0xEC,0xE4,0xED,0xEE,0xEF,0xF5,0xF0,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

#elif _CODE_PAGE == 771 /* KBL */
#define _DF1S 0
#define _EXCVT {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDC,0xDE,0xDE, \
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
        0xF0,0xF0,0xF2,0xF2,0xF4,0xF4,0xF6,0xF6,0xF8,0xF8,0xFA,0xFA,0xFC,0xFC,0xFE,0xFF}

#elif _CODE_PAGE == 775 /* Baltic */
#define _DF1S 0
#define _EXCVT {0x80,0x9A,0x91,0xA0,0x8E,0x95,0x8F,0x80,0xAD,0xED,0x8A,0x8A,0xA1,0x8D,0x8E,0x8F, \
        0x90,0x92,0x92,0xE2,0x99,0x95,0x96,0x97,0x97,0x99,0x9A,0x9D,0x9C,0x9D,0x9E,0x9F, \
        0xA0,0xA1,0xE0,0xA3,0xA3,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
        0xB5,0xB6,0xB7,0xB8,0xBD,0xBE,0xC6,0xC7,0xA5,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
        0xE0,0xE1,0xE2,0xE3,0xE5,0xE5,0xE6,0xE3,0xE8,0xE8,0xEA,0xEA,0xEE,0xED,0xEE,0xEF, \
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

#elif _CODE_PAGE == 850 /* Latin 1 */
#define _DF1S 0
#define _EXCVT {0x43,0x55,0x45,0x41,0x41,0x41,0x41,0x43,0x45,0x45,0x45,0x49,0x49,0x49,0x41,0x41, \
        0x45,0x92,0x92,0x4F,0x4F,0x4F,0x55,0x55,0x59,0x4F,0x55,0x4F,0x9C,0x4F,0x9E,0x9F, \
        0x41,0x49,0x4F,0x55,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
        0xB0,0xB1,0xB2,0xB3,0xB4,0x41,0x41,0x41,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0x41,0x41,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
        0xD1,0xD1,0x45,0x45,0x45,0x49,0x49,0x49,0x49,0xD9,0xDA,0xDB,0xDC,0xDD,0x49,0xDF, \
        0x4F,0xE1,0x4F,0x4F,0x4F,0x4F,0xE6,0xE8,0xE8,0x55,0x55,0x55,0x59,0x59,0xEE,0xEF, \
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

#elif _CODE_PAGE == 852 /* Latin 2 */
#define _DF1S 0
#define _EXCVT {0x80,0x9A,0x90,0xB6,0x8E,0xDE,0x8F,0x80,0x9D,0xD3,0x8A,0x8A,0xD7,0x8D,0x8E,0x8F, \
        0x90,0x91,0x91,0xE2,0x99,0x95,0x95,0x97,0x97,0x99,0x9A,0x9B,0x9B,0x9D,0x9E,0xAC, \
        0xB5,0xD6,0xE0,0xE9,0xA4,0xA4,0xA6,0xA6,0xA8,0xA8,0xAA,0x8D,0xAC,0xB8,0xAE,0xAF, \
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBD,0xBF, \
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC6,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
        0xD1,0xD1,0xD2,0xD3,0xD2,0xD5,0xD6,0xD7,0xB7,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
        0xE0,0xE1,0xE2,0xE3,0xE3,0xD5,0xE6,0xE6,0xE8,0xE9,0xE8,0xEB,0xED,0xED,0xDD,0xEF, \
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xEB,0xFC,0xFC,0xFE,0xFF}

#elif _CODE_PAGE == 855 /* Cyrillic */
#define _DF1S 0
#define _EXCVT {0x81,0x81,0x83,0x83,0x85,0x85,0x87,0x87,0x89,0x89,0x8B,0x8B,0x8D,0x8D,0x8F,0x8F, \
        0x91,0x91,0x93,0x93,0x95,0x95,0x97,0x97,0x99,0x99,0x9B,0x9B,0x9D,0x9D,0x9F,0x9F, \
        0xA1,0xA1,0xA3,0xA3,0xA5,0xA5,0xA7,0xA7,0xA9,0xA9,0xAB,0xAB,0xAD,0xAD,0xAE,0xAF, \
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB6,0xB6,0xB8,0xB8,0xB9,0xBA,0xBB,0xBC,0xBE,0xBE,0xBF, \
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC7,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
        0xD1,0xD1,0xD3,0xD3,0xD5,0xD5,0xD7,0xD7,0xDD,0xD9,0xDA,0xDB,0xDC,0xDD,0xE0,0xDF, \
        0xE0,0xE2,0xE2,0xE4,0xE4,0xE6,0xE6,0xE8,0xE8,0xEA,0xEA,0xEC,0xEC,0xEE,0xEE,0xEF, \
        0xF0,0xF2,0xF2,0xF4,0xF4,0xF6,0xF6,0xF8,0xF8,0xFA,0xFA,0xFC,0xFC,0xFD,0xFE,0xFF}

#elif _CODE_PAGE == 857 /* Turkish */
#define _DF1S 0
#define _EXCVT {0x80,0x9A,0x90,0xB6,0x8E,0xB7,0x8F,0x80,0xD2,0xD3,0xD4,0xD8,0xD7,0x49,0x8E,0x8F, \
        0x90,0x92,0x92,0xE2,0x99,0xE3,0xEA,0xEB,0x98,0x99,0x9A,0x9D,0x9C,0x9D,0x9E,0x9E, \
        0xB5,0xD6,0xE0,0xE9,0xA5,0xA5,0xA6,0xA6,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC7,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
        0xD0,0xD1,0xD2,0xD3,0xD4,0x49,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
        0xE0,0xE1,0xE2,0xE3,0xE5,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xDE,0xED,0xEE,0xEF, \
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

#elif _CODE_PAGE == 860 /* Portuguese */
#define _DF1S 0
#define _EXCVT {0x80,0x9A,0x90,0x8F,0x8E,0x91,0x86,0x80,0x89,0x89,0x92,0x8B,0x8C,0x98,0x8E,0x8F, \
        0x90,0x91,0x92,0x8C,0x99,0xA9,0x96,0x9D,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
        0x86,0x8B,0x9F,0x96,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

#elif _CODE_PAGE == 861 /* Icelandic */
#define _DF1S 0
#define _EXCVT {0x80,0x9A,0x90,0x41,0x8E,0x41,0x8F,0x80,0x45,0x45,0x45,0x8B,0x8B,0x8D,0x8E,0x8F, \
        0x90,0x92,0x92,0x4F,0x99,0x8D,0x55,0x97,0x97,0x99,0x9A,0x9D,0x9C,0x9D,0x9E,0x9F, \
        0xA4,0xA5,0xA6,0xA7,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

#elif _CODE_PAGE == 862 /* Hebrew */
#define _DF1S 0
#define _EXCVT {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
        0x41,0x49,0x4F,0x55,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

#elif _CODE_PAGE == 863 /* Canadian-French */
#define _DF1S 0
#define _EXCVT {0x43,0x55,0x45,0x41,0x41,0x41,0x86,0x43,0x45,0x45,0x45,0x49,0x49,0x8D,0x41,0x8F, \
        0x45,0x45,0x45,0x4F,0x45,0x49,0x55,0x55,0x98,0x4F,0x55,0x9B,0x9C,0x55,0x55,0x9F, \
        0xA0,0xA1,0x4F,0x55,0xA4,0xA5,0xA6,0xA7,0x49,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

#elif _CODE_PAGE == 864 /* Arabic */
#define _DF1S 0
#define _EXCVT {0x80,0x9A,0x45,0x41,0x8E,0x41,0x8F,0x80,0x45,0x45,0x45,0x49,0x49,0x49,0x8E,0x8F, \
        0x90,0x92,0x92,0x4F,0x99,0x4F,0x55,0x55,0x59,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
        0x41,0x49,0x4F,0x55,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

#elif _CODE_PAGE == 865 /* Nordic */
#define _DF1S 0
#define _EXCVT {0x80,0x9A,0x90,0x41,0x8E,0x41,0x8F,0x80,0x45,0x45,0x45,0x49,0x49,0x49,0x8E,0x8F, \
        0x90,0x92,0x92,0x4F,0x99,0x4F,0x55,0x55,0x59,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
        0x41,0x49,0x4F,0x55,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

#elif _CODE_PAGE == 866 /* Russian */
#define _DF1S 0
#define _EXCVT {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
        0x90,0x91,0x92,0x93,0x9d,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
        0xF0,0xF0,0xF2,0xF2,0xF4,0xF4,0xF6,0xF6,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

#elif _CODE_PAGE == 869 /* Greek 2 */
#define _DF1S 0
#define _EXCVT {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x86,0x9C,0x8D,0x8F,0x90, \
        0x91,0x90,0x92,0x95,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xA4,0xA5,0xA6,0xD9,0xDA,0xDB,0xDC,0xA7,0xA8,0xDF, \
        0xA9,0xAA,0xAC,0xAD,0xB5,0xB6,0xB7,0xB8,0xBD,0xBE,0xC6,0xC7,0xCF,0xCF,0xD0,0xEF, \
        0xF0,0xF1,0xD1,0xD2,0xD3,0xF5,0xD4,0xF7,0xF8,0xF9,0xD5,0x96,0x95,0x98,0xFE,0xFF}

#elif _CODE_PAGE == 1 /* ASCII (for only non-LFN cfg) */
#if _USE_LFN != 0
#error Cannot enable LFN without valid code page.
#endif
#define _DF1S 0

#else
#error Unknown code page

#endif


/* Character code support macros */
#define IsUpper(c)  (((c)>='A')&&((c)<='Z'))
#define IsLower(c)  (((c)>='a')&&((c)<='z'))
#define IsDigit(c)  (((c)>='0')&&((c)<='9'))

#if _DF1S != 0  /* Code page is DBCS */

#ifdef _DF2S  /* Two 1st byte areas */
#define IsDBCS1(c)  (((BYTE)(c) >= _DF1S && (BYTE)(c) <= _DF1E) || ((BYTE)(c) >= _DF2S && (BYTE)(c) <= _DF2E))
#else     /* One 1st byte area */
#define IsDBCS1(c)  ((BYTE)(c) >= _DF1S && (BYTE)(c) <= _DF1E)
#endif

#ifdef _DS3S  /* Three 2nd byte areas */
#define IsDBCS2(c)  (((BYTE)(c) >= _DS1S && (BYTE)(c) <= _DS1E) || ((BYTE)(c) >= _DS2S && (BYTE)(c) <= _DS2E) || ((BYTE)(c) >= _DS3S && (BYTE)(c) <= _DS3E))
#else     /* Two 2nd byte areas */
#define IsDBCS2(c)  (((BYTE)(c) >= _DS1S && (BYTE)(c) <= _DS1E) || ((BYTE)(c) >= _DS2S && (BYTE)(c) <= _DS2E))
#endif

#else     /* Code page is SBCS */

#define IsDBCS1(c)  0
#define IsDBCS2(c)  0

#endif /* _DF1S */


/* Name status flags */
#define NSFLAG    11    /* Index of name status byte in fn[] */
#define NS_LOSS   0x01  /* Out of 8.3 format */
#define NS_LFN    0x02  /* Force to create LFN entry */
#define NS_LAST   0x04  /* Last segment */
#define NS_BODY   0x08  /* Lower case flag (body) */
#define NS_EXT    0x10  /* Lower case flag (ext) */
#define NS_DOT    0x20  /* Dot entry */
#define NS_NONAME 0x80  /* Not followed */


/* Limits and Boundaries (Differ from specs but correct for real DOS/Windows) */
#define MIN_FAT16 4086U     /* Minimum number of clusters of FAT16 */
#define MIN_FAT32 65526U      /* Minimum number of clusters of FAT32 */
#define MAX_DIR   0x200000    /* Maximum size of FAT directory */
#define MAX_DIR_EX  0x10000000    /* Maximum size of exFAT directory */


/* FatFs refers the members in the FAT structures as byte array instead of
/ structure members because the structure is not binary compatible between
/ different platforms */

#define BS_jmpBoot      0   /* x86 jump instruction (3-byte) */
#define BS_OEMName      3   /* OEM name (8-byte) */
#define BPB_BytsPerSec    11    /* Sector size [byte] (WORD) */
#define BPB_SecPerClus    13    /* Cluster size [sector] (BYTE) */
#define BPB_RsvdSecCnt    14    /* Size of reserved area [sector] (WORD) */
#define BPB_NumFATs     16    /* Number of FATs (BYTE) */
#define BPB_RootEntCnt    17    /* Size of root directory area for FAT12/16 [entry] (WORD) */
#define BPB_TotSec16    19    /* Volume size (16-bit) [sector] (WORD) */
#define BPB_Media     21    /* Media descriptor (BYTE) */
#define BPB_FATSz16     22    /* FAT size (16-bit) [sector] (WORD) */
#define BPB_SecPerTrk   24    /* Track size for int13h [sector] (WORD) */
#define BPB_NumHeads    26    /* Number of heads for int13h (WORD) */
#define BPB_HiddSec     28    /* Volume offset from top of the drive (DWORD) */
#define BPB_TotSec32    32    /* Volume size (32-bit) [sector] (DWORD) */
#define BS_DrvNum     36    /* Physical drive number for int13h (BYTE) */
#define BS_NTres      37    /* Error flag (BYTE) */
#define BS_BootSig      38    /* Extended boot signature (BYTE) */
#define BS_VolID      39    /* Volume serial number (DWORD) */
#define BS_VolLab     43    /* Volume label string (8-byte) */
#define BS_FilSysType   54    /* File system type string (8-byte) */
#define BPB_FATSz32     36    /* FAT size (32-bit) [sector] (DWORD) */
#define BPB_ExtFlags    40    /* Extended flags (WORD) */

#define BPB_FSVer32     42    /* FAT32: File system version (WORD) */
#define BPB_RootClus32    44    /* FAT32: Root directory cluster (DWORD) */
#define BPB_FSInfo32    48    /* FAT32: Offset of FSINFO sector (WORD) */
#define BPB_BkBootSec32   50    /* FAT32: Offset of backup boot sector (WORD) */
#define BS_DrvNum32     64    /* FAT32: Physical drive number for int13h (BYTE) */
#define BS_NTres32      65    /* FAT32: Error flag (BYTE) */
#define BS_BootSig32    66    /* FAT32: Extended boot signature (BYTE) */
#define BS_VolID32      67    /* FAT32: Volume serial number (DWORD) */
#define BS_VolLab32     71    /* FAT32: Volume label string (8-byte) */
#define BS_FilSysType32   82    /* FAT32: File system type string (8-byte) */

#define BPB_ZeroedEx    11    /* exFAT: Must be zero (35-byte) */
#define BPB_VolOfsEx    64    /* exFAT: Volume offset from top of the drive [sector] (QWORD) */
#define BPB_TotSecEx    72    /* exFAT: Volume size [sector] (QWORD) */
#define BPB_FatOfsEx    80    /* exFAT: FAT offset from top of the volume [sector] (DWORD) */
#define BPB_FatSzEx     84    /* exFAT: FAT size [sector] (DWORD) */
#define BPB_DataOfsEx   88    /* exFAT: Data offset from top of the volume [sector] (DWORD) */
#define BPB_NumClusEx   92    /* exFAT: Number of clusters (DWORD) */
#define BPB_RootClusEx    96    /* exFAT: Root directory cluster (DWORD) */
#define BPB_VolIDEx     100   /* exFAT: Volume serial number (DWORD) */
#define BPB_FSVerEx     104   /* exFAT: File system version (WORD) */
#define BPB_VolFlagEx   106   /* exFAT: Volume flags (BYTE) */
#define BPB_ActFatEx    107   /* exFAT: Active FAT flags (BYTE) */
#define BPB_BytsPerSecEx  108   /* exFAT: Log2 of sector size in byte (BYTE) */
#define BPB_SecPerClusEx  109   /* exFAT: Log2 of cluster size in sector (BYTE) */
#define BPB_NumFATsEx   110   /* exFAT: Number of FATs (BYTE) */
#define BPB_DrvNumEx    111   /* exFAT: Physical drive number for int13h (BYTE) */
#define BPB_PercInUseEx   112   /* exFAT: Percent in use (BYTE) */

#define FSI_LeadSig     0   /* FAT32 FSI: Leading signature (DWORD) */
#define FSI_StrucSig    484   /* FAT32 FSI: Structure signature (DWORD) */
#define FSI_Free_Count    488   /* FAT32 FSI: Number of free clusters (DWORD) */
#define FSI_Nxt_Free    492   /* FAT32 FSI: Last allocated cluster (DWORD) */

#define MBR_Table     446   /* MBR: Partition table offset */
#define SZ_PTE        16    /* MBR: Size of a partition table entry */

#define BS_55AA       510   /* Signature word (WORD) */

#define DIR_Name      0   /* Short file name (11) */
#define DIR_Attr      11    /* Attribute (1) */
#define DIR_NTres     12    /* Lower case flag (1) */
#define DIR_CrtTime10   13    /* Created time sub-second (1) */
#define DIR_CrtTime     14    /* Created time (2) */
#define DIR_CrtDate     16    /* Created date (2) */
#define DIR_LstAccDate    18    /* Last accessed date (2) */
#define DIR_FstClusHI   20    /* Higher 16-bit of first cluster (WORD) */
#define DIR_WrtTime     22    /* Modified time (2) */
#define DIR_WrtDate     24    /* Modified date (2) */
#define DIR_FstClusLO   26    /* Lower 16-bit of first cluster (WORD) */
#define DIR_FileSize    28    /* File size (DWORD) */
#define LDIR_Ord      0   /* LFN entry order and LLE flag (1) */
#define LDIR_Attr     11    /* LFN attribute (1) */
#define LDIR_Type     12    /* LFN type (1) */
#define LDIR_Chksum     13    /* Checksum of the SFN entry */
#define LDIR_FstClusLO    26    /* Must be zero (WORD) */
#define XDIR_Type     0   /* Type of exFAT directory entry (BYTE) */
#define XDIR_NumLabel   1   /* Number of volume label characters (BYTE) */
#define XDIR_Label      2   /* Volume label (11-WORD) */
#define XDIR_CaseSum    4   /* Sum of case conversion table (DWORD) */
#define XDIR_NumSec     1   /* Number of secondary entries (BYTE) */
#define XDIR_SetSum     2   /* Sum of the set of directory entries (WORD) */
#define XDIR_Attr     4   /* File attribute (WORD) */
#define XDIR_CrtTime    8   /* Created time (4) */
#define XDIR_ModTime    12    /* Modified time (4) */
#define XDIR_AccTime    16    /* Last accessed time (4) */
#define XDIR_CrtTime10    20    /* Created time subsecond (1) */
#define XDIR_ModTime10    21    /* Modified time subsecond (1) */
#define XDIR_CrtTZ      22    /* Created timezone (1) */
#define XDIR_ModTZ      23    /* Modified timezone (1) */
#define XDIR_AccTZ      24    /* Last accessed timezone (1) */
#define XDIR_GenFlags   33    /* Gneral flags (1) */
#define XDIR_NumName    35    /* Number of file name characters (BYTE) */
#define XDIR_NameHash   36    /* Hash of file name (WORD) */
#define XDIR_ValidFileSize  40    /* Valid file size (QWORD) */
#define XDIR_FstClus    52    /* First cluster of the File/Directory (DWORD) */
#define XDIR_FileSize   56    /* File/Directory size (QWORD) */

#define SZDIRE        32    /* Size of a directory entry */
#define LLEF        0x40  /* Last long entry flag in LDIR_Ord */
#define DDEM        0xE5  /* Deleted directory entry mark at DIR_Name[0] */
#define RDDEM       0x05  /* Replacement of the character collides with DDEM */





/*--------------------------------------------------------------------------

   Module Private Work Area

---------------------------------------------------------------------------*/

/* Remark: Variables here without initial value shall be guaranteed zero/null
/  at start-up. If not, either the linker or start-up routine being used is
/  not compliance with C standard. */

#if _VOLUMES < 1 || _VOLUMES > 9
#error Wrong _VOLUMES setting
#endif
static FATFS *FatFs[_VOLUMES];  /* Pointer to the file system objects (logical drives) */
static WORD Fsid;       /* File system mount ID */

#if _FS_RPATH != 0 && _VOLUMES >= 2
static BYTE CurrVol;      /* Current drive */
#endif

#if _FS_LOCK != 0
static FILESEM Files[_FS_LOCK]; /* Open object lock semaphores */
#endif

#if _USE_LFN == 0     /* Non-LFN configuration */
#define DEF_NAMBUF      BYTE sfn[12]
#define INIT_NAMBUF(dobj) (dobj).fn = sfn
#define FREE_NAMBUF()
#define DEF_DIRBUF
#define INIT_DIRBUF(fs)
#define FREE_DIRBUF()
#else
#if _MAX_LFN < 12 || _MAX_LFN > 255
#error Wrong _MAX_LFN setting
#endif

#if _USE_LFN == 1   /* LFN enabled with static working buffer */
#if _FS_EXFAT
static BYTE DirBuf[SZDIRE*19];  /* Directory entry block scratchpad buffer (19 entries in size) */
#endif
static WCHAR LfnBuf[_MAX_LFN+1];  /* LFN enabled with static working buffer */
#define DEF_NAMBUF    BYTE sfn[12]
#define INIT_NAMBUF(dj) { (dj).fn = sfn; (dj).lfn = LfnBuf; }
#define FREE_NAMBUF()
#define DEF_DIRBUF
#define INIT_DIRBUF(fs)
#define FREE_DIRBUF()

#elif _USE_LFN == 2   /* LFN enabled with dynamic working buffer on the stack */
#if _FS_EXFAT
#define DEF_NAMBUF    BYTE sfn[12]; WCHAR lbuf[_MAX_LFN+1]; BYTE dbuf[SZDIRE*19]
#define INIT_NAMBUF(dj) { (dj).fn = sfn; (dj).lfn = lbuf; (dj).obj.fs->dirbuf = dbuf; }
#define FREE_NAMBUF()
#define DEF_DIRBUF    BYTE dbuf[SZDIRE*19]
#define INIT_DIRBUF(fs) fs->dirbuf = dbuf
#define FREE_DIRBUF()
#else
#define DEF_NAMBUF    BYTE sfn[12]; WCHAR lbuf[_MAX_LFN+1]
#define INIT_NAMBUF(dj) { (dj).fn = sfn; (dj).lfn = lbuf; }
#define FREE_NAMBUF()
#define DEF_DIRBUF
#define INIT_DIRBUF(fs)
#define FREE_DIRBUF()
#endif

#elif _USE_LFN == 3   /* LFN enabled with dynamic working buffer on the heap */
#if _FS_EXFAT
#define DEF_NAMBUF    BYTE sfn[12]; WCHAR *lfn
#define INIT_NAMBUF(dj) { lfn = ff_memalloc((_MAX_LFN+1)*2 + SZDIRE*19); if (!lfn) LEAVE_FF((dj).obj.fs, FR_NOT_ENOUGH_CORE); (dj).fn = sfn; (dj).lfn = lfn; (dj).obj.fs->dirbuf = (BYTE*)(lfn+_MAX_LFN+1); }
#define FREE_NAMBUF() ff_memfree(lfn)
#define DEF_DIRBUF    BYTE *dirb
#define INIT_DIRBUF(fs) { dirb = ff_memalloc(SZDIRE*19); if (!dirb) LEAVE_FF(fs, FR_NOT_ENOUGH_CORE); fs->dirbuf = dirb; }
#define FREE_DIRBUF() ff_memfree(dirb)
#else
#define DEF_NAMBUF    BYTE sfn[12]; WCHAR *lfn
#define INIT_NAMBUF(dj) { lfn = ff_memalloc((_MAX_LFN+1)*2); if (!lfn) LEAVE_FF((dj).obj.fs, FR_NOT_ENOUGH_CORE); (dj).fn = sfn; (dj).lfn = lfn; }
#define FREE_NAMBUF() ff_memfree(lfn)
#define DEF_DIRBUF
#define INIT_DIRBUF(fs)
#define FREE_DIRBUF()
#endif

#else
#error Wrong _USE_LFN setting
#endif
#endif

#ifdef _EXCVT
static const BYTE ExCvt[] = _EXCVT; /* Upper conversion table for SBCS extended characters */
#endif






/*--------------------------------------------------------------------------

   Module Private Functions

---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/* Load/Store multi-byte word in the FAT structure                       */
/*-----------------------------------------------------------------------*/

static
WORD ld_word (const BYTE* ptr)  /*   Load a 2-byte little-endian word */
{
  WORD rv;

  rv = ptr[1];
  rv = (WORD)(rv << 8 | ptr[0]);
  return rv;
}

static
DWORD ld_dword (const BYTE* ptr)  /* Load a 4-byte little-endian word */
{
  DWORD rv;

  rv = ptr[3];
  rv = rv << 8 | ptr[2];
  rv = rv << 8 | ptr[1];
  rv = rv << 8 | ptr[0];
  return rv;
}

#if _FS_EXFAT
static
QWORD ld_qword (const BYTE* ptr)  /* Load an 8-byte little-endian word */
{
  QWORD rv;

  rv = ptr[7];
  rv = rv << 8 | ptr[6];
  rv = rv << 8 | ptr[5];
  rv = rv << 8 | ptr[4];
  rv = rv << 8 | ptr[3];
  rv = rv << 8 | ptr[2];
  rv = rv << 8 | ptr[1];
  rv = rv << 8 | ptr[0];
  return rv;
}
#endif

#if !_FS_READONLY
static
void st_word (BYTE* ptr, WORD val)  /* Store a 2-byte word in little-endian */
{
  *ptr++ = (BYTE)val; val >>= 8;
  *ptr++ = (BYTE)val;
}

static
void st_dword (BYTE* ptr, DWORD val)  /* Store a 4-byte word in little-endian */
{
  *ptr++ = (BYTE)val; val >>= 8;
  *ptr++ = (BYTE)val; val >>= 8;
  *ptr++ = (BYTE)val; val >>= 8;
  *ptr++ = (BYTE)val;
}

#if _FS_EXFAT
static
void st_qword (BYTE* ptr, QWORD val)  /* Store an 8-byte word in little-endian */
{
  *ptr++ = (BYTE)val; val >>= 8;
  *ptr++ = (BYTE)val; val >>= 8;
  *ptr++ = (BYTE)val; val >>= 8;
  *ptr++ = (BYTE)val; val >>= 8;
  *ptr++ = (BYTE)val; val >>= 8;
  *ptr++ = (BYTE)val; val >>= 8;
  *ptr++ = (BYTE)val; val >>= 8;
  *ptr++ = (BYTE)val;
}
#endif
#endif  /* !_FS_READONLY */



/*-----------------------------------------------------------------------*/
/* String functions                                                      */
/*-----------------------------------------------------------------------*/

/* Copy memory to memory */
static
void mem_cpy (void* dst, const void* src, UINT cnt) {
  BYTE *d = (BYTE*)dst;
  const BYTE *s = (const BYTE*)src;

  if (cnt) {
    do *d++ = *s++; while (--cnt);
  }
}

/* Fill memory block */
static
void mem_set (void* dst, int val, UINT cnt) {
  BYTE *d = (BYTE*)dst;

  do *d++ = (BYTE)val; while (--cnt);
}

/* Compare memory block */
static
int mem_cmp (const void* dst, const void* src, UINT cnt) {  /* ZR:same, NZ:different */
  const BYTE *d = (const BYTE *)dst, *s = (const BYTE *)src;
  int r = 0;

  do {
    r = *d++ - *s++;
  } while (--cnt && r == 0);

  return r;
}

/* Check if chr is contained in the string */
static
int chk_chr (const char* str, int chr) {  /* NZ:contained, ZR:not contained */
  while (*str && *str != chr) str++;
  return *str;
}




/*-----------------------------------------------------------------------*/
/* Request/Release grant to access the volume                            */
/*-----------------------------------------------------------------------*/
#if _FS_REENTRANT
static
int lock_fs (
  FATFS* fs   /* File system object */
)
{
  return ff_req_grant(fs->sobj);
}


static
void unlock_fs (
  FATFS* fs,    /* File system object */
  FRESULT res   /* Result code to be returned */
)
{
  if (fs && res != FR_NOT_ENABLED && res != FR_INVALID_DRIVE && res != FR_TIMEOUT) {
    ff_rel_grant(fs->sobj);
  }
}
#endif




/*-----------------------------------------------------------------------*/
/* File lock control functions                                           */
/*-----------------------------------------------------------------------*/
#if _FS_LOCK != 0

static
FRESULT chk_lock (  /* Check if the file can be accessed */
  DIR* dp,    /* Directory object pointing the file to be checked */
  int acc     /* Desired access type (0:Read, 1:Write, 2:Delete/Rename) */
)
{
  UINT i, be;

  /* Search file semaphore table */
  for (i = be = 0; i < _FS_LOCK; i++) {
    if (Files[i].fs) {  /* Existing entry */
      if (Files[i].fs == dp->obj.fs &&    /* Check if the object matched with an open object */
        Files[i].clu == dp->obj.sclust &&
        Files[i].ofs == dp->dptr) break;
    } else {      /* Blank entry */
      be = 1;
    }
  }
  if (i == _FS_LOCK) {  /* The object is not opened */
    return (be || acc == 2) ? FR_OK : FR_TOO_MANY_OPEN_FILES; /* Is there a blank entry for new object? */
  }

  /* The object has been opened. Reject any open against writing file and all write mode open */
  return (acc || Files[i].ctr == 0x100) ? FR_LOCKED : FR_OK;
}


static
int enq_lock (void) /* Check if an entry is available for a new object */
{
  UINT i;

  for (i = 0; i < _FS_LOCK && Files[i].fs; i++) ;
  return (i == _FS_LOCK) ? 0 : 1;
}


static
UINT inc_lock ( /* Increment object open counter and returns its index (0:Internal error) */
  DIR* dp,  /* Directory object pointing the file to register or increment */
  int acc   /* Desired access (0:Read, 1:Write, 2:Delete/Rename) */
)
{
  UINT i;


  for (i = 0; i < _FS_LOCK; i++) {  /* Find the object */
    if (Files[i].fs == dp->obj.fs &&
      Files[i].clu == dp->obj.sclust &&
      Files[i].ofs == dp->dptr) break;
  }

  if (i == _FS_LOCK) {        /* Not opened. Register it as new. */
    for (i = 0; i < _FS_LOCK && Files[i].fs; i++) ;
    if (i == _FS_LOCK) return 0;  /* No free entry to register (int err) */
    Files[i].fs = dp->obj.fs;
    Files[i].clu = dp->obj.sclust;
    Files[i].ofs = dp->dptr;
    Files[i].ctr = 0;
  }

  if (acc && Files[i].ctr) return 0;  /* Access violation (int err) */

  Files[i].ctr = acc ? 0x100 : Files[i].ctr + 1;  /* Set semaphore value */

  return i + 1;
}


static
FRESULT dec_lock (  /* Decrement object open counter */
  UINT i      /* Semaphore index (1..) */
)
{
  WORD n;
  FRESULT res;


  if (--i < _FS_LOCK) { /* Shift index number origin from 0 */
    n = Files[i].ctr;
    if (n == 0x100) n = 0;    /* If write mode open, delete the entry */
    if (n > 0) n--;       /* Decrement read mode open count */
    Files[i].ctr = n;
    if (n == 0) Files[i].fs = 0;  /* Delete the entry if open count gets zero */
    res = FR_OK;
  } else {
    res = FR_INT_ERR;     /* Invalid index nunber */
  }
  return res;
}


static
void clear_lock ( /* Clear lock entries of the volume */
  FATFS *fs
)
{
  UINT i;

  for (i = 0; i < _FS_LOCK; i++) {
    if (Files[i].fs == fs) Files[i].fs = 0;
  }
}
#endif




/*-----------------------------------------------------------------------*/
/* Move/Flush disk access window in the file system object               */
/*-----------------------------------------------------------------------*/
#if !_FS_READONLY
static
FRESULT sync_window ( /* Returns FR_OK or FR_DISK_ERROR */
  FATFS* fs     /* File system object */
)
{
  DWORD wsect;
  UINT nf;
  FRESULT res = FR_OK;


  if (fs->wflag) {  /* Write back the sector if it is dirty */
    wsect = fs->winsect;  /* Current sector number */
    if (disk_write(fs->drv, fs->win, wsect, 1) != RES_OK) {
      res = FR_DISK_ERR;
    } else {
      fs->wflag = 0;
      if (wsect - fs->fatbase < fs->fsize) {    /* Is it in the FAT area? */
        for (nf = fs->n_fats; nf >= 2; nf--) {  /* Reflect the change to all FAT copies */
          wsect += fs->fsize;
          disk_write(fs->drv, fs->win, wsect, 1);
        }
      }
    }
  }
  return res;
}
#endif


static
FRESULT move_window ( /* Returns FR_OK or FR_DISK_ERROR */
  FATFS* fs,      /* File system object */
  DWORD sector    /* Sector number to make appearance in the fs->win[] */
)
{
  FRESULT res = FR_OK;


  if (sector != fs->winsect) {  /* Window offset changed? */
#if !_FS_READONLY
    res = sync_window(fs);    /* Write-back changes */
#endif
    if (res == FR_OK) {     /* Fill sector window with new data */
      if (disk_read(fs->drv, fs->win, sector, 1) != RES_OK) {
        sector = 0xFFFFFFFF;  /* Invalidate window if data is not reliable */
        res = FR_DISK_ERR;
      }
      fs->winsect = sector;
    }
  }
  return res;
}




/*-----------------------------------------------------------------------*/
/* Synchronize file system and strage device                             */
/*-----------------------------------------------------------------------*/
#if !_FS_READONLY
static
FRESULT sync_fs ( /* FR_OK:succeeded, !=0:error */
  FATFS* fs   /* File system object */
)
{
  FRESULT res;


  res = sync_window(fs);
  if (res == FR_OK) {
    /* Update FSInfo sector if needed */
    if (fs->fs_type == FS_FAT32 && fs->fsi_flag == 1) {
      /* Create FSInfo structure */
      mem_set(fs->win, 0, SS(fs));
      st_word(fs->win + BS_55AA, 0xAA55);
      st_dword(fs->win + FSI_LeadSig, 0x41615252);
      st_dword(fs->win + FSI_StrucSig, 0x61417272);
      st_dword(fs->win + FSI_Free_Count, fs->free_clst);
      st_dword(fs->win + FSI_Nxt_Free, fs->last_clst);
      /* Write it into the FSInfo sector */
      fs->winsect = fs->volbase + 1;
      disk_write(fs->drv, fs->win, fs->winsect, 1);
      fs->fsi_flag = 0;
    }
    /* Make sure that no pending write process in the physical drive */
    if (disk_ioctl(fs->drv, CTRL_SYNC, 0) != RES_OK) res = FR_DISK_ERR;
  }

  return res;
}
#endif




/*-----------------------------------------------------------------------*/
/* Get sector# from cluster#                                             */
/*-----------------------------------------------------------------------*/

static
DWORD clust2sect (  /* !=0:Sector number, 0:Failed (invalid cluster#) */
  FATFS* fs,    /* File system object */
  DWORD clst    /* Cluster# to be converted */
)
{
  clst -= 2;
  if (clst >= fs->n_fatent - 2) return 0;   /* Invalid cluster# */
  return clst * fs->csize + fs->database;
}




/*-----------------------------------------------------------------------*/
/* FAT access - Read value of a FAT entry                                */
/*-----------------------------------------------------------------------*/

static
DWORD get_fat ( /* 0xFFFFFFFF:Disk error, 1:Internal error, 2..0x7FFFFFFF:Cluster status */
  _FDID* obj, /* Corresponding object */
  DWORD clst  /* Cluster number to get the value */
)
{
  UINT wc, bc;
  DWORD val;
  FATFS *fs = obj->fs;


  if (clst < 2 || clst >= fs->n_fatent) { /* Check if in valid range */
    val = 1;  /* Internal error */

  } else {
    val = 0xFFFFFFFF; /* Default value falls on disk error */

    switch (fs->fs_type) {
    case FS_FAT12 :
      bc = (UINT)clst; bc += bc / 2;
      if (move_window(fs, fs->fatbase + (bc / SS(fs))) != FR_OK) break;
      wc = fs->win[bc++ % SS(fs)];
      if (move_window(fs, fs->fatbase + (bc / SS(fs))) != FR_OK) break;
      wc |= fs->win[bc % SS(fs)] << 8;
      val = clst & 1 ? wc >> 4 : (wc & 0xFFF);
      break;

    case FS_FAT16 :
      if (move_window(fs, fs->fatbase + (clst / (SS(fs) / 2))) != FR_OK) break;
      val = ld_word(&fs->win[clst * 2 % SS(fs)]);
      break;

    case FS_FAT32 :
      if (move_window(fs, fs->fatbase + (clst / (SS(fs) / 4))) != FR_OK) break;
      val = ld_dword(&fs->win[clst * 4 % SS(fs)]) & 0x0FFFFFFF;
      break;
#if _FS_EXFAT
    case FS_EXFAT :
      if (obj->objsize) {
        DWORD cofs = clst - obj->sclust;  /* Offset from start cluster */
        DWORD clen = (DWORD)((obj->objsize - 1) / SS(fs)) / fs->csize;  /* Number of clusters - 1 */

        if (obj->stat == 2) { /* Is there no valid chain on the FAT? */
          if (cofs <= clen) {
            val = (cofs == clen) ? 0x7FFFFFFF : clst + 1; /* Generate the value */
            break;
          }
        }
        if (obj->stat == 3 && cofs < obj->n_cont) { /* Is it in the contiguous part? */
          val = clst + 1;   /* Generate the value */
          break;
        }
        if (obj->stat != 2) { /* Get value from FAT if FAT chain is valid */
          if (move_window(fs, fs->fatbase + (clst / (SS(fs) / 4))) != FR_OK) break;
          val = ld_dword(&fs->win[clst * 4 % SS(fs)]) & 0x7FFFFFFF;
          break;
        }
      }
      /* Go default */
#endif
    default:
      val = 1;  /* Internal error */
    }
  }

  return val;
}




/*-----------------------------------------------------------------------*/
/* FAT access - Change value of a FAT entry                              */
/*-----------------------------------------------------------------------*/

#if !_FS_READONLY
static
FRESULT put_fat ( /* FR_OK(0):succeeded, !=0:error */
  FATFS* fs,    /* Corresponding object */
  DWORD clst,   /* FAT index number (cluster number) to be changed */
  DWORD val   /* New value to be set to the entry */
)
{
  UINT bc;
  BYTE *p;
  FRESULT res = FR_INT_ERR;


  if (clst >= 2 && clst < fs->n_fatent) { /* Check if in valid range */
    switch (fs->fs_type) {
    case FS_FAT12 : /* Bitfield items */
      bc = (UINT)clst; bc += bc / 2;
      res = move_window(fs, fs->fatbase + (bc / SS(fs)));
      if (res != FR_OK) break;
      p = &fs->win[bc++ % SS(fs)];
      *p = (clst & 1) ? ((*p & 0x0F) | ((BYTE)val << 4)) : (BYTE)val;
      fs->wflag = 1;
      res = move_window(fs, fs->fatbase + (bc / SS(fs)));
      if (res != FR_OK) break;
      p = &fs->win[bc % SS(fs)];
      *p = (clst & 1) ? (BYTE)(val >> 4) : ((*p & 0xF0) | ((BYTE)(val >> 8) & 0x0F));
      fs->wflag = 1;
      break;

    case FS_FAT16 : /* WORD aligned items */
      res = move_window(fs, fs->fatbase + (clst / (SS(fs) / 2)));
      if (res != FR_OK) break;
      st_word(&fs->win[clst * 2 % SS(fs)], (WORD)val);
      fs->wflag = 1;
      break;

    case FS_FAT32 : /* DWORD aligned items */
#if _FS_EXFAT
    case FS_EXFAT :
#endif
      res = move_window(fs, fs->fatbase + (clst / (SS(fs) / 4)));
      if (res != FR_OK) break;
      if (!_FS_EXFAT || fs->fs_type != FS_EXFAT) {
        val = (val & 0x0FFFFFFF) | (ld_dword(&fs->win[clst * 4 % SS(fs)]) & 0xF0000000);
      }
      st_dword(&fs->win[clst * 4 % SS(fs)], val);
      fs->wflag = 1;
      break;
    }
  }
  return res;
}
#endif /* !_FS_READONLY */




#if _FS_EXFAT && !_FS_READONLY
/*-----------------------------------------------------------------------*/
/* exFAT: Accessing FAT and Allocation Bitmap                            */
/*-----------------------------------------------------------------------*/

/*---------------------------------------------*/
/* exFAT: Find a contiguous free cluster block */
/*---------------------------------------------*/
static
DWORD find_bitmap ( /* 0:No free cluster, 2..:Free cluster found, 0xFFFFFFFF:Disk error */
  FATFS* fs,  /* File system object */
  DWORD clst, /* Cluster number to scan from */
  DWORD ncl /* Number of contiguous clusters to find (1..) */
)
{
  BYTE bm, bv;
  UINT i;
  DWORD val, scl, ctr;


  clst -= 2;  /* The first bit in the bitmap corresponds to cluster #2 */
  if (clst >= fs->n_fatent - 2) clst = 0;
  scl = val = clst; ctr = 0;
  for (;;) {
    if (move_window(fs, fs->database + val / 8 / SS(fs)) != FR_OK) return 0xFFFFFFFF;
    i = val / 8 & (SS(fs) - 1); bm = 1 << (val % 8);
    do {
      do {
        bv = fs->win[i] & bm; bm <<= 1;   /* Get bit value */
        if (++val >= fs->n_fatent - 2) {  /* Next cluster (with wrap-around) */
          val = 0; bm = 0; i = 4096;
        }
        if (!bv) {  /* Is it a free cluster? */
          if (++ctr == ncl) return scl + 2; /* Check run length */
        } else {
          scl = val; ctr = 0;   /* Encountered a live cluster, restart to scan */
        }
        if (val == clst) return 0;  /* All cluster scanned? */
      } while (bm);
      bm = 1;
    } while (++i < SS(fs));
  }
}

/*------------------------------------*/
/* exFAT: Set/Clear a block of bitmap */
/*------------------------------------*/
static
FRESULT change_bitmap (
  FATFS* fs,  /* File system object */
  DWORD clst, /* Cluster number to change from */
  DWORD ncl,  /* Number of clusters to be changed */
  int bv    /* bit value to be set (0 or 1) */
)
{
  BYTE bm;
  UINT i;
  DWORD sect;


  clst -= 2;  /* The first bit corresponds to cluster #2 */
  sect = fs->database + clst / 8 / SS(fs);  /* Sector address */
  i = clst / 8 & (SS(fs) - 1);        /* Byte offset in the sector */
  bm = 1 << (clst % 8);           /* Bit mask in the byte */
  for (;;) {
    if (move_window(fs, sect++) != FR_OK) return FR_DISK_ERR;
    do {
      do {
        if (bv == (int)((fs->win[i] & bm) != 0)) return FR_INT_ERR; /* Is the bit expected value? */
        fs->win[i] ^= bm; /* Flip the bit */
        fs->wflag = 1;
        if (--ncl == 0) return FR_OK; /* All bits processed? */
      } while (bm <<= 1);   /* Next bit */
      bm = 1;
    } while (++i < SS(fs));   /* Next byte */
  }
}


/*---------------------------------------------*/
/* Complement contiguous part of the FAT chain */
/*---------------------------------------------*/
static
FRESULT fill_fat_chain (
  _FDID* obj  /* Pointer to the corresponding object */
)
{
  FRESULT res;
  DWORD cl, n;

  if (obj->stat == 3) { /* Has the object got fragmented? */
    for (cl = obj->sclust, n = obj->n_cont; n; cl++, n--) { /* Create cluster chain on the FAT */
      res = put_fat(obj->fs, cl, cl + 1);
      if (res != FR_OK) return res;
    }
    obj->stat = 0;  /* Change status 'FAT chain is valid' */
  }
  return FR_OK;
}

#endif



/*-----------------------------------------------------------------------*/
/* FAT handling - Remove a cluster chain                                 */
/*-----------------------------------------------------------------------*/
#if !_FS_READONLY
static
FRESULT remove_chain (  /* FR_OK(0):succeeded, !=0:error */
  _FDID* obj,     /* Corresponding object */
  DWORD clst,     /* Cluster to remove a chain from */
  DWORD pclst     /* Previous cluster of clst (0:an entire chain) */
)
{
  FRESULT res = FR_OK;
  DWORD nxt;
  FATFS *fs = obj->fs;
#if _FS_EXFAT || _USE_TRIM
  DWORD scl = clst, ecl = clst;
#endif
#if _USE_TRIM
  DWORD rt[2];
#endif

  if (clst < 2 || clst >= fs->n_fatent) return FR_INT_ERR;  /* Check if in valid range */

  /* Mark the previous cluster 'EOC' on the FAT if it exists */
  if (pclst && (!_FS_EXFAT || fs->fs_type != FS_EXFAT || obj->stat != 2)) {
    res = put_fat(fs, pclst, 0xFFFFFFFF);
    if (res != FR_OK) return res;
  }

  /* Remove the chain */
  do {
    nxt = get_fat(obj, clst);     /* Get cluster status */
    if (nxt == 0) break;        /* Empty cluster? */
    if (nxt == 1) return FR_INT_ERR;  /* Internal error? */
    if (nxt == 0xFFFFFFFF) return FR_DISK_ERR;  /* Disk error? */
    if (!_FS_EXFAT || fs->fs_type != FS_EXFAT) {
      res = put_fat(fs, clst, 0);   /* Mark the cluster 'free' on the FAT */
      if (res != FR_OK) return res;
    }
    if (fs->free_clst != 0xFFFFFFFF) {  /* Update FSINFO */
      fs->free_clst++;
      fs->fsi_flag |= 1;
    }
#if _FS_EXFAT || _USE_TRIM
    if (ecl + 1 == nxt) { /* Is next cluster contiguous? */
      ecl = nxt;
    } else {        /* End of contiguous cluster block */
#if _FS_EXFAT
      if (fs->fs_type == FS_EXFAT) {
        res = change_bitmap(fs, scl, ecl - scl + 1, 0); /* Mark the cluster block 'free' on the bitmap */
        if (res != FR_OK) return res;
      }
#endif
#if _USE_TRIM
      rt[0] = clust2sect(fs, scl);          /* Start sector */
      rt[1] = clust2sect(fs, ecl) + fs->csize - 1;  /* End sector */
      disk_ioctl(fs->drv, CTRL_TRIM, rt);       /* Inform device the block can be erased */
#endif
      scl = ecl = nxt;
    }
#endif
    clst = nxt;         /* Next cluster */
  } while (clst < fs->n_fatent);  /* Repeat while not the last link */

#if _FS_EXFAT
  if (fs->fs_type == FS_EXFAT) {
    if (pclst == 0) { /* Does object have no chain? */
      obj->stat = 0;    /* Change the object status 'initial' */
    } else {
      if (obj->stat == 3 && pclst >= obj->sclust && pclst <= obj->sclust + obj->n_cont) { /* Did the chain got contiguous? */
        obj->stat = 2;  /* Change the object status 'contiguous' */
      }
    }
  }
#endif
  return FR_OK;
}
#endif




/*-----------------------------------------------------------------------*/
/* FAT handling - Stretch a chain or Create a new chain                  */
/*-----------------------------------------------------------------------*/
#if !_FS_READONLY
static
DWORD create_chain (  /* 0:No free cluster, 1:Internal error, 0xFFFFFFFF:Disk error, >=2:New cluster# */
  _FDID* obj,     /* Corresponding object */
  DWORD clst      /* Cluster# to stretch, 0:Create a new chain */
)
{
  DWORD cs, ncl, scl;
  FRESULT res;
  FATFS *fs = obj->fs;


  if (clst == 0) {  /* Create a new chain */
    scl = fs->last_clst;        /* Get suggested cluster to start at */
    if (scl == 0 || scl >= fs->n_fatent) scl = 1;
  }
  else {        /* Stretch current chain */
    cs = get_fat(obj, clst);      /* Check the cluster status */
    if (cs < 2) return 1;       /* Invalid value */
    if (cs == 0xFFFFFFFF) return cs;  /* A disk error occurred */
    if (cs < fs->n_fatent) return cs; /* It is already followed by next cluster */
    scl = clst;
  }

#if _FS_EXFAT
  if (fs->fs_type == FS_EXFAT) {  /* At the exFAT */
    ncl = find_bitmap(fs, scl, 1);        /* Find a free cluster */
    if (ncl == 0 || ncl == 0xFFFFFFFF) return ncl;  /* No free cluster or hard error? */
    res = change_bitmap(fs, ncl, 1, 1);     /* Mark the cluster 'in use' */
    if (res == FR_INT_ERR) return 1;
    if (res == FR_DISK_ERR) return 0xFFFFFFFF;
    if (clst == 0) {              /* Is it a new chain? */
      obj->stat = 2;              /* Set status 'contiguous chain' */
    } else {                  /* This is a stretched chain */
      if (obj->stat == 2 && ncl != scl + 1) { /* Is the chain got fragmented? */
        obj->n_cont = scl - obj->sclust;  /* Set size of the contiguous part */
        obj->stat = 3;            /* Change status 'just fragmented' */
      }
    }
  } else
#endif
  { /* At the FAT12/16/32 */
    ncl = scl;  /* Start cluster */
    for (;;) {
      ncl++;              /* Next cluster */
      if (ncl >= fs->n_fatent) {    /* Check wrap-around */
        ncl = 2;
        if (ncl > scl) return 0;  /* No free cluster */
      }
      cs = get_fat(obj, ncl);     /* Get the cluster status */
      if (cs == 0) break;       /* Found a free cluster */
      if (cs == 1 || cs == 0xFFFFFFFF) return cs; /* An error occurred */
      if (ncl == scl) return 0;   /* No free cluster */
    }
  }

  if (_FS_EXFAT && fs->fs_type == FS_EXFAT && obj->stat == 2) { /* Is it a contiguous chain? */
    res = FR_OK;            /* FAT does not need to be written */
  } else {
    res = put_fat(fs, ncl, 0xFFFFFFFF); /* Mark the new cluster 'EOC' */
    if (res == FR_OK && clst) {
      res = put_fat(fs, clst, ncl); /* Link it from the previous one if needed */
    }
  }

  if (res == FR_OK) {     /* Update FSINFO if function succeeded. */
    fs->last_clst = ncl;
    if (fs->free_clst < fs->n_fatent - 2) fs->free_clst--;
    fs->fsi_flag |= 1;
  } else {
    ncl = (res == FR_DISK_ERR) ? 0xFFFFFFFF : 1;  /* Failed. Create error status */
  }

  return ncl;   /* Return new cluster number or error status */
}
#endif /* !_FS_READONLY */




/*-----------------------------------------------------------------------*/
/* FAT handling - Convert offset into cluster with link map table        */
/*-----------------------------------------------------------------------*/

#if _USE_FASTSEEK
static
DWORD clmt_clust (  /* <2:Error, >=2:Cluster number */
  FIL* fp,    /* Pointer to the file object */
  FSIZE_t ofs   /* File offset to be converted to cluster# */
)
{
  DWORD cl, ncl, *tbl;
  FATFS *fs = fp->obj.fs;


  tbl = fp->cltbl + 1;  /* Top of CLMT */
  cl = (DWORD)(ofs / SS(fs) / fs->csize); /* Cluster order from top of the file */
  for (;;) {
    ncl = *tbl++;     /* Number of cluters in the fragment */
    if (ncl == 0) return 0; /* End of table? (error) */
    if (cl < ncl) break;  /* In this fragment? */
    cl -= ncl; tbl++;   /* Next fragment */
  }
  return cl + *tbl; /* Return the cluster number */
}
#endif  /* _USE_FASTSEEK */



/*-----------------------------------------------------------------------*/
/* Directory handling - Set directory index                              */
/*-----------------------------------------------------------------------*/

static
FRESULT dir_sdi ( /* FR_OK(0):succeeded, !=0:error */
  DIR* dp,    /* Pointer to directory object */
  DWORD ofs   /* Offset of directory table */
)
{
  DWORD csz, clst;
  FATFS *fs = dp->obj.fs;


  if (ofs >= (DWORD)((_FS_EXFAT && fs->fs_type == FS_EXFAT) ? MAX_DIR_EX : MAX_DIR) || ofs % SZDIRE) {  /* Check range of offset and alignment */
    return FR_INT_ERR;
  }
  dp->dptr = ofs;       /* Set current offset */
  clst = dp->obj.sclust;    /* Table start cluster (0:root) */
  if (clst == 0 && fs->fs_type >= FS_FAT32) { /* Replace cluster# 0 with root cluster# */
    clst = fs->dirbase;
    if (_FS_EXFAT) dp->obj.stat = 0;  /* exFAT: Root dir has an FAT chain */
  }

  if (clst == 0) {  /* Static table (root-directory in FAT12/16) */
    if (ofs / SZDIRE >= fs->n_rootdir)  return FR_INT_ERR;  /* Is index out of range? */
    dp->sect = fs->dirbase;

  } else {      /* Dynamic table (sub-directory or root-directory in FAT32+) */
    csz = (DWORD)fs->csize * SS(fs);  /* Bytes per cluster */
    while (ofs >= csz) {        /* Follow cluster chain */
      clst = get_fat(&dp->obj, clst);       /* Get next cluster */
      if (clst == 0xFFFFFFFF) return FR_DISK_ERR; /* Disk error */
      if (clst < 2 || clst >= fs->n_fatent) return FR_INT_ERR;  /* Reached to end of table or internal error */
      ofs -= csz;
    }
    dp->sect = clust2sect(fs, clst);
  }
  dp->clust = clst;         /* Current cluster# */
  if (!dp->sect) return FR_INT_ERR;
  dp->sect += ofs / SS(fs);     /* Sector# of the directory entry */
  dp->dir = fs->win + (ofs % SS(fs)); /* Pointer to the entry in the win[] */

  return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Directory handling - Move directory table index next                  */
/*-----------------------------------------------------------------------*/

static
FRESULT dir_next (  /* FR_OK(0):succeeded, FR_NO_FILE:End of table, FR_DENIED:Could not stretch */
  DIR* dp,    /* Pointer to the directory object */
  int stretch   /* 0: Do not stretch table, 1: Stretch table if needed */
)
{
  DWORD ofs, clst;
  FATFS *fs = dp->obj.fs;
#if !_FS_READONLY
  UINT n;
#endif

  ofs = dp->dptr + SZDIRE;  /* Next entry */
  if (!dp->sect || ofs >= (DWORD)((_FS_EXFAT && fs->fs_type == FS_EXFAT) ? MAX_DIR_EX : MAX_DIR)) return FR_NO_FILE;  /* Report EOT when offset has reached max value */

  if (ofs % SS(fs) == 0) {  /* Sector changed? */
    dp->sect++;       /* Next sector */

    if (!dp->clust) {   /* Static table */
      if (ofs / SZDIRE >= fs->n_rootdir) {  /* Report EOT if it reached end of static table */
        dp->sect = 0; return FR_NO_FILE;
      }
    }
    else {          /* Dynamic table */
      if ((ofs / SS(fs) & (fs->csize - 1)) == 0) {    /* Cluster changed? */
        clst = get_fat(&dp->obj, dp->clust);      /* Get next cluster */
        if (clst <= 1) return FR_INT_ERR;       /* Internal error */
        if (clst == 0xFFFFFFFF) return FR_DISK_ERR;   /* Disk error */
        if (clst >= fs->n_fatent) {           /* Reached end of dynamic table */
#if !_FS_READONLY
          if (!stretch) {               /* If no stretch, report EOT */
            dp->sect = 0; return FR_NO_FILE;
          }
          clst = create_chain(&dp->obj, dp->clust); /* Allocate a cluster */
          if (clst == 0) return FR_DENIED;      /* No free cluster */
          if (clst == 1) return FR_INT_ERR;     /* Internal error */
          if (clst == 0xFFFFFFFF) return FR_DISK_ERR; /* Disk error */
          /* Clean-up the stretched table */
          if (_FS_EXFAT) dp->obj.stat |= 4;     /* The directory needs to be updated */
          if (sync_window(fs) != FR_OK) return FR_DISK_ERR; /* Flush disk access window */
          mem_set(fs->win, 0, SS(fs));        /* Clear window buffer */
          for (n = 0, fs->winsect = clust2sect(fs, clst); n < fs->csize; n++, fs->winsect++) {  /* Fill the new cluster with 0 */
            fs->wflag = 1;
            if (sync_window(fs) != FR_OK) return FR_DISK_ERR;
          }
          fs->winsect -= n;             /* Restore window offset */
#else
          if (!stretch) dp->sect = 0;         /* If no stretch, report EOT (this is to suppress warning) */
          dp->sect = 0; return FR_NO_FILE;      /* Report EOT */
#endif
        }
        dp->clust = clst;   /* Initialize data for new cluster */
        dp->sect = clust2sect(fs, clst);
      }
    }
  }
  dp->dptr = ofs;           /* Current entry */
  dp->dir = &fs->win[ofs % SS(fs)]; /* Pointer to the entry in the win[] */

  return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Directory handling - Reserve a block of directory entries             */
/*-----------------------------------------------------------------------*/

#if !_FS_READONLY
static
FRESULT dir_alloc ( /* FR_OK(0):succeeded, !=0:error */
  DIR* dp,    /* Pointer to the directory object */
  UINT nent   /* Number of contiguous entries to allocate */
)
{
  FRESULT res;
  UINT n;
  FATFS *fs = dp->obj.fs;


  res = dir_sdi(dp, 0);
  if (res == FR_OK) {
    n = 0;
    do {
      res = move_window(fs, dp->sect);
      if (res != FR_OK) break;
#if _FS_EXFAT
      if (fs->fs_type == FS_EXFAT ? (int)((dp->dir[XDIR_Type] & 0x80) == 0) : (int)(dp->dir[DIR_Name] == DDEM || dp->dir[DIR_Name] == 0)) {
#else
      if (dp->dir[DIR_Name] == DDEM || dp->dir[DIR_Name] == 0) {
#endif
        if (++n == nent) break; /* A block of contiguous free entries is found */
      } else {
        n = 0;          /* Not a blank entry. Restart to search */
      }
      res = dir_next(dp, 1);
    } while (res == FR_OK); /* Next entry with table stretch enabled */
  }

  if (res == FR_NO_FILE) res = FR_DENIED; /* No directory entry to allocate */
  return res;
}
#endif




/*-----------------------------------------------------------------------*/
/* FAT: Directory handling - Load/Store start cluster number             */
/*-----------------------------------------------------------------------*/

static
DWORD ld_clust (  /* Returns the top cluster value of the SFN entry */
  FATFS* fs,    /* Pointer to the fs object */
  const BYTE* dir /* Pointer to the key entry */
)
{
  DWORD cl;

  cl = ld_word(dir + DIR_FstClusLO);
  if (fs->fs_type == FS_FAT32) {
    cl |= (DWORD)ld_word(dir + DIR_FstClusHI) << 16;
  }

  return cl;
}


#if !_FS_READONLY
static
void st_clust (
  FATFS* fs,  /* Pointer to the fs object */
  BYTE* dir,  /* Pointer to the key entry */
  DWORD cl  /* Value to be set */
)
{
  st_word(dir + DIR_FstClusLO, (WORD)cl);
  if (fs->fs_type == FS_FAT32) {
    st_word(dir + DIR_FstClusHI, (WORD)(cl >> 16));
  }
}
#endif




/*------------------------------------------------------------------------*/
/* FAT-LFN: LFN handling                                                  */
/*------------------------------------------------------------------------*/
#if _USE_LFN != 0
static
const BYTE LfnOfs[] = {1,3,5,7,9,14,16,18,20,22,24,28,30};  /* Offset of LFN characters in the directory entry */

/*--------------------------------------------------------*/
/* FAT-LFN: Compare a part of file name with an LFN entry */
/*--------------------------------------------------------*/
static
int cmp_lfn (       /* 1:matched, 0:not matched */
  const WCHAR* lfnbuf,  /* Pointer to the LFN working buffer to be compared */
  BYTE* dir       /* Pointer to the directory entry containing the part of LFN */
)
{
  UINT i, s;
  WCHAR wc, uc;


  if (ld_word(dir + LDIR_FstClusLO) != 0) return 0; /* Check LDIR_FstClusLO */

  i = ((dir[LDIR_Ord] & 0x3F) - 1) * 13;  /* Offset in the LFN buffer */

  for (wc = 1, s = 0; s < 13; s++) {    /* Process all characters in the entry */
    uc = ld_word(dir + LfnOfs[s]);    /* Pick an LFN character */
    if (wc) {
      if (i >= _MAX_LFN || ff_wtoupper(uc) != ff_wtoupper(lfnbuf[i++])) { /* Compare it */
        return 0;         /* Not matched */
      }
      wc = uc;
    } else {
      if (uc != 0xFFFF) return 0;   /* Check filler */
    }
  }

  if ((dir[LDIR_Ord] & LLEF) && wc && lfnbuf[i]) return 0;  /* Last segment matched but different length */

  return 1;   /* The part of LFN matched */
}



#if _FS_MINIMIZE <= 1 || _FS_EXFAT
/*-----------------------------------------------------*/
/* FAT-LFN: Pick a part of file name from an LFN entry */
/*-----------------------------------------------------*/
static
int pick_lfn (      /* 1:succeeded, 0:buffer overflow or invalid LFN entry */
  WCHAR* lfnbuf,    /* Pointer to the LFN working buffer */
  BYTE* dir     /* Pointer to the LFN entry */
)
{
  UINT i, s;
  WCHAR wc, uc;


  if (ld_word(dir + LDIR_FstClusLO) != 0) return 0; /* Check LDIR_FstClusLO */

  i = ((dir[LDIR_Ord] & 0x3F) - 1) * 13;  /* Offset in the LFN buffer */

  for (wc = 1, s = 0; s < 13; s++) {    /* Process all characters in the entry */
    uc = ld_word(dir + LfnOfs[s]);    /* Pick an LFN character */
    if (wc) {
      if (i >= _MAX_LFN) return 0;  /* Buffer overflow? */
      lfnbuf[i++] = wc = uc;      /* Store it */
    } else {
      if (uc != 0xFFFF) return 0;   /* Check filler */
    }
  }

  if (dir[LDIR_Ord] & LLEF) {       /* Put terminator if it is the last LFN part */
    if (i >= _MAX_LFN) return 0;    /* Buffer overflow? */
    lfnbuf[i] = 0;
  }

  return 1;   /* The part of LFN is valid */
}
#endif

#if !_FS_READONLY
/*-----------------------------------------*/
/* FAT-LFN: Create an entry of LFN entries */
/*-----------------------------------------*/
static
void put_lfn (
  const WCHAR* lfn, /* Pointer to the LFN */
  BYTE* dir,      /* Pointer to the LFN entry to be created */
  BYTE ord,     /* LFN order (1-20) */
  BYTE sum      /* Checksum of the corresponding SFN */
)
{
  UINT i, s;
  WCHAR wc;


  dir[LDIR_Chksum] = sum;     /* Set checksum */
  dir[LDIR_Attr] = AM_LFN;    /* Set attribute. LFN entry */
  dir[LDIR_Type] = 0;
  st_word(dir + LDIR_FstClusLO, 0);

  i = (ord - 1) * 13;       /* Get offset in the LFN working buffer */
  s = wc = 0;
  do {
    if (wc != 0xFFFF) wc = lfn[i++];  /* Get an effective character */
    st_word(dir + LfnOfs[s], wc);   /* Put it */
    if (wc == 0) wc = 0xFFFF;   /* Padding characters for left locations */
  } while (++s < 13);
  if (wc == 0xFFFF || !lfn[i]) ord |= LLEF; /* Last LFN part is the start of LFN sequence */
  dir[LDIR_Ord] = ord;      /* Set the LFN order */
}

#endif
#endif



/*-----------------------------------------------------------------------*/
/* FAT-LFN: Create a Numbered SFN                                        */
/*-----------------------------------------------------------------------*/
#if _USE_LFN != 0 && !_FS_READONLY
static
void gen_numname (
  BYTE* dst,      /* Pointer to the buffer to store numbered SFN */
  const BYTE* src,  /* Pointer to SFN */
  const WCHAR* lfn, /* Pointer to LFN */
  UINT seq      /* Sequence number */
)
{
  BYTE ns[8], c;
  UINT i, j;
  WCHAR wc;
  DWORD sr;


  mem_cpy(dst, src, 11);

  if (seq > 5) {  /* In case of many collisions, generate a hash number instead of sequential number */
    sr = seq;
    while (*lfn) {  /* Create a CRC */
      wc = *lfn++;
      for (i = 0; i < 16; i++) {
        sr = (sr << 1) + (wc & 1);
        wc >>= 1;
        if (sr & 0x10000) sr ^= 0x11021;
      }
    }
    seq = (UINT)sr;
  }

  /* itoa (hexdecimal) */
  i = 7;
  do {
    c = (seq % 16) + '0';
    if (c > '9') c += 7;
    ns[i--] = c;
    seq /= 16;
  } while (seq);
  ns[i] = '~';

  /* Append the number */
  for (j = 0; j < i && dst[j] != ' '; j++) {
    if (IsDBCS1(dst[j])) {
      if (j == i - 1) break;
      j++;
    }
  }
  do {
    dst[j++] = (i < 8) ? ns[i++] : ' ';
  } while (j < 8);
}
#endif



/*-----------------------------------------------------------------------*/
/* FAT-LFN: Calculate checksum of an SFN entry                           */
/*-----------------------------------------------------------------------*/
#if _USE_LFN != 0
static
BYTE sum_sfn (
  const BYTE* dir   /* Pointer to the SFN entry */
)
{
  BYTE sum = 0;
  UINT n = 11;

  do sum = (sum >> 1) + (sum << 7) + *dir++; while (--n);
  return sum;
}
#endif




#if _FS_EXFAT
/*-----------------------------------------------------------------------*/
/* exFAT: Directory handling - Load/Store a block of directory entries   */
/*-----------------------------------------------------------------------*/

static
WORD xdir_sum (     /* Get checksum of the directoly block */
  const BYTE* dir   /* Directory entry block to be calculated */
)
{
  UINT i, szblk;
  WORD sum;


  szblk = (dir[XDIR_NumSec] + 1) * SZDIRE;
  for (i = sum = 0; i < szblk; i++) {
    if (i == XDIR_SetSum) { /* Skip sum field */
      i++;
    } else {
      sum = ((sum & 1) ? 0x8000 : 0) + (sum >> 1) + dir[i];
    }
  }
  return sum;
}



static
WORD xname_sum (    /* Get check sum (to be used as hash) of the name */
  const WCHAR* name /* File name to be calculated */
)
{
  WCHAR chr;
  WORD sum = 0;


  while ((chr = *name++) != 0) {
    chr = ff_wtoupper(chr);   /* File name needs to be ignored case */
    sum = ((sum & 1) ? 0x8000 : 0) + (sum >> 1) + (chr & 0xFF);
    sum = ((sum & 1) ? 0x8000 : 0) + (sum >> 1) + (chr >> 8);
  }
  return sum;
}


/*------------------------------------------------------*/
/* exFAT: Get object information from a directory block */
/*------------------------------------------------------*/
static
void get_xdir_info (
  BYTE* dirb,     /* Pointer to the direcotry entry block 85+C0+C1s */
  FILINFO* fno    /* Buffer to store the extracted file information */
)
{
  UINT di, si, nc;
  WCHAR w;

  /* Get file name */
#if _LFN_UNICODE
  if (dirb[XDIR_NumName] <= _MAX_LFN) {
    for (si = SZDIRE * 2, di = 0; di < dirb[XDIR_NumName]; si += 2, di++) {
      if ((si % SZDIRE) == 0) si += 2;  /* Skip entry type field */
      w = ld_word(dirb + si);       /* Get a character */
      fno->fname[di] = w;         /* Store it */
    }
  } else {
    di = 0; /* Buffer overflow and inaccessible object */
  }
#else
  for (si = SZDIRE * 2, di = nc = 0; nc < dirb[XDIR_NumName]; si += 2, nc++) {
    if ((si % SZDIRE) == 0) si += 2;  /* Skip entry type field */
    w = ld_word(dirb + si);       /* Get a character */
    w = ff_convert(w, 0);       /* Unicode -> OEM */
    if (w == 0) { di = 0; break; }    /* Could not be converted and inaccessible object */
    if (_DF1S && w >= 0x100) {      /* Put 1st byte if it is a DBC (always false at SBCS cfg) */
      fno->fname[di++] = (char)(w >> 8);
    }
    if (di >= _MAX_LFN) { di = 0; break; }  /* Buffer overflow and inaccessible object */
    fno->fname[di++] = (char)w;
  }
#endif
  if (di == 0) fno->fname[di++] = '?';  /* Inaccessible object? */
  fno->fname[di] = 0;           /* Terminate file name */

  fno->altname[0] = 0;              /* No SFN */
  fno->fattrib = dirb[XDIR_Attr];         /* Attribute */
  fno->fsize = (fno->fattrib & AM_DIR) ? 0 : ld_qword(dirb + XDIR_FileSize);  /* Size */
  fno->ftime = ld_word(dirb + XDIR_ModTime + 0);  /* Time */
  fno->fdate = ld_word(dirb + XDIR_ModTime + 2);  /* Date */
}


/*-----------------------------------*/
/* exFAT: Get a directry entry block */
/*-----------------------------------*/
static
FRESULT load_xdir ( /* FR_INT_ERR: invalid entry block */
  DIR* dp     /* Pointer to the reading direcotry object pointing the 85 entry */
)
{
  FRESULT res;
  UINT i, nent;
  BYTE* dirb = dp->obj.fs->dirbuf;  /* Pointer to the on-memory direcotry entry block 85+C0+C1s */


  /* Load 85 entry */
  res = move_window(dp->obj.fs, dp->sect);
  if (res != FR_OK) return res;
  if (dp->dir[XDIR_Type] != 0x85) return FR_INT_ERR;
  mem_cpy(&dirb[0], dp->dir, SZDIRE);
  nent = dirb[XDIR_NumSec] + 1;

  /* Load C0 entry */
  res = dir_next(dp, 0);
  if (res != FR_OK) return res;
  res = move_window(dp->obj.fs, dp->sect);
  if (res != FR_OK) return res;
  if (dp->dir[XDIR_Type] != 0xC0) return FR_INT_ERR;
  mem_cpy(dirb + SZDIRE, dp->dir, SZDIRE);

  /* Load C1 entries */
  if (nent < 3 || nent > 19) return FR_NO_FILE;
  i = SZDIRE * 2; nent *= SZDIRE;
  do {
    res = dir_next(dp, 0);
    if (res != FR_OK) return res;
    res = move_window(dp->obj.fs, dp->sect);
    if (res != FR_OK) return res;
    if (dp->dir[XDIR_Type] != 0xC1) return FR_INT_ERR;
    mem_cpy(dirb + i, dp->dir, SZDIRE);
    i += SZDIRE;
  } while (i < nent);

  /* Sanity check */
  if (xdir_sum(dirb) != ld_word(dirb + XDIR_SetSum)) return FR_INT_ERR;

  return FR_OK;
}


#if !_FS_READONLY || _FS_RPATH != 0 
/*------------------------------------------------*/
/* exFAT: Load the object's directory entry block */
/*------------------------------------------------*/
static
FRESULT load_obj_dir (
  DIR* dp,      /* Blank directory object to be used to access containing direcotry */
  const _FDID* obj  /* Object with containing directory information */
)
{
  FRESULT res;


  /* Open object containing directory */
  dp->obj.fs = obj->fs;
  dp->obj.sclust = obj->c_scl;
  dp->obj.stat = (BYTE)obj->c_size;
  dp->obj.objsize = obj->c_size & 0xFFFFFF00;
  dp->blk_ofs = obj->c_ofs;

  res = dir_sdi(dp, dp->blk_ofs); /* Goto the block location */
  if (res == FR_OK) {
    res = load_xdir(dp);    /* Load the object's entry block */
  }
  return res;
}
#endif


#if !_FS_READONLY
/*-----------------------------------------------*/
/* exFAT: Store the directory block to the media */
/*-----------------------------------------------*/
static
FRESULT store_xdir (
  DIR* dp       /* Pointer to the direcotry object */
)
{
  FRESULT res;
  UINT nent;
  WORD sum;
  BYTE* dirb = dp->obj.fs->dirbuf;  /* Pointer to the direcotry entry block 85+C0+C1s */

  /* Create set sum */
  sum = xdir_sum(dirb);
  st_word(dirb + XDIR_SetSum, sum);
  nent = dirb[XDIR_NumSec] + 1;

  res = dir_sdi(dp, dp->blk_ofs);
  while (res == FR_OK && (res = move_window(dp->obj.fs, dp->sect)) == FR_OK) {
    mem_cpy(dp->dir, dirb, SZDIRE);
    dp->obj.fs->wflag = 1;
    if (--nent == 0) break;
    dirb += SZDIRE;
    res = dir_next(dp, 0);
  }
  return (res == FR_OK || res == FR_DISK_ERR) ? res : FR_INT_ERR;
}


/*-------------------------------------------*/
/* exFAT: Create a new directory enrty block */
/*-------------------------------------------*/
static
void create_xdir (
  BYTE* dirb,     /* Pointer to the direcotry entry block buffer */
  const WCHAR* lfn  /* Pointer to the nul terminated file name */
)
{
  UINT i;
  BYTE nb, nc;
  WCHAR chr;
  WORD hash;


  mem_set(dirb, 0, 2 * SZDIRE);     /* Initialize 85+C0 entry */
  dirb[XDIR_Type] = 0x85;
  dirb[XDIR_Type + SZDIRE] = 0xC0;
  hash = xname_sum(lfn);
  st_word(dirb + XDIR_NameHash, hash);  /* Set name hash */

  i = SZDIRE * 2; /* C1 offset */
  nc = 0; nb = 1; chr = 1;
  do {
    dirb[i++] = 0xC1; dirb[i++] = 0;  /* Entry type C1 */
    do {  /* Fill name field */
      if (chr && (chr = lfn[nc]) != 0) nc++;  /* Get a character if exist */
      st_word(dirb + i, chr); i += 2; /* Store it */
    } while (i % SZDIRE);
    nb++;
  } while (lfn[nc]);  /* Fill next entry if any char follows */

  dirb[XDIR_NumName] = nc;  /* Set name length */
  dirb[XDIR_NumSec] = nb;   /* Set number of C0+C1s */
}
#endif
#endif



/*-----------------------------------------------------------------------*/
/* Read an object from the directory                                     */
/*-----------------------------------------------------------------------*/
#if _FS_MINIMIZE <= 1 || _FS_RPATH >= 2 || _USE_LABEL || _FS_EXFAT
static
FRESULT dir_read (
  DIR* dp,    /* Pointer to the directory object */
  int vol     /* Filtered by 0:file/directory or 1:volume label */
)
{
  FRESULT res = FR_NO_FILE;
  FATFS *fs = dp->obj.fs;
  BYTE a, c;
#if _USE_LFN != 0
  BYTE ord = 0xFF, sum = 0xFF;
#endif

  while (dp->sect) {
    res = move_window(fs, dp->sect);
    if (res != FR_OK) break;
    c = dp->dir[DIR_Name];  /* Test for the entry type */
    if (c == 0) { res = FR_NO_FILE; break; }  /* Reached to end of the directory */
#if _FS_EXFAT
    if (fs->fs_type == FS_EXFAT) {  /* At the exFAT */
      if (_USE_LABEL && vol) {
        if (c == 0x83) break; /* Volume label entry? */
      } else {
        if (c == 0x85) {    /* Start of the entry block? */
          dp->blk_ofs = dp->dptr; /* Set location of block */
          res = load_xdir(dp);  /* Load the entry block */
          if (res == FR_OK) {
            dp->obj.attr = fs->dirbuf[XDIR_Attr] & AM_MASK; /* Get attribute */
          }
          break;
        }
      }
    } else
#endif
    { /* At the FAT12/16/32 */
      dp->obj.attr = a = dp->dir[DIR_Attr] & AM_MASK; /* Get attribute */
#if _USE_LFN != 0 /* LFN configuration */
      if (c == DDEM || c == '.' || (int)((a & ~AM_ARC) == AM_VOL) != vol) { /* An entry without valid data */
        ord = 0xFF;
      } else {
        if (a == AM_LFN) {      /* An LFN entry is found */
          if (c & LLEF) {     /* Is it start of an LFN sequence? */
            sum = dp->dir[LDIR_Chksum];
            c &= ~LLEF; ord = c;
            dp->blk_ofs = dp->dptr;
          }
          /* Check LFN validity and capture it */
          ord = (c == ord && sum == dp->dir[LDIR_Chksum] && pick_lfn(dp->lfn, dp->dir)) ? ord - 1 : 0xFF;
        } else {          /* An SFN entry is found */
          if (ord || sum != sum_sfn(dp->dir)) { /* Is there a valid LFN? */
            dp->blk_ofs = 0xFFFFFFFF;     /* It has no LFN. */
          }
          break;
        }
      }
#else   /* Non LFN configuration */
      if (c != DDEM && c != '.' && a != AM_LFN && (int)((a & ~AM_ARC) == AM_VOL) == vol) {  /* Is it a valid entry? */
        break;
      }
#endif
    }
    res = dir_next(dp, 0);    /* Next entry */
    if (res != FR_OK) break;
  }

  if (res != FR_OK) dp->sect = 0;   /* Terminate the read operation on error or EOT */
  return res;
}
#endif  /* _FS_MINIMIZE <= 1 || _USE_LABEL || _FS_RPATH >= 2 */



/*-----------------------------------------------------------------------*/
/* Directory handling - Find an object in the directory                  */
/*-----------------------------------------------------------------------*/

static
FRESULT dir_find (  /* FR_OK(0):succeeded, !=0:error */
  DIR* dp     /* Pointer to the directory object with the file name */
)
{
  FRESULT res;
  FATFS *fs = dp->obj.fs;
  BYTE c;
#if _USE_LFN != 0
  BYTE a, ord, sum;
#endif

  res = dir_sdi(dp, 0);     /* Rewind directory object */
  if (res != FR_OK) return res;
#if _FS_EXFAT
  if (fs->fs_type == FS_EXFAT) {  /* At the exFAT */
    BYTE nc;
    UINT di, ni;
    WORD hash = xname_sum(dp->lfn);   /* Hash value of the name to find */

    while ((res = dir_read(dp, 0)) == FR_OK) {  /* Read an item */
      if (ld_word(fs->dirbuf + XDIR_NameHash) != hash) continue;  /* Skip the comparison if hash value mismatched */
      for (nc = fs->dirbuf[XDIR_NumName], di = SZDIRE * 2, ni = 0; nc; nc--, di += 2, ni++) { /* Compare the name */
        if ((di % SZDIRE) == 0) di += 2;
        if (ff_wtoupper(ld_word(fs->dirbuf + di)) != ff_wtoupper(dp->lfn[ni])) break;
      }
      if (nc == 0 && !dp->lfn[ni]) break; /* Name matched? */
    }
    return res;
  }
#endif
  /* At the FAT12/16/32 */
#if _USE_LFN != 0
  ord = sum = 0xFF; dp->blk_ofs = 0xFFFFFFFF; /* Reset LFN sequence */
#endif
  do {
    res = move_window(fs, dp->sect);
    if (res != FR_OK) break;
    c = dp->dir[DIR_Name];
    if (c == 0) { res = FR_NO_FILE; break; }  /* Reached to end of table */
#if _USE_LFN != 0 /* LFN configuration */
    dp->obj.attr = a = dp->dir[DIR_Attr] & AM_MASK;
    if (c == DDEM || ((a & AM_VOL) && a != AM_LFN)) { /* An entry without valid data */
      ord = 0xFF; dp->blk_ofs = 0xFFFFFFFF; /* Reset LFN sequence */
    } else {
      if (a == AM_LFN) {      /* An LFN entry is found */
        if (dp->lfn) {
          if (c & LLEF) {   /* Is it start of LFN sequence? */
            sum = dp->dir[LDIR_Chksum];
            c &= ~LLEF; ord = c;  /* LFN start order */
            dp->blk_ofs = dp->dptr; /* Start offset of LFN */
          }
          /* Check validity of the LFN entry and compare it with given name */
          ord = (c == ord && sum == dp->dir[LDIR_Chksum] && cmp_lfn(dp->lfn, dp->dir)) ? ord - 1 : 0xFF;
        }
      } else {          /* An SFN entry is found */
        if (!ord && sum == sum_sfn(dp->dir)) break; /* LFN matched? */
        if (!(dp->fn[NSFLAG] & NS_LOSS) && !mem_cmp(dp->dir, dp->fn, 11)) break;  /* SFN matched? */
        ord = 0xFF; dp->blk_ofs = 0xFFFFFFFF; /* Reset LFN sequence */
      }
    }
#else   /* Non LFN configuration */
    dp->obj.attr = dp->dir[DIR_Attr] & AM_MASK;
    if (!(dp->dir[DIR_Attr] & AM_VOL) && !mem_cmp(dp->dir, dp->fn, 11)) break;  /* Is it a valid entry? */
#endif
    res = dir_next(dp, 0);  /* Next entry */
  } while (res == FR_OK);

  return res;
}




/*-----------------------------------------------------------------------*/
/* Register an object to the directory                                   */
/*-----------------------------------------------------------------------*/
#if !_FS_READONLY
static
FRESULT dir_register (  /* FR_OK:succeeded, FR_DENIED:no free entry or too many SFN collision, FR_DISK_ERR:disk error */
  DIR* dp       /* Target directory with object name to be created */
)
{
  FRESULT res;
  FATFS *fs = dp->obj.fs;
#if _USE_LFN != 0 /* LFN configuration */
  UINT n, nlen, nent;
  BYTE sn[12], *fn, sum;
  WCHAR *lfn;


  fn = dp->fn; lfn = dp->lfn;
  if (fn[NSFLAG] & (NS_DOT | NS_NONAME)) return FR_INVALID_NAME;  /* Check name validity */
  for (nlen = 0; lfn[nlen]; nlen++) ; /* Get lfn length */

#if _FS_EXFAT
  if (fs->fs_type == FS_EXFAT) {  /* At the exFAT */
    DIR dj;

    nent = (nlen + 14) / 15 + 2;  /* Number of entries to allocate (85+C0+C1s) */
    res = dir_alloc(dp, nent);    /* Allocate entries */
    if (res != FR_OK) return res;
    dp->blk_ofs = dp->dptr - SZDIRE * (nent - 1);     /* Set block position */

    if (dp->obj.stat & 4) {     /* Has the sub-directory been stretched? */
      dp->obj.stat &= 3;
      dp->obj.objsize += (DWORD)fs->csize * SS(fs); /* Increase object size by cluster size */
      res = fill_fat_chain(&dp->obj); /* Complement FAT chain if needed */
      if (res != FR_OK) return res;
      res = load_obj_dir(&dj, &dp->obj);
      if (res != FR_OK) return res; /* Load the object status */
      st_qword(fs->dirbuf + XDIR_FileSize, dp->obj.objsize);    /* Update the allocation status */
      st_qword(fs->dirbuf + XDIR_ValidFileSize, dp->obj.objsize);
      fs->dirbuf[XDIR_GenFlags] = dp->obj.stat | 1;
      res = store_xdir(&dj);      /* Store the object status */
      if (res != FR_OK) return res;
    }

    create_xdir(fs->dirbuf, lfn); /* Create on-memory directory block to be written later */
    return FR_OK;
  }
#endif
  /* At the FAT12/16/32 */
  mem_cpy(sn, fn, 12);
  if (sn[NSFLAG] & NS_LOSS) {     /* When LFN is out of 8.3 format, generate a numbered name */
    fn[NSFLAG] = 0; dp->lfn = 0;    /* Find only SFN */
    for (n = 1; n < 100; n++) {
      gen_numname(fn, sn, lfn, n);  /* Generate a numbered name */
      res = dir_find(dp);       /* Check if the name collides with existing SFN */
      if (res != FR_OK) break;
    }
    if (n == 100) return FR_DENIED;   /* Abort if too many collisions */
    if (res != FR_NO_FILE) return res;  /* Abort if the result is other than 'not collided' */
    fn[NSFLAG] = sn[NSFLAG]; dp->lfn = lfn;
  }

  /* Create an SFN with/without LFNs. */
  nent = (sn[NSFLAG] & NS_LFN) ? (nlen + 12) / 13 + 1 : 1;  /* Number of entries to allocate */
  res = dir_alloc(dp, nent);    /* Allocate entries */
  if (res == FR_OK && --nent) { /* Set LFN entry if needed */
    res = dir_sdi(dp, dp->dptr - nent * SZDIRE);
    if (res == FR_OK) {
      sum = sum_sfn(dp->fn);  /* Checksum value of the SFN tied to the LFN */
      do {          /* Store LFN entries in bottom first */
        res = move_window(fs, dp->sect);
        if (res != FR_OK) break;
        put_lfn(dp->lfn, dp->dir, (BYTE)nent, sum);
        fs->wflag = 1;
        res = dir_next(dp, 0);  /* Next entry */
      } while (res == FR_OK && --nent);
    }
  }

#else /* Non LFN configuration */
  res = dir_alloc(dp, 1);   /* Allocate an entry for SFN */

#endif

  /* Set SFN entry */
  if (res == FR_OK) {
    res = move_window(fs, dp->sect);
    if (res == FR_OK) {
      mem_set(dp->dir, 0, SZDIRE);  /* Clean the entry */
      mem_cpy(dp->dir + DIR_Name, dp->fn, 11);  /* Put SFN */
#if _USE_LFN != 0
      dp->dir[DIR_NTres] = dp->fn[NSFLAG] & (NS_BODY | NS_EXT); /* Put NT flag */
#endif
      fs->wflag = 1;
    }
  }

  return res;
}
#endif /* !_FS_READONLY */




/*-----------------------------------------------------------------------*/
/* Remove an object from the directory                                   */
/*-----------------------------------------------------------------------*/
#if !_FS_READONLY && !_FS_MINIMIZE
static
FRESULT dir_remove (  /* FR_OK:Succeeded, FR_DISK_ERR:A disk error */
  DIR* dp       /* Directory object pointing the entry to be removed */
)
{
  FRESULT res;
  FATFS *fs = dp->obj.fs;
#if _USE_LFN != 0 /* LFN configuration */
  DWORD last = dp->dptr;

  res = dp->blk_ofs == 0xFFFFFFFF ? FR_OK : dir_sdi(dp, dp->blk_ofs); /* Goto top of the entry block if LFN is exist */
  if (res == FR_OK) {
    do {
      res = move_window(fs, dp->sect);
      if (res != FR_OK) break;
      /* Mark an entry 'deleted' */
      if (_FS_EXFAT && fs->fs_type == FS_EXFAT) { /* At the exFAT */
        dp->dir[XDIR_Type] &= 0x7F;
      } else {                  /* At the FAT12/16/32 */
        dp->dir[DIR_Name] = DDEM;
      }
      fs->wflag = 1;
      if (dp->dptr >= last) break;  /* If reached last entry then all entries of the object has been deleted. */
      res = dir_next(dp, 0);  /* Next entry */
    } while (res == FR_OK);
    if (res == FR_NO_FILE) res = FR_INT_ERR;
  }
#else     /* Non LFN configuration */

  res = move_window(fs, dp->sect);
  if (res == FR_OK) {
    dp->dir[DIR_Name] = DDEM;
    fs->wflag = 1;
  }
#endif

  return res;
}
#endif /* !_FS_READONLY */




/*-----------------------------------------------------------------------*/
/* Get file information from directory entry                             */
/*-----------------------------------------------------------------------*/
#if _FS_MINIMIZE <= 1 || _FS_RPATH >= 2
static
void get_fileinfo (   /* No return code */
  DIR* dp,      /* Pointer to the directory object */
  FILINFO* fno    /* Pointer to the file information to be filled */
)
{
  UINT i, j;
  TCHAR c;
#if _USE_LFN != 0
  WCHAR w, *lfn;
  WCHAR lfv;
#endif


  fno->fname[0] = 0;    /* Invaidate file info */
  if (!dp->sect) return;  /* Exit if read pointer has reached end of directory */

#if _USE_LFN != 0 /* LFN configuration */
#if _FS_EXFAT
  if (dp->obj.fs->fs_type == FS_EXFAT) {  /* At the exFAT */
    get_xdir_info(dp->obj.fs->dirbuf, fno);
    return;
  } else
#endif
  { /* At the FAT12/16/32 */
    if (dp->blk_ofs != 0xFFFFFFFF) {  /* Get LFN if available */
      i = 0; lfn = dp->lfn;
      while ((w = *lfn++) != 0) {   /* Get an LFN character */
#if !_LFN_UNICODE
        w = ff_convert(w, 0);   /* Unicode -> OEM */
        if (w == 0) { i = 0; break; } /* No LFN if it could not be converted */
        if (_DF1S && w >= 0x100) {  /* Put 1st byte if it is a DBC (always false at SBCS cfg) */
          fno->fname[i++] = (char)(w >> 8);
        }
#endif
        if (i >= _MAX_LFN) { i = 0; break; }  /* No LFN if buffer overflow */
        fno->fname[i++] = (char)w;
      }
      fno->fname[i] = 0;  /* Terminate the LFN */
    }
  }

  i = j = 0;
  lfv = fno->fname[i];  /* LFN is exist if non-zero */
  while (i < 11) {    /* Copy name body and extension */
    c = (TCHAR)dp->dir[i++];
    if (c == ' ') continue;       /* Skip padding spaces */
    if (c == RDDEM) c = (TCHAR)DDEM;  /* Restore replaced DDEM character */
    if (i == 9) {           /* Insert a . if extension is exist */
      if (!lfv) fno->fname[j] = '.';
      fno->altname[j++] = '.';
    }
#if _LFN_UNICODE
    if (IsDBCS1(c) && i != 8 && i != 11 && IsDBCS2(dp->dir[i])) {
      c = c << 8 | dp->dir[i++];
    }
    c = ff_convert(c, 1); /* OEM -> Unicode */
    if (!c) c = '?';
#endif
    fno->altname[j] = c;
    if (!lfv) {
      if (IsUpper(c) && (dp->dir[DIR_NTres] & (i >= 9 ? NS_EXT : NS_BODY))) {
        c += 0x20;      /* To lower */
      }
      fno->fname[j] = c;
    }
    j++;
  }
  if (!lfv) {
    fno->fname[j] = 0;
    if (!dp->dir[DIR_NTres]) j = 0; /* Altname is no longer needed if neither LFN nor case info is exist. */
  }
  fno->altname[j] = 0;  /* Terminate the SFN */

#else /* Non-LFN configuration */
  i = j = 0;
  while (i < 11) {    /* Copy name body and extension */
    c = (TCHAR)dp->dir[i++];
    if (c == ' ') continue;       /* Skip padding spaces */
    if (c == RDDEM) c = (TCHAR)DDEM;  /* Restore replaced DDEM character */
    if (i == 9) fno->fname[j++] = '.';  /* Insert a . if extension is exist */
    fno->fname[j++] = c;
  }
  fno->fname[j] = 0;
#endif

  fno->fattrib = dp->dir[DIR_Attr];       /* Attribute */
  fno->fsize = ld_dword(dp->dir + DIR_FileSize);  /* Size */
  fno->fdate = ld_word(dp->dir + DIR_WrtDate);  /* Date */
  fno->ftime = ld_word(dp->dir + DIR_WrtTime);  /* Time */
}
#endif /* _FS_MINIMIZE <= 1 || _FS_RPATH >= 2 */




/*-----------------------------------------------------------------------*/
/* Pattern matching                                                      */
/*-----------------------------------------------------------------------*/
#if _USE_FIND && _FS_MINIMIZE <= 1
static
WCHAR get_achar (   /* Get a character and advances ptr 1 or 2 */
  const TCHAR** ptr /* Pointer to pointer to the SBCS/DBCS/Unicode string */
)
{
#if !_LFN_UNICODE
  WCHAR chr;

  chr = (BYTE)*(*ptr)++;          /* Get a byte */
  if (IsLower(chr)) chr -= 0x20;      /* To upper ASCII char */
#ifdef _EXCVT
  if (chr >= 0x80) chr = ExCvt[chr - 0x80]; /* To upper SBCS extended char */
#else
  if (IsDBCS1(chr) && IsDBCS2(**ptr)) {   /* Get DBC 2nd byte if needed */
    chr = chr << 8 | (BYTE)*(*ptr)++;
  }
#endif
  return chr;
#else
  return ff_wtoupper(*(*ptr)++);      /* Get a word and to upper */
#endif
}


static
int pattern_matching (  /* 0:not matched, 1:matched */
  const TCHAR* pat, /* Matching pattern */
  const TCHAR* nam, /* String to be tested */
  int skip,     /* Number of pre-skip chars (number of ?s) */
  int inf       /* Infinite search (* specified) */
)
{
  const TCHAR *pp, *np;
  WCHAR pc, nc;
  int nm, nx;


  while (skip--) {        /* Pre-skip name chars */
    if (!get_achar(&nam)) return 0; /* Branch mismatched if less name chars */
  }
  if (!*pat && inf) return 1;   /* (short circuit) */

  do {
    pp = pat; np = nam;     /* Top of pattern and name to match */
    for (;;) {
      if (*pp == '?' || *pp == '*') { /* Wildcard? */
        nm = nx = 0;
        do {        /* Analyze the wildcard chars */
          if (*pp++ == '?') nm++; else nx = 1;
        } while (*pp == '?' || *pp == '*');
        if (pattern_matching(pp, np, nm, nx)) return 1; /* Test new branch (recursions upto number of wildcard blocks in the pattern) */
        nc = *np; break;  /* Branch mismatched */
      }
      pc = get_achar(&pp);  /* Get a pattern char */
      nc = get_achar(&np);  /* Get a name char */
      if (pc != nc) break;  /* Branch mismatched? */
      if (pc == 0) return 1;  /* Branch matched? (matched at end of both strings) */
    }
    get_achar(&nam);      /* nam++ */
  } while (inf && nc);      /* Retry until end of name if infinite search is specified */

  return 0;
}
#endif /* _USE_FIND && _FS_MINIMIZE <= 1 */




/*-----------------------------------------------------------------------*/
/* Pick a top segment and create the object name in directory form       */
/*-----------------------------------------------------------------------*/

static
FRESULT create_name ( /* FR_OK: successful, FR_INVALID_NAME: could not create */
  DIR* dp,      /* Pointer to the directory object */
  const TCHAR** path  /* Pointer to pointer to the segment in the path string */
)
{
#if _USE_LFN != 0 /* LFN configuration */
  BYTE b, cf;
  WCHAR w, *lfn;
  UINT i, ni, si, di;
  const TCHAR *p;

  /* Create LFN in Unicode */
  p = *path; lfn = dp->lfn; si = di = 0;
  for (;;) {
    w = p[si++];          /* Get a character */
    if (w < ' ' || w == '/' || w == '\\') {   /* Break on end of segment */
      while (p[si] == '/' || p[si] == '\\') si++; /* Skip duplicated separator */
      break;
    }
    if (di >= _MAX_LFN) return FR_INVALID_NAME; /* Reject too long name */
#if !_LFN_UNICODE
    w &= 0xFF;
    if (IsDBCS1(w)) {       /* Check if it is a DBC 1st byte (always false on SBCS cfg) */
      b = (BYTE)p[si++];      /* Get 2nd byte */
      w = (w << 8) + b;     /* Create a DBC */
      if (!IsDBCS2(b)) return FR_INVALID_NAME;  /* Reject invalid sequence */
    }
    w = ff_convert(w, 1);     /* Convert ANSI/OEM to Unicode */
    if (!w) return FR_INVALID_NAME; /* Reject invalid code */
#endif
    if (w < 0x80 && chk_chr("\"*:<>\?|\x7F", w)) return FR_INVALID_NAME;  /* Reject illegal characters for LFN */
    lfn[di++] = w;          /* Store the Unicode character */
  }
  *path = &p[si];           /* Return pointer to the next segment */
  cf = (w < ' ') ? NS_LAST : 0;   /* Set last segment flag if end of path */
#if _FS_RPATH != 0
  if ((di == 1 && lfn[di - 1] == '.') ||
    (di == 2 && lfn[di - 1] == '.' && lfn[di - 2] == '.')) {  /* Is this segment a dot name? */
    lfn[di] = 0;
    for (i = 0; i < 11; i++)    /* Create dot name for SFN entry */
      dp->fn[i] = (i < di) ? '.' : ' ';
    dp->fn[i] = cf | NS_DOT;    /* This is a dot entry */
    return FR_OK;
  }
#endif
  while (di) {            /* Snip off trailing spaces and dots if exist */
    w = lfn[di - 1];
    if (w != ' ' && w != '.') break;
    di--;
  }
  lfn[di] = 0;            /* LFN is created */
  if (di == 0) return FR_INVALID_NAME;  /* Reject nul name */

  /* Create SFN in directory form */
  mem_set(dp->fn, ' ', 11);
  for (si = 0; lfn[si] == ' ' || lfn[si] == '.'; si++) ;  /* Strip leading spaces and dots */
  if (si) cf |= NS_LOSS | NS_LFN;
  while (di && lfn[di - 1] != '.') di--;  /* Find extension (di<=si: no extension) */

  b = i = 0; ni = 8;
  for (;;) {
    w = lfn[si++];          /* Get an LFN character */
    if (!w) break;          /* Break on end of the LFN */
    if (w == ' ' || (w == '.' && si != di)) { /* Remove spaces and dots */
      cf |= NS_LOSS | NS_LFN; continue;
    }

    if (i >= ni || si == di) {    /* Extension or end of SFN */
      if (ni == 11) {       /* Long extension */
        cf |= NS_LOSS | NS_LFN; break;
      }
      if (si != di) cf |= NS_LOSS | NS_LFN; /* Out of 8.3 format */
      if (si > di) break;     /* No extension */
      si = di; i = 8; ni = 11;  /* Enter extension section */
      b <<= 2; continue;
    }

    if (w >= 0x80) {        /* Non ASCII character */
#ifdef _EXCVT
      w = ff_convert(w, 0);   /* Unicode -> OEM code */
      if (w) w = ExCvt[w - 0x80]; /* Convert extended character to upper (SBCS) */
#else
      w = ff_convert(ff_wtoupper(w), 0);  /* Upper converted Unicode -> OEM code */
#endif
      cf |= NS_LFN;       /* Force create LFN entry */
    }

    if (_DF1S && w >= 0x100) {    /* Is this DBC? (always false at SBCS cfg) */
      if (i >= ni - 1) {
        cf |= NS_LOSS | NS_LFN; i = ni; continue;
      }
      dp->fn[i++] = (BYTE)(w >> 8);
    } else {            /* SBC */
      if (!w || chk_chr("+,;=[]", w)) { /* Replace illegal characters for SFN */
        w = '_'; cf |= NS_LOSS | NS_LFN;/* Lossy conversion */
      } else {
        if (IsUpper(w)) {   /* ASCII large capital */
          b |= 2;
        } else {
          if (IsLower(w)) { /* ASCII small capital */
            b |= 1; w -= 0x20;
          }
        }
      }
    }
    dp->fn[i++] = (BYTE)w;
  }

  if (dp->fn[0] == DDEM) dp->fn[0] = RDDEM; /* If the first character collides with DDEM, replace it with RDDEM */

  if (ni == 8) b <<= 2;
  if ((b & 0x0C) == 0x0C || (b & 0x03) == 0x03) cf |= NS_LFN; /* Create LFN entry when there are composite capitals */
  if (!(cf & NS_LFN)) {           /* When LFN is in 8.3 format without extended character, NT flags are created */
    if ((b & 0x03) == 0x01) cf |= NS_EXT; /* NT flag (Extension has only small capital) */
    if ((b & 0x0C) == 0x04) cf |= NS_BODY;  /* NT flag (Filename has only small capital) */
  }

  dp->fn[NSFLAG] = cf;  /* SFN is created */

  return FR_OK;


#else /* Non-LFN configuration */
  BYTE b, c, d, *sfn;
  UINT ni, si, i;
  const char *p;

  /* Create file name in directory form */
  p = *path; sfn = dp->fn;
  mem_set(sfn, ' ', 11);
  si = i = b = 0; ni = 8;
#if _FS_RPATH != 0
  if (p[si] == '.') { /* Is this a dot entry? */
    for (;;) {
      c = (BYTE)p[si++];
      if (c != '.' || si >= 3) break;
      sfn[i++] = c;
    }
    if (c != '/' && c != '\\' && c > ' ') return FR_INVALID_NAME;
    *path = &p[si];                 /* Return pointer to the next segment */
    sfn[NSFLAG] = (c <= ' ') ? NS_LAST | NS_DOT : NS_DOT; /* Set last segment flag if end of path */
    return FR_OK;
  }
#endif
  for (;;) {
    c = (BYTE)p[si++];
    if (c <= ' ' || c == '/' || c == '\\') {  /* Break on end of segment */
      while (p[si] == '/' || p[si] == '\\') si++; /* Skip duplicated separator */
      break;
    }
    if (c == '.' || i >= ni) {
      if (ni != 8 || c != '.') return FR_INVALID_NAME;
      i = 8; ni = 11;
      b <<= 2; continue;
    }
    if (c >= 0x80) {        /* Extended character? */
      b |= 3;           /* Eliminate NT flag */
#ifdef _EXCVT
      c = ExCvt[c - 0x80];    /* To upper extended characters (SBCS cfg) */
#else
#if !_DF1S
      return FR_INVALID_NAME;   /* Reject extended characters (ASCII cfg) */
#endif
#endif
    }
    if (IsDBCS1(c)) {       /* Check if it is a DBC 1st byte (always false at SBCS cfg.) */
      d = (BYTE)p[si++];      /* Get 2nd byte */
      if (!IsDBCS2(d) || i >= ni - 1) return FR_INVALID_NAME; /* Reject invalid DBC */
      sfn[i++] = c;
      sfn[i++] = d;
    } else {            /* SBC */
      if (chk_chr("\"*+,:;<=>\?[]|\x7F", c)) return FR_INVALID_NAME;  /* Reject illegal chrs for SFN */
      if (IsUpper(c)) {     /* ASCII large capital? */
        b |= 2;
      } else {
        if (IsLower(c)) {   /* ASCII small capital? */
          b |= 1; c -= 0x20;
        }
      }
      sfn[i++] = c;
    }
  }
  *path = &p[si];           /* Return pointer to the next segment */
  c = (c <= ' ') ? NS_LAST : 0;   /* Set last segment flag if end of path */

  if (i == 0) return FR_INVALID_NAME; /* Reject nul string */
  if (sfn[0] == DDEM) sfn[0] = RDDEM; /* When first character collides with DDEM, replace it with RDDEM */

  if (ni == 8) b <<= 2;
  if ((b & 0x03) == 0x01) c |= NS_EXT;  /* NT flag (Name extension has only small capital) */
  if ((b & 0x0C) == 0x04) c |= NS_BODY; /* NT flag (Name body has only small capital) */

  sfn[NSFLAG] = c;    /* Store NT flag, File name is created */

  return FR_OK;
#endif
}




/*-----------------------------------------------------------------------*/
/* Follow a file path                                                    */
/*-----------------------------------------------------------------------*/

static
FRESULT follow_path ( /* FR_OK(0): successful, !=0: error code */
  DIR* dp,      /* Directory object to return last directory and found object */
  const TCHAR* path /* Full-path string to find a file or directory */
)
{
  FRESULT res;
  BYTE ns;
  _FDID *obj = &dp->obj;
  FATFS *fs = obj->fs;


#if _FS_RPATH != 0
  if (*path != '/' && *path != '\\') {  /* Without heading separator */
    obj->sclust = fs->cdir;       /* Start from the current directory */
  } else
#endif
  {                   /* With heading separator */
    while (*path == '/' || *path == '\\') path++; /* Strip heading separator */
    obj->sclust = 0;          /* Start from the root directory */
  }
#if _FS_EXFAT && _FS_RPATH != 0
  if (fs->fs_type == FS_EXFAT && obj->sclust) { /* Retrieve the sub-directory status if needed */
    DIR dj;

    obj->c_scl = fs->cdc_scl;
    obj->c_size = fs->cdc_size;
    obj->c_ofs = fs->cdc_ofs;
    res = load_obj_dir(&dj, obj);
    if (res != FR_OK) return res;
    obj->objsize = ld_dword(fs->dirbuf + XDIR_FileSize);
    obj->stat = fs->dirbuf[XDIR_GenFlags] & 2;
  }
#endif

  if ((UINT)*path < ' ') {        /* Null path name is the origin directory itself */
    dp->fn[NSFLAG] = NS_NONAME;
    res = dir_sdi(dp, 0);

  } else {                /* Follow path */
    for (;;) {
      res = create_name(dp, &path); /* Get a segment name of the path */
      if (res != FR_OK) break;
      res = dir_find(dp);       /* Find an object with the segment name */
      ns = dp->fn[NSFLAG];
      if (res != FR_OK) {       /* Failed to find the object */
        if (res == FR_NO_FILE) {  /* Object is not found */
          if (_FS_RPATH && (ns & NS_DOT)) { /* If dot entry is not exist, stay there */
            if (!(ns & NS_LAST)) continue;  /* Continue to follow if not last segment */
            dp->fn[NSFLAG] = NS_NONAME;
            res = FR_OK;
          } else {              /* Could not find the object */
            if (!(ns & NS_LAST)) res = FR_NO_PATH;  /* Adjust error code if not last segment */
          }
        }
        break;
      }
      if (ns & NS_LAST) break;      /* Last segment matched. Function completed. */
      /* Get into the sub-directory */
      if (!(obj->attr & AM_DIR)) {    /* It is not a sub-directory and cannot follow */
        res = FR_NO_PATH; break;
      }
#if _FS_EXFAT
      if (fs->fs_type == FS_EXFAT) {
        obj->c_scl = obj->sclust;   /* Save containing directory information for next dir */
        obj->c_size = ((DWORD)obj->objsize & 0xFFFFFF00) | obj->stat;
        obj->c_ofs = dp->blk_ofs;
        obj->sclust = ld_dword(fs->dirbuf + XDIR_FstClus);  /* Open next directory */
        obj->stat = fs->dirbuf[XDIR_GenFlags] & 2;
        obj->objsize = ld_qword(fs->dirbuf + XDIR_FileSize);
      } else
#endif
      {
        obj->sclust = ld_clust(fs, &fs->win[dp->dptr % SS(fs)]);  /* Open next directory */
      }
    }
  }

  return res;
}




/*-----------------------------------------------------------------------*/
/* Get logical drive number from path name                               */
/*-----------------------------------------------------------------------*/

static
int get_ldnumber (    /* Returns logical drive number (-1:invalid drive) */
  const TCHAR** path  /* Pointer to pointer to the path name */
)
{
  const TCHAR *tp, *tt;
  UINT i;
  int vol = -1;
#if _STR_VOLUME_ID    /* Find string drive id */
  static const char* const str[] = {_VOLUME_STRS};
  const char *sp;
  char c;
  TCHAR tc;
#endif


  if (*path) {  /* If the pointer is not a null */
    for (tt = *path; (UINT)*tt >= (_USE_LFN ? ' ' : '!') && *tt != ':'; tt++) ; /* Find ':' in the path */
    if (*tt == ':') { /* If a ':' is exist in the path name */
      tp = *path;
      i = (UINT)(*tp++ - '0');
      if (i < 10 && tp == tt) { /* Is there a numeric drive id? */
        if (i < _VOLUMES) { /* If a drive id is found, get the value and strip it */
          vol = (int)i;
          *path = ++tt;
        }
      }
#if _STR_VOLUME_ID
       else { /* No numeric drive number, find string drive id */
        i = 0; tt++;
        do {
          sp = str[i]; tp = *path;
          do {  /* Compare a string drive id with path name */
            c = *sp++; tc = *tp++;
            if (IsLower(tc)) tc -= 0x20;
          } while (c && (TCHAR)c == tc);
        } while ((c || tp != tt) && ++i < _VOLUMES);  /* Repeat for each id until pattern match */
        if (i < _VOLUMES) { /* If a drive id is found, get the value and strip it */
          vol = (int)i;
          *path = tt;
        }
      }
#endif
      return vol;
    }
#if _FS_RPATH != 0 && _VOLUMES >= 2
    vol = CurrVol;  /* Current drive */
#else
    vol = 0;    /* Drive 0 */
#endif
  }
  return vol;
}




/*-----------------------------------------------------------------------*/
/* Load a sector and check if it is an FAT boot sector                   */
/*-----------------------------------------------------------------------*/

static
BYTE check_fs ( /* 0:FAT, 1:exFAT, 2:Valid BS but not FAT, 3:Not a BS, 4:Disk error */
  FATFS* fs,  /* File system object */
  DWORD sect  /* Sector# (lba) to check if it is an FAT boot record or not */
)
{
  fs->wflag = 0; fs->winsect = 0xFFFFFFFF;    /* Invaidate window */
  if (move_window(fs, sect) != FR_OK) return 4; /* Load boot record */

  if (ld_word(&fs->win[BS_55AA]) != 0xAA55) return 3; /* Check boot record signature (always placed at offset 510 even if the sector size is >512) */

  if ((ld_dword(&fs->win[BS_FilSysType]) & 0xFFFFFF) == 0x544146) return 0; /* Check "FAT" string */
  if ((ld_dword(&fs->win[BS_FilSysType32]) & 0xFFFFFF) == 0x544146) return 0; /* Check "FAT" string */
#if _FS_EXFAT
  if (!mem_cmp(&fs->win[BS_OEMName], "EXFAT   ", 8)) return 1;
#endif
  return 2;
}




/*-----------------------------------------------------------------------*/
/* Find logical drive and check if the volume is mounted                 */
/*-----------------------------------------------------------------------*/

static
FRESULT find_volume ( /* FR_OK(0): successful, !=0: any error occurred */
  const TCHAR** path, /* Pointer to pointer to the path name (drive number) */
  FATFS** rfs,    /* Pointer to pointer to the found file system object */
  BYTE mode     /* !=0: Check write protection for write access */
)
{
  BYTE fmt, *pt;
  int vol;
  DSTATUS stat;
  DWORD bsect, fasize, tsect, sysect, nclst, szbfat, br[4];
  WORD nrsv;
  FATFS *fs;
  UINT i;


  /* Get logical drive number from the path name */
  *rfs = 0;
  vol = get_ldnumber(path);
  if (vol < 0) return FR_INVALID_DRIVE;

  /* Check if the file system object is valid or not */
  fs = FatFs[vol];          /* Get pointer to the file system object */
  if (!fs) return FR_NOT_ENABLED;   /* Is the file system object available? */

  ENTER_FF(fs);           /* Lock the volume */
  *rfs = fs;              /* Return pointer to the file system object */

  mode &= ~FA_READ;         /* Desired access mode, write access or not */
  if (fs->fs_type) {          /* If the volume has been mounted */
    stat = disk_status(fs->drv);
    if (!(stat & STA_NOINIT)) {   /* and the physical drive is kept initialized */
      if (!_FS_READONLY && mode && (stat & STA_PROTECT)) {  /* Check write protection if needed */
        return FR_WRITE_PROTECTED;
      }
      return FR_OK;       /* The file system object is valid */
    }
  }

  /* The file system object is not valid. */
  /* Following code attempts to mount the volume. (analyze BPB and initialize the fs object) */

  fs->fs_type = 0;          /* Clear the file system object */
  fs->drv = LD2PD(vol);       /* Bind the logical drive and a physical drive */
  stat = disk_initialize(fs->drv);  /* Initialize the physical drive */
  if (stat & STA_NOINIT) {      /* Check if the initialization succeeded */
    return FR_NOT_READY;      /* Failed to initialize due to no medium or hard error */
  }
  if (!_FS_READONLY && mode && (stat & STA_PROTECT)) { /* Check disk write protection if needed */
    return FR_WRITE_PROTECTED;
  }
#if _MAX_SS != _MIN_SS            /* Get sector size (multiple sector size cfg only) */
  if (disk_ioctl(fs->drv, GET_SECTOR_SIZE, &SS(fs)) != RES_OK
    || SS(fs) < _MIN_SS || SS(fs) > _MAX_SS) return FR_DISK_ERR;
#endif
  /* Find an FAT partition on the drive. Supports only generic partitioning, FDISK and SFD. */
  bsect = 0;
  fmt = check_fs(fs, bsect);      /* Load sector 0 and check if it is an FAT boot sector as SFD */
  if (fmt == 2 || (fmt < 2 && LD2PT(vol))) {  /* Not an FAT boot sector or forced partition number */
    for (i = 0; i < 4; i++) {     /* Get partition offset */
      pt = fs->win + MBR_Table + i * SZ_PTE;
      br[i] = pt[4] ? ld_dword(&pt[8]) : 0;
    }
    i = LD2PT(vol);           /* Partition number: 0:auto, 1-4:forced */
    if (i) i--;
    do {                /* Find an FAT volume */
      bsect = br[i];
      fmt = bsect ? check_fs(fs, bsect) : 3;  /* Check the partition */
    } while (!LD2PT(vol) && fmt >= 2 && ++i < 4);
  }
  if (fmt == 4) return FR_DISK_ERR;   /* An error occured in the disk I/O layer */
  if (fmt >= 2) return FR_NO_FILESYSTEM;  /* No FAT volume is found */

  /* An FAT volume is found. Following code initializes the file system object */

#if _FS_EXFAT
  if (fmt == 1) {
    QWORD maxlba;

    for (i = BPB_ZeroedEx; i < BPB_ZeroedEx + 53 && !fs->win[i]; i++) ; /* Check zero filler */
    if (i < BPB_ZeroedEx + 53) return FR_NO_FILESYSTEM;

    if (ld_word(fs->win + BPB_FSVerEx) != 0x100) return FR_NO_FILESYSTEM; /* Check exFAT revision (Must be 1.0) */

    if (1 << fs->win[BPB_BytsPerSecEx] != SS(fs)) /* (BPB_BytsPerSecEx must be equal to the physical sector size) */
      return FR_NO_FILESYSTEM;

    maxlba = ld_qword(fs->win + BPB_TotSecEx) + bsect;  /* Number of sectors on the volume */
    if (maxlba >= 0x100000000) return FR_NO_FILESYSTEM; /* (It cannot be handled in 32-bit LBA) */

    fs->fsize = ld_dword(fs->win + BPB_FatSzEx);  /* Number of sectors per FAT */

    fs->n_fats = fs->win[BPB_NumFATsEx];      /* Number of FATs */
    if (fs->n_fats != 1) return FR_NO_FILESYSTEM; /* (Must be 1) */

    fs->csize = 1 << fs->win[BPB_SecPerClusEx];   /* Cluster size */
    if (fs->csize == 0) return FR_NO_FILESYSTEM;  /* (Must be 1..32768) */

    nclst = ld_dword(fs->win + BPB_NumClusEx);    /* Number of clusters */
    fs->n_fatent = nclst + 2;
    if (fs->n_fatent >= 0x80000000) return FR_NO_FILESYSTEM;  /* (Must be <= 0x7FFFFFFF) */

    /* Boundaries and Limits */
    fs->volbase = bsect;
    fs->database = bsect + ld_dword(fs->win + BPB_DataOfsEx);
    fs->fatbase = bsect + ld_dword(fs->win + BPB_FatOfsEx);
    if (maxlba < fs->database + nclst * fs->csize) return FR_NO_FILESYSTEM; /* (Volume size must not be smaller than the size requiered) */
    fs->dirbase = ld_dword(fs->win + BPB_RootClusEx);

    /* Check if bitmap location is in assumption (at the first cluster) */
    if (move_window(fs, clust2sect(fs, fs->dirbase)) != FR_OK) return FR_DISK_ERR;
    for (i = 0; i < SS(fs); i += SZDIRE) {
      if (fs->win[i] == 0x81 && ld_dword(fs->win + i + 20) == 2) break; /* 81 entry with cluster #2? */
    }
    if (i == SS(fs)) return FR_NO_FILESYSTEM;
#if !_FS_READONLY
    fs->last_clst = fs->free_clst = 0xFFFFFFFF;   /* Initialize cluster allocation information */
#endif
#if _USE_LFN == 1
    fs->dirbuf = DirBuf;  /* Static directory block working buuffer */
#endif
    fmt = FS_EXFAT;     /* FAT sub-type */
  } else
#endif
  {
    if (ld_word(fs->win + BPB_BytsPerSec) != SS(fs)) return FR_NO_FILESYSTEM; /* (BPB_BytsPerSec must be equal to the physical sector size) */

    fasize = ld_word(fs->win + BPB_FATSz16);      /* Number of sectors per FAT */
    if (fasize == 0) fasize = ld_dword(fs->win + BPB_FATSz32);
    fs->fsize = fasize;

    fs->n_fats = fs->win[BPB_NumFATs];          /* Number of FATs */
    if (fs->n_fats != 1 && fs->n_fats != 2) return FR_NO_FILESYSTEM;  /* (Must be 1 or 2) */
    fasize *= fs->n_fats;               /* Number of sectors for FAT area */

    fs->csize = fs->win[BPB_SecPerClus];        /* Cluster size */
    if (fs->csize == 0 || (fs->csize & (fs->csize - 1))) return FR_NO_FILESYSTEM; /* (Must be power of 2) */

    fs->n_rootdir = ld_word(fs->win + BPB_RootEntCnt);  /* Number of root directory entries */
    if (fs->n_rootdir % (SS(fs) / SZDIRE)) return FR_NO_FILESYSTEM; /* (Must be sector aligned) */

    tsect = ld_word(fs->win + BPB_TotSec16);      /* Number of sectors on the volume */
    if (tsect == 0) tsect = ld_dword(fs->win + BPB_TotSec32);

    nrsv = ld_word(fs->win + BPB_RsvdSecCnt);     /* Number of reserved sectors */
    if (nrsv == 0) return FR_NO_FILESYSTEM;       /* (Must not be 0) */

    /* Determine the FAT sub type */
    sysect = nrsv + fasize + fs->n_rootdir / (SS(fs) / SZDIRE); /* RSV + FAT + DIR */
    if (tsect < sysect) return FR_NO_FILESYSTEM;    /* (Invalid volume size) */
    nclst = (tsect - sysect) / fs->csize;       /* Number of clusters */
    if (nclst == 0) return FR_NO_FILESYSTEM;      /* (Invalid volume size) */
    fmt = FS_FAT12;
    if (nclst >= MIN_FAT16) fmt = FS_FAT16;
    if (nclst >= MIN_FAT32) fmt = FS_FAT32;

    /* Boundaries and Limits */
    fs->n_fatent = nclst + 2;             /* Number of FAT entries */
    fs->volbase = bsect;                /* Volume start sector */
    fs->fatbase = bsect + nrsv;             /* FAT start sector */
    fs->database = bsect + sysect;            /* Data start sector */
    if (fmt == FS_FAT32) {
      if (ld_word(fs->win + BPB_FSVer32) != 0) return FR_NO_FILESYSTEM; /* (Must be FAT32 revision 0.0) */
      if (fs->n_rootdir) return FR_NO_FILESYSTEM;   /* (BPB_RootEntCnt must be 0) */
      fs->dirbase = ld_dword(fs->win + BPB_RootClus32); /* Root directory start cluster */
      szbfat = fs->n_fatent * 4;            /* (Needed FAT size) */
    } else {
      if (fs->n_rootdir == 0) return FR_NO_FILESYSTEM;/* (BPB_RootEntCnt must not be 0) */
      fs->dirbase = fs->fatbase + fasize;       /* Root directory start sector */
      szbfat = (fmt == FS_FAT16) ?          /* (Needed FAT size) */
        fs->n_fatent * 2 : fs->n_fatent * 3 / 2 + (fs->n_fatent & 1);
    }
    if (fs->fsize < (szbfat + (SS(fs) - 1)) / SS(fs)) return FR_NO_FILESYSTEM;  /* (BPB_FATSz must not be less than the size needed) */

#if !_FS_READONLY
    /* Initialize cluster allocation information */
    fs->last_clst = fs->free_clst = 0xFFFFFFFF;

    /* Get FSINFO if available */
    fs->fsi_flag = 0x80;
#if (_FS_NOFSINFO & 3) != 3
    if (fmt == FS_FAT32       /* Enable FSINFO only if FAT32 and BPB_FSInfo32 == 1 */
      && ld_word(fs->win + BPB_FSInfo32) == 1
      && move_window(fs, bsect + 1) == FR_OK)
    {
      fs->fsi_flag = 0;
      if (ld_word(fs->win + BS_55AA) == 0xAA55  /* Load FSINFO data if available */
        && ld_dword(fs->win + FSI_LeadSig) == 0x41615252
        && ld_dword(fs->win + FSI_StrucSig) == 0x61417272)
      {
#if (_FS_NOFSINFO & 1) == 0
        fs->free_clst = ld_dword(fs->win + FSI_Free_Count);
#endif
#if (_FS_NOFSINFO & 2) == 0
        fs->last_clst = ld_dword(fs->win + FSI_Nxt_Free);
#endif
      }
    }
#endif
#endif
  }

  fs->fs_type = fmt;  /* FAT sub-type */
  fs->id = ++Fsid;  /* File system mount ID */
#if _FS_RPATH != 0
  fs->cdir = 0;   /* Initialize current directory */
#endif
#if _FS_LOCK != 0   /* Clear file lock semaphores */
  clear_lock(fs);
#endif
  return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Check if the file/directory object is valid or not                    */
/*-----------------------------------------------------------------------*/

static
FRESULT validate (  /* Returns FR_OK or FR_INVALID_OBJECT */
  void* dfp,    /* Pointer to the FIL/DIR object to check validity */
  FATFS** fs    /* Pointer to pointer to the owner file system object to return */
)
{
  _FDID *obj = (_FDID*)dfp; /* Assuming .obj in the FIL/DIR is the first member */
  FRESULT res;


  if (!dfp || !obj->fs || !obj->fs->fs_type || obj->fs->id != obj->id || (disk_status(obj->fs->drv) & STA_NOINIT)) {
    *fs = 0;        /* The object is invalid */
    res = FR_INVALID_OBJECT;
  } else {
    *fs = obj->fs;      /* Owner file sytem object */
    ENTER_FF(obj->fs);    /* Lock file system */
    res = FR_OK;
  }
  return res;
}




/*---------------------------------------------------------------------------

   Public Functions (FatFs API)

----------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------*/
/* Mount/Unmount a Logical Drive                                         */
/*-----------------------------------------------------------------------*/

FRESULT f_mount (
  FATFS* fs,      /* Pointer to the file system object (NULL:unmount)*/
  const TCHAR* path,  /* Logical drive number to be mounted/unmounted */
  BYTE opt      /* Mode option 0:Do not mount (delayed mount), 1:Mount immediately */
)
{
  FATFS *cfs;
  int vol;
  FRESULT res;
  const TCHAR *rp = path;


  vol = get_ldnumber(&rp);
  if (vol < 0) return FR_INVALID_DRIVE;
  cfs = FatFs[vol];         /* Pointer to fs object */

  if (cfs) {
#if _FS_LOCK != 0
    clear_lock(cfs);
#endif
#if _FS_REENTRANT           /* Discard sync object of the current volume */
    if (!ff_del_syncobj(cfs->sobj)) return FR_INT_ERR;
#endif
    cfs->fs_type = 0;       /* Clear old fs object */
  }

  if (fs) {
    fs->fs_type = 0;        /* Clear new fs object */
#if _FS_REENTRANT           /* Create sync object for the new volume */
    if (!ff_cre_syncobj((BYTE)vol, &fs->sobj)) return FR_INT_ERR;
#endif
  }
  FatFs[vol] = fs;          /* Register new fs object */

  if (!fs || opt != 1) return FR_OK;  /* Do not mount now, it will be mounted later */

  res = find_volume(&path, &fs, 0); /* Force mounted the volume */
  LEAVE_FF(fs, res);
}




/*-----------------------------------------------------------------------*/
/* Open or Create a File                                                 */
/*-----------------------------------------------------------------------*/

FRESULT f_open (
  FIL* fp,      /* Pointer to the blank file object */
  const TCHAR* path,  /* Pointer to the file name */
  BYTE mode     /* Access mode and file open mode flags */
)
{
  FRESULT res;
  DIR dj;
  FATFS *fs;
#if !_FS_READONLY
  DWORD dw, cl;
#endif
  DEF_NAMBUF;


  if (!fp) return FR_INVALID_OBJECT;
  fp->obj.fs = 0;   /* Clear file object */

  /* Get logical drive number */
  mode &= _FS_READONLY ? FA_READ : FA_READ | FA_WRITE | FA_CREATE_ALWAYS | FA_OPEN_ALWAYS | FA_CREATE_NEW;
  res = find_volume(&path, &fs, mode);
  if (res == FR_OK) {
    dj.obj.fs = fs;
    INIT_NAMBUF(dj);
    res = follow_path(&dj, path); /* Follow the file path */
#if !_FS_READONLY /* R/W configuration */
    if (res == FR_OK) {
      if (dj.fn[NSFLAG] & NS_NONAME) {  /* Origin directory itself? */
        res = FR_INVALID_NAME;
      }
#if _FS_LOCK != 0
      else {
        res = chk_lock(&dj, (mode & ~FA_READ) ? 1 : 0);
      }
#endif
    }
    /* Create or Open a file */
    if (mode & (FA_CREATE_ALWAYS | FA_OPEN_ALWAYS | FA_CREATE_NEW)) {
      if (res != FR_OK) {         /* No file, create new */
        if (res == FR_NO_FILE)      /* There is no file to open, create a new entry */
#if _FS_LOCK != 0
          res = enq_lock() ? dir_register(&dj) : FR_TOO_MANY_OPEN_FILES;
#else
          res = dir_register(&dj);
#endif
        mode |= FA_CREATE_ALWAYS;   /* File is created */
      }
      else {                /* Any object is already existing */
        if (dj.obj.attr & (AM_RDO | AM_DIR)) {  /* Cannot overwrite it (R/O or DIR) */
          res = FR_DENIED;
        } else {
          if (mode & FA_CREATE_NEW) res = FR_EXIST; /* Cannot create as new file */
        }
      }
      if (res == FR_OK && (mode & FA_CREATE_ALWAYS)) {  /* Truncate it if overwrite mode */
        dw = GET_FATTIME();
#if _FS_EXFAT
        if (fs->fs_type == FS_EXFAT) {
          /* Get current allocation info */
          fp->obj.fs = fs;
          fp->obj.sclust = ld_dword(fs->dirbuf + XDIR_FstClus);
          fp->obj.objsize = ld_qword(fs->dirbuf + XDIR_FileSize);
          fp->obj.stat = fs->dirbuf[XDIR_GenFlags] & 2;
          /* Initialize directory entry block */
          st_dword(fs->dirbuf + XDIR_CrtTime, dw);  /* Set created time */
          fs->dirbuf[XDIR_CrtTime10] = 0;
          st_dword(fs->dirbuf + XDIR_ModTime, dw);  /* Set modified time */
          fs->dirbuf[XDIR_ModTime10] = 0;
          fs->dirbuf[XDIR_Attr] = AM_ARC;       /* Reset attribute */
          st_dword(fs->dirbuf + XDIR_FstClus, 0);   /* Reset file allocation info */
          st_qword(fs->dirbuf + XDIR_FileSize, 0);
          st_qword(fs->dirbuf + XDIR_ValidFileSize, 0);
          fs->dirbuf[XDIR_GenFlags] = 1;
          res = store_xdir(&dj);
          if (res == FR_OK && fp->obj.sclust) {   /* Remove the cluster chain if exist */
            res = remove_chain(&fp->obj, fp->obj.sclust, 0);
            fs->last_clst = fp->obj.sclust - 1;   /* Reuse the cluster hole */
          }
        } else
#endif
        {
          /* Clean directory info */
          st_dword(dj.dir + DIR_CrtTime, dw); /* Set created time */
          st_dword(dj.dir + DIR_WrtTime, dw); /* Set modified time */
          dj.dir[DIR_Attr] = AM_ARC;      /* Reset attribute */
          cl = ld_clust(fs, dj.dir);      /* Get cluster chain */
          st_clust(fs, dj.dir, 0);      /* Reset file allocation info */
          st_dword(dj.dir + DIR_FileSize, 0);
          fs->wflag = 1;

          if (cl) {             /* Remove the cluster chain if exist */
            dw = fs->winsect;
            res = remove_chain(&dj.obj, cl, 0);
            if (res == FR_OK) {
              res = move_window(fs, dw);
              fs->last_clst = cl - 1;   /* Reuse the cluster hole */
            }
          }
        }
      }
    }
    else {  /* Open an existing file */
      if (res == FR_OK) {         /* Following succeeded */
        if (dj.obj.attr & AM_DIR) {   /* It is a directory */
          res = FR_NO_FILE;
        } else {
          if ((mode & FA_WRITE) && (dj.obj.attr & AM_RDO)) { /* R/O violation */
            res = FR_DENIED;
          }
        }
      }
    }
    if (res == FR_OK) {
      if (mode & FA_CREATE_ALWAYS)    /* Set file change flag if created or overwritten */
        mode |= _FA_MODIFIED;
      fp->dir_sect = fs->winsect;     /* Pointer to the directory entry */
      fp->dir_ptr = dj.dir;
#if _FS_LOCK != 0
      fp->obj.lockid = inc_lock(&dj, (mode & ~FA_READ) ? 1 : 0);
      if (!fp->obj.lockid) res = FR_INT_ERR;
#endif
    }
#else   /* R/O configuration */
    if (res == FR_OK) {
      if (dj.fn[NSFLAG] & NS_NONAME) {  /* Origin directory itself? */
        res = FR_INVALID_NAME;
      } else {
        if (dj.obj.attr & AM_DIR) {   /* It is a directory */
          res = FR_NO_FILE;
        }
      }
    }
#endif

    if (res == FR_OK) {
#if _FS_EXFAT
      if (fs->fs_type == FS_EXFAT) {
        fp->obj.sclust = ld_dword(fs->dirbuf + XDIR_FstClus);   /* Get allocation info */
        fp->obj.objsize = ld_qword(fs->dirbuf + XDIR_FileSize);
        fp->obj.stat = fs->dirbuf[XDIR_GenFlags] & 2;
        fp->obj.c_scl = dj.obj.sclust;
        fp->obj.c_size = ((DWORD)dj.obj.objsize & 0xFFFFFF00) | dj.obj.stat;
        fp->obj.c_ofs = dj.blk_ofs;
      } else
#endif
      {
        fp->obj.sclust = ld_clust(fs, dj.dir);        /* Get allocation info */
        fp->obj.objsize = ld_dword(dj.dir + DIR_FileSize);
      }
#if _USE_FASTSEEK
      fp->cltbl = 0;      /* Normal seek mode */
#endif
      fp->err = 0;      /* Clear error flag */
      fp->fptr = 0;     /* Set file pointer */
      fp->sect = 0;     /* Invalidate current data sector */
      fp->flag = mode;    /* File access mode */
      fp->obj.fs = fs;    /* Validate the file object */
      fp->obj.id = fs->id;
    }

    FREE_NAMBUF();
  }

  LEAVE_FF(dj.obj.fs, res);
}




/*-----------------------------------------------------------------------*/
/* Read File                                                             */
/*-----------------------------------------------------------------------*/

FRESULT f_read (
  FIL* fp,  /* Pointer to the file object */
  void* buff, /* Pointer to data buffer */
  UINT btr, /* Number of bytes to read */
  UINT* br  /* Pointer to number of bytes read */
)
{
  FRESULT res;
  FATFS *fs;
  DWORD clst, sect;
  FSIZE_t remain;
  UINT rcnt, cc, csect;
  BYTE *rbuff = (BYTE*)buff;


  *br = 0;  /* Clear read byte counter */
  res = validate(fp, &fs);
  if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) LEAVE_FF(fs, res); /* Check validity */
  if (!(fp->flag & FA_READ)) LEAVE_FF(fs, FR_DENIED); /* Check access mode */
  remain = fp->obj.objsize - fp->fptr;
  if (btr > remain) btr = (UINT)remain;   /* Truncate btr by remaining bytes */

  for ( ;  btr;               /* Repeat until all data read */
    rbuff += rcnt, fp->fptr += rcnt, *br += rcnt, btr -= rcnt) {
    if ((fp->fptr % SS(fs)) == 0) {     /* On the sector boundary? */
      csect = (UINT)(fp->fptr / SS(fs) & (fs->csize - 1));  /* Sector offset in the cluster */
      if (csect == 0) {         /* On the cluster boundary? */
        if (fp->fptr == 0) {      /* On the top of the file? */
          clst = fp->obj.sclust;    /* Follow cluster chain from the origin */
        } else {            /* Middle or end of the file */
#if _USE_FASTSEEK
          if (fp->cltbl) {
            clst = clmt_clust(fp, fp->fptr);  /* Get cluster# from the CLMT */
          } else
#endif
          {
            clst = get_fat(&fp->obj, fp->clust);  /* Follow cluster chain on the FAT */
          }
        }
        if (clst < 2) ABORT(fs, FR_INT_ERR);
        if (clst == 0xFFFFFFFF) ABORT(fs, FR_DISK_ERR);
        fp->clust = clst;       /* Update current cluster */
      }
      sect = clust2sect(fs, fp->clust); /* Get current sector */
      if (!sect) ABORT(fs, FR_INT_ERR);
      sect += csect;
      cc = btr / SS(fs);          /* When remaining bytes >= sector size, */
      if (cc) {             /* Read maximum contiguous sectors directly */
        if (csect + cc > fs->csize) { /* Clip at cluster boundary */
          cc = fs->csize - csect;
        }
        if (disk_read(fs->drv, rbuff, sect, cc) != RES_OK) {
          ABORT(fs, FR_DISK_ERR);
        }
#if !_FS_READONLY && _FS_MINIMIZE <= 2      /* Replace one of the read sectors with cached data if it contains a dirty sector */
#if _FS_TINY
        if (fs->wflag && fs->winsect - sect < cc) {
          mem_cpy(rbuff + ((fs->winsect - sect) * SS(fs)), fs->win, SS(fs));
        }
#else
        if ((fp->flag & _FA_DIRTY) && fp->sect - sect < cc) {
          mem_cpy(rbuff + ((fp->sect - sect) * SS(fs)), fp->buf, SS(fs));
        }
#endif
#endif
        rcnt = SS(fs) * cc;       /* Number of bytes transferred */
        continue;
      }
#if !_FS_TINY
      if (fp->sect != sect) {     /* Load data sector if not in cache */
#if !_FS_READONLY
        if (fp->flag & _FA_DIRTY) {   /* Write-back dirty sector cache */
          if (disk_write(fs->drv, fp->buf, fp->sect, 1) != RES_OK) {
            ABORT(fs, FR_DISK_ERR);
          }
          fp->flag &= ~_FA_DIRTY;
        }
#endif
        if (disk_read(fs->drv, fp->buf, sect, 1) != RES_OK) { /* Fill sector cache */
          ABORT(fs, FR_DISK_ERR);
        }
      }
#endif
      fp->sect = sect;
    }
    rcnt = SS(fs) - ((UINT)fp->fptr % SS(fs));  /* Get partial sector data from sector buffer */
    if (rcnt > btr) rcnt = btr;
#if _FS_TINY
    if (move_window(fs, fp->sect) != FR_OK) { /* Move sector window */
      ABORT(fs, FR_DISK_ERR);
    }
    mem_cpy(rbuff, &fs->win[fp->fptr % SS(fs)], rcnt);  /* Pick partial sector */
#else
    mem_cpy(rbuff, &fp->buf[fp->fptr % SS(fs)], rcnt);  /* Pick partial sector */
#endif
  }

  LEAVE_FF(fs, FR_OK);
}




#if !_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Write File                                                            */
/*-----------------------------------------------------------------------*/

FRESULT f_write (
  FIL* fp,      /* Pointer to the file object */
  const void* buff, /* Pointer to the data to be written */
  UINT btw,     /* Number of bytes to write */
  UINT* bw      /* Pointer to number of bytes written */
)
{
  FRESULT res;
  FATFS *fs;
  DWORD clst, sect;
  UINT wcnt, cc, csect;
  const BYTE *wbuff = (const BYTE*)buff;


  *bw = 0;  /* Clear write byte counter */
  res = validate(fp, &fs);
  if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) LEAVE_FF(fs, res); /* Check validity */
  if (!(fp->flag & FA_WRITE)) LEAVE_FF(fs, FR_DENIED);  /* Check access mode */

  /* Check fptr wrap-around (file size cannot exceed the limit on each FAT specs) */
  if ((_FS_EXFAT && fs->fs_type == FS_EXFAT && fp->fptr + btw < fp->fptr)
    || (DWORD)fp->fptr + btw < (DWORD)fp->fptr) {
    btw = (UINT)(0xFFFFFFFF - (DWORD)fp->fptr);
  }

  for ( ;  btw;             /* Repeat until all data written */
    wbuff += wcnt, fp->fptr += wcnt, fp->obj.objsize = (fp->fptr > fp->obj.objsize) ? fp->fptr : fp->obj.objsize, *bw += wcnt, btw -= wcnt) {
    if ((fp->fptr % SS(fs)) == 0) {   /* On the sector boundary? */
      csect = (UINT)(fp->fptr / SS(fs)) & (fs->csize - 1);  /* Sector offset in the cluster */
      if (csect == 0) {       /* On the cluster boundary? */
        if (fp->fptr == 0) {    /* On the top of the file? */
          clst = fp->obj.sclust;  /* Follow from the origin */
          if (clst == 0) {    /* If no cluster is allocated, */
            clst = create_chain(&fp->obj, 0); /* create a new cluster chain */
          }
        } else {          /* On the middle or end of the file */
#if _USE_FASTSEEK
          if (fp->cltbl) {
            clst = clmt_clust(fp, fp->fptr);  /* Get cluster# from the CLMT */
          } else
#endif
          {
            clst = create_chain(&fp->obj, fp->clust); /* Follow or stretch cluster chain on the FAT */
          }
        }
        if (clst == 0) break;   /* Could not allocate a new cluster (disk full) */
        if (clst == 1) ABORT(fs, FR_INT_ERR);
        if (clst == 0xFFFFFFFF) ABORT(fs, FR_DISK_ERR);
        fp->clust = clst;     /* Update current cluster */
        if (fp->obj.sclust == 0) fp->obj.sclust = clst; /* Set start cluster if the first write */
      }
#if _FS_TINY
      if (fs->winsect == fp->sect && sync_window(fs) != FR_OK)  { /* Write-back sector cache */
        ABORT(fs, FR_DISK_ERR);
      }
#else
      if (fp->flag & _FA_DIRTY) {   /* Write-back sector cache */
        if (disk_write(fs->drv, fp->buf, fp->sect, 1) != RES_OK) {
          ABORT(fs, FR_DISK_ERR);
        }
        fp->flag &= ~_FA_DIRTY;
      }
#endif
      sect = clust2sect(fs, fp->clust); /* Get current sector */
      if (!sect) ABORT(fs, FR_INT_ERR);
      sect += csect;
      cc = btw / SS(fs);        /* When remaining bytes >= sector size, */
      if (cc) {           /* Write maximum contiguous sectors directly */
        if (csect + cc > fs->csize) { /* Clip at cluster boundary */
          cc = fs->csize - csect;
        }
        if (disk_write(fs->drv, wbuff, sect, cc) != RES_OK) {
          ABORT(fs, FR_DISK_ERR);
        }
#if _FS_MINIMIZE <= 2
#if _FS_TINY
        if (fs->winsect - sect < cc) {  /* Refill sector cache if it gets invalidated by the direct write */
          mem_cpy(fs->win, wbuff + ((fs->winsect - sect) * SS(fs)), SS(fs));
          fs->wflag = 0;
        }
#else
        if (fp->sect - sect < cc) { /* Refill sector cache if it gets invalidated by the direct write */
          mem_cpy(fp->buf, wbuff + ((fp->sect - sect) * SS(fs)), SS(fs));
          fp->flag &= ~_FA_DIRTY;
        }
#endif
#endif
        wcnt = SS(fs) * cc;   /* Number of bytes transferred */
        continue;
      }
#if _FS_TINY
      if (fp->fptr >= fp->obj.objsize) {  /* Avoid silly cache filling at growing edge */
        if (sync_window(fs) != FR_OK) ABORT(fs, FR_DISK_ERR);
        fs->winsect = sect;
      }
#else
      if (fp->sect != sect) {   /* Fill sector cache with file data */
        if (fp->fptr < fp->obj.objsize &&
          disk_read(fs->drv, fp->buf, sect, 1) != RES_OK) {
            ABORT(fs, FR_DISK_ERR);
        }
      }
#endif
      fp->sect = sect;
    }
    wcnt = SS(fs) - ((UINT)fp->fptr % SS(fs));  /* Put partial sector into file I/O buffer */
    if (wcnt > btw) wcnt = btw;
#if _FS_TINY
    if (move_window(fs, fp->sect) != FR_OK) { /* Move sector window */
      ABORT(fs, FR_DISK_ERR);
    }
    mem_cpy(&fs->win[fp->fptr % SS(fs)], wbuff, wcnt);  /* Fit partial sector */
    fs->wflag = 1;
#else
    mem_cpy(&fp->buf[fp->fptr % SS(fs)], wbuff, wcnt);  /* Fit partial sector */
    fp->flag |= _FA_DIRTY;
#endif
  }

  fp->flag |= _FA_MODIFIED;           /* Set file change flag */

  LEAVE_FF(fs, FR_OK);
}




/*-----------------------------------------------------------------------*/
/* Synchronize the File                                                  */
/*-----------------------------------------------------------------------*/

FRESULT f_sync (
  FIL* fp   /* Pointer to the file object */
)
{
  FRESULT res;
  FATFS *fs;
  DWORD tm;
  BYTE *dir;
  DEF_DIRBUF;


  res = validate(fp, &fs);  /* Check validity of the object */
  if (res == FR_OK) {
    if (fp->flag & _FA_MODIFIED) {  /* Is there any change to the file? */
#if !_FS_TINY
      if (fp->flag & _FA_DIRTY) { /* Write-back cached data if needed */
        if (disk_write(fs->drv, fp->buf, fp->sect, 1) != RES_OK) {
          LEAVE_FF(fs, FR_DISK_ERR);
        }
        fp->flag &= ~_FA_DIRTY;
      }
#endif
      /* Update the directory entry */
      tm = GET_FATTIME();       /* Modified time */
#if _FS_EXFAT
      if (fs->fs_type == FS_EXFAT) {
        res = fill_fat_chain(&fp->obj); /* Create FAT chain if needed */
        if (res == FR_OK) {
          DIR dj;

          INIT_DIRBUF(fs);
          res = load_obj_dir(&dj, &fp->obj);  /* Load directory entry block */
          if (res == FR_OK) {
            fs->dirbuf[XDIR_Attr] |= AM_ARC;          /* Set archive bit */
            fs->dirbuf[XDIR_GenFlags] = fp->obj.stat | 1;   /* Update file allocation info */
            st_dword(fs->dirbuf + XDIR_FstClus, fp->obj.sclust);
            st_qword(fs->dirbuf + XDIR_FileSize, fp->obj.objsize);
            st_qword(fs->dirbuf + XDIR_ValidFileSize, fp->obj.objsize);
            st_dword(fs->dirbuf + XDIR_ModTime, tm);      /* Update modified time */
            fs->dirbuf[XDIR_ModTime10] = 0;
            st_dword(fs->dirbuf + XDIR_AccTime, 0);
            res = store_xdir(&dj);  /* Restore it to the directory */
            if (res == FR_OK) {
              res = sync_fs(fs);
              fp->flag &= ~_FA_MODIFIED;
            }
          }
          FREE_DIRBUF();
        }
      } else
#endif
      {
        res = move_window(fs, fp->dir_sect);
        if (res == FR_OK) {
          dir = fp->dir_ptr;
          dir[DIR_Attr] |= AM_ARC;            /* Set archive bit */
          st_clust(fp->obj.fs, dir, fp->obj.sclust);    /* Update file allocation info  */
          st_dword(dir + DIR_FileSize, (DWORD)fp->obj.objsize); /* Update file size */
          st_dword(dir + DIR_WrtTime, tm);        /* Update modified time */
          st_word(dir + DIR_LstAccDate, 0);
          fs->wflag = 1;
          res = sync_fs(fs);          /* Restore it to the directory */
          fp->flag &= ~_FA_MODIFIED;
        }
      }
    }
  }

  LEAVE_FF(fs, res);
}

#endif /* !_FS_READONLY */




/*-----------------------------------------------------------------------*/
/* Close File                                                            */
/*-----------------------------------------------------------------------*/

FRESULT f_close (
  FIL* fp   /* Pointer to the file object to be closed */
)
{
  FRESULT res;
  FATFS *fs;

#if !_FS_READONLY
  res = f_sync(fp);         /* Flush cached data */
  if (res == FR_OK)
#endif
  {
    res = validate(fp, &fs);  /* Lock volume */
    if (res == FR_OK) {
#if _FS_LOCK != 0
      res = dec_lock(fp->obj.lockid); /* Decrement file open counter */
      if (res == FR_OK)
#endif
      {
        fp->obj.fs = 0;     /* Invalidate file object */
      }
#if _FS_REENTRANT
      unlock_fs(fs, FR_OK);   /* Unlock volume */
#endif
    }
  }
  return res;
}




/*-----------------------------------------------------------------------*/
/* Change Current Directory or Current Drive, Get Current Directory      */
/*-----------------------------------------------------------------------*/

#if _FS_RPATH >= 1
#if _VOLUMES >= 2
FRESULT f_chdrive (
  const TCHAR* path   /* Drive number */
)
{
  int vol;


  vol = get_ldnumber(&path);
  if (vol < 0) return FR_INVALID_DRIVE;

  CurrVol = (BYTE)vol;

  return FR_OK;
}
#endif


FRESULT f_chdir (
  const TCHAR* path /* Pointer to the directory path */
)
{
  FRESULT res;
  DIR dj;
  FATFS *fs;
  DEF_NAMBUF;

  /* Get logical drive number */
  res = find_volume(&path, &fs, 0);
  if (res == FR_OK) {
    dj.obj.fs = fs;
    INIT_NAMBUF(dj);
    res = follow_path(&dj, path);   /* Follow the path */
    if (res == FR_OK) {         /* Follow completed */
      if (dj.fn[NSFLAG] & NS_NONAME) {
        fs->cdir = dj.obj.sclust; /* It is the start directory itself */
#if _FS_EXFAT
        if (fs->fs_type == FS_EXFAT) {
          fs->cdc_scl = dj.obj.c_scl;
          fs->cdc_size = dj.obj.c_size;
          fs->cdc_ofs = dj.obj.c_ofs;
        }
#endif
      } else {
        if (dj.obj.attr & AM_DIR) { /* It is a sub-directory */
#if _FS_EXFAT
          if (fs->fs_type == FS_EXFAT) {
            fs->cdir = ld_dword(fs->dirbuf + XDIR_FstClus);   /* Sub-directory cluster */
            fs->cdc_scl = dj.obj.sclust;            /* Save containing directory information */
            fs->cdc_size = ((DWORD)dj.obj.objsize & 0xFFFFFF00) | dj.obj.stat;
            fs->cdc_ofs = dj.blk_ofs;
          } else
#endif
          {
            fs->cdir = ld_clust(fs, dj.dir);          /* Sub-directory cluster */
          }
        } else {
          res = FR_NO_PATH;   /* Reached but a file */
        }
      }
    }
    FREE_NAMBUF();
    if (res == FR_NO_FILE) res = FR_NO_PATH;
  }

  LEAVE_FF(fs, res);
}


#if _FS_RPATH >= 2
FRESULT f_getcwd (
  TCHAR* buff,  /* Pointer to the directory path */
  UINT len    /* Size of path */
)
{
  FRESULT res;
  DIR dj;
  FATFS *fs;
  UINT i, n;
  DWORD ccl;
  TCHAR *tp;
  FILINFO fno;
  DEF_NAMBUF;


  *buff = 0;
  /* Get logical drive number */
  res = find_volume((const TCHAR**)&buff, &fs, 0);  /* Get current volume */
  if (res == FR_OK) {
    dj.obj.fs = fs;
    INIT_NAMBUF(dj);
    i = len;      /* Bottom of buffer (directory stack base) */
    if (!_FS_EXFAT || fs->fs_type != FS_EXFAT) {  /* (Cannot do getcwd on exFAT and returns root path) */
      dj.obj.sclust = fs->cdir;       /* Start to follow upper directory from current directory */
      while ((ccl = dj.obj.sclust) != 0) {  /* Repeat while current directory is a sub-directory */
        res = dir_sdi(&dj, 1 * SZDIRE); /* Get parent directory */
        if (res != FR_OK) break;
        res = move_window(fs, dj.sect);
        if (res != FR_OK) break;
        dj.obj.sclust = ld_clust(fs, dj.dir); /* Goto parent directory */
        res = dir_sdi(&dj, 0);
        if (res != FR_OK) break;
        do {              /* Find the entry links to the child directory */
          res = dir_read(&dj, 0);
          if (res != FR_OK) break;
          if (ccl == ld_clust(fs, dj.dir)) break; /* Found the entry */
          res = dir_next(&dj, 0);
        } while (res == FR_OK);
        if (res == FR_NO_FILE) res = FR_INT_ERR;/* It cannot be 'not found'. */
        if (res != FR_OK) break;
        get_fileinfo(&dj, &fno);    /* Get the directory name and push it to the buffer */
        for (n = 0; fno.fname[n]; n++) ;
        if (i < n + 3) {
          res = FR_NOT_ENOUGH_CORE; break;
        }
        while (n) buff[--i] = fno.fname[--n];
        buff[--i] = '/';
      }
    }
    tp = buff;
    if (res == FR_OK) {
#if _VOLUMES >= 2
      *tp++ = '0' + CurrVol;      /* Put drive number */
      *tp++ = ':';
#endif
      if (i == len) {         /* Root-directory */
        *tp++ = '/';
      } else {            /* Sub-directroy */
        do    /* Add stacked path str */
          *tp++ = buff[i++];
        while (i < len);
      }
    }
    *tp = 0;
    FREE_NAMBUF();
  }

  LEAVE_FF(fs, res);
}
#endif /* _FS_RPATH >= 2 */
#endif /* _FS_RPATH >= 1 */



#if _FS_MINIMIZE <= 2
/*-----------------------------------------------------------------------*/
/* Seek File R/W Pointer                                                 */
/*-----------------------------------------------------------------------*/

FRESULT f_lseek (
  FIL* fp,    /* Pointer to the file object */
  FSIZE_t ofs   /* File pointer from top of file */
)
{
  FRESULT res;
  FATFS *fs;
  DWORD clst, bcs, nsect;
  FSIZE_t ifptr;
#if _USE_FASTSEEK
  DWORD cl, pcl, ncl, tcl, dsc, tlen, ulen, *tbl;
#endif

  res = validate(fp, &fs);    /* Check validity of the object */
  if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) LEAVE_FF(fs, res); /* Check validity */
#if _USE_FASTSEEK
  if (fp->cltbl) {  /* Fast seek */
    if (ofs == CREATE_LINKMAP) {  /* Create CLMT */
      tbl = fp->cltbl;
      tlen = *tbl++; ulen = 2;  /* Given table size and required table size */
      cl = fp->obj.sclust;    /* Top of the chain */
      if (cl) {
        do {
          /* Get a fragment */
          tcl = cl; ncl = 0; ulen += 2; /* Top, length and used items */
          do {
            pcl = cl; ncl++;
            cl = get_fat(&fp->obj, cl);
            if (cl <= 1) ABORT(fs, FR_INT_ERR);
            if (cl == 0xFFFFFFFF) ABORT(fs, FR_DISK_ERR);
          } while (cl == pcl + 1);
          if (ulen <= tlen) {   /* Store the length and top of the fragment */
            *tbl++ = ncl; *tbl++ = tcl;
          }
        } while (cl < fs->n_fatent);  /* Repeat until end of chain */
      }
      *fp->cltbl = ulen;  /* Number of items used */
      if (ulen <= tlen) {
        *tbl = 0;   /* Terminate table */
      } else {
        res = FR_NOT_ENOUGH_CORE; /* Given table size is smaller than required */
      }
    } else {            /* Fast seek */
      if (ofs > fp->obj.objsize) ofs = fp->obj.objsize; /* Clip offset at the file size */
      fp->fptr = ofs;       /* Set file pointer */
      if (ofs) {
        fp->clust = clmt_clust(fp, ofs - 1);
        dsc = clust2sect(fs, fp->clust);
        if (!dsc) ABORT(fs, FR_INT_ERR);
        dsc += (ofs - 1) / SS(fs) & (fs->csize - 1);
        if (fp->fptr % SS(fs) && dsc != fp->sect) { /* Refill sector cache if needed */
#if !_FS_TINY
#if !_FS_READONLY
          if (fp->flag & _FA_DIRTY) {   /* Write-back dirty sector cache */
            if (disk_write(fs->drv, fp->buf, fp->sect, 1) != RES_OK) {
              ABORT(fs, FR_DISK_ERR);
            }
            fp->flag &= ~_FA_DIRTY;
          }
#endif
          if (disk_read(fs->drv, fp->buf, dsc, 1) != RES_OK) {  /* Load current sector */
            ABORT(fs, FR_DISK_ERR);
          }
#endif
          fp->sect = dsc;
        }
      }
    }
  } else
#endif

  /* Normal Seek */
  {
    if (ofs > fp->obj.objsize       /* In read-only mode, clip offset with the file size */
#if !_FS_READONLY
       && !(fp->flag & FA_WRITE)
#endif
      ) ofs = fp->obj.objsize;

    ifptr = fp->fptr;
    fp->fptr = nsect = 0;
    if (ofs) {
      bcs = (DWORD)fs->csize * SS(fs);  /* Cluster size (byte) */
      if (ifptr > 0 &&
        (ofs - 1) / bcs >= (ifptr - 1) / bcs) { /* When seek to same or following cluster, */
        fp->fptr = (ifptr - 1) & ~(bcs - 1);  /* start from the current cluster */
        ofs -= fp->fptr;
        clst = fp->clust;
      } else {                  /* When seek to back cluster, */
        clst = fp->obj.sclust;          /* start from the first cluster */
#if !_FS_READONLY
        if (clst == 0) {            /* If no cluster chain, create a new chain */
          clst = create_chain(&fp->obj, 0);
          if (clst == 1) ABORT(fs, FR_INT_ERR);
          if (clst == 0xFFFFFFFF) ABORT(fs, FR_DISK_ERR);
          fp->obj.sclust = clst;
        }
#endif
        fp->clust = clst;
      }
      if (clst != 0) {
        while (ofs > bcs) {           /* Cluster following loop */
#if !_FS_READONLY
          if (fp->flag & FA_WRITE) {      /* Check if in write mode or not */
            clst = create_chain(&fp->obj, clst);  /* Force stretch if in write mode */
            if (clst == 0) {        /* When disk gets full, clip file size */
              ofs = bcs; break;
            }
          } else
#endif
            clst = get_fat(&fp->obj, clst); /* Follow cluster chain if not in write mode */
          if (clst == 0xFFFFFFFF) ABORT(fs, FR_DISK_ERR);
          if (clst <= 1 || clst >= fs->n_fatent) ABORT(fs, FR_INT_ERR);
          fp->clust = clst;
          fp->fptr += bcs;
          ofs -= bcs;
        }
        fp->fptr += ofs;
        if (ofs % SS(fs)) {
          nsect = clust2sect(fs, clst); /* Current sector */
          if (!nsect) ABORT(fs, FR_INT_ERR);
          nsect += (DWORD)(ofs / SS(fs));
        }
      }
    }
    if (fp->fptr % SS(fs) && nsect != fp->sect) { /* Fill sector cache if needed */
#if !_FS_TINY
#if !_FS_READONLY
      if (fp->flag & _FA_DIRTY) {     /* Write-back dirty sector cache */
        if (disk_write(fs->drv, fp->buf, fp->sect, 1) != RES_OK) {
          ABORT(fs, FR_DISK_ERR);
        }
        fp->flag &= ~_FA_DIRTY;
      }
#endif
      if (disk_read(fs->drv, fp->buf, nsect, 1) != RES_OK) {  /* Fill sector cache */
        ABORT(fs, FR_DISK_ERR);
      }
#endif
      fp->sect = nsect;
    }
#if !_FS_READONLY
    if (fp->fptr > fp->obj.objsize) {   /* Set file change flag if the file size is extended */
      fp->obj.objsize = fp->fptr;
      fp->flag |= _FA_MODIFIED;
    }
#endif
  }

  LEAVE_FF(fs, res);
}



#if _FS_MINIMIZE <= 1
/*-----------------------------------------------------------------------*/
/* Create a Directory Object                                             */
/*-----------------------------------------------------------------------*/

FRESULT f_opendir (
  DIR* dp,      /* Pointer to directory object to create */
  const TCHAR* path /* Pointer to the directory path */
)
{
  FRESULT res;
  FATFS *fs;
  _FDID *obj;
  DEF_NAMBUF;


  if (!dp) return FR_INVALID_OBJECT;

  /* Get logical drive number */
  obj = &dp->obj;
  res = find_volume(&path, &fs, 0);
  if (res == FR_OK) {
    obj->fs = fs;
    INIT_NAMBUF(*dp);
    res = follow_path(dp, path);      /* Follow the path to the directory */
    if (res == FR_OK) {           /* Follow completed */
      if (!(dp->fn[NSFLAG] & NS_NONAME)) {  /* It is not the origin directory itself */
        if (obj->attr & AM_DIR) {   /* This object is a sub-directory */
#if _FS_EXFAT
          if (fs->fs_type == FS_EXFAT) {
            obj->c_scl = obj->sclust; /* Save containing directory inforamation */
            obj->c_size = ((DWORD)obj->objsize & 0xFFFFFF00) | obj->stat;
            obj->c_ofs = dp->blk_ofs;
            obj->sclust = ld_dword(fs->dirbuf + XDIR_FstClus);  /* Get object location and status */
            obj->objsize = ld_qword(fs->dirbuf + XDIR_FileSize);
            obj->stat = fs->dirbuf[XDIR_GenFlags] & 2;
          } else
#endif
          {
            obj->sclust = ld_clust(fs, dp->dir);  /* Get object location */
          }
        } else {            /* This object is a file */
          res = FR_NO_PATH;
        }
      }
      if (res == FR_OK) {
        obj->id = fs->id;
        res = dir_sdi(dp, 0);     /* Rewind directory */
#if _FS_LOCK != 0
        if (res == FR_OK) {
          if (obj->sclust) {
            obj->lockid = inc_lock(dp, 0);  /* Lock the sub directory */
            if (!obj->lockid) res = FR_TOO_MANY_OPEN_FILES;
          } else {
            obj->lockid = 0;  /* Root directory need not to be locked */
          }
        }
#endif
      }
    }
    FREE_NAMBUF();
    if (res == FR_NO_FILE) res = FR_NO_PATH;
  }
  if (res != FR_OK) obj->fs = 0;    /* Invalidate the directory object if function faild */

  LEAVE_FF(fs, res);
}




/*-----------------------------------------------------------------------*/
/* Close Directory                                                       */
/*-----------------------------------------------------------------------*/

FRESULT f_closedir (
  DIR *dp   /* Pointer to the directory object to be closed */
)
{
  FRESULT res;
  FATFS *fs;


  res = validate(dp, &fs);
  if (res == FR_OK) {
#if _FS_LOCK != 0
    if (dp->obj.lockid) {       /* Decrement sub-directory open counter */
      res = dec_lock(dp->obj.lockid);
    }
    if (res == FR_OK)
#endif
    {
      dp->obj.fs = 0;     /* Invalidate directory object */
    }
#if _FS_REENTRANT
    unlock_fs(fs, FR_OK);   /* Unlock volume */
#endif
  }
  return res;
}




/*-----------------------------------------------------------------------*/
/* Read Directory Entries in Sequence                                    */
/*-----------------------------------------------------------------------*/

FRESULT f_readdir (
  DIR* dp,      /* Pointer to the open directory object */
  FILINFO* fno    /* Pointer to file information to return */
)
{
  FRESULT res;
  FATFS *fs;
  DEF_NAMBUF;


  res = validate(dp, &fs);  /* Check validity of the object */
  if (res == FR_OK) {
    if (!fno) {
      res = dir_sdi(dp, 0);     /* Rewind the directory object */
    } else {
      INIT_NAMBUF(*dp);
      res = dir_read(dp, 0);      /* Read an item */
      if (res == FR_NO_FILE) res = FR_OK; /* Ignore end of directory */
      if (res == FR_OK) {       /* A valid entry is found */
        get_fileinfo(dp, fno);    /* Get the object information */
        res = dir_next(dp, 0);    /* Increment index for next */
        if (res == FR_NO_FILE) res = FR_OK; /* Ignore end of directory now */
      }
      FREE_NAMBUF();
    }
  }
  LEAVE_FF(fs, res);
}



#if _USE_FIND
/*-----------------------------------------------------------------------*/
/* Find Next File                                                        */
/*-----------------------------------------------------------------------*/

FRESULT f_findnext (
  DIR* dp,    /* Pointer to the open directory object */
  FILINFO* fno  /* Pointer to the file information structure */
)
{
  FRESULT res;


  for (;;) {
    res = f_readdir(dp, fno);   /* Get a directory item */
    if (res != FR_OK || !fno || !fno->fname[0]) break;  /* Terminate if any error or end of directory */
    if (pattern_matching(dp->pat, fno->fname, 0, 0)) break;   /* Test for the file name */
#if _USE_LFN != 0 && _USE_FIND == 2
    if (pattern_matching(dp->pat, fno->altname, 0, 0)) break; /* Test for alternative name if exist */
#endif
  }
  return res;
}



/*-----------------------------------------------------------------------*/
/* Find First File                                                       */
/*-----------------------------------------------------------------------*/

FRESULT f_findfirst (
  DIR* dp,        /* Pointer to the blank directory object */
  FILINFO* fno,     /* Pointer to the file information structure */
  const TCHAR* path,    /* Pointer to the directory to open */
  const TCHAR* pattern  /* Pointer to the matching pattern */
)
{
  FRESULT res;


  dp->pat = pattern;    /* Save pointer to pattern string */
  res = f_opendir(dp, path);    /* Open the target directory */
  if (res == FR_OK) {
    res = f_findnext(dp, fno);  /* Find the first item */
  }
  return res;
}

#endif  /* _USE_FIND */



#if _FS_MINIMIZE == 0
/*-----------------------------------------------------------------------*/
/* Get File Status                                                       */
/*-----------------------------------------------------------------------*/

FRESULT f_stat (
  const TCHAR* path,  /* Pointer to the file path */
  FILINFO* fno    /* Pointer to file information to return */
)
{
  FRESULT res;
  DIR dj;
  DEF_NAMBUF;


  /* Get logical drive number */
  res = find_volume(&path, &dj.obj.fs, 0);
  if (res == FR_OK) {
    INIT_NAMBUF(dj);
    res = follow_path(&dj, path); /* Follow the file path */
    if (res == FR_OK) {       /* Follow completed */
      if (dj.fn[NSFLAG] & NS_NONAME) {  /* It is origin directory */
        res = FR_INVALID_NAME;
      } else {              /* Found an object */
        if (fno) get_fileinfo(&dj, fno);
      }
    }
    FREE_NAMBUF();
  }

  LEAVE_FF(dj.obj.fs, res);
}



#if !_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Get Number of Free Clusters                                           */
/*-----------------------------------------------------------------------*/

FRESULT f_getfree (
  const TCHAR* path,  /* Path name of the logical drive number */
  DWORD* nclst,   /* Pointer to a variable to return number of free clusters */
  FATFS** fatfs   /* Pointer to return pointer to corresponding file system object */
)
{
  FRESULT res;
  FATFS *fs;
  DWORD nfree, clst, sect, stat;
  UINT i;
  BYTE *p;
  _FDID obj;


  /* Get logical drive number */
  res = find_volume(&path, &fs, 0);
  if (res == FR_OK) {
    *fatfs = fs;        /* Return ptr to the fs object */
    /* If free_clst is valid, return it without full cluster scan */
    if (fs->free_clst <= fs->n_fatent - 2) {
      *nclst = fs->free_clst;
    } else {
      /* Get number of free clusters */
      nfree = 0;
      if (fs->fs_type == FS_FAT12) {  /* FAT12: Sector unalighed FAT entries */
        clst = 2; obj.fs = fs;
        do {
          stat = get_fat(&obj, clst);
          if (stat == 0xFFFFFFFF) { res = FR_DISK_ERR; break; }
          if (stat == 1) { res = FR_INT_ERR; break; }
          if (stat == 0) nfree++;
        } while (++clst < fs->n_fatent);
      } else {
#if _FS_EXFAT
        if (fs->fs_type == FS_EXFAT) {  /* exFAT: Scan bitmap table */
          BYTE bm;
          UINT b;

          clst = fs->n_fatent - 2;
          sect = fs->database;
          i = 0;
          do {
            if (i == 0 && (res = move_window(fs, sect++)) != FR_OK) break;
            for (b = 8, bm = fs->win[i]; b && clst; b--, clst--) {
              if (!(bm & 1)) nfree++;
              bm >>= 1;
            }
            i = (i + 1) & (SS(fs) - 1);
          } while (clst);
        } else
#endif
        { /* FAT16/32: Sector alighed FAT entries */
          clst = fs->n_fatent; sect = fs->fatbase;
          i = 0; p = 0;
          do {
            if (i == 0) {
              res = move_window(fs, sect++);
              if (res != FR_OK) break;
              p = fs->win;
              i = SS(fs);
            }
            if (fs->fs_type == FS_FAT16) {
              if (ld_word(p) == 0) nfree++;
              p += 2; i -= 2;
            } else {
              if ((ld_dword(p) & 0x0FFFFFFF) == 0) nfree++;
              p += 4; i -= 4;
            }
          } while (--clst);
        }
      }
      *nclst = nfree;     /* Return the free clusters */
      fs->free_clst = nfree;  /* Now free_clst is valid */
      fs->fsi_flag |= 1;    /* FSInfo is to be updated */
    }
  }

  LEAVE_FF(fs, res);
}




/*-----------------------------------------------------------------------*/
/* Truncate File                                                         */
/*-----------------------------------------------------------------------*/

FRESULT f_truncate (
  FIL* fp   /* Pointer to the file object */
)
{
  FRESULT res;
  FATFS *fs;
  DWORD ncl;


  res = validate(fp, &fs);  /* Check validity of the object */
  if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) LEAVE_FF(fs, res); /* Check validity */
  if (!(fp->flag & FA_WRITE)) LEAVE_FF(fs, FR_DENIED);  /* Check access mode */

  if (fp->obj.objsize > fp->fptr) {
    if (fp->fptr == 0) {  /* When set file size to zero, remove entire cluster chain */
      res = remove_chain(&fp->obj, fp->obj.sclust, 0);
      fp->obj.sclust = 0;
    } else {        /* When truncate a part of the file, remove remaining clusters */
      ncl = get_fat(&fp->obj, fp->clust);
      res = FR_OK;
      if (ncl == 0xFFFFFFFF) res = FR_DISK_ERR;
      if (ncl == 1) res = FR_INT_ERR;
      if (res == FR_OK && ncl < fs->n_fatent) {
        res = remove_chain(&fp->obj, ncl, fp->clust);
      }
    }
    fp->obj.objsize = fp->fptr; /* Set file size to current R/W point */
    fp->flag |= _FA_MODIFIED;
#if !_FS_TINY
    if (res == FR_OK && (fp->flag & _FA_DIRTY)) {
      if (disk_write(fs->drv, fp->buf, fp->sect, 1) != RES_OK) {
        res = FR_DISK_ERR;
      } else {
        fp->flag &= ~_FA_DIRTY;
      }
    }
#endif
    if (res != FR_OK) ABORT(fs, res);
  }

  LEAVE_FF(fs, res);
}




/*-----------------------------------------------------------------------*/
/* Delete a File/Directory                                               */
/*-----------------------------------------------------------------------*/

FRESULT f_unlink (
  const TCHAR* path   /* Pointer to the file or directory path */
)
{
  FRESULT res;
  DIR dj, sdj;
  DWORD dclst = 0;
  FATFS *fs;
#if _FS_EXFAT
  _FDID obj;
#endif
  DEF_NAMBUF;


  /* Get logical drive number */
  res = find_volume(&path, &fs, FA_WRITE);
  dj.obj.fs = fs;
  if (res == FR_OK) {
    INIT_NAMBUF(dj);
    res = follow_path(&dj, path);   /* Follow the file path */
    if (_FS_RPATH && res == FR_OK && (dj.fn[NSFLAG] & NS_DOT)) {
      res = FR_INVALID_NAME;      /* Cannot remove dot entry */
    }
#if _FS_LOCK != 0
    if (res == FR_OK) res = chk_lock(&dj, 2); /* Check if it is an open object */
#endif
    if (res == FR_OK) {         /* The object is accessible */
      if (dj.fn[NSFLAG] & NS_NONAME) {
        res = FR_INVALID_NAME;    /* Cannot remove the origin directory */
      } else {
        if (dj.obj.attr & AM_RDO) {
          res = FR_DENIED;    /* Cannot remove R/O object */
        }
      }
      if (res == FR_OK) {
#if _FS_EXFAT
        obj.fs = fs;
        if (fs->fs_type == FS_EXFAT) {
          obj.sclust = dclst = ld_dword(fs->dirbuf + XDIR_FstClus);
          obj.objsize = ld_qword(fs->dirbuf + XDIR_FileSize);
          obj.stat = fs->dirbuf[XDIR_GenFlags] & 2;
        } else
#endif
        {
          dclst = ld_clust(fs, dj.dir);
        }
        if (dj.obj.attr & AM_DIR) {     /* Is it a sub-directory ? */
#if _FS_RPATH != 0
          if (dclst == fs->cdir) {        /* Is it the current directory? */
            res = FR_DENIED;
          } else
#endif
          {
            sdj.obj.fs = fs;            /* Open the sub-directory */
            sdj.obj.sclust = dclst;
#if _FS_EXFAT
            if (fs->fs_type == FS_EXFAT) {
              sdj.obj.objsize = obj.objsize;
              sdj.obj.stat = obj.stat;
            }
#endif
            res = dir_sdi(&sdj, 0);
            if (res == FR_OK) {
              res = dir_read(&sdj, 0);      /* Read an item */
              if (res == FR_OK) res = FR_DENIED;  /* Not empty? */
              if (res == FR_NO_FILE) res = FR_OK; /* Empty? */
            }
          }
        }
      }
      if (res == FR_OK) {
        res = dir_remove(&dj);      /* Remove the directory entry */
        if (res == FR_OK && dclst) {  /* Remove the cluster chain if exist */
#if _FS_EXFAT
          res = remove_chain(&obj, dclst, 0);
#else
          res = remove_chain(&dj.obj, dclst, 0);
#endif
        }
        if (res == FR_OK) res = sync_fs(fs);
      }
    }
    FREE_NAMBUF();
  }

  LEAVE_FF(fs, res);
}




/*-----------------------------------------------------------------------*/
/* Create a Directory                                                    */
/*-----------------------------------------------------------------------*/

FRESULT f_mkdir (
  const TCHAR* path   /* Pointer to the directory path */
)
{
  FRESULT res;
  DIR dj;
  FATFS *fs;
  BYTE *dir;
  UINT n;
  DWORD dsc, dcl, pcl, tm;
  DEF_NAMBUF;


  /* Get logical drive number */
  res = find_volume(&path, &fs, FA_WRITE);
  dj.obj.fs = fs;
  if (res == FR_OK) {
    INIT_NAMBUF(dj);
    res = follow_path(&dj, path);     /* Follow the file path */
    if (res == FR_OK) res = FR_EXIST;   /* Any object with same name is already existing */
    if (_FS_RPATH && res == FR_NO_FILE && (dj.fn[NSFLAG] & NS_DOT)) {
      res = FR_INVALID_NAME;
    }
    if (res == FR_NO_FILE) {        /* Can create a new directory */
      dcl = create_chain(&dj.obj, 0);   /* Allocate a cluster for the new directory table */
      dj.obj.objsize = (DWORD)fs->csize * SS(fs);
      res = FR_OK;
      if (dcl == 0) res = FR_DENIED;    /* No space to allocate a new cluster */
      if (dcl == 1) res = FR_INT_ERR;
      if (dcl == 0xFFFFFFFF) res = FR_DISK_ERR;
      if (res == FR_OK) res = sync_window(fs);  /* Flush FAT */
      tm = GET_FATTIME();
      if (res == FR_OK) {         /* Initialize the new directory table */
        dsc = clust2sect(fs, dcl);
        dir = fs->win;
        mem_set(dir, 0, SS(fs));
        if (!_FS_EXFAT || fs->fs_type != FS_EXFAT) {
          mem_set(dir + DIR_Name, ' ', 11); /* Create "." entry */
          dir[DIR_Name] = '.';
          dir[DIR_Attr] = AM_DIR;
          st_dword(dir + DIR_WrtTime, tm);
          st_clust(fs, dir, dcl);
          mem_cpy(dir + SZDIRE, dir, SZDIRE);   /* Create ".." entry */
          dir[SZDIRE + 1] = '.'; pcl = dj.obj.sclust;
          if (fs->fs_type == FS_FAT32 && pcl == fs->dirbase)
            pcl = 0;
          st_clust(fs, dir + SZDIRE, pcl);
        }
        for (n = fs->csize; n; n--) { /* Write dot entries and clear following sectors */
          fs->winsect = dsc++;
          fs->wflag = 1;
          res = sync_window(fs);
          if (res != FR_OK) break;
          mem_set(dir, 0, SS(fs));
        }
      }
      if (res == FR_OK) res = dir_register(&dj);  /* Register the object to the directoy */
      if (res == FR_OK) {
#if _FS_EXFAT
        if (fs->fs_type == FS_EXFAT) {
          st_dword(fs->dirbuf + XDIR_ModTime, tm);
          st_dword(fs->dirbuf + XDIR_FstClus, dcl);
          st_dword(fs->dirbuf + XDIR_FileSize, (DWORD)dj.obj.objsize);
          st_dword(fs->dirbuf + XDIR_ValidFileSize, (DWORD)dj.obj.objsize);
          fs->dirbuf[XDIR_GenFlags] = 3;
          fs->dirbuf[XDIR_Attr] = AM_DIR;
          res = store_xdir(&dj);
        } else
#endif
        {
          dir = dj.dir;
          st_dword(dir + DIR_WrtTime, tm);  /* Created time */
          st_clust(fs, dir, dcl);       /* Table start cluster */
          dir[DIR_Attr] = AM_DIR;       /* Attribute */
          fs->wflag = 1;
        }
        res = sync_fs(fs);
      } else {
        remove_chain(&dj.obj, dcl, 0);    /* Could not register, remove cluster chain */
      }
    }
    FREE_NAMBUF();
  }

  LEAVE_FF(fs, res);
}




/*-----------------------------------------------------------------------*/
/* Rename a File/Directory                                               */
/*-----------------------------------------------------------------------*/

FRESULT f_rename (
  const TCHAR* path_old,  /* Pointer to the object name to be renamed */
  const TCHAR* path_new /* Pointer to the new name */
)
{
  FRESULT res;
  DIR djo, djn;
  FATFS *fs;
  BYTE buf[_FS_EXFAT ? SZDIRE * 2 : 24], *dir;
  DWORD dw;
  DEF_NAMBUF;


  get_ldnumber(&path_new);            /* Ignore drive number of new name */
  res = find_volume(&path_old, &fs, FA_WRITE);  /* Get logical drive number of the old object */
  if (res == FR_OK) {
    djo.obj.fs = fs;
    INIT_NAMBUF(djo);
    res = follow_path(&djo, path_old);    /* Check old object */
    if (res == FR_OK && (djo.fn[NSFLAG] & (NS_DOT | NS_NONAME))) res = FR_INVALID_NAME; /* Check validity of name */
#if _FS_LOCK != 0
    if (res == FR_OK) res = chk_lock(&djo, 2);
#endif
    if (res == FR_OK) {           /* Object to be renamed is found */
#if _FS_EXFAT
      if (fs->fs_type == FS_EXFAT) {  /* At exFAT */
        BYTE nf, nn;
        WORD nh;

        mem_cpy(buf, fs->dirbuf, SZDIRE * 2); /* Save 85+C0 entry of old object */
        mem_cpy(&djn, &djo, sizeof djo);
        res = follow_path(&djn, path_new);  /* Make sure if new object name is not in use */
        if (res == FR_OK) res = FR_EXIST; /* Is new name already in use? */
        if (res == FR_NO_FILE) {      /* It is a valid path and no name collision */
          res = dir_register(&djn);   /* Register the new entry */
          if (res == FR_OK) {
            nf = fs->dirbuf[XDIR_NumSec]; nn = fs->dirbuf[XDIR_NumName];
            nh = ld_word(fs->dirbuf + XDIR_NameHash);
            mem_cpy(fs->dirbuf, buf, SZDIRE * 2);
            fs->dirbuf[XDIR_NumSec] = nf; fs->dirbuf[XDIR_NumName] = nn;
            st_word(fs->dirbuf + XDIR_NameHash, nh);
/* Start of critical section where any interruption can cause a cross-link */
            res = store_xdir(&djn);
          }
        }
      } else
#endif
      { /* At FAT12/FAT16/FAT32 */
        mem_cpy(buf, djo.dir + DIR_Attr, 21); /* Save information about the object except name */
        mem_cpy(&djn, &djo, sizeof (DIR));    /* Duplicate the directory object */
        res = follow_path(&djn, path_new);    /* Make sure if new object name is not in use */
        if (res == FR_OK) res = FR_EXIST;   /* Is new name already in use? */
        if (res == FR_NO_FILE) {        /* It is a valid path and no name collision */
          res = dir_register(&djn);     /* Register the new entry */
          if (res == FR_OK) {
            dir = djn.dir;          /* Copy information about object except name */
            mem_cpy(dir + 13, buf + 2, 19);
            dir[DIR_Attr] = buf[0] | AM_ARC;
            fs->wflag = 1;
            if ((dir[DIR_Attr] & AM_DIR) && djo.obj.sclust != djn.obj.sclust) { /* Update .. entry in the sub-directory if needed */
              dw = clust2sect(fs, ld_clust(fs, dir));
              if (!dw) {
                res = FR_INT_ERR;
              } else {
/* Start of critical section where any interruption can cause a cross-link */
                res = move_window(fs, dw);
                dir = fs->win + SZDIRE * 1; /* Ptr to .. entry */
                if (res == FR_OK && dir[1] == '.') {
                  st_clust(fs, dir, djn.obj.sclust);
                  fs->wflag = 1;
                }
              }
            }
          }
        }
      }
      if (res == FR_OK) {
        res = dir_remove(&djo);   /* Remove old entry */
        if (res == FR_OK) {
          res = sync_fs(fs);
        }
      }
/* End of critical section */
    }
    FREE_NAMBUF();
  }

  LEAVE_FF(fs, res);
}



#endif /* !_FS_READONLY */
#endif /* _FS_MINIMIZE == 0 */
#endif /* _FS_MINIMIZE <= 1 */
#endif /* _FS_MINIMIZE <= 2 */



#if _USE_CHMOD && !_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Change Attribute                                                      */
/*-----------------------------------------------------------------------*/

FRESULT f_chmod (
  const TCHAR* path,  /* Pointer to the file path */
  BYTE attr,      /* Attribute bits */
  BYTE mask     /* Attribute mask to change */
)
{
  FRESULT res;
  DIR dj;
  FATFS *fs;
  DEF_NAMBUF;


  res = find_volume(&path, &fs, FA_WRITE);  /* Get logical drive number */
  dj.obj.fs = fs;
  if (res == FR_OK) {
    INIT_NAMBUF(dj);
    res = follow_path(&dj, path); /* Follow the file path */
    if (res == FR_OK && (dj.fn[NSFLAG] & (NS_DOT | NS_NONAME))) res = FR_INVALID_NAME;  /* Check object validity */
    if (res == FR_OK) {
      mask &= AM_RDO|AM_HID|AM_SYS|AM_ARC;  /* Valid attribute mask */
#if _FS_EXFAT
      if (fs->fs_type == FS_EXFAT) {
        fs->dirbuf[XDIR_Attr] = (attr & mask) | (fs->dirbuf[XDIR_Attr] & (BYTE)~mask);  /* Apply attribute change */
        res = store_xdir(&dj);
      } else
#endif
      {
        dj.dir[DIR_Attr] = (attr & mask) | (dj.dir[DIR_Attr] & (BYTE)~mask);  /* Apply attribute change */
        fs->wflag = 1;
      }
      res = sync_fs(fs);
    }
    FREE_NAMBUF();
  }

  LEAVE_FF(fs, res);
}




/*-----------------------------------------------------------------------*/
/* Change Timestamp                                                      */
/*-----------------------------------------------------------------------*/

FRESULT f_utime (
  const TCHAR* path,  /* Pointer to the file/directory name */
  const FILINFO* fno  /* Pointer to the time stamp to be set */
)
{
  FRESULT res;
  DIR dj;
  FATFS *fs;
  DEF_NAMBUF;


  res = find_volume(&path, &fs, FA_WRITE);  /* Get logical drive number */
  dj.obj.fs = fs;
  if (res == FR_OK) {
    INIT_NAMBUF(dj);
    res = follow_path(&dj, path); /* Follow the file path */
    if (res == FR_OK && (dj.fn[NSFLAG] & (NS_DOT | NS_NONAME))) res = FR_INVALID_NAME;  /* Check object validity */
    if (res == FR_OK) {
#if _FS_EXFAT
      if (fs->fs_type == FS_EXFAT) {
        st_word(fs->dirbuf + XDIR_ModTime, fno->ftime);
        st_word(fs->dirbuf + XDIR_ModTime + 2, fno->fdate);
        res = store_xdir(&dj);
      } else
#endif
      {
        st_word(dj.dir + DIR_WrtTime, fno->ftime);
        st_word(dj.dir + DIR_WrtDate, fno->fdate);
        fs->wflag = 1;
      }
      if (res == FR_OK) res = sync_fs(fs);
    }
    FREE_NAMBUF();
  }

  LEAVE_FF(fs, res);
}

#endif  /* _USE_CHMOD && !_FS_READONLY */



#if _USE_LABEL
/*-----------------------------------------------------------------------*/
/* Get Volume Label                                                      */
/*-----------------------------------------------------------------------*/

FRESULT f_getlabel (
  const TCHAR* path,  /* Path name of the logical drive number */
  TCHAR* label,   /* Pointer to a buffer to return the volume label */
  DWORD* vsn      /* Pointer to a variable to return the volume serial number */
)
{
  FRESULT res;
  DIR dj;
  FATFS *fs;
  UINT si, di;
#if _LFN_UNICODE || _FS_EXFAT
  WCHAR w;
#endif

  /* Get logical drive number */
  res = find_volume(&path, &fs, 0);

  /* Get volume label */
  if (res == FR_OK && label) {
    dj.obj.fs = fs; dj.obj.sclust = 0;  /* Open root directory */
    res = dir_sdi(&dj, 0);
    if (res == FR_OK) {
      res = dir_read(&dj, 1);     /* Find a volume label entry */
      if (res == FR_OK) {
#if _FS_EXFAT
        if (fs->fs_type == FS_EXFAT) {
          for (si = di = 0; si < dj.dir[XDIR_NumLabel]; si++) { /* Extract volume label from 83 entry */
            w = ld_word(dj.dir + XDIR_Label + si * 2);
#if _LFN_UNICODE
            label[di++] = w;
#else
            w = ff_convert(w, 0); /* Unicode -> OEM */
            if (w == 0) w = '?';  /* Replace wrong character */
            if (_DF1S && w >= 0x100) label[di++] = (char)(w >> 8);
            label[di++] = (char)w;
#endif
          }
          label[di] = 0;
        } else
#endif
        {
          si = di = 0;    /* Extract volume label from AM_VOL entry with code comversion */
          do {
#if _LFN_UNICODE
            w = (si < 11) ? dj.dir[si++] : ' ';
            if (IsDBCS1(w) && si < 11 && IsDBCS2(dj.dir[si])) {
              w = w << 8 | dj.dir[si++];
            }
            label[di++] = ff_convert(w, 1); /* OEM -> Unicode */
#else
            label[di++] = dj.dir[si++];
#endif
          } while (di < 11);
          do {        /* Truncate trailing spaces */
            label[di] = 0;
            if (di == 0) break;
          } while (label[--di] == ' ');
        }
      }
    }
    if (res == FR_NO_FILE) {  /* No label entry and return nul string */
      label[0] = 0;
      res = FR_OK;
    }
  }

  /* Get volume serial number */
  if (res == FR_OK && vsn) {
    res = move_window(fs, fs->volbase);
    if (res == FR_OK) {
      switch (fs->fs_type) {
      case FS_EXFAT: di = BPB_VolIDEx; break;
      case FS_FAT32: di = BS_VolID32; break;
      default:       di = BS_VolID;
      }
      *vsn = ld_dword(&fs->win[di]);
    }
  }

  LEAVE_FF(fs, res);
}



#if !_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Set Volume Label                                                      */
/*-----------------------------------------------------------------------*/

FRESULT f_setlabel (
  const TCHAR* label  /* Pointer to the volume label to set */
)
{
  FRESULT res;
  DIR dj;
  FATFS *fs;
  BYTE dirvn[22];
  UINT i, j, slen;
  WCHAR w;
  static const char badchr[] = "\"*+,.:;<=>\?[]|\x7F";


  /* Get logical drive number */
  res = find_volume(&label, &fs, FA_WRITE);
  if (res != FR_OK) LEAVE_FF(fs, res);
  dj.obj.fs = fs;

  /* Get length of given volume label */
  for (slen = 0; (UINT)label[slen] >= ' '; slen++) ;  /* Get name length */

#if _FS_EXFAT
  if (fs->fs_type == FS_EXFAT) {  /* At the exFAT */
    for (i = j = 0; i < slen; ) { /* Create volume label in directory form */
      w = label[i++];
#if !_LFN_UNICODE
      if (IsDBCS1(w)) {
        w = (i < slen && IsDBCS2(label[i])) ? w << 8 | (BYTE)label[i++] : 0;
      }
      w = ff_convert(w, 1);
#endif
      if (w == 0 || chk_chr(badchr, w) || j == 22) {  /* Check validity check validity of the volume label */
        LEAVE_FF(fs, FR_INVALID_NAME);
      }
      st_word(dirvn + j, w); j += 2;
    }
    slen = j;
  } else
#endif
  { /* At the FAT12/16/32 */
    for ( ; slen && label[slen - 1] == ' '; slen--) ; /* Remove trailing spaces */
    if (slen) {   /* Is there a volume label to be set? */
      dirvn[0] = 0; i = j = 0;  /* Create volume label in directory form */
      do {
#if _LFN_UNICODE
        w = ff_convert(ff_wtoupper(label[i++]), 0);
#else
        w = (BYTE)label[i++];
        if (IsDBCS1(w)) {
          w = (WCHAR)((j < 10 && i < slen && IsDBCS2(label[i])) ? w << 8 | (BYTE)label[i++] : 0);
        }
#if _USE_LFN != 0
        w = ff_convert(ff_wtoupper(ff_convert(w, 1)), 0);
#else
        if (IsLower(w)) w -= 0x20;      /* To upper ASCII characters */
#ifdef _EXCVT
        if (w >= 0x80) w = ExCvt[w - 0x80]; /* To upper extended characters (SBCS cfg) */
#else
        if (!_DF1S && w >= 0x80) w = 0;   /* Reject extended characters (ASCII cfg) */
#endif
#endif
#endif
        if (w == 0 || chk_chr(badchr, w) || j >= (UINT)((w >= 0x100) ? 10 : 11)) {  /* Reject invalid characters for volume label */
          LEAVE_FF(fs, FR_INVALID_NAME);
        }
        if (w >= 0x100) dirvn[j++] = (BYTE)(w >> 8);
        dirvn[j++] = (BYTE)w;
      } while (i < slen);
      while (j < 11) dirvn[j++] = ' ';  /* Fill remaining name field */
      if (dirvn[0] == DDEM) LEAVE_FF(fs, FR_INVALID_NAME);  /* Reject illegal name (heading DDEM) */
    }
  }

  /* Set volume label */
  dj.obj.sclust = 0;    /* Open root directory */
  res = dir_sdi(&dj, 0);
  if (res == FR_OK) {
    res = dir_read(&dj, 1); /* Get volume label entry */
    if (res == FR_OK) {
      if (_FS_EXFAT && fs->fs_type == FS_EXFAT) {
        dj.dir[XDIR_NumLabel] = (BYTE)(slen / 2); /* Change the volume label */
        mem_cpy(dj.dir + XDIR_Label, dirvn, slen);
      } else {
        if (slen) {
          mem_cpy(dj.dir, dirvn, 11); /* Change the volume label */
        } else {
          dj.dir[DIR_Name] = DDEM;  /* Remove the volume label */
        }
      }
      fs->wflag = 1;
      res = sync_fs(fs);
    } else {      /* No volume label entry is found or error */
      if (res == FR_NO_FILE) {
        res = FR_OK;
        if (slen) { /* Create a volume label entry */
          res = dir_alloc(&dj, 1);  /* Allocate an entry */
          if (res == FR_OK) {
            mem_set(dj.dir, 0, SZDIRE); /* Clear the entry */
            if (_FS_EXFAT && fs->fs_type == FS_EXFAT) {
              dj.dir[XDIR_Type] = 0x83;   /* Create 83 entry */
              dj.dir[XDIR_NumLabel] = (BYTE)(slen / 2);
              mem_cpy(dj.dir + XDIR_Label, dirvn, slen);
            } else {
              dj.dir[DIR_Attr] = AM_VOL;    /* Create volume label entry */
              mem_cpy(dj.dir, dirvn, 11);
            }
            fs->wflag = 1;
            res = sync_fs(fs);
          }
        }
      }
    }
  }

  LEAVE_FF(fs, res);
}

#endif /* !_FS_READONLY */
#endif /* _USE_LABEL */



#if _USE_EXPAND && !_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Allocate a Contiguous Blocks to the File                              */
/*-----------------------------------------------------------------------*/

FRESULT f_expand (
  FIL* fp,    /* Pointer to the file object */
  FSIZE_t fsz,  /* File size to be expanded to */
  BYTE opt    /* Operation mode 0:Find and prepare or 1:Find and allocate */
)
{
  FRESULT res;
  FATFS *fs;
  DWORD val, clst, csz, stcl, scl, ncl, tcl;


  res = validate(fp, &fs);    /* Check validity of the object */
  if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) LEAVE_FF(fs, res); /* Check validity */
  if (fsz == 0 || fp->obj.objsize != 0 || !(fp->flag & FA_WRITE)) LEAVE_FF(fs, FR_DENIED);
#if _FS_EXFAT
  if (fs->fs_type != FS_EXFAT && fsz >= 0x100000000) LEAVE_FF(fs, FR_DENIED); /* Check if in size limit */
#endif
  csz = (DWORD)fs->csize * SS(fs);  /* Cluster size */
  tcl = (DWORD)(fsz / csz) + ((fsz & (csz - 1)) ? 1 : 0); /* Number of clusters required */
  stcl = fs->last_clst;
  if (stcl < 2 || stcl >= fs->n_fatent) stcl = 2;

#if _FS_EXFAT
  if (fs->fs_type == FS_EXFAT) {
    scl = find_bitmap(fs, stcl, tcl);     /* Find a contiguous cluster block */
    if (scl == 0) res = FR_DENIED;        /* No contiguous cluster block was found */
    if (scl == 1) res = FR_INT_ERR;
    if (scl == 0xFFFFFFFF) res = FR_DISK_ERR;
    if (res == FR_OK) {
      if (opt) {
        res = change_bitmap(fs, scl, tcl, 1); /* Mark the cluster block 'in use' */
        fs->last_clst = scl + tcl - 1;
      } else {
        fs->last_clst = scl - 1;        /* Set suggested cluster to start next */
      }
    }
  } else
#endif
  {
    scl = clst = stcl; ncl = 0;
    for (;;) {  /* Find a contiguous cluster block */
      val = get_fat(&fp->obj, clst);
      if (++clst >= fs->n_fatent) clst = 2;
      if (val == 1) { res = FR_INT_ERR; break; }
      if (val == 0xFFFFFFFF) { res = FR_DISK_ERR; break; }
      if (val == 0) { /* Is it a free cluster? */
        if (++ncl == tcl) break;  /* Break if a contiguous cluster block was found */
      } else {
        scl = clst; ncl = 0;    /* Not a free cluster */
      }
      if (clst == stcl) { res = FR_DENIED; break; } /* All cluster scanned? */
    }
    if (res == FR_OK) {
      if (opt) {
        for (clst = scl; tcl; clst++, tcl--) {  /* Create a cluster chain on the FAT */
          val = (tcl == 1) ? 0xFFFFFFFF : clst + 1;
          res = put_fat(fs, clst, val);
          if (res != FR_OK) break;
          fs->last_clst = clst;
        }
      } else {
        fs->last_clst = scl - 1;        /* Set suggested cluster to start next */
      }
    }
  }

  if (opt && res == FR_OK) {
    fp->obj.sclust = scl;   /* Update allocation information */
    fp->obj.objsize = fsz;
    if (_FS_EXFAT) fp->obj.stat = 2;
    fp->flag |= _FA_MODIFIED;
  }

  LEAVE_FF(fs, res);
}

#endif /* _USE_EXPAND && !_FS_READONLY */



/*-----------------------------------------------------------------------*/
/* Forward data to the stream directly                                   */
/*-----------------------------------------------------------------------*/
#if _USE_FORWARD

FRESULT f_forward (
  FIL* fp,            /* Pointer to the file object */
  UINT (*func)(const BYTE*,UINT), /* Pointer to the streaming function */
  UINT btf,           /* Number of bytes to forward */
  UINT* bf            /* Pointer to number of bytes forwarded */
)
{
  FRESULT res;
  FATFS *fs;
  DWORD clst, sect;
  FSIZE_t remain;
  UINT rcnt, csect;
  const BYTE *dbuf;


  *bf = 0;  /* Clear transfer byte counter */
  res = validate(fp, &fs);    /* Check validity of the object */
  if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) LEAVE_FF(fs, res); /* Check validity */
  if (!(fp->flag & FA_READ)) LEAVE_FF(fs, FR_DENIED); /* Check access mode */

  remain = fp->obj.objsize - fp->fptr;
  if (btf > remain) btf = (UINT)remain;     /* Truncate btf by remaining bytes */

  for ( ;  btf && (*func)(0, 0);          /* Repeat until all data transferred or stream goes busy */
    fp->fptr += rcnt, *bf += rcnt, btf -= rcnt) {
    csect = (UINT)(fp->fptr / SS(fs) & (fs->csize - 1));  /* Sector offset in the cluster */
    if (fp->fptr % SS(fs) == 0) {       /* On the sector boundary? */
      if (csect == 0) {           /* On the cluster boundary? */
        clst = (fp->fptr == 0) ?      /* On the top of the file? */
          fp->obj.sclust : get_fat(&fp->obj, fp->clust);
        if (clst <= 1) ABORT(fs, FR_INT_ERR);
        if (clst == 0xFFFFFFFF) ABORT(fs, FR_DISK_ERR);
        fp->clust = clst;         /* Update current cluster */
      }
    }
    sect = clust2sect(fs, fp->clust);     /* Get current data sector */
    if (!sect) ABORT(fs, FR_INT_ERR);
    sect += csect;
#if _FS_TINY
    if (move_window(fs, sect) != FR_OK) ABORT(fs, FR_DISK_ERR); /* Move sector window to the file data */
    dbuf = fs->win;
#else
    if (fp->sect != sect) {   /* Fill sector cache with file data */
#if !_FS_READONLY
      if (fp->flag & _FA_DIRTY) {   /* Write-back dirty sector cache */
        if (disk_write(fs->drv, fp->buf, fp->sect, 1) != RES_OK) ABORT(fs, FR_DISK_ERR);
        fp->flag &= ~_FA_DIRTY;
      }
#endif
      if (disk_read(fs->drv, fp->buf, sect, 1) != RES_OK) ABORT(fs, FR_DISK_ERR);
    }
    dbuf = fp->buf;
#endif
    fp->sect = sect;
    rcnt = SS(fs) - (UINT)fp->fptr % SS(fs);  /* Number of bytes left in the sector */
    if (rcnt > btf) rcnt = btf;         /* Clip it by btr if needed */
    rcnt = (*func)(dbuf + ((UINT)fp->fptr % SS(fs)), rcnt); /* Forward the file data */
    if (!rcnt) ABORT(fs, FR_INT_ERR);
  }

  LEAVE_FF(fs, FR_OK);
}
#endif /* _USE_FORWARD */



#if _USE_MKFS && !_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Create file system on the logical drive                               */
/*-----------------------------------------------------------------------*/
#define N_ROOTDIR 512   /* Number of root directory entries for FAT12/16 */
#define N_FATS    1   /* Number of FATs (1 or 2) */


FRESULT f_mkfs (
  const TCHAR* path,  /* Logical drive number */
  BYTE sfd,     /* Partitioning rule 0:FDISK, 1:SFD */
  UINT au       /* Size of allocation unit in unit of byte or sector */
)
{
  static const WORD vst[] = { 1024,   512,  256,  128,   64,    32,   16,    8,    4,    2,   0};
  static const WORD cst[] = {32768, 16384, 8192, 4096, 2048, 16384, 8192, 4096, 2048, 1024, 512};
  int vol;
  BYTE fmt, md, sys, *tbl, pdrv, part;
  DWORD n_clst, vs, n, wsect;
  UINT i;
  DWORD b_vol, b_fat, b_dir, b_data;  /* LBA */
  DWORD n_vol, n_rsv, n_fat, n_dir; /* Size */
  FATFS *fs;
  DSTATUS stat;
#if _USE_TRIM
  DWORD eb[2];
#endif


  /* Check mounted drive and clear work area */
  if (sfd > 1) return FR_INVALID_PARAMETER;
  vol = get_ldnumber(&path);        /* Get target volume */
  if (vol < 0) return FR_INVALID_DRIVE;
  fs = FatFs[vol];            /* Check if the volume has work area */
  if (!fs) return FR_NOT_ENABLED;
  fs->fs_type = 0;
  pdrv = LD2PD(vol);  /* Physical drive */
  part = LD2PT(vol);  /* Partition (0:auto detect, 1-4:get from partition table)*/

  /* Get disk statics */
  stat = disk_initialize(pdrv);
  if (stat & STA_NOINIT) return FR_NOT_READY;
  if (stat & STA_PROTECT) return FR_WRITE_PROTECTED;
#if _MAX_SS != _MIN_SS    /* Get disk sector size */
  if (disk_ioctl(pdrv, GET_SECTOR_SIZE, &SS(fs)) != RES_OK || SS(fs) > _MAX_SS || SS(fs) < _MIN_SS) {
    return FR_DISK_ERR;
  }
#endif
  if (_MULTI_PARTITION && part) {
    /* Get partition information from partition table in the MBR */
    if (disk_read(pdrv, fs->win, 0, 1) != RES_OK) return FR_DISK_ERR;
    if (ld_word(fs->win + BS_55AA) != 0xAA55) return FR_MKFS_ABORTED;
    tbl = &fs->win[MBR_Table + (part - 1) * SZ_PTE];
    if (!tbl[4]) return FR_MKFS_ABORTED;  /* No partition? */
    b_vol = ld_dword(tbl + 8);  /* Volume start sector */
    n_vol = ld_dword(tbl + 12); /* Volume size */
  } else {
    /* Create a single-partition in this function */
    if (disk_ioctl(pdrv, GET_SECTOR_COUNT, &n_vol) != RES_OK || n_vol < 128) {
      return FR_DISK_ERR;
    }
    b_vol = (sfd) ? 0 : 63;   /* Volume start sector */
    n_vol -= b_vol;       /* Volume size */
  }

  if (au & (au - 1)) au = 0;
  if (!au) {            /* AU auto selection */
    vs = n_vol / (2000 / (SS(fs) / 512));
    for (i = 0; vs < vst[i]; i++) ;
    au = cst[i];
  }
  if (au >= _MIN_SS) au /= SS(fs);  /* Number of sectors per cluster */
  if (!au) au = 1;
  if (au > 128) au = 128;

  /* Pre-compute number of clusters and FAT sub-type */
  n_clst = n_vol / au;
  fmt = FS_FAT12;
  if (n_clst >= MIN_FAT16) fmt = FS_FAT16;
  if (n_clst >= MIN_FAT32) fmt = FS_FAT32;

  /* Determine offset and size of FAT structure */
  if (fmt == FS_FAT32) {
    n_fat = ((n_clst * 4) + 8 + SS(fs) - 1) / SS(fs);
    n_rsv = 32;
    n_dir = 0;
  } else {
    n_fat = (fmt == FS_FAT12) ? (n_clst * 3 + 1) / 2 + 3 : (n_clst * 2) + 4;
    n_fat = (n_fat + SS(fs) - 1) / SS(fs);
    n_rsv = 1;
    n_dir = (DWORD)N_ROOTDIR * SZDIRE / SS(fs);
  }
  b_fat = b_vol + n_rsv;        /* FAT area start sector */
  b_dir = b_fat + n_fat * N_FATS;   /* Directory area start sector */
  b_data = b_dir + n_dir;       /* Data area start sector */
  if (n_vol < b_data + au - b_vol) return FR_MKFS_ABORTED;  /* Too small volume */

  /* Align data start sector to erase block boundary (for flash memory media) */
  if (disk_ioctl(pdrv, GET_BLOCK_SIZE, &n) != RES_OK || !n || n > 32768) n = 1;
  n = (b_data + n - 1) & ~(n - 1);  /* Next nearest erase block from current data start */
  n = (n - b_data) / N_FATS;
  if (fmt == FS_FAT32) {    /* FAT32: Move FAT offset */
    n_rsv += n;
    b_fat += n;
  } else {          /* FAT12/16: Expand FAT size */
    n_fat += n;
  }

  /* Determine number of clusters and final check of validity of the FAT sub-type */
  n_clst = (n_vol - n_rsv - n_fat * N_FATS - n_dir) / au;
  if (   (fmt == FS_FAT16 && n_clst < MIN_FAT16)
    || (fmt == FS_FAT32 && n_clst < MIN_FAT32)) {
    return FR_MKFS_ABORTED;
  }

  /* Determine system ID in the partition table */
  if (fmt == FS_FAT32) {
    sys = 0x0C;   /* FAT32X */
  } else {
    if (fmt == FS_FAT12 && n_vol < 0x10000) {
      sys = 0x01; /* FAT12(<65536) */
    } else {
      sys = (n_vol < 0x10000) ? 0x04 : 0x06;  /* FAT16(<65536) : FAT12/16(>=65536) */
    }
  }

  if (_MULTI_PARTITION && part) {
    /* Update system ID in the partition table */
    tbl = &fs->win[MBR_Table + (part - 1) * SZ_PTE];
    tbl[4] = sys;
    if (disk_write(pdrv, fs->win, 0, 1) != RES_OK) {  /* Write it to teh MBR */
      return FR_DISK_ERR;
    }
    md = 0xF8;
  } else {
    if (sfd) {  /* No partition table (SFD) */
      md = 0xF0;
    } else {  /* Create partition table (FDISK) */
      mem_set(fs->win, 0, SS(fs));
      tbl = fs->win + MBR_Table;  /* Create partition table for single partition in the drive */
      tbl[1] = 1;           /* Partition start head */
      tbl[2] = 1;           /* Partition start sector */
      tbl[3] = 0;           /* Partition start cylinder */
      tbl[4] = sys;         /* System type */
      tbl[5] = 254;         /* Partition end head */
      n = (b_vol + n_vol) / 63 / 255;
      tbl[6] = (BYTE)(n >> 2 | 63); /* Partition end sector */
      tbl[7] = (BYTE)n;       /* End cylinder */
      st_dword(tbl + 8, 63);      /* Partition start in LBA */
      st_dword(tbl + 12, n_vol);    /* Partition size in LBA */
      st_word(fs->win + BS_55AA, 0xAA55); /* MBR signature */
      if (disk_write(pdrv, fs->win, 0, 1) != RES_OK) {  /* Write it to the MBR */
        return FR_DISK_ERR;
      }
      md = 0xF8;
    }
  }

  /* Create BPB in the VBR */
  tbl = fs->win;              /* Clear sector */
  mem_set(tbl, 0, SS(fs));
  mem_cpy(tbl, "\xEB\xFE\x90" "MSDOS5.0", 11);/* Boot jump code, OEM name */
  i = SS(fs);               /* Sector size */
  st_word(tbl + BPB_BytsPerSec, (WORD)i);
  tbl[BPB_SecPerClus] = (BYTE)au;     /* Sectors per cluster */
  st_word(tbl + BPB_RsvdSecCnt, (WORD)n_rsv); /* Reserved sectors */
  tbl[BPB_NumFATs] = N_FATS;        /* Number of FATs */
  i = (fmt == FS_FAT32) ? 0 : N_ROOTDIR;  /* Number of root directory entries */
  st_word(tbl + BPB_RootEntCnt, (WORD)i);
  if (n_vol < 0x10000) {          /* Number of total sectors */
    st_word(tbl + BPB_TotSec16, (WORD)n_vol);
  } else {
    st_dword(tbl + BPB_TotSec32, n_vol);
  }
  tbl[BPB_Media] = md;          /* Media descriptor */
  st_word(tbl + BPB_SecPerTrk, 63);   /* Number of sectors per track */
  st_word(tbl + BPB_NumHeads, 255);   /* Number of heads */
  st_dword(tbl + BPB_HiddSec, b_vol);   /* Volume offset */
  n = GET_FATTIME();            /* Use current time as VSN */
  if (fmt == FS_FAT32) {
    st_dword(tbl + BS_VolID32, n);    /* VSN */
    st_dword(tbl + BPB_FATSz32, n_fat); /* Number of sectors per FAT */
    st_dword(tbl + BPB_RootClus32, 2);  /* Root directory start cluster (2) */
    st_word(tbl + BPB_FSInfo32, 1);   /* FSINFO record offset (VBR + 1) */
    st_word(tbl + BPB_BkBootSec32, 6);  /* Backup boot record offset (VBR + 6) */
    tbl[BS_DrvNum32] = 0x80;      /* Drive number */
    tbl[BS_BootSig32] = 0x29;     /* Extended boot signature */
    mem_cpy(tbl + BS_VolLab32, "NO NAME    " "FAT32   ", 19); /* Volume label, FAT signature */
  } else {
    st_dword(tbl + BS_VolID, n);    /* VSN */
    st_word(tbl + BPB_FATSz16, (WORD)n_fat);  /* Number of sectors per FAT */
    tbl[BS_DrvNum] = 0x80;        /* Drive number */
    tbl[BS_BootSig] = 0x29;       /* Extended boot signature */
    mem_cpy(tbl + BS_VolLab, "NO NAME    " "FAT     ", 19); /* Volume label, FAT signature */
  }
  st_word(tbl + BS_55AA, 0xAA55);     /* Signature (Offset is fixed here regardless of sector size) */
  if (disk_write(pdrv, tbl, b_vol, 1) != RES_OK) {  /* Write it to the VBR sector */
    return FR_DISK_ERR;
  }
  if (fmt == FS_FAT32) {          /* Write it to the backup VBR if needed (VBR + 6) */
    disk_write(pdrv, tbl, b_vol + 6, 1);
  }

  /* Initialize FAT area */
  wsect = b_fat;
  for (i = 0; i < N_FATS; i++) {    /* Initialize each FAT copy */
    mem_set(tbl, 0, SS(fs));      /* 1st sector of the FAT  */
    n = md;               /* Media descriptor byte */
    if (fmt != FS_FAT32) {
      n |= (fmt == FS_FAT12) ? 0x00FFFF00 : 0xFFFFFF00;
      st_dword(tbl + 0, n);     /* Reserve cluster #0-1 (FAT12/16) */
    } else {
      n |= 0xFFFFFF00;
      st_dword(tbl + 0, n);     /* Reserve cluster #0-1 (FAT32) */
      st_dword(tbl + 4, 0xFFFFFFFF);
      st_dword(tbl + 8, 0x0FFFFFFF);  /* Reserve cluster #2 for root directory */
    }
    if (disk_write(pdrv, tbl, wsect++, 1) != RES_OK) {
      return FR_DISK_ERR;
    }
    mem_set(tbl, 0, SS(fs));      /* Fill following FAT entries with zero */
    for (n = 1; n < n_fat; n++) {   /* This loop may take a time on FAT32 volume due to many single sector writes */
      if (disk_write(pdrv, tbl, wsect++, 1) != RES_OK) {
        return FR_DISK_ERR;
      }
    }
  }

  /* Initialize root directory */
  i = (fmt == FS_FAT32) ? au : (UINT)n_dir;
  do {
    if (disk_write(pdrv, tbl, wsect++, 1) != RES_OK) {
      return FR_DISK_ERR;
    }
  } while (--i);

#if _USE_TRIM /* Erase data area if needed */
  {
    eb[0] = wsect; eb[1] = wsect + (n_clst - ((fmt == FS_FAT32) ? 1 : 0)) * au - 1;
    disk_ioctl(pdrv, CTRL_TRIM, eb);
  }
#endif

  /* Create FSINFO if needed */
  if (fmt == FS_FAT32) {
    st_dword(tbl + FSI_LeadSig, 0x41615252);
    st_dword(tbl + FSI_StrucSig, 0x61417272);
    st_dword(tbl + FSI_Free_Count, n_clst - 1); /* Number of free clusters */
    st_dword(tbl + FSI_Nxt_Free, 2);      /* Last allocated cluster# */
    st_word(tbl + BS_55AA, 0xAA55);
    disk_write(pdrv, tbl, b_vol + 1, 1);  /* Write original (VBR + 1) */
    disk_write(pdrv, tbl, b_vol + 7, 1);  /* Write backup (VBR + 7) */
  }

  return (disk_ioctl(pdrv, CTRL_SYNC, 0) == RES_OK) ? FR_OK : FR_DISK_ERR;
}



#if _MULTI_PARTITION
/*-----------------------------------------------------------------------*/
/* Create partition table on the physical drive                          */
/*-----------------------------------------------------------------------*/

FRESULT f_fdisk (
  BYTE pdrv,      /* Physical drive number */
  const DWORD szt[],  /* Pointer to the size table for each partitions */
  void* work      /* Pointer to the working buffer */
)
{
  UINT i, n, sz_cyl, tot_cyl, b_cyl, e_cyl, p_cyl;
  BYTE s_hd, e_hd, *p, *buf = (BYTE*)work;
  DSTATUS stat;
  DWORD sz_disk, sz_part, s_part;


  stat = disk_initialize(pdrv);
  if (stat & STA_NOINIT) return FR_NOT_READY;
  if (stat & STA_PROTECT) return FR_WRITE_PROTECTED;
  if (disk_ioctl(pdrv, GET_SECTOR_COUNT, &sz_disk)) return FR_DISK_ERR;

  /* Determine CHS in the table regardless of the drive geometry */
  for (n = 16; n < 256 && sz_disk / n / 63 > 1024; n *= 2) ;
  if (n == 256) n--;
  e_hd = n - 1;
  sz_cyl = 63 * n;
  tot_cyl = sz_disk / sz_cyl;

  /* Create partition table */
  mem_set(buf, 0, _MAX_SS);
  p = buf + MBR_Table; b_cyl = 0;
  for (i = 0; i < 4; i++, p += SZ_PTE) {
    p_cyl = (szt[i] <= 100U) ? (DWORD)tot_cyl * szt[i] / 100 : szt[i] / sz_cyl;
    if (!p_cyl) continue;
    s_part = (DWORD)sz_cyl * b_cyl;
    sz_part = (DWORD)sz_cyl * p_cyl;
    if (i == 0) { /* Exclude first track of cylinder 0 */
      s_hd = 1;
      s_part += 63; sz_part -= 63;
    } else {
      s_hd = 0;
    }
    e_cyl = b_cyl + p_cyl - 1;
    if (e_cyl >= tot_cyl) return FR_INVALID_PARAMETER;

    /* Set partition table */
    p[1] = s_hd;            /* Start head */
    p[2] = (BYTE)((b_cyl >> 2) + 1);  /* Start sector */
    p[3] = (BYTE)b_cyl;         /* Start cylinder */
    p[4] = 0x06;            /* System type (temporary setting) */
    p[5] = e_hd;            /* End head */
    p[6] = (BYTE)((e_cyl >> 2) + 63); /* End sector */
    p[7] = (BYTE)e_cyl;         /* End cylinder */
    st_dword(p + 8, s_part);      /* Start sector in LBA */
    st_dword(p + 12, sz_part);      /* Partition size */

    /* Next partition */
    b_cyl += p_cyl;
  }
  st_word(p, 0xAA55);

  /* Write it to the MBR */
  return (disk_write(pdrv, buf, 0, 1) != RES_OK || disk_ioctl(pdrv, CTRL_SYNC, 0) != RES_OK) ? FR_DISK_ERR : FR_OK;
}


#endif /* _MULTI_PARTITION */
#endif /* _USE_MKFS && !_FS_READONLY */




#if _USE_STRFUNC
/*-----------------------------------------------------------------------*/
/* Get a string from the file                                            */
/*-----------------------------------------------------------------------*/

TCHAR* f_gets (
  TCHAR* buff,  /* Pointer to the string buffer to read */
  int len,    /* Size of string buffer (characters) */
  FIL* fp     /* Pointer to the file object */
)
{
  int n = 0;
  TCHAR c, *p = buff;
  BYTE s[2];
  UINT rc;


  while (n < len - 1) { /* Read characters until buffer gets filled */
#if _LFN_UNICODE
#if _STRF_ENCODE == 3   /* Read a character in UTF-8 */
    f_read(fp, s, 1, &rc);
    if (rc != 1) break;
    c = s[0];
    if (c >= 0x80) {
      if (c < 0xC0) continue; /* Skip stray trailer */
      if (c < 0xE0) {     /* Two-byte sequence */
        f_read(fp, s, 1, &rc);
        if (rc != 1) break;
        c = (c & 0x1F) << 6 | (s[0] & 0x3F);
        if (c < 0x80) c = '?';
      } else {
        if (c < 0xF0) {   /* Three-byte sequence */
          f_read(fp, s, 2, &rc);
          if (rc != 2) break;
          c = c << 12 | (s[0] & 0x3F) << 6 | (s[1] & 0x3F);
          if (c < 0x800) c = '?';
        } else {      /* Reject four-byte sequence */
          c = '?';
        }
      }
    }
#elif _STRF_ENCODE == 2   /* Read a character in UTF-16BE */
    f_read(fp, s, 2, &rc);
    if (rc != 2) break;
    c = s[1] + (s[0] << 8);
#elif _STRF_ENCODE == 1   /* Read a character in UTF-16LE */
    f_read(fp, s, 2, &rc);
    if (rc != 2) break;
    c = s[0] + (s[1] << 8);
#else           /* Read a character in ANSI/OEM */
    f_read(fp, s, 1, &rc);
    if (rc != 1) break;
    c = s[0];
    if (IsDBCS1(c)) {
      f_read(fp, s, 1, &rc);
      if (rc != 1) break;
      c = (c << 8) + s[0];
    }
    c = ff_convert(c, 1); /* OEM -> Unicode */
    if (!c) c = '?';
#endif
#else           /* Read a character without conversion */
    f_read(fp, s, 1, &rc);
    if (rc != 1) break;
    c = s[0];
#endif
    if (_USE_STRFUNC == 2 && c == '\r') continue; /* Strip '\r' */
    *p++ = c;
    n++;
    if (c == '\n') break;   /* Break on EOL */
  }
  *p = 0;
  return n ? buff : 0;      /* When no data read (eof or error), return with error. */
}




#if !_FS_READONLY
#include <stdarg.h>
/*-----------------------------------------------------------------------*/
/* Put a character to the file                                           */
/*-----------------------------------------------------------------------*/

typedef struct {
  FIL* fp;
  int idx, nchr;
  BYTE buf[64];
} putbuff;


static
void putc_bfd (
  putbuff* pb,
  TCHAR c
)
{
  UINT bw;
  int i;


  if (_USE_STRFUNC == 2 && c == '\n') {  /* LF -> CRLF conversion */
    putc_bfd(pb, '\r');
  }

  i = pb->idx;  /* Buffer write index (-1:error) */
  if (i < 0) return;

#if _LFN_UNICODE
#if _STRF_ENCODE == 3     /* Write a character in UTF-8 */
  if (c < 0x80) {       /* 7-bit */
    pb->buf[i++] = (BYTE)c;
  } else {
    if (c < 0x800) {    /* 11-bit */
      pb->buf[i++] = (BYTE)(0xC0 | c >> 6);
    } else {        /* 16-bit */
      pb->buf[i++] = (BYTE)(0xE0 | c >> 12);
      pb->buf[i++] = (BYTE)(0x80 | (c >> 6 & 0x3F));
    }
    pb->buf[i++] = (BYTE)(0x80 | (c & 0x3F));
  }
#elif _STRF_ENCODE == 2     /* Write a character in UTF-16BE */
  pb->buf[i++] = (BYTE)(c >> 8);
  pb->buf[i++] = (BYTE)c;
#elif _STRF_ENCODE == 1     /* Write a character in UTF-16LE */
  pb->buf[i++] = (BYTE)c;
  pb->buf[i++] = (BYTE)(c >> 8);
#else             /* Write a character in ANSI/OEM */
  c = ff_convert(c, 0); /* Unicode -> OEM */
  if (!c) c = '?';
  if (c >= 0x100)
    pb->buf[i++] = (BYTE)(c >> 8);
  pb->buf[i++] = (BYTE)c;
#endif
#else             /* Write a character without conversion */
  pb->buf[i++] = (BYTE)c;
#endif

  if (i >= (int)(sizeof pb->buf) - 3) { /* Write buffered characters to the file */
    f_write(pb->fp, pb->buf, (UINT)i, &bw);
    i = (bw == (UINT)i) ? 0 : -1;
  }
  pb->idx = i;
  pb->nchr++;
}



int f_putc (
  TCHAR c,  /* A character to be output */
  FIL* fp   /* Pointer to the file object */
)
{
  putbuff pb;
  UINT nw;


  pb.fp = fp;     /* Initialize output buffer */
  pb.nchr = pb.idx = 0;

  putc_bfd(&pb, c); /* Put a character */

  if (   pb.idx >= 0  /* Flush buffered characters to the file */
    && f_write(pb.fp, pb.buf, (UINT)pb.idx, &nw) == FR_OK
    && (UINT)pb.idx == nw) return pb.nchr;
  return EOF;
}




/*-----------------------------------------------------------------------*/
/* Put a string to the file                                              */
/*-----------------------------------------------------------------------*/

int f_puts (
  const TCHAR* str, /* Pointer to the string to be output */
  FIL* fp       /* Pointer to the file object */
)
{
  putbuff pb;
  UINT nw;


  pb.fp = fp;       /* Initialize output buffer */
  pb.nchr = pb.idx = 0;

  while (*str)      /* Put the string */
    putc_bfd(&pb, *str++);

  if (   pb.idx >= 0    /* Flush buffered characters to the file */
    && f_write(pb.fp, pb.buf, (UINT)pb.idx, &nw) == FR_OK
    && (UINT)pb.idx == nw) return pb.nchr;
  return EOF;
}




/*-----------------------------------------------------------------------*/
/* Put a formatted string to the file                                    */
/*-----------------------------------------------------------------------*/

int f_printf (
  FIL* fp,      /* Pointer to the file object */
  const TCHAR* fmt, /* Pointer to the format string */
  ...         /* Optional arguments... */
)
{
  va_list arp;
  BYTE f, r;
  UINT nw, i, j, w;
  DWORD v;
  TCHAR c, d, str[32], *p;
  putbuff pb;


  pb.fp = fp;       /* Initialize output buffer */
  pb.nchr = pb.idx = 0;

  va_start(arp, fmt);

  for (;;) {
    c = *fmt++;
    if (c == 0) break;      /* End of string */
    if (c != '%') {       /* Non escape character */
      putc_bfd(&pb, c);
      continue;
    }
    w = f = 0;
    c = *fmt++;
    if (c == '0') {       /* Flag: '0' padding */
      f = 1; c = *fmt++;
    } else {
      if (c == '-') {     /* Flag: left justified */
        f = 2; c = *fmt++;
      }
    }
    while (IsDigit(c)) {    /* Precision */
      w = w * 10 + c - '0';
      c = *fmt++;
    }
    if (c == 'l' || c == 'L') { /* Prefix: Size is long int */
      f |= 4; c = *fmt++;
    }
    if (!c) break;
    d = c;
    if (IsLower(d)) d -= 0x20;
    switch (d) {        /* Type is... */
    case 'S' :          /* String */
      p = va_arg(arp, TCHAR*);
      for (j = 0; p[j]; j++) ;
      if (!(f & 2)) {
        while (j++ < w) putc_bfd(&pb, ' ');
      }
      while (*p) putc_bfd(&pb, *p++);
      while (j++ < w) putc_bfd(&pb, ' ');
      continue;
    case 'C' :          /* Character */
      putc_bfd(&pb, (TCHAR)va_arg(arp, int)); continue;
    case 'B' :          /* Binary */
      r = 2; break;
    case 'O' :          /* Octal */
      r = 8; break;
    case 'D' :          /* Signed decimal */
    case 'U' :          /* Unsigned decimal */
      r = 10; break;
    case 'X' :          /* Hexdecimal */
      r = 16; break;
    default:          /* Unknown type (pass-through) */
      putc_bfd(&pb, c); continue;
    }

    /* Get an argument and put it in numeral */
    v = (f & 4) ? (DWORD)va_arg(arp, long) : ((d == 'D') ? (DWORD)(long)va_arg(arp, int) : (DWORD)va_arg(arp, unsigned int));
    if (d == 'D' && (v & 0x80000000)) {
      v = 0 - v;
      f |= 8;
    }
    i = 0;
    do {
      d = (TCHAR)(v % r); v /= r;
      if (d > 9) d += (c == 'x') ? 0x27 : 0x07;
      str[i++] = d + '0';
    } while (v && i < sizeof str / sizeof str[0]);
    if (f & 8) str[i++] = '-';
    j = i; d = (f & 1) ? '0' : ' ';
    while (!(f & 2) && j++ < w) putc_bfd(&pb, d);
    do putc_bfd(&pb, str[--i]); while (i);
    while (j++ < w) putc_bfd(&pb, d);
  }

  va_end(arp);

  if (   pb.idx >= 0    /* Flush buffered characters to the file */
    && f_write(pb.fp, pb.buf, (UINT)pb.idx, &nw) == FR_OK
    && (UINT)pb.idx == nw) return pb.nchr;
  return EOF;
}

#endif /* !_FS_READONLY */
#endif /* _USE_STRFUNC */



/*-------------------------------------------*/
/* Integer type definitions for FatFs module */
/*-------------------------------------------*/

#ifndef _INTEGER
#define _INTEGER

#ifdef _WIN32	/* FatFs development platform */

#include <windows.h>
#include <tchar.h>

#else			/* Embedded platform */

#include "PE_Types.h"

/* These types must be 16-bit, 32-bit or larger integer */
typedef int				INT;
typedef unsigned int	UINT;

/* These types must be 8-bit integer */
typedef char			CHAR;
typedef unsigned char	UCHAR;
//typedef unsigned char	BYTE; /* use uint8_t instead! */

/* These types must be 16-bit integer */
typedef short			SHORT;
typedef unsigned short	USHORT;
//typedef unsigned short	WORD; /* use uint16_t instead! */
typedef unsigned short	WCHAR;

/* These types must be 32-bit integer */
typedef long			LONG;
typedef unsigned long	ULONG;
//typedef unsigned long	DWORD; /* use uint32_t instead! */

#endif

#endif

/*-------------------------------------------*/
/* Integer type definitions for FatFs module */
/*-------------------------------------------*/

#ifndef _FF_INTEGER
#define _FF_INTEGER

#ifdef _WIN32	/* FatFs development platform */

#include <windows.h>
#include <tchar.h>
typedef unsigned __int64 QWORD;


#else			/* Embedded platform */

/* These types MUST be 16-bit or 32-bit */
typedef int				INT;
typedef unsigned int	UINT;

/* This type MUST be 8-bit */
#ifdef __ICCARM__
  typedef __UINT8_T_TYPE__	BYTE;
#else
  typedef unsigned char	BYTE;
#endif

/* These types MUST be 16-bit */
#ifdef __ICCARM__
  typedef __INT16_T_TYPE__	SHORT;
  typedef __UINT16_T_TYPE__	WORD;
  typedef __UINT16_T_TYPE__	WCHAR;
#else
  typedef short			SHORT;
  typedef unsigned short	WORD;
  typedef unsigned short	WCHAR;
#endif

/* These types MUST be 32-bit */
#ifdef __ICCARM__
  typedef __INT32_T_TYPE__	LONG;
  typedef __UINT32_T_TYPE__	DWORD;
#else
  typedef long			LONG;
  typedef unsigned long	DWORD;
#endif

/* This type MUST be 64-bit (Remove this for C89 compatibility) */
#ifdef __ICCARM__
  typedef __UINT64_T_TYPE__ QWORD;
#else
  typedef unsigned long long QWORD;
#endif

#endif /* _WIN32 */

#endif /* _FF_INTEGER */



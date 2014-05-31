/*  Glue functions for the minIni library, based on the FatFs and Petit-FatFs
 *  libraries, see http://elm-chan.org/fsw/ff/00index_e.html
 *
 *  By CompuPhase, 2008-2012
 *  This "glue file" is in the public domain. It is distributed without
 *  warranties or conditions of any kind, either express or implied.
 *
 *  (The FatFs and Petit-FatFs libraries are copyright by ChaN and licensed at
 *  its own terms.)
 */

#ifndef _MINGLUE_FATFS_H__
#define _MINGLUE_FATFS_H__

#ifdef __HIWARE__
  /* switching off some warnings */
  #pragma MESSAGE DISABLE C1420 /* Result of function call is ignored */
  #pragma MESSAGE DISABLE C5909 /* Assignment in condition */
#endif


%if defined(FatFsIniBufferSize)
#define INI_BUFFERSIZE  %FatFsIniBufferSize       /* maximum line length, maximum path length */
%else
#define INI_BUFFERSIZE  256       /* maximum line length, maximum path length */
%endif

/* You must set _USE_STRFUNC to 1 or 2 in the include file ff.h (or tff.h)
 * to enable the "string functions" fgets() and fputs().
 */
#include "ff.h"                   /* include tff.h for Tiny-FatFs */

#define INI_FILETYPE    FIL
#define ini_openread(filename,file)   (f_open((file), (filename), FA_READ+FA_OPEN_EXISTING) == FR_OK)
#define ini_openwrite(filename,file)  (f_open((file), (filename), FA_WRITE+FA_CREATE_ALWAYS) == FR_OK)
#define ini_close(file)               (f_close(file) == FR_OK)
#define ini_read(buffer,size,file)    f_gets((buffer), (size),(file))
#define ini_write(buffer,file)        f_puts((buffer), (file))
#define ini_remove(filename)          (f_unlink(filename) == FR_OK)

#define INI_FILEPOS                   unsigned long//DWORD
#define ini_tell(file,pos)            (*(pos) = f_tell((file)))
#define ini_seek(file,pos)            (f_lseek((file), *(pos)) == FR_OK)

#define ini_assert(condition)         /* empty */

int ini_rename(TCHAR *source, const TCHAR *dest);

#if defined(INI_REAL)
  #include <stdio.h> /* for sprintf() */

  #define ini_ftoa(string,value)        sprintf((string),"%%f",(value))
  #define ini_atof(string)              (INI_REAL)strtod((string),NULL)
#endif /* defined INI_REAL */


#endif /* _MINGLUE-FATFS_H__ */

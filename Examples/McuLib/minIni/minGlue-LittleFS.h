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

#include "McuMinINIconfig.h"

#if McuMinINI_CONFIG_FS==McuMinINI_CONFIG_FS_TYPE_LITTLE_FS

#ifdef __HIWARE__
  /* switching off some warnings */
  #pragma MESSAGE DISABLE C1420 /* Result of function call is ignored */
  #pragma MESSAGE DISABLE C5909 /* Assignment in condition */
#endif

#define INI_BUFFERSIZE  (McuMinINI_CONFIG_BUFFER_SIZE)       				 /* maximum line length, maximum path length */

/* You must set _USE_STRFUNC to 1 or 2 in the include file ff.h (or tff.h)
 * to enable the "string functions" fgets() and fputs().
 */
#include "littleFS/lfs.h"
#include "littleFS/McuLittleFS.h"

#define TCHAR           char

int ini_fileReadOpen(lfs_file_t *file, const char *name);
int ini_fileWriteOpen(lfs_file_t *file, const char *name);
int ini_fileClose(lfs_file_t *file);
int ini_fileRead( void *buffer, lfs_size_t size, lfs_file_t *file);
int ini_fileWrite( void *buffer, lfs_file_t *file);
int ini_fileRemove(const char *filename);
int ini_fileTell(lfs_file_t *file ,unsigned long* pos);
int ini_fileSeek(lfs_file_t *file ,unsigned long* pos);

#define INI_FILETYPE    			        lfs_file_t
#define ini_openread(filename,file)   (ini_fileReadOpen((file), (filename)))
#define ini_openwrite(filename,file)  (ini_fileWriteOpen((file), (filename)))
#define ini_close(file)               (ini_fileClose(file))
#define ini_read(buffer,size,file)    McuLFS_gets((buffer), (size),(file))
#define ini_write(buffer,file)        McuLFS_puts((buffer), (file))
#define ini_remove(filename)          (ini_fileRemove(filename))

#define INI_FILEPOS                   unsigned long//DWORD
#define ini_tell(file,pos)            (ini_fileTell((file),(pos)))
#define ini_seek(file,pos)            (ini_fileSeek((file),(pos)))

#define ini_assert(condition)         /* empty */

void ini_init(void);
void ini_deinit(void);

int ini_rename(char *source, const char *dest);

#if defined(INI_REAL)
  #include <stdio.h> /* for sprintf() */

  #define ini_ftoa(string,value)        sprintf((string),"%f",(value))
  #define ini_atof(string)              (INI_REAL)strtod((string),NULL)
#endif /* defined INI_REAL */

#endif /* McuMinINI_CONFIG_FS_TYPE_LITTLE_FS */

#endif /* _MINGLUE-FATFS_H__ */

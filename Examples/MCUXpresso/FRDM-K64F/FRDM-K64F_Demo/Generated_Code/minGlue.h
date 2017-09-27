/*  Glue functions for the minIni library, based on the C/C++ stdio library
 *
 *  Or better said: this file contains macros that maps the function interface
 *  used by minIni to the standard C/C++ file I/O functions.
 *
 *  By CompuPhase, 2008-2012
 *  This "glue file" is in the public domain. It is distributed without
 *  warranties or conditions of any kind, either express or implied.
 */

#if 0
/* map required file I/O types and functions to the standard C library */
#include <stdio.h>

#define INI_FILETYPE                  FILE*
#define ini_openread(filename,file)   ((*(file) = fopen((filename),"rb")) != NULL)
#define ini_openwrite(filename,file)  ((*(file) = fopen((filename),"wb")) != NULL)
#define ini_close(file)               (fclose(*(file)) == 0)
#define ini_read(buffer,size,file)    (fgets((buffer),(size),*(file)) != NULL)
#define ini_write(buffer,file)        (fputs((buffer),*(file)) >= 0)
#define ini_rename(source,dest)       (rename((source), (dest)) == 0)
#define ini_remove(filename)          (remove(filename) == 0)

#define INI_FILEPOS                   fpos_t
#define ini_tell(file,pos)            (fgetpos(*(file), (pos)) == 0)
#define ini_seek(file,pos)            (fsetpos(*(file), (pos)) == 0)

/* for floating-point support, define additional types and functions */
#define INI_REAL                      float
#define ini_ftoa(string,value)        sprintf((string),"%f",(value))
#define ini_atof(string)              (INI_REAL)strtod((string),NULL)
#endif

#include "minGlue-FatFs.h"



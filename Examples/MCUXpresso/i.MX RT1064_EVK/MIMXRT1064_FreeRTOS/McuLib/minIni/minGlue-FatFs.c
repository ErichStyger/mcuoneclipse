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

#include "McuMinINIconfig.h" /* MinIni config file */

#if McuMinINI_CONFIG_FS==McuMinINI_CONFIG_FS_TYPE_FAT_FS
#include "ff.h"                   /* include tff.h for Tiny-FatFs */
#include "minGlue-FatFs.h"
#include <stddef.h>
#include <string.h>

int ini_rename(TCHAR *source, const TCHAR *dest)
{
  /* Function f_rename() does not allow drive letters in the destination file */
  char *drive = strchr(dest, ':');
  drive = (drive == NULL) ? (char*)dest : drive + 1;
  return (f_rename(source, drive) == FR_OK);
}

int ini_deinit(void) {
  return 1; /* ok */
}

int ini_init(void) {
  return 1; /* ok */
}

#endif /* McuMinINI_CONFIG_FS==McuMinINI_CONFIG_FS_TYPE_FAT_FS */


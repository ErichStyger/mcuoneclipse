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

#include "littleFS/lfs.h"
#include "minGlue-LittleFS.h"
#include <stddef.h>
#include <string.h>
#include "McuUtility.h"

#if McuMinINI_CONFIG_FS==McuMinINI_CONFIG_FS_TYPE_LITTLE_FS

int ini_rename(char *source, const char *dest) {
	lfs_t *FS_lfs = McuLFS_GetFileSystem();
	/* Function f_rename() does not allow drive letters in the destination file */
	char *drive = strchr(dest, ':');
	drive = (drive == NULL) ? (char*)dest : drive + 1;
	return (lfs_rename(FS_lfs, source, dest) == 0);
}

int ini_fileReadOpen(lfs_file_t *file, const char *name) {
	lfs_t *FS_lfs = McuLFS_GetFileSystem();
	return (lfs_file_open(FS_lfs, file, name, LFS_O_RDONLY)== 0);
}

int ini_fileWriteOpen(lfs_file_t *file, const char *name) {
	lfs_t *FS_lfs = McuLFS_GetFileSystem();
	return (lfs_file_open(FS_lfs, file, name, LFS_O_RDWR | LFS_O_CREAT)== 0);
}

int ini_fileClose(lfs_file_t *file) {
	lfs_t *FS_lfs = McuLFS_GetFileSystem();
	return (lfs_file_close(FS_lfs, file) == 0);
}

int ini_fileRemove(const char *filename) {
	lfs_t *FS_lfs = McuLFS_GetFileSystem();
	return (lfs_remove(FS_lfs, filename) == 0);
}

int ini_fileTell(lfs_file_t *file ,unsigned long* pos) {
	lfs_t *FS_lfs = McuLFS_GetFileSystem();
	*pos = lfs_file_tell(FS_lfs, file);
	return TRUE;
}

int ini_fileSeek(lfs_file_t *file ,unsigned long* pos) {
	lfs_t *FS_lfs = McuLFS_GetFileSystem();
	lfs_file_seek(FS_lfs, file, *pos, LFS_SEEK_SET);
	return TRUE;
}

void ini_init(void) {}
void ini_deinit(void) {}


#endif /* McuMinINI_CONFIG_FS_TYPE_LITTLE_FS */

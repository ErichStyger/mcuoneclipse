/* @file
 * uffs_user.h
 *
 *  Created on: Sep 2, 2013
 *      Author: Marc Lindahl
 *  
 *  User defines for mount points, other implementation specifics
 */

#ifndef UFFS_USER_H_
#define UFFS_USER_H_

#include "uffs/uffs_os.h"
#include "uffs/uffs_fd.h"
#include "uffs/uffs_device.h"
#include "uffs/uffs_mtb.h"
#include "uffs/uffs_fs.h"
#include "uffs/uffs_find.h"

#define UFFS_PATHSIZE  128		// this has a big effect on stack usage by uffs_shell.c

#define MSG(msg,...) uffs_PerrorRaw(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)
#define MSGLN(msg,...) uffs_Perror(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)


/**
 * \brief POSIX DIR - should be in uffs_fd.h but was in uffs_fd.c
 */
struct uffs_dirSt {
    struct uffs_ObjectSt   *obj;		/* dir object */
    struct uffs_FindInfoSt f;			/* find info */
    struct uffs_ObjectInfoSt info;		/* object info */
    struct uffs_dirent dirent;			/* dir entry */
};

int my_init_filesystem(void);
int my_release_filesystem(void);
uffs_MountTable * get_flash_mount_table(void);

extern byte UFFS_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void uffs_SetupDebugOutputCLS(const CLS1_ConstStdIOType *io);


#endif /* UFFS_USER_H_ */

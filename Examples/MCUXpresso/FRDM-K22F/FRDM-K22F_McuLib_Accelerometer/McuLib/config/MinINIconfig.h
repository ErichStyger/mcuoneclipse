/**
 * \file
 * \brief Configuration header file for MinINI
 *
 * This header file is used to configure settings of the MinINI module.
 */
#ifndef __MinINI_CONFIG_H
#define __MinINI_CONFIG_H

#define MinINI_CONFIG_FS_TYPE_GENERIC  (0) /* Generic File System */
#define MinINI_CONFIG_FS_TYPE_FAT_FS   (1) /* FatFS File System */
#define MinINI_CONFIG_FS_TYPE_TINY_FS  (2) /* TinyFS File System */

#ifndef MinINI_CONFIG_FS
  #define MinINI_CONFIG_FS      (CONFIG_FS_TYPE_GENERIC)
    /*!< File System integration used, one of MinINI_CONFIG_FS_TYPE_GENERIC, MinINI_CONFIG_FS_TYPE_FAT_FS, MinINI_CONFIG_FS_TYPE_TINY_FS */
#endif

#define PORTABLE_STRNICMP

//#define INI_REAL double

//#define INI_READONLY

#define NDEBUG

#define INI_USE_GLOBAL_BUFFER   0 /* 0: use stack for buffer; 1: use global memory for buffer */

#endif /* __MinINI_CONFIG_H */

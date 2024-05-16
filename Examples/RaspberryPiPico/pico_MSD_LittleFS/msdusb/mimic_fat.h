/*
 * mimic FAT file system functions
 *
 * Copyright 2024, Hiroyuki OYAMA. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef PICO_LITTLEFS_USB_MIMIC_FAT_H_
#define PICO_LITTLEFS_USB_MIMIC_FAT_H_

#include <ctype.h>
#include <math.h>
#include <pico/stdlib.h>
#include <lfs.h>
#include "unicode.h"

#define LITTLE_ENDIAN16(x) (x)
#define LITTLE_ENDIAN32(x) (x)


typedef struct {
    uint8_t DIR_Name[11];
    uint8_t DIR_Attr;
    uint8_t DIR_NTRes;
    uint8_t DIR_CrtTimeTenth;
    uint16_t DIR_CrtTime;
    uint16_t DIR_CrtDate;
    uint16_t DIR_LstAccDate;
    uint16_t DIR_FstClusHI;
    uint16_t DIR_WrtTime;
    uint16_t DIR_WrtDate;
    uint16_t DIR_FstClusLO;
    uint32_t DIR_FileSize;
} fat_dir_entry_t;

typedef struct {
    uint8_t LDIR_Ord;
    uint8_t LDIR_Name1[10];
    uint8_t LDIR_Attr;
    uint8_t LDIR_Type;
    uint8_t LDIR_Chksum;
    uint8_t LDIR_Name2[12];
    uint8_t LDIR_FstClusLO[2];
    uint8_t LDIR_Name3[4];
} fat_lfn_t;

#define DISK_SECTOR_SIZE   512


void mimic_fat_init(const struct lfs_config *c);
size_t mimic_fat_total_sector_size(void);
void mimic_fat_create_cache(void);
void mimic_fat_cleanup_cache(void);
void mimic_fat_read(uint8_t lun, uint32_t sector, void *buffer, uint32_t bufsize);
void mimic_fat_write(uint8_t lun, uint32_t sector, void *buffer, uint32_t bufsize);
bool mimic_fat_usb_device_is_enabled(void);
void mimic_fat_update_usb_device_is_enabled(bool enable);

#endif

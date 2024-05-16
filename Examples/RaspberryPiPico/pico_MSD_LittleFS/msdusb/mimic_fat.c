/*
 * mimic FAT file system functions
 *
 * Copyright 2024, Hiroyuki OYAMA. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "mimic_fat.h"


#define ANSI_RED "\e[31m"
#define ANSI_CLEAR "\e[0m"

#ifdef  ENABLE_TRACE
#define TRACE(...) (printf(__VA_ARGS__))
#else
#define TRACE(...) ((void)0)
#endif


static const struct lfs_config *littlefs_lfs_config = NULL;



#define FAT_SHORT_NAME_MAX           11
#define FAT_LONG_FILENAME_CHUNK_MAX  13


static uint8_t fat_disk_image[1][DISK_SECTOR_SIZE] = {
  //------------- Block0: Boot Sector -------------//
  {
      0xEB, 0x3C, 0x90, // BS_JmpBoot
      'M', 'S', 'D', 'O', 'S', '5', '.', '0', // BS_OEMName
      0x00, 0x02, // BPB_BytsPerSec
      0x01, // BPB_SecPerClus
      0x01, 0x00, // BPB_RsvdSecCnt
      0x01, // BPB_NumFATs
      0x10, 0x00, // BPB_RootEntCnt
      0x00, 0x00, // BPB_TotSec16, to be set up later
      0xF8, // BPB_Media
      0x01, 0x00, // BPB_FATSz16
      0x01, 0x00, // BPB_SecPerTrk
      0x01, 0x00, // BPB_NumHeads
      0x00, 0x00, 0x00, 0x00, // BPB_HiddSec
      0x00, 0x00, 0x00, 0x00, // BPB_TotSec32
      0x80, // BS_DrvNum
      0x00, // BS_Reserved
      0x29, // BS_BootSig
      0x34, 0x12, 0x00, 0x00, // BS_VolID
      'l' , 'i' , 't' , 't' , 'l' , 'e' , 'f' , 's' , 'U' , 'S' , 'B' , // BS_VolLab
      0x46, 0x41, 0x54, 0x31, 0x32, 0x20, 0x20, 0x20, // BS_FilSysType
      0x00, 0x00,
      // Zero up to 2 last bytes of FAT magic code
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA
  }
};

static lfs_t real_filesystem;
static bool usb_device_is_enabled = false;

static lfs_file_t fat_cache;

void mimic_fat_init(const struct lfs_config *c) {
    littlefs_lfs_config = c;
}

bool mimic_fat_usb_device_is_enabled(void) {
    return usb_device_is_enabled;
}

void mimic_fat_update_usb_device_is_enabled(bool enable) {
    usb_device_is_enabled = enable;
}


static void print_block(uint8_t *buffer, size_t l) {
    size_t offset = 0;
    for (size_t i = 0; i < l; ++i) {
        if (i % 16 == 0)
            printf("0x%04u%s", offset, (i % 512) == 0 ? ">" : " ");
        if (isalnum(buffer[i])) {
            printf("'%c' ", buffer[i]);
        } else {
            printf("0x%02x", buffer[i]);
        }
        if (i % 16 == 15) {
            printf("\n");
            offset += 16;
        } else {
            printf(", ");
        }
    }
}

static void print_hex(uint8_t *buffer, size_t l) {
    size_t offset = 0;
    for (size_t i = 0; i < l; ++i) {
        if (i % 16 == 0)
            printf("0x%04u%s ", offset, (i % 512) == 0 ? ">" : " ");
        printf("0x%02x,", buffer[i]);
        if (i % 16 == 15) {
            printf("\n");
            offset += 16;
        }
    }
}

static void print_dir_entry(void *buffer) {
    uint8_t pbuffer[11+1];
    fat_dir_entry_t *dir = (fat_dir_entry_t *)buffer;
    TRACE("--------\n");
    for (size_t i = 0; i < DISK_SECTOR_SIZE / sizeof(fat_dir_entry_t); i++) {
        if (dir->DIR_Name[0] == '\0') {
            break;
        }
        if ((dir->DIR_Attr & 0x0F) != 0x0F) {
            memcpy(pbuffer, &dir->DIR_Name, 11);
            pbuffer[11] = '\0';
            TRACE("name='%s' attr=0x%02X size=%lu cluster=%u\n",
                   pbuffer,
                   dir->DIR_Attr,
                   dir->DIR_FileSize,
                   dir->DIR_FstClusLO);
        } else {
            fat_lfn_t *lfn = (fat_lfn_t *)dir;
            uint16_t utf16le[13 + 1];
            memcpy(utf16le, lfn->LDIR_Name1, 5*2);
            memcpy(utf16le + 5, lfn->LDIR_Name2, 6*2);
            memcpy(utf16le + 5 + 6, lfn->LDIR_Name3, 2*2);
            utf16le[13] = '\0';
            char utf8[13 * 4 + 1];
            utf16le_to_utf8(utf8, sizeof(utf8), utf16le, 13);
            TRACE("name='%s' attr=0x%02X ord=0x%02X checksum=%u  cluster=%u\n",
                  utf8, lfn->LDIR_Attr, lfn->LDIR_Ord, lfn->LDIR_Chksum, dir->DIR_FstClusLO);
        }
        dir++;
    }
}

static int is_fat_sfn_symbol(uint8_t c) {
    switch (c) {
    case '$':
    case '%':
    case '\'':
    case '-':
    case '_':
    case '@':
    case '~':
    case '`':
    case '!':
    case '(':
    case ')':
    case '{':
    case '}':
    case '^':
    case '#':
    case '&':
        return 1;
        break;
    default:
        return 0;
    }
}

static uint16_t read_fat(int cluster) {
    uint16_t offset = (uint16_t)floor((float)cluster + ((float)cluster / 2));
    lfs_soff_t o = lfs_file_seek(&real_filesystem, &fat_cache, offset, LFS_SEEK_SET);
    if (o < 0) {
        printf("read_fat: lfs_file_seek error=%ld\n", o);
        return 0xFFF;
    }
    uint8_t current[2] = {0};
    lfs_ssize_t s = lfs_file_read(&real_filesystem, &fat_cache, current, sizeof(current));
    if (s < 0) {
        printf("read_fat: lfs_file_read error=%ld\n", s);
    }

    int16_t result = 0;
    if (cluster & 0x01) {
        result = (current[0] >> 4) | ((uint16_t)current[1] << 4);
    } else {
        result = current[0] | ((uint16_t)(current[1] & 0x0F) << 8);
    }
    return result;
}

static void update_fat(uint32_t cluster, uint16_t value) {
    size_t offset = (size_t)floor((float)cluster + ((float)cluster / 2));

    uint8_t previous[2] = {0};
    lfs_soff_t o = lfs_file_seek(&real_filesystem, &fat_cache, offset, LFS_SEEK_SET);
    if (o < 0) {
        printf("update_fat: lfs_file_seek error=%ld\n", o);
        return;
    }
    lfs_ssize_t s = lfs_file_read(&real_filesystem, &fat_cache, previous, sizeof(previous));
    if (s < 0) {
        printf("update_fat: lfs_file_read error=%ld\n", s);
        return;
    }
    if (cluster & 0x01) {
        previous[0] = (previous[0] & 0x0F) | (value << 4);
        previous[1] = value >> 4;
    } else {
        previous[0] = value;
        previous[1] = (previous[1] & 0xF0) | ((value >> 8) & 0x0F);
    }

    o = lfs_file_seek(&real_filesystem, &fat_cache, offset, LFS_SEEK_SET);
    if (o < 0) {
        printf("update_fat: lfs_file_seek error=%ld\n", o);
        return;
    }
    s = lfs_file_write(&real_filesystem, &fat_cache, previous, sizeof(previous));
    if (s != sizeof(previous)) {
        printf("update_fat: lfs_file_write error=%ld\n", s);
    }
}

#define BUFFER_SIZE  512
#define END_OF_CLUSTER_CHAIN  0xFFF

static size_t bulk_update_fat_buffer_read(size_t offset, void *buffer, size_t size) {
    lfs_soff_t o = lfs_file_seek(&real_filesystem, &fat_cache, offset, LFS_SEEK_SET);
    if (o < 0) {
         printf("bulk_update_fat_buffer_read: lfs_file_seek error=%ld\n", o);
         return 0;
    }
    lfs_ssize_t s = lfs_file_read(&real_filesystem, &fat_cache, buffer, size);
    if (s < 0) {
        printf("bulk_update_fat_buffer_read: lfs_file_read error=%ld\n", s);
        return 0;
    }
    return (size_t)s;
}

static size_t bulk_update_fat_buffer_write(size_t offset, void *buffer, size_t size) {
    lfs_soff_t o = lfs_file_seek(&real_filesystem, &fat_cache, offset, LFS_SEEK_SET);
    if (o < 0) {
        printf("bulk_update_fat_buffer_write: lfs_file_seek error=%ld\n", o);
        return 0;
    }
    lfs_ssize_t s = lfs_file_write(&real_filesystem, &fat_cache, buffer, size);
    if (s < 0) {
        printf("bulk_update_fat_buffer_write: lfs_file_read error=%ld\n", s);
        return 0;
    }
    return (size_t)s;
}

static size_t bulk_update_fat(uint32_t start_cluster, size_t size) {
    size_t num_clusters = ceil((double)size / 512);
    unsigned char buffer[BUFFER_SIZE];
    unsigned int current_cluster = start_cluster;
    unsigned int next_cluster;
    int initial_offset = (3 * start_cluster) / 2;
    int initial_sector = initial_offset / BUFFER_SIZE;

    size_t read = bulk_update_fat_buffer_read(initial_sector * BUFFER_SIZE, buffer, sizeof(buffer));
    if (read == 0)
        return 0;

    int sector_size = 512;

    for (unsigned int i = 0; i < num_clusters; i++) {
        int offset = floor((3 * current_cluster) / 2.0);
        int buffer_index = offset % sector_size;

        next_cluster = (i < num_clusters - 1) ? current_cluster + 1 : END_OF_CLUSTER_CHAIN;
        if (current_cluster & 0x01) {
            buffer[buffer_index] = (buffer[buffer_index] & 0x0F) | (next_cluster << 4);
            buffer[buffer_index + 1] = (next_cluster >> 4) & 0xFF;
        } else {
            buffer[buffer_index] = next_cluster & 0xFF;
            buffer[buffer_index + 1] = (buffer[buffer_index + 1] & 0xF0) | ((next_cluster >> 8) & 0x0F);
        }

        // FAT12 sector boundaries
        if (((current_cluster & 0x01) && buffer_index + 2 >= sector_size) ||
             (buffer_index + 1 >= sector_size))
        {

            size_t write = bulk_update_fat_buffer_write(initial_sector * BUFFER_SIZE, buffer, sizeof(buffer));
            if (write == 0)
                return 0;

            initial_sector++;

            read = bulk_update_fat_buffer_read(initial_sector * BUFFER_SIZE, buffer, sizeof(buffer));
            if (read == 0)
                return 0;

            buffer_index = 0;
            if (current_cluster & 0x01) {
                buffer[buffer_index] = (next_cluster >> 4) & 0xFF;
            } else {
                buffer[buffer_index] = (buffer[buffer_index] & 0xF0) | ((next_cluster >> 8) & 0x0F);
            }
        }
        current_cluster++;
    }

    size_t write = bulk_update_fat_buffer_write(initial_sector * BUFFER_SIZE, buffer, sizeof(buffer));
    if (write == 0)
        return 0;
    return start_cluster + num_clusters + 1;
}

static void init_fat(void) {
    uint64_t storage_size = littlefs_lfs_config->block_count * littlefs_lfs_config->block_size;
    uint32_t cluster_size = storage_size / (DISK_SECTOR_SIZE * 1);

    struct lfs_info finfo;
    int err = lfs_stat(&real_filesystem, ".mimic", &finfo);
    if (err == LFS_ERR_NOENT) {
        err = lfs_mkdir(&real_filesystem, ".mimic");
        if (err != LFS_ERR_OK) {
            printf("init_fat: can't create .mimic directory: err=%d\n", err);
            return;
        }
    }

    err = lfs_file_open(&real_filesystem, &fat_cache, ".mimic/FAT", LFS_O_RDWR|LFS_O_CREAT);
    assert(err == 0);

    uint8_t head[3] = {0xF8, 0xFF, 0xFF};
    head[0] = 0xF8;
    head[1] = 0xFF;
    head[2] = 0xFF;
    lfs_ssize_t s = lfs_file_write(&real_filesystem, &fat_cache, head, sizeof(head));
    if (s != sizeof(head)) {
        printf("init_fat: lfs_file_write error=%ld\n", s);
        return;
    }

    uint8_t pair[3] = {0x00, 0x00, 0x00};
    for (size_t i = 0; i < (float)cluster_size / 2; i++) {
        s = lfs_file_write(&real_filesystem, &fat_cache, pair, sizeof(pair));
        if (s != sizeof(pair)) {
            printf("init_fat: lfs_file_write error=%ld\n", s);
            break;
        }
    }
}


static void print_fat(size_t l) {
    TRACE("FAT table-------\n");
    for (size_t i = 0; i < l; i++) {
        TRACE(" cluster=%d fat=%03x\n", i, read_fat(i));
    }
}


static void set_fat_short_filename(uint8_t *short_filename, const char *filename) {
    uint8_t buffer[LFS_NAME_MAX + 1];
    strncpy((char *)buffer, filename, sizeof(buffer));

    char *basename = strtok((char *)buffer, ".");
    char *ext = strtok(NULL, ".");
    snprintf((char *)short_filename, sizeof(buffer), "%-8s%-3s", basename, ext);
}

static void restore_from_short_filename(char *filename, const char *short_filename) {
    char buffer[FAT_SHORT_NAME_MAX + 1];
    strncpy(buffer, short_filename, sizeof(buffer) - 1);

    uint8_t basename[8 + 1];
    uint8_t fileext[3 + 1];
    for (int i = 0; i < 8; i++) {
        if (buffer[i] != ' ') {
            basename[i] = buffer[i];
        } else {
            basename[i] = '\0';
            break;
        }
    }
    basename[sizeof(basename)-1] = '\0';
    for (int i = 0; i < 3; i++) {
        if (buffer[8+i] != ' ') {
            fileext[i] = buffer[8+i];
        } else {
            fileext[i] = '\0';
            break;
        }
    }
    fileext[sizeof(fileext)-1] = '\0';

    sprintf((char *)filename, "%s.%s", basename, fileext);
}

static void restore_from_short_dirname(char *filename, const char *short_dirname) {
    strcpy(filename, short_dirname);

    size_t length = FAT_SHORT_NAME_MAX;
    while (length > 0 && filename[length - 1] == ' ') {
        --length;
    }
    filename[length] = '\0';
}

static bool is_short_filename_file(uint8_t *filename) {
    char buffer[LFS_NAME_MAX + 1];

    if (filename[0] == '.')
        return false;

    strncpy(buffer, (const char *)filename, sizeof(buffer));
    unsigned char *name = (unsigned char *)strtok(buffer, ".");
    if (strlen((char *)name) > 8) {
        return false;
    }
    unsigned char *ext = (unsigned char *)strtok(NULL, ".");
    if (strlen((char *)ext) > 3) {
        return false;
    }

    for (int i = 0; i < 8; i++) {
        if (name[i] == '\0') {
            break;
        }
        if (isalnum(name[i]) == 0 && is_fat_sfn_symbol(name[i]) == 0) {
            return false;
        }
        if (isalpha(name[i]) > 0 && isupper(name[i]) == 0) {
            return false;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (ext[i] == '\0') {
            break;
        }
        if (isalpha(ext[i]) > 0 && isupper(ext[i]) == 0) {
            return false;
        }
        if ((isalnum(ext[i]) == 0) && (is_fat_sfn_symbol(ext[i]) == 0)) {
            return false;
        }
    }
    return true;
}

static void to_uppercase(char *str) {
    if (str == NULL)
        return;

    while (*str) {
        *str = toupper((unsigned char) *str);
        str++;
    }
}

static bool is_short_filename_dir(uint8_t *filename) {
    uint8_t buffer[LFS_NAME_MAX + 1];
    strncpy((char *)buffer, (const char *)filename, sizeof(buffer));
    if (strlen((const char *)filename) > FAT_SHORT_NAME_MAX) {
        return false;
    }
    for (size_t i = 0; i < FAT_SHORT_NAME_MAX; i++) {
        if (filename[i] == '\0') {
            break;
        }
        if (isalnum(filename[i]) == 0 && is_fat_sfn_symbol(filename[i]) == 0) {
            return false;
        }
        if (isalpha(filename[i]) > 0 && isupper(filename[i]) == 0) {
            return false;
        }
    }
    return true;
}

static void create_shortened_short_filename(uint8_t *sfn, const char *long_filename) {
    uint8_t buffer[LFS_NAME_MAX + 1];
    uint8_t filename[FAT_SHORT_NAME_MAX + 1];

    strncpy((char *)buffer, long_filename, sizeof(buffer));
    char *name = strtok((char *)buffer, ".");
    (void)name;
    char *ext = strtok(NULL, ".");
    ext[3] = '\0';
    to_uppercase(ext);
    snprintf((char *)filename, sizeof(filename), "FIL~%04X%-3s", rand() % 0xFFFF, ext);
    memcpy(sfn, filename, FAT_SHORT_NAME_MAX);
}

static void create_shortened_short_filename_dir(uint8_t *sfn, const char *long_filename) {
    (void)long_filename;
    uint8_t filename[FAT_SHORT_NAME_MAX + 1];

    snprintf((char *)filename, sizeof(filename), "DIR~%04X   ", rand() % 0xFFFF);
    memcpy(sfn, filename, FAT_SHORT_NAME_MAX);
}

static uint8_t filename_check_sum(const uint8_t *filename) {
    uint8_t i, sum;

    for (i = sum = 0; i < FAT_SHORT_NAME_MAX; i++) {
        sum = (sum >> 1) + (sum << 7) + filename[i];
    }
    return sum;
}

static void set_LFN_name123(fat_lfn_t *dir, const uint16_t *filename) {
    memcpy(&dir->LDIR_Name1, filename + 0, sizeof(uint16_t) * 5);
    memcpy(&dir->LDIR_Name2, filename + 5, sizeof(uint16_t) * 6);
    memcpy(&dir->LDIR_Name3, filename + 5+6, sizeof(uint16_t) * 2);
}

void set_volume_label_entry(fat_dir_entry_t *dir, const char *name) {
    uint8_t sfn_name[FAT_SHORT_NAME_MAX + 1];
    snprintf((char *)sfn_name, sizeof(sfn_name), "%-11s", name);

    memcpy(dir->DIR_Name, sfn_name, FAT_SHORT_NAME_MAX);
    dir->DIR_Attr = 0x08;
    dir->DIR_NTRes = 0;
    dir->DIR_CrtTimeTenth = 0;
    dir->DIR_CrtTime = 0;
    dir->DIR_CrtDate = 0;
    dir->DIR_LstAccDate = 0;
    dir->DIR_FstClusHI = 0;
    dir->DIR_WrtTime = LITTLE_ENDIAN16(0x4F6D);
    dir->DIR_WrtDate = LITTLE_ENDIAN16(0x6543);
    dir->DIR_FstClusLO = 0;
    dir->DIR_FileSize = 0;
}

static void set_directory_entry(fat_dir_entry_t *dir, const char *name, int cluster) {
    uint8_t sfn_name[LFS_NAME_MAX + 1];
    snprintf((char *)sfn_name, sizeof(sfn_name), "%-11s", name);
    memcpy(dir->DIR_Name, sfn_name, FAT_SHORT_NAME_MAX);
    dir->DIR_Attr = 0x10; // directory
    dir->DIR_NTRes = 0;
    dir->DIR_CrtTimeTenth = 0xC6;
    dir->DIR_CrtTime = LITTLE_ENDIAN16(0x526D);
    dir->DIR_CrtDate = LITTLE_ENDIAN16(0x6543);
    dir->DIR_LstAccDate = LITTLE_ENDIAN16(0x6543);
    dir->DIR_FstClusHI = 0;
    dir->DIR_WrtTime = LITTLE_ENDIAN16(0x526D);
    dir->DIR_WrtDate = LITTLE_ENDIAN16(0x6543);
    dir->DIR_FstClusLO = cluster;
    dir->DIR_FileSize = 0;
}

static void set_file_entry(fat_dir_entry_t *dir, struct lfs_info *info, int cluster) {
    set_fat_short_filename(dir->DIR_Name, info->name);
    dir->DIR_Attr = 0x20;
    dir->DIR_NTRes = 0;
    dir->DIR_CrtTimeTenth = 0xC6;
    dir->DIR_CrtTime = LITTLE_ENDIAN16(0x526D);
    dir->DIR_CrtDate = LITTLE_ENDIAN16(0x6543);
    dir->DIR_LstAccDate = LITTLE_ENDIAN16(0x6543);
    dir->DIR_FstClusHI = 0;
    dir->DIR_WrtTime = LITTLE_ENDIAN16(0x526D);
    dir->DIR_WrtDate = LITTLE_ENDIAN16(0x6543);
    dir->DIR_FstClusLO = info->size > 0 ? LITTLE_ENDIAN16(cluster) : 0;
    dir->DIR_FileSize = LITTLE_ENDIAN32(info->size);
}

static void set_long_file_entry(fat_dir_entry_t *dir, uint16_t *lfn_chunk, uint8_t lfn_order, uint8_t check_sum) {
    fat_lfn_t *long_dir_entry = (fat_lfn_t *)dir;
    set_LFN_name123(long_dir_entry, lfn_chunk);
    long_dir_entry->LDIR_Ord = lfn_order;
    long_dir_entry->LDIR_Attr = 0x0F;
    long_dir_entry->LDIR_Type = 0x00;
    long_dir_entry->LDIR_Chksum = check_sum;
    long_dir_entry->LDIR_FstClusLO[0] = 0x00;
    long_dir_entry->LDIR_FstClusLO[1] = 0x00;
}


/*
 * Save buffers sent by the host to LFS temporary files
 */
static bool save_temporary_file(uint32_t cluster, void *buffer) {
    TRACE("save_temporary_file: cluster=%lu\n", cluster);

    char filename[LFS_NAME_MAX + 1];
    int tens = (cluster / 10) % 10;
    int hundreds = (cluster / 100) % 10;
    int thousands = (cluster / 1000) % 10;

    snprintf(filename, sizeof(filename), ".mimic/%d", thousands);
    struct lfs_info finfo;
    int err = lfs_stat(&real_filesystem, filename, &finfo);
    if (err == LFS_ERR_NOENT) {
        err = lfs_mkdir(&real_filesystem, filename);
        if (err != LFS_ERR_OK) {
            printf("save_temporary_file: can't create '%s' directory: err=%d\n", filename, err);
            return false;
        }
    }
    snprintf(filename, sizeof(filename), ".mimic/%d/%1d", thousands, hundreds);
    err = lfs_stat(&real_filesystem, filename, &finfo);
    if (err == LFS_ERR_NOENT) {
        err = lfs_mkdir(&real_filesystem, filename);
        if (err != LFS_ERR_OK) {
            printf("save_temporary_file: can't create '%s' directory: err=%d\n", filename, err);
            return false;
        }
    }
    snprintf(filename, sizeof(filename), ".mimic/%d/%1d/%1d", thousands, hundreds, tens);
    err = lfs_stat(&real_filesystem, filename, &finfo);
    if (err == LFS_ERR_NOENT) {
        err = lfs_mkdir(&real_filesystem, filename);
        if (err != LFS_ERR_OK) {
            printf("save_temporary_file: can't create '%s' directory: err=%d\n", filename, err);
            return false;
        }
    }

    snprintf(filename, sizeof(filename), ".mimic/%d/%1d/%1d/%04ld", thousands, hundreds,tens, cluster);
    lfs_file_t f;
    err = lfs_file_open(&real_filesystem, &f, filename, LFS_O_RDWR|LFS_O_CREAT);
    if (err != LFS_ERR_OK) {
        printf("save_temporary_file: can't lfs_file_open '%s' err=%d\n", filename, err);
        return false;
    }
    lfs_file_write(&real_filesystem, &f, buffer, 512);
    lfs_file_close(&real_filesystem, &f);
    return 1;
}

static int read_temporary_file(uint32_t cluster, void *buffer) {
    lfs_file_t f;
    char filename[LFS_NAME_MAX + 1];

    int tens = (cluster/ 10) % 10;
    int hundreds = (cluster/ 100) % 10;
    int thousands = (cluster/ 1000) % 10;
    snprintf(filename, sizeof(filename), ".mimic/%d/%1d/%1d/%04ld", thousands, hundreds,tens, cluster);
    int err = lfs_file_open(&real_filesystem, &f, filename, LFS_O_RDONLY);
    if (err != LFS_ERR_OK) {
        if (err == LFS_ERR_NOENT)
            return err;
        printf("read_temporary_file: can't open '%s': err=%d\n", filename, err);
        return err;
    }

    lfs_ssize_t size = lfs_file_read(&real_filesystem, &f, buffer, 512);
    if (size != 512) {
        printf("read_temporary_file: can't read '%s': size=%lu\n", filename, size);
        lfs_file_close(&real_filesystem, &f);
        return err;
    }

    lfs_file_close(&real_filesystem, &f);
    return LFS_ERR_OK;
}

/*
static bool delete_temporary_file(uint32_t cluster) {
    printf("delete_temporary_file: cluster=%lu\n", cluster);

    char filename[LFS_NAME_MAX + 1];
    int tens = (file_id / 10) % 10;
    int hundreds = (file_id / 100) % 10;
    int thousands = (file_id / 1000) % 10;
    snprintf(filename, sizeof(filename), ".mimic/%d/%1d/%1d/%04ld", thousands, hundreds,tens, cluster);
    int err = lfs_remove(&real_filesystem, filename);
    if (err != LFS_ERR_OK) {
        printf("delete_temporary_file: can't lfs_remove '%s' error=%d\n", filename, err);
        return false;
    }
    return true;
}
*/

static fat_dir_entry_t *append_dir_entry_volume_label(fat_dir_entry_t *entry, const char *volume_label) {
    uint8_t name[FAT_SHORT_NAME_MAX + 1];

    snprintf((char *)name, sizeof(name), "%-11s", volume_label);
    memcpy(entry->DIR_Name, name, FAT_SHORT_NAME_MAX);
    entry->DIR_Attr = 0x08;
    entry->DIR_NTRes = 0;
    entry->DIR_CrtTimeTenth = 0;
    entry->DIR_CrtTime = 0;
    entry->DIR_CrtDate = 0;
    entry->DIR_LstAccDate = 0;
    entry->DIR_FstClusHI = 0;
    entry->DIR_WrtTime = LITTLE_ENDIAN16(0x4F6D);
    entry->DIR_WrtDate = LITTLE_ENDIAN16(0x6543);
    entry->DIR_FstClusLO = 0;
    entry->DIR_FileSize = 0;
    entry++;
    return entry;
}

static void long_filename_padding(uint16_t *filename, size_t length, size_t size) {
    for (size_t i = length; i < size; i++) {
        if (i == length)
            filename[i] = 0x0000;
        else
            filename[i] = 0xFFFF;
    }
}

static fat_dir_entry_t *append_dir_entry_directory(fat_dir_entry_t *entry, struct lfs_info *finfo, uint32_t cluster) {
    TRACE("append_dir_entry_directory '%s'\n", finfo->name);

    if (strcmp(finfo->name, ".") == 0 || strcmp(finfo->name, "..") == 0) {
        set_directory_entry(entry, finfo->name, cluster == 1 ? 0 : cluster);
    }
    else if (is_short_filename_dir((uint8_t *)finfo->name)) {
        set_directory_entry(entry, finfo->name, cluster);
    } else {
        fat_dir_entry_t short_dir_entry;

        set_directory_entry(&short_dir_entry, finfo->name, cluster);
        create_shortened_short_filename_dir(short_dir_entry.DIR_Name, finfo->name);
        uint8_t check_sum = filename_check_sum(short_dir_entry.DIR_Name);

        uint16_t filename[LFS_NAME_MAX + 1];
        size_t len = utf8_to_utf16le(filename, sizeof(filename), finfo->name, strlen(finfo->name));
        long_filename_padding(filename, len, LFS_NAME_MAX + 1);
        int long_filename_num = floor((len - 1) / FAT_LONG_FILENAME_CHUNK_MAX);

        for (int i = long_filename_num; i >= 0; i--) {
            uint8_t order = i + 1;
            uint16_t chunk[FAT_LONG_FILENAME_CHUNK_MAX];
            uint16_t *head = (uint16_t *)&(filename[i * FAT_LONG_FILENAME_CHUNK_MAX]);
            memcpy(chunk, head, sizeof(chunk));
            if (i == long_filename_num)
                order |= 0x40;
            set_long_file_entry(entry, chunk, order, check_sum);
            entry++;
        }
        memcpy(entry, &short_dir_entry, sizeof(short_dir_entry));
    }
    entry++;
    return entry;
}

static fat_dir_entry_t *append_dir_entry_file(fat_dir_entry_t *entry, struct lfs_info *finfo, uint32_t cluster) {
    TRACE("append_dir_entry_file '%s' cluster=%lu\n", finfo->name, cluster);

    if (is_short_filename_file((uint8_t *)finfo->name)) {
        set_file_entry(entry, finfo, cluster);
    } else {
        fat_dir_entry_t short_dir_entry;
        set_file_entry(&short_dir_entry, finfo, cluster);
        create_shortened_short_filename(short_dir_entry.DIR_Name, finfo->name);

        uint8_t check_sum = filename_check_sum(short_dir_entry.DIR_Name);

        uint16_t filename[LFS_NAME_MAX + 1];
        size_t len = utf8_to_utf16le(filename, sizeof(filename), finfo->name, strlen(finfo->name));
        long_filename_padding(filename, len, LFS_NAME_MAX + 1);
        int long_filename_num = floor((len - 1) / FAT_LONG_FILENAME_CHUNK_MAX);

        for (int i = long_filename_num; i >= 0; i--) {
            uint8_t order = i + 1;
            uint16_t chunk[FAT_LONG_FILENAME_CHUNK_MAX];
            uint16_t *head = (uint16_t *)&(filename[i * FAT_LONG_FILENAME_CHUNK_MAX]);
            memcpy(chunk, head, sizeof(chunk));
            if (i == long_filename_num)
                order |= 0x40;
            set_long_file_entry(entry, chunk, order, check_sum);
            entry++;
        }
        memcpy(entry, &short_dir_entry, sizeof(short_dir_entry));
    }

    entry++;
    return entry;
}

/*
 * Create a directory entry cache corresponding to the base file system
 *
 * Recursively traverse the specified base file system directory and update cache and allocation tables.
 */
static int create_dir_entry_cache(const char *path, uint32_t parent_cluster, uint32_t *allocated_cluster) {
    TRACE("create_dir_entry_cache('%s', %lu, %lu)\n", path, parent_cluster, *allocated_cluster);
    uint32_t current_cluster = *allocated_cluster;
    fat_dir_entry_t *entry;
    fat_dir_entry_t dir_entry[DISK_SECTOR_SIZE / sizeof(fat_dir_entry_t)] = {0};
    lfs_dir_t dir;
    struct lfs_info finfo;
    char directory_path[LFS_NAME_MAX * 2 + 1 + 1];  // for sprintf "%s/%s"
    entry = dir_entry;

    if (parent_cluster == 0) {
        entry = append_dir_entry_volume_label(entry, "littlefsUSB");
        current_cluster = 1;
    }
    update_fat(current_cluster, 0xFFF);

    int err = lfs_dir_open(&real_filesystem, &dir, path);
    if (err != LFS_ERR_OK) {
        printf("create_dir_entry_cache: lfs_dir_open('%s') error=%d\n", path, err);
        return err;
    }

    while (true) {
        err = lfs_dir_read(&real_filesystem, &dir, &finfo);
        if (err == 0)
            break;
        if (err < 0) {
            printf("create_dir_entry_cache: lfs_dir_read('%s') error=%d\n", path, err);
            break;
        }

        if (finfo.type == LFS_TYPE_DIR && parent_cluster == 0 && strcmp(finfo.name, ".mimic") == 0) {
            continue;
        }
        if (finfo.type == LFS_TYPE_DIR && parent_cluster == 0
            && (strcmp(finfo.name, ".") == 0 || strcmp(finfo.name, "..") == 0))
        {
            continue;
        }
        if (finfo.type == LFS_TYPE_DIR  && strcmp(finfo.name, ".") == 0) {
            entry = append_dir_entry_directory(entry, &finfo, current_cluster);
            continue;
        }
        if (finfo.type == LFS_TYPE_DIR  && strcmp(finfo.name, "..") == 0) {
            if (parent_cluster == 0)
                entry = append_dir_entry_directory(entry, &finfo, 0);
            else
                entry = append_dir_entry_directory(entry, &finfo, parent_cluster);
            continue;
        }

        if (finfo.type == LFS_TYPE_DIR) {
            *allocated_cluster += 1;
            update_fat(*allocated_cluster, 0xFFF);
            entry = append_dir_entry_directory(entry, &finfo, *allocated_cluster);
            if (parent_cluster == 0)
                strncpy(directory_path, finfo.name, sizeof(directory_path));
            else
                snprintf(directory_path, sizeof(directory_path), "%s/%s", path, finfo.name);
            directory_path[LFS_NAME_MAX] = '\0';

            err = create_dir_entry_cache((const char *)directory_path, current_cluster, allocated_cluster);
            if (err < 0) {
                lfs_dir_close(&real_filesystem, &dir);
                return err;
            }

        } else if (finfo.type == LFS_TYPE_REG) {
            uint32_t file_cluster = *allocated_cluster + 1;
            if (finfo.size > 0)
                *allocated_cluster = bulk_update_fat(file_cluster, finfo.size);
            entry = append_dir_entry_file(entry, &finfo, file_cluster);
        }
    }
    lfs_dir_close(&real_filesystem, &dir);
    save_temporary_file(current_cluster, dir_entry);
    return 0;
}

/*
 * Rebuild the directory entry cache.
 *
 * Execute when USB is connected.
 */
void mimic_fat_create_cache(void) {
    TRACE(ANSI_RED "mimic_fat_create_cache()\n" ANSI_CLEAR);

    lfs_unmount(&real_filesystem);
    int err = lfs_mount(&real_filesystem, littlefs_lfs_config);
    if (err < 0) {
        printf("mimic_fat_create_cache: lfs_mount error=%d\n", err);
        return;
    }

    mimic_fat_cleanup_cache();

    init_fat();

    uint32_t allocated_cluster = 1;
    create_dir_entry_cache("", 0, &allocated_cluster);
}

static void delete_directory(const char *path) {
    uint8_t filename[LFS_NAME_MAX + 1 + 8];
    lfs_dir_t dir;
    struct lfs_info finfo;

    int err = lfs_dir_open(&real_filesystem, &dir, path);
    if (err != LFS_ERR_OK) {
        return;
    }
    while (true) {
        err = lfs_dir_read(&real_filesystem, &dir, &finfo);
        if (err == 0)
            break;
        if (err < 0) {
            printf("delete_directory: lfs_dir_read('%s') error=%d\n", path, err);
            break;
        }
        if (strcmp(finfo.name, ".") == 0 ||
            strcmp(finfo.name, "..") == 0)
        {
            continue;
        }

        snprintf((char *)filename, sizeof(filename), "%s/%s", path, finfo.name);
        if (finfo.type == LFS_TYPE_DIR)
            delete_directory((const char *)filename);
        err = lfs_remove(&real_filesystem, (const char *)filename);
        if (err != LFS_ERR_OK) {
            printf("delete_directory: lfs_remove('%s') error=%d\n", filename, err);
            continue;
        }
    }
    lfs_dir_close(&real_filesystem, &dir);

}

void mimic_fat_cleanup_cache(void) {
    uint8_t filename[LFS_NAME_MAX + 1 + 8];
    lfs_dir_t dir;
    struct lfs_info finfo;

    int err = lfs_dir_open(&real_filesystem, &dir, ".mimic");
    if (err != LFS_ERR_OK) {
        return;
    }
    while (true) {
        err = lfs_dir_read(&real_filesystem, &dir, &finfo);
        if (err == 0)
            break;
        if (err < 0) {
            printf("mimic_fat_cleanup_cache: lfs_dir_read('%s') error=%d\n", ".mimic", err);
            break;
        }
        if (strcmp(finfo.name, ".") == 0 ||
            strcmp(finfo.name, "..") == 0)
        {
            continue;
        }

        snprintf((char *)filename, sizeof(filename), "%s/%s", ".mimic", finfo.name);
        delete_directory((const char *)filename);
    }
    lfs_dir_close(&real_filesystem, &dir);
}

static uint32_t cluster_size(void) {
    uint64_t storage_size = littlefs_lfs_config->block_count * littlefs_lfs_config->block_size;
    return storage_size / (DISK_SECTOR_SIZE * 1);
}

static size_t fat_sector_size(void) {
    return ceil((double)cluster_size() / DISK_SECTOR_SIZE);
}

static bool is_fat_sector(uint32_t sector) {
    return sector > 0 && fat_sector_size() >= sector;
}

size_t mimic_fat_total_sector_size(void) {
    uint64_t storage_size = littlefs_lfs_config->block_count * littlefs_lfs_config->block_size;
    return (double)storage_size / DISK_SECTOR_SIZE;
}

/*
 * Returns the boot sector of the FAT image when USB requests sector 0
 */
static void read_boot_sector(void *buffer, uint32_t bufsize) {
    TRACE("\e[36mRead read_boot_sector()\e[0m\n");

    // BPB_TotSec16
    fat_disk_image[0][19] = (uint8_t)(mimic_fat_total_sector_size() & 0xFF);
    fat_disk_image[0][20] = (uint8_t)(mimic_fat_total_sector_size() >> 8);

    // BPB_FATSz16
    size_t fat_size = ceil((double)mimic_fat_total_sector_size() / DISK_SECTOR_SIZE);
    fat_disk_image[0][22] = fat_size & 0xFF;
    fat_disk_image[0][23] = (fat_size & 0xFF00) >> 8;

    uint8_t const *addr = fat_disk_image[0];
    memcpy(buffer, addr, bufsize);
}

/*
 * Return the FAT table when USB requests sector 1.
 * Build a FAT table based on littlefs files.
 */
static void read_fat_sector(uint32_t sector, void *buffer, uint32_t bufsize) {
    (void)bufsize;
    TRACE("\e[36mRead sector=%lu read_fat_sector()\e[0m\n", sector);

    lfs_soff_t offset = (sector - 1) * 512;
    lfs_soff_t o = lfs_file_seek(&real_filesystem, &fat_cache, offset, LFS_SEEK_SET);
    if (o < 0) {
        printf("read_fat_sector: lfs_file_seek err=%ld\n", o);
        return;
    }

    lfs_ssize_t s = lfs_file_read(&real_filesystem, &fat_cache, buffer, bufsize);
    if (s < 0) {
        printf("read_fat_sector: lfs_file_read error=%ld\n", s);
    }
}

static void save_fat_sector(uint32_t request_block, void *buffer, size_t bufsize) {
    size_t offset = (request_block - 1) * bufsize;
    lfs_soff_t o = lfs_file_seek(&real_filesystem, &fat_cache, offset, LFS_SEEK_SET);
    if (o < 0) {
        printf("save_fat_sector: lfs_file_seek error=%ld\n", o);
        return;
    }
    lfs_ssize_t s = lfs_file_write(&real_filesystem, &fat_cache, buffer, bufsize);
    if (s != (lfs_ssize_t)bufsize) {
        printf("save_fat_sector: lfs_file_read error=%ld\n", s);
    }
}

/*
 * Restore the *result_filename of the file_cluster_id file belonging to directory_cluster_id.
 */
static void restore_file_from(char *result_filename, uint32_t directory_cluster_id, uint32_t file_cluster_id) {
    TRACE("restore_file_from(directory_cluster_id=%lu, file_cluster_id=%lu)\n", directory_cluster_id, file_cluster_id);
    assert(file_cluster_id >= 2);

    if (directory_cluster_id == 0) {
        directory_cluster_id = 1;
    }

    int cluster_id = directory_cluster_id;
    int parent = 1;
    int target = file_cluster_id;

    fat_dir_entry_t dir[16];
    uint8_t result[LFS_NAME_MAX * 2 + 1 + 1] = {0}; // for sprintf "%s/%s"
    if (directory_cluster_id == 0 && file_cluster_id == 0) {
        TRACE("  this is initial cluster\n");
        //return;
    }

    uint32_t self = 0;
    while (cluster_id >= 0) {
        TRACE("restore_file_from: cluster_id=%u, parent=%u, target=%u\n", cluster_id, parent, target);
        if ((cluster_id == 0 || cluster_id == 1) && read_temporary_file(1, &dir[0]) != 0) {
            printf("temporary file '.mimic/%04d' not found\n", 1);
            break;
        } else if (read_temporary_file(cluster_id, &dir[0]) != 0) {
            printf("temporary file '.mimic/%04d' not found\n", cluster_id);
            break;
        }

        //printf("restore_file_from---\n");
        //print_dir_entry(&dir);
        //printf("--------------------\n");
        uint8_t child_filename[LFS_NAME_MAX + 1];
        char filename[LFS_NAME_MAX + 1];
        uint16_t long_filename[LFS_NAME_MAX + 1];
        bool is_long_filename = false;
        for (int i = 0; i < 16; i++) {
            if (dir[i].DIR_Attr == 0x08) {
                parent = -1;
                continue;
            }
            if (dir[i].DIR_Name[0] == '\0') {
                break;
            }
            if (memcmp(dir[i].DIR_Name, ".          ", 11) == 0) {
                self = dir[i].DIR_FstClusLO;
                continue;
            }
            if (memcmp(dir[i].DIR_Name, "..         ", 11) == 0) {
                parent = dir[i].DIR_FstClusLO;
                if (parent == 0) {
                    /* NOTE: According to the FAT specification, the reference to the root
                     * directory is `cluster==0`, but the actual state of the root directory
                     * is `cluster==1`, so it needs to be corrected.
                     */
                    parent = 1;  // Actual root directory
                }
                continue;
            }
            if (dir[i].DIR_Name[0] == 0xE5)
                continue;

            if ((dir[i].DIR_Attr & 0x0F) == 0x0F) {
                fat_lfn_t *long_file = (fat_lfn_t *)&dir[i];
                if (long_file->LDIR_Ord & 0x40) {
                    memset(long_filename, 0xFF, sizeof(long_filename));
                    is_long_filename = true;
                }
                int offset = (long_file->LDIR_Ord & 0x0F) - 1;
                memcpy(&long_filename[offset * 13 + 0], long_file->LDIR_Name1, sizeof(uint16_t) * 5);
                memcpy(&long_filename[offset * 13 + 5], long_file->LDIR_Name2, sizeof(uint16_t) * 6);
                memcpy(&long_filename[offset * 13 + 5 + 6], long_file->LDIR_Name3, sizeof(uint16_t) * 2);
                continue;
            }

            if (dir[i].DIR_Attr & 0x10) { // is directory
                if (is_long_filename) {
                    utf16le_to_utf8(filename, sizeof(filename), long_filename, sizeof(long_filename));
                } else {
                    restore_from_short_dirname(filename, (const char *)dir[i].DIR_Name);
                }

                if (dir[i].DIR_FstClusLO == target) {
                    strcpy((char *)child_filename, (const char *)result);
                    snprintf((char *)result, sizeof(result), "%s/%s", filename, child_filename);
                    result[LFS_NAME_MAX] = '\0';
                    break;
                }

                is_long_filename = false;
                continue;
            } else if (dir[i].DIR_Attr & 0x20 || dir[i].DIR_Attr == 0x00) { // is file
                if (is_long_filename) {
                    utf16le_to_utf8(filename, sizeof(filename), long_filename, sizeof(long_filename));
                } else {
                    restore_from_short_filename(filename, (const char *)dir[i].DIR_Name);
                }

                if (dir[i].DIR_FstClusLO == target) {
                    strcpy((char *)result, (const char *)filename);
                    target = cluster_id;
                    break;

                }
                is_long_filename = false;
            } else {
                TRACE("  unknown DIR_Attr=0x%02X\n", dir[i].DIR_Attr);
            }
        }

        cluster_id = parent;
        target = self;
    }

    strncpy((char *)result_filename, (const char *)result, LFS_NAME_MAX);
    result_filename[LFS_NAME_MAX] = '\0';
}


/*
 * Cache the results of the last search in case of reading large files.
 */
typedef struct {
    uint32_t cluster;
    uint32_t base_cluster;
    size_t offset;
} find_base_cluster_and_offset_cache_t;

static find_base_cluster_and_offset_cache_t base_cluster_cache = {0};
/*
 * Search for base cluster in the Allocation table
 *
 * Traverse the allocation table in reverse order and return the length of the allocation chain in offset.
 */
static uint32_t find_base_cluster_and_offset(uint32_t cluster, size_t *offset) {
    uint32_t target = cluster;
    uint32_t next_cluster;
    bool is_exists = false;
    uint32_t find_limit = cluster_size();

    if (cluster > cluster_size()) {
        return 0;
    }
    if (read_fat(cluster) == 0x00) {
        return 0;
    }

    // reset search cache
    if (base_cluster_cache.cluster + 1 != cluster) {
        base_cluster_cache.cluster = 0;
        base_cluster_cache.base_cluster = 0;
        base_cluster_cache.offset = 0;
    }

    *offset = 0;
    while (find_limit-- > 0) {
        is_exists = false;
        for (size_t i = 0; i < cluster_size(); i++) {
            next_cluster = read_fat(i);
            if (next_cluster >= 0xFF8 || next_cluster == 0x00)
                continue;
            if (next_cluster == cluster) {
                cluster = i;  // i is the cluster number cvhained to cluster
                is_exists = true;
                *offset += 1;

                if (base_cluster_cache.cluster == i) {
                    *offset += base_cluster_cache.offset;
                    base_cluster_cache.cluster = next_cluster;
                    base_cluster_cache.offset = *offset;
                    return base_cluster_cache.base_cluster;
                }

                break;
            }
        }
        if (!is_exists)
            break;
    }
    base_cluster_cache.cluster = target;
    base_cluster_cache.base_cluster = cluster;
    base_cluster_cache.offset = *offset;

    return cluster;
}

typedef struct {
    bool is_found;
    uint32_t directory_cluster;
    bool is_directory;
    char path[LFS_NAME_MAX + 1];
    size_t size;
} find_dir_entry_cache_result_t;

/*
 * Restore directory_cluster_id filename to *directory
 */
static void restore_directory_from(char *directory, uint32_t base_directory_cluster_id, uint32_t directory_cluster_id) {
    int cluster_id = base_directory_cluster_id;
    int parent = 0;
    int target = directory_cluster_id;

    fat_dir_entry_t dir[16];
    uint8_t result[LFS_NAME_MAX * 2 + 1 + 1] = {0};  // for sprintf "%s/%s"

    while (cluster_id >= 0) {
        if ((cluster_id == 0 || cluster_id == 1) && read_temporary_file(1, &dir[0]) != 0) {
            TRACE("temporary file '.mimic/%04d' not found\n", 1);
            break;

        } else if (read_temporary_file(cluster_id, &dir[0]) != 0) {
            TRACE("temporary file '.mimic/%04d' not found\n", cluster_id);
            break;
        }

        uint8_t child_filename[LFS_NAME_MAX + 1];
        char filename[LFS_NAME_MAX + 1];
        uint16_t long_filename[LFS_NAME_MAX + 1];

        bool is_long_filename = false;
        for (int i = 0; i < 16; i++) {
            if (dir[i].DIR_Attr == 0x08) {
                parent = -1;
                continue;
            }
            if (dir[i].DIR_Name[0] == '\0') {
                break;
            }
            if (memcmp(dir[i].DIR_Name,    ".          ", 11) == 0) {
                continue;
            }
            if (memcmp(dir[i].DIR_Name, "..         ", 11) == 0) {
                /* NOTE: According to the FAT specification, the reference to the root
                 * directory is `cluster==0`, but the actual state of the root directory
                 * is `cluster==1`, so it needs to be corrected.
                 */
                parent = dir[i].DIR_FstClusLO != 0 ? dir[i].DIR_FstClusLO : 1;
                continue;
            }
            if (dir[i].DIR_Name[0] == 0xE5)
                continue;

            if ((dir[i].DIR_Attr & 0x0F) == 0x0F) {
                fat_lfn_t *long_file = (fat_lfn_t *)&dir[i];
                if (long_file->LDIR_Ord & 0x40) {
                    memset(long_filename, 0xFF, sizeof(long_filename));
                    is_long_filename = true;
                }
                int offset = (long_file->LDIR_Ord & 0x0F) - 1;
                memcpy(&long_filename[offset * 13 + 0], long_file->LDIR_Name1, sizeof(uint16_t) * 5);
                memcpy(&long_filename[offset * 13 + 5], long_file->LDIR_Name2, sizeof(uint16_t) * 6);
                memcpy(&long_filename[offset * 13 + 5 + 6], long_file->LDIR_Name3, sizeof(uint16_t) * 2);
                continue;
            }
            if (dir[i].DIR_Attr & 0x10) { // is directory
                if (is_long_filename) {
                    utf16le_to_utf8(filename, sizeof(filename), long_filename, sizeof(long_filename));
                } else {
                    restore_from_short_dirname(filename, (const char *)dir[i].DIR_Name);
                }

                if (dir[i].DIR_FstClusLO == target) {
                    strcpy((char *)child_filename, (const char *)result);
                    if (strlen((const char *)child_filename) == 0)
                        strncpy((char *)result, (const char *)filename, sizeof(result));
                    else
                        snprintf((char *)result, sizeof(result), "%s/%s", filename, child_filename);
                    result[LFS_NAME_MAX] = '\0';

                    target = cluster_id;
                    break;
                }

                is_long_filename = false;
                continue;
            } else {
                is_long_filename = false;
            }
        }

        cluster_id = parent;
    }

    strncpy((char *)directory, (const char *)result, LFS_NAME_MAX);
    directory[LFS_NAME_MAX] = '\0';
}

typedef enum find_dir_entry_cache_return_t {
    FIND_DIR_ENTRY_CACHE_RESULT_ERROR = -1,
    FIND_DIR_ENTRY_CACHE_RESULT_NOT_FOUND = 0,
    FIND_DIR_ENTRY_CACHE_RESULT_FOUND = 1,
} find_dir_entry_cache_return_t;

static find_dir_entry_cache_return_t find_dir_entry_cache(find_dir_entry_cache_result_t *result, uint32_t base_cluster, uint32_t target_cluster) {
    TRACE("find_dir_entry_cache(base=%lu, target=%lu)\n", base_cluster, target_cluster);
    fat_dir_entry_t entry[16];

    int err = read_temporary_file(base_cluster, entry);
    if (err != LFS_ERR_OK) {
        TRACE("find_dir_entry_cache: read_temporary_file(cluster=%lu) error=%d\n", base_cluster, err);
        return FIND_DIR_ENTRY_CACHE_RESULT_ERROR;
    }

    for (int i = (base_cluster == 1 ? 1 : 2); i < 16; i++) {
        if (strncmp((const char *)entry[i].DIR_Name, "..         ", 11) == 0)
            continue;
        if (entry[i].DIR_Name[0] == 0xE5)
            continue;
        if (entry[i].DIR_Name[0] == 0)
            break;

        if (entry[i].DIR_FstClusLO == target_cluster) {
            result->is_found = true;
            result->directory_cluster = base_cluster;
            result->is_directory = (entry[i].DIR_Attr & 0x10) ? true : false;
            result->size = entry[i].DIR_FileSize;
            if (result->is_directory)
                restore_directory_from(result->path, base_cluster, target_cluster);
            else
                restore_file_from(result->path, base_cluster, target_cluster);
            return FIND_DIR_ENTRY_CACHE_RESULT_FOUND;
        }
        if ((entry[i].DIR_Attr & 0x10) == 0)
            continue;

        find_dir_entry_cache_return_t r = find_dir_entry_cache(result, entry[i].DIR_FstClusLO, target_cluster);
        if (r != FIND_DIR_ENTRY_CACHE_RESULT_NOT_FOUND)
            return r;
    }
    return FIND_DIR_ENTRY_CACHE_RESULT_NOT_FOUND;
}

static void create_blank_dir_entry_cache(uint32_t cluster, uint32_t parent_dir_cluster) {
    fat_dir_entry_t entry[16] = {0};

    set_directory_entry(&entry[0], ".", cluster);
    set_directory_entry(&entry[1], "..", parent_dir_cluster == 1 ? 0 : parent_dir_cluster);

    save_temporary_file(cluster, entry);
}

/*
 */
void mimic_fat_read(uint8_t lun, uint32_t sector, void *buffer, uint32_t bufsize) {
    TRACE("\e[36mRead sector=%lu mimic_fat_read()\e[0m\n", sector);
    (void)lun;

    if (sector == 0) {
        read_boot_sector(buffer, bufsize);
        return;
    } else if (is_fat_sector(sector)) {
        read_fat_sector(sector, buffer, bufsize);
        return;
    }

    uint32_t cluster = sector - fat_sector_size();
    size_t offset = 0;
    find_dir_entry_cache_result_t result = {0};

    if (cluster == 1) {
        read_temporary_file(cluster, buffer);
        return;
    }

    uint32_t base_cluster = find_base_cluster_and_offset(cluster, &offset);
    if (base_cluster == 0) { // is not allocated
        return;
    }

    find_dir_entry_cache_return_t r = find_dir_entry_cache(&result, 1, base_cluster);
    if (r != FIND_DIR_ENTRY_CACHE_RESULT_FOUND)
        return;
    if (result.is_directory) {
        read_temporary_file(cluster, buffer);
        return;
    }

    TRACE("mimic_fat_read: result.path='%s'\n", result.path);

    lfs_file_t f;
    int err = lfs_file_open(&real_filesystem, &f, result.path, LFS_O_RDONLY);
    if (err != LFS_ERR_OK) {
        printf("mimic_fat_read_cluster: lfs_file_open('%s') error=%d\n", result.path, err);
        return;
    }

    lfs_soff_t seek = lfs_file_seek(&real_filesystem, &f, offset * DISK_SECTOR_SIZE, LFS_SEEK_SET);
    if (seek < 0) {
        printf("mimic_fat_read: lfs_file_seek(path='%s', offset=%u) error=%ld\n", result.path, offset * DISK_SECTOR_SIZE, seek);
    }
    lfs_ssize_t size = lfs_file_read(&real_filesystem, &f, buffer, bufsize);
    if (size < 0) {
        printf("mimic_fat_read: lfs_file_read(path='%s', offset=%u) error=%ld\n", result.path, offset, seek);
    }
    lfs_file_close(&real_filesystem, &f);
}

static void difference_of_dir_entry(fat_dir_entry_t *orig, fat_dir_entry_t *new,
                                    fat_dir_entry_t *update,
                                    fat_dir_entry_t *delete)
{
    bool is_found = false;
    TRACE("difference_of_dir_entry-----\n");
    print_dir_entry(orig);
    TRACE("----------------------------\n");
    print_dir_entry(new);
    TRACE("----------------------------\n");

    if (memcmp(orig, new, sizeof(fat_dir_entry_t) * 16) == 0) {
        return;
    }

    for (int i = 0; i < 16; i++) {
        if (strncmp((const char *)new[i].DIR_Name, ".          ", 11) == 0
            || strncmp((const char *)new[i].DIR_Name, "..         ", 11) == 0
            || (new[i].DIR_Attr & 0x0F) == 0x0F
            || (new[i].DIR_Attr & 0x08) == 0x08) // volume label
        {
            continue;
        }

        if (new[i].DIR_Name[0] == 0xE5) {
            for (int j = 0; j < 16; j++) {
                if ((orig[j].DIR_Attr & 0x08) == 0x08) // volume label
                    continue;
                if (new[i].DIR_FstClusLO == orig[j].DIR_FstClusLO
                    && new[i].DIR_FileSize == orig[j].DIR_FileSize
                    && orig[j].DIR_Name[0] != 0xE5
                    && new[i].DIR_FileSize != 0)
                {
                    // `delete` or `rename`.
                    memcpy(delete, &orig[j], sizeof(fat_dir_entry_t));
                    delete++;
                    break;
                }

                if (orig[j].DIR_Attr & 0x10  // directory
                    && new[i].DIR_FstClusLO == orig[j].DIR_FstClusLO
                    && new[i].DIR_FileSize == 0
                    && orig[j].DIR_Name[0] != 0xE5
                    && i == j)
                {
                    // `delete` or `rename`.
                    memcpy(delete, &orig[j], sizeof(fat_dir_entry_t));
                    delete++;
                    break;
                }
            }
            continue;
        }

        is_found = false;
        for (int j = 0; j < 16; j++) {
            if (new[i].DIR_Name[0] == 0xE5
               || strncmp((const char *)orig[j].DIR_Name, ".          ", 11) == 0
               || strncmp((const char *)orig[j].DIR_Name, "..         ", 11) == 0
               || (orig[j].DIR_Attr & 0x0F) == 0x0F
               || (orig[j].DIR_Attr & 0x08) == 0x08)  // volume label
            {
                continue;
            }

            if (strncmp((const char *)new[i].DIR_Name, (const char *)orig[j].DIR_Name, 11) == 0 &&
                new[i].DIR_FstClusLO == orig[j].DIR_FstClusLO &&
                new[i].DIR_FileSize == orig[j].DIR_FileSize)
            {
                is_found = true;
                break;
            }

            // rename
            if (i == j &&
                new[i].DIR_FstClusLO == orig[j].DIR_FstClusLO &&
                new[i].DIR_FileSize == orig[j].DIR_FileSize)
            {
                memcpy(delete, &orig[j], sizeof(fat_dir_entry_t));
                delete++;
                break;
            }
        }
        if (!is_found) {
            memcpy(update, &new[i], sizeof(fat_dir_entry_t));
            update++;
        }
    }
}

static int littlefs_mkdir(const char *filename) {
    TRACE(ANSI_RED "littlefs_mkdir('%s')\n" ANSI_CLEAR, filename);
    struct lfs_info finfo;

    int err = lfs_stat(&real_filesystem, filename, &finfo);
    if (err == LFS_ERR_OK) {
        return LFS_ERR_OK;
    }

    err = lfs_mkdir(&real_filesystem, filename);
    if (err != LFS_ERR_OK && err != LFS_ERR_EXIST) {
        TRACE("littlefs_mkdir: lfs_mkdir err=%d\n", err);
        return err;
    }

    return LFS_ERR_OK;
}

static int littlefs_write(const char *filename, uint32_t cluster, size_t size) {
    TRACE(ANSI_RED "littlefs_write('%s', cluster=%lu, size=%u)\n" ANSI_CLEAR, filename, cluster, size);

    uint8_t buffer[512];

    if (strlen(filename) == 0) {
        printf(ANSI_RED "littlefs_write: filename not specified\n" ANSI_CLEAR);
        return -1;
    }

    lfs_file_t f;
    int err = lfs_file_open(&real_filesystem, &f, filename, LFS_O_RDWR|LFS_O_CREAT);
    if (err != LFS_ERR_OK) {
        TRACE("littlefs_write: lfs_file_open error=%d\n", err);
        return err;
    }

    while (true) {
        err = read_temporary_file(cluster, buffer);
        if (err != LFS_ERR_OK) {
            TRACE("littlefs_write: read_temporary_file error=%d\n", err);
            lfs_file_close(&real_filesystem, &f);
            return err;
        }
        size_t s = lfs_file_write(&real_filesystem, &f, buffer, sizeof(buffer));
        if (s != 512) {
            TRACE("littlefs_write: lfs_file_write, %u < %u\n", s, 512);
            lfs_file_close(&real_filesystem, &f);
            return -1;
        }
        int next_cluster = read_fat(cluster);
        if (next_cluster == 0x00) // not allocated
            break;
        if (next_cluster >= 0xFF8)  // eof
            break;
        cluster = next_cluster;
    }
    err = lfs_file_truncate(&real_filesystem, &f, size);
    if (err != LFS_ERR_OK) {
        TRACE("littlefs_write: lfs_file_truncate err=%d\n", err);
        lfs_file_close(&real_filesystem, &f);
        return err;
    }
    lfs_file_close(&real_filesystem, &f);
    return 0;
}

static int littlefs_remove(const char *filename) {
    TRACE(ANSI_RED "littlefs_remove('%s')\n" ANSI_CLEAR, filename);

    if (strlen(filename) == 0) {
        TRACE("littlefs_remove: not allow brank filename\n");
        return LFS_ERR_INVAL;
    }
    int err = lfs_remove(&real_filesystem, filename);
    if (err != LFS_ERR_OK) {
        TRACE("littlefs_remove: lfs_remove: err=%d\n", err);
        return err;
    }

    return LFS_ERR_OK;
}

/*
 * Update a file or directory from the difference indicated by *src in dir_cluster_id
 *
 * *src is an array of differences created by diff_dir_entry()
 */
static void update_lfs_file_or_directory(fat_dir_entry_t *src, uint32_t dir_cluster_id) {
    TRACE("update_lfs_file_or_directory(dir_cluster_id=%lu)\n", dir_cluster_id);
    char filename[LFS_NAME_MAX + 1];
    char directory[LFS_NAME_MAX + 1];
    uint16_t long_filename[LFS_NAME_MAX + 1] = {0};

    strcpy(directory, "");

    bool is_long_filename = false;
    for (int i = 0; i < 16; i++) {
        fat_dir_entry_t *dir = &src[i];
        if (dir->DIR_Name[0] == '\0')
            break;
        if (dir->DIR_Name[0] == 0xE5 || dir->DIR_Name[0] == 0x05)
            continue;
        if (memcmp(dir->DIR_Name, "..         ", 11) == 0)
            continue;
        if (memcmp(dir->DIR_Name, ".          ", 11) == 0)
            continue;

        if ((dir->DIR_Attr & 0x0F) == 0x0F) {
            fat_lfn_t *long_file = (fat_lfn_t *)dir;
            if (long_file->LDIR_Ord & 0x40) {
                memset(long_filename, 0xFF, sizeof(long_filename));
                is_long_filename = true;
            }
            int offset = (long_file->LDIR_Ord & 0x0F) - 1;
            memcpy(&long_filename[offset * 13], long_file->LDIR_Name1, sizeof(uint16_t) * 5);
            memcpy(&long_filename[offset * 13 + 5], long_file->LDIR_Name2, sizeof(uint16_t) * 6);
            memcpy(&long_filename[offset * 13 + 5 + 6], long_file->LDIR_Name3, sizeof(uint16_t) * 2);
            continue;
        }
        if (dir->DIR_Attr & 0x10) { // is directory
            if (is_long_filename) {
                utf16le_to_utf8(filename, sizeof(filename), long_filename, sizeof(long_filename));
            } else {
                restore_from_short_dirname(filename, (const char *)dir->DIR_Name);
            }
            // FIXME: If there is a directory to be deleted with the same name,
            //        the files in the directory must be copied.
            restore_directory_from(directory, dir_cluster_id, dir->DIR_FstClusLO);
            littlefs_mkdir(directory);
            create_blank_dir_entry_cache(dir->DIR_FstClusLO, dir_cluster_id);

            is_long_filename = false;

            continue;
        } else if (dir->DIR_Attr & 0x20 || dir->DIR_Attr == 0x00) { // is file
            if (is_long_filename) {
                utf16le_to_utf8(filename, sizeof(filename), long_filename, sizeof(long_filename));
            } else {
                restore_from_short_filename(filename, (const char *)dir->DIR_Name);
            }

            if (dir->DIR_FstClusLO == 0) {
                TRACE(" Files not yet assigned cluster=0\n");
                break;
            }

            restore_file_from(filename, dir_cluster_id,  dir->DIR_FstClusLO);
            littlefs_write((const char *)filename, dir->DIR_FstClusLO, dir->DIR_FileSize);
            is_long_filename = false;
            continue;
        } else {
            TRACE(" unknown DIR_Attr = 0x%02X\n", dir->DIR_Attr);
        }
        is_long_filename = false;
    }
}

/*
 * Save the contents of real file system filename in the cluster cache
 */
static void save_file_clusters(uint32_t cluster, const char *filename) {
    TRACE("save_file_clusters(cluster=%lu, '%s')\n", cluster, filename);

    uint8_t buffer[DISK_SECTOR_SIZE] = {0};
    uint32_t next_cluster = cluster;
    lfs_file_t f;

    int err = lfs_file_open(&real_filesystem, &f, filename, LFS_O_RDONLY);
    if (err != LFS_ERR_OK) {
        printf("save_file_clusters: lfs_file_open('%s') error=%d\n", filename, err);
        return;
    }

    lfs_soff_t seek_pos;
    lfs_ssize_t read_bytes;
    int offset = 0;
    while (next_cluster < 0xFF8) {
        next_cluster = read_fat(cluster);

        seek_pos = lfs_file_seek(&real_filesystem, &f, offset * DISK_SECTOR_SIZE, LFS_SEEK_SET);
        if (seek_pos < 0) {
            printf("save_file_clusters: lfs_file_seek(%u) failed: error=%ld\n",
                offset * DISK_SECTOR_SIZE, seek_pos);
            break;
        }
        read_bytes = lfs_file_read(&real_filesystem, &f, buffer, sizeof(buffer));
        if (read_bytes < 0) {
            printf("save_file_clusters: lfs_file_read() error=%ld\n", read_bytes);
            break;
        }
        save_temporary_file(cluster, buffer);
        cluster = next_cluster;
        offset++;
    }

    lfs_file_close(&real_filesystem, &f);
}

static void delete_dir_entry_cache(fat_dir_entry_t *src, uint32_t dir_cluster_id) {
    char filename[LFS_NAME_MAX + 1];

    for (int i = 0; i < 16; i++) {
        fat_dir_entry_t *dir = &src[i];
        if (dir->DIR_Name[0] == '\0')
            break;

        if (dir->DIR_Attr & 0x10) {
            restore_directory_from(filename, dir_cluster_id, dir->DIR_FstClusLO);
        } else {
            restore_file_from(filename, dir_cluster_id, dir->DIR_FstClusLO);
            save_file_clusters(dir->DIR_FstClusLO, filename);
        }
        littlefs_remove(filename);

        // Cluster cache is needed at the rename destination, so do not delete it.
        /*
        uint32_t next_cluster = dir->DIR_FstClusLO;
        while (true) {
            delete_temporary_file(next_cluster);
            next_cluster = read_fat(next_cluster);
            if (next_cluster >= 0xFF8) {
                break;
            }
        }
        */
        continue;
    }
}

static void update_dir_entry(uint32_t cluster, void *buffer) {
    fat_dir_entry_t orig[16] = {0};
    fat_dir_entry_t *new = buffer;
    fat_dir_entry_t dir_update[16] = {0};
    fat_dir_entry_t dir_delete[16] = {0};

    if (read_temporary_file(cluster, orig) != 0) {
        printf("update_dir_entry: entry not found cluster=%lu\n", cluster);
        return;
    }

    difference_of_dir_entry(orig, new, dir_update, dir_delete);
    delete_dir_entry_cache(dir_delete, cluster);

    save_temporary_file(cluster, buffer);
    update_lfs_file_or_directory(dir_update, cluster);
}

/*
 * Save request_blocks not associated with a resource in a temporary file
 */
static void update_file_entry(uint32_t cluster, void *buffer, uint32_t bufsize,
                              find_dir_entry_cache_result_t *result, size_t offset)
{
    save_temporary_file(cluster, buffer);
    if (!result->is_found)
        return;

    TRACE(ANSI_RED "lfs_file_open('%s', cluster=%lu, offset=%u)\n" ANSI_CLEAR, result->path, cluster, offset);
    lfs_file_t f;
    int err;
    if (offset == 0) {
        err = lfs_file_open(&real_filesystem, &f, result->path, LFS_O_WRONLY|LFS_O_CREAT|LFS_O_TRUNC);
        if (err != LFS_ERR_OK) {
            printf("update_file_entry: lfs_file_open('%s') error=%d\n", result->path, err);
            return;
        }
    } else {
        err = lfs_file_open(&real_filesystem, &f, result->path, LFS_O_WRONLY);
        if (err != LFS_ERR_OK) {
            printf("update_file_entry: lfs_file_open('%s') error=%d\n", result->path, err);
            return;
        }
        lfs_file_seek(&real_filesystem, &f, offset * DISK_SECTOR_SIZE, LFS_SEEK_SET);
    }

    lfs_ssize_t size = lfs_file_write(&real_filesystem, &f, buffer, bufsize);
    if (size < 0 || size != 512) {
        printf("update_file_entry: lfs_file_write('%s') error=%ld\n", result->path, size);
        lfs_file_close(&real_filesystem, &f);
        return;
    }

    if ((1 + offset) * 512 >= result->size) {
        err = lfs_file_truncate(&real_filesystem, &f, result->size);
        if (err != LFS_ERR_OK) {
            printf("update_file_entry: lfs_file_truncate('%s') error=%d\n", result->path, err);
            lfs_file_close(&real_filesystem, &f);
            return;
        }
    }
    err = lfs_file_close(&real_filesystem, &f);
    if (err != LFS_ERR_OK) {
        printf("update_file_entry: lfs_file_close('%s') error=%d\n", result->path, err);
        return;
    }
}

void mimic_fat_write(uint8_t lun, uint32_t request_block, void *buffer, uint32_t bufsize) {
    (void)lun;
    find_dir_entry_cache_result_t result;

    if (request_block == 0) // master boot record
        return;

    if (is_fat_sector(request_block)) { // FAT table
        TRACE("\e[35mWrite FAT table\n" ANSI_CLEAR);
        save_fat_sector(request_block, buffer, bufsize);
        return;
    }

    uint32_t cluster = request_block - fat_sector_size();
    TRACE("\e[35mWrite cluster=%lu\e[0m\n", cluster);
    if (cluster == 1) { // root dir entry
        TRACE("mimic_fat_write: update root dir_entry\n");

        fat_dir_entry_t orig[16] = {0};
        fat_dir_entry_t dir_update[16] = {0};
        fat_dir_entry_t dir_delete[16] = {0};

        read_temporary_file(cluster, orig);
        difference_of_dir_entry(&orig[0], (fat_dir_entry_t *)buffer, dir_update, dir_delete);

        delete_dir_entry_cache(dir_delete, cluster);

        save_temporary_file(cluster, buffer);
        save_temporary_file(0, buffer); // FIXME

        update_lfs_file_or_directory(dir_update, cluster);
    } else { // data or directory entry
        size_t offset = 0;
        uint32_t base_cluster = find_base_cluster_and_offset(cluster, &offset);

        if (base_cluster == 0) {
            TRACE("mimic_fat_write: not allocated cluster\n");
            save_temporary_file(cluster, buffer);

            // For hosts that write to unallocated space first
            find_dir_entry_cache_return_t r = find_dir_entry_cache(&result, 1, cluster);
            if (r != FIND_DIR_ENTRY_CACHE_RESULT_FOUND)  // error or not found
                return;
            if (result.is_found && !result.is_directory) {
                littlefs_write(result.path, cluster, result.size);
            }
            return;
        }

        find_dir_entry_cache_return_t r = find_dir_entry_cache(&result, 1, base_cluster);

        if (r == FIND_DIR_ENTRY_CACHE_RESULT_ERROR) {
            TRACE("mimic_fat_write: find_dir_entry_cache(1, base_cluster=%lu) error=%d\n",
                   base_cluster, r);
            return;
        }
        if (r == FIND_DIR_ENTRY_CACHE_RESULT_NOT_FOUND) {
            TRACE(ANSI_RED "find_dir_entry_cache not found cluster=%lu\n" ANSI_CLEAR, base_cluster);
            save_temporary_file(cluster, buffer);
            return;
        }

        if (result.is_directory)
            update_dir_entry(cluster, buffer);
        else
            update_file_entry(cluster, buffer, bufsize, &result, offset);
    }
}

/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if !defined(_FAT_DIRECTORY_ENTRY_H_)
#define _FAT_DIRECTORY_ENTRY_H_

#include "bootloader_common.h"
#include <wchar.h>

//! @addtogroup fat_dir_entry
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief FAT filesystem directory entry attributes.
enum _fat_directory_attributes
{
    kReadOnlyAttribute = 0x01,  //!< Read only.
    kHiddenAttribute = 0x02,    //!< Hidden.
    kSystemAttribute = 0x04,    //!< System.
    kVolumeIdAttribute = 0x08,  //!< Volume ID.
    kDirectoryAttribute = 0x10, //!< Directory.
    kArchiveAttribute = 0x20,   //!< Archive

    //! Attribute value to identify a long file name entry.
    kLongNameAttribute = kReadOnlyAttribute | kHiddenAttribute | kSystemAttribute | kVolumeIdAttribute,

    //! Marker flag for long name entry order field to indicate the final long name entry.
    kLastLongNameEntry = 0x40,

    //! The first name byte is set to this value to mark a directory entry as free.
    kFreeEntryMarkerByte = 0xe5
};

#pragma pack(push)
#pragma pack(1)
//! @brief FAT filesystem directory entry.
//!
//! This union can represent either a standard file or directory entry, or a long file name entry.
//!
//! The upper 2 bits of the attribute byte are reserved and should always be set to 0 when a
//! file is created and never modify or look at it after that.
//!
//! The ntReserved field must be set to 0 when file is created and never modified or look at it after that.
//!
//! The creationTimeTenths field actually contains a count of tenths of a second. The granularity
//! of the seconds part of the creationTime is two seconds so this field is a count of tenths of a
//! second and its valid value range is 0-199 inclusive.
//!
//! Note that there is no last access time, only a date. This is the date of last read or
//! write. In the case of a write, this should be set to the same date as DIR_WrtDate.
//!
//! The firstClusterHigh field will always be 0 for a FAT12 or FAT16 volume.
//!
//! Note that file creation is considered a write.
typedef union FatDirectoryEntry
{
    //! Standard file or directory entry with a short name.
    struct
    {
        uint8_t name[11];           //!< Short file name.
        uint8_t attributes;         //!< File attributes.
        uint8_t ntReserved;         //!< Reserved.
        uint8_t creationTimeTenths; //!< Millisecond stamp at file creation time.
        uint16_t creationTime;      //!< Time file was created.
        uint16_t creationDate;      //!< Date file was created.
        uint16_t lastAccessDate;    //!< Last access date.
        uint16_t firstClusterHigh;  //!< High two bytes of this entry's first cluster number.
        uint16_t writeTime;         //!< Time of last write.
        uint16_t writeDate;         //!< Date of last write.
        uint16_t firstClusterLow;   //!< Low two bytes of this entry's first cluster number.
        uint32_t fileSize;          //!< This file's size in bytes.
    } entry;
    //! Long file name directory entry.
    struct
    {
        uint8_t order;            //!< Order of this long file name entry. May be masked with #kLastLongNameEntry.
        wchar_t name1[5];         //!< Characters 1-5 of the long name.
        uint8_t attributes;       //!< Must be set to #kLongNameAttribute.
        uint8_t entryType;        //!< Should be 0 for long file name directory entries.
        uint8_t checksum;         //!< Checksum of the short file name.
        wchar_t name2[6];         //!< Characters 6-11 of the long name.
        uint16_t firstClusterLow; //!< Must be set to 0 for compatibility.
        wchar_t name3[2];         //!< Character 12-13 of the long name.
    } longName;
} fat_directory_entry_t;
#pragma pack(pop)

//! @brief Macro to help build a standard directory entry.
#define MAKE_FAT_VOLUME_LABEL(c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, t, d)           \
    {                                                                                       \
        .entry = {                                                                          \
            .name = { (c1), (c2), (c3), (c4), (c5), (c6), (c7), (c8), (c9), (c10), (c11) }, \
            .attributes = kVolumeIdAttribute,                                               \
            .writeTime = (t),                                                               \
            .writeDate = (d),                                                               \
        }                                                                                   \
    }

//! @brief Macro to help build a standard directory entry.
//!
//! Creation, last access, and write times/dates are all set to the same value.
//!
//! @param c1-c11 Characters of the file/directory name in 8.3 format.
//! @param a Attribute value.
//! @param t Time value.
//! @param d Date value.
//! @param cluster First cluster low. The first cluster high is set to 0.
//! @param s File size in bytes.
#define MAKE_FAT_DIR_ENTRY(c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, a, t, d, cluster, s)     \
    {                                                                                             \
        .entry = {.name = { (c1), (c2), (c3), (c4), (c5), (c6), (c7), (c8), (c9), (c10), (c11) }, \
                  .attributes = (a),                                                              \
                  .creationTime = (t),                                                            \
                  .creationDate = (d),                                                            \
                  .lastAccessDate = (d),                                                          \
                  .writeTime = (t),                                                               \
                  .writeDate = (d),                                                               \
                  .firstClusterLow = (cluster),                                                   \
                  .fileSize = (s) }                                                               \
    }

//! @brief Macro to help build a long name directory entry.
//!
//! @param o The order number for this entry.
//! @param c1-c13 Thirteen UTF16 characters.
//! @param k Checksum over the short name.
//! @param l Pass #kLastLongNameEntry if this is the last long file entry, or 0 otherwise.
#define MAKE_FAT_LONG_NAME(o, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, k, l) \
    {                                                                                       \
        .longName = {.order = (o) | (l),                                                    \
                     .name1 = { (c1), (c2), (c3), (c4), (c5) },                             \
                     .attributes = kLongNameAttribute,                                      \
                     .checksum = (k),                                                       \
                     .name2 = { (c6), (c7), (c8), (c9), (c10), (c11) },                     \
                     .name3 = { (c12), (c13) } }                                            \
    }

//! @brief Construct a FAT date value.
//!
//! Bits 0–4: Day of month, valid value range 1-31 inclusive.<br/>
//! Bits 5–8: Month of year, 1 = January, valid value range 1–12 inclusive.<br/>
//! Bits 9–15: Count of years from 1980, valid value range 0–127 inclusive (1980–2107).
#define MAKE_FAT_DATE(d, m, y) ((uint16_t)(((((y)-1980) & 0x7f) << 9) | (((m)&0xf) << 5) | ((d)&0x1f)))

//! @brief Construct a FAT time value.
//!
//! Bits 0–4: 2-second count, valid value range 0–29 inclusive (0 – 58 seconds).<br/>
//! Bits 5–10: Minutes, valid value range 0–59 inclusive.<br/>
//! Bits 11–15: Hours, valid value range 0–23 inclusive.
#define MAKE_FAT_TIME(h, m, s) ((uint16_t)((((h)&0x1f) << 11) | (((m)&0x3f) << 5) | (((s) / 2) & 0x1f)))

//! @}

#endif // _FAT_DIRECTORY_ENTRY_H_
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

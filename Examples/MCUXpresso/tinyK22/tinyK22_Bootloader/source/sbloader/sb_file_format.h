/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if !defined(_SB_FILE_FORMAT_H_)
#define _SB_FILE_FORMAT_H_

#include "bootloader_common.h"

//! @addtogroup sb_file_format
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

#pragma pack(push)
#pragma pack(1)

//! @brief Flag constants for the m_flags field of #sb_image_header_t.
enum
{
    ROM_DISPLAY_PROGRESS = (1 << 0), //!< Print progress reports.
    ROM_VERBOSE_PROGRESS = (1 << 1)  //!< Progress reports are verbose.
};

//! @brief Version struct used in SB files.
typedef struct _sb_version
{
    uint16_t m_major;
    uint16_t m_pad0;
    uint16_t m_minor;
    uint16_t m_pad1;
    uint16_t m_revision;
    uint16_t m_pad2;
} sb_version_t;

//! @brief Header for the entire boot image.
//!
//! Fields of this header are arranged so that those used by the bootloader ROM all come
//! first. They are also set up so that all fields are not split across cipher block
//! boundaries. The fields not used by the bootloader are not subject to this
//! restraint.
//!
//! Image header size is always a round number of cipher blocks. The same also applies to
//! the boot image itself. The padding, held in #sb_image_header_t::m_padding0
//! and #sb_image_header_t::m_padding1 is filled with random bytes.
//!
//! The DEK dictionary, section table, and each section data region must all start on
//! cipher block boundaries.
//!
//! This header is not encrypted in the image file.
//!
//! The m_digest field contains a SHA-1 digest of the fields of the header that follow it.
//! It is the first field in the header so it doesn't change position or split the header
//! in two if fields are added to the header.
typedef struct _sb_image_header
{
    uint8_t m_digest[20];              // !< SHA-1 digest of image header. Also used as the crypto IV.
    uint32_t m_signature;              // !< 'STMP', see #BOOT_SIGNATURE.
    uint8_t m_majorVersion;            // !< Major version for the image format, see #SB_FILE_MAJOR_VERSION.
    uint8_t m_minorVersion;            // !< Minor version of the boot image format.
    uint16_t m_flags;                  // !< Flags or options associated with the entire image.
    uint32_t m_imageBlocks;            // !< Size of entire image in blocks.
    uint32_t m_firstBootTagBlock;      // !< Offset from start of file to the first boot tag, in blocks.
    uint32_t m_firstBootableSectionID; // !< ID of section to start booting from.
    uint16_t m_keyCount;               // !< Number of entries in DEK dictionary.
    uint16_t m_keyDictionaryBlock;     // !< Starting block number for the key dictionary.
    uint16_t m_headerBlocks;           // !< Size of this header, including this size word, in blocks.
    uint16_t m_sectionCount;           // !< Number of section headers in this table.
    uint16_t m_sectionHeaderSize;      // !< Size in blocks of a section header.
    uint8_t m_padding0[2];             // !< Padding to align #m_timestamp to long word.
    uint32_t
        m_signature2; // !< Second signature to distinguish this .sb format from the 36xx format, see #BOOT_SIGNATURE2.
    uint64_t m_timestamp;            // !< Timestamp when image was generated in microseconds since 1-1-2000.
    sb_version_t m_productVersion;   // !< Product version.
    sb_version_t m_componentVersion; // !< Component version.
    uint16_t m_driveTag;             // !< Drive tag for the system drive which this boot image belongs to.
    uint8_t m_padding1[6];           // !< Padding to round up to next cipher block.
} sb_image_header_t;

//! @brief Entry in #sb_dek_dictionary_t.
//!
//! The m_dek field in each entry is encrypted using the KEK with the m_iv field from
//! the image header as the IV.
typedef struct _sb_dek_dictionary_entry
{
    uint8_t m_mac[16]; //!< CBC-MAC of the header.
    uint8_t m_dek[16]; //!< AES-128 key with which the image payload is encrypted.
} sb_dek_dictionary_entry_t;

//! @brief The DEK dictionary always follows the image header, in the next cipher block.
typedef struct _sb_dek_dictionary
{
    sb_dek_dictionary_entry_t m_entries[1];
} sb_dek_dictionary_t;

//! @brief Section flags constants for the m_flags field of #sb_section_header_t.
enum
{
    ROM_SECTION_BOOTABLE = (1 << 0), //!< The section contains bootloader commands.
    ROM_SECTION_CLEARTEXT =
        (1 << 1) //!< The section is unencrypted. Applies only if the rest of the boot image is encrypted.
};

//! @brief Information about each section, held in the section table.
//! @see sb_section_table_t
typedef struct _sb_section_header
{
    uint32_t m_tag;    //!< Unique identifier for this section. High bit must be zero.
    uint32_t m_offset; //!< Offset to section data from start of image in blocks.
    uint32_t m_length; //!< Size of section data in blocks.
    uint32_t m_flags;  //!< Section flags.
} sb_section_header_t;

//! @brief An index of all sections within the boot image.
//!
//! The section table will be padded so that its length is divisible by 16 (if necessary).
//! Actually, each entry is padded to be a round number of cipher blocks, which
//! automatically makes this true for the entire table.
//!
//! Sections are ordered as they appear in this table, but are identified by the
//! #sb_section_header_t::m_tag.
//!
//! The data for each section in encrypted separately with the DEK in CBC mode using
//! m_iv for the IV. This allows the ROM to jump to any given section without needing
//! to read the previous cipher block. In addition, the data for each section is
//! prefixed with a "boot tag", which describes the section which follows it.
//!
//! The section table starts immediately after the image header, coming before the
//! key dictionary (if present). The section table is not encrypted.
typedef struct _sb_section_table
{
    sb_section_header_t m_sections[1]; //!< The table entries.
} sb_section_table_t;

#pragma pack(pop)

//! @}

#endif // _SB_FILE_FORMAT_H_
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

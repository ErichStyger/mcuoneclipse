/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _loader_h
#define _loader_h

#include <stdint.h>
#include "bootloader_common.h"
#include "crc/crc32.h"

//! @addtogroup sbloader
//! @{

#ifndef SB_FILE_MAJOR_VERSION
//! Defines boot image file version compatibility. Image files with the major
//! version less than or equal to this value will be loaded.
#define SB_FILE_MAJOR_VERSION 1
#endif

//! @brief SB loader status codes.
enum _sbloader_status
{
    kStatusRomLdrSectionOverrun = MAKE_STATUS(kStatusGroup_SBLoader, 0),
    kStatusRomLdrSignature = MAKE_STATUS(kStatusGroup_SBLoader, 1),
    kStatusRomLdrSectionLength = MAKE_STATUS(kStatusGroup_SBLoader, 2),
    kStatusRomLdrUnencryptedOnly = MAKE_STATUS(kStatusGroup_SBLoader, 3),
    kStatusRomLdrEOFReached = MAKE_STATUS(kStatusGroup_SBLoader, 4),
    kStatusRomLdrChecksum = MAKE_STATUS(kStatusGroup_SBLoader, 5),
    kStatusRomLdrCrc32Error = MAKE_STATUS(kStatusGroup_SBLoader, 6),
    kStatusRomLdrUnknownCommand = MAKE_STATUS(kStatusGroup_SBLoader, 7),
    kStatusRomLdrIdNotFound = MAKE_STATUS(kStatusGroup_SBLoader, 8),
    kStatusRomLdrDataUnderrun = MAKE_STATUS(kStatusGroup_SBLoader, 9),
    kStatusRomLdrJumpReturned = MAKE_STATUS(kStatusGroup_SBLoader, 10),
    kStatusRomLdrCallFailed = MAKE_STATUS(kStatusGroup_SBLoader, 11),
    kStatusRomLdrKeyNotFound = MAKE_STATUS(kStatusGroup_SBLoader, 12),
    kStatusRomLdrSecureOnly = MAKE_STATUS(kStatusGroup_SBLoader, 13),
    kStatusRomLdrResetReturned = MAKE_STATUS(kStatusGroup_SBLoader, 14),
    kStatusRomLdrRollbackBlocked = MAKE_STATUS(kStatusGroup_SBLoader, 15),
    kStatusRomLdrInvalidSectionMacCount = MAKE_STATUS(kStatusGroup_SBLoader, 16),
    kStatusRomLdrUnexpectedCommand = MAKE_STATUS(kStatusGroup_SBLoader, 17),
};

//! Defines the number of bytes in a cipher block (chunk). This is dictated by
//! the encryption algorithm.
#define BYTES_PER_CHUNK 16

//! Boot image signature in 32-bit little-endian format "PMTS"
#define BOOT_SIGNATURE 0x504d5453

//! Boot image signature in 32-bit little-endian format "ltgs"
#define BOOT_SIGNATURE2 0x6c746773

//! These define file header flags
#define FFLG_DISPLAY_PROGRESS 0x0001

//! These define section header flags
#define SFLG_SECTION_BOOTABLE 0x0001

//! These define boot command flags
#define CFLG_LAST_TAG 0x01

//! ROM_ERASE_CMD flags
#define ROM_ERASE_ALL_MASK 0x01
#define ROM_ERASE_ALL_UNSECURE_MASK 0x02

//! ROM_JUMP_CMD flags
#define ROM_JUMP_SP_MASK 0x02

//! Memory device id shift at sb command flags
#define ROM_MEM_DEVICE_ID_SHIFT 0x8

//! Memory device id mask
#define ROM_MEM_DEVICE_ID_MASK 0xff00

//! Memory group id shift at sb command flags
#define ROM_MEM_GROUP_ID_SHIFT 0x4

//! Memory group id flags mask
#define ROM_MEM_GROUP_ID_MASK 0xf0

//! ROM_PROG_CMD flags
#define ROM_PROG_8BYTE_MASK 0x01

//! These define the boot command tags
#define ROM_NOP_CMD 0x00
#define ROM_TAG_CMD 0x01
#define ROM_LOAD_CMD 0x02
#define ROM_FILL_CMD 0x03
#define ROM_JUMP_CMD 0x04
#define ROM_CALL_CMD 0x05
#define ROM_MODE_CMD 0x06
#define ROM_ERASE_CMD 0x07
#define ROM_RESET_CMD 0x08
#define ROM_MEM_ENABLE_CMD 0x09
#define ROM_PROG_CMD 0x0a

//! Plugin return codes
#define ROM_BOOT_SECTION_ID 1
#define ROM_BOOT_IMAGE_ID 2

typedef uint8_t chunk_t[BYTES_PER_CHUNK];

//! Boot command definition
typedef struct _boot_cmd
{
    uint8_t checksum; //!< 8-bit checksum over command chunk
    uint8_t tag;      //!< command tag (identifier)
    uint16_t flags;   //!< command flags (modifier)
    uint32_t address; //!< address argument
    uint32_t count;   //!< count argument
    uint32_t data;    //!< data argument
} boot_cmd_t;

//! Definition for boot image file header chunk 1
typedef struct _boot_hdr1
{
    uint32_t hash;       //!< last 32-bits of SHA-1 hash
    uint32_t signature;  //!< must equal "STMP"
    uint8_t major;       //!< major file format version
    uint8_t minor;       //!< minor file format version
    uint16_t fileFlags;  //!< global file flags
    uint32_t fileChunks; //!< total chunks in the file
} boot_hdr1_t;

//! Definition for boot image file header chunk 2
typedef struct _boot_hdr2
{
    uint32_t bootOffset; //!< chunk offset to the first boot section
    uint32_t bootSectID; //!< section ID of the first boot section
    uint16_t keyCount;   //!< number of keys in the key dictionary
    uint16_t keyOffset;  //!< chunk offset to the key dictionary
    uint16_t hdrChunks;  //!< number of chunks in the header
    uint16_t sectCount;  //!< number of sections in the image
} boot_hdr2_t;

// Provides forward reference to the loader context definition.
typedef struct _ldr_Context ldr_Context_t;

//! Function pointer definition for all loader action functions.
typedef status_t (*pLdrFnc_t)(ldr_Context_t *);

//! Jump command function pointer definition.
typedef status_t (*pJumpFnc_t)(uint32_t);

//! Call command function pointer definition.
typedef status_t (*pCallFnc_t)(uint32_t, uint32_t *);

//! Loader context definition.
struct _ldr_Context
{
    pLdrFnc_t Action;        // !< pointer to loader action function
    uint32_t fileChunks;     // !< chunks remaining in file
    uint32_t sectChunks;     // !< chunks remaining in section
    uint32_t bootSectChunks; // !< number of chunks we need to complete the boot section
    uint32_t receivedChunks; // !< number of chunks we need to complete the boot section
    uint16_t fileFlags;      // !< file header flags
    uint16_t keyCount;       // !< number of keys in the key dictionary
    uint32_t objectID;       // !< ID of the current boot section or image
    crc32_data_t crc32;      // !< crc calculated over load command payload
    uint8_t *src;            // !< source buffer address
    chunk_t initVector;      // !< decryption initialization vector
    chunk_t dek;             // !< chunk size DEK if the image is encrypted
    chunk_t scratchPad;      // !< chunk size scratch pad area
    boot_cmd_t bootCmd;      // !< current boot command
    uint32_t skipCount;      // !< Number of chunks to skip
    bool skipToEnd;          // !< true if skipping to end of file
};

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

status_t sbloader_init(void);
status_t sbloader_pump(uint8_t *data, uint32_t length);
status_t sbloader_finalize(void);

#if defined(__cplusplus)
}
#endif // __cplusplus

//! @}

#endif // _loader_h

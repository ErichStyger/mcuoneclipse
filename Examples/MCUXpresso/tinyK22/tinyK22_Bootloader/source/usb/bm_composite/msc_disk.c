/*
 * Copyright (c) 2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "usb_device_config.h"
#include "usb.h"
#include "usb_device.h"

#include "usb_device_class.h"
#include "usb_device_msc.h"
#include "usb_device_ch9.h"
#include "usb_descriptor.h"
#include "msc_disk.h"
#include "sbloader/sbloader.h"
#include "sbloader/sb_file_format.h"
#include "bootloader/bootloader.h"
#include "utilities/fsl_rtos_abstraction.h"
#include "fsl_device_registers.h"
#include "utilities/fsl_assert.h"
#include "utilities/fsl_rtos_abstraction.h"
#include "bootloader/bl_peripheral_interface.h"
#include "bootloader/bl_context.h"
#include "fat_directory_entry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "composite.h"

#if (BL_CONFIG_USB_MSC || BL_CONFIG_HS_USB_MSC)

static usb_device_composite_struct_t *g_device_composite;

usb_status_t usb_msd_write_sector(uint32_t sector, const usb_device_lba_app_struct_t *lbaData);
usb_status_t usb_msd_read_sector(uint32_t sector, usb_device_lba_app_struct_t *lbaData);
bool is_valid_sb_file_header(const uint8_t *data, uint32_t *fileLength);
status_t feed_sbloader(void);
void usb_msd_start_transfer(uint32_t length);
void reset_usb_msd_state(uint8_t loaderStatus);
void format_hex_string(char *s, uint32_t value);
void usb_msd_update_info_file(uint8_t *buffer);

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Date and time constants for directory entries.
enum _date_time_constants
{
    kFileDate = MAKE_FAT_DATE(12, 1, 2013), //!< 01-Dec-2013
    kFileTime = MAKE_FAT_TIME(12, 0, 0)     //!< 12:00:00 noon
};

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////
USB_DMA_INIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE)
usb_device_inquiry_data_fromat_struct_t g_InquiryInfo = {
    (USB_DEVICE_MSC_UFI_PERIPHERAL_QUALIFIER << USB_DEVICE_MSC_UFI_PERIPHERAL_QUALIFIER_SHIFT) |
        USB_DEVICE_MSC_UFI_PERIPHERAL_DEVICE_TYPE,
    (uint8_t)(USB_DEVICE_MSC_UFI_REMOVABLE_MEDIUM_BIT << USB_DEVICE_MSC_UFI_REMOVABLE_MEDIUM_BIT_SHIFT),
    USB_DEVICE_MSC_UFI_VERSIONS,
    0x02,
    USB_DEVICE_MSC_UFI_ADDITIONAL_LENGTH,
    {0x00, 0x00, 0x00},
    {'N', 'X', 'P', ' ', 'S', 'E', 'M', 'I'},
    {'N', 'X', 'P', ' ', 'M', 'A', 'S', 'S', ' ', 'S', 'T', 'O', 'R', 'A', 'G', 'E'},
    {'0', '0', '0', '1'}};
USB_DMA_INIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE)
usb_device_mode_parameters_header_struct_t g_ModeParametersHeader = {
    /*refer to ufi spec mode parameter header*/
    0x0000, /*!< Mode Data Length*/
    0x00,   /*!<Default medium type (current mounted medium type)*/
    0x00,   /*!MODE SENSE command, a Write Protected bit of zero indicates the medium is write enabled*/
    {0x00, 0x00, 0x00, 0x00} /*!<This bit should be set to zero*/
};
//! @brief Used by format_hex_string().
static const char kHexChars[] = "0123456789abcdef";

//! @brief Messages corresponding to the various transfer statuses.
static const char *const kStatusMessages[] = {
    "Ready\r\n",        // kReadyStatus
    "Transferring\r\n", // kTransferringStatus
    "Success\r\n",      // kSuccessStatus
    "Failure\r\n"       // kFailureStatus
};

//! @brief Format for contents of the info.txt file.
static const char kInfoFileFormat[] =
    "Kinetis Bootloader %c%d.%d.%d\r\n"
    "\r\n"
    "System device ID: %s\r\n"
    "Flash size: %s bytes\r\n"
    "Flash range: %s-%s\r\n"
    "Flash sector size: %s bytes\r\n"
    "Flash blocks: %s\r\n"
    "RAM size: %s bytes\r\n"
    "RAM range: %s-%s\r\n"
    "Reserved region 0: %s-%s\r\n"
    "Reserved region 1: %s-%s\r\n"
    "Verify writes: %s\r\n"
    "Check reserved regions: %s\r\n"
    "Boot config present: %s\r\n"
    "Peripheral detection timeout: %s ms\r\n"
    "CPU clock: %s Hz\r\n";

//! @brief Partition boot sector.
//!
//! Defines the FAT16 file system.
//!
//! The 0xaa55 signature at the end of the sector is not stored in this data. Instead, it is
//! filled in at runtime. This is done in order to save const data space.
static const uint8_t k_pbs[] = {
    0xEB,
    0x3C,
    0x90, // x86 JMP instruction
    'M',
    'S',
    'W',
    'I',
    'N',
    '4',
    '.',
    '1',                                 // 'MSWIN4.1'
    U16_LE(kDiskSectorSize),             // bytes per sector = 512
    0x01,                                // sectors per cluster = 1
    U16_LE(1),                           // number of reserved sectors = 1 (FAT12/16)
    0x02,                                // number of FATs = 2
    U16_LE(32),                          // maximum number of root directory entries = 32
    U16_LE(kDiskTotalLogicalBlocks - 1), // total volume sectors starting with PBS (16-bit count)
    0xF0,                                // media type, must match FAT[0] = 0xf0 (removable media)
    U16_LE(kDiskSectorsPerFat),          // sectors per FAT = 1
    U16_LE(1),                           // sectors per track = 1
    U16_LE(1),                           // number of heads = 1
    U32_LE(1),                           // sectors before start of PBS including MBR = 1
    U32_LE(kDiskTotalLogicalBlocks - 1), // total volume sectors starting with PBS
    0x00,                                // driver number (0x80 for hard disks) = 0
    0x00,                                // reserved
    0x29,                                // boot signature
    '1',
    '2',
    '3',
    '4', // volume ID = '1234'
    'K',
    'i',
    'n',
    'e',
    't',
    'i',
    's',
    ' ',
    'U',
    'S',
    'B', // volume label = 'Kinetis USB'
    // ..448 reserved bytes
    // 0x55,0xaa signature bytes - must be filled in at runtime
};

static const uint16_t k_fat1[] = {
    0xfff0, // unused cluster 0 (low byte must match media type in PBS)
    0xffff, // unused cluster 1
    0xffff, // '.fseventsd' directory
    0xffff, // 'System Volume Information' directory
    0xffff, // 'IndexerVolumeGuid' file
    0xffff, // 'info.txt' file
    0xffff, // 'status.txt' file
};

//! @brief Root directory.
//!
//! Volume label: FSL Loader
//!
//! Contents:
//! - .fseventsd (FSEVEN~1)
//! - .metadata_never_index (METADA~1)
//! - .Trashes (TRASHE~1)
//! - System Volume Information (SYSTEM~1)
//! - info.txt
//! - status.txt
static const fat_directory_entry_t k_rootDir[] = {
    // Volume label 'FSL Loader'
    MAKE_FAT_VOLUME_LABEL('F', 'S', 'L', ' ', 'L', 'o', 'a', 'd', 'e', 'r', ' ', kFileTime, kFileDate),

    // Mac OS X '.fseventsd' directory
    MAKE_FAT_LONG_NAME(
        1, L'.', L'f', L's', L'e', L'v', L'e', L'n', L't', L's', L'd', 0, 0xffff, 0xffff, 0xda, kLastLongNameEntry),
    MAKE_FAT_DIR_ENTRY('F',
                       'S',
                       'E',
                       'V',
                       'E',
                       'N',
                       '~',
                       '1',
                       ' ',
                       ' ',
                       ' ',
                       (kDirectoryAttribute | kHiddenAttribute),
                       kFileTime,
                       kFileDate,
                       CLUSTER_FROM_SECTOR(kMacFseventsdDirSector),
                       0),

    // Mac OS X '.metadata_never_index' file
    MAKE_FAT_LONG_NAME(
        2, L'e', L'r', L'_', L'i', L'n', L'd', L'e', L'x', 0, 0xffff, 0xffff, 0xffff, 0xffff, 0xa8, kLastLongNameEntry),
    MAKE_FAT_LONG_NAME(1, L'.', L'm', L'e', L't', L'a', L'd', L'a', L't', L'a', L'_', L'n', L'e', L'v', 0xa8, 0),
    MAKE_FAT_DIR_ENTRY('M',
                       'E',
                       'T',
                       'A',
                       'D',
                       'A',
                       '~',
                       '1',
                       ' ',
                       ' ',
                       ' ',
                       (kArchiveAttribute | kHiddenAttribute),
                       kFileTime,
                       kFileDate,
                       0,
                       0),

    // Mac OS X '.Trashes' file
    MAKE_FAT_LONG_NAME(
        1, L'.', L'T', L'r', L'a', L's', L'h', L'e', L's', 0, 0xffff, 0xffff, 0xffff, 0xffff, 0x25, kLastLongNameEntry),
    MAKE_FAT_DIR_ENTRY('T',
                       'R',
                       'A',
                       'S',
                       'H',
                       'E',
                       '~',
                       '1',
                       ' ',
                       ' ',
                       ' ',
                       (kArchiveAttribute | kHiddenAttribute),
                       kFileTime,
                       kFileDate,
                       0,
                       0),

    // Windows 'System Volume Information' directory
    MAKE_FAT_LONG_NAME(
        2, L' ', L'I', L'n', L'f', L'o', L'r', L'm', L'a', L't', L'i', L'o', L'n', 0, 0x72, kLastLongNameEntry),
    MAKE_FAT_LONG_NAME(1, L'S', L'y', L's', L't', L'e', L'm', L' ', L'V', L'o', L'l', L'u', L'm', L'e', 0x72, 0),
    MAKE_FAT_DIR_ENTRY('S',
                       'Y',
                       'S',
                       'T',
                       'E',
                       'M',
                       '~',
                       '1',
                       ' ',
                       ' ',
                       ' ',
                       (kDirectoryAttribute | kSystemAttribute | kHiddenAttribute),
                       kFileTime,
                       kFileDate,
                       CLUSTER_FROM_SECTOR(kWindowsSysVolInfoDirSector),
                       0),

    // Info and status files
    MAKE_FAT_DIR_ENTRY('I',
                       'N',
                       'F',
                       'O',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       'T',
                       'X',
                       'T',
                       kArchiveAttribute,
                       kFileTime,
                       kFileDate,
                       CLUSTER_FROM_SECTOR(kInfoFileSector),
                       1), // File size is filled in at runtime
    MAKE_FAT_DIR_ENTRY('S',
                       'T',
                       'A',
                       'T',
                       'U',
                       'S',
                       ' ',
                       ' ',
                       'T',
                       'X',
                       'T',
                       kArchiveAttribute,
                       kFileTime,
                       kFileDate,
                       CLUSTER_FROM_SECTOR(kStatusFileSector),
                       1), // File size is filled in at runtime
};

//! @brief .fseventsd directory.
//!
//! Contents:
//! - .
//! - ..
//! - no_log
static const fat_directory_entry_t k_fseventsdDir[] = {
    // . and .. directories
    MAKE_FAT_DIR_ENTRY('.',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       (kDirectoryAttribute | kArchiveAttribute | kHiddenAttribute),
                       kFileTime,
                       kFileDate,
                       CLUSTER_FROM_SECTOR(kMacFseventsdDirSector),
                       0),
    MAKE_FAT_DIR_ENTRY(
        '.', '.', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', kDirectoryAttribute, kFileTime, kFileDate, 0, 0),

    // Special 'no_log' file with reserved byte set to 0x08.
    {.entry = {.name = { 'N', 'O', '_', 'L', 'O', 'G', ' ', ' ', ' ', ' ', ' ' },
               .attributes = kArchiveAttribute,
               .ntReserved = 0x08,
               .creationTime = kFileTime,
               .creationDate = kFileDate,
               .lastAccessDate = kFileDate,
               .firstClusterHigh = 0,
               .writeTime = kFileTime,
               .writeDate = kFileDate,
               .firstClusterLow = 0,
               .fileSize = 0 } },
};

static const wchar_t k_indexerVolumeGuidFile[] = L"{37203BF8-FD83-4321-A4C4-9A9ABF8FBCFD}";

//! @brief System Volume Information directory.
//!
//! Contents:
//! - .
//! - ..
//! - IndexerVolumeGuid (INDEXE~1)
static const fat_directory_entry_t k_sysVolInfoDir[] = {
    // . and .. directories
    MAKE_FAT_DIR_ENTRY('.',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       (kDirectoryAttribute | kArchiveAttribute | kHiddenAttribute),
                       kFileTime,
                       kFileDate,
                       CLUSTER_FROM_SECTOR(kWindowsSysVolInfoDirSector),
                       0),
    MAKE_FAT_DIR_ENTRY(
        '.', '.', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', kDirectoryAttribute, kFileTime, kFileDate, 0, 0),

    // 'IndexerVolumeGuid' file
    MAKE_FAT_LONG_NAME(
        2, L'G', L'u', L'i', L'd', 0, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0, 0, 0xff, kLastLongNameEntry),
    MAKE_FAT_LONG_NAME(1, L'I', L'n', L'd', L'e', L'x', L'e', L'r', L'V', L'o', L'l', L'u', L'm', L'e', 0xff, 0),
    MAKE_FAT_DIR_ENTRY('I',
                       'N',
                       'D',
                       'E',
                       'X',
                       'E',
                       '~',
                       '1',
                       ' ',
                       ' ',
                       ' ',
                       kArchiveAttribute,
                       kFileTime,
                       kFileDate,
                       CLUSTER_FROM_SECTOR(kWindowsIndexerVolumeGuidSector),
                       (sizeof(k_indexerVolumeGuidFile) - 1)), // subtract 1 to remove the trailing null byte
};

const sector_info_t g_msdDiskSectors[] = {
    { kPbsSector, k_pbs, sizeof(k_pbs) },
    { kFat1Sector, (const uint8_t *)k_fat1, sizeof(k_fat1) },
    { kRootDir1Sector, (const uint8_t *)k_rootDir, sizeof(k_rootDir) },

    // Support for Mac OS X: .fseventsd directory
    { kMacFseventsdDirSector, (const uint8_t *)k_fseventsdDir, sizeof(k_fseventsdDir) },

    // Support for Window 8.1: System Volume Information directory
    { kWindowsSysVolInfoDirSector, (const uint8_t *)k_sysVolInfoDir, sizeof(k_sysVolInfoDir) },
    { kWindowsIndexerVolumeGuidSector, (const uint8_t *)k_indexerVolumeGuidFile,
      sizeof(k_indexerVolumeGuidFile) - 1 }, // subtract 1 to remove the trailing null byte

    // contains info.txt
    //     { kInfoFileSector, (const uint8_t *)((const uint8_t *)BlockBuf + 512), 512 },
    //
    //     // contains status.txt
    //     { kStatusFileSector, (const uint8_t *)((const uint8_t *)BlockBuf + 1024), 512 },

    // Terminator
    { 0 }
};

/*!
 * @brief device msc callback function.
 *
 * This function handle the disk class specified event.
 * @param handle          The USB class  handle.
 * @param event           The USB device event type.
 * @param param           The parameter of the class specific event.
 * @return kStatus_USB_Success or error.
 */
usb_status_t usb_device_msc_callback(class_handle_t handle, uint32_t event, void *param)
{
    usb_status_t error = kStatus_USB_Error;
    usb_device_lba_information_struct_t *lba_info_structure_ptr;
    usb_device_lba_app_struct_t *lba_data_ptr;
    usb_device_ufi_app_struct_t *ufi;
    uint8_t *prevent_removal_ptr;
    uint32_t sector;

    switch (event)
    {
        case kUSB_DeviceMscEventReadResponse:
            /*!< Send data completed */
            lba_data_ptr = (usb_device_lba_app_struct_t *)param;

            if (lba_data_ptr != NULL)
            {
                sector = lba_data_ptr->offset;
                error = usb_msd_read_sector(sector, lba_data_ptr);
                if (error != kStatus_USB_Success)
                {
                    g_device_composite->msc_disk.msc_state.read_write_error = 1;
                }
            }

            break;
        case kUSB_DeviceMscEventWriteResponse:
            /*!< Data received */
            lba_data_ptr = (usb_device_lba_app_struct_t *)param;

            if (lba_data_ptr != NULL)
            {
                sector = lba_data_ptr->offset;
                error = usb_msd_write_sector(sector, lba_data_ptr);
                if (error != kStatus_USB_Success)
                {
                    g_device_composite->msc_disk.msc_state.read_write_error = 1;
                }
            }
            break;
        case kUSB_DeviceMscEventWriteRequest:
            /*!< Host write data*/
            lba_data_ptr = (usb_device_lba_app_struct_t *)param;

            /*offset is the write start address get from write command, refer to class driver*/
            // RAM disk
            //        lba_data_ptr->buff_ptr = g_device_composite->msc_disk.storage_disk + lba_data_ptr->offset;
            if (lba_data_ptr != NULL)
            {
                lba_data_ptr->buffer = (uint8_t *)g_device_composite->msc_disk.msc_state.buffer;
            }

            break;
        case kUSB_DeviceMscEventReadRequest:
            /*!< Host read data*/
            lba_data_ptr = (usb_device_lba_app_struct_t *)param;
            /*offset is the read start address get from read command, refer to class driver*/
            // RAM disk
            //        lba_data_ptr->buff_ptr = g_device_composite->msc_disk.storage_disk + lba_data_ptr->offset;

            if (lba_data_ptr != NULL)
            {
                lba_data_ptr->buffer = (uint8_t *)g_device_composite->msc_disk.msc_state.buffer;
                sector = lba_data_ptr->offset;
                error = usb_msd_read_sector(sector, lba_data_ptr);
            }

            break;
        case kUSB_DeviceMscEventGetLbaInformation:
            lba_info_structure_ptr = (usb_device_lba_information_struct_t *)param;
            //lba_info_structure_ptr->totalLbaNumberSupports = kDiskTotalLogicalBlocks;
            //lba_info_structure_ptr->lengthOfEachLba = kDiskSectorSize;
            lba_info_structure_ptr->logicalUnitNumberSupported = kDiskLogicalUnits;
            //lba_info_structure_ptr->bulkInBufferSize = USB_DEVICE_MSC_WRITE_BUFF_SIZE;
            //lba_info_structure_ptr->bulkOutBufferSize = USB_DEVICE_MSC_READ_BUFF_SIZE;
            error = kStatus_USB_Success;
            break;
        case kUSB_DeviceMscEventTestUnitReady:
            /*change the test unit ready command's sense data if need, be careful to modify*/
            ufi = (usb_device_ufi_app_struct_t *)param;
            break;
        case kUSB_DeviceMscEventInquiry:
            ufi = (usb_device_ufi_app_struct_t *)param;
            ufi->size = sizeof(usb_device_inquiry_data_fromat_struct_t);
            ufi->buffer = (uint8_t *)&g_InquiryInfo;
            break;
        case kUSB_DeviceMscEventModeSense:
            ufi = (usb_device_ufi_app_struct_t *)param;
            ufi->size = sizeof(usb_device_mode_parameters_header_struct_t);
            ufi->buffer = (uint8_t *)&g_ModeParametersHeader;
            break;
        case kUSB_DeviceMscEventModeSelect:
            break;
        case kUSB_DeviceMscEventModeSelectResponse:
            ufi = (usb_device_ufi_app_struct_t *)param;
            break;
        case kUSB_DeviceMscEventFormatComplete:
            break;
        case kUSB_DeviceMscEventRemovalRequest:
            prevent_removal_ptr = (uint8_t *)param;
            if (USB_DEVICE_CONFIG_MSC_SUPPORT_DISK_LOCKING_MECHANISM)
            {
                g_device_composite->msc_disk.msc_state.isDiskLocked = *prevent_removal_ptr;
            }
            else if ((!USB_DEVICE_CONFIG_MSC_SUPPORT_DISK_LOCKING_MECHANISM) && (!(*prevent_removal_ptr)))
            {
                /*there is no support for disk locking and removal of medium is enabled*/
                /* code to be added here for this condition, if required */
            }
            error = kStatus_USB_Success;
            break;
    }
    return error;
}

/*!
 * @brief msc device set configuration function.
 *
 * This function sets configuration for msc class.
 *
 * @param handle The msc class handle.
 * @param configure The msc class configure index.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t usb_device_msc_disk_set_configure(class_handle_t handle, uint8_t configure)
{
    //   g_device_composite->msc_disk.current_configuration = configure;
    return kStatus_USB_Success;
}
/*!
 * @brief device msc init function.
 *
 * This function initializes the device with the composite device class information.
 *
 * @param device_composite          The pointer to the composite device structure.
 * @return kStatus_USB_Success .
 */
usb_status_t usb_device_msc_disk_init(usb_device_composite_struct_t *device_composite)
{
    g_device_composite = device_composite;
    //    g_device_composite->msc_disk.storage_disk[0] = 0x01;   // RAM disk

    // Get the length of the info.txt file by writing it to a buffer temporarily.
    usb_msd_update_info_file(g_device_composite->msc_disk.msc_state.buffer);
    uint32_t length = strlen((char *)g_device_composite->msc_disk.msc_state.buffer);

    // Init the state info. This also clears the sector buffers.
    memset(&g_device_composite->msc_disk.msc_state, 0, sizeof(g_device_composite->msc_disk.msc_state));

    g_device_composite->msc_disk.msc_state.infoFileLength = length;

    g_device_composite->msc_disk.msc_state.start_app = false;
    return kStatus_USB_Success;
}

/*!
 * @brief device msc init function.
 *
 * This function initializes the device with the composite device class information.
 *
 * @param device_composite          The pointer to the composite device structure.
 * @return kStatus_USB_Success .
 */
usb_status_t usb_device_msc_disk_deinit(usb_device_composite_struct_t *device_composite)
{
    g_device_composite = device_composite;
    // RAM Disk
    // g_device_composite->msc_disk.storage_disk[0] = 0x01;
    g_device_composite->msc_disk.msc_handle = (class_handle_t)NULL;
    return kStatus_USB_Success;
}

//! @brief Run the sbloader state machine.
//!
//! This function is called repeatedly by the main application loop. We use it
//! to run the sbloader state machine from non-interrupt context.
void usb_device_msc_disk_pump(void)
{
    status_t status = kStatus_Success;

    // Init the sb loader state machine.
    if (g_device_composite->msc_disk.msc_state.sbLoaderStatus == kSbLoaderFree)
    {
        sbloader_init();
        g_device_composite->msc_disk.msc_state.sbLoaderStatus = kSbLoaderInited;
        g_device_composite->msc_disk.msc_state.start_app = true;
    }

    if (g_device_composite->msc_disk.msc_state.isProcessing)
    {
        // Process the SB file. This loop will exit under four conditions:
        //  - Error during SB file command execution.
        //  - Underrun: more data needed.
        //  - Jump command encountered.
        do
        {
            g_device_composite->msc_disk.msc_state.sbLoaderStatus = kSbLoaderLoading;
            status = feed_sbloader();
        } while (status == kStatus_Success);
        if ((g_device_composite->msc_disk.msc_state.remainingFileLength == 0) &&
            (g_device_composite->msc_disk.msc_state.sbLoaderStatus == kSbLoaderLoading))
        {
            reset_usb_msd_state(kSbLoaderFinal);
        }
        else
        {
            g_device_composite->msc_disk.msc_state.isProcessing = true;
        }
        // kStatusRomLdrDataUnderrun means need more data. This is OK to continue on.
        if (status == kStatusRomLdrDataUnderrun)
        {
            status = kStatus_Success;
        }

        // Stop saving SB data if we got an error.
        if (status != kStatus_Success)
        {
            g_device_composite->msc_disk.msc_state.isProcessing = false;

            if (status == kStatusRomLdrSectionOverrun)
            {
                g_device_composite->msc_disk.msc_state.transferStatus = kSuccessStatus;
                debug_printf("SB processing done: section overrun\r\n");
            }
            else if (status == kStatus_AbortDataPhase)
            {
                g_device_composite->msc_disk.msc_state.transferStatus = kSuccessStatus;

                debug_printf("SB processing done: hit jump command\r\n");
                reset_usb_msd_state(kSbLoaderFinal);
            }
            else
            {
                g_device_composite->msc_disk.msc_state.transferStatus = kFailureStatus;
                debug_printf("SB processing done: error %d\r\n", status);
                reset_usb_msd_state(kSbLoaderFree);
            }
        }
    }
    return;
}

usb_status_t usb_msd_write_sector(uint32_t sector, const usb_device_lba_app_struct_t *lbaData)
{
    if (sector >= kFirstUnusedSector)
    {
        bool saveSbData = false;

        if (!g_device_composite->msc_disk.msc_state.isTransferring)
        {
            if (g_device_composite->msc_disk.msc_state.isProcessing)
            {
                debug_printf("write_sector: ignoring sector %u write while SB processing continues...\r\n", sector);
                return kStatus_USB_BandwidthFail;
            }

            // Check if this is an .sb file by looking for signatures in the header. This call
            // also returns the total size in bytes of the SB file.
            uint32_t sbLength;
            if (is_valid_sb_file_header(lbaData->buffer, &sbLength))
            {
                //                debug_printf("write_sector: started receiving SB file on sector %u (length=%u
                //                bytes)\r\n", sector, sbLength);
                // This is a valid .sb file header
                usb_msd_start_transfer(sbLength);
                // Save the sector data.
                saveSbData = true;
            }
        }
        else if (sector == g_device_composite->msc_disk.msc_state.nextSector)
        {
            saveSbData = true;
        }
        else
        {
            // Out of order sector write.
            // debug_printf("Out of order sector write during transfer (%u)\r\n", sector);
        }

        // Save the SB file contents for processing by the main bootloader run loop (outside
        // of interrupt context).
        if (saveSbData)
        {
            // Update state information.
            uint32_t count = MIN(g_device_composite->msc_disk.msc_state.remainingFileLength, lbaData->size);
            g_device_composite->msc_disk.msc_state.dataBytesAvailable += count;
            g_device_composite->msc_disk.msc_state.remainingFileLength -= count;

            g_device_composite->msc_disk.msc_state.nextSector = sector + 1;

            if (g_device_composite->msc_disk.msc_state.remainingFileLength == 0)
            {
                g_device_composite->msc_disk.msc_state.isTransferring = false;
            }

            memcpy(g_device_composite->msc_disk.msc_state.sbBuffer, lbaData->buffer, count);

            usb_device_msc_disk_pump();
        }
    }
    return kStatus_USB_Success;
}

usb_status_t usb_msd_read_sector(uint32_t sector, usb_device_lba_app_struct_t *lbaData)
{
    // Clear the sector contents (all zeroes).
    memset(lbaData->buffer, 0, lbaData->size);

    // Search for a sector entry in our table.
    const sector_info_t *sectorInfo = g_msdDiskSectors;
    for (; sectorInfo->data; ++sectorInfo)
    {
        if (sectorInfo->sector == sector)
        {
            // Copy sector data into output buffer.
            memcpy(lbaData->buffer, sectorInfo->data, sectorInfo->length);
            break;
        }
    }

    // Special handling for certain sectors.
    switch (sector)
    {
        case kPbsSector:
            // Fill in signature bytes for PBS, so we don't have to have the full 512 bytes as const data.
            lbaData->buffer[510] = 0x55;
            lbaData->buffer[511] = 0xaa;
            break;

        case kRootDir1Sector:
        {
            // Update info.txt and status.txt file sizes in root directory.
            fat_directory_entry_t *rootDir = (fat_directory_entry_t *)lbaData->buffer;

            rootDir[kInfoFileDirEntry].entry.fileSize = g_device_composite->msc_disk.msc_state.infoFileLength;

            const char *statusMessage = kStatusMessages[g_device_composite->msc_disk.msc_state.transferStatus];
            rootDir[kStatusFileDirEntry].entry.fileSize = strlen(statusMessage);

            break;
        }

        case kInfoFileSector:
            usb_msd_update_info_file(lbaData->buffer);
            break;

        case kStatusFileSector:
        {
            const char *statusMessage = kStatusMessages[g_device_composite->msc_disk.msc_state.transferStatus];
            uint32_t statusLength = strlen(statusMessage);
            memcpy(lbaData->buffer, statusMessage, statusLength);
            break;
        }
    }

    return kStatus_USB_Success;
}

bool is_valid_sb_file_header(const uint8_t *data, uint32_t *fileLength)
{
    sb_image_header_t *header = (sb_image_header_t *)data;

    if ((header->m_signature == BOOT_SIGNATURE) && (header->m_signature2 == BOOT_SIGNATURE2) &&
        (header->m_majorVersion == SB_FILE_MAJOR_VERSION))
    {
        assert(fileLength);
        *fileLength = header->m_imageBlocks * BYTES_PER_CHUNK;

        return true;
    }
    else
    {
        return false;
    }
}

//! @brief Push data that has been received from host during data phase.
status_t feed_sbloader(void)
{
    status_t status = kStatus_Success;

    // Get the number of bytes we can give to sbloader. If there is no available data,
    // then there is nothing else for us to do here and we can return an underrun meaning waiting for more data
    uint32_t available = MIN(g_device_composite->msc_disk.msc_state.dataBytesAvailable, kDiskSectorSize);

    if (!available)
    {
        status = kStatusRomLdrDataUnderrun;
    }
    else
    {
        g_device_composite->msc_disk.msc_state.dataBytesAvailable -= available;

        // Give the data to sbloader.
        status = sbloader_pump(g_device_composite->msc_disk.msc_state.sbBuffer, available);
    }

    return status;
}

//! @brief Prepare for a new SB file transfer.
void usb_msd_start_transfer(uint32_t length)
{
    g_device_composite->msc_disk.msc_state.isActive = true;
    g_device_composite->msc_disk.msc_state.isTransferring = true;
    g_device_composite->msc_disk.msc_state.sbLoaderStatus = kSbLoaderFree;
    g_device_composite->msc_disk.msc_state.isProcessing = true;
    g_device_composite->msc_disk.msc_state.isReceivePending = false;
    g_device_composite->msc_disk.msc_state.dataBytesAvailable = 0;
    g_device_composite->msc_disk.msc_state.remainingFileLength = length;
    g_device_composite->msc_disk.msc_state.transferStatus = kTransferringStatus;
}

//! @brief Prepare for a new SB file transfer.
void reset_usb_msd_state(uint8_t loaderStatus)
{
    g_device_composite->msc_disk.msc_state.isActive = true;
    g_device_composite->msc_disk.msc_state.isTransferring = false;
    g_device_composite->msc_disk.msc_state.sbLoaderStatus = loaderStatus;
    g_device_composite->msc_disk.msc_state.isProcessing = false;
    g_device_composite->msc_disk.msc_state.isReceivePending = false;
    g_device_composite->msc_disk.msc_state.dataBytesAvailable = 0;
    g_device_composite->msc_disk.msc_state.remainingFileLength = 0;
    g_device_composite->msc_disk.msc_state.transferStatus = kTransferringStatus;
}

void format_hex_string(char *s, uint32_t value)
{
    s[0] = '0';
    s[1] = 'x';
    s[10] = 0;

    uint32_t i;
    for (i = 0; i < 8; ++i)
    {
        s[i + 2] = kHexChars[(value >> (28 - (i * 4))) & 0xf];
    }
}

void format_digit_string(char *s, uint32_t value)
{
    // Get reversed string
    uint32_t i = 0;
    if (value > 0)
    {
        while (value)
        {
            s[i] = (value % 10) + '0';
            value /= 10;
            i++;
        }
    }
    else
    {
        s[i++] = '0';
    }

    // Reverse above string, then get expected string.
    s[i] = '\0';
    char *head = s;
    char *tail = (s + i - 1);
    char tmp;
    while (head < tail)
    {
        tmp = *tail;
        *tail = *head;
        *head = tmp;
        tail--;
        head++;
    }
}

void usb_msd_update_info_file(uint8_t *buffer)
{
    property_store_t *store = g_bootloaderContext.propertyInterface->store;
    standard_version_t version = store->bootloaderVersion;

    char hexBuffers[9][11];
    char digitBuffers[6][11];
    uint32_t timeoutInMilliSeconds;

    timeoutInMilliSeconds = (store->configurationData.peripheralDetectionTimeoutMs != 0xffff) ?
                                store->configurationData.peripheralDetectionTimeoutMs :
                                BL_DEFAULT_PERIPHERAL_DETECT_TIMEOUT;

    format_hex_string(hexBuffers[0], SIM->SDID);
    format_hex_string(hexBuffers[1], store->flashStartAddress[kFlashIndex_Main]);
    format_hex_string(hexBuffers[2], store->flashStartAddress[kFlashIndex_Main] + store->flashSizeInBytes[kFlashIndex_Main] - 1);
    format_hex_string(hexBuffers[3], store->ramStartAddress[0]);
    format_hex_string(hexBuffers[4], store->ramStartAddress[0] + store->ramSizeInBytes[0] - 1);
    format_hex_string(hexBuffers[5], store->reservedRegions[0].startAddress);
    format_hex_string(hexBuffers[6], store->reservedRegions[0].endAddress);
    format_hex_string(hexBuffers[7], store->reservedRegions[1].startAddress);
    format_hex_string(hexBuffers[8], store->reservedRegions[1].endAddress);

    format_digit_string(digitBuffers[0], store->flashSizeInBytes[kFlashIndex_Main]);
    format_digit_string(digitBuffers[1], store->flashSectorSize[kFlashIndex_Main]);
    format_digit_string(digitBuffers[2], store->flashBlockCount[kFlashIndex_Main]);
    format_digit_string(digitBuffers[3], store->ramSizeInBytes[0]);
    format_digit_string(digitBuffers[4], timeoutInMilliSeconds);
    format_digit_string(digitBuffers[5], SystemCoreClock);

    sprintf((char *)buffer, kInfoFileFormat, version.name, version.major, version.minor, version.bugfix, // Version
            hexBuffers[0],                                                      // System device ID
            digitBuffers[0],                                                    // Flash size
            hexBuffers[1], hexBuffers[2],                                       // Flash range
            digitBuffers[1],                                                    // Flash sector size
            digitBuffers[2],                                                    // Flash block count
            digitBuffers[3],                                                    // RAM size
            hexBuffers[3], hexBuffers[4],                                       // RAM range
            hexBuffers[5], hexBuffers[6],                                       // Reserved range 0
            hexBuffers[7], hexBuffers[8],                                       // Reserved range 1
            store->verifyWrites ? "yes" : "no",                                 // Verify flag
            "yes",                                                              // Always check reserved region
            (store->configurationData.tag == kPropertyStoreTag) ? "yes" : "no", // BCA enabled flag
            digitBuffers[4],                                                    // Peripheral detection timeout
            digitBuffers[5]);                                                   // System Core Clock
}

#endif //  BL_CONFIG_USB_MSC

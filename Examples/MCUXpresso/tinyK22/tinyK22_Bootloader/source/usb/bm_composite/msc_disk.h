/*
 * Copyright (c) 2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __USB_DISK_H__
#define __USB_DISK_H__ 1

/*
#if  defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI>0)
#define CONTROLLER_ID         kUSB_ControllerEhci0
#endif
#if  defined(USB_DEVICE_CONFIG_KHCI) && (USB_DEVICE_CONFIG_KHCI>0)
#define CONTROLLER_ID         kUSB_ControllerKhci0
#endif
 */
#define USB_DEVICE_INTERRUPT_PRIORITY (4)

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @name Data format macros
//@{
//! @brief Format a 32-bit little endian word as four bytes separated by commas.
#define U32_LE(n) ((n)&0xff), (((n) >> 8) & 0xff), (((n) >> 16) & 0xff), (((n) >> 24) & 0xff)

//! @brief Format a 16-bit little endian half-word as two bytes separated by commas.
#define U16_LE(n) ((n)&0xff), (((n) >> 8) & 0xff)
//@}

/* Length of Each Logical Address Block */
#define LENGTH_OF_EACH_LBA (512)
/* total number of logical blocks present */
#define TOTAL_LOGICAL_ADDRESS_BLOCKS_NORMAL (48)
/* Net Disk Size , default disk is 48*512, that is 24kByte, however , the disk reconnised by that PC only has 4k Byte,
 * This is caused by that the file system also need memory*/
//#define DISK_SIZE_NORMAL (TOTAL_LOGICAL_ADDRESS_BLOCKS_NORMAL * LENGTH_OF_EACH_LBA)

#define LOGICAL_UNIT_SUPPORTED (1)

#define USB_DEVICE_MSC_WRITE_BUFF_NUM 2
#define USB_DEVICE_MSC_WRITE_BUFF_SIZE 512
#define USB_DEVICE_MSC_READ_BUFF_SIZE 512

//! @brief Disk related constants.
enum _disk_constants
{
    kDiskSectorSize = 512,                                        //!< Size in bytes of each sector of the disk.
    kDiskTotalLogicalBlocks = 2048 * 16,                          //!< Total number of sectors in the disk.
    kDiskSizeInBytes = kDiskTotalLogicalBlocks * kDiskSectorSize, //!< Size in bytes of the total disk.
    kDiskLogicalUnits = 1,                                        //!< Number of SCSI LUNs.
    kDiskHeaderSectorCount = 1,                                   //!< PBS
    kDiskFat16EntrySize = 2,                                      //!< Two bytes per FAT16 entry.
    kDiskClusterSize = 1,                                         //!< Number of sectors per cluster.
    kDiskDataClusterCount = (kDiskTotalLogicalBlocks - kDiskHeaderSectorCount) / kDiskClusterSize,
    kDiskSectorsPerFat = (kDiskDataClusterCount * kDiskFat16EntrySize + kDiskSectorSize - 1) /
                         kDiskSectorSize, //!< Number of sectors occupied by each FAT, rounded up.
};

//! @brief Sector number constants.
enum _sector_numbers
{
    kPbsSector = 0,                                     //!< Partition Boot Sector
    kFat1Sector = kPbsSector + 1,                       //!< FAT1
    kFat2Sector = kFat1Sector + kDiskSectorsPerFat,     //!< FAT2 (unused)
    kRootDir1Sector = kFat2Sector + kDiskSectorsPerFat, //!< Root directory 1 (16 x 32-byte entries)
    kRootDir2Sector,                                    //!< Root directory 2 (16 x 32-byte entries)
    kMacFseventsdDirSector,                             //!< Mac OS X '.fseventsd' directory
    kWindowsSysVolInfoDirSector,                        //!< Windows 8.1 'System Volume Information' directory
    kWindowsIndexerVolumeGuidSector,                    //!< Windows 8.1 'IndexerVolumeGuid' file
    kInfoFileSector,                                    //!< Info .txt file
    kStatusFileSector,                                  //!< Status .txt file
    kFirstUnusedSector,                                 //!< First sector available for data.

    kFirstClusterSector = kRootDir1Sector, //!< Sector number of the first cluster.
};

//! @brief Convert a sector number to a cluster number.
#define CLUSTER_FROM_SECTOR(s) (((s)-kFirstClusterSector) / kDiskClusterSize)

//! @brief Root directory entry constants.
enum _root_dir_entry_numbers
{
    kInfoFileDirEntry = 11,
    kStatusFileDirEntry = 12,
    kFirstUnusedDirEntry = 13
};

//! @brief Sector information.
//!
//! Information about canned sectors. The sector data does not have to completely fill the
//! sector. Any remainder bytes will be cleared to zero in the sector read function.
typedef struct SectorInfo
{
    uint32_t sector;     //!< Sector number.
    const uint8_t *data; //!< Data for the sector.
    uint32_t length;     //!< Number of bytes of data.
} sector_info_t;

//! @brief Status values for SB tranfsers.
typedef enum _sb_transfer_status
{
    kReadyStatus = 0,
    kTransferringStatus,
    kSuccessStatus,
    kFailureStatus
} sb_transfer_status_t;

//! @brief Status values for SB loader.
typedef enum _sb_loader_status
{
    kSbLoaderFree = 0,
    kSbLoaderInited,
    kSbLoaderLoading,
    kSbLoaderFinal,
} sb_loader_status_t;

//! @brief The various states that a sector buffer can be in.
typedef enum _sector_buffer_status
{
    kBufferFree = 0, //!< Buffer contains no data.
    kBufferPending,  //!< A write is pending for this buffer.
    kBufferFilled,   //!< Buffer has data that is waited to be processed.
    kBufferInUse     //!< The buffer's data is being processed by the sbloader.
} sector_buffer_status_t;

//! @brief Various constants for the MSD peripheral.
enum _usb_msd_constants
{
    //! Number of sector buffers we use.
    kNumberOfSectorBuffers = 2,

    //! Value used to indicate that the #usb_msd_state_t::lastBufferReadIndex is unset.
    kInvalidBufferReadIndex = ~0
};

//! @brief State information for the USB MSD peripheral.
//!
//! The sector buffers come first so they will be word aligned.
typedef struct _usb_msd_state
{
    uint32_t start_app;
    uint8_t buffer[kDiskSectorSize];   //!< Generic buffer.
    uint8_t sbBuffer[kDiskSectorSize]; //!< Buffer to hold SB file sectors
    uint8_t isDiskLocked;
    uint8_t read_write_error;
    uint8_t isActive;                    //!< Set to true when the first SB file is transferred.
    uint8_t isTransferring;              //!< Whether an SB file transfer has been started.
    uint8_t sbLoaderStatus;              // //!< Status to indicate that the SB loader has been initialized.
    uint8_t isProcessing;                //!< Set to true while the SB file is being processed.
    uint8_t isReceivePending;            //!< Whether a sector write is being held off until a buffer is free.
    uint32_t infoFileLength;             //!< Size in bytes of the info.txt file.
    uint32_t nextSector;                 //!< The next expected sector write for the SB file transfer.
    uint32_t remainingFileLength;        //!< Total length in bytes of the SB file being transferred.
    uint32_t dataBytesAvailable;         //!< Number of bytes available in sectorBuffer.
    sb_transfer_status_t transferStatus; //!< Status to present in the status.txt file.
} usb_msd_state_t;

typedef struct _usb_msc_struct
{
    usb_device_handle device_handle;
    class_handle_t msc_handle;
    //    uint8_t                   storage_disk[DISK_SIZE_NORMAL];
    usb_msd_state_t msc_state;
    uint8_t current_configuration;
    uint8_t current_interface_alternate_setting[USB_MSC_INTERFACE_COUNT];
    uint8_t speed;
    uint8_t attach;
} usb_msc_struct_t;

#endif

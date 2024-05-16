/*
 * USB mass storage class driver that mimics littlefs to FAT12 file system.
 *
 * Copyright 2024, Hiroyuki OYAMA. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <tusb.h>
#include "mimic_fat.h"


extern const struct lfs_config lfs_pico_flash_config;
static bool ejected = false;
static bool is_initialized = false;


void tud_msc_inquiry_cb(uint8_t lun, uint8_t vendor_id[8], uint8_t product_id[16], uint8_t product_rev[4]) {
    (void)lun;

    const char vid[] = "littlefs";
    const char pid[] = "Mass Storage";
    const char rev[] = "1.0";

    memcpy(vendor_id  , vid, strlen(vid));
    memcpy(product_id , pid, strlen(pid));
    memcpy(product_rev, rev, strlen(rev));
}

bool tud_msc_test_unit_ready_cb(uint8_t lun) {
    (void)lun;
    return true;
}

void tud_msc_capacity_cb(uint8_t lun, uint32_t* block_count, uint16_t* block_size) {
    (void)lun;

    *block_count = mimic_fat_total_sector_size();
    *block_size  = DISK_SECTOR_SIZE;
}

bool tud_msc_start_stop_cb(uint8_t lun, uint8_t power_condition, bool start, bool load_eject) {
    (void)lun;
    (void)power_condition;

    if (load_eject) {
        if (start) {
            // load disk storage
        } else {
            // unload disk storage
            ejected = true;
        }
    }
    return true;
}

int32_t tud_msc_read10_cb(uint8_t lun, uint32_t lba, uint32_t offset, void* buffer, uint32_t bufsize) {
    (void)lun;
    (void)offset;

    if (!is_initialized) {
        mimic_fat_init(&lfs_pico_flash_config);
        mimic_fat_update_usb_device_is_enabled(true);
        mimic_fat_create_cache();
        is_initialized = true;
    }
    mimic_fat_read(lun, lba, buffer, bufsize);

    return (int32_t)bufsize;
}

bool tud_msc_is_writable_cb (uint8_t lun) {
    (void) lun;
    return true;
}

int32_t tud_msc_write10_cb(uint8_t lun, uint32_t lba, uint32_t offset, uint8_t* buffer, uint32_t bufsize) {
    (void)offset;

    mimic_fat_write(lun, lba, buffer, bufsize);
    return bufsize;
}

int32_t tud_msc_scsi_cb(uint8_t lun, uint8_t const scsi_cmd[16], void *buffer, uint16_t bufsize) {
    void const *response = NULL;
    int32_t resplen = 0;

    // most scsi handled is input
    bool in_xfer = true;

    switch (scsi_cmd[0]) {
    default:
        // Set Sense = Invalid Command Operation
        tud_msc_set_sense(lun, SCSI_SENSE_ILLEGAL_REQUEST, 0x20, 0x00);
        // negative means error -> tinyusb could stall and/or response with failed status
        resplen = -1;
        break;
    }

    // return resplen must not larger than bufsize
    if (resplen > bufsize) resplen = bufsize;

    if (response && (resplen > 0)) {
        if(in_xfer) {
            memcpy(buffer, response, (size_t) resplen);
        } else {
            ; // SCSI output
        }
    }
    return (int32_t)resplen;
}

void tud_mount_cb(void) {
    printf("\e[45mmount\e[0m\n");
    /*
     * NOTE:
     * This callback must be returned immediately. Time-consuming processing
     * here will cause TinyUSB to PANIC `ep 0 in was already available`.
     */
    is_initialized = false;
}

void tud_suspend_cb(bool remote_wakeup_en) {
    (void)remote_wakeup_en;

    printf("\e[45msuspend\e[0m\n");
    mimic_fat_cleanup_cache();
    mimic_fat_update_usb_device_is_enabled(false);
}

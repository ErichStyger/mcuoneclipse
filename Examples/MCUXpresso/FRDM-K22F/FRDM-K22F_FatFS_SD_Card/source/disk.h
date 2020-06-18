/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef DISK_H_
#define DISK_H_

#include "platform.h"
#if PL_CONFIG_USE_SD_CARD || PL_CONFIG_USE_USB_MSD
#include <stdbool.h>

typedef enum {
#if PL_CONFIG_USE_SD_CARD
  DISK_EVENT_SD_CARD_INSERTED = (1<<0),
  DISK_EVENT_SD_CARD_REMOVED = (1<<1),
  DISK_EVENT_SD_CARD_REQ_MOUNT = (1<<2),
  DISK_EVENT_SD_CARD_REQ_UNMOUNT = (1<<3),
#endif
#if PL_CONFIG_USE_USB_MSD
  DISK_EVENT_USB_MSD_INSERTED = (1<<4),
  DISK_EVENT_USB_MSD_REMOVED = (1<<5),
  DISK_EVENT_USB_MSD_REQ_MOUNT = (1<<6),
  DISK_EVENT_USB_MSD_REQ_UNMOUNT = (1<<7),
#endif
} DISK_Events;

#include "McuShell.h"
uint8_t DISK_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

#define DISK_DRIVE_SD_CARD  "0:/"
#define DISK_DRIVE_USB_MSD  "1:/"

/* checks if the device is inserted */
bool DISK_IsInserted(unsigned char *drive);

/* checks if the device is mounted and ready to use */
bool DISK_IsMounted(unsigned char *drive);

void DISK_SendEvent(DISK_Events event);

void DISK_Init(void);

#endif /* PL_CONFIG_USE_SD_CARD || PL_CONFIG_USE_USB_MSD */

#endif /* DISK_H_ */

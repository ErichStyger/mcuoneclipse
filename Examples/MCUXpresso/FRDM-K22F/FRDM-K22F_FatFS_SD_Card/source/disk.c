/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "disk.h"
#include "McuLog.h"
#include "McuRTOS.h"
#include "McuFatFS.h"
#include "host_msd_fatfs.h"

static TaskHandle_t diskTaskHandle;

bool DISK_IsDiskPresent(unsigned char *drive) {
  /* hard coded for '0' (SD card) and '1' (MSD) for now */
  if (*drive=='0') {
    return McuFatFS_isDiskPresent(drive);
  } else if (*drive=='1') {

  }
  return false;
}

void DISK_SendEvent(DISK_Events event) {
  xTaskNotify(diskTaskHandle, event, eSetBits);
}

static void DiskTask(void *pv) {
  uint32_t ulNotificationValue;
  BaseType_t res;
#if PL_CONFIG_USE_SD_CARD
  bool sdMounted = false;
  static McuFatFS_FATFS fsSdCard;
#endif
#if PL_CONFIG_USE_USB_MSD
  bool msdMounted = false;
  static McuFatFS_FATFS fsUsbMSD;
#endif
  uint8_t result;

  for(;;) {
    res = xTaskNotifyWait(
        0, /* do not clear anything on enter */
         DISK_EVENT_SD_CARD_INSERTED|DISK_EVENT_SD_CARD_REMOVED
        |DISK_EVENT_SD_CARD_REQ_MOUNT|DISK_EVENT_SD_CARD_REQ_UNMOUNT
        |DISK_EVENT_USB_MSD_INSERTED|DISK_EVENT_USB_MSD_REMOVED
        |DISK_EVENT_USB_MSD_REQ_MOUNT|DISK_EVENT_USB_MSD_REQ_UNMOUNT,
        &ulNotificationValue,
        portMAX_DELAY);
    if (res==pdTRUE) { /* notification received */
    #if PL_CONFIG_USE_SD_CARD
      if (ulNotificationValue&DISK_EVENT_SD_CARD_INSERTED) {
        McuLog_info("SD card inserted");
        DISK_SendEvent(DISK_EVENT_SD_CARD_REQ_MOUNT);
      }
      if (ulNotificationValue&DISK_EVENT_SD_CARD_REMOVED) {
        McuLog_info("SD card removed");
        DISK_SendEvent(DISK_EVENT_SD_CARD_REQ_UNMOUNT);
      }
      if (ulNotificationValue&DISK_EVENT_SD_CARD_REQ_MOUNT) {
        if (sdMounted) {
          McuLog_error("Mount request, but SD card is already mounted. Unmount it first.");
        } else {
          McuLog_info("SD card mount request");
          /* mount card */
          result = McuFatFS_CheckCardPresence(&sdMounted, (unsigned char*)DISK_DRIVE_SD_CARD, &fsSdCard, NULL);
          if (result==ERR_OK) {
            McuLog_info("SD card mounted successfully");
          } else {
            McuLog_error("failed mounting SD card");
          }
        }
      }
      if (ulNotificationValue&DISK_EVENT_SD_CARD_REQ_UNMOUNT) {
        McuLog_info("SD card unmount request");
        /* unmount sd card */
        result = McuFatFS_CheckCardPresence(&sdMounted, (unsigned char*)DISK_DRIVE_SD_CARD, &fsSdCard, NULL);
        if (result==ERR_OK) {
          McuLog_info("SD card unmounted successfully");
        } else {
          McuLog_error("failed unmounting SD card");
        }
      }
    #endif /* PL_CONFIG_USE_SD_CARD */

    #if PL_CONFIG_USE_USB_MSD
      if (ulNotificationValue&DISK_EVENT_USB_MSD_INSERTED) {
        McuLog_info("USB MSD inserted");
        DISK_SendEvent(DISK_EVENT_USB_MSD_REQ_MOUNT);
      }
      if (ulNotificationValue&DISK_EVENT_USB_MSD_REMOVED) {
        McuLog_info("USB MSD removed");
        DISK_SendEvent(DISK_EVENT_USB_MSD_REQ_UNMOUNT);
      }
      if (ulNotificationValue&DISK_EVENT_USB_MSD_REQ_MOUNT) {
        if (msdMounted) {
          McuLog_error("Mount request, but USB MSD is already mounted. Unmount it first.");
        } else {
          McuLog_info("USB MSD mount request");
          /* mount card */
          result = USB_HostMsdCheckDiskPresence(&msdMounted, (unsigned char*)DISK_DRIVE_USB_MSD, &fsUsbMSD, NULL);
          if (result==ERR_OK) {
            McuLog_info("USB MSD mounted successfully");
          } else {
            McuLog_error("failed mounting USB MSD");
          }
        }
      }
      if (ulNotificationValue&DISK_EVENT_USB_MSD_REQ_UNMOUNT) {
        McuLog_info("USB MSD unmount request");
        /* unmount USB MSD */
        result = USB_HostMsdCheckDiskPresence(&msdMounted, (unsigned char*)DISK_DRIVE_USB_MSD, &fsUsbMSD, NULL);
        if (result==ERR_OK) {
          McuLog_info("USB MSD unmounted successfully");
        } else {
          McuLog_error("failed unmounting SD card");
        }
      }
    #endif /* PL_CONFIG_USE_USB_MSD */
    }
  }
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  McuShell_SendStatusStr((unsigned char*)"disk", (unsigned char*)"disk status\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  sd drive", (unsigned char*)DISK_DRIVE_SD_CARD, io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  msd drive", (unsigned char*)DISK_DRIVE_USB_MSD, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"disk", (unsigned char*)"Group of disk commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  sd eject", (unsigned char*)"Eject SD card device\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  msd eject", (unsigned char*)"Eject USB MSD device\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t DISK_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "disk help") == 0)
  {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "disk status")==0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "disk sd eject")==0) {
    *handled = TRUE;
    DISK_SendEvent(DISK_EVENT_SD_CARD_REQ_UNMOUNT);
  } else if (McuUtility_strcmp((char*)cmd, "disk msd eject")==0) {
    *handled = TRUE;
    DISK_SendEvent(DISK_EVENT_USB_MSD_REQ_UNMOUNT);
  }
  return res;
}

void DISK_Init(void) {
  BaseType_t result;

  result =xTaskCreate(DiskTask, "DiskTask", 2500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+2, &diskTaskHandle);
  if (result!=pdPASS) {
    McuLog_fatal("Failed creating DiskTask");
    for(;;) {}
  }
}


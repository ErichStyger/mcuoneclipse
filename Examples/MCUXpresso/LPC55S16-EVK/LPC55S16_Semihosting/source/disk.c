/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_SD_CARD || PL_CONFIG_USE_USB_MSD
#include "disk.h"
#include "McuLog.h"
#include "McuRTOS.h"
#include "McuFatFS.h"
#if PL_CONFIG_USE_USB_MSD
  #include "host_msd_fatfs.h"
#endif

static TaskHandle_t diskTaskHandle;
#if PL_CONFIG_USE_SD_CARD
  static bool DISK_sdMounted = false;
#endif
#if PL_CONFIG_USE_USB_MSD
  static bool DISK_msdMounted = false;
#endif

bool DISK_IsInserted(unsigned char *drive) {
  switch(*drive) {
  #if PL_CONFIG_USE_SD_CARD
    case '0': return McuFatFS_isDiskPresent(drive);
  #endif
  #if PL_CONFIG_USE_USB_MSD
    case '1': return DISK_msdMounted; /* no special hardware pin */
  #endif
    default: break;
  }
  return false;
}

bool DISK_IsMounted(unsigned char *drive) {
  switch(*drive) {
  #if PL_CONFIG_USE_SD_CARD
    case '0': return DISK_sdMounted;
  #endif
  #if PL_CONFIG_USE_USB_MSD
    case '1': return DISK_msdMounted;
  #endif
    default: break;
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
  static McuFatFS_FATFS fsSdCard;
#endif
#if PL_CONFIG_USE_USB_MSD
  static McuFatFS_FATFS fsUsbMSD;
#endif
  uint8_t result;
  McuFatFS_FRESULT fres;

#if PL_CONFIG_USE_SD_CARD
  DISK_sdMounted = false;
#endif
#if PL_CONFIG_USE_USB_MSD
  DISK_msdMounted = false;
#endif
  for(;;) {
    res = xTaskNotifyWait(
        0, /* do not clear anything on enter */
        0 /* dummy */
    #if PL_CONFIG_USE_SD_CARD
        |DISK_EVENT_SD_CARD_INSERTED|DISK_EVENT_SD_CARD_REMOVED
        |DISK_EVENT_SD_CARD_REQ_MOUNT|DISK_EVENT_SD_CARD_REQ_UNMOUNT
    #endif
    #if PL_CONFIG_USE_USB_MSD
        |DISK_EVENT_USB_MSD_INSERTED|DISK_EVENT_USB_MSD_REMOVED
        |DISK_EVENT_USB_MSD_REQ_MOUNT|DISK_EVENT_USB_MSD_REQ_UNMOUNT
    #endif
        ,
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
        if (DISK_sdMounted) {
          McuLog_error("Mount request, but SD card is already mounted. Unmount it first.");
        } else {
          McuLog_info("SD card mount request");
          /* mount card */
          result = McuFatFS_CheckCardPresence(&DISK_sdMounted, (unsigned char*)DISK_DRIVE_SD_CARD, &fsSdCard, NULL);
          if (result==ERR_OK) {
            McuLog_info("SD card mounted successfully");
          } else {
            McuLog_error("failed mounting SD card");
          }
        }
      }
      if (ulNotificationValue&DISK_EVENT_SD_CARD_REQ_UNMOUNT) {
        McuLog_info("SD card unmount request");
        if (DISK_sdMounted) {
          /* unmount sd card */
          fres = McuFatFS_mount(NULL, (const TCHAR*)DISK_DRIVE_SD_CARD, 0);
          if (fres==FR_OK) {
            DISK_sdMounted = false;
            McuLog_info("SD card unmounted successfully");
          } else {
            McuLog_error("Failed unmounting SD card");
          }
        } else {
          McuLog_error("Unmount request, but SD card is not mounted");
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
        if (DISK_msdMounted) {
          McuLog_error("Mount request, but USB MSD is already mounted. Unmount it first.");
        } else {
          McuLog_info("USB MSD mount request");
          /* mount card */
          result = USB_HostMsdCheckDiskPresence(&DISK_msdMounted, (unsigned char*)DISK_DRIVE_USB_MSD, &fsUsbMSD, NULL);
          if (result==ERR_OK) {
            McuLog_info("USB MSD mounted successfully");
          } else {
            McuLog_error("Failed mounting USB MSD");
          }
        }
      }
      if (ulNotificationValue&DISK_EVENT_USB_MSD_REQ_UNMOUNT) {
        McuLog_info("USB MSD unmount request");
        if (DISK_msdMounted) {
          /* unmount USB MSD */
          fres = McuFatFS_mount(NULL, (const TCHAR*)DISK_DRIVE_USB_MSD, 0);
          if (fres==FR_OK) {
            DISK_msdMounted = false;
            McuLog_info("USB MSD unmounted successfully");
          } else {
            McuLog_error("Failed unmounting USB MSD");
          }
        } else {
          McuLog_error("Unmount request, but USB MSD is not mounted");
        }
      }
    #endif /* PL_CONFIG_USE_USB_MSD */
    }
  }
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[32];

  McuShell_SendStatusStr((unsigned char*)"disk", (unsigned char*)"disk status\r\n", io->stdOut);
#if PL_CONFIG_USE_SD_CARD
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"\"");
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)DISK_DRIVE_SD_CARD);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\", mounted: ");
  McuUtility_strcat(buf, sizeof(buf), DISK_sdMounted? (unsigned char*)"yes\r\n":(unsigned char*)"no\r\n");
  McuShell_SendStatusStr((unsigned char*)"  sd drive", buf, io->stdOut);
#endif
#if PL_CONFIG_USE_USB_MSD
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"\"");
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)DISK_DRIVE_USB_MSD);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\", mounted: ");
  McuUtility_strcat(buf, sizeof(buf), DISK_msdMounted? (unsigned char*)"yes\r\n":(unsigned char*)"no\r\n");
  McuShell_SendStatusStr((unsigned char*)"  msd drive", buf, io->stdOut);
#endif
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"disk", (unsigned char*)"Group of disk commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
#if PL_CONFIG_USE_SD_CARD
  McuShell_SendHelpStr((unsigned char*)"  sd mount|unmount", (unsigned char*)"Mount or unmount SD card device\r\n", io->stdOut);
#endif
#if PL_CONFIG_USE_USB_MSD
  McuShell_SendHelpStr((unsigned char*)"  msd mount|unmount", (unsigned char*)"Mount or unmount USB MSD device\r\n", io->stdOut);
#endif
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
#if PL_CONFIG_USE_SD_CARD
  } else if (McuUtility_strcmp((char*)cmd, "disk sd mount")==0) {
    *handled = TRUE;
    DISK_SendEvent(DISK_EVENT_SD_CARD_REQ_MOUNT);
  } else if (McuUtility_strcmp((char*)cmd, "disk sd unmount")==0) {
    *handled = TRUE;
    DISK_SendEvent(DISK_EVENT_SD_CARD_REQ_UNMOUNT);
#endif
#if PL_CONFIG_USE_USB_MSD
  } else if (McuUtility_strcmp((char*)cmd, "disk msd mount")==0) {
    *handled = TRUE;
    DISK_SendEvent(DISK_EVENT_USB_MSD_REQ_MOUNT);
  } else if (McuUtility_strcmp((char*)cmd, "disk msd unmount")==0) {
    *handled = TRUE;
    DISK_SendEvent(DISK_EVENT_USB_MSD_REQ_UNMOUNT);
#endif
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
#endif /* PL_CONFIG_USE_SD_CARD || PL_CONFIG_USE_USB_MSD */


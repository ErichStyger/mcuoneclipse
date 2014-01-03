/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */

#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "LED1.h"
#include "LED2.h"
#include "FAT1.h"
#include "TmDt1.h"

#define PL_HAS_SD_CARD  1 /* if we have SD card support */

#if PL_HAS_SD_CARD
  static bool cardMounted = FALSE;
  static FAT1_FATFS fileSystemObject;
#endif

uint8_t Shell_ParseCommand(const unsigned char *cmd, bool *handled, CLS1_ConstStdIOType *io)
{
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "app help")==0) {
    CLS1_SendHelpStr((unsigned char*)"app", (const unsigned char*)"Group of CLS1 commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  mount|unmount", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, "app status")==0) {
    CLS1_SendStatusStr((unsigned char*)"app", (unsigned char*)"\r\n", io->stdOut);
    CLS1_SendStatusStr((unsigned char*)"  mounted", cardMounted?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "app mount")==0) {
    *handled = TRUE;
    if (cardMounted) {
      CLS1_SendStr((unsigned char*)"card already mounted!\r\n", io->stdErr);
      return ERR_FAILED;
    }
    if (FAT1_MountFileSystem(&fileSystemObject, 0, io)!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"failed!\r\n", io->stdErr);
      return ERR_FAILED;
    } else {
      cardMounted = TRUE;
    }
  } else if (UTIL1_strcmp((char*)cmd, "app unmount")==0) {
    *handled = TRUE;
    if (!cardMounted) {
      CLS1_SendStr((unsigned char*)"card not mounted!\r\n", io->stdErr);
      return ERR_FAILED;
    }
    if (FAT1_UnMountFileSystem(0, io)!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"failed!\r\n", io->stdErr);
      return ERR_FAILED;
    } else {
      cardMounted = FALSE;
    }
  }
  return ERR_OK; /* no error */
}

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  FRTOS1_ParseCommand,
  CLS1_ParseCommand,
  Shell_ParseCommand,
  FAT1_ParseCommand,
  TmDt1_ParseCommand,
  NULL /* sentinel */
};

static portTASK_FUNCTION(ShellTask, pvParameters) {
  unsigned char buf[48];

  (void)pvParameters; /* not used */
  buf[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
#if PL_HAS_SD_CARD
  FAT1_Init();
#endif
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
    LED2_Neg();
  }
}

void SHELL_Init(void) {
  cardMounted = FALSE;
  if (FRTOS1_xTaskCreate(ShellTask, (signed char*)"Shell", configMINIMAL_STACK_SIZE+200, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}


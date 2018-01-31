/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "LED1.h"
#include "LED2.h"
#if PL_HAS_LED3
  #include "LED3.h"
#endif
#if PL_HAS_RTC
  #include "RTC1.h"
#endif
#include "TmDt1.h"
#include "MazeRace.h"
#if PL_HAS_RNET
  #include "RNET1.h"
#endif
#if PL_HAS_MUSIC
  #include "VS1.h"
  #include "Music.h"
#endif
#if PL_HAS_MIDI
  #include "MidiMusic.h"
#endif
#if PL_HAS_SD_CARD
  #include "FAT1.h"
#endif
#if PL_HAS_NEO_PIXEL
  #include "NeoPixel.h"
#endif
#if PL_HAS_LED_CUBE
  #include "LedCube.h"
#endif
#if PL_HAS_LED_FRAME
  #include "LEDFrame.h"
#endif
#include "KIN1.h"


static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
#if PL_HAS_RTC && RTC1_PARSE_COMMAND_ENABLED
  RTC1_ParseCommand,
#endif
#if PL_HAS_RNET
#if RNET1_PARSE_COMMAND_ENABLED
  RNET1_ParseCommand,
#endif
#endif
#if PL_HAS_MUSIC
#if VS1_PARSE_COMMAND_ENABLED
  VS1_ParseCommand,
#endif
  MUSIC_ParseCommand,
#endif
#if PL_HAS_SD_CARD
#if FAT1_PARSE_COMMAND_ENABLED
  FAT1_ParseCommand,
#endif
#endif
#if TmDt1_PARSE_COMMAND_ENABLED
  TmDt1_ParseCommand,
#endif
#if KIN1_PARSE_COMMAND_ENABLED
  KIN1_ParseCommand,
#endif
#if PL_HAS_MAZE_RACE
  MR_ParseCommand,
#endif
#if LED1_PARSE_COMMAND_ENABLED
  LED1_ParseCommand,
#endif
#if LED2_PARSE_COMMAND_ENABLED
  LED2_ParseCommand,
#endif
#if PL_HAS_LED3 && LED3_PARSE_COMMAND_ENABLED
  LED3_ParseCommand,
#endif
#if PL_HAS_LED_FRAME
  LEDFRAME_ParseCommand,
#endif
#if PL_HAS_NEO_PIXEL
  NEO_ParseCommand,
#endif
#if PL_HAS_LED_CUBE
  LCUBE_ParseCommand,
#endif
#if PL_HAS_MIDI
  MM_ParseCommand,
#endif
  NULL /* sentinel */
};

static void ShellTask(void *pvParameters) {
  unsigned char buf[48];
#if PL_HAS_SD_CARD
  bool cardMounted = FALSE;
  static FAT1_FATFS fileSystemObject;
#endif

  (void)pvParameters; /* not used */
  buf[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
#if PL_HAS_SD_CARD
  FAT1_Init();
#endif
  for(;;) {
#if PL_HAS_SD_CARD
    (void)FAT1_CheckCardPresence(&cardMounted, "0" /* drive */, &fileSystemObject, CLS1_GetStdio());
#endif
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  }
}

void SHELL_Init(void) {
  if (FRTOS1_xTaskCreate(ShellTask, "Shell", (800/sizeof(StackType_t)), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

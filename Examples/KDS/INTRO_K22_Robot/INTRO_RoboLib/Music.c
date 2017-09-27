/*
 * Music.c
 *
 *  Created on: 07.12.2014
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_HAS_MUSIC_SHIELD
#include "Music.h"
#include "VS1053.h"
#include "FRTOS1.h"
#include "CLS1.h"
#include "Shell.h"
#include "FAT1.h"

//#define MUSIC_DEFAULT_VOLUME  0x2020 /* not loud */
#define MUSIC_DEFAULT_VOLUME  0x0000 /* loud */

static volatile bool MUSIC_playFile = FALSE;
static unsigned char MUSIC_playFileName[16];

static const unsigned char MUSIC_ThemeFiles[][32] = {
  /* MUSIC_THEME_BREATH */        "0:\\VADER.MP3",    /* breathing */
  /* MUSIC_THEME_DARK_SIDE */     "0:\\DARKSIDE.MP3", /* you don't know the power of the dark side */
  /* MUSIC_THEME_FAILED_ME */     "0:\\FAILEDME.MP3", /* you have failed me for the last time */
  /* MUSIC_THEME_DONT_MAKE */     "0:\\DONTMAKE.MP3", /* don't make me destroy you */
  /* MUSIC_THEME_COME_BACK */     "0:\\COMEBACK.MP3", /* you should not come back */
  /* MUSIC_THEME_IMPERIAL */      "0:\\IMPERIAL.MP3", /* imperial theme */
  /* MUSIC_THEME_GIVEYOURSELF */  "0:\\GIVYRSLF.MP3", /* give yourself to the dark side */
  /* MUSIC_THEME_DAVE */          "0:\\DAVE.MP3",
  /* MUSIC_THEME_LASER_LEFT */    "0:\\lightsbr.MP3",
  /* MUSIC_THEME_LASER_RIGHT */   "0:\\lightsbr.MP3",
  /* MUSIC_THEME_LASER_BOTH */    "0:\\lightsbr.MP3",
  /* MUSIC_THEME_LAST */
};

bool MUSIC_IsPlaying(void) {
  return MUSIC_playFile;
}

void MUSIC_Start(void) {
  MUSIC_playFile = TRUE;
}

void MUSIC_Stop(void) {
  MUSIC_playFile = FALSE;
}

static uint8_t MUSIC_PlaySong(const uint8_t *fileName, const CLS1_StdIOType *io) {
  UINT bytesRead;
  uint8_t readBuf[32];
  uint8_t res = ERR_OK;
  static FIL fp;

  if (io!=NULL) {
    CLS1_SendStr("Playing file '", io->stdOut);
    CLS1_SendStr(fileName, io->stdOut);
    CLS1_SendStr("'\r\n", io->stdOut);
  }
  if (FAT1_open(&fp, fileName, FA_READ)!=FR_OK) {
    if (io!=NULL) {
      CLS1_SendStr("ERR: Failed to open song file\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  for(;;) { /* breaks */
    if (!MUSIC_playFile) {
      break;
    }
    bytesRead = 0;
    if (FAT1_read(&fp, readBuf, sizeof(readBuf), &bytesRead)!=FR_OK) {
      if (io!=NULL) {
        CLS1_SendStr("ERR: Failed to read file\r\n", io->stdErr);
      }
      res = ERR_FAILED;
      break;
    }
    if (bytesRead==0) { /* end of file? */
      break;
    }
    while(!VS_Ready()) {
      FRTOS1_vTaskDelay(10/portTICK_PERIOD_MS);
    }
    VS_SendData(readBuf, sizeof(readBuf));
  }
  /* closing file */
  (void)FAT1_close(&fp);
  if (MUSIC_playFile) {
    VS_StartSong();
  } else {
    VS_StopSong();
  }
  CLS1_SendStr("Playing file done!\r\n", io->stdOut);
  return res;
}

void MUSIC_PlayTheme(MUSIC_Theme theme) {
  if (MUSIC_playFile) {
    MUSIC_Stop();
    FRTOS1_vTaskDelay(50/portTICK_PERIOD_MS);
  }
  if (theme<MUSIC_THEME_LAST) {
    UTIL1_strcpy(MUSIC_playFileName, sizeof(MUSIC_playFileName), MUSIC_ThemeFiles[theme]);
    MUSIC_Start();
  }
}

static portTASK_FUNCTION(MusicTask, pvParameters) {
  (void)pvParameters; /* not used */
  VS_SetVolume(MUSIC_DEFAULT_VOLUME);
  for(;;) {
    if (MUSIC_playFile) {
      MUSIC_PlaySong(MUSIC_playFileName, SHELL_GetStdio());
      MUSIC_playFile = FALSE;
    }
    FRTOS1_vTaskDelay(50/portTICK_PERIOD_MS);
  } /* for */
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[24];
  uint16_t val;

  CLS1_SendStatusStr((unsigned char*)"music", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  playing", MUSIC_playFile?"yes\r\n":"no\r\n", io->stdOut);

  return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"music", (unsigned char*)"Group of music commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  play <file>", (unsigned char*)"Play song file\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  stop", (unsigned char*)"Stop playing file\r\n", io->stdOut);
  return ERR_OK;
}


uint8_t MUSIC_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  const uint8_t *p;
  uint32_t val32u;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "music help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "music status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strncmp((char*)cmd, "music play ", sizeof("music play ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("music play ")-1;
    UTIL1_strcpy(MUSIC_playFileName, sizeof(MUSIC_playFileName), p);
    MUSIC_Start();
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "music stop")==0) {
    *handled = TRUE;
    MUSIC_Stop();
    return ERR_OK;
  }
  return ERR_OK;
}

void MUSIC_Deinit(void) {
  /* nothing */
}

void MUSIC_Init(void) {
  VS_Init();
  MUSIC_playFile = FALSE;
  if (FRTOS1_xTaskCreate(MusicTask, "Music", configMINIMAL_STACK_SIZE+20, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
#endif /* PL_HAS_MUSIC_SHIELD */

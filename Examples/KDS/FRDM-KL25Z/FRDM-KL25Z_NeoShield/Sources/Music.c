/*
 * Music.c
 *
 *  Created on: 07.12.2014
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_HAS_MUSIC
#include "Music.h"
#include "FRTOS1.h"
#include "CLS1.h"
#include "Shell.h"
#include "FAT1.h"
#include "VS1.h"

//#define MUSIC_DEFAULT_VOLUME  0x20 /* not loud */
#define MUSIC_DEFAULT_VOLUME  0x00 /* loud */

static volatile bool MUSIC_isPlaying = FALSE;
static unsigned char MUSIC_playFileName[16];
static xSemaphoreHandle MUSIC_StartSem = NULL;
static xSemaphoreHandle MUSIC_StopSem = NULL;

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
  /* MUSIC_THEME_WHOSH1 */        "0:\\woosh_3.mp3",
  /* MUSIC_THEME_LAST */
};

bool MUSIC_IsPlaying(void) {
  return MUSIC_isPlaying;
}

void MUSIC_Start(void) {
  (void)xSemaphoreGive(MUSIC_StartSem);
}

void MUSIC_Stop(void) {
  (void)xSemaphoreGive(MUSIC_StopSem);
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
  MUSIC_isPlaying = TRUE;
  for(;;) { /* breaks */
    if (FRTOS1_xSemaphoreTake(MUSIC_StopSem, 0)==pdTRUE) {
      CLS1_SendStr("Stop playing!\r\n", io->stdOut);
      MUSIC_isPlaying = FALSE;
      break; /* stop playing */
    }
    if (FRTOS1_xSemaphoreTake(MUSIC_StartSem, 0)==pdTRUE) {
      xSemaphoreGive(MUSIC_StartSem); /* re-give token */
      CLS1_SendStr("Start while playing!\r\n", io->stdOut);
      MUSIC_isPlaying = FALSE;
      break; /* stop playing */
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
    while(!VS1_IsReady()) {
      FRTOS1_vTaskDelay(1/portTICK_RATE_MS);
    }
    VS1_SendData(readBuf, sizeof(readBuf));
  }
  /* closing file */
  (void)FAT1_close(&fp);
  if (MUSIC_isPlaying) {
    VS1_StartSong();
    CLS1_SendStr("Playing file done!\r\n", io->stdOut);
  } else {
    VS1_TerminateStreams();
    CLS1_SendStr("Stopped!\r\n", io->stdOut);
  }
  MUSIC_isPlaying = FALSE;
  return res;
}

void MUSIC_PlayTheme(MUSIC_Theme theme) {
  if (theme<MUSIC_THEME_LAST) {
    UTIL1_strcpy(MUSIC_playFileName, sizeof(MUSIC_playFileName), MUSIC_ThemeFiles[theme]);
    MUSIC_Start();
  }
}

static portTASK_FUNCTION(MusicTask, pvParameters) {
  (void)pvParameters; /* not used */
  VS1_SetVolume(MUSIC_DEFAULT_VOLUME, MUSIC_DEFAULT_VOLUME);
  for(;;) {
    while (FRTOS1_xSemaphoreTake(MUSIC_StopSem, 0)==pdTRUE) {
      /* consume any stop signal */
    }
    if (FRTOS1_xSemaphoreTake(MUSIC_StartSem, portMAX_DELAY)==pdTRUE) {
      MUSIC_PlaySong(MUSIC_playFileName, CLS1_GetStdio());
    }
    FRTOS1_vTaskDelay(5/portTICK_RATE_MS);
  } /* for */
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[24];
  uint16_t val;

  CLS1_SendStatusStr((unsigned char*)"music", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  is playing", MUSIC_isPlaying?"yes\r\n":"no\r\n", io->stdOut);
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
  FRTOS1_vSemaphoreCreateBinary(MUSIC_StartSem);
  if (MUSIC_StartSem==NULL) { /* semaphore creation failed */
    for(;;){} /* error */
  }
  FRTOS1_vQueueAddToRegistry(MUSIC_StartSem, "MusicStart");
  FRTOS1_xSemaphoreTake(MUSIC_StartSem, 0); /* empty semaphore */

  FRTOS1_vSemaphoreCreateBinary(MUSIC_StopSem);
  if (MUSIC_StopSem==NULL) { /* semaphore creation failed */
    for(;;){} /* error */
  }
  FRTOS1_vQueueAddToRegistry(MUSIC_StopSem, "MusicStop");
  FRTOS1_xSemaphoreTake(MUSIC_StopSem, 0); /* empty semaphore */

  MUSIC_isPlaying = FALSE;
  if (FRTOS1_xTaskCreate(MusicTask, "Music", configMINIMAL_STACK_SIZE+200, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
#endif /* PL_HAS_MUSIC_SHIELD */

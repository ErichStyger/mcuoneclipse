/** ###################################################################
**     Filename  : SDcard.C
**     Project   : TWR_LCD_JM128
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 24.01.2010, 11:19
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE SDcard */

#include "Platform.h"

#if PL_HAS_SD_DEMO
#include "SDcard.h"
#include "App.h"
#if PL_USE_RTOS
  #include "FRTOS1.h"
#endif
#include "Cour08n.h"
#include "Cour10n.h"
#include "Helv10n.h"
#include "Helv12n.h"
#include "Helv14n.h"
#include "FAT1.h"
#include "UTIL1.h"
#include "string.h"
#include "EVNT1.h"

#if PL_USE_SINGLE_FONT /* use only one font */
  #define FONT_10             PL_FONT()
  #define FONT_12             PL_FONT()
  #define FONT_14             PL_FONT()
  #define FONT_C08N           PL_FONT()
#else
  #define FONT_10             Helv10n_GetFont()
  #define FONT_12             Helv12n_GetFont()
  #define FONT_14             Helv14n_GetFont()
  #define FONT_C08N           Cour08n_GetFont()
#endif

static SDC_WindowDesc *SDC_descP;
#define SDC_TEXT_BUF_SIZE  1024  /* buffer size for the text in the UI */
static char *SDC_WindowTextBufP = NULL; /* buffer for the text in the UI */

static FATFS fs;
static DWORD drive_sector_count;
static WORD drive_sector_size;
static DWORD drive_block_size;
static BYTE drive_type;
static BYTE drive_CSD[16];
static BYTE drive_CID[16];
static BYTE drive_OCR[4];
static BYTE drive_SDSTAT[64];

static FILINFO Finfo;
static FIL fo; /* global file object as this is a rather big chunk of memory! */

static void Fatal(const char *msg) {
  (void)msg;
  for(;;) {  }
}

static void ErrMsg(const char *msg, FRESULT err) {
  (void)msg; (void)err; /* to avoid compiler warning */
  Fatal(msg);
}

static byte SDC_Open(void) {
  if (FAT1_mount(0, &fs) != FR_OK) {
    Fatal("mount failed");
    return ERR_FAULT;
  }
  return ERR_OK;
}

static byte SDC_Close(void) {
  if (FAT1_mount(0, NULL) != FR_OK) {
    Fatal("unmount failed");
    return ERR_FAULT;
  }
  return ERR_OK;
}

static void SDC_ReadFile(void) {
  FAT1_FRESULT fres;
  UINT nofRead = 0;
  BYTE buf[15];
  BYTE path[12] = "\\test.txt";

  if ((fres=FAT1_open(&fo, (char*)path, FA_READ)) == FR_OK) {
    if ((fres=FAT1_read(&fo, buf, sizeof(buf), &nofRead)) != FR_OK) {
      ErrMsg("failed to read file", fres);
    }
    if ((fres=FAT1_close(&fo)) != FR_OK) {
      ErrMsg("failed to close file", fres);
    }
  } else {
    ErrMsg("failed to open file", fres);
    if (fres == FR_NO_FILESYSTEM) { /* create new file system */
      /* NYI */
    }
  }
}

static BYTE SDC_PrintDir(char *buf, size_t bufSize) {
  FAT1_FRESULT fres;
	DWORD p1;
	UINT s1, s2;
	DWORD sect = 0;
#if !_FS_READONLY
	FATFS *fs;
#endif
	DIR dir;				/* Directory object */
	BYTE path[5] = "\\";

  fres = FAT1_opendir(&dir, (char*)path);
  if (fres != FR_OK) {
    return ERR_FAULT;
  }

	p1 = s1 = s2 = 0;
#if _USE_LFN
	Finfo.lfname = Lfname;
	Finfo.lfsize = sizeof(Lfname);
#endif
	for(;;) {
		fres = FAT1_readdir(&dir, &Finfo);
		if ((fres != FR_OK) || !Finfo.fname[0]) break;
		if (Finfo.fattrib & AM_DIR) {
			s2++;
		} else {
			s1++;
			p1 += Finfo.fsize;
		}
    UTIL1_strcat(buf, bufSize, ((Finfo.fattrib & AM_DIR) ? "D" : "-"));
    UTIL1_strcat(buf, bufSize, ((Finfo.fattrib & AM_RDO) ? "R" : "-"));
    UTIL1_strcat(buf, bufSize, ((Finfo.fattrib & AM_HID) ? "H" : "-"));
    UTIL1_strcat(buf, bufSize, ((Finfo.fattrib & AM_SYS) ? "S" : "-"));
    UTIL1_strcat(buf, bufSize, ((Finfo.fattrib & AM_ARC) ? "A" : "-"));
    UTIL1_strcat(buf, bufSize, " ");
    UTIL1_strcatNum16sFormatted(buf, bufSize, (int16_t)((Finfo.fdate >> 9) + 1980), ' ', 4); /* year */
    UTIL1_strcat(buf, bufSize, "-");
    UTIL1_strcatNum16sFormatted(buf, bufSize, (int16_t)((Finfo.fdate >> 5) & 15), '0', 2); /* month */
    UTIL1_strcat(buf, bufSize, "-");
    UTIL1_strcatNum16sFormatted(buf, bufSize, (int16_t)(Finfo.fdate & 31), '0', 2); /* day */
    UTIL1_strcat(buf, bufSize, " ");
    UTIL1_strcatNum16sFormatted(buf, bufSize, (int16_t)((Finfo.ftime >> 11)), '0', 2); /* hour */
    UTIL1_strcat(buf, bufSize, ":");
    UTIL1_strcatNum16sFormatted(buf, bufSize, (int16_t)((Finfo.ftime >> 5) & 63), '0', 2); /* minute */
    UTIL1_strcat(buf, bufSize, " ");
    UTIL1_strcatNum32uFormatted(buf, bufSize, Finfo.fsize, ' ', 10); /* size */
    UTIL1_strcat(buf, bufSize, " ");
    UTIL1_strcat(buf, bufSize, Finfo.fname);
#if _USE_LFN
    UTIL1_strcat(buf, bufSize, Lfname);
#endif
    UTIL1_strcat(buf, bufSize, "\n");
	}
	UTIL1_strcatNum32u(buf, bufSize, (uint32_t)s1);
	UTIL1_strcat(buf, bufSize, " File(s), ");
	UTIL1_strcatNum32s(buf, bufSize, (long)p1);
	UTIL1_strcat(buf, bufSize, " bytes total\n");
	UTIL1_strcatNum32u(buf, bufSize, (uint32_t)s2);
	UTIL1_strcat(buf, bufSize, " Dir(s)");

#if !_FS_READONLY
	if (f_getfree((const char*)&path, &p1, &fs) == FR_OK) {
  	UTIL1_strcat(buf, bufSize, ", ");
  	UTIL1_strcatNum32s(buf, bufSize, (long)(p1*fs->csize/2));
  	UTIL1_strcat(buf, bufSize, " K bytes free");
	}
#endif
	return ERR_OK;
}

static const byte data1K[] = {
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
};


#if !_FS_READONLY
static byte SDC_AppendToFile(const char *path, const char *txt) {
  FAT1_FRESULT fres;
  UINT nof = 0;
  size_t len;
  //char buf[32];

  /* open file for write, create the file if it does not exist */
  if ((fres=FAT1_open(&fo, (char*)path, FA_WRITE|FA_OPEN_ALWAYS)) == FR_OK) {
    if ((fres=FAT1_lseek(&fo, fo.fsize)) != FR_OK || fo.fptr != fo.fsize) {
      //Fatal("lseek failed");
      return ERR_FAULT;
    }
    len = strlen(txt);
    if ((fres=FAT1_write(&fo, txt, len, &nof)) != FR_OK) {
      //UTIL1_strcpy(buf, sizeof(buf), "fwrite failed: ");
      //UTIL1_strcat(buf, sizeof(buf), path);
      //Fatal(buf);
      return ERR_FAULT;
    }
#if 1
    {
      byte n;
      for (n=0;n<16;n++) {
        if ((fres=FAT1_write(&fo, data1K, sizeof(data1K), &nof)) != FR_OK) {
          //UTIL1_strcpy(buf, sizeof(buf), "fwrite failed: ");
          //UTIL1_strcat(buf, sizeof(buf), path);
          //Fatal(buf);
          return ERR_FAULT;
        }
      } /* for */
    }
#endif
    if ((fres=FAT1_close(&fo)) != FR_OK) {
      //UTIL1_strcpy(buf, sizeof(buf), "fclose failed: ");
      //UTIL1_strcat(buf, sizeof(buf), path);
      //Fatal(buf);
      return ERR_FAULT;
    }
  } else {
    //UTIL1_strcpy(buf, sizeof(buf), "fopen failed: ");
    //UTIL1_strcat(buf, sizeof(buf), path);
    //Fatal(buf);
    return ERR_FAULT;
  }
  return ERR_OK;
}
#endif

#if PL_HAS_SD_WRITE
static byte LogBuf[1024];
static byte LogDataToFile(int i) {
  TIMEREC time;
  DATEREC date;

  (void)TmDt1_GetTime(&time);
  (void)TmDt1_GetDate(&date);
  UTIL1_strcpy(LogBuf, sizeof(LogBuf), "\r\n");
  UTIL1_strcatNum16sFormatted(LogBuf, sizeof(LogBuf), (int16_t)i, '0', 4);
  UTIL1_chcat(LogBuf, sizeof(LogBuf), ' ');
  UTIL1_strcatNum16sFormatted(LogBuf, sizeof(LogBuf), (int16_t)date.Year, '0', 4);
  UTIL1_chcat(LogBuf, sizeof(LogBuf), '-');
  UTIL1_strcatNum16sFormatted(LogBuf, sizeof(LogBuf), date.Month, '0', 2);
  UTIL1_chcat(LogBuf, sizeof(LogBuf), '-');
  UTIL1_strcatNum16sFormatted(LogBuf, sizeof(LogBuf), date.Day, '0', 2);
  UTIL1_chcat(LogBuf, sizeof(LogBuf), ' ');
  UTIL1_strcatNum16sFormatted(LogBuf, sizeof(LogBuf), time.Hour, '0', 2);
  UTIL1_chcat(LogBuf, sizeof(LogBuf), ':');
  UTIL1_strcatNum16sFormatted(LogBuf, sizeof(LogBuf), time.Min, '0', 2);
  UTIL1_chcat(LogBuf, sizeof(LogBuf), ':');
  UTIL1_strcatNum16sFormatted(LogBuf, sizeof(LogBuf), time.Sec, '0', 2);
  UTIL1_chcat(LogBuf, sizeof(LogBuf), ':');
  UTIL1_strcatNum16sFormatted(LogBuf, sizeof(LogBuf), time.Sec100, '0', 2);
  UTIL1_chcat(LogBuf, sizeof(LogBuf), ' ');
  UTIL1_strcat(LogBuf, sizeof(LogBuf), "Data: ");

  if (SDC_Open()==ERR_OK) {
    byte res;

    res = SDC_AppendToFile("\\data.txt", LogBuf);
    if (SDC_Close()!=ERR_OK) {
      return ERR_FAULT;
    }
    if (res != ERR_OK) {
      return ERR_FAULT;
    } else {
      return ERR_OK;
    }
    return ERR_OK;
  } else {
    return ERR_FAULT;
  }
}
#endif


static void SDC_DumpFile(const char *path) {
  FAT1_FRESULT fres;
  UINT nofRead = 0;
  BYTE buf[64];

  UTIL1_strcpy((char*)buf, sizeof(buf), "Dumping file: ");
  UTIL1_strcat((char*)buf, sizeof(buf), path);
  if ((fres=FAT1_open(&fo, (char*)path, FA_READ)) == FR_OK) {
    do {
      nofRead = 0;
      fres=FAT1_read(&fo, buf, sizeof(buf), &nofRead);
      if (fres != FR_OK) {
        Fatal("fread failed");
      } else {
        /* write file content to terminal */
      }
    } while(nofRead>0 && fres==FR_OK);
    if ((fres=FAT1_close(&fo)) != FR_OK) {
      Fatal("fclose failed");
    }
  } else {
    UTIL1_strcpy((char*)buf, sizeof(buf), "fopen failed: ");
    UTIL1_strcat((char*)buf, sizeof(buf), path);
    Fatal((char*)buf);
  }
}

static void SDC_DeleteFile(const char *path) {
  FAT1_FRESULT fres;
  UINT nofRead = 0;
  BYTE buf[36];

  UTIL1_strcpy((char*)buf, sizeof(buf), "Deleting file: ");
  UTIL1_strcat((char*)buf, sizeof(buf), path);
  if ((fres=FAT1_unlink(path)) != FR_OK) {
    UTIL1_strcpy((char*)buf, sizeof(buf), "unlink failed: ");
    UTIL1_strcat((char*)buf, sizeof(buf), path);
    Fatal((char*)buf);
  }
}

static void PrintDir(void) {
  char *bufP;

  UI1_ChangeText(&SDC_descP->window, (UI1_Element*)&SDC_descP->txt, SDC_TEXT_BUF_SIZE, "reading directory..."); /* clear text */
  bufP = FRTOS1_pvPortMalloc(SDC_TEXT_BUF_SIZE);
  if (bufP == NULL) {
    UI1_ChangeText(&SDC_descP->window, (UI1_Element*)&SDC_descP->txt, SDC_TEXT_BUF_SIZE, "*** out of memory ***");
    return;
  }
  *bufP = '\0';
  if (SDC_Open()==ERR_OK) {
    if (SDC_PrintDir(bufP, SDC_TEXT_BUF_SIZE) != ERR_OK) {
      UTIL1_strcat(bufP, SDC_TEXT_BUF_SIZE, "PrintDir failed");
    }
    (void)SDC_Close();
  } else {
    UTIL1_strcat(bufP, SDC_TEXT_BUF_SIZE, "Open failed");
  }
  UI1_ChangeText(&SDC_descP->window, (UI1_Element*)&SDC_descP->txt, SDC_TEXT_BUF_SIZE, bufP);
  FRTOS1_vPortFree(bufP); /* free memory */
}

static portTASK_FUNCTION(TaskSDcard, pvParameters) {
  (void)pvParameters;
  //bool SDisInit;
  byte maxInitRetry = 10;
  bool updateCardStateUI;

  UI1_CheckBoxSet(&SDC_descP->chkBoxCardPresent, SD1_CardPresent());
  UI1_CheckBoxSet(&SDC_descP->chkBoxWriteProtected, SD1_isWriteProtected());
  updateCardStateUI = TRUE;

  if (SDC_WindowTextBufP==NULL) {
    SDC_WindowTextBufP = FRTOS1_pvPortMalloc(SDC_TEXT_BUF_SIZE); /* allocate dynamic memory */
  }
  if (SDC_WindowTextBufP==NULL) { /* no memory :-( */
   for(;;) {}
  }
  *SDC_WindowTextBufP = '\0';
#if 0
  UI1_ChangeText(&SDC_descP->window, (UI1_Element*)&SDC_descP->txt, SDC_TEXT_BUF_SIZE, "initializing SD card driver...");
  while (maxInitRetry>0) {
    if (SD1_Init()==ERR_OK) {
      break;
    }
    maxInitRetry--;
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  } /* while */
  SDisInit = (bool)(maxInitRetry>0);
  if (!SDisInit) {
    Fatal("Failed SD card init!");
    UI1_ChangeText(&SDC_descP->window, (UI1_Element*)&SDC_descP->txt, SDC_TEXT_BUF_SIZE, "SD_Init failed!");
  } else {
    UI1_ChangeText(&SDC_descP->window, (UI1_Element*)&SDC_descP->txt, SDC_TEXT_BUF_SIZE, "...done!");
  }
#endif
  for(;;) {
    if (updateCardStateUI) { /* update card state UI elements */
      UI1_UpdateElement(&SDC_descP->window, (UI1_Element*)&SDC_descP->chkBoxCardPresent);
      UI1_UpdateElement(&SDC_descP->window, (UI1_Element*)&SDC_descP->chkBoxWriteProtected);
    }
    if (SD1_CardPresent() && !UI1_CheckBoxIsChecked(&SDC_descP->chkBoxCardPresent)) {
      /* card just has been inserted */
      UI1_CheckBoxSet(&SDC_descP->chkBoxCardPresent, TRUE);
      UI1_CheckBoxSet(&SDC_descP->chkBoxWriteProtected, SD1_isWriteProtected());
      updateCardStateUI = TRUE;
      PrintDir();
    } else if (!SD1_CardPresent() && UI1_CheckBoxIsChecked(&SDC_descP->chkBoxCardPresent)) {
      /* card just has been removed */
      UI1_CheckBoxSet(&SDC_descP->chkBoxCardPresent, FALSE);
      UI1_CheckBoxSet(&SDC_descP->chkBoxWriteProtected, FALSE);
      UI1_ChangeText(&SDC_descP->window, (UI1_Element*)&SDC_descP->txt, SDC_TEXT_BUF_SIZE, ""); /* clear text */
      updateCardStateUI = TRUE;
    } else {
      updateCardStateUI = FALSE;
    }
    if (EVNT1_GetEvent(EVNT1_APP_MODE_CHANGE)) { /* request to close application */
      EVNT1_ClearEvent(EVNT1_APP_MODE_CHANGE); /* reset event flag */
      FRTOS1_vTaskDelete(NULL); /* kill ourself */
    }
    FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
  } /* for */
}

static void sdW_WindowCallback(UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind kind, UI1_Pvoid data) {
  (void)window;
  (void)data; /* unused argument */
  if (kind==UI1_EVENT_CLICK) {
    if (UI1_EqualElement(element, &SDC_descP->iconClose)) {
      EVNT1_SetEvent(EVNT1_APP_MODE_CHANGE); /* request to close application */
      while(EVNT1_GetEvent(EVNT1_APP_MODE_CHANGE)) {
        /* wait until task has killed itself */
        FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
      }
      APP_SetApplicationMode(APP_MODE_MAIN_MENU);
      return;
    } else if (UI1_EqualElement(element, &SDC_descP->btnDirectory)) {
      PrintDir();
    } else if (UI1_EqualElement(element, &SDC_descP->btnDataFile)) {
#if PL_HAS_SD_WRITE
      if (SD1_CardPresent() && !SD1_isWriteProtected()) {
        int i;
        #define _LOG_NOF_RUN  20
        char buf[10];

        UI1_ChangeText(&SDC_descP->window, (UI1_Element*)&SDC_descP->txt, SDC_TEXT_BUF_SIZE, "starting LogDataToFile...");
        for(i=0;i<_LOG_NOF_RUN;i++) {
          if (LogDataToFile(i) != ERR_OK) {
            break;
          }
          buf[0] = '\0';
          UTIL1_strcatNum16s(buf, sizeof(buf), (int16_t)i);
          UTIL1_strcat(buf, sizeof(buf), " of ");
          UTIL1_strcatNum16s(buf, sizeof(buf), _LOG_NOF_RUN);
          UI1_ChangeText(&SDC_descP->window, (UI1_Element*)&SDC_descP->txt, SDC_TEXT_BUF_SIZE, buf);
        }
        if (i==_LOG_NOF_RUN) {
          UI1_ChangeText(&SDC_descP->window, (UI1_Element*)&SDC_descP->txt, SDC_TEXT_BUF_SIZE, "LogDataToFile success!");
        } else {
          UI1_ChangeText(&SDC_descP->window, (UI1_Element*)&SDC_descP->txt, SDC_TEXT_BUF_SIZE, "LogDataToFile failure!");
        }
      } else {
        UI1_ChangeText(&SDC_descP->window, (UI1_Element*)&SDC_descP->txt, SDC_TEXT_BUF_SIZE, "Card write protected or not ready!");
      }
#endif
    }
  }
}

static void SDC_CreateScreen(void) {
  UI1_PixelDim h, yPos, xPos;

  UI1_CreateScreen(&SDC_descP->screen, UI1_COLOR_WHITE);
  (void)UI1_CreateWindow(&SDC_descP->screen, &SDC_descP->window, UI1_COLOR_BRIGHT_YELLOW, 0, 0, UI1_GetWidth(), UI1_GetHeight());
  /* UI1_WindowSetBorder(&SDC_descP->window); */
  (void)UI1_CreateHeader(&SDC_descP->window, &SDC_descP->header, "SD Card", FONT_10, UI1_COLOR_BLUE);
  UI1_ChangeTextFgColor(&SDC_descP->header.element, UI1_COLOR_WHITE);
  UI1_SetWindowEventCallback(&SDC_descP->window, sdW_WindowCallback);
  /* Icon: Close */
  h = (UI1_PixelDim)(UI1_GetElementHeight(&SDC_descP->header));
  (void)UI1_CreateIcon(&SDC_descP->window, &SDC_descP->iconClose, 1, 1, (UI1_PixelDim)(h-2), (UI1_PixelDim)(h-2), UI1_ICON_CLOSE);
  SDC_descP->iconClose.element.prop.flags |= UI1_FLAGS_ALIGN_RIGHT;
  UI1_OnWindowResize(&SDC_descP->window); /* right align element(s) if needed */
  UI1_ChangeElementColor(&SDC_descP->iconClose, UI1_COLOR_BLUE);
  UI1_ChangeIconFgColor(&SDC_descP->iconClose, UI1_COLOR_WHITE);
  UI1_EnableElementSelection(&SDC_descP->iconClose);

  /* DIR button */
  yPos = (UI1_PixelDim)(UI1_GetElementHeight(&SDC_descP->header)+3);
  xPos = 5;
  (void)UI1_CreateButton(&SDC_descP->window, &SDC_descP->btnDirectory, xPos, yPos, 0, 0, "DIR", FONT_10, UI1_COLOR_BRIGHT_BLUE);
  UI1_EnableElementSelection(&SDC_descP->btnDirectory);

  /* Data file button */
  xPos = (UI1_PixelDim)(UI1_GetElementPosX(&SDC_descP->btnDirectory)+UI1_GetElementWidth(&SDC_descP->btnDirectory)+5);
  (void)UI1_CreateButton(&SDC_descP->window, &SDC_descP->btnDataFile, xPos, yPos, 0, 0, "DATA", FONT_10, UI1_COLOR_BRIGHT_BLUE);
  UI1_EnableElementSelection(&SDC_descP->btnDataFile);

  /* checkbox cardPresent */
  xPos = (UI1_PixelDim)(UI1_GetElementPosX(&SDC_descP->btnDataFile)+UI1_GetElementWidth(&SDC_descP->btnDataFile)+5);
  (void)UI1_CreateCheckBox(&SDC_descP->window, &SDC_descP->chkBoxCardPresent,
    xPos, yPos, 0, 0, UI1_COLOR_BLACK, UI1_COLOR_WHITE, "Card present", FONT_10, UI1_COLOR_BRIGHT_YELLOW);
  UI1_CheckBoxSet(&SDC_descP->chkBoxCardPresent, FALSE);

  /* checkbox writeProtected */
  xPos = (UI1_PixelDim)(UI1_GetElementPosX(&SDC_descP->chkBoxCardPresent)+UI1_GetElementWidth(&SDC_descP->chkBoxCardPresent)+5);
  (void)UI1_CreateCheckBox(&SDC_descP->window, &SDC_descP->chkBoxWriteProtected,
    xPos, yPos, 0, 0, UI1_COLOR_BLACK, UI1_COLOR_WHITE, "Write protected", FONT_10, UI1_COLOR_BRIGHT_YELLOW);
  UI1_CheckBoxSet(&SDC_descP->chkBoxWriteProtected, FALSE);

  yPos += (UI1_PixelDim)(UI1_GetElementHeight(&SDC_descP->btnDirectory)+3);

  /* status text */
  if (SDC_WindowTextBufP==NULL) {
    SDC_WindowTextBufP = FRTOS1_pvPortMalloc(SDC_TEXT_BUF_SIZE); /* allocate dynamic memory */
  }
  if (SDC_WindowTextBufP==NULL) { /* memory allocation failed */
    return; /* what else should we do? */
  }
  *SDC_WindowTextBufP = '\0';
  (void)UI1_CreateText(&SDC_descP->window, &SDC_descP->txt, 2, yPos, 0, 0, SDC_WindowTextBufP, FONT_C08N);

  /* update the screen */
  UI1_UpdateScreen(&SDC_descP->screen);
}

void SDC_StartTask(SDC_WindowDesc *desc) {
  signed portBASE_TYPE res;
  SDC_descP = desc; /* store pointer */

  SDC_CreateScreen();
#if PL_HAS_SD_WRITE
  res = FRTOS1_xTaskCreate(TaskSDcard, (signed portCHAR *)"SD Card", configMINIMAL_STACK_SIZE+500, NULL, tskIDLE_PRIORITY+1, NULL);
#else
  res = FRTOS1_xTaskCreate(TaskSDcard, (signed portCHAR *)"SD Card", configMINIMAL_STACK_SIZE+200, NULL, tskIDLE_PRIORITY+1, NULL);
#endif
  if (res == pdPASS) {
    /* everything ok */
  }
}

static byte errCNT;
void SDC_Err(void) {
  errCNT++;
}

#endif /* PL_HAS_SD_DEMO */

/* END SDcard */

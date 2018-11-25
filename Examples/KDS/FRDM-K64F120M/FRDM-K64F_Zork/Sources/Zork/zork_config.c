/*
 * zork_config.c
 *
  *      Author: Erich Styger
 */

#include "zork_config.h"
#include "CLS1.h"
#include "UTIL1.h"
#if USE_FATFS
  #include "FAT1.h"
#endif
#if USE_MCURSES
  #include "../mcurses/mcurses.h"
#endif

/* saving is done in dverb2.c */
/* note: some output code is in supp.c */


unsigned CLS1_fprintf(void *stream, const char *fmt, ...)
{
  va_list args;
  unsigned int count = 0;

  va_start(args,fmt);
  count = XF1_xvformat(CLS1_printfPutChar, (void*)CLS1_GetStdio()->stdOut, fmt, args);
  va_end(args);
  return count;
}


#if USE_FATFS
  static FAT1_FATFS mountDesc;
  static FIL dtextcFileDesc; /* file handle for the data file */
  static FIL dsaveFileDesc; /* file handle for the save file */

  int FatFsGetc(FIL *f) {
    unsigned char ch;
    int nofRead;
    FRESULT res;

    res = FAT1_read(f, &ch, 1, &nofRead);
    if (nofRead!=1 || res!=FR_OK) {
      return -1;
    }
    return ch;
  }

  int FatFsFtell(FIL *f) {
    return FAT1_f_tell(f);
  }

  int FatFsFClose(FIL *f) {
    return FAT1_close(f)==FR_OK;
  }

  int FatFsFSeek(FIL *f, int pos, int option) {
    if (FAT1_lseek(f, pos)!=FR_OK) {
      return EOF; /* failure */
    }
    return 0;
  }

  FIL *FatFsFOpen(const char *path, char *options) {
    BYTE mode;
    FIL *fileHndl = NULL;

    if (UTIL1_strcmp(options, "rb")==0) {
      mode = FA_OPEN_ALWAYS|FA_READ;
    } else if (UTIL1_strcmp(options, "wb")==0) {
      mode = FA_OPEN_ALWAYS|FA_WRITE;
    } else { /* default? */
      CLS1_SendStr("Failed detecting file mode!\r\n", CLS1_GetStdio()->stdErr);
      return NULL;
    }
    if (UTIL1_strcmp(path, SAVEFILE)==0) {
      fileHndl = &dsaveFileDesc;
    } else if (UTIL1_strcmp(path, TEXTFILE)==0) {
      fileHndl = &dtextcFileDesc;
    } else {
      return NULL;
    }
    if (FAT1_open(fileHndl, path, mode) == FR_OK) {
      return fileHndl;
    }
    return NULL;
  }

  size_t FatFsFRead(void *ptr, size_t size, size_t nmemb, FIL *stream) {
    FRESULT res;
    UINT nofRead;

    res = FAT1_read(stream, ptr, size*nmemb, &nofRead);
    if (res!=FR_OK) {
      return 0;
    }
    return nofRead;
  }

  size_t FatFsFWrite(const void *ptr, size_t size, size_t nmemb, FIL *stream) {
    FRESULT res;
    UINT nofRead;

    res = FAT1_write(stream, ptr, size*nmemb, &nofRead);
    if (res!=FR_OK) {
      return 0;
    }
    return nofRead;
  }
#endif

#if USE_MCURSES
  static void putChar(uint8_t ch) {
    CLS1_SendChar(ch);
  }

  static char getChar(void) {
    char ch;

    do {
      CLS1_ReadChar(&ch);
    } while(ch=='\0');
    //if(ch=='\0') {
    //  return ERR;
   // }
    return ch;
  }
#endif

#define TEST_FAT (1 && USE_FATFS)

void zork_main(void); /* game entry point */

void zork_config(void) {
#if USE_MCURSES
  setFunction_putchar(putChar);
  setFunction_getchar(getChar);
  initscr(); // initialize mcurses
  /* tests only */
 // clear();
 // move (11, 15); // set cursor position
 // addstr ("Hello, World"); // show text
  void hexedit (uint16_t offset);
  hexedit(0x2000);
#endif
  CLS1_SendStr("\n***************************\nWelcome to ZORK!\n***************************\n", CLS1_GetStdio()->stdOut);
#if USE_FATFS
  if (FAT1_Init()!=ERR_OK) { /* initialize FAT driver */
    CLS1_SendStr("Failed FAT init!\r\n", CLS1_GetStdio()->stdErr);
    return;
  }
  if (FAT1_mount(&mountDesc, "0", 1) != FR_OK) { /* mount file system */
    CLS1_SendStr("Failed FAT mount!\r\n", CLS1_GetStdio()->stdErr);
    return;
  }
#endif
#if TEST_FAT
  if (FAT1_open(&dtextcFileDesc, "./dtextc.dat", FA_OPEN_ALWAYS|FA_READ)!=FR_OK) {
    CLS1_SendStr("Failed test data file open!\r\n", CLS1_GetStdio()->stdErr);
    return;
  }
  if (FAT1_close(&dtextcFileDesc)!=FR_OK) {
    CLS1_SendStr("Failed test file close!\r\n", CLS1_GetStdio()->stdErr);
    return;
  }
#endif

  zork_main(); /* run game */
}

void _exit(int i) { /* own exit routine */
  CLS1_SendStr("exit program\r\n", CLS1_GetStdio()->stdErr);
  for(;;) {}
}

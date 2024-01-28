/*
 * zork_config.c
 *
  *      Author: Erich Styger
 */

#include <stdio.h>
#include "zork_config.h"
#include "CLS1.h"
#include "UTIL1.h"
#include "XF1.h"
#if USE_FATFS
  #include "FAT1.h"
#endif
#if USE_MCURSES
  #include "../mcurses/mcurses.h"
#endif
#if USE_FLASH_FILE
  #include "dtextc.h"
#endif
#include <string.h> /* for memset */

/* saving is done in dverb2.c */
/* note: some output code is in supp.c */

#if USE_CONSOLE
char *CLS1_fgets(char *buf, int bufSize, void *channel) {
  bool foundLine;
  size_t len;

  *buf = '\0';
  for(;;) {
    len = UTIL1_strlen((const char*)buf);
    foundLine = CLS1_ReadLine(buf, buf+len, bufSize-len, CLS1_GetStdio());
    if (foundLine) {
      len = UTIL1_strlen((const char*)buf); /* length of buffer string */
      if (len==1 && (buf[0]=='\n' || buf[0]=='\r')) { /* eat preceding newline characters */
        buf[0] = '\0';
      } else if (buf[len-1]=='\n' || buf[len-1]=='\r') { /* line end: parse command */
        buf[len-1] = '\n'; /* it expects \n */
        return buf;
      }
    }
  }
  return NULL; /* failed */
}
#endif

#if USE_CONSOLE
void CLS1_putchar(char ch) {
	CLS1_GetStdio()->stdOut(ch);
}
#endif

#if USE_CONSOLE
unsigned CLS1_fprintf(void *stream, const char *fmt, ...) {
  va_list args;
  unsigned int count = 0;

  va_start(args,fmt);
  count = XF1_xvformat(CLS1_printfPutChar, (void*)CLS1_GetStdio()->stdOut, fmt, args);
  va_end(args);
  return count;
}
#endif

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
	size_t newPos = 0;

	if (option==SEEK_SET) {
		/* from beginning of file */
		newPos = pos;
	} else if (option==SEEK_CUR) {
		newPos = f_tell(f)+pos;
	} else if (option==SEEK_END) {
		newPos = f_size(f);
	} else {
		return EOF;
	}
	if (FAT1_lseek(f, newPos)!=FR_OK) {
      return EOF; /* failure */
    }
    return 0; /* ok */
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
#elif USE_FLASH_FILE

  #define FLASH_FILE_INDEX_DATA  0
  #define FLASH_FILE_INDEX_SAVE  1

  typedef struct {
	  int kind; /* 0: dtextc, 1: save file */
	  size_t pos, size; /* byte position and file size */
	  uint8_t *data; /* pointer to the start of the file data */
  } FLASH_FileDesc;

  static FLASH_FileDesc files[2]; /* 0: dtextc, 1: save file */

  extern int FLASH_getc(FILE *f) {
      FLASH_FileDesc *fp = (FLASH_FileDesc*)f;
	  uint8_t data;

	  data = fp->data[fp->pos];
	  fp->pos++;
	  if (fp->pos>=fp->size) {
		  fp->pos=fp->size;
		  return EOF;
	  }
	  return data;
  }

  extern int FLASH_ftell(FILE *f) {
    FLASH_FileDesc *fp = (FLASH_FileDesc*)f;
	return fp->pos;
  }

  extern int FLASH_fseek(FILE *f, int pos, int option) {
    FLASH_FileDesc *fp = (FLASH_FileDesc*)f;
    size_t newPos = 0;

    if (option==SEEK_SET) {
    	/* from beginning of file */
    	newPos = pos;
    } else if (option==SEEK_CUR) {
    	newPos = fp->pos+pos;
    } else if (option==SEEK_END) {
    	newPos = fp->size+pos;
    } else {
    	return EOF;
    }
    if (newPos>fp->size) {
    	return EOF;
    }
    fp->pos = newPos;
	return 0; /* ok */
  }

  extern int FLASH_fclose(FILE *f) {
	FLASH_FileDesc *fp = (FLASH_FileDesc*)f;
	fp->kind = -1;
	fp->size = 0;
	fp->pos = 0;
	return 0;
  }

  extern FILE *FLASH_fopen(const char *path, char *option) {
	if (UTIL1_strcmp(path, SAVEFILE)==0) {
	  files[FLASH_FILE_INDEX_SAVE].kind = FLASH_FILE_INDEX_SAVE;
	  files[FLASH_FILE_INDEX_SAVE].size = 0; /* \todo */
	  files[FLASH_FILE_INDEX_SAVE].pos = 0; /* \todo */
	  files[FLASH_FILE_INDEX_SAVE].data = NULL;
	  return NULL; /* flash file writing NYI */
	  // return  &files[FLASH_FILE_INDEX_SAVE];
	} else if (UTIL1_strcmp(path, TEXTFILE)==0) {
	  files[FLASH_FILE_INDEX_DATA].kind = FLASH_FILE_INDEX_DATA;
	  files[FLASH_FILE_INDEX_DATA].size = sizeof(_acdtextc);
	  files[FLASH_FILE_INDEX_DATA].pos = 0;
	  files[FLASH_FILE_INDEX_DATA].data = (uint8_t*)&_acdtextc[0];
	  return &files[FLASH_FILE_INDEX_DATA];
	}
	return NULL;
  }

  extern size_t FLASH_fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	  size_t nofRead = 0;
	  size_t nofRequested = size*nmemb;
	  int data;

	  while (nofRequested>0) {
		  data = FLASH_getc(stream);
		  if (data==EOF) {
			  break;
		  }
		  *((uint8_t*)ptr) = (uint8_t)data;
		  ptr++;
		  nofRead++;
	  }
	  return nofRead;
  }

  extern size_t FLASH_fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
	  for(;;) { /* flash file writing NYI */ }
	  return 0; /* NYI */
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
  CLS1_SendStr("\n***************************\n* ZORK! ZORK! ZORK! ZORK! *\n***************************\n", CLS1_GetStdio()->stdOut);
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
#if USE_FLASH_FILE
  memset(files, 0, sizeof(files)); /* init to zero */
#endif
}

#if 0 /* \todo you might have to change this */
void _exit(int i) { /* own exit routine */
  extern FILE *dbfile;
  if (dbfile!=NULL) {
	fclose(dbfile); /* close the data file if it was open */
  }
  CLS1_SendStr("exit Zork program\r\n", CLS1_GetStdio()->stdErr);
  for(;;) {}
}
#endif

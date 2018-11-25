/*
 * zork_config.h
 *
 *      Author: Erich Styger  */


/* this header file needs to be included in vars.h */

/* configuration makros: */
#define USE_FATFS         (0) /* using FatFS with SD card */
#define USE_SEMIHOSTING   (1) /* using semihosting with the debug probe for file I/O */
#define USE_CONSOLE       (1) /* required, using Console input/output */
#define USE_MCURSES       (0) /* use mcurses */

#if (USE_FATFS+USE_SEMIHOSTING > 1)
  #error "only one can be active"
#endif

#if USE_CONSOLE
  #include "CLS1.h"
  #define   printf   CLS1_printf
  #undef putchar
  #define   putchar  CLS1_SendChar

  extern unsigned CLS1_fprintf(void *stream, const char *fmt, ...);
  #define fprintf    CLS1_fprintf

  extern char *CLS1_fgets(char *buf, int bufSize, void *channel);
  #define fgets      CLS1_fgets
#endif

#if USE_SEMIHOSTING
  /* if using semihosting, use the following linker settings
   * -specs=nano.specs -specs=rdimon.specs
   * (do *not* use -specs=nosys.specs)
   */
  #define BINREAD "rb"
  #define BINWRITE "wb"
  /* using relative path inside the project to load and store files: */
  #define TEXTFILE ".\\Sources\\Zork\\dtextc.dat"
  #define SAVEFILE ".\\Sources\\Zork\\dsave.dat"
#elif USE_FATFS
  #define BINREAD "rb"
  #define BINWRITE "wb"
  #define TEXTFILE "./dtextc.dat"
  #define SAVEFILE "./dsave.dat"


  #include "FAT1.h"
  #define FILE FIL
  extern int FatFsGetc(FIL *f);
  extern int FatFsFtell(FIL *f);
  extern int FatFsFClose(FIL *f);
  extern int FatFsFSeek(FIL *f, int pos, int option);
  extern FIL *FatFsFOpen(const char *path, char *option);
  extern size_t FatFsFRead(void *ptr, size_t size, size_t nmemb, FIL *stream);
  extern size_t FatFsFWrite(const void *ptr, size_t size, size_t nmemb, FIL *stream);

  #undef getc
  #define getc(file)                    FatFsGetc(file)
  #define ftell(f)                      FatFsFtell(f)
  #define fseek(f, pos, option)         FatFsFSeek(f, pos, option)
  #define fclose(f)                     FatFsFClose(f)
  #define fopen(path, option)           FatFsFOpen(path, option)
  #define fread(buf, size, nof, file)   FatFsFRead(buf, size, nof, file)
  #define fwrite(buf, size, nof, file)  FatFsFWrite(buf, size, nof, file)
#endif

void _exit(int i);

void zork_config(void);

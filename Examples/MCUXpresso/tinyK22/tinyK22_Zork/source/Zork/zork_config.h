/*
 * zork_config.h
 *
 *      Author: Erich Styger  */

#ifndef ZORK_CONFIG_H
#define ZORK_CONFIG_H
/* this header file needs to be included in vars.h */

#include "platform.h"

#if (USE_FATFS+USE_SEMIHOSTING+USE_FLASH_FILE > 1)
  #error "only one can be active"
#endif

#if USE_CONSOLE
  #include "McuShell.h"
  #define   printf   McuShell_printf
  #undef putchar
  extern void CLS1_putchar(char ch);
  #define   putchar  McuShell_putchar

  extern unsigned CLS1_fprintf(void *stream, const char *fmt, ...);
  #define fprintf    McuShell_fprintf

  extern char *CLS1_fgets(char *buf, int bufSize, void *channel);
  #define fgets      McuShell_fgets
#endif

#if USE_SEMIHOSTING
  /* if using semihosting, use the following linker settings
   * -specs=nano.specs -specs=rdimon.specs
   * (do *not* use -specs=nosys.specs)
   */
  #define BINREAD "rb"
  #define BINWRITE "wb"
#if 0
  /* Kinetis Design Studio IDE: using relative path inside the project to load and store files: */
  #define TEXTFILE ".\\Sources\\Zork\\dtextc.dat"
  #define SAVEFILE ".\\Sources\\Zork\\dsave.dat"
#else
  /* MCUXpresso IDE: using absolute path to the files inside the project: */
  #define TEXTFILE "P:\\MCUXpresso\\FRDM-K64F\\FRDM-K64F_Zork\\Sources\\Zork\\dtextc.dat"
  #define SAVEFILE "P:\\MCUXpresso\\FRDM-K64F\\FRDM-K64F_Zork\\Sources\\Zork\\dsave.dat"
#endif
#elif USE_FLASH_FILE
  #define TEXTFILE "dtextc.dat"
  #define SAVEFILE "dsave.dat"

  #define FILE void
  extern int FLASH_getc(FILE *f);
  extern int FLASH_ftell(FILE *f);
  extern int FLASH_fseek(FILE *f, int pos, int option);
  extern int FLASH_fclose(FILE *f);
  extern FILE *FLASH_fopen(const char *path, char *option);
  extern size_t FLASH_fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
  extern size_t FLASH_fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

  #undef getc
  #define getc(file)                    FLASH_getc(file)
  #define ftell(f)                      FLASH_ftell(f)
  #define fseek(f, pos, option)         FLASH_fseek(f, pos, option)
  #define fclose(f)                     FLASH_fclose(f)
  #define fopen(path, option)           FLASH_fopen(path, option)
  #define fread(buf, size, nof, file)   FLASH_fread(buf, size, nof, file)
  #define fwrite(buf, size, nof, file)  FLASH_fwrite(buf, size, nof, file)
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

int run_zork_game(void); /* run the game */

void zork_config(void);

#endif /* ZORK_CONFIG_H */

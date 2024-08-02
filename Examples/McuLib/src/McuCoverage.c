/*!
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * \brief Implementation of the McuCoverage module.
 */

#include "McuCoverage.h"

#if McuCoverage_CONFIG_IS_ENABLED
#include "McuLib.h"
#include <stdint.h>
#include <stdio.h>
#include "McuLog.h"
#if McuLib_CONFIG_SDK_USE_FREERTOS
  #include "McuRTOS.h"
#endif
#include <gcov.h>

int McuCoverage_Check(void) {
  FILE *file = NULL;

  /*
   * Creating a file without absolute path.
   * With J-Link and MCUXpresso IDE 11.4.1, this file gets created in the IDE installation directory (C:\NXP\MCUXpressoIDE_11.4.1_6260\ide).
   * Where the file gets created (current directory of the semihosting process on the host) really depends on the probe firmware and is non-standard.
   * See as well:
   * https://developer.arm.com/documentation/dui0058/d/semihosting/semihosting-swis/sys-open--0x01-?lang=en
   */
  file = fopen ("gcov_text.txt", "w"); /* on RP2040, file is present in project root folder */
  if (file!=NULL) {
    fputs("hello world with file I/O\r\n", file);
    fclose(file);
  } else {
    return 0; /* failed */
  }

  file = fopen ("c:\\tmp\\test.txt", "w");
  if (file!=NULL) {
    fputs("hello world with file I/O\r\n", file);
    (void)fwrite("hello\r\n", sizeof("hello\r\n")-1, 1, file);
    fclose(file);
    return 1; /* ok */
  }
  return 0; /* failed */
}

void McuCoverage_Deinit(void) {
  /* nothing needed  */
}

/* call the coverage initializers if not done by startup code */
void McuCoverage_Init(void) {
#if McuCoverage_CONFIG_USE_FREESTANDING
  /* In a freestanding environment, we use custom hooks to write data. The constructors/destructors are *not* used,
   * instead we rely on the .gcov_info in the binary.
  */
#else
  #if McuLib_CONFIG_CPU_IS_RPxxxx
    /* constructor calls for coverage already done in C:\Raspy\pico\pico-sdk\src\rp2_common\pico_runtime/runtime.c */
  #else
    void (**p)(void);
    extern uint32_t __init_array_start, __init_array_end; /* linker defined symbols, array of function pointers */
    uint32_t beg = (uint32_t)&__init_array_start;
    uint32_t end = (uint32_t)&__init_array_end;

    while(beg<end) {
      p = (void(**)(void))beg; /* get function pointer */
      (*p)(); /* call constructor */
      beg += sizeof(p); /* next pointer */
    }
  #endif
#endif
}

/* custom exit function */
void exit_(int i) {
  for(;;) {}
}

/* see https://gcc.gnu.org/onlinedocs/gcc/Freestanding-Environments.html#Tutorial */
#if McuCoverage_CONFIG_USE_FREESTANDING

static McuCoverage_OutputCharFct_t OutputCharFct = NULL;

void McuCoverage_OutputString(const unsigned char *str) {
  if (OutputCharFct==NULL) {
    return;
  }
  while(*str!='\0') {
    OutputCharFct(*str);
    str++;
  }
}

void McuCoverage_SetOuputCharCallback(McuCoverage_OutputCharFct_t callback) {
  OutputCharFct = callback;
}

/* The start and end symbols are provided by the linker script.  We use the
   array notation to avoid issues with a potential small-data area. */

/* Use the following in the linker file: 
  .gcov_info:
  {
    PROVIDE (__gcov_info_start = .);
    KEEP (*(.gcov_info))
    PROVIDE (__gcov_info_end = .);
  } > FLASH

  Additionally, set the following compiler option:
  -fprofile-info-section
  
  See https://github.com/gcc-mirror/gcc/blob/master/libgcc/gcov.h
*/

extern const struct gcov_info *const __gcov_info_start[];
extern const struct gcov_info *const __gcov_info_end[];

static const unsigned char a = 'a';

/* each 8bit binary data value c gets encoded into two characters, each in rang 'a'-'p' (p is 'a'+16):
  buf[0]: 'a' + LowNibble(c)
  buf[1]: 'a' + HighNibble(c)
*/
static inline unsigned char *encode(unsigned char c, unsigned char buf[2]) {
  buf[0] = a + c % 16;
  buf[1] = a + (c / 16) % 16;
  return buf;
}

#if 0
/* The application reads a character stream encoded by encode() from stdin,
   decodes it, and writes the decoded characters to stdout.  Characters other
   than the 16 characters 'a' to 'p' are ignored.  */
static int can_decode(unsigned char c) {
  return (unsigned char)(c - a) < 16;
}

/* application which reads from stdin a previously encoded data stream and decodes it to stdout. */
void application_decode(void) {
  int first = 1;
  int i;
  unsigned char c;

  while ((i = fgetc(stdin)) != EOF) {
    unsigned char x = (unsigned char)i;

    if (can_decode (x)) {
      if (first) {
        c = x - a;
      } else {
        fputc (c + 16 * (x - a), stdout);
      }
      first = !first;
    } else {
      first = 1;
    }
  }
}
#endif

/* This function shall produce a reliable in order byte stream to transfer the
   gcov information from the target to the host system.  */
static void dump(const void *d, unsigned n, void *arg) {
  (void)arg;
  const unsigned char *c = d;
  unsigned char buf[2];

  for(unsigned int i = 0; i<n; i++) {
    if (OutputCharFct!=NULL) {
      encode(c[i], buf);
      OutputCharFct(buf[0]);
      OutputCharFct(buf[1]);
    }
  }
}

/* The filename is serialized to a gcfn data stream by the
   __gcov_filename_to_gcfn() function.  The gcfn data is used by the
   "merge-stream" subcommand of the "gcov-tool" to figure out the filename
   associated with the gcov information. */
static void filename(const char *f, void *arg) {
  __gcov_filename_to_gcfn(f, dump, arg);
}

/* The __gcov_info_to_gcda() function may have to allocate memory under
   certain conditions.  Simply try it out if it is needed for your application
   or not.  */
static void *allocate (unsigned length, void *arg) {
  (void)arg;
  void *p;
  #if McuLib_CONFIG_SDK_USE_FREERTOS
    p = pvPortMalloc(length);
  #else
    p = malloc (length);
  #endif
  if (p==NULL) {
    McuLog_fatal("malloc failed");
    for(;;) {} /* error */
  }
}

/* Dump the gcov information of all translation units. */
static void dump_gcov_info (void) {
  const struct gcov_info *const *info = __gcov_info_start;
  const struct gcov_info *const *end = __gcov_info_end;

  __asm__ ("" : "+r" (info)); /* Obfuscate variable to prevent compiler optimizations.  */
  while (info != end) { /* iterate through all infos (or modules instrumented) */
    void *arg = NULL;
    __gcov_info_to_gcda(*info, filename, dump, allocate, arg); /* write record*/
    if (OutputCharFct!=NULL) { /* each record is terminated with a newline character */
      OutputCharFct('\n');
    }
    info++;
  }
}
#endif /* McuCoverage_CONFIG_USE_FREESTANDING */

void McuCoverage_WriteFiles(void) {
#if McuCoverage_CONFIG_USE_FREESTANDING
  dump_gcov_info();
#else
  #if __GNUC__ < 11
    // void __gcov_flush(void); /* internal gcov function to write data */
    __gcov_flush(); /* __gcov_flush() has been removed in the libraries for GCC11 */
  #else
    // void __gcov_dump(void); /* from GCC11 on, __gcov_flush() has been replaced by __gcov_dump() */
    __gcov_dump(); /* from GCC11 on, use __gcov_dump() */
  #endif
#endif
}

#endif /* #if McuCoverage_CONFIG_IS_ENABLED */

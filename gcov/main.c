/*
 * main.c
 *
 * Author: Erich Styger
 * License: PDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

static void printArgs(int argc, char *argv[]) {
  printf("argc: %d\n", argc);
  for(int i=0; i<argc; i++) {
    printf("argv[%d]: %s\n", i, argv[i]);
  }
}

static void printhelp(void) {
  printf("Use one of the following options:\n");
  printf("  -h             : prints this help\n");
  printf("  -f <file>      : input file, default \"standalone.txt\"\n");
  printf("  -o <file>      : output file, default \"data.gcda\"\n");
}

static const unsigned char a = 'a';

static inline unsigned char *encode (unsigned char c, unsigned char buf[2]) {
  buf[0] = c % 16 + a;
  buf[1] = (c / 16) % 16 + a;
  return buf;
}

/* The application reads a character stream encoded by encode() from stdin,
   decodes it, and writes the decoded characters to stdout.  Characters other
   than the 16 characters 'a' to 'p' are ignored.  */
static int can_decode (unsigned char c) {
  return (unsigned char)(c - a) < 16;
}

static int readChar(FILE *fp) {
  unsigned char ch;
  if (fread(&ch, 1, sizeof(ch), fp)!=sizeof(ch)) {
    return EOF;
  }
  return ch;
}

static int convertDataFile(const char *inFileName, const char *outFileName) {
  FILE *inFile, *outFile;
  int res = 0;
  long fileSize;

  int first = 1;
  int i;
  unsigned char c;

  printf("open input file '%s'\n", inFileName);
  inFile = fopen(inFileName, "rb");
  if (inFile==NULL) {
    printf("input file '%s' open failed\n", inFileName);
    return -1;
  }
  fseek(inFile, 0L, SEEK_END);
  fileSize = ftell(inFile);
  printf("input file size: %d bytes\n", fileSize);
  fseek(inFile, 0L, SEEK_SET); /* rewind to the start */

  printf("open output file '%s'\n", outFileName);
  outFile = fopen(outFileName, "w+"); /* create file if it does not exist */
  if (outFile==NULL) {
    printf("creating output file '%s' failed\n", outFileName);
    fclose(inFile); /* close input file */
    return -1;
  }

  /* from https://gcc.gnu.org/onlinedocs/gcc/Freestanding-Environments.html#Tutorial
   * $ ./a.out <gcda-1.txt 2>gcda-2.txt | gcov-tool merge-stream
   * $ gcov -bc app.c
   */
  while ((i = readChar(inFile)) != EOF) {
    unsigned char x = (unsigned char)i;

    if (can_decode(x)) {
      if (first) {
        c = x - a;
      } else {
        fputc(c + 16 * (x - a), outFile);
        //fputc(c + 16 * (x - a), stdout);
      }
      first = !first;
    } else {
      first = 1;
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  char inFileName[256];
  char outFileName[256];

  printf("Read freestanding gcov data stream file and convert it. Use -h for help.\n");

  memset(inFileName, 0, sizeof(inFileName));
  memset(outFileName, 0, sizeof(outFileName));
  /* printArgs(argc, argv); */ /* testing only */
  for(;;) { /* breaks */
    if (argc==1) {
      /* no arguments, using default values */
      break;
    }
    if (argc==2 && strcmp(argv[1], "-h")==0) { /* -h */
      printhelp();
      return 0; /* ok */
    }
    if (argc==3 || argc==5) {
      if (strcmp(argv[1], "-f")==0) { /* -f <filename> */
        strncpy(inFileName, argv[2], sizeof(inFileName)-1);
      } else if (strcmp(argv[3], "-f")==0) { /* -f <filename> */
        strncpy(inFileName, argv[4], sizeof(inFileName)-1);
      }
      if (strcmp(argv[1], "-o")==0) { /* -o <filename> */
        strncpy(outFileName, argv[2], sizeof(outFileName)-1);
      } else if (strcmp(argv[3], "-o")==0) { /* -o <filename> */
        strncpy(outFileName, argv[4], sizeof(outFileName)-1);
      }
    }
    break;
  } /* for */
  if (inFileName[0]=='\0') { /* use default */
    strncpy(inFileName, "stream.txt", sizeof(inFileName)-1);
  }
  if (outFileName[0]=='\0') { /* use default */
    strncpy(outFileName, "stream.gcfn", sizeof(outFileName)-1);
  }
  if (convertDataFile(inFileName, outFileName)!=0) {
    printf("failed converting stream file\n");
    return -1;
  }
  printf("finished converting stream file\n");
  return 0;
}

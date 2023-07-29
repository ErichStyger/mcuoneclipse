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

/* defines to control the output to the console */
#define CONFIG_LOG_TIME_TO_CONSOLE        (0) /* if timestamp items are printed to the console, useful for debugging */
#define CONFIG_LOG_DATA_TO_CONSOLE        (0) /* if data items are printed to the console, useful for debugging */
#define CONFIG_LOG_SUMMARY_TO_CONSOLE     (0) /* if summary items are printed to the console, useful for debugging */

#define ERROR_CODE_END_REACHED (1)

/* values from the Excel file: */
static const uint32_t unitMul = 3;
static const uint32_t unitDiv = 393216000;

typedef struct dataItem_t { /* data structure representing the raw data from the file */
  double timeStamp; /* time stamp (8 bytes): the time stamp associated with a value (time stamp 1 corresponds to the first value). This value is in microseconds. Example: 2.0358867E7 [us]. The first two timestamps can be used to calculate the sampling period. The other timestamp values are calculated based on the sampling period.  */
  uint32_t value; /* value (4 bytes): the value reported by ADC. Example: 4095. This value is further processed according to the used probe, see Data processing for more details.  */
  struct summary { /* summary values (16 bytes): Sequences of [min, avg, max] values. The summary values are calculated for each i-th value in the sequence, if “i” is a multiple of “base”. The number of summary values is adjusted logarithmically according to the number of values registered so far. */
    uint32_t min; /* minimal value of the previous items */
    double avg;   /* average value of the previous items */
    uint32_t max; /* maximum value of the previous items */
  } summary;
} dataItem_t;

typedef struct dataHeaderItem_t {
  uint32_t magicNumber;   /* file format identifier: "$EMF" as char sequence */
  uint16_t version;       /* version number, currently 0x0001 */
  uint32_t base;          /* number of data values in sequence, e.g. 0x10 */
  uint64_t step;          /* number of values used for summary value */
  uint32_t sourceID;      /* source ID of data, not clear yet */
} dataHeaderItem_t;

static int readBytes(FILE *fp, unsigned char *buf, size_t nofBytes) {
  if (fread(buf, 1, nofBytes, fp)!=nofBytes) {
    return -1;
  }
  return 0; /* ok */
}

static uint64_t swap64(unsigned char buf[8]) {
  uint32_t vh, vl;

  vh = (buf[0]<<24) + (buf[1]<<16) + (buf[2]<<8) + buf[3];
  vl = (buf[4]<<24) + (buf[5]<<16) + (buf[6]<<8) + buf[7];
  return (((uint64_t)vh)<<32) + vl;
}

static double swap64f(unsigned char buf[8]) {
  union {
    uint64_t i64;
    double f64;
  } u;
  u.i64 = swap64(buf);
  return u.f64;
}

static uint32_t swap32(unsigned char buf[4]) {
  return (buf[0]<<24) + (buf[1]<<16) + (buf[2]<<8) + buf[3];
}

static uint16_t swap16(unsigned char buf[2]) {
  return (buf[0]<<8) + buf[1];
}

static int read64u(FILE *fp, uint64_t *val) {
  unsigned char buf[sizeof(uint64_t)];

  if (fread(buf, 1, sizeof(uint64_t), fp)!=sizeof(uint64_t)) {
    return -1;
  }
  *val = swap64(buf);
  return 0; /* ok */
}

static int read32u(FILE *fp, uint32_t *val) {
  unsigned char buf[sizeof(uint32_t)];

  if (fread(buf, 1, sizeof(uint32_t), fp)!=sizeof(uint32_t)) {
    return -1;
  }
  *val = swap32(buf);
  return 0; /* ok */
}

static int read16u(FILE *fp, uint16_t *val) {
  unsigned char buf[sizeof(uint16_t)];

  if (fread(buf, 1, sizeof(uint16_t), fp)!=sizeof(uint16_t)) {
    return -1;
  }
  *val = swap16(buf);
  return 0; /* ok */
}

static int readFloat64(FILE *fp, double *val) {
  unsigned char buf[sizeof(double)];

  if (fread(buf, 1, sizeof(buf), fp)!=sizeof(buf)) {
    return -1;
  }
  *val = swap64f(buf);
  return 0; /* ok */
}

static int readMagicNumber(FILE *fp, uint32_t *pmagic) {
  /* Magic number (4 bytes): field used to verify if the imported file is an Energy Measurement file. */
  uint32_t magic;

  if (read32u(fp, &magic) != 0) {
    printf("failed reading magic number\n");
    return -1;
  }
  printf("magic number: 0x%x\n", magic);
  /* check for "$EMF": 0x24454D46 */
  if (magic!=0x24454D46) {
    printf("wrong magic number: 0x%x\n", magic);
    return -1;
  }
  *pmagic = magic;
  return 0; /* ok */
}

static int readVersionNumber(FILE *fp, uint16_t *pversion) {
  /* Version (2 bytes): the file version. */
  uint16_t version;

  if (read16u(fp, &version) != 0) {
    printf("failed reading version number\n");
    return -1;
  }
  printf("version: 0x%x\n", version);
  if (version!=0x0001) {
    printf("wrong version number: 0x%x\n", version);
    return -1;
  }
  *pversion = version;
  return 0; /* ok */
}

static int readBase(FILE *fp, uint32_t *pbase) {
  /* Base (4 bytes): the number of values that are registered as individual values. */
  uint32_t base;

  if (read32u(fp, &base) != 0) {
    printf("failed reading base\n");
    return -1;
  }
  printf("base: 0x%x\n", base);
  *pbase = base;
  return 0; /* ok */
}

static int readStep(FILE *fp, uint64_t *pstep) {
  /* Step (8 bytes): the number of samples used to calculate a summary value. */
  uint64_t step;

  if (read64u(fp, &step) != 0) {
    printf("failed reading version number\n");
    return -1;
  }
  printf("step: 0x%08x%08x\n", (uint32_t)(step>>32), (uint32_t)(step));
  *pstep = step;
  return 0; /* ok */
}

static int readSourceID(FILE *fp, uint32_t *pID) {
  /* SourceID (4 bytes): the measurement source ID associated with the registered data.
   * Examples of measurement sources: target current, target voltage, target power. */
  uint32_t id;

  if (read32u(fp, &id) != 0) {
    printf("failed reading sourceID\n");
    return -1;
  }
  printf("sourceID: 0x%x\n", id);
  *pID = id;
  return 0; /* ok */
}

static double Convert_to_mA(uint32_t adc)  {
  return ((double)(adc*1000*unitMul))/unitDiv;
}

static double Convert_double_to_mA(double val)  {
  return ((double)(val*1000.0*unitMul))/unitDiv;
}

static double Convert_double_to_us(double val)  {
  return ((double)(val*unitMul))/unitDiv;
}

static uint32_t log_a_to_base_b(uint32_t a, uint32_t b) {
  /* could use 'return log2(a)/log2(b);' but this would be on double.
   * Below an implementation with int type which is recursive.
   * See: https://www.geeksforgeeks.org/program-to-compute-log-a-to-any-base-b-logb-a/
   */
  return (a > b-1)
    ? 1 + log_a_to_base_b(a/b, b)
    : 0;
}

static uint32_t powi32(uint32_t base, unsigned int nof) {
  uint32_t val;

  if (nof==0) {
    return 1;
  }
  val = base;
  while (nof>1) {
    val *= base;
    nof--;
  }
  return val;
}

static int getNofSummaryItems(int dataItemIdx, int base) {
  /* After a number of 'base' data items, there is a summary item. For example for a base of 16:
   *    data1 - data16 (base)
   *    summary (of last 16 (base) items)
   *    data17 - data32
   *    summary (of last base items)
   *    data 33...
   *
   * At data item (base^2) there are *two* summary items:
   *    ..data256
   *    summary (summary of last base (16) items)
   *    summary (summary of last base^2 (256) items)
   *    data257 ...data272
   *    summary (of last base items)
   *    data273 - data288
   *    summary (of last base items)
   *
   * After every base^2 data items, there is again an extra summary covering the last base^2 data items:
   *    ...
   *    data481 - data496
   *    summary of last base items
   *    data497 - data512
   *    summary of last base items
   *    summary of last 256 items
   *    data513 - data528
   *    summary of last base items
   *    data529 -..
   *
   * This goes on, until we hit the next level (base^3): here we get an extra summary item:
   *    data4081 - data4096
   *    summary of base items
   *    summary of base^2 items
   *    summary of base^3 items
   *    data4097 - ...
   *
   * and so on.
   */
  uint32_t log, val;

  if ((dataItemIdx%base)!=0) {
    return 0; /* must be multiple of base */
  }
  log = log_a_to_base_b(dataItemIdx, base); /* log to base */
  while(log>1) {
    val = powi32(base, log);
    if (dataItemIdx==val) { /* matching (base^log)? */
      return log;
    }
    /* else: check if multiple of log-1 */
    if ((dataItemIdx%val)==0) {
      return log;
    }
    log--;
  }
  return log;
}

static int readDataItems(FILE *fp, uint32_t base, FILE *outFile, long fileSize) {
  dataItem_t data;
  int nofSummaries; /* number of summaries to read */
  uint32_t nofItems = 0; /* counting number of data items read */
  double us;

  for(;;) { /* breaks */
    if (readFloat64(fp, &data.timeStamp) != 0) {
      printf("failed reading time stamp\n");
      return -1;
    }
    us = Convert_double_to_us(data.timeStamp);
#if CONFIG_LOG_TIME_TO_CONSOLE
    printf("filepos: 0x%x\ntimestamp: %f us\n", ftell(fp), us);
#endif
    for(int i=0; i<base; i++) {
      if (read32u(fp, &data.value) != 0) {
        printf("failed reading value\n");
        return -1;
      }
      nofItems++;
      double mA = Convert_to_mA(data.value);
#if CONFIG_LOG_DATA_TO_CONSOLE
      printf("%d: 0x%x, %f mA\n", nofItems, data.value, mA);
#endif
      fprintf(outFile, "%f,%f\n", us, mA);
    }
    if (ftell(fp)==fileSize) { /* the end of the file is without a summary */
      printf("reached END\n");
      return ERROR_CODE_END_REACHED;
    }
    /* read summary items */
#if CONFIG_LOG_SUMMARY_TO_CONSOLE
    printf("%d: 0x%x: ----------------------------\n", nofItems, ftell(fp));
#endif
    nofSummaries = getNofSummaryItems(nofItems, base);
    for(int s=0; s<nofSummaries; s++) {
      if (read32u(fp, &data.summary.min) != 0) {
        printf("failed reading min\n");
        return -1;
      }
#if CONFIG_LOG_SUMMARY_TO_CONSOLE
      printf("==> min: 0x%x, %f mA\n", data.summary.min, Convert_to_mA(data.summary.min));
#endif
      if (ftell(fp)==fileSize) { /* the end of the file is without a summary */
        printf("reached END\n");
        return ERROR_CODE_END_REACHED;
      }
      if (readFloat64(fp, &data.summary.avg) != 0) {
        printf("failed reading avg\n");
        return -1;
      }
#if CONFIG_LOG_SUMMARY_TO_CONSOLE
      printf("==> avg: %f mA\n", Convert_double_to_mA(data.summary.avg));
#endif
      if (ftell(fp)==fileSize) { /* the end of the file is without a summary */
        printf("reached END\n");
        break;
      }
      if (read32u(fp, &data.summary.max) != 0) {
        printf("failed reading max\n");
        return -1;
      }
#if CONFIG_LOG_SUMMARY_TO_CONSOLE
      printf("==> max: 0x%x, %f mA\n", data.summary.max, Convert_to_mA(data.summary.max));
#endif
      if (ftell(fp)==fileSize) { /* the end of the file is without a summary */
        printf("reached END\n");
        return ERROR_CODE_END_REACHED;
     }
    } /* for nofSummaries */
#if CONFIG_LOG_SUMMARY_TO_CONSOLE
    printf("--------------------------------\n");
#endif
  }
  return 0;
}

static int convertDataFile(const char *inFileName, const char *outFileName) {
  /* see NXP MCUXpresso User Guide, MCUXpresso IDE LinkServer Energy Measurement Guide -> Appendix -> Raw data export format and data processing information */
  FILE *inFile, *outFile;
  int res = 0;
  dataHeaderItem_t data;
  long fileSize;

  printf("unitMul: %d\n", unitMul);
  printf("unitDiv: %d\n", unitDiv);

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
  fprintf(outFile, "us,mA\n"); /* write CSV header */
  for(;;) { /* at the end or in case of error */
    res = 0;
    if (readMagicNumber(inFile, &data.magicNumber)!=0) {
      printf("failed reading magic number\n");
      res = -1;
      break;
    }
    if (readVersionNumber(inFile, &data.version)!=0) {
      printf("failed reading version number\n");
      res = -1;
      break;
    }
    if (readBase(inFile, &data.base)!=0) {
      printf("failed reading base\n");
      res = -1;
      break;
    }
    if (readStep(inFile, &data.step)!=0) {
      printf("failed reading step\n");
      res = -1;
      break;
    }
    if (readSourceID(inFile, &data.sourceID)!=0) {
      printf("failed reading SourceID\n");
      res = -1;
      break;
    }
    res = readDataItems(inFile, data.base, outFile, fileSize);
    if (res==ERROR_CODE_END_REACHED) {
      res = 0;
      break;
    } else {
      printf("failed reading data item(s)\n");
      res = -1;
      break;
    }
    if (ftell(inFile)==fileSize) {
      printf("end of file reached\n");
      break;
    }
    break;
  } /* for */
  fclose(inFile);
  printf("input file '%s' closed\n", inFileName);
  fclose(outFile);
  printf("output file '%s' closed\n", outFileName);
  return res; /* ok */
}

static void printArgs(int argc, char *argv[]) {
  printf("argc: %d\n", argc);
  for(int i=0; i<argc; i++) {
    printf("argv[%d]: %s\n", i, argv[i]);
  }
}

static void printhelp(void) {
  printf("Use one of the following options:\n");
  printf("  -h             : prints this help\n");
  printf("  -f <file>      : input file, default \"rawData.bin\"\n");
  printf("  -o <file>      : output file, default \"data.csv\"\n");
}

static void testLog(void) {
  /* function to test the log function to determine the number of summaries in the data stream */
  int base = 16;
  int s;
  for(int i=base; i<=100000;i+=base) {
    s = getNofSummaryItems(i, base);
    if (s>1) {
      printf("i: %d ", i);
      for(int i=0; i<s; i++) {
        printf("s");
      }
      printf("\n");
    }
  }
}

int main(int argc, char *argv[]) {
  char inFileName[256];
  char outFileName[256];

  //testLog();
  printf("Program to read NXP power measurement binary data file and convert it to CSV.\n");

  memset(inFileName, 0, sizeof(inFileName));
  memset(outFileName, 0, sizeof(outFileName));
  //printArgs(argc, argv);
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
    strncpy(inFileName, "rawData.bin", sizeof(inFileName)-1);
  }
  if (outFileName[0]=='\0') { /* use default */
    strncpy(outFileName, "data.csv", sizeof(outFileName)-1);
  }
  if (convertDataFile(inFileName, outFileName)!=0) {
    printf("failed reading data file\n");
    return -1;
  }
  printf("finished reading data file\n");
  return 0;
}

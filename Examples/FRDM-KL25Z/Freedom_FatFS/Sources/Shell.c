/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */

#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "LEDR.h"
#include "LEDG.h"
#include "RTC1.h"
#include "FAT1.h"
#include "TmDt1.h"

#define PL_HAS_SD_CARD  1 /* if we have SD card support */

#if 1 && PL_HAS_SD_CARD
/*! \brief Simple benchmark function: first we are going to write a file, then we will copy it */
static void benchmark(const CLS1_StdIOType *io) {
  static FIL fp;
  uint16_t i;
  UINT bw;
  uint8_t read_buf[10];
  TIMEREC time, startTime;
  int32_t start_mseconds, mseconds;

  /* write benchmark */
  CLS1_SendStr((const unsigned char*)"Benchmark: open file, write 10k times 10 bytes (100'000 bytes), close file:\r\n", io->stdOut);
  CLS1_SendStr((const unsigned char*)"Deleting any existing files...\r\n", io->stdOut);
  (void)FAT1_DeleteFile((const unsigned char*)"./bench.txt", io);
  (void)FAT1_DeleteFile((const unsigned char*)"./copy.txt", io);

  CLS1_SendStr((const unsigned char*)"Creating benchmark file...\r\n", io->stdOut);
  (void)TmDt1_GetTime(&startTime);
  if (FAT1_open(&fp, "./bench.txt", FA_CREATE_ALWAYS|FA_WRITE)!=FR_OK) {
    CLS1_SendStr((const unsigned char*)"*** Failed opening benchmark file!\r\n", io->stdErr);
    return;
  }
  for(i=0;i<10000;i++) {
    if (FAT1_write(&fp, "benchmark ", sizeof("benchmark ")-1, &bw)!=FR_OK) {
      CLS1_SendStr((const unsigned char*)"*** Failed writing file!\r\n", io->stdErr);
      (void)FAT1_close(&fp);
      return;
    }
  }
  (void)FAT1_close(&fp);
  (void)TmDt1_GetTime(&time);
  start_mseconds = startTime.Hour*60*60*1000 + startTime.Min*60*1000 + startTime.Sec*1000 + startTime.Sec100*10;
  mseconds = time.Hour*60*60*1000 + time.Min*60*1000 + time.Sec*1000 + time.Sec100*10 - start_mseconds;
  CLS1_SendNum32s(mseconds, io->stdOut);
  CLS1_SendStr((const unsigned char*)" mseconds needed for command.\r\n", io->stdOut);

  /* read benchmark */
  CLS1_SendStr((const unsigned char*)"Reading benchmark file...\r\n", io->stdOut);
  (void)TmDt1_GetTime(&startTime);
  if (FAT1_open(&fp, "./bench.txt", FA_READ)!=FR_OK) {
    CLS1_SendStr((const unsigned char*)"*** Failed opening benchmark file!\r\n", io->stdErr);
    return;
  }
  for(i=0;i<10000;i++) {
    if (FAT1_read(&fp, &read_buf[0], sizeof(read_buf), &bw)!=FR_OK) {
      CLS1_SendStr((const unsigned char*)"*** Failed reading file!\r\n", io->stdErr);
      (void)FAT1_close(&fp);
      return;
    }
  }
  (void)FAT1_close(&fp);
  (void)TmDt1_GetTime(&time);
  start_mseconds = startTime.Hour*60*60*1000 + startTime.Min*60*1000 + startTime.Sec*1000 + startTime.Sec100*10;
  mseconds = time.Hour*60*60*1000 + time.Min*60*1000 + time.Sec*1000 + time.Sec100*10 - start_mseconds;
  CLS1_SendNum32s(mseconds, io->stdOut);
  CLS1_SendStr((const unsigned char*)" mseconds needed for command.\r\n", io->stdOut);

  /* copy benchmark */
  CLS1_SendStr((const unsigned char*)"Benchmark: copy file (100'000 bytes):\r\n", io->stdOut);
  CLS1_SendStr((const unsigned char*)"Going to copy file...\r\n", io->stdOut);
  (void)TmDt1_GetTime(&startTime);
  (void)FAT1_CopyFile((const unsigned char*)"./bench.txt", (const unsigned char*)"./copy.txt", io);
  (void)TmDt1_GetTime(&time);
  start_mseconds = startTime.Hour*60*60*1000 + startTime.Min*60*1000 + startTime.Sec*1000 + startTime.Sec100*10;
  mseconds = time.Hour*60*60*1000 + time.Min*60*1000 + time.Sec*1000 + time.Sec100*10 - start_mseconds;
  CLS1_SendNum32s(mseconds, io->stdOut);
  CLS1_SendStr((const unsigned char*)" mseconds needed for command.\r\n", io->stdOut);
  CLS1_SendStr((const unsigned char*)"done!\r\n", io->stdOut);
}
#endif /* PL_HAS_SD_CARD */

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
static uint8_t ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  /* handling our own commands */
#if PL_HAS_SD_CARD
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0) {
    CLS1_SendHelpStr((const unsigned char*)"run benchmark", (const unsigned char*)"Run FatFS benchmark\r\n", io->stdOut);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "run benchmark")==0) {
    benchmark(io);
    *handled = TRUE;
  }
#endif
  return ERR_OK;
}


static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if LEDR_PARSE_COMMAND_ENABLED
  LEDR_ParseCommand,
#endif
#if LEDG_PARSE_COMMAND_ENABLED
  LEDG_ParseCommand,
#endif
#if LEDB_PARSE_COMMAND_ENABLED
  LEDB_ParseCommand,
#endif
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
#if RTC1_PARSE_COMMAND_ENABLED
  RTC1_ParseCommand,
#endif
#if FAT1_PARSE_COMMAND_ENABLED
  FAT1_ParseCommand,
#endif
  ParseCommand,
  NULL /* sentinel */
};

static portTASK_FUNCTION(ShellTask, pvParameters) {
#if PL_HAS_SD_CARD
  bool cardMounted = FALSE;
  static FAT1_FATFS fileSystemObject;
#endif
  unsigned char buf[48];

  (void)pvParameters; /* not used */
  buf[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
  for(;;) {
#if PL_HAS_SD_CARD
    (void)FAT1_CheckCardPresence(&cardMounted,
        0 /* volume */, &fileSystemObject, CLS1_GetStdio());
#endif
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
    LEDG_Neg();
  }
}

void SHELL_Init(void) {
  if (FRTOS1_xTaskCreate(ShellTask, (signed portCHAR *)"Shell", configMINIMAL_STACK_SIZE+200, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}


/*
 * Shell.c
 *
 *  Created on: 23.05.2011
 *      Author: Erich Styger
 */

#include "FRTOS1.h"
#include "Shell.h"
#include "FSSH1.h"
#include "LED2.h"
#include <string.h>

#define PL_HAS_SD_CARD  1 /* if we have SD card support */

#if PL_HAS_SD_CARD
/*! \brief Simple benchmark function: first we are going to write a file, then we will copy it */
static void benchmark(const FSSH1_StdIOType *io) {
  static FIL fp;
  uint16_t i;
  UINT bw;
  uint8_t read_buf[10];
  TIMEREC time, startTime;
  int32_t start_mseconds, mseconds;

  /* write benchmark */
  FSSH1_SendStr((const unsigned char*)"Benchmark: open file, write 10k times 10 bytes (100'000 bytes), close file:\r\n", io->stdOut);
  FSSH1_SendStr((const unsigned char*)"Deleting any existing files...\r\n", io->stdOut);
  (void)FSSH1_DeleteFile((const unsigned char*)"./bench.txt", io);
  (void)FSSH1_DeleteFile((const unsigned char*)"./copy.txt", io);

  FSSH1_SendStr((const unsigned char*)"Creating benchmark file...\r\n", io->stdOut);
  (void)TmDt1_GetTime(&startTime);
  if (FAT1_open(&fp, "./bench.txt", FA_CREATE_ALWAYS|FA_WRITE)!=FR_OK) {
    FSSH1_SendStr((const unsigned char*)"*** Failed opening benchmark file!\r\n", io->stdErr);
    return;
  }
  for(i=0;i<10000;i++) {
    if (FAT1_write(&fp, "benchmark ", sizeof("benchmark ")-1, &bw)!=FR_OK) {
      FSSH1_SendStr((const unsigned char*)"*** Failed writing file!\r\n", io->stdErr);
      (void)FAT1_close(&fp);
      return;
    }
  }
  (void)FAT1_close(&fp);
  (void)TmDt1_GetTime(&time);
  start_mseconds = startTime.Hour*60*60*1000 + startTime.Min*60*1000 + startTime.Sec*1000 + startTime.Sec100*10;
  mseconds = time.Hour*60*60*1000 + time.Min*60*1000 + time.Sec*1000 + time.Sec100*10 - start_mseconds;
  FSSH1_SendNum32s(mseconds, io->stdOut);
  FSSH1_SendStr((const unsigned char*)" mseconds needed for command.\r\n", io->stdOut);

  /* read benchmark */
  FSSH1_SendStr((const unsigned char*)"Reading benchmark file...\r\n", io->stdOut);
  (void)TmDt1_GetTime(&startTime);
  if (FAT1_open(&fp, "./bench.txt", FA_READ)!=FR_OK) {
    FSSH1_SendStr((const unsigned char*)"*** Failed opening benchmark file!\r\n", io->stdErr);
    return;
  }
  for(i=0;i<10000;i++) {
    if (FAT1_read(&fp, &read_buf[0], sizeof(read_buf), &bw)!=FR_OK) {
      FSSH1_SendStr((const unsigned char*)"*** Failed reading file!\r\n", io->stdErr);
      (void)FAT1_close(&fp);
      return;
    }
  }
  (void)FAT1_close(&fp);
  (void)TmDt1_GetTime(&time);
  start_mseconds = startTime.Hour*60*60*1000 + startTime.Min*60*1000 + startTime.Sec*1000 + startTime.Sec100*10;
  mseconds = time.Hour*60*60*1000 + time.Min*60*1000 + time.Sec*1000 + time.Sec100*10 - start_mseconds;
  FSSH1_SendNum32s(mseconds, io->stdOut);
  FSSH1_SendStr((const unsigned char*)" mseconds needed for command.\r\n", io->stdOut);

  /* copy benchmark */
  FSSH1_SendStr((const unsigned char*)"Benchmark: copy file (100'000 bytes):\r\n", io->stdOut);
  FSSH1_SendStr((const unsigned char*)"Going to copy file...\r\n", io->stdOut);
  (void)TmDt1_GetTime(&startTime);
  (void)FSSH1_CopyFile((const unsigned char*)"./bench.txt", (const unsigned char*)"./copy.txt", io);
  (void)TmDt1_GetTime(&time);
  start_mseconds = startTime.Hour*60*60*1000 + startTime.Min*60*1000 + startTime.Sec*1000 + startTime.Sec100*10;
  mseconds = time.Hour*60*60*1000 + time.Min*60*1000 + time.Sec*1000 + time.Sec100*10 - start_mseconds;
  FSSH1_SendNum32s(mseconds, io->stdOut);
  FSSH1_SendStr((const unsigned char*)" mseconds needed for command.\r\n", io->stdOut);
  FSSH1_SendStr((const unsigned char*)"done!\r\n", io->stdOut);
}
#endif /* PL_HAS_SD_CARD */

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
static uint8_t ParseCommand(const unsigned char *cmd, bool *handled, const FSSH1_StdIOType *io) {
  /* handling our own commands */
#if PL_HAS_SD_CARD
  if (UTIL1_strcmp((char*)cmd, FSSH1_CMD_HELP)==0) {
    FSSH1_SendHelpStr((const unsigned char*)"run benchmark", (const unsigned char*)"Run FatFS benchmark\r\n", io->stdOut);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "run benchmark")==0) {
    benchmark(io);
    *handled = TRUE;
  }
#endif
  return ERR_OK;
}

static portTASK_FUNCTION(ShellTask, pvParameters) {
  unsigned char cmd_buf[32];
#if PL_HAS_SD_CARD
  bool cardMounted = FALSE;
  static FAT1_FATFS fileSystemObject;
#endif

  (void)pvParameters;
  FSSH1_Init();
  (void)FSSH1_ParseCommand((const unsigned char*)FSSH1_CMD_HELP, FSSH1_GetStdio(), ParseCommand);
  cmd_buf[0] = '\0';
  for(;;) {
#if PL_HAS_SD_CARD
    (void)FSSH1_CheckCardPresence(&cardMounted,
        0 /* volume */, &fileSystemObject, FSSH1_GetStdio());
#endif
    (void)FSSH1_ReadAndParseLine(cmd_buf, sizeof(cmd_buf), FSSH1_GetStdio(), ParseCommand /* local cmd parser */);
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
    LED2_Neg();
  };
}

void SHELL_Init(void) {
  if (FRTOS1_xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+550, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}


/**
 * \file
 * \brief GPS Data Logger Implementation
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This module implements the interface of the data logger.
 */

#include "Platform.h"
#if PL_HAS_LOGGER
#include "Logger.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#include "FAT1.h"
#include "TmDt1.h"
#include "NMEA.h"

static FAT1_FATFS fileSystemObject;
static FIL fp;

static void Err(void) {
  for(;;){}
}

static void LogToFile(int16_t x, int16_t y, int16_t z) {
  uint8_t write_buf[64];
  uint8_t pos_buf[20];
  UINT bw;
  TIMEREC time;

  /* open file */
  if (FAT1_open(&fp, "./log.txt", FA_OPEN_ALWAYS|FA_WRITE)!=FR_OK) {
    Err();
  }
  /* move to the end of the file */
  if (FAT1_lseek(&fp, fp.fsize) != FR_OK || fp.fptr != fp.fsize) {
    Err();
  }
  /* get time */
  if (TmDt1_GetTime(&time)!=ERR_OK) {
    Err();
  }
  /* write data */
  write_buf[0] = '\0';
  /* time */
  UTIL1_strcatNum16uFormatted(write_buf, sizeof(write_buf), time.Hour, '0', 2);
  UTIL1_chcat(write_buf, sizeof(write_buf), ':');
  UTIL1_strcatNum16uFormatted(write_buf, sizeof(write_buf), time.Min, '0', 2);
  UTIL1_chcat(write_buf, sizeof(write_buf), ':');
  UTIL1_strcatNum16uFormatted(write_buf, sizeof(write_buf), time.Sec, '0', 2);
  UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
  /* position */
  if (NMEA_GetPosString(pos_buf, sizeof(pos_buf), TRUE)!=ERR_OK) {
    UTIL1_strcpy(pos_buf, sizeof(pos_buf), (uint8_t*)"FAIL");
  }
  UTIL1_strcat(write_buf, sizeof(write_buf), pos_buf);
  UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
  if (NMEA_GetPosString(pos_buf, sizeof(pos_buf), FALSE)!=ERR_OK) {
    UTIL1_strcpy(pos_buf, sizeof(pos_buf), (uint8_t*)"FAIL");
  }
  UTIL1_strcat(write_buf, sizeof(write_buf), pos_buf);
  UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
  /* accelerometer */
  UTIL1_strcatNum16s(write_buf, sizeof(write_buf), x);
  UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
  UTIL1_strcatNum16s(write_buf, sizeof(write_buf), y);
  UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
  UTIL1_strcatNum16s(write_buf, sizeof(write_buf), z);
  UTIL1_strcat(write_buf, sizeof(write_buf), (unsigned char*)"\r\n");


  if (FAT1_write(&fp, write_buf, UTIL1_strlen((char*)write_buf), &bw)!=FR_OK) {
    (void)FAT1_close(&fp);
    Err();
  }
  /* closing file */
  (void)FAT1_close(&fp);
}

static portTASK_FUNCTION(LogTask, pvParameters) {
  int16_t x, y, z;

  (void)pvParameters; /* parameter not used */
  //res = FX1_Enable(); /* enable accelerometer (just in case) */
  //if (res!=ERR_OK) {
  //  Err();
  //}
  if (FAT1_Init()!=ERR_OK) { /* initialize FAT driver */
    Err();
  }
  if (FAT1_mount(0, &fileSystemObject) != FR_OK) { /* mount file system */
    Err();
  }
  for(;;) {
    /* get accelerometer values */
    x = 0; //FX1_GetX();
    y = 0; //FX1_GetY();
    z = 0; //FX1_GetZ();
    /* log it to the file on the SD card */
    LogToFile(x, y, z);
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  }
}

void LOG_Init(void) {
  if (FRTOS1_xTaskCreate(
        LogTask,  /* pointer to the task */
        "Log", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE+200, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}

#endif /* PL_HAS_LOGGER */

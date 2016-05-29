/*
 * DataLogger.c
 *
 *  Created on: 22.11.2015
 *      Author: tastyger
 */


#include "Platform.h"
#if PL_CONFIG_HAS_LOGGER
#include "DataLogger.h"
#include "FreeRTOS.h"
#include "LED1.h"
#include "FAT1.h"
#include "UTIL1.h"
#include "TmDt1.h"
#include "CLS1.h"

#define LOGGER_PERIOD_MS   1000         /* period between logs */
#define LOGGER_FILE_NAME   "./log.txt"  /* data log file name */

static FIL file; /* file system object */
static int nofErr = 0;

static void Err(uint8_t *str) {
  nofErr++;
  CLS1_SendStr(str, CLS1_GetStdio()->stdErr);
}

static void LogToFile(FIL *fp, int16_t x, int16_t y, int16_t z) {
  uint8_t write_buf[48];
  UINT bw;
  TIMEREC time;

  if (fp==NULL) {
    Err("File is NULL!\r\n");
    return;
  }
  /* get time */
  if (TmDt1_GetTime(&time)!=ERR_OK) {
    Err("Failed getting time/date\r\n");
  }
  /* write data */
  write_buf[0] = '\0';
  UTIL1_strcatNum8u(write_buf, sizeof(write_buf), time.Hour);
  UTIL1_chcat(write_buf, sizeof(write_buf), ':');
  UTIL1_strcatNum8u(write_buf, sizeof(write_buf), time.Min);
  UTIL1_chcat(write_buf, sizeof(write_buf), ':');
  UTIL1_strcatNum8u(write_buf, sizeof(write_buf), time.Sec);
  UTIL1_chcat(write_buf, sizeof(write_buf), '\t');

  UTIL1_strcatNum16s(write_buf, sizeof(write_buf), x);
  UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
  UTIL1_strcatNum16s(write_buf, sizeof(write_buf), y);
  UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
  UTIL1_strcatNum16s(write_buf, sizeof(write_buf), z);
  UTIL1_strcat(write_buf, sizeof(write_buf), (unsigned char*)"\r\n");

  if (FAT1_write(fp, write_buf, UTIL1_strlen((char*)write_buf), &bw)!=FR_OK) {
    Err("Failed writing buffer!\r\n");
    //(void)FAT1_close(&fp);
  }
#if 0
  /* closing file */
  if (FAT1_close(fp)!=FR_OK) {
    Err("Failed closing file!\r\n");
  }
#else
  if (FAT1_sync(fp)!=FR_OK) {
    Err("Failed closing file!\r\n");
  }
#endif
}

static void logger_task(void *param) {
  (void)param;
  bool cardMounted = FALSE;
  static FAT1_FATFS fileSystemObject;
  uint8_t res;
  TickType_t xLastWakeTime;
  FIL *fp = NULL;

  xLastWakeTime = xTaskGetTickCount();
  FAT1_Init(); /* initialize FAT module */
  for(;;) { /* breaks */
    do {
      res = FAT1_CheckCardPresence(&cardMounted, (unsigned char*)"0" /*volume*/, &fileSystemObject, CLS1_GetStdio());
      if (!cardMounted) {
        fp = NULL;
        LED1_Neg();
        FRTOS1_vTaskDelay(pdMS_TO_TICKS(50));
      }
    } while (res!=ERR_OK || !cardMounted);
    /* here we have the card inserted and properly mounted */
    if (fp==NULL) {
      /* open file */
      if (FAT1_open(&file, LOGGER_FILE_NAME, FA_OPEN_ALWAYS|FA_WRITE)!=FR_OK) {
        Err("Failed to open file!\r\n");
      }
      /* move to the end of the file */
      if (FAT1_lseek(&file, file.fsize) != FR_OK || file.fptr != file.fsize) {
        Err("Failed lseek\r\n");
      }
      fp = &file;
    }
    LED1_Neg();
    LogToFile(fp, 1,2,3);
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(LOGGER_PERIOD_MS));
  } /* for */
}

#define LOGGER_TASK_SIZE   configMINIMAL_STACK_SIZE+100
#if configSUPPORT_STATIC_ALLOCATION
  #if configUSE_HEAP_SECTION_NAME
    #define SECTION __attribute__((section (configHEAP_SECTION_NAME_STRING)))
  #else
    #define SECTION /* empty */
  #endif
  static StaticTask_t SECTION xTaskTCBBuffer;
  static StackType_t SECTION xStack[LOGGER_TASK_SIZE];
#endif

void LOGGER_Init(void) {
#if configSUPPORT_STATIC_ALLOCATION
  if (xTaskCreateStatic(logger_task, "Logger", LOGGER_TASK_SIZE, NULL, tskIDLE_PRIORITY+2, &xStack[0], &xTaskTCBBuffer)==NULL) {
    for(;;){} /* task creation failed */
  }
#elif configSUPPORT_DYNAMIC_ALLOCATION
  if (xTaskCreate(logger_task, "Logger", LOGGER_TASK_SIZE, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error! probably out of memory */
  }
#else
  #error "Either configSUPPORT_STATIC_ALLOCATION or configSUPPORT_DYNAMIC_ALLOCATION has to be enabled"
#endif
}

#endif /* PL_CONFIG_HAS_LOGGER */

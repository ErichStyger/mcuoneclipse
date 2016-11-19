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
#include "LEDR.h"
#include "LEDG.h"
#if PL_HAS_GPS
  #include "NMEA.h"
#endif
#if PL_HAS_ACCEL
  #include "MMA1.h"
#endif

#if !PL_HAS_SHELL
static FAT1_FATFS fileSystemObject;
#endif
static FIL LOG_LogFile;
static bool LOG_doLogging;

static void Err(uint8_t *msg) {
#if PL_HAS_SHELL
  CLS1_SendStr(msg, CLS1_GetStdio()->stdErr);
  FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
#else
  (void)msg; /* not used */
#endif
  taskDISABLE_INTERRUPTS();
  for(;;){}
}

uint8_t LOG_StopLogging(void) {
  LOG_doLogging = FALSE;
  if (FAT1_close(&LOG_LogFile)!=FR_OK) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t LOG_StartLogging(void) {
  /* open file */
  if (FAT1_open(&LOG_LogFile, "./log.txt", FA_OPEN_ALWAYS|FA_WRITE)!=FR_OK) {
    Err((uint8_t*)"Open file failed");
    return ERR_FAILED;
  }
  /* move to the end of the file */
  if (FAT1_lseek(&LOG_LogFile, f_size(&LOG_LogFile)) != FR_OK || LOG_LogFile.fptr != f_size(&LOG_LogFile)) {
    Err((uint8_t*)"lseed failed");
    return ERR_FAILED;
  }
  LOG_doLogging = TRUE;
  return ERR_OK;
}

static uint8_t LogToFile(FIL *file) {
#if PL_HAS_ACCEL
  int16_t x, y, z;
#endif
  uint8_t write_buf[96];
  uint8_t gps_buf[20];
  UINT bw;
  TIMEREC time;
  DATEREC date;

  /* get date */
  if (TmDt1_GetDate(&date)!=ERR_OK) {
    Err((uint8_t*)"Get Date failed");
  }
  /* write data */
  write_buf[0] = '\0';
  /* time */
  UTIL1_strcatNum16uFormatted(write_buf, sizeof(write_buf), date.Day, '0', 2);
  UTIL1_chcat(write_buf, sizeof(write_buf), '.');
  UTIL1_strcatNum16uFormatted(write_buf, sizeof(write_buf), date.Month, '0', 2);
  UTIL1_chcat(write_buf, sizeof(write_buf), '.');
  UTIL1_strcatNum16uFormatted(write_buf, sizeof(write_buf), date.Year, '0', 4);
  UTIL1_chcat(write_buf, sizeof(write_buf), '\t');

  /* get time */
  if (TmDt1_GetTime(&time)!=ERR_OK) {
    Err((uint8_t*)"Get Time failed");
  }

  /* time */
  UTIL1_strcatNum16uFormatted(write_buf, sizeof(write_buf), time.Hour, '0', 2);
  UTIL1_chcat(write_buf, sizeof(write_buf), ':');
  UTIL1_strcatNum16uFormatted(write_buf, sizeof(write_buf), time.Min, '0', 2);
  UTIL1_chcat(write_buf, sizeof(write_buf), ':');
  UTIL1_strcatNum16uFormatted(write_buf, sizeof(write_buf), time.Sec, '0', 2);
  UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
#if PL_HAS_GPS
  /* GPS position */
  if (NMEA_GetPosString(gps_buf, sizeof(gps_buf), TRUE)!=ERR_OK) {
    UTIL1_strcpy(gps_buf, sizeof(gps_buf), (uint8_t*)"FAIL");
  }
  UTIL1_strcat(write_buf, sizeof(write_buf), gps_buf);
  UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
  if (NMEA_GetPosString(gps_buf, sizeof(gps_buf), FALSE)!=ERR_OK) {
    UTIL1_strcpy(gps_buf, sizeof(gps_buf), (uint8_t*)"FAIL");
  }
  UTIL1_strcat(write_buf, sizeof(write_buf), gps_buf);
  UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
  /* speed */
  if (NMEA_GetSpeedString(gps_buf, sizeof(gps_buf))!=ERR_OK) {
    UTIL1_strcpy(gps_buf, sizeof(gps_buf), (uint8_t*)"FAIL");
  }
  UTIL1_strcat(write_buf, sizeof(write_buf), gps_buf);
  UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
  /* angle */
  if (NMEA_GetAngleString(gps_buf, sizeof(gps_buf))!=ERR_OK) {
    UTIL1_strcpy(gps_buf, sizeof(gps_buf), (uint8_t*)"FAIL");
  }
  UTIL1_strcat(write_buf, sizeof(write_buf), gps_buf);
  UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
#endif
#if PL_HAS_ACCEL
 /* get accelerometer values */
  x = MMA1_GetXmg();
  y = MMA1_GetYmg();
  z = MMA1_GetZmg();
  /* accelerometer */
  UTIL1_strcatNum16s(write_buf, sizeof(write_buf), x);
  UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
  UTIL1_strcatNum16s(write_buf, sizeof(write_buf), y);
  UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
  UTIL1_strcatNum16s(write_buf, sizeof(write_buf), z);
#endif
  UTIL1_strcat(write_buf, sizeof(write_buf), (unsigned char*)"\r\n");

  if (FAT1_write(file, write_buf, UTIL1_strlen((char*)write_buf), &bw)!=FR_OK) {
    Err((uint8_t*)"File write failed");
    return ERR_FAILED;
  }
  /* flush file */
  if (FAT1_sync(file)!=FR_OK) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

static portTASK_FUNCTION(LogTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
#if PL_HAS_ACCEL
  /* enable accelerometer (just in case) */
  if (MMA1_Enable()!=ERR_OK) {
    Err((uint8_t*)"MMA init failed");
  }
#endif
  if (FAT1_Init()!=ERR_OK) { /* initialize FAT driver */
    Err((uint8_t*)"FAT init failed");
  }
#if PL_HAS_SHELL
  /* mounting is done by shell, wait until it has finished it (\todo just temporary) */
  FRTOS1_vTaskDelay(2000/portTICK_RATE_MS);
#else
  if (FAT1_mount(0, &fileSystemObject) != FR_OK) { /* mount file system */
    Err((uint8_t*)"Mount failed");
  }
#endif
  if (LOG_doLogging) {
    LOG_StartLogging();
  }
  for(;;) {
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
    if (LOG_doLogging) {
      LEDR_Off(); LEDG_Neg(); /* blink green led if we have GPS data */
      if (LogToFile(&LOG_LogFile)!=ERR_OK) {
        Err((uint8_t*)"Logging failed");
      }
    } else {
      LEDR_Off(); LEDG_Off(); /* both LED's off */
    }
  }
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"log", (unsigned char*)"Group of logger commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  (on|off)", (unsigned char*)"Enable or disable logging\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"log", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  logging", LOG_doLogging?(const unsigned char*)"on\r\n":(const unsigned char*)"off\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t LOG_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "log help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "log status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "log on")==0) {
    *handled = TRUE;
    LOG_StartLogging();
  } else if (UTIL1_strcmp((char*)cmd, "log off")==0) {
    *handled = TRUE;
    LOG_StopLogging();
  }
  return ERR_OK;
}

void LOG_Init(void) {
  LOG_doLogging = TRUE;
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

/*
 * Application.c
 *
 *  Created on: 20.09.2015
 *      Author: tastyger
 */

#include "Platform.h"
#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "FRTOS1.h"
#include "PORT_PDD.h"
#include "FreeRTOS.h"
#if PL_HAS_SHELL
  #include "Shell.h"
#endif
#include "FAT1.h"

static void Err(uint8_t *msg) {
  /* generic error hook */
  SHELL_SendString(msg);
}

static void LogToFile(int16_t x) {
  FIL file;
  uint8_t write_buf[48];
  UINT bw;
  TIMEREC time;

  if (!FAT1_isDiskPresent("0")) {
    Err("Disk not present\r\n");
    return;
  } else {
    SHELL_SendString("logging data...\r\n");
  }
  /* open file */
  if (FAT1_open(&file, "./log.txt", FA_OPEN_ALWAYS|FA_WRITE)!=FR_OK) {
    Err("failed opening file\r\n");
  }
  /* move to the end of the file */
  if (FAT1_lseek(&file, f_size(&file)) != FR_OK || file.fptr != f_size(&file)) {
    Err("failed lseek\r\n");
  }
  /* get time */
  if (TmDt1_GetTime(&time)!=ERR_OK) {
    Err("Failed getting time\r\n");
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
  UTIL1_strcat(write_buf, sizeof(write_buf), (unsigned char*)"\r\n");
  if (FAT1_write(&file, write_buf, UTIL1_strlen((char*)write_buf), &bw)!=FR_OK) {
    (void)FAT1_close(&file);
    Err("Failed closing file\r\n");
  }
  /* closing file */
  (void)FAT1_close(&file);
}

static void AppTask(void *pvParameters) {
  uint8_t res;
  int i;

  (void)pvParameters; /* parameter not used */
  for(;;) {
    FRTOS1_vTaskDelay(5000/portTICK_PERIOD_MS);
    LED1_Neg(); /* Red LED */
   // LogToFile(i++);
  }
}

void APP_Run(void) {
#if PL_HAS_SD_CARD
  /* SD card detection: PTB16 with pull-down! */
  PORT_PDD_SetPinPullSelect(PORTB_BASE_PTR, 16, PORT_PDD_PULL_DOWN);
  PORT_PDD_SetPinPullEnable(PORTB_BASE_PTR, 16, PORT_PDD_PULL_ENABLE);
#endif
#if PL_HAS_SHELL
  SHELL_Init();
#endif
  LED1_On();
  LED1_Off();
  LED2_On();
  LED2_Off();
  LED3_On();
  LED3_Off();
  if (FRTOS1_xTaskCreate(
      AppTask,  /* pointer to the task */
      "Main", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE+200, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+1,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    for(;;){} /* error! probably out of memory */
  }
  FRTOS1_vTaskStartScheduler();
  for(;;) {}
}



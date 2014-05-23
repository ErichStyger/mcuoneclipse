/*
 * Application.c
 *
 *  Created on: 22.05.2014
 *      Author: tastyger
 */

#include "Application.h"
#include "WAIT1.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "FX1.h"
#include "FAT1.h"
#include "UTIL1.h"

static FAT1_FATFS fileSystemObject;
static FIL fp;

static void Err(void) {
  LED1_On();
  LED2_On();
  LED3_On();
  for(;;){}
}

static void LogToFile(int16_t x, int16_t y, int16_t z) {
  uint8_t write_buf[48];
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
  if (FAT1_write(&fp, write_buf, UTIL1_strlen((char*)write_buf), &bw)!=FR_OK) {
    (void)FAT1_close(&fp);
    Err();
  }
  /* closing file */
  (void)FAT1_close(&fp);
}

void APP_Run(void) {
  int16_t x,y,z;
  uint8_t res;
  #define ACCEL_VAL  2000

  res = FX1_Enable(); /* enable accelerometer (just in case) */
  if (res!=ERR_OK) {
    Err();
  }
  if (FAT1_Init()!=ERR_OK) {
    Err();
  }
  if (FAT1_mount(0, &fileSystemObject) != FR_OK) { /* mount file system */
    Err();
  }
  for(;;) {
    //LED1_Neg();
    x = FX1_GetX();
    y = FX1_GetY();
    z = FX1_GetZ();
    if (x>ACCEL_VAL || x<-ACCEL_VAL) {
      LED1_On();
      LED2_Off();
      LED3_Off();
    } else if (y>ACCEL_VAL || y<-ACCEL_VAL) {
      LED1_Off();
      LED2_On();
      LED3_Off();
    } else if (z>ACCEL_VAL || z<-ACCEL_VAL) {
      LED1_Off();
      LED2_Off();
      LED3_On();
    }
    LogToFile(x, y, z);
    WAIT1_Waitms(1000);
  }
}


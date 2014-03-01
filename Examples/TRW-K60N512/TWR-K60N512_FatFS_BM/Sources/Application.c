/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "LED4.h"
#include "FAT1.h"
#include "CLS1.h"
#include "WAIT1.h"
#include "UTIL1.h"

static FAT1_FATFS fileSystemObject;

static uint8_t Test(CLS1_ConstStdIOTypePtr io) {
  static FIL fp;
  UINT bw;
  uint8_t read_buf[16];
  uint8_t write_buf[10];
  uint8_t i;

  if (FAT1_isWriteProtected()) {
    CLS1_SendStr((unsigned char*)"disk is write protected!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  /* write file */
  CLS1_SendStr((const unsigned char*)"Creating test.txt...\r\n", io->stdOut);
  if (FAT1_open(&fp, "./test.txt", FA_CREATE_ALWAYS|FA_WRITE)!=FR_OK) {
    CLS1_SendStr((const unsigned char*)"*** Failed creating file!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  /* write text */
  if (FAT1_write(&fp, "Hello world ", sizeof("Hello world ")-1, &bw)!=FR_OK) {
    CLS1_SendStr((const unsigned char*)"*** Failed writing string!\r\n", io->stdErr);
    (void)FAT1_close(&fp);
    return ERR_FAILED;
  }
  write_buf[0] = '\0';
  for(i=0;i<4;i++) {
    UTIL1_strcatNum8u(write_buf, sizeof(write_buf), i);
    UTIL1_chcat(write_buf, sizeof(write_buf), ' ');
  }
  if (FAT1_write(&fp, write_buf, UTIL1_strlen((char*)write_buf), &bw)!=FR_OK) {
    CLS1_SendStr((const unsigned char*)"*** Failed writing string!\r\n", io->stdErr);
    (void)FAT1_close(&fp);
    return ERR_FAILED;
  }
  /* closing file */
  (void)FAT1_close(&fp);

  /* read from file */
  CLS1_SendStr((const unsigned char*)"Read from file...\r\n", io->stdOut);
  if (FAT1_open(&fp, "./test.txt", FA_READ)!=FR_OK) {
    CLS1_SendStr((const unsigned char*)"*** Failed opening file!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  if (FAT1_read(&fp, &read_buf[0], sizeof(read_buf)-2, &bw)!=FR_OK) {
    CLS1_SendStr((const unsigned char*)"*** Failed reading file!\r\n", io->stdErr);
    (void)FAT1_close(&fp);
    return ERR_FAILED;
  }
  read_buf[sizeof(read_buf)-2] = '\0'; /* terminate string */
  UTIL1_strcat(read_buf, sizeof(read_buf), (unsigned char*)"\r\n");
  CLS1_SendStr(read_buf, io->stdOut);
  CLS1_SendStr((const unsigned char*)"\r\n", io->stdOut);
  /* close file */
  (void)FAT1_close(&fp);
  return ERR_OK;
}

static void DiskTest(void) {
  CLS1_ConstStdIOTypePtr io;

  io = CLS1_GetStdio();
  if (FAT1_Init()!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"Failed FatFS initialization!\r\n", io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"Waiting for disk to be inserted...\r\n", io->stdOut);
  while(!FAT1_isDiskPresent()) {
    /* wait until card is present */
  }
  CLS1_SendStr((unsigned char*)"Mounting File system...\r\n", io->stdOut);
  FAT1_mount(0, &fileSystemObject); /* mount file system */
  (void)Test(io);
  CLS1_SendStr((unsigned char*)"Finished test...\r\n", io->stdOut);
  for(;;) {
    LED2_Neg();
    WAIT1_Waitms(100);
  }
}

void APP_Run(void) {
  LED1_Neg();
  LED2_Neg();
  LED3_Neg();
  LED4_Neg();
  DiskTest();
}


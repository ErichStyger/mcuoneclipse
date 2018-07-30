/*
 * Application.c
 *
 *  Created on: Mar 30, 2013
 *      Author: Erich Styger
 */

#include "Application.h"

#define USE_FREEMASTER     0

#include "MMA1.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "CLS1.h"
#if USE_FREEMASTER
  #include "FMSTR1.h"
#endif

#define ACCEL_G_MODE   2  /* 2, 4 or 8 g mode */

#if USE_FREEMASTER
/* global variables for FreeMaster */
static uint8_t AccelX, AccelY, AccelZ;
static FMSTR_APPCMD_CODE cmd; /* application command */
static FMSTR_APPCMD_PDATA cmdDataP; /* pointer to application command data */
static FMSTR_SIZE cmdSize; /* size of application command arguments */
static uint8_t stimulatedVar; /* variable stimulated with FreeMASTER */
#endif
static bool enableLED = TRUE; /* if LED's are used or not */

void APP_Run(void) {
  uint8_t res=ERR_OK;
  uint16_t xyz[3];
  uint8_t gScale;
  bool isEnabled;
  unsigned char ch;
  
  CLS1_SendStr((unsigned char*)"------------------------\r\nFRDM-KL25Z Accel\r\n------------------------\r\n", CLS1_GetStdio()->stdOut);
  LED1_On();
  LED2_On();
  LED3_On();
  res = MMA1_Init();
  if (res!=ERR_OK) {
    for(;;) {} /* error? */
  }
  WAIT1_Waitms(10);
  res = MMA1_SetFastMode(FALSE);
  if (res!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"FAILED setting fast mode\r\n", CLS1_GetStdio()->stdErr);
    for(;;) {} /* error? */
  }
  res = MMA1_isEnabled(&isEnabled);
  if(isEnabled) { /* have to disable device to set the g scale range! */
    CLS1_SendStr((unsigned char*)"Device is enabled, disable it before applying settings...\r\n", CLS1_GetStdio()->stdOut);
    res = MMA1_Disable();
    if (res!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"FAILED disabling device\r\n", CLS1_GetStdio()->stdErr);
      for(;;) {} /* error? */
    }
  }
  CLS1_printfIO(CLS1_GetStdio(), (unsigned char*)"Setting G mode to %d g.\r\n", ACCEL_G_MODE);
  res = MMA1_SetScaleRangeG(ACCEL_G_MODE); /* set to g scale */
  if (res!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"FAILED setting range\r\n", CLS1_GetStdio()->stdErr);
    for(;;) {} /* error? */
  }
  res = MMA1_GetScaleRangeG(&gScale); /* read back the value to check it */
  if (res!=ERR_OK || gScale!=ACCEL_G_MODE) {
    CLS1_SendStr((unsigned char*)"FAILED reading range\r\n", CLS1_GetStdio()->stdErr);
   for(;;) {} /* error? */
  }
  CLS1_SendStr((unsigned char*)"Enable device.\r\n", CLS1_GetStdio()->stdOut);
  res = MMA1_Enable(); /* re-enable device again */
  if (res!=ERR_OK) {
   CLS1_SendStr((unsigned char*)"FAILED enabling device\r\n", CLS1_GetStdio()->stdErr);
   for(;;) {} /* error? */
  }
  CLS1_SendStr((unsigned char*)"X axis calibration (1g for X): place the board with the USB connector pointing to the sky and press a key...\r\n", CLS1_GetStdio()->stdOut);
  do {
    WAIT1_Waitms(50);
  } while(!CLS1_KeyPressed());
  do {
    WAIT1_Waitms(50);
    CLS1_ReadChar(&ch); /* empty input buffer */
  } while(ch!='\0');
  MMA1_CalibrateX1g();

  CLS1_SendStr((unsigned char*)"Y axis calibration (1g for Y): place the board with the right arduino rows down and press a key...\r\n", CLS1_GetStdio()->stdOut);
  do {
    WAIT1_Waitms(50);
  } while(!CLS1_KeyPressed());
  do {
    WAIT1_Waitms(50);
    CLS1_ReadChar(&ch); /* empty input buffer */
  } while(ch!='\0');
  MMA1_CalibrateY1g();

  CLS1_SendStr((unsigned char*)"Z axis calibration (1g for Z): place the board flat on a table and press a key...\r\n", CLS1_GetStdio()->stdOut);
  do {
    WAIT1_Waitms(50);
  } while(!CLS1_KeyPressed());
  do {
    WAIT1_Waitms(50);
    CLS1_ReadChar(&ch); /* empty input buffer */
  } while(ch!='\0');
  MMA1_CalibrateZ1g();  /* for this, place the board flat */

  CLS1_SendStr((unsigned char*)"done!\r\n", CLS1_GetStdio()->stdOut);
  while (res==ERR_OK) {
    xyz[0] = MMA1_GetX();
    xyz[1] = MMA1_GetY();
    xyz[2] = MMA1_GetZ();
    CLS1_printfIO(CLS1_GetStdio(), "x: %d y: %d, z: %d\r\n", (int16_t)xyz[0], (int16_t)xyz[1], (int16_t)xyz[2]);
    if (enableLED) {
      LED1_Put(xyz[0]>50);
      LED2_Put(xyz[1]>50);
      LED3_Put(xyz[2]>50);
    }
#if USE_FREEMASTER
    /* stimulated variable by FreeMaster: turn OFF LEDs if variable is greater than 0 */
    if (stimulatedVar>0) { /* turn off LEDs */
      LED1_Off();
      LED2_Off();
      LED3_Off();
    }
    /* check application commands */
    cmd = FMSTR1_GetAppCmd();
    if (cmd!=FMSTR_APPCMDRESULT_NOCMD) { /* received command */
      cmdDataP = FMSTR1_GetAppCmdData(&cmdSize);
      if (cmd==0 && cmdSize==1) { /* ToggleLED_cmd (id: 0) has just one byte argument */
        switch(*cmdDataP) {
          case 0: 
            LED1_Neg();
            FMSTR1_AppCmdAck(0); /* acknowledge the command */
            break;
          case 1: 
            LED2_Neg();
            FMSTR1_AppCmdAck(0); /* acknowledge the command */
            break;
          case 2: 
            LED3_Neg();
            FMSTR1_AppCmdAck(0); /* acknowledge the command */
            break;
          default: 
            FMSTR1_AppCmdAck(1); /* failed */
            break;
        }
      } else {
        FMSTR1_AppCmdAck(1); /* acknowledge the command with failure code */
      }
    }
    /* FreeMaster needs global variables... */
    AccelX = xyz[0];
    AccelY = xyz[1];
    AccelZ = xyz[2];
    FMSTR1_Poll();
    FMSTR1_Recorder();
#endif
    WAIT1_Waitms(100);
  }
  /* get here if things were failing... */
  LED1_Off();
  LED2_Off();
  LED3_Off();
}

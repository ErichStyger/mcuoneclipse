/*
 * Application.c
 *
 *  Created on: Mar 30, 2013
 *      Author: Erich Styger
 */

#include "Application.h"

#define USE_PEX_COMPONENT  1
#define USE_FREEMASTER     0

#if !USE_PEX_COMPONENT
#include "MMA8451.h"
#else
#include "MMA1.h"
#endif
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#if USE_FREEMASTER
  #include "FMSTR1.h"
#endif

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
  uint8_t xyz[3];
  uint8_t gScale;
  bool isEnabled;
  
  LED1_On();
  LED2_On();
  LED3_On();
#if USE_PEX_COMPONENT
  res = MMA1_Init();
  if (res!=ERR_OK) {
    for(;;) {} /* error? */
  }
  WAIT1_Waitms(10);
  res = MMA1_SetFastMode(FALSE);
#else
  res = MMA8451_Init();
#endif
  if (res!=ERR_OK) {
    for(;;) {} /* error? */
  }
  res = MMA1_isEnabled(&isEnabled);
  if(isEnabled) { /* have to disable device to set the g scale range! */
    res = MMA1_Disable();
    if (res!=ERR_OK) {
      for(;;) {} /* error? */
    }
    res = MMA1_SetScaleRangeG(4); /* set to 4g scale */
    if (res!=ERR_OK) {
      for(;;) {} /* error? */
    }
    res = MMA1_GetScaleRangeG(&gScale); /* read back the value to check it */
    if (res!=ERR_OK || gScale!=4) {
      for(;;) {} /* error? */
    }
    res = MMA1_Enable(); /* re-enable device again */
    if (res!=ERR_OK) {
      for(;;) {} /* error? */
    }
  }
  while (res==ERR_OK) {
#if USE_PEX_COMPONENT
    xyz[0] = MMA1_GetX()>>8;
    xyz[1] = MMA1_GetY()>>8;
    xyz[2] = MMA1_GetZ()>>8;
#else
    res = MMA8451_GetRaw8XYZ(&xyz[0]);
#endif
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
  }
  /* get here if things were failing... */
  LED1_Off();
  LED2_Off();
  LED3_Off();
}

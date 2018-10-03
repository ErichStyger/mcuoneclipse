/*
 * Application.c
 *
 *  Created on: Mar 30, 2013
 *      Author: Erich Styger
 */

#include "Application.h"

#define USE_FREEMASTER     1

#include "MMA1.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "FMSTR1.h"

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
  bool isEnabled;
  
  LED1_On();
  LED2_On();
  LED3_On();
  res = MMA1_Init();
  res = MMA1_isEnabled(&isEnabled);
  if (!isEnabled) {
    res = MMA1_Enable();
  }
  res = MMA1_SetFastMode(FALSE);
  while (res==ERR_OK) {
    xyz[0] = MMA1_GetX()>>8;
    xyz[1] = MMA1_GetY()>>8;
    xyz[2] = MMA1_GetZ()>>8;
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

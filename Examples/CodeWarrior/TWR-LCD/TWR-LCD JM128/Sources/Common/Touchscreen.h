/** ###################################################################
**     Filename  : Touchscreen.H
**     Project   : TWR_LCD_JM128
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 29.01.2010, 11:00
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __Touchscreen_H
#define __Touchscreen_H

#include "PE_Types.h"

byte TouchScreen_CalibrateAndFlash(void);
  /* Performs a calibration, stores the calibration data in permanent memory. Returns ERR_OK if everything is fine */

void TouchScreen_CheckTouchScreenCalibrationData(void);
  /* Checks if we already have some calibration data stored in flash.
     If not, perform calibration and store in flash */

#endif


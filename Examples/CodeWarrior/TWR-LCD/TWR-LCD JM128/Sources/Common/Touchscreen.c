/** ###################################################################
**     Filename  : Touchscreen.C
**     Project   : TWR_LCD_JM128
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 29.01.2010, 11:00
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE Touchscreen */

#include "Platform.h"

#if PL_HAS_HW_TOUCHSCREEN
#include "Touchscreen.h"
#include "TCHS1.h"
#if PL_HAS_TOUCH_CALIB_FLASH
  #include "IFsh1.h" /* internal flash programmer */
#endif

byte TouchScreen_CalibrateAndFlash(void) {
  /* stores the calibration data in permanent memory. Returns ERR_OK if everything is fine */
#if PL_HAS_TOUCH_CALIB_FLASH
  byte i, res;
#endif
  byte nofBytes, *byteP; 
  
  TCHS1_Calibrate(GDisp1_COLOR_WHITE, GDisp1_COLOR_BLUE);
  TCHS1_GetCalibrationData(&byteP, &nofBytes);
#if PL_HAS_TOUCH_CALIB_FLASH
  res = IFsh1_EraseSector(PL_TOUCHSCREEN_FLASH_CALIBRATION_ADDRESS);
  if (res==ERR_OK) {
    for (i=0; i<nofBytes; i++) {
      res = IFsh1_SetByteFlash((IFsh1_TAddress)(PL_TOUCHSCREEN_FLASH_CALIBRATION_ADDRESS+i), byteP[i]);
      if (res != ERR_OK) {
       return ERR_FAILED; /* error case */
      }
    }
  }
#endif
  return ERR_OK;
}

void TouchScreen_CheckTouchScreenCalibrationData(void) {
  /* Checks if we already have some calibration data stored in flash.
     If not, perform calibration and store in flash */
#if PL_HAS_TOUCH_CALIB_FLASH
  if (!TCHS1_isCalibrated()) {
    byte *byteP, nofBytes;
  
    byteP = (byte*)PL_TOUCHSCREEN_FLASH_CALIBRATION_ADDRESS;
    if ((*byteP) == 0xff) { /* flash erased, no calibration data available */
      /* show calibration screen to user */
      (void)TouchScreen_CalibrateAndFlash();
    } else { /* use calibration data from flash */
      /* get needed size from the driver */
      TCHS1_GetCalibrationData(&byteP, &nofBytes);
      byteP = (byte*)PL_TOUCHSCREEN_FLASH_CALIBRATION_ADDRESS;
      TCHS1_SetCalibrationData(byteP, nofBytes);
    }
  }
#endif
}

#endif /* PL_HAS_HW_TOUCHSCREEN */


/* END Touchscreen */

/** ###################################################################
**     Filename  : SDcard.H
**     Project   : TWR_LCD_JM128
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 24.01.2010, 11:19
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __SDcard_H
#define __SDcard_H

/* MODULE SDcard */

#include "platform.h"
#include "UI1.h"

typedef struct {
  UI1_Screen screen;
  UI1_Window window;
  UI1_Header header;
  UI1_Icon iconClose;
  UI1_CheckBox chkBoxCardPresent;
  UI1_CheckBox chkBoxWriteProtected;
  UI1_Text txt;
  UI1_Button btnDirectory;
  UI1_Button btnDataFile;
} SDC_WindowDesc;

void SDC_StartTask(SDC_WindowDesc *desc);

/*! \brief Error handler to be called from the SD card driver */
void SDC_Err(void);

/* END SDcard */

#endif


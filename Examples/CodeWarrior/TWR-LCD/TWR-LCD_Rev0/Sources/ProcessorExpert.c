/** ###################################################################
**     Filename  : ProcessorExpert.C
**     Project   : ProcessorExpert
**     Processor : MCF51CN128CLK
**     Version   : Driver 01.00
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 30.05.2010, 18:36
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "XF1.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "LED4.h"
#include "LEDpin4.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "TRG1.h"
#include "FRTOS1.h"
#include "RTOSSWI1.h"
#include "TickCntr1.h"
#include "AD1.h"
#include "ACCEL1.h"
#include "EVNT1.h"
#include "BuzzerPPG.h"
#include "KEY1.h"
#include "keyPin1.h"
#include "MultiKey1.h"
#include "KEY2.h"
#include "Inhr1.h"
#include "Inhr2.h"
#include "TCHS1.h"
#include "Sensor1.h"
#include "Xminus1.h"
#include "Yminus1.h"
#include "Xplus1.h"
#include "Yplus1.h"
#include "GDisp1.h"
#include "LCD1.h"
#include "RESpin1.h"
#include "ALE1.h"
#include "Cour08n.h"
#include "Cour08b.h"
#include "Helv14n.h"
#include "Helv12n.h"
#include "Helv24n.h"
#include "Helv18n.h"
#include "Helv10n.h"
#include "Helv08n.h"
#include "TmDt1.h"
#include "UICalendar1.h"
#include "UI1.h"
#include "FDisp1.h"
#include "IFsh1.h"
#include "UIG1.h"
#include "WDog1.h"
#include "CS1.h"
#include "MCUC1.h"
#include "CLS1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "platform.h"
#include "RTOS.h"
#if PL_TWR_BOOTLOADER
  #include "Bootloader.h"
#endif

static bool CanUseDisplay(void) {
#if PL_BOARD_LCD /* we are the TWR-LCD board */
  PS2_SetInput();
  if (PS2_GetVal()!=0) {
    /* SW1-1 (PS2) OFF/high => EBI (8 or 16bit) protocol: this is not supported for the JM128 on the TWR-LCD
       PS2|PS1:  OFF ON : SPI serial protocol to the LCD
       PS2|PS1:  ON  OFF: EBI/16bit protocol to the LCD
       PS2|PS1:  ON  ON : EBI/8bit protocol to the LCD
    */
    return TRUE;
  }
  return FALSE;
#else /* we are a tower board */
  return TRUE;
#endif
}

static bool CanUseTouchPanel(void) {
#if PL_BOARD_LCD /* we are the TWR-LCD board */
  /* Check DIL switch SW1-6 (TP_SEL): Default is ON/low level for standalone mode (JM128 is using touch panel) */
  TP_SEL_SetInput();
  if (TP_SEL_GetVal()!=0) { /* high: Tower CPU is using touch panel */
    return FALSE;
  }
  return TRUE;
#else
  return TRUE;
#endif
}

void main(void) {
  /* Write your local variable definition here */
#if PL_BOARD_LCD
  /* NOTE: the JM128 on the TWR-LCD needs at least to pull-up the microSD card
     detection pin, otherwise the signal is floating for the the driver in U5A */
  PTGPE_PTGPE3 = 1; /* pull up enable for card detection line. Otherwise a CPU on the elevator will not be able to read the SD card detection signal */
#endif
#if PL_BOARD_LCD && !PL_IS_BOOTLOADER && !PL_APP_MODE_I2C_LCD /* we are the TWR-LCD, and not the bootloader or the I2C application */
  /* if we are not the bootloader:
     - if JM_ELE (SW1-3) is ON/low, then TWR CPU has control over the display (tristate lines)
     - if EuSD   (SW1-4) is ON/low, then TWR CPU has control over the microSD card (tristate lines, pull-up CD line)
     - if TP_SEL (SW1-6) is OFF/high, then TWR CPU has control over the touch panel lines (tristate lines)
  */
  if (!CanUseTouchPanel()) {
    for(;;) {}
  }
  if (!CanUseDisplay()) {
    for(;;) {}
  }
#endif
#if PL_HAS_BOOTLOADER
  BL_RedirectUserVectors(); /* need to redirect vectors before initializing the drivers below */
#endif
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

#if PL_IS_BOOTLOADER
  BL_Bootloader(); /* does not return */
#else
  RTOS_Start(); /* does not return */
#endif
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*
** ###################################################################
**
**     This file was created by Processor Expert 4.00 Beta [04.40]
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/

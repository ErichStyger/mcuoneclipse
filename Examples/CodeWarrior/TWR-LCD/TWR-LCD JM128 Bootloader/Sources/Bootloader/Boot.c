/*
 * Boot.c
 *
 *  Created on: 10.03.2011
 *      Author: Erich Styger
 */
#include "platform.h"
#include "Boot.h"
#if PL_HAS_RTOS
  #include "RTOS.h"
#endif
#if PL_HAS_BOOTLOADER || PL_IS_BOOTLOADER
  #include "Bootloader.h"
#endif
#if PL_BOARD_LCD
  #include "PS2.h"
  #include "TP_SEL.h"
#endif

#if PL_BOARD_LCD
static bool CanUseDisplay(void) {
#if PL_BOARD_LCD /* we are the TWR-LCD board */
  PS2_SetInput();
  if (PS2_GetVal()!=0) {
    /* SW1-1 (PS2) OFF/high => EBI (8 or 16bit) protocol: this is not supported for the JM128 on the TWR-LCD1
       PS2|PS1:  OFF ON : SPI serial protocol to the LCD1
       PS2|PS1:  ON  OFF: EBI/16bit protocol to the LCD1
       PS2|PS1:  ON  ON : EBI/8bit protocol to the LCD1
    */
    return TRUE;
  }
  return FALSE;
#else /* we are a tower board */
  return TRUE;
#endif
}
#endif

#if PL_BOARD_LCD
static bool CanUseTouchPanel(void) {
#if PL_BOARD_LCD /* we are the TWR-LCD board */
  /* Check DIL switch SW1-6 (TP_SEL): Default is OFF/high level for standalone mode (JM128 is using touch panel) */
  TP_SEL_SetInput();
  if (TP_SEL_GetVal()==0) { /* low: Tower CPU is using touch panel */
    return FALSE;
  }
  return TRUE;
#else
  return TRUE;
#endif
}
#endif

void BOOT_PreInit(void) {
#if PL_BOARD_LCD
  /* NOTE: the JM128 on the TWR-LCD1 needs at least to pull-up the microSD card
     detection pin, otherwise the signal is floating for the the driver in U5A */
 PTGPE_PTGPE3 = 1; /* pull up enable for card detection line. Otherwise a CPU on the elevator will not be able to read the SD card detection signal */
#endif
#if PL_BOARD_LCD && !PL_IS_BOOTLOADER && !PL_APP_MODE_I2C_LCD /* we are the TWR-LCD1, and not the bootloader or the I2C application */
  /* if we are not the bootloader:
     - if JM_ELE (SW1-3) is ON/low, then TWR CPU has control over the display (tristate lines)
     - if EuSD   (SW1-4) is ON/low, then TWR CPU has control over the microSD card (tristate lines, pull-up CD line)
     - if TP_SEL (SW1-6) is ON/low, then TWR CPU has control over the touch panel lines (tristate lines)
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
}

void BOOT_Start(void) {
#if PL_IS_BOOTLOADER
  BL_Bootloader(); /* does not return */
#else
  RTOS_Start(); /* does not return */
#endif
}


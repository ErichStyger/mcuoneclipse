/*
 * application.c
 *      Author: Erich Styger
 */

/* own modules and standard library */
#include "platform.h"
#include "application.h" /* own interface */

/* own modules */
#include "oled.h"

void APP_Run(void) {
  PL_Init();
  OLED_doOLED();
}

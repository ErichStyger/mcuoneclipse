/*
 * Application.h
 *
 *      Author: Erich Styger
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Cpu.h"

#define APP_HAS_SD_CARD  (defined(PEcfg_SD_CARD)&&PEcfg_SD_CARD==1) /* if we have SD card support, macro PEcfg_SD_CARD defined in Cpu.h */
#define APP_HAS_USB_CDC  0 /* if we have an additional USB CDC channel */

void APP_Run(void);

#endif /* APPLICATION_H_ */

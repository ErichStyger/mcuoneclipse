/*
 * Application.c
 *
 *  Created on: 27.12.2015
 *      Author: tastyger
 */


#include "Application.h"
#include "SM1.h"
#include "WAIT1.h"
#include "LED1.h"
#include "AdaBLE.h"


static void Test(void) {
  ABLE_sendPacket(SDEP_CMDTYPE_AT_WRAPPER, "AT\n", sizeof("AT\n")-1, 0);
  ABLE_getResponse();
}

static bool doIt = FALSE;

void APP_Run(void) {
  ABLE_Init();

  for(;;) {
    if (doIt) {
      Test();
    }
    LED1_Neg();
    WAIT1_Waitms(500);
  }
}

/*
 * RStack.c
 *
 *  Created on: Nov 8, 2013
 *      Author: tastyger
 */

#include "Platform.h"
#if PL_HAS_RADIO
#include "RStack.h"
#include "Radio.h"
#include "RMSG.h"
#include "RPHY.h"
#include "RMAC.h"
#include "RNWK.h"
#if PL_HAS_RSTDIO
#include "RStdIO.h"
#endif
#include "RApp.h"

void RSTACK_Init(void) {
  RADIO_Init();
  RMSG_Init();
  RPHY_Init();
  RMAC_Init();
  RNWK_Init();
#if PL_HAS_RSTDIO
  RSTDIO_Init();
#endif
  RAPP_Init();
}

void RSTACK_Deinit(void) {
  RAPP_Deinit();
#if PL_HAS_RSTDIO
  RSTDIO_Deinit();
#endif
  RNWK_Deinit();
  RMAC_Deinit();
  RPHY_Deinit();
  RMSG_Deinit();
  RADIO_Deinit();
}
#endif

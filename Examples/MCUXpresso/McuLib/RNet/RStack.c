/**
 * \file
 * \brief This main init module for the stack.
 * \author (c) 2013-2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module is used to simplify stack initialization.
 */

#include "McuRNetConfig.h"
#if McuRNET_CONFIG_IS_ENABLED
#include "RStack.h"
#include "Radio.h"
#include "RMSG.h"
#include "RPHY.h"
#include "RMAC.h"
#include "RNWK.h"
#include "RStdIO.h"
#include "RApp.h"

void RSTACK_Init(void) {
  /*lint -save -e522 function lacks side-effects */
  RADIO_Init();
  RMSG_Init();
  RPHY_Init();
  RMAC_Init();
  RNWK_Init();
  RSTDIO_Init();
  RAPP_Init();
  /*lint -restore */
}

void RSTACK_Deinit(void) {
  /*lint -save -e522 function lacks side-effects */
  RAPP_Deinit();
  RSTDIO_Deinit();
  RNWK_Deinit();
  RMAC_Deinit();
  RPHY_Deinit();
  RMSG_Deinit();
  RADIO_Deinit();
  /*lint -restore */
}

#endif /* McuRNET_CONFIG_IS_ENABLED */

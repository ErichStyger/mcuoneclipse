/**
 * \file
 * \brief This main init module for the stack.
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module is used to simplify stack initialization.
 */

#include "RNetConf.h"
#include "RStack.h"
#include "Radio.h"
#include "RMSG.h"
#include "RPHY.h"
#include "RMAC.h"
#include "RNWK.h"
%if defined(RStdioEnabled) & %RStdioEnabled='yes'
#include "RStdIO.h"
%endif
#include "RApp.h"

void RSTACK_Init(void) {
  RADIO_Init();
  RMSG_Init();
  RPHY_Init();
  RMAC_Init();
  RNWK_Init();
%if defined(RStdioEnabled) & %RStdioEnabled='yes'
  RSTDIO_Init();
%endif
  RAPP_Init();
}

void RSTACK_Deinit(void) {
  RAPP_Deinit();
%if defined(RStdioEnabled) & %RStdioEnabled='yes'
  RSTDIO_Deinit();
%endif
  RNWK_Deinit();
  RMAC_Deinit();
  RPHY_Deinit();
  RMSG_Deinit();
  RADIO_Deinit();
}

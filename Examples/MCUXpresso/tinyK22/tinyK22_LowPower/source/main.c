#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK22F51212.h"
#include "fsl_smc.h"
#include "fsl_rcm.h"
#include "fsl_pmc.h"
#include "application.h"

int main(void) {
  /* Init board hardware. */

  /* Power related. */
  SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeAll);
  if (kRCM_SourceWakeup & RCM_GetPreviousResetSources(RCM)) { /* Wakeup from VLLS. */
    PMC_ClearPeriphIOIsolationFlag(PMC);
    NVIC_ClearPendingIRQ(LLWU_IRQn);
  }

  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();

  APP_Run(); /* run application */
  return 0;
}

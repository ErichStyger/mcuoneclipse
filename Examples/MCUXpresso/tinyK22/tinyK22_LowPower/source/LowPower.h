/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LOWPOWER_H_
#define LOWPOWER_H_

#include <stdbool.h>
#include "fsl_smc.h"

/* Power mode definition used in application. */
typedef enum _app_power_mode {
    kAPP_PowerModeRun,   /* Normal RUN mode */
    kAPP_PowerModeWait,  /* WAIT mode. */
    kAPP_PowerModeStop,  /* STOP mode. */
    kAPP_PowerModeVlpr,  /* VLPR mode. */
    kAPP_PowerModeVlpw,  /* VLPW mode. */
    kAPP_PowerModeVlps,  /* VLPS mode. */
    kAPP_PowerModeLls,   /* LLS mode. */
    kAPP_PowerModeVlls0, /* VLLS0 mode. */
    kAPP_PowerModeVlls1, /* VLLS1 mode. */
    kAPP_PowerModeVlls2, /* VLLS2 mode. */
    kAPP_PowerModeVlls3, /* VLLS3 mode. */
    kAPP_PowerModeHsrun, /* HighSpeed RUN mode */
} app_power_mode_t;

typedef enum _app_wakeup_source {
    kAPP_WakeupSourceLptmr, /*!< Wakeup by LPTMR.        */
    kAPP_WakeupSourcePin    /*!< Wakeup by external pin. */
} app_wakeup_source_t;

/* check if switching to a power mode is possible */
bool LP_CheckPowerMode(smc_power_state_t curPowerState, app_power_mode_t targetPowerMode);

/* set of different low power modes: */
#define LP_MODE_RUN    (0)  /* run mode, actually no low power mode. */
#define LP_MODE_WAIT   (1)  /* wait mode, wfi, disables only CPU clock, wake-up is any interrupt. */
#define LP_MODE_STOP   (2)  /* stop mode, lowest power mode that retains all registers while maintaining LVD detection, wakeup by interrupt or reset.  */
#define LP_MODE_VLPR   (3)  /* VLPR mode, NYI */

/* selected low power mode: */
#if 0
  #define LP_MODE LP_MODE_RUN /* normal run mode */
#elif 0
  #define LP_MODE LP_MODE_WAIT /* using wait instruction: wait for interrupt */
#elif 1
  #define LP_MODE LP_MODE_STOP /* using stop mode */
#else /* NYI! */
  #define LP_MODE LP_MODE_VLPR /* using very-low-power mode */
#endif

smc_power_state_t LP_GetCurrPowerMode(void);

void LP_EnterLowPower(app_power_mode_t targetPowerMode);

void LP_StartLPTMR(uint32_t ms);

void LP_Init(void);

#endif /* LOWPOWER_H_ */

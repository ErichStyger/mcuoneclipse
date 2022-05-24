/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "LowPower.h"
#include "McuLED.h"
#include "leds.h"
#include "fsl_pit.h"
#include "fsl_smc.h"
#include "fsl_lptmr.h"
#include "fsl_port.h"
#include "fsl_llwu.h"

static smc_power_state_t LP_curPowerState;
static uint8_t s_wakeupTimeout;            /* Wakeup timeout. (Unit: Second) */
static app_wakeup_source_t s_wakeupSource; /* Wakeup source.                 */

#define APP_WAKEUP_BUTTON_GPIO        GPIOC
#define APP_WAKEUP_BUTTON_PORT        PORTC
#define APP_WAKEUP_BUTTON_GPIO_PIN    1
#define APP_WAKEUP_BUTTON_IRQ         PORTC_IRQn
#define APP_WAKEUP_BUTTON_IRQ_HANDLER PORTC_IRQHandler
#define APP_WAKEUP_BUTTON_IRQ_TYPE    kPORT_InterruptFallingEdge

#define LLWU_LPTMR_IDX       0U /* LLWU_M0IF */
#define LLWU_WAKEUP_PIN_IDX  6U /* LLWU_P6 */
#define LLWU_WAKEUP_PIN_TYPE kLLWU_ExternalPinFallingEdge

static void LP_SetClockVlpr(void) {
  const sim_clock_config_t simConfig = {
      .pllFllSel = 3U,          /* PLLFLLSEL select IRC48MCLK. */
      .er32kSrc  = 2U,          /* ERCLK32K selection, use RTC. */
      .clkdiv1   = 0x00040000U, /* SIM_CLKDIV1. */
  };

  CLOCK_SetSimSafeDivs();
  CLOCK_SetInternalRefClkConfig(kMCG_IrclkEnable, kMCG_IrcFast, 0U);

  /* MCG works in PEE mode now, will switch to BLPI mode. */

  CLOCK_ExternalModeToFbeModeQuick();                     /* Enter FBE. */
  CLOCK_SetFbiMode(kMCG_Dmx32Default, kMCG_DrsLow, NULL); /* Enter FBI. */
  CLOCK_SetLowPowerEnable(true);                          /* Enter BLPI. */

  CLOCK_SetSimConfig(&simConfig);
}

static void LP_SetClockRunFromVlpr(void) {
  const sim_clock_config_t simConfig = {
      .pllFllSel = 1U,          /* PLLFLLSEL select PLL. */
      .er32kSrc  = 2U,          /* ERCLK32K selection, use RTC. */
      .clkdiv1   = 0x01230000U, /* SIM_CLKDIV1. */
  };

  const mcg_pll_config_t pll0Config = {
      .enableMode = 0U,
      .prdiv      = 0x3U,
      .vdiv       = 0x10U,
  };

  CLOCK_SetSimSafeDivs();

  /* Currently in BLPI mode, will switch to PEE mode. */
  /* Enter FBI. */
  CLOCK_SetLowPowerEnable(false);
  /* Enter FBE. */
  CLOCK_SetFbeMode(3U, kMCG_Dmx32Default, kMCG_DrsLow, NULL);
  /* Enter PBE. */
  CLOCK_SetPbeMode(kMCG_PllClkSelPll0, &pll0Config);
  /* Enter PEE. */
  CLOCK_SetPeeMode();

  CLOCK_SetSimConfig(&simConfig);
}

static void LP_SetClockHsrun(void) {
  const sim_clock_config_t simConfig = {
      .pllFllSel = 1U,          /* PLLFLLSEL select PLL. */
      .er32kSrc  = 2U,          /* ERCLK32K selection, use RTC. */
      .clkdiv1   = 0x01340000U, /* SIM_CLKDIV1. */
  };

  const mcg_pll_config_t pll0Config = {
      .enableMode = 0U,
      .prdiv      = 0x1U,
      .vdiv       = 0x6U,
  };

  CLOCK_SetPbeMode(kMCG_PllClkSelPll0, &pll0Config);
  CLOCK_SetPeeMode();

  CLOCK_SetSimConfig(&simConfig);
}

static void LP_SetClockRunFromHsrun(void) {
  const sim_clock_config_t simConfig = {
      .pllFllSel = 1U,          /* PLLFLLSEL select PLL. */
      .er32kSrc  = 2U,          /* ERCLK32K selection, use RTC. */
      .clkdiv1   = 0x01230000U, /* SIM_CLKDIV1. */
  };

  const mcg_pll_config_t pll0Config = {
      .enableMode = 0U,
      .prdiv      = 0x3U,
      .vdiv       = 0x10U,
  };

  CLOCK_SetPbeMode(kMCG_PllClkSelPll0, &pll0Config);
  CLOCK_SetPeeMode();

  CLOCK_SetSimConfig(&simConfig);
}

/*
 * Check whether could switch to target power mode from current mode.
 * Return true if could switch, return false if could not switch.
 */
bool LP_CheckPowerMode(smc_power_state_t curPowerState, app_power_mode_t targetPowerMode) {
  bool modeValid = true;

  /*
   * Check whether the mode change is allowed.
   * 1. If current mode is HSRUN mode, the target mode must be RUN mode.
   * 2. If current mode is RUN mode, the target mode must not be VLPW mode.
   * 3. If current mode is VLPR mode, the target mode must not be HSRUN/WAIT/STOP mode.
   * 4. If already in the target mode.
   */
  switch (curPowerState) {
    case kSMC_PowerStateHsrun:
        if (kAPP_PowerModeRun != targetPowerMode) {
          //PRINTF("Current mode is HSRUN, please choose RUN mode as the target mode.\r\n");
          modeValid = false;
        }
        break;

    case kSMC_PowerStateRun:
        if (kAPP_PowerModeVlpw == targetPowerMode) {
          //PRINTF("Could not enter VLPW mode from RUN mode.\r\n");
          modeValid = false;
        }
        break;

    case kSMC_PowerStateVlpr:
        if ((kAPP_PowerModeWait == targetPowerMode) || (kAPP_PowerModeHsrun == targetPowerMode) ||
          (kAPP_PowerModeStop == targetPowerMode)) {
          //PRINTF("Could not enter HSRUN/STOP/WAIT modes from VLPR mode.\r\n");
          modeValid = false;
        }
        break;
    default:
        //PRINTF("Wrong power state.\r\n");
        modeValid = false;
        break;
  }

  if (!modeValid) {
      return false;
  }

  /* Don't need to change power mode if current mode is already the target mode. */
  if (((kAPP_PowerModeRun == targetPowerMode) && (kSMC_PowerStateRun == curPowerState)) ||
      ((kAPP_PowerModeHsrun == targetPowerMode) && (kSMC_PowerStateHsrun == curPowerState)) ||
      ((kAPP_PowerModeVlpr == targetPowerMode) && (kSMC_PowerStateVlpr == curPowerState)))
  {
      //PRINTF("Already in the target power mode.\r\n");
      return false;
  }
  return true;
}

/*
 * Power mode switch.
 */
void LP_PowerModeSwitch(smc_power_state_t curPowerState, app_power_mode_t targetPowerMode) {
  smc_power_mode_vlls_config_t vlls_config;
  vlls_config.enablePorDetectInVlls0 = true;
  smc_power_mode_lls_config_t lls_config;
  lls_config.subMode = kSMC_StopSub3;

  switch (targetPowerMode) {
    case kAPP_PowerModeVlpr:
        LP_SetClockVlpr();
        SMC_SetPowerModeVlpr(SMC);
        while (kSMC_PowerStateVlpr != SMC_GetPowerModeState(SMC))
        {
        }
        break;

    case kAPP_PowerModeRun:
        /* If enter RUN from HSRUN, first change clock. */
        if (kSMC_PowerStateHsrun == curPowerState) {
            LP_SetClockRunFromHsrun();
        }

        /* Power mode change. */
        SMC_SetPowerModeRun(SMC);
        while (kSMC_PowerStateRun != SMC_GetPowerModeState(SMC))
        {
        }

        /* If enter RUN from VLPR, change clock after the power mode change. */
        if (kSMC_PowerStateVlpr == curPowerState)
        {
            LP_SetClockRunFromVlpr();
        }
        break;

    case kAPP_PowerModeHsrun:
        SMC_SetPowerModeHsrun(SMC);
        while (kSMC_PowerStateHsrun != SMC_GetPowerModeState(SMC))
        {
        }

        LP_SetClockHsrun(); /* Change clock setting after power mode change. */
        break;

    case kAPP_PowerModeWait:
        SMC_PreEnterWaitModes();
        SMC_SetPowerModeWait(SMC);
        SMC_PostExitWaitModes();
        break;

    case kAPP_PowerModeStop:
        SMC_PreEnterStopModes();
        SMC_SetPowerModeStop(SMC, kSMC_PartialStop);
        SMC_PostExitStopModes();
        break;

    case kAPP_PowerModeVlpw:
        SMC_PreEnterWaitModes();
        SMC_SetPowerModeVlpw(SMC);
        SMC_PostExitWaitModes();
        break;

    case kAPP_PowerModeVlps:
        SMC_PreEnterStopModes();
        SMC_SetPowerModeVlps(SMC);
        SMC_PostExitStopModes();
        break;

    case kAPP_PowerModeLls:
        SMC_PreEnterStopModes();
        SMC_SetPowerModeLls(SMC, &lls_config);
        SMC_PostExitStopModes();
        break;

    case kAPP_PowerModeVlls0:
        vlls_config.subMode = kSMC_StopSub0;
        SMC_PreEnterStopModes();
        SMC_SetPowerModeVlls(SMC, &vlls_config);
        SMC_PostExitStopModes();
        break;

    case kAPP_PowerModeVlls1:
        vlls_config.subMode = kSMC_StopSub1;
        SMC_PreEnterStopModes();
        SMC_SetPowerModeVlls(SMC, &vlls_config);
        SMC_PostExitStopModes();
        break;

    case kAPP_PowerModeVlls2:
        vlls_config.subMode = kSMC_StopSub2;
        SMC_PreEnterStopModes();
        SMC_SetPowerModeVlls(SMC, &vlls_config);
        SMC_PostExitStopModes();
        break;

    case kAPP_PowerModeVlls3:
        vlls_config.subMode = kSMC_StopSub3;
        SMC_PreEnterStopModes();
        SMC_SetPowerModeVlls(SMC, &vlls_config);
        SMC_PostExitStopModes();
        break;

    default:
        //PRINTF("Wrong value");
        break;
  }
}

void LP_PowerPreSwitchHook(smc_power_state_t originPowerState, app_power_mode_t targetMode) {
#if 0
  /* Wait for debug console output finished. */
  while (!(kUART_TransmissionCompleteFlag & UART_GetStatusFlags((UART_Type *)BOARD_DEBUG_UART_BASEADDR)))
  {
  }
  DbgConsole_Deinit();
#endif
  if ((kAPP_PowerModeRun != targetMode) && (kAPP_PowerModeHsrun != targetMode) && (kAPP_PowerModeVlpr != targetMode)) {
    /*
     * Set pin for current leakage.
     * Debug console RX pin: Set to pinmux to disable.
     * Debug console TX pin: Don't need to change.
     */
   // PORT_SetPinMux(DEBUG_CONSOLE_RX_PORT, DEBUG_CONSOLE_RX_PIN, kPORT_PinDisabledOrAnalog);
  }
}

void LP_PowerPostSwitchHook(smc_power_state_t originPowerState, app_power_mode_t targetMode) {
  smc_power_state_t powerState = SMC_GetPowerModeState(SMC);

  /*
   * For some other platforms, if enter LLS mode from VLPR mode, when wake-up, the
   * power mode is VLPR. But for some platforms, if enter LLS mode from VLPR mode,
   * when wakeup, the power mode is RUN. In this case, the clock setting is still
   * VLPR mode setting, so change to RUN mode setting here.
   */
  if ((kSMC_PowerStateVlpr == originPowerState) && (kSMC_PowerStateRun == powerState)) {
    LP_SetClockRunFromVlpr();
  }

  if ((kAPP_PowerModeRun != targetMode) && (kAPP_PowerModeHsrun != targetMode) && (kAPP_PowerModeVlpr != targetMode)) {
    /*
     * Debug console RX pin is set to disable for current leakage, need to re-configure pinmux.
     * Debug console TX pin: Don't need to change.
     */
    //PORT_SetPinMux(DEBUG_CONSOLE_RX_PORT, DEBUG_CONSOLE_RX_PIN, DEBUG_CONSOLE_RX_PINMUX);
  }

  /*
   * If enter stop modes when MCG in PEE mode, then after wake-up, the MCG is in PBE mode,
   * need to enter PEE mode manually.
   */
  if ((kAPP_PowerModeRun != targetMode) && (kAPP_PowerModeWait != targetMode) && (kAPP_PowerModeVlpw != targetMode) &&
      (kAPP_PowerModeHsrun != targetMode) && (kAPP_PowerModeVlpr != targetMode))
  {
    if (kSMC_PowerStateRun == originPowerState) {
        /* Wait for PLL lock. */
        while (!(kMCG_Pll0LockFlag & CLOCK_GetStatusFlags()))
        {
        }
        CLOCK_SetPeeMode();
    }
  }
  /* Set debug console clock source. */
  //APP_InitDebugConsole();
}

/* Get wake-up source by user input. */
static app_wakeup_source_t LP_GetWakeupSource(void) {
#if 0
  uint8_t ch;

    while (1)
    {
        PRINTF("Select the wake up source:\r\n");
        PRINTF("Press T for LPTMR - Low Power Timer\r\n");
        PRINTF("Press S for switch/button %s. \r\n", APP_WAKEUP_BUTTON_NAME);

        PRINTF("\r\nWaiting for key press..\r\n\r\n");

        ch = GETCHAR();

        if ((ch >= 'a') && (ch <= 'z'))
        {
            ch -= 'a' - 'A';
        }

        if (ch == 'T')
        {
            return kAPP_WakeupSourceLptmr;
        }
        else if (ch == 'S')
        {
            return kAPP_WakeupSourcePin;
        }
        else
        {
            PRINTF("Wrong value!\r\n");
        }
    }
#else
  return kAPP_WakeupSourceLptmr;
#endif
}

void LP_StartLPTMR(uint32_t ms) {
  lptmr_config_t lptmrConfig;

  LPTMR_GetDefaultConfig(&lptmrConfig);
  LPTMR_Init(LPTMR0, &lptmrConfig);
  LPTMR_SetTimerPeriod(LPTMR0, USEC_TO_COUNT(ms*1000, CLOCK_GetFreq(kCLOCK_LpoClk)));
  LPTMR_EnableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);
  EnableIRQ(LPTMR0_IRQn);
  LPTMR_StartTimer(LPTMR0);
}

void LP_SetWakeupConfig(app_power_mode_t targetMode) {
  /* Set LPTMR timeout value. */
  if (kAPP_WakeupSourceLptmr == s_wakeupSource)
  {
      LPTMR_SetTimerPeriod(LPTMR0, (LPO_CLK_FREQ * s_wakeupTimeout) - 1U);
      LPTMR_StartTimer(LPTMR0);
  }

  /* Set the wakeup module. */
  if (kAPP_WakeupSourceLptmr == s_wakeupSource)
  {
      LPTMR_EnableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);
  }
  else
  {
      PORT_SetPinInterruptConfig(APP_WAKEUP_BUTTON_PORT, APP_WAKEUP_BUTTON_GPIO_PIN, APP_WAKEUP_BUTTON_IRQ_TYPE);
  }

  /* If targetMode is VLLS/LLS, setup LLWU. */
  if ((kAPP_PowerModeWait != targetMode) && (kAPP_PowerModeVlpw != targetMode) &&
      (kAPP_PowerModeVlps != targetMode) && (kAPP_PowerModeStop != targetMode))
  {
      if (kAPP_WakeupSourceLptmr == s_wakeupSource)
      {
          LLWU_EnableInternalModuleInterruptWakup(LLWU, LLWU_LPTMR_IDX, true);
      }
      else
      {
          LLWU_SetExternalWakeupPinMode(LLWU, LLWU_WAKEUP_PIN_IDX, LLWU_WAKEUP_PIN_TYPE);
      }
      NVIC_EnableIRQ(LLWU_IRQn);
  }
}

static uint8_t LP_GetWakeupTimeout(void) {
  return 1; /* seconds */
}

/* Get wake-up timeout and wake-up source. */
void LP_GetWakeupConfig(app_power_mode_t targetMode) {
    /* Get wakeup source by user input. */
    if (targetMode == kAPP_PowerModeVlls0) {
        /* In VLLS0 mode, the LPO is disabled, LPTMR could not work. */
   //     PRINTF("Not support LPTMR wakeup because LPO is disabled in VLLS0 mode.\r\n");
        s_wakeupSource = kAPP_WakeupSourcePin;
    } else {
        /* Get wakeup source by user input. */
        s_wakeupSource = LP_GetWakeupSource();
    }
    if (kAPP_WakeupSourceLptmr == s_wakeupSource) {
        /* Wakeup source is LPTMR, user should input wakeup timeout value. */
        s_wakeupTimeout = LP_GetWakeupTimeout();
     //   PRINTF("Will wakeup in %d seconds.\r\n", s_wakeupTimeout);
    } else {
       // PRINTF("Press %s to wake up.\r\n", APP_WAKEUP_BUTTON_NAME);
    }
}

/*!
 * @brief LLWU interrupt handler.
 */
void LLWU_IRQHandler(void) {
    /* If wakeup by LPTMR. */
    if (LLWU_GetInternalWakeupModuleFlag(LLWU, LLWU_LPTMR_IDX))
    {
        /* Disable lptmr as a wakeup source, so that lptmr's IRQ Handler will be executed when reset from VLLSx mode. */
        LLWU_EnableInternalModuleInterruptWakup(LLWU, LLWU_LPTMR_IDX, false);
    }
    /* If wakeup by external pin. */
    if (LLWU_GetExternalWakeupPinFlag(LLWU, LLWU_WAKEUP_PIN_IDX))
    {
        /* Disable WAKEUP pin as a wakeup source, so that WAKEUP pin's IRQ Handler will be executed when reset from
         * VLLSx mode. */
        LLWU_ClearExternalWakeupPinFlag(LLWU, LLWU_WAKEUP_PIN_IDX);
    }
    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
    exception return operation might vector to incorrect interrupt */
    __DSB();
    __ISB();
}

void LPTMR0_IRQHandler(void) {
#if 0// 1 || LP_MODE==LP_MODE_RUN
  LPTMR_ClearStatusFlags(LPTMR0, kLPTMR_TimerCompareFlag);
  //McuLED_Toggle(blueLED);
#else
  if (kLPTMR_TimerInterruptEnable & LPTMR_GetEnabledInterrupts(LPTMR0)) {
    McuLED_Toggle(blueLED);
    LPTMR_DisableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);
    LPTMR_ClearStatusFlags(LPTMR0, kLPTMR_TimerCompareFlag);
    LPTMR_StopTimer(LPTMR0);
  }
#endif
  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
  exception return operation might vector to incorrect interrupt */
  __DSB();
  __ISB();
}

void PORTC_IRQHandler(void) {
  if ((1U << APP_WAKEUP_BUTTON_GPIO_PIN) & PORT_GetPinsInterruptFlags(APP_WAKEUP_BUTTON_PORT)) {
      /* Disable interrupt. */
      PORT_SetPinInterruptConfig(APP_WAKEUP_BUTTON_PORT, APP_WAKEUP_BUTTON_GPIO_PIN, kPORT_InterruptOrDMADisabled);
      PORT_ClearPinsInterruptFlags(APP_WAKEUP_BUTTON_PORT, (1U << APP_WAKEUP_BUTTON_GPIO_PIN));
  }
  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
  exception return operation might vector to incorrect interrupt */
  __DSB();
  __ISB();
}

#if LP_MODE==LP_MODE_WAIT || LP_MODE==LP_MODE_STOP
#define PIT_BASEADDR       PIT
#define PIT_SOURCE_CLOCK   CLOCK_GetFreq(kCLOCK_BusClk)
#define PIT_CHANNEL        kPIT_Chnl_0
#define PIT_HANDLER        PIT0_IRQHandler
#define PIT_IRQ_ID         PIT0_IRQn

void PIT_HANDLER(void) {
  PIT_ClearStatusFlags(PIT_BASEADDR, PIT_CHANNEL, kPIT_TimerFlag);
  __DSB();
}

static void ConfigurePIT(void) {
  pit_config_t config;

  PIT_GetDefaultConfig(&config);
  config.enableRunInDebug = false;
  PIT_Init(PIT_BASEADDR, &config);
  PIT_SetTimerPeriod(PIT_BASEADDR, PIT_CHANNEL, MSEC_TO_COUNT(1*1000U, PIT_SOURCE_CLOCK));
  PIT_EnableInterrupts(PIT_BASEADDR, PIT_CHANNEL, kPIT_TimerInterruptEnable);
  NVIC_SetPriority(PIT_IRQ_ID, 0);
  EnableIRQ(PIT_IRQ_ID);
  PIT_StartTimer(PIT_BASEADDR, PIT_CHANNEL);
}
#endif

void LP_EnterLowPower(app_power_mode_t targetPowerMode) {
  bool needSetWakeup;

  if (!LP_CheckPowerMode(LP_curPowerState, targetPowerMode)) {
    return;
  }
  /* If target mode is RUN/VLPR/HSRUN, don't need to set wakeup source. */
  if ((kAPP_PowerModeRun == targetPowerMode) || (kAPP_PowerModeHsrun == targetPowerMode) ||
      (kAPP_PowerModeVlpr == targetPowerMode))
  {
    needSetWakeup = false;
  } else {
    needSetWakeup = true;
  }
  if (needSetWakeup) {
    LP_GetWakeupConfig(targetPowerMode);
  }
  LP_PowerPreSwitchHook(LP_curPowerState, targetPowerMode);
  if (needSetWakeup) {
    LP_SetWakeupConfig(targetPowerMode);
  }
  LP_PowerModeSwitch(LP_curPowerState, targetPowerMode);
  LP_PowerPostSwitchHook(LP_curPowerState, targetPowerMode);

#if 0
#if LP_MODE==LP_MODE_RUN
  /* not entering any low power mode */
#elif LP_MODE==LP_MODE_WAIT
  SMC_SetPowerModeWait(SMC);
   /* next interrupt will wake me up */
#elif LP_MODE==LP_MODE_STOP
  SMC_SetPowerModeStop(SMC, kSMC_PartialStop2); /* Partial Stop with system clock disabled and bus clock enabled */
  /* next interrupt will wake me up */
#endif
#endif
}

smc_power_state_t LP_GetCurrPowerMode(void) {
  return LP_curPowerState;
}

static void LP_InitLPTMR(void) {
  static  const lptmr_config_t LPTMR_config = {.timerMode            = kLPTMR_TimerModeTimeCounter,
      .pinSelect            = kLPTMR_PinSelectInput_0,
      .pinPolarity          = kLPTMR_PinPolarityActiveHigh,
      .enableFreeRunning    = false,
      .bypassPrescaler      = true,
      .prescalerClockSource = kLPTMR_PrescalerClock_1,
      .value                = kLPTMR_Prescale_Glitch_0};

  /* Initialize the LPTMR */
  LPTMR_Init(LPTMR0, &LPTMR_config);
  /* Set LPTMR period to 1000000us */
  LPTMR_SetTimerPeriod(LPTMR0, 1000);
  /* Configure timer interrupt */
  LPTMR_EnableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);
  /* Enable interrupt LPTMR0_IRQn request in the NVIC */
  EnableIRQ(LPTMR0_IRQn);
}

void LP_Init(void) {
  LP_curPowerState = SMC_GetPowerModeState(SMC);
  /* initialize LLWU */
  EnableIRQ(LLWU_IRQn);

  LP_InitLPTMR();

#if LP_MODE==LP_MODE_RUN
  /* not entering any low power mode */
#elif LP_MODE==LP_MODE_WAIT
  //ConfigurePIT(); /* configure timer used as wake-up source */
#elif LP_MODE==LP_MODE_STOP
  ConfigurePIT(); /* configure timer used as wake-up source */
#endif
}

/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_LOW_POWER
#include "LowPower.h"

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"
#include "clock_config.h"
#include "fsl_common.h"
#include "fsl_power.h"
#include "fsl_usart.h"
#include "fsl_syscon.h"
#include "fsl_wkt.h"
#include "fsl_iocon.h"
#include <stdbool.h>
#include "fsl_pint.h"
#include "fsl_swm.h"
#include "fsl_gpio.h"
#include "leds.h"
#include "McuWait.h"
#include "McuRTOS.h"

/* PIO0_1: lowest pin on LPC804 header */
#define BOARD_S1_GPIO_PORT  0U
#define BOARD_S1_GPIO_PIN   1U

#define BOARD_LED_GREEN_GPIO_PIN   LEDS_LED_GREEN_PIN
#define BOARD_LED_RED_GPIO_PIN     LEDS_LED_RED_PIN

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LP_ACTIVE_IN_DEEPSLEEP               (kPDSLEEPCFG_DeepSleepLPOscActive)
#define LP_USER_WAKEUP_KEY_GPIO              GPIO
#define LP_USER_WAKEUP_KEY_PORT              BOARD_S1_GPIO_PORT
#define LP_USER_WAKEUP_KEY_PIN               BOARD_S1_GPIO_PIN
#define LP_SYSCON_PIN_INT_SEL                (4U)
#define LP_SYSCON_STARTER0_MASK              (1U)
#define LP_SYSCON_STARTER1_MASK              (1U << 15U)
#define LP_WKT_TIMEOUT_VALUE                 ((250000U * 4U * 1U)) /* us */ /* 1000 ms */
#define LP_PINT_PIN_INT0_SRC                 kSYSCON_GpioPort0Pin13ToPintsel

/* user selection of different wakeup sources for modes: */
#define LP_SLEEP_WAKEUP_SOURCE               "\t1. S1, wakeup key\r\n\t2. Wkt timer\r\n\t3. S3, reset key\r\n"
#define LP_DEEP_SLEEP_WAKEUP_SOURCE          "\t1. S1, wakeup key\r\n\t2. Wkt timer\r\n\t3. S3, reset key\r\n"
#define LP_POWER_DOWN_WAKEUP_SOURCE          "\t1. S1, wakeup key\r\n\t2. Wkt timer\r\n\t3. S3, reset key\r\n"
#define LP_DEEP_POWERDOWN_WAKEUP_SOURCE      "\t1. S1, wakeup key\r\n"

#define LP_DEEP_POWERDOWN_RESET_ENABLE       (1U)
#define POWER_DPD_ENABLE_WAKEUP_PIN            POWER_DeepPowerDownWakeupSourceSelect(KPmu_Dpd_En_Pio0_13);
#define POWER_DPD_ENABLE_RESET_PIN

/* enable/disable support for different wake-up */
#define LP_WAKEUP_WITH_WKT   (1 && !McuLib_CONFIG_SDK_USE_FREERTOS)  /* if wakeup with WKT timer is enabled */
#define LP_WAKEUP_WITH_KEY   (0)  /* if wakeup with key or pin is enabled */
#define LP_WAKEUP_WITH_RESET (0)  /* if wakeup with reset is enabled */

#if LP_WAKEUP_WITH_KEY
/*
 * Callback function when wake-up key is pressed.
 */
static void pint_intr_callback(pint_pin_int_t pintr, uint32_t pmatch_status) {
    /* do nothing here */
}
#endif

#if LP_WAKEUP_WITH_WKT
void LP_InitWkt(void) {
   wkt_config_t wktConfig;

    POWER_EnableLPO(true);
    /*POWER_EnableLPOInDpdMode(true);*/

    wktConfig.clockSource = kWKT_LowPowerClockSource;
    WKT_Init(WKT, &wktConfig);  /* Init wkt module */
    NVIC_ClearPendingIRQ(WKT_IRQn); /* Clear Pending Interrupt */
    EnableIRQ(WKT_IRQn); /* Enable at the NVIC */
}
#endif

#if LP_WAKEUP_WITH_RESET
static void LP_InitResetPin(void) {
    SWM_SetFixedPinSelect(SWM0, kSWM_RESETN, true);
}
#endif

#if 0
static void configurePins(void) {
  gpio_pin_config_t gpioPinConfigStruct;
  uint32_t modefunc;

  /* Set all pin inactive mode(disable pull up/pull down) */
  for (int i=0; i<30; i++) {
    modefunc = (IOCON->PIO[i] & (~IOCON_PIO_MODE_MASK)) | IOCON_PIO_MODE(0UL);
    IOCON_PinMuxSet(IOCON, (uint8_t)i, modefunc);
  }
  /* Set all pin output and high Voltage, except pin for led and wake-up pin */
  gpioPinConfigStruct.pinDirection = kGPIO_DigitalOutput;
  gpioPinConfigStruct.outputLogic  = 0UL;
  for (int i=0; i<=30; i++) {
    if (i != BOARD_LED_RED_GPIO_PIN && i != BOARD_LED_GREEN_GPIO_PIN /* && i != BOARD_S1_GPIO_PIN */) {
      GPIO_PinInit(GPIO, 0UL, i, &gpioPinConfigStruct);
    }
  }
}
#endif

#if LP_WAKEUP_WITH_KEY
/*
 * Setup a GPIO input pin as wakeup source.
 */
static void LP_InitWakeupPin(void) {
    uint32_t i;
    uint32_t modefunc;

    gpio_pin_config_t gpioPinConfigStruct;

    /* Set SW pin as GPIO input. */
    gpioPinConfigStruct.pinDirection = kGPIO_DigitalInput;
    GPIO_PinInit(LP_USER_WAKEUP_KEY_GPIO, LP_USER_WAKEUP_KEY_PORT, LP_USER_WAKEUP_KEY_PIN, &gpioPinConfigStruct);

    SYSCON_AttachSignal(SYSCON, kPINT_PinInt0, LP_PINT_PIN_INT0_SRC);

    /* Configure the interrupt for SW pin. */
    PINT_Init(PINT);
    PINT_PinInterruptConfig(PINT, kPINT_PinInt0, kPINT_PinIntEnableFallEdge, pint_intr_callback);
    PINT_EnableCallback(PINT); /* Enable callbacks for PINT */

    /* Set all pin inactive mode(disable pull up/pull down) */
    for (i = 0; i < 30; i++)
    {
        modefunc = (IOCON->PIO[i] & (~IOCON_PIO_MODE_MASK)) | IOCON_PIO_MODE(0UL);
        IOCON_PinMuxSet(IOCON, (uint8_t)i, modefunc);
    }
    /* Set all pin output and high Voltage, except pin for led and wakup pin */
    gpioPinConfigStruct.pinDirection = kGPIO_DigitalOutput;
    gpioPinConfigStruct.outputLogic  = 1UL;
    for (i = 0; i <= 30; i++) {
        if (i != BOARD_LED_RED_GPIO_PIN && i != BOARD_LED_GREEN_GPIO_PIN && i != BOARD_S1_GPIO_PIN)
        {
            GPIO_PinInit(GPIO, 0UL, i, &gpioPinConfigStruct);
        }
    }
}
#endif

static void LP_ConfigureWakeUpSource(void) {
#if McuLib_CONFIG_SDK_USE_FREERTOS && configSYSTICK_USE_LOW_POWER_TIMER && (LP_LOW_POWER_MODE==LP_MODE_DEEP_SLEEP || LP_LOW_POWER_MODE==LP_MODE_POWER_DOWN)
  EnableDeepSleepIRQ(WKT_IRQn);
#endif
  #if LP_WAKEUP_WITH_WKT
    /* Enable wakeup for wkt. */
    EnableDeepSleepIRQ(WKT_IRQn);
    #if LP_WAKEUP_WITH_KEY
    DisableDeepSleepIRQ(PIN_INT0_IRQn);
    #endif
    WKT_StartTimer(WKT, USEC_TO_COUNT(LP_WKT_TIMEOUT_VALUE, CLOCK_GetFreq(kCLOCK_LPOsc)));
  #elif LP_WAKEUP_WITH_KEY
    /* Enable wakeup for PinInt0. */
     EnableDeepSleepIRQ(PIN_INT0_IRQn);
     DisableDeepSleepIRQ(WKT_IRQn);
     if (targetPowerMode == kPmu_Deep_PowerDown) {
         POWER_DPD_ENABLE_WAKEUP_PIN
     }
  #elif LP_WAKEUP_WITH_RESET
     if (targetPowerMode == kPmu_Deep_PowerDown) {
          POWER_DPD_ENABLE_RESET_PIN
      }
  #endif
}

void LP_PreEnterLowPower(void) {
  LP_ConfigureWakeUpSource();

  /* switch main clock source to FRO18M */
  POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);
  POWER_DisablePD(kPDRUNCFG_PD_FRO);
  CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro);
  CLOCK_SetFroOscFreq(kCLOCK_FroOscOut18M);
  /*CLOCK_SetFroOutClkSrc(kCLOCK_FroSrcFroOsc);*/

  /*
   * system osc power down
   * application should decide if more part need to power down to achieve better power consumption
   */
  //CLOCK_DisableClock(kCLOCK_Iocon);
  //CLOCK_DisableClock(kCLOCK_Uart0);
}

void LP_RestoreAfterWakeup(void) {
  BOARD_InitBootClocks(); /* clock configurations restore */

  //CLOCK_EnableClock(kCLOCK_Iocon);
  //CLOCK_EnableClock(kCLOCK_Uart0);
#if LP_WAKEUP_WITH_WKT
  WKT_StopTimer(WKT);
#endif
}

#if LP_WAKEUP_WITH_WKT
void WKT_IRQHandler(void) {
    /* Clear interrupt flag */
    WKT_ClearStatusFlags(WKT, kWKT_AlarmFlag);
    WKT_StartTimer(WKT, USEC_TO_COUNT(LP_WKT_TIMEOUT_VALUE, CLOCK_GetFreq(kCLOCK_LPOsc))); /* WKT clocked by low power oscillator */
}
#endif

void LP_InitHardware(void) {
    /* Init wake up source */
#if LP_WAKEUP_WITH_KEY
    LP_InitWakeupPin();
#endif
#if LP_WAKEUP_WITH_RESET
    LP_InitResetPin();
#endif
#if LP_WAKEUP_WITH_WKT
    LP_InitWkt();
#endif

    /* Disable BOD reset, Disable BOD reset before de-powering BOD */
    SYSCON->BODCTRL  = (SYSCON->BODCTRL & (~SYSCON_BODCTRL_BODRSTENA_MASK)) | SYSCON_BODCTRL_BODRSTENA(0UL);
    SYSCON->PDRUNCFG = (SYSCON->PDRUNCFG & (~SYSCON_PDSLEEPCFG_BOD_PD_MASK)) | SYSCON_PDSLEEPCFG_BOD_PD(1UL);

    //configurePins(); /* caution: needs to be updated for board pins, as we have I2C pins */
    CLOCK_DisableClock(kCLOCK_Iocon);
}

void LP_EnterLowPower(void) {
#if LP_LOW_POWER_MODE==LP_MODE_SLEEP
  POWER_EnterSleep();
#elif LP_LOW_POWER_MODE==LP_MODE_DEEP_SLEEP
  POWER_EnterDeepSleep(LP_ACTIVE_IN_DEEPSLEEP);
#elif LP_LOW_POWER_MODE==LP_MODE_POWER_DOWN
  POWER_EnterPowerDown(LP_ACTIVE_IN_DEEPSLEEP);
#elif LP_LOW_POWER_MODE==LP_MODE_DEEP_POWER_DOWN
  POWER_EnterDeepPowerDownMode();
#endif
}

void LP_EnterLowPowerMode(void) {
  LP_PreEnterLowPower();
  LP_EnterLowPower(); /* waits here */
  LP_RestoreAfterWakeup();
}

#if configUSE_TICKLESS_IDLE && configSYSTICK_USE_LOW_POWER_TIMER
/* see https://www.freertos.org/low-power-tickless-rtos.html */

#if McuLib_CONFIG_SDK_USE_FREERTOS
static uint32_t ulGetExternalTime(void) {
  return WKT_GetCounterValue(WKT);
}

void LP_vApplicationSleep(unsigned int xExpectedIdleTime) {
  unsigned long ulLowPowerTimeBeforeSleep, ulLowPowerTimeAfterSleep;
  eSleepModeStatus eSleepStatus;
  #define TIMER_COUNTS_FOR_ONE_TICK   (configSYSTICK_LOW_POWER_TIMER_CLOCK_HZ/configTICK_RATE_HZ)
  #define TICK_INTERRUPT_HAS_FIRED()   (WKT_GetStatusFlags(LPTMR_BASE_PTR)==WKT_CTRL_ALARMFLAG_MASK)


  /* Read the current time from a time source that will remain operational
  while the microcontroller is in a low power state. */
  ulLowPowerTimeBeforeSleep = ulGetExternalTime();

  /* Stop the timer that is generating the tick interrupt. */
  //prvStopTickInterruptTimer();
  WKT_StopTimer(WKT);

  /* Enter a critical section that will not effect interrupts bringing the MCU
  out of sleep mode. */
  portENTER_CRITICAL();

  /* Ensure it is still ok to enter the sleep mode. */
  eSleepStatus = eTaskConfirmSleepModeStatus();
  if( eSleepStatus == eAbortSleep ) {
    /* A task has been moved out of the Blocked state since this macro was
    executed, or a context switch is being held pending.  Do not enter a
    sleep state.  Restart the tick and exit the critical section. */
    //prvStartTickInterruptTimer();
    WKT_StartTimer(WKT, ulLowPowerTimeBeforeSleep);
    portEXIT_CRITICAL();
  } else {
    if( eSleepStatus == eNoTasksWaitingTimeout ) {
      /* It is not necessary to configure an interrupt to bring the
      microcontroller out of its low power state at a fixed time in the
      future. */
      //prvSleep();
      LP_EnterLowPowerMode();
    } else  {
      /* Configure an interrupt to bring the microcontroller out of its low
      power state at the time the kernel next needs to execute.  The
      interrupt must be generated from a source that remains operational
      when the microcontroller is in a low power state. */
      //vSetWakeTimeInterrupt( xExpectedIdleTime );
      ulLowPowerTimeBeforeSleep = TIMER_COUNTS_FOR_ONE_TICK*xExpectedIdleTime;
      WKT_StartTimer(WKT, ulLowPowerTimeBeforeSleep);
      /* Enter the low power state. */
      //prvSleep();
      LP_EnterLowPowerMode();

      /* Determine how long the microcontroller was actually in a low power
      state for, which will be less than xExpectedIdleTime if the
      microcontroller was brought out of low power mode by an interrupt
      other than that configured by the vSetWakeTimeInterrupt() call.
      Note that the scheduler is suspended before
      portSUPPRESS_TICKS_AND_SLEEP() is called, and resumed when
      portSUPPRESS_TICKS_AND_SLEEP() returns.  Therefore no other tasks will
      execute until this function completes. */

      if (WKT_GetStatusFlags(WKT)!=0) { /* call returns WKT_CTRL_ALARMFLAG_MASK flag */
        /* WKT interrupt has fired */
        vTaskStepTick(xExpectedIdleTime); /* report the low power mode time spent */
      } else {
        /* other interrupt has woke us up: calculate time we have been in low power mode */
        unsigned long remainingTimerTicks;

        ulLowPowerTimeAfterSleep = ulGetExternalTime();
        remainingTimerTicks = ulLowPowerTimeBeforeSleep - ulLowPowerTimeAfterSleep;
        vTaskStepTick(remainingTimerTicks/TIMER_COUNTS_FOR_ONE_TICK);
      }
      /* Correct the kernels tick count to account for the time the
      microcontroller spent in its low power state. */
      //vTaskStepTick( ulLowPowerTimeAfterSleep - ulLowPowerTimeBeforeSleep );
    }

    /* Exit the critical section - it might be possible to do this immediately
    after the prvSleep() calls. */
    portEXIT_CRITICAL();

    /* Restart the timer that is generating the tick interrupt. */
    //prvStartTickInterruptTimer();
    WKT_StartTimer(WKT, TIMER_COUNTS_FOR_ONE_TICK);
  }
}
#endif /* McuLib_CONFIG_SDK_USE_FREERTOS */
#endif

/* test low power without RTOS */
int lp_loop(void) {
  __enable_irq(); /* NOTE: PRIMASK has to enable interrupts, otherwise WFI will not wait! */
  while (1) {
    LP_EnterLowPowerMode();

    //LEDS_On(LEDS_GREEN);
    McuWait_Waitms(10);
    LEDS_Off(LEDS_GREEN);
  }
}

static void safetyBelt(void) {
  /* delay for safety, to be able to re-take control with the debugger */
  for(int i=0;i<10;i++) {
    LEDS_Neg(LEDS_RED);
    McuWait_Waitms(1000);
  }
  LEDS_Off(LEDS_RED);
}

void LP_Init(void) {
  safetyBelt();
	LP_InitHardware();
#if 0 && !McuLib_CONFIG_SDK_USE_FREERTOS /* only possible without RTOS! */
  #if !LP_WAKEUP_WITH_WKT
    #error "a wake-up source needs to be enabled!"
  #elif McuLib_CONFIG_SDK_USE_FREERTOS && configSYSTICK_USE_LOW_POWER_TIMER
    #warning "WKT enabled in RTOS! Disable RTOS with McuLib_CONFIG_SDK_USE_FREERTOS"
  #endif
	lp_loop(); /* stays in it! */
#endif
}

#endif /* PL_CONFIG_USE_LOW_POWER */

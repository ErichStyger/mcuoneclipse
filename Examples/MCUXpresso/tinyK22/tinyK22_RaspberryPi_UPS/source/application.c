/*
 * application.c
 *      Author: Erich Styger
 */

/* own modules and standard library */
#include "McuArmTools.h"
#include "application.h" /* own interface */
#include <ctype.h> /* for isupper() */
#include "platform.h"

/* SDK */
#include "fsl_lpuart.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "pin_mux.h"
#include "board.h"

/* own modules */
#include "leds.h"
#include "initPins.h"
#include "gateway.h"
#include "shutdown.h"
#include "oled.h"
#include "navSwitch.h"
#include "McuRB.h"

/* McuLib */
#include "McuWait.h"
#include "McuArmTools.h"
#include "McuGenericI2C.h"
#include "McuGenericSWI2C.h"
#if PL_CONFIG_USE_LVGL
  #include "lv.h"
  #include "gui.h"
#endif

#include "McuRTOS.h"
#include "FreeRTOS.h"

#if PL_CONFIG_USE_UPS
  #include "ups.h"
#endif
#if PL_CONFIG_USE_SHT31
  #include "SHT31.h"
#endif

#define ENABLE_TIMER   (1)

#if ENABLE_TIMER
/* blinky timer */
#include "fsl_ftm.h"

/* The Flextimer instance/channel used for board */
#define BOARD_FTM_BASEADDR FTM0

/* Interrupt number and interrupt handler for the FTM instance used */
#define BOARD_FTM_IRQ_NUM FTM0_IRQn

/* Get source clock for FTM driver */
#define FTM_SOURCE_CLOCK (CLOCK_GetFreq(kCLOCK_BusClk)/4)

void FTM0_IRQHandler(void) { /* called every 1 ms */
  /* Clear interrupt flag.*/
  static uint32_t ms = 0;

  FTM_ClearStatusFlags(BOARD_FTM_BASEADDR, kFTM_TimeOverflowFlag);
  ms++;
  if (ms>=1000) {
    McuLED_Neg(hatBlueLED);
    ms = 0;
  }
  __DSB();
}

static void InitTimer(void) {
  ftm_config_t ftmInfo;

  FTM_GetDefaultConfig(&ftmInfo);
  /* Divide FTM clock by 4 */
  ftmInfo.prescale = kFTM_Prescale_Divide_4;

  /* Initialize FTM module */
  FTM_Init(BOARD_FTM_BASEADDR, &ftmInfo);
  /*
   * Set timer period.
   */
  FTM_SetTimerPeriod(BOARD_FTM_BASEADDR, USEC_TO_COUNT(1000U, FTM_SOURCE_CLOCK));

  FTM_EnableInterrupts(BOARD_FTM_BASEADDR, kFTM_TimeOverflowInterruptEnable);
  EnableIRQ(BOARD_FTM_IRQ_NUM);

  FTM_StartTimer(BOARD_FTM_BASEADDR, kFTM_SystemClock);
}
#endif /* ENABLE_TIMER */


#if 0
static bool isBtnPressed(void) {
  if (GPIO_PinRead(PINS_HATNAVDOWN_GPIO, PINS_HATNAVDOWN_PIN)==0) {
    return true;
  }
  if (GPIO_PinRead(PINS_HATNAVUP_GPIO, PINS_HATNAVUP_PIN)==0) {
    return true;
  }
  if (GPIO_PinRead(PINS_HATNAVLEFT_GPIO, PINS_HATNAVLEFT_PIN)==0) {
    return true;
  }
  if (GPIO_PinRead(PINS_HATNAVRIGHT_GPIO, PINS_HATNAVRIGHT_PIN)==0) {
    return true;
  }
#if 1 /* pulled down by raspy? */
  if (GPIO_PinRead(PINS_HATNAVPUSH_GPIO, PINS_HATNAVPUSH_PIN)==0) {
    return true;
  }
#endif
  return false;
}
#endif

void PORTB_IRQHandler(void) {
  /* Clear external interrupt flag. */
  uint32_t flags;

  flags = GPIO_PortGetInterruptFlags(GPIOB);
  if (flags&(1U<<PINS_HATNAVLEFT_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVLEFT_GPIO, 1U<<PINS_HATNAVLEFT_PIN);
    GPIO_PortToggle(PINS_HATLEDBLUE_GPIO, (1<<PINS_HATLEDBLUE_PIN));
  }
  if (flags&(1U<<PINS_HATNAVRIGHT_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVRIGHT_GPIO, 1U<<PINS_HATNAVRIGHT_PIN);
    GPIO_PortToggle(PINS_HATLEDRED_GPIO, (1<<PINS_HATLEDRED_PIN));
  }
  if (flags&(1U<<PINS_HATNAVUP_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVUP_GPIO, 1U<<PINS_HATNAVUP_PIN);
    GPIO_PortToggle(PINS_HATLEDGREEN_GPIO, (1<<PINS_HATLEDGREEN_PIN));
  }
  if (flags&(1U<<PINS_HATNAVDOWN_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVDOWN_GPIO, 1U<<PINS_HATNAVDOWN_PIN);
    GPIO_PortToggle(PINS_HATLEDYELLOW_GPIO, (1<<PINS_HATLEDYELLOW_PIN));
  }
  if (flags&(1U<<PINS_HATNAVPUSH_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVPUSH_GPIO, 1U<<PINS_HATNAVPUSH_PIN);
    GPIO_PortToggle(PINS_LEDBLUE_GPIO, (1<<PINS_LEDBLUE_PIN));
  }
  __DSB();
}

void doNavInterrupts(void) {
  /*
   * HAT V3:
   * up:    PTB0
   * down:  PTB1
   * left:  PTB3
   * right: PTB2
   * push:  PTB16
   */
  PORT_SetPinInterruptConfig(PINS_HATNAVUP_PORT, PINS_HATNAVUP_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVDOWN_PORT, PINS_HATNAVDOWN_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVLEFT_PORT, PINS_HATNAVLEFT_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVRIGHT_PORT, PINS_HATNAVRIGHT_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVPUSH_PORT, PINS_HATNAVPUSH_PIN, kPORT_InterruptFallingEdge);

  EnableIRQ(PORTB_IRQn);
  for(;;) {
    McuWait_Waitms(1000);
    GPIO_PortToggle(PINS_LEDBLUE_GPIO, (1<<PINS_LEDBLUE_PIN));
  }
}

static void MainTask(void *pv) {
#if PL_CONFIG_USE_GATEWAY && PL_CONFIG_USE_OLED && !PL_CONFIG_USE_LVGL
  uint32_t oldNofRx=-1, oldNofTx=-1, nofRx, nofTx;
#endif
#if PL_CONFIG_USE_UPS
  float voltage, prevVoltage = 0.0f, charge;
  bool isCharging = true;
  int chargeCounter = 0; /* counting up for charging, counting down for discharging */
#endif
  uint32_t currCycleCnt, lastCycleCnt, elapsedCycleCnt;

  lastCycleCnt = McuArmTools_GetCycleCounter();
  for(;;) { /* main loop */
    currCycleCnt = McuArmTools_GetCycleCounter();
    elapsedCycleCnt = (int32_t)currCycleCnt - (int32_t)lastCycleCnt; /* calculate delta (signed) */
    if (elapsedCycleCnt > McuWait_NofCyclesMs(1000, SystemCoreClock)) { /* every second */
      lastCycleCnt = currCycleCnt;
      McuLED_Neg(tinyLED);
  #if PL_CONFIG_USE_UPS
      if (UPS_GetCharge(&charge)==0 && UPS_GetVoltage(&voltage)==0) {
        if (prevVoltage==0.0f) { /* first check */
          prevVoltage = voltage;
        }
        if (voltage-prevVoltage>0.02f) {
          chargeCounter++;
        } else if (prevVoltage-voltage>0.02f) {
          chargeCounter--;
        }
        if (!isCharging && chargeCounter>=5) {
          isCharging = true;
          prevVoltage = voltage;
          chargeCounter = 5;
        } else if (isCharging && chargeCounter<=-5) {
          isCharging = false;
          prevVoltage = voltage;
          chargeCounter = -5;
        }
  #if PL_CONFIG_USE_OLED && !PL_CONFIG_USE_LVGL
        OLED_ShowUPS(voltage, charge, isCharging);
  #endif
  #if PL_CONFIG_USE_SHUTDOWN
        if (charge<15.0f && !isCharging) { /* low battery and not is charging => power down */
      #if PL_CONFIG_USE_OLED && !PL_CONFIG_USE_LVGL
          OLED_PrintShutdownMsg();
      #endif
          SHUTDOWN_RequestPowerOff();
        }
  #endif
      }
  #endif
  #if PL_CONFIG_USE_GATEWAY && PL_CONFIG_USE_OLED && !PL_CONFIG_USE_LVGL
      nofRx = GATEWAY_GetNofRx();
      nofTx = GATEWAY_GetNofTx();
      if (nofRx!=oldNofRx || nofTx!=oldNofTx) {
        OLED_ShowRxTx(nofRx, nofTx);
        oldNofRx = nofRx;
        oldNofTx = nofTx;
      }
  #endif
  #if PL_CONFIG_USE_SHT31 && PL_CONFIG_USE_OLED && !PL_CONFIG_USE_LVGL
      {
        float temp, hum;

        if (SHT31_ReadTempHum(&temp, &hum)==ERR_OK) {
          OLED_ShowTemperatureHumidity(temp, hum);
        }
      }
  #endif
    } /* for */
#if PL_CONFIG_USE_SHUTDOWN
    if (SHUTDOWN_UserPowerOffRequested()) {
  #if PL_CONFIG_USE_OLED && !PL_CONFIG_USE_LVGL
      OLED_PrintShutdownMsg();
  #endif
      SHUTDOWN_RequestPowerOff();
    }
#endif
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void APP_Run(void) {
  PL_Init();
#if PL_CONFIG_USE_SHUTDOWN && PL_CONFIG_USE_OLED && !PL_CONFIG_USE_LVGL
  OLED_PrintShutdownHelp();
#endif
  InitTimer();

  McuRTOS_Init();
  if (xTaskCreate(
      MainTask,  /* pointer to the task */
      "Main", /* task name for kernel awareness debugging */
      400/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
  for(;;) { /* should not get here */ }
}

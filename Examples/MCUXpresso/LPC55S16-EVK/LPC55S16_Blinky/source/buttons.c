/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "buttons.h"
#include "buttons_config.h"
#include <assert.h>
#include "McuButton.h"
#include "fsl_pint.h"
//#include "fsl_syscon.h"
#include "McuLED.h"
#include "leds.h"
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif

typedef struct BTN_Desc_t {
  McuBtn_Handle_t handle; /* handle of button pin */
} BTN_Desc_t;

static BTN_Desc_t BTN_Infos[BTN_NOF_BUTTONS];

bool BTN_IsPressed(BTN_Buttons_e btn) {
  assert(btn<BTN_NOF_BUTTONS);
  return McuBtn_IsOn(BTN_Infos[btn].handle);
}

#if 0
static void SysViewLogStart(void) {
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #define MCU_SYSTEM_VIEW_USER_ID_BUTTON_INTERRUPT (0)
  McuSystemView_RecordEnterISR();
  McuSystemView_Print((const char*)"Pressed button\r\n");
  McuSystemView_OnUserStart(MCU_SYSTEM_VIEW_USER_ID_BUTTON_INTERRUPT);
#endif
}

static void SysViewLogEnd(void) {
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_OnUserStop(MCU_SYSTEM_VIEW_USER_ID_BUTTON_INTERRUPT);
  McuSystemView_RecordExitISR();
#endif
}
#endif

#if 0 && McuLib_CONFIG_CPU_IS_LPC
static void pint_intr_callback(pint_pin_int_t pintr, uint32_t pmatch_status) {
  SysViewLogStart();
  /* ... */
  SysViewLogEnd();
}
#endif

void BTN_Deinit(void) {
  for(int i=0; i<BTN_NOF_BUTTONS; i++) {
    BTN_Infos[i].handle = McuBtn_DeinitButton(BTN_Infos[i].handle);
  }
}

void BTN_Init(void) {
  McuBtn_Config_t btnConfig;

  McuBtn_GetDefaultConfig(&btnConfig);
  btnConfig.isLowActive = true;

  btnConfig.hw.gpio = BUTTONS_USER_GPIO;
  btnConfig.hw.port = BUTTONS_USER_PORT;
  btnConfig.hw.pin = BUTTONS_USER_PIN;
  BTN_Infos[BTN_USER].handle = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.gpio = BUTTONS_WAKEUP_GPIO;
  btnConfig.hw.port = BUTTONS_WAKEUP_PORT;
  btnConfig.hw.pin = BUTTONS_WAKEUP_PIN;
  BTN_Infos[BTN_WAKEUP].handle = McuBtn_InitButton(&btnConfig);
#if 0
  SYSCON_AttachSignal(SYSCON, kPINT_PinInt0, kSYSCON_GpioPort0Pin4ToPintsel);

  PINT_Init(PINT); /* Initialize PINT */
  /* Setup Pin Interrupt 0 for rising edge */
  PINT_PinInterruptConfig(PINT, kPINT_PinInt0, kPINT_PinIntEnableFallEdge, pint_intr_callback);
  /* Enable callbacks for PINT0 by Index */
  PINT_EnableCallbackByIndex(PINT, kPINT_PinInt0);
#endif
}

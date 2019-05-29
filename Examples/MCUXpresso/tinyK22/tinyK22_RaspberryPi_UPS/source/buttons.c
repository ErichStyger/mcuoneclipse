/*
 * buttons.c
 *
 *  Created on: 28.05.2019
 *      Author: Erich Styger
 */
#include "platform.h"
#include "buttons.h"
#include "McuButton.h"
#include "McuRTOS.h"
#include "RaspyUART.h"
#include "lv.h"

static McuBtn_Handle_t btnUp, btnDown, btnLeft, btnRight, btnCenter;

static void PollButtons(void) {
  if (McuBtn_IsOn(btnUp)) {
    RASPYU_OnJoystickEvent(EVNT_SW1_PRESSED);
    LV_ButtonEvent(LV_BTN_MASK_UP, LV_MASK_PRESSED);
    vTaskDelay(pdMS_TO_TICKS(50));
    LV_ButtonEvent(LV_BTN_MASK_UP, LV_MASK_RELEASED);
  }
  if (McuBtn_IsOn(btnDown)) {
    RASPYU_OnJoystickEvent(EVNT_SW2_PRESSED);
    LV_ButtonEvent(LV_BTN_MASK_DOWN, LV_MASK_PRESSED);
    vTaskDelay(pdMS_TO_TICKS(50));
    LV_ButtonEvent(LV_BTN_MASK_DOWN, LV_MASK_RELEASED);
  }
  if (McuBtn_IsOn(btnLeft)) {
    RASPYU_OnJoystickEvent(EVNT_SW3_PRESSED);
    LV_ButtonEvent(LV_BTN_MASK_LEFT, LV_MASK_PRESSED);
    vTaskDelay(pdMS_TO_TICKS(50));
    LV_ButtonEvent(LV_BTN_MASK_LEFT, LV_MASK_RELEASED);
  }
  if (McuBtn_IsOn(btnRight)) {
    RASPYU_OnJoystickEvent(EVNT_SW4_PRESSED);
    LV_ButtonEvent(LV_BTN_MASK_RIGHT, LV_MASK_PRESSED);
    vTaskDelay(pdMS_TO_TICKS(50));
    LV_ButtonEvent(LV_BTN_MASK_RIGHT, LV_MASK_RELEASED);
  }
  if (McuBtn_IsOn(btnCenter)) {
    RASPYU_OnJoystickEvent(EVNT_SW5_PRESSED);
    LV_ButtonEvent(LV_BTN_MASK_CENTER, LV_MASK_PRESSED);
    vTaskDelay(pdMS_TO_TICKS(50));
    LV_ButtonEvent(LV_BTN_MASK_CENTER, LV_MASK_RELEASED);
  }
}

static void BtnTask(void *pv) {
  for(;;) {
    PollButtons();
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

static TimerHandle_t timerDbnc;

static void vTimerCallbackDebounce(TimerHandle_t pxTimer) {
}


void BTN_Init(void) {
  McuBtn_Config_t btnConfig;

  McuBtn_GetDefaultConfig(&btnConfig);
  btnConfig.isLowActive = true;

  btnConfig.hw.gpio = PINS_HATNAVUP_GPIO;
  btnConfig.hw.port = PINS_HATNAVUP_PORT;
  btnConfig.hw.pin = PINS_HATNAVUP_PIN;
  btnUp = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.gpio = PINS_HATNAVDOWN_GPIO;
  btnConfig.hw.port = PINS_HATNAVDOWN_PORT;
  btnConfig.hw.pin = PINS_HATNAVDOWN_PIN;
  btnDown = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.gpio = PINS_HATNAVLEFT_GPIO;
  btnConfig.hw.port = PINS_HATNAVLEFT_PORT;
  btnConfig.hw.pin = PINS_HATNAVLEFT_PIN;
  btnLeft = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.gpio = PINS_HATNAVRIGHT_GPIO;
  btnConfig.hw.port = PINS_HATNAVRIGHT_PORT;
  btnConfig.hw.pin = PINS_HATNAVRIGHT_PIN;
  btnRight = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.gpio = PINS_HATNAVPUSH_GPIO;
  btnConfig.hw.port = PINS_HATNAVPUSH_PORT;
  btnConfig.hw.pin = PINS_HATNAVPUSH_PIN;
  btnCenter = McuBtn_InitButton(&btnConfig);

#if 0 && PL_CONFIG_HAS_KBI
  PORT_SetPinInterruptConfig(PINS_HATNAVUP_PORT, PINS_HATNAVUP_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVDOWN_PORT, PINS_HATNAVDOWN_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVLEFT_PORT, PINS_HATNAVLEFT_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVRIGHT_PORT, PINS_HATNAVRIGHT_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVPUSH_PORT, PINS_HATNAVPUSH_PIN, kPORT_InterruptFallingEdge);
  EnableIRQ(PORTB_IRQn);
#endif

  if (xTaskCreate(
      BtnTask,  /* pointer to the task */
      "Btn", /* task name for kernel awareness debugging */
      500/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+1,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    for(;;){} /* error! probably out of memory */
  }
  timerDbnc = xTimerCreate(
        "tmrDbnc", /* name */
        pdMS_TO_TICKS(1000), /* period/time */
        pdTRUE, /* auto reload */
        (void*)0, /* timer ID */
        vTimerCallbackDebounce); /* callback */
  if (timerDbnc==NULL) {
    for(;;); /* failure! */
  }
}

void BTN_Deinit(void) {
#if 0 && PL_CONFIG_HAS_KBI
  DisableIRQ(PORTB_IRQn);
#endif
  btnUp = McuBtn_DeinitButton(btnUp);
  btnDown = McuBtn_DeinitButton(btnDown);
  btnLeft = McuBtn_DeinitButton(btnLeft);
  btnRight = McuBtn_DeinitButton(btnRight);
  btnCenter = McuBtn_DeinitButton(btnCenter);
}

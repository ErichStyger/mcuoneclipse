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
#include "McuDebounce.h"
#include "RaspyUART.h"
#include "lv.h"

static McuBtn_Handle_t btnUp, btnDown, btnLeft, btnRight, btnCenter;
#define BTN_UP 		(1<<0)
#define BTN_DOWN 	(1<<1)
#define BTN_LEFT 	(1<<2)
#define BTN_RIGHT 	(1<<3)
#define BTN_CENTER 	(1<<4)


static uint32_t GetButtons(void) {
	return 0;
}

static void OnDebounceEvent(McuDbnc_EventKinds event, uint32_t buttons) {

}

#define TIMER_PERIOD_MS  20
static McuDbnc_Desc_t data =
{
	.state = MCUDBMC_STATE_IDLE,
	.flags = 0,
	.timerPeriodMs = TIMER_PERIOD_MS,
	.timer = NULL,
	.debounceTicks = 10,
	.scanValue = 0,
	.longKeyCnt = 0,
	.longKeyTicks = 500,
	.getButtons = GetButtons,
	.onDebounceEvent = OnDebounceEvent,
};

static void vTimerCallbackDebounce(TimerHandle_t pxTimer) {

}

static void StartDebounce(uint32_t buttons) {
  data.scanValue = buttons;
  if (xTimerStart(data.timer, 0)!=pdPASS) {
	for(;;); /* failure!?! */
  }
}


static void PollButtons(void) {
  if (McuBtn_IsOn(btnUp)) {
	StartDebounce(BTN_UP);
    RASPYU_OnJoystickEvent(EVNT_SW1_PRESSED);
#if PL_CONFIG_HAS_GUI_KEY_NAV
    LV_ButtonEvent(LV_BTN_MASK_UP, LV_MASK_PRESSED);
    vTaskDelay(pdMS_TO_TICKS(50));
    LV_ButtonEvent(LV_BTN_MASK_UP, LV_MASK_RELEASED);
#endif
  }
  if (McuBtn_IsOn(btnDown)) {
    RASPYU_OnJoystickEvent(EVNT_SW2_PRESSED);
#if PL_CONFIG_HAS_GUI_KEY_NAV
    LV_ButtonEvent(LV_BTN_MASK_DOWN, LV_MASK_PRESSED);
    vTaskDelay(pdMS_TO_TICKS(50));
    LV_ButtonEvent(LV_BTN_MASK_DOWN, LV_MASK_RELEASED);
#endif
  }
  if (McuBtn_IsOn(btnLeft)) {
    RASPYU_OnJoystickEvent(EVNT_SW3_PRESSED);
#if PL_CONFIG_HAS_GUI_KEY_NAV
    LV_ButtonEvent(LV_BTN_MASK_LEFT, LV_MASK_PRESSED);
    vTaskDelay(pdMS_TO_TICKS(50));
    LV_ButtonEvent(LV_BTN_MASK_LEFT, LV_MASK_RELEASED);
#endif
  }
  if (McuBtn_IsOn(btnRight)) {
    RASPYU_OnJoystickEvent(EVNT_SW4_PRESSED);
#if PL_CONFIG_HAS_GUI_KEY_NAV
    LV_ButtonEvent(LV_BTN_MASK_RIGHT, LV_MASK_PRESSED);
    vTaskDelay(pdMS_TO_TICKS(50));
    LV_ButtonEvent(LV_BTN_MASK_RIGHT, LV_MASK_RELEASED);
#endif
  }
  if (McuBtn_IsOn(btnCenter)) {
#if PL_CONFIG_HAS_GUI_KEY_NAV
    RASPYU_OnJoystickEvent(EVNT_SW5_PRESSED);
    LV_ButtonEvent(LV_BTN_MASK_CENTER, LV_MASK_PRESSED);
    vTaskDelay(pdMS_TO_TICKS(50));
    LV_ButtonEvent(LV_BTN_MASK_CENTER, LV_MASK_RELEASED);
#endif
  }
}

static void BtnTask(void *pv) {
  for(;;) {
    PollButtons();
    vTaskDelay(pdMS_TO_TICKS(50));
  }
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
  data.timer = xTimerCreate(
        "tmrDbnc", /* name */
        pdMS_TO_TICKS(TIMER_PERIOD_MS), /* period/time */
        pdTRUE, /* auto reload */
        (void*)2, /* timer ID */
        vTimerCallbackDebounce); /* callback */
  if (data.timer==NULL) {
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

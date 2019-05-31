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
#include "McuRTT.h"
#if PL_CONFIG_USE_KBI
  #include "fsl_port.h"
#endif

static McuBtn_Handle_t btnUp, btnDown, btnLeft, btnRight, btnCenter;

bool BTN_DownButtonIsPressed(void) {
  return McuBtn_IsOn(btnDown);
}

static uint32_t GetButtons(void) {
  uint32_t val = 0;

  if (McuBtn_IsOn(btnUp)) {
    val |= BTN_UP;
  }
  if (McuBtn_IsOn(btnDown)) {
    val |= BTN_DOWN;
  }
  if (McuBtn_IsOn(btnLeft)) {
    val |= BTN_LEFT;
  }
  if (McuBtn_IsOn(btnRight)) {
    val |= BTN_RIGHT;
  }
  if (McuBtn_IsOn(btnCenter)) {
    val |= BTN_CENTER;
  }
  return val;
}

static void OnDebounceEvent(McuDbnc_EventKinds event, uint32_t buttons);

#define TIMER_PERIOD_MS  20 /* frequency of timer */
static McuDbnc_Desc_t data =
{
	.state = MCUDBMC_STATE_IDLE,
	.timerPeriodMs = TIMER_PERIOD_MS,
	.timer = NULL,
	.debounceTimeMs = 100,
	.repeatTimeMs   = 300,
	.longKeyTimeMs  = 1000,
	.getButtons = GetButtons,
	.onDebounceEvent = OnDebounceEvent,
};

static void OnDebounceEvent(McuDbnc_EventKinds event, uint32_t buttons) {
  switch(event) {
    case MCUDBNC_EVENT_PRESSED:
      SEGGER_printf("pressed: %d\r\n", buttons);
    #if PL_CONFIG_USE_RASPY_UART
      RASPYU_OnJoystickEvent(buttons);
    #endif
    #if PL_CONFIG_USE_GUI
      if (buttons&BTN_UP) {
        LV_ButtonEvent(LV_BTN_MASK_UP, LV_MASK_PRESSED);
      }
      if (buttons&BTN_DOWN) {
        LV_ButtonEvent(LV_BTN_MASK_DOWN, LV_MASK_PRESSED);
      }
      if (buttons&BTN_LEFT) {
        LV_ButtonEvent(LV_BTN_MASK_LEFT, LV_MASK_PRESSED);
      }
      if (buttons&BTN_RIGHT) {
        LV_ButtonEvent(LV_BTN_MASK_RIGHT, LV_MASK_PRESSED);
      }
      if (buttons&BTN_CENTER) {
        LV_ButtonEvent(LV_BTN_MASK_CENTER, LV_MASK_PRESSED);
      }
    #endif
      break;

    case MCUDBNC_EVENT_PRESSED_REPEAT:
      SEGGER_printf("repeat: %d\r\n", buttons);
      break;

    case MCUDBNC_EVENT_LONG_PRESSED:
      SEGGER_printf("long pressed: %d\r\n", buttons);
    #if PL_CONFIG_USE_GUI
      if (buttons&BTN_UP) {
        LV_ButtonEvent(LV_BTN_MASK_UP, LV_MASK_PRESSED_LONG);
      }
      if (buttons&BTN_DOWN) {
        LV_ButtonEvent(LV_BTN_MASK_DOWN, LV_MASK_PRESSED_LONG);
      }
      if (buttons&BTN_LEFT) {
        LV_ButtonEvent(LV_BTN_MASK_LEFT, LV_MASK_PRESSED_LONG);
      }
      if (buttons&BTN_RIGHT) {
        LV_ButtonEvent(LV_BTN_MASK_RIGHT, LV_MASK_PRESSED_LONG);
      }
      if (buttons&BTN_CENTER) {
        LV_ButtonEvent(LV_BTN_MASK_CENTER, LV_MASK_PRESSED_LONG);
      }
    #endif
      break;

    case MCUDBNC_EVENT_LONG_PRESSED_REPEAT:
      SEGGER_printf("long repeat: %d\r\n", buttons);
      break;

    case MCUDBNC_EVENT_RELEASED:
      SEGGER_printf("released: %d\r\n", buttons);
    #if PL_CONFIG_USE_RASPY_UART
      RASPYU_OnJoystickEvent(0);
    #endif
    #if PL_CONFIG_USE_GUI
      if (buttons&BTN_UP) {
        LV_ButtonEvent(LV_BTN_MASK_UP, LV_MASK_RELEASED);
      }
      if (buttons&BTN_DOWN) {
        LV_ButtonEvent(LV_BTN_MASK_DOWN, LV_MASK_RELEASED);
      }
      if (buttons&BTN_LEFT) {
        LV_ButtonEvent(LV_BTN_MASK_LEFT, LV_MASK_RELEASED);
      }
      if (buttons&BTN_RIGHT) {
        LV_ButtonEvent(LV_BTN_MASK_RIGHT, LV_MASK_RELEASED);
      }
      if (buttons&BTN_CENTER) {
        LV_ButtonEvent(LV_BTN_MASK_CENTER, LV_MASK_RELEASED);
      }
    #endif
      break;

    default:
    case MCUDBNC_EVENT_END:
      (void)xTimerStop(data.timer, pdMS_TO_TICKS(100)); /* stop timer */
      SEGGER_printf("end: %d\r\n", buttons);
      break;
  }
}

static void vTimerCallbackDebounce(TimerHandle_t pxTimer) {
  /* called with TIMER_PERIOD_MS during debouncing */
  McuDbnc_Process(&data);
}

static void StartDebounce(uint32_t buttons, bool fromISR) {
  BaseType_t res;
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  if (data.state==MCUDBMC_STATE_IDLE) {
    data.scanValue = buttons;
    data.state = MCUDBMC_STATE_START;
    McuDbnc_Process(&data);
    if (fromISR) {
      res = xTimerStartFromISR(data.timer, &xHigherPriorityTaskWoken);
    } else {
      res = xTimerStart(data.timer, pdMS_TO_TICKS(100));
    }
    assert(res==pdPASS);
    if (fromISR) {
      portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
  }
}

#if !PL_CONFIG_USE_KBI
static void PollButtons(void) {
  if (McuBtn_IsOn(btnUp)) {
	StartDebounce(BTN_UP, false);
  }
  if (McuBtn_IsOn(btnDown)) {
    StartDebounce(BTN_DOWN, false);
  }
  if (McuBtn_IsOn(btnLeft)) {
    StartDebounce(BTN_LEFT, false);
  }
  if (McuBtn_IsOn(btnRight)) {
    StartDebounce(BTN_RIGHT, false);
  }
  if (McuBtn_IsOn(btnCenter)) {
    StartDebounce(BTN_CENTER, false);
  }
}

static void BtnTask(void *pv) {
  for(;;) {
    PollButtons();
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}
#else
void PORTB_IRQHandler(void) {
  uint32_t flags;

  flags = GPIO_PortGetInterruptFlags(GPIOB);
  if (flags&(1U<<PINS_HATNAVLEFT_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVLEFT_GPIO, 1U<<PINS_HATNAVLEFT_PIN);
    StartDebounce(BTN_LEFT, true);
  }
  if (flags&(1U<<PINS_HATNAVRIGHT_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVRIGHT_GPIO, 1U<<PINS_HATNAVRIGHT_PIN);
    StartDebounce(BTN_RIGHT, true);
  }
  if (flags&(1U<<PINS_HATNAVUP_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVUP_GPIO, 1U<<PINS_HATNAVUP_PIN);
    StartDebounce(BTN_UP, true);
  }
  if (flags&(1U<<PINS_HATNAVDOWN_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVDOWN_GPIO, 1U<<PINS_HATNAVDOWN_PIN);
    StartDebounce(BTN_DOWN, true);
  }
  if (flags&(1U<<PINS_HATNAVPUSH_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVPUSH_GPIO, 1U<<PINS_HATNAVPUSH_PIN);
    StartDebounce(BTN_CENTER, true);
  }
  __DSB();
}
#endif

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

#if PL_CONFIG_USE_KBI
  PORT_SetPinInterruptConfig(PINS_HATNAVUP_PORT, PINS_HATNAVUP_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVDOWN_PORT, PINS_HATNAVDOWN_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVLEFT_PORT, PINS_HATNAVLEFT_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVRIGHT_PORT, PINS_HATNAVRIGHT_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVPUSH_PORT, PINS_HATNAVPUSH_PIN, kPORT_InterruptFallingEdge);
  NVIC_SetPriority(PORTB_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
  EnableIRQ(PORTB_IRQn);
#else /* use task for button polling */
  if (xTaskCreate(
      BtnTask,  /* pointer to the task */
      "Btn", /* task name for kernel awareness debugging */
      500/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+4,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    for(;;){} /* error! probably out of memory */
  }
#endif
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
#if PL_CONFIG_USE_KBI
  DisableIRQ(PORTB_IRQn);
#endif
  btnUp = McuBtn_DeinitButton(btnUp);
  btnDown = McuBtn_DeinitButton(btnDown);
  btnLeft = McuBtn_DeinitButton(btnLeft);
  btnRight = McuBtn_DeinitButton(btnRight);
  btnCenter = McuBtn_DeinitButton(btnCenter);
}

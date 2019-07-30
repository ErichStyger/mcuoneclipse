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
#include "McuRTT.h"
#if PL_CONFIG_USE_KBI
  #include "fsl_port.h"
#endif

/* Buttons */
/* PIO0_4 */
#define PINS_BTNK3_GPIO       GPIO
#define PINS_BTNK3_PORT       0U
#define PINS_BTNK3_PIN        4U

/* PIO0_12 */
#define PINS_BTNK1_GPIO       GPIO
#define PINS_BTNK1_PORT       0U
#define PINS_BTNK1_PIN        12U

static McuBtn_Handle_t btnK1, btnK3;

bool BTN_K1ButtonIsPressed(void) {
  return McuBtn_IsOn(btnK1);
}

bool BTN_K3ButtonIsPressed(void) {
  return McuBtn_IsOn(btnK3);
}

static uint32_t GetButtons(void) {
  uint32_t val = 0;

  if (McuBtn_IsOn(btnK1)) {
    val |= BTN_K1;
  }
  if (McuBtn_IsOn(btnK3)) {
    val |= BTN_K3;
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

#if McuLib_CONFIG_SDK_USE_FREERTOS
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
#endif

#if !PL_CONFIG_USE_KBI
#if McuLib_CONFIG_SDK_USE_FREERTOS
static void PollButtons(void) {
  if (McuBtn_IsOn(btnK1)) {
	StartDebounce(BTN_K1, false);
  }
  if (McuBtn_IsOn(btnK3)) {
    StartDebounce(BTN_K3, false);
  }
}

static void BtnTask(void *pv) {
  for(;;) {
    PollButtons();
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}
#endif
#else
void PORTB_IRQHandler(void) {
  uint32_t flags;

  flags = GPIO_PortGetInterruptFlags(GPIOB);
#if TINYK22_HAT_VERSION==3 /* only Rev V3 has left and right on Port B. Rev V4 and V5 have it on Port A */
  if (flags&(1U<<PINS_HATNAVLEFT_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVLEFT_GPIO, 1U<<PINS_HATNAVLEFT_PIN);
    StartDebounce(BTN_LEFT, true);
  }
  if (flags&(1U<<PINS_HATNAVRIGHT_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVRIGHT_GPIO, 1U<<PINS_HATNAVRIGHT_PIN);
    StartDebounce(BTN_RIGHT, true);
  }
#endif
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

#if TINYK22_HAT_VERSION==4 || TINYK22_HAT_VERSION==5
void PORTA_IRQHandler(void) { /* left and right are on Port A */
  uint32_t flags;

  flags = GPIO_PortGetInterruptFlags(GPIOA);
  if (flags&(1U<<PINS_HATNAVLEFT_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVLEFT_GPIO, 1U<<PINS_HATNAVLEFT_PIN);
    StartDebounce(BTN_LEFT, true);
  }
  if (flags&(1U<<PINS_HATNAVRIGHT_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVRIGHT_GPIO, 1U<<PINS_HATNAVRIGHT_PIN);
    StartDebounce(BTN_RIGHT, true);
  }
  __DSB();
}
#endif

#endif

void BTN_Init(void) {
  McuBtn_Config_t btnConfig;

  McuBtn_GetDefaultConfig(&btnConfig);
  btnConfig.isLowActive = true;

  btnConfig.hw.gpio = PINS_BTNK1_GPIO;
  btnConfig.hw.port = PINS_BTNK1_PORT;
  btnConfig.hw.pin = PINS_BTNK1_PIN;
  btnK1 = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.gpio = PINS_BTNK3_GPIO;
  btnConfig.hw.port = PINS_BTNK3_PORT;
  btnConfig.hw.pin = PINS_BTNK3_PIN;
  btnK3 = McuBtn_InitButton(&btnConfig);

#if PL_CONFIG_USE_KBI
  PORT_SetPinInterruptConfig(PINS_HATNAVUP_PORT, PINS_HATNAVUP_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVDOWN_PORT, PINS_HATNAVDOWN_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVLEFT_PORT, PINS_HATNAVLEFT_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVRIGHT_PORT, PINS_HATNAVRIGHT_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVPUSH_PORT, PINS_HATNAVPUSH_PIN, kPORT_InterruptFallingEdge);
  #if TINYK22_HAT_VERSION==3
  /* all buttons are on Port B */
  NVIC_SetPriority(PORTB_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
  EnableIRQ(PORTB_IRQn);
  #elif TINYK22_HAT_VERSION==4 || TINYK22_HAT_VERSION==5
  /* left and right are on Port A. up, down and push are on Port B */
  NVIC_SetPriority(PORTA_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
  EnableIRQ(PORTA_IRQn);
  NVIC_SetPriority(PORTB_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
  EnableIRQ(PORTB_IRQn);
  #endif
#elif McuLib_CONFIG_SDK_USE_FREERTOS /* use task for button polling */
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
#if McuLib_CONFIG_SDK_USE_FREERTOS
  data.timer = xTimerCreate(
        "tmrDbnc", /* name */
        pdMS_TO_TICKS(TIMER_PERIOD_MS), /* period/time */
        pdTRUE, /* auto reload */
        (void*)2, /* timer ID */
        vTimerCallbackDebounce); /* callback */
  if (data.timer==NULL) {
    for(;;); /* failure! */
  }
#endif
}

void BTN_Deinit(void) {
#if PL_CONFIG_USE_KBI
  #if TINYK22_HAT_VERSION==3
    DisableIRQ(PORTB_IRQn); /* all buttons are on Port B */
  #elif TINYK22_HAT_VERSION==4 || TINYK22_HAT_VERSION==5
    DisableIRQ(PORTA_IRQn); /* left and right are on Port A */
    DisableIRQ(PORTB_IRQn); /* up, down, push are on Port B */
  #endif
#endif
  btnK1 = McuBtn_DeinitButton(btnK1);
  btnK3 = McuBtn_DeinitButton(btnK3);
}

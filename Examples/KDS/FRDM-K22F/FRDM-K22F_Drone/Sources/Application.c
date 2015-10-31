/*
 * Application.c
 *
 *  Created on: 20.09.2015
 *      Author: tastyger
 */

#include "Platform.h"
#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "FRTOS1.h"
#include "PORT_PDD.h"
#if PL_HAS_RTOS
  #include "FreeRTOS.h"
  #if configUSE_TRACE_HOOKS
  #include "RTOSTRC1.h"
  #endif
#endif
#if PL_HAS_SHELL
  #include "Shell.h"
#endif
#if PL_HAS_ESC
  #include "ESC.h"
#endif
#if PL_HAS_SENSOR_FUSION
  #include "SensorTasks.h"
#endif
#if PL_HAS_SUMD
  #include "SumD.h"
#endif

#if PL_HAS_SUMD
const uint8_t sumdmsg1[] =
{
    /* 0xA8: start */
    /* 0: SUMH (legacy), 1: SUMD */
    /* 0x8: nof channels */
    0xA8,
    0x01,
    0x08,
    0x2E, 0xE8,
    0x2E, 0xD0,
    0x2E, 0xF0,
    0x2E, 0xe0,
    0x2E, 0xE0,
    0x2E, 0xE0,
    0x2E, 0xE0,
    0x2E, 0xE0,
    /* (OF = Failsafe OFF) or extra 16bits for: FS = Failsafe POSITION ou HD = HOLD) */
    0x57, 0xB4,
};

static uint8_t TestSumD(void) {
  int res;
  int i;
  #define MAX_CHANNELS 8
  uint8_t rssi=0, rx_count=0;
  uint16_t channel_count, channels[MAX_CHANNELS];
  const uint16_t max_chan_count = MAX_CHANNELS;

  res = 1;
  for(i=0;i<sizeof(sumdmsg1) && res==1;i++) {
    res = sumd_decode(sumdmsg1[i], &rssi, &rx_count, &channel_count, &channels[0], max_chan_count);
// * @return 0 for success (a decoded packet), 1 for no packet yet (accumulating), 2 for unknown packet, 3 for out of sync, 4 for checksum error
  }
  if (res!=0) {
    return ERR_FAILED;
  }
  return ERR_OK;
}
#endif


static void AppTask(void *pvParameters) {
  (void)pvParameters; /* parameter not used */

  #if PL_HAS_SUMD
  TestSumD();
  #endif
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
}

void APP_Run(void) {
#if configUSE_TRACE_HOOKS
  if (RTOSTRC1_uiTraceStart()==0) {
    for(;;){} /* error starting trace recorder. Not setup for enough queues/tasks/etc? */
  }
#endif

#if PL_HAS_SD_CARD
  /* SD card detection: PTB16 with pull-down! */
  PORT_PDD_SetPinPullSelect(PORTB_BASE_PTR, 16, PORT_PDD_PULL_DOWN);
  PORT_PDD_SetPinPullEnable(PORTB_BASE_PTR, 16, PORT_PDD_PULL_ENABLE);
#endif
#if PL_HAS_PUSH_BUTTONS
  /* SW2: PTC1 */
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 1, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 1, PORT_PDD_PULL_ENABLE);
  /* SW3: PTB17 */
  PORT_PDD_SetPinPullSelect(PORTB_BASE_PTR, 17, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTB_BASE_PTR, 17, PORT_PDD_PULL_ENABLE);
#endif

  LED1_On();
  LED1_Off();
  LED2_On();
  LED2_Off();
  LED3_On();
  LED3_Off();
#if PL_HAS_SHELL
  SHELL_Init();
#endif
#if PL_HAS_ESC
  ESC_Init();
#endif
#if PL_HAS_SENSOR_FUSION
  SensorTasks_Init();
#endif
  if (FRTOS1_xTaskCreate(
      AppTask,  /* pointer to the task */
      "Main", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    for(;;){} /* error! probably out of memory */
  }
  FRTOS1_vTaskStartScheduler();
  for(;;) {}
}



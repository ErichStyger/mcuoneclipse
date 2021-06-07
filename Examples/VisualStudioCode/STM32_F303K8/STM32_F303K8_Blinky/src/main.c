#include "platform.h"
#include "McuWait.h"
#include "McuRTOS.h"
#include "Led.h"
#include "McuShell.h"
#include "McuLog.h"

int i;

static TimerHandle_t timerHndl;
#define TIMER_PERIOD_MS    McuTimeDate_CONFIG_TICK_TIME_MS

static void vTimerCallback(TimerHandle_t pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
  McuTimeDate_AddTick();
}

static void blinkyTask(void *pv) {
    McuLog_info("started blinky task");
    for(;;) {
        LED_Neg(LED_LED0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

int main(void) {
    PL_Init();
    McuLog_info("initialized system");
    if (xTaskCreate(
        blinkyTask,  /* pointer to the task */
        "blinky", /* task name for kernel awareness debugging */
        500/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+2,  /* initial priority */
        (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) 
    {
      McuLog_fatal("failed creating blinky task");
      for(;;){} /* error! probably out of memory */
    }
    timerHndl = xTimerCreate("timer0", pdMS_TO_TICKS(TIMER_PERIOD_MS), pdTRUE, (void *)0, vTimerCallback);
    if (timerHndl==NULL) {
       McuLog_fatal("failed creating timer");
      for(;;); /* failure! */
    }
    if (xTimerStart(timerHndl, 0)!=pdPASS) {
       McuLog_fatal("failed starting timer");
      for(;;); /* failure! */
    }

    McuLog_info("starting scheduler");
    vTaskStartScheduler();
    for(;;) {
        McuWait_Waitms(500);
        LED_Neg(LED_LED0);
        McuShell_SendStr((unsigned char*)"hello\r\n", McuShell_GetStdio()->stdOut);
        i++;
    }
}
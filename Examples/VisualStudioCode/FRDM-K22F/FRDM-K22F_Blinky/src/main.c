#include "main.h"
#include "platform.h"
#include "leds.h"
#include "McuLED.h"
#include "McuWait.h"
#include "McuRTOS.h"

void __assertion_failed(char *_Expr) {
  for(;;) {
    __asm("nop");
  }
}

static void BlinkyTask(void *p) {
  for(;;) {
    McuLED_Toggle(LEDS_LedBlue);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

cc

static int i;

int main(void) {
    volatile int local = 0;
    
    PL_Init();
    if (xTaskCreate(BlinkyTask, "Blinky", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL)!= pdPASS) {
      for(;;) {}
    }
    vTaskStartScheduler();
    for(;;) {
        McuLED_Toggle(LEDS_LedBlue);
        McuWait_Waitms(100);
        __asm("nop");
        i++;
        local++;  
    }
    return 0;
} 
#include "main.h"
#include "platform.h"
#include "leds.h"
#include "McuLED.h"
#include "McuWait.h"

void __assertion_failed(char *_Expr) {
  for(;;) {
    __asm("nop");
  }
}

static int i;

int main(void) {
    volatile int local = 0;
    
    PL_Init();
    for(;;) {
        McuLED_Toggle(LEDS_LedBlue);
        McuWait_Waitms(100);
        __asm("nop");
        i++;
        local++;  
    }
    return 0;
} 
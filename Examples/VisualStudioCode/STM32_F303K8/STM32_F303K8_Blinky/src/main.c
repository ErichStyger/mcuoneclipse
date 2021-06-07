#include "platform.h"
#include "McuWait.h"
#include "McuRTOS.h"

int i;

int main(void) {
    PL_Init();
    for(;;) {
        McuWait_Waitms(100);
        i++;
    }
}
#include "platform.h"
#include "McuWait.h"
#include "McuRTOS.h"
#include "Led.h"
#include "McuShell.h"

int i;

int main(void) {
    PL_Init();
    for(;;) {
        McuWait_Waitms(500);
        LED_Neg(LED_LED0);
        McuShell_SendStr("hello\r\n", McuShell_GetStdio()->stdOut);
        i++;
    }
}
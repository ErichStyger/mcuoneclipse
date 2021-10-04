#include "main.h"
#include "platform.h"
#include "application.h"
#include "McuLog.h"

void __assertion_failed(char *_Expr) {
  McuLog_fatal("assertion called: %s", _Expr);
  for(;;) {
    __asm("nop");
  }
}

int main(void) {
    APP_Run();
    return 0;
} 
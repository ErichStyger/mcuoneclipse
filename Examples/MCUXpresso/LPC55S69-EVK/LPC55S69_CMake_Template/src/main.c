#include <stdio.h>

int main(void) {
  printf("hello world!\n");
  for(;;) {
    __asm("nop");
  }
  return 0;
}

#include "Application.h"
#include <stdio.h>

void APP_Run(void) {
  int value;
  char buffer[64];

  for(;;) {
    printf("Hello world!\r\n");
    printf("Please enter a name:\n\r");
    scanf("%s", buffer);
    printf("  I have received: '%s'\r\n", buffer);

    printf("Please enter a number:\r\n");
    scanf("%i", &value);
    //printf("  I have received: '%i', %f\r\n", value, 3.75);
    printf("  I have received: '%i'\r\n", value);
  }
}

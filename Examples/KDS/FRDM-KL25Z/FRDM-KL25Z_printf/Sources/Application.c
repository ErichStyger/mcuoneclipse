/*
 * Application.c
 *
 *  Created on: 08.07.2014
 *      Author: tastyger
 */

#include "Application.h"
#include <stdio.h>
#include "LEDR.h"
#include "LEDG.h"
#include "LEDB.h"
#include "WAIT1.h"

void APP_Run(void) {
  int value=0;
  char buffer[64];
  float f = 0.0;

  printf("Hello world!\r\n");
  for(;;) {
    printf("Float value: %f\r\n", f);
    f+=1.1;

    LEDG_On();
    printf("Please enter a name:\n\r");
    scanf("%s", buffer);
    printf("  I have received: '%s'\r\n", buffer);
    LEDG_Off();

    LEDB_On();
    printf("Please enter a number:\r\n");
    scanf("%i", &value);
    printf("  I have received: '%i'\r\n", value);
    LEDB_Off();

  }
}

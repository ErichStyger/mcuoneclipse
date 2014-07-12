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
#include "WAIT1.h"

void APP_Run(void) {
  int value;
  char buffer[64];

  for(;;) {
    printf("Hello world!\r\n");
    LEDR_On();
    WAIT1_Waitms(500);
    LEDR_Off();

    LEDG_On();
    WAIT1_Waitms(500);
    LEDG_Off();
  }

  for(;;) {
    printf("Hello world!\r\n");
    printf("Please enter a name:\n\r");
    scanf("%s", buffer);
    printf("  I have received: '%s'\r\n", buffer);

    printf("Please enter a number:\r\n");
    scanf("%i", &value);
    printf("  I have received: '%i'\r\n", value);
  }
}

/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
#include <stdio.h>
#include "ConsoleIO.h"

int main(void)
{
	int counter = 0;
	
	ConsoleIO_Init();
	for(;;) {	   
	   	counter++;
	   	printf("Hello world!\r\n");
	}
	
	return 0;
}

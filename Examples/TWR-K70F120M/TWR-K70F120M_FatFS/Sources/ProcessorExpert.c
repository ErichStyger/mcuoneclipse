/** ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MK70FN1M0VMJ15
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior ARM C Compiler
**     Date/Time   : 2016-01-29, 08:10, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "TWR_UART.h"
#include "WAIT1.h"
#include "TmDt1.h"
#include "FATM1.h"
#include "SDHC1.h"
#include "GPIO1.h"
#include "TMOUT1.h"
#include "FAT1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "UART.h"

void main(void)
{
	/* Write your local variable definition here */
	uint8 buffer[32];
	LDD_TDeviceData* SD_data;
	FIL fp;
	UINT bw;
	FATFS fs;
	
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	WAIT1_Wait100Cycles();
	UART_print("hello\r\n", 7);
	
	SD_data = FATM1_Init(0);
	
	if(FATM1_CardPresent()){
		UART_print("card detected!\r\n", 16);
		
		if(FAT1_mount(0, &fs) != FR_OK){
			UART_print("Failed mount\r\n", 14);
		} else {
			if(FAT1_open(&fp, "./test.txt", FA_CREATE_ALWAYS|FA_WRITE) != FR_OK){
				UART_print("Failed file open\r\n", 18);
			} else {
				UART_print("File opened!\r\n", 14);
				if(FAT1_write(&fp, "test write", 10, &bw) != FR_OK){
					UART_print("Failed writing file\r\n", 21);
				} else {
					UART_print("File written\r\n", 14);
					//FAT1_sync(&fp);
				}
			}
			FAT1_close(&fp);
			UART_print("file closed\r\n", 13);
			
			FAT1_mount(0, NULL);
			UART_print("unmounted\r\n", 11);
		}
	} else{
		UART_print("card NOT detected!\r\n", 20);
	}
	
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*
** ###################################################################
**
**     This file was created by Processor Expert 5.3 [05.01]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

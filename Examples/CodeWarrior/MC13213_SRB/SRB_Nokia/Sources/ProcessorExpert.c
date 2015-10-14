/** ###################################################################
**     Filename  : ProcessorExpert.C
**     Project   : ProcessorExpert
**     Processor : MC13213
**     Version   : Driver 01.11
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 06.04.2010, 19:24
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE ProcessorExpert */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "WAIT1.h"
#include "PDC1.h"
#include "RESpin1.h"
#include "SCEpin1.h"
#include "D_Cpin1.h"
#include "SPI1.h"
#include "Output1.h"
#include "Clock1.h"
#include "GDisp1.h"
#include "FDisp1.h"
#include "GFONT1.h"
#include "KEY1.h"
#include "keyPin1.h"
#include "KeyISRpin1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "LED4.h"
#include "LEDpin4.h"
#include "TRG1.h"
#include "FRTOS1.h"
#include "RTOSSWI1.h"
#include "TickCntr1.h"
#include "LED5.h"
#include "LEDpin5.h"
#include "UTIL1.h"
#include "CS1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

/*! \brief Draw 4 dots into each display corner */
static void draw4Dots(void) {
  GDisp1_Clear(); /* clear display buffer */
  /* now draw the 4 corner pixels */
  GDisp1_SetPixel(0,0); /* left top corner */
  GDisp1_SetPixel(0,GDisp1_GetHeight()-1); /* left lower corner */
  GDisp1_SetPixel(GDisp1_GetWidth()-1, 0); /* right top corner */
  GDisp1_SetPixel(GDisp1_GetWidth()-1,GDisp1_GetHeight()-1); /* right bottom corner */
  /* drawing a horizontal line (on line 3) */
  GDisp1_DrawHLine(0, 3, GDisp1_GetWidth(), GDisp1_COLOR_BLACK);
  /* done manipulating the display local data */
  GDisp1_UpdateFull(); /* display it */
}

static void drawDemo(void) {
  int i;

  GDisp1_Clear(); /* clear display buffer */
  for (i=0; i<30; i++) {
    GDisp1_DrawLine(i, i, GDisp1_GetWidth()-i, GDisp1_GetHeight()-i, GDisp1_COLOR_BLACK);
  }
  GDisp1_DrawFilledCircle(15, 15, 10, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull(); /* display it */
}

static portTASK_FUNCTION(AppTask, pvParameters) {
  (void)pvParameters;
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  }
}

//#include "PE_Types.h"
void main(void) {
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  LED5_On();
  LED1_On();
  LED1_Off();
  PDC1_SetPos(0,0);
  PDC1_WriteChar('a');
  PDC1_WriteString("Hello World!");
  draw4Dots();
  drawDemo();
  if (FRTOS1_xTaskCreate(
      AppTask,  /* pointer to the task */
        "Main", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) 
  {
    /*lint -e527 */
    for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
  FRTOS1_vTaskStartScheduler(); 
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*
** ###################################################################
**
**     This file was created by Processor Expert 4.00 Beta [04.40]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/

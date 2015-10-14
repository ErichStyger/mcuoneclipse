/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MKE02Z64VLH2
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-11-16, 15:25, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file ProcessorExpert.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
**  @{
*/         
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd2.h"
#include "WAIT1.h"
#include "UTIL1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
static void TermEmulation(void) {
  for(;;) {
    Term1_SetColor(clRed, clBlack); /* red text on black background */
    Term1_SendStr("Hello World in Red!\r\n"); /* writing a string */
    Term1_SetColor(clBlue, clWhite); /* blue text on white background */
    Term1_SendStr("Hello World in Blue!\r\n"); /* writing a string */
    WAIT1_Waitms(500); /* slow down things */
  }
}

static void Write(void) {
  for(;;) {
    Term1_SendStr("Hello World!\r\n"); /* writing a string */
    Term1_SendChar('a'); /* writing a single character */
    Term1_CRLF(); /* writing a new line */
    Term1_SendNum(1234); /* writing a number */
    Term1_SendChar(' '); /* add a space */
    Term1_SendFloatNum(37.5); /* write a floating point number */
    Term1_CRLF(); /* writing a new line */
    
    WAIT1_Waitms(500); /* slow down things */
  }
}

static void ReadChar(void) {
  for(;;) {
    char ch;
    
    Term1_SendStr("\r\nPlease press a key\r\n");
    Term1_ReadChar(&ch);
    Term1_SendStr("You pressed: ");
    Term1_SendChar(ch);
  }
}

static void ReadString(void) {
  for(;;) {
    unsigned char buf[32];
    
    Term1_SendStr("\r\nPlease enter a string with return\r\n");
    Term1_ReadLine(buf);
    Term1_SendStr("You entered: ");
    Term1_SendStr(buf);
  }
}

static void PrintDataValues(uint16_t val1, uint16_t val2) {
  unsigned char buf[24];
  
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"Data: ");
  UTIL1_strcatNum16u(buf, sizeof(buf), val1);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)", ");
  UTIL1_strcatNum16u(buf, sizeof(buf), val2);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  Term1_SendStr(buf);
}

static void InputValues(void) {
  unsigned char buf[32];
  const unsigned char *p;
  int32_t val1, val2;
  
  Term1_SendStr("Enter two numbers, separated by space, followed by a new-line:\r\n");
  Term1_ReadLine(buf); /* will block */
  p = buf; /* point to start of the buffer */
  if (UTIL1_xatoi(&p, &val1) == ERR_OK) {
    /* first number was ok */
    if (UTIL1_strncmp((char*)p, (char*)" ", sizeof(" ")-1)==0) {
      /* ok, number followed space */
      if (UTIL1_xatoi(&p, &val2) == ERR_OK) {
        /* Successfully read "<number>, <number>"! Write the values in hex */
        UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"0x"); /* write hex prefix */
        UTIL1_strcatNum32Hex(buf, sizeof(buf), val1);
        Term1_SendStr(buf);
        UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)", 0x"); /* write hex prefix */
        UTIL1_strcatNum32Hex(buf, sizeof(buf), val2);
        Term1_SendStr(buf);
        Term1_SendStr("\r\nSuccess!\r\n");
        return;
      }
    }
  }
  Term1_SendStr("failed!\r\n");
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  //Write();
  //TermEmulation();
  //ReadChar();
  //ReadString();
  //PrintDataValues(37, 48);
  InputValues();

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

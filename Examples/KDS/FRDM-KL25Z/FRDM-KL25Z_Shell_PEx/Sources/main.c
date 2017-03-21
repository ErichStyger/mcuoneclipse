/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM-KL25Z_Shell_PEx
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-02-06, 15:14, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "UTIL1.h"
#include "CLS1.h"
#include "WAIT1.h"
#include "CS1.h"
#include "KSDK1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "XF1.h"
#include "MCUC1.h"
#include "RTT1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
static void ReadText(void) {
  uint8_t buffer[32], ch, i;

  for(;;) {
    CLS1_SendStr("Enter some text: ", CLS1_GetStdio()->stdOut);
    buffer[0] = '\0';
    i = 0;
    do {
      if (CLS1_KeyPressed()) {
        CLS1_ReadChar(&ch); /* read the character */
        if (ch!='\0') { /* received a character */
          buffer[i++] = ch; /* store in buffer */
          if (i>=sizeof(buffer)) { /* reached end of buffer? */
            buffer[i] = '\0'; /* terminate string */
            break; /* leave loop */
          }
          if (ch=='\n') { /* line end? */
            buffer[i] = '\0'; /* terminate string */
            break; /* leave loop */
          }
        }
      }
    } while(1);
    CLS1_SendStr("You entered: ", CLS1_GetStdio()->stdOut);
    CLS1_SendStr(buffer, CLS1_GetStdio()->stdOut);
    CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
  }
}

static int app_value = 0;

static uint8_t ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  int32_t tmp;
  const uint8_t *p;
  uint8_t buf[16];

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "app help")==0) {
    CLS1_SendHelpStr((unsigned char*)"app", (const unsigned char*)"Group of app commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  val <number>", (const unsigned char*)"Set value\r\n", io->stdOut);
    *handled = TRUE;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "app status")==0)) {
    CLS1_SendStatusStr((unsigned char*)"app", (const unsigned char*)"\r\n", io->stdOut);
    UTIL1_Num32sToStr(buf, sizeof(buf), app_value);
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
    CLS1_SendStatusStr("  val", buf, io->stdOut);
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, "app val", sizeof("app val")-1)==0) {
    p = cmd+sizeof("app val")-1;
    res = UTIL1_xatoi(&p, &tmp);
    if (res==ERR_OK) {
      app_value = tmp;
      *handled = TRUE;
    }
    return res;
  }
  return res;
}

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand, /* default shell parser */
  ParseCommand, /* my own shell parser */
  NULL /* Sentinel, must be last */
};

static void Shell(void) {
  unsigned char buf[48];
  int cntr = 0;

  app_value = 0; /* init value */
  buf[0] = '\0'; /* init buffer */
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable); /* write help */
  for(;;) { /* wait for input and parse it */
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
    cntr++;
  }
}

static void Test(void) {
  static int position=0;
  static unsigned char buff[64], ch='\0';
  for(;;) {
    LED1_Off();
    if (CLS1_KeyPressed()) {
      CLS1_ReadChar(&ch); /* read the character */
      CLS1_SendStr("read a char\r\n", CLS1_GetStdio()->stdOut);
    #if 1
      XF1_xsprintf(buff,"char =0x%x Pos=%d\r\n",ch,position);
      CLS1_SendStr(buff, CLS1_GetStdio()->stdOut);
    #endif
    }
    CLS1_SendStr("Hello World \r\n", CLS1_GetStdio()->stdOut);
    LED1_On();
    WAIT1_Waitms(1000);
  } /* for */
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
#if 0
  for(;;) {
    CLS1_SendStr("Hello World!\r\n", CLS1_GetStdio()->stdOut);
    WAIT1_Waitms(1000);
  }
#elif 0
  ReadText();
#elif 1
  Test();
#elif 1
  Shell();
#endif
  /* For example: for(;;) { } */

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

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

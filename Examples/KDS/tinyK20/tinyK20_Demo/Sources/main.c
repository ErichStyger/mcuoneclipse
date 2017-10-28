/* ###################################################################
**     Filename    : main.c
**     Project     : tinyK20_Demo
**     Processor   : MK20DX128VFT5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-06-19, 16:16, # CodeGen: 0
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
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#include "FAT1.h"
#include "SD1.h"
#include "SS1.h"
#include "CD1.h"
#include "TmDt1.h"
#include "RTC1.h"
#include "SM1.h"
#include "SMasterLdd1.h"
#include "TMOUT1.h"
#include "CS1.h"
#include "USB1.h"
#include "USB0.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "CLS1.h"
#include "HF1.h"
#include "KIN1.h"
#include "PTC.h"
#include "MINI1.h"
#include "SYS1.h"
#include "RTT1.h"
#include "XF1.h"
#include "MCUC1.h"
#include "OW1.h"
#include "DQ1.h"
#include "BitIoLdd5.h"
#include "InputRB1.h"
#include "DbgRd1.h"
#include "BitIoLdd6.h"
#include "DS1.h"
#include "TGT_SWD_OE.h"
#include "BitIoLdd8.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Application.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
uint8_t crc;
uint8_t data[] = {0x28, 0x87, 0x99, 0x37, 0x09, 0x00, 0x00};

static void delay(void) {
    __asm (
        "mov r0, #0xf00  \n" /* build address 0xfe5 */
        "add r0, #0xe5   \n"
        "blx r0          \n" /* jump to code disabling the watchdog at 0xfe5 */
        "mov r1, #0x2    \n"
      "Loop1:            \n"
        "mov r0, #0x20   \n"
      "Loop2:            \n"
        "subs r0, #1     \n"
        "nop             \n"
        "cmp r0, #0      \n"
        "bgt Loop2       \n"
        "subs r1, #1     \n"
        "bgt Loop1       \n"
#if 1
        /* jump to startup code */
        "mov r0, #0x600  \n" /* _startup is at 0x625 */
        "add r0, #0x25   \n" /* 0x25 because of thumb bit */
        "bx  r0          \n" /* jump! */
#else
        "bx lr           \n"
#endif
        "nop \n" /* make sure things are properly aligned */
        );
}

static const uint8_t delay_code[] = {
    0x4F,0xF4,0x70,0x60,  /* mov.w r0, #0xf00   */
    0x00,0xf1,0xe5,0x00,  /* add.w r0, #0xe5    */
    0x80,0x47,            /* blx r0             */
    0x4F,0xF0,0x02,0x01,  /* mov.w r1, #2       */
    0x4f,0xf4,0x20,0x00,  /* mov.w r0, #0x20    */
    0x01,0x38,            /* subs 50, #1        */
    0x00,0xBF,            /* nop                */
    0x00,0x28,            /* cmp r0, #0         */
    0x3F,0xF7,0xFB,0xAF,  /* bgt.w Loop2        */
    0x01,0x39,            /* subs r1, #1        */
    0x3F,0xF7,0xF6,0xAF,  /* bgt.w Loop1        */
#if 1
    /* jump to startup code */
    0x4f,0xf4,0xc0,0x60,  /* move.w 50, #0x600  */
    0x00,0xf1,0x25,0x00,  /* add.w r0, #0x25    */
    0x00,0x47,            /* bx r0              */
#else
    0x70,0x47             /* bx lr              */
#endif
    0x00,0xBF,            /* nop                */
};

void (*f)(void);

int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  int i;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
#if 1
  f =  (void(*)(void))(&delay_code[0]);
  f();
  delay();

  crc = OW1_CalcCRC(&data[0], sizeof(data));
#endif
  for(i=0;i<15;i++) { /* blink to indicate power up */
    LED1_Neg();
    WAIT1_Waitms(20);
  }
  APP_Run(); /* should not return */
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

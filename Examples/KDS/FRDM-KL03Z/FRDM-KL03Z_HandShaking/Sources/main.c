/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM-KL03Z_LED
**     Processor   : MKL03Z32VFK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-07-03, 15:44, # CodeGen: 0
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
#include "clockMan1.h"
#include "pin_init.h"
#include "osa1.h"
#include "WAIT1.h"
#include "MCUC1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "KIN1.h"
#include "UTIL1.h"
#include "SW2.h"
#include "SW3.h"
#include "RX_RDY.h"
#include "DATA_RDY.h"
#include "DATA.h"
#include "GI2C1.h"
#include "I2C1.h"
#include "SDA1.h"
#include "SCL1.h"
#include "MMA1.h"
#include "gpio1.h"
#if CPU_INIT_CONFIG
  #include "Init_Config.h"
#endif
/* User includes (#include below this line is not maintained by Processor Expert) */

#define CONFIG_I_AM_SENDER   (0)

#if CONFIG_I_AM_SENDER
static bool SW2_Pressed(void) {
  if (!SW2_GetVal()) { /* pressed */
	  WAIT1_Waitms(100); /* simple debound */
	  if (!SW2_GetVal()) { /* still pressed */
		  while(!SW2_GetVal()) {
			  /* wait for release */
		  }
		  return true; /* pressed */
	  }
  }
  return false; /* not pressed */
}

static bool SW3_Pressed(void) {
  if (!SW3_GetVal()) { /* pressed */
	  WAIT1_Waitms(100); /* simple debound */
	  if (!SW3_GetVal()) { /* still pressed */
		  while(!SW3_GetVal()) {
			  /* wait for release */
		  }
		  return true; /* pressed */
	  }
  }
  return false; /* not pressed */
}

static void sendData(bool data) {
#if 1
  while(!RX_RDY_GetVal()) { /* wait until receiver is ready */
    WAIT1_Waitms(1);
  }
  DATA_PutVal(data); /* put data on bus */
  WAIT1_Waitms(2);
  DATA_RDY_SetVal(); /* indicate to receiver that data is valid */
  WAIT1_Waitms(2);
  while(RX_RDY_GetVal()) { /* wait until receiver has received data */
    WAIT1_Waitms(1);
  }
  DATA_RDY_ClrVal(); /* de-assert */
#else
  /* \todo send data */
#endif
}

static void sender(void) {
	int32_t cntr = 0;

	RX_RDY_SetInput(); /* set as input pin */
	DATA_RDY_ClrVal(); /* signal is HIGH active, set it initially to LOW */
	DATA_RDY_SetOutput(); /* set as output pin */

	DATA_ClrVal();
	DATA_SetOutput();
	LED1_On(); /* red on */
	for(;;) {
	  /* handle push buttons */
	  if (SW2_Pressed()) { /* change LED color */
		  /* toggle between red and blue */
		  if (LED1_Get()) { /* red is on */
			  LED2_On(); /* blue on */
			  LED1_Off(); /* red off */
		  } else {
			  LED1_On(); /* red on */
			  LED2_Off(); /* blue off */
		  }
	  }
	  if (SW3_Pressed()) {
		  if (LED1_Get()) {
			sendData(true); /* red is on ==> 1 */
		  } else {
			sendData(false); /* blue is on ==> 0 */
		  }
	  }
	  cntr++;
	  if (cntr>=100) {
		cntr = 0;
	    LED3_On();
	    WAIT1_Waitms(20);
	    LED3_Off();
	  }
	  WAIT1_Waitms(10);
	}
}
#else
static void receiver(void) {
	bool data;

	RX_RDY_ClrVal(); /* is high active */
	RX_RDY_SetOutput(); /* set as output pin */

	DATA_RDY_ClrVal(); /* is high active */
	DATA_RDY_SetInput(); /* listen on that signal */

	DATA_ClrVal(); /* default value */
	DATA_SetInput(); /* we read from the data line */

	for(;;) {
#if 1
		RX_RDY_SetVal(); /* signal that we are ready */
		while(!DATA_RDY_GetVal()) {
			/* wait until data is ready */
		    WAIT1_Waitms(1);
		}
		data = DATA_GetVal(); /* read data from bus */
		RX_RDY_ClrVal(); /* de-assert ready signal */
		while(DATA_RDY_GetVal()) {
			/* wait until sender de-assert signal */
		    WAIT1_Waitms(1);
		}
		/* show data value with the LED */
		if (data) { /* received a 1 ==> red */
			LED1_On(); /* blink red */
			WAIT1_Waitms(100);
			LED1_Off();
		} else { /* received a 0 ==> blue */
			LED2_On(); /* blink blue */
			WAIT1_Waitms(100);
			LED2_Off();
		}
#else
		/* \todo Receive data and signal it with the LED */
#endif
	}
}
#endif /* CONFIG_I_AM_SENDER */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int16_t x, y, z;
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  MMA1_WriteReg8(0x2C, 0x01); // configure accelerometer interrupt pin to open drain!

#if CONFIG_I_AM_SENDER
  sender();
#else
  receiver();
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

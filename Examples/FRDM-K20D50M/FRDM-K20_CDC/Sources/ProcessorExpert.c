/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MK20DN128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-04-27, 13:13, # CodeGen: 0
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
** @date 2013-04-27, 13:13, # CodeGen: 0
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
#include "UTIL1.h"
#include "LEDR.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LEDG.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LEDB.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "WAIT1.h"
#include "USB1.h"
#include "USB0.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#define BSP_CLOCK_SRC   (8000000ul)     /* crystal, oscillator freq. */
#define BSP_REF_CLOCK_SRC   (2000000ul)     /* must be 2-4MHz */
#define BSP_REF_CLOCK_DIV   (BSP_CLOCK_SRC / BSP_REF_CLOCK_SRC)

  #define BSP_CORE_DIV    (1)
  #define BSP_BUS_DIV     (1)
  #define BSP_FLEXBUS_DIV (1)
  #define BSP_FLASH_DIV   (2)
  // BSP_CLOCK_MUL from interval 24 - 55
  #define BSP_CLOCK_MUL   (24)    // 48MHz

static int pll_init(
    )
{

    /* 
     * First move to FBE mode
     * Enable external oscillator, RANGE=0, HGO=, EREFS=, LP=, IRCS=
    */
  #if ((defined MCU_MK60N512VMD100) || (defined MCU_MK53N512CMD100))
    MCG_C2 = 0;
  #else
    #if(defined MCU_MK20D5) || (defined MCU_MK20D7) || (defined MCU_MK40D7)
      MCG_C2 = MCG_C2_RANGE0(2) | /*MCG_C2_HGO0_MASK |*/ MCG_C2_EREFS0_MASK | MCG_C2_IRCS_MASK;
    #else
      MCG_C2 = MCG_C2_RANGE(2) | MCG_C2_HGO_MASK | MCG_C2_EREFS_MASK|MCG_C2_IRCS_MASK;
    #endif
  #endif

    /* Select external oscillator and Reference Divider and clear IREFS 
     * to start external oscillator
     * CLKS = 2, FRDIV = 3, IREFS = 0, IRCLKEN = 0, IREFSTEN = 0
     */
    MCG_C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(3);
    
  /* Wait for oscillator to initialize */
  #if((defined MCU_MK20D5) || (defined MCU_MK20D7) || (defined MCU_MK40D7))
    while (!(MCG_S & MCG_S_OSCINIT0_MASK)){};
  #elif defined (MCU_MK40N512VMD100)
    while (!(MCG_S & MCG_S_OSCINIT_MASK)){};
  #endif    
      
  #ifndef MCU_MK20D5
      /* Wait for Reference Clock Status bit to clear */
      while (MCG_S & MCG_S_IREFST_MASK) {};
  #endif
    
    /* Wait for clock status bits to show clock source 
     * is external reference clock */
    while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2) {};
    
    /* Now in FBE
     * Configure PLL Reference Divider, PLLCLKEN = 0, PLLSTEN = 0, PRDIV = 0x18
     * The crystal frequency is used to select the PRDIV value. 
     * Only even frequency crystals are supported
     * that will produce a 2MHz reference clock to the PLL.
     */
  #if(defined MCU_MK20D5) || (defined MCU_MK20D7) || (defined MCU_MK40D7)
      MCG_C5 = MCG_C5_PRDIV0(BSP_REF_CLOCK_DIV - 1) | MCG_C5_PLLCLKEN0_MASK;
  #else
      MCG_C5 = MCG_C5_PRDIV(BSP_REF_CLOCK_DIV - 1);
  #endif
      
    /* Ensure MCG_C6 is at the reset default of 0. LOLIE disabled, 
     * PLL disabled, clock monitor disabled, PLL VCO divider is clear
     */
    MCG_C6 = 0;

    
    /* Calculate mask for System Clock Divider Register 1 SIM_CLKDIV1 */
  #if (defined MCU_MK20D5) || (defined MCU_MK40D7)
    SIM_CLKDIV1 =   SIM_CLKDIV1_OUTDIV1(BSP_CORE_DIV - 1) |   /* core/system clock */
            SIM_CLKDIV1_OUTDIV2(BSP_BUS_DIV - 1)  |   /* peripheral clock; */
            SIM_CLKDIV1_OUTDIV4(BSP_FLASH_DIV - 1);     /* flash clock */
  #else    
    SIM_CLKDIV1 =   SIM_CLKDIV1_OUTDIV1(BSP_CORE_DIV    - 1) |
            SIM_CLKDIV1_OUTDIV2(BSP_BUS_DIV     - 1) |
            SIM_CLKDIV1_OUTDIV3(BSP_FLEXBUS_DIV - 1) |
            SIM_CLKDIV1_OUTDIV4(BSP_FLASH_DIV   - 1);
  #endif
    
   /* Set the VCO divider and enable the PLL, 
     * LOLIE = 0, PLLS = 1, CME = 0, VDIV = 2MHz * BSP_CLOCK_MUL
     */
  #if(defined MCU_MK20D5) || (defined MCU_MK20D7) || (defined MCU_MK40D7)
    MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV0(BSP_CLOCK_MUL - 24);
  #else
    MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(BSP_CLOCK_MUL - 24);
  #endif
    
    /* Wait for PLL status bit to set */
    while (!(MCG_S & MCG_S_PLLST_MASK)) {};
    
    /* Wait for LOCK bit to set */
  #if(defined MCU_MK20D5) || (defined MCU_MK20D7) || (defined MCU_MK40D7)
    while (!(MCG_S & MCG_S_LOCK0_MASK)){};  
  #else    
    while (!(MCG_S & MCG_S_LOCK_MASK)) {};
  #endif
    
    /* Now running PBE Mode */

    /* Transition into PEE by setting CLKS to 0
     * CLKS=0, FRDIV=3, IREFS=0, IRCLKEN=0, IREFSTEN=0
     */
    MCG_C1 &= ~MCG_C1_CLKS_MASK;

    /* Wait for clock status bits to update */
    while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3) {};

  #if(defined MCU_MK20D5)
      /* Enable the ER clock of oscillators */
      OSC0_CR = OSC_CR_ERCLKEN_MASK | OSC_CR_EREFSTEN_MASK;    
  #else
      /* Enable the ER clock of oscillators */
      OSC_CR = OSC_CR_ERCLKEN_MASK | OSC_CR_EREFSTEN_MASK;       
    #endif
    
    /* Now running PEE Mode */
    return 0;
}


static uint8_t cdc_buffer[USB1_DATA_BUFF_SIZE];
static uint8_t in_buffer[USB1_DATA_BUFF_SIZE];

static void CDC_Run(void) {
  int i;
  uint32_t val = 0;
  unsigned char buf[16];

  for(;;) {
    while(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer))==ERR_BUSOFF) {
      /* device not enumerated */
      LEDR_Neg(); LEDG_Off();
      WAIT1_Waitms(10);
    }
    LEDR_Off(); LEDG_Neg();
    if (CDC1_GetCharsInRxBuf()!=0) {
      i = 0;
      while(   i<sizeof(in_buffer)-1
            && CDC1_GetChar(&in_buffer[i])==ERR_OK
           )
      {
        i++;
      }
      in_buffer[i] = '\0';
      (void)CDC1_SendString((unsigned char*)"echo: ");
      (void)CDC1_SendString(in_buffer);
      UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"val: ");
      UTIL1_strcatNum32u(buf, sizeof(buf), val);
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
      (void)CDC1_SendString(buf);
      val++;
    } else {
      WAIT1_Waitms(10);
    }
  }
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  pll_init();
  CDC_Run();

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
**     This file was created by Processor Expert 10.0.12 [05.05]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

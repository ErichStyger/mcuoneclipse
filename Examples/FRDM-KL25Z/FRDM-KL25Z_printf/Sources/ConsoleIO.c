/** ###################################################################
**     Filename    : CsIO1.c
**     Processor   : MKL25Z128VLK4
**     Component   : ConsoleIO
**     Version     : Component 01.001, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Abstract    :
**         This component generates low-level methods for redirecting console I/O to the selected UART.
**         These methods are typically used by printf()/scanf() methods.
**
**     Copyright : 1997 - 2012 Freescale Semiconductor, Inc. All Rights Reserved.
**
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#include "derivative.h"
#include "stdio.h"
#include <stdarg.h>
#include "UART0_PDD.h"
/*
** ===================================================================
**     Method      :  __read_console
**
** ===================================================================
*/
int __read_console(__file_handle handle, unsigned char* buffer, size_t * count)
{
  size_t CharCnt = 0x00;

  (void)handle;                        /* Parameter is not used, suppress unused argument warning */
  for (;*count > 0x00; --*count) {
    /* Clear error flags */
    UART0_PDD_ClearInterruptFlags(UART0_BASE_PTR,0x1FU);
    if ((UART0_PDD_ReadInterruptStatusReg(UART0_BASE_PTR) & UART0_S1_RDRF_MASK) == 0x00) { /* Any data in receiver buffer */
      if (CharCnt != 0x00) {           /* No, at least one char received? */
        break;                         /* Yes, return received char(s) */
      } else {                         /* Wait until a char is received */
        while ((UART0_PDD_ReadInterruptStatusReg(UART0_BASE_PTR) & UART0_S1_RDRF_MASK) == 0x00) {};
      }
    }
    CharCnt++;                         /* Increase char counter */
    /* Save character received by UARTx device into the receive buffer */
    *buffer = (unsigned char)UART0_PDD_GetChar8(UART0_BASE_PTR);
    /* Stop reading if CR (Ox0D) character is received */
    if (*buffer == 0x0DU) {            /* New line character (CR) received ? */
      *buffer = '\n';                  /* Yes, convert LF to '\n' char. */
      break;                           /* Stop loop and return received char(s) */
    }
    buffer++;                          /* Increase buffer pointer */
  }
  *count = CharCnt;
  return (__no_io_error);
}

/*
** ===================================================================
**     Method      :  CsIO1___write_console (component ConsoleIO)
**
**     Description :
**         __write_console
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
int __write_console(__file_handle handle, unsigned char* buffer, size_t* count)
{
  size_t CharCnt = 0x00;

  (void)handle;                        /* Parameter is not used, suppress unused argument warning */
  for (;*count > 0x00; --*count) {
    /* Wait until UART is ready for saving a next character into the transmit buffer */
    while ((UART0_PDD_ReadInterruptStatusReg(UART0_BASE_PTR) & UART0_S1_TDRE_MASK) == 0) {};
    if (*buffer == '\n') {
      /* Send '\r'(0x0D) before each '\n'(0x0A). */
      /* Save a character into the transmit buffer of the UART0 device */
      UART0_PDD_PutChar8(UART0_BASE_PTR, 0x0DU);
      /* Wait until UART is ready for saving a next character into the transmit buffer */
      while ((UART0_PDD_ReadInterruptStatusReg(UART0_BASE_PTR) & UART0_S1_TDRE_MASK) == 0) {};
    }
    /* Save a character into the transmit buffer of the UART0 device */
    UART0_PDD_PutChar8(UART0_BASE_PTR, (unsigned char)*buffer);
    buffer++;                          /* Increase buffer pointer */
    CharCnt++;                         /* Increase char counter */
  }
  *count = CharCnt;
  return(__no_io_error);
}

/*
** ===================================================================
**     Method      :  CsIO1___close_console (component ConsoleIO)
**
**     Description :
**         __close_console
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
int __close_console(__file_handle handle)
{
  (void)handle;                        /* Parameter is not used, suppress unused argument warning */
  return(__no_io_error);
}

/*
** ===================================================================
**     Method      :  InitClock
**
** ===================================================================
*/
static void InitClock()
{
	/* System clock initialization */
	/* SIM_SCGC5: PORTC=1,PORTA=1 */
	SIM_SCGC5 |= (SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTA_MASK); /* Enable clock gate for ports to enable pin routing */
	/* SIM_CLKDIV1: OUTDIV1=1,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,OUTDIV4=1,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
	SIM_CLKDIV1 = (SIM_CLKDIV1_OUTDIV1(0x01) | SIM_CLKDIV1_OUTDIV4(0x01)); /* Update system prescalers */
	/* SIM_SOPT2: PLLFLLSEL=1 */
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; /* Select PLL as a clock source for various peripherals */
	/* SIM_SOPT1: OSC32KSEL=0 */
	SIM_SOPT1 &= (uint32_t)~(uint32_t)(SIM_SOPT1_OSC32KSEL(0x03)); /* System oscillator drives 32 kHz clock for various peripherals */
	/* SIM_SOPT2: TPMSRC=1 */
	SIM_SOPT2 = (uint32_t)((SIM_SOPT2 & (uint32_t)~(uint32_t)(
			   SIM_SOPT2_TPMSRC(0x02)
			  )) | (uint32_t)(
			   SIM_SOPT2_TPMSRC(0x01)
			  ));                      /* Set the TPM clock */
	/* PORTA_PCR18: ISF=0,MUX=0 */
	PORTA_PCR18 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));                                                   
	/* PORTA_PCR19: ISF=0,MUX=0 */
	PORTA_PCR19 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));                                                   
	/* Switch to FBE Mode */
	/* OSC0_CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
	OSC0_CR = OSC_CR_ERCLKEN_MASK;                                                   
	/* MCG_C2: LOCRE0=0,??=0,RANGE0=2,HGO0=0,EREFS0=1,LP=0,IRCS=0 */
	MCG_C2 = (MCG_C2_RANGE0(0x02) | MCG_C2_EREFS0_MASK);                                                   
	/* MCG_C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
	MCG_C1 = (MCG_C1_CLKS(0x02) | MCG_C1_FRDIV(0x03) | MCG_C1_IRCLKEN_MASK);                                                   
	/* MCG_C4: DMX32=0,DRST_DRS=0 */
	MCG_C4 &= (uint8_t)~(uint8_t)((MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS(0x03)));                                                   
	/* MCG_C5: ??=0,PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=1 */
	MCG_C5 = MCG_C5_PRDIV0(0x01);                                                   
	/* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
	MCG_C6 = 0x00U;                                                   
	while((MCG_S & MCG_S_IREFST_MASK) != 0x00U) { /* Check that the source of the FLL reference clock is the external reference clock. */
	}
	while((MCG_S & 0x0CU) != 0x08U) {    /* Wait until external reference clock is selected as MCG output */
	}
	/* Switch to PBE Mode */
	/* OSC0_CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
	OSC0_CR = OSC_CR_ERCLKEN_MASK;                                                   
	/* MCG_C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
	MCG_C1 = (MCG_C1_CLKS(0x02) | MCG_C1_FRDIV(0x03) | MCG_C1_IRCLKEN_MASK);                                                   
	/* MCG_C2: LOCRE0=0,??=0,RANGE0=2,HGO0=0,EREFS0=1,LP=0,IRCS=0 */
	MCG_C2 = (MCG_C2_RANGE0(0x02) | MCG_C2_EREFS0_MASK);                                                   
	/* MCG_C5: ??=0,PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=1 */
	MCG_C5 = MCG_C5_PRDIV0(0x01);                                                   
	/* MCG_C6: LOLIE0=0,PLLS=1,CME0=0,VDIV0=0 */
	MCG_C6 = MCG_C6_PLLS_MASK;                                                   
	while((MCG_S & 0x0CU) != 0x08U) {    /* Wait until external reference clock is selected as MCG output */
	}
	while((MCG_S & MCG_S_LOCK0_MASK) == 0x00U) { /* Wait until locked */
	}
	/* Switch to PEE Mode */
	/* OSC0_CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
	OSC0_CR = OSC_CR_ERCLKEN_MASK;                                                   
	/* MCG_C1: CLKS=0,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
	MCG_C1 = (MCG_C1_FRDIV(0x03) | MCG_C1_IRCLKEN_MASK);                                                   
	/* MCG_C2: LOCRE0=0,??=0,RANGE0=2,HGO0=0,EREFS0=1,LP=0,IRCS=0 */
	MCG_C2 = (MCG_C2_RANGE0(0x02) | MCG_C2_EREFS0_MASK);                                                   
	/* MCG_C5: ??=0,PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=1 */
	MCG_C5 = MCG_C5_PRDIV0(0x01);                                                   
	/* MCG_C6: LOLIE0=0,PLLS=1,CME0=0,VDIV0=0 */
	MCG_C6 = MCG_C6_PLLS_MASK;                                                   
	while((MCG_S & 0x0CU) != 0x0CU) {    /* Wait until output of the PLL is selected */
	}
	/* Initialization of the RTC_CLKIN pin */
	/* PORTC_PCR1: ISF=0,MUX=1 */
	PORTC_PCR1 = (uint32_t)((PORTC_PCR1 & (uint32_t)~(uint32_t)(
				PORT_PCR_ISF_MASK |
				PORT_PCR_MUX(0x06)
			   )) | (uint32_t)(
				PORT_PCR_MUX(0x01)
			   )); 
}

/*
** ===================================================================
**     Method      :  ConsoleIO_Init
**
** ===================================================================
*/
void ConsoleIO_Init()
{
	InitClock();

	/* SIM_SCGC4: UART0=1 */
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK; 
#if 0 /* TWR version: PTA14, PTA15 */
	/* PORTA_PCR15: ISF=0,MUX=3 */
	PORTA_PCR15 = (uint32_t)((PORTA_PCR15 & (uint32_t)~(uint32_t)(
				 PORT_PCR_ISF_MASK |
				 PORT_PCR_MUX(0x04)
				)) | (uint32_t)(
				 PORT_PCR_MUX(0x03)
				));                                                  
	/* PORTA_PCR14: ISF=0,MUX=3 */
	PORTA_PCR14 = (uint32_t)((PORTA_PCR14 & (uint32_t)~(uint32_t)(
				 PORT_PCR_ISF_MASK |
				 PORT_PCR_MUX(0x04)
				)) | (uint32_t)(
				 PORT_PCR_MUX(0x03)
				));           
#else /* FRDM-KL25Z: PTA1/PTA2 */
	  /* PORTA_PCR1: ISF=0,MUX=2 */
	  PORTA_PCR1 = (uint32_t)((PORTA_PCR1 & (uint32_t)~0x01000500UL) | (uint32_t)0x0200UL);
	  /* PORTA_PCR2: ISF=0,MUX=2 */
	  PORTA_PCR2 = (uint32_t)((PORTA_PCR2 & (uint32_t)~0x01000500UL) | (uint32_t)0x0200UL);
#endif
	UART0_PDD_EnableTransmitter(UART0_BASE_PTR, PDD_DISABLE); /* Disable transmitter. */
	UART0_PDD_EnableReceiver(UART0_BASE_PTR, PDD_DISABLE); /* Disable receiver. */
	/* UART0_C1: LOOPS=0,DOZEEN=0,RSRC=0,M=0,WAKE=0,ILT=0,PE=0,PT=0 */
	UART0_C1 = 0x00U;                    /*  Set the C1 register */
	/* UART0_C3: R8T9=0,R9T8=0,TXDIR=0,TXINV=0,ORIE=0,NEIE=0,FEIE=0,PEIE=0 */
	UART0_C3 = 0x00U;                    /*  Set the C3 register */
	/* UART0_S2: LBKDIF=0,RXEDGIF=0,MSBF=0,RXINV=0,RWUID=0,BRK13=0,LBKDE=0,RAF=0 */
	UART0_S2 = 0x00U;                    /*  Set the S2 register */
	UART0_PDD_SetClockSource(UART0_BASE_PTR, UART0_PDD_PLL_FLL_CLOCK);
	UART0_PDD_SetBaudRate(UART0_BASE_PTR, 313U); /* Set the baud rate register. */
	UART0_PDD_SetOversamplingRatio(UART0_BASE_PTR, 3U);
	UART0_PDD_EnableSamplingOnBothEdges(UART0_BASE_PTR, PDD_ENABLE);
	UART0_PDD_EnableTransmitter(UART0_BASE_PTR, PDD_ENABLE); /* Enable transmitter */
	UART0_PDD_EnableReceiver(UART0_BASE_PTR, PDD_ENABLE); /* Enable receiver */
}

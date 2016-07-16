/**
 * \file system_MK20D5.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 17.11.2015
 * \brief Low level mcu initialization
 *
 */

#include "MK20D5.h"
#include "system_MK20D5.h"

void Cpu_SetBASEPRI( uint32_t Level );

/*********************** Default ISR handlers ***********************/
Default_ISR(NMI_Handler) {_DEBUGHALT();}
Default_ISR(HardFault_Handler) {_DEBUGHALT();}
Default_ISR(MemManage_Handler) {_DEBUGHALT();}
Default_ISR(BusFault_Handler) {_DEBUGHALT();}
Default_ISR(UsageFault_Handler) {_DEBUGHALT();}
Default_ISR(SysTick_Handler) {_DEBUGHALT();}
Default_ISR(DMA0_IRQHandler) {_DEBUGHALT();}
Default_ISR(DMA1_IRQHandler) {_DEBUGHALT();}
Default_ISR(DMA2_IRQHandler) {_DEBUGHALT();}
Default_ISR(DMA3_IRQHandler) {_DEBUGHALT();}
Default_ISR(DMA_Error_IRQHandler) {_DEBUGHALT();}
Default_ISR(Reserved21_IRQHandler) {_DEBUGHALT();}
Default_ISR(FTF_IRQHandler) {_DEBUGHALT();}
Default_ISR(Read_Collision_IRQHandler) {_DEBUGHALT();}
Default_ISR(LVD_LVW_IRQHandler) {_DEBUGHALT();}
Default_ISR(LLWU_IRQHandler) {_DEBUGHALT();}
Default_ISR(WDOG_IRQHandler) {_DEBUGHALT();}
Default_ISR(I2C0_IRQHandler) {_DEBUGHALT();}
Default_ISR(SPI0_IRQHandler) {_DEBUGHALT();}
Default_ISR(I2S0_Tx_IRQHandler) {_DEBUGHALT();}
Default_ISR(I2S0_Rx_IRQHandler) {_DEBUGHALT();}
Default_ISR(UART0_LON_IRQHandler) {_DEBUGHALT();}
Default_ISR(UART0_RX_TX_IRQHandler) {_DEBUGHALT();}
Default_ISR(UART0_ERR_IRQHandler) {_DEBUGHALT();}
Default_ISR(UART1_RX_TX_IRQHandler) {_DEBUGHALT();}
Default_ISR(UART1_ERR_IRQHandler) {_DEBUGHALT();}
Default_ISR(UART2_RX_TX_IRQHandler) {_DEBUGHALT();}
Default_ISR(UART2_ERR_IRQHandler) {_DEBUGHALT();}
Default_ISR(ADC0_IRQHandler) {_DEBUGHALT();}
Default_ISR(CMP0_IRQHandler) {_DEBUGHALT();}
Default_ISR(CMP1_IRQHandler) {_DEBUGHALT();}
Default_ISR(FTM0_IRQHandler) {_DEBUGHALT();}
Default_ISR(FTM1_IRQHandler) {_DEBUGHALT();}
Default_ISR(CMT_IRQHandler) {_DEBUGHALT();}
Default_ISR(RTC_IRQHandler) {_DEBUGHALT();}
Default_ISR(RTC_Seconds_IRQHandler) {_DEBUGHALT();}
Default_ISR(PIT0_IRQHandler) {_DEBUGHALT();}
Default_ISR(PIT1_IRQHandler) {_DEBUGHALT();}
Default_ISR(PIT2_IRQHandler) {_DEBUGHALT();}
Default_ISR(PIT3_IRQHandler) {_DEBUGHALT();}
Default_ISR(PDB0_IRQHandler) {_DEBUGHALT();}
Default_ISR(USB0_IRQHandler) {_DEBUGHALT();}
Default_ISR(USBCDC_IRQHandler) {_DEBUGHALT();}
Default_ISR(TSI0_IRQHandler) {_DEBUGHALT();}
Default_ISR(MCG_IRQHandler) {_DEBUGHALT();}
Default_ISR(LPTMR0_IRQHandler) {_DEBUGHALT();}
Default_ISR(PORTA_IRQHandler) {_DEBUGHALT();}
Default_ISR(PORTB_IRQHandler) {_DEBUGHALT();}
Default_ISR(PORTC_IRQHandler) {_DEBUGHALT();}
Default_ISR(PORTD_IRQHandler) {_DEBUGHALT();}
Default_ISR(PORTE_IRQHandler) {_DEBUGHALT();}
Default_ISR(SWI_IRQHandler) {_DEBUGHALT();}

void __init_hardware( void )
{
    /*** ### MK20DX128VFT5 "Cpu" init code ... ***/
    SCB_VTOR = (uint32_t)(&__vect_table); /* Set the interrupt vector table position */
    /* SIM_SCGC6: RTC=1 */
    SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;
    if ( (RTC_CR & RTC_CR_OSCE_MASK) == 0u ) { /* Only if the OSCILLATOR is not already enabled */
        /* RTC_CR: SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
        RTC_CR &= (uint32_t) ~(uint32_t)(
                RTC_CR_SC2P_MASK | RTC_CR_SC4P_MASK | RTC_CR_SC8P_MASK | RTC_CR_SC16P_MASK);
        /* RTC_CR: OSCE=1 */
        RTC_CR |= RTC_CR_OSCE_MASK;
        /* RTC_CR: CLKO=0 */
        RTC_CR &= (uint32_t) ~(uint32_t)(RTC_CR_CLKO_MASK);
    }
    /* Disable the WDOG module */
    /* WDOG_UNLOCK: WDOGUNLOCK=0xC520 */
    WDOG_UNLOCK = WDOG_UNLOCK_WDOGUNLOCK(0xC520); /* Key 1 */
    /* WDOG_UNLOCK: WDOGUNLOCK=0xD928 */
    WDOG_UNLOCK = WDOG_UNLOCK_WDOGUNLOCK(0xD928); /* Key 2 */
    /* WDOG_STCTRLH: ??=0,DISTESTWDOG=0,BYTESEL=0,TESTSEL=0,TESTWDOG=0,??=0,??=1,WAITEN=1,STOPEN=1,DBGEN=0,ALLOWUPDATE=1,WINEN=0,IRQRSTEN=0,CLKSRC=1,WDOGEN=0 */
    WDOG_STCTRLH = WDOG_STCTRLH_BYTESEL(0x00) | WDOG_STCTRLH_WAITEN_MASK | WDOG_STCTRLH_STOPEN_MASK
            | WDOG_STCTRLH_ALLOWUPDATE_MASK | WDOG_STCTRLH_CLKSRC_MASK | 0x0100U;

    /* System clock initialization */
    /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=1,??=0,??=0,??=0,??=0,OUTDIV4=3,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
    SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0x00) | SIM_CLKDIV1_OUTDIV2(0x01) | SIM_CLKDIV1_OUTDIV4(0x03); /* Set the system prescalers to safe value */
    /* SIM_SCGC5: PORTD=1,PORTC=1,PORTA=1 */
    SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTA_MASK; /* Enable clock gate for ports to enable pin routing */
    if ( (PMC_REGSC & PMC_REGSC_ACKISO_MASK) != 0x0U ) {
        /* PMC_REGSC: ACKISO=1 */
        PMC_REGSC |= PMC_REGSC_ACKISO_MASK; /* Release IO pads after wakeup from VLLS mode. */
    }
    /* SIM_CLKDIV1: OUTDIV1=1,OUTDIV2=1,??=0,??=0,??=0,??=0,OUTDIV4=3,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
    SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0x01) | SIM_CLKDIV1_OUTDIV2(0x01) | SIM_CLKDIV1_OUTDIV4(0x03); /* Update system prescalers */
    /* SIM_SOPT2: PLLFLLSEL=1 */
    SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; /* Select PLL as a clock source for various peripherals */
    /* SIM_SOPT1: OSC32KSEL=2 */
    SIM_SOPT1 = (uint32_t)(
            (SIM_SOPT1 & (uint32_t) ~(uint32_t)(SIM_SOPT1_OSC32KSEL(0x01)))
                    | (uint32_t)(SIM_SOPT1_OSC32KSEL(0x02))); /* System oscillator drives 32 kHz clock for various peripherals */
    /* PORTA_PCR18: ISF=0,MUX=0 */
    PORTA_PCR18 &= (uint32_t) ~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
    /* PORTA_PCR19: ISF=0,MUX=0 */
    PORTA_PCR19 &= (uint32_t) ~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
    /* MCG_SC: FCRDIV=1 */
    MCG_SC = (uint8_t)(
            (MCG_SC & (uint8_t) ~(uint8_t)(MCG_SC_FCRDIV(0x06))) | (uint8_t)(MCG_SC_FCRDIV(0x01)));
    /* Switch to FBE Mode */
    /* MCG_C2: LOCRE0=0,??=0,RANGE0=2,HGO0=0,EREFS0=1,LP=0,IRCS=1 */
    MCG_C2 = (MCG_C2_RANGE0(0x02) | MCG_C2_EREFS0_MASK | MCG_C2_IRCS_MASK);
    /* OSC0_CR: ERCLKEN=1,??=0,EREFSTEN=1,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
    OSC0_CR = (OSC_CR_ERCLKEN_MASK | OSC_CR_EREFSTEN_MASK);
    /* MCG_C7: OSCSEL=0 */
    MCG_C7 &= (uint8_t) ~(uint8_t)(MCG_C7_OSCSEL_MASK);
    /* MCG_C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=1 */
    MCG_C1 = MCG_C1_CLKS(0x02) | MCG_C1_FRDIV(0x03) | MCG_C1_IRCLKEN_MASK | MCG_C1_IREFSTEN_MASK;
    /* MCG_C4: DMX32=0,DRST_DRS=0 */
    MCG_C4 &= (uint8_t) ~(uint8_t)((MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS(0x03)));
    /* MCG_C5: ??=0,PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=1 */
    MCG_C5 = MCG_C5_PRDIV0(0x01);
    /* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
    MCG_C6 = MCG_C6_VDIV0(0x00);
    while ( (MCG_S & MCG_S_OSCINIT0_MASK) == 0x00U ) { /* Check that the oscillator is running */
    }
    while ( (MCG_S & MCG_S_IREFST_MASK) != 0x00U ) { /* Check that the source of the FLL reference clock is the external reference clock. */
    }
    while ( (MCG_S & 0x0CU) != 0x08U ) { /* Wait until external reference clock is selected as MCG output */
    }
    /* Switch to PBE Mode */
    /* MCG_C6: LOLIE0=0,PLLS=1,CME0=0,VDIV0=0 */
    MCG_C6 = (MCG_C6_PLLS_MASK | MCG_C6_VDIV0(0x00));
    while ( (MCG_S & 0x0CU) != 0x08U ) { /* Wait until external reference clock is selected as MCG output */
    }
    while ( (MCG_S & MCG_S_LOCK0_MASK) == 0x00U ) { /* Wait until locked */
    }
    /* Switch to PEE Mode */
    /* MCG_C1: CLKS=0,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=1 */
    MCG_C1 = MCG_C1_CLKS(0x00) | MCG_C1_FRDIV(0x03) | MCG_C1_IRCLKEN_MASK | MCG_C1_IREFSTEN_MASK;
    while ( (MCG_S & 0x0CU) != 0x0CU ) { /* Wait until output of the PLL is selected */
    }

}

#ifdef _lint
#define Cpu_SetBASEPRI(Level)  /* empty */
#else
void Cpu_SetBASEPRI( uint32_t Level )
{
    __asm ("msr basepri, %[input]"::[input] "r" (Level):);
}
#endif

void low_level_init( void )
{
    /* Initialization of the SIM module */
    /* Initialization of the RCM module */
    /* RCM_RPFW: RSTFLTSEL=0 */
    RCM_RPFW &= (uint8_t) ~(uint8_t)(RCM_RPFW_RSTFLTSEL(0x1F));
    /* RCM_RPFC: RSTFLTSS=0,RSTFLTSRW=0 */
    RCM_RPFC &= (uint8_t) ~(uint8_t)(RCM_RPFC_RSTFLTSS_MASK | RCM_RPFC_RSTFLTSRW(0x03));
    /* Initialization of the FTFL_FlashConfig module */
    /* Initialization of the PMC module */
    /* PMC_REGSC: ACKISO=0,BGBE=1 */
    PMC_REGSC = (uint8_t)(
            (PMC_REGSC & (uint8_t) ~(uint8_t)(PMC_REGSC_ACKISO_MASK))
                    | (uint8_t)(PMC_REGSC_BGBE_MASK));
    /* PMC_LVDSC1: LVDACK=1,LVDIE=0,LVDRE=1,LVDV=0 */
    PMC_LVDSC1 = (uint8_t)(
            (PMC_LVDSC1 & (uint8_t) ~(uint8_t)(PMC_LVDSC1_LVDIE_MASK | PMC_LVDSC1_LVDV(0x03)))
                    | (uint8_t)(PMC_LVDSC1_LVDACK_MASK | PMC_LVDSC1_LVDRE_MASK));
    /* PMC_LVDSC2: LVWACK=1,LVWIE=0,LVWV=0 */
    PMC_LVDSC2 = (uint8_t)(
            (PMC_LVDSC2 & (uint8_t) ~(uint8_t)(PMC_LVDSC2_LVWIE_MASK | PMC_LVDSC2_LVWV(0x03)))
                    | (uint8_t)(PMC_LVDSC2_LVWACK_MASK));
    /* Initialization of the LLWU module */
    /* LLWU_PE1: WUPE3=0 */
    LLWU_PE1 &= (uint8_t) ~(uint8_t)(LLWU_PE1_WUPE3(0x03));
    /* LLWU_PE2: WUPE7=0,WUPE6=0,WUPE5=0 */
    LLWU_PE2 &= (uint8_t) ~(uint8_t)(
            LLWU_PE2_WUPE7(0x03) | LLWU_PE2_WUPE6(0x03) | LLWU_PE2_WUPE5(0x03));
    /* LLWU_PE3: WUPE10=0,WUPE9=0,WUPE8=0 */
    LLWU_PE3 &= (uint8_t) ~(uint8_t)(
            LLWU_PE3_WUPE10(0x03) | LLWU_PE3_WUPE9(0x03) | LLWU_PE3_WUPE8(0x03));
    /* LLWU_PE4: WUPE15=0,WUPE14=0,WUPE13=0,WUPE12=0 */
    LLWU_PE4 = LLWU_PE4_WUPE15(0x00) | LLWU_PE4_WUPE14(0x00) | LLWU_PE4_WUPE13(0x00)
            | LLWU_PE4_WUPE12(0x00);
    /* LLWU_ME: WUME7=0,WUME5=0,WUME4=0,WUME2=0,WUME1=0,WUME0=1 */
    LLWU_ME = (uint8_t)(
            (LLWU_ME
                    & (uint8_t) ~(uint8_t)(
                            LLWU_ME_WUME7_MASK | LLWU_ME_WUME5_MASK | LLWU_ME_WUME4_MASK
                                    | LLWU_ME_WUME2_MASK | LLWU_ME_WUME1_MASK))
                    | (uint8_t)(LLWU_ME_WUME0_MASK));
    /* LLWU_FILT1: FILTF=1,FILTE=0,??=0,FILTSEL=0 */
    LLWU_FILT1 = LLWU_FILT1_FILTF_MASK | LLWU_FILT1_FILTE(0x00) | LLWU_FILT1_FILTSEL(0x00);
    /* LLWU_FILT2: FILTF=1,FILTE=0,??=0,FILTSEL=0 */
    LLWU_FILT2 = LLWU_FILT2_FILTF_MASK | LLWU_FILT2_FILTE(0x00) | LLWU_FILT2_FILTSEL(0x00);
    /* LLWU_RST: ??=0,??=0,??=0,??=0,??=0,??=0,LLRSTE=1,RSTFILT=0 */
    LLWU_RST = LLWU_RST_LLRSTE_MASK;
    /* SMC_PMPROT: ??=0,??=0,AVLP=1,??=0,ALLS=1,??=0,AVLLS=0,??=0 */
    SMC_PMPROT = (SMC_PMPROT_AVLP_MASK | SMC_PMPROT_ALLS_MASK); /* Setup Power mode protection register */
    /* Common initialization of the CPU registers */
    /* NVICIP8: PRI8=0 */
    NVICIP8 = NVIC_IP_PRI8(0x00); /* LVD_LVW_IRQHandler priority */
    /* NVICIP9: PRI9=0 */
    NVICIP9 = NVIC_IP_PRI9(0x00); /* LLWU_IRQHandler */
    /* Enable interrupts of the given priority level */
    Cpu_SetBASEPRI(0U);
}
/* Flash configuration field */
__attribute__ ((section (".cfmconfig"))) const uint8_t _cfm[0x10] = {
/* NV_BACKKEY3: KEY=0xFF */
0xFFU,
/* NV_BACKKEY2: KEY=0xFF */
0xFFU,
/* NV_BACKKEY1: KEY=0xFF */
0xFFU,
/* NV_BACKKEY0: KEY=0xFF */
0xFFU,
/* NV_BACKKEY7: KEY=0xFF */
0xFFU,
/* NV_BACKKEY6: KEY=0xFF */
0xFFU,
/* NV_BACKKEY5: KEY=0xFF */
0xFFU,
/* NV_BACKKEY4: KEY=0xFF */
0xFFU,
/* NV_FPROT3: PROT=0xFF */
0xFFU,
/* NV_FPROT2: PROT=0xFF */
0xFFU,
/* NV_FPROT1: PROT=0xFF */
0xFFU,
/* NV_FPROT0: PROT=0xFF */
0xFFU,
/* NV_FSEC: KEYEN=1,MEEN=3,FSLACC=3,SEC=2 */
0x7EU,
/* NV_FOPT: ??=1,??=1,??=1,??=1,??=1,NMI_DIS=0,EZPORT_DIS=0,LPBOOT=1 */
0xF9U,
/* NV_FEPROT: EPROT=0xFF */
0xFFU,
/* NV_FDPROT: DPROT=0xFF */
0xFFU };

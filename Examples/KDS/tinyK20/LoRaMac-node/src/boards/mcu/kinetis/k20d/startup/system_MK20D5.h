/**
 * \file system_MK20D5.h
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 17.11.2015
 * \brief Low level mcu initialization
 *
 */

#ifndef __SYSTEM_MK20D5_H__
#define __SYSTEM_MK20D5_H__

#include "types.h"

/* Active configuration define symbol */
#define PEcfg_FLASH 1U

/* Methods configuration constants - generated for all enabled component's methods */

/* Events configuration constants - generated for all enabled component's events */
#define Cpu_OnNMIINT_EVENT_ENABLED

#define CPU_BUS_CLK_HZ                  48000000U /* Initial value of the bus clock frequency in Hz */
#define CPU_CORE_CLK_HZ                 48000000U /* Initial value of the core/system clock frequency in Hz.  */

#define CPU_CLOCK_CONFIG_NUMBER         0x01U /* Specifies number of defined clock configurations. */

#define CPU_BUS_CLK_HZ_CLOCK_CONFIG0    48000000U /* Value of the bus clock frequency in the clock configuration 0 in Hz. */
#define CPU_CORE_CLK_HZ_CLOCK_CONFIG0   48000000U /* Value of the core/system clock frequency in the clock configuration 0 in Hz. */


#define CPU_XTAL_CLK_HZ                 8000000U /* Value of the external crystal or oscillator clock frequency in Hz */
#define CPU_XTAL32k_CLK_HZ              32768U /* Value of the external 32k crystal or oscillator clock frequency in Hz */
#define CPU_INT_SLOW_CLK_HZ             32768U /* Value of the slow internal oscillator clock frequency in Hz  */
#define CPU_INT_FAST_CLK_HZ             4000000U /* Value of the fast internal oscillator clock frequency in Hz  */

#define CPU_FAMILY_Kinetis             /* Specification of the core type of the selected cpu */
#define CPU_DERIVATIVE_MK20DX128FT5    /* Name of the selected cpu derivative */
#define CPU_PARTNUM_MK20DX128VFT5      /* Part number of the selected cpu */
#define CPU_LITTLE_ENDIAN              /* The selected cpu uses little endian */

/* CPU frequencies in clock configuration 0 */
#define CPU_CLOCK_CONFIG_0              0x00U /* Clock configuration 0 identifier */
#define CPU_CORE_CLK_HZ_CONFIG_0        48000000UL /* Core clock frequency in clock configuration 0 */
#define CPU_BUS_CLK_HZ_CONFIG_0         48000000UL /* Bus clock frequency in clock configuration 0 */
#define CPU_FLEXBUS_CLK_HZ_CONFIG_0     0UL /* Flexbus clock frequency in clock configuration 0 */
#define CPU_FLASH_CLK_HZ_CONFIG_0       24000000UL /* FLASH clock frequency in clock configuration 0 */
#define CPU_USB_CLK_HZ_CONFIG_0         0UL /* USB clock frequency in clock configuration 0 */
#define CPU_PLL_FLL_CLK_HZ_CONFIG_0     96000000UL /* PLL/FLL clock frequency in clock configuration 0 */
#define CPU_MCGIR_CLK_HZ_CONFIG_0       2000000UL /* MCG internal reference clock frequency in clock configuration 0 */
#define CPU_OSCER_CLK_HZ_CONFIG_0       8000000UL /* System OSC external reference clock frequency in clock configuration 0 */
#define CPU_ERCLK32K_CLK_HZ_CONFIG_0    32768UL /* External reference clock 32k frequency in clock configuration 0 */
#define CPU_MCGFF_CLK_HZ_CONFIG_0       31250UL /* MCG fixed frequency clock */


typedef struct  {
  uint32_t cpu_core_clk_hz;            /* Core clock frequency in clock configuration */
  uint32_t cpu_bus_clk_hz;             /* Bus clock frequency in clock configuration */
  uint32_t cpu_flexbus_clk_hz;         /* Flexbus clock frequency in clock configuration */
  uint32_t cpu_flash_clk_hz;           /* FLASH clock frequency in clock configuration */
  uint32_t cpu_usb_clk_hz;             /* USB clock frequency in clock configuration */
  uint32_t cpu_pll_fll_clk_hz;         /* PLL/FLL clock frequency in clock configuration */
  uint32_t cpu_mcgir_clk_hz;           /* MCG internal reference clock frequency in clock configuration */
  uint32_t cpu_oscer_clk_hz;           /* System OSC external reference clock frequency in clock configuration */
  uint32_t cpu_erclk32k_clk_hz;        /* External reference clock 32k frequency in clock configuration */
  uint32_t cpu_mcgff_clk_hz;           /* MCG fixed frequency clock */
} TCpuClockConfiguration;

/* The array of clock frequencies in configured clock configurations */
extern const TCpuClockConfiguration PE_CpuClockConfigurations[CPU_CLOCK_CONFIG_NUMBER];

  /* Interrupt vector table type definition */
  typedef void (*const tIsrFunc)(void);
  typedef struct {
    void * __ptr;
    tIsrFunc __fun[0x3D];
  } tVectorTable;

  extern const tVectorTable __vect_table;

/* Global variables */
/*lint -esym(765,SR_reg) Disable MISRA rule (8.10) checking for symbols (SR_reg). The SR_reg is used in inline assembler. */
extern volatile uint8_t SR_reg;        /* Current FAULTMASK register */
/*lint -esym(765,SR_lock) Disable MISRA rule (8.10) checking for symbols (SR_lock). The SR_reg is used in inline assembler. */
extern volatile uint8_t SR_lock;


/* Prototypes for interrupt service handlers */
void vPortSVCHandler(void);
void vPortPendSVHandler(void);
void vPortTickHandler(void);

/*!
 * \brief Cpu initialization.
 */
void __init_hardware(void);

/*!
 * \brief Low level peripheral initialization.
 */
void low_level_init(void);

/*********************** Default ISR handlers ***********************/
Default_ISR(NMI_Handler);
Default_ISR(HardFault_Handler);
Default_ISR(MemManage_Handler);
Default_ISR(BusFault_Handler);
Default_ISR(UsageFault_Handler);
Default_ISR(Reserved7_IRQHandler);
Default_ISR(Reserved8_IRQHandler);
Default_ISR(Reserved9_IRQHandler);
Default_ISR(Reserved10_IRQHandler);
Default_ISR(vPortSVCHandler);
Default_ISR(DebugMon_Handler);
Default_ISR(Reserved13_IRQHandler);
Default_ISR(vPortPendSVHandler);
Default_ISR(vPortTickHandler);
Default_ISR(DMA0_IRQHandler);
Default_ISR(DMA1_IRQHandler);
Default_ISR(DMA2_IRQHandler);
Default_ISR(DMA3_IRQHandler);
Default_ISR(DMA_Error_IRQHandler);
Default_ISR(Reserved21_IRQHandler);
Default_ISR(FTF_IRQHandler);
Default_ISR(Read_Collision_IRQHandler);
Default_ISR(LVD_LVW_IRQHandler);
Default_ISR(LLWU_IRQHandler);
Default_ISR(WDOG_IRQHandler);
Default_ISR(I2C0_IRQHandler);
Default_ISR(SPI0_IRQHandler);
Default_ISR(I2S0_Tx_IRQHandler);
Default_ISR(I2S0_Rx_IRQHandler);
Default_ISR(UART0_LON_IRQHandler);
Default_ISR(UART0_RX_TX_IRQHandler);
Default_ISR(UART0_ERR_IRQHandler);
Default_ISR(UART1_RX_TX_IRQHandler);
Default_ISR(UART1_ERR_IRQHandler);
Default_ISR(UART2_RX_TX_IRQHandler);
Default_ISR(UART2_ERR_IRQHandler);
Default_ISR(ADC0_IRQHandler);
Default_ISR(CMP0_IRQHandler);
Default_ISR(CMP1_IRQHandler);
Default_ISR(FTM0_IRQHandler);
Default_ISR(FTM1_IRQHandler);
Default_ISR(CMT_IRQHandler);
Default_ISR(RTC_IRQHandler);
Default_ISR(RTC_Seconds_IRQHandler);
Default_ISR(PIT0_IRQHandler);
Default_ISR(PIT1_IRQHandler);
Default_ISR(PIT2_IRQHandler);
Default_ISR(PIT3_IRQHandler);
Default_ISR(PDB0_IRQHandler);
Default_ISR(USB0_IRQHandler);
Default_ISR(USBCDC_IRQHandler);
Default_ISR(TSI0_IRQHandler);
Default_ISR(MCG_IRQHandler);
Default_ISR(LPTMR0_IRQHandler);
Default_ISR(PORTA_IRQHandler);
Default_ISR(PORTB_IRQHandler);
Default_ISR(PORTC_IRQHandler);
Default_ISR(PORTD_IRQHandler);
Default_ISR(PORTE_IRQHandler);
Default_ISR(SWI_IRQHandler);

#endif /* __SYSTEM_MK20D5_H__ */

/**
 * \file types.h
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 17.11.2015
 * \brief Type definitions
 *
 */

#ifndef __TYPES_H__
#define __TYPES_H__

/* Standard ANSI C types */
#include <stdint.h>

#ifndef FALSE
#define  FALSE  0x00u                /* Boolean value FALSE. FALSE is defined always as a zero value. */
#endif
#ifndef TRUE
#define  TRUE   0x01u                /* Boolean value TRUE. TRUE is defined always as a non zero value. */
#endif

#ifndef NULL
#define  NULL   0x00u
#endif

/* PE types definition */
#ifndef __cplusplus
#ifndef bool
typedef unsigned char bool;
#endif
#endif
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;
typedef unsigned long long dlong;
typedef unsigned char TPE_ErrCode;
#ifndef TPE_Float
typedef float TPE_Float;
#endif
#ifndef char_t
typedef char char_t;
#endif

/* Other basic data types */
typedef signed char int8;
typedef signed short int int16;
typedef signed long int int32;

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned long int uint32;

typedef enum IRQn {
    /* Auxiliary constants */
    NotAvail_IRQn = -128,               /**< Not available device specific interrupt */

    /* Core interrupts */
    NonMaskableInt_IRQn = -14,          /**< Non Maskable Interrupt */
    HardFault_IRQn = -13,               /**< Cortex-M4 SV Hard Fault Interrupt */
    MemoryManagement_IRQn = -12,        /**< Cortex-M4 Memory Management Interrupt */
    BusFault_IRQn = -11,                /**< Cortex-M4 Bus Fault Interrupt */
    UsageFault_IRQn = -10,              /**< Cortex-M4 Usage Fault Interrupt */
    SVCall_IRQn = -5,                   /**< Cortex-M4 SV Call Interrupt */
    DebugMonitor_IRQn = -4,             /**< Cortex-M4 Debug Monitor Interrupt */
    PendSV_IRQn = -2,                   /**< Cortex-M4 Pend SV Interrupt */
    SysTick_IRQn = -1,                  /**< Cortex-M4 System Tick Interrupt */

    /* Device specific interrupts */
    DMA0_IRQn = 0,                      /**< DMA Channel 0 Transfer Complete */
    DMA1_IRQn = 1,                      /**< DMA Channel 1 Transfer Complete */
    DMA2_IRQn = 2,                      /**< DMA Channel 2 Transfer Complete */
    DMA3_IRQn = 3,                      /**< DMA Channel 3 Transfer Complete */
    DMA_Error_IRQn = 4,                 /**< DMA Error Interrupt */
    Reserved21_IRQn = 5,                /**< Normal Interrupt */
    FTFL_IRQn = 6,                      /**< FTFA Command complete interrupt */
    Read_Collision_IRQn = 7,            /**< Read Collision Interrupt */
    LVD_LVW_IRQn = 8,                   /**< Low Voltage Detect, Low Voltage Warning */
    LLWU_IRQn = 9,                      /**< Low Leakage Wakeup Unit */
    WDOG_IRQn = 10,                     /**< WDOG Interrupt */
    I2C0_IRQn = 11,                     /**< I2C0 interrupt */
    SPI0_IRQn = 12,                     /**< SPI0 Interrupt */
    I2S0_Tx_IRQn = 13,                  /**< I2S0 transmit interrupt */
    I2S0_Rx_IRQn = 14,                  /**< I2S0 receive interrupt */
    UART0_LON_IRQn = 15,                /**< UART0 LON interrupt */
    UART0_RX_TX_IRQn = 16,              /**< UART0 Receive/Transmit interrupt */
    UART0_ERR_IRQn = 17,                /**< UART0 Error interrupt */
    UART1_RX_TX_IRQn = 18,              /**< UART1 Receive/Transmit interrupt */
    UART1_ERR_IRQn = 19,                /**< UART1 Error interrupt */
    UART2_RX_TX_IRQn = 20,              /**< UART2 Receive/Transmit interrupt */
    UART2_ERR_IRQn = 21,                /**< UART2 Error interrupt */
    ADC0_IRQn = 22,                     /**< ADC0 interrupt */
    CMP0_IRQn = 23,                     /**< CMP0 interrupt */
    CMP1_IRQn = 24,                     /**< CMP1 interrupt */
    FTM0_IRQn = 25,                     /**< FTM0 fault, overflow and channels interrupt */
    FTM1_IRQn = 26,                     /**< FTM1 fault, overflow and channels interrupt */
    CMT_IRQn = 27,                      /**< CMT interrupt */
    RTC_IRQn = 28,                      /**< RTC interrupt */
    RTC_Seconds_IRQn = 29,              /**< RTC seconds interrupt */
    PIT0_IRQn = 30,                     /**< PIT timer channel 0 interrupt */
    PIT1_IRQn = 31,                     /**< PIT timer channel 1 interrupt */
    PIT2_IRQn = 32,                     /**< PIT timer channel 2 interrupt */
    PIT3_IRQn = 33,                     /**< PIT timer channel 3 interrupt */
    PDB0_IRQn = 34,                     /**< PDB0 Interrupt */
    USB0_IRQn = 35,                     /**< USB0 interrupt */
    USB0DCD_IRQn = 36,                  /**< USBDCD interrupt */
    TSI0_IRQn = 37,                     /**< TSI0 interrupt */
    MCG_IRQn = 38,                      /**< MCG Interrupt */
    LPTMR0_IRQn = 39,                   /**< LPTimer interrupt */
    PORTA_IRQn = 40,                    /**< Port A interrupt */
    PORTB_IRQn = 41,                    /**< Port B interrupt */
    PORTC_IRQn = 42,                    /**< Port C interrupt */
    PORTD_IRQn = 43,                    /**< Port D interrupt */
    PORTE_IRQn = 44,                    /**< Port E interrupt */
    SWI_IRQn = 45,                      /**< Software interrupt */
} IRQn_Type;

/**********************************************************/
/* Uniform multiplatform 8-bits peripheral access macros */
/**********************************************************/

/* Enable maskable interrupts */
#define __enable_irq(void)\
 do {\
  /*lint -save  -e950 Disable MISRA rule (1.1) checking. */\
     __asm("CPSIE f");\
  /*lint -restore Enable MISRA rule (1.1) checking. */\
 } while(0)

/* Disable maskable interrupts */
#define __disable_irq() \
 do {\
  /*lint -save  -e950 Disable MISRA rule (1.1) checking. */\
     __asm ("CPSID f");\
  /*lint -restore Enable MISRA rule (1.1) checking. */\
 } while(0)

/* Save status register and disable interrupts */
#define EnterCritical() \
 do {\
  uint8_t SR_reg_local;\
  /*lint -save  -e586 -e950 Disable MISRA rule (2.1,1.1) checking. */\
   __asm ( \
   "MRS R0, FAULTMASK\n\t" \
   "CPSID f\n\t"            \
   "STRB R0, %[output]"  \
   : [output] "=m" (SR_reg_local)\
   :: "r0");\
  /*lint -restore Enable MISRA rule (2.1,1.1) checking. */\
   if (++SR_lock == 1u) {\
     SR_reg = SR_reg_local;\
   }\
 } while(0)

/* Restore status register  */
#define ExitCritical() \
 do {\
   if (--SR_lock == 0u) { \
  /*lint -save  -e586 -e950 Disable MISRA rule (2.1,1.1) checking. */\
     __asm (                 \
       "ldrb r0, %[input]\n\t"\
       "msr FAULTMASK,r0;\n\t" \
       ::[input] "m" (SR_reg)  \
       : "r0");                \
  /*lint -restore Enable MISRA rule (2.1,1.1) checking. */\
   }\
 } while(0)

#define _DEBUGHALT() \
  /*lint -save  -e586 -e950 Disable MISRA rule (2.1,1.1) checking. */\
  __asm( "BKPT 255") \
  /*lint -restore Enable MISRA rule (2.1,1.1) checking. */

#define _NOP() \
  /*lint -save  -e586 -e950 Disable MISRA rule (2.1,1.1) checking. */\
  __asm( "NOP") \
  /*lint -restore Enable MISRA rule (2.1,1.1) checking. */

#define _WFI() \
  /*lint -save  -e586 -e950 Disable MISRA rule (2.1,1.1) checking. */\
  __asm("WFI") \
  /*lint -restore Enable MISRA rule (2.1,1.1) checking. */

/* Interrupt definition template */
#if !defined(Default_ISR)
#define Default_ISR(ISR_name) void __attribute__ ((weak, interrupt)) ISR_name(void)
#endif

#endif /* __TYPES_H__ */

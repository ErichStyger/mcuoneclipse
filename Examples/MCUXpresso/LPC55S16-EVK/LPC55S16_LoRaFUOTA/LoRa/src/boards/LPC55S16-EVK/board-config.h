/*!
 * \file      board-config.h
 *
 * \brief     Board configuration
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \author    Diego Bienz
 */

#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "platform.h"

#define BOARD_CONFIG_HAS_GNSS             (0)
  /*!< if board has a GNSS (GPS) or not */

#define BOARD_CONFIG_HAS_SECURE_ELEMENT   (0)
  /*!< if board has a secure element or not */

#define BOARD_CONFIG_ENTER_LOW_POWER      (0)
  /*!< if we enter low power mode */

/**
 * General definitions
 */
#define BOARD_UART_BAUDRATE						115200

/**
 * UART definitions
 */
#if PL_CONFIG_USE_SHELL_UART /* using shell uart? disable USART direcly used by app */
  #define LPC_NUMBER_OF_USARTS                    0
#else
  #define LPC_NUMBER_OF_USARTS                    1
#endif

#if(LPC_NUMBER_OF_USARTS > 0)
#define LPC_USART1_TYPE                         USART0 /* Board UART */
#define LPC_USART1_CLK_FRQ                      CLOCK_GetFlexCommClkFreq(0U)
#define LPC_USART1_IRQn                         FLEXCOMM0_IRQn
#define LPC_USART1_IRQ_HANDLER                  FLEXCOMM0_IRQHandler
#define LPC_USART1_IRQ_ENABLE                   kUSART_RxLevelInterruptEnable | kUSART_RxErrorInterruptEnable
#define LPC_USART1_IRQ_FLAGS                    kUSART_RxFifoNotEmptyFlag | kUSART_RxError
#endif
#if(LPC_NUMBER_OF_USARTS > 1)
#define LPC_USART2_TYPE							USART3 /* GPS Modul UART */
#define LPC_USART2_CLK_FRQ						CLOCK_GetFlexCommClkFreq(3U)
#define LPC_USART2_IRQn							FLEXCOMM3_IRQn
#define LPC_USART2_IRQ_HANDLER					FLEXCOMM3_IRQHandler
#define LPC_USART2_IRQ_ENABLE					kUSART_RxLevelInterruptEnable | kUSART_RxErrorInterruptEnable
#define LPC_USART2_IRQ_FLAGS					kUSART_RxFifoNotEmptyFlag | kUSART_RxError
#endif

/**
 * SPI definitions
 */
#define LPC_NUMBER_OF_SPI                       2

#if(LPC_NUMBER_OF_SPI > 0)
  /* LoRa Transceiver is on FlexComm 8 */
  #define LPC_SPI1_TYPE                           SPI8 /* LoRa Transceiver */
  #define LPC_SPI1_CLK_FRQ                        CLOCK_GetFlexCommClkFreq(8U)
  #define LPC_SPI1_CONFIG_POLARITY                kSPI_ClockPolarityActiveHigh
  #define LPC_SPI1_CONFIG_PHASE                   kSPI_ClockPhaseFirstEdge
  #define LPC_SPI1_CONFIG_DIRECTION               kSPI_MsbFirst
  #define LPC_SPI1_CONFIG_BAUDRATE                500000U
  #define LPC_SPI1_CONFIG_DATAWIDTH               kSPI_Data8Bits
  #define LPC_SPI1_CONFIG_SS                      kSPI_Ssel0
  #define LPC_SPI1_CONFIG_SPOL                    kSPI_SpolActiveAllLow
#endif
#if(LPC_NUMBER_OF_SPI > 1)
	#define LPC_SPI2_TYPE                           SPI3 /* LoRa Transceiver */
	#define LPC_SPI2_CLK_FRQ                        CLOCK_GetFlexCommClkFreq(3U)
	#define LPC_SPI2_SPI_MASTER_IRQ      			  FLEXCOMM3_IRQn
	#define LPC_SPI2_CONFIG_POLARITY                kSPI_ClockPolarityActiveHigh
	#define LPC_SPI2_CONFIG_PHASE                   kSPI_ClockPhaseFirstEdge
	#define LPC_SPI2_CONFIG_DIRECTION               kSPI_MsbFirst
	#define LPC_SPI2_CONFIG_BAUDRATE                500000U
	#define LPC_SPI2_CONFIG_DATAWIDTH               kSPI_Data8Bits
	#define LPC_SPI2_CONFIG_SS                      kSPI_Ssel0
	#define LPC_SPI2_CONFIG_SPOL                    kSPI_SpolActiveAllLow
#endif

/**
 * I2C definitions
 */
#if BOARD_CONFIG_HAS_SECURE_ELEMENT
  #define LPC_NUMBER_OF_I2C                       1
#else
  #define LPC_NUMBER_OF_I2C                       0
#endif

#if(LPC_NUMBER_OF_I2C > 0)
#define LPC_I2C1_TYPE                           I2C7 /* Secure Element */
#define LPC_I2C1_CLK_FRQ                        12000000
#define LPC_I2C1_BAUDRATE                       100000
#define LPC_I2C1_SLAVE_ADDR_SIZE                I2C_ADDR_SIZE_8
#endif
#if(LPC_NUMBER_OF_I2C > 1)
#define LPC_I2C2_TYPE                           I2C2 /* Free */
#define LPC_I2C2_CLK_FRQ                        12000000
#define LPC_I2C2_BAUDRATE                       100000
#define LPC_I2C2_SLAVE_ADDR_SIZE                I2C_ADDR_SIZE_8
#endif

/**
 * ADC definitions
 */
#define LPC_ADC1_TYPE							          ADC0
#define LPC_ADC1_VREF_SRC						        kLPADC_ReferenceVoltageAlt2
#define LPC_ADC1_DO_OFFSET_CALIBRATION			true
#define LPC_ADC1_USE_HIGH_RESOLUTION			  true

/**
 * Radio definitions (LoRa Transceiver)
 */
#define RADIO_NSS_PIN							  PIO1_9  /* MCU pin 10, ARD_P1_10 */
#define RADIO_TCXO_WAKEUP_TIME      5
#define RADIO_RESET_PIN							PIO0_16 /* MCU pin 14,  FC1_I2C_SCL */
#define RADIO_ANT_SWITCH_PIN				PIO1_8  /* MCU pin 14, ARD_P1_8 */
#define RADIO_BUSY_PIN							PIO1_6  /* MCU pin 5, ARD_LEDB_PWM, blue RGB LED! */
#define RADIO_DIO_1_PIN							PIO1_4  /* MCU pin 1, ARD_LEDR_PWM, red RGB LED! */
#define RADIO_DEVICE_SEL_PIN        PIO0_0  /* MCU pin 54, ARD_CMP0_IN_A */

/**
 * LED pins
 */
#define LED_1     PIO1_7    /* MCU pin 9, ARD_LEDG_PW, green RGB LED */
#define LED_2     /* PIO0_0 no second LED available on board */

/**
 * GNSS definitions
 */
#if BOARD_CONFIG_HAS_GNSS
  #define GNSS_UART_BAUDRATE				9600
  #define GNSS_PPS_PIN							PIO0_25
  #define GNSS_RESET_PIN						PIO0_22
#endif
/**
 * Power Mode Options
 */
/* Deep Sleep is used for "Stop Mode" in this stack */
#define BOARD_EXCLUDE_FROM_DEEPSLEEP 									      	  \
												/* kPDRUNCFG_PD_DCDC | */         \
												/* kPDRUNCFG_PD_BIAS | */         \
												/* kPDRUNCFG_PD_BODCORE | */      \
												/* kPDRUNCFG_PD_BODVBAT | */ 	  \
												/* kPDRUNCFG_PD_FRO1M |	*/		  \
												/* kPDRUNCFG_PD_FRO192M | */      \
												/* kPDRUNCFG_PD_FRO32K  | */   	  \
												kPDRUNCFG_PD_XTAL32K        	  \
												/* kPDRUNCFG_PD_XTAL32M | */      \
												/* kPDRUNCFG_PD_PLL0 | */         \
												/* kPDRUNCFG_PD_PLL1 | */         \
												/* kPDRUNCFG_PD_USB0_PHY | */     \
												/* kPDRUNCFG_PD_USB1_PHY | */     \
												/* kPDRUNCFG_PD_COMP | */         \
												/* kPDRUNCFG_PD_TEMPSENS | */     \
												/* kPDRUNCFG_PD_GPADC | */        \
												/* kPDRUNCFG_PD_LDOMEM | */       \
												/* kPDRUNCFG_PD_LDODEEPSLEEP | */ \
												/* kPDRUNCFG_PD_LDOUSBHS | */     \
												/* kPDRUNCFG_PD_LDOGPADC | */     \
												/* kPDRUNCFG_PD_LDOXO32M | */     \
												/* kPDRUNCFG_PD_LDOFLASHNV | */   \
												/* kPDRUNCFG_PD_RNG | */          \
												/* kPDRUNCFG_PD_PLL0_SSCG | */    \
												/* kPDRUNCFG_PD_ROM   */          \

#define BOARD_SRAM_RETENTION_DEEPSLEEP		                                        	  	  \
												LOWPOWER_SRAMRETCTRL_RETEN_RAMX0 |            \
												LOWPOWER_SRAMRETCTRL_RETEN_RAMX1 |            \
												LOWPOWER_SRAMRETCTRL_RETEN_RAMX2 |            \
												LOWPOWER_SRAMRETCTRL_RETEN_RAMX3 |            \
												LOWPOWER_SRAMRETCTRL_RETEN_RAM00 |            \
												LOWPOWER_SRAMRETCTRL_RETEN_RAM10 |            \
												LOWPOWER_SRAMRETCTRL_RETEN_RAM20 |            \
												LOWPOWER_SRAMRETCTRL_RETEN_RAM_USB_HS         \

#define BOARD_WAKEUP_INTERRUPTS_DEEPSLEEP		                                      \
												/* WAKEUP_SYS | */                    \
												/* WAKEUP_SDMA0 | */                  \
												/* WAKEUP_GPIO_GLOBALINT0 | */        \
												/* WAKEUP_GPIO_GLOBALINT1 | */        \
												WAKEUP_GPIO_INT0_0 |             	  \
												WAKEUP_GPIO_INT0_1 |        		  \
												/* WAKEUP_GPIO_INT0_2 | */            \
												/* WAKEUP_GPIO_INT0_3 | */            \
												/* WAKEUP_UTICK | */                  \
												/* WAKEUP_MRT | */                    \
												/* WAKEUP_CTIMER0 */                  \
												/* WAKEUP_CTIMER1 | */                \
												/* WAKEUP_SCT | */                    \
												/* WAKEUP_CTIMER3 | */                \
												/* WAKEUP_FLEXCOMM0 | */              \
												/* WAKEUP_FLEXCOMM1 | */              \
												/* WAKEUP_FLEXCOMM2 | */              \
												/* WAKEUP_FLEXCOMM3 | */              \
												/* WAKEUP_FLEXCOMM4 | */              \
												/* WAKEUP_FLEXCOMM5 | */              \
												/* WAKEUP_FLEXCOMM6 | */              \
												/* WAKEUP_FLEXCOMM7 | */              \
												/* WAKEUP_ADC | */                    \
												/* WAKEUP_ACMP | */                   \
												/* WAKEUP_USB0_NEEDCLK | */           \
												/* WAKEUP_USB0 | */                   \
												/* WAKEUP_RTC_LITE_ALARM_WAKEUP | */  \
												/* WAKEUP_EZH_ARCH_B | */             \
												/* WAKEUP_WAKEUP | */                 \
												/* WAKEUP_GPIO_INT0_4 | */            \
												/* WAKEUP_GPIO_INT0_5 | */            \
												/* WAKEUP_GPIO_INT0_6 | */            \
												/* WAKEUP_GPIO_INT0_7 | */            \
												/* WAKEUP_CTIMER2 | */                \
												/* WAKEUP_CTIMER4 | */                \
												WAKEUP_OS_EVENT_TIMER 		          \
												/* WAKEUP_USB1 | */                   \
												/* WAKEUP_USB1_NEEDCLK | */           \
												/* WAKEUP_SEC_HYPERVISOR_CALL | */    \
												/* WAKEUP_SEC_GPIO_INT0_0 | */        \
												/* WAKEUP_SEC_GPIO_INT0_1 | */        \
												/* WAKEUP_PLU | */                    \
												/* WAKEUP_SEC_VIO | */                \
												/* WAKEUP_SHA | */                    \
												/* WAKEUP_CASPER | */                 \
												/* WAKEUP_PUF | */                    \
												/* WAKEUP_SDMA1 | */                  \
												/* WAKEUP_LSPI_HS | */                \
												/* WAKEUP_ALLWAKEUPIOS   */           \

/* Deep Power Down is used for "Off Mode" in this stack */
#define BOARD_EXCLUDE_FROM_DEEP_POWERDOWN 		kPDRUNCFG_PD_XTAL32K

#define BOARD_WAKEUP_INTERRUPTS_DEEP_POWERDOWN	WAKEUP_OS_EVENT_TIMER

#define BOARD_SRAM_RETENTION_DEEP_POWERDOWN	    LOWPOWER_SRAMRETCTRL_RETEN_RAM20

/* custom board interface */
void BoardPrintUUID(void);

#ifdef __cplusplus
}
#endif

#endif // __BOARD_CONFIG_H__

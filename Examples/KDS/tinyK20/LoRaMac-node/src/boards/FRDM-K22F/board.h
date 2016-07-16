/**
 * \file board.h
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief Target board general functions implementation
 *
 */
#ifndef __BOARD_H__
#define __BOARD_H__

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "fsl_os_abstraction.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_port_hal.h"
#include "utilities.h"
#include "timer.h"
#include "delay.h"
#include "gpio.h"
#include "adc.h"
#include "spi.h"
#include "i2c.h"
#include "uart.h"
#include "radio.h"
#include "gps.h"
#include "sx1276/sx1276.h"
#include "fxos.h"
#include "rtc-board.h"
#include "timer-board.h"
#include "sx1276-board.h"
#include "gps-board.h"
#include "uart-board.h"

#if defined( USE_USB_CDC )
#include "usb-cdc-board.h"
#endif

/*******************************************************************************
 * CONSTANT DEFINITIONS
 ******************************************************************************/
#if defined(USE_LOW_POWER_MODE)
#define LOW_POWER_MODE_ENABLE   1
#endif

/*!
 * NULL definition
 */
#ifndef NULL
#define NULL                           ( ( void * )0 )
#endif

/*!
 * Generic definition
 */
#ifndef SUCCESS
#define SUCCESS                        1
#endif

#ifndef FAIL
#define FAIL                           0
#endif

/* More specific error codes */
#define ERR_OK                          0x00U /*!< OK */
#define ERR_RANGE                       0x01U /*!< Parameter out of range. */
#define ERR_VALUE                       0x02U /*!< Parameter of incorrect value. */
#define ERR_OVERFLOW                    0x03U /*!< Timer overflow. */
#define ERR_ENABLED                     0x04U /*!< Device is enabled. */
#define ERR_DISABLED                    0x05U /*!< Device is disabled. */
#define ERR_BUSY                        0x06U /*!< Device is busy. */
#define ERR_NOTAVAIL                    0x07U /*!< Requested value or method not available. */
#define ERR_RXEMPTY                     0x08U /*!< No data in receiver. */
#define ERR_TXFULL                      0x09U /*!< Transmitter is full. */
#define ERR_OVERRUN                     0x0AU /*!< Overrun error is detected. */
#define ERR_IDLE                        0x0BU /*!< Idle error is detected. */
#define ERR_FAULT                       0x0CU /*!< Fault error is detected. */
#define ERR_CRC                         0x0DU /*!< CRC error is detected. */
#define ERR_UNDERFLOW                   0x0EU /*!< Underflow error is detected. */
#define ERR_UNDERRUN                    0x0FU /*!< Underrun error is detected. */
#define ERR_COMMON                      0x10U /*!< Common error of a device. */
#define ERR_FAILED                      0x11U /*!< Requested functionality or process failed. */
#define ERR_QFULL                       0x12U /*!< Queue is full. */
#define ERR_INVALID_TYPE                0x13U /*!< Invalid type. */
#define ERR_UNKNOWN                     0x14U /*!< */

/*!
 * Unique Devices IDs register set
 */
#define         ID1                    ( SIM_UIDH )
#define         ID2                    ( SIM_UIDMH )
#define         ID3                    ( SIM_UIDML )
#define         ID4                    ( SIM_UIDL )

/*!
 * Random seed generated using the MCU Unique ID
 */
#define RAND_SEED                      ( ( *( uint32_t* )ID1 ) ^ \
                                         ( *( uint32_t* )ID2 ) ^ \
                                         ( *( uint32_t* )ID3 ) ^ \
                                         ( *( uint32_t* )ID4 ) )

/*! Board MCU pins definitions */
#if !defined(SX1276_BOARD_EMBED)
#define LED_1                          PA_2
#define LED_2                          PA_1
#define LED_3                          PD_5
#endif

#define SWITCH_A                       PB_17
#define SWITCH_B                       PC_1

#if defined(SX1276_BOARD_EMBED)

#define RADIO_RESET                    PB_0

#define RADIO_SPI_INSTANCE             1
#define RADIO_MOSI                     PD_6
#define RADIO_MISO                     PD_7
#define RADIO_SCLK                     PD_5
#define RADIO_NSS                      PD_4

#define RADIO_DIO_0                    PB_16
#define RADIO_DIO_1                    PA_2
#define RADIO_DIO_2                    PA_4
#define RADIO_DIO_3                    PB_18
#define RADIO_DIO_4_A                  PB_19
#define RADIO_DIO_4_B                  PC_2
#define RADIO_DIO_5                    PA_1

#define RADIO_ANT_SWITCH_RX_TX         PB_3

#else

#define RADIO_RESET                    NC

#define RADIO_SPI_INSTANCE             -1
#define RADIO_MOSI                     NC
#define RADIO_MISO                     NC
#define RADIO_SCLK                     NC
#define RADIO_NSS                      NC

#define RADIO_DIO_0                    NC
#define RADIO_DIO_1                    NC
#define RADIO_DIO_2                    NC
#define RADIO_DIO_3                    NC
#define RADIO_DIO_4_A                  NC
#define RADIO_DIO_4_B                  NC
#define RADIO_DIO_5                    NC

#define RADIO_ANT_SWITCH_RX_TX         NC

#define FXOS8700CQ_I2C_INSTANCE        0
#define FXOS_I2C_ADDRESS               0x1C

#define IRQ_1_FXOS8700CQ               PD_0
#define IRQ_2_FXOS8700CQ               PD_1

#endif /* SX1276_BOARD */

#define PPS                            PD_4
#define I2C_SCL                        PB_2
#define I2C_SDA                        PB_3

/* Uart pin definition */
#define UART0_RX                       PD_6
#define UART0_TX                       PD_7
#define UART1_RX                       PE_1
#define UART1_TX                       PE_0

/*! MCU clock configuration */
#define CLOCK_VLPR 1U
#define CLOCK_RUN  2U
#define CLOCK_NUMBER_OF_CONFIGURATIONS 3U

#ifndef CLOCK_INIT_CONFIG
#define CLOCK_INIT_CONFIG CLOCK_RUN
#endif

/* OSC0 configuration. */
#define OSC0_XTAL_FREQ                 8000000U
#define OSC0_SC2P_ENABLE_CONFIG        false
#define OSC0_SC4P_ENABLE_CONFIG        false
#define OSC0_SC8P_ENABLE_CONFIG        false
#define OSC0_SC16P_ENABLE_CONFIG       false
#define MCG_HGO0                       kOscGainLow
#define MCG_RANGE0                     kOscRangeVeryHigh
#define MCG_EREFS0                     kOscSrcOsc

/* EXTAL0 PTA18 */
#define EXTAL0_PORT                    PORTA
#define EXTAL0_PIN                     18
#define EXTAL0_PINMUX                  kPortPinDisabled

/* XTAL0 PTA19 */
#define XTAL0_PORT                     PORTA
#define XTAL0_PIN                      19
#define XTAL0_PINMUX                   kPortPinDisabled

/* RTC external clock configuration. */
#define RTC_XTAL_FREQ                  32768U
#define RTC_SC2P_ENABLE_CONFIG         false
#define RTC_SC4P_ENABLE_CONFIG         false
#define RTC_SC8P_ENABLE_CONFIG         false
#define RTC_SC16P_ENABLE_CONFIG        false
#define RTC_OSC_ENABLE_CONFIG          true

#define BOARD_RTC_CLK_FREQUENCY        32768U;

/*******************************************************************************
 * PUBLIC VARIABLES
 ******************************************************************************/
#if !defined(SX1276_BOARD_EMBED)
/*! LED GPIO pin objects */
extern Gpio_t Led1;
extern Gpio_t Led2;
extern Gpio_t Led3;
#endif

/*! Button GPIO pin objects */
extern Gpio_t SwitchA;
extern Gpio_t SwitchB;

/*! External GPS interrupt */
extern Gpio_t GpsPps;

#if !defined(SX1276_BOARD_EMBED)
/*! IRQ GPIO pin objects */
extern Gpio_t Irq1Fxos8700;
extern Gpio_t Irq2Fxos8700;
#endif

/*! MCU objects  */
extern Adc_t Adc;
extern I2c_t I2c;
#if !defined(SX1276_BOARD_EMBED)
extern I2C_TypeDef Fxos;
#endif
extern Uart_t Lpuart;
extern Uart_t Uart0;
extern Uart_t Uart1;
extern Uart_t Uart2;
#if defined( USE_USB_CDC )
extern Uart_t UartUsb;
#endif

/*******************************************************************************
 * MODULE FUNCTION PROTOTYPES (PUBLIC)
 ******************************************************************************/
/*!
 * \brief Initializes the target board peripherals.
 */
void BoardInitMcu( void );

/*!
 * \brief Initializes the boards peripherals.
 */
void BoardInitPeriph( void );

/*!
 * \brief De-initializes the target board peripherals to decrease power
 *        consumption.
 */
void BoardDeInitMcu( void );

/*!
 * \brief Measure the Battery level
 *
 * \retval value  battery level ( 0: very low, 254: fully charged )
 */
uint8_t BoardGetBatteryLevel( void );

/*!
 * Returns a pseudo random seed generated using the MCU Unique ID
 *
 * \retval seed Generated pseudo random seed
 */
uint32_t BoardGetRandomSeed( void );

/*!
 * \brief Gets the board 64 bits unique ID
 *
 * \param [IN] id Pointer to an array that will contain the Unique ID
 */
void BoardGetUniqueId( uint8_t *id );

/*******************************************************************************
 * END OF CODE
 ******************************************************************************/

#endif // __BOARD_H__

/**
 * \file board.h
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief Target board general functions implementation
 *
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_port_hal.h"
#include "utilities.h"
#include "timer.h"
#include "delay.h"
#include "gpio.h"
#include "gps.h"
#include "adc.h"
#include "spi.h"
#include "i2c.h"
#include "uart.h"
#include "radio.h"
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

/*!
 * Unique Devices IDs register set
 */
#define         ID1                    ( SIM_UIDMH )
#define         ID2                    ( SIM_UIDML )
#define         ID3                    ( SIM_UIDL )

/*!
 * Random seed generated using the MCU Unique ID
 */
#define RAND_SEED                      ( ( *( uint32_t* )ID1 ) ^ \
                                         ( *( uint32_t* )ID2 ) ^ \
                                         ( *( uint32_t* )ID3 ) )

/*!
 * Board MCU pins definitions
 */
#define LED_1                          PE_31
#define LED_2                          PE_29
#if !defined(SX1276_BOARD_FREEDOM) && !defined(SX1276_BOARD_EMBED)
#define LED_3                          PD_5
#endif /* SX1276_BOARD_AVAILABLE */

#define SWITCH_A                       PC_3

#if defined(SX1276_BOARD_FREEDOM)

#define RADIO_RESET                    PC_1

#define RADIO_SPI_INSTANCE             1
#define RADIO_MOSI                     PD_6
#define RADIO_MISO                     PD_7
#define RADIO_SCLK                     PD_5
#define RADIO_NSS                      PD_4

#define RADIO_DIO_0                    PA_13
#define RADIO_DIO_1                    PD_2
#define RADIO_DIO_2                    PB_0
#define RADIO_DIO_3                    PB_2
#define RADIO_DIO_4                    PB_3
#define RADIO_DIO_5                    PC_2

#define RADIO_ANT_SWITCH_HF            PE_1
#define RADIO_ANT_SWITCH_LF            PE_0

#elif defined(SX1276_BOARD_EMBED)

#define RADIO_RESET                    PB_0

#define RADIO_SPI_INSTANCE             1
#define RADIO_MOSI                     PD_6
#define RADIO_MISO                     PD_7
#define RADIO_SCLK                     PD_5
#define RADIO_NSS                      PD_4

#define RADIO_DIO_0                    PD_3
#define RADIO_DIO_1                    PA_12
#define RADIO_DIO_2                    PA_4
#define RADIO_DIO_3                    PA_5
#define RADIO_DIO_4_A                  PA_13
#define RADIO_DIO_4_B                  PB_3
#define RADIO_DIO_5                    PD_2

#define RADIO_ANT_SWITCH_RX_TX         PC_2

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

#endif /* SX1276_BOARD */

#define FXOS8700CQ_I2C_INSTANCE        0
#define FXOS_I2C_ADDRESS               0x1D
#define I2C_SCL                        PE_24
#define I2C_SDA                        PE_25

#define IRQ_1_FXOS8700CQ               PD_0
#define IRQ_2_FXOS8700CQ               PD_1

#define UART0_RX                       PA_1
#define UART0_TX                       PA_2

#define TSIO_CH9                       PB_16
#define TSIO_CH10                      PB_17

#define SX_GPIO0                       PB_1

#define JTAG_RX_TGTMCU                 PA_1
#define JTAG_TX_TGTMCU                 PA_2
#define JTAG_SWD_CLK                   PA_0
#define JTAG_SWD_DIO_TGTMCU            PA_3
#define JTAG_NRST_TGTMCU               PA_20

/*!
 * LED GPIO pins objects
 */
extern Gpio_t Led1;
extern Gpio_t Led2;
#if !defined(SX1276_BOARD_FREEDOM) && !defined(SX1276_BOARD_EMBED)
extern Gpio_t Led3;
#endif

/*!
 * Button GPIO pin objects
 */
extern Gpio_t SwitchA;

/*!
 * IRQ GPIO pins objects
 */
extern Gpio_t Irq1Fxos8700;
extern Gpio_t Irq2Fxos8700;

/*!
 * MCU objects
 */
extern Adc_t Adc;
extern I2c_t I2c;
extern I2C_TypeDef Fxos;
extern Uart_t Uart0;
extern Uart_t Uart1;
extern Uart_t Uart2;
#if defined( USE_USB_CDC )
extern Uart_t UartUsb;
#endif

/*!
 * MCU clock configuration
 */

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
#define RTC_XTAL_FREQ                  0U
#define RTC_SC2P_ENABLE_CONFIG         false
#define RTC_SC4P_ENABLE_CONFIG         false
#define RTC_SC8P_ENABLE_CONFIG         false
#define RTC_SC16P_ENABLE_CONFIG        false
#define RTC_OSC_ENABLE_CONFIG          false
#define RTC_CLK_OUTPUT_ENABLE_CONFIG   false

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

#endif // __BOARD_H__

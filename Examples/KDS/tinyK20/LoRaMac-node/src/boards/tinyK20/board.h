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
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "MK20D5.h"
#include "system_MK20D5.h"
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
#include "rtc-board.h"
#include "timer-board.h"
#include "sx1276-board.h"
#include "gps-board.h"
#include "uart-board.h"

#if defined( USE_FREE_RTOS )
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#endif

#if defined( USE_USB_CDC )
#include "usb-cdc-board.h"
#endif

/*******************************************************************************
 * CONSTANT DEFINITIONS
 ******************************************************************************/
#if defined(USE_LOW_POWER_MODE)
#define LOW_POWER_MODE_ENABLE   1
#endif

/*! NULL definition */
#ifndef NULL
#define NULL                           ( ( void * )0 )
#endif

/*! Generic definition */
#ifndef SUCCESS
#define SUCCESS                        1
#endif

#ifndef FAIL
#define FAIL                           0
#endif

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

/*!
 * Board MCU pins definitions
 */
#define LED_1                          PD_4

#if defined(SX1276_BOARD_EMBED)

#define RADIO_RESET                    PC_1

#define RADIO_SPI_INSTANCE             0
#define RADIO_MOSI                     PC_6
#define RADIO_MISO                     PC_7
#define RADIO_SCLK                     PC_5
#define RADIO_NSS                      PD_0

#define RADIO_DIO_0                    PD_1
#define RADIO_DIO_1                    PA_2
#define RADIO_DIO_2                    PA_1
#define RADIO_DIO_3                    PD_5
#define RADIO_DIO_4_A                  PD_7
#define RADIO_DIO_4_B                  NC
#define RADIO_DIO_5                    PD_6

#define RADIO_ANT_SWITCH_RX_TX         PC_0

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

#define UART0_RX                       PB_16
#define UART0_TX                       PB_17
#define UART1_RX                       PC_3
#define UART1_TX                       PC_4
#define UART2_RX                       PD_2
#define UART2_TX                       PD_3

#define I2C_SCL                        NC//PB_0
#define I2C_SDA                        NC//PB_1

#define PPS                            PB_1//PC_2

/*******************************************************************************
 * PUBLIC VARIABLES
 ******************************************************************************/
/*! LED GPIO pin objects */
extern Gpio_t Led1;

/*! GPIO pin objects */
extern Gpio_t GpsPps;

/*! MCU objects */
extern Uart_t Uart0;
extern Uart_t Uart1;
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

#endif // __BOARD_H__

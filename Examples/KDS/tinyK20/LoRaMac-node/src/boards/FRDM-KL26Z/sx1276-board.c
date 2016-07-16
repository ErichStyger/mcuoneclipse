/**
 * \file sx1276-board.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief SX1276 driver specific target board functions implementation
 *
 */

#include "board.h"
#include "radio.h"
#include "sx1276/sx1276.h"
#include "sx1276-board.h"

/*!
 * Flag used to set the RF switch control pins in low power mode when the radio is not active.
 */
static bool RadioIsActive = false;

/*!
 * Radio driver structure initialization
 */
const struct Radio_s Radio = { SX1276Init, SX1276Reset, SX1276GetStatus, SX1276SetModem,
        SX1276SetChannel, SX1276IsChannelFree, SX1276Random, SX1276SetRxConfig,
        SX1276SetTxConfig, SX1276CheckRfFrequency, SX1276GetTimeOnAir, SX1276Send,
        SX1276SetSleep, SX1276SetStby, SX1276SetRx, SX1276StartCad, SX1276ReadRssi,
        SX1276Write, SX1276Read, SX1276WriteBuffer, SX1276ReadBuffer,
        SX1276SetMaxPayloadLength };

/*!
 * Antenna switch GPIO pins objects
 */
#if defined(SX1276_BOARD_FREEDOM)
Gpio_t AntSwitchLf;
Gpio_t AntSwitchHf;
#elif defined(SX1276_BOARD_EMBED)
Gpio_t AntSwitchRxTx;
#endif

void SX1276IoInit( void )
{
    GpioInit(&SX1276.Spi.Nss, RADIO_NSS, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 1);

    GpioInit(&SX1276.DIO0, RADIO_DIO_0, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0);
    GpioInit(&SX1276.DIO1, RADIO_DIO_1, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0);
    GpioInit(&SX1276.DIO2, RADIO_DIO_2, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0);
    GpioInit(&SX1276.DIO3, RADIO_DIO_3, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0);
#if defined(SX1276_BOARD_FREEDOM)
    GpioInit(&SX1276.DIO4, RADIO_DIO_4, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0);
#elif defined(SX1276_BOARD_EMBED)
    GpioInit(&SX1276.DIO4, RADIO_DIO_4_A, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0);
#endif
    GpioInit(&SX1276.DIO5, RADIO_DIO_5, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0);
}

void SX1276IoIrqInit( DioIrqHandler **irqHandlers )
{
    GpioSetInterrupt(&SX1276.DIO0, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, irqHandlers[0]);
    GpioSetInterrupt(&SX1276.DIO1, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, irqHandlers[1]);
    GpioSetInterrupt(&SX1276.DIO2, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, irqHandlers[2]);
    GpioSetInterrupt(&SX1276.DIO3, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, irqHandlers[3]);
    GpioSetInterrupt(&SX1276.DIO4, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, irqHandlers[4]);
    GpioSetInterrupt(&SX1276.DIO5, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, irqHandlers[5]);
}

void SX1276IoDeInit( void )
{
    GpioInit(&SX1276.Spi.Nss, RADIO_NSS, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 1);

    GpioInit(&SX1276.DIO0, RADIO_DIO_0, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
    GpioInit(&SX1276.DIO1, RADIO_DIO_1, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
    GpioInit(&SX1276.DIO2, RADIO_DIO_2, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
    GpioInit(&SX1276.DIO3, RADIO_DIO_3, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
#if defined(SX1276_BOARD_FREEDOM)
    GpioInit(&SX1276.DIO4, RADIO_DIO_4, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
#elif defined(SX1276_BOARD_EMBED)
    GpioInit(&SX1276.DIO4, RADIO_DIO_4_A, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
#endif
    GpioInit(&SX1276.DIO5, RADIO_DIO_5, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
}

uint8_t SX1276GetPaSelect( uint32_t channel )
{
    if ( channel < RF_MID_BAND_THRESH ) {
        return RF_PACONFIG_PASELECT_PABOOST;
    } else {
        return RF_PACONFIG_PASELECT_RFO;
    }
}

void SX1276SetAntSwLowPower( bool status )
{
    if ( RadioIsActive != status ) {
        RadioIsActive = status;

        if ( status == false ) {
            SX1276AntSwInit();
        } else {
            SX1276AntSwDeInit();
        }
    }
}

void SX1276AntSwInit( void )
{
#if defined(SX1276_BOARD_FREEDOM)
    GpioInit(&AntSwitchLf, RADIO_ANT_SWITCH_LF, PIN_OUTPUT, PIN_PUSH_PULL, PIN_PULL_UP, 1);
    GpioInit(&AntSwitchHf, RADIO_ANT_SWITCH_HF, PIN_OUTPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0);
#elif defined(SX1276_BOARD_EMBED)
    GpioInit(&AntSwitchRxTx, RADIO_ANT_SWITCH_RX_TX, PIN_OUTPUT, PIN_OPEN_DRAIN, PIN_NO_PULL, 0);
#endif
}

void SX1276AntSwDeInit( void )
{
#if defined(SX1276_BOARD_FREEDOM)
    GpioInit(&AntSwitchLf, RADIO_ANT_SWITCH_LF, PIN_OUTPUT, PIN_OPEN_DRAIN, PIN_NO_PULL, 0);
    GpioInit(&AntSwitchHf, RADIO_ANT_SWITCH_HF, PIN_OUTPUT, PIN_OPEN_DRAIN, PIN_NO_PULL, 0);
#elif defined(SX1276_BOARD_EMBED)
    GpioInit(&AntSwitchRxTx, RADIO_ANT_SWITCH_RX_TX, PIN_OUTPUT, PIN_OPEN_DRAIN, PIN_NO_PULL, 0);
#endif
}

void SX1276SetAntSw( uint8_t rxTx )
{
    if ( SX1276.RxTx == rxTx ) {
        return;
    }

    SX1276.RxTx = rxTx;

    // 1: TX, 0: RX
    if ( rxTx != 0 ) {
#if defined(SX1276_BOARD_FREEDOM)
        GpioWrite(&AntSwitchLf, 0);
        GpioWrite(&AntSwitchHf, 1);
#elif defined(SX1276_BOARD_EMBED)
        GpioWrite(&AntSwitchRxTx, 1);
#endif
    } else {
#if defined(SX1276_BOARD_FREEDOM)
        GpioWrite(&AntSwitchLf, 1);
        GpioWrite(&AntSwitchHf, 0);
#elif defined(SX1276_BOARD_EMBED)
        GpioWrite(&AntSwitchRxTx, 0);
#endif
    }
}

bool SX1276CheckRfFrequency( uint32_t frequency )
{
    // Implement check. Currently all frequencies are supported
    return true;
}

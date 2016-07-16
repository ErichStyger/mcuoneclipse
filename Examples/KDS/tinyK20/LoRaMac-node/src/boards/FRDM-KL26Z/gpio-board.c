/**
 * \file gpio-board.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief Target board GPIO driver implementation
 *
 */

#include "board.h"
#include "gpio-board.h"
#include "fsl_gpio_driver.h"
#include "fsl_port_hal.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

/*----------------------- Local Definitions ------------------------------*/
/*! Alternative pin function configuration struct */
typedef struct {
    PinNames pinName;
    port_mux_t muxConfig;
} gpio_alternate_fct_user_config_t;

extern gpio_alternate_fct_user_config_t alternateFctConfigs[];

/*!
 * Number of Pins per Port
 */
#define NR_OF_PINS_PORTA        11
#define NR_OF_PINS_PORTB        8
#define NR_OF_PINS_PORTAB       (NR_OF_PINS_PORTA+NR_OF_PINS_PORTB)
#define NR_OF_PINS_PORTC        12
#define NR_OF_PINS_PORTABC      (NR_OF_PINS_PORTA+NR_OF_PINS_PORTB+NR_OF_PINS_PORTC)
#define NR_OF_PINS_PORTD        8
#define NR_OF_PINS_PORTABCD     (NR_OF_PINS_PORTA+NR_OF_PINS_PORTB+NR_OF_PINS_PORTC+NR_OF_PINS_PORTD)
#define NR_OF_PINS_PORTE        11
#define NR_OF_PINS_PORTABCDE    (NR_OF_PINS_PORTA+NR_OF_PINS_PORTB+NR_OF_PINS_PORTC+NR_OF_PINS_PORTD+NR_OF_PINS_PORTE)
/*------------------------ Local Variables -------------------------------*/
/*!
 * Alternate pin configuration
 * \remark  For chip-specific alternate function see KL25 sub-family data sheet
 *          p. 44 - KL25 Signal Multiplexing and Pin Assignments.
 */
gpio_alternate_fct_user_config_t alternateFctConfigs[] = {
    {
        .pinName = PA_1,
        .muxConfig = kPortMuxAlt2, ///> UART0_RX
    },
    {
        .pinName = PA_2,
        .muxConfig = kPortMuxAlt2, ///> UART0_TX
    },
    {
        .pinName = PD_4,
        .muxConfig = kPortMuxAlt2, ///> SPI0_PCS0
    },
    {
        .pinName = PD_5,
        .muxConfig = kPortMuxAlt2, ///> SPI1_SCK
    },
    {
        .pinName = PD_6,
        .muxConfig = kPortMuxAlt2, ///> SPI1_MOSI
    },
    {
        .pinName = PD_7,
        .muxConfig = kPortMuxAlt2, ///> SPI1_MISO
    },
    {
        .pinName = PE_0,
        .muxConfig = kPortMuxAlt4, ///> RTC_CLKOUT
    },
    {
        .pinName = PE_24,
        .muxConfig = kPortMuxAlt5, ///> I2C0_SCL
    },
    {
        .pinName = PE_25,
        .muxConfig = kPortMuxAlt5, ///> I2C0_SDA
    },
    {
        .pinName = PIN_OUT_OF_RANGE,
    }
};

/*! Available pins for port A */
uint8_t pinsPortA[] = { 0, 1, 2, 3, 4, 5, 12, 13, 18, 19, 20 };
/*! Available pins for port B */
uint8_t pinsPortB[] = { 0, 1, 2, 3, 16, 17, 18, 19 };
/*! Available pins for port C */
uint8_t pinsPortC[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
/*! Available pins for port D */
uint8_t pinsPortD[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
/*! Available pins for port E */
uint8_t pinsPortE[] = { 0, 1, 20, 21, 22, 23, 24, 25, 29, 30, 31 };

/*! GPIO irq handler port A */
static GpioIrqHandler *GpioAIrq[21];

/*! GPIO irq handler port C */
static GpioIrqHandler *GpioCIrq[12];

/*! GPIO irq handler port D */
static GpioIrqHandler *GpioDIrq[8];

void GpioMcuInit(Gpio_t *obj, PinNames pin, PinModes mode, PinConfigs config, PinTypes type,
        uint32_t value)
{

    if (pin == NC) {
        return;
    }

    if (pin < NR_OF_PINS_PORTA) {
        obj->pinIndex = pinsPortA[pin];
        obj->portIndex = 0;
    } else if (pin < NR_OF_PINS_PORTAB) {
        obj->pinIndex = pinsPortB[(pin - NR_OF_PINS_PORTA)];
        obj->portIndex = 1;
    } else if (pin < NR_OF_PINS_PORTABC) {
        obj->pinIndex = pinsPortC[(pin - NR_OF_PINS_PORTAB)];
        obj->portIndex = 2;
    } else if (pin < NR_OF_PINS_PORTABCD) {
        obj->pinIndex = pinsPortD[(pin - NR_OF_PINS_PORTABC)];
        obj->portIndex = 3;
    } else if (pin < NR_OF_PINS_PORTABCDE) {
        obj->pinIndex = pinsPortE[(pin - NR_OF_PINS_PORTABCD)];
        obj->portIndex = 4;
    } else {
        return;
    }

    obj->pin = pin;
    obj->port = (void*) g_portBase[obj->portIndex];

#if 0
    switch (mode) {
        case PIN_INPUT:
        gpio_input_pin_user_config_t inputCfg;
        inputCfg.pinName = GPIO_MAKE_PIN(obj->portIndex, obj->pinIndex);
        inputCfg.config.isPullEnable = (type == PIN_NO_PULL) ? false : true;
        if (type == PIN_PULL_DOWN)
        inputCfg.config.pullSelect = kPortPullDown;
        else if (type == PIN_PULL_UP) inputCfg.config.pullSelect = kPortPullUp;
        inputCfg.config.interrupt = kPortIntDisabled;
        inputCfg.config.isPassiveFilterEnabled = false;
        GPIO_DRV_InputPinInit(&inputCfg);
        break;
        case PIN_OUTPUT:
        gpio_output_pin_user_config_t outputCfg;
        outputCfg.pinName = GPIO_MAKE_PIN(obj->portIndex, obj->pinIndex);
        outputCfg.config.outputLogic = value;
        outputCfg.config.driveStrength = kPortLowDriveStrength;
        outputCfg.config.slewRate = kPortFastSlewRate;
        GPIO_DRV_OutputPinInit(&outputCfg);
        break;
        case PIN_ALTERNATE_FCT:
        {
            int i = 0;
            while (alternateFctConfigs[i].pinName != PIN_OUT_OF_RANGE) {
                if (alternateFctConfigs[i].pinName == pin) {
                    PORT_HAL_SetMuxMode(g_portBase[obj->portIndex], obj->pinIndex,
                            alternateFctConfigs[i].muxConfig); // Configure alternate function muxing to gpio
                    break;
                }
                i++;
            }
            break;
        }
        case PIN_ANALOGIC:
        PORT_HAL_SetMuxMode(g_portBase[obj->portIndex], obj->pinIndex, kPortPinDisabled); // Set pin as disabled, but is used as an analog pin
        break;
        default:
        /* Nothing to do */
        break;
    }
#else
    /* Un-gate port clock*/
    CLOCK_SYS_EnablePortClock(obj->portIndex);

    switch (mode) {
        case PIN_INPUT:
            /* Set current pin as gpio.*/
            PORT_HAL_SetMuxMode(g_portBase[obj->portIndex], obj->pinIndex, kPortMuxAsGpio); // Configure pin muxing to gpio
            GPIO_HAL_SetPinDir(g_gpioBase[obj->portIndex], obj->pinIndex, kGpioDigitalInput); // Set pin direction to input
            PORT_HAL_SetPullCmd(g_portBase[obj->portIndex], obj->pinIndex,
                    ((type == PIN_NO_PULL) ? false : true)); // Enable/Disable internal pull resistor
            break;
        case PIN_OUTPUT:
            PORT_HAL_SetMuxMode(g_portBase[obj->portIndex], obj->pinIndex, kPortMuxAsGpio); // Configure pin muxing to gpio
            GPIO_HAL_WritePinOutput(g_gpioBase[obj->portIndex], obj->pinIndex, value); // Set default output level
            GPIO_HAL_SetPinDir(g_gpioBase[obj->portIndex], obj->pinIndex, kGpioDigitalOutput); // Set pin direction to output
            break;
        case PIN_ALTERNATE_FCT:
        {
            int i = 0;
            while (alternateFctConfigs[i].pinName != PIN_OUT_OF_RANGE) {
                if (alternateFctConfigs[i].pinName == pin) {
                    PORT_HAL_SetMuxMode(g_portBase[obj->portIndex], obj->pinIndex,
                            alternateFctConfigs[i].muxConfig); // Configure alternate function muxing to gpio
                    break;
                }
                i++;
            }
            break;
        }
        case PIN_ANALOGIC:
            PORT_HAL_SetMuxMode(g_portBase[obj->portIndex], obj->pinIndex, kPortPinDisabled); // Set pin as disabled, but is used as an analog pin
            break;
        default:
            /* Nothing to do */
            break;
    }
#endif
}

void GpioMcuSetInterrupt(Gpio_t *obj, IrqModes irqMode, IrqPriorities irqPriority,
        GpioIrqHandler *irqHandler)
{
    port_interrupt_config_t interruptCfg;

    if (irqHandler == NULL) {
        return;
    }

    if (obj->portIndex == 0)
        GpioAIrq[obj->pinIndex & 0x1F] = irqHandler;
    else if (obj->portIndex == 2)
        GpioCIrq[obj->pinIndex & 0x1F] = irqHandler;
    else if (obj->portIndex == 3)
        GpioDIrq[obj->pinIndex & 0x07] = irqHandler;
    else
        return;

    switch (irqMode) {
        case NO_IRQ:
            interruptCfg = kPortIntDisabled;
            break;
        case IRQ_RISING_EDGE:
            interruptCfg = kPortIntRisingEdge;
            break;
        case IRQ_FALLING_EDGE:
            interruptCfg = kPortIntFallingEdge;
            break;
        case IRQ_RISING_FALLING_EDGE:
            interruptCfg = kPortIntEitherEdge;
            break;
        default:
            interruptCfg = kPortIntRisingEdge;
            break;
    }

    PORT_HAL_SetPinIntMode(obj->port, obj->pinIndex, interruptCfg);

    /* Configure NVIC */
    if ((interruptCfg) && (g_portIrqId[obj->portIndex])) {
        /* Enable GPIO interrupt.*/
        INT_SYS_EnableIRQ (g_portIrqId[obj->portIndex]);
    }
}

void GpioMcuRemoveInterrupt(Gpio_t *obj)
{
    if (obj->portIndex == 0)
        GpioAIrq[obj->pinIndex & 0x1F] = NULL;
    else if (obj->portIndex == 3)
        GpioDIrq[obj->pinIndex & 0x1F] = NULL;
    else
        return;

    PORT_HAL_SetPinIntMode(obj->port, obj->pinIndex, kPortIntDisabled);
}

void GpioMcuWrite(Gpio_t *obj, uint32_t value)
{
    if ((obj == NULL) || (obj->port == NULL)) {
        while (1)
            ;
    }
    // Check if pin is not connected
    if (obj->pin == NC) {
        return;
    }
    GPIO_HAL_WritePinOutput(g_gpioBase[obj->portIndex], obj->pinIndex, value);
}

uint32_t GpioMcuRead(Gpio_t *obj)
{
    if (obj == NULL) {
        while (1)
            ;
    }
    // Check if pin is not connected
    if (obj->pin == NC) {
        return 0;
    }
    return GPIO_HAL_ReadPinOutput(g_gpioBase[obj->portIndex], obj->pinIndex);
}

void PORTA_IRQHandler(void)
{
    uint32_t pendingInt = PORTA_ISFR;

    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag (PORTA_BASE_PTR);

    if (pendingInt & 0x1)
        GpioAIrq[1]();
    else if ((pendingInt & (1U << 0)) >> 0)
        GpioAIrq[0]();
    else if ((pendingInt & (1U << 1)) >> 1)
        GpioAIrq[1]();
    else if ((pendingInt & (1U << 2)) >> 2)
        GpioAIrq[2]();
    else if ((pendingInt & (1U << 3)) >> 3)
        GpioAIrq[3]();
    else if ((pendingInt & (1U << 4)) >> 4)
        GpioAIrq[4]();
    else if ((pendingInt & (1U << 5)) >> 5)
        GpioAIrq[5]();
    /* PTA6 to PTA11 can't be used as GPIO */
    else if ((pendingInt & (1U << 12)) >> 12)
        GpioAIrq[12]();
    else if ((pendingInt & (1U << 13)) >> 13)
        GpioAIrq[13]();
    else if ((pendingInt & (1U << 14)) >> 14)
        GpioAIrq[14]();
    else if ((pendingInt & (1U << 15)) >> 15)
        GpioAIrq[15]();
    else if ((pendingInt & (1U << 16)) >> 16)
        GpioAIrq[16]();
    else if ((pendingInt & (1U << 17)) >> 17)
        GpioAIrq[17]();
    else if ((pendingInt & (1U << 18)) >> 18)
        GpioAIrq[18]();
    else if ((pendingInt & (1U << 19)) >> 19)
        GpioAIrq[19]();
    else if ((pendingInt & (1U << 20)) >> 20) GpioAIrq[20]();
    /* PTA21 to PTA31 can't be used as GPIO */
}

void PORTC_PORTD_IRQHandler(void)
{
    uint32_t pendingIntD = PORTD_ISFR;
    uint32_t pendingIntC = PORTC_ISFR;

    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag (PORTC_BASE_PTR);
    PORT_HAL_ClearPortIntFlag (PORTD_BASE_PTR);

    if (pendingIntD > 0) {
        if (pendingIntD & 0x1)
            GpioDIrq[1]();
        else if ((pendingIntD & (1U << 0)) >> 0)
            GpioDIrq[0]();
        else if ((pendingIntD & (1U << 1)) >> 1)
            GpioDIrq[1]();
        else if ((pendingIntD & (1U << 2)) >> 2)
            GpioDIrq[2]();
        else if ((pendingIntD & (1U << 3)) >> 3)
            GpioDIrq[3]();
        else if ((pendingIntD & (1U << 4)) >> 4)
            GpioDIrq[4]();
        else if ((pendingIntD & (1U << 5)) >> 5)
            GpioDIrq[5]();
        else if ((pendingIntD & (1U << 6)) >> 6)
            GpioDIrq[6]();
        else if ((pendingIntD & (1U << 7)) >> 7) GpioDIrq[7]();
        /* PTD8 to PTD31 can't be used as GPIO */
    }
    if (pendingIntC > 0) {
        if (pendingIntC & 0x1)
            GpioCIrq[1]();
        else if ((pendingIntC & (1U << 0)) >> 0)
            GpioCIrq[0]();
        else if ((pendingIntC & (1U << 1)) >> 1)
            GpioCIrq[1]();
        else if ((pendingIntC & (1U << 2)) >> 2)
            GpioCIrq[2]();
        else if ((pendingIntC & (1U << 3)) >> 3)
            GpioCIrq[3]();
        else if ((pendingIntC & (1U << 4)) >> 4)
            GpioCIrq[4]();
        else if ((pendingIntC & (1U << 5)) >> 5)
            GpioCIrq[5]();
        else if ((pendingIntC & (1U << 6)) >> 6)
            GpioCIrq[6]();
        else if ((pendingIntC & (1U << 7)) >> 7)
            GpioCIrq[7]();
        else if ((pendingIntC & (1U << 8)) >> 8)
            GpioCIrq[8]();
        else if ((pendingIntC & (1U << 9)) >> 9)
            GpioCIrq[9]();
        else if ((pendingIntC & (1U << 10)) >> 10)
            GpioCIrq[10]();
        else if ((pendingIntC & (1U << 11)) >> 11) GpioCIrq[11]();
        /* PTC12 to PTC31 can't be used as GPIO */
    }
}


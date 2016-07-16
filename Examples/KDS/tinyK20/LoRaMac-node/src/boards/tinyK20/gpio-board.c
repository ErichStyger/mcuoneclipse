/**
 * \file gpio-board.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief Target board GPIO driver implementation
 *
 */

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "board.h"
#include "gpio-board.h"

/*******************************************************************************
 * PRIVATE CONSTANT DEFINITIONS
 ******************************************************************************/
/*!
 * Number of Pins per Port
 */
#define NR_OF_PINS_PORTA        5
#define NR_OF_PINS_PORTB        6
#define NR_OF_PINS_PORTAB       (NR_OF_PINS_PORTA+NR_OF_PINS_PORTB)
#define NR_OF_PINS_PORTC        8
#define NR_OF_PINS_PORTABC      (NR_OF_PINS_PORTA+NR_OF_PINS_PORTB+NR_OF_PINS_PORTC)
#define NR_OF_PINS_PORTD        8
#define NR_OF_PINS_PORTABCD     (NR_OF_PINS_PORTA+NR_OF_PINS_PORTB+NR_OF_PINS_PORTC+NR_OF_PINS_PORTD)

/*******************************************************************************
 * PRIVATE TYPE DEFINITIONS
 ******************************************************************************/
typedef enum _port_interrupt_config {
    kPortIntDisabled = 0x0U, /*!< Interrupt/DMA request is disabled.*/
    kPortDmaRisingEdge = 0x1U, /*!< DMA request on rising edge.*/
    kPortDmaFallingEdge = 0x2U, /*!< DMA request on falling edge.*/
    kPortDmaEitherEdge = 0x3U, /*!< DMA request on either edge.*/
    kPortIntLogicZero = 0x8U, /*!< Interrupt when logic zero. */
    kPortIntRisingEdge = 0x9U, /*!< Interrupt on rising edge. */
    kPortIntFallingEdge = 0xAU, /*!< Interrupt on falling edge. */
    kPortIntEitherEdge = 0xBU, /*!< Interrupt on either edge. */
    kPortIntLogicOne = 0xCU /*!< Interrupt when logic one. */
} port_interrupt_config_t;

typedef enum _port_mux {
    kPortPinDisabled = 0U, /*!< Corresponding pin is disabled, but is used as an analog pin.*/
    kPortMuxAsGpio = 1U, /*!< Corresponding pin is configured as GPIO.*/
    kPortMuxAlt2 = 2U, /*!< Chip-specific*/
    kPortMuxAlt3 = 3U, /*!< Chip-specific*/
    kPortMuxAlt4 = 4U, /*!< Chip-specific*/
    kPortMuxAlt5 = 5U, /*!< Chip-specific*/
    kPortMuxAlt6 = 6U, /*!< Chip-specific*/
    kPortMuxAlt7 = 7U /*!< Chip-specific*/
} port_mux_t;

typedef struct {
    uint32_t pinName;
    port_mux_t muxConfig;
} alternate_fct_user_config_t;

/*******************************************************************************
 * PRIVATE VARIABLES (STATIC)
 ******************************************************************************/
/*! Available pins for port A */
uint8_t pinsPortA[] = { 0, 1, 2, 3, 4 };

/*! Available pins for port B */
uint8_t pinsPortB[] = { 0, 1, 2, 3, 16, 17 };

/*! Available pins for port C */
uint8_t pinsPortC[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

/*! Available pins for port D */
uint8_t pinsPortD[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

/*! GPIO irq handler port A */
static GpioIrqHandler *GpioAIrq[5];

/*! GPIO irq handler port B */
static GpioIrqHandler *GpioBIrq[18];

/*! GPIO irq handler port C */
static GpioIrqHandler *GpioCIrq[8];

/*! GPIO irq handler port D */
static GpioIrqHandler *GpioDIrq[8];

/* Base pointers */
const PORT_MemMapPtr g_portBase[] = PORT_BASE_PTRS;
const GPIO_MemMapPtr g_gpioBase[] = GPIO_BASE_PTRS;

static alternate_fct_user_config_t alternateFctCfg[] = {
    {
        .pinName = PB_16,
        .muxConfig = kPortMuxAlt3,   ///> UART0_RX
    },
    {
        .pinName = PB_17,
        .muxConfig = kPortMuxAlt3,   ///> UART0_TX
    },
    {
        .pinName = PC_4,
        .muxConfig = kPortMuxAlt3,   ///> UART1_TX
    },
    {
        .pinName = PC_3,
        .muxConfig = kPortMuxAlt3,   ///> UART1_RX
    },
    {
        .pinName = PD_2,
        .muxConfig = kPortMuxAlt3,   ///> UART2_RX
    },
    {
        .pinName = PD_3,
        .muxConfig = kPortMuxAlt3,   ///> UART2_TX
    },
    {
        .pinName = PD_0,
        .muxConfig = kPortMuxAlt2,   ///> SPI0_PCS0
    },
    {
        .pinName = PC_5,
        .muxConfig = kPortMuxAlt2,   ///> SPI0_SCK
    },
    {
        .pinName = PC_6,
        .muxConfig = kPortMuxAlt2,   ///> SPI0_MOSI
    },
    {
        .pinName = PC_7,
        .muxConfig = kPortMuxAlt2,   ///> SPI0_MISO
    },
    {
        .pinName = PB_3,
        .muxConfig = kPortMuxAlt2,   ///> I2C0_SDA
    },
    {
        .pinName = PB_2,
        .muxConfig = kPortMuxAlt2,   ///> I2C0_SCL
    },
    {
        .pinName = PIN_OUT_OF_RANGE,
    }
};

/*******************************************************************************
 * MODULE FUNCTIONS (PUBLIC)
 ******************************************************************************/
void GpioMcuInit( Gpio_t *obj, PinNames pin, PinModes mode, PinConfigs config, PinTypes type,
        uint32_t value )
{
    if ( pin == NC ) {
        return;
    }

    if ( pin < NR_OF_PINS_PORTA ) {
        obj->pinIndex = pinsPortA[pin];
        obj->portIndex = 0;
        /* Enable clock gating */
        SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTA_MASK;
    } else if ( pin < NR_OF_PINS_PORTAB ) {
        obj->pinIndex = pinsPortB[(pin - NR_OF_PINS_PORTA)];
        obj->portIndex = 1;
        /* Enable clock gating */
        SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTB_MASK;
    } else if ( pin < NR_OF_PINS_PORTABC ) {
        obj->pinIndex = pinsPortC[(pin - NR_OF_PINS_PORTAB)];
        obj->portIndex = 2;
        /* Enable clock gating */
        SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTC_MASK;
    } else if ( pin < NR_OF_PINS_PORTABCD ) {
        obj->pinIndex = pinsPortD[(pin - NR_OF_PINS_PORTABC)];
        obj->portIndex = 3;
        /* Enable clock gating */
        SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTD_MASK;
    } else {
        return;
    }

    obj->pin = pin;
    obj->port = (void*) g_portBase[obj->portIndex];

    switch ( mode ) {
        case PIN_INPUT:
        {
            /* Set pin muxing to gpio */
            g_portBase[obj->portIndex]->PCR[obj->pinIndex] =
                    (((g_portBase[obj->portIndex]->PCR[obj->pinIndex])
                            & ~(PORT_PCR_MUX_MASK | PORT_PCR_ISF_MASK)) | PORT_PCR_MUX(1));
            /* Set pin direction */
            g_gpioBase[obj->portIndex]->PDDR = ((g_gpioBase[obj->portIndex]->PDDR)
                    & ~(1U << obj->pinIndex));

            if ( type != PIN_NO_PULL ) {
                /* Enable internal pullup or pulldown */
                g_portBase[obj->portIndex]->PCR[obj->pinIndex] =
                        (((g_portBase[obj->portIndex]->PCR[obj->pinIndex]) & ~(PORT_PCR_PE_MASK))
                                | (1 << PORT_PCR_PE_SHIFT));
                /* Select pulldown or pullup */
                g_portBase[obj->portIndex]->PCR[obj->pinIndex] =
                        (((g_portBase[obj->portIndex]->PCR[obj->pinIndex]) & ~(PORT_PCR_PS_MASK))
                                | (((type == PIN_PULL_UP) ? 1 : 0) << PORT_PCR_PS_SHIFT));
            }
            break;
        }
        case PIN_OUTPUT:
            /* Set pin muxing to gpio */
            g_portBase[obj->portIndex]->PCR[obj->pinIndex] =
                    (((g_portBase[obj->portIndex]->PCR[obj->pinIndex])
                            & ~(PORT_PCR_MUX_MASK | PORT_PCR_ISF_MASK)) | PORT_PCR_MUX(1));
            /* Write pin output */
            if ( value > 0 )
                g_gpioBase[obj->portIndex]->PSOR = (1U << obj->pinIndex);
            else
                g_gpioBase[obj->portIndex]->PCOR = (1U << obj->pinIndex);
            /* Set pin direction */
            g_gpioBase[obj->portIndex]->PDDR |= (1U << obj->pinIndex);

            if ( config == PIN_OPEN_DRAIN ) {
                g_portBase[obj->portIndex]->PCR[obj->pinIndex] |= PORT_PCR_ODE_MASK;
            } else {
                if ( type != PIN_NO_PULL ) {
                    /* Enable internal pullup or pulldown */
                    g_portBase[obj->portIndex]->PCR[obj->pinIndex] =
                            (((g_portBase[obj->portIndex]->PCR[obj->pinIndex]) & ~(PORT_PCR_PE_MASK))
                                    | (1 << PORT_PCR_PE_SHIFT));
                    /* Select pulldown or pullup */
                    g_portBase[obj->portIndex]->PCR[obj->pinIndex] =
                            (((g_portBase[obj->portIndex]->PCR[obj->pinIndex]) & ~(PORT_PCR_PS_MASK))
                                    | (((type == PIN_PULL_UP) ? 1 : 0) << PORT_PCR_PS_SHIFT));
                }
            }
            break;
        case PIN_ALTERNATE_FCT:
        {
            uint8_t i = 0;
            while ( alternateFctCfg[i].pinName != PIN_OUT_OF_RANGE ) {
                if ( alternateFctCfg[i].pinName == pin ) {
                    g_portBase[obj->portIndex]->PCR[obj->pinIndex] =
                            (((g_portBase[obj->portIndex]->PCR[obj->pinIndex])
                                    & ~(PORT_PCR_MUX_MASK | PORT_PCR_ISF_MASK))
                                    | PORT_PCR_MUX(alternateFctCfg[i].muxConfig));
                    break;
                }
                i++;
            }
            if ( config == PIN_OPEN_DRAIN ) {
                g_portBase[obj->portIndex]->PCR[obj->pinIndex] |= PORT_PCR_ODE_MASK;
            }
        }
            break;
        case PIN_ANALOGIC:
            g_portBase[obj->portIndex]->PCR[obj->pinIndex] =
                    (((g_portBase[obj->portIndex]->PCR[obj->pinIndex])
                            & ~(PORT_PCR_MUX_MASK | PORT_PCR_ISF_MASK)) | PORT_PCR_MUX(0));
            break;
        default:
            /* Nothing to do */
            break;
    }
}

void GpioMcuSetInterrupt( Gpio_t *obj, IrqModes irqMode, IrqPriorities irqPriority,
        GpioIrqHandler *irqHandler )
{
    uint8_t intConfig;

    if ( irqHandler == NULL ) {
        return;
    }

    if ( obj->portIndex == 0 )
        GpioAIrq[obj->pinIndex & 0x1F] = irqHandler;
    else if ( obj->portIndex == 1 )
        GpioBIrq[obj->pinIndex & 0x1F] = irqHandler;
    else if ( obj->portIndex == 2 )
        GpioCIrq[obj->pinIndex & 0x0F] = irqHandler;
    else if ( obj->portIndex == 3 )
        GpioDIrq[obj->pinIndex & 0x07] = irqHandler;
    else
        return;

    switch ( irqMode ) {
        case NO_IRQ:
            intConfig = (uint8_t) kPortIntDisabled;
            break;
        case IRQ_RISING_EDGE:
            intConfig = (uint8_t) kPortIntRisingEdge;
            break;
        case IRQ_FALLING_EDGE:
            intConfig = (uint8_t) kPortIntFallingEdge;
            break;
        case IRQ_RISING_FALLING_EDGE:
            intConfig = (uint8_t) kPortIntEitherEdge;
            break;
        default:
            intConfig = (uint8_t) kPortIntRisingEdge;
            break;
    }

    /* Enable pin interrupt */
    g_portBase[obj->portIndex]->PCR[obj->pinIndex] =
            (((g_portBase[obj->portIndex]->PCR[obj->pinIndex])
                    & ~((PORT_PCR_IRQC_MASK | PORT_PCR_ISF_MASK)))
                    | ((((uint32_t)(((uint32_t)(intConfig)) << PORT_PCR_IRQC_SHIFT))
                            & PORT_PCR_IRQC_MASK)));

    /* Configure NVIC */
    if ( obj->pin == PPS ) {
        /* Set interrupt priority */
        NVIC_BASE_PTR->IP[40 + obj->portIndex] = 0x00u;
    } else {
        /* Set interrupt priority */
        NVIC_BASE_PTR->IP[40 + obj->portIndex] = 0x40u;
    }
    if ( intConfig ) {
        /* Enable port interrupt.*/
        NVIC_BASE_PTR->ISER[(((uint32_t)(int32_t)(PORTA_IRQn + obj->portIndex)) >> 5UL)] =
                (uint32_t)(1UL << (((uint32_t)(int32_t)(PORTA_IRQn + obj->portIndex)) & 0x1FUL));
    }
}

void GpioMcuRemoveInterrupt( Gpio_t *obj )
{
    if ( obj->portIndex == 0 )
        GpioAIrq[obj->pinIndex & 0x1F] = NULL;
    else if ( obj->portIndex == 1 )
        GpioBIrq[obj->pinIndex & 0x1F] = NULL;
    else if ( obj->portIndex == 2 )
        GpioCIrq[obj->pinIndex & 0x0F] = NULL;
    else if ( obj->portIndex == 3 )
        GpioDIrq[obj->pinIndex & 0x07] = NULL;
    else
        return;

    /* Disable pin interrupt */
    g_portBase[obj->portIndex]->PCR[obj->pinIndex] =
            (((g_portBase[obj->portIndex]->PCR[obj->pinIndex])
                    & ~((PORT_PCR_IRQC_MASK | PORT_PCR_ISF_MASK)))
                    | ((((uint32_t)(((uint32_t)(0)) << PORT_PCR_IRQC_SHIFT)) & PORT_PCR_IRQC_MASK)));
}

void GpioMcuWrite( Gpio_t *obj, uint32_t value )
{
    if ( (obj == NULL) || (obj->port == NULL) ) {
        while ( 1 )
            ;
    }
// Check if pin is not connected
    if ( obj->pin == NC ) {
        return;
    }

    /* Write pin output */
    if ( value > 0 )
        g_gpioBase[obj->portIndex]->PSOR = (1U << obj->pinIndex);
    else
        g_gpioBase[obj->portIndex]->PCOR = (1U << obj->pinIndex);
}

uint32_t GpioMcuRead( Gpio_t *obj )
{
    if ( obj == NULL ) {
        while ( 1 )
            ;
    }
// Check if pin is not connected
    if ( obj->pin == NC ) {
        return 0;
    }
    return ((g_gpioBase[obj->portIndex]->PDIR) >> obj->pinIndex);
}

void PORTA_IRQHandler( void )
{
    uint32_t pendingInt = PORTA_ISFR;

    /* Clear interrupt flag.*/
    PORTA_ISFR = ~0u;

    if ( pendingInt & 0x1 )
        GpioAIrq[0]();
    else if ( (pendingInt & (1U << 1)) >> 1 )
        GpioAIrq[1]();
    else if ( (pendingInt & (1U << 2)) >> 2 )
        GpioAIrq[2]();
    else if ( (pendingInt & (1U << 3)) >> 3 )
        GpioAIrq[3]();
    else if ( (pendingInt & (1U << 4)) >> 4 ) GpioAIrq[4]();
    /* PTA5 to PTA31 can't be used as GPIO */
}

void PORTB_IRQHandler( void )
{
    uint32_t pendingInt = PORTB_ISFR;

    /* Clear interrupt flag.*/
    PORTB_ISFR = ~0u;

    if ( (pendingInt & (1U << 1)) ) {
        SYST_CVR = 0x00; /* Reset current value register */
    }

    if ( pendingInt & 0x1 ) {
        GpioBIrq[0]();
    } else if ( (pendingInt & (1U << 1)) >> 1 ) {
        GpioBIrq[1]();
    } else if ( (pendingInt & (1U << 2)) >> 2 ) {
        GpioBIrq[2]();
    } else if ( (pendingInt & (1U << 3)) >> 3 ) {
        GpioBIrq[3]();
        /* PTB4 to PTB15 can't be used as GPIO */
    } else if ( (pendingInt & (1U << 16)) >> 16 ) {
        GpioBIrq[16]();
    } else if ( (pendingInt & (1U << 17)) >> 17 ) {
        GpioBIrq[17]();
    }
    /* PTB18 to PTB31 can't be used as GPIO */
}

void PORTC_IRQHandler( void )
{
    uint32_t pendingInt = PORTC_ISFR;

    /* Clear interrupt flag.*/
    PORTC_ISFR = ~0u;

    if ( pendingInt & 0x1 )
        GpioCIrq[0]();
    else if ( (pendingInt & (1U << 1)) >> 1 )
        GpioCIrq[1]();
    else if ( (pendingInt & (1U << 2)) >> 2 )
        GpioCIrq[2]();
    else if ( (pendingInt & (1U << 3)) >> 3 )
        GpioCIrq[3]();
    else if ( (pendingInt & (1U << 4)) >> 4 )
        GpioCIrq[4]();
    else if ( (pendingInt & (1U << 5)) >> 5 )
        GpioCIrq[5]();
    else if ( (pendingInt & (1U << 6)) >> 6 )
        GpioCIrq[6]();
    else if ( (pendingInt & (1U << 7)) >> 7 ) GpioCIrq[7]();
    /* PTC8 to PTC31 can't be used as GPIO */
}

void PORTD_IRQHandler( void )
{
    uint32_t pendingInt = PORTD_ISFR;

    /* Clear interrupt flag.*/
    PORTD_ISFR = ~0u;

    if ( pendingInt & 0x1 )
        GpioDIrq[0]();
    else if ( (pendingInt & (1U << 1)) >> 1 )
        GpioDIrq[1]();
    else if ( (pendingInt & (1U << 2)) >> 2 )
        GpioDIrq[2]();
    else if ( (pendingInt & (1U << 3)) >> 3 )
        GpioDIrq[3]();
    else if ( (pendingInt & (1U << 4)) >> 4 )
        GpioDIrq[4]();
    else if ( (pendingInt & (1U << 5)) >> 5 )
        GpioDIrq[5]();
    else if ( (pendingInt & (1U << 6)) >> 6 )
        GpioDIrq[6]();
    else if ( (pendingInt & (1U << 7)) >> 7 ) GpioDIrq[7]();
    /* PTD8 to PTD31 can't be used as GPIO */
}
/*******************************************************************************
 * END OF CODE
 ******************************************************************************/

/*!
 * \file      gpio-board.c
 *
 * \brief     Target board GPIO driver implementation
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \author    Diego Bienz
 */

#include "gpio-board.h"
#include "utilities.h"
#include "board-config.h"
#include "fsl_gpio.h"
#include "fsl_pint.h"
#include "fsl_inputmux.h"

/**
  * GPIO Port definitions
  */
#define LPC_GPIO_PORT_0 							0U
#define LPC_GPIO_PORT_1 							1U

/**
  * Interrupt definitions
  */
#define BOARD_NUMBER_OF_INTERRUPT_INPUTS			8

typedef struct
{
    pint_pin_int_t irqPin;
    bool inUse;
	Gpio_t* usedBy;
}irq_t;

static irq_t interruptPins[BOARD_NUMBER_OF_INTERRUPT_INPUTS];

/**
  * Flag to indicate if the PINT was initialized
  */
static bool pintInitialized = false;

/**
  * Function to get the next free interrupt pin from the available collection
  */
static void GetNextFreeIrq(irq_t** irq);

/**
  * Function to get the interrupt pin of a specific gpio
  */
static void GetIrqFromGpio(irq_t** irq, Gpio_t* gpio);

/**
  * Callback function for all interrupts from PINT
  */
void GpioIrqCallback(pint_pin_int_t pintr, uint32_t pmatch_status);

/**
  * CAUTION:
  * The pin configurations like muxing, clock, etc. is made with the pin_mux.* of the board.
  * You can also use the pin configuration tool of NXP.
  * This init function doesn't care about the handovered pin configurations
  */
void GpioMcuInit(Gpio_t *obj, PinNames pin, PinModes mode, PinConfigs config, PinTypes type, uint32_t value) {
  gpio_pin_direction_t direction;

	if (pin >= PIO0_0) {
		gpio_pin_config_t gpio_config;
		obj->pin = pin;

		obj->pinIndex = (obj->pin & 0x1F);
		if ((obj->pin & 0x0E0) == 0x80) {
			obj->portIndex = LPC_GPIO_PORT_0;
		} else if ((obj->pin & 0x0E0) == 0xA0) {
			obj->portIndex = LPC_GPIO_PORT_1;
		} else {
			for (;;) {
				/*!
				 * You should not reach this state. Invalid pin
				 */
			}
		}
		switch(mode) {
		  case PIN_INPUT:
		    direction = kGPIO_DigitalInput;
		    break;
		  case PIN_OUTPUT:
        direction = kGPIO_DigitalOutput;
        break;

		  default:
		  case PIN_ALTERNATE_FCT:
		  case PIN_ANALOGIC:
		    /* SDK does not support these. Using input instead */
        direction = kGPIO_DigitalInput;
        break;
		}
		gpio_config.pinDirection = direction;

		GPIO_PinInit(GPIO, (uint32_t) obj->portIndex, (uint32_t) obj->pinIndex, &gpio_config);

		// Sets initial output value
		if (mode == PIN_OUTPUT) {
			GpioMcuWrite(obj, value);
		}

	} else if (pin == NC) {
		return;
	}
}

void GpioMcuSetContext(Gpio_t *obj, void *context) {
	obj->Context = context;
}

/**
  * CAUTION: GPIO has to be initialised before, independent
  * whether as input or output
  */
void GpioMcuSetInterrupt(Gpio_t *obj, IrqModes irqMode,
		IrqPriorities irqPriority, GpioIrqHandler *irqHandler) {

	irq_t* irq;

	if (obj->pin >= PIO0_0) {

		if(!pintInitialized){
			PINT_Init(PINT);
			pintInitialized = true;

			for(int i = 0;i < BOARD_NUMBER_OF_INTERRUPT_INPUTS; i++){
				interruptPins[i].irqPin = i;
			}
		}

		obj->IrqHandler = irqHandler;

		GetNextFreeIrq(&irq);
		irq->inUse = true;
		irq->usedBy = obj;

		uint32_t pin = obj->portIndex << 5;
		pin += obj->pinIndex;
		inputmux_connection_t connection = pin + (PINTSEL0 << PMUX_SHIFT);

		INPUTMUX_Init(INPUTMUX);
		INPUTMUX_AttachSignal(INPUTMUX, irq->irqPin, connection);
		INPUTMUX_Deinit(INPUTMUX); // Turn off clock to inputmux to save power. Clock is only needed to make changes

		PINT_PinInterruptConfig(PINT, irq->irqPin, irqMode, GpioIrqCallback);
		PINT_EnableCallbackByIndex(PINT, irq->irqPin);
	}
}

void GpioMcuRemoveInterrupt(Gpio_t *obj) {
	irq_t* irq;

	if (obj->pin >= PIO0_0) {

		GetIrqFromGpio(&irq, obj);
		irq->inUse = false;
		irq->usedBy = NULL;

		PINT_PinInterruptConfig(PINT, irq->irqPin, kPINT_PinIntEnableNone, GpioIrqCallback);
		PINT_DisableCallbackByIndex(PINT, irq->irqPin);
	}
}

void GpioMcuWrite(Gpio_t *obj, uint32_t value) {
  if (obj == NULL) {
    for (;;) {
      /*!
       * You should not reach this state. Invalid pin
       */
    }
  }
	if (obj->pin >= PIO0_0) {
		if (obj->pin == NC) {
			return;
		}
		GPIO_PinWrite(GPIO, (uint32_t) obj->portIndex, (uint32_t) obj->pinIndex, (uint8_t) value);
	}
}

void GpioMcuToggle(Gpio_t *obj) {
  if (obj == NULL) {
    for (;;) {
      /*!
       * You should not reach this state. Invalid pin
       */
    }
  }
	if (obj->pin >= PIO0_0) {
		if (obj->pin == NC) {
			return;
		}
		GPIO_PortToggle(GPIO, (uint32_t) obj->portIndex, 1u << obj->pinIndex);
	}
}

uint32_t GpioMcuRead(Gpio_t *obj) {
  if (obj == NULL) {
    for (;;) {
      /*!
       * You should not reach this state. Invalid pin
       */
    }
  }
	if (obj->pin >= PIO0_0) {
		if (obj->pin == NC) {
			return -1;
		}
		return GPIO_PinRead(GPIO, (uint32_t) obj->portIndex, (uint32_t) obj->pinIndex);
	}
	return -1;
}

static void GetNextFreeIrq(irq_t** irq){
	bool freeIrqFound = false;

	for(int i = 0; i < BOARD_NUMBER_OF_INTERRUPT_INPUTS; i++){
		if(!interruptPins[i].inUse && !freeIrqFound){
			*irq = &interruptPins[i];
			freeIrqFound = true;
		}
	}

	if(!freeIrqFound){
		for(;;){
			/* All IRQ pins are used! */
		}
	}
}

static void GetIrqFromGpio(irq_t** irq, Gpio_t* gpio){
	bool irqFound = false;

	for(int i = 0; i < BOARD_NUMBER_OF_INTERRUPT_INPUTS; i++){
		if(!irqFound && interruptPins[i].usedBy->pinIndex == gpio->pinIndex && interruptPins[i].usedBy->portIndex == gpio->portIndex){
			*irq = &interruptPins[i];
			irqFound = true;
		}
	}

	if(!irqFound){
		for(;;){
			/* There is no irq from this gpio */
		}
	}
}

void GpioIrqCallback(pint_pin_int_t pintr, uint32_t pmatch_status){
	Gpio_t* gpio = interruptPins[pintr].usedBy;
	if(gpio->IrqHandler != NULL){
		gpio->IrqHandler(gpio->Context);
	}
}

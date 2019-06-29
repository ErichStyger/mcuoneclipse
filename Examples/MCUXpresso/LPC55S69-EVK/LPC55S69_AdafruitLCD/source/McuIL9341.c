/*
 * McuIL9341.c
 *
 *  Created on: 29.06.2019
 *      Author: Erich Styger
 */


#include "McuIL9341.h"
#include "McuGPIO.h"

/* TFT_CS_5V: LSPI_HS_SSEL1 */
#define MCUIL9341_CS_GPIO   GPIO
#define MCUIL9341_CS_PORT   1U
#define MCUIL9341_CS_PIN    7U

/* TFT_DC_5V: PIO1_5_GPIO_ARD */
#define MCUIL9341_DC_GPIO   GPIO
#define MCUIL9341_DC_PORT   1U
#define MCUIL9341_DC_PIN    5U

static McuGPIO_Handle_t MCUIL9341_CSPin;
static McuGPIO_Handle_t MCUIL9341_DCPin;

void MCUIL9341_Init(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);
  config.isInput = false;
  config.isLowOnInit = true;

#if 0
  /* initialize CS */
  config.hw.pin = MCUIL9341_CS_PIN;
  config.hw.port = MCUIL9341_CS_PORT;
  config.hw.gpio = MCUIL9341_CS_GPIO;
  MCUIL9341_CSPin = McuGPIO_InitGPIO(&config);
#endif

  /* initialize CS */
  config.hw.pin = MCUIL9341_DC_PIN;
  config.hw.port = MCUIL9341_DC_PORT;
  config.hw.gpio = MCUIL9341_DC_GPIO;
  MCUIL9341_DCPin = McuGPIO_InitGPIO(&config);
}

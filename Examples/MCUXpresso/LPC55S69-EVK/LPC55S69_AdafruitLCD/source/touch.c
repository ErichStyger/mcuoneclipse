/*
 * touch.c
 *
 *  Created on: 02.07.2019
 *      Author: Erich Styger Local
 */


#if 0

/* RT_CS_5V: PIO1_8_GPIO_ARD, PIO1_8 */
#define MCUSTMPE610_CS_GPIO   GPIO
#define MCUSTMPE610_CS_PORT   1U
#define MCUSTMPE610_CS_PIN    8U
static McuGPIO_Handle_t McuSTMPE610_CSPin;






/* initialize Touch CS (is LOW active) */
  config.hw.pin = MCUSTMPE610_CS_PIN;
  config.hw.port = MCUSTMPE610_CS_PORT;
  config.hw.gpio = MCUSTMPE610_CS_GPIO;
  McuSTMPE610_CSPin = McuGPIO_InitGPIO(&config);
#endif

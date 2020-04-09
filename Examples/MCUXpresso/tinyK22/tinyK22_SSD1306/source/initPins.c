/*
 * InitPins.c
 *
 */
#include "InitPins.h"
#include "fsl_gpio.h"
#include "pin_mux.h"
#include "fsl_port.h"

void InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortA); /* used for I2C */
#if 0
  /* turn on clocking for all the GPIO ports we are going to use */
  CLOCK_EnableClock(kCLOCK_PortB);
  CLOCK_EnableClock(kCLOCK_PortC);
  CLOCK_EnableClock(kCLOCK_PortD);

  /* mux the 5 GPIO Pins for the navigation switch on the HAT */
  gpio_pin_config_t input_config = {
      .pinDirection = kGPIO_DigitalInput,
      .outputLogic = 0U
  };
  GPIO_PinInit(PINS_HATNAVUP_GPIO, PINS_HATNAVUP_PIN, &input_config);
  GPIO_PinInit(PINS_HATNAVDOWN_GPIO, PINS_HATNAVDOWN_PIN, &input_config);
  GPIO_PinInit(PINS_HATNAVLEFT_GPIO, PINS_HATNAVLEFT_PIN, &input_config);
  GPIO_PinInit(PINS_HATNAVRIGHT_GPIO, PINS_HATNAVRIGHT_PIN, &input_config);
  GPIO_PinInit(PINS_HATNAVPUSH_GPIO, PINS_HATNAVPUSH_PIN, &input_config);

  PORT_SetPinMux(PINS_HATNAVUP_PORT, PINS_HATNAVUP_PIN, kPORT_MuxAsGpio);
  PORT_SetPinMux(PINS_HATNAVDOWN_PORT, PINS_HATNAVDOWN_PIN, kPORT_MuxAsGpio);
  PORT_SetPinMux(PINS_HATNAVLEFT_PORT, PINS_HATNAVLEFT_PIN, kPORT_MuxAsGpio);
  PORT_SetPinMux(PINS_HATNAVRIGHT_PORT, PINS_HATNAVRIGHT_PIN, kPORT_MuxAsGpio);
  PORT_SetPinMux(PINS_HATNAVPUSH_PORT, PINS_HATNAVPUSH_PIN, kPORT_MuxAsGpio);

  /* Mux tinyK22 LED plus the 4 LEDS on the HAT */
  gpio_pin_config_t LEDBLUE_config = {
      .pinDirection = kGPIO_DigitalOutput,
      .outputLogic = 1U
  };
  /* Initialize GPIO functionality on pin PTC2 (pin 45)  */
  GPIO_PinInit(BOARD_LEDBLUE_GPIO, BOARD_LEDBLUE_PIN, &LEDBLUE_config);

  gpio_pin_config_t ledHAT_config = {
      .pinDirection = kGPIO_DigitalOutput,
      .outputLogic = 0U
  };
  GPIO_PinInit(PINS_HATLEDBLUE_GPIO, PINS_HATLEDBLUE_PIN, &ledHAT_config);
  GPIO_PinInit(PINS_HATLEDGREEN_GPIO, PINS_HATLEDGREEN_PIN, &ledHAT_config);
  GPIO_PinInit(PINS_HATLEDYELLOW_GPIO, PINS_HATLEDYELLOW_PIN, &ledHAT_config);
  GPIO_PinInit(PINS_HATLEDRED_GPIO, PINS_HATLEDRED_PIN, &ledHAT_config);
  PORT_SetPinMux(PINS_LEDBLUE_PORT, PINS_LEDBLUE_PIN, kPORT_MuxAsGpio);
  PORT_SetPinMux(PINS_HATLEDYELLOW_PORT, PINS_HATLEDYELLOW_PIN, kPORT_MuxAsGpio);
  PORT_SetPinMux(PINS_HATLEDRED_PORT, PINS_HATLEDRED_PIN, kPORT_MuxAsGpio);
  PORT_SetPinMux(PINS_HATLEDGREEN_PORT, PINS_HATLEDGREEN_PIN, kPORT_MuxAsGpio);
  PORT_SetPinMux(PINS_HATLEDBLUE_PORT, PINS_HATLEDBLUE_PIN, kPORT_MuxAsGpio);

  /* mux the SHT alert pin, used to indicate Linux poweroff completed */
  gpio_pin_config_t shutdown_config = {
      .pinDirection = kGPIO_DigitalOutput,
      .outputLogic = 1U
  };
  GPIO_PinInit(PINS_ALERT_GPIO, PINS_ALERT_PIN, &shutdown_config);
  PORT_SetPinMux(PINS_ALERT_PORT, PINS_ALERT_PIN, kPORT_MuxAsGpio);

  /* Mux the UART to the OpenSDA and host side */
  PORT_SetPinMux(PINS_LPUART0_TX_PORT, PINS_LPUART0_TX_PIN, kPORT_MuxAlt7);
  PORT_SetPinMux(PINS_LPUART0_RX_PORT, PINS_LPUART0_RX_PIN, kPORT_MuxAlt7);

  /* Mux the UART0 to the Raspberr Pi */
  PORT_SetPinMux(PORTD, 6U, kPORT_MuxAlt3); /* PORTD6 (pin 63) is configured as UART0_RX */
  PORT_SetPinMux(PORTD, 7U, kPORT_MuxAlt3); /* PORTD7 (pin 64) is configured as UART0_TX */
#endif
}

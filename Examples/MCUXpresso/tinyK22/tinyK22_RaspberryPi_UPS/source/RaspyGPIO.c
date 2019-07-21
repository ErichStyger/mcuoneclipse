/*
 * RaspyGPIO.c
 *
 *  Created on: 20.07.2019
 *      Author: Erich Styger
 */

#include "platform.h"
#if PL_CONFIG_USE_RASPBERRY
#include "RaspyGPIO.h"
#include "McuGPIO.h"
#include "McuWait.h"
#include "leds.h"

static McuGPIO_Handle_t RGPIO_shutdown;   /* pin to signal Raspberry Pi to initiate a shutdown */
#if TINYK22_HAT_VERSION==5
  static McuGPIO_Handle_t RGPIO_wake_gpio;  /* used by the tinyK22 to connect or disconnect the SCL line to the Raspberry Pi which can wake it up */
  static McuGPIO_Handle_t RGPIO_state;      /* used by Raspberry Pi to signal that a shutdown/poweroff is completed */
#endif

void RGPIO_EnableI2CtoRaspy(bool enable) {
#if TINYK22_HAT_VERSION==5
  if (enable) {
    McuGPIO_SetHigh(RGPIO_wake_gpio); /* SCL connected to Raspberry Pi, can wake it up */
  } else {
    McuGPIO_SetLow(RGPIO_wake_gpio); /* SCL *not* connected to Raspberry Pi, I2C activity does not wake it up */
  }
#endif
}

void RGPIO_SignalPowerdown(void) {
  /* driving the pin low requests a poweroff */
  McuGPIO_SetLow(RGPIO_shutdown);   /* driving low */
  McuWait_WaitOSms(50);             /* wait for some time */
  McuGPIO_SetHigh(RGPIO_shutdown);  /* back to high again */
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[64];

  McuShell_SendStatusStr((unsigned char*)"rgpio", (const unsigned char*)"\r\n", io->stdOut);
  if (McuGPIO_IsHigh(RGPIO_shutdown)) {
    McuUtility_strcpy(buf, sizeof(buf), (const unsigned char*)"HIGH");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (const unsigned char*)"LOW");
  }
#if TINYK22_HAT_VERSION==5
  McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)" (GP_0)");
#else
  McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)" (SHT31 Alarm)");
#endif
  McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)": High-Low-High to request power-off\r\n");
  McuShell_SendStatusStr((unsigned char*)"  Shutdown", buf, io->stdOut);
#if TINYK22_HAT_VERSION==5
  if (McuGPIO_IsHigh(RGPIO_wake_gpio)) {
    McuUtility_strcpy(buf, sizeof(buf), (const unsigned char*)"HIGH: SCL connected to Raspy\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (const unsigned char*)"LOW: SCL disconnected to Raspy\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  Wake_Raspy", buf, io->stdOut);


  if (McuGPIO_IsHigh(RGPIO_state)) {
    McuUtility_strcpy(buf, sizeof(buf), (const unsigned char*)"HIGH (GP_1), Raspy down\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (const unsigned char*)"LOW (GP_1), Raspy up\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  State", buf, io->stdOut);
#else
  McuUtility_strcpy(buf, sizeof(buf), (const unsigned char*)"Check the red LED: if on, the Raspy has shutdown\r\n");
  McuShell_SendStatusStr((unsigned char*)"  State", buf, io->stdOut);
#endif
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"rgpio", (unsigned char*)"Group of Raspberry GPIO commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t GATEWAY_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "rgpio help") == 0)
  {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "rgpio status")==0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
  }
  return res;
}

void RGPIO_Deinit(void) {
  RGPIO_shutdown = McuGPIO_DeinitGPIO(RGPIO_shutdown);
#if TINYK22_HAT_VERSION==5
  RGPIO_wake_gpio = McuGPIO_DeinitGPIO(RGPIO_wake_gpio);
  RGPIO_state = McuGPIO_DeinitGPIO(RGPIO_state);
#endif
}

void RGPIO_Init(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);
#if TINYK22_HAT_VERSION==5
  /* wakeup pin which controls the connection of the I2C SCL signal: output pin */
  config.hw.gpio = PINS_WAKE_RASPY_GPIO;
  config.hw.port = PINS_WAKE_RASPY_PORT;
  config.hw.pin = PINS_WAKE_RASPY_PIN;
  config.isInput = false;
  config.isLowOnInit = true;
  RGPIO_wake_gpio = McuGPIO_InitGPIO(&config);

  /* shutdown pin to request a power-off: output pin */
  RGPIO_shutdown = McuGPIO_InitGPIO(&config);

  /* status pin which is used by Raspy to signal that the shutdown has been finished: input pin */
  config.hw.gpio = PINS_GP_1_GPIO;
  config.hw.port = PINS_GP_1_PORT;
  config.hw.pin = PINS_GP_1_PIN;
  config.isInput = true;
  config.isLowOnInit = true;
  RGPIO_state = McuGPIO_InitGPIO(&config);
#else
  /* shutdown pin to request a power-off: output pin */
  config.hw.gpio = PINS_ALERT_GPIO;
  config.hw.port = PINS_ALERT_PORT;
  config.hw.pin = PINS_ALERT_PIN;
  config.isInput = false;
  config.isLowOnInit = false;
  RGPIO_shutdown = McuGPIO_InitGPIO(&config);
  /* note: the RED LED is used by the Raspy to indicate a sucessful shutdown */
#endif
}
#endif /* PL_CONFIG_USE_RASPBERRY */

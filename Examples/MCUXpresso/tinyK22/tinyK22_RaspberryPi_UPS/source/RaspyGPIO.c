/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Handles GPIO pin connection to Raspberry Pi.
 * See shutdown.c for required overlays on the Pi.
 */

#include "platform.h"
#if PL_CONFIG_USE_RASPBERRY
#include "RaspyGPIO.h"
#include "McuGPIO.h"
#include "McuWait.h"
#include "leds.h"
#include "shutdown.h"
#include "McuSHT31.h"
#include "McuUtility.h"

static McuGPIO_Handle_t RGPIO_shutdown;   /* pin to signal Raspberry Pi to initiate a shutdown */
#if TINYK22_HAT_VERSION==5 || TINYK22_HAT_VERSION==6
  static McuGPIO_Handle_t RGPIO_wake_gpio;  /* used by the tinyK22 to connect or disconnect the SCL line to the Raspberry Pi which can wake it up */
#endif
#if PL_CONFIG_USE_POWER_DOWN_STATE_PIN
  /* if we want to power on the Raspy, we cannot use a hardware pin to indicate the shutdown finish */
  static McuGPIO_Handle_t RGPIO_state;      /* used by Raspberry Pi to signal that a shutdown/poweroff is completed */
#endif

void RGPIO_EnableI2CtoRaspy(bool enable) {
#if TINYK22_HAT_VERSION==5 || TINYK22_HAT_VERSION==6
  if (enable) {
    McuGPIO_SetHigh(RGPIO_wake_gpio); /* SCL connected to Raspberry Pi, can wake it up */
  } else {
    McuGPIO_SetLow(RGPIO_wake_gpio); /* SCL *not* connected to Raspberry Pi, I2C activity does not wake it up */
  }
#endif
}

void RGPIO_SetSignalPowerDown(bool setToHigh) {
  /* driving the pin low requests a poweroff */
  if (setToHigh) {
    McuGPIO_SetHigh(RGPIO_shutdown);
  } else {
    McuGPIO_SetLow(RGPIO_shutdown);
  }
}

void RGPIO_SignalPowerdown(void) {
#if PL_CONFIG_USE_POWER_DOWN_RED_LED
  McuLED_Off(hatRedLED); /* make sure we are not driving the poweroff LED */
#elif PL_CONFIG_USE_POWER_DOWN_GREEN_LED
  McuLED_Off(hatGreenLED); /* make sure we are not driving the poweroff LED */
#endif
#if (TINYK22_HAT_VERSION==5 || TINYK22_HAT_VERSION==6) && PL_CONFIG_USE_POWER_ON /* disconnect I2C bus to Raspy, otherwise a falling SCL can wakeup the Raspy */
  RGPIO_EnableI2CtoRaspy(false);
#endif
  /* driving the pin low requests a poweroff */
  RGPIO_SetSignalPowerDown(false);  /* driving low */
  McuWait_WaitOSms(10);
  RGPIO_SetSignalPowerDown(true);   /* back to high again */
}

#if TINYK22_HAT_VERSION==5 || TINYK22_HAT_VERSION==6
void RGPIO_ConnectSCL(bool yes) {
  if (yes) {
    McuGPIO_SetHigh(RGPIO_wake_gpio);
  } else {
    McuGPIO_SetLow(RGPIO_wake_gpio);
  }
}
#endif

#if PL_CONFIG_USE_POWER_ON
void RGPIO_PowerOn(void) {
  RGPIO_ConnectSCL(true);
  /* drive SCL low here: to make it simple, just send a command to the temperature sensor */
  (void)McuSHT31_Reset();
  McuWait_WaitOSms(500);
  RGPIO_ConnectSCL(false);
}
#endif

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[64];

  McuShell_SendStatusStr((unsigned char*)"rgpio", (const unsigned char*)"\r\n", io->stdOut);
  if (McuGPIO_IsHigh(RGPIO_shutdown)) {
    McuUtility_strcpy(buf, sizeof(buf), (const unsigned char*)"HIGH");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (const unsigned char*)"LOW");
  }
#if TINYK22_HAT_VERSION==5 || TINYK22_HAT_VERSION==6
  McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)" (GP_0, BCM17)");
#else
  McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)" (SHT31 Alert, BCM4)");
#endif
  McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)": falling edge to request power-off\r\n");
  McuShell_SendStatusStr((unsigned char*)"  Shutdown", buf, io->stdOut);
#if PL_CONFIG_USE_POWER_DOWN_STATE_PIN
  if (McuGPIO_IsHigh(RGPIO_state)) {
    McuUtility_strcpy(buf, sizeof(buf), (const unsigned char*)"HIGH (GP_1, BCM18), Raspy down or not powered\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (const unsigned char*)"LOW (GP_1, BCM18), Raspy up\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  State", buf, io->stdOut);
#endif
#if TINYK22_HAT_VERSION>=5
  if (McuGPIO_IsHigh(RGPIO_wake_gpio)) {
    McuUtility_strcpy(buf, sizeof(buf), (const unsigned char*)"Wake_Raspy HIGH: SCL connected, falling edge can wake-up Raspy\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (const unsigned char*)"Wake_Raspy LOW: SCL not connected to Raspy\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  Wake", buf, io->stdOut);
#elif PL_CONFIG_USE_POWER_DOWN_RED_LED
  McuUtility_strcpy(buf, sizeof(buf), (const unsigned char*)"Check the HAT red LED: if on, the Raspy has shutdown\r\n");
  McuShell_SendStatusStr((unsigned char*)"  State", buf, io->stdOut);
#elif PL_CONFIG_USE_POWER_DOWN_GREEN_LED
  McuUtility_strcpy(buf, sizeof(buf), (const unsigned char*)"Check the HAT green LED: if on, the Raspy has shutdown\r\n");
  McuShell_SendStatusStr((unsigned char*)"  State", buf, io->stdOut);
#endif
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"rgpio", (unsigned char*)"Group of Raspberry GPIO commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  shutdown", (unsigned char*)"Trigger Raspberry shutdown sequence\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  shutdown assert|deassert", (unsigned char*)"Assert (low) or deassert (high) the shutdown pin\r\n", io->stdOut);
#if TINYK22_HAT_VERSION>=5
  McuShell_SendHelpStr((unsigned char*)"  wake connect|disconnect", (unsigned char*)"Connect SCL to Raspy\r\n", io->stdOut);
#endif
#if PL_CONFIG_USE_POWER_ON
  McuShell_SendHelpStr((unsigned char*)"  poweron", (unsigned char*)"Drives BCM3 (SCL) low to power up Raspy\r\n", io->stdOut);
#endif
  return ERR_OK;
}

uint8_t RGPIO_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
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
#if TINYK22_HAT_VERSION==5 || TINYK22_HAT_VERSION==6
  } else if (McuUtility_strcmp((char*)cmd, "rgpio wake connect")==0) {
    *handled = TRUE;
    RGPIO_ConnectSCL(true);
  } else if (McuUtility_strcmp((char*)cmd, "rgpio wake disconnect")==0) {
    *handled = TRUE;
    RGPIO_ConnectSCL(false);
#endif
#if PL_CONFIG_USE_POWER_ON
  } else if (McuUtility_strcmp((char*)cmd, "rgpio poweron")==0) {
    *handled = TRUE;
    RGPIO_PowerOn();
#endif
  } else if (McuUtility_strcmp((char*)cmd, "rgpio shutdown assert")==0) {
    *handled = TRUE;
    RGPIO_SetSignalPowerDown(false); /* put it to LOW state */
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "rgpio shutdown deassert")==0) {
    *handled = TRUE;
    RGPIO_SetSignalPowerDown(true); /* put it to HIGH state */
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "rgpio shutdown")==0) {
    *handled = TRUE;
    SHUTDOWN_RequestPowerOff();
#if PL_CONFIG_USE_POWER_DOWN_STATE_PIN
    int timeout = 15;

    McuShell_SendStr((unsigned char*)"Waiting for Raspy to signal power down", io->stdOut);
    do {
      McuShell_SendStr((unsigned char*)".", io->stdOut); /* progress indicator */
      vTaskDelay(pdMS_TO_TICKS(1000));
      timeout--;
    } while(McuGPIO_IsLow(RGPIO_state) && timeout>0);
    if (timeout==0) {
      McuShell_SendStr((unsigned char*)" Timeout!\r\n", io->stdOut);
      for(int i=0; i<3; i++) {
        McuLED_Toggle(hatRedLED); /* visual indication of error */
        vTaskDelay(pdMS_TO_TICKS(100));
      }
      McuLED_Off(hatRedLED);
    } else {
      McuShell_SendStr((unsigned char*)" done!\r\n", io->stdOut);
      McuLED_On(hatRedLED); /* visual indication */
    }
#elif PL_CONFIG_USE_POWER_ON
    McuShell_SendStr((unsigned char*)"Please wait until there is no Raspberry activity anymore\r\n", io->stdOut);
#elif PL_CONFIG_USE_POWER_DOWN_RED_LED
    McuShell_SendStr((unsigned char*)"Please wait for the red LED\r\n", io->stdOut);
#elif PL_CONFIG_USE_POWER_DOWN_GREEN_LED
    McuShell_SendStr((unsigned char*)"Please wait for the green LED\r\n", io->stdOut);
#endif
  }
  return res;
}

void RGPIO_Deinit(void) {
  RGPIO_shutdown = McuGPIO_DeinitGPIO(RGPIO_shutdown);
#if TINYK22_HAT_VERSION==5 || TINYK22_HAT_VERSION==6
  RGPIO_wake_gpio = McuGPIO_DeinitGPIO(RGPIO_wake_gpio);
#endif
#if PL_CONFIG_USE_POWER_DOWN_STATE_PIN
  RGPIO_state = McuGPIO_DeinitGPIO(RGPIO_state);
#endif
}

void RGPIO_Init(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);
#if PL_CONFIG_USE_POWER_DOWN_STATE_PIN
  /* status pin which is used by Raspberry to signal to tinyK22 that the shutdown has been finished: input pin */
#if TINYK22_HAT_VERSION==3 || TINYK22_HAT_VERSION==4
  /* configure gpio-poweroff to use the Red LED to indicate power-off in /boot/config.txt:
   # State: Pin from Raspy which goes HIGH after a power down. Disable this for power-up functionality.
   # Board V3 & V4: Using physical 40, BCM21 (Red LED)
   dtoverlay=gpio-poweroff,gpiopin=21
   */
  /* nothing needed as using the (already) configured red LED for this */
#elif TINYK22_HAT_VERSION==5 || TINYK22_HAT_VERSION==6
  /* enabling the gpio-poweroff overlays will prevent the ability to boot by driving GPIO3 (SCL)low!
  # State: Pin from Raspy which goes HIGH after a power down. Disable this for power-up functionality.
  # Board V5: Using tinyGP_1 (physical 12, BCM18)
  #dtoverlay=gpio-poweroff,gpiopin=18
   */
  config.hw.gpio = PINS_GP_1_GPIO;
  config.hw.port = PINS_GP_1_PORT;
  config.hw.pin = PINS_GP_1_PIN;
#else
  #error "unknown configuration or not supported"
#endif
  config.isInput = true;
  config.isHighOnInit = false;
  RGPIO_state = McuGPIO_InitGPIO(&config);
#endif /* PL_CONFIG_USE_POWER_DOWN_STATE_PIN */

#if TINYK22_HAT_VERSION==5 || TINYK22_HAT_VERSION==6
  /* wake-up pin which controls the connection of the I2C SCL signal: output pin */
  config.hw.gpio = PINS_WAKE_RASPY_GPIO;
  config.hw.port = PINS_WAKE_RASPY_PORT;
  config.hw.pin = PINS_WAKE_RASPY_PIN;
  config.isInput = false;
  config.isHighOnInit = false;
  RGPIO_wake_gpio = McuGPIO_InitGPIO(&config);

  /* shutdown pin to request a power-off: output pin */
  config.hw.gpio = PINS_GP_0_GPIO;
  config.hw.port = PINS_GP_0_PORT;
  config.hw.pin = PINS_GP_0_PIN;
  config.isInput = false;
  config.isHighOnInit = true; /* a falling edge causes a power-down */
  RGPIO_shutdown = McuGPIO_InitGPIO(&config);
#else /* V3 & V4: we cannot wake-up the Pi, only request a power-off */
  /* power-off request pin: output pin */
  config.hw.gpio = PINS_ALERT_GPIO;
  config.hw.port = PINS_ALERT_PORT;
  config.hw.pin = PINS_ALERT_PIN;
  config.isInput = false;
  config.isHighOnInit = true; /* a falling edge causes a power-off */
  RGPIO_shutdown = McuGPIO_InitGPIO(&config);
  /* note: the RED LED is used by the Raspy to indicate a successful shutdown */
#endif
}
#endif /* PL_CONFIG_USE_RASPBERRY */

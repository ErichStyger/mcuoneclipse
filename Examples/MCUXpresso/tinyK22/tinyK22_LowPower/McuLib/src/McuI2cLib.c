/*
 * Copyright (c) 2019-2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuI2cLibconfig.h"

#if McuLib_CONFIG_MCUI2CLIB_ENABLED
#include "McuLib.h"
#include "McuI2cLib.h"
#include "fsl_i2c.h"
#include "McuGPIO.h"
#include "McuWait.h"
#if McuLib_CONFIG_CPU_IS_KINETIS
  #include "fsl_port.h"
#elif McuLib_CONFIG_CPU_IS_LPC
  #include "pin_mux.h"
  #include "fsl_iocon.h"
#endif
#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845
  #include "fsl_swm.h"
#endif

static uint8_t i2cSlaveDeviceAddr; /* used to store the current I2C device address used */

uint8_t McuI2cLib_SendBlock(void *Ptr, uint16_t Siz, uint16_t *Snt) {
  status_t status;

#if McuLib_CONFIG_CPU_IS_KINETIS
  I2C_MasterClearStatusFlags(MCUI2CLIB_CONFIG_I2C_MASTER_BASEADDR, kI2C_ArbitrationLostFlag | kI2C_IntPendingFlag | kI2C_StartDetectFlag | kI2C_StopDetectFlag);
#elif McuLib_CONFIG_CPU_IS_LPC
  I2C_MasterClearStatusFlags(MCUI2CLIB_CONFIG_I2C_MASTER_BASEADDR,  kI2C_MasterPendingFlag | kI2C_MasterArbitrationLostFlag | kI2C_MasterStartStopErrorFlag);
#endif
  status = I2C_MasterStart(MCUI2CLIB_CONFIG_I2C_MASTER_BASEADDR, i2cSlaveDeviceAddr, kI2C_Write);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
#if MCUI2CLIB_CONFIG_ADD_DELAY
  McuWait_Waitus(MCUI2CLIB_CONFIG_ADD_DELAY_US);
#endif
  status = I2C_MasterWriteBlocking(MCUI2CLIB_CONFIG_I2C_MASTER_BASEADDR, Ptr, Siz, kI2C_TransferNoStartFlag|kI2C_TransferNoStopFlag);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  *Snt = Siz;
  return ERR_OK;
}

uint8_t McuI2cLib_RecvBlock(void *Ptr, uint16_t Siz, uint16_t *Rcv) {
  status_t status;

  status = I2C_MasterRepeatedStart(MCUI2CLIB_CONFIG_I2C_MASTER_BASEADDR, i2cSlaveDeviceAddr, kI2C_Read);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
#if MCUI2CLIB_CONFIG_ADD_DELAY
  McuWait_Waitus(MCUI2CLIB_CONFIG_ADD_DELAY_US);
#endif
  status = I2C_MasterReadBlocking(MCUI2CLIB_CONFIG_I2C_MASTER_BASEADDR, Ptr, Siz, kI2C_TransferDefaultFlag);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  *Rcv = Siz;
  return ERR_OK;
}

uint8_t McuI2cLib_SendStop(void) {
  status_t status;

  status = I2C_MasterStop(MCUI2CLIB_CONFIG_I2C_MASTER_BASEADDR);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t McuI2cLib_SelectSlave(uint8_t Slv) {
  i2cSlaveDeviceAddr = Slv;
  return ERR_OK;
}

static void McuI2cLib_ReleaseBus(void) {
  McuGPIO_Handle_t sdaPin, sclPin;
  McuGPIO_Config_t config;
  uint8_t i = 0;

  McuGPIO_GetDefaultConfig(&config);
  config.isInput = false;
  config.isHighOnInit = true;
  config.hw.gpio = MCUI2CLIB_CONFIG_SDA_GPIO;
  config.hw.pin = MCUI2CLIB_CONFIG_SDA_GPIO_PIN;
  config.hw.port = MCUI2CLIB_CONFIG_SDA_GPIO_PORT;
  sdaPin = McuGPIO_InitGPIO(&config);

  config.hw.gpio = MCUI2CLIB_CONFIG_SCL_GPIO;
  config.hw.pin = MCUI2CLIB_CONFIG_SCL_GPIO_PIN;
  config.hw.port = MCUI2CLIB_CONFIG_SCL_GPIO_PORT;
  sclPin = McuGPIO_InitGPIO(&config);

  /* Drive SDA low first to simulate a start */
  McuGPIO_SetLow(sdaPin);
  McuWait_Waitus(10);
  /* Send 9 pulses on SCL and keep SDA high */
  for (i = 0; i < 9; i++) {
    McuGPIO_SetLow(sclPin);
    McuWait_Waitus(10);

    McuGPIO_SetHigh(sdaPin);
    McuWait_Waitus(10);

    McuGPIO_SetHigh(sclPin);
    McuWait_Waitus(20);
  }
  /* Send stop */
  McuGPIO_SetLow(sclPin);
  McuWait_Waitus(10);

  McuGPIO_SetLow(sdaPin);
  McuWait_Waitus(10);

  McuGPIO_SetLow(sclPin);
  McuWait_Waitus(10);

  McuGPIO_SetHigh(sdaPin);
  McuWait_Waitus(10);
  /* cleanup */
  sdaPin = McuGPIO_DeinitGPIO(sdaPin);
  sclPin = McuGPIO_DeinitGPIO(sclPin);
}

/* mux as I2C pins */
static void McuI2cLib_ConfigureI2cPins(void) {
#if    McuLib_CONFIG_CPU_IS_KINETIS \
    || McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16 \
    || McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S69 \
    || McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845
  MCUI2CLIB_CONFIG_MUX_I2C_PINS();
#else
  #error "unknown configuration and MCU"
#endif
}

void McuI2cLib_Deinit(void) {
}

void McuI2cLib_Init(void) {
  McuI2cLib_ReleaseBus();
#if McuLib_CONFIG_CPU_IS_KINETIS \
     || McuLib_CONFIG_CPU_IS_LPC55xx && McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16 \
     || McuLib_CONFIG_CPU_IS_LPC55xx && McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S69 \
     || McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845
  MCUI2CLIB_CONFIG_CLOCK_SELECT();
#else
  #error "unknown configuration and MCU"
#endif

  McuI2cLib_ConfigureI2cPins();

  i2c_master_config_t masterConfig;
  uint32_t sourceClock;
  /*
   * masterConfig->baudRate_Bps = 100000U;
   * masterConfig->enableStopHold = false;
   * masterConfig->glitchFilterWidth = 0U;
   * masterConfig->enableMaster = true;
   */
  I2C_MasterGetDefaultConfig(&masterConfig);
  masterConfig.baudRate_Bps = MCUI2CLIB_CONFIG_I2C_BAUDRATE;
  sourceClock = MCUI2CLIB_CONFIG_I2C_MASTER_CLK_FREQ;
  I2C_MasterInit(MCUI2CLIB_CONFIG_I2C_MASTER_BASEADDR, &masterConfig, sourceClock);
}
#endif /* McuGenericI2C_CONFIG_INTERFACE_HEADER_FILE */

/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_HW_I2C
#include "i2clibconfig.h"
#include "McuLib.h"
#include "i2clib.h"
#include "fsl_i2c.h"
#include "McuGPIO.h"
#include "McuWait.h"
#if McuLib_CONFIG_CPU_IS_KINETIS
  #include "fsl_port.h"
#elif McuLib_CONFIG_CPU_IS_LPC
  #include "pin_mux.h"
  #include "fsl_iocon.h"
#endif

static uint8_t i2cSlaveDeviceAddr;

uint8_t I2CLIB_SendBlock(void *Ptr, uint16_t Siz, uint16_t *Snt) {
  status_t status;

#if McuLib_CONFIG_CPU_IS_KINETIS
  I2C_MasterClearStatusFlags(I2C_MASTER_BASEADDR, kI2C_ArbitrationLostFlag | kI2C_IntPendingFlag | kI2C_StartDetectFlag | kI2C_StopDetectFlag);
#elif McuLib_CONFIG_CPU_IS_LPC
  I2C_MasterClearStatusFlags(I2C_MASTER_BASEADDR,  kI2C_MasterPendingFlag | kI2C_MasterArbitrationLostFlag | kI2C_MasterStartStopErrorFlag);
#endif
  status = I2C_MasterStart(I2C_MASTER_BASEADDR, i2cSlaveDeviceAddr, kI2C_Write);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
#if I2C_ADD_DELAY
  McuWait_Waitus(I2C_ADD_DELAY_US);
#endif
  status = I2C_MasterWriteBlocking(I2C_MASTER_BASEADDR, Ptr, Siz, kI2C_TransferNoStartFlag|kI2C_TransferNoStopFlag);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  *Snt = Siz;
  return ERR_OK;
}

uint8_t I2CLIB_RecvBlock(void *Ptr, uint16_t Siz, uint16_t *Rcv) {
  status_t status;

  status = I2C_MasterRepeatedStart(I2C_MASTER_BASEADDR, i2cSlaveDeviceAddr, kI2C_Read);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
#if I2C_ADD_DELAY
  McuWait_Waitus(I2C_ADD_DELAY_US);
#endif
  status = I2C_MasterReadBlocking(I2C_MASTER_BASEADDR, Ptr, Siz, kI2C_TransferDefaultFlag);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  *Rcv = Siz;
  return ERR_OK;
}

uint8_t I2CLIB_SendStop(void) {
  status_t status;

  status = I2C_MasterStop(I2C_MASTER_BASEADDR);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t I2CLIB_SelectSlave(uint8_t Slv) {
  i2cSlaveDeviceAddr = Slv;
  return ERR_OK;
}

static void I2CLIB_ReleaseBus(void) {
  McuGPIO_Handle_t sdaPin, sclPin;
  McuGPIO_Config_t config;
  uint8_t i = 0;

  /* muxing */
#if McuLib_CONFIG_CPU_IS_KINETIS
  /* Muxing is done inside McuGPIO for Kinetis */
#elif McuLib_CONFIG_CPU_IS_LPC  /*! \todo make it generic for LPC too */
  /*
   * Bit 3:0 FUNC
   *   5 (0101): I2C
   * Bit 5:4 MODE (resistor): 00 (inactive), 01 (pull-down), 10 (pull-up), 11 (repeater)
   */
  //IOCON->PIO[I2CLIB_SCL_GPIO_PORT][I2CLIB_SCL_GPIO_PIN] &= 0xFFF1; /* scl */
  //IOCON->PIO[I2CLIB_SDA_GPIO_PORT][I2CLIB_SDA_GPIO_PIN] &= 0xFFF1; /* sda */
  BOARD_InitI2cPinsAsGPIO(); /* mux pins using Pins tool */
#endif

  McuGPIO_GetDefaultConfig(&config);
  config.isInput = false;
  config.isHighOnInit = true;
  config.hw.gpio = I2CLIB_SDA_GPIO;
  config.hw.pin = I2CLIB_SDA_GPIO_PIN;
  config.hw.port = I2CLIB_SDA_GPIO_PORT;
  sdaPin = McuGPIO_InitGPIO(&config);

  config.hw.gpio = I2CLIB_SCL_GPIO;
  config.hw.pin = I2CLIB_SCL_GPIO_PIN;
  config.hw.port = I2CLIB_SCL_GPIO_PORT;
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
static void I2CLIB_ConfigurePins(void) {
#if McuLib_CONFIG_CPU_IS_KINETIS
  /* clock enable has to be done outside (e.g. in Pins tool or in platform.c) */
  /* I2C SCL Pin */
  PORT_SetPinMux(I2CLIB_SCL_GPIO_PORT, I2CLIB_SCL_GPIO_PIN, I2CLIB_CONFIG_SCL_GPIO_MUXING);
  I2CLIB_SCL_GPIO_PORT->PCR[I2CLIB_SCL_GPIO_PIN] = ((I2CLIB_SCL_GPIO_PORT->PCR[I2CLIB_SCL_GPIO_PIN] &
                    /* Mask bits to zero which are setting */
                    (~(PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK)))
                   /* Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin. */
                   | (uint32_t)(PORT_PCR_PE_MASK)
                   /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is
                    * configured as a digital output. */
                   | PORT_PCR_ODE(kPORT_OpenDrainEnable));

  /* I2C SDA Pin */
  PORT_SetPinMux(I2CLIB_SDA_GPIO_PORT, I2CLIB_SDA_GPIO_PIN, I2CLIB_CONFIG_SDA_GPIO_MUXING);
  I2CLIB_SDA_GPIO_PORT->PCR[I2CLIB_SDA_GPIO_PIN] = ((I2CLIB_SDA_GPIO_PORT->PCR[I2CLIB_SDA_GPIO_PIN] &
                    /* Mask bits to zero which are setting */
                    (~(PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK)))
                   /* Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin. */
                   | (uint32_t)(PORT_PCR_PE_MASK)
                   /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is
                    * configured as a digital output. */
                   | PORT_PCR_ODE(kPORT_OpenDrainEnable));
#elif McuLib_CONFIG_CPU_IS_LPC
  BOARD_InitI2cPins(); /* Mux GPIO pins using the Pins tool */
#if 0
  #define IOCON_PIO_FUNC5 0x05u         /*!<@brief Selects pin function 5 */

  const uint32_t port1_pin20_config = (/* Pin is configured as FC4_TXD_SCL_MISO_WS */
                                       IOCON_PIO_FUNC5 |
                                       /* No addition pin function */
                                       IOCON_PIO_MODE_INACT |
                                       /* Standard mode, output slew rate control is enabled */
                                       IOCON_PIO_SLEW_STANDARD |
                                       /* Input function is not inverted */
                                       IOCON_PIO_INV_DI |
                                       /* Enables digital function */
                                       IOCON_PIO_DIGITAL_EN |
                                       /* Open drain is disabled */
                                       IOCON_PIO_OPENDRAIN_DI);
  /* PORT1 PIN20 (coords: 4) is configured as FC4_TXD_SCL_MISO_WS */
  IOCON_PinMuxSet(IOCON, 1U, 20U, port1_pin20_config);

  const uint32_t port1_pin21_config = (/* Pin is configured as FC4_RXD_SDA_MOSI_DATA */
                                       IOCON_PIO_FUNC5 |
                                       /* No addition pin function */
                                       IOCON_PIO_MODE_INACT |
                                       /* Standard mode, output slew rate control is enabled */
                                       IOCON_PIO_SLEW_STANDARD |
                                       /* Input function is not inverted */
                                       IOCON_PIO_INV_DI |
                                       /* Enables digital function */
                                       IOCON_PIO_DIGITAL_EN |
                                       /* Open drain is disabled */
                                       IOCON_PIO_OPENDRAIN_DI);
  /* PORT1 PIN21 (coords: 30) is configured as FC4_RXD_SDA_MOSI_DATA */
  IOCON_PinMuxSet(IOCON, 1U, 21U, port1_pin21_config);
#endif
#endif
}

void I2CLIB_Init(void) {
  I2CLIB_ReleaseBus();
#if McuLib_CONFIG_CPU_IS_LPC55xx && McuLib_CONFIG_CORTEX_M==33 /* LPC55S69 */
  /* attach 12 MHz clock to FLEXCOMM4 (I2C master) */
  CLOCK_AttachClk(kFRO12M_to_FLEXCOMM4);
#elif McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==0 /* LPC845 */
  /* Select the main clock as source clock of I2C0. */
  CLOCK_Select(kI2C0_Clk_From_MainClk);
#endif

  I2CLIB_ConfigurePins();

  i2c_master_config_t masterConfig;
  uint32_t sourceClock;
  /*
   * masterConfig->baudRate_Bps = 100000U;
   * masterConfig->enableStopHold = false;
   * masterConfig->glitchFilterWidth = 0U;
   * masterConfig->enableMaster = true;
   */
  I2C_MasterGetDefaultConfig(&masterConfig);
  masterConfig.baudRate_Bps = I2C_BAUDRATE;
  sourceClock = I2C_MASTER_CLK_FREQ;
  I2C_MasterInit(I2C_MASTER_BASEADDR, &masterConfig, sourceClock);
}
#endif /* PL_CONFIG_USE_HW_I2C */

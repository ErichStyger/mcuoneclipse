/*
 * i2clib.c
 *
 *  Created on: 08.06.2019
 *      Author: Erich Styger
 */

#include "platform.h"
#include "i2clib.h"
#include "fsl_i2c.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "McuFXOS8700.h"

#define EXAMPLE_I2C_MASTER_BASEADDR     I2C0

static uint8_t i2cSlaveDeviceAddr;

uint8_t I2CLIB_ReadAddress(uint8_t i2cAddr, uint8_t *memAddr, uint8_t memAddrSize, uint8_t *data, uint16_t dataSize) {
  i2c_master_transfer_t masterXfer;
  status_t res;

  memset(&masterXfer, 0, sizeof(masterXfer));
  /* subAddress = memory address on device, data = g_master_rxBuff - read from slave.
    start + slaveaddress(w) + subAddress + repeated start + slaveaddress(r) + rx data buffer + stop */
  masterXfer.slaveAddress = i2cAddr;
  masterXfer.direction = kI2C_Read;
  masterXfer.subaddress = *memAddr;
  masterXfer.subaddressSize = memAddrSize; /* assuming 1! */
  masterXfer.data = data;
  masterXfer.dataSize = dataSize;
  masterXfer.flags = kI2C_TransferDefaultFlag;

  res = I2C_MasterTransferBlocking(EXAMPLE_I2C_MASTER_BASEADDR, &masterXfer);
  if (res!=kStatus_Success) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t I2CLIB_SendBlock(void *Ptr, uint16_t Siz, uint16_t *Snt) {
  status_t status;

  status = I2C_MasterStart(EXAMPLE_I2C_MASTER_BASEADDR, i2cSlaveDeviceAddr, kI2C_Write);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  status = I2C_MasterWriteBlocking(EXAMPLE_I2C_MASTER_BASEADDR, Ptr, Siz, kI2C_TransferNoStopFlag);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  *Snt = Siz;
  return ERR_OK;
}

uint8_t I2CLIB_SendBlockContinue(void *Ptr, uint16_t Siz, uint16_t *Snt) {
  status_t status;

  status = I2C_MasterWriteBlocking(EXAMPLE_I2C_MASTER_BASEADDR, Ptr, Siz, kI2C_TransferNoStopFlag);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  *Snt = Siz;
  return ERR_OK;
}

uint8_t I2CLIB_RecvBlockCustom(void *Ptr, uint16_t Siz, uint16_t *Rcv, I2CLIB_EnumStartFlags flagsStart, I2CLIB_EnumAckFlags flagsAck) {
  status_t status;

  if (flagsStart==I2CLIB_SEND_START) {
    status = I2C_MasterStart(EXAMPLE_I2C_MASTER_BASEADDR, i2cSlaveDeviceAddr, kI2C_Write);
  }
  status = I2C_MasterReadBlocking(EXAMPLE_I2C_MASTER_BASEADDR, Ptr, Siz, kI2C_TransferNoStopFlag);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  *Rcv = Siz;
  if (flagsAck==I2CLIB_SEND_LAST_ACK) {
    /* \todo */
  }
  return ERR_OK;
}

uint8_t I2CLIB_RecvBlock(void *Ptr, uint16_t Siz, uint16_t *Rcv) {
  status_t status;

 // status = I2C_MasterStart(EXAMPLE_I2C_MASTER_BASEADDR, i2cSlaveDeviceAddr, kI2C_Read);
 // if (status!=kStatus_Success) {
 //   return ERR_FAILED;
 // }
  status = I2C_MasterReadBlocking(EXAMPLE_I2C_MASTER_BASEADDR, Ptr, Siz, kI2C_TransferNoStartFlag|kI2C_TransferRepeatedStartFlag|kI2C_TransferNoStopFlag);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  *Rcv = Siz;
  return ERR_OK;
}

uint8_t I2CLIB_SendStop(void) {
  status_t status;

  status = I2C_MasterStop(EXAMPLE_I2C_MASTER_BASEADDR);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t I2CLIB_SelectSlave(uint8_t Slv) {
  i2cSlaveDeviceAddr = Slv;
  return ERR_OK;
}

#define I2C_MASTER_CLK_SRC              I2C0_CLK_SRC
#define I2C_MASTER_CLK_FREQ             CLOCK_GetFreq(I2C0_CLK_SRC)

#define I2C_MASTER_SLAVE_ADDR_7BIT      McuFXOS8700_I2C_ADDR
#define I2C_BAUDRATE 100000U
#define I2C_DATA_LENGTH 33U

uint8_t g_master_txBuff[I2C_DATA_LENGTH];
uint8_t g_master_rxBuff[I2C_DATA_LENGTH];
volatile bool g_MasterCompletionFlag = false;

#define I2C_RELEASE_SDA_PORT PORTB
#define I2C_RELEASE_SCL_PORT PORTB
#define I2C_RELEASE_SDA_GPIO GPIOB
#define I2C_RELEASE_SDA_PIN 3U
#define I2C_RELEASE_SCL_GPIO GPIOB
#define I2C_RELEASE_SCL_PIN 2U
#define I2C_RELEASE_BUS_COUNT 100U

static void i2c_release_bus_delay(void) {
  uint32_t i = 0;
  for (i = 0; i < I2C_RELEASE_BUS_COUNT; i++) {
      __NOP();
  }
}

static void I2CLIB_ReleaseBus(void) {
    uint8_t i = 0;
    gpio_pin_config_t pin_config;
    port_pin_config_t i2c_pin_config = {0};

    /* Config pin mux as gpio */
    i2c_pin_config.pullSelect = kPORT_PullUp;
    i2c_pin_config.mux = kPORT_MuxAsGpio;

    pin_config.pinDirection = kGPIO_DigitalOutput;
    pin_config.outputLogic = 1U;
    CLOCK_EnableClock(kCLOCK_PortB);
    PORT_SetPinConfig(I2C_RELEASE_SCL_PORT, I2C_RELEASE_SCL_PIN, &i2c_pin_config);
    PORT_SetPinConfig(I2C_RELEASE_SDA_PORT, I2C_RELEASE_SDA_PIN, &i2c_pin_config);

    GPIO_PinInit(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, &pin_config);
    GPIO_PinInit(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, &pin_config);

    /* Drive SDA low first to simulate a start */
    GPIO_PinWrite(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 0U);
    i2c_release_bus_delay();

    /* Send 9 pulses on SCL and keep SDA high */
    for (i = 0; i < 9; i++)
    {
        GPIO_PinWrite(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 0U);
        i2c_release_bus_delay();

        GPIO_PinWrite(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 1U);
        i2c_release_bus_delay();

        GPIO_PinWrite(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 1U);
        i2c_release_bus_delay();
        i2c_release_bus_delay();
    }

    /* Send stop */
    GPIO_PinWrite(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_PinWrite(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_PinWrite(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 1U);
    i2c_release_bus_delay();

    GPIO_PinWrite(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 1U);
    i2c_release_bus_delay();
}

static void I2CLIB_ConfigurePins(void) {
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);

    /* PORTB2 (pin 37) is configured as I2C0_SCL */
    PORT_SetPinMux(PORTB, 2U, kPORT_MuxAlt2);

    PORTB->PCR[2] = ((PORTB->PCR[2] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK)))

                     /* Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin. */
                     | (uint32_t)(PORT_PCR_PE_MASK)

                     /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is
                      * configured as a digital output. */
                     | PORT_PCR_ODE(kPORT_OpenDrainEnable));

    /* PORTB3 (pin 38) is configured as I2C0_SDA */
    PORT_SetPinMux(PORTB, 3U, kPORT_MuxAlt2);

    PORTB->PCR[3] = ((PORTB->PCR[3] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK)))

                     /* Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin. */
                     | (uint32_t)(PORT_PCR_PE_MASK)

                     /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is
                      * configured as a digital output. */
                     | PORT_PCR_ODE(kPORT_OpenDrainEnable));
}


void I2CLIB_Init(void) {
  I2CLIB_ReleaseBus();
  I2CLIB_ConfigurePins();

  i2c_master_config_t masterConfig;
  uint32_t sourceClock;

#if 0
  /* Set up i2c master to send data to slave*/
  /* First data in txBuff is data length of the transmiting data. */
  g_master_txBuff[0] = I2C_DATA_LENGTH - 1U;
  for (uint32_t i = 1U; i < I2C_DATA_LENGTH; i++)
  {
      g_master_txBuff[i] = i - 1;
  }
#endif
  /*
   * masterConfig->baudRate_Bps = 100000U;
   * masterConfig->enableStopHold = false;
   * masterConfig->glitchFilterWidth = 0U;
   * masterConfig->enableMaster = true;
   */
  I2C_MasterGetDefaultConfig(&masterConfig);
  masterConfig.baudRate_Bps = I2C_BAUDRATE;
  sourceClock = I2C_MASTER_CLK_FREQ;
  I2C_MasterInit(EXAMPLE_I2C_MASTER_BASEADDR, &masterConfig, sourceClock);

#if 0
  i2c_master_transfer_t masterXfer;
  memset(&masterXfer, 0, sizeof(masterXfer));

  /* subAddress = 0x01, data = g_master_txBuff - write to slave.
    start + slaveaddress(w) + subAddress + length of data buffer + data buffer + stop*/
  uint8_t deviceAddress = McuFXOS8700_WHO_AM_I;
#if 0
  masterXfer.slaveAddress = I2C_MASTER_SLAVE_ADDR_7BIT;
  masterXfer.direction = kI2C_Write;
  masterXfer.subaddress = (uint32_t)deviceAddress;
  masterXfer.subaddressSize = 1;
  masterXfer.data = g_master_txBuff;
  masterXfer.dataSize = I2C_DATA_LENGTH;
  masterXfer.flags = kI2C_TransferDefaultFlag;

  I2C_MasterTransferBlocking(EXAMPLE_I2C_MASTER_BASEADDR, &masterXfer);
#endif
  /* subAddress = 0x01, data = g_master_rxBuff - read from slave.
    start + slaveaddress(w) + subAddress + repeated start + slaveaddress(r) + rx data buffer + stop */
  masterXfer.slaveAddress = I2C_MASTER_SLAVE_ADDR_7BIT;
  masterXfer.direction = kI2C_Read;
  masterXfer.subaddress = (uint32_t)deviceAddress;
  masterXfer.subaddressSize = 1;
  masterXfer.data = g_master_rxBuff;
  masterXfer.dataSize = 1;
  masterXfer.flags = kI2C_TransferDefaultFlag;

  status_t res;

  res = I2C_MasterTransferBlocking(EXAMPLE_I2C_MASTER_BASEADDR, &masterXfer);
  if (res!=kStatus_Success) {
    for(;;) {}
  }
#endif
#if 1
  {
  uint8_t res;
  uint8_t whoami;

  res = McuFXOS8700_WhoAmI(&whoami);
  if (res!=ERR_OK) {
    for(;;){}
  }
  }
#endif
}

/*
 * Copyright (c) 2019-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuI2cLibconfig.h"

#if McuLib_CONFIG_MCUI2CLIB_ENABLED
#include "McuLib.h"
#include "McuI2cLib.h"
#if MCUI2CLIB_CONFIG_I2C_RELEASE_BUS
  #include "McuGPIO.h"
#endif
#include "McuWait.h"
#include "McuRTOS.h"
#include "McuLog.h"
#if McuLib_CONFIG_CPU_IS_KINETIS
  #include "fsl_port.h"
  #include "fsl_i2c.h"
#elif McuLib_CONFIG_CPU_IS_LPC
  #include "pin_mux.h"
  #include "fsl_iocon.h"
  #include "fsl_i2c.h"
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  #include "hardware/i2c.h"
#elif McuLib_CONFIG_CPU_IS_ESP32
  #include "driver/i2c_master.h"
#endif
#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845
  #include "fsl_swm.h"
  #include "fsl_i2c.h"
#endif
#if McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_LINUX
  #include <linux/i2c-dev.h>
  #include <sys/ioctl.h>
  #include <fcntl.h>
#endif

#if McuLib_CONFIG_SDK_VERSION_USED!=McuLib_CONFIG_SDK_LINUX
  static uint8_t i2cSlaveDeviceAddr; /* used to store the current I2C device address used */
#endif

#if McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_LINUX
  static int i2cBusHandle; /* file handle of I2C bus */
#endif

#if McuLib_CONFIG_CPU_IS_ESP32
  static i2c_device_config_t dev_cfg = {
    .dev_addr_length = I2C_ADDR_BIT_LEN_7,
    .device_address = 0, /* dummy device number */
    .scl_speed_hz = MCUI2CLIB_CONFIG_I2C_BAUDRATE,
    .scl_wait_us = 0, /* use default value */
    .flags.disable_ack_check = 0, /* ACK check enabled */
  };
  static i2c_master_dev_handle_t dev_handle = NULL;
  static i2c_master_bus_handle_t bus_handle = NULL;

  static void Esp32_SelectDevice(uint8_t deviceAddr) {
    /* for ESP32, we re-configure the dev_handle if we switch to a new device */
    esp_err_t err;

    if (deviceAddr!=dev_cfg.device_address) { /* new device to be used? */
      if (dev_handle!=NULL) { /* free previous device handle */
        err = i2c_master_bus_rm_device(dev_handle);
        if (err!=ESP_OK) {
          McuLog_fatal("failed adding bus device");
        }
      }
      dev_cfg.device_address = deviceAddr;
      err = i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle);
      if (err!=ESP_OK) {
        McuLog_fatal("failed adding bus device");
      }
    }
  }
#endif /* McuLib_CONFIG_CPU_IS_ESP32 */

uint8_t McuI2cLib_SendBlock(void *Ptr, uint16_t Siz, uint16_t *Snt) {
#if McuLib_CONFIG_CPU_IS_KINETIS  || McuLib_CONFIG_CPU_IS_LPC
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
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  /* nothing needed */
#elif McuLib_CONFIG_CPU_IS_ESP32
  /* nothing needed */
#endif

#if MCUI2CLIB_CONFIG_ADD_DELAY
  McuWait_Waitus(MCUI2CLIB_CONFIG_ADD_DELAY_US);
#endif
#if McuLib_CONFIG_CPU_IS_KINETIS  || McuLib_CONFIG_CPU_IS_LPC
  status = I2C_MasterWriteBlocking(MCUI2CLIB_CONFIG_I2C_MASTER_BASEADDR, Ptr, Siz, kI2C_TransferNoStartFlag|kI2C_TransferNoStopFlag);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  int nofBytesWritten;
  #if MCUI2CLIB_CONFIG_TIMEOUT_BYTE_US==0
    nofBytesWritten = i2c_write_blocking(MCUI2CLIB_CONFIG_I2C_DEVICE, i2cSlaveDeviceAddr, (uint8_t*)Ptr, Siz, false);
  #else
    nofBytesWritten = i2c_write_timeout_us(MCUI2CLIB_CONFIG_I2C_DEVICE, i2cSlaveDeviceAddr, (uint8_t*)Ptr, Siz, false, Siz*MCUI2CLIB_CONFIG_TIMEOUT_BYTE_US);
  #endif
  if (nofBytesWritten!=Siz) {
    *Snt = nofBytesWritten;
    return ERR_FAILED;
  }
#elif McuLib_CONFIG_CPU_IS_ESP32
  esp_err_t ret;

  ret = i2c_master_transmit(dev_handle, Ptr, Siz, pdMS_TO_TICKS(MCUI2CLIB_I2C_MASTER_TIMEOUT_MS));
  if (ret!=ESP_OK) {
    return ERR_FAILED;
  }
#elif McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_LINUX
  if (write(i2cBusHandle, Ptr, Siz)<0) {
    return ERR_FAILED;
  }
#endif
  *Snt = Siz;
  return ERR_OK;
}

uint8_t McuI2cLib_RecvBlock(void *Ptr, uint16_t Siz, uint16_t *Rcv) {
#if McuLib_CONFIG_CPU_IS_KINETIS  || McuLib_CONFIG_CPU_IS_LPC
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
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  int nofBytesRead;

  nofBytesRead = i2c_read_blocking(MCUI2CLIB_CONFIG_I2C_DEVICE, i2cSlaveDeviceAddr, (uint8_t*)Ptr, Siz, false);
  if (nofBytesRead!=Siz) {
    *Rcv = nofBytesRead;
    return ERR_FAILED;
  }
#elif McuLib_CONFIG_CPU_IS_ESP32
  esp_err_t ret;

  ret = i2c_master_receive(dev_handle, Ptr, Siz, pdMS_TO_TICKS(MCUI2CLIB_I2C_MASTER_TIMEOUT_MS));
  if (ret!=ESP_OK) {
    return ERR_FAILED;
  }
#elif McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_LINUX
  if (read(i2cBusHandle, Ptr, Siz)!=Siz) {
    return ERR_FAILED;
  }
#endif
  *Rcv = Siz;
  return ERR_OK;
}

uint8_t McuI2cLib_SendStop(void) {
#if McuLib_CONFIG_CPU_IS_KINETIS  || McuLib_CONFIG_CPU_IS_LPC
  status_t status;

  status = I2C_MasterStop(MCUI2CLIB_CONFIG_I2C_MASTER_BASEADDR);
  if (status!=kStatus_Success) {
    return ERR_FAILED;
  }
  return ERR_OK;
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  return ERR_OK; /* not required for RP2040 */
#elif McuLib_CONFIG_CPU_IS_ESP32
  return ERR_OK; /* not required for ESP32 */
#elif McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_LINUX
  return ERR_OK; /* not required for Linux */
#else
  return ERR_FAILED;
#endif
}

uint8_t McuI2cLib_SelectSlave(uint8_t Slv) {
#if McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_LINUX
  if (ioctl(i2cBusHandle, I2C_SLAVE, Slv)<0) { /* select the device */
    return ERR_FAILED;
  }
#else
  i2cSlaveDeviceAddr = Slv;
  #if McuLib_CONFIG_CPU_IS_ESP32
  Esp32_SelectDevice(Slv);
  #endif
#endif
  return ERR_OK;
}

#if MCUI2CLIB_CONFIG_I2C_RELEASE_BUS
static void McuI2cLib_ReleaseBus(void) {
  McuGPIO_Handle_t sdaPin, sclPin;
  McuGPIO_Config_t config;
  uint8_t i = 0;

  McuGPIO_GetDefaultConfig(&config);
  config.isInput = false;
  config.isHighOnInit = true;
#if McuLib_CONFIG_CPU_IS_KINETIS  || McuLib_CONFIG_CPU_IS_LPC
  config.hw.gpio = MCUI2CLIB_CONFIG_SDA_GPIO;
  config.hw.port = MCUI2CLIB_CONFIG_SDA_GPIO_PORT;
#endif
  config.hw.pin = MCUI2CLIB_CONFIG_SDA_GPIO_PIN;
  sdaPin = McuGPIO_InitGPIO(&config);

#if McuLib_CONFIG_CPU_IS_KINETIS  || McuLib_CONFIG_CPU_IS_LPC
  config.hw.gpio = MCUI2CLIB_CONFIG_SCL_GPIO;
  config.hw.port = MCUI2CLIB_CONFIG_SCL_GPIO_PORT;
#endif
  config.hw.pin = MCUI2CLIB_CONFIG_SCL_GPIO_PIN;
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
#endif /* MCUI2CLIB_CONFIG_I2C_RELEASE_BUS */

/* mux as I2C pins */
static void McuI2cLib_ConfigureI2cPins(void) {
#if    McuLib_CONFIG_CPU_IS_KINETIS \
    || McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16 \
    || McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S69 \
    || McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845
  MCUI2CLIB_CONFIG_MUX_I2C_PINS();
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  gpio_set_function(MCUI2CLIB_CONFIG_SDA_GPIO_PIN, GPIO_FUNC_I2C);
  gpio_set_function(MCUI2CLIB_CONFIG_SCL_GPIO_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(MCUI2CLIB_CONFIG_SDA_GPIO_PIN);
  gpio_pull_up(MCUI2CLIB_CONFIG_SCL_GPIO_PIN);
#elif McuLib_CONFIG_CPU_IS_ESP32
  /* nothing needed */
#elif McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_LINUX
  /* nothing needed */
#else
  #error "unknown configuration and MCU"
#endif
}

void McuI2cLib_Deinit(void) {
  /* nothing implemented */
}

#if McuLib_CONFIG_CPU_IS_ESP32
static esp_err_t esp32_master_init(void) {
  esp_err_t err;
  
  i2c_master_bus_config_t i2c_mst_config = {
      .clk_source = I2C_CLK_SRC_DEFAULT,
      .i2c_port = MCUI2CLIB_CONFIG_I2C_DEVICE,
      .scl_io_num = MCUI2CLIB_CONFIG_SCL_GPIO_PIN,
      .sda_io_num = MCUI2CLIB_CONFIG_SDA_GPIO_PIN,
      .glitch_ignore_cnt = 7,
      .intr_priority = 0, /* use default priority */
      .trans_queue_depth = 0, /* only valid/needed in asynchronous transaction */
      .flags.enable_internal_pullup = true, /* weak pull-ups anyway, use external pull-ups in addition! */
  };

  err = i2c_new_master_bus(&i2c_mst_config, &bus_handle);
  if (err!=ESP_OK) {
    McuLog_fatal("failed creating new master bus");
  }
  return err;
}
#endif /* McuLib_CONFIG_CPU_IS_ESP32 */

void McuI2cLib_Init(void) {
#if MCUI2CLIB_CONFIG_I2C_RELEASE_BUS
  McuI2cLib_ReleaseBus();
#endif
#if McuLib_CONFIG_CPU_IS_KINETIS \
     || McuLib_CONFIG_CPU_IS_LPC55xx && McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16 \
     || McuLib_CONFIG_CPU_IS_LPC55xx && McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S69 \
     || McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845
  MCUI2CLIB_CONFIG_CLOCK_SELECT();
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  i2c_init(MCUI2CLIB_CONFIG_I2C_DEVICE, MCUI2CLIB_CONFIG_I2C_BAUDRATE);
#elif McuLib_CONFIG_CPU_IS_ESP32
  if (esp32_master_init()!=ESP_OK) {
    McuLog_fatal("failed initializing I2C");
  }
#elif McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_LINUX
  i2cBusHandle = open(MCUI2CLIB_CONFIG_I2C_DEVICE, O_RDWR); /* device is something like "/dev/i2c-1" */
  if(i2cBusHandle<0) { /* open bus */
    McuLog_fatal("Failed to open I2C bus!\n");
  }
#else
  #error "unknown configuration and MCU"
#endif

  McuI2cLib_ConfigureI2cPins();

#if McuLib_CONFIG_CPU_IS_KINETIS  || McuLib_CONFIG_CPU_IS_LPC
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
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  /* nothing needed */
#elif McuLib_CONFIG_CPU_IS_ESP32
  /* nothing needed */
#elif McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_LINUX
  /* nothing needed */
#endif
}
#endif /* McuLib_CONFIG_MCUI2CLIB_ENABLED */

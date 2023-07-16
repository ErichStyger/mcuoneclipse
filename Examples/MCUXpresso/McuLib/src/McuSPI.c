/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuSPI.h"
#if MCUSPI_CONFIG_HW_TEMPLATE!=MCUSPI_CONFIG_HW_TEMPLATE_NONE
#include "McuLib.h"
#include "McuLog.h"
#if McuLib_CONFIG_CPU_IS_KINETIS
  #include "fsl_dspi.h"
#elif McuLib_CONFIG_CPU_IS_LPC55xx
  #include "fsl_spi.h"
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  #include "hardware/spi.h"
#elif McuLib_CONFIG_CPU_IS_ESP32
  #include "driver/spi_master.h"
#endif
#include "McuGPIO.h"
#include <string.h> /* Required for memset */

#if MCUSPI_CONFIG_USE_CS
  static McuGPIO_Handle_t McuSPI_CSpin;
#endif
#if McuLib_CONFIG_CPU_IS_RPxxxx
  static spi_inst_t *spiHandle;
#endif
#if McuLib_CONFIG_CPU_IS_ESP32
  static spi_device_handle_t handle;
#endif

int McuSPI_SendReceiveBlock(const uint8_t *txDataBuf, uint8_t *rxDataBuf, size_t dataSize) {
#if (MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_KINETIS_K22_SPI0) || (MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_KINETIS_K22_SPI1)
  dspi_transfer_t masterXfer;
  status_t status;

  /* Start master transfer, send data to slave */
  masterXfer.txData      = (uint8_t*)txDataBuf;
  masterXfer.rxData      = rxDataBuf;
  masterXfer.dataSize    = dataSize;
  masterXfer.configFlags = kDSPI_MasterCtar0 | MCUSPI_CONFIG_HW_SPI_MASTER_PCS_FOR_TRANSFER | kDSPI_MasterPcsContinuous;
  status = DSPI_MasterTransferBlocking(MCUSPI_CONFIG_HW_SPI_MASTER, &masterXfer);
  if (status==kStatus_Success) {
    return 0; /* ok */
  }
  return -1; /* error */
#elif MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_LPC55S16_FC3
  status_t status;
  spi_transfer_t xfer;

  /*Start Transfer*/
  xfer.txData      = (uint8_t*)txDataBuf;;
  xfer.rxData      = rxDataBuf;
  xfer.dataSize    = dataSize;
  xfer.configFlags = kSPI_FrameAssert;
  status = SPI_MasterTransferBlocking(MCUSPI_CONFIG_HW_SPI_MASTER, &xfer);
  if (status==kStatus_Success) {
    return 0; /* ok */
  }
  return -1; /* error */
#elif MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_RP2040_SPI1
  int res;

  res = spi_write_read_blocking(spiHandle, txDataBuf, rxDataBuf, dataSize);
  if (res==dataSize) { /* res is number of bytes written/read */
    return 0; /* ok */
  }
  return -1; /* failed */
#elif MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_ESP32_SPI3
  esp_err_t ret;
  spi_transaction_t t;
  memset(&t, 0, sizeof(t));

  t.length = dataSize*8; /* number of bits */
  t.tx_buffer = txDataBuf;
  t.rx_buffer = rxDataBuf;
  ret = spi_device_transmit(handle, &t);
  if (ret==ESP_OK) {
    return 0; /* ok */
  }
  return -1; /* failed */
#else
  #error "not implemented?"
  return -1; /* error */
#endif
}

int McuSPI_SendByte(unsigned char ch) {
  return McuSPI_SendReceiveBlock(&ch, NULL, sizeof(ch));
}

int McuSPI_SendReceiveByte(unsigned char ch, unsigned char *chp) {
  return McuSPI_SendReceiveBlock(&ch, chp, sizeof(ch));
}

int McuSPI_ReceiveByte(unsigned char *chp) {
  return McuSPI_SendReceiveBlock(NULL, chp, sizeof(char));
}

int McuSPI_SetBaudRate(uint32_t baud) {
#if (MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_KINETIS_K22_SPI0) || (MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_KINETIS_K22_SPI1)
  uint32_t bestBaud;

  bestBaud = DSPI_MasterSetBaudRate(MCUSPI_CONFIG_HW_SPI_MASTER, kDSPI_Ctar0, baud, MCUSPI_CONFIG_HW_SPI_MASTER_CLK_FREQ);
  return bestBaud!=0;
#elif MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_ESP32_SPI3
  return -1; /* error */
#else
  return ERR_FAILED;
#endif
}

#if 0 /* for testing only */
static void McuSPI_Test(void) {
  uint8_t tx = 'A';
  uint8_t rx;
  int res;

#if MCUSPI_CONFIG_USE_CS
  /* testing CS toggling */
  McuGPIO_SetLow(McuSPI_CSpin);
  McuGPIO_SetHigh(McuSPI_CSpin);
#endif
  /* testing a transfer */
  res = McuSPI_SendReceiveBlock(&tx, &rx, sizeof(tx));
  if (res!=0) {
    for(;;) { /* error */ }
  }
}
#endif

#if MCUSPI_CONFIG_USE_CS
void McuSPI_SetCS_Low(void) {
  McuGPIO_SetLow(McuSPI_CSpin);
}
#endif

#if MCUSPI_CONFIG_USE_CS
void McuSPI_SetCS_High(void) {
  McuGPIO_SetHigh(McuSPI_CSpin);
}
#endif

#if MCUSPI_CONFIG_USE_CS
static void McuSPI_InitCS(void) {
  McuGPIO_Config_t config;

  MCUSPI_CONFIG_HW_CS_INIT();
  McuGPIO_GetDefaultConfig(&config);
#if !McuLib_CONFIG_CPU_IS_RPxxxx /* Raspberry Pi Pico only has pin number */
  config.hw.gpio = MCUSPI_CONFIG_HW_CS_GPIO;
  config.hw.port = MCUSPI_CONFIG_HW_CS_PORT;
#endif
  config.hw.pin = MCUSPI_CONFIG_HW_CS_PIN;
  config.isInput = false;
  config.isHighOnInit = true; /* CS is LOW active */

  McuSPI_CSpin = McuGPIO_InitGPIO(&config);
  if (McuSPI_CSpin==NULL) {
    McuLog_fatal("failed initializing SPI CS pin");
    for(;;) {} /* error */
  }
}
#endif /* MCUSPI_CONFIG_USE_CS */

void McuSPI_Init(void) {
#if MCUSPI_CONFIG_USE_CS
  McuSPI_InitCS();
#endif
#if (MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_KINETIS_K22_SPI0) || (MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_KINETIS_K22_SPI1)
  dspi_master_config_t masterConfig;
  uint32_t srcClock_Hz;

  /* Master config */
  masterConfig.whichCtar                                = kDSPI_Ctar0;
  masterConfig.ctarConfig.baudRate                      = MCUSPI_CONFIG_TRANSFER_BAUDRATE;
  masterConfig.ctarConfig.bitsPerFrame                  = 8U;
  masterConfig.ctarConfig.cpol                          = kDSPI_ClockPolarityActiveHigh;
  masterConfig.ctarConfig.cpha                          = kDSPI_ClockPhaseFirstEdge;
  masterConfig.ctarConfig.direction                     = kDSPI_MsbFirst;
  masterConfig.ctarConfig.pcsToSckDelayInNanoSec        = 1000000000U / MCUSPI_CONFIG_TRANSFER_BAUDRATE;
  masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / MCUSPI_CONFIG_TRANSFER_BAUDRATE;
  masterConfig.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / MCUSPI_CONFIG_TRANSFER_BAUDRATE;

  masterConfig.whichPcs           = MCUSPI_CONFIG_HW_SPI_MASTER_PCS_FOR_INIT;
  masterConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;

  masterConfig.enableContinuousSCK        = false;
  masterConfig.enableRxFifoOverWrite      = false;
  masterConfig.enableModifiedTimingFormat = false;
  masterConfig.samplePoint                = kDSPI_SckToSin0Clock;

  srcClock_Hz = MCUSPI_CONFIG_HW_SPI_MASTER_CLK_FREQ;
  DSPI_MasterInit(MCUSPI_CONFIG_HW_SPI_MASTER, &masterConfig, srcClock_Hz);
#elif MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_LPC55S16_FC3
  spi_master_config_t userConfig = {0};
  uint32_t srcFreq               = 0;
  status_t status;

  MCUSPI_CONFIG_HW_SPI_INIT();
  SPI_MasterGetDefaultConfig(&userConfig);
  srcFreq            = MCUSPI_CONFIG_HW_SPI_MASTER_CLK_FREQ;
  userConfig.sselNum = (spi_ssel_t)MCUSPI_CONFIG_HW_SPI_SSEL;
  userConfig.sselPol = (spi_spol_t)MCUSPI_CONFIG_HW_SPI_SPOL;
  userConfig.baudRate_Bps = MCUSPI_CONFIG_TRANSFER_BAUDRATE;
  status = SPI_MasterInit(MCUSPI_CONFIG_HW_SPI_MASTER, &userConfig, srcFreq);
  if (status!=kStatus_Success) {
    for(;;) { /* error */ }
  }
#elif MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_RP2040_SPI1
  spiHandle = spi1;
  spi_init(spiHandle, MCUSPI_CONFIG_TRANSFER_BAUDRATE);
  gpio_set_function(MCUSPI_CONFIG_HW_MISO_PIN, GPIO_FUNC_SPI);
  gpio_set_function(MCUSPI_CONFIG_HW_MOSI_PIN, GPIO_FUNC_SPI);
  gpio_set_function(MCUSPI_CONFIG_HW_SCLK_PIN, GPIO_FUNC_SPI);
#elif MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_ESP32_SPI3
  /* \todo */
  esp_err_t ret;

  /* Configuration for the SPI bus */
  spi_bus_config_t buscfg = {
     .mosi_io_num=MCUSPI_CONFIG_HW_MOSI_PIN,
     .miso_io_num=MCUSPI_CONFIG_HW_MISO_PIN,
     .sclk_io_num=MCUSPI_CONFIG_HW_SCLK_PIN,
     .quadwp_io_num=-1,
     .quadhd_io_num=-1
   };
  spi_device_interface_config_t devcfg = {
     .command_bits=0,
     .address_bits=0,
     .dummy_bits=0,
     .clock_speed_hz=MCUSPI_CONFIG_TRANSFER_BAUDRATE,
     .duty_cycle_pos=128,        /* 50% duty cycle */
     .mode=0,
     .spics_io_num=MCUSPI_CONFIG_HW_CS_PIN, /* \todo */
     .cs_ena_posttrans=3,        //Keep the CS low 3 cycles after transaction, to stop slave from missing the last bit when CS has less propagation delay than CLK
     .queue_size=3
   };

  /* Initialize the SPI bus and add the device we want to send stuff to */
  ret = spi_bus_initialize(SPI3_HOST, &buscfg, SPI_DMA_CH_AUTO);
  if (ret!=ESP_OK) {
    McuLog_fatal("failed initialize SPI bus");
  }

  ret = spi_bus_add_device(SPI3_HOST, &devcfg, &handle);
  if (ret!=ESP_OK) {
    McuLog_fatal("failed initialize SPI bus");
  }
#else
  #error "SPI target not supported"
#endif
#if 0
  McuSPI_Test();
#endif
}

#endif /* #if MCUSPI_CONFIG_HW_TEMPLATE */

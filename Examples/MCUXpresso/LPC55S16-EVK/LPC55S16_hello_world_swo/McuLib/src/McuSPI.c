/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuSPI.h"
#if MCUSPI_CONFIG_HW_TEMPLATE!=MCUSPI_CONFIG_HW_TEMPLATE_NONE
#include "McuLib.h"
#if McuLib_CONFIG_CPU_IS_KINETIS
  #include "fsl_dspi.h"
#elif McuLib_CONFIG_CPU_IS_LPC55xx
  #include "fsl_spi.h"
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  #include "hardware/spi.h"
#endif
#include "McuGPIO.h"

static McuGPIO_Handle_t McuSPI_CSpin;
#if McuLib_CONFIG_CPU_IS_RPxxxx
  static spi_inst_t *spiHandle;
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
#else
  #error "not implemented?"
  return -1; /* error */
#endif
}

int McuSPI_SendByte(unsigned char ch) {
  return McuSPI_SendReceiveBlock(&ch, NULL, 1);
}

int McuSPI_SendReceiveByte(unsigned char ch, unsigned char *chp) {
  return McuSPI_SendReceiveBlock(&ch, chp, 1);
}

int McuSPI_ReceiveByte(unsigned char *chp) {
  return McuSPI_SendReceiveBlock(NULL, chp, 1);
}

#if 0 /* for testing only */
static void McuSPI_Test(void) {
  uint8_t tx = 'A';
  uint8_t rx;
  int res;

  /* testing CS toggling */
  McuGPIO_SetLow(McuSPI_CSpin);
  McuGPIO_SetHigh(McuSPI_CSpin);
  /* testing a transfer */
  res = McuSPI_SendReceiveBlock(&tx, &rx, sizeof(tx));
  if (res!=0) {
    for(;;) { /* error */ }
  }
}
#endif

void McuSPI_SetCS_Low(void) {
  McuGPIO_SetLow(McuSPI_CSpin);
}

void McuSPI_SetCS_High(void) {
  McuGPIO_SetHigh(McuSPI_CSpin);
}

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
    for(;;) {} /* error */
  }
}

void McuSPI_Init(void) {
  McuSPI_InitCS();
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
#else
  #error "SPI target not supported"
#endif
#if 0
  McuSPI_Test();
#endif
}

#endif /* #if MCUSPI_CONFIG_HW_TEMPLATE */

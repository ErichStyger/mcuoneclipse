/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuSPI.h"
#include "fsl_dspi.h"
#include "McuGPIO.h"

#define EXAMPLE_DSPI_MASTER_BASEADDR         SPI1
#define DSPI_MASTER_CLK_SRC                  DSPI1_CLK_SRC
#define DSPI_MASTER_CLK_FREQ                 CLOCK_GetFreq(DSPI1_CLK_SRC)
#define EXAMPLE_DSPI_MASTER_PCS_FOR_INIT     kDSPI_Pcs1
#define EXAMPLE_DSPI_MASTER_PCS_FOR_TRANSFER kDSPI_MasterPcs1

#define TRANSFER_SIZE     64U     /*! Transfer dataSize */
#define TRANSFER_BAUDRATE 500000U /*! Transfer baudrate - 500k */

static McuGPIO_Handle_t McuSPI_CSpin;

int McuSPI_SendReceiveData(const uint8_t *txDataBuf, uint8_t *rxDataBuf, size_t dataSize) {
  dspi_transfer_t masterXfer;
  status_t status;

  /* Start master transfer, send data to slave */
  masterXfer.txData      = (uint8_t*)txDataBuf;
  masterXfer.rxData      = rxDataBuf;
  masterXfer.dataSize    = dataSize;
  masterXfer.configFlags = kDSPI_MasterCtar0 | EXAMPLE_DSPI_MASTER_PCS_FOR_TRANSFER | kDSPI_MasterPcsContinuous;
  status = DSPI_MasterTransferBlocking(EXAMPLE_DSPI_MASTER_BASEADDR, &masterXfer);
  if (status==kStatus_Success) {
    return 0; /* ok */
  }
  return -1; /* error */
}

static void Test(void) {
  uint8_t tx = 'A';
  uint8_t rx;

  McuGPIO_SetLow(McuSPI_CSpin);
  McuGPIO_SetHigh(McuSPI_CSpin);
  McuSPI_SendReceiveData(&tx, &rx, sizeof(tx));
}

void McuSPI_Init(void) {
  dspi_master_config_t masterConfig;
  uint32_t srcClock_Hz;
  McuGPIO_Config_t config;

  CLOCK_EnableClock(kCLOCK_PortB);
  config.hw.gpio = GPIOB;
  config.hw.port = PORTB;
  config.hw.pin = 18;
  config.isInput = false;
  config.isHighOnInit = true; /* CS is LOW active */

  McuSPI_CSpin = McuGPIO_InitGPIO(&config);
  if (McuSPI_CSpin==NULL) {
    for(;;) {} /* error */
  }

  /* Master config */
  masterConfig.whichCtar                                = kDSPI_Ctar0;
  masterConfig.ctarConfig.baudRate                      = TRANSFER_BAUDRATE;
  masterConfig.ctarConfig.bitsPerFrame                  = 8U;
  masterConfig.ctarConfig.cpol                          = kDSPI_ClockPolarityActiveHigh;
  masterConfig.ctarConfig.cpha                          = kDSPI_ClockPhaseFirstEdge;
  masterConfig.ctarConfig.direction                     = kDSPI_MsbFirst;
  masterConfig.ctarConfig.pcsToSckDelayInNanoSec        = 1000000000U / TRANSFER_BAUDRATE;
  masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / TRANSFER_BAUDRATE;
  masterConfig.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / TRANSFER_BAUDRATE;

  masterConfig.whichPcs           = EXAMPLE_DSPI_MASTER_PCS_FOR_INIT;
  masterConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;

  masterConfig.enableContinuousSCK        = false;
  masterConfig.enableRxFifoOverWrite      = false;
  masterConfig.enableModifiedTimingFormat = false;
  masterConfig.samplePoint                = kDSPI_SckToSin0Clock;

  srcClock_Hz = DSPI_MASTER_CLK_FREQ;
  DSPI_MasterInit(EXAMPLE_DSPI_MASTER_BASEADDR, &masterConfig, srcClock_Hz);

  Test();
}

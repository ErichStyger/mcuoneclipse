/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuSPI.h"
#include "fsl_spi.h"

#define EXAMPLE_SPI_MASTER            SPI8
#define EXAMPLE_SPI_MASTER_IRQ        FLEXCOMM8_IRQn
#define EXAMPLE_SPI_MASTER_CLK_SRC    kCLOCK_Flexcomm8
#define EXAMPLE_SPI_MASTER_CLK_FREQ   CLOCK_GetFreq(kCLOCK_HsLspi)
#define SPI_MASTER_IRQHandler         FLEXCOMM8_IRQHandler

void McuSPI_WriteByte(uint8_t data) {
  spi_transfer_t xfer = {0};
  uint8_t destBuff;

  xfer.txData   = &data;
  xfer.rxData   = &destBuff;
  xfer.dataSize = 1;
  xfer.configFlags = kSPI_FrameAssert; /* required to get CLK low after transfer */
  SPI_MasterTransferBlocking(EXAMPLE_SPI_MASTER, &xfer);
}

void McuSPI_ReadByte(uint8_t *data) {
  spi_transfer_t xfer = {0};
  uint8_t dummy = 0xff;

  /*Start Transfer*/
  xfer.txData   = &dummy;
  xfer.rxData   = data;
  xfer.dataSize = 1;
  xfer.configFlags = kSPI_FrameAssert; /* required to get CLK low after transfer */
  SPI_MasterTransferBlocking(EXAMPLE_SPI_MASTER, &xfer);
}

void McuSPI_Init(void) {
  spi_master_config_t masterConfig = {0};
  uint32_t sourceClock             = 0U;

  /* attach 12 MHz clock to SPI3 */
  CLOCK_AttachClk(kFRO12M_to_FLEXCOMM7);

  /* reset FLEXCOMM for SPI */
  RESET_PeripheralReset(kFC7_RST_SHIFT_RSTn);

  /* Init SPI master */
  /*
   * masterConfig->enableLoopback = false;
   * masterConfig->enableMaster = true;
   * masterConfig->polarity = kSPI_ClockPolarityActiveHigh;
   * masterConfig->phase = kSPI_ClockPhaseFirstEdge;
   * masterConfig->direction = kSPI_MsbFirst;
   * masterConfig->baudRate_Bps = 500000U;
   */
  SPI_MasterGetDefaultConfig(&masterConfig);
  sourceClock = EXAMPLE_SPI_MASTER_CLK_FREQ;
  masterConfig.sselNum = kSPI_Ssel1;  /*! \todo */
  masterConfig.sselPol = kSPI_SpolActiveAllLow;
  masterConfig.polarity = kSPI_ClockPolarityActiveHigh; /* clock is LOW if not active, high if active */
  masterConfig.phase = kSPI_ClockPhaseFirstEdge; /* data is valid at raising clock edge */
  masterConfig.baudRate_Bps = 32*1000000;
  if (SPI_MasterInit(EXAMPLE_SPI_MASTER, &masterConfig, sourceClock)!=kStatus_Success) {
    for(;;) {
      /* error */
    }
  }
}

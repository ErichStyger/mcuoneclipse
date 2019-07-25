/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuSPIconfig.h"
#include "McuSPI.h"
#include "fsl_spi.h"
#if MCUSPI_CONFIG_USE_MUTEX
  #include "McuRTOS.h"
#endif

#if MCUSPI_CONFIG_USE_MUTEX
  static SemaphoreHandle_t mutex;
#endif

static spi_master_config_t configs[] = {
  { /* [0] McuSPI_ConfigLCD, SPI mode0 */
      .enableLoopback = false,
      .enableMaster = true,
      .polarity = kSPI_ClockPolarityActiveHigh,
      .phase = kSPI_ClockPhaseFirstEdge, /* data is valid at raising clock edge */
      .direction = kSPI_MsbFirst,
      .baudRate_Bps = 32*1000000U,
      .dataWidth = kSPI_Data8Bits,
      .sselNum = kSPI_Ssel1, /* \todo */
      .txWatermark = kSPI_TxFifo0,
      .rxWatermark = kSPI_RxFifo1,
      .sselPol = kSPI_SpolActiveAllLow,
      .delayConfig.preDelay = 0U,
      .delayConfig.postDelay = 0U,
      .delayConfig.frameDelay = 0U,
      .delayConfig.transferDelay = 0U,
  },
#if PL_CONFIG_USE_STMPE610
  { /* [1] McuSPI_ConfigTouch1, SPI mode0 */
      .enableLoopback = false,
      .enableMaster = true,
      .polarity = kSPI_ClockPolarityActiveHigh,
      .phase = kSPI_ClockPhaseFirstEdge, /* data is valid at raising clock edge */
      .direction = kSPI_MsbFirst,
      .baudRate_Bps = 1*1000000U, /* 1 MHz Max! */
      .dataWidth = kSPI_Data8Bits,
      .sselNum = kSPI_Ssel0,
      .txWatermark = kSPI_TxFifo0,
      .rxWatermark = kSPI_RxFifo1,
      .sselPol = kSPI_SpolActiveAllLow,
      .delayConfig.preDelay = 0U,
      .delayConfig.postDelay = 0U,
      .delayConfig.frameDelay = 0U,
      .delayConfig.transferDelay = 0U,
  },
  { /* [2] McuSPI_ConfigTouch2, SPI mode1 */
      .enableLoopback = false,
      .enableMaster = true,
      .polarity = kSPI_ClockPolarityActiveHigh,
      .phase = kSPI_ClockPhaseSecondEdge, /* data is valid at falling clock edge */
      .direction = kSPI_MsbFirst,
      .baudRate_Bps = 1*1000000U, /* 1 MHz Max! */
      .dataWidth = kSPI_Data8Bits,
      .sselNum = kSPI_Ssel0,
      .txWatermark = kSPI_TxFifo0,
      .rxWatermark = kSPI_RxFifo1,
      .sselPol = kSPI_SpolActiveAllLow,
      .delayConfig.preDelay = 0U,
      .delayConfig.postDelay = 0U,
      .delayConfig.frameDelay = 0U,
      .delayConfig.transferDelay = 0U,
  }
#endif
};

static McuSPI_Config McuSPI_CurrentConfig = -1;

void McuSPI_SwitchConfig(McuSPI_Config newConfig) {
  if (McuSPI_CurrentConfig!=newConfig) {
    if (SPI_MasterInit(DEVICE_SPI_MASTER, &configs[newConfig], DEVICE_SPI_MASTER_CLK_FREQ)!=kStatus_Success) {
      for(;;) {
        /* error */
      }
    }
    McuSPI_CurrentConfig = newConfig;
  }
}

void McuSPI_WriteByte(McuSPI_Config config, uint8_t data) {
  spi_transfer_t xfer = {0};

  xfer.txData   = &data;
  xfer.rxData   = NULL;
  xfer.dataSize = 1;
  xfer.configFlags = kSPI_FrameAssert; /* required to get CLK low after transfer */
#if MCUSPI_CONFIG_USE_MUTEX
  xSemaphoreTakeRecursive(mutex, portMAX_DELAY);
#endif
  McuSPI_SwitchConfig(config);
  SPI_MasterTransferBlocking(DEVICE_SPI_MASTER, &xfer);
#if MCUSPI_CONFIG_USE_MUTEX
  xSemaphoreGiveRecursive(mutex);
#endif
}

void McuSPI_WriteReadByte(McuSPI_Config config, uint8_t write, uint8_t *read) {
  spi_transfer_t xfer = {0};
  uint8_t tx = write;

  /*Start Transfer*/
  xfer.txData   = &tx;
  xfer.rxData   = read;
  xfer.dataSize = 1;
  xfer.configFlags = kSPI_FrameAssert; /* required to get CLK low after transfer */
#if MCUSPI_CONFIG_USE_MUTEX
  xSemaphoreTakeRecursive(mutex, portMAX_DELAY);
#endif
  McuSPI_SwitchConfig(config);
  SPI_MasterTransferBlocking(DEVICE_SPI_MASTER, &xfer);
#if MCUSPI_CONFIG_USE_MUTEX
  xSemaphoreGiveRecursive(mutex);
#endif
}

void McuSPI_ReadByte(McuSPI_Config config, uint8_t *data) {
  McuSPI_WriteReadByte(config, 0xff, data);
}

void MCUSPI_WriteBytes(McuSPI_Config config, uint8_t *data, size_t nofBytes) {
  spi_transfer_t xfer = {0};

  xfer.txData   = data;
  xfer.rxData   = NULL;
  xfer.dataSize = nofBytes;
  xfer.configFlags = kSPI_FrameAssert; /* required to get CLK low after transfer */
#if MCUSPI_CONFIG_USE_MUTEX
  xSemaphoreTakeRecursive(mutex, portMAX_DELAY);
#endif
  McuSPI_SwitchConfig(config);
  SPI_MasterTransferBlocking(DEVICE_SPI_MASTER, &xfer);
#if MCUSPI_CONFIG_USE_MUTEX
  xSemaphoreGiveRecursive(mutex);
#endif
}

void McuSPI_Deinit(void) {
#if MCUSPI_CONFIG_USE_MUTEX
  vSemaphoreDelete(mutex);
  mutex = NULL;
#endif
}

void McuSPI_Init(void) {
  /* attach 12 MHz clock to SPI3 */
  CLOCK_AttachClk(kFRO12M_to_FLEXCOMM7);

  /* reset FLEXCOMM for SPI */
  RESET_PeripheralReset(kFC7_RST_SHIFT_RSTn);

  McuSPI_CurrentConfig = -1; /* give it an illegal value */
  McuSPI_SwitchConfig(McuSPI_ConfigLCD);

#if MCUSPI_CONFIG_USE_MUTEX
  mutex = xSemaphoreCreateRecursiveMutex();
  if (mutex!=NULL) {
    vQueueAddToRegistry(mutex, "McuSPIMutex");
  } else {
    for(;;) { /* error */ }
  }
#endif
}

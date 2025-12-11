/*!
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_SPI
#include "McuSPI.h"
#include "McuGPIO.h"
#include "McuLog.h"
#include "McuRTOS.h"
#include "fsl_spi.h"
#include "board.h"
#include "LPC55S69_cm33_core0.h"

/* J19 on MCU-Link Pro (expansion port):
  black   1: GND
  brown   2  SPI_SSEL/DIO_0  ==> PIO0_20, pin 74
  red     3: SPI_MOSI/DIO_1  ==> PIO0_26, pin 60
  orange  4: SPI_CLK         ==> PIO1_2, pin 61    ==> IO_DIR1: HIGH, PIO1_1, pin 59
  yellow  5: SPI_MISO/DIO_3  ==> PIO1_3, pin 62    ==> IO_DIR2: LOW (Low by default)
  Green   6: I2C_SDA  => CAL_0
  Blue    7: I2C_SCL
  Violet  8: UART_IN  => CTRL_HIGH_CURR
  Gray    9: UART_OUT
  White   10: SYNC TRIG
  Black   11: GND
  Brown   12: AI_0
  Red     13: MEASUREMENT_TRIGGER
  Orange  14: VDD_IO_REF
*/

static McuGPIO_Handle_t IO_Dir1;
#if SpiBus_CONFIG_USE_MUTEX
  static SemaphoreHandle_t mutex = NULL; /* Mutex to protect access to SPI bus */
#endif

void SpiBus_Assert(void) {
	McuSPI_SetCS_Low();
}

void SpiBus_Deassert(void) {
	McuSPI_SetCS_High();
}

#if SpiBus_CONFIG_USE_MUTEX
void SpiBus_Lock(void) {
	if (xSemaphoreTakeRecursive(mutex, pdMS_TO_TICKS(portMAX_DELAY))!=pdTRUE) {
		McuLog_fatal("MCP3561: Failed to get bus semaphore!");
    for(;;) { /* error? */ }
  }
}
#endif

#if SpiBus_CONFIG_USE_MUTEX
void SpiBus_Unlock(void) {
	if (xSemaphoreGiveRecursive(mutex)!=pdTRUE) {
		McuLog_fatal("MCP3561: Failed to release bus semaphore!");
    for(;;) { /* error? */ }
  }
}
#endif

static void MuxSPIPins(void) {
    /*!
  * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
  #define PIO0_20_DIGIMODE_DIGITAL 0x01u
  /*!
  * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
  #define PIO0_26_DIGIMODE_DIGITAL 0x01u
  /*!
  * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
  #define PIO1_2_DIGIMODE_DIGITAL 0x01u
  /*!
  * @brief Selects pin function.: Alternative connection 6. */
  #define PIO1_2_FUNC_ALT6 0x06u
  /*!
  * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
  #define PIO1_3_DIGIMODE_DIGITAL 0x01u
  /*!
  * @brief Selects pin function.: Alternative connection 6. */
  #define PIO1_3_FUNC_ALT6 0x06u

  /* Enables the clock for the I/O controller.: Enable Clock. */
  CLOCK_EnableClock(kCLOCK_Iocon);

  IOCON->PIO[0][20] = ((IOCON->PIO[0][20] &
                        /* Mask bits to zero which are setting */
                        (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                        * : PORT020 (pin 74) is configured as HS_SPI_SSEL0. */
                        | IOCON_PIO_FUNC(0x08u)

                        /* Select Digital mode.
                        * : Enable Digital mode.
                        * Digital input is enabled. */
                        | IOCON_PIO_DIGIMODE(PIO0_20_DIGIMODE_DIGITAL));

  IOCON->PIO[0][26] = ((IOCON->PIO[0][26] &
                        /* Mask bits to zero which are setting */
                        (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                        * : PORT026 (pin 60) is configured as HS_SPI_MOSI. */
                        | IOCON_PIO_FUNC(0x09u)

                        /* Select Digital mode.
                        * : Enable Digital mode.
                        * Digital input is enabled. */
                        | IOCON_PIO_DIGIMODE(PIO0_26_DIGIMODE_DIGITAL));

  IOCON->PIO[1][2] = ((IOCON->PIO[1][2] &
                        /* Mask bits to zero which are setting */
                        (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                      /* Selects pin function.
                        * : PORT12 (pin 61) is configured as HS_SPI_SCK. */
                      | IOCON_PIO_FUNC(PIO1_2_FUNC_ALT6)

                      /* Select Digital mode.
                        * : Enable Digital mode.
                        * Digital input is enabled. */
                      | IOCON_PIO_DIGIMODE(PIO1_2_DIGIMODE_DIGITAL));

  IOCON->PIO[1][3] = ((IOCON->PIO[1][3] &
                        /* Mask bits to zero which are setting */
                        (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                      /* Selects pin function.
                        * : PORT13 (pin 62) is configured as HS_SPI_MISO. */
                      | IOCON_PIO_FUNC(PIO1_3_FUNC_ALT6)

                      /* Select Digital mode.
                        * : Enable Digital mode.
                        * Digital input is enabled. */
                      | IOCON_PIO_DIGIMODE(PIO1_3_DIGIMODE_DIGITAL));
}

void SpiBus_Deinit(void) {
#if SpiBus_CONFIG_USE_MUTEX
	vSemaphoreDelete(mutex);
  mutex = NULL;
#endif
  IO_Dir1 = McuGPIO_DeinitGPIO(IO_Dir1);
}
 
void SpiBus_Init(void) {
  MuxSPIPins();
  McuSPI_Init(); /* init SPI module */

  McuGPIO_Config_t config;
  McuGPIO_GetDefaultConfig(&config);
  config.isInput = false; /* is output */
  config.isHighOnInit = true; /* HIGH for MISO signal to pass it to the outside */
  config.hw.gpio = GPIO;
  config.hw.port = 1; /* PIO1_1 */
  config.hw.pin = 1; /* PIO1_1 */
  IO_Dir1 = McuGPIO_InitGPIO(&config);
  if (IO_Dir1 == NULL) {
    for(;;) {} /* error */
  }
#if SpiBus_CONFIG_USE_MUTEX
  mutex = xSemaphoreCreateRecursiveMutex();
  if (mutex==NULL) {
    for(;;) { /* error */ }
  }
  vQueueAddToRegistry(mutex, "SPI Mutex");
#endif
}

#endif /* PL_CONFIG_USE_SPI */
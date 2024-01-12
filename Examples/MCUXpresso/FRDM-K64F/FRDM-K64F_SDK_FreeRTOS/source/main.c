/*
 * The Clear BSD License
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 */

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "SEGGER_SYSVIEW.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "FreeRTOS_Timers.h"
#include "SysView.h"
#include "fsl_ftm.h"
#include "fsl_port.h"
#include "fsl_uart.h"
#include "fsl_i2c.h"
#include "fsl_dspi.h"
#include "fsl_clock.h"
#include "App_Config.h"
#include "InterProcessComm.h"

#if APP_CONFIG_USE_BLINKY
#define BOARD_LED_RED_GPIO      GPIOB
#define BOARD_LED_RED_PORT      PORTB
#define BOARD_LED_RED_PIN       22U

static void MuxInitLed(void) {
  CLOCK_EnableClock(kCLOCK_PortB);
  /* PORTB22 (pin 68) is configured as PTB22 */
  PORT_SetPinMux(BOARD_LED_RED_PORT, BOARD_LED_RED_GPIO_PIN, kPORT_MuxAsGpio);
  gpio_pin_config_t LED_RED_config = {
      .pinDirection = kGPIO_DigitalOutput,
      .outputLogic = 0U
  };
  /* Initialize GPIO functionality on pin PTB22 (pin 68)  */
  GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_PIN, &LED_RED_config);
}
#endif

#if APP_CONFIG_USE_UART
  #define APP_UART          UART0
  #define APP UART_CLKSRC   UART0_CLK_SRC
  #define APP_UART_CLK_FREQ CLOCK_GetFreq(UART0_CLK_SRC)
  #define APP_UART_BAUDRATE  (38400)
#endif

#if APP_CONFIG_USE_I2C
  #define I2C_MASTER_CLK_SRC          I2C0_CLK_SRC
  #define I2C_MASTER_CLK_FREQ         CLOCK_GetFreq(I2C0_CLK_SRC)
  #define EXAMPLE_I2C_MASTER_BASEADDR I2C0
  #define WAIT_TIME                   10U

  #define I2C_MASTER_SLAVE_ADDR_7BIT 0x7EU
  #define I2C_BAUDRATE               100000U
  #define I2C_DATA_LENGTH            33U
#endif

#if APP_CONFIG_USE_SPI
  #define EXAMPLE_DSPI_MASTER_BASEADDR         SPI0
  #define DSPI_MASTER_CLK_SRC                  DSPI0_CLK_SRC
  #define DSPI_MASTER_CLK_FREQ                 CLOCK_GetFreq(DSPI0_CLK_SRC)
  #define EXAMPLE_DSPI_MASTER_PCS_FOR_INIT     kDSPI_Pcs0
  #define EXAMPLE_DSPI_MASTER_PCS_FOR_TRANSFER kDSPI_MasterPcs0
  #define EXAMPLE_DSPI_DEALY_COUNT             0xfffffU

  #define TRANSFER_SIZE     64U     /*! Transfer dataSize */
  #define TRANSFER_BAUDRATE 500000U /*! Transfer baudrate - 500k */
#endif

#if APP_CONFIG_USE_FREERTOS
/*!
 * @brief Second task, lower priority.
 */
#if configSUPPORT_STATIC_ALLOCATION
#else
static void second_task(void *pvParameters) {
  for(;;) {
    if (GPIO_PinRead(BOARD_INITPINS_SW3_GPIO, BOARD_INITPINS_SW3_PIN)) { /* pin HIGH ==> SW03 push button not pressed */
      vTaskDelay(pdMS_TO_TICKS(50));
    } else {
      for(int i=0; i<20; i++) {
        GPIO_PortToggle(BOARD_INITPINS_LED_GREEN_GPIO, 1<<BOARD_INITPINS_LED_GREEN_PIN); /* toggle green LED on */
        vTaskDelay(pdMS_TO_TICKS(5));
      }
    }
  }
}
#endif
#endif

#if APP_CONFIG_USE_FREERTOS
/*!
 * @brief First task, higher priority.
 */
#if APP_CONFIG_USE_UART
  #define UART_STACK_SIZE (10)
#else
  #define UART_STACK_SIZE (0)
#endif
#if APP_CONFIG_USE_I2C
  #define I2C_STACK_SIZE (22)
#else
  #define I2C_STACK_SIZE (0)
#endif
#if APP_CONFIG_USE_SPI
  #define SPI_STACK_SIZE (32)
#else
  #define SPI_STACK_SIZE (0)
#endif
#define FIRST_TASK_SIZE   (20+UART_STACK_SIZE+I2C_STACK_SIZE+SPI_STACK_SIZE) /* stack units */

#if configSUPPORT_STATIC_ALLOCATION
#if configSUPPORT_STATIC_ALLOCATION
  static StaticTask_t xFirstTaskTCBBuffer;
  static StackType_t xFirstStack[FIRST_TASK_SIZE];
#endif

#else
#if 0
static void first_task(void *pvParameters) {
  if (xTaskCreate(second_task, "second_task", FIRST_TASK_SIZE/sizeof(StackType_t), NULL, 3, NULL) != pdPASS) {
      PRINTF("Task creation failed!.\r\n");
      vTaskSuspend(NULL);
  }
  /* dummy code, print counter and delay */
  for (int counter = 0;; counter++) {
#if APP_CONFIG_USE_SEGGER_SYSTEMVIEW
      SEGGER_SYSVIEW_PrintfTarget("first task counter: %d ", counter++);
#endif
      vTaskDelay(pdMS_TO_TICKS(100));
  }
}
#endif
#endif
#endif

#if APP_CONFIG_USE_FREERTOS
static void first_task(void *pvParameters) {
#if APP_CONFIG_USE_UART
  unsigned char ch = 'A';
#endif
#if APP_CONFIG_USE_I2C
  uint8_t g_master_txBuff[I2C_DATA_LENGTH];
  i2c_master_transfer_t masterXfer;
  memset(&masterXfer, 0, sizeof(masterXfer));

  /* subAddress = 0x01, data = g_master_txBuff - write to slave.
    start + slaveaddress(w) + subAddress + length of data buffer + data buffer + stop*/
  uint8_t deviceAddress     = 0x01U;
  masterXfer.slaveAddress   = I2C_MASTER_SLAVE_ADDR_7BIT;
  masterXfer.direction      = kI2C_Write;
  masterXfer.subaddress     = (uint32_t)deviceAddress;
  masterXfer.subaddressSize = 1;
  masterXfer.data           = g_master_txBuff;
  masterXfer.dataSize       = I2C_DATA_LENGTH;
  masterXfer.flags          = kI2C_TransferDefaultFlag;
#endif
#if APP_CONFIG_USE_SPI
  uint8_t masterTxData[TRANSFER_SIZE] = {0U};
  dspi_transfer_t masterSpiXfer;
  masterSpiXfer.txData      = masterTxData;
  masterSpiXfer.rxData      = NULL;
  masterSpiXfer.dataSize    = TRANSFER_SIZE;
  masterSpiXfer.configFlags = kDSPI_MasterCtar0 | EXAMPLE_DSPI_MASTER_PCS_FOR_TRANSFER | kDSPI_MasterPcsContinuous;
#endif
  for (;;) {
#if APP_CONFIG_USE_UART
    //UART_ReadBlocking(APP_UART, &ch, 1);
    UART_WriteBlocking(APP_UART, &ch, 1);
#endif

#if APP_CONFIG_USE_I2C
    I2C_MasterTransferBlocking(EXAMPLE_I2C_MASTER_BASEADDR, &masterXfer);
#endif

#if APP_CONFIG_USE_SPI
    /* Start master transfer, send data to slave */
    DSPI_MasterTransferBlocking(EXAMPLE_DSPI_MASTER_BASEADDR, &masterSpiXfer);
#endif
#if APP_CONFIG_USE_BLINKY
    GPIO_PortToggle(BOARD_LED_RED_GPIO, 1u<<BOARD_LED_RED_PIN);
#endif
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}
#endif

#if 0 && APP_CONFIG_USE_FREERTOS
uint32_t RTOS_RunTimeCounter; /* runtime counter, used for configGENERATE_RUNTIME_STATS */
void FTM0_IRQHandler(void) {
  /* Clear interrupt flag.*/
  FTM_ClearStatusFlags(FTM0, kFTM_TimeOverflowFlag);
  RTOS_RunTimeCounter++; /* increment runtime counter */
}

void RTOS_AppConfigureTimerForRuntimeStats(void) {
  RTOS_RunTimeCounter = 0;
  EnableIRQ(FTM0_IRQn);
}

uint32_t RTOS_AppGetRuntimeCounterValueFromISR(void) {
#if configGENERATE_RUN_TIME_STATS
  #if configGENERATE_RUN_TIME_STATS_USE_TICKS
  return xTaskGetTickCountFromISR(); /* using RTOS tick counter */
  #else /* using timer counter */
  return RTOS_RunTimeCounter;
  #endif
#else
  return 0; /* dummy value */
#endif
}
#endif

void __assertion_failed(char *_Expr)  {
  for(;;) {
    __asm("nop");
  }
}

void __assert_func(const char *file, int line, const char *func, const char *expr) {
  for(;;) {
    __asm("nop");
  }
}

#if configSUPPORT_STATIC_ALLOCATION && configUSE_TIMERS
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

/* If static allocation is supported then the application must provide the
   following callback function - which enables the application to optionally
   provide the memory that will be used by the timer task as the task's stack
   and TCB. */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize) {
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
#endif

#if configSUPPORT_STATIC_ALLOCATION
/* static memory allocation for the IDLE task */
#define IDLE_TASK_SIZE   (configMINIMAL_STACK_SIZE) /* stack units */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[IDLE_TASK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = IDLE_TASK_SIZE;
}
#endif

#if APP_CONFIG_USE_UART
static void MuxInitUART(void) {
  /* Port B Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortB);
  /* UART0 Rx and Tx */
  /* PORTB16 (pin 62) is configured as UART0_RX */
  PORT_SetPinMux(BOARD_INITPINS_DEBUG_UART_RX_PORT, BOARD_INITPINS_DEBUG_UART_RX_PIN, kPORT_MuxAlt3);

  /* PORTB17 (pin 63) is configured as UART0_TX */
  PORT_SetPinMux(BOARD_INITPINS_DEBUG_UART_TX_PORT, BOARD_INITPINS_DEBUG_UART_TX_PIN, kPORT_MuxAlt3);
  SIM->SOPT5 = ((SIM->SOPT5 &
                 /* Mask bits to zero which are setting */
                 (~(SIM_SOPT5_UART0TXSRC_MASK)))

                /* UART 0 transmit data source select: UART0_TX pin. */
                | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX));

  uart_config_t config;

  /*
   * config.baudRate_Bps = 115200U;
   * config.parityMode = kUART_ParityDisabled;
   * config.stopBitCount = kUART_OneStopBit;
   * config.txFifoWatermark = 0;
   * config.rxFifoWatermark = 1;
   * config.enableTx = false;
   * config.enableRx = false;
   */
  UART_GetDefaultConfig(&config);
  config.baudRate_Bps = APP_UART_BAUDRATE;
  config.enableTx     = true;
  config.enableRx     = true;

  UART_Init(APP_UART, &config, APP_UART_CLK_FREQ);
}
#endif

#if APP_CONFIG_USE_I2C
static void MuxInitI2C(void) {
  CLOCK_EnableClock(kCLOCK_PortE);
  const port_pin_config_t porte24_pin31_config = {/* Internal pull-up resistor is enabled */
                                                  kPORT_PullUp,
                                                  /* Fast slew rate is configured */
                                                  kPORT_FastSlewRate,
                                                  /* Passive filter is disabled */
                                                  kPORT_PassiveFilterDisable,
                                                  /* Open drain is enabled */
                                                  kPORT_OpenDrainEnable,
                                                  /* Low drive strength is configured */
                                                  kPORT_LowDriveStrength,
                                                  /* Pin is configured as I2C0_SCL */
                                                  kPORT_MuxAlt5,
                                                  /* Pin Control Register fields [15:0] are not locked */
                                                  kPORT_UnlockRegister};
  /* PORTE24 (pin 31) is configured as I2C0_SCL */
  PORT_SetPinConfig(PORTE, 24U, &porte24_pin31_config);

  const port_pin_config_t porte25_pin32_config = {/* Internal pull-up resistor is enabled */
                                                  kPORT_PullUp,
                                                  /* Fast slew rate is configured */
                                                  kPORT_FastSlewRate,
                                                  /* Passive filter is disabled */
                                                  kPORT_PassiveFilterDisable,
                                                  /* Open drain is enabled */
                                                  kPORT_OpenDrainEnable,
                                                  /* Low drive strength is configured */
                                                  kPORT_LowDriveStrength,
                                                  /* Pin is configured as I2C0_SDA */
                                                  kPORT_MuxAlt5,
                                                  /* Pin Control Register fields [15:0] are not locked */
                                                  kPORT_UnlockRegister};
  /* PORTE25 (pin 32) is configured as I2C0_SDA */
  PORT_SetPinConfig(PORTE, 25U, &porte25_pin32_config);

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
  I2C_MasterInit(EXAMPLE_I2C_MASTER_BASEADDR, &masterConfig, sourceClock);
}
#endif

#if APP_CONFIG_USE_SPI
static void MuxInitSPI(void) {
  CLOCK_EnableClock(kCLOCK_PortD);
  /* PORTD0 (pin 93) is configured as SPI0_PCS0 */
  PORT_SetPinMux(PORTD, 0U, kPORT_MuxAlt2);

  /* PORTD1 (pin 94) is configured as SPI0_SCK */
  PORT_SetPinMux(PORTD, 1U, kPORT_MuxAlt2);

  /* PORTD2 (pin 95) is configured as SPI0_SOUT */
  PORT_SetPinMux(PORTD, 2U, kPORT_MuxAlt2);

  /* PORTD3 (pin 96) is configured as SPI0_SIN */
  PORT_SetPinMux(PORTD, 3U, kPORT_MuxAlt2);

  dspi_master_config_t masterConfig;

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

  uint32_t srcClock_Hz;
  srcClock_Hz = DSPI_MASTER_CLK_FREQ;
  DSPI_MasterInit(EXAMPLE_DSPI_MASTER_BASEADDR, &masterConfig, srcClock_Hz);
}
#endif

/*!
 * @brief Main function
 */
int main(void) {
	/* Init board hardware. */
	//BOARD_InitPins();
	//BOARD_BootClockRUN();
	//BOARD_InitDebugConsole();
	//BOARD_InitBootPeripherals();
#if APP_CONFIG_USE_BLINKY
  MuxInitLed();
#endif
#if APP_CONFIG_USE_UART
  MuxInitUART();
#endif
#if APP_CONFIG_USE_I2C
  MuxInitI2C();
#endif
#if APP_CONFIG_USE_SPI
  MuxInitSPI();
#endif

#if APP_CONFIG_USE_SEGGER_SYSTEMVIEW
	SysView_Init();
#endif
#if APP_CONFIG_USE_FREERTOS
  #if configUSE_TIMERS
	  FreeRTOS_Timers_Init();
  #endif
	//IPC_Init();
#if APP_CONFIG_USE_USER_TASK
#if configSUPPORT_STATIC_ALLOCATION
  if (xTaskCreateStatic(first_task, "first_task", FIRST_TASK_SIZE, NULL, tskIDLE_PRIORITY+1, &xFirstStack[0], &xFirstTaskTCBBuffer)==NULL) {
    for(;;){} /* task creation failed */
  }
#else
	if (xTaskCreate(first_task, "first_task", FIRST_TASK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS)  {
		for(;;){}
	}
#endif
#endif
	vTaskStartScheduler();
#endif
	return 0;
}


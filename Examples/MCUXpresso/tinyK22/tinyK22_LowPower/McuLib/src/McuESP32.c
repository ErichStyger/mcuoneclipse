/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuESP32config.h"
#if McuESP32_CONFIG_UART!=McuESP32_CONFIG_UART_NONE
#include "McuESP32.h"
#include "McuGPIO.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuWait.h"
#include "McuLog.h"
#if McuESP32_CONFIG_USE_USB_CDC
  #include "virtual_com.h"
#endif

#if McuESP32_CONFIG_USE_CTRL_PINS
  static McuGPIO_Handle_t McuESP32_RF_EN_Pin;  /* pin pulled LOW to reset the module */
  static McuGPIO_Handle_t McuESP32_RF_IO0_Pin; /* pin pulled LOW to enable programming mode */
#endif
static QueueHandle_t uartRxQueue;  /* Rx from ESP32 module */
#define McuESP32_UART_RX_QUEUE_LENGTH                 (4096)
static QueueHandle_t uartTxQueue;  /* Tx to ESP32 module */
#define McuESP32_UART_TX_QUEUE_LENGTH                 (4096)

#if McuESP32_CONFIG_USE_USB_CDC
  typedef enum McuESP32_USB_PrgMode_e {
    McuESP32_USB_PRG_MODE_AUTO,
    McuESP32_USB_PRG_MODE_ON,
    McuESP32_USB_PRG_MODE_OFF,
  } McuESP32_USB_PrgMode_e;
  static McuESP32_USB_PrgMode_e McuESP32_UsbPrgMode = McuESP32_USB_PRG_MODE_AUTO;
  static bool McuESP32_IsProgramming = false; /* if we are currently programming the ESP32 */
  static bool McuESP32_ScheduleReset = true; /* do an initial reset at restart time */
#endif
static bool McuESP32_CopyUartToShell = true; /* if we copy the ESP32 UART to the Shell */

/* Below is the I/O handler for the console: data from the ESP is sent to that stdout (e.g. shell console).
 * Optionally with McuESP32_CONFIG_USE_USB_CDC enabled all CDC data is sent to the ESP32 as well.
 */
static McuShell_ConstStdIOType *McuESP32_RxFromESPStdIO = NULL; /* can be overwritten with McuESP32_SetRxFromESPStdio(); */

void McuESP32_SetRxFromESPStdio(McuShell_ConstStdIOTypePtr stdio) {
 McuESP32_RxFromESPStdIO = stdio;
}

McuShell_ConstStdIOTypePtr McuESP32_GetRxFromESPStdio(void) {
  return McuESP32_RxFromESPStdIO;
}

#if McuESP32_CONFIG_USE_CTRL_PINS
static void AssertReset(void) {
  McuGPIO_SetAsOutput(McuESP32_RF_EN_Pin, false); /* output, LOW */
}
#endif

#if McuESP32_CONFIG_USE_CTRL_PINS
static void DeassertReset(void) {
  McuGPIO_SetAsInput(McuESP32_RF_EN_Pin);
}
#endif

#if McuESP32_CONFIG_USE_CTRL_PINS
static void DoReset(void) {
  AssertReset();
  vTaskDelay(pdMS_TO_TICKS(1));
  DeassertReset();
}
#endif

#if McuESP32_CONFIG_USE_CTRL_PINS
static void AssertBootloaderMode(void) {
  McuGPIO_SetAsOutput(McuESP32_RF_IO0_Pin, false); /* output, LOW */
}
#endif

#if McuESP32_CONFIG_USE_CTRL_PINS
static void DeassertBootloaderMode(void) {
  McuGPIO_SetAsInput(McuESP32_RF_IO0_Pin);
}
#endif

#if McuESP32_CONFIG_USE_USB_CDC
/* idf.py flash sequence:
 *
 * 00> State: 3, DtrRts: 3

 * 00> State: 2, DtrRts: 1
 * 00> State: 3, DtrRts: 3
 * 00> State: 1, DtrRts: 2
 * 00> State: 0, DtrRts: 0

 * 00> State: 2, DtrRts: 1
 * 00> State: 3, DtrRts: 3
 * 00> State: 1, DtrRts: 2
 * 00> State: 0, DtrRts: 0
 *
 * reset at the end:
 * 00> State: 2, DtrRts: 1
 * 00> State: 0, DtrRts: 0
 */

void McuESP32_UartState_Callback(uint8_t state) { /* callback for DTR and RTS lines */
  static uint8_t prevState = -1;
  static uint8_t prevPrevState = -1;
  uint8_t DtrRts;

#if McuESP32_CONFIG_VERBOSE_CONTROL_SIGNALS
  McuLog_trace("state: %d, prev: %d, prevprev: %d", state, prevState, prevPrevState);
#endif
  if (state != prevState) {
    if (McuESP32_UsbPrgMode==McuESP32_USB_PRG_MODE_AUTO || McuESP32_UsbPrgMode==McuESP32_USB_PRG_MODE_ON) {
      /*
       * DTR  RTS  EN  GPIO0
       * 1    1    1   1
       * 0    0    1   1
       * 1    0    0   0
       * 0    1    1   0
       */
      DtrRts = 0;
      if ((state&1)==1) { /* DTR */
        DtrRts |= 2; /* DTR set */
      }
      if ((state&2)==2) { /* DTR */
        DtrRts |= 1; /* RTS set */
      }
    #if McuESP32_CONFIG_VERBOSE_CONTROL_SIGNALS
      McuLog_trace("State: %d, DtrRts: %d", state, DtrRts);
    #endif
      switch(DtrRts) {
        default:
        case 0:
          DeassertReset();
          McuWait_Waitus(100); /* block for a short time (in the ISR!!!) ==> should have a 100 uF added to the reset line */
          DeassertBootloaderMode();
          //McuLog_trace("Release both: %d", DtrRts);
          break;
        case 1:
          AssertBootloaderMode();
          //McuLog_trace("assert BL: %d", DtrRts);
          break;
        case 2:
          if (McuGPIO_IsLow(McuESP32_RF_EN_Pin)) {
            if (McuGPIO_IsLow(McuESP32_RF_IO0_Pin)) {
              McuESP32_IsProgramming = true; /* the DeassertReset() below will enter bootloader mode */
              McuLog_trace("Enter Bootloader Mode");
            } else {
              McuESP32_IsProgramming = false; /* the DeassertReset() below will do a reset without bootloader */
              McuLog_trace("Reset");
            }
          }
          DeassertReset();
          McuWait_Waitus(100); /* block for a short time (in the ISR!!!) ==> should have a 100 uF added to the reset line */
          //McuLog_trace("release reset: %d", DtrRts);
          break;
        case 3:
          AssertReset();
          //McuLog_trace("assert reset: %d", DtrRts);
          break;
      } /* switch */
      if (state==0 && prevState==2 && prevPrevState==0) {
        // reset sequence with idf.py and Arduino IDE:
        // State: 0 DtrRts: 0 Release both: 0
        // State: 2 DtrRts: 1 assert BL: 1
        // State: 0 DtrRts: 0 Release both: 0
        McuLog_info("Request Reset");
        McuESP32_ScheduleReset = true; /* cannot do reset sequence here, as called from an interrupt, so we cannot block */
        McuESP32_IsProgramming = false;
      }
    }
    prevPrevState = prevState;
    prevState = state;
  } /* if state!=prevState */
}
#endif

/*********************************************************************************************************/
/* Stdio Handler for sending text to the ESP32 */
static void QueueTxChar(unsigned char ch) {
 (void)xQueueSendToBack(uartTxQueue, &ch, 0); /* put it back in to the Tx queue */
}

static void Dummy_ReadChar(uint8_t *c) {
  *c = '\0'; /* nothing received */
}

static bool Dummy_CharPresent(void) {
  return false;
}

/* for sending data to the ESP32 (tx only) */
static const McuShell_ConstStdIOType McuESP32_Tx_stdio = {
    .stdIn = (McuShell_StdIO_In_FctType)Dummy_ReadChar,
    .stdOut = (McuShell_StdIO_OutErr_FctType)QueueTxChar,
    .stdErr = (McuShell_StdIO_OutErr_FctType)QueueTxChar,
    .keyPressed = Dummy_CharPresent, /* if input is not empty */
 #if McuShell_CONFIG_ECHO_ENABLED
    .echoEnabled = false,
  #endif
  };

McuShell_ConstStdIOTypePtr McuESP32_GetTxToESPStdio(void) {
  return &McuESP32_Tx_stdio;
}
/*********************************************************************************************************/
void McuESP32_CONFIG_UART_IRQ_HANDLER(void) {
  uint8_t data;
  uint32_t flags=0;
  BaseType_t xHigherPriorityTaskWoken;

  flags = McuESP32_CONFIG_UART_GET_FLAGS(McuESP32_CONFIG_UART_DEVICE);
  /* If new data arrived. */
  if (flags&McuESP32_CONFIG_UART_HW_RX_READY_FLAGS) {
    data = McuESP32_CONFIG_UART_READ_BYTE(McuESP32_CONFIG_UART_DEVICE);
    (void)xQueueSendFromISR(uartRxQueue, &data, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken != pdFALSE) {
      __DSB();
      vPortYieldFromISR();
    }
  }
  __DSB();
}

static uint8_t McuESP32_PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"esp32", (unsigned char*)"Group of ESP32 WiFi module commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows ESP32 help or status\r\n", io->stdOut);
#if McuESP32_CONFIG_USE_CTRL_PINS
  McuShell_SendHelpStr((unsigned char*)"  reset", (unsigned char*)"Perform reset sequence\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  assert|deassart reset", (unsigned char*)"Assert or deassert reset pin\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  assert|deassart bl", (unsigned char*)"Assert or deassert bootloader pin\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  prg start|stop", (unsigned char*)"Start and stop programming sequence\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  uarttoshell on|off", (unsigned char*)"Copy UART Rx to Shell\r\n", io->stdOut);
#if McuESP32_CONFIG_USE_USB_CDC
  McuShell_SendHelpStr((unsigned char*)"  usbprg auto|on|off", (unsigned char*)"Use USB CDC to UART for programming\r\n", io->stdOut);
#endif
#endif
  McuShell_SendHelpStr((unsigned char*)"  send <cmd>", (unsigned char*)"Send a command or string to the ESP32\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t McuESP32_PrintStatus(const McuShell_StdIOType *io) {
#if McuESP32_CONFIG_USE_CTRL_PINS || McuESP32_CONFIG_USE_USB_CDC
  uint8_t buf[64];
#endif

  McuShell_SendStatusStr((unsigned char*)"esp32", (unsigned char*)"ESP32 status\r\n", io->stdOut);
#if McuESP32_CONFIG_USE_CTRL_PINS
  McuGPIO_GetPinStatusString(McuESP32_RF_EN_Pin, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  EN", buf, io->stdOut);

  McuGPIO_GetPinStatusString(McuESP32_RF_IO0_Pin, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  IO0", buf, io->stdOut);
#endif
#if McuESP32_CONFIG_USE_USB_CDC
  if (McuESP32_UsbPrgMode==McuESP32_USB_PRG_MODE_ON) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"on");
    if (McuESP32_CopyUartToShell) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", nothing will be copied to shell.\r\n");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    }
  } else if (McuESP32_UsbPrgMode==McuESP32_USB_PRG_MODE_AUTO) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"auto\r\n");
  } else if (McuESP32_UsbPrgMode==McuESP32_USB_PRG_MODE_OFF) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"off\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  usbprg", buf, io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  programming", McuESP32_IsProgramming?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
#endif

  McuShell_SendStatusStr((unsigned char*)"  uarttoshell", McuESP32_CopyUartToShell?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t McuESP32_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, (char*)"esp32 help")==0) {
    *handled = true;
    return McuESP32_PrintHelp(io);
  } else if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_STATUS)==0 || McuUtility_strcmp((char*)cmd, (char*)"esp32 status")==0) {
    *handled = true;
    return McuESP32_PrintStatus(io);
#if McuESP32_CONFIG_USE_CTRL_PINS
  } else if (McuUtility_strcmp((char*)cmd, (char*)"esp32 reset")==0) {
    *handled = true;
    DoReset();
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, (char*)"esp32 prg start")==0) {
    /* pulling prg pin low, followed by a reset */
    *handled = true;
    AssertBootloaderMode(); /* pull prg pin low: during reset, device will enter serial programming mode */
    vTaskDelay(pdMS_TO_TICKS(1));
    DoReset();
    vTaskDelay(pdMS_TO_TICKS(1));
    DeassertBootloaderMode();
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, (char*)"esp32 prg stop")==0) {
    /* release prg pin, followed by a reset */
    *handled = true;
    DeassertBootloaderMode(); /* return prg pin to high (normal) again */
    vTaskDelay(pdMS_TO_TICKS(1));
    DoReset();
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, (char*)"esp32 assert bl")==0) {
    *handled = true;
    AssertBootloaderMode();
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, (char*)"esp32 deassert bl")==0) {
    *handled = true;
    DeassertBootloaderMode();
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, (char*)"esp32 assert reset")==0) {
    *handled = true;
    AssertReset();
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, (char*)"esp32 deassert reset")==0) {
    *handled = true;
    DeassertReset();
    return ERR_OK;
#endif
  } else if (McuUtility_strcmp((char*)cmd, (char*)"esp32 uarttoshell on")==0) {
    *handled = true;
    McuESP32_CopyUartToShell = true;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, (char*)"esp32 uarttoshell off")==0) {
    *handled = true;
    McuESP32_CopyUartToShell = false;
    return ERR_OK;
#if McuESP32_CONFIG_USE_USB_CDC
  } else if (McuUtility_strcmp((char*)cmd, (char*)"esp32 usbprg auto")==0) {
    *handled = true;
    McuESP32_UsbPrgMode = McuESP32_USB_PRG_MODE_AUTO;
    McuESP32_IsProgramming = false;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, (char*)"esp32 usbprg on")==0) {
    *handled = true;
    McuESP32_UsbPrgMode = McuESP32_USB_PRG_MODE_ON;
    McuESP32_IsProgramming = true;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, (char*)"esp32 usbprg off")==0) {
    *handled = true;
    McuESP32_UsbPrgMode = McuESP32_USB_PRG_MODE_OFF;
    McuESP32_IsProgramming = false;
    return ERR_OK;
#endif
  } else if (McuUtility_strncmp((char*)cmd, (char*)"esp32 send ", sizeof("esp32 send ")-1)==0) {
    const unsigned char *p;
    unsigned char buffer[McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE];

    *handled = true;
    p = cmd+sizeof("esp32 send ")-1;
    if (*p=='"') { /* double-quoted command: it can contain multiple commands */
      if (McuUtility_ScanDoubleQuotedString(&p, buffer, sizeof(buffer))!=ERR_OK) {
        return ERR_FAILED;
      }
      p = buffer;
    }
    /* send command string */
    McuShell_SendStr(p, McuESP32_GetTxToESPStdio()->stdOut);
    McuShell_SendStr((unsigned char*)"\r\n", McuESP32_GetTxToESPStdio()->stdOut);
    return ERR_OK;
  }
  return ERR_OK;
}

static void UartRxTask(void *pv) { /* task handling characters sent by the ESP32 module and coming from the UART of the ESP32 */
  unsigned char ch;
  BaseType_t res;
  McuShell_ConstStdIOType *io;

  (void)pv; /* not used */
  for(;;) {
    res = xQueueReceive(uartRxQueue, &ch, portMAX_DELAY);
    if (res==pdPASS) {
  #if McuESP32_CONFIG_USE_USB_CDC
      if (USB_CdcIsConnected()) { /* send directly to programmer attached on the USB or to the IDF monitor */
        USB_CdcStdio.stdOut(ch); /* forward to USB CDC and the programmer on the host */
      }
  #endif
      if (   McuESP32_CopyUartToShell
  #if McuESP32_CONFIG_USE_USB_CDC
          && !McuESP32_IsProgramming
  #endif
         )
      { /* only write to shell if not in programming mode. Programming mode might crash RTT */
        io = McuESP32_GetRxFromESPStdio();
        if (io!=NULL) {
          McuShell_SendCh(ch, io->stdOut); /* forward character */
        }
      }
    } else {
      McuLog_fatal("ESP32 UartRxTask queue failed");
    }
  }
}

static void UartTxTask(void *pv) { /* task handling sending data to the ESP32 module */
  unsigned char ch;
  BaseType_t res;
  bool workToDo;

  (void)pv; /* not used */
  for(;;) {
#if McuESP32_CONFIG_USE_USB_CDC
    if (McuESP32_ScheduleReset) {
      McuESP32_ScheduleReset = false;
      McuLog_info("Performing reset");
      DoReset();
    }
#endif
    workToDo = false;
    do {
      res = xQueueReceive(uartTxQueue, &ch, 0); /* poll queue */
      if (res==pdPASS) { /* write data to ESP over UART */
        workToDo = true;
        McuESP32_CONFIG_UART_WRITE_BLOCKING(McuESP32_CONFIG_UART_DEVICE, &ch, 1); /* send to ESP */
      }
    } while (res==pdPASS);
#if McuESP32_CONFIG_USE_USB_CDC
    while (USB_CdcStdio.keyPressed()) { /* check USB CDC data stream */
      workToDo = true;
      USB_CdcStdio.stdIn(&ch); /* read byte */
      McuESP32_CONFIG_UART_WRITE_BLOCKING(McuESP32_CONFIG_UART_DEVICE, &ch, 1); /* send to ESP */
      /* check if we can copy the USB CDC data to shell console too */
      if (McuESP32_CopyUartToShell && !McuESP32_IsProgramming) {
        McuShell_ConstStdIOTypePtr io = McuESP32_GetRxFromESPStdio();
        if (io!=NULL) {
          McuShell_SendCh(ch, io->stdOut); /* write to console */
        }
      }
    }
#endif
    if (!workToDo) { /* only delay if we are not busy */
      vTaskDelay(pdMS_TO_TICKS(5));
    }
  }
}

static void InitUart(void) {
  /* NOTE: Muxing of the UART pins needs to be done in the Pins tool! */
  McuESP32_CONFIG_UART_CONFIG_STRUCT config;

  McuESP32_CONFIG_UART_SET_UART_CLOCK();
  McuESP32_CONFIG_UART_GET_DEFAULT_CONFIG(&config);
  config.baudRate_Bps = McuESP32_CONFIG_UART_BAUDRATE;
  config.enableRx     = true;
  config.enableTx     = true;

  /* Initialize the USART with configuration. */
  McuESP32_CONFIG_UART_INIT(McuESP32_CONFIG_UART_DEVICE, &config, CLOCK_GetFreq(McuESP32_CONFIG_UART_GET_CLOCK_FREQ_SELECT));
  McuESP32_CONFIG_UART_ENABLE_INTERRUPTS(McuESP32_CONFIG_UART_DEVICE, McuESP32_CONFIG_UART_ENABLE_INTERRUPT_FLAGS);
  EnableIRQ(McuESP32_CONFIG_UART_IRQ_NUMBER);
  NVIC_SetPriority(McuESP32_CONFIG_UART_IRQ_NUMBER, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);

  uartRxQueue = xQueueCreate(McuESP32_UART_RX_QUEUE_LENGTH, sizeof(uint8_t));
  if (uartRxQueue==NULL) {
    McuLog_fatal("not able to create Rx queue");
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(uartRxQueue, "ESP32UartRxQueue");

  uartTxQueue = xQueueCreate(McuESP32_UART_TX_QUEUE_LENGTH, sizeof(uint8_t));
  if (uartTxQueue==NULL) {
    McuLog_fatal("not able to create Tx queue");
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(uartTxQueue, "ESP32UartTxQueue");
}

static void InitPins(void) {
#if McuESP32_CONFIG_USE_CTRL_PINS
  McuGPIO_Config_t gpioConfig;

  McuGPIO_GetDefaultConfig(&gpioConfig);
  gpioConfig.isInput = true;
  gpioConfig.hw.gpio = McuESP32_CONFIG_EN_GPIO;
  gpioConfig.hw.port = McuESP32_CONFIG_EN_PORT;
  gpioConfig.hw.pin = McuESP32_CONFIG_EN_PIN;
  McuESP32_RF_EN_Pin = McuGPIO_InitGPIO(&gpioConfig);

  gpioConfig.hw.gpio = McuESP32_CONFIG_RST_GPIO;
  gpioConfig.hw.port = McuESP32_CONFIG_RST_PORT;
  gpioConfig.hw.pin = McuESP32_CONFIG_RST_PIN;
  McuESP32_RF_IO0_Pin = McuGPIO_InitGPIO(&gpioConfig);
#endif
}

void McuESP32_Deinit(void) {
#if McuESP32_CONFIG_USE_CTRL_PINS
  McuESP32_RF_EN_Pin = McuGPIO_DeinitGPIO(McuESP32_RF_EN_Pin);
  McuESP32_RF_IO0_Pin = McuGPIO_DeinitGPIO(McuESP32_RF_IO0_Pin);
#endif
  vQueueDelete(uartRxQueue);
  uartRxQueue = NULL;
}

void McuESP32_Init(void) {
  InitPins();
  InitUart();
  if (xTaskCreate(
      UartRxTask,  /* pointer to the task */
      "ESP32UartRx", /* task name for kernel awareness debugging */
      500/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+3,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating ESP32 Rx Task");
    for(;;){} /* error! probably out of memory */
  }
  if (xTaskCreate(
      UartTxTask,  /* pointer to the task */
      "ESP32UartTx", /* task name for kernel awareness debugging */
      500/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+3,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating ESP32 Tx Task");
    for(;;){} /* error! probably out of memory */
  }
}
#endif /* #if McuESP32_CONFIG_UART */

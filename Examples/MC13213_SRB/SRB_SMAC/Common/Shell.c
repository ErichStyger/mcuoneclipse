/**
 * \file
 * \brief This is the implementation module of the Serial console
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This interface file is used for a console and terminal.
 * That way we can interact with the target and change settings using a shell implementation
 */
#include "Platform.h"

#if PL_HAS_SHELL
#include "Shell.h"
#include "CLS1.h"
#include "UTIL1.h"
#include "LED.h"
#include "Keys.h"
#if PL_USE_USB_SCI
  #include "USB1.h"
#endif
#if PL_HAS_MEALY
  #include "Mealy.h"
#endif
#if PL_HAS_TEMPERATURE
  #include "Temperature.h"
#endif
#if PL_HAS_RTOS
  #include "FRTOS1.h"
#endif
#if PL_HAS_QUEUE
  #include "MyQueue.h"
#endif
#if PL_HAS_ACCEL
  #include "Accel.h"
#endif
#if PL_HAS_TRACE
  #include "Trace.h"
#endif
#if PL_HAS_MOTOR
  #include "Motor.h"
  #include "QuadCounter.h"
  #include "Tacho.h"
  #include "PID.h"
  #include "I2C.h"
#endif
#if PL_HAS_TEMPERATURE
  #include "TEMP1.h"
#endif
#if PL_HAS_RADIO
  #include "Radio.h"
#endif
#if PL_HAS_REMOTE
  #include "Remote.h"
#endif

void SHELL_SendMessage(const char *msg) {
#if PL_HAS_QUEUE
  QUEUE_SendMessage(msg);
#else
  CLS1_SendStr(msg, CLS1_GetStdio()->stdOut);
#endif
}

/*!
 * \brief Prints the help text to the console
 * \param io I/O channel to be used
 */
static void PrintHelp(const CLS1_StdIOType *io) {
  /* list your local help here */
  (void)io;
}

/*!
 * \brief Prints the status text to the console
 * \param io I/O channel to be used
 */
static void PrintStatus(const CLS1_StdIOType *io) {
  /* list your local status here */
  (void)io;
}

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
static uint8_t ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  /* handling our own commands */
  if (UTIL1_strcmp(cmd, CLS1_CMD_HELP)==0) {
    PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, CLS1_CMD_STATUS)==0) {
    PrintStatus(io);
    *handled = TRUE;
  }
  /*! \todo Handle here the additional parsers */
#if PL_HAS_LED
  if (LED_ParseCommand(cmd, handled, io)!=ERR_OK) {
    return ERR_FAILED;
  }
#endif
#if PL_HAS_KEYBOARD
  if (KEY_ParseCommand(cmd, handled, io)!=ERR_OK) {
    return ERR_FAILED;
  }
#endif
#if PL_HAS_MEALY
  if (MEALY_ParseCommand(cmd, handled, io)!=ERR_OK) {
    return ERR_FAILED;
  }
#endif
#if PL_HAS_TEMPERATURE
  if (TEMP_ParseCommand(cmd, handled, io)!=ERR_OK) {
    return ERR_FAILED;
  }
#endif
#if PL_HAS_MOTOR
  if (MOT_ParseCommand(cmd, handled, io)!=ERR_OK) {
    return ERR_FAILED;
  }
#endif
#if PL_HAS_MOTOR_QUAD
  if (QUAD_ParseCommand(cmd, handled, io)!=ERR_OK) {
    return ERR_FAILED;
  }
#endif
#if PL_HAS_MOTOR_TACHO
  if (TACHO_ParseCommand(cmd, handled, io)!=ERR_OK) {
    return ERR_FAILED;
  }
#endif
#if PL_HAS_MOTOR_PID
  if (PID_ParseCommand(cmd, handled, io)!=ERR_OK) {
    return ERR_FAILED;
  }
#endif
#if PL_HAS_ACCEL
  if (ACCEL_ParseCommand(cmd, handled, io)!=ERR_OK) {
    return ERR_FAILED;
  }
#endif
#if PL_HAS_TRACE
  if (TRACE_ParseCommand(cmd, handled, io)!=ERR_OK) {
    return ERR_FAILED;
  }
#endif
#if PL_HAS_RADIO
  if (RADIO_ParseCommand(cmd, handled, io)!=ERR_OK) {
    return ERR_FAILED;
  }
#endif
#if PL_HAS_REMOTE
  if (REMOTE_ParseCommand(cmd, handled, io)!=ERR_OK) {
    return ERR_FAILED;
  }
#endif
  return ERR_OK;
}

#if PL_HAS_RTOS
static portTASK_FUNCTION(ShellTask, pvParameters) {
  char cmd_buf[32];

  (void)pvParameters;
  (void)CLS1_ParseCommand(CLS1_CMD_HELP, CLS1_GetStdio(), ParseCommand); /* print help and prints as well the prompt */
  for(;;) {
#if PL_USE_USB_SCI
    static char_t usb_tx_buf[USB1_DATA_BUFF_SIZE];
    (void)USB1_App_Task(usb_tx_buf, sizeof(usb_tx_buf)); /* Call the USB application task */
#endif
    (void)CLS1_ReadAndParseCmd(cmd_buf, sizeof(cmd_buf), CLS1_GetStdio(), ParseCommand);
#if 1 && PL_HAS_QUEUE
    {
      const char_t *msg;

      msg = QUEUE_ReceiveMessage();
      if (msg!=NULL) {
        CLS1_SendStr(msg, CLS1_GetStdio()->stdOut);
        FRTOS1_vPortFree((void*)msg);
      }
    }
#endif
    //WAIT1_Waitms(50);
#if 1 && PL_HAS_I2C
    if (I2C_ReceiveCommand(cmd_buf, sizeof(cmd_buf))==ERR_OK) {
      bool handled = FALSE;

      (void)ParseCommand(cmd_buf, &handled, CLS1_GetStdio());
    }
#endif
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  }
}
#endif /* PL_HAS_RTOS */


#if !PL_HAS_RTOS
void SHELL_ParseLine(const char_t *cmd) {
  (void)CLS1_ParseCommand(cmd, CLS1_GetStdio(), ParseCommand); /* print help and prints as well the prompt */
}
#endif

#if !PL_HAS_RTOS
void SHELL_ReadAndParseLine(void) {
  char_t cmd_buf[32];

#if PL_USE_USB_SCI
  static char_t usb_tx_buf[USB1_DATA_BUFF_SIZE];
  if (USB1_App_Task(usb_tx_buf, sizeof(usb_tx_buf))!=ERR_OK) { /* Call the USB application task */
    return;
  }
#endif
  (void)CLS1_ReadAndParseCmd(cmd_buf, sizeof(cmd_buf), CLS1_GetStdio(), ParseCommand);
}
#endif

void SHELL_Init(void) {
#if PL_USE_USB_SCI
  USB1_Init(); /* Initialize the USB */
#endif
#if PL_HAS_RTOS
  CLS1_Init(); /* create mutex/semaphore */
#if PL_HAS_RTOS_TRACE
  {
    xSemaphoreHandle sem = CLS1_GetSemaphore();;
    if (sem!=NULL) {
      Ptrc1_vTraceSetQueueName(sem, "ShellSem");
    }
  }
#endif
  if (FRTOS1_xTaskCreate(ShellTask, (signed portCHAR *)"Shell", configMINIMAL_STACK_SIZE+150, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
}

#endif /* PL_HAS_SHELL */

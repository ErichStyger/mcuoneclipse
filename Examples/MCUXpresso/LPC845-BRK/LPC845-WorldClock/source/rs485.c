/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_RS485
#include "McuGPIO.h"
#include "McuShellUart.h"
#include "McuShell.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "Shell.h"
#include "nvmc.h"

/* RS-485 EN/DE: PIO01_4 */
#define RS485_TXRX_EN_GPIO       GPIO
#define RS485_TXRX_EN_PORT       1U
#define RS485_TXRX_EN_PIN        4U
#define RS485_TXRX_EN_IOCON      IOCON_INDEX_PIO1_4

static McuGPIO_Handle_t RS485_TxRxEn;

void RS485_RxEnable(void) {
  McuGPIO_SetLow(RS485_TxRxEn);
}

void RS485_TxEnable(void) {
  McuGPIO_SetHigh(RS485_TxRxEn);
}

static void RS485_SendChar(unsigned char ch) {
  McuShellUart_stdio.stdOut(ch);
}

static void RS485_ReadChar(uint8_t *c) {
  *c = '\0'; /* only sending on this channel */
}

static bool RS485_CharPresent(void) {
  return false; /* only sending on this channel */
}

McuShell_ConstStdIOType RS485_stdio = {
    (McuShell_StdIO_In_FctType)RS485_ReadChar, /* stdin */
    (McuShell_StdIO_OutErr_FctType)RS485_SendChar,  /* stdout */
    (McuShell_StdIO_OutErr_FctType)RS485_SendChar,  /* stderr */
    RS485_CharPresent /* if input is not empty */
  };

static void RS485_SendStr(unsigned char *str) {
  while(*str!='\0') {
    RS485_stdio.stdOut(*str++);
  }
}


/* Protocol:
 * #@<addr> <cmd>\n
 * Response: "@0 OK\n" or "@0 NOK\n"
 *
 * Note: # is for silent commands (to not print a prompt)
 * Examples:
 * #@0x12 cmd 0  //
 */

static const unsigned char *RS485_CmdMapper[] =
{
    /* 0 */ (const unsigned char*)"stepper zero all",
};

uint8_t RS485_LowLevel_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;
  int32_t addr, command;

  *handled = TRUE;
  if (*cmd=='@') {
    p = cmd+1;
    if (McuUtility_xatoi(&p, &addr)==ERR_OK && addr==NVMC_GetRS485Addr()) { /* check for "@<RS485_DEVICE_ADDR>" */
      if (McuUtility_strncmp((char*)p, " cmd ", sizeof(" cmd ")-1)==0) {
        uint8_t res = ERR_FAILED;;

        RS485_TxEnable(); /* enable communication */
        p += sizeof(" cmd ")-1;
        if (McuUtility_xatoi(&p, &command)==ERR_OK) { /* short command with number, e.g. "#@0x12 cmd 0" */
          if (command >= 0 && command<sizeof(RS485_CmdMapper)/sizeof(RS485_CmdMapper[0])) {
            res = SHELL_ParseCommand((unsigned char*)RS485_CmdMapper[command], &RS485_stdio);
          } else {
            res = ERR_FAILED;
          }
        } else { /* pass as-is */
          res = SHELL_ParseCommand((unsigned char*)p, &RS485_stdio);
        } /* if */

        if (res==ERR_OK) {
          RS485_SendStr((unsigned char*)"\n@0 OK\n");
        } else {
          RS485_SendStr((unsigned char*)"\n@0 NOK\n");
        }
        RS485_RxEnable(); /* disable communication */
      }
  #if 0 /* debug only */
      SHELL_SendString((unsigned char*)"RS-485 OK Rx: '");
      SHELL_SendString((unsigned char*)cmd);
      SHELL_SendString((unsigned char*)"'\r\n");
  #endif
    } else {
      SHELL_SendString((unsigned char*)"RS-485 NOK Rx: '");
      SHELL_SendString((unsigned char*)cmd);
      SHELL_SendString((unsigned char*)"'\r\n");
    }
  }
  return ERR_OK;
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[16];

  McuShell_SendStatusStr((unsigned char*)"rs", (unsigned char*)"RS-485 settings\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), NVMC_GetRS485Addr());
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  addr", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"rs", (unsigned char*)"Group of RS-458 commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  addr <addr>", (unsigned char*)"Set RS-485 address\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t RS485_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;
  int32_t val;
  NVMC_Data_t data;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "rs help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "rs status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "rs set ", sizeof("res addr ")-1)==0) {
    *handled = true;
    if (NVMC_IsErased()) {
      McuShell_SendStr((unsigned char*)"FLASH is erased, initialize it first!\r\n", io->stdErr);
      return ERR_FAILED;
    }
    p = cmd + sizeof("rs addr ")-1;
    if (McuUtility_xatoi(&p, &val)==ERR_OK && val>=0 && val<=0xff) {
      data = *NVMC_GetDataPtr(); /* struct copy */
      data.addrRS485 = val;
      return NVMC_WriteConfig(&data);
    }
  }
  return ERR_OK;
}

static const McuShell_ParseCommandCallback CmdParserTable[] =
{
  RS485_LowLevel_ParseCommand, /* low level command parser */
  NULL /* Sentinel */
};


static uint8_t cmdBuf[McuShell_DEFAULT_SHELL_BUFFER_SIZE];

static void RS485Task(void *pv) {
  (void)pv; /* not used */
  cmdBuf[0] = '\0';
  for(;;) {
    McuShell_ReadAndParseWithCommandTable(cmdBuf, sizeof(cmdBuf), &McuShellUart_stdio, CmdParserTable);
    vTaskDelay(pdMS_TO_TICKS(20));
  }
}

void RS485_Deinit(void) {
  RS485_TxRxEn = McuGPIO_DeinitGPIO(RS485_TxRxEn);
  McuShellUart_Deinit();
}

void RS485_Init(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);
  config.hw.gpio  = RS485_TXRX_EN_GPIO;
  config.hw.port  = RS485_TXRX_EN_PORT;
  config.hw.pin   = RS485_TXRX_EN_PIN;
  config.hw.iocon = RS485_TXRX_EN_IOCON;
  config.isInput = false;
  config.isHighOnInit = false;
  RS485_TxRxEn = McuGPIO_InitGPIO(&config);

  McuShellUart_Init();
  if (xTaskCreate(
      RS485Task,  /* pointer to the task */
      "RS-485", /* task name for kernel awareness debugging */
      1000/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    for(;;){} /* error! probably out of memory */
  }
  RS485_RxEnable();
}

#endif /* PL_CONFIG_USE_RS485 */

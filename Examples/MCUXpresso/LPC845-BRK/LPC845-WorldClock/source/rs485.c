/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_RS485
#include "McuGPIO.h"
#include "rs485Uart.h"
#include "McuShell.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "Shell.h"
#include "nvmc.h"
#include "McuWait.h"
#if PL_CONFIG_IS_CLIENT
  #include "Stepper.h"
#endif

typedef enum {
  RS485_RESPONSE_CONTINUE, /* continue scanning and parsing */
  RS485_RESPONSE_OK, /* ok response */
  RS485_RESPONSE_NOK, /* not ok response */
  RS485_RESPONSE_TIMEOUT, /* timout */
} RS485_Response_e;

uint8_t RS485_GetAddress(void) {
  return NVMC_GetRS485Addr();
}

static void RS485_SendChar(unsigned char ch) {
  RS485Uart_stdio.stdOut(ch);
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

static const unsigned char *RS485_CmdMapper[] =
{
    /* 0 */ (const unsigned char*)"stepper zero all",
};

typedef enum {
  CMD_PARSER_INIT,
  CMD_PARSER_START_DETECTED, /* start '@' detected */
  CMD_PARSER_SCAN_DST_ADDR, /* scanning destination address */
  CMD_PARSER_SCAN_SRC_ADDR,  /* scan source address */
  CMD_PARSER_SCAN_OK_NOK,   /* reading NOK or OK */
} CMD_ParserState_e;

static RS485_Response_e Scan(CMD_ParserState_e *state, unsigned char ch, unsigned char *buf, size_t bufSize, uint8_t fromAddr) {
  /* scan for "@<dstaddr> <fromAddr> OK"
   * or "@<dstaddr> <fromAddr> NOK"
   */

  if (ch=='@') { /* a marker? start scanning again */
    *state = CMD_PARSER_START_DETECTED;
  }
  for(;;) { /* breaks or returns */
    switch(*state) {
      case CMD_PARSER_INIT:
        buf[0] = '\0'; /* reset buffer */
        if (ch=='@') { /* a marker? start scanning again */
          *state = CMD_PARSER_START_DETECTED;
          break; /* continue state machine */
        }
        return RS485_RESPONSE_CONTINUE;

       case CMD_PARSER_START_DETECTED:
        buf[0] = '\0'; /* reset buffer */
        *state = CMD_PARSER_SCAN_DST_ADDR;
        return RS485_RESPONSE_CONTINUE;

       case CMD_PARSER_SCAN_DST_ADDR:
         McuUtility_chcat(buf, bufSize, ch);
         if (ch==' ') {
           const unsigned char *p;
           int32_t val;

           p = &buf[0];
           if (McuUtility_xatoi(&p, &val)==ERR_OK && val==RS485_GetAddress()) {
             buf[0] = '\0'; /* reset buffer */
             *state = CMD_PARSER_SCAN_SRC_ADDR;
             return RS485_RESPONSE_CONTINUE;
           } else {
             buf[0] = '\0'; /* reset buffer */
             return RS485_RESPONSE_CONTINUE;
           }
         } else if (ch=='\n') { /* failed */
           *state = CMD_PARSER_INIT;
         }
         return RS485_RESPONSE_CONTINUE;

       case CMD_PARSER_SCAN_SRC_ADDR:
         McuUtility_chcat(buf, bufSize, ch);
         if (ch==' ') {
           const unsigned char *p;
           int32_t val;

           p = &buf[0];
           if (McuUtility_xatoi(&p, &val)==ERR_OK && val==fromAddr) {
             buf[0] = '\0'; /* reset buffer */
             *state = CMD_PARSER_SCAN_OK_NOK;
             return RS485_RESPONSE_CONTINUE;
           } else {
             *state = CMD_PARSER_INIT;
           }
         } else if (ch=='\n') { /* failed */
           *state = CMD_PARSER_INIT;
         }
         return RS485_RESPONSE_CONTINUE;

       case CMD_PARSER_SCAN_OK_NOK:
          McuUtility_chcat(buf, bufSize, ch);
          if (McuUtility_strncmp((char*)buf, (char*)"OK", sizeof("OK")-1)==0) { /* a match! */
            buf[0] = '\0'; /* reset buffer */
            *state = CMD_PARSER_INIT;
            return RS485_RESPONSE_OK;
          } else if (McuUtility_strncmp((char*)buf, (char*)"NOK", sizeof("NOK")-1)==0) { /* a match! */
            buf[0] = '\0'; /* reset buffer */
            *state = CMD_PARSER_INIT;
            return RS485_RESPONSE_NOK;
          } else if (ch=='\n') { /* failed */
            *state = CMD_PARSER_INIT;
            break; /* continue in state machine */
          }
          return RS485_RESPONSE_CONTINUE;

      default:
        break;
    } /* switch */
    /* get here with a break */
  } /* for */
}

static RS485_Response_e WaitForResponse(int32_t timeoutMs, uint8_t fromAddr) {
  unsigned char buf[24]; /* "@<addr> <fromAddr> OK" or "@<addr> <fromAddr> NOK" */
  unsigned char ch;
  RS485_Response_e resp;
  CMD_ParserState_e state = CMD_PARSER_INIT;

  for(;;) { /* returns */
    ch = RS458Uart_GetResponseQueueChar();
    if (ch!='\0') {
      resp = Scan(&state, ch, buf, sizeof(buf), fromAddr);
      if (resp==RS485_RESPONSE_OK || resp==RS485_RESPONSE_NOK) {
        return resp;
      }
    } else { /* empty input buffer: wait */
      vTaskDelay(pdMS_TO_TICKS(10));
      timeoutMs -= 10;
      if (timeoutMs<=0) {
        return RS485_RESPONSE_TIMEOUT;
      }
    }
  } /* for */
}

uint8_t RS485_SendCommand(uint8_t dstAddr, unsigned char *cmd, int32_t timeoutMs) {
  /* example: send "#@16:0 cmd stepper zero all" */
  unsigned char buf[McuShell_DEFAULT_SHELL_BUFFER_SIZE];
  uint8_t res = ERR_OK;

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)("@"));
  McuUtility_strcatNum8u(buf, sizeof(buf), dstAddr); /* add destination address */
  McuUtility_chcat(buf, sizeof(buf), ' ');
  McuUtility_strcatNum8u(buf, sizeof(buf), RS485_GetAddress()); /* add src address */
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)(" cmd "));
  McuUtility_strcat(buf, sizeof(buf), cmd);
  McuUtility_chcat(buf, sizeof(buf), '\n');

  int nofRetry = 3;
  RS485_Response_e resp;

  for(;;) { /* breaks */
    RS458Uart_ClearResponseQueue();
    RS485_SendStr(buf);
    if (dstAddr==0) {
      /* do not wait for a OK/NOK response for broadcasts */
      res = ERR_OK;
      break; /* leave loop */
    }
    resp = WaitForResponse(timeoutMs, dstAddr);
    if (resp==RS485_RESPONSE_OK) {
      res = ERR_OK;
      break; /* leave loop */
    }
    /* NOK or timeout */
    nofRetry--; /* try again */
    if (nofRetry==0) { /* tried enough */
      res = ERR_FAILED;
      break; /* leave loop */
    }
  }
  return res;
}

uint8_t RS485_LowLevel_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;
  int32_t addr, srcAddr, command;
  uint8_t buf[16];

  /* command is for example. "#@1 0 cmd #help" with the hash tag removed by the shell parser */
  *handled = TRUE;
  if (*cmd=='@') {
    p = cmd+1; /* skip '@' */
    if (   McuUtility_xatoi(&p, &addr)==ERR_OK
        && (addr==RS485_GetAddress() || addr==0) /* broadcast */ /* matching destination address */
        && McuUtility_xatoi(&p, &srcAddr)==ERR_OK /* get source address */
        )
    { /* check for "@<DST_ADDR>:<SRC_ADDR>" */
      if (McuUtility_strncmp((char*)p, " cmd ", sizeof(" cmd ")-1)==0) {
        uint8_t res = ERR_FAILED;

        p += sizeof(" cmd ")-1; /* skip cmd string */
        if (McuUtility_xatoi(&p, &command)==ERR_OK) { /* short command with number, e.g. "@0x12 0 cmd 0" */
          if (command >= 0 && command<sizeof(RS485_CmdMapper)/sizeof(RS485_CmdMapper[0])) {
            res = SHELL_ParseCommand((unsigned char*)RS485_CmdMapper[command], &RS485_stdio, true);
          } else {
            res = ERR_FAILED;
          }
      #if PL_CONFIG_IS_CLIENT
        } else if (McuUtility_strcmp((char*)p, (char*)"stepper idle")==0) {
          if (STEPPER_IsIdle()) {
            res = ERR_OK;  /* ERR_OK if board is idle */
          } else {
            res = ERR_FAILED;
          }
      #endif
        } else { /* pass as-is */
          res = SHELL_ParseCommand((unsigned char*)p, &RS485_stdio, true);
        } /* if */
        /* send response back */
        McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"@");
        McuUtility_strcatNum8u(buf, sizeof(buf), srcAddr);
        McuUtility_chcat(buf, sizeof(buf), ' ');
        McuUtility_strcatNum8u(buf, sizeof(buf), RS485_GetAddress());
        if (addr!=0) { /* do *not* send response for broadcast messages */
          if (res==ERR_OK) {
            McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OK\n");
          } else {
            McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" NOK\n");
          }
          RS485_SendStr(buf);
        }
      }
    }
#if PL_CONFIG_IS_MASTER
  } else {
    /* not a command, print it ... */
    SHELL_SendString((unsigned char *)cmd);
    SHELL_SendString((unsigned char*)"\r\n");
#endif
  }
  return ERR_OK;
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[16];

  McuShell_SendStatusStr((unsigned char*)"rs", (unsigned char*)"RS-485 settings\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), RS485_GetAddress());
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  addr", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"rs", (unsigned char*)"Group of RS-458 commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  addr <addr>", (unsigned char*)"Set RS-485 address\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  send <text>", (unsigned char*)"Send a text to the RS-485 bus\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  sendcmd <addr> <text>", (unsigned char*)"Send a command to the RS-485 address and check response\r\n", io->stdOut);
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
  } else if (McuUtility_strncmp((char*)cmd, "rs addr ", sizeof("rs addr ")-1)==0) {
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
    return ERR_FAILED;
  } else if (McuUtility_strncmp((char*)cmd, "rs send ", sizeof("rs send ")-1)==0) {
    *handled = true;
    RS485_SendStr((unsigned char*)cmd+sizeof("rs send ")-1);
    RS485_SendStr((unsigned char*)("\n"));
  } else if (McuUtility_strncmp((char*)cmd, "rs sendcmd ", sizeof("rs sendcmd ")-1)==0) {
    *handled = true;
    p = cmd + sizeof("rs sendcmd ")-1;
    if (McuUtility_xatoi(&p, &val)==ERR_OK) { /* parse destination address */
      while (*p==' ') { /* skip leading spaces */
        p++;
      }
      return RS485_SendCommand(val, (unsigned char*)p, 3000);
    }
    return ERR_FAILED;
  }
  return ERR_OK;
}

static const McuShell_ParseCommandCallback CmdParserTable[] =
{
  RS485_LowLevel_ParseCommand, /* low level command parser */
  NULL /* Sentinel */
};

static uint8_t cmdBuf[McuShell_DEFAULT_SHELL_BUFFER_SIZE*3]; /* to print longer lines */

static void RS485Task(void *pv) {
  (void)pv; /* not used */
  //RS485Uart_SendString((unsigned char*)"Hello World!");
  cmdBuf[0] = '\0';
  for(;;) {
    McuShell_ReadAndParseWithCommandTableExt(cmdBuf, sizeof(cmdBuf), &RS485Uart_stdio, CmdParserTable, true);
    if (!RS485Uart_stdio.keyPressed()) { /* if nothing in input, give back some CPU time */
      vTaskDelay(pdMS_TO_TICKS(20));
    }
  }
}

void RS485_Deinit(void) {
  RS485Uart_Deinit();
}

void RS485_Init(void) {
  RS485Uart_Init();
  if (xTaskCreate(
      RS485Task,  /* pointer to the task */
      "RS-485", /* task name for kernel awareness debugging */
      1000/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+3,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    for(;;){} /* error! probably out of memory */
  }
}

#endif /* PL_CONFIG_USE_RS485 */

/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_RS485
#include "rs485.h"
#include "McuGPIO.h"
#include "rs485Uart.h"
#include "McuShell.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuLog.h"
#include "Shell.h"
#if PL_CONFIG_USE_WDT
  #include "watchdog.h"
#endif

static void RS485_SendChar(unsigned char ch) {
  RS485Uart_stdio.stdOut(ch);
}

static void RS485_NullSend(unsigned char ch) {
  /* do nothing */
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

McuShell_ConstStdIOType RS485_stdioBroadcast = {
    (McuShell_StdIO_In_FctType)RS485_ReadChar, /* stdin */
    (McuShell_StdIO_OutErr_FctType)RS485_NullSend,  /* stdout */
    (McuShell_StdIO_OutErr_FctType)RS485_NullSend,  /* stderr */
    RS485_CharPresent /* if input is not empty */
  };


static void RS485_SendStr(unsigned char *str) {
  while(*str!='\0') {
    RS485_stdio.stdOut(*str++);
  }
}

static void RS485_SendData(uint8_t *data, size_t dataSize) {
  while(dataSize>0) {
    RS485_stdio.stdOut(*data++);
    dataSize--;
  }
}

static uint8_t calcCheckSum(uint8_t *buf, size_t bufSize) {
  int32_t sum = 0;
  for(int i=1; i<bufSize-2; i++) { /* sum up everything up including EOT at the end, but without SOT at the start */
    sum += buf[i];
  }
  sum &= 0xff; /* chop to a byte */
  sum ^= 255; /* EXOR it */
  sum += 1; /* add one */
  return sum;
}

static const char NumToHexChar[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

static void StoreASCIIHex8(uint8_t *buf, uint8_t val) {
  /* store checksum as ASCII, e.b. 0x4A  => '4' 'A' */
  buf[0] = NumToHexChar[val/16];
  buf[1] = NumToHexChar[val%16];
}
// 0x30 => '0'
// 0x31 => '1'
// 0x32 => '2'
// 0x33 => '3'

#define FLIP_DOT_DEVICE_ADDRESS  (1) /* position of rotary switch */
#define FLIP_DOT_NOF_COL         (20)
#define FLIP_DOT_NOF_ROW         (14)
#define FLIP_DOT_NOF_DATA        (FLIP_DOT_NOF_COL*((FLIP_DOT_NOF_ROW-1)/8)+1))
#define FLIP_DOT_NOF_BUF_BYTES   (1/*SOT*/ +1/*cmd*/ +1/*addr*/ +2/*nof*/ +FLIP_DOT_NOF_DATA +1/*EOT*/ +2/*checksum*/)

#define FLIP_DOT_BUF_POS_SOT     (0)
#define FLIP_DOT_BUF_POS_CMD     (1)
#define FLIP_DOT_BUF_POS_ADDR    (2)
#define FLIP_DOT_BUF_POS_NOF     (3)
#define FLIP_DOT_BUF_POS_DATA    (5)
#define FLIP_DOT_BUF_POS_EOT     (FLIP_DOT_BUF_POS_DATA+FLIP_DOT_NOF_DATA)
#define FLIP_DOT_BUF_POS_CHECK   (FLIP_DOT_BUF_POS_EOT+1)

static void test(void) {
  /* see https://github.com/hawkz/Hanover_Flipdot */
  /* https://cute766.info/adventures-with-flippy-the-flip-dot-display-software-and-teardown/ */
#if 0
  uint8_t buf[] = {
      0x02, /* SOT */
      0x31, /* command: '0': text message, '1': graphics message, followed by the address of the device */
      '0'+FLIP_DOT_DEVICE_ADDRESS+1, /* address: '1', 'val'+1 ('0' is broadcast) */
      0x32, 0x41, /* how man bytes (width*height/8) 0x32 0x41 => '2' 'A' => 0x2A => 42 bytes => 84 characters */  /* Example: '5' '4' => 0x54 => 84 bytes */
      0x30, 0x30, 0x30, 0x30, 0x30, 0x38, 0x30, 0x36, 0x46, 0x43, 0x30,  /* Data */
      0x37, 0x46, 0x43, 0x30, 0x37, 0x30, 0x30, 0x30, 0x36, 0x30, 0x30,
      0x30, 0x30, 0x46, 0x38, 0x30, 0x33, 0x46, 0x43, 0x30, 0x37, 0x30,
      0x43, 0x30, 0x36, 0x30, 0x43, 0x30, 0x36, 0x46, 0x43, 0x30, 0x37,
      0x46, 0x38, 0x30, 0x33, 0x30, 0x30, 0x30, 0x30, 0x46, 0x38, 0x30,
      0x33, 0x46, 0x43, 0x30, 0x37, 0x30, 0x43, 0x30, 0x36, 0x30, 0x43,
      0x30, 0x36, 0x46, 0x43, 0x30, 0x37, 0x46, 0x38, 0x30, 0x33, 0x30,
      0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,   /* End of data */
      0x03, /* EOT, footer */
      0x34, 0x41   /* checksum: 0x4A */
  };
#else
  uint8_t buf[] = {
      0x02, /* SOT */
      0x31, /* command: '0': text message, '1': graphics message, followed by the address of the device */
      '0'+FLIP_DOT_DEVICE_ADDRESS+1, /* address: '1', 'val'+1 ('0' is broadcast) */
      0x32, 0x41, /* how man bytes (20*14+2 /8) 0x32 0x41 => '2' 'A' => 0x2A => 42 bytes => 84 characters */  /* Example: '5' '4' => 0x54 => 84 bytes */
      0x30, 0x30, 0x30, 0x30, 0x30, 0x38, 0x30, 0x36, 0x46, 0x43, 0x30,  /* Data: treated column by column, from upper left to lower right */
      0x37, 0x46, 0x43, 0x30, 0x37, 0x30, 0x30, 0x30, 0x36, 0x30, 0x30,
      0x30, 0x30, 0x46, 0x38, 0x30, 0x33, 0x46, 0x43, 0x30, 0x37, 0x30,
      0x43, 0x30, 0x36, 0x30, 0x43, 0x30, 0x36, 0x46, 0x43, 0x30, 0x37,
      0x46, 0x38, 0x30, 0x33, 0x30, 0x30, 0x30, 0x30, 0x46, 0x38, 0x30,
      0x33, 0x46, 0x43, 0x30, 0x37, 0x30, 0x43, 0x30, 0x36, 0x30, 0x43,
      0x30, 0x36, 0x46, 0x43, 0x30, 0x37, 0x46, 0x38, 0x30, 0x33, 0x30,
      0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,   /* End of data */
      0x03, /* EOT, footer */
      0x34, 0x41   /* checksum: 0x4A */
  };
#endif
  uint8_t checkSum = calcCheckSum(buf, sizeof(buf));
  StoreASCIIHex8(&buf[sizeof(buf)-2], checkSum);
  RS485_SendData(buf, sizeof(buf));
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  McuShell_SendStatusStr((unsigned char*)"rs", (unsigned char*)"RS-485 settings\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"rs", (unsigned char*)"Group of RS-458 commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  send <text>", (unsigned char*)"Send a text to the RS-485 bus\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  test", (unsigned char*)"Test\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t RS485_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
//  const unsigned char *p;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "rs help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "rs status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "rs send ", sizeof("rs send ")-1)==0) {
    *handled = true;
    RS485_SendStr((unsigned char*)cmd+sizeof("rs send ")-1);
    RS485_SendStr((unsigned char*)("\n"));
  } else if (McuUtility_strcmp((char*)cmd, "rs test")==0) {
    *handled = true;
    test();
  }
  return ERR_OK;
}

void RS485_Deinit(void) {
  RS485Uart_Deinit();
}

void RS485_Init(void) {
  RS485Uart_Init();
}

#endif /* PL_CONFIG_USE_RS485 */

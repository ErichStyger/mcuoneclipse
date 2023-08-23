/*
 * Copyright (c) 2021-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuSWO.h"
#if McuSWO_CONFIG_HAS_SWO
#include "McuLib.h"
#include "McuUtility.h"
#include "McuShell.h"
#include "McuXFormat.h"
#include "board.h"
#include "pin_mux.h"
#include <assert.h>
#include <stdio.h>
#if defined (__NEWLIB__)
  #include <sys/stat.h>
#endif
#if McuLib_CONFIG_CPU_IS_KINETIS
  #include "fsl_clock.h"
  #include "fsl_port.h"
#endif

#if defined (__REDLIB__) && McuSWO_CONFIG_RETARGET_STDIO
  #error "SWO standard I/O redirection does not work with RedLib: use newlib (none) or newlib-nano (none) instead"
#endif

/* standard I/O handles */
#define McuSWO_StdIn   (0)
#define McuSWO_StdOut  (1)
#define McuSWO_StdErr  (2)

static uint32_t SWO_traceClock; /* clock feed into the ARM CoreSight */

#define McuSWO_ITM_RXBUFFER_EMPTY    ((int32_t)0x5AA55AA5) /* special pattern to indicate empty buffer */

volatile int32_t ITM_RxBuffer = McuSWO_ITM_RXBUFFER_EMPTY; /* implementation of buffer for Rx, must use this variable name as checked by the debugger */

static inline int32_t SWO_ReceiveChar(void) {
  int32_t ch = EOF; /* EOF, no character available */

  if (ITM_RxBuffer != McuSWO_ITM_RXBUFFER_EMPTY) {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = McuSWO_ITM_RXBUFFER_EMPTY; /* mark it ready for next character */
  }
  return ch;
}

static inline bool SWO_WriteChar(char c, uint8_t portNo) {
  volatile int timeout = 5000; /* arbitrary timeout value */
  while (ITM->PORT[portNo].u32 == 0) {
    /* Wait until STIMx is ready, then send data */
    timeout--;
    if (timeout==0) {
      return false; /* not able to send */
    }
  }
  ITM->PORT[portNo].u8 = c;
  return true;
}

#if McuSWO_CONFIG_RETARGET_STDIO
static void SWO_WriteBuf(char *buf, size_t count, uint8_t portNo) {
  while(count>0) {
    SWO_WriteChar(*buf, portNo);
    buf++;
    count--;
  }
}
#endif

static inline bool SWO_Enabled(uint8_t portNo) {
  /* Check if Trace Control Register (ITM->TCR at 0xE0000E80) is set */
  if ((ITM->TCR&ITM_TCR_ITMENA_Msk) == 0) { /* check Trace Control Register if ITM trace is enabled*/
    return false; /* not enabled? */
  }
  /* Check if the requested channel stimulus port (ITM->TER at 0xE0000E00) is enabled */
  if ((ITM->TER & (1ul<<portNo))==0) { /* check Trace Enable Register if requested port is enabled */
    return false; /* requested port not enabled? */
  }
  return true;
}

/*!
 * \brief Sends a character over the SWO channel
 * \param c Character to be sent
 * \param portNo SWO channel number, value in the range of 0 to 31
 */
void McuSWO_PrintChar(char c, uint8_t portNo) {
  if (!SWO_Enabled(portNo)) {
    return;
  }
  (void)SWO_WriteChar(c, portNo);
}

#if McuSWO_CONFIG_RETARGET_STDIO
/* retarget low level stdout write routines to SWO */
#if defined (__REDLIB__) /* low level functions depend on library used */
int __sys_write(int fd, char *buffer, int count) {
#elif defined (__NEWLIB__)
int _write(int fd, char *buffer, unsigned int count) {
#endif
  if(fd!=McuSWO_StdOut && fd!=McuSWO_StdErr) {
    return EOF; /* failed */
  }
  if (!SWO_Enabled(McuSWO_CONFIG_TERMINAL_CHANNEL)) {
    return EOF; /* failed */
  }
  SWO_WriteBuf(buffer, count, McuSWO_CONFIG_TERMINAL_CHANNEL);
  return count; /* return the number of chars written */
}
#endif /* McuSWO_CONFIG_RETARGET_STDIO */

/*!
 * \brief Sends a string over SWO to the host
 * \param s String to send
 * \param portNumber Port number, 0-31, use 0 for normal debug strings
 */
static void PrintString(const unsigned char *s, uint8_t portNumber) {
  while (*s!='\0') {
    McuSWO_PrintChar(*s++, portNumber);
  }
}

void McuSWO_SendStr(const unsigned char *str) {
  PrintString(str, McuSWO_CONFIG_TERMINAL_CHANNEL);
}

unsigned McuSWO_printf(const char *fmt, ...) {
  va_list args;
  unsigned int count = 0;

  va_start(args,fmt);
  count = McuXFormat_xvformat(McuShell_printfPutChar, (void*)McuSWO_GetStdio()->stdOut, fmt, args);
  va_end(args);
  return count;
}

bool McuSWO_StdIOKeyPressed(void) {
  if (ITM_RxBuffer != McuSWO_ITM_RXBUFFER_EMPTY) {
    return true;
  }
  return false;
}

void McuSWO_StdIOReadChar(uint8_t *ch) {
  int res;

  res = SWO_ReceiveChar();
  if (res==-1) { /* no character present */
    *ch = '\0';
  } else {
    *ch = (uint8_t)res; /* return character */
  }
}

uint8_t McuSWO_ReadAppendLine(unsigned char *buf, size_t bufSize) {
  unsigned char ch;

  if (McuSWO_StdIOKeyPressed()) { /* character present? */
    McuSWO_stdio.stdIn(&ch); /* read character */
    if (ch!='\0') { /* still available? */
      McuUtility_chcat(buf, bufSize, ch);
      if (ch=='\n') {
        return ERR_OK;
      }
    } /* if */
  } /* if */
  return ERR_BUSY; /* not reached the end of line yet */
}

void McuSWO_ReadLineBlocking(unsigned char *buf, size_t bufSize) {
  buf[0] = '\0'; /* init buffer */
  for(;;) { /* breaks */
    if (McuSWO_ReadAppendLine(buf, bufSize)==ERR_OK) { /* '\n' received */
      return;
    }
  } /* for */
}

#if McuSWO_CONFIG_RETARGET_STDIO
#if defined (__NEWLIB__)
  int _close_r(struct _reent *p, int fd) {
    return -1; /* 0: ok, -1 error.  Because no file should have been opened, we return an error */
  }

  /* return the status of an open file */
  int _fstat_r(struct _reent *p, int fd, struct stat *stp) {
    stp->st_mode = S_IFCHR; /* identify as character special device. This forces it as a one-byte-read device */
    return 0; /* ok */
  }

  /* checks if a descriptor is a file or a terminal (tty) */
  int _isatty_r(struct _reent *p, int fd) {
    return 1; /* return 1 if fd is a terminal file descriptor, otherwise return 0 */
  }

  /* position the offset within file */
  int _lseek_r(struct _reent *p, int fd, int offset, int whence) {
    return 0; /* return new position. Simply return 0 which implies the file is empty */
  }
#endif /* __NEWLIB__ */

  void _kill(int pid, int sig) {
    return; /* do nothing */
  }

  int _getpid(void) {
    return -1; /* no process */
  }

#if defined (__REDLIB__)
  void __sys_appexit(void) {
    for(;;) {}
  }

  int __sys_seek(int fd, int pos) {
    return 0;
  }

  int __sys_flen(int fd) {
    return 0;
  }

  int __sys_istty(int fd) {
    return 1; /* return 1 if fd is a terminal file descriptor, otherwise return 0 */
  }

  int __sys_readc(void) {
    int32_t c = -1;

    if (!SWO_Enabled(McuSWO_CONFIG_TERMINAL_CHANNEL)) {
      return -1; /* eof */
    }
    return SWO_ReceiveChar();
  }

  int __sys_read(int file, char *buf, int len) {
    *buf = __sys_readc();
    return 1;
  }
#elif defined (__NEWLIB__)
  int _read(int fd, char *buffer, int size) {
    if(fd!=McuSWO_StdIn) { /* 0 is stdin */
      return EOF; /* failed */
    }
    if (!SWO_Enabled(McuSWO_CONFIG_TERMINAL_CHANNEL)) {
      return EOF; /* failed */
    }
    /* only read a single byte */
    int32_t c;
    do {
      c = SWO_ReceiveChar();
    } while (c==EOF); /* blocking */
    *buffer = c;
    return 1; /* number of bytes read */
  }
#endif /* newlib or redlib */

#endif /* McuSWO_CONFIG_RETARGET_STDIO */

#if McuSWO_CONFIG_RETARGET_STDIO
  static void ReadLine_McuLib(unsigned char *buf, size_t bufSize) {
    /* McuLib way: */
    McuSWO_SendStr((unsigned char*)"Enter some text and press ENTER:\n");
    McuSWO_ReadLineBlocking(buf, bufSize);
    McuSWO_printf("Received:");
    McuSWO_SendStr(buf);
  }

  static void ReadLine_getc(unsigned char *buf, size_t bufSize) {
    int c;
    size_t i = 0;

    /* C standard library way with getc() */
    memset(buf, 0, bufSize); /* initialize buffer */
    printf("getc: Enter some text and press ENTER:\n");
    do {
      do {
        c = getc(stdin);
      } while(c==EOF); /* poll for input */
      if (i<bufSize) { /* avoid buffer overflow */
        buf[i++] = c;
      }
    } while(c!='\n');
    buf[bufSize-1] = '\0'; /* terminate */
    printf("getc: %s", buf);
  }

  static void ReadLine_getchar(unsigned char *buf, size_t bufSize) {
    int c;
    size_t i = 0;

    /* C standard library way with getchar() */
    memset(buf, 0, bufSize); /* initialize buffer */
    printf("getchar: Enter some text and press ENTER:\n");
    do {
      do {
        c = getchar();
      } while(c==EOF);
      if (i<bufSize) { /* avoid buffer overflow */
        buf[i++] = c;
      }
    } while(c!='\n');
    buf[bufSize-1] = '\0';
    printf("getchar: %s", buf);
  }

  static void ReadLine_fgets(unsigned char *buf, size_t bufSize) {
    /* C standard library way with fgets() */
    char *p;

    printf("fgets: Enter a line and press ENTER:\n");
    p = fgets((char*)buf, bufSize, stdin);
    if (p!=NULL) {
      printf("fgets: %s\n", buf);
    } else {
      printf("fgets FAILED\n");
    }
  }

  static void ReadLine_scanf(unsigned char *buf, size_t bufSize) {
    /* C standard library way with scanf(). Actually, you better do NOT use scanf() for this, use fgets() instead! */
    int res;
    char ch;

    printf("scanf: Enter a single name/word and press ENTER:\n");
    assert(bufSize>=20);
    res = scanf("%20s%c", buf, &ch); /* note: ch for the newline */
    printf("scanf: %s, res: %d, ch:%d\n", buf, res, ch);
  }

  static void TestStdOut(void) {
    printf("Using printf(), putc and putchar with SWO\n");
    putc('*', stdout);
    putc('#', stderr);
    putchar('!');
    putchar('\n');
  }

  void McuSWO_TestStdio(void) {
    unsigned char buf[64];

    McuSWO_SendStr((unsigned char*)"Starting testing SWO ITM stdout redirection\n");
    TestStdOut();
    /* test varioud methods using stdin */
    ReadLine_McuLib(buf, sizeof(buf));
    ReadLine_getc(buf, sizeof(buf));
    ReadLine_getchar(buf, sizeof(buf));
    ReadLine_fgets(buf, sizeof(buf));
    ReadLine_scanf(buf, sizeof(buf));
    McuSWO_SendStr((unsigned char*)"Finished testing SWO ITM stdout redirection\n");
  }
#endif

void McuSWO_StdIOSendChar(uint8_t ch) {
  (void)SWO_WriteChar(ch, 0);
}

/* default standard I/O struct */
McuShell_ConstStdIOType McuSWO_stdio = {
    (McuShell_StdIO_In_FctType)McuSWO_StdIOReadChar, /* stdin */
    (McuShell_StdIO_OutErr_FctType)McuSWO_StdIOSendChar, /* stdout */
    (McuShell_StdIO_OutErr_FctType)McuSWO_StdIOSendChar, /* stderr */
    McuSWO_StdIOKeyPressed /* if input is not empty */
  };
uint8_t McuSWO_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */

McuShell_ConstStdIOTypePtr McuSWO_GetStdio(void) {
  return &McuSWO_stdio;
}

#if McuSWO_CONFIG_DO_MUXING
static void MuxSWOPin(void) {
#if McuLib_CONFIG_CPU_IS_LPC
  CLOCK_EnableClock(kCLOCK_Iocon);
  #if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16
  /* local settings copied from pin_mux.h: have them local here in case muxing is not done in Pins Tool */
    #define IOCON_PIO_ASW_DI_SWO 0x00u        /*!<@brief Analog switch is open (disabled) */
    #define IOCON_PIO_DIGITAL_EN_SWO 0x0100u  /*!<@brief Enables digital function */
    #define IOCON_PIO_FUNC6_SWO 0x06u         /*!<@brief Selects pin function 6 */
    #define IOCON_PIO_INV_DI_SWO 0x00u        /*!<@brief Input function is not inverted */
    #define IOCON_PIO_MODE_INACT_SWO 0x00u    /*!<@brief No addition pin function */
    #define IOCON_PIO_OPENDRAIN_DI_SWO 0x00u  /*!<@brief Open drain is disabled */
    #define IOCON_PIO_SLEW_STANDARD_SWO 0x00u /*!<@brief Standard mode, output slew rate control is enabled */

    const uint32_t port0_pin10_config = (/* Pin is configured as SWO */
                                         IOCON_PIO_FUNC6_SWO |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT_SWO |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD_SWO |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI_SWO |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN_SWO |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI_SWO |
                                         /* Analog switch is open (disabled) */
                                         IOCON_PIO_ASW_DI_SWO);
    /* PORT0 PIN10 (coords: 21) is configured as SWO */
    IOCON_PinMuxSet(IOCON, 0U, 10U, port0_pin10_config);

  #elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S69
  /* local settings copied from pin_mux.h: have them local here in case muxing is not done in Pins Tool */
  #define PIO0_10_FUNC_ALT6_SWO           0x06u
  #define PIO0_10_DIGIMODE_DIGITAL_SWO    0x01u

  IOCON->PIO[0][10] = ((IOCON->PIO[0][10] &
                        /* Mask bits to zero which are setting */
                        (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                       /* Selects pin function.
                        * : PORT010 (pin 21) is configured as SWO. */
                       | IOCON_PIO_FUNC(PIO0_10_FUNC_ALT6_SWO)

                       /* Select Digital mode.
                        * : Enable Digital mode.
                        * Digital input is enabled. */
                       | IOCON_PIO_DIGIMODE(PIO0_10_DIGIMODE_DIGITAL_SWO));
  #else
    #error "NYI"
  #endif
#elif McuLib_CONFIG_CPU_IS_KINETIS && McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K64FN
  /* Port A Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortA);

  /* PORTA2 (pin 36) is configured as TRACE_SWO */
  PORT_SetPinMux(PORTA, 2U, kPORT_MuxAlt7);

  PORTA->PCR[2] = ((PORTA->PCR[2] &
                    /* Mask bits to zero which are setting */
                    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK | PORT_PCR_ISF_MASK)))

                   /* Pull Select: Internal pulldown resistor is enabled on the corresponding pin, if the
                    * corresponding PE field is set. */
                   | PORT_PCR_PS(kPORT_PullDown)

                   /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
                   | PORT_PCR_PE(kPORT_PullDisable)

                   /* Drive Strength Enable: Low drive strength is configured on the corresponding pin, if pin
                    * is configured as a digital output. */
                   | PORT_PCR_DSE(kPORT_LowDriveStrength));
#else
  #error "NYI"
#endif
}
#endif /* #if McuSWO_CONFIG_DO_MUXING */

static void SetSWOSpeed(uint32_t traceClockHz, uint32_t SWOSpeed) {
  uint32_t SWOPrescaler = (traceClockHz / SWOSpeed) - 1; /* SWOSpeed in Hz, note that traceClockHz is expected to be match the CPU core clock */

  TPI->ACPR = SWOPrescaler; /* "Async Clock Prescaler Register". Scale the baud rate of the asynchronous output */
}

#if McuSWO_CONFIG_SHELL_ENABLED
static void PrintRegHex(McuShell_ConstStdIOType *io, uint32_t regVal, const char *statusStr, const char *desc) {
  uint8_t buf[48];

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum32Hex(buf, sizeof(buf), regVal);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)desc);
  McuShell_SendStatusStr((unsigned char*)statusStr, buf, io->stdOut);
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  uint8_t buf[72];

  McuShell_SendStatusStr((const unsigned char*)"McuSWO", (const unsigned char*)"McuSWO module status\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"traceClock: ");
  McuUtility_strcatNum32u(buf, sizeof(buf), SWO_traceClock);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" Hz, Baud: ");
  McuUtility_strcatNum32u(buf, sizeof(buf), SWO_traceClock/(TPI->ACPR+1));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  Clocking", buf, io->stdOut);

  /* Core Debug */
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum32Hex(buf, sizeof(buf), CoreDebug->DEMCR);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (DEMCR)\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  CoreDebug", buf, io->stdOut);

  McuShell_SendStatusStr((const unsigned char*)"  DWT", (const unsigned char*)"Data Watchpoint and Trace\r\n", io->stdOut);
  /* DWT Trace Control register */
  PrintRegHex(io, DWT->CTRL, "   CTRL", " (Control)\r\n");

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), (DWT->CTRL&DWT_CTRL_NUMCOMP_Msk)>>DWT_CTRL_NUMCOMP_Pos);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" NUMCOMP\r\n");
  McuShell_SendStatusStr((const unsigned char*)"", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), (DWT->CTRL&DWT_CTRL_PCSAMPLENA_Msk)>>DWT_CTRL_PCSAMPLENA_Pos);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" PCSAMPLENA\r\n");
  McuShell_SendStatusStr((const unsigned char*)"", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), (DWT->CTRL&DWT_CTRL_SYNCTAP_Msk)>>DWT_CTRL_SYNCTAP_Pos);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" SYNCTAP\r\n");
  McuShell_SendStatusStr((const unsigned char*)"", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), (DWT->CTRL&DWT_CTRL_CYCTAP_Msk)>>DWT_CTRL_CYCTAP_Pos);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CYCTAP\r\n");
  McuShell_SendStatusStr((const unsigned char*)"", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), (DWT->CTRL&DWT_CTRL_POSTINIT_Msk)>>DWT_CTRL_POSTINIT_Pos);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" POSTINIT\r\n");
  McuShell_SendStatusStr((const unsigned char*)"", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), (DWT->CTRL&DWT_CTRL_POSTPRESET_Msk)>>DWT_CTRL_POSTPRESET_Pos);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" POSTPRESET\r\n");
  McuShell_SendStatusStr((const unsigned char*)"", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), (DWT->CTRL&DWT_CTRL_CYCCNTENA_Msk)>>DWT_CTRL_CYCCNTENA_Pos);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CYCCNTENA\r\n");
  McuShell_SendStatusStr((const unsigned char*)"", buf, io->stdOut);

  /* ITM registers */
  McuShell_SendStatusStr((const unsigned char*)"  ITM", (const unsigned char*)"Instrumentation Trace Macrocell\r\n", io->stdOut);
  PrintRegHex(io, ITM->TER, "   TER", " (trace enable stimulus ports)\r\n");
  PrintRegHex(io, ITM->TPR, "   TPR", " (trace privilege)\r\n");
  PrintRegHex(io, ITM->TCR, "   TCR", " (trace control)\r\n");
  PrintRegHex(io, ITM->LSR, "   LSR", " (lock status)\r\n");
#if McuLib_CONFIG_CORTEX_M==33
  PrintRegHex(io, ITM->DEVARCH, "   DEVARCH", " (device architecture, M33 only)\r\n");
#endif
  PrintRegHex(io, ITM->PID0, "   PID0", " (peripheral identification 0)\r\n");
  PrintRegHex(io, ITM->PID1, "   PID1", " (peripheral identification 1)\r\n");
  PrintRegHex(io, ITM->PID2, "   PID2", " (peripheral identification 2)\r\n");
  PrintRegHex(io, ITM->PID3, "   PID3", " (peripheral identification 3)\r\n");
  PrintRegHex(io, ITM->PID4, "   PID4", " (peripheral identification 4)\r\n");
  PrintRegHex(io, ITM->PID5, "   PID5", " (peripheral identification 5)\r\n");
  PrintRegHex(io, ITM->PID6, "   PID6", " (peripheral identification 6)\r\n");
  PrintRegHex(io, ITM->PID7, "   PID8", " (peripheral identification 7)\r\n");
  PrintRegHex(io, ITM->CID0, "   CID0", " (component identification 0)\r\n");
  PrintRegHex(io, ITM->CID1, "   CID1", " (component identification 1)\r\n");
  PrintRegHex(io, ITM->CID2, "   CID2", " (component identification 2)\r\n");
  PrintRegHex(io, ITM->CID3, "   CID3", " (component identification 3)\r\n");

  /* TPI: Trace Port Interface */
  McuShell_SendStatusStr((const unsigned char*)"  TPI", (const unsigned char*)"Trace Port Interface\r\n", io->stdOut);
  PrintRegHex(io, TPI->SSPSR, "   SSPSR", " (Supported Parallel Port Size)\r\n");
  PrintRegHex(io, TPI->CSPSR, "   CSPSR", " (Current Parallel Port Size)\r\n");
  PrintRegHex(io, TPI->ACPR,  "   ACPR",  " (Asynchronous Clock Prescaler)\r\n");
  PrintRegHex(io, TPI->SPPR,  "   SPPR",  " (Selected Pin Protocol)\r\n");
  PrintRegHex(io, TPI->FFSR,  "   FFSR",  " (Formatter and Flush Status)\r\n");
  PrintRegHex(io, TPI->FFCR,  "   FFSR",  " (Formatter and Flush Control)\r\n");
#if McuLib_CONFIG_CORTEX_M==33
  PrintRegHex(io, TPI->PSCR,  "   PSCR",  " (Periodic Synchronization Control)\r\n");
#endif
  PrintRegHex(io, TPI->TRIGGER,  "   TRIGGER",  " (Trigger)\r\n");
#if McuLib_CONFIG_CORTEX_M==33
  PrintRegHex(io, TPI->ITFTTD0,  "   ITFTTD0",  " (Integration Test FIFO Test Data 0)\r\n");
#endif
  PrintRegHex(io, TPI->ITATBCTR2,  "   ITATBCTR2",  " (Integration Test ATB Control 2)\r\n");
  PrintRegHex(io, TPI->ITATBCTR0,  "   ITATBCTR0",  " (Integration Test ATB Control 0)\r\n");
#if McuLib_CONFIG_CORTEX_M==33
  PrintRegHex(io, TPI->ITFTTD1,  "   ITFTTD1",  " (Integration Test FIFO Test Data 1)\r\n");
#endif
  PrintRegHex(io, TPI->ITCTRL,  "   ITCTRL",  " (Integration Mode Control)\r\n");
  PrintRegHex(io, TPI->CLAIMSET,  "   CLAIMSET",  " (Claim tag set)\r\n");
  PrintRegHex(io, TPI->CLAIMCLR,  "   CLAIMCLR",  " (Claim tag clear)\r\n");
  PrintRegHex(io, TPI->DEVID,  "   DEVID",  " (Device Configuration)\r\n");
  PrintRegHex(io, TPI->DEVTYPE,  "   DEVTYPE",  " (Device Type Identifier)\r\n");
  return ERR_OK;
}

static uint8_t PrintHelp(McuShell_ConstStdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"McuSWO", (const unsigned char*)"Group of McuSWO commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  baud <baud> [clockHz]", (const unsigned char*)"Set baud based on optional clock speed\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  send <str>", (const unsigned char*)"Send string\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t McuSWO_ParseCommand(const uint8_t *cmd, bool *handled, McuShell_ConstStdIOType *io) {
  const unsigned char *p;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "McuSWO help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "McuSWO status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "McuSWO baud ", sizeof("McuSWO baud ")-1)==0) {
    int32_t val = 0;
    uint32_t clock = 0, baud = 0;

    *handled = TRUE;
    p = cmd + sizeof("McuSWO baud ")-1;
    if (McuUtility_xatoi(&p, &val)!=ERR_OK || val<0) {
      return ERR_FAILED;
    }
    baud = val;
    if (*p!='\0') { /* clock? */
      if (McuUtility_xatoi(&p, &val)!=ERR_OK || val<0) {
        return ERR_FAILED;
      }
      clock = val;
    } else { /* take default */
      clock = SWO_traceClock;
    }
    SetSWOSpeed(clock, baud);
  } else if (McuUtility_strncmp((char*)cmd, "McuSWO send ", sizeof("McuSWO send ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("McuSWO send ")-1;
    PrintString(p, McuSWO_CONFIG_TERMINAL_CHANNEL);
    PrintString((unsigned char*)"\r\n", McuSWO_CONFIG_TERMINAL_CHANNEL);
  }
  return ERR_OK; /* no error */
}
#endif /* McuSWO_CONFIG_SHELL_ENABLED */

/*!
 * \brief Initialize the SWO trace port for debug message printing
 * \param portBits Port bit mask to be configured
 * \param cpuCoreFreqHz CPU core clock frequency in Hz
 */
static void Init(uint32_t traceClockHz, uint32_t SWOSpeed, uint32_t port) {
#if McuSWO_CONFIG_DO_MUXING
  /* Enables the clock for the I/O controller: Enable Clock. */
  MuxSWOPin();
#endif
#if McuSWO_CONFIG_DO_CLOCKING
  #if McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CPU_IS_LPC55xx
    /*!< Set up dividers */
    CLOCK_SetClkDiv(kCLOCK_DivAhbClk, 1U, false);         /*!< Set AHBCLKDIV divider to value 1 */
    CLOCK_SetClkDiv(kCLOCK_DivArmTrClkDiv, 0U, true);     /*!< Reset TRACECLKDIV divider counter and halt it */
    CLOCK_SetClkDiv(kCLOCK_DivArmTrClkDiv, 1U, false);    /*!< Set TRACECLKDIV divider to value 1 */

    /*!< Switch TRACE to TRACE_DIV */
    CLOCK_AttachClk(kTRACE_DIV_to_TRACE);
  #endif
#endif
#if McuSWO_CONFIG_DO_SWO_INIT
#if 1 /* new initialization */
  CoreDebug->DEMCR = CoreDebug_DEMCR_TRCENA_Msk;
  if ((CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk) == 0U) {
    assert(false);
  }
  ITM->LAR = 0xC5ACCE55U; /* ITM Lock Access Register, C5ACCE55 enables more write access to Control Register 0xE00 :: 0xFFC */
  ITM->TER &= ~(1UL << port); /* ITM Trace Enable Register. Enabled tracing on stimulus ports. One bit per stimulus port. Disable it */
  ITM->TCR = 0U; /* ITM Trace Control Register */
  TPI->SPPR = 0x2; /* "Selected PIN Protocol Register": Select which protocol to use for trace output (2: SWO NRZ (UART), 1: SWO Manchester encoding) */
  SetSWOSpeed(traceClockHz, SWOSpeed); /* set baud rate with prescaler */
  ITM->TPR = 0U; /* allow unprivileged access */
  ITM->TCR = ITM_TCR_ITMENA_Msk | ITM_TCR_SYNCENA_Msk /* enable ITM */
  #ifdef ITM_TCR_TraceBusID_Msk
             | ITM_TCR_TraceBusID_Msk
  #elif defined(ITM_TCR_TRACEBUSID_Msk)
             | ITM_TCR_TRACEBUSID_Msk
  #endif
             | ITM_TCR_SWOENA_Msk | ITM_TCR_DWTENA_Msk;
  ITM->TER = 1UL << port; /* enable the port bits */
#else /* old */
    CoreDebug->DEMCR = CoreDebug_DEMCR_TRCENA_Msk; /* enable trace in core debug */
    TPI->SPPR = 0x2; /* "Selected PIN Protocol Register": Select which protocol to use for trace output (2: SWO NRZ (UART), 1: SWO Manchester encoding) */
    SetSWOSpeed(traceClockHz, SWOSpeed); /* set baud rate */
    ITM->LAR = 0xC5ACCE55; /* ITM Lock Access Register, C5ACCE55 enables more write access to Control Register 0xE00 :: 0xFFC */
    /* enable trace with the TCR: this includes DWT and ITM packets to be sent */
    ITM->TCR = ITM_TCR_DWTENA_Msk | ITM_TCR_ITMENA_Msk | ITM_TCR_TRACEBUSID_Msk | ITM_TCR_SWOENA_Msk | ITM_TCR_SYNCENA_Msk; /* ITM Trace Control Register */
    ITM->TPR = ITM_TPR_PRIVMASK_Msk; /* ITM Trace Privilege Register */
    ITM->TER = portBits; /* ITM Trace Enable Register. Enabled tracing on stimulus ports. One bit per stimulus port. */
    DWT->CTRL = /* see https://interrupt.memfault.com/blog/profiling-firmware-on-cortex-m#enabling-pc-sampling-with-itm-and-openocd */
            (  4<<DWT_CTRL_NUMCOMP_Pos)    /* 4 bits */
  #if McuSWO_CONFIG_PC_SAMPLING
          | (  1<<DWT_CTRL_PCSAMPLENA_Pos) /* 1 bit: enable PC sampling */
  #endif
          | (  0<<DWT_CTRL_SYNCTAP_Pos)    /* 2 bits */
          | (  1<<DWT_CTRL_CYCTAP_Pos)     /* 1 bits: This selects which bit in the cycle counter is used to trigger PC sampling events. A 1 selects bit 10 to tap, a 0 selects bit 6 to tap. */
          | (0xF<<DWT_CTRL_POSTINIT_Pos)   /* 4 bits */
          | (0xF<<DWT_CTRL_POSTPRESET_Pos) /* 4 bits: These bits control how many times the time bit must toggle before a PC sample event is generated. */
  #if McuWait_CONFIG_USE_CYCLE_COUNTER || McuSWO_CONFIG_PC_SAMPLING
          | (  1<<DWT_CTRL_CYCCNTENA_Pos)  /* 1 bit: enable CYCCNT which is required for PC sampling */
  #endif
      ;
    TPI->FFCR = (1<<TPI_FFCR_TrigIn_Pos); /* Formatter and Flush Control Register */
#endif
#endif /* McuSWO_CONFIG_DO_SWO_INIT */
}

void McuSWO_ChangeSpeed(uint32_t baud) {
  SystemCoreClockUpdate();
  SWO_traceClock = SystemCoreClock; /* store new speed */
  assert(baud<=SWO_traceClock);
  SetSWOSpeed(SWO_traceClock, baud);
}

void McuSWO_Init(void) {
  SystemCoreClockUpdate();
  SWO_traceClock = SystemCoreClock; /* just the default! */
  Init(SWO_traceClock, McuSWO_CONFIG_SPEED_BAUD, McuSWO_CONFIG_TERMINAL_CHANNEL);
}
#endif /* McuSWO_CONFIG_HAS_SWO */

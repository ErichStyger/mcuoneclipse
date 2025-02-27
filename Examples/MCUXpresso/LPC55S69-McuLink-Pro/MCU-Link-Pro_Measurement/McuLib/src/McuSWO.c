/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuSWO.h"
#if McuSWO_CONFIG_HAS_SWO
#include "McuUtility.h"
#include "McuShell.h"
#include "board.h"
#include "pin_mux.h"

static uint32_t SWO_traceClock; /* clock feed into the ARM CoreSight */

/*!
 * \brief Sends a character over the SWO channel
 * \param c Character to be sent
 * \param portNo SWO channel number, value in the range of 0 to 31
 */
void SWO_PrintChar(char c, uint8_t portNo) {
  volatile int timeout;

  /* Check if Trace Control Register (ITM->TCR at 0xE0000E80) is set */
  if ((ITM->TCR&ITM_TCR_ITMENA_Msk) == 0) { /* check Trace Control Register if ITM trace is enabled*/
    return; /* not enabled? */
  }
  /* Check if the requested channel stimulus port (ITM->TER at 0xE0000E00) is enabled */
  if ((ITM->TER & (1ul<<portNo))==0) { /* check Trace Enable Register if requested port is enabled */
    return; /* requested port not enabled? */
  }
  timeout = 5000; /* arbitrary timeout value */
  while (ITM->PORT[0].u32 == 0) {
    /* Wait until STIMx is ready, then send data */
    timeout--;
    if (timeout==0) {
      return; /* not able to send */
    }
  }
  ITM->PORT[0].u8 = c;
}

/*!
 * \brief Sends a string over SWO to the host
 * \param s String to send
 * \param portNumber Port number, 0-31, use 0 for normal debug strings
 */
void PrintString(const unsigned char *s, uint8_t portNumber) {
  while (*s!='\0') {
    //SWO_PrintChar(*s++, portNumber);
    ITM_SendChar(*s++);
  }
}

void McuSWO_SendStr(const unsigned char *str) {
  PrintString(str, McuSWO_CONFIG_TERMINAL_CHANNEL);
}

volatile int32_t ITM_RxBuffer; /* implementation of buffer for Rx */

bool McuSWO_StdIOKeyPressed(void) {
  if (ITM_RxBuffer != ITM_RXBUFFER_EMPTY) {
    return true;
  }
  return false;
}

void McuSWO_StdIOReadChar(uint8_t *c) {
  int res;

  res = ITM_ReceiveChar();
  if (res==-1) { /* no character present */
    *c = '\0';
  } else {
    *c = (uint8_t)res; /* return character */
  }
}

void McuSWO_StdIOSendChar(uint8_t ch) {
  ITM_SendChar(ch);
}

/* default standard I/O struct */
McuShell_ConstStdIOType McuSWO_stdio = {
    (McuShell_StdIO_In_FctType)McuSWO_StdIOReadChar, /* stdin */
    (McuShell_StdIO_OutErr_FctType)McuSWO_StdIOSendChar, /* stdout */
    (McuShell_StdIO_OutErr_FctType)McuSWO_StdIOSendChar, /* stderr */
    McuSWO_StdIOKeyPressed /* if input is not empty */
  };
uint8_t McuSWO_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */


static void MuxSWOPin(void) {
#if McuLib_CONFIG_CPU_IS_LPC
  CLOCK_EnableClock(kCLOCK_Iocon);
  #if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16
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
                       | IOCON_PIO_DIGIMODE(PIO0_10_DIGIMODE_DIGITAL));
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
#else
  #error "NYI"
#endif
}

static void SetSWOSpeed(uint32_t traceClockHz, uint32_t SWOSpeed) {
  uint32_t SWOPrescaler = (traceClockHz / SWOSpeed) - 1; /* SWOSpeed in Hz, note that traceClockHz is expected to be match the CPU core clock */

  TPI->ACPR = SWOPrescaler; /* "Async Clock Prescaler Register". Scale the baud rate of the asynchronous output */
}

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
  PrintRegHex(io, ITM->DEVARCH, "   DEVARCH", " (device architecture, M33 only)\r\n");
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
  PrintRegHex(io, TPI->PSCR,  "   PSCR",  " (Periodic Synchronization Control)\r\n");
  PrintRegHex(io, TPI->TRIGGER,  "   TRIGGER",  " (Trigger)\r\n");
  PrintRegHex(io, TPI->ITFTTD0,  "   ITFTTD0",  " (Integration Test FIFO Test Data 0)\r\n");
  PrintRegHex(io, TPI->ITATBCTR2,  "   ITATBCTR2",  " (Integration Test ATB Control 2)\r\n");
  PrintRegHex(io, TPI->ITATBCTR0,  "   ITATBCTR0",  " (Integration Test ATB Control 0)\r\n");
  PrintRegHex(io, TPI->ITFTTD1,  "   ITFTTD1",  " (Integration Test FIFO Test Data 1)\r\n");
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

/*!
 * \brief Initialize the SWO trace port for debug message printing
 * \param portBits Port bit mask to be configured
 * \param cpuCoreFreqHz CPU core clock frequency in Hz
 */
static void Init(uint32_t portBits, uint32_t traceClockHz, uint32_t SWOSpeed) {
  /* Enables the clock for the I/O controller: Enable Clock. */
  MuxSWOPin();

  /*!< Set up dividers */
  CLOCK_SetClkDiv(kCLOCK_DivAhbClk, 1U, false);         /*!< Set AHBCLKDIV divider to value 1 */
  CLOCK_SetClkDiv(kCLOCK_DivArmTrClkDiv, 0U, true);     /*!< Reset TRACECLKDIV divider counter and halt it */
  CLOCK_SetClkDiv(kCLOCK_DivArmTrClkDiv, 1U, false);    /*!< Set TRACECLKDIV divider to value 1 */

  /*!< Switch TRACE to TRACE_DIV */
  CLOCK_AttachClk(kTRACE_DIV_to_TRACE);

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
}

void McuSWO_ChangeSpeed(uint32_t baud) {
  SetSWOSpeed(SWO_traceClock, baud);
}

void McuSWO_Init(uint32_t traceClock, uint32_t baud) {
  SWO_traceClock = traceClock; /* just the default! */
  Init(1, SWO_traceClock, baud);
}
#endif /* McuSWO_CONFIG_HAS_SWO */

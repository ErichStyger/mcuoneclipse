/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuSWO.h"
#include "board.h"
#include "pin_mux.h"

#define SWO_CONFIG_SPEED   (64000)

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
void PrintString(const char *s, uint8_t portNumber) {
  while (*s!='\0') {
    //SWO_PrintChar(*s++, portNumber);
    ITM_SendChar(*s++);
  }
}

void SWO_SendStr(const char *str) {
  PrintString(str, 0);
}

static void MuxSWOPin(void) {
  IOCON->PIO[0][10] = ((IOCON->PIO[0][10] &
                        /* Mask bits to zero which are setting */
                        (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                       /* Selects pin function.
                        * : PORT010 (pin 21) is configured as SWO. */
                       | IOCON_PIO_FUNC(PIO0_10_FUNC_ALT6)

                       /* Select Digital mode.
                        * : Enable Digital mode.
                        * Digital input is enabled. */
                       | IOCON_PIO_DIGIMODE(PIO0_10_DIGIMODE_DIGITAL));
}

static void SetSWOSpeed(uint32_t traceClockHz, uint32_t SWOSpeed) {
  uint32_t SWOPrescaler = (traceClockHz / SWOSpeed) - 1; /* SWOSpeed in Hz, note that traceClockHz is expected to be match the CPU core clock */

  *((volatile unsigned *)(ITM_BASE + 0x40010)) = SWOPrescaler; /* "Async Clock Prescaler Register". Scale the baud rate of the asynchronous output */
}

/*!
 * \brief Initialize the SWO trace port for debug message printing
 * \param portBits Port bit mask to be configured
 * \param cpuCoreFreqHz CPU core clock frequency in Hz
 */
static void Init(uint32_t portBits, uint32_t traceClockHz, uint32_t SWOSpeed) {

  /* Enables the clock for the I/O controller.: Enable Clock. */
  CLOCK_EnableClock(kCLOCK_Iocon);
  MuxSWOPin();

  /*!< Set up dividers */
  CLOCK_SetClkDiv(kCLOCK_DivAhbClk, 1U, false);         /*!< Set AHBCLKDIV divider to value 1 */
  CLOCK_SetClkDiv(kCLOCK_DivArmTrClkDiv, 0U, true);               /*!< Reset TRACECLKDIV divider counter and halt it */
  CLOCK_SetClkDiv(kCLOCK_DivArmTrClkDiv, 1U, false);         /*!< Set TRACECLKDIV divider to value 1 */

  /*!< Switch TRACE to TRACE_DIV */
  CLOCK_AttachClk(kTRACE_DIV_to_TRACE);

  CoreDebug->DEMCR = CoreDebug_DEMCR_TRCENA_Msk; /* enable trace in core debug */
  *((volatile unsigned *)(ITM_BASE + 0x400F0)) = 0x00000002; /* "Selected PIN Protocol Register": Select which protocol to use for trace output (2: SWO NRZ, 1: SWO Manchester encoding) */
  SetSWOSpeed(traceClockHz, SWOSpeed);
  *((volatile unsigned *)(ITM_BASE + 0x00FB0)) = 0xC5ACCE55; /* ITM Lock Access Register, C5ACCE55 enables more write access to Control Register 0xE00 :: 0xFFC */
  ITM->TCR = ITM_TCR_TRACEBUSID_Msk | ITM_TCR_SWOENA_Msk | ITM_TCR_SYNCENA_Msk | ITM_TCR_ITMENA_Msk; /* ITM Trace Control Register */
  ITM->TPR = ITM_TPR_PRIVMASK_Msk; /* ITM Trace Privilege Register */
  ITM->TER = portBits; /* ITM Trace Enable Register. Enabled tracing on stimulus ports. One bit per stimulus port. */
  *((volatile unsigned *)(ITM_BASE + 0x01000)) =  /* DWT_CTRL */ /* see https://interrupt.memfault.com/blog/profiling-firmware-on-cortex-m#enabling-pc-sampling-with-itm-and-openocd */
          (  4<<DWT_CTRL_NUMCOMP_Pos)    /* 4 bits */
        | (  0<<DWT_CTRL_PCSAMPLENA_Pos) /* 1 bit: enable PC sampling */
        | (  0<<DWT_CTRL_SYNCTAP_Pos)    /* 2 bits */
        | (  1<<DWT_CTRL_CYCTAP_Pos)     /* 1 bits: This selects which bit in the cycle counter is used to trigger PC sampling events. A 1 selects bit 10 to tap, a 0 selects bit 6 to tap. */
        | (0xF<<DWT_CTRL_POSTINIT_Pos)   /* 4 bits */
        | (0xF<<DWT_CTRL_POSTPRESET_Pos) /* 4 bits: These bits control how many times the time bit must toggle before a PC sample event is generated. */
        | (  0<<DWT_CTRL_CYCCNTENA_Pos)  /* 1 bit: enable CYCCNT which is required for PC sampling */
    ;
  *((volatile unsigned *)(ITM_BASE + 0x40304)) = 0x00000100; /* Formatter and Flush Control Register */
}

void SWO_SetSpeed(void) {
  SetSWOSpeed(SystemCoreClock, SWO_CONFIG_SPEED);
}

void SWO_Init(void) {
  Init(1, SystemCoreClock, SWO_CONFIG_SPEED);
}

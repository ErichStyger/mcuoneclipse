/*
 * KinetisTrace.c
 *
 *  Created on: 09.10.2016
 *      Author: Erich Styger
 */

#include "KinetisTrace.h"
#include "Cpu.h"

static void msg(char *msg) {
  (void)msg; /* dummy: put your own output routine here */
}

/* Kinetis has two trace sources (ITM, ETM) and 3 output options (ETM, ETB and SWO)
 * The following is possible:
 * no trace
 * ETM to TPIU (with ITM)
 * ETM to ETB, ITM to SWO
 * ETM to TPIU, ITM to ETB
 * Note: Using ETM and ETB  with SWO cannot co-exist, as using the same data channel.
 */
#define KINETIS_TRACE_ETM_ENABLE   (1<<0)
#define KINETIS_TRACE_ITM_ENABLE   (1<<1)
#define KINETIS_TRACE_ITM_ETM_MASK (KINETIS_TRACE_ITM_ENABLE|KINETIS_TRACE_ETM_ENABLE)

static void KinetisTrace_EnableTrace(uint32_t mask) {
  uint32_t value;

  /* setup of ETF (Embedded Trace FIFO) funnel */
  value = ETF_FCR; /* read ETF (Embedded Trace FIFO) Funnel Control Register at 0xE0043000 */
  if ((value&KINETIS_TRACE_ITM_ETM_MASK)!=mask) { /* Check if we need to change it */
    value &= ~KINETIS_TRACE_ITM_ETM_MASK; /* clear bits */
    value |= mask; /* enable bits */
    ETF_FCR = value; /* write ETF Funnel Control Register at 0xE0043000 */
  }
  /* MCM: Core Platform Miscellaneous Control Module:
   * bit 4 (ETDIS): ETM-To-TPIU Disable, 0: path enabled, 1: path disabled
   * bit 5 (ITDIS): ITM-To-TPIU Disable, 0: path enabled, 1: path disabled
   **/
  value = MCM_ETBCC; /* get ETBCC bits (address 0xE0080014) */
  value &= ~(KINETIS_TRACE_ITM_ETM_MASK<<4); /* clear bits */
  value |= ((~mask)&KINETIS_TRACE_ITM_ETM_MASK)<<4; /* build with invert bits: 0 enables the path */
  MCM_ETBCC = value; /* store back value to ETBCC (at 0xE0080014) */
  /* debug output only: show what we are tracing */
  value = (value>>4)&KINETIS_TRACE_ITM_ETM_MASK;
  if (value==0x0) { /* both bits cleared */
    msg("Kinetis: ITM and ETM routed to TPIU");
  } else if (value==0x1) { /* only ITM bit cleared */
    msg("Kinetis: ITM routed to TPIU");
  } else if (value == 0x2) { /* only ETM bit cleared */
    msg("Kinetis: ETM routed to TPIU");
  } else { /* 0x3, both bits set, both paths disabled */
    msg("Kinetis: routing to TPIU disabled");
  }
}

static void KinetisTrace_ConfigureGPIO(void) {
  uint32_t value;
  /* On the TWR-K64F, the following pins are are available on the JTAG/Trace connector:
   * PTE0: TRACE_CLKOUT
   * PTE4: TRACE_D0
   * PTE3: TRACE_D1
   * PTE2: TRACE_D2
   * PTE1: TRACE_D3
   */
  #define PORT_PCR_DSE_ENABLE       (1<<6)  /* Port Configuration Register, Drive Strength Enable (DSE) bit */
  #define PORT_PCR_MUX_ALTERNATE_5  (5<<8) /* Port Configuration Register, Alternate 5 function (mux as trace pin) */
  #define PORT_PCR_CONFIG_FOR_TRACE (PORT_PCR_DSE_ENABLE|PORT_PCR_DSE_ENABLE|PORT_PCR_MUX_ALTERNATE_5) /* for trace, mux it with function 5 and high drive strength */

  /* check and enable clocking of PORTE */
  value = SIM_SCGC5; /* read SIM_SCGC5 at 0x40048038 */
  if ((value & (1<<13)) == 0) { /* Bit13 in SCGC5 is the PortE clock gate control bit. Clock not already enabled? */
    SIM_SCGC5 |= (1<<13);    /* Enabling clock gate for Port E */
  }
  value = SIM_SOPT2; /* SIM_SOPT2 at 0x40048004 */
  if ((value&(1<<12))==0) { /* Bit 12 enables the trace clock. Is the debug trace clock not already enabled? */
    SIM_SOPT2 |= (1<<12); /* Debug trace clock select = Core/system clock */
  }
  /* Trace data (PTE1-4) and clock pin (PTE0), high drive strength */
  PORTE_PCR0 = PORT_PCR_CONFIG_FOR_TRACE; /* PTE0, PORTE_PCR0 at 0x4004D000, trace clock pin, high drive strength */
  PORTE_PCR1 = PORT_PCR_CONFIG_FOR_TRACE; /* PTE1, PORTE_PCR1 at 0x4004D004, trace data pin, high drive strength */
  PORTE_PCR2 = PORT_PCR_CONFIG_FOR_TRACE; /* PTE2, PORTE_PCR3 at 0x4004D008, trace data pin, high drive strength */
  PORTE_PCR3 = PORT_PCR_CONFIG_FOR_TRACE; /* PTE3, PORTE_PCR3 at 0x4004D00C, trace data pin, high drive strength */
  PORTE_PCR4 = PORT_PCR_CONFIG_FOR_TRACE; /* PTE4, PORTE_PCR4 at 0x4004D010, trace data pin, high drive strength */
}

void KinetisTrace_Init(void) {
  KinetisTrace_ConfigureGPIO();
  KinetisTrace_EnableTrace(KINETIS_TRACE_ETM_ENABLE|KINETIS_TRACE_ITM_ENABLE);
}

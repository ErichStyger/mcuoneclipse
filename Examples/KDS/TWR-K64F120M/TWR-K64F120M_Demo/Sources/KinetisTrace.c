/*
 * KinetisTrace.c
 *
 *  Created on: 09.10.2016
 *      Author: Erich Styger
 */

#include "KinetisTrace.h"
#include "Cpu.h"

/* Low level memory read function */
static uint32_t ReadMemory32(uint32_t addr) {
  return *((uint32_t*)addr);
}

/* low level memory write function */
static void WriteMemory32(uint32_t addr, uint32_t val) {
  *((uint32_t*)addr) = val;
}

static void __message(char *msg) {
  (void)msg; /* dummy: put your own output routine here */
}

static uint32_t GetTracePortSize(void) {
  /* number of trace data port pins */
  return 4; /* use either 2 or 4 pins */
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

static void KinetisTrace_EnableETB(uint32_t mask) {
  uint32_t value, bits;

  /* setup of ETF (Embedded Trace FIFO) funnel */
#if 0
  mask &= KINETIS_TRACE_ITM_ETM_MASK; /* make sure only valid bits are set */
  ETF_FCR = (ETF_FCR&(~KINETIS_TRACE_ITM_ETM_MASK))|mask;
#else
  bits = KINETIS_TRACE_ITM_ETM_MASK;
  value = ETF_FCR; /* read ETF (Embedded Trace FIFO) Funnel Control Register at 0xE0043000 */
  if ((value&bits)!=mask) { /* Check if we need to change it */
    value &= ~bits;
    value |= mask;
    ETF_FCR = value; /* write ETF Funnel Control Register at 0xE0043000 */
  }
#endif
  /* MCM: Core Platform Miscellaneous Control Module:
   * bit 4 (ETDIS): ETM-To-TPIU Disable, 0: path enabled, 1: path disabled
   * bit 5 (ITDIS): ITM-To-TPIU Disable, 0: path enabled, 1: path disabled
   **/
#if 1
  value = MCM_ETBCC;
  value &= ~(KINETIS_TRACE_ITM_ETM_MASK<<4); /* clear bits */
  value |= ((~mask)&KINETIS_TRACE_ITM_ETM_MASK)<<4; /* build with invert bits: 0 enables the path */
  MCM_ETBCC = value;
#else
  value = MCM_ETBCC; /* read MCM_ETBCC (ETB Counter Control register) at 0xE0080014 */
  if ((value&(bits<<4)) != (mask<<4)) { /* Check if we need to change it */
    value &= ~(bits<<4);
    value |= (mask<<4);
    MCM_ETBCC = value; /* write MCM_ETBCC (ETB Counter Control register) at 0xE0080014 */
  }
#endif
  value = (value>>4)&0x03;
  if (value==0x0) {
    __message("Kinetis: ITM and ETM routed to TPIU.");
  } else if (value==0x1) {
    __message("Kinetis: ITM routed to TPIU");
  } else if (value == 0x2) {
    __message("Kinetis: ETM routed to TPIU");
  } else { /* 0x3 */
    __message("Kinetis: routing to TPIU disabled");
  }
}

static void KinetisTrace_EnableGPIOForETM(void) {
  uint32_t value;

  // ReadRegister( SIM_SCGC5, &value);
  value = SIM_SCGC5; /* SIM_SCGC5 at 0x40048038 */
  //value = ReadMemory32(0x40048038);
  if ((value & (1<<13)) == 0) { /* clock not already enabled? */
    value |= (1<<13);    // Enabling internal clock to Port E
    SIM_SCGC5 = value;
    //WriteMemory32(0x40048038, value); // WriteRegister(SIM_SCGC5, value);
  }
  value = SIM_SOPT2; /* SIM_SOPT2 at 0x40048004 */
  //value = ReadMemory32(0x40048004);  // ReadRegister( SIM_SOPT2, &value);
  if ((value&(1<<12))==0) { /* debug trace clock not already enabled? */
    value |= (1<<12);       // Debug trace clock select = Core/system clock
    SIM_SOPT2 = value; /* SIM_SOPT2 at 0x40048004 */
    //WriteMemory32(0x40048004, value);  // WriteRegister(SIM_SOPT2, value);
  }
  /* ---- Enabling Trace Pin Function ---- */
  /* Trace data and clock pins, high drive strength */
  /* TRACE CLK and TRACE D0*/;
  WriteMemory32(0x4004D000, 0x00000540);  // WriteRegister(PORTE_PCR0,  0x00000540);  /* trace Clock, low drive strength */
  WriteMemory32(0x4004D010, 0x00000540);  // WriteRegister(PORTE_PCR4, 0x00000540);
  if (GetTracePortSize()>=2) { /* Enable TRACE D1 */;
    WriteMemory32(0x4004D00C, 0x00000540);  // WriteRegister(PORTE_PCR3,  0x00000540);
  }
  if (GetTracePortSize()==4) {  /* Enable TRACE D2, D3*/
    WriteMemory32(0x4004D008, 0x00000540);  // WriteRegister(PORTE_PCR2,  0x00000540);
    WriteMemory32(0x4004D004, 0x00000540);  // WriteRegister(PORTE_PCR1,  0x00000540); /* trace data, high drive strength */
  }
}

void KinetisTrace_Init(void) {
  KinetisTrace_EnableGPIOForETM();
//  KinetisTrace_EnableETB(6);
  KinetisTrace_EnableETB(KINETIS_TRACE_ETM_ENABLE);
//  KinetisTrace_EnableETB(3); fail
//  KinetisTrace_EnableETB(2);
}

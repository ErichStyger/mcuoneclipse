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

static void KinetisTrace_EnableETB(uint32_t mask) {
  uint32_t value, changed, bits;

  bits = 0x3;
  changed = 0;
  value = ReadMemory32(0xE0043000); /* Funnel */
  if ((value & bits) != mask) {    /* Check if we need to change it */
    value &= ~bits;
    value |= mask;
    WriteMemory32(0xE0043000, value);
    changed |= bits;
  }
  value = ReadMemory32(0xE0080014); /* MCM_ETBCC */
   if ((value & (bits << 4)) != (mask << 4)) { /* Check if we need to change it */
     value &= ~(bits << 4);
     value |= (mask << 4);
     WriteMemory32(0xE0080014, value);
     changed |= bits;
   }
   value = value >> 4;

   value &= 0x3;
   if (value == 0x3) {
     __message("Kinetis: ETB enabled (both ITM and ETM go to ETB)");
   } else
   if (value == 0x1) {
     __message("Kinetis: ETB enabled (only ETM goes to ETB)");
   } else
   if (value == 0x2) {
     __message("Kinetis: ETB enabled (only ITM goes to ETB)");
   } else {
     __message("Kinetis: ETB not enabled");
   }
}

static void KinetisTrace_EnableGPIOForETM(void) {
  uint32_t value;

  // ReadRegister( SIM_SCGC5, &value);
  value = ReadMemory32(0x40048038);
  if ((value & (1<<13)) == 0) { /* clock not already enabled? */
    value |= (1<<13);    // Enabling internal clock to Port E
    WriteMemory32(0x40048038, value); // WriteRegister(SIM_SCGC5, value);
  }
  value = ReadMemory32(0x40048004);  // ReadRegister( SIM_SOPT2, &value);
  if ((value & (1<<12)) == 0) { /* debug trace clock not already enabled? */
    value |= (1<<12);       // Debug trace clock select = Core/system clock
    WriteMemory32(0x40048004, value);  // WriteRegister(SIM_SOPT2, value);
  }
  /* ---- Enabling Trace Pin Function ---- */
  /* Trace data and clock pins, high drive strength */
  /* TRACE CLK and TRACE D0*/;
  WriteMemory32(0x4004D000, 0x00000540);  // WriteRegister(PORTE_PCR0,  0x00000700);
  WriteMemory32(0x4004D010, 0x00000540);  // WriteRegister(PORTE_PCR4, 0x00000740);
  if (GetTracePortSize()>=2) { /* Enable TRACE D1 */;
    WriteMemory32(0x4004D00C, 0x00000540);  // WriteRegister(PORTE_PCR3,  0x00000740);
  }
  if (GetTracePortSize()==4) {
    /* Enable TRACE D2, D3*/;
    WriteMemory32(0x4004D008, 0x00000540);  // WriteRegister(PORTE_PCR2,  0x00000540);
    WriteMemory32(0x4004D004, 0x00000540);  // WriteRegister(PORTE_PCR1,  0x00000540);
  }
}

void KinetisTrace_Init(void) {
  KinetisTrace_EnableGPIOForETM();
  KinetisTrace_EnableETB(6);
}

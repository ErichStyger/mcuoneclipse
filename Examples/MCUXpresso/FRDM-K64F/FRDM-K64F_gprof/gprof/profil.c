/* profil.c -- win32 profil.c equivalent

   Copyright 1998, 1999, 2000, 2001, 2002 Red Hat, Inc.

   This file is part of Cygwin.

   This software is a copyrighted work licensed under the terms of the
   Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
   details. */

/*
 * This file is taken from Cygwin distribution, adopted to be used for bare embeeded targets.
 */
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <math.h>
#include "profil.h"
#include <string.h>
#include <stdint.h>
#include "fsl_pit.h"


/* global profinfo for profil() call */
static struct profinfo prof = {
  PROFILE_NOT_INIT, 0, 0, 0, 0
};

#define PIT_BASEADDR 		PIT
#define PIT_CHANNEL  		kPIT_Chnl_0
#define PIT_HANDLER   		PIT0_IRQHandler
#define PIT_IRQ_ID      	PIT0_IRQn
#define PIT_SOURCE_CLOCK 	CLOCK_GetFreq(kCLOCK_BusClk)

/* sample the current program counter */
void PIT0_IRQHandler(void) {
  static size_t pc, idx;

  PIT_ClearStatusFlags(PIT_BASEADDR, PIT_CHANNEL, kPIT_TimerFlag);
  if (prof.state==PROFILE_ON) {
    pc = ((uint32_t*)(__builtin_frame_address(0)))[14]; /* get SP and use it to get the return address from stack */
    if (pc >= prof.lowpc && pc < prof.highpc) {
      idx = PROFIDX (pc, prof.lowpc, prof.scale);
      prof.counter[idx]++;
    }
  }
  __DSB();
}

void gprof_init_timer(void) {
    pit_config_t pitConfig;
    /*
     * pitConfig.enableRunInDebug = false;
     */
    PIT_GetDefaultConfig(&pitConfig);

    /* Init pit module */
    PIT_Init(PIT_BASEADDR, &pitConfig);

    /* Set timer period for channel 0 */
    PIT_SetTimerPeriod(PIT_BASEADDR, PIT_CHANNEL, USEC_TO_COUNT(1000U, PIT_SOURCE_CLOCK)); /* must be PROF_HZ */

    /* Enable timer interrupts for channel 0 */
    PIT_EnableInterrupts(PIT_BASEADDR, PIT_CHANNEL, kPIT_TimerInterruptEnable);

    /* Enable at the NVIC */
    EnableIRQ(PIT_IRQ_ID);
    PIT_StartTimer(PIT_BASEADDR, PIT_CHANNEL);
}

/* Stop profiling to the profiling buffer pointed to by p. */
static int profile_off (struct profinfo *p) {
  p->state = PROFILE_OFF;
  return 0;
}

/* Create a timer thread and pass it a pointer P to the profiling buffer. */
static int profile_on (struct profinfo *p) {
  p->state = PROFILE_ON;
  return 0; /* ok */
}

/*
 * start or stop profiling
 *
 * profiling goes into the SAMPLES buffer of size SIZE (which is treated
 * as an array of u_shorts of size size/2)
 *
 * each bin represents a range of pc addresses from OFFSET.  The number
 * of pc addresses in a bin depends on SCALE.  (A scale of 65536 maps
 * each bin to two addresses, A scale of 32768 maps each bin to 4 addresses,
 * a scale of 1 maps each bin to 128k address).  Scale may be 1 - 65536,
 * or zero to turn off profiling
 */
int profile_ctl (struct profinfo *p, char *samples, size_t size, size_t offset, u_int scale) {
  size_t maxbin;

  if (scale > 65536) {
    errno = EINVAL;
    return -1;
  }
  profile_off(p);
  if (scale) {
    memset(samples, 0, size);
    memset(p, 0, sizeof *p);
    maxbin = size >> 1;
    prof.counter = (u_short*)samples;
    prof.lowpc = offset;
    prof.highpc = PROFADDR(maxbin, offset, scale);
    prof.scale = scale;
    return profile_on(p);
  }
  return 0;
}

/* Equivalent to unix profil()
   Every SLEEPTIME interval, the user's program counter (PC) is examined:
   offset is subtracted and the result is multiplied by scale.
   The word pointed to by this address is incremented. */
int profil (char *samples, size_t size, size_t offset, u_int scale) {
  return profile_ctl (&prof, samples, size, offset, scale);
}

int profile_file_write_check(void) {
  FILE *file = NULL;

  file = fopen ("c:\\tmp\\test.txt", "w");
  if (file!=NULL) {
    fputs("hello world with file I/O\r\n", file);
    (void)fwrite("hello\r\n", sizeof("hello\r\n")-1, 1, file);
    fclose(file);
    return 1; /* ok */
  }
  return 0; /* failed */
}

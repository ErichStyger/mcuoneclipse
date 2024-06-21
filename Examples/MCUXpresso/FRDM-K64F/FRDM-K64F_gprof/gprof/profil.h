/* profil.h: gprof profiling header file

   Copyright 1998, 1999, 2000, 2001, 2002 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

/*
 * This file is taken from Cygwin distribution. Please keep it in sync.
 * The differences should be within __MINGW32__ guard.
 */

#ifndef __PROFIL_H__
#define __PROFIL_H__

typedef unsigned short u_short;
typedef unsigned int u_int;

/* profiling frequency.  (No larger than 1000) */
#define PROF_HZ			1000

/* convert an addr to an index */
#define PROFIDX(pc, base, scale)	\
  ({									\
    size_t i = (pc - base) / 2;				\
    if (sizeof (unsigned long long int) > sizeof (size_t))		\
      i = (unsigned long long int) i * scale / 65536;			\
    else								\
      i = i / 65536 * scale + i % 65536 * scale / 65536;		\
    i;									\
  })

/* convert an index into an address */
#define PROFADDR(idx, base, scale)		\
  ((base)					\
   + ((((unsigned long long)(idx) << 16)	\
       / (unsigned long long)(scale)) << 1))

/* convert a bin size into a scale */
#define PROFSCALE(range, bins)		(((bins) << 16) / ((range) >> 1))

typedef void *_WINHANDLE;

typedef enum {
  PROFILE_NOT_INIT = 0,
  PROFILE_ON,
  PROFILE_OFF
} PROFILE_State;

struct profinfo {
  PROFILE_State state; /* profiling state */
  u_short *counter;			/* profiling counters */
  size_t lowpc, highpc;		/* range to be profiled */
  u_int scale;			/* scale value of bins */
};

int profile_ctl(struct profinfo *, char *, size_t, size_t, u_int);
int profil(char *, size_t, size_t, u_int);
void gprof_init_timer(void);
int profile_file_write_check(void);

#endif /* __PROFIL_H__ */

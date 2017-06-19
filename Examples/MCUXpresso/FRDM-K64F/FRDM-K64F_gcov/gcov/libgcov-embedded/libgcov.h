/* Header file for libgcov-*.c.
   Copyright (C) 1996-2015 Free Software Foundation, Inc.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it under
   the terms of the GNU General Public License as published by the Free
   Software Foundation; either version 3, or (at your option) any later
   version.

   GCC is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
   for more details.

   Under Section 7 of GPL version 3, you are granted additional
   permissions described in the GCC Runtime Library Exception, version
   3.1, as published by the Free Software Foundation.

   You should have received a copy of the GNU General Public License and
   a copy of the GCC Runtime Library Exception along with this program;
   see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef GCC_LIBGCOV_H
#define GCC_LIBGCOV_H

/* work around the poisoned malloc/calloc in system.h.  */
#ifndef xmalloc
#define xmalloc malloc
#endif
#ifndef xcalloc
#define xcalloc calloc
#endif

#ifndef IN_GCOV_TOOL

#if BITS_PER_UNIT == 8
typedef unsigned gcov_unsigned_t __attribute__ ((mode (SI)));
typedef unsigned gcov_position_t __attribute__ ((mode (SI)));
#if LONG_LONG_TYPE_SIZE > 32
typedef signed gcov_type __attribute__ ((mode (DI)));
typedef unsigned gcov_type_unsigned __attribute__ ((mode (DI)));
#else
typedef signed gcov_type __attribute__ ((mode (SI)));
typedef unsigned gcov_type_unsigned __attribute__ ((mode (SI)));
#endif
#else
#if BITS_PER_UNIT == 16
typedef unsigned gcov_unsigned_t __attribute__ ((mode (HI)));
typedef unsigned gcov_position_t __attribute__ ((mode (HI)));
#if LONG_LONG_TYPE_SIZE > 32
typedef signed gcov_type __attribute__ ((mode (SI)));
typedef unsigned gcov_type_unsigned __attribute__ ((mode (SI)));
#else
typedef signed gcov_type __attribute__ ((mode (HI)));
typedef unsigned gcov_type_unsigned __attribute__ ((mode (HI)));
#endif
#else
typedef unsigned gcov_unsigned_t __attribute__ ((mode (QI)));
typedef unsigned gcov_position_t __attribute__ ((mode (QI)));
#if LONG_LONG_TYPE_SIZE > 32
typedef signed gcov_type __attribute__ ((mode (HI)));
typedef unsigned gcov_type_unsigned __attribute__ ((mode (HI)));
#else
typedef signed gcov_type __attribute__ ((mode (QI)));
typedef unsigned gcov_type_unsigned __attribute__ ((mode (QI)));
#endif
#endif
#endif

#if defined (TARGET_POSIX_IO)
#define GCOV_LOCKED 1
#else
#define GCOV_LOCKED 0
#endif

/* In libgcov we need these functions to be extern, so prefix them with
   __gcov.  In libgcov they must also be hidden so that the instance in
   the executable is not also used in a DSO.  */
#define gcov_var __gcov_var__ported
#define gcov_open __gcov_open__ported
#define gcov_close __gcov_close__ported
#define gcov_write_tag_length __gcov_write_tag_length__ported
#define gcov_seek __gcov_seek__ported
#define gcov_write_unsigned __gcov_write_unsigned__ported
#define gcov_write_counter __gcov_write_counter__ported
#define gcov_write_summary __gcov_write_summary__ported
#define gcov_sort_n_vals __gcov_sort_n_vals__ported
//#define gcov_exit gcov_exit__ported
#define __gcov_dump_one __gcov_dump_one__ported

/* @STRIPPED lines 105-136 */

#endif /* !IN_GCOV_TOOL */

/* @STRIPPED lines 140-151 */

#ifdef HAVE_GAS_HIDDEN
#define ATTRIBUTE_HIDDEN  __attribute__ ((__visibility__ ("hidden")))
#else
#define ATTRIBUTE_HIDDEN
#endif

#include <libgcov-embedded/gcov-io.h>

/* Structures embedded in coveraged program.  The structures generated
   by write_profile must match these.  */

/* Information about counters for a single function.  */
struct gcov_ctr_info
{
  gcov_unsigned_t num;      /* number of counters.  */
  gcov_type *values;        /* their values.  */
};

/* Information about a single function.  This uses the trailing array
   idiom. The number of counters is determined from the merge pointer
   array in gcov_info.  The key is used to detect which of a set of
   comdat functions was selected -- it points to the gcov_info object
   of the object file containing the selected comdat function.  */

struct gcov_fn_info
{
  const struct gcov_info *key;      /* comdat key */
  gcov_unsigned_t ident;        /* unique ident of function */
  gcov_unsigned_t lineno_checksum;  /* function lineo_checksum */
  gcov_unsigned_t cfg_checksum;     /* function cfg checksum */
  struct gcov_ctr_info ctrs[1];     /* instrumented counters */
};

/* Type of function used to merge counters.  */
typedef void (*gcov_merge_fn) (gcov_type *, gcov_unsigned_t);

/* Information about a single object file.  */
struct gcov_info
{
  gcov_unsigned_t version;  /* expected version number */
  struct gcov_info *next;   /* link to next, used by libgcov */

  gcov_unsigned_t stamp;    /* uniquifying time stamp */
  const char *filename;     /* output file name */

  gcov_merge_fn merge[GCOV_COUNTERS];  /* merge functions (null for
                      unused) */
  
  unsigned n_functions;     /* number of functions */

#ifndef IN_GCOV_TOOL
  const struct gcov_fn_info *const *functions; /* pointer to pointers
                                                  to function information  */
#else
  const struct gcov_fn_info **functions;
#endif /* !IN_GCOV_TOOL */
};

/* Root of a program/shared-object state */
struct gcov_root
{
  struct gcov_info *list;
  unsigned dumped : 1;  /* counts have been dumped.  */
  unsigned run_counted : 1;  /* run has been accounted for.  */
  struct gcov_root *next;
  struct gcov_root *prev;
};

extern struct gcov_root __gcov_root ATTRIBUTE_HIDDEN;

struct gcov_master
{
  gcov_unsigned_t version;
  struct gcov_root *root;
};
  
/* Exactly one of these will be active in the process.  */
extern struct gcov_master __gcov_master;

/* Dump a set of gcov objects.  */
extern void __gcov_dump_one (struct gcov_root *) ATTRIBUTE_HIDDEN;

/* @STRIPPED lines 235-344 */

#endif /* LIBGCOV_H_ */

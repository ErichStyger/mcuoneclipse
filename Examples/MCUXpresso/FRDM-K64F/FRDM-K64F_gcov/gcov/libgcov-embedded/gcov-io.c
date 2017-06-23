/* File format for coverage information
   Copyright (C) 1996-2015 Free Software Foundation, Inc.
   Contributed by Bob Manson <manson@cygnus.com>.
   Completely remangled by Nathan Sidwell <nathan@codesourcery.com>.

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

#include "gcov_support.h"

#ifdef ENABLE_LIBGCOV_PORT

/* Since this file is no longer included by other C files, we need definitions
 * of data structures, macros etc. from the following header files
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libgcov-port.h"
#include "libgcov.h"
#include "libgcov-embedded.h"

#if !IN_GCOV
static void gcov_write_block (unsigned);
static gcov_unsigned_t *gcov_write_words (unsigned);
#endif

/* @STRIPPED lines 34-37 */

/* Optimum number of gcov_unsigned_t's read from or written to disk.  */
#define GCOV_BLOCK_SIZE (1 << 8)

/* The original definition of this macro is (1 << 10) which results in a
 * very large buffer sitting inside gcov_var struct below. In typical usage
 * of libgcov/gcov, the purpose of this buffer is to be an in-memory buffer
 * of GCDA data before it is full and needs to be flushed to the actual GCDA
 * file.
 *
 * The gcov_var struct and the buffer with static memory using the above macro
 * for its size value are used across various functions in this file, which we
 * left as is for now to avoid buggy/unstable changes in this iteration of the
 * porting effort. In our port, there is no GCDA file to auto flush the in
 * memory buffer; however, we have left the in-memory buffer as is. Only the
 * point where the in-memory buffer is flushed into the GCDA file is where
 * we have made changes to replace the file-based mechanism with our own, which
 * is basically another large buffer that can be read by the GDB command 'dump
 * binary memory' to manually create the GCDA file on host system.
 *
 * The idea of changing from 1 << 10 to 1 << 8 is to minimize the buffer size
 * for embedded systems so it does not require too much memory, as our port is
 * going ahead with keeping this in-memory buffer mechanism.
 */


struct gcov_var
{
#ifndef ENABLE_LIBGCOV_PORT
  FILE *file;
#else
/*
 * The gcov_var struct is kept mostly as is, except the porting change of not
 * using a FILE (can't use possibly without POSIX semihosting and more importantly
 * we don't intend to use a FILE here for GCDA file, as we are not going to have
 * one GCDA file on the embedded system; but only create a GCDA file manually using
 * GDB 'dump binary memory' command on the host system
*/
#define GCOV_GCDA_BUF_SZ (1 << 13) /* 8192 bytes for GCDA files */

  unsigned char * gcda_buf; /* Holds GCDA data in memory */
  unsigned char * gcda_buf_pos; /* Position in above buffer to write to */
  const char * filename; /* Host system GCDA file name */
#endif
  gcov_position_t start;    /* Position of first byte of block */
  unsigned offset;      /* Read/write position within the block.  */
  unsigned length;      /* Read limit in the block.  */
  unsigned overread;        /* Number of words overread.  */
  int error;            /* < 0 overflow, > 0 disk error.  */
  int mode;                 /* < 0 writing, > 0 reading */
#if IN_LIBGCOV
  /* Holds one block plus 4 bytes, thus all coverage reads & writes
     fit within this buffer and we always can transfer GCOV_BLOCK_SIZE
     to and from the disk. libgcov never backtracks and only writes 4
     or 8 byte objects.  */
  gcov_unsigned_t buffer[GCOV_BLOCK_SIZE + 1];
#else
  int endian;           /* Swap endianness.  */
  /* Holds a variable length block, as the compiler can write
     strings and needs to backtrack.  */
  size_t alloc;
  gcov_unsigned_t *buffer;
#endif
} gcov_var;

/* Open a gcov file. NAME is the name of the file to open and MODE
   indicates whether a new file should be created, or an existing file
   opened. If MODE is >= 0 an existing file will be opened, if
   possible, and if MODE is <= 0, a new file will be created. Use
   MODE=0 to attempt to reopen an existing file and then fall back on
   creating a new one.  If MODE < 0, the file will be opened in
   read-only mode.  Otherwise it will be opened for modification.
   Return zero on failure, >0 on opening an existing file and <0 on
   creating a new one.  */

GCOV_LINKAGE int
#if IN_LIBGCOV
gcov_open (const char *name)
#else
gcov_open (const char *name, int mode)
#endif
{
#if IN_LIBGCOV
#ifndef ENABLE_LIBGCOV_PORT
  const int mode = 0;
#endif
#endif
#if GCOV_LOCKED
  struct flock s_flock;
  int fd;

  s_flock.l_whence = SEEK_SET;
  s_flock.l_start = 0;
  s_flock.l_len = 0; /* Until EOF.  */
  s_flock.l_pid = getpid ();
#endif

#ifndef ENABLE_LIBGCOV_PORT
  gcov_nonruntime_assert (!gcov_var.file);
#endif
  gcov_var.start = 0;
  gcov_var.offset = gcov_var.length = 0;
  gcov_var.overread = -1u;
  gcov_var.error = 0;
#if !IN_LIBGCOV
  gcov_var.endian = 0;
#endif
#if GCOV_LOCKED
  if (mode > 0)
    {
      /* Read-only mode - acquire a read-lock.  */
      s_flock.l_type = F_RDLCK;
      /* pass mode (ignored) for compatibility */
      fd = open (name, O_RDONLY, S_IRUSR | S_IWUSR);
    }
  else if (mode < 0)
     {
       /* Write mode - acquire a write-lock.  */
       s_flock.l_type = F_WRLCK;
      fd = open (name, O_RDWR | O_CREAT | O_TRUNC, 0666);
    }
  else /* mode == 0 */
    {
      /* Read-Write mode - acquire a write-lock.  */
      s_flock.l_type = F_WRLCK;
      fd = open (name, O_RDWR | O_CREAT, 0666);
    }
  if (fd < 0)
    return 0;

  while (fcntl (fd, F_SETLKW, &s_flock) && errno == EINTR)
    continue;

  gcov_var.file = fdopen (fd, (mode > 0) ? "rb" : "r+b");

  if (!gcov_var.file)
    {
      close (fd);
      return 0;
    }

  if (mode > 0)
    gcov_var.mode = 1;
  else if (mode == 0)
    {
      struct stat st;

      if (fstat (fd, &st) < 0)
    {
      fclose (gcov_var.file);
      gcov_var.file = 0;
      return 0;
    }
      if (st.st_size != 0)
    gcov_var.mode = 1;
      else
    gcov_var.mode = mode * 2 + 1;
    }
  else
    gcov_var.mode = mode * 2 + 1;
#else
#ifndef ENABLE_LIBGCOV_PORT
  if (mode >= 0)
    gcov_var.file = fopen (name, (mode > 0) ? "rb" : "r+b");

  if (gcov_var.file)
    gcov_var.mode = 1;
  else if (mode <= 0)
    {
      gcov_var.file = fopen (name, "w+b");
      if (gcov_var.file)
    gcov_var.mode = mode * 2 + 1;
    }
  if (!gcov_var.file)
    return 0;
#else
  gcov_var.filename = name;
  gcov_var.gcda_buf = (unsigned char*)calloc(GCOV_GCDA_BUF_SZ, 1);
  if (! gcov_var.gcda_buf)
    return 0;
  gcov_var.gcda_buf_pos = gcov_var.gcda_buf;
#endif
#endif

#ifndef ENABLE_LIBGCOV_PORT
  setbuf (gcov_var.file, (char *)0);
#endif

  return 1;
}

/* Close the current gcov file. Flushes data to disk. Returns nonzero
   on failure or error flag set.  */

GCOV_LINKAGE int
gcov_close (void)
{
#ifndef ENABLE_LIBGCOV_PORT
  if (gcov_var.file)
    {
#endif
#if !IN_GCOV
      if (gcov_var.offset /* @NO_GCDA_FILE && gcov_var.mode < 0*/)
        gcov_write_block (gcov_var.offset);
#endif
#ifndef ENABLE_LIBGCOV_PORT
      fclose (gcov_var.file);
      gcov_var.file = 0;
#else
      gcov_writeDataHook(gcov_var.gcda_buf, gcov_var.gcda_buf_pos, gcov_var.filename);
      free(gcov_var.gcda_buf);
      gcov_var.gcda_buf = gcov_var.gcda_buf_pos = 0;
      gcov_var.filename = NULL;
#endif
      gcov_var.length = 0;
#ifndef ENABLE_LIBGCOV_PORT
    }
#endif
#if !IN_LIBGCOV
  free (gcov_var.buffer);
  gcov_var.alloc = 0;
  gcov_var.buffer = 0;
#endif
  gcov_var.mode = 0;
  return gcov_var.error;
}

static void
gcov_write_block (unsigned size)
{
#ifndef ENABLE_LIBGCOV_PORT
  if (fwrite (gcov_var.buffer, size << 2, 1, gcov_var.file) != 1)
    gcov_var.error = 1;
#else
  if(((gcov_var.gcda_buf_pos + (size << 2)) - gcov_var.gcda_buf) > GCOV_GCDA_BUF_SZ)
    gcov_var.error = 1;
  else {
    memcpy(gcov_var.gcda_buf_pos, gcov_var.buffer, (size << 2));
    gcov_var.gcda_buf_pos += (size << 2);
  }
#endif
  gcov_var.start += size;
  gcov_var.offset -= size;
}

/* Allocate space to write BYTES bytes to the gcov file. Return a
   pointer to those bytes, or NULL on failure.  */

static gcov_unsigned_t *
gcov_write_words (unsigned words)
{
  gcov_unsigned_t *result;

  gcov_nonruntime_assert (gcov_var.mode < 0);
#if IN_LIBGCOV
  if (gcov_var.offset >= GCOV_BLOCK_SIZE)
    {
      gcov_write_block (GCOV_BLOCK_SIZE);
      if (gcov_var.offset)
    {
      memcpy (gcov_var.buffer, gcov_var.buffer + GCOV_BLOCK_SIZE, 4);
    }
    }
#else
  if (gcov_var.offset + words > gcov_var.alloc)
    gcov_allocate (gcov_var.offset + words);
#endif
  result = &gcov_var.buffer[gcov_var.offset];
  gcov_var.offset += words;

  return result;
}

/* Write unsigned VALUE to coverage file.  Sets error flag
   appropriately.  */

GCOV_LINKAGE void
gcov_write_unsigned (gcov_unsigned_t value)
{
  gcov_unsigned_t *buffer = gcov_write_words (1);

  buffer[0] = value;
}

/* Write counter VALUE to coverage file.  Sets error flag
   appropriately.  */

#if IN_LIBGCOV
GCOV_LINKAGE void
gcov_write_counter (gcov_type value)
{
  gcov_unsigned_t *buffer = gcov_write_words (2);

  buffer[0] = (gcov_unsigned_t) value;
  if (sizeof (value) > sizeof (gcov_unsigned_t))
    buffer[1] = (gcov_unsigned_t) (value >> 32);
  else
    buffer[1] = 0;
}
#endif /* IN_LIBGCOV */

/* Write a tag TAG and length LENGTH.  */

GCOV_LINKAGE void
gcov_write_tag_length (gcov_unsigned_t tag, gcov_unsigned_t length)
{
  gcov_unsigned_t *buffer = gcov_write_words (2);

  buffer[0] = tag;
  buffer[1] = length;
}

/* Write a summary structure to the gcov file.  Return nonzero on
   overflow.  */

GCOV_LINKAGE void
gcov_write_summary (gcov_unsigned_t tag, const struct gcov_summary *summary)
{
  unsigned ix, h_ix, bv_ix, h_cnt = 0;
  const struct gcov_ctr_summary *csum;
  unsigned histo_bitvector[GCOV_HISTOGRAM_BITVECTOR_SIZE];

  /* Count number of non-zero histogram entries, and fill in a bit vector
     of non-zero indices. The histogram is only currently computed for arc
     counters.  */
  for (bv_ix = 0; bv_ix < GCOV_HISTOGRAM_BITVECTOR_SIZE; bv_ix++)
    histo_bitvector[bv_ix] = 0;
  csum = &summary->ctrs[GCOV_COUNTER_ARCS];
  for (h_ix = 0; h_ix < GCOV_HISTOGRAM_SIZE; h_ix++)
    {
      if (csum->histogram[h_ix].num_counters > 0)
        {
          histo_bitvector[h_ix / 32] |= 1 << (h_ix % 32);
          h_cnt++;
        }
    }
  gcov_write_tag_length (tag, GCOV_TAG_SUMMARY_LENGTH (h_cnt));
  gcov_write_unsigned (summary->checksum);
  for (csum = summary->ctrs, ix = GCOV_COUNTERS_SUMMABLE; ix--; csum++)
    {
      gcov_write_unsigned (csum->num);
      gcov_write_unsigned (csum->runs);
      gcov_write_counter (csum->sum_all);
      gcov_write_counter (csum->run_max);
      gcov_write_counter (csum->sum_max);
      if (ix != GCOV_COUNTER_ARCS)
        {
          for (bv_ix = 0; bv_ix < GCOV_HISTOGRAM_BITVECTOR_SIZE; bv_ix++)
            gcov_write_unsigned (0);
          continue;
        }
      for (bv_ix = 0; bv_ix < GCOV_HISTOGRAM_BITVECTOR_SIZE; bv_ix++)
        gcov_write_unsigned (histo_bitvector[bv_ix]);
      for (h_ix = 0; h_ix < GCOV_HISTOGRAM_SIZE; h_ix++)
        {
          if (!csum->histogram[h_ix].num_counters)
            continue;
          gcov_write_unsigned (csum->histogram[h_ix].num_counters);
          gcov_write_counter (csum->histogram[h_ix].min_value);
          gcov_write_counter (csum->histogram[h_ix].cum_value);
        }
    }
}

#if IN_LIBGCOV
/* Move to a given position in a gcov file.  */

GCOV_LINKAGE void
gcov_seek (gcov_position_t base)
{
  if (gcov_var.offset)
    gcov_write_block (gcov_var.offset);
#ifndef ENABLE_LIBGCOV_PORT
  fseek (gcov_var.file, base << 2, SEEK_SET);
  gcov_var.start = ftell (gcov_var.file) >> 2;
#else
  gcov_var.gcda_buf_pos = gcov_var.gcda_buf + (base << 2);
  gcov_var.start = base;
#endif
}
#endif

#if !IN_GCOV
/* Determine the index into histogram for VALUE. */

#if IN_LIBGCOV
/* @NO_INCLUDE_SRC static */ unsigned
#else
GCOV_LINKAGE unsigned
#endif
gcov_histo_index (gcov_type value)
{
  gcov_type_unsigned v = (gcov_type_unsigned)value;
  unsigned r = 0;
  unsigned prev2bits = 0;

  /* Find index into log2 scale histogram, where each of the log2
     sized buckets is divided into 4 linear sub-buckets for better
     focus in the higher buckets.  */

  /* Find the place of the most-significant bit set.  */
  if (v > 0)
    {
#if IN_LIBGCOV
      /* When building libgcov we don't include system.h, which includes
         hwint.h (where floor_log2 is declared). However, libgcov.a
         is built by the bootstrapped compiler and therefore the builtins
         are always available.  */
      r = sizeof (long long) * __CHAR_BIT__ - 1 - __builtin_clzll (v);
#else
      /* We use floor_log2 from hwint.c, which takes a HOST_WIDE_INT
         that is 64 bits and gcov_type_unsigned is 64 bits.  */
      r = floor_log2 (v);
#endif
    }

  /* If at most the 2 least significant bits are set (value is
     0 - 3) then that value is our index into the lowest set of
     four buckets.  */
  if (r < 2)
    return (unsigned)value;

  gcov_nonruntime_assert (r < 64);

  /* Find the two next most significant bits to determine which
     of the four linear sub-buckets to select.  */
  prev2bits = (v >> (r - 2)) & 0x3;
  /* Finally, compose the final bucket index from the log2 index and
     the next 2 bits. The minimum r value at this point is 2 since we
     returned above if r was 2 or more, so the minimum bucket at this
     point is 4.  */
  return (r - 1) * 4 + prev2bits;
}

/* Merge SRC_HISTO into TGT_HISTO. The counters are assumed to be in
   the same relative order in both histograms, and are matched up
   and merged in reverse order. Each counter is assigned an equal portion of
   its entry's original cumulative counter value when computing the
   new merged cum_value.  */

/* @NO_INCLUDE_SRC static */ void gcov_histogram_merge (gcov_bucket_type *tgt_histo,
                                  gcov_bucket_type *src_histo)
{
  int src_i, tgt_i, tmp_i = 0;
  unsigned src_num, tgt_num, merge_num;
  gcov_type src_cum, tgt_cum, merge_src_cum, merge_tgt_cum, merge_cum;
  gcov_type merge_min;
  gcov_bucket_type tmp_histo[GCOV_HISTOGRAM_SIZE];
  int src_done = 0;

  memset (tmp_histo, 0, sizeof (gcov_bucket_type) * GCOV_HISTOGRAM_SIZE);

  /* Assume that the counters are in the same relative order in both
     histograms. Walk the histograms from largest to smallest entry,
     matching up and combining counters in order.  */
  src_num = 0;
  src_cum = 0;
  src_i = GCOV_HISTOGRAM_SIZE - 1;
  for (tgt_i = GCOV_HISTOGRAM_SIZE - 1; tgt_i >= 0 && !src_done; tgt_i--)
    {
      tgt_num = tgt_histo[tgt_i].num_counters;
      tgt_cum = tgt_histo[tgt_i].cum_value;
      /* Keep going until all of the target histogram's counters at this
         position have been matched and merged with counters from the
         source histogram.  */
      while (tgt_num > 0 && !src_done)
        {
          /* If this is either the first time through this loop or we just
             exhausted the previous non-zero source histogram entry, look
             for the next non-zero source histogram entry.  */
          if (!src_num)
            {
              /* Locate the next non-zero entry.  */
              while (src_i >= 0 && !src_histo[src_i].num_counters)
                src_i--;
              /* If source histogram has fewer counters, then just copy over the
                 remaining target counters and quit.  */
              if (src_i < 0)
                {
                  tmp_histo[tgt_i].num_counters += tgt_num;
                  tmp_histo[tgt_i].cum_value += tgt_cum;
                  if (!tmp_histo[tgt_i].min_value ||
                      tgt_histo[tgt_i].min_value < tmp_histo[tgt_i].min_value)
                    tmp_histo[tgt_i].min_value = tgt_histo[tgt_i].min_value;
                  while (--tgt_i >= 0)
                    {
                      tmp_histo[tgt_i].num_counters
                          += tgt_histo[tgt_i].num_counters;
                      tmp_histo[tgt_i].cum_value += tgt_histo[tgt_i].cum_value;
                      if (!tmp_histo[tgt_i].min_value ||
                          tgt_histo[tgt_i].min_value
                          < tmp_histo[tgt_i].min_value)
                        tmp_histo[tgt_i].min_value = tgt_histo[tgt_i].min_value;
                    }

                  src_done = 1;
                  break;
                }

              src_num = src_histo[src_i].num_counters;
              src_cum = src_histo[src_i].cum_value;
            }

          /* The number of counters to merge on this pass is the minimum
             of the remaining counters from the current target and source
             histogram entries.  */
          merge_num = tgt_num;
          if (src_num < merge_num)
            merge_num = src_num;

          /* The merged min_value is the sum of the min_values from target
             and source.  */
          merge_min = tgt_histo[tgt_i].min_value + src_histo[src_i].min_value;

          /* Compute the portion of source and target entries' cum_value
             that will be apportioned to the counters being merged.
             The total remaining cum_value from each entry is divided
             equally among the counters from that histogram entry if we
             are not merging all of them.  */
          merge_src_cum = src_cum;
          if (merge_num < src_num)
            merge_src_cum = merge_num * src_cum / src_num;
          merge_tgt_cum = tgt_cum;
          if (merge_num < tgt_num)
            merge_tgt_cum = merge_num * tgt_cum / tgt_num;
          /* The merged cum_value is the sum of the source and target
             components.  */
          merge_cum = merge_src_cum + merge_tgt_cum;

          /* Update the remaining number of counters and cum_value left
             to be merged from this source and target entry.  */
          src_cum -= merge_src_cum;
          tgt_cum -= merge_tgt_cum;
          src_num -= merge_num;
          tgt_num -= merge_num;

          /* The merged counters get placed in the new merged histogram
             at the entry for the merged min_value.  */
          tmp_i = gcov_histo_index (merge_min);
          gcov_nonruntime_assert (tmp_i < GCOV_HISTOGRAM_SIZE);
          tmp_histo[tmp_i].num_counters += merge_num;
          tmp_histo[tmp_i].cum_value += merge_cum;
          if (!tmp_histo[tmp_i].min_value ||
              merge_min < tmp_histo[tmp_i].min_value)
            tmp_histo[tmp_i].min_value = merge_min;

          /* Ensure the search for the next non-zero src_histo entry starts
             at the next smallest histogram bucket.  */
          if (!src_num)
            src_i--;
        }
    }

  gcov_nonruntime_assert (tgt_i < 0);

  /* In the case where there were more counters in the source histogram,
     accumulate the remaining unmerged cumulative counter values. Add
     those to the smallest non-zero target histogram entry. Otherwise,
     the total cumulative counter values in the histogram will be smaller
     than the sum_all stored in the summary, which will complicate
     computing the working set information from the histogram later on.  */
  if (src_num)
    src_i--;
  while (src_i >= 0)
    {
      src_cum += src_histo[src_i].cum_value;
      src_i--;
    }
  /* At this point, tmp_i should be the smallest non-zero entry in the
     tmp_histo.  */
  gcov_nonruntime_assert (tmp_i >= 0 && tmp_i < GCOV_HISTOGRAM_SIZE
                          && tmp_histo[tmp_i].num_counters > 0);
  tmp_histo[tmp_i].cum_value += src_cum;

  /* Finally, copy the merged histogram into tgt_histo.  */
  memcpy (tgt_histo, tmp_histo,
      sizeof (gcov_bucket_type) * GCOV_HISTOGRAM_SIZE);
}
#endif /* !IN_GCOV */

#endif /* ENABLE_LIBGCOV_PORT */

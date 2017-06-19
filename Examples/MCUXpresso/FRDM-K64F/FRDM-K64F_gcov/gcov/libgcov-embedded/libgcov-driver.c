/* Routines required for instrumenting a program.  */
/* Compile this one with gcc.  */
/* Copyright (C) 1989-2015 Free Software Foundation, Inc.

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

#include <stdlib.h>
#include <string.h>
#include "libgcov-port.h"
#include "libgcov.h"

GCOV_LINKAGE /* @NO_INCLUDE_SRC static */ int gcov_exit_open_gcda_file (struct gcov_info *gi_ptr
            /* @NO_AUTO_GCDA_CREATION , struct gcov_filename *gf*/);


struct gcov_fn_buffer
{
  struct gcov_fn_buffer *next;
  unsigned fn_ix;
  struct gcov_fn_info info;
  /* note gcov_fn_info ends in a trailing array.  */
};

struct gcov_summary_buffer
{
  struct gcov_summary_buffer *next;
  struct gcov_summary summary;
};

static struct gcov_fn_buffer *
free_fn_data (const struct gcov_info *gi_ptr, struct gcov_fn_buffer *buffer,
              unsigned limit)
{
  struct gcov_fn_buffer *next;
  unsigned ix, n_ctr = 0;

  if (!buffer)
    return 0;
  next = buffer->next;

  for (ix = 0; ix != limit; ix++)
    if (gi_ptr->merge[ix])
      free (buffer->info.ctrs[n_ctr++].values);
  free (buffer);
  return next;
}

static gcov_unsigned_t
crc32_unsigned (gcov_unsigned_t crc32, gcov_unsigned_t value)
{
  unsigned ix;

  for (ix = 32; ix--; value <<= 1)
    {
      unsigned feedback;

      feedback = (value ^ crc32) & 0x80000000 ? 0x04c11db7 : 0;
      crc32 <<= 1;
      crc32 ^= feedback;
    }

  return crc32;
}

/* Insert counter VALUE into HISTOGRAM.  */

static void
gcov_histogram_insert(gcov_bucket_type *histogram, gcov_type value)
{
  unsigned i;

  i = gcov_histo_index(value);
  histogram[i].num_counters++;
  histogram[i].cum_value += value;
  if (value < histogram[i].min_value)
    histogram[i].min_value = value;
}

/* Computes a histogram of the arc counters to place in the summary SUM.  */

static void
gcov_compute_histogram (struct gcov_info *list, struct gcov_summary *sum)
{
  struct gcov_info *gi_ptr;
  const struct gcov_fn_info *gfi_ptr;
  const struct gcov_ctr_info *ci_ptr;
  struct gcov_ctr_summary *cs_ptr;
  unsigned t_ix, f_ix, ctr_info_ix, ix;
/*
 * @GCOV_INFO_LIST_CIRCULAR_FIX
 * The gcov_info * list being parsed in several places is assumed to be a
 * non-circular singly linked list. However; it turns out that it is a circular
 * one! Because of this the loops were not exiting at all. This was the main
 * reason why __gcov_flush when used directly, not using this port, was never
 * ending.
*/   
  unsigned break_loop_counter = 0;
  int h_ix;

  /* This currently only applies to arc counters.  */
  t_ix = GCOV_COUNTER_ARCS;

  /* First check if there are any counts recorded for this counter.  */
  cs_ptr = &(sum->ctrs[t_ix]);
  if (!cs_ptr->num)
    return;

  for (h_ix = 0; h_ix < GCOV_HISTOGRAM_SIZE; h_ix++)
    {
      cs_ptr->histogram[h_ix].num_counters = 0;
      cs_ptr->histogram[h_ix].min_value = cs_ptr->run_max;
      cs_ptr->histogram[h_ix].cum_value = 0;
    }

  /* Walk through all the per-object structures and record each of
     the count values in histogram.  */
/*
 * @GCOV_INFO_LIST_CIRCULAR_FIX
 * The gcov_info * list being parsed in several places is assumed to be a
 * non-circular singly linked list. However; it turns out that it is a circular
 * one! Because of this the loops were not exiting at all. This was the main
 * reason why __gcov_flush when used directly, not using this port, was never
 * ending.
*/   
  for (gi_ptr = list; gi_ptr && !(gi_ptr == list && break_loop_counter); gi_ptr = gi_ptr->next, break_loop_counter++)
    {
      if (!gi_ptr->merge[t_ix])
        continue;

      /* Find the appropriate index into the gcov_ctr_info array
         for the counter we are currently working on based on the
         existence of the merge function pointer for this object.  */
      for (ix = 0, ctr_info_ix = 0; ix < t_ix; ix++)
        {
          if (gi_ptr->merge[ix])
            ctr_info_ix++;
        }
      for (f_ix = 0; f_ix != gi_ptr->n_functions; f_ix++)
        {
          gfi_ptr = gi_ptr->functions[f_ix];

          if (!gfi_ptr || gfi_ptr->key != gi_ptr)
            continue;

          ci_ptr = &gfi_ptr->ctrs[ctr_info_ix];
          for (ix = 0; ix < ci_ptr->num; ix++)
            gcov_histogram_insert (cs_ptr->histogram, ci_ptr->values[ix]);
        }
    }
}

/* buffer for the fn_data from another program.  */
static struct gcov_fn_buffer *fn_buffer;
/* buffer for summary from other programs to be written out. */
static struct gcov_summary_buffer *sum_buffer;

/* This function computes the program level summary and the histo-gram.
   It computes and returns CRC32 and stored summary in THIS_PRG.
   Also determines the longest filename length of the info files.  */

#if !IN_GCOV_TOOL
static
#endif
gcov_unsigned_t
compute_summary (struct gcov_info *list, struct gcov_summary *this_prg
                 /* @NO_GCDA_FILE , size_t *max_length*/)
{
  struct gcov_info *gi_ptr;
  const struct gcov_fn_info *gfi_ptr;
  struct gcov_ctr_summary *cs_ptr;
  const struct gcov_ctr_info *ci_ptr;
  int f_ix;
  unsigned t_ix;
  gcov_unsigned_t c_num;
  gcov_unsigned_t crc32 = 0;
/*
 * @GCOV_INFO_LIST_CIRCULAR_FIX
 * The gcov_info * list being parsed in several places is assumed to be a
 * non-circular singly linked list. However; it turns out that it is a circular
 * one! Because of this the loops were not exiting at all. This was the main
 * reason why __gcov_flush when used directly, not using this port, was never
 * ending.
*/   
  unsigned break_loop_counter = 0;

  /* Find the totals for this execution.  */
  memset (this_prg, 0, sizeof (*this_prg));
#ifndef ENABLE_LIBGCOV_PORT
  *max_length = 0;
#endif
/*
 * @GCOV_INFO_LIST_CIRCULAR_FIX
 * The gcov_info * list being parsed in several places is assumed to be a
 * non-circular singly linked list. However; it turns out that it is a circular
 * one! Because of this the loops were not exiting at all. This was the main
 * reason why __gcov_flush when used directly, not using this port, was never
 * ending.
*/   
  for (gi_ptr = list; gi_ptr && !(gi_ptr == list && break_loop_counter); gi_ptr = gi_ptr->next, break_loop_counter++)
    {
#ifndef ENABLE_LIBGCOV_PORT
      /* @NO_GCDA_FILE */
      size_t len = strlen (gi_ptr->filename);
      if (len > *max_length)
    *max_length = len;
#endif

      crc32 = crc32_unsigned (crc32, gi_ptr->stamp);
      crc32 = crc32_unsigned (crc32, gi_ptr->n_functions);

      for (f_ix = 0; (unsigned)f_ix != gi_ptr->n_functions; f_ix++)
        {
          gfi_ptr = gi_ptr->functions[f_ix];

          if (gfi_ptr && gfi_ptr->key != gi_ptr)
            gfi_ptr = 0;

          crc32 = crc32_unsigned (crc32, gfi_ptr ? gfi_ptr->cfg_checksum : 0);
          crc32 = crc32_unsigned (crc32,
                                  gfi_ptr ? gfi_ptr->lineno_checksum : 0);
          if (!gfi_ptr)
            continue;

          ci_ptr = gfi_ptr->ctrs;
          for (t_ix = 0; t_ix != GCOV_COUNTERS_SUMMABLE; t_ix++)
            {
              if (!gi_ptr->merge[t_ix])
                continue;

              cs_ptr = &(this_prg->ctrs[t_ix]);
              cs_ptr->num += ci_ptr->num;
              crc32 = crc32_unsigned (crc32, ci_ptr->num);

              for (c_num = 0; c_num < ci_ptr->num; c_num++)
                {
                  cs_ptr->sum_all += ci_ptr->values[c_num];
                  if (cs_ptr->run_max < ci_ptr->values[c_num])
                    cs_ptr->run_max = ci_ptr->values[c_num];
                }
              ci_ptr++;
            }
        }
    }
  gcov_compute_histogram (list, this_prg);
  return crc32;
}

/* Write counters in GI_PTR and the summary in PRG to a gcda file. In
   the case of appending to an existing file, SUMMARY_POS will be non-zero.
   We will write the file starting from SUMMAY_POS.  */

static void
write_one_data (const struct gcov_info *gi_ptr,
        const struct gcov_summary *prg_p,
        const gcov_position_t eof_pos,
        const gcov_position_t summary_pos)
{
  unsigned f_ix;
  struct gcov_summary_buffer *next_sum_buffer;

  /* Write out the data.  */
  if (!eof_pos)
    {
      gcov_write_tag_length (GCOV_DATA_MAGIC, GCOV_VERSION);
      gcov_write_unsigned (gi_ptr->stamp);
    }

  if (summary_pos)
    gcov_seek (summary_pos);

  /* Generate whole program statistics.  */
  gcov_write_summary (GCOV_TAG_PROGRAM_SUMMARY, prg_p);

  /* Rewrite all the summaries that were after the summary we merged
     into. This is necessary as the merged summary may have a different
     size due to the number of non-zero histogram entries changing after
     merging.  */

  while (sum_buffer)
    {
      gcov_write_summary (GCOV_TAG_PROGRAM_SUMMARY, &sum_buffer->summary);
      next_sum_buffer = sum_buffer->next;
      free (sum_buffer);
      sum_buffer = next_sum_buffer;
    }

  /* Write execution counts for each function.  */
  for (f_ix = 0; f_ix != gi_ptr->n_functions; f_ix++)
    {
      unsigned buffered = 0;
      const struct gcov_fn_info *gfi_ptr;
      const struct gcov_ctr_info *ci_ptr;
      gcov_unsigned_t length;
      unsigned t_ix;

      if (fn_buffer && fn_buffer->fn_ix == f_ix)
        {
          /* Buffered data from another program.  */
          buffered = 1;
          gfi_ptr = &fn_buffer->info;
          length = GCOV_TAG_FUNCTION_LENGTH;
        }
      else
        {
          gfi_ptr = gi_ptr->functions[f_ix];
          if (gfi_ptr && gfi_ptr->key == gi_ptr)
            length = GCOV_TAG_FUNCTION_LENGTH;
          else
                length = 0;
        }

      gcov_write_tag_length (GCOV_TAG_FUNCTION, length);
      if (!length)
        continue;

      gcov_write_unsigned (gfi_ptr->ident);
      gcov_write_unsigned (gfi_ptr->lineno_checksum);
      gcov_write_unsigned (gfi_ptr->cfg_checksum);

      ci_ptr = gfi_ptr->ctrs;
      for (t_ix = 0; t_ix < GCOV_COUNTERS; t_ix++)
        {
          gcov_unsigned_t n_counts;
          gcov_type *c_ptr;

          if (!gi_ptr->merge[t_ix])
            continue;

          n_counts = ci_ptr->num;
          gcov_write_tag_length (GCOV_TAG_FOR_COUNTER (t_ix),
                                 GCOV_TAG_COUNTER_LENGTH (n_counts));
          c_ptr = ci_ptr->values;
          while (n_counts--)
            gcov_write_counter (*c_ptr++);
          ci_ptr++;
        }
      if (buffered)
        fn_buffer = free_fn_data (gi_ptr, fn_buffer, GCOV_COUNTERS);
    }

  gcov_write_unsigned (0);
}

/* Helper function for merging summary.
   Return -1 on error. Return 0 on success.  */

static int
merge_summary (/* @NO_GCDA_FILE const char *filename, */ int run_counted,
           const struct gcov_info *gi_ptr, struct gcov_summary *prg,
           struct gcov_summary *this_prg, gcov_unsigned_t crc32,
           struct gcov_summary *all_prg __attribute__ ((unused)))
{
  struct gcov_ctr_summary *cs_prg, *cs_tprg;
  unsigned t_ix;
#if !GCOV_LOCKED 
  /* summary for all instances of program.  */ 
  struct gcov_ctr_summary *cs_all;
#endif 

  /* Merge the summaries.  */
  for (t_ix = 0; t_ix < GCOV_COUNTERS_SUMMABLE; t_ix++)
    {
      cs_prg = &(prg->ctrs[t_ix]);
      cs_tprg = &(this_prg->ctrs[t_ix]);

      if (gi_ptr->merge[t_ix])
        {
      int first = !cs_prg->runs;

      if (!run_counted)
        cs_prg->runs++;
          if (first)
            cs_prg->num = cs_tprg->num;
          cs_prg->sum_all += cs_tprg->sum_all;
          if (cs_prg->run_max < cs_tprg->run_max)
            cs_prg->run_max = cs_tprg->run_max;
          cs_prg->sum_max += cs_tprg->run_max;
          if (first)
            memcpy (cs_prg->histogram, cs_tprg->histogram,
                   sizeof (gcov_bucket_type) * GCOV_HISTOGRAM_SIZE);
          else
            gcov_histogram_merge (cs_prg->histogram, cs_tprg->histogram);
        }
      else if (cs_prg->runs)
        {
#ifndef ENABLE_LIBGCOV_PORT
          gcov_error ("profiling:%s:Merge mismatch for summary.\n",
                      filename);
#endif
          return -1;
        }
#if !GCOV_LOCKED
      cs_all = &all_prg->ctrs[t_ix];
      if (!cs_all->runs && cs_prg->runs)
        {
          cs_all->num = cs_prg->num;
          cs_all->runs = cs_prg->runs;
          cs_all->sum_all = cs_prg->sum_all;
          cs_all->run_max = cs_prg->run_max;
          cs_all->sum_max = cs_prg->sum_max;
        }
      else if (!all_prg->checksum
               /* Don't compare the histograms, which may have slight
                  variations depending on the order they were updated
                  due to the truncating integer divides used in the
                  merge.  */
               && (cs_all->num != cs_prg->num
                   || cs_all->runs != cs_prg->runs
                   || cs_all->sum_all != cs_prg->sum_all
                   || cs_all->run_max != cs_prg->run_max
                   || cs_all->sum_max != cs_prg->sum_max))
             {
#ifndef ENABLE_LIBGCOV_PORT
                gcov_error ("profiling:%s:Data file mismatch - some "
                           "data files may have been concurrently "
                           "updated without locking support\n", filename);
#endif
               all_prg->checksum = ~0u;
             }
#endif
    }
  
  prg->checksum = crc32;

  return 0;
}


/* Sort N entries in VALUE_ARRAY in descending order.
   Each entry in VALUE_ARRAY has two values. The sorting
   is based on the second value.  */

GCOV_LINKAGE  void
gcov_sort_n_vals (gcov_type *value_array, int n)
{
  int j, k;

  for (j = 2; j < n; j += 2)
    {
      gcov_type cur_ent[2];

      cur_ent[0] = value_array[j];
      cur_ent[1] = value_array[j + 1];
      k = j - 2;
      while (k >= 0 && value_array[k + 1] < cur_ent[1])
        {
          value_array[k + 2] = value_array[k];
          value_array[k + 3] = value_array[k+1];
          k -= 2;
        }
      value_array[k + 2] = cur_ent[0];
      value_array[k + 3] = cur_ent[1];
    }
}

/* Sort the profile counters for all indirect call sites. Counters
   for each call site are allocated in array COUNTERS.  */

static void
gcov_sort_icall_topn_counter (const struct gcov_ctr_info *counters)
{
  int i;
  gcov_type *values;
  int n = counters->num;

  gcc_assert (!(n % GCOV_ICALL_TOPN_NCOUNTS));
  values = counters->values;

  for (i = 0; i < n; i += GCOV_ICALL_TOPN_NCOUNTS)
    {
      gcov_type *value_array = &values[i + 1];
      gcov_sort_n_vals (value_array, GCOV_ICALL_TOPN_NCOUNTS - 1);
    }
}

/* Sort topn indirect_call profile counters in GI_PTR.  */

static void
gcov_sort_topn_counter_arrays (const struct gcov_info *gi_ptr)
{
  unsigned int i;
  int f_ix;
  const struct gcov_fn_info *gfi_ptr;
  const struct gcov_ctr_info *ci_ptr;

  if (!gi_ptr->merge[GCOV_COUNTER_ICALL_TOPNV]) 
    return;

  for (f_ix = 0; (unsigned)f_ix != gi_ptr->n_functions; f_ix++)
    {
      gfi_ptr = gi_ptr->functions[f_ix];
      ci_ptr = gfi_ptr->ctrs;
      for (i = 0; i < GCOV_COUNTERS; i++)
        {
          if (!gi_ptr->merge[i])
            continue;
          if (i == GCOV_COUNTER_ICALL_TOPNV)
            {
              gcov_sort_icall_topn_counter (ci_ptr);
              break;
            }
          ci_ptr++;
        }
    }
}

/* Dump the coverage counts for one gcov_info object. We merge with existing
   counts when possible, to avoid growing the .da files ad infinitum. We use
   this program's checksum to make sure we only accumulate whole program
   statistics to the correct summary. An object file might be embedded
   in two separate programs, and we must keep the two program
   summaries separate.  */

static void
dump_one_gcov (struct gcov_info *gi_ptr, /* @NO_GCDA_FILE struct gcov_filename *gf, */
           unsigned run_counted,
           gcov_unsigned_t crc32, struct gcov_summary *all_prg,
           struct gcov_summary *this_prg)
{
  struct gcov_summary prg; /* summary for this object over all program.  */
  int error;
#ifndef ENABLE_LIBGCOV_PORT
  gcov_unsigned_t tag;
#endif
  gcov_position_t summary_pos = 0;
  gcov_position_t eof_pos = 0;

  fn_buffer = 0;
  sum_buffer = 0;

  gcov_sort_topn_counter_arrays (gi_ptr);

  error = gcov_exit_open_gcda_file (gi_ptr/* @NO_GCDA_FILE, gf*/);
  if (error == -1)
    return;

#ifndef ENABLE_LIBGCOV_PORT
/*
 * For this version of the libgcov port, we have assumed that we don't need
 * to merge existing GCDA, and we need to generate and store fresh coverage
 * data alone. Hence this whole logic of reading existing GCDA files, and merging
 * the read data into this run's counters is disabled as of now.
*/
  tag = gcov_read_unsigned ();
  if (tag)
    {
      /* Merge data from file.  */
      if (tag != GCOV_DATA_MAGIC)
        {
          gcov_error ("profiling:%s:Not a gcov data file\n", gf->filename);
          goto read_fatal;
        }
      error = merge_one_data (gf->filename, gi_ptr, &prg, this_prg,
                  &summary_pos, &eof_pos, crc32);
      if (error == -1)
        goto read_fatal;
    }

  gcov_rewrite ();
#endif /* !ENABLE_LIBGCOV_PORT */

  if (!summary_pos)
    {
      memset (&prg, 0, sizeof (prg));
      summary_pos = eof_pos;
    }

  error = merge_summary (/* @NO_GCDA_FILE gf->filename, */ run_counted, gi_ptr, &prg, this_prg,
             crc32, all_prg);
  if (error == -1)
    goto read_fatal;

  write_one_data (gi_ptr, &prg, eof_pos, summary_pos);
  /* fall through */

read_fatal:;
  while (fn_buffer)
    fn_buffer = free_fn_data (gi_ptr, fn_buffer, GCOV_COUNTERS);

  if ((error = gcov_close ()))
#ifndef ENABLE_LIBGCOV_PORT
    gcov_error (error  < 0 ?
                "profiling:%s:Overflow writing\n" :
                "profiling:%s:Error writing\n",
                gf->filename);
#else
      { }
#endif
}


/* Dump all the coverage counts for the program. It first computes program
   summary and then traverses gcov_list list and dumps the gcov_info
   objects one by one.  */

#if !IN_GCOV_TOOL
static
#endif
void
gcov_do_dump (struct gcov_info *list, int run_counted)
{
  struct gcov_info *gi_ptr;
#ifndef ENABLE_LIBGCOV_PORT
  struct gcov_filename gf;
#endif
  gcov_unsigned_t crc32;
/*
 * @GCOV_INFO_LIST_CIRCULAR_FIX
 * The gcov_info * list being parsed in several places is assumed to be a
 * non-circular singly linked list. However; it turns out that it is a circular
 * one! Because of this the loops were not exiting at all. This was the main
 * reason why __gcov_flush when used directly, not using this port, was never
 * ending.
*/   
  gcov_unsigned_t break_loop_counter = 0;
  struct gcov_summary all_prg;
  struct gcov_summary this_prg;

  crc32 = compute_summary (list, &this_prg /* @NO_GCDA_FILE , &gf.max_length*/);

#ifndef ENABLE_LIBGCOV_PORT
  allocate_filename_struct (&gf);
#endif

#if !GCOV_LOCKED
  memset (&all_prg, 0, sizeof (all_prg));
#endif

  /* Now merge each file.  */
/*
 * @GCOV_INFO_LIST_CIRCULAR_FIX
 * The gcov_info * list being parsed in several places is assumed to be a
 * non-circular singly linked list. However; it turns out that it is a circular
 * one! Because of this the loops were not exiting at all. This was the main
 * reason why __gcov_flush when used directly, not using this port, was never
 * ending.
*/   
  for (gi_ptr = list; gi_ptr && !(gi_ptr == list && break_loop_counter); gi_ptr = gi_ptr->next, break_loop_counter++)
    dump_one_gcov (gi_ptr, /* @NO_GCDA_FILE &gf,*/ run_counted, crc32, &all_prg, &this_prg);

#ifndef ENABLE_LIBGCOV_PORT
  free (gf.filename);
#endif
}

#if !IN_GCOV_TOOL
void
__gcov_dump_one (struct gcov_root *root)
{
  if (root->dumped)
    return;

  gcov_do_dump (root->list, root->run_counted);
  
  root->dumped = 1;
  root->run_counted = 1;
}

#ifndef ENABLE_LIBGCOV_PORT
/*
 * The following two are the main gcov counter variables, which are already
 * available and populated by the gcov instrumentation. We are only going to
 * read these variables, and hence these are not defined by the port
*/

/* Per-dynamic-object gcov state.  */
struct gcov_root __gcov_root;

/* Exactly one of these will be live in the process image.  */
struct gcov_master __gcov_master = 
  {GCOV_VERSION, 0};

#endif

void
gcov_exit (void)
{
  __gcov_dump_one (&__gcov_root);
  if (__gcov_root.next)
    __gcov_root.next->prev = __gcov_root.prev;
  if (__gcov_root.prev)
    __gcov_root.prev->next = __gcov_root.next;
  else
    __gcov_master.root = __gcov_root.next;
}

#endif /* !IN_GCOV_TOOL */

#endif /* ENABLE_LIBGCOV_PORT */

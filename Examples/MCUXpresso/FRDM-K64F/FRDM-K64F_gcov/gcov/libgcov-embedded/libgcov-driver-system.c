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

#ifndef ENABLE_LIBGCOV_PORT
  #error "ENABLE_LIBGCOV_PORT must be defined and set to 0 or 1"
#endif

#ifdef ENABLE_LIBGCOV_PORT

#include "libgcov-port.h"
#include "libgcov.h"

/* @STRIPPED lines 26-129 */

/* Open a gcda file specified by GI_FILENAME.
   Return -1 on error.  Return 0 on success.  */

/* @NO_INCLUDE_SRC static */ int
gcov_exit_open_gcda_file (struct gcov_info *gi_ptr
                          /* @NO_AUTO_GCDA_CREATION struct gcov_filename *gf */)
{
  const char *fname = gi_ptr->filename;
  /* @NO_AUTO_GCDA_CREATION char *dst = gf->filename + gf->prefix; */

  fname = gi_ptr->filename;

#if 0 /* @NO_AUTO_GCDA_CREATION */
  /* Build relocated filename, stripping off leading
     directories from the initial filename if requested. */
  if (gf->strip > 0)
    {
      const char *probe = fname;
      int level;

      /* Remove a leading separator, without counting it.  */
      if (IS_DIR_SEPARATOR (*probe))
    probe++;

      /* Skip selected directory levels.  If we fall off the end, we
     keep the final part.  */
      for (level = gf->strip; *probe && level; probe++)
        if (IS_DIR_SEPARATOR (*probe))
          {
            fname = probe;
            level--;
          }
    }

  /* Update complete filename with stripped original. */
  if (gf->prefix)
    {
      /* Avoid to add multiple drive letters into combined path.  */
      if (HAS_DRIVE_SPEC(fname))
    fname += 2;

      if (!IS_DIR_SEPARATOR (*fname))
    *dst++ = '/';
    }
  strcpy (dst, fname);

#endif // NO_AUTO_GCDA_CREATION

  /* The GCDA file name with path is available in gi_ptr->filename
   * so we take it from there and pass. We use this file name for
   * help in dumping binary data into the corresponding GCDA file
   * using GDB commands
  */
  if (!gcov_open (fname /* gf->filename */))
    {
#if 0 /* @NO_AUTO_GCDA_CREATION */
      /* Open failed likely due to missed directory.
         Create directory and retry to open file. */
      if (create_file_directory (gf->filename))
        {
          fprintf (stderr, "profiling:%s:Skip\n", gf->filename);
          return -1;
        }
      if (!gcov_open (gf->filename))
        {
          fprintf (stderr, "profiling:%s:Cannot open\n", gf->filename);
          return -1;
        }
#endif // NO_AUTO_GCDA_CREATION
      return -1;
    }

  return 0;
}

#endif // ENABLE_LIBGCOV_PORT

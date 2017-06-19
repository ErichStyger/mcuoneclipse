/**
 * \file gcov_support.h
 * \brief Support helpers to use gcov for embedded targets.
 * \author Erich Styger
 * \copyright
 * Web:         https://mcuoneclipse.com
 * SourceForge: https://sourceforge.net/projects/mcuoneclipse
 * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ###################################################################*/

#ifndef GCOV_SUPPORT_H_
#define GCOV_SUPPORT_H_

#define GCOV_DO_COVERAGE               (1)
  /*<! 1: to enable coverage; 0: to disable it */
#define GCOV_USE_STANDARD_GCOV_LIB     (1 && GCOV_DO_COVERAGE)
  /*<! 1: using standard gcov library inside newlib/newlib nano; 0: using custom gcov library */
#define GCOV_USE_TCOV                  (0 && !GCOV_USE_STANDARD_GCOV_LIB)
  /*<! 1: to enable tiny coverage module (do *not* add --coverage to the linker flags!); 0: to disable it */
#define GCOV_USE_GCOV_4_7              (0 && !GCOV_USE_STANDARD_GCOV_LIB)
  /*<! 1: Use gcc 4.7 port (experimental!) (do *not* add --coverage to the linker flags!); 0: to disable it */
#define GCOV_USE_GCOV_EMBEDDED         (0 && !GCOV_USE_STANDARD_GCOV_LIB)
  /*<! 1: Use libgcov-embedded port (do *not* add --coverage to the linker flags!); 0: to disable it */

#if GCOV_USE_GCOV_EMBEDDED
  #define ENABLE_LIBGCOV_PORT  (1)
#endif

/*!
 * \brief Test function to verify file I/O needed for gcov information generation.
 * \return 1 if file I/O does work, 0 otherwise
 */
int gcov_check(void);

/*!
 * \brief Flush and write the coverage information collected so far
 */
void gcov_write(void);

/*!
 * \brief Initialize the coverage information/constructors. Need to call this at the start of main().
 */
void gcov_init(void);

#endif /* GCOV_SUPPORT_H_ */

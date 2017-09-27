/*
 * libgcov-port.h
 *
 * @author Reetesh Ranjan <reeteshranjan@piaxis.tech>
 *
 *   This file contains the additional/modified data structures, prototypes etc.
 *   that are needed and do not exist in/belong to other files that were ported
 *   already
*/

#ifndef LIBGCOV_PORT_H
#define LIBGCOV_PORT_H

/* This preprocessor directive is manually defined here. */
#define IN_LIBGCOV              1

/*
 * IMPORTANT
 * Do not define this!
*/
/*
#define IN_GCOV                 1
*/

/*
 * This is defined by gcc sources as 8 and should not need any change
 * for most platforms. This value works when compiling with GNU ARM
 * toolchain for the test project where this port was verified.
*/
#define BITS_PER_UNIT           8

/*
 * This is defined for each platform/architecture in gcc code. The value
 * for most architectures is 64. The aarch64.h file by ARM which is part
 * of GCC defines it as 64. The GNU ARM Eclipse test project that we used
 * uses Aarch32 toolchain and not Aarch64; however, sizeof(long long)
 * returns 64, so we went with 64 as the value.
*/
#define LONG_LONG_TYPE_SIZE     64

/*
 * IMPORTANT
 * Do not define this!
 *
 * TARGET_POSIX_IO is defined only for standard OSes like Linux in GCC.
 * This is a very important macro as GCOV_LOCKED macro gets different
 * values based on whether this is defined or not.
 *
 * I made our decision of not defining this macro as follows:
 *   - Our port of libgcov uses no file handling (POSIX IO)
 */
/*
#define TARGET_POSIX_IO
*/


/*
 * This is copied from gcc/system.h as opposed to bringing that file here
 * as this was the only macro needed from that file
*/

#if ENABLE_ASSERT_CHECKING
#define gcc_assert(EXPR)                        \
   ((void)(!(EXPR) ? fancy_abort (__FILE__, __LINE__, __FUNCTION__), 0 : 0))
#elif (GCC_VERSION >= 4005)
#define gcc_assert(EXPR)                        \
  ((void)(__builtin_expect (!(EXPR), 0) ? __builtin_unreachable (), 0 : 0))
#else
/* Include EXPR, so that unused variable warnings do not occur.  */
#define gcc_assert(EXPR) ((void)(0 && (EXPR)))
#endif

#endif // LIBGCOV_PORT_H

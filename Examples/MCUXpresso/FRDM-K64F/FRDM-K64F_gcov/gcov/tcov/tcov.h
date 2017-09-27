#ifndef TCOV_H_
#define TCOV_H_

#include "gcov_support.h"

#if GCOV_USE_TCOV
#include <stdint.h>

typedef struct {
  uint32_t ident;
  uint32_t cntrCount;
  uint64_t const * values;
} tcov_fn_t;

typedef struct {
  uint32_t stamp;
  uint32_t fnCount;
} tcov_cu_t;

extern void tcov_print_all(void);

extern uint32_t tcov_get_num_cu(void);

extern tcov_cu_t tcov_get_cu(uint32_t const aCU);

extern tcov_fn_t tcov_get_fn(uint32_t const aCU, uint32_t const aFn);

#endif /* GCOV_USE_TCOV */

#endif /* TCOV_H_ */

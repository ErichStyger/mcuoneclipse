/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "asan.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/* hooks if using -fsanitize=address */
/* -fasan-shadow-offset=number */
/* -fsanitize=kernel-address */
static void __asan_ReportGenericError(void) {
  __asm volatile("bkpt #0"); /* stop application */
  for(;;){}
}

void __asan_report_store1(void) {__asan_ReportGenericError();}
void __asan_report_store2(void) {__asan_ReportGenericError();}
void __asan_report_store4(void) {__asan_ReportGenericError();}
void __asan_report_store_n(void) {__asan_ReportGenericError();}
void __asan_report_load1(void) {__asan_ReportGenericError();}
void __asan_report_load2(void) {__asan_ReportGenericError();}
void __asan_report_load4(void) {__asan_ReportGenericError();}
void __asan_report_load_n(void) {__asan_ReportGenericError();}

void __asan_stack_malloc_1(void) {}
void __asan_stack_malloc_2(void) {}
void __asan_handle_no_return(void) {}
void __asan_option_detect_stack_use_after_return(void) {}

void __asan_register_globals(void) {}
void __asan_unregister_globals(void) {}
void __asan_version_mismatch_check_v8(void) {}

#define APP_MEM_START 0x20000000 /* base RAM address */
#define APP_MEM_SIZE  0x10000  /* 64 kByte */
#define APP_MEM_END   (APP_MEM_START+APP_MEM_SIZE-1)

/* see https://github.com/gcc-mirror/gcc/blob/master/libsanitizer/asan/asan_interface_internal.h */
static uint8_t shadow[APP_MEM_SIZE/8]; /* one shadow byte for 8 application memory bytes */

typedef enum {
  kIsWrite,
  kIsRead,
} rw_mode_e;

static uint8_t *MemToShadow(void *address) {
  address -= APP_MEM_START;
  return shadow+(((uint32_t)address)>>3);
}

static void PoisonShadow(void *addr) {
  *MemToShadow(addr) = -1; /* mark memory in shadow as poisoned */
}

static void ClearShadow(void *addr) {
  *MemToShadow(addr) = 0; /* clear shadow: it is a valid memory */
}


void __asan_init(void) {
  for(int i=0; i<sizeof(shadow); i++) {
    shadow[i] = 0; /* unpoisoned  */
  }
  /* because the shadow is part of the memory area: poison the shadow */
  for(int i=0; i<sizeof(shadow); i+=8) {
    PoisonShadow(&shadow[i]);
  }
}

static bool SlowPathCheck(uint8_t shadow_value, void *address, size_t kAccessSize) {
  uint8_t last_accessed_byte = (((uint32_t)address) & 7) + kAccessSize - 1;
  return (last_accessed_byte >= shadow_value);
}

static void ReportError(void *address, size_t kAccessSize, rw_mode_e mode) {
  __asan_ReportGenericError();
}

static void CheckShadow(void *address, size_t kAccessSize, rw_mode_e mode) {
  uint8_t *shadow_address;
  uint8_t shadow_value;

  shadow_address = MemToShadow(address);
  shadow_value = *shadow_address;
  if (shadow_value!=0) { /* fast check: poisoned! */
    if (SlowPathCheck(shadow_value, address, kAccessSize)) {
      ReportError(address, kAccessSize, mode);
    }
  }
}

void __asan_load4_noabort(void *address) {
  CheckShadow(address, 4, kIsRead);
}

void __asan_store4_noabort(void *address) {
  CheckShadow(address, 4, kIsWrite);
}

#define ASAN_MALLOC_RED_ZONE_BORDER  (8)
/*
 * rrrrrrr  red zone border (inkl. size below)
 * size
 * memory returned
 * rrrrrrrrrrr  red zone boarder
 */

void *__asan_malloc(size_t size) {
  /* malloc allocates the requested amount of memory with redzones around it.
   * The shadow values corresponding to the redzones are poisoned and the shadow values
   * for the memory region are cleared.
   */
  void *p = malloc(size+2*ASAN_MALLOC_RED_ZONE_BORDER);
  void *q;

  q = p;
  /* poison red zone at the beginning */
  for(int i=0; i<ASAN_MALLOC_RED_ZONE_BORDER; i++) {
    PoisonShadow(q);
    q++;
  }
  *((size_t*)q) = size; /* store memory size, needed for the free() part */
  /* clear valid memory */
  for(int i=0; i<size; i++) {
    ClearShadow(q);
    q++;
  }
  /* poison red zone at the end */
  for(int i=0; i<ASAN_MALLOC_RED_ZONE_BORDER; i++) {
    PoisonShadow(q);
    q++;
  }
  return p+ASAN_MALLOC_RED_ZONE_BORDER;
}

void __asan_free(void *p) {
  /* free poisons shadow values for the entire region and puts the chunk of memory into a quarantine queue
   * (such that this chunk will not be returned again by malloc during some period of time).
   */
  free(p-ASAN_MALLOC_RED_ZONE_BORDER);
}

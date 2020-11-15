/*
 * Copyright 2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TX_USER_H
#define TX_USER_H

#if defined (__MCUXPRESSO)

extern char _vStackBase;
extern char _pvHeapLimit;

#define GET_UNUSED_MEM_SIZE() (&_vStackBase - &_pvHeapLimit)

#elif defined(__ICCARM__)

#pragma section="HEAP"
#pragma section="CSTACK"

#define _StackBase ((unsigned int)__sfb("CSTACK"))
#define _HeapLimit ((unsigned int)__sfe("HEAP"))
#define GET_UNUSED_MEM_SIZE() (_StackBase - _HeapLimit)

#else

extern char __StackLimit;
extern char __HeapLimit;

#define GET_UNUSED_MEM_SIZE() (&__StackLimit - &__HeapLimit)

#endif

#define TX_ENABLE_FPU_SUPPORT

//#define TX_MAX_PRIORITIES                       32

//#define TX_MINIMUM_STACK

//#define TX_THREAD_USER_EXTENSION

//#define TX_TIMER_THREAD_STACK_SIZE

//#define TX_TIMER_THREAD_PRIORITY

//#define TX_TIMER_PROCESS_IN_ISR

//#define TX_REACTIVATE_INLINE

//#define TX_DISABLE_STACK_FILLING

//#define TX_ENABLE_STACK_CHECKING

//#define TX_DISABLE_PREEMPTION_THRESHOLD

//#define TX_DISABLE_REDUNDANT_CLEARING

//#define TX_NO_TIMER

//#define TX_DISABLE_NOTIFY_CALLBACKS

//#define TX_INLINE_THREAD_RESUME_SUSPEND

//#define TX_NOT_INTERRUPTABLE

//#define TX_ENABLE_EVENT_TRACE

//#define TX_BLOCK_POOL_ENABLE_PERFORMANCE_INFO

//#define TX_BYTE_POOL_ENABLE_PERFORMANCE_INFO

//#define TX_EVENT_FLAGS_ENABLE_PERFORMANCE_INFO

//#define TX_MUTEX_ENABLE_PERFORMANCE_INFO

//#define TX_QUEUE_ENABLE_PERFORMANCE_INFO

//#define TX_SEMAPHORE_ENABLE_PERFORMANCE_INFO

//#define TX_THREAD_ENABLE_PERFORMANCE_INFO

//#define TX_TIMER_ENABLE_PERFORMANCE_INFO

//#define TX_TIMER_TICKS_PER_SECOND 100
#endif

//*****************************************************************************
//
// Copyright (c) 2009-2012 Code Red Technologies Ltd.
// Copyright 2013, 2019, 2023 NXP
// All rights reserved.
//
// SPDX-License-Identifier: BSD-3-Clause
//
// Minimal implementations of the new/delete operators and the verbose 
// terminate handler for exceptions suitable for embedded use,
// plus optional "null" stubs for malloc/free (only used if symbol
// CPP_NO_HEAP is defined).
//
//*****************************************************************************

#include <stdlib.h>

void *operator new(size_t size)
{
    return malloc(size);
}

void *operator new[](size_t size)
{
    return malloc(size);
}

void operator delete(void *p)
{
    free(p);
}

void operator delete[](void *p)
{
    free(p);
}

extern "C" int __aeabi_atexit(void *object,
		void (*destructor)(void *),
		void *dso_handle)
{
	return 0;
}

#ifdef CPP_NO_HEAP
extern "C" void *malloc(size_t) {
	return (void *)0;
}

extern "C" void free(void *) {
}
#endif

#ifndef CPP_USE_CPPLIBRARY_TERMINATE_HANDLER
/******************************************************************
 * __verbose_terminate_handler()
 *
 * This is the function that is called when an uncaught C++
 * exception is encountered. The default version within the C++
 * library prints the name of the uncaught exception, but to do so
 * it must demangle its name - which causes a large amount of code
 * to be pulled in. The below minimal implementation can reduce
 * code size noticeably. Note that this function should not return.
 ******************************************************************/
namespace __gnu_cxx {
void __verbose_terminate_handler()
{
  while(1);
}
}
#endif

/*
 * This file is part of the xPack project (http://xpack.github.io).
 * Copyright (c) 2021 Liviu Ionescu. All rights reserved.
 *
 * This Software is provided under the terms of the MIT License.
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/MIT/.
 */

// ----------------------------------------------------------------------------

#include "hello-world.h"
#include "add/add.h"

#include <stdio.h>

int
main (int argc, char* argv[])
{
  printf ("%s\n", HELLO_WORLD_MESSAGE);

#if defined(DEBUG)
  printf ("%s\n", "(in debug mode)");
#else
  printf ("%s\n", "(in release mode)");
#endif

#if defined(NDEBUG)
  printf ("%s\n", "(no asserts)");
#endif

  printf ("Check adder lib: 41 + 1 = %d\n", add (41, 1));

  return 0;
}

// ----------------------------------------------------------------------------

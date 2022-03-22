/*
 * test.c
 *
 *  Created on: 22.03.2022
 *      Author: erich
 */

#include "test.h"

static int i = 15;

int test(void)
{
  if (i==15) {
	  return 1;
  } else if (i==10) {
	  return 0;
  }
  return 2;
}

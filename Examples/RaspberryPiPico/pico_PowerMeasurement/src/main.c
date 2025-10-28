/*
 * Copyright (c) 2024-2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
 
#include "platform.h"
#include "application.h"

int main(void) {
   App_Run();
   for(;;) {} /* not not leave main */
   return 0;
}

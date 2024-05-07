/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuRTOS.h"
#include "application.h"

int main(void) {
    APP_Run();
    for(;;) {}
    return 0;
}
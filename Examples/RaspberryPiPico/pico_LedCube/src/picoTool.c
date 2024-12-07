/*
 * Copyright (c) 2022-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "pico/binary_info.h"

void PicoTool_Init(void) {
  bi_decl(bi_program_description("This is a binary for a LED RGB cube."));
//  bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));
}

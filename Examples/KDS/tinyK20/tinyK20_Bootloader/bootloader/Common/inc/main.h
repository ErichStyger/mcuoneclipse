/* CMSIS-DAP Interface Firmware
 * Copyright (c) 2009-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

#if 1 /* << EST moved to main.h */
#include "FreeRTOS.h"
#include "event_groups.h"

#define TRANSFER_FINISHED_SUCCESS       (1 << 0)
#define TRANSFER_FINISHED_FAIL          (1 << 1)

#define MSC_TIMEOUT_SPLIT_FILES_EVENT   (0x1000)
#define MSC_TIMEOUT_START_EVENT         (0x2000)
#define MSC_TIMEOUT_STOP_EVENT          (0x4000)
#define MSC_TIMEOUT_RESTART_EVENT       (0x8000)

#define PROGRAM_PAGE_EVENT              (0x0008)
#define FLASH_INIT_EVENT                (0x0004)

extern EventGroupHandle_t transferEventGroup;

#endif

void main_transfer_finished(uint8_t success);

#endif

/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#include "myBLE.h"
#include "client.h"
#include "server.h"

void BLE_Init(void) {
#if PL_CONFIG_STANDALONE_BLE_TEMP_SENSOR_CLIENT
  Client_Init();
#elif PL_CONFIG_STANDALONE_BLE_TEMP_SENSOR_SERVER
  Server_Init();
#else
  #error"unknown configuration"
#endif
}

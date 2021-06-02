/*
 * Copyright (c) 2020, Erich Styger
  *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BLEMSG_H_
#define BLEMSG_H_

#include "McuRTOS.h"

typedef enum {
  BLE_MSG_TYPE_BUTTON_PRESSED,
  BLE_MSG_TYPE_BUTTON_RELEASED,
  BLE_MSG_TYPE_COLOR_PICKER,
  BLE_MSG_TYPE_ACCELEROMETER,
  BLE_MSG_TYPE_QUATERNION,
  BLE_MSG_TYPE_GYRO,
  BLE_MSG_TYPE_MAGNETOMETER,
  BLE_MSG_TYPE_LOCATION,
} BLE_Msg_e;

typedef struct {
  BLE_Msg_e type;
  union { /* different fields depending on type */
    uint8_t button;
    uint32_t color;
    float accel[3];
    float quaternion[4];
    float gyro[3];
    float magnetometer[3];
    float location[3];
  } u;
} BLE_Msg_t;

/* called from the shell task to handle messages. Return true if there are more in the queue */
bool BLEMSG_HandleMessage(void);

/* called from the BLE task to parse messages, starting with '!' */
bool BLEMSG_RxCallback(const uint8_t *buf);

void BLEMSG_Init(void);

#endif /* BLEMSG_H_ */

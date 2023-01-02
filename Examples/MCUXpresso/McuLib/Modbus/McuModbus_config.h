/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MODBUS_MCUMODBUS_CONFIG_H_
#define MODBUS_MCUMODBUS_CONFIG_H_

#ifndef McuModbus_CONFIG_IS_ENABLED
  #define McuModbus_CONFIG_IS_ENABLED  (0)
    /*!< 0: disabled; 1: enabled  */
#endif

#ifndef McuModbus_CONFIG_RX_TIMEOUT_MS
  #define McuModbus_CONFIG_RX_TIMEOUT_MS  (500)
    /*!< default timeout waiting for an answer from the device */
#endif

#ifndef McuModbus_CONFIG_QUEUE_RX_TIMEOUT_MS
  #define McuModbus_CONFIG_QUEUE_RX_TIMEOUT_MS  (10)
    /*!< default timeout waiting for a queue element from the RX interrupt */
#endif

#ifndef McuModbus_CONFIG_BUS_WAIT_TIME_MS
  #define McuModbus_CONFIG_BUS_WAIT_TIME_MS  (15)
    /*!< forced waiting time after a bus transfer */
#endif

#ifndef McuModbus_CONFIG_USE_MUTEX
  #define McuModbus_CONFIG_USE_MUTEX  (1)
    /*!< 1: use a mutex to access the bus; 0: no mutex used */
#endif

#endif /* MODBUS_MCUMODBUS_CONFIG_H_ */

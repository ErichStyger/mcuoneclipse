/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef CDC_VIRTUAL_COM_CONFIG_H_
#define CDC_VIRTUAL_COM_CONFIG_H_

#ifndef VIRTUAL_COM_CONFIG_RX_RINGBUF_SIZE
  #define VIRTUAL_COM_CONFIG_RX_RINGBUF_SIZE  (256)
    /*!< size of the rx ring buffer, effective buffer is this size multiply by DATA_BUFF_SIZE! */
#endif

#ifndef VIRTUAL_COM_CONFIG_TX_RINGBUF_SIZE
  #define VIRTUAL_COM_CONFIG_TX_RINGBUF_SIZE  (256)
    /*!< size of the Tx ring buffer, effective buffer is this size multiply by DATA_BUFF_SIZE! */
#endif

#ifndef VIRTUAL_COM_CONFIG_TASK_PRIORITY
  #define VIRTUAL_COM_CONFIG_TASK_PRIORITY  (tskIDLE_PRIORITY+5)
    /*!< FreeRTOS Task priority */
#endif

#ifndef VIRTUAL_COM_CONFIG_TASK_STACK_SIZE
  #define VIRTUAL_COM_CONFIG_TASK_STACK_SIZE  (600/sizeof(StackType_t))
    /*!< FreeRTOS Task stack size */
#endif

#ifndef VIRTUAL_COM_CONFIG_TASK_DELAY_MS
  #define VIRTUAL_COM_CONFIG_TASK_DELAY_MS  (5)
    /*!< FreeRTOS Task delay/waiting time */
#endif

#endif /* CDC_VIRTUAL_COM_CONFIG_H_ */

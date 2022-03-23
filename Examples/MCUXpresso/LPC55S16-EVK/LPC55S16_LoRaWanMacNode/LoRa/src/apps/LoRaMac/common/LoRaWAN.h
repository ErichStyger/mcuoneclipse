/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FREERTOS_LORAWAN_H_
#define FREERTOS_LORAWAN_H_

#include <stdint.h>

/* Task notification values */
#define LORAWAN_NOTIFICATION_EVENT_LMHANDLER     (1<<0) /* LmHandlerProcess */
#define LORAWAN_NOTIFICATION_EVENT_MAC_PENDING   (1<<1) /* MAC process pending */
#define LORAWAN_NOTIFICATION_EVENT_TX_REQUEST    (1<<2) /* request to send data */

/*!
 * \brief Notify LoRaWAN task to process messages and events
 */
void LORAWAN_LmHandlerNotififyTaskRequest(uint32_t event);

/*!
 * \brief Module initialization
 */
void LoRaWAN_Init(void);

#endif /* FREERTOS_LORAWAN_H_ */

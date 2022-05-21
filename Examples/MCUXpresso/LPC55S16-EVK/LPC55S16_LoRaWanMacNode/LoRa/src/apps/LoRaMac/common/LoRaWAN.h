/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FREERTOS_LORAWAN_H_
#define FREERTOS_LORAWAN_H_

#include <stdint.h>
#include <stdbool.h>

/* Task notification values */
#define LORAWAN_NOTIFICATION_EVENT_LMHANDLER     (1<<0) /* LmHandlerProcess */
#define LORAWAN_NOTIFICATION_EVENT_MAC_PENDING   (1<<1) /* MAC process pending */
#define LORAWAN_NOTIFICATION_EVENT_TX_REQUEST    (1<<2) /* request to send data */
#define LORAWAN_NOTIFICATION_EVENT_WAKEUP        (1<<3) /* wakeup event */

/*!
 * \brief Notify LoRaWAN task to process messages and events
 */
void LORAWAN_LmHandlerNotififyTaskRequest(uint32_t event);

#include "McuShell.h"
uint8_t LORAWAN_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

bool LORAWAN_StartUplink(void);
bool LORAWAN_StartJoin(void);

/*!
 * \brief Module initialization
 */
void LoRaWAN_Init(void);

#endif /* FREERTOS_LORAWAN_H_ */

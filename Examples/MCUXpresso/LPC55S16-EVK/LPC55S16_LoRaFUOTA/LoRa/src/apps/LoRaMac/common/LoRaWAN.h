/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FREERTOS_LORAWAN_H_
#define FREERTOS_LORAWAN_H_

/*!
 * \brief Notify LoRaWAN task to process messages and events
 */
void LORAWAN_LmHandlerNotififyTaskRequest(void);

/*!
 * \brief Module initialization
 */
void LoRaWAN_Init(void);

#endif /* FREERTOS_LORAWAN_H_ */

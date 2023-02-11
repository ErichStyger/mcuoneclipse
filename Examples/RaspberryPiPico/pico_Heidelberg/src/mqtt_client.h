/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SRC_MQTT_CLIENT_H_
#define SRC_MQTT_CLIENT_H_

/*!
 *
 */
void MqttClient_Connect(void);

/*!
 * \brief Module de-initialization
 */
void MqttClient_Deinit(void);

/*!
 * \brief Module initialization
 */
void MqttClient_Init(void);

#endif /* SRC_MQTT_CLIENT_H_ */

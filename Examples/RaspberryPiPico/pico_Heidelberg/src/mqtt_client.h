/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SRC_MQTT_CLIENT_H_
#define SRC_MQTT_CLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif

/* which topics to use: choose only one: */
#define MQTT_CLIENT_IS_EV_CHARGER    (1)
#define MQTT_CLIENT_IS_SENSOR        (0)

#if PL_CONFIG_USE_SHELL
  #include "McuShell.h"

  /*!
   * \brief Command line and shell handler
   * \param cmd The command to be parsed
   * \param handled If command has been recognized and handled
   * \param io I/O handler to be used
   * \return error code, otherwise ERR_OK
   */
  uint8_t MqttClient_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif

#if MQTT_CLIENT_IS_SENSOR
  int MqttClient_Publish_SensorValues(float temperature, float humidity);
#endif

#if MQTT_CLIENT_IS_EV_CHARGER
  int MqttClient_Publish_ChargingPower(uint32_t powerW);
#endif

/*!
 * \brief Connect as client to the server
 * \return error code, otherwise ERR_OK
 */
uint8_t MqttClient_Connect(void);

/*!
 * \brief Disconnect from the server
 * \return error code, otherwise ERR_OK
 */
uint8_t MqttClient_Disconnect(void);

/*!
 * \brief Decides if client is set to publish or not
 * \return true if client is publishing, false otherwise
 */
bool MqttClient_GetDoPublish(void);

/*!
 * \brief Sets if the client is publishing or not
 * \param publish true to publish, false otherwise
 */
void MqttClient_SetDoPublish(bool publish);

/*!
 * \brief Module de-initialization
 */
void MqttClient_Deinit(void);

/*!
 * \brief Module initialization
 */
void MqttClient_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SRC_MQTT_CLIENT_H_ */

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

#include "mqtt_client_config.h"

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

typedef void *mqtt_client_handle;  /* is actually a pointer to mqtt_client_s */
typedef const void *mqtt_connect_client_info_handle;  /* is actually a pointer to const struct mqtt_connect_client_info_t */

void mqtt_subscribeTopic(mqtt_client_handle client, mqtt_connect_client_info_handle client_info, const char *topic);

/*!
 * \brief Returns the current MQTT client handle
 * \return MQTT client handle
 */
mqtt_client_handle mqtt_getClient(void);

/*!
 * \brief Getter for the current logging mode
 * \return true if logging is enabled, false otherwise
 */
bool mqtt_doLogging(void);

/*!
 * \brief Set the incoming topic ID
*/
void mqtt_set_in_pub_ID(int id);

/*!
 * \brief GEt the incoming topic ID
 * \return ID
*/
int mqtt_get_in_pub_ID(void);

/*!
 * \brief Copy the MQTT data string with a given length into a buffer and zero terminates it.
 * \param [out] buf Buffer, where to store the data
 * \param [in] bufSize Size of the buffer in bytes
 * \param [in] data MQTT data
 * \param [in] len Number of bytes in data
*/
void MqttClient_GetDataString(unsigned char *buf, size_t bufSize, const uint8_t *data, uint16_t len);

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
 * \brief Decides if client can publish or not
 * \return true if client is publishing, false otherwise
 */
bool MqttClient_CanPublish(void);

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

/*
 * ESP8266.h
 *
 *      Author: Erich Styger
 */

#ifndef ESP8266_H_
#define ESP8266_H_

#include "CLS1.h"

#define ESP_DEFAULT_TIMEOUT_MS    (100)
  /*!< Default timeout value in milliseconds */

/*!
 * \brief Command line parser routine
 * \param cmd Pointer to command line string
 * \param handled Return value if command has been handled
 * \param io Standard Shell I/O handler
 * \return Error code, ERR_OK for no failure
 */
uint8_t ESP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

/*!
 * \brief Send a string to th ESP8266 module
 * \param str String to send, "\r\n" will be appended
 * \param io Shell I/O handler or NULL if not used
 * \return Error code, ERR_OK for no failure
 */
uint8_t ESP_SendStr(const uint8_t *str, CLS1_ConstStdIOType *io);

/*!
 * \brief Used to send an AT command to the ESP8266 module
 * \param cmd Command string to send
 * \param rxBuf Buffer for the response, can be NULL
 * \param rxBufSize Size of response buffer
 * \param expectedTailStr Expected response from the module, can be NULL
 * \param msTimeout Timeout time in milliseconds
 * \param io Shell I/O handler or NULL if not used
 * \return Error code, ERR_OK for no failure
 */
uint8_t ESP_SendATCommand(uint8_t *cmd, uint8_t *rxBuf, size_t rxBufSize, uint8_t *expectedTailStr, uint16_t msTimeout, const CLS1_StdIOType *io);

/*!
 * \brief Read from the serial line from the module until a sentinel char is received
 * \param buf
 * \param bufSize
 * \param sentinelChar
 * \param timeoutMs Timeout time in milliseconds
 * \return Error code, ERR_OK for no failure
 */
uint8_t ESP_ReadCharsUntil(uint8_t *buf, size_t bufSize, uint8_t sentinelChar, uint16_t timeoutMs);

/*!
 * \brief Sends an AT command to test the connection
 * \return Error code, ERR_OK for no failure
 */
uint8_t ESP_TestAT(void);

/*!
 * \brief Restarts the ESP8266 module
 * \param io Shell I/O handler or NULL if not used
 * \param timeoutMs Timeout time in milliseconds
 * \return Error code, ERR_OK for no failure
 */
uint8_t ESP_Restart(const CLS1_StdIOType *io, uint16_t timeoutMs);

/*!
 * \brief Set the current mode of the module
 * \param mode Where <mode> is 1=Sta, 2=AP or 3=both
 * \return Error code, ERR_OK for no failure
 */
uint8_t ESP_SelectMode(uint8_t mode);

/*!
 * \Brief returns the firmware version string
 * \param fwBuf Buffer for the string
 * \param fwBufSize Size of buffer in bytes
 * \return Error code, ERR_OK for no failure
 */
uint8_t ESP_GetFirmwareVersionString(uint8_t *fwBuf, size_t fwBufSize);

/*!
 * \brief Join an access point.
 * \param ssid SSID of access point
 * \param pwd Password of access point
 * \param nofRetries Number of connection retries
 * \param io Shell I/O or NULL if not used
 * \return Error code, ERR_OK for no failure
 */
uint8_t ESP_JoinAP(const uint8_t *ssid, const uint8_t *pwd, int nofRetries, CLS1_ConstStdIOType *io);

/*!
 * \brief Scans for an IPD message sent by the module
 * \param msgBuf Pointer to the message buffer where to store the message
 * \param msgBufSize Size of message buffer
 * \param ch_id Pointer to where to store the channel/id
 * \param size Pointer where to store the size of the message
 * \param isGet TRUE if it is a GET message, FALSE for a POST message
 * \param timeoutMs Error code, ERR_OK for no failure
 * \param io
 * \return Error code, ERR_OK for no failure
 */
uint8_t ESP_GetIPD(uint8_t *msgBuf, size_t msgBufSize, uint8_t *ch_id, uint16_t *size, bool *isGet, uint16_t timeoutMs, const CLS1_StdIOType *io);

/*!
 * \brief Closes a connection
 * \param channel Channel ID
 * \param io Error code, ERR_OK for no failure
 * \param timeoutMs Error code, ERR_OK for no failure
 * \return Error code, ERR_OK for no failure
 */
uint8_t ESP_CloseConnection(uint8_t channel, const CLS1_StdIOType *io, uint16_t timeoutMs);

/*!
 * \brief Used to determine if the web server is running or not.
 * \return TRUE if web server has beens started
 */
bool ESP_IsServerOn(void);

/*!
 * \brief Driver initialization
 */
void ESP_Init(void);

/*!
 * \brief Driver de-initialization
 */
void ESP_Deinit(void);

#endif /* ESP8266_H_ */

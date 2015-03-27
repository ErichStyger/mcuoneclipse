/**
 * \file
 * \brief Interface to the DHT11 temperature/humidity sensor.
 * \author Erich Styger
 */

#ifndef DHT11_H_
#define DHT11_H_

#include "PE_Types.h"

/*! Error codes */
typedef enum {
  DHT11_OK, /*!< OK */
  DHT11_NO_PULLUP, /*!< no pullup present */
  DHT11_NO_ACK_0, /*!< no 0 acknowledge detected */
  DHT11_NO_ACK_1, /*!< no 1 acknowledge detected */
  DHT11_NO_DATA_0, /*!< low level expected during data transmission */
  DHT11_NO_DATA_1, /*!< high level expected during data transmission */
  DHT11_BAD_CRC,   /*!< bad CRC */
} DHT11_ErrorCode;

/*!
 * \brief Returns for a given error code the description string.
 * \param code Error Code
 * \return Error code description string
 */
const unsigned char* DHT1_GetReturnCodeString(DHT11_ErrorCode code);

/*!
 * \brief Reads the sensor data values
 * \param temperatureCentigrade Temperature value, in 1/100 units. E.g. 1517 is 15.17°C
 * \param humidityCentipercent Humidity value, in 1/100 units. E.g. 3756 is 37.56%
 * \return Error code
 */
DHT11_ErrorCode DHT11_Read(uint16_t *temperatureCentigrade, uint16_t *humidityCentipercent);

#endif /* DHT11_H_ */

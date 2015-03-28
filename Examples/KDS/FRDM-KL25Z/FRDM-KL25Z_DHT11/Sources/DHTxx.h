/**
 * \file
 * \brief Interface to the DHT11/DHT22 temperature/humidity sensor.
 * \author Erich Styger
 */

#ifndef DHTxx_H_
#define DHTxx_H_

#include "PE_Types.h"

/* either one of the defines below needs to be set to 1: */
#define DHTxx_SENSOR_TYPE_IS_DHT11  (1)
  /*!< Sensor is DHT11_SENSOR_DHT22 */
#define DHTxx_SENSOR_TYPE_IS_DHT22  (0)
  /*!< Sensor is DHT11_SENSOR_DHT22 */

#if DHTxx_SENSOR_TYPE_IS_DHT11
  #define DHTxx_SENSOR_PERIOD_MS    1000
    /*!< can only read sensor values with 1 Hz! */
#elif DHTxx_SENSOR_TYPE==DHTxx_SENSOR_DHT22
  #define DHTxx_SENSOR_PERIOD_MS    2000
    /*!< can only read sensor values with 0.5 Hz! */
#else
  #error "unknown device!"
#endif

/*! Error codes */
typedef enum {
  DHTxx_OK, /*!< OK */
  DHTxx_NO_PULLUP, /*!< no pull-up present */
  DHTxx_NO_ACK_0, /*!< no 0 acknowledge detected */
  DHTxx_NO_ACK_1, /*!< no 1 acknowledge detected */
  DHTxx_NO_DATA_0, /*!< low level expected during data transmission */
  DHTxx_NO_DATA_1, /*!< high level expected during data transmission */
  DHTxx_BAD_CRC,   /*!< bad CRC */
} DHTxx_ErrorCode;

/*!
 * \brief Returns for a given error code the description string.
 * \param code Error Code
 * \return Error code description string
 */
const unsigned char *DHTxx_GetReturnCodeString(DHTxx_ErrorCode code);

/*!
 * \brief Reads the sensor data values
 * \param temperatureCentigrade Temperature value, in 1/100 units. E.g. 1517 is 15.17°C
 * \param humidityCentipercent Humidity value, in 1/100 units. E.g. 3756 is 37.56%
 * \return Error code
 */
DHTxx_ErrorCode DHTxx_Read(uint16_t *temperatureCentigrade, uint16_t *humidityCentipercent);

#endif /* DHTxx_H_ */

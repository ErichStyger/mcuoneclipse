/*
 / _____)             _              | |
 ( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
 (______/|_____)_|_|_| \__)_____)\____)_| |_|
 (C)2013 Semtech

 Description: Generic driver for the GPS receiver UP501

 License: Revised BSD License, see LICENSE.TXT file include in the project

 Maintainer: Miguel Luis and Gregory Cristian
 */
#ifndef __GPS_H__
#define __GPS_H__

/* Structure to handle the GPS parsed data in ASCII */
typedef struct {
    char NmeaDataType[6];
    char NmeaUtcTime[11];
    char NmeaDataStatus[2];
    char NmeaLatitude[10];
    char NmeaLatitudePole[2];
    char NmeaLongitude[11];
    char NmeaLongitudePole[2];
    char NmeaFixQuality[2];
    char NmeaSatelliteTracked[3];
    char NmeaHorizontalDilution[6];
    char NmeaAltitude[8];
    char NmeaAltitudeUnit[2];
    char NmeaHeightGeoid[8];
    char NmeaHeightGeoidUnit[2];
    char NmeaSpeed[8];
    char NmeaDetectionAngle[8];
    char NmeaDate[8];
} tNmeaGpsData;

typedef struct {
    unsigned char second;   // 0-59
    unsigned char minute;   // 0-59
    unsigned char hour;   // 0-23
    unsigned char day;    // 1-31
    unsigned char month;   // 1-12
    unsigned char year;   // 0-99 (representing 2000-2099)
} datetime_t;

extern tNmeaGpsData NmeaGpsData;

/*!
 * \brief Initializes the handling of the GPS receiver
 */
void GpsInit( void );

/*!
 * \brief PPS signal handling function
 */
void GpsPpsHandler( bool *parseData );

/*!
 * \brief PPS signal handling function
 *
 * \retval ppsDetected State of PPS signal.
 */
bool GpsGetPpsDetectedState( void );

/*!
 * \brief Indicates if GPS has fix
 *
 * \retval hasFix
 */
bool GpsHasFix( void );

/*!
 * \brief Indicates if GPS has a valid datetime
 *
 * \retval has valid datetime
 */
bool GpsHasValidDateTime( void );

/*!
 * \brief Converts the latest Position (latitude and longitude) into a binary
 *        number
 */
void GpsConvertPositionIntoBinary( void );

/*!
 * \brief Converts the latest Position (latitude and Longitude) from ASCII into
 *        DMS numerical format
 */
void GpsConvertPositionFromStringToNumerical( void );

/*!
 * \brief Get current unix time
 *
 * \retval unixTime Current unix time
 */
time_t GpsGetCurrentUnixTime( void );

/*!
 * \brief Gets the latest Position (latitude and Longitude) as two double values
 *        if available
 *
 * \param [OUT] lati Latitude value
 * \param [OUT] longi Longitude value
 *
 * \retval status [SUCCESS, FAIL]
 */
uint8_t GpsGetLatestGpsPositionDouble( double *lati, double *longi );

/*!
 * \brief Gets the latest Position (latitude and Longitude) as two binary values
 *        if available
 *
 * \param [OUT] latiBin Latitude value
 * \param [OUT] longiBin Longitude value
 *
 * \retval status [SUCCESS, FAIL]
 */
uint8_t GpsGetLatestGpsPositionBinary( int32_t *latiBin, int32_t *longiBin );

/*!
 * \brief Calculates the distance between the latest position and the specified
 *        location.
 *
 * \param[IN] latiBin Latitude value
 * \param[IN] longiBin Longitude value
 * \param[OUT] distance Calculated distance
 *
 * \retval status [SUCCESS, FAIL]
 */
uint8_t GpsGetDistanceToLatestGpsPositionBinary( int32_t latiBin, int32_t longiBin,
        uint32_t *distance );

/*!
 * \brief Parses the NMEA sentence.
 *
 * \remark Only parses GPGGA and GPRMC sentences
 *
 * \param [IN] rxBuffer Data buffer to be parsed
 * \param [IN] rxBufferSize Size of data buffer
 *
 * \retval status [SUCCESS, FAIL]
 */
uint8_t GpsParseGpsData( char *rxBuffer, size_t rxBufferSize );

/*!
 * \brief Returns the latest altitude from the parsed NMEA sentence
 *
 * \retval altitude
 */
uint16_t GpsGetLatestGpsAltitude( void );

/*!
 * \brief Gets the latest Vector track (ground speed and track) if available
 *
 * \param [OUT] groundSpeed Ground speed
 * \param [OUT] track Direction
 *
 * \retval status [SUCCESS, FAIL]
 */
uint8_t GpsGetLatestTrack( uint16_t *groundSpeed, uint16_t *track );

/*!
 * \brief Format GPS data into numeric and binary formats
 */
void GpsFormatGpsData( void );

/*!
 * \brief Resets the GPS position variables
 */
void GpsResetPosition( void );

#endif  // __GPS_H__

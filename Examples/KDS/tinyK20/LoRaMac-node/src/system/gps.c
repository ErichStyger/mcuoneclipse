/*
 / _____)             _              | |
 ( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
 (______/|_____)_|_|_| \__)_____)\____)_| |_|
 (C)2013 Semtech

 Description: Generic driver for any GPS receiver

 License: Revised BSD License, see LICENSE.TXT file include in the project

 Maintainer: Miguel Luis and Gregory Cristian
 */
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "board.h"
#include "gps.h"
#if defined(USE_LORA_MESH)
#include "LoRaMesh.h"
#endif

#define LOG_LEVEL_ERROR
#include "debug.h"

#define TRIGGER_GPS_CNT                             10

/* Various type of NMEA data we can receive with the Gps */
const char NmeaDataTypeGPGGA[] = "GPGGA";
const char NmeaDataTypeGPGSA[] = "GPGSA";
const char NmeaDataTypeGPGSV[] = "GPGSV";
const char NmeaDataTypeGPRMC[] = "GPRMC";

/* Value used for the conversion of the position from DMS to decimal */
const int32_t MaxNorthPosition = 8388607;       // 2^23 - 1
const int32_t MaxSouthPosition = 8388608;       // -2^23
const int32_t MaxEastPosition = 8388607;        // 2^23 - 1    
const int32_t MaxWestPosition = 8388608;        // -2^23

tNmeaGpsData NmeaGpsData;

static double Latitude = 0;
static double Longitude = 0;

static int32_t LatitudeBinary = 0;
static int32_t LongitudeBinary = 0;
static uint16_t GroundSpeedBinary = 0;
static uint16_t TrackBinary = 0;
static uint16_t AltitudeBinary = 0xFFFF;

static uint32_t PpsCnt = 0;

static time_t gpsUnixTime;

static bool bGpsHasFix = false;
static bool bGpsHasValidDateTime = false;
static bool PpsDetected = false;

void GpsPpsHandler( bool *parseData )
{
    PpsDetected = true;
    PpsCnt++;
    gpsUnixTime++;
    *parseData = false;

#if defined(USE_LORA_MESH)
    if ( bGpsHasFix && bGpsHasValidDateTime ) {
        LoRaMesh_TimeSynch(gpsUnixTime);
    }
#endif

    if ( PpsCnt >= TRIGGER_GPS_CNT ) {
        PpsCnt = 0;
        BlockLowPowerDuringTask(true);
        *parseData = true;
    }
}

void GpsInit( void )
{
    PpsDetected = false;
    gpsUnixTime = 0u;

    /* Reset datetime to make sure it is current */
    for ( uint8_t i = 0; i < 11; i++ ) {
        NmeaGpsData.NmeaUtcTime[i] = 0x00u;
        if ( i < 8 ) {
            NmeaGpsData.NmeaDate[i] = 0x00u;
        }
    }

    GpsMcuInit();
}

bool GpsGetPpsDetectedState( void )
{
    bool state = false;

    __disable_irq();
    state = PpsDetected;
    PpsDetected = false;
    __enable_irq();
    return state;
}

bool GpsHasFix( void )
{
    return bGpsHasFix;
}

bool GpsHasValidDateTime( void )
{
    return bGpsHasValidDateTime;
}

bool GpsValidateDateTime( struct tm *dt )
{
    if ( NmeaGpsData.NmeaUtcTime[0] > '2' || NmeaGpsData.NmeaUtcTime[0] < '0' ) {
        return false;
    } else if ( NmeaGpsData.NmeaUtcTime[1] > '9' || NmeaGpsData.NmeaUtcTime[1] < '0' ) {
        return false;
    } else if ( NmeaGpsData.NmeaUtcTime[2] > '6' || NmeaGpsData.NmeaUtcTime[2] < '0' ) {
        return false;
    } else if ( NmeaGpsData.NmeaUtcTime[3] > '9' || NmeaGpsData.NmeaUtcTime[3] < '0' ) {
        return false;
    } else if ( NmeaGpsData.NmeaUtcTime[4] > '6' || NmeaGpsData.NmeaUtcTime[4] < '0' ) {
        return false;
    } else if ( NmeaGpsData.NmeaUtcTime[5] > '9' || NmeaGpsData.NmeaUtcTime[5] < '0' ) {
        return false;
    } else if ( NmeaGpsData.NmeaDate[0] > '3' || NmeaGpsData.NmeaDate[0] < '0' ) {
        return false;
    } else if ( NmeaGpsData.NmeaDate[1] > '9' || NmeaGpsData.NmeaDate[1] < '0' ) {
        return false;
    } else if ( NmeaGpsData.NmeaDate[2] > '1' || NmeaGpsData.NmeaDate[2] < '0' ) {
        return false;
    } else if ( NmeaGpsData.NmeaDate[3] > '9' || NmeaGpsData.NmeaDate[3] < '0' ) {
        return false;
    } else if ( NmeaGpsData.NmeaDate[4] > '9' || NmeaGpsData.NmeaDate[4] < '0' ) {
        return false;
    } else if ( NmeaGpsData.NmeaDate[5] > '9' || NmeaGpsData.NmeaDate[5] < '0' ) {
        return false;
    }

    /* Valid datetime */
    dt->tm_hour = ((NmeaGpsData.NmeaUtcTime[0] - 0x30) * 10) + (NmeaGpsData.NmeaUtcTime[1] - 0x30);
    dt->tm_min = ((NmeaGpsData.NmeaUtcTime[2] - 0x30) * 10) + (NmeaGpsData.NmeaUtcTime[3] - 0x30);
    dt->tm_sec = ((NmeaGpsData.NmeaUtcTime[4] - 0x30) * 10) + (NmeaGpsData.NmeaUtcTime[5] - 0x30);
    dt->tm_mday = ((NmeaGpsData.NmeaDate[0] - 0x30) * 10) + (NmeaGpsData.NmeaDate[1] - 0x30);
    dt->tm_mon = ((NmeaGpsData.NmeaDate[2] - 0x30) * 10) + (NmeaGpsData.NmeaDate[3] - 0x30) - 1;
    dt->tm_year = (2000 - 1900) + ((NmeaGpsData.NmeaDate[4] - 0x30) * 10)
            + (NmeaGpsData.NmeaDate[5] - 0x30);
    dt->tm_isdst = -1;

    return true;
}

void GpsConvertPositionIntoBinary( void )
{
#if 1
    int32_t valueTmp1, valueTmp2;
    uint16_t i;

    valueTmp1 = (NmeaGpsData.NmeaLatitude[0] * 10 + NmeaGpsData.NmeaLatitude[1]) * 10000000;
    valueTmp1 += (NmeaGpsData.NmeaLatitude[2] * 10 + NmeaGpsData.NmeaLatitude[3]) * 100000;
    valueTmp1 += (NmeaGpsData.NmeaLatitude[5] * 1000 + NmeaGpsData.NmeaLatitude[6] * 100
            + NmeaGpsData.NmeaLatitude[7] * 10 + NmeaGpsData.NmeaLatitude[8]);

    LatitudeBinary = valueTmp1;

    if ( NmeaGpsData.NmeaLatitudePole[0] == 'S' ) {
        LatitudeBinary *= -1;
    }

    valueTmp2 = (NmeaGpsData.NmeaLongitude[0] * 100 + NmeaGpsData.NmeaLongitude[1] * 10
            + NmeaGpsData.NmeaLongitude[2]) * 1000000;
    valueTmp2 += (NmeaGpsData.NmeaLongitude[3] * 10 + NmeaGpsData.NmeaLongitude[4]) * 10000;
    valueTmp2 += (NmeaGpsData.NmeaLongitude[6] * 1000 + NmeaGpsData.NmeaLongitude[7] * 100
            + NmeaGpsData.NmeaLongitude[8] * 10 + NmeaGpsData.NmeaLongitude[9]);

    LongitudeBinary = valueTmp2;

    if ( NmeaGpsData.NmeaLongitudePole[0] == 'W' ) {
        LongitudeBinary *= -1;
    }

    // Convert the altitude from ASCII to uint8_t values
    for ( i = 0; i < 8; i++ ) {
        NmeaGpsData.NmeaAltitude[i] = NmeaGpsData.NmeaAltitude[i] & 0xF;
    }

    AltitudeBinary = (NmeaGpsData.NmeaAltitude[0] * 1000) + (NmeaGpsData.NmeaAltitude[1] * 100)
            + (NmeaGpsData.NmeaAltitude[2] * 10) + (NmeaGpsData.NmeaAltitude[4]);

    // Convert the ground speed from ASCII to uint8_t values
    for ( i = 0; i < 8; i++ ) {
        NmeaGpsData.NmeaSpeed[i] = NmeaGpsData.NmeaSpeed[i] & 0xF;
    }

    GroundSpeedBinary = (NmeaGpsData.NmeaSpeed[0] * 100) + (NmeaGpsData.NmeaSpeed[2] * 10)
            + (NmeaGpsData.NmeaSpeed[3]);

    // Convert the detection angle from ASCII to uint8_t values
    for ( i = 0; i < 8; i++ ) {
        NmeaGpsData.NmeaDetectionAngle[i] = NmeaGpsData.NmeaDetectionAngle[i] & 0xF;
    }

    TrackBinary = (NmeaGpsData.NmeaDetectionAngle[0] * 10000)
            + (NmeaGpsData.NmeaDetectionAngle[1] * 1000) + (NmeaGpsData.NmeaDetectionAngle[2] * 100)
            + (NmeaGpsData.NmeaDetectionAngle[4] * 10) + (NmeaGpsData.NmeaDetectionAngle[5]);

#else
    long double temp;

    if ( Latitude >= 0 )   // North
    {
        temp = Latitude * MaxNorthPosition;
        LatitudeBinary = temp / 90;
    } else                // South
    {
        temp = Latitude * MaxSouthPosition;
        LatitudeBinary = temp / 90;
    }

    if ( Longitude >= 0 )   // East
    {
        temp = Longitude * MaxEastPosition;
        LongitudeBinary = temp / 180;
    } else                // West
    {
        temp = Longitude * MaxWestPosition;
        LongitudeBinary = temp / 180;
    }
#endif
}

void GpsConvertUnixTimeFromStringToNumerical( void )
{
    struct tm dateTime;

    if ( GpsValidateDateTime(&dateTime) ) {
        gpsUnixTime = mktime(&dateTime);
        bGpsHasValidDateTime = true;
    } else {
        bGpsHasValidDateTime = false;
    }
}

void GpsConvertPositionFromStringToNumerical( void )
{
    int i;

    double valueTmp1;
    double valueTmp2;
    double valueTmp3;
    double valueTmp4;

    // Convert the latitude from ASCII to uint8_t values
    for ( i = 0; i < 10; i++ ) {
        NmeaGpsData.NmeaLatitude[i] = NmeaGpsData.NmeaLatitude[i] & 0xF;
    }
    // Convert latitude from degree/minute/second (DMS) format into decimal
    valueTmp1 = (double) NmeaGpsData.NmeaLatitude[0] * 10.0 + (double) NmeaGpsData.NmeaLatitude[1];
    valueTmp2 = (double) NmeaGpsData.NmeaLatitude[2] * 10.0 + (double) NmeaGpsData.NmeaLatitude[3];
    valueTmp3 = (double) NmeaGpsData.NmeaLatitude[5] * 1000.0
            + (double) NmeaGpsData.NmeaLatitude[6] * 100.0
            + (double) NmeaGpsData.NmeaLatitude[7] * 10.0 + (double) NmeaGpsData.NmeaLatitude[8];

    Latitude = valueTmp1 + ((valueTmp2 + (valueTmp3 * 0.0001)) / 60.0);

    if ( NmeaGpsData.NmeaLatitudePole[0] == 'S' ) {
        Latitude *= -1;
    }

    // Convert the longitude from ASCII to uint8_t values
    for ( i = 0; i < 10; i++ ) {
        NmeaGpsData.NmeaLongitude[i] = NmeaGpsData.NmeaLongitude[i] & 0xF;
    }
    // Convert longitude from degree/minute/second (DMS) format into decimal
    valueTmp1 = (double) NmeaGpsData.NmeaLongitude[0] * 100.0
            + (double) NmeaGpsData.NmeaLongitude[1] * 10.0 + (double) NmeaGpsData.NmeaLongitude[2];
    valueTmp2 = (double) NmeaGpsData.NmeaLongitude[3] * 10.0
            + (double) NmeaGpsData.NmeaLongitude[4];
    valueTmp3 = (double) NmeaGpsData.NmeaLongitude[6] * 1000.0
            + (double) NmeaGpsData.NmeaLongitude[7] * 100;
    valueTmp4 = (double) NmeaGpsData.NmeaLongitude[8] * 10.0
            + (double) NmeaGpsData.NmeaLongitude[9];

    Longitude = valueTmp1 + (valueTmp2 / 60.0) + (((valueTmp3 + valueTmp4) * 0.0001) / 60.0);

    if ( NmeaGpsData.NmeaLongitudePole[0] == 'W' ) {
        Longitude *= -1;
    }
}

time_t GpsGetCurrentUnixTime( void )
{
    return gpsUnixTime;
}

uint8_t GpsGetLatestGpsPositionDouble( double *lati, double *longi )
{
    uint8_t status = FAIL;
    if ( GpsHasFix() == true ) {
        status = SUCCESS;
    } else {
        GpsResetPosition();
    }
    *lati = Latitude;
    *longi = Longitude;
    return status;
}

uint8_t GpsGetLatestGpsPositionBinary( int32_t *latiBin, int32_t *longiBin )
{
    uint8_t status = FAIL;

    __disable_irq();
    if ( GpsHasFix() == true ) {
        status = SUCCESS;
    } else {
        GpsResetPosition();
    }
    *latiBin = LatitudeBinary;
    *longiBin = LongitudeBinary;
    __enable_irq();
    return status;
}

uint8_t GpsGetDistanceToLatestGpsPositionBinary( int32_t latiBin, int32_t longiBin,
        uint32_t *distance )
{
    return SUCCESS;
}

uint16_t GpsGetLatestGpsAltitude( void )
{
    uint16_t altBin;

    __disable_irq();
    if ( GpsHasFix() == true ) {
        altBin = AltitudeBinary;
    } else {
        altBin = 0xFFFF;
    }
    __enable_irq();

    return altBin;
}

uint8_t GpsGetLatestTrack( uint16_t *groundSpeed, uint16_t *track )
{
    uint8_t status = FAIL;

    __disable_irq();
    if ( GpsHasFix() == true ) {
        *groundSpeed = GroundSpeedBinary;
        *track = TrackBinary;
        status = SUCCESS;
    }
    __enable_irq();

    return status;
}

/*!
 * Calculates the checksum for a NMEA sentence
 *
 * Skip the first '$' if necessary and calculate checksum until '*' character is
 * reached (or buffSize exceeded).
 *
 * \retval chkPosIdx Position of the checksum in the sentence
 */
int32_t GpsNmeaChecksum( char *nmeaStr, size_t nmeaStrSize, uint8_t * checksum )
{
    int i = 0;
    uint8_t checkNum = 0;

// Check input parameters
    if ( (nmeaStr == NULL) || (checksum == NULL) || (nmeaStrSize <= 1) ) {
        return -1;
    }

// Skip the first '$' if necessary
    if ( nmeaStr[i] == '$' ) {
        i += 1;
    }

// XOR until '*' or max length is reached
    while ( nmeaStr[i] != '*' ) {
        checkNum ^= nmeaStr[i];
        i += 1;
        if ( i >= nmeaStrSize ) {
            return -1;
        }
    }

// Convert checksum value to 2 hexadecimal characters
    checksum[0] = Nibble2HexChar(checkNum / 16);   // upper nibble
    checksum[1] = Nibble2HexChar(checkNum % 16);   // lower nibble

    return i + 1;
}

/*!
 * Calculate the checksum of a NMEA frame and compare it to the checksum that is
 * present at the end of it.
 * Return true if it matches
 */
static bool GpsNmeaValidateChecksum( char *serialBuff, size_t buffSize )
{
    int32_t checksumIndex;
    uint8_t checksum[2];   // 2 characters to calculate NMEA checksum

    checksumIndex = GpsNmeaChecksum(serialBuff, buffSize, checksum);

// could we calculate a verification checksum ?
    if ( checksumIndex < 0 ) {
        return false;
    }

// check if there are enough char in the serial buffer to read checksum
    if ( checksumIndex >= (buffSize - 2) ) {
        return false;
    }

// check the checksum
    if ( (serialBuff[checksumIndex] == checksum[0])
            && (serialBuff[checksumIndex + 1] == checksum[1]) ) {
        return true;
    } else {
        return false;
    }
}

uint8_t GpsParseGpsData( char *rxBuffer, size_t rxBufferSize )
{
    uint8_t i = 1;
    uint8_t j = 0;
    uint8_t fieldSize = 0;

    if ( rxBuffer[0] != '$' ) {
        return FAIL;
    }

    if ( GpsNmeaValidateChecksum(rxBuffer, rxBufferSize) == false ) {
        return FAIL;
    }

    fieldSize = 0;
    while ( rxBuffer[i + fieldSize++] != ',' ) {
        if ( fieldSize > 6 ) {
            return FAIL;
        }
    }
    for ( j = 0; j < fieldSize; j++, i++ ) {
        NmeaGpsData.NmeaDataType[j] = rxBuffer[i];
    }
// Parse the GPGGA data 
    if ( strncmp((const char*) NmeaGpsData.NmeaDataType, (const char*) NmeaDataTypeGPGGA, 5)
            == 0 ) {
        // NmeaUtcTime
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 11 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaUtcTime[j] = rxBuffer[i];
        }
        // NmeaLatitude
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 10 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaLatitude[j] = rxBuffer[i];
        }
        // NmeaLatitudePole
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 2 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaLatitudePole[j] = rxBuffer[i];
        }
        // NmeaLongitude
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 11 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaLongitude[j] = rxBuffer[i];
        }
        // NmeaLongitudePole
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 2 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaLongitudePole[j] = rxBuffer[i];
        }
        // NmeaFixQuality
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 2 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaFixQuality[j] = rxBuffer[i];
        }
        if ( NmeaGpsData.NmeaFixQuality[0] > 0x30 ) {
            bGpsHasFix = true;
        } else {
            bGpsHasFix = false;
        }
        // NmeaSatelliteTracked
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 3 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaSatelliteTracked[j] = rxBuffer[i];
        }
        // NmeaHorizontalDilution
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 6 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaHorizontalDilution[j] = rxBuffer[i];
        }
        // NmeaAltitude
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 8 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaAltitude[j] = rxBuffer[i];
        }
        // NmeaAltitudeUnit
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 2 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaAltitudeUnit[j] = rxBuffer[i];
        }
        // NmeaHeightGeoid
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 8 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaHeightGeoid[j] = rxBuffer[i];
        }
        // NmeaHeightGeoidUnit
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 2 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaHeightGeoidUnit[j] = rxBuffer[i];
        }

        GpsFormatGpsData();
        return SUCCESS;
    } else if ( strncmp((const char*) NmeaGpsData.NmeaDataType, (const char*) NmeaDataTypeGPRMC, 5)
            == 0 ) {
        // NmeaUtcTime
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 11 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaUtcTime[j] = rxBuffer[i];
        }
        // NmeaDataStatus
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 2 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaDataStatus[j] = rxBuffer[i];
        }
        // NmeaLatitude
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 10 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaLatitude[j] = rxBuffer[i];
        }
        // NmeaLatitudePole
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 2 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaLatitudePole[j] = rxBuffer[i];
        }
        // NmeaLongitude
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 11 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaLongitude[j] = rxBuffer[i];
        }
        // NmeaLongitudePole
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 2 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaLongitudePole[j] = rxBuffer[i];
        }
        // NmeaSpeed
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 8 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaSpeed[j] = rxBuffer[i];
        }
        // NmeaDetectionAngle
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 8 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaDetectionAngle[j] = rxBuffer[i];
        }
        // NmeaDate
        fieldSize = 0;
        while ( rxBuffer[i + fieldSize++] != ',' ) {
            if ( fieldSize > 8 ) {
                return FAIL;
            }
        }
        for ( j = 0; j < fieldSize; j++, i++ ) {
            NmeaGpsData.NmeaDate[j] = rxBuffer[i];
        }

        GpsFormatGpsData();
        return SUCCESS;
    } else {
        return FAIL;
    }
}

void GpsFormatGpsData( void )
{
    GpsConvertPositionFromStringToNumerical();
    GpsConvertPositionIntoBinary();
    GpsConvertUnixTimeFromStringToNumerical();
}

void GpsResetPosition( void )
{
    AltitudeBinary = 0xFFFF;
    Latitude = 0;
    Longitude = 0;
    LatitudeBinary = 0;
    LongitudeBinary = 0;
}

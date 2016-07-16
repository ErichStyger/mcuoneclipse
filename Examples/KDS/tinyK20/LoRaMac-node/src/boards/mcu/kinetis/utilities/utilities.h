/**
 * \file utlities.h
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 28.09.2015
 * \brief Target mcu utilities
 *
 */

#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#if defined(USE_KINETIS_SDK)
/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "fsl_i2c_master_driver.h"

/*******************************************************************************
 * CONSTANT DEFINITIONS
 ******************************************************************************/
/* More specific error codes */
#define ERR_OK                          0x00U /*!< OK */
#define ERR_RANGE                       0x01U /*!< Parameter out of range. */
#define ERR_VALUE                       0x02U /*!< Parameter of incorrect value. */
#define ERR_OVERFLOW                    0x03U /*!< Timer overflow. */
#define ERR_ENABLED                     0x04U /*!< Device is enabled. */
#define ERR_DISABLED                    0x05U /*!< Device is disabled. */
#define ERR_BUSY                        0x06U /*!< Device is busy. */
#define ERR_NOTAVAIL                    0x07U /*!< Requested value or method not available. */
#define ERR_RXEMPTY                     0x08U /*!< No data in receiver. */
#define ERR_TXFULL                      0x09U /*!< Transmitter is full. */
#define ERR_OVERRUN                     0x0AU /*!< Overrun error is detected. */
#define ERR_IDLE                        0x0BU /*!< Idle error is detected. */
#define ERR_FAULT                       0x0CU /*!< Fault error is detected. */
#define ERR_CRC                         0x0DU /*!< CRC error is detected. */
#define ERR_UNDERFLOW                   0x0EU /*!< Underflow error is detected. */
#define ERR_UNDERRUN                    0x0FU /*!< Underrun error is detected. */
#define ERR_COMMON                      0x10U /*!< Common error of a device. */
#define ERR_FAILED                      0x11U /*!< Requested functionality or process failed. */
#define ERR_QFULL                       0x12U /*!< Queue is full. */
#define ERR_INVALID_TYPE                0x13U /*!< Invalid type. */
#define ERR_UNKNOWN                     0x14U /*!< */

/*******************************************************************************
 * TYPE DEFINITIONS
 ******************************************************************************/
/*!
 * LoRaMac specific ADC typedef
 */
typedef ADC_Type ADC_TypeDef;

/*!
 * LoRaMac specific I2C typedef
 */
typedef struct {
    uint32_t instance;
    i2c_device_t slave;
    i2c_master_state_t state;
}I2C_TypeDef;
#else
/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include <time.h>

/*******************************************************************************
 * CONSTANT DEFINITIONS
 ******************************************************************************/
/* More specific error codes */
#define ERR_OK                          0x00U /*!< OK */
#define ERR_RANGE                       0x01U /*!< Parameter out of range. */
#define ERR_VALUE                       0x02U /*!< Parameter of incorrect value. */
#define ERR_OVERFLOW                    0x03U /*!< Timer overflow. */
#define ERR_ENABLED                     0x04U /*!< Device is enabled. */
#define ERR_DISABLED                    0x05U /*!< Device is disabled. */
#define ERR_BUSY                        0x06U /*!< Device is busy. */
#define ERR_NOTAVAIL                    0x07U /*!< Requested value or method not available. */
#define ERR_RXEMPTY                     0x08U /*!< No data in receiver. */
#define ERR_TXFULL                      0x09U /*!< Transmitter is full. */
#define ERR_OVERRUN                     0x0AU /*!< Overrun error is detected. */
#define ERR_IDLE                        0x0BU /*!< Idle error is detected. */
#define ERR_FAULT                       0x0CU /*!< Fault error is detected. */
#define ERR_CRC                         0x0DU /*!< CRC error is detected. */
#define ERR_UNDERFLOW                   0x0EU /*!< Underflow error is detected. */
#define ERR_UNDERRUN                    0x0FU /*!< Underrun error is detected. */
#define ERR_COMMON                      0x10U /*!< Common error of a device. */
#define ERR_FAILED                      0x11U /*!< Requested functionality or process failed. */
#define ERR_QFULL                       0x12U /*!< Queue is full. */
#define ERR_INVALID_TYPE                0x13U /*!< Invalid type. */
#define ERR_UNKNOWN                     0x14U /*!< */

/*******************************************************************************
 * TYPE DEFINITIONS
 ******************************************************************************/
typedef uint32_t ADC_TypeDef;
typedef uint32_t I2C_TypeDef;
#endif

/*******************************************************************************
 * MODULE FUNCTION PROTOTYPES (PUBLIC)
 ******************************************************************************/
#if !defined(USE_KINETIS_SDK)
/** \brief  Get IPSR Register

 This function returns the content of the IPSR Register.

 \return               IPSR Register value
 */
__attribute__( ( always_inline ))                  static inline uint32_t __get_IPSR( void )
{
    uint32_t result;

    __asm volatile ("MRS %0, ipsr" : "=r" (result) );
    return (result);
}
#endif

/*!
 * \brief Returns the minimum value betwen a and b
 *
 * \param [IN] a 1st value
 * \param [IN] b 2nd value
 * \retval minValue Minimum value
 */
#define MIN( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )

/*!
 * \brief Returns the maximum value betwen a and b
 *
 * \param [IN] a 1st value
 * \param [IN] b 2nd value
 * \retval maxValue Maximum value
 */
#define MAX( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )

/*!
 * \brief Returns 2 raised to the power of n
 *
 * \param [IN] n power value
 * \retval result of raising 2 to the power n
 */
#define POW2( n ) ( 1 << n )

/*******************************************************************************
 * UTILITY FUNCTION PROTOTYPES (PUBLIC)
 ******************************************************************************/
void custom_strcpy( unsigned char *dst, size_t dstSize, const unsigned char *src );

void custom_strcat( unsigned char *dst, size_t dstSize, const unsigned char *src );

void strcatPad( uint8_t *dst, size_t dstSize, const unsigned char *src, char padChar,
        uint8_t srcPadSize );

void num16sToStr( unsigned char *dst, size_t dstSize, int16_t val );

void num16sToStrFormatted( unsigned char *dst, size_t dstSize, int16_t val, char fill,
        unsigned char nofFill );

void strcatNum16s( unsigned char *dst, size_t dstSize, int16_t val );

void strcatNum16sFormatted( unsigned char *dst, size_t dstSize, int16_t val, char fill,
        unsigned char nofFill );

void strcatNum8Hex( unsigned char *dst, size_t dstSize, unsigned char num );

void strcatNum16Hex( unsigned char *dst, size_t dstSize, unsigned short num );

void strcatNum32s( unsigned char *dst, size_t dstSize, long val );

void num32sToStr( unsigned char *dst, size_t dstSize, long val );

void strcatNum32Hex( unsigned char *dst, size_t dstSize, unsigned long num );

void chcat( unsigned char *dst, size_t dstSize, unsigned char ch );

void strcatNum32u( unsigned char *dst, size_t dstSize, unsigned long val );

void num32uToStr( unsigned char *dst, size_t dstSize, unsigned long val );

void strcatNum32uFormatted( unsigned char *dst, size_t dstSize, unsigned long val, char fill,
        unsigned char nofFill );

void num32uToStrFormatted( unsigned char *dst, size_t dstSize, unsigned long val, char fill,
        unsigned char nofFill );

void strcatNum24Hex( unsigned char *dst, size_t dstSize, unsigned long num );

void num16uToStr( unsigned char *dst, size_t dstSize, unsigned short val );

void num8sToStr( unsigned char *dst, size_t dstSize, signed char val );

void num8uToStr( unsigned char *dst, size_t dstSize, unsigned char val );

void num16uToStrFormatted( unsigned char *dst, size_t dstSize, unsigned short val, char fill,
        unsigned char nofFill );

void num32sToStrFormatted( unsigned char *dst, size_t dstSize, long val, char fill,
        unsigned char nofFill );

void strcatNum16u( unsigned char *dst, size_t dstSize, unsigned short val );

void strcatNum16uFormatted( unsigned char *dst, size_t dstSize, unsigned short val, char fill,
        unsigned char nofFill );

void strcatNum32sFormatted( unsigned char *dst, size_t dstSize, long val, char fill,
        unsigned char nofFill );

void strcatNum8u( unsigned char *dst, size_t dstSize, unsigned char val );

void strcatNum8s( unsigned char *dst, size_t dstSize, signed char val );

unsigned char xatoi( const unsigned char **str, int32_t *res );

/*!
 * \brief Initializes the pseudo ramdom generator initial value
 *
 * \param [IN] seed Pseudo ramdom generator initial value
 */
void srand1( uint32_t seed );

/*!
 * \brief Computes a random number between min and max
 *
 * \param [IN] min range minimum value
 * \param [IN] max range maximum value
 * \retval random random value in range min..max
 */
int32_t randr( int32_t min, int32_t max );

/*!
 * \brief Copies size elements of src array to dst array
 *
 * \remark STM32 Standard memcpy function only works on pointers that are aligned
 *
 * \param [OUT] dst  Destination array
 * \param [IN]  src  Source array
 * \param [IN]  size Number of bytes to be copied
 */
void memcpy1( uint8_t *dst, const uint8_t *src, uint16_t size );

/*!
 * \brief Set size elements of dst array with value
 *
 * \remark STM32 Standard memset function only works on pointers that are aligned
 *
 * \param [OUT] dst   Destination array
 * \param [IN]  value Default value
 * \param [IN]  size  Number of bytes to be copied
 */
void memset1( uint8_t *dst, uint8_t value, uint16_t size );

/*!
 * \brief Converts a nibble to an hexadecimal character
 *
 * \param [IN] a   Nibble to be converted
 * \retval hexChar Converted hexadecimal character
 */
int8_t Nibble2HexChar( uint8_t a );
#endif /* __UTILITIES_H__ */

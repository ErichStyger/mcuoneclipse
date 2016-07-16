/**
 * \file utlities.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 28.09.2015
 * \brief Target mcu utilities
 *
 */

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include <stdio.h>
#include <limits.h>
#include "board.h"
#include "utilities.h"

/*******************************************************************************
 * PRIVATE CONSTANT DEFINITIONS
 ******************************************************************************/
// Standard random functions redefinition start
#define RAND_LOCAL_MAX 2147483647L

/* 2000-03-01 (mod 400 year, immediately after feb29 */
#define LEAPOCH (946684800LL + 86400*(31+29))

#define DAYS_PER_400Y (365*400 + 97)
#define DAYS_PER_100Y (365*100 + 24)
#define DAYS_PER_4Y   (365*4   + 1)

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES (STATIC)
 ******************************************************************************/
static void ShiftRightAndFill( byte *dst, byte fill, byte nofFill );

/*******************************************************************************
 * PRIVATE VARIABLES (STATIC)
 ******************************************************************************/
static uint32_t next = 1;

/*******************************************************************************
 * MODULE FUNCTIONS (PUBLIC)
 ******************************************************************************/
/*!
 \brief copy the string src into dst. It performs the same task as strncpy, except
 - always terminates the result string.
 - does not zero out the remaining part in dst.
 Note: dstSize is the size of dst INCLUDING zero byte.
 Precondition: src, dst != NULL
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize The size of the buffer, including the zero byte
 \param[in] src The source string to copy
 */
void custom_strcpy( byte *dst, size_t dstSize, const unsigned char *src )
{
    dstSize--; /* for zero byte */
    while ( dstSize > 0 && *src != '\0' ) {
        *dst++ = *src++;
        dstSize--;
    }
    *dst = '\0';
}

/*!
 \brief Concat the string src into dst. Always terminates the result string.
 Note: count is the size of dst INCLUDING zero byte.
 Precondition: src, dst != NULL
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize The size of the buffer, including the zero byte
 \param[in] src The source string to add
 */
void custom_strcat( byte *dst, size_t dstSize, const unsigned char *src )
{
    dstSize--; /* for zero byte */
    /* point to the end of the source */
    while ( dstSize > 0 && *dst != '\0' ) {
        dst++;
        dstSize--;
    }
    /* copy the src in the destination */
    while ( dstSize > 0 && *src != '\0' ) {
        *dst++ = *src++;
        dstSize--;
    }
    /* terminate the string */
    *dst = '\0';
}

void strcatPad( uint8_t *dst, size_t dstSize, const unsigned char *src, char padChar,
        uint8_t srcPadSize )
{
    uint8_t *p;
    size_t nof = 0;

    if ( dstSize < 2 ) {
        return; /* hmm, really to small for anything than the zero byte? */
    }
    p = dst;
    while ( *p != '\0' ) { /* find end of string */
        p++;
        nof++;
    }
    custom_strcat(dst + nof, dstSize - nof, src); /* add string */
    dstSize -= nof;
    while ( *p != '\0' && srcPadSize > 0 && dstSize > 1 ) {
        p++;
        srcPadSize--;
        dstSize--;
    }
    while ( srcPadSize > 0 && dstSize > 1 ) {
        *p++ = padChar; /* add padding char */
        srcPadSize--;
        dstSize--;
    }
    *p = '\0'; /* terminate string */
}

void chcat( byte *dst, size_t dstSize, byte ch )
{
    dstSize--; /* for zero byte */
    /* point to the end of the source */
    while ( dstSize > 0 && *dst != '\0' ) {
        dst++;
        dstSize--;
    }
    /* copy the ch in the destination */
    if ( dstSize > 0 ) {
        *dst++ = ch;
    }
    /* terminate the string */
    *dst = '\0';
}

/*!
 \brief Converts an 8bit unsigned number into a string.
 \param[in,out] dst String buffer to store the number.
 \param[in] dstSize Size of the destination buffer in bytes.
 \param[in] val 8bit unsigned number to convert.
 */
void num8uToStr( byte *dst, size_t dstSize, byte val )
{
    num16uToStr(dst, dstSize, (uint16_t) val);
}

/*!
 \brief Converts an 8bit signed number into a string.
 \param[in,out] dst String buffer to store the number.
 \param[in] dstSize Size of the destination buffer in bytes.
 \param[in] val 8bit signed number to convert.
 */
void num8sToStr( byte *dst, size_t dstSize, signed char val )
{
    num16sToStr(dst, dstSize, (int16_t) val);
}

/*!
 \brief Converts a 16bit unsigned number into a string.
 \param[in,out] dst String buffer to store the number.
 \param[in] dstSize Size of the destination buffer in bytes.
 \param[in] val 16bit unsigned number to convert.
 */
void num16uToStr( byte *dst, size_t dstSize, word val )
{
    unsigned char *ptr = ((unsigned char *) dst);
    unsigned char i = 0, j;
    unsigned char tmp;

    dstSize--; /* for zero byte */
    if ( val == 0 && dstSize > 0 ) {
        ptr[i++] = '0';
        dstSize--;
    }
    while ( val > 0 && dstSize > 0 ) {
        ptr[i++] = (unsigned char) ((val % 10) + '0');
        dstSize--;
        val /= 10;
    }
    for ( j = 0; j < (i / 2); j++ ) { /* swap buffer */
        tmp = ptr[j];
        ptr[j] = ptr[(i - j) - 1];
        ptr[(i - j) - 1] = tmp;
    }
    ptr[i] = '\0';
}

/*!
 \brief Converts a 16bit signed number into a string.
 \param[in,out] dst String buffer to store the number.
 \param[in] dstSize Size of the destination buffer in bytes.
 \param[in] val 16bit signed number to convert.
 */
void num16sToStr( byte *dst, size_t dstSize, int16_t val )
{
    unsigned char *ptr = ((unsigned char *) dst);
    unsigned char i = 0, j;
    unsigned char tmp;
    unsigned char sign = (unsigned char) (val < 0);

    if ( val == (int16_t)(0x8000) ) { /* special case 0x8000/-32768: prevent overflow below. */
        custom_strcpy(dst, dstSize, (unsigned char*) "-32768");
        return;
    }
    dstSize--; /* for zero byte */
    if ( sign ) {
        val = -val;
    }
    if ( val == 0 && dstSize > 0 ) {
        ptr[i++] = '0';
        dstSize--;
    }
    while ( val > 0 && dstSize > 0 ) {
        ptr[i++] = (unsigned char) ((val % 10) + '0');
        dstSize--;
        val /= 10;
    }
    if ( sign && dstSize > 0 ) {
        ptr[i++] = '-';
        dstSize--;
    }
    for ( j = 0; j < (i / 2); j++ ) { /* swap buffer */
        tmp = ptr[j];
        ptr[j] = ptr[(i - j) - 1];
        ptr[(i - j) - 1] = tmp;
    }
    ptr[i] = '\0';
}

/*!
 \brief Converts a 16bit signed number to a string, in a formatted way (like printf with "%0d").
 Always terminates the result string.
 Note: count is the size of dst INCLUDING zero byte.
 Precondition: src, dst != NULL
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize Size of the destination buffer, in bytes.
 \param[in] val The 16bit signed number to add
 \param[in] fill Fill character, typically ' ' (like for "%2d" or '0' (for "%02d")
 \param[in] nofFill Size for the format (right aligned) string, e.g. '2' for "%2d"
 */
void num16sToStrFormatted( byte *dst, size_t dstSize, int16_t val, char fill, byte nofFill )
{
    num16sToStr(dst, dstSize, val);
    ShiftRightAndFill(dst, fill, nofFill);
}

/*!
 \brief Converts a 16bit unsigned number to a string, in a formatted way (like printf with "%0d").
 Always terminates the result string.
 Note: count is the size of dst INCLUDING zero byte.
 Precondition: src, dst != NULL
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize Size of the destination buffer, in bytes.
 \param[in] val The 16bit unsigned number to add
 \param[in] fill Fill character, typically ' ' (like for "%2d" or '0' (for "%02d")
 \param[in] nofFill Size for the format (right aligned) string, e.g. '2' for "%2d"
 */
void num16uToStrFormatted( byte *dst, size_t dstSize, word val, char fill, byte nofFill )
{
    num16uToStr(dst, dstSize, val);
    ShiftRightAndFill(dst, fill, nofFill);
}

/*!
 \brief Converts a 32bit unsigned number to a string, in a formatted way (like printf with "%0d").
 Always terminates the result string.
 Note: count is the size of dst INCLUDING zero byte.
 Precondition: src, dst != NULL
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize Size of the destination buffer, in bytes.
 \param[in] val The 32bit unsigned number to add
 \param[in] fill Fill character, typically ' ' (like for "%2d" or '0' (for "%02d")
 \param[in] nofFill Size for the format (right aligned) string, e.g. '2' for "%2d"
 */
void num32uToStrFormatted( byte *dst, size_t dstSize, unsigned long val, char fill, byte nofFill )
{
    num32uToStr(dst, dstSize, val);
    ShiftRightAndFill(dst, fill, nofFill);
}

/*!
 \brief Converts a 32bit signed number to a string, in a formatted way (like printf with "%0d").
 Always terminates the result string.
 Note: count is the size of dst INCLUDING zero byte.
 Precondition: src, dst != NULL
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize Size of the destination buffer, in bytes.
 \param[in] val The 32bit signed number to add
 \param[in] fill Fill character, typically ' ' (like for "%2d" or '0' (for "%02d")
 \param[in] nofFill Size for the format (right aligned) string, e.g. '2' for "%2d"
 */
void num32sToStrFormatted( byte *dst, size_t dstSize, long val, char fill, byte nofFill )
{
    num32sToStr(dst, dstSize, val);
    ShiftRightAndFill(dst, fill, nofFill);
}

/*!
 \brief appends a 8bit unsigned number to a string. Always terminates the result string.
 Note: count is the size of dst INCLUDING zero byte.
 Precondition: src, dst != NULL
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize The size of the buffer, including the zero byte
 \param[in] val The 8bit unsigned number to add
 */
void strcatNum8u( byte *dst, size_t dstSize, byte val )
{
    unsigned char buf[sizeof("256")]; /* maximum buffer size we need */

    num8uToStr(buf, sizeof(buf), val);
    custom_strcat(dst, dstSize, buf);
}

/*!
 \brief appends a 8bit signed number to a string. Always terminates the result string.
 Note: count is the size of dst INCLUDING zero byte.
 Precondition: src, dst != NULL
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize The size of the buffer, including the zero byte
 \param[in] val The 8bit signed number to add
 */
void strcatNum8s( byte *dst, size_t dstSize, signed char val )
{
    unsigned char buf[sizeof("-128")]; /* maximum buffer size we need */

    num8sToStr(buf, sizeof(buf), val);
    custom_strcat(dst, dstSize, buf);
}

/*!
 \brief appends a 16bit unsigned number to a string. Always terminates the result string.
 Note: count is the size of dst INCLUDING zero byte.
 Precondition: src, dst != NULL
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize The size of the buffer, including the zero byte
 \param[in] val The 16bit unsigned number to add
 */
void strcatNum16u( byte *dst, size_t dstSize, word val )
{
    unsigned char buf[sizeof("32768")]; /* maximum buffer size we need */

    num16uToStr(buf, sizeof(buf), val);
    custom_strcat(dst, dstSize, buf);
}

/*!
 \brief appends a 16bit signed number to a string. Always terminates the result string.
 Note: count is the size of dst INCLUDING zero byte.
 Precondition: src, dst != NULL
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize The size of the buffer, including the zero byte
 \param[in] val The 16bit signed number to add
 */
void strcatNum16s( byte *dst, size_t dstSize, int16_t val )
{
    unsigned char buf[sizeof("-32768")]; /* maximum buffer size we need */

    num16sToStr(buf, sizeof(buf), val);
    custom_strcat(dst, dstSize, buf);
}

/*!
 \brief appends a 16bit unsigned number to a string, in a formatted way (like printf with "%0d".
 Always terminates the result string.
 Note: count is the size of dst INCLUDING zero byte.
 Precondition: src, dst != NULL
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize The size of the buffer, including the zero byte
 \param[in] val The 16bit unsigned number to add
 \param[in] fill Fill character
 \param[in] nofFill Number of fill characters
 */
void strcatNum16uFormatted( byte *dst, size_t dstSize, word val, char fill, byte nofFill )
{
    unsigned char buf[sizeof("32768")]; /* maximum buffer size we need */

    num16uToStrFormatted(buf, dstSize, val, fill, nofFill);
    custom_strcat(dst, dstSize, buf);
}

/*!
 \brief appends a 16bit signed number to a string, in a formatted way (like printf with "%0d".
 Always terminates the result string.
 Note: count is the size of dst INCLUDING zero byte.
 Precondition: src, dst != NULL
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize The size of the buffer, including the zero byte
 \param[in] val The 16bit signed number to add
 \param[in] fill Fill character
 \param[in] nofFill Number of fill characters
 */
void strcatNum16sFormatted( byte *dst, size_t dstSize, int16_t val, char fill, byte nofFill )
{
    unsigned char buf[sizeof("-32768")]; /* maximum buffer size we need */

    num16sToStrFormatted(buf, dstSize, val, fill, nofFill);
    custom_strcat(dst, dstSize, buf);
}

/*!
 \brief appends a 32bit unsigned number to a string, in a formatted way (like printf with "%0d".
 Always terminates the result string.
 Note: count is the size of dst INCLUDING zero byte.
 Precondition: src, dst != NULL
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize The size of the buffer, including the zero byte
 \param[in] val The 32bit unsigned number to add
 \param[in] fill Fill character
 \param[in] nofFill Number of fill characters
 */
void strcatNum32uFormatted( byte *dst, size_t dstSize, unsigned long val, char fill, byte nofFill )
{
    unsigned char buf[sizeof("4294967295")]; /* maximum buffer size we need */

    num32uToStrFormatted(buf, dstSize, val, fill, nofFill);
    custom_strcat(dst, dstSize, buf);
}

/*!
 \brief appends a 32bit signed number to a string, in a formatted way (like printf with "%0d".
 Always terminates the result string.
 Note: count is the size of dst INCLUDING zero byte.
 Precondition: src, dst != NULL
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize The size of the buffer, including the zero byte
 \param[in] val The 32bit signed number to add
 \param[in] fill Fill character
 \param[in] nofFill Number of fill characters
 */
void strcatNum32sFormatted( byte *dst, size_t dstSize, long val, char fill, byte nofFill )
{
    unsigned char buf[sizeof("-4294967295")]; /* maximum buffer size we need */

    num32sToStrFormatted(buf, dstSize, val, fill, nofFill);
    custom_strcat(dst, dstSize, buf);
}

/*!
 \brief Adds a 8bit number as hex value to a string.
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize The size of the buffer, including the zero byte
 \param[in] num The 8bit number to add
 */
void strcatNum8Hex( byte *dst, size_t dstSize, byte num )
{
    unsigned char buf[sizeof("FF")]; /* maximum buffer size we need */
    unsigned char hex;

    buf[2] = '\0';
    hex = (char) (num & 0x0F);
    buf[1] = (char) (hex + ((hex <= 9) ? '0' : ('A' - 10)));
    hex = (char) ((num >> 4) & 0x0F);
    buf[0] = (char) (hex + ((hex <= 9) ? '0' : ('A' - 10)));
    custom_strcat(dst, dstSize, buf);
}

/*!
 \brief Adds a 16bit number as hex value to a string.
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize The size of the buffer, including the zero byte
 \param[in] num The 16bit number to add
 */
void strcatNum16Hex( byte *dst, size_t dstSize, word num )
{
    unsigned char buf[sizeof("FFFF")]; /* maximum buffer size we need */
    unsigned char hex;
    int8_t i;

    buf[4] = '\0';
    i = 3;
    do {
        hex = (char) (num & 0x0F);
        buf[i] = (char) (hex + ((hex <= 9) ? '0' : ('A' - 10)));
        num >>= 4; /* next nibble */
        i--;
    } while ( i >= 0 );
    custom_strcat(dst, dstSize, buf);
}

/*!
 \brief Adds a 24bit number as hex value to a string.
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize The size of the buffer, including the zero byte
 \param[in] num The 24bit number to add
 */
void strcatNum24Hex( byte *dst, size_t dstSize, unsigned long num )
{
    unsigned char buf[sizeof("FFFFFF")]; /* maximum buffer size we need */
    unsigned char hex;
    int8_t i;

    buf[6] = '\0';
    i = 5;
    do {
        hex = (char) (num & 0x0F);
        buf[i] = (char) (hex + ((hex <= 9) ? '0' : ('A' - 10)));
        num >>= 4; /* next nibble */
        i--;
    } while ( i >= 0 );
    custom_strcat(dst, dstSize, buf);
}

/*!
 \brief Adds a 32bit number as hex value to a string.
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize The size of the buffer, including the zero byte
 \param[in] num The 32bit number to add
 */
void strcatNum32Hex( byte *dst, size_t dstSize, unsigned long num )
{
    unsigned char buf[sizeof("FFFFFFFF")]; /* maximum buffer size we need */
    unsigned char hex;
    int8_t i;

    buf[8] = '\0';
    i = 7;
    do {
        hex = (char) (num & 0x0F);
        buf[i] = (char) (hex + ((hex <= 9) ? '0' : ('A' - 10)));
        num >>= 4; /* next nibble */
        i--;
    } while ( i >= 0 );
    custom_strcat(dst, dstSize, buf);
}

/*!
 \brief appends a 32bit (long) number to a string. Always terminates the result string.
 Note: count is the size of dst INCLUDING zero byte.
 Precondition: src, dst != NULL
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize The size of the buffer, including the zero byte
 \param[in] val The 32bit number to add
 */
void strcatNum32s( byte *dst, size_t dstSize, long val )
{
    unsigned char buf[sizeof("-4294967295")]; /* maximum buffer size we need */

    num32sToStr(buf, sizeof(buf), val);
    custom_strcat(dst, dstSize, buf);
}

/*!
 \brief appends a 32bit (unsigned long) number to a string. Always terminates the result string.
 Note: count is the size of dst INCLUDING zero byte.
 Precondition: src, dst != NULL
 \param[in,out] dst Start of buffer, where to append the number string
 \param[in] dstSize The size of the buffer, including the zero byte
 \param[in] val The 32bit unsigned number to add
 */
void strcatNum32u( byte *dst, size_t dstSize, unsigned long val )
{
    unsigned char buf[sizeof("4294967295")]; /* maximum buffer size we need */

    num32uToStr(buf, sizeof(buf), val);
    custom_strcat(dst, dstSize, buf);
}

/*!
 \brief Converts a 32bit number to a string.
 \param[in,out] dst String buffer to store the number.
 \param[in] dstSize Size of the destination buffer in bytes.
 \param[in] val 32bit signed number to convert.
 */
void num32sToStr( byte *dst, size_t dstSize, long val )
{
    unsigned char *ptr = ((unsigned char *) dst);
    unsigned char i = 0, j;
    unsigned char tmp;
    unsigned char sign = (unsigned char) (val < 0);

    if ( val == (int32_t)(0x80000000) ) { /* special case 0x80000000/-2147483648: prevent overflow below. */
        custom_strcpy(dst, dstSize, (unsigned char*) "-2147483648");
        return;
    }
    dstSize--; /* for zero byte */
    if ( sign ) {
        val = -val;
    }
    if ( val == 0 && dstSize > 0 ) {
        ptr[i++] = '0';
        dstSize--;
    }
    while ( val > 0 && dstSize > 0 ) {
        ptr[i++] = (unsigned char) ((val % 10) + '0');
        dstSize--;
        val /= 10;
    }
    if ( sign && dstSize > 0 ) {
        ptr[i++] = '-';
        dstSize--;
    }
    for ( j = 0; j < (i / 2); j++ ) { /* swap buffer */
        tmp = ptr[j];
        ptr[j] = ptr[(i - j) - 1];
        ptr[(i - j) - 1] = tmp;
    }
    ptr[i] = '\0';
}

/*!
 \brief Converts a 32bit signed number to a string.
 \param[in,out] dst String buffer to store the number.
 \param[in] dstSize Size of the destination buffer in bytes.
 \param[in] val 32bit unsigned number to convert.
 */
void num32uToStr( byte *dst, size_t dstSize, unsigned long val )
{
    unsigned char *ptr = ((unsigned char *) dst);
    unsigned char i = 0, j;
    unsigned char tmp;

    dstSize--; /* for zero byte */
    if ( val == 0 && dstSize > 0 ) {
        ptr[i++] = '0';
        dstSize--;
    }
    while ( val > 0 && dstSize > 0 ) {
        ptr[i++] = (unsigned char) ((val % 10) + '0');
        dstSize--;
        val /= 10;
    }
    for ( j = 0; j < (i / 2); j++ ) { /* swap buffer */
        tmp = ptr[j];
        ptr[j] = ptr[(i - j) - 1];
        ptr[(i - j) - 1] = tmp;
    }
    ptr[i] = '\0';
}

byte xatoi( const unsigned char **str, int32_t *res )
{
    uint32_t val;
    uint8_t c, r, s = 0;

    *res = 0;
    while ( **str == ' ' ) {
        (*str)++; /* Skip leading spaces */
    }
    c = **str;
    if ( c == '-' ) { /* negative? */
        s = 1;
        c = *(++(*str));
    }
    if ( c == '0' ) {
        c = *(++(*str));
        switch ( c ) {
            case 'x': /* hexadecimal */
                r = 16;
                c = *(++(*str));
                break;
            case 'b': /* binary */
                r = 2;
                c = *(++(*str));
                break;
            default:
                if ( c <= ' ' || c == '.' ) {
                    return ERR_OK; /* single zero */
                }
                if ( c < '0' || c > '9' ) {
                    return ERR_FAILED; /* invalid char */
                }
                r = 8; /* octal */
                break;
        } /* switch */
    } else {
        if ( c < '0' || c > '9' ) {
            return ERR_FAILED; /* EOL or invalid char */
        }
        r = 10; /* decimal */
    }
    val = 0;
    while ( c > ' ' && c != '.' ) {
        if ( c >= 'a' ) c -= 0x20;
        c -= '0';
        if ( c >= 17 ) {
            c -= 7;
            if ( c <= 9 ) return ERR_FAILED; /* invalid char */
        }
        if ( c >= r ) return ERR_FAILED; /* invalid char for current radix */
        val = val * r + c;
        c = *(++(*str));
    } /* while */
    if ( s ) val = 0 - val; /* apply sign if needed */
    *res = (long) val;
    return ERR_OK;
}

int32_t rand1( void )
{
    return ((next = next * 1103515245L + 12345L) % RAND_LOCAL_MAX);
}

void srand1( uint32_t seed )
{
    next = seed;
}

/*! Standard random functions redefinition end */

int32_t randr( int32_t min, int32_t max )
{
    return (int32_t)((uint32_t) rand1() % (max - min + 1) + min);
}

void memcpy1( uint8_t *dst, const uint8_t *src, uint16_t size )
{
    while ( size-- ) {
        *dst++ = *src++;
    }
}

void memset1( uint8_t *dst, uint8_t value, uint16_t size )
{
    while ( size-- ) {
        *dst++ = value;
    }
}

int8_t Nibble2HexChar( uint8_t a )
{
    if ( a < 10 ) {
        return '0' + a;
    } else if ( a < 16 ) {
        return 'A' + (a - 10);
    } else {
        return '?';
    }
}

static void ShiftRightAndFill( byte *dst, byte fill, byte nofFill )
{
    signed char i, j;

    j = 0;
    while ( dst[j] != '\0' ) {
        j++;
    }
    i = (signed char) nofFill;
    if ( i == j ) {
        /* nothing to do, we are done */
    } else if ( i > j ) {
        while ( j >= 0 ) {
            dst[i] = dst[j];
            i--;
            j--;
        }
        while ( i >= 0 ) {
            dst[i] = fill;
            i--;
        }
    } else {
        /* hmmm, not enough space, return what we have, do nothing */
    }
}


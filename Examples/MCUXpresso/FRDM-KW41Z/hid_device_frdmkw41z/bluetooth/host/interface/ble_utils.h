/*! *********************************************************************************
 * \addtogroup BLE
 * @{
 ********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file ble_utils.h
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
*   contributors may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _BLE_UTILS_H_
#define _BLE_UTILS_H_

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/
/*! Type qualifier - does not affect local variables of integral type */
#ifndef PACKED_STRUCT
#if defined(__GNUC__)
#define PACKED_STRUCT struct __attribute__ ((__packed__))
#elif defined(__IAR_SYSTEMS_ICC__)
#define PACKED_STRUCT __packed struct
#else
#define PACKED_STRUCT struct
#endif
#endif

/*! Type qualifier - does not affect local variables of integral type */
#ifndef PACKED_UNION
#if defined(__GNUC__)
#define PACKED_UNION  union __attribute__ ((__packed__))
#elif defined(__IAR_SYSTEMS_ICC__)
#define PACKED_UNION __packed union
#else
#define PACKED_UNION union
#endif
#endif

/*! Type qualifier - does not affect local variables of integral type */
#ifndef WEAK
#if defined(__GNUC__)
#define WEAK __attribute__ ((__weak__))
#elif defined(__IAR_SYSTEMS_ICC__)
#define WEAK __weak
#endif
#endif

/*! Storage class modifier - alignment of a variable. It does not affect the type of the function */
#if defined(__IAR_SYSTEMS_ICC__)
#define ALIGN_8BIT  #pragma data_alignment(1)
#define ALIGN_16BIT #pragma data_alignment(2)
#define ALIGN_32BIT #pragma data_alignment(4)
#define ALIGN_64BIT #pragma data_alignment(8)
#elif defined(__GNUC__)
#define ALIGN_8BIT  #pragma pack(1)
#define ALIGN_16BIT #pragma pack(2)
#define ALIGN_32BIT #pragma pack(4)
#define ALIGN_64BIT #pragma pack(8)
#endif

/*! Marks that this variable is in the interface. */
#ifndef global
#define global
#endif

/*! Marks a function that never returns. */
#if !defined(__IAR_SYSTEMS_ICC__)
#ifndef __noreturn
#define __noreturn
#endif
#endif

/*! Returns a uint16_t from a buffer, little-endian */
#define Utils_ExtractTwoByteValue(buf) \
        ((*(buf)) | ( (*((buf) + 1)) << 8) )

/*! Returns a 3-byte value from a buffer, little-endian */
#define Utils_ExtractThreeByteValue(buf) \
        ( \
                (*(buf)) \
                | ( (*((buf) + 1)) << 8) \
                | ( (*((buf) + 2)) << 16) \
        )

/*! Returns a uint32_t from a buffer, little-endian */
#define Utils_ExtractFourByteValue(buf) \
( \
    (*(buf)) \
    | ( (*((buf) + 1)) << 8) \
    | ( (*((buf) + 2)) << 16) \
    | ( (*((buf) + 3)) << 24) \
)

/*! Returns a uint16_t from a buffer, big-endian */
#define Utils_BeExtractTwoByteValue(buf) \
    ((*((buf) + 1)) | ( (*(buf)) << 8) )

/*! Returns a 3-byte value from a buffer, big-endian */
#define Utils_BeExtractThreeByteValue(buf) \
( \
    (*((buf) + 2)) \
    | ( (*((buf) + 1)) << 8) \
    | ( (*(buf)) << 16) \
)

/*! Returns a uint32_t from a buffer, big-endian */
#define Utils_BeExtractFourByteValue(buf) \
( \
    (*((buf) + 3)) \
    | ( (*((buf) + 2)) << 8) \
    | ( (*((buf) + 1)) << 16) \
    | ( (*(buf)) << 24) \
)

/*! Writes a uint16_t into a buffer, little-endian */
#define Utils_PackTwoByteValue(value, buf) \
{ \
    (buf)[0] = (uint8_t) ((value) & 0xFF); \
    (buf)[1] = (uint8_t) (((value) >> 8) & 0xFF); \
}

/*! Writes a 3-byte value into a buffer, little-endian */
#define Utils_PackThreeByteValue(value, buf) \
{ \
    (buf)[0] = (uint8_t) ((value) & 0xFF); \
    (buf)[1] = (uint8_t) (((value) >> 8) & 0xFF); \
    (buf)[2] = (uint8_t) (((value) >> 16) & 0xFF); \
}

/*! Writes a uint32_t into a buffer, little-endian */
#define Utils_PackFourByteValue(value, buf) \
{ \
    (buf)[0] = (uint8_t) ((value) & 0xFF); \
    (buf)[1] = (uint8_t) (((value) >> 8) & 0xFF); \
    (buf)[2] = (uint8_t) (((value) >> 16) & 0xFF); \
    (buf)[3] = (uint8_t) (((value) >> 24) & 0xFF); \
}

/*! Writes a uint16_t into a buffer, big-endian */
#define Utils_BePackTwoByteValue(value, buf) \
{ \
    (buf)[1] = (uint8_t) ((value) & 0xFF); \
    (buf)[0] = (uint8_t) (((value) >> 8) & 0xFF); \
}

/*! Writes a 3-byte value into a buffer, big-endian */
#define Utils_BePackThreeByteValue(value, buf) \
{ \
    (buf)[2] = (uint8_t) ((value) & 0xFF); \
    (buf)[1] = (uint8_t) (((value) >> 8) & 0xFF); \
    (buf)[0] = (uint8_t) (((value) >> 16) & 0xFF); \
}

/*! Writes a uint32_t into a buffer, big-endian */
#define Utils_BePackFourByteValue(value, buf) \
{ \
    (buf)[3] = (uint8_t) ((value) & 0xFF); \
    (buf)[2] = (uint8_t) (((value) >> 8) & 0xFF); \
    (buf)[1] = (uint8_t) (((value) >> 16) & 0xFF); \
    (buf)[0] = (uint8_t) (((value) >> 24) & 0xFF); \
}

/*! Writes a uint8_t into a buffer, little-endian, and increments the pointer.*/
#define Utils_Copy8(ptr, val8) \
        {   *(ptr)++ = (uint8_t)(val8); }

/*! Writes a uint16_t into a buffer, little-endian, and increments the pointer. */
#define Utils_Copy16(ptr, val16) \
        {   *(ptr)++ = (uint8_t)(val16);\
            *(ptr)++ = (uint8_t)((val16) >> SHIFT8); }

/*! Writes a uint32_t into a buffer, little-endian, and increments the pointer. */
#define Utils_Copy32(ptr, val32) \
        {   *(ptr)++ = (uint8_t)(val32);\
            *(ptr)++ = (uint8_t)((val32) >> SHIFT8);\
            *(ptr)++ = (uint8_t)((val32) >> SHIFT16);\
            *(ptr)++ = (uint8_t)((val32) >> SHIFT24); }

/*! Writes a uint64_t into a buffer, little-endian, and increments the pointer. */
#define Utils_Copy64(ptr, val64) \
        {   *(ptr)++ = (uint8_t)(val64);\
            *(ptr)++ = (uint8_t)((val64) >> SHIFT8);\
            *(ptr)++ = (uint8_t)((val64) >> SHIFT16);\
            *(ptr)++ = (uint8_t)((val64) >> SHIFT24);\
            *(ptr)++ = (uint8_t)((val64) >> SHIFT32);\
            *(ptr)++ = (uint8_t)((val64) >> SHIFT40);\
            *(ptr)++ = (uint8_t)((val64) >> SHIFT48);\
            *(ptr)++ = (uint8_t)((val64) >> SHIFT56); }

/*! Reverts the order of bytes in an array - useful for changing the endianness */
#define Utils_RevertByteArray(array, size) \
{ \
    uint8_t temp; \
    for (uint8_t j = 0; j < (size)/2; j++) \
    { \
        temp = (array)[j]; \
        (array)[j] = (array)[(size) - 1 - j]; \
        (array)[(size) - 1 - j] = temp; \
    } \
}

#endif /* _BLE_UTILS_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */

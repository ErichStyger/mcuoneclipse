/**
* Copyright Ivo Gärtner
* \file
* \author Ivo Gärtner
* \copyright Ivo Gärtner
* \date 9.11.2018
* SPDX-License-Identifier: BSD-3-Clause
*
* This program code does very closely rely on the example code
* of Ross Williams' article "A Painless Guide to CRC Error
* Detection Algorithms".
*
*
* How to use this code:
*
* First: Define the McuCRC_Generator_t structure, e.g. like this:
*
* McuCRC_Generator_t crcGen;
* crcGen.McuCRC_InitialValue = 0xFFFFFFFF;
* crcGen.McuCRC_Polynomial =  0x04C11DB7;
* crcGen.McuCRC_ReflectedInput = 0;
* crcGen.McuCRC_ReflectedOutput = 0;
* crcGen.McuCRC_Width = McuCRC_WIDTH_32_BIT;
* crcGen.McuCRC_XorOutput = 0xFFFFFFFF;
* crcGen.McuCRC_Table = NULL;
*
* Second: Run the McuCRC_Init function on the McuCRC_Generator_t structure:
*
* McuCRC_Init( &crcGen );
*
* Third: For the shift register implementation call McuCRC_CalculateBlock() and then McuCRC_GetCrcValue(), e.g. like this:
*
* uint32_t crc;
* uint8_t byteArray[] = {0x01, 0x01, 0x12, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5};
*
* McuCRC_CalculateBlock( &crcGen, byteArray, 8 );
* crc = McuCRC_GetCrcValue( &crcGen );
*
* Or for the LUT implementation call McuCRC_CalculateWithTableCRC32(), or the 8 / 16 bit versions of it, like this:
*
* crc = McuCRC_CalculateWithTableCRC8( &crcGen, byteArray, 8 );
*
*
* happy crc'ing
*/

#ifndef McuCRC_GENERATOR_H_INCLUDED
#define McuCRC_GENERATOR_H_INCLUDED

#include <stdint.h>
#include <stddef.h>

#define McuCRC_BIT_PER_BYTE 8

enum McuCRC_WIDTH_BITS
{
    McuCRC_WIDTH_8_BIT = 8,
    McuCRC_WIDTH_16_BIT = 16,
    McuCRC_WIDTH_32_BIT = 32
};

typedef struct
  {
   enum McuCRC_WIDTH_BITS McuCRC_Width; /**< PARAMETER: Width of the CRC in bits - 16 or 32 */
   uint32_t McuCRC_Polynomial;       /**< PARAMETER: The CRC algorithm's polynomial */
   uint32_t McuCRC_InitialValue;      /**< PARAMETER: Initial register value */
   uint32_t McuCRC_ReflectedInput;   /**< PARAMETER: Reflect input - 0: no, >=1: yes  */
   uint32_t McuCRC_ReflectedOutput;  /**< PARAMETER: Reflect output - 0: no, >=1: yes        */
   uint32_t McuCRC_XorOutput;        /**< PARAMETER: XOR this to the output of the CRC calculation */
   uint32_t McuCRC_WidthMask;        /**< CONTEXT: Mask for the crc width */
   uint32_t McuCRC_Register;         /**< CONTEXT: Storage for the crc value */
   void *McuCRC_Table;               /**< PARAMETER: Pointer to a LUT if no shift register implementation is used */
  } McuCRC_Generator_t;

/**
* \fn McuCRC_Init()
*
* \brief Sets the initial value of the crc calculation and calculates the width mask
*
* \param McuCRC_Generator_t *crcGen Pointer to a \a McuCRC_Generator_t structure
*/
void McuCRC_Init ( McuCRC_Generator_t *crcGen );

/**
* \fn McuCRC_CalculateBlock()
*
* \brief Calculates a crc from a block of data (uint8_t array)
*
* This function calculates the crc but does not Xor the output. To get the
* Xor'd output use the function \a McuCRC_GetCrcValue() which returns the Xor'd
* crc value.
*
* \param McuCRC_Generator_t *crcGen Pointer to a \a McuCRC_Generator_t structure
* \param uint8_t *data_pu8 Pointer to the data to be crc'd
* \param size_t length  Number of bytes in the data array
*/
void McuCRC_CalculateBlock (McuCRC_Generator_t *crcGen, uint8_t *data_pu8, size_t length );

/**
* \fn McuCRC_CalculateNextValue()
*
* \brief Calculates the crc of one byte in a data stream
*
* \param McuCRC_Generator_t *crcGen Pointer to a \a McuCRC_Generator_t structure
* \param uint8_t data_u8 Byte to be crc'd
*
*/
void McuCRC_CalculateNextValue ( McuCRC_Generator_t *crcGen, uint8_t data_u8 );

/**
* \fn McuCRC_GetCrcValue()
*
* \brief Returns you the Xor'd crc
*
* When you ran the functions \a McuCRC_CalculateBlock or \a McuCRC_CalculateNextValue over
* the data which you want to CRC, this function Xor's the calculated crc and returns
* this Xor'd value.
*
* \param McuCRC_Generator_t *crcGen Pointer to a \a McuCRC_Generator_t structure
* \return The value in crcGen->McuCRC_Register XOR^d with the crcGen->McuCRC_XorOut parameter
*/
uint32_t McuCRC_GetCrcValue ( McuCRC_Generator_t *crcGen );

/**
* \fn McuCRC_CalculateWithTableCRC32()
*
* \brief Calculates a 32 bit crc of a byte array using a LUT
*
* The LUT used for this function can be calculated using the function \a McuCRC_GenerateLookUpTable()
* The pointer the LUT has to be casted to (void*)
*
* \param McuCRC_Generator_t *crcGen Pointer to a \a McuCRC_Generator_t structure
* \return The calculated crc, XOR^d with the crcGen->McuCRC_XorOut parameter
*/
uint32_t McuCRC_CalculateWithTableCRC32 ( McuCRC_Generator_t *crcGen, uint8_t *data_pu8, size_t length );

/**
* \fn McuCRC_CalculateWithTableCRC16()
*
* \brief Calculates a 16 bit crc of a byte array using a LUT
*
* The LUT used for this function can be calculated using the function \a McuCRC_GenerateLookUpTable()
* The pointer the LUT has to be casted to (void*)
*
* \param McuCRC_Generator_t *crcGen Pointer to a \a McuCRC_Generator_t structure
* \return The calculated crc, XOR^d with the crcGen->McuCRC_XorOut parameter
*/
uint16_t McuCRC_CalculateWithTableCRC16 ( McuCRC_Generator_t *crcGen, uint8_t *data_pu8, size_t length );

/**
* \fn McuCRC_CalculateWithTableCRC8()
*
* \brief Calculates a 8 bit crc of a byte array using a LUT
*
* The LUT used for this function can be calculated using the function \a McuCRC_GenerateLookUpTable()
* The pointer the LUT has to be casted to (void*)
*
* \param McuCRC_Generator_t *crcGen Pointer to a \a McuCRC_Generator_t structure
* \return The calculated crc, XOR^d with the crcGen->McuCRC_XorOut parameter
*/
uint8_t McuCRC_CalculateWithTableCRC8 ( McuCRC_Generator_t *crcGen, uint8_t *data_pu8, size_t length );

/**
* \fn McuCRC_Reflect()
*
* \brief Returns the bottom \a noOfBits_u32 bits of \a value_u32 in revered order
*
* \param uint32_t value_u32 Value on which to perform the bit reversal
* \param uint32_t noOfBits_u32 Number of bits to reverse
*/
uint32_t McuCRC_Reflect ( uint32_t value_u32, uint32_t noOfBits_u32);

#endif // McuCRC_GENERATOR_H_INCLUDED

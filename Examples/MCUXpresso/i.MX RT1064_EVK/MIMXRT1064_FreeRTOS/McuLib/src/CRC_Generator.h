/**
* \file CRC_Generator.h
*
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
* First: Define the CRC_Generator_t structure, e.g. like this:
*
* CRC_Generator_t crcGen;
* crcGen.CRC_InitialValue = 0xFFFFFFFF;
* crcGen.CRC_Polynomial =  0x04C11DB7;
* crcGen.CRC_ReflectedInput = 0;
* crcGen.CRC_ReflectedOutput = 0;
* crcGen.CRC_Width = CRC_WIDTH_32_BIT;
* crcGen.CRC_XorOutput = 0xFFFFFFFF;
* crcGen.CRC_Table = NULL;
*
* Second: Run the CRC_Init function on the CRC_Generator_t structure:
*
* CRC_Init( &crcGen );
*
* Third: For the shift register implementation call CRC_CalculateBlock() and then CRC_GetCrcValue(), e.g. like this:
*
* uint32_t crc;
* uint8_t byteArray[] = {0x01, 0x01, 0x12, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5};
*
* CRC_CalculateBlock( &crcGen, byteArray, 8 );
* crc = CRC_GetCrcValue( &crcGen );
*
* Or for the LUT implementation call CRC_CalculateWithTableCRC32(), or the 8 / 16 bit versions of it, like this:
*
* crc = CRC_CalculateWithTableCRC8( &crcGen, byteArray, 8 );
*
*
* happy crc'ing
*/

#ifndef CRC_GENERATOR_H_INCLUDED
#define CRC_GENERATOR_H_INCLUDED

#include <stdint.h>
#include <stddef.h>

#define CRC_BIT_PER_BYTE 8

enum CRC_WIDTH_BITS
{
    CRC_WIDTH_8_BIT = 8,
    CRC_WIDTH_16_BIT = 16,
    CRC_WIDTH_32_BIT = 32
};

typedef struct
  {
   enum CRC_WIDTH_BITS CRC_Width; /**< PARAMETER: Width of the CRC in bits - 16 or 32 */
   uint32_t CRC_Polynomial;       /**< PARAMETER: The CRC algorithm's polynomial */
   uint32_t CRC_InitialValue;      /**< PARAMETER: Initial register value */
   uint32_t CRC_ReflectedInput;   /**< PARAMETER: Reflect input - 0: no, >=1: yes  */
   uint32_t CRC_ReflectedOutput;  /**< PARAMETER: Reflect output - 0: no, >=1: yes        */
   uint32_t CRC_XorOutput;        /**< PARAMETER: XOR this to the output of the CRC calculation */
   uint32_t CRC_WidthMask;        /**< CONTEXT: Mask for the crc width */
   uint32_t CRC_Register;         /**< CONTEXT: Storage for the crc value */
   void *CRC_Table;               /**< PARAMETER: Pointer to a LUT if no shift register implementation is used */
  } CRC_Generator_t;

/**
* \fn CRC_Init()
*
* \brief Sets the initial value of the crc calculation and calculates the width mask
*
* \param CRC_Generator_t *crcGen Pointer to a \a CRC_Generator_t structure
*/
void CRC_Init ( CRC_Generator_t *crcGen );

/**
* \fn CRC_CalculateBlock()
*
* \brief Calculates a crc from a block of data (uint8_t array)
*
* This function calculates the crc but does not Xor the output. To get the
* Xor'd output use the function \a CRC_GetCrcValue() which returns the Xor'd
* crc value.
*
* \param CRC_Generator_t *crcGen Pointer to a \a CRC_Generator_t structure
* \param uint8_t *data_pu8 Pointer to the data to be crc'd
* \param size_t length  Number of bytes in the data array
*/
void CRC_CalculateBlock (CRC_Generator_t *crcGen, uint8_t *data_pu8, size_t length );

/**
* \fn CRC_CalculateNextValue()
*
* \brief Calculates the crc of one byte in a data stream
*
* \param CRC_Generator_t *crcGen Pointer to a \a CRC_Generator_t structure
* \param uint8_t data_u8 Byte to be crc'd
*
*/
void CRC_CalculateNextValue ( CRC_Generator_t *crcGen, uint8_t data_u8 );

/**
* \fn CRC_GetCrcValue()
*
* \brief Returns you the Xor'd crc
*
* When you ran the functions \a CRC_CalculateBlock or \a CRC_CalculateNextValue over
* the data which you want to CRC, this function Xor's the calculated crc and returns
* this Xor'd value.
*
* \param CRC_Generator_t *crcGen Pointer to a \a CRC_Generator_t structure
* \return The value in crcGen->CRC_Register XOR^d with the crcGen->CRC_XorOut parameter
*/
uint32_t CRC_GetCrcValue ( CRC_Generator_t *crcGen );

/**
* \fn CRC_CalculateWithTableCRC32()
*
* \brief Calculates a 32 bit crc of a byte array using a LUT
*
* The LUT used for this function can be calculated using the function \a CRC_GenerateLookUpTable()
* The pointer the LUT has to be casted to (void*)
*
* \param CRC_Generator_t *crcGen Pointer to a \a CRC_Generator_t structure
* \return The calculated crc, XOR^d with the crcGen->CRC_XorOut parameter
*/
uint32_t CRC_CalculateWithTableCRC32 ( CRC_Generator_t *crcGen, uint8_t *data_pu8, size_t length );

/**
* \fn CRC_CalculateWithTableCRC16()
*
* \brief Calculates a 16 bit crc of a byte array using a LUT
*
* The LUT used for this function can be calculated using the function \a CRC_GenerateLookUpTable()
* The pointer the LUT has to be casted to (void*)
*
* \param CRC_Generator_t *crcGen Pointer to a \a CRC_Generator_t structure
* \return The calculated crc, XOR^d with the crcGen->CRC_XorOut parameter
*/
uint16_t CRC_CalculateWithTableCRC16 ( CRC_Generator_t *crcGen, uint8_t *data_pu8, size_t length );

/**
* \fn CRC_CalculateWithTableCRC8()
*
* \brief Calculates a 8 bit crc of a byte array using a LUT
*
* The LUT used for this function can be calculated using the function \a CRC_GenerateLookUpTable()
* The pointer the LUT has to be casted to (void*)
*
* \param CRC_Generator_t *crcGen Pointer to a \a CRC_Generator_t structure
* \return The calculated crc, XOR^d with the crcGen->CRC_XorOut parameter
*/
uint8_t CRC_CalculateWithTableCRC8 ( CRC_Generator_t *crcGen, uint8_t *data_pu8, size_t length );

/**
* \fn CRC_Reflect()
*
* \brief Returns the bottom \a noOfBits_u32 bits of \a value_u32 in revered order
*
* \param uint32_t value_u32 Value on which to perform the bit reversal
* \param uint32_t noOfBits_u32 Number of bits to reverse
*/
uint32_t CRC_Reflect ( uint32_t value_u32, uint32_t noOfBits_u32);

#endif // CRC_GENERATOR_H_INCLUDED

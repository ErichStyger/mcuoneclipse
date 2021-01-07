/**
* \file CRC_CreateTable.h
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
* How to use this code:
*
* These functions are only used to create a LUT for the CRC
* calculation. They are not meant to be executed on a MCU
* since they use stdlib.h and stdio.h
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
* Third: Run the CRC_GenerateLookUpTable function on the CRC_Generator_t structure:
*
* CRC_GenerateLookUpTable( &crcGen );
*
* This will create a file named as defined in CRC_FILENAME on your hard drive.
*
* Fourth: Copy the LUT declaration into your code and assign a pointer to the LUT
* to the CRC_Generator_t structure:
*
* crcGen.CRC_Table = (void*)CRC_Table;
*
* Now you can calculate crc's by using the function CRC_CalculateWithTableCRC32 or
* CRC_CalculateWithTableCRC16 if you calculated a 16 bit crc LUT, like this:
*
* uint8_t byteArray[] = {0x01, 0x01, 0x12, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5};
* crc = CRC_CalculateWithTableCRC32( &crcGen, byteArray, 8 );
*
* happy crc'ing
*/


#ifndef CRC_CREATETABLE_H_INCLUDED
#define CRC_CREATETABLE_H_INCLUDED

#include <stdint.h>
#include <stddef.h>
#include <CRC_Generator.h>

#define CRC_TABLE_SIZE 256

#define CRC_FILENAME "CrcTable.txt"


enum CRC_GenerateTableResult
{
    CRC_TABLE_OK,
    CRC_TABLE_ERR_WIDTH,
    CRC_TABLE_ERR_REFLECTED_INPUT_OUTPUT_NOT_IDENTICAL,
    CRC_TABLE_ERR_POLYNOMIAL_TOO_LARGE_FOR_8BIT_TABLE,
    CRC_TABLE_ERR_XOR_OUT_TOO_LARGE_FOR_8BIT_TABLE,
    CRC_TABLE_ERR_POLYNOMIAL_TOO_LARGE_FOR_16BIT_TABLE,
    CRC_TABLE_ERR_XOR_OUT_TOO_LARGE_FOR_16BIT_TABLE,
    CRC_TABLE_ERR_FILE_OPEN,
    CRC_TABLE_ERR_FILE_CLOSE
};

/**
* \fn CRC_GenerateLookUpTable()
*
* \brief Calculates the LUT entries and writes it into a file
*
* This function needs the \a CRC_Generator_t structure to be fully defined.
* Be aware that input and output reflection MUST BE THE SAME to create a
* table (I've seen no standard CRC which has them mixed).
* If you want to have input and output reflection not identical, you should
* use the shift register implementation!
*
* The XorOut parameter does not have any impact, since the Xor'ing of the
* output is calculated within the
*
* \param CRC_Generator_t *crcGen Pointer to a \a CRC_Generator_t structure
* \return CRC_GenerateTableResult Result of the crc table generation as described in \a CRC_GenerateTableResult
*/
enum CRC_GenerateTableResult CRC_GenerateLookUpTable( CRC_Generator_t *crcGen );

/**
* \fn CRC_CalculateTableEntry()
*
* \brief Calculates an entry for the LUT at a specific index
*
* \param CRC_Generator_t *crcGen Pointer to a \a CRC_Generator_t structure
* \param uint32_t index_u32 Index of the table entry
* \return Table entry as uint32_t
*/
uint32_t CRC_CalculateTableEntry ( CRC_Generator_t *crcGen, uint32_t index_u32 );

#endif // CRC_CREATETABLE_H_INCLUDED

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
* How to use this code:
*
* These functions are only used to create a LUT for the CRC
* calculation. They are not meant to be executed on a MCU
* since they use stdlib.h and stdio.h
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
* Third: Run the McuCRC_GenerateLookUpTable function on the McuCRC_Generator_t structure:
*
* McuCRC_GenerateLookUpTable( &crcGen );
*
* This will create a file named as defined in McuCRC_FILENAME on your hard drive.
*
* Fourth: Copy the LUT declaration into your code and assign a pointer to the LUT
* to the McuCRC_Generator_t structure:
*
* crcGen.McuCRC_Table = (void*)McuCRC_Table;
*
* Now you can calculate crc's by using the function McuCRC_CalculateWithTableCRC32 or
* McuCRC_CalculateWithTableCRC16 if you calculated a 16 bit crc LUT, like this:
*
* uint8_t byteArray[] = {0x01, 0x01, 0x12, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5};
* crc = McuCRC_CalculateWithTableCRC32( &crcGen, byteArray, 8 );
*
* happy crc'ing
*/


#ifndef McuCRC_CREATETABLE_H_INCLUDED
#define McuCRC_CREATETABLE_H_INCLUDED

#include <stdint.h>
#include <stddef.h>
#include "McuCRC_Generator.h"

#define McuCRC_TABLE_SIZE 256

#define McuCRC_FILENAME "CrcTable.txt"


enum McuCRC_GenerateTableResult
{
    McuCRC_TABLE_OK,
    McuCRC_TABLE_ERR_WIDTH,
    McuCRC_TABLE_ERR_REFLECTED_INPUT_OUTPUT_NOT_IDENTICAL,
    McuCRC_TABLE_ERR_POLYNOMIAL_TOO_LARGE_FOR_8BIT_TABLE,
    McuCRC_TABLE_ERR_XOR_OUT_TOO_LARGE_FOR_8BIT_TABLE,
    McuCRC_TABLE_ERR_POLYNOMIAL_TOO_LARGE_FOR_16BIT_TABLE,
    McuCRC_TABLE_ERR_XOR_OUT_TOO_LARGE_FOR_16BIT_TABLE,
    McuCRC_TABLE_ERR_FILE_OPEN,
    McuCRC_TABLE_ERR_FILE_CLOSE
};

/**
* \fn McuCRC_GenerateLookUpTable()
*
* \brief Calculates the LUT entries and writes it into a file
*
* This function needs the \a McuCRC_Generator_t structure to be fully defined.
* Be aware that input and output reflection MUST BE THE SAME to create a
* table (I've seen no standard CRC which has them mixed).
* If you want to have input and output reflection not identical, you should
* use the shift register implementation!
*
* The XorOut parameter does not have any impact, since the Xor'ing of the
* output is calculated within the
*
* \param McuCRC_Generator_t *crcGen Pointer to a \a McuCRC_Generator_t structure
* \return McuCRC_GenerateTableResult Result of the crc table generation as described in \a McuCRC_GenerateTableResult
*/
enum McuCRC_GenerateTableResult McuCRC_GenerateLookUpTable( McuCRC_Generator_t *crcGen );

/**
* \fn McuCRC_CalculateTableEntry()
*
* \brief Calculates an entry for the LUT at a specific index
*
* \param McuCRC_Generator_t *crcGen Pointer to a \a McuCRC_Generator_t structure
* \param uint32_t index_u32 Index of the table entry
* \return Table entry as uint32_t
*/
uint32_t McuCRC_CalculateTableEntry ( McuCRC_Generator_t *crcGen, uint32_t index_u32 );

#endif // McuCRC_CREATETABLE_H_INCLUDED

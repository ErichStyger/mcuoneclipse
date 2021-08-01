/**
* Copyright Ivo Gärtner
* \file
* \author Ivo Gärtner
* \copyright Ivo Gärtner
* \date 9.11.2018
* SPDX-License-Identifier: BSD-3-Clause
*
* See the header file for comments
*/

#include <stdint.h>
#include <stddef.h>

#include "McuCRC_Generator.h"

void McuCRC_Init (McuCRC_Generator_t *crcGen)
{
    crcGen->McuCRC_Register = crcGen->McuCRC_InitialValue;
    crcGen->McuCRC_WidthMask = ( ( (1 << ( crcGen->McuCRC_Width - 1 ) ) - 1 ) << 1) | 1;
}

void McuCRC_CalculateBlock (McuCRC_Generator_t *crcGen, uint8_t *data_pu8, size_t length )
{
    uint8_t inputData_u8;
    while ( length-- )
    {
        inputData_u8 = *data_pu8++;
        McuCRC_CalculateNextValue( crcGen, inputData_u8 );
    }
}

void McuCRC_CalculateNextValue ( McuCRC_Generator_t *crcGen, uint8_t data_u8 )
{
    uint32_t loopCounter_u32;
    uint32_t uData_u32;
    uint32_t topbit_u32;

    uData_u32 = data_u8;
    topbit_u32 = ( 1 << (crcGen->McuCRC_Width-1));

    if ( crcGen->McuCRC_ReflectedInput )
    {
    uData_u32 = McuCRC_Reflect( uData_u32, McuCRC_BIT_PER_BYTE );
    }
    crcGen->McuCRC_Register ^= (uData_u32 << (crcGen->McuCRC_Width - McuCRC_BIT_PER_BYTE));

    for ( loopCounter_u32 = 0; loopCounter_u32 < McuCRC_BIT_PER_BYTE; loopCounter_u32++)
    {
        if (crcGen->McuCRC_Register & topbit_u32)
        {
            crcGen->McuCRC_Register = (crcGen->McuCRC_Register << 1) ^ crcGen->McuCRC_Polynomial;
        }
        else
        {
            crcGen->McuCRC_Register =  (crcGen->McuCRC_Register << 1);
        }
        crcGen->McuCRC_Register &= crcGen->McuCRC_WidthMask;
    }
}

uint32_t McuCRC_GetCrcValue ( McuCRC_Generator_t *crcGen )
{
    if (crcGen->McuCRC_ReflectedOutput)
    {
        return crcGen->McuCRC_XorOutput ^ McuCRC_Reflect( crcGen->McuCRC_Register, crcGen->McuCRC_Width );
    }
    else
    {
        return crcGen->McuCRC_XorOutput ^ crcGen->McuCRC_Register;
    }
}

uint8_t McuCRC_CalculateWithTableCRC8 ( McuCRC_Generator_t *crcGen, uint8_t *data_pu8, size_t length )
{
    uint32_t loopCounter_u32;
    uint8_t crcValue_u8;
    uint8_t *crcTable_au8;

    crcTable_au8 = (uint8_t*)crcGen->McuCRC_Table;

    crcValue_u8 = crcGen->McuCRC_InitialValue;

    for ( loopCounter_u32 = 0 ; loopCounter_u32 < length ; loopCounter_u32++ )
    {
        crcValue_u8 = crcTable_au8[( crcValue_u8 ^ (data_pu8[loopCounter_u32])) & 0xFF];
    }

    crcValue_u8 ^= crcGen->McuCRC_XorOutput;

    return crcValue_u8;
}

uint16_t McuCRC_CalculateWithTableCRC16 ( McuCRC_Generator_t *crcGen, uint8_t *data_pu8, size_t length )
{
    uint32_t loopCounter_u32;
    uint16_t crcValue_u16;
    uint16_t *crcTable_au16;

    crcTable_au16 = (uint16_t*)crcGen->McuCRC_Table;

    crcValue_u16 = crcGen->McuCRC_InitialValue;

    if ( (crcGen->McuCRC_ReflectedInput == 0) && (crcGen->McuCRC_ReflectedOutput == 0) )
    {
        for ( loopCounter_u32 = 0 ; loopCounter_u32 < length ; loopCounter_u32++ )
        {
            crcValue_u16 = crcTable_au16[((crcValue_u16 >> 8) ^ (data_pu8[loopCounter_u32])) & 0xFF] ^ (crcValue_u16 << McuCRC_BIT_PER_BYTE);
        }
    }
    else if ( (crcGen->McuCRC_ReflectedInput == 1) && (crcGen->McuCRC_ReflectedOutput == 1) )
    {
        for ( loopCounter_u32 = 0 ; loopCounter_u32 < length ; loopCounter_u32++ )
        {
            crcValue_u16 = crcTable_au16[(crcValue_u16 ^ (data_pu8[loopCounter_u32])) & 0xFF] ^ (crcValue_u16 >> McuCRC_BIT_PER_BYTE);
        }
    }

    crcValue_u16 ^= crcGen->McuCRC_XorOutput;

    return crcValue_u16;
}

uint32_t McuCRC_CalculateWithTableCRC32 ( McuCRC_Generator_t *crcGen, uint8_t *data_pu8, size_t length )
{
    uint32_t loopCounter_u32;
    uint32_t crcValue_u32;
    uint32_t *crcTable_au32;

    crcTable_au32 = (uint32_t*)crcGen->McuCRC_Table;

    crcValue_u32 = crcGen->McuCRC_InitialValue;

    if ( (crcGen->McuCRC_ReflectedInput == 0) && (crcGen->McuCRC_ReflectedOutput == 0) )
    {
        for ( loopCounter_u32 = 0 ; loopCounter_u32 < length ; loopCounter_u32++ )
        {
            crcValue_u32 = crcTable_au32[((crcValue_u32 >> 24) ^ (data_pu8[loopCounter_u32])) & 0xFF] ^ (crcValue_u32 << McuCRC_BIT_PER_BYTE);
        }
    }
    else if ( (crcGen->McuCRC_ReflectedInput == 1) && (crcGen->McuCRC_ReflectedOutput == 1) )
    {
        for ( loopCounter_u32 = 0 ; loopCounter_u32 < length ; loopCounter_u32++ )
        {
            crcValue_u32 = crcTable_au32[(crcValue_u32 ^ (data_pu8[loopCounter_u32])) & 0xFF] ^ (crcValue_u32 >> McuCRC_BIT_PER_BYTE);
        }
    }

    crcValue_u32 ^= crcGen->McuCRC_XorOutput;

    return crcValue_u32;
}

uint32_t McuCRC_Reflect ( uint32_t value_u32, uint32_t noOfBits_u32)
{
     uint32_t loopCounter_u32, temp_u32;

     temp_u32 = value_u32;
     for ( loopCounter_u32 = 0 ; loopCounter_u32 < noOfBits_u32 ; loopCounter_u32++ )
       {
        if (temp_u32 & 1)
        {
            value_u32 |=  ( 1 << ( (noOfBits_u32 - 1) - loopCounter_u32 ) );
        }
        else
        {
            value_u32 &=  ~( 1 << ( (noOfBits_u32 - 1) - loopCounter_u32 ) );
        }
        temp_u32 =  (temp_u32 >> 1);
       }
     return value_u32;
}



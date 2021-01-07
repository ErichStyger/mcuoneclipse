/**
* \file CRC_Generator.c
*
* \author Ivo Gärtner
* \copyright Ivo Gärtner
* \date 9.11.2018
* SPDX-License-Identifier: BSD-3-Clause
*
* See the header file for comments
*/

#include <stdint.h>
#include <stddef.h>

#include <CRC_Generator.h>

void CRC_Init (CRC_Generator_t *crcGen)
{
    crcGen->CRC_Register = crcGen->CRC_InitialValue;
    crcGen->CRC_WidthMask = ( ( (1 << ( crcGen->CRC_Width - 1 ) ) - 1 ) << 1) | 1;
}

void CRC_CalculateBlock (CRC_Generator_t *crcGen, uint8_t *data_pu8, size_t length )
{
    uint8_t inputData_u8;
    while ( length-- )
    {
        inputData_u8 = *data_pu8++;
        CRC_CalculateNextValue( crcGen, inputData_u8 );
    }
}

void CRC_CalculateNextValue ( CRC_Generator_t *crcGen, uint8_t data_u8 )
{
    uint32_t loopCounter_u32;
    uint32_t uData_u32;
    uint32_t topbit_u32;

    uData_u32 = data_u8;
    topbit_u32 = ( 1 << (crcGen->CRC_Width-1));

    if ( crcGen->CRC_ReflectedInput )
    {
    uData_u32 = CRC_Reflect( uData_u32, CRC_BIT_PER_BYTE );
    }
    crcGen->CRC_Register ^= (uData_u32 << (crcGen->CRC_Width - CRC_BIT_PER_BYTE));

    for ( loopCounter_u32 = 0; loopCounter_u32 < CRC_BIT_PER_BYTE; loopCounter_u32++)
    {
        if (crcGen->CRC_Register & topbit_u32)
        {
            crcGen->CRC_Register = (crcGen->CRC_Register << 1) ^ crcGen->CRC_Polynomial;
        }
        else
        {
            crcGen->CRC_Register =  (crcGen->CRC_Register << 1);
        }
        crcGen->CRC_Register &= crcGen->CRC_WidthMask;
    }
}

uint32_t CRC_GetCrcValue ( CRC_Generator_t *crcGen )
{
    if (crcGen->CRC_ReflectedOutput)
    {
        return crcGen->CRC_XorOutput ^ CRC_Reflect( crcGen->CRC_Register, crcGen->CRC_Width );
    }
    else
    {
        return crcGen->CRC_XorOutput ^ crcGen->CRC_Register;
    }
}

uint8_t CRC_CalculateWithTableCRC8 ( CRC_Generator_t *crcGen, uint8_t *data_pu8, size_t length )
{
    uint32_t loopCounter_u32;
    uint8_t crcValue_u8;
    uint8_t *crcTable_au8;

    crcTable_au8 = (uint8_t*)crcGen->CRC_Table;

    crcValue_u8 = crcGen->CRC_InitialValue;

    for ( loopCounter_u32 = 0 ; loopCounter_u32 < length ; loopCounter_u32++ )
    {
        crcValue_u8 = crcTable_au8[( crcValue_u8 ^ (data_pu8[loopCounter_u32])) & 0xFF];
    }

    crcValue_u8 ^= crcGen->CRC_XorOutput;

    return crcValue_u8;
}

uint16_t CRC_CalculateWithTableCRC16 ( CRC_Generator_t *crcGen, uint8_t *data_pu8, size_t length )
{
    uint32_t loopCounter_u32;
    uint16_t crcValue_u16;
    uint16_t *crcTable_au16;

    crcTable_au16 = (uint16_t*)crcGen->CRC_Table;

    crcValue_u16 = crcGen->CRC_InitialValue;

    if ( (crcGen->CRC_ReflectedInput == 0) && (crcGen->CRC_ReflectedOutput == 0) )
    {
        for ( loopCounter_u32 = 0 ; loopCounter_u32 < length ; loopCounter_u32++ )
        {
            crcValue_u16 = crcTable_au16[((crcValue_u16 >> 8) ^ (data_pu8[loopCounter_u32])) & 0xFF] ^ (crcValue_u16 << CRC_BIT_PER_BYTE);
        }
    }
    else if ( (crcGen->CRC_ReflectedInput == 1) && (crcGen->CRC_ReflectedOutput == 1) )
    {
        for ( loopCounter_u32 = 0 ; loopCounter_u32 < length ; loopCounter_u32++ )
        {
            crcValue_u16 = crcTable_au16[(crcValue_u16 ^ (data_pu8[loopCounter_u32])) & 0xFF] ^ (crcValue_u16 >> CRC_BIT_PER_BYTE);
        }
    }

    crcValue_u16 ^= crcGen->CRC_XorOutput;

    return crcValue_u16;
}

uint32_t CRC_CalculateWithTableCRC32 ( CRC_Generator_t *crcGen, uint8_t *data_pu8, size_t length )
{
    uint32_t loopCounter_u32;
    uint32_t crcValue_u32;
    uint32_t *crcTable_au32;

    crcTable_au32 = (uint32_t*)crcGen->CRC_Table;

    crcValue_u32 = crcGen->CRC_InitialValue;

    if ( (crcGen->CRC_ReflectedInput == 0) && (crcGen->CRC_ReflectedOutput == 0) )
    {
        for ( loopCounter_u32 = 0 ; loopCounter_u32 < length ; loopCounter_u32++ )
        {
            crcValue_u32 = crcTable_au32[((crcValue_u32 >> 24) ^ (data_pu8[loopCounter_u32])) & 0xFF] ^ (crcValue_u32 << CRC_BIT_PER_BYTE);
        }
    }
    else if ( (crcGen->CRC_ReflectedInput == 1) && (crcGen->CRC_ReflectedOutput == 1) )
    {
        for ( loopCounter_u32 = 0 ; loopCounter_u32 < length ; loopCounter_u32++ )
        {
            crcValue_u32 = crcTable_au32[(crcValue_u32 ^ (data_pu8[loopCounter_u32])) & 0xFF] ^ (crcValue_u32 >> CRC_BIT_PER_BYTE);
        }
    }

    crcValue_u32 ^= crcGen->CRC_XorOutput;

    return crcValue_u32;
}

uint32_t CRC_Reflect ( uint32_t value_u32, uint32_t noOfBits_u32)
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



/**
* \file CRC_CreateTable.c
*
* \author Ivo Gärtner
* \copyright Ivo Gärtner
* \date 9.11.2018
* SPDX-License-Identifier: BSD-3-Clause
* See the header file for comments
*/

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <CRC_CreateTable.h>
#include <CRC_Generator.h>

enum CRC_GenerateTableResult CRC_GenerateLookUpTable( CRC_Generator_t *crcGen )
{
    char *formatString;
    uint32_t valuesPerLine_u32, loopCounter_u32, tableEntry_u32;
    FILE *outputFile;

    char formatString8[] = "0x%02X";
    char formatString16[] = "0x%04X";
    char formatString32[] = "0x%08X";

    if ( (crcGen->CRC_Width != 8) && (crcGen->CRC_Width != 16) && (crcGen->CRC_Width != 32) )
    {
        return CRC_TABLE_ERR_WIDTH;
    }

    if ( ((crcGen->CRC_ReflectedInput == 0) && (crcGen->CRC_ReflectedOutput != 0)) ||
         ((crcGen->CRC_ReflectedInput != 0) && (crcGen->CRC_ReflectedOutput == 0)) )
    {
        return CRC_TABLE_ERR_REFLECTED_INPUT_OUTPUT_NOT_IDENTICAL;
    }

    if ( (crcGen->CRC_Width == 8) && ( (crcGen->CRC_Polynomial & 0xFFFFFF00) != 0) )
    {
        return CRC_TABLE_ERR_POLYNOMIAL_TOO_LARGE_FOR_16BIT_TABLE;
    }
    if ( (crcGen->CRC_Width == 8) && ( (crcGen->CRC_XorOutput & 0xFFFFFF00) != 0) )
    {
        return CRC_TABLE_ERR_XOR_OUT_TOO_LARGE_FOR_16BIT_TABLE;
    }

    if ( (crcGen->CRC_Width == 16) && ( (crcGen->CRC_Polynomial & 0xFFFF0000) != 0) )
    {
        return CRC_TABLE_ERR_POLYNOMIAL_TOO_LARGE_FOR_16BIT_TABLE;
    }
    if ( (crcGen->CRC_Width == 16) && ( (crcGen->CRC_XorOutput & 0xFFFF0000) != 0) )
    {
        return CRC_TABLE_ERR_XOR_OUT_TOO_LARGE_FOR_16BIT_TABLE;
    }

    outputFile = fopen( CRC_FILENAME, "w" );

    if ( outputFile == NULL )
    {
        return CRC_TABLE_ERR_FILE_OPEN;
    }

    fprintf(outputFile, "/*****************************************************************/\n");
    fprintf(outputFile, "/*                                                               */\n");
    fprintf(outputFile, "/* CRC LOOKUP TABLE                                              */\n");
    fprintf(outputFile, "/* ================                                              */\n");
    fprintf(outputFile, "/* The following CRC lookup table was generated using program    */\n");
    fprintf(outputFile, "/* code which is inspired by Ross Williams' article              */\n");
    fprintf(outputFile, "/* \"A Painless Guide to CRC Error Detection Algorithms\".       */\n");
    fprintf(outputFile, "/*                                                               */\n");
    fprintf(outputFile, "/* The following parameters were used:                           */\n");
    fprintf(outputFile, "/*                                                               */\n");
    fprintf(outputFile, "/*    Width            : %u bits                                 */\n",
       crcGen->CRC_Width);
    if ( crcGen->CRC_Width == 32 ){
    fprintf(outputFile, "/*    Polynomial       : 0x%08X                              */\n",
            (unsigned int)crcGen->CRC_Polynomial);}
    else if ( crcGen->CRC_Width == 16 ) {
    fprintf(outputFile, "/*    Polynomial       : 0x%04X                                  */\n",
        (unsigned int)crcGen->CRC_Polynomial);}
    else {
    fprintf(outputFile, "/*    Polynomial       : 0x%02X                                    */\n",
        (unsigned int)crcGen->CRC_Polynomial);
    }
    if (crcGen->CRC_ReflectedInput == 1){
    fprintf(outputFile, "/*    Reflected Input  : TRUE                                    */\n");}
    else {
    fprintf(outputFile, "/*    Reflected Input  : FALSE                                   */\n");}
    if (crcGen->CRC_ReflectedOutput == 1){
    fprintf(outputFile, "/*    Reflected Output : TRUE                                    */\n");}
    else {
    fprintf(outputFile, "/*    Reflected Output : FALSE                                   */\n");}
    fprintf(outputFile, "/*                                                               */\n");
    fprintf(outputFile, "/*****************************************************************/\n");
    fprintf(outputFile, "\n");

    if ( crcGen->CRC_Width == 32 ){
        fprintf(outputFile, "uint32_t CRC_Table[%d] = \n{\n", CRC_TABLE_SIZE);
        formatString = formatString32;
        valuesPerLine_u32 = 4;
    }
    else if ( crcGen->CRC_Width == 16 ){
        fprintf(outputFile, "uint16_t CRC_Table[%d] = \n{\n", CRC_TABLE_SIZE);
        formatString = formatString16;
        valuesPerLine_u32 = 8;
    }
    else {
        fprintf(outputFile, "uint8_t CRC_Table[%d] = \n{\n", CRC_TABLE_SIZE);
        formatString = formatString8;
        valuesPerLine_u32 = 12;
    }

    for ( loopCounter_u32 = 0 ; loopCounter_u32 < CRC_TABLE_SIZE ; loopCounter_u32++ )
    {
        fprintf(outputFile, " ");
        tableEntry_u32 = (uint32_t)CRC_CalculateTableEntry( crcGen, loopCounter_u32 );
        fprintf(outputFile, formatString, tableEntry_u32 );
        if ( loopCounter_u32 != (CRC_TABLE_SIZE - 1) )
        {
            fprintf(outputFile, " , ");
        }
        if ( ((loopCounter_u32 + 1) % valuesPerLine_u32) == 0 )
        {
            fprintf(outputFile, "\n");
        }
    }
    fprintf(outputFile, "};\n");

    fprintf(outputFile, "\n");
    fprintf(outputFile, "/*****************************************************************/\n");
    fprintf(outputFile, "/* END OF THE CRC LOOKUP TABLE                                   */\n");
    fprintf(outputFile, "/*****************************************************************/\n");

    if ( fclose( outputFile ) != 0 )
    {
        return CRC_TABLE_ERR_FILE_CLOSE;
    }

    return CRC_TABLE_OK;
}

uint32_t CRC_CalculateTableEntry ( CRC_Generator_t *crcGen, uint32_t index_u32 )
{
 uint32_t loopCounter_u32;
 uint32_t tableEntry_u32;
 uint32_t topbit_u32 = ( 1 << (crcGen->CRC_Width - 1) );
 uint32_t inbyte_u32 = (uint32_t) index_u32;

 if ( crcGen->CRC_ReflectedInput )
 {
     inbyte_u32 = CRC_Reflect( inbyte_u32, CRC_BIT_PER_BYTE );
 }
 tableEntry_u32 = inbyte_u32 << ( crcGen->CRC_Width - CRC_BIT_PER_BYTE );

 for ( loopCounter_u32 = 0;  loopCounter_u32 < CRC_BIT_PER_BYTE ; loopCounter_u32++)
 {
    if ( tableEntry_u32 & topbit_u32 )
    {
        tableEntry_u32 = (tableEntry_u32 << 1) ^ crcGen->CRC_Polynomial;
    }
    else
    {
        tableEntry_u32 = (tableEntry_u32 << 1);
    }
 }

 if ( crcGen->CRC_ReflectedOutput )
 {
     tableEntry_u32 = CRC_Reflect( tableEntry_u32, crcGen->CRC_Width );
 }

 tableEntry_u32 &= crcGen->CRC_WidthMask;

 return tableEntry_u32;
}

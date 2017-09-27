/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file FunctionLib.h
* This is the Function Lib module header file
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

#ifndef _FUNCTION_LIB_H_
#define _FUNCTION_LIB_H_

#include "EmbeddedTypes.h"

/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */

#ifndef gUseToolchainMemFunc_d
#define gUseToolchainMemFunc_d 0
#endif

#ifndef gFLib_CheckBufferOverflow_d
#define gFLib_CheckBufferOverflow_d 0
#endif

#define FLib_MemSet16 FLib_MemSet

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */

#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
* \brief  Copy the content of one memory block to another. The amount of data to copy
*         must be specified in number of bytes.
*
* \param[out] pDst   Pointer to destination memory block
* \param[in] pSrc    Pointer to source memory block
* \param[in] cBytes  Number of bytes to copy
*
********************************************************************************** */
void FLib_MemCpy (void* pDst,
                  void* pSrc,
                  uint32_t cBytes
                  );

void FLib_MemCpyAligned32bit (void* to_ptr,
                              void* from_ptr,
                              register uint32_t number_of_bytes);

void FLib_MemCpyDir (void* pBuf1,
                     void* pBuf2,
                     bool_t dir,
                     uint32_t n);


/*! *********************************************************************************
* \brief  Copy bytes. The byte at index i from the source buffer is copied to index
*         ((n-1) - i) in the destination buffer (and vice versa).
*
* \param[out] pDst   Pointer to destination memory block
* \param[in] pSrc    Pointer to source memory block
* \param[in] cBytes  Number of bytes to copy
*
********************************************************************************** */
void FLib_MemCpyReverseOrder (void* pDst,
                              void* pSrc,
                              uint32_t cBytes
                             );


/*! *********************************************************************************
* \brief  Compare two memory blocks. The number of bytes to compare must be specified. 
*         If the blocks are equal byte by byte, the function returns TRUE, 
*         and FALSE otherwise.
*
* \param[in] pData1  First memory block to compare
* \param[in] pData2  Second memory block to compare
* \param[in] cBytes  Number of bytes to compare
*
* \return  TRUE if memory areas are equal. FALSE othwerwise.
*
********************************************************************************** */
bool_t FLib_MemCmp (void* pData1,
                    void* pData2,
                    uint32_t cBytes
                   );


/*! *********************************************************************************
* \brief  Reset bytes in a memory block to a certain value. The value, and the number
*         of bytes to be set, are supplied as arguments.
*
* \param[in] pData   Pointer to memory block to reset
* \param[in] value   Value that memory block will be set to
* \param[in] cBytes  Number of bytes to set
*
********************************************************************************** */
 void FLib_MemSet (void* pData,
                   uint8_t value,
                   uint32_t cBytes
                  );


/*! *********************************************************************************
* \brief Copy bytes, possibly into the same overlapping memory as it is taken from
*
* \param[out] pDst   Pointer to destination memory block
* \param[in] pSrc    Pointer to source memory block
* \param[in] cBytes  Number of bytes to copy
*
********************************************************************************** */
void FLib_MemInPlaceCpy (void* pDst,
                         void* pSrc,
                         uint32_t cBytes
                        );


/*! *********************************************************************************
* \brief  Copies a 16bit value to an unaligned a memory block.
*
* \param[out] pDst   Pointer to destination memory block
* \param[in] val16   The 16-bit value to be copied
*
********************************************************************************** */
void FLib_MemCopy16Unaligned (void* pDst, 
                              uint16_t val16
                             );


/*! *********************************************************************************
* \brief  Copies a 32bit value to an unaligned a memory block.
*
* \param[out] pDst   Pointer to destination memory block
* \param[in] val32   The 32-bit value to be copied
*
********************************************************************************** */
void FLib_MemCopy32Unaligned (void* pDst,
                              uint32_t val32
                             );


/*! *********************************************************************************
* \brief  Copies a 64bit value to an unaligned a memory block.
*
* \param[out] pDst   Pointer to destination memory block
* \param[in] val64   The 64-bit value to be copied
*
********************************************************************************** */
void FLib_MemCopy64Unaligned (void* pDst,
                              uint64_t val64
                             );


/*! *********************************************************************************
* \brief Add an offset to a pointer.
*
* \param[out] pPtr   Pointer to the pointer to be updated
* \param[in] offset  The offset(in bytes) to be added
*
********************************************************************************** */
void FLib_AddOffsetToPointer (void** pPtr,
                              uint32_t offset);

#define FLib_AddOffsetToPtr(pPtr,offset) FLib_AddOffsetToPointer((void**)(pPtr),(offset))


/*! *********************************************************************************
* \brief  This function returns the length of a NULL terminated string.
*
* \param[in]  str  A NULL terminated string
*
* \return  the size of string in bytes
*
********************************************************************************** */
uint32_t FLib_StrLen(char *str);


/*! *********************************************************************************
* \brief  Compare two bytes.
*
* \param[in] pCmp1  pointer to the first 2-byte compare value
* \param[in] pCmp2  pointer to the second 2-byte compare value
*
* \return  TRUE if the two bytes are equal, and FALSE otherwise.
*
********************************************************************************** */
#define FLib_Cmp2Bytes(pCmp1, pCmp2) ((((uint8_t *)(pCmp1))[0] == ((uint8_t *)(pCmp2))[0]) && \
                                      (((uint8_t *)(pCmp1))[1] == ((uint8_t *)(pCmp2))[1]))


/*! *********************************************************************************
* \brief  Returns the maximum value of arguments a and b.
*
* \return  The maximum value of arguments a and b
*
* \remarks
*   The primitive should must be implemented as a macro, as it should be possible to
*   evaluate the result on compile time if the arguments are constants.
*
********************************************************************************** */
#define FLib_GetMax(a,b)    (((a) > (b)) ? (a) : (b))


/*! *********************************************************************************
* \brief  Returns the minimum value of arguments a and b.
*
* \return  The minimum value of arguments a and b
*
* \remarks
*   The primitive should must be implemented as a macro, as it should be possible to
*   evaluate the result on compile time if the arguments are constants.
*
********************************************************************************** */
#define FLib_GetMin(a,b)    (((a) < (b)) ? (a) : (b))

#ifdef __cplusplus
}
#endif

#endif /* _FUNCTION_LIB_H_ */

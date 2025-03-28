/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : Tx1.h
**     Project     : FRDM-K22F_USB_CDC_FreeRTOS_PEx
**     Processor   : MK22FN512VDC12
**     Component   : RingBuffer
**     Version     : Component 01.054, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2022-05-05, 14:58, # CodeGen: 9
**     Abstract    :
**         This component implements a ring buffer for different integer data type.
**     Settings    :
**          Component name                                 : Tx1
**          Buffer Size                                    : 32
**     Contents    :
**         Clear           - void Tx1_Clear(void);
**         Put             - uint8_t Tx1_Put(Tx1_ElementType elem);
**         Get             - uint8_t Tx1_Get(Tx1_ElementType *elemP);
**         Peek            - uint8_t Tx1_Peek(Tx1_BufSizeType index, Tx1_ElementType *elemP);
**         Update          - uint8_t Tx1_Update(Tx1_BufSizeType index, Tx1_ElementType *elemP);
**         Putn            - uint8_t Tx1_Putn(Tx1_ElementType *elem, Tx1_BufSizeType nof);
**         Getn            - uint8_t Tx1_Getn(Tx1_ElementType *buf, Tx1_BufSizeType nof);
**         Compare         - uint8_t Tx1_Compare(Tx1_BufSizeType index, Tx1_ElementType *elemP,...
**         Delete          - uint8_t Tx1_Delete(void);
**         NofElements     - Tx1_BufSizeType Tx1_NofElements(void);
**         NofFreeElements - Tx1_BufSizeType Tx1_NofFreeElements(void);
**         Deinit          - void Tx1_Deinit(void);
**         Init            - void Tx1_Init(void);
**
** * Copyright (c) 2014-2020, Erich Styger
**  * Web:         https://mcuoneclipse.com
**  * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**  * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**  * All rights reserved.
**  *
**  * Redistribution and use in source and binary forms, with or without modification,
**  * are permitted provided that the following conditions are met:
**  *
**  * - Redistributions of source code must retain the above copyright notice, this list
**  *   of conditions and the following disclaimer.
**  *
**  * - Redistributions in binary form must reproduce the above copyright notice, this
**  *   list of conditions and the following disclaimer in the documentation and/or
**  *   other materials provided with the distribution.
**  *
**  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**  * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file Tx1.h
** @version 01.00
** @brief
**         This component implements a ring buffer for different integer data type.
*/         
/*!
**  @addtogroup Tx1_module Tx1 module documentation
**  @{
*/         

/* MODULE Tx1. */

#include "Tx1.h"

#if Tx1_CONFIG_REENTRANT
  #define Tx1_DEFINE_CRITICAL() CS1_CriticalVariable()
  #define Tx1_ENTER_CRITICAL()  CS1_EnterCritical()
  #define Tx1_EXIT_CRITICAL()   CS1_ExitCritical()
#else
  #define Tx1_DEFINE_CRITICAL() /* nothing */
  #define Tx1_ENTER_CRITICAL()  /* nothing */
  #define Tx1_EXIT_CRITICAL()   /* nothing */
#endif
static Tx1_ElementType Tx1_buffer[Tx1_CONFIG_BUF_SIZE]; /* ring buffer */
static Tx1_BufSizeType Tx1_inIdx;  /* input index */
static Tx1_BufSizeType Tx1_outIdx; /* output index */
static Tx1_BufSizeType Tx1_inSize; /* size data in buffer */
/*
** ===================================================================
**     Method      :  Put (component RingBuffer)
**
**     Description :
**         Puts a new element into the buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**         elem            - New element to be put into the buffer
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t Tx1_Put(Tx1_ElementType elem)
{
  uint8_t res = ERR_OK;
  Tx1_DEFINE_CRITICAL();

  Tx1_ENTER_CRITICAL();
  if (Tx1_inSize==Tx1_CONFIG_BUF_SIZE) {
    res = ERR_TXFULL;
  } else {
    Tx1_buffer[Tx1_inIdx] = elem;
    Tx1_inIdx++;
    if (Tx1_inIdx==Tx1_CONFIG_BUF_SIZE) {
      Tx1_inIdx = 0;
    }
    Tx1_inSize++;
  }
  Tx1_EXIT_CRITICAL();
  return res;
}

/*
** ===================================================================
**     Method      :  Putn (component RingBuffer)
**
**     Description :
**         Put a number new element into the buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * elem            - Pointer to new elements to be put into
**                           the buffer
**         nof             - number of elements
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t Tx1_Putn(Tx1_ElementType *elem, Tx1_BufSizeType nof)
{
  uint8_t res = ERR_OK;

  while(nof>0) {
    res = Tx1_Put(*elem);
    if (res!=ERR_OK) {
      break;
    }
    elem++; nof--;
  }
  return res;
}

/*
** ===================================================================
**     Method      :  Get (component RingBuffer)
**
**     Description :
**         Removes an element from the buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**       * elemP           - Pointer to where to store the received
**                           element
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t Tx1_Get(Tx1_ElementType *elemP)
{
  uint8_t res = ERR_OK;
  Tx1_DEFINE_CRITICAL();

  Tx1_ENTER_CRITICAL();
  if (Tx1_inSize==0) {
    res = ERR_RXEMPTY;
  } else {
    *elemP = Tx1_buffer[Tx1_outIdx];
    Tx1_inSize--;
    Tx1_outIdx++;
    if (Tx1_outIdx==Tx1_CONFIG_BUF_SIZE) {
      Tx1_outIdx = 0;
    }
  }
  Tx1_EXIT_CRITICAL();
  return res;
}

/*
** ===================================================================
**     Method      :  Getn (component RingBuffer)
**
**     Description :
**         Get a number elements into a buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * buf             - Pointer to buffer where to store the
**                           elements
**         nof             - number of elements
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t Tx1_Getn(Tx1_ElementType *buf, Tx1_BufSizeType nof)
{
  uint8_t res = ERR_OK;

  while(nof>0) {
    res = Tx1_Get(buf);
    if (res!=ERR_OK) {
      break;
    }
    buf++; nof--;
  }
  return res;
}

/*
** ===================================================================
**     Method      :  NofElements (component RingBuffer)
**
**     Description :
**         Returns the actual number of elements in the buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of elements in the buffer.
** ===================================================================
*/
Tx1_BufSizeType Tx1_NofElements(void)
{
  return Tx1_inSize;
}

/*
** ===================================================================
**     Method      :  NofFreeElements (component RingBuffer)
**
**     Description :
**         Returns the actual number of free elements/space in the
**         buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of elements in the buffer.
** ===================================================================
*/
Tx1_BufSizeType Tx1_NofFreeElements(void)
{
  return (Tx1_BufSizeType)(Tx1_CONFIG_BUF_SIZE-Tx1_inSize);
}

/*
** ===================================================================
**     Method      :  Init (component RingBuffer)
**
**     Description :
**         Initializes the data structure
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Tx1_Init(void)
{
  Tx1_inIdx = 0;
  Tx1_outIdx = 0;
  Tx1_inSize = 0;
}

/*
** ===================================================================
**     Method      :  Clear (component RingBuffer)
**
**     Description :
**         Clear (empty) the ring buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Tx1_Clear(void)
{
  Tx1_DEFINE_CRITICAL();

  Tx1_ENTER_CRITICAL();
  Tx1_Init();
  Tx1_EXIT_CRITICAL();
}

/*
** ===================================================================
**     Method      :  Peek (component RingBuffer)
**
**     Description :
**         Returns an element of the buffer without removiing it.
**     Parameters  :
**         NAME            - DESCRIPTION
**         index           - Index of element. 0 peeks the top
**                           element, 1 the next, and so on.
**       * elemP           - Pointer to where to store the received
**                           element
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t Tx1_Peek(Tx1_BufSizeType index, Tx1_ElementType *elemP)
{
  uint8_t res = ERR_OK;
  int idx; /* index inside ring buffer */
  Tx1_DEFINE_CRITICAL();

  Tx1_ENTER_CRITICAL();
  if (index>=Tx1_CONFIG_BUF_SIZE) {
    res = ERR_OVERFLOW; /* asking for an element outside of ring buffer size */
  } else if (index<Tx1_inSize) {
    idx = (Tx1_outIdx+index)%Tx1_CONFIG_BUF_SIZE;
    *elemP = Tx1_buffer[idx];
  } else { /* asking for an element which does not exist */
    res = ERR_RXEMPTY;
  }
  Tx1_EXIT_CRITICAL();
  return res;
}

/*
** ===================================================================
**     Method      :  Compare (component RingBuffer)
**
**     Description :
**         Compares the elements in the buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**         index           - Index of element. 0 peeks the top
**                           element, 1 the next, and so on.
**       * elemP           - Pointer to elements to compare with
**         nof             - number of elements to compare
**     Returns     :
**         ---             - zero if elements are the same, -1 otherwise
** ===================================================================
*/
uint8_t Tx1_Compare(Tx1_BufSizeType index, Tx1_ElementType *elemP, Tx1_BufSizeType nof)
{
  uint8_t cmpResult = 0;
  uint8_t res;
  Tx1_ElementType val;

  while(nof>0) {
    res = Tx1_Peek(index, &val);
    if (res!=ERR_OK) { /* general failure? */
      cmpResult = (uint8_t)-1; /* no match */
      break;
    }
    if (val!=*elemP) { /* mismatch */
      cmpResult = (uint8_t)-1; /* no match */
      break;
    }
    elemP++; index++; nof--;
  }

  return cmpResult;
}

/*
** ===================================================================
**     Method      :  Deinit (component RingBuffer)
**
**     Description :
**         Driver de-initialization
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/**
void Tx1_Deinit(void)
{
  ** Function is implemented as macro in the header file
}
*/
/*
** ===================================================================
**     Method      :  Delete (component RingBuffer)
**
**     Description :
**         Removes an element from the buffer
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t Tx1_Delete(void)
{
  uint8_t res = ERR_OK;
  Tx1_DEFINE_CRITICAL();

  Tx1_ENTER_CRITICAL();
  if (Tx1_inSize==0) {
    res = ERR_RXEMPTY;
  } else {
    Tx1_inSize--;
    Tx1_outIdx++;
    if (Tx1_outIdx==Tx1_CONFIG_BUF_SIZE) {
      Tx1_outIdx = 0;
    }
  }
  Tx1_EXIT_CRITICAL();
  return res;
}

/*
** ===================================================================
**     Method      :  Update (component RingBuffer)
**
**     Description :
**         Updates the data of an element.
**     Parameters  :
**         NAME            - DESCRIPTION
**         index           - Index of element. 0 peeks the top
**                           element, 1 the next, and so on.
**       * elemP           - Pointer to where to store the received
**                           element
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t Tx1_Update(Tx1_BufSizeType index, Tx1_ElementType *elemP)
{
  uint8_t res = ERR_OK;
  int idx; /* index inside ring buffer */
  Tx1_DEFINE_CRITICAL();

  Tx1_ENTER_CRITICAL();
  if (index>=Tx1_CONFIG_BUF_SIZE) {
    res = ERR_OVERFLOW; /* asking for an element outside of ring buffer size */
  } else if (index<Tx1_inSize) {
    idx = (Tx1_outIdx+index)%Tx1_CONFIG_BUF_SIZE;
    Tx1_buffer[idx] = *elemP; /* replace element */
  } else { /* asking for an element which does not exist */
    res = ERR_RXEMPTY;
  }
  Tx1_EXIT_CRITICAL();
  return res;
}

/* END Tx1. */

/*!
** @}
*/

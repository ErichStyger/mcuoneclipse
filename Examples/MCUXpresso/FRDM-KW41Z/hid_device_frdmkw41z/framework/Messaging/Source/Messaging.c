/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file Messaging.c
* This is a source file for the messaging module.
* It contains the implementation of inter-task messaging.
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

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "EmbeddedTypes.h"
#include "MemManager.h"
#include "Messaging.h"
#include "fsl_os_abstraction.h"

/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
/*! *********************************************************************************
* \brief     Links element to the tail of the list for the message system. 
*
* \param[in] list - pointer to the list to insert into.
*            pMsg - data block to add
*
* \return void.
*
* \pre Buffer must be allocated using MemManager.
*
* \post
*
* \remarks
*
********************************************************************************** */
listStatus_t ListAddTailMsg(listHandle_t list, void* pMsg)
{
  pMsg = (listHeader_t *)pMsg - 1;
  return ListAddTail(list, (listElementHandle_t)pMsg);
}

/*! *********************************************************************************
* \brief     Links element to the head of the list for the message system. 
*
* \param[in] list - pointer to the list to insert into.
*            pMsg - data block to add
*
* \return listStatus_t.
*
* \pre Buffer must be allocated using MemManager.
*
* \post
*
* \remarks
*
********************************************************************************** */
listStatus_t ListAddHeadMsg(listHandle_t list, void* pMsg)
{
  pMsg = (listHeader_t *)pMsg - 1;
  return ListAddHead(list, (listElementHandle_t)pMsg);
}

/*! *********************************************************************************
* \brief     Links the new element before a specified element. 
*
* \param[in] pMsg - current element from list
*            pNewMsg - new element to add
*
* \return listStatus_t.
*
* \pre Buffer must be allocated using MemManager.
*
* \post
*
* \remarks
*
********************************************************************************** */
listStatus_t ListAddPrevMsg( void* pMsg, void* pNewMsg )
{
  listHeader_t *pElem = (listHeader_t*) pMsg - 1;
  listHeader_t *pNewElem  = (listHeader_t*) pNewMsg - 1;
      
  return ListAddPrevElement((listElementHandle_t)pElem, (listElementHandle_t)pNewElem);            
}


/*! *********************************************************************************
* \brief     Unlinks element from the head of the list for the message system. 
*
* \param[in] list - pointer to the list to remove from.
*
* \return NULL if list is empty.
*         pointer to the data block if removal was successful.
*
* \pre Buffer must be allocated using MemManager.
*
* \post
*
* \remarks
*
********************************************************************************** */
void *ListRemoveHeadMsg(listHandle_t list)
{
  void *buffer;
  
  buffer = ListRemoveHead(list);
  return buffer ? (listHeader_t *)buffer+1 : buffer;
}

/*! *********************************************************************************
* \brief     Returns a pointer to the head of the list for the message system. 
*
* \param[in] list - pointer to the list
*
* \return NULL if list is empty.
*         pointer to the data block
*
* \pre
*
* \post
*
* \remarks
*
********************************************************************************** */
void *ListGetHeadMsg( listHandle_t list )
{
    listHeader_t *p;

    OSA_InterruptDisable();
    
    if( list->head )
    {
        p = (listHeader_t*)(list->head) + 1;
    }
    else
    {
        p = NULL;
    }
    
    OSA_InterruptEnable();

    return p;
}

/*! *********************************************************************************
* \brief     Returns a pointer to the data of the next message in the list.
*
* \param[in] pMsg - pointer to the data of the current message.
*
* \return NULL if buffer is the last element of the list.
*         pointer to the next data block if exists.
*
* \pre Buffer must be allocated using MemManager.
*
* \post
*
* \remarks
*
********************************************************************************** */
void *ListGetNextMsg( void* pMsg )
{
    listHeader_t *p;

    OSA_InterruptDisable();
    
    p = (listHeader_t*)pMsg - 1;

    if( p->link.next )
    {
        p = (listHeader_t*)(p->link.next) + 1;
    }
    else
    {
        p = NULL;
    }

    OSA_InterruptEnable();
    
    return p;
}

/*! *********************************************************************************
* \brief     Unlik the specified element from the list.
*
* \param[in] pMsg - pointer to the data of the current message.
*
* \return None.
*
* \pre Buffer must be allocated using MemManager.
*
* \post
*
* \remarks
*
********************************************************************************** */
listStatus_t ListRemoveMsg( void* pMsg )
{
    listHeader_t *p = (listHeader_t*)pMsg - 1;

    return ListRemoveElement( (listElementHandle_t)p );
}

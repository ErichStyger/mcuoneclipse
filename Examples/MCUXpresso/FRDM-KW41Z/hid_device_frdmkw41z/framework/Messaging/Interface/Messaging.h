/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file Messaging.h
* This is a header file for the messaging module.
* It contains the type definitions of inter-task messaging.
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

#ifndef _MESSAGING_H
#define _MESSAGING_H


/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "EmbeddedTypes.h"
#include "GenericList.h"
#include "MemManager.h"

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/
#define  anchor_t        list_t
#define  msgQueue_t      list_t

/************************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
************************************************************************************/
/* Put a message in a queue. */
#define MSG_Queue(anchor, element) ListAddTailMsg((anchor), (element))
#define MSG_QueueHead(anchor, element) ListAddHeadMsg((anchor), (element))

/* Get a message from a queue. Returns NULL if no messages in queue. */
#define MSG_DeQueue(anchor) ListRemoveHeadMsg(anchor)

/* Check if a message is pending in a queue. Returns */
/* TRUE if any pending messages, and FALSE otherwise. */
#define MSG_Pending(anchor) ((anchor)->head != 0)

#define MSG_InitQueue(anchor) ListInitMsg(anchor)
#define List_ClearAnchor(anchor) ListInitMsg(anchor)

#define  MSG_Alloc(element)         MEM_BufferAlloc(element)
#define  MSG_AllocType(type)        MEM_BufferAlloc(sizeof(type))
#define  MM_Free                    MEM_BufferFree
#define  MSG_Free(element)          MEM_BufferFree(element)
#define  MSG_FreeQueue(anchor)      while(MSG_Pending(anchor)) { MSG_Free(MSG_DeQueue(anchor)); }

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
#define ListInitMsg(listPtr) ListInit((listPtr), 0)
listStatus_t ListAddTailMsg    ( listHandle_t list, void* pMsg );
listStatus_t ListAddHeadMsg    ( listHandle_t list, void* pMsg );
listStatus_t ListAddPrevMsg    ( void* pMsg, void* pNewMsg );
listStatus_t ListRemoveMsg     ( void* pMsg );
void *ListRemoveHeadMsg( listHandle_t list );
void *ListGetHeadMsg   ( listHandle_t list );
void *ListGetNextMsg   ( void* pMsg );

/*================================================================================================*/

#endif  /* _MESSAGING_H */

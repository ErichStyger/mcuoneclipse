/**
 * \file
 * \brief This implements a queue/buffer for radio messages
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module uses queues to retrieve and store radio messages.
 */

#include "RNetConf.h"
#if PL_HAS_RADIO
#include "RMSG.h"
#include "FRTOS1.h"
#include "WAIT1.h"
#if PL_HAS_RTOS_TRACE
  #include "RTOSTRC1.h"
#endif
#include "RPHY.h"

/* Configuration for tx and rx queues */
#define RMSG_QUEUE_RX_NOF_ITEMS   (RNET_CONFIG_MSG_QUEUE_NOF_RX_ITEMS) /* number of items in the queue */
#define RMSG_QUEUE_TX_NOF_ITEMS   (RNET_CONFIG_MSG_QUEUE_NOF_TX_ITEMS) /* number of items in the queue */
#define RMSG_QUEUE_PUT_WAIT       (RNET_CONFIG_MSG_QUEUE_PUT_BLOCK_TIME_MS) /* blocking time for putting messages into queue */

static QueueHandle_t RMSG_MsgRxQueue, RMSG_MsgTxQueue; /* queue for messages,  format is: kind(8bit) dataSize(8bit) data */

uint8_t RMSG_FlushRxQueue(void) {
  if (FRTOS1_xQueueReset(RMSG_MsgRxQueue)!=pdPASS) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t RMSG_FlushTxQueue(void) {
  if (xQueueReset(RMSG_MsgTxQueue)!=pdPASS) {
    return ERR_FAILED;
  }
  return ERR_OK;
}


uint8_t RMSG_QueuePut(uint8_t *buf, size_t bufSize, uint8_t payloadSize, bool fromISR, bool isTx, RPHY_FlagsType flags) {
  /* data format is: dataSize(8bit) data */
  uint8_t res = ERR_OK;
  QueueHandle_t queue;

  if (payloadSize>RPHY_PAYLOAD_SIZE) {
    return ERR_OVERFLOW; /* more data than can fit into payload! */
  }
  if (bufSize!=RPHY_BUFFER_SIZE) {
    return ERR_FAILED; /* must be exactly this buffer size!!! */
  }
  if (isTx) {
    queue = RMSG_MsgTxQueue;
  } else {
    queue = RMSG_MsgRxQueue;
  }
  RPHY_BUF_FLAGS(buf) = flags;
  RPHY_BUF_SIZE(buf) = payloadSize;
  if (fromISR) {
    signed portBASE_TYPE pxHigherPriorityTaskWoken;
    
    if (FRTOS1_xQueueSendToBackFromISR(queue, buf, &pxHigherPriorityTaskWoken)!=pdTRUE) {
      /* was not able to send to the queue. Well, not much we can do here... */
      res = ERR_BUSY;
    }
  } else {
    if (xQueueSendToBack(queue, buf, RMSG_QUEUE_PUT_WAIT)!=pdTRUE) {
      res = ERR_BUSY;
    }
  }
  return res;
}

uint8_t RMSG_GetTxMsg(uint8_t *buf, size_t bufSize) {
  if (bufSize<RPHY_BUFFER_SIZE) {
    return ERR_OVERFLOW; /* not enough space in buffer */
  }
  if (xQueueReceive(RMSG_MsgTxQueue, buf, 0)==pdPASS) {
    /* received message from queue */
    return ERR_OK;
  }
  return ERR_RXEMPTY;
}

uint8_t RMSG_GetRxMsg(uint8_t *buf, size_t bufSize) {
  /* first byte in the queue is the size of the item */
  if (bufSize<RPHY_BUFFER_SIZE) {
    return ERR_OVERFLOW; /* not enough space in buffer */
  }
  if (FRTOS1_xQueueReceive(RMSG_MsgRxQueue, buf, 0)==pdPASS) { /* immediately returns if queue is empty */
    /* received message from queue */
    return ERR_OK;
  }
  return ERR_RXEMPTY;
}

uint8_t RMSG_QueueTxMsg(uint8_t *buf, size_t bufSize, uint8_t payloadSize, RPHY_FlagsType flags) {
  return RMSG_QueuePut(buf, bufSize, payloadSize, FALSE, TRUE, flags);
}

uint8_t RMSG_QueueRxMsg(uint8_t *buf, size_t bufSize, uint8_t payloadSize, RPHY_FlagsType flags) {
  return RMSG_QueuePut(buf, bufSize, payloadSize, FALSE, FALSE, flags);
}

void RMSG_Deinit(void) {
}

void RMSG_Init(void) {
  RMSG_MsgRxQueue = FRTOS1_xQueueCreate(RMSG_QUEUE_RX_NOF_ITEMS, RPHY_BUFFER_SIZE);
#if PL_HAS_RTOS_TRACE
  RTOSTRC1_vTraceSetQueueName(RMSG_MsgRxQueue, "RadioRxMsg");
#endif
  if (RMSG_MsgRxQueue==NULL) { /* queue creation failed! */
    for(;;) {} /* not enough memory? */
  }
  RMSG_MsgTxQueue = FRTOS1_xQueueCreate(RMSG_QUEUE_TX_NOF_ITEMS, RPHY_BUFFER_SIZE);
#if PL_HAS_RTOS_TRACE
  RTOSTRC1_vTraceSetQueueName(RMSG_MsgTxQueue, "RadioTxMsg");
#endif
  if (RMSG_MsgTxQueue==NULL) { /* queue creation failed! */
    for(;;) {} /* not enough memory? */
  }
}

#endif /* PL_HAS_RADIO */

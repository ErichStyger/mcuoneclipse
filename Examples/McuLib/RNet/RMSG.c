/**
 * \file
 * \brief This implements a queue/buffer for radio messages
 * \author (c) 2013-2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module uses queues to retrieve and store radio messages.
 */

#include "McuRNetConfig.h"
#if McuRNET_CONFIG_IS_ENABLED
#include "Radio.h"
#include "RMSG.h"
#include "McuRTOS.h"
#include "RPHY.h"

/* Configuration for tx and rx queues */
#define RMSG_QUEUE_RX_NOF_ITEMS   (RNET_CONFIG_MSG_QUEUE_NOF_RX_ITEMS) /* number of items in the queue */
#define RMSG_QUEUE_TX_NOF_ITEMS   (RNET_CONFIG_MSG_QUEUE_NOF_TX_ITEMS) /* number of items in the queue */
#define RMSG_QUEUE_PUT_WAIT       (RNET_CONFIG_MSG_QUEUE_PUT_BLOCK_TIME_TICKS) /* blocking time (ticks!) for putting messages into queue */

static QueueHandle_t RMSG_MsgRxQueue, RMSG_MsgTxQueue; /* queue for messages,  format is: kind(8bit) dataSize(8bit) data */

unsigned int RMSG_RxQueueNofItems(void) {
  return (unsigned int)McuRTOS_uxQueueMessagesWaiting(RMSG_MsgRxQueue);
}

unsigned int RMSG_TxQueueNofItems(void) {
  return (unsigned int)McuRTOS_uxQueueMessagesWaiting(RMSG_MsgTxQueue);
}

uint8_t RMSG_FlushRxQueue(void) {
  if (McuRTOS_xQueueReset(RMSG_MsgRxQueue)!=pdPASS) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t RMSG_FlushTxQueue(void) {
  if (McuRTOS_xQueueReset(RMSG_MsgTxQueue)!=pdPASS) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t RMSG_QueuePut(uint8_t *buf, size_t bufSize, uint8_t payloadSize, bool fromISR, bool isTx, bool toBack, RPHY_FlagsType flags) {
  /* data format is: dataSize(8bit) data */
  uint8_t res = ERR_OK;
  QueueHandle_t queue;
  BaseType_t qRes;

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
    BaseType_t pxHigherPriorityTaskWoken;
    
    if (toBack) {
      qRes = McuRTOS_xQueueSendToBackFromISR(queue, buf, &pxHigherPriorityTaskWoken);
    } else {
      qRes = McuRTOS_xQueueSendToFrontFromISR(queue, buf, &pxHigherPriorityTaskWoken);
    }
    if (qRes!=pdTRUE) {
      /* was not able to send to the queue. Well, not much we can do here... */
      res = ERR_BUSY;
    } else {
      if (isTx) {
        RADIO_NotifyFromInterrupt(RADIO_FLAG_TX_REQUEST, &pxHigherPriorityTaskWoken);
      }
    }
  } else {
    if (toBack) {
      qRes = McuRTOS_xQueueSendToBack(queue, buf, RMSG_QUEUE_PUT_WAIT);
    } else {
      qRes = McuRTOS_xQueueSendToFront(queue, buf, RMSG_QUEUE_PUT_WAIT);
    }
    if (qRes!=pdTRUE) {
      res = ERR_BUSY;
    } else {
      if (isTx) {
        RADIO_Notify(RADIO_FLAG_TX_REQUEST);
      }
    }
  }
  return res;
}

uint8_t RMSG_PutRetryTxMsg(uint8_t *buf, size_t bufSize) {
  if (bufSize<RPHY_BUFFER_SIZE) {
    return ERR_OVERFLOW; /* not enough space in buffer */
  }
  if (McuRTOS_xQueueSendToFront(RMSG_MsgTxQueue, buf, 0)==pdPASS) {
    RADIO_Notify(RADIO_FLAG_TX_REQUEST);
    return ERR_OK; /* success adding message to queue */
  }
  return ERR_RXEMPTY;
}

uint8_t RMSG_GetTxMsg(uint8_t *buf, size_t bufSize) {
  if (bufSize<RPHY_BUFFER_SIZE) {
    return ERR_OVERFLOW; /* not enough space in buffer */
  }
  if (McuRTOS_xQueueReceive(RMSG_MsgTxQueue, buf, 0)==pdPASS) {
    return ERR_OK; /* received message from queue */
  }
  return ERR_RXEMPTY;
}

uint8_t RMSG_GetRxMsg(uint8_t *buf, size_t bufSize) {
  /* first byte in the queue is the size of the item */
  if (bufSize<RPHY_BUFFER_SIZE) {
    return ERR_OVERFLOW; /* not enough space in buffer */
  }
  if (McuRTOS_xQueueReceive(RMSG_MsgRxQueue, buf, 0)==pdPASS) { /* immediately returns if queue is empty */
    return ERR_OK; /* received message from queue */
  }
  return ERR_RXEMPTY;
}

uint8_t RMSG_QueueTxMsg(uint8_t *buf, size_t bufSize, uint8_t payloadSize, RPHY_FlagsType flags) {
  return RMSG_QueuePut(buf, bufSize, payloadSize, FALSE, TRUE, TRUE, flags);
}

uint8_t RMSG_QueueRxMsg(uint8_t *buf, size_t bufSize, uint8_t payloadSize, RPHY_FlagsType flags) {
  return RMSG_QueuePut(buf, bufSize, payloadSize, FALSE, FALSE, TRUE, flags);
}

static uint8_t RMSG_PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"rmsg", (unsigned char*)"Group of rmsg commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows radio help or status\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t RMSG_PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[32];

  McuShell_SendStatusStr((unsigned char*)"rmsg", (unsigned char*)"\r\n", io->stdOut);

  McuUtility_Num32uToStr(buf, sizeof(buf), RMSG_RxQueueNofItems());
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" items\r\n");
  McuShell_SendStatusStr((unsigned char*)"  rx", buf, io->stdOut);
  McuUtility_Num32uToStr(buf, sizeof(buf), RMSG_TxQueueNofItems());
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" items\r\n");
  McuShell_SendStatusStr((unsigned char*)"  tx", buf, io->stdOut);
  return ERR_OK;
}

uint8_t RMSG_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, (char*)"rmsg help")==0) {
    *handled = TRUE;
    return RMSG_PrintHelp(io);
  } else if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_STATUS)==0 || McuUtility_strcmp((char*)cmd, (char*)"rmsg status")==0) {
    *handled = TRUE;
    return RMSG_PrintStatus(io);
  }
  return res;
}

void RMSG_Deinit(void) {
  McuRTOS_vQueueUnregisterQueue(RMSG_MsgRxQueue);
  McuRTOS_vQueueDelete(RMSG_MsgRxQueue);
  RMSG_MsgRxQueue = NULL;

  McuRTOS_vQueueUnregisterQueue(RMSG_MsgTxQueue);
  McuRTOS_vQueueDelete(RMSG_MsgTxQueue);
  RMSG_MsgTxQueue = NULL;
}

void RMSG_Init(void) {
  RMSG_MsgRxQueue = McuRTOS_xQueueCreate(RMSG_QUEUE_RX_NOF_ITEMS, RPHY_BUFFER_SIZE);
  if (RMSG_MsgRxQueue==NULL) { /* queue creation failed! */
    for(;;) {} /* not enough memory? */
  }
  McuRTOS_vQueueAddToRegistry(RMSG_MsgRxQueue, "RadioRxMsg");
#if configUSE_TRACE_HOOKS
  vTraceSetQueueName(RMSG_MsgRxQueue, "RadioRxMsg");
#endif

  RMSG_MsgTxQueue = McuRTOS_xQueueCreate(RMSG_QUEUE_TX_NOF_ITEMS, RPHY_BUFFER_SIZE);
  if (RMSG_MsgTxQueue==NULL) { /* queue creation failed! */
    for(;;) {} /* not enough memory? */
  }
  McuRTOS_vQueueAddToRegistry(RMSG_MsgTxQueue, "RadioTxMsg");
#if configUSE_TRACE_HOOKS
  vTraceSetQueueName(RMSG_MsgTxQueue, "RadioTxMsg");
#endif
}

#endif /* McuRNET_CONFIG_IS_ENABLED */

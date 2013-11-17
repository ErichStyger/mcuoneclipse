/*
 * Application.c
 *
 *  Created on: Nov 15, 2013
 *      Author: tastyger
 */

#include "RStack.h"
#include "RApp.h"
#if PL_HAS_SHELL
#include "RStdIO.h"
#endif

/* type ID's for application messages */
#define RAPP_MSG_TYPE_STDIN   0x01
#define RAPP_MSG_TYPE_STDOUT  0x02
#define RAPP_MSG_TYPE_STDERR  0x03

#if PL_HAS_SHELL
static uint8_t HandleStdioMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled) {
  (void)srcAddr;
  switch(type) {
    case RAPP_MSG_TYPE_STDIN: /* <type><size><data */
      *handled = TRUE;
      return RSTDIO_AddToQueue(RSTDIO_QUEUE_RX_IN, data, size);
    case RAPP_MSG_TYPE_STDOUT: /* <type><size><data */
      *handled = TRUE;
      return RSTDIO_AddToQueue(RSTDIO_QUEUE_RX_OUT, data, size);
    case RAPP_MSG_TYPE_STDERR: /* <type><size><data */
      *handled = TRUE;
      return RSTDIO_AddToQueue(RSTDIO_QUEUE_RX_ERR, data, size);
    default:
      break;
  } /* switch */
  return ERR_OK;
}
#endif

static const RAPP_MsgHandler handlerTable[] = 
{
#if PL_HAS_SHELL
  HandleStdioMessage,
#endif
  NULL /* sentinel */
};

void APP_Run(void) {
  RSTACK_Init();
  RAPP_SetMessageHandlerTable(handlerTable);
  for(;;) {
#if PL_HAS_SHELL
    RSTDIO_Print(io); /* handle stdout/stderr messages coming in */
#endif
  }
}

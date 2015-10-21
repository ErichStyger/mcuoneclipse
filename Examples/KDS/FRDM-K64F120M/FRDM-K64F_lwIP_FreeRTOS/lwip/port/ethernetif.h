/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

#ifndef ETHERNETIF_H
#define ETHERNETIF_H

#include "lwip/err.h"
#include "fsl_enet_driver.h"

/*! @brief Define parameter for configuration*/
#define ENET_RXBD_NUM                 (8)
#define ENET_TXBD_NUM                 (4)
#define ENET_EXTRXBD_NUM              (4)
#define ENET_RXBUFF_SIZE        (kEnetMaxFrameSize)
#define ENET_TXBUFF_SIZE        (kEnetMaxFrameSize)
#define ENET_RXLARGEBUFF_NUM    (4)
#define ENET_RX_BUFFER_ALIGNMENT     (16)  
#define ENET_TX_BUFFER_ALIGNMENT     (16)
#define ENET_BD_ALIGNMENT            (16)
#define ENET_RXBuffSizeAlign(n)      ENET_ALIGN(n, ENET_RX_BUFFER_ALIGNMENT)    
#define ENET_TXBuffSizeAlign(n)      ENET_ALIGN(n, ENET_TX_BUFFER_ALIGNMENT) 

/*! @brief Define the Macro to get variable aligned on 16-bytes except IAR compiler*/
#if defined   (__GNUC__)        /* GNU Compiler */
  #ifndef __ALIGN_END
    #define __ALIGN_END    __attribute__ ((aligned (ENET_BD_ALIGNMENT)))
  #endif 
  #ifndef __ALIGN_BEGIN 
    #define __ALIGN_BEGIN
  #endif 
#else
  #ifndef __ALIGN_END
    #define __ALIGN_END
  #endif 
  #ifndef __ALIGN_BEGIN      
    #if defined   (__CC_ARM)      /* ARM Compiler */
      #define __ALIGN_BEGIN    __align(ENET_BD_ALIGNMENT)  
    #elif defined (__ICCARM__)    /* IAR Compiler */
      #define __ALIGN_BEGIN 
    #endif
  #endif
#endif

 
#if FSL_FEATURE_ENET_SUPPORT_PTP
#define ENET_PTP_TXTS_RING_LEN           (25)
#define ENET_PTP_RXTS_RING_LEN           (25)
#define ENET_PTP_L2RING_LEN            (15)
#define ENET_PTP_SYNC_MSG              (0)
#define ENET_PTP_DELAYREQ_MSG          (1)
#define ENET_PTP_ETHERNET_LAYER2_TEST  (1)
#define ENET_IPV4_VERSION              (4)
#endif
/* MAC address configuration. */
#define configMAC_ADDR0	0x00
#define configMAC_ADDR1	0xCF
#define configMAC_ADDR2	0x52
#define configMAC_ADDR3	0x35
#define configMAC_ADDR4	0x00
#define configMAC_ADDR5	0x01

#define ENET_OK 0U
#define ENET_ERROR 0xffU
#if !ENET_RECEIVE_ALL_INTERRUPT
#define RECV_TASK_STACK_SIZE  (800)
#define ENET_RECV_TASK_PRIO    1
#endif
extern enet_dev_if_t enetDevIf[];
err_t ethernetif_init(struct netif *netif);
uint32_t ethernetif_input(void *enetPtr, enet_mac_packet_buffer_t *packetBuffer);
void ENET_receive(task_param_t param);

#endif

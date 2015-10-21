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

#include <string.h>
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include <lwip/stats.h>
#include <lwip/snmp.h>
#include "netif/etharp.h"
#include "netif/ppp_oe.h"
#include "ethernetif.h"

#include "fsl_enet_hal.h"
#include "fsl_phy_driver.h"

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////
/* Define those to better describe your network interface. */
#define IFNAME0 'e'
#define IFNAME1 'n'

///////////////////////////////////////////////////////////////////////////////
// Variables
///////////////////////////////////////////////////////////////////////////////
enet_config_rmii_t rmiiCfg = {kEnetCfgRmii, kEnetCfgSpeed100M, kEnetCfgFullDuplex, false, false};
enet_mac_config_t g_enetMacCfg[ENET_INSTANCE_COUNT] =
{
{
    kEnetMacNormalMode,  /*!< ENET normal mode*/
    NULL,      /*!< ENET mac address*/
    &rmiiCfg,  /*!< ENET rmii interface*/
    /*!< enet mac control flag recommended to use enet_mac_control_flag_t
      it is special control for loop mode, sleep mode, crc forward/terminate etc*/
    kEnetRxCrcFwdEnable | kEnetTxCrcBdEnable | kEnetMacEnhancedEnable,
    NULL,     /*!< ENET Rx FIFO threshold*/
    NULL,     /*!< ENET Tx FIFO threshold*/
    0,     /*!< ENET rxaccelerator config*/
    0,     /*!< ENET txaccelerator config*/
    0,     /*!< ENET Pause duration*/
    NULL,  /*!< ENET Special configure for MAC*/
#if FSL_FEATURE_ENET_SUPPORT_PTP
    false,
#endif
},
};
const enet_phy_config_t g_enetPhyCfg[ENET_INSTANCE_COUNT] =
{{false, 0, false }};

#if FSL_FEATURE_ENET_SUPPORT_PTP
enet_mac_ptp_ts_data_t ptpTsRxData[ENET_PTP_RXTS_RING_LEN];
enet_mac_ptp_ts_data_t ptpTsTxData[ENET_PTP_TXTS_RING_LEN];
#endif

enet_dev_if_t enetDevIf[ENET_INSTANCE_COUNT];
///////////////////////////////////////////////////////////////////////////////
// Prototypes
///////////////////////////////////////////////////////////////////////////////

#if defined(FSL_RTOS_MQX)
extern void MQX_ENET_Transmit_IRQHandler(void);
extern void MQX_ENET_Receive_IRQHandler(void);
extern void MQX_ENET_1588_Timer_IRQHandler(void);
#endif
#if !ENET_RECEIVE_ALL_INTERRUPT&&!NO_SYS
OSA_TASK_DEFINE(Enet_receive, RECV_TASK_STACK_SIZE);
#endif

///////////////////////////////////////////////////////////////////////////////
// Code
///////////////////////////////////////////////////////////////////////////////

#if !ENET_RECEIVE_ALL_INTERRUPT
/*FUNCTION****************************************************************
 *
 * Function Name: ENET_receive
 * Description:  Net Receive interface.
 *
 *END*********************************************************************/
void ENET_receive(task_param_t param)
{
    uint16_t counter = 0;
    uint32_t result;
    event_flags_t flag = 0x1, flagCheck;
    enet_mac_packet_buffer_t packetBuffer[kEnetMaxFrameBdNumbers];

    /* Init the packet buffer*/
    memset(&packetBuffer[0], 0, kEnetMaxFrameBdNumbers * sizeof(enet_mac_packet_buffer_t));
    for(counter = 0; counter < kEnetMaxFrameBdNumbers - 1; counter++)
    {
        packetBuffer[counter].next = &packetBuffer[counter + 1];
    }
	packetBuffer[counter].next = NULL;
    counter = 0;

    /* Check input parameter*/
    if (!param)
    {
        return ;
    }
    enet_dev_if_t * enetIfPtr = (enet_dev_if_t *)param;

#if !USE_RTOS
    osa_status_t status;
    /*receive frame*/
#else  
    while(1)
#endif
    {
        /* Init the packet buffer*/
        for(counter = 0; counter < kEnetMaxFrameBdNumbers; counter++)
        {
            packetBuffer[counter].data = NULL;
        }    
               /* Receive frame*/
        result = ENET_DRV_ReceiveData(enetIfPtr, &packetBuffer[0]);
        if ((result == kStatus_ENET_RxbdEmpty) || (result == kStatus_ENET_InvalidInput))
        {
            OSA_EventWait(&enetIfPtr->enetReceiveSync, flag, false, OSA_WAIT_FOREVER, &flagCheck);
        }

        /* Process with the right packets*/
        if (packetBuffer[0].data != NULL)
        {
           ethernetif_input(enetIfPtr,packetBuffer);
           for(counter = 0; packetBuffer[counter].length != 0 ; counter ++)
           {
              *(uint32_t *)(packetBuffer[counter].data) = 0;
              enet_mac_enqueue_buffer((void **)&enetIfPtr->bdContext.extRxBuffQue, packetBuffer[counter].data);
              packetBuffer[counter].length = 0;
           }		
        }
    }
}
#endif
uint8_t *txBdPtr[ENET_INSTANCE_COUNT], *rxBdPtr[ENET_INSTANCE_COUNT];
uint8_t *txBuffer[ENET_INSTANCE_COUNT], *rxBuffer[ENET_INSTANCE_COUNT];
uint8_t *rxExtBuffer[ENET_INSTANCE_COUNT];
/*FUNCTION****************************************************************
 *
 * Function Name: ENET_buffer_init
 * Return Value: The execution status.
 * Description: Initialize enet mac buffer.
 *
 *END*********************************************************************/
static uint32_t ENET_buffer_init(enet_dev_if_t * enetIfPtr, enet_buff_config_t *buffCfgPtr)
{
    uint32_t rxBufferSizeAlign, txBufferSizeAlign;
    uint8_t  *txBufferAlign, *rxBufferAlign;
    volatile enet_bd_struct_t *txBdPtrAlign, *rxBdPtrAlign;

    /* Check input parameter*/
    if((!enetIfPtr) || (!buffCfgPtr))
    {
        return kStatus_ENET_InvalidInput;
    }

    /* Allocate ENET receive buffer descriptors*/
    txBdPtr[enetIfPtr->deviceNumber] = (uint8_t *)OSA_MemAllocZero(ENET_TXBD_NUM * sizeof(enet_bd_struct_t) + ENET_BD_ALIGNMENT);
    if (!txBdPtr[enetIfPtr->deviceNumber])
    {
        return kStatus_ENET_MemoryAllocateFail;
    }
   txBdPtrAlign = (volatile enet_bd_struct_t *)ENET_ALIGN((uint32_t)txBdPtr[enetIfPtr->deviceNumber], ENET_BD_ALIGNMENT);

    rxBdPtr[enetIfPtr->deviceNumber] = (uint8_t *)OSA_MemAllocZero(ENET_RXBD_NUM * sizeof(enet_bd_struct_t) + ENET_BD_ALIGNMENT);
    if(!rxBdPtr[enetIfPtr->deviceNumber])
    {
         OSA_MemFree(txBdPtr[enetIfPtr->deviceNumber]);
         return kStatus_ENET_MemoryAllocateFail;
    }
    rxBdPtrAlign = (volatile enet_bd_struct_t *)ENET_ALIGN((uint32_t)rxBdPtr[enetIfPtr->deviceNumber], ENET_BD_ALIGNMENT);

    /* Allocate the transmit and receive date buffers*/
    rxBufferSizeAlign = ENET_RXBuffSizeAlign(ENET_RXBUFF_SIZE);
    rxBuffer[enetIfPtr->deviceNumber] = (uint8_t *)OSA_MemAllocZero(ENET_RXBD_NUM * rxBufferSizeAlign  + ENET_RX_BUFFER_ALIGNMENT);
    if (!rxBuffer[enetIfPtr->deviceNumber])
    {
        OSA_MemFree(txBdPtr[enetIfPtr->deviceNumber]);
        OSA_MemFree(rxBdPtr[enetIfPtr->deviceNumber]);
        return kStatus_ENET_MemoryAllocateFail;
    }
    rxBufferAlign = (uint8_t *)ENET_ALIGN((uint32_t)rxBuffer[enetIfPtr->deviceNumber], ENET_RX_BUFFER_ALIGNMENT);

    txBufferSizeAlign = ENET_RXBuffSizeAlign(ENET_TXBUFF_SIZE);
    txBuffer[enetIfPtr->deviceNumber] = OSA_MemAllocZero(ENET_TXBD_NUM * txBufferSizeAlign + ENET_TX_BUFFER_ALIGNMENT);
    if (!txBuffer[enetIfPtr->deviceNumber])
    {
        OSA_MemFree(txBdPtr[enetIfPtr->deviceNumber]);
        OSA_MemFree(rxBdPtr[enetIfPtr->deviceNumber]);
        OSA_MemFree(rxBuffer[enetIfPtr->deviceNumber]);
        return kStatus_ENET_MemoryAllocateFail;
    }
    txBufferAlign = (uint8_t *)ENET_ALIGN((uint32_t)txBuffer[enetIfPtr->deviceNumber], ENET_TX_BUFFER_ALIGNMENT);

#if FSL_FEATURE_ENET_SUPPORT_PTP
    buffCfgPtr->ptpTsRxDataPtr = &ptpTsRxData[0];
    buffCfgPtr->ptpTsRxBuffNum = ENET_PTP_RXTS_RING_LEN;
    buffCfgPtr->ptpTsTxDataPtr = &ptpTsTxData[0];
    buffCfgPtr->ptpTsTxBuffNum = ENET_PTP_TXTS_RING_LEN;
#endif
#if !ENET_RECEIVE_ALL_INTERRUPT
    uint8_t *rxExtBufferAlign;
    rxExtBuffer[enetIfPtr->deviceNumber] = (uint8_t *)OSA_MemAllocZero(ENET_EXTRXBD_NUM * rxBufferSizeAlign  + ENET_RX_BUFFER_ALIGNMENT);
    if (!rxExtBuffer[enetIfPtr->deviceNumber])
    {
        OSA_MemFree(txBdPtr[enetIfPtr->deviceNumber]);
        OSA_MemFree(rxBdPtr[enetIfPtr->deviceNumber]);
        OSA_MemFree(rxBuffer[enetIfPtr->deviceNumber]);
        OSA_MemFree(txBuffer[enetIfPtr->deviceNumber]);
        return kStatus_ENET_MemoryAllocateFail;
    }
    rxExtBufferAlign = (uint8_t *)ENET_ALIGN((uint32_t)rxExtBuffer[enetIfPtr->deviceNumber], ENET_RX_BUFFER_ALIGNMENT);
    buffCfgPtr->extRxBuffQue = rxExtBufferAlign;
    buffCfgPtr->extRxBuffNum = ENET_EXTRXBD_NUM;
#else
    buffCfgPtr->extRxBuffQue = NULL;
    buffCfgPtr->extRxBuffNum = 0;
#endif

    buffCfgPtr->rxBdNumber = ENET_RXBD_NUM;
    buffCfgPtr->rxBdPtrAlign = rxBdPtrAlign;
    buffCfgPtr->rxBufferAlign = rxBufferAlign;
    buffCfgPtr->rxBuffSizeAlign = rxBufferSizeAlign;
    buffCfgPtr->txBdNumber = ENET_TXBD_NUM;
    buffCfgPtr->txBdPtrAlign = txBdPtrAlign;
    buffCfgPtr->txBufferAlign = txBufferAlign;
    buffCfgPtr->txBuffSizeAlign = txBufferSizeAlign;

    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_buffer_deinit
 * Return Value: The execution status.
 * Description: Initialize enet mac buffer.
 *
 *END*********************************************************************/
static uint32_t ENET_buffer_deinit(enet_dev_if_t * enetIfPtr)
{
    /* Check input parameter*/
    if(!enetIfPtr)
    {
        return kStatus_ENET_InvalidInput;
    }

    /* Free allocated memory*/
    if(txBdPtr[enetIfPtr->deviceNumber])
    {
        OSA_MemFree(txBdPtr[enetIfPtr->deviceNumber]);
    }
    if(rxBdPtr[enetIfPtr->deviceNumber])
    {
        OSA_MemFree(rxBdPtr[enetIfPtr->deviceNumber]);
    }
    if(txBuffer[enetIfPtr->deviceNumber])
    {
        OSA_MemFree(txBuffer[enetIfPtr->deviceNumber]);
    }
    if(rxBuffer[enetIfPtr->deviceNumber])
    {
        OSA_MemFree(rxBuffer[enetIfPtr->deviceNumber]);
    }
#if !ENET_RECEIVE_ALL_INTERRUPT
    if(rxExtBuffer[enetIfPtr->deviceNumber])
    {
        OSA_MemFree(rxExtBuffer[enetIfPtr->deviceNumber]);
    }
#endif
    return kStatus_ENET_Success;
}

/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
err_t
low_level_init(struct netif *netif)
{
  enet_dev_if_t * enetIfPtr;
  uint32_t result;
  const enet_mac_config_t *macCfgPtr;
  enet_buff_config_t buffCfg;
  uint32_t devNumber = 0;
  enet_phy_speed_t physpeed;
  enet_phy_duplex_t phyduplex;
  bool linkstatus;
  enet_user_config_t enetUserConfig;
  
  #if LWIP_HAVE_LOOPIF
  devNumber = netif->num - 1;
  #else
  devNumber = netif->num;
  #endif
  /* set MAC hardware address length */
  netif->hwaddr_len = ETHARP_HWADDR_LEN;

  /* set MAC hardware address */
  netif->hwaddr[0] = configMAC_ADDR0;
  netif->hwaddr[1] = configMAC_ADDR1;
  netif->hwaddr[2] = configMAC_ADDR2;
  netif->hwaddr[3] = configMAC_ADDR3;
  netif->hwaddr[4] = configMAC_ADDR4;
  netif->hwaddr[5] = configMAC_ADDR5;


  /* maximum transfer unit */
  netif->mtu = kEnetMaxFrameDateSize;
  
  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;
  /* Do whatever else is needed to initialize interface. */ 
 
  if (devNumber >= ENET_INSTANCE_COUNT)
  	{
  	  return kStatus_ENET_InvalidDevice;
    }
  /* Initialize device*/
    enetIfPtr = (enet_dev_if_t *)&enetDevIf[devNumber];
  	netif->state = (void *)enetIfPtr;
    if (ENET_INSTANCE_COUNT - 1 == devNumber)
    {
        enetIfPtr->next = NULL;
    }   

    /* 	Configure strucutre*/
    enetIfPtr->deviceNumber = devNumber;
    g_enetMacCfg[devNumber].macAddr = (uint8_t *)&(netif->hwaddr[0]);
    macCfgPtr = &g_enetMacCfg[devNumber];
#if ENET_RECEIVE_ALL_INTERRUPT   
    enetIfPtr->enetNetifcall = ethernetif_input;
#endif
    /* Create sync signal*/
    OSA_MutexCreate(&enetIfPtr->enetContextSync);	
	 /* Initialize enet buffers*/
    result = ENET_buffer_init(enetIfPtr, &buffCfg);
	if(result != kStatus_ENET_Success)
	{
		return result;
	}

     /* Initialize ENET device*/
    enetUserConfig.macCfgPtr = macCfgPtr;
    enetUserConfig.buffCfgPtr = &buffCfg;
    result = ENET_DRV_Init(enetIfPtr, &enetUserConfig);
    if (result == kStatus_ENET_Success)
    {
        /* Initialize PHY*/ 
        if(g_enetPhyCfg[devNumber].isAutodiscoverEnabled)
        {
            uint32_t phyAddr;
            result = PHY_DRV_Autodiscover(devNumber, &phyAddr);
            if(result != kStatus_ENET_Success)
            return result;
            enetIfPtr->phyAddr = phyAddr;
        }
        else
        { 
    	    enetIfPtr->phyAddr = g_enetPhyCfg[devNumber].phyAddr;
        }

        PHY_DRV_Init(devNumber, enetIfPtr->phyAddr, g_enetPhyCfg[devNumber].isLoopEnabled);
        /*get negociation results and reconfigure MAC speed and duplex according to phy*/
        result = PHY_DRV_GetLinkStatus(devNumber,enetIfPtr->phyAddr,&linkstatus);
        if(result == kStatus_ENET_Success)
        {
    	    if(linkstatus == true)
    	    {
                result = PHY_DRV_GetLinkSpeed(devNumber,enetIfPtr->phyAddr,&physpeed);
                if(result == kStatus_ENET_Success)
                {
    	           result = PHY_DRV_GetLinkDuplex(devNumber,enetIfPtr->phyAddr,&phyduplex);
    	           if(result == kStatus_ENET_Success)
    	           {
    	               if (physpeed == kEnetSpeed10M)
    	               {
    	                   macCfgPtr->rmiiCfgPtr->speed = kEnetCfgSpeed10M;
    	               }
    	               else
    	               {
    	                   macCfgPtr->rmiiCfgPtr->speed = kEnetCfgSpeed100M;
    	               }
    	               if (phyduplex == kEnetFullDuplex)
    	               {
    	                   macCfgPtr->rmiiCfgPtr->duplex = kEnetCfgFullDuplex;
    	               }
    	               else
    	               {
    	                   macCfgPtr->rmiiCfgPtr->duplex = kEnetCfgHalfDuplex;
    	               }
                       ENET_HAL_SetRMIIMode(g_enetBase[0], macCfgPtr->rmiiCfgPtr);

    	           }
    	         }
    	    }
        }
        enetIfPtr->isInitialized = true;
#if !ENET_RECEIVE_ALL_INTERRUPT
    osa_status_t osaFlag;
    osaFlag = OSA_EventCreate(&enetIfPtr->enetReceiveSync, kEventAutoClear);
    if(osaFlag != kStatus_OSA_Success)
    {
        return osaFlag;
    }
#if USE_RTOS
    /* Create receive task*/
    osaFlag = OSA_TaskCreate(ENET_receive, "receive", RECV_TASK_STACK_SIZE, Enet_receive_stack, ENET_RECV_TASK_PRIO, (task_param_t)enetIfPtr, false, &Enet_receive_task_handler);
    if(osaFlag != kStatus_OSA_Success)
    {
        return osaFlag;
    }
#endif
#endif
        return ENET_OK;
    }
    else
    {
        ENET_DRV_Deinit(enetIfPtr);
		ENET_buffer_deinit(enetIfPtr);
        OSA_MutexDestroy(&enetIfPtr->enetContextSync);
#if !ENET_RECEIVE_ALL_INTERRUPT
#if USE_RTOS
        OSA_TaskDestroy(Enet_receive_task_handler);
#endif
        OSA_EventDestroy(&enetIfPtr->enetReceiveSync);
#endif
        return ENET_ERROR;
    }
}

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

static err_t
low_level_output(struct netif *netif, struct pbuf *p)
{
  enet_dev_if_t *enetIfPtr = (enet_dev_if_t *)netif->state;
  struct pbuf *q;
  uint16_t  lenTemp = 0, bdNumUsed = 0, bdNumUsedTmp,frameLen;
  volatile enet_bd_struct_t * curBd;

  uint8_t *frame;
  if ((!enetIfPtr) || (!p))
  {
    return  kStatus_ENET_InvalidInput;
  }
  if (p->tot_len> enetIfPtr->maxFrameSize)
  {
#if ENET_ENABLE_DETAIL_STATS 
    enetIfPtr->stats.statsTxLarge++;
#endif
    return kStatus_ENET_TxLarge;
  }
   /* Get the current transmit data buffer in buffer descriptor */
  curBd = enetIfPtr->bdContext.txBdCurPtr;
  frame = ENET_HAL_GetBuffDescripData(curBd);
  if(p->tot_len%enetIfPtr->bdContext.txBuffSizeAlign !=0)
  	bdNumUsed = p->tot_len/enetIfPtr->bdContext.txBuffSizeAlign + 1;
  else
  	bdNumUsed = p->tot_len/enetIfPtr->bdContext.txBuffSizeAlign;
  bdNumUsedTmp = bdNumUsed;
  frameLen = p->tot_len;
  while(bdNumUsedTmp--)
  {
    lenTemp = 0;
    for(q = p; q != NULL; q = q->next) {
	/* Send the data from the pbuf to the interface, one pbuf at a
	    time. The size of the data in each pbuf is kept in the ->len
	    variable. */
	  if(enetIfPtr->bdContext.txBuffSizeAlign - lenTemp >= q->len)
	  	{
	      memcpy(frame + lenTemp, q->payload, q->len);
          lenTemp += q->len;
	  	}
	  else
	  	{
	  	  memcpy(frame + lenTemp, q->payload, enetIfPtr->bdContext.txBuffSizeAlign - lenTemp); 
		  p->payload =(void *)((uint32_t )q->payload + enetIfPtr->bdContext.txBuffSizeAlign - lenTemp);
		  p->len = q->len + lenTemp - enetIfPtr->bdContext.txBuffSizeAlign;
		  p->tot_len = q->tot_len + lenTemp - enetIfPtr->bdContext.txBuffSizeAlign;
		  p->next = q->next;
		  break;
	  	}
    }
  }

    /* Send packet to the device*/
    return ENET_DRV_SendData(enetIfPtr, frameLen, bdNumUsed);
 
}

/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
static struct pbuf *
low_level_input(struct netif *netif, enet_mac_packet_buffer_t *packetBuffer)
{
  uint16_t location = 0;
  struct pbuf *head, *temphead, *p, *q;
  head = temphead = p = q = NULL;
  if (packetBuffer->length != 0)
  {
    head = temphead = p = pbuf_alloc(PBUF_RAW, packetBuffer->length, PBUF_POOL);
    if(p == NULL)
    {
      return NULL;
    }
  }
  else return NULL;
  while(1)
  {
    if (packetBuffer->length != 0)
    {
      location = 0;
      for(q = p; q != NULL; q = q->next)
      {
        memcpy((uint8_t*)q->payload, packetBuffer->data + location, q->len);
        location = location + q->len;
      }
    }
    packetBuffer = packetBuffer->next;
    if(packetBuffer != NULL)
    {
      if (packetBuffer->length != 0)
      {
        p = pbuf_alloc(PBUF_RAW, packetBuffer->length, PBUF_POOL);
        if(p == NULL)
        {
          return NULL;
        }
        pbuf_chain(temphead,p);
        temphead = p;
      }
    }else break;
  }
  return head;  
}
/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
uint32_t
ethernetif_input(void *enetPtr, enet_mac_packet_buffer_t *packetBuffer)
{

   struct eth_hdr *ethhdr;
   struct pbuf *p;
   struct netif *netif;
  	/* Check input param*/
    if((!enetPtr) || (!packetBuffer)) 
    {
        return kStatus_ENET_InvalidInput;
	}
	for(netif = netif_list; netif != NULL; netif = netif->next)
	{
	    if(netif->state == enetPtr)
		break;
	}
  /* move received packet into a new pbuf */
  p = low_level_input(netif,packetBuffer);
  /* no packet could be read, silently ignore this */
  if (p == NULL) return ENET_ERROR;
  /* points to packet payload, which starts with an Ethernet header */
  ethhdr = p->payload;

  switch (htons(ethhdr->type)) {
  /* IP or ARP packet? */
  case ETHTYPE_IP:
  case ETHTYPE_ARP:
#if PPPOE_SUPPORT
  /* PPPoE packet? */
  case ETHTYPE_PPPOEDISC:
  case ETHTYPE_PPPOE:
#endif /* PPPOE_SUPPORT */
    /* full packet send to tcpip_thread to process */
    if (netif->input(p, netif)!=ERR_OK)
     { 
       LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
       pbuf_free(p);
       p = NULL;
       return ENET_ERROR;
     }
    break;

  default:
    pbuf_free(p);
    p = NULL;
    break;
  }
  return ENET_OK;
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t
ethernetif_init(struct netif *netif)
{
  err_t result;
  LWIP_ASSERT("netif != NULL", (netif != NULL));

#if LWIP_NETIF_HOSTNAME
  /* Initialize interface hostname */
  netif->hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */

  /*
   * Initialize the snmp variables and counters inside the struct netif.
   * The last argument should be replaced with your link speed, in units
   * of bits per second.
   */
  NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, LINK_SPEED_OF_YOUR_NETIF_IN_BPS);

  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;
  /* We directly use etharp_output() here to save a function call.
   * You can instead declare your own function an call etharp_output()
   * from it if you have to do some checks before sending (e.g. if link
   * is available...) */
  netif->output = etharp_output;
  netif->linkoutput = low_level_output;
#if defined(FSL_RTOS_MQX)
    OSA_InstallIntHandler(ENET_Transmit_IRQn, MQX_ENET_Transmit_IRQHandler);
    OSA_InstallIntHandler(ENET_Receive_IRQn, MQX_ENET_Receive_IRQHandler);
#if defined(FSL_RTOS_MQX)
    OSA_InstallIntHandler(ENET_1588_Timer_IRQn, MQX_ENET_1588_Timer_IRQHandler); 
#endif
  /* Set priority for ISRs */
  NVIC_SetPriority(ENET_1588_Timer_IRQn, 4U);
  NVIC_SetPriority(ENET_Transmit_IRQn, 4U);
  NVIC_SetPriority(ENET_Receive_IRQn, 4U);
#endif  
  /* initialize the hardware */
  result = low_level_init(netif);

  return result;
}

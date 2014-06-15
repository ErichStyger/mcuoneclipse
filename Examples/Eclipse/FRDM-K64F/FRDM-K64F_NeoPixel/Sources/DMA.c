/*
 * DMA.c
 *
 *  Created on: 04.06.2014
 *      Author: tastyger
 */

#include <stdint.h>
#include "DMA.h"
#include "DMACH1.h"
#include "DMA_PDD.h"

uint16_t dmaSrc[32]={100,101,102,103,104,105};
uint16_t dmaDst[32]={200,201,202,203,204,205};


void DMA_Run(void) {
  for(;;) {
    //DMA_PDD_SetDestinationAddress(DMA_BASE_PTR, 0, (uint32_t)&TPM0_C1V); /* set destination address */

    DMA_PDD_SetSourceAddress(DMA_BASE_PTR, 0, (uint32_t)&dmaSrc[0]); /* set source address */
    DMA_PDD_SetDestinationAddress(DMA_BASE_PTR, 0, (uint32_t)&dmaDst[0]); /* set destination address */

    DMA_PDD_SetByteCount(DMA_BASE_PTR, 0, sizeof(dmaSrc));
    DMACH1_EnableRequest(DMACH1_DeviceData); /* enable first transfer */
    Cpu_EnableInt(); /* enable interrupts */
    for(;;) {
      //WAIT1_Waitms(200);
      //DMA1_SetTransactionCount(DMACH1_DeviceData, 3);
  #if SW_DMA_REQUEST
      DMA1_SetRequestCount(DMACH1_DeviceData, 1); /* 1: 100->101->102->103->104  3: 100->103->106 */
      DMACH1_StartTransfer(DMACH1_DeviceData);
  #endif
      //errors = DMACH1_GetError(DMACH1_DeviceData);
    }
  }
}

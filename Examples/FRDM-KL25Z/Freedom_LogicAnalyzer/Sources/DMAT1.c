/*
 * DMAT1.c
 *
 *  Created on: Mar 20, 2013
 *      Author: Reiner Geiger
 *      
 *      Handle DMA Channels
 *      
 *      Version 1.0	Basic Implementation
 *      
 *      We handle only one channel at this time; no error Handling
 */

#include "DMAT1.h"
#include "DMA1.h"

LDD_TError  DMAT1_Init(void)
{
	DMA1_Init();
	return ERR_OK;
}

LDD_TError  DMAT1_EnableChannel0(void)
{
	DMA_DCR0 |= DMA_DCR_ERQ_MASK;
	return ERR_OK;
}

LDD_TError  DMAT1_DisableChannel0(void)
{
	DMA_DCR0 &= ~DMA_DCR_ERQ_MASK;
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
	return ERR_OK;
}

LDD_TError  DMAT1_SetDestinationAddress0(uint32_t dest)
{
	DMA_DAR0 = (uint32_t)(dest);
	return ERR_OK;
}

LDD_TError  DMAT1_SetSourceAddress0(uint32_t dest)
{
	// DMA_SAR0 = (uint32_t)(&GPIOC_PDIR);
	DMA_DAR0 = (uint32_t)(dest);
	return ERR_OK;
}

LDD_TError  DMAT1_SetDestinationTransferSize0(uint16_t size)
{
	DMA_DSR_BCR0 |= DMA_DSR_BCR_BCR(size);
	return ERR_OK;
}

LDD_TError  DMAT1_StartTransfer0(void)
{
	DMA_DCR0 |= DMA_DCR_START_MASK;
	return ERR_OK;
}




/* EOF*/




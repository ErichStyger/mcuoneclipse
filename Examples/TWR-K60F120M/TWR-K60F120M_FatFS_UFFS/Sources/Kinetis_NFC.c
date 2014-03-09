/**
 * @file Kinetis_NFC.c
 *
 *  Created on: Mar 6, 2014
 *      Author: Marc Lindahl
 *      
 *  NAND Flash access routines for Kinetis
 *  Relies on Init_NFC ProcessorExpert component.
 *  
 */


#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

#include "Kinetis_NFC.h"

#ifdef NFC_SIMPLECACHE
// variables to implement crude caching - don't read/write the same page twice in a row
static uint8_t 	last_cs = 0xFF;				///< most recently accessed chip select
static uint8_t	last_rw = 0;				///< most recent access was read==0 write==1
static uint32_t	last_block = 0xFFFFFFFF;	///< most recently accessed block
static uint16_t last_page = 0xFFFF;			///< most recently accessed page
static uint32_t nfc_access = 0;				///< stats
static uint32_t nfc_cache_access = 0;			///< stats
#endif

/**
 * initialize NFC peripheral and reset NAND chip(s)
 */
void nand_init(void)
{
	NFC_Init();
	nfc_reset_cmd(0);
#if (NFC_NCHIPS == 2)
	nfc_reset_cmd(1);
#endif
	
}

/**
 * reset a NAND chip
 * @param chipselect = 0 or 1 
 */
void nfc_reset_cmd(uint8_t chipselect)
{
#ifdef NFC_SIMPLECACHE
	last_cs = chipselect;
	last_rw = 0;
	last_block = 0xFFFFFFFF;
	last_page = 0xFFFF;
	nfc_cache_access = 0;
	nfc_access = 0;
#endif
    /* Set the chip select to use */
    if(chipselect == 0)
    	NFC_PDD_WriteRARReg(NFC_DEVICE, NFC_RAR_CS0_MASK | NFC_RAR_RB0_MASK);
    else /* (NFC_CE == NFC_CE1) */
    	NFC_PDD_WriteRARReg(NFC_DEVICE, NFC_RAR_CS1_MASK | NFC_RAR_RB0_MASK);
    NFC_PDD_SetResetCmd(NFC_DEVICE);
    // do command
    NFC_PDD_ClrCmdIdleInterruptFlag(NFC_DEVICE);
    NFC_PDD_StartCommand(NFC_DEVICE);
    // wait til complete.
    while( !NFC_PDD_GetCmdIdleInterruptFlag(NFC_DEVICE) )
    	OS_YIELD();
}

/**
 * read ID of selected chip.
 * ID values will be in NFC_SR1 and NFC_SR2 upon success.
 * Use NFC_PDD_GetID1(NFC_DEVICE) etc. to retrieve (or read the uint32_t registers)
 * @param chipselect = 0 or 1 
 * @param ID address NFC_READID_MFG or NFC_READID_ONFI.  See NAND data sheet for details of return
 */
void nfc_read_flash_id(uint8_t chipselect, uint8_t addr)
{
    /* Set the chip select to use */
    if(chipselect == 0)
    	NFC_PDD_WriteRARReg(NFC_DEVICE, NFC_RAR_CS0_MASK | NFC_RAR_RB0_MASK);
    else /* (NFC_CE == NFC_CE1) */
    	NFC_PDD_WriteRARReg(NFC_DEVICE, NFC_RAR_CS1_MASK | NFC_RAR_RB0_MASK);
    NFC_PDD_SetReadIdCmd(NFC_DEVICE, addr, NFC_IDCNT);
    // do command
    NFC_PDD_ClrCmdIdleInterruptFlag(NFC_DEVICE);
    NFC_PDD_StartCommand(NFC_DEVICE);
    // wait til complete.
    while( !NFC_PDD_GetCmdIdleInterruptFlag(NFC_DEVICE) )
    	OS_YIELD();
}

/**
 * erase block of selected chip
 * @param chipselect = 0 or 1 
 * @param block block address (up to 24 bytes)
 */
void nfc_block_erase(uint8_t chipselect, uint32_t block)
{
#ifdef NFC_SIMPLECACHE
	last_cs = chipselect;
	last_rw = 0;
	last_block = block;
	last_page = 0xFFFF;
#endif
	if(chipselect == 0)
    	NFC_PDD_WriteRARReg(NFC_DEVICE, NFC_RAR_CS0_MASK | NFC_RAR_RB0_MASK);
    else /* (NFC_CE == NFC_CE1) */
    	NFC_PDD_WriteRARReg(NFC_DEVICE, NFC_RAR_CS1_MASK | NFC_RAR_RB0_MASK);
//TODO: verify if we should disable ECC - bare metal code does, PE driver doesn't.  Same with setting col address == 0.
    NFC_PDD_SetColAddress(NFC_DEVICE, 0);
    NFC_PDD_SetEraseBlockCmd(NFC_DEVICE, block << NFC_BLOCKSHIFT);
    // do command
    NFC_PDD_ClrCmdIdleInterruptFlag(NFC_DEVICE);
    NFC_PDD_StartCommand(NFC_DEVICE);
    // wait til complete.
    while( !NFC_PDD_GetCmdIdleInterruptFlag(NFC_DEVICE) )
    	OS_YIELD();
}

/**
 * program page with data from buffer and optionally spare data from spare buffer.
 * data or spare can be NULL, in which case the NFC buffer contents won't be touched in that area.
 * @param chipselect = 0 or 1 
 * @param block block address
 * @param page page address (within block)
 * @param data data buffer pointer. If NULL no DMA will occur.  Must be aligned on 8-byte boundary.
 * @param datalen length of data.  Note: if data is less than NFC_DATA_SIZE 
 * (or NFC_DATA_SIZE+NFC_SPARE_SIZE if spare==NULL) then the remainder will be stuffed with 0xFF before programming.
 * Must be multiple of 8.
 * @param spare spare data buffer pointer. If NULL no DMA will occur.  Must be aligned on 8-byte boundary.
 * @param sparelen length of spare data.  Note: if spare is less than NFC_SPARE_SIZE then remainder will be stuffed with 0xFF.
 * must be multiple of 8. 
 */
void nfc_page_program(uint8_t chipselect, uint32_t block, uint16_t page, uint8_t *data, uint16_t datalen, uint8_t *spare, uint16_t sparelen)
{
#ifdef NFC_SIMPLECACHE
	// check if we just wrote the same page and exit if so
	if ( (last_cs == chipselect) && (last_rw == 1) && (last_block == block) && (last_page == page) )
	{
		nfc_cache_access++;
		return;
	}
	nfc_access++;
	last_cs = chipselect;
	last_rw = 1;
	last_block = block;
	last_page = page;
#endif
	if(chipselect == 0)
    	NFC_PDD_WriteRARReg(NFC_DEVICE, NFC_RAR_CS0_MASK | NFC_RAR_RB0_MASK);
    else /* (NFC_CE == NFC_CE1) */
    	NFC_PDD_WriteRARReg(NFC_DEVICE, NFC_RAR_CS1_MASK | NFC_RAR_RB0_MASK);

    // set up DMA channels.  Spare area always immediately follows data area
    NFC_PDD_SetDma1AndDma2(NFC_DEVICE, data, datalen, spare, sparelen, NFC_SPARE_IDX/256);

    // disable unused DMA channels and fill extra space with FF's
    if(data && datalen)
    {
    	if( datalen < NFC_DATA_SIZE )
    		memset(NFC_BUFADDR + datalen, 0xFF, NFC_DATA_SIZE - datalen);
    }
    else
    	NFC_DMACFG_REG(NFC_DEVICE) &= ~NFC_DMACFG_ACT1_MASK;

    if(spare && sparelen)
    {
    	if( sparelen < NFC_SPARE_SIZE )
    		memset(NFC_BUFADDR + NFC_SPARE_IDX + sparelen, 0xFF, NFC_SPARE_SIZE - sparelen);
    }
    else
    	NFC_DMACFG_REG(NFC_DEVICE) &= ~NFC_DMACFG_ACT2_MASK;

    // enable DMA if any used
    if( data || spare )
    	NFC_CFG_REG(NFC_DEVICE) |= NFC_CFG_DMAREQ_MASK;
    else
       	NFC_CFG_REG(NFC_DEVICE) &= ~NFC_CFG_DMAREQ_MASK;

    NFC_PDD_SetColAddress(NFC_DEVICE, 0);
    NFC_PDD_SetWritePageCmd(NFC_DEVICE, (block << NFC_BLOCKSHIFT)|(NFC_PAGEMASK & page), 0, NFC_BUF);
    // do command
    NFC_PDD_ClrCmdIdleInterruptFlag(NFC_DEVICE);
    NFC_PDD_StartCommand(NFC_DEVICE);
    // wait til complete.
    while( !NFC_PDD_GetCmdIdleInterruptFlag(NFC_DEVICE) )
    	OS_YIELD();
}

/**
 * read page to data  buffer and optionally spare data to spare buffer.
 * data or spare can be NULL, in which case the NFC buffer contents won't be transferred.  
 * Transfer uses DMA channel 0 for data and channel 1 for spare.
 * @param chipselect = 0 or 1 
 * @param block block address. If NULL no DMA will occur.  Must be aligned on 8-byte boundary.
 * @param page page address (within block)
 * @param data data buffer pointer.  If NULL no DMA will occur. 
 * @param datalen length of data.  MUST BE MULTIPLE OF 8!
 * @param spare spare data buffer pointer. If NULL no DMA will occur.  Must be aligned on 8-byte boundary.
 * @param sparelen length of spare data.  MUST BE MULTIPLE OF 8!
 * @return ECC result.  If result <128, ECC is successful, >=128 failed.
 */
uint8_t nfc_page_read(uint8_t chipselect, uint32_t block, uint16_t page, uint8_t *data, uint16_t datalen, uint8_t *spare, uint16_t sparelen)
{
#ifdef NFC_SIMPLECACHE
	// check if we just read the same page and just recopy from SRAM buffer and exit if so
	if ( (last_cs == chipselect) && (last_rw == 0) && (last_block == block) && (last_page == page) )
	{
		nfc_cache_access++;
		if(data)
			memcpy( data, NFC_BUFADDR, datalen);
		if(spare)
			memcpy( spare, NFC_BUFADDR + NFC_SPARE_IDX, sparelen);
		return NFC_BUFADDR[NFC_ECCINFO_IDX];
	}
	nfc_access++;
	last_cs = chipselect;
	last_rw = 0;
	last_block = block;
	last_page = page;
#endif
    if(chipselect == 0)
    	NFC_PDD_WriteRARReg(NFC_DEVICE, NFC_RAR_CS0_MASK | NFC_RAR_RB0_MASK);
    else /* (NFC_CE == NFC_CE1) */
    	NFC_PDD_WriteRARReg(NFC_DEVICE, NFC_RAR_CS1_MASK | NFC_RAR_RB0_MASK);

    // set up DMA channels.  Spare area always immediately follows data area
    NFC_PDD_SetDma1AndDma2(NFC_DEVICE, data, datalen, spare, sparelen, NFC_SPARE_IDX/256);

    // disable unused DMA channels and fill extra space with FF's
    if(data && datalen)
    {
    	if( datalen < NFC_DATA_SIZE )
    		memset(NFC_BUFADDR + datalen, 0xFF, NFC_DATA_SIZE - datalen);
    }
    else
    	NFC_DMACFG_REG(NFC_DEVICE) &= ~NFC_DMACFG_ACT1_MASK;

    if(spare && sparelen)
    {
    	if( sparelen < NFC_SPARE_SIZE )
    		memset(NFC_BUFADDR + NFC_SPARE_IDX + sparelen, 0xFF, NFC_SPARE_SIZE - sparelen);
    }
    else
    	NFC_DMACFG_REG(NFC_DEVICE) &= ~NFC_DMACFG_ACT2_MASK;

    // enable DMA if any used
    if( data || spare )
    	NFC_CFG_REG(NFC_DEVICE) |= NFC_CFG_DMAREQ_MASK;
    else
       	NFC_CFG_REG(NFC_DEVICE) &= ~NFC_CFG_DMAREQ_MASK;

    NFC_PDD_SetColAddress(NFC_DEVICE, 0);
    NFC_PDD_SetReadPageCmd(NFC_DEVICE, (block << NFC_BLOCKSHIFT)|(NFC_PAGEMASK & page), 0, NFC_BUF);
    // do command
    NFC_PDD_ClrCmdIdleInterruptFlag(NFC_DEVICE);
    NFC_PDD_StartCommand(NFC_DEVICE);
    // wait til complete.
    while( !NFC_PDD_GetCmdIdleInterruptFlag(NFC_DEVICE) )
    	OS_YIELD();
     
     return NFC_BUFADDR[NFC_ECCINFO_IDX];
}



#define NFC_BUF	0		///< default buffer to use

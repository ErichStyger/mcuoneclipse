/**
 * @file Kinetis_NFC.h
 *
 *  Created on: Mar 6, 2014
 *      Author: Marc Lindahl
 *  NAND Flash access routines for Kinetis
 *  Relies on Init_NFC ProcessorExpert component.
 *  
 *  Some code lifted from KINETIS_120MHZ_SC nfc.
 *  
 *  Simple driver, does one block/sector at a time, with no overlap.
 *  
 *  Does not need or use interrupts.
 *  
 *  Also not thread safe - you'll need to add locks or other ways to serialize access.
 *  
 *  Supports two chip selects... both memories must be identical, and have R/B common.
 *
 */

#ifndef KINETIS_NFC_H_
#define KINETIS_NFC_H_

#include <cstdint>

#include "NFC.h"
#include "NFC_PDD.h"

#include "FRTOS1.h"

// processor expert settings - Init_NFC doesn't create defines for these, please duplicate your settings
#define NFC_DATA_SIZE		0x400			///< size of page data size.  Must be multiple of 256.
#define NFC_SPARE_SIZE		0x10			///< size of user spare data (not incuding ECC).  Must be multple of 8.
#define NFC_ECC_SIZE		0x10			///< size of ECC area used by NFC. Must be multple of 8.
#define NFC_BADBLOCK_IDX	0x400			///< index of back block marker
#define NFC_ECCINFO_IDX		(0x800+4)		///< address in buffer of ECC info (note in Init_NFC val is shifted left 3) plus offset (see https://community.freescale.com/thread/316862)
#define NFC_SPARE_IDX		NFC_DATA_SIZE	///< spare area right after data area
#define NFC_IDCNT			5				///< almost always 5 bytes of ReadID
#define NFC_16BIT			1				///< ==1 if NAND chips are 16bit or ==0 for 8bit
#define NFC_BLOCKSIZE		64				///< pages per block
#define NFC_BLOCKSHIFT		6				///< 2^NFC_BLOCKSHIFT == NFC_BLOCKSIZE
#define NFC_NBLOCKS			2048			///< number of blocks in the NAND


#define NFC_NCHIPS	1						///< number of NAND chips.  Assumed connection is individual CE to each chip, common R/nB
#define NFC_BUF		0						///< default buffer to use (within NFC)
#define NFC_READID_MFG	0					///< manufacturer ID info command
#define NFC_READID_ONFI	0x20				///< should return ascii "ONFI" in first 4 bytes



#define OS_YIELD()	FRTOS1_taskYIELD()		///< if there's an OS and you want to yield during wait loops


//derived defines
#define NFC_PAGEMASK ((1<<NFC_BLOCKSHIFT)-1)
#define NFC_BUFADDR ((uint8_t*)((uint8_t*)NFC_DEVICE+(0x1000 * NFC_BUF)))

#define NFC_SIMPLECACHE						///< if defined, then checks if the last access was the same, and doesn't re-do it (i.e. read same page twice)



/**
 * initialize NFC peripheral and reset NAND chip(s)
 */
void nand_init(void);

/**
 * reset a NAND chip
 * @param chipselect = 0 or 1 
 */
void nfc_reset_cmd(uint8_t chipselect);

/**
 * read ID of selected chip
 * @param chipselect = 0 or 1 
 * @param ID address NFC_READID_MFG or NFC_READID_ONFI.  See NAND data sheet for details of return
 * ID values will be in NFC_SR1 and NFC_SR2 upon success.
 */
void nfc_read_flash_id(uint8_t chipselect, uint8_t addr);

/**
 * erase block of selected chip
 * @param chipselect = 0 or 1 
 * @param block block address (up to 24 bytes)
 */
void nfc_block_erase(uint8_t chipselect, uint32_t block);

/**
 * program page with data from buffer and optionally spare data from spare buffer.
 * data or spare can be NULL, in which case the NFC buffer contents won't be touched in that area.
 * @param chipselect = 0 or 1 
 * @param block block address
 * @param page page address (within block)
 * @param data data buffer pointer. If NULL no DMA will occur.  Must be aligned on 8-byte boundary.
 * @param datalen length of data.  Note: if data is less than NFC_DATA_SIZE 
 * (or NFC_DATA_SIZE+NFC_SPARE_SIZE if spare==NULL) then the remainder will be stuffed with 0xFF before programming.
 * MUST BE MULTIPLE OF 8!
 * @param spare spare data buffer pointer. If NULL no DMA will occur.  Must be aligned on 8-byte boundary.
 * @param sparelen length of spare data. If NULL no DMA will occur. MUST BE MULTIPLE OF 8!
 */
void nfc_page_program(uint8_t chipselect, uint32_t block, uint16_t page, uint8_t *data, uint16_t datalen, uint8_t *spare, uint16_t sparelen);

/**
 * read page to data  buffer and optionally spare data to spare buffer.
 * data or spare can be NULL, in which case the NFC buffer contents won't be transferred.  
 * Transfer uses DMA channel 0 for data and channel 1 for spare.
 * @param chipselect = 0 or 1 
 * @param block block address
 * @param page page address (within block)
 * @param data data buffer pointer.  If NULL no DMA will occur.  Must be aligned on 8-byte boundary.
 * @param datalen length of data. MUST BE MULTIPLE OF 8!
 * @param spare spare data buffer pointer.  Must be aligned on 8-byte boundary.
 * @param sparelen length of spare data. If NULL no DMA will occur. MUST BE MULTIPLE OF 8!
 * @return ECC result.  If result <128, ECC is successful, >=128 failed.
 */
uint8_t nfc_page_read(uint8_t chipselect, uint32_t block, uint16_t page, uint8_t *data, uint16_t datalen, uint8_t *spare, uint16_t sparelen);



#endif /* KINETIS_NFC_H_ */

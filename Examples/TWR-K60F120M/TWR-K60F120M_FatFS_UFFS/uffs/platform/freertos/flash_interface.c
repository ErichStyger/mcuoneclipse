/*
  This file is part of UFFS, the Ultra-low-cost Flash File System.
  
  Copyright (C) 2005-2009 Ricky Zheng <ricky_gz_zheng@yahoo.co.nz>

  UFFS is free software; you can redistribute it and/or modify it under
  the GNU Library General Public License as published by the Free Software 
  Foundation; either version 2 of the License, or (at your option) any
  later version.

  UFFS is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
  or GNU Library General Public License, as applicable, for more details.
 
  You should have received a copy of the GNU General Public License
  and GNU Library General Public License along with UFFS; if not, write
  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA  02110-1301, USA.

  As a special exception, if other files instantiate templates or use
  macros or inline functions from this file, or you compile this file
  and link it with other works to produce a work based on this file,
  this file does not by itself cause the resulting work to be covered
  by the GNU General Public License. However the source code for this
  file must still be made available in accordance with section (3) of
  the GNU General Public License v2.
 
  This exception does not invalidate any other reasons why a work based
  on this file might be covered by the GNU General Public License.
*/
/**
 * \file flash-interface-example.c
 * \brief example for using flash driver and multiple partitions, with static memory allocator.
 * \author Ricky Zheng, created at 27 Nov, 2007
 */
  
#include <string.h>
#include "flash_interface_private.h"

#define PFX "uffs: "

// reflected from Kintetis_NFC.h setup
#define TOTAL_BLOCKS    		NFC_NBLOCKS		//total blocks per data sheet
#define PAGE_DATA_SIZE  		NFC_DATA_SIZE	//user area for data
#define PAGE_SPARE_SIZE			NFC_SPARE_SIZE	//user area for tag
#define PAGES_PER_BLOCK			NFC_BLOCKSIZE
#define BAD_BLOCK_MARKER_IDX	NFC_BADBLOCK_IDX			// index from beginning of page
#define TAG_IDX					(BAD_BLOCK_MARKER_IDX+1)	// index from beginning of page


/////////////////////////////////////////////////////////////////////////////////

// Set up your desired partitions here
// NOTE: partition names start & end with "/" and should not have ":" as second character

#define NR_PARTITION	2								/* total partitions */
#define PAR_1_BLOCKS	(TOTAL_BLOCKS/2)				/* partition 1 */
#define PAR_2_BLOCKS	(TOTAL_BLOCKS - PAR_1_BLOCKS)	/* partition 2 */

// define mount table

static uffs_Device flash_partition_1 = {0, 0, 0};	// third value is chip select (0 or 1)
static uffs_Device flash_partition_2 = {0, 0, 0};	// third value is chip select (0 or 1)

static uffs_MountTable flash_mount_table[] = {
	{ &flash_partition_1,  0, PAR_1_BLOCKS - 1, "/data/" },
	{ &flash_partition_2,  PAR_1_BLOCKS, PAR_1_BLOCKS + PAR_2_BLOCKS - 1, "/" },
	{ NULL, 0, 0, NULL }
};

/////////////////////////////////////////////////////////////////////////////////


#define FLASH_CHIPSEL (uint8_t)(dev->_private)

/// find first byte in an array not matching a byte, return index
/// @param data pointer to data
/// @param dataLen max length of data
/// @param matchByte byte to find
/// @return returns index of byte.  If index == dataLen then not found.
/*inline*/ int findNotByte( u8 *data, int dataLen, u8 matchByte )
{
	int idx = 0;
	while( idx < dataLen )
	{
		if( *data++ != matchByte )
			break;
		idx++;
	}
	return idx;
}

/// test if a buffer is blank, according to device info
/// @param data buffer
/// @param dev device info (for page size)
/// @return pdTRUE if page is all FF's
u8 pageIsBlank(u8 *data, uffs_Device *dev)
{
	int len = dev->attr->page_data_size + dev->attr->spare_size;
	return ( len == findNotByte( data, len, 0xFF ));
}




/*
UFFS_FLASH_NO_ERR: success 
UFFS_FLASH_IO_ERR: I/O error, expect retry ? 
UFFS_FLASH_ECC_FAIL: page data has flip bits and ecc correct failed (when ecc_opt == UFFS_ECC_HW_AUTO) 
UFFS_FLASH_ECC_OK: page data has flip bits and corrected by ecc (when ecc_opt == UFFS_ECC_HW_AUTO) 
UFFS_FLASH_BAD_BLK: if the block is a bad block (e.g., the bad block mark byte is not 0xFF) 
UFFS_FLASH_NOT_SEALED: if the page spare is not sealed properly
Note
if data is NULL, do not return data; if ts is NULL, do not read tag; 
if both data and ts are NULL, then read bad block mark and return UFFS_FLASH_BAD_BLK if bad block mark is not 0xFF.
flash driver DO NOT need to do ecc correction for tag, UFFS will take care of tag ecc.
 */

static int nand_read_page_with_layout(uffs_Device *dev, u32 block, u32 page, u8* data, int data_len, u8 *ecc, 
		uffs_TagStore *ts, u8 *ecc_store)
{
	uint8_t ret;
	
	if( (data_len%8) == 0 )
		ret = nfc_page_read(FLASH_CHIPSEL, block, page, data, data_len, NULL, 0);
	else
	{
		ret = nfc_page_read(FLASH_CHIPSEL, block, page, NULL, 0, NULL, 0);
		if(data)
			memcpy(data, NFC_BUFADDR, data_len);		
	}
	
	// copy tag store, which starts at offset 1 of spare (0 is bad block marker)
	if(ts)
	{
		memcpy(ts, NFC_BUFADDR + TAG_IDX, sizeof(uffs_Tags));
	}

	if(ret >= 128)
	{
		if(pageIsBlank(NFC_BUFADDR, dev))
			return UFFS_FLASH_NOT_SEALED;
		else
			return UFFS_FLASH_ECC_FAIL;
	}
	
	if( NFC_BUFADDR[BAD_BLOCK_MARKER_IDX] != 0xFF)
		return UFFS_FLASH_BAD_BLK;
		
	if( !TAG_IS_SEALED((uffs_Tags*)(NFC_BUFADDR + TAG_IDX)))
		return UFFS_FLASH_NOT_SEALED;
	
	if(ret > 0)
		return UFFS_FLASH_ECC_OK;
	
	return UFFS_FLASH_NO_ERR;
}

//static int nand_write_page(uffs_Device *dev, u32 block, u32 page,
//							const u8 *data, int data_len, const u8 *spare, int spare_len)


static int nand_write_page_with_layout(uffs_Device *dev, u32 block, u32 page,
		const u8 *data, int data_len, const u8 *ecc, const uffs_TagStore *ts)
{
	// If data == NULL && ts == NULL, driver should mark this block as a 'bad block'.
	if( !data && !ts )
	{
		memset(NFC_BUFADDR, 0xFF, NFC_DATA_SIZE + NFC_SPARE_SIZE);
		NFC_BUFADDR[BAD_BLOCK_MARKER_IDX] = 0;
	}
	else
	{
		memcpy( NFC_BUFADDR + TAG_IDX, ts, sizeof(uffs_Tags));
		NFC_BUFADDR[BAD_BLOCK_MARKER_IDX] = 0xFF;
		memset(NFC_BUFADDR + TAG_IDX + sizeof(uffs_Tags), 0xFF, NFC_SPARE_SIZE - sizeof(uffs_Tags));
	}

	if( (data_len%8) == 0 )
		nfc_page_program(FLASH_CHIPSEL, block, page, data, data_len, NULL, 0);
	else
	{
		if(data)
			memcpy(NFC_BUFADDR, data, data_len);		
   		memset(NFC_BUFADDR + data_len, 0xFF, NFC_DATA_SIZE - data_len);
		nfc_page_program(FLASH_CHIPSEL, block, page, NULL, 0, NULL, 0);
	}

	

	return UFFS_FLASH_NO_ERR;
}

static int nand_erase_block(uffs_Device *dev, u32 block)
{
	nfc_block_erase( FLASH_CHIPSEL, block);
	return UFFS_FLASH_NO_ERR;
}

//TODO: delete this it's only for debugging
static void nand_test(uffs_Device *dev)
{
	volatile uint32_t PageNumber = 0;
	volatile uint32_t ioerrs = 0;
	volatile uint32_t eccerrs = 0;
	volatile uint32_t eccok = 0;
	volatile uint32_t blankPages = 0;	
	volatile uint32_t badblocks = 0;
	volatile uint8_t ret;
	
	MSGLN("testing raw NAND:");
//	MSG("PageNumber ");
	
	while( PageNumber < TOTAL_BLOCKS *  PAGES_PER_BLOCK)	//debug only do 10 blocks to see what's going on
	{
		if( (PageNumber % PAGES_PER_BLOCK) == 0)
//			MSG("%d\t", PageNumber);

		// check for bad block

		memset(NFC_BUFADDR, 0xA5, NFC_DATA_SIZE+NFC_SPARE_SIZE+NFC_ECC_SIZE);
		ret = nfc_page_read(FLASH_CHIPSEL, PageNumber/PAGES_PER_BLOCK, PageNumber % PAGES_PER_BLOCK, NULL, 0, NULL, 0);

		if(ret >= 128)
		{
			if( pageIsBlank(NFC_BUFADDR, dev) )
				blankPages++;
			else
				eccerrs++;
		}
		else
		{
			if( ret > 0)
				eccok++;
			if( pageIsBlank(NFC_BUFADDR, dev) )
				blankPages++;
		}

		if( NFC_BUFADDR[BAD_BLOCK_MARKER_IDX] != 0xFF)
			badblocks++;
		PageNumber++;
	}
	MSGLN("pages %u blank %u ecc %u eccok %u bad %u",PageNumber, blankPages, eccerrs, eccok, badblocks);
	PageNumber = 0;
}


static void nand_erase_device(uffs_Device *dev, bool ignoreBadBlocks)
{
	volatile uint32_t block = 0;
	volatile uint32_t ioerrs = 0;
	volatile uint32_t eccerrs = 0;
	volatile uint32_t eccok = 0;
	volatile uint32_t blankPages = 0;	
	volatile uint32_t badblocks = 0;
	volatile uint32_t oldbadblocks = 0;
	volatile uint32_t oldblanks = 0;
	volatile uint8_t ret;
	volatile bool isBlank;

	MSGLN("erasing raw NAND:");
	if( ignoreBadBlocks )
		MSGLN("ignoring factory bad blocks");
//	MSG("block ");

	while( block < TOTAL_BLOCKS)
	{
//		MSG("%d\t", block);

		// check for bad block

		memset(NFC_BUFADDR, 0xA5, NFC_DATA_SIZE+NFC_SPARE_SIZE+NFC_ECC_SIZE);
		ret = nfc_page_read(FLASH_CHIPSEL, block, 0, NULL, 0, NULL, 0);

		if( NFC_BUFADDR[BAD_BLOCK_MARKER_IDX] != 0xFF)
			oldbadblocks++;
		isBlank = pageIsBlank(NFC_BUFADDR, dev);
		if( isBlank )
			oldblanks++;
		// first block always guaranteed good so always erase it
		if( !isBlank && ((block == 0) || ignoreBadBlocks || (NFC_BUFADDR[BAD_BLOCK_MARKER_IDX] == 0xFF)))
		{
			nfc_block_erase( FLASH_CHIPSEL, block);

			// read it back to check 

			memset(NFC_BUFADDR, 0xA5, NFC_DATA_SIZE+NFC_SPARE_SIZE+NFC_ECC_SIZE);

			ret = nfc_page_read(FLASH_CHIPSEL, block, 0, NULL, 0, NULL, 0);
		}

		if(ret >= 128)
		{
			if( pageIsBlank(NFC_BUFADDR, dev) )
				blankPages++;
			else
				eccerrs++;
		}
		else
		{
			if( ret > 0)
				eccok++;
			if( pageIsBlank(NFC_BUFADDR, dev) )
				blankPages++;
		}

		if( NFC_BUFADDR[BAD_BLOCK_MARKER_IDX] != 0xFF)
			badblocks++;
		block++;
	}
	MSGLN("blocks %u was blank %u is blank %u ecc %u eccok %u ",block, oldblanks, blankPages, eccerrs, eccok);	
	MSGLN("were bad %u still bad %u",oldbadblocks, badblocks);
}



static int nand_init_flash(uffs_Device *dev)
{
	// initialize your hardware here ...

	//FIXME comment out next two after testing
//	nand_erase_device(dev, pdTRUE);
//	nand_test(dev);

	return UFFS_FLASH_NO_ERR;
}

static int nand_release_flash(uffs_Device *dev)
{
	// release your hardware here
	return 0;
}

static uffs_FlashOps my_flash_ops = {
	nand_init_flash,				// InitFlash()
	nand_release_flash,				// ReleaseFlash()
	NULL,							// ReadPage()
	nand_read_page_with_layout,		// ReadPageWithLayout
	NULL,							// WritePage()
	nand_write_page_with_layout,	// WirtePageWithLayout
	NULL,							// IsBadBlock(), let UFFS take care of it.
	NULL,							// MarkBadBlock(), let UFFS take care of it.
	nand_erase_block,				// EraseBlock()
};



static struct uffs_StorageAttrSt my_flash_storage = {0};



uffs_MountTable * get_flash_mount_table(void)
{
	return flash_mount_table;
}

/* static alloc the memory for each partition */
//static int static_buffer_par1[UFFS_STATIC_BUFF_SIZE(PAGES_PER_BLOCK, (PAGE_DATA_SIZE + PAGE_SPARE_SIZE), PAR_1_BLOCKS) / sizeof(int)];
//static int static_buffer_par2[UFFS_STATIC_BUFF_SIZE(PAGES_PER_BLOCK, (PAGE_DATA_SIZE + PAGE_SPARE_SIZE), PAR_2_BLOCKS) / sizeof(int)];;

//static void init_nand_chip(void *chip)
static void init_nand_chip(void)
{
	// init chip IO address, etc.
	char onfi[] = "none";
	
	nand_init();
	
	nfc_read_flash_id(0, NFC_READID_ONFI);
	onfi[0] = NFC_PDD_GetID1(NFC_DEVICE);
	onfi[1] = NFC_PDD_GetID2(NFC_DEVICE);
	onfi[2] = NFC_PDD_GetID3(NFC_DEVICE);
	onfi[3] = NFC_PDD_GetID4(NFC_DEVICE);
	MSGLN("NAND 0 read ID returned %s",onfi);
#if NFC_NCHIPS > 1
	nfc_read_flash_id(1, NFC_READID_ONFI);
	onfi[0] = NFC_PDD_GetID1(NFC_DEVICE);
	onfi[1] = NFC_PDD_GetID2(NFC_DEVICE);
	onfi[2] = NFC_PDD_GetID3(NFC_DEVICE);
	onfi[3] = NFC_PDD_GetID4(NFC_DEVICE);
	MSGLN("NAND 1 read ID returned %s",onfi);
#endif
	
}

// see http://all-about-uffs.blogspot.com/2010/02/writing-nand-driver-for-uffs.html

static void setup_flash_storage(struct uffs_StorageAttrSt *attr)
{
	memset(attr, 0, sizeof(struct uffs_StorageAttrSt));
	const char data_layout[] = {0x01, sizeof(uffs_Tags), 0xFF, 0x00};
	const char ecc_layout[] = {(UFFS_MAX_SPARE_SIZE-UFFS_MAX_ECC_SIZE), UFFS_MAX_ECC_SIZE, 0xFF, 0x00};	/* Kinetis ECC is at end of spare block */
	
	// setup NAND flash attributes.	
	attr->total_blocks = TOTAL_BLOCKS;			/* total blocks */
	attr->page_data_size = PAGE_DATA_SIZE;		/* page data size */
	attr->pages_per_block = PAGES_PER_BLOCK;	/* pages per block */
	attr->spare_size = PAGE_SPARE_SIZE;		  	/* page spare size */
	attr->block_status_offs = 1;					/* beginning of spare area (NAND chip dependent) */
	attr->ecc_opt = UFFS_ECC_HW_AUTO;              /* ecc option */
	attr->ecc_size = UFFS_MAX_ECC_SIZE;				// not really used when ECC_HW_AUTO except debug message
	attr->layout_opt = UFFS_LAYOUT_FLASH;        /* let driver do the spare layout */  
	memcpy( attr->_uffs_data_layout, data_layout, sizeof(data_layout));
	memcpy( attr->_uffs_ecc_layout, ecc_layout, sizeof(ecc_layout));	// not used when UFFS_LAYOUT_FLASH
}

static URET my_InitDevice(uffs_Device *dev)
{
	dev->attr = &my_flash_storage;			// NAND flash attributes
//	dev->attr->_private = (void *) &g_nand_chip;// hook nand_chip data structure to attr->_private
	dev->ops = &my_flash_ops;					// NAND driver

//	init_nand_chip(&g_nand_chip);
	init_nand_chip();
    
	return U_SUCC;
}

static URET my_ReleaseDevice(uffs_Device *dev)
{
	return U_SUCC;
}


int my_init_filesystem(void)
{
	uffs_MountTable *mtbl = get_flash_mount_table();

	/* setup nand storage attributes */
	setup_flash_storage(&my_flash_storage);

	/* setup memory allocator */
	//	uffs_MemSetupStaticAllocator(&flash_partition_1.mem, static_buffer_par1, sizeof(static_buffer_par1));
	//	uffs_MemSetupStaticAllocator(&flash_partition_2.mem, static_buffer_par2, sizeof(static_buffer_par2));
	uffs_MemSetupSystemAllocator(&flash_partition_1.mem);
	uffs_MemSetupSystemAllocator(&flash_partition_2.mem);

	/* register mount table */
	while(mtbl->dev) {
		// setup device init/release entry
		mtbl->dev->Init = my_InitDevice;
		mtbl->dev->Release = my_ReleaseDevice;
		uffs_RegisterMountTable(mtbl);
		mtbl++;
	}

	// mount partitions
	for (mtbl = get_flash_mount_table(); mtbl->mount != NULL; mtbl++) {
		uffs_Mount(mtbl->mount);
	}

	return uffs_InitFileSystemObjects() == U_SUCC ? 0 : -1;
}

int my_release_filesystem(void)
{
	uffs_MountTable *mtbl;
	int ret = 0;

	// unmount partions & unregister mount tables
	for (mtbl = get_flash_mount_table(); /*ret == 0 &&*/ mtbl->mount != NULL; mtbl++) {
		ret = uffs_UnMount(mtbl->mount);
		uffs_UnRegisterMountTable(mtbl);
	}

	
	// release objects
//	if (ret == 0)
		ret = (uffs_ReleaseFileSystemObjects() == U_SUCC ? 0 : -1);

	return ret;
}

/* application entry */
/*
int main()
{
	uffs_SetupDebugOutput(); 	// setup debug output as early as possible

	my_init_filesystem();

	// ... my application codes ....
	// read/write/create/delete files ...

	my_release_filesystem();

	return 0;
}
*/

//#endif


/////////////////////////////////////////////////////////////////////////////////

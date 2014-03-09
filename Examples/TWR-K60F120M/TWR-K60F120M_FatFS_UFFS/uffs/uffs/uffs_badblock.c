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
 * \file uffs_badblock.c
 * \brief bad block checking and recovering
 * \author Ricky Zheng, created in 13th Jun, 2005
 */
#include "uffs_config.h"
#include "uffs/uffs_fs.h"
#include "uffs/uffs_ecc.h"
#include "uffs/uffs_badblock.h"
#include <string.h>

#define PFX "bbl : "

static const char *uffs_BadBlockPendingTypeName(int mark)
{
	switch (mark) {
	case UFFS_PENDING_BLK_RECOVER: 	return "Recover";
	case UFFS_PENDING_BLK_REFRESH: 	return "Refresh";
	case UFFS_PENDING_BLK_CLEANUP: 	return "Cleanup";
	default: 						return "Unknown";
	}
}

void uffs_BadBlockInit(uffs_Device *dev)
{
	dev->pending.count = 0;
	dev->pending.block_in_recovery = UFFS_INVALID_BLOCK;
}


/** 
 * \brief process bad block: mark it as 'bad'
 *			and put the node to bad block list.
 * \param[in] dev uffs device
 * \param[in] node bad block tree node
 *			(before the block turn 'bad', it must belong to something ...)
 */
void uffs_BadBlockProcessNode(uffs_Device *dev, TreeNode *node)
{
	if (node) {
		// mark bad block.
		uffs_FlashMarkBadBlock(dev, node->u.list.block);

		// and put it into bad block list
		uffs_TreeInsertToBadBlockList(dev, node);
	}
}


static void process_pending_recover(uffs_Device *dev, uffs_PendingBlock *s)
{
	TreeNode *good, *bad;
	uffs_Buf *buf;
	u16 i;
	u16 page;
	uffs_BlockInfo *bc = NULL, *newBc = NULL;
	uffs_Tags *tag, *newTag;
	uffs_Tags local_tag;
	UBOOL succRecov;
	UBOOL goodBlockIsDirty;
	int ret;
	int region;
	u8 type;

	//recover block
	bc = uffs_BlockInfoGet(dev, s->block);
	if (bc == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS, "can't get bad block info");
		return;
	}

	region = SEARCH_REGION_DIR|SEARCH_REGION_FILE|SEARCH_REGION_DATA;
	bad = uffs_TreeFindNodeByBlock(dev, s->block, &region);
	if (bad == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS,
					"can't find the reported bad block(%d) in the tree ? probably already been processed.",
					s->block);
		uffs_BlockInfoPut(dev, bc);
		return;
	}

retry:
	// pick up an erased good block
	good = uffs_TreeGetErasedNode(dev);
	if (good == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS, "no free block to replace bad block!");
		uffs_BlockInfoPut(dev, bc);
		return;
	}

	goodBlockIsDirty = U_FALSE;
	succRecov = U_TRUE;

	// check if the new block block info cache being loaded before ...
	newBc = uffs_BlockInfoFindInCache(dev, good->u.list.block);

	// read all spares of old block
	uffs_BlockInfoLoad(dev, bc, UFFS_ALL_PAGES);

	for (i = 0; i < dev->attr->pages_per_block; i++) {
		page = uffs_FindPageInBlockWithPageId(dev, bc, i);
		if (page == UFFS_INVALID_PAGE) {
			break;  //end of last valid page, normal break
		}
		page = uffs_FindBestPageInBlock(dev, bc, page);
		if (page == UFFS_INVALID_PAGE) {
			// got an invalid page ? it's bad block anyway ...
			uffs_Perror(UFFS_MSG_SERIOUS, "bad block recover (block %d) not finished!", bc->block);
			break;
		}
		tag = GET_TAG(bc, page);
		buf = uffs_BufClone(dev, NULL);
		if (buf == NULL) {	
			uffs_Perror(UFFS_MSG_SERIOUS, "Can't clone a new buf!");
			succRecov = U_FALSE;
			break;
		}

		ret = uffs_FlashReadPage(dev, bc->block, page, buf, U_FALSE);

		if (UFFS_FLASH_HAVE_ERR(ret)) {
			if (UFFS_FLASH_IS_BAD_BLOCK(ret)) {
				//NOTE: Since we are trying to recover data from a 'bad' block, we can't guarantee the data is ECC ok.
				//		If data is corrupted we can't do anything about it ...
				uffs_Perror(UFFS_MSG_NORMAL,
							"Read block %d page %d, return bad block or ECC failure, data corrupted!",
							bc->block, page);
			}
			else if (ret == UFFS_FLASH_IO_ERR) {
				// I/O error ? abort the mission.
				buf->mark = UFFS_BUF_EMPTY;
				uffs_Perror(UFFS_MSG_SERIOUS, "I/O error ? abort.");
				uffs_BufFreeClone(dev, buf);
				succRecov = U_FALSE;
				break;
			}
		}

		buf->mark = UFFS_BUF_VALID;
		buf->data_len = TAG_DATA_LEN(tag);
		if (buf->data_len > dev->com.pg_data_size) {
			uffs_Perror(UFFS_MSG_NOISY, "data length over flow!!!");
			buf->data_len = dev->com.pg_data_size;
		}

		buf->parent = TAG_PARENT(tag);
		buf->serial = TAG_SERIAL(tag);
		buf->type = TAG_TYPE(tag);
		buf->page_id = TAG_PAGE_ID(tag);
		
		// if good block info already been loaded then use it, otherwise use local tag
		if (newBc) {
			newTag = GET_TAG(newBc, i);
		}
		else {
			newTag = &local_tag;
		}

		// new tag copied from old tag, and increase time-stamp.
		*newTag = *tag;
		TAG_BLOCK_TS(newTag) = uffs_GetNextBlockTimeStamp(TAG_BLOCK_TS(tag));

		ret = uffs_FlashWritePageCombine(dev, good->u.list.block, i, buf, newTag);

		uffs_BufFreeClone(dev, buf);

		if (UFFS_FLASH_IS_BAD_BLOCK(ret)) {
			// put back block info cache before retry
			if (newBc)
				uffs_BlockInfoPut(dev, newBc);
		
			// we have a new bad block ? mark it and retry.
			uffs_Perror(UFFS_MSG_NOISY, "A new bad block is discovered during bad block recover ...");
			uffs_BadBlockProcessNode(dev, good);
			goto retry;
		}

		goodBlockIsDirty = U_TRUE;

		if (ret == UFFS_FLASH_IO_ERR) {
			uffs_Perror(UFFS_MSG_NORMAL, "I/O error ? abort.");
			succRecov = U_FALSE;
			break;
		}
	}

	// put back block info cache
	if (newBc)
		uffs_BlockInfoPut(dev, newBc);

	if (succRecov == U_TRUE) {
		// successful recover bad block, so need to mark bad block,
		// and replace with good one

		switch (region) {
		case SEARCH_REGION_DIR:
			bad->u.dir.block = good->u.list.block;
			type = UFFS_TYPE_DIR;
			break;
		case SEARCH_REGION_FILE:
			bad->u.file.block = good->u.list.block;
			type = UFFS_TYPE_FILE;
			break;
		case SEARCH_REGION_DATA:
			bad->u.data.block = good->u.list.block;
			type = UFFS_TYPE_DATA;
		}
			
		//from now, the 'bad' is actually good block :)))
		uffs_Perror(UFFS_MSG_NOISY,
					"recovered bad block %d replaced by %d, type %d!",
					s->block, good->u.list.block, type);
		uffs_BlockInfoExpire(dev, bc, UFFS_ALL_PAGES);

		//we reuse the 'good' node as bad block node, and process the bad block.
		good->u.list.block = s->block;

		if (s->mark == UFFS_PENDING_BLK_RECOVER) {
			uffs_BadBlockProcessNode(dev, good);
		}
		else if (s->mark == UFFS_PENDING_BLK_REFRESH ||
				 s->mark == UFFS_PENDING_BLK_CLEANUP) {
			uffs_TreeEraseNode(dev, good);
			uffs_TreeInsertToErasedListTail(dev, good); //put back to erased list
		}
		else {
			uffs_Perror(UFFS_MSG_SERIOUS, "Unrecognized pending mark: %d", s->mark);
		}
	}
	else {
		if (goodBlockIsDirty == U_TRUE) {
			uffs_TreeEraseNode(dev, good);	// erase the block if the block is dirty
		}
		uffs_TreeInsertToErasedListTail(dev, good); //put back to erased list
	}

	uffs_BlockInfoPut(dev, bc);
	
}

/** 
 * \brief recover bad block
 * \param[in] dev uffs device
 */
void uffs_BadBlockRecover(uffs_Device *dev)
{
	uffs_PendingBlock *s;

	while (dev->pending.count > 0) {
		dev->pending.count--;
		s = &dev->pending.list[dev->pending.count];
		uffs_Perror(UFFS_MSG_NOISY, "Process pending block %d - %s", 
						s->block, uffs_BadBlockPendingTypeName(s->mark));
		dev->pending.block_in_recovery = s->block;
		process_pending_recover(dev, s);
	}
	dev->pending.block_in_recovery = UFFS_INVALID_BLOCK;
}


/** put a new block to the bad block pending list */
void uffs_BadBlockAdd(uffs_Device *dev, int block, u8 mark)
{
	uffs_PendingBlock *s;
	int i;

	// check if the block is being processed right now 
	if (dev->pending.block_in_recovery == block)
		return;

	// check if the block already in pending list
	for (i = 0; i < dev->pending.count; i++) {
		s = &dev->pending.list[i];
		if (s->block == block) {
			if (s->mark != mark &&
				s->mark == UFFS_PENDING_BLK_REFRESH &&
				mark == UFFS_PENDING_BLK_RECOVER)	// RECOVER would overwrite REFRESH, but not vice versa.
			{	
				s->mark = mark;
				uffs_Perror(UFFS_MSG_NOISY, "Change pending block %d - %s",
								block, uffs_BadBlockPendingTypeName(s->mark));
			}
			return;
		}
	}

	// check if there is space in pending list		
	if (dev->pending.count >= CONFIG_MAX_PENDING_BLOCKS) {
		uffs_Perror(UFFS_MSG_SERIOUS, 
					"Too many pending bad blocks, please increase CONFIG_MAX_PENDING_BLOCKS !");
		return;
	}

	// add new pending block
	s = &dev->pending.list[dev->pending.count++];
	s->block = block;
	s->mark = mark;
	uffs_Perror(UFFS_MSG_NOISY, "Add pending block %d - %s",
					block, uffs_BadBlockPendingTypeName(mark));
}

/**
 * Check if a block is in bad block pending list
 * \return U_TRUE if block in pending list, U_FALSE if not.
 */
UBOOL uffs_BadBlockPendingCheck(uffs_Device *dev, int block)
{
	int i;

	for (i = 0; i < dev->pending.count; i++) {
		if (dev->pending.list[i].block == block)
			return U_TRUE;
	}

	return U_FALSE;
}

/**
 * Remove block from pending list
 * \return U_SUCC if the block is removed from pending list, U_FAIL if no block removed.
 */
URET uffs_BadBlockPendingRemove(uffs_Device *dev, int block)
{
	int i;

	for (i = 0; i < dev->pending.count; i++) {
		if (dev->pending.list[i].block == block)
			break;
	}

	if (i < dev->pending.count) {
		uffs_Perror(UFFS_MSG_NOISY, "pending block %d removed", dev->pending.list[i].block);
		for (; i < dev->pending.count - 1; i++) {
			dev->pending.list[i] = dev->pending.list[i+1];
		}
		dev->pending.count--;
		return U_SUCC;
	}
	else {
		return U_FAIL;
	}
}

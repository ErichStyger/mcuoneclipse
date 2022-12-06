/*
 * w25_interface.c
 *
 *  Created on: 23.05.2022
 *      Author: cc-isn
 */
#include "w25_interface.h"
#include "sha-256.h"


uint8_t W25_read_block_for_SHA(lfs_t *lfs, lfs_file_t* file, size_t nofBytes,  void *outputHASH) {
	struct Sha_256 sha_256;
	uint8_t hash[32];
	sha_256_init(&sha_256, outputHASH);

	static int32_t filePos;
	size_t fileSize;
	uint8_t buf[512];

	if( nofBytes > 512) {
		nofBytes = 512;
	}

	lfs_file_rewind(lfs,file);
	filePos = 0;

	fileSize = lfs_file_size(lfs, file);
	filePos = lfs_file_tell(lfs, file);
	fileSize = fileSize - filePos;

	while(fileSize>0){

		if(fileSize > nofBytes)  {
			if (lfs_file_read(lfs, file, buf, nofBytes) < 0) {
				return ERR_FAILED;
			}
			sha_256_write(&sha_256, buf, 512);

		} else {
			if (lfs_file_read(lfs, file, buf, fileSize) < 0) {
			}
			sha_256_write(&sha_256, buf, fileSize);
			sha_256_close(&sha_256);
			return ERR_PARAM_SIZE; //EOF
		}

		filePos = filePos + nofBytes;
		bzero(buf, nofBytes);
		filePos = lfs_file_tell(lfs, file);
		fileSize = fileSize - nofBytes;
	}
  return 0;
}

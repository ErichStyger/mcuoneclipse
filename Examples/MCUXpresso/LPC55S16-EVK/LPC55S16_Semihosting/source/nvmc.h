/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef NVMC_H_
#define NVMC_H_

#include "platform.h"
#include <stdint.h>
#include <stdbool.h>
#include "McuShell.h"

#define NVMC_VERSION_1_0  (10) /* initial version */

#define NVMC_CURRENT_VERSION    NVMC_VERSION_1_0 /* active and current version */

#define NVMC_FLAGS_MAGNET_ENABLED   (1<<0)  /* if magnets are present */

/* buffers need to be this size for flash programming! */
#if McuLib_CONFIG_CPU_IS_LPC55xx
  #define NVMC_ALIGNED_BLOCK_SIZE  512
#else
  #define NVMC_ALIGNED_BLOCK_SIZE  64
#endif


typedef struct {
  uint32_t version; /* NVMC_CURRENT_VERSION, must be 32bit type to have struct 4 byte aligned! */
  uint32_t flags; /* generic flags  */
  /* fill up to 64 or 128 bytes, needed for flash programming! */
  uint8_t filler[NVMC_ALIGNED_BLOCK_SIZE-4-4];
} NVMC_Data_t;

/*!
 * \brief Returns a pointer to the data or NULL if the data is not present (erased)
 */
const NVMC_Data_t *NVMC_GetDataPtr(void);

uint8_t NVMC_WriteConfig(NVMC_Data_t *data);

uint8_t NVMC_Getflags(void);

bool NVMC_IsErased(void);

uint8_t NVMC_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

bool NVMC_HasValidConfig(void);

void NVMC_Deinit(void);
void NVMC_Init(void);

#endif /* NVMC_H_ */

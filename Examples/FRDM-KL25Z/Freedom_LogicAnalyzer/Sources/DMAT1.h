/*
 * DMAT1.h
 *
 *  Created on: Mar 20, 2013
 *      Author: reinerg
 */

#ifndef DMAT1_H_
#define DMAT1_H_

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

LDD_TError  DMAT1_Init(void);
LDD_TError  DMAT1_EnableChannel0(void);
LDD_TError  DMAT1_DisableChannel0(void);
LDD_TError  DMAT1_SetDestinationAddress0(uint32_t dest);
LDD_TError  DMAT1_SetDestinationTransferSize0(uint16_t size);
LDD_TError  DMAT1_StartTransfer0(void);

#endif /* DMAT1_H_ */

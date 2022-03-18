/*
 * fragment_Data_handler.c
 *
 * \brief     handles the fragments received for the FUOTA
 *
 *  Created on: 23.12.2021
 *      Author: Corsin Obrist
 */

#include <stdio.h>
#include "../firmwareVersion.h"
#include "../../common/githubVersion.h"
#include "fragment_Data_handler.h"
#include "utilities.h"
#include "board-config.h"
#include "board.h"
#include "boards/board.h"
#include "gpio.h"
#include "uart.h"
#include "RegionCommon.h"
#include "lpm-board.h"
#include "gps.h"

#include "cli.h"
#include "Commissioning.h"
#include "LmHandler.h"
#include "LmhpCompliance.h"
#include "CayenneLpp.h"
#include "LmHandlerMsgDisplay.h"

#define FRAGMENT_NumberOffset 					2


static uint16_t fragmentCnt = 0;
static FragmtError_t  errorStat= ERROR_OK;
fuota_meta_t fuota_meta_data;
int *ptr_Fuota_Data;

static uint8_t checkMetaData(fuota_meta_t fuota_meta);

uint8_t FUOTA_FW_Meta_Data(LmHandlerAppData_t* appData)
{
	fuota_meta_t fuota_meta;

	if(appData->BufferSize==16)
	{
		fuota_meta.fw_fragm_numbers = (appData->Buffer[3]<<24) + (appData->Buffer[2]<<16) + (appData->Buffer[1]<<8) + appData->Buffer[0];
		fuota_meta.fw_pack_size = (appData->Buffer[7]<<24) + (appData->Buffer[6]<<16) + (appData->Buffer[5]<<8) + appData->Buffer[4];
		fuota_meta.fw_fragm_size = (appData->Buffer[11]<<24) + (appData->Buffer[10]<<16) + (appData->Buffer[9]<<8) + appData->Buffer[8];
		fuota_meta.fw_version = (appData->Buffer[12]<<24) + (appData->Buffer[13]<<16) + (appData->Buffer[14]<<8) + appData->Buffer[15];
		return checkMetaData(fuota_meta);
	}
	else{
		 return set_FuotaErrorState(ERROR_FragmentSize);
	}
}

void alloc_Fuota_Data_buf(void){
	//first 4 bytes are from the Fragmentcounter
	ptr_Fuota_Data = (int*)calloc((((int)(get_fw_fragm_size()-FRAGMENT_NumberOffset)/4)+1), sizeof(int8_t)*get_fragm_numbers());
}

uint8_t FUOTA_FW_Fragmt_Data(LmHandlerAppData_t* appData)
{
	uint32_t fragmtNumber = (appData->Buffer[0]<<8) + appData->Buffer[1];
	set_FragmentCnt(fragmtNumber);
	uint32_t pointer_offset = (((int)(get_fw_fragm_size()-FRAGMENT_NumberOffset)/4)+1)*(fragmtNumber-1);
	uint32_t forLoopSteps = (uint32_t)((appData->BufferSize)-FRAGMENT_NumberOffset);
	uint32_t restSteps = forLoopSteps%4;
	int ii =0;
	for(ii; ii < (uint32_t)(forLoopSteps/4); ++ii)
	{
		ptr_Fuota_Data[pointer_offset+ii] = (appData->Buffer[FRAGMENT_NumberOffset+(ii*4)+0]<<24)+(appData->Buffer[FRAGMENT_NumberOffset+(ii*4)+1]<<16)+(appData->Buffer[FRAGMENT_NumberOffset+(ii*4)+2]<<8)+(appData->Buffer[FRAGMENT_NumberOffset+(ii*4)+3]);
	}

	for(int i = 0; i < restSteps; ++i)
	{
		ptr_Fuota_Data[pointer_offset+ii] = (ptr_Fuota_Data[pointer_offset+ii] | (appData->Buffer[(appData->BufferSize)-(restSteps-i)]<<((restSteps-1-i)*8)));
	}


	return set_FuotaErrorState(ERROR_OK);
}

uint8_t FUOTA_FW_FINISH_Data(LmHandlerAppData_t* appData)
{
	uint32_t finishMsg = (appData->Buffer[0]);
	if(finishMsg == 0xFF){
		return set_FuotaErrorState(ERROR_OK);
	}

	return set_FuotaErrorState(ERROR_FINISH_MSG);
}



static uint8_t checkMetaData(fuota_meta_t fuota_meta)
{

	if((fuota_meta.fw_fragm_size*fuota_meta.fw_fragm_numbers) >=fuota_meta.fw_pack_size){
		return set_FuotaErrorState(ERROR_FW_Size);
	}
	if((fuota_meta.fw_version <= LPC_55S16_Node_FW_Version) || (fuota_meta.fw_version <= fw_verison)){
		return set_FuotaErrorState(ERROR_FW_Version);
	}
	else{
		set_fuota_meta_data(fuota_meta);
		fw_verison = fuota_meta.fw_version;
	}

    alloc_Fuota_Data_buf();
	return set_FuotaErrorState(ERROR_OK);
}


uint8_t FUOTA_Ready_Data( uint8_t* dst )
{
	//getFW_Version uint16
	uint32_t freeSpace = 65512;
	uint8_t PrePrpoData[FuotaReady_BUFFER_MAX_SIZE];
    PrePrpoData[0] = 0x01;
    PrePrpoData[1] = (uint8_t)(0xFF &(freeSpace>>24));
    PrePrpoData[2] = (uint8_t)(0xFF &(freeSpace>>16));
    PrePrpoData[3] = (uint8_t)(0xFF &(freeSpace>>8));
    PrePrpoData[4] = (uint8_t)(0xFF &(freeSpace>>0));
    memcpy1( dst, PrePrpoData, PrePrpoData_BUFFER_MAX_SIZE );

    return FuotaReady_BUFFER_MAX_SIZE;
}

uint8_t FUOTA_Error_Data( uint8_t* dst )
{
	//getFW_Version uint16
	uint16_t frag_cnt = get_FragmentCnt();
	uint16_t errorState = (uint16_t)get_FuotaErrorState();
	uint8_t PrePrpoData[FuotaError_BUFFER_MAX_SIZE];
    PrePrpoData[0] = (uint8_t)(0xFF &(frag_cnt>>8));;
    PrePrpoData[1] = (uint8_t)(0xFF &frag_cnt);
    PrePrpoData[2] = (uint8_t)(0xFF &(errorState>>8));;
    PrePrpoData[3] = (uint8_t)(0xFF &errorState);
    memcpy1( dst, PrePrpoData, FuotaError_BUFFER_MAX_SIZE );

    return FuotaError_BUFFER_MAX_SIZE;
}


uint8_t FUOTA_PrePro_Data( uint8_t* dst )
{
	//getFW_Version uint16
	int fwVersion = fw_verison;
	uint8_t PrePrpoData[PrePrpoData_BUFFER_MAX_SIZE];
    DeviceClass_t actClass =  LmHandlerGetCurrentClass();
    PrePrpoData[0] = 0x00;
    PrePrpoData[1] = actClass;
    PrePrpoData[2] = 0x00;
    PrePrpoData[3] = 0x00;
    PrePrpoData[4] = 0x00;
    PrePrpoData[5] = 0x01;

    PrePrpoData[6] = (uint8_t)(0xFFFFFFFF &(fwVersion>>32));
    PrePrpoData[7] = (uint8_t)(0xFFFFFF &(fwVersion>>24));
    PrePrpoData[8] =(uint8_t)(0xFFFF &(fwVersion>>16));
    PrePrpoData[9] = (uint8_t)(0xFF &(fwVersion>>8));
    PrePrpoData[10] =(uint8_t)(fwVersion);

    memcpy1( dst, PrePrpoData, PrePrpoData_BUFFER_MAX_SIZE );

    return PrePrpoData_BUFFER_MAX_SIZE;
}


uint8_t FUOTA_Fragment_rcv_Answer( uint8_t* dst )
{
	uint16_t frag_cnt = get_FragmentCnt();
	uint8_t PrePrpoData[FragmentINFO_BUFFER_MAX_SIZE];
    PrePrpoData[0] = (uint8_t)(0xFF &(frag_cnt>>8));
    PrePrpoData[1] =(uint8_t)(0xFF &frag_cnt);
    PrePrpoData[2] = (uint8_t)(0xFF &(get_FuotaErrorState()>>8));
    PrePrpoData[3] =(uint8_t)(0xFF &get_FuotaErrorState());

    memcpy1( dst, PrePrpoData, FragmentINFO_BUFFER_MAX_SIZE );

    return FragmentINFO_BUFFER_MAX_SIZE;
}


uint8_t FUOTA_FINISH_rcv_Answer( uint8_t* dst )
{
	uint16_t frag_cnt = get_FragmentCnt();
	uint8_t PrePrpoData[FragmentINFO_BUFFER_MAX_SIZE];
    PrePrpoData[0] = (uint8_t)(0xFF &(frag_cnt>>8));
    PrePrpoData[1] =(uint8_t)(0xFF &frag_cnt);
    PrePrpoData[2] = (uint8_t)(0xFF);
    PrePrpoData[3] =(uint8_t)(0xFF);

    memcpy1( dst, PrePrpoData, FragmentINFO_BUFFER_MAX_SIZE );

    return FragmentINFO_BUFFER_MAX_SIZE;
}



void incFragmentCnt(void){
	fragmentCnt++;
}

void decFragmentCnt(void){
	fragmentCnt--;
}

void set_FragmentCnt( uint16_t cnt){
	fragmentCnt = cnt;
}

uint16_t get_FragmentCnt(void){
	return fragmentCnt;
}

FragmtError_t set_FuotaErrorState( FragmtError_t error){
	errorStat = error;
	return get_FuotaErrorState();
}

FragmtError_t get_FuotaErrorState(void){
	return errorStat;
}


int fuota_nvm_init()
{
	fuota_meta_data.fw_fragm_numbers = 0;
	fuota_meta_data.fw_fragm_size = 0;
	fuota_meta_data.fw_pack_size = 0;
	fuota_meta_data.fw_version = 0;
    return 0;
}


int set_fuota_meta_data(fuota_meta_t fuota_meta)
{
	fuota_meta_data.fw_fragm_numbers = fuota_meta.fw_fragm_numbers;
	fuota_meta_data.fw_fragm_size = fuota_meta.fw_fragm_size;
	fuota_meta_data.fw_pack_size = fuota_meta.fw_pack_size;
	fuota_meta_data.fw_version = fuota_meta.fw_version;
    return 0;
}

fuota_meta_t*  get_fuota_meta_data(void)
{
    return &fuota_meta_data;
}

uint32_t get_fragm_numbers(void)
{
    return fuota_meta_data.fw_fragm_numbers;
}

uint32_t get_fw_fragm_size(void)
{
    return fuota_meta_data.fw_fragm_size;
}

uint32_t get_fw_pack_size(void)
{
    return fuota_meta_data.fw_pack_size;
}

uint32_t get_fw_version(void)
{
    return fuota_meta_data.fw_version;
}




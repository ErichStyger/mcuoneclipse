/*
 * fragment_Data_handler.h
 *
 *  Created on: 23.12.2021
 *      Author: Corsin Obrist
 */

#ifndef SRC_APPS_LORAMAC_FW_UPDATE_LPC55S16_EVK_FRAGMENT_DATA_HANDLER_H_
#define SRC_APPS_LORAMAC_FW_UPDATE_LPC55S16_EVK_FRAGMENT_DATA_HANDLER_H_

#include "LmHandler.h"
/*!
 * FUOTA PrePrpoDat data buffer size
 */
#define PrePrpoData_BUFFER_MAX_SIZE            11

/*!
 * FUOTA PrePrpoDat data buffer size
 */
#define FragmentINFO_BUFFER_MAX_SIZE            4

/*!
 * FUOTA PrePrpoDat data buffer size
 */
#define FuotaReady_BUFFER_MAX_SIZE            5

/*!
 * FUOTA PrePrpoDat data buffer size
 */
#define FuotaError_BUFFER_MAX_SIZE            4
/*!
 * LoRaWAN USERDEFINED LORAWAN_FRAGMENTED application port
 * @note do not use 224. It is reserved for certification
 */
#define LORAWAN_FRAGMENTED_BLOCK_PORT               11


/*!
 * LoRaWAN USERDEFINED LORAWAN_FRAGMENTED application port
 *
 */
#define FUOTA_PRE_PROCESS               12


/*!
 * LoRaWAN USERDEFINED LORAWAN_FRAGMENTED application port
 * @note do not use 224. It is reserved for certification
 */
#define FUOTA_FRAGMENT_HANDLING               13


/*!
 * LoRaWAN USERDEFINED LORAWAN_FRAGMENTED application port
 * @note do not use 224. It is reserved for certification
 */
#define FUOTA_FRAGMENT_INFO               14




typedef enum FragmtError_e
{
    ERROR_OK = 0x00,
	ERROR_FragmentSize = 0x01,
	ERROR_FW_Size = 0x02,
	ERROR_FW_Version = 0x03,
	ERROR_Undefined = 0x04,
	ERROR_FINISH_MSG = 0x05
}FragmtError_t;


typedef enum FuotaState_e
{
    IDLE = 0x00,
	CONF_CLASS_C = 0x01,
	CONF_READY = 0x02,
	FRAG_INFO = 0x03,
	FRAGMENT_RECEIVING = 0x04,
	Error_State = 0x05,
	FINISH = 0x06,
	UPDATE_NODE = 0x07
}FuotaState_t;

typedef struct
{
    uint32_t fw_pack_size;
    uint32_t fw_fragm_size;
    uint32_t fw_fragm_numbers;  /* max retry count after app call set_update_flag */
    uint32_t fw_version;  /* max retry count after app call set_update_flag */
}fuota_meta_t;


uint8_t FUOTA_FW_Meta_Data( LmHandlerAppData_t* appData);
uint8_t FUOTA_FW_Fragmt_Data(LmHandlerAppData_t* appData);
uint8_t FUOTA_FW_FINISH_Data(LmHandlerAppData_t* appData);
uint8_t FUOTA_FW_Fragment( uint8_t* dst );
uint8_t FUOTA_Ready_Data( uint8_t* dst );
uint8_t FUOTA_Error_Data( uint8_t* dst );
uint8_t FUOTA_PrePro_Data( uint8_t* dst );
uint8_t FUOTA_Fragment_rcv_Answer( uint8_t* dst );
uint8_t FUOTA_FINISH_rcv_Answer( uint8_t* dst );


void incFragmentCnt(void);
void decFragmentCnt(void);
void set_FragmentCnt( uint16_t cnt);
uint16_t get_FragmentCnt(void);

FragmtError_t set_FuotaErrorState( FragmtError_t error);
FragmtError_t get_FuotaErrorState(void);

int fuota_nvm_init(void);

fuota_meta_t* get_fuota_meta_data(void);


uint32_t get_fragm_numbers(void);


uint32_t get_fw_fragm_size(void);


uint32_t get_fw_pack_size(void);


uint32_t get_fw_version(void);
int set_fuota_meta_data(fuota_meta_t fuota_meta);




#endif /* SRC_APPS_LORAMAC_FW_UPDATE_LPC55S16_EVK_FRAGMENT_DATA_HANDLER_H_ */


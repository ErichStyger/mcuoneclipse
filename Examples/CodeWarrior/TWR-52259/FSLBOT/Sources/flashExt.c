/**
 *\file
 *\brief Implements the driver for a AT25DF641 64MBit flash chip, to communicate with SPI.
 *\author Andreas Schoepfer andreas.schoepfer@stud.hslu.ch
 *\date 23.11.11
 */

#include "flashExt.h"
#include "FLASH_CS.h"
#include "FLASH_WP.h"
#include "WAIT1.h"
#include "SM1.h"

static void  ChipSelectOn(void) {
	FLASH_CS_PutVal(FALSE);
}

static void ChipSelectOff(void) {
	FLASH_CS_PutVal(TRUE);
}

/**
 * Invoke before erasing or writing to flash. After writing or erasing,
 * the WEL-Bit gets automatically cleared by the chip. The WEL-Bit indicated
 * in the status registers. 
 */
static uint8_t SetWELBit(void) {
  uint8_t errCode;
  
  ChipSelectOn();
  errCode = SM1_SendChar(0x06);
  if(errCode != ERR_OK) {
	  return errCode;
  }
  ChipSelectOff();
  WAIT1_WaitOSms(1);				/* Delay for reset*/
  ChipSelectOn();
  WAIT1_WaitOSms(10);				/* Wait till flash ready to write*/
  return errCode;
}

static uint8_t SendAddr(uint32_t addr) { 
  uint8_t errCode;
  
  /* send high-byte*/
  errCode = SM1_SendChar((uint8_t)((addr&0xFF0000)>>16));
  if(errCode != ERR_OK) {
    return errCode; /* error occurred!*/
  }
  /* send mid-byte*/
  errCode = SM1_SendChar((uint8_t)((addr&0xFF00)>>8));
  if(errCode != ERR_OK) {
    return errCode; /* error occurred!*/
  }
  /* send low-byte*/
  return (SM1_SendChar((uint8_t)(addr&0xFF)));
}

uint8_t FLASH_ReadStatusReg(uint8_t* statusReg) {
  uint8_t errCode;
    
  ChipSelectOn();		                 /* Activate flash */
  errCode = SM1_SendChar(0x05);
  if (errCode != ERR_OK) {
    return errCode;
  }
  errCode = SM1_RecvChar(statusReg);
  ChipSelectOff();
  return errCode;                        /* Return error code */
}

uint8_t FLASH_ReadByte(uint32_t addr, uint8_t* data) {
	uint8_t errCode;
	
	ChipSelectOn();
	errCode = SM1_SendChar(0x03);
	if(errCode != ERR_OK) {
		ChipSelectOff();
		return errCode;
	}
	errCode = SendAddr(addr);
	if(errCode != ERR_OK) {
		ChipSelectOff();
		return errCode;
	}
	errCode = SM1_RecvChar(data);
	ChipSelectOff();
	return errCode;
}

uint8_t FLASH_WriteByte(uint32_t addr, uint8_t* data) {
  uint8_t errCode;
  
  errCode = SetWELBit();
  if(errCode != ERR_OK) {
  	ChipSelectOff();
  	return errCode;
  }
  errCode = SM1_SendChar(0x02);
  if(errCode != ERR_OK) {
  	ChipSelectOff();
  	return errCode;
  }
  errCode = SendAddr(addr);
  if(errCode != ERR_OK) {
  	ChipSelectOff();
  	return errCode;
  }
  errCode = SM1_SendChar(*data);
  ChipSelectOff();	/* Additionally check operation with EPE-Bit*/
  return errCode;
}

void FLASH_Init(void) {
	FLASH_WP_PutVal(TRUE);
	ChipSelectOff();
}


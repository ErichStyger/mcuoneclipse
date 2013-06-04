/**
 *\brief Implements a driver for the MPR121 touchsensor
 *\author Andreas Schoepfer andreas.schoepfer@stud.hslu.ch
 *\date 26.10.11
 * 
 * * 
 */

#include "I2C1.h"
#include "FSSH1.h"
#include <string.h>
#include "touch.h"

/** Touchsensor I2C-address*/
#define TOUCH_DEV_ADDR			0x5A
/** I2C-register-address low, for electrodestate*/
#define ELE_LOW_ADDR			0x00
/** I2C-register-address high, for electrodestate*/
#define ELE_HIGH_ADDR			0x01
/** I2C-address, to write first config block*/
#define BLOCK1_ADDR				0x2B
/** I2C-address, to write second config block*/
#define BLOCK2_ADDR				0x41
/** I2C-address, to write third config block*/
#define BLOCK3_ADDR				0x7B
/** I2C-address, to write fourth config block*/
#define BLOCK4_ADDR				0x5D
/** Thresholdvalue for touch state*/
#define TOUCH_THRESHOLD			0x0F
/** Thresholdvalue for release state*/
#define RELEASE_THRESHOLD		0x0A



static byte block1[] = {BLOCK1_ADDR,0x01,0x01,0x00,0x00,0x01,0x01,0xFF,0x02};

static byte block2[] = {BLOCK2_ADDR,
TOUCH_THRESHOLD,RELEASE_THRESHOLD,TOUCH_THRESHOLD,RELEASE_THRESHOLD, /*ELE0&ELE1*/
TOUCH_THRESHOLD,RELEASE_THRESHOLD,TOUCH_THRESHOLD,RELEASE_THRESHOLD, /*ELE2&ELE3*/
TOUCH_THRESHOLD,RELEASE_THRESHOLD,TOUCH_THRESHOLD,RELEASE_THRESHOLD, /*ELE4&ELE5*/
TOUCH_THRESHOLD,RELEASE_THRESHOLD,TOUCH_THRESHOLD,RELEASE_THRESHOLD, /*ELE6&ELE7*/
TOUCH_THRESHOLD,RELEASE_THRESHOLD,TOUCH_THRESHOLD,RELEASE_THRESHOLD, /*ELE8&ELE9*/
TOUCH_THRESHOLD,RELEASE_THRESHOLD,TOUCH_THRESHOLD,RELEASE_THRESHOLD, /*ELE10&ELE11*/};

static byte block3[] = {BLOCK3_ADDR,0x0B,0x00,0x9C,0x65,0x8C};

static byte block4[] = {BLOCK4_ADDR,0x04,0x0C};


void TOUCH_init(void)
{

	word cnt1=0;
	word cnt2=0;
	word cnt3=0;
	word cnt4=0;
	/*Configure I2C*/
	EnterCritical();
	I2C1_SelectSlave(TOUCH_DEV_ADDR);
	/*Write default initialization to MPR121*/
	I2C1_SendBlock(&block1,sizeof(block1),&cnt1);
	I2C1_SendBlock(&block2,sizeof(block2),&cnt2);
	I2C1_SendBlock(&block3,sizeof(block3),&cnt3);
	I2C1_SendBlock(&block4,sizeof(block4),&cnt4);
	ExitCritical();
}


uint8_t TOUCH_getELE(uint16_t* status)
{
  uint8_t errCode, resultByteLow, resultByteHigh;
  
  EnterCritical();
  I2C1_SelectSlave(TOUCH_DEV_ADDR);
  errCode=I2C1_SendChar(ELE_LOW_ADDR);
  if(errCode != ERR_OK) {
    return errCode;
  }
  errCode=I2C1_RecvChar(&resultByteLow);
  if(errCode != ERR_OK) {
    return errCode;
  }
  errCode=I2C1_SendChar(ELE_HIGH_ADDR);
  if(errCode != ERR_OK) {
  	  return errCode;
  }
  errCode=I2C1_RecvChar(&resultByteHigh);
  ExitCritical();
  *status = (uint16_t)(resultByteLow + ((resultByteHigh&0x0F)<<8));
  return errCode;
}

void TOUCH_powerOff(void)
{
	word cnt0=0;
	byte block0[] = {0x5E,0x00};
	
	/*ensure that the I2C-Module communicates with the Touch-Sensor!*/
	I2C1_SelectSlave(TOUCH_DEV_ADDR);
	
	I2C1_SendBlock(&block0,sizeof(block0),&cnt0);
}
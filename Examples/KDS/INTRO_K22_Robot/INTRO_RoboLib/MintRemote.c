/*
 * MintRemote.c
 *
 *  Created on: 16.09.2016
 *      Author: Erich Styger Local
 */

#include "Platform.h"
#if PL_HAS_MINT_REMOTE
#include "MintRemote.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "UTIL1.h"
#include "GI2C1.h"
#include "RApp.h"
#include "RNet_App.h"
#include "CDC1.h"
#include "Rapp.h"
#include "RNet_AppConfig.h"

static bool ballIsPresent = FALSE;
static bool parkingStartPos = FALSE;
static bool parkingFinishPos = FALSE;

void ISR_FTM1(void); /* prototype to avoid warning */

uint8_t MINTREMOTE_HandleRemoteRxMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet) {
  uint32_t val;
  uint16_t id;

  (void)size;
  (void)packet;
  (void)srcAddr;
  switch(type) {
    case RAPP_MSG_TYPE_NOTIFY_VALUE: /* got notification value */
      id = UTIL1_GetValue16LE(data); /* extract 16bit ID (little endian) */
      if (id==RAPP_MSG_TYPE_DATA_ID_MINT_BALL) {
        val = UTIL1_GetValue32LE(&data[2]);
        /* 0: no ball, 1: ball present */
        ballIsPresent = val != 0;
        if (val==0) {
          CLS1_SendStr((uint8_t*)"NOTIFY: ball removed!\r\n", SHELL_GetStdio()->stdOut);
        } else {
          CLS1_SendStr((uint8_t*)"NOTIFY: ball received!\r\n", SHELL_GetStdio()->stdOut);
        }
      } else if (id==RAPP_MSG_TYPE_DATA_ID_POSITION) {
        val = UTIL1_GetValue32LE(&data[2]);
        if (val==1) { /* start */
          parkingStartPos = TRUE;
          parkingFinishPos = FALSE;
          CLS1_SendStr((uint8_t*)"NOTIFY: Parking Start\r\n", SHELL_GetStdio()->stdOut);
        } else if (val==2) {
          parkingStartPos = FALSE;
          parkingFinishPos = TRUE;
          CLS1_SendStr((uint8_t*)"NOTIFY: Parking Finish\r\n", SHELL_GetStdio()->stdOut);
        }
        else {
          parkingStartPos = parkingFinishPos = FALSE;
        }
      }
      *handled = TRUE;
      break;
    default:
      break;
  } /* switch */
  return ERR_OK;
}


static uint8 state;
static uint8 data2; // PCA8574

typedef enum
{
  sDown,
  sPause,
  sUp,
  sIdle,
  wait
} tState;

#define MIN_POS     1400  //1450
#define MAX_POS     3200 //2950
#define STEP        10

// Dispenser state machine
void ISR_FTM1(void)
{
  static uint16 delay;
  static uint16 sleep;

  FTM1_SC = FTM1_SC & 0x7F;
  switch (state)
  {
    case sUp:
      FTM1_C0V += STEP*10;
      if (FTM1_C0V > MAX_POS) {
        FTM1_C0V = MAX_POS;
        state = sPause;
        delay = 10;
      }
      break;

    case sPause:
      if (delay > 0) delay--;
      else state = sDown;
      break;

    case sDown:
      FTM1_C0V -= STEP;
      if (FTM1_C0V < MIN_POS) {
        FTM1_C0V = MIN_POS+30;
        state = sIdle;
        //state = wait;
      }
      break;

    case wait:
      if (sleep > 0) sleep--;
      else state = sUp;
      break;

    case sIdle:
      FTM1_C0V = MIN_POS;
      break;

    default:
      break;
  }
}

static void MintReadPressure(void)
{
	uint8_t buf[10] = ";P\0"; //Pxxyy\0

	// Read Sensor 1
	ADC0_SC1A = 7;                            		// Start A adc conversion
	while (!(ADC0_SC1A & ADC_SC1_COCO_MASK));		// wait until adc conversion completed
	UTIL1_strcatNum8Hex(buf, sizeof(buf), ADC0_RA);

	// Read Sensor 2
	ADC0_SC1A = 6;                            		// Start A adc conversion
	while (!(ADC0_SC1A & ADC_SC1_COCO_MASK));		// wait until adc conversion completed
	UTIL1_strcatNum8Hex(buf, sizeof(buf), ADC0_RA);

	CLS1_SendStr(buf, CDC1_stdio.stdOut);
	//CLS1_SendStr(buf, SHELL_GetStdio()->stdOut);
}

static void MintReadJoystick(void)
{
	uint8_t buf[16] = ";J\0"; //JxxyyzzrrC\0

	// Read X
	ADC0_SC1A = 14;                            		// Start A adc conversion
	while (!(ADC0_SC1A & ADC_SC1_COCO_MASK));		  // wait until adc conversion completed
	UTIL1_strcatNum8Hex(buf, sizeof(buf), ADC0_RA);

	// Read Y
	ADC0_SC1A = 15;                            		// Start A adc conversion
	while (!(ADC0_SC1A & ADC_SC1_COCO_MASK));		  // wait until adc conversion completed
	UTIL1_strcatNum8Hex(buf, sizeof(buf), ADC0_RA);

	// Read Z
	ADC0_SC1A = 4;                            		// Start A adc conversion
	while (!(ADC0_SC1A & ADC_SC1_COCO_MASK));		  // wait until adc conversion completed
	UTIL1_strcatNum8Hex(buf, sizeof(buf), ADC0_RA);

	// Read REF
	ADC0_SC1A = 5;                            		// Start A adc conversion
	while (!(ADC0_SC1A & ADC_SC1_COCO_MASK));		  // wait until adc conversion completed
	UTIL1_strcatNum8Hex(buf, sizeof(buf), ADC0_RA);

	// PTA2 (Joystick center)
	UTIL1_strcatNum8u(buf, sizeof(buf), (GPIOA_PDIR & 1<<2));
	CLS1_SendStr(buf, CDC1_stdio.stdOut);
	//CLS1_SendStr(buf, SHELL_GetStdio()->stdOut);
}

static void MintReadKeyAndContainer(void)
{
	uint8_t buf[16] = ";K\0";
	uint8 data; //, result;

	// Read PCA8574
	  GI2C1_ReadAddress(0x38,NULL,0,&data,sizeof(data));
	//result = GI2C1_ReadByte(0x38, &data);

	// Insert Key state
	UTIL1_strcatNum8u(buf, sizeof(buf), ((data & (1<<5)) == 0));

	// Insert Container state
	UTIL1_strcat(buf, sizeof(buf), (uint8_t*)";C");
	UTIL1_strcatNum8Hex(buf, sizeof(buf), data & 0x1F); // 5 Bits

	CLS1_SendStr(buf, CDC1_stdio.stdOut);
}

static void MintReadZumo(void)
{
	uint8_t buf[16] = ";Z\0"; //ZBBC\0   B=Battery (Bat-Level 0..255) , C=Container (0=Empty, 1=Full)

	uint8 battery = 0xA6;		// ToDo Get Bat level

	UTIL1_strcatNum8Hex(buf, sizeof(buf), battery);
	UTIL1_strcatNum8u(buf, sizeof(buf), ballIsPresent);
	UTIL1_strcatNum8u(buf, sizeof(buf), parkingStartPos);
	UTIL1_strcatNum8u(buf, sizeof(buf), parkingFinishPos);

	parkingStartPos = 0;
	parkingFinishPos = 0;
	ballIsPresent = 0;

	//CLS1_SendStr(buf, SHELL_GetStdio()->stdOut);
	CLS1_SendStr(buf, CDC1_stdio.stdOut);
}

static void MintParseKeyCommand(const unsigned char *cmd)
{
  const unsigned char *p = cmd;

  PORTA_PCR0 = PORT_PCR_MUX(1);       // PTA0 MUX GPIO  Key Led R
  PORTA_PCR3 = PORT_PCR_MUX(1);       // PTA3 MUX GPIO  Key Led G
  PORTA_PCR4 = PORT_PCR_MUX(1);       // PTA4 MUX GPIO  Key LEd B

  uint8 red;
  //p = utilScanHex8u(p, &red);
  (void)UTIL1_ScanHex8uNumberNoPrefix(&p, &red);

  uint8 green;
  //p = utilScanHex8u(p, &green);
  (void)UTIL1_ScanHex8uNumberNoPrefix(&p, &green);

  uint8 blue;
  //p = utilScanHex8u(p, &blue);
  (void)UTIL1_ScanHex8uNumberNoPrefix(&p, &blue);

  if (red > 0) GPIOA_PCOR = (1<<0); // Red
  else GPIOA_PSOR = (1<<0);

  if (green > 0) GPIOA_PCOR = (1<<3); // Green
  else GPIOA_PSOR = (1<<3);

  if (blue > 0) GPIOA_PCOR = (1<<4); // Blue
  else GPIOA_PSOR = (1<<4);
}

static void MintParseZumoCommand(const unsigned char *cmd)
{
  const unsigned char *p = cmd + 1;

  uint8 bufXY[2];
  uint8 ledMode;

  switch (cmd[0])
  {
    case 'H': // Go to the start
      break;

    case 'F': // Go to the finish
      break;

    case 'D': // Drive
      //p = utilScanHex8u(p, &bufXY[0]);
      (void)UTIL1_ScanHex8uNumberNoPrefix(&p, &bufXY[0]);
      //p = utilScanHex8u(p, &bufXY[1]);
      (void)UTIL1_ScanHex8uNumberNoPrefix(&p, &bufXY[1]);
      RAPP_SendPayloadDataBlock(bufXY, sizeof(bufXY), RAPP_MSG_TYPE_JOYSTICK_XY, RNETA_GetDestAddr(),RPHY_PACKET_FLAGS_NONE);
      // ToDo Do drive...
      break;

    case 'L': // Set Led
      //p = utilScanHex8u(p, &ledMode);
      (void)UTIL1_ScanHex8uNumberNoPrefix(&p, &ledMode);
      break;
  }
}

static void MintParseContainer(const unsigned char *cmd)
{
  const unsigned char *p = cmd + 1;
  uint8 mode;

  switch (cmd[0])
  {
    case '1':
      //p = utilScanHex8u(p, &mode);
      (void)UTIL1_ScanHex8uNumberNoPrefix(&p, &mode);
      // ToDo set led mode container 1
      break;

    case '2':
      //p = utilScanHex8u(p, &mode);
      (void)UTIL1_ScanHex8uNumberNoPrefix(&p, &mode);
      // ToDo set led mode container 2
      break;
  }
}

static void MintParseDispenser(const unsigned char *cmd)
{
  switch(cmd[0])
  {
    case 'P': // Power control
      if (cmd[1] == '1') data2 = 0xFE;
      else data2 = 0xFF;
      GI2C1_WriteAddress(0x3C, &data2,sizeof(data2),NULL,0);
      break;

    case 'S': // Start
      if (state == sIdle) state = sUp;
      break;
  }
}

static void MintParseLighting(const unsigned char *cmd)
{
  const unsigned char *p = cmd + 1;
  uint8 channel;
  uint8 red;
  uint8 green;
  uint8 blue;
  uint8 white;
  uint8 time;

  //p = utilScanHex8u(p, &channel);
  //p = utilScanHex8u(p, &red);
  //p = utilScanHex8u(p, &green);
  //p = utilScanHex8u(p, &blue);
  //p = utilScanHex8u(p, &white);
  //p = utilScanHex8u(p, &time);
  (void)UTIL1_ScanHex8uNumberNoPrefix(&p, &channel);
  (void)UTIL1_ScanHex8uNumberNoPrefix(&p, &red);
  (void)UTIL1_ScanHex8uNumberNoPrefix(&p, &green);
  (void)UTIL1_ScanHex8uNumberNoPrefix(&p, &blue);
  (void)UTIL1_ScanHex8uNumberNoPrefix(&p, &white);
  (void)UTIL1_ScanHex8uNumberNoPrefix(&p, &time);

  // ToDo Set Led PCA9685PW, ADR-Bits = 0x03
}


static uint8_t MINTREMOTE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  (void)io;
	switch (cmd[0])
	{
		case 'K': // control key led
		  MintParseKeyCommand(cmd + 1);
		  *handled = TRUE;
		  break;

		case 'Z': // control zumo
		  MintParseZumoCommand(cmd + 1);
		  *handled = TRUE;
		  break;

		case 'C': // Container start and finish
		  MintParseContainer(cmd + 1);
		  *handled = TRUE;
		  break;

		case 'D': // Dispenser
		  MintParseDispenser(cmd + 1);
		  *handled = TRUE;
		  break;

		case 'L': // Ligthing
		  MintParseLighting(cmd + 1);
		  *handled = TRUE;
		  break;
	}
	return ERR_OK;
}

/*!
 * \brief Returns the reed contact pin status
 * \return 0: no contact, 1: start contact, 2: finish contact
 */
static uint8_t GetReedContactStatus(void) {
  uint8_t data;
  uint8_t addr = 0x3C;
  GI2C1_ReadAddress(addr,NULL,0,&data,sizeof(data));

  if ((data&0x80)==0) { /* \todo check reed contact pin */
    return 1;
  } else if ((data&0x40)==0) { /* \todo check reed contact pin */
    return 2;
  }
  return 0;
}
/*!
 * \brief Send a notification message about Reed contact
 */
static void CheckAndNotifyAboutReedContact(void) {
  static uint8_t prevContact = 0; /* 0: no contact, 1: start, 2: finish */
  uint8_t currContact;

  currContact = GetReedContactStatus();
  if (prevContact != currContact) { /* contact changed? */
    vTaskDelay(pdMS_TO_TICKS(50)); /* simple debounce */
    if (GetReedContactStatus() == currContact) { /* still the same status */
      prevContact = currContact; /* store value for next iteration */
      /* send notification */
      RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_NOTIFY_VALUE, RAPP_MSG_TYPE_DATA_ID_REED_CONTACT, currContact, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
    }
  }
}

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
    MINTREMOTE_ParseCommand,
    NULL
};

static unsigned char usb_cdc_buf[64];

static void MintRemoteTask(void *param) {
  (void)param;

  // init code
  PORTA_PCR2 = PORT_PCR_MUX(1); 			// PTA2 MUX GPIO Joystic Center

  //PORTA_PCR0 = PORT_PCR_MUX(1);       // PTA0 MUX GPIO  Key Led R
  //PORTA_PCR3 = PORT_PCR_MUX(1);       // PTA3 MUX GPIO  Key Led G
  PORTA_PCR4 = PORT_PCR_MUX(1);       // PTA4 MUX GPIO  Key LEd B


  // init dispenser servo & disable power
  FTM1_C0V = MIN_POS;
  state = sIdle;
  data2 = 0xFF;
  GI2C1_WriteAddress(0x3C,&data2,sizeof(data2),NULL,0);

  usb_cdc_buf[0] = '\0';
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(50));

    MintReadPressure();
    MintReadJoystick();
    MintReadZumo();
    MintReadKeyAndContainer();
    CheckAndNotifyAboutReedContact();

    CLS1_SendStr((uint8_t*)"\n", CDC1_stdio.stdOut);
    (void)CLS1_ReadAndParseWithCommandTable(usb_cdc_buf, sizeof(usb_cdc_buf), &CDC1_stdio, CmdParserTable);
  }
}

void MINTREMOTE_Init(void) {
  if (xTaskCreate(MintRemoteTask, "MintRemote", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
#endif /* PL_HAS_MINT_REMOTE */

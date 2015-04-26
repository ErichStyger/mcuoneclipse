/*
 * Application.c
 *
 *  Created on: 16.04.2015
 *      Author: Erich Styger
 */

#include "Application.h"
#include "crc16.h"

#define CRC_RANGE_START_ADDR    0x00410 /* start addr */
#define CRC_RANGE_END_ADDR      0x1FFFE /* end addr, this one will not be counted */
#define CRC_VALUE_ADDR          0x1FFFE /* address of CRC (16bits) */

void APP_CheckCRC(void) {
  unsigned short crc;

  crc = crc16_ccitt((void*)CRC_RANGE_START_ADDR, CRC_RANGE_END_ADDR-CRC_RANGE_START_ADDR, CRC16_START_VAL);
  if (crc!=*((unsigned short*)CRC_VALUE_ADDR)) {
    for(;;) {} /* error! CRC does not match! */
  }
}


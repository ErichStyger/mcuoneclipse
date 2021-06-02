/*
 * Copyright (c) 2020, Erich Styger
  *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_BLE_MSG
#include "bleMsg.h"
#include "McuRTOS.h"
#include "Shell.h"
#include "McuUtility.h"
#include "McuLog.h"
#include <string.h>

static QueueHandle_t BleMsgQueue; /* queue for the shell */

static BaseType_t BLEMSG_PutItem(BLE_Msg_t *msg, TickType_t ticksToWait) {
  return xQueueSend(BleMsgQueue, msg, ticksToWait);
}

static BaseType_t BLEMSG_GetItem(BLE_Msg_t *msg, TickType_t ticksToWait) {
  return xQueueReceive(BleMsgQueue, msg, ticksToWait);
}

bool BLEMSG_HandleMessage(void) {
  uint8_t cmd[64];
  BLE_Msg_t msg;

  cmd[0] = '\0';
  if (BLEMSG_GetItem(&msg, 0)==pdPASS) {
    if (msg.type==BLE_MSG_TYPE_BUTTON_PRESSED) {
      switch(msg.u.button) {
      case 1: /* button '1' */
      #if PL_CONFIG_USE_CLOCK
        McuUtility_strcpy(cmd, sizeof(cmd), (uint8_t*)"matrix he all on");
      #elif PL_CONFIG_USE_LED_PIXEL
      #endif
        break;
      case 2: /* button '2' */
      #if PL_CONFIG_USE_CLOCK
        McuUtility_strcpy(cmd, sizeof(cmd), (uint8_t*)"matrix he all off");
      #elif PL_CONFIG_USE_LED_PIXEL
      #endif
        break;
      case 3: /* button '3' */
      #if PL_CONFIG_USE_CLOCK
        McuUtility_strcpy(cmd, sizeof(cmd), (uint8_t*)"matrix he all on");
      #elif PL_CONFIG_USE_LED_PIXEL
      #endif
        break;
      case 4: /* button '4' */
      #if PL_CONFIG_USE_CLOCK
        McuUtility_strcpy(cmd, sizeof(cmd), (uint8_t*)"matrix he all off");
      #elif PL_CONFIG_USE_LED_PIXEL
      #endif
        break;
      case 5: /* button 'up' */
      #if PL_CONFIG_USE_CLOCK
        McuUtility_strcpy(cmd, sizeof(cmd), (uint8_t*)"matrix hour 12");
      #elif PL_CONFIG_USE_LED_PIXEL
      #endif
        break;
      case 6: /* button 'down' */
      #if PL_CONFIG_USE_CLOCK
        McuUtility_strcpy(cmd, sizeof(cmd), (uint8_t*)"matrix hour 6");
      #elif PL_CONFIG_USE_LED_PIXEL
      #endif
        break;
      case 7: /* button 'left' */
      #if PL_CONFIG_USE_CLOCK
        McuUtility_strcpy(cmd, sizeof(cmd), (uint8_t*)"matrix hour 9");
      #elif PL_CONFIG_USE_LED_PIXEL
      #endif
        break;
      case 8: /* button 'right' */
      #if PL_CONFIG_USE_CLOCK
        McuUtility_strcpy(cmd, sizeof(cmd), (uint8_t*)"matrix hour 3");
      #elif PL_CONFIG_USE_LED_PIXEL
      #endif
        break;
     default:
        cmd[0] = '\0';
        break;
      } /* switch */
    } else if (msg.type==BLE_MSG_TYPE_COLOR_PICKER) {
    #if PL_CONFIG_USE_CLOCK
      McuUtility_strcpy(cmd, sizeof(cmd), (uint8_t*)"matrix hand rgb all 0x");
      McuUtility_strcatNum24Hex(cmd, sizeof(cmd), msg.u.color);
    #elif PL_CONFIG_USE_LED_PIXEL
      McuUtility_strcpy(cmd, sizeof(cmd), (uint8_t*)"matrix sendcmd neo set all 0x");
      McuUtility_strcatNum24Hex(cmd, sizeof(cmd), msg.u.color);
    #endif
    } else if (msg.type==BLE_MSG_TYPE_ACCELEROMETER) {
      // does not work yet?
    //  McuUtility_strcpy(cmd, sizeof(cmd), (uint8_t*)"matrix hand rgb all 0x");
    //  McuUtility_strcatNum24Hex(cmd, sizeof(cmd), msg.value);
    }
    (void)SHELL_ParseCommand(cmd, NULL, true);
  } else {
    return false; /* no messages waiting */
  }
  return uxQueueMessagesWaiting(BleMsgQueue)!=0; /* true if messages are waiting, false if no more messages */
}

static bool checkCRC(const uint8_t *buffer, size_t crcPos) {
  uint8_t crc = buffer[crcPos];
  uint8_t sum = 0;

  for (int i=0; i<crcPos; i++) {
    sum += buffer[i];
  }
  sum = ~sum;
  if (crc==sum) {
    return true; /* pass */
  } else {
    return false; /* fail */
  }
}

bool BLEMSG_RxCallback(const uint8_t *buf) {
  /* note: the NeoPixel code is here: https://github.com/adafruit/Adafruit_BluefruitLE_nRF51/tree/master/examples/neopixel */
  size_t len;
  BLE_Msg_t msg;
  const uint8_t *p;
  bool noError = true;

  if (buf[0]!='!') {
    return false; /* not a valid message */
  }
  p = buf;
  for(;;) { /* breaks */
    while (p[0]=='\r' || p[0]=='\n') { /* skip line endings */
      p++;
    }
    if (p[0]=='\0') { /* reached the end */
      break;
    }
    if (p[0]!='!') {
      noError = false;
      break; /* not a valid message start */
    }
    len = strlen((char*)p);
    if (p[1]=='B' && len>=5) { /* Button */
      /*
      Button 4 pressed:  [‘!’] [‘B’] [‘4’] [‘1’] [CRC]
      Button 4 released: [‘!’] [‘B’] [‘4’] [‘0’] [CRC]
      Button Up pressed: [‘!’] [‘B’] [‘5’] [‘1’] [CRC]
      Button Down pressed: [‘!’] [‘B’] [‘6’] [‘1’] [CRC]
      Button Left pressed: [‘!’] [‘B’] [‘7’] [‘1’] [CRC]
      Button Right pressed: [‘!’] [‘B’] [‘8’] [‘1’] [CRC]
      */
      if (!checkCRC(p, 4)) {
        noError = false;
        break; /* wrong crc */
      }
      if (p[3]=='1') {
        msg.type = BLE_MSG_TYPE_BUTTON_PRESSED;
      } else { /* '0' */
        msg.type = BLE_MSG_TYPE_BUTTON_RELEASED;
      }
      msg.u.button = p[2]-'0';
      if (BLEMSG_PutItem(&msg, pdMS_TO_TICKS(100))!=pdTRUE) {
        noError = false;
        break;
      }
      p += sizeof("!B41c")-1;
    } else if (p[1]=='C' && len>=6) { /* Color */
      if (!checkCRC(p, 5)) {
        noError = false;
        break; /* wrong crc */
      }
      msg.type = BLE_MSG_TYPE_COLOR_PICKER;
      msg.u.color = (p[2]<<16)|(p[3]<<8)|p[4];
      if (BLEMSG_PutItem(&msg, pdMS_TO_TICKS(100))!=pdTRUE) {
        noError = false;
        break;
      }
      p += sizeof("!CRGBc")-1;
    } else if (p[1]=='A' && len>=9) { /* Accelerometer */
      if (!checkCRC(p, 8)) {
        noError = false;
        break; /* wrong crc */
      }
      msg.type = BLE_MSG_TYPE_ACCELEROMETER;
      msg.u.accel[0] = *((float*)(&p[2]));
      msg.u.accel[1] = *((float*)&p[4]);
      msg.u.accel[2] = *((float*)&p[6]);
      if (BLEMSG_PutItem(&msg, pdMS_TO_TICKS(100))!=pdTRUE) {
        noError = false;
        break;
      }
      p += sizeof("!Axxyyzzc")-1;
    } else if (p[1]=='M' && len>=9) { /* Magnetometer */
      if (!checkCRC(p, 8)) {
        noError = false;
        break; /* wrong crc */
      }
      msg.type = BLE_MSG_TYPE_MAGNETOMETER;
      msg.u.magnetometer[0] = *((float*)&p[2]);
      msg.u.magnetometer[1] = *((float*)&p[4]);
      msg.u.magnetometer[2] = *((float*)&p[6]);
      if (BLEMSG_PutItem(&msg, pdMS_TO_TICKS(100))!=pdTRUE) {
        noError = false;
        break;
      }
      p += sizeof("!Mxxyyzzc")-1;
     } else if (p[1]=='Q' && len>=11) { /* Quaternion */
      if (!checkCRC(p, 10)) {
        noError = false;
        break; /* wrong crc */
      }
      msg.type = BLE_MSG_TYPE_QUATERNION;
      msg.u.quaternion[0] = 0;
      msg.u.quaternion[1] = 0;
      msg.u.quaternion[2] = 0;
      msg.u.quaternion[3] = 0;
      if (BLEMSG_PutItem(&msg, pdMS_TO_TICKS(100))!=pdTRUE) {
        noError = false;
        break;
      }
      p += sizeof("!Qxxyyzzwwc")-1;
    } else if (p[1]=='G' && len>=8) { /* Gyro */
      if (!checkCRC(p, 8)) {
        noError = false;
        break; /* wrong crc */
      }
      msg.type = BLE_MSG_TYPE_GYRO;
      msg.u.gyro[0] = 0;
      msg.u.gyro[1] = 0;
      msg.u.gyro[2] = 0;
      if (BLEMSG_PutItem(&msg, pdMS_TO_TICKS(100))!=pdTRUE) {
        noError = false;
        break;
      }
      p += sizeof("!Gxxyyzzc")-1;
    } else if (p[1]=='L' && len>=8) { /* Location */
      if (!checkCRC(p, 8)) {
        noError = false;
        break; /* wrong crc */
      }
      msg.type = BLE_MSG_TYPE_LOCATION;
      msg.u.location[0] = 0;
      msg.u.location[1] = 0;
      msg.u.location[2] = 0;
      if (BLEMSG_PutItem(&msg, pdMS_TO_TICKS(100))!=pdTRUE) {
        noError = false;
        break;
      }
      p += sizeof("!Lllooaac")-1;
    }
  } /* for */
  return noError; /* true: no errors */
}

void BLEMSG_Init(void) {
  BleMsgQueue = xQueueCreate(10, sizeof(BLE_Msg_t));
  if (BleMsgQueue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(BleMsgQueue, "BleMsg");
}

#endif /* PL_CONFIG_USE_BLE_MSG */

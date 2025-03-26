/**
 * \file
 * \brief This is a configuration file for the RNet stack
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * Here the stack can be configured using macros.
 */

#ifndef __RNET_APP_CONFIG__
#define __RNET_APP_CONFIG__

#include "platform.h"

/*! type ID's for application messages */
typedef enum {
  RAPP_MSG_TYPE_STDIN = 0x00,                   /* remote shell standard in channel */
  RAPP_MSG_TYPE_STDOUT = 0x01,                  /* remote shell standard out channel */
  RAPP_MSG_TYPE_STDERR = 0x02,                  /* remote shell standard error channel */
  RAPP_MSG_TYPE_ACCEL = 0x03,                   /* accelerometer data */
  RAPP_MSG_TYPE_DATA = 0x04,                    /* generic data message */
  RAPP_MSG_TYPE_JOYSTICK_XY = 0x05,             /* Joystick xy message: data is x,y (two signed bytes) from -128...127 */
  RAPP_MSG_TYPE_JOYSTICK_BTN = 0x54,            /* Joystick button message (data is one byte: 'A', 'B', ... 'F' and 'K') */
  /* message types for key-value pairs. IDs are of RAPP_MSG_DataIDType (16bit) and data is always 32bit */
  RAPP_MSG_TYPE_REQUEST_SET_VALUE = 0x55,       /* Request to set a value for 16bit RAPP_MSG_DataIDType ID, followed by 32bit value */
  RAPP_MSG_TYPE_NOTIFY_VALUE = 0x56,            /* notify value for 16bit RAPP_MSG_DataIDType, followed by 32bit value */
  RAPP_MSG_TYPE_QUERY_VALUE = 0x57,             /* query value for 16bit RAPP_MSG_DataIDType */
  RAPP_MSG_TYPE_QUERY_VALUE_RESPONSE = 0x58,    /* response for RAPP_MSG_TYPE_QUERY_VALUE request: 16bit RAPP_MSG_DataIDType followed by 32bit data value */
} RAPP_MSG_Type;

/* IDs for RAPP_MSG_TYPE_REQUEST_SET_VALUE, RAPP_MSG_TYPE_NOTIFY_VALUE, RAPP_MSG_TYPE_QUERY_VALUE and RAPP_MSG_TYPE_QUERY_VALUE_RESPONSE */
typedef enum {
  RAPP_MSG_TYPE_DATA_ID_NONE = 0,           /* dummy ID */
  RAPP_MSG_TYPE_DATA_ID_MINT_BALL = 1,      /* ball presence status: 0: not present, 1: present */
  RAPP_MSG_TYPE_DATA_ID_MINT_MODE = 2,      /* mint mode: 0: manual, 1: automatic */
  RAPP_MSG_TYPE_DATA_ID_MINT_GOTO = 3,      /* goto command: 0 (line), 1 (start), 2 (finish) */
  RAPP_MSG_TYPE_DATA_ID_TOF_VALUES = 4,     /* ToF values: four 8bit values */
  RAPP_MSG_TYPE_DATA_ID_POSITION = 5,       /* Position information: 0: no position, 1: start position, 2: finish position */
  RAPP_MSG_TYPE_DATA_ID_REED_CONTACT = 6,   /* Reed contact position: 0: no position, 1: start position, 2: finish position */
  RAPP_MSG_TYPE_DATA_ID_BATTERY_V = 7,      /* Battery voltage, in mV */
  RAPP_MSG_TYPE_DATA_ID_PID_FW_SPEED = 8,   /* PID forward speed */
  RAPP_MSG_TYPE_DATA_ID_NEO_BRIGHTNESS = 9, /* NeoPixel brightness */
  RAPP_MSG_TYPE_DATA_ID_NEO_RED = 10,       /* NeoPixel red color level */
  RAPP_MSG_TYPE_DATA_ID_NEO_GREEN = 11,     /* NeoPixel green color level */
  RAPP_MSG_TYPE_DATA_ID_NEO_BLUE = 12,      /* NeoPixel blue color level */
  RAPP_MSG_TYPE_DATA_ID_SUMO_START_STOP=13, /* Start/Stop sumo, 0: stop, 1: start */
  RAPP_MSG_TYPE_DATA_ID_SUMO_RADAR=14,      /* Radar, 0: off, 1: on */
  RAPP_MSG_TYPE_DATA_ID_SUMO_START_LEFT=15, /* first turn, 0: right, 1: left */
  RAPP_MSG_TYPE_DATA_ID_PRESENCE_DETECTION=16, /* Presence detection, 0: no presence, 1: presence */
} RAPP_MSG_DataIDType;

#ifndef RNet_App_CONFIG_DO_SANITY_CHECK
  #define RNet_App_CONFIG_DO_SANITY_CHECK     (0)
#endif

#if PL_HAS_RADIO

#if PL_HAS_SMAC
#include "SMAC1.h"
#define RNET_CONFIG_TRANSCEIVER_PAYLOAD_SIZE  SMAC1_RADIO_BUF_SIZE  /* max 128 bytes */
  /*!< Size of the physical transceiver payload (bytes), max 32 bytes for nRF24L01+, max 128 bytes for MC1320x */
#endif

#if PL_HAS_NRF24
#define RNET_CONFIG_TRANSCEIVER_PAYLOAD_SIZE  32
  /*!< Size of the physical transceiver payload (bytes), max 32 bytes for nRF24L01+, max 128 bytes for MC1320x */
#endif

#endif /* PL_HAS_RADIO */

#endif /* __RNET_APP_CONFIG__ */

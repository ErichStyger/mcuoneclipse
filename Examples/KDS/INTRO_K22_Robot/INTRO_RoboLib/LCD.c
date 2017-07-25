/**
 * \file
 * \brief Module to handle the LCD display
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module is driving the Nokia LCD Display.
 */

#include "Platform.h"
#if PL_CONFIG_HAS_LCD
#include "LCD.h"
#include "Application.h"
#include "LED1.h"
#include "UTIL1.h"
#include "LCD_LED.h"
#include "PDC1.h"
#include "GDisp1.h"
#include "GFONT1.h"
#include "FDisp1.h"
#include "Event.h"
#include "FRTOS1.h"
#include "RApp.h"
#include "LCDMenu.h"
#include "RNet_App.h"

/* status variables */
static bool LedBackLightisOn = TRUE;
static bool requestLCDUpdate = FALSE;

static xTaskHandle LCDTaskHandle;

#define LCD_MENU_EVENT_UP     (1<<0)
#define LCD_MENU_EVENT_DOWN   (1<<1)
#define LCD_MENU_EVENT_LEFT   (1<<2)
#define LCD_MENU_EVENT_RIGHT  (1<<3)
#define LCD_MENU_EVENT_ENTER  (1<<4)

void LCD_SetEvent(LCD_BTN_Events event) {
  switch(event) {
    case LCD_BTN_LEFT:
      (void)xTaskNotify(LCDTaskHandle, LCD_MENU_EVENT_LEFT, eSetBits);
      break;
    case LCD_BTN_RIGHT:
      (void)xTaskNotify(LCDTaskHandle, LCD_MENU_EVENT_RIGHT, eSetBits);
      break;
    case LCD_BTN_UP:
      (void)xTaskNotify(LCDTaskHandle, LCD_MENU_EVENT_UP, eSetBits);
      break;
    case LCD_BTN_DOWN:
      (void)xTaskNotify(LCDTaskHandle, LCD_MENU_EVENT_DOWN, eSetBits);
      break;
    case LCD_BTN_CENTER:
      (void)xTaskNotify(LCDTaskHandle, LCD_MENU_EVENT_ENTER, eSetBits);
      break;
    case LCD_SIDE_BTN_UP:
      (void)xTaskNotify(LCDTaskHandle, LCD_MENU_EVENT_UP, eSetBits);
      break;
    case LCD_SIDE_BTN_DOWN:
      (void)xTaskNotify(LCDTaskHandle, LCD_MENU_EVENT_DOWN, eSetBits);
      break;
    default:
      break;
  }
}

#define MINT_MODE_MANUAL   0
#define MINT_MODE_AUTOMTIC 1
#define ENABLE_LCD_DEMO    0
#define ENABLE_EDIT_DEMO   0

typedef enum {
  MENU_HANDLER_FLAGS_NONE = 0,
  MENU_HANDLER_FLAGS_PERCENT = (1<<0), /* treat as percent value */
  MENU_HANDLER_FLAGS_UNSIGNED = (1<<1), /* treat as unsigned value */
} MenuHandlerFlags;

typedef struct {
  bool dataValid;
  int32_t val;
  uint8_t str[sizeof("Some Text ??%")+1]; /* used to store menu string */
} MenuValueSetting;

static struct {
  struct {
    bool dataValid;
    bool ballPresent;
  } ball;
  struct {
    bool dataValid;
    uint8_t contactNo;
    uint8_t str[sizeof("reed: 0")+1]; /* used to store menu string */
  } reed;
  struct {
    bool dataValid;
    uint32_t mintMode;
  } mintMode;
  struct {
    bool dataValid;
    uint8_t mm[4]; /* ToF Sensor Values */
    uint8_t str[sizeof("D:??:??:??:??")+1]; /* used to store menu string */
  } tof;
  struct {
    bool dataValid;
    uint16_t centiV;
    uint8_t str[sizeof("Batt: ?.??V")+1]; /* used to store menu string */
  } battVoltage;
  MenuValueSetting pidfw;
  MenuValueSetting NeoBrigthness, NeoRed, NeoGreen, NeoBlue;
} remoteValues;

typedef enum {
  LCD_MENU_ID_NONE = LCDMENU_ID_NONE, /* special value! */
  LCD_MENU_ID_MAIN,
    LCD_MENU_ID_BACKLIGHT,
#if ENABLE_EDIT_DEMO
    LCD_MENU_ID_NUM_VALUE,
#endif
  LCD_MENU_ID_ROBOT,
    LCD_MENU_ID_MINT,
      LCD_MENU_ID_MINT_CURR_MODE,
      LCD_MENU_ID_MINT_SET_MODE_MANUAL,
      LCD_MENU_ID_MINT_SET_MODE_AUTOMATIC,
      LCD_MENU_ID_MINT_BALL_SENSOR,
      LCD_MENU_ID_MINT_REED_CONTACT,
      LCD_MENU_ID_MINT_TOF_SENSOR,
      LCD_MENU_ID_MINT_GOTO_LINE,
      LCD_MENU_ID_MINT_GOTO_START,
      LCD_MENU_ID_MINT_GOTO_FINISH,
    LCD_MENU_ID_ROBOT_REMOTE,
      LCD_MENU_ID_ROBOT_REMOTE_FORWARD,
      LCD_MENU_ID_ROBOT_REMOTE_BACKWARD,
      LCD_MENU_ID_ROBOT_REMOTE_LEFT,
      LCD_MENU_ID_ROBOT_REMOTE_RIGHT,
      LCD_MENU_ID_ROBOT_REMOTE_STOP,
      LCD_MENU_ID_ROBOT_REMOTE_ON,
      LCD_MENU_ID_ROBOT_REMOTE_OFF,
    LCD_MENU_ID_ROBOT_STATUS,
      LCD_MENU_ID_BATTERY_VOLTAGE,
      LCD_MENU_ID_PID_FW_SPEED,
    LCD_MENU_ID_ROBOT_SUMO,
      LCD_MENU_ID_ROBOT_SUMO_START,
      LCD_MENU_ID_ROBOT_SUMO_STOP,
      LCD_MENU_ID_ROBOT_SUMO_START_LEFT,
      LCD_MENU_ID_ROBOT_SUMO_START_RIGHT,
      LCD_MENU_ID_ROBOT_SUMO_RADAR_ON,
      LCD_MENU_ID_ROBOT_SUMO_RADAR_OFF,
  LCD_MENU_ID_NEOPIXEL,
    LCD_MENU_ID_NEOPIXEL_BRIGHTNESS,
    LCD_MENU_ID_NEOPIXEL_RED,
    LCD_MENU_ID_NEOPIXEL_GREEN,
    LCD_MENU_ID_NEOPIXEL_BLUE,
} LCD_MenuIDs;

#if ENABLE_EDIT_DEMO
static LCDMenu_StatusFlags ValueChangeHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  static int value = 0;
  static uint8_t valueBuf[16];
  LCDMenu_StatusFlags flags = LCDMENU_STATUS_FLAGS_NONE;

  (void)item;
  if (event==LCDMENU_EVENT_GET_TEXT) {
    UTIL1_strcpy(valueBuf, sizeof(valueBuf), (uint8_t*)"Val: ");
    UTIL1_strcatNum32s(valueBuf, sizeof(valueBuf), value);
    *dataP = valueBuf;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_GET_EDIT_TEXT) {
    UTIL1_strcpy(valueBuf, sizeof(valueBuf), (uint8_t*)"[-] ");
    UTIL1_strcatNum32s(valueBuf, sizeof(valueBuf), value);
    UTIL1_strcat(valueBuf, sizeof(valueBuf), (uint8_t*)" [+]");
    *dataP = valueBuf;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_DECREMENT) {
    value--;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_INCREMENT) {
    value++;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  }
  return flags;
}
#endif

static LCDMenu_StatusFlags BackLightMenuHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  LCDMenu_StatusFlags flags = LCDMENU_STATUS_FLAGS_NONE;

  (void)item;
  if (event==LCDMENU_EVENT_GET_TEXT && dataP!=NULL) {
    if (LedBackLightisOn) {
      *dataP = "Backlight is ON";
    } else {
      *dataP = "Backlight is OFF";
    }
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_ENTER) { /* toggle setting */
    LedBackLightisOn = !LedBackLightisOn;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  }
  return flags;
}

static LCDMenu_StatusFlags RobotRemoteDriveMenuHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  uint8_t button = '\0'; /* default */
  LCDMenu_StatusFlags flags = LCDMENU_STATUS_FLAGS_NONE;

  (void)dataP;
  if (event==LCDMENU_EVENT_ENTER) {
    switch(item->id) {
      case LCD_MENU_ID_ROBOT_REMOTE_FORWARD:
        button = 'a';
        break;
      case LCD_MENU_ID_ROBOT_REMOTE_BACKWARD:
        button = 'c';
        break;
      case LCD_MENU_ID_ROBOT_REMOTE_LEFT:
        button = 'd';
        break;
      case LCD_MENU_ID_ROBOT_REMOTE_RIGHT:
        button = 'b';
        break;
      case LCD_MENU_ID_ROBOT_REMOTE_STOP:
        button = 's';
        break;
      case LCD_MENU_ID_ROBOT_REMOTE_ON:
        button = 'e';
        break;
      case LCD_MENU_ID_ROBOT_REMOTE_OFF:
        button = 'E';
        break;
    }
    if (button!='\0') {
      (void)RAPP_SendPayloadDataBlock(&button, sizeof(button), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
      flags |= LCDMENU_STATUS_FLAGS_HANDLED;
    }
  }
  return flags;
}

static LCDMenu_StatusFlags RobotSumoMenuHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  uint8_t data[6]; /* 2 byte ID and 4 bytes data */
  LCDMenu_StatusFlags flags = LCDMENU_STATUS_FLAGS_NONE;
  RAPP_MSG_Type msgType = -1;
  uint16_t dataID = RAPP_MSG_TYPE_DATA_ID_NONE;
  uint32_t dataValue = 0;

  (void)dataP;
  if (event==LCDMENU_EVENT_ENTER) {
    switch(item->id) {
      case LCD_MENU_ID_ROBOT_SUMO_START:
        msgType = RAPP_MSG_TYPE_REQUEST_SET_VALUE;
        dataID = RAPP_MSG_TYPE_DATA_ID_SUMO_START_STOP;
        dataValue = 1; /* start */
        break;
      case LCD_MENU_ID_ROBOT_SUMO_STOP:
        msgType = RAPP_MSG_TYPE_REQUEST_SET_VALUE;
        dataID = RAPP_MSG_TYPE_DATA_ID_SUMO_START_STOP;
        dataValue = 0; /* stop */
        break;
      case LCD_MENU_ID_ROBOT_SUMO_START_LEFT:
        msgType = RAPP_MSG_TYPE_REQUEST_SET_VALUE;
        dataID = RAPP_MSG_TYPE_DATA_ID_SUMO_START_LEFT;
        dataValue = 1; /* start to left */
        break;
      case LCD_MENU_ID_ROBOT_SUMO_START_RIGHT:
        msgType = RAPP_MSG_TYPE_REQUEST_SET_VALUE;
        dataID = RAPP_MSG_TYPE_DATA_ID_SUMO_START_LEFT;
        dataValue = 0; /* start to right */
        break;
      case LCD_MENU_ID_ROBOT_SUMO_RADAR_ON:
        msgType = RAPP_MSG_TYPE_REQUEST_SET_VALUE;
        dataID = RAPP_MSG_TYPE_DATA_ID_SUMO_RADAR;
        dataValue = 1; /* radar on */
        break;
      case LCD_MENU_ID_ROBOT_SUMO_RADAR_OFF:
        msgType = RAPP_MSG_TYPE_REQUEST_SET_VALUE;
        dataID = RAPP_MSG_TYPE_DATA_ID_SUMO_RADAR;
        dataValue = 0; /* radar on */
        break;
    }
    if (dataID!=RAPP_MSG_TYPE_DATA_ID_NONE) {
      UTIL1_SetValue16LE(dataID, &data[0]);
      UTIL1_SetValue32LE(dataValue, &data[2]);
      (void)RAPP_SendPayloadDataBlock(&data[0], sizeof(data), msgType, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
      flags |= LCDMENU_STATUS_FLAGS_HANDLED;
    }
  }
  return flags;
}


static LCDMenu_StatusFlags RobotRemoteMintMenuHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  uint8_t data[6]; /* 2 byte ID and 4 bytes data */
  bool sendData = FALSE;
  LCDMenu_StatusFlags flags = LCDMENU_STATUS_FLAGS_NONE;

  (void)dataP;
  if (event==LCDMENU_EVENT_ENTER) {
    switch(item->id) {
      case LCD_MENU_ID_MINT_SET_MODE_MANUAL:
        UTIL1_SetValue16LE(RAPP_MSG_TYPE_DATA_ID_MINT_MODE, &data[0]);
        UTIL1_SetValue32LE(MINT_MODE_MANUAL, &data[2]);
        sendData = TRUE;
        break;
      case LCD_MENU_ID_MINT_SET_MODE_AUTOMATIC:
        UTIL1_SetValue16LE(RAPP_MSG_TYPE_DATA_ID_MINT_MODE, &data[0]);
        UTIL1_SetValue32LE(MINT_MODE_AUTOMTIC, &data[2]);
        sendData = TRUE;
        break;
      case LCD_MENU_ID_MINT_GOTO_LINE:
        UTIL1_SetValue16LE(RAPP_MSG_TYPE_DATA_ID_MINT_GOTO, &data[0]);
        UTIL1_SetValue32LE(0, &data[2]);
        sendData = TRUE;
        break;
      case LCD_MENU_ID_MINT_GOTO_START:
        UTIL1_SetValue16LE(RAPP_MSG_TYPE_DATA_ID_MINT_GOTO, &data[0]);
        UTIL1_SetValue32LE(1, &data[2]);
        sendData = TRUE;
        break;
      case LCD_MENU_ID_MINT_GOTO_FINISH:
        UTIL1_SetValue16LE(RAPP_MSG_TYPE_DATA_ID_MINT_GOTO, &data[0]);
        UTIL1_SetValue32LE(2, &data[2]);
        sendData = TRUE;
        break;
    }
    if (sendData) {
      (void)RAPP_SendPayloadDataBlock(&data[0], sizeof(data), RAPP_MSG_TYPE_REQUEST_SET_VALUE, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
      flags |= LCDMENU_STATUS_FLAGS_HANDLED;
    }
  }
  return flags;
}

static LCDMenu_StatusFlags MenuValueHandler(
    const struct LCDMenu_MenuItem_ *item,  LCDMenu_EventType event, void **dataP,
    MenuValueSetting *menuData,
    uint8_t *buf, size_t bufSize,
    const uint8_t *labelStr,
    RAPP_MSG_DateIDType msgID,
    int32_t minValue, int32_t maxValue,
    MenuHandlerFlags menuFlags
    )
{
  LCDMenu_StatusFlags flags = LCDMENU_STATUS_FLAGS_NONE;

  if (item==NULL) {
    return LCDMENU_STATUS_FLAGS_ERROR; /* error case */
  }
  switch(event) {
    case LCDMENU_EVENT_GET_TEXT:
      UTIL1_strcpy(buf, bufSize, labelStr);
      if (menuData->dataValid) { /* use valid data */
        UTIL1_strcatNum8u(buf, bufSize, menuData->val);
      } else { /* request value from robot */
        (void)RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_QUERY_VALUE, msgID, 0, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
        /* use ??? for now until we get the response */
        UTIL1_strcat(buf, bufSize, (uint8_t*)"??");
      }
      if (menuFlags&MENU_HANDLER_FLAGS_PERCENT) {
        UTIL1_chcat(buf, bufSize, '%');
      }
      *dataP = menuData->str;
      flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
      break;

    case LCDMENU_EVENT_GET_EDIT_TEXT:
      UTIL1_strcpy(buf, bufSize, (uint8_t*)"[-] ");
      UTIL1_strcatNum8u(buf, bufSize, menuData->val);
      if (menuFlags&MENU_HANDLER_FLAGS_PERCENT) {
        UTIL1_chcat(buf, bufSize, '%');
      }
      UTIL1_strcat(buf, bufSize, (uint8_t*)" [+]");
      *dataP = menuData->str;
      flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
      break;

    case LCDMENU_EVENT_DECREMENT:
      if (menuData->val>minValue) {
        menuData->val--; /* keep inside limits */
      }
      flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
      break;

    case LCDMENU_EVENT_INCREMENT:
      if (menuData->val<maxValue) {
        menuData->val++; /* keep inside limits */
      }
      flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
      break;

    case LCDMENU_EVENT_ENTER_EDIT:
      if (!menuData->dataValid) {
        (void)RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_QUERY_VALUE, msgID, 0, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
        flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
      }
      break;

    case LCDMENU_EVENT_EXIT_EDIT:
      /* update robot with new value */
      (void)RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_REQUEST_SET_VALUE, msgID, menuData->val, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
      flags |= LCDMENU_STATUS_FLAGS_HANDLED;
      break;

    default:
      break;
  } /* switch */
  return flags;
}

static LCDMenu_StatusFlags RobotPIDMenuHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  /* called for ID LCD_MENU_ID_PID_FW_SPEED */
  return MenuValueHandler(item, event, dataP, &remoteValues.pidfw, remoteValues.pidfw.str, sizeof(remoteValues.pidfw.str),
      (uint8_t*)"PID fw ", RAPP_MSG_TYPE_DATA_ID_PID_FW_SPEED, 0, 100, MENU_HANDLER_FLAGS_PERCENT);
}


static LCDMenu_StatusFlags NeoPixelMenuHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  /* called for ID LCD_MENU_ID_NEOPIXEL_BRIGHTNESS */
  LCDMenu_StatusFlags flags = LCDMENU_STATUS_FLAGS_NONE;

  switch(item->id) {
    case LCD_MENU_ID_NEOPIXEL_BRIGHTNESS:
      return MenuValueHandler(item, event, dataP, &remoteValues.NeoBrigthness, remoteValues.NeoBrigthness.str, sizeof(remoteValues.NeoBrigthness.str),
          (uint8_t*)"Brightness ", RAPP_MSG_TYPE_DATA_ID_NEO_BRIGHTNESS, 0, 100, MENU_HANDLER_FLAGS_PERCENT);
    case LCD_MENU_ID_NEOPIXEL_RED:
      return MenuValueHandler(item, event, dataP, &remoteValues.NeoRed, remoteValues.NeoRed.str, sizeof(remoteValues.NeoRed.str),
          (uint8_t*)"Red ", RAPP_MSG_TYPE_DATA_ID_NEO_RED, 0, 0xff, MENU_HANDLER_FLAGS_NONE);
    case LCD_MENU_ID_NEOPIXEL_GREEN:
      return MenuValueHandler(item, event, dataP, &remoteValues.NeoGreen, remoteValues.NeoGreen.str, sizeof(remoteValues.NeoGreen.str),
          (uint8_t*)"Green ", RAPP_MSG_TYPE_DATA_ID_NEO_GREEN, 0, 0xff, MENU_HANDLER_FLAGS_NONE);
    case LCD_MENU_ID_NEOPIXEL_BLUE:
      return MenuValueHandler(item, event, dataP, &remoteValues.NeoBlue, remoteValues.NeoBlue.str, sizeof(remoteValues.NeoBlue.str),
          (uint8_t*)"Blue ", RAPP_MSG_TYPE_DATA_ID_NEO_BLUE, 0, 0xff, MENU_HANDLER_FLAGS_NONE);
    default:
      break;
  }
  return flags;
}

static LCDMenu_StatusFlags RobotBattMenuHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  /* called for ID LCD_MENU_ID_BATTERY_VOLTAGE */
  LCDMenu_StatusFlags flags = LCDMENU_STATUS_FLAGS_NONE;

  if (item==NULL || item->id!=LCD_MENU_ID_BATTERY_VOLTAGE) {
    return LCDMENU_STATUS_FLAGS_ERROR; /* error case */
  }
  switch(event) {
    case LCDMENU_EVENT_GET_TEXT:
      UTIL1_strcpy(remoteValues.battVoltage.str, sizeof(remoteValues.battVoltage.str), (uint8_t*)"Batt: ");
      if (remoteValues.battVoltage.dataValid) { /* use valid data */
        UTIL1_strcatNum32sDotValue100(remoteValues.battVoltage.str, sizeof(remoteValues.battVoltage.str), remoteValues.battVoltage.centiV);
      } else { /* request value from robot */
        (void)RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_QUERY_VALUE, RAPP_MSG_TYPE_DATA_ID_BATTERY_V, 0, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
        /* use ??? for now until we get the response */
        UTIL1_strcat(remoteValues.battVoltage.str, sizeof(remoteValues.battVoltage.str), (uint8_t*)"?.??");
      }
      UTIL1_strcat(remoteValues.battVoltage.str, sizeof(remoteValues.battVoltage.str), (uint8_t*)"V");
      *dataP = remoteValues.battVoltage.str;
      flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
      break;

    case LCDMENU_EVENT_ENTER:
      /* request new value on pressing enter */
      (void)RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_QUERY_VALUE, RAPP_MSG_TYPE_DATA_ID_BATTERY_V, 0, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
      flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
      break;

    default:
      break;
  } /* switch */
  return flags;
}

static LCDMenu_StatusFlags RobotRemoteMenuHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  LCDMenu_StatusFlags flags = LCDMENU_STATUS_FLAGS_NONE;

  if (event==LCDMENU_EVENT_GET_TEXT && dataP!=NULL) {
    if (item->id==LCD_MENU_ID_MINT_BALL_SENSOR) {
      if (remoteValues.ball.dataValid) {
        *dataP = remoteValues.ball.ballPresent ? "Ball: yes":"Ball: no";
      } else {
        *dataP = "Ball: ???";
      }
      flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
    } else if (item->id==LCD_MENU_ID_MINT_REED_CONTACT) {
      UTIL1_strcpy(remoteValues.reed.str, sizeof(remoteValues.reed.str), (uint8_t*)"reed: ");
      if (remoteValues.reed.dataValid) {
        UTIL1_strcatNum8u(remoteValues.reed.str, sizeof(remoteValues.reed.str), remoteValues.reed.contactNo);
      } else {
        UTIL1_strcat(remoteValues.reed.str, sizeof(remoteValues.reed.str), (uint8_t*)"?");
      }
      *dataP = remoteValues.reed.str;
      flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
    } else if (item->id==LCD_MENU_ID_MINT_TOF_SENSOR) {
      unsigned int i;

      UTIL1_strcpy(remoteValues.tof.str, sizeof(remoteValues.tof.str), (uint8_t*)"D:");
      for(i=0;i<sizeof(remoteValues.tof.mm);i++) {
        if (remoteValues.tof.dataValid) {
          UTIL1_strcatNum8Hex(remoteValues.tof.str, sizeof(remoteValues.tof.str), remoteValues.tof.mm[i]);
        } else {
          UTIL1_strcat(remoteValues.tof.str, sizeof(remoteValues.tof.str), (uint8_t*)"??");
        }
        if (i<sizeof(remoteValues.tof.mm)-1) {
          UTIL1_chcat(remoteValues.tof.str, sizeof(remoteValues.tof.str), ':');
        }
        *dataP = remoteValues.tof.str;
      }
      flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
    } else if (item->id==LCD_MENU_ID_MINT_CURR_MODE) {
      if (!remoteValues.mintMode.dataValid) {
        *dataP = "mode: ???";
      } else if (remoteValues.mintMode.mintMode==0) {
        *dataP = "mode: MANUAL";
      } else if (remoteValues.mintMode.mintMode==1) {
        *dataP = "mode: AUTO";
      } else {
        *dataP = "mode: ERROR";
      }
      flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
    }
  } else if (event==LCDMENU_EVENT_ENTER) { /* force update */
    uint16_t dataID = RAPP_MSG_TYPE_DATA_ID_NONE; /* default value, will be overwritten below */

    switch(item->id) {
      case LCD_MENU_ID_MINT_BALL_SENSOR:
        remoteValues.ball.dataValid = FALSE;
        dataID = RAPP_MSG_TYPE_DATA_ID_MINT_BALL;
        break;
      case LCD_MENU_ID_MINT_REED_CONTACT:
        remoteValues.reed.dataValid = FALSE;
        dataID = RAPP_MSG_TYPE_DATA_ID_REED_CONTACT;
        break;
      case LCD_MENU_ID_MINT_CURR_MODE:
        remoteValues.mintMode.dataValid = FALSE;
        dataID = RAPP_MSG_TYPE_DATA_ID_MINT_MODE;
        break;
      case LCD_MENU_ID_MINT_TOF_SENSOR:
        remoteValues.tof.dataValid = FALSE;
        dataID = RAPP_MSG_TYPE_DATA_ID_TOF_VALUES;
        break;
    }
    if (dataID!=RAPP_MSG_TYPE_DATA_ID_NONE) { /* request data */
      (void)RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_QUERY_VALUE, dataID, 0, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
      flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
    }
  }
  return flags;
}

static const LCDMenu_MenuItem menus[] =
{/* id,                                     grp, pos,   up,                       down,                             text,           handler                       flags                  */
    {LCD_MENU_ID_MAIN,                        0,   0,   LCD_MENU_ID_NONE,         LCD_MENU_ID_BACKLIGHT,            "General",      NULL,                         LCDMENU_MENU_FLAGS_NONE},
      {LCD_MENU_ID_BACKLIGHT,                 1,   0,   LCD_MENU_ID_MAIN,         LCD_MENU_ID_NONE,                 NULL,           BackLightMenuHandler,         LCDMENU_MENU_FLAGS_NONE},
#if ENABLE_EDIT_DEMO
      {LCD_MENU_ID_NUM_VALUE,                 1,   1,   LCD_MENU_ID_MAIN,         LCD_MENU_ID_NONE,                 NULL,           ValueChangeHandler,           LCDMENU_MENU_FLAGS_EDITABLE},
#endif
    {LCD_MENU_ID_ROBOT,                       0,   1,   LCD_MENU_ID_NONE,         LCD_MENU_ID_MINT,                 "Robot",        NULL,                         LCDMENU_MENU_FLAGS_NONE},
      {LCD_MENU_ID_MINT,                      2,   0,   LCD_MENU_ID_ROBOT,        LCD_MENU_ID_MINT_CURR_MODE,       "MINT",         NULL,                         LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_MINT_CURR_MODE,          3,   0,   LCD_MENU_ID_MINT,         LCD_MENU_ID_NONE,                 NULL,           RobotRemoteMenuHandler,       LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_MINT_SET_MODE_MANUAL,    3,   1,   LCD_MENU_ID_MINT,         LCD_MENU_ID_NONE,                 "set manual",   RobotRemoteMintMenuHandler,   LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_MINT_SET_MODE_AUTOMATIC, 3,   2,   LCD_MENU_ID_MINT,         LCD_MENU_ID_NONE,                 "set auto",     RobotRemoteMintMenuHandler,   LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_MINT_BALL_SENSOR,        3,   3,   LCD_MENU_ID_MINT,         LCD_MENU_ID_NONE,                 NULL,           RobotRemoteMenuHandler,       LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_MINT_REED_CONTACT,       3,   4,   LCD_MENU_ID_MINT,         LCD_MENU_ID_NONE,                 NULL,           RobotRemoteMenuHandler,       LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_MINT_TOF_SENSOR,         3,   5,   LCD_MENU_ID_MINT,         LCD_MENU_ID_NONE,                 NULL,           RobotRemoteMenuHandler,       LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_MINT_GOTO_LINE,          3,   6,   LCD_MENU_ID_MINT,         LCD_MENU_ID_NONE,                 "Goto Line!",   RobotRemoteMintMenuHandler,   LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_MINT_GOTO_START,         3,   7,   LCD_MENU_ID_MINT,         LCD_MENU_ID_NONE,                 "Goto Start!",  RobotRemoteMintMenuHandler,   LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_MINT_GOTO_FINISH,        3,   8,   LCD_MENU_ID_MINT,         LCD_MENU_ID_NONE,                 "Goto Finish!", RobotRemoteMintMenuHandler,   LCDMENU_MENU_FLAGS_NONE},
      {LCD_MENU_ID_ROBOT_REMOTE,              2,   1,   LCD_MENU_ID_ROBOT,        LCD_MENU_ID_ROBOT_REMOTE_FORWARD, "Remote",       NULL,                         LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_ROBOT_REMOTE_FORWARD,    4,   0,   LCD_MENU_ID_ROBOT_REMOTE, LCD_MENU_ID_NONE,                 "Forward",      RobotRemoteDriveMenuHandler,  LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_ROBOT_REMOTE_BACKWARD,   4,   1,   LCD_MENU_ID_ROBOT_REMOTE, LCD_MENU_ID_NONE,                 "Backward",     RobotRemoteDriveMenuHandler,  LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_ROBOT_REMOTE_LEFT,       4,   2,   LCD_MENU_ID_ROBOT_REMOTE, LCD_MENU_ID_NONE,                 "Left",         RobotRemoteDriveMenuHandler,  LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_ROBOT_REMOTE_RIGHT,      4,   3,   LCD_MENU_ID_ROBOT_REMOTE, LCD_MENU_ID_NONE,                 "Right",        RobotRemoteDriveMenuHandler,  LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_ROBOT_REMOTE_STOP,       4,   4,   LCD_MENU_ID_ROBOT_REMOTE, LCD_MENU_ID_NONE,                 "Stop",         RobotRemoteDriveMenuHandler,  LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_ROBOT_REMOTE_ON,         4,   5,   LCD_MENU_ID_ROBOT_REMOTE, LCD_MENU_ID_NONE,                 "Remote On",    RobotRemoteDriveMenuHandler,  LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_ROBOT_REMOTE_OFF,        4,   6,   LCD_MENU_ID_ROBOT_REMOTE, LCD_MENU_ID_NONE,                 "Remote Off",   RobotRemoteDriveMenuHandler,  LCDMENU_MENU_FLAGS_NONE},
      {LCD_MENU_ID_ROBOT_STATUS,              2,   2,   LCD_MENU_ID_ROBOT,        LCD_MENU_ID_BATTERY_VOLTAGE,      "Status",       NULL,                         LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_BATTERY_VOLTAGE,         5,   0,   LCD_MENU_ID_ROBOT_STATUS, LCD_MENU_ID_NONE,                 NULL,           RobotBattMenuHandler,         LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_PID_FW_SPEED,            5,   1,   LCD_MENU_ID_ROBOT_STATUS, LCD_MENU_ID_NONE,                 NULL,           RobotPIDMenuHandler,          LCDMENU_MENU_FLAGS_EDITABLE},
      {LCD_MENU_ID_ROBOT_SUMO,                2,   3,   LCD_MENU_ID_ROBOT,        LCD_MENU_ID_ROBOT_SUMO_START,     "Sumo",         NULL,                         LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_ROBOT_SUMO_START,        6,   0,   LCD_MENU_ID_ROBOT_SUMO,   LCD_MENU_ID_NONE,                 "Sumo Start",   RobotSumoMenuHandler,         LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_ROBOT_SUMO_STOP,         6,   1,   LCD_MENU_ID_ROBOT_SUMO,   LCD_MENU_ID_NONE,                 "Sumo Stop",    RobotSumoMenuHandler,         LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_ROBOT_SUMO_START_LEFT,   6,   2,   LCD_MENU_ID_ROBOT_SUMO,   LCD_MENU_ID_NONE,                 "Start Left",   RobotSumoMenuHandler,         LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_ROBOT_SUMO_START_RIGHT,  6,   3,   LCD_MENU_ID_ROBOT_SUMO,   LCD_MENU_ID_NONE,                 "Start Right",  RobotSumoMenuHandler,         LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_ROBOT_SUMO_RADAR_ON,     6,   4,   LCD_MENU_ID_ROBOT_SUMO,   LCD_MENU_ID_NONE,                 "Radar On",     RobotSumoMenuHandler,         LCDMENU_MENU_FLAGS_NONE},
        {LCD_MENU_ID_ROBOT_SUMO_RADAR_OFF,    6,   5,   LCD_MENU_ID_ROBOT_SUMO,   LCD_MENU_ID_NONE,                 "Radar Off",    RobotSumoMenuHandler,         LCDMENU_MENU_FLAGS_NONE},
    {LCD_MENU_ID_NEOPIXEL,                    0,   2,   LCD_MENU_ID_NONE,         LCD_MENU_ID_NEOPIXEL_BRIGHTNESS,  "NeoPixel",     NULL,                         LCDMENU_MENU_FLAGS_NONE},
      {LCD_MENU_ID_NEOPIXEL_BRIGHTNESS,       7,   0,   LCD_MENU_ID_NEOPIXEL,     LCD_MENU_ID_NONE,                 NULL,           NeoPixelMenuHandler,          LCDMENU_MENU_FLAGS_EDITABLE},
      {LCD_MENU_ID_NEOPIXEL_RED,              7,   1,   LCD_MENU_ID_NEOPIXEL,     LCD_MENU_ID_NONE,                 NULL,           NeoPixelMenuHandler,          LCDMENU_MENU_FLAGS_EDITABLE},
      {LCD_MENU_ID_NEOPIXEL_GREEN,            7,   2,   LCD_MENU_ID_NEOPIXEL,     LCD_MENU_ID_NONE,                 NULL,           NeoPixelMenuHandler,          LCDMENU_MENU_FLAGS_EDITABLE},
      {LCD_MENU_ID_NEOPIXEL_BLUE,             7,   3,   LCD_MENU_ID_NEOPIXEL,     LCD_MENU_ID_NONE,                 NULL,           NeoPixelMenuHandler,          LCDMENU_MENU_FLAGS_EDITABLE},
};

uint8_t LCD_HandleRemoteRxMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet) {
  uint16_t msgID;
  uint32_t msgValue;

  (void)size;
  (void)packet;
  (void)srcAddr;
  switch(type) {
    case RAPP_MSG_TYPE_QUERY_VALUE_RESPONSE: /* receive data value */
      *handled = TRUE;
      msgID = UTIL1_GetValue16LE(&data[0]); /* ID in little endian format */
      if (msgID==RAPP_MSG_TYPE_DATA_ID_MINT_BALL) {
        msgValue = UTIL1_GetValue32LE(&data[2]);
        remoteValues.ball.ballPresent = msgValue!=0;
        requestLCDUpdate = TRUE;
        remoteValues.ball.dataValid = TRUE;
      } else if (msgID==RAPP_MSG_TYPE_DATA_ID_REED_CONTACT) {
        msgValue = UTIL1_GetValue32LE(&data[2]);
        remoteValues.reed.contactNo = msgValue;
        requestLCDUpdate = TRUE;
        remoteValues.reed.dataValid = TRUE;
      } else if (msgID==RAPP_MSG_TYPE_DATA_ID_MINT_MODE) {
        msgValue = UTIL1_GetValue32LE(&data[2]);
        remoteValues.mintMode.mintMode = msgValue;
        requestLCDUpdate = TRUE;
        remoteValues.mintMode.dataValid = TRUE;
      } else if (msgID==RAPP_MSG_TYPE_DATA_ID_TOF_VALUES) {
        msgValue = UTIL1_GetValue32LE(&data[2]);
        remoteValues.tof.mm[3] = (msgValue>>24)&0xff;
        remoteValues.tof.mm[2] = (msgValue>>16)&0xff;
        remoteValues.tof.mm[1] = (msgValue>>8)&0xff;
        remoteValues.tof.mm[0] = msgValue&0xff;
        requestLCDUpdate = TRUE;
        remoteValues.tof.dataValid = TRUE;
      } else if (msgID==RAPP_MSG_TYPE_DATA_ID_BATTERY_V){
        msgValue = UTIL1_GetValue32LE(&data[2]);
        remoteValues.battVoltage.centiV = msgValue;
        requestLCDUpdate = TRUE;
        remoteValues.battVoltage.dataValid = TRUE;
      } else if (msgID==RAPP_MSG_TYPE_DATA_ID_PID_FW_SPEED){
        msgValue = UTIL1_GetValue32LE(&data[2]);
        remoteValues.pidfw.val = msgValue;
        requestLCDUpdate = TRUE;
        remoteValues.pidfw.dataValid = TRUE;
      } else if (msgID==RAPP_MSG_TYPE_DATA_ID_NEO_BRIGHTNESS){
        msgValue = UTIL1_GetValue32LE(&data[2]);
        remoteValues.NeoBrigthness.val = msgValue;
        requestLCDUpdate = TRUE;
        remoteValues.NeoBrigthness.dataValid = TRUE;
      } else if (msgID==RAPP_MSG_TYPE_DATA_ID_NEO_RED){
        msgValue = UTIL1_GetValue32LE(&data[2]);
        remoteValues.NeoRed.val = msgValue;
        requestLCDUpdate = TRUE;
        remoteValues.NeoRed.dataValid = TRUE;
      } else if (msgID==RAPP_MSG_TYPE_DATA_ID_NEO_GREEN){
        msgValue = UTIL1_GetValue32LE(&data[2]);
        remoteValues.NeoGreen.val = msgValue;
        requestLCDUpdate = TRUE;
        remoteValues.NeoGreen.dataValid = TRUE;
      } else if (msgID==RAPP_MSG_TYPE_DATA_ID_NEO_BLUE){
        msgValue = UTIL1_GetValue32LE(&data[2]);
        remoteValues.NeoBlue.val = msgValue;
        requestLCDUpdate = TRUE;
        remoteValues.NeoBlue.dataValid = TRUE;
      }
      break;

    default:
      break;
  } /* switch */
  return ERR_OK;
}

#if ENABLE_LCD_DEMO
/* simple demo to test the display */
static void DrawLines(void) {
  int i;
  GDisp1_PixelDim x, y, w, h;

  GDisp1_Clear();
  GDisp1_UpdateFull();

  GDisp1_DrawBox(0, 0, 10, 10, 1, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  vTaskDelay(pdMS_TO_TICKS(500));

  GDisp1_DrawBox(GDisp1_GetWidth()-10, 0, 10, 10, 1, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  vTaskDelay(pdMS_TO_TICKS(500));

  GDisp1_DrawLine(0, 0, GDisp1_GetWidth(), GDisp1_GetHeight(), GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  vTaskDelay(pdMS_TO_TICKS(500));
  GDisp1_DrawLine(0, GDisp1_GetHeight(), GDisp1_GetWidth(), 0, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  vTaskDelay(pdMS_TO_TICKS(500));
  for(i=0;i<10;i++) {
    GDisp1_DrawCircle(GDisp1_GetWidth()/2, GDisp1_GetHeight()/2, 5+i*2, GDisp1_COLOR_BLACK);
    GDisp1_UpdateFull();
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static void DrawFont(void) {
  FDisp1_PixelDim x, y;

  GDisp1_Clear();
  GDisp1_UpdateFull();
  x = 0;
  y = 10;
  FDisp1_WriteString("Hello World!", GDisp1_COLOR_BLACK, &x, &y, GFONT1_GetFont());
  GDisp1_UpdateFull();
  vTaskDelay(pdMS_TO_TICKS(500));
  x = 0;
  y += GFONT1_GetBoxHeight();
  FDisp1_WriteString("with Fonts!", GDisp1_COLOR_BLACK, &x, &y, GFONT1_GetFont());
  GDisp1_UpdateFull();
  WAIT1_Waitms(1000);
}

static void DrawText(void) {
  GDisp1_Clear();
  GDisp1_UpdateFull();
  PDC1_WriteLineStr(1, "hello");
  vTaskDelay(pdMS_TO_TICKS(200));
  PDC1_WriteLineStr(2, "world");
  vTaskDelay(pdMS_TO_TICKS(200));
  PDC1_WriteLineStr(3, "out");
  vTaskDelay(pdMS_TO_TICKS(200));
  PDC1_WriteLineStr(4, "there");
  vTaskDelay(pdMS_TO_TICKS(200));
  PDC1_WriteLineStr(5, "!!!!!");
  vTaskDelay(pdMS_TO_TICKS(200));
}

static void ShowTextOnLCD(unsigned char *text) {
  FDisp1_PixelDim x, y;

  GDisp1_Clear();
  x = 0;
  y = 10;
  FDisp1_WriteString(text, GDisp1_COLOR_BLACK, &x, &y, GFONT1_GetFont());
  GDisp1_UpdateFull();
}
#endif

static void LCD_Task(void *param) {
  (void)param; /* not used */
#if ENABLE_LCD_DEMO
  ShowTextOnLCD("Press a key!");
#endif
  LCDMenu_InitMenu(menus, sizeof(menus)/sizeof(menus[0]), 1);
  LCDMenu_OnEvent(LCDMENU_EVENT_DRAW, NULL);
  for(;;) {
    if (LedBackLightisOn) {
      LCD_LED_On(); /* LCD backlight on */
    } else {
      LCD_LED_Off(); /* LCD backlight off */
    }
    if (requestLCDUpdate) {
      requestLCDUpdate = FALSE;
      LCDMenu_OnEvent(LCDMENU_EVENT_DRAW, NULL);
    }
    {
      uint32_t notifcationValue;

      (void)xTaskNotifyWait(0UL, LCD_MENU_EVENT_UP|LCD_MENU_EVENT_DOWN|LCD_MENU_EVENT_LEFT|LCD_MENU_EVENT_RIGHT|LCD_MENU_EVENT_ENTER, &notifcationValue, 0); /* check flags */
      if (notifcationValue&LCD_MENU_EVENT_LEFT) {
        LCDMenu_OnEvent(LCDMENU_EVENT_LEFT, NULL);
      }
      if (notifcationValue&LCD_MENU_EVENT_RIGHT) {
        LCDMenu_OnEvent(LCDMENU_EVENT_RIGHT, NULL);
      }
      if (notifcationValue&LCD_MENU_EVENT_UP) {
        LCDMenu_OnEvent(LCDMENU_EVENT_UP, NULL);
      }
      if (notifcationValue&LCD_MENU_EVENT_DOWN) {
        LCDMenu_OnEvent(LCDMENU_EVENT_DOWN, NULL);
      }
      if (notifcationValue&LCD_MENU_EVENT_ENTER) {
        LCDMenu_OnEvent(LCDMENU_EVENT_ENTER, NULL);
      }
    }
    vTaskDelay(pdMS_TO_TICKS(20));
  }
}

void LCD_Deinit(void) {
#if PL_CONFIG_HAS_LCD_MENU
  LCDMenu_Deinit();
#endif
}

void LCD_Init(void) {
  LedBackLightisOn =  TRUE;
  if (xTaskCreate(LCD_Task, "LCD", 750/sizeof(StackType_t), NULL, tskIDLE_PRIORITY, &LCDTaskHandle) != pdPASS) {
    for(;;){} /* error! probably out of memory */
  }
  LCDMenu_Init();
}
#endif /* PL_CONFIG_HAS_LCD */

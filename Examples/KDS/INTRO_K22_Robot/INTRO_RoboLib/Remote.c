/**
 * \file
 * \brief Radio Remote Module
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module to handle accelerometer values passed over the Radio.
 */

#include "Platform.h" /* interface to the platform */
#if PL_CONFIG_HAS_REMOTE
#include "Remote.h"
#include "FRTOS1.h"
#include "CLS1.h"
#include "UTIL1.h"
#include "Shell.h"
#if PL_CONFIG_HAS_PID
  #include "PID.h"
#endif
#if PL_CONFIG_HAS_MOTOR
  #include "Motor.h"
#endif
#if PL_CONFIG_HAS_RADIO
  #include "RNet_App.h"
  #include "RNet_AppConfig.h"
#endif
#if PL_CONFIG_HAS_DRIVE
  #include "Drive.h"
#endif
#if PL_CONFIG_HAS_LED
  #include "LED.h"
#elif PL_HAS_USER_LED
  #include "LED1.h"
#endif
#if PL_CONFIG_HAS_JOYSTICK
  #include "AD1.h"
#endif
#if PL_CONFIG_HAS_SHELL
  #include "Shell.h"
#endif
#if PL_DO_LINE_MAZE
  #include "LineFollow.h"
  #include "Maze.h"
#endif
#if PL_HAS_DISTANCE_SENSOR
  #include "Distance.h"
#endif
#if PL_HAS_MINT
  #include "MintRobot.h"
#endif
#if PL_APP_LINE_FOLLOWING
  #include "LineFollow.h"
#endif
#if PL_APP_SUMO
  #include "Sumo.h"
#endif
#if PL_CONFIG_HAS_BUZZER
  #include "Buzzer.h"
#endif

static bool REMOTE_isOn = FALSE;
static bool REMOTE_isVerbose = FALSE;
static bool REMOTE_useJoystick = TRUE;
#if PL_CONFIG_HAS_JOYSTICK
static uint16_t midPointX, midPointY;
#endif

#if PL_CONFIG_CONTROL_SENDER
uint8_t REMOTE_SendButton(uint8_t button) {
  return RAPP_SendPayloadDataBlock(&button, sizeof(button), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
}
#endif

#if PL_CONFIG_CONTROL_SENDER
static int8_t ToSigned8Bit(uint16_t val, bool isX) {
  int32_t tmp;

  if (isX) {
    tmp = (int32_t)val-midPointX;
  } else {
    tmp = (int32_t)val-midPointY;
  }
  if (tmp>0) {
    tmp = (tmp*128)/0x7fff;
  } else {
    tmp = (-tmp*128)/0x7fff;
    tmp = -tmp;
  }
  if (tmp<-128) {
    tmp = -128;
  } else if (tmp>127) {
    tmp = 127;
  }
  return (int8_t)tmp;
}

static uint8_t REMOTE_GetXY(uint16_t *x, uint16_t *y, int8_t *x8, int8_t *y8) {
  uint8_t res;
  uint16_t values[2];

  res = AD1_Measure(TRUE);
  if (res!=ERR_OK) {
    return res;
  }
  res = AD1_GetValue16(&values[0]);
  if (res!=ERR_OK) {
    return res;
  }
  if (x!=NULL) {
    *x = values[0];
  }
  if (y!=NULL) {
    *y = values[1];
  }
  /* transform into -128...127 with zero as mid position */
  if (x8!=NULL) {
    *x8 = ToSigned8Bit(values[0], TRUE);
  }
  if (y8!=NULL) {
    *y8 = ToSigned8Bit(values[1], FALSE);
  }
  return ERR_OK;
}

static void RemoteTask(void *pvParameters) {
  (void)pvParameters;
#if PL_CONFIG_HAS_JOYSTICK
  (void)REMOTE_GetXY(&midPointX, &midPointY, NULL, NULL);
#endif
  FRTOS1_vTaskDelay(1000/portTICK_PERIOD_MS);
  for(;;) {
    if (REMOTE_isOn) {
#if PL_CONFIG_HAS_JOYSTICK
      if (REMOTE_useJoystick) {
        uint8_t buf[2];
        uint16_t x, y;
        int8_t x8, y8;

        /* send periodically messages */
        REMOTE_GetXY(&x, &y, &x8, &y8);
        buf[0] = x8;
        buf[1] = y8;
        if (REMOTE_isVerbose) {
          uint8_t txtBuf[48];

          UTIL1_strcpy(txtBuf, sizeof(txtBuf), (unsigned char*)"TX: x: ");
          UTIL1_strcatNum8s(txtBuf, sizeof(txtBuf), x8);
          UTIL1_strcat(txtBuf, sizeof(txtBuf), (unsigned char*)" y: ");
          UTIL1_strcatNum8s(txtBuf, sizeof(txtBuf), y8);
          UTIL1_strcat(txtBuf, sizeof(txtBuf), (unsigned char*)" to addr 0x");
    #if RNWK_SHORT_ADDR_SIZE==1
          UTIL1_strcatNum8Hex(txtBuf, sizeof(txtBuf), RNETA_GetDestAddr());
    #else
          UTIL1_strcatNum16Hex(txtBuf, sizeof(txtBuf), RNETA_GetDestAddr());
    #endif
          UTIL1_strcat(txtBuf, sizeof(txtBuf), (unsigned char*)"\r\n");
          SHELL_SendString(txtBuf);
        }
        (void)RAPP_SendPayloadDataBlock(buf, sizeof(buf), RAPP_MSG_TYPE_JOYSTICK_XY, RNETA_GetDestAddr(), RPHY_PACKET_FLAGS_REQ_ACK);
        LED1_Neg();
      }
#endif
      FRTOS1_vTaskDelay(200/portTICK_PERIOD_MS);
    } else {
      FRTOS1_vTaskDelay(1000/portTICK_PERIOD_MS);
    }
  } /* for */
}
#endif

#if PL_CONFIG_HAS_MOTOR
static bool AllowedToDrive(void) {
#if PL_HAS_MINT
  return MINT_AllowedToDrive();
#else
  return TRUE;
#endif
}

static void REMOTE_HandleMotorMsg(int16_t speedVal, int16_t directionVal, int16_t z) {
  #define MIN_VALUE   200 /* values below this value are ignored */
  int32_t speedLeft, speedRight;

  if (!REMOTE_isOn) {
    return;
  }
  if (!AllowedToDrive()) {
    return;
  }
  if (z<-900) { /* have a way to stop motor: turn FRDM USB port side up or down */
    speedLeft = speedRight = 0;
  } else if ((directionVal>MIN_VALUE || directionVal<-MIN_VALUE) && (speedVal>MIN_VALUE || speedVal<-MIN_VALUE)) {
    /* going diagonal */
    int16_t speed, speedL, speedR;
    
    speed = speedVal;
    if (directionVal<0) {
      if (speed<0) {
        speedR = speed+directionVal;
      } else {
        speedR = speed-directionVal;
      }
      speedL = speed;
    } else {
      speedR = speed;
      if (speed<0) {
        speedL = speed-directionVal;
      } else {
        speedL = speed+directionVal;
      }
    }
    speedLeft = speedL;
    speedRight = speedR;
  } else if (speedVal>100 || speedVal<-100) { /* straight driving forward/backward */
    speedLeft = speedVal;
    speedRight = speedVal;
  } else if (directionVal>100 || directionVal<-100) { /* direction, left/right turning */
    speedLeft = directionVal;
    speedRight = -directionVal;
  } else { /* device flat on the table? */
    speedLeft = speedRight = 0;
  }
#if PL_HAS_DISTANCE_SENSOR
  if (DIST_SpeedIntoObstacle(speedLeft, speedRight)!=0) {
    speedLeft = speedRight = 0;
  }
#endif
#if PL_CONFIG_HAS_DRIVE
  DRV_SetSpeed(speedLeft, speedRight);
#else
  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), speedLeft);
  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), speedRight);
#endif
}
#endif

#if PL_CONFIG_HAS_MOTOR
static int16_t scaleJoystickTo1K(int8_t val) {
  /* map speed from -128...127 to -1000...+1000 */
  int tmp;

  if (val>0) {
    tmp = ((val*10)/127)*100;
  } else {
    tmp = ((val*10)/128)*100;
  }
  if (tmp<-1000) {
    tmp = -1000;
  } else if (tmp>1000) {
    tmp = 1000;
  }
  return tmp;
}
#endif

uint8_t REMOTE_HandleRemoteRxMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet) {
  uint8_t val;
  bool beep = FALSE;
  
  (void)size;
  (void)packet;
  (void)srcAddr;
  switch(type) {
#if PL_APP_SUMO
    case RAPP_MSG_TYPE_REQUEST_SET_VALUE:
    {
      uint32_t val;
      uint16_t id;

      id = UTIL1_GetValue16LE(data); /* extract 16bit ID (little endian) */
      val = UTIL1_GetValue32LE(&data[2]);
      if (id==RAPP_MSG_TYPE_DATA_ID_SUMO_START_STOP) {
        *handled = FALSE;
        beep =  TRUE;
        if (val==0) {
          SUMO_StopSumo();
        } else {
          SUMO_StartCountdown();
        }
      } else if (id==RAPP_MSG_TYPE_DATA_ID_SUMO_RADAR) {
        *handled = FALSE;
        beep =  TRUE;
#if PL_HAS_DISTANCE_SENSOR
        if (val==0) {
          SUMO_RadarOff();
        } else {
          SUMO_RadarOn();
        }
#endif
      } else if (id==RAPP_MSG_TYPE_DATA_ID_SUMO_START_LEFT) {
        *handled = FALSE;
        beep =  TRUE;
#if PL_HAS_DISTANCE_SENSOR
        if (val==0) {
          SUMO_StartTurnRight();
        } else {
          SUMO_StartTurnLeft();
        }
#endif
      }
    }
    break;
#endif

#if PL_CONFIG_HAS_MOTOR
    case RAPP_MSG_TYPE_JOYSTICK_XY: /* values are -128...127 */
      {
        int8_t x, y;
        int16_t x1000, y1000;
        uint8_t buf[48];

        *handled = TRUE;
        x = *data; /* get x data value */
        y = *(data+1); /* get y data value */
        if (REMOTE_isVerbose) {
          UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"x/y: ");
          UTIL1_strcatNum8s(buf, sizeof(buf), (int8_t)x);
          UTIL1_chcat(buf, sizeof(buf), ',');
          UTIL1_strcatNum8s(buf, sizeof(buf), (int8_t)y);
          UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
          SHELL_SendString(buf);
        }
  #if 0 /* using shell command */
        UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"motor L duty ");
        UTIL1_strcatNum8s(buf, sizeof(buf), scaleSpeedToPercent(x));
        SHELL_ParseCmd(buf);
        UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"motor R duty ");
        UTIL1_strcatNum8s(buf, sizeof(buf), scaleSpeedToPercent(y));
        SHELL_ParseCmd(buf);
  #endif
        /* filter noise around zero */
        if (x>-5 && x<5) {
          x = 0;
        }
        if (y>-5 && y<5) {
          y = 0;
        }
        x1000 = scaleJoystickTo1K(x);
        y1000 = scaleJoystickTo1K(y);
        if (REMOTE_useJoystick) {
          REMOTE_HandleMotorMsg(y1000, x1000, 0); /* first param is forward/backward speed, second param is direction */
        }
      }
      break;
#endif

    case RAPP_MSG_TYPE_JOYSTICK_BTN:
      *handled = TRUE;
      val = *data; /* get data value */
      switch(val) {
        case 'u': /* up, forward */
        case 'a':
          #if PL_HAS_DRIVE
          if (AllowedToDrive()) {
            DRV_SetSpeed(700,700);
          }
          SHELL_SendString((uint8_t*)"Remote f\r\n");
          #endif
          break;
        case 'w': /* down, backward */
        case 'c':
          #if PL_HAS_DRIVE
          if (AllowedToDrive()) {
            DRV_SetSpeed(-700,-700);
          }
          SHELL_SendString((uint8_t*)"Remote b\r\n");
          #endif
          break;
        case 'l': /* left */
        case 'd':
          #if PL_HAS_DRIVE
          if (AllowedToDrive()) {
            DRV_SetSpeed(-500,500);
          }
          SHELL_SendString((uint8_t*)"Remote l\r\n");
          #endif
          break;
        case 'r': /* right */
        case 'b':
          #if PL_HAS_DRIVE
          if (AllowedToDrive()) {
            DRV_SetSpeed(500,-500);
          }
          SHELL_SendString((uint8_t*)"Remote r\r\n");
          #endif
          break;
        case 's': /* stop */
        case 'g': /* button analog joystick */
          #if PL_HAS_DRIVE
          if (AllowedToDrive()) {
            DRV_SetSpeed(0,0);
          }
          SHELL_SendString((uint8_t*)"Remote c\r\n");
          #endif
          break;

        case 'A':
          #if PL_CONFIG_HAS_BUZZER
          SHELL_ParseCmd((unsigned char*)"buzzer buz 300 500");
          #endif
          break;
        case 'B':
          #if PL_CONFIG_HAS_BUZZER
          SHELL_ParseCmd((unsigned char*)"buzzer buz 300 500");
          #endif
          break;
        case 'C':
          #if PL_CONFIG_HAS_BUZZER
          SHELL_ParseCmd((unsigned char*)"buzzer buz 300 500");
          #endif
          break;
        case 'D':
          #if PL_CONFIG_HAS_BUZZER
          SHELL_ParseCmd((unsigned char*)"buzzer buz 300 500");
          #endif
          break;
        case 'e':
          #if PL_CONFIG_HAS_BUZZER
          SHELL_ParseCmd((unsigned char*)"buzzer buz 300 200");
          #endif
          #if PL_CONFIG_HAS_REMOTE
          REMOTE_SetOnOff(TRUE);
          #endif
          #if PL_HAS_DRIVE
          DRV_SetSpeed(0,0); /* turn off motors */
          #endif
          SHELL_SendString((uint8_t*)"Remote ON\r\n");
          break;
        case 'E':
          #if PL_CONFIG_HAS_BUZZER
          SHELL_ParseCmd((unsigned char*)"buzzer buz 500 800");
          #endif
          #if PL_CONFIG_HAS_REMOTE
          REMOTE_SetOnOff(FALSE);
          #endif
          #if PL_HAS_DRIVE
          DRV_SetSpeed(0,0); /* turn off motors */
          DRV_SetMode(DRV_MODE_NONE);
          #endif
          SHELL_SendString((uint8_t*)"Remote OFF\r\n");
          break;
        case 'f':
          #if PL_APP_LINE_FOLLOWING
          if (LF_IsFollowing()) {
            LF_StopFollowing();
            SHELL_SendString((uint8_t*)"Stop Following\r\n");
          } else {
            LF_StartFollowing();
            SHELL_SendString((uint8_t*)"Start Following\r\n");
          }
          #endif
          break;
        case 'F': /* F button */
          #if PL_CONFIG_HAS_BUZZER
          SHELL_ParseCmd((unsigned char*)"buzzer buz 300 500");
          #endif
          #if PL_DO_LINE_MAZE
          if (MAZE_IsLeftHandRule()) {
            MAZE_SetHandRule(FALSE);
          } else {
            MAZE_SetHandRule(TRUE);
          }
          #endif
          break;
        case 'G': /* center joystick button for long: toggle joystick */
          if (REMOTE_useJoystick) {
            REMOTE_useJoystick = FALSE;
            #if PL_CONFIG_HAS_BUZZER
            SHELL_ParseCmd((unsigned char*)"buzzer buz 300 1000");
            #endif
            #if PL_CONFIG_HAS_SHELL
            SHELL_SendString((uint8_t*)"Joystick OFF\r\n");
            #endif
         } else {
            REMOTE_useJoystick = TRUE;
            #if PL_CONFIG_HAS_BUZZER
            SHELL_ParseCmd((unsigned char*)"buzzer buz 300 500");
            #endif
            #if PL_HAS_DRIVE
            DRV_SetSpeed(0,0); /* turn off motors */
            DRV_SetMode(DRV_MODE_SPEED);
            #endif
            #if PL_CONFIG_HAS_SHELL
            SHELL_SendString((uint8_t*)"Joystick ON\r\n");
            #endif
          }
          break;
        default: /* unknown? */
          #if PL_CONFIG_HAS_BUZZER
          SHELL_ParseCmd((unsigned char*)"buzzer buz 500 50");
          #endif
          break;
      } /* switch */
      break;
    default:
      break;
  } /* switch */
  if (beep) {
  #if PL_CONFIG_HAS_BUZZER
    BUZ_PlayTune(BUZ_TUNE_BUTTON);
  #endif
  }
  return ERR_OK;
}

#if PL_CONFIG_HAS_JOYSTICK
static void StatusPrintXY(CLS1_ConstStdIOType *io) {
  uint16_t x, y;
  int8_t x8, y8;
  uint8_t buf[64];

  if (REMOTE_GetXY(&x, &y, &x8, &y8)==ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"X: 0x");
    UTIL1_strcatNum16Hex(buf, sizeof(buf), x);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"(");
    UTIL1_strcatNum8s(buf, sizeof(buf), x8);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)") Y: 0x");
    UTIL1_strcatNum16Hex(buf, sizeof(buf), y);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"(");
    UTIL1_strcatNum8s(buf, sizeof(buf), y8);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)")\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"GetXY() failed!\r\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  analog", buf, io->stdOut);
}
#endif

static void REMOTE_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"remote", (unsigned char*)"Group of remote commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows remote help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  on|off", (unsigned char*)"Turns the remote on or off\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  verbose on|off", (unsigned char*)"Turns the verbose mode on or off\r\n", io->stdOut);
#if PL_CONFIG_HAS_JOYSTICK
  CLS1_SendHelpStr((unsigned char*)"  joystick on|off", (unsigned char*)"Use joystick\r\n", io->stdOut);
#endif
  CLS1_SendHelpStr((unsigned char*)"  Button keys", (unsigned char*)"lower case: short press, upper case: long press\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"",          (unsigned char*)"u:up, w:down, l:left, r:right, s:stop\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"",          (unsigned char*)"a:up, c:down, d:left, b:right, g:stop\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"",          (unsigned char*)"e:enable remote, E:disable remote remote\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"",          (unsigned char*)"f:start/stop line following, F:toggle Left/Right-Hand rule\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"",          (unsigned char*)"g:stop, G:enable/disable joystick)\r\n", io->stdOut);
}

static void REMOTE_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"remote", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  remote", REMOTE_isOn?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  joystick", REMOTE_useJoystick?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  verbose", REMOTE_isVerbose?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
#if PL_CONFIG_HAS_JOYSTICK
  StatusPrintXY(io);
#endif
}

uint8_t REMOTE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"remote help")==0) {
    REMOTE_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"remote status")==0) {
    REMOTE_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"remote on")==0) {
    REMOTE_isOn = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"remote off")==0) {
#if PL_CONFIG_HAS_MOTOR
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
#endif
    REMOTE_isOn = FALSE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"remote verbose on")==0) {
    REMOTE_isVerbose = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"remote verbose off")==0) {
    REMOTE_isVerbose = FALSE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"remote joystick on")==0) {
    REMOTE_useJoystick = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"remote joystick off")==0) {
    REMOTE_useJoystick = FALSE;
    *handled = TRUE;
  }
  return res;
}

bool REMOTE_GetOnOff(void) {
  return REMOTE_isOn;
}

void REMOTE_SetOnOff(bool on) {
  REMOTE_isOn = on;
}

void REMOTE_Deinit(void) {
  /* nothing to do */
}

/*! \brief Initializes module */
void REMOTE_Init(void) {
  REMOTE_isOn = TRUE;
  REMOTE_isVerbose = FALSE;
  REMOTE_useJoystick = TRUE;
#if PL_CONFIG_CONTROL_SENDER
  if (FRTOS1_xTaskCreate(RemoteTask, "Remote", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
}
#endif /* PL_CONFIG_HAS_REMOTE */


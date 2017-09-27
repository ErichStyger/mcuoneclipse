/*
 * Distance.c
 *
 *  Created on: Jun 23, 2013
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_HAS_DISTANCE_SENSOR
#include "Distance.h"
#include "CLS1.h"
#include "WAIT1.h"
#include "UTIL1.h"
#if PL_CONFIG_HAS_MOTOR
  #include "Motor.h"
#endif
#include "Shell.h"
#if PL_HAS_FRONT_DISTANCE
  #include "RSig.h"
  #include "REn.h"
  #include "MSig.h"
  #include "MEn.h"
  #include "LSig.h"
  #include "LEn.h"
#endif
#if PL_HAS_SIDE_DISTANCE
  #include "D5Left.h"
  #include "D5Right.h"
  #include "D10Left.h"
  #include "D10Right.h"
#endif
#if PL_HAS_TOF_SENSOR
  #include "VL6180X.h"
  #include "GI2C1.h"
  #include "TofPwr.h"
  #include "TofCE1.h"
  #include "TofCE2.h"
  #include "TofCE3.h"
  #include "TofCE4.h"
#endif

#if PL_HAS_TOF_SENSOR

#define VL_NOF_DEVICES 4 /* we have a sensor on each side of the robot */

static void DIST_TOF_CEPinAction_1(VL6180X_PIN_ACTION action) {
  switch(action) {
    case VL6180X_PIN_ACTION_SET_INPUT:  TofCE1_SetInput();  break;
    case VL6180X_PIN_ACTION_SET_OUTPUT: TofCE1_SetOutput(); break;
    case VL6180X_PIN_ACTION_SET_LOW:    TofCE1_ClrVal();    break;
    case VL6180X_PIN_ACTION_SET_HIGH:   TofCE1_SetVal();    break;
    default: break;
  }
}

static void DIST_TOF_CEPinAction_2(VL6180X_PIN_ACTION action) {
  switch(action) {
    case VL6180X_PIN_ACTION_SET_INPUT:  TofCE2_SetInput();  break;
    case VL6180X_PIN_ACTION_SET_OUTPUT: TofCE2_SetOutput(); break;
    case VL6180X_PIN_ACTION_SET_LOW:    TofCE2_ClrVal();    break;
    case VL6180X_PIN_ACTION_SET_HIGH:   TofCE2_SetVal();    break;
    default: break;
  }
}

static void DIST_TOF_CEPinAction_3(VL6180X_PIN_ACTION action) {
  switch(action) {
    case VL6180X_PIN_ACTION_SET_INPUT:  TofCE3_SetInput();  break;
    case VL6180X_PIN_ACTION_SET_OUTPUT: TofCE3_SetOutput(); break;
    case VL6180X_PIN_ACTION_SET_LOW:    TofCE3_ClrVal();    break;
    case VL6180X_PIN_ACTION_SET_HIGH:   TofCE3_SetVal();    break;
    default: break;
  }
}

static void DIST_TOF_CEPinAction_4(VL6180X_PIN_ACTION action) {
  switch(action) {
    case VL6180X_PIN_ACTION_SET_INPUT:  TofCE4_SetInput();  break;
    case VL6180X_PIN_ACTION_SET_OUTPUT: TofCE4_SetOutput(); break;
    case VL6180X_PIN_ACTION_SET_LOW:    TofCE4_ClrVal();    break;
    case VL6180X_PIN_ACTION_SET_HIGH:   TofCE4_SetVal();    break;
    default: break;
  }
}

typedef struct {
  int16_t mm; /* distance in mm, negative values are error values */
} DIST_ToF_DeviceDesc;

static DIST_ToF_DeviceDesc ToFDevice[VL_NOF_DEVICES]; /* ToF sensor distance in millimeters */
static VL6180X_Device DIST_ToF_Devices[] = {
  {.ptp_offset=0, .deviceAddr=VL6180X_DEFAULT_I2C_ADDRESS+1, .scale=VL6180X_SCALING_DEFAULT, .pinAction=DIST_TOF_CEPinAction_1},
  {.ptp_offset=0, .deviceAddr=VL6180X_DEFAULT_I2C_ADDRESS+2, .scale=VL6180X_SCALING_DEFAULT, .pinAction=DIST_TOF_CEPinAction_2},
  {.ptp_offset=0, .deviceAddr=VL6180X_DEFAULT_I2C_ADDRESS+3, .scale=VL6180X_SCALING_DEFAULT, .pinAction=DIST_TOF_CEPinAction_3},
  {.ptp_offset=0, .deviceAddr=VL6180X_DEFAULT_I2C_ADDRESS+4, .scale=VL6180X_SCALING_DEFAULT, .pinAction=DIST_TOF_CEPinAction_4},
};

typedef enum {
  DIST_TOF_REAR = 0,
  DIST_TOF_RIGHT = 1,
  DIST_TOF_FRONT = 2,
  DIST_TOF_LEFT = 3
} DIST_SensorPosition;

#endif

#if PL_HAS_FRONT_DISTANCE
  #define DIST_IR_WAIT_MS   1
#endif

#if PL_HAS_SIDE_DISTANCE
bool DIST_5cmLeftOn(void) {
  return D5Left_GetVal()==0;
}
#endif

#if PL_HAS_SIDE_DISTANCE
bool DIST_5cmRightOn(void) {
  return D5Right_GetVal()==0;
}
#endif

#if PL_HAS_SIDE_DISTANCE
bool DIST_10cmLeftOn(void) {
  return D10Left_GetVal()==0;
}
#endif

#if PL_HAS_SIDE_DISTANCE
bool DIST_10cmRightOn(void) {
  return D10Right_GetVal()==0;
}
#endif

#if PL_HAS_TOF_SENSOR
static int16_t DIST_GetToFDistance(DIST_SensorPosition pos) {
  if (pos>=sizeof(ToFDevice)/sizeof(ToFDevice[0])) {
    return 0; /* out of bounds? */
  }
  return ToFDevice[pos].mm;
}
#endif

int16_t DIST_GetDistance(DIST_Sensor sensor) {
  int16_t val = 0;

  switch(sensor) {
  case DIST_SENSOR_FRONT:
#if PL_HAS_TOF_SENSOR
    val = DIST_GetToFDistance(DIST_TOF_FRONT);
#endif
    break;
  case DIST_SENSOR_REAR:
#if PL_HAS_TOF_SENSOR
    val = DIST_GetToFDistance(DIST_TOF_REAR);
#endif
    break;
  case DIST_SENSOR_LEFT:
#if PL_HAS_TOF_SENSOR
    val = DIST_GetToFDistance(DIST_TOF_LEFT);
#endif
    break;
  case DIST_SENSOR_RIGHT:
#if PL_HAS_TOF_SENSOR
    val = DIST_GetToFDistance(DIST_TOF_RIGHT);
#endif
    break;
  }
  return val;
}

#if PL_HAS_FRONT_DISTANCE
/*!
 * \brief Return front sensor status
 * \return Bit pattern, 0b111 means echo on all sensors, 0b100 only on left, 0b010 only on middle, 0b001 only on right, and so on.
 */
static uint8_t LMRBits(void) {
  uint8_t val;
  
  val = 0;
  if (LSig_GetVal()==FALSE) { /* sensor received echo */
    val |= (1<<2);
  }
  if (MSig_GetVal()==FALSE) { /* sensor received echo */
    val |= (1<<1);
  }
  if (RSig_GetVal()==FALSE) { /* sensor received echo */
    val |= (1<<0);
  }
  return val;
}

uint8_t DIST_GetSensorBitsLeft(void) {
  uint8_t i, val = 0;

  LEn_SetVal(); /* HIGH: enable sensor */
  WAIT1_WaitOSms(DIST_IR_WAIT_MS); /* wait until IR LED is turned on */
  for(i=0;i<10;i++) {
    val |= LMRBits();
  }
  LEn_ClrVal(); /* LOW: disable sensor */
  return val;
}

uint8_t DIST_GetSensorBitsMiddle(void) {
  uint8_t i, val = 0;
  
  MEn_SetVal(); /* HIGH: enable sensor */
  WAIT1_WaitOSms(DIST_IR_WAIT_MS); /* wait until IR LED is turned on */
  for(i=0;i<10;i++) {
    val |= LMRBits();
  }
  MEn_ClrVal(); /* LOW: disable sensor */
  return val;
}

uint8_t DIST_GetSensorBitsRight(void) {
  uint8_t i, val = 0;

  REn_SetVal(); /* HIGH: enable sensor */
  WAIT1_WaitOSms(DIST_IR_WAIT_MS); /* wait until IR LED is turned on */
  for(i=0;i<10;i++) {
    val |= LMRBits();
  }
  REn_ClrVal(); /* LOW: disable sensor */
  return val;
}

bool DIST_LeftOn(void){
 bool isOn;
 
 LEn_SetVal(); /* HIGH: enable sensor */
 WAIT1_WaitOSms(DIST_IR_WAIT_MS); /* wait until IR LED is turned on */
 isOn = LSig_GetVal()==FALSE; /* LOW means something is in range */
 LEn_ClrVal(); /* LOW: disable sensor */
 return isOn;
}

bool DIST_MiddleOn(void){
 bool isOn;
 
 MEn_SetVal(); /* HIGH: enable sensor */
 WAIT1_WaitOSms(DIST_IR_WAIT_MS); /* wait until IR LED is turned on */
 isOn = MSig_GetVal()==FALSE; /* LOW means something is in range */
 MEn_ClrVal(); /* LOW: disable sensor */
 return isOn;
}

bool DIST_RightOn(void){
 bool isOn;
 
 REn_SetVal(); /* HIGH: enable sensor */
 WAIT1_WaitOSms(DIST_IR_WAIT_MS); /* wait until IR LED is turned on */
 isOn = RSig_GetVal()==FALSE; /* LOW means something is in range */
 REn_ClrVal(); /* LOW: disable sensor */
 return isOn;
}
#endif

bool DIST_NearFrontObstacle(int16_t distance) {
#if PL_HAS_TOF_SENSOR && VL_NOF_DEVICES>=1
  int16_t val;

  val = DIST_GetToFDistance(DIST_TOF_FRONT);
  if (val<0) {
    return TRUE; /* sensor failure? */
  }
  return val>=0 && val<=distance;
#else
  (void)distance;
  return FALSE;
#endif
}

bool DIST_NearRearObstacle(int distance) {
#if PL_HAS_TOF_SENSOR && VL_NOF_DEVICES>=3
  int16_t val;

  val = DIST_GetToFDistance(DIST_TOF_REAR);
  if (val<0) {
    return TRUE; /* sensor failure? */
  }
  return val>=0 && val<=distance;
#else
  (void)distance;
  return FALSE;
#endif
}

bool DIST_NearLeftObstacle(int distance) {
#if PL_HAS_TOF_SENSOR && VL_NOF_DEVICES>=4
  int16_t val;

  val = DIST_GetToFDistance(DIST_TOF_LEFT);
  if (val<0) {
    return TRUE; /* sensor failure? */
  }
  return val>=0 && val<=distance;
#else
  (void)distance;
  return FALSE;
#endif
}

bool DIST_NearRightObstacle(int distance) {
#if PL_HAS_TOF_SENSOR && VL_NOF_DEVICES>=4
  int16_t val;

  val = DIST_GetToFDistance(DIST_TOF_RIGHT);
  if (val<0) {
    return TRUE; /* sensor failure? */
  }
  return val>=0 && val<=distance;
#else
  (void)distance;
  return FALSE;
#endif
}

uint8_t DIST_CheckSurrounding(void) {
  uint8_t walls = 0;

#if PL_HAS_TOF_SENSOR
  if (DIST_NearFrontObstacle(60)) {
    walls |= (1<<DIST_TOF_FRONT);
  }
  if (DIST_NearRearObstacle(40)) {
    walls |= (1<<DIST_TOF_REAR);
  }
  if (DIST_NearLeftObstacle(50)) {
    walls |= (1<<DIST_TOF_LEFT);
  }
  if (DIST_NearRightObstacle(50)) {
    walls |= (1<<DIST_TOF_RIGHT);
  }
#endif
  return walls;
}

uint8_t DIST_SpeedIntoObstacle(int speedL, int speedR) { /* speed can be tacho ticks or percent */
  uint8_t hitBoundary = 0;

  if (speedL==0 && speedR==0) { /* not moving */
    return FALSE;
  }
  if (speedL>0 && speedR>0) { /* driving forward */
    if (DIST_NearFrontObstacle(60)) {
#if PL_HAS_TOF_SENSOR
      hitBoundary |= (1<<DIST_TOF_FRONT);
#endif
    }
  } else if (speedL<0 && speedR<0) { /* driving backward */
    if (DIST_NearRearObstacle(40)) {
#if PL_HAS_TOF_SENSOR
      hitBoundary |= (1<<DIST_TOF_REAR);
#endif
    }
  }
  if (speedL<=0 && speedR>0) { /* turning left on the spot */
    hitBoundary = DIST_CheckSurrounding();
  } else if (speedL>0 && speedR<=0) { /* turning right on the spot */
    hitBoundary = DIST_CheckSurrounding();
  }
  return hitBoundary; /* not driving into obstacle */
}

#if 0 && PL_CONFIG_HAS_MOTOR
uint8_t DIST_MotorDrivingIntoObstacle(void) {
  return DIST_SpeedIntoObstacle(
      MOT_GetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT)),
      MOT_GetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT)));
}
#endif

bool DIST_DriveToCenter(void) {
#if PL_HAS_TOF_SENSOR
  int16_t front, left, rear, right;

  front = ToFDevice[DIST_TOF_FRONT].mm;
  left  = ToFDevice[DIST_TOF_LEFT].mm;
  rear  = ToFDevice[DIST_TOF_REAR].mm;
  right  = ToFDevice[DIST_TOF_RIGHT].mm;
  if (front>150 && left>150 && right>150 && rear>150) {
    return TRUE; /* in the middle */
  }
#endif
  return FALSE; /* found center */
}

static void DIST_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"dist", (unsigned char*)"Group of distance commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows line help or status\r\n", io->stdOut);
#if PL_HAS_FRONT_DISTANCE
  CLS1_SendHelpStr((unsigned char*)"  (l|m|r) (on|off)", (unsigned char*)"Turn sensor (left, middle, right) on or off\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  test", (unsigned char*)"Test sensors\r\n", io->stdOut);
#endif
}

static void DIST_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"distance", (unsigned char*)"\r\n", io->stdOut);
#if PL_HAS_SIDE_DISTANCE
  CLS1_SendStatusStr((unsigned char*)"  10 cm", (unsigned char*)"", io->stdOut);
  if (DIST_10cmLeftOn()) {
    CLS1_SendStr((unsigned char*)"Left (on) ", io->stdOut);
  } else {
    CLS1_SendStr((unsigned char*)"Left (off) ", io->stdOut);
  }
  if (DIST_10cmRightOn()) {
    CLS1_SendStr((unsigned char*)"Right (on)\r\n", io->stdOut);
  } else {
    CLS1_SendStr((unsigned char*)"Right (off)\r\n", io->stdOut);
  }
  CLS1_SendStatusStr((unsigned char*)"  5 cm", (unsigned char*)"", io->stdOut);
  if (DIST_5cmLeftOn()) {
    CLS1_SendStr((unsigned char*)"Left (on) ", io->stdOut);
  } else {
    CLS1_SendStr((unsigned char*)"Left (off) ", io->stdOut);
  }
  if (DIST_5cmRightOn()) {
    CLS1_SendStr((unsigned char*)"Right (on)\r\n", io->stdOut);
  } else {
    CLS1_SendStr((unsigned char*)"Right (off)\r\n", io->stdOut);
  }
#endif
#if PL_HAS_FRONT_DISTANCE
  CLS1_SendStatusStr((unsigned char*)"  left", DIST_LeftOn()?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  middle", DIST_MiddleOn()?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  right", DIST_RightOn()?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  bits L", (unsigned char*)"", io->stdOut);
  {
    uint8_t val = DIST_GetSensorBitsLeft();
    if (val==0) {
      CLS1_SendStr((unsigned char*)"None\r\n", io->stdOut);
    } else {
      if (val&(1<<2)) {
        CLS1_SendStr((unsigned char*)"Left ", io->stdOut);
      }
      if (val&(1<<1)) {
        CLS1_SendStr((unsigned char*)"Middle ", io->stdOut);
      }
      if (val&(1<<0)) {
        CLS1_SendStr((unsigned char*)"Right", io->stdOut);
      }
      CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
    }
  }
  CLS1_SendStatusStr((unsigned char*)"  bits M", (unsigned char*)"", io->stdOut);
  {
    uint8_t val = DIST_GetSensorBitsMiddle();
    if (val==0) {
      CLS1_SendStr((unsigned char*)"None\r\n", io->stdOut);
    } else {
      if (val&(1<<2)) {
        CLS1_SendStr((unsigned char*)"Left ", io->stdOut);
      }
      if (val&(1<<1)) {
        CLS1_SendStr((unsigned char*)"Middle ", io->stdOut);
      }
      if (val&(1<<0)) {
        CLS1_SendStr((unsigned char*)"Right", io->stdOut);
      }
      CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
    }
  }
  CLS1_SendStatusStr((unsigned char*)"  bits R", (unsigned char*)"", io->stdOut);
  {
    uint8_t val = DIST_GetSensorBitsRight();
    if (val==0) {
      CLS1_SendStr((unsigned char*)"None\r\n", io->stdOut);
    } else {
      if (val&(1<<2)) {
        CLS1_SendStr((unsigned char*)"Left ", io->stdOut);
      }
      if (val&(1<<1)) {
        CLS1_SendStr((unsigned char*)"Middle ", io->stdOut);
      }
      if (val&(1<<0)) {
        CLS1_SendStr((unsigned char*)"Right", io->stdOut);
      }
      CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
    }
  }
#endif
#if PL_HAS_TOF_SENSOR
  {
#if 0
    uint8_t val=0;
    uint16_t ambient;
    int i;
#endif
    uint8_t buf[64];

    buf[0] = '\0';
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"front:");
    UTIL1_strcatNum16s(buf, sizeof(buf), DIST_GetDistance(DIST_SENSOR_FRONT));
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" mm left:");
    UTIL1_strcatNum16s(buf, sizeof(buf), DIST_GetDistance(DIST_SENSOR_LEFT));
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" mm rear:");
    UTIL1_strcatNum16s(buf, sizeof(buf), DIST_GetDistance(DIST_SENSOR_REAR));
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" mm right:");
    UTIL1_strcatNum16s(buf, sizeof(buf), DIST_GetDistance(DIST_SENSOR_RIGHT));
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" mm\r\n");
    CLS1_SendStatusStr((unsigned char*)"  range", buf, io->stdOut);
#if 0
    res = VL_ReadAmbientSingle(&ambient);
    if (res!=ERR_OK) {
      UTIL1_strcpy(buf, sizeof(buf), "ERROR ");
      UTIL1_strcatNum8u(buf, sizeof(buf), res);
      UTIL1_strcat(buf, sizeof(buf), "\r\n");
    } else {
      buf[0] = '\0';
      UTIL1_strcatNum16u(buf, sizeof(buf), ambient);
      UTIL1_strcat(buf, sizeof(buf), "\r\n");
    }
    CLS1_SendStatusStr((unsigned char*)"  ambient", buf, io->stdOut);
#endif
  }
#endif
}

uint8_t DIST_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"dist help")==0) {
    DIST_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"dist status")==0) {
    DIST_PrintStatus(io);
    *handled = TRUE;
#if PL_HAS_FRONT_DISTANCE
  } else if (UTIL1_strcmp((char*)cmd, (char*)"dist l on")==0) {
    LEn_SetVal(); /* HIGH: enable sensor */
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"dist l off")==0) {
    LEn_ClrVal(); /* LOW: disable sensor */
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"dist m on")==0) {
    MEn_SetVal(); /* HIGH: enable sensor */
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"dist m off")==0) {
    MEn_ClrVal(); /* LOW: disable sensor */
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"dist r on")==0) {
    REn_SetVal(); /* HIGH: enable sensor */
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"dist r off")==0) {
    REn_ClrVal(); /* LOW: disable sensor */
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"dist test")==0) {
    uint8_t i;
    
    for(i=0;i<10;i++) {
      LEn_SetVal(); /* HIGH: enable sensor */
      WAIT1_WaitOSms(1000);
      CLS1_SendStr((uint8_t*)"left: ", io->stdOut);
      CLS1_SendNum8u(DIST_GetSensorBitsLeft(), io->stdOut);
      
      MEn_SetVal(); /* HIGH: enable sensor */s
      WAIT1_WaitOSms(1000);
      CLS1_SendStr((uint8_t*)" middle: ", io->stdOut);
      CLS1_SendNum8u(DIST_GetSensorBitsMiddle(), io->stdOut);
      
      REn_SetVal(); /* HIGH: enable sensor */
      WAIT1_WaitOSms(1000);
      CLS1_SendStr((uint8_t*)" right: ", io->stdOut);
      CLS1_SendNum8u(DIST_GetSensorBitsRight(), io->stdOut);
      CLS1_SendStr((uint8_t*)"\r\n", io->stdOut);
    }
    *handled = TRUE;
#endif
  }
  return res;
}

#if PL_HAS_TOF_SENSOR
static uint8_t InitToF(void) {
  uint8_t res;
  int i;

  /* initialize data structure */
  for(i=0;i<VL_NOF_DEVICES;i++) {
    ToFDevice[i].mm = 0;
  }
  /* disable all devices (CE pin LOW): we will bring them up later one by one.... */
  for(i=0;i<VL_NOF_DEVICES;i++) {
    (void)VL6180X_ChipEnable(&DIST_ToF_Devices[i], FALSE); /* disable device */
  }
  for(i=0;i<VL_NOF_DEVICES;i++) {
    (void)VL6180X_ChipEnable(&DIST_ToF_Devices[i], TRUE); /* enable device */
    vTaskDelay(pdMS_TO_TICKS(100)); /* give some time to get it enabled */
    res = VL6180X_SetI2CDeviceAddress(&DIST_ToF_Devices[i]); /* set hardware I2C address */
    if (res!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"ERROR: Failed set i2C address of TOF device: ", SHELL_GetStdio()->stdErr);
      CLS1_SendNum8u(i, SHELL_GetStdio()->stdErr);
      CLS1_SendStr((unsigned char*)"\r\n", SHELL_GetStdio()->stdErr);
      vTaskDelay(pdMS_TO_TICKS(1000)); /* delay for some time */
      return res;
    }
  }
  /* at this time all devices are enabled (CE pin HIGH) and have unique I2C addresses */
  for(i=0;i<VL_NOF_DEVICES;i++) {
    res = VL6180X_InitAndConfigureDevice(&DIST_ToF_Devices[i]);
    if (res!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"ERROR: Failed init of TOF device: ", SHELL_GetStdio()->stdErr);
      CLS1_SendNum8u(i, SHELL_GetStdio()->stdErr);
      CLS1_SendStr((unsigned char*)"\r\n", SHELL_GetStdio()->stdErr);
      return res;
    }
  }
  return ERR_OK;
}

static void TofTask(void *param) {
  uint8_t res;
  int errCntr = 0;
  int i;
  bool initDevices = TRUE;

  (void)param;
  vTaskDelay(pdMS_TO_TICKS(500)); /* wait to give sensor time to power up */
  for(;;) {
    if (initDevices) {
      do {
        TofPwr_SetVal(); /* HIGH: disable power */
        vTaskDelay(pdMS_TO_TICKS(100));
        TofPwr_ClrVal(); /* LOW: enable power */
        vTaskDelay(pdMS_TO_TICKS(100));
        res = InitToF();
        if (res!=ERR_OK) {
          CLS1_SendStr((unsigned char*)"ToF init failed, retry....!\r\n", SHELL_GetStdio()->stdErr);
          vTaskDelay(pdMS_TO_TICKS(1000));
        }
      } while (res!=ERR_OK);
      CLS1_SendStr((unsigned char*)"ToF enabled!\r\n", SHELL_GetStdio()->stdOut);
      initDevices = FALSE;
    }
#if 0
    for(i=0;i<VL_NOF_DEVICES;i++) {
      int16_t range;

      range = 0;
      res = VL6180X_ReadRangeSingle(&DIST_ToF_Devices[i], &range);
      if (res!=ERR_OK) {
        CLS1_SendStr((unsigned char*)"Read ToF FAILED!\r\n", SHELL_GetStdio()->stdErr);
        errCntr++;
        //GI2C1_Deinit(); /* should not be necessary */
        //GI2C1_Init();
        initDevices = TRUE; /* re-init devices */
        range = -3; /* error range */
      }
      ToFDevice[i].mm = range;
    } /* for */
#else
    {
      int16_t range[VL_NOF_DEVICES];

      res = VL6180X_ReadRangeSingleMultiple(&DIST_ToF_Devices[0], &range[0], VL_NOF_DEVICES);
      if (res!=ERR_OK) {
        CLS1_SendStr((unsigned char*)"Read ToF FAILED!\r\n", SHELL_GetStdio()->stdErr);
        errCntr++;
        initDevices = TRUE; /* re-init devices */
      }
      for(i=0;i<VL_NOF_DEVICES;i++) {
        ToFDevice[i].mm = range[i];
      }
    }
#endif
    vTaskDelay(pdMS_TO_TICKS(5));
  }
}
#endif /* PL_HAS_TOF_SENSOR */

void DIST_Deinit(void) {
}

void DIST_Init(void) {
#if PL_HAS_TOF_SENSOR
  if (xTaskCreate(TofTask, "ToF", 1000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
}

#endif /* PL_HAS_DISTANCE_SENSOR */


#include "Platform.h"
#include "Pid.h"
#include "Motor.h"
#include "UTIL1.h"
#include "CLS1.h"
#include "Reflectance.h"

#define PID_DEBUG 0 /* careful: this will slow down the PID loop frequency! */

typedef struct {
  int32_t pFactor100;
  int32_t iFactor100;
  int32_t dFactor100;
  int32_t iAntiWindup;
  uint8_t maxSpeedPercent; /* max speed if 100% on the line, 0xffff would be full speed */
  int32_t lastError;
  int32_t integral;
} PID_Config;

static PID_Config lineFwConfig;
#if PL_GO_DEADEND_BW
static PID_Config lineBwConfig;
#endif
#if PL_HAS_QUADRATURE
static PID_Config posConfig;
#endif

#if PL_HAS_LINE_SENSOR
static int32_t Limit(int32_t val, int32_t minVal, int32_t maxVal) {
  if (val<minVal) {
    return minVal;
  } else if (val>maxVal) {
    return maxVal;
  }
  return val;
}
#endif

#if PL_HAS_LINE_SENSOR
static MOT_Direction AbsSpeed(int32_t *speedP) {
  if (*speedP<0) {
    *speedP = -(*speedP);
    return MOT_DIR_BACKWARD;
  }
  return MOT_DIR_FORWARD;
}
#endif 

#if PL_HAS_LINE_SENSOR
/*! \brief returns error (always positive) percent */
static uint8_t errorWithinPercent(int32_t error) {
  if (error<0) {
    error = -error;
  }
  return error/(REF_MAX_LINE_VALUE/2/100);
}

static int32_t PID(uint16_t currVal, uint16_t setVal, PID_Config *config) {
  int32_t error;
  int32_t pid;
  
  /* perform PID closed control loop calculation */
  error = setVal-currVal; /* calculate error */
  pid = (error*config->pFactor100)/100; /* P part */
  config->integral += error; /* integrate error */
  if (config->integral>config->iAntiWindup) {
    config->integral = config->iAntiWindup;
  } else if (config->integral<-config->iAntiWindup) {
    config->integral = -config->iAntiWindup;
  }
  pid += (config->integral*config->iFactor100)/100; /* add I part */
  pid += ((error-config->lastError)*config->dFactor100)/100; /* add D part */
  config->lastError = error; /* remember for next iteration of D part */
  return pid;
}

void PID_LineCfg(uint16_t currLine, uint16_t setLine, bool forward, PID_Config *config) {
  int32_t pid, speed, speedL, speedR;
#if PID_DEBUG
  unsigned char buf[16];
  static uint8_t cnt = 0;
#endif
  uint8_t errorPercent;
  MOT_Direction directionL=MOT_DIR_FORWARD, directionR=MOT_DIR_FORWARD;
  
  pid = PID(currLine, setLine, config);
  errorPercent = errorWithinPercent(currLine-setLine);
  
  /* transform into different speed for motors. The PID is used as difference value to the motor PWM */
  if (!forward) { /* going backward */
    /* need to do it slow as sensor is on the 'back', and we cannot usual turns to get the sensor back 'on line' */
    speed = ((int32_t)config->maxSpeedPercent)*(0xffff/100)*6/10; /* %60 */
    pid = Limit(pid, -speed, speed);
    if (pid<0) { /* turn right */
      speedR = speed;
      speedL = speed-pid;
    } else { /* turn left */
      speedR = speed+pid;
      speedL = speed;
    }
  } else if (errorPercent <= 20) { /* pretty on center: move forward both motors with base speed */
    speed = ((int32_t)config->maxSpeedPercent)*(0xffff/100); /* 100% */
    pid = Limit(pid, -speed, speed);
    if (pid<0) { /* turn right */
      speedR = speed;
      speedL = speed-pid;
    } else { /* turn left */
      speedR = speed+pid;
      speedL = speed;
    }
  } else if (errorPercent <= 40) { 
    /* outside left/right halve position from center, slow down one motor and speed up the other */
    speed = ((int32_t)config->maxSpeedPercent)*(0xffff/100)*8/10; /* 80% */
    pid = Limit(pid, -speed, speed);
    if (pid<0) { /* turn right */
      speedR = speed+pid; /* decrease speed */
      speedL = speed-pid; /* increase speed */
    } else { /* turn left */
      speedR = speed+pid; /* increase speed */
      speedL = speed-pid; /* decrease speed */
    }
  } else if (errorPercent <= 70) { 
    speed = ((int32_t)config->maxSpeedPercent)*(0xffff/100)*6/10; /* %60 */
    pid = Limit(pid, -speed, speed);
    if (pid<0) { /* turn right */
      speedR = 0 /*maxSpeed+pid*/; /* decrease speed */
      speedL = speed-pid; /* increase speed */
    } else { /* turn left */
      speedR = speed+pid; /* increase speed */
      speedL = 0 /*maxSpeed-pid*/; /* decrease speed */
    }
  } else  {
    /* line is far to the left or right: use backward motor motion */
    speed = ((int32_t)config->maxSpeedPercent)*(0xffff/100)*10/10; /* %80 */
    if (pid<0) { /* turn right */
      speedR = -speed+pid; /* decrease speed */
      speedL = speed-pid; /* increase speed */
    } else { /* turn left */
      speedR = speed+pid; /* increase speed */
      speedL = -speed-pid; /* decrease speed */
    }
    speedL = Limit(speedL, -speed, speed);
    speedR = Limit(speedR, -speed, speed);
    directionL = AbsSpeed(&speedL);
    directionR = AbsSpeed(&speedR);
  }
  /* speed is now always positive, make sure it is within 16bit PWM boundary */
  if (speedL>0xFFFF) {
    speedL = 0xFFFF;
  } else if (speedL<0) {
    speedL = 0;
  }
  if (speedR>0xFFFF) {
    speedR = 0xFFFF;
  } else if (speedR<0) {
    speedR = 0;
  }
  if (!forward) { /* swap direction/speed */
    if (directionL==MOT_DIR_FORWARD) {
      directionL=MOT_DIR_BACKWARD;
    } else {
      directionL=MOT_DIR_FORWARD;
    }
    if (directionR==MOT_DIR_FORWARD) {
      directionR=MOT_DIR_BACKWARD;
    } else {
      directionR=MOT_DIR_FORWARD;
    }
  }
  /* send new speed values to motor */
  MOT_SetVal(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0xFFFF-speedL); /* PWM is low active */
  MOT_SetDirection(MOT_GetMotorHandle(MOT_MOTOR_LEFT), directionL);
  MOT_SetVal(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0xFFFF-speedR); /* PWM is low active */
  MOT_SetDirection(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), directionR);
#if PID_DEBUG /* debug diagnostic */
  {
    cnt++;
    if (cnt>10) { /* limit number of messages to the console */
      CLS1_StdIO_OutErr_FctType ioOut = CLS1_GetStdio()->stdOut;
      cnt = 0;
      
      CLS1_SendStr((unsigned char*)"line:", ioOut);
      buf[0] = '\0';
      UTIL1_strcatNum16u(buf, sizeof(buf), currLine);
      CLS1_SendStr(buf, ioOut);
  
      CLS1_SendStr((unsigned char*)" sum:", ioOut);
      buf[0] = '\0';
      UTIL1_strcatNum32Hex(buf, sizeof(buf), integral);
      CLS1_SendStr(buf, ioOut);
      
      CLS1_SendStr((unsigned char*)" left:", ioOut);
      CLS1_SendStr(directionL==MOT_DIR_FORWARD?(unsigned char*)"fw ":(unsigned char*)"bw ", ioOut);
      buf[0] = '\0';
      UTIL1_strcatNum16Hex(buf, sizeof(buf), speedL);
      CLS1_SendStr(buf, ioOut);
  
      CLS1_SendStr((unsigned char*)" right:", ioOut);
      CLS1_SendStr(directionR==MOT_DIR_FORWARD?(unsigned char*)"fw ":(unsigned char*)"bw ", ioOut);
      buf[0] = '\0';
      UTIL1_strcatNum16Hex(buf, sizeof(buf), speedR);
      CLS1_SendStr(buf, ioOut);
      
      CLS1_SendStr((unsigned char*)"\r\n", ioOut);
    }
  }
#endif
}
#endif /* PL_HAS_LINE_SENSOR */

void PID_Line(uint16_t currLine, uint16_t setLine, bool forward) {
#if PL_GO_DEADEND_BW
  if (forward) {
    PID_LineCfg(currLine, setLine, forward, &lineFwConfig);
  } else {
    PID_LineCfg(currLine, setLine, forward, &lineBwConfig);
  }
#else
  (void)forward; /* not used */
  PID_LineCfg(currLine, setLine, forward, &lineFwConfig);
#endif
}

#if PL_HAS_QUADRATURE
void PID_PosCfg(int16_t currPos, int16_t setPos, bool isLeft, PID_Config *config) {
  int32_t pid, speed;
  MOT_Direction direction=MOT_DIR_FORWARD;
  
  pid = PID(currPos, setPos, config);

  /* transform into motor speed */
  speed = ((int32_t)config->maxSpeedPercent)*(0xffff/100); /* limit the speed */
  pid = Limit(pid, -speed, speed);
  if (pid<0) { /* move forward */
    speed -= pid;
    direction = MOT_DIR_FORWARD;
  } else { /* move backward */
    speed += pid;
    direction = MOT_DIR_BACKWARD;
  }
  /* speed is now always positive, make sure it is within 16bit PWM boundary */
  if (speed>0xFFFF) {
    speed = 0xFFFF;
  } else if (speed<0) {
    speed = 0;
  }
  /* send new speed values to motor */
  if (isLeft) {
    MOT_SetVal(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0xFFFF-speed); /* PWM is low active */
    MOT_SetDirection(MOT_GetMotorHandle(MOT_MOTOR_LEFT), direction);
  } else {
    MOT_SetVal(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0xFFFF-speed); /* PWM is low active */
    MOT_SetDirection(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), direction);
  }
}

void PID_Pos(int16_t currPos, int16_t setPos, bool isLeft) {
}
#endif

static void PID_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"pid", (unsigned char*)"Group of PID commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows PID help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  fw (p|d|i|w) <value>", (unsigned char*)"Sets P, D, I or anti-windup line value\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  fw speed <value>", (unsigned char*)"Maximum speed % value\r\n", io->stdOut);
#if PL_GO_DEADEND_BW
  CLS1_SendHelpStr((unsigned char*)"  bw (p|d|i|w) <value>", (unsigned char*)"Sets P, D, I or anti-windup backward value\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  bw speed <value>", (unsigned char*)"Maximum backward speed % value\r\n", io->stdOut);
#endif
#if PL_HAS_QUADRATURE
  CLS1_SendHelpStr((unsigned char*)"  pos (p|d|i|w) <value>", (unsigned char*)"Sets P, D, I or anti-windup position value\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  pos speed <value>", (unsigned char*)"Maximum speed % value\r\n", io->stdOut);
#endif
}

static void PrintPIDstatus(PID_Config *config, const unsigned char *kindStr, const CLS1_StdIOType *io) {
  unsigned char buf[48];
  unsigned char kindBuf[16];

  UTIL1_strcpy(kindBuf, sizeof(buf), (unsigned char*)"  ");
  UTIL1_strcat(kindBuf, sizeof(buf), kindStr);
  UTIL1_strcat(kindBuf, sizeof(buf), (unsigned char*)" PID");
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"p: ");
  UTIL1_strcatNum32s(buf, sizeof(buf), config->pFactor100);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" i: ");
  UTIL1_strcatNum32s(buf, sizeof(buf), config->iFactor100);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" d: ");
  UTIL1_strcatNum32s(buf, sizeof(buf), config->dFactor100);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr(kindBuf, buf, io->stdOut);

  UTIL1_strcpy(kindBuf, sizeof(buf), (unsigned char*)"  ");
  UTIL1_strcat(kindBuf, sizeof(buf), kindStr);
  UTIL1_strcat(kindBuf, sizeof(buf), (unsigned char*)" windup");
  UTIL1_Num32sToStr(buf, sizeof(buf), config->iAntiWindup);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr(kindBuf, buf, io->stdOut);

  UTIL1_strcpy(kindBuf, sizeof(buf), (unsigned char*)"  ");
  UTIL1_strcat(kindBuf, sizeof(buf), kindStr);
  UTIL1_strcat(kindBuf, sizeof(buf), (unsigned char*)" speed");
  UTIL1_Num8uToStr(buf, sizeof(buf), config->maxSpeedPercent);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"%\r\n");
  CLS1_SendStatusStr(kindBuf, buf, io->stdOut);
 
}

static void PID_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"pid", (unsigned char*)"\r\n", io->stdOut);
  PrintPIDstatus(&lineFwConfig, (unsigned char*)"fw", io);
#if PL_GO_DEADEND_BW
  PrintPIDstatus(&lineBwConfig, (unsigned char*)"bw", io);
#endif
#if PL_HAS_QUADRATURE
  PrintPIDstatus(&posConfig, (unsigned char*)"pos", io);
#endif  
}

static uint8_t ParsePidParameter(PID_Config *config, const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  const unsigned char *p;
  uint32_t val32u;
  uint8_t val8u;
  uint8_t res = ERR_OK;

  if (UTIL1_strncmp((char*)cmd, (char*)"p ", sizeof("p ")-1)==0) {
    p = cmd+sizeof("p");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      config->pFactor100 = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"i ", sizeof("i ")-1)==0) {
    p = cmd+sizeof("i");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      config->iFactor100 = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"d ", sizeof("d ")-1)==0) {
    p = cmd+sizeof("d");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      config->dFactor100 = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"w ", sizeof("w ")-1)==0) {
    p = cmd+sizeof("w");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      config->iAntiWindup = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"speed ", sizeof("speed ")-1)==0) {
    p = cmd+sizeof("speed");
    if (UTIL1_ScanDecimal8uNumber(&p, &val8u)==ERR_OK && val8u<=100) {
      config->maxSpeedPercent = val8u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  }
  return res;
}

uint8_t PID_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"pid help")==0) {
    PID_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"pid status")==0) {
    PID_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid fw ", sizeof("pid fw ")-1)==0) {
    res = ParsePidParameter(&lineFwConfig, cmd+sizeof("pid fw ")-1, handled, io);
#if PL_GO_DEADEND_BW
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid bw ", sizeof("pid bw ")-1)==0) {
    res = ParsePidParameter(&lineBwConfig, cmd+sizeof("pid bw ")-1, handled, io);
#endif
#if PL_HAS_QUADRATURE
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid pos ", sizeof("pid pos ")-1)==0) {
    res = ParsePidParameter(&posConfig, cmd+sizeof("pid pos ")-1, handled, io);
#endif
  }
  return res;
}

void PID_Start(void) {
  lineFwConfig.lastError = 0;
  lineFwConfig.integral = 0;
#if PL_GO_DEADEND_BW
  lineBwConfig.lastError = 0;
  lineBwConfig.integral = 0;
#endif
#if PL_HAS_QUADRATURE
  posConfig.lastError = 0;
  posConfig.integral = 0;
#endif
}

void PID_Init(void) {
#if PL_IS_ZUMO_ROBOT
  lineFwConfig.pFactor100 = 5000;
  lineFwConfig.iFactor100 = 10;
  lineFwConfig.dFactor100 = 100;
  lineFwConfig.iAntiWindup = 100000;
  lineFwConfig.maxSpeedPercent = 50;
  lineFwConfig.lastError = 0;
  lineFwConfig.integral = 0;
#elif PL_IS_ROUND_ROBOT
  lineFwConfig.pFactor100 = 200;
  lineFwConfig.iFactor100 = 1;
  lineFwConfig.dFactor100 = 50000;
  lineFwConfig.iAntiWindup = 20000;
  lineFwConfig.maxSpeedPercent = 15;
  lineFwConfig.lastError = 0;
  lineFwConfig.integral = 0;
#elif PL_IS_TRACK_ROBOT
  lineFwConfig.pFactor100 = 400;
  lineFwConfig.iFactor100 = 1;
  lineFwConfig.dFactor100 = 50000;
  lineFwConfig.iAntiWindup = 20000;
  lineFwConfig.maxSpeedPercent = 17;
  lineFwConfig.lastError = 0;
  lineFwConfig.integral = 0;
#else
  #error "unknown configuration!"
#endif
#if PL_GO_DEADEND_BW
  lineBwConfig.pFactor100 = 1000;
  lineBwConfig.iFactor100 = 0;
  lineBwConfig.dFactor100 = 0;
  lineBwConfig.iAntiWindup = 100000;
  lineBwConfig.maxSpeedPercent = 60;
  lineBwConfig.lastError = 0;
  lineBwConfig.integral = 0;
#endif
#if PL_HAS_QUADRATURE
  posConfig.pFactor100 = 3000;
  posConfig.iFactor100 = 1;
  posConfig.dFactor100 = 20000;
  posConfig.iAntiWindup = 50;
  posConfig.maxSpeedPercent = 15;
  posConfig.lastError = 0;
  posConfig.integral = 0;
#endif
}

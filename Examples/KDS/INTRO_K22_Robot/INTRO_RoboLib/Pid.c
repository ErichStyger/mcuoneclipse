/**
 * \file
 * \brief This is the implementation of the PID Module
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_HAS_PID
#include "Pid.h"
#include "Motor.h"
#include "UTIL1.h"
#include "Reflectance.h"

#define PID_DEBUG 0 /* careful: this will slow down the PID loop frequency! */

#if PL_HAS_LINE_PID
  static PID_Config lineFwConfig;
#endif
#if PL_GO_DEADEND_BW
  static PID_Config lineBwConfig;
#endif
#if PL_HAS_POS_PID
  static PID_Config posLeftConfig, posRightConfig;
#endif
#if PL_HAS_SPEED_PID
  static PID_Config speedLeftConfig, speedRightConfig;
#endif
  
uint8_t PID_GetPIDConfig(PID_ConfigType config, PID_Config **confP) {
  switch(config) {
#if PL_HAS_LINE_PID
    case PID_CONFIG_LINE_FW:
      *confP = &lineFwConfig; break;
#endif
#if PL_GO_DEADEND_BW
    case PID_CONFIG_LINE_BW:
      *confP = &lineBwConfig; break;
#endif
    case PID_CONFIG_POS_LEFT:
      *confP = &posLeftConfig; break;
    case PID_CONFIG_POS_RIGHT:
      *confP = &posRightConfig; break;
    case PID_CONFIG_SPEED_LEFT:
      *confP = &speedLeftConfig; break;
    case PID_CONFIG_SPEED_RIGHT:
      *confP = &speedRightConfig; break;
    default:
      *confP = NULL;
      return ERR_FAILED;
  }
  return ERR_OK;
}

#if PL_HAS_SPEED_PID || PL_HAS_POS_PID || PL_HAS_LINE_PID
static int32_t PID(int32_t currVal, int32_t setVal, PID_Config *config) {
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
#if 1 /* see http://brettbeauregard.com/blog/2011/04/improving-the-beginner%E2%80%99s-pid-reset-windup/ */
  {
    int32_t max;

    max = 0xffff; /* max value of PWM */
    if (config->integral > max) {
      config->integral = max;
    } else if (config->integral < -max) {
      config->integral = -max;
    }
  }
#endif
  pid += (config->integral*config->iFactor100)/100; /* add I part */
  pid += ((error-config->lastError)*config->dFactor100)/100; /* add D part */
  config->lastError = error; /* remember for next iteration of D part */
  return pid;
}
#endif

#if PL_HAS_LINE_PID
static int32_t Limit(int32_t val, int32_t minVal, int32_t maxVal) {
  if (val<minVal) {
    return minVal;
  } else if (val>maxVal) {
    return maxVal;
  }
  return val;
}

#if 0
static MOT_Direction AbsSpeed(int32_t *speedP) {
  if (*speedP<0) {
    *speedP = -(*speedP);
    return MOT_DIR_BACKWARD;
  }
  return MOT_DIR_FORWARD;
}
#endif

#if 0
/*! \brief returns error (always positive) percent */
static uint8_t errorWithinPercent(int32_t error) {
  if (error<0) {
    error = -error;
  }
  error = error/(REF_MAX_LINE_VALUE/2/100);
  if (error>100) {
    error = 100;
  }
  return error;
}
#endif

#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
static void PID_LineCfg(uint16_t currLine, uint16_t setLine, uint16_t currLineWidth, bool forward, PID_Config *config) {
  int32_t pid, speed, speedL, speedR;
#if PID_DEBUG
  unsigned char buf[16];
  static uint8_t cnt = 0;
#endif
//  uint8_t errorPercent;
  MOT_Direction directionL=MOT_DIR_FORWARD, directionR=MOT_DIR_FORWARD;
  
  (void)currLineWidth;

  pid = PID(currLine, setLine, config);
  //errorPercent = errorWithinPercent(currLine-setLine);
  
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
#if 0 /* simple differential steering */
  } else {
    speed = ((int32_t)config->maxSpeedPercent)*(0xffff/100); /* 100% */
    pid = Limit(pid, -speed, speed);
    if (pid<0) { /* turn right */
      speedR = speed;
      speedL = speed-pid;
    } else { /* turn left */
      speedR = speed+pid;
      speedL = speed;
    }
  }
#elif 1 || PL_DO_MINT /* aggressive line following! */
  } else {
    speed = ((int32_t)config->maxSpeedPercent)*(0xffff/100); /* scale to base speed */
    if (pid<0) { /* turn right */
      speedR = speed+pid; /* decrease speed */
      speedL = speed-pid; /* increase speed */
    } else { /* turn left */
      speedR = speed+pid; /* increase speed */
      speedL = speed-pid; /* decrease speed */
    }
  }
#else
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
  } else if (errorPercent <= 30) {
    /* outside left/right halve position from center, slow down one motor and speed up the other */
//    speed = ((int32_t)config->maxSpeedPercent)*(0xffff/100)*10/10; /* 80% */
    speed = 50*(0xffff/100);
    pid = Limit(pid, -speed, speed);
    if (pid<0) { /* turn right */
      speedR = speed+pid; /* decrease speed */
      speedL = speed-pid; /* increase speed */
    } else { /* turn left */
      speedR = speed+pid; /* increase speed */
      speedL = speed-pid; /* decrease speed */
    }
  } else if (errorPercent <= 60) {
//    speed = ((int32_t)config->maxSpeedPercent)*(0xffff/100)*10/10; /* %70 */
    speed = 80*(0xffff/100);
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
//    speed = ((int32_t)config->maxSpeedPercent)*(0xffff/100)*10/10; /* %100 */
    speed = 100*(0xffff/100);
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
#endif
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
      CLS1_StdIO_OutErr_FctType ioOut = SHELL_GetStdio()->stdOut;
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
#endif //PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE

#endif /* PL_HAS_LINE_SENSOR */

#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
void PID_Line(uint16_t currLinePos, uint16_t setLinePos, uint16_t currLineWidth, bool forward) {
#if PL_HAS_LINE_PID
#if PL_GO_DEADEND_BW
  if (forward) {
    PID_LineCfg(currLinePos, setLinePos, forward, &lineFwConfig);
  } else {
    PID_LineCfg(currLinePos, setLinePos, forward, &lineBwConfig);
  }
#else
  (void)forward; /* not used */
  PID_LineCfg(currLinePos, setLinePos, currLineWidth, forward, &lineFwConfig);
#endif
#endif
}
#endif

#if PL_HAS_POS_PID
static void PID_PosCfg(int32_t currPos, int32_t setPos, bool isLeft, PID_Config *config) {
  int32_t speed;
  MOT_Direction direction=MOT_DIR_FORWARD;
  MOT_MotorDevice *motHandle;

#if PL_HAS_HIGH_RES_ENCODER
  int error;

  error = setPos-currPos;
  if (error>-10 && error<10) { /* avoid jitter around zero */
    setPos = currPos;
  }
#endif
  speed = PID(currPos, setPos, config);
  /* transform into motor speed */
  speed *= 1000; /* scale PID, otherwise we need high PID constants */
  if (speed>=0) {
    direction = MOT_DIR_FORWARD;
  } else { /* negative, make it positive */
    speed = -speed; /* make positive */
    direction = MOT_DIR_BACKWARD;
  }
  /* speed is now always positive, make sure it is within 16bit PWM boundary */
  if (speed>0xFFFF) {
    speed = 0xFFFF;
  }
  /* limit speed to maximum value */
  speed = (speed*config->maxSpeedPercent)/100;
  /* send new speed values to motor */
  if (isLeft) {
    motHandle = MOT_GetMotorHandle(MOT_MOTOR_LEFT);
  } else {
    motHandle = MOT_GetMotorHandle(MOT_MOTOR_RIGHT);
  }
  MOT_SetVal(motHandle, 0xFFFF-speed); /* PWM is low active */
  MOT_SetDirection(motHandle, direction);
  MOT_UpdatePercent(motHandle, direction);
}

void PID_Pos(int32_t currPos, int32_t setPos, bool isLeft) {
  if (isLeft) {
    PID_PosCfg(currPos, setPos, isLeft, &posLeftConfig);
  } else {
    PID_PosCfg(currPos, setPos, isLeft, &posRightConfig);
  }
}
#endif /* PL_HAS_POS_PID */

#if PL_HAS_SPEED_PID
static void PID_SpeedCfg(int32_t currSpeed, int32_t setSpeed, bool isLeft, PID_Config *config) {
  int32_t speed;
  MOT_Direction direction=MOT_DIR_FORWARD;
  MOT_MotorDevice *motHandle;
  
  if (setSpeed==0) { /* \todo Actually this test is more of a hack, should not be needed! */
    speed = 0;
    PID_Start(); /* reset PID, especially integral counters */
  } else {
    speed = PID(currSpeed, setSpeed, config);
  }
  if (speed>=0) {
    direction = MOT_DIR_FORWARD;
  } else { /* negative, make it positive */
    speed = -speed; /* make positive */
    direction = MOT_DIR_BACKWARD;
  }
  /* speed shall be positive here, make sure it is within 16bit PWM boundary */
  if (speed>0xFFFF) {
    speed = 0xFFFF;
  }
  /* send new speed values to motor */
  if (isLeft) {
    motHandle = MOT_GetMotorHandle(MOT_MOTOR_LEFT);
  } else {
    motHandle = MOT_GetMotorHandle(MOT_MOTOR_RIGHT);
  }
  MOT_SetVal(motHandle, 0xFFFF-speed); /* PWM is low active */
  MOT_SetDirection(motHandle, direction);
  MOT_UpdatePercent(motHandle, direction);
}

void PID_Speed(int32_t currSpeed, int32_t setSpeed, bool isLeft) {
  if (isLeft) {
    PID_SpeedCfg(currSpeed, setSpeed, isLeft, &speedLeftConfig);
  } else {
    PID_SpeedCfg(currSpeed, setSpeed, isLeft, &speedRightConfig);
  }
}
#endif /* PL_HAS_SPEED_PID */

#if PL_CONFIG_HAS_SHELL
static void PID_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"pid", (unsigned char*)"Group of PID commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows PID help or status\r\n", io->stdOut);
#if PL_HAS_POS_PID
  CLS1_SendHelpStr((unsigned char*)"  pos (p|i|d|w) <value>", (unsigned char*)"Sets P, I, D or anti-Windup position value\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  pos speed <value>", (unsigned char*)"Maximum speed % value\r\n", io->stdOut);
#endif
#if PL_HAS_SPEED_PID
  CLS1_SendHelpStr((unsigned char*)"  speed (L|R) (p|i|d|w) <value>", (unsigned char*)"Sets P, I, D or anti-Windup position value\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  speed (L|R) speed <value>", (unsigned char*)"Maximum speed % value\r\n", io->stdOut);
#endif
#if PL_HAS_LINE_PID
  CLS1_SendHelpStr((unsigned char*)"  fw (p|i|d|w) <value>", (unsigned char*)"Sets P, I, D or anti-Windup line value\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  fw speed <value>", (unsigned char*)"Maximum speed % value\r\n", io->stdOut);
#endif
#if PL_GO_DEADEND_BW
  CLS1_SendHelpStr((unsigned char*)"  bw (p|i|d|w) <value>", (unsigned char*)"Sets P, I, D or anti-Windup backward value\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  bw speed <value>", (unsigned char*)"Maximum backward speed % value\r\n", io->stdOut);
#endif
}

#if PL_HAS_SPEED_PID || PL_HAS_POS_PID || PL_HAS_LINE_PID
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
  UTIL1_strcat(kindBuf, sizeof(buf), (unsigned char*)" error");
  UTIL1_Num32sToStr(buf, sizeof(buf), config->lastError);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr(kindBuf, buf, io->stdOut);

  UTIL1_strcpy(kindBuf, sizeof(buf), (unsigned char*)"  ");
  UTIL1_strcat(kindBuf, sizeof(buf), kindStr);
  UTIL1_strcat(kindBuf, sizeof(buf), (unsigned char*)" integral");
  UTIL1_Num32sToStr(buf, sizeof(buf), config->integral);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr(kindBuf, buf, io->stdOut);

  UTIL1_strcpy(kindBuf, sizeof(buf), (unsigned char*)"  ");
  UTIL1_strcat(kindBuf, sizeof(buf), kindStr);
  UTIL1_strcat(kindBuf, sizeof(buf), (unsigned char*)" speed");
  UTIL1_Num8uToStr(buf, sizeof(buf), config->maxSpeedPercent);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"%\r\n");
  CLS1_SendStatusStr(kindBuf, buf, io->stdOut);
}
#endif

static void PID_PrintStatus(const CLS1_StdIOType *io) {
#if PL_HAS_LINE_PID || PL_GO_DEADEND_BW || PL_HAS_POS_PID || PL_HAS_SPEED_PID
  CLS1_SendStatusStr((unsigned char*)"pid", (unsigned char*)"\r\n", io->stdOut);
#endif
#if PL_HAS_LINE_PID
  PrintPIDstatus(&lineFwConfig, (unsigned char*)"fw", io);
#endif
#if PL_GO_DEADEND_BW
  PrintPIDstatus(&lineBwConfig, (unsigned char*)"bw", io);
#endif
#if PL_HAS_POS_PID
  PrintPIDstatus(&posLeftConfig, (unsigned char*)"pos L", io);
  PrintPIDstatus(&posRightConfig, (unsigned char*)"pos R", io);
#endif  
#if PL_HAS_SPEED_PID
  PrintPIDstatus(&speedLeftConfig, (unsigned char*)"speed L", io);
  PrintPIDstatus(&speedRightConfig, (unsigned char*)"speed R", io);
#endif  
}

#if PL_HAS_SPEED_PID || PL_HAS_POS_PID || PL_HAS_LINE_PID
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
#endif

uint8_t PID_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"pid help")==0) {
    PID_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"pid status")==0) {
    PID_PrintStatus(io);
    *handled = TRUE;
#if PL_HAS_LINE_PID
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid fw ", sizeof("pid fw ")-1)==0) {
    res = ParsePidParameter(&lineFwConfig, cmd+sizeof("pid fw ")-1, handled, io);
#endif
#if PL_GO_DEADEND_BW
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid bw ", sizeof("pid bw ")-1)==0) {
    res = ParsePidParameter(&lineBwConfig, cmd+sizeof("pid bw ")-1, handled, io);
#endif
#if PL_HAS_POS_PID
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid pos ", sizeof("pid pos ")-1)==0) {
    res = ParsePidParameter(&posLeftConfig, cmd+sizeof("pid pos ")-1, handled, io);
    if (res==ERR_OK) {
      res = ParsePidParameter(&posRightConfig, cmd+sizeof("pid pos ")-1, handled, io);
    }
#endif
#if PL_HAS_SPEED_PID
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid speed L ", sizeof("pid speed L ")-1)==0) {
    res = ParsePidParameter(&speedLeftConfig, cmd+sizeof("pid speed L ")-1, handled, io);
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid speed R ", sizeof("pid speed R ")-1)==0) {
    res = ParsePidParameter(&speedRightConfig, cmd+sizeof("pid speed R ")-1, handled, io);
#endif
  }
  return res;
}
#endif /* PL_CONFIG_HAS_SHELL */

void PID_Start(void) {
#if PL_HAS_LINE_PID
  lineFwConfig.lastError = 0;
  lineFwConfig.integral = 0;
#endif
#if PL_GO_DEADEND_BW
  lineBwConfig.lastError = 0;
  lineBwConfig.integral = 0;
#endif
#if PL_HAS_POS_PID
  posLeftConfig.lastError = 0;
  posLeftConfig.integral = 0;
  posRightConfig.lastError = 0;
  posRightConfig.integral = 0;
#endif
#if PL_HAS_SPEED_PID
  speedLeftConfig.lastError = 0;
  speedLeftConfig.integral = 0;
  speedRightConfig.lastError = 0;
  speedRightConfig.integral = 0;
#endif
}

void PID_Deinit(void) {
}

void PID_Init(void) {
#if PL_HAS_LINE_PID
#if PL_IS_ZUMO_ROBOT && PL_IS_MOTOR_1_100
  lineFwConfig.pFactor100 = 5500;
  lineFwConfig.iFactor100 = 15;
  lineFwConfig.dFactor100 = 100;
  lineFwConfig.iAntiWindup = 100000;
  lineFwConfig.maxSpeedPercent = 100;
  lineFwConfig.lastError = 0;
  lineFwConfig.integral = 0;
#elif PL_IS_ZUMO_ROBOT
  lineFwConfig.pFactor100 = 5500;
  lineFwConfig.iFactor100 = 15;
  lineFwConfig.dFactor100 = 100;
  lineFwConfig.iAntiWindup = 100000;
  lineFwConfig.maxSpeedPercent = 60;
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
#elif PL_IS_INTRO_ZUMO_ROBOT
  lineFwConfig.pFactor100 = 5500;
  lineFwConfig.iFactor100 = 15;
  lineFwConfig.dFactor100 = 100;
  lineFwConfig.iAntiWindup = 100000;
  lineFwConfig.maxSpeedPercent = 15;
  lineFwConfig.lastError = 0;
  lineFwConfig.integral = 0;
#elif PL_IS_INTRO_ZUMO_K22 && PL_HAS_LIPO
  lineFwConfig.pFactor100 = 2000;
  lineFwConfig.iFactor100 = 15;
  lineFwConfig.dFactor100 = 100;
  lineFwConfig.iAntiWindup = 100000;
  lineFwConfig.maxSpeedPercent = 15;
  lineFwConfig.lastError = 0;
  lineFwConfig.integral = 0;
#elif PL_IS_INTRO_ZUMO_ROBOT2 || PL_IS_INTRO_ZUMO_K22
  lineFwConfig.pFactor100 = 5500;
  lineFwConfig.iFactor100 = 15;
  lineFwConfig.dFactor100 = 100;
  lineFwConfig.iAntiWindup = 100000;
  lineFwConfig.maxSpeedPercent = 50;
  lineFwConfig.lastError = 0;
  lineFwConfig.integral = 0;
#else
  #error "unknown configuration!"
#endif
#if PL_GO_DEADEND_BW
  lineBwConfig.param = 0;
  lineBwConfig.pFactor100 = 1000;
  lineBwConfig.iFactor100 = 0;
  lineBwConfig.dFactor100 = 0;
  lineBwConfig.iAntiWindup = 100000;
  lineBwConfig.maxSpeedPercent = 20;
  lineBwConfig.lastError = 0;
  lineBwConfig.integral = 0;
#endif
#endif /* PL_HAS_LINE_PID */  
  
#if PL_HAS_POS_PID
#if PL_DO_SUMO && PL_SLOWER_SPEED
  posLeftConfig.pFactor100 = 1000;
  posLeftConfig.iFactor100 = 1;
  posLeftConfig.dFactor100 = 50;
  posLeftConfig.iAntiWindup = 200;
  posLeftConfig.maxSpeedPercent = 30;
#elif PL_DO_SUMO /* sumo, high speed */
  posLeftConfig.pFactor100 = 1000;
  posLeftConfig.iFactor100 = 1;
  posLeftConfig.dFactor100 = 50;
  posLeftConfig.iAntiWindup = 200;
  posLeftConfig.maxSpeedPercent = 100;
#elif (PL_DO_LINE_FOLLOWING || PL_DO_LINE_MAZE) && PL_SLOWER_SPEED /* line/maze, high speed */
  posLeftConfig.pFactor100 = 1500;
  posLeftConfig.iFactor100 = 2;
  posLeftConfig.dFactor100 = 50;
  posLeftConfig.iAntiWindup = 200;
  posLeftConfig.maxSpeedPercent = 40;
#elif (PL_DO_LINE_FOLLOWING || PL_DO_LINE_MAZE) /* line/maze, high speed */
  posLeftConfig.pFactor100 = 1000;
  posLeftConfig.iFactor100 = 2;
  posLeftConfig.dFactor100 = 50;
  posLeftConfig.iAntiWindup = 200;
  posLeftConfig.maxSpeedPercent = 40;
#else
  #error "check configuration"
#endif
  posLeftConfig.lastError = 0;
  posLeftConfig.integral = 0;
  posRightConfig.pFactor100 = posLeftConfig.pFactor100;
  posRightConfig.iFactor100 = posLeftConfig.iFactor100;
  posRightConfig.dFactor100 = posLeftConfig.dFactor100;
  posRightConfig.iAntiWindup = posLeftConfig.iAntiWindup;
  posRightConfig.maxSpeedPercent = posLeftConfig.maxSpeedPercent;
  posRightConfig.lastError = posLeftConfig.lastError;
  posRightConfig.integral = posLeftConfig.integral;
#endif
#if PL_HAS_SPEED_PID
#if PL_IS_INTRO_ZUMO_K22
  speedLeftConfig.pFactor100 = 2000;
  speedLeftConfig.iFactor100 = 80;
  speedLeftConfig.dFactor100 = 0;
  speedLeftConfig.iAntiWindup = 120000;
  #if PL_SLOWER_SPEED
  speedLeftConfig.maxSpeedPercent = 50;
  #else
  speedLeftConfig.maxSpeedPercent = 100;
  #endif
#else
  speedLeftConfig.pFactor100 = 15000;
  speedLeftConfig.iFactor100 = 500;
  speedLeftConfig.dFactor100 = 100;
  speedLeftConfig.iAntiWindup = 15000;
  #if PL_SLOWER_SPEED
  speedLeftConfig.maxSpeedPercent = 30;
  #else
  speedLeftConfig.maxSpeedPercent = 50;
  #endif
#endif
  speedLeftConfig.lastError = 0;
  speedLeftConfig.integral = 0;
  speedRightConfig.pFactor100 = speedLeftConfig.pFactor100;
  speedRightConfig.iFactor100 = speedLeftConfig.iFactor100;
  speedRightConfig.dFactor100 = speedLeftConfig.dFactor100;
  speedRightConfig.iAntiWindup = speedLeftConfig.iAntiWindup;
  speedRightConfig.maxSpeedPercent = speedLeftConfig.maxSpeedPercent;
  speedRightConfig.lastError = speedLeftConfig.lastError;
  speedRightConfig.integral = speedLeftConfig.integral;
#endif
}
#endif /* PL_HAS_PID */

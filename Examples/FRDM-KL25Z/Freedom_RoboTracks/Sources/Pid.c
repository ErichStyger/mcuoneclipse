
#include "Platform.h"
#include "Pid.h"
#include "Motor.h"
#include "UTIL1.h"
#include "CLS1.h"
#include "Reflectance.h"

#define PID_DEBUG 0 /* careful: this will slow down the PID loop frequency! */

#if PL_IS_ZUMO_ROBOT
  static int32_t pLineFactor100 = 5000;
  static int32_t iLineFactor100 = 10;
  static int32_t dLineFactor100 = 100;
  static int32_t iLineAntiWindup = 100000;
  static uint8_t maxLineSpeedPercent = 30; /* max speed if 100% on the line, 0xffff would be full speed */
#else
  static int32_t pLineFactor100 = 200;
  static int32_t iLineFactor100 = 1;
  static int32_t dLineFactor100 = 50000;
  static int32_t iLineAntiWindup = 20000;
  static uint8_t maxLineSpeedPercent = 15; /* max speed if 100% on the line, 0xffff would be full speed */
#endif
#if PL_HAS_LINE_SENSOR
static int32_t lastLineError=0, integralLine=0;
#endif

#if PL_HAS_QUADRATURE
  static int32_t pPosFactor100 = 3000;
  static int32_t iPosFactor100 = 1;
  static int32_t dPosFactor100 = 20000;
  static int32_t iPosAntiWindup = 50;
  static uint8_t maxPosSpeedPercent = 15; /* max speed if 100% on the line, 0xffff would be full speed */
  static int32_t lastPosError=0, integralPos=0;
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
  
void PID_Line(uint16_t currLine, uint16_t setLine) {
  int32_t error;
  int32_t pid, speed, speedL, speedR;
#if PID_DEBUG
  unsigned char buf[16];
  static uint8_t cnt = 0;
#endif
  uint8_t errorPercent;
  MOT_Direction directionL=MOT_DIR_FORWARD, directionR=MOT_DIR_FORWARD;
  
  /* perform PID closed control loop calculation */
  error = currLine-setLine; /* calculate error */
  errorPercent = errorWithinPercent(error);
  pid = (error*pLineFactor100)/100; /* P part */
  integralLine += error; /* integrate error */
  if (integralLine>iLineAntiWindup) {
    integralLine = iLineAntiWindup;
  } else if (integralLine<-iLineAntiWindup) {
    integralLine = -iLineAntiWindup;
  }
  pid += (integralLine*iLineFactor100)/100; /* add I part */
  pid += ((error-lastLineError)*dLineFactor100)/100; /* add D part */
  lastLineError = error; /* remember for next iteration of D part */
  
  /* transform into different speed for motors. The PID is used as difference value to the motor PWM */
  if (errorPercent <= 20) { /* pretty on center: move forward both motors with base speed */
    speed = ((int32_t)maxLineSpeedPercent)*(0xffff/100); /* 100% */
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
    speed = ((int32_t)maxLineSpeedPercent)*(0xffff/100)*8/10; /* 80% */
    pid = Limit(pid, -speed, speed);
    if (pid<0) { /* turn right */
      speedR = speed+pid; /* decrease speed */
      speedL = speed-pid; /* increase speed */
    } else { /* turn left */
      speedR = speed+pid; /* increase speed */
      speedL = speed-pid; /* decrease speed */
    }
  } else if (errorPercent <= 70) { 
    speed = ((int32_t)maxLineSpeedPercent)*(0xffff/100)*6/10; /* %60 */
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
    speed = ((int32_t)maxLineSpeedPercent)*(0xffff/100)*10/10; /* %80 */
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

#if PL_HAS_QUADRATURE
void PID_Pos(int16_t currPos, int16_t setPos, bool isLeft) {
  int32_t error;
  int32_t pid, speed;
  MOT_Direction direction=MOT_DIR_FORWARD;
  
  /* perform PID closed control loop calculation */
  error = currPos-setPos; /* calculate error */
  pid = (error*pPosFactor100)/100; /* P part */
  integralPos += error; /* integrate error */
  if (integralPos>iPosAntiWindup) {
    integralPos = iPosAntiWindup;
  } else if (integralPos<-iPosAntiWindup) {
    integralPos = -iPosAntiWindup;
  }
  pid += (integralPos*iPosFactor100)/100; /* add I part */
  pid += ((error-lastPosError)*dPosFactor100)/100; /* add D part */
  lastPosError = error; /* remember for next iteration of D part */
  
  /* transform into motor speed */
  speed = ((int32_t)maxPosSpeedPercent)*(0xffff/100); /* limit the speed */
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
#endif

static void PID_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"pid", (unsigned char*)"Group of PID commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows PID help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  line (p|d|i|w) <value>", (unsigned char*)"Sets P, D, I or anti-windup line value\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  line speed <value>", (unsigned char*)"Maximum speed value\r\n", io->stdOut);
#if PL_HAS_QUADRATURE
  CLS1_SendHelpStr((unsigned char*)"  pos (p|d|i|w) <value>", (unsigned char*)"Sets P, D, I or anti-windup position value\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  pos speed <value>", (unsigned char*)"Maximum speed value\r\n", io->stdOut);
#endif
}

static void PID_PrintStatus(const CLS1_StdIOType *io) {
  unsigned char buf[48];

  CLS1_SendStatusStr((unsigned char*)"pid", (unsigned char*)"\r\n", io->stdOut);

  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"p: ");
  UTIL1_strcatNum32s(buf, sizeof(buf), pLineFactor100);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" i: ");
  UTIL1_strcatNum32s(buf, sizeof(buf), iLineFactor100);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" d: ");
  UTIL1_strcatNum32s(buf, sizeof(buf), dLineFactor100);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  line PID", buf, io->stdOut);

  UTIL1_Num32sToStr(buf, sizeof(buf), iLineAntiWindup);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  line windup", buf, io->stdOut);

  UTIL1_Num8uToStr(buf, sizeof(buf), maxLineSpeedPercent);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"%\r\n");
  CLS1_SendStatusStr((unsigned char*)"  line speed", buf, io->stdOut);

#if PL_HAS_QUADRATURE
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"p: ");
  UTIL1_strcatNum32s(buf, sizeof(buf), pPosFactor100);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" i: ");
  UTIL1_strcatNum32s(buf, sizeof(buf), iPosFactor100);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" d: ");
  UTIL1_strcatNum32s(buf, sizeof(buf), dPosFactor100);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  pos PID", buf, io->stdOut);
  
  UTIL1_Num32sToStr(buf, sizeof(buf), iPosAntiWindup);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  pos windup", buf, io->stdOut);

  UTIL1_Num8uToStr(buf, sizeof(buf), maxPosSpeedPercent);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"%\r\n");
  CLS1_SendStatusStr((unsigned char*)"  pos speed", buf, io->stdOut);
#endif  
}

uint8_t PID_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  const unsigned char *p;
  uint32_t val32u;
  uint8_t val8u;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"pid help")==0) {
    PID_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"pid status")==0) {
    PID_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid line p ", sizeof("pid line p ")-1)==0) {
    p = cmd+sizeof("pid line p");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      pLineFactor100 = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid line i ", sizeof("pid line i ")-1)==0) {
    p = cmd+sizeof("pid line i");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      iLineFactor100 = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid line d ", sizeof("pid line d ")-1)==0) {
    p = cmd+sizeof("pid line d");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      dLineFactor100 = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid line w ", sizeof("pid line w ")-1)==0) {
    p = cmd+sizeof("pid line w");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      iLineAntiWindup = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid line speed ", sizeof("pid line speed ")-1)==0) {
    p = cmd+sizeof("pid line speed");
    if (UTIL1_ScanDecimal8uNumber(&p, &val8u)==ERR_OK && val8u<=100) {
      maxLineSpeedPercent = val8u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
#if PL_HAS_QUADRATURE
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid pos p ", sizeof("pid pos p ")-1)==0) {
    p = cmd+sizeof("pid pos p");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      pPosFactor100 = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid pos i ", sizeof("pid pos i ")-1)==0) {
    p = cmd+sizeof("pid pos i");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      iPosFactor100 = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid pos d ", sizeof("pid pos d ")-1)==0) {
    p = cmd+sizeof("pid pos d");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      dPosFactor100 = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid pos w ", sizeof("pid pos w ")-1)==0) {
    p = cmd+sizeof("pid pos w");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      iPosAntiWindup = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid pos speed ", sizeof("pid pos speed ")-1)==0) {
    p = cmd+sizeof("pid pos speed");
    if (UTIL1_ScanDecimal8uNumber(&p, &val8u)==ERR_OK && val8u<=100) {
      maxPosSpeedPercent = val8u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
#endif
  }
  return res;
}

void PID_Init(void) {
#if PL_HAS_LINE_SENSOR
  integralLine = 0;
#endif
#if PL_HAS_QUADRATURE
  integralPos = 0;
#endif
}

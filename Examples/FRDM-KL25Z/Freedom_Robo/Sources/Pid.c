
#include "Platform.h"
#include "Pid.h"
#include "Motor.h"
#include "UTIL1.h"
#include "CLS1.h"
#include "Reflectance.h"

#define PID_DEBUG 0 /* careful: this will slow down the PID loop frequency! */

#if PL_IS_ZUMO_ROBOT
  static int32_t pFactor100 = 5000;
  static int32_t iFactor100 = 10;
  static int32_t dFactor100 = 100;
  static int32_t iAntiWindup = 100000;
  static uint8_t maxSpeedPercent = 30; /* max speed if 100% on the line, 0xffff would be full speed */
#else
  static int32_t pFactor100 = 200;
  static int32_t iFactor100 = 1;
  static int32_t dFactor100 = 50000;
  static int32_t iAntiWindup = 20000;
  static uint8_t maxSpeedPercent = 20; /* max speed if 100% on the line, 0xffff would be full speed */
#endif

static int32_t Limit(int32_t val, int32_t minVal, int32_t maxVal) {
  if (val<minVal) {
    return minVal;
  } else if (val>maxVal) {
    return maxVal;
  }
  return val;
}

static MOT_Direction AbsSpeed(int32_t *speedP) {
  if (*speedP<0) {
    *speedP = -(*speedP);
    return MOT_DIR_BACKWARD;
  }
  return MOT_DIR_FORWARD;
}

/*! \brief returns error (always positive) percent */
static uint8_t errorWithinPercent(int32_t error) {
  if (error<0) {
    error = -error;
  }
  return error/(REF_MAX_LINE_VALUE/2/100);
}
  
static int32_t lastError=0, integral=0;

void PID_Process(uint16_t currLine, uint16_t setLine) {
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
  pid = (error*pFactor100)/100; /* P part */
  integral += error; /* integrate error */
  if (integral>iAntiWindup) {
    integral = iAntiWindup;
  } else if (integral<-iAntiWindup) {
    integral = -iAntiWindup;
  }
  pid += (integral*iFactor100)/100; /* add I part */
  pid += ((error-lastError)*dFactor100)/100; /* add D part */
  lastError = error; /* remember for next iteration of D part */
  
  /* transform into different speed for motors. The PID is used as difference value to the motor PWM */
  if (errorPercent <= 20) { /* pretty on center: move forward both motors with base speed */
    speed = ((int32_t)maxSpeedPercent)*(0xffff/100); /* 100% */
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
    speed = ((int32_t)maxSpeedPercent)*(0xffff/100)*8/10; /* 80% */
    pid = Limit(pid, -speed, speed);
    if (pid<0) { /* turn right */
      speedR = speed+pid; /* decrease speed */
      speedL = speed-pid; /* increase speed */
    } else { /* turn left */
      speedR = speed+pid; /* increase speed */
      speedL = speed-pid; /* decrease speed */
    }
  } else if (errorPercent <= 70) { 
    speed = ((int32_t)maxSpeedPercent)*(0xffff/100)*6/10; /* %60 */
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
    speed = ((int32_t)maxSpeedPercent)*(0xffff/100)*10/10; /* %80 */
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
  /* send new speed values to motor, */
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

static void PID_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"pid", (unsigned char*)"Group of PID commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows PID help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  (p|d|i|w) <value>", (unsigned char*)"Sets P, D, I or anti-windup value\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  speed <value>", (unsigned char*)"Maximum speed value\r\n", io->stdOut);
}

static void PID_PrintStatus(const CLS1_StdIOType *io) {
  unsigned char buf[48];

  CLS1_SendStatusStr((unsigned char*)"pid", (unsigned char*)"\r\n", io->stdOut);
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"p0.001: ");
  UTIL1_strcatNum32s(buf, sizeof(buf), pFactor100);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" i0.001: ");
  UTIL1_strcatNum32s(buf, sizeof(buf), iFactor100);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" d0.001: ");
  UTIL1_strcatNum32s(buf, sizeof(buf), dFactor100);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  PID", buf, io->stdOut);

  buf[0]='\0';
  UTIL1_strcatNum32s(buf, sizeof(buf), iAntiWindup);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  anti-windup", buf, io->stdOut);

  buf[0]='\0';
  UTIL1_strcatNum8u(buf, sizeof(buf), maxSpeedPercent);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"%\r\n");
  CLS1_SendStatusStr((unsigned char*)"  max speed", buf, io->stdOut);
}

uint8_t PID_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  const unsigned char *p;
  uint32_t val32u;
  uint8_t val8u;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"line help")==0) {
    PID_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"line status")==0) {
    PID_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid p ", sizeof("pid p ")-1)==0) {
    p = cmd+sizeof("pid p");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      pFactor100 = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid i ", sizeof("pid i ")-1)==0) {
    p = cmd+sizeof("pid i");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      iFactor100 = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid d ", sizeof("pid d ")-1)==0) {
    p = cmd+sizeof("pid d");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      dFactor100 = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid w ", sizeof("pid w ")-1)==0) {
    p = cmd+sizeof("pid w");
    if (UTIL1_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      iAntiWindup = val32u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"pid speed ", sizeof("pid speed ")-1)==0) {
    p = cmd+sizeof("pid speed");
    if (UTIL1_ScanDecimal8uNumber(&p, &val8u)==ERR_OK && val8u<=100) {
      maxSpeedPercent = val8u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  }
  return res;
}

void PID_Init(void) {
  integral = 0;
}

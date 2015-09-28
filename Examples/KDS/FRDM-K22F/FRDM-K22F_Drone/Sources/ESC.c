/*
 * ESC.c
 *
 *  Created on: 20.09.2015
 *      Author: tastyger
 */

#include "Platform.h"
#if PL_HAS_ESC
#include "ESC.h"
#include "PWMFR.h"
#if PL_HAS_SHELL
  #include "CLS1.h"
  #include "UTIL1.h"
#endif

typedef uint8_t ESC_SpeedPercent; /* 0%...+100%, where negative is backward */
#define ESC_MIN_DUTY_MS  1000  /* default minimum duty in us */
#define ESC_MAX_DUTY_MS  2000  /* default maximum duty in us */

typedef struct ESC_MotorDevice_ {
  ESC_SpeedPercent currSpeedPercent; /* our current speed in %, negative percent means backward */
  uint16_t currPWMvalue; /* current PWM value used */
  uint16_t us; /* current duty in us */
  uint8_t (*SetRatio16)(uint16_t); /* function to set the ratio */
  uint8_t (*SetDutyUS)(uint16_t); /* function to set the duty us */
} ESC_MotorDevice;

typedef enum {
  ESC_MOTOR_FRONT_LEFT,
  ESC_MOTOR_FRONT_RIGHT,
  ESC_MOTOR_BACK_RIGHT,
  ESC_MOTOR_BACK_LEFT,
  ESC_MOTOR_NOF /* 4 */
} ESC_MotorID;

static ESC_MotorDevice ESC_motors[ESC_MOTOR_NOF]; /* motor front right */
static bool ESC_isMotorOn = TRUE;

ESC_MotorDevice *MOT_GetMotorHandle(ESC_MotorID motor) {
  return &ESC_motors[motor];
}

static uint8_t ESC_SetRatio16_FR(uint16_t ratio) {
  return PWMFR_SetRatio16(ratio);
}

static uint8_t ESC_SetDutyUS_FR(uint16_t us) {
  return PWMFR_SetDutyUS(us);
}

void ESC_SetVal(ESC_MotorDevice *motor, uint16_t val) {
  if (ESC_isMotorOn) {
    motor->currPWMvalue = val;
    motor->SetRatio16(val);
  } else { /* have motor stopped */
    motor->currPWMvalue = 0xFFFF;
    motor->SetRatio16(0xFFFF);
  }
}

uint16_t ESC_GetVal(ESC_MotorDevice *motor) {
  return motor->currPWMvalue;
}

void ESC_SetSpeedPercent(ESC_MotorDevice *motor, ESC_SpeedPercent percent) {
  uint32_t val;

  motor->currSpeedPercent = percent; /* store current value */
  if (percent>100) { /* make sure we are within 0..100 */
    percent = 100;
  }
  val = ((100-percent)*0xffff)/100;
  ESC_SetVal(motor, (uint16_t)val);
}

void ESC_UpdatePercent(ESC_MotorDevice *motor) {
  motor->currSpeedPercent = ((0xffff-motor->currPWMvalue)*100)/0xffff;
}

void ESC_ChangeSpeedPercent(ESC_MotorDevice *motor, ESC_SpeedPercent relPercent) {
  relPercent += motor->currSpeedPercent; /* make absolute number */
  if (relPercent>100) { /* check for overflow */
    relPercent = 100;
  } else if (relPercent<-100) { /* and underflow */
    relPercent = -100;
  }
  ESC_SetSpeedPercent(motor, relPercent);  /* set speed. This will care about the direction too */
}

uint8_t ESC_SetDutyMs(ESC_MotorDevice *motor, uint16_t us) {
  motor->us = us; /* store current value */
  return PWMFR_SetDutyUS(us);
}

#if PL_HAS_SHELL
static void ESC_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"esc", (unsigned char*)"Group of esc commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows motor help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  duty <motor> <number>", (unsigned char*)"Change <motor> (fl|fr|bl|br) duty (0..+100)%\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  us <motor> <number>", (unsigned char*)"Change <motor> (fl|fr|bl|br) duty time (500..1500us)%\r\n", io->stdOut);
}

static void ESC_PrintESCStatus(ESC_MotorID id, const CLS1_StdIOType *io) {
  unsigned char buf[48];
  const unsigned char *motorStr;

  if (id==ESC_MOTOR_FRONT_RIGHT) {
    motorStr = "  fr";
  } else if (id==ESC_MOTOR_FRONT_LEFT) {
    motorStr = "  fl";
  } else if (id==ESC_MOTOR_BACK_LEFT) {
    motorStr = "  bl";
  } else if (id==ESC_MOTOR_BACK_RIGHT) {
    motorStr = "  br";
  } else {
    motorStr = "  ??";
  }

  CLS1_SendStatusStr(motorStr, (unsigned char*)"", io->stdOut);
  buf[0] = '\0';
  UTIL1_Num16sToStrFormatted(buf, sizeof(buf), (int16_t)ESC_motors[id].currSpeedPercent, ' ', 4);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"% 0x");
  UTIL1_strcatNum16Hex(buf, sizeof(buf), ESC_motors[id].currPWMvalue);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)", ");
  UTIL1_strcatNum16u(buf, sizeof(buf), ESC_motors[id].us);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" us\r\n");
  CLS1_SendStr(buf, io->stdOut);
}

static void ESC_PrintStatus(const CLS1_StdIOType *io) {

  CLS1_SendStatusStr((unsigned char*)"esc", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  on/off", ESC_isMotorOn?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  ESC_PrintESCStatus(ESC_MOTOR_FRONT_LEFT, io);
  ESC_PrintESCStatus(ESC_MOTOR_FRONT_RIGHT, io);
  ESC_PrintESCStatus(ESC_MOTOR_BACK_LEFT, io);
  ESC_PrintESCStatus(ESC_MOTOR_BACK_RIGHT, io);
}

uint8_t ESC_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  int32_t val;
  const unsigned char *p;
  ESC_MotorID id;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"esc help")==0) {
    ESC_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"esc status")==0) {
    ESC_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, (char*)"esc on", sizeof("esc on")-1)==0) {
    ESC_isMotorOn = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, (char*)"esc off", sizeof("esc off")-1)==0) {
    for(id=0; id<ESC_MOTOR_NOF; id++) {
      ESC_SetSpeedPercent(&ESC_motors[id], 0);
    }
    ESC_isMotorOn = FALSE;
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, (char*)"esc duty ", sizeof("esc duty ")-1)==0) {
    if (!ESC_isMotorOn) {
      CLS1_SendStr((unsigned char*)"Motors are OFF, cannot set duty.\r\n", io->stdErr);
      res = ERR_FAILED;
    } else {
      p = cmd+sizeof("esc duty ")-1;
      if (UTIL1_strncmp((char*)p, (char*)"fl ", sizeof("fl ")-1)==0) {
        id = ESC_MOTOR_FRONT_LEFT;
      } else if (UTIL1_strncmp((char*)p, (char*)"fr ", sizeof("fr ")-1)==0) {
        id = ESC_MOTOR_FRONT_RIGHT;
      } else if (UTIL1_strncmp((char*)p, (char*)"bl ", sizeof("bl ")-1)==0) {
        id = ESC_MOTOR_BACK_LEFT;
      } else if (UTIL1_strncmp((char*)p, (char*)"br ", sizeof("br ")-1)==0) {
        id = ESC_MOTOR_BACK_RIGHT;
      } else {
        CLS1_SendStr((unsigned char*)"Wrong argument, motor must be either fl, fr, bl or br\r\n", io->stdErr);
        res = ERR_FAILED;
      }
      if (res==ERR_OK) {
        p = cmd+sizeof("esc duty xx ")-1;
        if (UTIL1_xatoi(&p, &val)==ERR_OK && val >=0 && val<=100) {
          ESC_SetSpeedPercent(&ESC_motors[id], (ESC_SpeedPercent)val);
          *handled = TRUE;
        } else {
          CLS1_SendStr((unsigned char*)"Wrong argument, must be in the range 0..100\r\n", io->stdErr);
          res = ERR_FAILED;
        }
      }
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"esc us ", sizeof("esc us ")-1)==0) {
    if (!ESC_isMotorOn) {
      CLS1_SendStr((unsigned char*)"Motors are OFF, cannot set ms duty.\r\n", io->stdErr);
      res = ERR_FAILED;
    } else {
      p = cmd+sizeof("esc us ")-1;
      if (UTIL1_strncmp((char*)p, (char*)"fl ", sizeof("fl ")-1)==0) {
        id = ESC_MOTOR_FRONT_LEFT;
      } else if (UTIL1_strncmp((char*)p, (char*)"fr ", sizeof("fr ")-1)==0) {
        id = ESC_MOTOR_FRONT_RIGHT;
      } else if (UTIL1_strncmp((char*)p, (char*)"bl ", sizeof("bl ")-1)==0) {
        id = ESC_MOTOR_BACK_LEFT;
      } else if (UTIL1_strncmp((char*)p, (char*)"br ", sizeof("br ")-1)==0) {
        id = ESC_MOTOR_BACK_RIGHT;
      } else {
        CLS1_SendStr((unsigned char*)"Wrong argument, motor must be either fl, fr, bl or br\r\n", io->stdErr);
        res = ERR_FAILED;
      }
      if (res==ERR_OK) {
        p = cmd+sizeof("esc us xx ")-1;
        if (UTIL1_xatoi(&p, &val)==ERR_OK) {
          if (ESC_SetDutyMs(&ESC_motors[id], val)!=ERR_OK) {
            CLS1_SendStr((unsigned char*)"Failed SetDutyMs()!\r\n", io->stdErr);
            res = ERR_FAILED;
          }
          *handled = TRUE;
        } else {
          CLS1_SendStr((unsigned char*)"Wrong argument, must be in the range 0..100\r\n", io->stdErr);
          res = ERR_FAILED;
        }
      }
    }
  }
  return res;
}
#endif /* PL_HAS_SHELL */


void ESC_Init(void) {
  ESC_MotorID id;

  ESC_isMotorOn = TRUE;
  ESC_motors[ESC_MOTOR_FRONT_LEFT].SetRatio16 = ESC_SetRatio16_FR;
  ESC_motors[ESC_MOTOR_FRONT_RIGHT].SetRatio16 = ESC_SetRatio16_FR;
  ESC_motors[ESC_MOTOR_BACK_RIGHT].SetRatio16 = ESC_SetRatio16_FR;
  ESC_motors[ESC_MOTOR_BACK_LEFT].SetRatio16 = ESC_SetRatio16_FR;
  ESC_motors[ESC_MOTOR_FRONT_LEFT].SetDutyUS = ESC_SetDutyUS_FR;
  ESC_motors[ESC_MOTOR_FRONT_RIGHT].SetDutyUS = ESC_SetDutyUS_FR;
  ESC_motors[ESC_MOTOR_BACK_RIGHT].SetDutyUS = ESC_SetDutyUS_FR;
  ESC_motors[ESC_MOTOR_BACK_LEFT].SetDutyUS = ESC_SetDutyUS_FR;
  (void)PWMFR_Enable();
  for(id=0; id<ESC_MOTOR_NOF; id++) {
    ESC_SetSpeedPercent(&ESC_motors[id], 0);
    ESC_motors[id].us = ESC_MIN_DUTY_MS;
    ESC_motors[id].SetDutyUS(ESC_MIN_DUTY_MS);
  }
}

#endif /* PL_HAS_ESC */



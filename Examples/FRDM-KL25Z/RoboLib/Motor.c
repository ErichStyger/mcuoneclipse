/*
 * Motor.c
 *
 *      Author: Erich Styger
 */
#include "Platform.h"
#if PL_HAS_MOTOR
#include "Motor.h"
#include "DIRR.h"
#include "DIRL.h"
#include "PWMR.h"
#include "PWML.h"
#if PL_HAS_MOTOR_BRAKE
  #include "BrakeL.h"
  #include "BrakeR.h"
#endif
#if PL_HAS_MOTOR_CURRENT_SENSE
  #include "SNS0.h"
#endif
#if PL_HAS_MOTOR_INAB
  #include "DIRRB.h"
  #include "DIRLB.h"
#endif

static MOT_MotorDevice motorL, motorR;
static bool isMotorOn = TRUE;

MOT_MotorDevice *MOT_GetMotorHandle(MOT_MotorSide side) {
  if (side==MOT_MOTOR_LEFT) {
    return &motorL;
  } else {
    return &motorR;
  }
}

#if PL_HAS_MOTOR_BRAKE
void MOT_SetBrake(MOT_MotorDevice *motor, bool on) {
  if (on && !motor->brake) {
    motor->BrakePutVal(1);
    motor->brake = TRUE;
  } else if (!on && motor->brake) {
    motor->BrakePutVal(0);
    motor->brake = FALSE;
  }
}

bool MOT_GetBrake(MOT_MotorDevice *motor) {
  return motor->brake;
}
#endif

#if PL_HAS_MOTOR_CURRENT_SENSE
void MOT_MeasureCurrent(MOT_MotorDevice *motorA, MOT_MotorDevice *motorB) {
  #define SAMPLE_GROUP_SIZE 1U
  SNS0_TResultData MeasuredValues[SAMPLE_GROUP_SIZE];
  LDD_ADC_TSample SampleGroup[SAMPLE_GROUP_SIZE];

  SampleGroup[0].ChannelIdx = 0U;  /* Create one-sample group */
  (void)SNS0_CreateSampleGroup(motorA->SNSdeviceData, (LDD_ADC_TSample *)SampleGroup, SAMPLE_GROUP_SIZE);  /* Set created sample group */
  (void)SNS0_StartSingleMeasurement(motorA->SNSdeviceData);           /* Start continuous measurement */
  while (!SNS0_GetMeasurementCompleteStatus(motorA->SNSdeviceData)) {}; /* Wait for conversion completeness */
  (void)SNS0_GetMeasuredValues(motorA->SNSdeviceData, (LDD_TData *)MeasuredValues);  /* Read measured values */
  motorA->currentValue = MeasuredValues[0];

  SampleGroup[0].ChannelIdx = 1U;  /* Create one-sample group */
  (void)SNS0_CreateSampleGroup(motorB->SNSdeviceData, (LDD_ADC_TSample *)SampleGroup, SAMPLE_GROUP_SIZE);  /* Set created sample group */
  (void)SNS0_StartSingleMeasurement(motorB->SNSdeviceData);           /* Start continuous measurement */
  while (!SNS0_GetMeasurementCompleteStatus(motorB->SNSdeviceData)) {}; /* Wait for conversion completeness */
  (void)SNS0_GetMeasuredValues(motorB->SNSdeviceData, (LDD_TData *)MeasuredValues);  /* Read measured values */
  motorB->currentValue = MeasuredValues[0];
}

static void WriteCurrent(MOT_MotorDevice *motor, const CLS1_StdIOType *io) {
  unsigned char buf[26];
  uint16_t val;

  buf[0] = '\0';
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)", current val 0x");
  UTIL1_strcatNum16Hex(buf, sizeof(buf), motor->currentValue);
  CLS1_SendStr(buf, io->stdOut);

  val = motor->currentValue/(0xFFFF/3300); /* 3300 mV full scale */
  buf[0] = '\0';
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)", mV ");
  UTIL1_strcatNum16u(buf, sizeof(buf), val);
  CLS1_SendStr(buf, io->stdOut);

  val = motor->currentValue/(0xFFFF/2000); /* 2000 mA full scale */
  buf[0] = '\0';
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)", mA ");
  UTIL1_strcatNum16u(buf, sizeof(buf), val);
  CLS1_SendStr(buf, io->stdOut);
}
#endif

static uint8_t PWMLSetRatio16(uint16_t ratio) {
  return PWML_SetRatio16(ratio);
}

static uint8_t PWMRSetRatio16(uint16_t ratio) {
  return PWMR_SetRatio16(ratio);
}

static void DirLPutVal(bool val) {
  DIRL_PutVal(val);
#if PL_HAS_MOTOR_INAB
  DIRLB_PutVal(!val);
#endif
}

static void DirRPutVal(bool val) {
  DIRR_PutVal(val);
#if PL_HAS_MOTOR_INAB
  DIRRB_PutVal(!val);
#endif
}

#if PL_HAS_MOTOR_BRAKE
static void BrakeLPutVal(bool val) {
  BrakeL_PutVal(val);
}

static void BrakeRPutVal(bool val) {
  BrakeR_PutVal(val);
}
#endif

void MOT_SetVal(MOT_MotorDevice *motor, uint16_t val) {
  if (isMotorOn) {
#if PL_HAS_MOTOR_BRAKE
    if (val==0xffff) { /* stop */
      motor->currPWMvalue = 0;
      motor->SetRatio16(0); /* for max brake */
      MOT_SetBrake(motor, TRUE);
    } else {
      motor->currPWMvalue = val;
      MOT_SetBrake(motor, FALSE);
      motor->SetRatio16(val);
    }
#else
    motor->currPWMvalue = val;
    motor->SetRatio16(val);
#endif
  } else { /* have motor stopped */
    motor->currPWMvalue = 0xFFFF;
    motor->SetRatio16(0xFFFF);
  }
}

uint16_t MOT_GetVal(MOT_MotorDevice *motor) {
  return motor->currPWMvalue;
}

void MOT_SetSpeedPercent(MOT_MotorDevice *motor, MOT_SpeedPercent percent) {
  uint32_t val;

  motor->currSpeedPercent = percent; /* store current value */
  if (percent<0) {
    MOT_SetDirection(motor, MOT_DIR_BACKWARD);
    percent = -percent;
  } else {
    MOT_SetDirection(motor, MOT_DIR_FORWARD);
  }
  if (percent>100) { /* make sure we are within 0..100 */
    percent = 100;
  }
  val = ((100-percent)*0xffff)/100;
  MOT_SetVal(motor, (uint16_t)val);
}

void MOT_ChangeSpeedPercent(MOT_MotorDevice *motor, MOT_SpeedPercent relPercent) {
  relPercent += motor->currSpeedPercent; /* make absolute number */
  if (relPercent>100) { /* check for overflow */
    relPercent = 100;
  } else if (relPercent<-100) { /* and underflow */
    relPercent = -100;
  }
  MOT_SetSpeedPercent(motor, relPercent);  /* set speed. This will care about the direction too */
}

void MOT_SetDirection(MOT_MotorDevice *motor, MOT_Direction dir) {
  if (dir==MOT_DIR_BACKWARD) {
    motor->DirPutVal(1);
    if (motor->currSpeedPercent>0) {
      motor->currSpeedPercent = -motor->currSpeedPercent;
    }
  } else if (dir==MOT_DIR_FORWARD) {
    motor->DirPutVal(0);
    if (motor->currSpeedPercent<0) {
      motor->currSpeedPercent = -motor->currSpeedPercent;
    }
  }
}

MOT_Direction MOT_GetDirection(MOT_MotorDevice *motor) {
  if (motor->currSpeedPercent<0) {
    return MOT_DIR_BACKWARD;
  } else {
    return MOT_DIR_FORWARD;
  }
}

static void MOT_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"motor", (unsigned char*)"Group of motor commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows motor help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  on|off", (unsigned char*)"Enables or disables motor\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  (L|R) forward|backward", (unsigned char*)"Change motor direction\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  (L|R) duty <number>", (unsigned char*)"Change motor PWM (-100..+100)%\r\n", io->stdOut);
#if PL_HAS_MOTOR_BRAKE
  CLS1_SendHelpStr((unsigned char*)"  (L|R) brake (on|off)", (unsigned char*)"Enable/disable brake for motor\r\n", io->stdOut);
#endif
}

static void MOT_PrintStatus(const CLS1_StdIOType *io) {
  unsigned char buf[32];

  CLS1_SendStatusStr((unsigned char*)"Motor", (unsigned char*)"\r\n", io->stdOut);
  
  CLS1_SendStatusStr((unsigned char*)"  on/off", isMotorOn?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  
  CLS1_SendStatusStr((unsigned char*)"  motor L", (unsigned char*)"", io->stdOut);
  buf[0] = '\0';
  UTIL1_Num16sToStrFormatted(buf, sizeof(buf), (int16_t)motorL.currSpeedPercent, ' ', 4);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"% 0x");
  UTIL1_strcatNum16Hex(buf, sizeof(buf), MOT_GetVal(&motorL));
  UTIL1_strcat(buf, sizeof(buf),(unsigned char*)(MOT_GetDirection(&motorL)==MOT_DIR_FORWARD?", fw":", bw"));
#if PL_HAS_MOTOR_BRAKE
  UTIL1_strcat(buf, sizeof(buf),(unsigned char*)(MOT_GetBrake(&motorL)?", brake on":", brake off"));
#endif
  CLS1_SendStr(buf, io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);

  CLS1_SendStatusStr((unsigned char*)"  motor R", (unsigned char*)"", io->stdOut);
  buf[0] = '\0';
  UTIL1_Num16sToStrFormatted(buf, sizeof(buf), (int16_t)motorR.currSpeedPercent, ' ', 4);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"% 0x");
  UTIL1_strcatNum16Hex(buf, sizeof(buf), MOT_GetVal(&motorR));
  UTIL1_strcat(buf, sizeof(buf),(unsigned char*)(MOT_GetDirection(&motorR)==MOT_DIR_FORWARD?", fw":", bw"));
#if PL_HAS_MOTOR_BRAKE
  UTIL1_strcat(buf, sizeof(buf),(unsigned char*)(MOT_GetBrake(&motorR)?", brake on":", brake off"));
#endif
  CLS1_SendStr(buf, io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);

#if PL_HAS_MOTOR_CURRENT_SENSE
  WriteCurrent(&motorA, io);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  WriteCurrent(&motorB, io);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
#endif
}

uint8_t MOT_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  int32_t val;
  const unsigned char *p;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"motor help")==0) {
    MOT_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"motor status")==0) {
    MOT_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"motor L forward")==0) {
    MOT_SetDirection(&motorL, MOT_DIR_FORWARD);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"motor R forward")==0) {
    MOT_SetDirection(&motorR, MOT_DIR_FORWARD);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"motor L backward")==0) {
    MOT_SetDirection(&motorL, MOT_DIR_BACKWARD);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"motor R backward")==0) {
    MOT_SetDirection(&motorR, MOT_DIR_BACKWARD);
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, (char*)"motor L duty ", sizeof("motor L duty ")-1)==0) {
    if (!isMotorOn) {
      CLS1_SendStr((unsigned char*)"Motor is OFF, cannot set duty.\r\n", io->stdErr);
      res = ERR_FAILED;
    } else {
      p = cmd+sizeof("motor L duty");
      if (UTIL1_xatoi(&p, &val)==ERR_OK && val >=-100 && val<=100) {
        MOT_SetSpeedPercent(&motorL, (MOT_SpeedPercent)val);
        *handled = TRUE;
      } else {
        CLS1_SendStr((unsigned char*)"Wrong argument, must be in the range -100..100\r\n", io->stdErr);
        res = ERR_FAILED;
      }
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"motor R duty ", sizeof("motor R duty ")-1)==0) {
    if (!isMotorOn) {
      CLS1_SendStr((unsigned char*)"Motor is OFF, cannot set duty.\r\n", io->stdErr);
      res = ERR_FAILED;
    } else {
      p = cmd+sizeof("motor R duty");
      if (UTIL1_xatoi(&p, &val)==ERR_OK && val >=-100 && val<=100) {
        MOT_SetSpeedPercent(&motorR, (MOT_SpeedPercent)val);
        *handled = TRUE;
      } else {
        CLS1_SendStr((unsigned char*)"Wrong argument, must be in the range -100..100\r\n", io->stdErr);
        res = ERR_FAILED;
      }
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"motor on", sizeof("motor on")-1)==0) {
    isMotorOn = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, (char*)"motor off", sizeof("motor off")-1)==0) {
    MOT_SetSpeedPercent(&motorL, 0);
    MOT_SetSpeedPercent(&motorR, 0);
    isMotorOn = FALSE;
    *handled = TRUE;
#if PL_HAS_MOTOR_BRAKE
  } else if (UTIL1_strcmp((char*)cmd, (char*)"motor L brake on")==0) {
    MOT_SetBrake(&motorL, TRUE);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"motor L brake off")==0) {
    MOT_SetBrake(&motorL, FALSE);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"motor R brake on")==0) {
    MOT_SetBrake(&motorR, TRUE);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"motor R brake off")==0) {
    MOT_SetBrake(&motorR, FALSE);
    *handled = TRUE;
#endif
  }
  return res;
}

void MOT_Init(void) {
#if PL_HAS_MOTOR_BRAKE
  motorL.BrakePutVal = BrakeLPutVal;
  motorR.BrakePutVal = BrakeRPutVal;
#endif
  motorL.DirPutVal = DirLPutVal;
  motorR.DirPutVal = DirRPutVal;
  motorL.SetRatio16 = PWMLSetRatio16;
  motorR.SetRatio16 = PWMRSetRatio16;
  MOT_SetSpeedPercent(&motorL, 0);
  MOT_SetSpeedPercent(&motorR, 0);
  PWML_Enable();
  PWMR_Enable();
}
#endif /* PL_HAS_MOTOR */

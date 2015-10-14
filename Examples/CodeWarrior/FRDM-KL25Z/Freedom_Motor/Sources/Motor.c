/*
 * Motor.c
 *
 *      Author: Erich Styger
 */

#include "Motor.h"
#include "DIRA.h"
#include "DIRB.h"
#include "PWMA.h"
#include "PWMB.h"
#include "BrakeA.h"
#include "BrakeB.h"
#include "SNS0.h"
#include "UTIL1.h"

static MOT_MotorDevice motorA, motorB;

void MOT_SetVal(MOT_MotorDevice *motor, uint16_t val) {
  motor->currPWMvalue = val;
  motor->SetRatio16(motor->PWMdeviceData, val);
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
  if (dir==MOT_DIR_BACKWARD && motor->currSpeedPercent>=0) {
    motor->DirPutVal(motor->DIRdeviceData, 0);
    motor->currSpeedPercent = -motor->currSpeedPercent;
  } else if (dir==MOT_DIR_FORWARD && motor->currSpeedPercent<0) {
    motor->DirPutVal(motor->DIRdeviceData, 1);
    motor->currSpeedPercent = -motor->currSpeedPercent;
  }
}

MOT_Direction MOT_GetDirection(MOT_MotorDevice *motor) {
  if (motor->currSpeedPercent<0) {
    return MOT_DIR_BACKWARD;
  } else {
    return MOT_DIR_FORWARD;
  }
}

void MOT_SetBrake(MOT_MotorDevice *motor, bool on) {
  if (on && !motor->brake) {
    motor->BrakePutVal(motor->BRAKEdeviceData, 1);
    motor->brake = TRUE;
  } else if (!on && motor->brake) {
    motor->BrakePutVal(motor->BRAKEdeviceData, 0);
    motor->brake = FALSE;
  }
}

bool MOT_GetBrake(MOT_MotorDevice *motor) {
  return motor->brake;
}

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

static void MOT_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"motor", (unsigned char*)"Group of motor commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows motor help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  (A|B) forward|backward", (unsigned char*)"Change motor direction\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  (A|B) duty <number>", (unsigned char*)"Change motor PWM (-100..+100)%\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  (A|B) brake (on|off)", (unsigned char*)"Enable/disable brake on motor\r\n", io->stdOut);
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

static void MOT_PrintStatus(const CLS1_StdIOType *io) {
  unsigned char buf[32];

  MOT_MeasureCurrent(&motorA, &motorB);
  CLS1_SendStatusStr((unsigned char*)"Motor", (unsigned char*)"\r\n", io->stdOut);

  CLS1_SendStatusStr((unsigned char*)"  motor A", (unsigned char*)"", io->stdOut);
  buf[0] = '\0';
  UTIL1_Num16sToStrFormatted(buf, sizeof(buf), (int16_t)motorA.currSpeedPercent, ' ', 4);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"% 0x");
  UTIL1_strcatNum16Hex(buf, sizeof(buf), MOT_GetVal(&motorA));
  UTIL1_strcat(buf, sizeof(buf),(unsigned char*)(MOT_GetDirection(&motorA)==MOT_DIR_FORWARD?", fw":", bw"));
  UTIL1_strcat(buf, sizeof(buf),(unsigned char*)(MOT_GetBrake(&motorA)?", brake on":", brake off"));
  CLS1_SendStr(buf, io->stdOut);

  WriteCurrent(&motorA, io);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);

  CLS1_SendStatusStr((unsigned char*)"  motor B", (unsigned char*)"", io->stdOut);
  buf[0] = '\0';
  UTIL1_Num16sToStrFormatted(buf, sizeof(buf), (int16_t)motorB.currSpeedPercent, ' ', 4);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"% 0x");
  UTIL1_strcatNum16Hex(buf, sizeof(buf), MOT_GetVal(&motorB));
  UTIL1_strcat(buf, sizeof(buf),(unsigned char*)(MOT_GetDirection(&motorB)==MOT_DIR_FORWARD?", fw":", bw"));
  UTIL1_strcat(buf, sizeof(buf),(unsigned char*)(MOT_GetBrake(&motorB)?", brake on":", brake off"));
  CLS1_SendStr(buf, io->stdOut);

  WriteCurrent(&motorB, io);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
}

uint8_t MOT_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  long val;
  const unsigned char *p;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"motor help")==0) {
    MOT_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"motor status")==0) {
    MOT_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"motor A forward")==0) {
    MOT_SetDirection(&motorA, MOT_DIR_FORWARD);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"motor B forward")==0) {
    MOT_SetDirection(&motorB, MOT_DIR_FORWARD);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"motor A backward")==0) {
    MOT_SetDirection(&motorA, MOT_DIR_BACKWARD);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"motor B backward")==0) {
    MOT_SetDirection(&motorB, MOT_DIR_BACKWARD);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"motor A brake on")==0) {
    MOT_SetBrake(&motorA, TRUE);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"motor A brake off")==0) {
    MOT_SetBrake(&motorA, FALSE);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"motor B brake on")==0) {
    MOT_SetBrake(&motorB, TRUE);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"motor B brake off")==0) {
    MOT_SetBrake(&motorB, FALSE);
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, (char*)"motor A duty", sizeof("motor duty")-1)==0) {
    p = cmd+sizeof("motor A duty");
    if (UTIL1_xatoi(&p, &val)==ERR_OK && val >=-100 && val<=100) {
      MOT_SetSpeedPercent(&motorA, (MOT_SpeedPercent)val);
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument, must be in the range -100..100\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"motor B duty", sizeof("motor B duty")-1)==0) {
    p = cmd+sizeof("motor B duty");
    if (UTIL1_xatoi(&p, &val)==ERR_OK && val >=-100 && val<=100) {
      MOT_SetSpeedPercent(&motorB, (MOT_SpeedPercent)val);
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument, must be in the range -100..100\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  }
  return res;
}

void MOT_Init(void) {

  motorA.SNSdeviceData = SNS0_Init(NULL);
  motorB.SNSdeviceData = motorA.SNSdeviceData;

  /* motor A */
  motorA.DIRdeviceData = DIRA_Init(NULL);
  motorA.DirPutVal = DIRA_PutVal;

  motorA.BRAKEdeviceData = BrakeA_Init(NULL);
  motorA.BrakePutVal = BrakeA_PutVal;

  motorA.PWMdeviceData = PWMA_Init(NULL);
  motorA.SetRatio16 = PWMA_SetRatio16;
  MOT_SetSpeedPercent(&motorA, 0);
  PWMA_Enable(motorA.PWMdeviceData);

  /* motor B */
  motorB.DIRdeviceData = DIRB_Init(NULL);
  motorB.DirPutVal = DIRB_PutVal;

  motorB.BRAKEdeviceData = BrakeB_Init(NULL);
  motorB.BrakePutVal = BrakeB_PutVal;

  motorB.PWMdeviceData = PWMB_Init(NULL);
  motorB.SetRatio16 = PWMB_SetRatio16;
  MOT_SetSpeedPercent(&motorB, 0);
  PWMB_Enable(motorB.PWMdeviceData);

  MOT_MeasureCurrent(&motorA, &motorB);
  motorA.offset = motorA.currentValue;
  motorB.offset = motorB.currentValue;
}

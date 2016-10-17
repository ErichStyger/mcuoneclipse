/*
 * Servo.c
 *
 *  Created on: 14.10.2016
 *      Author: Erich Styger Local
 */

#include "Platform.h"
#include "Servo.h"
#include "PCA9685.h"
#include "PE_Error.h"
#include "CLS1.h"
#include "UTIL1.h"

#define SERVO_FREQ_HZ   60


uint8_t SERVO_InitHardware(uint8_t i2cAddr) {
  if (PCA9685_Reset(i2cAddr)!=ERR_OK) { /* reset and disable PWM */
    return ERR_FAILED;
  }
  if (PCA9685_SetPWMFrequency(i2cAddr, SERVO_FREQ_HZ)!=ERR_OK) {  /* set base frequency */
    return ERR_FAILED;
  }
}

uint8_t SERVO_WriteDutyMicroSeconds(uint8_t i2cAddr, uint8_t channel, uint16_t microSeconds, uint16_t minTicks, uint16_t maxTicks) {
  uint32_t val;
  #define SERVO_MIN_MICROSECONDS  1000
  #define SERVO_MAX_MICROSECONDS  2000

  /* microseconds in the range 1000..2000 */
  if (microSeconds<SERVO_MIN_MICROSECONDS) {
    microSeconds =  SERVO_MIN_MICROSECONDS;
  } else if (microSeconds>SERVO_MAX_MICROSECONDS) {
    microSeconds = SERVO_MAX_MICROSECONDS;
  }
  val = minTicks + ((microSeconds-SERVO_MIN_MICROSECONDS)*(maxTicks-minTicks))/(SERVO_MAX_MICROSECONDS-SERVO_MIN_MICROSECONDS);
  /* ticks in the range of minTicks...maxTicks */
  if (val>maxTicks) {
    val = maxTicks;
  } else if (val<minTicks) {
    val = minTicks;
  }
  return PCA9685_SetChannelDuty12Bit(i2cAddr, channel, 4095-val);
}

static uint8_t PrintStatus(CLS1_ConstStdIOType *io) {
  uint8_t buf[48];

  CLS1_SendStatusStr((unsigned char*)"servo", (const unsigned char*)"\r\n", io->stdOut);
  buf[0] = '\0'; UTIL1_Num16uToStr(buf, sizeof(buf), SERVO_MIN_TICKS); UTIL1_strcat(buf, sizeof(buf), " us\r\n");
  CLS1_SendStatusStr((unsigned char*)"  MinTicks", buf, io->stdOut);
  buf[0] = '\0'; UTIL1_Num16uToStr(buf, sizeof(buf), SERVO_MAX_TICKS); UTIL1_strcat(buf, sizeof(buf), " us\r\n");
  CLS1_SendStatusStr((unsigned char*)"  MaxTicks", buf, io->stdOut);

  return ERR_OK;
}

uint8_t SERVO_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint16_t channel, duty;
  const uint8_t *p;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "servo help")==0) {
    CLS1_SendHelpStr((unsigned char*)"servo", (const unsigned char*)"Group of servo commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  duty <channel> <us>", (const unsigned char*)"Set duty of servo in microseconds\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "servo status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strncmp((char*)cmd, "servo duty ", sizeof("servo duty ")-1)==0) {
    p = cmd+sizeof("servo duty ")-1;
    if (UTIL1_ScanDecimal16uNumber(&p, &channel)==ERR_OK) {
      if (UTIL1_ScanDecimal16uNumber(&p, &duty)==ERR_OK) {
        SERVO_WriteDutyMicroSeconds(PCA9685_I2C_DEFAULT_ADDR, channel, duty, SERVO_MIN_TICKS, SERVO_MAX_TICKS);
      }
    }
    *handled = TRUE;
  }
  return ERR_OK;
}

void SERVO_Deinit(void) {
}

void SERVO_Init(void) {
}

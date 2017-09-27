/*
 * Test.c
 *
 *  Created on: Oct 6, 2013
 *      Author: tastyger
 */
#include "Platform.h"
#if PL_HAS_TEST
#include "Test.h"
#include "CLS1.h"
#include "WAIT1.h"
#include "USER_LED.h"
#include "SW1.h"
#include "Buzzer.h"
#include "Reflectance.h"
#include "Shell.h"

static uint8_t TEST_LED(const CLS1_StdIOType *io) {
  int i;
  
  CLS1_SendStr((unsigned char*)"LED Test:\r\n", io->stdOut);
  CLS1_SendStr((unsigned char*)"See it blink every 1 sec....\r\n", io->stdOut);
  for(i=0;i<5;i++) {
    USER_LED_On();
    WAIT1_WaitOSms(500);
    USER_LED_Off();
    WAIT1_WaitOSms(500);
  }
  CLS1_SendStr((unsigned char*)"Finished!\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t TEST_Button(const CLS1_StdIOType *io) {
  int i;
  bool pressed, prevState;
  
  CLS1_SendStr((unsigned char*)"Button Test:\r\n", io->stdOut);
  CLS1_SendStr((unsigned char*)"Press user button during the next 5 seconds...\r\n", io->stdOut);
  prevState = !(SW1_GetVal()==0);
  for(i=0;i<100;i++) {
    pressed = SW1_GetVal()==0;
    if (pressed!=prevState) {
      if (pressed) {
        CLS1_SendStr((unsigned char*)"Button pressed!\r\n", io->stdOut);
      } else {
        CLS1_SendStr((unsigned char*)"Button not pressed!\r\n", io->stdOut);
      }
      prevState = pressed;
    }
    WAIT1_WaitOSms(50);
  }
  CLS1_SendStr((unsigned char*)"Finished!\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t TEST_Buzzer(const CLS1_StdIOType *io) {
  int i;
  
  CLS1_SendStr((unsigned char*)"Buzzer Test:\r\n", io->stdOut);
  CLS1_SendStr((unsigned char*)"Hear the beeps....\r\n", io->stdOut);
  for(i=0;i<8;i++) {
    BUZ_Beep(i*100, 250); /* beep for 250 ms */
    WAIT1_WaitOSms(500);
  }
  CLS1_SendStr((unsigned char*)"Finished!\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t TEST_Reflectance(const CLS1_StdIOType *io) {
  int i;
  
  CLS1_SendStr((unsigned char*)"Reflectance Test:\r\n", io->stdOut);
  CLS1_SendStr((unsigned char*)"IR LED on/off....\r\n", io->stdOut);
  for(i=0;i<5;i++) {
    SHELL_ParseCmd((unsigned char*)"ref led off");
    WAIT1_WaitOSms(500);
    SHELL_ParseCmd((unsigned char*)"ref led on");
    WAIT1_WaitOSms(500);
  }
  CLS1_SendStr((unsigned char*)"showing reflectance status....\r\n", io->stdOut);
  for(i=0;i<10;i++) {
    SHELL_ParseCmd((unsigned char*)"ref status");
    WAIT1_WaitOSms(500);
  }
  CLS1_SendStr((unsigned char*)"Finished!\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t TEST_Motor(bool isLeft, const CLS1_StdIOType *io) {
  int i;
  uint8_t buf[32];
  const unsigned char *cmd;
  
  CLS1_SendStr((unsigned char*)"Motor Test:\r\n", io->stdOut);
  if (isLeft) {
    CLS1_SendStr((unsigned char*)"Left motor....\r\n", io->stdOut);
    cmd = (unsigned char*)"motor L duty ";
  } else {
    CLS1_SendStr((unsigned char*)"Right motor....\r\n", io->stdOut);
    cmd = (unsigned char*)"motor R duty ";
  }
  /* 0 to 100% */
  for(i=0;i<=100;i+=20) {
    UTIL1_strcpy(buf, sizeof(buf), cmd);
    UTIL1_strcatNum16s(buf, sizeof(buf), i);
    SHELL_ParseCmd(buf);
    WAIT1_WaitOSms(500);
  }
  /* 100% to -100% */
  for(i=80;i>=-100;i-=20) {
    UTIL1_strcpy(buf, sizeof(buf), cmd);
    UTIL1_strcatNum16s(buf, sizeof(buf), i);
    SHELL_ParseCmd(buf);
    WAIT1_WaitOSms(500);
  }
  /* back to 0% */
  for(i=-80;i<=0;i+=20) {
    UTIL1_strcpy(buf, sizeof(buf), cmd);
    UTIL1_strcatNum16s(buf, sizeof(buf), i);
    SHELL_ParseCmd(buf);
    WAIT1_WaitOSms(500);
  }
  CLS1_SendStr((unsigned char*)"Finished!\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t TEST_MotorLeft(const CLS1_StdIOType *io) {
  return TEST_Motor(TRUE, io);
}

static uint8_t TEST_MotorRight(const CLS1_StdIOType *io) {
  return TEST_Motor(FALSE, io);
}

static uint8_t TEST_Quad(bool isLeft, const CLS1_StdIOType *io) {
  int i;
  uint8_t buf[24];
  
  CLS1_SendStr((unsigned char*)"Quadrature Test:\r\n", io->stdOut);
  if (isLeft) {
    CLS1_SendStr((unsigned char*)"Left quadrature....\r\n", io->stdOut);
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"Q4CLeft status");
  } else {
    CLS1_SendStr((unsigned char*)"Right quadrature....\r\n", io->stdOut);
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"Q4CRight status");
  }
  for(i=0;i<=10;i++) {
    SHELL_ParseCmd(buf);
    WAIT1_WaitOSms(500);
  }
  CLS1_SendStr((unsigned char*)"Finished!\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t TEST_QuadLeft(const CLS1_StdIOType *io) {
  return TEST_Quad(TRUE, io);
}

static uint8_t TEST_QuadRight(const CLS1_StdIOType *io) {
  return TEST_Quad(FALSE, io);
}

static uint8_t TEST_Ultrasonic(const CLS1_StdIOType *io) {
  int i;
  
  CLS1_SendStr((unsigned char*)"Ultrasonic Test:\r\n", io->stdOut);
  for(i=0;i<10;i++) {
    SHELL_ParseCmd((unsigned char*)"ultrasonic status");
    WAIT1_WaitOSms(500);
  }
  CLS1_SendStr((unsigned char*)"Finished!\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t TEST_SideSensors(const CLS1_StdIOType *io) {
  int i;
  
  CLS1_SendStr((unsigned char*)"Side Sensor Test:\r\n", io->stdOut);
  for(i=0;i<10;i++) {
    SHELL_ParseCmd((unsigned char*)"dist status");
    WAIT1_WaitOSms(500);
  }
  CLS1_SendStr((unsigned char*)"Finished!\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t TEST_Bluetooth(const CLS1_StdIOType *io) {
  CLS1_SendStr((unsigned char*)"Bluetooth Test (red LED on module must blink, not connected!):\r\n", io->stdOut);
  SHELL_ParseCmd((unsigned char*)"BT1 status");
  WAIT1_WaitOSms(500);
  CLS1_SendStr((unsigned char*)"Finished!\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t (*TestFct[])(const CLS1_StdIOType *io) = {
    /* 0 */ TEST_LED,
    /* 1 */ TEST_Button,
    /* 2 */ TEST_Buzzer,
    /* 3 */ TEST_Reflectance,
    /* 4 */ TEST_MotorLeft,
    /* 5 */ TEST_MotorRight,
    /* 6 */ TEST_QuadLeft,
    /* 7 */ TEST_QuadRight,
    /* 8 */ TEST_Ultrasonic,
    /* 9 */ TEST_SideSensors,
    /* 10 */ TEST_Bluetooth
};

static uint8_t TEST_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"test", (unsigned char*)"Group of test commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows test help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  test 0", (unsigned char*)"LED\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  test 1", (unsigned char*)"Button\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  test 2", (unsigned char*)"Buzzer\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  test 3", (unsigned char*)"Reflectance\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  test 4", (unsigned char*)"Motor Left\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  test 5", (unsigned char*)"Motor Right\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  test 6", (unsigned char*)"Quadrature Left\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  test 7", (unsigned char*)"Quadrature Right\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  test 8", (unsigned char*)"Ultrasonic\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  test 9", (unsigned char*)"Side Sensors\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  test 10", (unsigned char*)"Bluetooth\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t TEST_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  uint8_t val;
  const unsigned char *p;
  
  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"test help")==0) {
    *handled = TRUE;
    return TEST_PrintHelp(io);
  } else if (UTIL1_strncmp((char*)cmd, (char*)"test ", sizeof("test ")-1)==0) {
    p = cmd+sizeof("test ")-1;
    if (UTIL1_ScanDecimal8uNumber(&p, &val)==ERR_OK && val >=0 && val<sizeof(TestFct)/sizeof(TestFct)[0]) {
      *handled = TRUE;
      return TestFct[val](io);
    }
    CLS1_SendStr((unsigned char*)"ERROR: illegal test number!\r\n", io->stdErr);
    res = ERR_FAILED;
  }
  return res;
}

void TEST_Init(void) {
}

void TEST_Deinit(void) {
}

#endif /* PL_HAS_TEST */

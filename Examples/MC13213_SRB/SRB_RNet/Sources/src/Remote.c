/**
 * \file
 * \brief Radio Remote Module
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module to handle accelerometer values passed over the Radio.
 */

#include "Platform.h" /* interface to the platform */
#if PL_HAS_REMOTE
#include "Remote.h"
#include "FRTOS1.h"
#include "CLS1.h"
#include "UTIL1.h"
#if PL_HAS_RADIO
#endif
#if PL_HAS_ACCEL
  #include "Accel.h"
#endif
#if PL_HAS_PID
  #include "PID.h"
#endif
#if PL_HAS_MOTOR
  #include "Motor.h"
#endif
#if PL_HAS_RADIO
  #include "RNet_App.h"
  #include "RNet_AppConfig.h"
#endif
#include "LED1.h"

static bool REMOTE_isOn = FALSE;

#if PL_APP_ACCEL_CONTROL_SENDER
static portTASK_FUNCTION(RemoteTask, pvParameters) {
  (void)pvParameters;
#if PL_HAS_ACCEL
  //ACCEL_LowLevelInit(); /* already done in main task */
#endif
  for(;;) {
    if (REMOTE_isOn) {
#if PL_HAS_ACCEL
      uint8_t buf[6];
      int16_t x, y, z;

      /* send periodically accelerometer messages */
      ACCEL_GetValues(&x, &y, &z);
      buf[0] = (uint8_t)(x&0xFF);
      buf[1] = (uint8_t)(x>>8);
      buf[2] = (uint8_t)(y&0xFF);
      buf[3] = (uint8_t)(y>>8);
      buf[4] = (uint8_t)(z&0xFF);
      buf[5] = (uint8_t)(z>>8);
      (void)RAPP_SendPayloadDataBlock(buf, sizeof(buf), RAPP_MSG_TYPE_ACCEL, RNETA_GetDestAddr());
      LED1_Neg();
#endif
#if PL_HAS_WATCHDOG
      WDT_IncTaskCntr(WDT_TASK_ID_TRACE, 200);
#endif
      FRTOS1_vTaskDelay(200/portTICK_RATE_MS);
    } else {
#if PL_HAS_WATCHDOG
      WDT_IncTaskCntr(WDT_TASK_ID_TRACE, 1000);
#endif
      FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
    }
  } /* for */
}
#endif

#if PL_HAS_MOTOR
static void REMOTE_HandleMsg(int16_t x, int16_t y, int16_t z) {
  #define SCALE_DOWN 30

  if (!REMOTE_isOn) {
    return;
  }
  if (y>950 || y<-950) { /* have a way to stop motor: turn SRB USB port side up or down */
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
  } else if ((y>150 || y<-150) && (x>150 || x<-150)) { /* x: speed, y: direction */
    int16_t speed, speedL, speedR;
    
    speed = x/SCALE_DOWN;
    if (y<0) {
      if (speed<0) {
        speedR = speed+(y/SCALE_DOWN);
      } else {
        speedR = speed-(y/SCALE_DOWN);
      }
      speedL = speed;
    } else {
      speedR = speed;
      if (speed<0) {
        speedL = speed-(y/SCALE_DOWN);
      } else {
        speedL = speed+(y/SCALE_DOWN);
      }
    }
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), speedL);
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), speedR);
  } else if (x>100 || x<-100) { /* speed */
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), x/SCALE_DOWN);
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), x/SCALE_DOWN);
  } else if (y>100 || y<-100) { /* direction */
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -y/SCALE_DOWN);
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), (y/SCALE_DOWN));
  } else { /* device flat on the table? */
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
  }
}
#endif

uint8_t REMOTE_HandleRemoteRxMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet) {
#if PL_HAS_SHELL
  uint8_t buf[16];
  CLS1_ConstStdIOTypePtr io = CLS1_GetStdio();
#endif
  int16_t x, y, z;
  
  (void)size;
  (void)packet;
  switch(type) {
    case RAPP_MSG_TYPE_ACCEL: /* <type><size><data */
      *handled = TRUE;
      /* get data value */
      x = (data[0])|(data[1]<<8);
      y = (data[2])|(data[3]<<8);
      z = (data[4])|(data[5]<<8);
#if PL_HAS_SHELL
      CLS1_SendStr((unsigned char*)"x: ", io->stdOut);
      CLS1_SendNum16s(x, io->stdOut);
      CLS1_SendStr((unsigned char*)" y: ", io->stdOut);
      CLS1_SendNum16s(y, io->stdOut);
      CLS1_SendStr((unsigned char*)" z: ", io->stdOut);
      CLS1_SendNum16s(z, io->stdOut);
      CLS1_SendStr((unsigned char*)" from addr 0x", io->stdOut);
      buf[0] = '\0';
#if RNWK_SHORT_ADDR_SIZE==1
      UTIL1_strcatNum8Hex(buf, sizeof(buf), srcAddr);
#else
      UTIL1_strcatNum16Hex(buf, sizeof(buf), srcAddr);
#endif
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
      CLS1_SendStr(buf, io->stdOut);
#endif
#if PL_HAS_MOTOR
      REMOTE_HandleMsg(x, y, z);
#endif
      return ERR_OK;
    default:
      break;
  } /* switch */
  return ERR_OK;
}

static void REMOTE_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"remote", (unsigned char*)"Group of remote commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows remote help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  on|off", (unsigned char*)"Turns the remote on or off\r\n", io->stdOut);
}

static void REMOTE_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"Remote", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  remote", REMOTE_isOn?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
}

uint8_t REMOTE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"remote help")==0) {
    REMOTE_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"remote status")==0) {
    REMOTE_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"remote on")==0) {
    REMOTE_isOn = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"remote off")==0) {
    REMOTE_isOn = FALSE;
    *handled = TRUE;
  }
  return res;
}

bool REMOTE_GetOnOff(void) {
  return REMOTE_isOn;
}

void REMOTE_SetOnOff(bool on) {
  REMOTE_isOn = on;
}

void REMOTE_Deinit(void) {
  /* nothing to do */
}

/*! \brief Initializes module */
void REMOTE_Init(void) {
  REMOTE_isOn = FALSE;
#if PL_APP_ACCEL_CONTROL_SENDER
  if (FRTOS1_xTaskCreate(RemoteTask, (signed portCHAR *)"Remote", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
}
#endif /* PL_HAS_REMOTE */


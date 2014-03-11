/**
 * \file
 * \brief Application module
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This is the implementation of the application.
 */
#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "FRTOS1.h"
#include "EVNT1.h"
#include "Shell.h"
#include "FX1.h"
#include "AD1.h"
#include "UTIL1.h"

static uint16_t GetLightValue(void) {
  uint16_t val;
  
  (void)AD1_Measure(TRUE);
  (void)AD1_GetValue16(&val);
  return val;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[24];
  
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  UTIL1_strcatNum16Hex(buf, sizeof(buf), GetLightValue());
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  Light", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"app", (unsigned char*)"Group of application commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "app help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "app status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  }
  return ERR_OK;
}

void APP_HandleEvent(uint8_t event) {
  switch(event) {
    case EVNT1_KEY1_PRESSED:
      CLS1_SendStr((unsigned char*)"KEY1 pressed!\r\n", CLS1_GetStdio()->stdOut);
      break;
    case EVNT1_KEY1_RELEASED:
      CLS1_SendStr((unsigned char*)"KEY1 released!\r\n", CLS1_GetStdio()->stdOut);
      break;
    case EVNT1_KEY1_LONG_RELEASED:
      CLS1_SendStr((unsigned char*)"KEY1 long released!\r\n", CLS1_GetStdio()->stdOut);
      break;
    default:
      break;
  }
}

static uint8_t InitAccelMagnetometer(void) {
  uint8_t databyte;
  
  FX1_Init(); /* call init function of component */
  
  if (FX1_WhoAmI(&databyte)!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"Failed!\r\n", CLS1_GetStdio()->stdErr);
    return ERR_FAILED;
  }
  if (databyte!=FX1_WHO_AM_I_VAL) {
    CLS1_SendStr((unsigned char*)"Unknown device!\r\n", CLS1_GetStdio()->stdErr);
    return ERR_FAILED;
  }
  // write 0000 0000 = 0x00 to accelerometer control register 1 to place FXOS8700 into
  // standby
  // [7-1] = 0000 000
  // [0]: active=0
  if (FX1_WriteReg8(FX1_CTRL_REG_1, 0x00) != ERR_OK) {
    CLS1_SendStr((unsigned char*)"Failed!\r\n", CLS1_GetStdio()->stdErr);
    return ERR_FAILED;
  }
  // write 0001 1111 = 0x1F to magnetometer control register 1
  // [7]: m_acal=0: auto calibration disabled
  // [6]: m_rst=0: no one-shot magnetic reset
  // [5]: m_ost=0: no one-shot magnetic measurement
  // [4-2]: m_os=111=7: 8x oversampling (for 200Hz) to reduce magnetometer noise
  // [1-0]: m_hms=11=3: select hybrid mode with accel and magnetometer active
  if (FX1_WriteReg8(FX1_M_CTRL_REG_1, 0x1F) != ERR_OK) {
    CLS1_SendStr((unsigned char*)"Failed!\r\n", CLS1_GetStdio()->stdErr);
    return ERR_FAILED;
  }
  // write 0010 0000 = 0x20 to magnetometer control register 2
  // [7]: reserved
  // [6]: reserved
  // [5]: hyb_autoinc_mode=1 to map the magnetometer registers to follow the
  // accelerometer registers
  // [4]: m_maxmin_dis=0 to retain default min/max latching even though not used
  // [3]: m_maxmin_dis_ths=0
  // [2]: m_maxmin_rst=0
  // [1-0]: m_rst_cnt=00 to enable magnetic reset each cycle
  if (FX1_WriteReg8(FX1_M_CTRL_REG_2, 0x20) != ERR_OK) {
    CLS1_SendStr((unsigned char*)"Failed!\r\n", CLS1_GetStdio()->stdErr);
    return ERR_FAILED;
  }
  // write 0000 0001= 0x00 to XYZ_DATA_CFG register
  // [7]: reserved
  // [6]: reserved
  // [5]: reserved
  // [4]: hpf_out=0
  // [3]: reserved
  // [2]: reserved
  // [1-0]: fs=00 for accelerometer range of +/-2g range with 0.244mg/LSB
  if (FX1_WriteReg8(FX1_XYZ_DATA_CFG, 0x00) != ERR_OK) {
    CLS1_SendStr((unsigned char*)"Failed!\r\n", CLS1_GetStdio()->stdErr);
    return ERR_FAILED;
  }
  // write 0000 1101b = 0x0D to accelerometer control register 1
  // [7-6]: aslp_rate=00
  // [5-3]: dr=001=1 for 200Hz data rate (when in hybrid mode)
  // [2]: lnoise=1 for low noise mode
  // [1]: f_read=0 for normal 16 bit reads
  // [0]: active=1 to take the part out of standby and enable sampling
  if (FX1_WriteReg8(FX1_CTRL_REG_1, 0x0D) != ERR_OK) {
    CLS1_SendStr((unsigned char*)"Failed!\r\n", CLS1_GetStdio()->stdErr);
    return ERR_FAILED;
  }
  return ERR_OK; /* normal return */
}

static void AppTask(void *pvParameters) {
  uint16_t lightVal;
  
  (void)InitAccelMagnetometer();
  for(;;) {
    EVNT1_HandleEvent();
    LED1_Neg();
#if 0
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
#else /* task rate depending on light sensor value */
    lightVal = GetLightValue();
    FRTOS1_vTaskDelay((lightVal>>8)/portTICK_RATE_MS);
#endif
  }
}

void APP_Run(void) {
  /* some hardware test... */
#if 0
  LED1_Neg();
  LED2_Neg();
  LED3_Neg();
  CLS1_SendStr((unsigned char*)"Hello world!\r\n", CLS1_GetStdio()->stdOut);
  LED1_Neg();
  LED2_Neg();
  LED3_Neg();
#endif
  
  /* now start the application */
  SHELL_Init();
  if (FRTOS1_xTaskCreate(
        AppTask,  /* pointer to the task */
        "App", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+2,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  FRTOS1_vTaskStartScheduler();
}

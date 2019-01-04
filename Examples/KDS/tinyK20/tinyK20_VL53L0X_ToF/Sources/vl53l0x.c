/*
 * vl53l0x.c
 *
 */

#include "vl53l0x.h"
#include "CLS1.h"
#include "UTIL1.h"

#include "vl53l0x_api.h"
#include "vl53l0x_platform.h"
#include "vl53l0x_i2c_platform.h"

static VL53L0X_Dev_t MyDevice; /* device descriptor */

static bool isMeasurementReady(void){
  uint8_t deviceReady;
  uint32_t err_code;

  err_code = VL53L0X_GetMeasurementDataReady(&MyDevice, &deviceReady);
  if(VL53L0X_ERROR_NONE != err_code) {
    CLS1_printf("ERROR: VL53L0X_GetMeasurementDataReady: %d\r\n", err_code);
    return FALSE;
  }
  return deviceReady!=0;
}

uint8_t VL53L0X_MeasureSingle(uint16_t *mm) {
  VL53L0X_RangingMeasurementData_t rangingData;
  uint32_t err_code;

  err_code = VL53L0X_StartMeasurement(&MyDevice);
  if (err_code!=VL53L0X_ERROR_NONE) {
    CLS1_printf("ERROR: VL53L0X_StartMeasurement() failed\r\n");
    return ERR_FAILED;
  }
  do{
    /* blocking wait! */
  } while(!isMeasurementReady());

  err_code = VL53L0X_GetRangingMeasurementData(&MyDevice, &rangingData);
  if (err_code!=VL53L0X_ERROR_NONE) {
    CLS1_printf("ERROR: VL53L0X_GetRangingMeasurementData() failed\r\n");
    return ERR_FAILED;
  }
  err_code = VL53L0X_ClearInterruptMask(&MyDevice, 0);
  if (err_code!=VL53L0X_ERROR_NONE) {
    CLS1_printf("ERROR: VL53L0X_ClearInterruptMask() failed\r\n");
    return ERR_FAILED;
  }
  if (mm!=NULL) {
    *mm = rangingData.RangeMilliMeter;
  }
  return ERR_OK;
}

uint8_t VL53L0X_Init(void) {
  VL53L0X_Error err_code;
  uint8_t vhvCalibrationValue;
  uint8_t phaseCalibrationValue;
  uint32_t refSpadCount;
  uint8_t isApertureSpads;

  /* Initialize Comms */
  MyDevice.I2cDevAddr      =  0x29;
  MyDevice.comms_type      =  1;
  MyDevice.comms_speed_khz =  400;

  err_code = VL53L0X_comms_initialise(I2C, MyDevice.comms_speed_khz);
  if(err_code!=VL53L0X_ERROR_NONE) {
    CLS1_printf("ERROR: VL53L0X_comms_initialise(): %d\r\n", err_code);
    return ERR_FAILED;
  }

  err_code = VL53L0X_DataInit(&MyDevice);
  if(err_code!=VL53L0X_ERROR_NONE) {
    CLS1_printf("ERROR: DataInit(): %d\r\n", err_code);
    return ERR_FAILED;
  }

  err_code = VL53L0X_StaticInit(&MyDevice);
  if(err_code != VL53L0X_ERROR_NONE) {
    CLS1_printf("ERROR: StaticInit: %d\r\n", err_code);
    return ERR_FAILED;
  }

  VL53L0X_PerformRefSpadManagement(&MyDevice, &refSpadCount, &isApertureSpads);
  if(err_code!=VL53L0X_ERROR_NONE) {
    CLS1_printf("ERROR: SpadCal: %d\r\n", err_code);
    return ERR_FAILED;
  }

  err_code = VL53L0X_PerformRefCalibration(&MyDevice, &vhvCalibrationValue, &phaseCalibrationValue);
  if(err_code!=VL53L0X_ERROR_NONE) {
    CLS1_printf("ERROR: VL53L0X_PerformRefCalibration(): %d\r\n", err_code);
    return ERR_FAILED;
  }

  err_code = VL53L0X_SetDeviceMode(&MyDevice, VL53L0X_DEVICEMODE_SINGLE_RANGING);
  if(err_code != VL53L0X_ERROR_NONE) {
    CLS1_printf("ERROR: VL53L0X_SetDeviceMode(): %d\r\n", err_code);
    return ERR_FAILED;
  }

  /* Enable/Disable Sigma and Signal check */
  err_code = VL53L0X_SetLimitCheckEnable(&MyDevice, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1 );
  if(err_code != VL53L0X_ERROR_NONE) {
    CLS1_printf("ERROR: VL53L0X_SetLimitCheckEnable(): %d\r\n", err_code);
    return ERR_FAILED;
  }

  err_code = VL53L0X_SetLimitCheckEnable(&MyDevice, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1 );
  if(err_code != VL53L0X_ERROR_NONE) {
    CLS1_printf("ERROR: VL53L0X_SetLimitCheckEnable(): %d\r\n", err_code);
    return ERR_FAILED;
  }

  err_code = VL53L0X_SetLimitCheckEnable(&MyDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, 1 );
  if(err_code != VL53L0X_ERROR_NONE) {
    CLS1_printf("ERROR: VL53L0X_SetLimitCheckEnable(): %d\r\n", err_code);
    return ERR_FAILED;
  }

  err_code = VL53L0X_SetLimitCheckValue(&MyDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, (FixPoint1616_t)( 1.5 * 0.023 * 65536 ) );
  if(err_code != VL53L0X_ERROR_NONE) {
    CLS1_printf("ERROR: VL53L0X_SetLimitCheckValue(): %d\r\n", err_code);
    return ERR_FAILED;
  }
  return ERR_OK;
}

static uint8_t VL53L0X_PrintStatus(CLS1_ConstStdIOType *io) {
  char pal[VL53L0X_MAX_STRING_LENGTH];
  uint8_t buf[48];
  VL53L0X_Error err_code;
  VL53L0X_Version_t version;
  uint8_t deviceRevisionMajor;
  uint8_t deviceRevisionMinor;
  uint8_t vhvCalibrationValue;
  uint8_t phaseCalibrationValue;
  uint32_t refSpadCount;
  uint8_t isApertureSpads;
  uint16_t mm;

  CLS1_SendStatusStr((const unsigned char*)"VL53L0X", (const unsigned char*)"\r\n", io->stdOut);

  err_code = VL53L0X_GetVersion(&version);
  if(err_code!=VL53L0X_ERROR_NONE) {
    VL53L0X_GetPalErrorString(err_code, pal);
    UTIL1_strcat(pal, sizeof(pal), "\r\n");
    CLS1_SendStatusStr((const unsigned char*)"  ERROR", pal, io->stdOut);
  } else {
    buf[0] = '\0';
    UTIL1_strcatNum8u(buf, sizeof(buf), version.major);
    UTIL1_chcat(buf, sizeof(buf), '.');
    UTIL1_strcatNum8u(buf, sizeof(buf), version.minor);
    UTIL1_chcat(buf, sizeof(buf), '.');
    UTIL1_strcatNum8u(buf, sizeof(buf), version.build);
    UTIL1_strcat(buf, sizeof(buf), " revision: ");
    UTIL1_strcatNum32u(buf, sizeof(buf), version.revision);
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
    CLS1_SendStatusStr((const unsigned char*)"  API", buf, io->stdOut);
  }

  err_code = VL53L0X_GetReferenceSpads(&MyDevice, &refSpadCount, &isApertureSpads);
  if(err_code!=VL53L0X_ERROR_NONE) {
    VL53L0X_GetPalErrorString(err_code, pal);
    UTIL1_strcat(pal, sizeof(pal), "\r\n");
    CLS1_SendStatusStr((const unsigned char*)"  ERROR", pal, io->stdOut);
  } else {
    buf[0] = '\0';
    UTIL1_strcat(buf, sizeof(buf), "refSpadCount: ");
    UTIL1_strcatNum32u(buf, sizeof(buf), refSpadCount);
    UTIL1_strcat(buf, sizeof(buf), ", isApertureSpads: ");
    UTIL1_strcatNum8u(buf, sizeof(buf), isApertureSpads);
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
    CLS1_SendStatusStr((const unsigned char*)"  Spads", buf, io->stdOut);
  }

  err_code =  VL53L0X_GetRefCalibration(&MyDevice, &vhvCalibrationValue, &phaseCalibrationValue);
  if(err_code!=VL53L0X_ERROR_NONE) {
    VL53L0X_GetPalErrorString(err_code, pal);
    UTIL1_strcat(pal, sizeof(pal), "\r\n");
    CLS1_SendStatusStr((const unsigned char*)"  ERROR", pal, io->stdOut);
  } else {
    buf[0] = '\0';
    UTIL1_strcat(buf, sizeof(buf), "VHV: ");
    UTIL1_strcatNum8u(buf, sizeof(buf), vhvCalibrationValue);
    UTIL1_strcat(buf, sizeof(buf), ", phase: ");
    UTIL1_strcatNum8u(buf, sizeof(buf), phaseCalibrationValue);
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
    CLS1_SendStatusStr((const unsigned char*)"  Calib", buf, io->stdOut);
  }

  if (VL53L0X_MeasureSingle(&mm)!=ERR_OK) {
    CLS1_SendStatusStr((const unsigned char*)"  Distance", "ERROR\r\n", io->stdOut);
  } else {
    buf[0] = '\0';
    UTIL1_strcatNum16u(buf, sizeof(buf), mm);
    UTIL1_strcat(buf, sizeof(buf), " mm\r\n");
    CLS1_SendStatusStr((const unsigned char*)"  Distance", buf, io->stdOut);
  }

  return ERR_OK;
}

uint8_t VL53L0X_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "VL53L0X help")==0) {
    CLS1_SendHelpStr((unsigned char*)"VL53L0X", (const unsigned char*)"Group of VL53L0X commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, "VL53L0X status")==0) {
    *handled = TRUE;
    return VL53L0X_PrintStatus(io);
  }
  return ERR_OK;
}


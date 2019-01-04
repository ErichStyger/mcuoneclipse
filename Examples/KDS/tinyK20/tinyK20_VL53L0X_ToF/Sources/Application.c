/*
 * Application.c
 *
 *  Created on: 04.03.2016
 *      Author: Erich Styger
 */

#include "Application.h"
#include "LED1.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "PORT_PDD.h"

#include "vl53l0x_api.h"
#include "vl53l0x_platform.h"
#include "vl53l0x_i2c_platform.h"

VL53L0X_Dev_t MyDevice;
VL53L0X_Dev_t *pMyDevice = &MyDevice;

uint16_t latestRange = 0 ;

static void print_pal_error(VL53L0X_Error Status){
  if(Status != 0){
    char buf[VL53L0X_MAX_STRING_LENGTH];
    VL53L0X_GetPalErrorString(Status, buf);
    CLS1_printf("API Status: %i : %s\n", (uint32_t)Status, *buf);
  }
}

static bool isMeasurementReady(void){
  uint8_t deviceReady;
  uint32_t err_code;

  err_code = VL53L0X_GetMeasurementDataReady(pMyDevice, &deviceReady);
  if(VL53L0X_ERROR_NONE != err_code) {
    CLS1_printf("ERROR: VL53L0X_GetMeasurementDataReady: %d\r\n", err_code);
    return FALSE;
  }
  return deviceReady!=0;
}


void APP_Start(void) {
  uint8_t val=0;
  int16_t range;
  uint8_t res;
  uint16_t ambient;
  float lux;
  CLS1_ConstStdIOType *io = CLS1_GetStdio();

  /* need pull-up on UART Rx pin (PTC3) */
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 3, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 3, PORT_PDD_PULL_ENABLE);

  CLS1_SendStr("\r\n*****************************\r\nVL53L0X with tinyK20\r\n*****************************\r\n", io->stdOut);
  uint32_t err_code;

  //    // Initialize Comms
  MyDevice.I2cDevAddr      =  0x29;
  MyDevice.comms_type      =  1;
  MyDevice.comms_speed_khz =  400;

  VL53L0X_Version_t                   Version;
  VL53L0X_Version_t                  *pVersion   = &Version;
  uint8_t deviceRevisionMajor;
  uint8_t deviceRevisionMinor;

  uint8_t vhvCalibrationValue;
  uint8_t phaseCalibrationValue;

  err_code = VL53L0X_comms_initialise(I2C, pMyDevice->comms_speed_khz);

  if (err_code==VL53L0X_ERROR_NONE) {

    err_code = VL53L0X_DataInit(pMyDevice);
    if(err_code!=VL53L0X_ERROR_NONE) {
      CLS1_printf("ERROR: DataInit: %d\r\n", err_code);
    }

    err_code = VL53L0X_GetVersion(pVersion);
    print_pal_error(err_code);
    CLS1_printf("VL53L0X API Version: %d.%d.%d (revision %d)\r\n", pVersion->major, pVersion->minor ,pVersion->build, pVersion->revision);

    err_code = VL53L0X_GetProductRevision(pMyDevice, &deviceRevisionMajor, &deviceRevisionMinor);
    if(err_code == VL53L0X_ERROR_NONE){
      CLS1_printf("VL53L0X product revision: %d.%d\r\n", deviceRevisionMajor, deviceRevisionMinor);
    } else {
      CLS1_printf("ERROR: Version Retrieval Failed.\r\n");
      print_pal_error(err_code);
    }

    err_code = VL53L0X_StaticInit(pMyDevice);
    if(err_code != VL53L0X_ERROR_NONE) {
      CLS1_printf("ERROR: StaticInit: %d\r\n", err_code);
    }

    uint32_t refSpadCount;
    uint8_t isApertureSpads;

    VL53L0X_PerformRefSpadManagement(pMyDevice, &refSpadCount, &isApertureSpads);
    if(err_code!=VL53L0X_ERROR_NONE) {
      CLS1_printf("ERROR: SpadCal: %d\r\n", err_code);
    } else {
      CLS1_printf("refSpadCount: %d\r\nisApertureSpads: %d\r\n", refSpadCount, isApertureSpads);
    }

    err_code = VL53L0X_PerformRefCalibration(pMyDevice, &vhvCalibrationValue, &phaseCalibrationValue);
    print_pal_error(err_code);
    CLS1_printf("Calibration Values: VHV:%d phaseCal:%d\r\n", vhvCalibrationValue, phaseCalibrationValue);


    err_code = VL53L0X_SetDeviceMode(pMyDevice, VL53L0X_DEVICEMODE_SINGLE_RANGING);
    if(err_code != VL53L0X_ERROR_NONE) {
      CLS1_printf("ERROR: VL53L0X_SetDeviceMode(): %d\r\n", err_code);
    }

    // Enable/Disable Sigma and Signal check
     if( err_code == VL53L0X_ERROR_NONE ) {
       err_code = VL53L0X_SetLimitCheckEnable( pMyDevice, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1 );
       if(err_code != VL53L0X_ERROR_NONE) {
         CLS1_printf("ERROR: VL53L0X_SetLimitCheckEnable(): %d\r\n", err_code);
       }
     }

     if( err_code == VL53L0X_ERROR_NONE ) {
       err_code = VL53L0X_SetLimitCheckEnable( pMyDevice, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1 );
       if(err_code != VL53L0X_ERROR_NONE) {
         CLS1_printf("ERROR: VL53L0X_SetLimitCheckEnable(): %d\r\n", err_code);
       }
     }

     if( err_code == VL53L0X_ERROR_NONE ) {
       err_code = VL53L0X_SetLimitCheckEnable( pMyDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, 1 );
       if(err_code != VL53L0X_ERROR_NONE) {
         CLS1_printf("ERROR: VL53L0X_SetLimitCheckEnable(): %d\r\n", err_code);
       }
     }

     if( err_code == VL53L0X_ERROR_NONE ) {
       err_code = VL53L0X_SetLimitCheckValue( pMyDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, (FixPoint1616_t)( 1.5 * 0.023 * 65536 ) );
       if(err_code != VL53L0X_ERROR_NONE) {
         CLS1_printf("ERROR: VL53L0X_SetLimitCheckValue(): %d\r\n", err_code);
       }
     }

#if 0
    uint16_t osc_calibrate_val=0;
    err_code = VL53L0X_RdWord(&MyDevice, VL53L0X_REG_OSC_CALIBRATE_VAL,&osc_calibrate_val);
    CLS1_printf("Calibrate value: %i\n",osc_calibrate_val);


    if (err_code == VL53L0X_ERROR_NONE) {
      err_code = VL53L0X_SetLimitCheckValue(pMyDevice,
          VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE,
          (FixPoint1616_t) (0.25 * 65536));
      if (err_code!=VL53L0X_ERROR_NONE) {
        CLS1_printf("ERROR: VL53L0X_SetLimitCheckValue() failed\r\n");
      }
    }

    if (err_code == VL53L0X_ERROR_NONE) {
      err_code = VL53L0X_SetLimitCheckValue(pMyDevice,
          VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE,
          (FixPoint1616_t) (18 * 65536));
      if (err_code!=VL53L0X_ERROR_NONE) {
        CLS1_printf("ERROR: VL53L0X_SetLimitCheckValue() failed\r\n");
      }
    }

    if (err_code == VL53L0X_ERROR_NONE) {
      err_code = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(pMyDevice, 200000);
      if (err_code!=VL53L0X_ERROR_NONE) {
        CLS1_printf("ERROR: VL53L0X_SetMeasurementTimingBudgetMicroSeconds() failed\r\n");
      }
    }
#endif
  } else {
    CLS1_printf("ERROR: Data Init Failed\r\n");
  }

  VL53L0X_RangingMeasurementData_t rangingData;

  for(;;) { /* main loop */
    err_code = VL53L0X_StartMeasurement(pMyDevice);
    if (err_code!=VL53L0X_ERROR_NONE) {
      CLS1_printf("ERROR: VL53L0X_StartMeasurement() failed\r\n");
    } else {
      do{
        WAIT1_Waitms(10);
      } while(!isMeasurementReady());

      err_code = VL53L0X_GetRangingMeasurementData(pMyDevice, &rangingData);
      if (err_code!=VL53L0X_ERROR_NONE) {
        CLS1_printf("ERROR: VL53L0X_GetRangingMeasurementData() failed\r\n");
      }
      err_code = VL53L0X_ClearInterruptMask(pMyDevice, 0);
      if (err_code!=VL53L0X_ERROR_NONE) {
        CLS1_printf("ERROR: VL53L0X_ClearInterruptMask() failed\r\n");
      }

      CLS1_printf("Range in MM: %d\r\n", rangingData.RangeMilliMeter);
    }
    LED1_Neg();
    WAIT1_Waitms(500);
  }
}

/*
 * Ultrasonic.c
 *
 *  Created on: Dec 30, 2012
 *      Author: Erich Styger
 *      Driver for the HC-SR04 and FRDM-KL25Z board
 */
#if 0
#include "Ultrasonic.h"
#include "TU_US.h"
#include "WAIT1.h"

typedef enum {
  ECHO_IDLE, /* device not used */
  ECHO_TRIGGERED, /* started trigger pulse */
  ECHO_MEASURE, /* measuring echo pulse */
  ECHO_OVERFLOW, /* measurement took too long */
  ECHO_FINISHED /* measurement finished */
} US_EchoState;

typedef struct {
  LDD_TDeviceData *trigDevice; /* device handle for the Trigger pin */
  LDD_TDeviceData *echoDevice; /* input capture device handle (echo pin) */
  volatile US_EchoState state; /* state */
  TU_US_TValueType capture; /* input capture value */
} US_DeviceType;

static US_DeviceType usDevice; /* device handle for the ultrasonic device */

void US_EventEchoOverflow(LDD_TUserData *UserDataPtr) {
  US_DeviceType *ptr = (US_DeviceType*)UserDataPtr;
  
  ptr->state = ECHO_OVERFLOW;
}

void US_EventEchoCapture(LDD_TUserData *UserDataPtr) {
  US_DeviceType *ptr = (US_DeviceType*)UserDataPtr;

  if (ptr->state==ECHO_TRIGGERED) { /* 1st edge, this is the raising edge, start measurement */
    TU_US_ResetCounter(ptr->echoDevice);
    ptr->state = ECHO_MEASURE;
  } else if (ptr->state==ECHO_MEASURE) { /* 2nd edge, this is the falling edge: use measurement */
    (void)TU_US_GetCaptureValue(ptr->echoDevice, 0, &ptr->capture);
    ptr->state = ECHO_FINISHED;
  }
}

static uint16_t calcAirspeed_dms(uint8_t temperatureCelsius) {
  /* Return the airspeed depending on the temperature, in deci-meter per second */
  unsigned int airspeed; /* decimeters per second */

  airspeed = 3313 + (6 * temperatureCelsius); /* dry air, 0% humidity, see http://en.wikipedia.org/wiki/Speed_of_sound */
  airspeed -= (airspeed/100)*17; /* factor in a relative humidity of ~40% */ 
  return airspeed;
}

uint16_t US_usToCentimeters(uint16_t microseconds, uint8_t temperatureCelsius) {
  return (microseconds*100UL)/calcAirspeed_dms(temperatureCelsius)/2; /* 2 because of two way */
}

/* measure and return the microseconds */
uint16_t US_Measure_us(void) {
  uint16_t us;
  
  /* send 10us pulse on TRIG line. */
  TRIG_SetVal(usDevice.trigDevice);
  WAIT1_Waitus(10);
  usDevice.state = ECHO_TRIGGERED;
  TRIG_ClrVal(usDevice.trigDevice);
  while(usDevice.state!=ECHO_FINISHED) {
    /* measure echo pulse */
    if (usDevice.state==ECHO_OVERFLOW) { /* measurement took too long? */
      usDevice.state = ECHO_IDLE;
      return 0; /* no echo, error case */
    }
  }
  us = (usDevice.capture*1000UL)/(TU_US_CNT_INP_FREQ_U_0/1000);
  return us;
}

void US_Init(void) {
  usDevice.state = ECHO_IDLE;
  usDevice.capture = 0;
  usDevice.trigDevice = TRIG_Init(NULL);
  usDevice.echoDevice = TU_US_Init(&usDevice);
}
#endif

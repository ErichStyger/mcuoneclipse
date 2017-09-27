/**
 * \file
 * \brief This is the implementation of the Ultrasonic HC-SR04 module driver.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_HAS_ULTRASONIC
#include "Ultrasonic.h"
#include "TU_US.h"
#include "WAIT1.h"
#include "TRIG.h"
#include "UTIL1.h"
#include "FRTOS1.h"

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
  uint16_t lastValue_us; /* last captured echo, in us */
  US_SignalState signalState; /* state of measurement */
} US_DeviceType;

static US_DeviceType usDevice; /* device handle for the ultrasonic device */
static xSemaphoreHandle mutexHandle;

void US_EventEchoOverflow(LDD_TUserData *UserDataPtr) {
  US_DeviceType *ptr = (US_DeviceType*)UserDataPtr;
  
  ptr->state = ECHO_OVERFLOW;
  (void)TU_US_Disable(usDevice.echoDevice);
}

void US_EventEchoCapture(LDD_TUserData *UserDataPtr) {
  US_DeviceType *ptr = (US_DeviceType*)UserDataPtr;

  if (ptr->state==ECHO_TRIGGERED) { /* 1st edge, this is the raising edge, start measurement */
    (void)TU_US_ResetCounter(ptr->echoDevice);
    ptr->state = ECHO_MEASURE;
  } else if (ptr->state==ECHO_MEASURE) { /* 2nd edge, this is the falling edge: use measurement */
    (void)TU_US_GetCaptureValue(ptr->echoDevice, 0, &ptr->capture);
    ptr->state = ECHO_FINISHED;
    (void)TU_US_Disable(usDevice.echoDevice);
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
  int timeout;
  
  (void)FRTOS1_xSemaphoreTake(mutexHandle, portMAX_DELAY);
  usDevice.signalState = US_SIGNAL_OK; /* default state */
  /* send 10us pulse on TRIG line. */
  TRIG_SetVal(usDevice.trigDevice);
  WAIT1_Waitus(10);
  usDevice.state = ECHO_TRIGGERED;
  (void)TU_US_Enable(usDevice.echoDevice);
  TRIG_ClrVal(usDevice.trigDevice);
  timeout = 30; /* timout in ms */
  while(usDevice.state!=ECHO_FINISHED) {
    /* measure echo pulse */
    if (usDevice.state==ECHO_OVERFLOW) { /* measurement took too long? */
      usDevice.signalState =  US_SIGNAL_NO_ECHO;
      break; /* no echo, error case */
    }
    WAIT1_WaitOSms(1);
    timeout--;
    if (timeout==0) {
      usDevice.signalState = US_SIGNAL_TIMEOUT;
      break;
    }
  } /* while */
  if (usDevice.state==ECHO_FINISHED) {
    usDevice.lastValue_us = (usDevice.capture*1000UL)/(TU_US_CNT_INP_FREQ_U_0/1000);
    usDevice.signalState = US_SIGNAL_OK;
  } else {
    usDevice.lastValue_us = 0; /* error case */
  }
  usDevice.state = ECHO_IDLE;
  (void)FRTOS1_xSemaphoreGive(mutexHandle);
  return usDevice.lastValue_us;
}

uint16_t US_GetLastCentimeterValue(void) {
  return US_usToCentimeters(usDevice.lastValue_us, 22);
}

#if PL_CONFIG_HAS_SHELL
static void US_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"ultrasonic", (unsigned char*)"Group of ultrasonic commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows radio help or status\r\n", io->stdOut);
}

static const uint8_t *SignalStateToStr(US_SignalState state) {
  switch(state) {
    case US_SIGNAL_OK: return (const unsigned char*)"OK";
    case US_SIGNAL_NO_ECHO: return (const unsigned char*)"NO_ECHO";
    case US_SIGNAL_TIMEOUT: return (const unsigned char*)"TIMEOUT";
    default:
      break;
  }
  return (const unsigned char*)"Unknown?";
}

static void US_PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[16];
  uint16_t cm, us;
  
  us = US_Measure_us();
  cm = US_usToCentimeters(us, 22);
  CLS1_SendStatusStr((unsigned char*)"ultrasonic", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  state", SignalStateToStr(usDevice.signalState), io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  UTIL1_Num16uToStr(buf, sizeof(buf), usDevice.lastValue_us);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  us", buf, io->stdOut);
  UTIL1_Num16uToStr(buf, sizeof(buf), cm);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  cm", buf, io->stdOut);
}

uint8_t US_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"ultrasonic help")==0) {
    US_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"ultrasonic status")==0) {
    US_PrintStatus(io);
    *handled = TRUE;
  }
  return res;
}
#endif

void US_Deinit(void) {
   TRIG_Deinit(usDevice.trigDevice);
   TU_US_Deinit(usDevice.echoDevice);
}

void US_Init(void) {
  usDevice.state = ECHO_IDLE;
  usDevice.capture = 0;
  usDevice.trigDevice = TRIG_Init(NULL);
  usDevice.echoDevice = TU_US_Init(&usDevice);
  mutexHandle = FRTOS1_xSemaphoreCreateMutex();
  if (mutexHandle==NULL) {
    for(;;);
  }
}
#endif /* PL_HAS_ULTRASONIC */

/*
 * Sumo.c
 *
 *  Created on: Aug 30, 2013
 *      Author: Erich Styger
 */
#include "Platform.h"
#if PL_APP_SUMO
#include "Sumo.h"
#include "Motor.h"
#include "Reflectance.h"
#include "Turn.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#include "WAIT1.h"
#include "Event.h"
#if PL_HAS_USER_LED
  #include "LED1.h"
  #include "LED2.h"
#endif
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif
#if PL_HAS_ACCEL_SENSOR
  #include "MMA1.h"
#endif
#if PL_HAS_ULTRASONIC
  #include "Ultrasonic.h"
#endif
#if PL_HAS_DISTANCE_SENSOR
  #include "Distance.h"
#endif
#if PL_HAS_DRIVE
  #include "Drive.h"
#endif
#if PL_HAS_QUADRATURE
  #include "Q4CLeft.h"
  #include "Q4CRight.h"
#endif
#if PL_HAS_DISTANCE_SENSOR
  #include "Distance.h"
#endif
#if PL_CONFIG_HAS_NVM_CONFIG
  #include "NVM_Config.h"
#endif
#if PL_HAS_LASER
  #include "Laser.h"
#endif
#if PL_HAS_MUSIC_SHIELD
  #include "Music.h"
#endif
#include "Shell.h"
#include "Application.h"
#include "Tacho.h"

/* direct task notification bits */
#define SUMO_START_SUMO (1<<0)  /* start sumo mode */
#define SUMO_STOP_SUMO  (1<<1)  /* stop stop sumo */
static TaskHandle_t sumoTaskHndl;

#if PL_HAS_DISTANCE_SENSOR
  static bool sumoRadar = FALSE;
  static bool useDistanceSensor = TRUE;
  static bool sumoStartFirstTurnLeft = TRUE;
#else
  static const bool useDistanceSensor = FALSE;
#endif

/* debug information */
#define PRINT_AIM_INFO    (0 && PL_CONFIG_HAS_SHELL)
#define PRINT_STATE_INFO  (0 && PL_CONFIG_HAS_SHELL)

/* configuration options */
#define SUMO_STRATEGY            (1) /* 0 or 1 */
#define SUMO_SEARCH_OBJECT_TOF   (1 && PL_HAS_TOF_SENSOR)
#define SUMO_SEARCH_OBJECT_US    (1 && PL_HAS_ULTRASONIC)
#define SUMO_SEARCH_OBJECT_IR    (1 && PL_HAS_FRONT_DISTANCE)
#define SUMO_SEARCH_OBJECT_LASER (1 && PL_HAS_LASER)
#define SUMO_SEARCH_OBJECT       (SUMO_SEARCH_OBJECT_US || SUMO_SEARCH_OBJECT_IR || SUMO_SEARCH_OBJECT_LASER || SUMO_SEARCH_OBJECT_TOF)
#define SUMO_SEARCH_SIDE_OBJECT  (0 && PL_HAS_DISTANCE_SENSOR)
#define SUMO_SPIN_AROUND         (0) /* spin around in the middle */
#define SUMO_CHECK_ACCEL         (PL_HAS_ACCEL_STOP) /* checking accelerometer to stop */
#define SUMO_HAS_DROP_BLADE      (0 && (PL_IS_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_K22_V2)) /* drop down blade in front */
#define TASK_DELAY_MS            (5) /* delay time of task, defines frequency */
#define SUMO_TURN_TIMEOUT_MOVE_TO_POS  1000 /* timeout for move */

#if SUMO_STRATEGY==1
#if PL_IS_MOTOR_1_100
  #define SUMO_CONFIG_MAX_DUTY       100
#else
  #if PL_HAS_MOTOR_TACHO
  #if PL_HAS_HIGH_RES_ENCODER
    #if PL_SLOWER_SPEED
      #define SUMO_CONFIG_SPEED_DRIVE_STEPS       1000 /* steps per second for normal drive */
      #define SUMO_CONFIG_SPEED_CHASE_STEPS       2000 /* steps per second for chase drive */
    #else
      #define SUMO_CONFIG_SPEED_DRIVE_STEPS       3000 /* steps per second for normal drive */
      #define SUMO_CONFIG_SPEED_CHASE_STEPS       6000 /* steps per second for chase drive */
    #endif
  #else /* slow speed encoder */
    #if PL_SLOWER_SPEED
      #define SUMO_CONFIG_SPEED_DRIVE_STEPS       40 /* steps per second for normal drive */
      #define SUMO_CONFIG_SPEED_CHASE_STEPS       80 /* steps per second for chase drive */
    #else
      #define SUMO_CONFIG_SPEED_DRIVE_STEPS       100 /* steps per second for normal drive */
      #define SUMO_CONFIG_SPEED_CHASE_STEPS       200 /* steps per second for chase drive */
    #endif
  #endif
  #if PL_HAS_DROP_BLADE
    #define SUMO_CONFIG_SPEED_DROP_BLADE_STEPS    10000 /* steps per second for dropping blade */
  #endif
  #else
  #define SUMO_CONFIG_MAX_DUTY       60 /* max duty % */
  #endif
#endif
  #define SUMO_CONFIG_BEEP_FREQ_ADD  500
  #define SUMO_CONFIG_ANGLE_STRAIGHT 120 /* if left or right sensor on edge */
  //#define SUMO_CONFIG_ANGLE_EDGE      90 
  //#define SUMO_CONFIG_ANGLE_NONE     160
  //#define SUMO_CONFIG_ANGLE_DEFAULT  120  
#else /* 1 */
#if PL_IS_MOTOR_1_100
  #define SUMO_CONFIG_MAX_DUTY       100
#else
  #define SUMO_CONFIG_MAX_DUTY        45
#endif
  #define SUMO_CONFIG_BEEP_FREQ_ADD  200
  #define SUMO_CONFIG_ANGLE_STRAIGHT 170 
  //#define SUMO_CONFIG_ANGLE_EDGE     120 /* if left or right sensor on edge */
  //#define SUMO_CONFIG_ANGLE_NONE     130 
  //#define SUMO_CONFIG_ANGLE_DEFAULT  110  
#endif

static bool SUMO_doRunSumo = FALSE; /* if we are running in sumo mode */
#if PL_HAS_MOTOR_TACHO
static int16_t SUMO_SpeedDriveSteps = SUMO_CONFIG_SPEED_DRIVE_STEPS;
static int16_t SUMO_SpeedChaseSteps = SUMO_CONFIG_SPEED_CHASE_STEPS;
#else
static MOT_SpeedPercent SUMO_SpeedDriveDuty = SUMO_CONFIG_MAX_DUTY;
static MOT_SpeedPercent SUMO_SpeedChaseDuty = SUMO_CONFIG_MAX_DUTY;
#endif
#define SUMO_NO_COUNTDOWN_MS  -1
static int16_t SUMO_countDownMs = SUMO_NO_COUNTDOWN_MS; /* -1 means no countdown */

#if SUMO_SEARCH_OBJECT_US
  #define DELAY_TIME_BETWEEN_PING   30 /* 29 ms should be the shortest delay between pings? */
  static const uint16_t SUMO_PingDelay = DELAY_TIME_BETWEEN_PING;

  #define SUMO_OSTACLE_DISTANCE 40
  static uint16_t SUMO_AimRadiusCm = SUMO_OSTACLE_DISTANCE; /* aiming radius in cm */
#else
  static uint16_t SUMO_AimRadiusCm = 50; /* aiming radius in cm */
#endif

#if PL_HAS_DISTANCE_SENSOR/* alias for ToF sensors behind blade */
  #define DIST_SENSOR_FRONT_FAR_LEFT     DIST_SENSOR_FRONT
  #define DIST_SENSOR_FRONT_LEFT         DIST_SENSOR_LEFT
  #define DIST_SENSOR_FRONT_RIGHT        DIST_SENSOR_RIGHT
  #define DIST_SENSOR_FRONT_FAR_RIGHT    DIST_SENSOR_REAR
#endif

typedef enum {
  SUMO_STATE_IDLE,
#if PL_HAS_DISTANCE_SENSOR
  SUMO_STATE_START_SEARCH,
  SUMO_STATE_SEARCH,
  SUMO_STATE_START_CHASE,
  SUMO_STATE_CHASE,
#endif
  SUMO_STATE_START_DRIVE,
  SUMO_STATE_CHECK_BORDER,
  SUMO_STATE_DRIVE,
  SUMO_STATE_MOVE_AWAY,
  SUMO_STATE_OUTSIDE
} SUMO_StateKinds;

static SUMO_StateKinds SUMO_State = SUMO_STATE_IDLE;

static unsigned char *SUMO_StatusStr(SUMO_StateKinds kind) {
  switch(kind) {
    case SUMO_STATE_IDLE:           return (unsigned char*)"IDLE";
#if PL_HAS_DISTANCE_SENSOR
    case SUMO_STATE_START_SEARCH:   return (unsigned char*)"START_SEARCH";
    case SUMO_STATE_SEARCH:         return (unsigned char*)"SEARCH";
    case SUMO_STATE_START_CHASE:    return (unsigned char*)"START_CHASE";
    case SUMO_STATE_CHASE:          return (unsigned char*)"CHASE";
#endif
    case SUMO_STATE_START_DRIVE:    return (unsigned char*)"START_DRIVE";
    case SUMO_STATE_CHECK_BORDER:   return (unsigned char*)"CHECK_BORDER";
    case SUMO_STATE_DRIVE:          return (unsigned char*)"DRIVE";
    case SUMO_STATE_MOVE_AWAY:      return (unsigned char*)"MOVE_AWAY";
    case SUMO_STATE_OUTSIDE:        return (unsigned char*)"OUTSIDE";
    default: return (unsigned char*)"UNKNOWN";
  } /* switch */
}

#if PL_HAS_DISTANCE_SENSOR
void SUMO_StartTurnLeft(void) {
  sumoStartFirstTurnLeft = TRUE;
}

void SUMO_StartTurnRight(void) {
  sumoStartFirstTurnLeft = FALSE;
}

void SUMO_RadarOn(void) {
  sumoRadar = TRUE;
}

void SUMO_RadarOff(void) {
  sumoRadar = FALSE;
}
#endif

static void SUMO_ChangeRunSumo(bool runIt) {
  if (runIt != SUMO_doRunSumo) {
    /* value changed */
  #if PL_CONFIG_HAS_NVM_CONFIG
    uint16_t val;
    
    if (runIt) {
      val = 1; /* enable */
    } else {
      val = 0; /* disable */
    }
    (void)NVMC_SaveSumoData(&val, sizeof(val));
  #endif  
    SUMO_doRunSumo = runIt;
  }
}

bool SUMO_IsDoingSumo(void) {
  return SUMO_doRunSumo || SUMO_countDownMs>=0;
}

void SUMO_StartCountdown(void) {
#if PL_HAS_USER_LED
  LED1_Off();
#endif
  SUMO_countDownMs = 5000; /* 5 seconds countdown */
}

void SUMO_StartSumo(void) {
  (void)xTaskNotify(sumoTaskHndl, SUMO_START_SUMO, eSetBits);
}

void SUMO_StopSumo(void) {
  (void)xTaskNotify(sumoTaskHndl, SUMO_STOP_SUMO, eSetBits);
}

void SUMO_StartStopSumo(void) {
  if (SUMO_IsDoingSumo()) {
    SUMO_StopSumo();
  } else {
    SUMO_StartSumo();
  }
}

#if PL_HAS_DISTANCE_SENSOR
static void RadarDistance(void) {
  int16_t mm;
  uint16_t freq = 0;
  int16_t minDist = 0x7fff;
  uint16_t ms = 100;

  mm = DIST_GetDistance(DIST_SENSOR_FRONT_FAR_LEFT);
  if (mm>0 && mm<=SUMO_AimRadiusCm*10) {
#if PRINT_AIM_INFO
    SHELL_SendString((uint8_t*)"farLeft ");
#endif
    freq += 200;
    if (mm<minDist) {
      minDist = mm;
    }
  }
  mm = DIST_GetDistance(DIST_SENSOR_FRONT_LEFT);
  if (mm>0 && mm<=SUMO_AimRadiusCm*10) {
#if PRINT_AIM_INFO
    SHELL_SendString((uint8_t*)"Left ");
#endif
    freq += 200;
    if (mm<minDist) {
      minDist = mm;
    }
  }
  mm = DIST_GetDistance(DIST_SENSOR_FRONT_RIGHT);
  if (mm>0 && mm<=SUMO_AimRadiusCm*10) {
#if PRINT_AIM_INFO
    SHELL_SendString((uint8_t*)"Right ");
#endif
    freq += 200;
    if (mm<minDist) {
      minDist = mm;
    }
  }
  mm = DIST_GetDistance(DIST_SENSOR_FRONT_FAR_RIGHT);
  if (mm>0 && mm<=SUMO_AimRadiusCm*10) {
#if PRINT_AIM_INFO
    SHELL_SendString((uint8_t*)"farRight ");
#endif
    freq += 200;
    if (mm<minDist) {
      minDist = mm;
    }
  }
  if (freq>0) {
#if PRINT_AIM_INFO
    {
      uint8_t buf[16];

      UTIL1_Num16sToStr(buf, sizeof(buf), minDist);
      UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"mm\r\n");
      SHELL_SendString(buf);
    }
#endif
    ms = UTIL1_map(minDist, 0, 600, 0, 100);
    BUZ_Beep(freq, ms);
  }
  vTaskDelay(pdMS_TO_TICKS(ms));
}
#endif

#if PL_HAS_DISTANCE_SENSOR
/*!
 * \brief Returns TRUE if there is an obstacle in drive sight
 */
static bool SUMO_ObstacleInFrontSight(uint16_t dist_cm, DIST_Sensor *flags) {
  DIST_Sensor d;
  if (!useDistanceSensor) {
    return FALSE;
  }
  d = 0;
#if SUMO_SEARCH_OBJECT_TOF
  int16_t mm;

  mm = DIST_GetDistance(DIST_SENSOR_FRONT_FAR_LEFT);
  if (mm>0 && mm<=dist_cm*10) {
    d |= DIST_SENSOR_FRONT_FAR_LEFT;
  }
  mm = DIST_GetDistance(DIST_SENSOR_FRONT_LEFT);
  if (mm>0 && mm<=dist_cm*10) {
    d |= DIST_SENSOR_FRONT_LEFT;
  }
  mm = DIST_GetDistance(DIST_SENSOR_FRONT_RIGHT);
  if (mm>0 && mm<=dist_cm*10) {
    d |= DIST_SENSOR_FRONT_RIGHT;
  }
  mm = DIST_GetDistance(DIST_SENSOR_FRONT_FAR_RIGHT);
  if (mm>0 && mm<=dist_cm*10) {
    d |= DIST_SENSOR_FRONT_FAR_RIGHT;
  }
  *flags = d;
  return d!=0;
#elif SUMO_SEARCH_OBJECT_LASER
  bool isLeft, isRight;

  LASER_LeftRightStatus(&isLeft, &isRight);
#if PL_HAS_MUSIC_LASER_LEFT || PL_HAS_MUSIC_LASER_RIGHT || PL_HAS_MUSIC_LASER_BOTH
  if (!MUSIC_IsPlaying()) {
    if (isLeft && isRight) {
#if PL_HAS_MUSIC_LASER_BOTH
      MUSIC_PlayTheme(MUSIC_THEME_LASER_BOTH);
#endif
    } else if (isLeft) {
#if PL_HAS_MUSIC_LASER_LEFT
    MUSIC_PlayTheme(MUSIC_THEME_LASER_LEFT);
#endif
    } else if (isRight) {
#if PL_HAS_MUSIC_LASER_RIGHT
    MUSIC_PlayTheme(MUSIC_THEME_LASER_RIGHT);
#endif
    }
  }
#endif
  return isLeft || isRight;
#elif SUMO_SEARCH_OBJECT_IR
  uint8_t val;

  val = DIST_GetSensorBitsMiddle();
  if (val&DIST_IR_MIDDLE) {
    return TRUE; /* heading to object */
  }
  val = DIST_GetSensorBitsRight();
  if (val&DIST_IR_MIDDLE) {
    return TRUE; /* heading to object */
  }
  val = DIST_GetSensorBitsLeft();
  if (val&DIST_IR_MIDDLE) {
    return TRUE; /* heading to object */
  }
  return FALSE;
#elif SUMO_SEARCH_OBJECT_US
  uint16_t cm;
  bool inRange;

  cm = US_usToCentimeters(US_Measure_us(), 22);
  inRange = cm!=0 && cm<=dist_cm;
  WAIT1_WaitOSms(SUMO_PingDelay);
  return inRange;
#else
  (void)dist_cm;
  return FALSE;
#endif /* SUMO_SEARCH_OBJECT_TOF */
}
#endif

#if SUMO_SEARCH_OBJECT_IR
static bool SUMO_AimObstacleIR(void) {
#if PL_HAS_FRONT_DISTANCE
  uint8_t val;
  
#if !PL_HAS_QUADRATURE
  DRV_SetMode(DRV_MODE_NONE);
#endif
  for(;;) { /* will break */
    /* check sensors with a beam in the middle */
    val = DIST_GetSensorBitsMiddle();
    if (val&DIST_IR_MIDDLE) {
      break; /* we receive signal in the middle: go on! */
    }
    /* check right side */
    val = DIST_GetSensorBitsRight();
    if (val==(DIST_IR_RIGHT)) { /* sensor on the right outer side is on */
      SHELL_SendString((unsigned char*)"right 40");
      TURN_TurnAngle(60); /* turn right */
      break;
    }
    if (val==(DIST_IR_MIDDLE|DIST_IR_RIGHT)) { /* sensor on the right outer side is on */
      TURN_TurnAngle(40); /* turn right */
      break;
    }
    if (val==(DIST_IR_LEFT|DIST_IR_MIDDLE|DIST_IR_RIGHT)) { /* sensor on the right outer side is on */
      TURN_TurnAngle(25); /* turn right */
      break;
    }
    if (val==(DIST_IR_LEFT|DIST_IR_MIDDLE)) { /* sensor on the left side is on */
      TURN_TurnAngle(-40); /* turn left */
      break;
    }
    /* check left side */
    val = DIST_GetSensorBitsLeft();
    if (val==(DIST_IR_LEFT)) { /* sensor on the left outer side is on */
      TURN_TurnAngle(-60); /* turn left */
      break;
    }
    if (val==(DIST_IR_LEFT|DIST_IR_MIDDLE)) { /* sensor on the left outer side is on */
      TURN_TurnAngle(-40); /* turn left */
      break;
    }
    if (val==(DIST_IR_LEFT|DIST_IR_MIDDLE|DIST_IR_RIGHT)) { /* sensor on the left outer side is on */
      TURN_TurnAngle(-25); /* turn left */
      break;
    }
    if (val==(DIST_IR_MIDDLE|DIST_IR_RIGHT)) { /* sensor on the left side is on */
      TURN_TurnAngle(40); /* turn left */
      break;
    }
    val = 0;
    break;
  }
  if (val!=0) {
    uint8_t buf[32];

    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"found: ");
    UTIL1_strcatNum8u(buf, sizeof(buf), val);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    SHELL_SendString(buf);
    return TRUE; /* found object */
  } else {
    SHELL_SendString((unsigned char*)"NOT found\r\n");
  }
#endif
  return FALSE; /* object not found */
}
#endif

#if SUMO_SEARCH_OBJECT
typedef enum {
  SUMO_AIM_CENTER_LEFT,   /* aim to center turning left */
  SUMO_AIM_CENTER_RIGHT,  /* aim to center turning left */
  SUMO_AIM_RIGHT,         /* aim to object turning right */
  SUMO_AIM_LEFT,          /* aim to object turning left */
} SUMO_AimType;

/*!
 * \brief Aims at an obstacle which has to be within the distance
 * \param distance Scan distance where to search for object
 * \param aimType Defines if the aiming pattern
 * \return TRUE if object has been found, FALSE otherwise.
 */
#if PL_HAS_HIGH_RES_ENCODER
  #define ANGLE_STEPS   ((4*750)/36)  /* 750 steps for 90° */
#else
  #define ANGLE_STEPS   ((4*34)/36)  /* 34 steps for 90° */
#endif
static bool SUMO_AimObstacle(uint16_t dist_cm, SUMO_AimType aimType, int16_t leftAngle, int16_t rightAngle) {
  int16_t minAngle, maxAngle, angle, backAngle;
  bool found;
  bool inRange;
  int32_t posLeft, posRight;
  #define AIM_ANGLE_INC  10
#if PRINT_AIM_INFO
  unsigned char buf[24];
#endif
  bool turnLeft;
  DIST_Sensor distFlags;
  
  if (!useDistanceSensor) {
    return FALSE;
  }
  minAngle = 360+1;
  maxAngle = -1;
  posLeft = Q4CLeft_GetPos();
  posRight = Q4CRight_GetPos();
  found = FALSE;
  inRange = FALSE;
  turnLeft = leftAngle<0 && (aimType==SUMO_AIM_RIGHT || aimType==SUMO_AIM_CENTER_RIGHT); /* if starting range is on the left (<0), then turn first left, then right */
  for(angle=0;angle<=rightAngle && angle >= leftAngle;) {
    if (SUMO_ObstacleInFrontSight(dist_cm, &distFlags)) { /* stop turning if we see something */
      found |= TRUE;
      inRange = TRUE;
      if (   ((aimType==SUMO_AIM_RIGHT || aimType==SUMO_AIM_LEFT) && ((distFlags&(DIST_SENSOR_LEFT|DIST_SENSOR_FRONT|DIST_SENSOR_RIGHT))!=0))
          || ((aimType==SUMO_AIM_CENTER_RIGHT || aimType==SUMO_AIM_CENTER_LEFT) && ((distFlags&(DIST_SENSOR_LEFT|DIST_SENSOR_RIGHT))==(DIST_SENSOR_LEFT|DIST_SENSOR_RIGHT)))
         )
      {
        break; /* found it! Get out of for loop */
      }
    } /* if */
#if PRINT_AIM_INFO
    buf[0] = '\0';
#endif
    if (inRange) { /* object in range! */
      if (angle<minAngle) {
        minAngle = angle; /* remember min angle */
#if PRINT_AIM_INFO
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"min ");
#endif
      }
      if (angle>maxAngle) {
        maxAngle = angle; /* remember max angle */
#if PRINT_AIM_INFO
       UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"max ");
#endif
      }
    }
#if PRINT_AIM_INFO
    UTIL1_strcatNum16s(buf, sizeof(buf), angle);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"° ");
    UTIL1_strcatNum16s(buf, sizeof(buf), dist_cm);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" cm\r\n");
    SHELL_SendString(buf);
#endif
    if (!inRange) {
      if (minAngle<=maxAngle) { /* scanned object */
        break;
      }
    }
    if (inRange && (aimType==SUMO_AIM_LEFT || aimType==SUMO_AIM_RIGHT)) {
      break; /* only want to aim at edge of object (or to object if already aiming at it) */
    }
    if (turnLeft) {
      posLeft -= ANGLE_STEPS; /* turn left */
      posRight += ANGLE_STEPS;
      angle -= AIM_ANGLE_INC;
    } else { /* turn left */
      posLeft += ANGLE_STEPS; /* turn right */
      posRight -= ANGLE_STEPS;
      angle += AIM_ANGLE_INC;
    }
    TURN_MoveToPos(posLeft, posRight, TRUE, NULL, SUMO_TURN_TIMEOUT_MOVE_TO_POS);
#if SUMO_SEARCH_OBJECT_US
    WAIT1_WaitOSms(SUMO_PingDelay);
#endif
    if (turnLeft && angle <= leftAngle && (aimType==SUMO_AIM_RIGHT || aimType==SUMO_AIM_CENTER_RIGHT)) {
      turnLeft = FALSE; /* going to the right */
    } else if (!turnLeft && angle >= rightAngle && (aimType==SUMO_AIM_LEFT || aimType==SUMO_AIM_CENTER_LEFT)) {
      turnLeft = TRUE;
    }
  } /* for */
  if (!found) {
#if PRINT_AIM_INFO
    SHELL_SendString((unsigned char*)"NOT found!\r\n");
#endif
    return FALSE; /* not found */
  }
  if (SUMO_ObstacleInFrontSight(dist_cm, &distFlags)) {
#if PRINT_AIM_INFO
    SHELL_SendString((unsigned char*)"found it!\r\n");
#endif
    return TRUE; /* found it! */
  }
  /* have found object! */
  if (aimType==SUMO_AIM_CENTER_LEFT || aimType==SUMO_AIM_CENTER_RIGHT) {
    /* determine angle to focus object in the middle */
    backAngle = ((angle-maxAngle)+(maxAngle-minAngle)/2);
    if (aimType==SUMO_AIM_CENTER_LEFT) {
      backAngle = -backAngle; /* invert turning direction */
    }
#if PRINT_AIM_INFO
    buf[0] = '\0';
    UTIL1_strcatNum16s(buf, sizeof(buf), backAngle);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"° turn\r\n");
    SHELL_SendString(buf);
#endif
    if (angle>=maxAngle) {
      TURN_TurnAngle(-backAngle, NULL); /* turn back left to the middle */
    } else {
      TURN_TurnAngle(backAngle, NULL); /* turn back right to the middle */
    }
  }
  return TRUE; /* found it! */
}

#if 0
static bool SUMO_ObstacleInDriveSight(uint16_t dist_cm, bool turnToLeft) {
  int i;
  int32_t posLeft, posRight;
  bool isDriving;
  DIST_Sensor distFlags;

  isDriving = TRUE; /* we are driving here */
  posLeft = Q4CLeft_GetPos();
  posRight = Q4CRight_GetPos();
  for(i=0;i<5;i++) {
    if (SUMO_ObstacleInFrontSight(dist_cm, &distFlags)) {
      if (!isDriving) {
        DRV_SetMode(DRV_MODE_SPEED); /* back to drive mode */
      }
      return TRUE; /* still see object */
    }
    /* lost it: turn to try to find it again */
    if (turnToLeft) {
      posLeft -= ANGLE_STEPS;
      posRight += ANGLE_STEPS;
    } else {
      posLeft += ANGLE_STEPS;
      posRight -= ANGLE_STEPS;
    }
    TURN_MoveToPos(posLeft, posRight, FALSE, NULL, SUMO_TURN_TIMEOUT_MOVE_TO_POS);
    isDriving = FALSE; /* TURN_MoveToPos() has put us into POSITION mode */
  }
  if (!isDriving) {
    DRV_SetMode(DRV_MODE_SPEED); /* back to drive mode */
  }
  return FALSE; /* not in sight any more */
}
#endif
#endif

#if SUMO_SPIN_AROUND
static portTickType lastTurnTickCount = 0;
#endif

#if SUMO_SPIN_AROUND
static bool SUMO_CheckForSpin(void) {
  portTickType tickCount, delta;
  
  tickCount = FRTOS1_xTaskGetTickCount();
  delta = tickCount-lastTurnTickCount;
  if (delta > (1200/portTICK_PERIOD_MS) && delta < (1800/portTICK_PERIOD_MS)) {
    MoveBackOnBoarder();
    SUMU_TurnAngle(360); /* spin around */
    lastTurnTickCount = tickCount;
    return TRUE; /* turning */
  } else if (delta > (2500/portTICK_PERIOD_MS)) {
    lastTurnTickCount = tickCount;
  }
  return FALSE; /* not turning */
}

static void SUMO_OnTurnFinished(void) {
  lastTurnTickCount = xTaskGetTickCount();
}
#endif

#if SUMO_CHECK_ACCEL
static bool RobotIsOutside(void) {
  int16_t mg;
  static uint16_t mg_cnt = 0;
#if 0
  unsigned char buf[16];
#endif
  #define TILT_VALUE_Z_MG   500 /* threshold value */
  #define TILT_DURATION_MS  400 /* must be tilted for that long */
#endif
#if SUMO_CHECK_ACCEL
      mg = MMA1_GetZmg();
#if 0 /* debug output */
      buf[0] = '\0';
      UTIL1_strcatNum16s(buf, sizeof(buf), mg);
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
      SHELL_SendString(buf);
#endif
#if PL_IS_INTRO_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_K22_V2 || PL_IS_INTRO_ZUMO_K22 /* board normal position */
      if (mg<TILT_VALUE_Z_MG) {
#elif (PL_IS_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT2) /* FRDM board is upside-down. Normal would be -1000 mg on Z */
      if (mg>-TILT_VALUE_Z_MG) {
#else
      if (0) {
       #error "verify correct board orientation!"
#endif
        mg_cnt++;
        if (mg_cnt>(TILT_DURATION_MS/TASK_DELAY_MS)) { /* fallen of sumo area? At least for given time? */
          mg_cnt = 0; /* reset counter */
          SUMO_Stop(); /* stop! */
        }
      } else if (mg_cnt>0) {
        mg_cnt--;
      }
  return FALSE;
}
#endif

static void SUMO_SetNextState(SUMO_StateKinds next) {
  SUMO_State = next;
#if PRINT_STATE_INFO
  SHELL_SendString(SUMO_StatusStr(next));
  SHELL_SendString((unsigned char*)"\r\n");
#endif
}

#if SUMO_HAS_DROP_BLADE
static void DropBlade(void) {
  /* move forward fast and then stop to drop the blade */
#if !PL_HAS_QUADRATURE
    uint8_t oldDuty;

    oldDuty = TURN_SetDutyPercent(100); /* full speed */
#endif /* PL_HAS_QUADRATURE */
#if PL_HAS_DRIVE
#if PL_HAS_DROP_BLADE
    DRV_SetSpeed(SUMO_CONFIG_SPEED_DROP_BLADE_STEPS, SUMO_CONFIG_SPEED_DROP_BLADE_STEPS);
    DRV_SetMode(DRV_MODE_SPEED); /* enable drive mode */
    WAIT1_WaitOSms(200);
    DRV_SetMode(DRV_MODE_STOP);
#endif
#if PL_HAS_QUADRATURE
    DRV_SetSpeed(SUMO_CONFIG_SPEED_DRIVE_STEPS, SUMO_CONFIG_SPEED_DRIVE_STEPS);
    WAIT1_WaitOSms(100);
#endif
#else
    //DRV_SetMode(DRV_MODE_NONE); /* needed for turn */
    TURN_Turn(TURN_STEP_LINE_FW, NULL);
#endif /* PL_HAS_DRIVE */
#if !PL_HAS_QUADRATURE
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
    MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
    WAIT1_WaitOSms(200);
    (void)TURN_SetDutyPercent(oldDuty); /* restore old duty */
#endif /* PL_HAS_QUADRATURE */
}
#endif

#if PL_HAS_DISTANCE_SENSOR
typedef enum {
  LAST_POS_UNKNOWN, LAST_POS_ON_THE_LEFT, LAST_POS_ON_THE_RIGHT, LAST_POS_ON_THE_FRONT
} SUMO_LastPosition_e;

static bool SearchOpponent(void) {
  DIST_Sensor distFlags;

  if (SUMO_ObstacleInFrontSight(SUMO_AimRadiusCm, &distFlags)) {
    return TRUE;
  }
  return FALSE; /* do not stop */
}

static bool SUMO_TurnAndSearchOpponent(int16_t angle, SUMO_LastPosition_e lastPos) {
  DIST_Sensor distFlags;

  if (lastPos==LAST_POS_ON_THE_LEFT) {
    if (angle>0) { /* angle is to the right? */
      angle = -angle; /* make it negative, search on the left */
    }
  } else if (lastPos==LAST_POS_ON_THE_RIGHT) {
    if (angle<0) { /* angle is to the left? */
      angle = 90; /* make it positive, search on the right */
    }
  }
  TURN_TurnAngle(angle, SearchOpponent); /* left turn */
  if (SUMO_ObstacleInFrontSight(SUMO_AimRadiusCm, &distFlags)) {
    return TRUE; /* found something! */
  }
  return FALSE; /* not found */
}
#endif

#if PL_HAS_DISTANCE_SENSOR
/*!
 * \brief Change speed based on distance sensor/object postion
 * \return FALSE if object is lost, TRUE if object is still visible
 */
static bool SUMO_UpdateChaseSpeed(SUMO_LastPosition_e *lastOpponentPos) {
  DIST_Sensor distFlags;
#if PL_SLOWER_SPEED
  #define SPEED_OFFSET_SMALL   500
  #define SPEED_OFFSET_MEDIUM 1000
  #define SPEED_OFFSET_LARGE  1500
#else
  #define SPEED_OFFSET_SMALL  1000
  #define SPEED_OFFSET_MEDIUM 2000
  #define SPEED_OFFSET_LARGE  3000
#endif

  /* check object position and adjust driving direction */
  if (SUMO_ObstacleInFrontSight(SUMO_AimRadiusCm, &distFlags)) { /* still visible */
    /* continue driving and chasing, but check in which direction we want to move */
    if ((distFlags&(DIST_SENSOR_FRONT_FAR_LEFT|DIST_SENSOR_FRONT_LEFT|DIST_SENSOR_FRONT_RIGHT|DIST_SENSOR_FRONT_FAR_RIGHT))==DIST_SENSOR_FRONT_FAR_LEFT) {
     DRV_SetSpeed(SUMO_SpeedChaseSteps-SPEED_OFFSET_LARGE, SUMO_SpeedChaseSteps+SPEED_OFFSET_LARGE); /* drive to the left */
     *lastOpponentPos = LAST_POS_ON_THE_LEFT;
    #if PRINT_AIM_INFO
      SHELL_SendString((unsigned char*)"far left\r\n");
    #endif
    } else if ((distFlags&(DIST_SENSOR_FRONT_FAR_LEFT|DIST_SENSOR_FRONT_LEFT|DIST_SENSOR_FRONT_RIGHT|DIST_SENSOR_FRONT_FAR_RIGHT))==(DIST_SENSOR_FRONT_FAR_LEFT|DIST_SENSOR_FRONT_LEFT)) {
      DRV_SetSpeed(SUMO_SpeedChaseSteps-SPEED_OFFSET_MEDIUM, SUMO_SpeedChaseSteps+SPEED_OFFSET_MEDIUM); /* drive to the left */
      *lastOpponentPos = LAST_POS_ON_THE_LEFT;
    #if PRINT_AIM_INFO
      SHELL_SendString((unsigned char*)"far left & left\r\n");
    #endif
    } else if ((distFlags&(DIST_SENSOR_FRONT_FAR_LEFT|DIST_SENSOR_FRONT_LEFT|DIST_SENSOR_FRONT_RIGHT|DIST_SENSOR_FRONT_FAR_RIGHT))==(DIST_SENSOR_FRONT_FAR_LEFT|DIST_SENSOR_FRONT_LEFT||DIST_SENSOR_FRONT_RIGHT)) {
      DRV_SetSpeed(SUMO_SpeedChaseSteps-SPEED_OFFSET_SMALL, SUMO_SpeedChaseSteps+SPEED_OFFSET_SMALL); /* drive to the left */
      *lastOpponentPos = LAST_POS_ON_THE_LEFT;
    #if PRINT_AIM_INFO
      SHELL_SendString((unsigned char*)"far left & left & right\r\n");
    #endif
    } else if ((distFlags&(DIST_SENSOR_FRONT_FAR_LEFT|DIST_SENSOR_FRONT_LEFT|DIST_SENSOR_FRONT_RIGHT|DIST_SENSOR_FRONT_FAR_RIGHT))==(DIST_SENSOR_FRONT_FAR_RIGHT)) {
      DRV_SetSpeed(SUMO_SpeedChaseSteps+SPEED_OFFSET_LARGE, SUMO_SpeedChaseSteps-SPEED_OFFSET_LARGE); /* drive to the right */
      *lastOpponentPos = LAST_POS_ON_THE_RIGHT;
    #if PRINT_AIM_INFO
      SHELL_SendString((unsigned char*)"far right\r\n");
    #endif
    } else if ((distFlags&(DIST_SENSOR_FRONT_FAR_LEFT|DIST_SENSOR_FRONT_LEFT|DIST_SENSOR_FRONT_RIGHT|DIST_SENSOR_FRONT_FAR_RIGHT))==(DIST_SENSOR_FRONT_FAR_RIGHT|DIST_SENSOR_FRONT_RIGHT)) {
      DRV_SetSpeed(SUMO_SpeedChaseSteps+SPEED_OFFSET_MEDIUM, SUMO_SpeedChaseSteps-SPEED_OFFSET_MEDIUM); /* drive to the right */
      *lastOpponentPos = LAST_POS_ON_THE_RIGHT;
    #if PRINT_AIM_INFO
      SHELL_SendString((unsigned char*)"far right & right\r\n");
    #endif
    } else if ((distFlags&(DIST_SENSOR_FRONT_FAR_LEFT|DIST_SENSOR_FRONT_LEFT|DIST_SENSOR_FRONT_RIGHT|DIST_SENSOR_FRONT_FAR_RIGHT))==(DIST_SENSOR_FRONT_FAR_RIGHT|DIST_SENSOR_FRONT_RIGHT|DIST_SENSOR_FRONT_LEFT)) {
      DRV_SetSpeed(SUMO_SpeedChaseSteps+SPEED_OFFSET_SMALL, SUMO_SpeedChaseSteps-SPEED_OFFSET_SMALL); /* drive to the right */
      *lastOpponentPos = LAST_POS_ON_THE_RIGHT;
    #if PRINT_AIM_INFO
      SHELL_SendString((unsigned char*)"far right & right & left\r\n");
    #endif
    } else if ((distFlags&(DIST_SENSOR_FRONT_FAR_LEFT|DIST_SENSOR_FRONT_LEFT|DIST_SENSOR_FRONT_RIGHT|DIST_SENSOR_FRONT_FAR_RIGHT))==(DIST_SENSOR_FRONT_FAR_LEFT|DIST_SENSOR_FRONT_LEFT|DIST_SENSOR_FRONT_RIGHT|DIST_SENSOR_FRONT_FAR_RIGHT)) {
      DRV_SetSpeed(SUMO_SpeedChaseSteps, SUMO_SpeedChaseSteps); /* full speed forward */
      *lastOpponentPos = LAST_POS_ON_THE_FRONT;
    #if PRINT_AIM_INFO
      SHELL_SendString((unsigned char*)"all in front\r\n");
    #endif
    }
    return TRUE; /* object still visible */
  }
  return FALSE; /* lost object? */
}
#endif

/*!
 * \brief Performs the Sumo 5 seconds countdown counting with beeps.
 * \return TRUE if countdown is going on, FALSE otherwise.
 */
static bool SUMO_CountDownDelay(void) {
  int i;

  if (SUMO_countDownMs==0) {
#if PL_HAS_USER_LED
    LED1_Off();
#endif
    SUMO_countDownMs = SUMO_NO_COUNTDOWN_MS; /* disable countdown */
    SUMO_StartSumo();
    return FALSE; /* finished countdown */
  } else if (SUMO_countDownMs>=0) {
#if PL_HAS_BUZZER
    BUZ_Beep((SUMO_countDownMs/10)+SUMO_CONFIG_BEEP_FREQ_ADD, 500);
#endif
    SUMO_countDownMs -= 1000;
    for(i=0;i<20;i++) {
#if PL_HAS_DISTANCE_SENSOR
      if (sumoStartFirstTurnLeft) {
        LED1_Neg();
        LED2_Off();
      } else {
        LED1_Off();
        LED2_Neg();
      }
      if (i<10) {
        if (SearchOpponent()) { /* returns TRUE if we see something */
          LED1_On();
          LED2_On();
        }
      }
#endif
      vTaskDelay(50/portTICK_PERIOD_MS);
    }
    return TRUE;
  }
  return FALSE;
}

#if !PL_SLOWER_SPEED
#include "Pid.h"

static void SUMO_SetFasterTurning(void) {
  uint8_t res;
  PID_Config *pLeft, *pRight;

  res = PID_GetPIDConfig(PID_CONFIG_POS_LEFT, &pLeft);
  if (res==ERR_OK) {
   pLeft->maxSpeedPercent = 100;
  }
  res = PID_GetPIDConfig(PID_CONFIG_POS_RIGHT, &pRight);
  if (res==ERR_OK) {
    pRight->maxSpeedPercent = 100;
  }
}

static void SUMO_SetSlowerTurning(void) {
  uint8_t res;
  PID_Config *pLeft, *pRight;

  res = PID_GetPIDConfig(PID_CONFIG_POS_LEFT, &pLeft);
  if (res==ERR_OK) {
    pLeft->maxSpeedPercent = 60;
  }
  res = PID_GetPIDConfig(PID_CONFIG_POS_RIGHT, &pRight);
  if (res==ERR_OK) {
    pRight->maxSpeedPercent = 60;
  }
}
#endif /* !PL_SLOWER_SPEED */

static void SUMO_ProcessStateMachine(void) {
  REF_LineKind lineKind;
  bool onLine;
  uint16_t lineVal;
#if SUMO_SEARCH_OBJECT_IR
  static uint8_t turnCnt;
#endif
#if SUMO_SEARCH_OBJECT_LASER
  bool isLeft, isRight;
#endif
#if PL_HAS_DISTANCE_SENSOR
  DIST_Sensor distFlags;
  static SUMO_LastPosition_e lastOpponentPos = LAST_POS_UNKNOWN;
#endif
  
  for(;;) { /* breaks */
#if SUMO_CHECK_ACCEL
    if (SUMO_State!=SUMO_STATE_OUTSIDE && RobotIsOutside()) {
      SUMO_SetNextState(SUMO_STATE_OUTSIDE);
    }
#endif
    if (SUMO_State!=SUMO_STATE_IDLE && SUMO_State!=SUMO_STATE_OUTSIDE) {
      lineKind = REF_GetLineKind(REF_LINE_KIND_MODE_SUMO);
      if (lineKind!=REF_LINE_FULL) { /* border! */
        SUMO_SetNextState(SUMO_STATE_MOVE_AWAY);
      }
    }
    switch(SUMO_State) { /* a 'break' will stay inside loop. Use 'continue' to re-iterate switch, and 'return' to leave function */
      case SUMO_STATE_IDLE:
      #if PL_HAS_DISTANCE_SENSOR
        if (sumoRadar) {
          RadarDistance();
        }
      #endif /* PL_HAS_DISTANCE_SENSOR */
        if (SUMO_doRunSumo) {
      #if SUMO_HAS_DROP_BLADE
          DropBlade();
      #endif /* SUMO_HAS_DROP_BLADE */
       #if PL_HAS_DISTANCE_SENSOR
          if (useDistanceSensor) {
            SUMO_SetNextState(SUMO_STATE_START_SEARCH);
          } else {
            SUMO_SetNextState(SUMO_STATE_START_DRIVE);
          }
       #else
          SUMO_SetNextState(SUMO_STATE_START_DRIVE);
       #endif
        }
        break;
        
#if PL_HAS_DISTANCE_SENSOR
      case SUMO_STATE_START_SEARCH:
#if SUMO_SEARCH_OBJECT_IR
        turnCnt = 0;
#endif
#if !PL_SLOWER_SPEED
        SUMO_SetSlowerTurning();
#endif
#if PL_HAS_DISTANCE_SENSOR
        lastOpponentPos = LAST_POS_UNKNOWN;
#endif
        SUMO_SetNextState(SUMO_STATE_SEARCH);
        continue;
#endif

#if SUMO_SEARCH_OBJECT
      case SUMO_STATE_SEARCH:
        /* we are *not* driving here */
        if (SUMO_TurnAndSearchOpponent(sumoStartFirstTurnLeft?-280:280, lastOpponentPos)) {
          SUMO_SetNextState(SUMO_STATE_START_CHASE);
        } else { /* not found object */
          SUMO_SetNextState(SUMO_STATE_START_DRIVE);
        }
        continue;
#endif
        
#if PL_HAS_DISTANCE_SENSOR
      case SUMO_STATE_START_CHASE:
#if PL_HAS_BUZZER
        BUZ_Beep(300, 500);
#endif
#if PL_HAS_DRIVE
        DRV_SetSpeed(SUMO_SpeedChaseSteps, SUMO_SpeedChaseSteps); /* drive forward with base speed */
        DRV_SetMode(DRV_MODE_SPEED); /* enable drive mode */
        if (!SUMO_UpdateChaseSpeed(&lastOpponentPos)) { /* update speed based on sensor data */
          /* lost it, search again */
          DRV_SetMode(DRV_MODE_STOP); /* stop it */
          SUMO_SetNextState(SUMO_STATE_SEARCH);
        } else {
          SUMO_SetNextState(SUMO_STATE_CHASE);
        }
#else
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), SUMO_SpeedDriveDuty);
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), SUMO_SpeedDriveDuty);
        SUMO_SetNextState(SUMO_STATE_CHASE);
#endif
        continue;

      case SUMO_STATE_CHASE:
        if (!SUMO_UpdateChaseSpeed(&lastOpponentPos)) {
          /* lost it, search again */
          SUMO_SetNextState(SUMO_STATE_SEARCH);
        }
        break;
#endif

      case SUMO_STATE_START_DRIVE:
#if !PL_SLOWER_SPEED
        SUMO_SetFasterTurning();
#endif
#if PL_HAS_DRIVE
        DRV_SetSpeed(SUMO_SpeedDriveSteps, SUMO_SpeedDriveSteps); /* drive forward */
        DRV_SetMode(DRV_MODE_SPEED); /* drive */
#else
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), SUMO_SpeedDriveDuty);
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), SUMO_SpeedDriveDuty);
#endif
        SUMO_SetNextState(SUMO_STATE_DRIVE);
        break;

      case SUMO_STATE_DRIVE:
      #if PL_HAS_DISTANCE_SENSOR
        if (SUMO_ObstacleInFrontSight(SUMO_AimRadiusCm, &distFlags)) {
          SUMO_SetNextState(SUMO_STATE_START_CHASE);
        } else {
          /* continue driving */
        }
      #else
        /* continue driving */
      #endif
        break;
        
      case SUMO_STATE_MOVE_AWAY: /* move away from the line */
      #if PL_HAS_DISTANCE_SENSOR
        lastOpponentPos = LAST_POS_UNKNOWN;
      #endif
      #if PL_HAS_DRIVE
        DRV_SetMode(DRV_MODE_NONE);
      #endif
        lineVal = REF_GetLineValue(&onLine);
        TURN_Turn(TURN_STEP_BORDER_BW, NULL); /* step back from border */
#if PL_HAS_DRIVE
        while (!DRV_HasTurned()) { /* wait until we moved away from line */
          vTaskDelay(50/portTICK_PERIOD_MS); /* hack! Give time for PID to reach position */
        }
#endif
#if PL_HAS_DISTANCE_SENSOR
        {
          int16_t turnAngle;

          if (lineVal>REF_MIDDLE_LINE_VALUE) {
            turnAngle = SUMO_CONFIG_ANGLE_STRAIGHT; /* turn right */
          } else {
            turnAngle = -SUMO_CONFIG_ANGLE_STRAIGHT; /* turn left */
          }
          if (SUMO_TurnAndSearchOpponent(turnAngle, lastOpponentPos)) {
            /* found something while turning! */
            SUMO_SetNextState(SUMO_STATE_START_CHASE);
          } else {
            SUMO_SetNextState(SUMO_STATE_START_DRIVE);
          }
        }
#else
        /* line value to determine if we should move left or right */
        if (lineVal>REF_MIDDLE_LINE_VALUE) {
          TURN_TurnAngle(SUMO_CONFIG_ANGLE_STRAIGHT, NULL); /* turn right */
        } else {
          TURN_TurnAngle(-SUMO_CONFIG_ANGLE_STRAIGHT, NULL); /* turn left */
        }
        SUMO_SetNextState(SUMO_STATE_START_DRIVE);
#endif
        continue; /* go to next state */

      case SUMO_STATE_OUTSIDE:
        SUMO_StopSumo();
        SUMO_SetNextState(SUMO_STATE_IDLE);
        break;
        
      default:
        break;
    } /* switch */
    break; /* break loop */
  } /* for */
}

static void SumoTask(void *pvParameters) {
  int cntr = 0;
  uint32_t notifcationValue;
#if PL_HAS_DISTANCE_SENSOR
  DIST_Sensor prevDistFlags=0;
#endif
#if PL_CONFIG_HAS_NVM_CONFIG
  void *p;
  uint16_t val;

  p = NVMC_GetSumoData();
  if (p!=NULL) {
    val = *(uint16_t*)p;
    if (val==1) {
      SUMO_doRunSumo = TRUE;
    } else {
      SUMO_doRunSumo = FALSE;
    }
  } else {
    SUMO_doRunSumo = FALSE;
  }
#endif  
  (void)pvParameters; /* not used */
  SUMO_State = SUMO_STATE_IDLE; /* init state */
  for(;;) {
    (void)xTaskNotifyWait(0UL, SUMO_START_SUMO|SUMO_STOP_SUMO, &notifcationValue, 0); /* check flags */
    cntr++;
    if ((notifcationValue&SUMO_START_SUMO)) {
    #if PL_CONFIG_HAS_SHELL
      SHELL_SendString((unsigned char*)"Sumo starting\r\n");
    #endif
      SUMO_ChangeRunSumo(TRUE);
    #if PL_HAS_USER_LED
      LED1_Off();
    #endif
      SUMO_SetNextState(SUMO_STATE_IDLE);
    #if PL_CONFIG_HAS_SHELL
      SHELL_SendString((unsigned char*)"Sumo started\r\n");
    #endif
    }
    if ((notifcationValue&SUMO_STOP_SUMO)) {
      SUMO_ChangeRunSumo(FALSE);
      SUMO_countDownMs = SUMO_NO_COUNTDOWN_MS;
      SUMO_SetNextState(SUMO_STATE_IDLE);
    #if PL_HAS_DRIVE
      DRV_SetSpeed(0,0); /* stop engines */
      DRV_SetMode(DRV_MODE_STOP);
    #else
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
    #endif
    #if PL_CONFIG_HAS_SHELL
      SHELL_SendString((unsigned char*)"Sumo stopped\r\n");
    #endif
    }
    SUMO_ProcessStateMachine();
    if (SUMO_doRunSumo) { /* running the sumo */
      if ((cntr%25)==0) {
        LED1_Neg();
        LED2_Neg();
      }
      vTaskDelay(TASK_DELAY_MS/portTICK_PERIOD_MS);
    } else { /* not running the sumo */
  #if PL_REMOTE_STOP_LINE
      /* stop on white line if using remote controller to avoid falling of the ring */
      if (REF_GetLineKind(REF_LINE_KIND_MODE_SUMO)!=REF_LINE_FULL) { /* white line, border! */
        if (!APP_StateIsCalibrating()) { /* during calibration we are allowed to be on white line */
          if (TACHO_GetSpeed(TRUE)>0 || TACHO_GetSpeed(FALSE)>0) { /* moving forward */
            if (DRV_GetMode()!=DRV_MODE_POS) {  /* stop engines, if not stopped already */
              DRV_SetPos(Q4CLeft_GetPos()/*-20*/, Q4CRight_GetPos()/*-20*/);
              DRV_SetMode(DRV_MODE_POS);
            #if PL_CONFIG_HAS_SHELL
              SHELL_SendString((unsigned char*)"Remote: stopped\r\n");
            #endif
            }
          }
        }
      }
  #endif
      if (SUMO_CountDownDelay()) { /* this delays for a second if we are in count-down mode */
        LED1_Off();
        LED2_Off();
      } else {
#if PL_HAS_DISTANCE_SENSOR
        DIST_Sensor distFlags;

        if (SUMO_ObstacleInFrontSight(SUMO_AimRadiusCm, &distFlags)) {
          if (prevDistFlags!=distFlags) { /* changed state */
            LED1_Off();
            LED2_Off();
          }
          prevDistFlags = distFlags;
          if ((cntr%50)==0) {
            if ((distFlags&(DIST_SENSOR_FRONT_LEFT|DIST_SENSOR_FRONT_RIGHT)) == (DIST_SENSOR_FRONT_LEFT|DIST_SENSOR_FRONT_RIGHT)) {
              LED1_Neg(); /* left LED */
              LED2_Neg(); /* right LED */
            } else if (distFlags&(DIST_SENSOR_FRONT_FAR_LEFT|DIST_SENSOR_FRONT_LEFT)) {
              LED1_Neg(); /* left LED */
            } else if (distFlags&(DIST_SENSOR_FRONT_FAR_RIGHT|DIST_SENSOR_FRONT_RIGHT)) {
              LED2_Neg(); /* right LED */
            }
          }
        } else { /* no object */
          if ((cntr%400)==0) {
            if (sumoStartFirstTurnLeft) {
              LED1_Neg();
              LED2_Off();
            } else {
              LED1_Off();
              LED2_Neg();
            }
          }
        }
#endif
        vTaskDelay(TASK_DELAY_MS/portTICK_PERIOD_MS);
      }
    }
  } /* for */
}

#if PL_CONFIG_HAS_SHELL
static uint8_t SUMO_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"sumo", (unsigned char*)"Group of sumo commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows sumo help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  start|stop", (unsigned char*)"Sumo start or stop\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  start countdown", (unsigned char*)"Start 5 second countdown\r\n", io->stdOut);
#if PL_HAS_DRIVE
  CLS1_SendHelpStr((unsigned char*)"  drive <steps>", (unsigned char*)"Sumo drive speed\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  chase <steps>", (unsigned char*)"Sumo chase speed\r\n", io->stdOut);
#else
  CLS1_SendHelpStr((unsigned char*)"  speed <percent>", (unsigned char*)"Sumo motor PWM duty percent\r\n", io->stdOut);
#endif
#if PL_HAS_DISTANCE_SENSOR
  CLS1_SendHelpStr((unsigned char*)"  radius <cm>", (unsigned char*)"Set aiming radius\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  sensor (on|off)", (unsigned char*)"Turn distance sensor on/off\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  startturn (left|right)", (unsigned char*)"Start first search turn left or right\r\n", io->stdOut);
#endif
#if SUMO_SEARCH_OBJECT
  CLS1_SendHelpStr((unsigned char*)"  aim <cm> (l|r|lc|rc)", (unsigned char*)"Aim opponent within <cm>, at left or right edge, or center\r\n", io->stdOut);
#endif
#if PL_HAS_TOF_SENSOR
  CLS1_SendHelpStr((unsigned char*)"  radar (on|off)", (unsigned char*)"Sumo radar buzzer on or off\r\n", io->stdOut);
#endif
  return ERR_OK;
}

static uint8_t SUMO_PrintStatus(const CLS1_StdIOType *io) {
  unsigned char buf[64];

  CLS1_SendStatusStr((unsigned char*)"sumo", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  sumo", SUMO_doRunSumo?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);

#if PL_HAS_DISTANCE_SENSOR
  CLS1_SendStatusStr((unsigned char*)"  radar", sumoRadar?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  sensor", useDistanceSensor?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  first turn", sumoStartFirstTurnLeft?(unsigned char*)"left\r\n":(unsigned char*)"right\r\n", io->stdOut);
  #endif
  CLS1_SendStatusStr((unsigned char*)"  state", SUMO_StatusStr(SUMO_State), io->stdOut);  
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  
#if PL_HAS_MOTOR_TACHO
  UTIL1_Num16sToStr(buf, sizeof(buf), SUMO_SpeedDriveSteps);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" steps\r\n");
#else
  UTIL1_Num16sToStr(buf, sizeof(buf), SUMO_SpeedDriveDuty);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"%\r\n");
#endif
  CLS1_SendStatusStr((unsigned char*)"  drive", buf, io->stdOut);

#if PL_HAS_MOTOR_TACHO
  UTIL1_Num16sToStr(buf, sizeof(buf), SUMO_SpeedChaseSteps);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" steps\r\n");
#else
  UTIL1_Num16sToStr(buf, sizeof(buf), SUMO_SpeedChaseDuty);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"%\r\n");
#endif
  CLS1_SendStatusStr((unsigned char*)"  chase", buf, io->stdOut);

  UTIL1_Num16sToStr(buf, sizeof(buf), SUMO_AimRadiusCm);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" cm\r\n");
  CLS1_SendStatusStr((unsigned char*)"  aim radius", buf, io->stdOut);

#if PL_HAS_DISTANCE_SENSOR
  buf[0] = '\0';
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"left to right: ");
  UTIL1_strcatNum16s(buf, sizeof(buf), DIST_GetDistance(DIST_SENSOR_FRONT_FAR_LEFT));
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" mm,");
  UTIL1_strcatNum16s(buf, sizeof(buf), DIST_GetDistance(DIST_SENSOR_FRONT_LEFT));
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" mm,");
  UTIL1_strcatNum16s(buf, sizeof(buf), DIST_GetDistance(DIST_SENSOR_FRONT_RIGHT));
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" mm,");
  UTIL1_strcatNum16s(buf, sizeof(buf), DIST_GetDistance(DIST_SENSOR_FRONT_FAR_RIGHT));
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" mm\r\n");
  CLS1_SendStatusStr((unsigned char*)"  range", buf, io->stdOut);
#endif

  return ERR_OK;
}

uint8_t SUMO_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  const unsigned char *p;
  
  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"sumo help")==0) {
    *handled = TRUE;
    return SUMO_PrintHelp(io);
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"sumo status")==0) {
    *handled = TRUE;
    return SUMO_PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, (char*)"sumo start countdown")==0) {
    *handled = TRUE;
    if (REF_CanUseSensor()) {
      SUMO_StartCountdown();
    } else {
      CLS1_SendStr((unsigned char*)"ERR: Reflectance not calibrated.\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strcmp((char*)cmd, (char*)"sumo start")==0) {
    *handled = TRUE;
    if (REF_CanUseSensor()) {
      SUMO_StartSumo();
    } else {
      CLS1_SendStr((unsigned char*)"ERR: Reflectance not calibrated.\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strcmp((char*)cmd, (char*)"sumo stop")==0) {
    SUMO_StopSumo();
    *handled = TRUE;
#if PL_HAS_MOTOR_TACHO
  } else if (UTIL1_strncmp((char*)cmd, (char*)"sumo drive ", sizeof("sumo drive ")-1)==0) {
    int16_t val16;

    p = cmd+sizeof("sumo drive");
    if (UTIL1_ScanDecimal16sNumber(&p, &val16)==ERR_OK && val16>=0) {
      SUMO_SpeedDriveSteps = val16;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument, steps must be positive.\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"sumo chase ", sizeof("sumo chase ")-1)==0) {
    int16_t val16;

    p = cmd+sizeof("sumo chase");
    if (UTIL1_ScanDecimal16sNumber(&p, &val16)==ERR_OK && val16>=0) {
      SUMO_SpeedChaseSteps = val16;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument, steps must be positive.\r\n", io->stdErr);
      res = ERR_FAILED;
    }
#else
  } else if (UTIL1_strncmp((char*)cmd, (char*)"sumo speed ", sizeof("sumo speed ")-1)==0) {
    uint8_t val8u;

    p = cmd+sizeof("sumo speed");
    if (UTIL1_ScanDecimal8uNumber(&p, &val8u)==ERR_OK && val8u<=100) {
      SUMO_SpeedDriveDuty = val8u;
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument, must be in the range 0..100\r\n", io->stdErr);
      res = ERR_FAILED;
    }
#endif
#if SUMO_SEARCH_OBJECT
  } else if (UTIL1_strncmp((char*)cmd, (char*)"sumo aim ", sizeof("sumo aim ")-1)==0) {
    uint8_t val8u;

    p = cmd+sizeof("sumo aim");
    if (UTIL1_ScanDecimal8uNumber(&p, &val8u)==ERR_OK && val8u>0) {
      if (UTIL1_strcmp((char*)p, (char*)" rc")==0) {
        (void)SUMO_AimObstacle(val8u, SUMO_AIM_CENTER_RIGHT, 0, 180);
      } else if (UTIL1_strcmp((char*)p, (char*)" lc")==0) {
        (void)SUMO_AimObstacle(val8u, SUMO_AIM_CENTER_LEFT, 0, -180);
      } else if (UTIL1_strcmp((char*)p, (char*)" l")==0) {
        (void)SUMO_AimObstacle(val8u, SUMO_AIM_LEFT, -180, 0);
      } else if (UTIL1_strcmp((char*)p, (char*)" r")==0) {
        (void)SUMO_AimObstacle(val8u, SUMO_AIM_RIGHT, 0, 180);
      } else {
        CLS1_SendStr((unsigned char*)"wrong aim argument\r\n", io->stdErr);
        res = ERR_FAILED;
      }
      *handled = TRUE;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong number argument\r\n", io->stdErr);
      res = ERR_FAILED;
    }
#endif
  } else if (UTIL1_strncmp((char*)cmd, (char*)"sumo radius ", sizeof("sumo radius ")-1)==0) {
    int16_t val16;

    *handled = TRUE;
    p = cmd+sizeof("sumo radius ")-1;
    if (UTIL1_ScanDecimal16sNumber(&p, &val16)==ERR_OK && val16>=0) {
      SUMO_AimRadiusCm = val16;
    } else {
      CLS1_SendStr((unsigned char*)"Wrong argument, steps must be positive.\r\n", io->stdErr);
      res = ERR_FAILED;
    }
#if PL_HAS_DISTANCE_SENSOR
  } else if (UTIL1_strcmp((char*)cmd, "sumo sensor on")==0) {
    *handled = TRUE;
    useDistanceSensor = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "sumo sensor off")==0) {
    *handled = TRUE;
    useDistanceSensor = FALSE;
  } else if (UTIL1_strcmp((char*)cmd, "sumo radar on")==0) {
    *handled = TRUE;
    SUMO_RadarOn();
  } else if (UTIL1_strcmp((char*)cmd, "sumo radar off")==0) {
    *handled = TRUE;
    SUMO_RadarOff();
  } else if (UTIL1_strcmp((char*)cmd, "sumo startturn left")==0) {
    *handled = TRUE;
    SUMO_StartTurnLeft();
  } else if (UTIL1_strcmp((char*)cmd, "sumo startturn right")==0) {
    *handled = TRUE;
    SUMO_StartTurnRight();
#endif
  }
  return res;
}
#endif /* PL_CONFIG_HAS_SHELL */

void SUMO_Init(void) {
  if (xTaskCreate(SumoTask, "Sumo", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+2, &sumoTaskHndl) != pdPASS) {
    for(;;){} /* error */
  }
}

#endif /* PL_APP_SUMO */



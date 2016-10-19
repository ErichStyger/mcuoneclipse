// Plotclock
// cc - by Johannes Heberlein 2014
// v 1.01
// thingiverse.com/joo   wiki.fablab-nuernberg.de

// units: mm; microseconds; radians
// origin: bottom left of drawing surface

#include "Plotclock.h"
#include <math.h>
#include "Servo.h"
#include "FRTOS1.h"
#include "WAIT1.h"
#include "PCA9685.h"
#include "TmDt1.h"
#include "Vibra.h"

static bool PlotClockIsEnabled = TRUE; /* if clock is enabled */
static bool PlotClockCalibrateIsOn = FALSE; /* if calibration mode is on */

/* When in calibration mode, adjust the following factor until the servos move exactly 90 degrees */
static int SERVOFAKTOR_LEFT = 650;
static int SERVOFAKTOR_RIGHT = 620;

/* Zero-position of left and right servo
   When in calibration mode, adjust the NULL-values so that the servo arms are at all times parallel
   either to the X or Y axis */
static int SERVOLEFTNULL = 1550;
static int SERVORIGHTNULL = 440;

#define PLOTCLOCK_MINPOS_X   -30
#define PLOTCLOCK_MAXPOS_X   90

#define PLOTCLOCK_MINPOS_Y   25
#define PLOTCLOCK_MAXPOS_Y   80

#define PLOTCLOCK_PARKPOS_X  75
#define PLOTCLOCK_PARKPOS_Y  30

/* lift positions of lifting servo */
static int LIFT0 = 1100; // on drawing surface
static int LIFT1 =  900;  // between numbers
static int LIFT2 =  800;  // going towards sweeper
static int LIFT_INIT = 900; /* start/reset position */
static int servoLift; /* current position of lift servo */

/* corresponds to servo channels */
typedef enum {
  PLOTCLOCK_SERVO_LIFT = 0,
  PLOTCLOCK_SERVO_LEFT = 1,
  PLOTCLOCK_SERVO_RIGHT= 2,
} PlotClockServo;

typedef enum {
  PLOTCLOCK_LIFT_POS_DRAW,
  PLOTCLOCK_LIFT_POS_BETWEEN_DRAW,
  PLOTCLOCK_LIFT_POS_PARKING
} PlotClockLiftPos;

/* last values */
static volatile double lastX = PLOTCLOCK_PARKPOS_X;
static volatile double lastY = PLOTCLOCK_PARKPOS_Y;
static uint8_t last_min = -1;

/* speed (actually delay time) of lifting arm, higher is slower */
#define LIFTSPEED 1500

/* length of arms in mm, see http://wiki.fablab-nuernberg.de/w/Datei:erklaerung.jpg */
#if 0 /* original */
  #define L1 35.0 /* arm from servo to the first joint */
  #define L2 55.1 /* arm from first joint to second joint */
  #define L3 13.2 /* last piece to the center of the pen */
#else
  #define L1 40.0 /* length of first arm, line from servo joint to the first joint */
  #define L2 57.0 /* line from first joint to center of pen */
  #define L3 12.0 /* length of 'front' arm, line from front joint to center of the pen */
  #define L4 50.0 /* length of the second arm, distance between first joint and second joint */
#endif

/* origin points in mm of left and right servo */
#define O1X  22  /* X position of the left servo to left border.  */
#define O1Y -30  /* Y position of of left servo to base line. */
#define O2X  48  /* X position of the right servo */
#define O2Y -30  /* Y position of the right servo */

#define M_PI    3.14159265358979323846

static void delay(uint32_t ms) {
  vTaskDelay(pdMS_TO_TICKS(ms));
}

static void delayMicroseconds(uint32_t us) {
  WAIT1_Waitus(us);
}

static void servo_writeMicroseconds(PlotClockServo servo, uint16_t us) {
  SERVO_WriteDutyMicroSeconds(PCA9685_I2C_DEFAULT_ADDR, (uint8_t)servo, us, SERVO_MIN_TICKS, SERVO_MAX_TICKS);
}

static double return_angle(double a, double b, double c) {
  /* cosine rule for angle between c and a */
  /* input to acos in range of -1 to +1 */
  double val = (a*a + c*c - b*b) / (2 * a * c);

  if (val>1.0) {
    val = 1.0;
  } else if (val<-1.0) {
    val = -1.0;
  }
  return acos(val);
}

static void set_XY(double Tx, double Ty) {
  double dx, dy, c, a1, a2, Hx, Hy;

  delay(1);
  /* calculate triangle between pen, servoLeft and arm joint */
  /* cartesian dx/dy */
  dx = Tx - O1X;
  dy = Ty - O1Y;

  /* polar length (c) and angle (a1) */
  c = sqrt(dx*dx + dy*dy);
  a1 = atan2(dy, dx);
  a2 = return_angle(L1, L2, c);

  servo_writeMicroseconds(PLOTCLOCK_SERVO_LEFT, floor(((a2 + a1 - M_PI) * SERVOFAKTOR_LEFT) + SERVOLEFTNULL));

  /* calculate join arm point for triangle of the right servo arm */
  a2 = return_angle(L2, L1, c);
  Hx = Tx + L3 * cos((a1 - a2 + 0.621) + M_PI); //36.5° is angle between marker and joint
  Hy = Ty + L3 * sin((a1 - a2 + 0.621) + M_PI);

  /* calculate triangle between pen joint, servoRight and arm joint */
  dx = Hx - O2X;
  dy = Hy - O2Y;

  c = sqrt(dx*dx + dy*dy);
  a1 = atan2(dy, dx);
  a2 = return_angle(L1, L4, c);

  servo_writeMicroseconds(PLOTCLOCK_SERVO_RIGHT, floor(((a1 - a2) * SERVOFAKTOR_RIGHT) + SERVORIGHTNULL));
}

static void drawTo(double pX, double pY) {
  double dx, dy, c;
  int i;

  if (pX<PLOTCLOCK_MINPOS_X) {
    pX = PLOTCLOCK_MINPOS_X;
  } else if (pX>PLOTCLOCK_MAXPOS_X) {
    pX = PLOTCLOCK_MAXPOS_X;
  }

  if (pY<PLOTCLOCK_MINPOS_Y) {
    pY = PLOTCLOCK_MINPOS_Y;
  } else if (pY>PLOTCLOCK_MAXPOS_Y) {
    pY = PLOTCLOCK_MAXPOS_Y;
  }

  /* dx dy of new point */
  dx = pX - lastX;
  dy = pY - lastY;
  //path length in mm, times 4 equals 4 steps per mm
#if 0 /* orig */
  c = floor(4 * sqrt(dx * dx + dy * dy));
#else
  c = floor(7 * sqrt(dx*dx + dy*dy));
#endif

  if (c < 1) {
    c = 1;
  }
  for (i = 0; i <= c; i++) {
    /* draw line point by point */
    set_XY(lastX + (i * dx / c), lastY + (i * dy / c));
  }
  lastX = pX;
  lastY = pY;
}

static void bogenGZS(float bx, float by, float radius, int start, int ende, float sqee) {
  float inkr = 0.05;
  float count = 0;

  do {
    drawTo(sqee * radius * cos(start + count) + bx,
    radius * sin(start + count) + by);
    count += inkr;
  }
  while ((start + count) <= ende);
}

static void bogenUZS(float bx, float by, float radius, int start, int ende, float sqee) {
  float inkr = -0.05;
  float count = 0;

  do {
    drawTo(sqee * radius * cos(start + count) + bx,
    radius * sin(start + count) + by);
    count += inkr;
  }
  while ((start + count) > ende);
}

static void lift(PlotClockLiftPos lift) {
  switch (lift) {
    case PLOTCLOCK_LIFT_POS_DRAW:
      if (servoLift >= LIFT0) {
        while (servoLift >= LIFT0) {
          servoLift--;
          servo_writeMicroseconds(PLOTCLOCK_SERVO_LIFT, servoLift);
          delayMicroseconds(LIFTSPEED);
        }
      } else {
        while (servoLift <= LIFT0) {
          servoLift++;
          servo_writeMicroseconds(PLOTCLOCK_SERVO_LIFT, servoLift);
          delayMicroseconds(LIFTSPEED);
        }
      }
      break;

    case PLOTCLOCK_LIFT_POS_BETWEEN_DRAW:
      if (servoLift >= LIFT1) {
        while (servoLift >= LIFT1) {
          servoLift--;
          servo_writeMicroseconds(PLOTCLOCK_SERVO_LIFT, servoLift);
          delayMicroseconds(LIFTSPEED);
        }
      } else {
        while (servoLift <= LIFT1) {
          servoLift++;
          servo_writeMicroseconds(PLOTCLOCK_SERVO_LIFT, servoLift);
          delayMicroseconds(LIFTSPEED);
        }
      }
      break;

    case PLOTCLOCK_LIFT_POS_PARKING:
      if (servoLift >= LIFT2) {
        while (servoLift >= LIFT2) {
          servoLift--;
          servo_writeMicroseconds(PLOTCLOCK_SERVO_LIFT, servoLift);
          delayMicroseconds(LIFTSPEED);
        }
      } else {
        while (servoLift <= LIFT2) {
          servoLift++;
          servo_writeMicroseconds(PLOTCLOCK_SERVO_LIFT, servoLift);
          delayMicroseconds(LIFTSPEED);
        }
      }
      break;

    default:
      break;
  } /* switch */
}

/* Writing numeral with bx by being the bottom left origin point. Scale 1 equals a 20 mm high font.
   The structure follows this principle: move to first start point of the numeral, lift down, draw numeral, lift up */
static void number(float bx, float by, int num, float scale) {
  switch (num) {
  case 0:
    drawTo(bx + 12.0 * scale, by + 6.0 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    bogenGZS(bx + 7.0 * scale, by + 10.0 * scale, 10.0 * scale, -0.8, 6.7, 0.5);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 1:
    drawTo(bx + 10.0 * scale, by + 20.0 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    drawTo(bx + 10.0 * scale, by + 0.0 * scale);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 2:
    drawTo(bx + 2.0 * scale, by + 12.0 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    bogenUZS(bx + 8.0 * scale, by + 14.0 * scale, 6.0 * scale, 3, -0.8, 1);
    drawTo(bx + 0.0 * scale, by + 0.0 * scale);
    drawTo(bx + 14.0 * scale, by + 0.0 * scale);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 3:
    drawTo(bx + 2.0 * scale, by + 20.0 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    drawTo(bx + 12.0 * scale, by + 20.0 * scale);
    drawTo(bx + 2.0 * scale, by + 10.0 * scale);
    bogenUZS(bx + 5.0 * scale, by + 5.0 * scale, 5.0 * scale, 1.57, -3, 1);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 4:
    drawTo(bx + 10.0 * scale, by + 2.0 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    drawTo(bx + 10.0 * scale, by + 22.0 * scale);
    drawTo(bx + 0.0 * scale, by + 8.0 * scale);
    drawTo(bx + 14.0 * scale, by + 8.0 * scale);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 5:
    drawTo(bx + 2.0 * scale, by + 5.0 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    bogenGZS(bx + 5.0 * scale, by + 6.0 * scale, 6.0 * scale, -2.5, 2, 1);
    drawTo(bx + 3.0 * scale, by + 20.0 * scale);
    drawTo(bx + 12.0 * scale, by + 20.0 * scale);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 6:
    drawTo(bx + 2.0 * scale, by + 10.0 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    bogenUZS(bx + 7.0 * scale, by + 6.0 * scale, 6.0 * scale, 2, -4.4, 1);
    drawTo(bx + 11.0 * scale, by + 20.0 * scale);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 7:
    drawTo(bx + 2.0 * scale, by + 20.0 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    drawTo(bx + 12.0 * scale, by + 20.0 * scale);
    drawTo(bx + 2.0 * scale, by + 0.0 * scale);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 8:
    drawTo(bx + 5.0 * scale, by + 10.0 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    bogenUZS(bx + 5.0 * scale, by + 15.0 * scale, 5.0 * scale, 4.7, -1.6, 1);
    bogenGZS(bx + 5.0 * scale, by + 5.0 * scale, 5.0 * scale, -4.7, 2, 1);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 9:
    drawTo(bx + 9.0 * scale, by + 11.0 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    bogenUZS(bx + 7.0 * scale, by + 15.0 * scale, 5.0 * scale, 4, -0.5, 1);
    drawTo(bx + 5 * scale, by + 0);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 11: /* special: draw ':' */
    drawTo(bx + 5.0 * scale, by + 15.0 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    delay(200); /* give time to put it down */
    bogenGZS(bx + 5.0 * scale, by + 15.0 * scale, 0.1 * scale, 1, -1, 1);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    drawTo(bx + 5 * scale, by + 5 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    delay(200); /* give time to put it down */
    bogenGZS(bx + 5.0 * scale, by + 5.0 * scale, 0.1 * scale, 1, -1, 1);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 111: /* special: wipe */
#if 1
    Vibra_SetVal(); /* motor on */
    delay(1000);
    Vibra_ClrVal(); /* motor off */
#else
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    drawTo(70, 46);
    drawTo(65, 43);

    drawTo(65, 49);
    drawTo(5, 49);
    drawTo(5, 45);
    drawTo(65, 45);
    drawTo(65, 40);

    drawTo(5, 40);
    drawTo(5, 35);
    drawTo(65, 35);
    drawTo(65, 30);

    drawTo(5, 30);
    drawTo(5, 25);
    drawTo(65, 25);
    drawTo(65, 20);

    drawTo(5, 20);
    drawTo(60, 44);

    drawTo(75.2, 47);
    lift(PLOTCLOCK_LIFT_POS_PARKING);
#endif
    break;
  }
}

void PlotClock_Setup(void) {
  Vibra_ClrVal(); /* vibra motor off */
  servoLift = LIFT_INIT;
  last_min = 0;
  servo_writeMicroseconds(PLOTCLOCK_SERVO_LIFT, servoLift);
  drawTo(PLOTCLOCK_PARKPOS_X, PLOTCLOCK_PARKPOS_Y); /* move to parking position */
  lift(PLOTCLOCK_LIFT_POS_DRAW); /* move down to surface */
  delay(1000);
}

static void PlotClockPrintTime(uint8_t hour, uint8_t minute) {
  float digitScale = 0.9;
  int8_t x, y;

  x = -10;
  y = 35;
  lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
  number(x,    y, hour/10, digitScale); /* write first digit of hour */
  number(x+16, y, hour%10, digitScale); /* write second digit */
  number(x+26, y, 11, digitScale); /* draw ':' */
  number(x+34, y, minute/10, digitScale); /* write most significant digit of hour */
  number(x+50, y, minute%10, digitScale); /* second digit */
  lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
  drawTo(PLOTCLOCK_PARKPOS_X, PLOTCLOCK_PARKPOS_Y); /* move to parking position */
}

void PlotClock_Loop(void) {
  if (!PlotClockIsEnabled) {
    return; /* clock not enabled */
  }
  if (PlotClockCalibrateIsOn) {
#if 0
    /* servo horns will have 90° between movements, parallel to x and y axis */
    drawTo(-3, 29.2);
    delay(500);
    drawTo(74.1, 28);
    delay(500);
#else
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    drawTo(0, 30);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    drawTo(70, 30);
    drawTo(70, 60);
    drawTo(0, 60);
    drawTo(0, 30);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
#endif
  } else {
    TIMEREC time;

    TmDt1_GetTime(&time);
    if (last_min != time.Min) {
      PlotClockPrintTime(time.Hour, time.Min);
      last_min = time.Min;
    }
  }
}

static uint8_t PrintStatus(CLS1_ConstStdIOType *io) {
  uint8_t buf[48];

  CLS1_SendStatusStr((unsigned char*)"plotclock", (const unsigned char*)"\r\n", io->stdOut);

  CLS1_SendStatusStr((unsigned char*)"  Enabled", PlotClockIsEnabled?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  Calibrating", PlotClockCalibrateIsOn?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);

  buf[0] = '\0'; UTIL1_Num16uToStr(buf, sizeof(buf), SERVOFAKTOR_LEFT); UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr((unsigned char*)"  FAKTOR L", buf, io->stdOut);

  buf[0] = '\0'; UTIL1_Num16uToStr(buf, sizeof(buf), SERVOFAKTOR_RIGHT); UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr((unsigned char*)"  FAKTOR R", buf, io->stdOut);

  buf[0] = '\0'; UTIL1_Num16uToStr(buf, sizeof(buf), SERVOLEFTNULL); UTIL1_strcat(buf, sizeof(buf), "us \r\n");
  CLS1_SendStatusStr((unsigned char*)"  LEFTNULL", buf, io->stdOut);

  buf[0] = '\0'; UTIL1_Num16uToStr(buf, sizeof(buf), SERVORIGHTNULL); UTIL1_strcat(buf, sizeof(buf), " us\r\n");
  CLS1_SendStatusStr((unsigned char*)"  RIGHTNULL", buf, io->stdOut);

  buf[0] = '\0'; UTIL1_Num16uToStr(buf, sizeof(buf), LIFT0); UTIL1_strcat(buf, sizeof(buf), " us (draw)\r\n");
  CLS1_SendStatusStr((unsigned char*)"  LIFT0", buf, io->stdOut);
  buf[0] = '\0'; UTIL1_Num16uToStr(buf, sizeof(buf), LIFT1); UTIL1_strcat(buf, sizeof(buf), " us (between drawing)\r\n");
  CLS1_SendStatusStr((unsigned char*)"  LIFT1", buf, io->stdOut);
  buf[0] = '\0'; UTIL1_Num16uToStr(buf, sizeof(buf), LIFT2); UTIL1_strcat(buf, sizeof(buf), " us (parking)\r\n");
  CLS1_SendStatusStr((unsigned char*)"  LIFT2", buf, io->stdOut);
  buf[0] = '\0'; UTIL1_Num16uToStr(buf, sizeof(buf), LIFTSPEED); UTIL1_strcat(buf, sizeof(buf), " us (higher is slower)\r\n");
  CLS1_SendStatusStr((unsigned char*)"  LIFTSPEED", buf, io->stdOut);

  buf[0] = '\0'; UTIL1_NumFloatToStr(buf, sizeof(buf), lastX, 2); UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr((unsigned char*)"  last X", buf, io->stdOut);

  buf[0] = '\0'; UTIL1_NumFloatToStr(buf, sizeof(buf), lastY, 2); UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr((unsigned char*)"  last Y", buf, io->stdOut);
  return ERR_OK;
}

uint8_t PlotClock_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "plotclock help")==0) {
    CLS1_SendHelpStr((unsigned char*)"plotclock", (const unsigned char*)"Group of plotclock commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  enable (on|off)", (const unsigned char*)"Turns the clock on or off\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  calibrate (on|off)", (const unsigned char*)"Calibration mode on or off\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  lift (0|1|2)", (const unsigned char*)"Lift servo arm\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  write <hh:mm>", (const unsigned char*)"Write time\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  moveto <x> <y>", (const unsigned char*)"Move to position\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  vibrate (on|off)", (const unsigned char*)"Turn vibration motor on or off\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "plotclock status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "plotclock enable on")==0) {
    PlotClockIsEnabled = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "plotclock enable off")==0) {
    PlotClockIsEnabled = FALSE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "plotclock calibrate on")==0) {
    PlotClockCalibrateIsOn = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "plotclock calibrate off")==0) {
    PlotClockCalibrateIsOn = FALSE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "plotclock lift 0")==0) {
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "plotclock lift 1")==0) {
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "plotclock lift 2")==0) {
    lift(PLOTCLOCK_LIFT_POS_PARKING);
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, "plotclock write ", sizeof("plotclock write ")-1)==0) {
    uint8_t hour, minute, second, hsecond;
    const uint8_t *p;

    p = cmd + sizeof("plotclock write ")-1;
    if (UTIL1_ScanTime(&p, &hour, &minute, &second, &hsecond)==ERR_OK) {
      PlotClockPrintTime(hour, minute);
    }
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, "plotclock moveto ", sizeof("plotclock moveto ")-1)==0) {
    int8_t x, y;
    const uint8_t *p;

    p = cmd + sizeof("plotclock moveto ")-1;
    if (UTIL1_ScanDecimal8sNumber(&p, &x)==ERR_OK && UTIL1_ScanDecimal8sNumber(&p, &y)==ERR_OK) {
      drawTo(x, y);
    }
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "plotclock vibrate on")==0) {
    Vibra_SetVal();
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "plotclock vibrate off")==0) {
    Vibra_ClrVal();
    *handled = TRUE;
  }
  return ERR_OK;
}


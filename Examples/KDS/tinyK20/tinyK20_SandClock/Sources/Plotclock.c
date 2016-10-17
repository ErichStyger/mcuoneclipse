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

static bool PlotClockIsEnabled = TRUE; /* if clock is enabled */
static bool PlotClockCalibrateIsOn = FALSE; /* if calibration mode is on */

// When in calibration mode, adjust the following factor until the servos move exactly 90 degrees
static int SERVOFAKTOR = 300;

// Zero-position of left and right servo
// When in calibration mode, adjust the NULL-values so that the servo arms are at all times parallel
// either to the X or Y axis
static int SERVOLEFTNULL = 1590;
static int SERVORIGHTNULL = 1210;

// lift positions of lifting servo
static int LIFT0 = 1300; // on drawing surface
static int LIFT1 = 1200;  // between numbers
static int LIFT2 = 1100;  // going towards sweeper
static int LIFT_INIT = 1100; /* start/reset position */
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
static volatile double lastX = 75;
static volatile double lastY = 47.5;
static int last_min = 0;

// speed of lifting arm, higher is slower
#define LIFTSPEED 1500

// length of arms
#define L1 35
#define L2 55.1
#define L3 13.2

// origin points of left and right servo
#define O1X 22
#define O1Y -25
#define O2X 47
#define O2Y -25

#define M_PI    3.14159265358979323846

static void delay(uint32_t ms) {
  vTaskDelay(pdMS_TO_TICKS(ms));
}

static void delayMicroseconds(uint32_t us) {
  WAIT1_Waitus(us);
}

static void servo_writeMicroseconds(PlotClockServo servo, uint16_t us) {
  /* servos:
   * 0: lifting servo PLOTCLOCK_SERVO_LIFT
   * 1: left servo
   * 2: right servo
   */
  /* tick values, for 0 to 1500 us */
  SERVO_WriteDutyMicroSeconds(PCA9685_I2C_DEFAULT_ADDR, (uint8_t)servo, us, SERVO_MIN_TICKS, SERVO_MAX_TICKS);
}

static double return_angle(double a, double b, double c) {
  // cosine rule for angle between c and a
  return acos((a * a + c * c - b * b) / (2 * a * c));
}

static void set_XY(double Tx, double Ty) {
  delay(1);
  double dx, dy, c, a1, a2, Hx, Hy;

  // calculate triangle between pen, servoLeft and arm joint
  // cartesian dx/dy
  dx = Tx - O1X;
  dy = Ty - O1Y;

  // polar length (c) and angle (a1)
  c = sqrt(dx * dx + dy * dy); //
  a1 = atan2(dy, dx); //
  a2 = return_angle(L1, L2, c);

  servo_writeMicroseconds(PLOTCLOCK_SERVO_LEFT, floor(((a2 + a1 - M_PI) * SERVOFAKTOR) + SERVOLEFTNULL));

  // calculate join arm point for triangle of the right servo arm
  a2 = return_angle(L2, L1, c);
  Hx = Tx + L3 * cos((a1 - a2 + 0.621) + M_PI); //36,5°
  Hy = Ty + L3 * sin((a1 - a2 + 0.621) + M_PI);

  // calculate triangle between pen joint, servoRight and arm joint
  dx = Hx - O2X;
  dy = Hy - O2Y;

  c = sqrt(dx * dx + dy * dy);
  a1 = atan2(dy, dx);
  a2 = return_angle(L1, (L2 - L3), c);

  servo_writeMicroseconds(PLOTCLOCK_SERVO_RIGHT, floor(((a1 - a2) * SERVOFAKTOR) + SERVORIGHTNULL));
}

static void drawTo(double pX, double pY) {
  double dx, dy, c;
  int i;

  // dx dy of new point
  dx = pX - lastX;
  dy = pY - lastY;
  //path length in mm, times 4 equals 4 steps per mm
  c = floor(4 * sqrt(dx * dx + dy * dy));

  if (c < 1) {
    c = 1;
  }
  for (i = 0; i <= c; i++) {
    // draw line point by point
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
    // room to optimize  !
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

// Writing numeral with bx by being the bottom left origin point. Scale 1 equals a 20 mm high font.
// The structure follows this principle: move to first start point of the numeral, lift down, draw numeral, lift up
static void number(float bx, float by, int num, float scale) {
  switch (num) {
  case 0:
    drawTo(bx + 12 * scale, by + 6 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    bogenGZS(bx + 7 * scale, by + 10 * scale, 10 * scale, -0.8, 6.7, 0.5);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 1:
    drawTo(bx + 3 * scale, by + 15 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    drawTo(bx + 10 * scale, by + 20 * scale);
    drawTo(bx + 10 * scale, by + 0 * scale);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 2:
    drawTo(bx + 2 * scale, by + 12 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    bogenUZS(bx + 8 * scale, by + 14 * scale, 6 * scale, 3, -0.8, 1);
    drawTo(bx + 1 * scale, by + 0 * scale);
    drawTo(bx + 12 * scale, by + 0 * scale);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 3:
    drawTo(bx + 2 * scale, by + 17 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 3, -2, 1);
    bogenUZS(bx + 5 * scale, by + 5 * scale, 5 * scale, 1.57, -3, 1);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 4:
    drawTo(bx + 10 * scale, by + 0 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    drawTo(bx + 10 * scale, by + 20 * scale);
    drawTo(bx + 2 * scale, by + 6 * scale);
    drawTo(bx + 12 * scale, by + 6 * scale);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 5:
    drawTo(bx + 2 * scale, by + 5 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    bogenGZS(bx + 5 * scale, by + 6 * scale, 6 * scale, -2.5, 2, 1);
    drawTo(bx + 5 * scale, by + 20 * scale);
    drawTo(bx + 12 * scale, by + 20 * scale);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 6:
    drawTo(bx + 2 * scale, by + 10 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    bogenUZS(bx + 7 * scale, by + 6 * scale, 6 * scale, 2, -4.4, 1);
    drawTo(bx + 11 * scale, by + 20 * scale);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 7:
    drawTo(bx + 2 * scale, by + 20 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    drawTo(bx + 12 * scale, by + 20 * scale);
    drawTo(bx + 2 * scale, by + 0);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 8:
    drawTo(bx + 5 * scale, by + 10 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 4.7, -1.6, 1);
    bogenGZS(bx + 5 * scale, by + 5 * scale, 5 * scale, -4.7, 2, 1);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 9:
    drawTo(bx + 9 * scale, by + 11 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    bogenUZS(bx + 7 * scale, by + 15 * scale, 5 * scale, 4, -0.5, 1);
    drawTo(bx + 5 * scale, by + 0);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  case 111:
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
    break;
  case 11: /* special: draw ':' */
    drawTo(bx + 5 * scale, by + 15 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    bogenGZS(bx + 5 * scale, by + 15 * scale, 0.1 * scale, 1, -1, 1);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    drawTo(bx + 5 * scale, by + 5 * scale);
    lift(PLOTCLOCK_LIFT_POS_DRAW);
    bogenGZS(bx + 5 * scale, by + 5 * scale, 0.1 * scale, 1, -1, 1);
    lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
    break;
  }
}

void PlotClock_Setup(void) {
  servoLift = LIFT_INIT;
  last_min = 0;
  servo_writeMicroseconds(PLOTCLOCK_SERVO_LIFT, servoLift);
  drawTo(75.2, 47); /* move to parking position */
  lift(PLOTCLOCK_LIFT_POS_DRAW); /* move down to surface */
  delay(1000);
}

void PlotClock_Loop(void) {
  if (!PlotClockIsEnabled) {
    return; /* clock not enabled */
  }
  if (PlotClockCalibrateIsOn) {
    // Servo horns will have 90° between movements, parallel to x and y axis
    drawTo(-3, 29.2);
    delay(500);
    drawTo(74.1, 28);
    delay(500);
  } else {
    TIMEREC time;

    TmDt1_GetTime(&time);
    if (last_min != time.Min) {
      float digitScale = 1.5;

      //lift(PLOTCLOCK_LIFT_POS_DRAW);
      //number(3, 3, 111, 1); /* sweep existing number */
      lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
      number(5, 25, time.Hour/10, digitScale); /* write first digit of hour */
      number(19, 25, time.Hour%10, digitScale); /* write second digit */
      number(28, 25, 11, digitScale); /* draw ':' */
      number(34, 25, time.Min/10, digitScale); /* write most significant digit of hour */
      number(48, 25, time.Min%10, digitScale); /* second digit */
      lift(PLOTCLOCK_LIFT_POS_PARKING);
      drawTo(74.2, 47.5); /* move to parking position */
      lift(PLOTCLOCK_LIFT_POS_BETWEEN_DRAW);
      last_min = time.Min;
    }
  }
}

static uint8_t PrintStatus(CLS1_ConstStdIOType *io) {
  uint8_t buf[48];

  CLS1_SendStatusStr((unsigned char*)"plotclock", (const unsigned char*)"\r\n", io->stdOut);

  CLS1_SendStatusStr((unsigned char*)"  Enabled", PlotClockIsEnabled?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  Calibrating", PlotClockCalibrateIsOn?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);

  buf[0] = '\0'; UTIL1_Num16uToStr(buf, sizeof(buf), SERVOFAKTOR); UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr((unsigned char*)"  FAKTOR", buf, io->stdOut);

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
  buf[0] = '\0'; UTIL1_Num16uToStr(buf, sizeof(buf), LIFTSPEED); UTIL1_strcat(buf, sizeof(buf), " us (higher is sloser)\r\n");
  CLS1_SendStatusStr((unsigned char*)"  LIFTSPEED", buf, io->stdOut);

  return ERR_OK;
}

uint8_t PlotClock_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "Plotclock help")==0) {
    CLS1_SendHelpStr((unsigned char*)"plotclock", (const unsigned char*)"Group of plotclock commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  enable (on|off)", (const unsigned char*)"Turns the clock on or off\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  calibrate (on|off)", (const unsigned char*)"Calibration mode on or off\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  lift (0|1|2)", (const unsigned char*)"Lift servo arm\r\n", io->stdOut);
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
  }
  return ERR_OK;
}


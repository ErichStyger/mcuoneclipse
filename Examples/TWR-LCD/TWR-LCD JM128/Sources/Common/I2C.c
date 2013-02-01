/** ###################################################################
**     Filename  : I2C.C
**     Project   : TWR_LCD_JM128
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 06.02.2010, 12:17
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE I2C */

#include "Platform.h"

#if PL_HAS_I2C_COMM

#include "I2C.h"
#include "I2C1.h"
#include "EVNT1.h"
#include "Slider.h"
#if PL_HAS_RUNNER
  #include "Runner.h"
#endif

typedef enum { /* these enumeration values are used as message kinds and sent over I2C */
  I2C_MSG_KEY, /* keyboard or navigation message, followed by uint8_t for the keyboard code */
  I2C_MSG_MOTOR_SPEED, /* motor speed, followed by int32_t (Big Endian) for speed */
  I2C_ACCEL_XYZ, /* accelerometer X, Y and Z, followed by 3 int16_t (Big Endian) accelerometer values */
  I2C_MSG_PID_SPEED, /* PID desired speed, followed by int32_t (Big Endian) for speed */
  I2C_MSG_GET_CMD,    /* request for command line string */
  I2C_MSG_RUNNER
} I2C_MessageKind;

#define I2C_PRE_BYTE0 0x27
#define I2C_PRE_BYTE1 0xFF

#define I2C_MSG_HEADER_LEN    3 /* prebyte0, prebyte1, zero end byte */

#define I2C_ACCEL_MSG_LEN     7 /* id, plus 3x2 bytes */
#define I2C_ACCEL_MSG_MAX_IDX (I2C_ACCEL_MSG_LEN+I2C_MSG_HEADER_LEN)

#define I2C_MOTOR_MSG_LEN     5 /* id plus 4 bytes */
#define I2C_MOTOR_MSG_MAX_IDX (I2C_MOTOR_MSG_LEN+I2C_MSG_HEADER_LEN)

#define I2C_PID_MSG_LEN       5 /* id plus 4 bytes */
#define I2C_PID_MSG_MAX_IDX   (I2C_PID_MSG_LEN+I2C_MSG_HEADER_LEN)

#define I2C_GET_CMD_MSG_LEN       1 /* id only */
#define I2C_GET_CMD_MSG_MAX_IDX   (I2C_GET_CMD_MSG_LEN+I2C_MSG_HEADER_LEN)

static int16_t AccelX, AccelY, AccelZ;
static int32_t motorSpeed, PIDSpeed;
static bool sendCmd = FALSE;
static char buf[32];
static uint8_t bufIdx=0;

int16_t I2C_GetAccelX(void) {
  return AccelX;
}

int16_t I2C_GetAccelY(void) {
  return AccelY;
}

int16_t I2C_GetAccelZ(void) {
  return AccelZ;
}

int32_t I2C_GetMotorSpeed(void) {
  return motorSpeed;
}

int32_t I2C_GetPIDSpeed(void) {
  return PIDSpeed;
}

void I2C_SendCmd(void) {
  if (sendCmd) {
#if PL_HAS_UI
    word snt;
    char buf[32];

#if PL_HAS_RUNNER
    buf[0] = '@';
    buf[1] = '\0';
    RUNNER_GetCmdString(buf, sizeof(buf));
#else
    SLIDER_GetCmdString(buf, sizeof(buf));
#endif
    (void)I2C1_SendBlock(buf, sizeof(buf), &snt);
#endif /* PL_HAS_UI */
    sendCmd = FALSE;
  }
}

#if PL_HAS_RUNNER
  static char RunnerBuf[I2C_RUNNER_I2C_MSG_SIZE];
  /* using a queue */
  static xQueueHandle I2C_RunnerQueue; /* message queue for runners received through I2C */
  #define I2C_RUNNER_MSG_QUEUE_LENGTH       24 /* number of queue items */
  #define I2C_Runner_MSG_QUEUE_ITEM_SIZE    I2C_RUNNER_I2C_MSG_SIZE /* size of each queue item */
#endif

#if PL_HAS_RUNNER
uint8_t I2C_GetRunnerMessage(char *buf, size_t bufSize) {
  if (I2C_RunnerQueue==NULL || bufSize<I2C_RUNNER_I2C_MSG_SIZE) {
    return ERR_FAILED;
  }
  if (FRTOS1_xQueueReceive(I2C_RunnerQueue, buf, 0)==pdPASS) { /* non blocking queue receive */
    return ERR_OK;
  }
  return ERR_RXEMPTY;
}
#endif


void I2C_OnReceiveData(void) {
#if PL_IS_I2C_SLAVE
  uint8_t data, res;
  uint16_t nofBytesReceived;

  res = I2C1_RecvBlock(&data, 1, &nofBytesReceived);
  if (res == ERR_OK && nofBytesReceived==1) { /* ok, no error */
    if (bufIdx==0 && data==I2C_PRE_BYTE0) {
      buf[0] = data;
      bufIdx++;
      return;
    } else if (bufIdx==1 && data==I2C_PRE_BYTE1 && buf[0]==I2C_PRE_BYTE0) {
      buf[1] = data;
      bufIdx++;
      return;
    } else if (bufIdx==2) {
      buf[2] = data; /* size */
      bufIdx++;
      return;
    /*------------------------------------------------*/
    } else if (bufIdx==3 && data==I2C_MSG_MOTOR_SPEED && buf[2]==I2C_MOTOR_MSG_LEN) { /* start of motor speed message */
      buf[3] = data; /* I2C_MSG_MOTOR_SPEED */
      bufIdx++;
      return;
    } else if (bufIdx>=4 && buf[3]==I2C_MSG_MOTOR_SPEED && bufIdx <= I2C_MOTOR_MSG_MAX_IDX) { /* motor speed message */
      buf[bufIdx++] = data;
    /*------------------------------------------------*/
    } else if (bufIdx==3 && data==I2C_MSG_PID_SPEED && buf[2]==I2C_PID_MSG_LEN) { /* start of motor speed message */
      buf[3] = data; /* I2C_MSG_PID_SPEED */
      bufIdx++;
      return;
    } else if (bufIdx>=4 && buf[3]==I2C_MSG_PID_SPEED && bufIdx <= I2C_PID_MSG_MAX_IDX) { /* motor speed message */
      buf[bufIdx++] = data;
    /*------------------------------------------------*/
    } else if (bufIdx==3 && data==I2C_ACCEL_XYZ && buf[2]==I2C_ACCEL_MSG_LEN) { /* start of Accel message */
      buf[3] = data; /* I2C_ACCEL_XYZ */
      bufIdx++;
      return;
    } else if (bufIdx>=4 && buf[3]==I2C_ACCEL_XYZ && bufIdx <= I2C_ACCEL_MSG_MAX_IDX) { /* Accel message */
      buf[bufIdx++] = data;
    /*------------------------------------------------*/
    } else if (bufIdx==3 && data==I2C_MSG_GET_CMD && buf[2]==I2C_GET_CMD_MSG_LEN) { /* start of GetCMD message */
      buf[3] = data; /* I2C_GET_CMD */
      bufIdx++;
      return;
    } else if (bufIdx>=4 && buf[3]==I2C_MSG_GET_CMD && bufIdx <= I2C_GET_CMD_MSG_MAX_IDX) { /* GetCmd message */
      buf[bufIdx++] = data;
    /*------------------------------------------------*/
#if PL_HAS_RUNNER
    } else if (bufIdx==3 && data==I2C_MSG_RUNNER ) { /* start of runner message */
      buf[3] = data; /* I2C_MSG_RUNNER */
      bufIdx++;
      return;
    } else if (bufIdx>=4 && buf[3]==I2C_MSG_RUNNER && bufIdx < sizeof(buf)) { /* runner message */
      buf[bufIdx++] = data;
      if (data != '\0') {
        return; /* get next byte */
      }
#endif
    } else {
      bufIdx = 0;
      return;
    }
  } else { /* error */
    bufIdx = 0;
    return;
  }
  if (data==0) { /* message finished? */
    if (buf[3]==I2C_ACCEL_XYZ && buf[2]==I2C_ACCEL_MSG_LEN && bufIdx>I2C_ACCEL_MSG_MAX_IDX) { /* message finished */
      AccelX = (int16_t)((buf[4]<<8)|buf[5]);
      AccelY = (int16_t)((buf[6]<<8)|buf[7]);
      AccelZ = (int16_t)((buf[8]<<8)|buf[9]);
      bufIdx = 0; /* message completed */
    } else if (buf[3]==I2C_MSG_MOTOR_SPEED && buf[2]==I2C_MOTOR_MSG_LEN && bufIdx>I2C_MOTOR_MSG_MAX_IDX) { /* message finished */
      motorSpeed = (int32_t)((buf[4]<<24)|(buf[5]<<16)|(buf[6]<<8)|buf[7]);
      bufIdx = 0; /* message completed */
    } else if (buf[3]==I2C_MSG_PID_SPEED && buf[2]==I2C_PID_MSG_LEN && bufIdx>I2C_PID_MSG_MAX_IDX) { /* message finished */
      PIDSpeed = (int32_t)((buf[4]<<24)|(buf[5]<<16)|(buf[6]<<8)|buf[7]);
      bufIdx = 0; /* message completed */
    } else if (buf[3]==I2C_MSG_GET_CMD && buf[2]==I2C_GET_CMD_MSG_LEN && bufIdx>I2C_GET_CMD_MSG_MAX_IDX) { /* message finished */
      sendCmd = TRUE;
      bufIdx = 0; /* message completed */
#if PL_HAS_RUNNER
    } else if (buf[3]==I2C_MSG_RUNNER) { /* message finished */
      UTIL1_strcpy(RunnerBuf, sizeof(RunnerBuf), &buf[4]);
      bufIdx = 0; /* message completed */
      if (I2C_RunnerQueue!=NULL) {
        signed portBASE_TYPE higherTaskWoken;

        FRTOS1_xQueueSendToBackFromISR(I2C_RunnerQueue, RunnerBuf, &higherTaskWoken);
      }
#endif
    }
  }
  if (bufIdx>sizeof(buf)) {
    bufIdx = 0;
  }
#else
#if PL_APP_MODE_I2C_TWR
  byte res;
  byte buf[1];
  word nofBytesReceived;

  res = I2C1_RecvBlock(&buf, sizeof(buf), &nofBytesReceived);
  if (res == ERR_OK) {
    switch(buf[0]) {
      case EVNT1_BUTTON_UI_LEFT:
      case EVNT1_BUTTON_UI_RIGHT:
      case EVNT1_BUTTON_UI_UP:
      case EVNT1_BUTTON_UI_DOWN:
      case EVNT1_BUTTON_UI_MIDDLE:
        EVNT1_SetEvent(buf[0]);
        break;
    } /* switch */
  }
#endif
#endif
}

void I2C_OnSendData(void) {
}

void I2C_HandleEvent(byte event) {
#if PL_APP_MODE_I2C_LCD
  switch(event) {
    case EVNT1_BUTTON_UI_LEFT:
    case EVNT1_BUTTON_UI_RIGHT:
    case EVNT1_BUTTON_UI_UP:
    case EVNT1_BUTTON_UI_DOWN:
    case EVNT1_BUTTON_UI_MIDDLE:
      (void)I2C1_SendChar(event);
      break;
  } /* switch */
#else
  (void)event;
#endif
}

void I2C_ClearBuffers(void) {
  I2C1_ClearTxBuf();
  I2C1_ClearRxBuf();
}

void I2C_Init(void) {
#if PL_IS_I2C_MASTER
  I2C1_SetMode(TRUE); /* master mode */
#elif PL_IS_I2C_SLAVE
  I2C1_SetMode(FALSE); /* slave mode */
#endif
#if PL_HAS_RUNNER
  I2C_RunnerQueue = FRTOS1_xQueueCreate(I2C_RUNNER_MSG_QUEUE_LENGTH, I2C_Runner_MSG_QUEUE_ITEM_SIZE); /* create Communication queue */
  if (I2C_RunnerQueue==NULL) {
    for(;;) {} /* out of memory? */
  }
#endif
}

#endif /* PL_HAS_I2C_COMM */

/* END I2C */

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
#include "FRTOS1.h"
#if PL_HAS_RUNNER
  #include "Runner.h"
#endif

#define I2C_LCD_ADDR_MOTOR_ACTUAL_SPEED   0x00 /* 4 bytes, actual motor speed */
#define I2C_LCD_ADDR_MOTOR_DESIRED_SPEED  0x04 /* 4 bytes, desired motor speed */
#define I2C_LCD_ADDR_PID_P                0x08 /* 4 bytes, PID P value */
#define I2C_LCD_ADDR_PID_I                0x0C /* 4 bytes, PID I value */
#define I2C_LCD_ADDR_PID_D                0x10 /* 4 bytes, PID D value */
#define I2C_LCD_ADDR_ACCEL_X              0x14 /* 2 bytes, accelerometer X value */
#define I2C_LCD_ADDR_ACCEL_Y              0x16 /* 2 bytes, accelerometer Y value */
#define I2C_LCD_ADDR_ACCEL_Z              0x18 /* 2 bytes, accelerometer Z value */
#define I2C_LCD_ADDR_NAV_KEY              0x1A /* 1 byte, navigation key  */
#define I2C_LCD_ADDR_MOTOR_PWM            0x1B /* 1 byte, PWM (-100..+100%) value */
#define I2C_LCD_ADDR_CMD_LENGTH           0x1C /* 1 bytes, size (in bytes) of the command string, including the zero byte */
#define I2C_LCD_ADDR_CMD_STR              0x1D /* 32 bytes, zero terminated command string */
#define I2C_LCD_ADDR_EKG_HEART_RATE       0x3D /* 1 byte, EKG heart rate (unsigned) */
#define I2C_LCD_ADDR_EKG_RAW              0x3E /* 32x2 bytes, EKG raw value (signed)  */
#define I2C_LCD_ADDR_EKG_NEW_DATA_READY   0xA1 /* 1 byte, EKG raw value (signed)  */

typedef struct {
  int32_t motorActualSpeed;   /* 0x00 I2C_LCD_ADDR_MOTOR_ACTUAL_SPEED, 4 bytes */
  int32_t motorDesiredSpeed;  /* 0x04 I2C_LCD_ADDR_MOTOR_DESIRED_SPEED, 4 bytes */
  int32_t motorPID_P;         /* 0x08 I2C_LCD_ADDR_PID_P, 2 bytes */
  int32_t motorPID_I;         /* 0x0C I2C_LCD_ADDR_PID_I, 2 bytes */
  int32_t motorPID_D;         /* 0x10 I2C_LCD_ADDR_PID_D, 2 bytes */
  int16_t accelX;             /* 0x14 I2C_LCD_ADDR_ACCEL_X, 2 bytes */
  int16_t accelY;             /* 0x16 I2C_LCD_ADDR_ACCEL_Y, 2 bytes */
  int16_t accelZ;             /* 0x18 I2C_LCD_ADDR_ACCEL_Z, 2 bytes */
  int8_t navKey;              /* 0x1A I2C_LCD_ADDR_NAV_KEY, 1 byte */
  int8_t motorPWM;            /* 0x1B I2C_LCD_ADDR_MOTOR_PWM, 1 byte */
  uint8_t cmdLength;          /* 0x1C I2C_LCD_ADDR_CMD_LENGTH, 1 byte */
  int8_t cmd[32];             /* 0x1D I2C_LCD_ADDR_CMD_STR, 32 bytes, zero terminated */
  uint8_t ekgHeartRate;       /* 0x3D I2C_LCD_ADDR_EKG_HEART_RATE, 1 byte */
  int8_t ekgRaw[64];          /* 0x3E I2C_LCD_ADDR_EKG_RAW, 64 bytes (32 int values, little endian) */
  int8_t ekgNewReady;         /* 0xA1 I2C_LCD_ADDR_EKG_NEW_DATA_READY, 1 byte, 0x1 indicating that new data is ready */
} Data;

typedef struct I2C_Device_ {
  bool nextRXisMemAddress; /* next received character is the address */
  uint8_t addr; /* memory memDevice address */
  union {
    uint8_t mem[4+4+2+2+2+1+1+32+1+64+1]; /* memory memDevice itself */
    Data data;
  } u; /* memory union */
} I2C_Device;

static I2C_Device memDevice;

#define I2C_DEBUG_LOG  0  /* if we create debugging diagnostic */

typedef enum I2C_DEBUG_EVENTS_ {
  I2C_DEBUG_WriteReq=1, /* start with one, as array is initialized with zeros */
  I2C_DEBUG_ReadReq=2,
  I2C_DEBUG_RxChar=3,
  I2C_DEBUG_TxChar=4
} I2C_DEBUG_EVENTS;

/* typical sequences (the first argument is the memory address, followed by data bytes):
 * "read 0xa"            ==> OnWriteReq(1), OnRxChar(3)[0xa], OnReadReq(2), OnTxChar(4)[0xa]
 * "write 0xa 0xbb"      ==> OnWriteReq(1), OnRxChar(3)[0xa], OnRxChar(3)[0xbb]
 * "write 0xa 0xbb 0xcc" ==> OnWriteReq(1), OnRxChar(3)[0xa], OnRxChar(3)[0xbb], OnRxChar(3)[0xcc]
 */

#if I2C_DEBUG_LOG
static I2C_DEBUG_EVENTS dbg[32]; /* array of debug events */
static uint8_t dbgIdx = 0; /* index into dbg[] array */

static void dbgF(I2C_DEBUG_EVENTS event) {
  dbg[dbgIdx++]=event;
  if (dbgIdx==sizeof(dbg)) { /* wrap over buffer */
    dbgIdx=0;
  }
}
#else
  #define dbgF(n) /* nothing */
#endif

void I2C_OnWriteReq(void) {
  /* Called by a master 'write' request on the bus. It is always followed by the device memory address.
   * At this time we have the device address on the bus, but not the address yet. */
  dbgF(I2C_DEBUG_WriteReq);
  I2C_ClearBuffers();
  memDevice.nextRXisMemAddress = TRUE; /* next byte on bus will be memory address */
}

void I2C_OnReadReq(void) {
  /* called by a master 'read' request on the bus */
  /* Write[@]+ACK
   * addr+ACK
   * Read[@]+ACK  <<= we are here!
   * data at mem[addr]  << Send this data
   */
  word nof;
  uint8_t data;

  dbgF(I2C_DEBUG_ReadReq);
  if (memDevice.addr<sizeof(memDevice.u)) {
    data = memDevice.u.mem[memDevice.addr];
    memDevice.addr++; /* increment address counter */
  } else {
    data = 0xFF; /* undefined byte */
  }
  (void)I2C1_SendBlock(&data, 1, &nof);
}

void I2C_OnTxChar(void) {
  /* request to send a character, this is a read from the memory */
  word nof;
  uint8_t data;

  dbgF(I2C_DEBUG_TxChar);
  if (memDevice.addr<sizeof(memDevice.u)) {
    data = memDevice.u.mem[memDevice.addr];
    memDevice.addr++; /* increment address counter */
  } else {
    data = 0xFF; /* undefined data */
  }
  (void)I2C1_SendBlock(&data, 1, &nof);
}

void I2C_OnRxChar(void) {
  uint8_t data;
  uint16_t nofBytesReceived;
  uint8_t res;

  dbgF(I2C_DEBUG_RxChar);
  res = I2C1_RecvBlock(&data, 1, &nofBytesReceived);
  if (res == ERR_OK) { /* ok, no error */
    if (memDevice.nextRXisMemAddress) { /* it is the memory address received from the master */
      memDevice.nextRXisMemAddress = FALSE;
      memDevice.addr = data;
    } else { /* data byte received from the master to write to the memory */
      if (memDevice.addr<sizeof(memDevice.u)) {
        memDevice.u.mem[memDevice.addr] = data;
        memDevice.addr++;
      }
    }
  }
}

int16_t I2C_GetAccelX(void) {
  int16_t val;

  EnterCritical();
  val = memDevice.u.data.accelX;
  ExitCritical();
  return val;
}

int16_t I2C_GetAccelY(void) {
  int16_t val;

  EnterCritical();
  val = memDevice.u.data.accelY;
  ExitCritical();
  return val;
}

int16_t I2C_GetAccelZ(void) {
  int16_t val;

  EnterCritical();
  val = memDevice.u.data.accelZ;
  ExitCritical();
  return val;
}

uint8_t I2C_GetEKGHeartRate(void) {
  uint8_t val;

  EnterCritical();
  val = memDevice.u.data.ekgHeartRate;
  ExitCritical();
  return val;
}

bool I2C_GetEKGIsDataReady(void) {
  bool val;

  EnterCritical();
  val = (bool)(memDevice.u.data.ekgNewReady!=0);
  ExitCritical();
  return val;
}

void I2C_ResetEKGIsDataReady(void) {
  EnterCritical();
  memDevice.u.data.ekgNewReady = 0;
  ExitCritical();
}


int16_t I2C_GetEKGRaw(uint8_t index) {
  int8_t valH, valL;
  int16_t val;

  index *= 2; /* transform word index into byte index */
  if (index>=sizeof(memDevice.u.data.ekgRaw)) {
    return 0; /* out of range! */
  }
  EnterCritical();
  valH = memDevice.u.data.ekgRaw[index];
  valL = memDevice.u.data.ekgRaw[index+1];
  ExitCritical();
  val = (int16_t)(valH+(valL<<8));
  return val;
}

int8_t I2C_GetMotorPWMPercent(void) {
  int8_t val;

  EnterCritical();
  val = memDevice.u.data.motorPWM;
  ExitCritical();
  return val;
}

void I2C_SetMotorPWMPercent(int8_t percent) {
  EnterCritical();
  memDevice.u.data.motorPWM = percent;
  ExitCritical();
}


int32_t I2C_GetMotorActualSpeed(void) {
  int32_t val;

  EnterCritical();
  val = memDevice.u.data.motorActualSpeed;
  ExitCritical();
  return val;
}

int32_t I2C_GetMotorDesiredSpeed(void) {
  int32_t val;

  EnterCritical();
  val = memDevice.u.data.motorDesiredSpeed;
  ExitCritical();
  return val;
}

void I2C_SetMotorDesiredSpeed(int32_t speed) {
  EnterCritical();
  memDevice.u.data.motorDesiredSpeed = speed;
  ExitCritical();
}

int32_t I2C_GetMotorPID_P(void) {
  int32_t val;

  EnterCritical();
  val = memDevice.u.data.motorPID_P;
  ExitCritical();
  return val;
}

void I2C_SetMotorPID_P(int32_t p) {
  EnterCritical();
  memDevice.u.data.motorPID_P = p;
  ExitCritical();
}

int32_t I2C_GetMotorPID_I(void) {
  int32_t val;

  EnterCritical();
  val = memDevice.u.data.motorPID_I;
  ExitCritical();
  return val;
}

void I2C_SetMotorPID_I(int32_t i) {
  EnterCritical();
  memDevice.u.data.motorPID_I = i;
  ExitCritical();
}

int32_t I2C_GetMotorPID_D(void) {
  int32_t val;

  EnterCritical();
  val = memDevice.u.data.motorPID_D;
  ExitCritical();
  return val;
}

void I2C_SetMotorPID_D(int32_t d) {
  EnterCritical();
  memDevice.u.data.motorPID_D = d;
  ExitCritical();
}


void I2C_StoreCmd(void) {
#if PL_HAS_UI
    unsigned char buf[32];
    uint8_t strSize;

#if PL_HAS_RUNNER
    buf[0] = '@';
    buf[1] = '\0';
    RUNNER_GetCmdString(buf, sizeof(buf));
#elif PL_HAS_SLIDER
    SLIDER_GetCmdString(buf, sizeof(buf));
#else
    buf[0] = '\0';
#endif
    if (buf[0]!='\0') {
      uint8_t cnt=3;

      while(cnt>0 && memDevice.u.data.cmdLength!=0) { /* poll cmdLength: this will be set to zero by the master if it is ok to place the string */
        FRTOS1_vTaskDelay(50/portTICK_RATE_MS); /* give master some time to clear the flasg */
        cnt--;
      }
      if (cnt==0) { /* timeout. Will loose that command. Not ideal, but simple :-) */
        return; /* get out here */
      }
      strSize = (uint8_t)(UTIL1_strlen(buf)+1); /* size of string including zero byte */
      if (strSize>sizeof(memDevice.u.data.cmd)) {
        strSize = sizeof(memDevice.u.data.cmd);
      }
      EnterCritical();
      memDevice.u.data.cmdLength = strSize;
      UTIL1_strcpy(memDevice.u.data.cmd, sizeof(memDevice.u.data.cmd), buf);
      ExitCritical();
    }
#endif /* PL_HAS_UI */
}


#if 0 &&  PL_APP_MODE_I2C_TWR
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
  I2C1_Enable();
}

#endif /* PL_HAS_I2C_COMM */

/* END I2C */

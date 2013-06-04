/**
 *\file
 *\brief In this file, FreeRTOS starts and runs several tasks for demonstration.
 *\author Andreas Schoepfer andreas.schoepfer@stud.hslu.ch
 *\date 03.01.12
 */

#include "Application.h"
#include "FRTOS1.h"
#include "FSSH1.h"
#include <string.h>
#include "PCA1.h"
#include "LHIP.h"
#include "RHIP.h"
#include "LFEET.h"
#include "RFEET.h"
#include "ACCEL.h"
#include "touch.h"
#include "flashExt.h"

/*! enables walking-task*/
#define WALKING		1
/*! enables accel-task*/
#define ACCEL		1
/*! enables touch-task*/
#define TOUCH		1
/*! enables shell-task*/
#define SHELL		1

/*! Used for start and stop walking-task*/
static xTaskHandle walkHandle;
static bool enabledWalking;

static SetWalking(bool on) {
  static bool isWalking = TRUE;

  EnterCritical();
  if((on && isWalking) || !enabledWalking) { /* stop walking*/
    isWalking = FALSE;
    FRTOS1_vTaskSuspend(walkHandle);
    FSSH1_SendStr((const unsigned char*)"Stop walking\r\n", FSSH1_GetStdio()->stdOut);
  } else { /* start walking*/
    isWalking = TRUE;
    FRTOS1_vTaskResume(walkHandle);
    FSSH1_SendStr((const unsigned char*)"Start walking\r\n", FSSH1_GetStdio()->stdOut);
  }
  ExitCritical();
}

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
static uint8_t ParseCommand(const unsigned char *cmd, bool *handled, const FSSH1_StdIOType *io) {
  /* handling our own commands */
  uint8_t res=ERR_OK;

  if (UTIL1_strcmp((const char*)cmd, FSSH1_CMD_HELP)==0) {
    FSSH1_SendHelpStr((const unsigned char*)"walking on|off", (const unsigned char*)"Turn walking on or off\r\n", io->stdOut);
  } else if (UTIL1_strcmp((const char*)cmd, FSSH1_CMD_STATUS)==0) {
    FSSH1_SendStatusStr((const unsigned char*)"Walking", enabledWalking?(const unsigned char*)"on\r\n":(const unsigned char*)"off\r\n", io->stdOut);
  } else if (UTIL1_strcmp((const char*)cmd, "walking off")==0) {
    enabledWalking = FALSE;
    SetWalking(FALSE);
    *handled = TRUE;
  } else if (UTIL1_strcmp((const char*)cmd, "walking on")==0) {
    enabledWalking = TRUE;
    SetWalking(TRUE);
    *handled = TRUE;
  }
#if 0
  res=LFEET_ParseCommand(cmd, handled, io);
  if (res!=ERR_OK) {
    return res;
  }
  res=RFEET_ParseCommand(cmd, handled, io);
  if (res!=ERR_OK) {
    return res;
  }
  res=LHIP_ParseCommand(cmd, handled, io);
  if (res!=ERR_OK) {
    return res;
  }
  res=RHIP_ParseCommand(cmd, handled, io);
  if (res!=ERR_OK) {
    return res;
  }
#endif
  return res;
}

/**
 * \brief Walking Task. FSM to walk strait forward with the MechBot.
 * @param WalkingTask Task name
 * @param pvParameters Not used
 * @return void
 */
typedef enum {
  ROBO_LEAN_RIGHT,
  ROBO_ROTATE_HIP_RIGHT,
  ROBO_LEAN_LEFT,
  ROBO_ROTATE_HIP_LEFT
} ROBO_State;

static portTASK_FUNCTION(WalkingTask, pvParameters) {
  ROBO_State state=ROBO_ROTATE_HIP_LEFT;  /* state variable for FSM*/
  int16_t ms=500;   /* global wait variable for change walking speed*/

  (void)pvParameters; /* parameter not used */
  for(;;) {
	  switch(state) {
	    case ROBO_LEAN_RIGHT: 	/* lean right*/
	    	LFEET_MovePos(40,ms);
	    	RFEET_MovePos(110,ms);
	    	WAIT1_WaitOSms((uint16_t)ms);
	    	RFEET_MovePos(100,ms);
	    	WAIT1_WaitOSms((uint16_t)ms);
	    	state=ROBO_ROTATE_HIP_RIGHT;
	    	break;
	    case ROBO_ROTATE_HIP_RIGHT:	/* rotate hips*/
	    	LFEET_MovePos(127,ms);
	    	RHIP_MovePos(200,ms-200);
	    	LHIP_MovePos(200,ms-200);
	    	WAIT1_WaitOSms((uint16_t)ms);
	    	RFEET_MovePos(127,ms+200);/*  initPos*/
	    	WAIT1_WaitOSms((uint16_t)(ms+200));
	    	state=ROBO_LEAN_LEFT;
	    	break;
	    case ROBO_LEAN_LEFT:	/* lean left*/
	    	RFEET_MovePos(255,ms);
	    	LFEET_MovePos(170,ms);
	    	WAIT1_WaitOSms((uint16_t)(ms));
	    	LFEET_MovePos(180,ms);
	    	WAIT1_WaitOSms((uint16_t)(ms));
	    	state=ROBO_ROTATE_HIP_LEFT;
	    	break;
	    case ROBO_ROTATE_HIP_LEFT:	/* rotate hips*/
	    	RFEET_MovePos(127,ms);
	    	RHIP_MovePos(50,ms-200);
	    	LHIP_MovePos(50,ms-200);
	    	WAIT1_WaitOSms((uint16_t)(ms));
	    	LFEET_MovePos(127,ms+200);/* initPos*/
	    	WAIT1_WaitOSms((uint16_t)(ms+200));
	    	state=ROBO_LEAN_RIGHT;
	    	break;
	  } /* switch */
  }
}

/**
 * \brief AccelToLED Task. Represents acceleration of x-axis with LED's (like a water-level).
 * @param AccelToLEDTask Taskname
 * @param pvParameters Not used
 * @return void
 */
static portTASK_FUNCTION(AccelToLEDTask, pvParameters) {
  int16_t accelX;
  uint8_t ledNumOld = 4;
  uint8_t ledNumNew;

  (void)pvParameters;
  EnterCritical();
  PCA1_WriteI2CByte(PCA1_ADDR_REG_CONFIG, 0x00);  	/* all as output*/
  PCA1_ClearOutputBit(1);
  PCA1_ClearOutputBit(2);
  PCA1_ClearOutputBit(3);
  PCA1_SetOutputBit(4);								/* activate LED in the middle*/
  PCA1_ClearOutputBit(5);
  PCA1_ClearOutputBit(6);
  PCA1_ClearOutputBit(7);
  /* Dont write to Pin0 of IO-Expander1! (flash-CS)*/
  ACCEL_Init();
  if(ACCEL_CalibrateAxes() != ERR_OK) {
	  for(;;) {} /* error occurred*/
  }
  ExitCritical();
  for(;;) {
	  WAIT1_WaitOSms(50);
	  EnterCritical();
  	if(ACCEL_GetXmg(&accelX) != ERR_OK) {
  		for(;;) {}	/* error occurred!*/
  	}
  	ExitCritical();
    /* scale accelX (-1000..1000) to LEDs (IO-Exp Pin 1..7)*/
  	ledNumNew = (uint8_t)(((accelX+1000)*7/2000)+1);
  	if(ledNumNew < 1) {
  		ledNumNew = 1;
  	} else if(ledNumNew > 7) {
  		ledNumNew = 7;
  	}
  	if(ledNumNew != ledNumOld) {	/* change LED*/
  		EnterCritical();
  		PCA1_ClearOutputBit(ledNumOld);
  		PCA1_SetOutputBit(ledNumNew);
  		ExitCritical();
  	}
  	ledNumOld = ledNumNew;
  }
}

/**
 * \brief Touch Task. Starts and stops walking Task by touchsensor.
 * @param TouchTask Taskname
 * @param pvParameters Not used
 * @return void
 */
static portTASK_FUNCTION(TouchTask, pvParameters) {
	uint8_t errCode;
	uint16_t touchStatus;
	bool walking = TRUE;

	(void)pvParameters;
	TOUCH_init();
  WAIT1_WaitOSms(10);
  for(;;) {
    errCode=TOUCH_getELE(&touchStatus);
    if(errCode != ERR_OK) {
      for(;;) {} /* error occurred!*/
    }
    if(touchStatus!=0) {
      if (enabledWalking) {
        EnterCritical();
        if(walking) { /* stop walking*/
          walking = FALSE;
          SetWalking(FALSE);
        } else { /* start walking*/
          walking = TRUE;
          SetWalking(TRUE);
        }
        ExitCritical();
      }
      WAIT1_WaitOSms(1000);
    }
    WAIT1_WaitOSms(16); /* 16ms sampling time*/
  }
}

/**
 * \brief Shell Task. Task reads and writes to shell.
 * @param ShellTask Taskname
 * @param pvParameters Not used
 * @return void
 */
static portTASK_FUNCTION(ShellTask, pvParameters) {
  unsigned char cmd_buf[32];

  (void)pvParameters; /* parameter not used */
  /* print help and prompt */
  (void)FSSH1_ParseCommand((const unsigned char*)FSSH1_CMD_HELP, FSSH1_GetStdio(), ParseCommand);
  cmd_buf[0]='\0';
  for(;;) {
    (void)FSSH1_ReadAndParseLine(cmd_buf, sizeof(cmd_buf), FSSH1_GetStdio(), ParseCommand);
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  }
}

void APP_Start(void) {
#if SHELL
  if (FRTOS1_xTaskCreate(
        ShellTask,  /* pointer to the task */
        (signed char *)"Shell", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE+200, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
     for(;;){}; /* error! probably out of memory */
  }
#endif
#if WALKING
  if (FRTOS1_xTaskCreate(
          WalkingTask,  /* pointer to the task */
          (signed char *)"Walking", /* task name for kernel awareness debugging */
          configMINIMAL_STACK_SIZE+200, /* task stack size */
          (void*)NULL, /* optional task startup argument */
          tskIDLE_PRIORITY+3,  /* initial priority */
          &walkHandle  /* with xTaskhandle to control task by touchsensor*/
        ) != pdPASS) {
       for(;;){}; /* error! probably out of memory */
    }
#endif
#if ACCEL
  if (FRTOS1_xTaskCreate(
            AccelToLEDTask,  /* pointer to the task */
            (signed char *)"Accel", /* task name for kernel awareness debugging */
            configMINIMAL_STACK_SIZE+200, /* task stack size */
            (void*)NULL, /* optional task startup argument */
            tskIDLE_PRIORITY+2,  /* initial priority */
            (xTaskHandle*)NULL /* optional task handle to create */
          ) != pdPASS) {
         for(;;){}; /* error! probably out of memory */
      }
#endif
#if TOUCH
  if (FRTOS1_xTaskCreate(
            TouchTask,  /* pointer to the task */
            (signed char *)"Touch", /* task name for kernel awareness debugging */
            configMINIMAL_STACK_SIZE+100, /* task stack size */
            (void*)NULL, /* optional task startup argument */
            tskIDLE_PRIORITY+4,  /* initial priority */
            (xTaskHandle*)NULL  /*optional task handle to create */
          ) != pdPASS) {
         for(;;){}; /* error! probably out of memory */
      }
#endif
  FRTOS1_vTaskStartScheduler();
}

/*
 * ==========================================================================================
 * ==========================================================================================
 *                                    UNUSED METHODES
 * ==========================================================================================
 * ==========================================================================================
 */

/**
 * \brief Accel Task. Tests the acceleration sensor, by writing its accelvalues to the shell.
 * @param AccelTask Taskname
 * @param pvParameters Not used
 * @return void
 */
static portTASK_FUNCTION(AccelTask, pvParameters)  {
	int16_t accel[] = {0,0,0};
	uint8_t errCode;

	(void)pvParameters;
	ACCEL_Init();
	if(ACCEL_CalibrateAxes()!= ERR_OK) {
		for(;;) {}	/* error occurred!*/
	}
	for(;;) {
		WAIT1_WaitOSms(200);
		errCode = ACCEL_GetXYZmg(accel);
		if(errCode != ERR_OK) {
			for(;;) {}	/* error occurred!*/
		}
		FSSH1_SendStr((const unsigned char*)"X: ",FSSH1_GetStdio()->stdOut);
		FSSH1_SendNum16s(accel[0], FSSH1_GetStdio()->stdOut);
		FSSH1_SendStr((const unsigned char*)"\tY: ",FSSH1_GetStdio()->stdOut);
		FSSH1_SendNum16s(accel[1], FSSH1_GetStdio()->stdOut);
		FSSH1_SendStr((const unsigned char*)"\tZ: ",FSSH1_GetStdio()->stdOut);
		FSSH1_SendNum16s(accel[2], FSSH1_GetStdio()->stdOut);
		FSSH1_SendStr((const unsigned char*)"\r\n",FSSH1_GetStdio()->stdOut);
	}
}

/**
 * \brief Test method to control RFEET with accel of x-axis.
 * (Shown at interim demonstration)
 */
static void interimDemo(void) {
	int8_t accelX;
	int16_t feetVal;

	RFEET_Init();
    WAIT1_Waitms(20);
	ACCEL_Init();
	for(;;) {
	  ACCEL_GetRawX(&accelX);
	  feetVal=(int16_t)((accelX+64)*2);
	  if (feetVal>255) {
		  feetVal = 255;
	  } else if (feetVal<0) {
		  feetVal = 0;
	  }
	  RFEET_MovePos((uint8_t)feetVal, 20);
	  WAIT1_Waitms(40);
	}
}

/**
 * \brief Method to test the flash chip.
 * @return void
 */
static void TestFlash(void) {
	uint8_t errCode;
	uint8_t test=55;
	uint8_t result=27;
	uint32_t testAddr=0x0000F300;
	uint8_t status=1;

	FLASH_Init();
	enabledWalking = TRUE;
	WAIT1_Waitms(1000);
	errCode = FLASH_ReadStatusReg(&status);
	if(errCode!=ERR_OK) {
		for(;;) {}
	}
	FSSH1_SendStr((const unsigned char*)"\r\nStatus: ",FSSH1_GetStdio()->stdOut);
	FSSH1_SendNum16u(status,FSSH1_GetStdio()->stdOut);
	for(;;) {}
	errCode = FLASH_WriteByte(testAddr,&test);
	if(errCode!=ERR_OK) {
		for(;;) {}
	}
	errCode = FLASH_ReadByte(testAddr,&result);
	if(errCode!=ERR_OK) {
		for(;;) {}
	}
	FSSH1_SendStr((const unsigned char*)"\r\nOutput: ",FSSH1_GetStdio()->stdOut);
	FSSH1_SendNum16u(result,FSSH1_GetStdio()->stdOut);
}

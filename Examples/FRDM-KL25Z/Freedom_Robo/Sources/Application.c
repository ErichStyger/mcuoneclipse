
#include "Ultrasonic.h"
#include "LEDR.h"
#include "LEDG.h"
#include "WAIT1.h"
#include "Shell.h"
#include "Motor.h"
#include "Reflectance.h"
#include "LineFollow.h"
#if PL_USE_TSS
  #include "TSS1.h"
#endif

#if 0
static uint8_t MeasureCm(void) {
  uint16_t us, cm;
  uint8_t buf[8];

  us = US_Measure_us();
  UTIL1_Num16uToStrFormatted(buf, sizeof(buf), us, ' ', 5);
  //LCD1_GotoXY(1,5);
  //LCD1_WriteString((char*)buf);

  cm = US_usToCentimeters(us, 22);
  UTIL1_Num16uToStrFormatted(buf, sizeof(buf), cm, ' ', 5);
  //LCD1_GotoXY(2,5);
  //LCD1_WriteString((char*)buf);
  
  LEDR_Put(cm>0 && cm<10); /* red LED if object closer than 10 cm */
//  LEDB_Put(cm>=10&&cm<=100); /* blue LED if object is in 10..100 cm range */
  LEDG_Put(cm>=10); /* blue LED if object is in 10..100 cm range */
  return cm;
}

static bool runIt = TRUE;

static portTASK_FUNCTION(RoboTask, pvParameters) {
  uint16_t cm;
  
  (void)pvParameters; /* not used */
  for(;;) {
    cm = MeasureCm();
    LEDR_Neg();
    if (runIt && cm != 0) {
      if (cm<10) { /* back up! */
        MOT_SetSpeedPercent(MOT_GetMotorA(), -40);
        MOT_SetSpeedPercent(MOT_GetMotorB(), -40);
      } else if (cm>=10 && cm<=15) {
        /* stand still */
        MOT_SetSpeedPercent(MOT_GetMotorA(), 0);
        MOT_SetSpeedPercent(MOT_GetMotorB(), 0);
      } else if (cm>15 && cm<=40) {
        MOT_SetSpeedPercent(MOT_GetMotorA(), 50);
        MOT_SetSpeedPercent(MOT_GetMotorB(), 50);
      } else if (cm>40 && cm<80) {
        MOT_SetSpeedPercent(MOT_GetMotorA(), 80);
        MOT_SetSpeedPercent(MOT_GetMotorB(), 80);
      } else { /* nothing in range */
        MOT_SetSpeedPercent(MOT_GetMotorA(), 0);
        MOT_SetSpeedPercent(MOT_GetMotorB(), 0);
      }
    }
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  }
}
#endif

#if PL_USE_TSS
static portTASK_FUNCTION(TssTask, pvParameters) {
  (void)pvParameters; /* not used */
  Configure(); /* initialize TSS library */
  for(;;) {
    TSS_Task(); /* call TSS library to process touches */
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}
#endif

void APP_Run(void) {
  REF_Init();
  MOT_Init();
  SHELL_Init();
  LF_Init();
#if 0
  US_Init();
#endif
#if PL_USE_TSS
  if (FRTOS1_xTaskCreate(TssTask, (signed portCHAR *)"Tss", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
  FRTOS1_vTaskStartScheduler();
}

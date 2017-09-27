/*
 * RoboShield.c
 *
 *  Created on: 30.09.2014
 *      Author: tastyger
 */

#include "Platform.h"
#if PL_HAS_ROBO_SHIELD
#include "FRTOS1.h"
#include "PCA1.h"
#include "Shell.h"
#include "UTIL1.h"

#include "Bit_D12.h" /* X5 front right */
#include "Bit_D11.h" /* X6 right */
#include "Bit_D6.h"  /* X8 back left*/
#include "Bit_D5.h"  /* X9 left */
#if 0 && !PL_HAS_MUSIC_SHIELD /* pins used by shield */
  #include "Bit_D13.h" /* X4 front left */
  //#include "Bit_A0.h" /* X13, multi-I/O back */
  #include "Bit_A1.h"  /* X13, multi-I/O middle */
  #include "Bit_A2.h"  /* X13, multi-I/O front */
#endif

/* pins */
/* PCA8554 */
#define ENABLE_FRONT_LEFT  (1<<0) /* X4 */
#define ENABLE_FRONT_RIGHT (1<<1) /* X5 */
#define ENABLE_RIGHT       (1<<2) /* X6 */
#define ENABLE_BACK_RIGHT  (1<<3) /* X7 */
#define ENABLE_BACK_LEFT   (1<<4) /* X8 */
#define ENABLE_LEFT        (1<<5) /* X9 */
#define ENABLE_IO1         (1<<6) /* X12 left pin */
#define ENABLE_IO2         (1<<7) /* X12 right pin */

static portTASK_FUNCTION(ShieldTask, pvParameters) {
  uint8_t val;
  uint8_t buf[32];

  (void)pvParameters; /* not used */
  PCA1_WriteConfig(0xff); /* all as input */
  for(;;) {
    val = PCA1_ReadInput(); /* read input byte */
    UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"shield val: 0x");
    UTIL1_strcatNum8Hex(buf, sizeof(buf), val);
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
    SHELL_SendString(buf);

#if 0 && !PL_HAS_MUSIC_SHIELD
    if (Bit_D13_GetVal()!=0) {
      SHELL_SendString((unsigned char*)" D13");
    } else {
      SHELL_SendString((unsigned char*)"    ");
    }
#endif
    if (Bit_D12_GetVal()!=0) {
      SHELL_SendString((unsigned char*)" D12");
    } else {
      SHELL_SendString((unsigned char*)"    ");
    }
    if (Bit_D11_GetVal()!=0) {
      SHELL_SendString((unsigned char*)" D11");
    } else {
      SHELL_SendString((unsigned char*)"    ");
    }
    if (Bit_D6_GetVal()!=0) {
      SHELL_SendString((unsigned char*)" D6");
    } else {
      SHELL_SendString((unsigned char*)"   ");
    }
    if (Bit_D5_GetVal()!=0) {
      SHELL_SendString((unsigned char*)" D5");
    } else {
      SHELL_SendString((unsigned char*)"   ");
    }
#if 0
    if (Bit_A0_GetVal()!=0) {
      SHELL_SendString((unsigned char*)" A0");
    } else {
      SHELL_SendString((unsigned char*)"   ");
    }
#endif
#if 0 && !PL_HAS_MUSIC_SHIELD
    if (Bit_A1_GetVal()!=0) {
      SHELL_SendString((unsigned char*)" A1");
    } else {
      SHELL_SendString((unsigned char*)"   ");
    }
    if (Bit_A2_GetVal()!=0) {
      SHELL_SendString((unsigned char*)" A2");
    } else {
      SHELL_SendString((unsigned char*)"   ");
    }
#endif
    SHELL_SendString((unsigned char*)"\r\n");
    FRTOS1_vTaskDelay(1000/portTICK_PERIOD_MS);
  } /* for */
}

void RS_Deinit(void) {
}

/*! \brief Initialization of the module */
void RS_Init(void) {
  if (FRTOS1_xTaskCreate(ShieldTask, (signed portCHAR *)"Shield", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
#endif /* PL_HAS_ROBO_SHIELD */

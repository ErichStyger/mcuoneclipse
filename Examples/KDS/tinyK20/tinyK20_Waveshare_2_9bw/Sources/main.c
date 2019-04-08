/* ###################################################################
**     Filename    : main.c
**     Project     : tinyK20_Waveshare_2_9bw
**     Processor   : MK20DX128VFT5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-11-02, 17:22, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "SM1.h"
#include "SMasterLdd1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd6.h"
#include "ResetPin.h"
#include "BitIoLdd1.h"
#include "BusyPin.h"
#include "BitIoLdd2.h"
#include "DcPin.h"
#include "BitIoLdd3.h"
#include "WAIT1.h"
#include "CsPin.h"
#include "BitIoLdd5.h"
#include "MCUC1.h"
#include "TGT_SWD_OE.h"
#include "BitIoLdd4.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

#include "Display_Config.h"
#if DISPLAY_IS_2_COLOR
  #include "epd2in9.h"
  #include "epd2in9.h"
#else
  #include "epd2in9b.h"
  #include "epd2in9b.h"
#endif
#include "epdif.h"
#include "epdpaint.h"
#include "imagedata.h"
#include "testimage.h"
#include <stdlib.h>

#if DISPLAY_IS_2_COLOR
  #define COLORED      0
  #define UNCOLORED    1
#elif DISPLAY_IS_3_COLOR
  #define COLORED      1
  #define UNCOLORED    0
#endif


#if DISPLAY_IS_2_COLOR

unsigned char frame_buffer[EPD_WIDTH * EPD_HEIGHT / 8];
static int Test(void) {
  char time_string[] = {'0', '0', ':', '0', '0', '\0'};
  unsigned long time_start_ms;
  unsigned long time_now_s;
  EPD epd;


  if (EPD_Init(&epd, lut_full_update) != 0) {
    //printf("e-Paper init failed\n");
    return -1;
  }

  Paint paint;
  Paint_Init(&paint, frame_buffer, epd.width, epd.height);
  Paint_Clear(&paint, UNCOLORED);

#if 0
  /* For simplicity, the arguments are explicit numerical coordinates */
  /* Write strings to the buffer */
  Paint_DrawFilledRectangle(&paint, 0, 10, 128, 34, COLORED);
  Paint_DrawStringAt(&paint, 0, 14, "Hello world!", &Font16, UNCOLORED);
  Paint_DrawStringAt(&paint, 0, 34, "e-Paper Demo", &Font16, COLORED);

  /* Draw something to the frame buffer */
  Paint_DrawRectangle(&paint, 16, 60, 56, 110, COLORED);
  Paint_DrawLine(&paint, 16, 60, 56, 110, COLORED);
  Paint_DrawLine(&paint, 56, 60, 16, 110, COLORED);
  Paint_DrawCircle(&paint, 120, 90, 30, COLORED);
  Paint_DrawFilledRectangle(&paint, 16, 130, 56, 180, COLORED);
  Paint_DrawFilledCircle(&paint, 120, 160, 30, COLORED);

  /* Display the frame_buffer */
  EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
  EPD_DisplayFrame(&epd);
  EPD_DelayMs(&epd, 2000);
#endif
  /**
   *  there are 2 memory areas embedded in the e-paper display
   *  and once the display is refreshed, the memory area will be auto-toggled,
   *  i.e. the next action of SetFrameMemory will set the other memory area
   *  therefore you have to set the frame memory and refresh the display twice.
   */
  EPD_ClearFrameMemory(&epd, 0xFF);
  EPD_DisplayFrame(&epd);
  EPD_ClearFrameMemory(&epd, 0xFF);
  EPD_DisplayFrame(&epd);

  int i;
#if 0
  Paint_Clear(&paint, UNCOLORED);
  for(i=0;i<40;i+=2) {
    Paint_DrawRectangle(&paint, i, i, EPD_WIDTH-i-1, EPD_HEIGHT-i-1, COLORED);
  }
  /* Display the frame_buffer */
  EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
  EPD_DisplayFrame(&epd);

//  for(;;) {
//    EPD_DelayMs(&epd, 500);
//  }
#endif
  EPD_ClearFrameMemory(&epd, 0xFF);
  EPD_SetFrameMemory(&epd, image_data_test, 0, 0, epd.width, epd.height);
  EPD_DisplayFrame(&epd);


#if 0
  /* EPD_or partial update */
  if (EPD_Init(&epd, lut_partial_update) != 0) {
    //printf("e-Paper init failed\n");
    return -1;
  }

  /**
   *  there are 2 memory areas embedded in the e-paper display
   *  and once the display is refreshed, the memory area will be auto-toggled,
   *  i.e. the next action of SetFrameMemory will set the other memory area
   *  therefore you have to set the frame memory and refresh the display twice.
   */
  EPD_SetFrameMemory(&epd, IMAGE_BLACK, 0, 0, epd.width, epd.height);
  EPD_DisplayFrame(&epd);
  EPD_SetFrameMemory(&epd, IMAGE_BLACK, 0, 0, epd.width, epd.height);
  EPD_DisplayFrame(&epd);

  time_start_ms = 1000; //HAL_GetTick();
  while (1)
  {
     //time_now_s = (HAL_GetTick() - time_start_ms) / 1000;
    time_now_s++;
    time_string[0] = time_now_s / 60 / 10 + '0';
    time_string[1] = time_now_s / 60 % 10 + '0';
    time_string[3] = time_now_s % 60 / 10 + '0';
    time_string[4] = time_now_s % 60 % 10 + '0';

    Paint_SetWidth(&paint, 32);
    Paint_SetHeight(&paint, 96);
    Paint_SetRotate(&paint, ROTATE_90);

    Paint_Clear(&paint, UNCOLORED);
    Paint_DrawStringAt(&paint, 0, 4, time_string, &Font24, COLORED);
    EPD_SetFrameMemory(&epd, frame_buffer, 80, 72, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
    EPD_DisplayFrame(&epd);

    EPD_DelayMs(&epd, 500);
  }
#endif
  for(;;) {}
}
#elif DISPLAY_IS_3_COLOR
unsigned char /*__attribute__((section (".m_data_20000000")))*/ frame_buffer_black[EPD_WIDTH * EPD_HEIGHT / 8];
unsigned char __attribute__((section (".m_data_20000000"))) frame_buffer_red[EPD_WIDTH * EPD_HEIGHT / 8];
int Test(void) {
  EPD epd;

  if (EPD_Init(&epd, NULL) != 0) {
    //printf("e-Paper init failed\n");
    return -1;
  }

  Paint paint_black;
  Paint paint_red;
  Paint_Init(&paint_black, frame_buffer_black, epd.width, epd.height);
  Paint_Init(&paint_red, frame_buffer_red, epd.width, epd.height);
  Paint_Clear(&paint_black, UNCOLORED);
  Paint_Clear(&paint_red, UNCOLORED);

  /* Display the frame_buffer (all white) */
   EPD_DisplayFrame(&epd, frame_buffer_black, frame_buffer_red);

#if 0
   /* Display the image buffer */
   EPD_DisplayFrame(&epd, G_Ultrachip, G_Ultrachip_red);

   /* Display the image buffer */
   EPD_DisplayFrame(&epd, G_Ultrachip1, G_Ultrachip_red1);
#endif

  /* Draw something to the frame buffer */
  /* For simplicity, the arguments are explicit numerical coordinates */
  Paint_SetRotate(&paint_black, ROTATE_0);
  Paint_SetRotate(&paint_red, ROTATE_0);
  Paint_DrawRectangle(&paint_black, 10, 80, 50, 140, COLORED);
  Paint_DrawLine(&paint_black, 10, 80, 50, 140, COLORED);
  Paint_DrawLine(&paint_black, 50, 80, 10, 140, COLORED);
  Paint_DrawCircle(&paint_black, 90, 110, 30, COLORED);
  Paint_DrawFilledRectangle(&paint_red, 10, 180, 50, 240, COLORED);
  Paint_DrawFilledRectangle(&paint_red, 0, 6, 128, 26, COLORED);
  Paint_DrawFilledCircle(&paint_red, 90, 210, 30, COLORED);

  /*Write strings to the buffer */
  Paint_DrawStringAt(&paint_red, 6, 10, "Hello", &Font12, UNCOLORED);
  Paint_DrawStringAt(&paint_black, 4, 30, "World", &Font12, COLORED);

  /* Display the frame_buffer */
  EPD_DisplayFrame(&epd, frame_buffer_black, frame_buffer_red);

  /* Display the image buffer with waveshare image */
  EPD_DisplayFrame(&epd, IMAGE_BLACK, IMAGE_RED);
  while (1)
  {
  }
}

#endif


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  LED1_On();
  Test();
  LED1_Off();
  /* For example: for(;;) { } */

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

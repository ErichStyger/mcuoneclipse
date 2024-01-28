/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM-K64F_SSD1306
**     Processor   : MK64FN1M0VLQ12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-11-24, 17:35, # CodeGen: 0
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
#include "Pins1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "MCUC1.h"
#include "GI2C1.h"
#include "I2C1.h"
#include "SDA1.h"
#include "BitIoLdd4.h"
#include "SCL1.h"
#include "BitIoLdd5.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "LCD1_China.h"
#include "RESpin1.h"
#include "BitIoLdd6.h"
#include "LCD1_Adafruit.h"
#include "RESpin2.h"
#include "BitIoLdd7.h"
#include "KIN1.h"
#include "FDisp1.h"
#include "Helv8.h"
#include "Helv10.h"
#include "Helv12.h"
#include "GDisp1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

#if 0
static void Matrix(void) {
  int x,y;
  int r;

  UTIL1_randomSetSeed(0x1234);
  r = UTIL1_random(0, 100);

  GDisp1_DrawFilledBox(0,0,GDisp1_GetWidth(), GDisp1_GetHeight(), GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();

  GDisp1_SetPixel(0,0);
  GDisp1_UpdateFull();
  GDisp1_SetPixel(GDisp1_GetWidth()-1,0);
  GDisp1_UpdateFull();
  GDisp1_SetPixel(0,GDisp1_GetHeight()-1);
  GDisp1_UpdateFull();
  GDisp1_SetPixel(GDisp1_GetWidth()-1,GDisp1_GetHeight()-1);
  GDisp1_UpdateFull();


  //GDisp1_DrawLine(0,0,GDisp1_GetWidth()-1, GDisp1_GetHeight()-1, GDisp1_COLOR_BLUE);
  //GDisp1_UpdateFull();
  for(;;) {
    for(y=GDisp1_GetHeight()-1; y>0;y--) {
      for(x=0;x<GDisp1_GetWidth();x++) {
        GDisp1_PutPixel(x, y, GDisp1_GetPixel(x, y-1));
      }
      //GDisp1_UpdateFull();
    }
    /* random first line */
    for(x=0;x<GDisp1_GetWidth();x++) {
      if (GDisp1_GetPixel(x,1)==GDisp1_COLOR_PIXEL_SET) {
        if (   GDisp1_GetPixel(x,2)==GDisp1_COLOR_PIXEL_SET
            || GDisp1_GetPixel(x,3)==GDisp1_COLOR_PIXEL_SET
            || GDisp1_GetPixel(x,4)==GDisp1_COLOR_PIXEL_SET
            || GDisp1_GetPixel(x,5)==GDisp1_COLOR_PIXEL_SET
          )
        {
          GDisp1_SetPixel(x,0); /* extend line */
        } else {
          GDisp1_PutPixel(x, 0, UTIL1_random(0, 1)); /* new random pixel */
        }
      } else { /* pixel cleared */
        if (   GDisp1_GetPixel(x,2)==GDisp1_COLOR_PIXEL_CLR
            || GDisp1_GetPixel(x,3)==GDisp1_COLOR_PIXEL_CLR
            || GDisp1_GetPixel(x,4)==GDisp1_COLOR_PIXEL_CLR
            || GDisp1_GetPixel(x,5)==GDisp1_COLOR_PIXEL_CLR
          )
        {
          GDisp1_ClrPixel(x,0); /* extend emtpy line */
        } else {
          GDisp1_PutPixel(x, 0, UTIL1_random(0, 1)); /* new random pixel */
        }
      }
#if 0
      if (   x>=3
          && GDisp1_GetPixel(x-1,0)==GDisp1_COLOR_BLACK
          && GDisp1_GetPixel(x-2,0)==GDisp1_COLOR_BLACK
          && GDisp1_GetPixel(x-3,0)==GDisp1_COLOR_BLACK
         )
      {
        /* gap of two pixels */
        GDisp1_PutPixel(x, 0, UTIL1_random(0, 1));
      } else {
        GDisp1_ClrPixel(x,0);
      }
#endif
    }
    GDisp1_UpdateFull();
  }
}
#endif

/* monochrome image (24x16 pixels)
 * 0: pixel set
 * 1: pixel clear
 * Bytes are from left-to-right and top-to-bottom, Bits in Big-Endian order
 *  */
typedef struct {
    const uint8_t *data;
    uint16_t width;
    uint16_t height;
    uint8_t dataSize;
    } tImage;
#include "square.inc"
#include "Circle.inc"

static void ShowMonoImage(void) {
    TIMAGE image;

    image.width = square.width;
    image.height = square.height;
    image.name = "";
    image.size = image.width*image.height;
    image.pixmap = square.data;

    GDisp1_Clear();
    GDisp1_DrawMonoBitmap(0, 0, &image, GDisp1_COLOR_BLACK, GDisp1_COLOR_WHITE);
    GDisp1_UpdateFull();

    image.width = Circle.width;
    image.height = Circle.height;
    image.name = "";
    image.size = image.width*image.height;
    image.pixmap = Circle.data;

    GDisp1_Clear();
    GDisp1_DrawMonoBitmap(0, 0, &image, GDisp1_COLOR_BLACK, GDisp1_COLOR_WHITE);
    GDisp1_UpdateFull();
}

static void RunLCD(void) {
  ShowMonoImage();
  //Matrix();
  //LCD1_China_Clear();
  //LCD1_China_PrintString("hello World!\n");
  //LCD1_China_PrintString("this is on a 2nd line\n");
  //LCD1_China_PrintString("this is on a 3rd line\n");
  GDisp1_DrawFilledBox(0,0,GDisp1_GetWidth(), GDisp1_GetHeight(), GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  GDisp1_DrawFilledBox(0,0,GDisp1_GetWidth(), GDisp1_GetHeight(), GDisp1_COLOR_BLUE);
  GDisp1_UpdateFull();

  GDisp1_Clear();
  GDisp1_DrawFilledBox(0,0,GDisp1_GetWidth(), GDisp1_GetHeight(), GDisp1_COLOR_BLACK);
  GDisp1_DrawBox(0, 0, 64, 8, 1, GDisp1_COLOR_BLUE);
  GDisp1_UpdateFull();
  GDisp1_DrawBox(0, 8, 64, 8, 1, GDisp1_COLOR_BLUE);
  GDisp1_UpdateFull();
  GDisp1_DrawBox(0, 16, 64, 8, 1, GDisp1_COLOR_BLUE);
  GDisp1_UpdateFull();
  GDisp1_DrawBox(0, 24, 64, 8, 1, GDisp1_COLOR_BLUE);
  GDisp1_UpdateFull();

  GDisp1_DrawFilledBox(0,0,GDisp1_GetWidth(), GDisp1_GetHeight(), GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  GDisp1_DrawFilledBox(0,0,GDisp1_GetWidth(), GDisp1_GetHeight(), GDisp1_COLOR_BLUE);
  GDisp1_UpdateFull();

  GDisp1_DrawBox(0, 0, GDisp1_GetWidth(), GDisp1_GetHeight(), 1, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  GDisp1_DrawBox(0, 0, GDisp1_GetWidth(), GDisp1_GetHeight(), 1, GDisp1_COLOR_BLUE);
  GDisp1_UpdateFull();

  GDisp1_Clear();
#if 0
  for(int x=0; x<10;x++) {
    GDisp1_SetPixel(x, 0);
  }
  GDisp1_DrawHLine(0,0,15,GDisp1_COLOR_WHITE);
#endif

  GDisp1_ClrPixel(0, 0);
  GDisp1_ClrPixel(1, 1);
  GDisp1_ClrPixel(2, 2);
  GDisp1_UpdateFull();

  GDisp1_DrawHLine(0,0,15,GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();

  for(;;){
    int i;
    FDisp1_PixelDim x, y;

    LED2_Neg();
    GDisp1_Clear();
    /* clear display */
    GDisp1_DrawFilledBox(0,0,GDisp1_GetWidth(), GDisp1_GetHeight(), GDisp1_COLOR_BLACK);
    GDisp1_UpdateFull();


    GDisp1_DrawBox(0, 0, GDisp1_GetWidth(), GDisp1_GetHeight(), 1, GDisp1_COLOR_BLUE);
    x = 2; y = 2;

    FDisp1_WriteString((uint8_t*)"Hello Helv8", GDisp1_COLOR_BLUE, &x, &y, Helv8_GetFont());
    x = 2; y+= Helv8_GetBoxHeight();
    FDisp1_WriteString((uint8_t*)"Hello Helv10", GDisp1_COLOR_BLUE, &x, &y, Helv10_GetFont());
    x = 2; y+= Helv10_GetBoxHeight();
    FDisp1_WriteString((uint8_t*)"Hello Helv12", GDisp1_COLOR_BLUE, &x, &y, Helv12_GetFont());
    GDisp1_UpdateFull();
  }

  GDisp1_DrawBox(2, 2, 20, 8, 1, GDisp1_COLOR_WHITE);
  for(;;) {
    GDisp1_Clear();
    for(int x=0;x<100;x+=10) {
      for(int y=0;y<50;y+=15) {
        GDisp1_DrawBox(x, y, 30, 10, 1, GDisp1_COLOR_BLACK);
      }
    }
    GDisp1_UpdateFull();
  }
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  LED1_On();
  WAIT1_Waitms(10);
  LED1_Off();
  RunLCD();
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

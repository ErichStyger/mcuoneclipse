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
#elif DISPLAY_IS_3_COLOR
  #include "epd2in9b.h"
  #include "epd2in9b.h"
#elif 0 && DISPLAY_IS_1_54_BW
  #include "EPD_1in54b.h"
#endif
#if 0
#include "epdif.h"
#include "epdpaint.h"
#include "imagedata.h"
#include "testimage.h"
#endif

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
#elif 0 && DISPLAY_IS_1_54_BW

#include "EPD_1in54b.h"
#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "imagedata.h"
#include <stdio.h>

#define IMAGE_SIZE (((EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1)) * EPD_HEIGHT)
static uint8_t BlackImage[IMAGE_SIZE];
//static uint8_t RedImage[IMAGE_SIZE];

static int Run(void) {
    //printf("epd init and clear------------------------\r\n");
    if(EPD_Init()) {
      //  printf("e-Paper init failed\r\n");
    }
    EPD_Clear();
    DEV_Delay_ms(200);

#if 0
    //Create a new image cache named IMAGE_BW and fill it with white
    UBYTE *BlackImage, *RedImage;
    UWORD Imagesize = IMAGE_SIZE;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }
    if((RedImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for red memory...\r\n");
        return -1;
    }
#endif
#if 0
    //printf("NewImage:BlackImage and RedImage\r\n");
    Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 270, WHITE);
    Paint_NewImage(RedImage, EPD_WIDTH, EPD_HEIGHT, 270, WHITE);

    //Select Image
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_SelectImage(RedImage);
    Paint_Clear(WHITE);
#endif

#if 1   //show image for array
    //printf("show image for array------------------------\r\n");
    Paint_SelectImage(BlackImage);
    Paint_DrawBitMap(IMAGE_BLACK);
#if 0
    Paint_SelectImage(RedImage);
    Paint_DrawBitMap(IMAGE_RED);

    EPD_Display(BlackImage, RedImage);
#else
    EPD_Display(BlackImage, BlackImage);
#endif
    DEV_Delay_ms(2000);
#endif

#if 0   //Drawing
    //printf("Drawing------------------------\r\n");
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawLine(20, 10, 70, 60, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(70, 10, 20, 60, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawRectangle(20, 10, 70, 60, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(170, 85, 20, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawString_EN(5, 70, "hello world", &Font16, WHITE, BLACK);
    Paint_DrawString_CN(5, 160, "Î¢Ñ©µç×Ó", &Font24CN, WHITE, BLACK);

    Paint_SelectImage(RedImage);
    Paint_Clear(WHITE);
    Paint_DrawPoint(5, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 55, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawLine(170, 15, 170, 55, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawLine(150, 35, 190, 35, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawRectangle(85, 10, 130, 60, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawCircle(170, 35, 20, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawString_EN(5, 90, "waveshare", &Font20, BLACK, WHITE);
    Paint_DrawNum(5, 120, 123456789, &Font20, BLACK, WHITE);
    Paint_DrawString_CN(5, 135,"ÄãºÃabc", &Font12CN, BLACK, WHITE);

    EPD_Display(BlackImage, RedImage);
    DEV_Delay_ms(2000);
#endif

    //printf("Goto Sleep mode...\r\n");
    EPD_Sleep();
#if 0
    free(BlackImage);
    free(RedImage);
    BlackImage = NULL;
    RedImage = NULL;
#endif
  while (1)
  {
  }
}
#endif

#if 1
#include "ep154.h"
#include "GUI_Paint.h"

#define IMAGE_SIZE  (((EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1)) * EPD_HEIGHT)
static uint8_t data[IMAGE_SIZE];

static int Run(void) {
  EPD_Init(lut_full_update);
  EPD_Clear();
  //Create a new image cache
  uint8_t *BlackImage;
  unsigned int Imagesize = ((EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1)) * EPD_HEIGHT;
#if 0
  if((BlackImage = (unsigned int *)malloc(Imagesize)) == NULL) {
      return 0;
  }
#else
  BlackImage = &data[0];
#endif
  Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 270, WHITE);
  Paint_SelectImage(BlackImage);

  Paint_Clear(WHITE);
  EPD_Display(BlackImage);

  Paint_DrawString_EN(10, 15,"Atomizer", &Font24, WHITE, BLACK);
  EPD_Display(BlackImage);

//  Paint_Clear(BLACK);
//  EPD_Display(BlackImage);

  //Paint_DrawBitMap(logo);
  //SetFrameMemory(logo,0,0,185,185);
   /* Paint_DrawLine(0, 48, 200, 48, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
  Paint_DrawString_EN(40,50 ,"31.03.2018", &Font16, WHITE, BLACK);
  if(EPD_Init(lut_partial_update) != 0) {
      printf("e-Paper init failed\r\n");
  }
  Paint_SelectImage(BlackImage);
  PAINT_TIME sPaint_time;
  sPaint_time.Hour = 17;
  sPaint_time.Min = 49;
  sPaint_time.Sec = 00;
  for (;;) {
      sPaint_time.Sec = sPaint_time.Sec + 1;
      if (sPaint_time.Sec == 60) {
          sPaint_time.Min = sPaint_time.Min + 1;
          sPaint_time.Sec = 0;
          if (sPaint_time.Min == 60) {
              sPaint_time.Hour =  sPaint_time.Hour + 1;
              sPaint_time.Min = 0;
              if (sPaint_time.Hour == 24) {
                  sPaint_time.Hour = 0;
                  sPaint_time.Min = 0;
                  sPaint_time.Sec = 0;
              }
          }
      }
      Paint_ClearWindows(35, 90, 35 + Font24.Width * 7, 90 + Font24.Height, WHITE);
      Paint_DrawTime(35, 90, &sPaint_time, &Font24, WHITE, BLACK);
  EPD_Display(BlackImage);
      WAIT1_Waitms(500);//Analog clock 1s
  }*/
  /* Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 270, WHITE);
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);
  Paint_DrawString_EN(5, 5,"Atomizer", &Font24, WHITE, BLACK);
  Paint_DrawLine(0, 28, 200, 28, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
  Paint_DrawString_EN(5,30 ,"25.03.2018", &Font12, WHITE, BLACK);*/

  //Paint_DrawCircle(170, 85, 20, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);
  //Paint_DrawNum(180, 180, 666, &Font20, WHITE, BLACK);
  /*Paint_DrawRectangle(5, 42, 110, 64, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
  Paint_DrawString_EN(7,45 ,"Parameter", &Font16, WHITE, BLACK);
  Paint_DrawString_EN(7,70 ,"Einstellungen", &Font16, WHITE, BLACK);
  Paint_DrawString_EN(10,90 ,"Volume:", &Font16, WHITE, BLACK);
  Paint_DrawString_EN(130, 90, "13", &Font16, WHITE, BLACK);
  Paint_DrawString_EN(10,110 ,"Frequenz:", &Font16, WHITE, BLACK);
  Paint_DrawString_EN(130, 110, "100Hz", &Font16, WHITE, BLACK);
  Paint_DrawString_EN(10,130 ,"Luefter 1:", &Font16, WHITE, BLACK);
  Paint_DrawString_EN(130, 130, "10", &Font16, WHITE, BLACK);
  Paint_DrawString_EN(10,150 ,"Luefter 2:", &Font16, WHITE, BLACK);
  Paint_DrawString_EN(130, 150, "10", &Font16, WHITE, BLACK);
  EPD_Display(BlackImage);
  Paint_DrawString_EN(10,130 ,"Luefter 1:", &Font16, WHITE, BLACK);
  Paint_DrawString_EN(130, 130, "15", &Font16, WHITE, BLACK);
  Paint_DrawString_EN(10,150 ,"Luefter 2:", &Font16, WHITE, BLACK);
  Paint_DrawString_EN(130, 150, "15", &Font16, WHITE, BLACK);
  Paint_Clear(WHITE);
  EPD_Display(BlackImage);*/
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
  Run();
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

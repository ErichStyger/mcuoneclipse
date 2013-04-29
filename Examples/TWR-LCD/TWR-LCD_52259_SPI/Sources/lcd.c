/*
 * lcd.c
 *
 *  Created on: Nov 2, 2012
 *      Author: Erich Styger
 */
#include "lcd.h"
#include "GDisp1.h"
#include "FDisp1.h"
#include "Helv08n.h"
//#include "LED1.h" /* LED1 is connected to the LCD Buzzer */
#include "LED2.h"
#include "LED3.h"
#include "LED4.h"
#include "TCHS1.h"
#include "UTIL1.h"

static TCHS1_TouchScreenEvent evnt=(TCHS1_TouchScreenEvent)0xff; /* just some value other than existing events */
static TCHS1_PixelDim xPos, yPos;

void OnTouch(TCHS1_TouchScreenEvent event, TCHS1_PixelDim x, TCHS1_PixelDim y) {
  if (event==TCHS1_TOUCHSCREEN_EVENT_TOUCH) {
    xPos = x;
    yPos = y;
    evnt = event;
  } else if (event==TCHS1_TOUCHSCREEN_EVENT_MOVE) {
    xPos = x;
    yPos = y;
    evnt = event;
  } else if (event==TCHS1_TOUCHSCREEN_EVENT_RELEASE) {
    xPos = x;
    yPos = y;
    evnt = event;
  }
}

static void PrintLCDText(unsigned char line, const unsigned char *txt) {
  GDisp1_PixelDim x, y;
  FDisp1_Font *font;
  #define TEXT_LEFT_BORDER 10
  #define TEXT_TOP_BORDER 5
  
  font = Helv08n_GetFont();
  x = TEXT_LEFT_BORDER;
  y = (FDisp1_PixelDim)(line*Helv08n_GetBoxHeight()+TEXT_TOP_BORDER);
  FDisp1_WriteString((unsigned char*)txt, GDisp1_COLOR_WHITE, &x, &y, font);
}

static void PrintTouchText(unsigned char line) {
  unsigned char buf[32];

  if (evnt==TCHS1_TOUCHSCREEN_EVENT_TOUCH) {
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"Touch: x:");
    UTIL1_strcatNum16uFormatted(buf, sizeof(buf), xPos, '0', 3);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" y:");
    UTIL1_strcatNum16uFormatted(buf, sizeof(buf), yPos, '0', 3);
  } else if (evnt==TCHS1_TOUCHSCREEN_EVENT_MOVE) {
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"Move: x:");
    UTIL1_strcatNum16uFormatted(buf, sizeof(buf), xPos, '0', 3);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" y:");
    UTIL1_strcatNum16uFormatted(buf, sizeof(buf), yPos, '0', 3);
  } else if (evnt==TCHS1_TOUCHSCREEN_EVENT_RELEASE) {
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"Release: x:");
    UTIL1_strcatNum16uFormatted(buf, sizeof(buf), xPos, '0', 3);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" y:");
    UTIL1_strcatNum16uFormatted(buf, sizeof(buf), yPos, '0', 3);
  } else {
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"Touch me!");
  }
  PrintLCDText(line, buf);
}

#define BOX_WIDTH  20
#define BOX_HEIGHT 30
#define OFFSET     5


#if 1 /* ************************* */
typedef volatile unsigned long vuint32;
typedef volatile unsigned char vuint8;

#define MCF_GPIO_PORTTE                      (*(vuint8 *)(0x40100000))
#define MCF_GPIO_DDRTE                       (*(vuint8 *)(0x40100018))
#define MCF_GPIO_SETTE                       (*(vuint8 *)(0x40100030))
#define MCF_GPIO_CLRTE                       (*(vuint8 *)(0x40100048))
#define MCF_GPIO_PTEPAR                      (*(vuint8 *)(0x40100060))

#define MCF_GPIO_PORTTF                      (*(vuint8 *)(0x40100001))
#define MCF_GPIO_DDRTF                       (*(vuint8 *)(0x40100019))
#define MCF_GPIO_SETTF                       (*(vuint8 *)(0x40100031))
#define MCF_GPIO_CLRTF                       (*(vuint8 *)(0x40100049))
#define MCF_GPIO_PTFPAR                      (*(vuint8 *)(0x40100061))

#define MCF_GPIO_PORTTG                      (*(vuint8 *)(0x40100002))
#define MCF_GPIO_DDRTG                       (*(vuint8 *)(0x4010001A))
#define MCF_GPIO_SETTG                       (*(vuint8 *)(0x40100032))
#define MCF_GPIO_CLRTG                       (*(vuint8 *)(0x4010004A))
#define MCF_GPIO_PTGPAR                      (*(vuint8 *)(0x40100062))


/* Register read/write macros */
#define MCF_FBCS0_CSAR                       (*(vuint32*)(0x40000080))
#define MCF_FBCS0_CSMR                       (*(vuint32*)(0x40000084))
#define MCF_FBCS0_CSCR                       (*(vuint32*)(0x40000088))

#define MCF_FBCS1_CSAR                       (*(vuint32*)(0x4000008C))
#define MCF_FBCS1_CSMR                       (*(vuint32*)(0x40000090))
#define MCF_FBCS1_CSCR                       (*(vuint32*)(0x40000094))

#define MCF_FBCS_CSAR(x)                     (*(vuint32*)(0x40000080 + ((x)*0xC)))
#define MCF_FBCS_CSMR(x)                     (*(vuint32*)(0x40000084 + ((x)*0xC)))
#define MCF_FBCS_CSCR(x)                     (*(vuint32*)(0x40000088 + ((x)*0xC)))


/* Bit definitions and macros for MCF_FBCS_CSAR */
#define MCF_FBCS_CSAR_BA(x)                  ((x)&0xFFFF0000)

/* Bit definitions and macros for MCF_FBCS_CSMR */
#define MCF_FBCS_CSMR_V                      (0x1)
#define MCF_FBCS_CSMR_WP                     (0x100)
#define MCF_FBCS_CSMR_BAM(x)                 (((x)&0xFFFF)<<0x10)
#define MCF_FBCS_CSMR_BAM_4G                 (0xFFFF0000)
#define MCF_FBCS_CSMR_BAM_2G                 (0x7FFF0000)
#define MCF_FBCS_CSMR_BAM_1G                 (0x3FFF0000)
#define MCF_FBCS_CSMR_BAM_1024M              (0x3FFF0000)
#define MCF_FBCS_CSMR_BAM_512M               (0x1FFF0000)
#define MCF_FBCS_CSMR_BAM_256M               (0xFFF0000)
#define MCF_FBCS_CSMR_BAM_128M               (0x7FF0000)
#define MCF_FBCS_CSMR_BAM_64M                (0x3FF0000)
#define MCF_FBCS_CSMR_BAM_32M                (0x1FF0000)
#define MCF_FBCS_CSMR_BAM_16M                (0xFF0000)
#define MCF_FBCS_CSMR_BAM_8M                 (0x7F0000)
#define MCF_FBCS_CSMR_BAM_4M                 (0x3F0000)
#define MCF_FBCS_CSMR_BAM_2M                 (0x1F0000)
#define MCF_FBCS_CSMR_BAM_1M                 (0xF0000)
#define MCF_FBCS_CSMR_BAM_1024K              (0xF0000)
#define MCF_FBCS_CSMR_BAM_512K               (0x70000)
#define MCF_FBCS_CSMR_BAM_256K               (0x30000)
#define MCF_FBCS_CSMR_BAM_128K               (0x10000)
#define MCF_FBCS_CSMR_BAM_64K                (0)

/* Bit definitions and macros for MCF_FBCS_CSCR */
#define MCF_FBCS_CSCR_BSTW                   (0x8)
#define MCF_FBCS_CSCR_BSTR                   (0x10)
#define MCF_FBCS_CSCR_PS(x)                  (((x)&0x3)<<0x6)
#define MCF_FBCS_CSCR_PS_8                   (0x40)
#define MCF_FBCS_CSCR_PS_16                  (0x80)
#define MCF_FBCS_CSCR_AA                     (0x100)
#define MCF_FBCS_CSCR_MUX                    (0x200)
#define MCF_FBCS_CSCR_WS(x)                  (((x)&0x3F)<<0xA)
#define MCF_FBCS_CSCR_WRAH(x)                (((x)&0x3)<<0x10)
#define MCF_FBCS_CSCR_RDAH(x)                (((x)&0x3)<<0x12)
#define MCF_FBCS_CSCR_ASET(x)                (((x)&0x3)<<0x14)
#define MCF_FBCS_CSCR_SWSEN                  (0x800000)
#define MCF_FBCS_CSCR_SWS(x)                 (((x)&0x3F)<<0x1A)

/* Bit definitions and macros for MCF_GPIO_PTEPAR */
#define MCF_GPIO_PTEPAR_PTEPAR0              (0x1)
#define MCF_GPIO_PTEPAR_MB_A0_GPIO           (0)
#define MCF_GPIO_PTEPAR_MB_A0_MB_A0          (0x1)
#define MCF_GPIO_PTEPAR_PTEPAR1              (0x2)
#define MCF_GPIO_PTEPAR_MB_A1_GPIO           (0)
#define MCF_GPIO_PTEPAR_MB_A1_MB_A1          (0x2)
#define MCF_GPIO_PTEPAR_PTEPAR2              (0x4)
#define MCF_GPIO_PTEPAR_MB_A2_GPIO           (0)
#define MCF_GPIO_PTEPAR_MB_A2_MB_A2          (0x4)
#define MCF_GPIO_PTEPAR_PTEPAR3              (0x8)
#define MCF_GPIO_PTEPAR_MB_A3_GPIO           (0)
#define MCF_GPIO_PTEPAR_MB_A3_MB_A3          (0x8)
#define MCF_GPIO_PTEPAR_PTEPAR4              (0x10)
#define MCF_GPIO_PTEPAR_MB_A4_GPIO           (0)
#define MCF_GPIO_PTEPAR_MB_A4_MB_A4          (0x10)
#define MCF_GPIO_PTEPAR_PTEPAR5              (0x20)
#define MCF_GPIO_PTEPAR_MB_A5_GPIO           (0)
#define MCF_GPIO_PTEPAR_MB_A5_MB_A5          (0x20)
#define MCF_GPIO_PTEPAR_PTEPAR6              (0x40)
#define MCF_GPIO_PTEPAR_MB_A6_GPIO           (0)
#define MCF_GPIO_PTEPAR_MB_A6_MB_A6          (0x40)
#define MCF_GPIO_PTEPAR_PTEPAR7              (0x80)
#define MCF_GPIO_PTEPAR_MB_A7_GPIO           (0)
#define MCF_GPIO_PTEPAR_MB_A7_MB_A7          (0x80)

/* Bit definitions and macros for MCF_GPIO_PTGPAR */
#define MCF_GPIO_PTGPAR_PTGPAR0              (0x1)
#define MCF_GPIO_PTGPAR_MB_A16_GPIO          (0)
#define MCF_GPIO_PTGPAR_MB_A16_MB_A16        (0x1)
#define MCF_GPIO_PTGPAR_PTGPAR1              (0x2)
#define MCF_GPIO_PTGPAR_MB_A17_GPIO          (0)
#define MCF_GPIO_PTGPAR_MB_A17_MB_A17        (0x2)
#define MCF_GPIO_PTGPAR_PTGPAR2              (0x4)
#define MCF_GPIO_PTGPAR_MB_A18_GPIO          (0)
#define MCF_GPIO_PTGPAR_MB_A18_MB_A18        (0x4)
#define MCF_GPIO_PTGPAR_PTGPAR3              (0x8)
#define MCF_GPIO_PTGPAR_MB_A19_GPIO          (0)
#define MCF_GPIO_PTGPAR_MB_A19_MB_A19        (0x8)
#define MCF_GPIO_PTGPAR_PTGPAR4              (0x10)
#define MCF_GPIO_PTGPAR_PTGPAR5              (0x20)
#define MCF_GPIO_PTGPAR_MB_CS1_GPIO          (0)
#define MCF_GPIO_PTGPAR_MB_CS0_MB_CS0        (0x20)
#define MCF_GPIO_PTGPAR_PTGPAR6              (0x40)
#define MCF_GPIO_PTGPAR_MB_OE_GPIO           (0)
#define MCF_GPIO_PTGPAR_MB_OE_MB_OE          (0x40)
#define MCF_GPIO_PTGPAR_PTGPAR7              (0x80)
#define MCF_GPIO_PTGPAR_MB_RW_GPIO           (0)
#define MCF_GPIO_PTGPAR_MB_RW_MB_RW          (0x80)

/* Bit definitions and macros for MCF_GPIO_PTFPAR */
#define MCF_GPIO_PTFPAR_PTFPAR0              (0x1)
#define MCF_GPIO_PTFPAR_MB_A8_GPIO           (0)
#define MCF_GPIO_PTFPAR_MB_A8_MB_A8          (0x1)
#define MCF_GPIO_PTFPAR_PTFPAR1              (0x2)
#define MCF_GPIO_PTFPAR_MB_A9_GPIO           (0)
#define MCF_GPIO_PTFPAR_MB_A9_MB_A9          (0x2)
#define MCF_GPIO_PTFPAR_PTFPAR2              (0x4)
#define MCF_GPIO_PTFPAR_MB_A10_GPIO          (0)
#define MCF_GPIO_PTFPAR_MB_A10_MB_A10        (0x4)
#define MCF_GPIO_PTFPAR_PTFPAR3              (0x8)
#define MCF_GPIO_PTFPAR_MB_A11_GPIO          (0)
#define MCF_GPIO_PTFPAR_MB_A11_MB_A11        (0x8)
#define MCF_GPIO_PTFPAR_PTFPAR4              (0x10)
#define MCF_GPIO_PTFPAR_MB_A12_GPIO          (0)
#define MCF_GPIO_PTFPAR_MB_A12_MB_A12        (0x10)
#define MCF_GPIO_PTFPAR_PTFPAR5              (0x20)
#define MCF_GPIO_PTFPAR_MB_A13_GPIO          (0)
#define MCF_GPIO_PTFPAR_MB_A13_MB_A13        (0x20)
#define MCF_GPIO_PTFPAR_PTFPAR6              (0x40)
#define MCF_GPIO_PTFPAR_MB_A14_GPIO          (0)
#define MCF_GPIO_PTFPAR_MB_A14_MB_A14        (0x40)
#define MCF_GPIO_PTFPAR_PTFPAR7              (0x80)
#define MCF_GPIO_PTFPAR_MB_A15_GPIO          (0)
#define MCF_GPIO_PTFPAR_MB_A15_MB_A15        (0x80)

/* Bit definitions and macros for MCF_GPIO_PTFPAR */
#define MCF_GPIO_PTFPAR_PTFPAR0              (0x1)
#define MCF_GPIO_PTFPAR_MB_A8_GPIO           (0)
#define MCF_GPIO_PTFPAR_MB_A8_MB_A8          (0x1)
#define MCF_GPIO_PTFPAR_PTFPAR1              (0x2)
#define MCF_GPIO_PTFPAR_MB_A9_GPIO           (0)
#define MCF_GPIO_PTFPAR_MB_A9_MB_A9          (0x2)
#define MCF_GPIO_PTFPAR_PTFPAR2              (0x4)
#define MCF_GPIO_PTFPAR_MB_A10_GPIO          (0)
#define MCF_GPIO_PTFPAR_MB_A10_MB_A10        (0x4)
#define MCF_GPIO_PTFPAR_PTFPAR3              (0x8)
#define MCF_GPIO_PTFPAR_MB_A11_GPIO          (0)
#define MCF_GPIO_PTFPAR_MB_A11_MB_A11        (0x8)
#define MCF_GPIO_PTFPAR_PTFPAR4              (0x10)
#define MCF_GPIO_PTFPAR_MB_A12_GPIO          (0)
#define MCF_GPIO_PTFPAR_MB_A12_MB_A12        (0x10)
#define MCF_GPIO_PTFPAR_PTFPAR5              (0x20)
#define MCF_GPIO_PTFPAR_MB_A13_GPIO          (0)
#define MCF_GPIO_PTFPAR_MB_A13_MB_A13        (0x20)
#define MCF_GPIO_PTFPAR_PTFPAR6              (0x40)
#define MCF_GPIO_PTFPAR_MB_A14_GPIO          (0)
#define MCF_GPIO_PTFPAR_MB_A14_MB_A14        (0x40)
#define MCF_GPIO_PTFPAR_PTFPAR7              (0x80)
#define MCF_GPIO_PTFPAR_MB_A15_GPIO          (0)
#define MCF_GPIO_PTFPAR_MB_A15_MB_A15        (0x80)


#define D4DLCD_DISPLAY_MCU_USER_INIT MCF_GPIO_PTEPAR |= MCF_GPIO_PTEPAR_MB_A0_MB_A0 | MCF_GPIO_PTEPAR_MB_A1_MB_A1 | MCF_GPIO_PTEPAR_MB_A2_MB_A2 | MCF_GPIO_PTEPAR_MB_A3_MB_A3 | MCF_GPIO_PTEPAR_MB_A4_MB_A4 | MCF_GPIO_PTEPAR_MB_A5_MB_A5 | MCF_GPIO_PTEPAR_MB_A6_MB_A6 | MCF_GPIO_PTEPAR_MB_A7_MB_A7; \
  MCF_GPIO_PTFPAR |= MCF_GPIO_PTFPAR_MB_A8_MB_A8 | MCF_GPIO_PTFPAR_MB_A9_MB_A9 | MCF_GPIO_PTFPAR_MB_A10_MB_A10 | MCF_GPIO_PTFPAR_MB_A11_MB_A11 | MCF_GPIO_PTFPAR_MB_A12_MB_A12 |MCF_GPIO_PTFPAR_MB_A13_MB_A13 | MCF_GPIO_PTFPAR_MB_A14_MB_A14 | MCF_GPIO_PTFPAR_MB_A15_MB_A15; \
  MCF_GPIO_PTGPAR |= MCF_GPIO_PTGPAR_MB_A16_MB_A16 | MCF_GPIO_PTGPAR_MB_CS0_MB_CS0 | MCF_GPIO_PTGPAR_MB_RW_MB_RW;

#define D4DLCD_FLEX_BASE_ADDRESS  0x00410000

  

#define D4DLCD_FLEX_DC_ADDRESS    0x00400000



#define D4DLCD_FLEX_ADRESS_MASK   0x00010000


#define D4DLCD_FLEX_CS 0


#define D4DLCD_FLEX_CSAR MCF_FBCS0_CSAR
#define D4DLCD_FLEX_CSMR MCF_FBCS0_CSMR
#define D4DLCD_FLEX_CSCR MCF_FBCS0_CSCR


#define D4DLCD_FLEX_CSMR_V_MASK MCF_FBCS_CSMR_V
#define D4DLCD_FLEX_CSCR_MUX_MASK MCF_FBCS_CSCR_MUX
#define D4DLCD_FLEX_CSCR_AA_MASK MCF_FBCS_CSCR_AA
#define D4DLCD_FLEX_CSCR_PS1_MASK MCF_FBCS_CSCR_PS_16


static unsigned char D4DLCDHW_Init_Flexbus_16b(void)
  {
    #ifdef D4DLCD_DISPLAY_MCU_USER_INIT
      D4DLCD_DISPLAY_MCU_USER_INIT
    #endif  
    
    
    D4DLCD_FLEX_CSAR = D4DLCD_FLEX_DC_ADDRESS; // CS0 base address
    D4DLCD_FLEX_CSMR = D4DLCD_FLEX_ADRESS_MASK | D4DLCD_FLEX_CSMR_V_MASK; // The address range is set to 128K because the DC signal is connected on address wire 
    D4DLCD_FLEX_CSCR = D4DLCD_FLEX_CSCR_MUX_MASK | D4DLCD_FLEX_CSCR_AA_MASK | D4DLCD_FLEX_CSCR_PS1_MASK; // FlexBus setup as fast as possible in multiplexed mode
    
    return 1; 
  }

#define D4DLCD_ASSERT_RESET RESET(D4DLCD_RESET);

#endif

void LCD_Run(void) {
  GDisp1_PixelDim x, y;
  short xOffset, yOffset;
  GDisp1_PixelColor color;
  unsigned char line;

  D4DLCDHW_Init_Flexbus_16b();
  LCD1_Init();
  
  GDisp1_DrawFilledBox(0, 0, GDisp1_GetWidth(), GDisp1_GetHeight(), GDisp1_COLOR_WHITE);
  color = GDisp1_COLOR_BLUE;
  yOffset = xOffset = OFFSET;
  x = y = 0;
  line = 1;
  for(;;) {
    /* toggle the LED's */
    LED2_Neg();
    LED3_Neg();
    LED4_Neg();
    /* show graphic routines */
    GDisp1_DrawBox(x, y, BOX_WIDTH, BOX_HEIGHT, 2, color);
    if (x>GDisp1_GetWidth()-BOX_WIDTH) {
      xOffset = -xOffset;
    }
    if (y>GDisp1_GetHeight()-BOX_HEIGHT) {
      yOffset = -yOffset;
    }
    color++; /* iterate through color */
    x += xOffset;
    y += yOffset;
    /* draw some text */
    PrintTouchText(line);
    line++;
    if (line>10) {
      /* clear text area */
      line = 1;
      GDisp1_DrawFilledBox(0, 0, 150, 160, color);
    }
    /* handling touch screen */
    TCHS1_Scan(); /* this will call TCHS1_OnEvent() */
  } /* for */}

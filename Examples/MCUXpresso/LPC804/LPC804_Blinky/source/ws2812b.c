/*

  ws2812b.c

  PLU will be configured as SPI client. 
  SPI clock should 800kHz: SPI clock div for the main clk can be 18 (833kHz) or 19 (789kHz)
  
  PLU configuration:
    sck: PIO0_22;
    mosi: PIO0_21;
  
*/
#include "platform.h"
#include "ws2812b.h"
#include "LPC8xx.h"
#include "iocon.h"
#include "syscon.h"
#include "gpio.h"
#include "swm.h"
#include "spi.h"
#include "McuWait.h"
#include "plu_setup.h"
#include "NeoPixel.h"
#include <string.h>

#define map_function_to_port   ConfigSWM

static void delay_micro_seconds(uint32_t us) {
  McuWait_Waitus(us);
}

void spi_init(void) {
  Enable_Periph_Clock(CLK_SPI0);
#if PL_NO_PLU_SPI_ONLY
  map_function_to_port(SPI0_SCK, 9);
  map_function_to_port(SPI0_MOSI, 8);
#else
  map_function_to_port(SPI0_SCK, 9);
  map_function_to_port(SPI0_MOSI, 11);
#endif
  
  LPC_SYSCON->SPI0CLKSEL = FCLKSEL_MAIN_CLK;	
#if PL_NO_PLU_SPI_ONLY
  LPC_SPI0->DIV = 6;  /* SPI Clock Div = 6 --> 2.5MHz SPI Clock --> 400ns */
#else
#if PL_PLU_FAST
  LPC_SPI0->DIV = 14;	/* 13 still seems to work */
#else
  LPC_SPI0->DIV = 24;	/* 22 still seems to work */
#endif
#endif
  LPC_SPI0->CFG = SPI_CFG_ENABLE | SPI_CFG_MASTER;
}

void WS2812B_spi_out(uint8_t *data, size_t cnt) {
  LPC_SPI0->TXCTL = 
      SPI_CTL_RXIGNORE | 		/* do not read data from MISO */
      SPI_CTL_LEN(8) | 			/* send 8 bits */
      SPI_TXDATCTL_SSELN(3); 	/* do not use any slave select */
  for(int i=0; i<cnt; i++) {
    /* wait until the tx register can accept further data */
    while( (LPC_SPI0->STAT & SPI_STAT_TXRDY) == 0 ) {}
    /* ensure, that the SCK goes to low after the byte transfer: */
    /* Set the EOT flag at the end of the transfer */
    if (i+1 == cnt) {
      LPC_SPI0->TXCTL |= SPI_CTL_EOT;
    }
    /* transfer one byte via SPI */
    LPC_SPI0->TXDAT = data[i];
  }
}

void WS2812B_SendPixels(uint8_t *data, size_t cnt) {
  WS2812B_spi_out(data, cnt);
  /* LPC804 has might have up to two bytes in the queue, wait for their transmission */
  delay_micro_seconds(24+24);
  /* write the new values into the LEDs */
  delay_micro_seconds(50);
}

#if PL_NO_PLU_SPI_ONLY
/*=======================================================================*/
/*
  convert 0 to 1000 and 1 to 1100
  "out" array must be 4x bigger than "in" array.
*/
void convert_to_ws2812b(int cnt, uint8_t *in, uint8_t *out)
{
  int i, j;
  uint8_t b;
  for ( i = 0; i < cnt; i++ )
  {
    b = in[i];
    j = 4;
    do
    {
      *out = 0x44;
      if ( b & 128 )
	*out |= 0x20;
      b <<= 1;
      if ( b & 128 )
	*out |= 0x02;
      b <<= 1;
      out++;
      j--;
    } while( j > 0 );
  }
}
#endif
/*=======================================================================*/

/* https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both */
void hsv_to_rgb(uint8_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g, uint8_t *b) {
    uint8_t region, remainder, p, q, t;

    if (s == 0) {
        *r = v;
        *g = v;
        *b = v;
        return ;
    }

    region = h / 43;
    remainder = (h - (region * 43)) * 6; 

    p = (v * (uint16_t)(255 - s)) >> 8;
    q = (v * (uint16_t)(255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (uint16_t)(255 - ((s * (uint16_t)(255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            *r = v; *g = t; *b = p;
            break;
        case 1:
            *r = q; *g = v; *b = p;
            break;
        case 2:
            *r = p; *g = v; *b = t;
            break;
        case 3:
            *r = p; *g = q; *b = v;
            break;
        case 4:
            *r = t; *g = p; *b = v;
            break;
        default:
            *r = v; *g = p; *b = q;
            break;
    }
}

/*=======================================================================*/

/* color component slide */
struct _ccs_t
{
  int16_t current;	/* contains the current color component */
  int16_t start;
  int16_t steps;
  
  int16_t dir;		/* 1 if start < end or -1 if start > end */
  int16_t num;
  int16_t quot;
  
  int16_t den;
  int16_t rem;  
  int16_t frac;
};
typedef struct _ccs_t ccs_t;


/*
  Setup change from "start" to "end" with a specified amount of "steps".
  After calling this procedure, ccs->current will contain the "start" value.
*/
void ccs_init(ccs_t *ccs, int16_t start, int16_t end, int16_t steps)
{
  ccs->start = start;
  ccs->num = end-start;
  ccs->den = steps-1;
  ccs->steps = steps;
  ccs->dir = 1;
  
  ccs->quot = ccs->num / ccs->den;
  if ( ccs->num < 0 )
  {
    ccs->num = -ccs->num;
    ccs->dir = -1;
  }
  ccs->rem = ccs->num % ccs->den;
  
  ccs->frac = ccs->den/2;
  ccs->current = start;
}

/*
  Make one step towards the "end" value. 
  ccs->current will contain the updated value.
*/
int16_t ccs_step(ccs_t *ccs)
{
  if ( ccs->steps == 0 ) 
    return 0;
  
  ccs->current += ccs->quot;
  ccs->frac += ccs->rem;
  if ( ccs->frac >= ccs->den )
  {
    ccs->current += ccs->dir;
    ccs->frac -= ccs->den;
  }
  ccs->steps--;
  return 1;
}

/*
  f(x) = (e-s)/(n-1) * x + s
  current = (num / den)  * (pos / den)
  
  Seek to the specified "pos"ition.
  "pos" must be between 0 and "end"-1
*/
void ccs_seek(ccs_t *ccs, int16_t pos)
{
  int16_t p;
  ccs->current = ccs->quot;
  ccs->current *= pos;
  p = ccs->rem * pos  + ccs->den/2;
  if ( ccs->dir >= 0 )
    ccs->current += p / ccs->den;
  else
    ccs->current -= p / ccs->den;
  ccs->frac = p % ccs->den;
  ccs->current += ccs->start;
}


//void SystemInit_PLU(void);
//void SystemCoreClockUpdate_PLU(void);

#define WS2812_NOF_LEDS   (16)
#define WS2812_NOF_COLORS (4)

void __attribute__ ((noinline)) WS2812B_main(void) {

  uint8_t a[WS2812_NOF_LEDS*WS2812_NOF_COLORS] =
  /* g     r     b */
  {
#if 0
    0x00, 0x3c, 0x00,
    0x00, 0x00, 0x3c,
	0x3c, 0x00, 0x00,
	0x11, 0x11, 0x11,
	0x22, 0x00, 0x22,
	0x00, 0x44, 0x22,
	0x22, 0x44, 0x00,
	0x11, 0x22, 0x44,
    0x00, 0x3c, 0x00,
    0x00, 0x00, 0x3c,
	0x3c, 0x00, 0x00,
	0x11, 0x11, 0x11,
	0x22, 0x00, 0x22,
	0x00, 0x44, 0x22,
	0x22, 0x44, 0x00,
	0x11, 0x22, 0x44,
#endif
  };
#if PL_NO_PLU_SPI_ONLY
  uint8_t aa[WS2812_NOF_LEDS*WS2812_NOF_COLORS*4]; /* in SPI mode, needs 4x time the memory */
  //uint8_t last_byte;
#endif
  int h = 0;
  ccs_t ccs_v;
  int is_v_up = 1;

  memset(a, 0, sizeof(a)); /* initialize */
#if PL_NO_PLU_SPI_ONLY
  GPIOInit();
  Enable_Periph_Clock(CLK_IOCON);
  Enable_Periph_Clock(CLK_SWM);
  GPIOSetDir(PORT0, 8, OUTPUT);	// output for MOSI
#endif

#if PL_CONFIG_USE_PLU
  plu_setup(); /*  will enable GPIO0 & SWM clock */
#endif
  spi_init();
#define B_START (10)
#define B_END   (40)

  delay_micro_seconds(50);
  ccs_init(&ccs_v, B_START, B_END, 30);
  is_v_up = 1;
  for(;;) {
#if 1 /* color cycling */
    h+=2;	/* will turn around at 255 */
    for(int led=0; led<WS2812_NOF_LEDS; led++) {
      hsv_to_rgb(h+led*20, 255, ccs_v.current, a+(led*WS2812_NOF_COLORS)+0, a+(led*WS2812_NOF_COLORS)+1, a+(led*WS2812_NOF_COLORS)+2);
    }
    if ( ccs_step(&ccs_v) == 0 ) {
      if ( is_v_up ) {
        ccs_init(&ccs_v, B_END, B_START, 30);
        is_v_up = 0;
      } else {
        ccs_init(&ccs_v, B_START, B_END, 30);
        is_v_up = 1;
      }
    }
#endif
#if PL_NO_PLU_SPI_ONLY
    convert_to_ws2812b(sizeof(a), a, aa);
    spi_out(aa, sizeof(aa));
    //last_byte = 0;
    //spi_out(&last_byte, sizeof(last_byte));
#else
    WS2812B_spi_out(a, sizeof(a));
#endif
    /* LPC804 has might have up to two bytes in the queue, wait for their transmission */    
    delay_micro_seconds(24+24);
    /* write the new values into the LEDs */
    delay_micro_seconds(50);
    
    /* end user delay */
    delay_micro_seconds(20000L);
  }
}

void WS2812B_Init(void) {
#if PL_CONFIG_USE_PLU
  plu_setup(); /*  will enable GPIO0 & SWM clock */
#endif
  spi_init();
}

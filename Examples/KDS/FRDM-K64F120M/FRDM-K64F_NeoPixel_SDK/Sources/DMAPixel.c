/**
 * \file
 * \brief WS2812B Driver using DMA.
 * \author Erich Styger
 *
 * This module deals with the low level timer and eDMA to
 * generate the bitstream for multiple WS2812B lanes.
 * \license
 *  This is a free software and is opened for education,  research and commercial developments under license policy of following terms:
 *  This is a free software and there is NO WARRANTY.
 *  No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
 *  Redistributions of source code must retain the above copyright notice.
 */

#include "DMAPixel.h"
#include <stdint.h>
#include <stdbool.h>
#include "fsl_ftm_driver.h"
#include "fsl_edma_driver.h"
#include "fsl_sim_hal_MK64F12.h"
#include "fsl_mcg_hal.h"
#include "fsl_port_hal.h"
#include <string.h> /* for memset() */

/* FTM related */
#define NOF_FTM_CHANNELS  3 /* using three FTM0 channels, running with 60 MHz system clock */
#define FTM_CH0_TICKS     (0x10)  /* delay until 0xFF */
#define FTM_CH1_TICKS     (0x2A)  /* at 0.4us write data */
#define FTM_CH2_TICKS     (0x40)  /* at 0.8us clear bits  */
#define FTM_PERIOD_TICKS  (0x4B)  /* 1.25 us period */

/* DMA related */
#define NOF_EDMA_CHANNELS  3 /* using three DMA channels */
static edma_chn_state_t chnStates[NOF_EDMA_CHANNELS]; /* array of DMA channel states */
static volatile bool dmaDone = false; /* set by DMA complete interrupt on DMA channel 3 */
static const uint8_t OneValue = 0x01; /* value to clear or set the port bit(s) */

const uint8_t gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,
    3,  3,  3,  4,  4,  4,  4,  4,  4,  5,  5,  5,  5,  6,  6,  6,
    6,  6,  7,  7,  7,  8,  8,  8,  8,  9,  9,  9, 10, 10, 10, 11,
   11, 12, 12, 12, 13, 13, 14, 14, 14, 15, 15, 16, 16, 17, 17, 18,
   18, 19, 19, 20, 21, 21, 22, 22, 23, 23, 24, 25, 25, 26, 27, 27,
   28, 29, 30, 30, 31, 32, 33, 33, 34, 35, 36, 37, 37, 38, 39, 40,
   41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56,
   57, 59, 60, 61, 62, 63, 65, 66, 67, 68, 70, 71, 72, 74, 75, 76,
   78, 79, 81, 82, 84, 85, 87, 88, 90, 91, 93, 95, 96, 98, 99,101,
  103,105,106,108,110,112,113,115,117,119,121,123,125,127,129,131,
  133,135,137,139,141,143,146,148,150,152,154,157,159,161,164,166,
  168,171,173,176,178,181,183,186,188,191,194,196,199,202,204,207,
  210,213,216,219,221,224,227,230,233,236,239,242,246,249,252,255
 };

/* --------------------------------------- */
/* FTM                                     */
/* --------------------------------------- */
static void StartStopFTM(uint32_t instance, bool startIt) {
  FTM_Type *ftmBase = g_ftmBase[instance];

  if (startIt) {
    FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_SystemClk); /* clock timer */
  } else {
    FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_None); /* disable clock */
  }
}

static void ResetFTM(uint32_t instance) {
  FTM_Type *ftmBase = g_ftmBase[instance];
  uint8_t channel;

  /* reset all values */
  FTM_HAL_SetCounter(ftmBase, 0); /* reset FTM counter */
  FTM_HAL_ClearTimerOverflow(ftmBase); /* clear timer overflow flag (if any) */
  for(channel=0; channel<NOF_FTM_CHANNELS; channel++) {
    FTM_HAL_ClearChnEventFlag(ftmBase, channel); /* clear channel flag */
    FTM_HAL_SetChnDmaCmd(ftmBase, channel, true); /* enable DMA request */
    FTM_HAL_EnableChnInt(ftmBase, channel); /* enable channel interrupt: need to have both DMA and CHnIE set for DMA transfers! See RM 40.4.23 */
  }
}

static void StopFTMDMA(uint32_t instance) {
  FTM_Type *ftmBase = g_ftmBase[instance];
  uint8_t channel;

  StartStopFTM(instance, false); /* stop FTM timer */
  /* reset all values */
  FTM_HAL_SetCounter(ftmBase, 0); /* reset FTM counter */
  FTM_HAL_ClearTimerOverflow(ftmBase); /* clear timer overflow flag (if any) */
  for(channel=0; channel<NOF_FTM_CHANNELS; channel++) {
    FTM_HAL_DisableChnInt(ftmBase, channel); /* disable channel interrupt */
    FTM_HAL_SetChnDmaCmd(ftmBase, channel, false); /* disable DMA request */
    FTM_HAL_ClearChnEventFlag(ftmBase, channel); /* clear channel flag */
  }
}

static void InitFlexTimer(uint32_t instance) {
  ftm_pwm_param_t flexTimer0_ChnConfig0 = { /* FTM channel configuration */
    .mode = kFtmEdgeAlignedPWM,
    .edgeMode = kFtmHighTrue,
    .uFrequencyHZ = 1000U, /* dummy value, will change it later on */
    .uDutyCyclePercent = 10U, /* dummy value, will change it later on */
    .uFirstEdgeDelayPercent = 0U,
  };
  ftm_user_config_t flexTimer0_InitConfig0 = {
    .tofFrequency      = 0U,
    .isWriteProtection = false, /* FTM is not write protected */
    .BDMMode           = kFtmBdmMode_00, /* default mode for debug: timer will be stopped, can modify registers */
    .syncMethod        = (uint32_t)(kFtmUseSoftwareTrig) /* using software synchronization */
  };
  FTM_Type *ftmBase = g_ftmBase[instance];

  /* initialize the driver */
  FTM_DRV_Init(instance, &flexTimer0_InitConfig0); /* initialize the driver with a default configuration */
  FTM_DRV_SetTimeOverflowIntCmd(instance, false); /* disable interrupt */
  FTM_DRV_SetFaultIntCmd(instance, false); /* disable interrupt */
  FTM_DRV_SetClock(instance, kClock_source_FTM_SystemClk, kFtmDividedBy1); /* use system clock with a divider of 1 */

  /* configure timer */
  FTM_HAL_ClearTimerOverflow(ftmBase); /* clear timer overflow */

  /* enable PWM mode for the channels */
  FTM_HAL_EnablePwmMode(ftmBase, (ftm_pwm_param_t*)&flexTimer0_ChnConfig0, 0);
  FTM_HAL_EnablePwmMode(ftmBase, (ftm_pwm_param_t*)&flexTimer0_ChnConfig0, 1);
  FTM_HAL_EnablePwmMode(ftmBase, (ftm_pwm_param_t*)&flexTimer0_ChnConfig0, 2);

  /* based on Ref manual, in PWM mode CNTIN is to be set 0*/
  FTM_HAL_SetCounterInitVal(ftmBase, 0);

  /* set the module counters */
  FTM_HAL_SetMod(ftmBase, FTM_PERIOD_TICKS);
  FTM_HAL_SetChnCountVal(ftmBase, 0, FTM_CH0_TICKS);
  FTM_HAL_SetChnCountVal(ftmBase, 1, FTM_CH1_TICKS);
  FTM_HAL_SetChnCountVal(ftmBase, 2, FTM_CH2_TICKS);
}

/* --------------------------------------- */
/* DMA                                     */
/* --------------------------------------- */
/*! @brief Dma channel 2 ISR */
void DMA2_IRQHandler(void){
   EDMA_DRV_IRQHandler(2U); /* call SDK EDMA IRQ handler, this will call EDMA_Callback() */
}

void EDMA_Callback(void *param, edma_chn_status_t chanStatus) {
  (void)param; /* not used */
  (void)chanStatus; /* not used */
  dmaDone = true; /* set 'done' flag at the end of the major loop */
}

static void PushDMADescriptor(edma_transfer_config_t *config, edma_chn_state_t *chn, bool enableInt) {
  /* If only one TCD is required, only hardware TCD is required and user
   * is not required to prepare the software TCD memory. */
  edma_software_tcd_t temp[2]; /* make it larger so we can have a 32byte aligned address into it */
  edma_software_tcd_t *tempTCD = STCD_ADDR(temp); /* ensure that we have a 32byte aligned address */

  memset((void*) tempTCD, 0, sizeof(edma_software_tcd_t)); /* initialize temporary descriptor with zeros */
  EDMA_DRV_PrepareDescriptorTransfer(chn, tempTCD, config, enableInt, true); /* prepare and copy descriptor into temporary one */
  EDMA_DRV_PushDescriptorToReg(chn, tempTCD); /* write EDMA registers */
}

void DMA_Transfer(uint8_t *transmitBuf, uint32_t nofBytes) {
  edma_transfer_config_t config;
  uint8_t channel;
  uint8_t res;

  ResetFTM(FTM0_IDX); /* clear FTFM and prepare for DMA */

  /* DMA Muxing: Allocate EDMA channel request trough DMAMUX */
  for (channel=0; channel<NOF_EDMA_CHANNELS; channel++) {
    res = EDMA_DRV_RequestChannel(channel, kDmaRequestMux0FTM0Channel0+channel, &chnStates[channel]);
    if (res==kEDMAInvalidChannel) { /* check error code */
      for(;;); /* ups!?! */
    }
  }
  /* Install callback for eDMA handler on last channel which is channel 2 */
  EDMA_DRV_InstallCallback(&chnStates[NOF_EDMA_CHANNELS-1], EDMA_Callback, NULL);

  /* prepare DMA configuration */
  config.srcLastAddrAdjust = 0; /* no address adjustment needed after last transfer */
  config.destLastAddrAdjust = 0; /* no address adjustment needed after last transfer */
  config.srcModulo = kEDMAModuloDisable; /* no address modulo (no ring buffer) */
  config.destModulo = kEDMAModuloDisable; /* no address modulo (no ring buffer) */
  config.srcTransferSize = kEDMATransferSize_1Bytes; /* transmitting one byte in each DMA transfer */
  config.destTransferSize = kEDMATransferSize_1Bytes; /* transmitting one byte in each DMA transfer */
  config.minorLoopCount = 1; /* one byte transmitted for each request */
  config.majorLoopCount = nofBytes; /* total number of bytes to send */
  config.destOffset = 0; /* do not increment destination address */

  config.srcAddr = (uint32_t)&OneValue; /* Bit set */
  config.destAddr = (uint32_t)&GPIO_PSOR_REG(PTD_BASE_PTR); /* Port Set Output register */
  config.srcOffset = 0; /* do not increment source address */
  PushDMADescriptor(&config, &chnStates[0], false); /* write configuration to DMA channel 0 */

  config.srcAddr = (uint32_t)transmitBuf; /* pointer to data */
  config.destAddr = (uint32_t)&GPIO_PDOR_REG(PTD_BASE_PTR); /* Port Data Output register */
  config.srcOffset = 1; /* increment source address */
  PushDMADescriptor(&config, &chnStates[1], false); /* write configuration to DMA channel 1 */

  config.srcAddr = (uint32_t)&OneValue; /* Bit set */
  config.destAddr = (uint32_t)&GPIO_PCOR_REG(PTD_BASE_PTR); /* Port Clear Output register */
  config.srcOffset = 0; /* do not increment source address */
  PushDMADescriptor(&config, &chnStates[2], true); /* write configuration to DMA channel 1, and enable 'end' interrupt for it */

  /* enable the DMA channels */
  for (channel=0; channel<NOF_EDMA_CHANNELS; channel++) {
    EDMA_DRV_StartChannel(&chnStates[channel]); /* enable DMA */
  }
  dmaDone = false; /* reset done flag */
  StartStopFTM(FTM0_IDX, true); /* start FTM timer to fire sequence of DMA transfers */
  do {
    /* wait until transfer is complete */
  } while(!dmaDone);
  StopFTMDMA(FTM0_IDX); /* stop FTM DMA transfers */
  for (channel=0; channel<NOF_EDMA_CHANNELS; channel++) {
    EDMA_DRV_StopChannel(&chnStates[channel]); /* stop DMA channel */
  }
  /* Release EDMA channel request trough DMAMUX, otherwise events might still be latched! */
  for (channel=0; channel<NOF_EDMA_CHANNELS; channel++) {
    res = EDMA_DRV_ReleaseChannel(&chnStates[channel]);
    if (res!=kStatus_EDMA_Success) { /* check error code */
      for(;;); /* ups!?! */
    }
  }
}

static void InitDMADriver(void) {
  edma_user_config_t  edmaUserConfig;
  static edma_state_t edmaState;
  uint8_t res, channel;

  /* Initialize eDMA modules. */
  edmaUserConfig.chnArbitration = kEDMAChnArbitrationRoundrobin; /* use round-robin arbitration */
  edmaUserConfig.notHaltOnError = false; /* do not halt in case of errors */
  EDMA_DRV_Init(&edmaState, &edmaUserConfig); /* initialize DMA with configuration */
}

static void InitHardware(void) {
  /* Enable clock for PORTs */
  SIM_HAL_EnableClock(SIM, kSimClockGatePortA);
  SIM_HAL_EnableClock(SIM, kSimClockGatePortB);
  SIM_HAL_EnableClock(SIM, kSimClockGatePortC);
  SIM_HAL_EnableClock(SIM, kSimClockGatePortD);
  SIM_HAL_EnableClock(SIM, kSimClockGatePortE);

  /* Setup board clock source. */
  g_xtal0ClkFreq = 50000000U;           /* Value of the external crystal or oscillator clock frequency of the system oscillator (OSC) in Hz */
  g_xtalRtcClkFreq = 32768U;            /* Value of the external 32k crystal or oscillator clock frequency of the RTC in Hz */

  /* Use PTD0 as DIN to the Neopixels: mux it as GPIO and output pin */
  PORT_HAL_SetMuxMode(PORTD, 0UL, kPortMuxAsGpio); /* PTD0: DIN to NeoPixels */
  GPIO_PDDR_REG(PTD_BASE_PTR) |= (1<<0); /* PTD0 as output */

  /* FTM and FTM Muxing */
  InitFlexTimer(FTM0_IDX);
  PORT_HAL_SetMuxMode(PORTC,1UL,kPortMuxAlt4); /* use PTC1 for channel 0 of FTM0 */
  PORT_HAL_SetMuxMode(PORTC,2UL,kPortMuxAlt4); /* use PTC2 for channel 1 of FTM0 */
  PORT_HAL_SetMuxMode(PORTC,3UL,kPortMuxAlt4); /* use PTC3 for channel 2 of FTM0 */

  InitDMADriver(); /* initialize DMA driver */
}

void DMA_Init(void) {
  InitHardware();
  ResetFTM(FTM0_IDX);
  StartStopFTM(FTM0_IDX, true); /* start FTM timer */
}

/* --------------------------------------- */
/* RNG                                     */
/* --------------------------------------- */
void RNG_Init(void){
	SIM_SCGC6 |= SIM_SCGC6_RNGA_MASK;// Gate the clock for RNG unit
	RNG_CR &= ~RNG_CR_SLP_MASK;// set SLP bit to 0 - "RNGA is not in sleep mode" 
	RNG_CR |= RNG_CR_HA_MASK;// set HA bit to 1 - "security violations masked" 
	RNG_CR |= RNG_CR_GO_MASK;// set GO bit to 1 - "output register loaded with data" 
}  

/* get a random number between 0 and limit
 * Used to get a random pixel for generating random LED patterns
*/
uint32_t getRandom(uint8_t limit){
	while((RNG_SR & RNG_SR_OREG_LVL(0xF)) == 0) {}
    /* get value */
    return RNG_OR%limit;
}

void initBuffer(void){
	for(uint32_t i=0;i<NEO_NOF_PIXEL*NEO_NOF_BITS_PIXEL;i++){
		transmitBuf[i] = 0;
	}	
}

void setPixel(uint8_t Pixel, Color c) {
	RGB cc = packColor(c);
	for(uint32_t j=(Pixel*NEO_NOF_BITS_PIXEL);j<(Pixel*NEO_NOF_BITS_PIXEL)+NEO_NOF_BITS_PIXEL;j++){
		transmitBuf[j] = cc & 0x1;
		cc=cc>>1;
	}
} 

void setAll(Color c) {
  for(uint8_t i=0; i<NEO_NOF_PIXEL; i++ ) {
    setPixel(i, c); 
  }
}

void theaterChase(Color c, uint32_t SpeedDelay) {
  for (uint8_t j=0; j<10; j++) {  //do 10 cycles of chasing
    for (uint8_t q=0; q < 4; q++) {
      for (uint8_t i=0; i < NEO_NOF_PIXEL; i=i+4) {
        setPixel(i+q, c);    //turn every third pixel on
        //setPixel(i+q-1, red, green, blue);
      }
      DMA_Transfer(transmitBuf, sizeof(transmitBuf));
      delay(SpeedDelay);
      for (uint8_t i=0; i < NEO_NOF_PIXEL; i=i+4) {
        setPixel(i+q-1, Black);        //turn every third pixel off
        //setPixel(i+q-1, 0,0,0);
      }
    }
  }
}

void FadeInOut(Color c){
  float r, g, b;
  Color cc;
      
  for(int k = 0; k < 256; k=k+1) { 
    r = (k/256.0)*c.r;
    g = (k/256.0)*c.g;
    b = (k/256.0)*c.b;
   	cc.r=r; cc.g=g; cc.b=b; 
    setAll(cc);
    DMA_Transfer(transmitBuf, sizeof(transmitBuf));
  }
     
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/256.0)*c.r;
    g = (k/256.0)*c.g;
    b = (k/256.0)*c.b;
    c.r=r; c.g=g; c.b=b; 
    setAll(c);
    DMA_Transfer(transmitBuf, sizeof(transmitBuf));
  }
}

void colorWipe(Color c, uint32_t SpeedDelay) {
  for(uint8_t i=0; i<NEO_NOF_PIXEL; i++) {
      setPixel(i, c);
      DMA_Transfer(transmitBuf, sizeof(transmitBuf));
      delay(SpeedDelay);
  }
  
}

void Twinkle(Color c, uint32_t Count, uint32_t SpeedDelay, uint8_t OnlyOne, uint8_t reset) {
  if(reset){
  	setAll(Black);
  }  
  for (int i=0; i<Count; i++) {
     setPixel(getRandom(NEO_NOF_PIXEL),c);
     DMA_Transfer(transmitBuf, sizeof(transmitBuf));
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAll(Black); 
     }
   }
  delay(SpeedDelay);
}

void randomColors(uint8_t count){
	for(uint8_t i=0;i<count;i++){
		Twinkle(Red,6,400,0,0);
		Twinkle(Green,4,400,0,0);
		Twinkle(Blue,7,400,0,0);
		Twinkle(Black,3,400,0,0);
	}
}

/*!brief Delay routine */
void delay(uint32_t ms)
{
  for(uint32_t i=0; i<1000*ms; i++){
      __asm__("nop");
  }
}

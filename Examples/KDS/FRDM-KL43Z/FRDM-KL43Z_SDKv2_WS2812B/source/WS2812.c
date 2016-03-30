#include <stdint.h>
#include "WS2812.h"
#include "MKL43Z4.h"

static uint32_t *isr_p32_strip_data, isr_data_cnt, isr_data_index, isr_cnt, isr_transfer_done;

// FlexIO isr indicator: high when the FlexIO isr is running
#define	FLEXIO_ISR_PORT			PORTE
#define	FLEXIO_ISR_IOPORT		PTE
#define	FLEXIO_ISR_PIN			20

// done flag waiting loop indicator: high while waiting for the RET code to be sent to the WS2812 strip
#define	WAITING_LOOP_PORT		PORTE
#define	WAITING_LOOP_IOPORT	PTE
#define	WAITING_LOOP_PIN		21

// WS2812B timing setup based on the 8 MHz FlexIO clock (IRC)
// 8 MHz => 1 clock cycle = 0.125 us
// T0H = 3*0.125 us = 0.375 us (0.40 us +/- 0.15 us)   T1H = 6*0.125 us = 0.75 us (0.80 us +/- 0.15 us)
// T0L = 7*0.125 us = 0.875 us (0.85 us +/- 0.15 us)   T1L = 4*0.125 us = 0.50 us (0.45 us +/- 0.15 us)
// WS2812B bit rate = 1/10 FlexIO clock
#define	WS2812_CLK_DIVIDER	10
#define	WS2812_T0H_CLKS			3
#define	WS2812_T0L_CLKS			7
#define	WS2812_T1H_CLKS			6
#define	WS2812_T1L_CLKS			4

// the ws2812 initialization routine:
// - drives the isr and waiting loop indicators to low
// - enables the 8 MHz IRC as the FlexIO clock source
// - performs FlexIO initialization common for all 3 control modes
//   - allocates timers and shifter resources
//   - configures port pins
//   - programs individual timer and shifter blocks
// - configures interrupt and DMA resources
static uint32_t ws2812_generator_shifter;
static uint32_t ws2812_ret_timer;

void WS2812_Init(void) {
  uint32_t ws2812_generator_timer;
  uint32_t ws2812_generator_clk_fxio_pin, ws2812_generator_data_fxio_pin;
  uint32_t ws2812_l0_timer, ws2812_l0_timer_fxio_pin;
  uint32_t ws2812_l1_timer, ws2812_l1_timer_fxio_pin;
  uint32_t ws2812_ret_fxio_pin;
  uint32_t ws2812_strip0_fxio_pin; /* pin number to be used for LED strip output, on PORT D */

  // enable access to all port registers
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK |\
								SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK |\
								SIM_SCGC5_PORTE_MASK;
	
  // FlexIO isr: output, low, GPIO
  FLEXIO_ISR_IOPORT->PDDR |= 1UL<<FLEXIO_ISR_PIN;
  FLEXIO_ISR_IOPORT->PCOR = 1UL<<FLEXIO_ISR_PIN;
  FLEXIO_ISR_PORT->PCR[FLEXIO_ISR_PIN] = PORT_PCR_MUX(1);

  // waiting loop: output, low, GPIO
  WAITING_LOOP_IOPORT->PDDR |= 1UL<<WAITING_LOOP_PIN;
  WAITING_LOOP_IOPORT->PCOR = 1UL<<WAITING_LOOP_PIN;
  WAITING_LOOP_PORT->PCR[WAITING_LOOP_PIN] = PORT_PCR_MUX(1);
	
	// resource allocation
	ws2812_generator_timer = 0;
	ws2812_generator_shifter = 0;
	
	// FlexIO will use the 8 MHz IRC so make sure it is on
	// and select it as the FlexIO clock source
	MCG->C1 |= MCG_C1_IRCLKEN_MASK;
	MCG->C2 |= MCG_C2_IRCS_MASK;
	MCG->MC = MCG_MC_LIRC_DIV2(0);
	MCG->SC = MCG_SC_FCRDIV(0);
	SIM->SOPT2 = (SIM->SOPT2 & SIM_SOPT2_FLEXIOSRC_MASK) | SIM_SOPT2_FLEXIOSRC(3);
	
	//FlexIO timer allocation
	ws2812_generator_timer 	= 0;
	ws2812_l0_timer					= 1;
	ws2812_l1_timer					= 2;
	ws2812_ret_timer				= 3;
	
	//FlexIO shifter allocation
	ws2812_generator_shifter= 0;

	// KL43Z pin selection (in the application) begin
	ws2812_strip0_fxio_pin					= 6; /* strip data on PTD6 */
	ws2812_generator_clk_fxio_pin		= 2; /* generator clock on PTD2 */
	ws2812_generator_data_fxio_pin	= 3; /* data 1 on PTD3 */
	ws2812_l0_timer_fxio_pin				= ws2812_strip0_fxio_pin; /* timer 0 output on strip data pin */
	ws2812_l1_timer_fxio_pin				= ws2812_strip0_fxio_pin; /* timer 1 output on strip data pin */
	ws2812_ret_fxio_pin							= 4; /* RET (end of pixel data) on PTD4 */
	
	PORTD->PCR[ 2] = PORT_PCR_MUX(6);	//PTD02 - FXIO_D2
	PORTD->PCR[ 3] = PORT_PCR_MUX(6);	//PTD03 - FXIO_D3
	PORTD->PCR[ 4] = PORT_PCR_MUX(6);	//PTD04 - FXIO_D4
	PORTD->PCR[ 6] = PORT_PCR_MUX(6);	//PTD06 - FXIO_D6
	//KL43Z pin selection (in the application) end

	// disable FLEXIO IRQ
	NVIC_DisableIRQ(UART2_FLEXIO_IRQn);

	// enable access to FlexIO registers
	SIM->SCGC5 |= SIM_SCGC5_FLEXIO_MASK;
	
	// disable FlexIO module
	FLEXIO->CTRL = 0;

	// disable shifter status & timer interrupt
	FLEXIO->SHIFTSIEN = 0;
	FLEXIO->TIMIEN		= 0;

	// ws2812_generator_shifter setup begin
	// SPI (CPHA=1) master driven by ws2812_generator_timer
	// generator outputs data at ws2812_generator_data_fxio_pin
	// this setup is based on the FlexIO SPI master example from the RM
	//==================================================================
	FLEXIO->SHIFTCTL[ws2812_generator_shifter] = 0;	//disable shifter
	
	FLEXIO->SHIFTCFG[ws2812_generator_shifter] =
									0<<FLEXIO_SHIFTCFG_INSRC_SHIFT	|	//NA
									FLEXIO_SHIFTCFG_SSTOP(0)				|	//STOP bit disabled
									FLEXIO_SHIFTCFG_SSTART(1);				//START bit disabled; load data on first shift
									
	FLEXIO->SHIFTCTL[ws2812_generator_shifter] =
									FLEXIO_SHIFTCTL_TIMSEL(ws2812_generator_timer)	|	//ws2812_generator_timer controls shifter
									0<<FLEXIO_SHIFTCTL_TIMPOL_SHIFT									|	//shift on posedge of shift clock
									FLEXIO_SHIFTCTL_PINCFG(3)												|	//shifter pin output
									FLEXIO_SHIFTCTL_PINSEL(ws2812_generator_data_fxio_pin)		|	//output: ws2812_generator_data_fxio_pin
									0<<FLEXIO_SHIFTCTL_PINPOL_SHIFT									|	//pin is active high
									FLEXIO_SHIFTCTL_SMOD(2);													//shifter mode: transmitter
	// ws2812_generator_shifter setup end
	//------------------------------------

	// ws2812_generator_timer setup begin
	// generates 32 shift edges for ws2812_generator_shifter
	// this timer output frequency matches the WS2812 bit rate
	// this setup is based on the FlexIO SPI master example from the RM
	//==================================================================
	FLEXIO->TIMCTL[ws2812_generator_timer] = 0;		//disable timer
	
	FLEXIO->TIMCMP[ws2812_generator_timer] =
								((32*2)-1)<<8 |									//32 bits
								((WS2812_CLK_DIVIDER/2)-1);			//FlexIO clock divider set to match the WS2812 timing 
								
	FLEXIO->TIMCFG[ws2812_generator_timer] =
								FLEXIO_TIMCFG_TIMOUT(1)				|	//output is logic zero when enabled not affected by reset
								FLEXIO_TIMCFG_TIMDEC(0)				|	//decrement on FlexIO clock, shift clock equals timer output
								FLEXIO_TIMCFG_TIMRST(0)				|	//never reset
								FLEXIO_TIMCFG_TIMDIS(2)				|	//disable on timer compare
								FLEXIO_TIMCFG_TIMENA(2)				|	//enabled on trigger high
								FLEXIO_TIMCFG_TSTOP(0)				|	//STOP bit disabled
								0<<FLEXIO_TIMCFG_TSTART_SHIFT;	//START bit disabled
								
	FLEXIO->TIMCTL[ws2812_generator_timer] =
								FLEXIO_TIMCTL_TRGSEL(ws2812_generator_shifter<<2 | 1)	|	//trigger: ws2812_generator_shifter status flag
								1<<FLEXIO_TIMCTL_TRGPOL_SHIFT	|	//trigger active low
								1<<FLEXIO_TIMCTL_TRGSRC_SHIFT	|	//internal trigger
								FLEXIO_TIMCTL_PINCFG(3)				|	//timer pin output
								FLEXIO_TIMCTL_PINSEL(ws2812_generator_clk_fxio_pin)		|	//output: ws2812_generator_clk_fxio_pin
								0<<FLEXIO_TIMCTL_PINPOL_SHIFT	|	//output active high
								FLEXIO_TIMCTL_TIMOD(1);					//dual 8-bit counter baud/bit mode
	// ws2812_generator_timer setup end
	//----------------------------------
	
	// ws2812_l0_timer setup begin (dual 8-bit counters PWM mode)
	//
	// a rising edge on ws2812_generator_clk enables this timer; 
	// when enabled this timer runs for 1 WS2812 bit period 
	// generating the WS2812 "0 code" waveform and then it stops;
	// ws2812_generator_clk is the trigger
	//=========================================================
	FLEXIO->TIMCTL[ws2812_l0_timer]	= 0;					//disable timer
	
	FLEXIO->TIMCMP[ws2812_l0_timer]	=
								(WS2812_T0L_CLKS-1)<< 8	|				//set PWM low period
								(WS2812_T0H_CLKS-1)<< 0;				//set PWM high period
	
	FLEXIO->TIMCFG[ws2812_l0_timer]	=
								FLEXIO_TIMCFG_TIMOUT(0) 			|	//timer outputs 1 when enabled and not affected by timer reset
								FLEXIO_TIMCFG_TIMDEC(0) 			|	//decrement on FlexIO clock
								FLEXIO_TIMCFG_TIMRST(0) 			|	//never reset
								FLEXIO_TIMCFG_TIMDIS(2)				|	//disable on compare
								FLEXIO_TIMCFG_TIMENA(6)				|	//enable on trigger rising edge
								FLEXIO_TIMCFG_TSTOP(0)				|	//stop bit disabled
								0<<FLEXIO_TIMCFG_TSTART_SHIFT;	//start bit disabled
																		
	FLEXIO->TIMCTL[ws2812_l0_timer]	=
								FLEXIO_TIMCTL_TRGSEL(ws2812_generator_clk_fxio_pin<<1 | 0)	|	//trigger select: ws2812_generator_clk_fxio_pin
								0<<FLEXIO_TIMCTL_TRGPOL_SHIFT	|	//trigger polarity: active high
								1<<FLEXIO_TIMCTL_TRGSRC_SHIFT	|	//trigger source: internal
								FLEXIO_TIMCTL_PINCFG(3)				|	//timer pin output
								FLEXIO_TIMCTL_PINSEL(ws2812_l0_timer_fxio_pin)		|	//pin: ws2812_l0_timer_fxio_pin
								0<<FLEXIO_TIMCTL_PINPOL_SHIFT	|	//pin is active high
								FLEXIO_TIMCTL_TIMOD(2);					//dual 8-bit counters PWM mode
	// ws2812_l0_timer setup end
	//---------------------------
	
	// ws2812_l1_timer setup begin (dual 8-bit counters PWM mode)
	//
	// a rising edge on ws2812_generator_data enables this timer and 
	// a falling edge on ws2812_generator_data disables this timer;
	// when enabled this timer generates back-to-back WS2812 "1 code" 
	// waveform;
	// ws2812_generator_data is the trigger
	//=========================================================
	FLEXIO->TIMCTL[ws2812_l1_timer]	= 0;					//disable timer
	
	FLEXIO->TIMCMP[ws2812_l1_timer]	=
								(WS2812_T1L_CLKS-1)<< 8	|				//set PWM low period
								(WS2812_T1H_CLKS-1)<< 0;				//set PWM high period
	
	FLEXIO->TIMCFG[ws2812_l1_timer]	=
								FLEXIO_TIMCFG_TIMOUT(0) 			|	//timer outputs 1 when enabled and not affected by timer reset
								FLEXIO_TIMCFG_TIMDEC(0) 			|	//decrement on FlexIO clock
								FLEXIO_TIMCFG_TIMRST(0) 			|	//never reset
								FLEXIO_TIMCFG_TIMDIS(6)				|	//disable on trigger falling edge
								FLEXIO_TIMCFG_TIMENA(6)				|	//enable on trigger rising edge
								FLEXIO_TIMCFG_TSTOP(0)				|	//stop bit disabled
								0<<FLEXIO_TIMCFG_TSTART_SHIFT;	//start bit disabled
																		
	FLEXIO->TIMCTL[ws2812_l1_timer]	=
								FLEXIO_TIMCTL_TRGSEL(ws2812_generator_data_fxio_pin<<1 | 0)	|	//trigger select: ws2812_generator_data_fxio_pin
								0<<FLEXIO_TIMCTL_TRGPOL_SHIFT	|	//trigger polarity: active high
								1<<FLEXIO_TIMCTL_TRGSRC_SHIFT	|	//trigger source: internal
								FLEXIO_TIMCTL_PINCFG(3)				|	//timer pin output
								FLEXIO_TIMCTL_PINSEL(ws2812_l1_timer_fxio_pin)		|	//pin: ws2812_l1_timer_fxio_pin
								0<<FLEXIO_TIMCTL_PINPOL_SHIFT	|	//pin is active high
								FLEXIO_TIMCTL_TIMOD(2);					//dual 8-bit counters PWM mode
	// ws2812_l1_timer setup end
	//---------------------------
	
	// ws2812_ret_timer setup begin (dual 8-bit counter baud/bit mode)
	//
	// runs for 50+ us; enabled and reset by the ws2812_generator_clk 
	// rising edge, disabled by compare; this timer reaches the final 
	// count and sets the flag after a RET code has been sent to the 
	// WS2812 strip; ws2812_generator_clk is the trigger
	//=================================================================
	FLEXIO->TIMCTL[ws2812_ret_timer]	= 0;				//disable timer
	
	FLEXIO->TIMCMP[ws2812_ret_timer]	=
								(((10+1)*2)-1)<<8 |
								((40/2)-1)<<0;									//50 us + 1 bit (clk leading edge resets the timer) @ 8 MHz (8 ticks per 1 us)
																								//(10+1) periods of 5 us (8 MHz/40 = 200 kHz <=> 5 us)
	
	FLEXIO->TIMCFG[ws2812_ret_timer]	=
								FLEXIO_TIMCFG_TIMOUT(0) 			|	//timer outputs logic 1 when enabled and not affected by timer reset
								FLEXIO_TIMCFG_TIMDEC(0) 			|	//decrement on FlexIO clock
								FLEXIO_TIMCFG_TIMRST(6) 			|	//reset on trigger rising edge
								FLEXIO_TIMCFG_TIMDIS(2)				|	//disable on compare
								FLEXIO_TIMCFG_TIMENA(6)				|	//enable on trigger rising edge
								FLEXIO_TIMCFG_TSTOP(0)				|	//stop bit disabled
								0<<FLEXIO_TIMCFG_TSTART_SHIFT;	//start bit disabled
																		
	FLEXIO->TIMCTL[ws2812_ret_timer]	=
								FLEXIO_TIMCTL_TRGSEL(ws2812_generator_clk_fxio_pin<<1 | 0)	|	//trigger select: ws2812_generator_clk_fxio_pin
								0<<FLEXIO_TIMCTL_TRGPOL_SHIFT	|	//trigger polarity: active high
								1<<FLEXIO_TIMCTL_TRGSRC_SHIFT	|	//trigger source: internal
								FLEXIO_TIMCTL_PINCFG(3)				|	//timer pin output enbled
								FLEXIO_TIMCTL_PINSEL(ws2812_ret_fxio_pin)		|	//pin: ws2812_ret_fxio_pin
								0<<FLEXIO_TIMCTL_PINPOL_SHIFT	|	//pin polarity: NA
								FLEXIO_TIMCTL_TIMOD(1);					//dual 8-bit counter baud/bit mode
	// ws2812_ret_timer setup end
	//----------------------------


  // Configure output pin for LED stripe
	FLEXIO->TIMCTL[ws2812_l0_timer] =
                (FLEXIO->TIMCTL[ws2812_l0_timer] & ~FLEXIO_TIMCTL_PINSEL_MASK) |
                FLEXIO_TIMCTL_PINSEL(ws2812_strip0_fxio_pin);

  FLEXIO->TIMCTL[ws2812_l1_timer] =
                (FLEXIO->TIMCTL[ws2812_l1_timer] & ~FLEXIO_TIMCTL_PINSEL_MASK) |
                FLEXIO_TIMCTL_PINSEL(ws2812_strip0_fxio_pin);
	


  FLEXIO->TIMSTAT = 1<<ws2812_ret_timer;				//clear the ret timer flag

	//enable FlexIO module
	FLEXIO->CTRL = FLEXIO_CTRL_FLEXEN_MASK;
	
  // DMA+timer isr; FLEXIO ret timer is th eonly one that generates an interrupt
  FLEXIO->SHIFTSDEN |= 1<<ws2812_generator_shifter;		//ws2812_generator_shifter status flag triggers DMA

  SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;								//enable access to DMAMUX registers
  DMAMUX0->CHCFG[2] = \
            1<<DMAMUX_CHCFG_ENBL_SHIFT	|							//enable DMA channel
            0<<DMAMUX_CHCFG_TRIG_SHIFT	|							//triggering disabled (normal mode)
            DMAMUX_CHCFG_SOURCE(10+ws2812_generator_shifter);	//source: ws2812_generator_shifter

  // interrupts; FLEXIO (shifter & timer) flags generate interrupts
  NVIC_SetPriority(UART2_FLEXIO_IRQn, 1);							//set ISR priority high, but not to 0
  while(NVIC_GetPendingIRQ(UART2_FLEXIO_IRQn) != 0)	{	//clear any pending ISRs...
    NVIC_ClearPendingIRQ(UART2_FLEXIO_IRQn);					//...
  }																										//...
  NVIC_EnableIRQ(UART2_FLEXIO_IRQn);									//enable the ISR
}

//
// use this routine to send data to a WS2812 LED strip via the DMA
// the routine sets up parameters for the FlexIO isr (triggered by ret code only)
// the DMA feeds (32-bit word) data to the shifter as long as they are available
// this routine waits for the ret code flag to get set to return
// 
// input parameters:
// - strip data pointer (32-bit data)
// - strip data length (in 32-bit words)
//
void WS2812_OutputDataDMA(uint32_t *p32_strip_data, uint32_t strip_data_word_cnt) {
	isr_data_cnt = 0;
	isr_data_index = 0;
	isr_cnt = 0;
	isr_transfer_done = 0;
	
	FLEXIO->TIMSTAT = 1<<ws2812_ret_timer;			//clear the ret timer flag
	DMA0->DMA[2].DSR_BCR =
							DMA_DSR_BCR_DONE_MASK;					//clear DONE bit => stop DMA transfers
	DMA0->DMA[2].SAR =
							(uint32_t) p32_strip_data;			//source: strip data
	DMA0->DMA[2].DAR =
							(uint32_t) &FLEXIO->SHIFTBUFBBS[ws2812_generator_shifter];	//destination: generator shifter
	DMA0->DMA[2].DSR_BCR =
							strip_data_word_cnt*4;					//number of bytes to transfer
	FLEXIO->TIMIEN |= 1<<ws2812_ret_timer;			//enable ret timer interrupt before the DMA
	DMA0->DMA[2].DCR =
							0<<DMA_DCR_EINT_SHIFT		|				//disable int on completion of transfer
							1<<DMA_DCR_ERQ_SHIFT		|				//enable peripheral request
							1<<DMA_DCR_CS_SHIFT			|				//single transfer per request
							0<<DMA_DCR_AA_SHIFT			|				//NA
							0<<24										|				//as per RM
							1<<DMA_DCR_EADREQ_SHIFT	|				//enable async DMA requests
							1<<DMA_DCR_SINC_SHIFT		|				//increment SAR
							DMA_DCR_SSIZE(0)				|				//source size: 32 bits
							0<<DMA_DCR_DINC_SHIFT		|				//do not increment DAR
							DMA_DCR_DSIZE(0)				|				//destination size: 32 bits
							0<<DMA_DCR_START_SHIFT	|				//no sw start
							DMA_DCR_SMOD(0)					|				//source address modulo buffer disabled
							DMA_DCR_DMOD(0)					|				//destination address modulo buffer disabled
							1<<DMA_DCR_D_REQ_SHIFT	|				//ERQ cleared when BCR exhausted
							DMA_DCR_LINKCC(0)				|				//no ch2ch linking
							DMA_DCR_LCH1(0)					|				//NA
							DMA_DCR_LCH2(0);								//NA
	WAITING_LOOP_IOPORT->PSOR = 1UL<<WAITING_LOOP_PIN;
	while(isr_transfer_done == 0);
	WAITING_LOOP_IOPORT->PCOR = 1UL<<WAITING_LOOP_PIN;
}

//
// this is the FlexIO interrupt service routine
//
void UART2_FLEXIO_IRQHandler(void) {
  FLEXIO_ISR_IOPORT->PSOR = 1UL<<FLEXIO_ISR_PIN;	//indicate FlexIO isr begin
	isr_cnt++;
	//if data still available, send them
	if (isr_data_index != isr_data_cnt) {
		//in case of the last round of data, disable generator shifter 
		//interrupt and enable ret timer interrupt
		if ((isr_data_index+1) == isr_data_cnt) {
			FLEXIO->SHIFTSIEN &= ~(1<<ws2812_generator_shifter);
			FLEXIO->TIMIEN |= 1<<ws2812_ret_timer;
		}
		FLEXIO->SHIFTBUFBBS[ws2812_generator_shifter] = *(isr_p32_strip_data+isr_data_index);
		isr_data_index++;
	} else {
  	//handle ret timer flag interrupt
		FLEXIO->TIMIEN &= ~(1<<ws2812_ret_timer);			//disable future ret timer interrupts
		FLEXIO->TIMSTAT = 1<<ws2812_ret_timer;				//clear the ret timer flag
		isr_transfer_done = 1;												//set ret code flag
	}
  FLEXIO_ISR_IOPORT->PCOR = 1UL<<FLEXIO_ISR_PIN;	//indicate FlexIO isr end
}

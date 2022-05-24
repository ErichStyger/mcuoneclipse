/*!
 * \file      board.c
 *
 * \brief     Target board general functions implementation
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \author    Diego Bienz
 */

#include "platform.h"
#include <stdio.h>
#include "LPC55S16.h"
#include "utilities.h"
#include "uart.h"
#include "board-config.h"
#include "board.h"
#include "sx126x-board.h"
#include "clock_config.h"
#include "pin_mux.h"
#include "gpio.h"
#include "rtc-board.h"
#include "spi.h"
#include "delay.h"
#include "gps.h"
#include "i2c.h"
#include "i2c-board.h"
#include "lpm-board.h"
#include "eeprom-board.h"
#include "fsl_power.h"
#include "McuArmTools.h"
#include "McuUtility.h"
#include "McuRTT.h"
#include "sx1276-board.h"


#if PL_CONFIG_RADIO_TRANSEIVER_SX126x
    #include "sx126x-board.h"
#elif PL_CONFIG_RADIO_TRANSEIVER_RFM96
    #include "sx1276-board.h"
#endif

/*!
 * Uart objects
 */
#if(LPC_NUMBER_OF_USARTS > 0)
Uart_t Uart0;  // Board Uart
#endif

#if BOARD_CONFIG_HAS_GNSS
Uart_t Uart1;  // GPS
#endif

#if PL_CONFIG_USE_LED1
Gpio_t Led1;
#endif
#if PL_CONFIG_USE_LED2
Gpio_t Led2;
#endif


#if BOARD_CONFIG_HAS_SECURE_ELEMENT
/*!
 * I2c objects
 */
I2c_t I2c0;  // Secure Element

/*!
 * Puts the secure element into sleep mode
 */
static void BoardPutSecureElementInSleepMode( void );
#endif

/*!
 * Puts the radio in sleep mode
 * If coldstart enabled, the radio will loose it's configuration
 * and needs to be reinitialised after wake up
 */
static void BoardPutRadioInSleepMode(bool coldstart);

/*!
 * Initializes the unused GPIO to a know status
 */
static void BoardUnusedIoInit( void );

/*!
 * System Clock Configuration
 */
static void SystemClockConfig( void );

/*!
 * System Clock Re-Configuration when waking up from STOP mode
 */
static void SystemClockReConfig( void );

/*!
 * \brief Initializes the EEPROM emulation driver to access the flash.
 *
 * \remark This function is defined in eeprom-board.c file
 */
void EepromMcuInit( void );

/*!
 * \brief Indicates if an erasing operation is on going.
 *
 * \remark This function is defined in eeprom-board.c file
 *
 * \retval isEradingOnGoing Returns true is an erasing operation is on going.
 */
bool EepromMcuIsErasingOnGoing( void );

void BoardCriticalSectionBegin( uint32_t *mask )
{
    *mask = __get_PRIMASK( );
    __disable_irq( );
}

void BoardCriticalSectionEnd( uint32_t *mask )
{
  __set_PRIMASK( *mask );
	__enable_irq();
}

void BoardInitPeriph( void )
{
#if BOARD_CONFIG_HAS_GNSS
	GpsInit();
#endif
}

void BoardInitMcu( void )
{
  BOARD_InitBootPins();
	SystemClockConfig();

#if(LPC_NUMBER_OF_USARTS > 0)
	// Configure your terminal for 8 Bits data (7 data bit + 1 parity bit), no parity and no flow ctrl
	UartInit( &Uart0, UART_1, NC, NC );
	UartConfig( &Uart0, RX_TX, BOARD_UART_BAUDRATE, UART_8_BIT, UART_1_STOP_BIT, NO_PARITY, NO_FLOW_CTRL );
#endif

  // LEDs
#if PL_CONFIG_USE_LED1
  GpioInit(&Led1, LED_1, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 1 );
#endif
#if PL_CONFIG_USE_LED2
  GpioInit(&Led2, LED_2, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 1 );
#endif

	RtcInit( );

	BoardUnusedIoInit( );


	  //SPI for LoRa transceiver
#if PL_CONFIG_RADIO_TRANSEIVER_SX126x
  //SPI for LoRa transceiver
	SpiInit( &SX126x.Spi, SPI_1, NC, NC, NC, NC );
	SX126xIoInit( );
	SX126xIoDbgInit();
	SX126xReset();
	SX126xIoTcxoInit();
#elif PL_CONFIG_RADIO_TRANSEIVER_RFM96
	SpiInit( &SX1276.Spi, SPI_1, NC, NC, NC, NC );
	SX1276IoInit( );
	SX1276IoDbgInit();
	SX1276Reset();
	SX1276IoTcxoInit();
#endif

#if BOARD_CONFIG_HAS_SECURE_ELEMENT
	//I2C for Secure Element
  I2cInit(&I2c0, I2C_1, NC, NC);
#endif

  //Actually flash on this platform
   EepromMcuInit();
}

void BoardResetMcu( void )
{
    CRITICAL_SECTION_BEGIN( );

    //Restart system
    NVIC_SystemReset( );
}

void BoardDeInitMcu( void )
{
	GpsStop();
#if(LPC_NUMBER_OF_USARTS > 0)
	if(Uart0.IsInitialized) {
		UartDeInit(&Uart0);
	}
#endif
#if BOARD_CONFIG_HAS_GNSS
	if(Uart1.IsInitialized) {
		UartDeInit(&Uart1);
	}
#endif

	BoardPutRadioInSleepMode(true);

#if PL_CONFIG_RADIO_TRANSEIVER_SX126x
	SpiDeInit(&SX126x.Spi);

#elif PL_CONFIG_RADIO_TRANSEIVER_RFM96
	SpiDeInit(&SX1276.Spi);
#endif



#if	BOARD_CONFIG_HAS_SECURE_ELEMENT
	BoardPutSecureElementInSleepMode();
	I2cDeInit(&I2c0);
#endif
}

void BoardGetUniqueId(McuArmTools_UID *id)
{
  McuArmTools_UIDGet(id);
}

uint32_t BoardGetRandomSeed( void )
{
	uint32_t seed[4];
	McuArmTools_UID uuid;

	BoardGetUniqueId(&uuid);

	seed[0] = 0;
	for(int i = 0; i < 4; i++){
		seed[0] += uuid.id[i] << 8*i;
	}
	seed[1] = 0;
	for(int i = 0; i < 4; i++){
		seed[1] += uuid.id[i+4] << 8*i;
	}
	seed[2] = 0;
	for(int i = 0; i < 4; i++){
		seed[2] += uuid.id[i+8] << 8*i;
	}
	seed[3] = 0;
	for(int i = 0; i < 4; i++){
		seed[3] += uuid.id[i+12] << 8*i;
	}
  return seed[0] ^ seed[1] ^ seed[2] ^ seed[3];
}

/**
  * NOT IMPLEMENTED ON THIS PLATFORM
  */
uint8_t BoardGetBatteryLevel( void )
{
    return 0;
}

static void BoardUnusedIoInit( void )
{
    /* Nothing to do */
}

void SystemClockConfig( void )
{
    BOARD_InitBootClocks();
}

void SystemClockReConfig( void )
{
    BOARD_InitBootClocks();
}

#if !McuLib_CONFIG_SDK_USE_FREERTOS
void SysTick_Handler( void )
{
	/* SysTick interrupt. Could be used to react on that */
}
#endif

/*!
 * \brief Enters off Power Mode (Deep Power Down on LPC55)
 * A reset is executed automatically on wake up
 *
 * Deep power-down: Deep-power down mode shuts down virtually all on-chip power
 *	consumption but requires a significantly longer wake-up time (compared to
 *	power-down mode). For maximal power savings, the entire system (CPU and all
 *	peripherals) is shut down except for the PMU, the PMC, the RTC and the OS event
 *	timer. On wake-up, the part reboots.
 *
 * IMPORTANT: SRAM retention defines which RAM sections should be retained while deep power down. It is important to place
 * variables in the retained sections if they are used after wake up from deep power down. One can place a variable
 * in a specified section as follows:
 *
 * bool __attribute__((section (".retainedSection"))) myBool = false;
 *
 * While the defined section .retainedSection is defined in the linker script.
 */
void LpmEnterOffMode( void ){
	/* First proper deinit of the MCU */
	BoardDeInitMcu();
  POWER_EnterDeepPowerDown(BOARD_EXCLUDE_FROM_DEEP_POWERDOWN, BOARD_SRAM_RETENTION_DEEP_POWERDOWN, BOARD_WAKEUP_INTERRUPTS_DEEP_POWERDOWN, 0);
}

/*!
 * \brief Exits off Power Mode
 */
void LpmExitOffMode( void ){
	/* Nothing to do, board will execute a RESET */
}

/**
  * \brief Enters Low Power Stop Mode
  *
  * \note ARM exits the function when waking up
  */
void LpmEnterStopMode( void)
{
    POWER_EnterDeepSleep(BOARD_EXCLUDE_FROM_DEEPSLEEP, BOARD_SRAM_RETENTION_DEEPSLEEP, BOARD_WAKEUP_INTERRUPTS_DEEPSLEEP, 0);
}

/*!
 * \brief Exits Low Power Stop Mode
 */
void LpmExitStopMode( void )
{
    CRITICAL_SECTION_BEGIN( );
    SystemClockReConfig();
    CRITICAL_SECTION_END( );
}

/*!
 * \brief Enters Low Power Sleep Mode
 *
 * \note ARM exits the function when waking up
 */
void LpmEnterSleepMode( void)
{
	POWER_EnterSleep();
}

void BoardLowPowerHandler( void )
{
    // Wait for any cleanup to complete before entering standby/shutdown mode
    while( EepromMcuIsErasingOnGoing( ) == true ){ }

    __disable_irq( );
    /*!
     * If an interrupt has occurred after __disable_irq( ), it is kept pending
     * and cortex will not enter low power anyway
     */

    LpmEnterLowPower( );

    __enable_irq( );
}

static void BoardPutRadioInSleepMode(bool coldstart){
    SleepParams_t params = { 0 };
    params.Fields.WarmStart = coldstart;

#if PL_CONFIG_RADIO_TRANSEIVER_SX126x
    SX126xSetSleep(params);

#elif PL_CONFIG_RADIO_TRANSEIVER_RFM96
    SX1276SetSleep();
#endif
}

void BoardPrintUUID(void) {
  McuArmTools_UID uid;
  unsigned char buf[96];

  BoardGetUniqueId(&uid);
  McuArmTools_UIDtoString(&uid, buf, sizeof(buf));
  printf( "######   Board UUID: %s   ######\r\n\r\n", buf);
}

#if BOARD_CONFIG_HAS_SECURE_ELEMENT
static void BoardPutSecureElementInSleepMode( void ){
    /* Wake up */
	uint8_t buffer[1] = {0};
    I2cMcuWriteBuffer(&I2c0, 0x00, 0, buffer, (size_t)0);
	DelayMs(100);

	/* Send to sleep */
    buffer[0] = 0x1;  // sleep word address value
    I2cMcuWriteBuffer(&I2c0, 0xC0, 0x1, buffer, (size_t)1);
}
#endif

#if !defined ( __CC_ARM )

/*
 * Function to be used by stdout for printf etc
 */
int _write( int fd, const void *buf, size_t count )
{
#if PL_CONFIG_USE_RTT
  size_t nof = count;
  char *p = (char*)buf;
  while(nof>0) {
    McuRTT_SendChar(*p);
    p++;
    nof--;
  }
#endif
#if(LPC_NUMBER_OF_USARTS > 0)
    while( UartPutBuffer( &Uart0, ( uint8_t* )buf, ( uint16_t )count ) != 0 ){ };
#elif !PL_CONFIG_USE_RTT
    McuShell_ConstStdIOType *io = McuShell_GetStdio();
    if (io!=NULL) {
      McuShell_SendData(buf, count, McuShell_GetStdio()->stdOut);
    }
#endif
    return count;
}

/*
 * Function to be used by stdin for scanf etc
 */
int _read( int fd, const void *buf, size_t count )
{
#if(LPC_NUMBER_OF_USARTS > 0)
    size_t bytesRead = 0;
    while( UartGetBuffer( &Uart0, ( uint8_t* )buf, count, ( uint16_t* )&bytesRead ) != 0 ){ };
    // Echo back the character
    while( UartPutBuffer( &Uart0, ( uint8_t* )buf, ( uint16_t )bytesRead ) != 0 ){ };
    return bytesRead;
#else
    size_t bytesRead = 0;
    McuShell_ConstStdIOType *io = McuShell_GetStdio();
    unsigned char ch;

    *(unsigned char*)buf = '\0';
    if (io==NULL) {
      return 0;
    }
    while(count>0) {
      if (io->keyPressed()) {
        io->stdIn(&ch);
        if (ch!='\0') {
          McuUtility_chcat((unsigned char*)buf, count, ch);
          count--;
        }
      }
    }
    return bytesRead;
#endif
}

#else

#include <stdio.h>

// Keil compiler
int fputc( int c, FILE *stream )
{
    while( UartPutChar( &Uart0, ( uint8_t )c ) != 0 );
    return c;
}

int fgetc( FILE *stream )
{
    uint8_t c = 0;
    while( UartGetChar( &Uart0, &c ) != 0 );
    // Echo back the character
    while( UartPutChar( &Uart0, c ) != 0 );
    return ( int )c;
}

#endif

#ifdef USE_FULL_ASSERT

#include <stdio.h>

/*
 * Function Name  : assert_failed
 * Description    : Reports the name of the source file and the source line number
 *                  where the assert_param error has occurred.
 * Input          : - file: pointer to the source file name
 *                  - line: assert_param error line source number
 * Output         : None
 * Return         : None
 */
void assert_failed( uint8_t* file, uint32_t line )
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %lu\n", file, line) */

    printf( "Wrong parameters value: file %s on line %lu\n", ( const char* )file, line );
    /* Infinite loop */
    while( 1 )
    {
    }
}
#endif

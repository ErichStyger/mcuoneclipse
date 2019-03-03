/**
 * \file
 * \brief Application configuration file for SSD1351 display driver
 *
 * This header file is a configuration header file to configure the module LCD1 (SSD1351).
 * You can configure the defines directly in this file or with the compiler -D option.
 */

#ifndef __LCD1_CONFIG_H
#define __LCD1_CONFIG_H

#ifndef LCD1_CONFIG_SPI_HEADER_FILE
  #define LCD1_CONFIG_SPI_HEADER_FILE   "SM1.h"
    /*!< Header file to be included for the SPI driver */
#endif

#ifndef LCD1_CONFIG_SPI_MODE
    /*!< 0: using software (bit banging) SPI; 1: using non-LDD hardware SPI; 3: using LDD hardware SPI */
#endif

#ifndef LCD1_CONFIG_SPI_SEND_CHAR
  /*!< method to send a character */
#endif

#ifndef LCD1_CONFIG_NOF_TX_CHAR
  /*!< method which returns how many characters are in the tx buffer */
#endif

#ifndef LCD1_CONFIG_DYNAMIC_DISPLAY_ORIENTATION
  #define LCD1_CONFIG_DYNAMIC_DISPLAY_ORIENTATION (1)
  /*!< 1: Use SetDisplayOrientation() to change display orientation at runtime; 0: fixed display orientation */
#endif

/* display orientation types used in macro below: */
#define LCD1_CONFIG_ORIENTATION_PORTRAIT      0
#define LCD1_CONFIG_ORIENTATION_PORTRAIT180   1
#define LCD1_CONFIG_ORIENTATION_LANDSCAPE     2
#define LCD1_CONFIG_ORIENTATION_LANDSCAPE180  3

#ifndef LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION
  #define LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION    LCD1_CONFIG_ORIENTATION_PORTRAIT
  /*!< Fixed display orientation setting, one of:
    LCD1_CONFIG_ORIENTATION_PORTRAIT
    LCD1_CONFIG_ORIENTATION_PORTRAIT180
    LCD1_CONFIG_ORIENTATION_LANDSCAPE
    LCD1_CONFIG_ORIENTATION_LANDSCAPE180
  */
#endif

#ifndef LCD1_CONFIG_CLEAR_DISPLAY_IN_INIT
  #define LCD1_CONFIG_CLEAR_DISPLAY_IN_INIT (0)
  /*!< 1: Clear display at the end of Init(); 0: Do not clear display at the end of Init() */
#endif

#ifndef LCD1_CONFIG_HWSPI_DELAY_US
  #define LCD1_CONFIG_HWSPI_DELAY_US    (0)
  /*!< Delay after an SPI transfer, use zero for not using a delay */
#endif

#ifndef LCD1_CONFIG_USE_RAM_BUFFER
  #define LCD1_CONFIG_USE_RAM_BUFFER    (1)
  /*!< 1: Use RAM Buffer for display memory; 0: Do not use RAM buffer (write directly to display) */
#endif

/* set of different possible SPI drivers */
#define LCD1_CONFIG_SPI_API_SW     1 /* bit banging SW SPI */
#define LCD1_CONFIG_SPI_API_HW     2 /* Hardware (non-LDD) SPI */
#define LCD1_CONFIG_SPI_API_HW_LDD 3 /* Hardware (LDD) SPI */

/* configuration of SPI API and method names */
#ifndef LCD1_CONFIG_USE_SPI_API
   #define LCD1_CONFIG_USE_SPI_API                     LCD1_CONFIG_SPI_API_HW_LDD
   #define LCD1_CONFIG_SPI_API_FCT_NAME_SEND           SM1_SendChar
   #define LCD1_CONFIG_SPI_API_FCT_NAME_RECEIVE        ReceiveChar
   #define LCD1_CONFIG_SPI_API_FCT_NAME_SEND_BLOCK     SM1_SendBlock
   #define LCD1_CONFIG_SPI_API_FCT_NAME_RECEIVE_BLOCK  SM1_ReceiveBlock
   #define LCD1_CONFIG_SPI_API_FCT_NAME_CHECK_TX       SM1_GetCharsInTxBuf
   #define LCD1_CONFIG_SPI_API_FCT_NAME_CHECK_RX       GetCharsInRxBuf
   #define LCD1_CONFIG_SPI_API_DEVICE_HANDLE           SM1_DeviceData
#endif

#if !defined(LCD1_CONFIG_PARSE_COMMAND_ENABLED)
  #define LCD1_CONFIG_PARSE_COMMAND_ENABLED                (0)
    /*!< 1: shell support enabled, 0: otherwise */
#endif

/* Contrast Master (Command 0xC7) and Contrast ABC values (Command 0xC1) */
#define LCD1_CONFIG_CONTRAST_MASTER   0x0F /* Adafruit default: 0x0F */
#define LCD1_CONFIG_CONTRAST_A        0xC8 /* Adafruit default: 0xC8 */
#define LCD1_CONFIG_CONTRAST_B        0x80 /* Adafruit default: 0x80 */
#define LCD1_CONFIG_CONTRAST_C        0xC8 /* Adafruit default: 0xC8 */

#ifndef LCD1_CONFIG_USE_BUS_SHARING
  #define LCD1_CONFIG_USE_BUS_SHARING  (0)
  #define LCD1_CONFIG_USE_BUS_SHARING_OnGet   OnGetBus
  #define LCD1_CONFIG_USE_BUS_SHARING_OnGive  OnGiveBus
    /*!< 1: Share SPI bus and generate OnGetLCD() and OnGiveLCD() events. 0: do not share bus */
#endif
/* prototypes */
extern void LCD1_CONFIG_USE_BUS_SHARING_OnGet(void);  /* called at the start of display critical section */
extern void LCD1_CONFIG_USE_BUS_SHARING_OnGive(void); /* called at the end of the display critical section */

#endif /* __LCD1_CONFIG_H */

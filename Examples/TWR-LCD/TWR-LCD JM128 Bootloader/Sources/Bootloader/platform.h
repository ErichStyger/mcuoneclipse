/** ###################################################################
**     Filename  : platform.H
**     Project   : TWR_LCD_JM128
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 21.01.2010, 08:24
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __platform_H
#define __platform_H

/* MODULE platform */

#include "Cpu.h" /* contains PEcfg_xxxxx macros */

/* target CPU */
#define PL_CPU_MCF51JM128  defined(CPU_DERIVATIVE_MCF51JM128)
#define PL_CPU_MCF51CN128  defined(CPU_DERIVATIVE_MCF51CN128)
#define PL_CPU_MCF52259    defined(CPU_DERIVATIVE_MCF52259_144_LQFP)
#define PL_LIMITED_NYI     (PL_CPU_MCF52259) /* for V2 we have several things not implemented/available, e.g. flash programming */

/* which TWR-LCD hardware */
#define PL_TWR_LCD_REV_0    defined(PEcfg_CN128_Rev0_ECUI_FlexBus_Accel)  /* Rev.0 board, which has the display 180 degree rotated, and different position for the navigation switch */
#define PL_TWR_LCD_REV_A    (   defined(PEcfg_JM128_RevA_BL_ECUI_SPI) \
                             || defined(PEcfg_JM128_RevA_noBL_ECUI_SPI) \
                             || defined(PEcfg_JM128_RevA_BL_TWR_I2C) \
                             || defined(PEcfg_JM128_RevA_Bootloader) \
                             || defined(PEcfg_CN128_RevA_ECUI_FlexBus_Accel) \
                             || defined(PEcfg_CN128_RevA_ECUI_FlexBus_SD) \
                             || defined(PEcfg_52259_RevA_ECUI_SPI_Accel) \
                             || defined(PEcfg_52259_RevA_ECUI_FlexBus_Accel) \
                            ) /* TWR-LCD Rev A board */
                            
#define PL_TWR_BOOTLOADER   (   defined(PEcfg_JM128_RevA_BL_ECUI_SPI) \
                             || defined(PEcfg_JM128_RevA_BL_TWR_I2C) \
                            ) /* Bootloader applications */

/* RTOS configuration */
#define PL_USE_RTOS         (   defined(PEcfg_CN128_Rev0_ECUI_FlexBus_Accel) \
                             || defined(PEcfg_JM128_RevA_BL_ECUI_SPI) \
                             || defined(PEcfg_JM128_RevA_BL_TWR_I2C) \
                             || defined(PEcfg_JM128_RevA_noBL_ECUI_SPI) \
                             || defined(PEcfg_CN128_RevA_ECUI_FlexBus_Accel) \
                             || defined(PEcfg_CN128_RevA_ECUI_FlexBus_SD) \
                             || defined(PEcfg_52259_RevA_ECUI_SPI_Accel) \
                             || defined(PEcfg_52259_RevA_ECUI_FlexBus_Accel) \
                            ) /* configurations using RTOS */

/* which board we are */
#define PL_BOARD_LCD        (   defined(PEcfg_JM128_RevA_BL_ECUI_SPI) \
                             || defined(PEcfg_JM128_RevA_noBL_ECUI_SPI) \
                             || defined(PEcfg_JM128_RevA_BL_TWR_I2C) \
                             || defined(PEcfg_JM128_RevA_Bootloader) \
                            ) /* we are the TWR-LCD board */
#define PL_BOARD_TWR        (!PL_BOARD_LCD) /* we are the tower board, e.g. TWR-CN128 */
#define PL_BOARD_TWR_CN128  (PL_CPU_MCF51CN128 && !PL_BOARD_LCD) /* TWR-CN128 board */
#define PL_BOARD_TWR_52259  (PL_CPU_MCF52259 && !PL_BOARD_LCD) /* TWR-52259 board */

/* which protocol is used */
#define PL_TWR_LCD_SPI4     (   defined(PEcfg_JM128_RevA_BL_ECUI_SPI) \
                             || defined(PEcfg_JM128_RevA_noBL_ECUI_SPI) \
                             || defined(PEcfg_JM128_RevA_BL_ECUI_SPI) \
                             || defined(PEcfg_52259_RevA_ECUI_SPI_Accel) \
                            )
#define PL_TWR_LCD_16BIT    (   defined(PEcfg_CN128_RevA_ECUI_FlexBus_Accel) \
                             || defined(PEcfg_CN128_RevA_ECUI_FlexBus_SD) \
                             || defined(PEcfg_52259_RevA_ECUI_FlexBus_Accel) \
                            )

/* hardware */
#define PL_HAS_HW_SOUNDER         1  /* if we have a buzzer for audible feedback */
#define PL_HAS_HW_ACCELEROMETER   (    defined(PEcfg_CN128_RevA_ECUI_FlexBus_Accel) \
                                    || defined(PEcfg_CN128_Rev0_ECUI_FlexBus_Accel) \
                                    || defined(PEcfg_52259_RevA_ECUI_FlexBus_Accel) \
                                    || defined(PEcfg_52259_RevA_ECUI_SPI_Accel) \
                                  )  /* if we have an acceleration sensor */
#define PL_HAS_HW_TOUCHSCREEN     (   (PL_TWR_LCD_REV_0 || PL_TWR_LCD_REV_A) \
                                   && !defined(PEcfg_JM128_RevA_Bootloader) \
                                   && !defined(PEcfg_JM128_RevA_BL_TWR_I2C) \
                                   /*&& !PL_LIMITED_NYI */  \
                                  )   /* if we use the touchscreen */
#define PL_HAS_TOUCH_CALIB_FLASH  (!PL_LIMITED_NYI && PL_HAS_HW_TOUCHSCREEN) /* if we can program flash with touchscreen calibration data */
#define PL_HAS_HW_LCD             ((PL_TWR_LCD_REV_0 || PL_TWR_LCD_REV_A) && !defined(PEcfg_JM128_RevA_Bootloader) && !defined(PEcfg_JM128_RevA_BL_TWR_I2C))   /* if we have an LCD */
#define PL_HAS_HW_SD_CARD         (PL_TWR_LCD_REV_A && !defined(PEcfg_CN128_RevA_ECUI_FlexBus_Accel) && !defined(PEcfg_52259_RevA_ECUI_SPI_Accel))   /* if we have SD (Secure Data) card slot */
#define PL_HAS_HW_TP_SEL          (PL_TWR_LCD_REV_A && PL_CPU_MCF51JM128) /* if we have the TP_SEL signal (only on RevA board) */
#define PL_HAS_HW_BTLD            (PL_TWR_LCD_REV_A && PL_CPU_MCF51JM128) /* if we have the BTLD (Bootloader) signal (only on RevA board) */
#define PL_HAS_HW_NAV_SWITCH      (PL_TWR_LCD_REV_0 || (PL_TWR_LCD_REV_A && PL_CPU_MCF51JM128 && !PL_IS_BOOTLOADER))
    /*!< if we have switches to navigate */
#define PL_HAS_HW_LED             (PL_CPU_MCF51CN128 || PL_BOARD_TWR_52259) /* TWR board has LED's we can use */
#define PL_HAS_HW_USB             (PL_CPU_MCF51JM128)
#define PL_HAS_KEY_SET2           (PL_BOARD_TWR_CN128) /* if we have a second set of keys */
#define PL_POLL_KEYS2             (PL_TWR_LCD_REV_0 || PL_BOARD_TWR_52259) /* if we have to poll keys */

/* bootloader configuration */
#define PL_HAS_BOOTLOADER         (PL_BOARD_LCD && PL_TWR_BOOTLOADER) /* if we have support for bootloader */
#define PL_IS_BOOTLOADER          defined(PEcfg_JM128_RevA_Bootloader) /* if we are just the bootloader */
#define PL_BOOTLOADER_LCD         (1 && PL_IS_BOOTLOADER) /* if bootloader shall use the LCD. Requires the JM_ELE switch in OFF position and SW1-1 OFF and SW1-2 ON for SPI communication to LCD */

/* application mode */
#define PL_APP_MODE_I2C_LCD       (   defined(PEcfg_JM128_RevA_BL_TWR_I2C) \
                                   || defined(PEcfg_JM128_RevA_BL_ECUI_SPI) \
                                   || defined(PEcfg_JM128_RevA_noBL_ECUI_SPI) \
                                  ) /* if we are the TWR-LCD board sending I2C messages */
#define PL_APP_MODE_I2C_TWR       (!PL_LIMITED_NYI && PL_BOARD_TWR && !PL_TWR_LCD_REV_0) /* if we are the TWR board using I2C */
#define PL_HAS_I2C_COMM           (PL_APP_MODE_I2C_LCD || PL_APP_MODE_I2C_TWR) /* if we communicate with I2C */
#define PL_IS_I2C_MASTER          (PL_HAS_I2C_COMM && PL_APP_MODE_I2C_TWR) /* tower is master */
#define PL_IS_I2C_SLAVE           (PL_HAS_I2C_COMM && PL_APP_MODE_I2C_LCD) /* LCD is slave */

/* touch screen calibration area, size 0xF0 bytes, but need only about 10 bytes for now */
#if PL_HAS_TOUCH_CALIB_FLASH
  #if defined(CPU_DERIVATIVE_MCF51JM128)
    #define PL_TOUCHSCREEN_FLASH_CALIBRATION_ADDRESS 0x1FF10 /* block of 0xF0 bytes in flash. Make sure you have this area reserved */ 
  #elif defined(CPU_DERIVATIVE_MCF51CN128)
    #define PL_TOUCHSCREEN_FLASH_CALIBRATION_ADDRESS 0x1FF10 /* block of 0xF0 bytes in flash. Make sure you have this area reserved */ 
  #else
    #error "unknown CPU, check cpu.h file"
  #endif
#endif
/* Demo configuration for Embedded Component UI. Some demos are disabled for bootloader applications (otherwise they do not fit into flash memory. */
#define PL_HAS_UI                 (   defined(PEcfg_JM128_RevA_BL_ECUI_SPI) \
                                   || defined(PEcfg_CN128_Rev0_ECUI_FlexBus_Accel) \
                                   || defined(PEcfg_JM128_RevA_noBL_ECUI_SPI) \
                                   || defined(PEcfg_CN128_RevA_ECUI_FlexBus_Accel) \
                                   || defined(PEcfg_52259_RevA_ECUI_SPI_Accel) \
                                   || defined(PEcfg_52259_RevA_ECUI_FlexBus_Accel) \
                                  )
#if PL_HAS_UI
  #include "UI1.h" /* for UI1_FIXED_FONT */
#endif

#define PL_HAS_WATCHDOG           (0) /* if we have a watchdog */
#define PL_HAS_SHELL              (1 && (PL_BOARD_TWR_52259/* || PL_BOARD_TWR_CN128*/)) /* if we have a console and shell available */
#define PL_USE_SINGLE_FONT        (0 && PL_HAS_UI) /* if we use just one single font (Helv10n) to reduce ROM size */
#define PL_HAS_TOUCHSCREEN_DEMO   (1 && PL_HAS_UI && PL_HAS_HW_TOUCHSCREEN)  /* if we include touch screen demo */
#define PL_HAS_CALIBRATION_DEMO   (1 && PL_HAS_UI && PL_HAS_HW_TOUCHSCREEN)  /* if we include a calibration demo */
#define PL_HAS_CUBE_DEMO          (1 && PL_HAS_UI)  /* if we include the 3D rotating cube demo */
#define PL_HAS_SHIP_DEMO          (1 && PL_HAS_UI && PL_HAS_CUBE_DEMO)  /* if include the ship demo in addition to the cube demo */
#define PL_HAS_TETRIS_DEMO        (1 && PL_HAS_UI)  /* if we include the Tetris game demo */
#define PL_HAS_FONT_DEMO          (0 && PL_HAS_UI && !PL_USE_SINGLE_FONT )  /* if we show the font demo */
#define PL_HAS_LARGE_FONT_DEMO    (0 && PL_HAS_UI && PL_HAS_FONT_DEMO)/* this will show large fonts, but needs more ROM */
#define PL_HAS_CALENDAR_DEMO      (0 && PL_HAS_UI)  /* if we show the calendar demo */
#define PL_HAS_TASKLIST           (1 && PL_HAS_UI && PL_USE_RTOS) /* if we show a list of RTOS tasks */
#define PL_HAS_ACCEL_DEMO         (1 && PL_HAS_UI && (PL_HAS_HW_ACCELEROMETER || PL_APP_MODE_I2C_LCD)) /* if we demo the accelerator sensor (either through hardware or through I2C messages */
#define PL_HAS_ACCEL_ORIENT       (1 && PL_HAS_UI && PL_HAS_HW_ACCELEROMETER) /* if we change the display through accelerometer orientation */
#define PL_HAS_SD_DEMO            (0 && PL_HAS_UI && PL_HAS_HW_SD_CARD) /* if we demo the microSD card */
#define PL_HAS_SD_WRITE           (1 && PL_HAS_UI && PL_HAS_SD_DEMO)
#define PL_HAS_MOTOR_GRAPH        (1 && PL_HAS_UI) /* if we show motor status through I2C */
#define PL_HAS_SLIDER             (1 && PL_HAS_UI && PL_HAS_MOTOR_GRAPH) /* if we have sliders */
#define PL_HAS_AUTO_DEMO          (0) /* if we iterate automatically through demos */
#define PL_HAS_SOLAR               0

#if PL_USE_SINGLE_FONT || UI1_FIXED_FONT
  #define PL_FONT()  UI1_FIXED_FONT() /* the font we use as single font */
#endif


/* END platform */

#endif

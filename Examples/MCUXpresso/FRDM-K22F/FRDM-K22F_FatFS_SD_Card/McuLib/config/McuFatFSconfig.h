/**
 * \file
 * \brief Configuration header file for FAT_FileSystem
 *
 * This header file is used to configure settings of the Generic I2C module.
 */

#ifndef __McuFatFS_CONFIG_H
#define __McuFatFS_CONFIG_H

#ifndef McuFatFS_CONFIG_CARD_INSERT_DELAY_TIME_MS
  #define McuFatFS_CONFIG_CARD_INSERT_DELAY_TIME_MS    (100)
    /*!< Delay time in milliseconds after insertion of the card detected */
#endif

#ifndef McuFatFS_CONFIG_SHELL_ENABLED
  #define McuFatFS_CONFIG_SHELL_ENABLED    (1)
    /*!< 1: Shell support is enabled; 0: no shell support enabled */
#endif

#ifndef McuFatFS_CONFIG_DEFAULT_DRIVE_STRING
  #define McuFatFS_CONFIG_DEFAULT_DRIVE_STRING    "0:/"
    /*!< default drive used for commands. The first letter defines the drive */
#endif


#endif /* __McuFatFS_CONFIG_H */


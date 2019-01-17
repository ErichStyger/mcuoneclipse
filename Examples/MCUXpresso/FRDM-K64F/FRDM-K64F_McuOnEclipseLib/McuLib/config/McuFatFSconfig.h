/**
 * \file
 * \brief Configuration header file for FAT_FileSystem
 *
 * This header file is used to configure settings of the Generic I2C module.
 */

#ifndef __McuFatFS_CONFIG_H
#define __McuFatFS_CONFIG_H

#if !defined(McuFatFS_CONFIG_CARD_INSERT_DELAY_TIME_MS)
  #define McuFatFS_CONFIG_CARD_INSERT_DELAY_TIME_MS    (100)
    /*!< Delay time in milliseconds after insertion of the card detected */
#endif

#endif /* __McuFatFS_CONFIG_H */


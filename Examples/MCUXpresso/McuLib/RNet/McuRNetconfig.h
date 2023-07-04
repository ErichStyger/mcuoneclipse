/**
 * \file
 * \brief Configuration header file for RNet
 *
 * This header file is used to configure settings RNet module.
 */
#ifndef __McuRNet_CONFIG_H
#define __McuRNet_CONFIG_H

#include "McuLib.h"
#ifndef McuRNET_CONFIG_IS_ENABLED
  #define McuRNET_CONFIG_IS_ENABLED       (1 && McuLib_CONFIG_SDK_USE_FREERTOS)
#endif

/* remote standard I/O destination address */
#ifndef RSTDIO_CONFIG_SETTING_RSTDIO_DEFAULT_DESTINATION_ADDRESS
  #define RSTDIO_CONFIG_SETTING_RSTDIO_DEFAULT_DESTINATION_ADDRESS   255
#endif

#endif /* __McuRNet_CONFIG_H */

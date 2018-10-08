/**
 * \file
 * \brief Configuration header file for MMA8451Q accelerometer
 *
 * This header file is used to configure settings of the MMA8451Q module.
 */

#ifndef __MMA1_CONFIG_H
#define __MMA1_CONFIG_H

#if !defined(MMA1_CONFIG_INIT_DRIVER_IN_STARTUP)
  #define MMA1_CONFIG_INIT_DRIVER_IN_STARTUP  (0)
   /*!< 1: Initialize driver durin startup, 0: Do not call Init during startup */
#endif

#endif /* __MMA1_CONFIG_H */

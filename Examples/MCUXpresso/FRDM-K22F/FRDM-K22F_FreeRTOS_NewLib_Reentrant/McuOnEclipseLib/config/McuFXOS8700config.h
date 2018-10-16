/**
 * \file
 * \brief Configuration header file for FXOS8700CQ accelerometer
 *
 * This header file is used to configure settings of the FXOS8700CQ module.
 */

#ifndef __McuFXOS8700_CONFIG_H
#define __McuFXOS8700_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(McuFXOS8700_CONFIG_PARSE_COMMAND_ENABLED)
  #define McuFXOS8700_CONFIG_PARSE_COMMAND_ENABLED  1
    /*!< 1: shell support enabled, 0: otherwise */
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* __McuFXOS8700_CONFIG_H */

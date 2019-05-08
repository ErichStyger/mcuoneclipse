/*
 * McuLEDconfig.h
 */

#ifndef MCULED_CONFIG_H_
#define MCULED_CONFIG_H_

#define MCULED_USE_DYNAMIC_MEMORY    (1)

#if !MCULED_USE_DYNAMIC_MEMORY
  #define MCULED_CONFIG_MAX_NOF_LEDS  (5)
#endif

#endif /* MCULEDCONFIG_H_ */

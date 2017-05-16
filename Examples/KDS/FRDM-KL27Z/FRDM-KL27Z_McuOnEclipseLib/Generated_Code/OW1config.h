/**
 * \file
 * \brief Configuration header file for 1-Wire
 *
 * This header file is used to configure settings of the 1-Wire module.
 */

#ifndef __OW1_CONFIG_H
#define __OW1_CONFIG_H

/* timing in micro seconds */
#define OW1_CONFIG_A_WRITE_1_LOW_TIME                       6 /* A */
#define OW1_CONFIG_B_WRITE_1_HIGH_TIME                      64 /* B */
#define OW1_CONFIG_C_WRITE_0_LOW_TIME                       60 /* C */
#define OW1_CONFIG_D_WRITE_0_HIGH_TIME                      10 /* D */
#define OW1_CONFIG_H_RESET_TIME                             480 /* H */
#define OW1_CONFIG_I_RESPONSE_TIME                          70 /* I */
#define OW1_CONFIG_A_READ_TIME                              OW1_CONFIG_A_WRITE_1_LOW_TIME /* A (for read) */
#define OW1_CONFIG_E_BEFORE_READ_DELAY_TIME                 1 /* E */
#define OW1_CONFIG_F_AFTER_READ_DELAY_TIME                  55 /* F */
#define OW1_CONFIG_SLOT_TIME                                100

#define OW1_CONFIG_DEBUG_READ_PIN_ENABLED                   (1)
  /*!< 1: Toggle extra GPIO pin during 1-wire read access; 0: no debug */

#if OW1_CONFIG_DEBUG_READ_PIN_ENABLED
  #include "DbgRd1.h" /* SDK and API used */
  #define OW1_CONFIG_DEBUG_READ_PIN_INIT                    DbgRd1_Init()
  #define OW1_CONFIG_DEBUG_READ_PIN_TOGGLE                  DbgRd1_NegVal()
#endif

#ifndef OW1_CONFIG_WRITE_PIN
  #define OW1_CONFIG_WRITE_PIN                              (0)
    /*!< 1: using dedicated write pin; 0: using single pin for read/write */
#endif

#if OW1_CONFIG_WRITE_PIN
  #include "WritePin.h"
  #define OW1_CONFIG_WRITE_PIN_INIT                         WritePin_Init()
  #define OW1_CONFIG_WRITE_PIN_LOW                          WritePin_ClrVal()
  #define OW1_CONFIG_WRITE_PIN_SET_OUTPUT                   WritePin_SetOutput()
#endif

#ifndef OW1_CONFIG_TIMER_UNIT_LDD
  #define OW1_CONFIG_TIMER_UNIT_LDD                         (0)
    /*!< 1: using TimerUnit_LDD, 0: not using TimerUnit_LDD */
#endif

#if !defined(OW1_CONFIG_PARSE_COMMAND_ENABLED)
  #define OW1_CONFIG_PARSE_COMMAND_ENABLED       (1)
    /*!< 1: shell support enabled, 0: otherwise */
#endif

#endif /* __OW1_CONFIG_H */
